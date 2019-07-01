#include "StdAfx.h"
#include "commoninterface.h"
#include "tpmsginit.h"
#include <io.h>

CCommonInterface* CCommonInterface::m_pMySelf = NULL;

CCommonInterface::CCommonInterface(void) :
					m_pCnsSession(NULL),
					m_pUmsConfCtrl(NULL),
					m_pCnsConfigCtrl(NULL),
					m_pCnsConfCtrl(NULL),
					m_pAddrBookCtrl(NULL),
					m_pCnsUserCtrl(NULL),
// 					m_pSipInfoCtrl(NULL),
// 					m_pNetMngCtrl(NULL),
					m_pPortDiagCtrl(NULL),
					m_tplUserList(),
// 					m_emConnectState( emConnectNotStart ),
// 					m_tCurConfTemplate(),
					m_tConfInfo(),
					m_pCenterCtrlIF(NULL),
                    m_bVidMixOpen(FALSE),
					m_bIsInWBConf(false)
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

}


CCommonInterface::~CCommonInterface(void)
{
	m_pCnsSession = NULL;
	m_pUmsConfCtrl = NULL; 
	m_pCnsConfigCtrl = NULL; 
	m_pCnsConfCtrl = NULL;
	m_pAddrBookCtrl = NULL;
	m_pCnsUserCtrl = NULL;
// 	m_pSipInfoCtrl = NULL;
// 	m_pNetMngCtrl = NULL;
	m_pPortDiagCtrl = NULL;
	m_pCenterCtrlIF = NULL;
	DestroyCommIF();
}


CCommonInterface* CCommonInterface::GetCommIF()
{
	if ( NULL != m_pMySelf )
	{
		return m_pMySelf ;
	}

	m_pMySelf = new CCommonInterface;
	return m_pMySelf;
}

void CCommonInterface::DestroyCommIF()
{   
    m_vctLocalAddrList.clear();
    m_vctGlobalAddrList.clear();

	if ( NULL != m_pMySelf )
	{
		delete m_pMySelf;
		m_pMySelf = NULL;
	}

	DesdroySession();
}



void CCommonInterface::CreateSession()
{
	InitTpEvent();

	//创建cnssession
	CCncLib::CreateSession( &m_pCnsSession );
	if ( NULL == m_pCnsSession )
	{
		return;
	}

	if ( UIDATAMGR->IsPcVersion() )
	{
		m_pCnsSession->InitEnv( AID_CNC2CNS_APP );
	}
	else
	{
		m_pCnsSession->InitEnv( AID_TPAD_CNC, MAKEIID( AID_TPAD_MSGTRANS, 1 ) );
	}	
	m_pCnsSession->SetNotifyWnd( GetRecvWindow() );

	m_pCnsSession->CncGetInterface( &m_pCnsConfigCtrl );
	if ( m_pCnsConfigCtrl != NULL ) 
	{
		m_pCnsConfigCtrl->SetNotifyWnd( GetRecvWindow() );
	}

	m_pCnsSession->CncGetInterface( &m_pCnsConfCtrl );
	if ( m_pCnsConfCtrl != NULL )
	{
		m_pCnsConfCtrl->SetNotifyWnd( GetRecvWindow() );
	}

	m_pCnsSession->CncGetInterface( &m_pUmsConfCtrl ) ;
	if ( m_pCnsConfCtrl != NULL )
	{
		m_pUmsConfCtrl->SetNotifyWnd( GetRecvWindow() );
	}

	m_pCnsSession->CncGetInterface( &m_pAddrBookCtrl );
	if ( m_pAddrBookCtrl != NULL )
	{
		m_pAddrBookCtrl->SetNotifyWnd( GetRecvWindow() );
	}

	m_pCnsSession->CncGetInterface( &m_pCnsUserCtrl );
	if ( m_pCnsUserCtrl != NULL )
	{
		m_pCnsUserCtrl->SetNotifyWnd( GetRecvWindow() );
	}

	m_pCnsSession->CncGetInterface( &m_pPortDiagCtrl );
	if ( m_pPortDiagCtrl != NULL )
	{
		m_pPortDiagCtrl->SetNotifyWnd( GetRecvWindow() );
	}

	m_pCnsSession->CncGetInterface( &m_pCenterCtrlIF );
	if ( m_pCenterCtrlIF != NULL )
	{
		m_pCenterCtrlIF->SetNotifyWnd( GetRecvWindow() );
	}
	m_pCnsSession->CncGetInterface( &m_pCenterCtrl );//添加中控 dyy 2015-4-1
	if ( m_pCenterCtrl != NULL ) 
	{
		m_pCenterCtrl->SetNotifyWnd( GetRecvWindow() );
	}
}


void CCommonInterface::DesdroySession()
{   	
	CCncLib::DestroySession( &m_pCnsSession );
}


