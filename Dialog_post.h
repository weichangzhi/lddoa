#if !defined(AFX_DIALOG_POST_H__5BAA7C3E_36C7_45BE_B03D_204CE6878EB2__INCLUDED_)
#define AFX_DIALOG_POST_H__5BAA7C3E_36C7_45BE_B03D_204CE6878EB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_post.h : header file
//
#include "XPButton.h"
/////////////////////////////////////////////////////////////////////////////
// CDialog_post dialog

class CDialog_post : public CDialog
{
// Construction
public:
	CDialog_post(CWnd* pParent = NULL);   // standard constructor
	int m_permission;

	int m_nCurHeight;
	int m_nScrollPos;
	int m_nCurWidth;
	int m_nHScrollPos;
	CRect m_rect;
// Dialog Data
	//{{AFX_DATA(CDialog_post)
	enum { IDD = IDD_DIALOG_POST };
	CXPButton	m_btn2;
	CXPButton	m_btnpost;
	CComboBox	m_department;
	CString	m_postid1;
	CString	m_postid2;
	CString	m_postid3;
	CString	m_postid4;
	CString	m_postid5;
	CString	m_postnumber1;
	CString	m_postnumber2;
	CString	m_postnumber3;
	CString	m_postnumber4;
	CString	m_postnumber5;
	CString	m_volume1;
	CString	m_volume2;
	CString	m_volume3;
	CString	m_volume4;
	CString	m_volume5;
	CString	m_designer1;
	CString	m_designer2;
	CString	m_designer3;
	CString	m_designer4;
	CString	m_designer5;
	CString	m_score1;
	CString	m_score2;
	CString	m_score3;
	CString	m_score4;
	CString	m_score5;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_post)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_post)
	afx_msg void OnPost();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeDepartment();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_POST_H__5BAA7C3E_36C7_45BE_B03D_204CE6878EB2__INCLUDED_)
