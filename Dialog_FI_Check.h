#if !defined(AFX_DIALOG_FI_CHECK_H__7E9935CF_6DB3_4B82_B3F6_B351560F8F68__INCLUDED_)
#define AFX_DIALOG_FI_CHECK_H__7E9935CF_6DB3_4B82_B3F6_B351560F8F68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_FI_Check.h : header file
//
#include "XPButton.h"
#include "LineColorListCtrl.h"
#include "Dialog_progress.h"
/////////////////////////////////////////////////////////////////////////////
// Dialog_FI_Check dialog

class Dialog_FI_Check : public CDialog
{
// Construction
public:
	Dialog_FI_Check(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dialog_FI_Check)
	enum { IDD = IDD_DIALOG_FI_CHECK };
	CXPButton	m_btcheck;
	CXPButton	m_btexcel;
	CLineColorListCtrl	m_listFI;
	CXPButton	m_btok;
	CComboBox	m_com_queryway;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_FI_Check)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_FI_Check)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnExcel();
	afx_msg void OnColumnclickListFi(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonCheck();
	afx_msg void OnSelchangeComboQueryWay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_FI_CHECK_H__7E9935CF_6DB3_4B82_B3F6_B351560F8F68__INCLUDED_)
