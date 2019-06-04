// tpadsession.cpp: implementation of the CTPadSession class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "tpadsession.h"
#include "tpadinstance.h"
#include "msgtransinstance.h"
#include "addrinstance.h"
#include "tpadconfctrl.h"
#include "cnsinnerstruct.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTPadSession::CTPadSession()
{
    m_bInitOsp = FALSE;
    m_dwCnsIp = 0;
    m_dwLocalIP = 0;

	m_pTpadSession = this;

    RegHandler(this);

//�ڸ����У�new�����еĹ����࣬�ⲿͨ���ӿ�GetInterface()��ȡ
#define NEW_REG(pCtrlIF, clsName)         \
	pCtrlIF = new clsName(*this);     \
	RegHandler(pCtrlIF);

	NEW_REG( m_pConfCtrlIF, CTpadConfCtrl );

#undef NEW_REG
}

CTPadSession::~CTPadSession()
{
    ClearDisp();
	UnregHandler(this);

    // ǿ�ƶϿ����� ��վ�̬����
    if(IsConnectedCns())
    {
        DisconnectCns();
    }

    SetNodeId(INVALID_NODE);
    MsgTransDriver->ClearOspMsg();

    // ���OSP���Լ���ʼ���ģ�����Ҫ�˳�OSP
    if(!m_bInitOsp)
    {
        OspQuit();
    }

	//�ͷſռ�
#define DEL_UNREG(pCtrlIF, clsName)           \
	UnregHandler(pCtrlIF);					  \
	if(NULL != pCtrlIF)                       \
	delete dynamic_cast<clsName*>(pCtrlIF);   \
	pCtrlIF = NULL;

	DEL_UNREG( m_pConfCtrlIF, CTpadConfCtrl );

#undef DEL_UNREG
}

void CTPadSession::InitEnv( u32 dwAppID )
{
    SetAppId( dwAppID );
    // ��ʼ��Osp
    u16 wRet = InitializeOsp();
    ASSERT(wRet == NO_ERROR);
}



u16 CTPadSession::TpadGetInterface(CTpadConfCtrlIF **ppCtrl)
{
	if( m_pConfCtrlIF != NULL)
	{
		*ppCtrl = m_pConfCtrlIF;
		return NO_ERROR;
	}
	else
	{
		*ppCtrl = NULL;
		return ERR_TPAD_TCPCONNECT;
	}
}

void CTPadSession::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CTPadSession, cMsg);
}

void CTPadSession::BuildEventsMap()
{
    REG_PFUN( OSP_DISCONNECT, CTPadSession::OnLinkBreak );
    REG_PFUN( ev_CnLogin_Rsp, CTPadSession::OnCnsLoginRsp );

	REG_PFUN( ev_Cn_CentreSleepNty, CTPadSession::OnCentreSleepNty );  

    REG_PFUN( ev_CNSLoginByOther_Notify, CTPadSession::OnLoginByOtherNotify );
    REG_PFUN( ev_TpadUpdateSystem_Cmd, CTPadSession::OnTpadUpdateCmd );    
    REG_PFUN( ev_TPadSetSysName_Nty, CTPadSession::OnCncSetSystemName );
	REG_PFUN( ev_TpadDisconnectCns_Nty, CTPadSession::DisConnectTpad );

	//����T300��Ϣ
	REG_PFUN( ev_CnUpdateSystemType_Nty, CTPadSession::OnT300UpdateNty );
	//ftp�˺�����������Ϣ
	REG_PFUN( ev_CnFtpInfo_Nty, CTPadSession::OnCnFtpInfoNty );
    REG_PFUN( ev_CnSetFtp_Rsp, CTPadSession::OnCnFtpInfoRsp );

	REG_PFUN( ev_CnsDisconnect_Nty, CTPadSession::OnCncNoReconnectNty );
}


void CTPadSession::OnTimeOut(u16 wEvent)
{ 
    //����ʱ��Ϣ
    if( wEvent == ev_CnLogin_Req )
    {
        // OSPͨ�������ɹ�,��ACK NACK��û���յ�
        OspDisconnectTcpNode( GetNodeId() );
        SetNodeId(INVALID_NODE);

        PostEvent( UI_CNS_LOGIN_TIMEOUT, wEvent );
    }
}


