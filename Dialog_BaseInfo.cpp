// Dialog_BaseInfo.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_BaseInfo.h"
#include "Dialog_InputBaseinfo.h"
#include "comdef.h"
#include "Dialog_Query_list.h"
#include "Dialog_New_List.h"
#include "Dialog_ModifyList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_BaseInfo dialog


CDialog_BaseInfo::CDialog_BaseInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_BaseInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_BaseInfo)
	m_str_select_baseinfo = _T("");
	m_time_bgein = 0;
	m_time_end = 0;
	//}}AFX_DATA_INIT
}


void CDialog_BaseInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_BaseInfo)
	DDX_Control(pDX, IDC_LIST_BASEINFO, m_list_baseinfo);
	DDX_Control(pDX, IDC_COMBO_BASEINFO, m_com_baseinfo);
	DDX_Text(pDX, IDC_EDIT_BASEINFO, m_str_select_baseinfo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_time_bgein);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_time_end);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_BaseInfo, CDialog)
	//{{AFX_MSG_MAP(CDialog_BaseInfo)
	ON_BN_CLICKED(IDC_BUTTON_SELL_SELECT, OnButtonSellSelect)
	ON_BN_CLICKED(IDC_BUTTON_BASEINFO_ADD, OnButtonBaseinfoAdd)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BASEINFO, OnDblclkListBaseinfo)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_BASEINFO, OnColumnclickListBaseinfo)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL, OnExcel)
	ON_CBN_SELCHANGE(IDC_COMBO_BASEINFO, OnSelchangeComboBaseinfo)
	ON_BN_CLICKED(IDC_BUTTON1, OnModifyList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_BaseInfo message handlers

void CDialog_BaseInfo::OnButtonSellSelect() 
{
	// TODO: Add your control notification handler code here
	m_list_baseinfo.DeleteAllItems();
	UpdateData();
	CString csSql;
	m_str_select_baseinfo.TrimLeft();
	m_str_select_baseinfo.TrimRight();
	CString starttime;
	starttime.Format("%04d-%02d-%02d",m_time_bgein.GetYear(),m_time_bgein.GetMonth(),m_time_bgein.GetDay());
	CString endtime;
	endtime.Format("%04d-%02d-%02d",m_time_end.GetYear(),m_time_end.GetMonth(),m_time_end.GetDay()+1);

	csSql.Format("select * from baseinfo where  savelisttime>=\"%s\"and savelisttime<=\"%s\" " ,starttime,endtime); 
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
					m_list_baseinfo.InsertItem(index,strindex);
					m_list_baseinfo.SetItemText(index,1,sql_row[0]);
					m_list_baseinfo.SetItemText(index,2,sql_row[1]);
					m_list_baseinfo.SetItemText(index,3,sql_row[8]);
					m_list_baseinfo.SetItemText(index,4,sql_row[9]);
					m_list_baseinfo.SetItemText(index,5,sql_row[10]);
					m_list_baseinfo.SetItemText(index,6,sql_row[11]);
					m_list_baseinfo.SetItemText(index,7,sql_row[12]);
					m_list_baseinfo.SetItemText(index,8,sql_row[5]);
					m_list_baseinfo.SetItemText(index,9,sql_row[6]);
					m_list_baseinfo.SetItemText(index,10,sql_row[13]);
					m_list_baseinfo.SetItemText(index,11,sql_row[14]);
					m_list_baseinfo.SetItemText(index,12,sql_row[15]);
					m_list_baseinfo.SetItemText(index,13,sql_row[16]);
					m_list_baseinfo.SetItemText(index,14,sql_row[17]);
					m_list_baseinfo.SetItemText(index,15,sql_row[18]);
					m_list_baseinfo.SetItemText(index,16,sql_row[19]);
					m_list_baseinfo.SetItemText(index,17,sql_row[20]);
					m_list_baseinfo.SetItemText(index,18,sql_row[3]);
					m_list_baseinfo.SetItemText(index,19,sql_row[21]);
					m_list_baseinfo.SetItemText(index,20,sql_row[22]);
					m_list_baseinfo.SetItemText(index,21,sql_row[23]);
					m_list_baseinfo.SetItemText(index,22,sql_row[24]);
					m_list_baseinfo.SetItemText(index,23,sql_row[25]);
					m_list_baseinfo.SetItemText(index,24,sql_row[26]);
					m_list_baseinfo.SetItemText(index,25,sql_row[27]);
					m_list_baseinfo.SetItemText(index,26,sql_row[4]);
					m_list_baseinfo.SetItemText(index,27,sql_row[29]);
					if(index%2==0)
						m_list_baseinfo.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
					index++;
                }
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
		MessageBox("连接数据库失败，请检查网络是否正确连接","提示",MB_OK);
        //cout<<"connect failed!"<<endl;
    }
    if(result!=NULL) mysql_free_result(result);//释放结果资源
    mysql_close(&myCont);//断开连接

	return;

}

