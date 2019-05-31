
// tpad.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTpadApp:
// See tpad.cpp for the implementation of this class
//

class CTpadApp : public CWinApp
{
public:
	CTpadApp();

// Overrides
public:
	virtual BOOL InitInstance();
    virtual int ExitInstance();
// Implementation

	DECLARE_MESSAGE_MAP()

private:
    BOOL OnlyStartOne();

    HHOOK m_hk;          //¼üÅÌ¹³×Ó
    HHOOK m_hkMouse;     //Êó±ê¹³×Ó
};

extern CTpadApp theApp;