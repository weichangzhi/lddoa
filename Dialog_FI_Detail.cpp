// Dialog_FI_Detail.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_FI_Detail.h"
#include "Dialog_FI_Proceeds.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_FI_Detail dialog


Dialog_FI_Detail::Dialog_FI_Detail(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_FI_Detail::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_FI_Detail)
	m_query_listid = _T("");
	m_timebegin = 0;
	m_timeend = 0;
	//}}AFX_DATA_INIT
}


void Dialog_FI_Detail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_FI_Detail)
	DDX_Control(pDX, IDC_LIST_FI, m_listFI);
	DDX_Control(pDX, IDC_EXCEL, m_btexcel);
	DDX_Control(pDX, IDOK, m_btok);
	DDX_Control(pDX, IDC_BUTTON_PROCEEDS, m_btproceeds);
	DDX_Text(pDX, IDC_EDIT_QUERY_LISTID, m_query_listid);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_timebegin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_timeend);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_FI_Detail, CDialog)
	//{{AFX_MSG_MAP(Dialog_FI_Detail)
	ON_BN_CLICKED(IDC_BUTTON_PROCEEDS, OnButtonProceeds)
	ON_BN_CLICKED(IDC_EXCEL, OnExcel)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_FI, OnColumnclickListFi)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_FI_Detail message handlers

BOOL Dialog_FI_Detail::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if((g_permission & FI)==0)
	{
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		GetDlgItem(IDC_EXCEL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PROCEEDS)->EnableWindow(FALSE);
	}
	
	CTime time1 = CTime::GetCurrentTime();
	m_timebegin = time1;
	m_timeend = time1;

	m_listFI.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listFI.InsertColumn(0, _T("���"), LVCFMT_LEFT,50);
	m_listFI.InsertColumn(1, _T("������"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(2, _T("ǩ����Ԫ��"), LVCFMT_LEFT,130);
	m_listFI.InsertColumn(3, _T("ҵ�񾭰���"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(4, _T("�տʽ"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(5, _T("�տ��Ԫ��"), LVCFMT_LEFT,130);
	m_listFI.InsertColumn(6, _T("�տ���"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(7, _T("�տ�����"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(8, _T("�տע"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(9, _T("��Ʊ����"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(10, _T("��Ʊ��Ԫ��"), LVCFMT_LEFT,130);
	m_listFI.InsertColumn(11, _T("��Ʊ��"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(12, _T("��Ʊ����"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(13, _T("��Ʊ����"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(14, _T("��Ʊ��ע"), LVCFMT_LEFT,100);

	UpdateData(FALSE);	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_FI_Detail::OnOK() 
{
	m_listFI.DeleteAllItems();
	UpdateData();
	CString csSql;
	CString starttime;
	starttime.Format("%04d-%02d-%02d",m_timebegin.GetYear(),m_timebegin.GetMonth(),m_timebegin.GetDay());
	CString endtime;
	endtime.Format("%04d-%02d-%02d",m_timeend.GetYear(),m_timeend.GetMonth(),m_timeend.GetDay()+1);

	if(m_query_listid.IsEmpty())
		csSql.Format("select * from fidetail where  timeproceeds>=\"%s\" and timeproceeds<=\"%s\" and timebill>=\"%s\" and timebill<=\"%s\" " ,starttime,endtime,starttime,endtime); 
	else
		csSql.Format("select * from fidetail where  listid=\"%s\" and timeproceeds>=\"%s\" and timeproceeds<=\"%s\" and timebill>=\"%s\" and timebill<=\"%s\" " ,m_query_listid,starttime,endtime,starttime,endtime); 

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
					m_listFI.InsertItem(index,strindex);
					int i=0;
					for(i=1;i<=14;i++)
					{
						m_listFI.SetItemText(index,i,sql_row[i]);
					}

					if(index%2==0)
						m_listFI.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
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
	//CDialog::OnOK();
}

void Dialog_FI_Detail::OnButtonProceeds() 
{
	Dialog_FI_Proceeds dlg;
	dlg.DoModal();
}

void Dialog_FI_Detail::OnExcel() 
{
	CreateExcel("������ϸ.xls",&m_listFI);
}

BOOL Dialog_FI_Detail::PreTranslateMessage(MSG* pMsg) 
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

void Dialog_FI_Detail::OnColumnclickListFi(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	listsort(&m_listFI,pNMListView);
	*pResult = 0;
}
