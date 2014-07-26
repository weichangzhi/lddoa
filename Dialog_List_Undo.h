#if !defined(AFX_DIALOG_LIST_UNDO_H__ABD03BC1_AEE2_4EE9_9284_548C7299C609__INCLUDED_)
#define AFX_DIALOG_LIST_UNDO_H__ABD03BC1_AEE2_4EE9_9284_548C7299C609__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_List_Undo.h : header file
//
#include "XPButton.h"
/////////////////////////////////////////////////////////////////////////////
// Dialog_List_Undo dialog

class Dialog_List_Undo : public CDialog
{
// Construction
public:
	Dialog_List_Undo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dialog_List_Undo)
	enum { IDD = IDD_DIALOG_LIST_UNDO };
	CXPButton	m_btok;
	CXPButton	m_btcancel;
	CString	m_strcost;
	CString	m_listid;
	CString	m_payment;
	CString	m_strreason;
	CString	m_strdepartment;
	CString	m_strtime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_List_Undo)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_List_Undo)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_LIST_UNDO_H__ABD03BC1_AEE2_4EE9_9284_548C7299C609__INCLUDED_)
