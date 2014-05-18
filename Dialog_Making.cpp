// Dialog_Making.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_Making.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Making dialog


CDialog_Making::CDialog_Making(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Making::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Making)
	m_timebegin = 0;
	m_timeend = 0;
	//}}AFX_DATA_INIT
}


void CDialog_Making::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Making)
	DDX_Control(pDX, IDC_LIST_SCHDEULE, m_list_schedule);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_timebegin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_timeend);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Making, CDialog)
	//{{AFX_MSG_MAP(CDialog_Making)
	ON_BN_CLICKED(IDC_BUTTON_SCHDEULE_SELECT, OnMakingQuery)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_SCHDEULE, OnCustomDraw)         
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Making message handlers

BOOL CDialog_Making::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_list_schedule.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list_schedule.InsertColumn(0, _T("���"), LVCFMT_LEFT,50);
	m_list_schedule.InsertColumn(1, _T("������"), LVCFMT_LEFT,80);
	m_list_schedule.InsertColumn(2, _T("��Ʒ����"), LVCFMT_LEFT,100);
	m_list_schedule.InsertColumn(3, _T("��Ʒ����"), LVCFMT_LEFT,80);
	m_list_schedule.InsertColumn(4, _T("��������"), LVCFMT_LEFT,100);
	m_list_schedule.InsertColumn(5, _T("��Ʒ���"), LVCFMT_LEFT,80);
	m_list_schedule.InsertColumn(6, _T("�յ�����"), LVCFMT_LEFT,100);
	m_list_schedule.InsertColumn(7, _T("��������"), LVCFMT_LEFT,100);
	m_list_schedule.InsertColumn(8, _T("��ݵ���"), LVCFMT_LEFT,120);
	m_list_schedule.InsertColumn(9, _T("������"), LVCFMT_LEFT,60);
	m_list_schedule.InsertColumn(10, _T("������"), LVCFMT_LEFT,60);
	m_list_schedule.InsertColumn(11, _T("�ʼ�"), LVCFMT_LEFT,60);
	m_list_schedule.InsertColumn(12, _T("��Ʒ��"), LVCFMT_LEFT,60);     
	CTime time1 = CTime::GetCurrentTime();
	m_timebegin = time1;
	m_timeend = time1;


    LOGFONT logfont;
    memset( &logfont,0,sizeof( logfont ) );
    logfont.lfHeight = 20;
    strcpy( logfont.lfFaceName,"����" );
    CFont font;
    font.CreateFontIndirect( &logfont );
    //m_list_schedule.SetFont( &font );


	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDialog_Making::PreTranslateMessage(MSG* pMsg) 
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

void CDialog_Making::OnMakingQuery() 
{
	m_list_schedule.DeleteAllItems();
	UpdateData();
	CString csSql;
	CString starttime;
	starttime.Format("%04d-%02d-%02d",m_timebegin.GetYear(),m_timebegin.GetMonth(),m_timebegin.GetDay());
	CString endtime;
	endtime.Format("%04d-%02d-%02d",m_timeend.GetYear(),m_timeend.GetMonth(),m_timeend.GetDay()+1);
			
	csSql.Format("select baseinfo.listid,baseinfo.listname,truelistnumber,material,volume,reveivedate,enddate,sendid,schedule.tcnumber,schedule.pdnumber,schedule.qcnumber,schedule.storagenumber,schedule.hasstoragenumber from baseinfo,schedule,scheduledetail where baseinfo.listid=schedule.listid and schedule.listid=scheduledetail.listid and end=0 and  businessendtime>=\"%s\" and businessendtime<=\"%s\" " ,starttime,endtime);

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
					if((atoi(sql_row[12]) >= atoi(sql_row[2])) && (atoi(sql_row[2])!=0))//��Ʒ���ѹ��˵���Ŀ�ﵽ�������Ͳ���ʾ
						continue;
					CString strindex ;
					strindex.Format("%d",index+1);
					m_list_schedule.InsertItem(index,strindex);
					int i=0;
					for(i=1;i<=8;i++)
					{
						m_list_schedule.SetItemText(index,i,sql_row[i-1]);
					}
					for(i=9;i<=12;i++)
					{
						if(atoi(sql_row[i-1])==0)
							m_list_schedule.SetItemText(index,i,"");
						else
							m_list_schedule.SetItemText(index,i,sql_row[i-1]);
					}
					if(index%2==0)
						m_list_schedule.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
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
		MessageBox("�������ݿ�ʧ�ܣ����������Ƿ���ȷ����","��ʾ",MB_OK);
    }
    if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
    mysql_close(&myCont);//�Ͽ�����

	return;
	
}

void CDialog_Making::OnCustomDraw(NMHDR *pnotify, LRESULT *result)
{
	LPNMLVCUSTOMDRAW lplvcd = (LPNMLVCUSTOMDRAW)pnotify;
	
	if(lplvcd->nmcd.dwDrawStage == CDDS_PREPAINT)
		*result = CDRF_NOTIFYITEMDRAW;

	if(lplvcd->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
	{
		CString strindex = m_list_schedule.GetItemText(lplvcd->nmcd.dwItemSpec, 0);   
		int index = atoi(strindex);
		//if((index%2)==0)
		//	lplvcd->clrText = RGB(0, 0, 255);
		*result = CDRF_DODEFAULT;
	}
}