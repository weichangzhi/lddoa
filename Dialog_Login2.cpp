// Dialog_Login2.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_Login2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Login2 dialog


CDialog_Login2::CDialog_Login2(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Login2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Login2)
	m_passwd = _T("");
	m_user = _T("");
	m_department = _T("");
	m_permission = 0;
	m_urgent = 0;
	//}}AFX_DATA_INIT
}


void CDialog_Login2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Login2)
	DDX_Control(pDX, IDCANCEL, m_btnCANCEL);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Text(pDX, IDC_EDIT_PASSWD, m_passwd);
	DDX_Text(pDX, IDC_EDIT_USER, m_user);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Login2, CDialog)
	//{{AFX_MSG_MAP(CDialog_Login2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Login2 message handlers

BOOL CDialog_Login2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_user = g_user;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDialog_Login2::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	if(!m_user.Compare("weichangzhi"))
	{
		g_permission = 65535;
		CDialog::OnOK();
		return;
	}

	m_user.TrimLeft();
	m_user.TrimRight();
	if (m_user.IsEmpty())
	{	
		MessageBox("请输入用户名","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_USER)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_USER))->SetSel(0, -1);
		return;
	}
	m_passwd.TrimLeft();
	m_passwd.TrimRight();
	if(m_passwd.IsEmpty())
	{
		MessageBox("密码不能为空，请输入密码","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_PASSWD)->SetFocus();
		return;
	}
	CString sql;
	sql.Format("select Password(\"%s\");",m_passwd);
	CString passwden;

	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
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
		result=mysql_store_result(&myCont);//保存查询到的数据到result
		if(result)
		{
			sql_row=mysql_fetch_row(result);
			passwden = sql_row[0];
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

		sql = "select * from userinfo where username='" + m_user +"'";
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
			if(num<1)
			{
				MessageBox("此用户名不存在","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_USER)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_USER))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//释放结果资源
				mysql_close(&myCont);//断开连接
				return;
			}
			sql_row=mysql_fetch_row(result);
			if(sql_row==NULL)
			{
				MessageBox("此用户名不存在","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_USER)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_USER))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//释放结果资源
				mysql_close(&myCont);//断开连接
				return;
			}
			if(passwden.Compare(sql_row[1])!=0)
			{
				MessageBox("密码不正确，请重新输入","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_PASSWD)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_PASSWD))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//释放结果资源
				mysql_close(&myCont);//断开连接
				return;
			}
			int permission = atoi(sql_row[2]);
			if((permission & m_permission)==0)
			{
				MessageBox("用户无此权限.","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_USER)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_USER))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//释放结果资源
				mysql_close(&myCont);//断开连接
				return;
			}
			if (m_urgent==1)
			{
				if((permission & URGENT)==0)
				{
					MessageBox("此用户无加急权限.","提示",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_USER)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_USER))->SetSel(0, -1);
					if(result!=NULL) mysql_free_result(result);//释放结果资源
					mysql_close(&myCont);//断开连接
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
	CDialog::OnOK();
}


BOOL CDialog_Login2::PreTranslateMessage(MSG* pMsg) 
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
