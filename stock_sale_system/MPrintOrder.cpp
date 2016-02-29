//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include<string>
#include<iostream>
using namespace std;
#include "MPrintOrder.h"
#include "Main.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "MyAccess"
#pragma link "MemDS"
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma resource "*.dfm"
TPrintOrder *PrintOrder;
boolean shifang = false;
//---------------------------------------------------------------------------
__fastcall TPrintOrder::TPrintOrder(TComponent* Owner)
	: TForm(Owner)
{   //设置临时记录数量值为1
	TempNumberOrderType = 1;
	TempNumberStore = 1;
	//设置订单日期、送货日期
	TDateTime ttime = Time();
	unsigned short h,mi,s,ss;
	unsigned short y,m,d;
	ttime.DecodeTime(&h,&mi,&s,&ss);
	if(h>=0 && h<=12) {
		SendOrderTime->Date = Now() - 1;
		ReachOrderTime->Date = Now();
		ReachOrderTime->Date.DecodeDate(&y,&m,&d);
		AnsiString str_month = "01";
	switch (m) {
	case 1 :
		str_month = "01";
		break;
	case 2:
		str_month = "02";
		break;
	case 3:
		str_month = "03";
		break;
	case 4:
		str_month = "04";
		break;
	case 5:
		str_month = "05";
		break;
	case 6:
		str_month = "06";
		break;
	case 7:
		str_month = "07";
		break;
	case 8:
		str_month = "08";
		break;
	case 9:
		str_month = "09";
		break;
	case 10:
		str_month = "10";
		break;
	case 11:
		str_month = "11";
		break;
	case 12:
		str_month = "12";
		break;
	default:
		;
	}
		CurrentMonth = AnsiString(y) + "年" + str_month + "月";
	} else {
		SendOrderTime->Date = Now();
		ReachOrderTime->Date = Now() + 1;
		ReachOrderTime->Date.DecodeDate(&y,&m,&d);
		AnsiString str_month = "01";
		switch (m) {
		case 1 :
			str_month = "01";
			break;
		case 2:
			str_month = "02";
			break;
		case 3:
			str_month = "03";
			break;
		case 4:
			str_month = "04";
			break;
		case 5:
			str_month = "05";
			break;
		case 6:
			str_month = "06";
			break;
		case 7:
			str_month = "07";
			break;
		case 8:
			str_month = "08";
			break;
		case 9:
			str_month = "09";
			break;
		case 10:
			str_month = "10";
			break;
		case 11:
			str_month = "11";
			break;
		case 12:
			str_month = "12";
			break;
		default:
			;
		}
		CurrentMonth = AnsiString(y) + "年" + str_month + "月";
	}
	//设置打单者名称
	OperatorName->Text = MainForm->OperatorName;
	if(OperatorName->Text.Trim()=="beslow"){
		auto_next->Checked = false;
		auto_fill->Checked = true;
		strong_insert->Checked = true;
	}
	your_input_is_printed_or_previewed = false;

	btn_num = 0;

	// 临时变量 保存 客户名、门店、单据类型
	temp_customer_name = "";
	temp_store_name = "";
	temp_order_type = "";
}
//---------------------------------------------------------------------------
void __fastcall TPrintOrder::FormClose(TObject *Sender, TCloseAction &Action)
{
	HWND hwnd=FindWindowA(NULL,MainForm->select_panel_name);
	AnsiString str="close^";
	COPYDATASTRUCT myCopyDATA;
	myCopyDATA.cbData=str.Length();
	myCopyDATA.lpData=str.c_str();
	SendMessageA(hwnd,WM_COPYDATA,NULL,(LPARAM)&myCopyDATA);
	Action=caFree;
}
//---------------------------------------------------------------------------

//初始化界面
void __fastcall TPrintOrder::FormCreate(TObject *Sender)
{
	//初始化InputGrid
	InputGrid->Cells[1][0]="简写";
	InputGrid->Cells[2][0]="名称";
	InputGrid->Cells[3][0]="订量";
	InputGrid->Cells[4][0]="实际量";
	InputGrid->Cells[5][0]="规格";
	InputGrid->Cells[6][0]="价格";
	InputGrid->ColWidths[0]=30;
	InputGrid->ColWidths[2]=100;
	for(int i=1;i<InputGrid->RowCount;i++) {
		InputGrid->Cells[0][i]=i;
	}
	StringGrid1->ColWidths[2] = 40;
	StringGrid1->ColWidths[3] = 40;

}
//---------------------------------------------------------------------------

//单位 单击 后发送查询单位字符串
void __fastcall TPrintOrder::CompanyNameClick(TObject *Sender)
{
	HWND hwnd=FindWindowA(NULL,MainForm->select_panel_name);
	AnsiString str="sql^ SELECT companies.simple_name as FName FROM ";
	str += " companies left join customers_companies ";
	str += " on companies.id = customers_companies.customer_id ";
	str += " where (customers_companies.delete_flag is null or customers_companies.delete_flag = 0) ";
	str += " and customers_companies.company_id = " + AnsiString(MainForm->ParentId) + " ^^";
	COPYDATASTRUCT myCopyDATA;
	myCopyDATA.cbData = str.Length();
	myCopyDATA.lpData = str.c_str();
	SendMessageA(hwnd,WM_COPYDATA,NULL,(LPARAM)&myCopyDATA);
}
//---------------------------------------------------------------------------

//打开面板
void __fastcall TPrintOrder::FormShow(TObject *Sender)
{
	AnsiString ExePath = ExtractFilePath(ParamStr(0))+MainForm->select_panel_name+ ".exe";
    WinExec(ExePath.c_str(),SW_SHOW);
}
//---------------------------------------------------------------------------

//门店 单击 后发送查询门店字符串
void __fastcall TPrintOrder::StoreClick(TObject *Sender)
{
	HWND hwnd=FindWindowA(NULL,MainForm->select_panel_name);
	AnsiString str="sql^ SELECT stores.name AS FName FROM stores LEFT JOIN ";
	str += " companies ON stores.company_id = companies.id WHERE ";
	str += "companies.simple_name = \"" + CompanyName->Text.Trim() + "\" ^^";
	COPYDATASTRUCT myCopyDATA;
	myCopyDATA.cbData = str.Length();
	myCopyDATA.lpData = str.c_str();
	SendMessageA(hwnd,WM_COPYDATA,NULL,(LPARAM)&myCopyDATA);
}
//---------------------------------------------------------------------------

//单据类型 单击 后发送查询单据类型字符串
void __fastcall TPrintOrder::OrderTypeClick(TObject *Sender)
{
	HWND hwnd=FindWindowA(NULL,MainForm->select_panel_name);
	AnsiString str="sql^ SELECT order_types.name AS FName FROM order_types LEFT JOIN ";
	str += " companies ON order_types.customer_id = companies.id WHERE (order_types.delete_flag is null or order_types.delete_flag = 0) and order_types.supplier_id = "+AnsiString(MainForm->ParentId);
	str += " and companies.simple_name = \"" + CompanyName->Text.Trim() + "\" ^^";
	COPYDATASTRUCT myCopyDATA;
	myCopyDATA.cbData = str.Length();
	myCopyDATA.lpData = str.c_str();
	SendMessageA(hwnd,WM_COPYDATA,NULL,(LPARAM)&myCopyDATA);
}
//---------------------------------------------------------------------------

//单据类型双击之后切换类型值
void __fastcall TPrintOrder::OrderTypeDblClick(TObject *Sender)
{
	Qry->Close();
	Qry->SQL->Clear();
	AnsiString StrSQL = "SELECT order_types.name AS FName FROM order_types ";
	StrSQL += " LEFT JOIN companies ON order_types.customer_id ";
	StrSQL += " = companies.id WHERE  (order_types.delete_flag is null or order_types.delete_flag = 0) and order_types.supplier_id ="+AnsiString(MainForm->ParentId)+" and companies.simple_name = ";
	StrSQL += "\"" + CompanyName->Text.Trim() + "\"";
	Qry->SQL->Add(StrSQL);
	Qry->Open();
	int Total = Qry->RecordCount;
	if( Total >= 1) {
		Qry->First();
		int t = 1;
		for(;t <= Total;t++,Qry->Next()) {
			if(t == TempNumberOrderType) {
				OrderType->Text = Qry->FieldByName("FName")->AsString;
				if(t == Total) {
					TempNumberOrderType = 1;
				} else {
					TempNumberOrderType += 1;
				}
				break;
			}
		}
	}
}
//---------------------------------------------------------------------------

