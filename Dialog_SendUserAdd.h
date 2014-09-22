#if !defined(AFX_DIALOG_SENDUSERADD_H__E7F0496E_FCED_4CED_B2C2_7CD7943878E5__INCLUDED_)
#define AFX_DIALOG_SENDUSERADD_H__E7F0496E_FCED_4CED_B2C2_7CD7943878E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_SendUserAdd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dialog_SendUserAdd dialog

class Dialog_SendUserAdd : public CDialog
{
// Construction
public:
	Dialog_SendUserAdd(CWnd* pParent = NULL);   // standard constructor
	int action;
// Dialog Data
	//{{AFX_DATA(Dialog_SendUserAdd)
	enum { IDD = IDD_DIALOG_SEND_USER_ADD };
	CXPButton	m_btOK;
	CXPButton	m_xpCancel;
	CString	m_strUserName;
	CString	m_strPhone;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_SendUserAdd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_SendUserAdd)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_SENDUSERADD_H__E7F0496E_FCED_4CED_B2C2_7CD7943878E5__INCLUDED_)
