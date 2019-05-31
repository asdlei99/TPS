#include "stdafx.h"
#include "netadapter.h"
//#include "netwinerr.h"
#include "windows.h"
#include "IpCfgLogic.h"
#include "WifiCfgLogic.h"


#define ALLOCATE_FROM_PROCESS_HEAP( bytes )		::HeapAlloc( ::GetProcessHeap(), HEAP_ZERO_MEMORY, bytes )
#define DEALLOCATE_FROM_PROCESS_HEAP( ptr )		if( ptr ) ::HeapFree( ::GetProcessHeap(), 0, ptr )
#define REALLOC_FROM_PROCESS_HEAP( ptr, bytes )	::HeapReAlloc( ::GetProcessHeap(), HEAP_ZERO_MEMORY, ptr, bytes )
#define  EXEFILE    _T("c:\\windows\\system32\\netsh.exe") //"c:\\WINDOWS\\system32\\cmd.exe"
HANDLE	g_hwndNetCheck = NULL;	// 读取线程内容的句柄
DWORD	g_dwNetCheckNum = 0;	// 读取内容线程编号
HANDLE	g_hNetCheckStop = NULL;	// 停止事件
DWORD WINAPI NetCheckThreadProc(LPVOID pParam);
//void CALLBACK MyTimerProc(HWND hwnd,UINT uMsg,UINT idEvent,u32 dwTime); 

CRITICAL_SECTION    CNetworkAdapter::m_s_tCriticalSection;
BOOL32              CNetworkAdapter::m_bCheckIP = TRUE;
s32                 CNetworkAdapter::m_nNetWorkCnt = 0;
CString             CNetworkAdapter::m_strCurNetWorkName = _T("");
CIPInfoManager*     CNetworkAdapter::m_pNetWorkAssist = NULL;
CString             CNetworkAdapter::m_cstrCurNetCardName = _T("本地连接");
CString             CNetworkAdapter::m_strWifiNetCardName = _T("WLAN");

CNetworkAdapter * CNetworkAdapter::m_ptNetParam = NULL;

//////////////////////////////////////////////////////////////////////////
// API 初始化
//////////////////////////////////////////////////////////////////////////
BOOL CNetworkAdapter::InitIPCfgAPI( /*CNetworkAdapter *ptNetParam*/ )
{
	DWORD	dwErr		= 0;
	ULONG	ulNeeded	= 0;
    
    
    EnterCriticalSection( &m_s_tCriticalSection );

    dwErr = EnumNetworkAdapters( CIpCfgLogic::GetSingletonPtr()->m_pNetCfg, 0, &ulNeeded );
	if( dwErr == ERROR_INSUFFICIENT_BUFFER ) 
	{		
        if ( /*ptNetParam*/ CIpCfgLogic::GetSingletonPtr()->m_pNetCfg != NULL )
        {
            delete[] CIpCfgLogic::GetSingletonPtr()->m_pNetCfg;
			CIpCfgLogic::GetSingletonPtr()->m_pNetCfg = NULL;
        }
		CIpCfgLogic::GetSingletonPtr()->m_pNetCfg = new CNetworkAdapter[ ulNeeded / sizeof( CNetworkAdapter ) ];		
		dwErr = EnumNetworkAdapters( CIpCfgLogic::GetSingletonPtr()->m_pNetCfg, ulNeeded, &ulNeeded );		
		if( NULL == CIpCfgLogic::GetSingletonPtr()->m_pNetCfg ) 
		{
            LeaveCriticalSection( &m_s_tCriticalSection );
			return FALSE;
		}		
	}
	else
    {
        LeaveCriticalSection( &m_s_tCriticalSection );
		return FALSE;
    }

    LeaveCriticalSection( &m_s_tCriticalSection );
    //m_ptNetParam = BusinessManagePtr->m_pNetCfg;
	return TRUE;
}


////////////////////////////////////////////////////////////
//	Desc:
//		获得当前系统中适配器的列表，获得当前适配器的ip等信息
//		如果没有足够的空间，返回ERROR_INSUFFICIENT_BUFFER
//		
//		成功返回buffer使用大小
//		
////////////////////////////////////////////////////////////
DWORD CNetworkAdapter::EnumNetworkAdapters( CNetworkAdapter* pAdapters, ULONG ulSzBuf, LPDWORD lpdwOutSzBuf, BOOL bWifi ) 
{	
	IP_ADAPTER_INFO* pAdptInfo	= NULL;
	IP_ADAPTER_INFO* pNextAd	= NULL;	
	ULONG ulLen					= 0;
	int nCnt					= 0;
	DWORD  erradapt;
	
	erradapt = ::GetAdaptersInfo( pAdptInfo, &ulLen );
	if( erradapt == ERROR_BUFFER_OVERFLOW ) 
	{
		pAdptInfo = ( IP_ADAPTER_INFO* )ALLOCATE_FROM_PROCESS_HEAP( ulLen );
		erradapt = ::GetAdaptersInfo( pAdptInfo, &ulLen );		
	}

	pNextAd = pAdptInfo;
    while( NULL != pNextAd ) 
    {
        nCnt++;
        pNextAd = pNextAd->Next;
    }

	*lpdwOutSzBuf = nCnt * sizeof( CNetworkAdapter );
	if( ulSzBuf < *lpdwOutSzBuf ) 
	{		
		DEALLOCATE_FROM_PROCESS_HEAP( pAdptInfo );
		return ERROR_INSUFFICIENT_BUFFER;
	}

	nCnt = 0;

	if( erradapt == ERROR_SUCCESS ) 
	{
		pNextAd = pAdptInfo;

		while( NULL != pNextAd ) 
		{
            if ( !bWifi )
            {
			    //只放入有线网卡
			    if ( pNextAd->Type == MIB_IF_TYPE_ETHERNET )
			    {
				    CString strText = _T("");
				    strText =  pNextAd->Description;
                    //防止有多个有线网卡
                    if ( -1 == strText.Find( _T("Bluetooth") ) )
				    {
					    m_strCurNetWorkName = strText; 
					    pAdapters[ nCnt ].SetupAdapterInfo( pNextAd );	

					    nCnt++;
				    }				
			    }
            }
            else
            {
                //只放入无线网卡
                if ( pNextAd->Type == 71 )
                {
                    CString strText = _T("");
                    strText =  pNextAd->Description;

                    BOOL bFind = FALSE;                   
                    if ( ComInterface->IsSysWin8() )
                    {
                        //描述中有Wireless的，防止有多个无线网卡
                        if ( -1 != strText.Find( _T("Wireless") ) )
				        {
                            bFind = TRUE;
                        }
                    }
                    else
                    {
                        if ( -1 == strText.Find( _T("Adapter") ) )
                        {
                            bFind = TRUE;
                        }
                    }
                    
                    if ( bFind )
				    {
                        m_strCurNetWorkName = strText; 
                        pAdapters[ nCnt ].SetupAdapterInfo( pNextAd );	
                    
                        nCnt++;     
                    }
			    }
            }
			
			pNextAd = pNextAd->Next;			
		}
	}

	m_nNetWorkCnt = nCnt;	
	DEALLOCATE_FROM_PROCESS_HEAP( pAdptInfo );		

	return ERROR_SUCCESS;
}



