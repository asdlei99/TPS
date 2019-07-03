#include "stdafx.h"
#include "CommonInterface.h"
#include "tpmsginit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void CCommonInterface::CreateSession()
{
	InitTpEvent();

	//创建cnssession
	CTPadLib::CreateSession( &m_pTPadSession );
	if ( NULL == m_pTPadSession )
	{
		return;
	}

	m_pTPadSession->InitEnv( AID_CNC2CNS_APP );
	m_pTPadSession->SetNotifyWnd( GetRecvWnd() ) ;

	m_pTPadSession->TpadGetInterface( &m_pTpadConfCtrl );
	if ( m_pTpadConfCtrl != NULL ) 
	{
		m_pTpadConfCtrl->SetNotifyWnd( GetRecvWnd() );
	}
}



UINT ThreadConnectCns(LPVOID lpParam)
{   
	u16 re = NO_ERROR;
	re = ComInterface->LinkCns();
	if ( re != NO_ERROR )
	{   
		if ( ERR_TPAD_ACTIVE_CONNECT ==  re )
		{
			//SendMessage( ComInterface->GetRecvWnd() ,UI_CNS_CONNECTED, TRUE, NO_ERROR);
			NOTIFY_MSG( UI_CNS_CONNECTED, TRUE, NO_ERROR );
		}
		else
		{
			//SendMessage( ComInterface->GetRecvWnd() ,UI_CNS_CONNECTED, FALSE, ERR_CNC_TCPCONNECT);
			NOTIFY_MSG( UI_CNS_CONNECTED, FALSE, ERR_TPAD_TCPCONNECT );
		}
	}

	return re;
} 


u16 CCommonInterface::Connect( u32 dwIp, u16 nPort, LPCTSTR pStrUserName, LPCTSTR pStrPswd )
{      
	if( NULL == m_pTPadSession )
	{
		return NO_ERROR;
	} 

	m_tLoginInfo.dwIp = dwIp;
	m_tLoginInfo.nPort = nPort;
	sprintf_s( m_tLoginInfo.achName, sizeof(m_tLoginInfo.achName), CT2A(pStrUserName) );
	sprintf_s( m_tLoginInfo.achPswd, sizeof(m_tLoginInfo.achPswd), CT2A(pStrPswd) );

	AfxBeginThread( ThreadConnectCns , NULL );

	return NO_ERROR;
}

u16 CCommonInterface::Connect( LPSTR pcIpv6, u16 nPort, LPCTSTR pStrUserName, LPCTSTR pStrPswd )
{
    if( NULL == m_pTPadSession )
    {
        return ERR_CMS;
    } 

    m_tLoginInfo.emIPver = emIPV6;//IPV6登录

    m_tLoginInfo.tRmtAddr.v6addr.sin6_family = AF_INET6;
    m_tLoginInfo.tRmtAddr.v6addr.sin6_port = htons(nPort);
    //     if ( OspPton(AF_INET6, pcIpv6, &m_tLoginInfo.tRmtAddr.v6addr.sin6_addr) < 0 )
    //     {
    //         return ERR_CMS;  
    //     }  

    OSP_SET_NETADDR_ADDR_STR(&m_tLoginInfo.tRmtAddr, OSP_NET_FAMILY_INET6, pcIpv6);

    strncpy(m_tLoginInfo.achName, CT2A(pStrUserName), sizeof(m_tLoginInfo.achName));
    strncpy(m_tLoginInfo.achPswd, CT2A(pStrPswd), sizeof(m_tLoginInfo.achPswd));

    //连接cns
    AfxBeginThread( ThreadConnectCns , NULL );

    return NO_ERROR;
}



u16 CCommonInterface::LinkCns()
{
	u16 re = 0;
	if ( m_pTPadSession != NULL )
	{
		s8 achVersion[MAX_DEVICEVER_LEN] = {0};
		GetTPadVersion( achVersion );
        if (m_tLoginInfo.emIPver == emIPV6)
        {
            re = m_pTPadSession->ConnectCns( m_tLoginInfo.tRmtAddr,
                m_tLoginInfo.achName, m_tLoginInfo.achPswd, achVersion );
        }
        else
        {
		    re = m_pTPadSession->ConnectCns( m_tLoginInfo.dwIp,  m_tLoginInfo.nPort,
			    m_tLoginInfo.achName, m_tLoginInfo.achPswd, achVersion );
        }
	}
	return re;
}

void CCommonInterface::ReConnectCns()
{
    if ( IsConnectCns() )
    {
        return;
    }

    AfxBeginThread( ThreadConnectCns , NULL );
}

