// Dialog_SendUserAdd.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_SendUserAdd.h"
#include "Dialog_progress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_SendUserAdd dialog


Dialog_SendUserAdd::Dialog_SendUserAdd(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_SendUserAdd::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_SendUserAdd)
	m_strUserName = _T("");
	m_strPhone = _T("");
	action  = 0;
	//}}AFX_DATA_INIT
}


void Dialog_SendUserAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_SendUserAdd)
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_xpCancel);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_strPhone);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_SendUserAdd, CDialog)
	//{{AFX_MSG_MAP(Dialog_SendUserAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_SendUserAdd message handlers

BOOL Dialog_SendUserAdd::PreTranslateMessage(MSG* pMsg) 
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

BOOL Dialog_SendUserAdd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(action == 0)
	{
		SetWindowText("����");
	}
	else
		if (action == 1)
		{
			SetWindowText("�޸�");
		}
		else
			if(action == 2)
			{
				SetWindowText("ɾ��");
				((CWnd*)GetDlgItem(IDC_STATIC_PHONE))->ShowWindow(FALSE);
				((CWnd*)GetDlgItem(IDC_EDIT_PHONE))->ShowWindow(FALSE);
			}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_SendUserAdd::OnOK() 
{
	UpdateData();
	m_strUserName.TrimLeft();
	m_strUserName.TrimRight();
	if(m_strUserName.IsEmpty())
	{
		MessageBox("�������û�����","��ʾ",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_USERNAME)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_USERNAME))->SetSel(0, -1);
			return;	
	}
	if(action==0 || action ==1)
	{
		if(m_strPhone.IsEmpty())
		{
			MessageBox("������绰���룺","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_PHONE)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_PHONE))->SetSel(0, -1);
			return;	
		}
	}
	if(!(m_strPhone.IsEmpty()))
	{
		if(!IsPhoneNum(m_strPhone))
		{
			MessageBox("��ϵ�绰�������Ϊ���֣�����������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_PHONE)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_PHONE))->SetSel(0, -1);
			return;	
		}
		int len = m_strPhone.GetLength();
		if(len!=11 && len!=12 && len!=15 && len!=16 && len!=17)
		{
			MessageBox("��ϵ�绰�����ʽ����ȷ������������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_PHONE)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_PHONE))->SetSel(0, -1);
			return;	
		}
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
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	mysql_init(&myCont);
	if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
	{
		if(action ==0 || action ==1)
		{
			dlgpro->setpos(500);
			mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
			sql = "select * from senduserinfo where username='" + m_strUserName +"'";
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
					dlgpro->setpos(800);
					sql.Format("update senduserinfo set phone=\"%s\"  where username=\"%s\" ",m_strPhone,m_strUserName);
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
					MessageBox("�޸��û���¼�ɹ�.","��ʾ",MB_OK);
				}
				else
				{//������¼
					dlgpro->setpos(800);
					sql.Format("insert into senduserinfo values (\"%s\",\"%s\") ",m_strUserName,m_strPhone);
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
					MessageBox("�����û���¼�ɹ�.","��ʾ",MB_OK);
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
			dlgpro->setpos(980);
		}
		else
			if(action==2)
			{
				dlgpro->setpos(800);
				sql.Format("delete from senduserinfo where username=\"%s\" ",m_strUserName);
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
				MessageBox("ɾ���û���¼�ɹ�.","��ʾ",MB_OK);
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
	mysql_close(&myCont);//�Ͽ�����
	dlgpro->endpos();
	CDialog::OnOK();
}
