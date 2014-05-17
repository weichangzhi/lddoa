#if !defined(AFX_DIALOG_CLIENT_H__CA4E2EA0_9A0B_4A29_A1DF_AF2E0327945F__INCLUDED_)
#define AFX_DIALOG_CLIENT_H__CA4E2EA0_9A0B_4A29_A1DF_AF2E0327945F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DIALOG_CLIENT.h : header file
//
#include "SortListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDIALOG_CLIENT dialog

class CDIALOG_CLIENT : public CDialog
{
// Construction
public:
	CDIALOG_CLIENT(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDIALOG_CLIENT)
	enum { IDD = IDD_DIALOG_CLIENT };
	CListCtrl	m_list_Clinet;
	CComboBox	m_com_Client;
	CString	m_strInput;
	CString	m_strinput;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDIALOG_CLIENT)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDIALOG_CLIENT)
	afx_msg void OnButtonClientAdd();
	afx_msg void OnButtonClientSelect();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListClient(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnCancel();
	afx_msg void OnDelete();
	afx_msg void OnRclickListClient(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickListClient(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnModifyPasswd();
	afx_msg void OnDeleteUser();
	afx_msg void OnModifyPermission();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_CLIENT_H__CA4E2EA0_9A0B_4A29_A1DF_AF2E0327945F__INCLUDED_)
