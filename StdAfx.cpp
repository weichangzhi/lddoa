// stdafx.cpp : source file that includes just the standard includes
//	GoodsManageSystem.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

BOOL bDesc = 0;
int nColToSort=0;
int nLastColToSort=0;

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

MysqlConnect g_MysqlConnect = {"root", "weichangzhi", "localhost", "sys", 3306};
CString g_user="";
int g_permission = 0;

PermissionLimit g_PermissionLimit[PERMISSION_NUMBER] =
{
	{0,SAVE_LIST,"�ύ����"},
	{1,START_LIST,"�µ�"},
	{2,END_LIST,"�ᵥ"},
	{3,DEL_LIST,"����"},
	{4,REFUND,"����"},
	{5,MODIFY_LIST_BEFORE,"�޸Ķ�������(�µ�ǰ)"},
	{6,MODIFY_LIST_AFTER,"�޸Ķ�������(�µ���)"},
	{7,QUERY_LIST,"��ѯ�������"},
	{8,POST_TC,"����(������)"},
	{9,POST_PD,"����(������)"},
	{10,POST_STORAGE,"����(��Ʒ��)"},
	{11,POST_SEND,"����(����)"},
	{12,PERMISSION,"Ȩ�޹���"},
	{13,QC,"�ʼ�"}
};


