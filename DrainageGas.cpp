// DrainageGas.cpp : 实现文件
//

#include "stdafx.h"
#include "Drainage Methane Evaluate.h"
#include "DrainageGas.h"
#include "FuzzyFunctionTable1.h"	//定义煤层瓦斯抽采综合能力自定义库的头文件
#include "WorkflowDlg.h"	//添加工况流量计算模块对话框头文件
#include "FactorAssessResult.h"    //添加分析结果数据类头文件

extern CFactorAssessResult m_G_FactorAssessResult;	//引用声明全局变量
// CDrainageGas 对话框

IMPLEMENT_DYNAMIC(CDrainageGas, CDialog)

CDrainageGas::CDrainageGas(CWnd* pParent /*=NULL*/)
	: CDialog(CDrainageGas::IDD, pParent)
	, nMethod(0)
	, strAssessResult(_T(""))
	, nDiameter(0)
	, fInterval(0)
	, nSealtechnology(0)
	, nUniformity(0)
	, nControlrange(0)
	, fNetability(0)
	, nNetsafety(0)
	, nMonitor(0)
	, nResponsibility(0)
	, nExamine(0)
	, nMeeting(0)
	, nCheck(0)
	, nTraincount(0)
	, nCertification(0)
	, nScheme(0)
	, nImplementation(0)
	, p_dlg(NULL)	//初始化计算模块对话框指针
	, fWorkflow(0)
	, fRunningpump(0)
	, fReadypump(0)
	, fMaxpump(0)
{

}

CDrainageGas::~CDrainageGas()
{
	delete p_dlg;	//瓦斯抽采综合能力模块消失后，计算对话框模块也消失（即其对象被析构）。
}

void CDrainageGas::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_METHOD, nMethod);
	DDX_Text(pDX, IDC_EDIT_ASSESSRESULT, strAssessResult);
	DDV_MaxChars(pDX, strAssessResult, 100);
	DDX_CBIndex(pDX, IDC_DIAMETER, nDiameter);
	DDX_Text(pDX, IDC_EIDT_INTERVAL, fInterval);
	DDV_MinMaxDouble(pDX, fInterval, 0.0, 100);
	DDX_CBIndex(pDX, IDC_SEALTECH, nSealtechnology);
	DDX_CBIndex(pDX, IDC_UNIFORMITY, nUniformity);
	DDX_CBIndex(pDX, IDC_CONTROLRANGE, nControlrange);
	DDX_Text(pDX, IDC_EDIT_NETABILITY, fNetability);
	DDV_MinMaxDouble(pDX, fNetability, 0, 100000);
	DDX_CBIndex(pDX, IDC_NETSAFETY, nNetsafety);
	DDX_CBIndex(pDX, IDC_MONITOR, nMonitor);
	DDX_CBIndex(pDX, IDC_RESPONSIBILITY, nResponsibility);
	DDX_CBIndex(pDX, IDC_EXAMINE, nExamine);
	DDX_CBIndex(pDX, IDC_MEETING, nMeeting);
	DDX_CBIndex(pDX, IDC_CHECK, nCheck);
	DDX_CBIndex(pDX, IDC_TRAIN, nTraincount);
	DDV_MinMaxInt(pDX, nTraincount, 0, 1000);
	DDX_CBIndex(pDX, IDC_CERTIFICATION, nCertification);
	DDX_CBIndex(pDX, IDC_SCHEME, nScheme);
	DDX_CBIndex(pDX, IDC_IMPLEMENTATION, nImplementation);
	DDX_Text(pDX, IDC_EDIT_WORKFLOW, fWorkflow);
	DDV_MinMaxDouble(pDX, fWorkflow, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_RUNNINGPUMP, fRunningpump);
	DDV_MinMaxDouble(pDX, fRunningpump, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_READYPUMP, fReadypump);
	DDV_MinMaxDouble(pDX, fReadypump, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_MAXPUMP, fMaxpump);
	DDV_MinMaxDouble(pDX, fMaxpump, 0, 10000);
}


BEGIN_MESSAGE_MAP(CDrainageGas, CDialog)
	ON_BN_CLICKED(ID_ASSESS, &CDrainageGas::OnBnClickedAssess)
	ON_BN_CLICKED(IDC_CANCEL_GAS, &CDrainageGas::OnBnClickedCancelGas)
	ON_CBN_SELCHANGE(IDC_METHOD, &CDrainageGas::OnCbnSelchangeMethod)
	ON_BN_CLICKED(IDC_WORKFLOW_COMPUTE, &CDrainageGas::OnBnClickedWorkflowCompute)
	ON_BN_CLICKED(IDC_RESET_GAS, &CDrainageGas::OnBnClickedResetGas)
	ON_CBN_SELCHANGE(IDC_EXAMINE, &CDrainageGas::OnCbnSelchangeExamine)