UINT ThreadConnectCns(LPVOID lpParam)
{   
	u16 re= NO_ERROR;
	re = ComInterface->LinkCns();

	if ( re != NO_ERROR )
	{   
		if ( ERR_CNC_ACTIVE_CONNECT ==  re )
		{
			//SendMessage( ComInterface->GetRecvWnd() ,UI_CNS_CONNECTED, TRUE, NO_ERROR);
			NOTIFY_MSG( UI_CNS_CONNECTED, TRUE, NO_ERROR );
		}
		else
		{
			//SendMessage( ComInterface->GetRecvWnd() ,UI_CNS_CONNECTED, FALSE, ERR_CNC_TCPCONNECT);
			NOTIFY_MSG( UI_CNS_CONNECTED, FALSE, ERR_CNC_TCPCONNECT );
		}
	}

	return re;
}

u16 CCommonInterface::Connect( u32 dwIp, u16 nPort, LPCTSTR pStrUserName, LPCTSTR pStrPswd )
{   
	if( NULL == m_pCnsSession )
	{
		return ERR_CMS;
	} 

    m_tLoginInfo.emIPver = emIPV4;//IPV4登录

	m_tLoginInfo.dwIp = dwIp;
	m_tLoginInfo.nPort = nPort;
// 	sprintf_s( m_tLoginInfo.achName, sizeof(m_tLoginInfo.achName), CT2A(pStrUserName) );
// 	sprintf_s( m_tLoginInfo.achPswd, sizeof(m_tLoginInfo.achPswd), CT2A(pStrPswd) );

	strncpy(m_tLoginInfo.achName, CT2A(pStrUserName), sizeof(m_tLoginInfo.achName));
	strncpy(m_tLoginInfo.achPswd, CT2A(pStrPswd), sizeof(m_tLoginInfo.achPswd));

	//连接cns
	AfxBeginThread( ThreadConnectCns , NULL );

	return NO_ERROR;
}

u16 CCommonInterface::Connect( LPSTR pcIpv6, u16 nPort, LPCTSTR pStrUserName, LPCTSTR pStrPswd )
{
    if( NULL == m_pCnsSession )
    {
        return ERR_CMS;
    } 

    m_tLoginInfo.emIPver = emIPV6;//IPV6登录

    m_tLoginInfo.tRmtAddr.v6addr.sin6_family = AF_INET6;
    m_tLoginInfo.tRmtAddr.v6addr.sin6_port = nPort;
    if ( OspPton(AF_INET6, pcIpv6, &m_tLoginInfo.tRmtAddr.v6addr.sin6_addr) < 0 )
    {
        return ERR_CMS;  
    }  

    strncpy(m_tLoginInfo.achName, CT2A(pStrUserName), sizeof(m_tLoginInfo.achName));
    strncpy(m_tLoginInfo.achPswd, CT2A(pStrPswd), sizeof(m_tLoginInfo.achPswd));

    //连接cns
    AfxBeginThread( ThreadConnectCns , NULL );

    return NO_ERROR;
}

u16 CCommonInterface::RebootCns()
{
	u16 re = ERR_CMS;
	if (m_pPortDiagCtrl != NULL)
	{
		re = m_pPortDiagCtrl->RebootCns();
	}
	return re;
}

u16 CCommonInterface::LinkCns()
{
	u16 re =  ERR_CMS;
	if ( m_pCnsSession != NULL )
	{
        if (m_tLoginInfo.emIPver == emIPV6)
        {
            re = m_pCnsSession->ConnectCns( m_tLoginInfo.tRmtAddr,
                m_tLoginInfo.achName, m_tLoginInfo.achPswd );
        }
        else
        {
            re = m_pCnsSession->ConnectCns( m_tLoginInfo.dwIp,  m_tLoginInfo.nPort,
                m_tLoginInfo.achName, m_tLoginInfo.achPswd );
        }
	}
	return re;
}


