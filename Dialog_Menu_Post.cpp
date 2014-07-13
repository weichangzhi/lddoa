// Dialog_Menu_Post.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_Menu_Post.h"
#include "Dialog_Login2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_Menu_Post dialog


Dialog_Menu_Post::Dialog_Menu_Post(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_Menu_Post::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_Menu_Post)
	m_listid = _T("");
	m_postnumber = _T("");
	m_volume = _T("");
	m_indexdepartment = -1;
	//}}AFX_DATA_INIT
}


void Dialog_Menu_Post::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_Menu_Post)
	DDX_Control(pDX, IDC_COMBO_DEPARTMENT, m_department);
	DDX_Text(pDX, IDC_EDIT_LISTID, m_listid);
	DDX_Text(pDX, IDC_EDIT_POST_NUM, m_postnumber);
	DDX_Text(pDX, IDC_EDIT_VOLUME_SENDID, m_volume);
	DDX_CBIndex(pDX, IDC_COMBO_DEPARTMENT, m_indexdepartment);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_Menu_Post, CDialog)
	//{{AFX_MSG_MAP(Dialog_Menu_Post)
	ON_CBN_SELCHANGE(IDC_COMBO_DEPARTMENT, OnSelchangeComboDepartment)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_Menu_Post message handlers

BOOL Dialog_Menu_Post::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_department.InsertString(0,"技术部");
	m_department.InsertString(1,"生产部");
	m_department.InsertString(2,"质检");
	m_department.InsertString(3,"成品仓");
	m_department.InsertString(4,"物流");
	m_department.SetCurSel(m_indexdepartment);
	switch(m_indexdepartment)
	{
	case 0://技术部
		SetWindowText("技术部过账");
		GetDlgItem(IDC_STATIC1)->SetWindowText("总体积（cm3）:");
		GetDlgItem(IDC_STATIC1)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID)->ShowWindow(TRUE);
		m_permission = POST_TC;
		break;
	case 1://生产部
		SetWindowText("生产部过账");
		GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID)->ShowWindow(FALSE);
		m_permission = POST_PD;
		break;
	case 2://质检
		SetWindowText("质检部过账");
		GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID)->ShowWindow(FALSE);
		m_permission = QC;
		break;
	case 3://成品仓
		SetWindowText("成品仓过账");
		GetDlgItem(IDC_STATIC1)->SetWindowText("快递公司及单号:");
		GetDlgItem(IDC_STATIC1)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID)->ShowWindow(TRUE);
		m_permission = POST_STORAGE;
		break;
	case 4://物流
		SetWindowText("物流过账");
		GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID)->ShowWindow(FALSE);
		m_permission = POST_SEND;
		break;
	default:
		break;
	}
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_Menu_Post::OnOK() 
{
	UpdateData();

	CString strdepartment;
	m_department.GetWindowText(strdepartment);
	int indexSel = m_department.GetCurSel();

	if(!(m_postnumber.IsEmpty()))
	{
		if(!IsInt(m_postnumber))
		{
			MessageBox("过账数量输入必须为整数，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM))->SetSel(0, -1);
			return;
		}
	}
	if(atoi(m_postnumber)<=0)
	{
		MessageBox("过账数量不正确，请重新输入","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM))->SetSel(0, -1);
		return;
	}
	if (indexSel==0)
	{
		if(!(m_volume.IsEmpty()))
		{
			if(!IsNum(m_volume))
			{
				MessageBox("体积输入必须为数字，请重新输入","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID))->SetSel(0, -1);
				return;
			}
		}
		if(atof(m_volume)<=0)
		{
			MessageBox("体积输入不正确，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID))->SetSel(0, -1);
			return;
		}
	}
	int postnumber = atoi(m_postnumber);

	CDialog_Login2 login2;
	login2.m_department = strdepartment;
	login2.m_permission = m_permission;
	if (login2.DoModal()!=IDOK)
	{
		return;
	}

	CString sql;
	sql.Format("select * from schedule where listid=\"%s\" ",m_listid);

	
	int totelnumber,businessnumber,tcnumber,pdnumber,qcnumber,storagenumber,sendnumber,post,end,hasstoragenumber;
	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	mysql_init(&myCont);
	if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
	{
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
		if(mysql_query(&myCont,sql)!= 0)
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
			int j;
			j=mysql_num_fields(result);//查看多少列
			unsigned __int64 num = mysql_num_rows(result);//行数
			int index = 0;
			sql_row=mysql_fetch_row(result);//获取具体的数据
			if(sql_row==NULL)
			{
				MessageBox("无此订单号（可能还没下单）","提示",MB_OK);
				if(result!=NULL) mysql_free_result(result);//释放结果资源
					mysql_close(&myCont);//断开连接
			}
			totelnumber		= atoi(sql_row[2]);
			businessnumber	= atoi(sql_row[3]);
			tcnumber		= atoi(sql_row[4]);
			pdnumber		= atoi(sql_row[5]);
			qcnumber		= atoi(sql_row[6]);
			storagenumber	= atoi(sql_row[7]);
			sendnumber		= atoi(sql_row[8]);
			post			= atoi(sql_row[9]);
			end				= atoi(sql_row[10]);
			hasstoragenumber= atoi(sql_row[11]);
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

		
		CTime time = CTime::GetCurrentTime();
		CString currenttime;
		//currenttime.Format("%04d-%02d-%02d-%02d:%02d",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute());
		
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
			if(sql_row==NULL)
			{
				const char *error = mysql_error(&myCont);
				CString str;
				str.Format("数据库错误(%s)",error);
				MessageBox(str,"提示",MB_OK);
				mysql_close(&myCont);//断开连接
				return;
			}
			currenttime = sql_row[0];
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

		
		int indexSel = m_department.GetCurSel();
		switch(indexSel)
		{
		case 0://技术部
			if( (postnumber>tcnumber) || (postnumber>totelnumber))
			{
				MessageBox("过账数量不正确，请重新输入","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//释放结果资源
					mysql_close(&myCont);//断开连接
				return;
			}
			sql.Format("update schedule set tcnumber=%d,pdnumber=%d  where listid=\"%s\" ",tcnumber-postnumber,pdnumber+postnumber,m_listid);
			if(mysql_query(&myCont,sql)!= 0)
			{
				const char *error = mysql_error(&myCont);
				CString str;
				str.Format("数据库错误(%s)",error);
				MessageBox(str,"提示",MB_OK);
				mysql_close(&myCont);//断开连接
				return;
			}

			sql.Format("update scheduledetail set tcendtime=\"%s\",tcnumber=%d,tcpeople=\"%s\",pdstarttme=\"%s\" where listid=\"%s\" ",currenttime,postnumber,login2.m_user,currenttime,m_listid);
			if(mysql_query(&myCont,sql)!= 0)
			{
				const char *error = mysql_error(&myCont);
				CString str;
				str.Format("数据库错误(%s)",error);
				MessageBox(str,"提示",MB_OK);
				mysql_close(&myCont);//断开连接
				return;
			}

			sql.Format("update baseinfo set volume=\"%s\"  where listid=\"%s\" ",m_volume,m_listid);
			if(mysql_query(&myCont,sql)!= 0)
			{
				const char *error = mysql_error(&myCont);
				CString str;
				str.Format("数据库错误(%s)",error);
				MessageBox(str,"提示",MB_OK);
				mysql_close(&myCont);//断开连接
				return;
			}
			break;
		case 1://生产部
			if( (postnumber>pdnumber) || (postnumber>totelnumber))
			{
				const char *error = mysql_error(&myCont);
				CString str;
				str.Format("数据库错误(%s)",error);
				MessageBox(str,"提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//释放结果资源
					mysql_close(&myCont);//断开连接
				return;
			}
			sql.Format("update schedule set pdnumber=%d,qcnumber=%d  where listid=\"%s\" ",pdnumber-postnumber,qcnumber+postnumber,m_listid);
			if(mysql_query(&myCont,sql)!= 0)
			{
				const char *error = mysql_error(&myCont);
				CString str;
				str.Format("数据库错误(%s)",error);
				MessageBox(str,"提示",MB_OK);
				mysql_close(&myCont);//断开连接
				return;
			}

			sql.Format("update scheduledetail set pdendtime=\"%s\",pdnumber=%d,pdpeople=\"%s\",qcstarttime=\"%s\" where listid=\"%s\" ",currenttime,postnumber,login2.m_user,currenttime,m_listid);
			if(mysql_query(&myCont,sql)!= 0)
			{
				const char *error = mysql_error(&myCont);
				CString str;
				str.Format("数据库错误(%s)",error);
				MessageBox(str,"提示",MB_OK);
				mysql_close(&myCont);//断开连接
				return;
			}
			break;
		case 2://质检
			if( (postnumber>qcnumber) || (postnumber>totelnumber))
			{
				MessageBox("过账数量不正确，请重新输入","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//释放结果资源
					mysql_close(&myCont);//断开连接
				return;
			}
			sql.Format("update schedule set qcnumber=%d,storagenumber=%d  where listid=\"%s\" ",qcnumber-postnumber,storagenumber+postnumber,m_listid);
			if(mysql_query(&myCont,sql)!= 0)
			{
				const char *error = mysql_error(&myCont);
				CString str;
				str.Format("数据库错误(%s)",error);
				MessageBox(str,"提示",MB_OK);
				mysql_close(&myCont);//断开连接
				return;
			}

			sql.Format("update scheduledetail set qcendtime=\"%s\",qcnumber=%d,qcpeople=\"%s\",storagestarttime=\"%s\" where listid=\"%s\" ",currenttime,postnumber,login2.m_user,currenttime,m_listid);
			if(mysql_query(&myCont,sql)!= 0)
			{
				const char *error = mysql_error(&myCont);
				CString str;
				str.Format("数据库错误(%s)",error);
				MessageBox(str,"提示",MB_OK);
				mysql_close(&myCont);//断开连接
				return;
			}
			break;
		case 3://成品仓
			if( (postnumber>storagenumber) || (postnumber>totelnumber))
			{
				MessageBox("过账数量不正确，请重新输入","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//释放结果资源
					mysql_close(&myCont);//断开连接
				return;
			}
			sql.Format("update schedule set storagenumber=%d,sendnumber=%d,hasstoragenumber=%d  where listid=\"%s\" ",storagenumber-postnumber,sendnumber+postnumber,hasstoragenumber+postnumber , m_listid);
			if(mysql_query(&myCont,sql)!= 0)
			{
				const char *error = mysql_error(&myCont);
				CString str;
				str.Format("数据库错误(%s)",error);
				MessageBox(str,"提示",MB_OK);
				mysql_close(&myCont);//断开连接
				return;
			}

			sql.Format("update scheduledetail set storageendtime=\"%s\",storagenumber=%d,storagepopple=\"%s\",sendstarttime=\"%s\" where listid=\"%s\" ",currenttime,postnumber,login2.m_user,currenttime,m_listid);
			if(mysql_query(&myCont,sql)!= 0)
			{
				const char *error = mysql_error(&myCont);
				CString str;
				str.Format("数据库错误(%s)",error);
				MessageBox(str,"提示",MB_OK);
				mysql_close(&myCont);//断开连接
				return;
			}

			sql.Format("update baseinfo set sendid=\"%s\"  where listid=\"%s\" ",m_volume,m_listid);
			if(mysql_query(&myCont,sql)!= 0)
			{
				const char *error = mysql_error(&myCont);
				CString str;
				str.Format("数据库错误(%s)",error);
				MessageBox(str,"提示",MB_OK);
				mysql_close(&myCont);//断开连接
				return;
			}
			break;
		case 4://物流
			if( (postnumber>sendnumber) || (postnumber>totelnumber))
			{
				MessageBox("过账数量不正确，请重新输入","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//释放结果资源
					mysql_close(&myCont);//断开连接
				return;
			}
			sql.Format("update schedule set sendnumber=%d,post=%d where listid=\"%s\" ",sendnumber-postnumber,post+postnumber,m_listid);
			if(mysql_query(&myCont,sql)!= 0)
			{
				const char *error = mysql_error(&myCont);
				CString str;
				str.Format("数据库错误(%s)",error);
				MessageBox(str,"提示",MB_OK);
				mysql_close(&myCont);//断开连接
				return;
			}

			sql.Format("update scheduledetail set sendendtime=\"%s\",sendnumber=%d,sendpeople=\"%s\"  where listid=\"%s\" ",currenttime,postnumber,login2.m_user,m_listid);
			if(mysql_query(&myCont,sql)!= 0)
			{
				const char *error = mysql_error(&myCont);
				CString str;
				str.Format("数据库错误(%s)",error);
				MessageBox(str,"提示",MB_OK);
				mysql_close(&myCont);//断开连接
				return;
			}
			break;
		default:
			;
		}
		if(mysql_affected_rows(&myCont)>0)
		{
			MessageBox("过账成功","提示",MB_OK);
		}
		else
		{
			MessageBox("过账成功","提示",MB_OK);
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
	
	CDialog::OnOK();
}

void Dialog_Menu_Post::OnSelchangeComboDepartment() 
{
	int indexSel = m_department.GetCurSel();
	switch(indexSel)
	{
	case 0://技术部
		GetDlgItem(IDC_STATIC1)->SetWindowText("总体积（cm3）:");
		GetDlgItem(IDC_STATIC1)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID)->ShowWindow(TRUE);
		m_permission = POST_TC;
		break;
	case 1://生产部
		GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID)->ShowWindow(FALSE);
		m_permission = POST_PD;
		break;
	case 2://质检
		GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID)->ShowWindow(FALSE);
		m_permission = QC;
		break;
	case 3://成品仓
		GetDlgItem(IDC_STATIC1)->SetWindowText("快递公司及单号:");
		GetDlgItem(IDC_STATIC1)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID)->ShowWindow(TRUE);
		m_permission = POST_STORAGE;
		break;
	case 4://物流
		GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID)->ShowWindow(FALSE);
		m_permission = POST_SEND;
		break;
	default:
		break;
	}	
}

BOOL Dialog_Menu_Post::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN) 
	{  
		switch(pMsg->wParam) 
		{  
			//		case VK_RETURN: //回车  
			//			return TRUE;  
		case VK_ESCAPE: //ESC  
			return TRUE;  
		}  
	}	
	return CDialog::PreTranslateMessage(pMsg);
}
