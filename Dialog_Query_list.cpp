// Dialog_Query_list.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_Query_list.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Query_list dialog


CDialog_Query_list::CDialog_Query_list(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Query_list::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Query_list)
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
	m_other = _T("");
	m_str_reveive_time = _T("");
	m_str_end_date = _T("");
	m_query_listid = _T("");
	//}}AFX_DATA_INIT
}


void CDialog_Query_list::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Query_list)
	DDX_Check(pDX, IDC_CHECK_DESIGN_SERVER, m_design_server);
	DDX_Check(pDX, IDC_CHECK_HAS_MODELING, m_has_modeling);
	DDX_Check(pDX, IDC_CHECK_MODELING, m_modeling);
	DDX_Check(pDX, IDC_CHECK_MODELING_PRINT, m_modeling_pring);
	DDX_Check(pDX, IDC_CHECK_NO_MODELING, m_no_modeling);
	DDX_Check(pDX, IDC_CHECK_SCAN, m_scan);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ENDDATE, m_enddate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_RECEIVEDATE, m_receivedate);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_address);
	DDX_Text(pDX, IDC_EDIT_BILL, m_bill);
	DDX_Text(pDX, IDC_EDIT_BOTTOM, m_bottom);
	DDX_Text(pDX, IDC_EDIT_COLOR, m_color);
	DDX_Text(pDX, IDC_EDIT_DEPARTMENT, m_department);
	DDX_Text(pDX, IDC_EDIT_ERRORRANGE, m_error_range);
	DDX_Text(pDX, IDC_EDIT_LISTID, m_listid);
	DDX_Text(pDX, IDC_EDIT_LISTTNAME, m_listname);
	DDX_Text(pDX, IDC_EDIT_MATERIAL, m_material);
	DDX_Text(pDX, IDC_EDIT_MONDY, m_money);
	DDX_Text(pDX, IDC_EDIT_PAINT, m_print);
	DDX_Text(pDX, IDC_EDIT_PEOPLE, m_people);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_phone);
	DDX_Text(pDX, IDC_EDIT_RECEIVE_NAME, m_receivename);
	DDX_Text(pDX, IDC_EDIT_SHINE, m_shine);
	DDX_Text(pDX, IDC_EDIT_SIZE, m_size);
	DDX_Text(pDX, IDC_EDIT_TOTEL_NUMBER, m_totel_number);
	DDX_Text(pDX, IDC_EDIT_USAGE, m_usage);
	DDX_Text(pDX, IDC_EDIT_VOLUEME, m_volume);
	DDX_Text(pDX, IDC_RICHEDIT_OTHER, m_other);
	DDX_Text(pDX, IDC_EDIT_QUERYLISTID, m_query_listid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Query_list, CDialog)
	//{{AFX_MSG_MAP(CDialog_Query_list)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Query_list message handlers

BOOL CDialog_Query_list::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CTime time1 = CTime::GetCurrentTime();
	m_receivedate = time1;
	m_enddate = time1;	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDialog_Query_list::PreTranslateMessage(MSG* pMsg) 
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

void CDialog_Query_list::OnOK() 
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
                int j;
                j=mysql_num_fields(result);//�鿴������
				unsigned __int64 num = mysql_num_rows(result);//����
				int index = 0;
                sql_row=mysql_fetch_row(result);//��ȡ���������
                {
					m_listid = sql_row[0];
					m_listname = sql_row[1];
					//m_true_number = atoi(sql_row[2]);
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
                    UpdateData(FALSE);
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
