#if !defined(AFX_DIALOG_FI_QUERY_H__12A2F57E_C19C_4F2D_8FCE_1F719D93FA22__INCLUDED_)
#define AFX_DIALOG_FI_QUERY_H__12A2F57E_C19C_4F2D_8FCE_1F719D93FA22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_FI_Query.h : header file
//
#include "XPButton.h"
#include "LineColorListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// Dialog_FI_Query dialog

class Dialog_FI_Query : public CDialog
{
// Construction
public:
	Dialog_FI_Query(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(Dialog_FI_Query)
	enum { IDD = IDD_DIALOG_FI_QUERY };
	CXPButton	m_btok;
	CXPButton	m_btexcel;
	CLineColorListCtrl	m_listFI;
	CComboBox	m_comQueryWay;
	CXPButton	m_btproceeds;
	CTime	m_timebegin;
	CTime	m_timeend;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_FI_Query)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_FI_Query)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnExcel();
	afx_msg void OnButtonProceeds();
	afx_msg void OnColumnclickListFi(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickListFi(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnModify();
	afx_msg void OnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_FI_QUERY_H__12A2F57E_C19C_4F2D_8FCE_1F719D93FA22__INCLUDED_)
