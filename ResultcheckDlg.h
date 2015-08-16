#pragma once


// CResultcheckDlg 对话框

class CResultcheckDlg : public CDialog
{
	DECLARE_DYNAMIC(CResultcheckDlg)

public:
	CResultcheckDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CResultcheckDlg();

// 对话框数据
	enum { IDD = IDD_CHECKRESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 评价时间
	CString strAssesstime;
	// 评价单位
	CString strCompany;
	// 评价煤层
	CString strCoalseam;
	// 评价人员
	CString strPerson;
	// 煤层特性评价结果
	CString strCoalseamres;
	// 瓦斯抽采综合能力评价结果
	CString strDrainagegasres;
	// 匹配性分析结果
	CString strMatchres;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
