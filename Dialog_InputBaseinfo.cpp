// Dialog_InputBaseinfo.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_InputBaseinfo.h"
#include "Dialog_Login2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_InputBaseinfo dialog


CDialog_InputBaseinfo::CDialog_InputBaseinfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_InputBaseinfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_InputBaseinfo)
	m_ListID = _T("");
	m_ClientName = _T("");
	m_Phone = _T("");
	m_department = _T("");
	m_adress = _T("");
	m_Mondy = _T("");
	m_reveivedate = 0;
	m_enddate = 0;
	m_size = _T("");
	m_material = _T("");
	m_color = _T("");
	m_paint = _T("");
	m_bottom = _T("");
	m_accuracy = _T("");
	m_errorrange = _T("");
	m_other = _T("");
	m_totelnumber = _T("");
	m_bModify = 0;
	//}}AFX_DATA_INIT
}


void CDialog_InputBaseinfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_InputBaseinfo)
	DDX_Text(pDX, IDC_EDIT_LISTID, m_ListID);
	DDX_Text(pDX, IDC_EDIT_CLIENTNAME, m_ClientName);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_Phone);
	DDX_Text(pDX, IDC_EDIT_DEPARTMENT, m_department);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_adress);
	DDX_Text(pDX, IDC_EDIT_MONDY, m_Mondy);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_RECEIVEDATE, m_reveivedate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ENDDATE, m_enddate);
	DDX_Text(pDX, IDC_EDIT_SIZE, m_size);
	DDX_Text(pDX, IDC_EDIT_MATERIAL, m_material);
	DDX_Text(pDX, IDC_EDIT_COLOR, m_color);
	DDX_Text(pDX, IDC_EDIT_PAINT, m_paint);
	DDX_Text(pDX, IDC_EDIT_BOTTOM, m_bottom);
	DDX_Text(pDX, IDC_EDIT_ACCURACY, m_accuracy);
	DDX_Text(pDX, IDC_EDIT_ERRORRANGE, m_errorrange);
	DDX_Text(pDX, IDC_RICHEDIT_OTHER, m_other);
	DDX_Text(pDX, IDC_EDIT1_TOTELNUMBER, m_totelnumber);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_InputBaseinfo, CDialog)
	//{{AFX_MSG_MAP(CDialog_InputBaseinfo)
	ON_BN_CLICKED(IDC_BUTTON_SUBMITLIST, OnSubmitlist)
	ON_BN_CLICKED(IDC_BUTTON_START_LIST, OnStartList)
	ON_BN_CLICKED(IDC_BUTTON_END_LIST, OnEndList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_InputBaseinfo message handlers

BOOL CDialog_InputBaseinfo::OnInitDialog() 
{
	
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	if(m_bModify==0)
	{
		SetWindowText("新增订单信息");
		GetDlgItem(IDC_BUTTON_SUBMITLIST)->SetWindowText("保存订单") ;
		CTime time1 = CTime::GetCurrentTime();
		m_reveivedate = time1;
		m_enddate = time1;
	}
	else
	{
		GetDlgItem(IDC_EDIT_LISTID)->EnableWindow(FALSE);
		SetWindowText("修改订单信息");
		GetDlgItem(IDC_BUTTON_SUBMITLIST)->SetWindowText("修改订单") ;
		CTime timeTmp(atoi(m_str_reveive_time.Mid(0,4)),atoi(m_str_reveive_time.Mid(5,2)),atoi(m_str_reveive_time.Mid(8,2)),0,0,0,0);
		m_reveivedate = timeTmp;
		CTime timeTmp1(atoi(m_str_end_date.Mid(0,4)),atoi(m_str_end_date.Mid(5,2)),atoi(m_str_end_date.Mid(8,2)),0,0,0,0);
		m_enddate = timeTmp1;
	}
	
/*
	GetDlgItem(IDC_BUTTON_TC_POST)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PD_POST)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STORAGE_POST)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEND_POST)->EnableWindow(FALSE);
*/
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_InputBaseinfo::OnSubmitlist() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	m_str_reveive_time.Format("%04d-%02d-%02d",m_reveivedate.GetYear(),m_reveivedate.GetMonth(),m_reveivedate.GetDay());
	m_str_end_date.Format("%04d-%02d-%02d",m_enddate.GetYear(),m_enddate.GetMonth(),m_enddate.GetDay());

	if (!m_bModify)//插入
	{
		CString sql;
		sql.Format("insert into baseinfo values (%s,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\")", \
			m_ListID,m_ClientName,m_str_reveive_time,m_str_end_date,m_department,m_adress,m_Phone,m_Mondy,m_size, \
			m_material,m_color,m_paint,m_bottom,m_accuracy,m_errorrange,m_other);

		MYSQL myCont;
		mysql_init(&myCont);
		if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
		{
			mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
			if(mysql_query(&myCont,sql)!= 0)
			{
				const char *error = mysql_error(&myCont);
				CString str;
				str.Format("数据库错误(%s)",error);
				MessageBox(str,"提示",MB_OK);
				mysql_close(&myCont);//断开连接
				return;
			}
			if(mysql_affected_rows(&myCont)>0)
			{
				MessageBox("保存订单成功","提示",MB_OK);
			}
			else
			{
				MessageBox("保存订单失败","提示",MB_OK);
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
		mysql_close(&myCont);//断开连接
		//MessageBox("保存订单成功","提示",MB_OK);
	}
	else//修改
	{
		CString sql;
		sql.Format("update baseinfo set listid=\"%s\",clientname=\"%s\",reveivedate=\"%s\",enddate=\"%s\",department=\"%s\"  \
			,address=\"%s\",phone=\"%s\",money=\"%s\",size=\"%s\",material=\"%s\",color=\"%s\" \
			,paint=\"%s\",bottom=\"%s\",accuracy=\"%s\",errorrange=\"%s\",other=\"%s\" where listid=\"%s\" ", \
				m_ListID,m_ClientName,m_str_reveive_time,m_str_end_date,m_department,m_adress,m_Phone,m_Mondy,m_size, \
			m_material,m_color,m_paint,m_bottom,m_accuracy,m_errorrange,m_other,m_ListID);

		MYSQL myCont;
		mysql_init(&myCont);
		if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
		{
			mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
			if(mysql_query(&myCont,sql)!= 0)
			{
				const char *error = mysql_error(&myCont);
				CString str;
				str.Format("数据库错误(%s)",error);
				MessageBox(str,"提示",MB_OK);
				mysql_close(&myCont);//断开连接
				return;
			}
			if(mysql_affected_rows(&myCont)>0)
			{
				MessageBox("修改订单成功","提示",MB_OK);
			}
			else
			{
				MessageBox("修改订单失败","提示",MB_OK);
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
		mysql_close(&myCont);//断开连接
		//MessageBox("修改订单成功","提示",MB_OK); 
	}
}

void CDialog_InputBaseinfo::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDialog_InputBaseinfo::OnStartList() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int totelnumber = atoi(m_totelnumber);
	if(totelnumber==0)
	{
		MessageBox("订单总数非法，请重新输入","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT1_TOTELNUMBER)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT1_TOTELNUMBER))->SetSel(0, -1);
		return;
	}
	CDialog_Login2 login2;
	login2.m_department = "业务部";
	if (login2.DoModal()!=IDOK)
	{
		return;
	}
	
	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	mysql_init(&myCont);
	if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
	{
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
		CString sql;
		sql.Format("insert into schedule(listid,listname,totelnumber,businessnumber,tcnumber,pdnumber,storagenumber,sendnumber,post,end) \
		values (\"%s\",\"%s\",%d,0,%d,0,0,0,0,0)",m_ListID,"订单名称",totelnumber,totelnumber);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			return;
		}

		CTime time = CTime::GetCurrentTime();
		CString starttime;

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
			starttime = sql_row[0];
		}


		sql.Format("insert into scheduledetail(listid,businessendtime,businessnumber,businesspeople,tcstarttime) \
		values (\"%s\",\"%s\",%d,\"%s\",\"%s\")",m_ListID,starttime,totelnumber,login2.m_user,starttime);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			return;
		}
		if(mysql_affected_rows(&myCont)>0)
		{
			MessageBox("下单成功","提示",MB_OK);
		}
		else
		{
			MessageBox("下单失败","提示",MB_OK);
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
	mysql_close(&myCont);//断开连接
	//MessageBox("下单成功","提示",MB_OK);

}

void CDialog_InputBaseinfo::OnEndList() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CDialog_Login2 login2;
	login2.m_department = "业务部";
	if (login2.DoModal()!=IDOK)
	{
		return;
	}
	

	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	mysql_init(&myCont);
	if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
	{
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
		CString sql;
		CTime time = CTime::GetCurrentTime();
		CString starttime;

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
			starttime = sql_row[0];
		}

		sql.Format("update schedule set end=%d where listid=\"%s\" " ,1,m_ListID);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			return;
		}
		if(mysql_affected_rows(&myCont)>0)
		{
			MessageBox("结单成功","提示",MB_OK);
		}
		else
		{
			MessageBox("结单失败","提示",MB_OK);
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
	mysql_close(&myCont);//断开连接
	//MessageBox("结单成功","提示",MB_OK);
	
}

int CDialog_InputBaseinfo::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DoModal();
}

void CDialog_InputBaseinfo::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL CDialog_InputBaseinfo::PreTranslateMessage(MSG* pMsg) 
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
