// Dialog_BaseInfo.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_BaseInfo.h"
#include "Dialog_InputBaseinfo.h"
#include "Dialog_Query_list.h"
#include "Dialog_New_List.h"
#include "Dialog_ModifyList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_BaseInfo dialog


CDialog_BaseInfo::CDialog_BaseInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_BaseInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_BaseInfo)
	m_time_bgein = 0;
	m_time_end = 0;
	m_strSubWay = _T("");
	//}}AFX_DATA_INIT
}


void CDialog_BaseInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_BaseInfo)
	DDX_Control(pDX, IDC_COMBO_SUBWAY, m_comSubWay);
	DDX_Control(pDX, IDC_LIST_BASEINFO, m_list_baseinfo);
	DDX_Control(pDX, IDC_COMBO_BASEINFO, m_com_baseinfo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_time_bgein);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_time_end);
	DDX_CBString(pDX, IDC_COMBO_SUBWAY, m_strSubWay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_BaseInfo, CDialog)
	//{{AFX_MSG_MAP(CDialog_BaseInfo)
	ON_BN_CLICKED(IDC_BUTTON_SELL_SELECT, OnButtonSellSelect)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL, OnExcel)
	ON_CBN_SELCHANGE(IDC_COMBO_BASEINFO, OnSelchangeComboBaseinfo)
	ON_WM_HSCROLL()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_BASEINFO, OnColumnclickListBaseinfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_BaseInfo message handlers

