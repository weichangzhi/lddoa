#if !defined(AFX_DIALOG_PROGRESS_H__7A363D45_BA98_4B4D_80CB_2F285BD53811__INCLUDED_)
#define AFX_DIALOG_PROGRESS_H__7A363D45_BA98_4B4D_80CB_2F285BD53811__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_progress.h : header file
//
#include "GradientProgressCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// Dialog_progress dialog

class Dialog_progress : public CDialog
{
// Construction
public:
	Dialog_progress(CWnd* pParent = NULL);   // standard constructor
	void setpos(int i);
	void endpos();
	UINT	m_nRange;
// Dialog Data
	//{{AFX_DATA(Dialog_progress)
	enum { IDD = IDD_DIALOG_PROGRESS };
	CGradientProgressCtrl	m_cProgress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_progress)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	COLORREF m_clrText, m_clrBk, m_clrStart, m_clrEnd;
	// Generated message map functions
	//{{AFX_MSG(Dialog_progress)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_PROGRESS_H__7A363D45_BA98_4B4D_80CB_2F285BD53811__INCLUDED_)
