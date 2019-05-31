#include "StdAfx.h"
#include "wificfglogic.h"
#include "modalwndlogic.h"
#include "UIDataMgr.h"

template<> CWifiCfgLogic* Singleton<CWifiCfgLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CWifiCfgLogic, CNotifyUIImpl)

    MSG_CREATEWINDOW(_T("NetCfgLayout"), OnCreate)
    MSG_INIWINDOW(_T("NetCfgLayout"), OnInit)

    MSG_SELECTCHANGE(_T("CheckWifiOpen"), OnCheckWifiOpen) 

    MSG_CLICK(_T("BtnRefresh"), OnBtnRefreshWifi)
    MSG_CLICK(_T("btnCfgWifiIp"), OnBtnCfgWifiIp)
    MSG_ITEMCLICK(_T("WifiListItem"), OnClickWifiItem)
    MSG_CLICK(_T("BtnAddWifi"), OnBtnAddWifi)

    MSG_CLICK(_T("BtnConnectWifi"), OnBtnConnectWifi)
    MSG_CLICK(_T("BtnConnectBack"), OnBtnConnectBack)
        
    MSG_CLICK(_T("BtnCancelWifiAdd"), OnBtnCancelWifiAdd)
    MSG_CLICK(_T("BtnSaveWifiAdd"), OnBtnSaveWifiAdd)
    MSG_SELECTCHANGE(_T("CheckSafe"), OnCheckSafe)
      
    MSG_CLICK(_T("BtnCancelWifiIp"), OnBtnCancelWifiIp)
    MSG_CLICK(_T("BtnSaveWifiIp"), OnBtnSaveWifiIp)
    MSG_SELECTCHANGE(_T("WifiCheckAutoIpAddress"), OnWifiCheckAutoIp) 
    MSG_SELECTCHANGE(_T("WifiCheckAutoDNSAddress"), OnWifiCheckAutoDns)

    USER_MSG( WM_WLAN_CONNECT_SUCCED, OnWiFiConnectSuccess )
    USER_MSG( WM_WLAN_CONNECT_FAILED, OnWiFiConnectFailed )
    USER_MSG( WM_WLAN_DISCONT, OnWiFiDisconnect )
	USER_MSG( WM_WLAN_SCAN_RESULT, OnWiFiScanResult )

APP_END_MSG_MAP()


static UINT g_nTmHandleWifiConnect = 0;  //wifi连接超时timer
static UINT g_wWifiReTimerID = 0;     //wifi断网自动重连的timer
static UINT g_nTmShowModal = 0;			//wifi连接超时timer

VOID  CALLBACK  CWifiTimerFun(  HWND   hwnd,   UINT   uMsg, UINT_PTR  idEvent, DWORD   dwTime  )
{  
    if ( idEvent == g_wWifiReTimerID )
    {
        CWifiCfgLogic::GetSingletonPtr()->ReConnectLastWifi();
    }
    else if( idEvent == g_nTmHandleWifiConnect )
    {  
        ::KillTimer( NULL, g_nTmHandleWifiConnect );
        g_nTmHandleWifiConnect = 0;
        CWifiCfgLogic::GetSingletonPtr()->OnWiFiConnectTimeOut();
    }
	else if (idEvent == g_nTmShowModal)
	{
		::KillTimer( NULL, g_nTmShowModal );
		g_nTmShowModal = 0;
		CWifiCfgLogic::GetSingletonPtr()->ShowWifiConnectModalTrue();
	}
}

CWifiCfgLogic::CWifiCfgLogic(void)
{
    m_pNetCfg = NULL;
	m_bIsScanning = FALSE;
    m_bWaitWifi = FALSE;
    m_bWaitReConnect = FALSE;
    memset( m_achConnectName, 0, sizeof(m_achConnectName) );
    memset( m_achLastWifiName, 0, sizeof(m_achLastWifiName) );
}


CWifiCfgLogic::~CWifiCfgLogic(void)
{
    APIWlanQuit();
}

bool CWifiCfgLogic::OnCreate(TNotifyUI& msg)
{
    REG_TPAD_MSG_WND_OB(m_pm->GetPaintWindow());

    //WiFi初始化
    APIWlanInit();
    APIWlanReg(m_pm->GetPaintWindow());

    //获取wifi ip
    ReFreshIpCfg(); 
    UpdateUI( m_tLocalIp );
    return true;
}


bool CWifiCfgLogic::OnInit(TNotifyUI& msg)
{
    if ( APIWlanIsWifiEnable() )
    {
        RefreshWifiList();
        m_pm->DoCase( _T("caseWifiOn") );

        CCheckBoxUI* pCheckWifi = (CCheckBoxUI*)ITPadCommonOp::FindControl(m_pm,_T("CheckWifiOpen"));
        if ( pCheckWifi != NULL  )
        {
            pCheckWifi->SetCheckNoMsg(true);
        }
    }
    else
    {
        m_pm->DoCase( _T("caseWifiOff") );

        CCheckBoxUI* pCheckWifi = (CCheckBoxUI*)ITPadCommonOp::FindControl(m_pm,_T("CheckWifiOpen"));
        if ( pCheckWifi != NULL )
        {
            pCheckWifi->SetCheckNoMsg(false);
        }
    }

    return true;
}


