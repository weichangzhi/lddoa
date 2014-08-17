// Dialog_Storage_Print.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_Storage_Print.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_Print dialog


Dialog_Storage_Print::Dialog_Storage_Print(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_Storage_Print::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_Storage_Print)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dialog_Storage_Print::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_Storage_Print)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_Storage_Print, CDialog)
	//{{AFX_MSG_MAP(Dialog_Storage_Print)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_Print message handlers

HBRUSH Dialog_Storage_Print::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	CBrush m_brush (RGB(255,255,255));
	
	CRect m_rect;
	GetClientRect(m_rect);
	
	pDC->FillRect(m_rect,&m_brush);
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL Dialog_Storage_Print::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_Storage_Print::OnPaint() 
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
	DrawReport(m_rect,GetDC(),false,TRUE);
	
	// Do not call CDialog::OnPaint() for painting messages
}

void Dialog_Storage_Print::DrawReport(CRect rect, CDC *pDC, BOOL isprinted, BOOL isIn)
{
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
	if(isIn)
		strtmp.Format("������");
	else
		strtmp.Format("���ⵥ");
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

	
	font150.CreatePointFont(180,_T("����"),pDC);
	font120.CreatePointFont(120,_T("����"),pDC);
	font90.CreatePointFont(100,_T("����"),pDC);	
	pen1.CreatePen (PS_SOLID,2,RGB(0,0,0));
	pen2.CreatePen (PS_SOLID,1,RGB(0,0,0));

	pDC->SelectObject(&font150);
	recttmp.top += (int)(ratey*30);
	pDC->DrawText(strtmp,recttmp,DT_CENTER);

	pDC->SelectObject(&font120);
	strtmp.Format("�Ƶ����ڣ�%s        ",m_strCurrent);
	recttmp = rect;
	recttmp.left += (int)(0*ratex);
	recttmp.top += (int)(ratey*60);
	recttmp.right -= (int)(ratex*50);
	pDC->DrawText(strtmp,recttmp,DT_RIGHT|DT_EDITCONTROL|DT_WORDBREAK);
	strtmp.Format("���ݱ�ţ�%s",m_StorageInID);
	recttmp = rect;
	recttmp.left += (int)(0*ratex);
	recttmp.top += (int)(ratey*80);
	recttmp.right -= (int)(ratex*50);
	pDC->DrawText(strtmp,recttmp,DT_RIGHT|DT_EDITCONTROL|DT_WORDBREAK);
	
	if(isIn)
	{
		strtmp.Format("��Ӧ��:%s    ������:%s    ����:%s    ��������:%s",m_strProvider,m_strOperator,m_strDepartment,m_strPayment);
		recttmp = rect;
		recttmp.left += (int)(50*ratex);
		recttmp.top += (int)(ratey*100);
		pDC->DrawText(strtmp,recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);

		strtmp.Format("�ջ��ֿ�:%s    ժҪ:%s",m_strStorage,m_Digest);
		recttmp = rect;
		recttmp.left += (int)(50*ratex);
		recttmp.top += (int)(ratey*120);
		pDC->DrawText(strtmp,recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	}
	else
	{
		strtmp.Format("ȡ����:%s    ������:%s    ����:%s    ȡ������:%s",m_strProvider,m_strOperator,m_strDepartment,m_strPayment);
		recttmp = rect;
		recttmp.left += (int)(50*ratex);
		recttmp.top += (int)(ratey*100);
		pDC->DrawText(strtmp,recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);

		strtmp.Format("�ֿ�:%s    ժҪ:%s",m_strStorage,m_Digest);
		recttmp = rect;
		recttmp.left += (int)(50*ratex);
		recttmp.top += (int)(ratey*120);
		pDC->DrawText(strtmp,recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	}
	//table height 20 ,width 50   17*11

	pOldPen=pDC->SelectObject (&pen1);
	//�������߿�
	recttmp = rect;
	pDC->Rectangle (recttmp.left+(int)(ratex*50),recttmp.top+(int)(ratey*140),recttmp.right-(int)(ratex*50),recttmp.top+(int)(ratey*480));
	//��������
	pOldPen=pDC->SelectObject (&pen1);

	int i;
	for(i=1;i<17;i++)
	{
		recttmp = rect;
		pDC->MoveTo (recttmp.left+(int)(ratex*50),recttmp.top+(int)(ratey*140+ratey*20*i));
		pDC->LineTo (recttmp.right-(int)(ratex*50),recttmp.top+(int)(ratey*140+ratey*20*i));
	}
	for(i=1;i<10;i++)
	{
		recttmp = rect;
		pDC->MoveTo (recttmp.left+(int)(ratex*50+ratex*50*i),recttmp.top+(int)(ratey*140));
		pDC->LineTo (recttmp.left+(int)(ratex*50+ratex*50*i),recttmp.top+(int)(ratey*480));
	}

	pDC->SelectObject(&font90);
	recttmp = rect;
	recttmp.left += (int)(52*ratex);
	recttmp.top += (int)(ratey*146);
	pDC->DrawText("�к�",recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	recttmp = rect;
	recttmp.left += (int)(102*ratex);
	recttmp.top += (int)(ratey*146);
	pDC->DrawText("�ֿ���",recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	recttmp = rect;
	recttmp.left += (int)(152*ratex);
	recttmp.top += (int)(ratey*146);
	pDC->DrawText("�ֿ�ȫ��",recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	recttmp = rect;
	recttmp.left += (int)(202*ratex);
	recttmp.top += (int)(ratey*146);
	pDC->DrawText("SCB",recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	recttmp = rect;
	recttmp.left += (int)(252*ratex);
	recttmp.top += (int)(ratey*146);
	pDC->DrawText("����",recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	recttmp = rect;
	recttmp.left += (int)(302*ratex);
	recttmp.top += (int)(ratey*146);
	pDC->DrawText("����",recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	recttmp = rect;
	recttmp.left += (int)(352*ratex);
	recttmp.top += (int)(ratey*146);
	pDC->DrawText("��λ",recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	recttmp = rect;
	recttmp.left += (int)(402*ratex);
	recttmp.top += (int)(ratey*146);
	pDC->DrawText("����",recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	recttmp = rect;
	recttmp.left += (int)(452*ratex);
	recttmp.top += (int)(ratey*146);
	pDC->DrawText("���",recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	recttmp = rect;
	recttmp.left += (int)(502*ratex);
	recttmp.top += (int)(ratey*146);
	pDC->DrawText("��ժҪ",recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);

	int j=0;
	for(i=0;i<15;i++)
		for(j=0;j<10;j++)
		{
			strtmp = m_list->GetItemText(i,j);
			recttmp = rect;
			recttmp.left += (int)(52*ratex + 50*ratex*j);
			recttmp.top += (int)(ratey*166 + ratey*20*i);
			pDC->DrawText(strtmp,recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
		}
	
	int number = 0;
	float money = 0;
	for(i=0;i<15;i++)
	{
		number += atoi(m_list->GetItemText(i,5));
		money  += atof(m_list->GetItemText(i,8));
	}
	recttmp = rect;
	recttmp.left += (int)(52*ratex);
	recttmp.top += (int)(ratey*466);
	pDC->DrawText("�ϼ�",recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	strtmp.Format("%d",number);
	recttmp = rect;
	recttmp.left += (int)(302*ratex);
	recttmp.top += (int)(ratey*466);
	pDC->DrawText(strtmp,recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);
	strtmp.Format("%0.2f",money);
	recttmp = rect;
	recttmp.left += (int)(452*ratex);
	recttmp.top += (int)(ratey*466);
	pDC->DrawText(strtmp,recttmp,DT_LEFT|DT_EDITCONTROL|DT_WORDBREAK);



	if(isprinted)
	{
		pDC->EndPage();
		pDC->EndDoc();
	}
}
