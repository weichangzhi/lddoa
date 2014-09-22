// Dialog_SendUser.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_SendUser.h"
#include "Dialog_SendUserAdd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_SendUser dialog


Dialog_SendUser::Dialog_SendUser(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_SendUser::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_SendUser)
	m_strUserName = _T("");
	//}}AFX_DATA_INIT
}


void Dialog_SendUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_SendUser)
	DDX_Control(pDX, IDC_LIST_CLIENT, m_listSendUser);
	DDX_Control(pDX, IDC_EXCEL, m_btExcel);
	DDX_Control(pDX, IDC_BUTTON_CLIENT_ADD, m_btAdd);
	DDX_Control(pDX, IDC_BUTTON_CLIENT_SELECT, m_btQuery);
	DDX_Control(pDX, IDC_BUTTON_DELETE_USER, m_btdeleteuser);
	DDX_Control(pDX, IDC_BUTTON_MODIFY, m_btmodify);
	DDX_Text(pDX, IDC_EDIT_CLIENT, m_strUserName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_SendUser, CDialog)
	//{{AFX_MSG_MAP(Dialog_SendUser)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CLIENT, OnRclickListClient)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_CLIENT, OnColumnclickListClient)
	ON_BN_CLICKED(IDC_BUTTON_CLIENT_SELECT, OnButtonClientQuery)
	ON_BN_CLICKED(IDC_BUTTON_CLIENT_ADD, OnButtonClientAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_USER, OnButtonDeleteUser)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnButtonModify)
	ON_BN_CLICKED(IDC_EXCEL, OnExcel)
	ON_COMMAND(IDM_DEL, OnDel)
	ON_COMMAND(IDM_MODIFY, OnModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_SendUser message handlers

BOOL Dialog_SendUser::PreTranslateMessage(MSG* pMsg) 
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

BOOL Dialog_SendUser::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_listSendUser.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listSendUser.InsertColumn(0, _T("���"), LVCFMT_LEFT,60);
	m_listSendUser.InsertColumn(1, _T("����"), LVCFMT_LEFT,100);
	m_listSendUser.InsertColumn(2, _T("�绰����"), LVCFMT_LEFT,150);
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_SendUser::OnRclickListClient(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CMenu       menu ,* pSubMenu;//��������Ҫ�õ���cmenu����	
	menu.LoadMenu(IDR_MENU_SEND_USER);//װ���Զ�����Ҽ��˵�
	pSubMenu = menu.GetSubMenu(0);//��ȡ��һ�������˵������Ե�һ���˵��������Ӳ˵�	
    CPoint oPoint;//����һ������ȷ�����λ�õ�λ��	
    GetCursorPos( &oPoint);//��ȡ��ǰ����λ�ã��Ա�ʹ�ò˵����Ը�����
	int istat=m_listSendUser.GetSelectionMark();//��istat��ŵ�ǰѡ�����ǵڼ���	
	if(istat == -1) return;
	pSubMenu->TrackPopupMenu (TPM_LEFTALIGN, oPoint.x, oPoint.y, this); //��ָ��λ����ʾ�����˵�
	*pResult = 0;
}

void Dialog_SendUser::OnColumnclickListClient(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	listsort(&m_listSendUser,pNMListView);
	*pResult = 0;
}

void Dialog_SendUser::OnButtonClientQuery() 
{
	m_listSendUser.DeleteAllItems();
	UpdateData();
	CString csSql;
	if(m_strUserName.IsEmpty()) 
		csSql.Format("select * from senduserinfo");	
	else
		csSql.Format("select * from senduserinfo where username=\"%s\"",m_strUserName);	
	MYSQL myCont;
    MYSQL_RES *result;
    MYSQL_ROW sql_row;
    int res;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
    {
        mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
        res=mysql_query(&myCont,csSql);//��ѯ
        if(!res)
        {
            result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
			if(result)
            {
                int i,j;
                j=mysql_num_fields(result);//�鿴������
				unsigned __int64 num = mysql_num_rows(result);//����
				int index = 0;
                while(sql_row=mysql_fetch_row(result))//��ȡ���������
                {
					CString strindex ;
					strindex.Format("%d",index+1);
					m_listSendUser.InsertItem(index,strindex);
                    m_listSendUser.SetItemText(index,1,sql_row[0]);
					m_listSendUser.SetItemText(index,2,sql_row[1]);
					if(index%2==0)
						m_listSendUser.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
					index++;
                }
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
	
	return;
}

void Dialog_SendUser::OnButtonClientAdd() 
{
	Dialog_SendUserAdd dlg;
	dlg.action = 0;
	dlg.DoModal();
	OnButtonClientQuery();
}

void Dialog_SendUser::OnButtonDeleteUser() 
{
	Dialog_SendUserAdd dlg;
	dlg.action = 2;
	dlg.DoModal();
	OnButtonClientQuery();
}

void Dialog_SendUser::OnButtonModify() 
{
	Dialog_SendUserAdd dlg;
	dlg.action = 1;
	dlg.DoModal();
	OnButtonClientQuery();
}

void Dialog_SendUser::OnExcel() 
{
	CreateExcel("���������Ͽ�.xls",&m_listSendUser);
}

void Dialog_SendUser::OnDel() 
{
	int istat=m_listSendUser.GetSelectionMark();//��istat��ŵ�ǰѡ�����ǵڼ���	
	Dialog_SendUserAdd dlg;
	dlg.m_strUserName = m_listSendUser.GetItemText(istat,1);
	dlg.m_strPhone = m_listSendUser.GetItemText(istat,2);
	dlg.action = 2;
	dlg.DoModal();
	OnButtonClientQuery();
}

void Dialog_SendUser::OnModify() 
{
	int istat=m_listSendUser.GetSelectionMark();//��istat��ŵ�ǰѡ�����ǵڼ���	
	Dialog_SendUserAdd dlg;
	dlg.m_strUserName = m_listSendUser.GetItemText(istat,1);
	dlg.m_strPhone = m_listSendUser.GetItemText(istat,2);
	dlg.action = 1;
	dlg.DoModal();
	OnButtonClientQuery();
}
