// CoalseamDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Drainage Methane Evaluate.h"
#include "CoalseamDlg.h"
#include "FuzzyFunctionTable.h"	//添加自定义库文件的头文件
#include "FactorAssessResult.h"	//添加数据类头文件
#include "Permea_ComputeDlg.h"  //添加透气性系数计算模块头文件

extern CFactorAssessResult m_G_FactorAssessResult;	//全局变量引用声明
// CCoalseamDlg 对话框

IMPLEMENT_DYNAMIC(CCoalseamDlg, CDialog)

CCoalseamDlg::CCoalseamDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCoalseamDlg::IDD, pParent)
	, nbreaktype(0)
	, strEvaluateresult(_T(""))
	, fPractical(0)
	, fWater(0)
	, fTemperature(0)
	, fPermeability(0)
	, p_dlg(NULL)	//初始化透气性计算模块对话框指针
{

}

CCoalseamDlg::~CCoalseamDlg()
{
	delete p_dlg;	//煤层特性模块消失后，计算对话框模块也消失（即其对象被析构）。
}

void CCoalseamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_BREAKTYPE, nbreaktype);
	DDX_Text(pDX, IDC_EDIT_EVARES, strEvaluateresult);
	DDX_Text(pDX, IDC_EDIT_PRACTICAL, fPractical);
	DDV_MinMaxDouble(pDX, fPractical, 0.0, 200);
	DDX_Text(pDX, IDC_EDIT_WATER, fWater);
	DDV_MinMaxDouble(pDX, fWater, 0.0, 100);
	DDX_Text(pDX, IDC_EDIT_TEMPERATURE, fTemperature);
	DDV_MinMaxDouble(pDX, fTemperature, -1000, 2000);
	DDX_Text(pDX, IDC_EDIT_PERMEABILITY, fPermeability);
	DDV_MinMaxDouble(pDX, fPermeability, 0.0, 10000);
}


BEGIN_MESSAGE_MAP(CCoalseamDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CCoalseamDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCoalseamDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_PERMEA_COMPUTE, &CCoalseamDlg::OnBnClickedPermeaCompute)
	ON_BN_CLICKED(IDC_RESET, &CCoalseamDlg::OnBnClickedReset)
END_MESSAGE_MAP()


// CCoalseamDlg 消息处理程序

void CCoalseamDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	
	//所有数据大于0时才开始分析
	if(fPermeability > 0 && fPractical > 0 && fTemperature > 0 && fWater > 0)
	{
		//计算破坏类型评价结果向量r_C1
		double r_C1[5] = {0};
		for(int i = 0; i < 5; i++)	//i为行标志
		{
			if(nbreaktype == i)
			{
				for(int j = 0; j < 5; j++)	//j为列标志
				{
					r_C1[j] = Table::Breaktype[i][j];
				}
			}
		}

		//计算煤的粒度的评价结果向量r_C2
		double r_C2[5] = {0};
		for(int i = 0; i < 5; i++)
		{
			r_C2[i] = Function::Partical::pf[i](fPractical);
		}

		//计算煤的水分的评价结果向量r_C3
		double r_C3[5] = {0};
		for(int i = 0; i < 5; i++)
		{
			r_C3[i] = Function::Water::pf[i](fWater);
		}
		
		//计算煤的温度的评价结果向量r_C4
		double r_C4[5] = {0};
		for(int i = 0; i < 5; i++)
		{
			r_C4[i] = Function::Temperature::pf[i](fTemperature);
		}

		//计算煤层透气性的评价结果向量r_B1
		double r_B1[5] = {0};
		for(int i = 0; i < 5; i++)
		{
			r_B1[i] = Function::Permeability::pf[i](fPermeability);
		}

		//模糊综合评价：第一步，C层因素分析
		//得到B2评价结果
		double * R_B2[] = {r_C1, r_C2, r_C3, r_C4};	
		double r_B2[5] = {0};
		Function::BasicFunction::Matrix_Multiply(Weight::W_B2, R_B2, r_B2, 4);

		//模糊综合评价：第二步，B层因素分析
		//得到A1评价结果
		double * R_A1[] = {r_B1, r_B2};	
		double r_A1[5] = {0};
		Function::BasicFunction::Matrix_Multiply(Weight::W_A1, R_A1, r_A1, 2);

		/////////////////////////////////////////////////将分析结果赋给全局变量(赋给数值而不是指针)//////////////////////////////////////////////////////
		extern CFactorAssessResult m_G_FactorAssessResult;
		for(int i = 0; i < 5; i++)
		{
			//最终分析结果
			m_G_FactorAssessResult.A[0][i] = r_A1[i]; //将A1结果赋值到全局变量
			//评价单元因素分析结果
			m_G_FactorAssessResult.B[0][i] = r_B1[i]; //将B1结果赋值到全局变量
			m_G_FactorAssessResult.C[0][i] = r_C1[i]; //将C1结果赋值到全局变量
			m_G_FactorAssessResult.C[1][i] = r_C2[i]; //将C2结果赋值到全局变量
			m_G_FactorAssessResult.C[2][i] = r_C3[i]; //将C3结果赋值到全局变量
			m_G_FactorAssessResult.C[3][i] = r_C4[i]; //将C4结果赋值到全局变量
		}
		//得出评价结果
		switch(m_G_FactorAssessResult.GetRank(m_G_FactorAssessResult.A[0]))
		{
		case 0:
			strEvaluateresult = _T("Level I ; good");
			break;
		case 1:
			strEvaluateresult = _T("Level II ; relatively good");
			break;
		case 2:
			strEvaluateresult = _T("Level III ; average");
			break;
		case 3:
			strEvaluateresult = _T("Level IV ; relatively bad");
			break;
		case 4:
			strEvaluateresult = _T("Level V ; bad");
			break;
		}
		//作测试用
		//strEvaluateresult.Format(_T("%f+%f+%f+%f+%f"),m_G_FactorAssessResult.A[0][0], m_G_FactorAssessResult.A[0][1], m_G_FactorAssessResult.A[0][2], m_G_FactorAssessResult.A[0][3], m_G_FactorAssessResult.A[0][4]);
		////////////////////////////////////////////在末尾判断是否完成数据的拷贝///////////////////////////////////////////
		m_G_FactorAssessResult.Isdone_Coalseam = true;  //已经分析
	}
	else
	{
		MessageBox(_T("The input data is wrong, please input again!"),_T("Tips"));
	}
	
	UpdateData(FALSE);
	
}

void CCoalseamDlg::OnBnClickedCancel()
{
	OnCancel();
}

void CCoalseamDlg::OnBnClickedPermeaCompute()
{
	extern CCoalseamDlg * p_G_Coalseam;
	//初始化定义的全局变量（瓦斯抽采综合能力对话框指针）
	p_G_Coalseam = this;

	//如果计算模块已经打开，则设置焦点
	if(p_dlg != NULL)
	{
		p_dlg->SetFocus();
		p_dlg->ShowWindow(SW_SHOW);
	}
	//如果计算模块未打开，则打开
	else
	{
		p_dlg = new CPermea_ComputeDlg();
		p_dlg->Create(IDD_PERMEABILITY_COMPUTE);
		p_dlg->ShowWindow(SW_SHOW);
	}	

}

//void CCoalseamDlg::OnBnClickedCompute()
//{
//	
//}

void CCoalseamDlg::OnBnClickedReset()
{
	//将所有值初始化为0再更新
	UpdateData(TRUE);
	//煤层破坏类型
	nbreaktype = 0;
	// 煤层特性评价结果
	strEvaluateresult = _T("");
	// 煤的粒度
	fPractical = 0;
	// 煤的水分
	fWater = 0;
	// 煤的温度
	fTemperature = 0;
	//煤的透气性
	fPermeability = 0;
	//将所有值重置为初始状态
	UpdateData(FALSE);
}
