// Drainage Methane Evaluate.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDrainageMethaneEvaluateApp:
// �йش����ʵ�֣������ Drainage Methane Evaluate.cpp
//

class CDrainageMethaneEvaluateApp : public CWinApp
{
public:
	CDrainageMethaneEvaluateApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDrainageMethaneEvaluateApp theApp;