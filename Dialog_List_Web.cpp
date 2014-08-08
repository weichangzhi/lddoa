// Dialog_List_Web.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_List_Web.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_List_Web dialog


Dialog_List_Web::Dialog_List_Web(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_List_Web::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_List_Web)
	m_timebegin = 0;
	m_timeend = 0;
	//}}AFX_DATA_INIT
}


void Dialog_List_Web::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_List_Web)
	DDX_Control(pDX, IDC_BUTTON_LIST_START, m_btliststart);
	DDX_Control(pDX, IDOK, m_btok);
	DDX_Control(pDX, IDC_LIST_BASEINFO, m_listweb);
	DDX_Control(pDX, IDC_BUTTON_EXCEL, m_btexcel);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_timebegin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_timeend);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_List_Web, CDialog)
	//{{AFX_MSG_MAP(Dialog_List_Web)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL, OnButtonExcel)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_BASEINFO, OnColumnclickListBaseinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BASEINFO, OnDblclkListBaseinfo)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_LIST_START, OnButtonListStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_List_Web message handlers

BOOL Dialog_List_Web::PreTranslateMessage(MSG* pMsg) 
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

BOOL Dialog_List_Web::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CTime time1 = CTime::GetCurrentTime();
	m_timebegin = time1;
	m_timeend = time1;	

	m_listweb.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES | WS_HSCROLL | WS_VSCROLL);
	m_listweb.InsertColumn(0, _T("序号"), LVCFMT_LEFT,60);
	m_listweb.InsertColumn(1, _T("单号"), LVCFMT_LEFT,100);
	m_listweb.InsertColumn(2, _T("订单名称"), LVCFMT_LEFT,300);
	m_listweb.InsertColumn(3, _T("经办人"), LVCFMT_LEFT,90);
	m_listweb.InsertColumn(4, _T("收件人"), LVCFMT_LEFT,90);
	m_listweb.InsertColumn(5, _T("联系电话"), LVCFMT_LEFT,100);
	m_listweb.InsertColumn(6, _T("详细地址"), LVCFMT_LEFT,100);
	m_listweb.InsertColumn(7, _T("部门/门店"), LVCFMT_LEFT,100);
	m_listweb.InsertColumn(8, _T("派单日期"), LVCFMT_LEFT,100);
	m_listweb.InsertColumn(9, _T("交货日期"), LVCFMT_LEFT,100);
	m_listweb.InsertColumn(10, _T("建模"), LVCFMT_LEFT,60);
	m_listweb.InsertColumn(11, _T("设计服务"), LVCFMT_LEFT,80);
	m_listweb.InsertColumn(12, _T("扫描业务"), LVCFMT_LEFT,80);
	m_listweb.InsertColumn(13, _T("模型打印"), LVCFMT_LEFT,80);
	m_listweb.InsertColumn(14, _T("有模型"), LVCFMT_LEFT,80);
	m_listweb.InsertColumn(15, _T("无模型"), LVCFMT_LEFT,80);
	m_listweb.InsertColumn(16, _T("加急"), LVCFMT_LEFT,60);
	m_listweb.InsertColumn(17, _T("尺寸"), LVCFMT_LEFT,150);
	m_listweb.InsertColumn(18, _T("加工数量"), LVCFMT_LEFT,90);
	m_listweb.InsertColumn(19, _T("制作材料"), LVCFMT_LEFT,150);
	m_listweb.InsertColumn(20, _T("颜色"), LVCFMT_LEFT,90);
	m_listweb.InsertColumn(21, _T("喷漆"), LVCFMT_LEFT,90);
	m_listweb.InsertColumn(22, _T("打磨"), LVCFMT_LEFT,90);
	m_listweb.InsertColumn(23, _T("底座搭配"), LVCFMT_LEFT,90);
	m_listweb.InsertColumn(24, _T("发票随寄"), LVCFMT_LEFT,90);
	m_listweb.InsertColumn(25, _T("用途"), LVCFMT_LEFT,90);
	m_listweb.InsertColumn(26, _T("误差范围"), LVCFMT_LEFT,90);
	m_listweb.InsertColumn(27, _T("签单金额"), LVCFMT_LEFT,100);
	m_listweb.InsertColumn(28, _T("体积"), LVCFMT_LEFT,90);
	m_listweb.InsertColumn(29, _T("其他要求"), LVCFMT_LEFT,90);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_List_Web::OnOK() 
{
	m_listweb.DeleteAllItems();
	UpdateData();
	CString csSql;
	//CString starttime;
	//starttime.Format("%04d-%02d-%02d",m_timebegin.GetYear(),m_timebegin.GetMonth(),m_timebegin.GetDay());
	//CString endtime;
//	endtime.Format("%04d-%02d-%02d",m_timeend.GetYear(),m_timeend.GetMonth(),m_timeend.GetDay()+1);

	csSql.Format("select keke_witkey_order.order_id, order_name,username,mobile,area,address,order_time,ys_end_time,num,price\
		from keke_witkey_order,keke_witkey_order_detail,keke_witkey_address where order_time>=%d and order_time<=%d and \
		keke_witkey_order.order_id=keke_witkey_order_detail.order_id and keke_witkey_order.order_uid=keke_witkey_address.uid" ,m_timebegin,m_timeend); 

	
//	csSql.Format("select * from keke_witkey_order where  order_time>=%d and order_time<=%d " ,m_timebegin,m_timeend); 

	//csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
    MYSQL myCont;
    MYSQL_RES *result;
    MYSQL_ROW sql_row;
    int res;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,g_MysqlConnect_web.host,g_MysqlConnect_web.user,g_MysqlConnect_web.pswd,g_MysqlConnect_web.table,g_MysqlConnect_web.port,NULL,0))
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
					m_listweb.InsertItem(index,strindex);
					m_listweb.SetItemText(index,1,sql_row[0]);//单号
					m_listweb.SetItemText(index,2,sql_row[1]);//订单名称
					m_listweb.SetItemText(index,4,sql_row[2]);//收件人
					m_listweb.SetItemText(index,5,sql_row[3]);//联系电话
					CString straddress;
					straddress.Format("%s,%s",sql_row[4], sql_row[5]);
					m_listweb.SetItemText(index,6,straddress);//详细地址
					if(sql_row[6]!=NULL)
					{
						CTime TimeOrder(time_t(atol(sql_row[6])));
						CString starttime;
						starttime.Format("%04d-%02d-%02d",TimeOrder.GetYear(),TimeOrder.GetMonth(),TimeOrder.GetDay());
						m_listweb.SetItemText(index,8,starttime);//派单日期
					}
					if(sql_row[7]!=NULL)
					{
						CTime TimeEnd(time_t(atol(sql_row[7])));
						CString endtime;
						endtime.Format("%04d-%02d-%02d",TimeEnd.GetYear(),TimeEnd.GetMonth(),TimeEnd.GetDay()+1);
						m_listweb.SetItemText(index,9,endtime);//交货日期
					}
					m_listweb.SetItemText(index,18,sql_row[8]);//加工数量
					CString strmatrail1(sql_row[1]);
					int index1 = strmatrail1.ReverseFind('[');
					int index2 = strmatrail1.ReverseFind(']');
					CString strmatrail2;
					strmatrail2 = strmatrail1.Mid(index1+1,index2-index1-1);
					m_listweb.SetItemText(index,19,strmatrail2);//制作材料
					if(sql_row[8]!=NULL && sql_row[9]!=NULL)
					{
						double money = atoi(sql_row[8]) * atof(sql_row[9]);
						CString strMoney;
						strMoney.Format("%0.2f",money);
						m_listweb.SetItemText(index,27,strMoney);//签单金额
					}
					if(index%2==0)
						m_listweb.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
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
	
	//CDialog::OnOK();
}

