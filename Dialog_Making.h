#if !defined(AFX_DIALOG_MAKING_H__74202BFA_D62D_494E_B67E_2E28D2135539__INCLUDED_)
#define AFX_DIALOG_MAKING_H__74202BFA_D62D_494E_B67E_2E28D2135539__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Making.h : header file
//
#include "LineColorListCtrl.h"
#include "XPButton.h"
/////////////////////////////////////////////////////////////////////////////
// CDialog_Making dialog

class CDialog_Making : public CDialog
{
// Construction
public:
	CDialog_Making(CWnd* pParent = NULL);   // standard constructor
	void updatelist(int cursel);
// Dialog Data
	//{{AFX_DATA(CDialog_Making)
	enum { IDD = IDD_DIALOG_MAKEING };
	CXPButton	m_btnexcel;
	CXPButton	m_btnquery;
	CEdit	m_edit;
	CComboBox	m_ComDepartment;
	CLineColorListCtrl 	m_list_schedule;
	CTime	m_timebegin;
	CTime	m_timeend;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Making)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_Making)
	afx_msg void OnMakingQuery();
	afx_msg void OnCustomDraw(NMHDR *pnotify, LRESULT *result);
	virtual BOOL OnInitDialog();
	afx_msg void OnExcel();
	afx_msg void OnRclickListSchdeule(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuitemPostTC();
	afx_msg void OnMenuitemPostPd();
	afx_msg void OnMenuitemPostQc();
	afx_msg void OnMenuitemPostStorage();
	afx_msg void OnColumnclickListSchdeule(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListSchdeule(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEditList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_MAKING_H__74202BFA_D62D_494E_B67E_2E28D2135539__INCLUDED_)