BOOL CNetworkAdapter::InitWifiIPCfgAPI( /*CNetworkAdapter *ptNetParam*/ )
{
    DWORD	dwErr		= 0;
    ULONG	ulNeeded	= 0;
    
    
    EnterCriticalSection( &m_s_tCriticalSection );

    dwErr = EnumNetworkAdapters( CWifiCfgLogic::GetSingletonPtr()->m_pNetCfg, 0, &ulNeeded, TRUE );
    if( dwErr == ERROR_INSUFFICIENT_BUFFER ) 
    {		
        if (  CWifiCfgLogic::GetSingletonPtr()->m_pNetCfg != NULL )
        {
            delete[] CWifiCfgLogic::GetSingletonPtr()->m_pNetCfg;
            CWifiCfgLogic::GetSingletonPtr()->m_pNetCfg;
        }
        CWifiCfgLogic::GetSingletonPtr()->m_pNetCfg = new CNetworkAdapter[ ulNeeded / sizeof( CNetworkAdapter ) ];		
        dwErr = EnumNetworkAdapters( CWifiCfgLogic::GetSingletonPtr()->m_pNetCfg, ulNeeded, &ulNeeded, TRUE );		
        if( NULL == CWifiCfgLogic::GetSingletonPtr()->m_pNetCfg ) 
        {
            LeaveCriticalSection( &m_s_tCriticalSection );
            return FALSE;
        }		
    }
    else
    {
        LeaveCriticalSection( &m_s_tCriticalSection );
        return FALSE;
    }
  
    LeaveCriticalSection( &m_s_tCriticalSection );

    return TRUE;
}



BOOL CNetworkAdapter::GetNetAdapterName()
{
    DWORD	dwErr		= 0;
    ULONG	ulNeeded	= 0;
    ULONG ulSzBuf = 0;
    
    EnterCriticalSection( &m_s_tCriticalSection );
    
    IP_ADAPTER_INFO* pAdptInfo	= NULL;
    IP_ADAPTER_INFO* pNextAd	= NULL;	
    ULONG ulLen					= 0;
    int nCnt					= 0;
    DWORD  erradapt;
    
    erradapt = ::GetAdaptersInfo( pAdptInfo, &ulLen );
    if( erradapt == ERROR_BUFFER_OVERFLOW ) 
    {
        pAdptInfo = ( IP_ADAPTER_INFO* )ALLOCATE_FROM_PROCESS_HEAP( ulLen );
        erradapt = ::GetAdaptersInfo( pAdptInfo, &ulLen );		
    }
    
    pNextAd = pAdptInfo;
    while( NULL != pNextAd ) 
    {
        nCnt++;
        pNextAd = pNextAd->Next;
    }
    
    ulNeeded = nCnt * sizeof( CNetworkAdapter );
    //if( ulSzBuf < ulNeeded ) 
    //{		
    //    DEALLOCATE_FROM_PROCESS_HEAP( pAdptInfo );
    //    return ERROR_INSUFFICIENT_BUFFER;
    //}
    
    nCnt = 0;
    
    if( erradapt == ERROR_SUCCESS ) 
    {
        pNextAd = pAdptInfo;
        
        while( NULL != pNextAd ) 
        {
            {
                //只放入有线网卡
                if ( pNextAd->Type == MIB_IF_TYPE_ETHERNET )
                {
                    CString strText = _T("");
                    strText =  pNextAd->Description;
                    //防止有多个有线网卡			
                    BOOL bFind = FALSE;                   
                    if ( ComInterface->IsSysWin8() )
                    {
                        //描述中有Wireless的，防止有多个无线网卡
                        if ( -1 == strText.Find( _T("Bluetooth") ) )
                        {
                            bFind = TRUE;
                        }
                    }
                    else
                    {
                        if ( -1 == strText.Find( _T("Adapter") ) )
                        {
                            bFind = TRUE;
                        }
                    }
                    if ( bFind )
                    {
                        m_strCurNetWorkName = strText; 
                        //pAdapters[ nCnt ].SetupAdapterInfo( pNextAd );	
                        //m_cstrCurNetCardName = pNextAd->AdapterName;
                        m_cstrCurNetCardName.Format( _T("%d"), pNextAd->Index );
                        OspPrintf( 1, 0, "=======NetWorkName:%s, Index:%d\n", (CT2A)m_strCurNetWorkName, pNextAd->Index );
                        nCnt++;   
                    }
                }
            }
            
            pNextAd = pNextAd->Next;			
        }
    }
    
    //m_nNetWorkCnt = nCnt;	
    DEALLOCATE_FROM_PROCESS_HEAP( pAdptInfo );	
    
    LeaveCriticalSection( &m_s_tCriticalSection );
    //m_ptNetParam = BusinessManagePtr->m_pNetCfg;
    return TRUE;
}


////////////////////////////////////////////////////////////
//	Construction.  
//		
////////////////////////////////////////////////////////////
CNetworkAdapter::CNetworkAdapter() 
{
	m_bDhcpUsed		= FALSE;
	m_bWinsUsed		= FALSE;
    m_bDnsDhcpUsed  = FALSE;
	m_dwIndex		= 0;
	m_nAdapterType	= 0;
	m_dwIP          = 0;

	m_nIndexNet     = -1;

	::memset( &m_ucAddress.ucAddress, 0, MAX_ADAPTER_ADDRESS_LENGTH );
	m_ucAddress.nLen = 0;
	
	m_pIfTable = NULL;
	m_nNetWorkCnt = 0; 
	m_strCurNetWorkName = "";
	m_dwCurIfRowIndex = 0;

	m_DnsAddresses.clear();
	m_IpAddresses.clear();
	m_GatewayList.clear();

    
	return;
}

