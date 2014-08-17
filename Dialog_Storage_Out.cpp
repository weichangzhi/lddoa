// Dialog_Storage_Out.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_Storage_Out.h"
#include "Dialog_progress.h"
#include "Dialog_Storage_Left2.h"
#include "Dialog_Storage_ID.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_Out dialog


Dialog_Storage_Out::Dialog_Storage_Out(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_Storage_Out::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_Storage_Out)
	m_timeCurrent = 0;
	m_timePayment = 0;
	m_StorageInID = _T("");
	m_Digest = _T("");
	m_row = 0;
	m_column = 0;
	m_strDepartment = _T("");
	m_strOperator = _T("");
	m_strProvider = _T("");
	m_strStorage = _T("");
	//}}AFX_DATA_INIT
}


void Dialog_Storage_Out::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_Storage_Out)
	DDX_Control(pDX, IDC_COMBO_STORAGE, m_comStorage);
	DDX_Control(pDX, IDC_COMBO_PROVIDER, m_comProvider);
	DDX_Control(pDX, IDC_COMBO_OPERATOR, m_comOperator);
	DDX_Control(pDX, IDC_COMBO_DEPARTMENT, m_comDepartment);
	DDX_Control(pDX, IDC_EXCEL, m_btexcel);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_btsave);
	DDX_Control(pDX, IDC_BUTTON_QUIT, m_btquit);
	DDX_Control(pDX, IDC_BUTTON_QUERY, m_btquery);
	DDX_Control(pDX, IDC_BUTTON_PRINT, m_btprint);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_btnew);
	DDX_Control(pDX, IDC_BUTTON_MODIFY, m_btmodify);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_CURRENT, m_timeCurrent);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_PAYMENT, m_timePayment);
	DDX_Control(pDX, IDC_LIST_TOTAL, m_listTotal);
	DDX_Control(pDX, IDC_LIST_STORAGE_IN, m_listStorageIn);
	DDX_Text(pDX, IDC_EDIT_STORAGE_IN_ID, m_StorageInID);
	DDX_Text(pDX, IDC_RICHEDIT_DIGEST, m_Digest);
	DDX_CBString(pDX, IDC_COMBO_DEPARTMENT, m_strDepartment);
	DDX_CBString(pDX, IDC_COMBO_OPERATOR, m_strOperator);
	DDX_CBString(pDX, IDC_COMBO_PROVIDER, m_strProvider);
	DDX_CBString(pDX, IDC_COMBO_STORAGE, m_strStorage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_Storage_Out, CDialog)
	//{{AFX_MSG_MAP(Dialog_Storage_Out)
	ON_BN_CLICKED(IDC_EXCEL, OnExcel)
	ON_BN_CLICKED(IDC_BUTTON_NEW, OnButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnButtonPrint)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, OnButtonQuit)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnButtonModify)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_TOTAL, OnColumnclickListTotal)
	ON_NOTIFY(NM_CLICK, IDC_LIST_STORAGE_IN, OnClickListStorageIn)
	ON_COMMAND(IDM_BUY_QUERY, OnBuyQuery)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, OnButtonQuery)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_Out message handlers

BOOL Dialog_Storage_Out::GetConfig()
{
	CString strpathini="";
	::GetCurrentDirectory(_MAX_PATH,strpathini.GetBuffer(_MAX_PATH));
	strpathini.ReleaseBuffer();
	strpathini = strpathini + "\\" + CONFIGINI_STORAGE;
	//char buf[_MAX_PATH] = {0};
	int indexid = 0;
	indexid = ::GetPrivateProfileInt("StorageID","OutID",0,strpathini);
	indexid++;
	m_StorageInID.Format("CK-%04d-%02d-%02d-%04d",m_timeCurrent.GetYear(),m_timeCurrent.GetMonth(),m_timeCurrent.GetDay(),indexid);
	CString strTemp;
	strTemp.Format("%d",indexid);
	::WritePrivateProfileString("StorageID","OutID",strTemp,strpathini);

	int nCount = 0, i = 0;
	CString strtemp1;

	m_strDepartment = g_department;
	m_comDepartment.ResetContent();
	nCount = ::GetPrivateProfileInt("Department","Count",1,strpathini);
	for(i=0;i<nCount;i++)
	{
		strTemp.Format("%d",i+1);
		strTemp="Department"+strTemp;
		::GetPrivateProfileString("Department",strTemp,"", strtemp1.GetBuffer(MAX_PATH),MAX_PATH,strpathini);
		m_comDepartment.InsertString(i,strtemp1);
	}

	m_strStorage = "";
	m_comStorage.ResetContent();
	nCount = ::GetPrivateProfileInt("Storage","Count",1,strpathini);
	for(i=0;i<nCount;i++)
	{
		strTemp.Format("%d",i+1);
		strTemp="Storage"+strTemp;
		::GetPrivateProfileString("Storage",strTemp,"", strtemp1.GetBuffer(MAX_PATH),MAX_PATH,strpathini);
		m_comStorage.InsertString(i,strtemp1);
	}
	m_comStorage.SetCurSel(-1);

	m_strProvider = "";
	m_comProvider.ResetContent();
	nCount = ::GetPrivateProfileInt("receiver","Count",1,strpathini);
	for(i=0;i<nCount;i++)
	{
		strTemp.Format("%d",i+1);
		strTemp="receiver"+strTemp;
		::GetPrivateProfileString("receiver",strTemp,"", strtemp1.GetBuffer(MAX_PATH),MAX_PATH,strpathini);
		m_comProvider.InsertString(i,strtemp1);
	}
	m_comProvider.SetCurSel(-1);

	m_strOperator = g_user;
	m_comOperator.ResetContent();
	nCount = ::GetPrivateProfileInt("Operator","Count",1,strpathini);
	for(i=0;i<nCount;i++)
	{
		strTemp.Format("%d",i+1);
		strTemp="Operator"+strTemp;
		::GetPrivateProfileString("Operator",strTemp,"", strtemp1.GetBuffer(MAX_PATH),MAX_PATH,strpathini);
		m_comOperator.InsertString(i,strtemp1);
	}
	
	return TRUE;
}

