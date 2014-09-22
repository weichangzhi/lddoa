#if !defined(AFX_DIALOG_LISTSHIPPINGPRINT_H__5D3EBEF5_41EF_4191_9EB2_20F9A384FB60__INCLUDED_)
#define AFX_DIALOG_LISTSHIPPINGPRINT_H__5D3EBEF5_41EF_4191_9EB2_20F9A384FB60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_ListShippingPrint.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dialog_ListShippingPrint dialog

class Dialog_ListShippingPrint : public CDialog
{
// Construction
public:
	Dialog_ListShippingPrint(CWnd* pParent = NULL);   // standard constructor
	void DrawReport(CRect rect, CDC *pDC, BOOL isprinted);
	int screenx;
	int screeny;
	CListCtrl *m_list;
// Dialog Data
	//{{AFX_DATA(Dialog_ListShippingPrint)
	enum { IDD = IDD_DIALOG_LIST_SHIPPING_PRINT };
	 
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog_ListShippingPrint)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog_ListShippingPrint)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_LISTSHIPPINGPRINT_H__5D3EBEF5_41EF_4191_9EB2_20F9A384FB60__INCLUDED_)
