// GoodsManageSystemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "GoodsManageSystemDlg.h"
#include "Winuser.h"
#include "Dialog_TipsSetting.h"
#include "Dialog_Tips.h"
#include "Dialog_FI_Proceeds.h"
#include "Dialog_FI_Detail.h"
#include "Dialog_FI_Check.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CXPButton	m_btnok;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDOK, m_btnok);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGoodsManageSystemDlg dialog

CGoodsManageSystemDlg::CGoodsManageSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGoodsManageSystemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGoodsManageSystemDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	writelog("CGoodsManageSystemDl���캯��");
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	bFirstin = 1;
	icurrentpage = 8;
	timertime = DEFAULT_TIME;
	m_hour = 14;
	m_min = 0;
	int i = 0;
	for(i=0;i<MAX_TREE_PAGE;i++)
	{
		m_treePages[i]=NULL;
	}
	writelog("CGoodsManageSystemDl���캯������");
}

void CGoodsManageSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGoodsManageSystemDlg)
	DDX_Control(pDX, IDC_TREE1, m_tree);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGoodsManageSystemDlg, CDialog)
	//{{AFX_MSG_MAP(CGoodsManageSystemDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_COMMAND(IDM_HELP, OnHelp)
	ON_COMMAND(IDM_CLIENT_ADD, OnClientAdd)
	ON_COMMAND(IDM_CLIENT_QUERY, OnClientQuery)
	ON_COMMAND(IDM_SELL_ADD, OnSellAdd)
	ON_COMMAND(IDM_SELL_QUERY, OnSellQuery)
	ON_COMMAND(IDM_BUY_ADD, OnBuyAdd)
	ON_COMMAND(IDM_BUY_QUERY, OnBuyQuery)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree)
	ON_COMMAND(ID_MENUITEM_TIPS, OnMenuitemTips)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGoodsManageSystemDlg message handlers

