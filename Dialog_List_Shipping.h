#if !defined(AFX_DIALOG_LIST_SHIPPING_H__36DB6397_F74F_4A1F_B26C_9EC53AA8812C__INCLUDED_)
#define AFX_DIALOG_LIST_SHIPPING_H__36DB6397_F74F_4A1F_B26C_9EC53AA8812C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_List_Shipping.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dialog_List_Shipping dialog

class Dialog_List_Shipping : public CDialog
{
// Construction
public:
	Dialog_List_Shipping(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dialog_List_Shipping)
	enum { IDD = IDD_DIALOG_LIST_SHIPPING };
	CButton	m_btSelectAll;
	CLineColorListCtrl	m_listBaseInfo;
	CXPButton	m_btQuery1;
	CComboBox	m_ComSubway;
	CComboBox	m_ComStore;
	CComboBox	m_ComBaseinfo;
	CXPButton	m_btPrint;
	CXPButton	m_btExcel;
	CString	m_strStore;
	CString	m_strSubWay;
	CTime	m_timeBegin;
	CTime	m_timeEnd;
	BOOL	m_bSelectAll;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_List_Shipping)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_List_Shipping)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonExcel();
	afx_msg void OnButtonPrint();
	afx_msg void OnButtonQuery();
	afx_msg void OnColumnclickListBaseinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboBaseinfo();
	afx_msg void OnCheckSelectall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_LIST_SHIPPING_H__36DB6397_F74F_4A1F_B26C_9EC53AA8812C__INCLUDED_)
