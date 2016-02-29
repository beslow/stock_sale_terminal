//---------------------------------------------------------------------------

#ifndef UThreadCurlH
#define UThreadCurlH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class TThreadCurl : public TThread
{
public:
	int do_run;

  char *memory;
  size_t size_downloaded;
  size_t size_memory;
  unsigned long content_length;
  unsigned long start_byte;
  unsigned long stop_byte;
  unsigned long last_byte;
  int can_resume;
  int invalid;
  AnsiString url;
  AnsiString unescaped;
  AnsiString referer;
  AnsiString cookie;
  int header;
  int status;
  int http_code;
  int download_step;
  int download_prev_step;
	AnsiString header_filename;
	void prepare_memorystruct(AnsiString url, AnsiString referer, AnsiString icookie);


private:
protected:
	void __fastcall Execute();
public:
	__fastcall TThreadCurl(bool CreateSuspended);
};
extern TThreadCurl *curl;

enum {CURL_STARTED = 1, CURL_RECEIVING = 2, CURL_TERMINATED = 3};
enum {STEP_DOWNLOAD_NOTHING = 0, STEP_DOWNLOAD_HEADER = 1, STEP_DOWNLOAD_DATA_FIRST = 2, STEP_DOWNLOAD_DATA = 3};

char *str_status[] = {"[UNKNOWN 0]", "[CURL STARTED]", "[CURL RECEIVING]", "[CURL TERMINATED]", "[UNKNOWN 5]"};

size_t header_callback(char *buffer,   size_t size,   size_t nmemb,   void *userdata);
size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
int do_curl(TThreadCurl *chunk, unsigned long range_from, unsigned long range_to, int headeronly);
AnsiString uri_decode(AnsiString inuri);

//---------------------------------------------------------------------------
#endif
