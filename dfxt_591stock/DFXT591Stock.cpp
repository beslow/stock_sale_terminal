//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------
USEFORM("MSaleLossOrder.cpp", SaleLossOrder);
USEFORM("MPurchaseOrder.cpp", PurchaseOrder);
USEFORM("MStorageLossOrder.cpp", StorageLossOrder);
USEFORM("MDatabaseInfo.cpp", DatabaseInfo);
USEFORM("MAIN.CPP", MainForm);
USEFORM("MPrintOrder.cpp", PrintOrder);
USEFORM("MLogin.cpp", Login);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	Application->Initialize();
	Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->Run();
	return 0;
}
//---------------------------------------------------------------------
