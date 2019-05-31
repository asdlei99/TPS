// UmcWebProj.cpp : Implementation of CUmcWebProjApp and DLL registration.

#include "stdafx.h"
#include "UmcWebProj.h"
#include "exceptioncatch.h"
#include "tpmsginit.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CUmcWebProjApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x38ef4e0b, 0x4e0f, 0x4c57, { 0x93, 0x58, 0xbc, 0x6b, 0xad, 0x8a, 0x66, 0x99 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


CMainLogic* g_pMainDlg = NULL;
CLoginLogic* m_pLoginDlg = NULL;

HHOOK g_hHook = NULL;

float CUR_SCREEN_WIDTH_PER = 1.0;
float CUR_SCREEN_HEIGHT_PER = 1.0;
////////////////////////////////////////////////////////////////////////////
// CUmcWebProjApp::InitInstance - DLL initialization

void CUmcWebProjApp::RegMethod()
{
	REG_ALGORITHM( IAlgorithm::strVert, CLayoutAlgorithm_Vert )
	REG_ALGORITHM( IAlgorithm::strHori, CLayoutAlgorithm_Hori )
	REG_ALGORITHM( IAlgorithm::strCharacter, CSortAlgorithm_Char )
	REG_ALGORITHM( IAlgorithm::strNormalItem, CLayoutAlgorithm_NormalItem )
	REG_ALGORITHM( IAlgorithm::strAddrGroupItem, CLayoutAlgorithm_AddrGroupItem )
	REG_ALGORITHM( IAlgorithm::strHoriConfLst, CLayoutAlgorithm_HoriConfLst )	
	REG_ALGORITHM( IAlgorithm::strTextOnly, CLayoutAlgorithm_TextOnly )
	REG_ALGORITHM( IAlgorithm::strDoubleColumn, CLayoutAlgorithm_DoubleColumn )
	REG_ALGORITHM( IAlgorithm::strTPadMainMenu, CLayoutAlgorithm_TPadMainMenu )
	REG_ALGORITHM( IAlgorithm::strTextBottom, CLayoutAlgorithm_TextBottom )
	REG_ALGORITHM( IAlgorithm::strWifiItem, CLayoutAlgorithm_WifiItem )
    REG_ALGORITHM( IAlgorithm::strTvwView, CLayoutAlgorithm_TvwView )
	REG_ALGORITHM( IAlgorithm::strTvwItem, CLayoutAlgorithm_TvwItem )
    REG_ALGORITHM( "TvwCns", CLayoutAlgorithm_TvwCns )
}

typedef struct tagKBDLLHOOKSTRUCT {
    DWORD   vkCode;
    DWORD   scanCode;
    DWORD   flags;
    DWORD   time;
    DWORD   dwExtraInfo;
} KBDLLHOOKSTRUCT, FAR *LPKBDLLHOOKSTRUCT, *PKBDLLHOOKSTRUCT;

void ShowKeyboard()
{
    char * achFileName= "C:\\Program Files\\Common Files\\microsoft shared\\ink\\TabTip.exe";
    LPCSTR windName = "触摸键盘";
    if ( access(achFileName, 0) != 0 )
    {
        windName = "屏幕键盘";
        achFileName = "osk.exe";
    }
    
    HWND hWnd = ::FindWindow( NULL, windName );
    if ( !IsWindow( hWnd ) )
    {
        ShellExecute( NULL, NULL, _T( achFileName ), NULL, NULL,SW_NORMAL);
    }
    
    if (::IsIconic(hWnd)) 			
    {
        ::ShowWindow( hWnd, SW_RESTORE );
    }
    else
    {
        ::ShowWindow( hWnd, SW_SHOW );
    }
    return;
}

//#define WM_GESTURE                      0x0119
#define WM_GESTURENOTIFY                0x011A


