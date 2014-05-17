// Dialog_Unpost.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_Unpost.h"
#include "Dialog_Login2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_Unpost dialog


CDialog_Unpost::CDialog_Unpost(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Unpost::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Unpost)
	m_postid1 = _T("");
	m_postid2 = _T("");
	m_postid3 = _T("");
	m_postid4 = _T("");
	m_postid5 = _T("");
	m_postnumber1 = _T("");
	m_postnumber2 = _T("");
	m_postnumber3 = _T("");
	m_postnumber4 = _T("");
	m_postnumber5 = _T("");
	m_volume1 = _T("");
	m_volume2 = _T("");
	m_volume3 = _T("");
	m_volume4 = _T("");
	m_volume5 = _T("");
	m_permission = 0;
	//}}AFX_DATA_INIT
}


void CDialog_Unpost::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Unpost)
	DDX_Control(pDX, IDC_COMBO_DEPARTMENT, m_department);
	DDX_Text(pDX, IDC_EDIT_POST_ID1, m_postid1);
	DDX_Text(pDX, IDC_EDIT_POST_ID2, m_postid2);
	DDX_Text(pDX, IDC_EDIT_POST_ID3, m_postid3);
	DDX_Text(pDX, IDC_EDIT_POST_ID4, m_postid4);
	DDX_Text(pDX, IDC_EDIT_POST_ID5, m_postid5);
	DDX_Text(pDX, IDC_EDIT_POST_NUM1, m_postnumber1);
	DDX_Text(pDX, IDC_EDIT_POST_NUM2, m_postnumber2);
	DDX_Text(pDX, IDC_EDIT_POST_NUM3, m_postnumber3);
	DDX_Text(pDX, IDC_EDIT_POST_NUM4, m_postnumber4);
	DDX_Text(pDX, IDC_EDIT_POST_NUM5, m_postnumber5);
	DDX_Text(pDX, IDC_EDIT_VOLUME_SENDID, m_volume1);
	DDX_Text(pDX, IDC_EDIT_VOLUME_SENDID2, m_volume2);
	DDX_Text(pDX, IDC_EDIT_VOLUME_SENDID3, m_volume3);
	DDX_Text(pDX, IDC_EDIT_VOLUME_SENDID4, m_volume4);
	DDX_Text(pDX, IDC_EDIT_VOLUME_SENDID5, m_volume5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Unpost, CDialog)
	//{{AFX_MSG_MAP(CDialog_Unpost)
	ON_BN_CLICKED(IDC_BUTTON_POST, OnUnPost)
	ON_CBN_SELCHANGE(IDC_COMBO_DEPARTMENT, OnSelchangeDepartment)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Unpost message handlers

BOOL CDialog_Unpost::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDialog_Unpost::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_department.InsertString(0,"技术部");
	m_department.InsertString(1,"生产部");
	m_department.InsertString(2,"质检");
	m_department.InsertString(3,"成品仓");
	m_department.InsertString(4,"物流");
	m_department.SetCurSel(0);
	m_permission = REFUND;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_Unpost::OnUnPost() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CDialog_Unpost::OnSelchangeDepartment() 
{
	int indexSel = m_department.GetCurSel();
	return;
	switch(indexSel)
	{
	case 0://技术部
		GetDlgItem(IDC_STATIC1)->SetWindowText("总体积:");
		GetDlgItem(IDC_STATIC2)->SetWindowText("总体积:");
		GetDlgItem(IDC_STATIC3)->SetWindowText("总体积:");
		GetDlgItem(IDC_STATIC4)->SetWindowText("总体积:");
		GetDlgItem(IDC_STATIC5)->SetWindowText("总体积:");
		GetDlgItem(IDC_STATIC1)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC3)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC4)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC5)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID2)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID3)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID4)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID5)->ShowWindow(TRUE);
		//m_permission = POST_TC;
		break;
	case 1://生产部
		GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC3)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC4)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC5)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID3)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID4)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID5)->ShowWindow(FALSE);
		//m_permission = POST_PD;
		break;
	case 2://质检
		GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC3)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC4)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC5)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID3)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID4)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID5)->ShowWindow(FALSE);
		//m_permission = QC;
		break;
	case 3://成品仓
		GetDlgItem(IDC_STATIC1)->SetWindowText("快递单号:");
		GetDlgItem(IDC_STATIC2)->SetWindowText("快递单号:");
		GetDlgItem(IDC_STATIC3)->SetWindowText("快递单号:");
		GetDlgItem(IDC_STATIC4)->SetWindowText("快递单号:");
		GetDlgItem(IDC_STATIC5)->SetWindowText("快递单号:");
		GetDlgItem(IDC_STATIC1)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC3)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC4)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC5)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID2)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID3)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID4)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID5)->ShowWindow(TRUE);
		//m_permission = POST_STORAGE;
		break;
	case 4://物流
		GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC3)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC4)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC5)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID3)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID4)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID5)->ShowWindow(FALSE);
		//m_permission = POST_SEND;
		break;
	default:
		break;
	}		
}

