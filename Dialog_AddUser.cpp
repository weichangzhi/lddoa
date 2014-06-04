// Dialog_AddUser.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_AddUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_AddUser dialog


CDialog_AddUser::CDialog_AddUser(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_AddUser::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_AddUser)
	m_passwd = _T("");
	m_passwd2 = _T("");
	m_username = _T("");
	m_del_list = FALSE;
	m_end_list = FALSE;
	m_modify_list_after = FALSE;
	m_modify_list_before = FALSE;
	m_post_pd = FALSE;
	m_post_send = FALSE;
	m_post_storage = FALSE;
	m_post_tc = FALSE;
	m_query_list = FALSE;
	m_refund = FALSE;
	m_save_list = FALSE;
	m_start_list = FALSE;
	m_Bpermission = FALSE;
	m_permission = 0;
	m_qc = FALSE;
	//}}AFX_DATA_INIT
}


void CDialog_AddUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_AddUser)
	DDX_Text(pDX, IDC_EDIT_PASSWD, m_passwd);
	DDX_Text(pDX, IDC_EDIT_PASSWD2, m_passwd2);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_username);
	DDX_Check(pDX, IDC_CHECK_DEL_LIST, m_del_list);
	DDX_Check(pDX, IDC_CHECK_END_LIST, m_end_list);
	DDX_Check(pDX, IDC_CHECK_MODIFY_LIST_AFTER, m_modify_list_after);
	DDX_Check(pDX, IDC_CHECK_MODIFY_LIST_BEFORE, m_modify_list_before);
	DDX_Check(pDX, IDC_CHECK_POST_PD, m_post_pd);
	DDX_Check(pDX, IDC_CHECK_POST_SEND, m_post_send);
	DDX_Check(pDX, IDC_CHECK_POST_STORAGE, m_post_storage);
	DDX_Check(pDX, IDC_CHECK_POST_TC, m_post_tc);
	DDX_Check(pDX, IDC_CHECK_QUERY_LIST, m_query_list);
	DDX_Check(pDX, IDC_CHECK_REFUND, m_refund);
	DDX_Check(pDX, IDC_CHECK_SAVE_LIST, m_save_list);
	DDX_Check(pDX, IDC_CHECK_START_LIST, m_start_list);
	DDX_Check(pDX, IDC_CHECK_PERMISSION, m_Bpermission);
	DDX_Check(pDX, IDC_CHECK_QC, m_qc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_AddUser, CDialog)
	//{{AFX_MSG_MAP(CDialog_AddUser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_AddUser message handlers

BOOL CDialog_AddUser::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_AddUser::OnOK() 
{
	// TODO: Add extra validation here
		UpdateData();
		if(m_passwd.IsEmpty())
		{
			MessageBox("���벻��Ϊ�գ�����������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_PASSWD)->SetFocus();
			return;
		}
		if((m_passwd.Compare(m_passwd2))!=0)
		{
			MessageBox("2�����벻һ�£���������������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_PASSWD2)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_PASSWD2))->SetSel(0, -1);
			return;
		}
		m_username.TrimLeft();
		m_username.TrimRight();
		if (m_username.IsEmpty())
		{	
			MessageBox("�������û���","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_USER_NAME)->SetFocus();
			return;
		}
		//m_permission = 0;
		if(m_del_list) m_permission+=DEL_LIST;
		if(m_end_list) m_permission+=END_LIST;
		if(m_modify_list_after) m_permission+=MODIFY_LIST_AFTER;
		if(m_modify_list_before) m_permission+=MODIFY_LIST_BEFORE;
		if(m_post_pd) m_permission+=POST_PD;
		if(m_post_send) m_permission+=POST_SEND;
		if(m_post_storage) m_permission+=POST_STORAGE;
		if(m_post_tc) m_permission+=POST_TC;
		if(m_query_list) m_permission+=QUERY_LIST;
		if(m_refund) m_permission+=REFUND;
		if(m_save_list) m_permission+=SAVE_LIST;
		if(m_start_list) m_permission+=START_LIST;
		if(m_Bpermission) m_permission+=PERMISSION;
		if(m_qc) m_permission+=QC;
		
		CString sql;
		sql = "select username from userinfo where username='" + m_username +"'";

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
				if(num>=1)
				{
					MessageBox("�û����Ѵ��ڣ������´����û���","��ʾ",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_USER_NAME)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_USER_NAME))->SetSel(0, -1);
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

			sql.Format("insert into userinfo values (\"%s\",password(\"%s\"),%d)", m_username,m_passwd,m_permission);
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
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			return;
		}

		if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
		mysql_close(&myCont);//�Ͽ�����
		MessageBox("�����û��ɹ�","��ʾ",MB_OK);
		CDialog::OnOK();
}

BOOL CDialog_AddUser::PreTranslateMessage(MSG* pMsg) 
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
