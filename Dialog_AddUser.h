#if !defined(AFX_DIALOG_ADDUSER_H__81881401_A6A1_4320_A861_E2CDE2F26263__INCLUDED_)
#define AFX_DIALOG_ADDUSER_H__81881401_A6A1_4320_A861_E2CDE2F26263__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_AddUser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog_AddUser dialog

class CDialog_AddUser : public CDialog
{
// Construction
public:
	CDialog_AddUser(CWnd* pParent = NULL);   // standard constructor
	int m_permission;
	CString strdepartment ;
// Dialog Data
	//{{AFX_DATA(CDialog_AddUser)
	enum { IDD = IDD_DIALOG_ADD_USER };
	CComboBox	m_comDepartment;
	CString	m_passwd;
	CString	m_passwd2;
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
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_AddUser)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_AddUser)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeComboDepartment();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_ADDUSER_H__81881401_A6A1_4320_A861_E2CDE2F26263__INCLUDED_)
