// Dialog_post.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_post.h"
#include "Dialog_Login2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog_post dialog


CDialog_post::CDialog_post(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_post::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_post)
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
	m_designer1 = _T("");
	m_designer2 = _T("");
	m_designer3 = _T("");
	m_designer4 = _T("");
	m_designer5 = _T("");
	m_score1 = _T("");
	m_score2 = _T("");
	m_score3 = _T("");
	m_score4 = _T("");
	m_score5 = _T("");
	//}}AFX_DATA_INIT
}


void CDialog_post::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_post)
	DDX_Control(pDX, IDC_BUTTON2, m_btn2);
	DDX_Control(pDX, IDC_BUTTON_POST, m_btnpost);
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
	DDX_Text(pDX, IDC_EDIT_DESIGNER1, m_designer1);
	DDX_Text(pDX, IDC_EDIT_DESIGNER2, m_designer2);
	DDX_Text(pDX, IDC_EDIT_DESIGNER3, m_designer3);
	DDX_Text(pDX, IDC_EDIT_DESIGNER4, m_designer4);
	DDX_Text(pDX, IDC_EDIT_DESIGNER5, m_designer5);
	DDX_Text(pDX, IDC_EDIT_SCORE1, m_score1);
	DDX_Text(pDX, IDC_EDIT_SCORE2, m_score2);
	DDX_Text(pDX, IDC_EDIT_SCORE3, m_score3);
	DDX_Text(pDX, IDC_EDIT_SCORE4, m_score4);
	DDX_Text(pDX, IDC_EDIT_SCORE5, m_score5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_post, CDialog)
	//{{AFX_MSG_MAP(CDialog_post)
	ON_BN_CLICKED(IDC_BUTTON_POST, OnPost)
	ON_CBN_SELCHANGE(IDC_COMBO_DEPARTMENT, OnSelchangeDepartment)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_post message handlers