void CDialog_BaseInfo::OnButtonBaseinfoAdd() 
{
	// TODO: Add your control notification handler code here
	CDialog_New_List dlg;
	dlg.DoModal();
	return;
	CDialog_InputBaseinfo dlg_baseinfo;
	if (dlg_baseinfo.DoModal()==IDOK)
	{
		m_list_baseinfo.DeleteAllItems();

		m_list_baseinfo.InsertItem(0,dlg_baseinfo.m_ListID);
		m_list_baseinfo.SetItemText(0,1,dlg_baseinfo.m_ClientName);
		m_list_baseinfo.SetItemText(0,2,dlg_baseinfo.m_str_reveive_time);
		m_list_baseinfo.SetItemText(0,3,dlg_baseinfo.m_str_end_date);
		m_list_baseinfo.SetItemText(0,4,dlg_baseinfo.m_department);
		m_list_baseinfo.SetItemText(0,5,dlg_baseinfo.m_adress);
		m_list_baseinfo.SetItemText(0,6,dlg_baseinfo.m_Phone);
		m_list_baseinfo.SetItemText(0,7,dlg_baseinfo.m_Mondy);
		m_list_baseinfo.SetItemText(0,8,dlg_baseinfo.m_size);
		m_list_baseinfo.SetItemText(0,9,dlg_baseinfo.m_material);
		m_list_baseinfo.SetItemText(0,10,dlg_baseinfo.m_color);
		m_list_baseinfo.SetItemText(0,11,dlg_baseinfo.m_paint);
		m_list_baseinfo.SetItemText(0,12,dlg_baseinfo.m_bottom);
		m_list_baseinfo.SetItemText(0,13,dlg_baseinfo.m_accuracy);
		m_list_baseinfo.SetItemText(0,14,dlg_baseinfo.m_errorrange);
		m_list_baseinfo.SetItemText(0,15,dlg_baseinfo.m_other);
	}
}