u16 CTPadSession::ConnectCns(u32 dwIP, u32 dwPort, LPSTR strUser,
	LPSTR strPwd,s8* achVersion, BOOL32 bConnect /* = TRUE */)
{
    // ����TCP����
    if( IsConnectedCns() )
    { 
        //����Ѿ���¼�˸�IP����ֱ�ӷ��أ�����Ͽ�����
        if ( dwIP == m_dwCnsIp )
        {
            return ERR_TPAD_ACTIVE_CONNECT;
        }
        else
        {
            DisconnectCns();
			return ERR_TPAD_ACTIVE_CONNECT;
        }      
    }
    
    //����Osp��TCP����,�õ����ػ�����IP��ַ
	u32 dwCnNodeId = 0;
	if ( bConnect )
	{
		dwCnNodeId = OspConnectTcpNode( htonl(dwIP), static_cast<u16>(dwPort), /*5*/10  
			, 3, 5000/*30000*/, &m_dwLocalIP );
		//������½Cns��ip
		m_dwCnsIp = dwIP;
		m_dwLocalIP = ntohl( m_dwLocalIP );
		if( dwCnNodeId == INVALID_NODE )
		{
			return ERR_TPAD_TCPCONNECT;
		}		
	}

    SetNodeId( dwCnNodeId );
    //������node�����ж�ʱ��֪ͨ��appid��InstId
    ::OspNodeDiscCBReg( dwCnNodeId, GetAppId(), 1 );

	m_cUser.Empty();
    m_cUser.SetName((s8*)(LPCTSTR)strUser);
    m_cUser.SetPassword((s8*)(LPCTSTR)strPwd);

    TTPTPadLoginRequest tLoginRequest;
    tLoginRequest.cLoginRequest = m_cUser;
    memcpy( tLoginRequest.achTPadVersion, achVersion, MAX_DEVICEVER_LEN );

    // ��CNS���͵�¼����
    u8 abyTemp[sizeof(TTPTPadLoginRequest) + 1] = {0};
    ZeroMemory(&m_cMsg, sizeof(CMessage));
    m_cMsg.event = ev_CnLogin_Req;
    m_cMsg.length = sizeof(TTPTPadLoginRequest);
	memcpy( abyTemp, &tLoginRequest, sizeof(TTPTPadLoginRequest) );

    m_cMsg.content = abyTemp;

    u16 awEvent[1];
    awEvent[0] = ev_CnLogin_Rsp;
	u16 wRet = PostCommand(this, awEvent, 1, TYPE_CMESSAGE, 3000);

	PrtMsg( ev_CnLogin_Req,emEventTypeCnsSend, "UserName=%s, Version=%s", m_cUser.GetName(), achVersion );

	return wRet;
}


BOOL CTPadSession::IsConnectedCns()
{
    return ( GetNodeId() != INVALID_NODE );
}


u16 CTPadSession::DisconnectCns()
{
    if( !IsConnectedCns() )
    {
        return NO_ERROR;
    }
    
    OspDisconnectTcpNode( GetNodeId() );
    m_dwCnsIp = 0;
    
    return NO_ERROR;
}


void CTPadSession::OnLinkBreak(const CMessage& cMsg)
{
    // OSP����֪ͨ
    u32 u32NodeId = *(u32*)(cMsg.content);
    
    PrtMsg( OSP_DISCONNECT, emEventTypeCnsRecv, "Link Break (NodeID: %d)", u32NodeId );
    
    ClearWaiting();	// OSP������,��δִ����������ж�ִ�� 
    ClearAllCommand(); // ��������ڶ����еȴ�ִ�е�����
    MsgTransDriver->ClearOspMsg();
    
    m_cUser.SetName("");
    m_cUser.SetPassword("");
    SetNodeId(INVALID_NODE);
    m_dwCnsIp = 0;
    
    PostEvent(UI_CNS_DISCONNECTED);
}


void CTPadSession::OnCnsLoginRsp(const CMessage& cMsg)
{
    // 	CTpMsg cTpMsg(&cMsg);
    // 	TLoginRet tLogRe = *reinterpret_cast<TLoginRet *>(cTpMsg.GetBody());
    
    TLoginRet tLogRe = *reinterpret_cast<TLoginRet *>( cMsg.content );

    EmTpLoginUmsRet emRet = tLogRe.GetRet();
    
    PrtMsg( ev_CnLogin_Rsp, emEventTypeCnsRecv,"EmTpLoginUmsRet: %d, ErrorCode: %d, ErrorNumber: %d ", emRet, tLogRe.m_dwErrorCode,tLogRe.m_byNumber );
	m_tLoginRet = tLogRe;//��¼���ؽ��
    
    BOOL bLogin = FALSE;
    u32 dwErrCode = NO_ERROR;
    if ( emRet == tp_LoginUms_sucess )
    {
         bLogin = TRUE;
    }
    
    // ֪ͨ����
    PostEvent( UI_CNS_CONNECTED, bLogin, emRet );
    
    if ( bLogin )
    {
        //֪ͨ��¼�û���Ϣ
        NotifyLoginUser();
    }
    else
    {
        DisconnectCns();
    }
    
}