//门店输入框双击-->切换门店
void __fastcall TPrintOrder::StoreDblClick(TObject *Sender)
{

	Qry->Close();
	Qry->SQL->Clear();
	AnsiString StrSQL = "SELECT stores.name AS FName FROM stores ";
	StrSQL += " LEFT JOIN companies ON stores.company_id ";
	StrSQL += " = companies.id WHERE companies.simple_name = ";
	StrSQL += "\"" + CompanyName->Text.Trim() + "\"";
	Qry->SQL->Add(StrSQL);
	Qry->Open();
	int Total = Qry->RecordCount;
	if( Total >= 1) {
		Qry->First();
		int t = 1;
		for(;t <= Total;t++,Qry->Next()) {
			if(t == TempNumberStore) {
				Store->Text = Qry->FieldByName("FName")->AsString;
				if(t == Total) {
					TempNumberStore = 1;
				} else {
					TempNumberStore += 1;
				}
				break;
			}
		}
	}
}
//---------------------------------------------------------------------------

//如果单位、门店、单据类型都填写了，才可以操作InputGrid
void __fastcall TPrintOrder::CompanyNameChange(TObject *Sender)
{
	if(CompanyName->Text.Trim()!=""&&Store->Text.Trim()!=""&&OrderType->Text.Trim()!=""){
		InputGrid->Enabled = true;
		BitBtn1->Enabled = true;
		BtnPrint->Enabled = true;
		BitBtn2->Enabled = true;
		//Panel1->Visible = true;
		BitBtn7->Enabled = true;
		BitBtn9->Enabled = true;
		BitBtn6->Enabled = true;
		BitBtn3->Enabled = true;

		AnsiString sql;
		//frxReport->DesignReport();
		//获得一些id值，比如company_id、store_id

		sql = "SELECT id FROM companies where simple_name = \""+ CompanyName->Text.Trim() +"\"";
		Qry->Close();
		Qry->SQL->Clear();
		Qry->SQL->Add(sql);
		Qry->Open();
		Qry->First();
		//单位ID
		AnsiString company_id = Qry->FieldByName("id")->AsString;

		sql = "SELECT notice from print_order_notices where customer_id = " + company_id + " and supplier_id = " + AnsiString(MainForm->ParentId);
        Qry->Close();
		Qry->SQL->Clear();
		Qry->SQL->Add(sql);
		Qry->Open();
		Qry->First();
		AnsiString notice = "";
		for (int i = 1; i <= Qry->RecordCount; i++,Qry->Next()) {
			notice += Qry->FieldByName("notice")->AsString + ";";		
		}
		Label15->Caption = notice;
	}
	else{
		InputGrid->Enabled = false;
		BitBtn1->Enabled = false;
		BtnPrint->Enabled = false;
		BitBtn2->Enabled = false;
		//Panel1->Visible = false;
		BitBtn7->Enabled = false;
		BitBtn9->Enabled = false;
		BitBtn6->Enabled = false;
		BitBtn3->Enabled = false;
	}
}
//---------------------------------------------------------------------------

//即时改变面板的位置
void __fastcall TPrintOrder::Timer1Timer(TObject *Sender)
{
	HWND hwnd=FindWindowA(NULL,MainForm->select_panel_name);
	AnsiString str="pos^"+AnsiString(Left-300)+"^^"+AnsiString(Top+40);
	COPYDATASTRUCT myCopyDATA;
	myCopyDATA.cbData = str.Length();
	myCopyDATA.lpData = str.c_str();
	SendMessageA(hwnd,WM_COPYDATA,NULL,(LPARAM)&myCopyDATA);
}
//---------------------------------------------------------------------------




void __fastcall TPrintOrder::InputGridSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{
	if(ACol==2)
	{
//		AnsiString sql="";
//        sql = "SELECT id FROM companies where simple_name = \""+ CompanyName->Text.Trim() +"\"";
//		Qry->Close();
//		Qry->SQL->Clear();
//		Qry->SQL->Add(sql);
//		Qry->Open();
//		Qry->First();
//		//单位ID
//		company_id = Qry->FieldByName("id")->AsString;
//
//		sql = "SELECT id FROM stores where name = \""+ Store->Text.Trim() +"\"";
//		Qry->Close();
//		Qry->SQL->Clear();
//		Qry->SQL->Add(sql);
//		Qry->Open();
//		Qry->First();
//		//门店ID
//		store_id = Qry->FieldByName("id")->AsString;
//
//		sql = "SELECT * FROM order_types where name = \""+ OrderType->Text.Trim() +"\" and company_id = " + company_id;
//		Qry->Close();
//		Qry->SQL->Clear();
//		Qry->SQL->Add(sql);
//		Qry->Open();
//		Qry->First();
//		//单据类型ID
//		order_type_id = Qry->FieldByName("id")->AsString;
//
//		//到货日期
//		reach_order_date = ReachOrderTime->Date.DateString();
//
//		//订货日期
//		send_order_date = SendOrderTime->Date.DateString();
//
//		TDateTime temp = Now();
//		//打单时间
//		created_at = temp.DateTimeString();
//
//		sql = " SELECT id FROM year_months WHERE val = '"+ CurrentMonth +"'";
//		Qry->Close();
//		Qry->SQL->Clear();
//		Qry->SQL->Add(sql);
//		Qry->Open();
//		Qry->First();
//		//月份ID
//		year_month_id = Qry->FieldByName("id")->AsString;

		HWND hwnd=FindWindowA(NULL,MainForm->select_panel_name);
		AnsiString str="sql^ ";
		COPYDATASTRUCT myCopyDATA;
		if(InputGrid->Cells[1][ARow].Trim() != "") {
			str += " SELECT products.chinese_name AS FName FROM prices ";
			str += " LEFT JOIN products ON products.id = prices.product_id ";
			str += " LEFT JOIN year_months ON prices.year_month_id = year_months.id ";
			str += " LEFT JOIN companies ON prices.customer_id = companies.id ";
			str += " WHERE 1 = 1 and products.is_valid = 1 AND prices.is_used = 1 ";
			str += " AND prices.supplier_id = " + AnsiString(MainForm->ParentId);
			str += " AND companies.simple_name = \"" + CompanyName->Text + "\" ";
			str += " AND year_months.val = \"" + CurrentMonth + "\" ";
			str += " AND products.simple_abc LIKE \"%" + InputGrid->Cells[1][ARow].Trim() + "%\" ";
			str += " ORDER BY prices.print_times DESC ";
		} else {
			str += " select '简写没有输入!' as FName";
		}
		str += " ^^";

		myCopyDATA.cbData=str.Length();
        myCopyDATA.lpData=str.c_str();
		SendMessageA(hwnd,WM_COPYDATA,NULL,(LPARAM)&myCopyDATA);

		if(auto_fill->Checked && InputGrid->Cells[1][ARow].Trim() != "") {
			AnsiString StrSQL = " SELECT products.chinese_name as chinese_name, prices.* ";
			StrSQL += " FROM prices ";
			StrSQL += " LEFT JOIN products ON products.id = prices.product_id ";
			StrSQL += " LEFT JOIN year_months ON prices.year_month_id = year_months.id ";
			StrSQL += " LEFT JOIN companies ON prices.customer_id = companies.id ";
			StrSQL += " WHERE products.is_valid = 1 and 1 = 1 AND prices.is_used = 1 ";
			StrSQL += " AND prices.supplier_id = " + AnsiString(MainForm->ParentId);
			StrSQL += " AND companies.simple_name = \""+ CompanyName->Text.Trim() +"\" ";
			StrSQL += " AND year_months.val = \""+ CurrentMonth +"\" ";
			StrSQL += " AND products.simple_abc LIKE \"%" + InputGrid->Cells[1][ARow].Trim() + "%\" ";
			StrSQL += " ORDER BY prices.print_times DESC ";
			Qry->SQL->Add(StrSQL);
			Qry->Close();
			Qry->SQL->Clear();
			Qry->SQL->Add(StrSQL);
			Qry->Open();
			Qry->First();
			if(Qry->RecordCount == 1) {		
				Qry->First();
				InputGrid->Cells[2][ARow] = Qry->FieldByName("chinese_name")->AsString;
				InputGrid->Cells[5][ARow] = Qry->FieldByName("true_spec")->AsString;
				AnsiString temp_price = Qry->FieldByName("price")->AsString;
				InputGrid->Cells[6][ARow] = temp_price==AnsiString("0")?AnsiString(""):temp_price;
				if(!auto_next->Checked){
					keybd_event(9,0,0,0);
					keybd_event(9,0,KEYEVENTF_KEYUP,0);
				}
			} else if(Qry->RecordCount > 1 && strong_insert->Checked){
				Qry->First();
				InputGrid->Cells[2][ARow] = Qry->FieldByName("chinese_name")->AsString;
				InputGrid->Cells[5][ARow] = Qry->FieldByName("true_spec")->AsString;
				AnsiString temp_price = Qry->FieldByName("price")->AsString;
				InputGrid->Cells[6][ARow] = temp_price==AnsiString("0")?AnsiString(""):temp_price;
				if(!auto_next->Checked){
					keybd_event(9,0,0,0);
					keybd_event(9,0,KEYEVENTF_KEYUP,0);
				}
			}
		}
    }
}
//---------------------------------------------------------------------------

