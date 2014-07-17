// Dialog_ModifyPW_Admin.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_ModifyPW_Admin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_ModifyPW_Admin dialog


CDialog_ModifyPW_Admin::CDialog_ModifyPW_Admin(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_ModifyPW_Admin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_ModifyPW_Admin)
	m_user = _T("");
	m_new_passwd = _T("");
	m_new_passwd2 = _T("");
	//}}AFX_DATA_INIT
}


void CDialog_ModifyPW_Admin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_ModifyPW_Admin)
	DDX_Control(pDX, IDCANCEL, m_btnCANCEL);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Text(pDX, IDC_EDIT_USER, m_user);
	DDX_Text(pDX, IDC_EDIT_NEW_PASSWD, m_new_passwd);
	DDX_Text(pDX, IDC_EDIT_NEW_PASSWD2, m_new_passwd2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_ModifyPW_Admin, CDialog)
	//{{AFX_MSG_MAP(CDialog_ModifyPW_Admin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_ModifyPW_Admin message handlers

void CDialog_ModifyPW_Admin::OnOK() 
{
	UpdateData();
	m_user.TrimLeft();
	m_user.TrimRight();
	if (m_user.IsEmpty())
	{	
		MessageBox("�������û���","��ʾ",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_USER)->SetFocus();
		return;
	}

	m_new_passwd.TrimLeft();
	m_new_passwd.TrimRight();
	if(m_new_passwd.IsEmpty())
	{
		MessageBox("�����벻��Ϊ�գ�������������","��ʾ",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_NEW_PASSWD)->SetFocus();
		return;
	}
	if((m_new_passwd.Compare(m_new_passwd2))!=0)
	{
		MessageBox("2�������벻һ�£�����������������","��ʾ",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_NEW_PASSWD2)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_NEW_PASSWD2))->SetSel(0, -1);
		return;
	}

	CString sql;
	sql = "select passwd from userinfo where username='" + m_user +"'";

	MYSQL myCont;
	MYSQL_RES *result;
	mysql_init(&myCont);
	if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
	{
		mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			return;
		}
		result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
		if(result)
		{
			unsigned __int64 num = mysql_num_rows(result);//����
			if(num<1)
			{
				MessageBox("���û���������","��ʾ",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_USER)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_USER))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
				mysql_close(&myCont);//�Ͽ�����
				return;
			}
		}
		else
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			return;
		}
		sql.Format("update userinfo set passwd=password(\"%s\") where username=\"%s\" " ,m_new_passwd,m_user);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			return;
		}
		if(mysql_affected_rows(&myCont)>0)
		{
			MessageBox("�޸�����ɹ�","��ʾ",MB_OK);
		}
		else
		{
			MessageBox("�޸�����ʧ��","��ʾ",MB_OK);
		}
		
	}
	else
	{
		const char *error = mysql_error(&myCont);
		CString str;
		str.Format("���ݿ����(%s)",error);
		MessageBox(str,"��ʾ",MB_OK);
		mysql_close(&myCont);//�Ͽ�����
		return;
	}

	if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
	mysql_close(&myCont);//�Ͽ�����
	//MessageBox("�޸�����ɹ�","��ʾ",MB_OK);
	CDialog::OnOK();	
}

BOOL CDialog_ModifyPW_Admin::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN) 
	{  
		switch(pMsg->wParam) 
		{  
		//case VK_RETURN: //�س�  
		//	return TRUE;  
		case VK_ESCAPE: //ESC  
			return TRUE;  
		}  
	}		
	return CDialog::PreTranslateMessage(pMsg);
}
