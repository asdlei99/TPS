
// kdvplayertester.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CkdvplayertesterApp:
// �йش����ʵ�֣������ kdvplayertester.cpp
//

class CkdvplayertesterApp : public CWinApp
{
public:
	CkdvplayertesterApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CkdvplayertesterApp theApp;