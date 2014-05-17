#if !defined(AFX_DIALOG_MODIFYLIST_H__D10BD023_199A_4D68_BED2_39677A9C71A5__INCLUDED_)
#define AFX_DIALOG_MODIFYLIST_H__D10BD023_199A_4D68_BED2_39677A9C71A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_ModifyList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog_ModifyList dialog

class CDialog_ModifyList : public CDialog
{
// Construction
public:
	CDialog_ModifyList(CWnd* pParent = NULL);   // standard constructor
	CString m_str_reveive_time;
	CString m_str_end_date;
// Dialog Data
	//{{AFX_DATA(CDialog_ModifyList)
	enum { IDD = IDD_DIALOG_MODIFY_LIST1 };
	BOOL	m_design_server;
	BOOL	m_has_modeling;
	BOOL	m_modeling;
	BOOL	m_modeling_pring;
	BOOL	m_no_modeling;
	BOOL	m_scan;
	CTime	m_enddate;
	CTime	m_receivedate;
	CString	m_address;
	CString	m_bill;
	CString	m_bottom;
	CString	m_color;
	CString	m_department;
	CString	m_error_range;
	CString	m_listid;
	CString	m_listname;
	CString	m_material;
	CString	m_money;
	CString	m_print;
	CString	m_people;
	CString	m_phone;
	CString	m_receivename;
	CString	m_shine;
	CString	m_size;
	int		m_totel_number;
	CString	m_usage;
	CString	m_volume;
	int		m_true_number;
	CString	m_other;
	CString	m_query_listid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_ModifyList)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_ModifyList)
	virtual BOOL OnInitDialog();
	afx_msg void OnQueryList();
	afx_msg void OnModifylist();
	afx_msg void OnStartList();
	afx_msg void OnEndList();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_MODIFYLIST_H__D10BD023_199A_4D68_BED2_39677A9C71A5__INCLUDED_)
