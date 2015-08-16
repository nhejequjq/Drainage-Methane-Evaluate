// DrainageGas.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Drainage Methane Evaluate.h"
#include "DrainageGas.h"
#include "FuzzyFunctionTable1.h"	//����ú����˹����ۺ������Զ�����ͷ�ļ�
#include "WorkflowDlg.h"	//��ӹ�����������ģ��Ի���ͷ�ļ�
#include "FactorAssessResult.h"    //��ӷ������������ͷ�ļ�

extern CFactorAssessResult m_G_FactorAssessResult;	//��������ȫ�ֱ���
// CDrainageGas �Ի���

IMPLEMENT_DYNAMIC(CDrainageGas, CDialog)

CDrainageGas::CDrainageGas(CWnd* pParent /*=NULL*/)
	: CDialog(CDrainageGas::IDD, pParent)
	, nMethod(0)
	, strAssessResult(_T(""))
	, nDiameter(0)
	, fInterval(0)
	, nSealtechnology(0)
	, nUniformity(0)
	, nControlrange(0)
	, fNetability(0)
	, nNetsafety(0)
	, nMonitor(0)
	, nResponsibility(0)
	, nExamine(0)
	, nMeeting(0)
	, nCheck(0)
	, nTraincount(0)
	, nCertification(0)
	, nScheme(0)
	, nImplementation(0)
	, p_dlg(NULL)	//��ʼ������ģ��Ի���ָ��
	, fWorkflow(0)
	, fRunningpump(0)
	, fReadypump(0)
	, fMaxpump(0)
{

}

CDrainageGas::~CDrainageGas()
{
	delete p_dlg;	//��˹����ۺ�����ģ����ʧ�󣬼���Ի���ģ��Ҳ��ʧ�����������������
}

void CDrainageGas::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_METHOD, nMethod);
	DDX_Text(pDX, IDC_EDIT_ASSESSRESULT, strAssessResult);
	DDV_MaxChars(pDX, strAssessResult, 100);
	DDX_CBIndex(pDX, IDC_DIAMETER, nDiameter);
	DDX_Text(pDX, IDC_EIDT_INTERVAL, fInterval);
	DDV_MinMaxDouble(pDX, fInterval, 0.0, 100);
	DDX_CBIndex(pDX, IDC_SEALTECH, nSealtechnology);
	DDX_CBIndex(pDX, IDC_UNIFORMITY, nUniformity);
	DDX_CBIndex(pDX, IDC_CONTROLRANGE, nControlrange);
	DDX_Text(pDX, IDC_EDIT_NETABILITY, fNetability);
	DDV_MinMaxDouble(pDX, fNetability, 0, 100000);
	DDX_CBIndex(pDX, IDC_NETSAFETY, nNetsafety);
	DDX_CBIndex(pDX, IDC_MONITOR, nMonitor);
	DDX_CBIndex(pDX, IDC_RESPONSIBILITY, nResponsibility);
	DDX_CBIndex(pDX, IDC_EXAMINE, nExamine);
	DDX_CBIndex(pDX, IDC_MEETING, nMeeting);
	DDX_CBIndex(pDX, IDC_CHECK, nCheck);
	DDX_CBIndex(pDX, IDC_TRAIN, nTraincount);
	DDV_MinMaxInt(pDX, nTraincount, 0, 1000);
	DDX_CBIndex(pDX, IDC_CERTIFICATION, nCertification);
	DDX_CBIndex(pDX, IDC_SCHEME, nScheme);
	DDX_CBIndex(pDX, IDC_IMPLEMENTATION, nImplementation);
	DDX_Text(pDX, IDC_EDIT_WORKFLOW, fWorkflow);
	DDV_MinMaxDouble(pDX, fWorkflow, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_RUNNINGPUMP, fRunningpump);
	DDV_MinMaxDouble(pDX, fRunningpump, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_READYPUMP, fReadypump);
	DDV_MinMaxDouble(pDX, fReadypump, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_MAXPUMP, fMaxpump);
	DDV_MinMaxDouble(pDX, fMaxpump, 0, 10000);
}


