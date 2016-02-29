//---------------------------------------------------------------------------

#ifndef MLoginH
#define MLoginH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include "DBAccess.hpp"
#include "MemDS.hpp"
#include "MyAccess.hpp"
#include <Data.DB.hpp>
//---------------------------------------------------------------------------
class TLogin : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *user_name_or_email;
	TLabel *Label2;
	TEdit *terminal_password;
	TBitBtn *BitBtn1;
	TLabel *message;
	TMyConnection *my_con;
	TMyQuery *my_qry;
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall terminal_passwordKeyPress(TObject *Sender, System::WideChar &Key);

private:	// User declarations
public:		// User declarations
	__fastcall TLogin(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLogin *Login;
//---------------------------------------------------------------------------
#endif
