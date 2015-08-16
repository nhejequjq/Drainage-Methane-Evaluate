// WorkflowDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Drainage Methane Evaluate.h"
#include "WorkflowDlg.h"
#include "DrainageGas.h"

// CWorkflowDlg 对话框

IMPLEMENT_DYNAMIC(CWorkflowDlg, CDialog)

CWorkflowDlg::CWorkflowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWorkflowDlg::IDD, pParent)
	, fFlow(0)
	, fPressure(0)
	, fConcentration(0)
	, fPressurepump(0)
{

}

CWorkflowDlg::~CWorkflowDlg()
{
}

void CWorkflowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, fFlow);
	DDV_MinMaxDouble(pDX, fFlow, 0, 10000);
	DDX_Text(pDX, IDC_EDIT2, fPressure);
	DDV_MinMaxDouble(pDX, fPressure, 0, 10000);
	DDX_Text(pDX, IDC_EDIT3, fConcentration);
	DDV_MinMaxDouble(pDX, fConcentration, 0, 100);
	DDX_Text(pDX, IDC_EDIT13, fPressurepump);
	DDV_MinMaxDouble(pDX, fPressurepump, 0, 10000);
}


BEGIN_MESSAGE_MAP(CWorkflowDlg, CDialog)
	ON_BN_CLICKED(IDC_COMPUTE, &CWorkflowDlg::OnBnClickedCompute)
END_MESSAGE_MAP()


// CWorkflowDlg 消息处理程序

void CWorkflowDlg::OnBnClickedCompute()
{
	extern CDrainageGas * p_G_DrainageGas;	//引用申明全局变量

	UpdateData(TRUE);
	p_G_DrainageGas->UpdateData(TRUE);	//读入瓦斯抽采综合能力对话框中所有控件的数据

	if(fConcentration > 0 &&  fPressure > 0 &&  fPressurepump > 0 &&  fFlow > 0  )
	{
		p_G_DrainageGas->fWorkflow = 100 * fFlow * 101.325 /(fConcentration * fPressure * fPressurepump);
	}
	else
	{
		MessageBox(_T("The input data is wrong, please input again!"),_T("Tips"));
	}
	p_G_DrainageGas->UpdateData(FALSE);	//更新瓦斯抽采综合能力对话框中所有数据
	UpdateData(FALSE);
}
