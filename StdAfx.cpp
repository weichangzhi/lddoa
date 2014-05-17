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
	{0,SAVE_LIST,"提交订单"},
	{1,START_LIST,"下单"},
	{2,END_LIST,"结单"},
	{3,DEL_LIST,"销单"},
	{4,REFUND,"退账"},
	{5,MODIFY_LIST_BEFORE,"修改订单资料(下单前)"},
	{6,MODIFY_LIST_AFTER,"修改订单资料(下单后)"},
	{7,QUERY_LIST,"查询订单金额"},
	{8,POST_TC,"过账(技术部)"},
	{9,POST_PD,"过账(生产部)"},
	{10,POST_STORAGE,"过账(成品仓)"},
	{11,POST_SEND,"过账(物流)"},
	{12,PERMISSION,"权限管理"},
	{13,QC,"质检"}
};


