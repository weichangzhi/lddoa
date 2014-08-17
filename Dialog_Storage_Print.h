#if !defined(AFX_DIALOG_STORAGE_PRINT_H__37469EB3_DAAE_4F0D_A820_A302E0AA899B__INCLUDED_)
#define AFX_DIALOG_STORAGE_PRINT_H__37469EB3_DAAE_4F0D_A820_A302E0AA899B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Storage_Print.h : header file
//
#include "StdAfx.h"
/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_Print dialog

class Dialog_Storage_Print : public CDialog
{
// Construction
public:
	Dialog_Storage_Print(CWnd* pParent = NULL);   // standard constructor
	void DrawReport(CRect rect, CDC *pDC, BOOL isprinted,BOOL isIn);
	CString	m_strCurrent;
	CString	m_strPayment;
	CString	m_StorageInID;
	CString	m_Digest;
	CString	m_strDepartment;
	CString	m_strOperator;
	CString	m_strProvider;
	CString	m_strStorage;
	CListCtrl *m_list; 
	int screenx;
	int screeny;
// Dialog Data
	//{{AFX_DATA(Dialog_Storage_Print)
	enum { IDD = IDD_DIALOG_STORAGE_PRINT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_Storage_Print)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_Storage_Print)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_STORAGE_PRINT_H__37469EB3_DAAE_4F0D_A820_A302E0AA899B__INCLUDED_)