LRESULT CALLBACK CCommonInterface::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if ( uMsg > CMS_MSG_BEGIN ) 
	{
		if ( uMsg == UI_CNS_ADDRBOOK_CHANGED )
		{
			ComInterface->UpdateAddrBook( wParam, lParam );
		}
		else if ( uMsg == UI_CNS_REFRESH_GLOBAL_ADDRBOOK )
		{
			ComInterface->OnRefreshGlobalAddrBook( wParam, lParam );
		}
		else
		{
			NOTIFY_MSG( uMsg, wParam, lParam );
		}	
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



u16 CCommonInterface::UpdateTpadLoginInfo()
{	
	CLoginRequest cUser = m_pCnsSession->GetTpadLoginInfo();
	sprintf_s( m_tLoginInfo.achName, sizeof(m_tLoginInfo.achName),cUser.GetName() );
	sprintf_s( m_tLoginInfo.achPswd, sizeof(m_tLoginInfo.achPswd),cUser.GetPassword() );
	return NO_ERROR;
}

u16 CCommonInterface::GetLoginInfo( TLoginInfo& tLoginInfo )
{
	tLoginInfo = m_tLoginInfo;

	return NO_ERROR;
}

u16 CCommonInterface::SetLoginInfo( TLoginInfo tLoginInfo )
{
	m_tLoginInfo = tLoginInfo;

	return NO_ERROR;
}

u16 CCommonInterface::GetLoginIp( u32 & IP )
{
	if( NULL == m_pCnsSession )
	{
		return ERR_CMS;
	}

	IP  =  m_pCnsSession->GetLoginIp();
	return NO_ERROR;
}

u16 CCommonInterface::GetLocalIP( u32 & dwIP )
{
	if( NULL == m_pCnsSession )
	{
		return ERR_CMS;
	}

	dwIP  =  m_pCnsSession->GetLocalHostIP();
	return NO_ERROR;
}

u16 CCommonInterface::SetCnFtpInfo( TTPFtpInfo tTPFtpInfo )
{
    if( NULL == m_pPortDiagCtrl )
    {
        return ERR_CMS;
    }

    return m_pPortDiagCtrl->SetCnFtpInfo(tTPFtpInfo);
}

u16 CCommonInterface::GetCnFtpInfo( TTPFtpInfo &tTPFtpInfo )
{
	if( NULL == m_pPortDiagCtrl )
	{
		return ERR_CMS;
	}

	tTPFtpInfo = m_pPortDiagCtrl->GetCnFtpInfo();
	return NO_ERROR;
}

u16 CCommonInterface::GetCnTelnetInfo( TTPTelnetInfo &tTPTelnetInfo )
{
	if( NULL == m_pPortDiagCtrl )
	{
		return ERR_CMS;
	}

	tTPTelnetInfo = m_pPortDiagCtrl->GetCnTelnetInfo();
	return NO_ERROR;
}

u16 CCommonInterface::GetEncrytInfo( TTpEncryptKey& tEncryt )
{
	if ( NULL == m_pPortDiagCtrl )
	{
		return ERR_CMS;
	}

	return m_pPortDiagCtrl->GetEncrytInfo(tEncryt);
}

u16 CCommonInterface::EncrytCmd( const TTpEncryptKey& tEncryt )
{
	if ( NULL == m_pPortDiagCtrl )
	{
		return ERR_CMS;
	}

	return m_pPortDiagCtrl->EncrytCmd(tEncryt);;
}

u16 CCommonInterface::DisConnect()
{
	u16 wRe = NO_ERROR;
	BOOL32 bCon = m_pCnsSession->IsConnectedCns() ;
	if ( bCon )
	{
		wRe = m_pCnsSession->DisconnectCns();
	}

	return wRe;
}

void CCommonInterface::ShutDownCmc( BOOL bRestart /*= FALSE */ )
{
	PrtMsg( 0, emEventTypeCmsWindow, "[CCommonInterface::ShutDownCmc]" );
	//UINT uExitCode = 0;
	//ExitProcess( uExitCode );

	//使用ExitProcess在xp中会产生崩溃，改用TerminateProcess

	OspQuit();//释放端口
	TerminateProcess(GetCurrentProcess(), 0);   
}

u16 CCommonInterface::ConnectTPad()
{
	if( NULL == m_pCnsSession )
	{
		return ERR_CMS;
	} 

	u32 dwIp = ntohl( inet_addr( "127.0.0.1" ) );

	TTPadSubInfo tTPadSubInfo;
	tTPadSubInfo.dwIp = dwIp;
	tTPadSubInfo.dwPort = TPAD_LISTEN_PORT;
	tTPadSubInfo.emType = emTPad_cnc;

	u16 re = m_pCnsSession->ConnectTPad( tTPadSubInfo );

	return re;
}

BOOL CCommonInterface::IsManagerUser()
{
	CString strUser(m_tLoginInfo.achName);
	if ( strUser.Compare( _T(MANAGER_USER) ) == 0 )
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CCommonInterface::ExistDir( const CString strDir )
{
	CFileStatus fs;
	return CFile::GetStatus(strDir, fs);
}

BOOL CCommonInterface::CreateDir( CString strDir )
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
			if (_tmkdir(strDir.Left(nPos)) == -1)
				return FALSE;
		}
	}
	return TRUE;
}


//设置系统名
u16 CCommonInterface::changeSysName()
{
	if ( NULL == m_pCnsSession )
	{
		return ERR_CMS;
	}

	u16 re = m_pCnsSession->SetTpadSysName();

	return re;
}

u16 CCommonInterface::NotifyTPadNoReconnect()
{
	if ( NULL == m_pCnsSession )
	{
		return ERR_CMS;
	}

	u16 re = m_pCnsSession->NotifyTPadNoReconnect();

	return re;
}

void CCommonInterface::ShowKeyboard()
{
    if( UIDATAMGR->IsPcVersion() )
    {
        return;
    }
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
	if ( NULL == m_pCnsSession )
	{
		return ERR_CMS;
	}

	tLoginRet = m_pCnsSession->GetLoginRet();

    return TRUE;
}
