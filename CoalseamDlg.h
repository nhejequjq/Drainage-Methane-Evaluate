#pragma once

#include "Permea_ComputeDlg.h"
// CCoalseamDlg �Ի���

class CCoalseamDlg : public CDialog
{
	DECLARE_DYNAMIC(CCoalseamDlg)

public:
	CCoalseamDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCoalseamDlg();

// �Ի�������
	enum { IDD = IDD_COALSEAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �ƻ����Ͳ��Ա���
	int nbreaktype;
	// ú���������۽��
	CString strEvaluateresult;
	afx_msg void OnBnClickedOk();
	// ú������
	double fPractical;
	// ú��ˮ��
	double fWater;
	// ú���¶�
	double fTemperature;
	//ú��͸����
	double fPermeability;
	//͸���Լ���ģ��Ի���ָ��
	CPermea_ComputeDlg * p_dlg;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedPermeaCompute();
	afx_msg void OnBnClickedReset();
};
