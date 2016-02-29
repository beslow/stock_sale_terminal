//---------------------------------------------------------------------------

#ifndef MPurchaseOrderH
#define MPurchaseOrderH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "DBAccess.hpp"
#include "MemDS.hpp"
#include "MyAccess.hpp"
#include <Data.DB.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TPurchaseOrder : public TForm
{
__published:	// IDE-managed Components
	TMyQuery *Qry;
	TMyCommand *Cmd;
	TDateTimePicker *DateTimePicker1;
	TLabel *½ø²ÖÈÕÆÚ;
	TEdit *FromName;
	TLabel *Label1;
	TStringGrid *StringGrid1;
	TBitBtn *BitBtn1;
	TTimer *Timer1;
	TCheckBox *auto_next;
	TButton *Button1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *Edit1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FromNameClick(TObject *Sender);
	void __fastcall StringGrid1SelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall FromNameChange(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);

private:	// User declarations
	Boolean CanGo;
	int StorageId;

	int SupplierId;
    int TypeDetailPurchase;
public:		// User declarations
	int SellerId;
	__fastcall TPurchaseOrder(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPurchaseOrder *PurchaseOrder;
//---------------------------------------------------------------------------
#endif
