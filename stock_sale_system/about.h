//----------------------------------------------------------------------------
#ifndef AboutH
#define AboutH
//----------------------------------------------------------------------------
#include <Windows.hpp>
#include <System.hpp>
#include <Classes.hpp>
#include <Graphics.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Buttons.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//----------------------------------------------------------------------------
class TAboutBox : public TForm
{
__published:
	TPanel *Panel1;
	TButton *OKButton;
	TImage *ProgramIcon;
	TLabel *ProductName;
	TLabel *Version;
	TLabel *Copyright;
	TLabel *Comments;
private:
public:
	virtual __fastcall TAboutBox(TComponent *Owner);
};
//----------------------------------------------------------------------------
extern TAboutBox *AboutBox;
//----------------------------------------------------------------------------
#endif	
