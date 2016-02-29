//---------------------------------------------------------------------------

#ifndef MDatabaseInfoH
#define MDatabaseInfoH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TDatabaseInfo : public TForm
{
__published:	// IDE-managed Components
	TEdit *Host;
	TEdit *UserName;
	TEdit *Password;
	TEdit *DatabaseName;
	TEdit *Port;
	TLabel *服务器名称;
	TLabel *用户名;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TDatabaseInfo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDatabaseInfo *DatabaseInfo;
//---------------------------------------------------------------------------
#endif
