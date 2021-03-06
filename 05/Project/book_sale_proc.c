#include "book_sale_proc.h"
#define FIELD_NUM 7								//窗体中信息表可控制的字段数
#define PRIMARY "salecode"						//主键
#define TB_NAME "tb_book_sale"					//信息表名
#define	EDIT_COUNT 3								//连续EDIT控件数量
#define BASE_TB_NAME  "tb_base_desk_info"			//外键表
#define	INFO_TB_BOOK_NAME  "tb_book_info"				//外键表
#define BOOK_FK		"barcode"
#define SUB_TITLES_BOOK_COUNT	8	
#define RESULT_TB_NAME "tb_stock_info"			//结果表
#define RESULT_TB_FIELD_NUM 2						//结果表条件字段个数
#define RESULT_TB_BOOK_CONDITION	"barcode"		//结果表更新的条件属性
#define RESULT_TB_STORE_CONDITION	"store"			//结果表更新的条件属性	
#define RESULT_TB_TARGET		"stock"			//结果表更新的目标属性
BOOL CALLBACK Book_Sale_Proc(HWND hDlg, UINT message,WPARAM wParam, LPARAM lParam)
{
	char titles[FIELD_NUM][TITLE_LENTH_MAX] = {"操作员","条形码","柜台","顾客姓名","数量","日期","实付金额"};
	char sub_book_titles[SUB_TITLES_BOOK_COUNT][TITLE_LENTH_MAX] = {"条形码","图书名称","助记码","作者","出版社","价格","备注","种类"};
	HWND hView = GetDlgItem(hDlg,IDC_LIST_VIEW);
	static HWND bookSubView;
	ColumnMessage cms[FIELD_NUM];
	char values[VALUE_LENTH_MAX*FIELD_NUM+FIELD_NUM-1];					 //inser语句中的值,数组大小为：值总长度和逗号数量加和的最大值
	char fields[FIELD_LENTH_MAX*FIELD_NUM+FIELD_NUM-1];					 //inser语句中的字段,数组大小为：字段总长度和逗号数量加和的最大值
	int selIndex;														 //控件当前被选中的项
	int i;																 //迭代器
	//	int updateFlag;														//更新标识，当没有参数需要更新时，flag为0
	char sets[(VALUE_LENTH_MAX+FIELD_LENTH_MAX)*(FIELD_NUM)+(FIELD_NUM-1)*2+1] = "\0";		 //Update语句中SET的内容，数组大小为：值和字段的总长度加上逗号、加号的数量
	LPNMHDR pNmhdr;														//NMHDR表示WM_NOTIFY消息内容,LPNMHDR则表示指向它的指针类型
	char temp[VALUE_LENTH_MAX];											//设置EDIT文字时所用的字符缓冲
	SYSTEMTIME   systime;												//系统时间结构体
	double rebate;														//折扣
	double pay;															//实
	char sql[SQL_LENTH_MAX];
	_int64 nums;

	switch (message)						
	{
	case   WM_INITDIALOG : 
		InitCommonControls();	
		SendMessage(hView,LVM_SETEXTENDEDLISTVIEWSTYLE,0,LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FLATSB);
		InitListViewColumns(hView,titles,FIELD_NUM );
		/*初始化下拉条*/
		sprintf(sql,"select * from %s",BASE_TB_NAME);
		mysql_query(&mysql,sql);
		if(mysql_errno(&mysql))
		{
			MessageBoxEx(GetParent(hView),"操作错误","提示",MB_ICONERROR|MB_TOPMOST,0);
			return 0;
		}
		result = mysql_store_result(&mysql);	
		nums = mysql_num_rows(result);
		for(i=0;i<nums;i++)
		{
			row = mysql_fetch_row(result);
			SendMessage(GetDlgItem(hDlg,IDC_COMBO_DESK),CB_ADDSTRING,0,(LPARAM)row[0]);
		}
		mysql_free_result(result);
		/*初始化折扣*/
		SetWindowText(GetDlgItem(hDlg,IDC_SALE_REBATE),"1.00");
		/*初始化辅助窗口*/
		CreateSubViewProc(hDlg,&bookSubView,"图书",sub_book_titles,SUB_TITLES_BOOK_COUNT,0);
		/*初始化操作员名称*/
		SetWindowText(GetDlgItem(hDlg,IDC_DISEDIT_OPERATOR),g_operator);
		return TRUE ;
	case   WM_COMMAND :
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON_ADD:
			sprintf(cms[0].fieldName,"operator");
			sprintf(cms[1].fieldName,"barcode");
			sprintf(cms[2].fieldName,"desk");
			sprintf(cms[3].fieldName,"customer");
			sprintf(cms[4].fieldName,"count");
			sprintf(cms[5].fieldName,"date");
			sprintf(cms[6].fieldName,"pay");
			for(i=0;i<FIELD_NUM;i++)
			{
				cms[i].type = DB_CHAR;
			}
			cms[4].type = DB_INT;
			cms[6].type = DB_INT;
			GetDlgItemText(hDlg,IDC_DISEDIT_OPERATOR,cms[0].value,VALUE_LENTH_MAX);
			GetDlgItemText(hDlg,IDC_SALE_BARCODE,cms[1].value,VALUE_LENTH_MAX);
			if(strlen(cms[1].value)<1)
			{
				MessageBoxEx(hDlg,"请输入条形码","提示",MB_ICONHAND|MB_TOPMOST,0);
				return 0;
			}
			/*获取柜台*/
			selIndex = SendMessage(GetDlgItem(hDlg,IDC_COMBO_DESK),CB_GETCURSEL,0,0);
			if(selIndex == -1)
			{
				MessageBoxEx(hDlg,"请选择柜台","提示",MB_ICONHAND|MB_TOPMOST,0);
				return 0;
			}
			SendMessage(GetDlgItem(hDlg,IDC_COMBO_DESK),CB_GETLBTEXT,selIndex,(LPARAM)cms[2].value);
			GetDlgItemText(hDlg,IDC_SALE_CUSTOMER,cms[3].value,VALUE_LENTH_MAX);
			 /*获取数量*/
			GetDlgItemText(hDlg,IDC_SALE_COUNT,cms[4].value,VALUE_LENTH_MAX);
			if(strlen(cms[4].value)<1)
			{
				MessageBoxEx(hDlg,"请输入数量","提示",MB_ICONHAND|MB_TOPMOST,0);
				return 0;
			}
			/*获取的系统时间*/
			GetSystemTime(&systime);
			sprintf(cms[5].value,"%d/%d/%d %d:%d:%d",systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute,systime.wSecond);  	
			/*通过数量、折扣、单价获取实付金额*/
			GetDlgItemText(hDlg,IDC_SALE_REBATE,temp,VALUE_LENTH_MAX);
			if(strlen(temp)<1)
			{
				MessageBoxEx(hDlg,"请输入折扣","提示",MB_ICONHAND|MB_TOPMOST,0);
				return 0;
			}
			rebate = atof(temp);
			if((int)(rebate*10)<3)
			{
				MessageBoxEx(hDlg,"折扣过低","提示",MB_ICONHAND|MB_TOPMOST,0);
				return 0;
			}
			if((int)(rebate*10)>10)
			{
				MessageBoxEx(hDlg,"折扣不能超过1","提示",MB_ICONHAND|MB_TOPMOST,0);
				return 0;
			}
			sprintf(sql,"select price from %s where %s='%s'",INFO_TB_BOOK_NAME,BOOK_FK,cms[1].value);
			mysql_query(&mysql,sql);
			result = mysql_store_result(&mysql);
			if(mysql_num_rows(result)==0)
			{
				MessageBoxEx(hDlg,"条形码输入有误","提示",MB_ICONHAND|MB_TOPMOST,0);
				return 0;
			}
			row = mysql_fetch_row(result);
			pay =atof(row[0])*atof(cms[4].value);
			sprintf(temp,"%3.2f",pay);
			SetDlgItemText(hDlg,IDC_SUMMONEY,temp);
			pay = pay*rebate;
			mysql_free_result(result);
			sprintf(cms[6].value,"%3.2f",pay);
			SetDlgItemText(hDlg,IDC_FACTMONEY,cms[6].value);
			/*格式化字符串*/
			FomatCMInsert(cms,FIELD_NUM,fields,values);
			/*对信息表进行操作*/
			mysql_query(&mysql,"BEGIN");									//开启事务管理
			if(!InsertData(TB_NAME,fields,values))
			{
				MessageBoxEx(GetParent(hView),"操作错误","提示",MB_ICONERROR|MB_TOPMOST,0);
				mysql_query(&mysql,"ROLLBACK");
				return 0;
			}
			/*对结果表进行操作*/
			sprintf(sql,"update %s set %s=%s-%s where %s='%s' and %s='%s'",RESULT_TB_NAME,RESULT_TB_TARGET,RESULT_TB_TARGET,cms[4].value,RESULT_TB_BOOK_CONDITION,cms[1].value,RESULT_TB_STORE_CONDITION,"店内");
			mysql_query(&mysql,sql);
			if(mysql_errno(&mysql))
			{
				MessageBoxEx(GetParent(hView),"操作错误","提示",MB_ICONERROR|MB_TOPMOST,0);
				mysql_query(&mysql,"ROLLBACK");
				return 0;
			}
			/*事务提交*/
			mysql_query(&mysql,"COMMIT");
		    HoldInsertIDCondition(sql,PRIMARY);
		    QueryRecordToView(hView,TB_NAME,FIELD_NUM,sql,1,1);
			MessageBox(hDlg,"操作成功","提示",MB_OK);
			break;
		case IDC_BUTTON_SUB:
			if(IsWindow(bookSubView)==0)
			{
				CreateSubViewProc(hDlg,&bookSubView,"图书",sub_book_titles,SUB_TITLES_BOOK_COUNT,0);
			}
			break;
		case ID_QUIT:
			EndDialog(hDlg,0);
			break;
		case IDC_SALE_BARCODE:
			if(HIWORD(wParam)==EN_CHANGE)
			{
				SetSubViewFromEdit(GetDlgItem(hDlg,IDC_SALE_BARCODE),bookSubView,INFO_TB_BOOK_NAME,BOOK_FK,SUB_TITLES_BOOK_COUNT);
			}
			break;
		}
	   return TRUE ; 
       break ;
	case WM_NOTIFY:
		pNmhdr = (LPNMHDR)lParam;
		if(NM_DBLCLK == pNmhdr->code)
		{
			selIndex = SendMessage(pNmhdr->hwndFrom,LVM_GETSELECTIONMARK,0,0);
			if(selIndex == -1)
			{
				return 0;
			}
			ListView_GetItemText(pNmhdr->hwndFrom,selIndex,0,temp,VALUE_LENTH_MAX);
			if(pNmhdr->hwndFrom==bookSubView)
			{
				SetWindowText(GetDlgItem(hDlg,IDC_SALE_BARCODE),temp);
			}
		}
		return 1;
	case  WM_CLOSE: 
		EndDialog(hDlg,0);
		//PostQuitMessage (0) ;
	case  WM_DESTROY :
		//PostQuitMessage (0) ;
		break;
	   return 0 ;
    }
    return FALSE ;	
}


