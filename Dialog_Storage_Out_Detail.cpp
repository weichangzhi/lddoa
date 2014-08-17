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
	m_strWay = _T("");
	m_strSubWay = _T("");
	//}}AFX_DATA_INIT
}


void Dialog_Storage_Out_Detail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_Storage_Out_Detail)
	DDX_Control(pDX, IDC_COMBO_SUBWAY, m_comSubWay);
	DDX_Control(pDX, IDC_COMBO_WAY, m_comWay);
	DDX_Control(pDX, IDC_LIST_TOTAL, m_listTotal);
	DDX_Control(pDX, IDC_LIST_STORAGE_DETAIL, m_listStorageInDetail);
	DDX_Control(pDX, IDOK, m_btok);
	DDX_Control(pDX, IDC_BUTTON_EXCEL, m_btexcel);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BEGIN, m_timebegin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_END, m_timeend);
	DDX_CBString(pDX, IDC_COMBO_WAY, m_strWay);
	DDX_CBString(pDX, IDC_COMBO_SUBWAY, m_strSubWay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_Storage_Out_Detail, CDialog)
	//{{AFX_MSG_MAP(Dialog_Storage_Out_Detail)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL, OnButtonExcel)
	ON_CBN_SELCHANGE(IDC_COMBO_WAY, OnSelchangeComboWay)
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
		//case VK_RETURN: //回车  
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

	m_comWay.InsertString(0,"部门");
	m_comWay.InsertString(1,"仓库");
	m_comWay.InsertString(2,"取货人");
	m_comWay.InsertString(3,"经办人");
	m_comWay.InsertString(4,"全部");
	m_comWay.SetCurSel(0);
	m_strWay = "部门";

	CString strpathini="";
	::GetCurrentDirectory(_MAX_PATH,strpathini.GetBuffer(_MAX_PATH));
	strpathini.ReleaseBuffer();
	strpathini = strpathini + "\\" + CONFIGINI_STORAGE;
	int nCount = 0, i = 0;
	CString strTemp,strtemp1;	
	m_strSubWay = g_department;
	m_comSubWay.ResetContent();
	nCount = ::GetPrivateProfileInt("Department","Count",1,strpathini);
	for(i=0;i<nCount;i++)
	{
		strTemp.Format("%d",i+1);
		strTemp="Department"+strTemp;
		::GetPrivateProfileString("Department",strTemp,"", strtemp1.GetBuffer(MAX_PATH),MAX_PATH,strpathini);
		m_comSubWay.InsertString(i,strtemp1);
	}

	m_listStorageInDetail.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listStorageInDetail.InsertColumn(0, _T("序号"), LVCFMT_LEFT,60);
	m_listStorageInDetail.InsertColumn(1, _T("日期"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(2, _T("单据编号"), LVCFMT_LEFT,160);
	m_listStorageInDetail.InsertColumn(3, _T("取货日期"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(4, _T("单据摘要"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(5, _T("取货人"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(6, _T("经办人"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(7, _T("部门"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(8, _T("仓库"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(9, _T("货物名称"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(10, _T("数量"), LVCFMT_LEFT,100);
	m_listStorageInDetail.InsertColumn(11, _T("金额"), LVCFMT_LEFT,100);

	m_listTotal.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listTotal.InsertColumn(0, _T("合计"), LVCFMT_LEFT,60);
	m_listTotal.InsertColumn(1, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(2, _T(""), LVCFMT_LEFT,160);
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

	int cursel = m_comWay.GetCurSel();
	switch (cursel)
	{
	case 0://部门
		csSql.Format("select time_make,storage_out_id,time_payment,digest,provider,operator,department,storage  from storage_out_baseinfo where department=\"%s\" and time_make<=\"%s\" and time_make>=\"%s\" " ,m_strSubWay,endtime,starttime);
		break;
	case 1://仓库
		csSql.Format("select time_make,storage_out_id,time_payment,digest,provider,operator,department,storage  from storage_out_baseinfo where storage=\"%s\" and time_make<=\"%s\" and time_make>=\"%s\" " ,m_strSubWay,endtime,starttime);
		break;
	case 2://取货人
		csSql.Format("select time_make,storage_out_id,time_payment,digest,provider,operator,department,storage  from storage_out_baseinfo where provider=\"%s\" and time_make<=\"%s\" and time_make>=\"%s\" " ,m_strSubWay,endtime,starttime);
		break;
	case 3://经办人
		csSql.Format("select time_make,storage_out_id,time_payment,digest,provider,operator,department,storage  from storage_out_baseinfo where operator=\"%s\" and time_make<=\"%s\" and time_make>=\"%s\" " ,m_strSubWay,endtime,starttime);
		break;
	case 4://全部
		csSql.Format("select time_make,storage_out_id,time_payment,digest,provider,operator,department,storage  from storage_out_baseinfo where time_make<=\"%s\" and time_make>=\"%s\" " ,endtime,starttime); 
		break;
	default:
		csSql.Format("select time_make,storage_out_id,time_payment,digest,provider,operator,department,storage  from storage_out_baseinfo where time_make<=\"%s\" and time_make>=\"%s\" " ,endtime,starttime); 
		break;
	}

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
				int totalnumber = 0;
				float totalmoney = 0;
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

					csSql.Format("select item_name,item_number,item_money  from storage_out_item where storage_out_id=\"%s\" " ,strid); 
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
								number += atoi(sql_row2[1]);
								money += atof(sql_row2[2]);
								indexitem++;
								index++;
							}
							if(num>0)
							{
								totalnumber += number;
								totalmoney  += money;
								strindex.Format("%d",index+1);
								m_listStorageInDetail.InsertItem(index,strindex);
								m_listStorageInDetail.SetItemText(index,2,"小计");
								CString strtmp;
								strtmp.Format("%d",number);
								m_listStorageInDetail.SetItemText(index,10,strtmp);
								strtmp.Format("%0.2f",money);
								m_listStorageInDetail.SetItemText(index,11,strtmp);
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
					m_listTotal.InsertColumn(2,"数量",LVCFMT_LEFT,150);
					m_listTotal.DeleteColumn(3);
					m_listTotal.InsertColumn(3,strtmp,LVCFMT_LEFT,100);
					m_listTotal.DeleteColumn(10);
					m_listTotal.InsertColumn(10,strtmp,LVCFMT_LEFT,100);
					
					strtmp.Format("%0.2f",totalmoney);
					m_listTotal.DeleteColumn(5);					
					m_listTotal.InsertColumn(5,"金额",LVCFMT_LEFT,100);
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

void Dialog_Storage_Out_Detail::OnButtonExcel() 
{
	CreateExcel("出库明细.xls",&m_listStorageInDetail);
}

void Dialog_Storage_Out_Detail::OnSelchangeComboWay() 
{
	CString strpathini="";
	::GetCurrentDirectory(_MAX_PATH,strpathini.GetBuffer(_MAX_PATH));
	strpathini.ReleaseBuffer();
	strpathini = strpathini + "\\" + CONFIGINI_STORAGE;
	int nCount = 0, i = 0;
	CString strTemp,strtemp1;

	int cursel = m_comWay.GetCurSel();
	switch (cursel)
	{
	case 0://部门
		m_strSubWay = g_department;
		m_comSubWay.ResetContent();
		nCount = ::GetPrivateProfileInt("Department","Count",1,strpathini);
		for(i=0;i<nCount;i++)
		{
			strTemp.Format("%d",i+1);
			strTemp="Department"+strTemp;
			::GetPrivateProfileString("Department",strTemp,"", strtemp1.GetBuffer(MAX_PATH),MAX_PATH,strpathini);
			m_comSubWay.InsertString(i,strtemp1);
		}
		m_strWay = "部门";
		break;
	case 1://仓库
		m_comSubWay.ResetContent();
		nCount = ::GetPrivateProfileInt("Storage","Count",1,strpathini);
		for(i=0;i<nCount;i++)
		{
			strTemp.Format("%d",i+1);
			strTemp="Storage"+strTemp;
			::GetPrivateProfileString("Storage",strTemp,"", strtemp1.GetBuffer(MAX_PATH),MAX_PATH,strpathini);
			m_comSubWay.InsertString(i,strtemp1);
		}
		m_strWay = "仓库";
		m_strSubWay = strtemp1;
		break;
	case 2://取货人
		m_comSubWay.ResetContent();
		nCount = ::GetPrivateProfileInt("receiver","Count",1,strpathini);
		for(i=0;i<nCount;i++)
		{
			strTemp.Format("%d",i+1);
			strTemp="receiver"+strTemp;
			::GetPrivateProfileString("receiver",strTemp,"", strtemp1.GetBuffer(MAX_PATH),MAX_PATH,strpathini);
			m_comSubWay.InsertString(i,strtemp1);
		}
		m_strWay = "取货人";
		m_strSubWay = strtemp1;
		break;
	case 3://经办人
		m_comSubWay.ResetContent();
		nCount = ::GetPrivateProfileInt("Operator","Count",1,strpathini);
		for(i=0;i<nCount;i++)
		{
			strTemp.Format("%d",i+1);
			strTemp="Operator"+strTemp;
			::GetPrivateProfileString("Operator",strTemp,"", strtemp1.GetBuffer(MAX_PATH),MAX_PATH,strpathini);
			m_comSubWay.InsertString(i,strtemp1);
		}
		m_strWay = "经办人";
		m_strSubWay = strtemp1;
		break;
	case 4://全部
		m_comSubWay.ResetContent();
		m_comSubWay.InsertString(0,"全部");
		m_comSubWay.SetCurSel(0);
		m_strSubWay = "全部";
		m_strWay = "全部";
		break;
	default:
		m_comSubWay.ResetContent();
		m_comSubWay.InsertString(0,"全部");
		m_comSubWay.SetCurSel(0);
		m_strSubWay = "全部";
		m_strWay = "全部";
		break;
	}
	UpdateData(FALSE);
}
