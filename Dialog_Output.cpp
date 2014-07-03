// Dialog_Output.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_Output.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Output dialog


CDialog_Output::CDialog_Output(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Output::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Output)
	m_time_start = 0;
	m_time_end = 0;
	//}}AFX_DATA_INIT
}


void CDialog_Output::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Output)
	DDX_Control(pDX, IDC_LIST_OUTPUT, m_list_output);
	DDX_Control(pDX, IDC_COMBO_OUTPUT, m_com_output);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_time_start);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_time_end);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Output, CDialog)
	//{{AFX_MSG_MAP(CDialog_Output)
	ON_BN_CLICKED(IDC_EXCEL, OnExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Output message handlers

BOOL CDialog_Output::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_com_output.InsertString(0,"ҵ��");
	//m_com_output.InsertString(1,"������");
	m_com_output.InsertString(1,"������");
	m_com_output.SetCurSel(0);

	m_list_output.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list_output.InsertColumn(0, _T("���"), LVCFMT_LEFT,60);
	m_list_output.InsertColumn(1, _T("������"), LVCFMT_LEFT,90);
	m_list_output.InsertColumn(2, _T("��������"), LVCFMT_LEFT,80);
	m_list_output.InsertColumn(3, _T("��Ʒ����"), LVCFMT_LEFT,80);
	m_list_output.InsertColumn(4, _T("��������"), LVCFMT_LEFT,90);
	m_list_output.InsertColumn(5, _T("�������(Ԫ)"), LVCFMT_LEFT,110);
	m_list_output.InsertColumn(6, _T("�������(cm3)"), LVCFMT_LEFT,120);
	m_list_output.InsertColumn(7, _T("��ݵ���"), LVCFMT_LEFT,90);
	m_list_output.InsertColumn(8, _T("ҵ��"), LVCFMT_LEFT,80);
	m_list_output.InsertColumn(9, _T("������"), LVCFMT_LEFT,80);
	m_list_output.InsertColumn(10, _T("������"), LVCFMT_LEFT,80);
	m_list_output.InsertColumn(11, _T("�ʼ�"), LVCFMT_LEFT,80);
	m_list_output.InsertColumn(12, _T("��Ʒ��"), LVCFMT_LEFT,80);
	m_list_output.InsertColumn(13, _T("����"), LVCFMT_LEFT,80);
	CTime time1 = CTime::GetCurrentTime();
	m_time_start = time1;
	m_time_end = time1;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_Output::OnOK() 
{
	m_list_output.DeleteAllItems();
	UpdateData();
	CString csSql;
	CString starttime;
	starttime.Format("%04d-%02d-%02d",m_time_start.GetYear(),m_time_start.GetMonth(),m_time_start.GetDay());
	CString endtime;
	endtime.Format("%04d-%02d-%02d",m_time_end.GetYear(),m_time_end.GetMonth(),m_time_end.GetDay()+1);
			
	int indexSel = m_com_output.GetCurSel();
	switch(indexSel)
	{
	case 0://ҵ��
		//csSql.Format("select listid,listname,material,volume,listnumber,businesspeople,money  from baseinfo,scheduledetail where  businessendtime>=\"%s\"and businessendtime<=\"%s\" and  baseinfo.listid=scheduledetail.listid" ,starttime,endtime);
		csSql.Format("select baseinfo.listid,baseinfo.listname,baseinfo.truelistnumber,baseinfo.material,baseinfo.money,baseinfo.volume,baseinfo.sendid, businesspeople,tcpeople,pdpeople,qcpeople,storagepopple,sendpeople     from baseinfo,scheduledetail where  baseinfo.listid=scheduledetail.listid and businessendtime>=\"%s\"and businessendtime<=\"%s\" " ,starttime,endtime);
		break;
	case 1://������
		csSql.Format("select baseinfo.listid,baseinfo.listname,baseinfo.truelistnumber,baseinfo.material,baseinfo.money,baseinfo.volume,baseinfo.sendid, businesspeople,tcpeople,pdpeople,qcpeople,storagepopple,sendpeople from baseinfo,scheduledetail where baseinfo.listid=scheduledetail.listid and pdendtime>=\"%s\"and pdendtime<=\"%s\" " ,starttime,endtime);
		break;
	default:
		break;
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
				float money=0, volume=0;
				int number = 0;
                while(sql_row=mysql_fetch_row(result))//��ȡ���������
                {
					number += atoi(sql_row[2]);
					money += atof(sql_row[4]);
					volume += atof(sql_row[5]);
					CString strindex ;
					strindex.Format("%d",index+1);
					m_list_output.InsertItem(index,strindex);
					int i=0;
					for(i=1;i<=13;i++)
					{
						if(i==5)
						{
							if(g_permission & QUERY_LIST)
								m_list_output.SetItemText(index,i,sql_row[i-1]);
							else
								m_list_output.SetItemText(index,i,"****");
							continue;
						}
						m_list_output.SetItemText(index,i,sql_row[i-1]);
					}
					if(index%2==0)
						m_list_output.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
					index++;
                }//while
				if(index!=0)
				{
					m_list_output.InsertItem(index++," ");
					m_list_output.InsertItem(index++," ");
					m_list_output.InsertItem(index++," ");
					m_list_output.InsertItem(index,"�ܼƣ�");
					CString strtmp;
					strtmp.Format("%d",number);
					m_list_output.SetItemText(index,3,strtmp);
					strtmp.Format("%0.1f",money);
					if(g_permission & QUERY_LIST)
						m_list_output.SetItemText(index,5,strtmp);
					else
						m_list_output.SetItemText(index,5,"****");
					strtmp.Format("%0.1f",volume);
					m_list_output.SetItemText(index,6,strtmp);
					m_list_output.SetItemColor(index,RGB(255,0,0),RGB(255,255,255));
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
	//CDialog::OnOK();
}

BOOL CDialog_Output::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
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

void CDialog_Output::OnExcel() 
{
	CreateExcel("����ͳ��.xls",&m_list_output);
}
