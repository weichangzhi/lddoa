// Dialog_BaseInfo1.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_BaseInfo1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_BaseInfo1 dialog


CDialog_BaseInfo1::CDialog_BaseInfo1(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_BaseInfo1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_BaseInfo1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialog_BaseInfo1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_BaseInfo1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_BaseInfo1, CDialog)
	//{{AFX_MSG_MAP(CDialog_BaseInfo1)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_BaseInfo1 message handlers
