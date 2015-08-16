
#ifndef _FUZZYFUNCTIONTABLE_H
#define _FUZZYFUNCTIONTABLE_H

/////////////////////////////////////////////该头文件只针对煤层特性评价模块/////////////////////////////////////////////
//包括所有模糊评价规则表的命名空间
namespace Table
{
	//破坏类型评价规则表
	double Breaktype[5][5] = {
		{0, 0, 0.1, 0.3, 1},
		{0, 0.1, 0.3, 1, 0.3},
		{0.1, 0.3, 1, 0.3, 0.1},
		{0.3, 1, 0.3, 0.1, 0},
		{1, 0.3, 0.1, 0, 0}
	};
	//抽采方法评价规则表
	double Method[2][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.6, 0.9, 0.6, 0.3, 0}
	};
}

//定义隶属函数的命名空间
namespace Function
{
	//定义基础的三类隶属函数S函数、Z函数、PI函数的命名空间
	namespace BasicFunction
	{
		//定义S函数
		double Fuzzy_S(double x, double a, double b)
		{
			//结果在[0,1]为正常，-1为异常情况
			if(a < b)
			{
				if(x <= a)	return 0;
				else if(x > a && x <= (a + b)/2)
					return 2*((x - a)/(b - a))*((x - a)/(b - a));
				else if(x > (a + b)/2 && x <= b)
					return 1 - 2*((x - b)/(b - a))*((x - b)/(b - a));
				else if(x > b)	return 1;
				else	return -1;	//异常则为-1
			}
			else
				return -1;	//异常则为-1
		}

		//定义Z函数
		double Fuzzy_Z(double x, double a, double b)
		{
			if(a < b && Fuzzy_S(x, a, b) != -1)
				return 1 - Fuzzy_S(x, a, b);
			else 
				return -1;	//结果为异常时
		}

		//定义PI函数
		double Fuzzy_PI(double x, double a, double b)
		{
			if(a < b)
			{
				if(x <= (a + b)/2 && Fuzzy_S(x, a, (a + b)/2) != -1)
					return	Fuzzy_S(x, a, (a + b)/2);
				else if(x > (a + b)/2 && Fuzzy_Z(x, (a + b)/2, b) != -1)
					return	Fuzzy_Z(x, (a + b)/2, b);
				else	
					return -1;	//结果为异常
			}
			else
				return -1;	//结果为异常
		}
		//定义矩阵的乘法（使用C语言方法实现）
		void Matrix_Multiply(double A[], double * B[], double C[], int p, int n = 5)	//A为向量，p为B矩阵行数,C为结果矩阵
		{
			//计算矩阵C=A*B
			for(int j = 0; j < n; j++)
			{
				for(int k = 0; k < p; k++)
				{
					C[j] += A[k] * B[k][j];
				}
			}
			return ;
		}
		
	}
	//每个评价单元因素所用到的三类隶属函数（S函数、Z函数、PI函数）的参数的命名空间
	namespace Para
	{
		//煤的粒度的隶属函数参数
		double Para_Partical[5][2] = {{0.1133,0.5},{0.2233,1.6667},{0.75,3.6667},{2.3333,6.5},{4.3333,7}};
		//煤的内在水分的隶属函数参数
		double Para_Water[5][2] = {{1,2.6667},{1.3333,5.3333},{3.3333,11.3333},{6.6667,22},{15,25}};
		//煤的内在温度的隶属函数参数
		double Para_Temperature[5][2] = {{46.66,60},{36.66,53.33},{26.66,43.33},{16.66,33.33},{10,23.33}};
		//煤层透气性的隶属函数参数
		double Para_Permeability[5][2] = {{70,150},{8,120},{0.07,13},{0.0008,0.12},{0.0001,0.0012}};
	}

