// cncconfig.cpp: implementation of the CCncConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cncconfig.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCncConfig::CCncConfig(CCnsSession &cSession) : CCncConfigIF(),m_tGkCfg(),m_vecTTPNMServerCfg()
{
	m_pSession = &cSession;

	memset( m_achMainRoom, 0, sizeof(m_achMainRoom) );
	m_bLocalPanCam = FALSE;
	m_bVidCutLine = FALSE;

	BuildEventsMap();
}

CCncConfig::~CCncConfig()
{

}

void CCncConfig::BuildEventsMap()
{
    REG_PFUN( ev_CnCfgCnsInfo_Ind, CCncConfig::OnCnsInfoNty );
    REG_PFUN( ev_CnCfgEthnet_Ind, CCncConfig::OnEthnetInfoInd );
    REG_PFUN( ev_tppRegisterRs_Req, CCncConfig::OnRegSipNty );
    REG_PFUN( ev_tpRegisterResult_Nty, CCncConfig::OnRegResultNty );
    REG_PFUN( ev_CnSetMainRoom_Ind, CCncConfig::OnMainCnsInd );
    REG_PFUN( ev_tpRoomOffline_Nty, CCncConfig::OnCnsOfflineNty );
    REG_PFUN( ev_CnGetSysTime_Rsp, CCncConfig::OnSysTimeRsp );
    REG_PFUN( ev_tpRegisterResultFail_Nty, CCncConfig::OnRegResultFailNty );
    REG_PFUN( ev_CnsGKReg_Ret, CCncConfig::OnRegGkRsp );
    REG_PFUN( ev_CnsGKReg_Nty, CCncConfig::OnRegGkNty );

    //IPV6
    REG_PFUN( ev_CnCfgEthnetIPV6_Ind, CCncConfig::OnCfgEthnetIPV6Ind );
    REG_PFUN( ev_CnCfgIPVtpye_Ind, CCncConfig::OnIPVtpyeInd );

	REG_PFUN( ev_tppNatReg_Nty, CCncConfig::OnRegNatNty);
	//画面裁剪
	REG_PFUN( ev_TppSetVidCutLine_Ind, CCncConfig::OnVidCurLineInd);

    REG_PFUN( ev_TppSetDualInputPortName_Ind, CCncConfig::OnSetDualPortNameInd );
    REG_PFUN( ev_TppSelDualInputPort_Ind, CCncConfig::OnSelDualInputPortInd );
    REG_PFUN( ev_TppCurrentVgaInfo_Nty, CCncConfig::OnVgaInfoNty );
    REG_PFUN( ev_TppConfVgaInfo_Nty, CCncConfig::OnConfVgaInfoNty );
	REG_PFUN( ev_Cn_SetSleepInfoInd, CCncConfig::OnSysSleepNty );

	//网管页面消息处理
	REG_PFUN( ev_tppCnAgtAddNMServer_Ind, CCncConfig::OnAddNetMngInd );
	REG_PFUN( ev_tppCnAgtDelNMServer_Ind, CCncConfig::OnDelNetMngInd );
	REG_PFUN( ev_tppCnAgtModifyNMServer_Ind, CCncConfig::OnModifyNetMngInd );
	REG_PFUN( ev_tppCurAgtNMServerInfo_Nty, CCncConfig::OnNetMngNty );

	REG_PFUN( ev_tppGetRegInfo_Rsp, CCncConfig::OnRegInfoRsp );
	REG_PFUN( ev_tppGetRegInfo_Nty, CCncConfig::OnRegInfoNty );
	REG_PFUN( ev_tppGetRegGKInfo_Nty, CCncConfig::OnGetGkRegInfo );
	REG_PFUN( ev_tppGetRegInfoCNS_Rsp, CCncConfig::OnGetCnsRegInfo );
	REG_PFUN( ev_tppGetRegInfoUMS_Rsp, CCncConfig::OnGetUmsRegInfo );
	//白板
	REG_PFUN( ev_tppSetDataServerInfo_Nty, CCncConfig::OnWBServerNty );
	REG_PFUN( ev_tppSetDataServerInfo_Ind, CCncConfig::OnWBServerInd );
    
	REG_PFUN( ev_CnSetVedioInfo_Ind, CCncConfig::OnMainVideoPort );
	REG_PFUN( ev_Cns_PanCamCfgNty, CCncConfig::OnPanCamCfgNty );
	REG_PFUN( ev_tppSetSnapShotInd, CCncConfig::OnPanCamSavePresetInd );//ev_Cns_PanCamSavePresetInd
	REG_PFUN( ev_Cns_PanCamPresetMoveInd, CCncConfig::OnPanCamImplePresetInd );
	REG_PFUN( ev_Cns_PanCamPresetDeleteInd, CCncConfig::OnPanCamDeletePresetInd );
	REG_PFUN( ev_Cns_SetPanCamNameInd, CCncConfig::OnPanCamSavePresetNameInd );
	REG_PFUN( ev_Cns_PanCamSelectInd, CCncConfig::OnPanCamSelInd );
	
	REG_PFUN( ev_TppGetVidSrc_Nty, CCncConfig::OnVidSrcNty );
	REG_PFUN( ev_CnSetVedioInfo_Nty, CCncConfig::OnVedioInfoNty );

    REG_PFUN( OSP_DISCONNECT, CCncConfig::OnLinkBreak ); 
	//全景摄像机
	REG_PFUN( ev_Cns_SetPanCamOpenInd, CCncConfig::OnSetLocalCnsPanCamNty); 

	//服务器配置-量子加密
	REG_PFUN( ev_tppSetQtEncryptInfo_Ind, CCncConfig::OnSetQTEncryptInd);  
	REG_PFUN( ev_tppSetQtEncryptInfo_Nty, CCncConfig::OnSetQTEncryptNty);  

	//时间同步
	REG_PFUN( ev_CnSysTimeToCnc_Nty, CCncConfig::OnCnSysTimeToCncNty);  
	REG_PFUN( ev_CnNtpIsUsed_Ind, CCncConfig::OnCnNtpIsUsedInd);  

	//密码周期更新
	REG_PFUN( ev_CnTpadPasswordUpdate_Nty, CCncConfig::OnCnTpadPasswordUpdateNty);
	REG_PFUN( ev_CnTpadPasswordUpdate_Ind, CCncConfig::OnCnTpadPasswordUpdateInd);

    //超级管理员信息
    REG_PFUN( ev_tppSuperadmin_Nty, CCncConfig::OnSuperadminNty);
    REG_PFUN( ev_tppSuperadmin_Ind, CCncConfig::OnSuperadminInd);

    //升级后第一次登录
    REG_PFUN( ev_Cn_CNCFirstLogin_Nty, CCncConfig::OnFirstLoginAfterUpdateNty);
}

void CCncConfig::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CCncConfig, cMsg);
}


void CCncConfig::OnTimeOut(u16 wEvent)
{
    //PostEvent(MTC_UI_CMD_TIMEOUT, wEvent);
}


u16 CCncConfig::RegSipService(const TTPSipRegistrarCfg& tSipCfg)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( ins_each );
	pcTpMsg->SetEvent( ev_tppRegisterRs_Req );
	pcTpMsg->SetBody( &tSipCfg, sizeof(TTPSipRegistrarCfg) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

	in_addr tAddr;
	tAddr.S_un.S_addr = tSipCfg.dwRegIP;
	PrtMsg( ev_tppRegisterRs_Req, emEventTypeCnsSend, "TTPSipRegistrarCfg: RegIP: %s ", inet_ntoa(tAddr) );
	return wRet;
}

u16 CCncConfig::UnRegSipService()
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( ins_each );
	pcTpMsg->SetEvent( ev_tppUnRegisterRs_Req );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

	PrtMsg( ev_tppUnRegisterRs_Req, emEventTypeCnsSend, "" );
	return wRet;
}

 
u16 CCncConfig::RegGk( const TTPGKCfg& tGkCfg )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( ins_each );
   
    pcTpMsg->SetEvent( ev_CnsGKReg_Cmd );
    pcTpMsg->SetBody( &tGkCfg, sizeof(TTPGKCfg) );
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    in_addr tAddr;
    tAddr.S_un.S_addr = tGkCfg.dwGKIP;
    PrtMsg( ev_CnsGKReg_Cmd, emEventTypeCnsSend, "RegGk: isUse=%d  GkRegIP: %s ", tGkCfg.bUsed, inet_ntoa(tAddr) );
    
	return wRet;
}

const TTPGKCfg& CCncConfig::GetGkCfg() const
{
    return m_tGkCfg;
} 


u16 CCncConfig::UpdateCnsInfo( const TTPCnsInfo& tInfo, u8 byIndex, EmTpIpNameNatSyn em )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_CnCfgCnsInfo_Cmd );
	pcTpMsg->SetBody( &tInfo, sizeof(TTPCnsInfo) );
	pcTpMsg->CatBody( &byIndex, sizeof(u8) );
	pcTpMsg->CatBody( &em, sizeof(EmTpIpNameNatSyn) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

	PrtMsg( ev_CnCfgCnsInfo_Cmd, emEventTypeCnsSend, "TTPCnsInfo: CnsName: %s, E164: %s, CnsLevel: %d, ScreenNum: %d, From: %d EmTpIpNameNatSyn:%d",
		tInfo.m_achRoomName, tInfo.m_achE164, tInfo.m_emLevel, tInfo.m_wScreenNum, byIndex,em );
	return wRet;
}

u16 CCncConfig::SetMainCns( s8* pbyRoomName )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( LOCAL_CNS );
	pcTpMsg->SetEvent( ev_CnSetMainRoom_Cmd );
	s8 achName[TP_MAX_NAME_LEN+1] = {0};
	strcpy( achName, pbyRoomName );
	pcTpMsg->SetBody( achName, sizeof(achName) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_CnSetMainRoom_Cmd, emEventTypeCnsSend, "MainCnsName: %s", pbyRoomName );
	return wRet;
}

