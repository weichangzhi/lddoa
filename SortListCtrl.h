/*----------------------------------------------------------------------
Copyright (C)2001 MJSoft. All Rights Reserved.
          This source may be used freely as long as it is not sold for
					profit and this copyright information is not altered or removed.
					Visit the web-site at www.mjsoft.co.uk
					e-mail comments to info@mjsoft.co.uk
File:     SortListCtrl.h
Purpose:  Provides a sortable list control, it will sort text, numbers
          and dates, ascending or descending, and will even draw the
					arrows just like windows explorer!
----------------------------------------------------------------------*/

#ifndef SORTLISTCTRL_H
#define SORTLISTCTRL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef SORTHEADERCTRL_H
	#include "SortHeaderCtrl.h"
#endif	// SORTHEADERCTRL_H

class CSortListCtrl : public CListCtrl
{
// Construction
public:
	CSortListCtrl(UINT nSubItem=0);
// Attributes
public:
	int m_SubItem;
// Operations
public:
	void Sort( int iColumn, BOOL bAscending );
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSortListCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
// Implementation
public:
	virtual ~CSortListCtrl();
	BOOL Create (DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	// Generated message map functions
protected:
	static int CALLBACK CompareFunction( LPARAM lParam1, LPARAM lParam2, LPARAM lParamData );

	CSortHeaderCtrl m_ctlHeader;	
	int m_iNumColumns;
	int m_iSortColumn;
	BOOL m_bSortAscending;

	//{{AFX_MSG(CSortListCtrl)
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // SORTLISTCTRL_H
