// Drainage Methane EvaluateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Drainage Methane Evaluate.h"
#include "Drainage Methane EvaluateDlg.h"
#include "InfoInputDlg.h"	//���������Ϣ¼��Ի���ͷ�ļ�
#include "CoalseamDLg.h"	//���ú�����۶Ի���ͷ�ļ�
#include "DrainageGas.h"	//�����˹����ۺ��������۶Ի���ͷ�ļ�
#include "ResultcheckDlg.h" //��ӽ���鿴�Ի���ͷ�ļ�
#include "FactorAssessResult.h" //������ط�������������ͷ�ļ�

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//������Ի���ָ���ȫ�ֱ���
CDrainageMethaneEvaluateDlg * pMainViewDlg = NULL;
//�����˹����ۺ������Ի����ȫ��ָ��
CDrainageGas * p_G_DrainageGas = NULL;
//���ú�����ԶԻ����ȫ��ָ��
CCoalseamDlg * p_G_Coalseam = NULL;
//������ط�������ṹ�����
CFactorAssessResult m_G_FactorAssessResult;//Ψһһ�������������m_G_FactorAssessResult����¼�����ó��Ľ��

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CDrainageMethaneEvaluateDlg �Ի���




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


// CDrainageMethaneEvaluateDlg ��Ϣ�������

BOOL CDrainageMethaneEvaluateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	//�����Ի���ָ��ָ�����Ի������
	pMainViewDlg = this;

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//���ϵͳ���˵�
	//CMenu menu;
	m_menu.LoadMenu(IDR_MENU_MAIN);
	SetMenu(&m_menu);
	m_menu.Detach();
	
	//��ӹ�����
	if (!m_wndtoolbar.CreateEx( this,TBSTYLE_FLAT,WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_SIZE_DYNAMIC | CBRS_FLYBY ) || !m_wndtoolbar.LoadToolBar(IDR_TOOLBAR) )
	{
		TRACE0("failed to create toolbar\n");
		return FALSE;
	}
	//m_wndtoolbar.ShowWindow(SW_SHOW);//��ʾ������
	m_wndtoolbar.SetButtonText(0,_T("Input Information"));
	m_wndtoolbar.SetButtonText(1,_T("Evaluate coal seam"));
	m_wndtoolbar.SetButtonText(2,_T("Comprehensive Capacity"));
	m_wndtoolbar.SetButtonText(3,_T("Check Result"));
	m_wndtoolbar.SetSizes(CSize(150,50),CSize(31,32));//���ð�ť�ߴ�͹�����ͼ��ߴ�
	m_wndtoolbar.EnableToolTips(TRUE);	//����ͼ����ʾ����
	
	//���״̬��
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

	//��ȡϵͳʱ��
	CTime t = CTime::GetCurrentTime(); 
	int year = t.GetYear();
	int month = t.GetMonth();
	int day = t.GetDay();
	CString str;
	str.Format(_T("%d/%d/%d"),year,month,day);
	//��ȡ״̬������
	m_statusbar.SetPaneText(2,_T("Date: ")+str);
	m_statusbar.SetPaneText(1,_T("Author: Xu Mingjing"));
	m_statusbar.SetPaneText(0,_T("The matching analysis system of comprehensive capacities of gas drainage V1.0"));

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);//�ػ湤��������
	


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDrainageMethaneEvaluateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	//�򿪽���Ի���֮ǰ��У���������ط��������ı����Ƿ���ȷ��ֵ��������ģ���Ƿ��Ѿ�������
	//��������������㣬�ſ�ʼ����
	if(m_G_FactorAssessResult.Isdone_Coalseam && m_G_FactorAssessResult.Isdone_Drainagegas && m_G_FactorAssessResult.Isdone_Infoinput)
	{
		CResultcheckDlg dlg;
		dlg.DoModal();
	}
	else
	{
		CString str;
		if(!m_G_FactorAssessResult.Isdone_Infoinput)	//��Ϣ¼��δ���
			str += _T("Input Information, ");
		if(!m_G_FactorAssessResult.Isdone_Coalseam)	//ú����������δ���
			str += _T("Evaluate Coal seam Characteristics, ");
		if(!m_G_FactorAssessResult.Isdone_Drainagegas)	//��˹����ۺ���������δ���
			str += _T("Evaluate Comprehensive Capacity of Gas Drainage ");
		MessageBox(_T("Please finish ") + str + _T("!"),_T("Tips"));
	}
}

void CDrainageMethaneEvaluateDlg::OnAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}
