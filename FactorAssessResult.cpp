#include "StdAfx.h"
#include "FactorAssessResult.h"
#include <cmath>	//������ѧ��

CFactorAssessResult::CFactorAssessResult(void)
{
	//�����Ա��ֵȫ����ʼ��Ϊ-1
	//A���������صĳ�ʼ��
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 5; j++)
			A[i][j] = -1;
	//B���������صĳ�ʼ��
	for(int i = 0; i < 5; i++)
		for(int j = 0; j < 5; j++)
			B[i][j] = -1;
	//C���������صĳ�ʼ��
	for(int i = 0; i < 17; i++)
		for(int j = 0; j < 5; j++)
			C[i][j] = -1;
	//D���������صĳ�ʼ��
	for(int i = 0; i < 10; i++)
		for(int j = 0; j < 5; j++)
			D[i][j] = -1;
	Isdone_Coalseam = false; //Ĭ��δ����
	Isdone_Drainagegas = false; //Ĭ��δ����
	Isdone_Infoinput = false;   //Ĭ��δ����
}

CFactorAssessResult::~CFactorAssessResult(void)
{
}

// �������صĽ�������������صȼ�
int CFactorAssessResult::GetRank(double result[])
{
	int MaxIndex = 0;
	for(int i = 0; i < 5 ; i++)
		if(result[i] > result[MaxIndex])
			MaxIndex = i;
	return MaxIndex;
}

// ����ú��͸���Եĺ��������Զ�����������У�
double CFactorAssessResult::Cal_Permeability(double A, double B, double lumda, double F0)
{
	if(F0 >= (double)powf(10,-2) && F0 < (double)powf(10,0))
	{
		//����lumda �� F0
		lumda = powf(A, 1.61) * powf(B, 0.61);
		F0 = B * lumda;
		//������һ��У��
		if(F0 >= powf(10,-2) && F0 < powf(10,0))	//У��ϸ񣬷��ؽ��
			return lumda;
		else	//У�鲻�ϸ񣬵���������ֱ���ϸ�
			return Cal_Permeability(A, B, lumda, F0);
	}
	else if(F0 >= powf(10,0) && F0 < powf(10,1))
	{
		//����lumda �� F0
		lumda = powf(A, 1.39) * powf(B, 0.39);
		F0 = B * lumda;
		//������һ��У��
		if(F0 >= powf(10,0) && F0 < powf(10,1))	//У��ϸ񣬷��ؽ��
			return lumda;
		else	//У�鲻�ϸ񣬵���������ֱ���ϸ�
			return Cal_Permeability(A, B, lumda, F0);
	}
	else if(F0 >= powf(10,1) && F0 < powf(10,2))
	{
		//����lumda �� F0
		lumda = 1.10 * powf(A, 1.25) * powf(B, 0.25);
		F0 = B * lumda;
		//������һ��У��
		if(F0 >= powf(10,1) && F0 < powf(10,2))	//У��ϸ񣬷��ؽ��
			return lumda;
		else	//У�鲻�ϸ񣬵���������ֱ���ϸ�
			return Cal_Permeability(A, B, lumda, F0);
	}
	else if(F0 >= powf(10,2) && F0 < powf(10,3))
	{
		//����lumda �� F0
		lumda = 1.83 * powf(A, 1.14) * powf(B, 0.14);
		F0 = B * lumda;
		//������һ��У��
		if(F0 >= powf(10,2) && F0 < powf(10,3))	//У��ϸ񣬷��ؽ��
			return lumda;
		else	//У�鲻�ϸ񣬵���������ֱ���ϸ�
			return Cal_Permeability(A, B, lumda, F0);
	}
	else if(F0 >= powf(10,3) && F0 < powf(10,5))
	{
		//����lumda �� F0
		lumda = 2.10 * powf(A, 1.11) * powf(B, 0.11);
		F0 = B * lumda;
		//������һ��У��
		if(F0 >= powf(10,3) && F0 < powf(10,5))	//У��ϸ񣬷��ؽ��
			return lumda;
		else	//У�鲻�ϸ񣬵���������ֱ���ϸ�
			return Cal_Permeability(A, B, lumda, F0);
	}
	else if(F0 >= powf(10,5) && F0 < powf(10,7))
	{
		//����lumda �� F0
		lumda = 3.14 * powf(A, 1.07) * powf(B, 0.07);
		F0 = B * lumda;
		//������һ��У��
		if(F0 >= powf(10,5) && F0 < powf(10,7))	//У��ϸ񣬷��ؽ��
			return lumda;
		else	//У�鲻�ϸ񣬵���������ֱ���ϸ�
			return Cal_Permeability(A, B, lumda, F0);
	}
	else 
		VERIFY(true);	//���Դ���
}

