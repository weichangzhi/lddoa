// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__438E6034_6C1E_442E_AF95_C5691A6C1514__INCLUDED_)
#define AFX_STDAFX_H__438E6034_6C1E_442E_AF95_C5691A6C1514__INCLUDED_

#undef WINVER 
#define WINVER 0X500

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include "comdef.h"
#include "winsock.h"
#include "mysql.h"
#pragma comment(lib,"libmysql.lib")

#include "excel.h"

extern BOOL bDesc;
extern int nColToSort;
extern int nLastColToSort;
//static int CALLBACK SortLVProc(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort);
bool IsNumber( LPCTSTR pszText );
int NumberCompare( LPCTSTR pszNumber1, LPCTSTR pszNumber2 );
BOOL IsNum(CString &str);
BOOL IsPhoneNum(CString &str);
BOOL IsInt(CString &str);
int CalcDaySpan(CString strtime1,CString strtime2);
void CreateExcel(CString filename,CListCtrl *listctl);
static int CALLBACK SortLVProc(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort) 
{ 	
	// lParamSort contains a pointer to the list view control. 
	CListCtrl* pListCtrl = (CListCtrl*) lParamSort; 
	CString strItem1 = pListCtrl->GetItemText(lParam1,nColToSort); 
	CString strItem2 = pListCtrl->GetItemText(lParam2,nColToSort); 
	if( IsNumber( strItem1 )&&IsNumber( strItem2 ))
	{
		if(bDesc)
			return NumberCompare(strItem1.GetBuffer(0),strItem2.GetBuffer(0));
		else
			return NumberCompare(strItem2.GetBuffer(0),strItem1.GetBuffer(0));
	}
	else
	{
		if(bDesc) 
			return strcmp(strItem1,strItem2); 
		else 
	    	return strcmp(strItem2,strItem1); 
	}	
}

typedef struct _ProductInfo //一条记录结构
{
	CString strProType;   //产品型号
	CString strCount;     //产品数量
	CString strPrice;     //产品价格	
	CString strUint;      //产品单位
	CString strMoney;     //产品金额
	CString strTips;      //备注
}ProductInfo, *pProductInfo ;

typedef struct _MysqlConnect
{
	char user[32];         //username
    char pswd[32] ;         //password
    char host[32];    //or"127.0.0.1"
    char table[32];        //database
    unsigned int port;           //server port   
}MysqlConnect, *pMysqlConnect;

extern MysqlConnect g_MysqlConnect;

extern CString g_user;
extern CString g_department;
extern int g_permission;
extern FILE* g_fplog ;
void writelog(CString strlog);

typedef struct _PermissionLimit
{
	int index;
	int value;
	char info[256];
}PermissionLimit, *pPermissionLimit;

#define SAVE_LIST			1
#define START_LIST			2
#define END_LIST			4
#define DEL_LIST			8
#define REFUND				16
#define MODIFY_LIST_BEFORE	32
#define MODIFY_LIST_AFTER	64
#define QUERY_LIST			128
#define POST_TC				256
#define POST_PD				512
#define POST_STORAGE		1024
#define POST_SEND			2048
#define PERMISSION			4096
#define QC					8192
#define URGENT				16384
#define FI					32768

#define PERMISSION_NUMBER 16
extern PermissionLimit g_PermissionLimit[PERMISSION_NUMBER];
#define CONFIGINI "config.ini"
#define DEFAULT_TIME "14:00"





//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__438E6034_6C1E_442E_AF95_C5691A6C1514__INCLUDED_)
