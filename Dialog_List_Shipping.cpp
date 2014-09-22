// Dialog_List_Shipping.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_List_Shipping.h"
#include "Dialog_ListShippingPrint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_List_Shipping dialog


Dialog_List_Shipping::Dialog_List_Shipping(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_List_Shipping::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_List_Shipping)
	m_strStore = _T("");
	m_strSubWay = _T("");
	m_timeBegin = 0;
	m_timeEnd = 0;
	m_bSelectAll = FALSE;
	//}}AFX_DATA_INIT
}


void Dialog_List_Shipping::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_List_Shipping)
	DDX_Control(pDX, IDC_CHECK_SELECTALL, m_btSelectAll);
	DDX_Control(pDX, IDC_LIST_BASEINFO, m_listBaseInfo);
	DDX_Control(pDX, IDC_BUTTON_QUERY, m_btQuery1);
	DDX_Control(pDX, IDC_COMBO_SUBWAY, m_ComSubway);
	DDX_Control(pDX, IDC_COMBO_STORE, m_ComStore);
	DDX_Control(pDX, IDC_COMBO_BASEINFO, m_ComBaseinfo);
	DDX_Control(pDX, IDC_BUTTON_PRINT, m_btPrint);
	DDX_Control(pDX, IDC_BUTTON_EXCEL, m_btExcel);
	DDX_CBString(pDX, IDC_COMBO_STORE, m_strStore);
	DDX_CBString(pDX, IDC_COMBO_SUBWAY, m_strSubWay);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_timeBegin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_timeEnd);
	DDX_Check(pDX, IDC_CHECK_SELECTALL, m_bSelectAll);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_List_Shipping, CDialog)
	//{{AFX_MSG_MAP(Dialog_List_Shipping)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL, OnButtonExcel)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnButtonPrint)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, OnButtonQuery)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_BASEINFO, OnColumnclickListBaseinfo)
	ON_CBN_SELCHANGE(IDC_COMBO_BASEINFO, OnSelchangeComboBaseinfo)
	ON_BN_CLICKED(IDC_CHECK_SELECTALL, OnCheckSelectall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_List_Shipping message handlers

BOOL Dialog_List_Shipping::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CTime time1 = CTime::GetCurrentTime();
	m_timeBegin = time1;
	m_timeEnd = time1;	
	
	m_ComBaseinfo.InsertString(0,"������");
	m_ComBaseinfo.InsertString(1,"�ߴ�");
	m_ComBaseinfo.InsertString(2,"�ռ���");
	m_ComBaseinfo.InsertString(3,"������");
	m_ComBaseinfo.InsertString(4,"����");
	m_ComBaseinfo.InsertString(5,"����");
	m_ComBaseinfo.SetCurSel(2);

	//m_ComSubway.InsertString(0,"����");
	//m_ComSubway.SetCurSel(0);
	m_ComSubway.InsertString(0,"����");
	m_ComSubway.InsertString(1,"����������ά");
	m_ComSubway.InsertString(2,"���������");
	m_ComSubway.InsertString(3,"���������͵�");
	m_ComSubway.InsertString(4,"��ɳ��");
	m_ComSubway.InsertString(5,"��˾��Ʒ");
	m_ComSubway.InsertString(6,"���ڵ�");
	m_ComSubway.InsertString(7,"���ڵ�");
	m_ComSubway.InsertString(8,"��ɽ��");
	m_ComSubway.InsertString(9,"�Ϻ���");
	m_ComSubway.InsertString(10,"���˵�");
	m_ComSubway.InsertString(11,"̫ԭ��");
	m_ComSubway.InsertString(12,"����");
	m_ComSubway.InsertString(13,"��³ľ���");
	m_ComSubway.InsertString(14,"֣�ݵ�");
	m_ComSubway.SetCurSel(0);
	//m_strStore = "����";
	m_strSubWay = "����";
	
	m_listBaseInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES | WS_HSCROLL | WS_VSCROLL |LVS_EX_CHECKBOXES);
	m_listBaseInfo.InsertColumn(0, _T("���"), LVCFMT_LEFT,60);
	m_listBaseInfo.InsertColumn(1, _T("������"), LVCFMT_LEFT,100);
	m_listBaseInfo.InsertColumn(2, _T("�ͻ�����"), LVCFMT_LEFT,100);
	m_listBaseInfo.InsertColumn(3, _T("��Ӫ������"), LVCFMT_LEFT,100);
	m_listBaseInfo.InsertColumn(4, _T("�ߴ�"), LVCFMT_LEFT,120);
	m_listBaseInfo.InsertColumn(5, _T("����"), LVCFMT_LEFT,60);
	m_listBaseInfo.InsertColumn(6, _T("�ռ���"), LVCFMT_LEFT,100);
	m_listBaseInfo.InsertColumn(7, _T("�ɵ�����"), LVCFMT_LEFT,100);
	m_listBaseInfo.InsertColumn(8, _T("��������"), LVCFMT_LEFT,100);
	m_listBaseInfo.InsertColumn(9, _T("������"), LVCFMT_LEFT,100);
	m_listBaseInfo.InsertColumn(10, _T("��ע"), LVCFMT_LEFT,150);
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_List_Shipping::OnButtonExcel() 
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
	filename.Format("�����嵥.xls");
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
	strtmp.Format("�����嵥");
	m_ExlSheet.SetName(strtmp); 

	m_ExlRge.AttachDispatch(m_ExlSheet.GetCells(),TRUE);//�������е�Ԫ��
	m_ExlRge.SetNumberFormatLocal(COleVariant("@")); 

	//�ϲ���Ԫ��
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("J1")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));
	
	////////���ñ������//////// 
	CString strtmp1;

	m_ExlRge.AttachDispatch(m_ExlSheet.GetCells(),TRUE);//�������е�Ԫ�� 
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(1)),_variant_t("�����嵥"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(1)),_variant_t("������"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(2)),_variant_t("�ͻ�����"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(3)),_variant_t("������"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(4)),_variant_t("�ߴ�"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(5)),_variant_t("����"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(6)),_variant_t("�ռ���"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(7)),_variant_t("�ɵ�����"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(8)),_variant_t("��������"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(9)),_variant_t("������"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(10)),_variant_t("��ע"));
	int curline = 2,j=0;
	for(i=0; i<m_listBaseInfo.GetItemCount(); i++)
	{
	   //if( m_listFI.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || m_listFI.GetCheck(i))
		if(m_listBaseInfo.GetCheck(i))
		{
			curline++;
			for(j=1;j<11;j++)
				m_ExlRge.SetItem(_variant_t((long)(curline)),_variant_t((long)(j)),_variant_t(m_listBaseInfo.GetItemText(i,j)));
		}
	}

	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"), _variant_t("J16")));//��ȡ���е���"P"����
	m_ExlRge.SetColumnWidth(_variant_t((long)8));  //�����п�Ϊ100

	m_ExlRge.AttachDispatch(m_ExlSheet.GetUsedRange());//������ʹ�õĵ�Ԫ�� 
	m_ExlRge.SetWrapText(_variant_t((long)1));//���õ�Ԫ���ڵ��ı�Ϊ�Զ����� 
	//m_ExlRge.SetColumnWidth(_variant_t((long)13));  //�����п�Ϊ100
	m_ExlRge.SetRowHeight(_variant_t((long)40));

	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"), _variant_t("J2")));
	m_ExlRge.SetRowHeight(_variant_t((long)30));

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

	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("J1"))); 

	ft.AttachDispatch(m_ExlRge.GetFont()); 
	//ft.SetBold(_variant_t((long)0));//���� 
	ft.SetSize(_variant_t((long)15)); 
	//ft.SetColorIndex(_variant_t((long)2)); 

	//CellFormat cf; 
	//cf.AttachDispatch(m_ExlRge.GetCells()); 

	//����
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("J1")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4108));
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
	for(i=2;i<=selcount+2;i++) 
	{
		//if((i==1)||(i==2)||(i==7)||(i==14))
		//	continue;
		for(int j=1;j<=10;j++) 
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

void Dialog_List_Shipping::OnButtonPrint() 
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
		MessageBox("��ѡ�񶩵����ڴ�ӡ","��ʾ",MB_OK);
		return;
	}

	Dialog_ListShippingPrint PreviewDlg;
	PreviewDlg.m_list = &m_listBaseInfo;
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
		PreviewDlg.DrawReport(m_rect,&dc1,TRUE);
	}	
	
}

