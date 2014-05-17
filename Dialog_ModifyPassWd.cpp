// Dialog_ModifyPassWd.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_ModifyPassWd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_ModifyPassWd dialog


CDialog_ModifyPassWd::CDialog_ModifyPassWd(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_ModifyPassWd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_ModifyPassWd)
	m_new_passwd = _T("");
	m_new_passwd2 = _T("");
	m_passwd = _T("");
	m_user = _T("");
	//}}AFX_DATA_INIT
}


void CDialog_ModifyPassWd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_ModifyPassWd)
	DDX_Text(pDX, IDC_EDIT_NEW_PASSWD, m_new_passwd);
	DDX_Text(pDX, IDC_EDIT_NEW_PASSWD2, m_new_passwd2);
	DDX_Text(pDX, IDC_EDIT_PASSWD, m_passwd);
	DDX_Text(pDX, IDC_EDIT_USER, m_user);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_ModifyPassWd, CDialog)
	//{{AFX_MSG_MAP(CDialog_ModifyPassWd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_ModifyPassWd message handlers

BOOL CDialog_ModifyPassWd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_ModifyPassWd::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	m_user.TrimLeft();
	m_user.TrimRight();
	if (m_user.IsEmpty())
	{	
		MessageBox("�������û���","��ʾ",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_USER)->SetFocus();
		return;
	}

	if(m_passwd.IsEmpty())
	{
		MessageBox("���벻��Ϊ�գ�����������","��ʾ",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_PASSWD)->SetFocus();
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
	sql.Format("select Password(\"%s\");",m_passwd);
	CString passwden;

	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
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
			sql_row=mysql_fetch_row(result);
			passwden = sql_row[0];
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

		sql = "select passwd from userinfo where username='" + m_user +"'";
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
			sql_row=mysql_fetch_row(result);
			if(passwden.Compare(sql_row[0])!=0)
			{
				MessageBox("ԭʼ���벻��ȷ������������","��ʾ",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_PASSWD)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_PASSWD))->SetSel(0, -1);
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
	}
	else
	{
		MessageBox("�������ݿ�ʧ��","��ʾ",MB_OK);
		return;
	}

	if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
	mysql_close(&myCont);//�Ͽ�����
	MessageBox("�޸�����ɹ�","��ʾ",MB_OK);
	CDialog::OnOK();
}

BOOL CDialog_ModifyPassWd::PreTranslateMessage(MSG* pMsg) 
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
