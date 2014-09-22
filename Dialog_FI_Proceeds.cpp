// Dialog_FI_Proceeds.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_FI_Proceeds.h"
#include "Dialog_progress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_FI_Proceeds dialog


Dialog_FI_Proceeds::Dialog_FI_Proceeds(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_FI_Proceeds::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_FI_Proceeds)
	m_timeProceeds = 0;
	m_bill_id = _T("");
	m_bill_way = _T("");
	m_comment = _T("");
	m_listid = _T("");
	m_money_bill = _T("");
	m_money_proceeds = _T("");
	m_money_totel = _T("");
	m_people_business = _T("");
	m_people_fi = _T("");
	m_proceeds_way = _T("");
	m_query_listid = _T("");
	m_timeBill = 0;
	m_comment_Bill = _T("");
	m_people_bill = _T("");
	m_listName = _T("");
	//}}AFX_DATA_INIT
}


void Dialog_FI_Proceeds::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_FI_Proceeds)
	DDX_Control(pDX, IDC_BUTTON_INPUT, m_output);
	DDX_Control(pDX, IDC_BUTTON_OUTPUT, m_input);
	DDX_Control(pDX, IDC_COMBO_PROCEEDS_WAY, m_comProceedsWay);
	DDX_Control(pDX, IDC_COMBO_BILL_WAY, m_comBillWay);
	DDX_Control(pDX, IDCANCEL, m_btcancel);
	DDX_Control(pDX, IDOK, m_btok);
	DDX_Control(pDX, IDC_BUTTON_PROCEEDS, m_btquery);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_RECEIVEDATE, m_timeProceeds);
	DDX_Text(pDX, IDC_EDIT_BILL_ID, m_bill_id);
	DDX_Text(pDX, IDC_COMBO_BILL_WAY, m_bill_way);
	DDX_Text(pDX, IDC_EDIT_COMMENT, m_comment);
	DDX_Text(pDX, IDC_EDIT_LISTID, m_listid);
	DDX_Text(pDX, IDC_EDIT_MONEY_BILL, m_money_bill);
	DDX_Text(pDX, IDC_EDIT_MONEY_PROCEEDS, m_money_proceeds);
	DDX_Text(pDX, IDC_EDIT_MONEY_TOTEL, m_money_totel);
	DDX_Text(pDX, IDC_EDIT_PEOPLE_BUSINESS, m_people_business);
	DDX_Text(pDX, IDC_EDIT_PEOPLE_FI, m_people_fi);
	DDX_Text(pDX, IDC_COMBO_PROCEEDS_WAY, m_proceeds_way);
	DDX_Text(pDX, IDC_EDIT_QUERYLISTID, m_query_listid);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BILL, m_timeBill);
	DDX_Text(pDX, IDC_EDIT_COMMENT_BILL, m_comment_Bill);
	DDX_Text(pDX, IDC_EDIT_PEOPLE_BILL, m_people_bill);
	DDX_Text(pDX, IDC_EDIT_LISTNAME, m_listName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_FI_Proceeds, CDialog)
	//{{AFX_MSG_MAP(Dialog_FI_Proceeds)
	ON_BN_CLICKED(IDC_BUTTON_PROCEEDS, OnProceeds)
	ON_BN_CLICKED(IDC_BUTTON_INPUT, OnButtonInput)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT, OnButtonOutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_FI_Proceeds message handlers