bool CWifiCfgLogic::OnCheckWifiOpen(TNotifyUI& msg)
{
    CCheckBoxUI *pCheckBox = (CCheckBoxUI*)msg.pSender;

    bool bCheck = false;
    if ( pCheckBox != NULL && pCheckBox->GetCheck() )
    {
        bCheck = true;
    }

    if ( bCheck )
    {	
        APIWlanEnableWifi( TRUE );

        if ( APIWlanIsWifiEnable() )
        {
            RefreshWifiList();
            //连接上一次的Wifi
            /*if ( !m_strLastWifiName.IsEmpty() )
            {
                if( APIWlanIsHaveProfile( (LPTSTR)(LPCTSTR)m_strLastWifiName ) )
                {
                    m_bWaitConnect = TRUE;
                    APIWlanDirectConnect( (LPTSTR)(LPCTSTR)m_strLastWifiName );
                }			
            }*/

            m_pm->DoCase( _T("caseWifiOn") );
        }
        else
        {
            m_pm->DoCase( _T("caseWifiOff") );
            pCheckBox->SetCheckNoMsg( false );

            ShowMessageBox( _T("开启Wifi失败，请检查无线网络适配器是否启用") );
        }
    }
    else
    {
        APIWlanEnableWifi( FALSE );

        NOTIFY_MSG( UI_TPAD_REFRESH_WIFI, 0 , 0 );

        m_pm->DoCase( _T("caseWifiOff") );
    }
    return true;
}

void CWifiCfgLogic::RefreshWifiList()
{
    ZeroMemory( &(m_tWlanInfo[0]), sizeof( m_tWlanInfo ) );
    int nTotalItemNum = APIWlanScan( m_tWlanInfo );

    //已连接上的网络排在第一个
    for ( int nIndex = 0; nIndex < nTotalItemNum; nIndex++ )
    {
        if ( m_tWlanInfo[nIndex].m_bConnected )
        {
            strncpy( m_achLastWifiName, m_tWlanInfo[nIndex].m_chrSsid, TP_MAX_ALIAS_LEN_CNC );
            if ( nIndex != 0 )
            {
                TWlanInfo tWlanInfo = m_tWlanInfo[0];
                m_tWlanInfo[0] = m_tWlanInfo[nIndex];
                m_tWlanInfo[nIndex] = tWlanInfo;
            }						
            break;
        }
    }

    m_vctWifiList.clear();
    for ( int i = 0; i < nTotalItemNum; i++ )
    {
        TWifiItem tItem;
        strncpy( tItem.achSSID, m_tWlanInfo[i].m_chrSsid, sizeof(tItem.achSSID) );
        tItem.bEncrypt = m_tWlanInfo[i].m_bEnableSect;
        tItem.nQuality = m_tWlanInfo[i].m_nQuality;
        tItem.nAuthType = m_tWlanInfo[i].m_dotTypeOfAuth;
        tItem.bConnect = m_tWlanInfo[i].m_bConnected;

        if ( strcmp( tItem.achSSID, "" ) != 0 )
        {
            m_vctWifiList.push_back( tItem );
        }		 
    }

    CListUI* pWifiList = (CListUI*)ITPadCommonOp::FindControl( m_pm, _T("WifiList"));
    if ( pWifiList == NULL )
    {
        return;
    }

    int nListHeight = nTotalItemNum * 113 + 20;
    pWifiList->SetFixedHeight( nListHeight );

    pWifiList->RemoveAll();

    for ( u16 i = 0; i < m_vctWifiList.size(); i++ )
    {
        CListContainerElementUI *pListContainer = 
            (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("WifiListItem"));

        TWifiItem tWifiItem; 
        tWifiItem = m_vctWifiList.at(i);
        
        ITPadCommonOp::SetControlText( UIDATAMGR->UTF82Unicode(tWifiItem.achSSID), m_pm, _T("lbWifiName"), pListContainer );

        if ( tWifiItem.bConnect )
        {
             ITPadCommonOp::SetControlTextColor( _T("#CC379FDB"), m_pm, _T("lbWifiName"), pListContainer );
        }

        if ( tWifiItem.bEncrypt )
        {
            ITPadCommonOp::ShowControl( true, m_pm, _T("imgPswLock"), pListContainer );
        }
        else
        {
            ITPadCommonOp::ShowControl( false, m_pm, _T("imgPswLock"), pListContainer );
        }

        int nQuality = tWifiItem.nQuality;
        if ( nQuality < 33 )
        {
            ITPadCommonOp::SetControlBkImg( _T("res\\netcfg\\WifiLittleSignal.png"), m_pm, _T("imgWifiSignal"), pListContainer );			
        }
        else if ( nQuality >= 33 && nQuality <= 66 )
        {
            ITPadCommonOp::SetControlBkImg( _T("res\\netcfg\\WifiHalfSignal.png"), m_pm, _T("imgWifiSignal"), pListContainer );
        }
        else if ( nQuality > 66 )
        {
            ITPadCommonOp::SetControlBkImg( _T("res\\netcfg\\WifiFullSignal.png"), m_pm, _T("imgWifiSignal"), pListContainer );
        }		

        pListContainer->SetTag( (UINT_PTR)&m_vctWifiList.at(i) );
        
        pWifiList->Add(pListContainer);
    }
}


bool CWifiCfgLogic::OnBtnRefreshWifi(TNotifyUI& msg)
{
	if (APIWlanDriverScan())
	{
		m_bIsScanning = TRUE;
		ITPadCommonOp::EnableControl( false, m_pm, _T("BtnRefresh") );
	}

    return true;
}


