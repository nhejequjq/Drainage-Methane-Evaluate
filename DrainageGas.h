#pragma once

#include "WorkflowDlg.h"
// CDrainageGas �Ի���

class CDrainageGas : public CDialog
{
	DECLARE_DYNAMIC(CDrainageGas)

public:
	CDrainageGas(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDrainageGas();

// �Ի�������
	enum { IDD = IDD_DRAINAGEGAS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��ɷ�������
	int nMethod;
	// ��˹����ۺ��������۽��
	CString strAssessResult;
	afx_msg void OnBnClickedAssess();
	afx_msg void OnBnClickedCancelGas();
	// ���ֱ��
	int nDiameter;
	// ��׼��
	double fInterval;
	// ��׼���
	int nSealtechnology;
	// ���׾��ȳ̶�
	int nUniformity;
	// ��׿��Ʒ�Χ
	int nControlrange;
	// ��������
	double fNetability;
	// ����ȫװ�ú�����
	int nNetsafety;
	// ��ɼ��ϵͳ������
	int nMonitor;
	// �����ƺ�����
	int nResponsibility;
	// ���˽�����
	int nExamine;
	// ������
	int nMeeting;
	// ��������ƺ�����
	int nCheck;
	// �˾�������ѵ����
	int nTraincount;
	// ��Ա��֤�ϸ���
	int nCertification;
	// ��ɴ��滮���ƶ�
	int nScheme;
	// ���ʵʩ�ƻ����ƶ�
	int nImplementation;
	afx_msg void OnCbnSelchangeMethod();
	afx_msg void OnBnClickedWorkflowCompute();

	//����ģ��Ի���ָ��
	CWorkflowDlg * p_dlg;
	// Ӧ�����˹����Ӧ��������
	double fWorkflow;
	// ���б�����
	double fRunningpump;
	// ���ñ�����
	double fReadypump;
	// ���һ̨��������
	double fMaxpump;
	afx_msg void OnBnClickedResetGas();
	afx_msg void OnCbnSelchangeExamine();
};
