#if !defined(AFX_DIALOG_MODIFY_PERMISSION_H__9CB17ABA_A044_471F_8CE5_40AE94A265B5__INCLUDED_)
#define AFX_DIALOG_MODIFY_PERMISSION_H__9CB17ABA_A044_471F_8CE5_40AE94A265B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Modify_Permission.h : header file
//
#include "XPButton.h"
/////////////////////////////////////////////////////////////////////////////
// CDialog_Modify_Permission dialog

class CDialog_Modify_Permission : public CDialog
{
// Construction
public:
	CDialog_Modify_Permission(CWnd* pParent = NULL);   // standard constructor
	int m_permission;
// Dialog Data
	//{{AFX_DATA(CDialog_Modify_Permission)
	enum { IDD = IDD_DIALOG_MODIFY_PERMISSION };
	CXPButton	m_btnok;
	CXPButton	m_btncancel;
	CXPButton	m_btnmodify;
	CComboBox	m_department;
	CString	m_username;
	BOOL	m_del_list;
	BOOL	m_end_list;
	BOOL	m_modify_list_after;
	BOOL	m_modify_list_before;
	BOOL	m_post_pd;
	BOOL	m_post_send;
	BOOL	m_post_storage;
	BOOL	m_post_tc;
	BOOL	m_query_list;
	BOOL	m_refund;
	BOOL	m_save_list;
	BOOL	m_start_list;
	BOOL	m_Bpermission;
	BOOL	m_qc;
	BOOL	m_urgent;
	BOOL	m_fi;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Modify_Permission)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_Modify_Permission)
	virtual void OnOK();
	afx_msg void OnQueryPermission();
	virtual BOOL OnInitDialog();
	afx_msg void OnModify();
	afx_msg void OnSelchangeComboDepartment();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_MODIFY_PERMISSION_H__9CB17ABA_A044_471F_8CE5_40AE94A265B5__INCLUDED_)
