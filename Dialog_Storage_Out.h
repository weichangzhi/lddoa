#if !defined(AFX_DIALOG_STORAGE_OUT_H__72264C47_96F0_43BC_91FB_C98E140FD9CE__INCLUDED_)
#define AFX_DIALOG_STORAGE_OUT_H__72264C47_96F0_43BC_91FB_C98E140FD9CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Storage_Out.h : header file
//
#include "EditListCtrl.h "
#include "XPButton.h"
/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_Out dialog

class Dialog_Storage_Out : public CDialog
{
// Construction
public:
	Dialog_Storage_Out(CWnd* pParent = NULL);   // standard constructor
	int m_row;
	int m_column;
// Dialog Data
	//{{AFX_DATA(Dialog_Storage_Out)
	enum { IDD = IDD_DIALOG_STORAGE_OUT };
	CXPButton	m_btexcel;
	CXPButton	m_btsave;
	CXPButton	m_btquit;
	CXPButton	m_btquery;
	CXPButton	m_btprint;
	CXPButton	m_btnew;
	CXPButton	m_btmodify;
	CTime	m_timeCurrent;
	CTime	m_timePayment;
	CListCtrl	m_listTotal;
	CEditListCtrl	m_listStorageIn;
	CString	m_StorageInID;
	CString	m_Department;
	CString	m_Digest;
	CString	m_Operator;
	CString	m_Provider;
	CString	m_Storage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_Storage_Out)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_Storage_Out)
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_STORAGE_OUT_H__72264C47_96F0_43BC_91FB_C98E140FD9CE__INCLUDED_)
