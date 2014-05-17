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
	m_strTime = _T("");
	m_strIndex = _T("");
	m_strSellName = _T("");
	m_strSellPhone = _T("");
	
	m_strCompanyName = _T("");
	m_strUserAddress = _T("");
	m_strUserName  = _T("");
	m_strUserPhone = _T("");
	
	m_dProCount = 0;
	m_pProInfo = NULL;
	
	m_strTotalPrice = _T("");
	m_strSellPrice = _T("");
	m_strTotalCount = _T("");
	m_strUpperMoney = _T("");
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
	if(isprinted)
	{
		
		pDC->StartDoc("printinformation");	
	}
	else
	{
		ratex=1,ratey=1;
	}
	CFont font130,font150,font90,font80;
	CPen pen1,pen2,*pOldPen;
	font130.CreatePointFont(130,_T("宋体"),pDC);
	pDC->SelectObject(&font130);
	rect.DeflateRect(0,(int)(ratey*30),0,0);
	pDC->DrawText("武汉东邦自动化设备有限公司",rect,DT_CENTER);
	font90.CreatePointFont(90,_T("宋体"),pDC);
	pDC->SelectObject(&font90);
	rect.DeflateRect(0,(int)(ratey*25),0,0);
	pDC->DrawText("公司地址：武汉市江汉区前进四路72号",rect,DT_CENTER);	
	rect.DeflateRect(0,(int)(ratey*20),0,0);
	pDC->DrawText("TEL：027-82772709  FAX:027-82772709  Email:HKP.618@163.com",rect,DT_CENTER);
	font150.CreatePointFont(150,_T("宋体"),pDC);
	pDC->SelectObject(&font150);
	rect.DeflateRect(0,(int)(ratey*30),0,0);
	pDC->DrawText("销售出货单",rect,DT_CENTER);

	pDC->SelectObject(&font90);
	rect.DeflateRect((int)(25*ratex),(int)(ratey*20),0,0);
	pDC->DrawText("公司名称:",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*70),0,0,0);
	pDC->DrawText(m_strCompanyName,rect,DT_LEFT);
	rect.DeflateRect((int)(-ratex*70),(int)(ratey*15),0,0);
	pDC->DrawText("客户地址:",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*70),0,0,0);
	pDC->DrawText(m_strUserAddress,rect,DT_LEFT);
	rect.DeflateRect((int)(-ratex*70),(int)(ratey*15),0,0);
	pDC->DrawText("客户电话:",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*70),0,0,0);
	pDC->DrawText(m_strUserPhone,rect,DT_LEFT);
	rect.DeflateRect((int)(-ratex*70),(int)(ratey*15),0,0);
	pDC->DrawText("联系人:",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*70),0,0,0);
	pDC->DrawText(m_strUserName,rect,DT_LEFT);

	rect.DeflateRect((int)(ratex*350),(int)(-ratey*45),0,0);
	pDC->DrawText("出货单号:",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*70),0,0,0);
	pDC->DrawText(m_strIndex,rect,DT_LEFT);
	rect.DeflateRect((int)(-ratex*70),(int)(ratey*15),0,0);
	pDC->DrawText("出货日期:",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*70),0,0,0);
	pDC->DrawText(m_strTime,rect,DT_LEFT);
	rect.DeflateRect((int)(-ratex*70),(int)(ratey*15),0,0);
	pDC->DrawText("销售人员:",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*70),0,0,0);
	pDC->DrawText(m_strSellName,rect,DT_LEFT);
	rect.DeflateRect((int)(-ratex*70),(int)(ratey*15),0,0);
	pDC->DrawText("联系电话:",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*70),0,0,0);
	pDC->DrawText(m_strSellPhone,rect,DT_LEFT);
	//170,486,515,638
	pen1.CreatePen (PS_SOLID,2,RGB(0,0,0));
	pOldPen=pDC->SelectObject (&pen1);
	//画表格外边框
	pDC->Rectangle ((int)(ratex*25),(int)(ratey*185),610,465);
	//创建画笔
	pen2.CreatePen (PS_SOLID,1,RGB(0,0,0));
	pOldPen=pDC->SelectObject (&pen2);
	//画横线
	for(int i=1;i<=13;i++)
	{
		pDC->MoveTo ((int)(ratex*25),(int)(ratey*185+i*20));
		pDC->LineTo ((int)(ratex*609),(int)(ratey*185+i*20));
	}
	//画竖线
	pDC->MoveTo ((int)(ratex*60),(int)(ratey*185));
	pDC->LineTo ((int)(ratex*60),(int)(ratey*425));
	pDC->MoveTo ((int)(ratex*260),(int)(ratey*185));
	pDC->LineTo ((int)(ratex*260),(int)(ratey*445));
	pDC->MoveTo ((int)(ratex*320),(int)(ratey*185));
	pDC->LineTo ((int)(ratex*320),(int)(ratey*445));
	pDC->MoveTo ((int)(ratex*380),(int)(ratey*185));
	pDC->LineTo ((int)(ratex*380),(int)(ratey*445));
	pDC->MoveTo ((int)(ratex*440),(int)(ratey*185));
	pDC->LineTo ((int)(ratex*440),(int)(ratey*445));
	pDC->MoveTo ((int)(ratex*500),(int)(ratey*185));
	pDC->LineTo ((int)(ratex*500),(int)(ratey*425));

	pDC->MoveTo ((int)(ratex*85),(int)(ratey*425));
	pDC->LineTo ((int)(ratex*85),(int)(ratey*465));
	pDC->MoveTo ((int)(ratex*200),(int)(ratey*425));
	pDC->LineTo ((int)(ratex*200),(int)(ratey*445));


 	pDC->MoveTo ((int)(ratex*25),(int)(ratey*485));
 	pDC->LineTo ((int)(ratex*610),(int)(ratey*485));
 	pDC->MoveTo ((int)(ratex*25),(int)(ratey*487));
 	pDC->LineTo ((int)(ratex*610),(int)(ratey*487));

	//写产品标头
	rect.DeflateRect((int)(-485*ratex),(int)(ratey*20),0,0);
	pDC->DrawText("序号",rect,DT_LEFT);
	rect.DeflateRect((int)(ratey*100),0,0,0);
	pDC->DrawText("商品型号",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*150),0,0,0);
	pDC->DrawText("单位",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*55),0,0,0);
	pDC->DrawText("单价",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*65),0,0,0);
	pDC->DrawText("数量",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*55),0,0,0);
	pDC->DrawText("金额",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*85),0,0,0);
	pDC->DrawText("备注",rect,DT_LEFT);
	//t 190,b 526,l 540,r 638
	//写入产品信息
	if (m_dProCount>0)
	{
		int index = 0;
		for (index=0;(index<m_dProCount) && (index<11);index++)//每页只能写入11项产品
		{
			if(index==0)
			{
				rect.DeflateRect((int)(-502*ratex),(int)(ratey*20),0,0);
			}
			else
			{
				rect.DeflateRect((int)(-467*ratex),(int)(ratey*20),0,0);
			}
			CString strIndex;
			strIndex.Format("%d",index+1);
			pDC->DrawText(strIndex,rect,DT_LEFT);
			rect.DeflateRect((int)(ratex*32),0,0,0);
			pDC->DrawText(m_pProInfo[index].strProType,rect,DT_LEFT);
			rect.DeflateRect((int)(ratex*210),0,0,0);
			pDC->DrawText(m_pProInfo[index].strUint,rect,DT_LEFT);
			rect.DeflateRect((int)(ratex*50),0,0,0);
			pDC->DrawText(m_pProInfo[index].strPrice,rect,DT_LEFT);
			rect.DeflateRect((int)(ratex*65),0,0,0);
			pDC->DrawText(m_pProInfo[index].strCount,rect,DT_LEFT);
			rect.DeflateRect((int)(ratex*50),0,0,0);
			pDC->DrawText(m_pProInfo[index].strMoney,rect,DT_LEFT);
			rect.DeflateRect((int)(ratex*60),0,0,0);
			pDC->DrawText(m_pProInfo[index].strTips,rect,DT_LEFT);		
		}
	}
	if (m_dProCount==0)
	{
		rect.DeflateRect((int)(-ratex*35),0,0,0);
	}
	rect.DeflateRect((int)(-ratex*475),(int)(ratex*(240-(20*m_dProCount))),0,0);
	pDC->DrawText("金额合计",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*60),0,0,0);//大写总金额
	pDC->DrawText("零",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*115),0,0,0);
	pDC->DrawText("开票类型",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*60),0,0,0);
	pDC->DrawText("已开",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*60),0,0,0);
	pDC->DrawText("合计",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*60),0,0,0);//数量
	pDC->DrawText(m_strTotalCount,rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*60),0,0,0);//总金额
	pDC->DrawText(m_strTotalPrice,rect,DT_LEFT);
	//430,526,445,638
	rect.DeflateRect((int)(-ratex*415),(int)(ratex*20),0,0);
	pDC->DrawText("发货方式",rect,DT_LEFT);
	rect.DeflateRect(0,(int)(ratex*20),0,0);
	pDC->DrawText("审核人:",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*200),0,0,0);
	pDC->DrawText("制单人:",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*60),0,0,0);
	pDC->DrawText("吴明清:",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*200),0,0,0);
	pDC->DrawText("客户签收:",rect,DT_LEFT);

	font80.CreatePointFont(85,_T("宋体"),pDC);
	pDC->SelectObject(&font80);
	rect.DeflateRect((int)(-ratex*460),20,0,0);
	pDC->DrawText("第1页/共1页",rect,DT_LEFT);
	rect.DeflateRect((int)(ratex*380),0,0,0);
	pDC->DrawText("打印时间:",rect,DT_LEFT);
	CTime currentTime = CTime::GetCurrentTime();
	CString strTimePrint;
	strTimePrint.Format("%04d-%02d-%02d  %02d:%02d:%02d",currentTime.GetYear(),
		currentTime.GetMonth(),currentTime.GetDay(),currentTime.GetHour(),currentTime.GetMinute(),currentTime.GetSecond());
	rect.DeflateRect((int)(ratex*80),0,0,0);
	pDC->DrawText(strTimePrint,rect,DT_LEFT);

	if(isprinted)
	{
		pDC->EndDoc();
	}
}