u16 CCncConfig::UpdateEthnetCfg( const TTPEthnetInfo& cfg, EmTpIpNameNatSyn em )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_CnCfgEthnet_Cmd );
	pcTpMsg->SetBody( &cfg, sizeof(TTPEthnetInfo) );
	pcTpMsg->CatBody( &em, sizeof(EmTpIpNameNatSyn) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = cfg.dwIP;
	PrtMsg( ev_CnCfgEthnet_Cmd, emEventTypeCnsSend, "CnsIP: %s EmTpIpNameNatSyn:%d", inet_ntoa(tAddr), em );
	return wRet;
}

const TTPSipRegistrarCfg& CCncConfig::GetSipRegCfg() const
{
	return m_tSipCfg;
}

const TTPEthnetInfo& CCncConfig::GetEthnetCfg() const
{
	return m_tEthnetInfo;
}


const TTPCnsInfo& CCncConfig::GetLocalCnsInfo() const
{
	return m_tLocalCnsInfo;
}

const vector<TTPCnsInfo>& CCncConfig::GetLocalCnsList() const
{
	return m_vctCnsList;
}

const s8* CCncConfig::GetMainCnsName() const
{
	return m_achMainRoom;
}

const TDualSrcInfo& CCncConfig::GetDualSrcInfo() const
{
    return m_tDualSrcInfo;
}

const TCenDevSleepInfo& CCncConfig::GetSysSleepInfo() const
{
    return m_tCenDevSleepInfo;
}

const TTPVgaMixInfo& CCncConfig::GetVgaMixInfo() const
{
	return m_tVgaMixInfo;
}

void CCncConfig::OnCnsInfoNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
    
    u8 uInst = cTpMsg.GetHomeplace();

	TTPCnsInfo tCnsInfo = *reinterpret_cast<TTPCnsInfo*>(cTpMsg.GetBody());

	EmTPCNSInfoRst tRst = *(EmTPCNSInfoRst*)( cTpMsg.GetBody() + sizeof(TTPCnsInfo) );

	//UpdateCnsList( tCnsInfo );
	
	if ( tRst == emTPCNSInfoSuccess )
	{
		m_tLocalCnsInfo = tCnsInfo;	
	}
	
	PostEvent( UI_CNS_CNSINFO_NOTIFY, NULL, (LPARAM)tRst );	

	PrtMsg( ev_CnCfgCnsInfo_Ind, emEventTypeCnsRecv, "TTPCnsInfo: CnsName: %s, E164: %s, CnsLevel: %d, ScreenNum: %d, emRst: %d, Inst: %d ", 
		tCnsInfo.m_achRoomName, tCnsInfo.m_achE164, tCnsInfo.m_emLevel, tCnsInfo.m_wScreenNum, tRst, uInst );
}

void CCncConfig::OnRegSipNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

    m_tSipCfg = *reinterpret_cast<TTPSipRegistrarCfg*>(cTpMsg.GetBody());

	PostEvent( UI_CNS_REGSIP_NOTIFY );

	in_addr tAddr;
	tAddr.S_un.S_addr = m_tSipCfg.dwRegIP;
	PrtMsg( ev_tppRegisterRs_Req, emEventTypeCnsRecv, "TTPSipRegCfg: bUsed: %d, RegIp: %s", m_tSipCfg.bUsed, inet_ntoa(tAddr) );
}

void CCncConfig::OnRegResultNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
    u8 uInst = cTpMsg.GetHomeplace();

	BOOL bResult = *(BOOL*)(cTpMsg.GetBody());	

	s8 achCnsName[TP_MAX_ALIAS_LEN + 1] = {0};
	strncpy( achCnsName, (s8*)(cTpMsg.GetBody()+sizeof(BOOL)), TP_MAX_ALIAS_LEN + 1 );
	
	PostEvent( UI_CNS_REGRESULT_NOTIFY, bResult, (LPARAM)achCnsName );
	
	PrtMsg( ev_tpRegisterResult_Nty, emEventTypeCnsRecv, "RegResult: %d, RoomName: %s, Inst: %d", bResult, achCnsName, uInst );
}

void CCncConfig::OnRegResultFailNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	//BOOL bResult = *(BOOL*)(cTpMsg.GetBody());	
	
	s8 achCnsName[TP_MAX_ALIAS_LEN + 1] = {0};
	strncpy( achCnsName, (s8*)cTpMsg.GetBody(), TP_MAX_ALIAS_LEN + 1 );

	EmTpCnsRegUms emReg = *(EmTpCnsRegUms*)( cTpMsg.GetBody()+TP_MAX_ALIAS_LEN+1 );

	if ( emReg == tp_CnsRegRet_AliasRepeat )
	{
		TTPRegNameRepeatInfo tRepeatInfo = *(TTPRegNameRepeatInfo*)( cTpMsg.GetBody()+ TP_MAX_ALIAS_LEN+1 + sizeof(EmTpCnsRegUms) );

		PostEvent( UI_CNS_SIPREG_ALIASREPEAT_NOTIFY, (WPARAM)&tRepeatInfo, (LPARAM)achCnsName );
		
		PrtMsg( ev_tpRegisterResultFail_Nty, emEventTypeCnsRecv, "RoomName: %s, EmTpCnsRegUms: %d, RepeatSize: %d", achCnsName, emReg, tRepeatInfo.dwsize );
	}
	else
	{
		PostEvent( UI_CNS_REGRESULT_NOTIFY, emReg, (LPARAM)achCnsName );

        u8 uInst = cTpMsg.GetHomeplace();
		
		PrtMsg( ev_tpRegisterResultFail_Nty, emEventTypeCnsRecv, "RoomName: %s, EmTpCnsRegUms: %d, Inst: %d", achCnsName, emReg, uInst );
	}
}


/*
tp_CnsRegRet_Unknow,
tp_CnsRegRet_Success,		//成功
tp_CnsRegRet_MaxRegNum,		//注册满
tp_CnsRegRet_MaxAliasNum,	//注册满
tp_CnsRegRet_MsgError,		//注册消息错误
tp_CnsRegRet_AliasRepeat,	//别名重复
tp_CnsRegRet_UnReg,			//删除时，未找到删除记录
tp_CnsRegRet_SysError,		//APP错误
tp_CnsRegRet_NotFind,		//查找失败
tp_CnsRegRet_Fail,          //其他失败
	tp_CnsRegRet_Unreachable,   //服务器不可达
*/
void CCncConfig::OnRegGkRsp(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    m_tUCSipRegResult = *(TUCSipRegResult*)(cTpMsg.GetBody());
      
	PrtMsg( ev_CnsGKReg_Ret, emEventTypeCnsRecv, "RegResult: %d(tp_CnsRegRet_Unknow:%d,tp_CnsRegRet_Success:%d )",
              m_tUCSipRegResult.m_emTpCnsRegUms, tp_CnsRegRet_Unknow, tp_CnsRegRet_Success );

	PostEvent( UI_CNS_REG_GK_RSP, (WPARAM)&m_tUCSipRegResult, 0 ); 
}

void CCncConfig::OnRegGkNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    TTPGKCfg tResult = *(TTPGKCfg*)(cTpMsg.GetBody());
    
    m_tGkCfg = tResult;
    
    in_addr tAddr;
    tAddr.S_un.S_addr = tResult.dwGKIP;
    PrtMsg( ev_CnsGKReg_Nty, emEventTypeCnsRecv, "RegGk: isUse=%d  GkRegIP: %s  ", tResult.bUsed, inet_ntoa(tAddr) ); 
    
	PostEvent( UI_CNS_REG_GK_NTY, 0, 0 ); 
}

void CCncConfig::OnEthnetInfoInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);	

    u8 uInst = cTpMsg.GetHomeplace();

    TTPEthnetInfo tEthnetInfo = *reinterpret_cast<TTPEthnetInfo*>(cTpMsg.GetBody());

	m_tEthnetInfo = tEthnetInfo;
	PostEvent( UI_CNS_ETHNETINFO_NOTIFY );

    in_addr tAddr;
    tAddr.S_un.S_addr = tEthnetInfo.dwIP;
    PrtMsg( ev_CnCfgEthnet_Ind, emEventTypeCnsRecv, "TTPEthnetInfo: Ip: %s, Inst: %d", inet_ntoa(tAddr), uInst );
}

void CCncConfig::OnMainCnsInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
    
    u8 uInst = cTpMsg.GetHomeplace();
    
	s8 *pRoomName = reinterpret_cast<s8 *>(cTpMsg.GetBody());
	memcpy( m_achMainRoom, pRoomName, sizeof(m_achMainRoom) );
	
	PostEvent( UI_CNS_MAINROOM_NOTIFY );	

	PrtMsg( ev_CnSetMainRoom_Ind, emEventTypeCnsRecv, "MainCnsName: %s, Inst: %d", m_achMainRoom, uInst );
}


void CCncConfig::UpdateCnsList( TTPCnsInfo tCnsInfo )
{
	for ( u32 i = 0; i < m_vctCnsList.size(); i++ )
	{
		TTPCnsInfo tInfo = m_vctCnsList.at(i);
		if ( strcmp( tInfo.m_achRoomName, tCnsInfo.m_achRoomName ) == 0 )
		{
			m_vctCnsList[i] = tCnsInfo;
			return;
		}
	}
	m_vctCnsList.push_back( tCnsInfo );
}

void CCncConfig::OnCnsOfflineNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
    
    u8 uInst = cTpMsg.GetHomeplace();
    
	s8 achCnsName[TP_MAX_ALIAS_LEN + 1] = {0};
	s8 *pRoomName = reinterpret_cast<s8 *>(cTpMsg.GetBody());
	memcpy( achCnsName, pRoomName, sizeof(achCnsName) );

	BOOL bLocalCns = FALSE;
	if ( strcmp( m_tLocalCnsInfo.m_achRoomName, achCnsName ) == 0 )
	{
		bLocalCns = TRUE;
		memset( &m_tLocalCnsInfo, 0, sizeof(m_tLocalCnsInfo) );
	}

