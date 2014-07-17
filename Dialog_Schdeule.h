#if !defined(AFX_DIALOG_SCHDEULE_H__59039ECD_6688_4678_AE7A_48569FA746AA__INCLUDED_)
#define AFX_DIALOG_SCHDEULE_H__59039ECD_6688_4678_AE7A_48569FA746AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Schdeule.h : header file
//
#include "XPButton.h"
/////////////////////////////////////////////////////////////////////////////
// CDialog_Schdeule dialog

#include "LineColorListCtrl.h"
class CDialog_Schdeule : public CDialog
{
// Construction
public:
	CDialog_Schdeule(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_Schdeule)
	enum { IDD = IDD_DIALOG_SCHEDULE };
	CXPButton	m_btnexcel;
	CXPButton	m_btnquery;
	CComboBox	m_com_schdeule2;
	CLineColorListCtrl	m_list_schedule;
	CComboBox	m_com_schdeule;
	CTime	m_timebegin;
	CTime	m_timeend;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Schdeule)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_Schdeule)
	virtual BOOL OnInitDialog();
	afx_msg void OnSchdeuleSelect();
	afx_msg void OnSelchangeComboSchedule();
	afx_msg void OnExcel();
	afx_msg void OnColumnclickListSchdeule(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_SCHDEULE_H__59039ECD_6688_4678_AE7A_48569FA746AA__INCLUDED_)