////////////////////////////////////////////////////////////
//	Desc:
//		Deconstruction.
////////////////////////////////////////////////////////////
CNetworkAdapter::~CNetworkAdapter() 
{
#ifdef _DEBUG
	::memset( &m_ucAddress.ucAddress, 0, MAX_ADAPTER_ADDRESS_LENGTH );
	m_ucAddress.nLen = 0;
	m_bDhcpUsed		= FALSE;
	m_bWinsUsed		= FALSE;
    m_bDnsDhcpUsed  = FALSE;
	m_dwIndex		= 0;
	m_nAdapterType	= 0;
#endif
	
	m_DnsAddresses.clear();
	m_IpAddresses.clear();
	m_GatewayList.clear();

	m_nIndexNet     = -1;

	if ( NULL != m_pIfTable )
	{
		DEALLOCATE_FROM_PROCESS_HEAP(m_pIfTable);
		m_pIfTable = NULL;	
	}

// 	if ( NULL != CNetworkAdapter::m_pNetWorkAssist )
// 	{
// 		delete CNetworkAdapter::m_pNetWorkAssist;
// 		CNetworkAdapter::m_pNetWorkAssist = NULL;
// 	}

	return;
}

////////////////////////////////////////////////////////////
//	Desc:
//
////////////////////////////////////////////////////////////
BOOL CNetworkAdapter::SetupAdapterInfo( IP_ADAPTER_INFO* pAdaptInfo ) 
{
	BOOL bSetupPassed				= FALSE;
	IP_ADDR_STRING* pNext			= NULL;
	IP_PER_ADAPTER_INFO* pPerAdapt	= NULL;
	ULONG ulLen						= 0;
	DWORD  err;

	TIPINFO iphold;
	
	if( pAdaptInfo ) 
	{
		if ( m_nIndexNet >= 0 )
		{
			m_nIndexNet ++;
		}
		
#ifndef _UNICODE 
		m_sName			= pAdaptInfo->AdapterName;		
		m_sDesc			= pAdaptInfo->Description;
#else
		USES_CONVERSION;
		m_sName			= A2W( pAdaptInfo->AdapterName );
		m_sDesc			= A2W( pAdaptInfo->Description );
#endif
		//要是有多个适配器开启要在此处作修改
// 		if ( m_sDesc.c_str() != "Realtek RTL8168/811 Family PCI-E GBE Ethernet NIC" )
// 		{
// 			return FALSE;
// 		}

		s32 nI = -1;
		nI ++;
		if ( m_nIndexNet < 0 )
		{
			m_nIndexNet = nI;
		}
		

		m_sPriWins		= (CA2T)pAdaptInfo->PrimaryWinsServer.IpAddress.String;
		m_sSecWins		= (CA2T)pAdaptInfo->SecondaryWinsServer.IpAddress.String;
		m_dwIndex		= pAdaptInfo->Index;		
		m_nAdapterType	= pAdaptInfo->Type;	
		m_bDhcpUsed		= pAdaptInfo->DhcpEnabled;
		m_bWinsUsed		= pAdaptInfo->HaveWins;	
		m_tLeaseObtained= pAdaptInfo->LeaseObtained;
		m_tLeaseExpires	= pAdaptInfo->LeaseExpires;
		m_sDhcpAddr		= (CA2T)pAdaptInfo->DhcpServer.IpAddress.String;
		
		if( pAdaptInfo->CurrentIpAddress ) 
		{
			m_sCurIpAddr.sIp		= (CA2T)pAdaptInfo->CurrentIpAddress->IpAddress.String;
			m_sCurIpAddr.sSubnet	= (CA2T)pAdaptInfo->CurrentIpAddress->IpMask.String;
		}
		else
		{
			m_sCurIpAddr.sIp		= _T("0.0.0.0");
			m_sCurIpAddr.sSubnet	= _T("0.0.0.0");
		}

		pNext = &( pAdaptInfo->IpAddressList );
		while( NULL != pNext ) 
		{
			iphold.sIp		= (CA2T)pNext->IpAddress.String;
			iphold.sSubnet	= (CA2T)pNext->IpMask.String;
			m_IpAddresses.push_back( iphold );
			pNext = pNext->Next;
		}

		pNext = &( pAdaptInfo->GatewayList );
		while( NULL != pNext ) 
		{
            tstring strAddr;
            strAddr = (CA2T)pNext->IpAddress.String;
			m_GatewayList.push_back( strAddr );
			pNext = pNext->Next;
		}	
       
		err = ::GetPerAdapterInfo( m_dwIndex, pPerAdapt, &ulLen );
		if( err == ERROR_BUFFER_OVERFLOW ) 
		{
			pPerAdapt = ( IP_PER_ADAPTER_INFO* ) ALLOCATE_FROM_PROCESS_HEAP( ulLen );
			err = ::GetPerAdapterInfo( m_dwIndex, pPerAdapt, &ulLen );
			
			if( err == ERROR_SUCCESS ) 
			{
				pNext = &( pPerAdapt->DnsServerList );
				while( NULL != pNext ) 
				{
                    tstring strDnsAddr;
                    strDnsAddr = (CA2T)pNext->IpAddress.String;
					m_DnsAddresses.push_back( strDnsAddr );
					pNext = pNext->Next;
				}				
				bSetupPassed = TRUE;
			}

			DEALLOCATE_FROM_PROCESS_HEAP( pPerAdapt );
		}


        //通过注册表查询是否开启DNS DHCP。  如果DNS地址为空，查询的值是错误的-xcr
        CString strRegPath;
        strRegPath.Format( _T("SYSTEM\\ControlSet001\\Services\\Tcpip\\Parameters\\Interfaces\\%s"), m_sName.c_str() );
        HKEY hKey;
        LONG lRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, strRegPath, REG_OPTION_NON_VOLATILE, KEY_READ, &hKey);
        if (lRes ==  ERROR_SUCCESS)
        {
            char achDNSIp[32] = {0};
            DWORD dwTypeLen  = sizeof(achDNSIp);
            if ( RegQueryValueExA(hKey, ("NameServer"), 0, NULL, (u8*)achDNSIp, &dwTypeLen) == ERROR_SUCCESS )
            {
                if ( !m_bDhcpUsed )
                {
                    //DHCP关闭时，DNS DHCP肯定关闭 -2016.11.30 xcr
                    m_bDnsDhcpUsed = FALSE;
                }
                else
                {
                    if ( strcmp( achDNSIp, "" ) == 0 )
                    {
                        m_bDnsDhcpUsed = TRUE;
                    }
                    else
                    {
                        m_bDnsDhcpUsed = FALSE;
                    }
                }                 
            }

            //没有插网线时，IP_ADAPTER_INFO中获取不到IP地址，因此从注册表中获取IP
            if ( !m_bDhcpUsed && m_IpAddresses[0].sIp == _T("0.0.0.0") && m_IpAddresses[0].sSubnet == _T("0.0.0.0") )
            {
                m_IpAddresses.clear();
                m_GatewayList.clear();

                TIPINFO ipInfo;
                char achIp[32] = {0};
                char achSubMask[32] = {0};
                char achGateway[32] = {0};
                dwTypeLen = sizeof(achIp);
                if ( RegQueryValueExA(hKey, ("IPAddress"), 0, NULL, (u8*)achIp, &dwTypeLen) == ERROR_SUCCESS )
                {
                    ipInfo.sIp = (CA2T)achIp;
                }

                dwTypeLen = sizeof(achSubMask);
                if ( RegQueryValueExA(hKey, ("SubnetMask"), 0, NULL, (u8*)achSubMask, &dwTypeLen) == ERROR_SUCCESS )
                {
                    ipInfo.sSubnet = (CA2T)achSubMask;
                }
                m_IpAddresses.push_back( ipInfo );

                tstring strGateway;
                dwTypeLen = sizeof(achGateway);
                if ( RegQueryValueExA(hKey, ("DefaultGateway"), 0, NULL, (u8*)achGateway, &dwTypeLen) == ERROR_SUCCESS )
                {
                    strGateway = (CA2T)achGateway;
                    m_GatewayList.push_back( strGateway );
                }

                m_DnsAddresses.clear();
                CString strDns;
                strDns.Format( _T("%s"), (CA2T)achDNSIp );

                while( strDns.Find( ',' ) != -1 )
                {
                    int nFind = strDns.Find( ',' );
                    m_DnsAddresses.push_back( (LPCTSTR)strDns.Left( nFind ) );
                    strDns.Delete( 0, nFind + 1 );
                }
                if ( !strDns.IsEmpty() )
                {
                    m_DnsAddresses.push_back( (LPCTSTR)strDns );
                }
            }

            RegCloseKey( hKey );
        }      
            
	}
	
	return bSetupPassed;
}

