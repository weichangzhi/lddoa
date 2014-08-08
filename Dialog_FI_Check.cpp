// Dialog_FI_Check.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_FI_Check.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_FI_Check dialog


Dialog_FI_Check::Dialog_FI_Check(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_FI_Check::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_FI_Check)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dialog_FI_Check::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_FI_Check)
	DDX_Control(pDX, IDC_BUTTON_CHECK, m_btcheck);
	DDX_Control(pDX, IDC_EXCEL, m_btexcel);
	DDX_Control(pDX, IDC_LIST_FI, m_listFI);
	DDX_Control(pDX, IDOK, m_btok);
	DDX_Control(pDX, IDC_COMBO_QUERY_WAY, m_com_queryway);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_FI_Check, CDialog)
	//{{AFX_MSG_MAP(Dialog_FI_Check)
	ON_BN_CLICKED(IDC_EXCEL, OnExcel)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_FI, OnColumnclickListFi)
	ON_BN_CLICKED(IDC_BUTTON_CHECK, OnButtonCheck)
	ON_CBN_SELCHANGE(IDC_COMBO_QUERY_WAY, OnSelchangeComboQueryWay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_FI_Check message handlers

BOOL Dialog_FI_Check::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if((g_permission & FI)==0)
	{
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		GetDlgItem(IDC_EXCEL)->EnableWindow(FALSE);
	}
	m_com_queryway.InsertString(0,"�ɺ���");
	m_com_queryway.InsertString(1,"�Ѻ���");
	m_com_queryway.SetCurSel(0);

	m_listFI.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES );
	m_listFI.InsertColumn(0, _T("���"), LVCFMT_LEFT,50);
	m_listFI.InsertColumn(1, _T("������"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(2, _T("�տʽ"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(3, _T("��Ʊ����"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(4, _T("ǩ����Ԫ��"), LVCFMT_LEFT,140);
	m_listFI.InsertColumn(5, _T("���տ��Ԫ��"), LVCFMT_LEFT,140);
	m_listFI.InsertColumn(6, _T("�ѿ�Ʊ��Ԫ��"), LVCFMT_LEFT,140);
	m_listFI.InsertColumn(7, _T("����״̬"), LVCFMT_LEFT,100);
	DWORD style = m_listFI.GetExtendedStyle();

	UpdateData(FALSE);	
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_FI_Check::OnOK() 
{
	int count = m_listFI.GetItemCount();
	for(int i=0;i<count;i++)
		m_listFI.SetItemColor(i,RGB(0,0,0),RGB(255,255,255));
	m_listFI.DeleteAllItems();
	UpdateData();

	CString csSql;
	int indexsel = m_com_queryway.GetCurSel();
	switch(indexsel)
	{
	case 0://�ɺ���
		csSql.Format("select listid,proceedsway,billway,moneytotel,moneyproceeds,moneybill  from fiproceeds where ficheck=%d and moneyproceeds>=moneytotel and moneybill>=moneytotel ",0);
		break;
	case 1://�Ѻ���
		csSql.Format("select listid,proceedsway,billway,moneytotel,moneyproceeds,moneybill  from fiproceeds where ficheck=%d",1);
		break;
	default:
		csSql.Format("select listid,proceedsway,billway,moneytotel,moneyproceeds,moneybill  from fiproceeds where ficheck=%d and moneyproceeds>=moneytotel and moneybill>=moneytotel ",0);
		break;
	}

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
        mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
		dlgpro->setpos(500);
        res=mysql_query(&myCont,csSql);//��ѯ
		dlgpro->setpos(700);
        if(!res)
        {
            result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
			dlgpro->setpos(950);
			dlgpro->endpos();
		    if(result)
            {
                int j;
                j=mysql_num_fields(result);//�鿴������
				unsigned __int64 num = mysql_num_rows(result);//����
				int index = 0;
				
                while(sql_row=mysql_fetch_row(result))//��ȡ���������
                {
					float moneyproceedsleft = 0;
					float moneybillleft = 0;
					CString strindex ;
					strindex.Format("%d",index+1);
					m_listFI.InsertItem(index,strindex);
					int i=0;
					for(i=1;i<=6;i++)
					{
						m_listFI.SetItemText(index,i,sql_row[i-1]);
					}
					int indexsel = m_com_queryway.GetCurSel();
					if(indexsel==0)
						m_listFI.SetItemText(index,7,"������");
					else
						m_listFI.SetItemText(index,7,"�Ѻ���");
					if(index%2==0)
						m_listFI.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));//��ɫ
					index++;
                }//while
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
	return;
	
	//CDialog::OnOK();
}

void Dialog_FI_Check::OnExcel() 
{
	CreateExcel("�������.xls",&m_listFI);
	
}

void Dialog_FI_Check::OnColumnclickListFi(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	listsort(&m_listFI,pNMListView);
	*pResult = 0;
}

BOOL Dialog_FI_Check::PreTranslateMessage(MSG* pMsg) 
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

void Dialog_FI_Check::OnButtonCheck() 
{

	CString strlistid;
	int selcount = 0;
	for(int i=0; i<m_listFI.GetItemCount(); i++)
	{
	   //if( m_listFI.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || m_listFI.GetCheck(i))
		if(m_listFI.GetCheck(i))
		{
			CString strtmp = m_listFI.GetItemText(i,1);
			strtmp+=",";
			strlistid+=strtmp;
			selcount++;
		}
	}
	if(selcount==0)
	{
		MessageBox("��ѡ�񶩵����ں���","��ʾ",MB_OK);
		return;
	}
	else
	{
		CString strtmp;
		strtmp.Format("�Ƿ��������:%s",strlistid);
		int ret = MessageBox(strtmp,"��ʾ",MB_OKCANCEL);
		if(ret!=IDOK)
			return;
	}
	Dialog_progress *dlgpro;
	dlgpro=new Dialog_progress(); 
	dlgpro->Create(IDD_DIALOG_PROGRESS);
	if(g_openprocess)
		dlgpro->ShowWindow(SW_SHOW);
	else
		dlgpro->ShowWindow(SW_HIDE);

	CString sql;
	MYSQL myCont;
	mysql_init(&myCont);
	if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
	{
		dlgpro->setpos(500);
		mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����

		for(int i=0; i<m_listFI.GetItemCount(); i++)
		{
			if(m_listFI.GetCheck(i))
			{
				CString strtmp = m_listFI.GetItemText(i,1);
				sql.Format("update fiproceeds set ficheck=%d where listid=\"%s\" ",1,strtmp);
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
		dlgpro->setpos(980);
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
	mysql_close(&myCont);//�Ͽ�����
	dlgpro->endpos();
	MessageBox("�����ɹ�","��ʾ",MB_OK);
}

void Dialog_FI_Check::OnSelchangeComboQueryWay() 
{
	int cursel = m_com_queryway.GetCurSel();
	DWORD style = m_listFI.GetExtendedStyle();
	switch (cursel)
	{
	case 0:
		style = style|LVS_EX_CHECKBOXES;
		break;
    case 1:
		style =  style&~LVS_EX_CHECKBOXES;
		break;
	default:
		style = style&LVS_EX_CHECKBOXES;
		break;		
	}
	m_listFI.SetExtendedStyle(style);
	m_listFI.DeleteAllItems();
}
