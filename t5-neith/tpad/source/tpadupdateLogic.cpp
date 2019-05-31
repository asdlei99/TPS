#include "StdAfx.h"
#include "tpadupdateLogic.h"

//系统升级线程
UINT ThreadTpadUpdate(LPVOID lpParam)
{   
	CTPadUpdateLogic::GetSingleton().UnZip();
	return NO_ERROR;
} 

template<> CTPadUpdateLogic* Singleton<CTPadUpdateLogic>::ms_pSingleton  = NULL;
APP_BEGIN_MSG_MAP(CTPadUpdateLogic, CNotifyUIImpl)

	MSG_CREATEWINDOW(_T("UpdateLayout"), OnCreate)
	MSG_INIWINDOW(_T("UpdateLayout"), OnInit)
	MSG_WINDOWDESTORY(_T("UpdateLayout"), OnDestroy)

	USER_MSG(UI_CNS_DISCONNECTED,OnDisconnect)

	MSG_CLICK(_T("BtnOk"), OnBtnOk)
	MSG_CLICK(_T("BtnCancel"), OnBtnCancel)
	USER_MSG( UI_TPADUPDATE_PROGRESS, OnLoadTPadProgress )
    USER_MSG( UI_CNSETFTPRSP, OnSetCnFtpRsp )

APP_END_MSG_MAP()


CTPadUpdateLogic::CTPadUpdateLogic( void )
{
	m_emDownState = emDownNo;
    m_bIsWaitForFtp = false;
}


CTPadUpdateLogic::~CTPadUpdateLogic(void)
{
}


bool CTPadUpdateLogic::OnCreate( TNotifyUI& msg )
{
	REG_TPAD_MSG_WND_OB(m_pm->GetPaintWindow());

	s32 nTop = 0;
	RECT rcParent;
	HWND hparent = GetParent(m_pm->GetPaintWindow());
	GetWindowRect(hparent,&rcParent);
	SIZE szDlg = m_pm->GetInitSize();
	s32 nLeft = (rcParent.right - rcParent.left - szDlg.cx)/2;
	nTop = (rcParent.bottom - rcParent.top - szDlg.cy)/2;
	if ( CPaintManagerUI::IsSelfAdaption() )
	{
		float fAdpX, fAdpY;
		CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
		nTop = s32(nTop * fAdpY);
		nLeft = s32(nLeft * fAdpY);
	}
	SetWindowPos( m_pm->GetPaintWindow(), NULL, nLeft, nTop, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );
	return false;
}

bool CTPadUpdateLogic::OnInit(TNotifyUI& msg)
{
	m_emFtpStatus = emFtpEnd;
	ComInterface->GetTPadVerInfo(m_tTPadVerInfo);

	s8 achVersion[MAX_DEVICEVER_LEN] = {0};
	ComInterface->GetTPadVersion( achVersion );

	CString strVer(m_tTPadVerInfo.m_achTPadVersion);
	CString strOriVer(achVersion);

	CString strTip;
	int numCheckReturn = wcscmp(strVer,strOriVer);
	if (0 > numCheckReturn)
	{
		strTip.Format(_T("系统检测到版本%s,请确认是否回退此版本?"),strVer);
		ITPadCommonOp::SetControlText( _T("立即回退"), m_pm, _T("BtnOk") );
	}
	else
	{
		strTip.Format(_T("系统检测到新版本%s,请确认是否升级?"),strVer);
	}

	ITPadCommonOp::SetControlText( strTip, m_pm, _T("LabelTip") );

	return true;
}

bool CTPadUpdateLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	if ( emFtpEnd != m_emFtpStatus )
	{
		m_emFtpStatus = emFtpEnd;
		m_cFtp.EndFtpFile();
		m_emDownState = emDownNo;
	}

    m_bIsWaitForFtp = false;

	WINDOW_MGR_PTR->CloseWindow(g_strUpdateDlg.c_str(), IDCANCEL);
	CTPadUpdateLogic::RemoveInstance();
	return NO_ERROR;
}

