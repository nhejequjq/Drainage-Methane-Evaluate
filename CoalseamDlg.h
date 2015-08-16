#pragma once

#include "Permea_ComputeDlg.h"
// CCoalseamDlg 对话框

class CCoalseamDlg : public CDialog
{
	DECLARE_DYNAMIC(CCoalseamDlg)

public:
	CCoalseamDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCoalseamDlg();

// 对话框数据
	enum { IDD = IDD_COALSEAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 破坏类型测试变量
	int nbreaktype;
	// 煤层特性评价结果
	CString strEvaluateresult;
	afx_msg void OnBnClickedOk();
	// 煤的粒度
	double fPractical;
	// 煤的水分
	double fWater;
	// 煤的温度
	double fTemperature;
	//煤的透气性
	double fPermeability;
	//透气性计算模块对话框指针
	CPermea_ComputeDlg * p_dlg;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedPermeaCompute();
	afx_msg void OnBnClickedReset();
};
