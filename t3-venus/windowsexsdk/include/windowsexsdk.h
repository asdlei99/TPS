// windowsexsdk.h : main header file for the windowsexsdk DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


#ifndef DLL_EXPORTS
#define DLL_DECL __declspec(dllexport)
#else
#define DLL_DECL __declspec(dllimport)
#endif


// CwindowsexsdkApp
// See windowsexsdk.cpp for the implementation of this class
//

class CwindowsexsdkApp : public CWinApp
{
public:
	CwindowsexsdkApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};



//×¢²á´°¿Ú
DLL_DECL VOID WINSDK_RegTouchWindow( HWND hWnd );

DLL_DECL BOOL WINSDK_GetTouchInputInfo( LPARAM lParam, UINT cInputs, TOUCHINPUT& tInput );

DLL_DECL BOOL WINSDK_GetTouchInputPoint( LPARAM lParam, UINT cInputs, POINT& ptInput );

DLL_DECL BOOL WINSDK_GetGestureInfo( LPARAM lParam, GESTUREINFO& gi );

DLL_DECL BOOL WINSDK_SetGestureConfig(  HWND hwnd, DWORD dwReserved, UINT cIDs, PGESTURECONFIG pGestureConfig, UINT cbSize );