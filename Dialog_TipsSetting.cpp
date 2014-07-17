// Dialog_TipsSetting.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_TipsSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_TipsSetting dialog


Dialog_TipsSetting::Dialog_TipsSetting(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_TipsSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_TipsSetting)
	m_logintips = TRUE;
	m_timertips = TRUE;
	m_strhour = _T("14");
	m_strmin = _T("00");
	//}}AFX_DATA_INIT
}


void Dialog_TipsSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_TipsSetting)
	DDX_Control(pDX, IDC_BUTTON1, m_btn1);
	DDX_Control(pDX, IDOK, m_btnok);
	DDX_Check(pDX, IDC_CHECK_LOGINTIPS, m_logintips);
	DDX_Check(pDX, IDC_CHECK_TIMERTIPS, m_timertips);
	DDX_Text(pDX, IDC_EDIT1, m_strhour);
	DDX_Text(pDX, IDC_EDIT2, m_strmin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_TipsSetting, CDialog)
	//{{AFX_MSG_MAP(Dialog_TipsSetting)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_TipsSetting message handlers

BOOL Dialog_TipsSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString strpathini="";
	::GetCurrentDirectory(_MAX_PATH,strpathini.GetBuffer(_MAX_PATH));
	strpathini.ReleaseBuffer();
	strpathini = strpathini + "\\" + CONFIGINI;
	char buf[_MAX_PATH] = {0};
	m_logintips = GetPrivateProfileInt("Tips", "LoginTips", 1, strpathini);
	m_timertips = GetPrivateProfileInt("Tips", "TimerTips", 1, strpathini);
	//if (m_timertips)
	{
		GetPrivateProfileString("Tips", "Timer", DEFAULT_TIME, buf, _MAX_PATH, strpathini);
		CString timertime;
		timertime = buf;
		m_strhour = timertime.Mid(0,2);
		m_strmin = timertime.Mid(3,2);
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_TipsSetting::OnOK() 
{
	UpdateData();
	if(m_timertips)
	{
		if (m_strhour.IsEmpty() || m_strmin.IsEmpty())
		{
			MessageBox("请输入定时的时间","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT1)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT1))->SetSel(0, -1);
			return;
		}
		else
		{
			if (!IsNum(m_strhour))
			{
				MessageBox("请输入数字","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT1)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT1))->SetSel(0, -1);
				return;
			}
			if (!IsNum(m_strmin))
			{
				MessageBox("请输入数字","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT2)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT2))->SetSel(0, -1);
				return;
			}
			int hour = atoi(m_strhour);
			int min = atoi(m_strmin);
			if (hour<0 || hour > 24  )
			{
				MessageBox("请输入正确的时间","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT1)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT1))->SetSel(0, -1);
				return;
			}
			if (min<0 || min>60)
			{
				MessageBox("请输入正确的时间","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT2)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT2))->SetSel(0, -1);
				return;
			}
		}
	}

	CString strpathini="";
	::GetCurrentDirectory(_MAX_PATH,strpathini.GetBuffer(_MAX_PATH));
	strpathini.ReleaseBuffer();
	strpathini = strpathini + "\\" + CONFIGINI;

	CString strtips ;
	strtips.Format("%d",m_logintips);
	::WritePrivateProfileString("Tips","LoginTips",strtips,strpathini);
	strtips.Format("%d",m_timertips);
	::WritePrivateProfileString("Tips","TimerTips",strtips,strpathini);
	if (m_timertips)
	{
		strtips.Format("%s:%s",m_strhour,m_strmin);
		::WritePrivateProfileString("Tips","Timer",strtips,strpathini);
	}
	CDialog::OnOK();
}

HBRUSH Dialog_TipsSetting::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd->GetDlgCtrlID() == IDC_STATIC_TIPS)   
	{   
		pDC->SetTextColor(RGB(255,0,0));   
	}  
	return hbr;
}

BOOL Dialog_TipsSetting::PreTranslateMessage(MSG* pMsg) 
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
