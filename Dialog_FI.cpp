// Dialog_FI.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_FI.h"
#include "Dialog_progress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_FI dialog


Dialog_FI::Dialog_FI(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_FI::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_FI)
	m_strlistid_add = _T("");
	m_strlistid_query = _T("");
	m_billing = FALSE;
	m_gathering = FALSE;
	m_time_start = 0;
	m_time_end = 0;
	//}}AFX_DATA_INIT
}


void Dialog_FI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_FI)
	DDX_Control(pDX, IDOK, m_btnok);
	DDX_Control(pDX, IDC_EXCEL, m_btnexcel);
	DDX_Control(pDX, IDC_BUTTON_FIADD, m_btnadd);
	DDX_Control(pDX, IDC_EDIT_LIST, m_edit);
	DDX_Control(pDX, IDC_LIST_FI, m_listFI);
	DDX_Text(pDX, IDC_EDIT_LISTID_ADD, m_strlistid_add);
	DDX_Text(pDX, IDC_EDIT_LISTID_QUERY, m_strlistid_query);
	DDX_Check(pDX, IDC_CHECK_BILLING, m_billing);
	DDX_Check(pDX, IDC_CHECK_GATHERING, m_gathering);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_time_start);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_time_end);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_FI, CDialog)
	//{{AFX_MSG_MAP(Dialog_FI)
	ON_BN_CLICKED(IDC_BUTTON_FIADD, OnFiadd)
	ON_BN_CLICKED(IDC_EXCEL, OnExcel)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_FI, OnColumnclickListFi)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_FI, OnEndlabeleditListFi)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FI, OnDblclkListFi)
	ON_EN_KILLFOCUS(IDC_EDIT_LIST, OnKillfocusEditList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_FI message handlers

BOOL Dialog_FI::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if((g_permission & FI)==0)
	{
		GetDlgItem(IDC_BUTTON_FIADD)->EnableWindow(FALSE);
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		GetDlgItem(IDC_EXCEL)->EnableWindow(FALSE);
	}
	LONG lStyle;
	lStyle = GetWindowLong(m_listFI.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_listFI.m_hWnd, GWL_STYLE, lStyle);//设置style
	DWORD dwStyle = m_listFI.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_listFI.SetExtendedStyle(dwStyle); //设置扩展风格
	m_edit.ShowWindow(SW_HIDE);


	//m_listFI.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EDITLABELS);
	m_listFI.InsertColumn(0, _T("序号"), LVCFMT_LEFT,60);
	m_listFI.InsertColumn(1, _T("订单号"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(2, _T("是否收款"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(3, _T("是否开发票"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(4, _T("操作时间"), LVCFMT_LEFT,200);
	CTime time1 = CTime::GetCurrentTime();
	m_time_start = time1;
	m_time_end = time1;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_FI::OnFiadd() 
{
	UpdateData();
	if(m_strlistid_add.IsEmpty())
	{
		MessageBox("请输入订单号：","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_LISTID_ADD)->SetFocus();
		return;
	}
	CString strgathering;
	CString strbilling;
	strgathering.Format("%d",m_gathering);
	strbilling.Format("%d",m_billing);
	CString curtime;

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
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
		CString strsql ;
		strsql.Format("select now()");
		if(mysql_query(&myCont,strsql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
			return;
		}
		dlgpro->setpos(600);
		result=mysql_store_result(&myCont);//保存查询到的数据到result
		if(result)
		{
			sql_row=mysql_fetch_row(result);
			curtime = sql_row[0];
		}
		else
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
			return;
		}

		dlgpro->setpos(700);
		sql = "select * from fi where listid='" + m_strlistid_add +"'";
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
			return;
		}
		dlgpro->setpos(800);
		result=mysql_store_result(&myCont);//保存查询到的数据到result
		if(result)
		{
			unsigned __int64 num = mysql_num_rows(result);//行数
			if(num>=1)
			{
				//修改记录				
				dlgpro->setpos(900);
				sql.Format("update fi set gathering=\"%s\",billing=\"%s\",optime=\"%s\" where listid=\"%s\" ",strgathering,strbilling,curtime,m_strlistid_add);
				int ret = mysql_query(&myCont,sql);
				const char *error = mysql_error(&myCont);
				if(ret!= 0)
				{
					const char *error = mysql_error(&myCont);
					CString str;
					str.Format("数据库错误(%s)",error);
					MessageBox(str,"提示",MB_OK);
					mysql_close(&myCont);//断开连接
					dlgpro->endpos();
					return;
				}
				if(result!=NULL) mysql_free_result(result);//释放结果资源
				mysql_close(&myCont);//断开连接
				dlgpro->endpos();
				MessageBox("修改记录成功","提示",MB_OK);
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
			dlgpro->endpos();
			return;
		}
		dlgpro->setpos(900);
		sql.Format("select * from schedule where listid=\"%s\" ",m_strlistid_add);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
			return;
		}
		result=mysql_store_result(&myCont);//保存查询到的数据到result
		if(result)
		{
			dlgpro->setpos(950);
			unsigned __int64 num = mysql_num_rows(result);//行数
			if(num!=1)//
			{
				MessageBox("无此订单或未下单","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_LISTID_ADD)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_LISTID_ADD))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//释放结果资源
				mysql_close(&myCont);//断开连接
				dlgpro->endpos();
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
			dlgpro->endpos();
			return;
		}
		dlgpro->setpos(980);

		sql.Format("insert into fi values (\"%s\",\"%s\",\"%s\",\"%s\")", m_strlistid_add,strgathering,strbilling,curtime);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
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
		dlgpro->endpos();
		return;
	}
	if(result!=NULL) mysql_free_result(result);//释放结果资源
	mysql_close(&myCont);//断开连接
	dlgpro->endpos();
	MessageBox("增加记录成功","提示",MB_OK);
}

void Dialog_FI::OnExcel() 
{
	CreateExcel("财务统计.xls",&m_listFI);	
}

void Dialog_FI::OnOK() 
{
	m_listFI.DeleteAllItems();
	UpdateData();
	CString starttime;
	starttime.Format("%04d-%02d-%02d",m_time_start.GetYear(),m_time_start.GetMonth(),m_time_start.GetDay());
	CString endtime;
	endtime.Format("%04d-%02d-%02d",m_time_end.GetYear(),m_time_end.GetMonth(),m_time_end.GetDay()+1);
	CString csSql;
	if(m_strlistid_query.IsEmpty())
		csSql.Format("select * from fi where optime>=\"%s\" and optime<=\"%s\" ",starttime,endtime);
	else
		csSql.Format("select * from fi where listid=\"%s\"  ",m_strlistid_query);

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
        mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
        res=mysql_query(&myCont,csSql);//查询
        if(!res)
        {
			dlgpro->setpos(600);
            result=mysql_store_result(&myCont);//保存查询到的数据到result
		    if(result)
            {
                int j;
                j=mysql_num_fields(result);//查看多少列
				unsigned __int64 num = mysql_num_rows(result);//行数
				int index = 0;
				float money=0, volume=0;
				int number = 0;
				dlgpro->setpos(700);
                while(sql_row=mysql_fetch_row(result))//获取具体的数据
                {
					CString strindex ;
					strindex.Format("%d",index+1);
					m_listFI.InsertItem(index,strindex);
					int i=0;
					for(i=1;i<=4;i++)
					{
						m_listFI.SetItemText(index,i,sql_row[i-1]);
					}
					if(index%2==0)
						m_listFI.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
					index++;
                }//while	
				dlgpro->setpos(900);
            }
        }
        else
        {
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("数据库错误(%s)",error);
			MessageBox(str,"提示",MB_OK);
			mysql_close(&myCont);//断开连接
			dlgpro->endpos();
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
		dlgpro->endpos();
		return;
    }
    if(result!=NULL) mysql_free_result(result);//释放结果资源
    mysql_close(&myCont);//断开连接
	dlgpro->endpos();
	
	return;
	//CDialog::OnOK();
}

BOOL Dialog_FI::PreTranslateMessage(MSG* pMsg) 
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

void Dialog_FI::OnColumnclickListFi(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	listsort(&m_listFI,pNMListView);
	*pResult = 0;
}

void Dialog_FI::OnEndlabeleditListFi(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = TRUE;
}

void Dialog_FI::OnDblclkListFi(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;
	CRect rc;
	if(pNMListView->iItem!=-1)
	{
	   int m_row=pNMListView->iItem;//m_row为被选中行的行序号（int类型成员变量）
	   int m_column=pNMListView->iSubItem;//m_column为被选中行的列序号（int类型成员变量）
	   m_listFI.GetSubItemRect(pNMListView->iItem, pNMListView->iSubItem,LVIR_LABEL,rc);//取得子项的矩形
	   rc.left+=3;
	   rc.top+=167;
	   rc.right+=3;
	   rc.bottom+=170;
	   char * ch=new char [128];
	   m_listFI.GetItemText(pNMListView->iItem, pNMListView->iSubItem,ch,128);//取得子项的内容
	   m_edit.SetWindowText(ch);//将子项的内容显示到编辑框中
	   m_edit.ShowWindow(SW_SHOW);//显示编辑框
	   m_edit.MoveWindow(&rc);//将编辑框移动到子项上面，覆盖在子项上
	   m_edit.SetFocus();//使编辑框取得焦点
	   m_edit.CreateSolidCaret(1,rc.Height()-5);//创建一个光标
	   m_edit.ShowCaret();//显示光标
	   m_edit.SetSel(0,-1);//使光标移到最后面
	}
	*pResult = 0;
}

void Dialog_FI::OnKillfocusEditList() 
{
	CString str;
	m_edit.GetWindowText(str);//取得编辑框的内容
	m_edit.ShowWindow(SW_HIDE);//隐藏编辑框	
}