BOOL Dialog_FI_Proceeds::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CTime time1 = CTime::GetCurrentTime();
	m_timeProceeds = time1;
	m_timeBill = time1;
	m_people_bill = m_people_fi = g_user;
	m_comProceedsWay.InsertString(0,"银行转账");
	m_comProceedsWay.InsertString(1,"现金");
	m_comBillWay.InsertString(0,"普通发票");
	m_comBillWay.InsertString(1,"专用发票");
	m_comProceedsWay.SetCurSel(0);
	m_comBillWay.SetCurSel(0);
	m_proceeds_way = "银行转账";
	m_bill_way = "普通发票";

	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_FI_Proceeds::OnProceeds() 
{
	UpdateData();
	if(m_listid.IsEmpty())
	{
		MessageBox("请输入订单号：","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
		return;
	}
	if(!(m_money_totel.IsEmpty()))
	{
		if(!IsNum(m_money_totel))
		{
			MessageBox("金额输入必须为数字，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_TOTEL)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_TOTEL))->SetSel(0, -1);
			return;
		}
		if(atof(m_money_totel)>10000000)
		{
			MessageBox("金额超过上限一千万，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_TOTEL)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_TOTEL))->SetSel(0, -1);
			return;
		}
	}
	if(!(m_money_proceeds.IsEmpty()))
	{
		if(!IsNum(m_money_proceeds))
		{
			MessageBox("金额输入必须为数字，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS))->SetSel(0, -1);
			return;
		}
		if(atof(m_money_proceeds)>10000000)
		{
			MessageBox("金额超过上限一千万，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS))->SetSel(0, -1);
			return;
		}
	}
	if(!(m_money_bill.IsEmpty()))
	{
		if(!IsNum(m_money_bill))
		{
			MessageBox("金额输入必须为数字，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL))->SetSel(0, -1);
			return;
		}
		if(atof(m_money_bill)>10000000)
		{
			MessageBox("金额超过上限一千万，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL))->SetSel(0, -1);
			return;
		}
	}


	CString strtimeproceeds;
	strtimeproceeds.Format("%04d-%02d-%02d",m_timeProceeds.GetYear(),m_timeProceeds.GetMonth(),m_timeProceeds.GetDay());
	CString strtimebill;
	strtimebill.Format("%04d-%02d-%02d",m_timeBill.GetYear(),m_timeBill.GetMonth(),m_timeBill.GetDay());


	Dialog_progress *dlgpro;
	dlgpro=new Dialog_progress(); 
	dlgpro->Create(IDD_DIALOG_PROGRESS);
	if(g_openprocess)
		dlgpro->ShowWindow(SW_SHOW);
	else
		dlgpro->ShowWindow(SW_HIDE);

	CString sql;
	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	mysql_init(&myCont);
	if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
	{
		dlgpro->setpos(500);
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
		sql = "select moneyproceeds,moneybill,ficheck from fiproceeds where listid='" + m_query_listid +"'";
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
			return;
		}
		dlgpro->setpos(600);
		result=mysql_store_result(&myCont);//保存查询到的数据到result
		if(result)
		{
			unsigned __int64 num = mysql_num_rows(result);//行数
			if(num>=1)
			{
				//修改记录	
				float money_proceeds = 0;
				float money_bill = 0;
				int check = 0;
				while(sql_row=mysql_fetch_row(result))//获取具体的数据
                {
					if(sql_row[0]!=NULL)
						money_proceeds = atof(sql_row[0]);
					if(sql_row[1]!=NULL)
						money_bill = atof(sql_row[1]);
					if(sql_row[2]!=NULL)
						check = atoi(sql_row[2]);					
                }//while
				if(check==1)
				{
					MessageBox("此订单已被核销，不可再收款","提示",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_LISTID_QUERY)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_LISTID_QUERY))->SetSel(0, -1);
					mysql_close(&myCont);//断开连接
					dlgpro->endpos();
					return;
				}
				CString strmoney_proceeds;
				CString strmoney_bill;
				strmoney_proceeds.Format("%0.2f",money_proceeds+atof(m_money_proceeds));
				strmoney_bill.Format("%0.2f",money_bill+atof(m_money_bill));
				if(atof(strmoney_proceeds)>atof(m_money_totel))
				{
					CString str;
					str.Format("此订单的签单金额为%s,已收款金额%0.2f,余下收款金额不能超过 %0.2f ,是否继续？",m_money_totel,money_proceeds,atof(m_money_totel)-money_proceeds);
					int ret = MessageBox(str,"提示",MB_OKCANCEL);
					if(ret!=1)
					{
						(CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS))->SetSel(0, -1);
						mysql_close(&myCont);//断开连接
						dlgpro->endpos();
						return;
					}					
				}
				if(atof(strmoney_bill)>atof(m_money_totel))
				{
					CString str;
					str.Format("此订单的签单金额为%s,已开票金额%0.2f,余下开票金额不能超过 %0.2f ,是否继续？",m_money_totel,money_bill,atof(m_money_totel)-money_bill);
					if(MessageBox(str,"提示",MB_OKCANCEL)!=1)
					{
						(CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL))->SetSel(0, -1);
						mysql_close(&myCont);//断开连接
						dlgpro->endpos();
						return;
					}					
				}
				dlgpro->setpos(800);
				sql.Format("update fiproceeds set listname=\"%s\",moneytotel=\"%s\",peoplebusiness=\"%s\",proceedsway=\"%s\",moneyproceeds=\"%s\",peopleproceeds=\"%s\",timeproceeds=\"%s\",comment=\"%s\",billway=\"%s\",moneybill=\"%s\",billid=\"%s\",peoplebill=\"%s\",timebill=\"%s\",commentbill=\"%s\" where listid=\"%s\" ",
					m_listName,m_money_totel,m_people_business,m_proceeds_way,strmoney_proceeds,m_people_fi,strtimeproceeds,m_comment,m_bill_way,strmoney_bill,m_bill_id,m_people_bill,strtimebill,m_comment_Bill,m_query_listid);
				int ret = mysql_query(&myCont,sql);
				if(ret!= 0)
				{
					const char *error = mysql_error(&myCont);
					CString str;
					str.Format("数据库错误(%s)",error);
					MessageBox(str,"提示",MB_OK);
					mysql_close(&myCont);//断开连接
					dlgpro->endpos();
					return;
				}
			}
			else
			{//新增记录
				dlgpro->setpos(700);
				sql.Format("select * from baseinfo where listid=\"%s\" ",m_query_listid);
				if(mysql_query(&myCont,sql)!= 0)
				{
					const char *error = mysql_error(&myCont);
					CString str;
					str.Format("数据库错误(%s)",error);
					MessageBox(str,"提示",MB_OK);
					mysql_close(&myCont);//断开连接
					dlgpro->endpos();
					return;
				}
				result=mysql_store_result(&myCont);//保存查询到的数据到result
				if(result)
				{
					dlgpro->setpos(750);
					unsigned __int64 num = mysql_num_rows(result);//行数
					if(num!=1)//
					{
						MessageBox("无此订单或未保存订单","提示",MB_OK);
						(CEdit*)GetDlgItem(IDC_EDIT_LISTID_QUERY)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_LISTID_QUERY))->SetSel(0, -1);
						if(result!=NULL) mysql_free_result(result);//释放结果资源
						mysql_close(&myCont);//断开连接
						dlgpro->endpos();
						return;	
					}
				}
				else
				{
					const char *error = mysql_error(&myCont);
					CString str;
					str.Format("数据库错误(%s)",error);
					MessageBox(str,"提示",MB_OK);
					mysql_close(&myCont);//断开连接
					dlgpro->endpos();
					return;
				}
				dlgpro->setpos(800);

				sql.Format("insert into fiproceeds values (\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\")",
					m_listid,m_listName,m_money_totel,m_people_business,m_proceeds_way,m_money_proceeds,m_people_fi,strtimeproceeds,m_comment,m_bill_way,m_money_bill,m_bill_id,0,m_people_bill,strtimebill,m_comment_Bill);
				if(mysql_query(&myCont,sql)!= 0)
				{
					const char *error = mysql_error(&myCont);
					CString str;
					str.Format("数据库错误(%s)",error);
					MessageBox(str,"提示",MB_OK);
					mysql_close(&myCont);//断开连接
					dlgpro->endpos();
					return;
				}
			}
		}
		else
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
			return;
		}
		//detail
		dlgpro->setpos(900);
		sql.Format("insert into fidetail values (%d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d)",
				0,m_listid,m_listName,m_money_totel,m_people_business,m_proceeds_way,m_money_proceeds,m_people_fi,strtimeproceeds,m_comment,m_bill_way,m_money_bill,m_bill_id,m_people_bill,strtimebill,m_comment_Bill,0);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
			return;
		}
		dlgpro->setpos(980);
		
	}
	else
	{
		const char *error = mysql_error(&myCont);
		CString str;
		str.Format("数据库错误(%s)",error);
		MessageBox(str,"提示",MB_OK);
		mysql_close(&myCont);//断开连接
		dlgpro->endpos();
		return;
	}
	if(result!=NULL) mysql_free_result(result);//释放结果资源
	mysql_close(&myCont);//断开连接
	dlgpro->endpos();
	MessageBox("收款开票成功","提示",MB_OK);
}


