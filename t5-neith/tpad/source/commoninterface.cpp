// CommonInterface.cpp: implementation of the CCommonInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CommonInterface.h"
#include "direct.h"
#include <io.h>

CCommonInterface* CCommonInterface::m_pMySelf = NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommonInterface::CCommonInterface() :
					m_pTPadSession(NULL),
					m_pTpadConfCtrl(NULL),
					m_bIsWin8(FALSE),
					m_bReceiveDual(FALSE),
                    m_bAutoLogin(FALSE)
{
	m_hRecvWnd = ::CreateWindowEx(0, _T("Static"), _T("CncCommon"), WS_DISABLED,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, 0, 0);

	if ( m_hRecvWnd != NULL )
	{
		m_wndprocOld = reinterpret_cast<WNDPROC>(GetWindowLong(m_hRecvWnd, GWL_WNDPROC));
		SetWindowLong(m_hRecvWnd, GWL_WNDPROC, reinterpret_cast<s32>(WndProc));
	} 
	else
	{
		m_wndprocOld = NULL;
	}

	m_tItemInfo.SetNull();
}

CCommonInterface::~CCommonInterface()
{

}

//bIsSelfStart 是否自己主动开启  bool bIsSuccess 是否开启成功
void WBConfStart( bool bIsSelfStart, bool bIsSuccess )
{
	ComInterface->WBConfStartNty( bIsSelfStart, bIsSuccess );
}

CCommonInterface* CCommonInterface::GetCommIF()
{
	if ( NULL != m_pMySelf )
	{
		return m_pMySelf ;
	}

	m_pMySelf = new CCommonInterface;

	//获取系统版本
	m_pMySelf->GetWindowsSysVersion();

	//creatsession的时就注册白板会议的回调函数  dyy 2014-5-14 

	WB_API_RegCallbakFun( WBConfStart );

	return m_pMySelf;
}


void CCommonInterface::DestroyCommIF()
{   
	if ( NULL != m_pMySelf )
	{
		delete m_pMySelf;
		m_pMySelf = NULL;
	}
}


LRESULT CALLBACK CCommonInterface::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if ( uMsg > CMS_MSG_BEGIN ) 
	{
		NOTIFY_MSG( uMsg, wParam, lParam );
	}
	else
	{
		if ( ComInterface->m_wndprocOld != NULL )
		{
			return CallWindowProc(ComInterface->m_wndprocOld, hWnd, uMsg, wParam, lParam);
		}
	}
	return 0;
}


//创建一个新的进程，并等待其结束
UINT ThrdExCreatProc( LPVOID lpParam )
{
	TMainMenuInfo* pTItemInfo = (TMainMenuInfo*)lpParam;
	if ( pTItemInfo == NULL )
	{
		return 0;
	}

	STARTUPINFO   si; 
	PROCESS_INFORMATION   pi; 

	ZeroMemory( &si,  sizeof(si) ); 
	si.cb  =  sizeof(si); 

	BOOL bRe = CreateProcess(  NULL,  (pTItemInfo->achExePath) , NULL, NULL, FALSE, 
		NORMAL_PRIORITY_CLASS, NULL,  NULL,  &si,   &pi) ;

	if ( bRe )
	{
		//pTItemInfo->dwProcID = pi.dwProcessId;
		//CMsgDispatch::SendMessage( UI_TPAD_UPDATE_MAINMENU, 0, 0 );

		CloseHandle( pi.hThread );// 关闭子进程的主线程句柄

		WaitForSingleObject( pi.hProcess, INFINITE );//等待程序结束

		//GetExitCodeProcess(pi.hProcess, &dwExitCode);// 获取子进程的退出码

		CloseHandle( pi.hProcess );// 关闭子进程句柄
		return 0;
	} 

	//进程已结束
	//pTItemInfo->dwProcID = 0;

	//发送消息，刷新列表
	//CMsgDispatch::SendMessage( UI_TPAD_UPDATE_MAINMENU, 0, 0 );

	return 0;
}


