#pragma once


// CAdviseDlg �Ի���

class CAdviseDlg : public CDialog
{
	DECLARE_DYNAMIC(CAdviseDlg)

public:
	CAdviseDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAdviseDlg();

// �Ի�������
	enum { IDD = IDD_ADVISE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ���Ľ���
	CString strAdvise;
	afx_msg void OnBnClickedOk();
};
