// Dialog_Output.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_Output.h"
#include "Dialog_progress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Output dialog


CDialog_Output::CDialog_Output(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Output::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Output)
	m_time_start = 0;
	m_time_end = 0;
	m_strName = _T("");
	m_strDepartment = _T("");
	//}}AFX_DATA_INIT
}


void CDialog_Output::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Output)
	DDX_Control(pDX, IDOK, m_btnok);
	DDX_Control(pDX, IDC_EXCEL, m_btnexcel);
	DDX_Control(pDX, IDC_EDIT_NAME, m_EditName);
	DDX_Control(pDX, IDC_COMBO_WAY, m_ComWay);
	DDX_Control(pDX, IDC_LIST_OUTPUT, m_list_output);
	DDX_Control(pDX, IDC_COMBO_OUTPUT, m_com_output);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_time_start);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_time_end);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_STATIC_DEPARTMENT, m_strDepartment);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Output, CDialog)
	//{{AFX_MSG_MAP(CDialog_Output)
	ON_BN_CLICKED(IDC_EXCEL, OnExcel)
	ON_CBN_SELCHANGE(IDC_COMBO_WAY, OnSelchangeComboWay)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_OUTPUT, OnColumnclickListOutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Output message handlers

BOOL CDialog_Output::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//m_com_output.InsertString(0,"业务部");
	//m_com_output.InsertString(1,"技术部");
	//m_com_output.InsertString(1,"生产部");
	//m_com_output.SetCurSel(0);

	m_list_output.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list_output.InsertColumn(0, _T("序号"), LVCFMT_LEFT,60);
	m_list_output.InsertColumn(1, _T("订单号"), LVCFMT_LEFT,100);
	m_list_output.InsertColumn(2, _T("订单名称"), LVCFMT_LEFT,80);
	m_list_output.InsertColumn(3, _T("经办人"), LVCFMT_LEFT,100);
	m_list_output.InsertColumn(4, _T("营销部门"), LVCFMT_LEFT,80);
	m_list_output.InsertColumn(5, _T("产品总数"), LVCFMT_LEFT,80);
	m_list_output.InsertColumn(6, _T("制作材料"), LVCFMT_LEFT,150);
	m_list_output.InsertColumn(7, _T("订单金额(元)"), LVCFMT_LEFT,110);
	m_list_output.InsertColumn(8, _T("订单体积(cm3)"), LVCFMT_LEFT,120);
	m_list_output.InsertColumn(9, _T("快递单号"), LVCFMT_LEFT,90);
	m_list_output.InsertColumn(10, _T("业务部"), LVCFMT_LEFT,80);
	m_list_output.InsertColumn(11, _T("技术部"), LVCFMT_LEFT,80);
	m_list_output.InsertColumn(12, _T("生产部"), LVCFMT_LEFT,80);
	m_list_output.InsertColumn(13, _T("质检"), LVCFMT_LEFT,80);
	m_list_output.InsertColumn(14, _T("成品仓"), LVCFMT_LEFT,80);
	m_list_output.InsertColumn(15, _T("物流"), LVCFMT_LEFT,80);
	CTime time1 = CTime::GetCurrentTime();
	m_time_start = time1;
	m_time_end = time1;

	m_ComWay.InsertString(0,"个人");
	m_ComWay.InsertString(1,"部门");
	m_ComWay.InsertString(2,"全部");
	m_ComWay.SetCurSel(0);

	m_com_output.InsertString(0,"意造销售");
	m_com_output.InsertString(1,"电商");
	m_com_output.InsertString(2,"运营");
	m_com_output.InsertString(3,"加盟");
	m_com_output.InsertString(4,"研发");
	m_com_output.InsertString(5,"技术部意造");
	m_com_output.InsertString(6,"技术部记梦馆");
	m_com_output.InsertString(7,"生产部");
	m_com_output.InsertString(8,"成品仓");
	m_com_output.ShowWindow(FALSE);
	//m_strDepartment = "负责人";
	m_strName = g_user;
	m_EditName.ShowWindow(TRUE);
	m_com_output.ShowWindow(FALSE);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_Output::OnOK() 
{
	int count = m_list_output.GetItemCount();
	for(int i=0;i<count;i++)
		m_list_output.SetItemColor(i,RGB(0,0,0),RGB(255,255,255));
	m_list_output.DeleteAllItems();
	UpdateData();
	CString csSql;
	CString starttime;
	starttime.Format("%04d-%02d-%02d",m_time_start.GetYear(),m_time_start.GetMonth(),m_time_start.GetDay());
	CString endtime;
	endtime.Format("%04d-%02d-%02d",m_time_end.GetYear(),m_time_end.GetMonth(),m_time_end.GetDay()+1);

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
	CString strdepartment;
	int indexSeldepartment;
	int curselway = m_ComWay.GetCurSel();
	switch (curselway)
	{
	case 0://个人
		csSql.Format("select department from userinfo where username=\"%s\" ",m_strName);
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
					unsigned __int64 num = mysql_num_rows(result);//行数
					if(num<1)
					{
						MessageBox("此用户名不存在","提示",MB_OK);
						(CEdit*)GetDlgItem(IDC_EDIT_NAME)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_NAME))->SetSel(0, -1);
						if(result!=NULL) mysql_free_result(result);//释放结果资源
						mysql_close(&myCont);//断开连接
						dlgpro->endpos();
						return;
					}
					sql_row=mysql_fetch_row(result);
					if(sql_row)
					{
						strdepartment = sql_row[0];
					}
					else
					{
						MessageBox("此用户名不存在","提示",MB_OK);
						(CEdit*)GetDlgItem(IDC_EDIT_USER)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_USER))->SetSel(0, -1);
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


		if ((strdepartment.Compare("意造销售")==0) ||
			(strdepartment.Compare("电商")==0) ||
			(strdepartment.Compare("运营")==0) ||
			(strdepartment.Compare("加盟")==0) ||
			(strdepartment.Compare("研发")==0) )
			csSql.Format("select baseinfo.listid,baseinfo.listname,baseinfo.people,baseinfo.department,baseinfo.truelistnumber,baseinfo.material,baseinfo.money,baseinfo.volume,baseinfo.sendid, businesspeople,tcpeople,pdpeople,qcpeople,storagepopple,sendpeople from baseinfo,scheduledetail where  baseinfo.listid=scheduledetail.listid and baseinfo.people=\"%s\" and businessendtime>=\"%s\"and businessendtime<=\"%s\" " ,m_strName,starttime,endtime);
		else if ((strdepartment.Compare("技术部意造")==0) || (strdepartment.Compare("技术部记梦馆")==0))
			csSql.Format("select baseinfo.listid,baseinfo.listname,baseinfo.people,baseinfo.department,baseinfo.truelistnumber,baseinfo.material,baseinfo.money,baseinfo.volume,baseinfo.sendid, businesspeople,tcpeople,pdpeople,qcpeople,storagepopple,sendpeople from baseinfo,scheduledetail where  baseinfo.listid=scheduledetail.listid and scheduledetail.tcpeople=\"%s\" and tcendtime>=\"%s\"and tcendtime<=\"%s\" " ,m_strName,starttime,endtime);
		else if ((strdepartment.Compare("生产部")==0))
			csSql.Format("select baseinfo.listid,baseinfo.listname,baseinfo.people,baseinfo.department,baseinfo.truelistnumber,baseinfo.material,baseinfo.money,baseinfo.volume,baseinfo.sendid, businesspeople,tcpeople,pdpeople,qcpeople,storagepopple,sendpeople from baseinfo,scheduledetail where  baseinfo.listid=scheduledetail.listid and scheduledetail.pdpeople=\"%s\" and pdendtime>=\"%s\"and pdendtime<=\"%s\" " ,m_strName,starttime,endtime);
		else if ((strdepartment.Compare("成品仓")==0))
			csSql.Format("select baseinfo.listid,baseinfo.listname,baseinfo.people,baseinfo.department,baseinfo.truelistnumber,baseinfo.material,baseinfo.money,baseinfo.volume,baseinfo.sendid, businesspeople,tcpeople,pdpeople,qcpeople,storagepopple,sendpeople from baseinfo,scheduledetail where  baseinfo.listid=scheduledetail.listid and scheduledetail.storagepopple=\"%s\" and storageendtime>=\"%s\"and storageendtime<=\"%s\" " ,m_strName,starttime,endtime);		
		break;
	case 1://部门
		m_com_output.GetWindowText(strdepartment);
		indexSeldepartment = m_com_output.GetCurSel();	
		switch(indexSeldepartment)
		{
		case 0://意造销售
		case 1://电商
		case 2://运营
		case 3://加盟
		case 4://研发
			csSql.Format("select baseinfo.listid,baseinfo.listname,baseinfo.people,baseinfo.department,baseinfo.truelistnumber,baseinfo.material,baseinfo.money,baseinfo.volume,baseinfo.sendid, businesspeople,tcpeople,pdpeople,qcpeople,storagepopple,sendpeople     from baseinfo,scheduledetail where  baseinfo.department=\"%s\" and baseinfo.listid=scheduledetail.listid and businessendtime>=\"%s\"and businessendtime<=\"%s\" " ,strdepartment,starttime,endtime);
			break;
		case 5://技术部意造
		case 6://技术部记梦馆
			csSql.Format("select baseinfo.listid,baseinfo.listname,baseinfo.people,baseinfo.department,baseinfo.truelistnumber,baseinfo.material,baseinfo.money,baseinfo.volume,baseinfo.sendid, businesspeople,tcpeople,pdpeople,qcpeople,storagepopple,sendpeople from userinfo,baseinfo,scheduledetail where userinfo.username=scheduledetail.tcpeople and  userinfo.department=\"%s\" and  baseinfo.listid=scheduledetail.listid and tcendtime>=\"%s\"and tcendtime<=\"%s\" " ,strdepartment,starttime,endtime);
			break;
		case 7://生产部
			csSql.Format("select baseinfo.listid,baseinfo.listname,baseinfo.people,baseinfo.department,baseinfo.truelistnumber,baseinfo.material,baseinfo.money,baseinfo.volume,baseinfo.sendid, businesspeople,tcpeople,pdpeople,qcpeople,storagepopple,sendpeople from baseinfo,scheduledetail where baseinfo.listid=scheduledetail.listid and pdendtime>=\"%s\"and pdendtime<=\"%s\" " ,starttime,endtime);
			break;
		case 8://成品仓
			csSql.Format("select baseinfo.listid,baseinfo.listname,baseinfo.people,baseinfo.department,baseinfo.truelistnumber,baseinfo.material,baseinfo.money,baseinfo.volume,baseinfo.sendid, businesspeople,tcpeople,pdpeople,qcpeople,storagepopple,sendpeople from baseinfo,scheduledetail where baseinfo.listid=scheduledetail.listid and storageendtime>=\"%s\"and storageendtime<=\"%s\" " ,starttime,endtime);
			break;
		default:
			break;
		}
		break;
	case 2://全部
		csSql.Format("select baseinfo.listid,baseinfo.listname,baseinfo.people,baseinfo.department,baseinfo.truelistnumber,baseinfo.material,baseinfo.money,baseinfo.volume,baseinfo.sendid, businesspeople,tcpeople,pdpeople,qcpeople,storagepopple,sendpeople     from baseinfo,scheduledetail where  baseinfo.listid=scheduledetail.listid and businessendtime>=\"%s\"and businessendtime<=\"%s\" " ,starttime,endtime);
		break;
	default:
		break;
	}
	dlgpro->setpos(700);

    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
    {
        mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
        res=mysql_query(&myCont,csSql);//查询
        if(!res)
        {
			dlgpro->setpos(800);
            result=mysql_store_result(&myCont);//保存查询到的数据到result
		    if(result)
            {
                int j;
                j=mysql_num_fields(result);//查看多少列
				unsigned __int64 num = mysql_num_rows(result);//行数
				int index = 0;
				double money=0, volume=0;
				int number = 0;
				int hasmoney = 0;
                while(sql_row=mysql_fetch_row(result))//获取具体的数据
                {
					number += atoi(sql_row[4]);
					//money += atof(sql_row[6]);
					volume += atof(sql_row[7]);
					CString strindex ;
					strindex.Format("%d",index+1);
					m_list_output.InsertItem(index,strindex);
					CString strdepartment = sql_row[3];
					CString strmoney;
					int i=0;
					for(i=1;i<=15;i++)
					{
						if(i==7)
						{
							strmoney = "******";
							if(((strdepartment.Compare("意造销售")==0) && (g_permission&MONEY_SELL))
								||((strdepartment.Compare("电商")==0) && (g_permission&MONEY_EC))
								||((strdepartment.Compare("运营")==0) && (g_permission&MONEY_RUN))
								||((strdepartment.Compare("加盟")==0) && (g_permission&MONEY_JOIN)))
							{
								strmoney = sql_row[i-1];
								money += atof(strmoney);
								hasmoney = 1;
							}
							m_list_output.SetItemText(index,i,strmoney);
							continue;
						}
						m_list_output.SetItemText(index,i,sql_row[i-1]);
					}
					if(index%2==0)
						m_list_output.SetItemColor(index,RGB(0,0,0),RGB(230,230,230));
					index++;
                }//while
				dlgpro->setpos(900);
				if(index!=0)
				{
					m_list_output.InsertItem(index++," ");
					m_list_output.InsertItem(index++," ");
					m_list_output.InsertItem(index++," ");
					m_list_output.InsertItem(index,"总计：");
					CString strtmp;
					strtmp.Format("%d",number);
					m_list_output.SetItemText(index,5,strtmp);

				
					strtmp.Format("%0.1f",money);
					if(hasmoney==1)
						m_list_output.SetItemText(index,7,strtmp);
					else
						m_list_output.SetItemText(index,7,"******");
					strtmp.Format("%0.1f",volume);
					m_list_output.SetItemText(index,8,strtmp);
					m_list_output.SetItemColor(index,RGB(255,0,0),RGB(255,255,255));
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

BOOL CDialog_Output::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
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

void CDialog_Output::OnExcel() 
{
	CreateExcel("产能统计.xls",&m_list_output);
}

void CDialog_Output::OnSelchangeComboWay() 
{
	CString strdepartment;
	strdepartment = g_department;
	int cursel = m_ComWay.GetCurSel();
	switch (cursel)
	{
	case 0://个人
		//m_strDepartment = "负责人";
		m_strName = g_user;
		m_EditName.ShowWindow(TRUE);
		m_com_output.ShowWindow(FALSE);
		break;
	case 1://部门
		//m_strDepartment = "部门";	
		m_EditName.ShowWindow(FALSE);
		m_com_output.ShowWindow(TRUE);
		if(strdepartment.Compare("意造销售")==0)
			m_com_output.SetCurSel(0);
		else if(strdepartment.Compare("电商")==0)
			m_com_output.SetCurSel(1);
		else if(strdepartment.Compare("运营")==0)
			m_com_output.SetCurSel(2);
		else if(strdepartment.Compare("加盟")==0)
			m_com_output.SetCurSel(3);
		else if(strdepartment.Compare("研发")==0)
			m_com_output.SetCurSel(4);
		else if(strdepartment.Compare("技术部意造")==0)
			m_com_output.SetCurSel(5);
		else if(strdepartment.Compare("技术部记梦馆")==0)
			m_com_output.SetCurSel(6);
		else if(strdepartment.Compare("生产部")==0)
			m_com_output.SetCurSel(7);
		else if(strdepartment.Compare("成品仓")==0)
			m_com_output.SetCurSel(8);
		break;
	case 2://全部
		//m_strDepartment = "";
		m_EditName.ShowWindow(FALSE);
		m_com_output.ShowWindow(FALSE);
		break;
	default:
		break;
	}
	UpdateData(FALSE);
	
}

void CDialog_Output::OnColumnclickListOutput(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	listsort(&m_list_output,pNMListView);
	*pResult = 0;
}
