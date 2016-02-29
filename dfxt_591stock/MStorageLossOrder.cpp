//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MStorageLossOrder.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "MemDS"
#pragma link "MyAccess"
#pragma resource "*.dfm"
TStorageLossOrder *StorageLossOrder;
//---------------------------------------------------------------------------
__fastcall TStorageLossOrder::TStorageLossOrder(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TStorageLossOrder::FormCreate(TObject *Sender)
{
	TypeDetail = -1;
    SellerId = 0;

	//默认日期为当天
	DateTimePicker1->Date = Now();

	//StringGrid1
	StorageLossStringGrid->Cells[1][0]="简写";
	StorageLossStringGrid->Cells[2][0]="名称";
	StorageLossStringGrid->Cells[3][0]="损耗量";
	StorageLossStringGrid->Cells[4][0]="规格";
	for(int i=1;i<StorageLossStringGrid->RowCount;i++) {
		StorageLossStringGrid->Cells[0][i]=i;
	}
	StorageLossStringGrid->ColWidths[1] = 40;

	//查询数据库，获取仓库ID：storage_id
	AnsiString user_id = MainForm->OperatorId;
	AnsiString sql = "";
	sql = "select store_id from users where id = " + user_id;
	Qry->Close();
	Qry->SQL->Clear();
	Qry->SQL->Add(sql);
	Qry->Open();
	Qry->First();
	int store_id = Qry->FieldByName("store_id")->AsInteger;
	if(store_id == 0){
		ShowMessage("当前登录用户没有权限管理任何一个仓库，请联系管理员！");

	} else {
		sql = "select id from storages where store_id = " + AnsiString(store_id);
		Qry->Close();
		Qry->SQL->Clear();
		Qry->SQL->Add(sql);
		Qry->Open();
		if (Qry->RecordCount == 0) {
			ShowMessage("当前登录用户可以管理的仓库不存在，请联系管理员！");

		} else {
			Qry->First();
			StorageId = Qry->FieldByName("id")->AsInteger;
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TStorageLossOrder::FormClose(TObject *Sender, TCloseAction &Action)

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

void __fastcall TStorageLossOrder::Timer1Timer(TObject *Sender)
{
	HWND hwnd=FindWindowA(NULL,MainForm->select_panel_name);
	AnsiString str="pos^"+AnsiString(Left-300)+"^^"+AnsiString(Top+40);
	COPYDATASTRUCT myCopyDATA;
	myCopyDATA.cbData = str.Length();
	myCopyDATA.lpData = str.c_str();
	SendMessageA(hwnd,WM_COPYDATA,NULL,(LPARAM)&myCopyDATA);
}
//---------------------------------------------------------------------------

void __fastcall TStorageLossOrder::SLSellerNameChange(TObject *Sender)
{
	if(SLSellerName->Text.Trim() == "" || LossType->ItemIndex == -1){
		StorageLossStringGrid->Enabled = false;
		BitBtn1->Enabled = false;
	} else {
		StorageLossStringGrid->Enabled = true;
		BitBtn1->Enabled = true;
	}
	Qry->Close();
	Qry->SQL->Clear();
	AnsiString sql = "select id from sellers where (delete_flag is null or delete_flag = 0) and supplier_id = " + AnsiString(MainForm->ParentId) + " and name = '" + SLSellerName->Text.Trim() + "'";

	Qry->SQL->Add(sql);
	Qry->Open();
	if (Qry->RecordCount == 0) {
		ShowMessage("当前所填的采购来源不存在，请确认是否填错。");
	} else {
		Qry->First();
		SellerId = Qry->FieldByName("id")->AsInteger;
	}
}
//---------------------------------------------------------------------------

void __fastcall TStorageLossOrder::SLSellerNameClick(TObject *Sender)
{
	HWND hwnd=FindWindowA(NULL,MainForm->select_panel_name);
	AnsiString str="sql^ SELECT name as FName FROM sellers where 1=1";
	str += " and supplier_id = ";
	str += MainForm->ParentId;
	str += " and (delete_flag = 0 or delete_flag is null) ^^";
	COPYDATASTRUCT myCopyDATA;
	myCopyDATA.cbData = str.Length();
	myCopyDATA.lpData = str.c_str();
	SendMessageA(hwnd,WM_COPYDATA,NULL,(LPARAM)&myCopyDATA);
}
//---------------------------------------------------------------------------

void __fastcall TStorageLossOrder::StorageLossStringGridSelectCell(TObject *Sender,
          int ACol, int ARow, bool &CanSelect)
{
	if (ACol == 2) {
		HWND hwnd=FindWindowA(NULL,MainForm->select_panel_name);
		AnsiString str="sql^ ";
		COPYDATASTRUCT myCopyDATA;
		if(StorageLossStringGrid->Cells[1][ARow].Trim() != "") {
			str += " select products.chinese_name as FName";
			str += " from products";
			str += " left join purchase_prices on purchase_prices.product_id = products.id";
			str += " where 1 = 1";
			str += " and purchase_prices.seller_id = " + AnsiString(SellerId);
			str += " and purchase_prices.is_used = 1";
			str += " and purchase_prices.supplier_id = " + AnsiString(MainForm->ParentId);
			str += " and products.simple_abc like \"%" + StorageLossStringGrid->Cells[1][ARow].Trim() + "%\" ";
			str += " order by purchase_prices.print_times desc ";
		} else {
			str += " select '简写没有输入!' as FName";
		}
		str += " ^^";

		myCopyDATA.cbData=str.Length();
        myCopyDATA.lpData=str.c_str();
		SendMessageA(hwnd,WM_COPYDATA,NULL,(LPARAM)&myCopyDATA);
	}
}
//---------------------------------------------------------------------------


void __fastcall TStorageLossOrder::LossTypeChange(TObject *Sender)
{
	if(LossType->ItemIndex==0) {
		TypeDetail = 3;
	} else if (LossType->ItemIndex==1) {
		TypeDetail = 4;
	}
	if(SLSellerName->Text.Trim() == "" || LossType->ItemIndex == -1){
		StorageLossStringGrid->Enabled = false;
		BitBtn1->Enabled = false;
	} else {
		StorageLossStringGrid->Enabled = true;
		BitBtn1->Enabled = true;
	}
}
//---------------------------------------------------------------------------


void __fastcall TStorageLossOrder::BitBtn1Click(TObject *Sender)
{
	try
	{
		AnsiString sql = "";
		//开始事务
		Cmd->Connection->StartTransaction();

		if(StorageId == 0){
			ShowMessage("当前用户没有权限操作任何仓库，故不能进行相关的进货操作。");
			sql = "Insert into `xxx`";
			Cmd->SQL->Clear();
			Cmd->SQL->Add(sql);
			Cmd->Execute();
		}
		//生成purchase_orders
//		sql = "INSERT INTO `purchase_orders` (`storage_id`, `purchase_date`, `user_id`, `delete_flag`, `created_at`, `updated_at`, `supplier_id`, `seller_id`) ";
//		sql += " VALUES ( ";
//		sql += AnsiString(StorageId) + ", ";
//		sql += " '" + DateTimePicker1->Date.DateString() + "', ";
//		sql += AnsiString(MainForm->OperatorId) + ", ";
//		sql += " 0, ";
//		sql += " '" + Now().DateString() + "', ";
//		sql += " '" + Now().DateString() + "', ";
//		sql += AnsiString(MainForm->ParentId) + ", ";
//		sql += AnsiString(SellerId) + ");";
//		Cmd->SQL->Clear();
//		Cmd->SQL->Add(sql);
//		Cmd->Execute();

//		AnsiString purchase_order_id = Cmd->InsertId;
		//生成purchase_order_items
		for(unsigned i=1;i<=StorageLossStringGrid->RowCount;i++){
			if(StorageLossStringGrid->Cells[2][i].Trim()=="") continue;
			AnsiString current_simple_abc = StorageLossStringGrid->Cells[1][i].Trim();
			AnsiString current_chinese_name = StorageLossStringGrid->Cells[2][i].Trim();
			AnsiString current_real_weight = StorageLossStringGrid->Cells[3][i].Trim();
			AnsiString current_ture_spec = StorageLossStringGrid->Cells[4][i].Trim();
			float t_real_weight;
			if(current_real_weight == "") {
				ShowMessage("第"+AnsiString(i)+"行的到货量必须填写");
				sql = "Insert into `xxx`";
				Cmd->SQL->Clear();
				Cmd->SQL->Add(sql);
				Cmd->Execute();
			}

			if(!TryStrToFloat(current_real_weight, t_real_weight) ) {
				ShowMessage("第"+AnsiString(i)+"行的到货量"+current_real_weight+"，请修改成数值型。");
				sql = "Insert into `xxx`";
				Cmd->SQL->Clear();
				Cmd->SQL->Add(sql);
				Cmd->Execute();
			}

			//*获得product_id
			AnsiString product_id;
			AnsiString general_product_id;
			sql = "SELECT id, general_product_id FROM products WHERE chinese_name = '"+ StorageLossStringGrid->Cells[2][i] +"' and supplier_id = "+ AnsiString(MainForm->ParentId);
			Qry->Close();
			Qry->SQL->Clear();
			Qry->SQL->Add(sql);
			Qry->Open();
			if(Qry->RecordCount==0) {
				ShowMessage("第"+AnsiString(i)+"行的"+StorageLossStringGrid->Cells[2][i]+"不在产品表中，是你手动添加的吧！");
				sql = "Insert into `xxx`";
				Cmd->SQL->Clear();
				Cmd->SQL->Add(sql);
				Cmd->Execute();
			}
			Qry->Last();
			//产品ID
			product_id = Qry->FieldByName("id")->AsString;
			general_product_id = Qry->FieldByName("general_product_id")->AsInteger;
			if(general_product_id == 0){
				ShowMessage("第"+AnsiString(i)+"行的"+StorageLossStringGrid->Cells[2][i]+"还没有关联任何通用产品，请做关联！");
				sql = "Insert into `xxx`";
				Cmd->SQL->Clear();
				Cmd->SQL->Add(sql);
				Cmd->Execute();
			}

			//*获得purchase_price_id 、 ratio
			AnsiString purchase_price_id;
			AnsiString str_ratio;
			float ratio;
			sql = "select id, ratio from purchase_prices where 1 = 1 ";
			sql += " and supplier_id = " + AnsiString(MainForm->ParentId);
			sql += " and seller_id = " + AnsiString(SellerId);
			sql += " and is_used = 1 ";
			sql += " and product_id = " + AnsiString(product_id);
			Qry->Close();
			Qry->SQL->Clear();
			Qry->SQL->Add(sql);
			Qry->Open();
			if(Qry->RecordCount==0){
				ShowMessage("第"+AnsiString(i)+"行的"+StorageLossStringGrid->Cells[2][i]+"不在价格表中");
				sql = "Insert into `xxx`";
				Cmd->SQL->Clear();
				Cmd->SQL->Add(sql);
				Cmd->Execute();
			} else {
			if(Qry->RecordCount>1){
				ShowMessage("第"+AnsiString(i)+"行的"+StorageLossStringGrid->Cells[2][i]+"在价格表中找到2个或2个以上个价格，请改正。");
				sql = "Insert into `xxx`";
				Cmd->SQL->Clear();
				Cmd->SQL->Add(sql);
				Cmd->Execute();
			} else {
				Qry->First();
				purchase_price_id = Qry->FieldByName("id")->AsString;
				str_ratio = Qry->FieldByName("ratio")->AsString;
				if(!TryStrToFloat(str_ratio, ratio)) {
					ShowMessage("第"+AnsiString(i)+"行的"+StorageLossStringGrid->Cells[2][i]+"的进货单位与库存单位换算比值不正确，请修改后，再来此操作。");
					sql = "Insert into `xxx`";
					Cmd->SQL->Clear();
					Cmd->SQL->Add(sql);
					Cmd->Execute();
				}
			}
			}
//			sql = " INSERT INTO `purchase_order_items` (`purchase_order_id`, `product_id`, `real_weight`, `price`, `money`, `created_at`, `updated_at`, `plan_weight`, `purchase_price_id`)";
//			sql += " VALUES ( ";
//			sql += AnsiString(purchase_order_id) + ", ";
//			sql += AnsiString(product_id) + ", ";
//			sql += AnsiString(current_real_weight) + ", ";
//			sql += AnsiString(current_purchase_price) + ", ";
//			float item_money = t_real_weight*t_purchase_price;
//			sql += AnsiString(item_money) + ", ";
//			sql += "'" + AnsiString(Now().DateString()) + "', ";
//			sql += "'" + AnsiString(Now().DateString()) + "', ";
//			sql += AnsiString(current_plan_weight) + ", ";
//			sql += AnsiString(purchase_price_id) + "); ";
//			Cmd->SQL->Clear();
//			Cmd->SQL->Add(sql);
//			Cmd->Execute();
//			AnsiString item_id = Cmd->InsertId;

			//增加库存进出明细
			sql = " INSERT INTO `order_details` (`supplier_id`, `related_company_id`, `detail_type`, `detail_date`, `product_id`, `real_weight`, `delete_flag`, `created_at`, `updated_at`) ";
			sql += " VALUES ";
			sql += " (";
			sql += AnsiString(MainForm->ParentId) + ", ";
			sql += AnsiString(SellerId) + ", ";
			sql += AnsiString(TypeDetail) + ", ";
			sql += "'" + DateTimePicker1->Date.DateString() + "', ";
			sql += AnsiString(product_id) + ", ";
			sql += AnsiString(current_real_weight) + ", ";
			sql += AnsiString(0) + ", ";
			sql += "'" + Now().DateString() + "', ";
			sql += "'" + Now().DateString() + "'); ";

			Cmd->SQL->Clear();
			Cmd->SQL->Add(sql);
			Cmd->Execute();

			//更新库存
			sql = " select id, real_weight from stocks where general_product_id = " + AnsiString(general_product_id);
			sql += " and supplier_id = " + AnsiString(MainForm->ParentId);
			sql += " and storage_id = " + AnsiString(StorageId);
			//ShowMessage(sql);
			Qry->Close();
			Qry->SQL->Clear();
			Qry->SQL->Add(sql);
			Qry->Open();
			if(Qry->RecordCount >= 2){
				ShowMessage("第"+AnsiString(i)+"行的"+StorageLossStringGrid->Cells[2][i]+"查找到的库存大于等于2条记录，请检查更正！");
				sql = "Insert into `xxx`";
				Cmd->SQL->Clear();
				Cmd->SQL->Add(sql);
				Cmd->Execute();
			}
			AnsiString stock_id = "";
			AnsiString stock_real_weight = "";

			if(Qry->RecordCount == 0) {
				//暂无该产品的库存记录，插入一条
                sql = " INSERT INTO `stocks` ( `general_product_id`, `storage_id`, `real_weight`, `min_weight`, `last_purchase_price`, `created_at`, `updated_at`, `supplier_id`)";
				sql += " VALUES( ";
				sql += AnsiString(general_product_id) + ", ";
				sql += AnsiString(StorageId) + ", ";
				sql += AnsiString(0) + ", ";
				sql += " NULL, ";
				sql += " NUll, ";
				sql += "'" + Now().DateString() + "', ";
				sql += "'" + Now().DateString() + "', ";
				sql += AnsiString(MainForm->ParentId) + ");";
				Cmd->SQL->Clear();
				Cmd->SQL->Add(sql);
				Cmd->Execute();
				stock_id = Cmd->InsertId;
				stock_real_weight = "0";
			}
			if(Qry->RecordCount == 1){
				Qry->First();
				stock_id = Qry->FieldByName("id")->AsString;
				stock_real_weight = Qry->FieldByName("real_weight")->AsString;
			}
			float temp_stock_real_weight = 0.0;
			float weight_after_come_in = 0.0;

			if(TryStrToFloat(stock_real_weight, temp_stock_real_weight)){
				weight_after_come_in = temp_stock_real_weight - ratio * t_real_weight;
			} else {
				ShowMessage("第"+AnsiString(i)+"行的"+StorageLossStringGrid->Cells[2][i]+"查找到的库存数值有误！");
				sql = "Insert into `xxx`";
				Cmd->SQL->Clear();
				Cmd->SQL->Add(sql);
				Cmd->Execute();
			}

			sql = " update stocks set real_weight = " + AnsiString(weight_after_come_in);
			sql += " where id = " + AnsiString(stock_id);
			Cmd->SQL->Clear();
			Cmd->SQL->Add(sql);
			Cmd->Execute();

		}


		//提交事务
		Cmd->Connection->Commit();
		//SLSellerName->Text = "";
		for(int i=1;i<=StorageLossStringGrid->ColCount;i++)
		{
			for(int j=1;j<=StorageLossStringGrid->RowCount;j++)
			{
				StorageLossStringGrid->Cells[i][j]="";
			}
		}
		ShowMessage("提交成功。");
	}
	catch(...)
	{
		//回滚事务
		Cmd->Connection->Rollback();
	}

}
//---------------------------------------------------------------------------

