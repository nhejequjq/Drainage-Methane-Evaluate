#include "StdAfx.h"
#include "FactorAssessResult.h"
#include <cmath>	//包含数学库

CFactorAssessResult::CFactorAssessResult(void)
{
	//将其成员的值全部初始化为-1
	//A层所有因素的初始化
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 5; j++)
			A[i][j] = -1;
	//B层所有因素的初始化
	for(int i = 0; i < 5; i++)
		for(int j = 0; j < 5; j++)
			B[i][j] = -1;
	//C层所有因素的初始化
	for(int i = 0; i < 17; i++)
		for(int j = 0; j < 5; j++)
			C[i][j] = -1;
	//D层所有因素的初始化
	for(int i = 0; i < 10; i++)
		for(int j = 0; j < 5; j++)
			D[i][j] = -1;
	Isdone_Coalseam = false; //默认未评价
	Isdone_Drainagegas = false; //默认未评价
	Isdone_Infoinput = false;   //默认未评价
}

CFactorAssessResult::~CFactorAssessResult(void)
{
}

// 根据因素的结果向量返回因素等级
int CFactorAssessResult::GetRank(double result[])
{
	int MaxIndex = 0;
	for(int i = 0; i < 5 ; i++)
		if(result[i] > result[MaxIndex])
			MaxIndex = i;
	return MaxIndex;
}

// 计算煤层透气性的函数（在自定义的数据类中）
double CFactorAssessResult::Cal_Permeability(double A, double B, double lumda, double F0)
{
	if(F0 >= (double)powf(10,-2) && F0 < (double)powf(10,0))
	{
		//更新lumda 和 F0
		lumda = powf(A, 1.61) * powf(B, 0.61);
		F0 = B * lumda;
		//进行下一步校验
		if(F0 >= powf(10,-2) && F0 < powf(10,0))	//校验合格，返回结果
			return lumda;
		else	//校验不合格，迭代函数，直至合格
			return Cal_Permeability(A, B, lumda, F0);
	}
	else if(F0 >= powf(10,0) && F0 < powf(10,1))
	{
		//更新lumda 和 F0
		lumda = powf(A, 1.39) * powf(B, 0.39);
		F0 = B * lumda;
		//进行下一步校验
		if(F0 >= powf(10,0) && F0 < powf(10,1))	//校验合格，返回结果
			return lumda;
		else	//校验不合格，迭代函数，直至合格
			return Cal_Permeability(A, B, lumda, F0);
	}
	else if(F0 >= powf(10,1) && F0 < powf(10,2))
	{
		//更新lumda 和 F0
		lumda = 1.10 * powf(A, 1.25) * powf(B, 0.25);
		F0 = B * lumda;
		//进行下一步校验
		if(F0 >= powf(10,1) && F0 < powf(10,2))	//校验合格，返回结果
			return lumda;
		else	//校验不合格，迭代函数，直至合格
			return Cal_Permeability(A, B, lumda, F0);
	}
	else if(F0 >= powf(10,2) && F0 < powf(10,3))
	{
		//更新lumda 和 F0
		lumda = 1.83 * powf(A, 1.14) * powf(B, 0.14);
		F0 = B * lumda;
		//进行下一步校验
		if(F0 >= powf(10,2) && F0 < powf(10,3))	//校验合格，返回结果
			return lumda;
		else	//校验不合格，迭代函数，直至合格
			return Cal_Permeability(A, B, lumda, F0);
	}
	else if(F0 >= powf(10,3) && F0 < powf(10,5))
	{
		//更新lumda 和 F0
		lumda = 2.10 * powf(A, 1.11) * powf(B, 0.11);
		F0 = B * lumda;
		//进行下一步校验
		if(F0 >= powf(10,3) && F0 < powf(10,5))	//校验合格，返回结果
			return lumda;
		else	//校验不合格，迭代函数，直至合格
			return Cal_Permeability(A, B, lumda, F0);
	}
	else if(F0 >= powf(10,5) && F0 < powf(10,7))
	{
		//更新lumda 和 F0
		lumda = 3.14 * powf(A, 1.07) * powf(B, 0.07);
		F0 = B * lumda;
		//进行下一步校验
		if(F0 >= powf(10,5) && F0 < powf(10,7))	//校验合格，返回结果
			return lumda;
		else	//校验不合格，迭代函数，直至合格
			return Cal_Permeability(A, B, lumda, F0);
	}
	else 
		VERIFY(true);	//断言错误
}

