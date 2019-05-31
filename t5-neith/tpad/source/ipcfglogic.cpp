#include "StdAfx.h"
#include "ipcfglogic.h"
#include "modalwndlogic.h"
#include "mainframelogic.h"

template<> CIpCfgLogic* Singleton<CIpCfgLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CIpCfgLogic, CNotifyUIImpl)
    MSG_CREATEWINDOW(_T("NetCfgLayout"), OnCreate)
    MSG_INIWINDOW(_T("NetCfgLayout"), OnInit)

    MSG_CLICK(_T("BtnBack"), OnBtnBack)

    MSG_SELECTCHANGE(_T("wificfg"), OnTabWifiCfg)
    MSG_SELECTCHANGE(_T("ipcfg"), OnTabIpCfg)

    MSG_CLICK(_T("BtnCancelIp"), OnBtnCancelIp)
    MSG_CLICK(_T("BtnSaveIp"), OnBtnSaveIp)
    MSG_SELECTCHANGE(_T("CheckAutoIpAddress"), OnCheckAutoIp) 
    MSG_SELECTCHANGE(_T("CheckAutoDNSAddress"), OnCheckAutoDns)

    USER_MSG(WM_DUI_EDITSETFOCUS, OnEditSetFocus)
    
APP_END_MSG_MAP()


UINT ThreadSetIP(LPVOID lpParam)
{    
    u16 re= NO_ERROR;
    TIpConfig *ipCfg = ( TIpConfig * )lpParam;

    BOOL bOK = FALSE;
    if ( ipCfg != NULL )
    {
        bOK = CIpCfgLogic::GetSingletonPtr()->SetPc(*ipCfg );    

        OspPrintf(TRUE,FALSE,"ThreadSetIP bDnsDhcp :%d",ipCfg->bDnsDhcp);
    }

    if ( bOK )
    {
        CModalWndLogic::GetSingletonPtr()->SetWndText( _T("������������ɹ�") );

        //CIpCfgLogic::GetSingletonPtr()->ReFreshIpCfg();  
        //CIpCfgLogic::GetSingletonPtr()->m_tLocalIp.bDnsDhcp = ipCfg->bDnsDhcp;

        //UIManagePtr->SaveToFile( g_stcStrIpCfgDlg, "", "WindowCaption" ,TRUE );
        //UIManagePtr->SaveToFile( g_stcStrIpCfgDlg, "", "SwitchState"  ,TRUE  ); 

        Sleep( 1000 );

        CModalWndLogic::GetSingletonPtr()->CloseModalWnd();

        //������ɺ�ˢ��UI
        TNotifyUI msg;
        CIpCfgLogic::GetSingletonPtr()->OnBtnCancelIp( msg );
    }
    else
    {
        Sleep( 1000 );
        CModalWndLogic::GetSingletonPtr()->CloseModalWnd();
        //����ʧ�ܣ���ʱֻ��IP��ͻ��ԭ��
        ShowMessageBox( _T("������������ʧ�ܣ�IP��ַ��ͻ"), false );		
    }

    return re;
} 



CIpCfgLogic::CIpCfgLogic(void)
{
    m_pNetCfg = NULL;
}


CIpCfgLogic::~CIpCfgLogic(void)
{
    CNetworkAdapter::DelCriticalSection();
}

bool CIpCfgLogic::OnCreate(TNotifyUI& msg)
{
    CNetworkAdapter::InitCriticalSection();
    CNetworkAdapter::CreateCurNetCardName();

    ReFreshIpCfg(); 

    UpdateUI( m_tLocalIp );

    return true;
}

bool CIpCfgLogic::OnInit(TNotifyUI& msg)
{
    return true;
}

bool CIpCfgLogic::OnBtnBack(TNotifyUI& msg)
{
    CMainFrameLogic::GetSingletonPtr()->ShowLoginPage();
    WINDOW_MGR_PTR->ShowWindow( g_strNetCfgDlg.c_str(), false );
    return true;
}

