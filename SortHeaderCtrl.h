/*----------------------------------------------------------------------
Copyright (C)2001 MJSoft. All Rights Reserved.
          This source may be used freely as long as it is not sold for
					profit and this copyright information is not altered or removed.
					Visit the web-site at www.mjsoft.co.uk
					e-mail comments to info@mjsoft.co.uk
File:     SortHeaderCtrl.h
Purpose:  Provides the header control, with drawing of the arrows, for
          the list control.
----------------------------------------------------------------------*/

#ifndef SORTHEADERCTRL_H
#define SORTHEADERCTRL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSortHeaderCtrl : public CHeaderCtrl
{
// Construction
public:
	CSortHeaderCtrl();
//	CSortHeaderCtrl() : m_bLocked(FALSE) { }

	// turn locking on/off
	void Lock(BOOL bLock) {
		m_bLocked = bLock;
	}

	// find out if locked
	BOOL IsLocked() {
		return m_bLocked;
	}

// Attributes
public:
	int m_SubItem;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSortHeaderCtrl)
	public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSortHeaderCtrl();

	void SetSortArrow( const int iColumn, const BOOL bAscending );

	// Generated message map functions
protected:
	void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );
 
	int m_iSortColumn;
	BOOL m_bSortAscending;
	BOOL m_bLocked;	// columns are locked
	virtual BOOL OnChildNotify(UINT msg, WPARAM wp, LPARAM lp, LRESULT* pRes);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
//	DECLARE_MESSAGE_MAP();

	//{{AFX_MSG(CSortHeaderCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // SORTHEADERCTRL_H
