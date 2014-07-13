#if !defined(AFX_DIALOG_DETAIL_H__73FE9BB1_68F1_401A_971E_A033D4638207__INCLUDED_)
#define AFX_DIALOG_DETAIL_H__73FE9BB1_68F1_401A_971E_A033D4638207__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Detail.h : header file
//

#include "LineColorListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CDialog_Detail dialog

class CDialog_Detail : public CDialog
{
// Construction
public:
	CDialog_Detail(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_Detail)
	enum { IDD = IDD_DIALOG_DETAIL };
	CLineColorListCtrl	m_listdetail;
	CString	m_listid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Detail)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_Detail)
	virtual BOOL OnInitDialog();
	afx_msg void OnDetailSelect();
	afx_msg void OnExcel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnColumnclickListDetail(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_DETAIL_H__73FE9BB1_68F1_401A_971E_A033D4638207__INCLUDED_)
