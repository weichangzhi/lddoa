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
	m_qc = FALSE;
	m_urgent = FALSE;
	strdepartment = _T("");
	m_permission = 0;
	m_fi = FALSE;
	//}}AFX_DATA_INIT
}


void CDialog_AddUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_AddUser)
	DDX_Control(pDX, IDCANCEL, m_btncan);
	DDX_Control(pDX, IDOK, m_btnok);
	DDX_Control(pDX, IDC_COMBO_DEPARTMENT, m_comDepartment);
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
	DDX_Check(pDX, IDC_CHECK_URGENT, m_urgent);
	DDX_Check(pDX, IDC_CHECK_FI, m_fi);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_AddUser, CDialog)
	//{{AFX_MSG_MAP(CDialog_AddUser)
	ON_CBN_SELCHANGE(IDC_COMBO_DEPARTMENT, OnSelchangeComboDepartment)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_AddUser message handlers

BOOL CDialog_AddUser::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_comDepartment.InsertString(0,"意造销售");
	m_comDepartment.InsertString(1,"电商");
	m_comDepartment.InsertString(2,"运营");
	m_comDepartment.InsertString(3,"加盟");
	m_comDepartment.InsertString(4,"研发");
	m_comDepartment.InsertString(5,"技术部意造");
	m_comDepartment.InsertString(6,"技术部记梦馆");
	m_comDepartment.InsertString(7,"生产部");
	m_comDepartment.InsertString(8,"成品仓");
	m_comDepartment.InsertString(9,"财务");
	m_comDepartment.SetCurSel(0);
	m_save_list = TRUE;
	m_start_list = TRUE;
	m_end_list = TRUE;
	m_modify_list_before = TRUE;
	m_query_list = TRUE;
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
			MessageBox("密码不能为空，请输入密码","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_PASSWD)->SetFocus();
			return;
		}
		if((m_passwd.Compare(m_passwd2))!=0)
		{
			MessageBox("2次密码不一致，请重新输入密码","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_PASSWD2)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_PASSWD2))->SetSel(0, -1);
			return;
		}
		m_username.TrimLeft();
		m_username.TrimRight();
		if (m_username.IsEmpty())
		{	
			MessageBox("请输入用户名","提示",MB_OK);
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
		if(m_urgent) m_permission+=URGENT;
		if(m_fi) m_permission+=FI;


		m_comDepartment.GetWindowText(strdepartment);
		CString sql;
		sql = "select username from userinfo where username='" + m_username +"'";

		MYSQL myCont;
		MYSQL_RES *result;
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
				unsigned __int64 num = mysql_num_rows(result);//行数
				if(num>=1)
				{
					MessageBox("用户名已存在，请重新创建用户名","提示",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_USER_NAME)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_USER_NAME))->SetSel(0, -1);
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

			sql.Format("insert into userinfo values (\"%s\",password(\"%s\"),%d,\"%s\")", m_username,m_passwd,m_permission,strdepartment);
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
		MessageBox("创建用户成功","提示",MB_OK);
		CDialog::OnOK();
}

BOOL CDialog_AddUser::PreTranslateMessage(MSG* pMsg) 
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

void CDialog_AddUser::OnSelchangeComboDepartment() 
{
	UpdateData();
	int indexSel = m_comDepartment.GetCurSel();
	switch(indexSel)
	{
	case 0://意造销售
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
	case 1://电商
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
	case 2://运营
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
	case 3://加盟
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
	case 4://研发
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
	case 5://技术部意造
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
	case 6://技术部记梦馆
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
	case 7://生产部
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
	case 8://成品仓
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
	case 9://财务
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
