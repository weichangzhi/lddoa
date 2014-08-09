// Dialog_Storage_In.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_Storage_In.h"
#include "Dialog_progress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_Storage_In dialog


Dialog_Storage_In::Dialog_Storage_In(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_Storage_In::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_Storage_In)
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


void Dialog_Storage_In::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_Storage_In)
	DDX_Control(pDX, IDC_LIST_TOTAL, m_listTotal);
	DDX_Control(pDX, IDC_BUTTON_QUERY, m_btquery);
	DDX_Control(pDX, IDC_BUTTON_MODIFY, m_btmodify);
	DDX_Control(pDX, IDC_EDIT_MODIFY2, m_edit2);
	DDX_Control(pDX, IDC_RICHEDIT_MODIFY, m_edit);
	DDX_Control(pDX, IDC_EXCEL, m_btExcel);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_btSave);
	DDX_Control(pDX, IDC_BUTTON_QUIT, m_btQuit);
	DDX_Control(pDX, IDC_BUTTON_PRINT, m_btPrint);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_btNew);
	DDX_Control(pDX, IDC_LIST_STORAGE_IN, m_listStorageIn);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_CURRENT, m_timeCurrent);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_PAYMENT, m_timePayment);
	DDX_Text(pDX, IDC_EDIT_STORAGE_IN_ID, m_StorageInID);
	DDX_Text(pDX, IDC_RICHEDIT_DEPARTMENT, m_Department);
	DDX_Text(pDX, IDC_RICHEDIT_DIGEST, m_Digest);
	DDX_Text(pDX, IDC_RICHEDIT_OPERATOR, m_Operator);
	DDX_Text(pDX, IDC_RICHEDIT_PROVIDER, m_Provider);
	DDX_Text(pDX, IDC_RICHEDIT_STORAGE, m_Storage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_Storage_In, CDialog)
	//{{AFX_MSG_MAP(Dialog_Storage_In)
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
// Dialog_Storage_In message handlers

