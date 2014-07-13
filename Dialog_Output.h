#if !defined(AFX_DIALOG_OUTPUT_H__2E21B077_521B_489B_9C69_1EC2B178D962__INCLUDED_)
#define AFX_DIALOG_OUTPUT_H__2E21B077_521B_489B_9C69_1EC2B178D962__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_Output.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog_Output dialog

#include "LineColorListCtrl.h"
class CDialog_Output : public CDialog
{
// Construction
public:
	CDialog_Output(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_Output)
	enum { IDD = IDD_DIALOG_OUTPUT1 };
	CEdit	m_EditName;
	CComboBox	m_ComWay;
	CLineColorListCtrl	m_list_output;
	CComboBox	m_com_output;
	CTime	m_time_start;
	CTime	m_time_end;
	CString	m_strName;
	CString	m_strDepartment;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_Output)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_Output)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnExcel();
	afx_msg void OnSelchangeComboWay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_OUTPUT_H__2E21B077_521B_489B_9C69_1EC2B178D962__INCLUDED_)
