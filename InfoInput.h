#pragma once


// InfoInput �Ի���

class InfoInput : public CDialog
{
	DECLARE_DYNAMIC(InfoInput)

public:
	InfoInput(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~InfoInput();

// �Ի�������
	enum { IDD = IDD_INFOINPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
