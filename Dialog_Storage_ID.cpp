// Dialog_Storage_ID.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_Storage_ID.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_ID dialog


Dialog_Storage_ID::Dialog_Storage_ID(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_Storage_ID::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_Storage_ID)
	m_StorageID = _T("");
	//}}AFX_DATA_INIT
}


void Dialog_Storage_ID::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_Storage_ID)
	DDX_Control(pDX, IDOK, m_btok);
	DDX_Control(pDX, IDCANCEL, m_btcancel);
	DDX_Text(pDX, IDC_EDIT_ID, m_StorageID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_Storage_ID, CDialog)
	//{{AFX_MSG_MAP(Dialog_Storage_ID)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_ID message handlers

BOOL Dialog_Storage_ID::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->wParam) 
	{  
	//case VK_RETURN: //回车  
	//	return TRUE;  
	case VK_ESCAPE: //ESC  
		return TRUE;  
	}  
	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL Dialog_Storage_ID::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_Storage_ID::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	m_StorageID.TrimLeft();
	m_StorageID.TrimRight();
	if(m_StorageID.IsEmpty())
	{
		MessageBox("请输入单据编号","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_ID)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_ID))->SetSel(0, -1);
		return;
	}
	CDialog::OnOK();
}
