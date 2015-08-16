// AdviseDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Drainage Methane Evaluate.h"
#include "AdviseDlg.h"
#include "FactorAssessResult.h"  //���������

extern CFactorAssessResult m_G_FactorAssessResult;
// CAdviseDlg �Ի���

IMPLEMENT_DYNAMIC(CAdviseDlg, CDialog)

CAdviseDlg::CAdviseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdviseDlg::IDD, pParent)
	, strAdvise(_T(""))
{
	//��ʼ�����۵�Ԫ���صĽ��
	double * result[19] = {
		m_G_FactorAssessResult.C[4], m_G_FactorAssessResult.C[5], m_G_FactorAssessResult.C[6],
		m_G_FactorAssessResult.C[7], m_G_FactorAssessResult.C[8], m_G_FactorAssessResult.C[9],

		m_G_FactorAssessResult.D[0], m_G_FactorAssessResult.D[1],

		m_G_FactorAssessResult.C[11], m_G_FactorAssessResult.C[12], m_G_FactorAssessResult.C[13],

		m_G_FactorAssessResult.D[2], m_G_FactorAssessResult.D[3], m_G_FactorAssessResult.D[4],
		m_G_FactorAssessResult.D[5], m_G_FactorAssessResult.D[6], m_G_FactorAssessResult.D[7],
		m_G_FactorAssessResult.D[8], m_G_FactorAssessResult.D[9]
	};
	//��ʼ�����۵�Ԫ���ص����۵ȼ��Ľ��
	int Rank[19];
	for(int i = 0; i < 19; i++)
	{
		Rank[i] = m_G_FactorAssessResult.GetRank(result[i]);
	}
	//��ʼ�����۵�Ԫ���ص���ʾ�ַ�
	CString strTip[19] = {
		_T("\t>>Gas drainage method should be improved;\r\n"),
		_T("\t>>Appropriate increase extraction hole diameter;\r\n"),
		_T("\t>>Reduce the extraction borehole interval;\r\n"),
		_T("\t>>To improve the borehole sealing technology;\r\n"),
		_T("\t>>Uniform layout borehole;\r\n"),
		_T("\t>>Advance drilling control area;\r\n"),
		_T("\t>>Improve the capability of running pump;\r\n"),
		_T("\t>>Improve the capability of stand by pump;\r\n"),
		_T("\t>>Improve the ability of gas drainage network(pump negative control pressure);\r\n"),
		_T("\t>>Reasonable increase pipeline safety device or enhance its safety;\r\n"),
		_T("\t>>To increase the gas drainage monitoring system device;\r\n"),
		_T("\t>>Strengthen the rationality of the responsibility system;\r\n"),
		_T("\t>>To strengthen rationality of rewards and punishment system;\r\n"),
		_T("\t>>To strengthen rationality of acceptance checks system;\r\n"),
		_T("\t>>To strengthen rationality of regular meeting;\r\n"),
		_T("\t>>To strengthen rationality of training system;\r\n"),
		_T("\t>>Enhance the technical quality of staff, increase staff licensed rate;\r\n"),
		_T("\t>>Enhance the gas drainage standard plan perfectness;\r\n"),
		_T("\t>>Enhance the gas drainage implementation plan perfectness;\r\n"),
	};

	int RankA1 = m_G_FactorAssessResult.GetRank(m_G_FactorAssessResult.A[0]); //��ʶA1�ĵȼ�
	int RankA2 = m_G_FactorAssessResult.GetRank(m_G_FactorAssessResult.A[1]); //��ʶA2�ĵȼ�
	bool bMatch = false;	//��ʶ�Ƿ�ƥ��
	//����ƥ����
	if(RankA1 > 0)
	{
		if(RankA1 + RankA2 <= 4)
			bMatch = true; //ƥ��
		else
			bMatch = false; //��ƥ��
	}
	else if(RankA1 == 0)
	{
		if(RankA1 + RankA2 <= 3)
			bMatch = true; //ƥ��
		else
			bMatch = false; //��ƥ��
	}
	else
	{
		VERIFY(false);
	}
	//������ո����Ľ��鵽����Ի���
	strAdvise += _T(">>>>Improving comprehensive ability of gas drainage rectification are as follows:\r\n");
	if(bMatch == true) //���ƥ�䣬���ڵ��ļ��͵��弶��������ʾ
	{
		for(int i = 0; i < 19; i++)
			if(m_G_FactorAssessResult.GetRank(result[i]) >= 3)
				strAdvise += strTip[i];
	}
	else //�����ƥ�䣬��ƥ�������ʾ 
	{	
		switch(RankA1)
		{
		case 0:
			for(int i = 0; i < 19; i++)
				if(Rank[i] == 4)
					strAdvise += strTip[i];
			break;
		case 1:
			for(int i = 0; i < 19; i++)
				if(Rank[i] >= 3)
					strAdvise += strTip[i];
			break;
		case 2:
			for(int i = 0; i < 19; i++)
				if(Rank[i] >= 3)
					strAdvise += strTip[i];
			break;
		case 3:
			for(int i = 0; i < 19; i++)
				if(Rank[i] >= 2)
					strAdvise += strTip[i];
			break;
		case 4:
			for(int i = 0; i < 19; i++)
				if(Rank[i] >= 1)
					strAdvise += strTip[i];
			break;
		}
	}
}

CAdviseDlg::~CAdviseDlg()
{
}

void CAdviseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ADVISE, strAdvise);
}


BEGIN_MESSAGE_MAP(CAdviseDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAdviseDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAdviseDlg ��Ϣ�������

void CAdviseDlg::OnBnClickedOk()
{
	OnOK();
}
