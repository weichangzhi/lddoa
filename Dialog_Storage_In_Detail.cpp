// Dialog_Storage_In_Detail.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_Storage_In_Detail.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_In_Detail dialog


Dialog_Storage_In_Detail::Dialog_Storage_In_Detail(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_Storage_In_Detail::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_Storage_In_Detail)
	m_timebegin = 0;
	m_timeend = 0;
	//}}AFX_DATA_INIT
}


void Dialog_Storage_In_Detail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_Storage_In_Detail)
	DDX_Control(pDX, IDC_LIST_STORAGE_DETAIL, m_listStorageInDetail);
	DDX_Control(pDX, IDOK, m_btok);
	DDX_Control(pDX, IDC_BUTTON_EXCEL, m_btexcel);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BEGIN, m_timebegin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_END, m_timeend);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_Storage_In_Detail, CDialog)
	//{{AFX_MSG_MAP(Dialog_Storage_In_Detail)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL, OnButtonExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_In_Detail message handlers

BOOL Dialog_Storage_In_Detail::PreTranslateMessage(MSG* pMsg) 
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

BOOL Dialog_Storage_In_Detail::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CTime time1 = CTime::GetCurrentTime();
	m_timebegin = time1;
	m_timeend = time1;

	m_listStorageInDetail.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listStorageInDetail.InsertColumn(0, _T("序号"), LVCFMT_LEFT,60);
	m_listStorageInDetail.InsertColumn(1, _T("日期"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(2, _T("单据编号"), LVCFMT_LEFT,150);
	m_listStorageInDetail.InsertColumn(3, _T("交货日期"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(4, _T("单据摘要"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(5, _T("供应商"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(6, _T("经办人"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(7, _T("部门"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(8, _T("仓库"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(9, _T("明细摘要"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(10, _T("货物名称"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(11, _T("数量"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(12, _T("金额"), LVCFMT_LEFT,100);

	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_Storage_In_Detail::OnOK() 
{
	m_listStorageInDetail.DeleteAllItems();
	UpdateData();
	CString csSql;
	CString starttime;
	starttime.Format("%04d-%02d-%02d",m_timebegin.GetYear(),m_timebegin.GetMonth(),m_timebegin.GetDay());
	CString endtime;
	endtime.Format("%04d-%02d-%02d",m_timeend.GetYear(),m_timeend.GetMonth(),m_timeend.GetDay()+1);

	csSql.Format("select time_make,storage_in_id,time_payment,digest,provider,operator,department,storage  from storage_in_baseinfo where time_make<=\"%s\" and time_make>=\"%s\" " ,endtime,starttime); 

	MYSQL myCont;
    MYSQL_RES *result,*result2;
    MYSQL_ROW sql_row,sql_row2;
    int res;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
    {
        mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
        res=mysql_query(&myCont,csSql);//查询
        if(!res)
        {
            result=mysql_store_result(&myCont);//保存查询到的数据到result
		    if(result)
            {
                int j;
                j=mysql_num_fields(result);//查看多少列
				unsigned __int64 num = mysql_num_rows(result);//行数
				int index = 0;
				CString strid;
                while(sql_row=mysql_fetch_row(result))//获取具体的数据
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

					csSql.Format("select item_digest,item_name,item_number,item_money  from storage_in_item where storage_in_id=\"%s\" " ,strid); 
					res=mysql_query(&myCont,csSql);//查询
					if(!res)
					{
						result2=mysql_store_result(&myCont);//保存查询到的数据到result
						if(result2)
						{
							int j;
							j=mysql_num_fields(result2);//查看多少列
							unsigned __int64 num = mysql_num_rows(result2);//行数
							int indexitem = 0;
							int number = 0;
							float money = 0.0;
							CString strid;
							while(sql_row2=mysql_fetch_row(result2))//获取具体的数据
							{
								if(indexitem>0)
								{
									strindex.Format("%d",index+1);
									m_listStorageInDetail.InsertItem(index,strindex);
								}
								m_listStorageInDetail.SetItemText(index,9,sql_row2[0]);
								m_listStorageInDetail.SetItemText(index,10,sql_row2[1]);
								m_listStorageInDetail.SetItemText(index,11,sql_row2[2]);
								m_listStorageInDetail.SetItemText(index,12,sql_row2[3]);
								number += atoi(sql_row2[2]);
								money += atof(sql_row2[3]);
								indexitem++;
								index++;
							}
							strindex.Format("%d",index+1);
							m_listStorageInDetail.InsertItem(index,strindex);
							m_listStorageInDetail.SetItemText(index,2,"小计");
							CString strtmp;
							strtmp.Format("%d",number);
							m_listStorageInDetail.SetItemText(index,11,strtmp);
							strtmp.Format("%0.2f",money);
							m_listStorageInDetail.SetItemText(index,12,strtmp);

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
					index++;
					strindex.Format("%d",index+1);
					m_listStorageInDetail.InsertItem(index,strindex);
					m_listStorageInDetail.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
					index++;
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
    if(result!=NULL) mysql_free_result(result);//释放结果资源
    mysql_close(&myCont);//断开连接

	return;
}

void Dialog_Storage_In_Detail::OnButtonExcel() 
{
	CreateExcel("进货明细.xls",&m_listStorageInDetail);
}
