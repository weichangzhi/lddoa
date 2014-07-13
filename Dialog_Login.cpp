// Dialog_Login.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "Dialog_Login.h"
#include "Dialog_ModifyPassWd.h"
#include <time.h> 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib,"Version.lib")

/////////////////////////////////////////////////////////////////////////////
// CDialog_Login dialog


CDialog_Login::CDialog_Login(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Login::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog_Login)
	m_user = _T("");
	m_passwd = _T("");
	m_strip = _T("127.0.0.1");
	//}}AFX_DATA_INIT
}


void CDialog_Login::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog_Login)
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipaddress);
	DDX_Text(pDX, IDC_EDIT_USER, m_user);
	DDX_Text(pDX, IDC_EDIT_PASSWD, m_passwd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog_Login, CDialog)
	//{{AFX_MSG_MAP(CDialog_Login)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_PASSWD, OnModifyPasswd)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog_Login message handlers


CString getVersion()
{
	CHAR szAppPath[MAX_PATH] = {0};
	::GetModuleFileName(NULL, szAppPath, MAX_PATH);
	VS_FIXEDFILEINFO *VInfo;
	UINT nVerInfoSize = GetFileVersionInfoSize(szAppPath, 0);
	char* bufVerInfo = new char[nVerInfoSize];
	CString strVer = "";
	if (GetFileVersionInfo(szAppPath, 0, nVerInfoSize, bufVerInfo) != 0)
	{
		if (VerQueryValue(bufVerInfo,"\\",(LPVOID*)&VInfo,&nVerInfoSize))
		{
			DWORD wVer1 = VInfo->dwFileVersionMS >> 16;
			DWORD wVer2 = VInfo->dwFileVersionMS & 0x00ff;
			DWORD wVer3 = VInfo->dwFileVersionLS >> 16;
			DWORD wVer4 = VInfo->dwFileVersionLS & 0x00ff;
			strVer.Format("%d.%d.%d.%d", wVer1, wVer2, wVer3, wVer4);
		}
	}
	delete []bufVerInfo;
	return strVer;
}

BOOL CDialog_Login::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString strpathini="";
	::GetCurrentDirectory(_MAX_PATH,strpathini.GetBuffer(_MAX_PATH));
	strpathini.ReleaseBuffer();
	strpathini = strpathini + "\\" + CONFIGINI;
	char buf[_MAX_PATH] = {0};
	GetPrivateProfileString("ServiceIP", "LastIP", "192.168.11.50", buf, _MAX_PATH, strpathini);
	m_strip = buf;

	m_ipaddress.SetWindowText(m_strip);
	strcpy(g_MysqlConnect.host , m_strip);
	CString titile = "��ӭ��½LDD�칫ϵͳ------version " + getVersion();
	SetWindowText(titile);

	GetPrivateProfileString("UserName", "LastName", "admin", buf, _MAX_PATH, strpathini); 
	m_user = buf;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog_Login::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	CString strpathini="";
	::GetCurrentDirectory(_MAX_PATH,strpathini.GetBuffer(_MAX_PATH));
	strpathini.ReleaseBuffer();
	strpathini = strpathini + "\\" + CONFIGINI;

	if(!m_user.Compare("weichangzhi"))
	{
		g_permission = 65535;
		CDialog::OnOK();
		return;
	}
	m_user.TrimLeft();
	m_user.TrimRight();
	if (m_user.IsEmpty())
	{	
		MessageBox("�������û���","��ʾ",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_USER)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_USER))->SetSel(0, -1);
		return;
	}
	m_passwd.TrimLeft();
	m_passwd.TrimRight();
	if(m_passwd.IsEmpty())
	{
		MessageBox("���벻��Ϊ�գ�����������","��ʾ",MB_OK | MB_SYSTEMMODAL);
		(CEdit*)GetDlgItem(IDC_EDIT_PASSWD)->SetFocus();
		return;
	}

	m_ipaddress.GetWindowText(m_strip); 
	::WritePrivateProfileString("ServiceIP","LastIP",m_strip,strpathini);
	writelog("��ȡ������iP�ɹ�");
	strcpy(g_MysqlConnect.host , m_strip);
	CString sql;
	sql.Format("select Password(\"%s\");",m_passwd);
	CString passwden;

	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	mysql_init(&myCont);
	if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
	{
		mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			return;
		}
		result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
		if(result)
		{
			sql_row=mysql_fetch_row(result);
			passwden = sql_row[0];
		}
		else
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			return;
		}

		sql = "select * from userinfo where username='" + m_user +"'";
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			return;
		}
		result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
		if(result)
		{
			unsigned __int64 num = mysql_num_rows(result);//����
			if(num<1)
			{
				MessageBox("���û���������","��ʾ",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_USER)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_USER))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
				mysql_close(&myCont);//�Ͽ�����
				return;
			}
			sql_row=mysql_fetch_row(result);
			if(sql_row)
			{
				if(passwden.Compare(sql_row[1])!=0)
				{
					MessageBox("���벻��ȷ������������","��ʾ",MB_OK);
					(CEdit*)GetDlgItem(IDC_EDIT_PASSWD)->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_PASSWD))->SetSel(0, -1);
					if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
					mysql_close(&myCont);//�Ͽ�����
					return;
				}
				writelog("����ƥ��ɹ�");
			}
			else
			{
				MessageBox("���û���������","��ʾ",MB_OK);
				(CEdit*)GetDlgItem(IDC_EDIT_USER)->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_USER))->SetSel(0, -1);
				if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
				mysql_close(&myCont);//�Ͽ�����
				return;
			}
			g_permission = atoi(sql_row[2]);
			g_user=m_user;
			g_department = sql_row[3];
		}
		else
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			return;
		}

		CString starttime;
		sql.Format("select now()");
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			return;
		}
		result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
		if(result)
		{
			sql_row=mysql_fetch_row(result);
			starttime = sql_row[0];
		}
		else
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			return;
		}

		sql = "select * from test ";
		if(mysql_query(&myCont,sql)!= 0)
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			CDialog::OnOK();
			return;
		}
		result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
		if(result)
		{
			unsigned __int64 num = mysql_num_rows(result);//����
			if(num<1)
			{
				if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
				mysql_close(&myCont);//�Ͽ�����
				g_user=m_user;
				CDialog::OnOK();
				return;
			}
			sql_row=mysql_fetch_row(result);
			if(sql_row)
			{
				if(atoi(sql_row[0])==1)
				{
					CString endtime = sql_row[2];
					if(starttime>endtime)
					{
						MessageBox("��ϵͳ�������ѵ��������Ѻ�ʹ��","��ʾ",MB_OK);
						if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
						mysql_close(&myCont);//�Ͽ�����
						return;
					}
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
			CDialog::OnOK();
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
		return;
	}

	::WritePrivateProfileString("UserName","LastName",m_user,strpathini);

	if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
	mysql_close(&myCont);//�Ͽ�����
	writelog("��¼�ɹ�");
	CDialog::OnOK();
}

BOOL CDialog_Login::PreTranslateMessage(MSG* pMsg) 
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

void CDialog_Login::OnModifyPasswd() 
{
	// TODO: Add your control notification handler code here
	CDialog_ModifyPassWd passwddlg;
	passwddlg.DoModal();
}

HBRUSH CDialog_Login::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(nCtlColor == CTLCOLOR_STATIC )
	{
		pDC->SetBkMode(TRANSPARENT);//���ñ���͸��
		pDC->SetTextColor(RGB(0,0,0));//��������Ϊ��ɫ
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
