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
	//}}AFX_DATA_INIT
}


void Dialog_FI_Proceeds::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_FI_Proceeds)
	DDX_Control(pDX, IDCANCEL, m_btcancel);
	DDX_Control(pDX, IDOK, m_btok);
	DDX_Control(pDX, IDC_BUTTON_PROCEEDS, m_btquery);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_RECEIVEDATE, m_timeProceeds);
	DDX_Text(pDX, IDC_EDIT_BILL_ID, m_bill_id);
	DDX_Text(pDX, IDC_EDIT_BILL_WAY, m_bill_way);
	DDX_Text(pDX, IDC_EDIT_COMMENT, m_comment);
	DDX_Text(pDX, IDC_EDIT_LISTID, m_listid);
	DDX_Text(pDX, IDC_EDIT_MONEY_BILL, m_money_bill);
	DDX_Text(pDX, IDC_EDIT_MONEY_PROCEEDS, m_money_proceeds);
	DDX_Text(pDX, IDC_EDIT_MONEY_TOTEL, m_money_totel);
	DDX_Text(pDX, IDC_EDIT_PEOPLE_BUSINESS, m_people_business);
	DDX_Text(pDX, IDC_EDIT_PEOPLE_FI, m_people_fi);
	DDX_Text(pDX, IDC_EDIT_PROCEEDS_WAY, m_proceeds_way);
	DDX_Text(pDX, IDC_EDIT_QUERYLISTID, m_query_listid);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BILL, m_timeBill);
	DDX_Text(pDX, IDC_EDIT_COMMENT_BILL, m_comment_Bill);
	DDX_Text(pDX, IDC_EDIT_PEOPLE_BILL, m_people_bill);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_FI_Proceeds, CDialog)
	//{{AFX_MSG_MAP(Dialog_FI_Proceeds)
	ON_BN_CLICKED(IDC_BUTTON_PROCEEDS, OnProceeds)
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
					str.Format("此订单的签单金额为%s,已收款金额%0.2f,余下收款金额不能超过 %0.2f .",m_money_totel,money_proceeds,atof(m_money_totel)-money_proceeds);
					MessageBox(str,"提示",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS))->SetSel(0, -1);
					mysql_close(&myCont);//断开连接
					dlgpro->endpos();
					return;
				}
				dlgpro->setpos(800);
				sql.Format("update fiproceeds set moneytotel=\"%s\",peoplebusiness=\"%s\",proceedsway=\"%s\",moneyproceeds=\"%s\",peopleproceeds=\"%s\",timeproceeds=\"%s\",comment=\"%s\",billway=\"%s\",moneybill=\"%s\",billid=\"%s\",peoplebill=\"%s\",timebill=\"%s\",commentbill=\"%s\" where listid=\"%s\" ",
					m_money_totel,m_people_business,m_proceeds_way,strmoney_proceeds,m_people_fi,strtimeproceeds,m_comment,m_bill_way,strmoney_bill,m_bill_id,m_people_bill,strtimebill,m_comment_Bill,m_query_listid);
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

				sql.Format("insert into fiproceeds values (\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\")",
					m_listid,m_money_totel,m_people_business,m_proceeds_way,m_money_proceeds,m_people_fi,strtimeproceeds,m_comment,m_bill_way,m_money_bill,m_bill_id,0,m_people_bill,strtimebill,m_comment_Bill);
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
		sql.Format("insert into fidetail values (%d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d)",
				0,m_listid,m_money_totel,m_people_business,m_proceeds_way,m_money_proceeds,m_people_fi,strtimeproceeds,m_comment,m_bill_way,m_money_bill,m_bill_id,m_people_bill,strtimebill,m_comment_Bill,0);
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
		csSql.Format("select people,money from baseinfo where listid=\"%s\" ",m_query_listid);	
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
					m_money_totel = sql_row[1];
					m_people_business = sql_row[0];

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
