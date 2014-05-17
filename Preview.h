#if !defined(AFX_PREVIEW_H__22E99377_9898_4382_84B0_E284DF4E9F74__INCLUDED_)
#define AFX_PREVIEW_H__22E99377_9898_4382_84B0_E284DF4E9F74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Preview.h : header file
//
#include "StdAfx.h"
/////////////////////////////////////////////////////////////////////////////
// CPreview dialog

class CPreview : public CDialog
{
// Construction
public:
	CPreview(CWnd* pParent = NULL);   // standard constructor
	void DrawReport(CRect rect, CDC *pDC, BOOL isprinted);

	int screenx,screeny;	

	CString m_strTime;
	CString m_strIndex;
	CString	m_strSellName;
	CString	m_strSellPhone;
	
	CString m_strCompanyName;
	CString	m_strUserAddress;
	CString	m_strUserName;
	CString	m_strUserPhone;

	int m_dProCount;
	pProductInfo m_pProInfo;
		
	CString m_strTotalPrice;
	CString m_strSellPrice;
	CString m_strTotalCount;
	CString m_strUpperMoney;
	// Dialog Data
	//{{AFX_DATA(CPreview)
	enum { IDD = IDD_DIGPREVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreview)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPreview)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREVIEW_H__22E99377_9898_4382_84B0_E284DF4E9F74__INCLUDED_)
