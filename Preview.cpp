// Preview.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Preview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreview dialog


CPreview::CPreview(CWnd* pParent /*=NULL*/)
	: CDialog(CPreview::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPreview)
	m_design_server = _T("");
	m_has_modeling = _T("");
	m_modeling = _T("");
	m_modeling_pring = _T("");
	m_no_modeling = _T("");
	m_scan = _T("");
	m_urgent = _T("");

	m_address = _T("");
	m_bill = _T("");
	m_bottom = _T("");
	m_color = _T("");
	m_department = _T("");
	m_error_range = _T("");
	m_listid = _T("");
	m_listname = _T("");
	m_material = _T("");
	m_money = _T("");
	m_print = _T("");
	m_people = _T("");
	m_phone = _T("");
	m_receivename = _T("");
	m_shine = _T("");
	m_size = _T("");
	m_usage = _T("");
	m_volume = _T("");
	m_other = _T("");
	m_str_reveive_time = _T("");
	m_str_end_date = _T("");
	
	m_totel_number = _T("");
	m_true_number = _T("");
	//}}AFX_DATA_INIT
}


void CPreview::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreview)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreview, CDialog)
	//{{AFX_MSG_MAP(CPreview)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreview message handlers

HBRUSH CPreview::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	CBrush m_brush (RGB(255,255,255));
	
	CRect m_rect;
	GetClientRect(m_rect);
	
	pDC->FillRect(m_rect,&m_brush);
	// TODO: Return a different brush if the default is not desired
	return m_brush;
}

BOOL CPreview::OnInitDialog() 
{
	CDialog::OnInitDialog();
		return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPreview::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect m_rect;
	GetClientRect(m_rect);	
	CDC* pDC = GetDC();
	screenx = pDC->GetDeviceCaps(LOGPIXELSX);
	screeny = pDC->GetDeviceCaps(LOGPIXELSY);
	DrawReport(m_rect,GetDC(),false);
}

void CPreview::DrawReport(CRect rect, CDC *pDC, BOOL isprinted)
{
	int printx,printy;
	printx = pDC->GetDeviceCaps(LOGPIXELSX);
	printy = pDC->GetDeviceCaps(LOGPIXELSY);
	double ratex = (double)(printx)/screenx;
	double ratey = (double)(printy)/screeny;
	char log[256] = {0};
	sprintf(log,"DrawReport \t%s,%d:rect [%dx%d, %dx%d],print [%dx%d], screan[%dx%d],rate[%fx%f]",__FILE__,__LINE__,
			rect.left,rect.top,rect.right,rect.bottom,printx,printy,screenx,screeny,ratex,ratey);
	writelog(log);
	if(isprinted)
	{
		DOCINFO   doc;     
	    ZeroMemory(&doc,sizeof(doc));     
	    doc.cbSize = sizeof(doc);     
	    doc.lpszDocName = (LPCTSTR)"Print Test File";  
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

	CString strtmp;
	strtmp.Format("%s 生产派单表",m_department);
	font150.CreatePointFont(150,_T("宋体"),pDC);
	pDC->SelectObject(&font150);
	recttmp.top += (int)(ratey*20);
	pDC->DrawText(strtmp,recttmp,DT_CENTER);

	//table
	pen1.CreatePen (PS_SOLID,2,RGB(0,0,0));
	pOldPen=pDC->SelectObject (&pen1);
	//画表格外边框
	recttmp = rect;
	pDC->Rectangle (recttmp.left+(int)(ratex*3),recttmp.top+(int)(ratey*70),recttmp.right-(int)(ratex*3),recttmp.top+(int)(ratey*195));
	//创建画笔
	pen2.CreatePen (PS_SOLID,1,RGB(0,0,0));
	pOldPen=pDC->SelectObject (&pen2);
	//画横线
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*3),recttmp.top+(int)(ratey*100));
	pDC->LineTo (recttmp.right-(int)(ratex*3),recttmp.top+(int)(ratey*100));
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*3),recttmp.top+(int)(ratey*130));
	pDC->LineTo (recttmp.right-(int)(ratex*3),recttmp.top+(int)(ratey*130));
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*3),recttmp.top+(int)(ratey*160));
	pDC->LineTo (recttmp.right-(int)(ratex*3),recttmp.top+(int)(ratey*160));
	//画竖线
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*55),recttmp.top+(int)(ratey*70));
	pDC->LineTo (recttmp.left+(int)(ratex*55),recttmp.top+(int)(ratey*195));
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*135),recttmp.top+(int)(ratey*70));
	pDC->LineTo (recttmp.left+(int)(ratex*135),recttmp.top+(int)(ratey*160));
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*195),recttmp.top+(int)(ratey*70));
	pDC->LineTo (recttmp.left+(int)(ratex*195),recttmp.top+(int)(ratey*160));
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*275),recttmp.top+(int)(ratey*70));
	pDC->LineTo (recttmp.left+(int)(ratex*275),recttmp.top+(int)(ratey*160));
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*325),recttmp.top+(int)(ratey*70));
	pDC->LineTo (recttmp.left+(int)(ratex*325),recttmp.top+(int)(ratey*160));
	
	font120.CreatePointFont(120,_T("宋体"),pDC);
	pDC->SelectObject(&font120);
	recttmp = rect;
	recttmp.left += (int)(5*ratex);
	recttmp.top += (int)(ratey*50);
	pDC->DrawText("基本资料：",recttmp,DT_LEFT);

	
	//line 1
	font90.CreatePointFont(90,_T("宋体"),pDC);
	pDC->SelectObject(&font90);
	recttmp = rect;
	recttmp.left += (int)(5*ratex);
	recttmp.top += (int)(ratey*80);
	pDC->DrawText("订单号",recttmp,DT_LEFT);
	recttmp = rect;
	recttmp.left += (int)(60*ratex);
	recttmp.top += (int)(ratey*80);
	pDC->DrawText(m_listid,recttmp,DT_LEFT);

	recttmp = rect;
	recttmp.left += (int)(140*ratex);
	recttmp.top += (int)(ratey*80);
	pDC->DrawText("订单名称",recttmp,DT_LEFT);
	recttmp = rect;
	recttmp.left += (int)(200*ratex);
	recttmp.top += (int)(ratey*80);
	pDC->DrawText(m_listname,recttmp,DT_LEFT);

	recttmp = rect;
	recttmp.left += (int)(280*ratex);
	recttmp.top += (int)(ratey*80);
	pDC->DrawText("经办人",recttmp,DT_LEFT);
	recttmp = rect;
	recttmp.left += (int)(330*ratex);
	recttmp.top += (int)(ratey*80);
	pDC->DrawText(m_people,recttmp,DT_LEFT);