// 	vector<TTPCnsInfo>::iterator iter = m_vctCnsList.begin();
// 	while( iter != m_vctCnsList.end() )
// 	{
// 		if ( strcmp( (*iter).m_achRoomName, achCnsName ) == 0 )
// 		{
// 			m_vctCnsList.erase( iter );
// 			break;
// 		}
// 		iter++;
// 	}	

	PrtMsg( ev_tpRoomOffline_Nty, emEventTypeCnsRecv, "CnsOffline: %s, LocalCns: %d, Inst: %d", achCnsName, bLocalCns, uInst );
	
	PostEvent( UI_CNS_ROOMOFFLINE, (WPARAM)achCnsName, bLocalCns );
}

//设置系统时间
u16 CCncConfig::UpdateSysTime( const TTPTime& time )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_CnSetSysTime_Cmd );
    pcTpMsg->SetBody( &time, sizeof(TTPTime) );
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
     
    PrtMsg( ev_CnSetSysTime_Cmd, emEventTypeCnsSend, "time: %d/%d/%d %d:%d:%d", time.m_wYear, time.m_byMonth, time.m_byMDay,time.m_byHour,time.m_byMinute,time.m_bySecond  );
	return wRet;
}

//获取系统时间
u16 CCncConfig::ReqSysTime()
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_CnGetSysTime_Req ); 
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
    PrtMsg( ev_CnGetSysTime_Req, emEventTypeCnsSend,"" );
	return wRet;
}


// 
void CCncConfig::OnSysTimeRsp(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    TTPTime time = *reinterpret_cast<TTPTime *>(cTpMsg.GetBody()); 
	PrtMsg( ev_CnGetSysTime_Rsp, emEventTypeCnsRecv, "time: %d/%d/%d %d:%d:%d", 
         time.m_wYear, time.m_byMonth, time.m_byMDay,time.m_byHour,time.m_byMinute,time.m_bySecond  );

    PostEvent( UI_CNS_SYSTIME_RSP, (WPARAM)&time, 0 );
}


u16 CCncConfig::SelDualInputPort( EmVgaType emType )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );

    pcTpMsg->SetEvent( ev_TppSelDualInputPort_Cmd ); 
    pcTpMsg->SetBody( &emType, sizeof(EmVgaType) );

    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
    PrtMsg( ev_TppSelDualInputPort_Cmd, emEventTypeCnsSend, "EmVgaType: %d", emType );
    return wRet;
     
}

u16 CCncConfig::SetDualPortInfo( const TVgaInfo& tVgaInfo, BOOL bDefault )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    
    pcTpMsg->SetEvent( ev_TppSetDualInputPortName_Cmd ); 
    pcTpMsg->SetBody( &tVgaInfo, sizeof(TVgaInfo) );
    pcTpMsg->CatBody( &bDefault, sizeof(BOOL) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
    PrtMsg( ev_TppSetDualInputPortName_Cmd, emEventTypeCnsSend, "EmVgaType: %d, Name: %s, bDefault: %d", tVgaInfo.m_emVgaType, tVgaInfo.m_achAlias, bDefault );
    return wRet;
}

void CCncConfig::OnSetDualPortNameInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    BOOL bOk = *reinterpret_cast<BOOL *>(cTpMsg.GetBody());	
    
	PrtMsg( ev_TppSetDualInputPortName_Ind, emEventTypeCnsRecv, "bOK: %d", bOk );
	//cnc中 此回复用于不在会议中进行演示源的默认设置回复 nlf确认 dyy 2015-6-9 
	PostEvent( UI_CNS_SELDEFAULTDUALPORT_IND, bOk, NULL );
}

void CCncConfig::OnSelDualInputPortInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *reinterpret_cast<BOOL*>(cTpMsg.GetBody());	

    EmVgaType emType = *reinterpret_cast<EmVgaType*>( cTpMsg.GetBody() + sizeof(BOOL) );
	//没有nty 此处保存
	m_tDualSrcInfo.emCurrentType = emType;

    EmVgaSwitchResult emResult = *reinterpret_cast<EmVgaSwitchResult*>( cTpMsg.GetBody() + sizeof(BOOL) + sizeof(EmVgaType) );
    
	PrtMsg( ev_TppSelDualInputPort_Ind, emEventTypeCnsRecv, "bOk: %d, emType: %d, emResult:%d", bOk, emType, emResult );

    PostEvent( UI_CNS_SELDUALPORT_IND, emType, emResult );
    
}

void CCncConfig::OnVgaInfoNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	m_tDualSrcInfo.Clear();

	for ( int i = 0; i < CNS_VGA_TYPE_NUM; i++ )
	{
		TVgaInfo tVgaInfo = *reinterpret_cast<TVgaInfo *>( cTpMsg.GetBody() + i * sizeof(TVgaInfo) );
		m_tDualSrcInfo.vctVgaInfo.push_back( tVgaInfo );
	}

	TVgaInfo tDefaultVga = *reinterpret_cast<TVgaInfo *>( cTpMsg.GetBody() + CNS_VGA_TYPE_NUM * sizeof(TVgaInfo) );

	m_tDualSrcInfo.emDefaultType = tDefaultVga.m_emVgaType;
	m_tDualSrcInfo.emCurrentType = *reinterpret_cast<EmVgaType *>( cTpMsg.GetBody() + (CNS_VGA_TYPE_NUM+1) * sizeof(TVgaInfo) );

	m_tVgaMixInfo = *reinterpret_cast<TTPVgaMixInfo *>( cTpMsg.GetBody() + (CNS_VGA_TYPE_NUM+1) * sizeof(TVgaInfo) + sizeof(EmVgaType) );
	PrtMsg( ev_TppCurrentVgaInfo_Nty, emEventTypeCnsRecv, "DefaultType: %d, CurrentType: %d, OutCurrent:%d, OutFstName:%s, OutFstName:%s", 
		m_tDualSrcInfo.emDefaultType, m_tDualSrcInfo.emCurrentType, m_tVgaMixInfo.m_emDualOutputType, m_tVgaMixInfo.m_achVgaOutputFstName, m_tVgaMixInfo.m_achVgaOutputSndName );

	PostEvent( UI_CNS_VGAINFO_NOTIFY );
}
 
void CCncConfig::OnConfVgaInfoNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    EmVgaType emType = *reinterpret_cast<EmVgaType*>(cTpMsg.GetBody());

    m_tDualSrcInfo.emCurrentType = emType;

    PrtMsg( ev_TppConfVgaInfo_Nty, emEventTypeCnsRecv, "CurrentType: %d", emType );

    PostEvent( UI_CNS_CONFVGAINFO_NOTIFY );
}

u16 CCncConfig::UpdateNATCfg( const TTPNatCfg& cfg, EmTpIpNameNatSyn em )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( ins_each );//此类消息需要通知所有会场
	pcTpMsg->SetEvent( ev_tppNatReg_Cmd );
	pcTpMsg->SetBody( &cfg, sizeof(TTPNatCfg) );
	pcTpMsg->CatBody( &em, sizeof(EmTpIpNameNatSyn) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = cfg.dwNatIP;
	PrtMsg( ev_tppNatReg_Cmd, emEventTypeCnsSend, "NATIP: %s EmTpIpNameNatSyn:%d", inet_ntoa(tAddr), em );
	return wRet;
}

const TTPNatCfg& CCncConfig::GetNATCfg() const
{
	return m_tNATCfg;
}

void CCncConfig::OnRegNatNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    TTPNatCfg tResult = *(TTPNatCfg*)(cTpMsg.GetBody());
    
    m_tNATCfg = tResult;
    
    in_addr tAddr;
    tAddr.S_un.S_addr = tResult.dwNatIP;
    PrtMsg( ev_tppNatReg_Nty, emEventTypeCnsRecv, "RegNAT: isUse=%d  NATRegIP: %s  ", tResult.bUsed, inet_ntoa(tAddr) ); 
    
	PostEvent( UI_CNS_REG_NAT_NTY, 0, 0 ); 	
}

void CCncConfig::OnVidCurLineInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	BOOL bIsVidCutLine = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() );
	BOOL bIsSuccess = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() + sizeof(BOOL) );
	if (bIsSuccess)
	{
		m_bVidCutLine = bIsVidCutLine;
	}

	PrtMsg( ev_TppSetVidCutLine_Ind, emEventTypeCnsRecv, _T( "IsVidCutLine:%d IsSuccess:%d"),bIsVidCutLine, bIsSuccess );
	PostEvent( UI_CNC_VIDCUTLINE_IND, bIsVidCutLine, bIsSuccess );
}

u16 CCncConfig::SetSysSleepInfo( const TCenDevSleepInfo& tCenDevSleepInfo )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    
    pcTpMsg->SetEvent( ev_Cn_SetSleepInfoCmd ); 
    pcTpMsg->SetBody( &tCenDevSleepInfo, sizeof(TCenDevSleepInfo) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
    PrtMsg( ev_Cn_SetSleepInfoCmd, emEventTypeCnsSend, "SleepTimes: %d, bOpen: %d", tCenDevSleepInfo.wSleepWaitTime, tCenDevSleepInfo.bSleepUsed );
    return wRet;
}

void CCncConfig::OnSysSleepNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    TCenDevSleepInfo tResult = *(TCenDevSleepInfo*)(cTpMsg.GetBody());
    
    m_tCenDevSleepInfo = tResult;

    
    PrtMsg( ev_Cn_SetSleepInfoInd, emEventTypeCnsRecv,  "SleepTimes: %d, bOpen: %d", m_tCenDevSleepInfo.wSleepWaitTime, m_tCenDevSleepInfo.bSleepUsed ); 
    
	PostEvent( UI_CNS_SLEEPINFO_NOTIFY, 0, 0 ); 
}

