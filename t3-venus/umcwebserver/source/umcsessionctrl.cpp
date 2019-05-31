#include "umcglodef.h"
#include "umcsessionctrl.h"

#define SERVER_IP_ADDR "172.16.216.2"

CUmcSessionCtrl::CUmcSessionCtrl()
:m_pAddrbookCtrl(NULL)
,m_pConfinfoCtrl(NULL)
,m_pSysCfgCtrl(NULL)
,m_pConfTemplateCtrl(NULL)
{
	MappingEventName();

	// 构造事件映射表
    BuildEventsMap(); 

	ClearData();

  	u16 wRet = InitializeLib( AID_UMS2UMC_APP, AID_UMC2UMS_APP );
 	assert(wRet == NO_ERROR);
 
	PTR_MSGDRIVER->RegHandler(this);

	//在该类中，new出所有的功能类，外部通过接口GetInterface()获取
#define NEW_REG(pCtrl, clsName)         \
	pCtrl = new clsName();     \
    PTR_MSGDRIVER->RegHandler(pCtrl);
	
	NEW_REG(m_pAddrbookCtrl,CUmcAddrbookCtrl);
	NEW_REG(m_pConfinfoCtrl,CUmcConfinfoCtrl);
	NEW_REG(m_pSysCfgCtrl,CUmcSysCfgCtrl);
	NEW_REG(m_pConfTemplateCtrl,CUmcConfTemplateCtrl);
	

#undef NEW_REG
}

CUmcSessionCtrl::~CUmcSessionCtrl()
{
    g_MsgRecApp.SetNodeId(INVALID_NODE);
    g_MsgRecApp.ClearOspMsg();

	ClearData();

	PTR_MSGDRIVER->UnregHandler(m_pAddrbookCtrl);
	SAFE_RELEASE(m_pAddrbookCtrl);

	PTR_MSGDRIVER->UnregHandler(m_pConfinfoCtrl);
	SAFE_RELEASE(m_pConfinfoCtrl);

	PTR_MSGDRIVER->UnregHandler(m_pSysCfgCtrl);
	SAFE_RELEASE(m_pSysCfgCtrl);

	PTR_MSGDRIVER->UnregHandler(m_pConfTemplateCtrl);
	SAFE_RELEASE(m_pConfTemplateCtrl);

	OspQuit();
}

void CUmcSessionCtrl::ClearData()
{
	g_MsgRecApp.SetNodeId(INVALID_NODE);
	m_bLogin = FALSE;
	m_bRefresh = FALSE;
}

BOOL CUmcSessionCtrl::IsConnected()
{   
	return g_MsgRecApp.GetNodeId() != INVALID_NODE;
} 

u16 CUmcSessionCtrl::InitializeLib( u16 wAppID, u16 wDesAppID )
{
    // 初始化OSP
    const u32 dwTelnetPort = 0;
	u16 nRe = NO_ERROR;
    if(!IsOspInitd())
    {  
        BOOL bTelnet  = FALSE ;
#ifdef _DEBUG
        bTelnet = TRUE;
#endif
        if(!OspInit( bTelnet , dwTelnetPort ) )
        {
			FLogPrt("osp init fails!");
            return RET_FAILS;
        }

 		OspSetPrompt(TELNET_PROMPT);
    }
	
	
	char szOspApp[] = "MsgRecApp";
	const u32 dwPrior = 80;
	int nRet = g_MsgRecApp.CreateApp( &szOspApp[0], wAppID, dwPrior, 300, 200 );
	if ( OSP_OK != nRet)
	{
		nRe = RET_FAILS;
		FLogPrt("create app fails!");
	}
	else
	{
		PTR_MSGDRIVER->SetAppID(wAppID);			//设置源APP ID
		PTR_MSGDRIVER->SetDesAppID(wDesAppID);		//设置服务器目的端APP ID
	}

    return nRe;
}

void CUmcSessionCtrl::BuildEventsMap()
{
	REG_PFUN( ev_UMSLoginRet, &CUmcSessionCtrl::OnConnectUmsRsp );
	REG_PFUN( OSP_DISCONNECT, &CUmcSessionCtrl::OnLinkBreak ); 

	BuildReqEventsMap();
}

void CUmcSessionCtrl::BuildReqEventsMap()
{
	REG_REQ_PFUN( ev_umcweb_login_req, &CUmcSessionCtrl::OnConnectUmsReq );
}

void CUmcSessionCtrl::DispEvent(const CMessage &cMsg)
{
    DISP_FUN( CUmcSessionCtrl, cMsg );
}

void CUmcSessionCtrl::DispReqEvent( u16 wEvent, const boost::any& arg )
{
    DISP_REQ_FUN( CUmcSessionCtrl, wEvent, arg );
}