BOOL Dialog_FI_Proceeds::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN) 
	{  
		switch(pMsg->wParam) 
		{  
		//case VK_RETURN: //回车  
		//	return TRUE;  
		case VK_ESCAPE: //ESC  
			return TRUE;  
		}  
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void Dialog_FI_Proceeds::OnOK() 
{
	UpdateData();
	CString csSql;
	m_query_listid.TrimLeft();
	m_query_listid.TrimRight();
	if (m_query_listid.IsEmpty())
	{	
		MessageBox("订单号为空，请输入","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
		return;
	}
	else
	{
		csSql.Format("select listname,people,money from baseinfo where listid=\"%s\" ",m_query_listid);	
	}
	Dialog_progress *dlgpro;
	dlgpro=new Dialog_progress(); 
	dlgpro->Create(IDD_DIALOG_PROGRESS);
	if(g_openprocess)
		dlgpro->ShowWindow(SW_SHOW);
	else
		dlgpro->ShowWindow(SW_HIDE);
    MYSQL myCont;
    MYSQL_RES *result;
    MYSQL_ROW sql_row;
    int res;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
    {
		dlgpro->setpos(500);
        mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
        res=mysql_query(&myCont,csSql);//查询
        if(!res)
        {
			dlgpro->setpos(600);
            result=mysql_store_result(&myCont);//保存查询到的数据到result
			dlgpro->setpos(700);
		    if(result)
            {
                int j = 0;
                j=mysql_num_fields(result);//查看多少列
				unsigned __int64 num = mysql_num_rows(result);//行数
				int index = 0;
                sql_row=mysql_fetch_row(result);//获取具体的数据
				if(sql_row)
                {
					m_listid = m_query_listid;
					m_listName = sql_row[0];
					m_money_bill = m_money_proceeds = m_money_totel = sql_row[2];
					m_people_business = sql_row[1];

					dlgpro->setpos(900);
					dlgpro->endpos();
                    UpdateData(FALSE);
                }
				else
				{
					MessageBox("无此订单号，请重新输入","提示",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
					mysql_close(&myCont);//断开连接
					dlgpro->endpos();
					return;
				}
            }
        }
        else
        {
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
			return;
        }
    }
    else
    {
		const char *error = mysql_error(&myCont);
		CString str;
		str.Format("数据库错误(%s)",error);
		MessageBox(str,"提示",MB_OK);
		mysql_close(&myCont);//断开连接
		dlgpro->endpos();
		return;
    }
    if(result!=NULL) mysql_free_result(result);//释放结果资源
    mysql_close(&myCont);//断开连接
	return;
	//CDialog::OnOK();
}

void Dialog_FI_Proceeds::OnProceedsInput() 
{
	UpdateData();
	if(m_listid.IsEmpty())
	{
		MessageBox("请输入订单号：","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
		return;
	}
	if(!(m_money_totel.IsEmpty()))
	{
		if(!IsNum(m_money_totel))
		{
			MessageBox("金额输入必须为数字，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_TOTEL)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_TOTEL))->SetSel(0, -1);
			return;
		}
		if(atof(m_money_totel)>10000000)
		{
			MessageBox("金额超过上限一千万，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_TOTEL)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_TOTEL))->SetSel(0, -1);
			return;
		}
	}
	if(!(m_money_proceeds.IsEmpty()))
	{
		if(!IsNum(m_money_proceeds))
		{
			MessageBox("金额输入必须为数字，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS))->SetSel(0, -1);
			return;
		}
		if(atof(m_money_proceeds)>10000000)
		{
			MessageBox("金额超过上限一千万，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS))->SetSel(0, -1);
			return;
		}
	}
	if(!(m_money_bill.IsEmpty()))
	{
		if(!IsNum(m_money_bill))
		{
			MessageBox("金额输入必须为数字，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL))->SetSel(0, -1);
			return;
		}
		if(atof(m_money_bill)>10000000)
		{
			MessageBox("金额超过上限一千万，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL))->SetSel(0, -1);
			return;
		}
	}


	CString strtimeproceeds;
	strtimeproceeds.Format("%04d-%02d-%02d",m_timeProceeds.GetYear(),m_timeProceeds.GetMonth(),m_timeProceeds.GetDay());
	CString strtimebill;
	strtimebill.Format("%04d-%02d-%02d",m_timeBill.GetYear(),m_timeBill.GetMonth(),m_timeBill.GetDay());


	Dialog_progress *dlgpro;
	dlgpro=new Dialog_progress(); 
	dlgpro->Create(IDD_DIALOG_PROGRESS);
	if(g_openprocess)
		dlgpro->ShowWindow(SW_SHOW);
	else
		dlgpro->ShowWindow(SW_HIDE);

	CString sql;
	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	mysql_init(&myCont);
	if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
	{
		dlgpro->setpos(500);
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
		sql = "select moneyproceeds,moneybill,ficheck from fiproceeds where listid='" + m_query_listid +"'";
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
			return;
		}
		dlgpro->setpos(600);
		result=mysql_store_result(&myCont);//保存查询到的数据到result
		if(result)
		{
			unsigned __int64 num = mysql_num_rows(result);//行数
			if(num>=1)
			{
				//修改记录	
				float money_proceeds = 0;
				float money_bill = 0;
				int check = 0;
				while(sql_row=mysql_fetch_row(result))//获取具体的数据
                {
					if(sql_row[0]!=NULL)
						money_proceeds = atof(sql_row[0]);
					if(sql_row[1]!=NULL)
						money_bill = atof(sql_row[1]);
					if(sql_row[2]!=NULL)
						check = atoi(sql_row[2]);					
                }//while
				if(check==1)
				{
					MessageBox("此订单已被核销，不可再收款","提示",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_LISTID_QUERY)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_LISTID_QUERY))->SetSel(0, -1);
					mysql_close(&myCont);//断开连接
					dlgpro->endpos();
					return;
				}
				CString strmoney_proceeds;
				CString strmoney_bill;
				strmoney_proceeds.Format("%0.2f",money_proceeds+atof(m_money_proceeds));
				strmoney_bill.Format("%0.2f",money_bill+atof(m_money_bill));
				if(atof(strmoney_proceeds)>atof(m_money_totel))
				{
					CString str;
					str.Format("此订单%s的签单金额为%s,已收款金额%0.2f,余下收款金额不能超过 %0.2f ,是否继续？",m_query_listid,m_money_totel,money_proceeds,atof(m_money_totel)-money_proceeds);
					int ret = MessageBox(str,"提示",MB_OKCANCEL);
					if(ret!=1)
					{
						(CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS))->SetSel(0, -1);
						mysql_close(&myCont);//断开连接
						dlgpro->endpos();
						return;
					}					
				}
				if(atof(strmoney_bill)>atof(m_money_totel))
				{
					CString str;
					str.Format("此订单%s的签单金额为%s,已开票金额%0.2f,余下开票金额不能超过 %0.2f ,是否继续？",m_query_listid,m_money_totel,money_bill,atof(m_money_totel)-money_bill);
					if(MessageBox(str,"提示",MB_OKCANCEL)!=1)
					{
						(CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL))->SetSel(0, -1);
						mysql_close(&myCont);//断开连接
						dlgpro->endpos();
						return;
					}					
				}
				dlgpro->setpos(800);
				sql.Format("update fiproceeds set listname=\"%s\",moneytotel=\"%s\",peoplebusiness=\"%s\",proceedsway=\"%s\",moneyproceeds=\"%s\",peopleproceeds=\"%s\",timeproceeds=\"%s\",comment=\"%s\",billway=\"%s\",moneybill=\"%s\",billid=\"%s\",peoplebill=\"%s\",timebill=\"%s\",commentbill=\"%s\" where listid=\"%s\" ",
					m_listName,m_money_totel,m_people_business,m_proceeds_way,strmoney_proceeds,m_people_fi,strtimeproceeds,m_comment,m_bill_way,strmoney_bill,m_bill_id,m_people_bill,strtimebill,m_comment_Bill,m_query_listid);
				int ret = mysql_query(&myCont,sql);
				if(ret!= 0)
				{
					const char *error = mysql_error(&myCont);
					CString str;
					str.Format("数据库错误(%s)",error);
					MessageBox(str,"提示",MB_OK);
					mysql_close(&myCont);//断开连接
					dlgpro->endpos();
					return;
				}
			}
			else
			{//新增记录
				dlgpro->setpos(700);
				sql.Format("select * from baseinfo where listid=\"%s\" ",m_query_listid);
				if(mysql_query(&myCont,sql)!= 0)
				{
					const char *error = mysql_error(&myCont);
					CString str;
					str.Format("数据库错误(%s)",error);
					MessageBox(str,"提示",MB_OK);
					mysql_close(&myCont);//断开连接
					dlgpro->endpos();
					return;
				}
				result=mysql_store_result(&myCont);//保存查询到的数据到result
				if(result)
				{
					dlgpro->setpos(750);
					unsigned __int64 num = mysql_num_rows(result);//行数
					if(num!=1)//
					{
						CString str;
						str.Format("无此订单%s或此订单未保存.",m_query_listid);
						MessageBox(str,"提示",MB_OK);
						(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID))->SetSel(0, -1);
						if(result!=NULL) mysql_free_result(result);//释放结果资源
						mysql_close(&myCont);//断开连接
						dlgpro->endpos();
						return;	
					}
				}
				else
				{
					const char *error = mysql_error(&myCont);
					CString str;
					str.Format("数据库错误(%s)",error);
					MessageBox(str,"提示",MB_OK);
					mysql_close(&myCont);//断开连接
					dlgpro->endpos();
					return;
				}
				dlgpro->setpos(800);

				sql.Format("insert into fiproceeds values (\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\")",
					m_listid,m_listName,m_money_totel,m_people_business,m_proceeds_way,m_money_proceeds,m_people_fi,strtimeproceeds,m_comment,m_bill_way,m_money_bill,m_bill_id,0,m_people_bill,strtimebill,m_comment_Bill);
				if(mysql_query(&myCont,sql)!= 0)
				{
					const char *error = mysql_error(&myCont);
					CString str;
					str.Format("数据库错误(%s)",error);
					MessageBox(str,"提示",MB_OK);
					mysql_close(&myCont);//断开连接
					dlgpro->endpos();
					return;
				}
			}
		}
		else
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
			return;
		}
		//detail
		dlgpro->setpos(900);
		sql.Format("insert into fidetail values (%d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d)",
				0,m_listid,m_listName,m_money_totel,m_people_business,m_proceeds_way,m_money_proceeds,m_people_fi,strtimeproceeds,m_comment,m_bill_way,m_money_bill,m_bill_id,m_people_bill,strtimebill,m_comment_Bill,0);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
			return;
		}
		dlgpro->setpos(980);
		
	}
	else
	{
		const char *error = mysql_error(&myCont);
		CString str;
		str.Format("数据库错误(%s)",error);
		MessageBox(str,"提示",MB_OK);
		mysql_close(&myCont);//断开连接
		dlgpro->endpos();
		return;
	}
	if(result!=NULL) mysql_free_result(result);//释放结果资源
	mysql_close(&myCont);//断开连接
	dlgpro->endpos();
}

void Dialog_FI_Proceeds::OnButtonInput() 
{
	CString FilePathName;
    CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
        NULL, 
        NULL,
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        (LPCTSTR)_TEXT("xls Files (*.xls)|*.xls|All Files (*.*)|*.*||"),
        NULL);
    if(dlg.DoModal()==IDOK)
    {
        FilePathName=dlg.GetPathName(); //文件名保存在了FilePathName里
    }
    else
    {
         return;
    }

	_Application   m_oExcelApp;              // Excel程序
	_Worksheet     m_oWorkSheet;     // 工作表
	_Workbook      m_oWorkBook;      // 工作簿
	Workbooks      m_oWorkBooks;    // 工作簿集合
	Worksheets     m_oWorkSheets;    // 工作表集合
	Range          m_oCurrRange;      // 使用区域
	if (!m_oExcelApp.CreateDispatch( _T( "Excel.Application" ), NULL ) )
	{
		::MessageBox( NULL, _T( "创建Excel服务失败！" ), _T( "错误提示！" ), MB_OK | MB_ICONERROR);
		return;
	}

	//设置为显示
	m_oExcelApp.SetVisible(FALSE);
	m_oWorkBooks.AttachDispatch( m_oExcelApp.GetWorkbooks(), TRUE ); //没有这条语句，下面打开文件返回失败。

	LPDISPATCH lpDisp = NULL;
	COleVariant covTrue((short)TRUE);
	COleVariant covFalse((short)FALSE);
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR); 
	Range       oCurCell;

// 	CString theAppPath,theAppName; 
// 	char Path[MAX_PATH]; 
// //找到文件
// 	GetModuleFileName(NULL,Path,MAX_PATH);//得到应用程序的全路径 
// 	theAppPath=(CString)Path; 
// 
// 	theAppName=AfxGetApp()->m_pszAppName; 
// 	theAppName+=".exe"; 
// 
// 	//把最后的文件名去掉 
// 	int length1,length2; 
// 
// 	length1=theAppPath.GetLength(); 
// 	length2=theAppName.GetLength(); 
// 
// 	theAppPath.Delete(length1-length2,length2); 
// 	CString strFilePath=""; 
// 	strFilePath=theAppPath+"收款开票.xls";//EXCEL模板的路径

	// 打开文件
	lpDisp = m_oWorkBooks.Open( FilePathName,
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing) );
	// 获得活动的WorkBook( 工作簿 )
	m_oWorkBook.AttachDispatch( lpDisp, TRUE );
	// 获得活动的WorkSheet( 工作表 )
	m_oWorkSheet.AttachDispatch( m_oWorkBook.GetActiveSheet(), TRUE );
	// 获得使用的区域Range( 区域 )
	m_oCurrRange.AttachDispatch( m_oWorkSheet.GetUsedRange(), TRUE );

	// 获得使用的行数
	long lgUsedRowNum = 0;
	m_oCurrRange.AttachDispatch( m_oCurrRange.GetRows(), TRUE );
	lgUsedRowNum = m_oCurrRange.GetCount();
	// 获得使用的列数
	long lgUsedColumnNum = 0;
	m_oCurrRange.AttachDispatch( m_oCurrRange.GetColumns(), TRUE );
	lgUsedColumnNum = m_oCurrRange.GetCount();
	// 读取Sheet的名称
	CString strSheetName = m_oWorkSheet.GetName();

	//得到全部Cells，此时,CurrRange是cells的集合
	m_oCurrRange.AttachDispatch( m_oWorkSheet.GetCells(), TRUE );

	oCurCell.AttachDispatch( m_oCurrRange.GetItem( COleVariant( (long)(1)), COleVariant( (long)1 ) ).pdispVal, TRUE );
	VARIANT varItemName = oCurCell.GetText();
	CString strItemName;
	strItemName = varItemName.bstrVal;
	if(strItemName.Compare("收款开票")!=0)
	{
		MessageBox("数据格式不正确，请导入正确格式的数据.","提示",MB_OK);
		return;
	}

	// 遍历整个Excel表格
	for ( int i = 4; i <= lgUsedRowNum; i++)
	{
		for ( int j = 2; j <= lgUsedColumnNum; j++ )
		{
			oCurCell.AttachDispatch( m_oCurrRange.GetItem( COleVariant( (long)(i)), COleVariant( (long)j ) ).pdispVal, TRUE );
			varItemName = oCurCell.GetText();
			strItemName = varItemName.bstrVal;
			if(j==2) m_listid = m_query_listid = strItemName;
			if(m_listid.IsEmpty())
				break;
			if(j==3) m_listName = strItemName;
			if(j==4) m_money_totel = strItemName;
			if(j==5) m_people_business = strItemName;
			if(j==6) m_proceeds_way = strItemName;
			if(j==7) m_money_proceeds = strItemName;
			if(j==8) m_people_fi = strItemName;
			if(j==10) m_comment = strItemName;
			if(j==11) m_bill_way = strItemName;
			if(j==12) m_money_bill = strItemName;
			if(j==13) m_people_bill = strItemName;
			if(j==14) m_bill_id = strItemName;
			if(j==16) m_comment_Bill = strItemName;
			if(j==9)
			{
				if(strItemName.GetLength()<10)
				{
					CTime time1 = CTime::GetCurrentTime();
					m_timeProceeds = time1;
				}
				else
				{
					CTime timeTmp(atoi(strItemName.Mid(0,4)),atoi(strItemName.Mid(5,2)),atoi(strItemName.Mid(8,2)),0,0,0,0);
					m_timeProceeds = timeTmp;
				}
				
			}
			if(j==15)
			{
				if(strItemName.GetLength()<10)
				{
					CTime time1 = CTime::GetCurrentTime();
					m_timeProceeds = time1;
				}
				else
				{
					CTime timeTmp1(atoi(strItemName.Mid(0,4)),atoi(strItemName.Mid(5,2)),atoi(strItemName.Mid(8,2)),0,0,0,0);
					m_timeBill = timeTmp1;
				}
				
			}
			
		}
		UpdateData(FALSE);
		if(m_listid.IsEmpty())
			continue ;
		OnProceedsInput();
		m_listid = m_query_listid = "";
		m_listName = "";
		m_money_totel = "";
		m_people_business = "";
		m_proceeds_way = "";
		m_money_proceeds = "";
		m_people_fi = "";
		m_comment = "";
		m_bill_way = "";
		m_money_bill = "";
		m_people_bill = "";
		m_bill_id = "";
		m_comment_Bill = "";
		CTime time1 = CTime::GetCurrentTime();
		m_timeBill = m_timeProceeds = time1;
	}
	MessageBox("收款开票已完成.","提示",MB_OK);

	// 关闭
	m_oWorkBook.Close( covOptional, COleVariant( FilePathName ), covOptional );
	m_oWorkBooks.Close();
	// 释放
	m_oCurrRange.ReleaseDispatch();
	m_oWorkSheet.ReleaseDispatch();
	m_oWorkSheets.ReleaseDispatch();
	m_oWorkBook.ReleaseDispatch();
	m_oWorkBooks.ReleaseDispatch();
	m_oExcelApp.ReleaseDispatch();
	m_oExcelApp.Quit();    // 这条语句是推出Excel程序，任务管理器中的EXCEL进程会自动结束。
	
}

