#pragma once


// CWorkflowDlg �Ի���

class CWorkflowDlg : public CDialog
{
	DECLARE_DYNAMIC(CWorkflowDlg)

public:
	CWorkflowDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWorkflowDlg();

// �Ի�������
	enum { IDD = IDD_FLOWCOMPUTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��ɴ��ʱ�����
	double fFlow;
	// ���ش���ѹ
	double fPressure;
	// �����˹Ũ��
	double fConcentration;
	// �����и�ѹ
	double fPressurepump;
	afx_msg void OnBnClickedCompute();
};
