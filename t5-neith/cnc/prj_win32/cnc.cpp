
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

//ץ���쳣��Ϣ
LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)  
{     
	// ����Dump�ļ�
	HANDLE hDumpFile = CreateFileW(L"CncException.dmp", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
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

// CcncApp initialization

#define EXCEPTION_FILE_PATH _T("exception.log")

BOOL CcncApp::InitInstance()
{
	//ֻ����һ������ʵ��
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


	//�쳣����
	CString strFullPath = GetModuleFullPath();
	strFullPath += EXCEPTION_FILE_PATH;
	CExceptionCatch::LogToFile( (CT2A)strFullPath );
	CExceptionCatch::Start();   

	//ץ���쳣�ļ�
	::SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);  //cash����

	//CWndShadow::Initialize(m_hInstance);
	InitAppFrame(m_hInstance);

	new CSystem(_T("system.xml"));

	//����cns session
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
    PrtMsg( "\nshowver: ��ʾ�汾�ͱ���ʱ��");
    //PrtMsg( "\ntask 1/0: �Ƿ����������������1������ ��0������");
    PrtMsg( "\nprt: ��ӡ���м���Ϊ3���ϵ���Ϣ");
    PrtMsg( "\nprtlevel nLevel: ��ӡ����ΪnLevel����Ϣ����Ϣ���� 1-3��\n \
    1Ϊ������ߵ���Ϣ���ü������Ϣ��ϵͳ���ܲ�������Ӱ��\n \
    2Ϊһ�㼶�����Ϣ\n \
    3Ϊ��ͼ�����Ϣ " );
    PrtMsg( "\nprtid msgID: ��ӡ��Ϣ����msgID����Ϣ");
    PrtMsg( "\nprtrange MaxMsgID, MinMsgID: ��ӡ��Ϣ�ŷ�Χ�� MinMsgID �� MaxMsgID ֮�����Ϣ");
    PrtMsg( "\nstopprt: ֹͣ��ӡ������Ϣ");
    //PrtMsg( "\nprtrecive 0 / 1: ��ӡ���н��ܵ�����Ϣ, 0:����ӡ��1:��ӡ");
    //PrtMsg( "\nprtsend 0 / 1: ��ӡ���з��ͳ�ȥ����Ϣ, 0:����ӡ��1:��ӡ"); 
    PrtMsg( "\nshowallconf: ��ʾ���л�����Ϣ");
    PrtMsg( "\nshowcns: ��ʾ���ػ᳡��Ϣ");
    PrtMsg( "\nshowconf : ��ʾ���᳡���ڵĻ�����Ϣ");
    PrtMsg( "\nhangupep wConfID epID: �Ҷϻ����еĻ᳡��wConfID������ID��epID��������cns��ID"); 
    PrtMsg( "\nhangupconf wConfID: �Ҷϻ��飬wConfID������ID");  
    PrtMsg( "\nshowconfcns wCnsID: ��ʾ�����л᳡��Ϣ��wCnsID��������cns��ID");
    PrtMsg( "\nshowcnsstate: cns����״̬");
    //PrtMsg( "\nshowalltemp: ��ʾ��Ӧ��ģ����Ϣ��������ʾ����ģ����Ϣ" );
    //PrtMsg( "\nshowtemp ID: ����ʾ��Ӧ��ģ����Ϣ " );
    PrtMsg( "\nshowscrninfo: ��ʾ����ѡ����Ϣ ");
    PrtMsg( "\nshowvmpinfo: ��ʾ����ϳ���Ϣ" );   
    PrtMsg( "\nshowalluser: ��ʾ�����û���Ϣ" );
    //PrtMsg( "\nshowlocalip: ��ʾ����PC��IP" );
    //PrtMsg( "\nsetdecvol 0-255: ���ý�������������Χ 0-255" );
    //PrtMsg( "\nshowdecvol :��ʾ��ǰ��������������Χ 0-255" );
    //PrtMsg( "\nshowalarm: ��ʾ��ǰ���и澯��Ϣ" );
    PrtMsg( "\nshowaddrbook: ��ʾ��ǰ��ַ����Ϣ" );
    PrtMsg( "\nshowonlineaddr: ��ʾȫ�ֵ�ַ����Ϣ" );
    PrtMsg( "\nshowaddrentry dwEntryIndex: ��ʾ��ַ���᳡��Ϣ, dwEntryIndex:�᳡����" );
    PrtMsg( "\ndeleteaddr dwEntryIndex: ɾ����ַ���᳡��Ϣ, dwEntryIndex:�᳡����" );
	PrtMsg( "\nfreshconf��ˢ�»���״̬" );
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

// ��ʾ���л���
API void showallconf()
{
    COutPrint::GetAllConfInfo();
}

//��ʾĳID�Ļ�����Ϣ
API void showconf()
{
    //COutPrint::GetConfInfo( wConfID );
    COutPrint::GetConfCnsInfo( );
}



//��ʾ������cns����Ϣ
API void showconfcns( u16 wCnsID )
{
    COutPrint::GetConfCnsInfo( wCnsID );
}

//��ʾ �᳡��Ϣ
API void showcns()
{
    COutPrint::GetLocalCnsInfo();
}


//��ʾ����cns״̬
API void showcnsstate()
{
    COutPrint::IsLocalCnsInConf();
}


API void showvmpinfo()
{
    COutPrint::ShowVmpInfo();
}

//��ʾ����ѡ����Ϣ
API void showscrninfo()
{
    COutPrint::ShowScrnInfo();
}

//��ʾ�����û���Ϣ
API void showalluser()
{
     COutPrint::ShowAllUseInfo();
}

API void  showlocalip()
{
    COutPrint::ShowLocalIP();
}


//�Ҷ�ĳ�����е�ĳ���᳡
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

//��������
API void hangupconf( u16 wConfID )
{   
//     u16 re = BusinessManagePtr->HangupConf(   );
//     if ( re != NO_ERROR )
//     {
//         PrtMsg("\n[API void hangupconf]re = %d \n", re );
//     }
    
}


//��ʾ��ַ����Ϣ
API void showaddrbook()
{
    COutPrint::ShowAddrbook();
}

//��ʾȫ�ֵ�ַ����Ϣ
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