u16 CCommonInterface::DisConnect()
{
	if ( NULL == m_pTPadSession ) 
	{
		return FALSE;
	}

	m_tItemInfo.SetNull();
	u16 wRe = m_pTPadSession->DisconnectCns();

	return wRe;
}

BOOL CCommonInterface::IsConnectCns()
{
	if ( NULL == m_pTPadSession ) 
	{
		return FALSE;
	}

	return m_pTPadSession->IsConnectedCns() ;
}

BOOL CCommonInterface::IsManagerUser()
{
	CString strUser(m_tLoginInfo.achName);
	if ( strUser.Compare( _T(MANAGER_USER) ) == 0 || strUser.Compare( _T(T300E_TPAD_SUPERUSRNAME) ) == 0 )
	{
		return TRUE;
	}

	return FALSE;
}

u16  CCommonInterface::GetLocalIP( u32 &dwIP )
{ 

	if( NULL == m_pTPadSession )
	{
		return ERR_CMS;
	}

	dwIP  = m_pTPadSession->GetLocalHostIP();
	return NO_ERROR;
}

//请求码流
u16 CCommonInterface::StartDualCodeStream(   const TTPCnMediaTransPort  &tVedioTransAddr, const TTPCnMediaTransPort  &tAudioTransAddr  ) const  
{
	if( NULL == m_pTpadConfCtrl )
	{
		return ERR_CMS;
	}  

	u16 wRe = m_pTpadConfCtrl->StartDualCodeStream( tVedioTransAddr , tAudioTransAddr);

	return wRe;
}

u16 CCommonInterface::StopDualCodeStream() const
{
	if( NULL == m_pTpadConfCtrl )
	{
		return ERR_CMS;
	}  


	u16 wRe = m_pTpadConfCtrl->StopDualCodeStream( );

	return wRe;
}

u16 CCommonInterface::ReqKeyFrame( BOOL32 bForce ) const
{
	if( NULL == m_pTpadConfCtrl )
	{
		return ERR_CMS;
	}  


	u16 wRe = m_pTpadConfCtrl->ReqKeyFrame( bForce );

	return wRe;
}

TTPCnMediaTransPort CCommonInterface::GetVedioTransAddr() const  
{
	TTPCnMediaTransPort tAdddr;
	if( NULL == m_pTpadConfCtrl )
	{
		return  tAdddr;
	} 

	tAdddr = m_pTpadConfCtrl->GetVedioTransAddr( );

	return tAdddr;
}


TTPCnMediaTransPort CCommonInterface::GetAudioTransAddr() const  
{
	TTPCnMediaTransPort tAdddr;
	if( NULL == m_pTpadConfCtrl )
	{
		return  tAdddr;
	} 

	tAdddr = m_pTpadConfCtrl->GetAudioTransAddr( );

	return tAdddr;
}


BOOL32 CCommonInterface::IsInConf( TCMSConf *pConf )
{   
	BOOL32 bIn = FALSE;

	TTPCnsConfStatus status = GetLocalCnsConfState() ;
	if ( status.emState == em_CALL_CONNECTED )
	{
		bIn = TRUE;
	}

	return bIn;
}

/**
* 功能:  获取本地cns会议状态
* @param [out]tConfInfo  本级cns参加的会议信息
* @return 成功返回TRUE,失败返回FALSE
* @remarks 
*/
TTPCnsConfStatus CCommonInterface::GetLocalCnsConfState() const
{  
	TTPCnsConfStatus tConfStatus;
	if ( NULL == m_pTpadConfCtrl )
	{
		return tConfStatus;
	}

	return m_pTpadConfCtrl->GetCnsConfStatus();
}

