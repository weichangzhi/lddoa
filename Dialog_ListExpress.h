#if !defined(AFX_DIALOG_LISTEXPRESS_H__BBAF9C0C_E8DC_4544_A906_B93684C6BFFC__INCLUDED_)
#define AFX_DIALOG_LISTEXPRESS_H__BBAF9C0C_E8DC_4544_A906_B93684C6BFFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_ListExpress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dialog_ListExpress dialog

class Dialog_ListExpress : public CDialog
{
// Construction
public:
	Dialog_ListExpress(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dialog_ListExpress)
	enum { IDD = IDD_DIALOG_LIST_EXPRESS };
	CXPButton	m_btdelete;
	CLineColorListCtrl	m_listBaseInfo;
	CComboBox	m_comSubWay;
	CComboBox	m_comBaseInfo;
	CButton	m_btSelectAll;
	CXPButton	m_btquery;
	CXPButton	m_btprint;
	CXPButton	m_btexcel;
	BOOL	m_bSelectAll;
	int		m_bBaseInfo;
	CString	m_strSubWay;
	CTime	m_timeBegin;
	CTime	m_timeEnd;
	CString	m_strListNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_ListExpress)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_ListExpress)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonExcel();
	afx_msg void OnButtonPrint();
	afx_msg void OnButtonAdd();
	afx_msg void OnCheckSelectall();
	afx_msg void OnColumnclickListBaseinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboBaseinfo();
	afx_msg void OnButtonDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_LISTEXPRESS_H__BBAF9C0C_E8DC_4544_A906_B93684C6BFFC__INCLUDED_)
