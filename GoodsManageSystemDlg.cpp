// GoodsManageSystemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GoodsManageSystem.h"
#include "GoodsManageSystemDlg.h"
#include "Winuser.h"

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
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGoodsManageSystemDlg message handlers

#define MAX_ICO 24
BOOL CGoodsManageSystemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	this->ShowWindow(SW_SHOWMAXIMIZED);
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	SetWindowText("LDD办公系统");

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	CRect rectSc(0,0,width,height);
	//MoveWindow(&rectSc);
	//CRect recttab(0,20,width,height);
	//m_tab.MoveWindow(&recttab);

	//节点的图标	 
	int i=0;
	int i_count=MAX_ICO;
	//载入图标
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


	//创建图像列表控件
	CImageList *imagelist=new CImageList; 
	imagelist->Create(24,24,0,MAX_ICO,MAX_ICO); 
	imagelist->SetBkColor (RGB(255,255,255));
	for(int n=0;n<MAX_ICO;n++)
	{
		imagelist->Add(icon[n]);  //把图标载入图像列表控件
	}
	m_tree.SetImageList(imagelist,TVSIL_NORMAL);  //为m_mytree设置一个图像列表，使CtreeCtrl的节点显示不同的图标 
	m_tree.SetBkColor(RGB(211,223,252));//设置m_mytree的背景色

	m_tree.ModifyStyle(NULL,TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT);
	//创建节点
	//父节点
	HTREEITEM root0=m_tree.InsertItem("LDD办公系统",22,22,TVI_ROOT,TVI_LAST);
	//一层子节点
	HTREEITEM sub_son0=m_tree.InsertItem("权限管理",10,10,root0,TVI_LAST);
	HTREEITEM sub_son1=m_tree.InsertItem("订单资料",8,8,root0,TVI_LAST);
	HTREEITEM sub_son2=m_tree.InsertItem("账目流转",18,18,root0,TVI_LAST);
	HTREEITEM sub_son6=m_tree.InsertItem("在制品进度",19,19,root0,TVI_LAST);
	HTREEITEM sub_son3=m_tree.InsertItem("订单进度",23,23,root0,TVI_LAST);
	HTREEITEM sub_son4=m_tree.InsertItem("进度明细",21,21,root0,TVI_LAST);
	HTREEITEM sub_son5=m_tree.InsertItem("产能统计",20,20,root0,TVI_LAST);
	//二层孙子节点
	HTREEITEM sub_m_son00=m_tree.InsertItem("增加用户",5,5,sub_son0,TVI_LAST);
	HTREEITEM sub_m_son01=m_tree.InsertItem("修改权限",4,4,sub_son0,TVI_LAST);
	HTREEITEM sub_m_son02=m_tree.InsertItem("修改密码",11,11,sub_son0,TVI_LAST);
	HTREEITEM sub_m_son03=m_tree.InsertItem("查询权限",9,9,sub_son0,TVI_LAST);
	HTREEITEM sub_m_son04=m_tree.InsertItem("删除用户",14,14,sub_son0,TVI_LAST);

	HTREEITEM sub_m_son10=m_tree.InsertItem("新增订单",15,15,sub_son1,TVI_LAST);
	HTREEITEM sub_m_son11=m_tree.InsertItem("修改订单",12,12,sub_son1,TVI_LAST);
	HTREEITEM sub_m_son12=m_tree.InsertItem("查询订单",13,13,sub_son1,TVI_LAST);

	HTREEITEM sub_m_son20=m_tree.InsertItem("过账",17,17,sub_son2,TVI_LAST);
	HTREEITEM sub_m_son21=m_tree.InsertItem("退账",16,16,sub_son2,TVI_LAST);

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

	//建立节点对应的Dialog
	m_treePages[0]->Create(IDD_DIALOG_CLIENT,this);
	m_treePages[1]->Create(IDD_DIALOG_BASEINFO,this);
	m_treePages[2]->Create(IDD_DIALOG_POST,this);
	m_treePages[3]->Create(IDD_DIALOG_SCHEDULE,this);
	m_treePages[4]->Create(IDD_DIALOG_DETAIL,this);
	m_treePages[5]->Create(IDD_DIALOG_OUTPUT,this);
	m_treePages[6]->Create(IDD_DIALOG_NEW_LIST,this);
	m_treePages[7]->Create(IDD_DIALOG_MODIFY_LIST1,this);
	m_treePages[8]->Create(IDD_DIALOG_MAKEING,this);
	m_treePages[9]->Create(IDD_DIALOG_UNPOST,this);

	//把Dialog移到合适位置

	m_tree.MoveWindow(0,0,200,height-20);

	CRect m_rect;
	GetClientRect(m_rect);
	m_rect.DeflateRect(200,0,20,20);

	for(i=0;i<MAX_TREE_PAGE;i++)
	{
		m_treePages[i]->MoveWindow(m_rect);
		if(i!=8)
			m_treePages[i]->ShowWindow(SW_HIDE);
	}
	m_treePages[8]->ShowWindow(SW_SHOW);