void __fastcall TPrintOrder::ReachOrderTimeChange(TObject *Sender)
{
	unsigned short y,m,d;
	ReachOrderTime->Date.DecodeDate(&y,&m,&d);
	AnsiString str_month = "01";
	switch (m) {
	case 1 :
		str_month = "01";
		break;
	case 2:
		str_month = "02";
		break;
	case 3:
		str_month = "03";
		break;
	case 4:
		str_month = "04";
		break;
	case 5:
		str_month = "05";
		break;
	case 6:
		str_month = "06";
		break;
	case 7:
		str_month = "07";
		break;
	case 8:
		str_month = "08";
		break;
	case 9:
		str_month = "09";
		break;
	case 10:
		str_month = "10";
		break;
	case 11:
		str_month = "11";
		break;
	case 12:
		str_month = "12";
		break;
	default:
		;
	}
	CurrentMonth = AnsiString(y) + "年" + str_month + "月";
}
//---------------------------------------------------------------------------

void __fastcall TPrintOrder::InputGridKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key== VK_RETURN&&InputGrid->Row< InputGrid->RowCount-1) {
		if(CheckBox1->Checked && InputGrid->Col==1){
			//使用扫描枪
			//查询对应条形码的产品
			AnsiString str = "";
			str += " SELECT products.chinese_name, prices.price, prices.true_spec  ";
			str += " FROM prices ";
			str += " LEFT JOIN products ON products.id = prices.product_id ";
			str += " LEFT JOIN year_months ON prices.year_month_id = year_months.id ";
			str += " LEFT JOIN companies ON prices.customer_id = companies.id ";
			str += " WHERE 1 = 1 ";
			str += " AND prices.is_used = 1 ";
			str += " AND prices.supplier_id =  " + AnsiString(MainForm->ParentId) + " ";
			str += " AND companies.simple_name = '"+CompanyName->Text.Trim()+"' ";
			str += " AND year_months.val = '"+CurrentMonth+"' ";
			str += " AND products.barcode = '"+InputGrid->Cells[1][InputGrid->Row]+"' ";
			Qry->Close();
			Qry->SQL->Clear();
			Qry->SQL->Add(str);
			Qry->Open();
			Qry->First();
			AnsiString chinese_name = Qry->FieldByName("chinese_name")->AsString;
			AnsiString price = Qry->FieldByName("price")->AsString;
			AnsiString true_spec = Qry->FieldByName("true_spec")->AsString;
			InputGrid->Cells[2][InputGrid->Row] = chinese_name;
			InputGrid->Cells[5][InputGrid->Row] = true_spec;
			InputGrid->Cells[6][InputGrid->Row] = price==AnsiString("0")?AnsiString(""):price;
            InputGrid->Col = 3;
		}
		else
		{
			InputGrid->Row++;
			InputGrid->Col = 1;
		}
	}
	//if(Key== VK_TAB&&InputGrid->Col<4) InputGrid->Col++;
	if(Key== VK_TAB&&InputGrid->Col==4&&InputGrid->Row< InputGrid->RowCount-1){
		if(CheckBox1->Checked){

		}
		else{
			InputGrid->Row++;
			InputGrid->Col = 1;
		}
	}

}
//---------------------------------------------------------------------------

//打印
void __fastcall TPrintOrder::BtnPrintClick(TObject *Sender)
{
	TfrxReport* re=printORshow();
	if(re!=NULL) re->Print(); else return;
	your_input_is_printed_or_previewed = true;
	BitBtn3Click(Sender);
}
//---------------------------------------------------------------------------



void __fastcall TPrintOrder::frxReportGetValue(const UnicodeString VarName, Variant &Value)

{
	if(VarName=="CompanyName") Value = "value_a";
}
//---------------------------------------------------------------------------