u16  CCncConfig::NetMngAddCmd( const TTPNMServerCfg& tTPNMServerCfg )
{
	if ( NULL == m_pSession ) 
	{
		return ERR_CMS;
	}

	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_CnAgtAddNMServerCmd );
	pcTpMsg->SetBody( &tTPNMServerCfg, sizeof(TTPNMServerCfg) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

	in_addr tAddr;
	tAddr.S_un.S_addr = tTPNMServerCfg.dwNMServerIP;
	PrtMsg( ev_CnAgtAddNMServerCmd, emEventTypeCnsSend, 
		"NMServerIP: %s, NMReadCommunity: %s, NMWriteCommunity: %s, NMGetSetPort: %d, NMTrapPort: %d, NMServerNO: %d",
		inet_ntoa(tAddr), tTPNMServerCfg.achNMReadCommunity, tTPNMServerCfg.achNMWriteCommunity,
		tTPNMServerCfg.wNMGetSetPort, tTPNMServerCfg.WNMTrapPort, tTPNMServerCfg.wNMServerNO );
	return wRet;
}

u16  CCncConfig::NetMngModifyCmd( const TTPNMServerCfg& tTPNMServerCfg )
{
	if ( NULL == m_pSession ) 
	{
		return ERR_CMS;
	}

	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr(); 
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_CnAgtModifyNMServerCmd );
	pcTpMsg->SetBody( &tTPNMServerCfg, sizeof(TTPNMServerCfg) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

	in_addr tAddr;
	tAddr.S_un.S_addr = tTPNMServerCfg.dwNMServerIP;
	PrtMsg( ev_CnAgtModifyNMServerCmd, emEventTypeCnsSend, 
		"NMServerIP: %s, NMReadCommunity: %s, NMWriteCommunity: %s, NMGetSetPort: %d, NMTrapPort: %d, NMServerNO: %d",
		inet_ntoa(tAddr), tTPNMServerCfg.achNMReadCommunity, tTPNMServerCfg.achNMWriteCommunity,
		tTPNMServerCfg.wNMGetSetPort, tTPNMServerCfg.WNMTrapPort, tTPNMServerCfg.wNMServerNO );
	return wRet;
}

u16  CCncConfig::NetMngDeleteCmd( const TTPNMServerCfg& tTPNMServerCfg )
{
	if ( NULL == m_pSession ) 
	{
		return ERR_CMS;
	}

	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr(); 
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_CnAgtDelNMServerCmd );
	pcTpMsg->SetBody( &tTPNMServerCfg, sizeof(TTPNMServerCfg) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

	in_addr tAddr;
	tAddr.S_un.S_addr = tTPNMServerCfg.dwNMServerIP;
	PrtMsg( ev_CnAgtDelNMServerCmd, emEventTypeCnsSend, 
		"NMServerIP: %s, NMReadCommunity: %s, NMWriteCommunity: %s, NMGetSetPort: %d, NMTrapPort: %d, NMServerNO: %d",
		inet_ntoa(tAddr), tTPNMServerCfg.achNMReadCommunity, tTPNMServerCfg.achNMWriteCommunity,
		tTPNMServerCfg.wNMGetSetPort, tTPNMServerCfg.WNMTrapPort, tTPNMServerCfg.wNMServerNO );
	return wRet;
}

void CCncConfig::GetNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg )const
{
	vecTTPNMServerCfg = m_vecTTPNMServerCfg;
	return;
}


void  CCncConfig::OnAddNetMngInd(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );

	TTPNMServerCfg tTPNMServerCfg = *reinterpret_cast<TTPNMServerCfg*>( kdvMsg.GetBody() );
	EmModifyNMServerRet emRet = *reinterpret_cast<EmModifyNMServerRet*>( kdvMsg.GetBody() + sizeof(TTPNMServerCfg) );

	if ( emRet == em_nmserver_modify_success )
	{
		if ( 0 == tTPNMServerCfg.wNMServerNO )		
		{
			m_vecTTPNMServerCfg.insert( m_vecTTPNMServerCfg.begin(), tTPNMServerCfg );
		}
		else
		{
			m_vecTTPNMServerCfg.push_back(tTPNMServerCfg);
		}
	}

	PrtMsg( ev_tppCnAgtAddNMServer_Ind, emEventTypeCnsRecv, "netmng add issuccess =%d", emRet );
	PostEvent( UI_CNSTOOL_ADD_NETMNG_IND, (WPARAM)emRet );
}

void  CCncConfig::OnDelNetMngInd(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );

	TTPNMServerCfg tTPNMServerCfg = *reinterpret_cast<TTPNMServerCfg*>( kdvMsg.GetBody() );
	EmModifyNMServerRet emRet = *reinterpret_cast<EmModifyNMServerRet*>( kdvMsg.GetBody() + sizeof(TTPNMServerCfg) );

	if ( emRet == em_nmserver_modify_success )
	{
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
	}

	PrtMsg( ev_tppCnAgtDelNMServer_Ind, emEventTypeCnsRecv, "netmng del issuccess =%d", emRet );    
	PostEvent( UI_CNSTOOL_DEL_NETMNG_IND, (WPARAM)emRet );
}

void  CCncConfig::OnModifyNetMngInd(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );

	TTPNMServerCfg tTPNMServerCfg = *reinterpret_cast<TTPNMServerCfg*>( kdvMsg.GetBody() );
	EmModifyNMServerRet emRet = *reinterpret_cast<EmModifyNMServerRet*>( kdvMsg.GetBody() + sizeof(TTPNMServerCfg) );

	if ( emRet == em_nmserver_modify_success )
	{
		vector<TTPNMServerCfg>::iterator it;
		for ( it = m_vecTTPNMServerCfg.begin(); it != m_vecTTPNMServerCfg.end(); it++ )
		{
			if ( tTPNMServerCfg.wNMServerNO == it->wNMServerNO )
			{
				*it = tTPNMServerCfg;
				break;
			}
		}
	}

	PrtMsg( ev_tppCnAgtModifyNMServer_Ind, emEventTypeCnsRecv, "netmng mdy issuccess =%d", emRet );
	PostEvent( UI_CNSTOOL_MODIFY_NETMNG_IND, (WPARAM)emRet );
}

void  CCncConfig::OnNetMngNty(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );

	TTPNMServerCfg tTPNMServerCfg = *reinterpret_cast<TTPNMServerCfg*>( kdvMsg.GetBody() );
	m_vecTTPNMServerCfg.push_back( tTPNMServerCfg );

	in_addr tAddr;
	tAddr.S_un.S_addr = tTPNMServerCfg.dwNMServerIP;
	PrtMsg( ev_tppCurAgtNMServerInfo_Nty, emEventTypeCnsRecv, "NMServerIP: %s, NMReadCommunity: %s, NMWriteCommunity: %s, NMGetSetPort: %d, NMTrapPort: %d, NMServerNO: %d",
		inet_ntoa(tAddr), tTPNMServerCfg.achNMReadCommunity, tTPNMServerCfg.achNMWriteCommunity,
		tTPNMServerCfg.wNMGetSetPort, tTPNMServerCfg.WNMTrapPort, tTPNMServerCfg.wNMServerNO );
	PostEvent( UI_CNSTOOL_NETMNG_NTY, (WPARAM)&tTPNMServerCfg );
}


const vector<TAddrInfo>& CCncConfig::GetCnsRegInfo() const
{
	return m_vctCnsRegInfo;
}

const vector<TTPAlias>& CCncConfig::GetUmsRegInfo() const
{
	return m_vctUmsRegInfo;
}

u16 CCncConfig::ReqSipRegInfo( EmGetRegInfoType emType )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();

	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_tppGetRegInfo_Req );
	pcTpMsg->SetBody( &emType, sizeof(EmGetRegInfoType) );

	if ( emType == emGetRegInfoType_CNS )
	{
		m_vctCnsRegInfo.clear();
		m_vctGkRegInfo.clear();
	}
	else if ( emType == emGetRegInfoType_UMS )
	{
		m_vctUmsRegInfo.clear();
	}

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppGetRegInfo_Req, emEventTypeCnsSend, "EmGetRegInfoType=%d ( emGetRegInfoType_CNS:%d, emGetRegInfoType_UMS:%d )", emType, emGetRegInfoType_CNS, emGetRegInfoType_UMS );
	return wRet;
}

void CCncConfig::OnRegInfoRsp(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	TTPSipRegPackInfo tPackInfo = *reinterpret_cast<TTPSipRegPackInfo*>(cTpMsg.GetBody());
	EmGetRegInfoType emType = *(EmGetRegInfoType*)( cTpMsg.GetBody() + sizeof(TTPSipRegPackInfo) );	
	TTPSipRegInfo tRegInfo = *(TTPSipRegInfo*)( cTpMsg.GetBody() + sizeof(TTPSipRegPackInfo) + sizeof(EmGetRegInfoType) );

	PrtMsg( ev_tppGetRegInfo_Rsp, emEventTypeCnsRecv, "GetType: %d, TotalPackNum: %d, PackSeq: %d, RegInfoType: %d(CNS: 1, UMS: 2), AliasNum: %d"
		, emType, tPackInfo.m_wTotalPackNum, tPackInfo.m_wPackSeq, tRegInfo.m_emSelfType, tRegInfo.m_wAliasNum );

	if ( tRegInfo.m_emSelfType == emTPEndpointTypeCNS )
	{
		//更新全局地址簿
		for ( int i = 0; i < tRegInfo.m_wAliasNum; i++ )
		{
			TAddrInfo tAddrInfo;
			TTPAlias tAlias = tRegInfo.m_atAlias[i];
			if ( tAlias.m_byType == tp_Alias_e164 )
			{
				strncpy( tAddrInfo.achE164, tAlias.m_abyAlias, TP_MAX_ALIAS_LEN_CNC+1 );
			}
			else
			{
				strncpy( tAddrInfo.achEntryName, tAlias.m_abyAlias, TP_MAX_ALIAS_LEN_CNC+1 );
			}  
			m_vctCnsRegInfo.push_back( tAddrInfo );
			//TTPAlias tAlias = tRegInfo.m_atAlias[i];			
			//m_vctCnsRegInfo.push_back( tAlias );			
		}

		if ( tPackInfo.m_wPackSeq == tPackInfo.m_wTotalPackNum )
		{			
			PostEvent( UI_CNS_REFRESH_GLOBAL_ADDRBOOK );
			if ( emType == emGetRegInfoType_ALL )
			{
				PostEvent( UI_CNS_REFRESH_CONFTEMPLATE_LIST );
			}
		}
	}
	else if ( tRegInfo.m_emSelfType == emTPEndpointTypeUMS )
	{
		//更新会议模板
		for ( int i = 0; i < tRegInfo.m_wAliasNum; i++ )
		{
			TTPAlias tAlias = tRegInfo.m_atAlias[i];			
			m_vctUmsRegInfo.push_back( tAlias );
		}

		if ( tPackInfo.m_wPackSeq == tPackInfo.m_wTotalPackNum )
		{			
			PostEvent( UI_CNS_REFRESH_CONFTEMPLATE_LIST );
			if ( emType == emGetRegInfoType_ALL )
			{
				PostEvent( UI_CNS_REFRESH_GLOBAL_ADDRBOOK );
			}
		}
	}
	else
	{
		if ( tPackInfo.m_wPackSeq == tPackInfo.m_wTotalPackNum )
		{	
			if ( emType == emGetRegInfoType_CNS )
			{
				PostEvent( UI_CNS_REFRESH_GLOBAL_ADDRBOOK );
			}
			else if ( emType == emGetRegInfoType_UMS )
			{
				PostEvent( UI_CNS_REFRESH_CONFTEMPLATE_LIST );
			}
		}
	}

}


