#if !defined(AFX_DIALOG_FI_H__983573EC_76F1_4AF6_9E89_4435B8FD471F__INCLUDED_)
#define AFX_DIALOG_FI_H__983573EC_76F1_4AF6_9E89_4435B8FD471F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_FI.h : header file
//
#include "LineColorListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// Dialog_FI dialog

class Dialog_FI : public CDialog
{
// Construction
public:
	Dialog_FI(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dialog_FI)
	enum { IDD = IDD_DIALOG_FI };
	CLineColorListCtrl	m_listFI;
	CString	m_strlistid_add;
	CString	m_strlistid_query;
	BOOL	m_billing;
	BOOL	m_gathering;
	CTime	m_time_start;
	CTime	m_time_end;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_FI)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_FI)
	virtual BOOL OnInitDialog();
	afx_msg void OnFiadd();
	afx_msg void OnExcel();
	virtual void OnOK();
	afx_msg void OnColumnclickListFi(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_FI_H__983573EC_76F1_4AF6_9E89_4435B8FD471F__INCLUDED_)
