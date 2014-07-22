// Dialog_ModifyList.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_ModifyList.h"
#include "Dialog_Login2.h"
#include "Dialog_progress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_ModifyList dialog


CDialog_ModifyList::CDialog_ModifyList(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_ModifyList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_ModifyList)
	m_design_server = FALSE;
	m_has_modeling = FALSE;
	m_modeling = FALSE;
	m_modeling_pring = FALSE;
	m_no_modeling = FALSE;
	m_scan = FALSE;
	m_enddate = 0;
	m_receivedate = 0;
	m_address = _T("");
	m_bill = _T("");
	m_bottom = _T("");
	m_color = _T("");
	m_department = _T("");
	m_error_range = _T("");
	m_listid = _T("");
	m_listname = _T("");
	m_material = _T("");
	m_money = _T("");
	m_print = _T("");
	m_people = _T("");
	m_phone = _T("");
	m_receivename = _T("");
	m_shine = _T("");
	m_size = _T("");
	m_totel_number = 0;
	m_usage = _T("");
	m_volume = _T("");
	m_true_number = 0;
	m_other = _T("");
	m_query_listid = _T("");
	m_str_reveive_time = _T("");
	m_str_end_date = _T("");
	m_urgent = FALSE;

	m_design_server1 = FALSE;
	m_has_modeling1 = FALSE;
	m_modeling1 = FALSE;
	m_modeling_pring1 = FALSE;
	m_no_modeling1 = FALSE;
	m_scan1 = FALSE;
	m_urgent1 = FALSE;
	m_totel_number1 = 0;
	//}}AFX_DATA_INIT
	CString m_str_reveive_time1 = _T("");
	CString m_str_end_date1 = _T("");
	CString	m_address1 = _T("");
	CString	m_bill1 = _T("");
	CString	m_bottom1 = _T("");
	CString	m_color1 = _T("");
	CString	m_department1 = _T("");
	CString	m_error_range1 = _T("");
	CString	m_listname1 = _T("");
	CString	m_material1 = _T("");
	CString	m_money1 = _T("");
	CString	m_print1 = _T("");
	CString	m_people1 = _T("");
	CString	m_phone1 = _T("");
	CString	m_receivename1 = _T("");
	CString	m_shine1 = _T("");
	CString	m_size1 = _T("");
	CString	m_usage1 = _T("");
	CString	m_volume1 = _T("");
	CString	m_other1 = _T("");
}


