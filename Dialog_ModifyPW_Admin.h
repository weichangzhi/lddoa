#if !defined(AFX_DIALOG_MODIFYPW_ADMIN_H__815AEFDF_5F19_4A77_85E3_590894E71C4D__INCLUDED_)
#define AFX_DIALOG_MODIFYPW_ADMIN_H__815AEFDF_5F19_4A77_85E3_590894E71C4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_ModifyPW_Admin.h : header file
//
#include "XPButton.h"
/////////////////////////////////////////////////////////////////////////////
// CDialog_ModifyPW_Admin dialog

class CDialog_ModifyPW_Admin : public CDialog
{
// Construction
public:
	CDialog_ModifyPW_Admin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_ModifyPW_Admin)
	enum { IDD = IDD_DIALOG_MODIFY_PASSWD_ADMIN };
	CXPButton	m_btnCANCEL;
	CXPButton	m_btnOK;
	CString	m_user;
	CString	m_new_passwd;
	CString	m_new_passwd2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_ModifyPW_Admin)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_ModifyPW_Admin)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_MODIFYPW_ADMIN_H__815AEFDF_5F19_4A77_85E3_590894E71C4D__INCLUDED_)
