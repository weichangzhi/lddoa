#if !defined(AFX_DIALOG_BASEINFO_H__FA0C192D_0DBC_4D54_B51E_0242FE2503DD__INCLUDED_)
#define AFX_DIALOG_BASEINFO_H__FA0C192D_0DBC_4D54_B51E_0242FE2503DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_BaseInfo.h : header file
//

#include "LineColorListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CDialog_BaseInfo dialog

class CDialog_BaseInfo : public CDialog
{
// Construction
public:
	CDialog_BaseInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_BaseInfo)
	enum { IDD = IDD_DIALOG_BASEINFO };
	CLineColorListCtrl	m_list_baseinfo;
	CComboBox	m_com_baseinfo;
	CTime	m_time_bgein;
	CTime	m_time_end;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_BaseInfo)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_BaseInfo)
	afx_msg void OnButtonSellSelect();
	virtual BOOL OnInitDialog();
	afx_msg void OnExcel();
	afx_msg void OnSelchangeComboBaseinfo();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_BASEINFO_H__FA0C192D_0DBC_4D54_B51E_0242FE2503DD__INCLUDED_)