BOOL CDialog_post::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_department.InsertString(0,"技术部");
	m_department.InsertString(1,"生产部");
	m_department.InsertString(2,"质检");
	m_department.InsertString(3,"成品仓");
	m_department.InsertString(4,"物流");

	CString strdepartment = g_department;
	if((strdepartment.Compare("技术部")==0) || 
		(strdepartment.Compare("意造销售")==0) ||
		(strdepartment.Compare("电商")==0) ||
		(strdepartment.Compare("运营")==0) ||
		(strdepartment.Compare("加盟")==0) ||
		(strdepartment.Compare("研发")==0) )
		m_department.SetCurSel(0);
	else if(strdepartment.Compare("生产部")==0)
		m_department.SetCurSel(1);
	else if(strdepartment.Compare("质检")==0)
		m_department.SetCurSel(2);
	else if(strdepartment.Compare("成品仓")==0)
		m_department.SetCurSel(3);
	else if(strdepartment.Compare("物流")==0)
		m_department.SetCurSel(4);
	m_permission = POST_TC;
	OnSelchangeDepartment();
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDialog_post::OnOK() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	CString strdepartment;
	m_department.GetWindowText(strdepartment);

	CString postid[5];
	int postnumber[5];
	CString volume_sendid[5];
	CString designer[5];
	int score[5];
	int enable[5] ;
	int i=0;
	postid[0] = m_postid1;
	postid[1] = m_postid2;
	postid[2] = m_postid3;
	postid[3] = m_postid4;
	postid[4] = m_postid5;

	for(i=0;i<5;i++)
		enable[i] = 1;
	for(i=0;i<5;i++)
	{
		if(postid[i].IsEmpty())
			enable[i] = 0;
	}

	int indexSel = m_department.GetCurSel();
	if((enable[0]==0) && (enable[1]==0) && (enable[2]==0) && (enable[3]==0) && (enable[4]==0))
	{
		MessageBox("没有订单号，请重新输入","提示",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1))->SetSel(0, -1);
		return;
	}

	if((enable[0]==1))
	{
		if(!(m_postnumber1.IsEmpty()))
		{
			if(!IsInt(m_postnumber1))
			{
				MessageBox("过账数量输入必须为整数，请重新输入","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1))->SetSel(0, -1);
				return;
			}
		}
		if(atoi(m_postnumber1)<=0)
		{
			MessageBox("过账数量不正确，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1))->SetSel(0, -1);
			return;
		}
		if (indexSel==0)
		{
			if(!(m_volume1.IsEmpty()))
			{
				if(!IsNum(m_volume1))
				{
					MessageBox("体积输入必须为数字，请重新输入","提示",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID))->SetSel(0, -1);
					return;
				}
			}
			if(atof(m_volume1)<=0)
			{
				MessageBox("体积输入不正确，请重新输入","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID))->SetSel(0, -1);
				return;
			}
			if(!(m_score1.IsEmpty()))
			{
				if(!IsInt(m_score1))
				{
					MessageBox("积分输入必须为整数，请重新输入","提示",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_SCORE1)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_SCORE1))->SetSel(0, -1);
					return;
				}
			}
		}
	}
	if((enable[1]==1))
	{
		if(!(m_postnumber2.IsEmpty()))
		{
			if(!IsInt(m_postnumber2))
			{
				MessageBox("过账数量输入必须为整数，请重新输入","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM2)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM2))->SetSel(0, -1);
				return;
			}
		}
		if(atoi(m_postnumber2)<=0)
		{
			MessageBox("过账数量不正确，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM2)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM2))->SetSel(0, -1);
			return;
		}
		if (indexSel==0)
		{
			if(!(m_volume2.IsEmpty()))
			{
				if(!IsNum(m_volume2))
				{
					MessageBox("体积输入必须为数字，请重新输入","提示",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID2)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID2))->SetSel(0, -1);
					return;
				}
			}
			if(atof(m_volume2)<=0)
			{
				MessageBox("体积输入不正确，请重新输入","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID2)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID2))->SetSel(0, -1);
				return;
			}
			if(!(m_score2.IsEmpty()))
			{
				if(!IsInt(m_score2))
				{
					MessageBox("积分输入必须为整数，请重新输入","提示",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_SCORE2)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_SCORE2))->SetSel(0, -1);
					return;
				}
			}
		}
	}
	if((enable[2]==1))
	{
		if(!(m_postnumber3.IsEmpty()))
		{
			if(!IsInt(m_postnumber3))
			{
				MessageBox("过账数量输入必须为整数，请重新输入","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM3)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM3))->SetSel(0, -1);
				return;
			}
		}
		if(atoi(m_postnumber3)<=0)
		{
			MessageBox("过账数量不正确，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM3)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM3))->SetSel(0, -1);
			return;
		}
		if (indexSel==0)
		{
			if(!(m_volume3.IsEmpty()))
			{
				if(!IsNum(m_volume3))
				{
					MessageBox("体积输入必须为数字，请重新输入","提示",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID3)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID3))->SetSel(0, -1);
					return;
				}
			}
			if(atof(m_volume3)<=0)
			{
				MessageBox("体积输入不正确，请重新输入","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID3)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID3))->SetSel(0, -1);
				return;
			}
			if(!(m_score3.IsEmpty()))
			{
				if(!IsInt(m_score3))
				{
					MessageBox("积分输入必须为整数，请重新输入","提示",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_SCORE3)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_SCORE3))->SetSel(0, -1);
					return;
				}
			}
		}
	}
	if((enable[3]==1))
	{
		if(!(m_postnumber4.IsEmpty()))
		{
			if(!IsInt(m_postnumber4))
			{
				MessageBox("过账数量输入必须为整数，请重新输入","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM4)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM4))->SetSel(0, -1);
				return;
			}
		}
		if(atoi(m_postnumber4)<=0)
		{
			MessageBox("过账数量不正确，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM4)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM4))->SetSel(0, -1);
			return;
		}
		if (indexSel==0)
		{
			if(!(m_volume4.IsEmpty()))
			{
				if(!IsNum(m_volume4))
				{
					MessageBox("体积输入必须为数字，请重新输入","提示",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID4)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID4))->SetSel(0, -1);
					return;
				}
			}
			if(atof(m_volume4)<=0)
			{
				MessageBox("体积输入不正确，请重新输入","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID4)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID4))->SetSel(0, -1);
				return;
			}
			if(!(m_score4.IsEmpty()))
			{
				if(!IsInt(m_score4))
				{
					MessageBox("积分输入必须为整数，请重新输入","提示",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_SCORE4)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_SCORE4))->SetSel(0, -1);
					return;
				}
			}
		}
	}
	if((enable[4]==1))
	{
		if(!(m_postnumber5.IsEmpty()))
		{
			if(!IsInt(m_postnumber5))
			{
				MessageBox("过账数量输入必须为整数，请重新输入","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM5)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM5))->SetSel(0, -1);
				return;
			}
		}
		if(atoi(m_postnumber5)<=0)
		{
			MessageBox("过账数量不正确，请重新输入","提示",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM5)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM5))->SetSel(0, -1);
			return;
		}
		if (indexSel==0)
		{
			if(!(m_volume5.IsEmpty()))
			{
				if(!IsNum(m_volume5))
				{
					MessageBox("体积输入必须为数字，请重新输入","提示",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID5)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID5))->SetSel(0, -1);
					return;
				}
			}
			if(atof(m_volume5)<=0)
			{
				MessageBox("体积输入不正确，请重新输入","提示",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID5)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_VOLUME_SENDID5))->SetSel(0, -1);
				return;
			}
			if(!(m_score5.IsEmpty()))
			{
				if(!IsInt(m_score5))
				{
					MessageBox("积分输入必须为整数，请重新输入","提示",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_SCORE5)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_SCORE5))->SetSel(0, -1);
					return;
				}
			}
		}
	}

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
	designer[0] = m_designer1;
	designer[1] = m_designer2;
	designer[2] = m_designer3;
	designer[3] = m_designer4;
	designer[4] = m_designer5;
	score[0] = atoi(m_score1);
	score[1] = atoi(m_score2);
	score[2] = atoi(m_score3);
	score[3] = atoi(m_score4);
	score[4] = atoi(m_score5);

	CDialog_Login2 login2;
	login2.m_department = strdepartment;
	login2.m_permission = m_permission;
	if (login2.DoModal()!=IDOK)
	{
		return;
	}

	CString sql[5];
	for(i=0;i<5;i++)
		sql[i].Format("select * from schedule where listid=\"%s\" ",postid[i]);

	
	int totelnumber[5],businessnumber[5],tcnumber[5],pdnumber[5],qcnumber[5],storagenumber[5],sendnumber[5],post[5],end[5],hasstoragenumber[5],undolist[5];
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
					undolist[i]			= atoi(sql_row[12]);
					if(undolist[i]==1)
					{
						CString str;
						str.Format("订单 %s 已被销单，请续单后过账",postid[i]);
						MessageBox(str,"提示",MB_OK);
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
							break;							
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
			for(i=0;i<5;i++)
			{
				if(enable[i]==1)
				{
					if( (postnumber[i]>tcnumber[i]) || (postnumber[i]>totelnumber[i]))
					{
						MessageBox("过账数量不正确，请重新输入","提示",MB_OK);
						(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1))->SetSel(0, -1);
						goto _exit;
					}
					sql[i].Format("update schedule set tcnumber=%d,pdnumber=%d  where listid=\"%s\" ",tcnumber[i]-postnumber[i],pdnumber[i]+postnumber[i],postid[i]);
					if(mysql_query(&myCont,sql[i])!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						mysql_close(&myCont);//断开连接
						return;
					}

					sql[i].Format("update scheduledetail set tcendtime=\"%s\",tcnumber=%d,tcpeople=\"%s\",pdstarttme=\"%s\" where listid=\"%s\" ",currenttime,postnumber[i],login2.m_user,currenttime,postid[i]);
					if(mysql_query(&myCont,sql[i])!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						mysql_close(&myCont);//断开连接
						return;
					}

					sql[i].Format("update baseinfo set volume=\"%s\",desinger=\"%s\",score=%d  where listid=\"%s\" ",volume_sendid[i],designer[i],score[i],postid[i]);
					if(mysql_query(&myCont,sql[i])!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						mysql_close(&myCont);//断开连接
						return;
					}
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
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1))->SetSel(0, -1);
						goto _exit;
					}
					sql[i].Format("update schedule set pdnumber=%d,qcnumber=%d  where listid=\"%s\" ",pdnumber[i]-postnumber[i],qcnumber[i]+postnumber[i],postid[i]);
					if(mysql_query(&myCont,sql[i])!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						mysql_close(&myCont);//断开连接
						return;
					}

					sql[i].Format("update scheduledetail set pdendtime=\"%s\",pdnumber=%d,pdpeople=\"%s\",qcstarttime=\"%s\" where listid=\"%s\" ",currenttime,postnumber[i],login2.m_user,currenttime,postid[i]);
					if(mysql_query(&myCont,sql[i])!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						mysql_close(&myCont);//断开连接
						return;
					}

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
						MessageBox("过账数量不正确，请重新输入","提示",MB_OK);
						(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1))->SetSel(0, -1);
						goto _exit;
					}
					sql[i].Format("update schedule set qcnumber=%d,storagenumber=%d  where listid=\"%s\" ",qcnumber[i]-postnumber[i],storagenumber[i]+postnumber[i],postid[i]);
					if(mysql_query(&myCont,sql[i])!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						mysql_close(&myCont);//断开连接
						return;
					}

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

				/*	sql[i].Format("update baseinfo set sendid=\"%s\"  where listid=\"%s\" ",volume_sendid[i],postid[i]);
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
						MessageBox("过账数量不正确，请重新输入","提示",MB_OK);
						(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1))->SetSel(0, -1);
						goto _exit;
					}
					sql[i].Format("update schedule set storagenumber=%d,sendnumber=%d,hasstoragenumber=%d  where listid=\"%s\" ",storagenumber[i]-postnumber[i],sendnumber[i]+postnumber[i],hasstoragenumber[i]+postnumber[i] , postid[i]);
					if(mysql_query(&myCont,sql[i])!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						mysql_close(&myCont);//断开连接
						return;
					}

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
						MessageBox("过账数量不正确，请重新输入","提示",MB_OK);
						(CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1)->SetFocus();
						((CEdit*)GetDlgItem(IDC_EDIT_POST_NUM1))->SetSel(0, -1);
						goto _exit;
					}
					sql[i].Format("update schedule set sendnumber=%d,post=%d where listid=\"%s\" ",sendnumber[i]-postnumber[i],post[i]+postnumber[i],postid[i]);
					if(mysql_query(&myCont,sql[i])!= 0)
					{
						const char *error = mysql_error(&myCont);
						CString str;
						str.Format("数据库错误(%s)",error);
						MessageBox(str,"提示",MB_OK);
						mysql_close(&myCont);//断开连接
						return;
					}

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
				}
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
	//MessageBox("过账成功","提示",MB_OK);
_exit:
	if(result!=NULL) mysql_free_result(result);//释放结果资源
	mysql_close(&myCont);//断开连接
	//CDialog::OnOK();
}

BOOL CDialog_post::PreTranslateMessage(MSG* pMsg) 
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
  
void CDialog_post::OnPost() 
{
	// TODO: Add extra validation here
	OnOK();
}

void CDialog_post::OnSelchangeDepartment() 
{
	GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC3)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC4)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC5)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC6)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC7)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC8)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC9)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC10)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC11)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC12)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC13)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC14)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC15)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_VOLUME_SENDID)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_VOLUME_SENDID2)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_VOLUME_SENDID3)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_VOLUME_SENDID4)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_VOLUME_SENDID5)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_DESIGNER1)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_DESIGNER2)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_DESIGNER3)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_DESIGNER4)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_DESIGNER5)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_SCORE1)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_SCORE2)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_SCORE3)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_SCORE4)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_SCORE5)->ShowWindow(FALSE);
	int indexSel = m_department.GetCurSel();
	switch(indexSel)
	{
	case 0://技术部
		GetDlgItem(IDC_STATIC1)->SetWindowText("总体积（cm3）:");
		GetDlgItem(IDC_STATIC2)->SetWindowText("总体积（cm3）:");
		GetDlgItem(IDC_STATIC3)->SetWindowText("总体积（cm3）:");
		GetDlgItem(IDC_STATIC4)->SetWindowText("总体积（cm3）:");
		GetDlgItem(IDC_STATIC5)->SetWindowText("总体积（cm3）:");
		GetDlgItem(IDC_STATIC1)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC3)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC4)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC5)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC6)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC7)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC8)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC9)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC10)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC11)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC12)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC13)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC14)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC15)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID2)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID3)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID4)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VOLUME_SENDID5)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_DESIGNER1)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_DESIGNER2)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_DESIGNER3)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_DESIGNER4)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_DESIGNER5)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_SCORE1)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_SCORE2)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_SCORE3)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_SCORE4)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_SCORE5)->ShowWindow(TRUE);

		m_permission = POST_TC;
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
		m_permission = POST_PD;
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
		m_permission = QC;
		break;
	case 3://成品仓
		GetDlgItem(IDC_STATIC1)->SetWindowText("快递公司及单号:");
		GetDlgItem(IDC_STATIC2)->SetWindowText("快递公司及单号:");
		GetDlgItem(IDC_STATIC3)->SetWindowText("快递公司及单号:");
		GetDlgItem(IDC_STATIC4)->SetWindowText("快递公司及单号:");
		GetDlgItem(IDC_STATIC5)->SetWindowText("快递公司及单号:");
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
		m_permission = POST_STORAGE;
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
		m_permission = POST_SEND;
		break;
	default:
		break;
	}	
}
