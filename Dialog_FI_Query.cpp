// Dialog_FI_Query.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_FI_Query.h"
#include "Dialog_FI_Proceeds.h"
#include "Dialog_progress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_FI_Query dialog


Dialog_FI_Query::Dialog_FI_Query(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_FI_Query::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_FI_Query)
	m_timebegin = 0;
	m_timeend = 0;
	//}}AFX_DATA_INIT
}


void Dialog_FI_Query::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_FI_Query)
	DDX_Control(pDX, IDOK, m_btok);
	DDX_Control(pDX, IDC_EXCEL, m_btexcel);
	DDX_Control(pDX, IDC_LIST_FI, m_listFI);
	DDX_Control(pDX, IDC_COMBO_QUERY_WAY, m_comQueryWay);
	DDX_Control(pDX, IDC_BUTTON_PROCEEDS, m_btproceeds);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_timebegin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_timeend);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_FI_Query, CDialog)
	//{{AFX_MSG_MAP(Dialog_FI_Query)
	ON_BN_CLICKED(IDC_EXCEL, OnExcel)
	ON_BN_CLICKED(IDC_BUTTON_PROCEEDS, OnButtonProceeds)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_FI, OnColumnclickListFi)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_FI, OnRclickListFi)
	ON_COMMAND(IDM_MODIFY, OnModify)
	ON_COMMAND(IDM_DELETE, OnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_FI_Query message handlers

BOOL Dialog_FI_Query::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if((g_permission & FI)==0)
	{
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		GetDlgItem(IDC_EXCEL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PROCEEDS)->EnableWindow(FALSE);
	}
	m_comQueryWay.InsertString(0,"����δ�տ�");
	m_comQueryWay.InsertString(1,"ȫ��δ�տ�");
	m_comQueryWay.InsertString(2,"����δ��Ʊ");
	m_comQueryWay.InsertString(3,"ȫ��δ��Ʊ");
	m_comQueryWay.InsertString(4,"ȫ��");
	m_comQueryWay.SetCurSel(4);

	m_listFI.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listFI.InsertColumn(0, _T("���"), LVCFMT_LEFT,50);
	m_listFI.InsertColumn(1, _T("������"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(2, _T("��������"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(3, _T("ҵ�񾭰���"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(4, _T("�տʽ"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(5, _T("��Ʊ����"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(6, _T("ǩ����Ԫ��"), LVCFMT_LEFT,140);
	m_listFI.InsertColumn(7, _T("���տ��Ԫ��"), LVCFMT_LEFT,140);
	m_listFI.InsertColumn(8, _T("�ѿ�Ʊ��Ԫ��"), LVCFMT_LEFT,140);
	m_listFI.InsertColumn(9, _T("δ�տ��Ԫ��"), LVCFMT_LEFT,140);
	m_listFI.InsertColumn(10, _T("δ��Ʊ��Ԫ��"), LVCFMT_LEFT,140);

	CTime time1 = CTime::GetCurrentTime();
	m_timebegin = time1;
	m_timeend = time1;

	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL Dialog_FI_Query::PreTranslateMessage(MSG* pMsg) 
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

void Dialog_FI_Query::OnOK() 
{
	int count = m_listFI.GetItemCount();
	for(int i=0;i<count;i++)
		m_listFI.SetItemColor(i,RGB(0,0,0),RGB(255,255,255));
	m_listFI.DeleteAllItems();
	UpdateData();

	CString starttime;
	starttime.Format("%04d-%02d-%02d",m_timebegin.GetYear(),m_timebegin.GetMonth(),m_timebegin.GetDay());
	CString endtime;
	endtime.Format("%04d-%02d-%02d",m_timeend.GetYear(),m_timeend.GetMonth(),m_timeend.GetDay()+1);

	CString csSql;
	int indexsel = m_comQueryWay.GetCurSel();
	/*
	switch(indexsel)
	{
	case 0://����δ�տ�
		csSql.Format("select listid,peoplebusiness,proceedsway,billway,moneytotel,moneyproceeds,moneybill  from fiproceeds where ficheck=%d and moneyproceeds>0 and moneyproceeds<moneytotel ",0);
		break;
	case 1://ȫ��δ�տ�
		csSql.Format("select listid,peoplebusiness,proceedsway,billway,moneytotel,moneyproceeds,moneybill  from fiproceeds where ficheck=%d and moneyproceeds=0",0);
		break;
	case 2://����δ��Ʊ
		csSql.Format("select listid,peoplebusiness,proceedsway,billway,moneytotel,moneyproceeds,moneybill  from fiproceeds where ficheck=%d and moneybill>0 and moneybill!=moneytotel",0);
		break;
	case 3://ȫ��δ��Ʊ
		csSql.Format("select listid,peoplebusiness,proceedsway,billway,moneytotel,moneyproceeds,moneybill  from fiproceeds where ficheck=%d and moneybill=0",0);
		break;
	case 4:
		csSql.Format("select listid,peoplebusiness,proceedsway,billway,moneytotel,moneyproceeds,moneybill  from fiproceeds where ficheck=%d ",0);
		break;
	default:
		csSql.Format("select listid,peoplebusiness,proceedsway,billway,moneytotel,moneyproceeds,moneybill  from fiproceeds where ficheck=%d ",0);
		break;
	}
*/
	csSql.Format("select fiproceeds.listid,fiproceeds.listname,peoplebusiness,proceedsway,billway,moneytotel,moneyproceeds,moneybill  from fiproceeds,scheduledetail where ficheck=%d and scheduledetail.listid=fiproceeds.listid  and businessendtime>=\"%s\" and businessendtime<=\"%s\"",0,starttime,endtime);

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
					float moneyproceedsleft = 0, moneyproceeds = 0, moneytotal = 0;
					float moneybillleft = 0,moneybill = 0;
					CString strindex ;
					int i=0;
					CString strproceeds,strbill;
					if(sql_row[5]!=NULL && sql_row[6]!=NULL && sql_row[7]!=NULL)
					{
						moneytotal = atof(sql_row[5]);
						moneyproceeds = atof(sql_row[6]);
						moneybill = atof(sql_row[7]);
						moneyproceedsleft = moneytotal - moneyproceeds;
						moneybillleft = moneytotal - moneybill;
					}

					switch(indexsel)
					{
					case 0://����δ�տ�
						if(!(moneyproceedsleft>0 && moneyproceeds>0))
							continue;
						break;
					case 1://ȫ��δ�տ�
						if(moneyproceeds!=0)
							continue;
						break;
					case 2://����δ��Ʊ
						if(!(moneybillleft>0 && moneybill>0))
							continue;
						break;
					case 3://ȫ��δ��Ʊ
						if(moneybill!=0)
							continue;
						break;
					case 4://ȫ��
						break;
					default:
						break;
					}

					strindex.Format("%d",index+1);
					m_listFI.InsertItem(index,strindex);

					for(i=1;i<=8;i++)
					{
						m_listFI.SetItemText(index,i,sql_row[i-1]);
					}
					strproceeds.Format("%0.2f",moneyproceedsleft);
					strbill.Format("%0.2f",moneybillleft);
					m_listFI.SetItemText(index,9,strproceeds);
					m_listFI.SetItemText(index,10,strbill);
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

void Dialog_FI_Query::OnExcel() 
{
	CreateExcel("�����ѯ.xls",&m_listFI);
}

void Dialog_FI_Query::OnButtonProceeds() 
{
	Dialog_FI_Proceeds dlg;
	dlg.DoModal();
}

void Dialog_FI_Query::OnColumnclickListFi(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	listsort(&m_listFI,pNMListView);
	*pResult = 0;
}

void Dialog_FI_Query::OnRclickListFi(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CMenu       menu ,* pSubMenu;//��������Ҫ�õ���cmenu����	
	menu.LoadMenu(IDR_MENU_FI);//װ���Զ�����Ҽ��˵�
	pSubMenu = menu.GetSubMenu(0);//��ȡ��һ�������˵������Ե�һ���˵��������Ӳ˵�	
    CPoint oPoint;//����һ������ȷ�����λ�õ�λ��	
    GetCursorPos( &oPoint);//��ȡ��ǰ����λ�ã��Ա�ʹ�ò˵����Ը�����
	int istat=m_listFI.GetSelectionMark();//��istat��ŵ�ǰѡ�����ǵڼ���	
	if(istat == -1) return;
	pSubMenu->TrackPopupMenu (TPM_LEFTALIGN, oPoint.x, oPoint.y, this); //��ָ��λ����ʾ�����˵�
	*pResult = 0;
}

void Dialog_FI_Query::OnModify() 
{
	int istat=m_listFI.GetSelectionMark();
	if(istat == -1) return;
	Dialog_FI_Proceeds dlg;
	dlg.m_listid = dlg.m_query_listid = m_listFI.GetItemText(istat,1);
	dlg.m_listName = m_listFI.GetItemText(istat,2);
	dlg.m_people_business = m_listFI.GetItemText(istat,3);
	dlg.m_proceeds_way = m_listFI.GetItemText(istat,4);
	dlg.m_bill_way = m_listFI.GetItemText(istat,5);
	dlg.m_money_totel = m_listFI.GetItemText(istat,6);
	dlg.m_money_proceeds = m_listFI.GetItemText(istat,9);
	dlg.m_money_bill = m_listFI.GetItemText(istat,10);
	int ret = dlg.DoModal();
	OnOK();
}

void Dialog_FI_Query::OnDelete() 
{
	int istat=m_listFI.GetSelectionMark();
	if(istat == -1) return;
	CString strlistid = m_listFI.GetItemText(istat,1);
	
	CString str;
	str.Format("�Ƿ�ɾ������%s���տƱ��¼��",strlistid);
	if(MessageBox(str,"��ʾ",MB_OKCANCEL)!=1)
		return;


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
		sql.Format("delete from fiproceeds  where listid=\"%s\" ",strlistid);
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
	MessageBox("ɾ����¼�ɹ�","��ʾ",MB_OK);

	m_listFI.DeleteItem(istat);
}
