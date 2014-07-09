// Dialog_ModifyList.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_ModifyList.h"
#include "Dialog_Login2.h"

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
	//}}AFX_DATA_INIT
}


void CDialog_ModifyList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_ModifyList)
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
	//DDX_Text(pDX, IDC_EDIT_BILL, m_bill);
	//DDX_Text(pDX, IDC_EDIT_BOTTOM, m_bottom);
	//DDX_Text(pDX, IDC_EDIT_COLOR, m_color);
	//DDX_Text(pDX, IDC_EDIT_DEPARTMENT, m_department);
	DDX_Text(pDX, IDC_EDIT_ERRORRANGE, m_error_range);
	DDX_Text(pDX, IDC_EDIT_LISTID, m_listid);
	DDX_Text(pDX, IDC_EDIT_LISTTNAME, m_listname);
	//DDX_Text(pDX, IDC_EDIT_MATERIAL, m_material);
	DDX_Text(pDX, IDC_EDIT_MONDY, m_money);
	//DDX_Text(pDX, IDC_EDIT_PAINT, m_print);
	DDX_Text(pDX, IDC_EDIT_PEOPLE, m_people);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_phone);
	DDX_Text(pDX, IDC_EDIT_RECEIVE_NAME, m_receivename);
	//DDX_Text(pDX, IDC_EDIT_SHINE, m_shine);
	//DDX_Text(pDX, IDC_EDIT_SIZE, m_size);
	//DDX_Text(pDX, IDC_EDIT_TOTEL_NUMBER, m_totel_number);
	DDX_Text(pDX, IDC_EDIT_USAGE, m_usage);
	DDX_Text(pDX, IDC_EDIT_VOLUEME, m_volume);
	//DDX_Text(pDX, IDC_EDIT1_TRUE_NUMBER, m_true_number);
	DDX_Text(pDX, IDC_RICHEDIT_OTHER, m_other);
	DDX_Text(pDX, IDC_EDIT_QUERYLISTID, m_query_listid);
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
                int j = 0;
                j=mysql_num_fields(result);//�鿴������
				unsigned __int64 num = mysql_num_rows(result);//����
				int index = 0;
                sql_row=mysql_fetch_row(result);//��ȡ���������
				if(sql_row)
                {
					m_listid = sql_row[0];
					m_listname = sql_row[1];
					m_true_number = atoi(sql_row[2]);
					m_material = sql_row[3];
					m_volume = sql_row[4];
					m_str_reveive_time = sql_row[5];
					m_str_end_date = sql_row[6];
					//"" = sql_row[];
					m_people = sql_row[8];
					m_receivename = sql_row[9];
					m_phone = sql_row[10];
					m_address = sql_row[11];
					m_department = sql_row[12];
					m_modeling = atoi(sql_row[13]);
					m_design_server = atoi(sql_row[14]);
					m_scan = atoi(sql_row[15]);
					m_modeling_pring = atoi(sql_row[16]);
					m_has_modeling = atoi(sql_row[17]);
					m_no_modeling = atoi(sql_row[18]);
					m_size = sql_row[19];
					m_totel_number = atoi(sql_row[20]);
					m_color = sql_row[21];
					m_print = sql_row[22];
					m_shine = sql_row[23];
					m_bottom = sql_row[24];
					m_bill = sql_row[25];
					m_usage = sql_row[26];
					m_error_range = sql_row[27];
					m_money = sql_row[28];
					m_other = sql_row[29];

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

                    UpdateData(FALSE);
                }
				else
				{
					MessageBox("�޴˶����ţ�����������","��ʾ",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
					mysql_close(&myCont);//�Ͽ�����
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

void CDialog_ModifyList::OnModifylist() 
{
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
		if(len!=11 && len!=12)
		{
			MessageBox("��ϵ�绰Ϊ11Ϊ���֣�����������","��ʾ",MB_OK);
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

	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	mysql_init(&myCont);
	if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
	{
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
			return;
		}
		result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
		if(result)
		{
			unsigned __int64 num = mysql_num_rows(result);//����
			if(num==1)//���µ���
			{
				CDialog_Login2 login2;
				login2.m_permission = MODIFY_LIST_AFTER;
				if (login2.DoModal()!=IDOK)
				{
					MessageBox("�˶������ѱ��µ���ֻ�����ܲ���Ȩ���޸�","��ʾ",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
					if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
					mysql_close(&myCont);//�Ͽ�����
					return;
				}
				
			}
			else//δ�µ�
			{
				CDialog_Login2 login2;
				login2.m_permission = MODIFY_LIST_BEFORE;
				if (login2.DoModal()!=IDOK)
				{
					if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
					mysql_close(&myCont);//�Ͽ�����
					return;
				}

				sql.Format("select savelistpeople from baseinfo where listid=\"%s\" ",m_listid);
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
					if(sql_row==NULL)
					{
						MessageBox("�޴˶����ţ�����������","��ʾ",MB_OK);
						(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
						mysql_close(&myCont);//�Ͽ�����
						return;
					}
					if(strcmp(sql_row[0],login2.m_user))
					{
						MessageBox("ֻ���ύ�������˲����޸Ĵ˶���","��ʾ",MB_OK);
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



		sql.Format("update baseinfo set listname=\"%s\",truelistnumber=%d,material=\"%s\",volume=\"%s\",reveivedate=\"%s\",enddate=\"%s\",people=\"%s\",receivepeople=\"%s\",phone=\"%s\",address=\"%s\",department=\"%s\", modeling=%d, designserver=%d, scan=%d, modlingprint=%d, hasmodeling=%d, nomodeling=%d,  size=\"%s\",totelnumber=%d,color=\"%s\",paint=\"%s\",shine=\"%s\",bottom=\"%s\",bill=\"%s\",usage1=\"%s\",errorrange=\"%s\",money=\"%s\",other=\"%s\" where listid=\"%s\" ", \
		m_listname,m_true_number, m_material, m_volume, m_str_reveive_time,m_str_end_date, m_people,m_receivename ,m_phone, m_address,m_department , \
		m_modeling,m_design_server, m_scan, m_modeling_pring,m_has_modeling,m_no_modeling,m_size ,m_totel_number, \
		m_color,m_print,m_shine,m_bottom, m_bill, m_usage ,m_error_range ,m_money,m_other,m_listid);

		int ret = mysql_query(&myCont,sql);
		const char *error = mysql_error(&myCont);
		if(ret!= 0)
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
			MessageBox("�޸Ķ����ɹ�","��ʾ",MB_OK);
		}
		else
		{
			MessageBox("�޸Ķ���ʧ��","��ʾ",MB_OK);
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
	//MessageBox("�޸Ķ����ɹ�","��ʾ",MB_OK); 
}

void CDialog_ModifyList::OnStartList() 
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
	
	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	mysql_init(&myCont);
	if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
	{
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
			return;
		}
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
		sql.Format("insert into schedule(listid,listname,totelnumber,businessnumber,tcnumber,pdnumber,qcnumber,storagenumber,sendnumber,post,end,hasstoragenumber) \
		values (\"%s\",\"%s\",%d,0,%d,0,0,0,0,0,0,0)",m_listid,m_listname,totelnumber,totelnumber);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
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
			return;
		}
		result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
		if(result)
		{
			sql_row=mysql_fetch_row(result);
			starttime = sql_row[0];
		}

		sql.Format("insert into scheduledetail(listid,businessendtime,businessnumber,businesspeople,tcstarttime) \
		values (\"%s\",\"%s\",%d,\"%s\",\"%s\")",m_listid,starttime,totelnumber,login2.m_user,starttime);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			return;
		}

		sql.Format("update baseinfo set truelistnumber=%d  where listid=\"%s\" " ,m_true_number,m_listid);
		if(mysql_query(&myCont,sql)!= 0)
		{
			MessageBox("�ύ���ݿ�ʧ��","��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			return ;
		}
		if(mysql_affected_rows(&myCont)>0)
		{
			MessageBox("�µ��ɹ�","��ʾ",MB_OK);
		}
		else
		{
			MessageBox("�µ�ʧ��","��ʾ",MB_OK);
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
				(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
				mysql_close(&myCont);//�Ͽ�����
				return;
			}
			sql_row=mysql_fetch_row(result);
			if(sql_row==NULL)
			{
				MessageBox("�˶���������","��ʾ",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_LISTID)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_LISTID))->SetSel(0, -1);
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
