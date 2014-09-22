#if !defined(AFX_DIALOG_SENDUSER_H__BE067666_C7E2_4424_B50A_045A7E869D28__INCLUDED_)
#define AFX_DIALOG_SENDUSER_H__BE067666_C7E2_4424_B50A_045A7E869D28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_SendUser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dialog_SendUser dialog

class Dialog_SendUser : public CDialog
{
// Construction
public:
	Dialog_SendUser(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dialog_SendUser)
	enum { IDD = IDD_DIALOG_SEND_USER };
	CLineColorListCtrl	m_listSendUser;
	CXPButton	m_btExcel;
	CXPButton	m_btAdd;
	CXPButton	m_btQuery;
	CXPButton	m_btdeleteuser;
	CXPButton	m_btmodify;
	CString	m_strUserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_SendUser)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_SendUser)
	virtual BOOL OnInitDialog();
	afx_msg void OnRclickListClient(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickListClient(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonClientQuery();
	afx_msg void OnButtonClientAdd();
	afx_msg void OnButtonDeleteUser();
	afx_msg void OnButtonModify();
	afx_msg void OnExcel();
	afx_msg void OnDel();
	afx_msg void OnModify();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_SENDUSER_H__BE067666_C7E2_4424_B50A_045A7E869D28__INCLUDED_)
