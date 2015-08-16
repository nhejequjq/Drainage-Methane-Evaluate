// Drainage Methane EvaluateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Drainage Methane Evaluate.h"
#include "Drainage Methane EvaluateDlg.h"
#include "InfoInputDlg.h"	//添加评价信息录入对话框头文件
#include "CoalseamDLg.h"	//添加煤层评价对话框头文件
#include "DrainageGas.h"	//添加瓦斯抽采综合能力评价对话框头文件
#include "ResultcheckDlg.h" //添加结果查看对话框头文件
#include "FactorAssessResult.h" //添加因素分析结果数据类的头文件

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//添加主对话框指针的全局变量
CDrainageMethaneEvaluateDlg * pMainViewDlg = NULL;
//添加瓦斯抽采综合能力对话框的全局指针
CDrainageGas * p_G_DrainageGas = NULL;
//添加煤层特性对话框的全局指针
CCoalseamDlg * p_G_Coalseam = NULL;
//添加因素分析结果结构体变量
CFactorAssessResult m_G_FactorAssessResult;//唯一一个数据类变量，m_G_FactorAssessResult来记录分析得出的结果

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDrainageMethaneEvaluateDlg 对话框




CDrainageMethaneEvaluateDlg::CDrainageMethaneEvaluateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDrainageMethaneEvaluateDlg::IDD, pParent)
	, time(0)
	, strCompany(_T(""))
	, strCoalseam(_T(""))
	, strPerson(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrainageMethaneEvaluateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDrainageMethaneEvaluateDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_INFOINPUT, &CDrainageMethaneEvaluateDlg::OnInfoinput)
	ON_COMMAND(ID_COALSEAM, &CDrainageMethaneEvaluateDlg::OnCoalseam)
	ON_COMMAND(ID_DRAINAGEGAS, &CDrainageMethaneEvaluateDlg::OnDrainagegas)
	ON_COMMAND(ID_RESULTCHECK, &CDrainageMethaneEvaluateDlg::OnResultcheck)
	ON_COMMAND(ID_ABOUT, &CDrainageMethaneEvaluateDlg::OnAbout)
END_MESSAGE_MAP()


// CDrainageMethaneEvaluateDlg 消息处理程序

BOOL CDrainageMethaneEvaluateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	//将主对话框指针指向主对话框对象
	pMainViewDlg = this;

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//添加系统主菜单
	//CMenu menu;
	m_menu.LoadMenu(IDR_MENU_MAIN);
	SetMenu(&m_menu);
	m_menu.Detach();
	
	//添加工具栏
	if (!m_wndtoolbar.CreateEx( this,TBSTYLE_FLAT,WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_SIZE_DYNAMIC | CBRS_FLYBY ) || !m_wndtoolbar.LoadToolBar(IDR_TOOLBAR) )
	{
		TRACE0("failed to create toolbar\n");
		return FALSE;
	}
	//m_wndtoolbar.ShowWindow(SW_SHOW);//显示工具栏
	m_wndtoolbar.SetButtonText(0,_T("Input Information"));
	m_wndtoolbar.SetButtonText(1,_T("Evaluate coal seam"));
	m_wndtoolbar.SetButtonText(2,_T("Comprehensive Capacity"));
	m_wndtoolbar.SetButtonText(3,_T("Check Result"));
	m_wndtoolbar.SetSizes(CSize(150,50),CSize(31,32));//设置按钮尺寸和工具栏图标尺寸
	m_wndtoolbar.EnableToolTips(TRUE);	//激活图标提示功能
	
	//添加状态栏
	static UINT nIndicators[3] = {
		ID_SEPARATOR,
		ID_SEPARATOR,
		ID_SEPARATOR
	};
	m_statusbar.Create(this);
	m_statusbar.SetIndicators(nIndicators,3);
	m_statusbar.SetPaneInfo(0,nIndicators[1],SBPS_POPOUT,500);
	m_statusbar.SetPaneInfo(1,nIndicators[1],SBPS_POPOUT,200);
	m_statusbar.SetPaneInfo(2,nIndicators[2],SBPS_POPOUT,500);

	//获取系统时间
	CTime t = CTime::GetCurrentTime(); 
	int year = t.GetYear();
	int month = t.GetMonth();
	int day = t.GetDay();
	CString str;
	str.Format(_T("%d/%d/%d"),year,month,day);
	//获取状态栏文字
	m_statusbar.SetPaneText(2,_T("Date: ")+str);
	m_statusbar.SetPaneText(1,_T("Author: Xu Mingjing"));
	m_statusbar.SetPaneText(0,_T("The matching analysis system of comprehensive capacities of gas drainage V1.0"));

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);//重绘工具栏窗口
	


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDrainageMethaneEvaluateDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDrainageMethaneEvaluateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDrainageMethaneEvaluateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDrainageMethaneEvaluateDlg::OnInfoinput()
{
	InfoInputDlg dlg;
	dlg.DoModal();
}

void CAboutDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CDrainageMethaneEvaluateDlg::OnCoalseam()
{
	CCoalseamDlg dlg;
	dlg.DoModal();
}

void CDrainageMethaneEvaluateDlg::OnDrainagegas()
{
	CDrainageGas dlg;
	dlg.DoModal();
}

void CDrainageMethaneEvaluateDlg::OnResultcheck()
{
	//打开结果对话框之前先校验所有因素分析结果类的变量是否被正确赋值并且三个模块是否已经分析；
	//如果上述条件满足，才开始分析
	if(m_G_FactorAssessResult.Isdone_Coalseam && m_G_FactorAssessResult.Isdone_Drainagegas && m_G_FactorAssessResult.Isdone_Infoinput)
	{
		CResultcheckDlg dlg;
		dlg.DoModal();
	}
	else
	{
		CString str;
		if(!m_G_FactorAssessResult.Isdone_Infoinput)	//信息录入未完成
			str += _T("Input Information, ");
		if(!m_G_FactorAssessResult.Isdone_Coalseam)	//煤层特性评价未完成
			str += _T("Evaluate Coal seam Characteristics, ");
		if(!m_G_FactorAssessResult.Isdone_Drainagegas)	//瓦斯抽采综合能力评价未完成
			str += _T("Evaluate Comprehensive Capacity of Gas Drainage ");
		MessageBox(_T("Please finish ") + str + _T("!"),_T("Tips"));
	}
}

void CDrainageMethaneEvaluateDlg::OnAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}
