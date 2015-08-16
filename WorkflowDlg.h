#pragma once


// CWorkflowDlg 对话框

class CWorkflowDlg : public CDialog
{
	DECLARE_DYNAMIC(CWorkflowDlg)

public:
	CWorkflowDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWorkflowDlg();

// 对话框数据
	enum { IDD = IDD_FLOWCOMPUTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 抽采达标时抽采量
	double fFlow;
	// 当地大气压
	double fPressure;
	// 抽采瓦斯浓度
	double fConcentration;
	// 泵运行负压
	double fPressurepump;
	afx_msg void OnBnClickedCompute();
};
