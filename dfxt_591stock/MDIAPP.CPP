//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------
USEFORM("Main.cpp", MainForm);
USEFORM("ChildWin.cpp", MDIChild);
USERES("mdiapp.res");
USEFORM("about.cpp", AboutBox);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	Application->Initialize();
	Application->CreateForm(__classid(TMainForm), &MainForm);
	Application->CreateForm(__classid(TAboutBox), &AboutBox);
	Application->Run();
	return 0;
}
//---------------------------------------------------------------------
