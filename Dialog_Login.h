#if !defined(AFX_DIALOG_LOGIN_H__58CA584C_40A6_4945_95EC_8D4E400C5AF1__INCLUDED_)
#define AFX_DIALOG_LOGIN_H__58CA584C_40A6_4945_95EC_8D4E400C5AF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Login.h : header file
//
#include "XPButton.h"
/////////////////////////////////////////////////////////////////////////////
// CDialog_Login dialog

class CDialog_Login : public CDialog
{
// Construction
public:
	CDialog_Login(CWnd* pParent = NULL);   // standard constructor
	CString m_strip;
// Dialog Data
	//{{AFX_DATA(CDialog_Login)
	enum { IDD = IDD_DIALOG_LOGIN };
	CXPButton	m_btnModifyPasswd;
	CXPButton	m_btnOK;
	CIPAddressCtrl	m_ipaddress;
	CString	m_user;
	CString	m_passwd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Login)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_Login)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnModifyPasswd();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_LOGIN_H__58CA584C_40A6_4945_95EC_8D4E400C5AF1__INCLUDED_)