bool CWifiCfgLogic::OnClickWifiItem(TNotifyUI& msg)
{
    if ( m_bWaitWifi || m_bIsScanning )
    {
        return true;
    }

    if ( const CListContainerElementUI *pItem = dynamic_cast<const CListContainerElementUI*>(msg.pSender) )
    {       
        TWifiItem tWifiItem = *(TWifiItem*)pItem->GetTag();

        if ( tWifiItem.bConnect )
        {
            return true;
        }

        m_tSelItem = tWifiItem;
        //如果系统中已有网络配置文件，则不需要再输入密码
        if ( APIWlanIsHaveProfile( tWifiItem.achSSID ) )
        {
            strncpy( m_achConnectName, tWifiItem.achSSID, sizeof(m_achConnectName) );
            m_bWaitWifi = TRUE;          
            APIWlanDirectConnect( tWifiItem.achSSID );
          
            ShowWifiConnectModal();
        }
        else
        {				
            if ( tWifiItem.bEncrypt )
            {		
                ITPadCommonOp::SetControlText( UIDATAMGR->UTF82Unicode(tWifiItem.achSSID), m_pm, _T("labWifiName") );
                ITPadCommonOp::SetControlText( _T(""), m_pm, _T("edtWifiPsw") );
                ITPadCommonOp::ShowControl( true, m_pm, _T("ConnectWifiLayout") );
            }
            else
            {
                strncpy( m_achConnectName, tWifiItem.achSSID, sizeof(m_achConnectName) );
                m_bWaitWifi = TRUE;               
                APIWlanConnect( tWifiItem.achSSID, NULL );

                ShowWifiConnectModal();
            }
        }
    }
    return true;
}


bool CWifiCfgLogic::OnBtnConnectWifi(TNotifyUI& msg)
{
    if ( m_bWaitWifi )
    {
        return true;
    }

    String strPsw = ITPadCommonOp::GetControlText( m_pm, _T("edtWifiPsw") );

    CString stPswd(strPsw.c_str());
    CString strErr = _T("");
    BOOL32 bOk =  CheckWifiPswd( m_tSelItem.nAuthType, stPswd, strErr );
    if ( !bOk )
    {
        showMessageBox( strErr );
        return false;
    }

    strncpy( m_achConnectName, m_tSelItem.achSSID, sizeof(m_achConnectName) );
    m_bWaitWifi = TRUE;		
    APIWlanConnect( m_tSelItem.achSSID, CT2A(strPsw.c_str()) );

    ITPadCommonOp::ShowControl( false, m_pm, _T("ConnectWifiLayout") );

    ShowWifiConnectModal();

    return true;
}

bool CWifiCfgLogic::OnBtnConnectBack(TNotifyUI& msg)
{
    ITPadCommonOp::ShowControl( false, m_pm, _T("ConnectWifiLayout") );
    return true;
}


bool CWifiCfgLogic::OnBtnAddWifi(TNotifyUI& msg)
{  
    m_pm->DoCase( _T("caseAddWifiSafeOff") );
    ITPadCommonOp::SetControlText( _T(""), m_pm, _T("edtAddWifiName") );
    
    ITPadCommonOp::ShowControl( true, m_pm, _T("AddWifiLayout") );
    ITPadCommonOp::ShowControl( false, m_pm, _T("WifiCfgLayout") );
    
    return true;
}

bool CWifiCfgLogic::OnBtnCancelWifiAdd(TNotifyUI& msg)
{
    ITPadCommonOp::ShowControl( true, m_pm, _T("WifiCfgLayout") );
    ITPadCommonOp::ShowControl( false, m_pm, _T("AddWifiLayout") );
    return true;
}

bool CWifiCfgLogic::OnBtnSaveWifiAdd(TNotifyUI& msg)
{
    String strName = ITPadCommonOp::GetControlText( m_pm, _T("edtAddWifiName") );		
    if ( strName.empty() )
    {
        showMessageBox( _T("网络名称不能为空") );
        return false;
    }

    CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ITPadCommonOp::FindControl(m_pm,_T("CheckSafe"));
    bool bCheckSafe = false;
    if ( pCheckBox != NULL && pCheckBox->GetCheck() )
    {
        bCheckSafe = true;
    }
		
    if ( bCheckSafe )
    {
        String strPsw = ITPadCommonOp::GetControlText( m_pm, _T("edtAddWifiPsw") );

        EM_WifiEncryptMode emEncryptMode;
        if ( ITPadCommonOp::IsOptionSelected( m_pm, _T("opModeNull") ) )
        {
            emEncryptMode = em_Wep_open;
        }
        if ( ITPadCommonOp::IsOptionSelected( m_pm, _T("opModeShare") ) )
        {
            emEncryptMode = em_Wep_share;
        }
        if ( ITPadCommonOp::IsOptionSelected( m_pm, _T("opModeWPA") ) )
        {
            emEncryptMode = em_WPA;
        }
        if ( ITPadCommonOp::IsOptionSelected( m_pm, _T("opModeWPA2") ) )
        {
            emEncryptMode = em_WPA2;
        }

        CString stPswd(strPsw.c_str());
        CString strErr = _T("");
        BOOL32 bOk =  CheckWifiPswd( emEncryptMode, stPswd, strErr );
        if ( !bOk )
        {
            showMessageBox( strErr );
            return false;
        }      

        EM_WifiEncryptType emEncryptType;
        if ( ITPadCommonOp::IsOptionSelected( m_pm, _T("opTypeTkip") ) )
        {
            emEncryptType = em_Cipher_TKIP;
        }
        if ( ITPadCommonOp::IsOptionSelected( m_pm, _T("opTypeAes") ) )
        {
            emEncryptType = em_Cipher_AES;
        }

        if ( emEncryptMode == em_Wep_open || emEncryptMode == em_Wep_share )
        {
            emEncryptType = em_Cipher_WEP;
        }

        strncpy( m_achConnectName, CT2A(strName.c_str()), sizeof(m_achConnectName) );
        m_bWaitWifi = TRUE;
        APIWlanNewConnect( m_achConnectName, emEncryptMode, emEncryptType, CT2A(strPsw.c_str()) );	

        ShowWifiConnectModal();
    }
    else
    {
        strncpy( m_achConnectName, CT2A(strName.c_str()), sizeof(m_achConnectName) );
        m_bWaitWifi = TRUE;
        APIWlanNewConnect( m_achConnectName, em_Wep_open, em_Cipher_None, NULL );

        ShowWifiConnectModal();
    }
    return true;
}

