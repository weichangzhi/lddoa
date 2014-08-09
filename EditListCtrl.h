/********************************************/
/* EditListCtrl.h                            */
/* �ɱ༭ListCtrl                            */
/********************************************/
#pragma once
#include "afxwin.h"
// �������Զ���༭������Ϣ
#define WM_USER_EDIT_END WM_USER + 1001
#define WM_USER_EDIT_DBCLK WM_USER + 1002
class CListCtrlEdit : public CRichEditCtrl
{
    // ������������̬����ʱCRuntimeClass
    DECLARE_DYNAMIC(CListCtrlEdit)
    // ������ 2012-11-16 ��
public:
    DECLARE_MESSAGE_MAP()
    // �����󣺿ؼ�����Ϣ���壬��Ҫ��CWndΪ����
    afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    // ������ 2012-11-16 ��
public:
    CListCtrlEdit(void);
    ~CListCtrlEdit(void);
};


#include <afxtempl.h>
#include "afxcmn.h"
// �����󣺶���һ��ID
#define IDC_EDIT 1001
class CEditListCtrl :public CListCtrl
{
    // ������������̬����ʱCRuntimeClass
    DECLARE_DYNAMIC(CEditListCtrl)
    // ������ 2012-11-16 ��
public:
    int nItem;                // ��
    int nSubItem;            // ��
    CListCtrlEdit m_Edit;
    void ShowEdit(bool bShow, int nItem, int nSubItem, CRect rcCtrl);
	CMap<DWORD, DWORD&, TEXT_BK, TEXT_BK&> MapItemColor;
	void SetItemColor(DWORD iItem, COLORREF TextColor, COLORREF TextBkColor);	//����ĳһ�е�ǰ��ɫ�ͱ���ɫ
	void SetAllItemColor(DWORD iItem, COLORREF TextColor, COLORREF TextBkColor);//����ȫ���е�ǰ��ɫ�ͱ���ɫ
	void ClearColor();			
public:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg LRESULT OnEditEnd(WPARAM wParam,LPARAM lParam = FALSE);
	afx_msg void OnEditDbClk(UINT nFlags, CPoint point);
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
    // ������ 2012-11-16 ��
public:
    CEditListCtrl(void);
    ~CEditListCtrl(void);
};