BOOL Dialog_Storage_Out::SetConfig()
{
	CString strpathini="";
	::GetCurrentDirectory(_MAX_PATH,strpathini.GetBuffer(_MAX_PATH));
	strpathini.ReleaseBuffer();
	strpathini = strpathini + "\\" + CONFIGINI_STORAGE;

	int nCount = 0, cursel = 0, i = 0 ;
	CString strTemp,strTemp1;

	cursel = m_comDepartment.GetCurSel();
	if(cursel==-1 && (!m_strDepartment.IsEmpty()))
	{
		nCount = ::GetPrivateProfileInt("Department","Count",1,strpathini);
		for(i=0;i<nCount;i++)
		{
			strTemp.Format("%d",i+1);
			strTemp="Department"+strTemp;
			::GetPrivateProfileString("Department",strTemp,"", strTemp1.GetBuffer(MAX_PATH),MAX_PATH,strpathini);
			if(m_strDepartment.Compare(strTemp1)==0)
				break;
		}
		if(i==nCount)
		{
			strTemp1.Format("Department%d",nCount+1);
			::WritePrivateProfileString("Department",strTemp1,m_strDepartment,strpathini);
			strTemp.Format("%d",nCount+1);
			::WritePrivateProfileString("Department","Count",strTemp,strpathini);
		}
	}

	cursel = m_comStorage.GetCurSel();
	if(cursel==-1 && (!m_strStorage.IsEmpty()))
	{
		nCount = ::GetPrivateProfileInt("Storage","Count",1,strpathini);
		for(i=0;i<nCount;i++)
		{
			strTemp.Format("%d",i+1);
			strTemp="Storage"+strTemp;
			::GetPrivateProfileString("Storage",strTemp,"", strTemp1.GetBuffer(MAX_PATH),MAX_PATH,strpathini);
			if(m_strStorage.Compare(strTemp1)==0)
				break;
		}
		if(i==nCount)
		{
			strTemp1.Format("Storage%d",nCount+1);
			::WritePrivateProfileString("Storage",strTemp1,m_strStorage,strpathini);
			strTemp.Format("%d",nCount+1);
			::WritePrivateProfileString("Storage","Count",strTemp,strpathini);
		}
	}

	cursel = m_comProvider.GetCurSel();
	if(cursel==-1 && (!m_strProvider.IsEmpty()))
	{
		nCount = ::GetPrivateProfileInt("receiver","Count",1,strpathini);
		for(i=0;i<nCount;i++)
		{
			strTemp.Format("%d",i+1);
			strTemp="receiver"+strTemp;
			::GetPrivateProfileString("receiver",strTemp,"", strTemp1.GetBuffer(MAX_PATH),MAX_PATH,strpathini);
			if(m_strProvider.Compare(strTemp1)==0)
				break;
		}
		if(i==nCount)
		{
			strTemp1.Format("receiver%d",nCount+1);
			::WritePrivateProfileString("receiver",strTemp1,m_strProvider,strpathini);
			strTemp.Format("%d",nCount+1);
			::WritePrivateProfileString("receiver","Count",strTemp,strpathini);
		}
	}

	cursel = m_comOperator.GetCurSel();
	if(cursel==-1 && (!m_strOperator.IsEmpty()))
	{
		nCount = ::GetPrivateProfileInt("Operator","Count",1,strpathini);
		for(i=0;i<nCount;i++)
		{
			strTemp.Format("%d",i+1);
			strTemp="Operator"+strTemp;
			::GetPrivateProfileString("Operator",strTemp,"", strTemp1.GetBuffer(MAX_PATH),MAX_PATH,strpathini);
			if(m_strOperator.Compare(strTemp1)==0)
				break;
		}
		if(i==nCount)
		{
			strTemp1.Format("Operator%d",nCount+1);
			::WritePrivateProfileString("Operator",strTemp1,m_strOperator,strpathini);
			strTemp.Format("%d",nCount+1);
			::WritePrivateProfileString("Operator","Count",strTemp,strpathini);
		}
	}

	return TRUE;
}

