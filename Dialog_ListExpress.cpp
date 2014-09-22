// Dialog_ListExpress.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_ListExpress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_ListExpress dialog


Dialog_ListExpress::Dialog_ListExpress(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_ListExpress::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_ListExpress)
	m_bSelectAll = FALSE;
	m_bBaseInfo = -1;
	m_strSubWay = _T("");
	m_timeBegin = 0;
	m_timeEnd = 0;
	m_strListNo = _T("");
	//}}AFX_DATA_INIT
}


void Dialog_ListExpress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_ListExpress)
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_btdelete);
	DDX_Control(pDX, IDC_LIST_BASEINFO, m_listBaseInfo);
	DDX_Control(pDX, IDC_COMBO_SUBWAY, m_comSubWay);
	DDX_Control(pDX, IDC_COMBO_BASEINFO, m_comBaseInfo);
	DDX_Control(pDX, IDC_CHECK_SELECTALL, m_btSelectAll);
	DDX_Control(pDX, IDC_BUTTON_QUERY, m_btquery);
	DDX_Control(pDX, IDC_BUTTON_PRINT, m_btprint);
	DDX_Control(pDX, IDC_BUTTON_EXCEL, m_btexcel);
	DDX_Check(pDX, IDC_CHECK_SELECTALL, m_bSelectAll);
	DDX_CBIndex(pDX, IDC_COMBO_BASEINFO, m_bBaseInfo);
	DDX_CBString(pDX, IDC_COMBO_SUBWAY, m_strSubWay);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_timeBegin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_timeEnd);
	DDX_Text(pDX, IDC_EDIT_LIST, m_strListNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_ListExpress, CDialog)
	//{{AFX_MSG_MAP(Dialog_ListExpress)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL, OnButtonExcel)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnButtonPrint)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, OnButtonAdd)
	ON_BN_CLICKED(IDC_CHECK_SELECTALL, OnCheckSelectall)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_BASEINFO, OnColumnclickListBaseinfo)
	ON_CBN_SELCHANGE(IDC_COMBO_BASEINFO, OnSelchangeComboBaseinfo)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_ListExpress message handlers

