#pragma once

class CFactorAssessResult
{
public:
	CFactorAssessResult(void);
	~CFactorAssessResult(void);
	double A[2][5]; //A层的所有因素
	double B[5][5]; //B层的所有因素
	double C[17][5]; //C层的所有因素
	double D[10][5]; //D层的所有因素
	bool Isdone_Coalseam;	//标识煤层是否评价
	bool Isdone_Drainagegas;//标识瓦斯抽采综合能力是否评价
	bool Isdone_Infoinput;  //标识信息录入是否完成
	// 根据因素的结果向量返回因素等级
	int GetRank(double result[]);
	// 计算煤层透气性的函数（在自定义的数据类中）
	double Cal_Permeability(double A, double B, double lumda, double F0);
};
