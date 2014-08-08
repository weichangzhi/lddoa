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
		case VK_RETURN: //�س�  
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
	m_listStorageIn.InsertColumn(0, _T("�к�"), LVCFMT_LEFT,60);
	m_listStorageIn.InsertColumn(1, _T("�ֿ���"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(2, _T("�ֿ�ȫ��"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(3, _T("SCB"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(4, _T("����"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(5, _T("����"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(6, _T("����"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(7, _T("���"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(8, _T("��ժҪ"), LVCFMT_LEFT,200);

	CString strindex ;
	int index = 0;
//	while(index<15)
	{
		//strindex.Format("%d",index+1);
		//m_listStorageIn.InsertItem(index,strindex);
		//if(index%2==0)
		//	m_listStorageIn.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));//��ɫ
		//index++;
	}
	
	LONG lStyle;
	lStyle = GetWindowLong(m_listStorageIn.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(m_listStorageIn.m_hWnd, GWL_STYLE, lStyle);//����style
	DWORD dwStyle = m_listStorageIn.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	m_listStorageIn.SetExtendedStyle(dwStyle); //������չ���
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
	m_edit2.GetWindowText(str);//ȡ�ñ༭�������
	m_listStorageIn.SetItemText(m_row,m_column,str);//�������ݸ��µ�CListCtrl��
	m_edit2.ShowWindow(SW_HIDE);//���ر༭��	
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
	   m_row=pNMListView->iItem;//m_rowΪ��ѡ���е�����ţ�int���ͳ�Ա������
	   m_column=pNMListView->iSubItem;//m_columnΪ��ѡ���е�����ţ�int���ͳ�Ա������
	   m_listStorageIn.GetSubItemRect(pNMListView->iItem, pNMListView->iSubItem,LVIR_LABEL,rc);//ȡ������ľ���
	   rc.left+=12;
	   rc.top+=202;
	   rc.right+=12;
	   rc.bottom+=205;
	   char * ch=new char [128];
	   m_listStorageIn.GetItemText(pNMListView->iItem, pNMListView->iSubItem,ch,128);//ȡ�����������
	   m_edit2.SetWindowText(ch);//�������������ʾ���༭����
	   m_edit2.ShowWindow(SW_SHOW);//��ʾ�༭��
	   m_edit2.MoveWindow(&rc);//���༭���ƶ����������棬������������
	   m_edit2.SetFocus();//ʹ�༭��ȡ�ý���
	   m_edit2.CreateSolidCaret(1,rc.Height()-5);//����һ�����
	   m_edit2.ShowCaret();//��ʾ���
	   m_edit2.SetSel(0,-1);//ʹ����Ƶ������
	}
	*pResult = 0;
}


void Dialog_Storage_In::OnKillfocusEditModify2() 
{
	CString str;
	m_edit2.GetWindowText(str);//ȡ�ñ༭�������
	m_listStorageIn.SetItemText(m_row,m_column,str);//�������ݸ��µ�CListCtrl��
	m_edit2.ShowWindow(SW_HIDE);//���ر༭��	
	UpdateData(FALSE);
}