BOOL Dialog_Storage_Out::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CTime time1 = CTime::GetCurrentTime();
	m_timeCurrent = time1;
	m_timePayment = time1;
	GetConfig();
	m_strOperator = g_user;
	m_strDepartment = g_department;
		
	m_listStorageIn.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listStorageIn.InsertColumn(0, _T("�к�"), LVCFMT_LEFT,60);
	m_listStorageIn.InsertColumn(1, _T("�ֿ���"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(2, _T("�ֿ�ȫ��"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(3, _T("SCB"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(4, _T("����"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(5, _T("����"), LVCFMT_LEFT,80);
	m_listStorageIn.InsertColumn(6, _T("��λ"), LVCFMT_LEFT,80);
	m_listStorageIn.InsertColumn(7, _T("����"), LVCFMT_LEFT,80);
	m_listStorageIn.InsertColumn(8, _T("���"), LVCFMT_LEFT,100);

	m_listTotal.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listTotal.InsertColumn(0, _T("�ϼ�"), LVCFMT_LEFT,60);
	m_listTotal.InsertColumn(1, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(2, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(3, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(4, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(5, _T(""), LVCFMT_LEFT,80);
	m_listTotal.InsertColumn(6, _T(""), LVCFMT_LEFT,80);
	m_listTotal.InsertColumn(7, _T(""), LVCFMT_LEFT,80);
	m_listTotal.InsertColumn(8, _T(""), LVCFMT_LEFT,100);

	CString strindex ;
	int index = 0;
	while(index<15)
	{
		strindex.Format("%d",index+1);
		m_listStorageIn.InsertItem(index,strindex);
		if(index%2==0)
			m_listStorageIn.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));//��ɫ
		index++;
	}

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_Storage_Out::OnExcel() 
{
	UpdateData();
	CString strcurrent,strpayment;
	strcurrent.Format("%04d-%02d-%02d",m_timeCurrent.GetYear(),m_timeCurrent.GetMonth(),m_timeCurrent.GetDay());
	strpayment.Format("%04d-%02d-%02d",m_timePayment.GetYear(),m_timePayment.GetMonth(),m_timePayment.GetDay());
	
	CString filename ;
	filename.Format("���ⵥ-%s.xls",m_StorageInID);
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
	CString strtmp;
	strtmp.Format("���ⵥ");
	m_ExlSheet.SetName(strtmp); 

	m_ExlRge.AttachDispatch(m_ExlSheet.GetCells(),TRUE);//�������е�Ԫ��
	m_ExlRge.SetNumberFormatLocal(COleVariant("@")); 

	//�ϲ���Ԫ��
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("I1")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"),_variant_t("I2")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A3"),_variant_t("I3")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A4"),_variant_t("I4")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A5"),_variant_t("I5")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));

	////////���ñ������//////// 
	CString strtmp1;

	m_ExlRge.AttachDispatch(m_ExlSheet.GetCells(),TRUE);//�������е�Ԫ�� 
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(1)),_variant_t(strtmp));
	strtmp1.Format("�Ƶ�����:%s       .",strcurrent);
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(1)),_variant_t(strtmp1));
	strtmp1.Format("���ݱ��:%s",m_StorageInID);
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(1)),_variant_t(strtmp1));
	strtmp1.Format("    ȡ����:%s    ������:%s    ����:%s    ȡ������:%s",m_strProvider,m_strOperator,m_strDepartment,strpayment);
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(1)),_variant_t(strtmp1));
	strtmp1.Format("    �ֿ�:%s    ժҪ:%s",m_strStorage,m_Digest);
	m_ExlRge.SetItem(_variant_t((long)(5)),_variant_t((long)(1)),_variant_t(strtmp1));

	m_ExlRge.SetItem(_variant_t((long)(6)),_variant_t((long)(1)),_variant_t("�к�"));
	m_ExlRge.SetItem(_variant_t((long)(6)),_variant_t((long)(2)),_variant_t("�ֿ���"));
	m_ExlRge.SetItem(_variant_t((long)(6)),_variant_t((long)(3)),_variant_t("�ֿ�ȫ��"));
	m_ExlRge.SetItem(_variant_t((long)(6)),_variant_t((long)(4)),_variant_t("SCB"));
	m_ExlRge.SetItem(_variant_t((long)(6)),_variant_t((long)(5)),_variant_t("����"));
	m_ExlRge.SetItem(_variant_t((long)(6)),_variant_t((long)(6)),_variant_t("����"));
	m_ExlRge.SetItem(_variant_t((long)(6)),_variant_t((long)(7)),_variant_t("��λ"));
	m_ExlRge.SetItem(_variant_t((long)(6)),_variant_t((long)(8)),_variant_t("����"));
	m_ExlRge.SetItem(_variant_t((long)(6)),_variant_t((long)(9)),_variant_t("���"));

	int i = 0, j = 0;
	int total = 0;
	float money = 0;
	for(i=0;i<15;i++)
		for(j=0;j<9;j++)
		{
			m_ExlRge.SetItem(_variant_t((long)(i+7)),_variant_t((long)(j+1)),_variant_t(m_listStorageIn.GetItemText(i,j)));
			if(j==5)
				total += atoi(m_listStorageIn.GetItemText(i,5));
			if(j==8)
				money += atoi(m_listStorageIn.GetItemText(i,8));

		}

	m_ExlRge.SetItem(_variant_t((long)(22)),_variant_t((long)(1)),_variant_t("�ϼ�"));
	strtmp1.Format("%d",total);
	m_ExlRge.SetItem(_variant_t((long)(22)),_variant_t((long)(6)),_variant_t(strtmp1));
	strtmp1.Format("%0.2f",money);
	m_ExlRge.SetItem(_variant_t((long)(22)),_variant_t((long)(9)),_variant_t(strtmp1));
	
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A6"), _variant_t("I6")));//��ȡ���е���"P"����
	m_ExlRge.SetColumnWidth(_variant_t((long)9));  //�����п�Ϊ100

	m_ExlRge.AttachDispatch(m_ExlSheet.GetUsedRange());//������ʹ�õĵ�Ԫ�� 
	m_ExlRge.SetWrapText(_variant_t((long)1));//���õ�Ԫ���ڵ��ı�Ϊ�Զ����� 
	//m_ExlRge.SetColumnWidth(_variant_t((long)13));  //�����п�Ϊ100
	m_ExlRge.SetRowHeight(_variant_t((long)30	));

	//�����뷽ʽΪˮƽ��ֱ���� 
	//ˮƽ���룺Ĭ�ϣ�1,���У�-4108,��-4131,�ң�-4152 
	//��ֱ���룺Ĭ�ϣ�2,���У�-4108,��-4160,�ң�-4107 
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4131));
	m_ExlRge.SetVerticalAlignment(_variant_t((long)-4108));

	///////������������塢�ֺż���ɫ////// 

	Font ft; 

	ft.AttachDispatch(m_ExlRge.GetFont()); 

	ft.SetName(_variant_t("����"));//���� 
	//ft.SetColorIndex(_variant_t((long)11));//�ֵ���ɫ 
	ft.SetColor( _variant_t((long) RGB(32, 32, 32) ) );
	ft.SetSize(_variant_t((long)12));//�ֺ� 

	///////////���ñ������弰��ɫ////////// 

	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("I1"))); 

	ft.AttachDispatch(m_ExlRge.GetFont()); 
	//ft.SetBold(_variant_t((long)0));//���� 
	ft.SetSize(_variant_t((long)15)); 
	//ft.SetColorIndex(_variant_t((long)2)); 

	//CellFormat cf; 
	//cf.AttachDispatch(m_ExlRge.GetCells()); 

	//����
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("I1")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4108));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"),_variant_t("I2")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4152));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A3"),_variant_t("I3")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4152));
	ft.AttachDispatch(m_ExlRge.GetFont()); 
	//ft.SetBold(_variant_t((long)0));//���� 
