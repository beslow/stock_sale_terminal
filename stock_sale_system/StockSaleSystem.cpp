//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------
USEFORM("MPurchaseOrder.cpp", PurchaseOrder);
USEFORM("MPrintOrder.cpp", PrintOrder);
USEFORM("MDatabaseInfo.cpp", DatabaseInfo);
USEFORM("MAIN.CPP", MainForm);
USEFORM("MLogin.cpp", Login);
USEFORM("MStorageLossOrder.cpp", StorageLossOrder);
USEFORM("MSaleLossOrder.cpp", SaleLossOrder);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	Application->Initialize();
	Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->Run();
	return 0;
}
//---------------------------------------------------------------------
