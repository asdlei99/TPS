// windowsexsdk.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "windowsexsdk.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CwindowsexsdkApp

BEGIN_MESSAGE_MAP(CwindowsexsdkApp, CWinApp)
END_MESSAGE_MAP()


// CwindowsexsdkApp construction

CwindowsexsdkApp::CwindowsexsdkApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CwindowsexsdkApp object

CwindowsexsdkApp theApp;


// CwindowsexsdkApp initialization

BOOL CwindowsexsdkApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


VOID WINSDK_RegTouchWindow( HWND hWnd )
{
	if ( hWnd == NULL )
	{
		return;
	}

	RegisterTouchWindow( hWnd, 0 );
}

BOOL WINSDK_GetTouchInputPoint( LPARAM lParam, UINT cInputs, POINT& ptInput )
{
	PTOUCHINPUT pInputs = new TOUCHINPUT[cInputs];
	if (NULL != pInputs)
	{

		if (GetTouchInputInfo((HTOUCHINPUT)lParam,
			cInputs,
			pInputs,
			sizeof(TOUCHINPUT)))
		{
			// process pInputs

			for (int i=0; i < static_cast<INT>(cInputs); i++)  
			{  
				TOUCHINPUT ti = pInputs[i];                        
				if (ti.dwID != 0)  
				{  
					// Do something with your touch input handle.  
					ptInput.x = TOUCH_COORD_TO_PIXEL(ti.x);  
					ptInput.y = TOUCH_COORD_TO_PIXEL(ti.y);  
					//ScreenToClient(g_hWnd, &ptInput);  

					//CString msg;
					//msg.Format( _T("\nOnTouch, hWnd:%d, ptInput.x:%d, ptInput.y:%d \n"), g_hWnd, ptInput.x, ptInput.y );
					//AfxOutputDebugString( msg );
				}  
			}		

			if (!CloseTouchInputHandle((HTOUCHINPUT)lParam))
			{
				// error handling
			}
		}

		delete [] pInputs;
	}
	else
	{
		// error handling, presumably out of memory
		return FALSE;
	}

	return TRUE;
}

BOOL WINSDK_GetTouchInputInfo( LPARAM lParam, UINT cInputs, TOUCHINPUT& tInput )
{
	PTOUCHINPUT pInputs = new TOUCHINPUT[cInputs];
	if (NULL != pInputs)
	{

		if (GetTouchInputInfo((HTOUCHINPUT)lParam,
			cInputs,
			pInputs,
			sizeof(TOUCHINPUT)))
		{
			// process pInputs
			//暂只支持一个点触摸
			if ( pInputs > 0 )
			{
				TOUCHINPUT ti = pInputs[0];
				if (ti.dwID != 0)  
				{
					tInput = ti;
				}
			}
			/*
			for (int i=0; i < static_cast<INT>(cInputs); i++)  
			{  
				TOUCHINPUT ti = pInputs[i];                        
				if (ti.dwID != 0)  
				{  
					// Do something with your touch input handle.  
					tInput = ti;

					BOOL bDown = FALSE;
					BOOL bUp = FALSE;
					if ( (ti.dwFlags & TOUCHEVENTF_DOWN) == TOUCHEVENTF_DOWN )
					{
						bDown = TRUE;
					}
					if ( (ti.dwFlags & TOUCHEVENTF_UP) == TOUCHEVENTF_UP )
					{
						bUp = TRUE;
					}
					CString msg;
					msg.Format( _T("\nOnTouch, cInputs:%d, bDown.x:%d, bUp.y:%d \n"), cInputs, bDown, bUp );
					AfxOutputDebugString( msg );
				}  
			}*/		

			if (!CloseTouchInputHandle((HTOUCHINPUT)lParam))
			{
				// error handling
			}
		}

		delete [] pInputs;
	}
	else
	{
		// error handling, presumably out of memory
		return FALSE;
	}

	return TRUE;
}

BOOL WINSDK_GetGestureInfo( HGESTUREINFO hgi, /*PGESTUREINFO*/GESTUREINFO& gi )
{ 
	return GetGestureInfo( hgi, &gi);;
}

BOOL WINSDK_SetGestureConfig( HWND hwnd, DWORD dwReserved, UINT cIDs, PGESTURECONFIG pGestureConfig, UINT cbSize )
{ 
	return SetGestureConfig( hwnd, dwReserved, cIDs, pGestureConfig, cbSize ); 
}


/*
LRESULT OnTouch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	UINT cInputs = LOWORD(wParam);
	PTOUCHINPUT pInputs = new TOUCHINPUT[cInputs];
	if (NULL != pInputs)
	{
		POINT ptInput; 

		if (GetTouchInputInfo((HTOUCHINPUT)lParam,
			cInputs,
			pInputs,
			sizeof(TOUCHINPUT)))
		{
			// process pInputs

			for (int i=0; i < static_cast<INT>(cInputs); i++)  
			{  
				TOUCHINPUT ti = pInputs[i];                        
				if (ti.dwID != 0)  
				{  
					// Do something with your touch input handle.  
					ptInput.x = TOUCH_COORD_TO_PIXEL(ti.x);  
					ptInput.y = TOUCH_COORD_TO_PIXEL(ti.y);  
					ScreenToClient(hWnd, &ptInput);  

					CString msg;
					msg.Format( _T("\nOnTouch, hWnd:%d, ptInput.x:%d, ptInput.y:%d \n"), hWnd, ptInput.x, ptInput.y );
					AfxOutputDebugString( msg );
				}  
			}		

			if (!CloseTouchInputHandle((HTOUCHINPUT)lParam))
			{
				// error handling
			}
		}
		else
		{
			// GetLastError() and error handling
		}
		delete [] pInputs;
	}
	else
	{
		// error handling, presumably out of memory
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
*/