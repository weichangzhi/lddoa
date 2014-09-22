// GoodsManageSystemDlg.h : header file
//

#if !defined(AFX_GOODSMANAGESYSTEMDLG_H__A19BCE02_407D_4B17_84B1_7B0103988BEC__INCLUDED_)
#define AFX_GOODSMANAGESYSTEMDLG_H__A19BCE02_407D_4B17_84B1_7B0103988BEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "SelTab.h"
#include "DIALOG_CLIENT.h"
#include "Dialog_BaseInfo.h"
#include "Dialog_post.h"
#include "Dialog_Schdeule.h"
#include "Dialog_Detail.h"
#include "Dialog_Output.h"
#include "Dialog_AddUser.h"
#include "Dialog_Delete_User.h"
#include "Dialog_ModifyPW_Admin.h"
#include "Dialog_Modify_Permission.h"
#include "Dialog_New_List.h"
#include "Dialog_ModifyList.h"
#include "Dialog_Making.h"
#include "Dialog_Unpost.h"
#include "Dialog_ChangeRecord.h"
#include "Dialog_FI.h"
#include "XPButton.h"
#include "Dialog_UndoRecord.h"
#include "Dialog_FI_Query.h"

/////////////////////////////////////////////////////////////////////////////
// CGoodsManageSystemDlg dialog

#define MAX_TREE_PAGE 24
class CGoodsManageSystemDlg : public CDialog
{
// Construction
public:
	CGoodsManageSystemDlg(CWnd* pParent = NULL);	// standard constructor
	CImageList m_imagelist;
	CDialog * m_treePages[MAX_TREE_PAGE];
	CString node_name;
	HTREEITEM m_itemNewList;
	BOOL InitMytree();
	BOOL bFirstin;
	int icurrentpage;
	CString timertime;
	int m_hour;
	int m_min;
// Dialog Data
	//{{AFX_DATA(CGoodsManageSystemDlg)
	enum { IDD = IDD_GOODSMANAGESYSTEM_DIALOG };
	CTreeCtrl	m_tree;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGoodsManageSystemDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGoodsManageSystemDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHelp();
	afx_msg void OnClientAdd();
	afx_msg void OnClientQuery();
	afx_msg void OnSellAdd();
	afx_msg void OnSellQuery();
	afx_msg void OnBuyAdd();
	afx_msg void OnBuyQuery();
	afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuitemTips();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOODSMANAGESYSTEMDLG_H__A19BCE02_407D_4B17_84B1_7B0103988BEC__INCLUDED_)
