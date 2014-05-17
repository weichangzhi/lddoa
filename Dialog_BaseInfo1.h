#if !defined(AFX_DIALOG_BASEINFO1_H__66AC3AE3_400D_481D_BB7B_F84A2E8D7346__INCLUDED_)
#define AFX_DIALOG_BASEINFO1_H__66AC3AE3_400D_481D_BB7B_F84A2E8D7346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_BaseInfo1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog_BaseInfo1 dialog

class CDialog_BaseInfo1 : public CDialog
{
// Construction
public:
	CDialog_BaseInfo1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_BaseInfo1)
	enum { IDD = IDD_DIALOG_BASEINFO1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_BaseInfo1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_BaseInfo1)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_BASEINFO1_H__66AC3AE3_400D_481D_BB7B_F84A2E8D7346__INCLUDED_)
