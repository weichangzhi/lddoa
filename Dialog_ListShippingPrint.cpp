// Dialog_ListShippingPrint.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_ListShippingPrint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_ListShippingPrint dialog


Dialog_ListShippingPrint::Dialog_ListShippingPrint(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_ListShippingPrint::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_ListShippingPrint)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dialog_ListShippingPrint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_ListShippingPrint)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_ListShippingPrint, CDialog)
	//{{AFX_MSG_MAP(Dialog_ListShippingPrint)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_ListShippingPrint message handlers

HBRUSH Dialog_ListShippingPrint::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	CBrush m_brush (RGB(255,255,255));
	
	CRect m_rect;
	GetClientRect(m_rect);
	
	pDC->FillRect(m_rect,&m_brush);
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL Dialog_ListShippingPrint::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_ListShippingPrint::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect m_rect;
	GetClientRect(m_rect);	
	CDC* pDC = GetDC();
	screenx = pDC->GetDeviceCaps(LOGPIXELSX);
	screeny = pDC->GetDeviceCaps(LOGPIXELSY);
	char log[256] = {0};
	sprintf(log,"OnPaint \t%s,%d:rect [%dx%d, %dx%d],screan[%dx%d]",__FILE__,__LINE__,
			m_rect.left,m_rect.top,m_rect.right,m_rect.bottom,screenx,screeny);
	writelog(log);
	DrawReport(m_rect,GetDC(),false);
}

void Dialog_ListShippingPrint::DrawReport(CRect rect, CDC *pDC, BOOL isprinted)
{
	int selcount = 0;
	int i=0;
	for(i=0; i<m_list->GetItemCount(); i++)
	{
	   //if( m_listFI.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || m_listFI.GetCheck(i))
		if(m_list->GetCheck(i))
		{
			selcount++;
		}
	}

	int printx,printy;
	printx = pDC->GetDeviceCaps(LOGPIXELSX);
	printy = pDC->GetDeviceCaps(LOGPIXELSY);
	double ratex = (double)(printx)/screenx;
	double ratey = (double)(printy)/screeny;
	int phyx = pDC->GetDeviceCaps(PHYSICALWIDTH);
	int phyy = pDC->GetDeviceCaps(PHYSICALHEIGHT);
	ratex = (double)(phyx)/screenx * (screenx/600.0);
	ratey = (double)(phyy)/screeny * (screeny/600.0);
	char log[256] = {0};
	sprintf(log,"DrawReport \t%s,%d:rect [%dx%d, %dx%d],phy [%dx%d], screan[%dx%d],rate[%fx%f]",__FILE__,__LINE__,
			rect.left,rect.top,rect.right,rect.bottom,phyx,phyy,screenx,screeny,ratex,ratey);
	writelog(log);

	CString strtmp;
	strtmp.Format("发货清单");
	if(isprinted)
	{
		DOCINFO   doc;
	    ZeroMemory(&doc,sizeof(doc));
	    doc.cbSize = sizeof(doc);
	    doc.lpszDocName = (LPCTSTR)strtmp;
		pDC->StartDoc(&doc);	
		pDC->StartPage();
	}
	else
	{
		ratex=1,ratey=1;
	}

	CRect recttmp(rect);
	CFont font120,font150,font90,font80;
	CPen pen1,pen2,*pOldPen;

	
	font150.CreatePointFont(180,_T("宋体"),pDC);
	font120.CreatePointFont(120,_T("宋体"),pDC);
	font90.CreatePointFont(100,_T("宋体"),pDC);	
	pen1.CreatePen (PS_SOLID,2,RGB(0,0,0));
	pen2.CreatePen (PS_SOLID,1,RGB(0,0,0));

	pDC->SelectObject(&font150);
	recttmp.top += (int)(ratey*30);
	pDC->DrawText(strtmp,recttmp,DT_CENTER);

	pOldPen=pDC->SelectObject (&pen1);
	//画表格外边框
	recttmp = rect;
	pDC->Rectangle (recttmp.left+(int)(ratex*50),recttmp.top+(int)(ratey*60),recttmp.right-(int)(ratex*50),recttmp.top+(int)(ratey*(60+20*(selcount+1))));
	//创建画笔
	pOldPen=pDC->SelectObject (&pen1);
//横线
	for(i=1;i<=selcount;i++)
	{
		recttmp = rect;
		pDC->MoveTo (recttmp.left+(int)(ratex*50),recttmp.top+(int)(ratey*60+ratey*20*i));
		pDC->LineTo (recttmp.right-(int)(ratex*50),recttmp.top+(int)(ratey*60+ratey*20*i));
	}
	//竖线
	for(i=1;i<10;i++)
	{
		recttmp = rect;
		pDC->MoveTo (recttmp.left+(int)(ratex*50+ratex*50*i),recttmp.top+(int)(ratey*60));
		pDC->LineTo (recttmp.left+(int)(ratex*50+ratex*50*i),recttmp.top+(int)(ratey*(60+20*(selcount+1))));
	}

	pDC->SelectObject(&font90);
	recttmp = rect;
	recttmp.left += (int)(52*ratex);
	recttmp.top += (int)(ratey*67);
	pDC->DrawText("订单号",recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	recttmp = rect;
	recttmp.left += (int)(102*ratex);
	recttmp.top += (int)(ratey*67);
	pDC->DrawText("客户姓名",recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	recttmp = rect;
	recttmp.left += (int)(152*ratex);
	recttmp.top += (int)(ratey*67);
	pDC->DrawText("负责人",recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	recttmp = rect;
	recttmp.left += (int)(202*ratex);
	recttmp.top += (int)(ratey*67);
	pDC->DrawText("尺寸",recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	recttmp = rect;
	recttmp.left += (int)(252*ratex);
	recttmp.top += (int)(ratey*67);
	pDC->DrawText("数量",recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	recttmp = rect;
	recttmp.left += (int)(302*ratex);
	recttmp.top += (int)(ratey*67);
	pDC->DrawText("收件人",recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	recttmp = rect;
	recttmp.left += (int)(352*ratex);
	recttmp.top += (int)(ratey*67);
	pDC->DrawText("派单日期",recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	recttmp = rect;
	recttmp.left += (int)(402*ratex);
	recttmp.top += (int)(ratey*67);
	pDC->DrawText("发货日期",recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	recttmp = rect;
	recttmp.left += (int)(452*ratex);
	recttmp.top += (int)(ratey*67);
	pDC->DrawText("经办人",recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	recttmp = rect;
	recttmp.left += (int)(502*ratex);
	recttmp.top += (int)(ratey*67);
	pDC->DrawText("备注",recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);

	int j=0;
	for(i=0;i<selcount;i++)
		for(j=0;j<10;j++)
		{
			strtmp = m_list->GetItemText(i,j+1);
			recttmp = rect;
			recttmp.left += (int)(52*ratex + 50*ratex*j);
			recttmp.top += (int)(ratey*82 + ratey*20*i);
			recttmp.right  = recttmp.left + (int)(46*ratex);
			pDC->DrawText(strtmp,recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
		}

	if(isprinted)
	{
		pDC->EndPage();
		pDC->EndDoc();
	}
}
