//---------------------------------------------------------------------------

#include <vcl.h>
#include <System.RegularExpressionsCore.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Inifiles.hpp>

#pragma hdrstop

#include "curl.h"
#include "UMain.h"
#include "UThreadCurl.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;
TStringList *msglist;

#define URLSIZE 1024
#define COOKIESIZE 4096

struct TShm {
	char url[URLSIZE];
	char ref[URLSIZE];
	char ofile[URLSIZE]; // output file
	char odir[URLSIZE]; // output dir
	char cookie[COOKIESIZE]; // output dir
	char comment[COOKIESIZE]; // comment
	char sug_filename[COOKIESIZE]; // comment
	int flag;
	int que;
};
TShm *shm = NULL;
int runasserver = 0;
TList *download_que;
int download_finished = 1;
int fromcommandline = 0;
AnsiString lastoutfolder = "";
int setoutdir = 0;
enum {SHM_FLAG_FRESH = 1, SHM_FLAG_READY = 2, SHM_FLAG_TAKEN = 3, SHM_FLAG_DATAIN = 4, SHM_FLAG_WAIT = 5};

/*
large integer definition
define in: winnt.h
typedef union _LARGE_INTEGER {
  struct {
	DWORD LowPart;
	LONG  HighPart;
  };
  struct {
	DWORD LowPart;
	LONG  HighPart;
  } u;
  LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;
*/

LARGE_INTEGER shm_size;
int shmstatus = 0;
enum {APP_STATUS_SERVER = 1, APP_STATUS_CLIENT = 2};
int app_status = 0;

AnsiString sanitize(AnsiString istr) {
	AnsiString strret;
	TPerlRegEx *pcre = new TPerlRegEx();
	pcre->RegEx = "[^a-zA-Z0-9\\.]"; // replace anything else
	pcre->Replacement = "_";
	pcre->Subject = istr;
	pcre->ReplaceAll();
	strret = pcre->Subject;
	delete pcre;
	return strret;
}

