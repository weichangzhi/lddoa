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

BOOL IsNum(CString &str)
{
	int n=str.GetLength();
	for(int i=0;i<n;i++)
	{
		if ((str[i]<'0'||str[i]>'9') && (str[i]!='.' ))
			return FALSE;
	}
	return TRUE;
}

void CreateExcel(CString filename,CListCtrl *listctl)
{
	Range m_ExlRge; 
	_Worksheet m_ExlSheet; 
	Worksheets m_ExlSheets; 
	_Workbook m_ExlBook; 
	Workbooks m_ExlBooks; 
	_Application m_ExlApp; 
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	//用m_ExlApp对象创建Excel2003进程 

	if(!m_ExlApp.CreateDispatch("Excel.Application",NULL)) 
	{ 
		AfxMessageBox("创建Excel服务失败!"); 
		return; 
	} 

	//设置为可见 
	m_ExlApp.SetVisible(TRUE); 

	///////////////////下面得到应用程序所在的路径/////////////////// 
	CString theAppPath,theAppName; 
	char Path[MAX_PATH]; 

	GetModuleFileName(NULL,Path,MAX_PATH);//得到应用程序的全路径 
	theAppPath=(CString)Path; 

	theAppName=AfxGetApp()->m_pszAppName; 
	theAppName+=".exe"; 

	//把最后的文件名去掉 
	int length1,length2; 

	length1=theAppPath.GetLength(); 
	length2=theAppName.GetLength(); 

	theAppPath.Delete(length1-length2,length2); 
	CString TempPath=""; 
	TempPath=theAppPath+filename;//EXCEL模板的路径 
//	CFile file;
//	file.Open(TempPath,CFile::modeCreate|CFile::modeWrite);
//	file.Close();


	m_ExlBooks.AttachDispatch(m_ExlApp.GetWorkbooks(),TRUE); 

	//m_ExlBook.AttachDispatch(m_ExlBooks.Add((_variant_t)TempPath),TRUE);//加载EXCEL模板 
	m_ExlBook.AttachDispatch(m_ExlBooks.Add(covOptional),TRUE);//加载EXCEL模板 

	m_ExlSheets.AttachDispatch(m_ExlBook.GetSheets(),TRUE);//加载Sheet页面 

	//添加新的Sheet页面 
	m_ExlSheets.Add(vtMissing,vtMissing,_variant_t((long)1),vtMissing); 

	//删除第二个Sheet页面 
	m_ExlSheet.AttachDispatch(m_ExlSheets.GetItem(_variant_t((long)2)),TRUE); 
	m_ExlSheet.Delete(); 

	//把第一个Sheet页面的名字改变为TestSheet 
	m_ExlSheet.AttachDispatch(m_ExlSheets.GetItem(_variant_t((long)1)),TRUE); 
	m_ExlSheet.SetName("订单资料"); 


	////////设置表格内容//////// 

	m_ExlRge.AttachDispatch(m_ExlSheet.GetCells(),TRUE);//加载所有单元格 

	LVCOLUMN col;
	col.mask = LVCF_TEXT ;
	int Column ;
	CHeaderCtrl* pHeaderCtrl = listctl->GetHeaderCtrl();
	if (pHeaderCtrl != NULL)
	{
		Column = pHeaderCtrl->GetItemCount();
	}
	else
	{
		return;
	}
	int count = listctl->GetItemCount();
	int i=0,j=0;
	
	for(i=1;i<=Column;i++)
	{
		HDITEM hdi;
		TCHAR  lpBuffer[256]= {0};
		hdi.mask = HDI_TEXT;
		hdi.pszText = lpBuffer;
		hdi.cchTextMax = 256;
		pHeaderCtrl->GetItem(i-1,&hdi);
		m_ExlRge.SetItem(_variant_t((long)1),_variant_t((long)i),_variant_t(lpBuffer));
	}


	for(i=0;i<count;i++)
	{
		for(j=0;j<Column;j++)
		{
			CString strtmp = listctl->GetItemText(i,j);
			m_ExlRge.SetItem(_variant_t((long)(i+2)),_variant_t((long)(j+1)),_variant_t(strtmp)); 
		}
	}
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("P2"), _variant_t("P100")));//获取表单中的列"P"对象
	m_ExlRge.SetColumnWidth(_variant_t((long)40));  //设置列宽为100

	m_ExlRge.AttachDispatch(m_ExlSheet.GetUsedRange());//加载已使用的单元格 