#define MAX_ICO 27
#define TIMERID_TIP      1100
#define TIMER_WAIT_TIP   1000*60 //1 min
BOOL CGoodsManageSystemDlg::OnInitDialog()
{
	writelog("OnInitDialog");
	CDialog::OnInitDialog();
	writelog("CGoodsManageSystemDlg::OnInitDialog ��ʾ������");
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	//EnableMenuItem(GetSubMenu(GetSkinMenu(*AfxGetApp()->m_pMainWnd), 0), 0, MF_BYPOSITION  | MF_GRAYED);
	this->ShowWindow(SW_SHOWMAXIMIZED);
	bFirstin = 1;
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	SetWindowText("LDD�칫ϵͳ");

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	CRect rectSc(0,0,width,height);
	//MoveWindow(&rectSc);
	//CRect recttab(0,20,width,height);
	//m_tab.MoveWindow(&recttab);

	//�ڵ��ͼ��	 
	int i=0;
	int i_count=MAX_ICO;
	//����ͼ��
	HICON icon[MAX_ICO];
	icon[0]=AfxGetApp()->LoadIcon (IDI_USER_ADD); 
	icon[1]=AfxGetApp()->LoadIcon (IDI_USER_MODIFY);
	icon[2]=AfxGetApp()->LoadIcon (IDI_LIST_ADD);
	icon[3]=AfxGetApp()->LoadIcon (IDI_MAKEING);
	icon[4]=AfxGetApp()->LoadIcon (IDI_LIST_MODIFY);
	icon[5]=AfxGetApp()->LoadIcon (IDI_USER_ADD1);
	icon[6]=AfxGetApp()->LoadIcon (IDI_PERMISSION);
	icon[7]=AfxGetApp()->LoadIcon (IDI_LIST_ADD1);
	icon[8]=AfxGetApp()->LoadIcon (IDI_LIST);
	icon[9]=AfxGetApp()->LoadIcon (IDI_LIST_QUERY);
	icon[10]=AfxGetApp()->LoadIcon (IDI_PERMISSIONS);
	icon[11]=AfxGetApp()->LoadIcon (IDI_USER_PASSWD);
	icon[12]=AfxGetApp()->LoadIcon (IDI_PERMISSION_MODIFY1);
	icon[13]=AfxGetApp()->LoadIcon (IDI_LIST_QUERY1);
	icon[14]=AfxGetApp()->LoadIcon (IDI_USER_DEL1);
	icon[15]=AfxGetApp()->LoadIcon (IDI_LIST_ADD2);
	icon[16]=AfxGetApp()->LoadIcon (IDI_UNPOST);
	icon[17]=AfxGetApp()->LoadIcon (IDI_POST);
	icon[18]=AfxGetApp()->LoadIcon (IDI_POST_UNPOST);
	icon[19]=AfxGetApp()->LoadIcon (IDI_MAKEING1);
	icon[20]=AfxGetApp()->LoadIcon (IDI_OUTPUT);
	icon[21]=AfxGetApp()->LoadIcon (IDI_DETAIL);
	icon[22]=AfxGetApp()->LoadIcon (IDI_MAIN2);
	icon[23]=AfxGetApp()->LoadIcon (IDI_PROCESS);
	icon[24]=AfxGetApp()->LoadIcon (IDI_MAKEING);
	icon[25]=AfxGetApp()->LoadIcon (IDI_CHANGE_RECORD);
	icon[26]=AfxGetApp()->LoadIcon (IDI_UNDO);


	//����ͼ���б�ؼ�
	CImageList *imagelist=new CImageList; 
	//imagelist->Create(24,24,0,MAX_ICO,MAX_ICO);
	//imagelist->SetBkColor (RGB(255,255,255));
	imagelist->Create(32,32,TRUE | ILC_COLOR8,MAX_ICO,MAX_ICO); 
	
	for(int n=0;n<MAX_ICO;n++)
	{
		imagelist->Add(icon[n]);  //��ͼ������ͼ���б�ؼ�
	}
	m_tree.SetImageList(imagelist,TVSIL_NORMAL);  //Ϊm_mytree����һ��ͼ���б�ʹCtreeCtrl�Ľڵ���ʾ��ͬ��ͼ�� 
	m_tree.SetBkColor(RGB(211,223,252));//����m_mytree�ı���ɫ

	m_tree.ModifyStyle(NULL,TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT|TVS_SHOWSELALWAYS);
	//�����ڵ�
	//���ڵ�
	HTREEITEM root0=m_tree.InsertItem("LDD�칫ϵͳ",22,22,TVI_ROOT,TVI_LAST);
	//һ���ӽڵ�
	HTREEITEM sub_son0=m_tree.InsertItem("Ȩ�޹���",10,10,root0,TVI_LAST);
	HTREEITEM sub_son1=m_tree.InsertItem("��������",8,8,root0,TVI_LAST);
	HTREEITEM sub_son2=m_tree.InsertItem("��Ŀ��ת",18,18,root0,TVI_LAST);
	HTREEITEM sub_son6=m_tree.InsertItem("����Ʒ����",19,19,root0,TVI_LAST);
	HTREEITEM sub_son3=m_tree.InsertItem("��������",23,23,root0,TVI_LAST);
	HTREEITEM sub_son4=m_tree.InsertItem("������ϸ",21,21,root0,TVI_LAST);
	HTREEITEM sub_son5=m_tree.InsertItem("����ͳ��",20,20,root0,TVI_LAST);
	HTREEITEM sub_son7=m_tree.InsertItem("�������",24,24,root0,TVI_LAST);
	//�������ӽڵ�
	HTREEITEM sub_m_son00=m_tree.InsertItem("�����û�",5,5,sub_son0,TVI_LAST);
	HTREEITEM sub_m_son01=m_tree.InsertItem("�޸�Ȩ��",4,4,sub_son0,TVI_LAST);
	HTREEITEM sub_m_son02=m_tree.InsertItem("�޸�����",11,11,sub_son0,TVI_LAST);
	HTREEITEM sub_m_son03=m_tree.InsertItem("��ѯȨ��",9,9,sub_son0,TVI_LAST);
	HTREEITEM sub_m_son04=m_tree.InsertItem("ɾ���û�",14,14,sub_son0,TVI_LAST);

	HTREEITEM sub_m_son10=m_tree.InsertItem("��������",15,15,sub_son1,TVI_LAST);
	HTREEITEM sub_m_son11=m_tree.InsertItem("�޸Ķ���",12,12,sub_son1,TVI_LAST);
	HTREEITEM sub_m_son12=m_tree.InsertItem("��ѯ����",13,13,sub_son1,TVI_LAST);
	HTREEITEM sub_m_son13=m_tree.InsertItem("�����¼",25,25,sub_son1,TVI_LAST);
	HTREEITEM sub_m_son14=m_tree.InsertItem("������¼",26,26,sub_son1,TVI_LAST);

	HTREEITEM sub_m_son20=m_tree.InsertItem("����",17,17,sub_son2,TVI_LAST);
	HTREEITEM sub_m_son21=m_tree.InsertItem("����",16,16,sub_son2,TVI_LAST);

	HTREEITEM sub_m_son30=m_tree.InsertItem("�տƱ",24,24,sub_son7,TVI_LAST);
	HTREEITEM sub_m_son31=m_tree.InsertItem("����",24,24,sub_son7,TVI_LAST);
	HTREEITEM sub_m_son32=m_tree.InsertItem("��ѯ",24,24,sub_son7,TVI_LAST);
	HTREEITEM sub_m_son33=m_tree.InsertItem("��ϸ",24,24,sub_son7,TVI_LAST);

	m_treePages[0]=new CDIALOG_CLIENT;
	m_treePages[1]=new CDialog_BaseInfo;
	m_treePages[2]=new CDialog_post;
	m_treePages[3]=new CDialog_Schdeule;
	m_treePages[4]=new CDialog_Detail;
	m_treePages[5]=new CDialog_Output;
	m_treePages[6]=new CDialog_New_List;
	m_treePages[7]=new CDialog_ModifyList;
	m_treePages[8]=new CDialog_Making;
	m_treePages[9]=new CDialog_Unpost;
	m_treePages[10]=new Dialog_ChangeRecord;
	m_treePages[11]=new Dialog_FI_Check;
	m_treePages[12]=new Dialog_UndoRecord;
	m_treePages[13]=new Dialog_FI_Query;
	m_treePages[14]=new Dialog_FI_Detail;


	//�����ڵ��Ӧ��Dialog
	m_treePages[0]->Create(IDD_DIALOG_CLIENT,this);
	m_treePages[1]->Create(IDD_DIALOG_BASEINFO,this);
	m_treePages[2]->Create(IDD_DIALOG_POST,this);
	m_treePages[3]->Create(IDD_DIALOG_SCHEDULE,this);
	m_treePages[4]->Create(IDD_DIALOG_DETAIL,this);
	m_treePages[5]->Create(IDD_DIALOG_OUTPUT1,this);
	m_treePages[6]->Create(IDD_DIALOG_NEW_LIST,this);
	m_treePages[7]->Create(IDD_DIALOG_MODIFY_LIST1,this);
	m_treePages[8]->Create(IDD_DIALOG_MAKEING,this);
	m_treePages[9]->Create(IDD_DIALOG_UNPOST,this);
	m_treePages[10]->Create(IDD_DIALOG_CHAGNE_RECORD,this);
	m_treePages[11]->Create(IDD_DIALOG_FI_CHECK,this);
	m_treePages[12]->Create(IDD_DIALOG_UNDO_RECORD,this);
	m_treePages[13]->Create(IDD_DIALOG_FI_QUERY,this);
	m_treePages[14]->Create(IDD_DIALOG_FI_DETAIL,this);


	//��Dialog�Ƶ�����λ��

	m_tree.MoveWindow(0,0,230,height-50);

	CRect m_rect;
	GetClientRect(m_rect);
	CRect rectlist(m_rect);
	CRect rectlistfi(m_rect);
	CRect rectlistoutput(m_rect);
	CRect rectlisttotal(m_rect);
	m_rect.DeflateRect(230,0,20,20);
	rectlist.DeflateRect(0,50,250,20);
	rectlistfi.DeflateRect(0,165,250,20);
	rectlistoutput.DeflateRect(0,50,250,45);
	rectlisttotal.DeflateRect(0,m_rect.bottom-22,250,0);

	m_treePages[0]->MoveWindow(m_rect);
	((CDIALOG_CLIENT*)(m_treePages[0]))->m_list_Clinet.MoveWindow(rectlist);
	m_treePages[0]->ShowWindow(SW_HIDE);
	m_treePages[1]->MoveWindow(m_rect);
	((CDialog_BaseInfo*)(m_treePages[1]))->m_list_baseinfo.MoveWindow(rectlist);
	m_treePages[1]->ShowWindow(SW_HIDE);
	m_treePages[2]->MoveWindow(m_rect);
	m_treePages[2]->ShowWindow(SW_HIDE);
	m_treePages[3]->MoveWindow(m_rect);
	((CDialog_Schdeule*)(m_treePages[3]))->m_list_schedule.MoveWindow(rectlist);
	m_treePages[3]->ShowWindow(SW_HIDE);
	m_treePages[4]->MoveWindow(m_rect);
	((CDialog_Detail*)(m_treePages[4]))->m_listdetail.MoveWindow(rectlist);
	m_treePages[4]->ShowWindow(SW_HIDE);
	m_treePages[5]->MoveWindow(m_rect);
	((CDialog_Output*)(m_treePages[5]))->m_list_output.MoveWindow(rectlistoutput);
	((CDialog_Output*)(m_treePages[5]))->m_list_total.MoveWindow(rectlisttotal);
	m_treePages[5]->ShowWindow(SW_HIDE);
	m_treePages[6]->MoveWindow(m_rect);
	m_treePages[6]->ShowWindow(SW_HIDE);
	m_treePages[7]->MoveWindow(m_rect);
	m_treePages[7]->ShowWindow(SW_HIDE);
	m_treePages[8]->MoveWindow(m_rect);
	((CDialog_Making*)(m_treePages[8]))->m_list_schedule.MoveWindow(rectlist);
	m_treePages[8]->ShowWindow(SW_SHOW);
	m_treePages[9]->MoveWindow(m_rect);
	m_treePages[9]->ShowWindow(SW_HIDE);
	m_treePages[10]->MoveWindow(m_rect);
	((Dialog_ChangeRecord*)(m_treePages[10]))->m_listChangeRecord.MoveWindow(rectlist);
	m_treePages[10]->ShowWindow(SW_HIDE);
	m_treePages[11]->MoveWindow(m_rect);
	((Dialog_FI_Check*)(m_treePages[11]))->m_listFI.MoveWindow(rectlist);
	m_treePages[11]->ShowWindow(SW_HIDE);
	m_treePages[12]->MoveWindow(m_rect);
	((Dialog_UndoRecord*)(m_treePages[12]))->m_listUndoRecord.MoveWindow(rectlist);
	m_treePages[12]->ShowWindow(SW_HIDE);
	m_treePages[13]->MoveWindow(m_rect);
	((Dialog_FI_Query*)(m_treePages[13]))->m_listFI.MoveWindow(rectlist);
	m_treePages[13]->ShowWindow(SW_HIDE);
	m_treePages[14]->MoveWindow(m_rect);
	((Dialog_FI_Detail*)(m_treePages[14]))->m_listFI.MoveWindow(rectlist);
	m_treePages[14]->ShowWindow(SW_HIDE);


	m_tree.Expand(m_tree.GetRootItem(),TVE_EXPAND);//չ��/������  
	//m_tree.Expand(sub_son0,TVE_EXPAND);
	m_tree.Expand(sub_son1,TVE_EXPAND);
	m_tree.Expand(sub_son2,TVE_EXPAND);
	m_tree.Expand(sub_son7,TVE_EXPAND);

	//logintips
	CString strpathini="";
	::GetCurrentDirectory(_MAX_PATH,strpathini.GetBuffer(_MAX_PATH));
	strpathini.ReleaseBuffer();
	strpathini = strpathini + "\\" + CONFIGINI;
	char buf[_MAX_PATH] = {0};
	int logintips = GetPrivateProfileInt("Tips", "LoginTips", 1, strpathini);
	int timertips = GetPrivateProfileInt("Tips", "TimerTips", 1, strpathini);
	if (timertips)
	{
		GetPrivateProfileString("Tips", "Timer", DEFAULT_TIME, buf, _MAX_PATH, strpathini);
		timertime = buf;
		m_hour = atoi(timertime.Mid(0,2));
		m_min = atoi(timertime.Mid(3,2));
	}
	
	if (logintips)
	{
		if ((g_department.Compare("����������")==0) || (g_department.Compare("���������ι�")==0) ||  (g_department.Compare("������")==0))
		{
			Dialog_Tips *dlg;
			dlg=new Dialog_Tips(); 
			dlg->m_blogintips = 1;
			dlg->Create(IDD_DIALOG_TIPS);
			dlg->CenterWindow();
			dlg->ShowWindow(SW_SHOW);
		}
	}
	if (timertips)
	{
		SetTimer(TIMERID_TIP, TIMER_WAIT_TIP, NULL);
	}
	writelog("dlg init ok");
	return true;
}
	
void CGoodsManageSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	char log[256] = {0};
	sprintf(log,"OnSysCommand \t%s,%d",__FILE__,__LINE__);
	writelog(log);
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGoodsManageSystemDlg::OnPaint() 
{
	char log[256] = {0};
	sprintf(log,"OnPaint \t%s,%d",__FILE__,__LINE__);
	writelog(log);
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGoodsManageSystemDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGoodsManageSystemDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}

void CGoodsManageSystemDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//AnimateWindow(this->GetSafeHwnd(),800,AW_HOR_NEGATIVE|AW_HIDE|AW_VER_POSITIVE);
	char log[256] = {0};
	sprintf(log,"OnClose \t%s,%d",__FILE__,__LINE__);
	writelog(log);
	CDialog::OnClose();
	CDialog::OnCancel();
}

void CGoodsManageSystemDlg::OnSize(UINT nType, int cx, int cy) 
{
	char log[256] = {0};
	sprintf(log,"OnSize \t%s,%d",__FILE__,__LINE__);
	writelog(log);
	CDialog::OnSize(nType, cx, cy);
	sprintf(log,"OnSize \t%s,%d",__FILE__,__LINE__);
	writelog(log);
	CRect m_rect;
	GetClientRect(m_rect);
	CRect rectlist(m_rect);
	CRect rectlistfi(m_rect);
	CRect rectlistoutput(m_rect);
	CRect rectlisttotal(m_rect);
	m_rect.DeflateRect(230,0,20,20);
	rectlist.DeflateRect(0,50,250,20);
	rectlistfi.DeflateRect(0,165,250,20);
	rectlistoutput.DeflateRect(0,50,250,45);
	rectlisttotal.DeflateRect(0,m_rect.bottom-22,250,0);

	sprintf(log,"OnSize \t%s,%d",__FILE__,__LINE__);
	writelog(log);
	int i = 0;
	for(i=0;i<MAX_TREE_PAGE;i++)
	{
		if(m_treePages[i]==NULL)
			return;
	}
	sprintf(log,"OnSize %x \t%s,%d",&m_treePages[0],__FILE__,__LINE__);
	writelog(log);
	m_treePages[0]->MoveWindow(m_rect);
	((CDIALOG_CLIENT*)(m_treePages[0]))->m_list_Clinet.MoveWindow(rectlist);
	sprintf(log,"OnSize \t%s,%d",__FILE__,__LINE__);
	writelog(log);
	m_treePages[1]->MoveWindow(m_rect);
	((CDialog_BaseInfo*)(m_treePages[1]))->m_list_baseinfo.MoveWindow(rectlist);
	m_treePages[2]->MoveWindow(m_rect);
	m_treePages[3]->MoveWindow(m_rect);
	((CDialog_Schdeule*)(m_treePages[3]))->m_list_schedule.MoveWindow(rectlist);
	m_treePages[4]->MoveWindow(m_rect);
	((CDialog_Detail*)(m_treePages[4]))->m_listdetail.MoveWindow(rectlist);
	m_treePages[5]->MoveWindow(m_rect);
	((CDialog_Output*)(m_treePages[5]))->m_list_output.MoveWindow(rectlistoutput);
	((CDialog_Output*)(m_treePages[5]))->m_list_total.MoveWindow(rectlisttotal);
	m_treePages[6]->MoveWindow(m_rect);
	m_treePages[7]->MoveWindow(m_rect);
	m_treePages[8]->MoveWindow(m_rect);
	((CDialog_Making*)(m_treePages[8]))->m_list_schedule.MoveWindow(rectlist);
	m_treePages[9]->MoveWindow(m_rect);
	sprintf(log,"OnSize \t%s,%d",__FILE__,__LINE__);
	writelog(log);
	m_treePages[10]->MoveWindow(m_rect);
	((Dialog_ChangeRecord*)(m_treePages[10]))->m_listChangeRecord.MoveWindow(rectlist);
	m_treePages[11]->MoveWindow(m_rect);
	((Dialog_FI_Check*)(m_treePages[11]))->m_listFI.MoveWindow(rectlist);
	m_treePages[12]->MoveWindow(m_rect);
	((Dialog_UndoRecord*)(m_treePages[12]))->m_listUndoRecord.MoveWindow(rectlist);
	m_treePages[13]->MoveWindow(m_rect);
	((Dialog_FI_Query*)(m_treePages[13]))->m_listFI.MoveWindow(rectlist);
	m_treePages[14]->MoveWindow(m_rect);
	((Dialog_FI_Detail*)(m_treePages[14]))->m_listFI.MoveWindow(rectlist);


	sprintf(log,"OnSize \t%s,%d",__FILE__,__LINE__);
	writelog(log);

}