//---------------------------------------------------------------------------
void BCBCurlInit()  // this function called once at Application->Initialize()
{
	download_que = new TList();
	HANDLE hMapFile;
	LPCTSTR pBuf;
	shm_size.QuadPart = sizeof(TShm);

   hMapFile = CreateFileMapping(
				 INVALID_HANDLE_VALUE,    // use paging file
				 NULL,                    // default security
				 PAGE_READWRITE,          // read/write access
				 shm_size.HighPart,                       // maximum object size (high-order DWORD)
				 shm_size.LowPart,                // maximum object size (low-order DWORD)
				 "SHM_BCBCURL");                 // name of mapping object
	int err = GetLastError();
	if (hMapFile == NULL)
	{
		AnsiString().sprintf("Could not create file mapping object (%d).\n", err);
			return;
	}
	else
	if (err == ERROR_ALREADY_EXISTS) {
//		Memo1->Lines->Add("SHM ALREADY EXISTS");
		app_status = APP_STATUS_CLIENT;
	}
	else {
//		Memo1->Lines->Add("SHM FRESH CREATED");
		shmstatus = SHM_FLAG_FRESH;
		app_status = APP_STATUS_SERVER;
	}


   shm = (TShm *) MapViewOfFile(hMapFile,   // handle to map object
						FILE_MAP_ALL_ACCESS, // read/write permission
						0,
						0,
						shm_size.QuadPart);

   if (shm == NULL)
   {
		CloseHandle(hMapFile);
   }

// from OnShow
	AnsiString outfile = "";
	AnsiString outfolder = "";
	AnsiString cookie = "";
	AnsiString url = "";
	AnsiString referer = "";
	AnsiString comment = "";
	AnsiString sug_filename = "";


	for(int i=1; i<ParamCount()+1; i++) {
	// check for outfile
		if (ParamStr(i).SubString(1, 2) == "-o"){ // output file
			if (ParamStr(i).Length() > 2) {
				outfile =ParamStr(i).SubString(3, ParamStr(i).Length()-2);
			}
			else {
				i++;
				outfile =ParamStr(i);
			}
		}

	// suggested file name (FDM placeholder)
		if (ParamStr(i).SubString(1, 2) == "-f"){ // output file
			if (ParamStr(i).Length() > 2) {
				sug_filename =ParamStr(i).SubString(3, ParamStr(i).Length()-2);
			}
			else {
				i++;
				sug_filename =ParamStr(i);
			}
		}

	// check for outfolder
		else
		if (ParamStr(i).SubString(1, 2) == "-d"){ // output folder
			if (ParamStr(i).Length() > 2) {
				outfolder = ParamStr(i).SubString(3, ParamStr(i).Length()-2);
			}
			else {
				i++;
				outfolder = ParamStr(i);
			}
		}

	// check for cookie
		else
		if (ParamStr(i).SubString(1, 2) == "-k"){ // cookie
			if (ParamStr(i).Length() > 2) {
				cookie = ParamStr(i).SubString(3, ParamStr(i).Length()-2);
			}
			else {
				i++;
				cookie = ParamStr(i);
			}
		}

	// check for referer
		else
		if (ParamStr(i).SubString(1, 2) == "-r"){ // referer
			if (ParamStr(i).Length() > 2) {
				referer = ParamStr(i).SubString(3, ParamStr(i).Length()-2);
			}
			else {
				i++;
				referer =ParamStr(i);
			}
		}

	// check for comment (FDM placeholder)
		else
		if (ParamStr(i).SubString(1, 2) == "-m"){ // comment
			if (ParamStr(i).Length() > 2) {
				comment = ParamStr(i).SubString(3, ParamStr(i).Length()-2);
			}
			else {
				i++;
				comment =ParamStr(i);
			}
		}

	// check for exec mode
		else
		if (app_status == APP_STATUS_SERVER && ParamStr(i).SubString(1, 2) == "-c"){ // client only, will spawn server
			shm->flag = SHM_FLAG_WAIT; // wait until flag change to ready
			app_status = APP_STATUS_CLIENT;
			AnsiString cmdline = AnsiString("\"") + ParamStr(0) + AnsiString("\" -s");
			unsigned int retval = WinExec(cmdline.c_str(), SW_SHOWNORMAL);

			if (retval == 0) {
				ShowMessage("out of memory");
			}
			if (retval == ERROR_BAD_FORMAT) {
				ShowMessage("bad format");
			}
			if (retval == ERROR_FILE_NOT_FOUND) {
				ShowMessage("file not found");
			}
			if (retval == ERROR_PATH_NOT_FOUND) {
				ShowMessage("path not found");
			}

			while(shm->flag != SHM_FLAG_READY) {
				Sleep(100);
				//TODO: make a way out of here
			}
		}
		else
		if (app_status == APP_STATUS_CLIENT && ParamStr(i).SubString(1, 2) == "-s"){ // will run as server
			runasserver = 1;
		}

	// get the url, no switch
		else { // URL
			url = ParamStr(i);
		}
	}
	//finished parsing command line parameters.


	if (url != "") {

		while(shm->flag != SHM_FLAG_READY) { // wait until server ready
			Sleep(100);
			//TODO: make a way out of here
		}
		shm->flag = SHM_FLAG_TAKEN;
		strncpy(shm->url, url.c_str(), URLSIZE);
		strncpy(shm->ref, referer.c_str(), URLSIZE);
		strncpy(shm->ofile, outfile.c_str(), URLSIZE);
		strncpy(shm->odir, outfolder.c_str(), URLSIZE);
		strncpy(shm->cookie, cookie.c_str(), COOKIESIZE);
		strncpy(shm->comment, comment.c_str(), COOKIESIZE);
		strncpy(shm->sug_filename, sug_filename.c_str(), COOKIESIZE);
		shm->flag = SHM_FLAG_DATAIN;

		if (app_status == APP_STATUS_CLIENT ) {
			exit(1);
		}
		else {
			curl_global_init(CURL_GLOBAL_ALL);
			fromcommandline = 1;
		}
	}
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
   //form1

   if (shm == NULL)
   {
		Memo1->Lines->Add("Could not map view of file");
		return;
   }

   Memo1->Lines->Add("SHM status: " + AnsiString(shm->flag));

   if (shmstatus == SHM_FLAG_FRESH) {
	shm->flag = shmstatus;
	Timer1->Enabled = true;

   }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
	if (ParamCount() > 1) {
		Application->Minimize();
	}

	if (runasserver) {
			shm->flag = SHM_FLAG_READY;
			app_status = APP_STATUS_SERVER;
//			Memo1->Lines->Add("Spawned by client");
//			Timer2->Enabled = true;
			Timer1->Enabled = true;
	}



	TIniFile *ini = new TIniFile(ChangeFileExt(Application->ExeName, ".ini"));
	edOutfile->Text = ini->ReadString("config", "lastsavefile", "");
	edOutFolder->Text = ini->ReadString("config", "lastfolder", "");
	edReferer->Text = ini->ReadString("config", "lastreferer", "");
	lastoutfolder = edOutFolder->Text;
	delete ini;

	msglist = new TStringList();
	ComboBox1->Items->LoadFromFile(ChangeFileExt(Application->ExeName, ".mru"));
	ComboBox1->Text = ComboBox1->Items->Strings[0];

   if (app_status == APP_STATUS_SERVER && shm->flag == SHM_FLAG_FRESH) {
	shm->flag = SHM_FLAG_READY; // ready to process
	Memo1->Lines->Add("shm flag: " + AnsiString(shm->flag));
   }



	//---------------------------------------------------------------------


//	if (referer != "") {
//		Memo1->Lines->Add("referer : " + referer);
//		edReferer->Text = referer;
//	}
	this->Caption = "BCBCurl server";
	curl = new TThreadCurl(true); //create suspend
}
//---------------------------------------------------------------------------
void TForm1::save_inifile()
{
	TIniFile *ini = new TIniFile(ChangeFileExt(Application->ExeName, ".ini"));
	ini->WriteString("config", "lastsavefile", edOutfile->Text);
	ini->WriteString("config", "lastfolder", edOutFolder->Text);
	ini->WriteString("config", "lastreferer", edReferer->Text);

	int found = -1;
	int combnum = ComboBox1->Items->Count;
	combnum > 100 ? combnum = 100 : 0;
	for(int i=0; i<combnum; i++) {
		if(ComboBox1->Items->Strings[i] == ComboBox1->Text) {
			found = i;
			break;
		}
	}
	if (found > -1) {
		AnsiString tmp = ComboBox1->Items->Strings[found];
		ComboBox1->Items->Strings[found] = ComboBox1->Items->Strings[0];
		ComboBox1->Items->Strings[0] = tmp;
	} else {
		for(int i=(combnum-1); i>0; i--) {
			ComboBox1->Items->Strings[i] = ComboBox1->Items->Strings[i-1];
		}
		ComboBox1->Items->Strings[0] = ComboBox1->Text;
	}
	ComboBox1->Items->SaveToFile(ChangeFileExt(Application->ExeName, ".mru"));
	ComboBox1->Items->LoadFromFile(ChangeFileExt(Application->ExeName, ".mru"));
	ComboBox1->Text = ComboBox1->Items->Strings[0];

	delete ini;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	save_inifile();
	while(download_que->Count) {
		TShm *tmp = (TShm*) download_que->Items[0];
		download_que->Delete(0);
		delete tmp;
	}
	delete download_que;
	if (curl) {
		curl->do_run = 0;
	}
	Sleep(150); //threadcurl use 100ms sleep

	if (app_status == APP_STATUS_CLIENT ) {
	}
	else {
		curl_global_cleanup();
	}

}