void CCncConfig::OnRegInfoNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	TTPSipRegInfo tRegInfo = *reinterpret_cast<TTPSipRegInfo*>(cTpMsg.GetBody());

	PrtMsg( ev_tppGetRegInfo_Nty, emEventTypeCnsRecv, "RegInfoType, AliasNum: %d", tRegInfo.m_emSelfType, tRegInfo.m_wAliasNum );
}


void CCncConfig::OnGetGkRegInfo(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	TTPMtRegInfo tRegInfo = *reinterpret_cast<TTPMtRegInfo*>(cTpMsg.GetBody());

	PrtMsg( ev_tppGetRegGKInfo_Nty, emEventTypeCnsRecv, "Num: %d, IsEnd: %d", tRegInfo.m_wListNum, tRegInfo.m_bIsEnd );

	//加入在线地址簿
	for ( int i = 0; i < tRegInfo.m_wListNum; i++ )
	{
		TTPMtTerminal tMt = tRegInfo.m_atTerminal[i];

		TAddrInfo tAddrInfo;
		for ( int j = 0; j < MAX_MT_ALIAS_NUM; j++ )
		{
			TTPAlias tAlias = tMt.m_atAlias[j];
			if ( tAlias.m_byType == tp_Alias_e164 )
			{
				strncpy( tAddrInfo.achE164, tAlias.m_abyAlias, TP_MAX_ALIAS_LEN_CNC+1 );
			}
			else if ( tAlias.m_byType == tp_Alias_h323 )
			{
				strncpy( tAddrInfo.achEntryName, tAlias.m_abyAlias, TP_MAX_ALIAS_LEN_CNC+1 );
			}         
		}
        if ( tMt.m_dwIp != 0 )
        {
            in_addr tAddr;
            tAddr.S_un.S_addr = tMt.m_dwIp;
            strncpy( tAddrInfo.achIp, inet_ntoa(tAddr), TP_MAX_ALIAS_LEN_CNC+1 );
        }  
		tAddrInfo.m_emEndpointType = tMt.m_emType;

		m_vctGkRegInfo.push_back( tAddrInfo );
		//m_vctCnsRegInfo.push_back( tAddrInfo );	
	}
}

void CCncConfig::OnGetCnsRegInfo(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	TRegPackInfoEx tPackInfo = *reinterpret_cast<TRegPackInfoEx*>( cTpMsg.GetBody() );
	EmGetRegInfoType emType = *reinterpret_cast<EmGetRegInfoType*>( cTpMsg.GetBody() + sizeof(TRegPackInfoEx) );
	TCnsRegPackEx tRegPack = *reinterpret_cast<TCnsRegPackEx*>( cTpMsg.GetBody() + sizeof(TRegPackInfoEx) + sizeof(EmGetRegInfoType) );

	PrtMsg( ev_tppGetRegInfoCNS_Rsp, emEventTypeCnsRecv, "TotalPackNum: %d, PackSeq: %d, PackSize: %d"
		, tPackInfo.m_tPackInfo.m_wTotalPackNum, tPackInfo.m_tPackInfo.m_wPackSeq, tRegPack.m_wSize );

	//更新全局地址簿
	for ( int i = 0; i < tRegPack.m_wSize; i++ )
	{
		TCnsRegInfoEx tRegInfo = tRegPack.m_atRegInfo[i];

		TAddrInfo tAddrInfo;
		for ( int j = 0; j < tRegInfo.m_wAliasNum; j++ )
		{
			TTPAlias tAlias = tRegInfo.m_atAlias[j];
			if ( tAlias.m_byType == tp_Alias_e164 )
			{
				strncpy( tAddrInfo.achE164, tAlias.m_abyAlias, TP_MAX_ALIAS_LEN_CNC+1 );
			}
			else
			{
				strncpy( tAddrInfo.achEntryName, tAlias.m_abyAlias, TP_MAX_ALIAS_LEN_CNC+1 );
			}         
		}

        if ( tRegInfo.m_locolIP != 0 )
        {
            in_addr tAddr;
            tAddr.S_un.S_addr = tRegInfo.m_locolIP;
            strncpy( tAddrInfo.achIp, inet_ntoa(tAddr), TP_MAX_ALIAS_LEN_CNC+1 );
        }       

		tAddrInfo.m_emEndpointType = tRegInfo.m_emEndpointType;

		//如果gk中也注册了，用sip替换掉
		vector<TAddrInfo>::iterator itfind = m_vctGkRegInfo.begin();
		for ( ; itfind != m_vctGkRegInfo.end(); itfind++ )
		{
			if ( strcmp( tAddrInfo.achEntryName, "" ) == 0 )
			{
                if ( strcmp( tAddrInfo.achE164, "" ) == 0 )
                {
                    if ( 0 == strcmp( tAddrInfo.achIp, itfind->achIp ) )
                    {
                        break;
                    }
                }
                else
                {
				    if ( 0 == strcmp( tAddrInfo.achE164, itfind->achE164 ) )
				    {
					    break;
				    }
                }
			}
			else
			{
				if ( 0 == strcmp( tAddrInfo.achEntryName, itfind->achEntryName ) )
				{
					break;
				}
			}
		}
		if ( itfind == m_vctGkRegInfo.end() )
		{
			m_vctCnsRegInfo.push_back( tAddrInfo );
		}
		else
		{
			strncpy( itfind->achEntryName, tAddrInfo.achEntryName, TP_MAX_ALIAS_LEN_CNC+1 );
			strncpy( itfind->achE164, tAddrInfo.achE164, TP_MAX_ALIAS_LEN_CNC+1 );
            strncpy( itfind->achIp, tAddrInfo.achIp, TP_MAX_ALIAS_LEN_CNC+1 );
			itfind->m_emEndpointType = tAddrInfo.m_emEndpointType;
		}    			
	}

	if ( tPackInfo.m_tPackInfo.m_wPackSeq == tPackInfo.m_tPackInfo.m_wTotalPackNum )
	{			
		m_vctCnsRegInfo.insert( m_vctCnsRegInfo.begin(), m_vctGkRegInfo.begin(), m_vctGkRegInfo.end() );
		PostEvent( UI_CNS_REFRESH_GLOBAL_ADDRBOOK );
	}
}

void CCncConfig::OnGetUmsRegInfo(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	TRegPackInfoEx tPackInfo = *reinterpret_cast<TRegPackInfoEx*>( cTpMsg.GetBody() );
	EmGetRegInfoType emType = *reinterpret_cast<EmGetRegInfoType*>( cTpMsg.GetBody() + sizeof(TRegPackInfoEx) );
	TUmsRegPackEx tRegPack = *reinterpret_cast<TUmsRegPackEx*>( cTpMsg.GetBody() + sizeof(TRegPackInfoEx) + sizeof(EmGetRegInfoType) );

	PrtMsg( ev_tppGetRegInfoUMS_Rsp, emEventTypeCnsRecv, "TotalPackNum: %d, PackSeq: %d, PackSize: %d"
		, tPackInfo.m_tPackInfo.m_wTotalPackNum, tPackInfo.m_tPackInfo.m_wPackSeq, tRegPack.m_wSize );

	for ( int i = 0; i < tRegPack.m_wSize; i++ )
	{
		TUmsRegInfoEx tRegInfo = tRegPack.m_atRegInfo[i];

		for ( int j = 0; j < tRegInfo.m_wAliasNum; j++ )
		{
			TTPAlias tAlias = tRegInfo.m_atAlias[j];
			m_vctUmsRegInfo.push_back( tAlias );    
		}		
	}

	if ( tPackInfo.m_tPackInfo.m_wPackSeq == tPackInfo.m_tPackInfo.m_wTotalPackNum )
	{			
		PostEvent( UI_CNS_REFRESH_CONFTEMPLATE_LIST );
	}
}

