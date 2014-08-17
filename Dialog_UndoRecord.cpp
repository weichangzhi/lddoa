// Dialog_UndoRecord.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_UndoRecord.h"
#include "Dialog_progress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_UndoRecord dialog


Dialog_UndoRecord::Dialog_UndoRecord(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_UndoRecord::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_UndoRecord)
	m_timestart = 0;
	m_timeend = 0;
	m_strListid = _T("");
	//}}AFX_DATA_INIT
}


void Dialog_UndoRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_UndoRecord)
	DDX_Control(pDX, IDC_LIST_CHANGERECORD, m_listUndoRecord);
	DDX_Control(pDX, IDC_BUTTON_EXCEL, m_btexcel);
	DDX_Control(pDX, IDC_BUTTON__SELECT, m_btselect);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_timestart);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_timeend);
	DDX_Text(pDX, IDC_EDIT_LIDTID, m_strListid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_UndoRecord, CDialog)
	//{{AFX_MSG_MAP(Dialog_UndoRecord)
	ON_BN_CLICKED(IDC_BUTTON__SELECT, OnButtonSelect)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL, OnButtonExcel)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_CHANGERECORD, OnColumnclickListChangerecord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_UndoRecord message handlers

BOOL Dialog_UndoRecord::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CTime time1 = CTime::GetCurrentTime();
	m_timestart = time1;
	m_timeend = time1;

	m_listUndoRecord.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES | WS_HSCROLL | WS_VSCROLL);
	m_listUndoRecord.InsertColumn(0, _T("序号"), LVCFMT_LEFT,50);
	m_listUndoRecord.InsertColumn(1, _T("订单号"), LVCFMT_LEFT,100);
	m_listUndoRecord.InsertColumn(2, _T("产品名称"), LVCFMT_LEFT,80);
	m_listUndoRecord.InsertColumn(3, _T("经办人"), LVCFMT_LEFT,100);
	m_listUndoRecord.InsertColumn(4, _T("设计师"), LVCFMT_LEFT,100);
	m_listUndoRecord.InsertColumn(5, _T("营销部门"), LVCFMT_LEFT,80);
	m_listUndoRecord.InsertColumn(6, _T("产品总数"), LVCFMT_LEFT,80);
	m_listUndoRecord.InsertColumn(7, _T("材料"), LVCFMT_LEFT,150);
	m_listUndoRecord.InsertColumn(8, _T("产品体积(cm3)"), LVCFMT_LEFT,120);
	m_listUndoRecord.InsertColumn(9, _T("派单日期"), LVCFMT_LEFT,100);
	m_listUndoRecord.InsertColumn(10, _T("交货日期"), LVCFMT_LEFT,100);
	m_listUndoRecord.InsertColumn(11, _T("快递单号"), LVCFMT_LEFT,100);

	m_listUndoRecord.InsertColumn(12, _T("销单原因"), LVCFMT_LEFT,200);
	m_listUndoRecord.InsertColumn(13, _T("成本"), LVCFMT_LEFT,100);
	m_listUndoRecord.InsertColumn(14, _T("已付金额"), LVCFMT_LEFT,100);
	m_listUndoRecord.InsertColumn(15, _T("销单时间"), LVCFMT_LEFT,180);
	m_listUndoRecord.InsertColumn(16, _T("订单部门"), LVCFMT_LEFT,100);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_UndoRecord::OnButtonSelect() 
{
	m_listUndoRecord.DeleteAllItems();
	UpdateData();
	CString csSql;
	CString starttime;
	starttime.Format("%04d-%02d-%02d",m_timestart.GetYear(),m_timestart.GetMonth(),m_timestart.GetDay());
	CString endtime;
	endtime.Format("%04d-%02d-%02d",m_timeend.GetYear(),m_timeend.GetMonth(),m_timeend.GetDay()+1);
	if(m_strListid.IsEmpty())
	{
		csSql.Format("select baseinfo.listid,baseinfo.listname,baseinfo.people,baseinfo.desinger,baseinfo.department,baseinfo.truelistnumber,baseinfo.material,baseinfo.volume,baseinfo.reveivedate,baseinfo.enddate,baseinfo.sendid, reason,cost,payment,undotime,undolist.department from baseinfo,schedule,undolist,scheduledetail where  schedule.undolist=1 and baseinfo.listid=schedule.listid  and  schedule.listid=undolist.listid and schedule.listid=scheduledetail.listid  and businessendtime>=\"%s\"and businessendtime<=\"%s\" " ,starttime,endtime);
	}
	else
	{
		csSql.Format("select baseinfo.listid,baseinfo.listname,baseinfo.people,baseinfo.desinger,baseinfo.department,baseinfo.truelistnumber,baseinfo.material,baseinfo.volume,baseinfo.reveivedate,baseinfo.enddate,baseinfo.sendid, reason,cost,payment,undotime,undolist.department from baseinfo,schedule,undolist,scheduledetail where schedule.listid=\"%s\" and schedule.undolist=1 and baseinfo.listid=schedule.listid  and  schedule.listid=undolist.listid and schedule.listid=scheduledetail.listid  and businessendtime>=\"%s\"and businessendtime<=\"%s\" " ,m_strListid,starttime,endtime);
	}

	Dialog_progress *dlgpro;
	dlgpro=new Dialog_progress(); 
	dlgpro->Create(IDD_DIALOG_PROGRESS);
	if(g_openprocess)
		dlgpro->ShowWindow(SW_SHOW);
	else
		dlgpro->ShowWindow(SW_HIDE);

	MYSQL myCont;
    MYSQL_RES *result;
    MYSQL_ROW sql_row;
    int res;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
    {
		dlgpro->setpos(500);
        mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
        res=mysql_query(&myCont,csSql);//查询
        if(!res)
        {
			dlgpro->setpos(600);
            result=mysql_store_result(&myCont);//保存查询到的数据到result
		    if(result)
            {
                int j;
				dlgpro->setpos(700);
                j=mysql_num_fields(result);//查看多少列
				unsigned __int64 num = mysql_num_rows(result);//行数
				int index = 0;
				dlgpro->setpos(800);
                while(sql_row=mysql_fetch_row(result))//获取具体的数据
                {
					CString strindex ;
					strindex.Format("%d",index+1);
					m_listUndoRecord.InsertItem(index,strindex);
					int i=0;
					for(i=1;i<=16;i++)
					{
						m_listUndoRecord.SetItemText(index,i,sql_row[i-1]);
					}
					if(index%2==0)
						m_listUndoRecord.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
					index++;
                }//while
				dlgpro->setpos(900);
            }
        }
        else
        {
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
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
		dlgpro->endpos();
		return;
    }
    if(result!=NULL) mysql_free_result(result);//释放结果资源
    mysql_close(&myCont);//断开连接
	dlgpro->endpos();

	return;
	
}

void Dialog_UndoRecord::OnButtonExcel() 
{
	CreateExcel("销单记录.xls",&m_listUndoRecord);
}

BOOL Dialog_UndoRecord::PreTranslateMessage(MSG* pMsg) 
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

void Dialog_UndoRecord::OnColumnclickListChangerecord(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	listsort(&m_listUndoRecord,pNMListView);
	*pResult = 0;
}
