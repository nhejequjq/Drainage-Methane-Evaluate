// InfoInputDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Drainage Methane Evaluate.h"
#include "Drainage Methane EvaluateDlg.h"
#include "InfoInputDlg.h"
#include "FactorAssessResult.h"	//添加数据类


//引用声明主对话框全局指针 pMainViewDlg
extern CDrainageMethaneEvaluateDlg * pMainViewDlg;

// InfoInputDlg 对话框

IMPLEMENT_DYNAMIC(InfoInputDlg, CDialog)

InfoInputDlg::InfoInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(InfoInputDlg::IDD, pParent)
	, strPerson(_T(""))
	, strCompany(_T(""))
	, strCoalseam(_T(""))
{

}

InfoInputDlg::~InfoInputDlg()
{
}

void InfoInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TIME, m_DateTime);
	DDX_Text(pDX, IDC_EDIT_COMPANY, strCompany);
	DDV_MaxChars(pDX, strCompany, 50);
	DDX_Text(pDX, IDC_EDIT_COALSEAM, strCoalseam);
	DDV_MaxChars(pDX, strCoalseam, 50);
	DDX_Text(pDX, IDC_EDIT_PERSON, strPerson);
	DDV_MaxChars(pDX, strPerson, 30);
}


BEGIN_MESSAGE_MAP(InfoInputDlg, CDialog)
	ON_BN_CLICKED(IDCANCEL, &InfoInputDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDB_INPUT, &InfoInputDlg::OnBnClickedInput)
//	ON_EN_CHANGE(IDC_EDIT_PERSON, &InfoInputDlg::OnEnChangeEditPerson)
ON_NOTIFY(DTN_DATETIMECHANGE, IDC_TIME, &InfoInputDlg::OnDtnDatetimechangeTime)
ON_EN_CHANGE(IDC_EDIT_COMPANY, &InfoInputDlg::OnEnChangeEditCompany)
END_MESSAGE_MAP()


// InfoInputDlg 消息处理程序




void InfoInputDlg::OnBnClickedCancel()
{
	OnCancel();
}

void InfoInputDlg::OnBnClickedInput()
{
	UpdateData(TRUE);
	extern CFactorAssessResult m_G_FactorAssessResult;	//引用全局声明
	
	if(strCompany != _T("") && strCoalseam != _T("") && strPerson != _T(""))
	{
		MessageBox(_T("Information has been recorded!"),_T("Tips"),MB_OK);
		CTime time;  
		m_DateTime.GetTime(time);  
		//将录入的信息赋给主界面对话框对象
		pMainViewDlg->time = time;
		pMainViewDlg->strCompany = strCompany;
		pMainViewDlg->strCoalseam = strCoalseam;
		pMainViewDlg->strPerson = strPerson;
		OnOK();
		m_G_FactorAssessResult.Isdone_Infoinput = true;	//信息已录入
	}
	else
	{
		MessageBox(_T("Please complete the above information!"),_T("Tips"),MB_OK);
	}

	UpdateData(FALSE);
}


void InfoInputDlg::OnDtnDatetimechangeTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void InfoInputDlg::OnEnChangeEditCompany()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
