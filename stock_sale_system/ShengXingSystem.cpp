//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------
USEFORM("MPrintOrder.cpp", PrintOrder);
USEFORM("MAIN.CPP", MainForm);
USEFORM("MDatabaseInfo.cpp", DatabaseInfo);
USEFORM("MLogin.cpp", Login);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	Application->Initialize();
	Application->CreateForm(__classid(TMainForm), &MainForm);
//	Application->CreateForm(__classid(TLogin), &Login);
	Application->Run();
	return 0;
}
//---------------------------------------------------------------------