//	m_ExlRge.SetWrapText(_variant_t((long)1));//设置单元格内的文本为自动换行 

	//设置齐方式为水平垂直居中 
	//水平对齐：默认＝1,居中＝-4108,左＝-4131,右＝-4152 
	//垂直对齐：默认＝2,居中＝-4108,左＝-4160,右＝-4107 
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4131)); 
	m_ExlRge.SetVerticalAlignment(_variant_t((long)-4160)); 

	///////设置整体的字体、字号及颜色////// 

	Font ft; 

	ft.AttachDispatch(m_ExlRge.GetFont()); 

	ft.SetName(_variant_t("宋体"));//字体 
	ft.SetColorIndex(_variant_t((long)11));//字的颜色 
	ft.SetSize(_variant_t((long)12));//字号 

	///////////设置标题字体及颜色////////// 

//	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("D1"))); 

//	ft.AttachDispatch(m_ExlRge.GetFont()); 

//	ft.SetBold(_variant_t((long)1));//粗体 
//	ft.SetSize(_variant_t((long)13)); 
//	ft.SetColorIndex(_variant_t((long)2)); 

//	CellFormat cf; 
//	cf.AttachDispatch(m_ExlRge.GetCells()); 

	//////////////设置底色///////////////// 

//	Interior it; 

//	it.AttachDispatch(m_ExlRge.GetInterior()); 

//	it.SetColorIndex(_variant_t((long)11));//标题底色 

/*	////表格内容的底色//// 

//	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"),_variant_t("D5"))); 

//	it.AttachDispatch(m_ExlRge.GetInterior()); 

//	it.SetColorIndex(_variant_t((long)15)); 


	//////////////为表格设置边框///////////// 

	Range UnitRge; 
	CString CellName; 

	for(i=1;i<=4;i++) 
	{ 
		for(int j=1;j<=4;j++) 
		{ 
			CellName.Format("%c%d",j+64,i);//单元格的名称 

			UnitRge.AttachDispatch(m_ExlRge.GetRange(_variant_t(CellName),_variant_t(CellName)));//加载单元格 

			//LineStyle=线型 Weight=线宽 ColorIndex=线的颜色(-4105为自动) 
			UnitRge.BorderAround(_variant_t((long)1),_variant_t((long)2),_variant_t((long)-4105),vtMissing);//设置边框 
		} 
	} 
	*/
	Range cols;
	cols=m_ExlRge.GetEntireColumn();//选择A:A列，设置宽度为自动适应
	cols.AutoFit();
	m_ExlApp.SetVisible(TRUE);//显示Excel表格，并设置状态为用户可控制
	m_ExlApp.SetUserControl(TRUE);

	m_ExlBook.SaveAs(COleVariant(TempPath),covOptional,
	covOptional,covOptional,
	covOptional,covOptional,(long)0,covOptional,covOptional,covOptional,
	covOptional,covOptional);

	//释放对象（相当重要！） 
	m_ExlRge.ReleaseDispatch(); 
	m_ExlSheet.ReleaseDispatch(); 
	m_ExlSheets.ReleaseDispatch(); 
	m_ExlBook.ReleaseDispatch(); 
	m_ExlBooks.ReleaseDispatch(); 
	//m_ExlApp一定要释放，否则程序结束后还会有一个Excel进程驻留在内存中，而且程序重复运行的时候会出错 
	m_ExlApp.ReleaseDispatch(); 

	//退出程序
	m_ExlApp.Quit(); 
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


