// Dialog_FI_Proceeds.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_FI_Proceeds.h"
#include "Dialog_progress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_FI_Proceeds dialog


Dialog_FI_Proceeds::Dialog_FI_Proceeds(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_FI_Proceeds::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_FI_Proceeds)
	m_timeProceeds = 0;
	m_bill_id = _T("");
	m_bill_way = _T("");
	m_comment = _T("");
	m_listid = _T("");
	m_money_bill = _T("");
	m_money_proceeds = _T("");
	m_money_totel = _T("");
	m_people_business = _T("");
	m_people_fi = _T("");
	m_proceeds_way = _T("");
	m_query_listid = _T("");
	m_timeBill = 0;
	m_comment_Bill = _T("");
	m_people_bill = _T("");
	m_listName = _T("");
	//}}AFX_DATA_INIT
}


void Dialog_FI_Proceeds::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_FI_Proceeds)
	DDX_Control(pDX, IDC_BUTTON_INPUT, m_output);
	DDX_Control(pDX, IDC_BUTTON_OUTPUT, m_input);
	DDX_Control(pDX, IDC_COMBO_PROCEEDS_WAY, m_comProceedsWay);
	DDX_Control(pDX, IDC_COMBO_BILL_WAY, m_comBillWay);
	DDX_Control(pDX, IDCANCEL, m_btcancel);
	DDX_Control(pDX, IDOK, m_btok);
	DDX_Control(pDX, IDC_BUTTON_PROCEEDS, m_btquery);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_RECEIVEDATE, m_timeProceeds);
	DDX_Text(pDX, IDC_EDIT_BILL_ID, m_bill_id);
	DDX_Text(pDX, IDC_COMBO_BILL_WAY, m_bill_way);
	DDX_Text(pDX, IDC_EDIT_COMMENT, m_comment);
	DDX_Text(pDX, IDC_EDIT_LISTID, m_listid);
	DDX_Text(pDX, IDC_EDIT_MONEY_BILL, m_money_bill);
	DDX_Text(pDX, IDC_EDIT_MONEY_PROCEEDS, m_money_proceeds);
	DDX_Text(pDX, IDC_EDIT_MONEY_TOTEL, m_money_totel);
	DDX_Text(pDX, IDC_EDIT_PEOPLE_BUSINESS, m_people_business);
	DDX_Text(pDX, IDC_EDIT_PEOPLE_FI, m_people_fi);
	DDX_Text(pDX, IDC_COMBO_PROCEEDS_WAY, m_proceeds_way);
	DDX_Text(pDX, IDC_EDIT_QUERYLISTID, m_query_listid);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BILL, m_timeBill);
	DDX_Text(pDX, IDC_EDIT_COMMENT_BILL, m_comment_Bill);
	DDX_Text(pDX, IDC_EDIT_PEOPLE_BILL, m_people_bill);
	DDX_Text(pDX, IDC_EDIT_LISTNAME, m_listName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_FI_Proceeds, CDialog)
	//{{AFX_MSG_MAP(Dialog_FI_Proceeds)
	ON_BN_CLICKED(IDC_BUTTON_PROCEEDS, OnProceeds)
	ON_BN_CLICKED(IDC_BUTTON_INPUT, OnButtonInput)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT, OnButtonOutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_FI_Proceeds message handlers