BOOL Dialog_ListExpress::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN) 
	{  
		switch(pMsg->wParam) 
		{  
			//case VK_RETURN: //�س�  
			//	return TRUE;  
		case VK_ESCAPE: //ESC  
			return TRUE;  
		}  
	}	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL Dialog_ListExpress::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CTime time1 = CTime::GetCurrentTime();
	m_timeBegin = time1;
	m_timeEnd = time1;	
	
	m_comBaseInfo.InsertString(0,"������");
	m_comBaseInfo.InsertString(1,"�ߴ�");
	m_comBaseInfo.InsertString(2,"�ռ���");
	m_comBaseInfo.InsertString(3,"������");
	m_comBaseInfo.InsertString(4,"����");
	m_comBaseInfo.InsertString(5,"����");
	m_comBaseInfo.SetCurSel(0);
	m_bBaseInfo = 0;
	
	//m_ComSubway.InsertString(0,"����");
	//m_ComSubway.SetCurSel(0);
	m_comSubWay.SetCurSel(-1);
	//m_strStore = "����";
	m_strSubWay = "";
	
	m_listBaseInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES | WS_HSCROLL | WS_VSCROLL |LVS_EX_CHECKBOXES);
	m_listBaseInfo.InsertColumn(0, _T("���"), LVCFMT_LEFT,60);
	m_listBaseInfo.InsertColumn(1, _T("������"), LVCFMT_LEFT,100);
	m_listBaseInfo.InsertColumn(2, _T("��������"), LVCFMT_LEFT,100);
	m_listBaseInfo.InsertColumn(3, _T("�ļ���"), LVCFMT_LEFT,100);
	m_listBaseInfo.InsertColumn(4, _T("�ļ���˾"), LVCFMT_LEFT,120);
	m_listBaseInfo.InsertColumn(5, _T("�ļ�����ϵ�绰"), LVCFMT_LEFT,140);
	m_listBaseInfo.InsertColumn(6, _T("�ļ��˵�ַ"), LVCFMT_LEFT,150);
	m_listBaseInfo.InsertColumn(7, _T("�м�������"), LVCFMT_LEFT,100);
	m_listBaseInfo.InsertColumn(8, _T("����"), LVCFMT_LEFT,60);
	m_listBaseInfo.InsertColumn(9, _T("�ջ���"), LVCFMT_LEFT,100);
	m_listBaseInfo.InsertColumn(10, _T("�ջ���˾"), LVCFMT_LEFT,120);
	m_listBaseInfo.InsertColumn(11, _T("�ջ�����ϵ�绰"), LVCFMT_LEFT,140);
	m_listBaseInfo.InsertColumn(12, _T("�ջ���ַ"), LVCFMT_LEFT,150);
	m_listBaseInfo.InsertColumn(13, _T("��ע"), LVCFMT_LEFT,100);
	UpdateData(FALSE);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_ListExpress::OnButtonExcel() 
{
	UpdateData();
	CString strlistid;
	int selcount = 0;
	int i=0;
	for(i=0; i<m_listBaseInfo.GetItemCount(); i++)
	{
	   //if( m_listFI.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || m_listFI.GetCheck(i))
		if(m_listBaseInfo.GetCheck(i))
		{
			CString strtmp = m_listBaseInfo.GetItemText(i,1);
			strtmp+=",";
			strlistid+=strtmp;
			selcount++;
		}
	}
	if(selcount==0)
	{
		MessageBox("��ѡ�񶩵����ڵ���","��ʾ",MB_OK);
		return;
	}
	
	CString filename ;
	filename.Format("������ӡ.xls");
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
	strtmp.Format("������ӡ");
	m_ExlSheet.SetName(strtmp); 

	m_ExlRge.AttachDispatch(m_ExlSheet.GetCells(),TRUE);//�������е�Ԫ��
	m_ExlRge.SetNumberFormatLocal(COleVariant("@")); 

	//�ϲ���Ԫ��
//	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("J1")),TRUE); 
//    m_ExlRge.Merge(_variant_t((long)0));
	
	////////���ñ������//////// 
	CString strtmp1;

	m_ExlRge.AttachDispatch(m_ExlSheet.GetCells(),TRUE);//�������е�Ԫ�� 
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(1)),_variant_t("�ļ��ͻ����"));
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(2)),_variant_t("�ļ���"));
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(3)),_variant_t("�ļ���˾"));
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(4)),_variant_t("�ļ�����ϵ�绰"));
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(5)),_variant_t("�ļ��˵�ַ"));
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(6)),_variant_t("�м�������"));
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(7)),_variant_t("����"));
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(8)),_variant_t("�ռ���"));
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(9)),_variant_t("�ջ���˾"));
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(10)),_variant_t("�ջ�����ϵ�绰"));
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(11)),_variant_t("�ջ���ַ"));
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(12)),_variant_t("��ע"));
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(13)),_variant_t("���ʽ"));
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(14)),_variant_t("����"));
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(15)),_variant_t("���۽��"));
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(16)),_variant_t("���մ���"));
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(17)),_variant_t("���մ����"));
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(18)),_variant_t("���մ�����"));
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(19)),_variant_t("��ע1"));
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(20)),_variant_t("��ע2"));
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(21)),_variant_t("��ע3"));
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(22)),_variant_t("����"));
	int curline = 1,j=0;
	for(i=0; i<m_listBaseInfo.GetItemCount(); i++)
	{
	   //if( m_listFI.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || m_listFI.GetCheck(i))
		if(m_listBaseInfo.GetCheck(i))
		{
			curline++;
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(1)),_variant_t(""));
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(2)),_variant_t(m_listBaseInfo.GetItemText(i,3)));
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(3)),_variant_t("�人��ش����Ļ��������޹�˾"));
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(4)),_variant_t(m_listBaseInfo.GetItemText(i,5)));
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(5)),_variant_t(m_listBaseInfo.GetItemText(i,6)));
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(6)),_variant_t(m_listBaseInfo.GetItemText(i,7)));
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(7)),_variant_t(m_listBaseInfo.GetItemText(i,8)));
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(8)),_variant_t(m_listBaseInfo.GetItemText(i,9)));
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(9)),_variant_t(""));
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(10)),_variant_t(m_listBaseInfo.GetItemText(i,11)));
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(11)),_variant_t(m_listBaseInfo.GetItemText(i,12)));
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(12)),_variant_t(""));
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(13)),_variant_t(""));
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(14)),_variant_t(""));
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(15)),_variant_t(""));
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(16)),_variant_t(""));
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(17)),_variant_t("N-��"));
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(18)),_variant_t(""));
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(19)),_variant_t(""));
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(20)),_variant_t(""));
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(21)),_variant_t(""));
			m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(22)),_variant_t(""));
		}
	}

	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"), _variant_t("V16")));//��ȡ���е���"P"����
