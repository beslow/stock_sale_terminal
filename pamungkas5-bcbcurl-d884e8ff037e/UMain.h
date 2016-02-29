//---------------------------------------------------------------------------

#ifndef UMainH
#define UMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo1;
	TCheckBox *cbHeader;
	TComboBox *ComboBox1;
	TButton *btDownload;
	TTimer *Timer1;
	TEdit *edOutfile;
	TLabel *Label1;
	TEdit *edReferer;
	TMemo *Memo2;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TCheckBox *cbPause;
	TEdit *edOutFolder;
	TLabel *Label5;
	TButton *btBrowseFolder;
	TFileOpenDialog *FileOpenDialog1;
	TLabel *Label6;
	TEdit *edCookie;
	TLabel *Label7;
	TSplitter *Splitter1;
	TLabel *Label8;
	TEdit *edComment;
	TCheckBox *CheckBox1;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall btDownloadClick(TObject *Sender);
	void __fastcall btBrowseFolderClick(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	void process_que();
	void save_inifile();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