void CUmcSessionCtrl::OnLinkBreak( const CMessage& cMsg )
{
	ClearData();

	PrtMsg( OSP_DISCONNECT, emEventTypeServerRecv,"CUmcSessionCtrl::OnLinkBreak"); 
}

u16 CUmcSessionCtrl::OnConnectUmsReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pte = COwsCommon::GetPropertyTree(strData);
	std::string strUserName = COwsCommon::GetPropertyTreeVar( pte, PRO_ET_USR );
	std::string strUserPwd = COwsCommon::GetPropertyTreeVar( pte, PRO_ET_PSW );
	
	PrtMsg( ev_umcweb_login_req, emEventTypeClientRecv,"UserName:%s,UserPwd:%s",strUserName.c_str(),strUserPwd.c_str());
	
	if ( !IsConnected() )
	{
		if ( NO_ERROR != ConnectToUms( strUserName, strUserPwd ) )
		{
			//如果连接失败   则直接反馈给用户   系统服务器未初始化    否则就收服务器的回应
			PTR_FCGIPRINTF("{\"event\":\"ev_umcweb_login_res\",\"EmTpLoginUmsRet\":\"%d\"}", tp_LoginUms_SysIniting );
			PrtMsg( ev_umcweb_login_res, emEventTypeClientSend,"EmTpLoginUmsRet:%d",tp_LoginUms_SysIniting );
		}
	}
	else
	{
		//shishi
		PTR_FCGIPRINTF("{\"event\":\"ev_umcweb_login_res\",\"EmTpLoginUmsRet\":\"%d\"}", tp_LoginUms_sucess );
		PrtMsg( ev_umcweb_login_res, emEventTypeClientSend,"EmTpLoginUmsRet:%d",tp_LoginUms_sucess );
	}
	
	return NO_ERROR;
}

u16 CUmcSessionCtrl::ConnectToUms( string strUsr, string strPwd )
{
	//构建数据
	u32 dwIP = htonl(inet_addr(SERVER_IP_ADDR));
	u16 dwPort = UMS_LISTEN_PORT;		 //服务器监听端口
	
	// 建立TCP连接
    if( IsConnected() )
    {   
		DisConnect();
    }
    
    ClearDisp();
	
    // 重构消息分发表
    BuildEventsMap();
    
    //建立Osp的TCP连接,得到本地机器的IP地址
	u32 dwDceNodeId = OspConnectTcpNode( inet_addr(SERVER_IP_ADDR), static_cast<u16>(dwPort), 5, 3, 5000 );    
	
	if( dwDceNodeId == INVALID_NODE )
	{
		PrtMsg( "创建TCP失败，端口号：%d\n", dwDceNodeId );
		
		FLogPrt( "connect to server node fails!" );
		
		return RET_FAILS;
	}
	else
	{
		FLogPrt( "connect to server node success!" );
	}
	
	g_MsgRecApp.SetNodeId( dwDceNodeId );
	
    //设置在node连接中断时需通知的appid和InstId
    ::OspNodeDiscCBReg( dwDceNodeId, PTR_MSGDRIVER->GetAppID(), 1 ); 
	
	//发送登录请求
	//登录ums ，验证用户
	CLoginRequest cUser;
	cUser.SetName( (char*)strUsr.c_str() );
	cUser.SetPassword( (char*)strPwd.c_str() );
	
	CMessage* pCMsg = PTR_MSGDRIVER->GetCMsgPtr();
	pCMsg->event = ev_UMSLoginReq;
	pCMsg->content =  (u8*)&cUser;
	pCMsg->length = sizeof(CLoginRequest);
	
	in_addr tAddr;
	tAddr.s_addr = ntohl(dwIP);  
    PrtMsg( ev_UMSLoginReq, emEventTypeServerSend, "ip:%s, usrName:%s, pwd:%s", inet_ntoa(tAddr), strUsr.c_str(), strPwd.c_str() );
	
	PTR_MSGDRIVER->PostCommand(this, ev_UMSLoginRet);
	
	return NO_ERROR;
}

void CUmcSessionCtrl::OnConnectUmsRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg( &cMsg );
	TLoginRet ret = *reinterpret_cast<TLoginRet *>(kdvMsg.GetBody());

	if ( ret.m_emRet == tp_LoginUms_sucess )
	{
		m_bLogin = TRUE;
	}

	PrtMsg( ev_UMSLoginRet, emEventTypeServerRecv
		,"m_dwUserID=%d,errorCode: %d ( %d:sucess, %d:NameError, %d:PwdError, %d: MaxLogin, %d: Logged )"
		,ret.m_dwUserID,ret.m_emRet
		,tp_LoginUms_sucess,tp_LoginUms_NameError,tp_LoginUms_PwdError,tp_LoginUms_MaxLogin,tp_LoginUms_Logged );

	PTR_FCGIPRINTF("{\"event\":\"ev_umcweb_login_res\",\"EmTpLoginUmsRet\":\"%d\"}", ret.m_emRet );

	PrtMsg( ev_umcweb_login_res, emEventTypeClientSend, "EmTpLoginUmsRet:%d", ret.m_emRet );
	FLogPrt( "connect to server: EmTpLoginUmsRet=%d", ret.m_emRet );
}