void Dialog_FI_Proceeds::OnButtonOutput() 
{
	UpdateData();
	CString strTimeProceeds,strTimeBill;
	strTimeProceeds.Format("%04d-%02d-%02d",m_timeProceeds.GetYear(),m_timeProceeds.GetMonth(),m_timeProceeds.GetDay());
	strTimeBill.Format("%04d-%02d-%02d",m_timeBill.GetYear(),m_timeBill.GetMonth(),m_timeBill.GetDay());
	CString filename ;
	filename.Format("收款开票.xls");
	Range m_ExlRge; 
	_Worksheet m_ExlSheet; 
	Worksheets m_ExlSheets; 
	_Workbook m_ExlBook; 
	Workbooks m_ExlBooks; 
	_Application m_ExlApp; 
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	//用m_ExlApp对象创建Excel2003进程 

	if(!m_ExlApp.CreateDispatch("Excel.Application",NULL)) 
	{ 
		AfxMessageBox("创建Excel服务失败!"); 
		return; 
	} 

	//设置为可见 
	m_ExlApp.SetVisible(TRUE); 

	///////////////////下面得到应用程序所在的路径/////////////////// 
	CString theAppPath,theAppName; 
	char Path[MAX_PATH]; 

	GetModuleFileName(NULL,Path,MAX_PATH);//得到应用程序的全路径 
	theAppPath=(CString)Path; 

	theAppName=AfxGetApp()->m_pszAppName; 
	theAppName+=".exe"; 

	//把最后的文件名去掉 
	int length1,length2; 

	length1=theAppPath.GetLength(); 
	length2=theAppName.GetLength(); 

	theAppPath.Delete(length1-length2,length2); 
	CString TempPath=""; 
	TempPath=theAppPath+filename;//EXCEL模板的路径 
//	CFile file;
//	file.Open(TempPath,CFile::modeCreate|CFile::modeWrite);
//	file.Close();


	m_ExlBooks.AttachDispatch(m_ExlApp.GetWorkbooks(),TRUE); 

	//m_ExlBook.AttachDispatch(m_ExlBooks.Add((_variant_t)TempPath),TRUE);//加载EXCEL模板 
	m_ExlBook.AttachDispatch(m_ExlBooks.Add(covOptional),TRUE);//加载EXCEL模板 

	m_ExlSheets.AttachDispatch(m_ExlBook.GetSheets(),TRUE);//加载Sheet页面 

	//添加新的Sheet页面 
	m_ExlSheets.Add(vtMissing,vtMissing,_variant_t((long)1),vtMissing); 

	//删除第二个Sheet页面 
	m_ExlSheet.AttachDispatch(m_ExlSheets.GetItem(_variant_t((long)2)),TRUE); 
	m_ExlSheet.Delete(); 

	//把第一个Sheet页面的名字改变为TestSheet 
	m_ExlSheet.AttachDispatch(m_ExlSheets.GetItem(_variant_t((long)1)),TRUE);
	CString strtmp;
	m_ExlSheet.SetName(filename); 

	m_ExlRge.AttachDispatch(m_ExlSheet.GetCells(),TRUE);//加载所有单元格
	m_ExlRge.SetNumberFormatLocal(COleVariant("@")); 

	//合并单元格
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("P1")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("B2"),_variant_t("E2")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("F2"),_variant_t("J2")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("K2"),_variant_t("P2")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));
	////////设置表格内容//////// 

	m_ExlRge.AttachDispatch(m_ExlSheet.GetCells(),TRUE);//加载所有单元格
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(1)),_variant_t("收款开票"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(2)),_variant_t("订单信息"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(6)),_variant_t("收款"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(11)),_variant_t("开票"));

	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(1)),_variant_t("序号"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(2)),_variant_t("订单号"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(3)),_variant_t("订单名称"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(4)),_variant_t("订单金额"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(5)),_variant_t("业务经办人"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(6)),_variant_t("收款方式"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(7)),_variant_t("收款金额"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(8)),_variant_t("收款人"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(9)),_variant_t("收款日期"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(10)),_variant_t("收款备注"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(11)),_variant_t("发票类型"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(12)),_variant_t("开票金额"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(13)),_variant_t("开票人"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(14)),_variant_t("发票号码"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(15)),_variant_t("开票日期"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(16)),_variant_t("开票备注"));

	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(1)),_variant_t("1"));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(2)),_variant_t(m_listid));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(3)),_variant_t(m_listName));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(4)),_variant_t(m_money_totel));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(5)),_variant_t(m_people_business));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(6)),_variant_t(m_proceeds_way));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(7)),_variant_t(m_money_proceeds));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(8)),_variant_t(m_people_fi));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(9)),_variant_t(strTimeProceeds));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(10)),_variant_t(m_comment));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(11)),_variant_t(m_bill_way));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(12)),_variant_t(m_money_bill));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(13)),_variant_t(m_people_bill));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(14)),_variant_t(m_bill_id));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(15)),_variant_t(strTimeBill));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(16)),_variant_t(m_comment_Bill));

	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"), _variant_t("A4")));//获取表单中的列"P"对象
	m_ExlRge.SetColumnWidth(_variant_t((long)6));  //设置列宽为100
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("B3"), _variant_t("P20")));//获取表单中的列"P"对象
	m_ExlRge.SetColumnWidth(_variant_t((long)14));  //设置列宽为100

	//m_ExlRge.AttachDispatch(m_ExlSheet.GetUsedRange());//加载已使用的单元格 
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A3"), _variant_t("P20")));//获取表单中的列"P"对象
	m_ExlRge.SetWrapText(_variant_t((long)1));//设置单元格内的文本为自动换行 
	//m_ExlRge.SetColumnWidth(_variant_t((long)13));  //设置列宽为100
	m_ExlRge.SetRowHeight(_variant_t((long)30	));

	//设置齐方式为水平垂直居中 
	//水平对齐：默认＝1,居中＝-4108,左＝-4131,右＝-4152 
	//垂直对齐：默认＝2,居中＝-4108,左＝-4160,右＝-4107 
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4131));
	m_ExlRge.SetVerticalAlignment(_variant_t((long)-4108));

	///////设置整体的字体、字号及颜色////// 

	Font ft; 

	ft.AttachDispatch(m_ExlRge.GetFont()); 

	ft.SetName(_variant_t("宋体"));//字体 
	//ft.SetColorIndex(_variant_t((long)11));//字的颜色 
	ft.SetColor( _variant_t((long) RGB(32, 32, 32) ) );
	ft.SetSize(_variant_t((long)12));//字号 

	///////////设置标题字体及颜色////////// 

	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("P1"))); 

	ft.AttachDispatch(m_ExlRge.GetFont()); 
	//ft.SetBold(_variant_t((long)0));//粗体 
	ft.SetSize(_variant_t((long)15)); 
	//ft.SetColorIndex(_variant_t((long)2)); 

	//CellFormat cf; 
	//cf.AttachDispatch(m_ExlRge.GetCells()); 

	//居中
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("P1")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4108));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"),_variant_t("P2")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4108));

	ft.AttachDispatch(m_ExlRge.GetFont());
	//ft.SetBold(_variant_t((long)0));//粗体
	ft.SetSize(_variant_t((long)14));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("P1")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4108));
	ft.AttachDispatch(m_ExlRge.GetFont());
	//ft.SetBold(_variant_t((long)0));//粗体
	ft.SetSize(_variant_t((long)14));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"),_variant_t("P2")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4108));
	ft.AttachDispatch(m_ExlRge.GetFont());
	//ft.SetBold(_variant_t((long)0));//粗体
	ft.SetSize(_variant_t((long)14));


	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A3"),_variant_t("P3")));
	ft.AttachDispatch(m_ExlRge.GetFont());
	ft.SetColor( _variant_t((long) RGB(255,0,0 )) );
	ft.SetSize(_variant_t((long)12));//字号

	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A4"),_variant_t("P20")));
	ft.AttachDispatch(m_ExlRge.GetFont());
	ft.SetColor( _variant_t((long) RGB(32,32,32)) );
	ft.SetSize(_variant_t((long)12));//字号

	//////////////设置底色///////////////// 

