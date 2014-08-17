// Dialog_Storage_Left2.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_Storage_Left2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_Left2 dialog


Dialog_Storage_Left2::Dialog_Storage_Left2(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_Storage_Left2::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_Storage_Left2)
	m_scb = "";
	m_name = "";
	m_number = "";
	m_unit = "";
	m_price = "";
	//}}AFX_DATA_INIT
}


void Dialog_Storage_Left2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_Storage_Left2)
	DDX_Control(pDX, IDCANCEL, m_btcancel);
	DDX_Control(pDX, IDOK, m_btok);
	DDX_Control(pDX, IDC_LIST_STORAGE_LEFT, m_listLeft);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_Storage_Left2, CDialog)
	//{{AFX_MSG_MAP(Dialog_Storage_Left2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_STORAGE_LEFT, OnDblclkListStorageLeft)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_Left2 message handlers

BOOL Dialog_Storage_Left2::PreTranslateMessage(MSG* pMsg) 
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

BOOL Dialog_Storage_Left2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_listLeft.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listLeft.InsertColumn(0, _T("序号"), LVCFMT_LEFT,60);
	m_listLeft.InsertColumn(1, _T("SCB"), LVCFMT_LEFT,100);
	m_listLeft.InsertColumn(2, _T("名称"), LVCFMT_LEFT,200);
	m_listLeft.InsertColumn(3, _T("数量"), LVCFMT_LEFT,100);
	m_listLeft.InsertColumn(4, _T("单位"), LVCFMT_LEFT,100);
	m_listLeft.InsertColumn(5, _T("单价"), LVCFMT_LEFT,100);
	
	CString csSql;
	csSql.Format("select scb,item_name,item_number,item_unit,item_price from storage_left " ); 

	MYSQL myCont;
    MYSQL_RES *result;
    MYSQL_ROW sql_row;
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
				int number = 0;
				float money = 0.0;
                while(sql_row=mysql_fetch_row(result))//获取具体的数据
                {
					CString strindex ;
					strindex.Format("%d",index+1);
					m_listLeft.InsertItem(index,strindex);
					m_listLeft.SetItemText(index,1,sql_row[0]);
					m_listLeft.SetItemText(index,2,sql_row[1]);
					m_listLeft.SetItemText(index,3,sql_row[2]);
					m_listLeft.SetItemText(index,4,sql_row[3]);
					m_listLeft.SetItemText(index,5,sql_row[4]);
					if(index%2==0)
						m_listLeft.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
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
			return TRUE;
        }
    }
    else
    {
		const char *error = mysql_error(&myCont);
		CString str;
		str.Format("数据库错误(%s)",error);
		MessageBox(str,"提示",MB_OK);
		mysql_close(&myCont);//断开连接
		return TRUE;
    }
    if(result!=NULL) mysql_free_result(result);//释放结果资源
    mysql_close(&myCont);//断开连接

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH Dialog_Storage_Left2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd->GetDlgCtrlID() == IDC_STATIC1)   
	{   
		pDC->SetTextColor(RGB(255,0,0));   
	}  
	return hbr;
}

void Dialog_Storage_Left2::OnOK() 
{
	int cursel = m_listLeft.GetSelectionMark();
	if(cursel==-1)
		return;
	m_scb = m_listLeft.GetItemText(cursel,1);
	m_name = m_listLeft.GetItemText(cursel,2);
	m_number = m_listLeft.GetItemText(cursel,3);
	m_unit = m_listLeft.GetItemText(cursel,4);
	m_price = m_listLeft.GetItemText(cursel,5);
	
	CDialog::OnOK();
}

void Dialog_Storage_Left2::OnDblclkListStorageLeft(NMHDR* pNMHDR, LRESULT* pResult) 
{

	int cursel = m_listLeft.GetSelectionMark();
	if(cursel==-1)
		return;
	m_scb = m_listLeft.GetItemText(cursel,1);
	m_name = m_listLeft.GetItemText(cursel,2);
	m_number = m_listLeft.GetItemText(cursel,3);
	m_unit = m_listLeft.GetItemText(cursel,4);
	m_price = m_listLeft.GetItemText(cursel,5);
	
	*pResult = 0;
	CDialog::OnOK();
}
