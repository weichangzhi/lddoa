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
	m_ComDepartment.InsertString(0,"��������");
	m_ComDepartment.InsertString(1,"����");
	m_ComDepartment.InsertString(2,"��Ӫ");
	m_ComDepartment.InsertString(3,"����");
	m_ComDepartment.InsertString(4,"�з�");
	
	m_ComSize.InsertString(0,"6cm������");
	m_ComSize.InsertString(1,"12cm������");
	m_ComSize.InsertString(2,"10cmȫ����");
	m_ComSize.InsertString(3,"13.14cmȫ����");
	m_ComSize.InsertString(4,"15cmȫ����");
	m_ComSize.InsertString(5,"19.9cmȫ����");
	m_ComSize.InsertString(6,"19.9cm��ɴȫ����");
	m_ComSize.InsertString(7,"28cmȫ����");
	m_ComSize.InsertString(8,"6cm���ذ�����");
	m_ComSize.InsertString(9,"6cm���ذ���˫��");
	m_ComSize.InsertString(10,"10cm����ȫ����");
	m_ComSize.InsertString(11,"10cm����ȫ��˫��");
	m_ComSize.InsertString(12,"10cm����·��");
	m_ComSize.InsertString(13,"10cm���������ӳ�");
	m_ComSize.InsertString(14,"10cm����������");
	m_ComSize.InsertString(15,"10cm������������");
	m_ComSize.SetCurSel(-1);
	m_ComMaterial.InsertString(0,"ȫ��660ɰ��");
	m_ComMaterial.InsertString(1,"ȫ��4500����");
	m_ComMaterial.InsertString(2,"����");
	m_ComMaterial.InsertString(3,"����66");
	m_ComMaterial.InsertString(4,"RS6000��ɫ��֬");
	m_ComMaterial.InsertString(5,"EDEN260��ɫ�߾�");
	m_ComMaterial.InsertString(6,"EDEN260��͸���߾�");
	m_ComMaterial.InsertString(7,"͸���߾�");
	m_ComMaterial.InsertString(8,"��");
	m_ComMaterial.InsertString(9,"ABS����");
	m_ComMaterial.InsertString(10,"PLA");
	m_ComMaterial.InsertString(11,"CNC");
	m_ComMaterial.SetCurSel(0);
	m_ComColor.InsertString(0,"��");
	m_ComColor.InsertString(1,"ȫ��");
	m_ComColor.InsertString(2,"��ɫ");
	m_ComColor.InsertString(3,"��");
	m_ComColor.SetCurSel(0);
	m_ComPaint1.InsertString(0,"��");
	m_ComPaint1.InsertString(1,"��");
	m_ComPaint1.SetCurSel(0);
	m_ComShine.InsertString(0,"ϸ��ĥ");
	m_ComShine.InsertString(1,"��");
	m_ComShine.SetCurSel(0);
	m_ComBottom.InsertString(0,"��");
	m_ComBottom.InsertString(1,"����");
	m_ComBottom.InsertString(2,"ˮ��");
	m_ComBottom.SetCurSel(0);
	m_ComBill.InsertString(0,"��");
	m_ComBill.InsertString(1,"��");
	m_ComBill.SetCurSel(0);

	if(m_department.Compare("��������")==0)
	{
		m_ComDepartment.SetCurSel(0);
		m_ComMaterial.SetCurSel(4);
		m_ComShine.SetCurSel(0);
	}
	else if(m_department.Compare("����")==0)
	{
		m_ComDepartment.SetCurSel(1);
		m_ComMaterial.SetCurSel(10);
		m_ComShine.SetCurSel(1);
	}
	else if(m_department.Compare("��Ӫ")==0)
	{
		m_ComDepartment.SetCurSel(2);
		m_ComMaterial.SetCurSel(0);
		m_ComShine.SetCurSel(0);
	}
	else if(m_department.Compare("����")==0)
	{
		m_ComDepartment.SetCurSel(3);
		m_ComMaterial.SetCurSel(0);
		m_ComShine.SetCurSel(0);
	}
	else if(m_department.Compare("�з�")==0)
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
		MessageBox("�޶����ţ�����������","��ʾ",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
		return;
	}
	if(!(m_phone.IsEmpty()))
	{
		if(!IsPhoneNum(m_phone))
		{
			MessageBox("��ϵ�绰�������Ϊ���֣�����������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_PHONE)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_PHONE))->SetSel(0, -1);
			return;	
		}
		int len = m_phone.GetLength();
		if(len!=11 && len!=12 && len!=15 && len!=16 && len!=17)
		{
			MessageBox("��ϵ�绰�����ʽ����ȷ������������","��ʾ",MB_OK);
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
			MessageBox("���������������Ϊ����������������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_TOTEL_NUMBER)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_TOTEL_NUMBER))->SetSel(0, -1);
			return;
		}
	}
	int totelnumber = m_totel_number = atoi(strTotalNum);;
	if(totelnumber<=0)
	{
		MessageBox("���������Ƿ�������������","��ʾ",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_TOTEL_NUMBER)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_TOTEL_NUMBER))->SetSel(0, -1);
		return;
	}
	GetDlgItem(IDC_EDIT1_TRUE_NUMBER)->SetWindowText(strTotalNum);
	if(!(m_money.IsEmpty()))
	{
		if(!IsNum(m_money))
		{
			MessageBox("����������Ϊ���֣�����������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONDY)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONDY))->SetSel(0, -1);
			return;
		}
		if(atof(m_money)>10000000)
		{
			MessageBox("��������һǧ������������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONDY)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONDY))->SetSel(0, -1);
			return;
		}
	}
	if(!(m_volume.IsEmpty()))
	{
		if(!IsNum(m_volume))
		{
			MessageBox("����������Ϊ���֣�����������","��ʾ",MB_OK);
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
		mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
		sql.Format("select * from baseinfo where listid=\"%s\" ",m_listid);
		if(mysql_query(&myCont,sql)!= 0)
		{
			dlgpro->endpos();
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			return;
		}
		dlgpro->setpos(600);
		result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
		if(result)
		{
			unsigned __int64 num = mysql_num_rows(result);//����
			if(num==1)
			{
				dlgpro->endpos();
				MessageBox("�˶����ѱ��ύ�������´���������","��ʾ",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
				mysql_close(&myCont);//�Ͽ�����
				return;
			}
		}
		else
		{
			dlgpro->endpos();
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
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
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			return;
		}
		result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
		if(result)
		{
			sql_row=mysql_fetch_row(result);
			starttime = sql_row[0];
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
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			return;
		}
		dlgpro->endpos();
		if(mysql_affected_rows(&myCont)>0)
		{
			MessageBox("���涩���ɹ�","��ʾ",MB_OK);			
		}
		else
		{
			MessageBox("���涩��ʧ��","��ʾ",MB_OK);
		}
		GetDlgItem(IDC_BUTTON_START_LIST)->EnableWindow(TRUE);
	}
	else
	{
		dlgpro->endpos();
		const char *error = mysql_error(&myCont);
		CString str;
		str.Format("���ݿ����(%s)",error);
		MessageBox(str,"��ʾ",MB_OK);
		mysql_close(&myCont);//�Ͽ�����
		return;
	}
	mysql_close(&myCont);//�Ͽ�����
	//MessageBox("���涩���ɹ�","��ʾ",MB_OK);
}

void CDialog_New_List::OnStartList() 
{
	UpdateData();
	if(m_listid.IsEmpty())
	{
		MessageBox("�޶����ţ�����������","��ʾ",MB_OK);
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
			MessageBox("�µ������������Ϊ����������������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT1_TRUE_NUMBER)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT1_TRUE_NUMBER))->SetSel(0, -1);
			return;
		}
	}
	int totelnumber = m_true_number = atoi(strTotalNum);
	if(totelnumber<=0)
	{
		MessageBox("���������Ƿ�������������","��ʾ",MB_OK);
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
		mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
		CString sql;
		sql.Format("select * from schedule where listid=\"%s\" ",m_listid);
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
			if(num==1)
			{
				MessageBox("�˶������Ѵ���","��ʾ",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
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

/*		sql.Format("select savelistpeople from baseinfo where listid=\"%s\" ",m_listid);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			return;
		}
		result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
		if(result)
		{
			sql_row=mysql_fetch_row(result);
			if(strcmp(sql_row[0],login2.m_user))
			{
				MessageBox("�µ�����ӵ��˲�һ��","��ʾ",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
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
*/
		dlgpro->setpos(700);
		sql.Format("insert into schedule(listid,listname,totelnumber,businessnumber,tcnumber,pdnumber,qcnumber,storagenumber,sendnumber,post,end,hasstoragenumber,undolist) \
		values (\"%s\",\"%s\",%d,0,%d,0,0,0,0,0,0,0,0)",m_listid,m_listname,totelnumber,totelnumber);
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
		CTime time = CTime::GetCurrentTime();
		CString starttime;
		dlgpro->setpos(800);
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
			starttime = sql_row[0];
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
		dlgpro->setpos(900);
		sql.Format("insert into scheduledetail(listid,businessendtime,businessnumber,businesspeople,tcstarttime) \
		values (\"%s\",\"%s\",%d,\"%s\",\"%s\")",m_listid,starttime,totelnumber,login2.m_user,starttime);
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
		dlgpro->setpos(950);
		sql.Format("update baseinfo set truelistnumber=%d  where listid=\"%s\" " ,m_true_number,m_listid);
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
		if(mysql_affected_rows(&myCont)>0)
		{
			MessageBox("�µ��ɹ�","��ʾ",MB_OK);
			dlgpro->endpos();
		}
		else
		{
			MessageBox("�µ��ɹ�","��ʾ",MB_OK);
			dlgpro->endpos();
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
	mysql_close(&myCont);//�Ͽ�����
	//MessageBox("�µ��ɹ�","��ʾ",MB_OK);
	
}

void CDialog_New_List::OnEndList() 
{
	return;
	UpdateData();
	if(m_listid.IsEmpty())
	{
		MessageBox("�޶����ţ�����������","��ʾ",MB_OK);
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
		//case VK_RETURN: //�س�  
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
	case 0://��������
		m_ComMaterial.SetCurSel(4);
		m_ComShine.SetCurSel(0);
		break;
	case 1://����
		m_ComMaterial.SetCurSel(10);
		m_ComShine.SetCurSel(1);
		break;
	case 2://��Ӫ
		m_ComMaterial.SetCurSel(0);
		m_ComShine.SetCurSel(0);
		break;
	case 3://����
		m_ComMaterial.SetCurSel(0);
		m_ComShine.SetCurSel(0);
		break;
	case 4://�з�
		m_ComMaterial.SetCurSel(-1);
		m_ComSize.SetCurSel(-1);
		break;
	default:
		m_ComMaterial.SetCurSel(-1);
		m_ComSize.SetCurSel(-1);
		break;
	}
	
}

void CDialog_New_List::OnButtonPreview() 
{
	// TODO: Add your control notification handler code here
	
}

void CDialog_New_List::OnButtonPrint() 
{
	// TODO: Add your control notification handler code here
	
}
