#pragma once


// CResultcheckDlg �Ի���

class CResultcheckDlg : public CDialog
{
	DECLARE_DYNAMIC(CResultcheckDlg)

public:
	CResultcheckDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CResultcheckDlg();

// �Ի�������
	enum { IDD = IDD_CHECKRESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ����ʱ��
	CString strAssesstime;
	// ���۵�λ
	CString strCompany;
	// ����ú��
	CString strCoalseam;
	// ������Ա
	CString strPerson;
	// ú���������۽��
	CString strCoalseamres;
	// ��˹����ۺ��������۽��
	CString strDrainagegasres;
	// ƥ���Է������
	CString strMatchres;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
