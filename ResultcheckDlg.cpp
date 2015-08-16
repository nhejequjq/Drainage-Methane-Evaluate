// ResultcheckDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Drainage Methane Evaluate.h"
#include "ResultcheckDlg.h"
#include "Drainage Methane EvaluateDlg.h"	//添加主对话框类头文件
#include "FactorAssessResult.h"				//添加分析结果数据类头文件
#include "AdviseDlg.h"						//添加整改建议对话框头文件



// CResultcheckDlg 对话框

IMPLEMENT_DYNAMIC(CResultcheckDlg, CDialog)

CResultcheckDlg::CResultcheckDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CResultcheckDlg::IDD, pParent)
	, strAssesstime(_T(""))
	, strCompany(_T(""))
	, strCoalseam(_T(""))
	, strPerson(_T(""))
	, strCoalseamres(_T(""))
	, strDrainagegasres(_T(""))
	, strMatchres(_T(""))
{
	extern CDrainageMethaneEvaluateDlg * pMainViewDlg;  //引用全局声明主对话框指针
	extern CFactorAssessResult m_G_FactorAssessResult;	//引用全局声明分析结果数据类
	//初始化评价信息
	strAssesstime.Format(_T("%d/%d/%d"),pMainViewDlg->time.GetYear(),pMainViewDlg->time.GetMonth(),pMainViewDlg->time.GetDay());
	strCompany = pMainViewDlg->strCompany;
	strCoalseam = pMainViewDlg->strCoalseam;
	strPerson = pMainViewDlg->strPerson;
	//初始化评价结果
	//煤层特性评价结果
//////////////////////////////////////可以用函数简化///////////////////////////////////////
	int MaxIndex = 0;
	for(int i = 0; i < 5; i++)
	{
		if(m_G_FactorAssessResult.A[0][i] > m_G_FactorAssessResult.A[0][MaxIndex])
			MaxIndex = i;
	}
	switch(MaxIndex)
	{
	case 0:
		strCoalseamres = _T("Level I ; good");
		break;
	case 1:
		strCoalseamres = _T("Level II ; relatively good");
		break;
	case 2:
		strCoalseamres = _T("Level III ; average");
		break;
	case 3:
		strCoalseamres = _T("Level IV ; relatively bad");
		break;
	case 4:
		strCoalseamres = _T("Level V ; bad");
		break;
	}
	//瓦斯抽采综合能力评价结果
	int MaxIndex_1 = 0;
	for(int i = 0; i < 5-1; i++)
	{
		if(m_G_FactorAssessResult.A[1][i] > m_G_FactorAssessResult.A[1][MaxIndex_1])
			MaxIndex_1 = i;
	}
	switch(MaxIndex_1)
	{
	case 0:
		strDrainagegasres = _T("Level I ; good");
		break;
	case 1:
		strDrainagegasres = _T("Level II ; relatively good");
		break;
	case 2:
		strDrainagegasres = _T("Level III ; average");
		break;
	case 3:
		strDrainagegasres = _T("Level IV ; relatively bad");
		break;
	case 4:
		strDrainagegasres = _T("Level V ; bad");
		break;
	}
	//初始化匹配性结果
	if(MaxIndex > 0)
	{
		if(MaxIndex + MaxIndex_1 <= 4)
			strMatchres = _T("Matched");
		else
			strMatchres = _T("Not Matched");
	}
	else if(MaxIndex == 0)
	{
		if(MaxIndex + MaxIndex_1 <= 3)
			strMatchres = _T("Matched");
		else
			strMatchres = _T("Not Matched");
	}
	else
	{
		VERIFY(false);
	}
}

CResultcheckDlg::~CResultcheckDlg()
{
}

void CResultcheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ASSESSTIME, strAssesstime);
	DDX_Text(pDX, IDC_COMPANY, strCompany);
	DDX_Text(pDX, IDC_COALSEAM, strCoalseam);
	DDX_Text(pDX, IDC_PERSON, strPerson);
	DDX_Text(pDX, IDC_COALSEAMRES, strCoalseamres);
	DDX_Text(pDX, IDC_DRAINAGEGASRES, strDrainagegasres);
	DDX_Text(pDX, IDC_MATCHRES, strMatchres);
}


BEGIN_MESSAGE_MAP(CResultcheckDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CResultcheckDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CResultcheckDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CResultcheckDlg 消息处理程序

void CResultcheckDlg::OnBnClickedOk()
{
	OnOK();
}

void CResultcheckDlg::OnBnClickedButton1()
{
	CAdviseDlg dlg;
	dlg.DoModal();
}

