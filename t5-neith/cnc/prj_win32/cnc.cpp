
// cnc.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "cnc.h"
#include "cncDlg.h"
#include "system.h"
#include "outPrint.h"
#include "exceptioncatch.h"

#pragma comment(lib, "DbgHelp.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcncApp

BEGIN_MESSAGE_MAP(CcncApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CcncApp construction

CcncApp::CcncApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CcncApp object

CcncApp theApp;

//抓捕异常信息
LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)  
{     
	// 创建Dump文件
	HANDLE hDumpFile = CreateFileW(L"CncException.dmp", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	// Dump信息
	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
	dumpInfo.ExceptionPointers = pException;
	dumpInfo.ThreadId = GetCurrentThreadId();
	dumpInfo.ClientPointers = TRUE;
	// 写入Dump文件内容
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
	CloseHandle(hDumpFile);
	return EXCEPTION_EXECUTE_HANDLER;  
}

// CcncApp initialization

#define EXCEPTION_FILE_PATH _T("exception.log")

BOOL CcncApp::InitInstance()
{
	//只开启一个程序实例
	if ( !OnlyStartOne() )
	{
		TerminateProcess(GetCurrentProcess(), 0);
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
	//CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));


	//异常处理
	CString strFullPath = GetModuleFullPath();
	strFullPath += EXCEPTION_FILE_PATH;
	CExceptionCatch::LogToFile( (CT2A)strFullPath );
	CExceptionCatch::Start();   

	//抓捕异常文件
	::SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);  //cash代码

	//CWndShadow::Initialize(m_hInstance);
	InitAppFrame(m_hInstance);

	new CSystem(_T("system.xml"));

	//创建cns session
	ComInterface->CreateSession();

	CSystem::GetSingletonPtr()->Launch();

	::SetProp( m_pMainWnd->GetSafeHwnd(), AfxGetApp()->m_pszAppName, (HANDLE)1 );

	return TRUE;

	CcncDlg dlg;
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
	/*if (pShellManager != NULL)
	{
		delete pShellManager;
	}*/

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


int CcncApp::ExitInstance()
{
	CExceptionCatch::Free();
	
	QuitAppFrame();

	::RemoveProp( m_pMainWnd->GetSafeHwnd(), AfxGetApp()->m_pszAppName );

	return CWinApp::ExitInstance();
}





API void help()
{
    PrtMsg( "\nshowver: 显示版本和编译时间");
    //PrtMsg( "\ntask 1/0: 是否启用任务管理器；1：启用 ，0：禁用");
    PrtMsg( "\nprt: 打印所有级别为3以上的消息");
    PrtMsg( "\nprtlevel nLevel: 打印级别为nLevel的消息；消息级别 1-3，\n \
    1为级别最高的消息，该级别的消息对系统可能产生致命影响\n \
    2为一般级别的消息\n \
    3为最低级别消息 " );
    PrtMsg( "\nprtid msgID: 打印消息号是msgID的消息");
    PrtMsg( "\nprtrange MaxMsgID, MinMsgID: 打印消息号范围在 MinMsgID 和 MaxMsgID 之间的消息");
    PrtMsg( "\nstopprt: 停止打印所有消息");
    //PrtMsg( "\nprtrecive 0 / 1: 打印所有接受到的消息, 0:不打印，1:打印");
    //PrtMsg( "\nprtsend 0 / 1: 打印所有发送出去的消息, 0:不打印，1:打印"); 
    PrtMsg( "\nshowallconf: 显示所有会议信息");
    PrtMsg( "\nshowcns: 显示本地会场信息");
    PrtMsg( "\nshowconf : 显示本会场所在的会议信息");
    PrtMsg( "\nhangupep wConfID epID: 挂断会议中的会场，wConfID：会议ID，epID：会议中cns的ID"); 
    PrtMsg( "\nhangupconf wConfID: 挂断会议，wConfID：会议ID");  
    PrtMsg( "\nshowconfcns wCnsID: 显示会议中会场信息，wCnsID：会议中cns的ID");
    PrtMsg( "\nshowcnsstate: cns会议状态");
    //PrtMsg( "\nshowalltemp: 显示相应的模板信息，否则，显示所有模板信息" );
    //PrtMsg( "\nshowtemp ID: 则显示相应的模板信息 " );
    PrtMsg( "\nshowscrninfo: 显示屏和选看信息 ");
    PrtMsg( "\nshowvmpinfo: 显示画面合成信息" );   
    PrtMsg( "\nshowalluser: 显示所有用户信息" );
    //PrtMsg( "\nshowlocalip: 显示本地PC机IP" );
    //PrtMsg( "\nsetdecvol 0-255: 设置解码器音量，范围 0-255" );
    //PrtMsg( "\nshowdecvol :显示当前解码器音量，范围 0-255" );
    //PrtMsg( "\nshowalarm: 显示当前所有告警信息" );
    PrtMsg( "\nshowaddrbook: 显示当前地址簿信息" );
    PrtMsg( "\nshowonlineaddr: 显示全局地址簿信息" );
    PrtMsg( "\nshowaddrentry dwEntryIndex: 显示地址簿会场信息, dwEntryIndex:会场索引" );
    PrtMsg( "\ndeleteaddr dwEntryIndex: 删除地址簿会场信息, dwEntryIndex:会场索引" );
	PrtMsg( "\nfreshconf：刷新会议状态" );
}

API void freshconf()
{
	u16 wRe = wRe = ComInterface->FreshConf();
}

API void task( BOOL bEnable/* = TRUE */)
{
    //BusinessManagePtr->DisableTaskMgr( !bEnable );
}

API void prt()
{
    CPrintCtrl::GetPrintCtrl()->PrintAllMsg();
}


API void prtlevel( u8 byLevel )
{
    CPrintCtrl::GetPrintCtrl()->PrintMsgLevel( byLevel );
}

API void stopprt()
{
   CPrintCtrl::GetPrintCtrl()->StopPrint();
}


API void prtid( u32 msgID )
{
   CPrintCtrl::GetPrintCtrl()->SetPrintMsgID( msgID );
}

API void prtrange( u32 beginID, u32 endID )
{ 
    CPrintCtrl::GetPrintCtrl()->SetPrintMsgRange( beginID, endID ); 
}


API void prtrecive( BOOL bPrint /*= TRUE */ )
{
    CPrintCtrl::GetPrintCtrl()->PrintEnterMsg( bPrint ); 
}

API void prtsend( BOOL bPrint/* = TRUE */)
{
   CPrintCtrl::GetPrintCtrl()->PrintOutMsg( bPrint );
}


API void showver()
{   
	s8 achVersion[MAX_DEVICEVER_LEN] = {0};
	COutPrint::GetCncBuildVersion(achVersion);
    PrtMsg( "Cnc  version: V%s  \n", achVersion ); 
    PrtMsg( "compile time: %s %s", __DATE__, __TIME__ );
}

// 显示所有会议
API void showallconf()
{
    COutPrint::GetAllConfInfo();
}

//显示某ID的会议信息
API void showconf()
{
    //COutPrint::GetConfInfo( wConfID );
    COutPrint::GetConfCnsInfo( );
}



//显示会议中cns的信息
API void showconfcns( u16 wCnsID )
{
    COutPrint::GetConfCnsInfo( wCnsID );
}

//显示 会场信息
API void showcns()
{
    COutPrint::GetLocalCnsInfo();
}


//显示本地cns状态
API void showcnsstate()
{
    COutPrint::IsLocalCnsInConf();
}


API void showvmpinfo()
{
    COutPrint::ShowVmpInfo();
}

//显示屏和选看信息
API void showscrninfo()
{
    COutPrint::ShowScrnInfo();
}

//显示所有用户信息
API void showalluser()
{
     COutPrint::ShowAllUseInfo();
}

API void  showlocalip()
{
    COutPrint::ShowLocalIP();
}


//挂断某会议中的某个会场
API void hangupep( u16 wConfID, u16 epID )
{
//     TConfEpID ep;
//     ep.m_wConfID = wConfID;
//     ep.m_wEpID = epID;
//     u16 re = BusinessManagePtr->HangupCNS( ep );
//     if ( re != NO_ERROR )
//     {
//         PrtMsg("\n[API void hangupep]re = %d \n", re );
//     }
}

//结束会议
API void hangupconf( u16 wConfID )
{   
//     u16 re = BusinessManagePtr->HangupConf(   );
//     if ( re != NO_ERROR )
//     {
//         PrtMsg("\n[API void hangupconf]re = %d \n", re );
//     }
    
}


//显示地址簿信息
API void showaddrbook()
{
    COutPrint::ShowAddrbook();
}

//显示全局地址簿信息
API void showonlineaddr()
{
    COutPrint::ShowOnlineAddr();
}

API void showaddrentry( u32 dwEntryIndex )
{
    COutPrint::ShowAddrEntry( dwEntryIndex );
}

API void deleteaddr( u32 dwEntryIndex )
{
    COutPrint::DeleteAddr( dwEntryIndex );
}

API void showUIInfo()
{
	PrtMsg("\n ===========================UI Info=============================\n" );
	PrtMsg("\n CurBackName: %s\n", CT2A(UIDATAMGR->GetCurShowWndName().c_str()) );
	PrtMsg("\n ===============================================================\n" );
}


BOOL OnlyStartOne()
{
	HANDLE  hSem  =  CreateSemaphore(NULL,  1,  1, AfxGetApp()->m_pszAppName);   

	//   信号量存在，则程序已有一个实例运行   
	if (GetLastError()   ==   ERROR_ALREADY_EXISTS)   
	{  		
		//   关闭信号量句柄   
		CloseHandle(hSem);   
		//   寻找先前实例的主窗口   
		HWND   hWndPrevious = ::GetWindow(::GetDesktopWindow(),GW_CHILD);   
		while   (::IsWindow(hWndPrevious))   
		{   
			//   检查窗口是否有预设的标记?   
			//   有，则是我们寻找的主窗   
			if   (::GetProp(hWndPrevious, AfxGetApp()->m_pszAppName))   
			{    		 
				//BOOL re = ((CIPSetterDlg)(CWnd::FromHandle(hWndPrevious))).setDestroyFlagEx(FALSE);
				//(CWnd::FromHandle(hWndPrevious))->SendMessage(WM_DESTROY_FLAG,FALSE,TRUE); 

				//   主窗口已最小化，则恢复其大小   
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
			//   继续寻找下一个窗口   
			hWndPrevious   =   ::GetWindow(hWndPrevious,GW_HWNDNEXT); 
		}   
		//   前一实例已存在，但找不到其主窗   
		//   退出本实例   
		return   FALSE;   
	} 
	return TRUE;
}