bool CWifiCfgLogic::OnCheckSafe(TNotifyUI& msg)
{
    CCheckBoxUI *pCheckBox = (CCheckBoxUI*)msg.pSender;

    bool bCheck = false;
    if ( pCheckBox != NULL && pCheckBox->GetCheck() )
    {
        bCheck = true;
    }
    if ( bCheck )
    {
        m_pm->DoCase( _T("caseAddWifiSafeOn") );
    }
    else
    {
        m_pm->DoCase( _T("caseAddWifiSafeOff") );
    }
    return true;
}


//根据加密类型 检测wifi的密码是否合法
BOOL32 CWifiCfgLogic::CheckWifiPswd( int nMode, CString strPswd, CString& strErr )
{   
    if ( strPswd.IsEmpty() )
    {
        strErr = _T("网络密钥不能为空");
        return FALSE;
    }
    
    size_t sz = strPswd.GetLength();

    BOOL32 bOk = FALSE;
    switch ( nMode )
    {
    case em_Wep_open://WEP时必须是下列之一：   5个区分大小写的字符                       13个区分大小写的字符
        // 10个十六进制[0-9a-f]不区分大小写的字符    26个十六进制[0-9a-f]不区分大小写的字符
    case em_Wep_share:
        {

            if ( sz == 5 || sz == 13 )
            {
                bOk = TRUE;  
            }
            else if ( sz == 10 || sz == 26 )
            {
                CString strEx = strPswd.SpanExcluding(_T("1234567890abcdefABCDEF"));
                if ( strEx.IsEmpty() )
                {
                    bOk = TRUE;  
                }
            }
            if ( !bOk )
            {
                //strErr = _T("无效的WEP密钥, WEP密钥必须是下列项之一：\n5或13 个区分大小写字符。\n10或26 个十六进制的字符。");
				strErr = _T("网络安全秘钥不正确");
            }

        }
        break;
    case em_WPA:  //WPA时必须是下列之一： 8-63个区分大小写的字符     由数字0-9和字母A-F组成的64个字符
    case em_WPA2:
        { 
            if (  sz >= 8 && sz <= 63 )
            {
                bOk = TRUE;  
            }
            else if ( sz == 64 )
            {
                CString strEx = strPswd.SpanExcluding(_T("1234567890abcdefABCDEF"));
                if ( strEx.IsEmpty() )
                {
                    bOk = TRUE;  
                }
            }
            if ( !bOk )
            {
                //strErr = _T("无效密码, 密码必须是下列项之一：\n8至63 个区分大小写字符。\n64 个使用数字 0-9 和字母 A-F 的字符。");
				//win10 简化密码提示
				strErr = _T("网络安全秘钥不正确");
            }
        }
        break;
    default:
        {
        }
        break;
    }

    if ( !bOk && strErr.IsEmpty())
    {
        strErr = _T("无效密码");
    }
    return bOk;
}

void CWifiCfgLogic::ShowWifiConnectModal()
{
	g_nTmShowModal = SetTimer( NULL, 0, 10, CWifiTimerFun );
}

void CWifiCfgLogic::ShowWifiConnectModalTrue()
{
	g_nTmHandleWifiConnect = SetTimer( NULL, 0, 15000, CWifiTimerFun ); 
	CModalWndLogic::GetSingletonPtr()->ShowModalWnd( _T("正在连接......") );
}


UINT ThreadSetWifiIP(LPVOID lpParam)
{    
    u16 re= NO_ERROR;
    TIpConfig *ipCfg = ( TIpConfig * )lpParam;

    BOOL bOK = FALSE;
    if ( ipCfg != NULL )
    {
        bOK = CWifiCfgLogic::GetSingletonPtr()->SetPc(*ipCfg );    
    }

    if ( bOK )
    {
        CModalWndLogic::GetSingletonPtr()->SetWndText( _T("设置无线网络成功") );

        Sleep( 1000 );
        CModalWndLogic::GetSingletonPtr()->CloseModalWnd();

        //设置完成后刷新UI
        TNotifyUI msg;
        CWifiCfgLogic::GetSingletonPtr()->OnBtnCancelWifiIp( msg );
    }
    else
    {
        Sleep( 1000 );
        CModalWndLogic::GetSingletonPtr()->CloseModalWnd();
        //设置失败，暂时只有IP冲突的原因
        ShowMessageBox( _T("设置无线网络失败：IP地址冲突"), false );	
    }

    return re;
} 



bool CWifiCfgLogic::OnBtnCfgWifiIp(TNotifyUI& msg)
{
    ITPadCommonOp::ShowControl( true, m_pm, _T("WifiIpCfgLayout") );
    ITPadCommonOp::ShowControl( false, m_pm, _T("WifiCfgLayout") );
    return true;
}

bool CWifiCfgLogic::OnBtnCancelWifiIp(TNotifyUI& msg)
{
    ReFreshIpCfg();
    UpdateUI( m_tLocalIp );
    ITPadCommonOp::ShowControl( true, m_pm, _T("WifiCfgLayout") );
    ITPadCommonOp::ShowControl( false, m_pm, _T("WifiIpCfgLayout") );
    return true;
}