bool CIpCfgLogic::OnTabWifiCfg(TNotifyUI& msg)
{
    CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ITPadCommonOp::FindControl( m_pm, _T("slidetab") );
    if (pControl)
    {
        pControl->SelectItem(emTabID_WifiCfg);
    }
    return true;
}

bool CIpCfgLogic::OnTabIpCfg(TNotifyUI& msg)
{
    CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ITPadCommonOp::FindControl( m_pm, _T("slidetab") );
    if (pControl)
    {
        pControl->SelectItem(emTabID_IpCfg);
    }
    return true;
}

bool CIpCfgLogic::OnBtnCancelIp(TNotifyUI& msg)
{
    ReFreshIpCfg();
    UpdateUI( m_tLocalIp );
    return true;
}


bool CIpCfgLogic::OnBtnSaveIp(TNotifyUI& msg)
{  
    TIpConfig  tIpCfg;
    bool bRe = GetIpCfgFrmUI( tIpCfg );

    if ( tIpCfg == m_tLocalIp )
    {
        return true;
    }

    String strCaption;

    //���IP 
    if ( !tIpCfg.bIpDhcp  )
    {        
        String strIp = ITPadCommonOp::GetControlText( m_pm,_T("edtIP") ); 
        if ( strIp.empty() )
        {  
            ShowMessageBox( _T("IP��ַΪ�գ������"), false );
            return false;
        }

        if(!CCallAddr::IsValidIpV4(tIpCfg.dwIP) )
        {
            ShowMessageBox((_T("IP��ַ�Ƿ�")),false);
            return false;
        }

        //Ч����������
        String strSubMask = ITPadCommonOp::GetControlText( m_pm,_T("edtSubnetMask") );
        if ( strSubMask.empty() )
        {  
            ShowMessageBox( _T("��������Ϊ�գ������"), false );
            return false;
        }

        if ( !CCallAddr::IsValidIpMask(tIpCfg.dwSubMask) )
        {  
            ShowMessageBox( _T("����������Ч������������������ڵģ���������Ч������"), false );
            return false;
        }

        char achErrStr[256] = {0};
        if ( !CCallAddr::IsValidDevIP( tIpCfg.dwIP, tIpCfg.dwSubMask, achErrStr, 0 ) ) 
        {
            CString str(achErrStr);
            if (str.IsEmpty())
            {
                str = _T("IP��ַ�Ƿ�");
            }
            ShowMessageBox(str);
            return false;
        }

        //Ч������
        String strGateWay = ITPadCommonOp::GetControlText( m_pm,_T("edtGateWay") );
        if ( !strGateWay.empty() && !CCallAddr::IsValidCallIP(tIpCfg.dwGateWay) )
        {   
            ShowMessageBox((_T("����IP��ַ�Ƿ�")),false);
            return false;
        } 

        if ( !strGateWay.empty() )
        {
            DWORD dwNetID = tIpCfg.dwIP & tIpCfg.dwSubMask;
            DWORD dwNetGate = tIpCfg.dwGateWay & tIpCfg.dwSubMask;
            if ( dwNetGate != dwNetID )
            {
                ShowMessageBox( _T("���ز�����IP��ַ���������붨���ͬһ�������"), false);
                return false; 
            }
        }

        //Ч��DNS��ַ
        String strPriDns = ITPadCommonOp::GetControlText( m_pm,_T("edtPriorityDNS") );
        if ( !strPriDns.empty() && !CCallAddr::IsValidCallIP(tIpCfg.dwPriorityCns) )
        {
            ShowMessageBox( _T("��ѡDNS��������ַ�Ƿ�"), false );
            return false;
        }

        String strBkupDns = ITPadCommonOp::GetControlText( m_pm,_T("edtBkupDNS") );
        if ( !strBkupDns.empty() && !CCallAddr::IsValidCallIP(tIpCfg.dwBkupCns) )
        {
            ShowMessageBox( _T("����DNS��������ַ�Ƿ�"), false );
            return false;
        }

        if ( tIpCfg.dwPriorityCns != 0 && tIpCfg.dwPriorityCns == tIpCfg.dwBkupCns )
        {   
            ShowMessageBox( _T("��ѡDNS�������ͱ���DNS��������ַ�������ظ�"), false );
            return false; 
        }
    }
    else
    {
        if ( !tIpCfg.bDnsDhcp)
        {
            //Ч��DNS��ַ
            String strPriDns = ITPadCommonOp::GetControlText( m_pm,_T("edtPriorityDNS") );
            if ( !strPriDns.empty() && !CCallAddr::IsValidCallIP(tIpCfg.dwPriorityCns) )
            {
                ShowMessageBox( _T("��ѡDNS��������ַ�Ƿ�"), false );
                return false;
            }

            String strBkupDns = ITPadCommonOp::GetControlText( m_pm,_T("edtBkupDNS") );
            if ( !strBkupDns.empty() && !CCallAddr::IsValidCallIP(tIpCfg.dwBkupCns) )
            {
                ShowMessageBox( _T("����DNS��������ַ�Ƿ�"), false );
                return false;
            }

            //DNS��ַ���ܶ�Ϊ�գ������Ƿ��Զ���ȡDNSֵ����
            if ( strPriDns.empty() && strBkupDns.empty() )
            {   
                ShowMessageBox( _T("��ѡDNS�ͱ���DNS��������ַ��Ϊ�գ������"), false );
                return false; 
            }

            if ( tIpCfg.dwPriorityCns != 0 && tIpCfg.dwPriorityCns == tIpCfg.dwBkupCns )
            {   
                ShowMessageBox( _T("��ѡDNS�������ͱ���DNS��������ַ�������ظ�"), false );
                return false; 
            }        
        }
    }
  
    m_tAUiIpCfg = tIpCfg;

    //ReFreshIpCfg();
    AfxBeginThread( ThreadSetIP, &m_tAUiIpCfg );  

    CModalWndLogic::GetSingletonPtr()->ShowModalWnd( _T("���������������磬�����ĵȴ�......") );

    return true;
}