//---------------------------------------------------------------------------


int dlstep = -1;

TThreadCurl *curl;
FILE *outfile;
size_t wsize;
extern int exitcode;
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	process_que();
	while(msglist->Count) {
		Memo1->Lines->Add(msglist->Strings[0]);
		msglist->Delete(0);
		Application->ProcessMessages();
	}
	switch(dlstep) {
		case 0:
			btDownload->Enabled = false;
			Memo1->Lines->Add("download step 1");
			curl->prepare_memorystruct(ComboBox1->Text, edReferer->Text, edCookie->Text);
			dlstep = 1;
			break;

		case 1:
			dlstep = 5;
			Memo1->Lines->Add("download step 2");
			Memo1->Lines->Add("STEP_DOWNLOAD_HEADER");
			curl->download_step = STEP_DOWNLOAD_HEADER;
			curl->Resume();
			break;

		case 2:
			while(msglist->Count) {
				Memo1->Lines->Add(msglist->Strings[0]);
				msglist->Delete(0);
			}
			if (msglist->Count < 1 && curl->last_byte == curl->content_length) {
				dlstep = 3; // download finished
			}
			break;

		case 3: // download finished
			dlstep = -1; // do nothing
			Memo1->Lines->Add("download step 3");
			if (curl->invalid) {
				Memo1->Lines->Add("Download terminated");
			}
			else {
				AnsiString stroutfile = "";
				//case 1: odir non empty, use odir, extract filename only form ofile
				if (setoutdir || ExtractFileDrive(edOutfile->Text) == "") { //  outdir set from command line OR outfile doesnt contains drive letter
					lastoutfolder = edOutFolder->Text;
					int retval = ForceDirectories(lastoutfolder);
					if (!retval) {
						Memo1->Lines->Add("ERROR: Create directory failed!");
						Memo1->Lines->Add(edOutFolder->Text);
						break;
					}
					stroutfile = edOutFolder->Text + "\\" + ExtractFileName(edOutfile->Text);
				}
//				//case : odir empty, ofile contains filename only
//				else
//				if (ExtractFileDrive(edOutfile->Text) == "") { // outfile doesnt contains drive letter
//					stroutfile = lastoutfolder + "\\" + ExtractFileName(edOutfile->Text);
//				}
				else { // outfile contains drive letter (full path assumed)
					stroutfile = edOutfile->Text;
				}

				//case : odir empty, ofile contains fullpath

				Memo1->Lines->Add("FINISHED, writing file: " + stroutfile);

				outfile = fopen(stroutfile.c_str(), "wb");
				wsize = fwrite(curl->memory, curl->content_length, 1, outfile);
				fclose(outfile);
				save_inifile();
			}
			if (curl->memory) {
				free(curl->memory);
			}
//			Memo1->Lines->Add("[case 3] chunk status: " + AnsiString(curl->status) + " " + AnsiString(str_status[curl->status]));
			download_finished = 1;
			btDownload->Enabled = true;
			break;

		case 4: // this step will be called every 2 seconds while downloading
//			Memo1->Lines->Add("[case 4] chunk status: " + AnsiString(curl->status) + " " + AnsiString(str_status[curl->status]));

			if (edOutfile->Text == "") {
				AnsiString stroutfile = "";
				if (curl->header_filename != "") { // use filename from Content-Disposition
					stroutfile = curl->header_filename;
				} else { // extract filename from url
					TPerlRegEx *pcre = new TPerlRegEx();
					pcre->RegEx = "/([^\\/]+)$"; // get anything after '/'
					pcre->Subject = curl->url;
					if(pcre->Match()) {
						stroutfile = pcre->Groups[1];
					}
					pcre->RegEx = "^([^\\?]+)\\?"; // get anything before '?'
					pcre->Subject = stroutfile;
					if(pcre->Match()) {
						stroutfile = pcre->Groups[1];
						Memo1->Lines->Add("====================================" + pcre->Groups[1]);
					}
					stroutfile = uri_decode(stroutfile);
				}
				if (stroutfile.Length() > 64 && edComment->Text != "" && edComment->Text.Length() < 128) {
					stroutfile = edComment->Text;
				}

				if (edComment->Text != "" && CheckBox1->Checked) {
					stroutfile = uri_decode(edComment->Text);
				}

				Memo1->Lines->Add("UNESCAPE: " + uri_decode(curl->url));
//					ShowMessage(outfile);
//				TPerlRegEx *pcre = new TPerlRegEx();
//				pcre->RegEx = "[^a-zA-Z0-9\\.]"; // replace anything else
//				pcre->Replacement = "_";
//				pcre->Subject = stroutfile;
//				pcre->ReplaceAll();
				edOutfile->Text = sanitize(stroutfile);
//					edOutfile->Text = stroutfile;
				stroutfile = "";

				if (edOutfile->Text == "") // still empty for unknown reason
				{
					edOutfile->Text = "outfile";
				}
}
			if (curl->last_byte > curl->content_length) {
				dlstep = 3; // stop download
				exitcode = -1;
				return;
			}
			if (curl->status == CURL_TERMINATED) {
				if (curl->invalid || curl->content_length == curl->last_byte) { // finished
					dlstep = 3;
				} else { // restart download
					Memo1->Lines->Add("--- unfinished download, restart curl ---");
					Memo1->Lines->Add("STEP_DOWNLOAD_DATA");
					curl->download_step = STEP_DOWNLOAD_DATA;
				}
			}
			break;
		case 5: // finished download header, advance to next step
//			Memo1->Lines->Add("download step 5");
			if (curl->download_prev_step == STEP_DOWNLOAD_HEADER && curl->download_step == STEP_DOWNLOAD_NOTHING) {
				Memo1->Lines->Add("HTTP code: " + AnsiString(curl->http_code));
				if (curl->invalid) {
					dlstep = 3; // terminate
				}
				else {
					Memo1->Lines->Add("STEP_DOWNLOAD_DATA_FIRST");
					curl->download_step = STEP_DOWNLOAD_DATA_FIRST;
					dlstep = 6;
//					dlstep = 4; // download content
				}
			}
		case 6:
			if (curl->status == CURL_RECEIVING || curl->status == CURL_TERMINATED
			) {
				// wait until curl gets header
					dlstep = 4;
			}
			break;
	}
	Label1->Caption = "Content-Length : " + AnsiString(curl->content_length) + " , que: " + AnsiString(download_que->Count) +
	", last byte: " + AnsiString(curl->last_byte) + ", progress: " + AnsiString(100 * curl->last_byte / (curl->content_length > 0 ? curl->content_length : 1000)) + "%";

}
//---------------------------------------------------------------------------

