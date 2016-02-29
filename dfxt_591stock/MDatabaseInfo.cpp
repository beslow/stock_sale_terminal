//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <inifiles.hpp>
#include "MDatabaseInfo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDatabaseInfo *DatabaseInfo;
//---------------------------------------------------------------------------
__fastcall TDatabaseInfo::TDatabaseInfo(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDatabaseInfo::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action=caFree;
}
//---------------------------------------------------------------------------

void __fastcall TDatabaseInfo::FormShow(TObject *Sender)
{
	TIniFile* regKey;
    AnsiString ExePath=ExtractFilePath(ParamStr(0));
    regKey=new TIniFile(ExePath+"database.ini");
    Host->Text = regKey->ReadString("databaseinfo","server",ExePath);
    DatabaseName->Text = regKey->ReadString("databaseinfo","databasename",ExePath);
	UserName->Text = regKey->ReadString("databaseinfo","user",ExePath);
	Password->Text = regKey->ReadString("databaseinfo","password",ExePath);
	Port->Text = regKey->ReadString("databaseinfo","port",ExePath);
    delete regKey;
}
//---------------------------------------------------------------------------
