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
	m_comQueryWay.InsertString(0,"部分未收款");
	m_comQueryWay.InsertString(1,"全部未收款");
	m_comQueryWay.InsertString(2,"部分未开票");
	m_comQueryWay.InsertString(3,"全部未开票");
	m_comQueryWay.InsertString(4,"全部");
	m_comQueryWay.SetCurSel(4);

	m_listFI.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listFI.InsertColumn(0, _T("序号"), LVCFMT_LEFT,50);
	m_listFI.InsertColumn(1, _T("订单号"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(2, _T("订单名称"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(3, _T("业务经办人"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(4, _T("收款方式"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(5, _T("发票类型"), LVCFMT_LEFT,100);
	m_listFI.InsertColumn(6, _T("签单金额（元）"), LVCFMT_LEFT,140);
	m_listFI.InsertColumn(7, _T("已收款金额（元）"), LVCFMT_LEFT,140);
	m_listFI.InsertColumn(8, _T("已开票金额（元）"), LVCFMT_LEFT,140);
	m_listFI.InsertColumn(9, _T("未收款金额（元）"), LVCFMT_LEFT,140);
	m_listFI.InsertColumn(10, _T("未开票金额（元）"), LVCFMT_LEFT,140);

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
		//case VK_RETURN: //回车  
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
	case 0://部分未收款
		csSql.Format("select listid,peoplebusiness,proceedsway,billway,moneytotel,moneyproceeds,moneybill  from fiproceeds where ficheck=%d and moneyproceeds>0 and moneyproceeds<moneytotel ",0);
		break;
	case 1://全部未收款
		csSql.Format("select listid,peoplebusiness,proceedsway,billway,moneytotel,moneyproceeds,moneybill  from fiproceeds where ficheck=%d and moneyproceeds=0",0);
		break;
	case 2://部分未开票
		csSql.Format("select listid,peoplebusiness,proceedsway,billway,moneytotel,moneyproceeds,moneybill  from fiproceeds where ficheck=%d and moneybill>0 and moneybill!=moneytotel",0);
		break;
	case 3://全部未开票
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
        mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
		dlgpro->setpos(500);
        res=mysql_query(&myCont,csSql);//查询
		dlgpro->setpos(700);
        if(!res)
        {
            result=mysql_store_result(&myCont);//保存查询到的数据到result
			dlgpro->setpos(950);
			dlgpro->endpos();
		    if(result)
            {
                int j;
                j=mysql_num_fields(result);//查看多少列
				unsigned __int64 num = mysql_num_rows(result);//行数
				int index = 0;

                while(sql_row=mysql_fetch_row(result))//获取具体的数据
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
					case 0://部分未收款
						if(!(moneyproceedsleft>0 && moneyproceeds>0))
							continue;
						break;
					case 1://全部未收款
						if(moneyproceeds!=0)
							continue;
						break;
					case 2://部分未开票
						if(!(moneybillleft>0 && moneybill>0))
							continue;
						break;
					case 3://全部未开票
						if(moneybill!=0)
							continue;
						break;
					case 4://全部
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
						m_listFI.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));//灰色
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
	return;
	//CDialog::OnOK();
}

void Dialog_FI_Query::OnExcel() 
{
	CreateExcel("财务查询.xls",&m_listFI);
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
	CMenu       menu ,* pSubMenu;//定义下面要用到的cmenu对象	
	menu.LoadMenu(IDR_MENU_FI);//装载自定义的右键菜单
	pSubMenu = menu.GetSubMenu(0);//获取第一个弹出菜单，所以第一个菜单必须有子菜单	
    CPoint oPoint;//定义一个用于确定光标位置的位置	
    GetCursorPos( &oPoint);//获取当前光标的位置，以便使得菜单可以跟随光标
	int istat=m_listFI.GetSelectionMark();//用istat存放当前选定的是第几项	
	if(istat == -1) return;
	pSubMenu->TrackPopupMenu (TPM_LEFTALIGN, oPoint.x, oPoint.y, this); //在指定位置显示弹出菜单
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
	str.Format("是否删除订单%s的收款开票记录？",strlistid);
	if(MessageBox(str,"提示",MB_OKCANCEL)!=1)
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
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
		sql.Format("delete from fiproceeds  where listid=\"%s\" ",strlistid);
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
	mysql_close(&myCont);//断开连接
	dlgpro->endpos();
	MessageBox("删除记录成功","提示",MB_OK);

	m_listFI.DeleteItem(istat);
}