BOOL CDialog_BaseInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CTime time1 = CTime::GetCurrentTime();
	m_time_bgein = time1;
	m_time_end = time1;	
	
	m_com_baseinfo.InsertString(0,"时间");
	m_com_baseinfo.InsertString(1,"单号");
	m_com_baseinfo.SetCurSel(0);
	
	m_list_baseinfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list_baseinfo.InsertColumn(0, _T("序号"), LVCFMT_LEFT,60);
	m_list_baseinfo.InsertColumn(1, _T("单号"), LVCFMT_LEFT,100);
	m_list_baseinfo.InsertColumn(2, _T("订单名称"), LVCFMT_LEFT,80);
	m_list_baseinfo.InsertColumn(3, _T("经办人"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(4, _T("收件人"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(5, _T("联系电话"), LVCFMT_LEFT,100);
	m_list_baseinfo.InsertColumn(6, _T("详细地址"), LVCFMT_LEFT,100);
	m_list_baseinfo.InsertColumn(7, _T("部门/门店"), LVCFMT_LEFT,100);
	m_list_baseinfo.InsertColumn(8, _T("派单日期"), LVCFMT_LEFT,100);
	m_list_baseinfo.InsertColumn(9, _T("交货日期"), LVCFMT_LEFT,100);
	m_list_baseinfo.InsertColumn(10, _T("建模"), LVCFMT_LEFT,60);
	m_list_baseinfo.InsertColumn(11, _T("设计服务"), LVCFMT_LEFT,80);
	m_list_baseinfo.InsertColumn(12, _T("扫描业务"), LVCFMT_LEFT,80);
	m_list_baseinfo.InsertColumn(13, _T("模型打印"), LVCFMT_LEFT,80);
	m_list_baseinfo.InsertColumn(14, _T("有模型"), LVCFMT_LEFT,80);
	m_list_baseinfo.InsertColumn(15, _T("无模型"), LVCFMT_LEFT,80);
	m_list_baseinfo.InsertColumn(16, _T("尺寸"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(17, _T("加工数量"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(18, _T("制作材料"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(19, _T("颜色"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(20, _T("喷漆"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(21, _T("打磨"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(22, _T("底座搭配"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(23, _T("发票随寄"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(24, _T("用途"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(25, _T("误差范围"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(26, _T("体积"), LVCFMT_LEFT,90);
	m_list_baseinfo.InsertColumn(27, _T("其他要求"), LVCFMT_LEFT,90);


	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_BaseInfo::OnDblclkListBaseinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int sel=m_list_baseinfo.GetSelectionMark();
	if(sel==-1) return;
	return;
	/*
	CDialog_InputBaseinfo *dlg_baseinfo=new CDialog_InputBaseinfo(); 
	dlg_baseinfo->Create(IDD_DIALOG_INPUT_BASEINFO); 
	dlg_baseinfo->m_bModify = 1;
	dlg_baseinfo->m_ListID = m_list_baseinfo.GetItemText(sel,0);
	dlg_baseinfo->m_ClientName = m_list_baseinfo.GetItemText(sel,1);
	dlg_baseinfo->m_str_reveive_time = m_list_baseinfo.GetItemText(sel,2);
	dlg_baseinfo->m_str_end_date = m_list_baseinfo.GetItemText(sel,3);
	dlg_baseinfo->m_department = m_list_baseinfo.GetItemText(sel,4);
	dlg_baseinfo->m_adress = m_list_baseinfo.GetItemText(sel,5);
	dlg_baseinfo->m_Phone = m_list_baseinfo.GetItemText(sel,6);
	dlg_baseinfo->m_Mondy = m_list_baseinfo.GetItemText(sel,7);
	dlg_baseinfo->m_size = m_list_baseinfo.GetItemText(sel,8);
	dlg_baseinfo->m_material = m_list_baseinfo.GetItemText(sel,9);
	dlg_baseinfo->m_color = m_list_baseinfo.GetItemText(sel,10);
	dlg_baseinfo->m_paint = m_list_baseinfo.GetItemText(sel,11);
	dlg_baseinfo->m_bottom = m_list_baseinfo.GetItemText(sel,12);
	dlg_baseinfo->m_accuracy = m_list_baseinfo.GetItemText(sel,13);
	dlg_baseinfo->m_errorrange = m_list_baseinfo.GetItemText(sel,14);
	dlg_baseinfo->m_other = m_list_baseinfo.GetItemText(sel,15);
	dlg_baseinfo->ShowWindow(SW_SHOW);
	*/
	/*
	CDialog_InputBaseinfo dlg_baseinfo;
	dlg_baseinfo.m_bModify = 1;
	dlg_baseinfo.m_ListID = m_list_baseinfo.GetItemText(sel,0);
	dlg_baseinfo.m_ClientName = m_list_baseinfo.GetItemText(sel,1);
	dlg_baseinfo.m_str_reveive_time = m_list_baseinfo.GetItemText(sel,2);
	dlg_baseinfo.m_str_end_date = m_list_baseinfo.GetItemText(sel,3);
	dlg_baseinfo.m_department = m_list_baseinfo.GetItemText(sel,4);
	dlg_baseinfo.m_adress = m_list_baseinfo.GetItemText(sel,5);
	dlg_baseinfo.m_Phone = m_list_baseinfo.GetItemText(sel,6);
	dlg_baseinfo.m_Mondy = m_list_baseinfo.GetItemText(sel,7);
	dlg_baseinfo.m_size = m_list_baseinfo.GetItemText(sel,8);
	dlg_baseinfo.m_material = m_list_baseinfo.GetItemText(sel,9);
	dlg_baseinfo.m_color = m_list_baseinfo.GetItemText(sel,10);
	dlg_baseinfo.m_paint = m_list_baseinfo.GetItemText(sel,11);
	dlg_baseinfo.m_bottom = m_list_baseinfo.GetItemText(sel,12);
	dlg_baseinfo.m_accuracy = m_list_baseinfo.GetItemText(sel,13);
	dlg_baseinfo.m_errorrange = m_list_baseinfo.GetItemText(sel,14);
	dlg_baseinfo.m_other = m_list_baseinfo.GetItemText(sel,15);

	if (dlg_baseinfo.DoModal()==IDOK)
	{}
	*/
	*pResult = 0;
}

void CDialog_BaseInfo::OnColumnclickListBaseinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CDialog_BaseInfo::OnExcel() 
{
	// TODO: Add your control notification handler code here
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
	TempPath=theAppPath+"订单资料.xls";//EXCEL模板的路径 
//	CFile file;
//	file.Open(TempPath,CFile::modeCreate|CFile::modeWrite);
//	file.Close();


	m_ExlBooks.AttachDispatch(m_ExlApp.GetWorkbooks(),TRUE); 

	m_ExlBook.AttachDispatch(m_ExlBooks.Add((_variant_t)TempPath),TRUE);//加载EXCEL模板 

	m_ExlSheets.AttachDispatch(m_ExlBook.GetSheets(),TRUE);//加载Sheet页面 

	//添加新的Sheet页面 
	m_ExlSheets.Add(vtMissing,vtMissing,_variant_t((long)1),vtMissing); 

	//删除第二个Sheet页面 
	m_ExlSheet.AttachDispatch(m_ExlSheets.GetItem(_variant_t((long)2)),TRUE); 
	m_ExlSheet.Delete(); 

	//把第一个Sheet页面的名字改变为TestSheet 
	m_ExlSheet.AttachDispatch(m_ExlSheets.GetItem(_variant_t((long)1)),TRUE); 
	m_ExlSheet.SetName("订单资料"); 


	///////合并第一行单元格A1至D1////// 

	//加载要合并的单元格 
//	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("P1")),TRUE); 

//	m_ExlRge.Merge(_variant_t((long)0)); 

	////////设置表格内容//////// 

	m_ExlRge.AttachDispatch(m_ExlSheet.GetCells(),TRUE);//加载所有单元格 

//	m_ExlRge.SetItem(_variant_t((long)1),_variant_t((long)1),_variant_t("订单资料")); 

	m_ExlRge.SetItem(_variant_t((long)1),_variant_t((long)1),_variant_t("订单号")); 
	m_ExlRge.SetItem(_variant_t((long)1),_variant_t((long)2),_variant_t("客户姓名")); 
	m_ExlRge.SetItem(_variant_t((long)1),_variant_t((long)3),_variant_t("收单日期")); 
	m_ExlRge.SetItem(_variant_t((long)1),_variant_t((long)4),_variant_t("交货日期")); 
	m_ExlRge.SetItem(_variant_t((long)1),_variant_t((long)5),_variant_t("部门")); 
	m_ExlRge.SetItem(_variant_t((long)1),_variant_t((long)6),_variant_t("详细地址")); 
	m_ExlRge.SetItem(_variant_t((long)1),_variant_t((long)7),_variant_t("联系电话")); 
	m_ExlRge.SetItem(_variant_t((long)1),_variant_t((long)8),_variant_t("签单金额")); 
	m_ExlRge.SetItem(_variant_t((long)1),_variant_t((long)9),_variant_t("尺寸规格")); 
	m_ExlRge.SetItem(_variant_t((long)1),_variant_t((long)10),_variant_t("制作材料"));
	m_ExlRge.SetItem(_variant_t((long)1),_variant_t((long)11),_variant_t("颜色")); 
	m_ExlRge.SetItem(_variant_t((long)1),_variant_t((long)12),_variant_t("喷漆")); 
	m_ExlRge.SetItem(_variant_t((long)1),_variant_t((long)13),_variant_t("底座搭配")); 
	m_ExlRge.SetItem(_variant_t((long)1),_variant_t((long)14),_variant_t("精度要求")); 
	m_ExlRge.SetItem(_variant_t((long)1),_variant_t((long)15),_variant_t("误差范围"));
	m_ExlRge.SetItem(_variant_t((long)1),_variant_t((long)16),_variant_t("其他要求"));

	LVCOLUMN col;
	col.mask = LVCF_TEXT ;
	int Column ;
	CHeaderCtrl* pHeaderCtrl = m_list_baseinfo.GetHeaderCtrl();
	if (pHeaderCtrl != NULL)
	{
		Column = pHeaderCtrl->GetItemCount();
	}
	else
	{
		return;
	}
	int count = m_list_baseinfo.GetItemCount();
	int i=0,j=0;
	
	for(i=0;i<count;i++)
	{
		for(j=0;j<Column;j++)
		{
			CString strtmp = m_list_baseinfo.GetItemText(i,j);
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

BOOL CDialog_BaseInfo::PreTranslateMessage(MSG* pMsg) 
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

void CDialog_BaseInfo::OnSelchangeComboBaseinfo() 
{
	int indexSel = m_com_baseinfo.GetCurSel();	
	if(indexSel==1)
	{

		CDialog_Query_list *dlg_baseinfo=new CDialog_Query_list(); 
		dlg_baseinfo->Create(IDD_DIALOG_LIST_QUERY);
		dlg_baseinfo->ShowWindow(SW_SHOW);
	}

}

void CDialog_BaseInfo::OnModifyList() 
{
	CDialog_ModifyList	dlg;
	dlg.DoModal();
}