void CDialog_ModifyList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_ModifyList)
	DDX_Control(pDX, IDOK, m_btnok);
	DDX_Control(pDX, IDCANCEL, m_btncancel);
	DDX_Control(pDX, IDC_BUTTON1, m_btn1);
	DDX_Control(pDX, IDC_BUTTON_START_LIST, m_btnstartlist);
	DDX_Control(pDX, IDC_BUTTON_MODIFYLIST, m_btnmodifylist);
	DDX_Control(pDX, IDC_BUTTON_END_LIST, m_btnendlist);
	DDX_Control(pDX, IDC_COMBO_SHINE, m_ComShine);
	DDX_Control(pDX, IDC_COMBO_COLOR, m_ComColor);
	DDX_Control(pDX, IDC_COMBO_SIZE, m_ComSize);
	DDX_Control(pDX, IDC_COMBO_PAINT, m_ComPaint);
	DDX_Control(pDX, IDC_COMBO_MATERIAL, m_ComMaterial);
	DDX_Control(pDX, IDC_COMBO_DEPARTMENT, m_ComDepartment);
	DDX_Control(pDX, IDC_COMBO_BOTTOM, m_ComBottom);
	DDX_Control(pDX, IDC_COMBO_BILL, m_ComBill);
	DDX_Check(pDX, IDC_CHECK_DESIGN_SERVER, m_design_server);
	DDX_Check(pDX, IDC_CHECK_HAS_MODELING, m_has_modeling);
	DDX_Check(pDX, IDC_CHECK_MODELING, m_modeling);
	DDX_Check(pDX, IDC_CHECK_MODELING_PRINT, m_modeling_pring);
	DDX_Check(pDX, IDC_CHECK_NO_MODELING, m_no_modeling);
	DDX_Check(pDX, IDC_CHECK_SCAN, m_scan);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ENDDATE, m_enddate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_RECEIVEDATE, m_receivedate);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_address);
	DDX_Text(pDX, IDC_EDIT_ERRORRANGE, m_error_range);
	DDX_Text(pDX, IDC_EDIT_LISTID, m_listid);
	DDX_Text(pDX, IDC_EDIT_LISTTNAME, m_listname);
	DDX_Text(pDX, IDC_EDIT_MONDY, m_money);
	DDX_Text(pDX, IDC_EDIT_PEOPLE, m_people);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_phone);
	DDX_Text(pDX, IDC_EDIT_RECEIVE_NAME, m_receivename);
	DDX_Text(pDX, IDC_EDIT_USAGE, m_usage);
	DDX_Text(pDX, IDC_EDIT_VOLUEME, m_volume);
	DDX_Text(pDX, IDC_RICHEDIT_OTHER, m_other);
	DDX_Text(pDX, IDC_EDIT_QUERYLISTID, m_query_listid);
	DDX_Check(pDX, IDC_CHECK_URGENT, m_urgent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_ModifyList, CDialog)
	//{{AFX_MSG_MAP(CDialog_ModifyList)
	ON_BN_CLICKED(IDC_BUTTON1, OnQueryList)
	ON_BN_CLICKED(IDC_BUTTON_MODIFYLIST, OnModifylist)
	ON_BN_CLICKED(IDC_BUTTON_START_LIST, OnStartList)
	ON_BN_CLICKED(IDC_BUTTON_END_LIST, OnEndList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_ModifyList message handlers

BOOL CDialog_ModifyList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CTime time1 = CTime::GetCurrentTime();
	m_receivedate = time1;
	m_enddate = time1;
	m_people = g_user;
	m_department = g_department;
	m_ComDepartment.InsertString(0,"意造销售");
	m_ComDepartment.InsertString(1,"电商");
	m_ComDepartment.InsertString(2,"运营");
	m_ComDepartment.InsertString(3,"加盟");
	m_ComDepartment.InsertString(4,"研发");
	if(m_department.Compare("意造销售")==0)
		m_ComDepartment.SetCurSel(0);
	else if(m_department.Compare("电商")==0)
		m_ComDepartment.SetCurSel(1);
	else if(m_department.Compare("运营")==0)
		m_ComDepartment.SetCurSel(2);
	else if(m_department.Compare("加盟")==0)
		m_ComDepartment.SetCurSel(3);
	else if(m_department.Compare("研发")==0)
		m_ComDepartment.SetCurSel(4);
	m_ComSize.InsertString(0,"6cm半身单人");
	m_ComSize.InsertString(1,"12cm半身单人");
	m_ComSize.InsertString(2,"10cm全身单人");
	m_ComSize.InsertString(3,"13.14cm全身单人");
	m_ComSize.InsertString(4,"15cm全身单人");
	m_ComSize.InsertString(5,"19.9cm全身单人");
	m_ComSize.InsertString(6,"19.9cm婚纱全身单人");
	m_ComSize.InsertString(7,"28cm全身单人");
	m_ComSize.InsertString(8,"6cm车载半身单人");
	m_ComSize.InsertString(9,"6cm车载半身双人");
	m_ComSize.InsertString(10,"10cm车载全身单人");
	m_ComSize.InsertString(11,"10cm车载全身双人");
	m_ComSize.InsertString(12,"10cm动漫路飞");
	m_ComSize.InsertString(13,"10cm动漫美国队长");
	m_ComSize.InsertString(14,"10cm动漫蝙蝠侠");
	m_ComSize.InsertString(15,"10cm动漫德玛西亚");
	//m_ComSize.SetCurSel(0);
	m_ComMaterial.InsertString(0,"全彩660砂岩");
	m_ComMaterial.InsertString(1,"全彩4500塑料");
	m_ComMaterial.InsertString(2,"尼龙");
	m_ComMaterial.InsertString(3,"尼龙66");
	m_ComMaterial.InsertString(4,"RS6000白色树脂");
	m_ComMaterial.InsertString(5,"EDEN260白色高精");
	m_ComMaterial.InsertString(6,"EDEN260半透明高精");
	m_ComMaterial.InsertString(7,"透明高精");
	m_ComMaterial.InsertString(8,"橡胶");
	m_ComMaterial.InsertString(9,"ABS塑料");
	m_ComMaterial.InsertString(10,"PLA");
	m_ComMaterial.InsertString(11,"CNC");
	//m_ComMaterial.SetCurSel(0);
	m_ComColor.InsertString(0,"白");
	m_ComColor.InsertString(1,"全彩");
	m_ComColor.InsertString(2,"黑色");
	m_ComColor.InsertString(3,"无");
	//m_ComColor.SetCurSel(0);
	m_ComPaint.InsertString(0,"无");
	m_ComPaint.InsertString(1,"有");
	//m_ComPaint.SetCurSel(0);
	m_ComShine.InsertString(0,"细打磨");
	m_ComShine.InsertString(1,"无");
	//m_ComShine.SetCurSel(0);
	m_ComBottom.InsertString(0,"无");
	m_ComBottom.InsertString(1,"标配");
	m_ComBottom.InsertString(2,"水晶");
	//m_ComBottom.SetCurSel(0);
	m_ComBill.InsertString(0,"否");
	m_ComBill.InsertString(1,"是");
	//m_ComBill.SetCurSel(0);
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDialog_ModifyList::PreTranslateMessage(MSG* pMsg) 
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

void CDialog_ModifyList::OnQueryList() 
{
	UpdateData();
	CString csSql;
	m_query_listid.TrimLeft();
	m_query_listid.TrimRight();
	if (m_query_listid.IsEmpty())
	{	
		MessageBox("订单号为空，请输入","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
		return;
	}
	else
	{
		csSql.Format("select * from baseinfo where listid=\"%s\" ",m_query_listid);	
	}
	Dialog_progress *dlgpro;
	dlgpro=new Dialog_progress(); 
	dlgpro->Create(IDD_DIALOG_PROGRESS);
	if(g_openprocess)
		dlgpro->ShowWindow(SW_SHOW);
	else
		dlgpro->ShowWindow(SW_HIDE);
    MYSQL myCont;
    MYSQL_RES *result;
    MYSQL_ROW sql_row;
    int res;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
    {
		dlgpro->setpos(500);
        mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
        res=mysql_query(&myCont,csSql);//查询
        if(!res)
        {
			dlgpro->setpos(600);
            result=mysql_store_result(&myCont);//保存查询到的数据到result
			dlgpro->setpos(700);
		    if(result)
            {
                int j = 0;
                j=mysql_num_fields(result);//查看多少列
				unsigned __int64 num = mysql_num_rows(result);//行数
				int index = 0;
                sql_row=mysql_fetch_row(result);//获取具体的数据
				if(sql_row)
                {
					m_listid = sql_row[0];
					m_listname1 = m_listname = sql_row[1];
					m_true_number = atoi(sql_row[2]);
					m_material1 = m_material = sql_row[3];
					m_volume1 = m_volume = sql_row[4];
					m_str_reveive_time1 = m_str_reveive_time = sql_row[5];
					m_str_end_date1 = m_str_end_date = sql_row[6];
					m_people1 = m_people = sql_row[8];
					m_receivename1 = m_receivename = sql_row[9];
					m_phone1 = m_phone = sql_row[10];
					m_address1 = m_address = sql_row[11];
					m_department1 = m_department = sql_row[12];
					m_modeling1 = m_modeling = atoi(sql_row[13]);
					m_design_server1 = m_design_server = atoi(sql_row[14]);
					m_scan1 = m_scan = atoi(sql_row[15]);
					m_modeling_pring1 = m_modeling_pring = atoi(sql_row[16]);
					m_has_modeling1 = m_has_modeling = atoi(sql_row[17]);
					m_no_modeling1 = m_no_modeling = atoi(sql_row[18]);
					m_size1 = m_size = sql_row[19];
					m_totel_number1 = m_totel_number = atoi(sql_row[20]);
					m_color1 = m_color = sql_row[21];
					m_print1 = m_print = sql_row[22];
					m_shine1 = m_shine = sql_row[23];
					m_bottom1 = m_bottom = sql_row[24];
					m_bill1 = m_bill = sql_row[25];
					m_usage1 = m_usage = sql_row[26];
					m_error_range1 = m_error_range = sql_row[27];
					m_money1 = m_money = sql_row[28];
					m_other1 = m_other = sql_row[29];
					if(sql_row[32]!=NULL)
						m_urgent = atoi(sql_row[32]);
					else
						m_urgent = 0;
					m_urgent1 = m_urgent;
					GetDlgItem(IDC_EDIT_TOTEL_NUMBER)->SetWindowText(sql_row[20]);
					GetDlgItem(IDC_EDIT1_TRUE_NUMBER)->SetWindowText(sql_row[20]);
					GetDlgItem(IDC_RICHEDIT_OTHER)->SetWindowText(m_other);
					CTime timeTmp(atoi(m_str_reveive_time.Mid(0,4)),atoi(m_str_reveive_time.Mid(5,2)),atoi(m_str_reveive_time.Mid(8,2)),0,0,0,0);
					m_receivedate = timeTmp;
					CTime timeTmp1(atoi(m_str_end_date.Mid(0,4)),atoi(m_str_end_date.Mid(5,2)),atoi(m_str_end_date.Mid(8,2)),0,0,0,0);
					m_enddate = timeTmp1;
					if(m_department.Compare("意造销售")==0)
						m_ComDepartment.SetCurSel(0);
					else if(m_department.Compare("电商")==0)
						m_ComDepartment.SetCurSel(1);
					else if(m_department.Compare("运营")==0)
						m_ComDepartment.SetCurSel(2);
					else if(m_department.Compare("加盟")==0)
						m_ComDepartment.SetCurSel(3);
					else if(m_department.Compare("研发")==0)
						m_ComDepartment.SetCurSel(4);

					m_money = "******";
					if(((m_department.Compare("意造销售")==0) && (g_permission&MONEY_SELL))
						||((m_department.Compare("电商")==0) && (g_permission&MONEY_EC))
						||((m_department.Compare("运营")==0) && (g_permission&MONEY_RUN))
						||((m_department.Compare("加盟")==0) && (g_permission&MONEY_JOIN)))
						m_money = sql_row[28];
					

					if(m_size.Compare("6cm半身单人")==0)
						m_ComSize.SetCurSel(0);
					else if(m_size.Compare("12cm半身单人")==0)
						m_ComSize.SetCurSel(1);
					else if(m_size.Compare("10cm全身单人")==0)
						m_ComSize.SetCurSel(2);
					else if(m_size.Compare("13.14cm全身单人")==0)
						m_ComSize.SetCurSel(3);
					else if(m_size.Compare("15cm全身单人")==0)
						m_ComSize.SetCurSel(4);
					else if(m_size.Compare("19.9cm全身单人")==0)
						m_ComSize.SetCurSel(5);
					else if(m_size.Compare("19.9cm婚纱全身单人")==0)
						m_ComSize.SetCurSel(6);
					else if(m_size.Compare("28cm全身单人")==0)
						m_ComSize.SetCurSel(7);
					else if(m_size.Compare("6cm车载半身单人")==0)
						m_ComSize.SetCurSel(8);
					else if(m_size.Compare("6cm车载半身双人")==0)
						m_ComSize.SetCurSel(9);
					else if(m_size.Compare("10cm车载全身单人")==0)
						m_ComSize.SetCurSel(10);
					else if(m_size.Compare("10cm车载全身双人")==0)
						m_ComSize.SetCurSel(11);
					else if(m_size.Compare("10cm动漫路飞")==0)
						m_ComSize.SetCurSel(12);
					else if(m_size.Compare("10cm动漫美国队长")==0)
						m_ComSize.SetCurSel(13);
					else if(m_size.Compare("10cm动漫蝙蝠侠")==0)
						m_ComSize.SetCurSel(14);
					else if(m_size.Compare("10cm动漫德玛西亚")==0)
						m_ComSize.SetCurSel(15);
					else 
						m_ComSize.SetWindowText(m_size);

					if(m_material.Compare("全彩660砂岩")==0)
						m_ComMaterial.SetCurSel(0);
					else if(m_material.Compare("全彩4500塑料")==0)
						m_ComMaterial.SetCurSel(1);
					else if(m_material.Compare("尼龙")==0)
						m_ComMaterial.SetCurSel(2);
					else if(m_material.Compare("尼龙66")==0)
						m_ComMaterial.SetCurSel(3);
					else if(m_material.Compare("RS6000白色树脂")==0)
						m_ComMaterial.SetCurSel(4);
					else if(m_material.Compare("EDEN260白色高精")==0)
						m_ComMaterial.SetCurSel(5);
					else if(m_material.Compare("EDEN260半透明高精")==0)
						m_ComMaterial.SetCurSel(6);
					else if(m_material.Compare("透明高精")==0)
						m_ComMaterial.SetCurSel(7);
					else if(m_material.Compare("橡胶")==0)
						m_ComMaterial.SetCurSel(8);
					else if(m_material.Compare("ABS塑料")==0)
						m_ComMaterial.SetCurSel(9);
					else if(m_material.Compare("PLA")==0)
						m_ComMaterial.SetCurSel(10);
					else if(m_material.Compare("CNC")==0)
						m_ComMaterial.SetCurSel(11);
					else 
						m_ComMaterial.SetWindowText(m_material);
					
					if(m_color.Compare("白")==0)
						m_ComColor.SetCurSel(0);
					else if(m_color.Compare("全彩")==0)
						m_ComColor.SetCurSel(1);
					else if(m_color.Compare("黑色")==0)
						m_ComColor.SetCurSel(2);
					else if(m_color.Compare("无")==0)
						m_ComColor.SetCurSel(3);
					else 
						m_ComColor.SetWindowText(m_color);
				
					if(m_print.Compare("无")==0)
						m_ComPaint.SetCurSel(0);
					else if(m_print.Compare("有")==0)
						m_ComPaint.SetCurSel(1);
					else 
						m_ComPaint.SetWindowText(m_print);
					
					if(m_shine.Compare("细打磨")==0)
						m_ComShine.SetCurSel(0);
					else if(m_shine.Compare("无")==0)
						m_ComShine.SetCurSel(1);
					else 
						m_ComShine.SetWindowText(m_shine);

					if(m_bottom.Compare("无")==0)
						m_ComBottom.SetCurSel(0);
					else if(m_bottom.Compare("标配")==0)
						m_ComBottom.SetCurSel(1);
					else if(m_bottom.Compare("水晶")==0)
						m_ComBottom.SetCurSel(2);
					else 
						m_ComBottom.SetWindowText(m_bottom);

					if(m_bill.Compare("否")==0)
						m_ComBill.SetCurSel(0);
					else if(m_bill.Compare("是")==0)
						m_ComBill.SetCurSel(1);
					else 
						m_ComBill.SetWindowText(m_bill);
					dlgpro->setpos(900);
					dlgpro->endpos();
                    UpdateData(FALSE);
                }
				else
				{
					MessageBox("无此订单号，请重新输入","提示",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
					mysql_close(&myCont);//断开连接
					dlgpro->endpos();
					return;
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
			dlgpro->endpos();
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
		dlgpro->endpos();
		return;
    }
    if(result!=NULL) mysql_free_result(result);//释放结果资源
    mysql_close(&myCont);//断开连接

	return;
	
}

void CDialog_ModifyList::OnModifylist() 
{
	UpdateData();
	if(m_listid.IsEmpty())
	{
		MessageBox("无订单号，请重新输入","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
		return;
	}
	if(!(m_phone.IsEmpty()))
	{
		if(!IsPhoneNum(m_phone))
		{
			MessageBox("联系电话输入必须为数字，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_PHONE)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_PHONE))->SetSel(0, -1);
			return;	
		}
		int len = m_phone.GetLength();
		if(len!=11 && len!=12 && len!=15 && len!=16 && len!=17)
		{
			MessageBox("联系电话输入格式不正确，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_PHONE)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_PHONE))->SetSel(0, -1);
			return;	
		}
	}
	CString strTotalNum;
	GetDlgItem(IDC_EDIT_TOTEL_NUMBER)->GetWindowText(strTotalNum);
	if(!(strTotalNum.IsEmpty()))
	{
		if(!IsInt(strTotalNum))
		{
			MessageBox("生产数量输入必须为整数，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_TOTEL_NUMBER)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_TOTEL_NUMBER))->SetSel(0, -1);
			return;
		}
	}
	int totelnumber = m_totel_number = atoi(strTotalNum);;
	if(totelnumber<=0)
	{
		MessageBox("生产数量非法，请重新输入","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_TOTEL_NUMBER)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_TOTEL_NUMBER))->SetSel(0, -1);
		return;
	}
	if(!(m_money.IsEmpty()))
	{
		if(!IsNum(m_money))
		{
			MessageBox("金额输入必须为数字，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONDY)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONDY))->SetSel(0, -1);
			return;	
		}
		if(atof(m_money)>10000000)
		{
			MessageBox("金额超过上限一千万，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONDY)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONDY))->SetSel(0, -1);
			return;
		}
	}
	if(!(m_volume.IsEmpty()))
	{
		if(!IsNum(m_volume))
		{
			MessageBox("体积输入必须为数字，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_VOLUEME)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_VOLUEME))->SetSel(0, -1);
			return;	
		}
	}
	m_ComBill.GetWindowText(m_bill);
	m_ComBottom.GetWindowText(m_bottom);
	m_ComColor.GetWindowText(m_color);
	m_ComDepartment.GetWindowText(m_department);
	m_ComMaterial.GetWindowText(m_material);
	m_ComPaint.GetWindowText(m_print);
	m_ComShine.GetWindowText(m_shine);
	m_ComSize.GetWindowText(m_size);

	m_str_reveive_time.Format("%04d-%02d-%02d",m_receivedate.GetYear(),m_receivedate.GetMonth(),m_receivedate.GetDay());
	m_str_end_date.Format("%04d-%02d-%02d",m_enddate.GetYear(),m_enddate.GetMonth(),m_enddate.GetDay());

	Dialog_progress *dlgpro;
	dlgpro=new Dialog_progress(); 
	dlgpro->Create(IDD_DIALOG_PROGRESS);
	if(g_openprocess)
		dlgpro->ShowWindow(SW_SHOW);
	else
		dlgpro->ShowWindow(SW_HIDE);

	int isend = 0;
	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	mysql_init(&myCont);
	if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
	{
		dlgpro->setpos(500);
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
		CString sql;
		sql.Format("select * from schedule where listid=\"%s\" ",m_listid);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
			return;
		}
		dlgpro->setpos(600);
		result=mysql_store_result(&myCont);//保存查询到的数据到result
		if(result)
		{
			unsigned __int64 num = mysql_num_rows(result);//行数
			if(num==1)//已下单，
			{
				sql_row=mysql_fetch_row(result);
				if(sql_row)
				{
					isend = atoi(sql_row[10]);
					if(isend==1)
					{
						MessageBox("此订单号已被结单，不可在修改","提示",MB_OK);
						(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
						if(result!=NULL) mysql_free_result(result);//释放结果资源
						mysql_close(&myCont);//断开连接
						dlgpro->endpos();
						return;
					}
				}
				else
				{
					MessageBox("此订单号已被下单","提示",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
					if(result!=NULL) mysql_free_result(result);//释放结果资源
					mysql_close(&myCont);//断开连接
					dlgpro->endpos();
					return;
				}
				dlgpro->setpos(700);
				CDialog_Login2 login2;
				if(m_urgent)
					login2.m_urgent = 1;
				login2.m_permission = MODIFY_LIST_AFTER;
				if (login2.DoModal()!=IDOK)
				{
					MessageBox("此订单号已被下单，只有主管才有权限修改","提示",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
					if(result!=NULL) mysql_free_result(result);//释放结果资源
					mysql_close(&myCont);//断开连接
					dlgpro->endpos();
					return;
				}

				//添加变更记录到数据库
				CString strChangeRecord;
				CString tmp;
				if(m_listname.Compare(m_listname1)!=0)
				{
					tmp.Format("订单名称：%s -> %s； ",m_listname1,m_listname);
					strChangeRecord += tmp;
				}
				if(m_people.Compare(m_people1)!=0)
				{
					tmp.Format("经办人：%s -> %s； ",m_people1,m_people);
					strChangeRecord += tmp;
				}
				if(m_receivename.Compare(m_receivename1)!=0)
				{
					tmp.Format("收件人：%s -> %s； ",m_receivename1,m_receivename);
					strChangeRecord += tmp;
				}
				if(m_phone.Compare(m_phone1)!=0)
				{
					tmp.Format("联系电话：%s -> %s； ",m_phone1,m_phone);
					strChangeRecord += tmp;
				}
				if(m_address.Compare(m_address1)!=0)
				{
					tmp.Format("详细地址：%s -> %s； ",m_address1,m_address);
					strChangeRecord += tmp;
				}
				if(m_department.Compare(m_department1)!=0)
				{
					tmp.Format("部门：%s -> %s； ",m_department1,m_department);
					strChangeRecord += tmp;
				}
				if(m_str_reveive_time.Compare(m_str_reveive_time1)!=0)
				{
					tmp.Format("派单日期：%s -> %s； ",m_str_reveive_time1,m_str_reveive_time);
					strChangeRecord += tmp;
				}
				if(m_str_end_date.Compare(m_str_end_date1)!=0)
				{
					tmp.Format("交货日期：%s -> %s； ",m_str_end_date1,m_str_end_date);
					strChangeRecord += tmp;
				}
				if(m_modeling!=m_modeling1)
				{
					tmp.Format("建模：%d -> %d； ",m_modeling1,m_modeling);
					strChangeRecord += tmp;
				}
				if(m_design_server!=m_design_server1)
				{
					tmp.Format("设计服务：%d -> %d； ",m_design_server1,m_design_server);
					strChangeRecord += tmp;
				}
				if(m_scan!=m_scan1)
				{
					tmp.Format("扫描业务：%d -> %d； ",m_scan1,m_scan);
					strChangeRecord += tmp;
				}
				if(m_modeling_pring!=m_modeling_pring1)
				{
					tmp.Format("模型打印：%d -> %d； ",m_modeling_pring1,m_modeling_pring);
					strChangeRecord += tmp;
				}
				if(m_has_modeling!=m_has_modeling1)
				{
					tmp.Format("有模型：%d -> %d； ",m_has_modeling1,m_has_modeling);
					strChangeRecord += tmp;
				}
				if(m_no_modeling!=m_no_modeling1)
				{
					tmp.Format("无模型：%d -> %d； ",m_no_modeling1,m_no_modeling);
					strChangeRecord += tmp;
				}
				if(m_urgent!=m_urgent1)
				{
					tmp.Format("加急：%d -> %d； ",m_urgent1,m_urgent);
					strChangeRecord += tmp;
				}

				if(m_size.Compare(m_size1)!=0)
				{
					tmp.Format("尺寸：%s -> %s； ",m_size1,m_size);
					strChangeRecord += tmp;
				}
				if(m_totel_number!=m_totel_number1)
				{
					tmp.Format("生产数量：%d -> %d； ",m_totel_number1,m_totel_number);
					strChangeRecord += tmp;
				}

				if(m_material.Compare(m_material1)!=0)
				{
					tmp.Format("制作材料：%s -> %s； ",m_material1,m_material);
					strChangeRecord += tmp;
				}
				if(m_color.Compare(m_color1)!=0)
				{
					tmp.Format("颜色：%s -> %s； ",m_color1,m_color);
					strChangeRecord += tmp;
				}
				if(m_print.Compare(m_print1)!=0)
				{
					tmp.Format("喷漆：%s -> %s； ",m_print1,m_print);
					strChangeRecord += tmp;
				}
				if(m_shine.Compare(m_shine1)!=0)
				{
					tmp.Format("打磨：%s -> %s； ",m_shine1,m_shine);
					strChangeRecord += tmp;
				}
				if(m_bottom.Compare(m_bottom1)!=0)
				{
					tmp.Format("底座搭配：%s -> %s； ",m_bottom1,m_bottom);
					strChangeRecord += tmp;
				}
				if(m_bill.Compare(m_bill1)!=0)
				{
					tmp.Format("发票随寄：%s -> %s； ",m_bill1,m_bill);
					strChangeRecord += tmp;
				}
				if(m_usage.Compare(m_usage1)!=0)
				{
					tmp.Format("用途：%s -> %s； ",m_usage1,m_usage);
					strChangeRecord += tmp;
				}
				if(m_error_range.Compare(m_error_range1)!=0)
				{
					tmp.Format("误差范围：%s -> %s； ",m_error_range1,m_error_range);
					strChangeRecord += tmp;
				}
				if(m_money.Compare(m_money1)!=0)
				{
					tmp.Format("签单金额：%s -> %s； ",m_money1,m_money);
					strChangeRecord += tmp;
				}
				if(m_volume.Compare(m_volume1)!=0)
				{
					tmp.Format("体积：%s -> %s； ",m_volume1,m_volume);
					strChangeRecord += tmp;
				}
				if(m_other.Compare(m_other1)!=0)
				{
					tmp.Format("其他要求：%s -> %s； ",m_other1,m_other);
					strChangeRecord += tmp;
				}

				CString starttime;
				CString strsql ;
				strsql.Format("select now()");
				if(mysql_query(&myCont,strsql)!= 0)
				{
					const char *error = mysql_error(&myCont);
					CString str;
					str.Format("数据库错误(%s)",error);
					MessageBox(str,"提示",MB_OK);
					mysql_close(&myCont);//断开连接
					dlgpro->endpos();
					return;
				}
				result=mysql_store_result(&myCont);//保存查询到的数据到result
				if(result)
				{
					sql_row=mysql_fetch_row(result);
					starttime = sql_row[0];
				}
				else
				{
					const char *error = mysql_error(&myCont);
					CString str;
					str.Format("数据库错误(%s)",error);
					MessageBox(str,"提示",MB_OK);
					mysql_close(&myCont);//断开连接
					dlgpro->endpos();
					return;
				}
				dlgpro->setpos(800);
				sql.Format("insert into changerecord values (%d,\"%s\",\"%s\",\"%s\",\"%s\")", 0,m_listid,starttime,login2.m_user,strChangeRecord);
				if(mysql_query(&myCont,sql)!= 0)
				{
					const char *error = mysql_error(&myCont);
					CString str;
					str.Format("数据库错误(%s)",error);
					MessageBox(str,"提示",MB_OK);
					mysql_close(&myCont);//断开连接
					dlgpro->endpos();
					return;
				}
				writelog("插入变更记录成功");
			}
			else//未下单
			{
				CDialog_Login2 login2;
				if(m_urgent)
					login2.m_urgent = 1;
				login2.m_permission = MODIFY_LIST_BEFORE;
				if (login2.DoModal()!=IDOK)
				{
					if(result!=NULL) mysql_free_result(result);//释放结果资源
					mysql_close(&myCont);//断开连接
					dlgpro->endpos();
					return;
				}
				dlgpro->setpos(700);
				sql.Format("select savelistpeople from baseinfo where listid=\"%s\" ",m_listid);
				if(mysql_query(&myCont,sql)!= 0)
				{
					const char *error = mysql_error(&myCont);
					CString str;
					str.Format("数据库错误(%s)",error);
					MessageBox(str,"提示",MB_OK);
					mysql_close(&myCont);//断开连接
					dlgpro->endpos();
					return;
				}
				dlgpro->setpos(800);
				result=mysql_store_result(&myCont);//保存查询到的数据到result
				if(result)
				{
					sql_row=mysql_fetch_row(result);
					if(sql_row==NULL)
					{
						MessageBox("无此订单号，请重新输入","提示",MB_OK);
						(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
						mysql_close(&myCont);//断开连接
						dlgpro->endpos();
						return;
					}
					if(strcmp(sql_row[0],login2.m_user))
					{
						if (m_urgent==0)
						{
							MessageBox("只有提交订单本人才能修改此订单","提示",MB_OK);
							(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
							((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
							if(result!=NULL) mysql_free_result(result);//释放结果资源
							mysql_close(&myCont);//断开连接
							dlgpro->endpos();
							return;
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
					dlgpro->endpos();
					return;
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
			dlgpro->endpos();
			return;
		}

		sql.Format("update baseinfo set listname=\"%s\",truelistnumber=%d,material=\"%s\",volume=\"%s\",reveivedate=\"%s\",enddate=\"%s\",people=\"%s\",receivepeople=\"%s\",phone=\"%s\",address=\"%s\",department=\"%s\", modeling=%d, designserver=%d, scan=%d, modlingprint=%d, hasmodeling=%d, nomodeling=%d,  size=\"%s\",totelnumber=%d,color=\"%s\",paint=\"%s\",shine=\"%s\",bottom=\"%s\",bill=\"%s\",usage1=\"%s\",errorrange=\"%s\",money=\"%s\",other=\"%s\" ,urgent=%d where listid=\"%s\" ", \
		m_listname,m_true_number, m_material, m_volume, m_str_reveive_time,m_str_end_date, m_people,m_receivename ,m_phone, m_address,m_department , \
		m_modeling,m_design_server, m_scan, m_modeling_pring,m_has_modeling,m_no_modeling,m_size ,m_totel_number, \
		m_color,m_print,m_shine,m_bottom, m_bill, m_usage ,m_error_range ,m_money,m_other,m_urgent,m_listid);
		dlgpro->setpos(900);
		int ret = mysql_query(&myCont,sql);
		const char *error = mysql_error(&myCont);
		if(ret!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
			return;
		}
		dlgpro->setpos(950);
		dlgpro->endpos();
		if(mysql_affected_rows(&myCont)>0)
		{
			MessageBox("修改订单成功","提示",MB_OK);
		}
		else
		{
			MessageBox("修改订单失败，可能数据没有变化","提示",MB_OK);
		}
	}
	else
	{
		const char *error = mysql_error(&myCont);
		CString str;
		str.Format("数据库错误(%s)",error);
		MessageBox(str,"提示",MB_OK);
		mysql_close(&myCont);//断开连接
		dlgpro->endpos();
		return;
	}
	mysql_close(&myCont);//断开连接
	//MessageBox("修改订单成功","提示",MB_OK); 
}

void CDialog_ModifyList::OnStartList() 
{
	UpdateData();
	if(m_listid.IsEmpty())
	{
		MessageBox("无订单号，请重新输入","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
		return;
	}
	CString strTotalNum;
	GetDlgItem(IDC_EDIT1_TRUE_NUMBER)->GetWindowText(strTotalNum);
	if(!(strTotalNum.IsEmpty()))
	{
		if(!IsInt(strTotalNum))
		{
			MessageBox("下单数量输入必须为整数，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT1_TRUE_NUMBER)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT1_TRUE_NUMBER))->SetSel(0, -1);
			return;
		}
	}
	int totelnumber = m_true_number = atoi(strTotalNum);;
	if(totelnumber<=0)
	{
		MessageBox("订单总数非法，请重新输入","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT1_TRUE_NUMBER)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT1_TRUE_NUMBER))->SetSel(0, -1);
		return;
	}

	CDialog_Login2 login2;
	login2.m_permission = START_LIST;
	if (login2.DoModal()!=IDOK)
	{
		return;
	}

	Dialog_progress *dlgpro;
	dlgpro=new Dialog_progress(); 
	dlgpro->Create(IDD_DIALOG_PROGRESS);
	if(g_openprocess)
		dlgpro->ShowWindow(SW_SHOW);
	else
		dlgpro->ShowWindow(SW_HIDE);

	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	mysql_init(&myCont);
	if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
	{
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
		dlgpro->setpos(500);
		CString sql;
		sql.Format("select * from schedule where listid=\"%s\" ",m_listid);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
			return;
		}
		dlgpro->setpos(600);
		result=mysql_store_result(&myCont);//保存查询到的数据到result
		if(result)
		{
			unsigned __int64 num = mysql_num_rows(result);//行数
			if(num==1)
			{
				MessageBox("此订单号已存在","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//释放结果资源
				mysql_close(&myCont);//断开连接
				dlgpro->endpos();
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
			dlgpro->endpos();
			return;
		}

/*		sql.Format("select savelistpeople from baseinfo where listid=\"%s\" ",m_listid);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			return;
		}
		result=mysql_store_result(&myCont);//保存查询到的数据到result
		if(result)
		{
			sql_row=mysql_fetch_row(result);
			if(strcmp(sql_row[0],login2.m_user))
			{
				MessageBox("下单人与接单人不一致","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//释放结果资源
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
*/
		dlgpro->setpos(700);
		sql.Format("insert into schedule(listid,listname,totelnumber,businessnumber,tcnumber,pdnumber,qcnumber,storagenumber,sendnumber,post,end,hasstoragenumber) \
		values (\"%s\",\"%s\",%d,0,%d,0,0,0,0,0,0,0)",m_listid,m_listname,totelnumber,totelnumber);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
			return;
		}
		CTime time = CTime::GetCurrentTime();
		CString starttime;

		CString strsql ;
		strsql.Format("select now()");
		if(mysql_query(&myCont,strsql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
			return;
		}
		result=mysql_store_result(&myCont);//保存查询到的数据到result
		if(result)
		{
			sql_row=mysql_fetch_row(result);
			starttime = sql_row[0];
		}
		else
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
			return;
		}
		dlgpro->setpos(800);
		sql.Format("insert into scheduledetail(listid,businessendtime,businessnumber,businesspeople,tcstarttime) \
		values (\"%s\",\"%s\",%d,\"%s\",\"%s\")",m_listid,starttime,totelnumber,login2.m_user,starttime);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
			return;
		}
		dlgpro->setpos(900);
		sql.Format("update baseinfo set truelistnumber=%d  where listid=\"%s\" " ,m_true_number,m_listid);
		if(mysql_query(&myCont,sql)!= 0)
		{
			MessageBox("提交数据库失败","提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
			return ;
		}
		dlgpro->endpos();
		if(mysql_affected_rows(&myCont)>0)
		{
			MessageBox("下单成功","提示",MB_OK);
		}
		else
		{
			MessageBox("下单成功","提示",MB_OK);
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
	mysql_close(&myCont);//断开连接
	//MessageBox("下单成功","提示",MB_OK);
	
}

void CDialog_ModifyList::OnEndList() 
{
	UpdateData();
	if(m_listid.IsEmpty())
	{
		MessageBox("无订单号，请重新输入","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
		return;
	}
	CDialog_Login2 login2;
	login2.m_permission = END_LIST;
	if (login2.DoModal()!=IDOK)
	{
		return;
	}
	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	mysql_init(&myCont);
	if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
	{
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
		CString sql;
		CTime time = CTime::GetCurrentTime();
		CString starttime;

		CString strsql ;
		strsql.Format("select now()");
		if(mysql_query(&myCont,strsql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			return;
		}
		result=mysql_store_result(&myCont);//保存查询到的数据到result
		if(result)
		{
			sql_row=mysql_fetch_row(result);
			starttime = sql_row[0];
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
		
		
		strsql.Format("select totelnumber,post,end from schedule where listid=\"%s\" ",m_listid);
		if(mysql_query(&myCont,strsql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			return;
		}
		result=mysql_store_result(&myCont);//保存查询到的数据到result
		if(result)
		{
			unsigned __int64 num = mysql_num_rows(result);//行数
			if(num<1)
			{
				MessageBox("此订单不存在","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//释放结果资源
				mysql_close(&myCont);//断开连接
				return;
			}
			sql_row=mysql_fetch_row(result);
			if(sql_row==NULL)
			{
				MessageBox("此订单不存在","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//释放结果资源
				mysql_close(&myCont);//断开连接
				return;
			}
			if(atoi(sql_row[1])<atoi(sql_row[0]))
			{	
				CString strerr;
				strerr.Format("订单 %s 还有 %d 个没有经过物流过账.",m_listid,atoi(sql_row[0])-atoi(sql_row[1]));
				MessageBox(strerr,"提示",MB_OK);
				if(result!=NULL) mysql_free_result(result);//释放结果资源
				mysql_close(&myCont);//断开连接
				return;
			}
			if(atoi(sql_row[2])==1)
			{
				MessageBox("此订单已结单","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//释放结果资源
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


		sql.Format("update schedule set end=%d where listid=\"%s\" " ,1,m_listid);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			return;
		}
		if(mysql_affected_rows(&myCont)>0)
		{
			MessageBox("结单成功","提示",MB_OK);
		}
		else
		{
			MessageBox("结单失败","提示",MB_OK);
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
	mysql_close(&myCont);//断开连接
	//MessageBox("结单成功","提示",MB_OK);
	
}

void CDialog_ModifyList::OnOK() 
{
	// TODO: Add extra validation here
	OnQueryList();
	//CDialog::OnOK();
}
