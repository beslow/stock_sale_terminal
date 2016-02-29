//----------------------------------------------------------------------------
#ifndef MainH
#define MainH
//----------------------------------------------------------------------------
#include "ChildWin.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Messages.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <StdCtrls.hpp>
#include <Menus.hpp>
#include <Controls.hpp>
#include <Forms.hpp>
#include <Graphics.hpp>
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Windows.hpp>
#include <System.hpp>
#include <ActnList.hpp>
#include <ImgList.hpp>
#include <StdActns.hpp>
#include <ToolWin.hpp>
#include <System.Actions.hpp>
#include "DBAccess.hpp"
#include "MyAccess.hpp"
#include <Data.DB.hpp>
#include "MPrintOrder.h"
#include "MPurchaseOrder.h"
#include "MSaleLossOrder.h"
#include "MStorageLossOrder.h"
//----------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:
	TMainMenu *MainMenu1;
	TOpenDialog *OpenDialog;
	TStatusBar *StatusBar;
	TActionList *ActionList1;
	TImageList *ImageList1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMyConnection *Connection;
	TMenuItem *N3;
	TAction *Action1;
	TMenuItem *N4;
	TMenuItem *N5;
	void __fastcall N2Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
public:
	void __fastcall GetData(TWMCopyData &Msg);
//public:
	int ParentId;
	AnsiString OperatorId;
	AnsiString OperatorName;
	AnsiString OperatorCompanyName;
	char *select_panel_name;
	bool login_success;
	bool __fastcall ExistForm(AnsiString formClassType);
	virtual __fastcall TMainForm(TComponent *Owner);
	BEGIN_MESSAGE_MAP
	MESSAGE_HANDLER(WM_COPYDATA, TWMCopyData, GetData)
	END_MESSAGE_MAP(TForm)
};
//----------------------------------------------------------------------------
extern TMainForm *MainForm;
extern TMDIChild *__fastcall MDIChildCreate(void);
//----------------------------------------------------------------------------
#endif    
