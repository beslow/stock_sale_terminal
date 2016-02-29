//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <System.RegularExpressionsCore.hpp>
#include "curl.h"
#include "UThreadCurl.h"
#pragma package(smart_init)
#include "UMain.h"
#pragma comment (lib, "msvcrt.lib")

//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TThreadCurl::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

extern TStringList *msglist;


__fastcall TThreadCurl::TThreadCurl(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}

//---------------------------------------------------------------------------
void TThreadCurl::prepare_memorystruct(AnsiString iurl, AnsiString ireferer, AnsiString icookie)
{
	memory = (char *) malloc(1);  /* will be grown as needed by the realloc */
	size_downloaded = 0;    /* no data at this point */
	size_memory = 1;
	content_length = 0;
	start_byte = 0;
	last_byte = 0;
	stop_byte = 0;
	can_resume = 0;
	url = iurl;
	referer = ireferer;
	cookie = icookie;
	header = 0;
	invalid = 0;
	http_code = 0;
	header_filename = "";
	download_step = STEP_DOWNLOAD_NOTHING;
	download_prev_step = STEP_DOWNLOAD_NOTHING;
}

//---------------------------------------------------------------------------
void __fastcall TThreadCurl::Execute()
{
	do_run = 1;
	while(do_run) {
		switch(download_step)
		{

			case STEP_DOWNLOAD_HEADER :
				download_prev_step = download_step;
				do_curl(this, 0, 0, 1); // get header only
				download_step = STEP_DOWNLOAD_NOTHING;
				break;

			case STEP_DOWNLOAD_DATA_FIRST :
				download_prev_step = download_step;
				start_byte = 0;
				last_byte = 0;
				size_downloaded = 0;
				header = 1;
				do_curl(this, 0, 0, 0); // get data
				download_step = STEP_DOWNLOAD_NOTHING;
				break;

			case STEP_DOWNLOAD_DATA :
				download_prev_step = download_step;
				do_curl(this, 0, 0, 0); // get data
				download_step = STEP_DOWNLOAD_NOTHING;
				break;
			case STEP_DOWNLOAD_NOTHING :
				break;// do nothing, wait for step command
		}
		Sleep(100);
	}

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
int do_curl(TThreadCurl *chunk, unsigned long range_from, unsigned long range_to, int headeronly) {
	chunk->status = CURL_STARTED;
  CURL *curl_handle;
  CURLcode res;
  curl_handle = curl_easy_init();

  /* specify URL to get */
//  curl_easy_setopt(curl_handle, CURLOPT_URL, "http://www.example.com/");
  curl_easy_setopt(curl_handle, CURLOPT_URL, chunk->url.c_str());
  if (chunk->referer != "") {
	curl_easy_setopt(curl_handle, CURLOPT_REFERER, chunk->referer.c_str());
  }

  if (chunk->cookie != "") {
	curl_easy_setopt(curl_handle, CURLOPT_COOKIE, chunk->cookie.c_str());
  }

//  curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT, 60);
	curl_easy_setopt(curl_handle, CURLOPT_LOW_SPEED_LIMIT, 1);

	if (chunk->invalid) {
		chunk->status = CURL_TERMINATED;
		return 0;
	}

	int len;
	char *unescaped = curl_easy_unescape(curl_handle, chunk->url.c_str(), chunk->url.Length(), &len);
	chunk->unescaped = unescaped;
	curl_free(unescaped);

  /* send header data to this function  */
	curl_easy_setopt(curl_handle, CURLOPT_HEADERFUNCTION, header_callback);
	curl_easy_setopt(curl_handle, CURLOPT_HEADERDATA, (void*) chunk);

	curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYHOST, 0L);

  /* send content to this function  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

  /* we pass our 'chunk' struct to the callback function */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*) chunk);

	if(headeronly > 0) {
//		curl_easy_setopt(curl_handle, CURLOPT_HEADERFUNCTION, header_callback);
//		curl_easy_setopt(curl_handle, CURLOPT_HEADERDATA, (void*) chunk);
		curl_easy_setopt(curl_handle, CURLOPT_HEADER, 1);
		curl_easy_setopt(curl_handle, CURLOPT_NOBODY, 1);
	}


	/* range download, FROM-TO byte */
	if ((range_from + range_to) > 0) {
		AnsiString srange = AnsiString().sprintf("%ld-%ld", range_from, range_to);
		msglist->Add("\r\n---\r\nDownload range: " + srange);
		curl_easy_setopt(curl_handle, CURLOPT_RANGE, srange.c_str());
		chunk->start_byte = range_from;
		chunk->last_byte = range_from;
		chunk->stop_byte = range_to;
		chunk->size_downloaded = range_from;
	}
	else
	if (chunk->stop_byte > chunk->last_byte) {
		AnsiString autorange = AnsiString().sprintf("%ld-%ld", chunk->last_byte, chunk->stop_byte);
		msglist->Add("Autorange: " + AnsiString(autorange));
		curl_easy_setopt(curl_handle, CURLOPT_RANGE, autorange.c_str());
		chunk->last_byte = chunk->last_byte;
		chunk->stop_byte = chunk->stop_byte;
		chunk->size_downloaded = chunk->last_byte;
	}
	else
	if (chunk->stop_byte > 0 && chunk->last_byte > 0) {
		msglist->Add("nothing to do");
		chunk->status = CURL_TERMINATED;
		return 0;
	}
  /* some servers don't like requests that are made without a user-agent
	 field, so we provide one */
