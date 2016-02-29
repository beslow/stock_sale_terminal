//---------------------------------------------------------------------------

#ifndef MStorageLossOrderH
#define MStorageLossOrderH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "DBAccess.hpp"
#include "MemDS.hpp"
#include "MyAccess.hpp"
#include <Data.DB.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TStorageLossOrder : public TForm
{
__published:	// IDE-managed Components
	TMyQuery *Qry;
	TMyCommand *Cmd;
	TTimer *Timer1;
	TStringGrid *StorageLossStringGrid;
	TDateTimePicker *DateTimePicker1;
	TLabel *Label1;
	TBitBtn *BitBtn1;
	TLabel *Label2;
	TEdit *SLSellerName;
	TCheckBox *auto_next;
	TComboBox *LossType;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall SLSellerNameChange(TObject *Sender);
	void __fastcall SLSellerNameClick(TObject *Sender);
	void __fastcall StorageLossStringGridSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
	void __fastcall LossTypeChange(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
	int TypeDetail;
	int StorageId;
public:		// User declarations
	int SellerId;
	__fastcall TStorageLossOrder(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TStorageLossOrder *StorageLossOrder;
//---------------------------------------------------------------------------
#endif