/*	ft.SetSize(_variant_t((long)14)); 
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A7"),_variant_t("F7")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4108));
	ft.AttachDispatch(m_ExlRge.GetFont()); 
	//ft.SetBold(_variant_t((long)0));//���� 
	ft.SetSize(_variant_t((long)14)); 
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A14"),_variant_t("F14")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4108));
	ft.AttachDispatch(m_ExlRge.GetFont()); 
	//ft.SetBold(_variant_t((long)0));//���� 
	ft.SetSize(_variant_t((long)14)); 
	*/

	//////////////���õ�ɫ///////////////// 

//	Interior it; 
//	it.AttachDispatch(m_ExlRge.GetInterior()); 
//	it.SetColorIndex(_variant_t((long)11));//�����ɫ 

	////������ݵĵ�ɫ//// 

//	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"),_variant_t("D5"))); 

//	it.AttachDispatch(m_ExlRge.GetInterior()); 

//	it.SetColorIndex(_variant_t((long)15)); 


	//////////////Ϊ������ñ߿�///////////// 

	Range UnitRge; 
	CString CellName; 
	for(i=6;i<=22;i++) 
	{
		//if((i==1)||(i==2)||(i==7)||(i==14))
		//	continue;
		for(int j=1;j<=9;j++) 
		{
			CellName.Format("%c%d",j+64,i);//��Ԫ�������
			UnitRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t(CellName),_variant_t(CellName)));//���ص�Ԫ��
			//LineStyle=���� Weight=�߿� ColorIndex=�ߵ���ɫ(-4105Ϊ�Զ�)
			UnitRge.BorderAround(_variant_t((long)1),_variant_t((long)2),_variant_t((long)-4105),vtMissing);//���ñ߿�
		}
	} 