void CCommonInterface::OpenExe( TMainMenuInfo tItemInfo )
{   
	m_tItemInfo.SetNull();
	if (_tcsicmp(tItemInfo.achExePath, _T("")) != 0)
	{
		m_tItemInfo = tItemInfo;
	}

	LPCWSTR className = NULL;
	LPCWSTR windName = NULL;

	if (_tcsicmp(tItemInfo.achExeClassName, _T("")) != 0) 
	{
		className = tItemInfo.achExeClassName;
	}

	if (_tcsicmp(tItemInfo.achExeCaption, _T("")) != 0)
	{
		windName = tItemInfo.achExeCaption;
	}

	HWND hWnd = ::FindWindow( className , windName );
	if ( !IsWindow( hWnd ) )
	{
		AfxBeginThread( ThrdExCreatProc, &m_tItemInfo );
		return;
	}

	if (::IsIconic(hWnd)) 			
	{
		::PostMessage( hWnd,WM_SHOWWINDOW , 0, 0 );//::PostMessage( hWnd, WM_REDRAW_UI, 0, 0 );
		::ShowWindow( hWnd, SW_RESTORE );
	}
	else
	{
		::ShowWindow( hWnd, SW_SHOW );
	}

	::SetForegroundWindow( hWnd );
}

//判断是否为64位系统  dyy
BOOL CCommonInterface::Is64BitSystem()
{      
	typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

	LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(CA2T("kernel32")), "IsWow64Process" );
	BOOL bIsWow64 = FALSE;

	if (NULL != fnIsWow64Process)
	{
		fnIsWow64Process(GetCurrentProcess(),&bIsWow64);
	} 

	return bIsWow64;
} 


BOOL CALLBACK EnumWindowsProce( HWND hwnd,    LPARAM lParam     ) 
{
	DWORD wndProcId = 0;
	GetWindowThreadProcessId( hwnd, &wndProcId );
	if (  wndProcId == lParam )   
	{   
		HWND   hMain  = GetAncestor( hwnd,/*GA_ROOT*/  GA_ROOTOWNER  );
		HWND   hRoot = GetAncestor(hwnd,GA_ROOT);
		if ( hMain == 0 )
		{
			hMain = hwnd;
		}
		// 主窗口已最小化，则恢复其大小   
		if (::IsIconic(hMain)) 				
			::ShowWindow(hMain,SW_RESTORE);   

		HWND hdl = ::GetForegroundWindow();
		if ( hMain !=  hdl )
		{   					
			::ShowWindow(hMain,/*SW_RESTORE*/SW_NORMAL); 

			//   ::SendMessage(cWnd->m_hWnd,WM_SYSCOMMAND,SC_RESTORE,0);

			::SetForegroundWindow(hwnd);
		}

		return TRUE;
	}

	return FALSE;
}


//根据进程ID，显示对应的窗口，返回该窗口的句柄
HWND CCommonInterface::ShowWndByProID( u32 dwProcID )
{

	EnumWindows( EnumWindowsProce,dwProcID );
	return 0;


	HWND  hWndPrevious = ::GetWindow(::GetDesktopWindow(),GW_CHILD);   
	while (::IsWindow(hWndPrevious))   
	{   

		DWORD wndProcId = 0;
		GetWindowThreadProcessId( hWndPrevious, &wndProcId );
		if ( wndProcId == dwProcID )   
		{   
			HWND   hMain  = GetAncestor( hWndPrevious,/*GA_ROOT*/ /*GA_ROOTOWNER*/GA_PARENT );
			if ( hMain == 0 )
			{
				hMain = hWndPrevious;
			}

			::SendMessage(hMain,WM_SHOWWINDOW,0,0);

			return 0;

			// 主窗口已最小化，则恢复其大小   
			if (::IsIconic(hMain)) 				
				::ShowWindow(hMain,SW_RESTORE);   

			HWND hdl = ::GetForegroundWindow();
			if ( hMain !=  hdl )
			{   					
				::ShowWindow(hMain,/*SW_RESTORE*/SW_MAX); 
				::SetForegroundWindow(hMain);
			}

			return   hMain;   
		}   
		// 继续寻找下一个窗口   
		hWndPrevious = ::GetWindow(hWndPrevious,GW_HWNDNEXT); 
	}  

	return 0;

}