LRESULT CALLBACK GetMessageProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));//模块切换时的状态保护指向当前模块状态

	LPMSG lpMsg = (LPMSG) lParam;


     PKBDLLHOOKSTRUCT p;   //121029 ldy 解决除登陆界面键盘回车界面控件清空的情况
	 switch (lpMsg->message) 
	 {
	 case WM_KEYDOWN:  
		 {
			 if ( lpMsg->wParam == VK_ESCAPE )
			 {
				 return TRUE;
			 }

			 //140429 shicheng 禁掉键盘上下键切换左侧菜单栏
			 if ( lpMsg->wParam == VK_UP || lpMsg->wParam == VK_DOWN || lpMsg->wParam == VK_LEFT || lpMsg->wParam == VK_RIGHT )
			 {
				 HWND hwnd = g_pMainDlg->GetSafeHwnd();
				 if ( GetParent(lpMsg->hwnd) == hwnd )
				 {
					 return TRUE;
				 }
			 }

			 //140707 xhx 解决除登陆界面键盘回车界面控件清空的情况
			 p = (PKBDLLHOOKSTRUCT)lParam;
			 if( NULL != p )
			 {
				 if( p->flags == VK_RETURN  )
				 {
					 HWND hFocus = ::GetFocus( ); 
					 if( NULL != m_pLoginDlg )
					 {
						 if ( m_pLoginDlg->m_hWnd != ::GetParent(hFocus) )
						 {
							 return TRUE;
						 }
					 }
				 }
			 }

			 break;
		 }
	 case WM_SYSKEYDOWN:
	 case WM_KEYUP: 
     case WM_SYSKEYUP: 
		 {
			 p = (PKBDLLHOOKSTRUCT)lParam;
			 if( NULL != p )
			 {
				 if( p->flags == VK_RETURN  )
				 {
					 HWND hFocus = ::GetFocus( ); 
					 if( NULL != m_pLoginDlg )
					 {
						 if ( m_pLoginDlg->m_hWnd != ::GetParent(hFocus) )
						 {
							 return TRUE;
						 }
					 }
				}
			 }
			 break;
		 }
	 }

	if ( lpMsg->message == WM_CHAR )   //ldy 120926解决编辑框输入中文乱码问题
	{
		return ::CallNextHookEx( g_hHook, nCode, wParam, lParam );
	}	
	
	if( (nCode >= 0) && (PM_REMOVE == wParam) &&
		AfxGetApp()->PreTranslateMessage(lpMsg))
	{
		lpMsg->message = WM_NULL;
		lpMsg->lParam = 0L;
		lpMsg->wParam = 0;
	}
	
	// 将钩子消息传递给当前钩子链中的下一个钩子
	return ::CallNextHookEx( g_hHook, nCode, wParam, lParam );
}

BOOL CUmcWebProjApp::InitInstance()
{
	CExceptionCatch::Start();
	CExceptionCatch::LogToFile("D:\\UmcWebException.txt");

	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.

		InitTpEvent();

		g_hHook = ::SetWindowsHookEx( WH_GETMESSAGE, GetMessageProc, 
                     /*AfxGetInstanceHandle()*/NULL, GetCurrentThreadId() );

		


		GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR           gdiplusToken;
		GdiplusStartup( &gdiplusToken, &gdiplusStartupInput, NULL );

		RegMethod();

		CUmcwebCommon::GetResolutionScale( CUR_SCREEN_WIDTH_PER, CUR_SCREEN_HEIGHT_PER );
        CUR_SCREEN_WIDTH_PER = 1;
        CUR_SCREEN_HEIGHT_PER = 1;
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CUmcWebProjApp::ExitInstance - DLL termination

int CUmcWebProjApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	//DESTORYUMSSESSION

	if ( m_pLoginDlg )
	{
		SAFE_RELEASE(m_pLoginDlg);
		if (m_pLoginDlg->GetSafeHwnd())
		{
			m_pLoginDlg->DestroyWindow();
		}
	}
	
	if ( g_pMainDlg )
	{
		SAFE_RELEASE(g_pMainDlg);
		if (g_pMainDlg->GetSafeHwnd())
		{
			g_pMainDlg->DestroyWindow();
		}
	}

    CExceptionCatch::Free();

	if ( NULL != g_hHook )
	{
		::UnhookWindowsHookEx(g_hHook);
		g_hHook = NULL;
	}

	return COleControlModule::ExitInstance();
}


BOOL CUmcWebProjApp::PreTranslateMessage(MSG* pMsg) 
{
// 	switch (pMsg->message)
// 	{
// 	case WM_QUIT:
// 		{
// 			ExitInstance();
// 			//ExitInstance不能再调用PreTranslateMessage()，解决关闭后打开出现白页面bug，2013818----by石城
// 			break;
// 		}
// 	default:
// 		break;
// 	}

    return CWinApp::PreTranslateMessage(pMsg);
}



/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