bool CWifiCfgLogic::OnBtnSaveWifiIp(TNotifyUI& msg)
{
    TIpConfig  tIpCfg;
    bool bRe = GetIpCfgFrmUI( tIpCfg );

    if ( tIpCfg == m_tLocalIp )
    {
        return true;
    }

    String strCaption;

    //检测IP 
    if ( !tIpCfg.bIpDhcp  )
    {        
        String strIp = ITPadCommonOp::GetControlText( m_pm,_T("edtWifiIP") ); 
        if ( strIp.empty() )
        {  
            ShowMessageBox( _T("IP地址为空，请添加"), false );
            return false;
        }

        if(!CCallAddr::IsValidIpV4(tIpCfg.dwIP) )
        {
            ShowMessageBox((_T("IP地址非法")),false);
            return false;
        }

        //效验子网掩码
        String strSubMask = ITPadCommonOp::GetControlText( m_pm,_T("edtWifiSubnetMask") );
        if ( strSubMask.empty() )
        {  
            ShowMessageBox( _T("子网掩码为空，请添加"), false );
            return false;
        }

        if ( !CCallAddr::IsValidIpMask(tIpCfg.dwSubMask) )
        {  
            ShowMessageBox( _T("子网掩码无效。子网掩码必须是相邻的，请输入有效的掩码"), false );
            return false;
        }

        char achErrStr[256] = {0};
        if ( !CCallAddr::IsValidDevIP( tIpCfg.dwIP, tIpCfg.dwSubMask, achErrStr, 0 ) ) 
        {
            CString str(achErrStr);
            if (str.IsEmpty())
            {
                str = _T("IP地址非法");
            }
            ShowMessageBox(str);
            return false;
        }

        //效验网关
        String strGateWay = ITPadCommonOp::GetControlText( m_pm,_T("edtWifiGateWay") );
        if ( !strGateWay.empty() && !CCallAddr::IsValidCallIP(tIpCfg.dwGateWay) )
        {   
            ShowMessageBox((_T("网关IP地址非法")),false);
            return false;
        } 

        if ( !strGateWay.empty() )
        {
            DWORD dwNetID = tIpCfg.dwIP & tIpCfg.dwSubMask;
            DWORD dwNetGate = tIpCfg.dwGateWay & tIpCfg.dwSubMask;
            if ( dwNetGate != dwNetID )
            {
                ShowMessageBox( _T("网关不在由IP地址和子网掩码定义的同一网络段上"), false);
                return false; 
            }
        }

        //效验DNS地址
        String strPriDns = ITPadCommonOp::GetControlText( m_pm,_T("edtWifiPriorityDNS") );
        if ( !strPriDns.empty() && !CCallAddr::IsValidCallIP(tIpCfg.dwPriorityCns) )
        {
            ShowMessageBox( _T("首选DNS服务器地址非法"), false );
            return false;
        }

        String strBkupDns = ITPadCommonOp::GetControlText( m_pm,_T("edtWifiBkupDNS") );
        if ( !strBkupDns.empty() && !CCallAddr::IsValidCallIP(tIpCfg.dwBkupCns) )
        {
            ShowMessageBox( _T("备用DNS服务器地址非法"), false );
            return false;
        }

        if ( tIpCfg.dwPriorityCns != 0 && tIpCfg.dwPriorityCns == tIpCfg.dwBkupCns )
        {   
            ShowMessageBox( _T("首选DNS服务器和备用DNS服务器地址不可以重复"), false );
            return false; 
        }
    }
    else
    {
        if ( !tIpCfg.bDnsDhcp)
        {
            //效验DNS地址
            String strPriDns = ITPadCommonOp::GetControlText( m_pm,_T("edtWifiPriorityDNS") );
            if ( !strPriDns.empty() && !CCallAddr::IsValidCallIP(tIpCfg.dwPriorityCns) )
            {
                ShowMessageBox( _T("首选DNS服务器地址非法"), false );
                return false;
            }

            String strBkupDns = ITPadCommonOp::GetControlText( m_pm,_T("edtWifiBkupDNS") );
            if ( !strBkupDns.empty() && !CCallAddr::IsValidCallIP(tIpCfg.dwBkupCns) )
            {
                ShowMessageBox( _T("备用DNS服务器地址非法"), false );
                return false;
            }

            //DNS地址不能都为空，否则是否自动获取DNS值有误
            if ( strPriDns.empty() && strBkupDns.empty() )
            {   
                ShowMessageBox( _T("首选DNS和备用DNS服务器地址都为空，请添加"), false );
                return false; 
            }

            if ( tIpCfg.dwPriorityCns != 0 && tIpCfg.dwPriorityCns == tIpCfg.dwBkupCns )
            {   
                ShowMessageBox( _T("首选DNS服务器和备用DNS服务器地址不可以重复"), false );
                return false; 
            }           
        }
    }

    m_tAUiIpCfg = tIpCfg;

    ReFreshIpCfg();
    AfxBeginThread( ThreadSetWifiIP, &m_tAUiIpCfg );

    CModalWndLogic::GetSingletonPtr()->ShowModalWnd( _T("正在设置无线网络，请耐心等待......") );

    return true;
}

bool CWifiCfgLogic::OnWifiCheckAutoIp(TNotifyUI& msg)
{
    CCheckBoxUI *pCheckBox = (CCheckBoxUI*)msg.pSender;

    bool bCheck = false;
    if ( pCheckBox != NULL && pCheckBox->GetCheck() )
    {
        bCheck = true;
    }

    if ( bCheck )
    {
        m_pm->DoCase( _T("caseWifiUseIPDhcp") );
    }
    else
    {
        m_pm->DoCase( _T("caseWifiNotUseIPDhcp") );
    }
    return true;
}

