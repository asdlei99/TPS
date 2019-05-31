
// tpad.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "tpad.h"
#include "tpadDlg.h"
#include "exceptioncatch.h"
#include "toolwindowlogic.h"
#include "mainframelogic.h"
#include "videologic.h"
#include "filemanager.h"

#pragma comment(lib, "DbgHelp.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define EXCEPTION_FILE_PATH _T("exception.log")

void ResetHomeWindow();

// CTpadApp

BEGIN_MESSAGE_MAP(CTpadApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTpadApp construction

CTpadApp::CTpadApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTpadApp object

CTpadApp theApp;

//ץ���쳣��Ϣ
LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)  
{     
	// ����Dump�ļ�
	HANDLE hDumpFile = CreateFileW(L"Exception.dmp", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	// Dump��Ϣ
	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
	dumpInfo.ExceptionPointers = pException;
	dumpInfo.ThreadId = GetCurrentThreadId();
	dumpInfo.ClientPointers = TRUE;
	// д��Dump�ļ�����
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
	CloseHandle(hDumpFile);
	return EXCEPTION_EXECUTE_HANDLER;  
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        PKBDLLHOOKSTRUCT p;// 
        
        switch (wParam) 
        {
        case WM_KEYDOWN:  
        case WM_SYSKEYDOWN:
        case WM_KEYUP:    
        case WM_SYSKEYUP: 
            p = (PKBDLLHOOKSTRUCT)lParam;	
            if( //(p->vkCode==VK_TAB) ||
                (p->vkCode == VK_ESCAPE) ||
                (p->vkCode == VK_SHIFT) ||
                (p->vkCode == VK_F1) ||
                ( (p->vkCode == VK_F4) && ((p->flags & LLKHF_ALTDOWN)!=0) ) ||    //ALT+F4
                ( (p->vkCode == VK_TAB) && ((p->flags & LLKHF_ALTDOWN)!=0) ) ||    //ALT+TAB
                ( (p->vkCode == VK_ESCAPE) && ((p->flags & LLKHF_ALTDOWN)!=0) ) ||   //ALT+ESC
                ( (p->vkCode == VK_ESCAPE) && ((GetKeyState(VK_CONTROL) & 0x8000)!=0) ) || //CTRL+ESC
                ( (p->vkCode == VK_DELETE) && ((p->flags & LLKHF_ALTDOWN)!=0) && ((GetKeyState(VK_CONTROL) & 0x8000)!=0)  ) //CTRL+ALT + DEL  
                
                )
            {
                return TRUE;
            }
            
			//CString str;
			//str.Format( _T("\n --Home����ֵ��%d-- \n"), p->vkCode);
			//AfxOutputDebugString( str );

            if ( (p->vkCode == VK_LWIN) || (p->vkCode == VK_RWIN) ) // dyy 2013-9-22 
            {
                OSVERSIONINFO  osversioninfo = { sizeof(OSVERSIONINFO) };
                GetVersionEx(&osversioninfo);
                if ( (osversioninfo.dwMajorVersion == 5)  && (osversioninfo.dwMinorVersion == 1) )//winxp
                {
                    return TRUE;                 
                }
				
                //�����HOME��
                HWND hWnd = GetWndByAppName( AfxGetApp()->m_pszAppName );
                if ( NULL != hWnd )
                {	
                    //   ����������С������ָ����С   
                    if ( ::IsIconic(hWnd) ) 
                    {
                        ::ShowWindow( hWnd,SW_RESTORE );  
                    }
                    
                    //��׽�����õ�ǰ���㴰��Ϊ���ǵĴ���    
                    AttachThreadInput(   
                        GetWindowThreadProcessId(   
                        ::GetForegroundWindow(),NULL),   
                        GetCurrentThreadId(),TRUE);   
                    
                    ::SetForegroundWindow( hWnd );  
                    //SetFocus();  
                    
                    //�ͷ�thread    
                    AttachThreadInput(   
                        GetWindowThreadProcessId(   
                        ::GetForegroundWindow(),NULL),   
                        GetCurrentThreadId(),FALSE); 
                    
                    
                    //��ԭ��������
                    ResetHomeWindow();
				}
                 
                break;//return TRUE;
            }    

            //thinkpad����������
            if ( p->vkCode == 0xAE )
            {
                CMainFrameLogic::GetSingletonPtr()->OnThinkpadVolumeLow();
            }
            else if ( p->vkCode == 0xAF )
            {
                CMainFrameLogic::GetSingletonPtr()->OnThinkpadVolumeAdd();
            }
            break;
        }       
    }
    
    return ::CallNextHookEx( NULL, nCode, wParam, lParam );	
}