void CCommonInterface::ExitWindowsOS( EM_OSType emOSType )
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;

	//   Get   a   token   for   this   process.
	if ( TRUE == OpenProcessToken( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) )
	{
		// Get   the   LUID   for   the   shutdown   privilege.
		LookupPrivilegeValue( NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid );

		tkp.PrivilegeCount = 1;     //   one   privilege   to   set
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

		// Get   the   shutdown   privilege   for   this   process.
		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0 );

		if ( GetLastError() == ERROR_SUCCESS )
		{   
			// Shut   down   the   system   and   force   all   applications   to   close.
			switch( emOSType )
			{
			case emShutDown:
				if ( TRUE == ExitWindowsEx( EWX_POWEROFF | EWX_FORCE, 0 ) )
				{
					ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0); //关机
				}
				break;
			case emReboot:
				ExitWindowsEx( EWX_REBOOT | EWX_FORCE, 0 ); //重启
				break;
			case emSleep:
				SetSystemPowerState( true, true );  //待机 
				//SetSystemPowerState( false, true ); //休眠 
				break;
			default:
				break;
			}				
		}
	}
}


BOOL CCommonInterface::ExistDir(const CString strDir)
{
	CFileStatus fs;
	return CFile::GetStatus(strDir, fs);
}

BOOL CCommonInterface::CreateDir(CString strDir)
{
	if (ExistDir(strDir))
		return TRUE;
	if (strDir.Right(1) != _T("\\"))
		strDir += _T("\\");

	// can not create network directory
	int nPos = strDir.Find(_T(":"));
	if (nPos == -1)
		return FALSE;
	// no need to create drive
	nPos = strDir.Find(_T("\\"), nPos + 1);
	if (nPos + 1 == strDir.GetLength())
		return TRUE;

	CFileStatus fs;
	while (nPos < strDir.GetLength() - 1)
	{
		nPos = strDir.Find(_T("\\"), nPos + 1);
		if (!CFile::GetStatus(strDir.Left(nPos), fs))
		{
			if (/*_tmkdir*/_tmkdir(strDir.Left(nPos)) == -1)
				return FALSE;
		}
	}
	return TRUE;
}


BOOL CCommonInterface::GetUDiskList( vector<CString>& vctUDisk )
{
	BOOL bExist = FALSE;	
	CString strTemp  = _T("");
	vctUDisk.clear();

	//C--->Z盘, 考虑性能 检查到n盘
	for ( s32 i = 99; i <= 110/*122*/; i++ )
	{
		// 		strTemp = (s32)i;
		// 		strTemp += _T(":\\");
		strTemp.Format(_T("%d:\\"),i);

		if ( GetDriveType( strTemp ) == DRIVE_REMOVABLE )
		{
			BOOL32 bInsert = IsUDiskInsert( i );

			if ( bInsert )
			{
				bExist = TRUE;
				vctUDisk.push_back( strTemp );
			}
		}
	}

	return bExist;
}


/*
功能:  查找第一个存在指定文件名strFileName的U盘的盘符
参数:  strPathName :返回找到的盘符名称 eg c:\ strFileName : 不带路径的文件名称
返回值: TRUE: 存在，FALSE: 不存在
*/
BOOL CCommonInterface::GetFirstUDiskNameByFileName( CString& strPartName, const CString& strFileName, BOOL& bHaveUDisk )
{
	if ( strFileName.IsEmpty() )
	{
		return FALSE;
	}

	bHaveUDisk = FALSE;
	BOOL32 bExist = FALSE;	
	CString strTemp  = _T("");
	CString strCheck = _T("");

	strPartName = _T("");
	//C--->Z盘, 考虑性能 检查到n盘
	for ( s32 i = 99; i <= 110/*122*/; i++ )
	{
		// 		strTemp = (s32)i;
		// 		strTemp += _T(":\\");
		TCHAR tchar = (char)i;
		strTemp = tchar;
		strTemp = strTemp +  _T(":\\");
		if ( GetDriveType( strTemp ) == DRIVE_REMOVABLE )
		{
			BOOL32 bInsert = IsUDiskInsert( i );

			if ( bInsert )
			{
				bHaveUDisk = TRUE;
				//判断是否存在指定文件
				strCheck = strTemp + strFileName;

				bExist = IsFileExist( strCheck );				
				if ( bExist )
				{
					strPartName = strTemp;
					bExist = TRUE;
					break;
				}
			}
		}
	}

	return bExist;
}