void Dialog_List_Shipping::OnButtonQuery() 
{
	m_listBaseInfo.DeleteAllItems();
	UpdateData();
	m_bSelectAll=0;
	UpdateData(FALSE);
	CString csSql;
	CString starttime;
	starttime.Format("%04d-%02d-%02d",m_timeBegin.GetYear(),m_timeBegin.GetMonth(),m_timeBegin.GetDay());
	CString endtime;
	endtime.Format("%04d-%02d-%02d",m_timeEnd.GetYear(),m_timeEnd.GetMonth(),m_timeEnd.GetDay()+1);

	int selstore = m_ComStore.GetCurSel();
	int cursel = m_ComBaseinfo.GetCurSel();
	switch (cursel)
	{
	case 0://������
		if(m_strSubWay.IsEmpty())
			csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		else
			csSql.Format("select * from baseinfo where  listid=\"%s\" and savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,m_strSubWay,starttime,endtime); 
		break;
	case 1://�ߴ�
		if(m_strSubWay.IsEmpty())
			csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		else
			csSql = "select * from baseinfo where  size LIKE '" + m_strSubWay + "%'  and savelisttime>= '" + starttime + "' and savelisttime<= '" +endtime + "'";	
		break;
	case 2://�ռ���
		if(m_strSubWay.IsEmpty() || m_strSubWay.Compare("����")==0)
			csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		else
			csSql = "select * from baseinfo where  receivepeople LIKE '" + m_strSubWay + "%'  and savelisttime>= '" + starttime + "' and savelisttime<= '" +endtime + "'";
		break;
	case 3://������
		if(m_strSubWay.IsEmpty())
			csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		else
			csSql = "select * from baseinfo where  people LIKE '" + m_strSubWay + "%'  and savelisttime>= '" + starttime + "' and savelisttime<= '" +endtime + "'";
		break;
	case 4://����
		if(m_strSubWay.IsEmpty())
			csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		else
			csSql = "select * from baseinfo where  department = '" + m_strSubWay + "'  and savelisttime>= '" + starttime + "' and savelisttime<= '" +endtime + "'";
		break;
	case 5://����
		csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		break;
	default:
		break;
	}

	//csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
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
					strindex.Format("%d",index+1);
					m_listBaseInfo.InsertItem(index,strindex);
					m_listBaseInfo.SetItemText(index,1,sql_row[0]);
					m_listBaseInfo.SetItemText(index,2,sql_row[1]);
					m_listBaseInfo.SetItemText(index,3,sql_row[8]);
					m_listBaseInfo.SetItemText(index,4,sql_row[19]);
					m_listBaseInfo.SetItemText(index,5,sql_row[2]);
					m_listBaseInfo.SetItemText(index,6,sql_row[9]);
					m_listBaseInfo.SetItemText(index,7,sql_row[5]);
					m_listBaseInfo.SetItemText(index,8,sql_row[6]);
					m_listBaseInfo.SetItemText(index,9,sql_row[8]);
					m_listBaseInfo.SetItemText(index,10,"");
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

BOOL Dialog_List_Shipping::PreTranslateMessage(MSG* pMsg) 
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

void Dialog_List_Shipping::OnColumnclickListBaseinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	listsort(&m_listBaseInfo,pNMListView);
	*pResult = 0;
}

void Dialog_List_Shipping::OnSelchangeComboBaseinfo() 
{
	CString strdepartment;
	strdepartment = g_department;
	int indexSel = m_ComBaseinfo.GetCurSel();
	switch (indexSel)
	{
	case 0://������
		m_ComSubway.ResetContent();
		break;
	case 1://�ߴ�
		m_ComSubway.ResetContent();
		m_ComSubway.InsertString(0,"6cm������");
		m_ComSubway.InsertString(1,"12cm������");
		m_ComSubway.InsertString(2,"10cmȫ����");
		m_ComSubway.InsertString(3,"13.14cmȫ����");
		m_ComSubway.InsertString(4,"15cmȫ����");
		m_ComSubway.InsertString(5,"19.9cmȫ����");
		m_ComSubway.InsertString(6,"19.9cm��ɴȫ����");
		m_ComSubway.InsertString(7,"28cmȫ����");
		m_ComSubway.InsertString(8,"6cm���ذ�����");
		m_ComSubway.InsertString(9,"6cm���ذ���˫��");
		m_ComSubway.InsertString(10,"10cm����ȫ����");
		m_ComSubway.InsertString(11,"10cm����ȫ��˫��");
		m_ComSubway.InsertString(12,"10cm����·��");
		m_ComSubway.InsertString(13,"10cm���������ӳ�");
		m_ComSubway.InsertString(14,"10cm����������");
		m_ComSubway.InsertString(15,"10cm������������");
		m_ComSubway.SetCurSel(0);
		break;
	case 2://�ռ���
		m_ComSubway.ResetContent();
		m_ComSubway.InsertString(0,"����");
		m_ComSubway.InsertString(1,"����������ά");
		m_ComSubway.InsertString(2,"���������");
		m_ComSubway.InsertString(3,"���������͵�");
		m_ComSubway.InsertString(4,"��ɳ��");
		m_ComSubway.InsertString(5,"��˾��Ʒ");
		m_ComSubway.InsertString(6,"���ڵ�");
		m_ComSubway.InsertString(7,"���ڵ�");
		m_ComSubway.InsertString(8,"��ɽ��");
		m_ComSubway.InsertString(9,"�Ϻ���");
		m_ComSubway.InsertString(10,"���˵�");
		m_ComSubway.InsertString(11,"̫ԭ��");
		m_ComSubway.InsertString(12,"����");
		m_ComSubway.InsertString(13,"��³ľ���");
		m_ComSubway.InsertString(14,"֣�ݵ�");
		m_ComSubway.SetCurSel(0);
		break;
	case 3://������
		m_ComSubway.ResetContent();
		m_ComSubway.InsertString(0,g_user);
		m_ComSubway.SetCurSel(0);
		break;
	case 4://����
		m_ComSubway.ResetContent();
		m_ComSubway.InsertString(0,"��������");
		m_ComSubway.InsertString(1,"����");
		m_ComSubway.InsertString(2,"��Ӫ");
		m_ComSubway.InsertString(3,"����");
		m_ComSubway.InsertString(4,"�з�");

		if(strdepartment.Compare("��������")==0)
			m_ComSubway.SetCurSel(0);
		else if(strdepartment.Compare("����")==0)
			m_ComSubway.SetCurSel(1);
		else if(strdepartment.Compare("��Ӫ")==0)
			m_ComSubway.SetCurSel(2);
		else if(strdepartment.Compare("����")==0)
			m_ComSubway.SetCurSel(3);
		else if(strdepartment.Compare("�з�")==0)
			m_ComSubway.SetCurSel(4);
		else
			m_ComSubway.SetCurSel(0);
		break;
	case 5://����
		m_ComSubway.ResetContent();
		m_ComSubway.InsertString(0,"����");
		m_ComSubway.SetCurSel(0);
		break;
	default:
		break;
	}
	m_strStore = "����";	
}

void Dialog_List_Shipping::OnCheckSelectall() 
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
