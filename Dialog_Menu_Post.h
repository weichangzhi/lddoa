#if !defined(AFX_DIALOG_MENU_POST_H__E215E308_940B_46E6_934F_23F76B2F7122__INCLUDED_)
#define AFX_DIALOG_MENU_POST_H__E215E308_940B_46E6_934F_23F76B2F7122__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Menu_Post.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dialog_Menu_Post dialog

class Dialog_Menu_Post : public CDialog
{
// Construction
public:
	Dialog_Menu_Post(CWnd* pParent = NULL);   // standard constructor
	int m_permission;
// Dialog Data
	//{{AFX_DATA(Dialog_Menu_Post)
	enum { IDD = IDD_DIALOG_MENU_POST };
	CComboBox	m_department;
	CString	m_listid;
	CString	m_postnumber;
	CString	m_volume;
	int		m_indexdepartment;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_Menu_Post)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_Menu_Post)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeComboDepartment();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_MENU_POST_H__E215E308_940B_46E6_934F_23F76B2F7122__INCLUDED_)
