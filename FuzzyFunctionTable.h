
#ifndef _FUZZYFUNCTIONTABLE_H
#define _FUZZYFUNCTIONTABLE_H

/////////////////////////////////////////////��ͷ�ļ�ֻ���ú����������ģ��/////////////////////////////////////////////
//��������ģ�����۹����������ռ�
namespace Table
{
	//�ƻ��������۹����
	double Breaktype[5][5] = {
		{0, 0, 0.1, 0.3, 1},
		{0, 0.1, 0.3, 1, 0.3},
		{0.1, 0.3, 1, 0.3, 0.1},
		{0.3, 1, 0.3, 0.1, 0},
		{1, 0.3, 0.1, 0, 0}
	};
	//��ɷ������۹����
	double Method[2][5] = {
		{0.9, 0.6, 0.3, 0, 0},
		{0.6, 0.9, 0.6, 0.3, 0}
	};
}

//�������������������ռ�
namespace Function
{
	//���������������������S������Z������PI�����������ռ�
	namespace BasicFunction
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
	namespace Para
	{
		//ú�����ȵ�������������
		double Para_Partical[5][2] = {{0.1133,0.5},{0.2233,1.6667},{0.75,3.6667},{2.3333,6.5},{4.3333,7}};
		//ú������ˮ�ֵ�������������
		double Para_Water[5][2] = {{1,2.6667},{1.3333,5.3333},{3.3333,11.3333},{6.6667,22},{15,25}};
		//ú�������¶ȵ�������������
		double Para_Temperature[5][2] = {{46.66,60},{36.66,53.33},{26.66,43.33},{16.66,33.33},{10,23.33}};
		//ú��͸���Ե�������������
		double Para_Permeability[5][2] = {{70,150},{8,120},{0.07,13},{0.0008,0.12},{0.0001,0.0012}};
	}

	//�ֱ���ú�����ȵ������Ⱥ����������ռ�
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
		//�ú���ָ������(*pf[5])��ʼ��ú�����ȵ�5�������Ⱥ���
		double (*pf[5])(double x) = {Level_1, Level_2, Level_3, Level_4, Level_5};
	}

	//�ֱ���ú��ˮ�ֵ������Ⱥ����������ռ�
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
		//�ú���ָ������(*pf[5])��ʼ��ú�����ȵ�5�������Ⱥ���
		double (*pf[5])(double x) = {Level_1, Level_2, Level_3, Level_4, Level_5};
	}


	//�ֱ���ú���¶ȵ������Ⱥ����������ռ�
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
		//�ú���ָ������(*pf[5])��ʼ��ú�����ȵ�5�������Ⱥ���
		double (*pf[5])(double x) = {Level_1, Level_2, Level_3, Level_4, Level_5};
	}

	//�ֱ���ú��͸���Ե������Ⱥ����������ռ�
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
		//�ú���ָ������(*pf[5])��ʼ��ú�����ȵ�5�������Ⱥ���
		double (*pf[5])(double x) = {Level_1, Level_2, Level_3, Level_4, Level_5};
	}
}
//����Ȩ�������������ռ�
namespace Weight
{
	//ú����������ģ��Ȩ����
	double W_B2[4] = {0.5839, 0.0843, 0.0926, 0.2392};
	double W_A1[2] = {0.5, 0.5};
}

#endif