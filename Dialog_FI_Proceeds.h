#if !defined(AFX_DIALOG_FI_PROCEEDS_H__CB213FC5_2C77_4142_B5D0_A5476D550FBC__INCLUDED_)
#define AFX_DIALOG_FI_PROCEEDS_H__CB213FC5_2C77_4142_B5D0_A5476D550FBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_FI_Proceeds.h : header file
//
#include "XPButton.h"
/////////////////////////////////////////////////////////////////////////////
// Dialog_FI_Proceeds dialog

class Dialog_FI_Proceeds : public CDialog
{
// Construction
public:
	Dialog_FI_Proceeds(CWnd* pParent = NULL);   // standard constructor
	void OnProceedsInput();
// Dialog Data
	//{{AFX_DATA(Dialog_FI_Proceeds)
	enum { IDD = IDD_DIALOG_FI_PROCEEDS };
	CXPButton	m_output;
	CXPButton	m_input;
	CComboBox	m_comProceedsWay;
	CComboBox	m_comBillWay;
	CXPButton	m_btcancel;
	CXPButton	m_btok;
	CXPButton	m_btquery;
	CTime	m_timeProceeds;
	CString	m_bill_id;
	CString	m_bill_way;
	CString	m_comment;
	CString	m_listid;
	CString	m_money_bill;
	CString	m_money_proceeds;
	CString	m_money_totel;
	CString	m_people_business;
	CString	m_people_fi;
	CString	m_proceeds_way;
	CString	m_query_listid;
	CTime	m_timeBill;
	CString	m_comment_Bill;
	CString	m_people_bill;
	CString	m_listName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_FI_Proceeds)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_FI_Proceeds)
	afx_msg void OnProceeds();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonInput();
	afx_msg void OnButtonOutput();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_FI_PROCEEDS_H__CB213FC5_2C77_4142_B5D0_A5476D550FBC__INCLUDED_)
