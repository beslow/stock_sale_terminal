//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "math.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "MemDS"
#pragma link "MyAccess"
#pragma resource "*.dfm"
TForm2 *Form2;
vector<AnsiString> temp_vecstr;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
	FormStyle = fsStayOnTop;
	SetWindowLong(Handle, GWL_EXSTYLE,
  		WS_EX_TOPMOST|WS_EX_WINDOWEDGE|WS_EX_NOACTIVATE|WS_EX_TOOLWINDOW);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
	Form2->Left=50;Form2->Top=50;
	//从database.ini配置文件读取连接信息
	TIniFile* regKey;
    AnsiString ExePath=ExtractFilePath(ParamStr(0));
    regKey=new TIniFile(ExePath+"database.ini");
    AnsiString server=regKey->ReadString("databaseinfo","server",ExePath);
    AnsiString databasename=regKey->ReadString("databaseinfo","databasename",ExePath);
    AnsiString user=regKey->ReadString("databaseinfo","user",ExePath);
	AnsiString password=regKey->ReadString("databaseinfo","password",ExePath);
	AnsiString port=regKey->ReadString("databaseinfo","port",ExePath);
	delete regKey;

	//设置连接信息
	con1->Server = server;
	con1->Username = user;
	con1->Password = password;
	con1->Database = databasename;
	con1->Port = port.ToInt();
	con1->Options->Charset ="gbk";
	con1->Connect();
	//("set NAMES'gbk';",NULL,0);
	index=0;
	move_flag=False;
	sql_exist=False;
	createbymemory=false;
	count_srf=0;
	index_srf=0;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
	deleteall();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormDblClick(TObject *Sender)
{
	createbtn();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::BnClick(TObject *Sender)//动态创建的按钮的单击事件响应
{
	HWND wnd=GetForegroundWindow();
	//HWND wnd=FindWindowA(NULL,"ShengXingSystem");
	movebtn=(TButton*)Sender;
	AnsiString str=movebtn->Caption;
	movebtn=NULL;
	COPYDATASTRUCT myCopyDATA;
	myCopyDATA.cbData=str.Length();
	myCopyDATA.lpData=str.c_str();
	SendMessageA(wnd,WM_COPYDATA,NULL,(LPARAM)&myCopyDATA);
}
// ---------------------------------------------------------------------------
void __fastcall TForm2::createbtn()               //根据消息"sql"动态创建按钮
{
    deleteall();
    SqlBtn* temp_sqlbtn;
    temp_sqlbtn=new SqlBtn();
    temp_sqlbtn->sql=tempstr;
    int ii,yy,ww;
    ww=0;yy=0;
    count=qry1->RecordCount;
    int bn_w=floor((pnlcontent->Width-3*5)/4) ;
    int bn_h=60;
    for(ii=0;ii<count;ii++)
    {
      Bn[ii]=new TButton(this);
      Bn[ii]->Parent=pnlcontent;
      ////置响应函数
      Bn[ii]->OnClick=BnClick;
      Bn[ii]->Caption="("+IntToStr(ii+1)+")"+qry1->FieldByName("FName")->AsString.TrimRight();
      Bn[ii]->ShowHint=True;
      Bn[ii]->Hint=Bn[ii]->Caption;
      Bn[ii]->Height=bn_h;Bn[ii]->Width=bn_w;
      Bn[ii]->Font->Size=12;
      Bn[ii]->Font->Name="黑体";
      if(Bn[ii]->Parent!=NULL)
      SetWindowLong(Bn[ii]->Handle, GWL_STYLE,GetWindowLong(Bn[ii]->Handle, GWL_STYLE)|BS_MULTILINE);
      //SetWindowLong(Bn[ii]->Handle, GWL_STYLE,GetWindowLong(this, GWL_STYLE|BS_MULTILINE)); //
      Bn[ii]->Enabled=true;
      ////根据窗口的宽度布置按钮的位置
      if(ww+Bn[ii]->Width+10>Width)
      {
        yy=yy+Bn[ii]->Height+5;
        ww=0;
      }
      Bn[ii]->Left=ww;
      Bn[ii]->Top=yy;
      ww=ww+Bn[ii]->Width+5;
      TButton* tbn;
      tbn=new TButton(this);
	  copybutton(Bn[ii],tbn);
	  temp_sqlbtn->btn.push_back(tbn);
      qry1->Next();
    }
    newbutton_exist=True;
    type_keyboard="newbtn";
    vecbtn.push_back(temp_sqlbtn);
    qry1->First();
}
void __fastcall TForm2::copybutton(TButton* src,TButton* &tar)
{
        tar->Parent=NULL;
        tar->OnClick=src->OnClick;
        tar->Caption=src->Caption;
        tar->Height=src->Height;
        tar->Width=src->Width;
        tar->Left=src->Left;
        tar->Top=src->Top;
}
void __fastcall TForm2::increatebtn() //当sql语句已在缓存中则执行此方法
{
    deleteall();
    count=vecbtn[index]->btn.size();
    vector<TButton*>::iterator it;
    for (it=vecbtn[index]->btn.begin();it!=vecbtn[index]->btn.end();++it)
    {
         (*it)->Parent=pnlcontent;
         (*it)->Font->Size=12;
         (*it)->Font->Name="黑体";
    }
    memorybutton_exist=True;
    type_keyboard="memorybtn";
    oldindex=index;
}
void __fastcall TForm2::createstandardkeyboard()//当接受到消息“standard”时执行此方法
{
    deleteall();
    MoveWindow(Handle,Left,Top,755,215,True);
    type_keyboard="standard";
//    changesize(m_width,m_height);
}
void __fastcall TForm2::createnumkeyboard() //当接收到消息“num”时执行此方法
{
    deleteall();
    MoveWindow(Handle,Left,Top,755,215,True);
    numbutton_exist=True;
    type_keyboard="num";
//    changesize(m_width,m_height);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::deleteall()               //删除动态创建的按钮
{
  if(newbutton_exist)
  {
	int ii;
	for(ii=0;ii<count;ii++)
	{
	   delete Bn[ii];
	}
	newbutton_exist=False;
  }
  if(memorybutton_exist)
  {
	vector<TButton*>::iterator it;
	for (it=vecbtn[oldindex]->btn.begin();it!=vecbtn[oldindex]->btn.end();++it)
	{
	 (*it)->Parent=NULL;
	}
	memorybutton_exist=False;
  }
  if(numbutton_exist)
  {
     numbutton_exist=False;
  }
  if(standard_exist)
  {
    standard_exist=False;
  }
}
// ---------------------------------------------------------------------------
void __fastcall TForm2::fun_copydata(TWMCopyData &Msg)//响应其他应用程序发来的WM_COPYDATA讯息
{
	//解析消息字符串

    int p,q;
    UnicodeString parameter1,parameter2;
    COPYDATASTRUCT *cds;
    char* DataBuf;
    cds=(COPYDATASTRUCT*)Msg.CopyDataStruct;
    DataBuf=new char[2000];
    memset(DataBuf,0,2000);
    CopyMemory(DataBuf,cds->lpData,cds->cbData);
    UnicodeString Str=UnicodeString(DataBuf);
    delete[] DataBuf;
    p=Str.Pos("^");
    q=Str.Pos("^^");
    UnicodeString eventstr;
    eventstr=Str.SubString(1,p-1);
    parameter1=Str.SubString(p+1,q-p-1);
    parameter2=Str.SubString(q+2,Str.Length()-q);

    //处理
    if(eventstr=="choose")
    {
        if(newbutton_exist)
            Bn[parameter1.ToInt()-1]->Click();
        else if(memorybutton_exist)
            vecbtn[oldindex]->btn.at(parameter1.ToInt()-1)->Click();
    }
    else if(eventstr=="close")       //关闭
    {
      SendMessageA(Handle,WM_CLOSE,0,0);
    }else if(eventstr=="delete")
    {
      deleteall();
    }
    else if(eventstr=="hide")  //隐藏
    {
      this->Hide();
    }else if(eventstr=="show")    //显示
    {
        this->Show();
    }else if(eventstr=="pos")      //设置位置 坐标(parameter1,parameter2)
    {
      int x=parameter1.ToInt();int y=parameter2.ToInt();
//      if(x<0)x=0;if(y<0)y=0;
      MoveWindow(Handle,x,y,Width,Height,True);
    }else if(eventstr=="standard") //标准键盘
    {
      if(type_keyboard!="standard")
      createstandardkeyboard();
    }else if(eventstr=="num")     //数字键盘
    {
      if(type_keyboard!="num")
      createnumkeyboard();
    }
    else if(eventstr=="size")     //改变尺寸，宽:parameter1，  高:parameter2
    {
//      changesize(parameter1.ToInt(),parameter2.ToInt());
    }else if(eventstr==UnicodeString("sql"))
	{
		int i=0;
        vector<SqlBtn*>::iterator it;
        for(it=vecbtn.begin();it!=vecbtn.end();++it)
        {
          i++;
          if((*it)->sql==parameter1)
          {
            sql_exist=false;
            break;
          }
        }
      if(i>0)
	  index=i-1;

      if(!sql_exist)
	  {
          tempstr=parameter1;
		  qry1->Close();
          qry1->SQL->Clear();
		  qry1->SQL->Add(parameter1);   //加入SQL程序码
		  qry1->Open();              //执行SQL程序码
	  //qry1->ExecSQL();
          if(qry1->RecordCount>0)
          {
            createbtn();
          }
      }
      else
      {
        sql_exist=False;
        increatebtn();
      }
    }
    TForm::Dispatch(&Msg);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
        move_flag=True;
        begin_point.x=X;
        begin_point.y=Y;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
        move_flag=False;
}
void __fastcall TForm2::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
        if(move_flag)
         MoveWindow(Handle,Left+X-begin_point.x,Top+Y-begin_point.y,Width,Height,True);
}
//---------------------------------------------------------------------------
