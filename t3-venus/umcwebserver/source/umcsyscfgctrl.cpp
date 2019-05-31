#include "umcglodef.h"
#include "umcsyscfgctrl.h"
#include <time.h>
#include <sys/time.h>

static time_t g_timeDate;
void sigroutine(int signo)
{
	if ( SIGALRM == signo )
	{
		//printf("Catch a signal -- SIGALRM \n");
		g_timeDate += 1;
		//防止time_t越界
		if ( g_timeDate < 0 )
		{
			g_timeDate = 0;
		}

		signal(SIGALRM, sigroutine);
	}

	//fflush(stdout);
	return;
}

CUmcSysCfgCtrl::CUmcSysCfgCtrl()
{
	ClearData();

    BuildEventsMap();
}

CUmcSysCfgCtrl::~CUmcSysCfgCtrl()
{
	ClearData();
}

void CUmcSysCfgCtrl::ClearData()
{
	m_vecUser.clear();
	memset( &m_tEthnet, 0, sizeof(TTPEthnetInfo)) ;
	memset( &m_tSipRegCfg, 0, sizeof(TTPSipRegistrarCfg) );
	memset( &m_tGKRegCfg, 0, sizeof(TTPGKCfg) );
	m_vecTTPNMServerCfg.clear();
}

void CUmcSysCfgCtrl::BuildEventsMap()
{
	//REG_PFUN(evtp_HungUpConf_result, &CUmcSysCfgCtrl::OnHungUpConfRsp );
	REG_PFUN(ev_UmsAddUser_Notify,&CUmcSysCfgCtrl::OnAddUserNotify);
	REG_PFUN(ev_UmsUpdateUser_Notify,&CUmcSysCfgCtrl::OnUpdateUserNotify);
	REG_PFUN(ev_UmsDelUser_Notify,&CUmcSysCfgCtrl::OnDelUserNotify);
	
	REG_PFUN(ev_UMSAddUserRet,&CUmcSysCfgCtrl::OnAddUserRsp);
	REG_PFUN(ev_UMSChangePWDRet,&CUmcSysCfgCtrl::OnChangePWDRsp);
	REG_PFUN(ev_UMSDelUserRet,&CUmcSysCfgCtrl::OnDelUserRsp);

	REG_PFUN(ev_UmsIPCfg_Ind,&CUmcSysCfgCtrl::OnIPCfgNty);
	REG_PFUN(ev_umsreg_notify,&CUmcSysCfgCtrl::OnSipserverNty);
	REG_PFUN(ev_umsGKReg_notify,&CUmcSysCfgCtrl::OnGkserverNty);
	
	

	REG_PFUN(ev_UmsGetSysTime_Rsp, &CUmcSysCfgCtrl::OnUmsGetSysTimeRsp);

//	REG_PFUN(ev_NMServer_nty, &CUmcSysCfgCtrl::OnNetMngNty);
//	REG_PFUN(ev_NMServerAdd_rsp, &CUmcSysCfgCtrl::OnAddNetMngRsp);
//	REG_PFUN(ev_NMServerMdy_rsp, &CUmcSysCfgCtrl::OnModifyNetMngRsp);
//	REG_PFUN(ev_NMServerDel_rsp, &CUmcSysCfgCtrl::OnDelNetMngRsp);
	
	//断链清空资源
	REG_PFUN( OSP_DISCONNECT, &CUmcSysCfgCtrl::OnLinkBreak ); 

	BuildReqEventsMap();
}

void CUmcSysCfgCtrl::BuildReqEventsMap()
{
	REG_REQ_PFUN( ev_umcweb_AddUser_req, &CUmcSysCfgCtrl::OnUmcwebAddUserReq );
	REG_REQ_PFUN( ev_umcweb_ChangePwd_req, &CUmcSysCfgCtrl::OnUmcwebChangePwdReq );
	REG_REQ_PFUN( ev_umcweb_DelUser_req, &CUmcSysCfgCtrl::OnUmcwebDelUserReq );
	REG_REQ_PFUN( ev_umcweb_User_nty_req, &CUmcSysCfgCtrl::OnUmcwebUserNtyReq );

	REG_REQ_PFUN( ev_umcweb_IpCfg_req, &CUmcSysCfgCtrl::OnUmcwebIpCfgReq );
	REG_REQ_PFUN( ev_umcweb_IpCfg_nty_req, &CUmcSysCfgCtrl::OnUmcwebIpCfgNtyReq );

	REG_REQ_PFUN( ev_umcweb_sipserver_req, &CUmcSysCfgCtrl::OnUmcwebSipserverReq );
	REG_REQ_PFUN( ev_umcweb_sipserver_nty_req, &CUmcSysCfgCtrl::OnUmcwebSipserverNtyReq );

	REG_REQ_PFUN( ev_umcweb_gkserver_req, &CUmcSysCfgCtrl::OnUmcwebGkserverReq );
	REG_REQ_PFUN( ev_umcweb_gkserver_nty_req, &CUmcSysCfgCtrl::OnUmcwebGkserverNtyReq );
	

	REG_REQ_PFUN( ev_umcweb_SetSysTime_req, &CUmcSysCfgCtrl::OnUmcwebSetSysTimeReq );
	REG_REQ_PFUN( ev_umcweb_GetSysTime_nty_req, &CUmcSysCfgCtrl::OnUmcwebGetSysTimeNtyReq );

//	REG_REQ_PFUN( ev_umcweb_NMServer_req, &CUmcSysCfgCtrl::OnUmcwebNMServerReq );
//	REG_REQ_PFUN( ev_umcweb_NMServer_nty_req, &CUmcSysCfgCtrl::OnUmcwebNMServerNtyReq );
}

void CUmcSysCfgCtrl::DispEvent(const CMessage &cMsg)
{
    DISP_FUN( CUmcSysCfgCtrl, cMsg );
}

void CUmcSysCfgCtrl::DispReqEvent( u16 wEvent, const boost::any& arg )
{
    DISP_REQ_FUN( CUmcSysCfgCtrl, wEvent, arg );
}

void CUmcSysCfgCtrl::OnLinkBreak( const CMessage& cMsg )
{
	ClearData();

	PrtMsg( OSP_DISCONNECT, emEventTypeServerRecv,"CUmcSysCfgCtrl::OnLinkBreak"); 
}

void CUmcSysCfgCtrl::OnAddUserNotify( const CMessage& cMsg )
{
	CUserFullInfo cUser = *reinterpret_cast<CUserFullInfo *>( cMsg.content );
	
	PrtMsg( ev_UmsAddUser_Notify,emEventTypeServerRecv,"userName:%s, userPwd:%s", cUser.name, cUser.password );
	
	m_vecUser.push_back(cUser);
}

void CUmcSysCfgCtrl::OnUpdateUserNotify( const CMessage& cMsg )
{
	CUserFullInfo cUser = *reinterpret_cast<CUserFullInfo *>( cMsg.content );
	
	PrtMsg( ev_UmsUpdateUser_Notify,emEventTypeServerRecv,"userName:%s, userPwd:%s", cUser.name, cUser.password );

	vector<CUserFullInfo>::iterator it = m_vecUser.begin();
	for ( ; it != m_vecUser.end(); it++ )
	{
		if ( strcmp( it->name, cUser.name ) == 0 )
		{
			strcpy( it->password, cUser.password );
		}
	}
}

