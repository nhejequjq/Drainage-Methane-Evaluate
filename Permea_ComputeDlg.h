#pragma once


// CPermea_ComputeDlg 对话框

class CPermea_ComputeDlg : public CDialog
{
	DECLARE_DYNAMIC(CPermea_ComputeDlg)

public:
	CPermea_ComputeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPermea_ComputeDlg();

// 对话框数据
	enum { IDD = IDD_PERMEABILITY_COMPUTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 钻孔流量
	double fDrillflow;
	// 煤层厚度
	double fThickness;
	// 钻孔半径
	double fDrillDiameter;
	// 煤层绝对瓦斯压力
	double fGaspressure;
	// 瓦斯含量
	double fGascontent;
	// 时间间隔
	double fInterval;
	afx_msg void OnBnClickedPermeaCompute();
};
