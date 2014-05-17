/*----------------------------------------------------------------------
Copyright (C)2001 MJSoft. All Rights Reserved.
          This source may be used freely as long as it is not sold for
					profit and this copyright information is not altered or removed.
					Visit the web-site at www.mjsoft.co.uk
					e-mail comments to info@mjsoft.co.uk
File:     SortListCtrl.cpp
Purpose:  Provides a sortable list control, it will sort text, numbers
          and dates, ascending or descending, and will even draw the
					arrows just like windows explorer!
----------------------------------------------------------------------*/

#include "stdafx.h"
#include "SortListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


LPCTSTR g_pszSection = _T("ListCtrls");


struct ItemData
{
public:
	ItemData() : arrpsz( NULL ), dwData( NULL ) {}

	LPTSTR* arrpsz;
	DWORD dwData;

private:
	// ban copying.
	ItemData( const ItemData& );
	ItemData& operator=( const ItemData& );
};

CSortListCtrl::CSortListCtrl(UINT nSubItem)
	: m_iNumColumns( 0 )
	, m_iSortColumn( -1 )
	, m_bSortAscending( TRUE )
	,m_SubItem(nSubItem)
{
}

CSortListCtrl::~CSortListCtrl()
{
}


BEGIN_MESSAGE_MAP(CSortListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CSortListCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSortListCtrl message handlers
BOOL CSortListCtrl::Create (DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
    if ( !CListCtrl::Create (dwStyle, rect, pParentWnd, nID) )
    {
        return FALSE;
    }
	m_ctlHeader.m_SubItem = m_SubItem;
	VERIFY( m_ctlHeader.SubclassWindow( GetHeaderCtrl()->GetSafeHwnd() ) );
    return TRUE;
}

void CSortListCtrl::PreSubclassWindow()
{
	// the list control must have the report style.
	ASSERT( GetStyle() & LVS_REPORT );

	CListCtrl::PreSubclassWindow();

//	VERIFY( m_ctlHeader.SubclassWindow( GetHeaderCtrl()->GetSafeHwnd() ) );
}
bool IsNumber( LPCTSTR pszText )
{
	if (lstrlen( pszText )==0||lstrlen( pszText )>9)
		return false;
	for( int i = 0; i < lstrlen( pszText ); i++ )
		if( !_istdigit( pszText[ i ] ) )
			return false;

	return true;
}


int NumberCompare( LPCTSTR pszNumber1, LPCTSTR pszNumber2 )
{
	const int iNumber1 = atoi( pszNumber1 );
	const int iNumber2 = atoi( pszNumber2 );

	if( iNumber1 < iNumber2 )
		return -1;
	
	if( iNumber1 > iNumber2 )
		return 1;

	return 0;
}


bool IsDate( LPCTSTR pszText )
{
	// format should be 99/99/9999.

	if( lstrlen( pszText ) != 10 )
		return false;

	return _istdigit( pszText[ 0 ] )
		&& _istdigit( pszText[ 1 ] )
		&& pszText[ 2 ] == _T('/')
		&& _istdigit( pszText[ 3 ] )
		&& _istdigit( pszText[ 4 ] )
		&& pszText[ 5 ] == _T('/')
		&& _istdigit( pszText[ 6 ] )
		&& _istdigit( pszText[ 7 ] )
		&& _istdigit( pszText[ 8 ] )
		&& _istdigit( pszText[ 9 ] );
}


int DateCompare( const CString& strDate1, const CString& strDate2 )
{
	const int iYear1 = atoi( strDate1.Mid( 6, 4 ) );
	const int iYear2 = atoi( strDate2.Mid( 6, 4 ) );

	if( iYear1 < iYear2 )
		return -1;

	if( iYear1 > iYear2 )
		return 1;

	const int iMonth1 = atoi( strDate1.Mid( 3, 2 ) );
	const int iMonth2 = atoi( strDate2.Mid( 3, 2 ) );

	if( iMonth1 < iMonth2 )
		return -1;

	if( iMonth1 > iMonth2 )
		return 1;

	const int iDay1 = atoi( strDate1.Mid( 0, 2 ) );
	const int iDay2 = atoi( strDate2.Mid( 0, 2 ) );

	if( iDay1 < iDay2 )
		return -1;

	if( iDay1 > iDay2 )
		return 1;

	return 0;
}

int CALLBACK CSortListCtrl::CompareFunction( LPARAM lParam1, LPARAM lParam2, LPARAM lParamData )
{
	CSortListCtrl* pListCtrl = reinterpret_cast<CSortListCtrl*>( lParamData );
	ASSERT( pListCtrl->IsKindOf( RUNTIME_CLASS( CListCtrl ) ) );

	CString pszText1 = pListCtrl->GetItemText(lParam1,pListCtrl->m_iSortColumn);//pid1->arrpsz[ pListCtrl->m_iSortColumn ];
	CString pszText2 = pListCtrl->GetItemText(lParam2,pListCtrl->m_iSortColumn);//pid2->arrpsz[ pListCtrl->m_iSortColumn ];

	if( IsNumber( pszText1 )&&IsNumber( pszText2 ) )
		return pListCtrl->m_bSortAscending ? NumberCompare( pszText1.GetBuffer(0), pszText2.GetBuffer(0) ) : NumberCompare( pszText2.GetBuffer(0), pszText1.GetBuffer(0) );
	else if( IsDate( pszText1 )&& IsDate( pszText2 ))
		return pListCtrl->m_bSortAscending ? DateCompare( pszText1.GetBuffer(0), pszText2.GetBuffer(0) ) : DateCompare( pszText2.GetBuffer(0), pszText1.GetBuffer(0) );
	else
		// text.
		return pListCtrl->m_bSortAscending ? lstrcmp( pszText1.GetBuffer(0), pszText2.GetBuffer(0) ) : lstrcmp( pszText2.GetBuffer(0), pszText1.GetBuffer(0) );
}

void CSortListCtrl::OnColumnClick( NMHDR* pNMHDR, LRESULT* pResult )
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	const int iColumn = pNMListView->iSubItem;
    //为了排序正确，必须做这样一件事情
//	AfxMessageBox("1");
	int i, n = this->GetItemCount();
	for (i=0; i<n; i++)
		this->SetItemData(i, i);

	// if it's a second click on the same column then reverse the sort order,
	// otherwise sort the new column in ascending order.
	Sort( iColumn, iColumn == m_iSortColumn ? !m_bSortAscending : TRUE );

	*pResult = 0;
}


void CSortListCtrl::Sort( int iColumn, BOOL bAscending )
{
	m_iSortColumn = iColumn;
	m_bSortAscending = bAscending;

	// show the appropriate arrow in the header control.
	m_ctlHeader.SetSortArrow( m_iSortColumn, m_bSortAscending );

	VERIFY( SortItems( CompareFunction, reinterpret_cast<DWORD>( this ) ) );
}