void __fastcall TForm1::btDownloadClick(TObject *Sender)
{
	download_finished = 0;
	dlstep = 0;
}
//---------------------------------------------------------------------------


int inactive_timer = 0;
void TForm1::process_que()
{
	inactive_timer++;
	if (download_que->Count) {
		shm->que = download_que->Count;
//		Memo1->Lines->Add("Timer2, shm flag: " + AnsiString(shm->flag) + ", Queue: " + AnsiString(download_que->Count));
	}
	if (shm->flag == SHM_FLAG_DATAIN) {
		Memo1->Lines->Add("Data in to que:");
		Memo1->Lines->Add("url: " + AnsiString(shm->url));
		Memo1->Lines->Add("referer: " + AnsiString(shm->ref));
		Memo1->Lines->Add("out file: " + AnsiString(shm->ofile));
		TShm *listitem = new TShm;
		memcpy(listitem, shm, sizeof(TShm));
		shm->flag = SHM_FLAG_READY;
		download_que->Add(listitem);
		inactive_timer = 0;
	}

	if (download_que->Count > 0) {
		if (download_finished && !cbPause->Checked) {
			TShm *listitem = (TShm*) download_que->Items[0];
			download_que->Delete(0);
			ComboBox1->Text = listitem->url;
			edReferer->Text = listitem->ref;
			edOutfile->Text = listitem->ofile;
			edCookie->Text = listitem->cookie;
			edComment->Text = listitem->comment;
			if (AnsiString(listitem->sug_filename) != "" && edOutfile->Text == "") {
				edOutfile->Text = sanitize(listitem->sug_filename);
			}
//			Memo1->Lines->Add("suggested filename " + AnsiString(listitem->sug_filename));
			if (strlen(listitem->odir) > 0) {
				edOutFolder->Text = listitem->odir;
				setoutdir = 1; // output folder set from command line
			} else {
            	setoutdir = 0;
			}
			Label6->Caption = "Last folder: " + lastoutfolder;

			Memo1->Lines->Add("Downloading:");
			Memo1->Lines->Add("url: " + AnsiString(listitem->url));
			Memo1->Lines->Add("referer: " + AnsiString(listitem->ref));
			Memo1->Lines->Add("out file: " + AnsiString(listitem->ofile));
			btDownload->Click();
			delete listitem;
		}
		AnsiString text = "";
		for(int i=0; i<download_que->Count; i++) {
			TShm *listitem = (TShm*) download_que->Items[i];
			text = text + listitem->url;
			text = text + "\r\n";
		}
		Memo2->Text = text;
		inactive_timer = 0;
	}
	if (inactive_timer > 5) {
//		Close(); // ERROR! close prematurely while processing last download
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::btBrowseFolderClick(TObject *Sender)
{
	if (FileOpenDialog1->Execute() == IDOK) {
		edOutFolder->Text = FileOpenDialog1->FileName;
	}
}
//---------------------------------------------------------------------------

// HTMLDecode
void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
	if (CheckBox1->Checked) {
		edOutfile->Text = sanitize(uri_decode(edComment->Text));
	}
}
//---------------------------------------------------------------------------