//	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("B13"),_variant_t("B13")));
//	m_ExlRge.SetRowHeight(COleVariant((short)120));
	
	//Range cols;
	//cols=m_ExlRge.GetEntireColumn();//ѡ��A:A�У����ÿ��Ϊ�Զ���Ӧ
	//cols.AutoFit();
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

void Dialog_Storage_Out::ResetStorageOut()
{
	m_Digest = "";
	CTime time1 = CTime::GetCurrentTime();
	m_timeCurrent = time1;
	m_timePayment = time1;
	CString strindex;
	for(int i=0;i<15;i++)
	{
		strindex.Format("%d",i+1);
		m_listStorageIn.DeleteItem(i);
		m_listStorageIn.InsertItem(i,strindex);
	}
	m_listTotal.DeleteColumn(5);
	m_listTotal.InsertColumn(5, _T(""), LVCFMT_LEFT,80);
	m_listTotal.DeleteColumn(8);
	m_listTotal.InsertColumn(8, _T(""), LVCFMT_LEFT,100);
}

void Dialog_Storage_Out::OnButtonNew() 
{
	ResetStorageOut();
	GetConfig();			
	UpdateData(FALSE);
}

void Dialog_Storage_Out::SetPreviewDlg(Dialog_Storage_Print *PreviewDlg)
{
	UpdateData();
	CString	strCurrent;
	CString	strPayment;
	strCurrent.Format("%04d-%02d-%02d",m_timeCurrent.GetYear(),m_timeCurrent.GetMonth(),m_timeCurrent.GetDay());
	strPayment.Format("%04d-%02d-%02d",m_timePayment.GetYear(),m_timePayment.GetMonth(),m_timePayment.GetDay());
	PreviewDlg->m_StorageInID = m_StorageInID;
	PreviewDlg->m_Digest = "";
	PreviewDlg->m_strDepartment = m_strDepartment;
	PreviewDlg->m_strOperator = m_strOperator;
	PreviewDlg->m_strProvider = m_strProvider;
	PreviewDlg->m_strStorage = m_strStorage;
	PreviewDlg->m_strCurrent = strCurrent;
	PreviewDlg->m_strPayment = strPayment;
	PreviewDlg->m_list = &m_listStorageIn;
}

void Dialog_Storage_Out::OnButtonPrint() 
{
	Dialog_Storage_Print PreviewDlg;
	SetPreviewDlg(&PreviewDlg);
	CPrintDialog m_printdlg(false);
	if (m_printdlg.DoModal()==IDOK)
	{
		CDC dc1;		
		dc1.Attach(m_printdlg.GetPrinterDC());
		int screenx = dc1.GetDeviceCaps(LOGPIXELSX);
		int screeny = dc1.GetDeviceCaps(LOGPIXELSY);
		char log[256] = {0};
		sprintf(log,"OnButtonPrint \t%s,%d:print [%dx%d]",__FILE__,__LINE__,screenx,screeny);
		writelog(log);
		PreviewDlg.screenx = screenx;
		PreviewDlg.screeny = screeny;
		int leftmargin;
		leftmargin = dc1.GetDeviceCaps(PHYSICALOFFSETX);
		CRect m_rect(-leftmargin,0,dc1.GetDeviceCaps(PHYSICALWIDTH)-leftmargin,dc1.GetDeviceCaps(PHYSICALHEIGHT)) ;	
		char log1[256] = {0};
		sprintf(log1,"OnButtonPrint \t%s,%d:leftmargin=%d rect [%dx%d, %dx%d]",__FILE__,__LINE__,
			leftmargin,m_rect.left,m_rect.top,m_rect.right,m_rect.bottom);
		writelog(log1);
		PreviewDlg.DrawReport(m_rect,&dc1,TRUE,FALSE);
	}
}

void Dialog_Storage_Out::OnButtonQuit() 
{
	ResetStorageOut();
	GetConfig();			
	UpdateData(FALSE);
}

