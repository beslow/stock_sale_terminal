//---------------------------------------------------------------------------

#ifndef MSaleLossOrderH
#define MSaleLossOrderH
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
//---------------------------------------------------------------------------
class TSaleLossOrder : public TForm
{
__published:	// IDE-managed Components
	TMyQuery *Qry;
	TMyCommand *Cmd;
	TTimer *Timer1;
	TStringGrid *SaleLossStringGrid;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
	int TypeDetailPurchase;
	int StorageId;
public:		// User declarations
	__fastcall TSaleLossOrder(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TSaleLossOrder *SaleLossOrder;
//---------------------------------------------------------------------------
#endif