u16 CUmcSessionCtrl::OnLinkBreakReq(const boost::any& arg)
{
// 	PrtMsg( ev_dcweb_OSP_DISCONNECT_nty_req, emEventTypeDccRecv, "" );
// 
// 	PTR_FCGIPRINTF("{\"event\":\"ev_dcweb_OSP_DISCONNECT_nty_rsp\",\"bLogin\":\"%d\"}", m_bLogin );
// 
// 	PrtMsg( ev_dcweb_OSP_DISCONNECT_nty_rsp, emEventTypeDccSend, "bLogin:%d", m_bLogin );

	return NO_ERROR;
}

u16 CUmcSessionCtrl::DisConnect()
{
	if ( !IsConnected() )
	{
		return NO_ERROR;
	}

	BOOL32 re = OspDisconnectTcpNode( g_MsgRecApp.GetNodeId() );

    g_MsgRecApp.SetNodeId(INVALID_NODE);
	
	return (u16)re;
}

void CUmcSessionCtrl::MappingEventName()
{   
	////////////////////////////登陆///////////////////////////////////////
	COwsCommon::MappingHelper( ev_umcweb_login_req, "ev_umcweb_login_req" );
	COwsCommon::MappingHelper( ev_umcweb_login_res, "ev_umcweb_login_res" );

	COwsCommon::MappingHelper( ev_UMSLoginReq, "ev_UMSLoginReq" );
    COwsCommon::MappingHelper( ev_UMSLoginRet, "ev_UMSLoginRet" );
    COwsCommon::MappingHelper( OSP_DISCONNECT, "OSP_DISCONNECT" );	

	////////////////////////////全局地址簿///////////////////////////////////////
	COwsCommon::MappingHelper( ev_umcweb_addrbook_globle_get_req, "ev_umcweb_addrbook_globle_get_req" );
	COwsCommon::MappingHelper( ev_umcweb_addrbook_globle_get_res, "ev_umcweb_addrbook_globle_get_res" );
	COwsCommon::MappingHelper( ev_umcweb_addrbook_globle_refresh_req, "ev_umcweb_addrbook_globle_refresh_req" );
	COwsCommon::MappingHelper( ev_umcweb_addrbook_globle_refresh_res, "ev_umcweb_addrbook_globle_refresh_res" );

	COwsCommon::MappingHelper( ev_umsGetRegInfo_Req, "ev_umsGetRegInfo_Req" );
	COwsCommon::MappingHelper( ev_umsGetRegInfo_UmsRspEx, "ev_umsGetRegInfo_UmsRspEx" );
	COwsCommon::MappingHelper( ev_umsGetRegInfo_CnsRspEx, "ev_umsGetRegInfo_CnsRspEx" );
	COwsCommon::MappingHelper( ev_umsGetRegInfo_MtRspEx, "ev_umsGetRegInfo_MtRspEx" );
	COwsCommon::MappingHelper( ev_umsGetRegInfo_McuRspEx, "ev_umsGetRegInfo_McuRspEx" );

	////////////////////////////本地地址簿///////////////////////////////////////
	COwsCommon::MappingHelper( ev_umcweb_addrbook_itemgroup_get_req, "ev_umcweb_addrbook_itemgroup_get_req" );
	COwsCommon::MappingHelper( ev_umcweb_addrbook_itemgroup_get_res, "ev_umcweb_addrbook_itemgroup_get_res" );

	COwsCommon::MappingHelper( ev_umcweb_addrbook_itemgroup_search_req, "ev_umcweb_addrbook_itemgroup_search_req" );
	COwsCommon::MappingHelper( ev_umcweb_addrbook_itemgroup_search_res, "ev_umcweb_addrbook_itemgroup_search_res" );

	COwsCommon::MappingHelper( ev_umcweb_addrbook_item_add_req, "ev_umcweb_addrbook_item_add_req" );
	COwsCommon::MappingHelper( ev_umcweb_addrbook_item_add_res, "ev_umcweb_addrbook_item_add_res" );

	COwsCommon::MappingHelper( ev_umcweb_addrbook_item_mod_req, "ev_umcweb_addrbook_item_mod_req" );
	COwsCommon::MappingHelper( ev_umcweb_addrbook_item_mod_res, "ev_umcweb_addrbook_item_mod_res" );

	COwsCommon::MappingHelper( ev_umcweb_addrbook_item_del_req, "ev_umcweb_addrbook_item_del_req" );
	COwsCommon::MappingHelper( ev_umcweb_addrbook_item_del_res, "ev_umcweb_addrbook_item_del_res" );

	COwsCommon::MappingHelper( ev_umcweb_addrbook_item_get_req, "ev_umcweb_addrbook_item_get_req" );
	COwsCommon::MappingHelper( ev_umcweb_addrbook_item_get_res, "ev_umcweb_addrbook_item_get_res" );

	COwsCommon::MappingHelper( ev_umcweb_addrbook_item_number_req, "ev_umcweb_addrbook_item_number_req" );
	COwsCommon::MappingHelper( ev_umcweb_addrbook_item_number_res, "ev_umcweb_addrbook_item_number_res" );

	COwsCommon::MappingHelper( ev_umcweb_addrbook_group_get_req, "ev_umcweb_addrbook_group_get_req" );
	COwsCommon::MappingHelper( ev_umcweb_addrbook_group_get_res, "ev_umcweb_addrbook_group_get_res" );

	COwsCommon::MappingHelper( ev_umcweb_addrbook_group_add_req, "ev_umcweb_addrbook_group_add_req" );
	COwsCommon::MappingHelper( ev_umcweb_addrbook_group_add_res, "ev_umcweb_addrbook_group_add_res" );

	COwsCommon::MappingHelper( ev_umcweb_addrbook_group_mod_req, "ev_umcweb_addrbook_group_mod_req" );
	COwsCommon::MappingHelper( ev_umcweb_addrbook_group_mod_res, "ev_umcweb_addrbook_group_mod_res" );

	COwsCommon::MappingHelper( ev_umcweb_addrbook_group_del_req, "ev_umcweb_addrbook_group_del_req" );
	COwsCommon::MappingHelper( ev_umcweb_addrbook_group_del_res, "ev_umcweb_addrbook_group_del_res" );

	COwsCommon::MappingHelper( ev_umcweb_addrbook_ig_add_req, "ev_umcweb_addrbook_ig_add_req" );
	COwsCommon::MappingHelper( ev_umcweb_addrbook_ig_add_res, "ev_umcweb_addrbook_ig_add_res" );

	COwsCommon::MappingHelper( ev_umcweb_addrbook_ig_del_req, "ev_umcweb_addrbook_ig_del_req" );
	COwsCommon::MappingHelper( ev_umcweb_addrbook_ig_del_res, "ev_umcweb_addrbook_ig_del_res" );

	COwsCommon::MappingHelper( ev_umcweb_addrbook_gg_add_req, "ev_umcweb_addrbook_gg_add_req" );
	COwsCommon::MappingHelper( ev_umcweb_addrbook_gg_add_res, "ev_umcweb_addrbook_gg_add_res" );
	
	COwsCommon::MappingHelper( ev_umcweb_addrbook_gg_del_req, "ev_umcweb_addrbook_gg_del_req" );
	COwsCommon::MappingHelper( ev_umcweb_addrbook_gg_del_res, "ev_umcweb_addrbook_gg_del_res" );

	////////////////////////////会议管理///////////////////////////////////////
	COwsCommon::MappingHelper( evtp_HungUpConf_cmd, "evtp_HungUpConf_cmd" );
	COwsCommon::MappingHelper( evtp_HungUpConf_result, "evtp_HungUpConf_result" );
	COwsCommon::MappingHelper( evtp_AddConfList_Notify, "evtp_AddConfList_Notify" );
	COwsCommon::MappingHelper( evtp_DelConflist_Notify, "evtp_DelConflist_Notify" );
	COwsCommon::MappingHelper( evtp_UpdateConfCnsList_Notify, "evtp_UpdateConfCnsList_Notify" );

	COwsCommon::MappingHelper( evtp_UpdateConfTurnlist_Notify, "evtp_UpdateConfTurnlist_Notify" );
	COwsCommon::MappingHelper( evtp_UpdateTurn_cmd, "evtp_UpdateTurn_cmd" );
	COwsCommon::MappingHelper( evtp_UpdateTurn_ind, "evtp_UpdateTurn_ind" );
	COwsCommon::MappingHelper( evtp_StartTurn_cmd, "evtp_StartTurn_cmd" );
	COwsCommon::MappingHelper( evtp_StartTurn_ind, "evtp_StartTurn_ind" );
	COwsCommon::MappingHelper( evtp_StopTurn_cmd, "evtp_StopTurn_cmd" );
	COwsCommon::MappingHelper( evtp_StopTurn_ind, "evtp_StopTurn_ind" );
	COwsCommon::MappingHelper( evtp_SuspendTurn_cmd, "evtp_SuspendTurn_cmd" );
	COwsCommon::MappingHelper( evtp_SuspendTurn_ind, "evtp_SuspendTurn_ind" );
	COwsCommon::MappingHelper( evtp_TurnStat_ntfy, "evtp_TurnStat_ntfy" );

	COwsCommon::MappingHelper( evtp_AuxMixInfo_Notify, "evtp_AuxMixInfo_Notify" );
	COwsCommon::MappingHelper( evtp_UpdateAudMixInfo_cmd, "evtp_UpdateAudMixInfo_cmd" );
	COwsCommon::MappingHelper( evtp_UpdateAudMixInfo_Ind, "evtp_UpdateAudMixInfo_Ind" );
	COwsCommon::MappingHelper( evtp_StartAuxMix_cmd, "evtp_StartAuxMix_cmd" );
	COwsCommon::MappingHelper( evtp_StartAuxMix_ind, "evtp_StartAuxMix_ind" );
	COwsCommon::MappingHelper( ev_AuxMixVacSwitch, "ev_AuxMixVacSwitch" );
	COwsCommon::MappingHelper( ev_AuxMixVacSwitchInd, "ev_AuxMixVacSwitchInd" );
	
	COwsCommon::MappingHelper( ev_umcweb_confmng_listconf_get_req, "ev_umcweb_confmng_listconf_get_req" );
	COwsCommon::MappingHelper( ev_umcweb_confmng_listconf_get_res, "ev_umcweb_confmng_listconf_get_res" );

	COwsCommon::MappingHelper( ev_umcweb_hangupconf_req, "ev_umcweb_hangupconf_req" );
	COwsCommon::MappingHelper( ev_umcweb_hangupconf_res, "ev_umcweb_hangupconf_res" );

	COwsCommon::MappingHelper( ev_umcweb_RefreshConfinfoInfo_nty_req, "ev_umcweb_RefreshConfinfoInfo_nty_req" );
	COwsCommon::MappingHelper( ev_umcweb_RefreshConfinfoInfo_nty_res, "ev_umcweb_RefreshConfinfoInfo_nty_res" );
	COwsCommon::MappingHelper( ev_umcweb_RefreshConfinfo_PollingList_nty_req, "ev_umcweb_RefreshConfinfo_PollingList_nty_req" );
	COwsCommon::MappingHelper( ev_umcweb_RefreshConfinfo_PollingList_nty_res, "ev_umcweb_RefreshConfinfo_PollingList_nty_res" );
	COwsCommon::MappingHelper( ev_umcweb_RefreshConfinfo_DiscussList_nty_req, "ev_umcweb_RefreshConfinfo_DiscussList_nty_req" );
	COwsCommon::MappingHelper( ev_umcweb_RefreshConfinfo_DiscussList_nty_res, "ev_umcweb_RefreshConfinfo_DiscussList_nty_res" );

	COwsCommon::MappingHelper( ev_umcweb_SuspendTurn_req, "ev_umcweb_SuspendTurn_req" );
	COwsCommon::MappingHelper( ev_umcweb_SuspendTurn_res, "ev_umcweb_SuspendTurn_res" );
	COwsCommon::MappingHelper( ev_umcweb_StartTurn_req, "ev_umcweb_StartTurn_req" );
	COwsCommon::MappingHelper( ev_umcweb_StartTurn_res, "ev_umcweb_StartTurn_res" );
	COwsCommon::MappingHelper( ev_umcweb_UpdateTurn_req, "ev_umcweb_UpdateTurn_req" );

	COwsCommon::MappingHelper( ev_umcweb_AuxMixVacSwitch_req, "ev_umcweb_AuxMixVacSwitch_req" );
	COwsCommon::MappingHelper( ev_umcweb_AuxMixVacSwitch_res, "ev_umcweb_AuxMixVacSwitch_res" );
	COwsCommon::MappingHelper( ev_umcweb_UpdateAudMixInfo_req, "ev_umcweb_UpdateAudMixInfo_req" );
//	COwsCommon::MappingHelper( ev_umcweb_UpdateAudMixInfo_res, "ev_umcweb_UpdateAudMixInfo_res" );
	COwsCommon::MappingHelper( ev_umcweb_StartAuxMix_req, "ev_umcweb_StartAuxMix_req" );
//	COwsCommon::MappingHelper( ev_umcweb_StartAuxMix_res, "ev_umcweb_StartAuxMix_res" );

	////////////////////////////系统配置///////////////////////////////////////
	COwsCommon::MappingHelper( ev_UmsAddUser_Notify, "ev_UmsAddUser_Notify" );
	COwsCommon::MappingHelper( ev_UmsUpdateUser_Notify, "ev_UmsUpdateUser_Notify" );
	COwsCommon::MappingHelper( ev_UmsDelUser_Notify, "ev_UmsDelUser_Notify" );
	COwsCommon::MappingHelper( ev_UMSAddUserRet, "ev_UMSAddUserRet" );
	COwsCommon::MappingHelper( ev_UMSChangePWDRet, "ev_UMSChangePWDRet" );
	COwsCommon::MappingHelper( ev_UMSDelUserRet, "ev_UMSDelUserRet" );
	COwsCommon::MappingHelper( ev_UMSAddUserReq, "ev_UMSAddUserReq" );
	COwsCommon::MappingHelper( ev_UMSChangePWDReq, "ev_UMSChangePWDReq" );
	COwsCommon::MappingHelper( ev_UMSDelUserReq, "ev_UMSDelUserReq" );
	COwsCommon::MappingHelper( ev_umcweb_AddUser_req, "ev_umcweb_AddUser_req" );
	COwsCommon::MappingHelper( ev_umcweb_AddUser_res, "ev_umcweb_AddUser_res" );
	COwsCommon::MappingHelper( ev_umcweb_ChangePwd_req, "ev_umcweb_ChangePwd_req" );
	COwsCommon::MappingHelper( ev_umcweb_ChangePwd_res, "ev_umcweb_ChangePwd_res" );
	COwsCommon::MappingHelper( ev_umcweb_DelUser_req, "ev_umcweb_DelUser_req" );
	COwsCommon::MappingHelper( ev_umcweb_DelUser_res, "ev_umcweb_DelUser_res" );
	COwsCommon::MappingHelper( ev_umcweb_User_nty_req, "ev_umcweb_User_nty_req" );
	COwsCommon::MappingHelper( ev_umcweb_User_nty_res, "ev_umcweb_User_nty_res" );
	

 	COwsCommon::MappingHelper( ev_UmsIPCfg, "ev_UmsIPCfg" );
 	COwsCommon::MappingHelper( ev_UmsIPCfg_Ind, "ev_UmsIPCfg_Ind" );
	COwsCommon::MappingHelper( ev_umcweb_IpCfg_req, "ev_umcweb_IpCfg_req" );
	COwsCommon::MappingHelper( ev_umcweb_IpCfg_res, "ev_umcweb_IpCfg_res" );
 	COwsCommon::MappingHelper( ev_umcweb_IpCfg_nty_req, "ev_umcweb_IpCfg_nty_req" );
 	COwsCommon::MappingHelper( ev_umcweb_IpCfg_nty_res, "ev_umcweb_IpCfg_nty_res" );
	COwsCommon::MappingHelper( ev_umsreg_cmd, "ev_umsreg_cmd" );
 	COwsCommon::MappingHelper( ev_umsreg_notify, "ev_umsreg_notify" );
	COwsCommon::MappingHelper( ev_umcweb_sipserver_req, "ev_umcweb_sipserver_req" );
	COwsCommon::MappingHelper( ev_umcweb_sipserver_res, "ev_umcweb_sipserver_res" );
	COwsCommon::MappingHelper( ev_umcweb_sipserver_nty_req, "ev_umcweb_sipserver_nty_req" );
	COwsCommon::MappingHelper( ev_umcweb_sipserver_nty_res, "ev_umcweb_sipserver_nty_res" );
	COwsCommon::MappingHelper( ev_umsGKReg_cmd, "ev_umsGKReg_cmd" );
 	COwsCommon::MappingHelper( ev_umsGKReg_notify, "ev_umsGKReg_notify" );
	COwsCommon::MappingHelper( ev_umcweb_gkserver_req, "ev_umcweb_gkserver_req" );
 	COwsCommon::MappingHelper( ev_umcweb_gkserver_res, "ev_umcweb_gkserver_res" );
	COwsCommon::MappingHelper( ev_umcweb_gkserver_nty_req, "ev_umcweb_gkserver_nty_req" );
 	COwsCommon::MappingHelper( ev_umcweb_gkserver_nty_res, "ev_umcweb_gkserver_nty_res" );

	COwsCommon::MappingHelper( ev_umcweb_SetSysTime_req, "ev_umcweb_SetSysTime_req" );
	COwsCommon::MappingHelper( ev_umcweb_SetSysTime_res, "ev_umcweb_SetSysTime_res" );
	COwsCommon::MappingHelper( ev_umcweb_GetSysTime_nty_req, "ev_umcweb_GetSysTime_nty_req" );
	COwsCommon::MappingHelper( ev_umcweb_GetSysTime_nty_res, "ev_umcweb_GetSysTime_nty_res" );
	COwsCommon::MappingHelper( ev_UmsSetSysTime_Cmd, "ev_UmsSetSysTime_Cmd" );
	COwsCommon::MappingHelper( ev_UmsGetSysTime_Rsp, "ev_UmsGetSysTime_Rsp" );
/*
	COwsCommon::MappingHelper( ev_umcweb_NMServer_req, "ev_umcweb_NMServer_req" );
	COwsCommon::MappingHelper( ev_umcweb_NMServer_res, "ev_umcweb_NMServer_res" );
	COwsCommon::MappingHelper( ev_umcweb_NMServer_nty_req, "ev_umcweb_NMServer_nty_req" );
	COwsCommon::MappingHelper( ev_umcweb_NMServer_nty_res, "ev_umcweb_NMServer_nty_res" );
	COwsCommon::MappingHelper( ev_NMServer_nty, "ev_NMServer_nty" );
	COwsCommon::MappingHelper( ev_NMServerAdd_req, "ev_NMServerAdd_req" );
	COwsCommon::MappingHelper( ev_NMServerAdd_rsp, "ev_NMServerAdd_rsp" );
	COwsCommon::MappingHelper( ev_NMServerMdy_req, "ev_NMServerMdy_req" );
	COwsCommon::MappingHelper( ev_NMServerMdy_rsp, "ev_NMServerMdy_rsp" );
	COwsCommon::MappingHelper( ev_NMServerDel_req, "ev_NMServerDel_req" );
	COwsCommon::MappingHelper( ev_NMServerDel_rsp, "ev_NMServerDel_rsp" );
*/
	////////////////////////////会议模板///////////////////////////////////////
	COwsCommon::MappingHelper( ev_umcweb_OperatorConfTemplate_res, "ev_umcweb_OperatorConfTemplate_res" );
	COwsCommon::MappingHelper( ev_umcweb_AddConftemplate_req, "ev_umcweb_AddConftemplate_req" );
	COwsCommon::MappingHelper( ev_umcweb_UpdateConftemplate_req, "ev_umcweb_UpdateConftemplate_req" );
	COwsCommon::MappingHelper( ev_umcweb_DelConftemplate_req, "ev_umcweb_DelConftemplate_req" );
	COwsCommon::MappingHelper( ev_umcweb_RefreshConfTempResult_res, "ev_umcweb_RefreshConfTempResult_res" );
	COwsCommon::MappingHelper( ev_umcweb_DelAllConftemp_req, "ev_umcweb_DelAllConftemp_req" );
	COwsCommon::MappingHelper( ev_umcweb_DelAllConftemp_res, "ev_umcweb_DelAllConftemp_res" );
	COwsCommon::MappingHelper( ev_umcweb_StartConfTemplate_req, "ev_umcweb_StartConfTemplate_req" );
	COwsCommon::MappingHelper( ev_umcweb_StartConfTemplate_res, "ev_umcweb_StartConfTemplate_res" );
	COwsCommon::MappingHelper( ev_umcweb_RefreshConftempList_nty_req, "ev_umcweb_RefreshConftempList_nty_req" );
	COwsCommon::MappingHelper( ev_umcweb_RefreshConftempList_nty_res, "ev_umcweb_RefreshConftempList_nty_res" );
	COwsCommon::MappingHelper( ev_umcweb_RefreshConftempInfo_nty_req, "ev_umcweb_RefreshConftempInfo_nty_req" );
	COwsCommon::MappingHelper( ev_umcweb_RefreshConftempInfo_nty_res, "ev_umcweb_RefreshConftempInfo_nty_res" );
	COwsCommon::MappingHelper( ev_umcweb_RefreshConftemp_MeetNameList_nty_req, "ev_umcweb_RefreshConftemp_MeetNameList_nty_req" );
	COwsCommon::MappingHelper( ev_umcweb_RefreshConftemp_MeetNameList_nty_res, "ev_umcweb_RefreshConftemp_MeetNameList_nty_res" );
	COwsCommon::MappingHelper( ev_umcweb_RefreshConftemp_PollingList_nty_req, "ev_umcweb_RefreshConftemp_PollingList_nty_req" );
	COwsCommon::MappingHelper( ev_umcweb_RefreshConftemp_PollingList_nty_res, "ev_umcweb_RefreshConftemp_PollingList_nty_res" );
	COwsCommon::MappingHelper( ev_umcweb_RefreshConftemp_DiscussList_nty_req, "ev_umcweb_RefreshConftemp_DiscussList_nty_req" );
	COwsCommon::MappingHelper( ev_umcweb_RefreshConftemp_DiscussList_nty_res, "ev_umcweb_RefreshConftemp_DiscussList_nty_res" );
	COwsCommon::MappingHelper( ev_umcweb_ConfBasUsed_nty_req, "ev_umcweb_ConfBasUsed_nty_req" );
	COwsCommon::MappingHelper( ev_umcweb_ConfBasUsed_nty_res, "ev_umcweb_ConfBasUsed_nty_res" );
	COwsCommon::MappingHelper( ev_umcweb_confmng_listconfbook_get_req, "ev_umcweb_confmng_listconfbook_get_req" );
	COwsCommon::MappingHelper( ev_umcweb_confmng_listconfbook_get_res, "ev_umcweb_confmng_listconfbook_get_res" );
	COwsCommon::MappingHelper( evtp_AddConfTemplate_req, "evtp_AddConfTemplate_req" );
	COwsCommon::MappingHelper( evtp_AddConftemplate_Notify, "evtp_AddConftemplate_Notify" );
	COwsCommon::MappingHelper( evtp_Updateconftemplate_Req, "evtp_Updateconftemplate_Req" );
	COwsCommon::MappingHelper( evtp_Updateconftemplate_Notify, "evtp_Updateconftemplate_Notify" );
	COwsCommon::MappingHelper( evtp_DelConftemplate_Req, "evtp_DelConftemplate_Req" );
	COwsCommon::MappingHelper( evtp_Delconftemplate_Notify, "evtp_Delconftemplate_Notify" );
	COwsCommon::MappingHelper( ev_del_all_conftemp_req, "ev_del_all_conftemp_req" );
	COwsCommon::MappingHelper( ev_del_all_conftemp_rsp, "ev_del_all_conftemp_rsp" );
	COwsCommon::MappingHelper( evpt_OperatorConfTemplate_Ret, "evpt_OperatorConfTemplate_Ret" );
	COwsCommon::MappingHelper( evtp_StartConfTemplate_Req, "evtp_StartConfTemplate_Req" );
	COwsCommon::MappingHelper( evtp_StartConfTemplate_Ret, "evtp_StartConfTemplate_Ret" );
	COwsCommon::MappingHelper( ev_conf_bas_used_nty, "ev_conf_bas_used_nty" );
	COwsCommon::MappingHelper( ev_umcweb_CheckConftempRepeat_req, "ev_umcweb_CheckConftempRepeat_req" );
	COwsCommon::MappingHelper( ev_umcweb_CheckConftempRepeat_res, "ev_umcweb_CheckConftempRepeat_res" );

	///////////////////////////会场操作///////////////////////////////////////
	COwsCommon::MappingHelper( ev_umcweb_epoper_startdual_req, "ev_umcweb_epoper_startdual_req" );
	COwsCommon::MappingHelper( ev_umcweb_epoper_startdual_res, "ev_umcweb_epoper_startdual_res" );
	COwsCommon::MappingHelper( ev_umcweb_epoper_stopdual_req, "ev_umcweb_epoper_stopdual_req" );
	COwsCommon::MappingHelper( ev_umcweb_epoper_stopdual_res, "ev_umcweb_epoper_stopdual_res" );
	COwsCommon::MappingHelper( ev_umcweb_epoper_applyspeaker_req, "ev_umcweb_epoper_applyspeaker_req" );
	COwsCommon::MappingHelper( ev_umcweb_epoper_applyspeaker_res, "ev_umcweb_epoper_applyspeaker_res" );
	COwsCommon::MappingHelper( ev_umcweb_epoper_quiet_req, "ev_umcweb_epoper_quiet_req" );
	COwsCommon::MappingHelper( ev_umcweb_epoper_quiet_res, "ev_umcweb_epoper_quiet_res" );
	COwsCommon::MappingHelper( ev_umcweb_epoper_mute_req, "ev_umcweb_epoper_mute_req" );
	COwsCommon::MappingHelper( ev_umcweb_epoper_mute_res, "ev_umcweb_epoper_mute_res" );
	COwsCommon::MappingHelper( ev_umcweb_epoper_drop_req, "ev_umcweb_epoper_drop_req" );
	COwsCommon::MappingHelper( ev_umcweb_epoper_drop_res, "ev_umcweb_epoper_drop_res" );
	COwsCommon::MappingHelper( ev_umcweb_epoper_call_req, "ev_umcweb_epoper_call_req" );
	COwsCommon::MappingHelper( ev_umcweb_epoper_call_res, "ev_umcweb_epoper_call_res" );
	COwsCommon::MappingHelper( ev_umcweb_list_meetingroom_get_req, "ev_umcweb_list_meetingroom_get_req" );
	COwsCommon::MappingHelper( ev_umcweb_list_meetingroom_get_res, "ev_umcweb_list_meetingroom_get_res" );
	COwsCommon::MappingHelper( ev_umcweb_epoper_selview_req, "ev_umcweb_epoper_selview_req" );
	COwsCommon::MappingHelper( ev_umcweb_epoper_selview_res, "ev_umcweb_epoper_selview_res" );
	COwsCommon::MappingHelper( ev_umcweb_selviewinfo_get_req, "ev_umcweb_selviewinfo_get_req" );
	COwsCommon::MappingHelper( ev_umcweb_selviewinfo_get_res, "ev_umcweb_selviewinfo_get_res" );
	
}
