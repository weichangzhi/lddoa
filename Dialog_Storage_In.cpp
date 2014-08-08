// Dialog_Storage_In.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_Storage_In.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_In dialog


Dialog_Storage_In::Dialog_Storage_In(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_Storage_In::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_Storage_In)
	m_timeCurrent = 0;
	m_timePayment = 0;
	m_StorageInID = _T("");
	m_Department = _T("");
	m_Digest = _T("");
	m_Operator = _T("");
	m_Provider = _T("");
	m_Storage = _T("");
	m_row = 0;
	m_column = 0;
	//}}AFX_DATA_INIT
}


void Dialog_Storage_In::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_Storage_In)
	DDX_Control(pDX, IDC_EDIT_MODIFY2, m_edit2);
	DDX_Control(pDX, IDC_RICHEDIT_MODIFY, m_edit);
	DDX_Control(pDX, IDC_EXCEL, m_btExcel);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_btSave);
	DDX_Control(pDX, IDC_BUTTON_QUIT, m_btQuit);
	DDX_Control(pDX, IDC_BUTTON_PRINT, m_btPrint);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_btNew);
	DDX_Control(pDX, IDC_LIST_STORAGE_IN, m_listStorageIn);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_CURRENT, m_timeCurrent);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_PAYMENT, m_timePayment);
	DDX_Text(pDX, IDC_EDIT_STORAGE_IN_ID, m_StorageInID);
	DDX_Text(pDX, IDC_RICHEDIT_DEPARTMENT, m_Department);
	DDX_Text(pDX, IDC_RICHEDIT_DIGEST, m_Digest);
	DDX_Text(pDX, IDC_RICHEDIT_OPERATOR, m_Operator);
	DDX_Text(pDX, IDC_RICHEDIT_PROVIDER, m_Provider);
	DDX_Text(pDX, IDC_RICHEDIT_STORAGE, m_Storage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_Storage_In, CDialog)
	//{{AFX_MSG_MAP(Dialog_Storage_In)
	ON_BN_CLICKED(IDC_EXCEL, OnExcel)
	ON_BN_CLICKED(IDC_BUTTON_NEW, OnButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnButtonPrint)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, OnButtonQuit)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_NOTIFY(NM_DBLCLK, IDC_RICHEDIT_DEPARTMENT, OnDblclkRicheditDepartment)
	ON_NOTIFY(NM_DBLCLK, IDC_RICHEDIT_DIGEST, OnDblclkRicheditDigest)
	ON_NOTIFY(NM_DBLCLK, IDC_RICHEDIT_OPERATOR, OnDblclkRicheditOperator)
	ON_NOTIFY(NM_DBLCLK, IDC_RICHEDIT_PROVIDER, OnDblclkRicheditProvider)
	ON_NOTIFY(NM_DBLCLK, IDC_RICHEDIT_STORAGE, OnDblclkRicheditStorage)
	ON_NOTIFY(NM_KILLFOCUS, IDC_LIST_STORAGE_IN, OnKillfocusListStorageIn)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_STORAGE_IN, OnDblclkListStorageIn)
	ON_EN_KILLFOCUS(IDC_EDIT_MODIFY2, OnKillfocusEditModify2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_In message handlers

BOOL Dialog_Storage_In::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN) 
	{  
		switch(pMsg->wParam) 
		{  
		case VK_RETURN: //回车  
			return TRUE;  
		case VK_ESCAPE: //ESC  
			return TRUE;  
		}  
	}

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL Dialog_Storage_In::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CTime time1 = CTime::GetCurrentTime();
	m_timeCurrent = time1;
	m_timePayment = time1;
	m_Operator = g_user;
	m_Department = g_department;
	static indexid=0;
	m_StorageInID.Format("JH-%04d-%02d-%02d-%03d",m_timeCurrent.GetYear(),m_timeCurrent.GetMonth(),m_timeCurrent.GetDay(),++indexid);
	
	m_listStorageIn.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listStorageIn.InsertColumn(0, _T("行号"), LVCFMT_LEFT,60);
	m_listStorageIn.InsertColumn(1, _T("仓库编号"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(2, _T("仓库全称"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(3, _T("SCB"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(4, _T("名称"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(5, _T("数量"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(6, _T("单价"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(7, _T("金额"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(8, _T("行摘要"), LVCFMT_LEFT,200);

	CString strindex ;
	int index = 0;
//	while(index<15)
	{
		//strindex.Format("%d",index+1);
		//m_listStorageIn.InsertItem(index,strindex);
		//if(index%2==0)
		//	m_listStorageIn.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));//灰色
		//index++;
	}
	
	LONG lStyle;
	lStyle = GetWindowLong(m_listStorageIn.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_listStorageIn.m_hWnd, GWL_STYLE, lStyle);//设置style
	DWORD dwStyle = m_listStorageIn.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_listStorageIn.SetExtendedStyle(dwStyle); //设置扩展风格
	m_edit2.ShowWindow(SW_HIDE);
	m_edit.ShowWindow(SW_HIDE);

	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_Storage_In::OnExcel() 
{
	// TODO: Add your control notification handler code here
	
}

void Dialog_Storage_In::OnButtonNew() 
{
	// TODO: Add your control notification handler code here
	
}

void Dialog_Storage_In::OnButtonPrint() 
{
	// TODO: Add your control notification handler code here
	
}

void Dialog_Storage_In::OnButtonQuit() 
{
	// TODO: Add your control notification handler code here
	
}

void Dialog_Storage_In::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	
}

void Dialog_Storage_In::OnDblclkRicheditDepartment(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void Dialog_Storage_In::OnDblclkRicheditDigest(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void Dialog_Storage_In::OnDblclkRicheditOperator(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void Dialog_Storage_In::OnDblclkRicheditProvider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void Dialog_Storage_In::OnDblclkRicheditStorage(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}


void Dialog_Storage_In::OnKillfocusListStorageIn(NMHDR* pNMHDR, LRESULT* pResult) 
{
	return;
	CString str;
	m_edit2.GetWindowText(str);//取得编辑框的内容
	m_listStorageIn.SetItemText(m_row,m_column,str);//将该内容更新到CListCtrl中
	m_edit2.ShowWindow(SW_HIDE);//隐藏编辑框	
	UpdateData(FALSE);
	//*pResult = 0;
}

void Dialog_Storage_In::OnDblclkListStorageIn(NMHDR* pNMHDR, LRESULT* pResult) 
{
	return;
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;
	CRect rc;
	if(pNMListView->iItem!=-1)
	{
	   m_row=pNMListView->iItem;//m_row为被选中行的行序号（int类型成员变量）
	   m_column=pNMListView->iSubItem;//m_column为被选中行的列序号（int类型成员变量）
	   m_listStorageIn.GetSubItemRect(pNMListView->iItem, pNMListView->iSubItem,LVIR_LABEL,rc);//取得子项的矩形
	   rc.left+=12;
	   rc.top+=202;
	   rc.right+=12;
	   rc.bottom+=205;
	   char * ch=new char [128];
	   m_listStorageIn.GetItemText(pNMListView->iItem, pNMListView->iSubItem,ch,128);//取得子项的内容
	   m_edit2.SetWindowText(ch);//将子项的内容显示到编辑框中
	   m_edit2.ShowWindow(SW_SHOW);//显示编辑框
	   m_edit2.MoveWindow(&rc);//将编辑框移动到子项上面，覆盖在子项上
	   m_edit2.SetFocus();//使编辑框取得焦点
	   m_edit2.CreateSolidCaret(1,rc.Height()-5);//创建一个光标
	   m_edit2.ShowCaret();//显示光标
	   m_edit2.SetSel(0,-1);//使光标移到最后面
	}
	*pResult = 0;
}


void Dialog_Storage_In::OnKillfocusEditModify2() 
{
	CString str;
	m_edit2.GetWindowText(str);//取得编辑框的内容
	m_listStorageIn.SetItemText(m_row,m_column,str);//将该内容更新到CListCtrl中
	m_edit2.ShowWindow(SW_HIDE);//隐藏编辑框	
	UpdateData(FALSE);
}