void CTPadSession::NotifyLoginUser()
{
    CMessage cMsg;
    u8 abyTemp[sizeof(TPadLoginInfo) + 1] = {0};
    ZeroMemory(&cMsg, sizeof(CMessage));

    TPadLoginInfo tLoginInfo;
    tLoginInfo.dwCnsIp = m_dwCnsIp;
    tLoginInfo.dwLocalIp = m_dwLocalIP;
    tLoginInfo.cUserInfo = m_cUser;

    cMsg.event = ev_TPadLoginInfo_Nty;
    cMsg.length = sizeof(TPadLoginInfo);
    memcpy( abyTemp, &tLoginInfo, sizeof(TPadLoginInfo) );
    cMsg.content = abyTemp;

    MsgTransDriver->DispatchMsg( &cMsg );
}


//������
void CTPadSession::OnLoginByOtherNotify(const CMessage& cMsg)
{
    u32 dwIP = *reinterpret_cast<u32*>( cMsg.content );
    
    in_addr tAddr;
    tAddr.S_un.S_addr = dwIP ;   
    PrtMsg( ev_CNSLoginByOther_Notify, emEventTypeCnsRecv, "����֪ͨ(��ռ��IP: %s)", inet_ntoa(tAddr) );
    
    PostEvent( UI_UMS_GRAB_LOGIN_NOTIFY, (WPARAM)dwIP );
}


void CTPadSession::OnTpadUpdateCmd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    m_tVerInfo = *(TTPTPadVerInfo*)(cTpMsg.GetBody());

    PrtMsg( ev_TpadUpdateSystem_Cmd, emEventTypeCnsRecv, "EmTPUpdateType: %d, TPadVersion: %s, FilePath: %s",
		m_tVerInfo.m_emTPUpdateType, m_tVerInfo.m_achTPadVersion, m_tVerInfo.m_tPadVerFileInfo.achFilePath );

    PostEvent( UI_TPAD_UPDATESYS_CMD);
}


void CTPadSession::OnCentreSleepNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    PrtMsg( ev_Cn_CentreSleepNty, emEventTypeCnsRecv, "" );
    
    PostEvent( UI_TPAD_CENTRESLEEP_NTY );
}



u16 CTPadSession::InitializeOsp()
{
    // ��ʼ��OSP
    const u32 dwTelnetPort = 0;
    if( !IsOspInitd() )
    {
        
        BOOL bTelnet  = FALSE ;
        
#ifdef _DEBUG
        bTelnet = TRUE;
#endif
        
        if( !OspInit( bTelnet, dwTelnetPort) )
        {
            return ERR_TPAD_OSPINIT;
        }
        else
        {
            m_bInitOsp = FALSE;
        }
    }
    else
    {
        m_bInitOsp = TRUE;
    }
       
    //����tpad����cns App
    char szOspApp[] = "TPadLib1.0";
    const u32 dwPrior = 80;
    int nRet = g_tPadApp.CreateApp( &szOspApp[0], /*AID_CNC2CNS_APP*/GetAppId(), dwPrior, 300, 200 );
    ASSERT(nRet == 0);

    // �����¼�ӳ���
	BuildEventsMap(); 

    //�������ؼ����ڵ�
    nRet = ::OspCreateTcpNode( 0, TPAD_LISTEN_PORT, TRUE );
	OspPrintf( TRUE, FALSE,"�����˿ڷ���ֵ%d \n", nRet );
    if (INVALID_SOCKET == nRet)
    {
        return ERR_TPAD_CREAT_TCPNODE;
	}

    //������Ϣת��App
    nRet = g_MsgTransApp.CreateApp( "MsgTrans", AID_TPAD_MSGTRANS, dwPrior, 300, 200 );
    ASSERT(nRet == 0);

    //������ַ��App
    nRet = g_AddrBookApp.CreateApp( "Addrbook", AID_ADDRBOOK, dwPrior, 300, 1024);
	ASSERT(nRet == 0);

    PrtMsg( "TPadLib osp�����ɹ�\n" );
    
    return NO_ERROR;
}

//�޸�ϵͳ�������ڱ���ini�У�tpad�յ���Ϣ��ֱ�Ӷ�ȡ 2016-8-8
void CTPadSession::OnCncSetSystemName(const CMessage& cMsg)
{ 
    PrtMsg( ev_TPadSetSysName_Nty, emEventTypeCnsRecv, "cnc��ϵͳ���������޸�");
    PostEvent( UI_TPAD_SETSYSNAME ); 
}

BOOL CTPadSession::IsReadyLogin( vector<TNodeInfo>&vctNodeList )//dyy
{
    return MsgTransDriver->IsAlreadyReg( vctNodeList );
}

void CTPadSession::TPadHomeKeyNty()
{
    CMessage cMsg;
    ZeroMemory(&cMsg, sizeof(CMessage));
      
    cMsg.event = ev_TPadHomeKey_Nty;
    
    MsgTransDriver->DispatchMsg( &cMsg );
}

