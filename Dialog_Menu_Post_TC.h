#if !defined(AFX_DIALOG_MENU_POST_TC_H__263F499C_C4EB_4342_AC59_E8454D02E77B__INCLUDED_)
#define AFX_DIALOG_MENU_POST_TC_H__263F499C_C4EB_4342_AC59_E8454D02E77B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Menu_Post_TC.h : header file
//
#include "XPButton.h"
/////////////////////////////////////////////////////////////////////////////
// Dialog_Menu_Post_TC dialog

class Dialog_Menu_Post_TC : public CDialog
{
// Construction
public:
	Dialog_Menu_Post_TC(CWnd* pParent = NULL);   // standard constructor
	int m_permission;
// Dialog Data
	//{{AFX_DATA(Dialog_Menu_Post_TC)
	enum { IDD = IDD_DIALOG_MENU_POST_TC };
	CXPButton	m_btCancel;
	CXPButton	m_btOK;
	CComboBox	m_comdepartment;
	int		m_indexdepartment;
	CString	m_list;
	CString	m_postnumber;
	CString	m_volume;
	CString	m_score;
	CString	m_designer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_Menu_Post_TC)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_Menu_Post_TC)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_MENU_POST_TC_H__263F499C_C4EB_4342_AC59_E8454D02E77B__INCLUDED_)
