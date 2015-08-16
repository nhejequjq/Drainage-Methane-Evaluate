// Drainage Methane EvaluateDlg.h : 头文件
//

#pragma once
#include "afxext.h"



// CDrainageMethaneEvaluateDlg 对话框
class CDrainageMethaneEvaluateDlg : public CDialog
{
// 构造
public:
	CDrainageMethaneEvaluateDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DRAINAGEMETHANEEVALUATE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	// 评价信息的全局变量（评价单位）
	CString strCompany;
	// 评价信息的全局变量（评价煤层）
	CString strCoalseam;
	// 评价信息的全局变量（评价人员）
	CString strPerson;
	afx_msg void OnCoalseam();
	afx_msg void OnDrainagegas();
	afx_msg void OnResultcheck();
	afx_msg void OnAbout();
};