void CUmcSysCfgCtrl::OnDelUserNotify( const CMessage& cMsg )
{
	CUserFullInfo cUser = *reinterpret_cast<CUserFullInfo *>( cMsg.content );
	
	PrtMsg( ev_UmsDelUser_Notify,emEventTypeServerRecv,"userName:%s, userPwd:%s", cUser.name, cUser.password );

	vector<CUserFullInfo>::iterator it = m_vecUser.begin();
	for ( ; it != m_vecUser.end(); it++ )
	{
		if ( strcmp( it->name, cUser.name ) == 0 )
		{
			m_vecUser.erase(it);
			break;
		}
	}
}


void CUmcSysCfgCtrl::OnAddUserRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg( &cMsg ); 
    EmTpRet emRet = *reinterpret_cast<EmTpRet *>( kdvMsg.GetBody() );
	
	PrtMsg( ev_UMSAddUserRet,emEventTypeServerRecv,"emRet: %d ( 0:Failed, 1:Success )",emRet );

	//fcgi 应答（json到前端）
	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_AddUser_res\",\"emRet\":\"%d\"}", emRet );
	
	PrtMsg( ev_umcweb_AddUser_res, emEventTypeClientSend, "emRet:%d", emRet );
}

void CUmcSysCfgCtrl::OnChangePWDRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg( &cMsg ); 
    EmTpRet emRet = *reinterpret_cast<EmTpRet *>( kdvMsg.GetBody() );
	
	PrtMsg( ev_UMSChangePWDRet,emEventTypeServerRecv,"emRet: %d ( 0:Failed, 1:Success )",emRet );
	
	//fcgi 应答（json到前端）
	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_ChangePwd_res\",\"emRet\":\"%d\"}", emRet );
	
	PrtMsg( ev_umcweb_ChangePwd_res, emEventTypeClientSend, "emRet:%d", emRet );
}

void CUmcSysCfgCtrl::OnDelUserRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg( &cMsg ); 
    EmTpRet emRet = *reinterpret_cast<EmTpRet *>( kdvMsg.GetBody() );
	
	PrtMsg( ev_UMSDelUserRet,emEventTypeServerRecv,"emRet: %d ( 0:Failed, 1:Success )",emRet );
	
	//fcgi 应答（json到前端）
	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_DelUser_res\",\"emRet\":\"%d\"}", emRet );
	
	PrtMsg( ev_umcweb_DelUser_res, emEventTypeClientSend, "emRet:%d", emRet );
}

void CUmcSysCfgCtrl::ShowSysCfginfo()
{
	PrtMsg( "\n--------------------系统配置---------------------\n" );

	//用户信息
	vector<CUserFullInfo>::iterator it = m_vecUser.begin();
	for ( ; it != m_vecUser.end(); it++ )
	{
		CUserFullInfo cUser = *it;

		PrtMsg( "\n----------------------------userName:%s, userPwd:%s-------------------------------\n", cUser.name, cUser.password );
	}
}

u16 CUmcSysCfgCtrl::OnUmcwebAddUserReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strName = COwsCommon::GetPropertyTreeVar( pt, "name" );
	std::string strPwd = COwsCommon::GetPropertyTreeVar( pt, "pwd" );
	
	PrtMsg( ev_umcweb_AddUser_req, emEventTypeClientRecv, "name:%s, pwd:%s", strName.c_str(), strPwd.c_str() );
	
	CUserFullInfo tUserInfo;
	tUserInfo.SetName((char*)strName.c_str());
	tUserInfo.SetPassword((char*)strPwd.c_str());

	CMessage* pCMsg = PTR_MSGDRIVER->GetCMsgPtr();
	pCMsg->event = ev_UMSAddUserReq;
	pCMsg->content =  (u8*)&tUserInfo;
	pCMsg->length = sizeof(CLoginRequest);	
	
    PrtMsg( ev_UMSAddUserReq, emEventTypeServerSend, "name:%s, pwd:%s", strName.c_str(), strPwd.c_str() );

	PTR_MSGDRIVER->PostCommand(this, ev_UMSAddUserRet);

	return NO_ERROR;
}

u16 CUmcSysCfgCtrl::OnUmcwebChangePwdReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strName = COwsCommon::GetPropertyTreeVar( pt, "name" );
	std::string strPwd = COwsCommon::GetPropertyTreeVar( pt, "pwd" );
	
	PrtMsg( ev_umcweb_ChangePwd_req, emEventTypeClientRecv, "name:%s, pwd:%s", strName.c_str(), strPwd.c_str() );
	
	CUserFullInfo tUserInfo;
	tUserInfo.SetName((char*)strName.c_str());
	tUserInfo.SetPassword((char*)strPwd.c_str());
	
	CMessage* pCMsg = PTR_MSGDRIVER->GetCMsgPtr();
	pCMsg->event = ev_UMSChangePWDReq;
	pCMsg->content =  (u8*)&tUserInfo;
	pCMsg->length = sizeof(CLoginRequest);	
	
    PrtMsg( ev_UMSChangePWDReq, emEventTypeServerSend, "name:%s, pwd:%s", strName.c_str(), strPwd.c_str() );
	
	PTR_MSGDRIVER->PostCommand(this, ev_UMSChangePWDRet);
	
	return NO_ERROR;
}

u16 CUmcSysCfgCtrl::OnUmcwebDelUserReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strName = COwsCommon::GetPropertyTreeVar( pt, "name" );
	
	PrtMsg( ev_umcweb_DelUser_req, emEventTypeClientRecv, "name:%s", strName.c_str() );
	
	CUserFullInfo tUserInfo;
	tUserInfo.SetName((char*)strName.c_str());
	
	CMessage* pCMsg = PTR_MSGDRIVER->GetCMsgPtr();
	pCMsg->event = ev_UMSDelUserReq;
	pCMsg->content =  (u8*)&tUserInfo;
	pCMsg->length = sizeof(CLoginRequest);	
	
    PrtMsg( ev_UMSDelUserReq, emEventTypeServerSend, "name:%s", strName.c_str() );
	
	PTR_MSGDRIVER->PostCommand(this, ev_UMSDelUserRet);
	
	return NO_ERROR;
}


void CUmcSysCfgCtrl::OnIPCfgNty( const CMessage& cMsg )
{
	CTpMsg kdvMsg( &cMsg );
    m_tEthnet = *reinterpret_cast<TTPEthnetInfo*>( kdvMsg.GetBody() );

	std::string strAddr;
	std::string strAddrMsk;
	std::string strAddrGateway;
	
	in_addr tAddr;
	tAddr.s_addr = m_tEthnet.dwIP;
	strAddr = inet_ntoa(tAddr);
	
	in_addr tAddrMsk;
	tAddrMsk.s_addr = m_tEthnet.dwMask;
	strAddrMsk = inet_ntoa(tAddrMsk);
	
	in_addr tAddrGateWay;
	tAddrGateWay.s_addr = m_tEthnet.dwGateWay;
	strAddrGateway = inet_ntoa(tAddrGateWay);
	
	PrtMsg( ev_UmsIPCfg_Ind, emEventTypeServerRecv, "ip:%s, submask:%s, gateway:%s", 
		strAddr.c_str(),strAddrMsk.c_str(),strAddrGateway.c_str() );


	if ( PTR_SESSION->m_bRefresh == TRUE )
	{
		//fcgi 应答（json到前端）
		string strJson = COwsCommon::StringFormat( "{\"event\":\"ev_umcweb_IpCfg_res\",\"ip\":\"%s\",\"submask\":\"%s\",\"gateway\":\"%s\""
			, strAddr.c_str(),strAddrMsk.c_str(),strAddrGateway.c_str() );

		PTR_FCGIPRINTF( strJson.c_str() );
		
		PrtMsg( ev_umcweb_IpCfg_res, emEventTypeClientSend, strJson.c_str() );
		
		PTR_SESSION->m_bRefresh = FALSE;
	}
}

void CUmcSysCfgCtrl::OnSipserverNty( const CMessage& cMsg )
{
	CTpMsg kdvMsg( &cMsg );
    m_tSipRegCfg = *reinterpret_cast<TTPSipRegistrarCfg*>( kdvMsg.GetBody() );
	
	std::string strAddr;
	
	in_addr tAddr;
	tAddr.s_addr = m_tSipRegCfg.dwRegIP;
	strAddr = inet_ntoa(tAddr);

	
	PrtMsg( ev_umsreg_notify, emEventTypeServerRecv, "ip:%s", strAddr.c_str() );
	
	
	if ( PTR_SESSION->m_bRefresh == TRUE )
	{
		//fcgi 应答（json到前端）
		string strJson = COwsCommon::StringFormat( "{\"event\":\"ev_umcweb_sipserver_res\",\"ip\":\"%s\"", strAddr.c_str() );
		
		PTR_FCGIPRINTF( strJson.c_str() );
		
		PrtMsg( ev_umcweb_sipserver_res, emEventTypeClientSend, strJson.c_str() );
		
		PTR_SESSION->m_bRefresh = FALSE;
	}
}

void CUmcSysCfgCtrl::OnGkserverNty( const CMessage& cMsg )
{
	CTpMsg kdvMsg( &cMsg );
    m_tGKRegCfg = *reinterpret_cast<TTPGKCfg*>( kdvMsg.GetBody() );
	
	std::string strAddr;
	
	in_addr tAddr;
	tAddr.s_addr = m_tGKRegCfg.dwGKIP;
	strAddr = inet_ntoa(tAddr);
	
	BOOL bReg = m_tGKRegCfg.bRegistered;
	
	PrtMsg( ev_umsGKReg_notify, emEventTypeServerRecv, "ip:%s, bUsed=%d", strAddr.c_str(), bReg );
	
	
	if ( PTR_SESSION->m_bRefresh == TRUE )
	{
		//fcgi 应答（json到前端）
		string strJson = COwsCommon::StringFormat( "{\"event\":\"ev_umcweb_gkserver_res\",\"ip\":\"%s\",\"bReg\":\"%d\""
			, strAddr.c_str(), bReg );
		
		PTR_FCGIPRINTF( strJson.c_str() );
		
		PrtMsg( ev_umcweb_gkserver_res, emEventTypeClientSend, strJson.c_str() );
		
		PTR_SESSION->m_bRefresh = FALSE;
	}
}

u16 CUmcSysCfgCtrl::OnUmcwebIpCfgReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strIp = COwsCommon::GetPropertyTreeVar( pt, "ip" );
	std::string strSubmask = COwsCommon::GetPropertyTreeVar( pt, "submask" );
	std::string strGateway = COwsCommon::GetPropertyTreeVar( pt, "gateway" );
	
	PrtMsg( ev_umcweb_IpCfg_req, emEventTypeClientRecv, "ip:%s, submask:%s, gateway:%s", strIp.c_str(), strSubmask.c_str(), strGateway.c_str() );
	
	TTPEthnetInfo tTypethnetInfo;
	tTypethnetInfo.bEnable = TRUE;
	tTypethnetInfo.dwIP = inet_addr(strIp.c_str());
	tTypethnetInfo.dwMask = inet_addr(strSubmask.c_str());
	tTypethnetInfo.dwGateWay = inet_addr(strGateway.c_str());

	if ( m_tEthnet.dwIP == tTypethnetInfo.dwIP && m_tEthnet.dwMask == tTypethnetInfo.dwMask && m_tEthnet.dwGateWay == tTypethnetInfo.dwGateWay )
	{
		std::string strAddr;
		std::string strAddrMsk;
		std::string strAddrGateway;
		
		in_addr tAddr;
		tAddr.s_addr = m_tEthnet.dwIP;
		strAddr = inet_ntoa(tAddr);
		
		in_addr tAddrMsk;
		tAddrMsk.s_addr = m_tEthnet.dwMask;
		strAddrMsk = inet_ntoa(tAddrMsk);
		
		in_addr tAddrGateWay;
		tAddrGateWay.s_addr = m_tEthnet.dwGateWay;
		strAddrGateway = inet_ntoa(tAddrGateWay);
		
		string strJson = COwsCommon::StringFormat( "{\"event\":\"ev_UmsIPCfg_Ind\",\"ip\":\"%s\",\"submask\":\"%s\",\"gateway\":\"%s\"}"
			, strAddr.c_str(),strAddrMsk.c_str(),strAddrGateway.c_str() );
		
		PTR_FCGIPRINTF( strJson.c_str() );
		
		PrtMsg( ev_UmsIPCfg_Ind, emEventTypeClientSend, strJson.c_str() );
		
		return NO_ERROR;
	}

	CTpMsg *pcTpMsg = PTR_MSGDRIVER->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_UmsIPCfg );
	pcTpMsg->SetBody( &tTypethnetInfo, sizeof(TTPEthnetInfo) );
	
	//shishi
	
    PrtMsg( ev_UmsIPCfg, emEventTypeServerSend, "ip:%s, submask:%s, gateway:%s", strIp.c_str(), strSubmask.c_str(), strGateway.c_str() );
	

	PTR_SESSION->m_bRefresh = TRUE;

	/*
	PTR_MSGDRIVER->PostCommand(this, ev_UmsIPCfg_Ind, TYPE_TPMSG);
	*/
	
	
	return NO_ERROR;
}

u16 CUmcSysCfgCtrl::OnUmcwebSipserverReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strIp = COwsCommon::GetPropertyTreeVar( pt, "ip" );
	
	PrtMsg( ev_umcweb_sipserver_req, emEventTypeClientRecv, "ip:%s", strIp.c_str() );
	
	TTPSipRegistrarCfg tSip;
	tSip.bUsed = TRUE;
	tSip.dwRegIP = inet_addr(strIp.c_str());
	tSip.wRegPort = 5060;
	tSip.wExpire = 30;
	
	CTpMsg *pcTpMsg = PTR_MSGDRIVER->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_umsreg_cmd );
	pcTpMsg->SetBody( &tSip, sizeof(TTPSipRegistrarCfg) );
	
    PrtMsg( ev_umsreg_cmd, emEventTypeServerSend, "ip:%s", strIp.c_str() );
	
	PTR_SESSION->m_bRefresh = TRUE;
	
	PTR_MSGDRIVER->PostCommand(this, ev_umsreg_notify, TYPE_TPMSG);
	
	return NO_ERROR;
}