TfrxReport* __fastcall TPrintOrder::printORshow()
{
	// 保存客户名、门店、单据类型
	temp_customer_name = CompanyName->Text.Trim();
	temp_store_name = Store->Text.Trim();
	temp_order_type = OrderType->Text.Trim();
	
 	bool has_detail = false;
	for(unsigned i=1;i<=InputGrid->RowCount;i++){
		if(InputGrid->Cells[2][i].Trim()=="") continue; else has_detail = true;
		if(InputGrid->Cells[3][i].Trim()=="") {
			ShowMessage("第"+AnsiString(i)+"行"+InputGrid->Cells[2][i].Trim()+"的订量没有填写！");
			return NULL;
		}
		if(InputGrid->Cells[2][i].Trim()=="大孔芝士" && CompanyName->Text.Trim()=="梦奇屋"){
			try
			{
				StrToInt(InputGrid->Cells[5][i].Trim());
				ShowMessage("第"+AnsiString(i)+"行"+InputGrid->Cells[2][i].Trim()+"的到货量应该是带小数点的数（比如2.729）！");
				return NULL;
			}
			catch(EConvertError &e)
			{

			}
		}
	}
	if(!has_detail) {
		ShowMessage("您还没有填写任何品项！");
		return NULL;
	}

	AnsiString sql;
	//frxReport->DesignReport();
	//获得一些id值，比如company_id、store_id

	sql = "SELECT id FROM companies where simple_name = \""+ CompanyName->Text.Trim() +"\"";
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	//单位ID
	company_id = Qry->FieldByName("id")->AsString;

	sql = "SELECT id FROM stores where name = \""+ Store->Text.Trim() +"\" and company_id = " +company_id;
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	//门店ID
	store_id = Qry->FieldByName("id")->AsString;

	sql = "SELECT * FROM order_types where supplier_id = "+AnsiString(MainForm->ParentId)+" and name = \""+ OrderType->Text.Trim() +"\" and customer_id = " + company_id;
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	//单据类型ID
	order_type_id = Qry->FieldByName("id")->AsString;

	//到货日期
	reach_order_date = ReachOrderTime->Date.DateString();

	//订货日期
	send_order_date = SendOrderTime->Date.DateString();

	TDateTime temp = Now();
	//打单时间
	created_at = temp.DateTimeString();

	sql = " SELECT id FROM year_months WHERE val = '"+ CurrentMonth +"'";
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	//月份ID
	year_month_id = Qry->FieldByName("id")->AsString;

	//查询要打的单据是否已经存在，存在的话放出，弹出提示框，问是否覆盖已经打印了的单据
	//选择是，就会覆盖，选择否，取消打印
	sql = " select * from orders ";
	sql += " WHERE customer_id = "+company_id+" and store_id = "+store_id+" and order_type_id = "+order_type_id+" ";
	sql += " and supplier_id = "+AnsiString(MainForm->ParentId)+" and reach_order_date = '"+reach_order_date+"' ";
	sql += " and (delete_flag is null or delete_flag=0) ";
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	//查到的单据的ID
	AnsiString will_delete_order_id = Qry->FieldByName("id")->AsString;

//	UnicodeString Warning = CompanyName->Text.Trim()+" "+Store->Text.Trim()+" "+OrderType->Text.Trim();
//	Warning += reach_order_date +" "+"已经有了，是否要覆盖呢？";
	if(Qry->RecordCount>0) {
		if(Application->MessageBox(L"对应您输入的单位、门店、单据类型、送货日期的单据已经有了，是否覆盖？",L"温馨提示",MB_YESNO)!=6)
			return NULL;
	}

	//逻辑删除旧的表单
	sql = " UPDATE orders set delete_flag = true ";
	sql += " WHERE customer_id = "+company_id+" and store_id = "+store_id+" and order_type_id = "+order_type_id+" ";
	sql += " and supplier_id = "+AnsiString(MainForm->ParentId)+" and reach_order_date = '"+reach_order_date+"' ";
	Cmd->SQL->Clear();
	Cmd->SQL->Add(sql);
	Cmd->Execute();

	if (will_delete_order_id != "") {
		sql = " select * from order_items where order_id = " + will_delete_order_id;
		Qry->Close();
		Qry->SQL->Clear();
		Qry->SQL->Add(sql);
		Qry->Open();
		Qry->First();
		AnsiString price_ids = "";
		AnsiString product_ids = "";
		for(signed i=1;i<=Qry->RecordCount;i++,Qry->Next())
		{
			price_ids += Qry->FieldByName("price_id")->AsString.Trim();
			price_ids += ",";
			product_ids += Qry->FieldByName("product_id")->AsString.Trim();
			product_ids += ",";
		}
		price_ids += "-1";
		product_ids += "-1";
		//单据删除后，对应的品项对应的产品和价格的打印次数都要减1
		sql = "update prices set print_times = print_times - 1 where id in ( " + price_ids + " )";
		Cmd->SQL->Clear();
		Cmd->SQL->Add(sql);
		Cmd->Execute();
		sql = "update products set print_times = print_times - 1 where id in (" + product_ids + ")";
		Cmd->SQL->Clear();
		Cmd->SQL->Add(sql);
		Cmd->Execute();
	}

	//***********************************************************
	//将数据插入表orders和表order_items
	//第一步，插入一条orders记录
	sql = "";
	sql += " insert into `orders` (`customer_id`,`store_id`,`order_type_id`,`reach_order_date`,`send_order_date`,`created_at`,`user_id`, `supplier_id`) ";
	sql += " values('"+ company_id +"','"+store_id+"','"+order_type_id+"','"+reach_order_date+"','"+send_order_date+"','"+created_at+"','"+ MainForm->OperatorId +"','"+ AnsiString(MainForm->ParentId) +"') ";
	Cmd->SQL->Clear();
	Cmd->SQL->Add(sql);
	Cmd->Execute();
	AnsiString order_id = Cmd->InsertId;

	//第二步，插入很多条order_items记录
	AnsiString product_id = "";
	AnsiString price_id = "";
	AnsiString price_from = "";
	AnsiString true_spec_from = "";
	bool need_result = true;
	float total_money = 0.0;
	for(unsigned i=1;i<=InputGrid->RowCount;i++){
		if(InputGrid->Cells[2][i].Trim()=="") continue;
		//获得一些id值，比如product_id、price_id
		sql = "SELECT id FROM products WHERE is_valid = 1 and chinese_name = '"+ InputGrid->Cells[2][i] +"' and supplier_id = " + AnsiString(MainForm->ParentId);
		Qry->Close();
		Qry->SQL->Clear();
		Qry->SQL->Add(sql);
		Qry->Open();
		if(Qry->RecordCount==0) {
			ShowMessage("第"+AnsiString(i)+"行的"+InputGrid->Cells[2][i]+"不在价格表中，是你手动添加的吧！添加新品项，请在右下角 新增品项名中添加！");
			return NULL;
		}
		Qry->Last();
		//产品ID
		product_id = Qry->FieldByName("id")->AsString;

		sql = " SELECT id, ratio, customer_id,product_id, supplier_id,year_month_id, price, true_spec FROM prices WHERE is_used = true and year_month_id = "+year_month_id+" and customer_id = "+company_id+" and  product_id = "+product_id+" and supplier_id = " + AnsiString(MainForm->ParentId) + " order by id";
		Qry->Close();
		Qry->SQL->Clear();
		Qry->SQL->Add(sql);
		Qry->Open();
		Qry->First();
		//价格ID
		price_id = Qry->FieldByName("id")->AsString;
		AnsiString tt_customer_id = Qry->FieldByName("customer_id")->AsString;
		AnsiString tt_product_id = Qry->FieldByName("product_id")->AsString;
		AnsiString tt_supplier_id = Qry->FieldByName("supplier_id")->AsString;
		AnsiString tt_year_month_id = Qry->FieldByName("year_month_id")->AsString;
		price_from = Qry->FieldByName("price")->AsString;
		true_spec_from = Qry->FieldByName("true_spec")->AsString;
        AnsiString ratio = Qry->FieldByName("ratio")->AsString;
        if(ratio=="") ratio="0";
		AnsiString last_spec = InputGrid->Cells[5][i].Trim();
		AnsiString real_weight = InputGrid->Cells[4][i].Trim();
		AnsiString last_price = InputGrid->Cells[6][i].Trim();
		//价格更新，任何价格变化都会影响到数据库
		float temp_1_last_price = 0.0;
		if (last_price=="") last_price="0.0";
		if (price_from=="") price_from="0.0";
		if( TryStrToFloat(last_price, temp_1_last_price) )  {
			if(fabs(StrToFloat(last_price)-StrToFloat(price_from))> 0.01) {
				sql = "update prices set is_used = false where id = "+ price_id;
				Cmd->SQL->Clear();
				Cmd->SQL->Add(sql);
				Cmd->Execute();
				sql = "insert into `prices` (`year_month_id`,`customer_id`,`product_id`,`price`,`is_used`,`created_at`,`true_spec`,`supplier_id`, `ratio`) ";
				sql += " values("+tt_year_month_id+","+tt_customer_id+","+tt_product_id+",'"  +last_price.Trim()+    "',true,'"+created_at+"','"+last_spec+"','"+AnsiString(MainForm->ParentId)+"', "+ratio+")";
                Cmd->SQL->Clear();
				Cmd->SQL->Add(sql);
				Cmd->Execute();
				price_id = Cmd->InsertId;

				//记录此次价格修改
				sql = " insert into `price_change_histories` (`price_id`,`from_price`,`to_price`,`change_time`,`user_id`) ";
				sql += "values("+price_id+","+price_from+","+last_price+",'"+created_at+"',"+MainForm->OperatorId+")";
				Cmd->SQL->Clear();
				Cmd->SQL->Add(sql);
				Cmd->Execute();
			} else if (last_spec!= true_spec_from) {
				sql = "update prices set is_used = false where id = "+ price_id;
				Cmd->SQL->Clear();
				Cmd->SQL->Add(sql);
				Cmd->Execute();
				sql = "insert into `prices` (`year_month_id`,`customer_id`,`product_id`,`price`,`is_used`,`created_at`,`true_spec`,`supplier_id`, `ratio`) ";
				sql += " values("+tt_year_month_id+","+tt_customer_id+","+tt_product_id+",'"  +last_price.Trim()+    "',true,'"+created_at+"','"+last_spec+"','"+AnsiString(MainForm->ParentId)+"', 0)";
				Cmd->SQL->Clear();
				Cmd->SQL->Add(sql);
				Cmd->Execute();
				price_id = Cmd->InsertId;

				//sql = "update prices set ratio = 0 and true_spec = '"+last_spec+"' where id = "+ price_id;
				//Cmd->SQL->Clear();
				//Cmd->SQL->Add(sql);
				//Cmd->Execute();
			}
		}else {
			ShowMessage("第"+AnsiString(i)+"行"+InputGrid->Cells[2][i]+"的价格有问题，应该是数值");
			return NULL;
		}

//		规格更新，任何规格变化都会影响到数据库
//		if(last_spec!= true_spec_from){
//			sql = "update prices set true_spec = '"+last_spec+"' where id = "+ price_id;
//			Cmd->SQL->Clear();
//			Cmd->SQL->Add(sql);
//			Cmd->Execute();
//		}


		sql = " insert into `order_items` (`order_id`,`product_id`,`price_id`,`plan_weight`,`real_weight`,`created_at`,`money`) ";
		sql += " values('"+ order_id +"','"+product_id+"','"+ price_id +"','"+InputGrid->Cells[3][i];
		if(real_weight == ""){ real_weight = "NULL";}
		sql += "',"+real_weight+",'"+created_at+"',";
		float temp_real_weight = 0.0;
		float temp_last_price = 0.0;
		if(TryStrToFloat(real_weight, temp_real_weight) && TryStrToFloat(last_price, temp_last_price) ) {
			float result = temp_real_weight*temp_last_price;
			sql +=  AnsiString(result) +")";
			total_money += result;
		} else {
			sql += "null)";
			need_result = false;
		}
		Cmd->SQL->Clear();
		Cmd->SQL->Add(sql);
		Cmd->Execute();

		//更新价格表打印次数
		sql = " update prices set print_times = print_times + 1 where id = " + price_id;
		Cmd->SQL->Clear();
		Cmd->SQL->Add(sql);
		Cmd->Execute();

		//更新产品表打印次数
		sql = " update products set print_times = print_times + 1 where id = " + product_id;
		Cmd->SQL->Clear();
		Cmd->SQL->Add(sql);
		Cmd->Execute();
	}
	// 更新order的not_input_number字段
	sql = "";
	sql += " select count(*) as not_input_number from order_items ";
	sql += " left join orders on orders.id = order_items.order_id ";
	sql += " where orders.id = " + order_id + " and order_items.real_weight = 0 ";
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	AnsiString not_input_number = Qry->FieldByName("not_input_number")->AsString;
	sql = " update orders set not_input_number = " + not_input_number + " where id = " + order_id;
	Cmd->SQL->Clear();
	Cmd->SQL->Add(sql);
	Cmd->Execute();


	AnsiString ExePath=ExtractFilePath(ParamStr(0))+"报表\\"+"order_template.fr3";
	frxReport->LoadFromFile(ExePath);
	//为报表准备表头相关数据
	sql = " SELECT '"+ MainForm->OperatorCompanyName + "' AS supplier_name, '"+CompanyName->Text+"' AS company_name, '"+Store->Text+"' AS store_name, ";
	sql += " '"+OrderType->Text+"' AS order_type, '"+ReachOrderTime->Date.DateString()+"' AS reach_date, ";
	sql += " '"+OperatorName->Text+"' AS printer, '"+order_id+"' AS order_id, '"+company_id+"' AS company_id ";
	if(need_result) {
		sql += ",'"+AnsiString(FormatFloat("0.00",total_money))+"' AS total_money ";
	} else {
		sql += ", '' AS total_money ";
	}
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	frxTitleData->DataSet = Qry;
	frxReport->DataSets->Add(frxTitleData);

	//为报表准备明细相关数据
	sql = " SELECT products.chinese_name AS name,prices.true_spec AS speci, ";
	sql +=" order_items.plan_weight AS order_weight, ";
	sql +=" case order_items.real_weight when 0 then '' else order_items.real_weight end AS real_weight, ";
	sql +=" case prices.price when 0 then '' else prices.price end AS price, case order_items.money when 0 then '' else order_items.money end AS money ";
	sql +=" FROM order_items ";
	sql +=" left join products on products.id=order_items.product_id ";
	sql +=" left join prices on prices.id=order_items.price_id ";
	sql +=" where products.is_valid = 1 and order_items.order_id = " + order_id;
	QryDetail->Close();
	QryDetail->SQL->Clear();
	QryDetail->SQL->Add(sql);
	QryDetail->Open();
	frxDetailData->DataSet = QryDetail;
	frxReport->DataSets->Add(frxDetailData);

	frxReport->PrepareReport(true);
	if(chk_default_printer->Checked)
		frxReport->PrintOptions->ShowDialog=false;
	else
		frxReport->PrintOptions->ShowDialog=true;
	return frxReport;


}

