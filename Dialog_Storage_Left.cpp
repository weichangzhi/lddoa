// Dialog_Storage_Left.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_Storage_Left.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_Left dialog


Dialog_Storage_Left::Dialog_Storage_Left(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_Storage_Left::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_Storage_Left)
	m_time = 0;
	//}}AFX_DATA_INIT
}


void Dialog_Storage_Left::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_Storage_Left)
	DDX_Control(pDX, IDC_LIST_TOTAL, m_listTotal);
	DDX_Control(pDX, IDOK, m_btok);
	DDX_Control(pDX, IDC_LIST_STORAGE_LEFT, m_list_StorageLeft);
	DDX_Control(pDX, IDC_BUTTON_EXCEL, m_btexcel);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_time);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_Storage_Left, CDialog)
	//{{AFX_MSG_MAP(Dialog_Storage_Left)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL, OnButtonExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_Left message handlers

BOOL Dialog_Storage_Left::PreTranslateMessage(MSG* pMsg) 
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

BOOL Dialog_Storage_Left::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CTime time1 = CTime::GetCurrentTime();
	m_time = time1;

	m_list_StorageLeft.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list_StorageLeft.InsertColumn(0, _T("���"), LVCFMT_LEFT,60);
	m_list_StorageLeft.InsertColumn(1, _T("SCB"), LVCFMT_LEFT,100);
	m_list_StorageLeft.InsertColumn(2, _T("����"), LVCFMT_LEFT,200);
	m_list_StorageLeft.InsertColumn(3, _T("����"), LVCFMT_LEFT,100);
	m_list_StorageLeft.InsertColumn(4, _T("��λ"), LVCFMT_LEFT,100);
	m_list_StorageLeft.InsertColumn(5, _T("����"), LVCFMT_LEFT,100);
	m_list_StorageLeft.InsertColumn(6, _T("���"), LVCFMT_LEFT,100);

	m_listTotal.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listTotal.InsertColumn(0, _T("�ϼ�"), LVCFMT_LEFT,60);
	m_listTotal.InsertColumn(1, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(2, _T(""), LVCFMT_LEFT,200);
	m_listTotal.InsertColumn(3, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(4, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(5, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(6, _T(""), LVCFMT_LEFT,100);
	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_Storage_Left::OnButtonExcel() 
{
	CreateExcel("�������ѯ.xls",&m_list_StorageLeft);
}

void Dialog_Storage_Left::OnOK() 
{
	m_list_StorageLeft.DeleteAllItems();
	UpdateData();
	CString csSql;
	CString starttime;
	starttime.Format("%04d-%02d-%02d 23:59:59",m_time.GetYear(),m_time.GetMonth(),m_time.GetDay());

	csSql.Format("select scb,item_name,item_number,item_unit,item_price,item_money from storage_left where item_time<=\"%s\" " ,starttime); 

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
				int number = 0;
				float money = 0.0;
                while(sql_row=mysql_fetch_row(result))//��ȡ���������
                {
					CString strindex ;
					strindex.Format("%d",index+1);
					m_list_StorageLeft.InsertItem(index,strindex);
					m_list_StorageLeft.SetItemText(index,1,sql_row[0]);
					m_list_StorageLeft.SetItemText(index,2,sql_row[1]);
					m_list_StorageLeft.SetItemText(index,3,sql_row[2]);
					m_list_StorageLeft.SetItemText(index,4,sql_row[3]);
					m_list_StorageLeft.SetItemText(index,5,sql_row[4]);
					m_list_StorageLeft.SetItemText(index,6,sql_row[5]);
					number += atoi(sql_row[2]);
					money += atof(sql_row[5]);
					if(index%2==0)
						m_list_StorageLeft.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
					index++;
                }
				if(index!=0)
				{
					CString strtmp;
					strtmp.Format("%d",number);
					m_listTotal.DeleteColumn(3);
					m_listTotal.InsertColumn(3,strtmp,LVCFMT_LEFT,100);
					strtmp.Format("%0.1f",money);
					m_listTotal.DeleteColumn(6);
					m_listTotal.InsertColumn(6,strtmp,LVCFMT_LEFT,100);
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
