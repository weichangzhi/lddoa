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
	//��m_ExlApp���󴴽�Excel2003���� 

	if(!m_ExlApp.CreateDispatch("Excel.Application",NULL)) 
	{ 
		AfxMessageBox("����Excel����ʧ��!"); 
		return; 
	} 

	//����Ϊ�ɼ� 
	m_ExlApp.SetVisible(TRUE); 

	///////////////////����õ�Ӧ�ó������ڵ�·��/////////////////// 
	CString theAppPath,theAppName; 
	char Path[MAX_PATH]; 

	GetModuleFileName(NULL,Path,MAX_PATH);//�õ�Ӧ�ó����ȫ·�� 
	theAppPath=(CString)Path; 

	theAppName=AfxGetApp()->m_pszAppName; 
	theAppName+=".exe"; 

	//�������ļ���ȥ�� 
	int length1,length2; 

	length1=theAppPath.GetLength(); 
	length2=theAppName.GetLength(); 

	theAppPath.Delete(length1-length2,length2); 
	CString TempPath=""; 
	TempPath=theAppPath+filename;//EXCELģ���·�� 
//	CFile file;
//	file.Open(TempPath,CFile::modeCreate|CFile::modeWrite);
//	file.Close();


	m_ExlBooks.AttachDispatch(m_ExlApp.GetWorkbooks(),TRUE); 

	//m_ExlBook.AttachDispatch(m_ExlBooks.Add((_variant_t)TempPath),TRUE);//����EXCELģ�� 
	m_ExlBook.AttachDispatch(m_ExlBooks.Add(covOptional),TRUE);//����EXCELģ�� 

	m_ExlSheets.AttachDispatch(m_ExlBook.GetSheets(),TRUE);//����Sheetҳ�� 

	//����µ�Sheetҳ�� 
	m_ExlSheets.Add(vtMissing,vtMissing,_variant_t((long)1),vtMissing); 

	//ɾ���ڶ���Sheetҳ�� 
	m_ExlSheet.AttachDispatch(m_ExlSheets.GetItem(_variant_t((long)2)),TRUE); 
	m_ExlSheet.Delete(); 

	//�ѵ�һ��Sheetҳ������ָı�ΪTestSheet 
	m_ExlSheet.AttachDispatch(m_ExlSheets.GetItem(_variant_t((long)1)),TRUE); 
	m_ExlSheet.SetName("��������"); 


	////////���ñ������//////// 

	m_ExlRge.AttachDispatch(m_ExlSheet.GetCells(),TRUE);//�������е�Ԫ�� 

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
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("P2"), _variant_t("P100")));//��ȡ���е���"P"����
	m_ExlRge.SetColumnWidth(_variant_t((long)40));  //�����п�Ϊ100

	m_ExlRge.AttachDispatch(m_ExlSheet.GetUsedRange());//������ʹ�õĵ�Ԫ�� 

//	m_ExlRge.SetWrapText(_variant_t((long)1));//���õ�Ԫ���ڵ��ı�Ϊ�Զ����� 

	//�����뷽ʽΪˮƽ��ֱ���� 
	//ˮƽ���룺Ĭ�ϣ�1,���У�-4108,��-4131,�ң�-4152 
	//��ֱ���룺Ĭ�ϣ�2,���У�-4108,��-4160,�ң�-4107 
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4131)); 
	m_ExlRge.SetVerticalAlignment(_variant_t((long)-4160)); 

	///////������������塢�ֺż���ɫ////// 

	Font ft; 

	ft.AttachDispatch(m_ExlRge.GetFont()); 

	ft.SetName(_variant_t("����"));//���� 
	ft.SetColorIndex(_variant_t((long)11));//�ֵ���ɫ 
	ft.SetSize(_variant_t((long)12));//�ֺ� 

	///////////���ñ������弰��ɫ////////// 

//	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("D1"))); 

//	ft.AttachDispatch(m_ExlRge.GetFont()); 

//	ft.SetBold(_variant_t((long)1));//���� 
//	ft.SetSize(_variant_t((long)13)); 
//	ft.SetColorIndex(_variant_t((long)2)); 

//	CellFormat cf; 
//	cf.AttachDispatch(m_ExlRge.GetCells()); 

	//////////////���õ�ɫ///////////////// 

//	Interior it; 

//	it.AttachDispatch(m_ExlRge.GetInterior()); 

//	it.SetColorIndex(_variant_t((long)11));//�����ɫ 

/*	////������ݵĵ�ɫ//// 

//	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"),_variant_t("D5"))); 

//	it.AttachDispatch(m_ExlRge.GetInterior()); 

//	it.SetColorIndex(_variant_t((long)15)); 


	//////////////Ϊ������ñ߿�///////////// 

	Range UnitRge; 
	CString CellName; 

	for(i=1;i<=4;i++) 
	{ 
		for(int j=1;j<=4;j++) 
		{ 
			CellName.Format("%c%d",j+64,i);//��Ԫ������� 

			UnitRge.AttachDispatch(m_ExlRge.GetRange(_variant_t(CellName),_variant_t(CellName)));//���ص�Ԫ�� 

			//LineStyle=���� Weight=�߿� ColorIndex=�ߵ���ɫ(-4105Ϊ�Զ�) 
			UnitRge.BorderAround(_variant_t((long)1),_variant_t((long)2),_variant_t((long)-4105),vtMissing);//���ñ߿� 
		} 
	} 
	*/
	Range cols;
	cols=m_ExlRge.GetEntireColumn();//ѡ��A:A�У����ÿ��Ϊ�Զ���Ӧ
	cols.AutoFit();
	m_ExlApp.SetVisible(TRUE);//��ʾExcel��񣬲�����״̬Ϊ�û��ɿ���
	m_ExlApp.SetUserControl(TRUE);

	m_ExlBook.SaveAs(COleVariant(TempPath),covOptional,
	covOptional,covOptional,
	covOptional,covOptional,(long)0,covOptional,covOptional,covOptional,
	covOptional,covOptional);

	//�ͷŶ����൱��Ҫ���� 
	m_ExlRge.ReleaseDispatch(); 
	m_ExlSheet.ReleaseDispatch(); 
	m_ExlSheets.ReleaseDispatch(); 
	m_ExlBook.ReleaseDispatch(); 
	m_ExlBooks.ReleaseDispatch(); 
	//m_ExlAppһ��Ҫ�ͷţ������������󻹻���һ��Excel����פ�����ڴ��У����ҳ����ظ����е�ʱ������ 
	m_ExlApp.ReleaseDispatch(); 

	//�˳�����
	m_ExlApp.Quit(); 
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


