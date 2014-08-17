#if !defined(AFX_DIALOG_STORAGE_IN_DETAIL_H__F8136EE0_7273_49F4_9E76_8C9F263C39AF__INCLUDED_)
#define AFX_DIALOG_STORAGE_IN_DETAIL_H__F8136EE0_7273_49F4_9E76_8C9F263C39AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Storage_In_Detail.h : header file
//
#include "LineColorListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_In_Detail dialog

class Dialog_Storage_In_Detail : public CDialog
{
// Construction
public:
	Dialog_Storage_In_Detail(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dialog_Storage_In_Detail)
	enum { IDD = IDD_DIALOG_STORAGE_IN_DETAIL };
	CComboBox	m_comSubWay;
	CComboBox	m_comWay;
	CListCtrl	m_listTotal;
	CLineColorListCtrl	m_listStorageInDetail;
	CXPButton	m_btok;
	CXPButton	m_btexcel;
	CTime	m_timebegin;
	CTime	m_timeend;
	CString	m_strWay;
	CString	m_strSubWay;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_Storage_In_Detail)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_Storage_In_Detail)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonExcel();
	afx_msg void OnSelchangeComboWay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_STORAGE_IN_DETAIL_H__F8136EE0_7273_49F4_9E76_8C9F263C39AF__INCLUDED_)