//line 2
	recttmp = rect;
	recttmp.left += (int)(5*ratex);
	recttmp.top += (int)(ratey*110);
	pDC->DrawText("收件人",recttmp,DT_LEFT);
	recttmp = rect;
	recttmp.left += (int)(60*ratex);
	recttmp.top += (int)(ratey*110);
	pDC->DrawText(m_receivename,recttmp,DT_LEFT);

	recttmp = rect;
	recttmp.left += (int)(140*ratex);
	recttmp.top += (int)(ratey*110);
	pDC->DrawText("联系电话",recttmp,DT_LEFT);
	recttmp = rect;
	recttmp.left += (int)(200*ratex);
	recttmp.top += (int)(ratey*110);
	pDC->DrawText(m_phone,recttmp,DT_LEFT);

	recttmp = rect;
	recttmp.left += (int)(280*ratex);
	recttmp.top += (int)(ratey*110);
	pDC->DrawText("部门",recttmp,DT_LEFT);
	recttmp = rect;
	recttmp.left += (int)(330*ratex);
	recttmp.top += (int)(ratey*110);
	pDC->DrawText(m_department,recttmp,DT_LEFT);
//line 3
	recttmp = rect;
	recttmp.left += (int)(5*ratex);
	recttmp.top += (int)(ratey*140);
	pDC->DrawText("派单日期",recttmp,DT_LEFT);
	recttmp = rect;
	recttmp.left += (int)(60*ratex);
	recttmp.top += (int)(ratey*140);
	pDC->DrawText(m_str_reveive_time,recttmp,DT_LEFT);

	recttmp = rect;
	recttmp.left += (int)(140*ratex);
	recttmp.top += (int)(ratey*140);
	pDC->DrawText("交货日期",recttmp,DT_LEFT);
	recttmp = rect;
	recttmp.left += (int)(200*ratex);
	recttmp.top += (int)(ratey*140);
	pDC->DrawText(m_str_end_date,recttmp,DT_LEFT);
