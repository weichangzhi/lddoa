// DIALOG_CLIENT.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "DIALOG_CLIENT.h"
//#include "DIALOG_INPUT_CLIENT.h"
#include "Dialog_AddUser.h"
//#include "Dialog_ModifyPassWd.h"
#include "Dialog_Delete_User.h"
#include "Dialog_ModifyPW_Admin.h"
#include "Dialog_Modify_Permission.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIALOG_CLIENT dialog


CDIALOG_CLIENT::CDIALOG_CLIENT(CWnd* pParent /*=NULL*/)
	: CDialog(CDIALOG_CLIENT::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDIALOG_CLIENT)
	m_strinput = _T("");
	//}}AFX_DATA_INIT
}


void CDIALOG_CLIENT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDIALOG_CLIENT)
	DDX_Control(pDX, IDC_BUTTON1, m_btn1);
	DDX_Control(pDX, IDC_EXCEL, m_btnexcel);
	DDX_Control(pDX, IDC_BUTTON_MODIFY_PASSWD, m_btnmodifypasswd);
	DDX_Control(pDX, IDC_BUTTON_DELETE_USER, m_btndel);
	DDX_Control(pDX, IDC_BUTTON_CLIENT_SELECT, m_btnquery);
	DDX_Control(pDX, IDC_BUTTON_CLIENT_ADD, m_btnadd);
	DDX_Control(pDX, IDC_LIST_CLIENT, m_list_Clinet);
	DDX_Text(pDX, IDC_EDIT_CLIENT, m_strinput);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDIALOG_CLIENT, CDialog)
	//{{AFX_MSG_MAP(CDIALOG_CLIENT)
	ON_BN_CLICKED(IDC_BUTTON_CLIENT_ADD, OnButtonClientAdd)
	ON_BN_CLICKED(IDC_BUTTON_CLIENT_SELECT, OnButtonClientSelect)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CLIENT, OnDblclkListClient)
	ON_COMMAND(ID_MENUITEM_INPUTSELL,OnDelete)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CLIENT, OnRclickListClient)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_CLIENT, OnColumnclickListClient)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_PASSWD, OnModifyPasswd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_USER, OnDeleteUser)
	ON_BN_CLICKED(IDC_BUTTON1, OnModifyPermission)
	ON_BN_CLICKED(IDC_EXCEL, OnExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDIALOG_CLIENT message handlers

BOOL CDIALOG_CLIENT::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if((g_permission & PERMISSION)==0)
	{
		GetDlgItem(IDC_BUTTON_CLIENT_SELECT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CLIENT_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_MODIFY_PASSWD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_DELETE_USER)->EnableWindow(FALSE);
	}
	m_list_Clinet.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list_Clinet.InsertColumn(0, _T("序号"), LVCFMT_LEFT,60);
	m_list_Clinet.InsertColumn(1, _T("姓名"), LVCFMT_LEFT,100);
	m_list_Clinet.InsertColumn(2, _T("部门"), LVCFMT_LEFT,100);
	m_list_Clinet.InsertColumn(3, _T("权限"), LVCFMT_LEFT,1000);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDIALOG_CLIENT::OnButtonClientAdd() 
{
	// TODO: Add your control notification handler code here
	CDialog_AddUser adduser;
	if(adduser.DoModal()==IDOK)
	{
		m_list_Clinet.DeleteAllItems();
		m_list_Clinet.InsertItem(0,"1");
		m_list_Clinet.SetItemText(0,1,adduser.m_username);
		m_list_Clinet.SetItemText(0,2,adduser.strdepartment);
		//m_list_Clinet.InsertItem(0,adduser.m_username);
		int permission = adduser.m_permission;
		CString strPermission = "";
		int i=0;
		for(i=0;i<PERMISSION_NUMBER;i++)
		{
			if(permission & g_PermissionLimit[i].value)
			{
				strPermission += g_PermissionLimit[i].info;
				strPermission += ", ";
			}
		}

		m_list_Clinet.SetItemText(0,3,strPermission);
	}
	return;
}

void CDIALOG_CLIENT::OnButtonClientSelect() 
{
	// TODO: Add your control notification handler code here
	m_list_Clinet.DeleteAllItems();
	UpdateData();
	CString csSql;
	if(m_strinput.IsEmpty()) 
		csSql.Format("select * from userinfo");	
	else
		csSql.Format("select * from userinfo where username=\"%s\"",m_strinput);	
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
                int i,j;
                j=mysql_num_fields(result);//查看多少列
				unsigned __int64 num = mysql_num_rows(result);//行数
				int index = 0;
                while(sql_row=mysql_fetch_row(result))//获取具体的数据
                {
					CString strindex ;
					strindex.Format("%d",index+1);
					m_list_Clinet.InsertItem(index,strindex);
                    for(i=0;i<j;i++)
                    {
						if(i==0)
						{
							m_list_Clinet.SetItemText(index,1,sql_row[i]);
						}
						else if(i==2)
						{
							int permission = atoi(sql_row[i]);
							CString strPermission = "";
							int i=0;
							for(i=0;i<PERMISSION_NUMBER;i++)
							{
								if(permission & g_PermissionLimit[i].value)
								{
									strPermission += g_PermissionLimit[i].info;
									strPermission += ", ";
								}
							}
							m_list_Clinet.SetItemText(index,3,strPermission);
						}
						else if (i==3)
						{
							m_list_Clinet.SetItemText(index,2,sql_row[i]);
						}
                    }
					if(index%2==0)
						m_list_Clinet.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
					index++;
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

	return;
}


void CDIALOG_CLIENT::OnDblclkListClient(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	return;
	int sel=m_list_Clinet.GetSelectionMark();
	if(sel==-1) return ;
/*	CDIALOG_INPUT_CLIENT InputClient;
	InputClient.m_bModify = 1;
	InputClient.m_dLogId         = atoi(m_list_Clinet.GetItemText(sel,0));
	InputClient.m_strCompanyName = m_list_Clinet.GetItemText(sel,1);
	InputClient.m_strTaxIndex    = m_list_Clinet.GetItemText(sel,2);
	InputClient.m_strBank        = m_list_Clinet.GetItemText(sel,3);
	InputClient.m_strAddress     = m_list_Clinet.GetItemText(sel,4);
	InputClient.m_strReceiver    = m_list_Clinet.GetItemText(sel,5);
	InputClient.m_strMail        = m_list_Clinet.GetItemText(sel,6);
	if(InputClient.DoModal()==IDOK)
	{
		if(MessageBox("确定要修改用户资料?","提示",MB_OKCANCEL)==IDOK)
		{
			CString sql;	
			sql.Format("update client set companyname=\"%s\",taxindex=\"%s\",bank_no=\"%s\",address_pho=\"%s\",receiver=\"%s\",mail_phone=\"%s\" where logid=%d",
				InputClient.m_strCompanyName,InputClient.m_strTaxIndex,InputClient.m_strBank,InputClient.m_strAddress,InputClient.m_strReceiver,InputClient.m_strMail,InputClient.m_dLogId);
			//if(!g_adoDataSet.ExecSql(sql))
			{
				MessageBox("修改数据库失败","提示",MB_OK);
				return ;
			}
			CString strLogID ;
			strLogID.Format("%d",InputClient.m_dLogId);
			m_list_Clinet.SetItemText(sel,0,strLogID);
			m_list_Clinet.SetItemText(sel,1,InputClient.m_strCompanyName);
			m_list_Clinet.SetItemText(sel,2,InputClient.m_strTaxIndex);
			m_list_Clinet.SetItemText(sel,3,InputClient.m_strBank);
			m_list_Clinet.SetItemText(sel,4,InputClient.m_strAddress);
			m_list_Clinet.SetItemText(sel,5,InputClient.m_strReceiver);
			m_list_Clinet.SetItemText(sel,6,InputClient.m_strMail);
		}
	}
	*/
	*pResult = 0;
}

void CDIALOG_CLIENT::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}

void CDIALOG_CLIENT::OnRclickListClient(NMHDR* pNMHDR, LRESULT* pResult) 
{
	return;
	// TODO: Add your control notification handler code here
	CMenu       menu ,* pSubMenu;//定义下面要用到的cmenu对象	
	menu.LoadMenu(IDR_MENU_POST);//装载自定义的右键菜单
	pSubMenu = menu.GetSubMenu(0);//获取第一个弹出菜单，所以第一个菜单必须有子菜单	
    CPoint oPoint;//定义一个用于确定光标位置的位置	
    GetCursorPos( &oPoint);//获取当前光标的位置，以便使得菜单可以跟随光标
	int istat=m_list_Clinet.GetSelectionMark();//用istat存放当前选定的是第几项	
	if(istat == -1) return;
	pSubMenu->TrackPopupMenu (TPM_LEFTALIGN, oPoint.x, oPoint.y, this); //在指定位置显示弹出菜单
	*pResult = 0;
}

void CDIALOG_CLIENT::OnDelete()
{
	return;
	int istat=m_list_Clinet.GetSelectionMark();
	if(istat == -1) return;
	CString strComName = m_list_Clinet.GetItemText(istat,1);
	CString strTips ;
	strTips.Format("确定要删除%s这个客户吗?",strComName);
	int ret = MessageBox(strTips,"提示",MB_OKCANCEL);
	if (ret==IDOK)
	{
		int dLogID  = atoi(m_list_Clinet.GetItemText(istat,0));
		CString sql;
		sql.Format("delete from client where logid=%d",dLogID);
//		if(!g_adoDataSet.ExecSql(sql))
		{
			MessageBox("删除数据库失败","提示",MB_OK);
			return ;
		}
		m_list_Clinet.DeleteItem(istat);
		strTips.Format("删除客户%s成功.",strComName);
		MessageBox(strTips,"提示",MB_OK);
	}
	
}

void CDIALOG_CLIENT::OnColumnclickListClient(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	listsort(&m_list_Clinet,pNMListView);
	*pResult = 0; 
}

void CDIALOG_CLIENT::OnModifyPasswd() 
{
	// TODO: Add your control notification handler code here
	CDialog_ModifyPW_Admin modidypasswd;
	modidypasswd.DoModal();
}

void CDIALOG_CLIENT::OnDeleteUser() 
{
	// TODO: Add your control notification handler code here
	CDialog_Delete_User deleteuser;
	deleteuser.DoModal();
}

BOOL CDIALOG_CLIENT::PreTranslateMessage(MSG* pMsg) 
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

void CDIALOG_CLIENT::OnModifyPermission() 
{
	CDialog_Modify_Permission	dlg;
	dlg.DoModal();
}

void CDIALOG_CLIENT::OnExcel() 
{
	CreateExcel("权限查询.xls",&m_list_Clinet);
}