//��깳�ӣ��ػ�WM_LBUTTONDOWN �¼�
LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{   
    if ( HC_ACTION == nCode &&  WM_LBUTTONUP == wParam )
    {       
        PMSLLHOOKSTRUCT p = (PMSLLHOOKSTRUCT)lParam;	
        if ( p == NULL )
        {
            //AfxOutputDebugString("\nMouseHook: p==NULL\n");
            return CallNextHookEx( NULL, nCode, wParam, lParam );
        }

        if( ( (p->flags) & 0x1 ) == 0 ) //˵������ʵ���
        {   
            //AfxOutputDebugString("\nmouseHook������������ؼ���\n");
            //SetSoftKBDlgHide( ); 
            return CallNextHookEx( NULL, nCode, wParam, lParam );
        }

        CURSORINFO ci;
        ci.cbSize = sizeof(CURSORINFO);
        GetCursorInfo(&ci);
        bool bIsEdit = false;

        //CString msg;
        //msg.Format(_T("\nci.hCursor = %d;\n"), ci.hCursor);
        //AfxOutputDebugString(msg);
        if ( (int)ci.hCursor == 0x00010005 )//������״̬�Ǳ���״̬
        {
            //ֻ�аװ��ù��ӵ�������� -2017.3.7
            LPCWSTR windName = _T("whiteboard");
            HWND hWnd = ::FindWindow( NULL, windName );
            if ( hWnd != NULL && IsWindowVisible(hWnd))
            {
                bIsEdit = true;
            }

            if (  bIsEdit )
            {   
                //AfxOutputDebugString("\nMouseHook: ShowKeyboard\n");  
                ComInterface->ShowKeyboard();
            }
        }
    }

    return CallNextHookEx( NULL, nCode, wParam, lParam );
}

// CTpadApp initialization

BOOL CTpadApp::InitInstance()
{
    //ֻ����һ��
    if ( !OnlyStartOne() )
    {   
        UINT uExitCode = 0;
        ExitProcess( uExitCode );
        return FALSE;
    }

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

    //�쳣����
//     CString strFullPath = GetModuleFullPath();
//     strFullPath += EXCEPTION_FILE_PATH;
//     CExceptionCatch::LogToFile( (CT2A)strFullPath );
//     CExceptionCatch::Start(); 

	//ץ���쳣�ļ�
	::SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);  //cash����

#ifndef _DEBUG 
    //���̹���
    m_hk = ::SetWindowsHookEx( WH_KEYBOARD_LL, LowLevelKeyboardProc, AfxGetApp()->m_hInstance, 0 ); 
    //��ס��꣬������ʾ�����
    m_hkMouse = ::SetWindowsHookEx(/* WH_MOUSE_LL*/14, LowLevelMouseProc, AfxGetApp()->m_hInstance, 0 );  
    if (m_hkMouse == NULL  )
    {
        CString strErr;
        strErr.Format(_T("\n[InitInstance] hook mouse fail, GetLastError() = %d \n"), GetLastError() );
        AfxOutputDebugString( strErr );       
    }