BOOL Dialog_FI_Proceeds::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CTime time1 = CTime::GetCurrentTime();
	m_timeProceeds = time1;
	m_timeBill = time1;
	m_people_bill = m_people_fi = g_user;
	m_comProceedsWay.InsertString(0,"����ת��");
	m_comProceedsWay.InsertString(1,"�ֽ�");
	m_comBillWay.InsertString(0,"��ͨ��Ʊ");
	m_comBillWay.InsertString(1,"ר�÷�Ʊ");
	m_comProceedsWay.SetCurSel(0);
	m_comBillWay.SetCurSel(0);
	m_proceeds_way = "����ת��";
	m_bill_way = "��ͨ��Ʊ";

	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_FI_Proceeds::OnProceeds() 
{
	UpdateData();
	if(m_listid.IsEmpty())
	{
		MessageBox("�����붩���ţ�","��ʾ",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
		return;
	}
	if(!(m_money_totel.IsEmpty()))
	{
		if(!IsNum(m_money_totel))
		{
			MessageBox("����������Ϊ���֣�����������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_TOTEL)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_TOTEL))->SetSel(0, -1);
			return;
		}
		if(atof(m_money_totel)>10000000)
		{
			MessageBox("��������һǧ������������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_TOTEL)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_TOTEL))->SetSel(0, -1);
			return;
		}
	}
	if(!(m_money_proceeds.IsEmpty()))
	{
		if(!IsNum(m_money_proceeds))
		{
			MessageBox("����������Ϊ���֣�����������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS))->SetSel(0, -1);
			return;
		}
		if(atof(m_money_proceeds)>10000000)
		{
			MessageBox("��������һǧ������������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS))->SetSel(0, -1);
			return;
		}
	}
	if(!(m_money_bill.IsEmpty()))
	{
		if(!IsNum(m_money_bill))
		{
			MessageBox("����������Ϊ���֣�����������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL))->SetSel(0, -1);
			return;
		}
		if(atof(m_money_bill)>10000000)
		{
			MessageBox("��������һǧ������������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL))->SetSel(0, -1);
			return;
		}
	}


	CString strtimeproceeds;
	strtimeproceeds.Format("%04d-%02d-%02d",m_timeProceeds.GetYear(),m_timeProceeds.GetMonth(),m_timeProceeds.GetDay());
	CString strtimebill;
	strtimebill.Format("%04d-%02d-%02d",m_timeBill.GetYear(),m_timeBill.GetMonth(),m_timeBill.GetDay());


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
		sql = "select moneyproceeds,moneybill,ficheck from fiproceeds where listid='" + m_query_listid +"'";
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
				//�޸ļ�¼	
				float money_proceeds = 0;
				float money_bill = 0;
				int check = 0;
				while(sql_row=mysql_fetch_row(result))//��ȡ���������
                {
					if(sql_row[0]!=NULL)
						money_proceeds = atof(sql_row[0]);
					if(sql_row[1]!=NULL)
						money_bill = atof(sql_row[1]);
					if(sql_row[2]!=NULL)
						check = atoi(sql_row[2]);					
                }//while
				if(check==1)
				{
					MessageBox("�˶����ѱ��������������տ�","��ʾ",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_LISTID_QUERY)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_LISTID_QUERY))->SetSel(0, -1);
					mysql_close(&myCont);//�Ͽ�����
					dlgpro->endpos();
					return;
				}
				CString strmoney_proceeds;
				CString strmoney_bill;
				strmoney_proceeds.Format("%0.2f",money_proceeds+atof(m_money_proceeds));
				strmoney_bill.Format("%0.2f",money_bill+atof(m_money_bill));
				if(atof(strmoney_proceeds)>atof(m_money_totel))
				{
					CString str;
					str.Format("�˶�����ǩ�����Ϊ%s,���տ���%0.2f,�����տ���ܳ��� %0.2f ,�Ƿ������",m_money_totel,money_proceeds,atof(m_money_totel)-money_proceeds);
					int ret = MessageBox(str,"��ʾ",MB_OKCANCEL);
					if(ret!=1)
					{
						(CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS))->SetSel(0, -1);
						mysql_close(&myCont);//�Ͽ�����
						dlgpro->endpos();
						return;
					}					
				}
				if(atof(strmoney_bill)>atof(m_money_totel))
				{
					CString str;
					str.Format("�˶�����ǩ�����Ϊ%s,�ѿ�Ʊ���%0.2f,���¿�Ʊ���ܳ��� %0.2f ,�Ƿ������",m_money_totel,money_bill,atof(m_money_totel)-money_bill);
					if(MessageBox(str,"��ʾ",MB_OKCANCEL)!=1)
					{
						(CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL))->SetSel(0, -1);
						mysql_close(&myCont);//�Ͽ�����
						dlgpro->endpos();
						return;
					}					
				}
				dlgpro->setpos(800);
				sql.Format("update fiproceeds set listname=\"%s\",moneytotel=\"%s\",peoplebusiness=\"%s\",proceedsway=\"%s\",moneyproceeds=\"%s\",peopleproceeds=\"%s\",timeproceeds=\"%s\",comment=\"%s\",billway=\"%s\",moneybill=\"%s\",billid=\"%s\",peoplebill=\"%s\",timebill=\"%s\",commentbill=\"%s\" where listid=\"%s\" ",
					m_listName,m_money_totel,m_people_business,m_proceeds_way,strmoney_proceeds,m_people_fi,strtimeproceeds,m_comment,m_bill_way,strmoney_bill,m_bill_id,m_people_bill,strtimebill,m_comment_Bill,m_query_listid);
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
			{//������¼
				dlgpro->setpos(700);
				sql.Format("select * from baseinfo where listid=\"%s\" ",m_query_listid);
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
					dlgpro->setpos(750);
					unsigned __int64 num = mysql_num_rows(result);//����
					if(num!=1)//
					{
						MessageBox("�޴˶�����δ���涩��","��ʾ",MB_OK);
						(CEdit*)GetDlgItem(IDC_EDIT_LISTID_QUERY)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_LISTID_QUERY))->SetSel(0, -1);
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
				dlgpro->setpos(800);

				sql.Format("insert into fiproceeds values (\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\")",
					m_listid,m_listName,m_money_totel,m_people_business,m_proceeds_way,m_money_proceeds,m_people_fi,strtimeproceeds,m_comment,m_bill_way,m_money_bill,m_bill_id,0,m_people_bill,strtimebill,m_comment_Bill);
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
		//detail
		dlgpro->setpos(900);
		sql.Format("insert into fidetail values (%d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d)",
				0,m_listid,m_listName,m_money_totel,m_people_business,m_proceeds_way,m_money_proceeds,m_people_fi,strtimeproceeds,m_comment,m_bill_way,m_money_bill,m_bill_id,m_people_bill,strtimebill,m_comment_Bill,0);
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
	MessageBox("�տƱ�ɹ�","��ʾ",MB_OK);
}


BOOL Dialog_FI_Proceeds::PreTranslateMessage(MSG* pMsg) 
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

void Dialog_FI_Proceeds::OnOK() 
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
		csSql.Format("select listname,people,money from baseinfo where listid=\"%s\" ",m_query_listid);	
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
					m_listid = m_query_listid;
					m_listName = sql_row[0];
					m_money_bill = m_money_proceeds = m_money_totel = sql_row[2];
					m_people_business = sql_row[1];

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
	//CDialog::OnOK();
}

void Dialog_FI_Proceeds::OnProceedsInput() 
{
	UpdateData();
	if(m_listid.IsEmpty())
	{
		MessageBox("�����붩���ţ�","��ʾ",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_QUERYLISTID)->SetFocus();
		return;
	}
	if(!(m_money_totel.IsEmpty()))
	{
		if(!IsNum(m_money_totel))
		{
			MessageBox("����������Ϊ���֣�����������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_TOTEL)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_TOTEL))->SetSel(0, -1);
			return;
		}
		if(atof(m_money_totel)>10000000)
		{
			MessageBox("��������һǧ������������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_TOTEL)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_TOTEL))->SetSel(0, -1);
			return;
		}
	}
	if(!(m_money_proceeds.IsEmpty()))
	{
		if(!IsNum(m_money_proceeds))
		{
			MessageBox("����������Ϊ���֣�����������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS))->SetSel(0, -1);
			return;
		}
		if(atof(m_money_proceeds)>10000000)
		{
			MessageBox("��������һǧ������������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS))->SetSel(0, -1);
			return;
		}
	}
	if(!(m_money_bill.IsEmpty()))
	{
		if(!IsNum(m_money_bill))
		{
			MessageBox("����������Ϊ���֣�����������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL))->SetSel(0, -1);
			return;
		}
		if(atof(m_money_bill)>10000000)
		{
			MessageBox("��������һǧ������������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL))->SetSel(0, -1);
			return;
		}
	}


	CString strtimeproceeds;
	strtimeproceeds.Format("%04d-%02d-%02d",m_timeProceeds.GetYear(),m_timeProceeds.GetMonth(),m_timeProceeds.GetDay());
	CString strtimebill;
	strtimebill.Format("%04d-%02d-%02d",m_timeBill.GetYear(),m_timeBill.GetMonth(),m_timeBill.GetDay());


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
		sql = "select moneyproceeds,moneybill,ficheck from fiproceeds where listid='" + m_query_listid +"'";
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
				//�޸ļ�¼	
				float money_proceeds = 0;
				float money_bill = 0;
				int check = 0;
				while(sql_row=mysql_fetch_row(result))//��ȡ���������
                {
					if(sql_row[0]!=NULL)
						money_proceeds = atof(sql_row[0]);
					if(sql_row[1]!=NULL)
						money_bill = atof(sql_row[1]);
					if(sql_row[2]!=NULL)
						check = atoi(sql_row[2]);					
                }//while
				if(check==1)
				{
					MessageBox("�˶����ѱ��������������տ�","��ʾ",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_LISTID_QUERY)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_LISTID_QUERY))->SetSel(0, -1);
					mysql_close(&myCont);//�Ͽ�����
					dlgpro->endpos();
					return;
				}
				CString strmoney_proceeds;
				CString strmoney_bill;
				strmoney_proceeds.Format("%0.2f",money_proceeds+atof(m_money_proceeds));
				strmoney_bill.Format("%0.2f",money_bill+atof(m_money_bill));
				if(atof(strmoney_proceeds)>atof(m_money_totel))
				{
					CString str;
					str.Format("�˶���%s��ǩ�����Ϊ%s,���տ���%0.2f,�����տ���ܳ��� %0.2f ,�Ƿ������",m_query_listid,m_money_totel,money_proceeds,atof(m_money_totel)-money_proceeds);
					int ret = MessageBox(str,"��ʾ",MB_OKCANCEL);
					if(ret!=1)
					{
						(CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_MONEY_PROCEEDS))->SetSel(0, -1);
						mysql_close(&myCont);//�Ͽ�����
						dlgpro->endpos();
						return;
					}					
				}
				if(atof(strmoney_bill)>atof(m_money_totel))
				{
					CString str;
					str.Format("�˶���%s��ǩ�����Ϊ%s,�ѿ�Ʊ���%0.2f,���¿�Ʊ���ܳ��� %0.2f ,�Ƿ������",m_query_listid,m_money_totel,money_bill,atof(m_money_totel)-money_bill);
					if(MessageBox(str,"��ʾ",MB_OKCANCEL)!=1)
					{
						(CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_MONEY_BILL))->SetSel(0, -1);
						mysql_close(&myCont);//�Ͽ�����
						dlgpro->endpos();
						return;
					}					
				}
				dlgpro->setpos(800);
				sql.Format("update fiproceeds set listname=\"%s\",moneytotel=\"%s\",peoplebusiness=\"%s\",proceedsway=\"%s\",moneyproceeds=\"%s\",peopleproceeds=\"%s\",timeproceeds=\"%s\",comment=\"%s\",billway=\"%s\",moneybill=\"%s\",billid=\"%s\",peoplebill=\"%s\",timebill=\"%s\",commentbill=\"%s\" where listid=\"%s\" ",
					m_listName,m_money_totel,m_people_business,m_proceeds_way,strmoney_proceeds,m_people_fi,strtimeproceeds,m_comment,m_bill_way,strmoney_bill,m_bill_id,m_people_bill,strtimebill,m_comment_Bill,m_query_listid);
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
			{//������¼
				dlgpro->setpos(700);
				sql.Format("select * from baseinfo where listid=\"%s\" ",m_query_listid);
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
					dlgpro->setpos(750);
					unsigned __int64 num = mysql_num_rows(result);//����
					if(num!=1)//
					{
						CString str;
						str.Format("�޴˶���%s��˶���δ����.",m_query_listid);
						MessageBox(str,"��ʾ",MB_OK);
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
				dlgpro->setpos(800);

				sql.Format("insert into fiproceeds values (\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",\"%s\",\"%s\")",
					m_listid,m_listName,m_money_totel,m_people_business,m_proceeds_way,m_money_proceeds,m_people_fi,strtimeproceeds,m_comment,m_bill_way,m_money_bill,m_bill_id,0,m_people_bill,strtimebill,m_comment_Bill);
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
		//detail
		dlgpro->setpos(900);
		sql.Format("insert into fidetail values (%d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d)",
				0,m_listid,m_listName,m_money_totel,m_people_business,m_proceeds_way,m_money_proceeds,m_people_fi,strtimeproceeds,m_comment,m_bill_way,m_money_bill,m_bill_id,m_people_bill,strtimebill,m_comment_Bill,0);
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
}

void Dialog_FI_Proceeds::OnButtonInput() 
{
	CString FilePathName;
    CFileDialog dlg(TRUE, //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
        NULL, 
        NULL,
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        (LPCTSTR)_TEXT("xls Files (*.xls)|*.xls|All Files (*.*)|*.*||"),
        NULL);
    if(dlg.DoModal()==IDOK)
    {
        FilePathName=dlg.GetPathName(); //�ļ�����������FilePathName��
    }
    else
    {
         return;
    }

	_Application   m_oExcelApp;              // Excel����
	_Worksheet     m_oWorkSheet;     // ������
	_Workbook      m_oWorkBook;      // ������
	Workbooks      m_oWorkBooks;    // ����������
	Worksheets     m_oWorkSheets;    // ��������
	Range          m_oCurrRange;      // ʹ������
	if (!m_oExcelApp.CreateDispatch( _T( "Excel.Application" ), NULL ) )
	{
		::MessageBox( NULL, _T( "����Excel����ʧ�ܣ�" ), _T( "������ʾ��" ), MB_OK | MB_ICONERROR);
		return;
	}

	//����Ϊ��ʾ
	m_oExcelApp.SetVisible(FALSE);
	m_oWorkBooks.AttachDispatch( m_oExcelApp.GetWorkbooks(), TRUE ); //û��������䣬������ļ�����ʧ�ܡ�

	LPDISPATCH lpDisp = NULL;
	COleVariant covTrue((short)TRUE);
	COleVariant covFalse((short)FALSE);
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR); 
	Range       oCurCell;

// 	CString theAppPath,theAppName; 
// 	char Path[MAX_PATH]; 
// //�ҵ��ļ�
// 	GetModuleFileName(NULL,Path,MAX_PATH);//�õ�Ӧ�ó����ȫ·�� 
// 	theAppPath=(CString)Path; 
// 
// 	theAppName=AfxGetApp()->m_pszAppName; 
// 	theAppName+=".exe"; 
// 
// 	//�������ļ���ȥ�� 
// 	int length1,length2; 
// 
// 	length1=theAppPath.GetLength(); 
// 	length2=theAppName.GetLength(); 
// 
// 	theAppPath.Delete(length1-length2,length2); 
// 	CString strFilePath=""; 
// 	strFilePath=theAppPath+"�տƱ.xls";//EXCELģ���·��

	// ���ļ�
	lpDisp = m_oWorkBooks.Open( FilePathName,
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing),
								  _variant_t(vtMissing) );
	// ��û��WorkBook( ������ )
	m_oWorkBook.AttachDispatch( lpDisp, TRUE );
	// ��û��WorkSheet( ������ )
	m_oWorkSheet.AttachDispatch( m_oWorkBook.GetActiveSheet(), TRUE );
	// ���ʹ�õ�����Range( ���� )
	m_oCurrRange.AttachDispatch( m_oWorkSheet.GetUsedRange(), TRUE );

	// ���ʹ�õ�����
	long lgUsedRowNum = 0;
	m_oCurrRange.AttachDispatch( m_oCurrRange.GetRows(), TRUE );
	lgUsedRowNum = m_oCurrRange.GetCount();
	// ���ʹ�õ�����
	long lgUsedColumnNum = 0;
	m_oCurrRange.AttachDispatch( m_oCurrRange.GetColumns(), TRUE );
	lgUsedColumnNum = m_oCurrRange.GetCount();
	// ��ȡSheet������
	CString strSheetName = m_oWorkSheet.GetName();

	//�õ�ȫ��Cells����ʱ,CurrRange��cells�ļ���
	m_oCurrRange.AttachDispatch( m_oWorkSheet.GetCells(), TRUE );

	oCurCell.AttachDispatch( m_oCurrRange.GetItem( COleVariant( (long)(1)), COleVariant( (long)1 ) ).pdispVal, TRUE );
	VARIANT varItemName = oCurCell.GetText();
	CString strItemName;
	strItemName = varItemName.bstrVal;
	if(strItemName.Compare("�տƱ")!=0)
	{
		MessageBox("���ݸ�ʽ����ȷ���뵼����ȷ��ʽ������.","��ʾ",MB_OK);
		return;
	}

	// ��������Excel���
	for ( int i = 4; i <= lgUsedRowNum; i++)
	{
		for ( int j = 2; j <= lgUsedColumnNum; j++ )
		{
			oCurCell.AttachDispatch( m_oCurrRange.GetItem( COleVariant( (long)(i)), COleVariant( (long)j ) ).pdispVal, TRUE );
			varItemName = oCurCell.GetText();
			strItemName = varItemName.bstrVal;
			if(j==2) m_listid = m_query_listid = strItemName;
			if(m_listid.IsEmpty())
				break;
			if(j==3) m_listName = strItemName;
			if(j==4) m_money_totel = strItemName;
			if(j==5) m_people_business = strItemName;
			if(j==6) m_proceeds_way = strItemName;
			if(j==7) m_money_proceeds = strItemName;
			if(j==8) m_people_fi = strItemName;
			if(j==10) m_comment = strItemName;
			if(j==11) m_bill_way = strItemName;
			if(j==12) m_money_bill = strItemName;
			if(j==13) m_people_bill = strItemName;
			if(j==14) m_bill_id = strItemName;
			if(j==16) m_comment_Bill = strItemName;
			if(j==9)
			{
				if(strItemName.GetLength()<10)
				{
					CTime time1 = CTime::GetCurrentTime();
					m_timeProceeds = time1;
				}
				else
				{
					CTime timeTmp(atoi(strItemName.Mid(0,4)),atoi(strItemName.Mid(5,2)),atoi(strItemName.Mid(8,2)),0,0,0,0);
					m_timeProceeds = timeTmp;
				}
				
			}
			if(j==15)
			{
				if(strItemName.GetLength()<10)
				{
					CTime time1 = CTime::GetCurrentTime();
					m_timeProceeds = time1;
				}
				else
				{
					CTime timeTmp1(atoi(strItemName.Mid(0,4)),atoi(strItemName.Mid(5,2)),atoi(strItemName.Mid(8,2)),0,0,0,0);
					m_timeBill = timeTmp1;
				}
				
			}
			
		}
		UpdateData(FALSE);
		if(m_listid.IsEmpty())
			continue ;
		OnProceedsInput();
		m_listid = m_query_listid = "";
		m_listName = "";
		m_money_totel = "";
		m_people_business = "";
		m_proceeds_way = "";
		m_money_proceeds = "";
		m_people_fi = "";
		m_comment = "";
		m_bill_way = "";
		m_money_bill = "";
		m_people_bill = "";
		m_bill_id = "";
		m_comment_Bill = "";
		CTime time1 = CTime::GetCurrentTime();
		m_timeBill = m_timeProceeds = time1;
	}
	MessageBox("�տƱ�����.","��ʾ",MB_OK);

	// �ر�
	m_oWorkBook.Close( covOptional, COleVariant( FilePathName ), covOptional );
	m_oWorkBooks.Close();
	// �ͷ�
	m_oCurrRange.ReleaseDispatch();
	m_oWorkSheet.ReleaseDispatch();
	m_oWorkSheets.ReleaseDispatch();
	m_oWorkBook.ReleaseDispatch();
	m_oWorkBooks.ReleaseDispatch();
	m_oExcelApp.ReleaseDispatch();
	m_oExcelApp.Quit();    // ����������Ƴ�Excel��������������е�EXCEL���̻��Զ�������
	
}

void Dialog_FI_Proceeds::OnButtonOutput() 
{
	UpdateData();
	CString strTimeProceeds,strTimeBill;
	strTimeProceeds.Format("%04d-%02d-%02d",m_timeProceeds.GetYear(),m_timeProceeds.GetMonth(),m_timeProceeds.GetDay());
	strTimeBill.Format("%04d-%02d-%02d",m_timeBill.GetYear(),m_timeBill.GetMonth(),m_timeBill.GetDay());
	CString filename ;
	filename.Format("�տƱ.xls");
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
	m_ExlSheet.SetName(filename); 

	m_ExlRge.AttachDispatch(m_ExlSheet.GetCells(),TRUE);//�������е�Ԫ��
	m_ExlRge.SetNumberFormatLocal(COleVariant("@")); 

	//�ϲ���Ԫ��
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("P1")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("B2"),_variant_t("E2")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("F2"),_variant_t("J2")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("K2"),_variant_t("P2")),TRUE); 
    m_ExlRge.Merge(_variant_t((long)0));
	////////���ñ������//////// 

	m_ExlRge.AttachDispatch(m_ExlSheet.GetCells(),TRUE);//�������е�Ԫ��
	m_ExlRge.SetItem(_variant_t((long)(1)),_variant_t((long)(1)),_variant_t("�տƱ"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(2)),_variant_t("������Ϣ"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(6)),_variant_t("�տ�"));
	m_ExlRge.SetItem(_variant_t((long)(2)),_variant_t((long)(11)),_variant_t("��Ʊ"));

	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(1)),_variant_t("���"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(2)),_variant_t("������"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(3)),_variant_t("��������"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(4)),_variant_t("�������"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(5)),_variant_t("ҵ�񾭰���"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(6)),_variant_t("�տʽ"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(7)),_variant_t("�տ���"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(8)),_variant_t("�տ���"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(9)),_variant_t("�տ�����"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(10)),_variant_t("�տע"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(11)),_variant_t("��Ʊ����"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(12)),_variant_t("��Ʊ���"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(13)),_variant_t("��Ʊ��"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(14)),_variant_t("��Ʊ����"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(15)),_variant_t("��Ʊ����"));
	m_ExlRge.SetItem(_variant_t((long)(3)),_variant_t((long)(16)),_variant_t("��Ʊ��ע"));

	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(1)),_variant_t("1"));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(2)),_variant_t(m_listid));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(3)),_variant_t(m_listName));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(4)),_variant_t(m_money_totel));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(5)),_variant_t(m_people_business));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(6)),_variant_t(m_proceeds_way));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(7)),_variant_t(m_money_proceeds));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(8)),_variant_t(m_people_fi));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(9)),_variant_t(strTimeProceeds));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(10)),_variant_t(m_comment));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(11)),_variant_t(m_bill_way));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(12)),_variant_t(m_money_bill));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(13)),_variant_t(m_people_bill));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(14)),_variant_t(m_bill_id));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(15)),_variant_t(strTimeBill));
	m_ExlRge.SetItem(_variant_t((long)(4)),_variant_t((long)(16)),_variant_t(m_comment_Bill));

	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"), _variant_t("A4")));//��ȡ���е���"P"����
	m_ExlRge.SetColumnWidth(_variant_t((long)6));  //�����п�Ϊ100
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("B3"), _variant_t("P20")));//��ȡ���е���"P"����
	m_ExlRge.SetColumnWidth(_variant_t((long)14));  //�����п�Ϊ100

	//m_ExlRge.AttachDispatch(m_ExlSheet.GetUsedRange());//������ʹ�õĵ�Ԫ�� 
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A3"), _variant_t("P20")));//��ȡ���е���"P"����
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

	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("P1"))); 

	ft.AttachDispatch(m_ExlRge.GetFont()); 
	//ft.SetBold(_variant_t((long)0));//���� 
	ft.SetSize(_variant_t((long)15)); 
	//ft.SetColorIndex(_variant_t((long)2)); 

	//CellFormat cf; 
	//cf.AttachDispatch(m_ExlRge.GetCells()); 

	//����
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("P1")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4108));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"),_variant_t("P2")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4108));

	ft.AttachDispatch(m_ExlRge.GetFont());
	//ft.SetBold(_variant_t((long)0));//����
	ft.SetSize(_variant_t((long)14));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("P1")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4108));
	ft.AttachDispatch(m_ExlRge.GetFont());
	//ft.SetBold(_variant_t((long)0));//����
	ft.SetSize(_variant_t((long)14));
	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"),_variant_t("P2")));
	m_ExlRge.SetHorizontalAlignment(_variant_t((long)-4108));
	ft.AttachDispatch(m_ExlRge.GetFont());
	//ft.SetBold(_variant_t((long)0));//����
	ft.SetSize(_variant_t((long)14));


	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A3"),_variant_t("P3")));
	ft.AttachDispatch(m_ExlRge.GetFont());
	ft.SetColor( _variant_t((long) RGB(255,0,0 )) );
	ft.SetSize(_variant_t((long)12));//�ֺ�

	m_ExlRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A4"),_variant_t("P20")));
	ft.AttachDispatch(m_ExlRge.GetFont());
	ft.SetColor( _variant_t((long) RGB(32,32,32)) );
	ft.SetSize(_variant_t((long)12));//�ֺ�

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
	for(i=3;i<=20;i++) 
	{
		for(int j=1;j<=16;j++) 
		{
			CellName.Format("%c%d",j+64,i);//��Ԫ�������
			UnitRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t(CellName),_variant_t(CellName)));//���ص�Ԫ��
			//LineStyle=���� Weight=�߿� ColorIndex=�ߵ���ɫ(-4105Ϊ�Զ�)
			UnitRge.BorderAround(_variant_t((long)1),_variant_t((long)2),_variant_t((long)-4105),vtMissing);//���ñ߿�
		}
	}
	UnitRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A1"),_variant_t("P1")));//���ص�Ԫ��
	UnitRge.BorderAround(_variant_t((long)1),_variant_t((long)2),_variant_t((long)-4105),vtMissing);//���ñ߿�
	UnitRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("A2"),_variant_t("A2")));//���ص�Ԫ��
	UnitRge.BorderAround(_variant_t((long)1),_variant_t((long)2),_variant_t((long)-4105),vtMissing);//���ñ߿�
	UnitRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("B2"),_variant_t("E2")));//���ص�Ԫ��
	UnitRge.BorderAround(_variant_t((long)1),_variant_t((long)2),_variant_t((long)-4105),vtMissing);//���ñ߿�
	UnitRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("F2"),_variant_t("J2")));//���ص�Ԫ��
	UnitRge.BorderAround(_variant_t((long)1),_variant_t((long)2),_variant_t((long)-4105),vtMissing);//���ñ߿�
	UnitRge.AttachDispatch(m_ExlSheet.GetRange(_variant_t("K2"),_variant_t("P2")));//���ص�Ԫ��
	UnitRge.BorderAround(_variant_t((long)1),_variant_t((long)2),_variant_t((long)-4105),vtMissing);//���ñ߿�
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

	//�ͷŶ����൱��Ҫ
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
