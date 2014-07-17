// Dialog_Modify_Permission.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_Modify_Permission.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Modify_Permission dialog


CDialog_Modify_Permission::CDialog_Modify_Permission(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Modify_Permission::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Modify_Permission)
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
	m_qc = FALSE;
	m_urgent = FALSE;
	m_permission = 0;
	m_fi = FALSE;
	//}}AFX_DATA_INIT
}


void CDialog_Modify_Permission::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Modify_Permission)
	DDX_Control(pDX, IDOK, m_btnok);
	DDX_Control(pDX, IDCANCEL, m_btncancel);
	DDX_Control(pDX, ID_MODIFY, m_btnmodify);
	DDX_Control(pDX, IDC_COMBO_DEPARTMENT, m_department);
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
	DDX_Check(pDX, IDC_CHECK_URGENT, m_urgent);
	DDX_Check(pDX, IDC_CHECK_FI, m_fi);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Modify_Permission, CDialog)
	//{{AFX_MSG_MAP(CDialog_Modify_Permission)
	ON_BN_CLICKED(IDOK, OnQueryPermission)
	ON_BN_CLICKED(ID_MODIFY, OnOK)
	ON_CBN_SELCHANGE(IDC_COMBO_DEPARTMENT, OnSelchangeComboDepartment)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Modify_Permission message handlers

void CDialog_Modify_Permission::OnOK() 
{
		UpdateData();
		
		m_username.TrimLeft();
		m_username.TrimRight();
		if (m_username.IsEmpty())
		{	
			MessageBox("�������û���","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_USER_NAME)->SetFocus();
			return;
		}
		m_permission = 0;
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
		if(m_urgent) m_permission+=URGENT;
		if(m_fi) m_permission+=FI;
		CString strdepartment ;
		m_department.GetWindowText(strdepartment);
		CString sql;
		sql = "select * from userinfo where username='" + m_username +"'";

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
					MessageBox("���û��������ڣ��������û�","��ʾ",MB_OK);
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

			sql.Format("update userinfo set permission=%d,department=\"%s\" where username=\"%s\" " ,m_permission,strdepartment,m_username);
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
				MessageBox("�޸�Ȩ�޳ɹ�","��ʾ",MB_OK);
			}
			else
			{
				MessageBox("�޸�Ȩ��ʧ��","��ʾ",MB_OK);
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
		//MessageBox("�޸�Ȩ�޳ɹ�","��ʾ",MB_OK);
		CDialog::OnOK();
}

void CDialog_Modify_Permission::OnQueryPermission() 
{
	((CButton*)GetDlgItem(IDC_CHECK_DEL_LIST))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_END_LIST))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_MODIFY_LIST_AFTER))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_MODIFY_LIST_BEFORE))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_POST_PD))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_POST_SEND))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_POST_STORAGE))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_POST_TC))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_QUERY_LIST))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_REFUND))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_SAVE_LIST))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_START_LIST))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_PERMISSION))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_QC))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_URGENT))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CHECK_FI))->SetCheck(0);
	UpdateData();

	m_username.TrimLeft();
	m_username.TrimRight();
	if (m_username.IsEmpty())
	{	
		MessageBox("�������û���","��ʾ",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_USER_NAME)->SetFocus();
		return;
	}

	CString sql;
	sql = "select permission,department from userinfo where username='" + m_username +"'";

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
			unsigned __int64 num = mysql_num_rows(result);//����
			if(num<1)
			{
				MessageBox("���û��������ڣ��������û�","��ʾ",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_USER_NAME)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_USER_NAME))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
				mysql_close(&myCont);//�Ͽ�����
				return;
			}
			sql_row=mysql_fetch_row(result);
			if(sql_row==NULL)
			{
				MessageBox("���û��������ڣ��������û�","��ʾ",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_USER_NAME)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_USER_NAME))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
				mysql_close(&myCont);//�Ͽ�����
				return;
			}
			m_permission = atoi(sql_row[0]);
			CString strdepartment = sql_row[1];

			if(strdepartment.Compare("��������")==0)
				m_department.SetCurSel(0);
			else if(strdepartment.Compare("����")==0)
				m_department.SetCurSel(1);
			else if(strdepartment.Compare("��Ӫ")==0)
				m_department.SetCurSel(2);
			else if(strdepartment.Compare("����")==0)
				m_department.SetCurSel(3);
			else if(strdepartment.Compare("�з�")==0)
				m_department.SetCurSel(4);
			else if(strdepartment.Compare("����������")==0)
				m_department.SetCurSel(5);
			else if(strdepartment.Compare("���������ι�")==0)
				m_department.SetCurSel(6);
			else if(strdepartment.Compare("������")==0)
				m_department.SetCurSel(7);
			else if(strdepartment.Compare("��Ʒ��")==0)
				m_department.SetCurSel(8);
			else if(strdepartment.Compare("����")==0)
				m_department.SetCurSel(9);
			
			if(m_permission & DEL_LIST)	((CButton*)GetDlgItem(IDC_CHECK_DEL_LIST))->SetCheck(1);
			if(m_permission & END_LIST)	((CButton*)GetDlgItem(IDC_CHECK_END_LIST))->SetCheck(1);
			if(m_permission & MODIFY_LIST_AFTER)	((CButton*)GetDlgItem(IDC_CHECK_MODIFY_LIST_AFTER))->SetCheck(1);
			if(m_permission & MODIFY_LIST_BEFORE)	((CButton*)GetDlgItem(IDC_CHECK_MODIFY_LIST_BEFORE))->SetCheck(1);
			if(m_permission & POST_PD)	((CButton*)GetDlgItem(IDC_CHECK_POST_PD))->SetCheck(1);
			if(m_permission & POST_SEND)	((CButton*)GetDlgItem(IDC_CHECK_POST_SEND))->SetCheck(1);
			if(m_permission & POST_STORAGE)	((CButton*)GetDlgItem(IDC_CHECK_POST_STORAGE))->SetCheck(1);
			if(m_permission & POST_TC)	((CButton*)GetDlgItem(IDC_CHECK_POST_TC))->SetCheck(1);
			if(m_permission & QUERY_LIST)	((CButton*)GetDlgItem(IDC_CHECK_QUERY_LIST))->SetCheck(1);
			if(m_permission & REFUND)	((CButton*)GetDlgItem(IDC_CHECK_REFUND))->SetCheck(1);
			if(m_permission & SAVE_LIST)	((CButton*)GetDlgItem(IDC_CHECK_SAVE_LIST))->SetCheck(1);
			if(m_permission & START_LIST)	((CButton*)GetDlgItem(IDC_CHECK_START_LIST))->SetCheck(1);
			if(m_permission & PERMISSION)	((CButton*)GetDlgItem(IDC_CHECK_PERMISSION))->SetCheck(1);
			if(m_permission & QC)	((CButton*)GetDlgItem(IDC_CHECK_QC))->SetCheck(1);
			if(m_permission & URGENT)	((CButton*)GetDlgItem(IDC_CHECK_URGENT))->SetCheck(1);
			if(m_permission & FI)	((CButton*)GetDlgItem(IDC_CHECK_FI))->SetCheck(1);
			UpdateData();
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
}

