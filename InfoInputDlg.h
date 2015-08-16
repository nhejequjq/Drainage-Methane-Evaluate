#pragma once
#include "afxdtctl.h"


// InfoInputDlg �Ի���

class InfoInputDlg : public CDialog
{
	DECLARE_DYNAMIC(InfoInputDlg)

public:
	InfoInputDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~InfoInputDlg();

// �Ի�������
	enum { IDD = IDD_INFOINPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnInfoinput();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedInput();
	// DataTime�ؼ���CDateTime���͵ı���
	CDateTimeCtrl m_DateTime;
	// ���۵�λ
	CString strCompany;
	// ����ú��
	CString strCoalseam;
	// ������Ա
	CString strPerson;
	afx_msg void OnDtnDatetimechangeTime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditCompany();
};
