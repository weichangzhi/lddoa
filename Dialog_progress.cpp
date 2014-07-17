// Dialog_progress.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_progress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_progress dialog


Dialog_progress::Dialog_progress(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_progress::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_progress)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dialog_progress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_progress)
	DDX_Control(pDX, IDC_PROGRESS, m_cProgress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_progress, CDialog)
	//{{AFX_MSG_MAP(Dialog_progress)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_progress message handlers

BOOL Dialog_progress::PreTranslateMessage(MSG* pMsg) 
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

BOOL Dialog_progress::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CenterWindow();
	ModifyStyleEx(0,0x00080000);
	HINSTANCE hInst = LoadLibrary("User32.DLL"); 
	if(hInst) 
	{ 
		typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD); 
		MYFUNC fun = NULL;
		//取得SetLayeredWindowAttributes（）函数指针 
		fun=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		if(fun)fun(this->GetSafeHwnd(),0,100,2); 
		FreeLibrary(hInst); 
	} 

	// TODO: Add extra initialization here
	m_clrText = m_cProgress.GetTextColor();
	m_clrBk = m_cProgress.GetBkColor();
	m_clrStart = m_cProgress.GetStartColor();
	m_clrEnd = m_cProgress.GetEndColor();

	//设置参数
	m_cProgress.SetRange(0, 1000);

	m_cProgress.SetStartColor(m_clrStart);
	m_cProgress.SetEndColor(m_clrEnd);
	m_cProgress.SetTextColor(m_clrText);
	m_cProgress.SetBkColor(m_clrBk);
	m_cProgress.SetPos(200);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
BOOL PeekAndPump()
{
	static MSG msg;

	while (::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)) {
		if (!AfxGetApp()->PumpMessage()) {
			::PostQuitMessage(0);
			return FALSE;
		}	
	}

	return TRUE;
}

void Dialog_progress::setpos(int i) 
{
	PeekAndPump();
	m_cProgress.SetPos(i);
	//Sleep(1000);
}

void Dialog_progress::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
void Dialog_progress::endpos()
{
	CDialog::OnOK();
}