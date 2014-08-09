/***********************************************/
/* EditListCtrl.cpp                            */
/***********************************************/
#include "StdAfx.h"
#include "EditListCtrl.h"


// 大气象：确定运行时对象
IMPLEMENT_DYNAMIC(CListCtrlEdit,CRichEditCtrl)

// 大气象 2012-11-16 ↓
BEGIN_MESSAGE_MAP(CListCtrlEdit, CRichEditCtrl)
    ON_WM_KILLFOCUS()// 大气象：与对话框中控件消息映射定义不同。
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()
void CListCtrlEdit::OnKillFocus(CWnd* pNewWnd)
{
    CRichEditCtrl::OnKillFocus(pNewWnd);
    // 大气象：向父窗口发消息
    CWnd* pParent = this->GetParent();
    ::PostMessage(pParent->GetSafeHwnd(),WM_USER_EDIT_END,0,0);
}

void CListCtrlEdit::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    CRichEditCtrl::OnLButtonDblClk(nFlags, point);
    // 大气象：向父窗口发消息
    CWnd* pParent = this->GetParent();
    ::PostMessage(pParent->GetSafeHwnd(),WM_USER_EDIT_DBCLK,0,0);
}

// 大气象 2012-11-16 ↑
CListCtrlEdit::CListCtrlEdit(void)
{
}
CListCtrlEdit::~CListCtrlEdit(void)
{
}



// 大气象：确定运行时对象
IMPLEMENT_DYNAMIC(CEditListCtrl,CListCtrl)

// 大气象 2012-11-16 ↓
BEGIN_MESSAGE_MAP(CEditListCtrl, CListCtrl)
    ON_WM_LBUTTONDBLCLK() // 可以切换到类视图，右击属性生成。
    ON_MESSAGE(WM_USER_EDIT_END,CEditListCtrl::OnEditEnd)
	ON_MESSAGE(WM_USER_EDIT_DBCLK,CEditListCtrl::OnEditDbClk)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnNMCustomdraw)
END_MESSAGE_MAP()

void CEditListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // 大气象：取得行列信息的固定方法
    LVHITTESTINFO lvhti;    // 大气象：保存ListCtrl行列信息的结构
    lvhti.pt = point;
    nItem = CListCtrl::SubItemHitTest(&lvhti);
    if (nItem == -1) return;
    nSubItem = lvhti.iSubItem;

    CRect rect;
    CListCtrl::GetSubItemRect(nItem,nSubItem,LVIR_LABEL,rect);

    ShowEdit(TRUE,nItem,nSubItem,rect);

    CListCtrl::OnLButtonDblClk(nFlags, point);
}
void CEditListCtrl::ShowEdit(bool bShow, int nItem, int nSubItem, CRect rcCtrl)
{
    if (m_Edit.m_hWnd == NULL)
    {
        m_Edit.Create(ES_AUTOHSCROLL|WS_CHILD|ES_LEFT|ES_WANTRETURN|WS_BORDER,CRect(0,0,0,0),this,IDC_EDIT);
        m_Edit.ShowWindow(SW_HIDE);

        CFont tpFont;
        tpFont.CreateStockObject(DEFAULT_GUI_FONT);
        m_Edit.SetFont(&tpFont);
        tpFont.DeleteObject();
    }
    if (bShow == TRUE)
    {
        CString strItem = CListCtrl::GetItemText(nItem,nSubItem);
        rcCtrl.top -= 2;    // 大气象：防止上边框被遮挡
        m_Edit.MoveWindow(&rcCtrl);
        m_Edit.ShowWindow(SW_SHOW);
        m_Edit.SetWindowText(strItem);
        m_Edit.SetFocus();
        m_Edit.SetSel(-1,-1); 
    }
    else
        m_Edit.ShowWindow(SW_HIDE);
}
LRESULT CEditListCtrl::OnEditEnd(WPARAM wParam,LPARAM lParam)
{
    CString strText;
    m_Edit.GetWindowText(strText);
    CListCtrl::SetItemText(nItem,nSubItem,strText);
    m_Edit.ShowWindow(SW_HIDE);
	
    return 0;
}

void CEditListCtrl::OnEditDbClk(UINT nFlags, CPoint point)
{
    CString strText;
    m_Edit.GetWindowText(strText);
	MessageBox("可以添加内容","提示",MB_OK);
    //CListCtrl::SetItemText(nItem,nSubItem,strText);
    //m_Edit.ShowWindow(SW_HIDE);
}

void CEditListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)  
{  
    // TODO: Add your control notification handler code here   
    *pResult = CDRF_DODEFAULT;  
    NMLVCUSTOMDRAW * lplvdr=(NMLVCUSTOMDRAW*)pNMHDR;  
    NMCUSTOMDRAW &nmcd = lplvdr->nmcd;  
    switch(lplvdr->nmcd.dwDrawStage)//判断状态   
    {  
	case CDDS_PREPAINT:  
        {  
            *pResult = CDRF_NOTIFYITEMDRAW;  
            break;  
        }  
	case CDDS_ITEMPREPAINT://如果为画ITEM之前就要进行颜色的改变   
        {  
			TEXT_BK tb;

            if(MapItemColor.Lookup(nmcd.dwItemSpec, tb))  
				// 根据在 SetItemColor(DWORD iItem, COLORREF color) 设置的   
				// ITEM号和COLORREF 在摸板中查找，然后进行颜色赋值。   
            {  
                lplvdr->clrText = tb.colText;   
                lplvdr->clrTextBk = tb.colTextBk;  
                *pResult = CDRF_DODEFAULT;  
            }  
        }  
        break;  
    }  
}  

void CEditListCtrl::ClearColor()
{
	MapItemColor.RemoveAll();
}

void CEditListCtrl::SetItemColor(DWORD iItem, COLORREF TextColor, COLORREF TextBkColor)
{  
	TEXT_BK tb;
	tb.colText = TextColor;
	tb.colTextBk = TextBkColor;


    MapItemColor.SetAt(iItem, tb);//设置某行的颜色。   
    this->RedrawItems(iItem, iItem);//重新染色   
	
    //this->SetCheck(iItem,1);   
    this->SetFocus();    //设置焦点   
    UpdateWindow();  
}  


void CEditListCtrl::SetAllItemColor(DWORD iItem, COLORREF TextColor, COLORREF TextBkColor)  
{  
    //INT_PTR ncount = this->GetItemCount();
	TEXT_BK tb;
	tb.colText = TextColor;
	tb.colTextBk = TextBkColor;

    if(iItem > 0)  
    {  
        for(DWORD numItem = 0; numItem < iItem ;numItem ++)  
        {  
            //iItem = i;   
            MapItemColor.SetAt(numItem, tb);  
            this->RedrawItems(numItem, numItem);  
        }  
    }  
	
    return;  
	
}  


// 大气象 2012-11-16 ↑
CEditListCtrl::CEditListCtrl(void)
{
}
CEditListCtrl::~CEditListCtrl(void)
{
}
