#pragma once


// CPermea_ComputeDlg �Ի���

class CPermea_ComputeDlg : public CDialog
{
	DECLARE_DYNAMIC(CPermea_ComputeDlg)

public:
	CPermea_ComputeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPermea_ComputeDlg();

// �Ի�������
	enum { IDD = IDD_PERMEABILITY_COMPUTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �������
	double fDrillflow;
	// ú����
	double fThickness;
	// ��װ뾶
	double fDrillDiameter;
	// ú�������˹ѹ��
	double fGaspressure;
	// ��˹����
	double fGascontent;
	// ʱ����
	double fInterval;
	afx_msg void OnBnClickedPermeaCompute();
};
