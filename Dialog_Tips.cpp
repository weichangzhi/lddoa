// Dialog_Tips.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_Tips.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_Tips dialog


Dialog_Tips::Dialog_Tips(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_Tips::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_Tips)
	m_strtips = _T("");
	m_boolTips = FALSE;
	//}}AFX_DATA_INIT
}


void Dialog_Tips::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_Tips)
	DDX_Control(pDX, IDC_LIST_TIPS, m_litTips);
	DDX_Text(pDX, IDC_STATIC_TIPS, m_strtips);
	DDX_Check(pDX, IDC_CHECK_TIPS, m_boolTips);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_Tips, CDialog)
	//{{AFX_MSG_MAP(Dialog_Tips)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_Tips message handlers

BOOL Dialog_Tips::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_litTips.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_litTips.InsertColumn(0, _T("序号"), LVCFMT_LEFT,50);
	m_litTips.InsertColumn(1, _T("订单号"), LVCFMT_LEFT,100);
	m_litTips.InsertColumn(2, _T("订单名称"), LVCFMT_LEFT,100);
	m_litTips.InsertColumn(3, _T("制作材料"), LVCFMT_LEFT,150);
	m_litTips.InsertColumn(4, _T("交付日期"), LVCFMT_LEFT,100);
	CString strDepartment = g_department;
	if ((strDepartment.Compare("技术部意造")==0) || (strDepartment.Compare("技术部记梦馆")==0))
	{
		m_strtips = "下面是停留在技术部的订单：";
	}
	else
		m_strtips = "下面是停留在生产部的订单：";
	GetDlgItem(IDC_STATIC_TIPS)->SetWindowText(m_strtips);
	if (m_blogintips)
	{
		SetWindowText("登录提醒");
	}
	else
	{
		SetWindowText("定时提醒");
	}
	UpdateData(FALSE);
	
	querysql();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_Tips::querysql() 
{
	m_litTips.DeleteAllItems();
	UpdateData();
	CString csSql;
	
	CString strDepartment = g_department;
	if ((strDepartment.Compare("技术部意造")==0) || (strDepartment.Compare("技术部记梦馆")==0))
	{
		csSql.Format("select baseinfo.listid,baseinfo.listname,baseinfo.material,baseinfo.reveivedate,baseinfo.urgent,schedule.tcnumber from baseinfo,schedule  where schedule.tcnumber>0 and baseinfo.listid=schedule.listid");
	}
	else if(strDepartment.Compare("生产部")==0)
	{
		csSql.Format("select baseinfo.listid,baseinfo.listname,baseinfo.material,baseinfo.reveivedate,baseinfo.urgent,schedule.pdnumber from baseinfo,schedule  where schedule.pdnumber>0 and baseinfo.listid=schedule.listid");
	}

	MYSQL myCont;
    MYSQL_RES *result;
    MYSQL_ROW sql_row;
    int res;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
    {
        mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文

		CString curtime;
		CString strsql ;
		strsql.Format("select now()");
		if(mysql_query(&myCont,strsql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			return;
		}
		result=mysql_store_result(&myCont);//保存查询到的数据到result
		if(result)
		{
			sql_row=mysql_fetch_row(result);
			CString tmp = sql_row[0];
			curtime = tmp.Mid(0,10);
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
                while(sql_row=mysql_fetch_row(result))//获取具体的数据
                {
					CString strindex ;
					strindex.Format("%d",index+1);
					m_litTips.InsertItem(index,strindex);
					int i=0;
					for(i=1;i<=4;i++)
					{
						m_litTips.SetItemText(index,i,sql_row[i-1]);
					}
					
					int tcnumber = atoi(sql_row[5]);
					int pdnumber = atoi(sql_row[5]);
					if(index%2==0)
						m_litTips.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
					if (sql_row[4]!=NULL)
					{
						int spanday = CalcDaySpan(curtime,sql_row[3]);
						if (atoi(sql_row[4])==1)//加急 紫色
						{
							m_litTips.SetItemColor(index,RGB(230,230,230),RGB(128,0,128));
						}
						else if (spanday<0)//sql_row[8]交货日期 超时 红色
						{
							m_litTips.SetItemColor(index,RGB(0,0,0),RGB(255,0,128));
						}
						else if(spanday<2 && spanday>=0 &&  (strDepartment.Compare("生产部")==0))
						{
							m_litTips.SetItemColor(index,RGB(0,0,0),RGB(255,255,128));
						}
						else if(spanday<3 &&  spanday>=0 && ((strDepartment.Compare("技术部意造")==0) || (strDepartment.Compare("技术部记梦馆")==0)))
						{
							m_litTips.SetItemColor(index,RGB(0,0,0),RGB(255,255,128));
						}
					}
					index++;
                }//while
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


void Dialog_Tips::OnClose() 
{
	UpdateData();
	CString strpathini="";
	::GetCurrentDirectory(_MAX_PATH,strpathini.GetBuffer(_MAX_PATH));
	strpathini.ReleaseBuffer();
	strpathini = strpathini + "\\" + CONFIGINI;
	CString strtips ;
	if (m_blogintips)
	{
		strtips.Format("%d",!m_boolTips);
		::WritePrivateProfileString("Tips","LoginTips",strtips,strpathini);
	}
	else
	{
		strtips.Format("%d",!m_boolTips);
		::WritePrivateProfileString("Tips","TimerTips",strtips,strpathini);
	}
	CDialog::OnClose();
}

BOOL Dialog_Tips::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN) 
	{  
		switch(pMsg->wParam) 
		{  
		case VK_RETURN: //回车  
			return TRUE;  
		case VK_ESCAPE: //ESC  
			return TRUE;  
		}  
	}	
	return CDialog::PreTranslateMessage(pMsg);
}
