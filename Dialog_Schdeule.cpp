// Dialog_Schdeule.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_Schdeule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Schdeule dialog


CDialog_Schdeule::CDialog_Schdeule(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Schdeule::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Schdeule)
	m_timebegin = 0;
	m_timeend = 0;
	//}}AFX_DATA_INIT
}


void CDialog_Schdeule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Schdeule)
	DDX_Control(pDX, IDC_COMBO2, m_com_schdeule2);
	DDX_Control(pDX, IDC_LIST_SCHDEULE, m_list_schedule);
	DDX_Control(pDX, IDC_COMBO_SCHEDULE, m_com_schdeule);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_timebegin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_timeend);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Schdeule, CDialog)
	//{{AFX_MSG_MAP(CDialog_Schdeule)
	ON_BN_CLICKED(IDC_BUTTON_SCHDEULE_SELECT, OnSchdeuleSelect)
	ON_CBN_SELCHANGE(IDC_COMBO_SCHEDULE, OnSelchangeComboSchedule)
	ON_BN_CLICKED(IDC_EXCEL, OnExcel)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_SCHDEULE, OnColumnclickListSchdeule)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Schdeule message handlers

BOOL CDialog_Schdeule::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_com_schdeule.InsertString(0,"全部");
	m_com_schdeule.InsertString(1,"物流及以前");
	m_com_schdeule.InsertString(2,"物流后待结单");
	m_com_schdeule.InsertString(3,"已结单");
	m_com_schdeule.SetCurSel(1);

	m_com_schdeule2.InsertString(0,"过账时间");
	m_com_schdeule2.InsertString(1,"停留时间");
	m_com_schdeule2.SetCurSel(1);

	m_list_schedule.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list_schedule.InsertColumn(0, _T("序号"), LVCFMT_LEFT,50);
	m_list_schedule.InsertColumn(1, _T("订单号"), LVCFMT_LEFT,100);
	m_list_schedule.InsertColumn(2, _T("产品名称"), LVCFMT_LEFT,80);
	m_list_schedule.InsertColumn(3, _T("经办人"), LVCFMT_LEFT,100);
	m_list_schedule.InsertColumn(4, _T("营销部门"), LVCFMT_LEFT,80);
	m_list_schedule.InsertColumn(5, _T("产品总数"), LVCFMT_LEFT,80);
	m_list_schedule.InsertColumn(6, _T("材料"), LVCFMT_LEFT,150);
	m_list_schedule.InsertColumn(7, _T("产品体积(cm3)"), LVCFMT_LEFT,120);
	m_list_schedule.InsertColumn(8, _T("收单日期"), LVCFMT_LEFT,100);
	m_list_schedule.InsertColumn(9, _T("交货日期"), LVCFMT_LEFT,100);
	m_list_schedule.InsertColumn(10, _T("快递单号"), LVCFMT_LEFT,100);
	m_list_schedule.InsertColumn(11, _T("业务"), LVCFMT_LEFT,170);
	m_list_schedule.InsertColumn(12, _T("技术部"), LVCFMT_LEFT,170);
	m_list_schedule.InsertColumn(13, _T("生产部"), LVCFMT_LEFT,170);
	m_list_schedule.InsertColumn(14, _T("质检"), LVCFMT_LEFT,170);
	m_list_schedule.InsertColumn(15, _T("成品仓"), LVCFMT_LEFT,170);
	m_list_schedule.InsertColumn(16, _T("物流"), LVCFMT_LEFT,170);

	CTime time1 = CTime::GetCurrentTime();
	m_timebegin = time1;
	m_timeend = time1;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_Schdeule::OnSelchangeComboSchedule() 
{
	// TODO: Add your control notification handler code here
	int i = 0;
	for (i = m_com_schdeule2.GetCount() - 1; i >= 0; i--)
	{
	   m_com_schdeule2.DeleteString(i);
	}

	int indexSel = m_com_schdeule.GetCurSel();
	switch(indexSel)
	{
	case 0:
		m_com_schdeule2.InsertString(0,"过账时间");
		m_com_schdeule2.InsertString(1,"停留时间");
		m_com_schdeule2.SetCurSel(1);
		break;
	case 1:
		m_com_schdeule2.InsertString(0,"过账时间");
		m_com_schdeule2.InsertString(1,"停留时间");
		m_com_schdeule2.SetCurSel(1);
		break;
	case 2:
		m_com_schdeule2.InsertString(0,"过账时间");
		m_com_schdeule2.InsertString(1,"停留时间");
		m_com_schdeule2.SetCurSel(1);
		break;
	case 3:
		m_com_schdeule2.InsertString(0,"过账时间");
		m_com_schdeule2.InsertString(1,"停留时间");
		m_com_schdeule2.SetCurSel(1);
		break;
	default:
		break;
	}
}

