// Dialog_Making.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_Making.h"
#include "Dialog_Menu_Post.h"
#include "Dialog_progress.h"
#include "Dialog_Menu_Post_TC.h"

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
	DDX_Control(pDX, IDC_EXCEL, m_btnexcel);
	DDX_Control(pDX, IDC_BUTTON_SCHDEULE_SELECT, m_btnquery);
	DDX_Control(pDX, IDC_EDIT_LIST, m_edit);
	DDX_Control(pDX, IDC_COMBO_DEPARTMENT, m_ComDepartment);
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
	ON_NOTIFY(NM_RCLICK, IDC_LIST_SCHDEULE, OnRclickListSchdeule)
	ON_COMMAND(ID_MENUITEM_POST_TC, OnMenuitemPostTC)
	ON_COMMAND(ID_MENUITEM_POST_PD, OnMenuitemPostPd)
	ON_COMMAND(ID_MENUITEM_POST_QC, OnMenuitemPostQc)
	ON_COMMAND(ID_MENUITEM_POST_STORAGE, OnMenuitemPostStorage)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_SCHDEULE, OnColumnclickListSchdeule)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SCHDEULE, OnDblclkListSchdeule)
	ON_EN_KILLFOCUS(IDC_EDIT_LIST, OnKillfocusEditList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Making message handlers

BOOL CDialog_Making::OnInitDialog() 
{
	CDialog::OnInitDialog();

	LONG lStyle;
	lStyle = GetWindowLong(m_list_schedule.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_list_schedule.m_hWnd, GWL_STYLE, lStyle);//设置style
	DWORD dwStyle = m_list_schedule.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_list_schedule.SetExtendedStyle(dwStyle); //设置扩展风格
	m_edit.ShowWindow(SW_HIDE);

	m_list_schedule.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list_schedule.InsertColumn(0, _T("序号"), LVCFMT_LEFT,50);
	m_list_schedule.InsertColumn(1, _T("订单号"), LVCFMT_LEFT,100);
	m_list_schedule.InsertColumn(2, _T("产品名称"), LVCFMT_LEFT,100);
	m_list_schedule.InsertColumn(3, _T("经办人"), LVCFMT_LEFT,100);
	m_list_schedule.InsertColumn(4, _T("设计师"), LVCFMT_LEFT,100);
	m_list_schedule.InsertColumn(5, _T("营销部门"), LVCFMT_LEFT,80);
	m_list_schedule.InsertColumn(6, _T("产品总数"), LVCFMT_LEFT,80);
	m_list_schedule.InsertColumn(7, _T("制作材料"), LVCFMT_LEFT,150);
	m_list_schedule.InsertColumn(8, _T("产品体积(cm3)"), LVCFMT_LEFT,120);
	m_list_schedule.InsertColumn(9, _T("收单日期"), LVCFMT_LEFT,100);
	m_list_schedule.InsertColumn(10, _T("交货日期"), LVCFMT_LEFT,100);
	//m_list_schedule.InsertColumn(8, _T("快递单号"), LVCFMT_LEFT,120);
	m_list_schedule.InsertColumn(11, _T("技术部"), LVCFMT_LEFT,60);
	m_list_schedule.InsertColumn(12, _T("生产部"), LVCFMT_LEFT,60);
	m_list_schedule.InsertColumn(13, _T("质检"), LVCFMT_LEFT,60);
	m_list_schedule.InsertColumn(14, _T("成品仓"), LVCFMT_LEFT,60);     
	CTime time1 = CTime::GetCurrentTime();
	m_timebegin = time1;
	m_timeend = time1;

	CString m_department = g_department;
	m_ComDepartment.InsertString(0,"意造销售");
	m_ComDepartment.InsertString(1,"电商");
	m_ComDepartment.InsertString(2,"运营");
	m_ComDepartment.InsertString(3,"加盟");
	m_ComDepartment.InsertString(4,"研发");
	m_ComDepartment.InsertString(5,"全部");
	if(m_department.Compare("意造销售")==0)
		m_ComDepartment.SetCurSel(0);
	else if(m_department.Compare("电商")==0)
		m_ComDepartment.SetCurSel(1);
	else if(m_department.Compare("运营")==0)
		m_ComDepartment.SetCurSel(2);
	else if(m_department.Compare("加盟")==0)
		m_ComDepartment.SetCurSel(3);
	else if(m_department.Compare("研发")==0)
		m_ComDepartment.SetCurSel(4);
	else
		m_ComDepartment.SetCurSel(5);

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
	int count = m_list_schedule.GetItemCount();
	for(int i=0;i<count;i++)
		m_list_schedule.SetItemColor(i,RGB(0,0,0),RGB(255,255,255));
	m_list_schedule.DeleteAllItems();
	UpdateData();
	CString csSql;
	CString starttime;
	starttime.Format("%04d-%02d-%02d",m_timebegin.GetYear(),m_timebegin.GetMonth(),m_timebegin.GetDay());
	CString endtime;
	endtime.Format("%04d-%02d-%02d",m_timeend.GetYear(),m_timeend.GetMonth(),m_timeend.GetDay()+1);

	CString strDepartment;
	m_ComDepartment.GetWindowText(strDepartment);
	int indexsel = m_ComDepartment.GetCurSel();
	if (indexsel==5)
		csSql.Format("select baseinfo.listid,baseinfo.listname,people,desinger,department,truelistnumber,material,volume,reveivedate,enddate,schedule.tcnumber,schedule.pdnumber,schedule.qcnumber,schedule.storagenumber,schedule.hasstoragenumber,baseinfo.urgent from baseinfo,schedule,scheduledetail where baseinfo.listid=schedule.listid and schedule.listid=scheduledetail.listid and end=0  and  businessendtime>=\"%s\" and businessendtime<=\"%s\"  " ,starttime,endtime);
	else
		csSql.Format("select baseinfo.listid,baseinfo.listname,people,desinger,department,truelistnumber,material,volume,reveivedate,enddate,schedule.tcnumber,schedule.pdnumber,schedule.qcnumber,schedule.storagenumber,schedule.hasstoragenumber,baseinfo.urgent from baseinfo,schedule,scheduledetail where baseinfo.listid=schedule.listid and schedule.listid=scheduledetail.listid and end=0 and baseinfo.department=\"%s\" and  businessendtime>=\"%s\" and businessendtime<=\"%s\"  " ,strDepartment,starttime,endtime);

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
        mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
		dlgpro->setpos(500);
		CString curtime;
		CString strsql ;
		strsql.Format("select now()");
		if(mysql_query(&myCont,strsql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
			return;
		}
		dlgpro->setpos(600);
		result=mysql_store_result(&myCont);//保存查询到的数据到result
		if(result)
		{
			sql_row=mysql_fetch_row(result);
			CString tmp = sql_row[0];
			curtime = tmp.Mid(0,10);
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


        res=mysql_query(&myCont,csSql);//查询
		dlgpro->setpos(700);
        if(!res)
        {
            result=mysql_store_result(&myCont);//保存查询到的数据到result
			dlgpro->setpos(950);
			dlgpro->endpos();
		    if(result)
            {
                int j;
                j=mysql_num_fields(result);//查看多少列
				unsigned __int64 num = mysql_num_rows(result);//行数
				int index = 0;
                while(sql_row=mysql_fetch_row(result))//获取具体的数据
                {
					if((atoi(sql_row[14]) >= atoi(sql_row[5])) && (atoi(sql_row[5])!=0))//成品仓已过账的数目达到总数，就不显示
						continue;
					CString strindex ;
					strindex.Format("%d",index+1);
					m_list_schedule.InsertItem(index,strindex);
					int i=0;
					for(i=1;i<=10;i++)
					{
						m_list_schedule.SetItemText(index,i,sql_row[i-1]);
					}
					for(i=11;i<=14;i++)
					{
						if(atoi(sql_row[i-1])==0)
							m_list_schedule.SetItemText(index,i,"");
						else
							m_list_schedule.SetItemText(index,i,sql_row[i-1]);
					}
					int tcnumber = atoi(sql_row[10]);
					int pdnumber = atoi(sql_row[11]);
					if(index%2==0)
						m_list_schedule.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));//灰色
					if (sql_row[15]!=NULL)
					{
						int spanday = CalcDaySpan(curtime,sql_row[9]);
						if (atoi(sql_row[15])==1)//加急 紫色
						{
							m_list_schedule.SetItemColor(index,RGB(230,230,230),RGB(128,0,128));
						}
						else if (spanday<0)//sql_row[8]交货日期 超时 红色
						{
							m_list_schedule.SetItemColor(index,RGB(0,0,0),RGB(255,128,128));
						}
						else if(spanday<2 && spanday>=0 &&  pdnumber>0)//即将到期 黄色
						{
							m_list_schedule.SetItemColor(index,RGB(0,0,0),RGB(255,255,128));
						}
						else if(spanday<3 &&  spanday>=0 && tcnumber>0)
						{
							m_list_schedule.SetItemColor(index,RGB(0,0,0),RGB(255,255,128));
						}
					}
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

void CDialog_Making::OnRclickListSchdeule(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CMenu       menu ,* pSubMenu;//定义下面要用到的cmenu对象	
	menu.LoadMenu(IDR_MENU_POST);//装载自定义的右键菜单
	pSubMenu = menu.GetSubMenu(0);//获取第一个弹出菜单，所以第一个菜单必须有子菜单	
    CPoint oPoint;//定义一个用于确定光标位置的位置	
    GetCursorPos( &oPoint);//获取当前光标的位置，以便使得菜单可以跟随光标
	int istat=m_list_schedule.GetSelectionMark();//用istat存放当前选定的是第几项	
	if(istat == -1) return;
	pSubMenu->TrackPopupMenu (TPM_LEFTALIGN, oPoint.x, oPoint.y, this); //在指定位置显示弹出菜单
	*pResult = 0;
}

void CDialog_Making::updatelist(int cursel)
{
	CString csSql;
	CString listid = m_list_schedule.GetItemText(cursel,1);
	csSql.Format("select tcnumber,pdnumber,qcnumber,storagenumber from schedule where listid=\"%s\" ",listid);

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
                sql_row=mysql_fetch_row(result);//获取具体的数据
				if(sql_row)
                {
					int i=0;
					for(i=11;i<=14;i++)
					{
						if(atoi(sql_row[i-11])==0)
							m_list_schedule.SetItemText(cursel,i,"");
						else
							m_list_schedule.SetItemText(cursel,i,sql_row[i-11]);
					}
					UpdateData(FALSE);
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

void CDialog_Making::OnMenuitemPostTC() 
{
	int istat=m_list_schedule.GetSelectionMark();
	if(istat == -1) return;
	CString curnumber = m_list_schedule.GetItemText(istat,11);
	CString nextnumber = m_list_schedule.GetItemText(istat,12);
	Dialog_Menu_Post_TC dlg;
	dlg.m_indexdepartment = 0;
	dlg.m_permission = POST_TC;
	dlg.m_list = m_list_schedule.GetItemText(istat,1);	
	dlg.m_postnumber = curnumber;
	int ret = dlg.DoModal();
	if (ret==IDOK)
	{
		updatelist(istat);
		return;
		CString strleftnumber ;
		int haspostnumber = atoi(dlg.m_postnumber);
		int leftnumber = atoi(curnumber) - haspostnumber;
		if (leftnumber==0)
			strleftnumber.Format("");
		else
			strleftnumber.Format("%d",leftnumber);
		m_list_schedule.SetItemText(istat,11,strleftnumber);
		strleftnumber.Format("%d",atoi(nextnumber) + haspostnumber);
		m_list_schedule.SetItemText(istat,12,strleftnumber);
	}
}

void CDialog_Making::OnMenuitemPostPd() 
{
	int istat=m_list_schedule.GetSelectionMark();
	if(istat == -1) return;
	CString curnumber = m_list_schedule.GetItemText(istat,12);
	CString nextnumber = m_list_schedule.GetItemText(istat,13);
	Dialog_Menu_Post dlg;
	dlg.m_indexdepartment = 1;
	dlg.m_permission = POST_PD;
	dlg.m_listid = m_list_schedule.GetItemText(istat,1);	
	dlg.m_postnumber = curnumber;
	int ret = dlg.DoModal();
	if (ret==IDOK)
	{
		updatelist(istat);
		return;
		CString strleftnumber ;
		int haspostnumber = atoi(dlg.m_postnumber);
		int leftnumber = atoi(curnumber) - haspostnumber;
		if (leftnumber==0)
			strleftnumber.Format("");
		else
			strleftnumber.Format("%d",leftnumber);
		m_list_schedule.SetItemText(istat,12,strleftnumber);
		strleftnumber.Format("%d",atoi(nextnumber) + haspostnumber);
		m_list_schedule.SetItemText(istat,13,strleftnumber);
	}
}

void CDialog_Making::OnMenuitemPostQc() 
{
	int istat=m_list_schedule.GetSelectionMark();
	if(istat == -1) return;
	CString curnumber = m_list_schedule.GetItemText(istat,13);
	CString nextnumber = m_list_schedule.GetItemText(istat,14);
	Dialog_Menu_Post dlg;
	dlg.m_indexdepartment = 2;
	dlg.m_permission = QC;
	dlg.m_listid = m_list_schedule.GetItemText(istat,1);	
	dlg.m_postnumber = curnumber;
	int ret = dlg.DoModal();
	if (ret==IDOK)
	{
		updatelist(istat);
		return;
		CString strleftnumber ;
		int haspostnumber = atoi(dlg.m_postnumber);
		int leftnumber = atoi(curnumber) - haspostnumber;
		if (leftnumber==0)
			strleftnumber.Format("");
		else
			strleftnumber.Format("%d",leftnumber);
		m_list_schedule.SetItemText(istat,13,strleftnumber);
		strleftnumber.Format("%d",atoi(nextnumber) + haspostnumber);
		m_list_schedule.SetItemText(istat,14,strleftnumber);
	}
	
}

void CDialog_Making::OnMenuitemPostStorage() 
{
	int istat=m_list_schedule.GetSelectionMark();
	if(istat == -1) return;
	CString curnumber = m_list_schedule.GetItemText(istat,14);
	CString nextnumber = m_list_schedule.GetItemText(istat,15);
	Dialog_Menu_Post dlg;
	dlg.m_indexdepartment = 3;
	dlg.m_permission = POST_STORAGE;
	dlg.m_listid = m_list_schedule.GetItemText(istat,1);	
	dlg.m_postnumber = curnumber;
	int ret = dlg.DoModal();
	if (ret==IDOK)
	{
		updatelist(istat);
		return;
		CString strleftnumber ;
		int haspostnumber = atoi(dlg.m_postnumber);
		int leftnumber = atoi(curnumber) - haspostnumber;
		if (leftnumber==0)
			strleftnumber.Format("");
		else
			strleftnumber.Format("%d",leftnumber);
		m_list_schedule.SetItemText(istat,14,strleftnumber);
		strleftnumber.Format("%d",atoi(nextnumber) + haspostnumber);
		m_list_schedule.SetItemText(istat,15,strleftnumber);
	}
}

void CDialog_Making::OnColumnclickListSchdeule(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	//listsort(&m_list_schedule,pNMListView);	
	*pResult = 0;
}

void CDialog_Making::OnDblclkListSchdeule(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;
	CRect rc;
	if(pNMListView->iItem!=-1)
	{
	   int m_row=pNMListView->iItem;//m_row为被选中行的行序号（int类型成员变量）
	   int m_column=pNMListView->iSubItem;//m_column为被选中行的列序号（int类型成员变量）
	   m_list_schedule.GetSubItemRect(pNMListView->iItem, pNMListView->iSubItem,LVIR_LABEL,rc);//取得子项的矩形
	   rc.left+=3;
	   rc.top+=52;
	   rc.right+=3;
	   rc.bottom+=55;
	   char * ch=new char [128];
	   m_list_schedule.GetItemText(pNMListView->iItem, pNMListView->iSubItem,ch,128);//取得子项的内容
	   m_edit.SetWindowText(ch);//将子项的内容显示到编辑框中
	   m_edit.ShowWindow(SW_SHOW);//显示编辑框
	   m_edit.MoveWindow(&rc);//将编辑框移动到子项上面，覆盖在子项上
	   m_edit.SetFocus();//使编辑框取得焦点
	   m_edit.CreateSolidCaret(1,rc.Height()-5);//创建一个光标
	   m_edit.ShowCaret();//显示光标
	   m_edit.SetSel(0,-1);//使光标移到最后面
	}
	*pResult = 0;
}

void CDialog_Making::OnKillfocusEditList() 
{
	CString str;
	m_edit.GetWindowText(str);//取得编辑框的内容
	m_edit.ShowWindow(SW_HIDE);//隐藏编辑框	
}
