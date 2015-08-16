// InfoInput.cpp : 实现文件
//

#include "stdafx.h"
#include "Drainage Methane Evaluate.h"
#include "InfoInput.h"


// InfoInput 对话框

IMPLEMENT_DYNAMIC(InfoInput, CDialog)

InfoInput::InfoInput(CWnd* pParent /*=NULL*/)
	: CDialog(InfoInput::IDD, pParent)
{

}

InfoInput::~InfoInput()
{
}

void InfoInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(InfoInput, CDialog)
END_MESSAGE_MAP()


// InfoInput 消息处理程序
