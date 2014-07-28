// Dialog_ModifyList.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_ModifyList.h"
#include "Dialog_Login2.h"
#include "Dialog_progress.h"
#include "Dialog_List_Undo.h"

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
	DDX_Control(pDX, IDC_BUTTON_EXCEL, m_btexcel);
	DDX_Control(pDX, IDC_BUTTON_PRINT, m_btprint);
	DDX_Control(pDX, IDC_BUTTON_PREVIEW, m_btpreview);
	DDX_Control(pDX, IDC_BUTTON_UNDO_LIST, m_bt_undo);
	DDX_Control(pDX, IDC_BUTTON_CONTINUE_LIST, m_btcontinue);
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
	ON_BN_CLICKED(IDC_BUTTON_UNDO_LIST, OnButtonUndoList)
	ON_BN_CLICKED(IDC_BUTTON_CONTINUE_LIST, OnButtonContinueList)
	ON_BN_CLICKED(IDC_BUTTON_PREVIEW, OnButtonPreview)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnButtonPrint)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL, OnButtonExcel)
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
	m_ComDepartment.InsertString(0,"��������");
	m_ComDepartment.InsertString(1,"����");
	m_ComDepartment.InsertString(2,"��Ӫ");
	m_ComDepartment.InsertString(3,"����");
	m_ComDepartment.InsertString(4,"�з�");
	if(m_department.Compare("��������")==0)
		m_ComDepartment.SetCurSel(0);
	else if(m_department.Compare("����")==0)
		m_ComDepartment.SetCurSel(1);
	else if(m_department.Compare("��Ӫ")==0)
		m_ComDepartment.SetCurSel(2);
	else if(m_department.Compare("����")==0)
		m_ComDepartment.SetCurSel(3);
	else if(m_department.Compare("�з�")==0)
		m_ComDepartment.SetCurSel(4);
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
	//m_ComSize.SetCurSel(0);
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
	//m_ComMaterial.SetCurSel(0);
	m_ComColor.InsertString(0,"��");
	m_ComColor.InsertString(1,"ȫ��");
	m_ComColor.InsertString(2,"��ɫ");
	m_ComColor.InsertString(3,"��");
	//m_ComColor.SetCurSel(0);
	m_ComPaint.InsertString(0,"��");
	m_ComPaint.InsertString(1,"��");
	//m_ComPaint.SetCurSel(0);
	m_ComShine.InsertString(0,"ϸ��ĥ");
	m_ComShine.InsertString(1,"��");
	//m_ComShine.SetCurSel(0);
	m_ComBottom.InsertString(0,"��");
	m_ComBottom.InsertString(1,"����");
	m_ComBottom.InsertString(2,"ˮ��");
	//m_ComBottom.SetCurSel(0);
	m_ComBill.InsertString(0,"��");
	m_ComBill.InsertString(1,"��");
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
		//case VK_RETURN: //�س�  
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
		MessageBox("������Ϊ�գ�������","��ʾ",MB_OK);
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
        mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
        res=mysql_query(&myCont,csSql);//��ѯ
        if(!res)
        {
			dlgpro->setpos(600);
            result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
			dlgpro->setpos(700);
		    if(result)
            {
                int j = 0;
                j=mysql_num_fields(result);//�鿴������
				unsigned __int64 num = mysql_num_rows(result);//����
				int index = 0;
                sql_row=mysql_fetch_row(result);//��ȡ���������
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
					if(m_department.Compare("��������")==0)
						m_ComDepartment.SetCurSel(0);
					else if(m_department.Compare("����")==0)
						m_ComDepartment.SetCurSel(1);
					else if(m_department.Compare("��Ӫ")==0)
						m_ComDepartment.SetCurSel(2);
					else if(m_department.Compare("����")==0)
						m_ComDepartment.SetCurSel(3);
					else if(m_department.Compare("�з�")==0)
						m_ComDepartment.SetCurSel(4);

					m_money = "******";
					if(((m_department.Compare("��������")==0) && (g_permission&MONEY_SELL))
						||((m_department.Compare("����")==0) && (g_permission&MONEY_EC))
						||((m_department.Compare("��Ӫ")==0) && (g_permission&MONEY_RUN))
						||((m_department.Compare("����")==0) && (g_permission&MONEY_JOIN)))
						m_money = sql_row[28];
					

					if(m_size.Compare("6cm������")==0)
						m_ComSize.SetCurSel(0);
					else if(m_size.Compare("12cm������")==0)
						m_ComSize.SetCurSel(1);
					else if(m_size.Compare("10cmȫ����")==0)
						m_ComSize.SetCurSel(2);
					else if(m_size.Compare("13.14cmȫ����")==0)
						m_ComSize.SetCurSel(3);
					else if(m_size.Compare("15cmȫ����")==0)
						m_ComSize.SetCurSel(4);
					else if(m_size.Compare("19.9cmȫ����")==0)
						m_ComSize.SetCurSel(5);
					else if(m_size.Compare("19.9cm��ɴȫ����")==0)
						m_ComSize.SetCurSel(6);
					else if(m_size.Compare("28cmȫ����")==0)
						m_ComSize.SetCurSel(7);
					else if(m_size.Compare("6cm���ذ�����")==0)
						m_ComSize.SetCurSel(8);
					else if(m_size.Compare("6cm���ذ���˫��")==0)
						m_ComSize.SetCurSel(9);
					else if(m_size.Compare("10cm����ȫ����")==0)
						m_ComSize.SetCurSel(10);
					else if(m_size.Compare("10cm����ȫ��˫��")==0)
						m_ComSize.SetCurSel(11);
					else if(m_size.Compare("10cm����·��")==0)
						m_ComSize.SetCurSel(12);
					else if(m_size.Compare("10cm���������ӳ�")==0)
						m_ComSize.SetCurSel(13);
					else if(m_size.Compare("10cm����������")==0)
						m_ComSize.SetCurSel(14);
					else if(m_size.Compare("10cm������������")==0)
						m_ComSize.SetCurSel(15);
					else 
						m_ComSize.SetWindowText(m_size);

					if(m_material.Compare("ȫ��660ɰ��")==0)
						m_ComMaterial.SetCurSel(0);
					else if(m_material.Compare("ȫ��4500����")==0)
						m_ComMaterial.SetCurSel(1);
					else if(m_material.Compare("����")==0)
						m_ComMaterial.SetCurSel(2);
					else if(m_material.Compare("����66")==0)
						m_ComMaterial.SetCurSel(3);
					else if(m_material.Compare("RS6000��ɫ��֬")==0)
						m_ComMaterial.SetCurSel(4);
					else if(m_material.Compare("EDEN260��ɫ�߾�")==0)
						m_ComMaterial.SetCurSel(5);
					else if(m_material.Compare("EDEN260��͸���߾�")==0)
						m_ComMaterial.SetCurSel(6);
					else if(m_material.Compare("͸���߾�")==0)
						m_ComMaterial.SetCurSel(7);
					else if(m_material.Compare("��")==0)
						m_ComMaterial.SetCurSel(8);
					else if(m_material.Compare("ABS����")==0)
						m_ComMaterial.SetCurSel(9);
					else if(m_material.Compare("PLA")==0)
						m_ComMaterial.SetCurSel(10);
					else if(m_material.Compare("CNC")==0)
						m_ComMaterial.SetCurSel(11);
					else 
						m_ComMaterial.SetWindowText(m_material);
					
					if(m_color.Compare("��")==0)
						m_ComColor.SetCurSel(0);
					else if(m_color.Compare("ȫ��")==0)
						m_ComColor.SetCurSel(1);
					else if(m_color.Compare("��ɫ")==0)
						m_ComColor.SetCurSel(2);
					else if(m_color.Compare("��")==0)
						m_ComColor.SetCurSel(3);
					else 
						m_ComColor.SetWindowText(m_color);
				
					if(m_print.Compare("��")==0)
						m_ComPaint.SetCurSel(0);
					else if(m_print.Compare("��")==0)
						m_ComPaint.SetCurSel(1);
					else 
						m_ComPaint.SetWindowText(m_print);
					
					if(m_shine.Compare("ϸ��ĥ")==0)
						m_ComShine.SetCurSel(0);
					else if(m_shine.Compare("��")==0)
						m_ComShine.SetCurSel(1);
					else 
						m_ComShine.SetWindowText(m_shine);

					if(m_bottom.Compare("��")==0)
						m_ComBottom.SetCurSel(0);
					else if(m_bottom.Compare("����")==0)
						m_ComBottom.SetCurSel(1);
					else if(m_bottom.Compare("ˮ��")==0)
						m_ComBottom.SetCurSel(2);
					else 
						m_ComBottom.SetWindowText(m_bottom);

					if(m_bill.Compare("��")==0)
						m_ComBill.SetCurSel(0);
					else if(m_bill.Compare("��")==0)
						m_ComBill.SetCurSel(1);
					else 
						m_ComBill.SetWindowText(m_bill);
					dlgpro->setpos(900);
					dlgpro->endpos();
                    UpdateData(FALSE);
                }
				else
				{
					MessageBox("�޴˶����ţ�����������","��ʾ",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
					mysql_close(&myCont);//�Ͽ�����
					dlgpro->endpos();
					return;
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

	return;
	
}

void CDialog_ModifyList::OnModifylist() 
{
	UpdateData();
	if(m_listid.IsEmpty())
	{
		MessageBox("�޶����ţ�����������","��ʾ",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID))->SetSel(0, -1);
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
			if(num==1)//���µ���
			{
				sql_row=mysql_fetch_row(result);
				if(sql_row)
				{
					isend = atoi(sql_row[10]);
					if(isend==1)
					{
						MessageBox("�˶������ѱ��ᵥ���������޸�","��ʾ",MB_OK);
						(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID))->SetSel(0, -1);
						if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
						mysql_close(&myCont);//�Ͽ�����
						dlgpro->endpos();
						return;
					}
				}
				else
				{
					MessageBox("�˶������ѱ��µ�","��ʾ",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID))->SetSel(0, -1);
					if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
					mysql_close(&myCont);//�Ͽ�����
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
					MessageBox("�˶������ѱ��µ���ֻ�����ܲ���Ȩ���޸�","��ʾ",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID))->SetSel(0, -1);
					if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
					mysql_close(&myCont);//�Ͽ�����
					dlgpro->endpos();
					return;
				}

				//��ӱ����¼�����ݿ�
				CString strChangeRecord;
				CString tmp;
				if(m_listname.Compare(m_listname1)!=0)
				{
					tmp.Format("�������ƣ�%s -> %s�� ",m_listname1,m_listname);
					strChangeRecord += tmp;
				}
				if(m_people.Compare(m_people1)!=0)
				{
					tmp.Format("�����ˣ�%s -> %s�� ",m_people1,m_people);
					strChangeRecord += tmp;
				}
				if(m_receivename.Compare(m_receivename1)!=0)
				{
					tmp.Format("�ռ��ˣ�%s -> %s�� ",m_receivename1,m_receivename);
					strChangeRecord += tmp;
				}
				if(m_phone.Compare(m_phone1)!=0)
				{
					tmp.Format("��ϵ�绰��%s -> %s�� ",m_phone1,m_phone);
					strChangeRecord += tmp;
				}
				if(m_address.Compare(m_address1)!=0)
				{
					tmp.Format("��ϸ��ַ��%s -> %s�� ",m_address1,m_address);
					strChangeRecord += tmp;
				}
				if(m_department.Compare(m_department1)!=0)
				{
					tmp.Format("���ţ�%s -> %s�� ",m_department1,m_department);
					strChangeRecord += tmp;
				}
				if(m_str_reveive_time.Compare(m_str_reveive_time1)!=0)
				{
					tmp.Format("�ɵ����ڣ�%s -> %s�� ",m_str_reveive_time1,m_str_reveive_time);
					strChangeRecord += tmp;
				}
				if(m_str_end_date.Compare(m_str_end_date1)!=0)
				{
					tmp.Format("�������ڣ�%s -> %s�� ",m_str_end_date1,m_str_end_date);
					strChangeRecord += tmp;
				}
				if(m_modeling!=m_modeling1)
				{
					tmp.Format("��ģ��%d -> %d�� ",m_modeling1,m_modeling);
					strChangeRecord += tmp;
				}
				if(m_design_server!=m_design_server1)
				{
					tmp.Format("��Ʒ���%d -> %d�� ",m_design_server1,m_design_server);
					strChangeRecord += tmp;
				}
				if(m_scan!=m_scan1)
				{
					tmp.Format("ɨ��ҵ��%d -> %d�� ",m_scan1,m_scan);
					strChangeRecord += tmp;
				}
				if(m_modeling_pring!=m_modeling_pring1)
				{
					tmp.Format("ģ�ʹ�ӡ��%d -> %d�� ",m_modeling_pring1,m_modeling_pring);
					strChangeRecord += tmp;
				}
				if(m_has_modeling!=m_has_modeling1)
				{
					tmp.Format("��ģ�ͣ�%d -> %d�� ",m_has_modeling1,m_has_modeling);
					strChangeRecord += tmp;
				}
				if(m_no_modeling!=m_no_modeling1)
				{
					tmp.Format("��ģ�ͣ�%d -> %d�� ",m_no_modeling1,m_no_modeling);
					strChangeRecord += tmp;
				}
				if(m_urgent!=m_urgent1)
				{
					tmp.Format("�Ӽ���%d -> %d�� ",m_urgent1,m_urgent);
					strChangeRecord += tmp;
				}

				if(m_size.Compare(m_size1)!=0)
				{
					tmp.Format("�ߴ磺%s -> %s�� ",m_size1,m_size);
					strChangeRecord += tmp;
				}
				if(m_totel_number!=m_totel_number1)
				{
					tmp.Format("����������%d -> %d�� ",m_totel_number1,m_totel_number);
					strChangeRecord += tmp;
				}

				if(m_material.Compare(m_material1)!=0)
				{
					tmp.Format("�������ϣ�%s -> %s�� ",m_material1,m_material);
					strChangeRecord += tmp;
				}
				if(m_color.Compare(m_color1)!=0)
				{
					tmp.Format("��ɫ��%s -> %s�� ",m_color1,m_color);
					strChangeRecord += tmp;
				}
				if(m_print.Compare(m_print1)!=0)
				{
					tmp.Format("���᣺%s -> %s�� ",m_print1,m_print);
					strChangeRecord += tmp;
				}
				if(m_shine.Compare(m_shine1)!=0)
				{
					tmp.Format("��ĥ��%s -> %s�� ",m_shine1,m_shine);
					strChangeRecord += tmp;
				}
				if(m_bottom.Compare(m_bottom1)!=0)
				{
					tmp.Format("�������䣺%s -> %s�� ",m_bottom1,m_bottom);
					strChangeRecord += tmp;
				}
				if(m_bill.Compare(m_bill1)!=0)
				{
					tmp.Format("��Ʊ��ģ�%s -> %s�� ",m_bill1,m_bill);
					strChangeRecord += tmp;
				}
				if(m_usage.Compare(m_usage1)!=0)
				{
					tmp.Format("��;��%s -> %s�� ",m_usage1,m_usage);
					strChangeRecord += tmp;
				}
				if(m_error_range.Compare(m_error_range1)!=0)
				{
					tmp.Format("��Χ��%s -> %s�� ",m_error_range1,m_error_range);
					strChangeRecord += tmp;
				}
				if(m_money.Compare(m_money1)!=0)
				{
					tmp.Format("ǩ����%s -> %s�� ",m_money1,m_money);
					strChangeRecord += tmp;
				}
				if(m_volume.Compare(m_volume1)!=0)
				{
					tmp.Format("�����%s -> %s�� ",m_volume1,m_volume);
					strChangeRecord += tmp;
				}
				if(m_other.Compare(m_other1)!=0)
				{
					tmp.Format("����Ҫ��%s -> %s�� ",m_other1,m_other);
					strChangeRecord += tmp;
				}

				CString starttime;
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
				dlgpro->setpos(800);
				sql.Format("insert into changerecord values (%d,\"%s\",\"%s\",\"%s\",\"%s\")", 0,m_listid,starttime,login2.m_user,strChangeRecord);
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
				writelog("��������¼�ɹ�");
			}
			else//δ�µ�
			{
				CDialog_Login2 login2;
				if(m_urgent)
					login2.m_urgent = 1;
				login2.m_permission = MODIFY_LIST_BEFORE;
				if (login2.DoModal()!=IDOK)
				{
					if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
					mysql_close(&myCont);//�Ͽ�����
					dlgpro->endpos();
					return;
				}
				dlgpro->setpos(700);
				sql.Format("select savelistpeople from baseinfo where listid=\"%s\" ",m_listid);
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
				dlgpro->setpos(800);
				result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
				if(result)
				{
					sql_row=mysql_fetch_row(result);
					if(sql_row==NULL)
					{
						MessageBox("�޴˶����ţ�����������","��ʾ",MB_OK);
						(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID))->SetSel(0, -1);
						mysql_close(&myCont);//�Ͽ�����
						dlgpro->endpos();
						return;
					}
					if(strcmp(sql_row[0],login2.m_user))
					{
						if (m_urgent==0)
						{
							MessageBox("ֻ���ύ�������˲����޸Ĵ˶���","��ʾ",MB_OK);
							(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
							((CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID))->SetSel(0, -1);
							if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
							mysql_close(&myCont);//�Ͽ�����
							dlgpro->endpos();
							return;
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
					dlgpro->endpos();
					return;
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
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			dlgpro->endpos();
			return;
		}
		dlgpro->setpos(950);
		dlgpro->endpos();
		if(mysql_affected_rows(&myCont)>0)
		{
			MessageBox("�޸Ķ����ɹ�","��ʾ",MB_OK);
		}
		else
		{
			MessageBox("�޸Ķ���ʧ�ܣ���������û�б仯","��ʾ",MB_OK);
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
	//MessageBox("�޸Ķ����ɹ�","��ʾ",MB_OK); 
}

void CDialog_ModifyList::OnStartList() 
{
	UpdateData();
	if(m_listid.IsEmpty())
	{
		MessageBox("�޶����ţ�����������","��ʾ",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID))->SetSel(0, -1);
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
	int totelnumber = m_true_number = atoi(strTotalNum);;
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
		mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
		dlgpro->setpos(500);
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
				(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID))->SetSel(0, -1);
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
		dlgpro->setpos(800);
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
		dlgpro->setpos(900);
		sql.Format("update baseinfo set truelistnumber=%d  where listid=\"%s\" " ,m_true_number,m_listid);
		if(mysql_query(&myCont,sql)!= 0)
		{
			MessageBox("�ύ���ݿ�ʧ��","��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			dlgpro->endpos();
			return ;
		}
		dlgpro->endpos();
		if(mysql_affected_rows(&myCont)>0)
		{
			MessageBox("�µ��ɹ�","��ʾ",MB_OK);
		}
		else
		{
			MessageBox("�µ��ɹ�","��ʾ",MB_OK);
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
	mysql_close(&myCont);//�Ͽ�����
	//MessageBox("�µ��ɹ�","��ʾ",MB_OK);
	
}

void CDialog_ModifyList::OnEndList() 
{
	UpdateData();
	if(m_listid.IsEmpty())
	{
		MessageBox("�޶����ţ�����������","��ʾ",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID))->SetSel(0, -1);
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
		mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
		CString sql;
		CTime time = CTime::GetCurrentTime();
		CString starttime;

		CString strsql ;
		strsql.Format("select now()");
		if(mysql_query(&myCont,strsql)!= 0)
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
		
		
		strsql.Format("select totelnumber,post,end from schedule where listid=\"%s\" ",m_listid);
		if(mysql_query(&myCont,strsql)!= 0)
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
			unsigned __int64 num = mysql_num_rows(result);//����
			if(num<1)
			{
				MessageBox("�˶���������","��ʾ",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
				mysql_close(&myCont);//�Ͽ�����
				return;
			}
			sql_row=mysql_fetch_row(result);
			if(sql_row==NULL)
			{
				MessageBox("�˶���������","��ʾ",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
				mysql_close(&myCont);//�Ͽ�����
				return;
			}
			if(atoi(sql_row[1])<atoi(sql_row[0]))
			{	
				CString strerr;
				strerr.Format("���� %s ���� %d ��û�о�����������.",m_listid,atoi(sql_row[0])-atoi(sql_row[1]));
				MessageBox(strerr,"��ʾ",MB_OK);
				if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
				mysql_close(&myCont);//�Ͽ�����
				return;
			}
			if(atoi(sql_row[2])==1)
			{
				MessageBox("�˶����ѽᵥ","��ʾ",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID))->SetSel(0, -1);
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


		sql.Format("update schedule set end=%d where listid=\"%s\" " ,1,m_listid);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			return;
		}
		if(mysql_affected_rows(&myCont)>0)
		{
			MessageBox("�ᵥ�ɹ�","��ʾ",MB_OK);
		}
		else
		{
			MessageBox("�ᵥʧ��","��ʾ",MB_OK);
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
	mysql_close(&myCont);//�Ͽ�����
	//MessageBox("�ᵥ�ɹ�","��ʾ",MB_OK);
	
}

void CDialog_ModifyList::OnOK() 
{
	// TODO: Add extra validation here
	OnQueryList();
	//CDialog::OnOK();
}

void CDialog_ModifyList::OnButtonUndoList() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_query_listid.TrimLeft();
	m_query_listid.TrimRight();
	if (m_query_listid.IsEmpty())
	{	
		MessageBox("������Ϊ�գ�������","��ʾ",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
		return;
	}
	Dialog_List_Undo dlg;
	dlg.m_listid = m_query_listid;
	if(dlg.DoModal()==IDOK)
	{
		
	}
}

void CDialog_ModifyList::OnButtonContinueList() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if(m_listid.IsEmpty())
	{
		MessageBox("�޶����ţ�����������","��ʾ",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID))->SetSel(0, -1);
		return;
	}
	
	Dialog_progress *dlgpro;
	dlgpro=new Dialog_progress(); 
	dlgpro->Create(IDD_DIALOG_PROGRESS);
	if(g_openprocess)
		dlgpro->ShowWindow(SW_SHOW);
	else
		dlgpro->ShowWindow(SW_HIDE);

	int undolist = 0;
	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	mysql_init(&myCont);
	if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
	{
		dlgpro->setpos(500);
		mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
		CString sql;
		sql.Format("select undolist from schedule where listid=\"%s\" ",m_listid);
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
			if(num==1)//�м�¼��
			{
				sql_row=mysql_fetch_row(result);
				if(sql_row)
				{
					undolist = atoi(sql_row[0]);
					if(undolist==0)
					{
						MessageBox("�˶���û�б�����������������","��ʾ",MB_OK);
						(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID))->SetSel(0, -1);
						if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
						mysql_close(&myCont);//�Ͽ�����
						dlgpro->endpos();
						return;
					}
				}
				else
				{
					MessageBox("�˶���δ�µ�","��ʾ",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID))->SetSel(0, -1);
					if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
					mysql_close(&myCont);//�Ͽ�����
					dlgpro->endpos();
					return;
				}
				dlgpro->setpos(700);
				CDialog_Login2 login2;
				if(m_urgent)
					login2.m_urgent = 1;
				login2.m_permission = DEL_LIST;
				if (login2.DoModal()!=IDOK)
				{
					(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID))->SetSel(0, -1);
					if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
					mysql_close(&myCont);//�Ͽ�����
					dlgpro->endpos();
					return;
				}

				dlgpro->setpos(800);
				sql.Format("update schedule set undolist=0 where listid=\"%s\" ", m_listid);
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
				writelog("�����ɹ�");
				dlgpro->setpos(950);
				dlgpro->endpos();
				MessageBox("�����ɹ�","��ʾ",MB_OK);
			}
			else//δ�µ�
			{
				MessageBox("�˶���δ�µ�","��ʾ",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID))->SetSel(0, -1);
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
}

void CDialog_ModifyList::SetPreviewDlg(CPreview *PreviewDlg)
{
	UpdateData();
	updatedlg();
	PreviewDlg->m_str_reveive_time = m_str_reveive_time;
	PreviewDlg->m_str_end_date = m_str_end_date;
	CString strtmp;
	if(m_design_server)
		strtmp.Format("%s","��");
	else
		strtmp.Format("%s"," ");
	PreviewDlg->m_design_server = strtmp;
	if(m_has_modeling)
		strtmp.Format("%s","��");
	else
		strtmp.Format("%s"," ");
	PreviewDlg->m_has_modeling = strtmp;
	if(m_modeling)
		strtmp.Format("%s","��");
	else
		strtmp.Format("%s"," ");
	PreviewDlg->m_modeling = strtmp;
	if(m_modeling_pring)
		strtmp.Format("%s","��");
	else
		strtmp.Format("%s"," ");
	PreviewDlg->m_modeling_pring = strtmp;
	if(m_no_modeling)
		strtmp.Format("%s","��");
	else
		strtmp.Format("%s"," ");
	PreviewDlg->m_no_modeling = strtmp;
	if(m_scan)
		strtmp.Format("%s","��");
	else
		strtmp.Format("%s"," ");
	PreviewDlg->m_scan = strtmp;
	if(m_urgent)
		strtmp.Format("%s","��");
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

void CDialog_ModifyList::OnButtonPreview() 
{
	CPreview PreviewDlg;
	SetPreviewDlg(&PreviewDlg);
	PreviewDlg.DoModal();
}

void CDialog_ModifyList::OnButtonPrint() 
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

void CDialog_ModifyList::updatedlg() 
{
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
	CString strTotalNum;
	GetDlgItem(IDC_EDIT_TOTEL_NUMBER)->GetWindowText(strTotalNum);
	m_totel_number = atoi(strTotalNum);
}

void CDialog_ModifyList::OnButtonExcel() 
{
	UpdateData();
	updatedlg();	
	CString filename = "�����ɵ���.xls";
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
	strtmp.Format("%s�����ɵ���",m_department);
	m_ExlSheet.SetName(strtmp); 

	m_ExlRge.AttachDispatch(m_ExlSheet.GetCells(),TRUE);//�������е�Ԫ��
	m_ExlRge.SetNumberFormatLocal(COleVariant("@")); 

	//�ϲ���Ԫ��
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


	////////���ñ������//////// 

	m_ExlRge.AttachDispatch(m_ExlSheet.GetCells(),TRUE);//�������е�Ԫ�� 
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(1)),_variant_t(strtmp));

	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(1)),_variant_t("��������"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(1)),_variant_t("������"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(2)),_variant_t(m_listid));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(3)),_variant_t("��������"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(4)),_variant_t(m_listname));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(5)),_variant_t("������"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(6)),_variant_t(m_people));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(1)),_variant_t("�ռ���"));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(2)),_variant_t(m_receivename));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(3)),_variant_t("��ϵ�绰"));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(4)),_variant_t(m_phone));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(5)),_variant_t("����"));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(6)),_variant_t(m_department));
	m_ExlRge.SetItem(_variant_t((long)(5)),_variant_t((long)(1)),_variant_t("�ɵ�����"));
	m_ExlRge.SetItem(_variant_t((long)(5)),_variant_t((long)(2)),_variant_t(m_str_reveive_time));
	m_ExlRge.SetItem(_variant_t((long)(5)),_variant_t((long)(3)),_variant_t("��������"));
	m_ExlRge.SetItem(_variant_t((long)(5)),_variant_t((long)(4)),_variant_t(m_str_end_date));
	m_ExlRge.SetItem(_variant_t((long)(6)),_variant_t((long)(1)),_variant_t("��ϸ��ַ"));
	m_ExlRge.SetItem(_variant_t((long)(6)),_variant_t((long)(2)),_variant_t(m_address));

	m_ExlRge.SetItem(_variant_t((long)(7)),_variant_t((long)(1)),_variant_t("����Ҫ��"));
	if(m_modeling)
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(1)),_variant_t("��ģ ��"));
	else
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(1)),_variant_t("��ģ"));
	if(m_design_server)
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(2)),_variant_t("��Ʒ��� ��"));
	else
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(2)),_variant_t("��Ʒ���"));
	if(m_scan)
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(3)),_variant_t("ɨ��ҵ�� ��"));
	else
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(3)),_variant_t("ɨ��ҵ��"));
	if(m_modeling_pring)
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(4)),_variant_t("ģ�ʹ�ӡ ��"));
	else
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(4)),_variant_t("ģ�ʹ�ӡ"));
	if(m_has_modeling)
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(5)),_variant_t("��ģ�� ��"));
	else
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(5)),_variant_t("��ģ��"));
	if(m_urgent)
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(6)),_variant_t("�Ӽ� ��"));
	else
		m_ExlRge.SetItem(_variant_t((long)(8)),_variant_t((long)(6)),_variant_t("�Ӽ�"));
	
	m_ExlRge.SetItem(_variant_t((long)(9)),_variant_t((long)(1)),_variant_t("�ߴ�"));
	m_ExlRge.SetItem(_variant_t((long)(9)),_variant_t((long)(2)),_variant_t(m_size));
	m_ExlRge.SetItem(_variant_t((long)(9)),_variant_t((long)(3)),_variant_t("��������"));
	strtmp.Format("%d",m_totel_number);
	m_ExlRge.SetItem(_variant_t((long)(9)),_variant_t((long)(4)),_variant_t(strtmp));
	m_ExlRge.SetItem(_variant_t((long)(9)),_variant_t((long)(5)),_variant_t("��������"));
	m_ExlRge.SetItem(_variant_t((long)(9)),_variant_t((long)(6)),_variant_t(m_material));
	m_ExlRge.SetItem(_variant_t((long)(10)),_variant_t((long)(1)),_variant_t("��ɫ"));
	m_ExlRge.SetItem(_variant_t((long)(10)),_variant_t((long)(2)),_variant_t(m_color));
	m_ExlRge.SetItem(_variant_t((long)(10)),_variant_t((long)(3)),_variant_t("��������"));
	m_ExlRge.SetItem(_variant_t((long)(10)),_variant_t((long)(4)),_variant_t(m_bottom));
	m_ExlRge.SetItem(_variant_t((long)(10)),_variant_t((long)(5)),_variant_t("��Ʊ���"));
	m_ExlRge.SetItem(_variant_t((long)(10)),_variant_t((long)(6)),_variant_t(m_bill));
	m_ExlRge.SetItem(_variant_t((long)(11)),_variant_t((long)(1)),_variant_t("��ĥ"));
	m_ExlRge.SetItem(_variant_t((long)(11)),_variant_t((long)(2)),_variant_t(m_shine));
	m_ExlRge.SetItem(_variant_t((long)(11)),_variant_t((long)(3)),_variant_t("��Χ"));
	m_ExlRge.SetItem(_variant_t((long)(11)),_variant_t((long)(4)),_variant_t(m_error_range));
	m_ExlRge.SetItem(_variant_t((long)(11)),_variant_t((long)(5)),_variant_t("���"));
	m_ExlRge.SetItem(_variant_t((long)(11)),_variant_t((long)(6)),_variant_t(m_volume));
	m_ExlRge.SetItem(_variant_t((long)(12)),_variant_t((long)(1)),_variant_t("����"));
	m_ExlRge.SetItem(_variant_t((long)(12)),_variant_t((long)(2)),_variant_t(m_print));
	m_ExlRge.SetItem(_variant_t((long)(12)),_variant_t((long)(3)),_variant_t("��;"));
	m_ExlRge.SetItem(_variant_t((long)(12)),_variant_t((long)(4)),_variant_t(m_usage));
	m_ExlRge.SetItem(_variant_t((long)(13)),_variant_t((long)(1)),_variant_t("����Ҫ��"));
	m_ExlRge.SetItem(_variant_t((long)(13)),_variant_t((long)(2)),_variant_t(m_other));

	m_ExlRge.SetItem(_variant_t((long)(14)),_variant_t((long)(1)),_variant_t("ǩ��"));
	m_ExlRge.SetItem(_variant_t((long)(15)),_variant_t((long)(1)),_variant_t("���۲�"));
	m_ExlRge.SetItem(_variant_t((long)(15)),_variant_t((long)(3)),_variant_t("����"));
	m_ExlRge.SetItem(_variant_t((long)(15)),_variant_t((long)(5)),_variant_t("����"));
	m_ExlRge.SetItem(_variant_t((long)(16)),_variant_t((long)(1)),_variant_t("������"));
	m_ExlRge.SetItem(_variant_t((long)(16)),_variant_t((long)(3)),_variant_t("����"));
	m_ExlRge.SetItem(_variant_t((long)(16)),_variant_t((long)(5)),_variant_t("����"));
	m_ExlRge.SetItem(_variant_t((long)(17)),_variant_t((long)(1)),_variant_t("������"));
	m_ExlRge.SetItem(_variant_t((long)(17)),_variant_t((long)(3)),_variant_t("����"));
	m_ExlRge.SetItem(_variant_t((long)(17)),_variant_t((long)(5)),_variant_t("����"));
	m_ExlRge.SetItem(_variant_t((long)(18)),_variant_t((long)(1)),_variant_t("�ʼ�"));
	//m_ExlRge.SetItem(_variant_t((long)(18)),_variant_t((long)(3)),_variant_t("����"));
	m_ExlRge.SetItem(_variant_t((long)(18)),_variant_t((long)(5)),_variant_t("����"));
	m_ExlRge.SetItem(_variant_t((long)(19)),_variant_t((long)(1)),_variant_t("��Ʒ��"));
	m_ExlRge.SetItem(_variant_t((long)(19)),_variant_t((long)(3)),_variant_t("��ݵ���"));
	m_ExlRge.SetItem(_variant_t((long)(19)),_variant_t((long)(5)),_variant_t("����"));


	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A3"), _variant_t("F3")));//��ȡ���е���"P"����
	m_ExlRge.SetColumnWidth(_variant_t((long)14));  //�����п�Ϊ100

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

	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("F1"))); 

	ft.AttachDispatch(m_ExlRge.GetFont()); 
	//ft.SetBold(_variant_t((long)0));//���� 
	ft.SetSize(_variant_t((long)15)); 
	//ft.SetColorIndex(_variant_t((long)2)); 

	//CellFormat cf; 
	//cf.AttachDispatch(m_ExlRge.GetCells()); 

	//����
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("F1")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4108));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"),_variant_t("F2")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4108));
	ft.AttachDispatch(m_ExlRge.GetFont()); 
	//ft.SetBold(_variant_t((long)0));//���� 
	ft.SetSize(_variant_t((long)14)); 
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
	int i = 0;
	for(i=1;i<=19;i++) 
	{
		if((i==1)||(i==2)||(i==7)||(i==14))
			continue;
		for(int j=1;j<=6;j++) 
		{
			CellName.Format("%c%d",j+64,i);//��Ԫ�������
			UnitRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t(CellName),_variant_t(CellName)));//���ص�Ԫ��
			//LineStyle=���� Weight=�߿� ColorIndex=�ߵ���ɫ(-4105Ϊ�Զ�)
			UnitRge.BorderAround(_variant_t((long)1),_variant_t((long)2),_variant_t((long)-4105),vtMissing);//���ñ߿�
		}
	} 
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("B13"),_variant_t("B13")));
	m_ExlRge.SetRowHeight(COleVariant((short)120));
	
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
