#if !defined(AFX_DIALOG_TIPSSETTING_H__F0BB00A8_1BB4_4B39_8C82_0A73DC2416B4__INCLUDED_)
#define AFX_DIALOG_TIPSSETTING_H__F0BB00A8_1BB4_4B39_8C82_0A73DC2416B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_TipsSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dialog_TipsSetting dialog

class Dialog_TipsSetting : public CDialog
{
// Construction
public:
	Dialog_TipsSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dialog_TipsSetting)
	enum { IDD = IDD_TIPS_SETTING };
	BOOL	m_logintips;
	BOOL	m_timertips;
	CString	m_strhour;
	CString	m_strmin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_TipsSetting)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_TipsSetting)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_TIPSSETTING_H__F0BB00A8_1BB4_4B39_8C82_0A73DC2416B4__INCLUDED_)
