#pragma once
#include "afxdtctl.h"


// InfoInputDlg 对话框

class InfoInputDlg : public CDialog
{
	DECLARE_DYNAMIC(InfoInputDlg)

public:
	InfoInputDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~InfoInputDlg();

// 对话框数据
	enum { IDD = IDD_INFOINPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnInfoinput();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedInput();
	// DataTime控件的CDateTime类型的变量
	CDateTimeCtrl m_DateTime;
	// 评价单位
	CString strCompany;
	// 评价煤层
	CString strCoalseam;
	// 评价人员
	CString strPerson;
	afx_msg void OnDtnDatetimechangeTime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditCompany();
};