bool CWifiCfgLogic::OnWifiCheckAutoDns(TNotifyUI& msg)
{
    CCheckBoxUI *pCheckBox = (CCheckBoxUI*)msg.pSender;

    bool bCheck = false;
    if ( pCheckBox != NULL && pCheckBox->GetCheck() )
    {
        bCheck = true;
    }

    if ( bCheck )
    {
        m_pm->DoCase( _T("caseWifiUseDnsDhcp") );
    }
    else
    {
        m_pm->DoCase( _T("caseWifiNotUseDnsDhcp") );
    }
    return true;
}


bool CWifiCfgLogic::OnWiFiConnectSuccess(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    //CModalWndLogic::GetSingletonPtr()->SetWndText( _T("设置无线网络成功") );
    //strncpy( m_achLastWifiName, (char*)wParam, sizeof(m_achLastWifiName) );

    if ( m_bWaitWifi )
    {
        m_bWaitWifi = FALSE;

        Sleep(1000);
        CModalWndLogic::GetSingletonPtr()->CloseModalWnd();
    }

    if ( g_nTmHandleWifiConnect != 0 )
    {
        ::KillTimer( NULL, g_nTmHandleWifiConnect );
        g_nTmHandleWifiConnect = 0;
    }

    if ( m_bWaitReConnect )
    {
         if ( g_wWifiReTimerID != 0  )
         {
             ::KillTimer( NULL, g_wWifiReTimerID );
             g_wWifiReTimerID = 0;
         }
         m_bWaitReConnect = FALSE;
         /*if ( m_bReLogin )不在此自动重连，因为可能tpad还没断链
         {
             //2s后自动重连
             if ( g_wReConnectTimerID == 0 )    
             {
                 PrtMsg( ("ConnectSuccess ReConnectTimer\n" ) );
                 g_wReConnectTimerID = SetTimer( NULL, 0, 2000, CWifiTimerFun ); 
             }  
             m_bReLogin = FALSE;
         }*/ 
    }
     
	if (!m_bIsScanning)
	{
		RefreshWifiList();
	}

    return true;
}

bool CWifiCfgLogic::OnWiFiConnectFailed(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    //CModalWndLogic::GetSingletonPtr()->SetWndText( _T("设置无线网络失败") );  
    if ( g_nTmHandleWifiConnect != 0 )
    {
        ::KillTimer( NULL, g_nTmHandleWifiConnect );
        g_nTmHandleWifiConnect = 0;
    }

    if ( m_bWaitWifi )
    {
        m_bWaitWifi = FALSE;
        Sleep(1000);
        CModalWndLogic::GetSingletonPtr()->CloseModalWnd();

        CString strError;
        strError.Format( _T("连接网络:%s 失败"), UIDATAMGR->UTF82Unicode(m_achConnectName) );

        ShowMessageBox( strError );

        APIWlanDeleteProfile( m_achConnectName );
        memset( m_achLastWifiName, 0 , sizeof(m_achLastWifiName) );
    }
    
	if (!m_bIsScanning)
	{
		RefreshWifiList();
	}
   
    return true;
}

bool CWifiCfgLogic::OnWiFiDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    if ( strcmp( m_achLastWifiName, "" ) != 0 )
    {
        m_bWaitReConnect = TRUE;
        //网络掉线重连
        if ( g_wWifiReTimerID == 0 )
        {
            g_wWifiReTimerID = SetTimer( NULL, 0, 5000, CWifiTimerFun ); 
        }      
    }
	if (!m_bIsScanning)
	{
		RefreshWifiList();
	}
    return true;
}

bool CWifiCfgLogic::OnWiFiScanResult(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    if (m_bIsScanning == FALSE)
    {
        return false;
    }
    m_bIsScanning = FALSE;
    ITPadCommonOp::EnableControl( true, m_pm, _T("BtnRefresh") );

    if (0 != (int)wParam)
    {
        RefreshWifiList();
        //刷新主界面wifi图标
        NOTIFY_MSG( UI_TPAD_REFRESH_WIFI, 0 , 0 );
    }
    return true;
}

bool CWifiCfgLogic::OnWiFiConnectTimeOut()
{
    if ( m_bWaitWifi )
    {
        m_bWaitWifi = FALSE;
        Sleep( 1000 );
        CModalWndLogic::GetSingletonPtr()->CloseModalWnd();

        CString strError;
        strError.Format( _T("连接网络 %s 失败:超时"), UIDATAMGR->UTF82Unicode(m_achConnectName) );
        ShowMessageBox( strError );

        APIWlanDeleteProfile( m_achConnectName );
    }
    
	if (!m_bIsScanning)
	{
		RefreshWifiList();
	}
   
    return true;
}

void CWifiCfgLogic::ReConnectLastWifi()
{
    //连接上一次的Wifi
    if ( strcmp( m_achLastWifiName, "" ) != 0 )
    {
        if( APIWlanIsHaveProfile( m_achLastWifiName ) )
        {
            m_bWaitReConnect = TRUE;
            APIWlanDirectConnect( m_achLastWifiName );
        }			
    }
}


