#if !defined(AFX_DIALOG_STORAGE_LEFT2_H__3B1B69CD_51F4_4BCB_BDB8_6CA802735E03__INCLUDED_)
#define AFX_DIALOG_STORAGE_LEFT2_H__3B1B69CD_51F4_4BCB_BDB8_6CA802735E03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Storage_Left2.h : header file
//
#include "XPButton.h"
#include "LineColorListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_Left2 dialog

class Dialog_Storage_Left2 : public CDialog
{
// Construction
public:
	Dialog_Storage_Left2(CWnd* pParent = NULL);   // standard constructor
	CString m_scb;
	CString m_name;
	CString m_number;
	CString m_unit;
	CString m_price;	
// Dialog Data
	//{{AFX_DATA(Dialog_Storage_Left2)
	enum { IDD = IDD_DIALOG_STORAGE_LEFT2 };
	CXPButton	m_btcancel;
	CXPButton	m_btok;
	CLineColorListCtrl	m_listLeft;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_Storage_Left2)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_Storage_Left2)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListStorageLeft(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_STORAGE_LEFT2_H__3B1B69CD_51F4_4BCB_BDB8_6CA802735E03__INCLUDED_)
