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

	CString m_str_reveive_time;
	CString m_str_end_date;

	CString	m_design_server;
	CString	m_has_modeling;
	CString	m_modeling;
	CString	m_modeling_pring;
	CString	m_no_modeling;
	CString	m_scan;
	CString	m_urgent;

	CString	m_address;
	CString	m_bill;
	CString	m_bottom;
	CString	m_color;
	CString	m_department;
	CString	m_error_range;
	CString	m_listid;
	CString	m_listname;
	CString	m_material;
	CString	m_money;
	CString	m_print;
	CString	m_people;
	CString	m_phone;
	CString	m_receivename;
	CString	m_shine;
	CString	m_size;	
	CString	m_usage;
	CString	m_volume;
	CString	m_other;

	CString	m_totel_number;
	CString	m_true_number;
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
