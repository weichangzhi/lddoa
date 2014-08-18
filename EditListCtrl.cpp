/***********************************************/
/* EditListCtrl.cpp                            */
/***********************************************/
#include "StdAfx.h"
#include "goodsmanagesystem.h"
#include "EditListCtrl.h"
#include "Dialog_Storage_Left2.h"
#include "Dialog_Storage_Name.h"


// 确定运行时对象
IMPLEMENT_DYNAMIC(CListCtrlEdit,CRichEditCtrl)


BEGIN_MESSAGE_MAP(CListCtrlEdit, CRichEditCtrl)
	//{{AFX_MSG_MAP(Dialog_Storage_In)
    ON_WM_KILLFOCUS()// 与对话框中控件消息映射定义不同。
	//ON_WM_LBUTTONDBLCLK()
	//ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CListCtrlEdit::OnKillFocus(CWnd* pNewWnd)
{
    CRichEditCtrl::OnKillFocus(pNewWnd);
    // 向父窗口发消息
    CWnd* pParent = this->GetParent();
    ::PostMessage(pParent->GetSafeHwnd(),WM_USER_EDIT_END,0,0);
}

/*
void CListCtrlEdit::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    CRichEditCtrl::OnLButtonDblClk(nFlags, point);
    // 向父窗口发消息
    CWnd* pParent = this->GetParent();
	char log[256] = {0};
	sprintf(log,"OnLButtonDblClk \t%s,%d: pParent=%p,hwnd=%p",__FILE__,__LINE__,pParent,pParent->GetSafeHwnd());
	writelog(log);

    ::PostMessage(pParent->GetSafeHwnd(),WM_USER_EDIT_DBCLK,0,0);
}


void CListCtrlEdit::OnLButtonUp(UINT nFlags, CPoint point)
{
    CRichEditCtrl::OnLButtonUp(nFlags, point);
    // 向父窗口发消息
    CWnd* pParent = this->GetParent();
	char log[256] = {0};
	sprintf(log,"OnLButtonUp \t%s,%d: pParent=%p,hwnd=%p",__FILE__,__LINE__,pParent,pParent->GetSafeHwnd());
	writelog(log);

    ::PostMessage(pParent->GetSafeHwnd(),WM_USER_EDIT_DBCLK,0,0);
}*/


CListCtrlEdit::CListCtrlEdit(void)
{
}
CListCtrlEdit::~CListCtrlEdit(void)
{
}



// 确定运行时对象
IMPLEMENT_DYNAMIC(CEditListCtrl,CListCtrl)

BEGIN_MESSAGE_MAP(CEditListCtrl, CListCtrl)
    ON_WM_LBUTTONDBLCLK() // 可以切换到类视图，右击属性生成。
    ON_MESSAGE(WM_USER_EDIT_END,CEditListCtrl::OnEditEnd)
	//ON_MESSAGE(WM_USER_EDIT_DBCLK,CEditListCtrl::OnEditDbClk)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, CEditListCtrl::OnNMCustomdraw)
END_MESSAGE_MAP()

void CEditListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    LVHITTESTINFO lvhti;
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
        rcCtrl.top -= 2;
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
	char log[1024] = {0};
	sprintf(log,"OnEditDbClk \t%s,%d: %d-%d,%s",__FILE__,__LINE__,nItem,nSubItem,strText);
	writelog(log);
    CListCtrl::SetItemText(nItem,nSubItem,strText);

	sprintf(log,"OnEditDbClk \t%s,%d: %d-%d,strText=%s",__FILE__,__LINE__,
				nItem,nSubItem,strText);
	writelog(log);
	if(nSubItem==5 || nSubItem==7)
	{
		CString strnumber,strprice;
		strnumber = CListCtrl::GetItemText(nItem,5);
		strprice  = CListCtrl::GetItemText(nItem,7);
		if(!strnumber.IsEmpty() && !strprice.IsEmpty())
		{
			CString strmoney;
			strmoney.Format("%0.2f",atoi(strnumber)*atof(strprice));
			CListCtrl::SetItemText(nItem,8,strmoney);
		}
		
	}
    m_Edit.ShowWindow(SW_HIDE);
	sprintf(log,"OnEditDbClk \t%s,%d:  %d-%d,strText=%s",__FILE__,__LINE__,
				nItem,nSubItem,strText);
	writelog(log);
	
    return 0;
}

/*
void CEditListCtrl::OnEditDbClk(UINT nFlags, CPoint point)
{
	if(nSubItem==3 || nSubItem==4)
	{
		Dialog_Storage_Left2 dlg;
		if(dlg.DoModal()==IDOK)
		{
			CListCtrl::SetItemText(nItem,3,dlg.m_scb);
			CListCtrl::SetItemText(nItem,4,dlg.m_name);
			CListCtrl::SetItemText(nItem,5,dlg.m_number);
			CListCtrl::SetItemText(nItem,6,dlg.m_unit);
			CListCtrl::SetItemText(nItem,7,dlg.m_price);
			CString strmoney;
			strmoney.Format("%0.2f",atoi(dlg.m_number) * atof(dlg.m_price));
			CListCtrl::SetItemText(nItem,8,strmoney);
			if(nSubItem==3)
				m_Edit.SetWindowText(dlg.m_scb);
			if(nSubItem==4)
				m_Edit.SetWindowText(dlg.m_name);
		}
	}
	if(nSubItem==1 || nSubItem==2)//仓库
	{
		Dialog_Storage_Name dlg;
		if(dlg.DoModal()==IDOK)
		{
			char log[1024] = {0};
			sprintf(log,"OnEditDbClk \t%s,%d: %d-%d,id=%s,name=%s",__FILE__,__LINE__,
				nItem,nSubItem,dlg.storageid,dlg.storagename);
			writelog(log);
			CListCtrl::SetItemText(nItem,1,dlg.storageid);
			CListCtrl::SetItemText(nItem,2,dlg.storagename);
			sprintf(log,"OnEditDbClk \t%s,%d: m_edit=%p",__FILE__,__LINE__,m_Edit);
			writelog(log);
			if(nSubItem==1)
				m_Edit.SetWindowText(dlg.storageid);
			if(nSubItem==2)
				m_Edit.SetWindowText(dlg.storagename);
			sprintf(log,"OnEditDbClk \t%s,%d: m_edit=%p",__FILE__,__LINE__,m_Edit);
			writelog(log);
		//OnEditEnd(NULL,NULL);
		}
	}
}
*/

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

CEditListCtrl::CEditListCtrl(void)
{
}
CEditListCtrl::~CEditListCtrl(void)
{
	char log[256] = {0};
	sprintf(log,"CEditListCtrl \t%s,%d:",__FILE__,__LINE__);
	writelog(log);
}