END_MESSAGE_MAP()


// CDrainageGas 消息处理程序

void CDrainageGas::OnBnClickedAssess()
{
	UpdateData(TRUE);

	//容错性判别
	//如果数据量都>0，则进行计算
	if(fInterval > 0 && fMaxpump > 0 && fNetability > 0 && fReadypump > 0 && fRunningpump > 0 && fWorkflow > 0)
	{
		//计算抽采方法评价结果向量r_C5
		double r_C5[5] = {0};
		for(int i = 0; i < 2; i++)	//i为行标志
		{
			if(nMethod == i)
			{
				for(int j = 0; j < 5; j++)	//j为列标志
				{
					r_C5[j] = Table_1::Method[i][j];
				}
			}
		}
		//计算钻孔直径评价结果向量r_C6
		double r_C6[5] = {0};
		for(int i = 0; i < 5; i++)	//i为行标志
		{
			if(nDiameter == i)
			{
				for(int j = 0; j < 5; j++)	//j为列标志
				{
					r_C6[j] = Table_1::Diameter[i][j];
				}
			}
		}
		//计算钻孔间距的评价结果向量r_C7
		double r_C7[5] = {0};
		for(int i = 0; i < 5; i++)
		{
			r_C7[i] = Function_1::Interval::pf[i](fInterval);
		}
		//计算封孔技术评价结果向量r_C8
		double r_C8[5] = {0};
		for(int i = 0; i < 4; i++)	//i为行标志
		{
			if( nSealtechnology== i)
			{
				for(int j = 0; j < 5; j++)	//j为列标志
				{
					r_C8[j] = Table_1::Sealtechnology[i][j];
				}
			}
		}
		//计算布孔均匀程度评价结果向量r_C9
		double r_C9[5] = {0};
		for(int i = 0; i < 3; i++)	//i为行标志
		{
			if( nUniformity== i)
			{
				for(int j = 0; j < 5; j++)	//j为列标志
				{
					r_C9[j] = Table_1::Uniformity[i][j];
				}
			}
		}
		//计算钻孔控制范围评价结果向量r_C10
		double r_C10[5] = {0};
		for(int i = 0; i < 3; i++)	//i为行标志
		{
			if( nControlrange== i)
			{
				for(int j = 0; j < 5; j++)	//j为列标志
				{
					r_C10[j] = Table_1::Controlrange[i][j];
				}
			}
		}
		//计算管网能力的评价结果向量r_C12
		double r_C12[5] = {0};
		for(int i = 0; i < 5; i++)
		{
			r_C12[i] = Function_1::Netability::pf[i](fNetability);
		}
		//计算管理安全装置合理性评价结果向量r_C13
		double r_C13[5] = {0};
		for(int i = 0; i < 3; i++)	//i为行标志
		{
			if( nNetsafety== i)
			{
				for(int j = 0; j < 5; j++)	//j为列标志
				{
					r_C13[j] = Table_1::Netsafety[i][j];
				}
			}
		}
		//计算抽采监控系统合理性评价结果向量r_C14
		double r_C14[5] = {0};
		for(int i = 0; i < 3; i++)	//i为行标志
		{
			if( nMonitor== i)
			{
				for(int j = 0; j < 5; j++)	//j为列标志
				{
					r_C14[j] = Table_1::Monitor[i][j];
				}
			}
		}
		//计算责任制合理性评价结果向量r_D3
		double r_D3[5] = {0};
		for(int i = 0; i < 3; i++)	//i为行标志
		{
			if( nResponsibility== i)
			{
				for(int j = 0; j < 5; j++)	//j为列标志
				{
					r_D3[j] = Table_1::Responsibility[i][j];
				}
			}
		}
		//计算考核奖惩制合理性评价结果向量r_D4
		double r_D4[5] = {0};
		for(int i = 0; i < 3; i++)	//i为行标志
		{
			if( nExamine== i)
			{
				for(int j = 0; j < 5; j++)	//j为列标志
				{
					r_D4[j] = Table_1::Examine[i][j];
				}
			}
		}
		//计算例会制合理性评价结果向量r_D6
		double r_D6[5] = {0};
		for(int i = 0; i < 3; i++)	//i为行标志
		{
			if( nMeeting== i)
			{
				for(int j = 0; j < 5; j++)	//j为列标志
				{
					r_D6[j] = Table_1::Meeting[i][j];
				}
			}
		}
		//检查验收制合理性评价结果向量r_D5
		double r_D5[5] = {0};
		for(int i = 0; i < 3; i++)	//i为行标志
		{
			if( nCheck== i)
			{
				for(int j = 0; j < 5; j++)	//j为列标志
				{
					r_D5[j] = Table_1::Check[i][j];
				}
			}
		}
		//人均年内培训次数评价结果向量r_D7
		double r_D7[5] = {0};
		for(int i = 0; i < 3; i++)	//i为行标志
		{
			if( nTraincount== i)
			{
				for(int j = 0; j < 5; j++)	//j为列标志
				{
					r_D7[j] = Table_1::Traincount[i][j];
				}
			}
		}
		//人员持证上岗率评价结果向量r_D8
		double r_D8[5] = {0};
		for(int i = 0; i < 3; i++)	//i为行标志
		{
			if( nCertification== i)
			{
				for(int j = 0; j < 5; j++)	//j为列标志
				{
					r_D8[j] = Table_1::Certification[i][j];
				}
			}
		}
		//抽采达标规划完善度评价结果向量r_D9
		double r_D9[5] = {0};
		for(int i = 0; i < 3; i++)	//i为行标志
		{
			if( nScheme== i)
			{
				for(int j = 0; j < 5; j++)	//j为列标志
				{
					r_D9[j] = Table_1::Scheme[i][j];
				}
			}
		}
		//年度实施计划完善度评价结果向量r_D10
		double r_D10[5] = {0};
		for(int i = 0; i < 3; i++)	//i为行标志
		{
			if( nImplementation== i)
			{
				for(int j = 0; j < 5; j++)	//j为列标志
				{
					r_D10[j] = Table_1::Implementation[i][j];
				}
			}
		}
		//计算运行泵能力的评价结果向量r_D1
		double r_D1[5] = {0};
		r_D1[0] = Function_1::BasicFunction_1::Fuzzy_S(fRunningpump, fWorkflow * Function_1::Para_1::Para_Runningpump[0][0], fWorkflow * Function_1::Para_1::Para_Runningpump[0][1]);
		r_D1[1] = Function_1::BasicFunction_1::Fuzzy_PI(fRunningpump, fWorkflow * Function_1::Para_1::Para_Runningpump[1][0], fWorkflow * Function_1::Para_1::Para_Runningpump[1][1]);
		r_D1[2] = Function_1::BasicFunction_1::Fuzzy_PI(fRunningpump, fWorkflow * Function_1::Para_1::Para_Runningpump[2][0], fWorkflow * Function_1::Para_1::Para_Runningpump[2][1]);
		r_D1[3] = Function_1::BasicFunction_1::Fuzzy_PI(fRunningpump, fWorkflow * Function_1::Para_1::Para_Runningpump[3][0], fWorkflow * Function_1::Para_1::Para_Runningpump[3][1]);
		r_D1[4] = Function_1::BasicFunction_1::Fuzzy_Z(fRunningpump, fWorkflow * Function_1::Para_1::Para_Runningpump[4][0], fWorkflow * Function_1::Para_1::Para_Runningpump[4][1]);
		
		//计算备用泵能力的评价结果向量r_D2
		double r_D2[5] = {0};
		r_D2[0] = Function_1::BasicFunction_1::Fuzzy_S(fReadypump, fMaxpump * Function_1::Para_1::Para_Readypump[0][0], fMaxpump * Function_1::Para_1::Para_Readypump[0][1]);
		r_D2[1] = Function_1::BasicFunction_1::Fuzzy_PI(fReadypump, fMaxpump * Function_1::Para_1::Para_Readypump[1][0], fMaxpump * Function_1::Para_1::Para_Readypump[1][1]);
		r_D2[2] = Function_1::BasicFunction_1::Fuzzy_PI(fReadypump, fMaxpump * Function_1::Para_1::Para_Readypump[2][0], fMaxpump * Function_1::Para_1::Para_Readypump[2][1]);
		r_D2[3] = Function_1::BasicFunction_1::Fuzzy_PI(fReadypump, fMaxpump * Function_1::Para_1::Para_Readypump[3][0], fMaxpump * Function_1::Para_1::Para_Readypump[3][1]);
		r_D2[4] = Function_1::BasicFunction_1::Fuzzy_Z(fReadypump, fMaxpump * Function_1::Para_1::Para_Readypump[4][0], fMaxpump * Function_1::Para_1::Para_Readypump[4][1]);
		
		////////////////////////////////////////////////////进行模糊综合评价///////////////////////////////////////////////////
		//模糊综合评价：第一步，D层因素分析
		//得到C11评价结果
		double * R_C11[] = {r_D1, r_D2};	//评价矩阵	
		double r_C11[5] = {0};	//评价结果
		Function_1::BasicFunction_1::Matrix_Multiply(Weight_1::W_C11, R_C11, r_C11, 2);
		//得到C15评价结果
		double * R_C15[] = {r_D3, r_D4, r_D5, r_D6};	//评价矩阵	
		double r_C15[5] = {0};	//评价结果
		Function_1::BasicFunction_1::Matrix_Multiply(Weight_1::W_C15, R_C15, r_C15, 4);
		//得到C16评价结果
		double * R_C16[] = {r_D7, r_D8};	//评价矩阵	
		double r_C16[5] = {0};	//评价结果
		Function_1::BasicFunction_1::Matrix_Multiply(Weight_1::W_C16, R_C16, r_C16, 2);
		//得到C17评价结果
		double * R_C17[] = {r_D9, r_D10};	//评价矩阵	
		double r_C17[5] = {0};	//评价结果
		Function_1::BasicFunction_1::Matrix_Multiply(Weight_1::W_C17, R_C17, r_C17, 2);

		//模糊综合评价：第二步，C层因素分析
		//得到B3评价结果
		double * R_B3[] = {r_C5, r_C6, r_C7, r_C8, r_C9, r_C10};	
		double r_B3[5] = {0};
		Function_1::BasicFunction_1::Matrix_Multiply(Weight_1::W_B3, R_B3, r_B3, 6);
		//得到B4评价结果
		double * R_B4[] = {r_C11, r_C12, r_C13, r_C14};	
		double r_B4[5] = {0};
		Function_1::BasicFunction_1::Matrix_Multiply(Weight_1::W_B4, R_B4, r_B4, 4);
		//得到B5评价结果
		double * R_B5[] = {r_C15, r_C16, r_C17};	
		double r_B5[5] = {0};
		Function_1::BasicFunction_1::Matrix_Multiply(Weight_1::W_B5, R_B5, r_B5, 3);

		//模糊综合评价：第三步，B层因素分析
		//得到A2评价结果
		double * R_A2[] = {r_B3, r_B4, r_B5};	
		double r_A2[5] = {0};
		Function_1::BasicFunction_1::Matrix_Multiply(Weight_1::W_A2, R_A2, r_A2, 3);

		/////////////////////////////////////////////////将分析结果赋给全局变量(赋给数值而不是指针)//////////////////////////////////////////////////////

		for(int i = 0; i < 5; i++)
		{
			//最终分析结果
			m_G_FactorAssessResult.A[1][i] = r_A2[i]; //将A1结果赋值到全局变量
			//评价单元因素分析结果
			m_G_FactorAssessResult.C[4][i] = r_C5[i]; //将C5结果赋值到全局变量
			m_G_FactorAssessResult.C[5][i] = r_C6[i]; //将C6结果赋值到全局变量
			m_G_FactorAssessResult.C[6][i] = r_C7[i]; //将C7结果赋值到全局变量
			m_G_FactorAssessResult.C[7][i] = r_C8[i]; //将C8结果赋值到全局变量
			m_G_FactorAssessResult.C[8][i] = r_C9[i]; //将C9结果赋值到全局变量
			m_G_FactorAssessResult.C[9][i] = r_C10[i]; //将C10结果赋值到全局变量
			m_G_FactorAssessResult.D[0][i] = r_D1[i]; //将D1结果赋值到全局变量
			m_G_FactorAssessResult.D[1][i] = r_D2[i]; //将D2结果赋值到全局变量
			m_G_FactorAssessResult.C[11][i] = r_C12[i]; //将C12结果赋值到全局变量
			m_G_FactorAssessResult.C[12][i] = r_C13[i]; //将C13结果赋值到全局变量
			m_G_FactorAssessResult.C[13][i] = r_C14[i]; //将C14结果赋值到全局变量
			m_G_FactorAssessResult.D[2][i] = r_D3[i]; //将D3结果赋值到全局变量
			m_G_FactorAssessResult.D[3][i] = r_D4[i]; //将D4结果赋值到全局变量
			m_G_FactorAssessResult.D[4][i] = r_D5[i]; //将D5结果赋值到全局变量
			m_G_FactorAssessResult.D[5][i] = r_D6[i]; //将D6结果赋值到全局变量
			m_G_FactorAssessResult.D[6][i] = r_D7[i]; //将D7结果赋值到全局变量
			m_G_FactorAssessResult.D[7][i] = r_D8[i]; //将D8结果赋值到全局变量
			m_G_FactorAssessResult.D[8][i] = r_D9[i]; //将D9结果赋值到全局变量
			m_G_FactorAssessResult.D[9][i] = r_D10[i]; //将D10结果赋值到全局变量
		}
		//得出评价结果
		switch(m_G_FactorAssessResult.GetRank(m_G_FactorAssessResult.A[1]))
		{
		case 0:
			strAssessResult = _T("Level I ; good");
			break;
		case 1:
			strAssessResult = _T("Level II ; relatively good");
			break;
		case 2:
			strAssessResult = _T("Level III ; average");
			break;
		case 3:
			strAssessResult = _T("Level IV ; relatively bad");
			break;
		case 4:
			strAssessResult = _T("Level V ; bad");
			break;
		}
		//测试结果
		//strAssessResult.Format(_T("%2f+%2f+%2f+%2f+%2f"),m_G_FactorAssessResult.C[11][0],m_G_FactorAssessResult.C[11][1],m_G_FactorAssessResult.C[11][2],m_G_FactorAssessResult.C[11][3],m_G_FactorAssessResult.C[11][4]);
		m_G_FactorAssessResult.Isdone_Drainagegas = true;  //已经分析
	}
	else
	{
		MessageBox(_T("The input data is wrong, please input again!"),_T("Tips"));
	}
	UpdateData(FALSE);
}

