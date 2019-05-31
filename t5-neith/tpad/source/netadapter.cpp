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
HANDLE	g_hwndNetCheck = NULL;	// ��ȡ�߳����ݵľ��
DWORD	g_dwNetCheckNum = 0;	// ��ȡ�����̱߳��
HANDLE	g_hNetCheckStop = NULL;	// ֹͣ�¼�
DWORD WINAPI NetCheckThreadProc(LPVOID pParam);
//void CALLBACK MyTimerProc(HWND hwnd,UINT uMsg,UINT idEvent,u32 dwTime); 

CRITICAL_SECTION    CNetworkAdapter::m_s_tCriticalSection;
BOOL32              CNetworkAdapter::m_bCheckIP = TRUE;
s32                 CNetworkAdapter::m_nNetWorkCnt = 0;
CString             CNetworkAdapter::m_strCurNetWorkName = _T("");
CIPInfoManager*     CNetworkAdapter::m_pNetWorkAssist = NULL;
CString             CNetworkAdapter::m_cstrCurNetCardName = _T("��������");
CString             CNetworkAdapter::m_strWifiNetCardName = _T("WLAN");

CNetworkAdapter * CNetworkAdapter::m_ptNetParam = NULL;

//////////////////////////////////////////////////////////////////////////
// API ��ʼ��
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
//		��õ�ǰϵͳ�����������б���õ�ǰ��������ip����Ϣ
//		���û���㹻�Ŀռ䣬����ERROR_INSUFFICIENT_BUFFER
//		
//		�ɹ�����bufferʹ�ô�С
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
			    //ֻ������������
			    if ( pNextAd->Type == MIB_IF_TYPE_ETHERNET )
			    {
				    CString strText = _T("");
				    strText =  pNextAd->Description;
                    //��ֹ�ж����������
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
                //ֻ������������
                if ( pNextAd->Type == 71 )
                {
                    CString strText = _T("");
                    strText =  pNextAd->Description;

                    BOOL bFind = FALSE;                   
                    if ( ComInterface->IsSysWin8() )
                    {
                        //��������Wireless�ģ���ֹ�ж����������
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
                //ֻ������������
                if ( pNextAd->Type == MIB_IF_TYPE_ETHERNET )
                {
                    CString strText = _T("");
                    strText =  pNextAd->Description;
                    //��ֹ�ж����������			
                    BOOL bFind = FALSE;                   
                    if ( ComInterface->IsSysWin8() )
                    {
                        //��������Wireless�ģ���ֹ�ж����������
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
		//Ҫ���ж������������Ҫ�ڴ˴����޸�
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


        //ͨ��ע����ѯ�Ƿ���DNS DHCP��  ���DNS��ַΪ�գ���ѯ��ֵ�Ǵ����-xcr
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
                    //DHCP�ر�ʱ��DNS DHCP�϶��ر� -2016.11.30 xcr
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

            //û�в�����ʱ��IP_ADAPTER_INFO�л�ȡ����IP��ַ����˴�ע����л�ȡIP
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
	//��ֹ��vista��û����ֵʱ��ʾ����255.255.255.255
	if ( sStr == _T("") )
	{
		sStr = _T("0.0.0.0");
	}

	return sStr;
}

////////////////////////////////////////////////////////////
//	Desc:
//		����string������������
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

		//��ȡ����MAC��ַ,��ǰipΪ0�����ڶ���ʱ����߻�ȡ����ipʱ��
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
		//MAC ��ַת��
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
		
		//��ȡ����������ȥip��MAC��ַ
		if ( chIP == 0 )
		{
			return TRUE;
		}

		ulLen = 6;
		memset(pulMac, 0xff, sizeof(pulMac));
		hr = SendARP(chIP, 0, pulMac, &ulLen);
		// 
		//ת��MAC��ַ 
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
			//MessageBox( "IP��ͻ" );
			
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

	//��ipʼ�տ�������ȥ��ip��ͻ�ж����߳����ж�
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
			
	//strExut += "�������� static";
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
        //����DHCP
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
	//strExut += "name=�������� source=dhcp";
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

 //����DNS������ʹ��DHCP
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
    //strExut += "name=�������� source=dhcp";
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

//����DNS��ַ
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

 //���ñ���DNS��ַ
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
    //netsh interface ip add dns "�������� " 202.193.160.33  
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

//ɾ��DNS��ַ
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
    //netsh interface ip delete dns "��������" 202.193.160.33  
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

        // ������������������Ϣ���ں���
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
			
			if ( m_pIfRow->dwType   == MIB_IF_TYPE_ETHERNET) //ֻ����ethernet
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
				sprintf(temp,"����:%s �����ַ:%s  ����:%d\n", strTemp, strPhy, m_nNetCnt);
				*/
				//Ŀǰû�и��÷���ȥ���ֵ�ǰ����ʹ�õ�����������������ȥ����
				if ( 0 == m_strCurNetWorkName.CompareNoCase(strTemp)) 
				{
					//��ס���������ݴ�����ȥ�жϵ�ǰ����������״̬
					//��win7���棬����ںܶ����������������ʹ������ȫ���ģ�Ϊ��ʹ��������״̬���ж�
					//����״̬ ������Ҫ�������Ĵ���
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
        CloseHandle( pi.hThread );// �ر��ӽ��̵����߳̾��
        WaitForSingleObject(pi.hProcess,INFINITE);      
        CloseHandle( pi.hProcess );// �ر��ӽ��̾��
    }
    //Sleep(100);//���������IP���˳�Ȼ��5s�������������ȡ��������ӿ����� 2010-12-17
    return bRe;
} 

//////////////////////////////////////////// End Accessor Functions ////////////////////////////////////////////





/* ////////�����������ļ�///////////////////////////////
C:\Documents and Settings\yujinjin>netsh interface help
   ���������е�����:
   ?              - ��ʾ�����б�
   add            - ��������һ��������Ŀ��
   delete         - �ӱ���ɾ��һ��������Ŀ��
   dump           - ��ʾһ�����ýű���
   help           - ��ʾ�����б�
   ip             - ���ĵ� `netsh interface ip' �����ġ�
   ipv6           - ���ĵ� `netsh interface ipv6' �����ġ�
   portproxy      - ���ĵ� `netsh interface portproxy' �����ġ�
   reset          - ��λ��Ϣ��
   set            - ����������Ϣ��
   show           - ��ʾ��Ϣ��
   
���е��������Ŀ���:
 ip ipv6 portproxy

C:\Documents and Settings\yujinjin>netsh interface ip set ?

  ����ָ����Ч:
  
    ���������е�����:
    set address    - ����ָ���Ľӿڵ� IP ��ַ��Ĭ�����ء�
    set dns        - ���� DNS ������ģʽ�͵�ַ��
    set wins       - ���� WINS ������ģʽ�͵�ַ��
 
   C:\Documents and Settings\yujinjin>netsh interface ip set ?
   
     ����ָ����Ч:
     
       ���������е�����:
       set address    - ����ָ���Ľӿڵ� IP ��ַ��Ĭ�����ء�
       set dns        - ���� DNS ������ģʽ�͵�ַ��
       set wins       - ���� WINS ������ģʽ�͵�ַ��
       
         C:\Documents and Settings\yujinjin>netsh interface ip set address ?
         
           �÷�: set address [name=]<string>
           [[source=]dhcp |
           [source=] static [addr=]IP address [mask=]IP subnet mask]
           [[gateway=]<IP address>|none [gwmetric=]integer]
           
            ����:

            ���           ֵ
            name         - �ӿ����ơ�
            source       - ����ֵ֮һ:
            dhcp: ����ָ���ӿڣ������� DHCP ���� IP
            ��ַ��
            static: ����ʹ�ñ��ؾ�̬�������� IP
            ��ַ��

            gateway      - ����ֵ֮һ:
            <IP address>: �����õ� IP ��ַ��ָ��Ĭ��
            ���ء�
            none: ������Ĭ�����ء�
            gwmetric     - Ĭ�����ص�Ծ�����������������Ϊ 'none'����
            ��Ӧ���ô��ֶΡ�
            ֻ���� 'source' Ϊ 'static' ʱ����������ѡ��:

            addr         - ָ���ӿڵ� IP ��ַ��
            mask         - ָ�� IP ��ַ���������롣

            ע��   : ������ IP ��ַ����ģʽ�� DHCP ģʽ��Ϊ static����� static
            ģʽ��Ϊ DHCP���þ�̬ IP ��ַ�ڽӿ������ IP ��ַ�������
            Ĭ�����ء�
            ʾ��   :

            set address name="Local Area Connection" source=dhcp
            set address local static 10.0.0.9 255.0.0.0 10.0.0.1 1



C:\Documents and Settings\yujinjin>netsh interface ip set dns ? 
       

�÷�: set dns [name=]<string> [source=]dhcp|static [addr=]<IP address>|none
[[register=]none|primary|both]

  ����:
  
    ��־           ֵ
    name         - ��������ơ�
    source       - �����ֵ֮һ:
    dhcp: ���� DHCP ��ΪΪĳһ���������� DNS ��������Դ��
    
    ��̬: �������� DNS ��������ԴΪ���ؾ�̬���á�

    addr         - �����ֵ֮һ:
    <IP ��ַ>: DNS ��������һ�� IP��
    none: ��� DNS �������б�
    register     - �����ֵ֮һ:
    none: ���ö�̬ DNS ע�ᡣ
    primary: ֻ���� DNS ��׺��ע�ᡣ
    both: ���� DNS ��׺��ע�ᣬҲ���ض����Ӻ�׺��ע�ᡣ

    ˵��:    ���� DNS ����������Ϊ DHCP ��̬ģʽ��ֻ����Դ�ǡ�static����
    ���ҡ�addr�� ѡ��Ҳ������Ϊ���ض��Ľ������� DNS �������� IP
    ��ַ��һ����̬�б������¡�

    ʾ��:

      set dns name="Local Area Connection" source=dhcp
     set dns "Local Area Connection" static 10.0.0.1 primary  
   

    //���ñ���DNS������
     netsh interface ip add dns "�������� " 202.193.160.33  
*/


