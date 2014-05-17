#if !defined(AFX_DIALOG_INPUTBASEINFO_H__E136810C_9E45_4C68_8FB7_DFEF1BC368F1__INCLUDED_)
#define AFX_DIALOG_INPUTBASEINFO_H__E136810C_9E45_4C68_8FB7_DFEF1BC368F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog_InputBaseinfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialog_InputBaseinfo dialog

class CDialog_InputBaseinfo : public CDialog
{
// Construction
public:
	CDialog_InputBaseinfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog_InputBaseinfo)
	enum { IDD = IDD_DIALOG_INPUT_BASEINFO };
	CString	m_ListID;
	CString	m_ClientName;
	CString	m_Phone;
	CString	m_department;
	CString	m_adress;
	CString	m_Mondy;
	CTime	m_reveivedate;
	CTime	m_enddate;
	CString	m_size;
	CString	m_material;
	CString	m_color;
	CString	m_paint;
	CString	m_bottom;
	CString	m_accuracy;
	CString	m_errorrange;
	CString	m_other;
	CString	m_totelnumber;
	CString m_str_reveive_time;
	CString m_str_end_date;
	BOOL m_bModify;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog_InputBaseinfo)
	public:
	virtual int DoModal();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog_InputBaseinfo)
	virtual BOOL OnInitDialog();
	afx_msg void OnSubmitlist();
	virtual void OnCancel();
	afx_msg void OnStartList();
	afx_msg void OnEndList();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_INPUTBASEINFO_H__E136810C_9E45_4C68_8FB7_DFEF1BC368F1__INCLUDED_)