////////////////////////////////////////////////////////////
//	Desc:
//		Generic function to grab a string from an array.
//		purpose of this function is just to add error 
//		checking.
////////////////////////////////////////////////////////////
tstring	CNetworkAdapter::GetStringFromArray( const StringArray* pPtr, int nIndex ) const 
{
	tstring sStr = _T("");
	if( pPtr && ( ( SIZE_T )nIndex < pPtr->size() ) ) 
	{
		sStr = ( *pPtr )[ nIndex ];
	}
	//防止在vista上没有设值时显示的是255.255.255.255
	if ( sStr == _T("") )
	{
		sStr = _T("0.0.0.0");
	}

	return sStr;
}

////////////////////////////////////////////////////////////
//	Desc:
//		返回string的适配器类型
//		
////////////////////////////////////////////////////////////
tstring CNetworkAdapter::GetAdapterTypeString( UINT nType ) 
{
	tstring sType = _T("");
	switch( nType ) 
	{
		case MIB_IF_TYPE_OTHER:		sType = _T("Other");		break;
		case MIB_IF_TYPE_ETHERNET:	sType = _T("Ethernet");		break; 
		case MIB_IF_TYPE_TOKENRING:	sType = _T("Token Ring");	break; 
		case MIB_IF_TYPE_FDDI:		sType = _T("FDDI");			break; 
		case MIB_IF_TYPE_PPP:		sType = _T("PPP");			break; 
		case MIB_IF_TYPE_LOOPBACK:	sType = _T("Loopback");		break; 
		case MIB_IF_TYPE_SLIP:		sType = _T("SLIP");			break; 	
		default: sType = _T("Invalid Adapter Type");			break;
	};

	return sType;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																									//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

tstring CNetworkAdapter::GetAdapterName()				const {	return m_sName; }
tstring CNetworkAdapter::GetAdapterDescription()		const { return m_sDesc; }
time_t CNetworkAdapter::GetLeaseObtained()				const {	return m_tLeaseObtained; }
time_t CNetworkAdapter::GetLeaseExpired()				const {	return m_tLeaseExpires; }
SIZE_T	CNetworkAdapter::GetNumIpAddrs()				const {	return m_IpAddresses.size(); }
SIZE_T	CNetworkAdapter::GetNumDnsAddrs()				const { return m_DnsAddresses.size(); }
tstring	CNetworkAdapter::GetDnsAddr( int nDns )			const { return GetStringFromArray( &m_DnsAddresses, nDns ); }
tstring CNetworkAdapter::GetCurrentIpAddress()			const { return m_sCurIpAddr.sIp; }
BOOL CNetworkAdapter::IsDhcpUsed()						const { return m_bDhcpUsed; }
BOOL CNetworkAdapter::IsDnsDhcpUsed()                   const { return m_bDnsDhcpUsed; }
tstring	CNetworkAdapter::GetDchpAddr()					const {	return m_sDhcpAddr; }
BOOL CNetworkAdapter::IsWinsUsed()						const { return m_bWinsUsed; }
tstring CNetworkAdapter::GetPrimaryWinsServer()			const { return m_sPriWins; }
tstring CNetworkAdapter::GetSecondaryWinsServer()		const { return m_sSecWins; }
tstring	CNetworkAdapter::GetGatewayAddr( int nGateway ) const { return GetStringFromArray( &m_GatewayList, nGateway ); }
SIZE_T	CNetworkAdapter::GetNumGatewayAddrs()			const { return m_GatewayList.size(); }
u32 CNetworkAdapter::GetAdapterIndex()				const {	return m_dwIndex; }
UINT CNetworkAdapter::GetAdapterType()					const { return m_nAdapterType; }

s32 CNetworkAdapter::GetIndex()
{
	return m_nIndexNet;
}


tstring	CNetworkAdapter::GetIpAddr( int nIp ) 
{	
	tstring sAddr = _T("");
	if( ( SIZE_T )nIp < m_IpAddresses.size() ) 
	{
        sAddr = m_IpAddresses[ nIp ].sIp;
	}

	m_dwIP = inet_addr( (CT2A)sAddr.c_str() );

	return sAddr;
}

tstring CNetworkAdapter::GetSubnetForIpAddr( int nIp ) const 
{ 
	tstring sAddr = _T("");
	if( ( SIZE_T )nIp < m_IpAddresses.size() ) 
	{
        sAddr = m_IpAddresses[ nIp ].sSubnet;
	}
	return sAddr;
}

BOOL CNetworkAdapter::NetIpConflict( DWORD chIP )
{
	try
	{

		HRESULT hr; 
		ULONG  pulMac[6];
		ULONG ulLen; 

		//获取本机MAC地址,当前ip为0出现在断链时候或者获取不了ip时候
		if ( m_dwIP == 0 )
		{
			return FALSE;
		}

		ulLen = 6;
		hr = SendARP(m_dwIP, 0, pulMac, &ulLen);
		
		s8 achIP[16];
		u8 *pIP;
		pIP = (u8*)&m_dwIP;
		sprintf(achIP, "%u.%u.%u.%u", *(pIP+3), *(pIP+2), *(pIP+1), *pIP);
		// 
		//MAC 地址转换
		// 
		size_t i, j; 
		char* szMac = NULL;
		szMac = new char[30]; 
		if ( NULL == szMac )
		{
			return FALSE;
		}
		memset(szMac, 0, 30 );
		PBYTE pbHexMac = (PBYTE) pulMac;
		tstring strMACRem;
		ulLen = 6;
		for( i = 0, j = 0; i < ulLen - 1; ++ i )   
		{ 
			j += sprintf( szMac + j, "%02X: ", pbHexMac[i] );
		} 
		
		sprintf(szMac + j, "%02X ", pbHexMac[i]); 
	//	printf("MAC address %s\n ", szMac);
		m_strMAC = (CA2T)szMac;
		
		//获取网络上设下去ip的MAC地址
		if ( chIP == 0 )
		{
			return TRUE;
		}

		ulLen = 6;
		memset(pulMac, 0xff, sizeof(pulMac));
		hr = SendARP(chIP, 0, pulMac, &ulLen);
		// 
		//转换MAC地址 
		//
		ulLen = 6;
		pbHexMac = (PBYTE) pulMac;
		for( i = 0, j = 0; i < ulLen - 1; ++ i )   
		{ 
			j += sprintf( szMac + j, "%02X: ", pbHexMac[i] );
		} 
		
		sprintf(szMac + j, "%02X ", pbHexMac[i]); 
		strMACRem = (CA2T)szMac;
		
		if( strMACRem != m_strMAC  && strMACRem != _T("FF: FF: FF: FF: FF: FF ") )
		{
			//MessageBox( "IP冲突" );
			
			delete []szMac;
			szMac = NULL;
			
			return TRUE;
		}
		else if ( m_strMAC == _T("CC: CC: CC: CC: CC: CC ") )
		{
			delete []szMac;
			szMac = NULL;
			
			return FALSE;
		}	
		
		delete []szMac;
		szMac = NULL;
	}
	catch ( ... )
	{
		return FALSE;
	}
	return FALSE;
}

EmNetStatus CNetworkAdapter::NetAlive( DWORD dw )
{
	if ( !IsNetworkAlive( &dw ) )
	{
		DWORD dwRst = GetLastError();
		if ( dwRst == ERROR_SUCCESS )
		{
			return emNetDisconnnect;
		}
		else
		{
			return emNetException;
		}
	}
	else
	{
		return emNetOK;
	}
}

EmNetStatus CNetworkAdapter::GetNetWorkState()
{
	if ( m_nNetWorkCnt == 0) 
	{	
		return emNetDisconnnect;
	}

	BOOL32 bRet = GetIfData();

	if ( !bRet )
	{
		return emNetException;
	}

	m_pIfRow = (MIB_IFROW *)&m_pIfTable->table[m_dwCurIfRowIndex];
	
	if (GetIfEntry(m_pIfRow) != NO_ERROR)
	{
		return emNetException;
	}

	DWORD dwOperStatusMy = 0;
	dwOperStatusMy = m_pIfRow->dwOperStatus;
	
	CString strText = _T("");
	switch ( dwOperStatusMy )
	{
	case MIB_IF_OPER_STATUS_NON_OPERATIONAL:
	case MIB_IF_OPER_STATUS_UNREACHABLE:
	case MIB_IF_OPER_STATUS_DISCONNECTED:
	case MIB_IF_OPER_STATUS_CONNECTING:
	case MIB_IF_OPER_STATUS_CONNECTED:
		return emNetDisconnnect;
	case MIB_IF_OPER_STATUS_OPERATIONAL:
		return emNetOK;
	default:
		break;
	}
	
	return emNetOK;
}




BOOL CNetworkAdapter::SetIPToPC( u32 dwIPAddr, u32 dwMaskAddr, u32 dwGateAddr, BOOL bRefreshIPCfg /*= TRUE */, BOOL bWifi )
{
    s8 achIP[16];
	s8 achMask[16];
	s8 achGate[16]; 
	u8 *pIP, *pMask, *pGate;

	pIP = (u8*)&dwIPAddr;
	pMask = (u8*)&dwMaskAddr;
	pGate = (u8*)&dwGateAddr;
   

	sprintf(achIP, "%u.%u.%u.%u", *(pIP+3), *(pIP+2), *(pIP+1), *pIP);
	sprintf(achMask, "%u.%u.%u.%u", *(pMask+3), *(pMask+2), *(pMask+1), *pMask);

	if ( dwGateAddr != 0 )
	{
		sprintf(achGate, "%u.%u.%u.%u", *(pGate+3), *(pGate+2), *(pGate+1), *pGate);
	}
	else
	{
		strcpy( achGate, "none" );
	}	
 
	dwIPAddr = inet_addr( achIP );

	//让ip始终可以设下去，ip冲突判断在线程里判断
 	if ( TRUE == NetIpConflict( dwIPAddr) )
 	{
 		return FALSE;
 	}	

    CString strNetCardName;
    if ( bWifi )
    {
        strNetCardName = m_strWifiNetCardName;
    }
    else
    {
        strNetCardName = m_cstrCurNetCardName;
    }

	CString strExut = _T("netsh interface ip set address name=\"");
			
	//strExut += "本地连接 static";
	strExut += strNetCardName;
	strExut += _T("\" static");
	strExut += _T(" ");
	strExut += achIP;
	strExut += _T(" ");
	strExut += achMask;
	strExut += _T(" ");
	strExut += achGate;
	if ( dwGateAddr != 0 )
	{
		strExut += _T(" ");
		strExut += _T("1");
	}	
	OspPrintf( 1, 0, "\n====setip :%s\n", (CT2A)strExut);
	//WinExec( strExut, SW_HIDE );
    WinExecAndWait( EXEFILE, (LPTSTR)(LPCTSTR)strExut );
    
    if( bRefreshIPCfg )
    {    
        if ( bWifi )
        {
            InitWifiIPCfgAPI();
        }
        else
        {
            InitIPCfgAPI( /*m_ptNetParam*/ );
        }
    }

    return TRUE;
}

BOOL CNetworkAdapter::SetIPToPC( u32 dwIPAddr, u32 dwMaskAddr, u32 dwGateAddr, u32 dwDNSAddr )
{
    SetIPToPC( dwIPAddr, dwMaskAddr, dwGateAddr, FALSE );
		
    SetDnsAddr( dwDNSAddr, FALSE );

	InitIPCfgAPI( /*m_ptNetParam*/ );
	
	return TRUE;
}

BOOL CNetworkAdapter::SetIPToPC( TIpConfig &tEthnet )
{ 
    if ( tEthnet.bIpDhcp )
    {
        //设置DHCP
        SetDHCPToPC( FALSE );
        
        if ( tEthnet.bDnsDhcp )
        {
             SetDnsDhcpToPc( FALSE );
        }
        else
        { 
             SetDnsAddr( tEthnet.dwPriorityCns, FALSE ); 
             SetBackupDnsAddr( tEthnet.dwBkupCns, FALSE );
        } 
        
    }
    else
    {
        SetIPToPC( tEthnet.dwIP, tEthnet.dwSubMask, tEthnet.dwGateWay , FALSE );
        SetDnsAddr( tEthnet.dwPriorityCns, FALSE ); 
        SetBackupDnsAddr( tEthnet.dwBkupCns, FALSE ); 
    } 
    
    InitIPCfgAPI( /*m_ptNetParam*/ );
    
	return TRUE;

}



BOOL CNetworkAdapter::SetDHCPToPC( BOOL bRefreshIPCfg /*= TRUE*/, BOOL bWifi )
{
	m_bDhcpUsed = TRUE;

    CString strNetCardName;
    if ( bWifi )
    {
        strNetCardName = m_strWifiNetCardName;
    }
    else
    {
        strNetCardName = m_cstrCurNetCardName;
    }

	CString strExut = _T("netsh interface ip set address ");
	//strExut += "name=本地连接 source=dhcp";
	strExut += _T("name=\"");
	strExut += strNetCardName;
	strExut += _T("\" source=dhcp");
    OspPrintf( 1, 0, "\n====SetDHCPToPC :%s\n", (CT2A)strExut);
	
	//WinExec( strExut, SW_HIDE );
    WinExecAndWait(EXEFILE, (LPTSTR)(LPCTSTR)strExut);
   
    if( bRefreshIPCfg )
    {      
        if ( bWifi )
        {
            InitWifiIPCfgAPI();
        }
        else
        {
            InitIPCfgAPI( /*m_ptNetParam*/ );
        }
    }

	return TRUE;
}

 //设置DNS服务器使用DHCP
BOOL CNetworkAdapter::SetDnsDhcpToPc( BOOL bRefreshIPCfg /*= TRUE*/, BOOL bWifi )
{
    m_bDnsDhcpUsed = TRUE;

    CString strNetCardName;
    if ( bWifi )
    {
        strNetCardName = m_strWifiNetCardName;
    }
    else
    {
        strNetCardName = m_cstrCurNetCardName;
    }

    CString strExu =  _T("netsh interface ip set dns ");	
    //strExut += "name=本地连接 source=dhcp";
    //set dns name="Local Area Connection" source=dhcp
    strExu += _T("name=\"");
    strExu += strNetCardName;
    strExu += _T("\" source=dhcp");
    OspPrintf( 1, 0, "\n====SetDnsDhcpToPc :%s\n", (CT2A)strExu);
    //WinExec( strExu, SW_HIDE );
    WinExecAndWait( EXEFILE, (LPTSTR)(LPCTSTR)strExu );

    if( bRefreshIPCfg )
    {
        if ( bWifi )
        {
            InitWifiIPCfgAPI();
        }
        else
        {
            InitIPCfgAPI( /*m_ptNetParam*/ );
        }
    }
 
    return TRUE;
} 

//设置DNS地址
BOOL CNetworkAdapter::SetDnsAddr( u32 dwDNSAddr, BOOL bRefreshIPCfg /*= TRUE*/, BOOL bWifi /*= FALSE*/ )
{   
    CString strNetCardName;
    if ( bWifi )
    {
        strNetCardName = m_strWifiNetCardName;
    }
    else
    {
        strNetCardName = m_cstrCurNetCardName;
    }

    s8 achDNSAddr[16];
    u8  *pDNS; 
    pDNS = (u8*)&dwDNSAddr;
    sprintf(achDNSAddr, "%u.%u.%u.%u", *(pDNS+3), *(pDNS+2), *(pDNS+1), *pDNS);
    
    CString strDNS = _T("");
    strDNS.Format( _T("netsh interface ip set dns name=\"%s\" source=static addr="), strNetCardName );
    if ( dwDNSAddr == 0 )
    {
    }
    else
    {
        strDNS += achDNSAddr;
        strDNS += _T(" primary ");
    }
    //OspPrintf( 1, 0, "\n====SetDnsAddr :%s\n", strDNS);
    // WinExec( strDNS, SW_HIDE );
    WinExecAndWait(EXEFILE, (LPTSTR)(LPCTSTR)strDNS);
    if( bRefreshIPCfg )
    {
        if ( bWifi )
        {
            InitWifiIPCfgAPI();
        }
        else
        {
            InitIPCfgAPI( /*m_ptNetParam*/ );
        }
    }
 
    return TRUE;
}

 //设置备用DNS地址
BOOL CNetworkAdapter::SetBackupDnsAddr( u32 dwDNSAddr, BOOL bRefreshIPCfg /*= TRUE */, BOOL bWifi /*= FALSE*/ )
{
    CString strNetCardName;
    if ( bWifi )
    {
        strNetCardName = m_strWifiNetCardName;
    }
    else
    {
        strNetCardName = m_cstrCurNetCardName;
    }

    s8 achDNSAddr[16];
    u8  *pDNS; 
    pDNS = (u8*)&dwDNSAddr;
    sprintf(achDNSAddr, "%u.%u.%u.%u", *(pDNS+3), *(pDNS+2), *(pDNS+1), *pDNS);
    
    CString strDNS = _T("");
    //netsh interface ip add dns "本地连接 " 202.193.160.33  
    strDNS.Format(_T("netsh interface ip add dns name=\"%s\" "), strNetCardName );
    if ( dwDNSAddr == 0 )
    {
    }
    else
    {
        strDNS += achDNSAddr;
        strDNS += _T("  index=2 ");
    }

    //OspPrintf( 1, 0, "\n====SetBackupDnsAddr :%s\n", strDNS);
    
    //WinExec( strDNS, SW_HIDE );
    WinExecAndWait(EXEFILE, (LPTSTR)(LPCTSTR)strDNS);
   
    if( bRefreshIPCfg )
    {
        if ( bWifi )
        {
            InitWifiIPCfgAPI();
        }
        else
        {
            InitIPCfgAPI( /*m_ptNetParam*/ );
        }
    }

    return TRUE;
 
} 

//删除DNS地址
BOOL CNetworkAdapter::DeleteDnsAddr( u32 dwDNSAddr, BOOL bWifi /* = FALSE */ )
{
    CString strNetCardName;
    if ( bWifi )
    {
        strNetCardName = m_strWifiNetCardName;
    }
    else
    {
        strNetCardName = m_cstrCurNetCardName;
    }
    
    s8 achDNSAddr[16];
    u8  *pDNS; 
    pDNS = (u8*)&dwDNSAddr;
    sprintf(achDNSAddr, "%u.%u.%u.%u", *(pDNS+3), *(pDNS+2), *(pDNS+1), *pDNS);
    
    CString strDNS = _T("");
    //netsh interface ip delete dns "本地连接" 202.193.160.33  
    strDNS.Format( _T("netsh interface ip delete dns name=\"%s\" "), strNetCardName );
    if ( dwDNSAddr == 0 )
    {
    }
    else
    {
        strDNS += achDNSAddr;
    }
    
    //OspPrintf( 1, 0, "\n====SetBackupDnsAddr :%s\n", strDNS);
    
    WinExecAndWait(EXEFILE, (LPTSTR)(LPCTSTR)strDNS);
       
    return TRUE;
}


void CNetworkAdapter::StartCheckNet( )
{
	g_hwndNetCheck = CreateThread( NULL,
		                           0,
								   NetCheckThreadProc,
								   0,
								   0,
								   &g_dwNetCheckNum );

	if ( g_hwndNetCheck == NULL )
	{
		CloseHandle(g_hNetCheckStop);
		g_hNetCheckStop = NULL;
		return;
	}
}

DWORD WINAPI NetCheckThreadProc(LPVOID pParam)
{
//WND hWnd = reinterpret_cast<HWND>(pParam);

	while(true)
	{
        u32 dwMsgId = 0;
        WPARAM wParam = 0;
        LPARAM lParam = 0;

        EnterCriticalSection( &CNetworkAdapter::m_s_tCriticalSection );

        if ( NULL !=  CNetworkAdapter::GetIpCfg() && TRUE == CNetworkAdapter::m_bCheckIP )
        {
            u32 dwTempip = inet_addr( (CT2A)CNetworkAdapter::GetIpCfg()->GetIpAddr(0).c_str());
			
			//EmNetStatus emNetStatus = theApp.m_pNetParam->NetAlive(dwTempip);
			EmNetStatus emNetStatus = CNetworkAdapter::GetIpCfg()->GetNetWorkState();

			switch ( emNetStatus )
			{
			case emNetOK:
				{
					if ( TRUE == CNetworkAdapter::GetIpCfg()->NetIpConflict( dwTempip ) && FALSE == CNetworkAdapter::GetIpCfg()->IsDhcpUsed() )
					{
						dwMsgId = WM_NET_IPCONFLICT;
						wParam = 0;
						lParam = 0;
					}
					else
					{
						dwMsgId = WM_NET_IPCONFLICT;
						wParam = 1;
						lParam = 0;
					}
				}
				break;
			case emNetDisconnnect:
				{
					dwMsgId = WM_NET_DISCONNECT;
					wParam = emNetDisconnnect;
					lParam = 0;
				}
				break;
			case emNetException:
				{
					dwMsgId = WM_NET_DISCONNECT;
					wParam = emNetException;
					lParam = 0;
				}
				break;
			default:
				{
					dwMsgId = WM_NET_DISCONNECT;
					wParam = emNetDisconnnect;
					lParam = 0;
				}
				break;
			}
        }

        LeaveCriticalSection( &CNetworkAdapter::m_s_tCriticalSection );

        // 避免死锁，将发送消息放在后面
        if ( dwMsgId != 0 )
        {
            //CMsgDispatch::SendMessage( dwMsgId, wParam, lParam );
            NOTIFY_MSG( dwMsgId, wParam, lParam );
        }

		Sleep( 500 );
	}

	return 0;
}

BOOL CNetworkAdapter::GetIfData()
{	
	DWORD dwSize = 0;
	
	if ( NULL == m_pIfTable ) 
	{
		m_pIfTable = (MIB_IFTABLE *)ALLOCATE_FROM_PROCESS_HEAP(sizeof (MIB_IFTABLE));
		
		if ( NULL == m_pIfTable)
		{
			return FALSE;
		}
	}
	
	dwSize = sizeof (MIB_IFTABLE);
	
	if ( GetIfTable( m_pIfTable, &dwSize, FALSE ) == ERROR_INSUFFICIENT_BUFFER ) 
	{
		DEALLOCATE_FROM_PROCESS_HEAP(m_pIfTable);
		m_pIfTable = NULL;		

		if ( NULL == m_pIfTable ) 
		{
			m_pIfTable = (MIB_IFTABLE *) ALLOCATE_FROM_PROCESS_HEAP( dwSize );

			if ( NULL == m_pIfTable)
			{
				return FALSE;
			}
		}
	}
	
    char temp[256]={0};
	
	if ( GetIfTable(m_pIfTable, &dwSize, FALSE) == NO_ERROR ) 
	{
		for (int i = 0; i < (int) m_pIfTable->dwNumEntries; i++) 
		{
			m_pIfRow = (MIB_IFROW *) & m_pIfTable->table[i];
			
			if ( m_pIfRow->dwType   == MIB_IF_TYPE_ETHERNET) //只处理ethernet
			{	
				CString strTemp;
                strTemp.Format( _T("%s"), (CA2T)(char*)m_pIfRow->bDescr );

				/*
				DWORD	dwPhysAddrLen = 0;
				dwPhysAddrLen = m_pIfRow->dwPhysAddrLen;
				CString strPhy = "";
				CString strPhyText = "";
				CString strTemp = m_pIfRow->bDescr;
				if( dwPhysAddrLen > 0 )
				{
					for(DWORD wIndex=0; wIndex < dwPhysAddrLen-1; ++wIndex)
					{
						strPhyText.Format("%02X-" , m_pIfRow->bPhysAddr[wIndex]);
						strPhy += strPhyText;
					}
					strPhyText.Format("%02X" , m_pIfRow->bPhysAddr[wIndex]);
					strPhy += strPhyText;
				}
				sprintf(temp,"名称:%s 物理地址:%s  数量:%d\n", strTemp, strPhy, m_nNetCnt);
				*/
				//目前没有更好方法去区分当前正在使用的网卡，所以用名称去区别
				if ( 0 == m_strCurNetWorkName.CompareNoCase(strTemp)) 
				{
					//记住索引，根据此索引去判断当前网卡的网络状态
					//在win7上面，会存在很多个网络适配器，即使禁用了全部的，为了使用适配器状态来判断
					//网络状态 所以需要做这样的处理
					m_dwCurIfRowIndex = i; 
				}
			}
		}
		
	}
	return TRUE;
}


void CNetworkAdapter::CreateCurNetCardName()
{
 
	if ( NULL == CNetworkAdapter::m_pNetWorkAssist )
	{
		CNetworkAdapter::m_pNetWorkAssist = new CIPInfoManager();
	}
    
    m_cstrCurNetCardName = CNetworkAdapter::m_pNetWorkAssist->GetCurNetWorkName( m_strWifiNetCardName );
	//OspPrintf( 1, 0, "=======netcard:%s\n",m_cstrCurNetCardName ) ;
}

BOOL CNetworkAdapter::WinExecAndWait(LPCTSTR lpExeName, LPTSTR lpCmdLine)
{  
    BOOL bRe = FALSE;
    PROCESS_INFORMATION pi;
    
    STARTUPINFO si;
    
    memset(&si,0,sizeof(si));
    
    si.cb=sizeof(si);
    
    si.wShowWindow=SW_HIDE;
    
    si.dwFlags=STARTF_USESHOWWINDOW;	
    
    bRe = CreateProcess( lpExeName, lpCmdLine,NULL, FALSE,NULL,NULL,NULL,NULL,&si,&pi);
    
    if ( bRe )
    {
        CloseHandle( pi.hThread );// 关闭子进程的主线程句柄
        WaitForSingleObject(pi.hProcess,INFINITE);      
        CloseHandle( pi.hProcess );// 关闭子进程句柄
    }
    //Sleep(100);//解决：设置IP后退出然后5s内再启动软件获取不到网络接口问题 2010-12-17
    return bRe;
} 

//////////////////////////////////////////// End Accessor Functions ////////////////////////////////////////////





/* ////////相关命令帮助文件///////////////////////////////
C:\Documents and Settings\yujinjin>netsh interface help
   此上下文中的命令:
   ?              - 显示命令列表。
   add            - 向表中添加一个配置项目。
   delete         - 从表中删除一个配置项目。
   dump           - 显示一个配置脚本。
   help           - 显示命令列表。
   ip             - 更改到 `netsh interface ip' 上下文。
   ipv6           - 更改到 `netsh interface ipv6' 上下文。
   portproxy      - 更改到 `netsh interface portproxy' 上下文。
   reset          - 复位信息。
   set            - 设置配置信息。
   show           - 显示信息。
   
下列的子上下文可用:
 ip ipv6 portproxy

C:\Documents and Settings\yujinjin>netsh interface ip set ?

  下列指令有效:
  
    此上下文中的命令:
    set address    - 设置指定的接口的 IP 地址或默认网关。
    set dns        - 设置 DNS 服务器模式和地址。
    set wins       - 设置 WINS 服务器模式和地址。
 
   C:\Documents and Settings\yujinjin>netsh interface ip set ?
   
     下列指令有效:
     
       此上下文中的命令:
       set address    - 设置指定的接口的 IP 地址或默认网关。
       set dns        - 设置 DNS 服务器模式和地址。
       set wins       - 设置 WINS 服务器模式和地址。
       
         C:\Documents and Settings\yujinjin>netsh interface ip set address ?
         
           用法: set address [name=]<string>
           [[source=]dhcp |
           [source=] static [addr=]IP address [mask=]IP subnet mask]
           [[gateway=]<IP address>|none [gwmetric=]integer]
           
            参数:

            标记           值
            name         - 接口名称。
            source       - 下列值之一:
            dhcp: 对于指定接口，设置用 DHCP 配置 IP
            地址。
            static: 设置使用本地静态配置设置 IP
            地址。

            gateway      - 下列值之一:
            <IP address>: 您设置的 IP 地址的指定默认
            网关。
            none: 不设置默认网关。
            gwmetric     - 默认网关的跃点数。如果网关设置为 'none'，则
            不应设置此字段。
            只有在 'source' 为 'static' 时才设置下列选项:

            addr         - 指定接口的 IP 地址。
            mask         - 指定 IP 地址的子网掩码。

            注释   : 用来将 IP 地址配置模式从 DHCP 模式改为 static，或从 static
            模式改为 DHCP。用静态 IP 地址在接口上添加 IP 地址，或添加
            默认网关。
            示例   :

            set address name="Local Area Connection" source=dhcp
            set address local static 10.0.0.9 255.0.0.0 10.0.0.1 1



C:\Documents and Settings\yujinjin>netsh interface ip set dns ? 
       

用法: set dns [name=]<string> [source=]dhcp|static [addr=]<IP address>|none
[[register=]none|primary|both]

  参数:
  
    标志           值
    name         - 界面的名称。
    source       - 下面的值之一:
    dhcp: 设置 DHCP 作为为某一个界面配置 DNS 服务器的源。
    
    静态: 设置配置 DNS 服务器的源为本地静态配置。

    addr         - 下面的值之一:
    <IP 地址>: DNS 服务器的一个 IP。
    none: 清除 DNS 服务器列表。
    register     - 下面的值之一:
    none: 禁用动态 DNS 注册。
    primary: 只在主 DNS 后缀下注册。
    both: 在主 DNS 后缀下注册，也在特定连接后缀下注册。

    说明:    设置 DNS 服务器配置为 DHCP 或静态模式。只有在源是“static”，
    并且“addr” 选项也可用以为此特定的界面配置 DNS 服务器的 IP
    地址的一个静态列表的情况下。

    示例:

      set dns name="Local Area Connection" source=dhcp
     set dns "Local Area Connection" static 10.0.0.1 primary  
   

    //设置备用DNS服务器
     netsh interface ip add dns "本地连接 " 202.193.160.33  
*/


