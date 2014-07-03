// Dialog_Detail.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_Detail.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Detail dialog


CDialog_Detail::CDialog_Detail(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Detail::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Detail)
	m_listid = _T("");
	//}}AFX_DATA_INIT
}


void CDialog_Detail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Detail)
	DDX_Control(pDX, IDC_LIST_DETAIL, m_listdetail);
	DDX_Text(pDX, IDC_EDIT_DETAIL, m_listid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Detail, CDialog)
	//{{AFX_MSG_MAP(CDialog_Detail)
	ON_BN_CLICKED(IDC_BUTTON_DETAIL_SELECT, OnDetailSelect)
	ON_BN_CLICKED(IDC_EXCEL, OnExcel)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Detail message handlers

BOOL CDialog_Detail::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_listdetail.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listdetail.InsertColumn(0, _T("���"), LVCFMT_LEFT,60);
	m_listdetail.InsertColumn(1, _T("������"), LVCFMT_LEFT,90);
	m_listdetail.InsertColumn(2, _T("��������"), LVCFMT_LEFT,100);
	m_listdetail.InsertColumn(3, _T("��Ʒ����"), LVCFMT_LEFT,80);
	m_listdetail.InsertColumn(4, _T("��������"), LVCFMT_LEFT,80);
	m_listdetail.InsertColumn(5, _T("�������(cm3)"), LVCFMT_LEFT,120);
	m_listdetail.InsertColumn(6, _T("�յ�����"), LVCFMT_LEFT,100);
	m_listdetail.InsertColumn(7, _T("��������"), LVCFMT_LEFT,100);
	m_listdetail.InsertColumn(8, _T("ҵ��  (�µ�ʱ�� | �µ����� | ������)"), LVCFMT_LEFT,320);
	m_listdetail.InsertColumn(9, _T("������  (����ʱ�� | �������� | ������)"), LVCFMT_LEFT,320);
	m_listdetail.InsertColumn(10, _T("������  (����ʱ�� | �������� | ������)"), LVCFMT_LEFT,320);
	m_listdetail.InsertColumn(11, _T("�ʼ�  (����ʱ�� | �������� | ������)"), LVCFMT_LEFT,320);
	m_listdetail.InsertColumn(12, _T("��Ʒ��  (����ʱ�� | �������� | ������)"), LVCFMT_LEFT,320);
	m_listdetail.InsertColumn(13, _T("����  (����ʱ�� | �������� | ������)"), LVCFMT_LEFT,320);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_Detail::OnDetailSelect() 
{
	// TODO: Add your control notification handler code here
	m_listdetail.DeleteAllItems();
	UpdateData();
	CString csSql;
	csSql.Format("select baseinfo.listid,baseinfo.listname,baseinfo.truelistnumber,baseinfo.material,baseinfo.volume,baseinfo.reveivedate,baseinfo.enddate,businessendtime,businessnumber,businesspeople,tcendtime,tcnumber,tcpeople,pdendtime,pdnumber,pdpeople,qcendtime,qcnumber,qcpeople,storageendtime,storagenumber,storagepopple,sendendtime,sendnumber,sendpeople from baseinfo,scheduledetail where baseinfo.listid=scheduledetail.listid and  scheduledetail.listid=\"%s\" " ,m_listid);

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
                while(sql_row=mysql_fetch_row(result))//��ȡ���������
                {
					CString strindex ;
					strindex.Format("%d",index+1);
					m_listdetail.InsertItem(index,strindex);
					m_listdetail.SetItemText(index,1,sql_row[0]);
					m_listdetail.SetItemText(index,2,sql_row[1]);
					m_listdetail.SetItemText(index,3,sql_row[2]);
					m_listdetail.SetItemText(index,4,sql_row[3]);
					m_listdetail.SetItemText(index,5,sql_row[4]);	
					m_listdetail.SetItemText(index,6,sql_row[5]);
					m_listdetail.SetItemText(index,7,sql_row[6]);
					CString strtime_people;
					if(sql_row[8]!=NULL)
					{
						strtime_people.Format("%s | %d | %s",sql_row[7],atoi(sql_row[8]),sql_row[9]);
						m_listdetail.SetItemText(index,8,strtime_people);
					}
					if(sql_row[11]!=NULL)
					{
						strtime_people.Format("%s | %d | %s",sql_row[10],atoi(sql_row[11]),sql_row[12]);
						m_listdetail.SetItemText(index,9,strtime_people);
					}
					if(sql_row[14]!=NULL)
					{
						strtime_people.Format("%s | %d | %s",sql_row[13],atoi(sql_row[14]),sql_row[15]);
						m_listdetail.SetItemText(index,10,strtime_people);
					}
					if(sql_row[17]!=NULL)
					{
						strtime_people.Format("%s | %d | %s",sql_row[16],atoi(sql_row[17]),sql_row[18]);
						m_listdetail.SetItemText(index,11,strtime_people);
					}
					if(sql_row[20]!=NULL)
					{
						strtime_people.Format("%s | %d | %s",sql_row[19],atoi(sql_row[20]),sql_row[21]);
						m_listdetail.SetItemText(index,12,strtime_people);
					}
					if(sql_row[23]!=NULL)
					{
						strtime_people.Format("%s | %d | %s",sql_row[22],atoi(sql_row[23]),sql_row[24]);
						m_listdetail.SetItemText(index,13,strtime_people);
					}
					if(index%2==0)
						m_listdetail.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
					index++;
                }//while
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

BOOL CDialog_Detail::PreTranslateMessage(MSG* pMsg) 
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

void CDialog_Detail::OnExcel() 
{
	CreateExcel("������ϸ.xls",&m_listdetail);
}

void CDialog_Detail::OnSize(UINT nType, int cx, int cy) 
{
	/*int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	CRect m_rect(0,0,width,height);
	m_rect.DeflateRect(200,0,20,20);
	this->MoveWindow(m_rect); 
	*/
	CDialog::OnSize(nType, cx, cy);

}
