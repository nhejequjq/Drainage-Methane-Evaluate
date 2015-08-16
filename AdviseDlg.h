#pragma once


// CAdviseDlg 对话框

class CAdviseDlg : public CDialog
{
	DECLARE_DYNAMIC(CAdviseDlg)

public:
	CAdviseDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAdviseDlg();

// 对话框数据
	enum { IDD = IDD_ADVISE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 整改建议
	CString strAdvise;
	afx_msg void OnBnClickedOk();
};
