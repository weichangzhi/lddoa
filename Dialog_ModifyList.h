#if !defined(AFX_DIALOG_MODIFYLIST_H__D10BD023_199A_4D68_BED2_39677A9C71A5__INCLUDED_)
#define AFX_DIALOG_MODIFYLIST_H__D10BD023_199A_4D68_BED2_39677A9C71A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_ModifyList.h : header file
//
#include "XPButton.h"
#include "Preview.h"
/////////////////////////////////////////////////////////////////////////////
// CDialog_ModifyList dialog

class CDialog_ModifyList : public CDialog
{
// Construction
public:
	CDialog_ModifyList(CWnd* pParent = NULL);   // standard constructor
	void SetPreviewDlg(CPreview *PreviewDlg);
	void updatedlg();
	CString m_str_reveive_time;
	CString m_str_end_date;

	BOOL	m_design_server1;
	BOOL	m_has_modeling1;
	BOOL	m_modeling1;
	BOOL	m_modeling_pring1;
	BOOL	m_no_modeling1;
	BOOL	m_scan1;
	BOOL	m_urgent1;
	CString m_str_reveive_time1;
	CString m_str_end_date1;
	CString	m_address1;
	CString	m_bill1;
	CString	m_bottom1;
	CString	m_color1;
	CString	m_department1;
	CString	m_error_range1;
	CString	m_listname1;
	CString	m_material1;
	CString	m_money1;
	CString	m_print1;
	CString	m_people1;
	CString	m_phone1;
	CString	m_receivename1;
	CString	m_shine1;
	CString	m_size1;
	int		m_totel_number1;
	CString	m_usage1;
	CString	m_volume1;
	CString	m_other1;
	
	int m_nCurHeight;
	int m_nScrollPos;
	int m_nCurWidth;
	int m_nHScrollPos;
	CRect m_rect;
// Dialog Data
	//{{AFX_DATA(CDialog_ModifyList)
	enum { IDD = IDD_DIALOG_MODIFY_LIST1 };
	CXPButton	m_btexcel;
	CXPButton	m_btprint;
	CXPButton	m_btpreview;
	CXPButton	m_bt_undo;
	CXPButton	m_btcontinue;
	CXPButton	m_btnok;
	CXPButton	m_btncancel;
	CXPButton	m_btn1;
	CXPButton	m_btnstartlist;
	CXPButton	m_btnmodifylist;
	CXPButton	m_btnendlist;
	CComboBox	m_ComShine;
	CComboBox	m_ComColor;
	CComboBox	m_ComSize;
	CComboBox	m_ComPaint;
	CComboBox	m_ComMaterial;
	CComboBox	m_ComDepartment;
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
	CString	m_query_listid;
	BOOL	m_urgent;
	CTime	m_timestart2;
	CTime	m_timeEnd2;
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
	afx_msg void OnButtonUndoList();
	afx_msg void OnButtonContinueList();
	afx_msg void OnButtonPreview();
	afx_msg void OnButtonPrint();
	afx_msg void OnButtonExcel();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_MODIFYLIST_H__D10BD023_199A_4D68_BED2_39677A9C71A5__INCLUDED_)