BOOL CCommonInterface::IsFileExist( LPCTSTR lpszFilePath )
{
	BOOL bExist = FALSE;
	HANDLE hFile = NULL;

	hFile = CreateFile( lpszFilePath
		, GENERIC_READ
		, FILE_SHARE_READ | FILE_SHARE_WRITE
		, NULL
		, OPEN_EXISTING
		, 0
		, 0
		);

	if( hFile != INVALID_HANDLE_VALUE )
	{
		CloseHandle( hFile );
		bExist = TRUE;
	}

	return bExist;
}


/*
功能:   判断指定的U盘是否插入了设备
参数:   nDiskNo : 盘符值 
返回值: TRUE: 已插入，FALSE: 未插入
*/
BOOL CCommonInterface::IsUDiskInsert( int nDiskNo )
{
	BOOL bExist = FALSE;

	if ( nDiskNo < 99 || nDiskNo > 122 )
	{
		return bExist;
	}

	char  szName[10] = {0};
	sprintf(szName, "%c:\\", nDiskNo);

	UINT nDriveType = 0 ;
	nDriveType = GetDriveType( CA2T(szName) );

	if ( nDriveType == DRIVE_REMOVABLE )
	{
		//判断是否支持写入操作
		ULARGE_INTEGER a1, a2, a3;

		if ( GetDiskFreeSpaceEx(CA2T(szName), (PULARGE_INTEGER)&a1, (PULARGE_INTEGER)&a2, (PULARGE_INTEGER)&a3) != 0 )
		{
			if ( a1.QuadPart > 0 )
			{
				bExist =  TRUE;
			}
			else
			{
				bExist =  FALSE;
			}
		}
		else
		{
			bExist = FALSE;
		}
	}
	else
	{
		bExist = FALSE;
	}

	return bExist;
}

//overload of GetFolderFiles Function 
//can get the file numbers in one folder, not include hidden
DWORD CCommonInterface::GetFolderFilesCount( CString strFolderPath )
{
	DWORD dwFileCount = 0;   //count of files include folders in one folder

	if( strFolderPath.IsEmpty() == TRUE )
	{
		return dwFileCount;
	}

	u16 wIndex = strFolderPath.ReverseFind( _T('\\') );
	if ( wIndex == strFolderPath.GetLength()-1 )
	{
		strFolderPath.Delete(wIndex, 1);
	}
	strFolderPath +=  _T("\\*.*");


	CFileFind finder;
	BOOL bWorking = finder.FindFile(strFolderPath );
	if ( bWorking == 0 )
	{
		return dwFileCount;
	}

	while ( bWorking )
	{
		bWorking = finder.FindNextFile();
		if ( finder.IsDots() ||finder.IsHidden() ) 
		{
			continue;
		}

		dwFileCount++;

	}

	finder.Close();

	return dwFileCount;
}

