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
	
	m_ComBaseinfo.InsertString(0,"订单号");
	m_ComBaseinfo.InsertString(1,"尺寸");
	m_ComBaseinfo.InsertString(2,"收件人");
	m_ComBaseinfo.InsertString(3,"经办人");
	m_ComBaseinfo.InsertString(4,"部门");
	m_ComBaseinfo.InsertString(5,"所有");
	m_ComBaseinfo.SetCurSel(2);

	//m_ComSubway.InsertString(0,"所有");
	//m_ComSubway.SetCurSel(0);
	m_ComSubway.InsertString(0,"所有");
	m_ComSubway.InsertString(1,"北京朝日三维");
	m_ComSubway.InsertString(2,"北京海淀店");
	m_ComSubway.InsertString(3,"北京三里屯店");
	m_ComSubway.InsertString(4,"长沙店");
	m_ComSubway.InsertString(5,"公司样品");
	m_ComSubway.InsertString(6,"海口店");
	m_ComSubway.InsertString(7,"汉口店");
	m_ComSubway.InsertString(8,"乐山店");
	m_ComSubway.InsertString(9,"上海店");
	m_ComSubway.InsertString(10,"绍兴店");
	m_ComSubway.InsertString(11,"太原店");
	m_ComSubway.InsertString(12,"天津店");
	m_ComSubway.InsertString(13,"乌鲁木齐店");
	m_ComSubway.InsertString(14,"郑州店");
	m_ComSubway.SetCurSel(0);
	//m_strStore = "所有";
	m_strSubWay = "所有";
	
	m_listBaseInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES | WS_HSCROLL | WS_VSCROLL |LVS_EX_CHECKBOXES);
	m_listBaseInfo.InsertColumn(0, _T("序号"), LVCFMT_LEFT,60);
	m_listBaseInfo.InsertColumn(1, _T("订单号"), LVCFMT_LEFT,100);
	m_listBaseInfo.InsertColumn(2, _T("客户姓名"), LVCFMT_LEFT,100);
	m_listBaseInfo.InsertColumn(3, _T("运营负责人"), LVCFMT_LEFT,100);
	m_listBaseInfo.InsertColumn(4, _T("尺寸"), LVCFMT_LEFT,120);
	m_listBaseInfo.InsertColumn(5, _T("数量"), LVCFMT_LEFT,60);
	m_listBaseInfo.InsertColumn(6, _T("收件人"), LVCFMT_LEFT,100);
	m_listBaseInfo.InsertColumn(7, _T("派单日期"), LVCFMT_LEFT,100);
	m_listBaseInfo.InsertColumn(8, _T("发货日期"), LVCFMT_LEFT,100);
	m_listBaseInfo.InsertColumn(9, _T("经办人"), LVCFMT_LEFT,100);
	m_listBaseInfo.InsertColumn(10, _T("备注"), LVCFMT_LEFT,150);
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
		MessageBox("请选择订单后在导出","提示",MB_OK);
		return;
	}
	
	CString filename ;
	filename.Format("发货清单.xls");
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
	CString strtmp;
	strtmp.Format("发货清单");
	m_ExlSheet.SetName(strtmp); 

	m_ExlRge.AttachDispatch(m_ExlSheet.GetCells(),TRUE);//加载所有单元格
	m_ExlRge.SetNumberFormatLocal(COleVariant("@")); 

	//合并单元格
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("J1")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));
	
	////////设置表格内容//////// 
	CString strtmp1;

	m_ExlRge.AttachDispatch(m_ExlSheet.GetCells(),TRUE);//加载所有单元格 
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(1)),_variant_t("发货清单"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(1)),_variant_t("订单号"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(2)),_variant_t("客户姓名"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(3)),_variant_t("负责人"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(4)),_variant_t("尺寸"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(5)),_variant_t("数量"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(6)),_variant_t("收件人"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(7)),_variant_t("派单日期"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(8)),_variant_t("发货日期"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(9)),_variant_t("经办人"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(10)),_variant_t("备注"));
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

	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"), _variant_t("J16")));//获取表单中的列"P"对象
	m_ExlRge.SetColumnWidth(_variant_t((long)8));  //设置列宽为100

	m_ExlRge.AttachDispatch(m_ExlSheet.GetUsedRange());//加载已使用的单元格 
	m_ExlRge.SetWrapText(_variant_t((long)1));//设置单元格内的文本为自动换行 
	//m_ExlRge.SetColumnWidth(_variant_t((long)13));  //设置列宽为100
	m_ExlRge.SetRowHeight(_variant_t((long)40));

	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"), _variant_t("J2")));
	m_ExlRge.SetRowHeight(_variant_t((long)30));

	//设置齐方式为水平垂直居中 
	//水平对齐：默认＝1,居中＝-4108,左＝-4131,右＝-4152 
	//垂直对齐：默认＝2,居中＝-4108,左＝-4160,右＝-4107 
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4131));
	m_ExlRge.SetVerticalAlignment(_variant_t((long)-4108));

	///////设置整体的字体、字号及颜色////// 

	Font ft; 

	ft.AttachDispatch(m_ExlRge.GetFont()); 

	ft.SetName(_variant_t("宋体"));//字体 
	//ft.SetColorIndex(_variant_t((long)11));//字的颜色 
	ft.SetColor( _variant_t((long) RGB(32, 32, 32) ) );
	ft.SetSize(_variant_t((long)12));//字号 

	///////////设置标题字体及颜色////////// 

	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("J1"))); 

	ft.AttachDispatch(m_ExlRge.GetFont()); 
	//ft.SetBold(_variant_t((long)0));//粗体 
	ft.SetSize(_variant_t((long)15)); 
	//ft.SetColorIndex(_variant_t((long)2)); 

	//CellFormat cf; 
	//cf.AttachDispatch(m_ExlRge.GetCells()); 

	//居中
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("J1")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4108));
	ft.AttachDispatch(m_ExlRge.GetFont()); 
	//ft.SetBold(_variant_t((long)0));//粗体 