// 断链清空数据
void CCncConfig::OnLinkBreak(const CMessage& cMsg)
{
	memset( &m_tEthnetInfo, 0, sizeof(m_tEthnetInfo) );
	memset( &m_tSipCfg, 0, sizeof(m_tSipCfg) );
	memset( &m_tLocalCnsInfo, 0, sizeof(m_tLocalCnsInfo) );
	memset( m_achMainRoom, 0, sizeof(m_achMainRoom) );
	memset( &m_tGkCfg, 0, sizeof(m_tGkCfg) );
	memset( &m_tVgaMixInfo, 0, sizeof(m_tVgaMixInfo) );
	memset( &m_tWBSerIp, 0, sizeof(m_tWBSerIp) );
	m_vctCnsList.clear();
	m_tDualSrcInfo.Clear();
	m_vecTTPNMServerCfg.clear();
	m_vctGkRegInfo.clear();
	m_vctCnsRegInfo.clear();
	m_vctUmsRegInfo.clear();
	m_bLocalPanCam = FALSE;
	m_bVidCutLine = FALSE;

	memset( &m_tPanCamInfo, 0, sizeof(m_tPanCamInfo) );
	memset( &m_tCenDevSleepInfo, 0, sizeof(m_tCenDevSleepInfo) );
	memset( &m_tNATCfg, 0, sizeof(m_tNATCfg) );
	m_mapEmTPMtVideoPort.clear();

	m_tQTEncrypt.Clear();

	PrtMsg( OSP_DISCONNECT, emEventTypeCnsRecv,"[CCncConfig::OnLinkBreak]清空配置信息" );
}

u16 CCncConfig::SetDataServerInfoCmd( u32 dwIp )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( 1 );
	pcTpMsg->SetEvent( ev_tppSetDataServerInfo_Cmd );

	TTPDataConfInfo tDCInfo;
	tDCInfo.dwSerIP = dwIp;

	pcTpMsg->SetBody( &tDCInfo, sizeof(TTPDataConfInfo) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

	in_addr tAddr;
	tAddr.S_un.S_addr = dwIp;
	PrtMsg( ev_tppSetDataServerInfo_Cmd, emEventTypeCnsSend, "DataConfIp:%s", inet_ntoa(tAddr) );

	return wRet;
}

const TTPDataConfInfo& CCncConfig::GetWBSerIp() const
{
	return m_tWBSerIp;
}

void CCncConfig::OnWBServerNty( const CMessage& cMsg ) 
{
	CTpMsg cTpMsg(&cMsg); 

	m_tWBSerIp = *reinterpret_cast<TTPDataConfInfo*>(cTpMsg.GetBody());

	in_addr tAddr;
	tAddr.S_un.S_addr = m_tWBSerIp.dwSerIP;
	PrtMsg( ev_tppSetDataServerInfo_Nty, emEventTypeCnsSend, "DataConfIp:%s", inet_ntoa(tAddr) );

	PostEvent( UI_CNSTOOL_MSG_BD_NTY, 0, 0 );

}

void CCncConfig::OnWBServerInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg); 

	TTPDataConfInfo tWBSerIp = *reinterpret_cast<TTPDataConfInfo*>(cTpMsg.GetBody()); //ind不刷新 nty刷新
	BOOL bIsSuc = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() + sizeof(TTPDataConfInfo) );
    if ( bIsSuc )
    {
        m_tWBSerIp = tWBSerIp;
    }

	in_addr tAddr;
	tAddr.S_un.S_addr = tWBSerIp.dwSerIP;
	PrtMsg( ev_tppSetDataServerInfo_Ind, emEventTypeCnsSend, "DataConfIp:%s success:%d", inet_ntoa(tAddr), bIsSuc );

	PostEvent( UI_CNSTOOL_MSG_BD_IND,0,(LPARAM)bIsSuc );
}

u16 CCncConfig::SetMainVideoPort( EmTPMtVideoPort emTPMtVideoPort, u8 wID )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_CnSetVedioInfo_Cmd ); 
	pcTpMsg->SetBody( &wID, sizeof(u8) );
	pcTpMsg->CatBody( &emTPMtVideoPort, sizeof(EmTPMtVideoPort) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
	PrtMsg( ev_CnSetVedioInfo_Cmd, emEventTypeCnsSend, "EmTPMtVideoPort: %d,ID: %d",emTPMtVideoPort, wID );
	return wRet;
}

void CCncConfig::OnMainVideoPort( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	u8 wIndex  = *reinterpret_cast<u8 *>( cTpMsg.GetBody() );
	EmTPMtVideoPort emTPMtVideoPort = *reinterpret_cast<EmTPMtVideoPort *>( cTpMsg.GetBody() + sizeof(u8) );

	BOOL bIsSuccess = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() + sizeof(u8) + sizeof(EmTPMtVideoPort) );
	if (bIsSuccess)
	{
		m_mapEmTPMtVideoPort[wIndex] = emTPMtVideoPort;
	}

	PrtMsg( ev_CnSetVedioInfo_Ind, emEventTypeCnsRecv, _T( "set CnSetVedioInfo:%d "),bIsSuccess  );

	PostEvent( UI_CNS_SETMAINVEDIO_IND, bIsSuccess, wIndex );
}

const map<u16, EmTPMtVideoPort>& CCncConfig::GetMainVideoPort() const
{
	return m_mapEmTPMtVideoPort;
}

void CCncConfig::OnPanCamCfgNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	m_tPanCamInfo = *reinterpret_cast<TPanCamInfo *>( cTpMsg.GetBody());

	u8 wIndex = *reinterpret_cast<u8 *>( cTpMsg.GetBody() + sizeof(TPanCamInfo) );

	PrtMsg( ev_Cns_PanCamCfgNty, emEventTypeCnsRecv, _T( "CurrentPanCamIndex:%d byPanCamNum:%d bPanCamOpen:%d"),wIndex, m_tPanCamInfo.byPanCamNum, m_tPanCamInfo.bPanCamOpen);
	m_bLocalPanCam = m_tPanCamInfo.bPanCamOpen;

	PostEvent( UI_CNS_PANCAMINFO_NTY, wIndex, 0 );
}

const TPanCamInfo& CCncConfig::GetPanCamInfo() const
{
	return m_tPanCamInfo;
}

BOOL32 CCncConfig::IsLocalCnsPanCam() const
{
	return m_bLocalPanCam;
}

u16 CCncConfig::SetLocalCnsPanCam( u8 wCamId ,BOOL bPanCam/* = TRUE*/)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();

	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_Cns_SetPanCamOpenCmd );
	pcTpMsg->SetBody( &bPanCam, sizeof(BOOL) );
	pcTpMsg->CatBody( &wCamId, sizeof(u8) );

	m_bLocalPanCam = bPanCam;//记录状态 因为ind返回的是操作是否成功 无状态
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cns_SetPanCamOpenCmd, emEventTypeCnsSend, "bPanCam: %d CamId:%d", bPanCam ,wCamId);
	return wRet;
}

void CCncConfig::OnSetLocalCnsPanCamNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg);  	
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody());//操作是否成功 不表示当前实际状态 
	u8 byScreenID = *(u8*)(cTpMsg.GetBody() + sizeof(BOOL) );//废弃 fxb确认 2015-6-29

	if (!bSuccess)//操作失败 状态还原
	{
		m_bLocalPanCam = !m_bLocalPanCam;
	}
	PrtMsg( ev_Cns_SetPanCamOpenInd, emEventTypeCnsRecv, "Screen: %d, bSuccess: %d", byScreenID, bSuccess );
	PostEvent( UI_CNS_PANCAMSTART_RSP, byScreenID, bSuccess ); 
}

void CCncConfig::OnPanCamSavePresetInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	EmTpSnapShotType emTpSnapShotType = *reinterpret_cast<EmTpSnapShotType *>( cTpMsg.GetBody() );
	BOOL bIsSuccess = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() + sizeof(EmTpSnapShotType) );
	//两个u8第一个是照相机索引 第二个是预置位索引
	u8 wCamID = *reinterpret_cast<u8 *>( cTpMsg.GetBody() + sizeof(EmTpSnapShotType) + sizeof(BOOL) );
	u8 wPresetID = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() + sizeof(EmTpSnapShotType) + sizeof(BOOL) + sizeof(u8) );
	if (emTpSnapShotType == EmTpSnatShot_PanoramicCamera )
	{
		PrtMsg( ev_tppSetSnapShotInd, emEventTypeCnsRecv, _T( "PanCamSavePreset Success:%d PresetID:%d"),bIsSuccess, wPresetID  );//ev_Cns_PanCamSavePresetInd废弃 范小波确认 ev_tppSetSnapShotInd代替 2015-6-1
		PostEvent( UI_CNS_PANCAMPRESETSAVE_IND, bIsSuccess, wPresetID );
	} 
	else if (emTpSnapShotType == EmTpSnatShot_Docamera )//ev_Cn_DocSetSnapShotInd废弃 范小波确认 ev_tppSetSnapShotInd代替 2015-6-1
	{
		PrtMsg( ev_tppSetSnapShotInd, emEventTypeCnsRecv, "DocSetSnapShot bSuccess: %d CamID:%d", bIsSuccess, wCamID );
		PostEvent( UI_CNS_DOCSNAPSHOT_IND, bIsSuccess, wPresetID );
	} 
	
}

void CCncConfig::OnPanCamDeletePresetInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	u8 wPresetID = *reinterpret_cast<u8 *>( cTpMsg.GetBody() );
	BOOL bIsSuccess = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() + sizeof(u8) );

	PrtMsg( ev_Cns_PanCamPresetDeleteInd, emEventTypeCnsRecv, _T( "PanCamSavePreset Success:%d PresetID:%d"),bIsSuccess, wPresetID );
	PostEvent( UI_CNS_PANCAMPRESETDEL_IND, bIsSuccess, wPresetID );

}

void CCncConfig::OnPanCamImplePresetInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	u8 wPresetID = *reinterpret_cast<u8 *>( cTpMsg.GetBody() );
	BOOL bIsSuccess = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() + sizeof(u8) );

	PrtMsg( ev_Cns_PanCamPresetMoveInd, emEventTypeCnsRecv, _T( "PanCamSavePreset Success:%d PresetID:%d"),bIsSuccess, wPresetID );
	PostEvent( UI_CNS_PANCAMPRESETIMPLE_IND, bIsSuccess, wPresetID );

}

void CCncConfig::OnPanCamSavePresetNameInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	u8 wPresetID = *reinterpret_cast<u8 *>( cTpMsg.GetBody() );
	BOOL bIsSuccess = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() + sizeof(u8) );

	PrtMsg( ev_Cns_SetPanCamNameInd, emEventTypeCnsRecv, _T( "PanCamSavePresetNameSave Success:%d PresetID:%d"),bIsSuccess, wPresetID );
	PostEvent( UI_CNS_PANCAMPRESETNAMESAVE_IND, bIsSuccess, wPresetID );

}

