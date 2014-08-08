#if !defined(AFX_DIALOG_STORAGE_IN_H__C9688C71_E458_461E_BB38_D152938A68C2__INCLUDED_)
#define AFX_DIALOG_STORAGE_IN_H__C9688C71_E458_461E_BB38_D152938A68C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Storage_In.h : header file
//
#include "EditListCtrl.h "
#include "LineColorListCtrl.h"
#include "XPButton.h"
/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_In dialog

class Dialog_Storage_In : public CDialog
{
// Construction
public:
	Dialog_Storage_In(CWnd* pParent = NULL);   // standard constructor
	int m_row;
	int m_column;
// Dialog Data
	//{{AFX_DATA(Dialog_Storage_In)
	enum { IDD = IDD_DIALOG_STORAGE_IN };
	CEdit	m_edit2;
	CRichEditCtrl	m_edit;
	CXPButton	m_btExcel;
	CXPButton	m_btSave;
	CXPButton	m_btQuit;
	CXPButton	m_btPrint;
	CXPButton	m_btNew;
	CEditListCtrl	m_listStorageIn;
	CTime	m_timeCurrent;
	CTime	m_timePayment;
	CString	m_StorageInID;
	CString	m_Department;
	CString	m_Digest;
	CString	m_Operator;
	CString	m_Provider;
	CString	m_Storage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_Storage_In)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_Storage_In)
	virtual BOOL OnInitDialog();
	afx_msg void OnExcel();
	afx_msg void OnButtonNew();
	afx_msg void OnButtonPrint();
	afx_msg void OnButtonQuit();
	afx_msg void OnButtonSave();
	afx_msg void OnDblclkRicheditDepartment(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkRicheditDigest(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkRicheditOperator(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkRicheditProvider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkRicheditStorage(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusListStorageIn(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListStorageIn(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEditModify2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_STORAGE_IN_H__C9688C71_E458_461E_BB38_D152938A68C2__INCLUDED_)