void Dialog_Storage_Out::OnButtonSave() 
{
	UpdateData();
	int count = m_listStorageIn.GetItemCount();
	int i=0;
	CString strnumber;
	CString strprice;
	CString strmoney;
	CString strscb,stritemname;
	for(i=0;i<count;i++)
	{
		strscb = m_listStorageIn.GetItemText(i,3);
		stritemname = m_listStorageIn.GetItemText(i,4);
		if(strscb.IsEmpty()&& stritemname.IsEmpty())
			continue;
		strnumber = m_listStorageIn.GetItemText(i,5);
		if(strnumber.IsEmpty())
		{
			MessageBox("��������Ϊ�գ�������","��ʾ",MB_OK);
			return;
		}
		else
		{
			if(!IsInt(strnumber))
			{
				MessageBox("�����������Ϊ����������������","��ʾ",MB_OK);
				return;
			}
			if(atoi(strnumber)<=0)
			{
				MessageBox("��������Ƿ�������������","��ʾ",MB_OK);
				return;
			}
		}
		strprice = m_listStorageIn.GetItemText(i,7);
		if(!(strprice.IsEmpty()))
		{
			if(!IsNum(strprice))
			{
				MessageBox("�����������Ϊ���֣�����������","��ʾ",MB_OK);
				return;
			}
		}
		strmoney = m_listStorageIn.GetItemText(i,8);
		if(!(strmoney.IsEmpty()))
		{
			if(!IsNum(strmoney))
			{
				MessageBox("����������Ϊ���֣�����������","��ʾ",MB_OK);
				return;
			}
		}
	}
	
	CString strtimepayment;
	strtimepayment.Format("%04d-%02d-%02d",m_timePayment.GetYear(),m_timePayment.GetMonth(),m_timePayment.GetDay());
	CString strtimecurrent;
	strtimecurrent.Format("%04d-%02d-%02d",m_timeCurrent.GetYear(),m_timeCurrent.GetMonth(),m_timeCurrent.GetDay());

	SetConfig();
	Dialog_progress *dlgpro;
	dlgpro=new Dialog_progress(); 
	dlgpro->Create(IDD_DIALOG_PROGRESS);
	if(g_openprocess)
		dlgpro->ShowWindow(SW_SHOW);
	else
		dlgpro->ShowWindow(SW_HIDE);

	CString sql;
	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	mysql_init(&myCont);
	if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
	{
		dlgpro->setpos(500);
		mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
		sql.Format("select * from storage_out_baseinfo,storage_out_item where storage_out_baseinfo.storage_out_id=\"%s\" and storage_out_item.storage_out_id=\"%s\" ",m_StorageInID,m_StorageInID);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			dlgpro->endpos();
			return;
		}
		dlgpro->setpos(600);
		result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
		if(result)
		{
			unsigned __int64 num = mysql_num_rows(result);//����
			if(num>=1)
			{
				MessageBox("�˵��ݱ���Ѵ��ڣ����޸�","��ʾ",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_STORAGE_IN_ID)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_STORAGE_IN_ID))->SetSel(0, -1);
				mysql_close(&myCont);//�Ͽ�����
				dlgpro->endpos();
				return;
			}
			else
			{//������¼
				dlgpro->setpos(700);
				int count = m_listStorageIn.GetItemCount();
				int i=0,j=0;
				for(i=0;i<count;i++)
				{
					CString strscb = m_listStorageIn.GetItemText(i,3);
					CString stritemname = m_listStorageIn.GetItemText(i,4);
					if(strscb.IsEmpty()&& stritemname.IsEmpty())
						continue;
					CString storage_id = m_listStorageIn.GetItemText(i,1);
					CString storage_name = m_listStorageIn.GetItemText(i,2);
					CString SCB = m_listStorageIn.GetItemText(i,3);
					CString item_name = m_listStorageIn.GetItemText(i,4);
					int     item_number = atoi(m_listStorageIn.GetItemText(i,5));
					CString item_unit = m_listStorageIn.GetItemText(i,6);
					float   item_price = atof(m_listStorageIn.GetItemText(i,7));
					float   item_money = atof(m_listStorageIn.GetItemText(i,8));

					CTime time = CTime::GetCurrentTime();
					CString curenttime;
					CString strsql ;
					strsql.Format("select now()");
					if(mysql_query(&myCont,strsql)!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("���ݿ����(%s)",error);
						MessageBox(str,"��ʾ",MB_OK);
						mysql_close(&myCont);//�Ͽ�����
						dlgpro->endpos();
						return;
					}
					result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
					if(result)
					{
						sql_row=mysql_fetch_row(result);
						curenttime = sql_row[0];
					}
					else
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("���ݿ����(%s)",error);
						MessageBox(str,"��ʾ",MB_OK);
						mysql_close(&myCont);//�Ͽ�����
						dlgpro->endpos();
						return;
					}
					//left
					sql.Format("select item_number,item_price from storage_left where scb=\"%s\" ",SCB);
					if(mysql_query(&myCont,sql)!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("���ݿ����(%s)",error);
						MessageBox(str,"��ʾ",MB_OK);
						mysql_close(&myCont);//�Ͽ�����
						dlgpro->endpos();
						return;
					}
					result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
					if(result)
					{
						unsigned __int64 num = mysql_num_rows(result);//����
						if(num>=1)
						{
							//�޸ļ�¼	
							float oldprice = 0;
							int	  oldnumber = 0;
							float oldmoney = 0;
							while(sql_row=mysql_fetch_row(result))//��ȡ���������
							{
								if(sql_row[0]!=NULL)
									oldnumber = atoi(sql_row[0]);
								if(sql_row[1]!=NULL)
									oldprice = atof(sql_row[1]);					
							}//while
							if(oldnumber<item_number)
							{
								CString str;
								str.Format("%s �������.",item_name);
								MessageBox(str,"��ʾ",MB_OK);
								mysql_close(&myCont);//�Ͽ�����
								dlgpro->endpos();
								return;
							}
							oldnumber -= (item_number);
							oldmoney = oldnumber* (oldprice);
							sql.Format("update storage_left set item_number=%d,item_money=%f,item_time=\"%s\" where scb=\"%s\" ",
								oldnumber,oldmoney,curenttime,SCB);
							int ret = mysql_query(&myCont,sql);
							if(ret!= 0)
							{
								const char *error = mysql_error(&myCont);
								CString str;
								str.Format("���ݿ����(%s)",error);
								MessageBox(str,"��ʾ",MB_OK);
								mysql_close(&myCont);//�Ͽ�����
								dlgpro->endpos();
								return;
							}
						}
						else
						{//
							CString str;
							str.Format("����޴���Ʒ��%s ",item_name);
							MessageBox(str,"��ʾ",MB_OK);
							mysql_close(&myCont);//�Ͽ�����
							dlgpro->endpos();
							return;
						}
					}
					else
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("���ݿ����(%s)",error);
						MessageBox(str,"��ʾ",MB_OK);
						mysql_close(&myCont);//�Ͽ�����
						dlgpro->endpos();
						return;
					}
					//item
					sql.Format("insert into storage_out_item values (%d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",%0.2f,%0.2f)",
					0,m_StorageInID,storage_id,storage_name,SCB,item_name,(item_number),item_unit,(item_price),(item_money));
					if(mysql_query(&myCont,sql)!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("���ݿ����(%s)",error);
						MessageBox(str,"��ʾ",MB_OK);
						mysql_close(&myCont);//�Ͽ�����
						dlgpro->endpos();
						return;
					}
					
				}//for
				dlgpro->setpos(900);
				sql.Format("insert into storage_out_baseinfo values (\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\")",
					m_StorageInID,strtimecurrent,m_strProvider,m_strOperator,m_strDepartment,strtimepayment,m_strStorage,m_Digest);
				if(mysql_query(&myCont,sql)!= 0)
				{
					const char *error = mysql_error(&myCont);
					CString str;
					str.Format("���ݿ����(%s)",error);
					MessageBox(str,"��ʾ",MB_OK);
					mysql_close(&myCont);//�Ͽ�����
					dlgpro->endpos();
					return;
				}
				dlgpro->setpos(980);
			}
		}
		else
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			dlgpro->endpos();
			return;
		}		
	}
	else
	{
		const char *error = mysql_error(&myCont);
		CString str;
		str.Format("���ݿ����(%s)",error);
		MessageBox(str,"��ʾ",MB_OK);
		mysql_close(&myCont);//�Ͽ�����
		dlgpro->endpos();
		return;
	}
	if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
	mysql_close(&myCont);//�Ͽ�����
	dlgpro->endpos();
	MessageBox("���ⵥ����ɹ�","��ʾ",MB_OK);
}

