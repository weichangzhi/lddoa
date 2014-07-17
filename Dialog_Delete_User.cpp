// Dialog_Delete_User.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_Delete_User.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Delete_User dialog


CDialog_Delete_User::CDialog_Delete_User(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Delete_User::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Delete_User)
	m_user = _T("");
	//}}AFX_DATA_INIT
}


void CDialog_Delete_User::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Delete_User)
	DDX_Control(pDX, IDOK, m_btnok);
	DDX_Control(pDX, IDCANCEL, m_btncancel);
	DDX_Text(pDX, IDC_EDIT_USER, m_user);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Delete_User, CDialog)
	//{{AFX_MSG_MAP(CDialog_Delete_User)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Delete_User message handlers

BOOL CDialog_Delete_User::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_Delete_User::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	m_user.TrimLeft();
	m_user.TrimRight();
	if (m_user.IsEmpty())
	{	
		MessageBox("请输入用户名","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_USER)->SetFocus();
		return;
	}

	CString sql;
	sql = "delete from userinfo where username='" + m_user +"'";

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
			MessageBox("删除用户成功","提示",MB_OK);
		}
		else
		{
			MessageBox("此用户不存在","提示",MB_OK);
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
	//MessageBox("删除用户成功","提示",MB_OK);
	CDialog::OnOK();
}

BOOL CDialog_Delete_User::PreTranslateMessage(MSG* pMsg) 
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