DWORD CCommonInterface::GetUDiskList( vector<TFileItem>& vctUDisk)
{
	TFileItem tDongleDiskInfo;
	DWORD dwCount = 0;

	vctUDisk.clear();
	SetErrorMode(SEM_FAILCRITICALERRORS);  //set error mode

	//DWORD dwLen;
	//dwLen=GetLogicalDriveStrings( MAX_PATH-1, CA2T(szTemp) );

	DWORD dwLen=GetLogicalDriveStrings(0,NULL);
	if( dwLen == 0) //error
	{
		return FALSE;
	}
	LPTSTR lpDriveStrings=(LPTSTR)HeapAlloc(GetProcessHeap(),0,dwLen*sizeof(TCHAR));
	GetLogicalDriveStrings(dwLen,lpDriveStrings);



	LPTSTR pszName = lpDriveStrings;    
	while ( *pszName )
	{
		//如果是可移动磁盘，得到其物理磁盘号
		if(DRIVE_REMOVABLE == GetDriveType(pszName ))
		{
			TCHAR szVolName[MAX_PATH] = { 0 };                      

			GetVolumeInformation( pszName, szVolName, MAX_PATH, NULL,NULL,/*&VolFlags*/NULL,NULL,NULL);

			if ( 0 == lstrlen( (szVolName) ))
			{
				lstrcpy( (szVolName), _T("可移动磁盘") );

			}

			CString strTemp;
			strTemp.Format( _T("%s (%s)"), (szVolName), (pszName) );
			int index = strTemp.ReverseFind( '\\' );
			strTemp.Delete( index );

			memcpy(&tDongleDiskInfo.achFileName, strTemp, strTemp.GetLength()*2);
			memcpy(&tDongleDiskInfo.achFilePath, pszName, sizeof(pszName)*2);

			tDongleDiskInfo.bIsFolder = TRUE;  
			tDongleDiskInfo.em_DeviceType = emDevice_Udisk;
			CString strName(pszName);
			tDongleDiskInfo.dwFileCount = GetFolderFilesCount( strName );
			vctUDisk.push_back( tDongleDiskInfo );
			dwCount++;

			tDongleDiskInfo.setNULL();   //清空
		}
		else if (DRIVE_FIXED == GetDriveType((pszName)))
		{

			HANDLE hDevice;         // 设备句柄
			BOOL bResult;           // DeviceIoControl的返回结果


			// 打开设备
			CString DeviceName;
			DeviceName.Format(_T("\\\\.\\%s"),pszName);
			DeviceName = DeviceName.Left( DeviceName.Find(_T(":")) + 1 );

			hDevice = ::CreateFile(DeviceName,           // 文件名
				GENERIC_READ,                          // 软驱需要读盘
				FILE_SHARE_READ | FILE_SHARE_WRITE,    // 共享方式
				NULL,                                  // 默认的安全描述符
				OPEN_EXISTING,                         // 创建方式
				0,                                     // 不需设置文件属性
				NULL); 


			if (hDevice == INVALID_HANDLE_VALUE)
			{
				pszName+=lstrlen((pszName))+1;
				continue;
			}

			STORAGE_PROPERTY_QUERY Query; // input param for query
			DWORD dwOutBytes; // IOCTL output length

			Query.PropertyId = StorageDeviceProperty;
			Query.QueryType = PropertyStandardQuery;

			STORAGE_DEVICE_DESCRIPTOR pDevDesc;

			pDevDesc.Size = sizeof(STORAGE_DEVICE_DESCRIPTOR);

			// 用 IOCTL_STORAGE_QUERY_PROPERTY            
			bResult = ::DeviceIoControl(hDevice, // device handle
				IOCTL_STORAGE_QUERY_PROPERTY, // info of device property
				&Query, sizeof(STORAGE_PROPERTY_QUERY), // input data buffer
				&pDevDesc, pDevDesc.Size, // output data buffer
				&dwOutBytes, // out's length
				(LPOVERLAPPED)NULL);


			UINT Type = pDevDesc.BusType;
			if ( Type == 0x07/*BusTypeUsb*/ )
			{
				TCHAR szVolName[MAX_PATH] = { 0 };                      

				GetVolumeInformation( pszName, szVolName, MAX_PATH, NULL,NULL,/*&VolFlags*/NULL,NULL,NULL);

				if ( 0 == lstrlen( (szVolName) ))
				{
					lstrcpy( (szVolName), _T("可移动硬盘") );                   
				}

				CString strTemp;
				strTemp.Format( _T("%s (%s)"), szVolName, pszName );
				int index = strTemp.ReverseFind( '\\' );
				strTemp.Delete( index );

				memcpy(&tDongleDiskInfo.achFileName, strTemp, sizeof(strTemp));
				memcpy(&tDongleDiskInfo.achFilePath, pszName, sizeof(pszName));

				tDongleDiskInfo.bIsFolder = TRUE;       
				tDongleDiskInfo.em_DeviceType = emDevice_HDD;
				CString strName(pszName);
				tDongleDiskInfo.dwFileCount = GetFolderFilesCount( strName );
				vctUDisk.push_back( tDongleDiskInfo );
				dwCount++;

				tDongleDiskInfo.setNULL();   //清空
			}

			::CloseHandle(hDevice); //关闭句柄
		}

		pszName+=lstrlen((pszName))+1;
	}

	return dwCount;
}