	//分别定义煤的粒度的隶属度函数的命名空间
	namespace Partical
	{
		using namespace BasicFunction;
		using namespace Para;
		double Level_1(double x)
		{
			return	Fuzzy_PI( x, Para_Partical[0][0], Para_Partical[0][1]);
		}
		double Level_2(double x)
		{
			return	Fuzzy_PI( x, Para_Partical[1][0], Para_Partical[1][1]);
		}
		double Level_3(double x)
		{
			return	Fuzzy_PI( x, Para_Partical[2][0], Para_Partical[2][1]);
		}
		double Level_4(double x)
		{
			return	Fuzzy_PI( x, Para_Partical[3][0], Para_Partical[3][1]);
		}
		double Level_5(double x)
		{
			return	Fuzzy_S( x, Para_Partical[4][0], Para_Partical[4][1]);
		}
		//用函数指针数组(*pf[5])初始化煤的粒度的5个隶属度函数
		double (*pf[5])(double x) = {Level_1, Level_2, Level_3, Level_4, Level_5};
	}

	//分别定义煤的水分的隶属度函数的命名空间
	namespace Water
	{
		using namespace BasicFunction;
		using namespace Para;
		double Level_1(double x)
		{
			return	Fuzzy_Z( x, Para_Water[0][0], Para_Water[0][1]);
		}
		double Level_2(double x)
		{
			return	Fuzzy_PI( x, Para_Water[1][0], Para_Water[1][1]);
		}
		double Level_3(double x)
		{
			return	Fuzzy_PI( x, Para_Water[2][0], Para_Water[2][1]);
		}
		double Level_4(double x)
		{
			return	Fuzzy_PI( x, Para_Water[3][0], Para_Water[3][1]);
		}
		double Level_5(double x)
		{
			return	Fuzzy_S( x, Para_Water[4][0], Para_Water[4][1]);
		}
		//用函数指针数组(*pf[5])初始化煤的粒度的5个隶属度函数
		double (*pf[5])(double x) = {Level_1, Level_2, Level_3, Level_4, Level_5};
	}


	//分别定义煤的温度的隶属度函数的命名空间
	namespace Temperature
	{
		using namespace BasicFunction;
		using namespace Para;
		double Level_1(double x)
		{
			return	Fuzzy_S( x, Para_Temperature[0][0], Para_Temperature[0][1]);
		}
		double Level_2(double x)
		{
			return	Fuzzy_PI( x, Para_Temperature[1][0], Para_Temperature[1][1]);
		}
		double Level_3(double x)
		{
			return	Fuzzy_PI( x, Para_Temperature[2][0], Para_Temperature[2][1]);
		}
		double Level_4(double x)
		{
			return	Fuzzy_PI( x, Para_Temperature[3][0], Para_Temperature[3][1]);
		}
		double Level_5(double x)
		{
			return	Fuzzy_Z( x, Para_Temperature[4][0], Para_Temperature[4][1]);
		}
		//用函数指针数组(*pf[5])初始化煤的粒度的5个隶属度函数
		double (*pf[5])(double x) = {Level_1, Level_2, Level_3, Level_4, Level_5};
	}

	//分别定义煤层透气性的隶属度函数的命名空间
	namespace Permeability
	{
		using namespace BasicFunction;
		using namespace Para;
		double Level_1(double x)
		{
			return	Fuzzy_S( x, Para_Permeability[0][0], Para_Permeability[0][1]);
		}
		double Level_2(double x)
		{
			return	Fuzzy_PI( x, Para_Permeability[1][0], Para_Permeability[1][1]);
		}
		double Level_3(double x)
		{
			return	Fuzzy_PI( x, Para_Permeability[2][0], Para_Permeability[2][1]);
		}
		double Level_4(double x)
		{
			return	Fuzzy_PI( x, Para_Permeability[3][0], Para_Permeability[3][1]);
		}
		double Level_5(double x)
		{
			return	Fuzzy_Z( x, Para_Permeability[4][0], Para_Permeability[4][1]);
		}
		//用函数指针数组(*pf[5])初始化煤的粒度的5个隶属度函数
		double (*pf[5])(double x) = {Level_1, Level_2, Level_3, Level_4, Level_5};
	}
}
//定义权重向量的命名空间
namespace Weight
{
	//煤层特性评价模型权向量
	double W_B2[4] = {0.5839, 0.0843, 0.0926, 0.2392};
	double W_A1[2] = {0.5, 0.5};
}

#endif