void CDialog_Unpost::OnOK() 
{
	// TODO: Add extra validation here
	
	UpdateData();

	CString strdepartment;
	m_department.GetWindowText(strdepartment);

	CDialog_Login2 login2;
	login2.m_department = strdepartment;
	login2.m_permission = m_permission;
	if (login2.DoModal()!=IDOK)
	{
		return;
	}

	CString postid[5];
	int postnumber[5];
	CString volume_sendid[5];
	int enable[5] ; 
	int i=0;
	postid[0] = m_postid1;
	postid[1] = m_postid2;
	postid[2] = m_postid3;
	postid[3] = m_postid4;
	postid[4] = m_postid5;
	volume_sendid[0] = m_volume1;
	volume_sendid[1] = m_volume2;
	volume_sendid[2] = m_volume3;
	volume_sendid[3] = m_volume4;
	volume_sendid[4] = m_volume5;
	postnumber[0] = atoi(m_postnumber1);
	postnumber[1] = atoi(m_postnumber2);
	postnumber[2] = atoi(m_postnumber3);
	postnumber[3] = atoi(m_postnumber4);
	postnumber[4] = atoi(m_postnumber5);
	for(i=0;i<5;i++)
		enable[i] = 1;
	for(i=0;i<5;i++)
	{
		if(postid[i].IsEmpty())
			enable[i] = 0;
	}

	if((enable[0]==0) && (enable[1]==0) && (enable[2]==0) && (enable[3]==0) && (enable[4]==0))
	{
		MessageBox("没有订单号，请重新输入","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1))->SetSel(0, -1);
		return;
	}

	if((enable[0]==1) && (postnumber[0]==0))
	{
		MessageBox("退账数量不正确，请重新输入","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1))->SetSel(0, -1);
		return;
	}
	if((enable[1]==1) && (postnumber[1]==0))
	{
		MessageBox("退账数量不正确，请重新输入","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM2)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM2))->SetSel(0, -1);
		return;
	}
	if((enable[2]==1) && (postnumber[2]==0))
	{
		MessageBox("退账数量不正确，请重新输入","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM3)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM3))->SetSel(0, -1);
		return;
	}
	if((enable[3]==1) && (postnumber[3]==0))
	{
		MessageBox("退账数量不正确，请重新输入","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM4)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM4))->SetSel(0, -1);
		return;
	}
	if((enable[4]==1) && (postnumber[4]==0))
	{
		MessageBox("退账数量不正确，请重新输入","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM5)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM5))->SetSel(0, -1);
		return;
	}
		

	CString sql[5];
	for(i=0;i<5;i++)
		sql[i].Format("select * from schedule where listid=\"%s\" ",postid[i]);

	
	int totelnumber[5],businessnumber[5],tcnumber[5],pdnumber[5],qcnumber[5],storagenumber[5],sendnumber[5],post[5],end[5],hasstoragenumber[5];
	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	mysql_init(&myCont);
	if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
	{
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
		for(i=0;i<5;i++)
		{
			if(enable[i]==1)
			{
				if(mysql_query(&myCont,sql[i])!= 0)
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
						MessageBox("无此订单号（可能还没下单），请重新输入","提示",MB_OK);
						switch (i)
						{
						case 0:
							(CEdit*)GetDlgItem(IDC_EDIT_POST_ID1)->SetFocus();
							((CEdit*)GetDlgItem(IDC_EDIT_POST_ID1))->SetSel(0, -1);
							goto _exit;
							break;
						case 1:
							(CEdit*)GetDlgItem(IDC_EDIT_POST_ID2)->SetFocus();
							((CEdit*)GetDlgItem(IDC_EDIT_POST_ID2))->SetSel(0, -1);
							goto _exit;
							break;
						case 2:
							(CEdit*)GetDlgItem(IDC_EDIT_POST_ID3)->SetFocus();
							((CEdit*)GetDlgItem(IDC_EDIT_POST_ID3))->SetSel(0, -1);
							goto _exit;
							break;
						case 3:
							(CEdit*)GetDlgItem(IDC_EDIT_POST_ID4)->SetFocus();
							((CEdit*)GetDlgItem(IDC_EDIT_POST_ID4))->SetSel(0, -1);
							goto _exit;
							break;
						case 4:
							(CEdit*)GetDlgItem(IDC_EDIT_POST_ID5)->SetFocus();
							((CEdit*)GetDlgItem(IDC_EDIT_POST_ID5))->SetSel(0, -1);
							goto _exit;
							break;
						default:
							;
							
						}
						
					}
					totelnumber[i]		= atoi(sql_row[2]);
					businessnumber[i]	= atoi(sql_row[3]);
					tcnumber[i]			= atoi(sql_row[4]);
					pdnumber[i]			= atoi(sql_row[5]);
					qcnumber[i]			= atoi(sql_row[6]);
					storagenumber[i]	= atoi(sql_row[7]);
					sendnumber[i]		= atoi(sql_row[8]);
					post[i]				= atoi(sql_row[9]);
					end[i]				= atoi(sql_row[10]);
					hasstoragenumber[i]	= atoi(sql_row[11]);
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
			}//if(enable[i]==1)
		}//for(i=0;i<5;i++)
		
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
			currenttime = sql_row[0];
		}

		
		int indexSel = m_department.GetCurSel();
		switch(indexSel)
		{
		case 0://技术部
			for(i=0;i<5;i++)
			{
				if(enable[i]==1)
				{
					if( (postnumber[i]>tcnumber[i]) || (postnumber[i]>totelnumber[i]))
					{
						MessageBox("退账数量不正确，请重新输入","提示",MB_OK);
						(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1))->SetSel(0, -1);
						goto _exit;
					}
				/*	sql[i].Format("update schedule set tcnumber=%d  where listid=\"%s\" ",tcnumber[i]-postnumber[i],postid[i]);
					if(mysql_query(&myCont,sql[i])!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						mysql_close(&myCont);//断开连接
						return;
					}
					*/

	/*				sql[i].Format("update scheduledetail set tcendtime=\"%s\",tcnumber=%d,tcpeople=\"%s\",pdstarttme=\"%s\" where listid=\"%s\" ",currenttime,postnumber[i],login2.m_user,currenttime,postid[i]);
					if(mysql_query(&myCont,sql[i])!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						mysql_close(&myCont);//断开连接
						return;
					}

					sql[i].Format("update baseinfo set volume=\"%s\"  where listid=\"%s\" ",volume_sendid[i],postid[i]);
					if(mysql_query(&myCont,sql[i])!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						mysql_close(&myCont);//断开连接
						return;
					}
	*/
				}
			}
			break;
		case 1://生产部
			for(i=0;i<5;i++)
			{
				if(enable[i]==1)
				{
					if( (postnumber[i]>pdnumber[i]) || (postnumber[i]>totelnumber[i]))
					{
						MessageBox("退账数量不正确，请重新输入","提示",MB_OK);
						(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1))->SetSel(0, -1);
						goto _exit;
					}
					sql[i].Format("update schedule set pdnumber=%d,tcnumber=%d  where listid=\"%s\" ",pdnumber[i]-postnumber[i],tcnumber[i]+postnumber[i],postid[i]);
					if(mysql_query(&myCont,sql[i])!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						mysql_close(&myCont);//断开连接
						return;
					}

/*					sql[i].Format("update scheduledetail set pdendtime=\"%s\",pdnumber=%d,pdpeople=\"%s\",qcstarttime=\"%s\" where listid=\"%s\" ",currenttime,postnumber[i],login2.m_user,currenttime,postid[i]);
					if(mysql_query(&myCont,sql[i])!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						mysql_close(&myCont);//断开连接
						return;
					}
*/
				}
			}
			break;
		case 2://质检
			for(i=0;i<5;i++)
			{
				if(enable[i]==1)
				{
					if( (postnumber[i]>qcnumber[i]) || (postnumber[i]>totelnumber[i]))
					{
						MessageBox("退账数量不正确，请重新输入","提示",MB_OK);
						(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1))->SetSel(0, -1);
						goto _exit;
					}
					sql[i].Format("update schedule set qcnumber=%d,pdnumber=%d  where listid=\"%s\" ",qcnumber[i]-postnumber[i],pdnumber[i]+postnumber[i],postid[i]);
					if(mysql_query(&myCont,sql[i])!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						mysql_close(&myCont);//断开连接
						return;
					}
/*
					sql[i].Format("update scheduledetail set qcendtime=\"%s\",qcnumber=%d,qcpeople=\"%s\",storagestarttime=\"%s\" where listid=\"%s\" ",currenttime,postnumber[i],login2.m_user,currenttime,postid[i]);
					if(mysql_query(&myCont,sql[i])!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						mysql_close(&myCont);//断开连接
						return;
					}

					sql[i].Format("update baseinfo set sendid=\"%s\"  where listid=\"%s\" ",volume_sendid[i],postid[i]);
					if(mysql_query(&myCont,sql[i])!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						mysql_close(&myCont);//断开连接
						return;
					}
*/
				}
			}
			break;
		case 3://成品仓
			for(i=0;i<5;i++)
			{
				if(enable[i]==1)
				{
					if( (postnumber[i]>storagenumber[i]) || (postnumber[i]>totelnumber[i]))
					{
						MessageBox("退账数量不正确，请重新输入","提示",MB_OK);
						(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1))->SetSel(0, -1);
						goto _exit;
					}
					sql[i].Format("update schedule set storagenumber=%d,qcnumber=%d  where listid=\"%s\" ",storagenumber[i]-postnumber[i],qcnumber[i]+postnumber[i], postid[i]);
					if(mysql_query(&myCont,sql[i])!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						mysql_close(&myCont);//断开连接
						return;
					}
/*
					sql[i].Format("update scheduledetail set storageendtime=\"%s\",storagenumber=%d,storagepopple=\"%s\",sendstarttime=\"%s\" where listid=\"%s\" ",currenttime,postnumber[i],login2.m_user,currenttime,postid[i]);
					if(mysql_query(&myCont,sql[i])!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						mysql_close(&myCont);//断开连接
						return;
					}

					sql[i].Format("update baseinfo set sendid=\"%s\"  where listid=\"%s\" ",volume_sendid[i],postid[i]);
					if(mysql_query(&myCont,sql[i])!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						mysql_close(&myCont);//断开连接
						return;
					}
*/
				}
			}
			break;
		case 4://物流
			for(i=0;i<5;i++)
			{
				if(enable[i]==1)
				{
					if( (postnumber[i]>sendnumber[i]) || (postnumber[i]>totelnumber[i]))
					{
						MessageBox("退账数量不正确，请重新输入","提示",MB_OK);
						(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1))->SetSel(0, -1);
						goto _exit;
					}
					sql[i].Format("update schedule set sendnumber=%d,storagenumber=%d,hasstoragenumber=%d where listid=\"%s\" ",sendnumber[i]-postnumber[i],storagenumber[i]+postnumber[i],hasstoragenumber[i]-postnumber[i],postid[i]);
					if(mysql_query(&myCont,sql[i])!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						mysql_close(&myCont);//断开连接
						return;
					}
/*
					sql[i].Format("update scheduledetail set sendendtime=\"%s\",sendnumber=%d,sendpeople=\"%s\"  where listid=\"%s\" ",currenttime,postnumber[i],login2.m_user,postid[i]);
					if(mysql_query(&myCont,sql[i])!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						mysql_close(&myCont);//断开连接
						return;
					}
*/
				}
			}
			break;
		default:
			;
		}	
	}
	else
		goto _exit;
	MessageBox("退账成功","提示",MB_OK);
_exit:
	if(result!=NULL) mysql_free_result(result);//释放结果资源
	mysql_close(&myCont);//断开连接
}