bool CIpCfgLogic::OnCheckAutoIp(TNotifyUI& msg)
{
    CCheckBoxUI *pCheckBox = (CCheckBoxUI*)msg.pSender;

    bool bCheck = false;
    if ( pCheckBox != NULL && pCheckBox->GetCheck() )
    {
        bCheck = true;
    }

    if ( bCheck )
    {
        m_pm->DoCase( _T("caseUseIPDhcp") );
    }
    else
    {
        m_pm->DoCase( _T("caseNotUseIPDhcp") );
    }

    return true;
}

bool CIpCfgLogic::OnCheckAutoDns(TNotifyUI& msg)
{
    CCheckBoxUI *pCheckBox = (CCheckBoxUI*)msg.pSender;

    bool bCheck = false;
    if ( pCheckBox != NULL && pCheckBox->GetCheck() )
    {
        bCheck = true;
    }

    if ( bCheck )
    {
        m_pm->DoCase( _T("caseUseDnsDhcp") );
    }
    else
    {
        m_pm->DoCase( _T("caseNotUseDnsDhcp") );
    }
    return true;
}

bool CIpCfgLogic::GetIpCfgFrmUI( TIpConfig& tIpCfg )
{ 
    ZeroMemory(&tIpCfg,sizeof(TIpConfig) );

    CCheckBoxUI *pCheckAutoIp = (CCheckBoxUI*)ITPadCommonOp::FindControl( m_pm, _T("CheckAutoIpAddress") );
    if (pCheckAutoIp!= NULL)
    {
        tIpCfg.bIpDhcp = pCheckAutoIp->GetCheck();
    }   

    CCheckBoxUI *pCheckAutoDNS = (CCheckBoxUI*)ITPadCommonOp::FindControl( m_pm, _T("CheckAutoDNSAddress") );
    if (pCheckAutoDNS!= NULL)
    {
        tIpCfg.bDnsDhcp = pCheckAutoDNS->GetCheck();
    } 

    if ( !tIpCfg.bIpDhcp  )
    {
        String strIp = ITPadCommonOp::GetControlText( m_pm,_T("edtIP") ); 
        String strMask = ITPadCommonOp::GetControlText( m_pm,_T("edtSubnetMask") );
        String strGateWay = ITPadCommonOp::GetControlText( m_pm,_T("edtGateWay") );
        String strPriDns = ITPadCommonOp::GetControlText( m_pm,_T("edtPriorityDNS") );
        String strBkupDns = ITPadCommonOp::GetControlText( m_pm,_T("edtBkupDNS") );

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
            String strPriDns = ITPadCommonOp::GetControlText( m_pm,_T("edtPriorityDNS") );
            String strBkupDns = ITPadCommonOp::GetControlText( m_pm,_T("edtBkupDNS") );

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

//����UI�ϵ�IP������PC
BOOL CIpCfgLogic::SetPc( TIpConfig& tIpCfg )
{  
    bool bNeedSetIp = false ;
    if ( tIpCfg.bIpDhcp != m_tLocalIp.bIpDhcp )
    {   
        bNeedSetIp = true;
    } 
    else if( !tIpCfg.bIpDhcp  )  //���dhcp״̬��ͬ
    {
        if ( tIpCfg.dwIP != m_tLocalIp.dwIP || tIpCfg.dwSubMask != m_tLocalIp.dwSubMask
            || tIpCfg.dwGateWay != m_tLocalIp.dwGateWay )
        {
            bNeedSetIp = true;

        }         
    }

    if ( bNeedSetIp )
    {
        //����IP
        if ( tIpCfg.bIpDhcp  )
        {
            GetIPCfg()->SetDHCPToPC( TRUE );
        }
        else 
        {
            BOOL bOK = GetIPCfg()->SetIPToPC( tIpCfg.dwIP, tIpCfg.dwSubMask, tIpCfg.dwGateWay, TRUE );
            if ( !bOK )
            {
                return FALSE;
            }
        }       
    }  

    bool bNeedSetDNS = true ;

    if( tIpCfg.bDnsDhcp  && tIpCfg.bDnsDhcp == m_tLocalIp.bDnsDhcp  ) // ����Ҫ����dns��Ϣ
    {
        bNeedSetDNS = false;
    }

    if ( bNeedSetDNS )
    {
        if ( tIpCfg.bDnsDhcp )
        {
            GetIPCfg()->SetDnsDhcpToPc();
        }
        else
        {
            if (tIpCfg.dwPriorityCns != m_tLocalIp.dwPriorityCns )
            {
                if ( tIpCfg.dwPriorityCns == 0 )
                {
                    GetIPCfg()->DeleteDnsAddr( m_tLocalIp.dwPriorityCns );
                }
                else
                {
                    GetIPCfg()->SetDnsAddr( tIpCfg.dwPriorityCns );
                }              
            }

            if ( tIpCfg.dwBkupCns != m_tLocalIp.dwBkupCns )
            {
                if ( tIpCfg.dwBkupCns == 0 )
                {
                    GetIPCfg()->DeleteDnsAddr( m_tLocalIp.dwBkupCns );
                }
                else
                {
                    GetIPCfg()->SetBackupDnsAddr( tIpCfg.dwBkupCns );
                }             
            }
        }       
    } 

    return TRUE;
}


//����pc��IP������UI
void CIpCfgLogic::UpdateUI( TIpConfig& tIpCfg )
{
    bool bUseDchp = tIpCfg.bIpDhcp;
    ITPadCommonOp::OptionSelect( bUseDchp, m_pm, _T("CheckAutoIpAddress") );

    bool bAutoGetDns = tIpCfg.bDnsDhcp; 
    ITPadCommonOp::OptionSelect( bAutoGetDns, m_pm, _T("CheckAutoDNSAddress") );

    in_addr tAddr;
    tAddr.S_un.S_addr = htonl(tIpCfg.dwIP);
    String strIP = CA2T(inet_ntoa(tAddr));
    if ( strIP == _T("0.0.0.0") )
    {
        strIP = _T("");
    }
    ITPadCommonOp::SetControlText(strIP.c_str(),m_pm,_T("edtIP"));

    tAddr.S_un.S_addr = htonl(tIpCfg.dwSubMask);
    String strMaskIP = CA2T(inet_ntoa(tAddr));
    if ( strMaskIP == _T("0.0.0.0") )
    {
        strMaskIP = _T("");
    }
    ITPadCommonOp::SetControlText(strMaskIP.c_str(),m_pm,_T("edtSubnetMask")); 

    tAddr.S_un.S_addr = htonl(tIpCfg.dwGateWay);
    String strGateWayIP = CA2T(inet_ntoa(tAddr));
    if ( strGateWayIP == _T("0.0.0.0") )
    {
        strGateWayIP = _T("");
    }
    ITPadCommonOp::SetControlText(strGateWayIP.c_str(),m_pm,_T("edtGateWay")); 

    tAddr.S_un.S_addr = htonl(tIpCfg.dwPriorityCns);
    String strPriorityCns = CA2T(inet_ntoa(tAddr));
    if ( strPriorityCns == _T("0.0.0.0") )
    {
        strPriorityCns = _T("");
    }
    ITPadCommonOp::SetControlText(strPriorityCns.c_str(),m_pm,_T("edtPriorityDNS")); 

    tAddr.S_un.S_addr = htonl(tIpCfg.dwBkupCns);
    String strBkupCns = CA2T(inet_ntoa(tAddr));
    if ( strBkupCns == _T("0.0.0.0") )
    {
        strBkupCns = _T("");
    }
    ITPadCommonOp::SetControlText(strBkupCns.c_str(),m_pm,_T("edtBkupDNS")); 

    if ( bUseDchp )
    {   
        m_pm->DoCase( _T("caseUseIPDhcp") );
        if ( bAutoGetDns )
        {
            m_pm->DoCase( _T("caseUseDnsDhcp") );           
        }
        else
        {
            m_pm->DoCase( _T("caseNotUseDnsDhcp") ); 
        }
    }
    else
    {  
        m_pm->DoCase( _T("caseNotUseIPDhcp") );
    }    
}


void CIpCfgLogic::ReFreshIpCfg()
{
    CNetworkAdapter *pcAdt = NULL;
    u32 dwIP = 0;
    u32 dwMask = 0;
    u32 dwDns = 0;
    u32 dwGateWay= 0;
    u8 byUseDHCP = 0;

    bool bIs = CNetworkAdapter::InitIPCfgAPI();
    OspPrintf(TRUE,FALSE,"CNetworkAdapter::InitIPCfgAPI():%d\n",bIs);

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
    //PrtMsg("\nbDnsDhcp=%d\n",m_tLocalIp.bDnsDhcp);
    //DNS DHCPͨ��ע����ȡ������ͨ��dwPriorityCns�ж� -2012.9.3 xcr
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

    //��ֹIP����255.255
    if ( m_tLocalIp.dwIP == -1 )
    {
        m_tLocalIp.dwIP = 0;
    }
    if ( m_tLocalIp.dwSubMask == -1 )
    {
        m_tLocalIp.dwSubMask = 0;
    }
}

bool CIpCfgLogic::OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    ComInterface->ShowKeyboard();
    return true;
}