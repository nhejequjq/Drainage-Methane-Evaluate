#pragma once

class CFactorAssessResult
{
public:
	CFactorAssessResult(void);
	~CFactorAssessResult(void);
	double A[2][5]; //A�����������
	double B[5][5]; //B�����������
	double C[17][5]; //C�����������
	double D[10][5]; //D�����������
	bool Isdone_Coalseam;	//��ʶú���Ƿ�����
	bool Isdone_Drainagegas;//��ʶ��˹����ۺ������Ƿ�����
	bool Isdone_Infoinput;  //��ʶ��Ϣ¼���Ƿ����
	// �������صĽ�������������صȼ�
	int GetRank(double result[]);
	// ����ú��͸���Եĺ��������Զ�����������У�
	double Cal_Permeability(double A, double B, double lumda, double F0);
};