u16 CUmcSysCfgCtrl::OnUmcwebGkserverReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strIp = COwsCommon::GetPropertyTreeVar( pt, "ip" );
	BOOL bReg = boost::lexical_cast<BOOL>(atoi(COwsCommon::GetPropertyTreeVar( pt, "bReg" ).c_str()));
	
	PrtMsg( ev_umcweb_gkserver_req, emEventTypeClientRecv, "ip:%s, bReg:%d", strIp.c_str(), bReg );
	
	TTPGKCfg tGKCfg;
	tGKCfg.bUsed = bReg;
	tGKCfg.dwGKIP = inet_addr(strIp.c_str());
	tGKCfg.wExpire = 30;
	
	CTpMsg *pcTpMsg = PTR_MSGDRIVER->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_umsGKReg_cmd );
	pcTpMsg->SetBody( &tGKCfg, sizeof(TTPGKCfg) );	
	
    PrtMsg( ev_umsGKReg_cmd, emEventTypeServerSend, "ip:%s, bReg:%d", strIp.c_str(), bReg );
	
	PTR_SESSION->m_bRefresh = TRUE;
	
	PTR_MSGDRIVER->PostCommand(this, ev_umsGKReg_notify, TYPE_TPMSG);
	
	return NO_ERROR;
}

u16 CUmcSysCfgCtrl::OnUmcwebIpCfgNtyReq(const boost::any& arg)
{
	PrtMsg( ev_umcweb_IpCfg_nty_req, emEventTypeClientRecv, "" );
	
	std::string strAddr;
	std::string strAddrMsk;
	std::string strAddrGateway;
	
	in_addr tAddr;
	tAddr.s_addr = m_tEthnet.dwIP;
	strAddr = inet_ntoa(tAddr);
	
	in_addr tAddrMsk;
	tAddrMsk.s_addr = m_tEthnet.dwMask;
	strAddrMsk = inet_ntoa(tAddrMsk);
	
	in_addr tAddrGateWay;
	tAddrGateWay.s_addr = m_tEthnet.dwGateWay;
	strAddrGateway = inet_ntoa(tAddrGateWay);

	string strJson = COwsCommon::StringFormat( "{\"event\":\"ev_umcweb_IpCfg_nty_res\",\"ip\":\"%s\",\"submask\":\"%s\",\"gateway\":\"%s\"}"
		, strAddr.c_str(),strAddrMsk.c_str(),strAddrGateway.c_str() );
	
	PTR_FCGIPRINTF( strJson.c_str() );
	
	PrtMsg( ev_umcweb_IpCfg_nty_res, emEventTypeClientSend, strJson.c_str() );
	
	return NO_ERROR;
}

u16 CUmcSysCfgCtrl::OnUmcwebSipserverNtyReq(const boost::any& arg)
{
	PrtMsg( ev_umcweb_sipserver_nty_req, emEventTypeClientRecv, "" );
	
	std::string strAddr;
	
	in_addr tAddr;
	tAddr.s_addr = m_tSipRegCfg.dwRegIP;
	strAddr = inet_ntoa(tAddr);
	
	
	string strJson = COwsCommon::StringFormat( "{\"event\":\"ev_umcweb_sipserver_nty_res\",\"ip\":\"%s\"}", strAddr.c_str() );
	
	PTR_FCGIPRINTF( strJson.c_str() );
	
	PrtMsg( ev_umcweb_sipserver_nty_res, emEventTypeClientSend, strJson.c_str() );
	
	return NO_ERROR;
}


u16 CUmcSysCfgCtrl::OnUmcwebGkserverNtyReq(const boost::any& arg)
{
	PrtMsg( ev_umcweb_gkserver_nty_req, emEventTypeClientRecv, "" );
	
	std::string strAddr;
	
	in_addr tAddr;
	tAddr.s_addr = m_tGKRegCfg.dwGKIP;
	strAddr = inet_ntoa(tAddr);
	
	BOOL bReg = m_tGKRegCfg.bRegistered;
	
	
	string strJson = COwsCommon::StringFormat( "{\"event\":\"ev_umcweb_gkserver_nty_res\",\"ip\":\"%s\",\"bReg\":\"%d\"}"
		, strAddr.c_str(), bReg );
	
	PTR_FCGIPRINTF( strJson.c_str() );
	
	PrtMsg( ev_umcweb_gkserver_nty_res, emEventTypeClientSend, strJson.c_str() );
	
	return NO_ERROR;
}

u16 CUmcSysCfgCtrl::OnUmcwebUserNtyReq(const boost::any& arg)
{
	PrtMsg( ev_umcweb_User_nty_req, emEventTypeClientRecv, "" );

	string strJsonHead = "{\"event\":\"ev_umcweb_User_nty_res\",\"items\":";

	vector<string> vecStrJson;
	
	std::vector<CUserFullInfo>::iterator it = m_vecUser.begin();
	for ( ; it != m_vecUser.end(); it++ )
	{
		char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
		sprintf( chItem, "{\"name\":\"%s\"}", it->name );
		
		vecStrJson.push_back(chItem);
	}
	
	std::string strJson = COwsCommon::CreateStringJson( strJsonHead, vecStrJson );

	PTR_FCGIPRINTF( strJson.c_str() );
	PrtMsg( ev_umcweb_User_nty_res, emEventTypeClientSend, "strJson:%s", strJson.c_str() );
	
	return NO_ERROR;
}

u16 CUmcSysCfgCtrl::OnUmcwebSetSysTimeReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	ptree pte = COwsCommon::GetPropertyTree(strData);
	std::string strYear = COwsCommon::GetPropertyTreeVar( pte, "nYear" );
	std::string strMonth = COwsCommon::GetPropertyTreeVar( pte, "nMonth" );
	std::string strMDay = COwsCommon::GetPropertyTreeVar( pte, "nMDay" );
	std::string strHour = COwsCommon::GetPropertyTreeVar( pte, "nHour" );
	std::string strMinute = COwsCommon::GetPropertyTreeVar( pte, "nMinute" );
	std::string strSecond = COwsCommon::GetPropertyTreeVar( pte, "nSecond" );

	PrtMsg( ev_umcweb_SetSysTime_req, emEventTypeClientRecv, "set server time: %s-%s-%s %s:%s:%s",
		strYear.c_str(), strMonth.c_str(), strMDay.c_str(), strHour.c_str(), strMinute.c_str(), strSecond.c_str() );

	PTR_SESSION->m_bRefresh = TRUE;
	
	TTPTime tTPTimeSever;
	tTPTimeSever.m_wYear = atoi(strYear.c_str());
	tTPTimeSever.m_byMonth = atoi(strMonth.c_str());
	tTPTimeSever.m_byMDay = atoi(strMDay.c_str());
	tTPTimeSever.m_byHour = atoi(strHour.c_str());
	tTPTimeSever.m_byMinute = atoi(strMinute.c_str());
	tTPTimeSever.m_bySecond = atoi(strSecond.c_str());

	CTpMsg *pcTpMsg = PTR_MSGDRIVER->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_UmsSetSysTime_Cmd );
	pcTpMsg->SetBody( &tTPTimeSever, sizeof(TTPTime) );
	
    PrtMsg( ev_UmsSetSysTime_Cmd, emEventTypeServerSend, "set server time: %d-%d-%d %d:%d:%d",
		tTPTimeSever.m_wYear, tTPTimeSever.m_byMonth, tTPTimeSever.m_byMDay, tTPTimeSever.m_byHour, tTPTimeSever.m_byMinute, tTPTimeSever.m_bySecond );
	
	PTR_MSGDRIVER->PostCommand(this, ev_UmsGetSysTime_Rsp, TYPE_TPMSG);

	return NO_ERROR;
}

