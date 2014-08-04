#if !defined(AFX_DIALOG_FI_DETAIL_H__C272566F_7B2C_4C5B_89A5_8CF59072EA19__INCLUDED_)
#define AFX_DIALOG_FI_DETAIL_H__C272566F_7B2C_4C5B_89A5_8CF59072EA19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_FI_Detail.h : header file
//
#include "XPButton.h"
#include "LineColorListCtrl.h"
#include "Dialog_progress.h"
/////////////////////////////////////////////////////////////////////////////
// Dialog_FI_Detail dialog

class Dialog_FI_Detail : public CDialog
{
// Construction
public:
	Dialog_FI_Detail(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dialog_FI_Detail)
	enum { IDD = IDD_DIALOG_FI_DETAIL };
	CLineColorListCtrl	m_listFI;
	CXPButton	m_btexcel;
	CXPButton	m_btok;
	CXPButton	m_btproceeds;
	CString	m_query_listid;
	CTime	m_timebegin;
	CTime	m_timeend;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_FI_Detail)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_FI_Detail)
	afx_msg void OnButtonProceeds();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnExcel();
	afx_msg void OnColumnclickListFi(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_FI_DETAIL_H__C272566F_7B2C_4C5B_89A5_8CF59072EA19__INCLUDED_)