void CTPadSession::OpenCenterCtrl()
{
    CMessage cMsg;
    ZeroMemory(&cMsg, sizeof(CMessage));
	
    cMsg.event = ev_OpenCenterCtrl_Nty;
    

	PrtMsg( ev_OpenCenterCtrl_Nty, emEventTypeCnsSend, "TPad Show CenterCtrl" );
    MsgTransDriver->DispatchMsg( &cMsg );
}

void CTPadSession::OpenSysConfig()
{
	CMessage cMsg;
	ZeroMemory(&cMsg, sizeof(CMessage));

	cMsg.event = ev_OpenSysConfig_Nty;

	PrtMsg( ev_OpenSysConfig_Nty, emEventTypeCnsSend, "TPad Show SysConfig" );
	MsgTransDriver->DispatchMsg( &cMsg );
}


void CTPadSession::OpenCnsManage()
{
    CMessage cMsg;
    ZeroMemory(&cMsg, sizeof(CMessage));

    cMsg.event = ev_OpenCnsManage_Nty;

    PrtMsg( ev_OpenCnsManage_Nty, emEventTypeCnsSend, "TPad Show CnsManage" );
    MsgTransDriver->DispatchMsg( &cMsg );
}

void CTPadSession::DisConnectTpad( const CMessage& cMsg )
{
	DisconnectCns();
}

void CTPadSession::OnT300UpdateNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 
    
    EmTPUpdateType emTPUpdateType = *reinterpret_cast<EmTPUpdateType*>(cTpMsg.GetBody());
    
    PrtMsg( ev_CnUpdateSystemType_Nty, emEventTypeCnsRecv, "emTPUpdateType:%d",emTPUpdateType );
    
    PostEvent( UI_TPPUPDATET300NTY, 0, 0 );
}

void CTPadSession::T300UpdateInd( BOOL bIsUpT300 )
{
	CTpMsg *pcTpMsg = m_pTpadSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( 1 );
    pcTpMsg->SetEvent( ev_TpsT300Update_Ind );
    pcTpMsg->SetBody( &bIsUpT300, sizeof(BOOL) );
    
    u16 wRet = m_pTpadSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TpsT300Update_Ind, emEventTypeCnsSend, "bIsUpT300:%d", bIsUpT300 );

}

void CTPadSession::OnCnFtpInfoNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	m_tTPFtpInfo = *(TTPFtpInfo*)( cTpMsg.GetBody() ); 
	PrtMsg( ev_CnFtpInfo_Nty, emEventTypecnstoolRecv, "bOpen:%d", m_tTPFtpInfo.bOpen );
}

void CTPadSession::OnCnFtpInfoRsp(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    TTPFtpInfo tTPFtpInfo = *(TTPFtpInfo*)( cTpMsg.GetBody() ); 
    BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPFtpInfo));
    if (bSuccess)
    {
        m_tTPFtpInfo = tTPFtpInfo;
    }
    PrtMsg( ev_CnSetFtp_Rsp, emEventTypecnstoolRecv, "bSuccess:%d", bSuccess );
    PostEvent( UI_CNSETFTPRSP, 0, 0 );
}


void CTPadSession::NotifyCnsDisconnect( BOOL bActiveExit )
{
	CMessage cMsg;
	ZeroMemory(&cMsg, sizeof(CMessage));
	u8 abyTemp[sizeof(BOOL) + 1] = {0};

	cMsg.event = ev_CnsDisconnect_Nty;
	cMsg.length = sizeof(BOOL);
	memcpy( abyTemp, &bActiveExit, sizeof(BOOL) );
	cMsg.content = abyTemp;

	PrtMsg( ev_CnsDisconnect_Nty, emEventTypeCnsSend, "bActiveExit:%d", bActiveExit );
	MsgTransDriver->DispatchMsg( &cMsg );
}

void CTPadSession::OnCncNoReconnectNty(const CMessage& cMsg)
{
	PrtMsg( ev_CnsDisconnect_Nty, emEventTypeTPadRecv, "" );

	PostEvent( UI_TPAD_CNSDISCONNECTED_NTY, 0, 0 );
}

u16 CTPadSession::SetCnFtpInfo(const TTPFtpInfo tTPFtpInfo)
{
    CTpMsg *pcTpMsg = m_pTpadSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( 1 );
    pcTpMsg->SetEvent( ev_CnSetFtp_Req );
    pcTpMsg->SetBody( &tTPFtpInfo, sizeof(TTPFtpInfo) );

    u16 wRet = m_pTpadSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_CnSetFtp_Req, emEventTypeCnsSend, "tTPFtpInfo.bOpen: %d, tTPFtpInfo.achUserName: %s, tTPFtpInfo.achPassword: %s", tTPFtpInfo.bOpen, tTPFtpInfo.achUserName, tTPFtpInfo.achPassword );

    return wRet;
}