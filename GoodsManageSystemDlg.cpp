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
#include "Dialog_List_Web.h"
#include "Dialog_Storage_In.h"
#include "Dialog_Storage_Left.h"
#include "Dialog_Storage_In_Detail.h"
#include "Dialog_Storage_Out_Detail.h"
#include "Dialog_Storage_Out.h"
#include "Dialog_List_Shipping.h"
#include "Dialog_SendUser.h"
#include "Dialog_ListExpress.h"

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
	writelog("CGoodsManageSystemDl构造函数");
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
	writelog("CGoodsManageSystemDl构造函数结束");
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
	writelog("CGoodsManageSystemDlg::OnInitDialog 显示主界面");
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
	icon[24]=AfxGetApp()->LoadIcon (IDI_MAKEING);
	icon[25]=AfxGetApp()->LoadIcon (IDI_CHANGE_RECORD);
	icon[26]=AfxGetApp()->LoadIcon (IDI_UNDO);


	//创建图像列表控件
	CImageList *imagelist=new CImageList; 
	//imagelist->Create(24,24,0,MAX_ICO,MAX_ICO);
	//imagelist->SetBkColor (RGB(255,255,255));
	imagelist->Create(32,32,TRUE | ILC_COLOR8,MAX_ICO,MAX_ICO); 
	
	for(int n=0;n<MAX_ICO;n++)
	{
		imagelist->Add(icon[n]);  //把图标载入图像列表控件
	}
	m_tree.SetImageList(imagelist,TVSIL_NORMAL);  //为m_mytree设置一个图像列表，使CtreeCtrl的节点显示不同的图标 
	m_tree.SetBkColor(RGB(211,223,252));//设置m_mytree的背景色

	m_tree.ModifyStyle(NULL,TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT|TVS_SHOWSELALWAYS);
	//创建节点
	//父节点
	HTREEITEM root0=m_tree.InsertItem("LDD办公系统",22,22,TVI_ROOT,TVI_LAST);
	//一层子节点
	HTREEITEM sub_son0=m_tree.InsertItem("权限管理",10,10,root0,TVI_LAST);
	HTREEITEM sub_son1=m_tree.InsertItem("订单资料",8,8,root0,TVI_LAST);
	HTREEITEM sub_son2=m_tree.InsertItem("账目流转",18,18,root0,TVI_LAST);
	HTREEITEM sub_son6=m_tree.InsertItem("在制品进度",9,9,root0,TVI_LAST);
	HTREEITEM sub_son3=m_tree.InsertItem("订单进度",13,13,root0,TVI_LAST);
	HTREEITEM sub_son4=m_tree.InsertItem("进度明细",21,21,root0,TVI_LAST);
	HTREEITEM sub_son5=m_tree.InsertItem("产能统计",20,20,root0,TVI_LAST);
	HTREEITEM sub_son9=m_tree.InsertItem("发货管理",22,22,root0,TVI_LAST);
	HTREEITEM sub_son7=m_tree.InsertItem("财务管理",24,24,root0,TVI_LAST);
	HTREEITEM sub_son8=m_tree.InsertItem("仓库管理",22,22,root0,TVI_LAST);
	//二层孙子节点
	HTREEITEM sub_m_son00=m_tree.InsertItem("增加用户",5,5,sub_son0,TVI_LAST);
	HTREEITEM sub_m_son01=m_tree.InsertItem("修改权限",4,4,sub_son0,TVI_LAST);
	HTREEITEM sub_m_son02=m_tree.InsertItem("修改密码",11,11,sub_son0,TVI_LAST);
	HTREEITEM sub_m_son03=m_tree.InsertItem("查询权限",9,9,sub_son0,TVI_LAST);
	HTREEITEM sub_m_son04=m_tree.InsertItem("删除用户",14,14,sub_son0,TVI_LAST);

	HTREEITEM sub_m_son10=m_tree.InsertItem("新增订单",15,15,sub_son1,TVI_LAST);
	HTREEITEM sub_m_son11=m_tree.InsertItem("修改订单",12,12,sub_son1,TVI_LAST);
	HTREEITEM sub_m_son12=m_tree.InsertItem("查询订单",13,13,sub_son1,TVI_LAST);
	HTREEITEM sub_m_son13=m_tree.InsertItem("变更记录",25,25,sub_son1,TVI_LAST);
	HTREEITEM sub_m_son14=m_tree.InsertItem("销单记录",26,26,sub_son1,TVI_LAST);
	HTREEITEM sub_m_son15=m_tree.InsertItem("网络订单",13,13,sub_son1,TVI_LAST);

	HTREEITEM sub_m_son20=m_tree.InsertItem("过账",17,17,sub_son2,TVI_LAST);
	HTREEITEM sub_m_son21=m_tree.InsertItem("退账",16,16,sub_son2,TVI_LAST);

	HTREEITEM sub_m_son50=m_tree.InsertItem("发货清单",25,25,sub_son9,TVI_LAST);
	HTREEITEM sub_m_son51=m_tree.InsertItem("经办人资料库",5,5,sub_son9,TVI_LAST);
	HTREEITEM sub_m_son52=m_tree.InsertItem("快递单打印",13,13,sub_son9,TVI_LAST);

	HTREEITEM sub_m_son30=m_tree.InsertItem("收款开票",4,4,sub_son7,TVI_LAST);
	HTREEITEM sub_m_son31=m_tree.InsertItem("核销",11,11,sub_son7,TVI_LAST);
	HTREEITEM sub_m_son32=m_tree.InsertItem("查询",9,9,sub_son7,TVI_LAST);
	HTREEITEM sub_m_son33=m_tree.InsertItem("明细",21,21,sub_son7,TVI_LAST);

	HTREEITEM sub_m_son40=m_tree.InsertItem("进货单",17,17,sub_son8,TVI_LAST);
	HTREEITEM sub_m_son41=m_tree.InsertItem("出库单",16,16,sub_son8,TVI_LAST);
	HTREEITEM sub_m_son42=m_tree.InsertItem("进货明细",13,13,sub_son8,TVI_LAST);
	HTREEITEM sub_m_son43=m_tree.InsertItem("出库明细",21,21,sub_son8,TVI_LAST);
	HTREEITEM sub_m_son44=m_tree.InsertItem("库存余额",9,9,sub_son8,TVI_LAST);

	m_itemNewList = sub_m_son10;
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
	m_treePages[15]=new Dialog_List_Web;
	m_treePages[16]=new Dialog_Storage_In;
	m_treePages[17]=new Dialog_Storage_Left;
	m_treePages[18]=new Dialog_Storage_In_Detail;
	m_treePages[19]=new Dialog_Storage_Out;
	m_treePages[20]=new Dialog_Storage_Out_Detail;
	m_treePages[21]=new Dialog_List_Shipping;
	m_treePages[22]=new Dialog_SendUser;
	m_treePages[23]=new Dialog_ListExpress;


	//建立节点对应的Dialog
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
	m_treePages[15]->Create(IDD_DIALOG_LIST_WEB,this);
	m_treePages[16]->Create(IDD_DIALOG_STORAGE_IN,this);
	m_treePages[17]->Create(IDD_DIALOG_STORAGE_LEFT,this);
	m_treePages[18]->Create(IDD_DIALOG_STORAGE_IN_DETAIL,this);
	m_treePages[19]->Create(IDD_DIALOG_STORAGE_OUT,this);
	m_treePages[20]->Create(IDD_DIALOG_STORAGE_OUT_DETAIL,this);
	m_treePages[21]->Create(IDD_DIALOG_LIST_SHIPPING,this);
	m_treePages[22]->Create(IDD_DIALOG_SEND_USER,this);
	m_treePages[23]->Create(IDD_DIALOG_LIST_EXPRESS,this);

	//把Dialog移到合适位置

	m_tree.MoveWindow(0,0,230,height-50);

	CRect m_rect;
	GetClientRect(m_rect);
	CRect rectlist(m_rect);
	CRect rectlistoutput(m_rect);
	CRect rectlisttotal(m_rect);
	CRect rectliststorage(m_rect);
	m_rect.DeflateRect(230,0,20,20);
	rectlist.DeflateRect(0,50,250,20);
	rectlistoutput.DeflateRect(0,50,250,45);
	rectlisttotal.DeflateRect(0,m_rect.bottom-22,250,0);
	rectliststorage.DeflateRect(0,240,250,45);

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
	m_treePages[15]->MoveWindow(m_rect);
	((Dialog_List_Web*)(m_treePages[15]))->m_listweb.MoveWindow(rectlist);
	m_treePages[15]->ShowWindow(SW_HIDE);
	m_treePages[16]->MoveWindow(m_rect);
	((Dialog_Storage_In*)(m_treePages[16]))->m_listStorageIn.MoveWindow(rectliststorage);
	((Dialog_Storage_In*)(m_treePages[16]))->m_listTotal.MoveWindow(rectlisttotal);
	m_treePages[16]->ShowWindow(SW_HIDE);
	m_treePages[17]->MoveWindow(m_rect);
	((Dialog_Storage_Left*)(m_treePages[17]))->m_list_StorageLeft.MoveWindow(rectlistoutput);
	((Dialog_Storage_Left*)(m_treePages[17]))->m_listTotal.MoveWindow(rectlisttotal);
	m_treePages[17]->ShowWindow(SW_HIDE);
	m_treePages[18]->MoveWindow(m_rect);
	((Dialog_Storage_In_Detail*)(m_treePages[18]))->m_listStorageInDetail.MoveWindow(rectlistoutput);
	((Dialog_Storage_In_Detail*)(m_treePages[18]))->m_listTotal.MoveWindow(rectlisttotal);
	m_treePages[18]->ShowWindow(SW_HIDE);
	m_treePages[19]->MoveWindow(m_rect);
	((Dialog_Storage_Out*)(m_treePages[19]))->m_listStorageIn.MoveWindow(rectliststorage);
	((Dialog_Storage_Out*)(m_treePages[19]))->m_listTotal.MoveWindow(rectlisttotal);
	m_treePages[19]->ShowWindow(SW_HIDE);
	m_treePages[20]->MoveWindow(m_rect);
	((Dialog_Storage_Out_Detail*)(m_treePages[20]))->m_listStorageInDetail.MoveWindow(rectlistoutput);
	((Dialog_Storage_Out_Detail*)(m_treePages[20]))->m_listTotal.MoveWindow(rectlisttotal);
	m_treePages[20]->ShowWindow(SW_HIDE);
	m_treePages[21]->MoveWindow(m_rect);
	((Dialog_List_Shipping*)(m_treePages[21]))->m_listBaseInfo.MoveWindow(rectlist);
	m_treePages[21]->ShowWindow(SW_HIDE);
	m_treePages[22]->MoveWindow(m_rect);
	((Dialog_SendUser*)(m_treePages[22]))->m_listSendUser.MoveWindow(rectlist);
	m_treePages[22]->ShowWindow(SW_HIDE);
	m_treePages[23]->MoveWindow(m_rect);
	((Dialog_ListExpress*)(m_treePages[23]))->m_listBaseInfo.MoveWindow(rectlist);
	m_treePages[23]->ShowWindow(SW_HIDE);

	m_tree.Expand(m_tree.GetRootItem(),TVE_EXPAND);//展开/叠起结点
	//m_tree.Expand(sub_son0,TVE_EXPAND);//权限管理
	m_tree.Expand(sub_son1,TVE_EXPAND);//订单资料
	//m_tree.Expand(sub_son2,TVE_EXPAND);//账目流转
	//m_tree.Expand(sub_son7,TVE_EXPAND);//财务管理
	//m_tree.Expand(sub_son8,TVE_EXPAND);//仓库管理
	m_tree.SelectItem(sub_son6);

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
		if ((g_department.Compare("技术部意造")==0) || (g_department.Compare("技术部记梦馆")==0) ||  (g_department.Compare("生产部")==0))
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
	if(m_hWnd)
		return;
	writelog(log);
	CDialog::OnSize(nType, cx, cy);
	sprintf(log,"OnSize \t%s,%d",__FILE__,__LINE__);
	writelog(log);
	CRect m_rect;
	GetClientRect(m_rect);
	CRect rectlist(m_rect);
	CRect rectlistoutput(m_rect);
	CRect rectlisttotal(m_rect);
	CRect rectliststorage(m_rect);
	m_rect.DeflateRect(230,0,20,20);
	rectlist.DeflateRect(0,50,250,20);
	rectlistoutput.DeflateRect(0,50,250,45);
	rectlisttotal.DeflateRect(0,m_rect.bottom-22,250,0);
	rectliststorage.DeflateRect(0,240,250,45);

	sprintf(log,"OnSize \t%s,%d",__FILE__,__LINE__);
	writelog(log);
	int i = 0;
	for(i=0;i<MAX_TREE_PAGE;i++)
	{
		if(m_treePages[i]==NULL)
		{
			return;
		}
			
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
	m_treePages[15]->MoveWindow(m_rect);
	((Dialog_List_Web*)(m_treePages[15]))->m_listweb.MoveWindow(rectlist);
	m_treePages[16]->MoveWindow(m_rect);
	((Dialog_Storage_In*)(m_treePages[16]))->m_listStorageIn.MoveWindow(rectliststorage);
	((Dialog_Storage_In*)(m_treePages[16]))->m_listTotal.MoveWindow(rectlisttotal);
	m_treePages[17]->MoveWindow(m_rect);
	((Dialog_Storage_Left*)(m_treePages[17]))->m_list_StorageLeft.MoveWindow(rectlistoutput);
	((Dialog_Storage_Left*)(m_treePages[17]))->m_listTotal.MoveWindow(rectlisttotal);
	m_treePages[18]->MoveWindow(m_rect);
	((Dialog_Storage_In_Detail*)(m_treePages[18]))->m_listStorageInDetail.MoveWindow(rectlist);
	((Dialog_Storage_In_Detail*)(m_treePages[16]))->m_listTotal.MoveWindow(rectlisttotal);
	m_treePages[19]->MoveWindow(m_rect);
	((Dialog_Storage_Out*)(m_treePages[19]))->m_listStorageIn.MoveWindow(rectliststorage);
	((Dialog_Storage_Out*)(m_treePages[19]))->m_listTotal.MoveWindow(rectlisttotal);
	m_treePages[20]->MoveWindow(m_rect);
	((Dialog_Storage_Out_Detail*)(m_treePages[20]))->m_listStorageInDetail.MoveWindow(rectlist);
	((Dialog_Storage_Out_Detail*)(m_treePages[20]))->m_listTotal.MoveWindow(rectlisttotal);
	m_treePages[21]->MoveWindow(m_rect);
	((Dialog_List_Shipping*)(m_treePages[21]))->m_listBaseInfo.MoveWindow(rectlist);
	m_treePages[22]->MoveWindow(m_rect);
	((Dialog_SendUser*)(m_treePages[22]))->m_listSendUser.MoveWindow(rectlist);
	m_treePages[21]->MoveWindow(m_rect);
	((Dialog_ListExpress*)(m_treePages[21]))->m_listBaseInfo.MoveWindow(rectlist);


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

	if(node_name=="LDD办公系统"){
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
	else if(node_name=="增加用户"){
		m_treePages[0]->ShowWindow(SW_SHOW);
		if(g_permission & PERMISSION)
		{
			CDialog_AddUser dlg;
			dlg.DoModal();
		}
		icurrentpage = 0;
	}
	else if(node_name=="修改权限"){
		m_treePages[0]->ShowWindow(SW_SHOW);
		if(g_permission & PERMISSION)
		{
			CDialog_Modify_Permission	dlg;
			dlg.DoModal();
		}
		icurrentpage = 0;
	}
	else if(node_name=="修改密码"){
		m_treePages[0]->ShowWindow(SW_SHOW);
		if(g_permission & PERMISSION)
		{
			CDialog_ModifyPW_Admin dlg;
			dlg.DoModal();
		}
		icurrentpage = 0;
	}
	else if(node_name=="查询权限" || node_name=="权限管理"){
		m_treePages[0]->ShowWindow(SW_SHOW);
		icurrentpage = 0;
	}
	else if(node_name=="删除用户"){
		m_treePages[0]->ShowWindow(SW_SHOW);
		if(g_permission & PERMISSION)
		{
			CDialog_Delete_User dlg;
			dlg.DoModal();
		}
		icurrentpage = 0;
	}
	else if(node_name=="新增订单"){
		m_treePages[6]->ShowWindow(SW_SHOW);
		icurrentpage = 6;
	}
	else if(node_name=="修改订单" ){
		m_treePages[7]->ShowWindow(SW_SHOW);
		icurrentpage = 7;
	}
	else if(node_name=="查询订单" || node_name=="订单资料"){
		m_treePages[1]->ShowWindow(SW_SHOW);
		icurrentpage = 1;
	}
	else if(node_name=="变更记录" ){
		m_treePages[10]->ShowWindow(SW_SHOW);
		icurrentpage = 10;
	}
	else if(node_name=="销单记录" ){
		m_treePages[12]->ShowWindow(SW_SHOW);
		icurrentpage = 12;
	}
	else if(node_name=="网络订单" ){
		m_treePages[15]->ShowWindow(SW_SHOW);
		icurrentpage = 15;
	}
	else if(node_name=="过账" || node_name=="账目流转"){
		m_treePages[2]->ShowWindow(SW_SHOW);
		icurrentpage = 2;
	}
	else if(node_name=="退账"){
		m_treePages[9]->ShowWindow(SW_SHOW);
		icurrentpage = 9;
	}
	else if(node_name=="在制品进度"){
		m_treePages[8]->ShowWindow(SW_SHOW);
		icurrentpage = 8;
	}
	else if(node_name=="订单进度"){
		m_treePages[3]->ShowWindow(SW_SHOW);
		icurrentpage = 3;
	}
	else if(node_name=="进度明细"){
		m_treePages[4]->ShowWindow(SW_SHOW);
		icurrentpage = 4;
	}
	else if(node_name=="产能统计"){
		m_treePages[5]->ShowWindow(SW_SHOW);
		icurrentpage = 5;
	}
	else if(node_name=="财务管理"){
		m_treePages[13]->ShowWindow(SW_SHOW);
		icurrentpage = 13;
	}
	else if(node_name=="收款开票"){
		m_treePages[13]->ShowWindow(SW_SHOW);
		if(g_permission & FI)
		{
			Dialog_FI_Proceeds dlg;
			dlg.DoModal();
		}		
		icurrentpage = 13;
	}
	else if(node_name=="核销"){
		m_treePages[11]->ShowWindow(SW_SHOW);
		icurrentpage = 11;
	}
	else if(node_name=="查询"){
		m_treePages[13]->ShowWindow(SW_SHOW);
		icurrentpage = 13;
	}
	else if(node_name=="明细"){
		m_treePages[14]->ShowWindow(SW_SHOW);
		icurrentpage = 14;
	}
	else if(node_name=="仓库管理" || node_name=="进货单"){
		m_treePages[16]->ShowWindow(SW_SHOW);
		icurrentpage = 16;
	}
	else if(node_name=="库存余额"){
		m_treePages[17]->ShowWindow(SW_SHOW);
		icurrentpage = 17;
	}
	else if(node_name=="进货明细"){
		m_treePages[18]->ShowWindow(SW_SHOW);
		icurrentpage = 18;
	}
	else if(node_name=="出库单"){
		m_treePages[19]->ShowWindow(SW_SHOW);
		icurrentpage = 19;
	}
	else if(node_name=="出库明细"){
		m_treePages[20]->ShowWindow(SW_SHOW);
		icurrentpage = 20;
	}
	else if(node_name=="发货管理" || node_name=="发货清单"){
		m_treePages[21]->ShowWindow(SW_SHOW);
		icurrentpage = 21;
	}
	else if(node_name=="经办人资料库"){
		m_treePages[22]->ShowWindow(SW_SHOW);
		icurrentpage = 22;
	}
	else if(node_name=="快递单打印"){
		m_treePages[23]->ShowWindow(SW_SHOW);
		icurrentpage = 23;
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
			if ((g_department.Compare("技术部意造")==0) || (g_department.Compare("技术部记梦馆")==0) ||  (g_department.Compare("生产部")==0))
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