/*	ft.SetSize(_variant_t((long)14)); 
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A7"),_variant_t("F7")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4108));
	ft.AttachDispatch(m_ExlRge.GetFont()); 
	//ft.SetBold(_variant_t((long)0));//粗体 
	ft.SetSize(_variant_t((long)14)); 
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A14"),_variant_t("F14")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4108));
	ft.AttachDispatch(m_ExlRge.GetFont()); 
	//ft.SetBold(_variant_t((long)0));//粗体 
	ft.SetSize(_variant_t((long)14)); 
	*/

	//////////////设置底色///////////////// 

//	Interior it; 
//	it.AttachDispatch(m_ExlRge.GetInterior()); 
//	it.SetColorIndex(_variant_t((long)11));//标题底色 

	////表格内容的底色//// 

//	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"),_variant_t("D5"))); 

//	it.AttachDispatch(m_ExlRge.GetInterior()); 

//	it.SetColorIndex(_variant_t((long)15)); 


	//////////////为表格设置边框///////////// 

	Range UnitRge; 
	CString CellName; 
	for(i=2;i<=selcount+2;i++) 
	{
		//if((i==1)||(i==2)||(i==7)||(i==14))
		//	continue;
		for(int j=1;j<=10;j++) 
		{
			CellName.Format("%c%d",j+64,i);//单元格的名称
			UnitRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t(CellName),_variant_t(CellName)));//加载单元格
			//LineStyle=线型 Weight=线宽 ColorIndex=线的颜色(-4105为自动)
			UnitRge.BorderAround(_variant_t((long)1),_variant_t((long)2),_variant_t((long)-4105),vtMissing);//设置边框
		}
	} 
//	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("B13"),_variant_t("B13")));
//	m_ExlRge.SetRowHeight(COleVariant((short)120));
	
	//Range cols;
	//cols=m_ExlRge.GetEntireColumn();//选择A:A列，设置宽度为自动适应
	//cols.AutoFit();
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
		MessageBox("请选择订单后在打印","提示",MB_OK);
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
	case 0://订单号
		if(m_strSubWay.IsEmpty())
			csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		else
			csSql.Format("select * from baseinfo where  listid=\"%s\" and savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,m_strSubWay,starttime,endtime); 
		break;
	case 1://尺寸
		if(m_strSubWay.IsEmpty())
			csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		else
			csSql = "select * from baseinfo where  size LIKE '" + m_strSubWay + "%'  and savelisttime>= '" + starttime + "' and savelisttime<= '" +endtime + "'";	
		break;
	case 2://收件人
		if(m_strSubWay.IsEmpty() || m_strSubWay.Compare("所有")==0)
			csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		else
			csSql = "select * from baseinfo where  receivepeople LIKE '" + m_strSubWay + "%'  and savelisttime>= '" + starttime + "' and savelisttime<= '" +endtime + "'";
		break;
	case 3://经办人
		if(m_strSubWay.IsEmpty())
			csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		else
			csSql = "select * from baseinfo where  people LIKE '" + m_strSubWay + "%'  and savelisttime>= '" + starttime + "' and savelisttime<= '" +endtime + "'";
		break;
	case 4://部门
		if(m_strSubWay.IsEmpty())
			csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
		else
			csSql = "select * from baseinfo where  department = '" + m_strSubWay + "'  and savelisttime>= '" + starttime + "' and savelisttime<= '" +endtime + "'";
		break;
	case 5://所有
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
        mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
        res=mysql_query(&myCont,csSql);//查询
        if(!res)
        {
            result=mysql_store_result(&myCont);//保存查询到的数据到result
		    if(result)
            {
                int j;
                j=mysql_num_fields(result);//查看多少列
				unsigned __int64 num = mysql_num_rows(result);//行数
				int index = 0;
                while(sql_row=mysql_fetch_row(result))//获取具体的数据
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
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			return;
        }
    }
    else
    {
		const char *error = mysql_error(&myCont);
		CString str;
		str.Format("数据库错误(%s)",error);
		MessageBox(str,"提示",MB_OK);
		mysql_close(&myCont);//断开连接
		return;
    }
    if(result!=NULL) mysql_free_result(result);//释放结果资源
    mysql_close(&myCont);//断开连接
	return;
}