/*
	m_ExlRge.SetColumnWidth(_variant_t((long)8));  //�����п�Ϊ100

	m_ExlRge.AttachDispatch(m_ExlSheet.GetUsedRange());//������ʹ�õĵ�Ԫ�� 
	m_ExlRge.SetWrapText(_variant_t((long)1));//���õ�Ԫ���ڵ��ı�Ϊ�Զ����� 
	//m_ExlRge.SetColumnWidth(_variant_t((long)13));  //�����п�Ϊ100
	m_ExlRge.SetRowHeight(_variant_t((long)40));
	*/

	//m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"), _variant_t("J2")));
	//m_ExlRge.SetRowHeight(_variant_t((long)30));

	//�����뷽ʽΪˮƽ��ֱ���� 
	//ˮƽ���룺Ĭ�ϣ�1,���У�-4108,��-4131,�ң�-4152 
	//��ֱ���룺Ĭ�ϣ�2,���У�-4108,��-4160,�ң�-4107 
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4131));
	m_ExlRge.SetVerticalAlignment(_variant_t((long)-4108));

	///////������������塢�ֺż���ɫ////// 

/*	Font ft; 

	ft.AttachDispatch(m_ExlRge.GetFont()); 

	ft.SetName(_variant_t("����"));//���� 
	//ft.SetColorIndex(_variant_t((long)11));//�ֵ���ɫ 
	ft.SetColor( _variant_t((long) RGB(32, 32, 32) ) );
	ft.SetSize(_variant_t((long)12));//�ֺ� 

	///////////���ñ������弰��ɫ////////// 

	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("V1"))); 

	ft.AttachDispatch(m_ExlRge.GetFont()); 
	//ft.SetBold(_variant_t((long)0));//���� 
	ft.SetSize(_variant_t((long)15)); 
	//ft.SetColorIndex(_variant_t((long)2)); 

	//CellFormat cf; 
	//cf.AttachDispatch(m_ExlRge.GetCells()); 

	//����
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("V1")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4108));
	ft.AttachDispatch(m_ExlRge.GetFont()); 

	*/
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
	for(i=1;i<=selcount+1;i++) 
	{
		//if((i==1)||(i==2)||(i==7)||(i==14))
		//	continue;
		for(int j=1;j<=22;j++) 
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

void Dialog_ListExpress::OnButtonPrint() 
{
	// TODO: Add your control notification handler code here
	
}

void Dialog_ListExpress::OnButtonAdd() 
{
	UpdateData();
	m_bSelectAll=0;
	UpdateData(FALSE);
	CString csSql;
	csSql.Format("select baseinfo.listid,baseinfo.listname,people,truelistnumber,receivepeople,baseinfo.phone,address  from baseinfo where  listid=\"%s\" " ,m_strListNo);
	int count = m_listBaseInfo.GetItemCount();
	CString strSenderUser;

    MYSQL myCont;
    MYSQL_RES *result;
    MYSQL_ROW sql_row;
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
                int j;
                j=mysql_num_fields(result);//�鿴������
				unsigned __int64 num = mysql_num_rows(result);//����
				int index = 0;
                while(sql_row=mysql_fetch_row(result))//��ȡ���������
                {
					CString strindex ;
					strindex.Format("%d",count+1);
					m_listBaseInfo.InsertItem(count,strindex);
					m_listBaseInfo.SetItemText(count,1,sql_row[0]);
					m_listBaseInfo.SetItemText(count,2,sql_row[1]);
					m_listBaseInfo.SetItemText(count,3,sql_row[2]);
					m_listBaseInfo.SetItemText(count,4,"�人��ش����Ļ��������޹�˾");
					strSenderUser = sql_row[2];
					//m_listBaseInfo.SetItemText(index,5,sql_row[3]);
					m_listBaseInfo.SetItemText(count,6,"����ʡ�人�к�ɽ�� ��ȴ�� ������ҵ���Ķ��� ����¥1-3¥");
					m_listBaseInfo.SetItemText(count,7,sql_row[1]);
					m_listBaseInfo.SetItemText(count,8,sql_row[3]);
					m_listBaseInfo.SetItemText(count,9,sql_row[4]);
					m_listBaseInfo.SetItemText(count,10,"");
					m_listBaseInfo.SetItemText(count,11,sql_row[5]);
					m_listBaseInfo.SetItemText(count,12,sql_row[6]);
					m_listBaseInfo.SetItemText(count,13,"");
					if(index%2==0)
						m_listBaseInfo.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
					index++;
                }
				m_btSelectAll.ShowWindow(TRUE);
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

		csSql.Format("select phone from senduserinfo where  username=\"%s\" " ,strSenderUser);
		res=mysql_query(&myCont,csSql);//��ѯ
        if(!res)
        {
            result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
			if(result)
            {
                int j;
                j=mysql_num_fields(result);//�鿴������
				unsigned __int64 num = mysql_num_rows(result);//����
				int index = 0;
                while(sql_row=mysql_fetch_row(result))//��ȡ���������
                {
					m_listBaseInfo.SetItemText(count,5,sql_row[0]);					
                }
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
	return;
}

void Dialog_ListExpress::OnCheckSelectall() 
{
	UpdateData(TRUE);
	if(m_bSelectAll==1)
	{
		for(int i=0; i<m_listBaseInfo.GetItemCount(); i++)
		{
			m_listBaseInfo.SetCheck(i,TRUE);			
		}
	}
	else
	{
		for(int i=0; i<m_listBaseInfo.GetItemCount(); i++)
		{
			m_listBaseInfo.SetCheck(i,FALSE);			
		}
	}
	UpdateData(TRUE);
}

void Dialog_ListExpress::OnColumnclickListBaseinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	listsort(&m_listBaseInfo,pNMListView);
	
	*pResult = 0;
}

void Dialog_ListExpress::OnSelchangeComboBaseinfo() 
{
	// TODO: Add your control notification handler code here
	
}

void Dialog_ListExpress::OnButtonDelete() 
{
	UpdateData();
	CString strlistid;
	int selcount = 0;
	int i=0;
	for(i=0; i<m_listBaseInfo.GetItemCount(); i++)
	{
		if(m_listBaseInfo.GetCheck(i))
		{
			CString strtmp = m_listBaseInfo.GetItemText(i,1);
			strtmp+=",";
			strlistid+=strtmp;
			selcount++;
			m_listBaseInfo.DeleteItem(i);
		}
	}
	if(selcount==0)
	{
		MessageBox("��ѡ�񶩵�����ɾ��","��ʾ",MB_OK);
		return;
	}

}
