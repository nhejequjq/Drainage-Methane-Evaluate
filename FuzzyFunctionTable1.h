
#ifndef _FUZZYFUNCTIONTable_1_H
#define _FUZZYFUNCTIONTable_1_H

/////////////////////////////////////////////��ͷ�ļ�ֻ�����˹����ۺ���������ģ��/////////////////////////////////////////////
//��������ģ�����۹����������ռ�
namespace Table_1
{
	//��ɷ������۹����
	double Method[2][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.6, 0.9, 0.6, 0.3, 0}
	};
	//���ֱ�����۹����
	double Diameter[5][5] = {
		{0, 0.1, 0.3, 0.6, 0.9},
		{0.3, 0.6, 0.9, 0.3, 0},
		{0.9, 0.6, 0.1, 0, 0},
		{0.6, 0.9, 0.3, 0, 0},
		{0, 0.3, 0.6, 0.9, 0.6}
	};
	//��׼������۹����
	double Sealtechnology[4][5] = {
		{0, 0, 0.3, 0.6, 0.9},
		{0, 0.3, 0.6, 0.9, 0.6},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0.9, 0.6, 0.3, 0, 0}
	};
	//���׾��ȳ̶����۹����
	double Uniformity[3][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0, 0.3, 0.6, 0.9, 0.6}
	};
	//��׿��Ʒ�Χ���۹����
	double Controlrange[3][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0, 0.3, 0.6, 0.9, 0.6}
	};
	//����ȫװ�ú��������۹����
	double Netsafety[3][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0, 0.3, 0.6, 0.9, 0.6}
	};
	//��ɼ��ϵͳ���������۹����
	double Monitor[3][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0, 0.3, 0.6, 0.9, 0.6}
	};
	//�����ƺ��������۹����
	double Responsibility[3][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0, 0.3, 0.6, 0.9, 0.6}
	};
	//���˽����ƺ��������۹����
	double Examine[3][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0, 0.3, 0.6, 0.9, 0.6}
	};
	//�����ƺ��������۹����
	double Meeting[3][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0, 0.3, 0.6, 0.9, 0.6}
	};
	//��������ƺ��������۹����
	double Check[3][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0, 0.3, 0.6, 0.9, 0.6}
		
	};
	//�˾�������ѵ�������۹����
	double Traincount[3][5] = {
		{0, 0.3, 0.6, 0.9, 0.6},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0.9, 0.6, 0.3, 0, 0}	
	};
	//�˾�������ѵ�������۹����
	double Certification[3][5] = {
		{0, 0.3, 0.6, 0.9, 0.6},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0.9, 0.6, 0.3, 0, 0}	
	};
	//��ɴ��滮���ƶ����۹����
	double Scheme[3][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0, 0.3, 0.6, 0.9, 0.6}
	};
	//���ʵʩ�ƻ����ƶ����۹����
	double Implementation[3][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.3, 0.6, 0.9, 0.6, 0.3},
		{0, 0.3, 0.6, 0.9, 0.6}
	};
}

//�������������������ռ�
namespace Function_1
{
	//���������������������S������Z������PI�����������ռ�
	namespace BasicFunction_1
	{
		//����S����
		double Fuzzy_S(double x, double a, double b)
		{
			//�����[0,1]Ϊ������-1Ϊ�쳣���
			if(a < b)
			{
				if(x <= a)	return 0;
				else if(x > a && x <= (a + b)/2)
					return 2*((x - a)/(b - a))*((x - a)/(b - a));
				else if(x > (a + b)/2 && x <= b)
					return 1 - 2*((x - b)/(b - a))*((x - b)/(b - a));
				else if(x > b)	return 1;
				else	return -1;	//�쳣��Ϊ-1
			}
			else
				return -1;	//�쳣��Ϊ-1
		}

		//����Z����
		double Fuzzy_Z(double x, double a, double b)
		{
			if(a < b && Fuzzy_S(x, a, b) != -1)
				return 1 - Fuzzy_S(x, a, b);
			else 
				return -1;	//���Ϊ�쳣ʱ
		}

		//����PI����
		double Fuzzy_PI(double x, double a, double b)
		{
			if(a < b)
			{
				if(x <= (a + b)/2 && Fuzzy_S(x, a, (a + b)/2) != -1)
					return	Fuzzy_S(x, a, (a + b)/2);
				else if(x > (a + b)/2 && Fuzzy_Z(x, (a + b)/2, b) != -1)
					return	Fuzzy_Z(x, (a + b)/2, b);
				else	
					return -1;	//���Ϊ�쳣
			}
			else
				return -1;	//���Ϊ�쳣
		}
		//�������ĳ˷���ʹ��C���Է���ʵ�֣�
		void Matrix_Multiply(double A[], double * B[], double C[], int p, int n = 5)	//AΪ������pΪB��������,CΪ�������
		{
			//�������C=A*B
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
	//ÿ�����۵�Ԫ�������õ�����������������S������Z������PI�������Ĳ����������ռ�
	namespace Para_1
	{	
		//��׼���������������
		double Para_Interval[5][2] = {{0.3,1.8},{1.2,2.8},{2.2,3.8},{3.2,4.8},{4.2,5.5}};
		//����������������������
		double Para_Netability[5][2] = {{16,20},{12,20},{8,16},{4,12},{4,6}};
		//���б�������������������
		double Para_Runningpump[5][2] = {{2.2,3},{1.8,2.7},{1.3,2.2},{0.8,1.7},{0.5,1.2}};
		//���ñ�������������������
		double Para_Readypump[5][2] = {{1.3,2},{1.05,1.7},{0.55,1.45},{0.05,0.95},{0,0.45}};
	}

	//�ֱ�����׼��������Ⱥ����������ռ�
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
		//�ú���ָ������(*pf[5])��ʼ��ú�����ȵ�5�������Ⱥ���
		double (*pf[5])(double x) = {Level_1, Level_2, Level_3, Level_4, Level_5};
	}

	//�ֱ�����������������Ⱥ����������ռ�
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
		//�ú���ָ������(*pf[5])��ʼ��ú�����ȵ�5�������Ⱥ���
		double (*pf[5])(double x) = {Level_1, Level_2, Level_3, Level_4, Level_5};
	}

	//�ֱ������б������������Ⱥ����������ռ�
	
}
//����Ȩ�������������ռ�
namespace Weight_1
{
	//��˹����ۺ���������ģ��Ȩ����(����8��)
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