BOOL Dialog_List_Shipping::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN) 
	{  
		switch(pMsg->wParam) 
		{  
		//case VK_RETURN: //回车  
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
	case 0://订单号
		m_ComSubway.ResetContent();
		break;
	case 1://尺寸
		m_ComSubway.ResetContent();
		m_ComSubway.InsertString(0,"6cm半身单人");
		m_ComSubway.InsertString(1,"12cm半身单人");
		m_ComSubway.InsertString(2,"10cm全身单人");
		m_ComSubway.InsertString(3,"13.14cm全身单人");
		m_ComSubway.InsertString(4,"15cm全身单人");
		m_ComSubway.InsertString(5,"19.9cm全身单人");
		m_ComSubway.InsertString(6,"19.9cm婚纱全身单人");
		m_ComSubway.InsertString(7,"28cm全身单人");
		m_ComSubway.InsertString(8,"6cm车载半身单人");
		m_ComSubway.InsertString(9,"6cm车载半身双人");
		m_ComSubway.InsertString(10,"10cm车载全身单人");
		m_ComSubway.InsertString(11,"10cm车载全身双人");
		m_ComSubway.InsertString(12,"10cm动漫路飞");
		m_ComSubway.InsertString(13,"10cm动漫美国队长");
		m_ComSubway.InsertString(14,"10cm动漫蝙蝠侠");
		m_ComSubway.InsertString(15,"10cm动漫德玛西亚");
		m_ComSubway.SetCurSel(0);
		break;
	case 2://收件人
		m_ComSubway.ResetContent();
		m_ComSubway.InsertString(0,"所有");
		m_ComSubway.InsertString(1,"北京朝日三维");
		m_ComSubway.InsertString(2,"北京海淀店");
		m_ComSubway.InsertString(3,"北京三里屯店");
		m_ComSubway.InsertString(4,"长沙店");
		m_ComSubway.InsertString(5,"公司样品");
		m_ComSubway.InsertString(6,"海口店");
		m_ComSubway.InsertString(7,"汉口店");
		m_ComSubway.InsertString(8,"乐山店");
		m_ComSubway.InsertString(9,"上海店");
		m_ComSubway.InsertString(10,"绍兴店");
		m_ComSubway.InsertString(11,"太原店");
		m_ComSubway.InsertString(12,"天津店");
		m_ComSubway.InsertString(13,"乌鲁木齐店");
		m_ComSubway.InsertString(14,"郑州店");
		m_ComSubway.SetCurSel(0);
		break;
	case 3://经办人
		m_ComSubway.ResetContent();
		m_ComSubway.InsertString(0,g_user);
		m_ComSubway.SetCurSel(0);
		break;
	case 4://部门
		m_ComSubway.ResetContent();
		m_ComSubway.InsertString(0,"意造销售");
		m_ComSubway.InsertString(1,"电商");
		m_ComSubway.InsertString(2,"运营");
		m_ComSubway.InsertString(3,"加盟");
		m_ComSubway.InsertString(4,"研发");

		if(strdepartment.Compare("意造销售")==0)
			m_ComSubway.SetCurSel(0);
		else if(strdepartment.Compare("电商")==0)
			m_ComSubway.SetCurSel(1);
		else if(strdepartment.Compare("运营")==0)
			m_ComSubway.SetCurSel(2);
		else if(strdepartment.Compare("加盟")==0)
			m_ComSubway.SetCurSel(3);
		else if(strdepartment.Compare("研发")==0)
			m_ComSubway.SetCurSel(4);
		else
			m_ComSubway.SetCurSel(0);
		break;
	case 5://所有
		m_ComSubway.ResetContent();
		m_ComSubway.InsertString(0,"所有");
		m_ComSubway.SetCurSel(0);
		break;
	default:
		break;
	}
	m_strStore = "所有";	
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
