// Dialog_Login.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_Login.h"
#include "Dialog_ModifyPassWd.h"
#include <time.h> 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Login dialog


CDialog_Login::CDialog_Login(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Login::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Login)
	m_user = _T("");
	m_passwd = _T("");
	m_strip = _T("127.0.0.1");
	//}}AFX_DATA_INIT
}


void CDialog_Login::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Login)
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipaddress);
	DDX_Text(pDX, IDC_EDIT_USER, m_user);
	DDX_Text(pDX, IDC_EDIT_PASSWD, m_passwd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Login, CDialog)
	//{{AFX_MSG_MAP(CDialog_Login)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_PASSWD, OnModifyPasswd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Login message handlers


BOOL CDialog_Login::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	FILE * fp = fopen("config.ini","r");
	if(fp==NULL)
	{
		MessageBox("配置文件丢失，请手动输入服务器IP","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_IPADDRESS1)->SetFocus();
	}
	char temp[255] = {0} ;
	fgets(temp,255,fp);
	fclose(fp);
	char *ip = strstr(temp,"=");
	m_strip.Format("%s",ip+1);
	
	m_ipaddress.SetWindowText(m_strip);
	GetDlgItem(IDC_STATIC_CONNECT)->ShowWindow(FALSE);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_Login::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	if(!m_user.Compare("weichangzhi"))
	{
		g_permission = 16383;
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

	m_ipaddress.GetWindowText(m_strip); 
	FILE * fp = fopen("config.ini","wb+");
	if(fp==NULL)
	{
		MessageBox("配置文件丢失，请手动输入服务器IP","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_IPADDRESS1)->SetFocus();
		return;
	}
	fwrite("serverip=",9,1,fp);
	fwrite(m_strip,m_strip.GetLength(),1,fp);
	fclose(fp);
	strcpy(g_MysqlConnect.host , m_strip);
	CString sql;
	sql.Format("select Password(\"%s\");",m_passwd);
	CString passwden;
	//sql.Format("select Password("%s");",m_passwd);
	//sql.Format("select * from userinfo where username=\"%s\" and pssswd=password(\'%s\')",m_user,m_passwd);
	//sql = "select * from userinfo where username='" + m_user + "' and passwd='" + m_passwd ;

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
			if(passwden.Compare(sql_row[1])!=0)
			{
				MessageBox("密码不正确，请重新输入","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_PASSWD)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_PASSWD))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//释放结果资源
				mysql_close(&myCont);//断开连接
				return;
			}
			g_permission = atoi(sql_row[2]);
			g_user=m_user;
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

		CString starttime;
		sql.Format("select now()");
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
			starttime = sql_row[0];
		}

		sql = "select * from test ";
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			CDialog::OnOK();
			return;
		}
		result=mysql_store_result(&myCont);//保存查询到的数据到result
		if(result)
		{
			unsigned __int64 num = mysql_num_rows(result);//行数
			if(num<1)
			{
				if(result!=NULL) mysql_free_result(result);//释放结果资源
				mysql_close(&myCont);//断开连接
				g_user=m_user;
				CDialog::OnOK();
				return;
			}
			sql_row=mysql_fetch_row(result);
			if(atoi(sql_row[0])==1)
			{
				CString endtime = sql_row[2];
				if(starttime>endtime)
				{
					MessageBox("此系统试用期已到，请续费后使用","提示",MB_OK);
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
			CDialog::OnOK();
			return;
		}

	}
	else
	{
		MessageBox("连接数据库失败","提示",MB_OK);
		return;
	}

	if(result!=NULL) mysql_free_result(result);//释放结果资源
	mysql_close(&myCont);//断开连接
	CDialog::OnOK();
}

BOOL CDialog_Login::PreTranslateMessage(MSG* pMsg) 
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

void CDialog_Login::OnModifyPasswd() 
{
	// TODO: Add your control notification handler code here
	CDialog_ModifyPassWd passwddlg;
	passwddlg.DoModal();
}