BEGIN_MESSAGE_MAP(CDrainageGas, CDialog)
	ON_BN_CLICKED(ID_ASSESS, &CDrainageGas::OnBnClickedAssess)
	ON_BN_CLICKED(IDC_CANCEL_GAS, &CDrainageGas::OnBnClickedCancelGas)
	ON_CBN_SELCHANGE(IDC_METHOD, &CDrainageGas::OnCbnSelchangeMethod)
	ON_BN_CLICKED(IDC_WORKFLOW_COMPUTE, &CDrainageGas::OnBnClickedWorkflowCompute)
	ON_BN_CLICKED(IDC_RESET_GAS, &CDrainageGas::OnBnClickedResetGas)
	ON_CBN_SELCHANGE(IDC_EXAMINE, &CDrainageGas::OnCbnSelchangeExamine)
END_MESSAGE_MAP()


// CDrainageGas ��Ϣ�������

void CDrainageGas::OnBnClickedAssess()
{
	UpdateData(TRUE);

	//�ݴ����б�
	//�����������>0������м���
	if(fInterval > 0 && fMaxpump > 0 && fNetability > 0 && fReadypump > 0 && fRunningpump > 0 && fWorkflow > 0)
	{
		//�����ɷ������۽������r_C5
		double r_C5[5] = {0};
		for(int i = 0; i < 2; i++)	//iΪ�б�־
		{
			if(nMethod == i)
			{
				for(int j = 0; j < 5; j++)	//jΪ�б�־
				{
					r_C5[j] = Table_1::Method[i][j];
				}
			}
		}
		//�������ֱ�����۽������r_C6
		double r_C6[5] = {0};
		for(int i = 0; i < 5; i++)	//iΪ�б�־
		{
			if(nDiameter == i)
			{
				for(int j = 0; j < 5; j++)	//jΪ�б�־
				{
					r_C6[j] = Table_1::Diameter[i][j];
				}
			}
		}
		//������׼������۽������r_C7
		double r_C7[5] = {0};
		for(int i = 0; i < 5; i++)
		{
			r_C7[i] = Function_1::Interval::pf[i](fInterval);
		}
		//�����׼������۽������r_C8
		double r_C8[5] = {0};
		for(int i = 0; i < 4; i++)	//iΪ�б�־
		{
			if( nSealtechnology== i)
			{
				for(int j = 0; j < 5; j++)	//jΪ�б�־
				{
					r_C8[j] = Table_1::Sealtechnology[i][j];
				}
			}
		}
		//���㲼�׾��ȳ̶����۽������r_C9
		double r_C9[5] = {0};
		for(int i = 0; i < 3; i++)	//iΪ�б�־
		{
			if( nUniformity== i)
			{
				for(int j = 0; j < 5; j++)	//jΪ�б�־
				{
					r_C9[j] = Table_1::Uniformity[i][j];
				}
			}
		}
		//������׿��Ʒ�Χ���۽������r_C10
		double r_C10[5] = {0};
		for(int i = 0; i < 3; i++)	//iΪ�б�־
		{
			if( nControlrange== i)
			{
				for(int j = 0; j < 5; j++)	//jΪ�б�־
				{
					r_C10[j] = Table_1::Controlrange[i][j];
				}
			}
		}
		//����������������۽������r_C12
		double r_C12[5] = {0};
		for(int i = 0; i < 5; i++)
		{
			r_C12[i] = Function_1::Netability::pf[i](fNetability);
		}
		//�������ȫװ�ú��������۽������r_C13
		double r_C13[5] = {0};
		for(int i = 0; i < 3; i++)	//iΪ�б�־
		{
			if( nNetsafety== i)
			{
				for(int j = 0; j < 5; j++)	//jΪ�б�־
				{
					r_C13[j] = Table_1::Netsafety[i][j];
				}
			}
		}
		//�����ɼ��ϵͳ���������۽������r_C14
		double r_C14[5] = {0};
		for(int i = 0; i < 3; i++)	//iΪ�б�־
		{
			if( nMonitor== i)
			{
				for(int j = 0; j < 5; j++)	//jΪ�б�־
				{
					r_C14[j] = Table_1::Monitor[i][j];
				}
			}
		}
		//���������ƺ��������۽������r_D3
		double r_D3[5] = {0};
		for(int i = 0; i < 3; i++)	//iΪ�б�־
		{
			if( nResponsibility== i)
			{
				for(int j = 0; j < 5; j++)	//jΪ�б�־
				{
					r_D3[j] = Table_1::Responsibility[i][j];
				}
			}
		}
		//���㿼�˽����ƺ��������۽������r_D4
		double r_D4[5] = {0};
		for(int i = 0; i < 3; i++)	//iΪ�б�־
		{
			if( nExamine== i)
			{
				for(int j = 0; j < 5; j++)	//jΪ�б�־
				{
					r_D4[j] = Table_1::Examine[i][j];
				}
			}
		}
		//���������ƺ��������۽������r_D6
		double r_D6[5] = {0};
		for(int i = 0; i < 3; i++)	//iΪ�б�־
		{
			if( nMeeting== i)
			{
				for(int j = 0; j < 5; j++)	//jΪ�б�־
				{
					r_D6[j] = Table_1::Meeting[i][j];
				}
			}
		}
		//��������ƺ��������۽������r_D5
		double r_D5[5] = {0};
		for(int i = 0; i < 3; i++)	//iΪ�б�־
		{
			if( nCheck== i)
			{
				for(int j = 0; j < 5; j++)	//jΪ�б�־
				{
					r_D5[j] = Table_1::Check[i][j];
				}
			}
		}
		//�˾�������ѵ�������۽������r_D7
		double r_D7[5] = {0};
		for(int i = 0; i < 3; i++)	//iΪ�б�־
		{
			if( nTraincount== i)
			{
				for(int j = 0; j < 5; j++)	//jΪ�б�־
				{
					r_D7[j] = Table_1::Traincount[i][j];
				}
			}
		}
		//��Ա��֤�ϸ������۽������r_D8
		double r_D8[5] = {0};
		for(int i = 0; i < 3; i++)	//iΪ�б�־
		{
			if( nCertification== i)
			{
				for(int j = 0; j < 5; j++)	//jΪ�б�־
				{
					r_D8[j] = Table_1::Certification[i][j];
				}
			}
		}
		//��ɴ��滮���ƶ����۽������r_D9
		double r_D9[5] = {0};
		for(int i = 0; i < 3; i++)	//iΪ�б�־
		{
			if( nScheme== i)
			{
				for(int j = 0; j < 5; j++)	//jΪ�б�־
				{
					r_D9[j] = Table_1::Scheme[i][j];
				}
			}
		}
		//���ʵʩ�ƻ����ƶ����۽������r_D10
		double r_D10[5] = {0};
		for(int i = 0; i < 3; i++)	//iΪ�б�־
		{
			if( nImplementation== i)
			{
				for(int j = 0; j < 5; j++)	//jΪ�б�־
				{
					r_D10[j] = Table_1::Implementation[i][j];
				}
			}
		}
		//�������б����������۽������r_D1
		double r_D1[5] = {0};
		r_D1[0] = Function_1::BasicFunction_1::Fuzzy_S(fRunningpump, fWorkflow * Function_1::Para_1::Para_Runningpump[0][0], fWorkflow * Function_1::Para_1::Para_Runningpump[0][1]);
		r_D1[1] = Function_1::BasicFunction_1::Fuzzy_PI(fRunningpump, fWorkflow * Function_1::Para_1::Para_Runningpump[1][0], fWorkflow * Function_1::Para_1::Para_Runningpump[1][1]);
		r_D1[2] = Function_1::BasicFunction_1::Fuzzy_PI(fRunningpump, fWorkflow * Function_1::Para_1::Para_Runningpump[2][0], fWorkflow * Function_1::Para_1::Para_Runningpump[2][1]);
		r_D1[3] = Function_1::BasicFunction_1::Fuzzy_PI(fRunningpump, fWorkflow * Function_1::Para_1::Para_Runningpump[3][0], fWorkflow * Function_1::Para_1::Para_Runningpump[3][1]);
		r_D1[4] = Function_1::BasicFunction_1::Fuzzy_Z(fRunningpump, fWorkflow * Function_1::Para_1::Para_Runningpump[4][0], fWorkflow * Function_1::Para_1::Para_Runningpump[4][1]);
		
		//���㱸�ñ����������۽������r_D2
		double r_D2[5] = {0};
		r_D2[0] = Function_1::BasicFunction_1::Fuzzy_S(fReadypump, fMaxpump * Function_1::Para_1::Para_Readypump[0][0], fMaxpump * Function_1::Para_1::Para_Readypump[0][1]);
		r_D2[1] = Function_1::BasicFunction_1::Fuzzy_PI(fReadypump, fMaxpump * Function_1::Para_1::Para_Readypump[1][0], fMaxpump * Function_1::Para_1::Para_Readypump[1][1]);
		r_D2[2] = Function_1::BasicFunction_1::Fuzzy_PI(fReadypump, fMaxpump * Function_1::Para_1::Para_Readypump[2][0], fMaxpump * Function_1::Para_1::Para_Readypump[2][1]);
		r_D2[3] = Function_1::BasicFunction_1::Fuzzy_PI(fReadypump, fMaxpump * Function_1::Para_1::Para_Readypump[3][0], fMaxpump * Function_1::Para_1::Para_Readypump[3][1]);
		r_D2[4] = Function_1::BasicFunction_1::Fuzzy_Z(fReadypump, fMaxpump * Function_1::Para_1::Para_Readypump[4][0], fMaxpump * Function_1::Para_1::Para_Readypump[4][1]);
		
		////////////////////////////////////////////////////����ģ���ۺ�����///////////////////////////////////////////////////
		//ģ���ۺ����ۣ���һ����D�����ط���
		//�õ�C11���۽��
		double * R_C11[] = {r_D1, r_D2};	//���۾���	
		double r_C11[5] = {0};	//���۽��
		Function_1::BasicFunction_1::Matrix_Multiply(Weight_1::W_C11, R_C11, r_C11, 2);
		//�õ�C15���۽��
		double * R_C15[] = {r_D3, r_D4, r_D5, r_D6};	//���۾���	
		double r_C15[5] = {0};	//���۽��
		Function_1::BasicFunction_1::Matrix_Multiply(Weight_1::W_C15, R_C15, r_C15, 4);
		//�õ�C16���۽��
		double * R_C16[] = {r_D7, r_D8};	//���۾���	
		double r_C16[5] = {0};	//���۽��
		Function_1::BasicFunction_1::Matrix_Multiply(Weight_1::W_C16, R_C16, r_C16, 2);
		//�õ�C17���۽��
		double * R_C17[] = {r_D9, r_D10};	//���۾���	
		double r_C17[5] = {0};	//���۽��
		Function_1::BasicFunction_1::Matrix_Multiply(Weight_1::W_C17, R_C17, r_C17, 2);

		//ģ���ۺ����ۣ��ڶ�����C�����ط���
		//�õ�B3���۽��
		double * R_B3[] = {r_C5, r_C6, r_C7, r_C8, r_C9, r_C10};	
		double r_B3[5] = {0};
		Function_1::BasicFunction_1::Matrix_Multiply(Weight_1::W_B3, R_B3, r_B3, 6);
		//�õ�B4���۽��
		double * R_B4[] = {r_C11, r_C12, r_C13, r_C14};	
		double r_B4[5] = {0};
		Function_1::BasicFunction_1::Matrix_Multiply(Weight_1::W_B4, R_B4, r_B4, 4);
		//�õ�B5���۽��
		double * R_B5[] = {r_C15, r_C16, r_C17};	
		double r_B5[5] = {0};
		Function_1::BasicFunction_1::Matrix_Multiply(Weight_1::W_B5, R_B5, r_B5, 3);

		//ģ���ۺ����ۣ���������B�����ط���
		//�õ�A2���۽��
		double * R_A2[] = {r_B3, r_B4, r_B5};	
		double r_A2[5] = {0};
		Function_1::BasicFunction_1::Matrix_Multiply(Weight_1::W_A2, R_A2, r_A2, 3);

		/////////////////////////////////////////////////�������������ȫ�ֱ���(������ֵ������ָ��)//////////////////////////////////////////////////////

		for(int i = 0; i < 5; i++)
		{
			//���շ������
			m_G_FactorAssessResult.A[1][i] = r_A2[i]; //��A1�����ֵ��ȫ�ֱ���
			//���۵�Ԫ���ط������
			m_G_FactorAssessResult.C[4][i] = r_C5[i]; //��C5�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.C[5][i] = r_C6[i]; //��C6�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.C[6][i] = r_C7[i]; //��C7�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.C[7][i] = r_C8[i]; //��C8�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.C[8][i] = r_C9[i]; //��C9�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.C[9][i] = r_C10[i]; //��C10�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.D[0][i] = r_D1[i]; //��D1�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.D[1][i] = r_D2[i]; //��D2�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.C[11][i] = r_C12[i]; //��C12�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.C[12][i] = r_C13[i]; //��C13�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.C[13][i] = r_C14[i]; //��C14�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.D[2][i] = r_D3[i]; //��D3�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.D[3][i] = r_D4[i]; //��D4�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.D[4][i] = r_D5[i]; //��D5�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.D[5][i] = r_D6[i]; //��D6�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.D[6][i] = r_D7[i]; //��D7�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.D[7][i] = r_D8[i]; //��D8�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.D[8][i] = r_D9[i]; //��D9�����ֵ��ȫ�ֱ���
			m_G_FactorAssessResult.D[9][i] = r_D10[i]; //��D10�����ֵ��ȫ�ֱ���
		}
		//�ó����۽��
		switch(m_G_FactorAssessResult.GetRank(m_G_FactorAssessResult.A[1]))
		{
		case 0:
			strAssessResult = _T("Level I ; good");
			break;
		case 1:
			strAssessResult = _T("Level II ; relatively good");
			break;
		case 2:
			strAssessResult = _T("Level III ; average");
			break;
		case 3:
			strAssessResult = _T("Level IV ; relatively bad");
			break;
		case 4:
			strAssessResult = _T("Level V ; bad");
			break;
		}
		//���Խ��
		//strAssessResult.Format(_T("%2f+%2f+%2f+%2f+%2f"),m_G_FactorAssessResult.C[11][0],m_G_FactorAssessResult.C[11][1],m_G_FactorAssessResult.C[11][2],m_G_FactorAssessResult.C[11][3],m_G_FactorAssessResult.C[11][4]);
		m_G_FactorAssessResult.Isdone_Drainagegas = true;  //�Ѿ�����
	}
	else
	{
		MessageBox(_T("The input data is wrong, please input again!"),_T("Tips"));
	}
	UpdateData(FALSE);
}