bool CTPadUpdateLogic::OnDestroy( TNotifyUI& msg )
{
	UNREG_TPAD_MSG_WND_OB(m_pm->GetPaintWindow());
	return true;
}


bool CTPadUpdateLogic::OnBtnOk(TNotifyUI& msg)
{
	if (m_emDownState == emDownNo)
	{
		DownLoadFile();
	}

	if (m_emDownState == emDownFail)
	{
		OnBtnCancel(msg);
	}

	if (m_emDownState == emDownEnd)
	{
		//m_pm->DoCase(_T("caseDownLoadEnd"));
		//AfxBeginThread( ThreadTpadUpdate, NULL );

		//重启系统
		ComInterface->ExitWindowsOS( emReboot );
	}

	return true;
}


bool CTPadUpdateLogic::OnBtnCancel(TNotifyUI& msg)
{
	if ( emFtpEnd != m_emFtpStatus )
	{
		m_cFtp.EndFtpFile();
		m_emDownState = emDownNo;
		m_emFtpStatus = emFtpEnd;
	}

    m_bIsWaitForFtp = false;
	
	m_pm->DoCase(_T("caseNoUpdate"));
	WINDOW_MGR_PTR->CloseWindow(g_strUpdateDlg.c_str(), IDCANCEL);
	CTPadUpdateLogic::RemoveInstance();
	return true;
}


bool CTPadUpdateLogic::OnLoadTPadProgress( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	EmFtpStatus emFileFtpStatus = static_cast<EmFtpStatus>(wParam);
	m_emFtpStatus = static_cast<EmFtpStatus>(wParam);

	switch( m_emFtpStatus )
	{
	case emFtpBegin:
		{
			m_nProgress = 0;
			m_pm->DoCase(_T("caseUpdate"));
			m_emDownState = emDowning;
		}
		break;
	case emFtpTransfer:
		{
			int dwCurrentFtpSize = m_cFtp.GetCurrentFtpSize();
			int dwtTotalFileSize = m_cFtp.GetTotalFileSize();
			if ( dwtTotalFileSize != 0)
			{
				int dwFtpProgress = ( 100 * (float)m_cFtp.GetCurrentFtpSize() )/(m_cFtp.GetTotalFileSize() );			
				CString str;
				str.Format(_T("已完成：%d%%"),dwFtpProgress);

				ITPadCommonOp::SetControlText(str,m_pm,_T("LbProgress"));
				CProgressUI* pProBar = (CProgressUI*)ITPadCommonOp::FindControl(m_pm, _T("progressBar"));
				if (pProBar)
				{
					pProBar->SetValue(dwFtpProgress);
				}
			}
		}
		break;
	case emFtpEnd:
		{
			DWORD dwSuccess = static_cast<DWORD>(lParam);     //FTP接口0为成功  默认失败
			if ( 0 == dwSuccess )
			{		
				CString str;
				str.Format(_T("已完成：100%%"));

				ITPadCommonOp::SetControlText(str,m_pm,_T("LbProgress"));
				CProgressUI* pProBar = (CProgressUI*)ITPadCommonOp::FindControl(m_pm, _T("progressBar"));
				if (pProBar)
				{
					pProBar->SetValue(100);
				}

				//m_pm->DoCase(_T("caseDownLoadEnd"));     
				m_emDownState = emDownEnd;
				m_pm->DoCase(_T("caseIntall"));
				AfxBeginThread( ThreadTpadUpdate, NULL );
			}
			else
			{
				//FtpFindFirstFile Error With 18--没有更多文件.这是获取远端文件大小的时候提示的错误,不关闭Ftp,之后可以成功
				if ( dwSuccess == 18 )  
				{
					break;
				}

				LPTSTR pszMsg = NULL;
				m_cFtp.FormatFtpError( dwSuccess, &pszMsg );
				
				CString str;
				if (dwSuccess == 122)
				{
					str += _T("下载失败，错误原因：系统找不到指定的文件。");
				}
				else
				{
					CString strError(pszMsg);
					if (strError.IsEmpty())
					{
						str.Format(_T("下载失败，错误号：%d"), dwSuccess);
					}
					else
					{
						str.Format(_T("下载失败，错误原因：%s"), strError);
					}
				}
				
				
				ITPadCommonOp::SetControlText(str,m_pm,_T("LabelTip"));
				LocalFree( pszMsg );
				
				m_pm->DoCase(_T("caseDownLoadFail"));  
				m_emDownState = emDownFail;
			}

			m_cFtp.EndFtpFile();
		}
		break;
	default:
		break;
	}

	return true;
}


bool CTPadUpdateLogic::DownLoadFile()
{
	//禁用升级，防止连续点击
	ITPadCommonOp::EnableControl( false, m_pm, _T("BtnOk") );

    TTPFtpInfo tTPFtpInfo;
    ComInterface->GetCnFtpInfo(tTPFtpInfo);
    if (tTPFtpInfo.bOpen == FALSE)
    {
        m_bIsWaitForFtp = true;
        tTPFtpInfo.bOpen = TRUE;
        ComInterface->SetCnFtpInfo(tTPFtpInfo);
        return false;
    }

    BeginDownload();

	return true;
}

bool CTPadUpdateLogic::BeginDownload()
{
    TTPFTPFileInfo tFileInfo = m_tTPadVerInfo.m_tPadVerFileInfo;

    CString strIP;
    in_addr addrIPAddr;
    addrIPAddr.S_un.S_addr = /*htonl*/(tFileInfo.dwSerIP);
    strIP = CA2T(inet_ntoa(addrIPAddr));

    TTPFtpInfo tTPFtpInfo;
    ComInterface->GetCnFtpInfo(tTPFtpInfo);

    m_cFtp.SethWnd( m_pm->GetPaintWindow() );
    m_cFtp.RegisterMsgHandle( UI_TPADUPDATE_PROGRESS );

    BOOL32 bRet = m_cFtp.SetServerParam( strIP, CA2W(tTPFtpInfo.achUserName)/*_T("admin")*/, CA2W(tTPFtpInfo.achPassword)/*_T("kedacomTP")*/ );
    if ( !bRet )
    {
        ITPadCommonOp::SetControlText( _T("连接服务器失败"), m_pm, _T("LabelTip") );
        ITPadCommonOp::EnableControl( true, m_pm, _T("BtnOk") );
        return FALSE;
    }


    CString strRemoteFile;
    strRemoteFile.Format(_T("%s"),CA2T( tFileInfo.achFilePath));

    int nIndex = strRemoteFile.ReverseFind( '/' );
    if ( nIndex == -1 )
    {
        ITPadCommonOp::EnableControl( true, m_pm, _T("BtnOk") );
        return false;
    }
    CString strFileName = strRemoteFile.Right( strRemoteFile.GetLength() - nIndex - 1 );

    CString strSavePath = GetModuleFullPath();
    m_strSavePath = strSavePath + strFileName;

    if ( !m_cFtp.BeginDownload( strRemoteFile, m_strSavePath, FTP_TRANSFER_TYPE_BINARY, FTP_AGENT, 0 ) ) 
    {
        ITPadCommonOp::SetControlText( _T("下载文件失败，参数错误"), m_pm, _T("LabelTip") );
        ITPadCommonOp::EnableControl( true, m_pm, _T("BtnOk") );
        return FALSE;
    }
}

