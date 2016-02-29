//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
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
#include <Vcl.Buttons.hpp>
#include <map>
#include <string>
#include <vector>
using namespace std;
struct SqlBtn
{
        AnsiString sql;
        vector<TButton*>btn;
};
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TPanel *pnlcontent;
	TMyConnection *con1;
	TMyQuery *qry1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormDblClick(TObject *Sender);
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
private:	// User declarations
	bool sql_exist;
	//vector<vector<AnsiString> >vecbtn;
	vector<AnsiString> tempvec;
	vector<SqlBtn*>vecbtn;
	AnsiString tempstr;
	TButton *Bn[1000];
	TBitBtn *Bitn[50];
	TButton *movebtn;
	BOOL move_flag;
	bool createbymemory;
	TPoint begin_point;
	int count;
	int index;
	int oldindex;
	AnsiString type_keyboard;
	bool newbutton_exist;
	bool memorybutton_exist;
	bool numbutton_exist;
	bool standard_exist;
	int m_width;
	int m_height;

	int index_srf;
	int count_srf;
	HKL hkl[30];
	//vector<vector> vecbtn;
	void __fastcall deleteall();
	void __fastcall createbtn();
	void __fastcall increatebtn();
	void __fastcall createstandardkeyboard();
	void __fastcall createnumkeyboard();
	void __fastcall BnClick(TObject *Sender);

	void __fastcall fun_copydata(TWMCopyData &Msg);
	void __fastcall copybutton(TButton* src,TButton* &tar);
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
	BEGIN_MESSAGE_MAP
	MESSAGE_HANDLER(WM_COPYDATA, TWMCopyData, fun_copydata)
	END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
