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

//bIsSelfStart �Ƿ��Լ���������  bool bIsSuccess �Ƿ����ɹ�
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

	//��ȡϵͳ�汾
	m_pMySelf->GetWindowsSysVersion();

	//creatsession��ʱ��ע��װ����Ļص�����  dyy 2014-5-14 

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


//����һ���µĽ��̣����ȴ������
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

		CloseHandle( pi.hThread );// �ر��ӽ��̵����߳̾��

		WaitForSingleObject( pi.hProcess, INFINITE );//�ȴ��������

		//GetExitCodeProcess(pi.hProcess, &dwExitCode);// ��ȡ�ӽ��̵��˳���

		CloseHandle( pi.hProcess );// �ر��ӽ��̾��
		return 0;
	} 

	//�����ѽ���
	//pTItemInfo->dwProcID = 0;

	//������Ϣ��ˢ���б�
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

//�ж��Ƿ�Ϊ64λϵͳ  dyy
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
		// ����������С������ָ����С   
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


//���ݽ���ID����ʾ��Ӧ�Ĵ��ڣ����ظô��ڵľ��
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

			// ����������С������ָ����С   
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
		// ����Ѱ����һ������   
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
					ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0); //�ػ�
				}
				break;
			case emReboot:
				ExitWindowsEx( EWX_REBOOT | EWX_FORCE, 0 ); //����
				break;
			case emSleep:
				SetSystemPowerState( true, true );  //���� 
				//SetSystemPowerState( false, true ); //���� 
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

	//C--->Z��, �������� ��鵽n��
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
����:  ���ҵ�һ������ָ���ļ���strFileName��U�̵��̷�
����:  strPathName :�����ҵ����̷����� eg c:\ strFileName : ����·�����ļ�����
����ֵ: TRUE: ���ڣ�FALSE: ������
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
	//C--->Z��, �������� ��鵽n��
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
				//�ж��Ƿ����ָ���ļ�
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
����:   �ж�ָ����U���Ƿ�������豸
����:   nDiskNo : �̷�ֵ 
����ֵ: TRUE: �Ѳ��룬FALSE: δ����
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
		//�ж��Ƿ�֧��д�����
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
		//����ǿ��ƶ����̣��õ���������̺�
		if(DRIVE_REMOVABLE == GetDriveType(pszName ))
		{
			TCHAR szVolName[MAX_PATH] = { 0 };                      

			GetVolumeInformation( pszName, szVolName, MAX_PATH, NULL,NULL,/*&VolFlags*/NULL,NULL,NULL);

			if ( 0 == lstrlen( (szVolName) ))
			{
				lstrcpy( (szVolName), _T("���ƶ�����") );

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

			tDongleDiskInfo.setNULL();   //���
		}
		else if (DRIVE_FIXED == GetDriveType((pszName)))
		{

			HANDLE hDevice;         // �豸���
			BOOL bResult;           // DeviceIoControl�ķ��ؽ��


			// ���豸
			CString DeviceName;
			DeviceName.Format(_T("\\\\.\\%s"),pszName);
			DeviceName = DeviceName.Left( DeviceName.Find(_T(":")) + 1 );

			hDevice = ::CreateFile(DeviceName,           // �ļ���
				GENERIC_READ,                          // ������Ҫ����
				FILE_SHARE_READ | FILE_SHARE_WRITE,    // ����ʽ
				NULL,                                  // Ĭ�ϵİ�ȫ������
				OPEN_EXISTING,                         // ������ʽ
				0,                                     // ���������ļ�����
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

			// �� IOCTL_STORAGE_QUERY_PROPERTY            
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
					lstrcpy( (szVolName), _T("���ƶ�Ӳ��") );                   
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

				tDongleDiskInfo.setNULL();   //���
			}

			::CloseHandle(hDevice); //�رվ��
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

	//��ȡϵͳ�汾
	OSVERSIONINFOEX osvi;
	BOOL bOsVersionInfoEx;
	//����OSVERSIONINFOEX�ṹ����GetVersionEx()����
	//�������ʧ�ܣ��ɳ���ʹ��OSVERSIONINFO�ṹ
	ZeroMemory( &osvi, sizeof(OSVERSIONINFOEX) );
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if( !( bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO*)&osvi) ) )
	{
		osvi.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
		if(!GetVersionEx((OSVERSIONINFO*)&osvi))
			return ;
	}

	//windows8������
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
	LPCSTR windName = "��������";
	if ( _access(achFileName, 0) != 0 )
	{
		windName = "��Ļ����";
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