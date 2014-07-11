#if !defined(AFX_DIALOG_LOGIN2_H__258CC9B7_13DC_40C2_AB85_BEB9BA474862__INCLUDED_)
#define AFX_DIALOG_LOGIN2_H__258CC9B7_13DC_40C2_AB85_BEB9BA474862__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Login2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog_Login2 dialog

class CDialog_Login2 : public CDialog
{
// Construction
public:
	CDialog_Login2(CWnd* pParent = NULL);   // standard constructor
	int m_urgent;
// Dialog Data
	//{{AFX_DATA(CDialog_Login2)
	enum { IDD = IDD_DIALOG_LOGIN2 };
	CString	m_passwd;
	CString	m_user;
	CString	m_department;
	int		m_permission;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Login2)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_Login2)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_LOGIN2_H__258CC9B7_13DC_40C2_AB85_BEB9BA474862__INCLUDED_)