void CGoodsManageSystemDlg::OnHelp() 
{
	// TODO: Add your command handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}

void CGoodsManageSystemDlg::OnBuyQuery() 
{

}

void CGoodsManageSystemDlg::OnClientAdd() 
{

}

void CGoodsManageSystemDlg::OnClientQuery() 
{

}

void CGoodsManageSystemDlg::OnSellAdd() 
{
		
}

void CGoodsManageSystemDlg::OnSellQuery() 
{

}

void CGoodsManageSystemDlg::OnBuyAdd() 
{
}

void CGoodsManageSystemDlg::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	char log[256] = {0};
	sprintf(log,"OnSelchangedTree \t%s,%d",__FILE__,__LINE__);
	writelog(log);
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	UpdateData(true);
	node_name=m_tree.GetItemText(pNMTreeView->itemNew.hItem);
	//�ڱ�������ʾ�ڵ���Ϣ
	CString strtext;
	strtext.Format("%s->%s",g_user,node_name);
	SetWindowText(strtext);
	//�л����
	int i=0;
	for(i=0;i<MAX_TREE_PAGE;i++)
	{
		m_treePages[i]->ShowWindow(SW_HIDE);
	}

	if(node_name=="LDD�칫ϵͳ"){
		if(bFirstin==1)
		{
			m_treePages[8]->ShowWindow(SW_SHOW);
		}
		else
		{
			m_treePages[icurrentpage]->ShowWindow(SW_SHOW);
		}
		bFirstin = 0 ;
	}
	else if(node_name=="�����û�"){
		m_treePages[0]->ShowWindow(SW_SHOW);
		if(g_permission & PERMISSION)
		{
			CDialog_AddUser dlg;
			dlg.DoModal();
		}
		icurrentpage = 0;
	}
	else if(node_name=="�޸�Ȩ��"){
		m_treePages[0]->ShowWindow(SW_SHOW);
		if(g_permission & PERMISSION)
		{
			CDialog_Modify_Permission	dlg;
			dlg.DoModal();
		}
		icurrentpage = 0;
	}
	else if(node_name=="�޸�����"){
		m_treePages[0]->ShowWindow(SW_SHOW);
		if(g_permission & PERMISSION)
		{
			CDialog_ModifyPW_Admin dlg;
			dlg.DoModal();
		}
		icurrentpage = 0;
	}
	else if(node_name=="��ѯȨ��" || node_name=="Ȩ�޹���"){
		m_treePages[0]->ShowWindow(SW_SHOW);
		icurrentpage = 0;
	}
	else if(node_name=="ɾ���û�"){
		m_treePages[0]->ShowWindow(SW_SHOW);
		if(g_permission & PERMISSION)
		{
			CDialog_Delete_User dlg;
			dlg.DoModal();
		}
		icurrentpage = 0;
	}
	else if(node_name=="��������"){
		m_treePages[6]->ShowWindow(SW_SHOW);
		icurrentpage = 6;
	}
	else if(node_name=="�޸Ķ���" ){
		m_treePages[7]->ShowWindow(SW_SHOW);
		icurrentpage = 7;
	}
	else if(node_name=="��ѯ����" || node_name=="��������"){
		m_treePages[1]->ShowWindow(SW_SHOW);
		icurrentpage = 1;
	}
	else if(node_name=="�����¼" ){
		m_treePages[10]->ShowWindow(SW_SHOW);
		icurrentpage = 10;
	}
	else if(node_name=="������¼" ){
		m_treePages[12]->ShowWindow(SW_SHOW);
		icurrentpage = 12;
	}
	else if(node_name=="����" || node_name=="��Ŀ��ת"){
		m_treePages[2]->ShowWindow(SW_SHOW);
		icurrentpage = 2;
	}
	else if(node_name=="����"){
		m_treePages[9]->ShowWindow(SW_SHOW);
		icurrentpage = 9;
	}
	else if(node_name=="����Ʒ����"){
		m_treePages[8]->ShowWindow(SW_SHOW);
		icurrentpage = 8;
	}
	else if(node_name=="��������"){
		m_treePages[3]->ShowWindow(SW_SHOW);
		icurrentpage = 3;
	}
	else if(node_name=="������ϸ"){
		m_treePages[4]->ShowWindow(SW_SHOW);
		icurrentpage = 4;
	}
	else if(node_name=="����ͳ��"){
		m_treePages[5]->ShowWindow(SW_SHOW);
		icurrentpage = 5;
	}
	else if(node_name=="�������"){
		m_treePages[13]->ShowWindow(SW_SHOW);
		icurrentpage = 13;
	}
	else if(node_name=="�տƱ"){
		m_treePages[13]->ShowWindow(SW_SHOW);
		if(g_permission & FI)
		{
			Dialog_FI_Proceeds dlg;
			dlg.DoModal();
		}		
		icurrentpage = 13;
	}
	else if(node_name=="����"){
		m_treePages[11]->ShowWindow(SW_SHOW);
		icurrentpage = 11;
	}
	else if(node_name=="��ѯ"){
		m_treePages[13]->ShowWindow(SW_SHOW);
		icurrentpage = 13;
	}
	else if(node_name=="��ϸ"){
		m_treePages[14]->ShowWindow(SW_SHOW);
		icurrentpage = 14;
	}
	UpdateData(false);

	*pResult = 0;
}