void Dialog_List_Web::OnButtonExcel() 
{
	CreateExcel("网络订单资料.xls",&m_listweb);
}

void Dialog_List_Web::OnColumnclickListBaseinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	listsort(&m_listweb,pNMListView);	
	*pResult = 0;
}

void Dialog_List_Web::OnDblclkListBaseinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int sel=m_listweb.GetSelectionMark();
	if(sel==-1) return;
	this->ShowWindow(SW_HIDE);
	CDialog_New_List * DlgNewList =(CDialog_New_List*)( ((CGoodsManageSystemDlg*)AfxGetMainWnd())->m_treePages[6]);
	DlgNewList->SetDlgItemText(IDC_EDIT_LISTID,m_listweb.GetItemText(sel,1));
	DlgNewList->SetDlgItemText(IDC_EDIT_LISTTNAME,m_listweb.GetItemText(sel,2));
	DlgNewList->SetDlgItemText(IDC_EDIT_RECEIVE_NAME,m_listweb.GetItemText(sel,4));
	DlgNewList->SetDlgItemText(IDC_EDIT_PHONE,m_listweb.GetItemText(sel,5));
	DlgNewList->SetDlgItemText(IDC_EDIT_ADDRESS,m_listweb.GetItemText(sel,6));
	DlgNewList->SetDlgItemText(IDC_EDIT_TOTEL_NUMBER,m_listweb.GetItemText(sel,18));
	DlgNewList->m_ComMaterial.SetCurSel(-1);
	DlgNewList->SetDlgItemText(IDC_COMBO_MATERIAL,m_listweb.GetItemText(sel,19));
	DlgNewList->SetDlgItemText(IDC_EDIT_MONDY,m_listweb.GetItemText(sel,27));
	DlgNewList->m_ComColor.SetCurSel(3);
	DlgNewList->m_ComPaint1.SetCurSel(0);
	DlgNewList->m_ComShine.SetCurSel(1);
	DlgNewList->m_ComBottom.SetCurSel(0);
	DlgNewList->m_ComBill.SetCurSel(0);
	CString strdata = m_listweb.GetItemText(sel,8);
	if(!strdata.IsEmpty())
	{
		CTime timeTmp(atoi(strdata.Mid(0,4)),atoi(strdata.Mid(5,2)),atoi(strdata.Mid(8,2)),0,0,0,0);
		DlgNewList->m_ctrlReveiveDate.SetTime(&timeTmp);	
	}
	CString enddata = m_listweb.GetItemText(sel,9);
	if(!enddata.IsEmpty())
	{
		CTime timeTmp1(atoi(enddata.Mid(0,4)),atoi(enddata.Mid(5,2)),atoi(enddata.Mid(8,2)),0,0,0,0);
		DlgNewList->m_ctrlEndDate.SetTime(&timeTmp1);
	}
	else
		DlgNewList->m_ctrlEndDate.SetTime(&(CTime::GetCurrentTime()));

	UpdateData(FALSE);
	DlgNewList->ShowWindow(SW_SHOW);
	((CGoodsManageSystemDlg*)AfxGetMainWnd())->m_tree.SelectItem(((CGoodsManageSystemDlg*)AfxGetMainWnd())->m_itemNewList);
	*pResult = 0;
}

