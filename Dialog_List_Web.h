#if !defined(AFX_DIALOG_LIST_WEB_H__1CBA9424_19DB_4D11_A92F_2BAD8F984DB1__INCLUDED_)
#define AFX_DIALOG_LIST_WEB_H__1CBA9424_19DB_4D11_A92F_2BAD8F984DB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_List_Web.h : header file
//
#include "XPButton.h"
#include "LineColorListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// Dialog_List_Web dialog

class Dialog_List_Web : public CDialog
{
// Construction
public:
	Dialog_List_Web(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dialog_List_Web)
	enum { IDD = IDD_DIALOG_LIST_WEB };
	CXPButton	m_btliststart;
	CXPButton	m_btok;
	CLineColorListCtrl	m_listweb;
	CXPButton	m_btexcel;
	CTime	m_timebegin;
	CTime	m_timeend;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_List_Web)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_List_Web)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonExcel();
	afx_msg void OnColumnclickListBaseinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListBaseinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButtonListStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_LIST_WEB_H__1CBA9424_19DB_4D11_A92F_2BAD8F984DB1__INCLUDED_)