BOOL CDialog_Modify_Permission::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_department.InsertString(0,"��������");
	m_department.InsertString(1,"����");
	m_department.InsertString(2,"��Ӫ");
	m_department.InsertString(3,"����");
	m_department.InsertString(4,"�з�");
	m_department.InsertString(5,"����������");
	m_department.InsertString(6,"���������ι�");
	m_department.InsertString(7,"������");
	m_department.InsertString(8,"��Ʒ��");
	m_department.InsertString(9,"����");
	m_department.SetCurSel(0);

	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDialog_Modify_Permission::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN) 
	{  
		switch(pMsg->wParam) 
		{  
		case VK_RETURN: //�س�  
			return TRUE;  
		case VK_ESCAPE: //ESC  
			return TRUE;  
		}  
	}	
		
	return CDialog::PreTranslateMessage(pMsg);
}

void CDialog_Modify_Permission::OnSelchangeComboDepartment() 
{
	UpdateData();
	int indexSel = m_department.GetCurSel();
	switch(indexSel)
	{
	case 0://��������
		m_del_list = FALSE;
		m_end_list = TRUE;
		m_modify_list_after = FALSE;
		m_modify_list_before = TRUE;
		m_post_pd = FALSE;
		m_post_send = FALSE;
		m_post_storage = FALSE;
		m_post_tc = FALSE;
		m_query_list = TRUE;
		m_refund = FALSE;
		m_save_list = TRUE;
		m_start_list = TRUE;
		m_Bpermission = FALSE;
		m_qc = FALSE;
		m_urgent = FALSE;
		m_fi = FALSE;
		break;
	case 1://����
		m_del_list = FALSE;
		m_end_list = TRUE;
		m_modify_list_after = FALSE;
		m_modify_list_before = TRUE;
		m_post_pd = FALSE;
		m_post_send = FALSE;
		m_post_storage = FALSE;
		m_post_tc = FALSE;
		m_query_list = TRUE;
		m_refund = FALSE;
		m_save_list = TRUE;
		m_start_list = TRUE;
		m_Bpermission = FALSE;
		m_qc = FALSE;
		m_urgent = FALSE;
		m_fi = FALSE;
		break;
	case 2://��Ӫ
		m_del_list = FALSE;
		m_end_list = TRUE;
		m_modify_list_after = FALSE;
		m_modify_list_before = TRUE;
		m_post_pd = FALSE;
		m_post_send = FALSE;
		m_post_storage = FALSE;
		m_post_tc = FALSE;
		m_query_list = TRUE;
		m_refund = FALSE;
		m_save_list = TRUE;
		m_start_list = TRUE;
		m_Bpermission = FALSE;
		m_qc = FALSE;
		m_urgent = FALSE;
		m_fi = FALSE;
		break;
	case 3://����
		m_del_list = FALSE;
		m_end_list = TRUE;
		m_modify_list_after = FALSE;
		m_modify_list_before = TRUE;
		m_post_pd = FALSE;
		m_post_send = FALSE;
		m_post_storage = FALSE;
		m_post_tc = FALSE;
		m_query_list = TRUE;
		m_refund = FALSE;
		m_save_list = TRUE;
		m_start_list = TRUE;
		m_Bpermission = FALSE;
		m_qc = FALSE;
		m_urgent = FALSE;
		m_fi = FALSE;
		break;
	case 4://�з�
		m_del_list = FALSE;
		m_end_list = TRUE;
		m_modify_list_after = FALSE;
		m_modify_list_before = TRUE;
		m_post_pd = FALSE;
		m_post_send = FALSE;
		m_post_storage = FALSE;
		m_post_tc = TRUE;
		m_query_list = FALSE;
		m_refund = FALSE;
		m_save_list = TRUE;
		m_start_list = TRUE;
		m_Bpermission = FALSE;
		m_qc = FALSE;
		m_urgent = FALSE;
		m_fi = FALSE;
		break;
	case 5://����������
		m_del_list = FALSE;
		m_end_list = FALSE;
		m_modify_list_after = FALSE;
		m_modify_list_before = FALSE;
		m_post_pd = FALSE;
		m_post_send = FALSE;
		m_post_storage = FALSE;
		m_post_tc = TRUE;
		m_query_list = FALSE;
		m_refund = FALSE;
		m_save_list = FALSE;
		m_start_list = FALSE;
		m_Bpermission = FALSE;
		m_qc = FALSE;
		m_urgent = FALSE;
		m_fi = FALSE;
		break;
	case 6://���������ι�
		m_del_list = FALSE;
		m_end_list = FALSE;
		m_modify_list_after = FALSE;
		m_modify_list_before = FALSE;
		m_post_pd = FALSE;
		m_post_send = FALSE;
		m_post_storage = FALSE;
		m_post_tc = TRUE;
		m_query_list = FALSE;
		m_refund = FALSE;
		m_save_list = FALSE;
		m_start_list = FALSE;
		m_Bpermission = FALSE;
		m_qc = FALSE;
		m_urgent = FALSE;
		m_fi = FALSE;
		break;
	case 7://������
		m_del_list = FALSE;
		m_end_list = FALSE;
		m_modify_list_after = FALSE;
		m_modify_list_before = FALSE;
		m_post_pd = TRUE;
		m_post_send = FALSE;
		m_post_storage = FALSE;
		m_post_tc = FALSE;
		m_query_list = FALSE;
		m_refund = FALSE;
		m_save_list = FALSE;
		m_start_list = FALSE;
		m_Bpermission = FALSE;
		m_qc = TRUE;
		m_urgent = FALSE;
		m_fi = FALSE;
		break;
	case 8://��Ʒ��
		m_del_list = FALSE;
		m_end_list = FALSE;
		m_modify_list_after = FALSE;
		m_modify_list_before = FALSE;
		m_post_pd = FALSE;
		m_post_send = TRUE;
		m_post_storage = TRUE;
		m_post_tc = FALSE;
		m_query_list = FALSE;
		m_refund = FALSE;
		m_save_list = FALSE;
		m_start_list = FALSE;
		m_Bpermission = FALSE;
		m_qc = FALSE;
		m_urgent = FALSE;
		m_fi = FALSE;
		break;
	case 9://����
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
		m_qc = FALSE;
		m_urgent = FALSE;
		m_fi = TRUE;
		break;
	default:
		break;
	}
	UpdateData(FALSE);
	
}