void CDrainageGas::OnBnClickedCancelGas()
{
	OnCancel();
}

void CDrainageGas::OnCbnSelchangeMethod()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDrainageGas::OnBnClickedWorkflowCompute()
{
	extern CDrainageGas * p_G_DrainageGas;
	//初始化定义的全局变量（瓦斯抽采综合能力对话框指针）
	p_G_DrainageGas = this;

	//如果计算模块已经打开，则设置焦点
	if(p_dlg != NULL)
	{
		p_dlg->SetFocus();
		p_dlg->ShowWindow(SW_SHOW);
	}
	//如果计算模块未打开，则打开
	else
	{
		p_dlg = new CWorkflowDlg();
		p_dlg->Create(IDD_FLOWCOMPUTE);
		p_dlg->ShowWindow(SW_SHOW);
	}	
}

void CDrainageGas::OnBnClickedResetGas()
{
	//将所有值初始化为0再更新
	UpdateData(TRUE);
	
	//钻孔间距
	fInterval = 0;
	//最大一台单泵能力
	fMaxpump = 0;
	//管网能力
	fNetability = 0;
	//备用泵能力
	fReadypump = 0;
	//运行泵能力
	fRunningpump = 0;
	//工况流量
	fWorkflow = 0;
	//员工持证上岗率
	nCertification = 0;
	//检查验收制度
	nCheck = 0;
	//钻孔控制范围
	nControlrange = 0;
	//钻孔直径
	nDiameter = 0;
	//考核奖惩制度
	nExamine = 0;
	//年度实施计划
	nImplementation = 0;
	//例会制度
	nMeeting = 0;
	//抽采方法
	nMethod = 0;
	//抽采监控装置
	nMonitor = 0;
	//管路安全装置
	nNetsafety = 0;
	//责任制
	nResponsibility = 0;
	//抽采达标规划
	nScheme = 0;
	//封孔技术
	nSealtechnology = 0;
	//人均年内培训次数
	nTraincount = 0;
	//钻孔均匀程度
	nUniformity = 0;
	//计算模块对话框对象
	p_dlg = NULL;
	//瓦斯抽采综合能力评价结果
	strAssessResult = _T("");
	
	//将所有值重置为初始状态
	UpdateData(FALSE);
}

void CDrainageGas::OnCbnSelchangeExamine()
{
	// TODO: 在此添加控件通知处理程序代码
}