/*	CRect rect,rect1,rec;
	this->GetClientRect(&rect);  
	ClientToScreen(&rect);
	
	for(i=0;i<MAX_TREE_PAGE;i++)
	{
		m_treePages[i]->GetClientRect(&rect1);
		m_treePages[i]->CalcWindowRect(&rect1);
		m_treePages[i]->MoveWindow(200,0,rect1.Width(),rect1.Height());
		if(i!=8)
			m_treePages[i]->ShowWindow(SW_HIDE);
	}
	m_treePages[8]->ShowWindow(SW_SHOW);
*/

	m_tree.Expand(m_tree.GetRootItem(),TVE_EXPAND);//展开/叠起结点  
	m_tree.Expand(sub_son0,TVE_EXPAND);
	m_tree.Expand(sub_son1,TVE_EXPAND);
	m_tree.Expand(sub_son2,TVE_EXPAND);
	return true;
}
	
void CGoodsManageSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
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
	CDialog::OnClose();
	CDialog::OnCancel();
}

void CGoodsManageSystemDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
/*	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	CRect m_rect(0,0,width,height);
	m_rect.DeflateRect(200,0,20,20);
	//this->MoveWindow(m_rect);
	int i=0;
	for(i=0;i<MAX_TREE_PAGE;i++)
	{
		m_treePages[i]->GetClientRect(&m_rect);
		m_treePages[i]->CalcWindowRect(&m_rect);
		m_treePages[i]->MoveWindow(200,0,m_rect.Width(),m_rect.Height());
	}
	*/
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
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	UpdateData(true);
	node_name=m_tree.GetItemText(pNMTreeView->itemNew.hItem);
	//在标题栏显示节点信息
	CString strtext;
	strtext.Format("%s->%s",g_user,node_name);
	SetWindowText(strtext);
	//切换面板
	int i=0;
	for(i=0;i<MAX_TREE_PAGE;i++)
	{
		m_treePages[i]->ShowWindow(SW_HIDE);
	}

	if(node_name=="增加用户"){
		m_treePages[0]->ShowWindow(SW_SHOW);
		if(g_permission & PERMISSION)
		{
			CDialog_AddUser dlg;
			dlg.DoModal();
		}
	}
	else if(node_name=="修改权限"){
		m_treePages[0]->ShowWindow(SW_SHOW);
		if(g_permission & PERMISSION)
		{
			CDialog_Modify_Permission	dlg;
			dlg.DoModal();
		}
	}
	else if(node_name=="修改密码"){
		m_treePages[0]->ShowWindow(SW_SHOW);
		if(g_permission & PERMISSION)
		{
			CDialog_ModifyPW_Admin dlg;
			dlg.DoModal();
		}
	}
	else if(node_name=="查询权限" || node_name=="权限管理"){
		m_treePages[0]->ShowWindow(SW_SHOW);
	}
	else if(node_name=="删除用户"){
		m_treePages[0]->ShowWindow(SW_SHOW);
		if(g_permission & PERMISSION)
		{
			CDialog_Delete_User dlg;
			dlg.DoModal();
		}
	}
	else if(node_name=="新增订单"){
		m_treePages[6]->ShowWindow(SW_SHOW);
	}
	else if(node_name=="修改订单" ){
		m_treePages[7]->ShowWindow(SW_SHOW);
	}
	else if(node_name=="查询订单" || node_name=="订单资料"){
		m_treePages[1]->ShowWindow(SW_SHOW);
	}
	else if(node_name=="过账" || node_name=="账目流转"){
		m_treePages[2]->ShowWindow(SW_SHOW);
	}
	else if(node_name=="退账"){
		m_treePages[9]->ShowWindow(SW_SHOW);
	}
	else if(node_name=="在制品进度" || node_name=="LDD办公系统"){
		m_treePages[8]->ShowWindow(SW_SHOW);
	}
	else if(node_name=="订单进度"){
		m_treePages[3]->ShowWindow(SW_SHOW);
	}
	else if(node_name=="进度明细"){
		m_treePages[4]->ShowWindow(SW_SHOW);
	}
	else if(node_name=="产能统计"){
		m_treePages[5]->ShowWindow(SW_SHOW);
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
		case VK_RETURN: //回车  
			return TRUE;  
		case VK_ESCAPE: //ESC  
			return TRUE;  
		}  
	}	
	
	return CDialog::PreTranslateMessage(pMsg);
}
