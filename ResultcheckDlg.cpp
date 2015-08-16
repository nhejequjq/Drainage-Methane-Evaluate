// ResultcheckDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Drainage Methane Evaluate.h"
#include "ResultcheckDlg.h"
#include "Drainage Methane EvaluateDlg.h"	//������Ի�����ͷ�ļ�
#include "FactorAssessResult.h"				//��ӷ������������ͷ�ļ�
#include "AdviseDlg.h"						//������Ľ���Ի���ͷ�ļ�



// CResultcheckDlg �Ի���

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
	extern CDrainageMethaneEvaluateDlg * pMainViewDlg;  //����ȫ���������Ի���ָ��
	extern CFactorAssessResult m_G_FactorAssessResult;	//����ȫ�������������������
	//��ʼ��������Ϣ
	strAssesstime.Format(_T("%d/%d/%d"),pMainViewDlg->time.GetYear(),pMainViewDlg->time.GetMonth(),pMainViewDlg->time.GetDay());
	strCompany = pMainViewDlg->strCompany;
	strCoalseam = pMainViewDlg->strCoalseam;
	strPerson = pMainViewDlg->strPerson;
	//��ʼ�����۽��
	//ú���������۽��
//////////////////////////////////////�����ú�����///////////////////////////////////////
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
	//��˹����ۺ��������۽��
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
	//��ʼ��ƥ���Խ��
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


// CResultcheckDlg ��Ϣ�������

void CResultcheckDlg::OnBnClickedOk()
{
	OnOK();
}

void CResultcheckDlg::OnBnClickedButton1()
{
	CAdviseDlg dlg;
	dlg.DoModal();
}

