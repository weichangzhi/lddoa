#if !defined(AFX_DIALOG_UNDORECORD_H__1F52999B_455D_40CE_8B5A_598F840BB57A__INCLUDED_)
#define AFX_DIALOG_UNDORECORD_H__1F52999B_455D_40CE_8B5A_598F840BB57A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_UndoRecord.h : header file
//
#include "LineColorListCtrl.h"
#include "XPButton.h"
/////////////////////////////////////////////////////////////////////////////
// Dialog_UndoRecord dialog

class Dialog_UndoRecord : public CDialog
{
// Construction
public:
	Dialog_UndoRecord(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dialog_UndoRecord)
	enum { IDD = IDD_DIALOG_UNDO_RECORD };
	CLineColorListCtrl	m_listUndoRecord;
	CXPButton	m_btexcel;
	CXPButton	m_btselect;
	CTime	m_timestart;
	CTime	m_timeend;
	CString	m_strListid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_UndoRecord)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_UndoRecord)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSelect();
	afx_msg void OnButtonExcel();
	afx_msg void OnColumnclickListChangerecord(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_UNDORECORD_H__1F52999B_455D_40CE_8B5A_598F840BB57A__INCLUDED_)
