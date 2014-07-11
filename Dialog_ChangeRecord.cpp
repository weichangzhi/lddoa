// Dialog_ChangeRecord.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_ChangeRecord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_ChangeRecord dialog


Dialog_ChangeRecord::Dialog_ChangeRecord(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_ChangeRecord::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_ChangeRecord)
	m_strListID = _T("");
	m_timeStart = 0;
	m_timeEnd = 0;
	//}}AFX_DATA_INIT
}


void Dialog_ChangeRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_ChangeRecord)
	DDX_Control(pDX, IDC_LIST_CHANGERECORD, m_listChangeRecord);
	DDX_Text(pDX, IDC_EDIT_LIDTID, m_strListID);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_timeStart);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_timeEnd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_ChangeRecord, CDialog)
	//{{AFX_MSG_MAP(Dialog_ChangeRecord)
	ON_BN_CLICKED(IDC_BUTTON__SELECT, OnButtonSelect)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL, OnButtonExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_ChangeRecord message handlers

BOOL Dialog_ChangeRecord::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CTime time1 = CTime::GetCurrentTime();
	m_timeStart = time1;
	m_timeEnd = time1;

	m_listChangeRecord.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES | WS_HSCROLL | WS_VSCROLL);
	m_listChangeRecord.InsertColumn(0, _T("���"), LVCFMT_LEFT,60);
	m_listChangeRecord.InsertColumn(1, _T("������"), LVCFMT_LEFT,120);
	m_listChangeRecord.InsertColumn(2, _T("���ʱ��"), LVCFMT_LEFT,180);
	m_listChangeRecord.InsertColumn(3, _T("�������"), LVCFMT_LEFT,800);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_ChangeRecord::OnButtonSelect() 
{
	m_listChangeRecord.DeleteAllItems();
	UpdateData();
	CString csSql;
	CString starttime;
	starttime.Format("%04d-%02d-%02d",m_timeStart.GetYear(),m_timeStart.GetMonth(),m_timeStart.GetDay());
	CString endtime;
	endtime.Format("%04d-%02d-%02d",m_timeEnd.GetYear(),m_timeEnd.GetMonth(),m_timeEnd.GetDay()+1);

	if (m_strListID.IsEmpty())
	{
		csSql.Format("select * from changerecord where  changetime>=\"%s\"and changetime<=\"%s\" " ,starttime,endtime); 
	}
	else
		csSql.Format("select * from changerecord where  listid=\"%s\" and changetime>=\"%s\" and changetime<=\"%s\" ",m_strListID,starttime,endtime); 
	
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
					m_listChangeRecord.InsertItem(index,strindex);
					m_listChangeRecord.SetItemText(index,1,sql_row[1]);
					m_listChangeRecord.SetItemText(index,2,sql_row[2]);
					m_listChangeRecord.SetItemText(index,3,sql_row[3]);				
					if(index%2==0)
						m_listChangeRecord.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
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

void Dialog_ChangeRecord::OnButtonExcel() 
{
	CreateExcel("�������ϱ����¼.xls",&m_listChangeRecord);
	
}
