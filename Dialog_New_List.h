#if !defined(AFX_DIALOG_NEW_LIST_H__9B9EC593_8F8E_4443_A932_AA9129926F02__INCLUDED_)
#define AFX_DIALOG_NEW_LIST_H__9B9EC593_8F8E_4443_A932_AA9129926F02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_New_List.h : header file
//
#include "XPButton.h"
#include "Preview.h"
/////////////////////////////////////////////////////////////////////////////
// CDialog_New_List dialog

class CDialog_New_List : public CDialog
{
// Construction
public:
	CDialog_New_List(CWnd* pParent = NULL);   // standard constructor
	void SetPreviewDlg(CPreview *PreviewDlg);
	void updatedlg();
	CString m_str_reveive_time;
	CString m_str_end_date;

	int m_nCurHeight;
	int m_nScrollPos;
	int m_nCurWidth;
	int m_nHScrollPos;
	CRect m_rect;
// Dialog Data
	//{{AFX_DATA(CDialog_New_List)
	enum { IDD = IDD_DIALOG_NEW_LIST };
	CComboBox	m_ComDepTC;
	CComboBox	m_ComClass;
	CDateTimeCtrl	m_ctrlEndDate;
	CDateTimeCtrl	m_ctrlReveiveDate;
	CXPButton	m_btexcel;
	CXPButton	m_btprint;
	CXPButton	m_btpreview;
	CXPButton	m_btnok;
	CXPButton	m_btncancel;
	CXPButton	m_btnsubmitlist;
	CXPButton	m_btnstartlist;
	CXPButton	m_btnendlist;
	CComboBox	m_ComSize;
	CComboBox	m_ComShine;
	CComboBox	m_ComPaint1;
	CComboBox	m_ComMaterial;
	CComboBox	m_ComDepartment;
	CComboBox	m_ComColor;
	CComboBox	m_ComBottom;
	CComboBox	m_ComBill;
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
	BOOL	m_urgent;
	CString	m_strClass;
	CString	m_strDepTC;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_New_List)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_New_List)
	afx_msg void OnEndList();
	afx_msg void OnStartList();
	afx_msg void OnSubmitlist();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeComboDepartment();
	afx_msg void OnButtonPreview();
	afx_msg void OnButtonPrint();
	afx_msg void OnButtonExcel();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_NEW_LIST_H__9B9EC593_8F8E_4443_A932_AA9129926F02__INCLUDED_)
