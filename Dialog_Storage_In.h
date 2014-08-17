#if !defined(AFX_DIALOG_STORAGE_IN_H__C9688C71_E458_461E_BB38_D152938A68C2__INCLUDED_)
#define AFX_DIALOG_STORAGE_IN_H__C9688C71_E458_461E_BB38_D152938A68C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Storage_In.h : header file
//
#include "EditListCtrl.h "
#include "XPButton.h"
#include "Dialog_Storage_Print.h"
/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_In dialog

class Dialog_Storage_In : public CDialog
{
// Construction
public:
	Dialog_Storage_In(CWnd* pParent = NULL);   // standard constructor
	BOOL GetConfig();
	BOOL SetConfig();
	void ResetStorageIn();
	void SetPreviewDlg(Dialog_Storage_Print *PreviewDlg);
	int m_row;
	int m_column;
	bool m_bModify;
// Dialog Data
	//{{AFX_DATA(Dialog_Storage_In)
	enum { IDD = IDD_DIALOG_STORAGE_IN };
	CStatic	m_static1;
	CComboBox	m_comStorage;
	CComboBox	m_comProvider;
	CComboBox	m_comOperator;
	CComboBox	m_comDepartment;
	CListCtrl	m_listTotal;
	CXPButton	m_btquery;
	CXPButton	m_btmodify;
	CXPButton	m_btExcel;
	CXPButton	m_btSave;
	CXPButton	m_btQuit;
	CXPButton	m_btPrint;
	CXPButton	m_btNew;
	CEditListCtrl	m_listStorageIn;
	CTime	m_timeCurrent;
	CTime	m_timePayment;
	CString	m_StorageInID;
	CString	m_Digest;
	CString	m_strDepartment;
	CString	m_strOperator;
	CString	m_strProvider;
	CString	m_strStorage;
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
	afx_msg void OnButtonModify();
	afx_msg void OnColumnclickListTotal(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListStorageIn(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButtonQuery();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_STORAGE_IN_H__C9688C71_E458_461E_BB38_D152938A68C2__INCLUDED_)
