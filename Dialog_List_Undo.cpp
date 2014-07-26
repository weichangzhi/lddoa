// Dialog_List_Undo.cpp : implementation file
//

#include "stdafx.h"
#include "goodsmanagesystem.h"
#include "Dialog_List_Undo.h"
#include "Dialog_progress.h"
#include "Dialog_Login2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog_List_Undo dialog


Dialog_List_Undo::Dialog_List_Undo(CWnd* pParent /*=NULL*/)
	: CDialog(Dialog_List_Undo::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog_List_Undo)
	m_strcost = _T("");
	m_listid = _T("");
	m_payment = _T("");
	m_strreason = _T("");
	m_strdepartment = _T("");
	m_strtime = _T("");
	//}}AFX_DATA_INIT
}


void Dialog_List_Undo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog_List_Undo)
	DDX_Control(pDX, IDOK, m_btok);
	DDX_Control(pDX, IDCANCEL, m_btcancel);
	DDX_Text(pDX, IDC_EDIT_COST, m_strcost);
	DDX_Text(pDX, IDC_EDIT_LISTID, m_listid);
	DDX_Text(pDX, IDC_EDIT_PAYMENT, m_payment);
	DDX_Text(pDX, IDC_EDIT_REASON, m_strreason);
	DDX_Text(pDX, IDC_EDIT_DEPARTMENT, m_strdepartment);
	DDX_Text(pDX, IDC_EDIT_TIME, m_strtime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog_List_Undo, CDialog)
	//{{AFX_MSG_MAP(Dialog_List_Undo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog_List_Undo message handlers

BOOL Dialog_List_Undo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CenterWindow();
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
		CString curtime;
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
			return TRUE;
		}
		dlgpro->setpos(600);
		result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
		if(result)
		{
			sql_row=mysql_fetch_row(result);
			CString tmp = sql_row[0];
			m_strtime = tmp;
			curtime = tmp.Mid(0,10);
		}
		else
		{
			const char *error = mysql_error(&myCont);
			CString str;
			str.Format("���ݿ����(%s)",error);
			MessageBox(str,"��ʾ",MB_OK);
			mysql_close(&myCont);//�Ͽ�����
			dlgpro->endpos();
			return TRUE;
		}
		CString csSql;
		csSql.Format("select tcnumber,pdnumber,qcnumber,storagenumber from schedule where listid=\"%s\" " ,m_listid);

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
					if(atoi(sql_row[0])>0)
						m_strdepartment = "������";
					else if(atoi(sql_row[1])>0)
						m_strdepartment = "������";
					else if(atoi(sql_row[2])>0)
						m_strdepartment = "�ʼ�";
					else if(atoi(sql_row[3])>0)
						m_strdepartment = "��Ʒ��";
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
			return TRUE;
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
		return TRUE;
    }
    if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
    mysql_close(&myCont);//�Ͽ�����
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog_List_Undo::OnOK() 
{
	UpdateData();
	if(!(m_strcost.IsEmpty()))
	{
		if(!IsNum(m_strcost))
		{
			MessageBox("�ɱ��������Ϊ���֣�����������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_COST)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_COST))->SetSel(0, -1);
			return;	
		}
		if(atof(m_strcost)>10000000)
		{
			MessageBox("�ɱ���������һǧ������������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_COST)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_COST))->SetSel(0, -1);
			return;
		}
	}
	if(!(m_payment.IsEmpty()))
	{
		if(!IsNum(m_payment))
		{
			MessageBox("�Ѹ�����������Ϊ���֣�����������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_PAYMENT)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_PAYMENT))->SetSel(0, -1);
			return;	
		}
		if(atof(m_payment)>10000000)
		{
			MessageBox("�Ѹ���������һǧ������������","��ʾ",MB_OK);
			(CEdit*)GetDlgItem(IDC_EDIT_PAYMENT)->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_PAYMENT))->SetSel(0, -1);
			return;
		}
	}
	if(m_strreason.IsEmpty())
	{
		MessageBox("����ԭ����Ϊ�գ�������","��ʾ",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_REASON)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_REASON))->SetSel(0, -1);
		return;
	}
	int len = m_strreason.GetLength();
	if(len>=255)
	{
		MessageBox("����ԭ���ܳ���255���֣�����������","��ʾ",MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_REASON)->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_REASON))->SetSel(0, -1);
		return;
	}

	CDialog_Login2 login2;
	login2.m_permission = DEL_LIST;
	if (login2.DoModal()!=IDOK)
	{
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
	MYSQL_RES *result;
	//MYSQL_ROW sql_row;
	mysql_init(&myCont);
	if(mysql_real_connect(&myCont,g_MysqlConnect.host,g_MysqlConnect.user,g_MysqlConnect.pswd,g_MysqlConnect.table,g_MysqlConnect.port,NULL,0))
	{
		dlgpro->setpos(500);
		mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
		sql = "select * from undolist where listid='" + m_listid +"'";
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
				dlgpro->setpos(700);
				sql.Format("update undolist set reason=\"%s\",cost=\"%s\",payment=\"%s\",undotime=\"%s\",department=\"%s\" where listid=\"%s\" ",m_strreason,m_strcost,m_payment,m_strtime,m_strdepartment,m_listid);
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
				sql.Format("update schedule set undolist=%d where listid=\"%s\" ",1,m_listid);
				ret = mysql_query(&myCont,sql);
				dlgpro->setpos(900);
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
				if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
				mysql_close(&myCont);//�Ͽ�����
				dlgpro->endpos();
				MessageBox("�����ɹ�","��ʾ",MB_OK);
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
			dlgpro->endpos();
			return;
		}
		dlgpro->setpos(700);
		sql.Format("select * from schedule where listid=\"%s\" ",m_listid);
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
		result=mysql_store_result(&myCont);//�����ѯ�������ݵ�result
		if(result)
		{
			dlgpro->setpos(950);
			unsigned __int64 num = mysql_num_rows(result);//����
			if(num!=1)//
			{
				MessageBox("�޴˶�����δ�µ�","��ʾ",MB_OK);
				if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
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
		sql.Format("insert into undolist values (\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\")", m_listid,m_strreason,m_strcost,m_payment,m_strtime,m_strdepartment);
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
		dlgpro->setpos(900);
		sql.Format("update schedule set undolist=%d where listid=\"%s\" ",1,m_listid);
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
	if(result!=NULL) mysql_free_result(result);//�ͷŽ����Դ
	mysql_close(&myCont);//�Ͽ�����
	dlgpro->endpos();
	MessageBox("�����ɹ�","��ʾ",MB_OK);

	CDialog::OnOK();
}

BOOL Dialog_List_Undo::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
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
