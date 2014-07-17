#if !defined(AFX_DIALOG_MODIFYPASSWD_H__D106B839_8A39_4A71_B5D4_595DA2E03B45__INCLUDED_)
#define AFX_DIALOG_MODIFYPASSWD_H__D106B839_8A39_4A71_B5D4_595DA2E03B45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_ModifyPassWd.h : header file
//
#include "XPButton.h"
/////////////////////////////////////////////////////////////////////////////
// CDialog_ModifyPassWd dialog

class CDialog_ModifyPassWd : public CDialog
{
// Construction
public:
	CDialog_ModifyPassWd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_ModifyPassWd)
	enum { IDD = IDD_DIALOG_MODIFY_PASSWD };
	CXPButton	m_btnOK;
	CXPButton	m_btnCANCEL;
	CString	m_new_passwd;
	CString	m_new_passwd2;
	CString	m_passwd;
	CString	m_user;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_ModifyPassWd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_ModifyPassWd)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_MODIFYPASSWD_H__D106B839_8A39_4A71_B5D4_595DA2E03B45__INCLUDED_)