//	Interior it; 
//	it.AttachDispatch(m_ExlRge.GetInterior()); 
//	it.SetColorIndex(_variant_t((long)11));//标题底色 

	////表格内容的底色//// 

//	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"),_variant_t("D5"))); 

//	it.AttachDispatch(m_ExlRge.GetInterior()); 

//	it.SetColorIndex(_variant_t((long)15)); 


	//////////////为表格设置边框///////////// 

	Range UnitRge; 
	CString CellName; 
	int i = 0;
	for(i=3;i<=20;i++) 
	{
		for(int j=1;j<=16;j++) 
		{
			CellName.Format("%c%d",j+64,i);//单元格的名称
			UnitRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t(CellName),_variant_t(CellName)));//加载单元格
			//LineStyle=线型 Weight=线宽 ColorIndex=线的颜色(-4105为自动)
			UnitRge.BorderAround(_variant_t((long)1),_variant_t((long)2),_variant_t((long)-4105),vtMissing);//设置边框
		}
	}
	UnitRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("P1")));//加载单元格
	UnitRge.BorderAround(_variant_t((long)1),_variant_t((long)2),_variant_t((long)-4105),vtMissing);//设置边框
	UnitRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"),_variant_t("A2")));//加载单元格
	UnitRge.BorderAround(_variant_t((long)1),_variant_t((long)2),_variant_t((long)-4105),vtMissing);//设置边框
	UnitRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("B2"),_variant_t("E2")));//加载单元格
	UnitRge.BorderAround(_variant_t((long)1),_variant_t((long)2),_variant_t((long)-4105),vtMissing);//设置边框
	UnitRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("F2"),_variant_t("J2")));//加载单元格
	UnitRge.BorderAround(_variant_t((long)1),_variant_t((long)2),_variant_t((long)-4105),vtMissing);//设置边框
	UnitRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("K2"),_variant_t("P2")));//加载单元格
	UnitRge.BorderAround(_variant_t((long)1),_variant_t((long)2),_variant_t((long)-4105),vtMissing);//设置边框
//	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("B13"),_variant_t("B13")));
//	m_ExlRge.SetRowHeight(COleVariant((short)120));
	
	//Range cols;
	//cols=m_ExlRge.GetEntireColumn();//选择A:A列，设置宽度为自动适应
	//cols.AutoFit();
	m_ExlApp.SetVisible(TRUE);//显示Excel表格，并设置状态为用户可控制
	m_ExlApp.SetUserControl(TRUE);

	m_ExlBook.SaveAs(COleVariant(TempPath),covOptional,
	covOptional,covOptional,
	covOptional,covOptional,(long)0,covOptional,covOptional,covOptional,
	covOptional,covOptional);

	//释放对象（相当重要
	m_ExlRge.ReleaseDispatch();
	m_ExlSheet.ReleaseDispatch();
	m_ExlSheets.ReleaseDispatch();
	m_ExlBook.ReleaseDispatch();
	m_ExlBooks.ReleaseDispatch();
	//m_ExlApp一定要释放，否则程序结束后还会有一个Excel进程驻留在内存中，而且程序重复运行的时候会出错 
	m_ExlApp.ReleaseDispatch();

	//退出程序
	m_ExlApp.Quit();
}
