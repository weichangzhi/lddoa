// Dialog_FI.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_FI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_FI dialog


Dialog_FI::Dialog_FI(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_FI::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_FI)
	m_strlistid_add = _T("");
	m_strlistid_query = _T("");
	m_billing = FALSE;
	m_gathering = FALSE;
	m_time_start = 0;
	m_time_end = 0;
	//}}AFX_DATA_INIT
}


void Dialog_FI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_FI)
	DDX_Control(pDX, IDC_LIST_FI, m_listFI);
	DDX_Text(pDX, IDC_EDIT_LISTID_ADD, m_strlistid_add);
	DDX_Text(pDX, IDC_EDIT_LISTID_QUERY, m_strlistid_query);
	DDX_Check(pDX, IDC_CHECK_BILLING, m_billing);
	DDX_Check(pDX, IDC_CHECK_GATHERING, m_gathering);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_time_start);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_time_end);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_FI, CDialog)
	//{{AFX_MSG_MAP(Dialog_FI)
	ON_BN_CLICKED(IDC_BUTTON_FIADD, OnFiadd)
	ON_BN_CLICKED(IDC_EXCEL, OnExcel)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_FI, OnColumnclickListFi)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_FI message handlers

BOOL Dialog_FI::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if((g_permission & FI)==0)
	{
		GetDlgItem(IDC_BUTTON_FIADD)->EnableWindow(FALSE);
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		GetDlgItem(IDC_EXCEL)->EnableWindow(FALSE);
	}

	m_listFI.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listFI.InsertColumn(0, _T("序号"), LVCFMT_LEFT,60);
	m_listFI.InsertColumn(1, _T("订单号"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(2, _T("是否收款"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(3, _T("是否开发票"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(4, _T("操作时间"), LVCFMT_LEFT,200);
	CTime time1 = CTime::GetCurrentTime();
	m_time_start = time1;
	m_time_end = time1;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_FI::OnFiadd() 
{
	UpdateData();
	if(m_strlistid_add.IsEmpty())
	{
		MessageBox("请输入订单号：","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_LISTID_ADD)->SetFocus();
		return;
	}
	CString strgathering;
	CString strbilling;
	strgathering.Format("%d",m_gathering);
	strbilling.Format("%d",m_billing);
	CString curtime;
	CString sql;
	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	mysql_init(&myCont);
	if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
	{
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
		CString strsql ;
		strsql.Format("select now()");
		if(mysql_query(&myCont,strsql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			return;
		}
		result=mysql_store_result(&myCont);//保存查询到的数据到result
		if(result)
		{
			sql_row=mysql_fetch_row(result);
			curtime = sql_row[0];
		}
		else
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			return;
		}

		sql = "select * from fi where listid='" + m_strlistid_add +"'";
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			return;
		}
		result=mysql_store_result(&myCont);//保存查询到的数据到result
		if(result)
		{
			unsigned __int64 num = mysql_num_rows(result);//行数
			if(num>=1)
			{
				//修改记录				
				sql.Format("update fi set gathering=\"%s\",billing=\"%s\",optime=\"%s\" where listid=\"%s\" ",strgathering,strbilling,curtime,m_strlistid_add);
				int ret = mysql_query(&myCont,sql);
				const char *error = mysql_error(&myCont);
				if(ret!= 0)
				{
					const char *error = mysql_error(&myCont);
					CString str;
					str.Format("数据库错误(%s)",error);
					MessageBox(str,"提示",MB_OK);
					mysql_close(&myCont);//断开连接
					return;
				}
				if(result!=NULL) mysql_free_result(result);//释放结果资源
				mysql_close(&myCont);//断开连接
				MessageBox("修改记录成功","提示",MB_OK);
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
			return;
		}

		sql.Format("select * from schedule where listid=\"%s\" ",m_strlistid_add);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			return;
		}
		result=mysql_store_result(&myCont);//保存查询到的数据到result
		if(result)
		{
			unsigned __int64 num = mysql_num_rows(result);//行数
			if(num!=1)//
			{
				MessageBox("无此订单或未下单","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_LISTID_ADD)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_LISTID_ADD))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//释放结果资源
				mysql_close(&myCont);//断开连接
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
			return;
		}

		sql.Format("insert into fi values (\"%s\",\"%s\",\"%s\",\"%s\")", m_strlistid_add,strgathering,strbilling,curtime);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
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
		return;
	}
	if(result!=NULL) mysql_free_result(result);//释放结果资源
	mysql_close(&myCont);//断开连接
	MessageBox("增加记录成功","提示",MB_OK);
}

void Dialog_FI::OnExcel() 
{
	CreateExcel("财务统计.xls",&m_listFI);	
}

void Dialog_FI::OnOK() 
{
	m_listFI.DeleteAllItems();
	UpdateData();
	CString starttime;
	starttime.Format("%04d-%02d-%02d",m_time_start.GetYear(),m_time_start.GetMonth(),m_time_start.GetDay());
	CString endtime;
	endtime.Format("%04d-%02d-%02d",m_time_end.GetYear(),m_time_end.GetMonth(),m_time_end.GetDay()+1);
	CString csSql;
	if(m_strlistid_query.IsEmpty())
		csSql.Format("select * from fi where optime>=\"%s\" and optime<=\"%s\" ",starttime,endtime);
	else
		csSql.Format("select * from fi where listid=\"%s\"  ",m_strlistid_query);
	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	int res;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
    {
        mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
        res=mysql_query(&myCont,csSql);//查询
        if(!res)
        {
            result=mysql_store_result(&myCont);//保存查询到的数据到result
		    if(result)
            {
                int j;
                j=mysql_num_fields(result);//查看多少列
				unsigned __int64 num = mysql_num_rows(result);//行数
				int index = 0;
				float money=0, volume=0;
				int number = 0;
                while(sql_row=mysql_fetch_row(result))//获取具体的数据
                {
					CString strindex ;
					strindex.Format("%d",index+1);
					m_listFI.InsertItem(index,strindex);
					int i=0;
					for(i=1;i<=4;i++)
					{
						m_listFI.SetItemText(index,i,sql_row[i-1]);
					}
					if(index%2==0)
						m_listFI.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
					index++;
                }//while				
            }
        }
        else
        {
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
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
		return;
    }
    if(result!=NULL) mysql_free_result(result);//释放结果资源
    mysql_close(&myCont);//断开连接

	return;
	//CDialog::OnOK();
}

BOOL Dialog_FI::PreTranslateMessage(MSG* pMsg) 
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

void Dialog_FI::OnColumnclickListFi(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	listsort(&m_listFI,pNMListView);
	*pResult = 0;
}