void CDrainageGas::OnBnClickedCancelGas()
{
	OnCancel();
}

void CDrainageGas::OnCbnSelchangeMethod()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CDrainageGas::OnBnClickedWorkflowCompute()
{
	extern CDrainageGas * p_G_DrainageGas;
	//��ʼ�������ȫ�ֱ�������˹����ۺ������Ի���ָ�룩
	p_G_DrainageGas = this;

	//�������ģ���Ѿ��򿪣������ý���
	if(p_dlg != NULL)
	{
		p_dlg->SetFocus();
		p_dlg->ShowWindow(SW_SHOW);
	}
	//�������ģ��δ�򿪣����
	else
	{
		p_dlg = new CWorkflowDlg();
		p_dlg->Create(IDD_FLOWCOMPUTE);
		p_dlg->ShowWindow(SW_SHOW);
	}	
}

void CDrainageGas::OnBnClickedResetGas()
{
	//������ֵ��ʼ��Ϊ0�ٸ���
	UpdateData(TRUE);
	
	//��׼��
	fInterval = 0;
	//���һ̨��������
	fMaxpump = 0;
	//��������
	fNetability = 0;
	//���ñ�����
	fReadypump = 0;
	//���б�����
	fRunningpump = 0;
	//��������
	fWorkflow = 0;
	//Ա����֤�ϸ���
	nCertification = 0;
	//��������ƶ�
	nCheck = 0;
	//��׿��Ʒ�Χ
	nControlrange = 0;
	//���ֱ��
	nDiameter = 0;
	//���˽����ƶ�
	nExamine = 0;
	//���ʵʩ�ƻ�
	nImplementation = 0;
	//�����ƶ�
	nMeeting = 0;
	//��ɷ���
	nMethod = 0;
	//��ɼ��װ��
	nMonitor = 0;
	//��·��ȫװ��
	nNetsafety = 0;
	//������
	nResponsibility = 0;
	//��ɴ��滮
	nScheme = 0;
	//��׼���
	nSealtechnology = 0;
	//�˾�������ѵ����
	nTraincount = 0;
	//��׾��ȳ̶�
	nUniformity = 0;
	//����ģ��Ի������
	p_dlg = NULL;
	//��˹����ۺ��������۽��
	strAssessResult = _T("");
	
	//������ֵ����Ϊ��ʼ״̬
	UpdateData(FALSE);
}

void CDrainageGas::OnCbnSelchangeExamine()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
