
// zxqz.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CzxqzApp: 
// �йش����ʵ�֣������ zxqz.cpp
//

class CzxqzApp : public CWinApp
{
public:
	CzxqzApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CzxqzApp theApp;