#if !defined(AFX_DIALOG_UNPOST_H__42DD6AB5_7A09_4092_B319_A49075C964AE__INCLUDED_)
#define AFX_DIALOG_UNPOST_H__42DD6AB5_7A09_4092_B319_A49075C964AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Unpost.h : header file
//
#include "XPButton.h"
/////////////////////////////////////////////////////////////////////////////
// CDialog_Unpost dialog

class CDialog_Unpost : public CDialog
{
// Construction
public:
	CDialog_Unpost(CWnd* pParent = NULL);   // standard constructor
	int m_permission;
// Dialog Data
	//{{AFX_DATA(CDialog_Unpost)
	enum { IDD = IDD_DIALOG_UNPOST };
	CXPButton	m_btnok;
	CXPButton	m_btn2;
	CXPButton	m_btnpost;
	CComboBox	m_department;
	CString	m_postid1;
	CString	m_postid2;
	CString	m_postid3;
	CString	m_postid4;
	CString	m_postid5;
	CString	m_postnumber1;
	CString	m_postnumber2;
	CString	m_postnumber3;
	CString	m_postnumber4;
	CString	m_postnumber5;
	CString	m_volume1;
	CString	m_volume2;
	CString	m_volume3;
	CString	m_volume4;
	CString	m_volume5;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Unpost)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_Unpost)
	virtual BOOL OnInitDialog();
	afx_msg void OnUnPost();
	afx_msg void OnSelchangeDepartment();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_UNPOST_H__42DD6AB5_7A09_4092_B319_A49075C964AE__INCLUDED_)