void CUmcSysCfgCtrl::OnUmsGetSysTimeRsp( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);	
	TTPTime tTime = *reinterpret_cast<TTPTime*>(cTpMsg.GetBody());
	
	if ( tTime.IsValid() )
	{
		PrtMsg( ev_UmsGetSysTime_Rsp, emEventTypeServerRecv, "get server time: %d-%d-%d %d:%d:%d",
			tTime.m_wYear, tTime.m_byMonth, tTime.m_byMDay, tTime.m_byHour, tTime.m_byMinute, tTime.m_bySecond );

		struct tm tmDate;
		memset(&tmDate, 0, sizeof(tmDate));
		tmDate.tm_year = tTime.m_wYear - 1900;
		tmDate.tm_mon = tTime.m_byMonth - 1;
		tmDate.tm_mday = tTime.m_byMDay;
		tmDate.tm_hour = tTime.m_byHour;
		tmDate.tm_min = tTime.m_byMinute;
		tmDate.tm_sec = tTime.m_bySecond;
		
		g_timeDate = mktime(&tmDate);
		//防止time_t越界
		if ( g_timeDate < 0 )
		{
			g_timeDate = 0;
		}

		struct itimerval value, ovalue;
		memset( &value, 0, sizeof(value) );  
		//printf( "process id is %d\n", getpid() );
		signal( SIGALRM, sigroutine );
		value.it_value.tv_sec = 1;
		value.it_value.tv_usec = 0;
		value.it_interval.tv_sec = 1;
		value.it_interval.tv_usec = 0;
		int res = setitimer( ITIMER_REAL, &value, &ovalue );
		if ( res != 0 )
		{
			//printf("Set timer failed!!/n");
			PrtMsg( ev_UmsGetSysTime_Rsp, emEventTypeServerRecv, "set timer failed !" );
		}
	}
	else
	{
		PrtMsg( ev_UmsGetSysTime_Rsp, emEventTypeServerRecv, "server time is Invalid !" );
	}

	if ( PTR_SESSION->m_bRefresh )
	{
		PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_SetSysTime_res\",\"nYear\":\"%d\",\"nMonth\":\"%d\",\"nMDay\":\"%d\",\"nHour\":\"%d\",\"nMinute\":\"%d\",\"nSecond\":\"%d\"}",
			tTime.m_wYear, tTime.m_byMonth, tTime.m_byMDay, tTime.m_byHour, tTime.m_byMinute, tTime.m_bySecond);
		
		PrtMsg( ev_umcweb_SetSysTime_res, emEventTypeClientSend, "get server time: %d-%d-%d %d:%d:%d",
		tTime.m_wYear, tTime.m_byMonth, tTime.m_byMDay, tTime.m_byHour, tTime.m_byMinute, tTime.m_bySecond );
	}
	
	PTR_SESSION->m_bRefresh = FALSE;
}

