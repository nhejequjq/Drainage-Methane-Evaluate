// Permea_ComputeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Drainage Methane Evaluate.h"
#include "Permea_ComputeDlg.h"
#include "CoalseamDlg.h"
#include "FactorAssessResult.h" //���������ͷ�ļ�
#include <math.h>


// CPermea_ComputeDlg �Ի���

IMPLEMENT_DYNAMIC(CPermea_ComputeDlg, CDialog)

CPermea_ComputeDlg::CPermea_ComputeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPermea_ComputeDlg::IDD, pParent)
	, fDrillflow(0)
	, fThickness(0)
	, fDrillDiameter(0)
	, fGaspressure(0)
	, fGascontent(0)
	, fInterval(0)
{

}

CPermea_ComputeDlg::~CPermea_ComputeDlg()
{
}

void CPermea_ComputeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, fDrillflow);
	DDV_MinMaxDouble(pDX, fDrillflow, 0, 1000);
	DDX_Text(pDX, IDC_EDIT14, fThickness);
	DDV_MinMaxDouble(pDX, fThickness, 0, 100);
	DDX_Text(pDX, IDC_EDIT15, fDrillDiameter);
	DDV_MinMaxDouble(pDX, fDrillDiameter, 0, 10);
	DDX_Text(pDX, IDC_EDIT16, fGaspressure);
	DDV_MinMaxDouble(pDX, fGaspressure, 0, 100);
	DDX_Text(pDX, IDC_EDIT17, fGascontent);
	DDV_MinMaxDouble(pDX, fGascontent, 0, 1000);
	DDX_Text(pDX, IDC_EDIT18, fInterval);
	DDV_MinMaxDouble(pDX, fInterval, 0, 100);
}


BEGIN_MESSAGE_MAP(CPermea_ComputeDlg, CDialog)
	ON_BN_CLICKED(IDC_PERMEA_COMPUTE, &CPermea_ComputeDlg::OnBnClickedPermeaCompute)
END_MESSAGE_MAP()


// CPermea_ComputeDlg ��Ϣ�������

void CPermea_ComputeDlg::OnBnClickedPermeaCompute()
{
	extern CCoalseamDlg * p_G_Coalseam;	//��������ȫ�ֱ���

	UpdateData(TRUE);
	p_G_Coalseam->UpdateData(TRUE);	//����ú�����ԶԻ��������пؼ�������
	//�������ģ�������������Ч�������
	if(fDrillDiameter > 0 && fDrillflow > 0 && fGascontent > 0 && fGaspressure > 0.1 && fInterval > 0 && fThickness > 0 )
	{
		extern CFactorAssessResult m_G_FactorAssessResult; //��������ȫ�ֱ���
		//�������A �� ����B
		double A = fDrillflow / (2 * 3.1415 * fThickness * (pow(fGaspressure, 2) - 0.01));
		double B = 4 * fInterval * pow(fGaspressure, 2) / (fGascontent * pow(fDrillDiameter, 2));
		//��ʼ�� F0 �� lumda
		double lumda = pow(A, 1.61) * pow(B, 0.61);
		double F0 = B * lumda;
		//����õ�ú��͸����
		p_G_Coalseam->fPermeability = m_G_FactorAssessResult.Cal_Permeability(A, B, lumda, F0);
	}
	else
	{
		MessageBox(_T("The input data is wrong, please input again!"),_T("Tips"));
	}
	p_G_Coalseam->UpdateData(FALSE);	//����ú�����ԶԻ�������������
	UpdateData(FALSE);	//���¼���ģ��Ի����е�����
}
