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
	ON_BN_CLICKED(IDC_EXCEL, OnExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Making message handlers

BOOL CDialog_Making::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_list_schedule.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list_schedule.InsertColumn(0, _T("序号"), LVCFMT_LEFT,50);
	m_list_schedule.InsertColumn(1, _T("订单号"), LVCFMT_LEFT,80);
	m_list_schedule.InsertColumn(2, _T("产品名称"), LVCFMT_LEFT,100);
	m_list_schedule.InsertColumn(3, _T("产品总数"), LVCFMT_LEFT,80);
	m_list_schedule.InsertColumn(4, _T("制作材料"), LVCFMT_LEFT,100);
	m_list_schedule.InsertColumn(5, _T("产品体积"), LVCFMT_LEFT,80);
	m_list_schedule.InsertColumn(6, _T("收单日期"), LVCFMT_LEFT,100);
	m_list_schedule.InsertColumn(7, _T("交货日期"), LVCFMT_LEFT,100);
	//m_list_schedule.InsertColumn(8, _T("快递单号"), LVCFMT_LEFT,120);
	m_list_schedule.InsertColumn(8, _T("技术部"), LVCFMT_LEFT,60);
	m_list_schedule.InsertColumn(9, _T("生产部"), LVCFMT_LEFT,60);
	m_list_schedule.InsertColumn(10, _T("质检"), LVCFMT_LEFT,60);
	m_list_schedule.InsertColumn(11, _T("成品仓"), LVCFMT_LEFT,60);     
	CTime time1 = CTime::GetCurrentTime();
	m_timebegin = time1;
	m_timeend = time1;


    LOGFONT logfont;
    memset( &logfont,0,sizeof( logfont ) );
    logfont.lfHeight = 20;
    strcpy( logfont.lfFaceName,"宋体" );
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
		//case VK_RETURN: //回车  
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
			
	csSql.Format("select baseinfo.listid,baseinfo.listname,truelistnumber,material,volume,reveivedate,enddate,schedule.tcnumber,schedule.pdnumber,schedule.qcnumber,schedule.storagenumber,schedule.hasstoragenumber from baseinfo,schedule,scheduledetail where baseinfo.listid=schedule.listid and schedule.listid=scheduledetail.listid and end=0 and  businessendtime>=\"%s\" and businessendtime<=\"%s\" " ,starttime,endtime);

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
                int j;
                j=mysql_num_fields(result);//查看多少列
				unsigned __int64 num = mysql_num_rows(result);//行数
				int index = 0;
                while(sql_row=mysql_fetch_row(result))//获取具体的数据
                {
					if((atoi(sql_row[12]) >= atoi(sql_row[2])) && (atoi(sql_row[2])!=0))//成品仓已过账的数目达到总数，就不显示
						continue;
					CString strindex ;
					strindex.Format("%d",index+1);
					m_list_schedule.InsertItem(index,strindex);
					int i=0;
					for(i=1;i<=7;i++)
					{
						m_list_schedule.SetItemText(index,i,sql_row[i-1]);
					}
					for(i=8;i<=11;i++)
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
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			return;
        }
    }
    else
    {
		MessageBox("连接数据库失败，请检查网络是否正确连接","提示",MB_OK);
    }
    if(result!=NULL) mysql_free_result(result);//释放结果资源
    mysql_close(&myCont);//断开连接

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

void CDialog_Making::OnExcel() 
{
	CreateExcel("在制品清单.xls",&m_list_schedule);		
}