void CCommonInterface::KillProcess( LPCSTR pszWindowTitle)
{
	HANDLE hProcessHandle;  
	ULONG nProcessID;
	HWND  hTheWindow;

	hTheWindow = ::FindWindow( NULL, CA2T(pszWindowTitle) );
	if ( !IsWindow( hTheWindow ) )
	{
		return;
	}

	::GetWindowThreadProcessId( hTheWindow, &nProcessID );

	hProcessHandle = ::OpenProcess( PROCESS_TERMINATE, FALSE, nProcessID );

	::TerminateProcess( hProcessHandle, 4 );
}

void CCommonInterface::GetWindowsSysVersion()
{
	m_bIsWin8 = FALSE;

	//获取系统版本
	OSVERSIONINFOEX osvi;
	BOOL bOsVersionInfoEx;
	//利用OSVERSIONINFOEX结构调用GetVersionEx()函数
	//如果调用失败，可尝试使用OSVERSIONINFO结构
	ZeroMemory( &osvi, sizeof(OSVERSIONINFOEX) );
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if( !( bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO*)&osvi) ) )
	{
		osvi.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
		if(!GetVersionEx((OSVERSIONINFO*)&osvi))
			return ;
	}

	//windows8及以上
	if ( (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion >= 2) || osvi.dwMajorVersion > 6  )
	{
		m_bIsWin8 = TRUE;
	}

	m_osvi = osvi;
}

void CCommonInterface::GetSysVersion( OSVERSIONINFOEX& osvi )
{
	osvi = m_osvi;
}


void CCommonInterface::ShowKeyboard()
{
#ifdef _DEBUG
    return;
#endif

	char * achFileName= "C:\\Program Files\\Common Files\\microsoft shared\\ink\\TabTip.exe";
	CString strFileName = _T("C:\\Program Files\\Common Files\\microsoft shared\\ink\\TabTip.exe");
	LPCSTR windName = "触摸键盘";
	if ( _access(achFileName, 0) != 0 )
	{
		windName = "屏幕键盘";
		strFileName = _T("osk.exe");
	}

	HWND hWnd = ::FindWindow( NULL, CA2T(windName) );
	if ( !IsWindow( hWnd ) )
	{
		ShellExecute( NULL, NULL, strFileName, NULL, NULL,SW_NORMAL);
	}

	if (::IsIconic(hWnd)) 			
	{
		::ShowWindow( hWnd, SW_RESTORE );
	}
	else
	{
		::ShowWindow( hWnd, SW_SHOW );
	}
}

u16 CCommonInterface::GetLoginRet(TLoginRet& tLoginRet)
{
	if ( NULL == m_pTPadSession )
	{
		return ERR_CMS;
	}

	tLoginRet = m_pTPadSession->GetLoginRet();
    return NO_ERROR;
}


void CCommonInterface::SetReceiveDual( BOOL bDual )
{
	m_bReceiveDual = bDual;
}

BOOL CCommonInterface::IsReceiveDual()
{
	return m_bReceiveDual;
}

void CCommonInterface::T300UpdateInd( BOOL bIsUpT300 )
{
	if ( NULL != m_pTPadSession ) 
	{
		m_pTPadSession->T300UpdateInd( bIsUpT300 );
	}	
}

u16  CCommonInterface::GetTPadVerInfo( TTPTPadVerInfo &tTPTPadVerInfo )
{ 
	if( NULL == m_pTPadSession )
	{
		return ERR_CMS;
	}

	tTPTPadVerInfo  = m_pTPadSession->GetTPadVerInfo();
	return NO_ERROR;
}

u16 CCommonInterface::GetCnFtpInfo(TTPFtpInfo &tTPFtpInfo)
{
	if( NULL == m_pTPadSession )
	{
		return ERR_CMS;
	}

	tTPFtpInfo  = m_pTPadSession->GetCnFtpInfo();
	return NO_ERROR;
}

u16 CCommonInterface::SetCnFtpInfo(const TTPFtpInfo tTPFtpInfo)
{
    if( NULL == m_pTPadSession )
    {
        return ERR_CMS;
    }

    return m_pTPadSession->SetCnFtpInfo(tTPFtpInfo);
}

void CCommonInterface::SetAutoLogin( BOOL bAuto )
{
    m_bAutoLogin = bAuto;
}

BOOL CCommonInterface::IsAutoLogin()
{
    return m_bAutoLogin;
}