BOOL Dialog_Storage_In::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN) 
	{  
		switch(pMsg->wParam) 
		{  
		case VK_RETURN: //�س�  
			return TRUE;  
		case VK_ESCAPE: //ESC  
			return TRUE;  
		}  
	}

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL Dialog_Storage_In::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CTime time1 = CTime::GetCurrentTime();
	m_timeCurrent = time1;
	m_timePayment = time1;
	m_Operator = g_user;
	m_Department = g_department;
	static indexid=0;
	m_StorageInID.Format("JH-%04d-%02d-%02d-%03d",m_timeCurrent.GetYear(),m_timeCurrent.GetMonth(),m_timeCurrent.GetDay(),++indexid);
	
	m_listStorageIn.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listStorageIn.InsertColumn(0, _T("�к�"), LVCFMT_LEFT,60);
	m_listStorageIn.InsertColumn(1, _T("�ֿ���"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(2, _T("�ֿ�ȫ��"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(3, _T("SCB"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(4, _T("����"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(5, _T("����"), LVCFMT_LEFT,80);
	m_listStorageIn.InsertColumn(6, _T("��λ"), LVCFMT_LEFT,80);
	m_listStorageIn.InsertColumn(7, _T("����"), LVCFMT_LEFT,80);
	m_listStorageIn.InsertColumn(8, _T("���"), LVCFMT_LEFT,100);
	m_listStorageIn.InsertColumn(9, _T("��ժҪ"), LVCFMT_LEFT,230);

	m_listTotal.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listTotal.InsertColumn(0, _T("�ϼ�"), LVCFMT_LEFT,60);
	m_listTotal.InsertColumn(1, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(2, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(3, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(4, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(5, _T(""), LVCFMT_LEFT,80);
	m_listTotal.InsertColumn(6, _T(""), LVCFMT_LEFT,80);
	m_listTotal.InsertColumn(7, _T(""), LVCFMT_LEFT,80);
	m_listTotal.InsertColumn(8, _T(""), LVCFMT_LEFT,100);
	m_listTotal.InsertColumn(9, _T(""), LVCFMT_LEFT,230);

	CString strindex ;
	int index = 0;
	while(index<15)
	{
		strindex.Format("%d",index+1);
		m_listStorageIn.InsertItem(index,strindex);
		if(index%2==0)
			m_listStorageIn.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));//��ɫ
		index++;
	}
	m_listStorageIn.InsertItem(15," ");
	m_listStorageIn.InsertItem(16," ");
	m_listStorageIn.InsertItem(17," ");
	m_listStorageIn.InsertItem(18,"�ϼ�");
	m_listStorageIn.SetItemColor(18,RGB(255,0,0),RGB(255,255,255));//��ɫ

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_Storage_In::OnExcel() 
{
	// TODO: Add your control notification handler code here
	
}

void Dialog_Storage_In::OnButtonNew() 
{
	// TODO: Add your control notification handler code here
	
}

void Dialog_Storage_In::OnButtonPrint() 
{
	// TODO: Add your control notification handler code here
	
}

void Dialog_Storage_In::OnButtonQuit() 
{
	// TODO: Add your control notification handler code here
	
}

void Dialog_Storage_In::OnButtonSave() 
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
			MessageBox("��������Ϊ�գ�������","��ʾ",MB_OK);
			return;
		}
		else
		{
			if(!IsInt(strnumber))
			{
				MessageBox("�����������Ϊ����������������","��ʾ",MB_OK);
				return;
			}
			if(atoi(strnumber)<=0)
			{
				MessageBox("��������Ƿ�������������","��ʾ",MB_OK);
				return;
			}
		}
		strprice = m_listStorageIn.GetItemText(i,7);
		if(!(strprice.IsEmpty()))
		{
			if(!IsNum(strprice))
			{
				MessageBox("�����������Ϊ���֣�����������","��ʾ",MB_OK);
				return;
			}
		}
		strmoney = m_listStorageIn.GetItemText(i,8);
		if(!(strmoney.IsEmpty()))
		{
			if(!IsNum(strmoney))
			{
				MessageBox("����������Ϊ���֣�����������","��ʾ",MB_OK);
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
		mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
		sql.Format("select * from storage_in_baseinfo,storage_in_item where storage_in_baseinfo.storage_in_id=\"%s\" and storage_in_item.storage_in_id=\"%s\" ",m_StorageInID,m_StorageInID);
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			dlgpro->endpos();
			return;
		}
		dlgpro->setpos(600);
		result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
		if(result)
		{
			unsigned __int64 num = mysql_num_rows(result);//����
			if(num>=1)
			{
				MessageBox("�˵��ݱ���Ѵ��ڣ����޸�","��ʾ",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_STORAGE_IN_ID)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_STORAGE_IN_ID))->SetSel(0, -1);
				mysql_close(&myCont);//�Ͽ�����
				dlgpro->endpos();
				return;
			}
			else
			{//������¼
				dlgpro->setpos(700);

				sql.Format("insert into storage_in_baseinfo values (\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\")",
					m_StorageInID,strtimecurrent,m_Provider,m_Operator,m_Department,strtimepayment,m_Storage,m_Digest);
				if(mysql_query(&myCont,sql)!= 0)
				{
					const char *error = mysql_error(&myCont);
					CString str;
					str.Format("���ݿ����(%s)",error);
					MessageBox(str,"��ʾ",MB_OK);
					mysql_close(&myCont);//�Ͽ�����
					dlgpro->endpos();
					return;
				}
				dlgpro->setpos(800);
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
					CString item_digest = m_listStorageIn.GetItemText(i,9);

					CTime time = CTime::GetCurrentTime();
					CString curenttime;
					CString strsql ;
					strsql.Format("select now()");
					if(mysql_query(&myCont,strsql)!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("���ݿ����(%s)",error);
						MessageBox(str,"��ʾ",MB_OK);
						mysql_close(&myCont);//�Ͽ�����
						dlgpro->endpos();
						return;
					}
					result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
					if(result)
					{
						sql_row=mysql_fetch_row(result);
						curenttime = sql_row[0];
					}
					else
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("���ݿ����(%s)",error);
						MessageBox(str,"��ʾ",MB_OK);
						mysql_close(&myCont);//�Ͽ�����
						dlgpro->endpos();
						return;
					}

					//item
					sql.Format("insert into storage_in_item values (%d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d,\"%s\",%0.2f,%0.2f,\"%s\")",
					0,m_StorageInID,storage_id,storage_name,SCB,item_name,(item_number),item_unit,(item_price),(item_money),item_digest);
					if(mysql_query(&myCont,sql)!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("���ݿ����(%s)",error);
						MessageBox(str,"��ʾ",MB_OK);
						mysql_close(&myCont);//�Ͽ�����
						dlgpro->endpos();
						return;
					}
					//left
					sql.Format("select item_number,item_price from storage_left where scb=\"%s\" ",SCB);
					if(mysql_query(&myCont,sql)!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("���ݿ����(%s)",error);
						MessageBox(str,"��ʾ",MB_OK);
						mysql_close(&myCont);//�Ͽ�����
						dlgpro->endpos();
						return;
					}
					dlgpro->setpos(600);
					result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
					if(result)
					{
						unsigned __int64 num = mysql_num_rows(result);//����
						if(num>=1)
						{
							//�޸ļ�¼	
							float oldprice = 0;
							int	  oldnumber = 0;
							float oldmoney = 0;
							while(sql_row=mysql_fetch_row(result))//��ȡ���������
							{
								if(sql_row[0]!=NULL)
									oldnumber = atoi(sql_row[0]);
								if(sql_row[1]!=NULL)
									oldprice = atof(sql_row[1]);					
							}//while		
							oldnumber += (item_number);
							oldmoney = oldnumber* (item_price);
							dlgpro->setpos(800);
							sql.Format("update storage_left set item_number=%d,item_price=%f,item_money=%f,item_time=\"%s\" where scb=\"%s\" ",
								oldnumber,(item_price),oldmoney,curenttime,SCB);
							int ret = mysql_query(&myCont,sql);
							if(ret!= 0)
							{
								const char *error = mysql_error(&myCont);
								CString str;
								str.Format("���ݿ����(%s)",error);
								MessageBox(str,"��ʾ",MB_OK);
								mysql_close(&myCont);//�Ͽ�����
								dlgpro->endpos();
								return;
							}
						}
						else
						{//������¼
							dlgpro->setpos(700);
							sql.Format("insert into storage_left values (\"%s\",\"%s\",%d,\"%s\",%f,%f,\"%s\")",
								SCB,item_name,item_number,item_unit,item_price,item_money,curenttime);
							if(mysql_query(&myCont,sql)!= 0)
							{
								const char *error = mysql_error(&myCont);
								CString str;
								str.Format("���ݿ����(%s)",error);
								MessageBox(str,"��ʾ",MB_OK);
								mysql_close(&myCont);//�Ͽ�����
								dlgpro->endpos();
								return;
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
						dlgpro->endpos();
						return;
					}
					//detail
					/*dlgpro->setpos(900);
					sql.Format("insert into fidetail values (%d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%d)",
							0,m_listid,m_money_totel,m_people_business,m_proceeds_way,m_money_proceeds,m_people_fi,strtimeproceeds,m_comment,m_bill_way,m_money_bill,m_bill_id,m_people_bill,strtimebill,m_comment_Bill,0);
					if(mysql_query(&myCont,sql)!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("���ݿ����(%s)",error);
						MessageBox(str,"��ʾ",MB_OK);
						mysql_close(&myCont);//�Ͽ�����
						dlgpro->endpos();
						return;
					}
					*/
					dlgpro->setpos(980);


				}//for
				dlgpro->setpos(980);

			}
		}
		else
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			dlgpro->endpos();
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
		dlgpro->endpos();
		return;
	}
	if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
	mysql_close(&myCont);//�Ͽ�����
	dlgpro->endpos();
	MessageBox("����������ɹ�","��ʾ",MB_OK);

}

void Dialog_Storage_In::OnDblclkRicheditDepartment(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void Dialog_Storage_In::OnDblclkRicheditDigest(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void Dialog_Storage_In::OnDblclkRicheditOperator(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void Dialog_Storage_In::OnDblclkRicheditProvider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void Dialog_Storage_In::OnDblclkRicheditStorage(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

/*
void Dialog_Storage_In::OnKillfocusListStorageIn(NMHDR* pNMHDR, LRESULT* pResult) 
{
	return;
	CString str;
	m_edit2.GetWindowText(str);//ȡ�ñ༭�������
	m_listStorageIn.SetItemText(m_row,m_column,str);//�������ݸ��µ�CListCtrl��
	m_edit2.ShowWindow(SW_HIDE);//���ر༭��	
	UpdateData(FALSE);
	//*pResult = 0;
}

void Dialog_Storage_In::OnDblclkListStorageIn(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;
	CRect rc;
	if(pNMListView->iItem!=-1)
	{
	   m_row=pNMListView->iItem;//m_rowΪ��ѡ���е�����ţ�int���ͳ�Ա������
	   m_column=pNMListView->iSubItem;//m_columnΪ��ѡ���е�����ţ�int���ͳ�Ա������
	   m_listStorageIn.GetSubItemRect(pNMListView->iItem, pNMListView->iSubItem,LVIR_LABEL,rc);//ȡ������ľ���
	   rc.left+=12;
	   rc.top+=202;
	   rc.right+=12;
	   rc.bottom+=205;
	   char * ch=new char [128];
	   m_listStorageIn.GetItemText(pNMListView->iItem, pNMListView->iSubItem,ch,128);//ȡ�����������
	   m_edit2.SetWindowText(ch);//�������������ʾ���༭����
	   m_edit2.ShowWindow(SW_SHOW);//��ʾ�༭��
	   m_edit2.MoveWindow(&rc);//���༭���ƶ����������棬������������
	   m_edit2.SetFocus();//ʹ�༭��ȡ�ý���
	   m_edit2.CreateSolidCaret(1,rc.Height()-5);//����һ�����
	   m_edit2.ShowCaret();//��ʾ���
	   m_edit2.SetSel(0,-1);//ʹ����Ƶ������
	}
	*pResult = 0;
}


void Dialog_Storage_In::OnKillfocusEditModify2() 
{
	CString str;
	m_edit2.GetWindowText(str);//ȡ�ñ༭�������
	m_listStorageIn.SetItemText(m_row,m_column,str);//�������ݸ��µ�CListCtrl��
	m_edit2.ShowWindow(SW_HIDE);//���ر༭��	
	UpdateData(FALSE);
}
*/
