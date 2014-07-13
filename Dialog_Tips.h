#if !defined(AFX_DIALOG_TIPS_H__249221BB_8D5A_4686_9E81_E7AB296F0DCB__INCLUDED_)
#define AFX_DIALOG_TIPS_H__249221BB_8D5A_4686_9E81_E7AB296F0DCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Tips.h : header file
//
#include "LineColorListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// Dialog_Tips dialog

class Dialog_Tips : public CDialog
{
// Construction
public:
	Dialog_Tips(CWnd* pParent = NULL);   // standard constructor
	void querysql();
	BOOL m_blogintips;
// Dialog Data
	//{{AFX_DATA(Dialog_Tips)
	enum { IDD = IDD_DIALOG_TIPS };
	CLineColorListCtrl	m_litTips;
	CString	m_strtips;
	BOOL	m_boolTips;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_Tips)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_Tips)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_TIPS_H__249221BB_8D5A_4686_9E81_E7AB296F0DCB__INCLUDED_)
