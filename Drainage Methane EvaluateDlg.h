// Drainage Methane EvaluateDlg.h : ͷ�ļ�
//

#pragma once
#include "afxext.h"



// CDrainageMethaneEvaluateDlg �Ի���
class CDrainageMethaneEvaluateDlg : public CDialog
{
// ����
public:
	CDrainageMethaneEvaluateDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DRAINAGEMETHANEEVALUATE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CToolBar m_wndtoolbar;
	CMenu m_menu;
	CStatusBar m_statusbar;
	afx_msg void OnInfoinput();
	CTime time;
	// ������Ϣ��ȫ�ֱ��������۵�λ��
	CString strCompany;
	// ������Ϣ��ȫ�ֱ���������ú�㣩
	CString strCoalseam;
	// ������Ϣ��ȫ�ֱ�����������Ա��
	CString strPerson;
	afx_msg void OnCoalseam();
	afx_msg void OnDrainagegas();
	afx_msg void OnResultcheck();
	afx_msg void OnAbout();
};