CString CalcTimeSpan(CString strtime1,CString strtime2)
{
	if(strtime1.IsEmpty() || strtime2.IsEmpty())
		return "";
	CString strspan;
	CTime time1(atoi(strtime1.Mid(0,4)),atoi(strtime1.Mid(5,2)),atoi(strtime1.Mid(8,2)),atoi(strtime1.Mid(11,2)),atoi(strtime1.Mid(14,2)),0,0);
	CTime time2(atoi(strtime2.Mid(0,4)),atoi(strtime2.Mid(5,2)),atoi(strtime2.Mid(8,2)),atoi(strtime2.Mid(11,2)),atoi(strtime2.Mid(14,2)),0,0);
						
	CTimeSpan timeSpan = time2 - time1;
	int day = timeSpan.GetDays();
	int hour = timeSpan.GetTotalHours();
	int min = timeSpan.GetTotalMinutes();
	if(day>0)
		strspan.Format("%d天%d小时",day,timeSpan.GetHours());
	else if(hour>0)
		strspan.Format("%d小时",hour);
	else
		strspan.Format("%d分钟",min);
	return strspan;
}

void CDialog_Schdeule::OnSchdeuleSelect() 
{
	// TODO: Add your control notification handler code here
	m_list_schedule.DeleteAllItems();
	UpdateData();
	CString csSql;
	CString starttime;
	starttime.Format("%04d-%02d-%02d",m_timebegin.GetYear(),m_timebegin.GetMonth(),m_timebegin.GetDay());
	CString endtime;
	endtime.Format("%04d-%02d-%02d",m_timeend.GetYear(),m_timeend.GetMonth(),m_timeend.GetDay()+1);
			
	int indexSel = m_com_schdeule.GetCurSel();
	int indexSel2 = m_com_schdeule2.GetCurSel();
	switch(indexSel)
	{
	case 0://全部
		csSql.Format("select baseinfo.listid,baseinfo.listname,baseinfo.people,baseinfo.department,baseinfo.truelistnumber,baseinfo.material,baseinfo.volume,baseinfo.reveivedate,baseinfo.enddate,baseinfo.sendid,businessendtime,tcendtime,pdendtime,qcendtime,storageendtime,sendendtime from baseinfo,scheduledetail where  businessendtime>=\"%s\"and businessendtime<=\"%s\" and baseinfo.listid=scheduledetail.listid" ,starttime,endtime);
		break;
	case 1://物流及以前
		csSql.Format("select baseinfo.listid,baseinfo.listname,baseinfo.people,baseinfo.department,baseinfo.truelistnumber,baseinfo.material,baseinfo.volume,baseinfo.reveivedate,baseinfo.enddate,baseinfo.sendid,businessendtime,tcendtime,pdendtime,qcendtime,storageendtime,sendendtime from baseinfo,schedule,scheduledetail where  baseinfo.listid=schedule.listid  and  schedule.listid=scheduledetail.listid and end=0 and  schedule.totelnumber>schedule.post  and businessendtime>=\"%s\"and businessendtime<=\"%s\" " ,starttime,endtime);
		break;
	case 2://物流后待结单
		csSql.Format("select baseinfo.listid,baseinfo.listname,baseinfo.people,baseinfo.department,baseinfo.truelistnumber,baseinfo.material,baseinfo.volume,baseinfo.reveivedate,baseinfo.enddate,baseinfo.sendid,businessendtime,tcendtime,pdendtime,qcendtime,storageendtime,sendendtime from baseinfo,schedule,scheduledetail where baseinfo.listid=schedule.listid  and  schedule.listid=scheduledetail.listid and end=0 and schedule.totelnumber=schedule.post and  businessendtime>=\"%s\"and businessendtime<=\"%s\"  " ,starttime,endtime);
		break;
	case 3://已结单
		csSql.Format("select baseinfo.listid,baseinfo.listname,baseinfo.people,baseinfo.department,baseinfo.truelistnumber,baseinfo.material,baseinfo.volume,baseinfo.reveivedate,baseinfo.enddate,baseinfo.sendid,businessendtime,tcendtime,pdendtime,qcendtime,storageendtime,sendendtime from baseinfo,schedule,scheduledetail where baseinfo.listid=schedule.listid  and  schedule.listid=scheduledetail.listid and end=1 and  businessendtime>=\"%s\"and businessendtime<=\"%s\" " ,starttime,endtime);
		break;
	default:
		break;
	}


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
					CString strindex ;
					strindex.Format("%d",index+1);
					m_list_schedule.InsertItem(index,strindex);
					int i=0;
					for(i=1;i<=10;i++)
					{
						m_list_schedule.SetItemText(index,i,sql_row[i-1]);
					}
					switch(indexSel2)
					{
					case 0://过账时间
						for(i=11;i<=16;i++)
						{
							m_list_schedule.SetItemText(index,i,sql_row[i-1]);
						}
						break;
					case 1://停留时间
						m_list_schedule.SetItemText(index,11,"0");						
						for(i=12;i<=16;i++)
						{
							m_list_schedule.SetItemText(index,i,CalcTimeSpan(sql_row[i-2],sql_row[i-1]));
						}
						break;
					default :
						break;

					}
					/*m_list_schedule.SetItemText(index,1,sql_row[1]);
					m_list_schedule.SetItemText(index,2,sql_row[2]);
					m_list_schedule.SetItemText(index,3,sql_row[3]);
					m_list_schedule.SetItemText(index,4,sql_row[4]);
					m_list_schedule.SetItemText(index,5,sql_row[5]);
					m_list_schedule.SetItemText(index,6,sql_row[6]);
					m_list_schedule.SetItemText(index,7,sql_row[7]);


					switch(indexSel2)
					{
					case 0://过账时间
						m_list_schedule.SetItemText(index,8,sql_row[42]);
						m_list_schedule.SetItemText(index,9,sql_row[46]);
						m_list_schedule.SetItemText(index,10,sql_row[50]);
						m_list_schedule.SetItemText(index,11,sql_row[54]);
						m_list_schedule.SetItemText(index,12,sql_row[58]);
						break;
					case 1://停留时间
						m_list_schedule.SetItemText(index,8,"0");
						m_list_schedule.SetItemText(index,9,CalcTimeSpan(sql_row[45],sql_row[46]));
						m_list_schedule.SetItemText(index,10,CalcTimeSpan(sql_row[49],sql_row[50]));
						m_list_schedule.SetItemText(index,11,CalcTimeSpan(sql_row[53],sql_row[54]));
						m_list_schedule.SetItemText(index,12,CalcTimeSpan(sql_row[57],sql_row[58]));
						break;
					default:
						break;
					}//switch
					*/
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

BOOL CDialog_Schdeule::PreTranslateMessage(MSG* pMsg) 
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

void CDialog_Schdeule::OnExcel() 
{
	CreateExcel("订单进度.xls",&m_list_schedule);	
}

void CDialog_Schdeule::OnColumnclickListSchdeule(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	listsort(&m_list_schedule,pNMListView);
	*pResult = 0;
}
