#if !defined(AFX_DIALOG_STORAGE_LEFT_H__0EA37499_DB40_40E8_81E3_EAE8850CB5B8__INCLUDED_)
#define AFX_DIALOG_STORAGE_LEFT_H__0EA37499_DB40_40E8_81E3_EAE8850CB5B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Storage_Left.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_Left dialog

class Dialog_Storage_Left : public CDialog
{
// Construction
public:
	Dialog_Storage_Left(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dialog_Storage_Left)
	enum { IDD = IDD_DIALOG_STORAGE_LEFT };
	CListCtrl	m_listTotal;
	CXPButton	m_btok;
	CLineColorListCtrl	m_list_StorageLeft;
	CXPButton	m_btexcel;
	CTime	m_time;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_Storage_Left)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_Storage_Left)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonExcel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_STORAGE_LEFT_H__0EA37499_DB40_40E8_81E3_EAE8850CB5B8__INCLUDED_)
