// Dialog_New_List.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_New_List.h"
#include "Dialog_Login2.h"
#include "Dialog_progress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_New_List dialog


CDialog_New_List::CDialog_New_List(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_New_List::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_New_List)
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
	m_str_reveive_time = _T("");
	m_str_end_date = _T("");
	m_urgent = FALSE;
	//}}AFX_DATA_INIT
}


void CDialog_New_List::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_New_List)
	DDX_Control(pDX, IDC_DATETIMEPICKER_ENDDATE, m_ctrlEndDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_RECEIVEDATE, m_ctrlReveiveDate);
	DDX_Control(pDX, IDC_BUTTON_EXCEL, m_btexcel);
	DDX_Control(pDX, IDC_BUTTON_PRINT, m_btprint);
	DDX_Control(pDX, IDC_BUTTON_PREVIEW, m_btpreview);
	DDX_Control(pDX, IDOK, m_btnok);
	DDX_Control(pDX, IDCANCEL, m_btncancel);
	DDX_Control(pDX, IDC_BUTTON_SUBMITLIST, m_btnsubmitlist);
	DDX_Control(pDX, IDC_BUTTON_START_LIST, m_btnstartlist);
	DDX_Control(pDX, IDC_BUTTON_END_LIST, m_btnendlist);
	DDX_Control(pDX, IDC_COMBO_SIZE, m_ComSize);
	DDX_Control(pDX, IDC_COMBO_SHINE, m_ComShine);
	DDX_Control(pDX, IDC_COMBO_PAINT, m_ComPaint1);
	DDX_Control(pDX, IDC_COMBO_MATERIAL, m_ComMaterial);
	DDX_Control(pDX, IDC_COMBO_DEPARTMENT, m_ComDepartment);
	DDX_Control(pDX, IDC_COMBO_COLOR, m_ComColor);
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
	DDX_Check(pDX, IDC_CHECK_URGENT, m_urgent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_New_List, CDialog)
	//{{AFX_MSG_MAP(CDialog_New_List)
	ON_BN_CLICKED(IDC_BUTTON_END_LIST, OnEndList)
	ON_BN_CLICKED(IDC_BUTTON_START_LIST, OnStartList)
	ON_BN_CLICKED(IDC_BUTTON_SUBMITLIST, OnSubmitlist)
	ON_CBN_SELCHANGE(IDC_COMBO_DEPARTMENT, OnSelchangeComboDepartment)
	ON_BN_CLICKED(IDC_BUTTON_PREVIEW, OnButtonPreview)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnButtonPrint)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL, OnButtonExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_New_List message handlers