//预览
void __fastcall TPrintOrder::BitBtn1Click(TObject *Sender)
{
	TfrxReport* re=printORshow();
	if(re!=NULL) re->ShowPreparedReport(); else return;
	your_input_is_printed_or_previewed = true;
}
//---------------------------------------------------------------------------

void __fastcall TPrintOrder::BitBtn2Click(TObject *Sender)
{
	AnsiString sql;
	//获得一些id值，比如company_id、store_id
	sql = "SELECT id FROM companies where simple_name = \""+ CompanyName->Text.Trim() +"\"";
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	//单位ID
	company_id = Qry->FieldByName("id")->AsString;

	sql = "SELECT id FROM stores where name = \""+ Store->Text.Trim() +"\" and company_id = " +company_id;
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	//门店ID
	store_id = Qry->FieldByName("id")->AsString;

	sql = "SELECT id FROM order_types where supplier_id = "+AnsiString(MainForm->ParentId)+" and name = \""+ OrderType->Text.Trim() +"\" and customer_id = " + company_id;
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	//单据类型ID
	order_type_id = Qry->FieldByName("id")->AsString;

	//到货日期
	reach_order_date = ReachOrderTime->Date.DateString();

	sql= "select id from orders where supplier_id = "+AnsiString(MainForm->ParentId)+" and customer_id="+company_id+" and store_id="+store_id+" and order_type_id = "+order_type_id+" and reach_order_date='"+reach_order_date+"' and (delete_flag is null or delete_flag=0)";
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	if(Qry->RecordCount==0){
		ShowMessage(CompanyName->Text.Trim()+"->"+Store->Text.Trim()+"->"+OrderType->Text.Trim()+"->"+reach_order_date+"->还没打印过！");
		Qry->Close();
		return;
	}
	Qry->First();
	//单据ID
	AnsiString order_id = Qry->FieldByName("id")->AsString;
	sql="select ";
	sql+=" products.simple_abc as simple_abc, products.chinese_name as chinese_name, ";
	sql+=" order_items.plan_weight as plan_weight, order_items.real_weight as real_weight, ";
	sql+=" prices.true_spec as true_spec, prices.price as price ";
	sql+=" from order_items ";
	sql+=" left join products on products.id=order_items.product_id ";
	sql+=" left join prices on prices.id=order_items.price_id ";
	sql+=" where products.is_valid = 1 and order_items.order_id= "+order_id;

	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	for(signed i=1;i<=Qry->RecordCount;i++,Qry->Next())
	{
		InputGrid->Cells[1][i]=Qry->FieldByName("simple_abc")->AsString.Trim();
		InputGrid->Cells[2][i]=Qry->FieldByName("chinese_name")->AsString.Trim();
		InputGrid->Cells[3][i]=Qry->FieldByName("plan_weight")->AsString.Trim();
		AnsiString temp_real_weight = Qry->FieldByName("real_weight")->AsString.Trim();
		InputGrid->Cells[4][i]=(temp_real_weight==AnsiString("0"))?AnsiString(""):temp_real_weight;
		InputGrid->Cells[5][i]=Qry->FieldByName("true_spec")->AsString.Trim();
		AnsiString price=Qry->FieldByName("Price")->AsString.Trim();
		InputGrid->Cells[6][i]=(price==AnsiString("0"))?AnsiString(""):price;
	}
}
//---------------------------------------------------------------------------

