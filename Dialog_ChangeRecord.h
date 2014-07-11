#if !defined(AFX_DIALOG_CHANGERECORD_H__98C7A39B_67E9_40C7_B8DE_4189719DF6BC__INCLUDED_)
#define AFX_DIALOG_CHANGERECORD_H__98C7A39B_67E9_40C7_B8DE_4189719DF6BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_ChangeRecord.h : header file
//
#include "LineColorListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// Dialog_ChangeRecord dialog

class Dialog_ChangeRecord : public CDialog
{
// Construction
public:
	Dialog_ChangeRecord(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dialog_ChangeRecord)
	enum { IDD = IDD_DIALOG_CHAGNE_RECORD };
	CLineColorListCtrl	m_listChangeRecord;
	CString	m_strListID;
	CTime	m_timeStart;
	CTime	m_timeEnd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_ChangeRecord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_ChangeRecord)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSelect();
	afx_msg void OnButtonExcel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_CHANGERECORD_H__98C7A39B_67E9_40C7_B8DE_4189719DF6BC__INCLUDED_)