void CWifiCfgLogic::ReFreshIpCfg()
{
    CNetworkAdapter *pcAdt = NULL;
    u32 dwIP = 0;
    u32 dwMask = 0;
    u32 dwDns = 0;
    u32 dwGateWay= 0;
    u8 byUseDHCP = 0;

    bool bIs = CNetworkAdapter::InitWifiIPCfgAPI();
    pcAdt = GetIPCfg();
    if ( pcAdt == NULL )
    {
        OspPrintf(TRUE,FALSE," GetIPCfg() == none");
        return ;
    }

    m_tLocalIp.dwIP = inet_addr( (CT2A)pcAdt->GetIpAddr(0).c_str() );
    m_tLocalIp.dwSubMask = inet_addr( (CT2A)pcAdt->GetSubnetForIpAddr(0).c_str() );
    m_tLocalIp.dwGateWay = inet_addr( (CT2A)pcAdt->GetGatewayAddr(DEFAULT_GATEWAY_ADDR).c_str() );
    m_tLocalIp.dwPriorityCns = inet_addr( (CT2A)pcAdt->GetDnsAddr(0).c_str() );
    m_tLocalIp.dwBkupCns = inet_addr( (CT2A)pcAdt->GetDnsAddr(1).c_str() );
    m_tLocalIp.bIpDhcp = pcAdt->IsDhcpUsed();
    m_tLocalIp.bDnsDhcp = pcAdt->IsDnsDhcpUsed();

    //OspPrintf(TRUE,FALSE,"m_tLocalIp.bDnsDhcp:%d",m_tLocalIp.bDnsDhcp);
    //DNS DHCP通过注册表获取，不再通过dwPriorityCns判断 -2012.9.3 xcr
    //m_tLocalIp.bDnsDhcp = TRUE;
    //if ( m_tLocalIp.dwPriorityCns != 0 )
    //{
    //    m_tLocalIp.bDnsDhcp = FALSE;
    //}

    m_tLocalIp.dwIP = ntohl( m_tLocalIp.dwIP );
    m_tLocalIp.dwSubMask = ntohl( m_tLocalIp.dwSubMask ); 
    m_tLocalIp.dwGateWay = ntohl( m_tLocalIp.dwGateWay ); 
    m_tLocalIp.dwPriorityCns = ntohl( m_tLocalIp.dwPriorityCns ); 
    m_tLocalIp.dwBkupCns = ntohl( m_tLocalIp.dwBkupCns ); 

    //防止IP出现255.255
    if ( m_tLocalIp.dwIP == -1 )
    {
        m_tLocalIp.dwIP = 0;
    }
    if ( m_tLocalIp.dwSubMask == -1 )
    {
        m_tLocalIp.dwSubMask = 0;
    }
}


bool CWifiCfgLogic::GetIpCfgFrmUI( TIpConfig& tIpCfg )
{ 
    ZeroMemory(&tIpCfg,sizeof(TIpConfig) );

    CCheckBoxUI *pCheckAutoIp = (CCheckBoxUI*)ITPadCommonOp::FindControl( m_pm, _T("WifiCheckAutoIpAddress") );
    if (pCheckAutoIp!= NULL)
    {
        tIpCfg.bIpDhcp = pCheckAutoIp->GetCheck();
    }   

    CCheckBoxUI *pCheckAutoDNS = (CCheckBoxUI*)ITPadCommonOp::FindControl( m_pm, _T("WifiCheckAutoDNSAddress") );
    if (pCheckAutoDNS!= NULL)
    {
        tIpCfg.bDnsDhcp = pCheckAutoDNS->GetCheck();
    } 

    if ( !tIpCfg.bIpDhcp  )
    {
        String strIp = ITPadCommonOp::GetControlText( m_pm,_T("edtWifiIP") ); 
        String strMask = ITPadCommonOp::GetControlText( m_pm,_T("edtWifiSubnetMask") );
        String strGateWay = ITPadCommonOp::GetControlText( m_pm,_T("edtWifiGateWay") );
        String strPriDns = ITPadCommonOp::GetControlText( m_pm,_T("edtWifiPriorityDNS") );
        String strBkupDns = ITPadCommonOp::GetControlText( m_pm,_T("edtWifiBkupDNS") );

        tIpCfg.dwIP = ntohl(inet_addr(CT2A(strIp.c_str())));
        tIpCfg.dwSubMask = ntohl(inet_addr(CT2A(strMask.c_str())));
        if ( strGateWay.empty() )
        {
            tIpCfg.dwGateWay = 0;
        }
        else
        {
            tIpCfg.dwGateWay = ntohl(inet_addr(CT2A(strGateWay.c_str())));
        }
        if ( strPriDns.empty() )
        {
            tIpCfg.dwPriorityCns = 0;
        }
        else
        {
            tIpCfg.dwPriorityCns = ntohl(inet_addr(CT2A(strPriDns.c_str())));
        }
        if ( strBkupDns.empty() )
        {
            tIpCfg.dwBkupCns = 0;
        }
        else
        {
            tIpCfg.dwBkupCns = ntohl(inet_addr(CT2A(strBkupDns.c_str())));
        }
    } 
    else
    {
        if ( !tIpCfg.bDnsDhcp )
        {
            String strPriDns = ITPadCommonOp::GetControlText( m_pm,_T("edtWifiPriorityDNS") );
            String strBkupDns = ITPadCommonOp::GetControlText( m_pm,_T("edtWifiBkupDNS") );

            if ( strPriDns.empty() )
            {
                tIpCfg.dwPriorityCns = 0;
            }
            else
            {
                tIpCfg.dwPriorityCns = ntohl(inet_addr(CT2A(strPriDns.c_str())));
            }
            if ( strBkupDns.empty() )
            {
                tIpCfg.dwBkupCns = 0;
            }
            else
            {
                tIpCfg.dwBkupCns = ntohl(inet_addr(CT2A(strBkupDns.c_str())));
            }
        }
    }

    return true;
}


