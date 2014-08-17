#if !defined(AFX_DIALOG_STORAGE_ID_H__1B3FFAFA_4337_4897_86D1_74451926A2E1__INCLUDED_)
#define AFX_DIALOG_STORAGE_ID_H__1B3FFAFA_4337_4897_86D1_74451926A2E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Storage_ID.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_ID dialog

class Dialog_Storage_ID : public CDialog
{
// Construction
public:
	Dialog_Storage_ID(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dialog_Storage_ID)
	enum { IDD = IDD_DIALOG_STORAGE_ID };
	CXPButton	m_btok;
	CXPButton	m_btcancel;
	CString	m_StorageID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_Storage_ID)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_Storage_ID)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_STORAGE_ID_H__1B3FFAFA_4337_4897_86D1_74451926A2E1__INCLUDED_)
