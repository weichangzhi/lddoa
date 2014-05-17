#if !defined(AFX_DIALOG_DELETE_USER_H__DCFBE2D9_AF24_4139_B81A_9B09E2753368__INCLUDED_)
#define AFX_DIALOG_DELETE_USER_H__DCFBE2D9_AF24_4139_B81A_9B09E2753368__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Delete_User.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog_Delete_User dialog

class CDialog_Delete_User : public CDialog
{
// Construction
public:
	CDialog_Delete_User(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_Delete_User)
	enum { IDD = IDD_DIALOG_DELETE_USER };
	CString	m_user;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Delete_User)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_Delete_User)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_DELETE_USER_H__DCFBE2D9_AF24_4139_B81A_9B09E2753368__INCLUDED_)
