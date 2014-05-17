// GoodsManageSystem.h : main header file for the GOODSMANAGESYSTEM application
//

#if !defined(AFX_GOODSMANAGESYSTEM_H__D5FF00CA_B8F9_4254_B3D9_9F715B1E3FCD__INCLUDED_)
#define AFX_GOODSMANAGESYSTEM_H__D5FF00CA_B8F9_4254_B3D9_9F715B1E3FCD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGoodsManageSystemApp:
// See GoodsManageSystem.cpp for the implementation of this class
//

class CGoodsManageSystemApp : public CWinApp
{
public:
	CGoodsManageSystemApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGoodsManageSystemApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGoodsManageSystemApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOODSMANAGESYSTEM_H__D5FF00CA_B8F9_4254_B3D9_9F715B1E3FCD__INCLUDED_)