#endif


	ComInterface->CreateSession();

    InitAppFrame(m_hInstance);

    new CSystem(_T("system.xml"));

    CSystem::GetSingletonPtr()->Launch();

    return TRUE;


	CtpadDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CTpadApp::ExitInstance()
{
    CExceptionCatch::Free();

    QuitAppFrame();

    if ( m_hkMouse )
    {
        ::UnhookWindowsHookEx( m_hkMouse );
    }

    ::RemoveProp( m_pMainWnd->GetSafeHwnd(), AfxGetApp()->m_pszAppName );

    return CWinApp::ExitInstance();
}


BOOL CTpadApp::OnlyStartOne()
{
    HANDLE  hSem  =  CreateSemaphore(NULL,  1,  1, AfxGetApp()->m_pszAppName);   

    //   �ź������ڣ����������һ��ʵ������   
    if (GetLastError()   ==   ERROR_ALREADY_EXISTS)   
    {  		
        //   �ر��ź������   
        CloseHandle(hSem);   
        //   Ѱ����ǰʵ����������   
        HWND   hWndPrevious = ::GetWindow(::GetDesktopWindow(),GW_CHILD);   
        while   (::IsWindow(hWndPrevious))   
        {   
            //   ��鴰���Ƿ���Ԥ��ı��?   
            //   �У���������Ѱ�ҵ�����   
            if   (::GetProp(hWndPrevious, AfxGetApp()->m_pszAppName))   
            {    		 
                //BOOL re = ((CIPSetterDlg)(CWnd::FromHandle(hWndPrevious))).setDestroyFlagEx(FALSE);
                //(CWnd::FromHandle(hWndPrevious))->SendMessage(WM_DESTROY_FLAG,FALSE,TRUE); 

                //   ����������С������ָ����С   
                if   (::IsIconic(hWndPrevious)) 				
                    ::ShowWindow(hWndPrevious,SW_RESTORE);   

                HWND hdl = GetForegroundWindow();
                if (hWndPrevious !=  hdl )
                {   					
                    ::ShowWindow(hWndPrevious,SW_RESTORE); 
                    ::SetForegroundWindow(hWndPrevious);
                }

                return   FALSE;   
            }   
            //   ����Ѱ����һ������   
            hWndPrevious   =   ::GetWindow(hWndPrevious,GW_HWNDNEXT); 
        }   
        //   ǰһʵ���Ѵ��ڣ����Ҳ���������   
        //   �˳���ʵ��   
        return   FALSE;   
    } 
    return TRUE;
}


//��ԭ��������
void ResetHomeWindow()
{
    WINDOW_MGR_PTR->ShowWindow( g_strAboutDlg.c_str(), false );
    WINDOW_MGR_PTR->ShowWindow( g_strNetCfgDlg.c_str(), false );

    if ( !ComInterface->IsConnectCns() )
    {
        CMainFrameLogic::GetSingletonPtr()->ShowLoginPage();
    }
    else
    {
        ComInterface->TPadHomeKeyNty();

        WINDOW_MGR_PTR->ShowWindow( g_strFilemanagerDlg.c_str(), false );
        WINDOW_MGR_PTR->ShowWindow( g_strFilePreviewDlg.c_str(), false );
        
        if ( WINDOW_MGR_PTR->IsWindowVisible(g_strVideoDlg.c_str()) )
        {
            TNotifyUI msg;
            CVideoLogic::GetSingletonPtr()->OnHideVideo(msg);
        }
        if ( WINDOW_MGR_PTR->IsWindowVisible( g_strFilemanagerDlg.c_str() ) )
        {   
            TNotifyUI msg;
            CFileManagerLogic::GetSingletonPtr()->OnBtnExit(msg);
        }

        LPCWSTR windName = _T("whiteboard");
        HWND hWnd = ::FindWindow( NULL, windName );
        if ( hWnd != NULL && IsWindowVisible(hWnd))
        {
            WB_API_showDataConfWindow(FALSE);
        }

        WINDOW_MGR_PTR->ShowWindow( g_strMainMenuDlg.c_str(), true );
    } 
}