//根据UI上的IP来设置PC
BOOL CWifiCfgLogic::SetPc( TIpConfig& tIpCfg )
{  

    bool bNeedSetIp = false ;
    if ( tIpCfg.bIpDhcp != m_tLocalIp.bIpDhcp )
    {   
        bNeedSetIp = true;
    } 
    else if( !tIpCfg.bIpDhcp  )  //如果dhcp状态相同
    {
        if ( tIpCfg.dwIP != m_tLocalIp.dwIP || tIpCfg.dwSubMask != m_tLocalIp.dwSubMask
            || tIpCfg.dwGateWay != m_tLocalIp.dwGateWay )
        {
            bNeedSetIp = true;

        }         
    }

    if ( bNeedSetIp )
    {
        //设置IP
        if ( tIpCfg.bIpDhcp  )
        {
            GetIPCfg()->SetDHCPToPC( TRUE, TRUE );
        }
        else 
        {
            BOOL bOK = GetIPCfg()->SetIPToPC( tIpCfg.dwIP, tIpCfg.dwSubMask, tIpCfg.dwGateWay, TRUE, TRUE );
            if ( !bOK )
            {
                return FALSE;
            }
        }       
    }  

    bool bNeedSetDNS = true ;

    if( tIpCfg.bDnsDhcp  && tIpCfg.bDnsDhcp == m_tLocalIp.bDnsDhcp  ) // 不需要设置dns信息
    {
        bNeedSetDNS = false;
    }

    if ( bNeedSetDNS )
    {
        if ( tIpCfg.bDnsDhcp )
        {
            GetIPCfg()->SetDnsDhcpToPc( TRUE, TRUE );
        }
        else
        {
            if (tIpCfg.dwPriorityCns != m_tLocalIp.dwPriorityCns )
            {
                if ( tIpCfg.dwPriorityCns == 0 )
                {
                    GetIPCfg()->DeleteDnsAddr( m_tLocalIp.dwPriorityCns, TRUE );
                }
                else
                {
                    GetIPCfg()->SetDnsAddr( tIpCfg.dwPriorityCns, FALSE, TRUE );
                }              
            }

            if ( tIpCfg.dwBkupCns != m_tLocalIp.dwBkupCns )
            {
                if ( tIpCfg.dwBkupCns == 0 )
                {
                    GetIPCfg()->DeleteDnsAddr( m_tLocalIp.dwBkupCns, TRUE );
                }
                else
                {
                    GetIPCfg()->SetBackupDnsAddr( tIpCfg.dwBkupCns, FALSE, TRUE );
                }             
            }
        }       
    } 

    return TRUE;
}

//根据pc的IP来设置UI
void CWifiCfgLogic::UpdateUI( TIpConfig& tIpCfg )
{
    bool bUseDchp = tIpCfg.bIpDhcp;
    ITPadCommonOp::OptionSelect( bUseDchp, m_pm, _T("WifiCheckAutoIpAddress") );

    bool bAutoGetDns = tIpCfg.bDnsDhcp; 
    ITPadCommonOp::OptionSelect( bAutoGetDns, m_pm, _T("WifiCheckAutoDNSAddress") );

    in_addr tAddr;
    tAddr.S_un.S_addr = htonl(tIpCfg.dwIP);
    String strIP = CA2T(inet_ntoa(tAddr));
    if ( strIP == _T("0.0.0.0") )
    {
        strIP = _T("");
    }
    ITPadCommonOp::SetControlText(strIP.c_str(),m_pm,_T("edtWifiIP"));

    tAddr.S_un.S_addr = htonl(tIpCfg.dwSubMask);
    String strMaskIP = CA2T(inet_ntoa(tAddr));
    if ( strMaskIP == _T("0.0.0.0") )
    {
        strMaskIP = _T("");
    }
    ITPadCommonOp::SetControlText(strMaskIP.c_str(),m_pm,_T("edtWifiSubnetMask")); 

    tAddr.S_un.S_addr = htonl(tIpCfg.dwGateWay);
    String strGateWayIP = CA2T(inet_ntoa(tAddr));
    if ( strGateWayIP == _T("0.0.0.0") )
    {
        strGateWayIP = _T("");
    }
    ITPadCommonOp::SetControlText(strGateWayIP.c_str(),m_pm,_T("edtWifiGateWay")); 

    tAddr.S_un.S_addr = htonl(tIpCfg.dwPriorityCns);
    String strPriorityCns = CA2T(inet_ntoa(tAddr));
    if ( strPriorityCns == _T("0.0.0.0") )
    {
        strPriorityCns = _T("");
    }
    ITPadCommonOp::SetControlText(strPriorityCns.c_str(),m_pm,_T("edtWifiPriorityDNS")); 

    tAddr.S_un.S_addr = htonl(tIpCfg.dwBkupCns);
    String strBkupCns = CA2T(inet_ntoa(tAddr));
    if ( strBkupCns == _T("0.0.0.0") )
    {
        strBkupCns = _T("");
    }
    ITPadCommonOp::SetControlText(strBkupCns.c_str(),m_pm,_T("edtWifiBkupDNS")); 

    if ( bUseDchp )
    {   
        m_pm->DoCase( _T("caseWifiUseIPDhcp") );
        if ( bAutoGetDns )
        {
            m_pm->DoCase( _T("caseWifiUseDnsDhcp") );           
        }
        else
        {
            m_pm->DoCase( _T("caseWifiNotUseDnsDhcp") ); 
        }
    }
    else
    {  
        m_pm->DoCase( _T("caseWifiNotUseIPDhcp") );
    }
}
