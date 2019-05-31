// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__7EC2C131_F589_46BE_A4DB_7BE39EC3000B__INCLUDED_)
#define AFX_STDAFX_H__7EC2C131_F589_46BE_A4DB_7BE39EC3000B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#pragma warning( disable : 4786 )	// 标识符名称超过255字节
#pragma warning( disable : 4503 )
#pragma warning( disable : 4800 )
#pragma warning( disable : 4099 )

 
#pragma comment(lib, "osplib.lib")
 

#include "uiexhead.h"

#pragma comment (lib, "uiex.lib ") 


#include "kdvtype.h" 


//打印控制 
//#include "printctrl.h"
#pragma comment (lib,"nmscommon.lib")
 
#include "nmscommon.h"


extern long      g_lOrigResolutionX  ;//原分辨率
extern long      g_lOrigResolutionY ;//原分辨率
extern BOOL      g_bResolutionAdp  ;        //是否进行分辨率自适应

//分辨率自适应
void  ResolutionAdp( long &nx, long &ny);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__7EC2C131_F589_46BE_A4DB_7BE39EC3000B__INCLUDED_)
