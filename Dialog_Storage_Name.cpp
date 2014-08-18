// Dialog_Storage_Name.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_Storage_Name.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_Name dialog


Dialog_Storage_Name::Dialog_Storage_Name(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_Storage_Name::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_Storage_Name)
	storageid = "";
	storagename = "";
	//}}AFX_DATA_INIT
}


void Dialog_Storage_Name::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_Storage_Name)
	DDX_Control(pDX, IDOK, m_btok);
	DDX_Control(pDX, IDCANCEL, m_btcancel);
	DDX_Control(pDX, IDC_LIST_STORAGE_LEFT, m_listStorage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_Storage_Name, CDialog)
	//{{AFX_MSG_MAP(Dialog_Storage_Name)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_STORAGE_LEFT, OnDblclkListStorageLeft)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_Name message handlers

void Dialog_Storage_Name::OnDblclkListStorageLeft(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int cursel = 0;
	cursel = m_listStorage.GetSelectionMark();

	if(cursel==-1)
		return;
	storageid = m_listStorage.GetItemText(cursel,1);
	storagename = m_listStorage.GetItemText(cursel,2);
	char log[256] = {0};
	sprintf(log,"OnEditDbClk \t%s,%d: cursel=%d,id=%s,name=%s",__FILE__,__LINE__,cursel,storageid,storagename);
	writelog(log);

	*pResult = 0;
	CDialog::OnOK();
}

BOOL Dialog_Storage_Name::PreTranslateMessage(MSG* pMsg) 
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


HBRUSH Dialog_Storage_Name::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd->GetDlgCtrlID() == IDC_STATIC1)   
	{   
		pDC->SetTextColor(RGB(255,0,0));   
	}  
	return hbr;
}


BOOL Dialog_Storage_Name::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_listStorage.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listStorage.InsertColumn(0, _T("���"), LVCFMT_LEFT,60);
	m_listStorage.InsertColumn(1, _T("�ֿ���"), LVCFMT_LEFT,100);
	m_listStorage.InsertColumn(2, _T("�ֿ�ȫ��"), LVCFMT_LEFT,200);
	
	CString csSql;
	csSql.Format("select storageid,storagename from storage_name " ); 

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
                int j;
                j=mysql_num_fields(result);//�鿴������
				unsigned __int64 num = mysql_num_rows(result);//����
				int index = 0;
				int number = 0;
				float money = 0.0;
                while(sql_row=mysql_fetch_row(result))//��ȡ���������
                {
					CString strindex ;
					strindex.Format("%d",index+1);
					m_listStorage.InsertItem(index,strindex);
					m_listStorage.SetItemText(index,1,sql_row[0]);
					m_listStorage.SetItemText(index,2,sql_row[1]);
					if(index%2==0)
						m_listStorage.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
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
			return TRUE;
        }
    }
    else
    {
		const char *error = mysql_error(&myCont);
		CString str;
		str.Format("���ݿ����(%s)",error);
		MessageBox(str,"��ʾ",MB_OK);
		mysql_close(&myCont);//�Ͽ�����
		return TRUE;
    }
    if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
    mysql_close(&myCont);//�Ͽ�����

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_Storage_Name::OnOK() 
{
	int cursel = 0;
	cursel = m_listStorage.GetSelectionMark();
	if(cursel==-1)
		return;
	storageid = m_listStorage.GetItemText(cursel,1);
	storagename = m_listStorage.GetItemText(cursel,2);

	CDialog::OnOK();
}

void Dialog_Storage_Name::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