//  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.7.8) Gecko/20050511 Firefox/1.0.4");

  /* get it! */
	/* perform curl download */
  res = curl_easy_perform(curl_handle);

  /* check for errors */
  if(res != CURLE_OK) {
	msglist->Add("Err: " + AnsiString(curl_easy_strerror(res)));
	chunk->status = CURL_TERMINATED;
  }
  else {
	/*
	 * Now, our chunk.memory points to a memory block that is chunk.size
	 * bytes big and contains the remote file.
	 *
	 * Do something nice with it!
	 */

//	Memo1->Lines->Add(AnsiString().sprintf("%lu bytes retrieved\n", (long)chunk.size_downloaded));
  }

  /* cleanup curl stuff */
  curl_easy_cleanup(curl_handle);

	chunk->status = CURL_TERMINATED;
	return res;
}

//---------------------------------------------------------------------------
size_t header_callback(char *buffer,   size_t size,   size_t nmemb,   void *userdata)
{
//	ShowMessage(buffer);

	msglist->Add("HEADER: " + AnsiString(buffer).TrimRight());

	TPerlRegEx *pcre = new TPerlRegEx();

	TThreadCurl *curl = (TThreadCurl *)userdata;

	pcre->RegEx = "(ACCEPT-RANGE)";
	pcre->Options = TPerlRegExOptions() << preCaseLess;
	pcre->Subject = AnsiString(buffer);//.UpperCase();
	if (pcre->Match()) {
//		msglist->Add("ACCEPT RANGE YAY ---------------------------");
		msglist->Add(buffer);
		curl->can_resume = 1;
	}

	pcre->RegEx = "HTTP\\/.*\\s*(\\d\\d\\d)";
	pcre->Options = TPerlRegExOptions() << preCaseLess;
	pcre->Subject = AnsiString(buffer);//.UpperCase();
	if (pcre->Match()) {
		curl->http_code = StrToInt(pcre->Groups[1]);
		if (curl->http_code > 206) {
			curl->invalid = 1;// cancel download
		}
	}

	pcre->RegEx = "Content-Disposition:";
	pcre->Options = TPerlRegExOptions() << preCaseLess;
	pcre->Subject = AnsiString(buffer);//.UpperCase();
	if (pcre->Match()) {
		pcre->RegEx = "Content-Disposition:.*filename=[\"\'](.*)[\"\']";
		pcre->Options = TPerlRegExOptions() << preCaseLess;
		pcre->Subject = AnsiString(buffer);//.UpperCase();
		if (pcre->Match()) {
			curl->header_filename = pcre->Groups[1];
		} else {
			pcre->RegEx = "Content-Disposition:.*filename=\\s*([^\\s]+)[\\s$]";
			pcre->Options = TPerlRegExOptions() << preCaseLess;
			pcre->Subject = AnsiString(buffer);//.UpperCase();
			if (pcre->Match()) {
				curl->header_filename = pcre->Groups[1];
			}
		}
	}

	pcre->RegEx = "CONTENT-LENGTH\\s*:\\s*(\\d+)";
	pcre->Options = TPerlRegExOptions() << preCaseLess;
	pcre->Subject = AnsiString(buffer);//.UpperCase();
	if (pcre->Match()) {
		msglist->Add(" --- CONTENT LENGTH: " + pcre->Groups[1]);
		unsigned long ctlen = StrToInt(pcre->Groups[1]);

		// CHECK HTTP PROTOCOL, WHY SUBSEQUENT CONTENT LENGTH REDUCED WITH DOWNLOADED SIZE
		if (ctlen > curl->content_length) {
			curl->content_length = ctlen;
		}
		size_t total_chunk_size = curl->content_length + 1;
		curl->memory = (char *) realloc(curl->memory, total_chunk_size);
		curl->size_memory = total_chunk_size;
		curl->stop_byte = curl->content_length;
		if(curl->memory == NULL) {
		/* out of memory! */
			msglist->Add("not enough memory (realloc returned NULL)\n");
		return 0;
	  }
	}
	size_t realsize = size * nmemb;
	return  realsize;
}

//---------------------------------------------------------------------------
size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  TThreadCurl *curl = (TThreadCurl *)userp;
  curl->status = CURL_RECEIVING;
  size_t total_chunk_size = curl->size_downloaded + realsize + 1;

  if (curl->size_memory < total_chunk_size) {
	curl->memory = (char *) realloc(curl->memory, total_chunk_size);
	curl->size_memory = total_chunk_size;
  }

  if(curl->memory == NULL) {
	/* out of memory! */
	msglist->Add("not enough memory (realloc returned NULL)\n");
	return 0;
  }
  unsigned long offset = curl->size_downloaded > 0 ? curl->size_downloaded : 0;
  memcpy(&(curl->memory[offset]), contents, realsize);
  curl->last_byte = curl->last_byte + realsize;
//  msglist->Add("last byte: " + AnsiString(curl->last_byte) + "( " + AnsiString(100 * curl->last_byte / (curl->content_length > 0 ? curl->content_length : 1000)) + "% )");
  curl->size_downloaded += realsize;
  Application->ProcessMessages();
  return realsize;
}


//---------------------------------------------------------------------------
AnsiString uri_decode(AnsiString inuri)
{
	CURL *curl_handle;
	curl_handle = curl_easy_init();
	int outlength;
	char * result = curl_easy_unescape( curl_handle, inuri.c_str() , inuri.Length() , &outlength );
	AnsiString retval = result;
	curl_easy_cleanup(curl_handle);
	return retval;
}

//---------------------------------------------------------------------------

