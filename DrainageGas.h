#pragma once

#include "WorkflowDlg.h"
// CDrainageGas 对话框

class CDrainageGas : public CDialog
{
	DECLARE_DYNAMIC(CDrainageGas)

public:
	CDrainageGas(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDrainageGas();

// 对话框数据
	enum { IDD = IDD_DRAINAGEGAS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 抽采方法变量
	int nMethod;
	// 瓦斯抽采综合能力评价结果
	CString strAssessResult;
	afx_msg void OnBnClickedAssess();
	afx_msg void OnBnClickedCancelGas();
	// 钻孔直径
	int nDiameter;
	// 钻孔间距
	double fInterval;
	// 封孔技术
	int nSealtechnology;
	// 布孔均匀程度
	int nUniformity;
	// 钻孔控制范围
	int nControlrange;
	// 管网能力
	double fNetability;
	// 管理安全装置合理性
	int nNetsafety;
	// 抽采监控系统合理性
	int nMonitor;
	// 责任制合理性
	int nResponsibility;
	// 考核奖惩制
	int nExamine;
	// 例会制
	int nMeeting;
	// 检查验收制合理性
	int nCheck;
	// 人均年内培训次数
	int nTraincount;
	// 人员持证上岗率
	int nCertification;
	// 抽采达标规划完善度
	int nScheme;
	// 年度实施计划完善度
	int nImplementation;
	afx_msg void OnCbnSelchangeMethod();
	afx_msg void OnBnClickedWorkflowCompute();

	//计算模块对话框指针
	CWorkflowDlg * p_dlg;
	// 应抽采瓦斯量对应工况流量
	double fWorkflow;
	// 运行泵能力
	double fRunningpump;
	// 备用泵能力
	double fReadypump;
	// 最大一台单泵能力
	double fMaxpump;
	afx_msg void OnBnClickedResetGas();
	afx_msg void OnCbnSelchangeExamine();
};
