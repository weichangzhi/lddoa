/********************************************/
/* EditListCtrl.h                            */
/* 可编辑ListCtrl                            */
/********************************************/
#pragma once
#include "afxwin.h"
// 大气象：自定义编辑结束消息
#define WM_USER_EDIT_END WM_USER + 1001
#define WM_USER_EDIT_DBCLK WM_USER + 1002
class CListCtrlEdit : public CRichEditCtrl
{
    // 大气象：声明动态运行时CRuntimeClass
    DECLARE_DYNAMIC(CListCtrlEdit)
    // 大气象 2012-11-16 ↓
public:
    DECLARE_MESSAGE_MAP()
    // 大气象：控件中消息定义，需要以CWnd为参数
    afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    // 大气象 2012-11-16 ↑
public:
    CListCtrlEdit(void);
    ~CListCtrlEdit(void);
};


#include <afxtempl.h>
#include "afxcmn.h"
// 大气象：定义一个ID
#define IDC_EDIT 1001
class CEditListCtrl :public CListCtrl
{
    // 大气象：声明动态运行时CRuntimeClass
    DECLARE_DYNAMIC(CEditListCtrl)
    // 大气象 2012-11-16 ↓
public:
    int nItem;                // 行
    int nSubItem;            // 列
    CListCtrlEdit m_Edit;
    void ShowEdit(bool bShow, int nItem, int nSubItem, CRect rcCtrl);
	CMap<DWORD, DWORD&, TEXT_BK, TEXT_BK&> MapItemColor;
	void SetItemColor(DWORD iItem, COLORREF TextColor, COLORREF TextBkColor);	//设置某一行的前景色和背景色
	void SetAllItemColor(DWORD iItem, COLORREF TextColor, COLORREF TextBkColor);//设置全部行的前景色和背景色
	void ClearColor();			
public:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg LRESULT OnEditEnd(WPARAM wParam,LPARAM lParam = FALSE);
	afx_msg void OnEditDbClk(UINT nFlags, CPoint point);
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
    // 大气象 2012-11-16 ↑
public:
    CEditListCtrl(void);
    ~CEditListCtrl(void);
};