void CCommonInterface::GetTPadVersion( s8 achVersion[MAX_DEVICEVER_LEN] )
{	
	s8 achMon[16] = {0};
	u32 byDay = 0;
	u32 byMonth = 0;
	u32 wYear = 0;
	s8 achFullDate[24] = {0};

	s8 achDate[32] = {0};
	sprintf(achDate, "%s", __DATE__);

#ifdef WIN32
	sscanf(achDate, "%s %d %d", achMon, &byDay, &wYear );

	if ( 0 == stricmp( achMon, "JAN") )
		byMonth = 1;
	else if ( 0 == stricmp( achMon, "FEB") )
		byMonth = 2;
	else if ( 0 == stricmp( achMon, "MAR") )
		byMonth = 3;
	else if ( 0 == stricmp( achMon, "APR") )
		byMonth = 4;
	else if ( 0 == stricmp( achMon, "MAY") )
		byMonth = 5;
	else if ( 0 == stricmp( achMon, "JUN") )
		byMonth = 6;
	else if ( 0 == stricmp( achMon, "JUL") )
		byMonth = 7;
	else if ( 0 == stricmp( achMon, "AUG") )
		byMonth = 8;
	else if ( 0 == stricmp( achMon, "SEP") )
		byMonth = 9;
	else if ( 0 == stricmp( achMon, "OCT") )
		byMonth = 10;
	else if ( 0 == stricmp( achMon, "NOV") )
		byMonth = 11;
	else if ( 0 == stricmp( achMon, "DEC") )
		byMonth = 12;
	else
		byMonth = 0;

	sprintf( achFullDate, "%04d%02d%02d", wYear, byMonth, byDay );

	_snprintf( achVersion, MAX_DEVICEVER_LEN, "%s.%s", TPAD_VERSION_ID, achFullDate );

#else
	_snprintf( achVersion, MAX_DEVICEVER_LEN, "%s.%s", TPAD_VERSION_ID, achDate );
#endif

	//strncpy( achVersion, TPAD_VERSION_ID, MAX_DEVICEVER_LEN );  
	achVersion[strlen(achVersion) + 1] = '\0';
}

BOOL32 CCommonInterface::IsReadyLogin( vector<TNodeInfo>&vctNodeList )
{
	if ( NULL == m_pTPadSession ) 
	{
		return FALSE;
	}

	return m_pTPadSession->IsReadyLogin( vctNodeList );
}

void CCommonInterface::TPadHomeKeyNty()
{
	if ( NULL != m_pTPadSession ) 
	{
		m_pTPadSession->TPadHomeKeyNty();
	}	
}

void CCommonInterface::OpenCnsManage()
{
    if ( NULL != m_pTPadSession ) 
    {
        m_pTPadSession->OpenCnsManage();
    }
}

void CCommonInterface::OpenCenterCtrl()
{
	if ( NULL != m_pTPadSession ) 
	{
		m_pTPadSession->OpenCenterCtrl();
	}
}

void CCommonInterface::OpenSysConfig()
{
	if ( NULL != m_pTPadSession ) 
	{
		m_pTPadSession->OpenSysConfig();
	}
}

void CCommonInterface::WBConfStateNty( BOOL bIsInWBConf )
{
	if ( NULL != m_pTpadConfCtrl ) 
	{
		m_pTpadConfCtrl->WBConfStateNty( bIsInWBConf );
	}	
}


//白板会议相关
void CCommonInterface::WBConfStartNty( bool bIsSelfStart, bool bIsSuccess  )
{
	if ( NULL != m_pTpadConfCtrl ) 
	{
		m_pTpadConfCtrl->WBConfStartNty(bIsSelfStart, bIsSuccess);
	}	
}

void CCommonInterface::JoinNewConfRsp( BOOL bIsJoinWBConf )
{
    if ( NULL != m_pTpadConfCtrl ) 
    {
        //m_pTpadConfCtrl->NewConfCallRsp(bIsJoinWBConf);
    }	
}

void CCommonInterface::SetDataServerInfoCmd( u32 dwIp )
{
	if ( NULL != m_pTpadConfCtrl ) 
	{
		m_pTpadConfCtrl->SetDataServerInfoCmd(dwIp);
	}	
}

u16 CCommonInterface::GetWBCnsConfStatus(TTPCnsConfStatus &tTPCnsConfStatus)
{
	if( NULL == m_pTpadConfCtrl )
	{
		return ERR_CMS;
	}

	tTPCnsConfStatus  = m_pTpadConfCtrl->GetWBCnsConfStatus();
	return NO_ERROR;
}

u16 CCommonInterface::GetDataConfInfo(TTPDataConfInfo &tTPDataConfInfo)
{
	if( NULL == m_pTpadConfCtrl )
	{
		return ERR_CMS;
	}

	tTPDataConfInfo  = m_pTpadConfCtrl->GetDataConfInfo();
	return NO_ERROR;
}

u16 CCommonInterface::GetWBCnsInfo(TTPCnsInfo &tTPCnsInfo)
{
	if( NULL == m_pTpadConfCtrl )
	{
		return ERR_CMS;
	}

	tTPCnsInfo  = m_pTpadConfCtrl->GetWBCnsInfo();
	return NO_ERROR;
}

void CCommonInterface::NotifyCnsDisconnect( BOOL bActiveExit )
{
	if ( NULL != m_pTPadSession ) 
	{
		m_pTPadSession->NotifyCnsDisconnect( bActiveExit );
	}
}