BOOL CGoodsManageSystemDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN) 
	{  
		switch(pMsg->wParam) 
		{  
		case VK_RETURN: //�س�  
			return TRUE;  
		case VK_ESCAPE: //ESC  
			return TRUE;  
		}  
	}	
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CGoodsManageSystemDlg::OnMenuitemTips() 
{
	char log[256] = {0};
	sprintf(log,"OnMenuitemTips \t%s,%d",__FILE__,__LINE__);
	writelog(log);
	Dialog_TipsSetting dlg;
	dlg.DoModal();
}

void CGoodsManageSystemDlg::OnTimer(UINT nIDEvent) 
{
	char log[256] = {0};
	sprintf(log,"OnTimer \t%s,%d",__FILE__,__LINE__);
	writelog(log);

	CTime CurrentTime;
	int hour = 0,min = 0;
	switch(nIDEvent)
	{	
	case TIMERID_TIP:
		KillTimer(TIMERID_TIP);
		CurrentTime = CTime::GetCurrentTime();
		hour = CurrentTime.GetHour();
		min = CurrentTime.GetMinute();
		if ((hour == m_hour) && (min == m_min))
		{
			if ((g_department.Compare("����������")==0) || (g_department.Compare("���������ι�")==0) ||  (g_department.Compare("������")==0))
			{
				Dialog_Tips *dlg;
				dlg=new Dialog_Tips(); 
				dlg->m_blogintips = 0;
				dlg->Create(IDD_DIALOG_TIPS);
				dlg->CenterWindow();
				dlg->ShowWindow(SW_SHOW);
			}
		}
		SetTimer(TIMERID_TIP,TIMER_WAIT_TIP,NULL);
		break;
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}
