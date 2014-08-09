// Dialog_Storage_Out_Detail.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_Storage_Out_Detail.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_Out_Detail dialog


Dialog_Storage_Out_Detail::Dialog_Storage_Out_Detail(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_Storage_Out_Detail::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_Storage_Out_Detail)
	m_timebegin = 0;
	m_timeend = 0;
	//}}AFX_DATA_INIT
}


void Dialog_Storage_Out_Detail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_Storage_Out_Detail)
	DDX_Control(pDX, IDC_LIST_TOTAL, m_listTotal);
	DDX_Control(pDX, IDC_LIST_STORAGE_DETAIL, m_listStorageInDetail);
	DDX_Control(pDX, IDOK, m_btok);
	DDX_Control(pDX, IDC_BUTTON_EXCEL, m_btexcel);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BEGIN, m_timebegin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_END, m_timeend);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_Storage_Out_Detail, CDialog)
	//{{AFX_MSG_MAP(Dialog_Storage_Out_Detail)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL, OnButtonExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_Out_Detail message handlers
BOOL Dialog_Storage_Out_Detail::PreTranslateMessage(MSG* pMsg) 
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

BOOL Dialog_Storage_Out_Detail::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CTime time1 = CTime::GetCurrentTime();
	m_timebegin = time1;
	m_timeend = time1;

	m_listStorageInDetail.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listStorageInDetail.InsertColumn(0, _T("���"), LVCFMT_LEFT,60);
	m_listStorageInDetail.InsertColumn(1, _T("����"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(2, _T("���ݱ��"), LVCFMT_LEFT,150);
	m_listStorageInDetail.InsertColumn(3, _T("��������"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(4, _T("����ժҪ"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(5, _T("ȡ����"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(6, _T("������"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(7, _T("����"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(8, _T("�ֿ�"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(9, _T("��������"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(10, _T("����"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(11, _T("���"), LVCFMT_LEFT,100);

	m_listTotal.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listTotal.InsertColumn(0, _T("�ϼ�"), LVCFMT_LEFT,60);
	m_listTotal.InsertColumn(1, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(2, _T(""), LVCFMT_LEFT,150);
	m_listTotal.InsertColumn(3, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(4, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(5, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(6, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(7, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(8, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(9, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(10, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(11, _T(""), LVCFMT_LEFT,100);

	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_Storage_Out_Detail::OnOK() 
{
	m_listStorageInDetail.DeleteAllItems();
	UpdateData();
	CString csSql;
	CString starttime;
	starttime.Format("%04d-%02d-%02d",m_timebegin.GetYear(),m_timebegin.GetMonth(),m_timebegin.GetDay());
	CString endtime;
	endtime.Format("%04d-%02d-%02d",m_timeend.GetYear(),m_timeend.GetMonth(),m_timeend.GetDay()+1);

	csSql.Format("select time_make,storage_out_id,time_payment,digest,provider,operator,department,storage  from storage_out_baseinfo where time_make<=\"%s\" and time_make>=\"%s\" " ,endtime,starttime); 

	MYSQL myCont;
    MYSQL_RES *result,*result2;
    MYSQL_ROW sql_row,sql_row2;
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
				int totalnumber = 0;
				float totalmoney = 0;
                int j;
                j=mysql_num_fields(result);//�鿴������
				unsigned __int64 num = mysql_num_rows(result);//����
				int index = 0;
				CString strid;
                while(sql_row=mysql_fetch_row(result))//��ȡ���������
                {
					CString strindex ;
					strindex.Format("%d",index+1);
					m_listStorageInDetail.InsertItem(index,strindex);
					m_listStorageInDetail.SetItemText(index,1,sql_row[0]);
					m_listStorageInDetail.SetItemText(index,2,sql_row[1]);
					m_listStorageInDetail.SetItemText(index,3,sql_row[2]);
					m_listStorageInDetail.SetItemText(index,4,sql_row[3]);
					m_listStorageInDetail.SetItemText(index,5,sql_row[4]);
					m_listStorageInDetail.SetItemText(index,6,sql_row[5]);
					m_listStorageInDetail.SetItemText(index,7,sql_row[6]);
					m_listStorageInDetail.SetItemText(index,8,sql_row[7]);
					strid = sql_row[1];

					csSql.Format("select item_name,item_number,item_money  from storage_out_item where storage_out_id=\"%s\" " ,strid); 
					res=mysql_query(&myCont,csSql);//��ѯ
					if(!res)
					{
						result2=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
						if(result2)
						{
							int j;
							j=mysql_num_fields(result2);//�鿴������
							unsigned __int64 num = mysql_num_rows(result2);//����
							int indexitem = 0;
							int number = 0;
							float money = 0.0;
							CString strid;
							while(sql_row2=mysql_fetch_row(result2))//��ȡ���������
							{
								if(indexitem>0)
								{
									strindex.Format("%d",index+1);
									m_listStorageInDetail.InsertItem(index,strindex);
								}
								m_listStorageInDetail.SetItemText(index,9,sql_row2[0]);
								m_listStorageInDetail.SetItemText(index,10,sql_row2[1]);
								m_listStorageInDetail.SetItemText(index,11,sql_row2[2]);
								number += atoi(sql_row2[1]);
								money += atof(sql_row2[2]);
								indexitem++;
								index++;
							}
							totalnumber += number;
							totalmoney  += money;
							strindex.Format("%d",index+1);
							m_listStorageInDetail.InsertItem(index,strindex);
							m_listStorageInDetail.SetItemText(index,2,"С��");
							CString strtmp;
							strtmp.Format("%d",number);
							m_listStorageInDetail.SetItemText(index,10,strtmp);
							strtmp.Format("%0.2f",money);
							m_listStorageInDetail.SetItemText(index,11,strtmp);

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
					index++;
					strindex.Format("%d",index+1);
					m_listStorageInDetail.InsertItem(index,strindex);
					m_listStorageInDetail.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
					index++;
                }//while
				if(index!=0)
				{
					CString strtmp;
					strtmp.Format("%d",totalnumber);
					m_listTotal.DeleteColumn(2);					
					m_listTotal.InsertColumn(2,"����",LVCFMT_LEFT,150);
					m_listTotal.DeleteColumn(3);
					m_listTotal.InsertColumn(3,strtmp,LVCFMT_LEFT,100);
					m_listTotal.DeleteColumn(10);
					m_listTotal.InsertColumn(10,strtmp,LVCFMT_LEFT,100);
					
					strtmp.Format("%0.2f",totalmoney);
					m_listTotal.DeleteColumn(5);					
					m_listTotal.InsertColumn(5,"���",LVCFMT_LEFT,100);
					m_listTotal.DeleteColumn(6);
					m_listTotal.InsertColumn(6,strtmp,LVCFMT_LEFT,100);
					m_listTotal.DeleteColumn(11);
					m_listTotal.InsertColumn(11,strtmp,LVCFMT_LEFT,100);
					
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

void Dialog_Storage_Out_Detail::OnButtonExcel() 
{
	CreateExcel("������ϸ.xls",&m_listStorageInDetail);
}