u16 CUmcSysCfgCtrl::OnUmcwebGetSysTimeNtyReq(const boost::any& arg)
{
	PrtMsg( ev_umcweb_GetSysTime_nty_req, emEventTypeClientRecv, "req server time " );

    struct tm ptm = { 0 };  
    localtime_r(&g_timeDate, &ptm);  

	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_GetSysTime_nty_res\",\"nYear\":\"%d\",\"nMonth\":\"%d\",\"nMDay\":\"%d\",\"nHour\":\"%d\",\"nMinute\":\"%d\",\"nSecond\":\"%d\"}",
		ptm.tm_year+1900, ptm.tm_mon+1, ptm.tm_mday, ptm.tm_hour, ptm.tm_min, ptm.tm_sec );
	
	PrtMsg( ev_umcweb_GetSysTime_nty_res, emEventTypeClientSend, "get server time: %d-%d-%d %d:%d:%d",
		ptm.tm_year+1900, ptm.tm_mon+1, ptm.tm_mday, ptm.tm_hour, ptm.tm_min, ptm.tm_sec );

	return NO_ERROR;
}
/*
void CUmcSysCfgCtrl::OnNetMngNty( const CMessage& cMsg )
{
	CTpMsg kdvMsg( &cMsg );
	u16 wNum = *reinterpret_cast<u16*>( kdvMsg.GetBody() );

	m_vecTTPNMServerCfg.clear();

	for ( u16 n = 0; n < wNum; n++ )
	{
		TTPNMServerCfg tTPNMServerCfg = *reinterpret_cast<TTPNMServerCfg*>( kdvMsg.GetBody() + sizeof(u16) + n*sizeof(TTPNMServerCfg) );
		m_vecTTPNMServerCfg.push_back( tTPNMServerCfg );

		//test:
		in_addr tAddr;
    	tAddr.s_addr = ntohl(tTPNMServerCfg.dwNMServerIP);
		PrtMsg( ev_NMServer_nty, emEventTypeServerRecv, "bIsServerOn: %d, dwNMServerIP: %s, wNMGetSetPort: %d, WNMTrapPort: %d, achNMReadCommunity: %s, achNMWriteCommunity: %s, wNMServerNO: %d \n", 
			tTPNMServerCfg.bIsServerOn, inet_ntoa(tAddr), tTPNMServerCfg.wNMGetSetPort, tTPNMServerCfg.WNMTrapPort, tTPNMServerCfg.achNMReadCommunity, tTPNMServerCfg.achNMWriteCommunity, tTPNMServerCfg.wNMServerNO );
	}

	PrtMsg( ev_NMServer_nty, emEventTypeServerRecv, "ev_NMServer_nty" );
}

u16 CUmcSysCfgCtrl::NetMngAddReq( const TTPNMServerCfg& tTPNMServerCfg )
{
	CTpMsg *pcTpMsg = PTR_MSGDRIVER->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_NMServerAdd_req );
	pcTpMsg->SetBody( &tTPNMServerCfg, sizeof(TTPNMServerCfg) );
	
	in_addr tAddr;
    tAddr.s_addr = htonl(tTPNMServerCfg.dwNMServerIP);
    PrtMsg( ev_NMServerAdd_req, emEventTypeServerSend, "bIsServerOn: %d, dwNMServerIP: %s, wNMGetSetPort: %d, WNMTrapPort: %d, achNMReadCommunity: %s, achNMWriteCommunity: %s, wNMServerNO: %d ",
		tTPNMServerCfg.bIsServerOn, inet_ntoa(tAddr), tTPNMServerCfg.wNMGetSetPort, tTPNMServerCfg.WNMTrapPort, tTPNMServerCfg.achNMReadCommunity, tTPNMServerCfg.achNMWriteCommunity, tTPNMServerCfg.wNMServerNO );
	
	u16 wRet = PTR_MSGDRIVER->PostCommand(this, ev_NMServer_nty, TYPE_TPMSG);
	return wRet;
}

void CUmcSysCfgCtrl::OnAddNetMngRsp(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	EmModifyNMServerRet emRet = *reinterpret_cast<EmModifyNMServerRet*>( kdvMsg.GetBody() );
	
	if ( emRet == em_nmserver_modify_success )
	{
		TTPNMServerCfg tTPNMServerCfg = *reinterpret_cast<TTPNMServerCfg*>( kdvMsg.GetBody() + sizeof(EmModifyNMServerRet) );
		m_vecTTPNMServerCfg.push_back(tTPNMServerCfg);

		//test:
		in_addr tAddr;
		tAddr.s_addr = ntohl(tTPNMServerCfg.dwNMServerIP);
		PrtMsg( ev_NMServerAdd_rsp, emEventTypeServerRecv, "bIsServerOn: %d, dwNMServerIP: %s, wNMGetSetPort: %d, WNMTrapPort: %d, achNMReadCommunity: %s, achNMWriteCommunity: %s, wNMServerNO: %d \n",
			tTPNMServerCfg.bIsServerOn, inet_ntoa(tAddr), tTPNMServerCfg.wNMGetSetPort, tTPNMServerCfg.WNMTrapPort, tTPNMServerCfg.achNMReadCommunity, tTPNMServerCfg.achNMWriteCommunity, tTPNMServerCfg.wNMServerNO );
	}
	
	PrtMsg( ev_NMServerAdd_rsp, emEventTypeServerRecv, "netmng add is success =%d", emRet );
	NetMngInfoNty();
}

u16 CUmcSysCfgCtrl::NetMngModifyReq( const TTPNMServerCfg& tTPNMServerCfg )
{	
	CTpMsg *pcTpMsg = PTR_MSGDRIVER->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_NMServerMdy_req );
	pcTpMsg->SetBody( &tTPNMServerCfg, sizeof(TTPNMServerCfg) );
	
	in_addr tAddr;
    tAddr.s_addr = htonl(tTPNMServerCfg.dwNMServerIP);
    PrtMsg( ev_NMServerMdy_req, emEventTypeServerSend, "bIsServerOn: %d, dwNMServerIP: %s, wNMGetSetPort: %d, WNMTrapPort: %d, achNMReadCommunity: %s, achNMWriteCommunity: %s, wNMServerNO: %d ",
		tTPNMServerCfg.bIsServerOn, inet_ntoa(tAddr), tTPNMServerCfg.wNMGetSetPort, tTPNMServerCfg.WNMTrapPort, tTPNMServerCfg.achNMReadCommunity, tTPNMServerCfg.achNMWriteCommunity, tTPNMServerCfg.wNMServerNO );
	
	u16 wRet = PTR_MSGDRIVER->PostCommand(this, ev_NMServer_nty, TYPE_TPMSG);
	return wRet;
}

void  CUmcSysCfgCtrl::OnModifyNetMngRsp(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	EmModifyNMServerRet emRet = *reinterpret_cast<EmModifyNMServerRet*>( kdvMsg.GetBody() );
	
	if ( emRet == em_nmserver_modify_success )
	{
		TTPNMServerCfg tTPNMServerCfg = *reinterpret_cast<TTPNMServerCfg*>( kdvMsg.GetBody() + sizeof(EmModifyNMServerRet) );
		vector<TTPNMServerCfg>::iterator it;
		for ( it = m_vecTTPNMServerCfg.begin(); it != m_vecTTPNMServerCfg.end(); it++ )
		{
			if ( tTPNMServerCfg.wNMServerNO == it->wNMServerNO )
			{
				*it = tTPNMServerCfg;
				break;
			}
		}

		//test:
		in_addr tAddr;
		tAddr.s_addr = ntohl(tTPNMServerCfg.dwNMServerIP);
		PrtMsg( ev_NMServerMdy_rsp, emEventTypeServerRecv, "bIsServerOn: %d, dwNMServerIP: %s, wNMGetSetPort: %d, WNMTrapPort: %d, achNMReadCommunity: %s, achNMWriteCommunity: %s, wNMServerNO: %d \n",
			tTPNMServerCfg.bIsServerOn, inet_ntoa(tAddr), tTPNMServerCfg.wNMGetSetPort, tTPNMServerCfg.WNMTrapPort, tTPNMServerCfg.achNMReadCommunity, tTPNMServerCfg.achNMWriteCommunity, tTPNMServerCfg.wNMServerNO );
	}

	PrtMsg( ev_NMServerMdy_rsp, emEventTypeServerRecv, "netmng mdy is success =%d", emRet );
	NetMngInfoNty();
}

u16 CUmcSysCfgCtrl::NetMngDeleteReq( const TTPNMServerCfg& tTPNMServerCfg )
{	
	CTpMsg *pcTpMsg = PTR_MSGDRIVER->GetKdvMsgPtr(); 
	pcTpMsg->SetEvent( ev_NMServerDel_req );
	pcTpMsg->SetBody( &tTPNMServerCfg, sizeof(TTPNMServerCfg) );
	
	in_addr tAddr;
    tAddr.s_addr = htonl(tTPNMServerCfg.dwNMServerIP);
    PrtMsg( ev_NMServerDel_req, emEventTypeServerSend, "bIsServerOn: %d, dwNMServerIP: %s, wNMGetSetPort: %d, WNMTrapPort: %d, achNMReadCommunity: %s, achNMWriteCommunity: %s, wNMServerNO: %d ",
		tTPNMServerCfg.bIsServerOn, inet_ntoa(tAddr), tTPNMServerCfg.wNMGetSetPort, tTPNMServerCfg.WNMTrapPort, tTPNMServerCfg.achNMReadCommunity, tTPNMServerCfg.achNMWriteCommunity, tTPNMServerCfg.wNMServerNO );
	
	u16 wRet = PTR_MSGDRIVER->PostCommand(this, ev_NMServerDel_rsp, TYPE_TPMSG);
	return wRet;
}

void  CUmcSysCfgCtrl::OnDelNetMngRsp(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	EmModifyNMServerRet emRet = *reinterpret_cast<EmModifyNMServerRet*>( kdvMsg.GetBody() );
	
	if ( emRet == em_nmserver_modify_success )
	{
		TTPNMServerCfg tTPNMServerCfg = *reinterpret_cast<TTPNMServerCfg*>( kdvMsg.GetBody() + sizeof(EmModifyNMServerRet) );
		vector<TTPNMServerCfg>::iterator it;
		for ( it = m_vecTTPNMServerCfg.begin(); it != m_vecTTPNMServerCfg.end(); )
		{
			if ( tTPNMServerCfg.wNMServerNO == it->wNMServerNO )
			{
				it = m_vecTTPNMServerCfg.erase(it);
				break;
			}
			it++;
		}

		//test:
		in_addr tAddr;
		tAddr.s_addr = ntohl(tTPNMServerCfg.dwNMServerIP);
		PrtMsg( ev_NMServerDel_rsp, emEventTypeServerRecv, "bIsServerOn: %d, dwNMServerIP: %s, wNMGetSetPort: %d, WNMTrapPort: %d, achNMReadCommunity: %s, achNMWriteCommunity: %s, wNMServerNO: %d \n",
			tTPNMServerCfg.bIsServerOn, inet_ntoa(tAddr), tTPNMServerCfg.wNMGetSetPort, tTPNMServerCfg.WNMTrapPort, tTPNMServerCfg.achNMReadCommunity, tTPNMServerCfg.achNMWriteCommunity, tTPNMServerCfg.wNMServerNO );
	}

	PrtMsg( ev_NMServerDel_rsp, emEventTypeServerRecv, "netmng del is success =%d", emRet );
	NetMngInfoNty();
}

void CUmcSysCfgCtrl::NetMngInfoNty()
{
	TTPNMServerCfg tTPNMServerCfg1, tTPNMServerCfg2;
	vector<TTPNMServerCfg>::iterator it;
	for ( it = m_vecTTPNMServerCfg.begin(); it != m_vecTTPNMServerCfg.end(); it++ )
	{
		if ( 0 == it->wNMServerNO )
		{
			tTPNMServerCfg1 = *it;
		}
		else if ( 1 == it->wNMServerNO )
		{
			tTPNMServerCfg2 = *it;
		}
	}

	in_addr tAddr1, tAddr2;
	tAddr1.s_addr = htonl(tTPNMServerCfg1.dwNMServerIP);
	tAddr2.s_addr = htonl(tTPNMServerCfg2.dwNMServerIP);

	PrtMsg( ev_umcweb_NMServer_res, emEventTypeClientSend, 
				"bIsServerOn1: %d, dwNMServerIP1: %s, wNMGetSetPort1: %d, WNMTrapPort1: %d, achNMReadCommunity1: %s, achNMWriteCommunity1: %s, wNMServerNO1: %d, bIsServerOn2: %d, dwNMServerIP2: %s, wNMGetSetPort2: %d, WNMTrapPort2: %d, achNMReadCommunity2: %s, achNMWriteCommunity2: %s, wNMServerNO2: %d ",
		tTPNMServerCfg1.bIsServerOn, inet_ntoa(tAddr1), tTPNMServerCfg1.wNMGetSetPort, tTPNMServerCfg1.WNMTrapPort, 
		tTPNMServerCfg1.achNMReadCommunity, tTPNMServerCfg1.achNMWriteCommunity, tTPNMServerCfg1.wNMServerNO, 
		tTPNMServerCfg2.bIsServerOn, inet_ntoa(tAddr2), tTPNMServerCfg2.wNMGetSetPort, tTPNMServerCfg2.WNMTrapPort, 
		tTPNMServerCfg2.achNMReadCommunity, tTPNMServerCfg2.achNMWriteCommunity, tTPNMServerCfg2.wNMServerNO );

	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_NMServer_res\",\"IsServerOn1\":\"%d\",\"NMServerIP1\":\"%s\",\"NMGetSetPort1\":\"%d\",\"NMTrapPort1\":\"%d\",\"NMReadCommunity1\":\"%s\",\"NMWriteCommunity1\":\"%s\",\"NMServerNO1\":\"%d\",\"IsServerOn2\":\"%d\",\"NMServerIP2\":\"%s\",\"NMGetSetPort2\":\"%d\",\"NMTrapPort2\":\"%d\",\"NMReadCommunity2\":\"%s\",\"NMWriteCommunity2\":\"%s\",\"NMServerNO2\":\"%d\"}",
		tTPNMServerCfg1.bIsServerOn, inet_ntoa(tAddr1), tTPNMServerCfg1.wNMGetSetPort, tTPNMServerCfg1.WNMTrapPort, 
		tTPNMServerCfg1.achNMReadCommunity, tTPNMServerCfg1.achNMWriteCommunity, tTPNMServerCfg1.wNMServerNO,
		tTPNMServerCfg2.bIsServerOn, inet_ntoa(tAddr2), tTPNMServerCfg2.wNMGetSetPort, tTPNMServerCfg2.WNMTrapPort, 
		tTPNMServerCfg2.achNMReadCommunity, tTPNMServerCfg2.achNMWriteCommunity, tTPNMServerCfg2.wNMServerNO);
}

void CUmcSysCfgCtrl::NetMngInfoReq( vector<TTPNMServerCfg>& vecTTPNMServerCfg )
{	
	vector<TTPNMServerCfg>::iterator itNew = vecTTPNMServerCfg.begin();
	for ( ; itNew != vecTTPNMServerCfg.end(); itNew++ )
	{
		bool bFind = false;
		vector<TTPNMServerCfg>::iterator itOld = m_vecTTPNMServerCfg.begin();
		for ( ; itOld != m_vecTTPNMServerCfg.end(); itOld++ )
		{
			if ( itNew->wNMServerNO == itOld->wNMServerNO )
			{
				NetMngModifyReq( *itNew );
				bFind = true;
			}
		}
		if ( bFind == false )
		{
			NetMngAddReq( *itNew );
		}
	}
	
	vector<TTPNMServerCfg>::iterator itOld = m_vecTTPNMServerCfg.begin();
	for ( ; itOld != m_vecTTPNMServerCfg.end(); itOld++ )
	{
		bool bFind = false;
		vector<TTPNMServerCfg>::iterator itNew = vecTTPNMServerCfg.begin();
		for ( ; itNew != vecTTPNMServerCfg.end(); itNew++ )
		{
			if ( itOld->wNMServerNO == itNew->wNMServerNO )
			{
				bFind = true;
			}
		}
		if ( bFind == false )
		{
			NetMngDeleteReq( *itOld );
		}
	}
}

u16 CUmcSysCfgCtrl::OnUmcwebNMServerReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	ptree pte = COwsCommon::GetPropertyTree(strData);

	std::string strIsServerOn1 = COwsCommon::GetPropertyTreeVar( pte, "IsServerOn1" );
	std::string strServerIP1 = COwsCommon::GetPropertyTreeVar( pte, "NMServerIP1" );
	std::string strGetSetPort1 = COwsCommon::GetPropertyTreeVar( pte, "NMGetSetPort1" );
	std::string strTrapPort1 = COwsCommon::GetPropertyTreeVar( pte, "NMTrapPort1" );
	std::string strReadCommunity1 = COwsCommon::GetPropertyTreeVar( pte, "NMReadCommunity1" );
	std::string strWriteCommunity1 = COwsCommon::GetPropertyTreeVar( pte, "NMWriteCommunity1" );
	std::string strServerNO1 = COwsCommon::GetPropertyTreeVar( pte, "NMServerNO1" );

	std::string strIsServerOn2 = COwsCommon::GetPropertyTreeVar( pte, "IsServerOn2" );
	std::string strServerIP2 = COwsCommon::GetPropertyTreeVar( pte, "NMServerIP2" );
	std::string strGetSetPort2 = COwsCommon::GetPropertyTreeVar( pte, "NMGetSetPort2" );
	std::string strTrapPort2 = COwsCommon::GetPropertyTreeVar( pte, "NMTrapPort2" );
	std::string strReadCommunity2 = COwsCommon::GetPropertyTreeVar( pte, "NMReadCommunity2" );
	std::string strWriteCommunity2 = COwsCommon::GetPropertyTreeVar( pte, "NMWriteCommunity2" );
	std::string strServerNO2 = COwsCommon::GetPropertyTreeVar( pte, "NMServerNO2" );
	
	PrtMsg( ev_umcweb_NMServer_req, emEventTypeClientRecv, 
				"bIsServerOn1: %s, dwNMServerIP1: %s, wNMGetSetPort1: %s, WNMTrapPort1: %s, achNMReadCommunity1: %s, \
achNMWriteCommunity1: %s, wNMServerNO1: %s, bIsServerOn2: %s, dwNMServerIP2: %s, wNMGetSetPort2: %s, WNMTrapPort2: %s, \
achNMReadCommunity2: %s, achNMWriteCommunity2: %s, wNMServerNO2: %s ",
		strIsServerOn1.c_str(), strServerIP1.c_str(), strGetSetPort1.c_str(), strTrapPort1.c_str(), 
		strReadCommunity1.c_str(), strWriteCommunity1.c_str(), strServerNO1.c_str(), 
		strIsServerOn2.c_str(), strServerIP2.c_str(), strGetSetPort2.c_str(), strTrapPort2.c_str(), 
		strReadCommunity2.c_str(), strWriteCommunity2.c_str(), strServerNO2.c_str() );	

	//判断 增/删/改
	vector<TTPNMServerCfg> vecTTPNMServerCfg;
	vecTTPNMServerCfg.clear();

	//网管服务器1
	if ( !( strIsServerOn1.length() == 0 && strServerIP1.length() == 0 && strGetSetPort1.length() == 0 && strTrapPort1.length() == 0
		&& strReadCommunity1.length() == 0 && strWriteCommunity1.length() == 0 ) )
	{
		TTPNMServerCfg tTPNMServerCfg1;
		
		if ( strIsServerOn1 == "0" )
		{
			tTPNMServerCfg1.bIsServerOn = FALSE;
		}
		else
		{
			tTPNMServerCfg1.bIsServerOn = TRUE;
		}

		tTPNMServerCfg1.dwNMServerIP = ntohl(inet_addr(strServerIP1.c_str()));

		tTPNMServerCfg1.wNMGetSetPort = atoi( strGetSetPort1.c_str() );
		tTPNMServerCfg1.WNMTrapPort = atoi( strTrapPort1.c_str() );
		strncpy( tTPNMServerCfg1.achNMReadCommunity, strReadCommunity1.c_str(), MAX_COMMUNITY_LENGTH );
		strncpy( tTPNMServerCfg1.achNMWriteCommunity, strWriteCommunity1.c_str(), MAX_COMMUNITY_LENGTH );

		tTPNMServerCfg1.wNMServerNO = 0;

		vecTTPNMServerCfg.push_back( tTPNMServerCfg1 );
	}

	//网管服务器2
	if ( !( strIsServerOn2.length() == 0 && strServerIP2.length() == 0 && strGetSetPort2.length() == 0 && strTrapPort2.length() == 0
		&& strReadCommunity2.length() == 0 && strWriteCommunity2.length() == 0 ) )
	{
		TTPNMServerCfg tTPNMServerCfg2;
		
		if ( strIsServerOn2 == "0" )
		{
			tTPNMServerCfg2.bIsServerOn = FALSE;
		}
		else
		{
			tTPNMServerCfg2.bIsServerOn = TRUE;
		}

		tTPNMServerCfg2.dwNMServerIP = ntohl(inet_addr(strServerIP2.c_str()));

		tTPNMServerCfg2.wNMGetSetPort = atoi( strGetSetPort2.c_str() );
		tTPNMServerCfg2.WNMTrapPort = atoi( strTrapPort2.c_str() );
		strncpy( tTPNMServerCfg2.achNMReadCommunity, strReadCommunity2.c_str(), MAX_COMMUNITY_LENGTH );
		strncpy( tTPNMServerCfg2.achNMWriteCommunity, strWriteCommunity2.c_str(), MAX_COMMUNITY_LENGTH );

		tTPNMServerCfg2.wNMServerNO = 1;

		vecTTPNMServerCfg.push_back( tTPNMServerCfg2 );
	}

	NetMngInfoReq(vecTTPNMServerCfg);
	
	return NO_ERROR;
}

u16 CUmcSysCfgCtrl::OnUmcwebNMServerNtyReq(const boost::any& arg)
{
	PrtMsg( ev_umcweb_NMServer_nty_req, emEventTypeClientRecv, "req nmserver info " );
	
	TTPNMServerCfg tTPNMServerCfg1, tTPNMServerCfg2;
	vector<TTPNMServerCfg>::iterator it;
	for ( it = m_vecTTPNMServerCfg.begin(); it != m_vecTTPNMServerCfg.end(); it++ )
	{
		if ( 0 == it->wNMServerNO )
		{
			tTPNMServerCfg1 = *it;
		}
		else if ( 1 == it->wNMServerNO )
		{
			tTPNMServerCfg2 = *it;
		}
	}
	
	in_addr tAddr1, tAddr2;
	tAddr1.s_addr = htonl(tTPNMServerCfg1.dwNMServerIP);
	tAddr2.s_addr = htonl(tTPNMServerCfg2.dwNMServerIP);
	
	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_NMServer_nty_res\",\"IsServerOn1\":\"%d\",\"NMServerIP1\":\"%s\",\"NMGetSetPort1\":\"%d\",\"NMTrapPort1\":\"%d\",\"NMReadCommunity1\":\"%s\",\"NMWriteCommunity1\":\"%s\",\"NMServerNO1\":\"%d\",\"IsServerOn2\":\"%d\",\"NMServerIP2\":\"%s\",\"NMGetSetPort2\":\"%d\",\"NMTrapPort2\":\"%d\",\"NMReadCommunity2\":\"%s\",\"NMWriteCommunity2\":\"%s\",\"NMServerNO2\":\"%d\"}",
		tTPNMServerCfg1.bIsServerOn, inet_ntoa(tAddr1), tTPNMServerCfg1.wNMGetSetPort, tTPNMServerCfg1.WNMTrapPort, 
		tTPNMServerCfg1.achNMReadCommunity, tTPNMServerCfg1.achNMWriteCommunity, tTPNMServerCfg1.wNMServerNO,
		tTPNMServerCfg2.bIsServerOn, inet_ntoa(tAddr2), tTPNMServerCfg2.wNMGetSetPort, tTPNMServerCfg2.WNMTrapPort, 
		tTPNMServerCfg2.achNMReadCommunity, tTPNMServerCfg2.achNMWriteCommunity, tTPNMServerCfg2.wNMServerNO);
	
	PrtMsg( ev_umcweb_NMServer_nty_res, emEventTypeClientSend, 
				"bIsServerOn1: %d, dwNMServerIP1: %s, wNMGetSetPort1: %d, WNMTrapPort1: %d, \
achNMReadCommunity1: %s, achNMWriteCommunity1: %s, wNMServerNO1: %d, bIsServerOn2: %d, \
dwNMServerIP2: %s, wNMGetSetPort2: %d, WNMTrapPort2: %d, achNMReadCommunity2: %s, achNMWriteCommunity2: %s, wNMServerNO2: %d ",
		tTPNMServerCfg1.bIsServerOn, inet_ntoa(tAddr1), tTPNMServerCfg1.wNMGetSetPort, tTPNMServerCfg1.WNMTrapPort, 
		tTPNMServerCfg1.achNMReadCommunity, tTPNMServerCfg1.achNMWriteCommunity, tTPNMServerCfg1.wNMServerNO, 
		tTPNMServerCfg2.bIsServerOn, inet_ntoa(tAddr2), tTPNMServerCfg2.wNMGetSetPort, tTPNMServerCfg2.WNMTrapPort, 
		tTPNMServerCfg2.achNMReadCommunity, tTPNMServerCfg2.achNMWriteCommunity, tTPNMServerCfg2.wNMServerNO );
	
	return NO_ERROR;
}
*/