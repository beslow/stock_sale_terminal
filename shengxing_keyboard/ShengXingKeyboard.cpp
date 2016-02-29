//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("main.cpp", Form2);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		SetWindowLong(Application->Handle, GWL_EXSTYLE,
		WS_EX_TOPMOST|WS_EX_WINDOWEDGE|WS_EX_NOACTIVATE|WS_EX_TOOLWINDOW);
		Application->CreateForm(__classid(TForm2), &Form2);
//		Application->ShowMainForm   =   false;             //增加这一行和下面一行
//		ShowWindow(Application->Handle, SW_HIDE);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