bool CTPadUpdateLogic::UnZip()
{
	//将rar文件解压到updatetpad目录中
	CString str;
	str = _T("WinRAR.exe x -ibck -o+ -y ");

	CString cstrPath = GetModuleFullPath();
	cstrPath = cstrPath.Left( cstrPath.ReverseFind('\\') );
	CString strUpdatePath = cstrPath.Left( cstrPath.ReverseFind('\\') + 1 );
	strUpdatePath += _T("updatetpad");

	BOOL bExist = ComInterface->ExistDir( strUpdatePath );	
	if ( !bExist )
	{
		//不存在则创建
		ComInterface->CreateDir( strUpdatePath );
	}

	// Bug00183862 执行命令时 路径需加引号 否则无法识别
	CString strSavePath;
	strSavePath = m_strSavePath;
	strSavePath = _T("\"") + strSavePath + _T("\"");
	str += strSavePath; 


	str += _T(" ");
	strUpdatePath = _T("\"") + strUpdatePath + _T("\"");
	str += strUpdatePath;

	PROCESS_INFORMATION   pidInfo;
	STARTUPINFO           startInfo;
	startInfo.cb            =   sizeof(STARTUPINFO); 
	startInfo.lpReserved    =   NULL; 
	startInfo.lpTitle       =   NULL; 
	startInfo.lpDesktop     =   NULL; 
	startInfo.dwX           =   0; 
	startInfo.dwY           =   0; 
	startInfo.dwXSize       =   0; 
	startInfo.dwYSize       =   0; 
	startInfo.dwXCountChars =   0; 
	startInfo.dwYCountChars =   0; 
	startInfo.dwFlags       =   STARTF_USESTDHANDLES; 
	startInfo.wShowWindow   =   0;   //SW_SHOWDEFAULT; 
	startInfo.lpReserved2   =   NULL; 
	startInfo.cbReserved2   =   0; 
	startInfo.hStdInput     =   GetStdHandle(STD_INPUT_HANDLE); 
	startInfo.hStdOutput    =   GetStdHandle(STD_OUTPUT_HANDLE); 
	startInfo.hStdError     =   GetStdHandle(STD_ERROR_HANDLE); 

	CString strExePath;
	if ( ComInterface->Is64BitSystem() )//对操作系统类型进行判断 dyy 
	{
		strExePath = _T("C:\\Program Files (x86)\\WinRAR\\WinRAR.exe");
		BOOL bExist = ComInterface->ExistDir( strExePath );	
		if ( !bExist )
		{
			strExePath = _T("C:\\Program Files\\WinRAR\\WinRAR.exe");
		}
	}
	else
	{
		strExePath = _T("C:\\Program Files\\WinRAR\\WinRAR.exe");
	}

	BOOL bRarExist = ComInterface->ExistDir( strExePath );	
	if ( !bRarExist )
	{
		PrtMsg( "\n未安装解压文件" );
		m_pm->DoCase(_T("caseDownLoadFail"));
		ITPadCommonOp::SetControlText(_T("未安装解压文件，请先安装WinRAR后进行升级"),m_pm,_T("LabelTip"));
		return false;
	}

	BOOL bOk = CreateProcess( strExePath, (LPWSTR)(LPCTSTR)str,NULL,NULL,TRUE,CREATE_NO_WINDOW,NULL,NULL,&startInfo,&pidInfo );

	if( !bOk )
	{
		PrtMsg( "\n解压文件失败: %s", str );
		m_pm->DoCase(_T("caseDownLoadFail"));
		ITPadCommonOp::SetControlText(_T("解压文件失败"),m_pm,_T("LabelTip"));
		return false;
	}

	WaitForSingleObject(pidInfo.hProcess,INFINITE);
	CloseHandle(pidInfo.hProcess);
	CloseHandle(pidInfo.hThread);

	Sleep( 200 );

	//重启系统
	//ComInterface->ExitWindowsOS( emReboot );

	m_pm->DoCase(_T("caseDownLoadEnd"));

	return true;
}

bool CTPadUpdateLogic::OnSetCnFtpRsp(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    TTPFtpInfo tTPFtpInfo;
    ComInterface->GetCnFtpInfo(tTPFtpInfo);
    if (tTPFtpInfo.bOpen == FALSE && m_bIsWaitForFtp)
    {
        ITPadCommonOp::SetControlText( _T("连接服务器失败"), m_pm, _T("LabelTip") );
        ITPadCommonOp::EnableControl( true, m_pm, _T("BtnOk") );
        return false;
    }
    if (m_bIsWaitForFtp)
    {
        m_bIsWaitForFtp = false;

        BeginDownload();
    }
    return true;
}