void __fastcall TPrintOrder::BitBtn3Click(TObject *Sender)
{
	if(!your_input_is_printed_or_previewed) {
		ShowMessage("您的输入还没有打印呢！");
		return;
    }
	CompanyName->Text = "";
	Store->Text = "";
	OrderType->Text = "";
	Label10->Caption = "";
	for(int i=1;i<=InputGrid->ColCount;i++)
	{
		for(int j=1;j<=InputGrid->RowCount;j++)
		{
			InputGrid->Cells[i][j]="";
		}
	}
	InputGrid->Row=1;
	your_input_is_printed_or_previewed=false;
	CompanyName->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TPrintOrder::BitBtn4Click(TObject *Sender)
{
	for(int i=1;i<=btn_num;i++) {
		delete btn[i];
	}
	btn_num = 0;
	shifang = true;
	Panel2->Visible = false;

	if(will_add->Text.Trim()==""){
		ShowMessage("哎呀！还没填写新增品项名！");
		return;
	}
	AnsiString sql;
	sql="select * from products where is_valid = 1 and chinese_name like '%"+will_add->Text.Trim()+"%'";
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	if(!shifang) {
		for(int i=0;i<50;i++){
			delete btn[i];
		}
	}
	shifang = true;
	if(Qry->RecordCount>0) {
		btn_num = Qry->RecordCount;
		for(signed i=1;i<=btn_num;i++,Qry->Next())
		{
			btn[i]=new TBitBtn(this);
			btn[i]->Parent = Panel2;
			btn[i]->Caption = Qry->FieldByName("chinese_name")->AsString;
			btn[i]->Top=(i-1)* (btn[i]->Height);
			btn[i]->OnClick = BnClick;
		}
		shifang = false;
		Label8->Visible = false;
		edit->Visible = false;
		BitBtn5->Visible = false;

	} else {
		Label8->Visible = true;
		edit->Visible = true;
		BitBtn5->Visible = true;
//		Label13->Visible = true;
//		Label14->Visible = true;
//		Edit2->Visible = true;
//		Edit3->Visible = true;
	}
	Edit2->Text = "";
	Edit3->Text = "";
	Panel2->Visible = true;
	message->Caption = "右边继续-->";
}
//---------------------------------------------------------------------------

void __fastcall TPrintOrder::BnClick(TObject *Sender)//动态创建的按钮的单击事件响应
{
	AnsiString t_price = Edit3->Text.Trim();
	AnsiString t_true_spec = Edit2->Text.Trim();
	AnsiString sql="";
	//获得一些id值

	sql = "SELECT id FROM companies where simple_name = \""+ CompanyName->Text.Trim() +"\"";
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	//单位ID
	company_id = Qry->FieldByName("id")->AsString;

	sql = " SELECT id FROM year_months WHERE val = '"+ CurrentMonth +"'";
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	//月份ID
	year_month_id = Qry->FieldByName("id")->AsString;

	TBitBtn* movebtn = (TBitBtn*)Sender;
	AnsiString caption = movebtn->Caption;
	sql="select id, simple_abc from products where is_valid = 1 and chinese_name = '"+caption+"'";
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	//产品ID
	AnsiString product_id = Qry->FieldByName("id")->AsString;
	AnsiString suoxie = Qry->FieldByName("simple_abc")->AsString;

	sql = "select * from prices where is_used = true and year_month_id ="+year_month_id;
	sql +=" and customer_id="+company_id;
	sql +=" and product_id="+product_id;
	sql +=" and supplier_id="+AnsiString(MainForm->ParentId);
    Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	if(Qry->RecordCount>0) {
//		Qry->First();
//		//价格ID
//		AnsiString price_id = Qry->FieldByName("id")->AsString;
//		AnsiString origin_true_spec = Qry->FieldByName("true_spec")->AsString;
//		if(t_price!=AnsiString("")){
//        	sql = "update prices set is_used = false where year_month_id ="+year_month_id;
//			sql +=" and customer_id="+company_id;
//			sql +=" and product_id="+product_id;
//			sql +=" and supplier_id="+AnsiString(MainForm->ParentId);
//			Cmd->SQL->Clear();
//			Cmd->SQL->Add(sql);
//			Cmd->Execute();
//			sql  = "insert into `prices` (`year_month_id`,`customer_id`,`product_id`,`price`,`is_used`,`created_at`,`true_spec`,`supplier_id`) ";
//			sql += " values("+year_month_id+","+company_id+","+product_id;
//			sql += ",'"+t_price+"',true,'"+created_at+"','";
//			if(t_true_spec==AnsiString("")){
//				sql+= origin_true_spec + "','"+AnsiString(MainForm->ParentId)+"')";
//			} else {
//				sql+= t_true_spec      + "','"+AnsiString(MainForm->ParentId)+"')";
//			}
//			//ShowMessage("已经存在此价格，更新后插入一条:"+sql);
//			Cmd->SQL->Clear();
//			Cmd->SQL->Add(sql);
//			Cmd->Execute();
//		}
		ShowMessage(caption + "已经存在于价格表中，缩写是" + suoxie);
	} else {
		TDateTime temp = Now();
		created_at = temp.DateTimeString();
		sql = "insert into `prices` (`year_month_id`,`customer_id`,`product_id`,`price`,`is_used`,`created_at`,`true_spec`,`supplier_id`) ";
		sql += " values("+year_month_id+","+company_id+","+product_id+",'";
		if (t_price==AnsiString("")) {
			sql += "0.0";
		} else{
			sql += t_price;
        }
		sql+="',true,'"+created_at+"','";
		sql+= t_true_spec;
		sql+="','"+AnsiString(MainForm->ParentId)+"')";
		//ShowMessage("不存在此价格，插入一条:"+sql);
		Cmd->SQL->Clear();
		Cmd->SQL->Add(sql);
		Cmd->Execute();
	}
	for(int i=1;i<=btn_num;i++) {
        delete btn[i];
	}
	btn_num = 0;
	shifang = true;
	will_add->Text = "";
	Panel2->Visible = false;
	message->Caption = caption+"添加成功！";
	InputGrid->SetFocus();
}

void __fastcall TPrintOrder::BitBtn5Click(TObject *Sender)
{
	AnsiString simple_abc = edit->Text.Trim();
	AnsiString t_price = Edit3->Text.Trim();
	AnsiString t_true_spec = Edit2->Text.Trim();
	if ( simple_abc == AnsiString("") ) {
		ShowMessage("字母缩写没有填！请填写。");
		return;
	}
	TDateTime temp = Now();
	created_at = temp.DateTimeString();
	AnsiString sql="";
	//查找seller_id
	AnsiString seller_id = "";
	sql = "select id from sellers where name = '其他' and (delete_flag is null or delete_flag = 0 ) and supplier_id = " + AnsiString(MainForm->ParentId);
	Qry->Close();
    Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	if (Qry->RecordCount>0) {
		Qry->First();
		seller_id = Qry->FieldByName("id")->AsString;
	} else {
		ShowMessage("卖家表中没有名为\"其他\"的卖家，请添加");
		return;
	}

	AnsiString another_seller_id = "";
	sql = "select id from sellers where name = '其他东西' and delete_flag = 1 and supplier_id = " + AnsiString(MainForm->ParentId);
	Qry->Close();
    Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	if (Qry->RecordCount>0) {
		Qry->First();
		another_seller_id = Qry->FieldByName("id")->AsString;
	} else {
		ShowMessage("卖家表中没有名为\"其他东西\"的卖家，请添加");
		return;
	}

	//检查新增品项是否已经存在
	sql="select id, simple_abc from products where is_valid = 1 and chinese_name = '"+will_add->Text.Trim()+"'";
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	AnsiString product_id = "";
	if (Qry->RecordCount>0) {
		Qry->First();
		product_id = Qry->FieldByName("id")->AsString;
	} else {
		sql = " select id from general_products where name = '"+ will_add->Text.Trim() +"' ";
		sql += " and supplier_id = " + AnsiString(MainForm->ParentId);
		Qry->Close();
		Qry->SQL->Clear();
		Qry->SQL->Add(sql);
		Qry->Open();
		AnsiString general_product_id = "";
		if (Qry->RecordCount>0) {
			Qry->First();
			general_product_id = Qry->FieldByName("id")->AsString;
		}	else {
			//新增产品的同时也要新增通用产品
			sql = " insert into `general_products` (`name`, `seller_id`, `another_seller_id`, `supplier_id`) ";
			sql += " values('" + will_add->Text.Trim()+"','"+seller_id+"','"+another_seller_id+"','"+AnsiString(MainForm->ParentId)+"')";
			Cmd->SQL->Clear();
			Cmd->SQL->Add(sql);
			Cmd->Execute();
			//通用产品ID
			general_product_id = Cmd->InsertId;
		}

		sql=" insert into `products` (`chinese_name`,`simple_abc`,`created_at`, `supplier_id`,`general_product_id`, `print_times`) ";
		sql+=" values('"+will_add->Text.Trim()+"','"+simple_abc+"','"+created_at+"','" + AnsiString(MainForm->ParentId) + "','"+general_product_id+"','0')";
		Cmd->SQL->Clear();
		Cmd->SQL->Add(sql);
		Cmd->Execute();
		//产品ID
		product_id = Cmd->InsertId;
    }


	sql = "SELECT id FROM companies where simple_name = \""+ CompanyName->Text.Trim() +"\"";
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	//单位ID
	company_id = Qry->FieldByName("id")->AsString;

	sql = " SELECT id FROM year_months WHERE val = '"+ CurrentMonth +"'";
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	//月份ID
	year_month_id = Qry->FieldByName("id")->AsString;
	if(t_price==AnsiString("")){
    	t_price="0.0";
	}
	sql = "insert into `prices` (`year_month_id`,`customer_id`,`product_id`,`price`,`is_used`,`created_at`,`true_spec`,`supplier_id`, `print_times`) ";
	sql += " values("+year_month_id+","+company_id+","+product_id+",'"  +t_price+    "',true,'"+created_at+"','"+t_true_spec+"','"+AnsiString(MainForm->ParentId)+"', '0')";
	Cmd->SQL->Clear();
	Cmd->SQL->Add(sql);
	Cmd->Execute();

	Label8->Visible = false;
	edit->Visible = false;
	BitBtn5->Visible = false;
//	Label13->Visible = false;
//	Label14->Visible = false;
//	Edit2->Visible = false;
//	Edit3->Visible = false;
	Panel2->Visible = false;
	will_add->Text = "";
	edit->Text = "";
	message->Caption = will_add->Text.Trim()+"添加成功！";
    InputGrid->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TPrintOrder::InputGridKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{   if(Shift.Contains(ssAlt)){
		AnsiString str="";
		if(Shift.Contains(ssAlt)&&Key==49)
			str="choose^1^^";
		if(Shift.Contains(ssAlt)&&Key==50)
			str="choose^2^^";
		if(Shift.Contains(ssAlt)&&Key==51)
			str="choose^3^^";
		if(Shift.Contains(ssAlt)&&Key==52)
			str="choose^4^^";
		if(Shift.Contains(ssAlt)&&Key==53)
			str="choose^5^^";
		if(Shift.Contains(ssAlt)&&Key==54)
			str="choose^6^^";
		if(Shift.Contains(ssAlt)&&Key==55)
			str="choose^7^^";
		if(Shift.Contains(ssAlt)&&Key==56)
			str="choose^8^^";
		if(Shift.Contains(ssAlt)&&Key==57)
			str="choose^9^^";
		HWND hwnd=FindWindowA(NULL,MainForm->select_panel_name);
		COPYDATASTRUCT myCopyDATA;
		myCopyDATA.cbData=str.Length();
		myCopyDATA.lpData=str.c_str();
		SendMessageA(hwnd,WM_COPYDATA,NULL,(LPARAM)&myCopyDATA);
	}
	if(Shift.Contains(ssCtrl)&&Key==78){
		will_add->SetFocus();
	}
	if(Shift.Contains(ssCtrl)&&Key==81){
		Edit1->SetFocus();
	}
	if(Shift.Contains(ssCtrl)&&Key==82){
    	BtnPrintClick(Sender);
	}
}
//---------------------------------------------------------------------------

void __fastcall TPrintOrder::BitBtn6Click(TObject *Sender)
{
	TfrxReport* re=printORshow();
	if (re==NULL) {
		Label10->Caption = "未保存！";
		return;
	}
	your_input_is_printed_or_previewed = true;
	Label10->Caption = "保存成功！";
}
//---------------------------------------------------------------------------


void __fastcall TPrintOrder::BitBtn8Click(TObject *Sender)
{         //StrToInt("2.789");
	if (Edit1->Text.Trim()=="") {
		ShowMessage("还没有输入参考品项名呢！");
		return;
	}
	TDateTime temp = Date() - 90;
	AnsiString reach_date = temp.DateString();
	AnsiString sql = "";
	sql += " select y_m, company_name, product_name, price, spec from ";
	sql += " ( ";
	sql += " select companies.simple_name as company_name, year_months.val as y_m,";
	sql += " products.chinese_name as product_name, prices.price as price, prices.true_spec as spec ";
	sql += " from ";
	sql += " ( ";
	sql += " SELECT orders.customer_id as customer_id,orders.reach_order_date as reach_order_date, ";
	sql += " order_items.product_id as product_id, order_items.price_id as price_id ";
	sql += " FROM order_items left join orders on orders.id=order_items.order_id ";
	sql += " where orders.reach_order_date > '"+reach_date+"' and orders.supplier_id = "+AnsiString(MainForm->ParentId)+" and (orders.delete_flag is null or orders.delete_flag=0) ";
	sql += " ) T1 left join companies on companies.id=T1.customer_id ";
	sql += " left join products on products.id=T1.product_id ";
	sql += " left join prices on prices.id=T1.price_id ";
	sql += " left join year_months on year_months.id=prices.year_month_id ";	
	sql += " where products.chinese_name like '%"+Edit1->Text.Trim()+"%' and prices.supplier_id = "+AnsiString(MainForm->ParentId)+" and prices.price is not null and prices.price <> 0 ";
	sql += " ) T2 ";
	sql += " group by company_name, product_name, price, spec ";
	sql += " order by y_m desc, price desc ";
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	StringGrid1->RowCount = Qry->RecordCount;
	StringGrid1->Height = StringGrid1->RowCount * 30;
	if (StringGrid1->Height>250) {
    	StringGrid1->Height =250;
	}
	for(unsigned i=0; i< StringGrid1->RowCount; i++,Qry->Next()) {
		StringGrid1->Cells[0][i] = Qry->FieldByName("y_m")->AsString.Trim();
		StringGrid1->Cells[1][i] = Qry->FieldByName("company_name")->AsString.Trim();
		StringGrid1->Cells[2][i] = Qry->FieldByName("product_name")->AsString.Trim();
		StringGrid1->Cells[3][i] = Qry->FieldByName("price")->AsString.Trim();
		StringGrid1->Cells[4][i] = Qry->FieldByName("spec")->AsString.Trim();
	}
}
//---------------------------------------------------------------------------

void __fastcall TPrintOrder::BitBtn9Click(TObject *Sender)
{
	AnsiString sql;
	//frxReport->DesignReport();
	//获得一些id值，比如company_id、store_id

	sql = "SELECT id FROM companies where simple_name = \""+ CompanyName->Text.Trim() +"\"";
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	//单位ID
	company_id = Qry->FieldByName("id")->AsString;

	sql = "SELECT id FROM stores where name = \""+ Store->Text.Trim() +"\"";
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	//门店ID
	store_id = Qry->FieldByName("id")->AsString;

	sql = "SELECT * FROM order_types where supplier_id = "+AnsiString(MainForm->ParentId)+" and name = \""+ OrderType->Text.Trim() +"\" and customer_id = " + company_id;
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	//单据类型ID
	order_type_id = Qry->FieldByName("id")->AsString;

	//到货日期
	reach_order_date = ReachOrderTime->Date.DateString();

	//订货日期
	send_order_date = SendOrderTime->Date.DateString();

	TDateTime temp = Now();
	//打单时间
	created_at = temp.DateTimeString();

	sql = " SELECT id FROM year_months WHERE val = '"+ CurrentMonth +"'";
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	//月份ID
	year_month_id = Qry->FieldByName("id")->AsString;

	//查询要打的单据是否已经存在，存在的话放出，弹出提示框，问是否作废已经打印了的单据
	//选择是，就会作废，选择否，取消作废
	sql = " select * from orders ";
	sql += " WHERE customer_id = "+company_id+" and store_id = "+store_id+" and order_type_id = "+order_type_id+" ";
	sql += " and supplier_id = "+AnsiString(MainForm->ParentId)+" and reach_order_date = '"+reach_order_date+"' ";
    sql += " and (delete_flag is null or delete_flag=0) ";
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	if(Qry->RecordCount>0) {
		if(Application->MessageBox(L"找到了对应您输入的单位、门店、单据类型、送货日期的单据，您确认作废该单据？",L"温馨提示",MB_YESNO)!=6)
			return;
		else {
        	sql = " update orders set delete_flag = 1 ";
			sql += " WHERE customer_id = "+company_id+" and store_id = "+store_id+" and order_type_id = "+order_type_id+" ";
			sql += " and supplier_id = "+AnsiString(MainForm->ParentId)+" and reach_order_date = '"+reach_order_date+"' ";
            sql += " and (delete_flag is null or delete_flag=0) ";
			Cmd->SQL->Clear();
			Cmd->SQL->Add(sql);
			Cmd->Execute();
        }
	} else {
		ShowMessage(CompanyName->Text.Trim()+"->"+Store->Text.Trim()+"->"+OrderType->Text.Trim()+"->"+reach_order_date+"->还没有打印过！");
    }
}
//---------------------------------------------------------------------------
//去皮番茄1桶，切片牛肉2斤，意大利直面3包，螺丝面2包，盒装豆腐2盒，薄披萨底9寸2包，绿叶1斤，红叶0.5斤，苦叶0.5斤，罗勒叶0.2斤，黄节瓜2根，彩椒各2个，香菇0.5斤，香菜0.2斤，
//---------------------------------------------------------------------------


void __fastcall TPrintOrder::Button3Click(TObject *Sender)
{
	if( Memo1->Lines->Count == 0 || Memo1->Lines->Strings[0].Trim() == "" ) {
		ShowMessage("请先填写订货微信息。");
		return;
	}
	if(CompanyName->Text.Trim()==""){
		ShowMessage("请先选择客户再来操作。");
		return;
	}
	AnsiString t_text = Memo1->Text;
	Memo1->Lines->Clear();
	TStringList* psl = new TStringList;
	t_text = StringReplace(t_text, "，", ",", TReplaceFlags() << rfReplaceAll);
	psl->DelimitedText = t_text;
	psl->Delimiter = ',';
	for(int i=0;i<psl->Count;i++){
		if (psl->Strings[i].Trim() == "") {
            continue;
		}
		InputGrid->Cells[2][i+1] = psl->Strings[i];
	}
	delete psl;

}
//---------------------------------------------------------------------------

void __fastcall TPrintOrder::Button4Click(TObject *Sender)
{
	AnsiString basic_number_string = "0123456789.";
	AnsiString Str = "";
	for(unsigned i=1;i<=InputGrid->RowCount;i++){
		if(InputGrid->Cells[2][i].Trim()=="") continue;
		AnsiString temp = InputGrid->Cells[2][i].Trim();
		if(basic_number_string.Pos(temp.SubString(1,1)) == 0)
		{
			int p = temp.Length();
			AnsiString sub_string = temp.SubString(p,1);

			while( basic_number_string.Pos(sub_string) == 0 && p >= 1){
				  p = p - 1;
				  sub_string = temp.SubString(p,1);
			}
			while(basic_number_string.Pos(sub_string) != 0 && p >= 1){
				p = p - 1;
				sub_string = temp.SubString(p,1);
			}
			if (p==0) {
				Str = temp;
			} else {
				Str = AnsiString(temp.SubString(1,p));
				InputGrid->Cells[3][i] = temp.SubString(p+1,temp.Length()-p);
			}
		} else {
			int p = 1;
			AnsiString sub_string = temp.SubString(p,1);
			while( basic_number_string.Pos(sub_string) != 0 && p <= temp.Length() ){
				p = p + 1;
				sub_string = temp.SubString(p,1);
			}
			if (p==temp.Length()+1) {
            	InputGrid->Cells[3][i] = temp;
			} else {
            	InputGrid->Cells[3][i] = temp.SubString(1,p+1);
				Str = AnsiString(temp.SubString(p+2, temp.Length()-p-1));
			}

		}
		Str = Str.Trim();
		if (Str != "") {
        	InputGrid->Cells[2][i] = Str;
			Qry->Close();
			Qry->SQL->Clear();
			AnsiString StrSQL = " SELECT products.simple_abc as simple_abc, prices.* ";
			StrSQL += " FROM prices ";
			StrSQL += " LEFT JOIN products ON products.id = prices.product_id ";
			StrSQL += " LEFT JOIN year_months ON prices.year_month_id = year_months.id ";
			StrSQL += " LEFT JOIN companies ON prices.customer_id = companies.id ";
			StrSQL += " WHERE 1 = 1 and products.is_valid = 1 AND prices.is_used = 1 ";
			StrSQL += " AND prices.supplier_id = " + AnsiString(MainForm->ParentId);
			StrSQL += " AND companies.simple_name = \""+ CompanyName->Text.Trim() +"\" ";
			StrSQL += " AND year_months.val = \""+ CurrentMonth +"\" ";
			StrSQL += " AND products.chinese_name = \"" + Str + "\" ";
			Qry->SQL->Add(StrSQL);
			Qry->Open();
			if(Qry->RecordCount == 0){
				//ShowMessage("【"+Str + "】在价格表中不存在。");
			} else if(Qry->RecordCount == 1){
				Qry->First();
				InputGrid->Cells[1][i] = Qry->FieldByName("simple_abc")->AsString;
				InputGrid->Cells[5][i] = Qry->FieldByName("true_spec")->AsString;
				AnsiString temp_price = Qry->FieldByName("price")->AsString;
				InputGrid->Cells[6][i] = temp_price==AnsiString("0")?AnsiString(""):temp_price;
			} else {
				ShowMessage("价格表中 " + Str +" 这个品项重复！");
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TPrintOrder::Button5Click(TObject *Sender)
{
	for(unsigned i=1;i<=InputGrid->RowCount;i++){
		if(InputGrid->Cells[3][i].Trim() == "") continue;
    	InputGrid->Cells[4][i] = InputGrid->Cells[3][i];
	}
}
//---------------------------------------------------------------------------

void __fastcall TPrintOrder::Edit1KeyPress(TObject *Sender, System::WideChar &Key)
          
{
	if(Key==VK_RETURN){	
		BitBtn8Click(Sender);
		InputGrid->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TPrintOrder::will_addKeyPress(TObject *Sender, System::WideChar &Key)
          
{
	if(Key==VK_RETURN){	
		BitBtn4Click(Sender);
		Edit1->Text = will_add->Text;
		BitBtn8Click(Sender);
	}	
}
//---------------------------------------------------------------------------


void __fastcall TPrintOrder::will_addKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Shift.Contains(ssCtrl)&&Key==70){
		InputGrid->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall TPrintOrder::CompanyNameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key>=48&&Key<=57){
		// alt + 0-9     1--10
		// ctrl + 0-9    11--20
		// shift + 0-9   21--30
		// 选择对应的选项
		AnsiString str="";
		if(Shift.Contains(ssAlt)&&Key==49)
			str="choose^1^^";
		if(Shift.Contains(ssAlt)&&Key==50)
			str="choose^2^^";
		if(Shift.Contains(ssAlt)&&Key==51)
			str="choose^3^^";
		if(Shift.Contains(ssAlt)&&Key==52)
			str="choose^4^^";
		if(Shift.Contains(ssAlt)&&Key==53)
			str="choose^5^^";
		if(Shift.Contains(ssAlt)&&Key==54)
			str="choose^6^^";
		if(Shift.Contains(ssAlt)&&Key==55)
			str="choose^7^^";
		if(Shift.Contains(ssAlt)&&Key==56)
			str="choose^8^^";
		if(Shift.Contains(ssAlt)&&Key==57)
			str="choose^9^^";
		if(Shift.Contains(ssAlt)&&Key==48)
			str="choose^10^^";
		if(Shift.Contains(ssCtrl)&&Key==49)
			str="choose^11^^";
		if(Shift.Contains(ssCtrl)&&Key==50)
			str="choose^12^^";
		if(Shift.Contains(ssCtrl)&&Key==51)
			str="choose^13^^";
		if(Shift.Contains(ssCtrl)&&Key==52)
			str="choose^14^^";
		if(Shift.Contains(ssCtrl)&&Key==53)
			str="choose^15^^";
		if(Shift.Contains(ssCtrl)&&Key==54)
			str="choose^16^^";
		if(Shift.Contains(ssCtrl)&&Key==55)
			str="choose^17^^";
		if(Shift.Contains(ssCtrl)&&Key==56)
			str="choose^18^^";
		if(Shift.Contains(ssCtrl)&&Key==57)
			str="choose^19^^";
		if(Shift.Contains(ssCtrl)&&Key==48)
			str="choose^20^^";
		if(Shift.Contains(ssShift)&&Key==49)
			str="choose^21^^";
		if(Shift.Contains(ssShift)&&Key==50)
			str="choose^22^^";
		if(Shift.Contains(ssShift)&&Key==51)
			str="choose^23^^";
		if(Shift.Contains(ssShift)&&Key==52)
			str="choose^24^^";
		if(Shift.Contains(ssShift)&&Key==53)
			str="choose^25^^";
		if(Shift.Contains(ssShift)&&Key==54)
			str="choose^26^^";
		if(Shift.Contains(ssShift)&&Key==55)
			str="choose^27^^";
		if(Shift.Contains(ssShift)&&Key==56)
			str="choose^28^^";
		if(Shift.Contains(ssShift)&&Key==57)
			str="choose^29^^";
		if(Shift.Contains(ssShift)&&Key==48)
			str="choose^30^^";
		HWND hwnd=FindWindowA(NULL,MainForm->select_panel_name);
		COPYDATASTRUCT myCopyDATA;
		myCopyDATA.cbData=str.Length();
		myCopyDATA.lpData=str.c_str();
		SendMessageA(hwnd,WM_COPYDATA,NULL,(LPARAM)&myCopyDATA);
	} else if(!Shift.Contains(ssShift)&&!Shift.Contains(ssCtrl)&&!Shift.Contains(ssAlt)&&Key==112){
		// F1 聚焦单位输入框&列出单位
		CompanyNameClick(Sender);
		CompanyName->SetFocus();
	} else if (!Shift.Contains(ssShift)&&!Shift.Contains(ssCtrl)&&!Shift.Contains(ssAlt)&&Key == 113 ) {
		// F2 聚焦门店输入框&列出门店
		StoreClick(Sender);
		Store->SetFocus();
	} else if (!Shift.Contains(ssShift)&&!Shift.Contains(ssCtrl)&&!Shift.Contains(ssAlt)&&Key == 114 ) {
		// F3 聚焦单据类型输入&列出单据类型
		OrderTypeClick(Sender);
		OrderType->SetFocus();
	} else if (!Shift.Contains(ssShift)&&!Shift.Contains(ssCtrl)&&!Shift.Contains(ssAlt)&&Key == 116 ) {
		// F5 填充上一次单位选择情况
		CompanyName->Text = temp_customer_name;
		Store->Text = temp_store_name;
		OrderType->Text = temp_order_type;
	} else if(Shift.Contains(ssCtrl)&&Key==78){
	    // ctrl + N 聚焦增加新品项输入框
		will_add->SetFocus();
	} else if(Shift.Contains(ssCtrl)&&Key==81){
	    // ctrl + Q 聚焦查询输入框
		Edit1->SetFocus();
	} else if(Shift.Contains(ssCtrl)&&Key==82){
	    // ctrl + R 打印
		BtnPrintClick(Sender);
	} else if(Shift.Contains(ssCtrl)&&Key==70){
		// ctrl + F 聚焦Grid
		InputGrid->SetFocus();
	} else if(Shift.Contains(ssCtrl)&&Key==83){
		// ctrl + S 保存
		BitBtn6Click(Sender);
	} else if(Shift.Contains(ssCtrl)&&Key==80){
		// ctrl + P 预览
		BitBtn1Click(Sender);
	} else if(Shift.Contains(ssCtrl)&&Key==79){
		// ctrl + O 清空
		BitBtn3Click(Sender);
	} else if(Shift.Contains(ssCtrl)&&Key==74){
		// ctrl + J 聚焦订货单粘贴框
		Memo1->SetFocus();
	} else if(Shift.Contains(ssCtrl)&&Key==75){
		// ctrl + K 扔进表单
		Button3Click(Sender);
	} else if(Shift.Contains(ssCtrl)&&Key==76){
		// ctrl + L 解析
		Button4Click(Sender);
	} else if(Shift.Contains(ssCtrl)&&Key==186){
		// ctrl + ; 扔进表单&解析
		Button3Click(Sender);
		Button4Click(Sender);
	} else if(Shift.Contains(ssCtrl)&&Key==171){
		// ctrl + G 获取已打印
		BitBtn2Click(Sender);
	} else if(Shift.Contains(ssCtrl)&&Key==72){
		// ctrl + H 弹出帮助
		AnsiString help = "alt + 0-9     1--10 \n";
		help += "ctrl + 0-9    11--20  \n";
		help += "shift + 0-9   21--30 \n";
		help += "选择对应的选项 \n";
		help += "F1 聚焦单位输入框&列出单位 \n";
		help += "F2 聚焦门店输入框&列出门店 \n";
		help += "F3 聚焦单据类型输入&列出单据类型 \n";
		help += "F5 填充上一次单位选择情况 \n";
		help += "ctrl + N 聚焦增加新品项输入框 \n";
		help += "ctrl + Q 聚焦查询输入框 \n";
		help += "ctrl + R 打印 \n";
		help += "ctrl + F 聚焦Grid \n";
		help += "ctrl + S 保存 \n";
		help += "ctrl + P 预览 \n";
		help += "ctrl + O 清空 \n";
		help += "ctrl + J 聚焦订货单粘贴框 \n";
		help += "ctrl + K 扔进表单 \n";
		help += "ctrl + L 解析 \n";
		help += "ctrl + ; 扔进表单&解析 \n";
		help += "ctrl + G 获取已打印/保存 \n";
		ShowMessage(help);
	} 
}
//---------------------------------------------------------------------------

void __fastcall TPrintOrder::StoreKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	CompanyNameKeyDown(Sender,Key,Shift);
}
//---------------------------------------------------------------------------

void __fastcall TPrintOrder::OrderTypeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	CompanyNameKeyDown(Sender,Key,Shift);
}
//---------------------------------------------------------------------------