void CCncConfig::OnPanCamSelInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	u8 wCamID = *reinterpret_cast<u8 *>( cTpMsg.GetBody() );
	BOOL bIsSuccess = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() + sizeof(u8) );

	PrtMsg( ev_Cns_PanCamSelectInd, emEventTypeCnsRecv, _T( "PanCamSel Success:%d PresetID:%d"),bIsSuccess, wCamID );
	PostEvent( UI_CNS_PANCAMSEL_IND, bIsSuccess, wCamID );
}

u16 CCncConfig::SetPanCamSelectIndex( u8 wIndex )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_Cns_PanCamSelectCmd ); 
	pcTpMsg->SetBody( &wIndex, sizeof(u8) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
	PrtMsg( ev_Cns_PanCamSelectCmd, emEventTypeCnsSend, "PanCamSelectedIndex=: %d", wIndex );
	return wRet;
}

u16 CCncConfig::SetPanCamPT( EmDirection emDirection, EmCnAction emCnAction )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_Cns_PanCamPTCmd ); 
	pcTpMsg->SetBody( &emDirection, sizeof(EmDirection) );
	pcTpMsg->CatBody( &emCnAction, sizeof(EmCnAction) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
	PrtMsg( ev_Cns_PanCamPTCmd, emEventTypeCnsSend, "Direction:%d, Action:%d", emDirection, emCnAction );
	return wRet;
}


u16 CCncConfig::SetPanCamView( EmZoom emZoom, EmCnAction emCnAction )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_Cns_PanCamZoomCmd ); 
	pcTpMsg->SetBody( &emZoom, sizeof(EmZoom) );
	pcTpMsg->CatBody( &emCnAction, sizeof(EmCnAction) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
	PrtMsg( ev_Cns_PanCamZoomCmd, emEventTypeCnsSend, "Zoom:%d, Action:%d", emZoom, emCnAction );
	return wRet;
}

u16 CCncConfig::SetPanCamLight( EmPanCamBright emPanCamBright, EmCnAction emCnAction )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_Cns_PanCamBackLightCmd ); 
	pcTpMsg->SetBody( &emPanCamBright, sizeof(EmPanCamBright) );
	pcTpMsg->CatBody( &emCnAction, sizeof(EmCnAction) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
	PrtMsg( ev_Cns_PanCamBackLightCmd, emEventTypeCnsSend, "PanCamBright:%d, Action:%d", emPanCamBright, emCnAction );
	return wRet;
}

u16 CCncConfig::SetPanCamFocus( EmFocus emFocus, EmCnAction emCnAction )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_Cns_PanCamFocusCmd ); 
	pcTpMsg->SetBody( &emFocus, sizeof(EmFocus) );
	pcTpMsg->CatBody( &emCnAction, sizeof(EmCnAction) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
	PrtMsg( ev_Cns_PanCamFocusCmd, emEventTypeCnsSend, "Focus:%d, Action:%d", emFocus, emCnAction );
	return wRet;
}

u16 CCncConfig::SetPanCamAotoFocus()
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_Cns_PanCamAutoFocusCmd ); 

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
	PrtMsg( ev_Cns_PanCamAutoFocusCmd, emEventTypeCnsSend, "AotoFocus" );
	return wRet;
}

u16 CCncConfig::SavePanCamPreset( u8 wID )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_Cns_PanCamSavePresetCmd ); 
	pcTpMsg->SetBody( &wID, sizeof(u8) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
	PrtMsg( ev_Cns_PanCamSavePresetCmd, emEventTypeCnsSend, "ID:%d", wID );
	return wRet;
}

u16 CCncConfig::ImpelPanCamPreset( u8 wID )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_Cns_PanCamPresetMoveCmd ); 
	pcTpMsg->SetBody( &wID, sizeof(u8) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
	PrtMsg( ev_Cns_PanCamPresetMoveCmd, emEventTypeCnsSend, "ID:%d", wID );
	return wRet;
}

u16 CCncConfig::DeletePanCamPreset( u8 wID )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_Cns_PanCamPresetDeleteCmd ); 
	pcTpMsg->SetBody( &wID, sizeof(u8) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
	PrtMsg( ev_Cns_PanCamPresetDeleteCmd, emEventTypeCnsSend, "ID:%d", wID );
	return wRet;
}

u16 CCncConfig::SavePanCamPresetName( u8 wID ,TPanCamName tPanCamName)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_Cns_SetPanCamNameCmd ); 
	pcTpMsg->SetBody( &wID, sizeof(u8) );
	pcTpMsg->CatBody( &tPanCamName, sizeof(TPanCamName) );
	

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
	PrtMsg( ev_Cns_SetPanCamNameCmd, emEventTypeCnsSend, "ID:%d", wID );
	return wRet;
}

void CCncConfig::OnVidSrcNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	u8 wSrcID = *reinterpret_cast<u8 *>( cTpMsg.GetBody() );
	BOOL bIsSuccess = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() + sizeof(u8) );

	PrtMsg( ev_TppGetVidSrc_Nty, emEventTypeCnsRecv, _T( "PanCamSel Success:%d PresetID:%d"),bIsSuccess, wSrcID );
	PostEvent( UI_CNS_VIDSRC_NTY, bIsSuccess, wSrcID );
}

void CCncConfig::OnVedioInfoNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	m_tTPVideoInfoTool = *reinterpret_cast<TTPVideoInfoTool *>( cTpMsg.GetBody() );

	PrtMsg( ev_CnSetVedioInfo_Nty, emEventTypeCnsRecv, _T( "m_tTPVideoInfoTool update") );
	PostEvent( UI_CNS_SETVEDIOINFO_NTY );
}

BOOL32 CCncConfig::IsVidCutLine() const
{
	return m_bVidCutLine;
}

u16 CCncConfig::SetVidCutLine( BOOL bIsVidCutLine )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_TppSetVidCutLine_Cmd ); 
	pcTpMsg->SetBody( &bIsVidCutLine, sizeof(BOOL) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
	PrtMsg( ev_TppSetVidCutLine_Cmd, emEventTypeCnsSend, "bIsVidCutLine：%d", bIsVidCutLine );
	return wRet;
}

u16 CCncConfig::SetQtEncryptCfg( const TTpQtEncryptCfg& tQtEncrypt)
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_tppSetQtEncryptInfo_Cmd ); 
	pcTpMsg->SetBody( &tQtEncrypt, sizeof(TTpQtEncryptCfg) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 

	in_addr tAddr;
	tAddr.S_un.S_addr = tQtEncrypt.m_dwQtIP;
	PrtMsg( ev_tppSetQtEncryptInfo_Cmd, emEventTypeCnsSend, _T("bOpen:%d IP:%s ID:%d"), tQtEncrypt.m_bOpen, inet_ntoa(tAddr), tQtEncrypt.m_dwQtID );
	return wRet;
}

const TTpQtEncryptCfg& CCncConfig::GetQTEncrypt() const
{
	return m_tQTEncrypt;
}

void CCncConfig::OnSetQTEncryptInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg); 

	TTpQtEncryptCfg tQTEncrypt = *reinterpret_cast<TTpQtEncryptCfg*>(cTpMsg.GetBody()); //ind不刷新 nty刷新
	BOOL bIsSuc = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() + sizeof(TTpQtEncryptCfg) );
	u8 nCncOrTools = *reinterpret_cast<u8 *>( cTpMsg.GetBody() + sizeof(TTpQtEncryptCfg) + sizeof(BOOL) );
    BOOL bIsReboot = FALSE; 
	if ( bIsSuc )
	{
        if ( (m_tQTEncrypt.m_dwQtID != tQTEncrypt.m_dwQtID || m_tQTEncrypt.m_dwQtIP != tQTEncrypt.m_dwQtIP) && nCncOrTools != node_cnstool2cns)
        {
            bIsReboot = TRUE;
        }
		m_tQTEncrypt = tQTEncrypt;
	}

	in_addr tAddr;
	tAddr.S_un.S_addr = tQTEncrypt.m_dwQtIP;
	PrtMsg( ev_tppSetQtEncryptInfo_Ind, emEventTypeCnsRecv, _T("bOpen:%d IP:%s ID:%d StemFrom:%d success:%d"), m_tQTEncrypt.m_bOpen, inet_ntoa(tAddr), tQTEncrypt.m_dwQtID, nCncOrTools, bIsSuc );

	PostEvent( UI_CNC_QTENCRYPT_IND,(WPARAM)bIsReboot,(LPARAM)bIsSuc );
}

void CCncConfig::OnSetQTEncryptNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg); 

	m_tQTEncrypt = *reinterpret_cast<TTpQtEncryptCfg*>(cTpMsg.GetBody());

	in_addr tAddr;
	tAddr.S_un.S_addr = m_tQTEncrypt.m_dwQtIP;
	PrtMsg( ev_tppSetQtEncryptInfo_Nty, emEventTypeCnsRecv, _T("bOpen:%d IP:%s ID:%d"), m_tQTEncrypt.m_bOpen, inet_ntoa(tAddr), m_tQTEncrypt.m_dwQtID );

	PostEvent( UI_CNC_QTENCRYPT_NTY, 0, 0 );
}

u16 CCncConfig::SetTimeSynchroCmd( BOOL bIsCheck )
{
	if ( NULL == m_pSession ) 
	{
		return ERR_CMS;
	}

	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_CnNtpIsUsed_Cmd );
	pcTpMsg->SetBody( &bIsCheck, sizeof(BOOL) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

	PrtMsg( ev_CnAgtAddNMServerCmd, emEventTypeCnsSend, "bIsCheck:%d", bIsCheck );
	return wRet;
}

void CCncConfig::OnCnSysTimeToCncNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg); 

	m_tTPTime = *reinterpret_cast<TTPTime*>(cTpMsg.GetBody());
	BOOL bState = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() + sizeof(TTPTime) );

	PrtMsg( ev_CnSysTimeToCnc_Nty, emEventTypeCnsRecv, _T("bState:%d time:%d-%d-%d %d:%d:%d"), bState, m_tTPTime.m_wYear, m_tTPTime.m_byMonth, m_tTPTime.m_byMDay, m_tTPTime.m_byHour, m_tTPTime.m_byMinute, m_tTPTime.m_bySecond );

	PostEvent( UI_CNC_CNSYSTIMETOCNC_NTY, (WPARAM)&m_tTPTime, bState );
}

void CCncConfig::OnCnNtpIsUsedInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	BOOL bState = *reinterpret_cast<BOOL*>( cTpMsg.GetBody() );
	BOOL bIsOK = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() + sizeof(BOOL) );
	if (!bIsOK)
	{
		bState = !bState;
	}
	m_tTPTime = *reinterpret_cast<TTPTime*>( cTpMsg.GetBody() + sizeof(BOOL) + sizeof(BOOL) );

	PrtMsg( ev_CnNtpIsUsed_Ind, emEventTypeCnsRecv, _T("bState:%d time:%d-%d-%d %d:%d:%d"), bState, m_tTPTime.m_wYear, m_tTPTime.m_byMonth, m_tTPTime.m_byMDay, m_tTPTime.m_byHour, m_tTPTime.m_byMinute, m_tTPTime.m_bySecond );

	PostEvent( UI_CNC_CNSYSTIMETOCNC_NTY, (WPARAM)&m_tTPTime, bState );
}

u16 CCncConfig::SetTpadPasswordUpdate(TTpPasswordUpdateInfo tTpPasswordUpdateInfo)
{
	if ( NULL == m_pSession ) 
	{
		return ERR_CMS;
	}

	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_CnTpadPasswordUpdate_Cmd );
	pcTpMsg->SetBody( &tTpPasswordUpdateInfo, sizeof(tTpPasswordUpdateInfo) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

	PrtMsg( ev_CnTpadPasswordUpdate_Cmd, emEventTypeCnsSend,  _T("bOpen:%d frequency:%d modifytime:%d-%d-%d %d:%d:%d"), m_tTpPasswordUpdateInfo.m_bOpen, m_tTpPasswordUpdateInfo.m_emUpdateFrequency );
	return wRet;
}

const TTpPasswordUpdateInfo& CCncConfig::GetPasswordUpdateInfo()const
{
	return m_tTpPasswordUpdateInfo;
}

u16 CCncConfig::SetSuperadmninInfo(TTpSuperUser tTpSuperUser)
{
    if ( NULL == m_pSession ) 
    {
        return ERR_CMS;
    }

    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_tppSuperadmin_Cmd );
    pcTpMsg->SetBody( &tTpSuperUser, sizeof(tTpSuperUser) );
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

    PrtMsg( ev_tppSuperadmin_Cmd, emEventTypeCnsSend,  _T("LockNumber:%d LockTime:%d"), tTpSuperUser.m_byLockNumber, tTpSuperUser.m_dwLockTime );
    return wRet;
}

const TTpSuperUser& CCncConfig::GetSuperadmninInfo()const
{
    return m_tTpSuperUser;
}

u16 CCncConfig::UnlockAllUser()
{
    if ( NULL == m_pSession ) 
    {
        return ERR_CMS;
    }

    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_tppSuperadminClear_Cmd );
    BOOL bOk = TRUE;
    pcTpMsg->SetBody( &bOk, sizeof(BOOL) );
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

    PrtMsg( ev_tppSuperadminClear_Cmd, emEventTypeCnsSend, _T("Unlock all user.") );
    return wRet;
}

void CCncConfig::OnCnTpadPasswordUpdateNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	m_tTpPasswordUpdateInfo = *reinterpret_cast<TTpPasswordUpdateInfo*>( cTpMsg.GetBody() );

	TTPTime tTPTime = m_tTpPasswordUpdateInfo.m_tTime;
	PrtMsg( ev_CnTpadPasswordUpdate_Nty, emEventTypeCnsRecv, _T("bOpen:%d frequency:%d modifytime:%d-%d-%d %d:%d:%d"), m_tTpPasswordUpdateInfo.m_bOpen, m_tTpPasswordUpdateInfo.m_emUpdateFrequency,
																 tTPTime.m_wYear, tTPTime.m_byMonth, tTPTime.m_byMDay, tTPTime.m_byHour, tTPTime.m_byMinute, tTPTime.m_bySecond);

	PostEvent( UI_CNTPADPWUPDATE_NTY, (WPARAM)&m_tTpPasswordUpdateInfo, 0 );
}

void CCncConfig::OnCnTpadPasswordUpdateInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	TTpPasswordUpdateInfo tTpPasswordUpdateInfo = *reinterpret_cast<TTpPasswordUpdateInfo*>( cTpMsg.GetBody() );
	BOOL bIsOK = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() + sizeof(TTpPasswordUpdateInfo) );

	PrtMsg( ev_CnTpadPasswordUpdate_Ind, emEventTypeCnsRecv, _T("bState:%d"), bIsOK);

	if (bIsOK)
	{
		m_tTpPasswordUpdateInfo = tTpPasswordUpdateInfo;
	}

	PostEvent( UI_CNTPADPWUPDATE_IND, (WPARAM)&m_tTpPasswordUpdateInfo, 0 );
}

void CCncConfig::OnSuperadminNty( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);

    m_tTpSuperUser = *reinterpret_cast<TTpSuperUser*>( cTpMsg.GetBody() );

    PrtMsg( ev_tppSuperadmin_Nty, emEventTypeCnsRecv, _T("bOpen:%d frequency:%d"), m_tTpSuperUser.m_byLockNumber, m_tTpSuperUser.m_dwLockTime);

    PostEvent( UI_SUPERADMIN_NTY, (WPARAM)&m_tTpSuperUser, 0 );
}

void CCncConfig::OnSuperadminInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);

    TTpSuperUser tTpSuperUser = *reinterpret_cast<TTpSuperUser*>( cTpMsg.GetBody() );
    BOOL bIsOK = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() + sizeof(TTpSuperUser) );

    PrtMsg( ev_tppSuperadmin_Ind, emEventTypeCnsRecv, _T("bState:%d"), bIsOK);

    if (bIsOK)
    {
        m_tTpSuperUser = tTpSuperUser;
    }

    PostEvent( UI_SUPERADMIN_NTY, (WPARAM)&m_tTpSuperUser, 0 );
}


void CCncConfig::OnFirstLoginAfterUpdateNty(const CMessage& cMsg)
{
    PrtMsg( ev_Cn_CNCFirstLogin_Nty, emEventTypeCnsRecv, _T("first login after update."));

    PostEvent( UI_FIRSTLOGINAFTERUPDATE_NTY );
}

//IPV6配置
u16 CCncConfig::SetIpv6Cfg( TTPEthnetIPV6Info tTPEthnetIPV6Info, EmTpIpNameNatSyn emTpIpNameNatSyn)
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_CnCfgEthnetIPV6_Cmd );
    pcTpMsg->SetBody( &tTPEthnetIPV6Info, sizeof(TTPEthnetIPV6Info) );
    pcTpMsg->CatBody( &emTpIpNameNatSyn, sizeof(EmTpIpNameNatSyn) );

    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_CnCfgEthnetIPV6_Cmd, emEventTypeCnsSend, "IP:%s, SubLen:%d, GateWay:%s, DNS1:%s, DNS2:%s, emTpIpNameNatSyn : %d" ,
        tTPEthnetIPV6Info.m_achIP,tTPEthnetIPV6Info.m_dwPrefix,tTPEthnetIPV6Info.m_achGateWay,tTPEthnetIPV6Info.m_achDns1,tTPEthnetIPV6Info.m_achDns2, emTpIpNameNatSyn);

    return wRet;
}

void CCncConfig::OnCfgEthnetIPV6Ind(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);	

    TTPEthnetIPV6Info tTPEthnetIPV6Info = *(TTPEthnetIPV6Info*)(cTpMsg.GetBody());

    m_tTPEthnetIPV6Info = tTPEthnetIPV6Info;

    PostEvent( UI_CNS_IPV6CFG_NOTIFY );

    PrtMsg( ev_CnCfgEthnetIPV6_Ind, emEventTypeCnsRecv, "IP:%s, SubLen:%d, GateWay:%s, DNS1:%s, DNS2:%s.",
        tTPEthnetIPV6Info.m_achIP,tTPEthnetIPV6Info.m_dwPrefix,tTPEthnetIPV6Info.m_achGateWay,tTPEthnetIPV6Info.m_achDns1,tTPEthnetIPV6Info.m_achDns2);
}

const TTPEthnetIPV6Info CCncConfig::GetIpv6Cfg()
{
    return m_tTPEthnetIPV6Info;
}

u16 CCncConfig::SetIpvType( EmProtocolVersion emProtocolVer )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_CnCfgIPVtpye_Cmd );
    pcTpMsg->SetBody( &emProtocolVer, sizeof(EmProtocolVersion) );

    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_CnCfgIPVtpye_Cmd, emEventTypeCnsSend, "ProtocolVer : %d" , emProtocolVer);

    return wRet;
}

void CCncConfig::OnIPVtpyeInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);	

    EmProtocolVersion emProtocolVer = *(EmProtocolVersion*)(cTpMsg.GetBody());
    BOOL bSuccess = *(BOOL*)(cTpMsg.GetBody() + sizeof(EmProtocolVersion));

    if (bSuccess)
    {
        m_emProtocolVersion = emProtocolVer;
    }
    PostEvent( UI_CNS_IPVTYPE_NOTIFY );

    PrtMsg( ev_CnCfgIPVtpye_Ind, emEventTypeCnsRecv, "Protocol: %d, Success: %d", emProtocolVer, bSuccess );
}

const EmProtocolVersion CCncConfig::GetIpvType()
{
    return m_emProtocolVersion;
}
