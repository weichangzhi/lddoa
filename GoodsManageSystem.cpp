// GoodsManageSystem.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "GoodsManageSystemDlg.h"
#include "Dialog_Login.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGoodsManageSystemApp

BEGIN_MESSAGE_MAP(CGoodsManageSystemApp, CWinApp)
	//{{AFX_MSG_MAP(CGoodsManageSystemApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGoodsManageSystemApp construction

CGoodsManageSystemApp::CGoodsManageSystemApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGoodsManageSystemApp object

CGoodsManageSystemApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGoodsManageSystemApp initialization

BOOL CGoodsManageSystemApp::InitInstance()
{
	 if( !AfxOleInit() ){
          AfxMessageBox("初始化Ole出错！");
          return FALSE;
     }
	 //if (CoInitialize(NULL)!=0)
	{
			//AfxMessageBox("初始化COM支持库失败!");
			//exit(1);
	}
	AfxEnableControlContainer();
	
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	AfxInitRichEdit();
	CDialog_Login login;
	if(login.DoModal()==IDOK)
	{
		CGoodsManageSystemDlg dlg;
		m_pMainWnd = &dlg;
		int nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with OK
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with Cancel
		}
	}
	else
	{
		/*CGoodsManageSystemDlg dlg;
		m_pMainWnd = &dlg;
		int nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with OK
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with Cancel
		}
		*/
	}
	
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
//	CoUninitialize(); 
	return FALSE;
}

int CGoodsManageSystemApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	//g_adoConn.Close();
//	g_adoDataSet.Close();
	return CWinApp::ExitInstance();
}
