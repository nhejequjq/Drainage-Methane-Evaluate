// CoalseamDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Drainage Methane Evaluate.h"
#include "CoalseamDlg.h"
#include "FuzzyFunctionTable.h"	//����Զ�����ļ���ͷ�ļ�
#include "FactorAssessResult.h"	//���������ͷ�ļ�
#include "Permea_ComputeDlg.h"  //���͸����ϵ������ģ��ͷ�ļ�

extern CFactorAssessResult m_G_FactorAssessResult;	//ȫ�ֱ�����������
// CCoalseamDlg �Ի���

IMPLEMENT_DYNAMIC(CCoalseamDlg, CDialog)

CCoalseamDlg::CCoalseamDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCoalseamDlg::IDD, pParent)
	, nbreaktype(0)
	, strEvaluateresult(_T(""))
	, fPractical(0)
	, fWater(0)
	, fTemperature(0)
	, fPermeability(0)
	, p_dlg(NULL)	//��ʼ��͸���Լ���ģ��Ի���ָ��
{

}

CCoalseamDlg::~CCoalseamDlg()
{
	delete p_dlg;	//ú������ģ����ʧ�󣬼���Ի���ģ��Ҳ��ʧ�����������������
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


// CCoalseamDlg ��Ϣ�������

void CCoalseamDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	
	//�������ݴ���0ʱ�ſ�ʼ����
	if(fPermeability > 0 && fPractical > 0 && fTemperature > 0 && fWater > 0)
	{
		//�����ƻ��������۽������r_C1
		double r_C1[5] = {0};
		for(int i = 0; i < 5; i++)	//iΪ�б�־
		{
			if(nbreaktype == i)
			{
				for(int j = 0; j < 5; j++)	//jΪ�б�־
				{
					r_C1[j] = Table::Breaktype[i][j];
				}
			}
		}

		//����ú�����ȵ����۽������r_C2
		double r_C2[5] = {0};
		for(int i = 0; i < 5; i++)
		{
			r_C2[i] = Function::Partical::pf[i](fPractical);
		}

		//����ú��ˮ�ֵ����۽������r_C3
		double r_C3[5] = {0};
		for(int i = 0; i < 5; i++)
		{
			r_C3[i] = Function::Water::pf[i](fWater);
		}
		
		//����ú���¶ȵ����۽������r_C4
		double r_C4[5] = {0};
		for(int i = 0; i < 5; i++)
		{
			r_C4[i] = Function::Temperature::pf[i](fTemperature);
		}

		//����ú��͸���Ե����۽������r_B1
		double r_B1[5] = {0};
		for(int i = 0; i < 5; i++)
		{
			r_B1[i] = Function::Permeability::pf[i](fPermeability);
		}

		//ģ���ۺ����ۣ���һ����C�����ط���
		//�õ�B2���۽��
		double * R_B2[] = {r_C1, r_C2, r_C3, r_C4};	
		double r_B2[5] = {0};
		Function::BasicFunction::Matrix_Multiply(Weight::W_B2, R_B2, r_B2, 4);

		//ģ���ۺ����ۣ��ڶ�����B�����ط���
		//�õ�A1���۽��
		double * R_A1[] = {r_B1, r_B2};	
		double r_A1[5] = {0};
		Function::BasicFunction::Matrix_Multiply(Weight::W_A1, R_A1, r_A1, 2);

		/////////////////////////////////////////////////�������������ȫ�ֱ���(������ֵ������ָ��)//////////////////////////////////////////////////////
		extern CFactorAssessResult m_G_FactorAssessResult;
		for(int i = 0; i < 5; i++)
		{
			//���շ������
			m_G_FactorAssessResult.A[0][i] = r_A1[i]; //��A1�����ֵ��ȫ�ֱ���
			//���۵�Ԫ���ط������
			m_G_FactorAssessResult.B[0][i] = r_B1[i]; //��B1�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.C[0][i] = r_C1[i]; //��C1�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.C[1][i] = r_C2[i]; //��C2�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.C[2][i] = r_C3[i]; //��C3�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.C[3][i] = r_C4[i]; //��C4�����ֵ��ȫ�ֱ���
		}
		//�ó����۽��
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
		//��������
		//strEvaluateresult.Format(_T("%f+%f+%f+%f+%f"),m_G_FactorAssessResult.A[0][0], m_G_FactorAssessResult.A[0][1], m_G_FactorAssessResult.A[0][2], m_G_FactorAssessResult.A[0][3], m_G_FactorAssessResult.A[0][4]);
		////////////////////////////////////////////��ĩβ�ж��Ƿ�������ݵĿ���///////////////////////////////////////////
		m_G_FactorAssessResult.Isdone_Coalseam = true;  //�Ѿ�����
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
	//��ʼ�������ȫ�ֱ�������˹����ۺ������Ի���ָ�룩
	p_G_Coalseam = this;

	//�������ģ���Ѿ��򿪣������ý���
	if(p_dlg != NULL)
	{
		p_dlg->SetFocus();
		p_dlg->ShowWindow(SW_SHOW);
	}
	//�������ģ��δ�򿪣����
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
	//������ֵ��ʼ��Ϊ0�ٸ���
	UpdateData(TRUE);
	//ú���ƻ�����
	nbreaktype = 0;
	// ú���������۽��
	strEvaluateresult = _T("");
	// ú������
	fPractical = 0;
	// ú��ˮ��
	fWater = 0;
	// ú���¶�
	fTemperature = 0;
	//ú��͸����
	fPermeability = 0;
	//������ֵ����Ϊ��ʼ״̬
	UpdateData(FALSE);
}
