
#ifndef _FUZZYFUNCTIONTable_1_H
#define _FUZZYFUNCTIONTable_1_H

/////////////////////////////////////////////该头文件只针对瓦斯抽采综合能力评价模块/////////////////////////////////////////////
//包括所有模糊评价规则表的命名空间
namespace Table_1
{
	//抽采方法评价规则表
	double Method[2][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.6, 0.9, 0.6, 0.3, 0}
	};
	//钻孔直径评价规则表
	double Diameter[5][5] = {
		{0, 0.1, 0.3, 0.6, 0.9},
		{0.3, 0.6, 0.9, 0.3, 0},
		{0.9, 0.6, 0.1, 0, 0},
		{0.6, 0.9, 0.3, 0, 0},
		{0, 0.3, 0.6, 0.9, 0.6}
	};
	//封孔技术评价规则表
	double Sealtechnology[4][5] = {
		{0, 0, 0.3, 0.6, 0.9},
		{0, 0.3, 0.6, 0.9, 0.6},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0.9, 0.6, 0.3, 0, 0}
	};
	//布孔均匀程度评价规则表
	double Uniformity[3][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0, 0.3, 0.6, 0.9, 0.6}
	};
	//钻孔控制范围评价规则表
	double Controlrange[3][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0, 0.3, 0.6, 0.9, 0.6}
	};
	//管理安全装置合理性评价规则表
	double Netsafety[3][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0, 0.3, 0.6, 0.9, 0.6}
	};
	//抽采监控系统合理性评价规则表
	double Monitor[3][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0, 0.3, 0.6, 0.9, 0.6}
	};
	//责任制合理性评价规则表
	double Responsibility[3][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0, 0.3, 0.6, 0.9, 0.6}
	};
	//考核奖惩制合理性评价规则表
	double Examine[3][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0, 0.3, 0.6, 0.9, 0.6}
	};
	//例会制合理性评价规则表
	double Meeting[3][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0, 0.3, 0.6, 0.9, 0.6}
	};
	//检查验收制合理性评价规则表
	double Check[3][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0, 0.3, 0.6, 0.9, 0.6}
		
	};
	//人均年内培训次数评价规则表
	double Traincount[3][5] = {
		{0, 0.3, 0.6, 0.9, 0.6},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0.9, 0.6, 0.3, 0, 0}	
	};
	//人均年内培训次数评价规则表
	double Certification[3][5] = {
		{0, 0.3, 0.6, 0.9, 0.6},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0.9, 0.6, 0.3, 0, 0}	
	};
	//抽采达标规划完善度评价规则表
	double Scheme[3][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0, 0.3, 0.6, 0.9, 0.6}
	};
	//年度实施计划完善度评价规则表
	double Implementation[3][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0, 0.3, 0.6, 0.9, 0.6}
	};
}

//定义隶属函数的命名空间
namespace Function_1
{
	//定义基础的三类隶属函数S函数、Z函数、PI函数的命名空间
	namespace BasicFunction_1
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
	namespace Para_1
	{	
		//钻孔间距的隶属函数参数
		double Para_Interval[5][2] = {{0.3,1.8},{1.2,2.8},{2.2,3.8},{3.2,4.8},{4.2,5.5}};
		//管网能力的隶属函数参数
		double Para_Netability[5][2] = {{16,20},{12,20},{8,16},{4,12},{4,6}};
		//运行泵能力的隶属函数参数
		double Para_Runningpump[5][2] = {{2.2,3},{1.8,2.7},{1.3,2.2},{0.8,1.7},{0.5,1.2}};
		//备用泵能力的隶属函数参数
		double Para_Readypump[5][2] = {{1.3,2},{1.05,1.7},{0.55,1.45},{0.05,0.95},{0,0.45}};
	}

	//分别定义钻孔间距的隶属度函数的命名空间
	namespace Interval
	{
		using namespace BasicFunction_1;
		using namespace Para_1;
		double Level_1(double x)
		{
			return	Fuzzy_Z( x, Para_Interval[0][0], Para_Interval[0][1]);
		}
		double Level_2(double x)
		{
			return	Fuzzy_PI( x, Para_Interval[1][0], Para_Interval[1][1]);
		}
		double Level_3(double x)
		{
			return	Fuzzy_PI( x, Para_Interval[2][0], Para_Interval[2][1]);
		}
		double Level_4(double x)
		{
			return	Fuzzy_PI( x, Para_Interval[3][0], Para_Interval[3][1]);
		}
		double Level_5(double x)
		{
			return	Fuzzy_S( x, Para_Interval[4][0], Para_Interval[4][1]);
		}
		//用函数指针数组(*pf[5])初始化煤的粒度的5个隶属度函数
		double (*pf[5])(double x) = {Level_1, Level_2, Level_3, Level_4, Level_5};
	}

	//分别定义管网能力的隶属度函数的命名空间
	namespace Netability
	{
		using namespace BasicFunction_1;
		using namespace Para_1;
		double Level_1(double x)
		{
			return	Fuzzy_S( x, Para_Netability[0][0], Para_Netability[0][1]);
		}
		double Level_2(double x)
		{
			return	Fuzzy_PI( x, Para_Netability[1][0], Para_Netability[1][1]);
		}
		double Level_3(double x)
		{
			return	Fuzzy_PI( x, Para_Netability[2][0], Para_Netability[2][1]);
		}
		double Level_4(double x)
		{
			return	Fuzzy_PI( x, Para_Netability[3][0], Para_Netability[3][1]);
		}
		double Level_5(double x)
		{
			return	Fuzzy_Z( x, Para_Netability[4][0], Para_Netability[4][1]);
		}
		//用函数指针数组(*pf[5])初始化煤的粒度的5个隶属度函数
		double (*pf[5])(double x) = {Level_1, Level_2, Level_3, Level_4, Level_5};
	}

	//分别定义运行泵能力的隶属度函数的命名空间
	
}
//定义权重向量的命名空间
namespace Weight_1
{
	//瓦斯抽采综合能力评价模型权向量(共计8组)
	double W_A2[3] = {0.6986, 0.2370, 0.0643};
	double W_B3[6] = {0.5137, 0.1778, 0.1005, 0.0324, 0.0475, 0.1281};
	double W_B4[4] = {0.5820, 0.2381, 0.1055, 0.0744};
	double W_C11[2] = {0.6667, 0.3333};
	double W_B5[3] = {0.5171, 0.3586, 0.1243};
	double W_C15[4] = {0.4193, 0.1661, 0.2314, 0.1832};
	double W_C16[2] = {0.6667, 0.3333};
	double W_C17[2] = {0.5, 0.5};
}

#endif