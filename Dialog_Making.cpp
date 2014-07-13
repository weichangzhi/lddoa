// Dialog_Making.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_Making.h"
#include "Dialog_Menu_Post.h"

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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Making message handlers

BOOL CDialog_Making::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_list_schedule.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list_schedule.InsertColumn(0, _T("���"), LVCFMT_LEFT,50);
	m_list_schedule.InsertColumn(1, _T("������"), LVCFMT_LEFT,100);
	m_list_schedule.InsertColumn(2, _T("��Ʒ����"), LVCFMT_LEFT,100);
	m_list_schedule.InsertColumn(3, _T("������"), LVCFMT_LEFT,100);
	m_list_schedule.InsertColumn(4, _T("Ӫ������"), LVCFMT_LEFT,80);
	m_list_schedule.InsertColumn(5, _T("��Ʒ����"), LVCFMT_LEFT,80);
	m_list_schedule.InsertColumn(6, _T("��������"), LVCFMT_LEFT,150);
	m_list_schedule.InsertColumn(7, _T("��Ʒ���(cm3)"), LVCFMT_LEFT,120);
	m_list_schedule.InsertColumn(8, _T("�յ�����"), LVCFMT_LEFT,100);
	m_list_schedule.InsertColumn(9, _T("��������"), LVCFMT_LEFT,100);
	//m_list_schedule.InsertColumn(8, _T("��ݵ���"), LVCFMT_LEFT,120);
	m_list_schedule.InsertColumn(10, _T("������"), LVCFMT_LEFT,60);
	m_list_schedule.InsertColumn(11, _T("������"), LVCFMT_LEFT,60);
	m_list_schedule.InsertColumn(12, _T("�ʼ�"), LVCFMT_LEFT,60);
	m_list_schedule.InsertColumn(13, _T("��Ʒ��"), LVCFMT_LEFT,60);     
	CTime time1 = CTime::GetCurrentTime();
	m_timebegin = time1;
	m_timeend = time1;

	CString m_department = g_department;
	m_ComDepartment.InsertString(0,"��������");
	m_ComDepartment.InsertString(1,"����");
	m_ComDepartment.InsertString(2,"��Ӫ");
	m_ComDepartment.InsertString(3,"����");
	m_ComDepartment.InsertString(4,"�з�");
	m_ComDepartment.InsertString(5,"ȫ��");
	if(m_department.Compare("��������")==0)
		m_ComDepartment.SetCurSel(0);
	else if(m_department.Compare("����")==0)
		m_ComDepartment.SetCurSel(1);
	else if(m_department.Compare("��Ӫ")==0)
		m_ComDepartment.SetCurSel(2);
	else if(m_department.Compare("����")==0)
		m_ComDepartment.SetCurSel(3);
	else if(m_department.Compare("�з�")==0)
		m_ComDepartment.SetCurSel(4);
	else
		m_ComDepartment.SetCurSel(5);

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

	CString strDepartment;
	m_ComDepartment.GetWindowText(strDepartment);
	int indexsel = m_ComDepartment.GetCurSel();
	if (indexsel==5)
		csSql.Format("select baseinfo.listid,baseinfo.listname,people,department,truelistnumber,material,volume,reveivedate,enddate,schedule.tcnumber,schedule.pdnumber,schedule.qcnumber,schedule.storagenumber,schedule.hasstoragenumber,baseinfo.urgent from baseinfo,schedule,scheduledetail where baseinfo.listid=schedule.listid and schedule.listid=scheduledetail.listid and end=0  and  businessendtime>=\"%s\" and businessendtime<=\"%s\"  " ,starttime,endtime);
	else
		csSql.Format("select baseinfo.listid,baseinfo.listname,people,department,truelistnumber,material,volume,reveivedate,enddate,schedule.tcnumber,schedule.pdnumber,schedule.qcnumber,schedule.storagenumber,schedule.hasstoragenumber,baseinfo.urgent from baseinfo,schedule,scheduledetail where baseinfo.listid=schedule.listid and schedule.listid=scheduledetail.listid and end=0 and baseinfo.department=\"%s\" and  businessendtime>=\"%s\" and businessendtime<=\"%s\"  " ,strDepartment,starttime,endtime);

	MYSQL myCont;
    MYSQL_RES *result;
    MYSQL_ROW sql_row;
    int res;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
    {
        mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����

		CString curtime;
		CString strsql ;
		strsql.Format("select now()");
		if(mysql_query(&myCont,strsql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			return;
		}
		result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
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
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			return;
		}


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
					if((atoi(sql_row[13]) >= atoi(sql_row[4])) && (atoi(sql_row[4])!=0))//��Ʒ���ѹ��˵���Ŀ�ﵽ�������Ͳ���ʾ
						continue;
					CString strindex ;
					strindex.Format("%d",index+1);
					m_list_schedule.InsertItem(index,strindex);
					int i=0;
					for(i=1;i<=9;i++)
					{
						m_list_schedule.SetItemText(index,i,sql_row[i-1]);
					}
					for(i=10;i<=13;i++)
					{
						if(atoi(sql_row[i-1])==0)
							m_list_schedule.SetItemText(index,i,"");
						else
							m_list_schedule.SetItemText(index,i,sql_row[i-1]);
					}
					int tcnumber = atoi(sql_row[9]);
					int pdnumber = atoi(sql_row[10]);
					if(index%2==0)
						m_list_schedule.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
					if (sql_row[14]!=NULL)
					{
						int spanday = CalcDaySpan(curtime,sql_row[8]);
						if (atoi(sql_row[14])==1)//�Ӽ� ��ɫ
						{
							m_list_schedule.SetItemColor(index,RGB(230,230,230),RGB(128,0,128));
						}
						else if (spanday<0)//sql_row[8]�������� ��ʱ ��ɫ
						{
							m_list_schedule.SetItemColor(index,RGB(0,0,0),RGB(255,0,0));
						}
						else if(spanday<2 && spanday>=0 &&  pdnumber>0)
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
	CreateExcel("����Ʒ�嵥.xls",&m_list_schedule);		
}

void CDialog_Making::OnRclickListSchdeule(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CMenu       menu ,* pSubMenu;//��������Ҫ�õ���cmenu����	
	menu.LoadMenu(IDR_MENU_POST);//װ���Զ�����Ҽ��˵�
	pSubMenu = menu.GetSubMenu(0);//��ȡ��һ�������˵������Ե�һ���˵��������Ӳ˵�	
    CPoint oPoint;//����һ������ȷ�����λ�õ�λ��	
    GetCursorPos( &oPoint);//��ȡ��ǰ����λ�ã��Ա�ʹ�ò˵����Ը�����
	int istat=m_list_schedule.GetSelectionMark();//��istat��ŵ�ǰѡ�����ǵڼ���	
	if(istat == -1) return;
	pSubMenu->TrackPopupMenu (TPM_LEFTALIGN, oPoint.x, oPoint.y, this); //��ָ��λ����ʾ�����˵�
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
                sql_row=mysql_fetch_row(result);//��ȡ���������
				if(sql_row)
                {
					int i=0;
					for(i=10;i<=13;i++)
					{
						if(atoi(sql_row[i-10])==0)
							m_list_schedule.SetItemText(cursel,i,"");
						else
							m_list_schedule.SetItemText(cursel,i,sql_row[i-10]);
					}
					UpdateData(FALSE);
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

void CDialog_Making::OnMenuitemPostTC() 
{
	int istat=m_list_schedule.GetSelectionMark();
	if(istat == -1) return;
	CString curnumber = m_list_schedule.GetItemText(istat,10);
	CString nextnumber = m_list_schedule.GetItemText(istat,11);
	Dialog_Menu_Post dlg;
	dlg.m_indexdepartment = 0;
	dlg.m_permission = POST_TC;
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
		m_list_schedule.SetItemText(istat,10,strleftnumber);
		strleftnumber.Format("%d",atoi(nextnumber) + haspostnumber);
		m_list_schedule.SetItemText(istat,11,strleftnumber);
	}
}

void CDialog_Making::OnMenuitemPostPd() 
{
	int istat=m_list_schedule.GetSelectionMark();
	if(istat == -1) return;
	CString curnumber = m_list_schedule.GetItemText(istat,11);
	CString nextnumber = m_list_schedule.GetItemText(istat,12);
	Dialog_Menu_Post dlg;
	dlg.m_indexdepartment = 1;
	dlg.m_permission = POST_PD;
	dlg.m_listid = m_list_schedule.GetItemText(istat,1);	
	dlg.m_postnumber = curnumber;
	int ret = dlg.DoModal();
	if (ret==IDOK)
	{
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

void CDialog_Making::OnMenuitemPostQc() 
{
	int istat=m_list_schedule.GetSelectionMark();
	if(istat == -1) return;
	CString curnumber = m_list_schedule.GetItemText(istat,12);
	CString nextnumber = m_list_schedule.GetItemText(istat,13);
	Dialog_Menu_Post dlg;
	dlg.m_indexdepartment = 2;
	dlg.m_permission = QC;
	dlg.m_listid = m_list_schedule.GetItemText(istat,1);	
	dlg.m_postnumber = curnumber;
	int ret = dlg.DoModal();
	if (ret==IDOK)
	{
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

void CDialog_Making::OnMenuitemPostStorage() 
{
	int istat=m_list_schedule.GetSelectionMark();
	if(istat == -1) return;
	CString curnumber = m_list_schedule.GetItemText(istat,13);
	CString nextnumber = m_list_schedule.GetItemText(istat,14);
	Dialog_Menu_Post dlg;
	dlg.m_indexdepartment = 3;
	dlg.m_permission = POST_STORAGE;
	dlg.m_listid = m_list_schedule.GetItemText(istat,1);	
	dlg.m_postnumber = curnumber;
	int ret = dlg.DoModal();
	if (ret==IDOK)
	{
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
