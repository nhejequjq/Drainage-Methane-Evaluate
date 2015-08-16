#pragma once


// InfoInput 对话框

class InfoInput : public CDialog
{
	DECLARE_DYNAMIC(InfoInput)

public:
	InfoInput(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~InfoInput();

// 对话框数据
	enum { IDD = IDD_INFOINPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