void CDialog_BaseInfo::OnButtonSellSelect() 
{
	// TODO: Add your control notification handler code here
	m_list_baseinfo.DeleteAllItems();
	UpdateData();
	CString csSql;
	CString starttime;
	starttime.Format("%04d-%02d-%02d",m_time_bgein.GetYear(),m_time_bgein.GetMonth(),m_time_bgein.GetDay());
	CString endtime;
	endtime.Format("%04d-%02d-%02d",m_time_end.GetYear(),m_time_end.GetMonth(),m_time_end.GetDay()+1);

	int cursel = m_com_baseinfo.GetCurSel();
	switch (cursel)
	{
	case 0://������
		if(m_strSubWay.IsEmpty())
			csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		else
			csSql.Format("select * from baseinfo where  listid=\"%s\" and savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,m_strSubWay,starttime,endtime); 
		break;
	case 1://�ߴ�
		if(m_strSubWay.IsEmpty())
			csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		else
			csSql = "select * from baseinfo where  size LIKE '" + m_strSubWay + "%'  and savelisttime>= '" + starttime + "' and savelisttime<= '" +endtime + "'";
		break;
	case 2://�ռ���
		if(m_strSubWay.IsEmpty())
			csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		else
			csSql = "select * from baseinfo where  receivepeople LIKE '" + m_strSubWay + "%'  and savelisttime>= '" + starttime + "' and savelisttime<= '" +endtime + "'";
		break;
	case 3://������
		if(m_strSubWay.IsEmpty())
			csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		else
			csSql = "select * from baseinfo where  people LIKE '" + m_strSubWay + "%'  and savelisttime>= '" + starttime + "' and savelisttime<= '" +endtime + "'";
		break;
	case 4://����
		if(m_strSubWay.IsEmpty())
			csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		else
			csSql = "select * from baseinfo where  department = '" + m_strSubWay + "'  and savelisttime>= '" + starttime + "' and savelisttime<= '" +endtime + "'";
		break;
	case 5://����
		csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		break;
	default:
		break;
	}
	//csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
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
					m_list_baseinfo.InsertItem(index,strindex);
					m_list_baseinfo.SetItemText(index,1,sql_row[0]);
					m_list_baseinfo.SetItemText(index,2,sql_row[1]);
					m_list_baseinfo.SetItemText(index,3,sql_row[8]);
					m_list_baseinfo.SetItemText(index,4,sql_row[9]);
					m_list_baseinfo.SetItemText(index,5,sql_row[10]);
					m_list_baseinfo.SetItemText(index,6,sql_row[11]);
					m_list_baseinfo.SetItemText(index,7,sql_row[12]);
					m_list_baseinfo.SetItemText(index,8,sql_row[5]);
					m_list_baseinfo.SetItemText(index,9,sql_row[6]);
					m_list_baseinfo.SetItemText(index,10,sql_row[13]);
					m_list_baseinfo.SetItemText(index,11,sql_row[14]);
					m_list_baseinfo.SetItemText(index,12,sql_row[15]);
					m_list_baseinfo.SetItemText(index,13,sql_row[16]);
					m_list_baseinfo.SetItemText(index,14,sql_row[17]);
					m_list_baseinfo.SetItemText(index,15,sql_row[18]);
					m_list_baseinfo.SetItemText(index,16,sql_row[32]);
					m_list_baseinfo.SetItemText(index,17,sql_row[19]);
					m_list_baseinfo.SetItemText(index,18,sql_row[20]);
					m_list_baseinfo.SetItemText(index,19,sql_row[3]);
					m_list_baseinfo.SetItemText(index,20,sql_row[21]);
					m_list_baseinfo.SetItemText(index,21,sql_row[22]);
					m_list_baseinfo.SetItemText(index,22,sql_row[23]);
					m_list_baseinfo.SetItemText(index,23,sql_row[24]);
					m_list_baseinfo.SetItemText(index,24,sql_row[25]);
					m_list_baseinfo.SetItemText(index,25,sql_row[26]);
					m_list_baseinfo.SetItemText(index,26,sql_row[27]);
					m_list_baseinfo.SetItemText(index,27,sql_row[4]);
					m_list_baseinfo.SetItemText(index,28,sql_row[29]);
					if(index%2==0)
						m_list_baseinfo.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
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

BOOL CDialog_BaseInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CTime time1 = CTime::GetCurrentTime();
	m_time_bgein = time1;
	m_time_end = time1;	
	
	m_com_baseinfo.InsertString(0,"������");
	m_com_baseinfo.InsertString(1,"�ߴ�");
	m_com_baseinfo.InsertString(2,"�ռ���");
	m_com_baseinfo.InsertString(3,"������");
	m_com_baseinfo.InsertString(4,"����");
	m_com_baseinfo.InsertString(5,"����");
	m_com_baseinfo.SetCurSel(5);

	m_comSubWay.InsertString(0,"����");
	m_comSubWay.SetCurSel(0);
	
	m_list_baseinfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES | WS_HSCROLL | WS_VSCROLL);
	m_list_baseinfo.InsertColumn(0, _T("���"), LVCFMT_LEFT,60);
	m_list_baseinfo.InsertColumn(1, _T("����"), LVCFMT_LEFT,100);
	m_list_baseinfo.InsertColumn(2, _T("��������"), LVCFMT_LEFT,80);
	m_list_baseinfo.InsertColumn(3, _T("������"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(4, _T("�ռ���"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(5, _T("��ϵ�绰"), LVCFMT_LEFT,100);
	m_list_baseinfo.InsertColumn(6, _T("��ϸ��ַ"), LVCFMT_LEFT,100);
	m_list_baseinfo.InsertColumn(7, _T("����/�ŵ�"), LVCFMT_LEFT,100);
	m_list_baseinfo.InsertColumn(8, _T("�ɵ�����"), LVCFMT_LEFT,100);
	m_list_baseinfo.InsertColumn(9, _T("��������"), LVCFMT_LEFT,100);
	m_list_baseinfo.InsertColumn(10, _T("��ģ"), LVCFMT_LEFT,60);
	m_list_baseinfo.InsertColumn(11, _T("��Ʒ���"), LVCFMT_LEFT,80);
	m_list_baseinfo.InsertColumn(12, _T("ɨ��ҵ��"), LVCFMT_LEFT,80);
	m_list_baseinfo.InsertColumn(13, _T("ģ�ʹ�ӡ"), LVCFMT_LEFT,80);
	m_list_baseinfo.InsertColumn(14, _T("��ģ��"), LVCFMT_LEFT,80);
	m_list_baseinfo.InsertColumn(15, _T("��ģ��"), LVCFMT_LEFT,80);
	m_list_baseinfo.InsertColumn(16, _T("�Ӽ�"), LVCFMT_LEFT,60);
	m_list_baseinfo.InsertColumn(17, _T("�ߴ�"), LVCFMT_LEFT,150);
	m_list_baseinfo.InsertColumn(18, _T("�ӹ�����"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(19, _T("��������"), LVCFMT_LEFT,150);
	m_list_baseinfo.InsertColumn(20, _T("��ɫ"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(21, _T("����"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(22, _T("��ĥ"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(23, _T("��������"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(24, _T("��Ʊ���"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(25, _T("��;"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(26, _T("��Χ"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(27, _T("���"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(28, _T("����Ҫ��"), LVCFMT_LEFT,90);


	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDialog_BaseInfo::OnExcel() 
{
	// TODO: Add your control notification handler code here
	CreateExcel("��������.xls",&m_list_baseinfo);
}

BOOL CDialog_BaseInfo::PreTranslateMessage(MSG* pMsg) 
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

void CDialog_BaseInfo::OnSelchangeComboBaseinfo() 
{
	CString strdepartment;
	CDialog_Query_list *dlg_baseinfo;
	strdepartment = g_department;
	int indexSel = m_com_baseinfo.GetCurSel();
	switch (indexSel)
	{
	case 0://������
		m_comSubWay.ResetContent();
		dlg_baseinfo=new CDialog_Query_list(); 
		dlg_baseinfo->Create(IDD_DIALOG_LIST_QUERY);
		dlg_baseinfo->ShowWindow(SW_SHOW);
		break;
	case 1://�ߴ�
		m_comSubWay.ResetContent();
		m_comSubWay.InsertString(0,"6cm������");
		m_comSubWay.InsertString(1,"12cm������");
		m_comSubWay.InsertString(2,"10cmȫ����");
		m_comSubWay.InsertString(3,"13.14cmȫ����");
		m_comSubWay.InsertString(4,"15cmȫ����");
		m_comSubWay.InsertString(5,"19.9cmȫ����");
		m_comSubWay.InsertString(6,"19.9cm��ɴȫ����");
		m_comSubWay.InsertString(7,"28cmȫ����");
		m_comSubWay.InsertString(8,"6cm���ذ�����");
		m_comSubWay.InsertString(9,"6cm���ذ���˫��");
		m_comSubWay.InsertString(10,"10cm����ȫ����");
		m_comSubWay.InsertString(11,"10cm����ȫ��˫��");
		m_comSubWay.InsertString(12,"10cm����·��");
		m_comSubWay.InsertString(13,"10cm���������ӳ�");
		m_comSubWay.InsertString(14,"10cm����������");
		m_comSubWay.InsertString(15,"10cm������������");
		m_comSubWay.SetCurSel(0);
		break;
	case 2://�ռ���
		m_comSubWay.ResetContent();
		m_comSubWay.InsertString(0,g_user);
		m_comSubWay.SetCurSel(0);
		break;
	case 3://������
		m_comSubWay.ResetContent();
		m_comSubWay.InsertString(0,g_user);
		m_comSubWay.SetCurSel(0);
		break;
	case 4://����
		m_comSubWay.ResetContent();
		m_comSubWay.InsertString(0,"��������");
		m_comSubWay.InsertString(1,"����");
		m_comSubWay.InsertString(2,"��Ӫ");
		m_comSubWay.InsertString(3,"����");
		m_comSubWay.InsertString(4,"�з�");

		if(strdepartment.Compare("��������")==0)
			m_comSubWay.SetCurSel(0);
		else if(strdepartment.Compare("����")==0)
			m_comSubWay.SetCurSel(1);
		else if(strdepartment.Compare("��Ӫ")==0)
			m_comSubWay.SetCurSel(2);
		else if(strdepartment.Compare("����")==0)
			m_comSubWay.SetCurSel(3);
		else if(strdepartment.Compare("�з�")==0)
			m_comSubWay.SetCurSel(4);
		else
			m_comSubWay.SetCurSel(0);
		break;
	case 5://����
		m_comSubWay.ResetContent();
		m_comSubWay.InsertString(0,"����");
		m_comSubWay.SetCurSel(0);
		break;
	default:
		break;
	}
}

void CDialog_BaseInfo::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDialog_BaseInfo::OnSize(UINT nType, int cx, int cy) 
{
/*
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	CRect m_rect(0,0,width,height);
	m_rect.DeflateRect(200,0,20,20);
	this->MoveWindow(m_rect);
	*/
	CDialog::OnSize(nType, cx, cy);
	
}

void CDialog_BaseInfo::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CDialog_BaseInfo::OnColumnclickListBaseinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	listsort(&m_list_baseinfo,pNMListView);
	*pResult = 0;
}
