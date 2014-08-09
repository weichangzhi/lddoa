#if !defined(AFX_DIALOG_STORAGE_OUT_DETAIL_H__82C7FA47_2069_4473_8608_DA28F6380BD1__INCLUDED_)
#define AFX_DIALOG_STORAGE_OUT_DETAIL_H__82C7FA47_2069_4473_8608_DA28F6380BD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Storage_Out_Detail.h : header file
//
#include "LineColorListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_Out_Detail dialog

class Dialog_Storage_Out_Detail : public CDialog
{
// Construction
public:
	Dialog_Storage_Out_Detail(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dialog_Storage_Out_Detail)
	enum { IDD = IDD_DIALOG_STORAGE_OUT_DETAIL };
	CListCtrl	m_listTotal;
	CLineColorListCtrl	m_listStorageInDetail;
	CXPButton	m_btok;
	CXPButton	m_btexcel;
	CTime	m_timebegin;
	CTime	m_timeend;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_Storage_Out_Detail)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_Storage_Out_Detail)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonExcel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_STORAGE_OUT_DETAIL_H__82C7FA47_2069_4473_8608_DA28F6380BD1__INCLUDED_)
