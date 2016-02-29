//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MSaleLossOrder.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "MemDS"
#pragma link "MyAccess"
#pragma resource "*.dfm"
TSaleLossOrder *SaleLossOrder;
//---------------------------------------------------------------------------
__fastcall TSaleLossOrder::TSaleLossOrder(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSaleLossOrder::FormCreate(TObject *Sender)
{
	TypeDetailPurchase = 4;

	//查询数据库，获取仓库ID：storage_id
	AnsiString user_id = MainForm->OperatorId;
	AnsiString sql = "";
	sql = "select store_id from users where id = " + user_id;
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	int store_id = Qry->FieldByName("store_id")->AsInteger;
	if(store_id == 0){
		ShowMessage("当前登录用户没有权限管理任何一个仓库，请联系管理员！");

	} else {
		sql = "select id from storages where store_id = " + AnsiString(store_id);
		Qry->Close();
		Qry->SQL->Clear();
		Qry->SQL->Add(sql);
		Qry->Open();
		if (Qry->RecordCount == 0) {
			ShowMessage("当前登录用户可以管理的仓库不存在，请联系管理员！");

		} else {
			Qry->First();
			StorageId = Qry->FieldByName("id")->AsInteger;
        }
	}
}
//---------------------------------------------------------------------------
void __fastcall TSaleLossOrder::FormClose(TObject *Sender, TCloseAction &Action)
{
	HWND hwnd=FindWindowA(NULL,MainForm->select_panel_name);
	AnsiString str="close^";
	COPYDATASTRUCT myCopyDATA;
	myCopyDATA.cbData=str.Length();
	myCopyDATA.lpData=str.c_str();
	SendMessageA(hwnd,WM_COPYDATA,NULL,(LPARAM)&myCopyDATA);
	Action=caFree;
}
//---------------------------------------------------------------------------
void __fastcall TSaleLossOrder::Timer1Timer(TObject *Sender)
{
	HWND hwnd=FindWindowA(NULL,MainForm->select_panel_name);
	AnsiString str="pos^"+AnsiString(Left-300)+"^^"+AnsiString(Top+40);
	COPYDATASTRUCT myCopyDATA;
	myCopyDATA.cbData = str.Length();
	myCopyDATA.lpData = str.c_str();
	SendMessageA(hwnd,WM_COPYDATA,NULL,(LPARAM)&myCopyDATA);
}
//---------------------------------------------------------------------------