//line 4
	recttmp = rect;
	recttmp.left += (int)(5*ratex);
	recttmp.top += (int)(ratey*170);
	pDC->DrawText("详细地址",recttmp,DT_LEFT);
	recttmp = rect;
	recttmp.left += (int)(60*ratex);
	recttmp.top += (int)(ratey*170);
	pDC->DrawText(m_address,recttmp,DT_LEFT);


	pDC->SelectObject(&font120);
	recttmp = rect;
	recttmp.left += (int)(5*ratex);
	recttmp.top += (int)(ratey*210);
	pDC->DrawText("制作要求：",recttmp,DT_LEFT);

	//table 2
	pOldPen=pDC->SelectObject (&pen1);
	//画表格外边框
	recttmp = rect;
	pDC->Rectangle (recttmp.left+(int)(ratex*3),recttmp.top+(int)(ratey*230),recttmp.right-(int)(ratex*3),recttmp.top+(int)(ratey*410));
	pOldPen=pDC->SelectObject (&pen2);
	//画横线
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*3),recttmp.top+(int)(ratey*260));
	pDC->LineTo (recttmp.right-(int)(ratex*3),recttmp.top+(int)(ratey*260));
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*3),recttmp.top+(int)(ratey*290));
	pDC->LineTo (recttmp.right-(int)(ratex*3),recttmp.top+(int)(ratey*290));
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*3),recttmp.top+(int)(ratey*320));
	pDC->LineTo (recttmp.right-(int)(ratex*3),recttmp.top+(int)(ratey*320));
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*3),recttmp.top+(int)(ratey*350));
	pDC->LineTo (recttmp.right-(int)(ratex*3),recttmp.top+(int)(ratey*350));
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*3),recttmp.top+(int)(ratey*380));
	pDC->LineTo (recttmp.right-(int)(ratex*3),recttmp.top+(int)(ratey*380));

	pDC->SelectObject(&font90);
	strtmp.Format("建模%s 设计服务%s 扫描业务%s 模型打印%s 有模型%s 无模型%s 加急%s",
		m_modeling,m_design_server,m_scan,m_modeling_pring,m_has_modeling,m_no_modeling,m_urgent);
	recttmp = rect;
	recttmp.left += (int)(5*ratex);
	recttmp.top += (int)(ratey*240);
	pDC->DrawText(strtmp,recttmp,DT_LEFT);

	strtmp.Format("尺寸:%s  生产数量:%s  制作材料:%s",m_size,m_totel_number,m_material);
	recttmp = rect;
	recttmp.left += (int)(5*ratex);
	recttmp.top += (int)(ratey*270);
	pDC->DrawText(strtmp,recttmp,DT_LEFT);

	strtmp.Format("颜色:%s  打磨:%s  底座搭配:%s  发票随寄:%s",m_color,m_shine,m_bottom,m_bill);
	recttmp = rect;
	recttmp.left += (int)(5*ratex);
	recttmp.top += (int)(ratey*300);
	pDC->DrawText(strtmp,recttmp,DT_LEFT);

	strtmp.Format("用途:%s  误差范围:%s  体积:%s",m_usage,m_error_range,m_volume);
	recttmp = rect;
	recttmp.left += (int)(5*ratex);
	recttmp.top += (int)(ratey*330);
	pDC->DrawText(strtmp,recttmp,DT_LEFT);

	strtmp.Format("喷漆:%s",m_print);
	recttmp = rect;
	recttmp.left += (int)(5*ratex);
	recttmp.top += (int)(ratey*360);
	pDC->DrawText(strtmp,recttmp,DT_LEFT);

	strtmp.Format("其他要求:%s",m_other);
	recttmp = rect;
	recttmp.left += (int)(5*ratex);
	recttmp.top += (int)(ratey*390);
	pDC->DrawText(strtmp,recttmp,DT_LEFT);


	pDC->SelectObject(&font120);
	recttmp = rect;
	recttmp.left += (int)(5*ratex);
	recttmp.top += (int)(ratey*420);
	pDC->DrawText("签名：",recttmp,DT_LEFT);

	//table 3
	pOldPen=pDC->SelectObject (&pen1);
	//画表格外边框
	recttmp = rect;
	pDC->Rectangle (recttmp.left+(int)(ratex*3),recttmp.top+(int)(ratey*440),recttmp.right-(int)(ratex*3),recttmp.top+(int)(ratey*590));
	//创建画笔
	pOldPen=pDC->SelectObject (&pen2);
	//画横线
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*3),recttmp.top+(int)(ratey*470));
	pDC->LineTo (recttmp.right-(int)(ratex*3),recttmp.top+(int)(ratey*470));
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*3),recttmp.top+(int)(ratey*500));
	pDC->LineTo (recttmp.right-(int)(ratex*3),recttmp.top+(int)(ratey*500));
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*3),recttmp.top+(int)(ratey*530));
	pDC->LineTo (recttmp.right-(int)(ratex*3),recttmp.top+(int)(ratey*530));
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*3),recttmp.top+(int)(ratey*560));
	pDC->LineTo (recttmp.right-(int)(ratex*3),recttmp.top+(int)(ratey*560));
	//画竖线
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*55),recttmp.top+(int)(ratey*440));
	pDC->LineTo (recttmp.left+(int)(ratex*55),recttmp.top+(int)(ratey*590));
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*135),recttmp.top+(int)(ratey*440));
	pDC->LineTo (recttmp.left+(int)(ratex*135),recttmp.top+(int)(ratey*590));
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*190),recttmp.top+(int)(ratey*440));
	pDC->LineTo (recttmp.left+(int)(ratex*190),recttmp.top+(int)(ratey*590));
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*275),recttmp.top+(int)(ratey*440));
	pDC->LineTo (recttmp.left+(int)(ratex*275),recttmp.top+(int)(ratey*590));
	recttmp = rect;
	pDC->MoveTo (recttmp.left+(int)(ratex*330),recttmp.top+(int)(ratey*440));
	pDC->LineTo (recttmp.left+(int)(ratex*330),recttmp.top+(int)(ratey*590));
	


	pDC->SelectObject(&font90);
	recttmp = rect;
	recttmp.left += (int)(5*ratex);
	recttmp.top += (int)(ratey*450);
	pDC->DrawText("销售部",recttmp,DT_LEFT);
	recttmp = rect;
	recttmp.left += (int)(140*ratex);
	recttmp.top += (int)(ratey*450);
	pDC->DrawText("主管",recttmp,DT_LEFT);
	recttmp = rect;
	recttmp.left += (int)(280*ratex);
	recttmp.top += (int)(ratey*450);
	pDC->DrawText("日期",recttmp,DT_LEFT);



	recttmp = rect;
	recttmp.left += (int)(5*ratex);
	recttmp.top += (int)(ratey*480);
	pDC->DrawText("技术部",recttmp,DT_LEFT);
	recttmp = rect;
	recttmp.left += (int)(140*ratex);
	recttmp.top += (int)(ratey*480);
	pDC->DrawText("主管",recttmp,DT_LEFT);
	recttmp = rect;
	recttmp.left += (int)(280*ratex);
	recttmp.top += (int)(ratey*480);
	pDC->DrawText("日期",recttmp,DT_LEFT);

	recttmp = rect;
	recttmp.left += (int)(5*ratex);
	recttmp.top += (int)(ratey*510);
	pDC->DrawText("生产部",recttmp,DT_LEFT);
	recttmp = rect;
	recttmp.left += (int)(140*ratex);
	recttmp.top += (int)(ratey*510);
	pDC->DrawText("主管",recttmp,DT_LEFT);
	recttmp = rect;
	recttmp.left += (int)(280*ratex);
	recttmp.top += (int)(ratey*510);
	pDC->DrawText("日期",recttmp,DT_LEFT);

	recttmp = rect;
	recttmp.left += (int)(5*ratex);
	recttmp.top += (int)(ratey*540);
	pDC->DrawText("质检",recttmp,DT_LEFT);
	recttmp = rect;
	recttmp.left += (int)(140*ratex);
	recttmp.top += (int)(ratey*540);
	pDC->DrawText("主管",recttmp,DT_LEFT);
	recttmp = rect;
	recttmp.left += (int)(280*ratex);
	recttmp.top += (int)(ratey*540);
	pDC->DrawText("日期",recttmp,DT_LEFT);

	recttmp = rect;
	recttmp.left += (int)(5*ratex);
	recttmp.top += (int)(ratey*570);
	pDC->DrawText("成品仓",recttmp,DT_LEFT);
	recttmp = rect;
	recttmp.left += (int)(140*ratex);
	recttmp.top += (int)(ratey*570);
	pDC->DrawText("快递单号",recttmp,DT_LEFT);
	recttmp = rect;
	recttmp.left += (int)(280*ratex);
	recttmp.top += (int)(ratey*570);
	pDC->DrawText("日期",recttmp,DT_LEFT);
	
	if(isprinted)
	{
		pDC->EndPage();
		pDC->EndDoc();
	}
}
