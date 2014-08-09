// Dialog_Storage_Out.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_Storage_Out.h"
#include "Dialog_progress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_Out dialog


Dialog_Storage_Out::Dialog_Storage_Out(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_Storage_Out::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_Storage_Out)
	m_timeCurrent = 0;
	m_timePayment = 0;
	m_StorageInID = _T("");
	m_Department = _T("");
	m_Digest = _T("");
	m_Operator = _T("");
	m_Provider = _T("");
	m_Storage = _T("");
	m_row = 0;
	m_column = 0;
	//}}AFX_DATA_INIT
}


void Dialog_Storage_Out::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_Storage_Out)
	DDX_Control(pDX, IDC_EXCEL, m_btexcel);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_btsave);
	DDX_Control(pDX, IDC_BUTTON_QUIT, m_btquit);
	DDX_Control(pDX, IDC_BUTTON_QUERY, m_btquery);
	DDX_Control(pDX, IDC_BUTTON_PRINT, m_btprint);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_btnew);
	DDX_Control(pDX, IDC_BUTTON_MODIFY, m_btmodify);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_CURRENT, m_timeCurrent);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_PAYMENT, m_timePayment);
	DDX_Control(pDX, IDC_LIST_TOTAL, m_listTotal);
	DDX_Control(pDX, IDC_LIST_STORAGE_IN, m_listStorageIn);
	DDX_Text(pDX, IDC_EDIT_STORAGE_IN_ID, m_StorageInID);
	DDX_Text(pDX, IDC_RICHEDIT_DEPARTMENT, m_Department);
	DDX_Text(pDX, IDC_RICHEDIT_DIGEST, m_Digest);
	DDX_Text(pDX, IDC_RICHEDIT_OPERATOR, m_Operator);
	DDX_Text(pDX, IDC_RICHEDIT_PROVIDER, m_Provider);
	DDX_Text(pDX, IDC_RICHEDIT_STORAGE, m_Storage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_Storage_Out, CDialog)
	//{{AFX_MSG_MAP(Dialog_Storage_Out)
	ON_BN_CLICKED(IDC_EXCEL, OnExcel)
	ON_BN_CLICKED(IDC_BUTTON_NEW, OnButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnButtonPrint)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, OnButtonQuit)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_NOTIFY(NM_DBLCLK, IDC_RICHEDIT_DEPARTMENT, OnDblclkRicheditDepartment)
	ON_NOTIFY(NM_DBLCLK, IDC_RICHEDIT_DIGEST, OnDblclkRicheditDigest)
	ON_NOTIFY(NM_DBLCLK, IDC_RICHEDIT_OPERATOR, OnDblclkRicheditOperator)
	ON_NOTIFY(NM_DBLCLK, IDC_RICHEDIT_PROVIDER, OnDblclkRicheditProvider)
	ON_NOTIFY(NM_DBLCLK, IDC_RICHEDIT_STORAGE, OnDblclkRicheditStorage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_Out message handlers

BOOL Dialog_Storage_Out::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CTime time1 = CTime::GetCurrentTime();
	m_timeCurrent = time1;
	m_timePayment = time1;
	m_Operator = g_user;
	m_Department = g_department;
	static indexid=0;
	m_StorageInID.Format("CK-%04d-%02d-%02d-%03d",m_timeCurrent.GetYear(),m_timeCurrent.GetMonth(),m_timeCurrent.GetDay(),++indexid);
	
	m_listStorageIn.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listStorageIn.InsertColumn(0, _T("行号"), LVCFMT_LEFT,60);
	m_listStorageIn.InsertColumn(1, _T("仓库编号"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(2, _T("仓库全称"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(3, _T("SCB"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(4, _T("名称"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(5, _T("数量"), LVCFMT_LEFT,80);
	m_listStorageIn.InsertColumn(6, _T("单位"), LVCFMT_LEFT,80);
	m_listStorageIn.InsertColumn(7, _T("单价"), LVCFMT_LEFT,80);
	m_listStorageIn.InsertColumn(8, _T("金额"), LVCFMT_LEFT,100);

	m_listTotal.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listTotal.InsertColumn(0, _T("合计"), LVCFMT_LEFT,60);
	m_listTotal.InsertColumn(1, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(2, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(3, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(4, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(5, _T(""), LVCFMT_LEFT,80);
	m_listTotal.InsertColumn(6, _T(""), LVCFMT_LEFT,80);
	m_listTotal.InsertColumn(7, _T(""), LVCFMT_LEFT,80);
	m_listTotal.InsertColumn(8, _T(""), LVCFMT_LEFT,100);

	CString strindex ;
	int index = 0;
	while(index<15)
	{
		strindex.Format("%d",index+1);
		m_listStorageIn.InsertItem(index,strindex);
		if(index%2==0)
			m_listStorageIn.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));//灰色
		index++;
	}

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_Storage_Out::OnExcel() 
{
	// TODO: Add your control notification handler code here
	
}

void Dialog_Storage_Out::OnButtonNew() 
{
	// TODO: Add your control notification handler code here
	
}

void Dialog_Storage_Out::OnButtonPrint() 
{
	// TODO: Add your control notification handler code here
	
}

void Dialog_Storage_Out::OnButtonQuit() 
{
	// TODO: Add your control notification handler code here
	
}

void Dialog_Storage_Out::OnButtonSave() 
{
	UpdateData();
	int count = m_listStorageIn.GetItemCount();
	int i=0;
	CString strnumber;
	CString strprice;
	CString strmoney;
	CString strscb,stritemname;
	for(i=0;i<count;i++)
	{
		strscb = m_listStorageIn.GetItemText(i,3);
		stritemname = m_listStorageIn.GetItemText(i,4);
		if(strscb.IsEmpty()&& stritemname.IsEmpty())
			continue;
		strnumber = m_listStorageIn.GetItemText(i,5);
		if(strnumber.IsEmpty())
		{
			MessageBox("数量不能为空，请输入","提示",MB_OK);
			return;
		}
		else
		{
			if(!IsInt(strnumber))
			{
				MessageBox("数量输入必须为整数，请重新输入","提示",MB_OK);
				return;
			}
			if(atoi(strnumber)<=0)
			{
				MessageBox("数量输入非法，请重新输入","提示",MB_OK);
				return;
			}
		}
		strprice = m_listStorageIn.GetItemText(i,7);
		if(!(strprice.IsEmpty()))
		{
			if(!IsNum(strprice))
			{
				MessageBox("单价输入必须为数字，请重新输入","提示",MB_OK);
				return;
			}
		}
		strmoney = m_listStorageIn.GetItemText(i,8);
		if(!(strmoney.IsEmpty()))
		{
			if(!IsNum(strmoney))
			{
				MessageBox("金额输入必须为数字，请重新输入","提示",MB_OK);
				return;
			}
		}
	}
	
	CString strtimepayment;
	strtimepayment.Format("%04d-%02d-%02d",m_timePayment.GetYear(),m_timePayment.GetMonth(),m_timePayment.GetDay());
	CString strtimecurrent;
	strtimecurrent.Format("%04d-%02d-%02d",m_timeCurrent.GetYear(),m_timeCurrent.GetMonth(),m_timeCurrent.GetDay());


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
		sql.Format("select * from storage_out_baseinfo,storage_out_item where storage_out_baseinfo.storage_out_id=\"%s\" and storage_out_item.storage_out_id=\"%s\" ",m_StorageInID,m_StorageInID);
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
		dlgpro->setpos(600);
		result=mysql_store_result(&myCont);//保存查询到的数据到result
		if(result)
		{
			unsigned __int64 num = mysql_num_rows(result);//行数
			if(num>=1)
			{
				MessageBox("此单据编号已存在，请修改","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_STORAGE_IN_ID)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_STORAGE_IN_ID))->SetSel(0, -1);
				mysql_close(&myCont);//断开连接
				dlgpro->endpos();
				return;
			}
			else
			{//新增记录
				dlgpro->setpos(700);
				int count = m_listStorageIn.GetItemCount();
				int i=0,j=0;
				for(i=0;i<count;i++)
				{
					CString strscb = m_listStorageIn.GetItemText(i,3);
					CString stritemname = m_listStorageIn.GetItemText(i,4);
					if(strscb.IsEmpty()&& stritemname.IsEmpty())
						continue;
					CString storage_id = m_listStorageIn.GetItemText(i,1);
					CString storage_name = m_listStorageIn.GetItemText(i,2);
					CString SCB = m_listStorageIn.GetItemText(i,3);
					CString item_name = m_listStorageIn.GetItemText(i,4);
					int     item_number = atoi(m_listStorageIn.GetItemText(i,5));
					CString item_unit = m_listStorageIn.GetItemText(i,6);
					float   item_price = atof(m_listStorageIn.GetItemText(i,7));
					float   item_money = atof(m_listStorageIn.GetItemText(i,8));

					CTime time = CTime::GetCurrentTime();
					CString curenttime;
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
					result=mysql_store_result(&myCont);//保存查询到的数据到result
					if(result)
					{
						sql_row=mysql_fetch_row(result);
						curenttime = sql_row[0];
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
					//left
					sql.Format("select item_number,item_price from storage_left where scb=\"%s\" ",SCB);
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
						unsigned __int64 num = mysql_num_rows(result);//行数
						if(num>=1)
						{
							//修改记录	
							float oldprice = 0;
							int	  oldnumber = 0;
							float oldmoney = 0;
							while(sql_row=mysql_fetch_row(result))//获取具体的数据
							{
								if(sql_row[0]!=NULL)
									oldnumber = atoi(sql_row[0]);
								if(sql_row[1]!=NULL)
									oldprice = atof(sql_row[1]);					
							}//while
							if(oldnumber<item_number)
							{
								CString str;
								str.Format("%s 库存余额不足.",item_name);
								MessageBox(str,"提示",MB_OK);
								mysql_close(&myCont);//断开连接
								dlgpro->endpos();
								return;
							}
							oldnumber -= (item_number);
							oldmoney = oldnumber* (oldprice);
							sql.Format("update storage_left set item_number=%d,item_money=%f,item_time=\"%s\" where scb=\"%s\" ",
								oldnumber,oldmoney,curenttime,SCB);
							int ret = mysql_query(&myCont,sql);
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
						}
						else
						{//
							CString str;
							str.Format("库存无此物品：%s ",item_name);
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
					//item
					sql.Format("insert into storage_out_item values (%d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",%0.2f,%0.2f)",
					0,m_StorageInID,storage_id,storage_name,SCB,item_name,(item_number),item_unit,(item_price),(item_money));
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
					
				}//for
				dlgpro->setpos(900);
				sql.Format("insert into storage_out_baseinfo values (\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\")",
					m_StorageInID,strtimecurrent,m_Provider,m_Operator,m_Department,strtimepayment,m_Storage,m_Digest);
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
				dlgpro->setpos(980);
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
	MessageBox("出库单保存成功","提示",MB_OK);
}

void Dialog_Storage_Out::OnDblclkRicheditDepartment(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void Dialog_Storage_Out::OnDblclkRicheditDigest(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void Dialog_Storage_Out::OnDblclkRicheditOperator(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void Dialog_Storage_Out::OnDblclkRicheditProvider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void Dialog_Storage_Out::OnDblclkRicheditStorage(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

BOOL Dialog_Storage_Out::PreTranslateMessage(MSG* pMsg) 
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
