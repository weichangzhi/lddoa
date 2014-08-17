#if !defined(AFX_DIALOG_STORAGE_NAME_H__85882EC8_1744_477E_B919_B82B4FC4649E__INCLUDED_)
#define AFX_DIALOG_STORAGE_NAME_H__85882EC8_1744_477E_B919_B82B4FC4649E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Storage_Name.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_Name dialog

class Dialog_Storage_Name : public CDialog
{
// Construction
public:
	Dialog_Storage_Name(CWnd* pParent = NULL);   // standard constructor
	CString storageid;
	CString storagename;
// Dialog Data
	//{{AFX_DATA(Dialog_Storage_Name)
	enum { IDD = IDD_DIALOG_STORAGE_NAME };
	CXPButton	m_btok;
	CXPButton	m_btcancel;
	CLineColorListCtrl	m_listStorage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_Storage_Name)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_Storage_Name)
	afx_msg void OnDblclkListStorageLeft(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_STORAGE_NAME_H__85882EC8_1744_477E_B919_B82B4FC4649E__INCLUDED_)
