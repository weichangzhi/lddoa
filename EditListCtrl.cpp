/***********************************************/
/* EditListCtrl.cpp                            */
/***********************************************/
#include "StdAfx.h"
#include "EditListCtrl.h"


// ������ȷ������ʱ����
IMPLEMENT_DYNAMIC(CListCtrlEdit,CRichEditCtrl)

// ������ 2012-11-16 ��
BEGIN_MESSAGE_MAP(CListCtrlEdit, CRichEditCtrl)
    ON_WM_KILLFOCUS()// ��������Ի����пؼ���Ϣӳ�䶨�岻ͬ��
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()
void CListCtrlEdit::OnKillFocus(CWnd* pNewWnd)
{
    CRichEditCtrl::OnKillFocus(pNewWnd);
    // �������򸸴��ڷ���Ϣ
    CWnd* pParent = this->GetParent();
    ::PostMessage(pParent->GetSafeHwnd(),WM_USER_EDIT_END,0,0);
}

void CListCtrlEdit::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    CRichEditCtrl::OnLButtonDblClk(nFlags, point);
    // �������򸸴��ڷ���Ϣ
    CWnd* pParent = this->GetParent();
    ::PostMessage(pParent->GetSafeHwnd(),WM_USER_EDIT_DBCLK,0,0);
}

// ������ 2012-11-16 ��
CListCtrlEdit::CListCtrlEdit(void)
{
}
CListCtrlEdit::~CListCtrlEdit(void)
{
}



// ������ȷ������ʱ����
IMPLEMENT_DYNAMIC(CEditListCtrl,CListCtrl)

// ������ 2012-11-16 ��
BEGIN_MESSAGE_MAP(CEditListCtrl, CListCtrl)
    ON_WM_LBUTTONDBLCLK() // �����л�������ͼ���һ��������ɡ�
    ON_MESSAGE(WM_USER_EDIT_END,CEditListCtrl::OnEditEnd)
	ON_MESSAGE(WM_USER_EDIT_DBCLK,CEditListCtrl::OnEditDbClk)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnNMCustomdraw)
END_MESSAGE_MAP()

void CEditListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // ������ȡ��������Ϣ�Ĺ̶�����
    LVHITTESTINFO lvhti;    // �����󣺱���ListCtrl������Ϣ�Ľṹ
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
        rcCtrl.top -= 2;    // �����󣺷�ֹ�ϱ߿��ڵ�
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
	MessageBox("�����������","��ʾ",MB_OK);
    //CListCtrl::SetItemText(nItem,nSubItem,strText);
    //m_Edit.ShowWindow(SW_HIDE);
}

void CEditListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)  
{  
    // TODO: Add your control notification handler code here   
    *pResult = CDRF_DODEFAULT;  
    NMLVCUSTOMDRAW * lplvdr=(NMLVCUSTOMDRAW*)pNMHDR;  
    NMCUSTOMDRAW &nmcd = lplvdr->nmcd;  
    switch(lplvdr->nmcd.dwDrawStage)//�ж�״̬   
    {  
	case CDDS_PREPAINT:  
        {  
            *pResult = CDRF_NOTIFYITEMDRAW;  
            break;  
        }  
	case CDDS_ITEMPREPAINT://���Ϊ��ITEM֮ǰ��Ҫ������ɫ�ĸı�   
        {  
			TEXT_BK tb;

            if(MapItemColor.Lookup(nmcd.dwItemSpec, tb))  
				// ������ SetItemColor(DWORD iItem, COLORREF color) ���õ�   
				// ITEM�ź�COLORREF �������в��ң�Ȼ�������ɫ��ֵ��   
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


    MapItemColor.SetAt(iItem, tb);//����ĳ�е���ɫ��   
    this->RedrawItems(iItem, iItem);//����Ⱦɫ   
	
    //this->SetCheck(iItem,1);   
    this->SetFocus();    //���ý���   
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


// ������ 2012-11-16 ��
CEditListCtrl::CEditListCtrl(void)
{
}
CEditListCtrl::~CEditListCtrl(void)
{
}