BOOL CDialog_New_List::OnInitDialog() 
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
	m_ComSize.SetCurSel(-1);
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
	m_ComMaterial.InsertString(12,"蓝蜡");
	m_ComMaterial.InsertString(13,"透明树脂");
	m_ComMaterial.InsertString(14,"半透明树脂");
	m_ComMaterial.InsertString(15,"CNC铝合金");
	m_ComMaterial.InsertString(16,"CNC ABS");
	m_ComMaterial.SetCurSel(0);
	m_ComColor.InsertString(0,"白");
	m_ComColor.InsertString(1,"全彩");
	m_ComColor.InsertString(2,"黑色");
	m_ComColor.InsertString(3,"无");
	m_ComColor.SetCurSel(0);
	m_ComPaint1.InsertString(0,"无");
	m_ComPaint1.InsertString(1,"有");
	m_ComPaint1.SetCurSel(0);
	m_ComShine.InsertString(0,"细打磨");
	m_ComShine.InsertString(1,"无");
	m_ComShine.SetCurSel(0);
	m_ComBottom.InsertString(0,"无");
	m_ComBottom.InsertString(1,"标配");
	m_ComBottom.InsertString(2,"水晶");
	m_ComBottom.SetCurSel(0);
	m_ComBill.InsertString(0,"否");
	m_ComBill.InsertString(1,"是");
	m_ComBill.SetCurSel(0);

	if(m_department.Compare("意造销售")==0)
	{
		m_ComDepartment.SetCurSel(0);
		m_ComMaterial.SetCurSel(4);
		m_ComShine.SetCurSel(0);
	}
	else if(m_department.Compare("电商")==0)
	{
		m_ComDepartment.SetCurSel(1);
		m_ComMaterial.SetCurSel(10);
		m_ComShine.SetCurSel(1);
	}
	else if(m_department.Compare("运营")==0)
	{
		m_ComDepartment.SetCurSel(2);
		m_ComMaterial.SetCurSel(0);
		m_ComShine.SetCurSel(0);
	}
	else if(m_department.Compare("加盟")==0)
	{
		m_ComDepartment.SetCurSel(3);
		m_ComMaterial.SetCurSel(0);
		m_ComShine.SetCurSel(0);
	}
	else if(m_department.Compare("研发")==0)
	{
		m_ComDepartment.SetCurSel(4);
		m_ComMaterial.SetCurSel(-1);
		m_ComSize.SetCurSel(-1);
	}

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_New_List::OnSubmitlist() 
{
	// TODO: Add your control notification handler code here
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
	int totelnumber = m_totel_number = atoi(strTotalNum);
	if(totelnumber<=0)
	{
		MessageBox("生产数量非法，请重新输入","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_TOTEL_NUMBER)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_TOTEL_NUMBER))->SetSel(0, -1);
		return;
	}
	GetDlgItem(IDC_EDIT1_TRUE_NUMBER)->SetWindowText(strTotalNum);
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
	m_ComPaint1.GetWindowText(m_print);
	m_ComShine.GetWindowText(m_shine);
	m_ComSize.GetWindowText(m_size);
	CDialog_Login2 login2;
	if(m_urgent)
		login2.m_urgent = 1;
	login2.m_permission = SAVE_LIST;
	if (login2.DoModal()!=IDOK)
	{
		return;
	}
	m_str_reveive_time.Format("%04d-%02d-%02d",m_receivedate.GetYear(),m_receivedate.GetMonth(),m_receivedate.GetDay());
	m_str_end_date.Format("%04d-%02d-%02d",m_enddate.GetYear(),m_enddate.GetMonth(),m_enddate.GetDay());
	CString sql;
	
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
		dlgpro->setpos(500);
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
		sql.Format("select * from baseinfo where listid=\"%s\" ",m_listid);
		if(mysql_query(&myCont,sql)!= 0)
		{
			dlgpro->endpos();
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			return;
		}
		dlgpro->setpos(600);
		result=mysql_store_result(&myCont);//保存查询到的数据到result
		if(result)
		{
			unsigned __int64 num = mysql_num_rows(result);//行数
			if(num==1)
			{
				dlgpro->endpos();
				MessageBox("此订单已被提交，请重新创建订单号","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//释放结果资源
				mysql_close(&myCont);//断开连接
				return;
			}
		}
		else
		{
			dlgpro->endpos();
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			return;
		}

		dlgpro->setpos(700);
		CString starttime;
		sql.Format("select now()");
		if(mysql_query(&myCont,sql)!= 0)
		{
			dlgpro->endpos();
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

		sql.Format("insert into baseinfo(listid,listname,truelistnumber,material,volume,reveivedate,enddate,sendid,people,receivepeople,phone,address,department,modeling,designserver,scan,modlingprint,hasmodeling,nomodeling,size,totelnumber,color,paint,shine,bottom,bill,usage1,errorrange,money,other,savelisttime,savelistpeople,urgent)  \
			   values (\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\", \
		%d, %d, %d, %d, %d, %d,  \"%s\",%d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d)", \
		m_listid,m_listname,m_true_number, m_material, m_volume, m_str_reveive_time,m_str_end_date,"", m_people,m_receivename ,m_phone, m_address,m_department , \
		m_modeling,m_design_server, m_scan, m_modeling_pring,m_has_modeling,m_no_modeling,m_size ,m_totel_number, \
		m_color,m_print,m_shine,m_bottom, m_bill, m_usage ,m_error_range ,m_money,m_other,starttime,login2.m_user,m_urgent);
		dlgpro->setpos(900);
		if(mysql_query(&myCont,sql)!= 0)
		{
			dlgpro->endpos();
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			return;
		}
		dlgpro->setpos(950);
		sql.Format("insert into fiproceeds(listid,moneytotel,peoplebusiness,moneyproceeds,moneybill) values (\"%s\",\"%s\",\"%s\",0,0)",m_listid,m_money,m_people);
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

		dlgpro->endpos();
		if(mysql_affected_rows(&myCont)>0)
		{
			MessageBox("保存订单成功","提示",MB_OK);			
		}
		else
		{
			MessageBox("保存订单失败","提示",MB_OK);
		}
		GetDlgItem(IDC_BUTTON_START_LIST)->EnableWindow(TRUE);
	}
	else
	{
		dlgpro->endpos();
		const char *error = mysql_error(&myCont);
		CString str;
		str.Format("数据库错误(%s)",error);
		MessageBox(str,"提示",MB_OK);
		mysql_close(&myCont);//断开连接
		return;
	}
	mysql_close(&myCont);//断开连接
	//MessageBox("保存订单成功","提示",MB_OK);
}

void CDialog_New_List::OnStartList() 
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
	int totelnumber = m_true_number = atoi(strTotalNum);
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
		sql.Format("insert into schedule(listid,listname,totelnumber,businessnumber,tcnumber,pdnumber,qcnumber,storagenumber,sendnumber,post,end,hasstoragenumber,undolist) \
		values (\"%s\",\"%s\",%d,0,%d,0,0,0,0,0,0,0,0)",m_listid,m_listname,totelnumber,totelnumber);
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
		dlgpro->setpos(800);
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
		dlgpro->setpos(900);
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
		dlgpro->setpos(950);
		sql.Format("update baseinfo set truelistnumber=%d  where listid=\"%s\" " ,m_true_number,m_listid);
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
		if(mysql_affected_rows(&myCont)>0)
		{
			MessageBox("下单成功","提示",MB_OK);
			dlgpro->endpos();
		}
		else
		{
			MessageBox("下单成功","提示",MB_OK);
			dlgpro->endpos();
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
	//MessageBox("下单成功","提示",MB_OK);
	
}

void CDialog_New_List::OnEndList() 
{
	return;
	UpdateData();
	if(m_listid.IsEmpty())
	{
		MessageBox("无订单号，请重新输入","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
		return;
	}
	
}

BOOL CDialog_New_List::PreTranslateMessage(MSG* pMsg) 
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

void CDialog_New_List::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CDialog_New_List::OnSelchangeComboDepartment() 
{
	// TODO: Add your control notification handler code here
	int index = m_ComDepartment.GetCurSel();
	switch (index)
	{
	case 0://意造销售
		m_ComMaterial.SetCurSel(4);
		m_ComShine.SetCurSel(0);
		break;
	case 1://电商
		m_ComMaterial.SetCurSel(10);
		m_ComShine.SetCurSel(1);
		break;
	case 2://运营
		m_ComMaterial.SetCurSel(0);
		m_ComShine.SetCurSel(0);
		break;
	case 3://加盟
		m_ComMaterial.SetCurSel(0);
		m_ComShine.SetCurSel(0);
		break;
	case 4://研发
		m_ComMaterial.SetCurSel(-1);
		m_ComSize.SetCurSel(-1);
		break;
	default:
		m_ComMaterial.SetCurSel(-1);
		m_ComSize.SetCurSel(-1);
		break;
	}
	
}

void CDialog_New_List::SetPreviewDlg(CPreview *PreviewDlg)
{
	UpdateData();
	updatedlg();
	PreviewDlg->m_str_reveive_time = m_str_reveive_time;
	PreviewDlg->m_str_end_date = m_str_end_date;
		CString strtmp;
	if(m_design_server)
		strtmp.Format("%s","√");
	else
		strtmp.Format("%s"," ");
	PreviewDlg->m_design_server = strtmp;
	if(m_has_modeling)
		strtmp.Format("%s","√");
	else
		strtmp.Format("%s"," ");
	PreviewDlg->m_has_modeling = strtmp;
	if(m_modeling)
		strtmp.Format("%s","√");
	else
		strtmp.Format("%s"," ");
	PreviewDlg->m_modeling = strtmp;
	if(m_modeling_pring)
		strtmp.Format("%s","√");
	else
		strtmp.Format("%s"," ");
	PreviewDlg->m_modeling_pring = strtmp;
	if(m_no_modeling)
		strtmp.Format("%s","√");
	else
		strtmp.Format("%s"," ");
	PreviewDlg->m_no_modeling = strtmp;
	if(m_scan)
		strtmp.Format("%s","√");
	else
		strtmp.Format("%s"," ");
	PreviewDlg->m_scan = strtmp;
	if(m_urgent)
		strtmp.Format("%s","√");
	else
		strtmp.Format("%s"," ");
	PreviewDlg->m_urgent = strtmp;
	
	PreviewDlg->m_address = m_address;
	PreviewDlg->m_bill = m_bill;
	PreviewDlg->m_bottom = m_bottom;
	PreviewDlg->m_color = m_color;
	PreviewDlg->m_department = m_department;
	PreviewDlg->m_error_range = m_error_range;
	PreviewDlg->m_listid = m_listid;
	PreviewDlg->m_listname = m_listname;
	PreviewDlg->m_material = m_material;
	PreviewDlg->m_money = m_money;
	PreviewDlg->m_print = m_print;
	PreviewDlg->m_people = m_people;
	PreviewDlg->m_phone = m_phone;
	PreviewDlg->m_receivename = m_receivename;
	PreviewDlg->m_shine = m_shine;
	PreviewDlg->m_size = m_size;
	PreviewDlg->m_usage = m_usage;
	PreviewDlg->m_volume = m_volume;
	PreviewDlg->m_other = m_other;

	strtmp.Format("%d",m_totel_number);
	PreviewDlg->m_totel_number = strtmp;
	strtmp.Format("%d",m_true_number);
	PreviewDlg->m_true_number = strtmp;
	
}


void CDialog_New_List::OnButtonPreview() 
{
	// TODO: Add your control notification handler code here
	CPreview PreviewDlg;
	SetPreviewDlg(&PreviewDlg);
	PreviewDlg.DoModal();
}

void CDialog_New_List::OnButtonPrint() 
{
	CPreview PreviewDlg;
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
		PreviewDlg.DrawReport(m_rect,&dc1,true);
	}		
}

void CDialog_New_List::updatedlg() 
{
	m_ComBill.GetWindowText(m_bill);
	m_ComBottom.GetWindowText(m_bottom);
	m_ComColor.GetWindowText(m_color);
	m_ComDepartment.GetWindowText(m_department);
	m_ComMaterial.GetWindowText(m_material);
	m_ComPaint1.GetWindowText(m_print);
	m_ComShine.GetWindowText(m_shine);
	m_ComSize.GetWindowText(m_size);
	m_str_reveive_time.Format("%04d-%02d-%02d",m_receivedate.GetYear(),m_receivedate.GetMonth(),m_receivedate.GetDay());
	m_str_end_date.Format("%04d-%02d-%02d",m_enddate.GetYear(),m_enddate.GetMonth(),m_enddate.GetDay());
	CString strTotalNum;
	GetDlgItem(IDC_EDIT_TOTEL_NUMBER)->GetWindowText(strTotalNum);
	m_totel_number = atoi(strTotalNum);
}

void CDialog_New_List::OnButtonExcel() 
{
	UpdateData();
	updatedlg();	
	CString filename ;
	filename.Format("%s-生产派单表-%s.xls",m_department,m_listid);
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
	strtmp.Format("%s 生产派单表",m_department);
	m_ExlSheet.SetName(strtmp); 

	m_ExlRge.AttachDispatch(m_ExlSheet.GetCells(),TRUE);//加载所有单元格
	m_ExlRge.SetNumberFormatLocal(COleVariant("@")); 

	//合并单元格
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("F1")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"),_variant_t("F2")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A7"),_variant_t("F7")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A14"),_variant_t("F14")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("B6"),_variant_t("F6")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("B13"),_variant_t("F13")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("D12"),_variant_t("F12")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));


	////////设置表格内容//////// 

	m_ExlRge.AttachDispatch(m_ExlSheet.GetCells(),TRUE);//加载所有单元格 
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(1)),_variant_t(strtmp));

	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(1)),_variant_t("基本资料"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(1)),_variant_t("订单号"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(2)),_variant_t(m_listid));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(3)),_variant_t("订单名称"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(4)),_variant_t(m_listname));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(5)),_variant_t("经办人"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(6)),_variant_t(m_people));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(1)),_variant_t("收件人"));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(2)),_variant_t(m_receivename));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(3)),_variant_t("联系电话"));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(4)),_variant_t(m_phone));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(5)),_variant_t("部门"));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(6)),_variant_t(m_department));
	m_ExlRge.SetItem(_variant_t((long)(5)),_variant_t((long)(1)),_variant_t("派单日期"));
	m_ExlRge.SetItem(_variant_t((long)(5)),_variant_t((long)(2)),_variant_t(m_str_reveive_time));
	m_ExlRge.SetItem(_variant_t((long)(5)),_variant_t((long)(3)),_variant_t("交货日期"));
	m_ExlRge.SetItem(_variant_t((long)(5)),_variant_t((long)(4)),_variant_t(m_str_end_date));
	m_ExlRge.SetItem(_variant_t((long)(6)),_variant_t((long)(1)),_variant_t("详细地址"));
	m_ExlRge.SetItem(_variant_t((long)(6)),_variant_t((long)(2)),_variant_t(m_address));

	m_ExlRge.SetItem(_variant_t((long)(7)),_variant_t((long)(1)),_variant_t("制作要求"));
	if(m_modeling)
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(1)),_variant_t("建模 √"));
	else
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(1)),_variant_t("建模"));
	if(m_design_server)
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(2)),_variant_t("设计服务 √"));
	else
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(2)),_variant_t("设计服务"));
	if(m_scan)
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(3)),_variant_t("扫描业务 √"));
	else
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(3)),_variant_t("扫描业务"));
	if(m_modeling_pring)
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(4)),_variant_t("模型打印 √"));
	else
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(4)),_variant_t("模型打印"));
	if(m_has_modeling)
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(5)),_variant_t("有模型 √"));
	else
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(5)),_variant_t("有模型"));
	if(m_urgent)
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(6)),_variant_t("加急 √"));
	else
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(6)),_variant_t("加急"));
	
	m_ExlRge.SetItem(_variant_t((long)(9)),_variant_t((long)(1)),_variant_t("尺寸"));
	m_ExlRge.SetItem(_variant_t((long)(9)),_variant_t((long)(2)),_variant_t(m_size));
	m_ExlRge.SetItem(_variant_t((long)(9)),_variant_t((long)(3)),_variant_t("生产数量"));
	strtmp.Format("%d",m_totel_number);
	m_ExlRge.SetItem(_variant_t((long)(9)),_variant_t((long)(4)),_variant_t(strtmp));
	m_ExlRge.SetItem(_variant_t((long)(9)),_variant_t((long)(5)),_variant_t("制作材料"));
	m_ExlRge.SetItem(_variant_t((long)(9)),_variant_t((long)(6)),_variant_t(m_material));
	m_ExlRge.SetItem(_variant_t((long)(10)),_variant_t((long)(1)),_variant_t("颜色"));
	m_ExlRge.SetItem(_variant_t((long)(10)),_variant_t((long)(2)),_variant_t(m_color));
	m_ExlRge.SetItem(_variant_t((long)(10)),_variant_t((long)(3)),_variant_t("底座搭配"));
	m_ExlRge.SetItem(_variant_t((long)(10)),_variant_t((long)(4)),_variant_t(m_bottom));
	m_ExlRge.SetItem(_variant_t((long)(10)),_variant_t((long)(5)),_variant_t("发票随寄"));
	m_ExlRge.SetItem(_variant_t((long)(10)),_variant_t((long)(6)),_variant_t(m_bill));
	m_ExlRge.SetItem(_variant_t((long)(11)),_variant_t((long)(1)),_variant_t("打磨"));
	m_ExlRge.SetItem(_variant_t((long)(11)),_variant_t((long)(2)),_variant_t(m_shine));
	m_ExlRge.SetItem(_variant_t((long)(11)),_variant_t((long)(3)),_variant_t("误差范围"));
	m_ExlRge.SetItem(_variant_t((long)(11)),_variant_t((long)(4)),_variant_t(m_error_range));
	m_ExlRge.SetItem(_variant_t((long)(11)),_variant_t((long)(5)),_variant_t("体积"));
	strtmp.Format("%s cm3",m_volume);
	m_ExlRge.SetItem(_variant_t((long)(11)),_variant_t((long)(6)),_variant_t(strtmp));
	m_ExlRge.SetItem(_variant_t((long)(12)),_variant_t((long)(1)),_variant_t("喷漆"));
	m_ExlRge.SetItem(_variant_t((long)(12)),_variant_t((long)(2)),_variant_t(m_print));
	m_ExlRge.SetItem(_variant_t((long)(12)),_variant_t((long)(3)),_variant_t("用途"));
	m_ExlRge.SetItem(_variant_t((long)(12)),_variant_t((long)(4)),_variant_t(m_usage));
	m_ExlRge.SetItem(_variant_t((long)(13)),_variant_t((long)(1)),_variant_t("其他要求"));
	m_ExlRge.SetItem(_variant_t((long)(13)),_variant_t((long)(2)),_variant_t(m_other));

	m_ExlRge.SetItem(_variant_t((long)(14)),_variant_t((long)(1)),_variant_t("签名"));
	m_ExlRge.SetItem(_variant_t((long)(15)),_variant_t((long)(1)),_variant_t("销售部"));
	m_ExlRge.SetItem(_variant_t((long)(15)),_variant_t((long)(3)),_variant_t("主管"));
	m_ExlRge.SetItem(_variant_t((long)(15)),_variant_t((long)(5)),_variant_t("日期"));
	m_ExlRge.SetItem(_variant_t((long)(16)),_variant_t((long)(1)),_variant_t("技术部"));
	m_ExlRge.SetItem(_variant_t((long)(16)),_variant_t((long)(3)),_variant_t("主管"));
	m_ExlRge.SetItem(_variant_t((long)(16)),_variant_t((long)(5)),_variant_t("日期"));
	m_ExlRge.SetItem(_variant_t((long)(17)),_variant_t((long)(1)),_variant_t("生产部"));
	m_ExlRge.SetItem(_variant_t((long)(17)),_variant_t((long)(3)),_variant_t("主管"));
	m_ExlRge.SetItem(_variant_t((long)(17)),_variant_t((long)(5)),_variant_t("日期"));
	m_ExlRge.SetItem(_variant_t((long)(18)),_variant_t((long)(1)),_variant_t("质检"));
	//m_ExlRge.SetItem(_variant_t((long)(18)),_variant_t((long)(3)),_variant_t("主管"));
	m_ExlRge.SetItem(_variant_t((long)(18)),_variant_t((long)(5)),_variant_t("日期"));
	m_ExlRge.SetItem(_variant_t((long)(19)),_variant_t((long)(1)),_variant_t("成品仓"));
	m_ExlRge.SetItem(_variant_t((long)(19)),_variant_t((long)(3)),_variant_t("快递单号"));
	m_ExlRge.SetItem(_variant_t((long)(19)),_variant_t((long)(5)),_variant_t("日期"));


	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A3"), _variant_t("F3")));//获取表单中的列"P"对象
	m_ExlRge.SetColumnWidth(_variant_t((long)14));  //设置列宽为100

	m_ExlRge.AttachDispatch(m_ExlSheet.GetUsedRange());//加载已使用的单元格 
	m_ExlRge.SetWrapText(_variant_t((long)1));//设置单元格内的文本为自动换行 
	//m_ExlRge.SetColumnWidth(_variant_t((long)13));  //设置列宽为100
	m_ExlRge.SetRowHeight(_variant_t((long)30	));

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

	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("F1"))); 

	ft.AttachDispatch(m_ExlRge.GetFont()); 
	//ft.SetBold(_variant_t((long)0));//粗体 
	ft.SetSize(_variant_t((long)15)); 
	//ft.SetColorIndex(_variant_t((long)2)); 

	//CellFormat cf; 
	//cf.AttachDispatch(m_ExlRge.GetCells()); 

	//居中
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("F1")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4108));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"),_variant_t("F2")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4108));
	ft.AttachDispatch(m_ExlRge.GetFont()); 
	//ft.SetBold(_variant_t((long)0));//粗体 
	ft.SetSize(_variant_t((long)14)); 
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
	int i = 0;
	for(i=1;i<=19;i++) 
	{
		if((i==1)||(i==2)||(i==7)||(i==14))
			continue;
		for(int j=1;j<=6;j++) 
		{
			CellName.Format("%c%d",j+64,i);//单元格的名称
			UnitRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t(CellName),_variant_t(CellName)));//加载单元格
			//LineStyle=线型 Weight=线宽 ColorIndex=线的颜色(-4105为自动)
			UnitRge.BorderAround(_variant_t((long)1),_variant_t((long)2),_variant_t((long)-4105),vtMissing);//设置边框
		}
	} 
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("B13"),_variant_t("B13")));
	m_ExlRge.SetRowHeight(COleVariant((short)120));
	
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