HBRUSH Dialog_List_Web::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd->GetDlgCtrlID() == IDC_STATIC_TIPS)   
	{   
		pDC->SetTextColor(RGB(255,0,0));   
	}  
	return hbr;
}

void Dialog_List_Web::OnButtonListStart() 
{
	int sel=m_listweb.GetSelectionMark();
	if(sel==-1) return;
	this->ShowWindow(SW_HIDE);
	CDialog_New_List * DlgNewList =(CDialog_New_List*)( ((CGoodsManageSystemDlg*)AfxGetMainWnd())->m_treePages[6]);
	DlgNewList->SetDlgItemText(IDC_EDIT_LISTID,m_listweb.GetItemText(sel,1));
	DlgNewList->SetDlgItemText(IDC_EDIT_LISTTNAME,m_listweb.GetItemText(sel,2));
	DlgNewList->SetDlgItemText(IDC_EDIT_RECEIVE_NAME,m_listweb.GetItemText(sel,4));
	DlgNewList->SetDlgItemText(IDC_EDIT_PHONE,m_listweb.GetItemText(sel,5));
	DlgNewList->SetDlgItemText(IDC_EDIT_ADDRESS,m_listweb.GetItemText(sel,6));
	DlgNewList->SetDlgItemText(IDC_EDIT_TOTEL_NUMBER,m_listweb.GetItemText(sel,18));
	DlgNewList->m_ComMaterial.SetCurSel(-1);
	DlgNewList->SetDlgItemText(IDC_COMBO_MATERIAL,m_listweb.GetItemText(sel,19));
	DlgNewList->SetDlgItemText(IDC_EDIT_MONDY,m_listweb.GetItemText(sel,27));
	DlgNewList->m_ComColor.SetCurSel(3);
	DlgNewList->m_ComPaint1.SetCurSel(0);
	DlgNewList->m_ComShine.SetCurSel(1);
	DlgNewList->m_ComBottom.SetCurSel(0);
	DlgNewList->m_ComBill.SetCurSel(0);
	CString strdata = m_listweb.GetItemText(sel,8);
	if(!strdata.IsEmpty())
	{
		CTime timeTmp(atoi(strdata.Mid(0,4)),atoi(strdata.Mid(5,2)),atoi(strdata.Mid(8,2)),0,0,0,0);
		DlgNewList->m_ctrlReveiveDate.SetTime(&timeTmp);	
	}
	CString enddata = m_listweb.GetItemText(sel,9);
	if(!enddata.IsEmpty())
	{
		CTime timeTmp1(atoi(enddata.Mid(0,4)),atoi(enddata.Mid(5,2)),atoi(enddata.Mid(8,2)),0,0,0,0);
		DlgNewList->m_ctrlEndDate.SetTime(&timeTmp1);
	}
	else
		DlgNewList->m_ctrlEndDate.SetTime(&(CTime::GetCurrentTime()));

	UpdateData(FALSE);
	DlgNewList->ShowWindow(SW_SHOW);
	((CGoodsManageSystemDlg*)AfxGetMainWnd())->m_tree.SelectItem(((CGoodsManageSystemDlg*)AfxGetMainWnd())->m_itemNewList);
}
