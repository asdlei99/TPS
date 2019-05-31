#if !defined(AFX_UMCWEBPROJ_H__47ABEAD3_B4F0_40C1_8C8C_9AE043B49CF1__INCLUDED_)
#define AFX_UMCWEBPROJ_H__47ABEAD3_B4F0_40C1_8C8C_9AE043B49CF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

 
#include "mainLogic.h"
#include "loginLogic.h"

// UmcWebProj.h : main header file for UMCWEBPROJ.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols
/////////////////////////////////////////////////////////////////////////////
// CUmcWebProjApp : See UmcWebProj.cpp for implementation.

LRESULT CALLBACK GetMessageProc(int nCode, WPARAM wParam, LPARAM lParam);

class CUmcWebProjApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();

	void RegMethod();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UMCWEBPROJ_H__47ABEAD3_B4F0_40C1_8C8C_9AE043B49CF1__INCLUDED)
