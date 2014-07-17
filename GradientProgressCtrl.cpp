// GradientProgressCtrl.cpp : implementation file

#include "stdafx.h"
#include "GradientProgressCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGradientProgressCtrl

CGradientProgressCtrl::CGradientProgressCtrl()
{
	//��ʼ��
	m_nLower = 0;
	m_nUpper = 100;
	m_nCurrentPosition = 0;
	m_nStep = 10;	
	
	//m_clrStart	= COLORREF(RGB(255, 0,0));
	//m_clrEnd =	 COLORREF(RGB(0,0,255));
	m_clrStart	= COLORREF(RGB(232,237,253));
	m_clrEnd =	 COLORREF(RGB(0,0,255));
	m_clrBkGround = ::GetSysColor(COLOR_3DFACE);
	m_clrText = COLORREF(RGB(255, 255, 255));

	m_bShowPercent = FALSE;
}

CGradientProgressCtrl::~CGradientProgressCtrl()
{
}


BEGIN_MESSAGE_MAP(CGradientProgressCtrl, CProgressCtrl)
	//{{AFX_MSG_MAP(CGradientProgressCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGradientProgressCtrl message handlers

void CGradientProgressCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	//����������ĵ�ǰλ�ò���ȷ���򽥱䵽����ɫ
	if (m_nCurrentPosition <= m_nLower || m_nCurrentPosition >= m_nUpper)
	{
		CRect rect;
		GetClientRect(rect);
		CBrush brush;
		brush.CreateSolidBrush(::GetSysColor(COLOR_3DFACE));
		dc.FillRect(&rect, &brush);
		VERIFY(brush.DeleteObject());
		return;
	}


	//�����Ҫ���������
	CRect rectClient;
	GetClientRect(&rectClient);
	float maxWidth((float)m_nCurrentPosition/(float)m_nUpper * (float)rectClient.right);


	//��������ɫ
	DrawGradient(&dc, rectClient, (int)maxWidth);

	//�����Ҫ��ʾ�ٷ���������ʾ
	if (m_bShowPercent)
	{
		CString percent;
		percent.Format("%.0f%%", 100.0f*(float)m_nCurrentPosition/(float)m_nUpper);
		dc.SetTextColor(m_clrText);
		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(percent, &rectClient, DT_VCENTER |  DT_CENTER | DT_SINGLELINE);
	}
}


//���ý�������Χ
void CGradientProgressCtrl:: SetRange(int nLower, int nUpper)
{
	m_nLower = nLower;
	m_nUpper = nUpper;
	m_nCurrentPosition = nLower;
	CProgressCtrl::SetRange(nLower, nUpper);
}

//���ý�������λ��
int CGradientProgressCtrl:: SetPos(int nPos)
{
	m_nCurrentPosition = nPos;
	return (CProgressCtrl::SetPos(nPos));
}

//���ý������Ĳ���
int CGradientProgressCtrl:: SetStep(int nStep)
{
	m_nStep = nStep;
	return (CProgressCtrl::SetStep(nStep));
}

int CGradientProgressCtrl:: StepIt(void)
{
	m_nCurrentPosition += m_nStep;
	return (CProgressCtrl::StepIt());
}

//���ʵ����򻭽�����ɫ
void CGradientProgressCtrl::DrawGradient(CPaintDC *pDC, const RECT &rectClient, const int &nMaxWidth)
{
	RECT rectFill;			   
	float fStep;              
	CBrush brush;			

	
	CMemDC memDC(pDC);

	//�ҵ���ʵ��ɫ�ͽ�����ɫ֮��������ɫֵ���������䲽����
	int r, g, b;							
	float rStep, gStep, bStep;		

	r = (GetRValue(m_clrEnd) - GetRValue(m_clrStart));
	g = (GetGValue(m_clrEnd) - GetGValue(m_clrStart));
	b =  (GetBValue(m_clrEnd) - GetBValue(m_clrStart));

	int nSteps = max(abs(r), max(abs(g), abs(b)));

	fStep = (float)rectClient.right / (float)nSteps;

	//����ÿ����ɫ�Ĳ���
	rStep = r/(float)nSteps;
	gStep = g/(float)nSteps;
	bStep = b/(float)nSteps;

	r = GetRValue(m_clrStart);
	g = GetGValue(m_clrStart);
	b = GetBValue(m_clrStart);


	// ��ʼ�����ɫ
	for (int iOnBand = 0; iOnBand < nSteps; iOnBand++) 
	{
		
		::SetRect(&rectFill,
					(int)(iOnBand * fStep),       
					 0,									 
					(int)((iOnBand+1) * fStep),         
					rectClient.bottom+1);			
	
		VERIFY(brush.CreateSolidBrush(RGB(r+rStep*iOnBand, g + gStep*iOnBand, b + bStep *iOnBand)));
		memDC.FillRect(&rectFill,&brush);
		VERIFY(brush.DeleteObject());

		if (rectFill.right > nMaxWidth)
		{
			::SetRect(&rectFill, rectFill.right, 0, rectClient.right, rectClient.bottom);
			VERIFY(brush.CreateSolidBrush(m_clrBkGround));
			memDC.FillRect(&rectFill, &brush);
			VERIFY(brush.DeleteObject());
			return;
		}
	}
}

BOOL CGradientProgressCtrl::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}