BOOL Dialog_Storage_Out::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN) 
	{  
		switch(pMsg->wParam) 
		{  
		case VK_RETURN: //�س�  
			return TRUE;  
		case VK_ESCAPE: //ESC  
			return TRUE;  
		}  
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void Dialog_Storage_Out::OnButtonModify() 
{
	Dialog_Storage_Left2 dlg;
	dlg.DoModal();
	
}

void Dialog_Storage_Out::OnColumnclickListTotal(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int number = 0;
	float money = 0;
	CString strtmp;
	for(int i=0;i<15;i++)
	{
		number += atoi(m_listStorageIn.GetItemText(i,5));
		money += atof(m_listStorageIn.GetItemText(i,8));
	}
	strtmp.Format("%d",number);
	m_listTotal.DeleteColumn(5);
	m_listTotal.InsertColumn(5, strtmp, LVCFMT_LEFT,80);


	strtmp.Format("%0.2f",money);
	m_listTotal.DeleteColumn(8);
	m_listTotal.InsertColumn(8, strtmp, LVCFMT_LEFT,100);
	
	*pResult = 0;
}

void Dialog_Storage_Out::OnClickListStorageIn(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int number = 0;
	float money = 0;
	CString strtmp;
	for(int i=0;i<15;i++)
	{
		number += atoi(m_listStorageIn.GetItemText(i,5));
		money += atof(m_listStorageIn.GetItemText(i,8));
	}
	strtmp.Format("%d",number);
	m_listTotal.DeleteColumn(5);
	m_listTotal.InsertColumn(5, strtmp, LVCFMT_LEFT,80);

	strtmp.Format("%0.2f",money);
	m_listTotal.DeleteColumn(8);
	m_listTotal.InsertColumn(8, strtmp, LVCFMT_LEFT,100);
	
	*pResult = 0;
}

void Dialog_Storage_Out::OnBuyQuery() 
{
		
}

void Dialog_Storage_Out::OnButtonQuery() 
{
	ResetStorageOut();
	GetConfig();			
	UpdateData(FALSE);
	Dialog_Storage_ID dlg;
	if(dlg.DoModal()!=IDOK)
		return;
	m_StorageInID = dlg.m_StorageID;
	CString csSql;

	csSql.Format("select time_make,time_payment,digest,provider,operator,department,storage  from storage_out_baseinfo where storage_out_id=\"%s\" " ,m_StorageInID); 

	MYSQL myCont;
    MYSQL_RES *result,*result2;
    MYSQL_ROW sql_row,sql_row2;
    int res;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
    {
        mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
        res=mysql_query(&myCont,csSql);//��ѯ
        if(!res)
        {
            result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
		    if(result)
            {
				int totalnumber = 0;
				float totalmoney = 0;
                int j;
                j=mysql_num_fields(result);//�鿴������
				unsigned __int64 num = mysql_num_rows(result);//����
				int index = 0;
				CString strid;
				sql_row=mysql_fetch_row(result);
                if(sql_row!=NULL)//��ȡ���������
                {
					CString strtime;
					strtime = sql_row[0];
					CTime timeTmp(atoi(strtime.Mid(0,4)),atoi(strtime.Mid(5,2)),atoi(strtime.Mid(8,2)),0,0,0,0);
					m_timeCurrent = timeTmp;
					strtime = sql_row[1];
					CTime timeTmp1(atoi(strtime.Mid(0,4)),atoi(strtime.Mid(5,2)),atoi(strtime.Mid(8,2)),0,0,0,0);
					m_timePayment = timeTmp1;
					m_Digest = sql_row[2];
					m_strProvider = sql_row[3];
					m_strOperator = sql_row[4];
					m_strDepartment = sql_row[5];
					m_strStorage = sql_row[6];
					GetDlgItem(IDC_RICHEDIT_DIGEST)->SetWindowText(m_Digest);
					GetDlgItem(IDC_EDIT_STORAGE_IN_ID)->SetWindowText(m_StorageInID);
					UpdateData(FALSE);
                }
				else
				{
					MessageBox("�˵��ݱ�Ų����ڣ���������ȷ���ݱ�ź��ٲ�ѯ","��ʾ",MB_OK);
					mysql_close(&myCont);//�Ͽ�����
					return;
				}

				//item

				csSql.Format("select storage_id,storage_name,SCB,item_name,item_number,item_unit,item_price,item_money from storage_out_item where storage_out_id=\"%s\" " ,m_StorageInID); 
				res=mysql_query(&myCont,csSql);//��ѯ
				if(!res)
				{
					result2=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
					if(result2)
					{
						int j;
						j=mysql_num_fields(result2);//�鿴������
						unsigned __int64 num = mysql_num_rows(result2);//����
						int indexitem = 0;
						int number = 0;
						float money = 0.0;
						CString strid;
						while(sql_row2=mysql_fetch_row(result2))//��ȡ���������
						{
							for(int i=0;i<9;i++)
								m_listStorageIn.SetItemText(index,i+1,sql_row2[i]);
							number += atoi(sql_row2[4]);
							money += atof(sql_row2[7]);
							index++;
						}
						if(index!=0)
						{
							CString strtmp;
							strtmp.Format("%d",number);
							m_listTotal.DeleteColumn(5);
							m_listTotal.InsertColumn(5,strtmp,LVCFMT_LEFT,80);
							
							strtmp.Format("%0.2f",money);
							m_listTotal.DeleteColumn(8);
							m_listTotal.InsertColumn(8,strtmp,LVCFMT_LEFT,100);
						}
						UpdateData(FALSE);
					}
				}
				else
				{
					const char *error = mysql_error(&myCont);
					CString str;
					str.Format("���ݿ����(%s)",error);
					MessageBox(str,"��ʾ",MB_OK);
					mysql_close(&myCont);//�Ͽ�����
					return;
				}
            }
			else
			{
				MessageBox("�˵��ݱ�Ų����ڣ���������ȷ���ݱ�ź��ٲ�ѯ","��ʾ",MB_OK);
				mysql_close(&myCont);//�Ͽ�����
				return;
			}
        }
        else
        {
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			return;
        }
    }
    else
    {
		const char *error = mysql_error(&myCont);
		CString str;
		str.Format("���ݿ����(%s)",error);
		MessageBox(str,"��ʾ",MB_OK);
		mysql_close(&myCont);//�Ͽ�����
		return;
    }
    if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
    mysql_close(&myCont);//�Ͽ�����
}
