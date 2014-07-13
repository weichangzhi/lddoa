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
	case 0://订单号
		if(m_strSubWay.IsEmpty())
			csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		else
			csSql.Format("select * from baseinfo where  listid=\"%s\" and savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,m_strSubWay,starttime,endtime); 
		break;
	case 1://尺寸
		if(m_strSubWay.IsEmpty())
			csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		else
			csSql = "select * from baseinfo where  size LIKE '" + m_strSubWay + "%'  and savelisttime>= '" + starttime + "' and savelisttime<= '" +endtime + "'";
		break;
	case 2://收件人
		if(m_strSubWay.IsEmpty())
			csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		else
			csSql = "select * from baseinfo where  receivepeople LIKE '" + m_strSubWay + "%'  and savelisttime>= '" + starttime + "' and savelisttime<= '" +endtime + "'";
		break;
	case 3://经办人
		if(m_strSubWay.IsEmpty())
			csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		else
			csSql = "select * from baseinfo where  people LIKE '" + m_strSubWay + "%'  and savelisttime>= '" + starttime + "' and savelisttime<= '" +endtime + "'";
		break;
	case 4://部门
		if(m_strSubWay.IsEmpty())
			csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		else
			csSql = "select * from baseinfo where  department = '" + m_strSubWay + "'  and savelisttime>= '" + starttime + "' and savelisttime<= '" +endtime + "'";
		break;
	case 5://所有
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

BOOL CDialog_BaseInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CTime time1 = CTime::GetCurrentTime();
	m_time_bgein = time1;
	m_time_end = time1;	
	
	m_com_baseinfo.InsertString(0,"订单号");
	m_com_baseinfo.InsertString(1,"尺寸");
	m_com_baseinfo.InsertString(2,"收件人");
	m_com_baseinfo.InsertString(3,"经办人");
	m_com_baseinfo.InsertString(4,"部门");
	m_com_baseinfo.InsertString(5,"所有");
	m_com_baseinfo.SetCurSel(5);

	m_comSubWay.InsertString(0,"所有");
	m_comSubWay.SetCurSel(0);
	
	m_list_baseinfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES | WS_HSCROLL | WS_VSCROLL);
	m_list_baseinfo.InsertColumn(0, _T("序号"), LVCFMT_LEFT,60);
	m_list_baseinfo.InsertColumn(1, _T("单号"), LVCFMT_LEFT,100);
	m_list_baseinfo.InsertColumn(2, _T("订单名称"), LVCFMT_LEFT,80);
	m_list_baseinfo.InsertColumn(3, _T("经办人"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(4, _T("收件人"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(5, _T("联系电话"), LVCFMT_LEFT,100);
	m_list_baseinfo.InsertColumn(6, _T("详细地址"), LVCFMT_LEFT,100);
	m_list_baseinfo.InsertColumn(7, _T("部门/门店"), LVCFMT_LEFT,100);
	m_list_baseinfo.InsertColumn(8, _T("派单日期"), LVCFMT_LEFT,100);
	m_list_baseinfo.InsertColumn(9, _T("交货日期"), LVCFMT_LEFT,100);
	m_list_baseinfo.InsertColumn(10, _T("建模"), LVCFMT_LEFT,60);
	m_list_baseinfo.InsertColumn(11, _T("设计服务"), LVCFMT_LEFT,80);
	m_list_baseinfo.InsertColumn(12, _T("扫描业务"), LVCFMT_LEFT,80);
	m_list_baseinfo.InsertColumn(13, _T("模型打印"), LVCFMT_LEFT,80);
	m_list_baseinfo.InsertColumn(14, _T("有模型"), LVCFMT_LEFT,80);
	m_list_baseinfo.InsertColumn(15, _T("无模型"), LVCFMT_LEFT,80);
	m_list_baseinfo.InsertColumn(16, _T("加急"), LVCFMT_LEFT,60);
	m_list_baseinfo.InsertColumn(17, _T("尺寸"), LVCFMT_LEFT,150);
	m_list_baseinfo.InsertColumn(18, _T("加工数量"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(19, _T("制作材料"), LVCFMT_LEFT,150);
	m_list_baseinfo.InsertColumn(20, _T("颜色"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(21, _T("喷漆"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(22, _T("打磨"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(23, _T("底座搭配"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(24, _T("发票随寄"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(25, _T("用途"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(26, _T("误差范围"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(27, _T("体积"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(28, _T("其他要求"), LVCFMT_LEFT,90);


	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDialog_BaseInfo::OnExcel() 
{
	// TODO: Add your control notification handler code here
	CreateExcel("订单资料.xls",&m_list_baseinfo);
}

BOOL CDialog_BaseInfo::PreTranslateMessage(MSG* pMsg) 
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

void CDialog_BaseInfo::OnSelchangeComboBaseinfo() 
{
	CString strdepartment;
	CDialog_Query_list *dlg_baseinfo;
	strdepartment = g_department;
	int indexSel = m_com_baseinfo.GetCurSel();
	switch (indexSel)
	{
	case 0://订单号
		m_comSubWay.ResetContent();
		dlg_baseinfo=new CDialog_Query_list(); 
		dlg_baseinfo->Create(IDD_DIALOG_LIST_QUERY);
		dlg_baseinfo->ShowWindow(SW_SHOW);
		break;
	case 1://尺寸
		m_comSubWay.ResetContent();
		m_comSubWay.InsertString(0,"6cm半身单人");
		m_comSubWay.InsertString(1,"12cm半身单人");
		m_comSubWay.InsertString(2,"10cm全身单人");
		m_comSubWay.InsertString(3,"13.14cm全身单人");
		m_comSubWay.InsertString(4,"15cm全身单人");
		m_comSubWay.InsertString(5,"19.9cm全身单人");
		m_comSubWay.InsertString(6,"19.9cm婚纱全身单人");
		m_comSubWay.InsertString(7,"28cm全身单人");
		m_comSubWay.InsertString(8,"6cm车载半身单人");
		m_comSubWay.InsertString(9,"6cm车载半身双人");
		m_comSubWay.InsertString(10,"10cm车载全身单人");
		m_comSubWay.InsertString(11,"10cm车载全身双人");
		m_comSubWay.InsertString(12,"10cm动漫路飞");
		m_comSubWay.InsertString(13,"10cm动漫美国队长");
		m_comSubWay.InsertString(14,"10cm动漫蝙蝠侠");
		m_comSubWay.InsertString(15,"10cm动漫德玛西亚");
		m_comSubWay.SetCurSel(0);
		break;
	case 2://收件人
		m_comSubWay.ResetContent();
		m_comSubWay.InsertString(0,g_user);
		m_comSubWay.SetCurSel(0);
		break;
	case 3://经办人
		m_comSubWay.ResetContent();
		m_comSubWay.InsertString(0,g_user);
		m_comSubWay.SetCurSel(0);
		break;
	case 4://部门
		m_comSubWay.ResetContent();
		m_comSubWay.InsertString(0,"意造销售");
		m_comSubWay.InsertString(1,"电商");
		m_comSubWay.InsertString(2,"运营");
		m_comSubWay.InsertString(3,"加盟");
		m_comSubWay.InsertString(4,"研发");

		if(strdepartment.Compare("意造销售")==0)
			m_comSubWay.SetCurSel(0);
		else if(strdepartment.Compare("电商")==0)
			m_comSubWay.SetCurSel(1);
		else if(strdepartment.Compare("运营")==0)
			m_comSubWay.SetCurSel(2);
		else if(strdepartment.Compare("加盟")==0)
			m_comSubWay.SetCurSel(3);
		else if(strdepartment.Compare("研发")==0)
			m_comSubWay.SetCurSel(4);
		else
			m_comSubWay.SetCurSel(0);
		break;
	case 5://所有
		m_comSubWay.ResetContent();
		m_comSubWay.InsertString(0,"所有");
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
