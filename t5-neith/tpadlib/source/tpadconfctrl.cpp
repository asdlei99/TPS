#include "StdAfx.h"
#include "TpadConfCtrl.h"


CTpadConfCtrl::CTpadConfCtrl(CTPadSession &cTpadSession)
	:CTpadConfCtrlIF(),m_pTpadSession(NULL)
{
	m_pTpadSession = &cTpadSession;
	m_bRecvDual = FALSE;
	m_nVideoNode = TP_INVALID_INDEX;
	m_nAudioNode = TP_INVALID_INDEX;

	BuildEventsMap();
}

CTpadConfCtrl::~CTpadConfCtrl(void)
{
}

void CTpadConfCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN(CTpadConfCtrl, cMsg);
}

void CTpadConfCtrl::OnTimeOut(u16 wEvent)
{
}

void CTpadConfCtrl::BuildEventsMap()
{

	REG_PFUN( OSP_DISCONNECT, CTpadConfCtrl::OnLinkBreak );

	REG_PFUN( ev_TppIsRcvDual_Nty, CTpadConfCtrl::OnRecvDualNty );

	REG_PFUN( ev_TppAddDualRcvAddr_Ind, CTpadConfCtrl::OnStartDualCdStrmRsp );
	REG_PFUN( ev_TppDelDualRcvAddr_Ind, CTpadConfCtrl::OnStopDualCdStrmRsp );

	REG_PFUN( ev_tppCodecEncryptKey_Nty, CTpadConfCtrl::OnDualCodeEnCryptKeyNty );

	REG_PFUN( ev_CnConfState_Nty, CTpadConfCtrl::OnConfStateNty );	

	//白板会议获得会场名进行消息解析 dyy 2014-5-15
	REG_PFUN( ev_CnCfgCnsInfo_Ind, CTpadConfCtrl::OnCnsInfoNty );	
	//白板会议相关消息响应 dyy 2014-5-14
	REG_PFUN( ev_tpp_JoinWBConf_Cmd, CTpadConfCtrl::OnJoinWBConfCmd );	
	REG_PFUN( ev_tpp_LeaveWBConf_Nty, CTpadConfCtrl::OnLeaveWBConfNty );
	REG_PFUN( ev_tpp_NewConfCall_Req, CTpadConfCtrl::OnNewConfCallReq );

	REG_PFUN( ev_tppSetDataServerInfo_Ind, CTpadConfCtrl::OnSetDataServerInfoInd );
	REG_PFUN( ev_tppSetDataServerInfo_Nty, CTpadConfCtrl::OnSetDataServerInfoNty );   
	REG_PFUN( ev_tpp_DataConfName_Nty, CTpadConfCtrl::OnSetDataConfNameNty );
	REG_PFUN( ev_TppMakeCall_Cmd, CTpadConfCtrl::OnSelfMakeCallCmd );   
}

void CTpadConfCtrl::OnLinkBreak(const CMessage& cMsg)
{
	m_bRecvDual = FALSE;
	m_nVideoNode = TP_INVALID_INDEX;
	m_nAudioNode = TP_INVALID_INDEX;
}

void CTpadConfCtrl::OnRecvDualNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 

	u8 uInst = cTpMsg.GetHomeplace();

	BOOL bDual = *(BOOL*)(cTpMsg.GetBody());
	PrtMsg( ev_TppIsRcvDual_Nty, emEventTypeCnsRecv, "bRcvDual: %d, Inst: %d ", bDual, uInst );

	if ( m_bRecvDual!= bDual )
	{
		m_bRecvDual = bDual;
		PostEvent( UI_CNS_RECV_DUAL_NOTIFY, m_bRecvDual, 0 ); 
	}		
}

void CTpadConfCtrl::OnStartDualCdStrmRsp( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg);    

	EmTPAddDualRcvResult emReVideo = *(EmTPAddDualRcvResult*)(cTpMsg.GetBody()); 

	if ( emReVideo == emAddDualRcvSucceed )
	{
		m_tVideoTranAddr = *(TTPCnMediaTransPort*)(cTpMsg.GetBody() + sizeof( EmTPAddDualRcvResult )*2 );

		m_nVideoNode = *(u16*)(cTpMsg.GetBody() + 
			sizeof( EmTPAddDualRcvResult ) * 2 +
			sizeof(TTPCnMediaTransPort ) * 2  );


	}


	EmTPAddDualRcvResult emReAudio = *(EmTPAddDualRcvResult*)(cTpMsg.GetBody() + sizeof( EmTPAddDualRcvResult ) ); 
	if ( emReAudio == emAddDualRcvSucceed )
	{
		m_tAudioTranAddr = *(TTPCnMediaTransPort*)(cTpMsg.GetBody() + sizeof( EmTPAddDualRcvResult )*2 + 
			sizeof(TTPCnMediaTransPort ) );

		m_nAudioNode = *(u16*)(cTpMsg.GetBody() +  sizeof( EmTPAddDualRcvResult )*2 + 
			sizeof(TTPCnMediaTransPort )*2 + sizeof(u16 ) );
	}

	u8 uInst = cTpMsg.GetHomeplace();     

	PrtMsg( ev_TppAddDualRcvAddr_Ind, emEventTypeCnsRecv, "m_nVideoNode:%d, m_nAudioNode:%d, emVideoReason:%d , emAudioReaso=%d  \
														  ( %d:emAddDualRcvSucceed,%d:emAddDualRcvFailNoDual,%d:emAddDualRcvFailIllegalPos，%d:emAddDualRcvFailNoPos, \
														  %d:emAddDualRcvFailUnKown)",m_nVideoNode, m_nAudioNode, emReVideo,emReAudio, emAddDualRcvSucceed,emAddDualRcvFailNoDual,
														  emAddDualRcvFailIllegalPos,emAddDualRcvFailNoPos,emAddDualRcvFailUnKown );


	PostEvent( UI_CNSINS_START_DUALCODESTREAM_RSP,  emReVideo , emReAudio ); 
}

void CTpadConfCtrl::OnStopDualCdStrmRsp( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 

	m_nVideoNode = TP_INVALID_INDEX;
	m_nAudioNode = TP_INVALID_INDEX;

	EmTPDeleteDualRcvResult emReVideo = *(EmTPDeleteDualRcvResult*)(cTpMsg.GetBody());

	PrtMsg( ev_TppDelDualRcvAddr_Ind, emEventTypeCnsRecv, "" );
}

void CTpadConfCtrl::OnDualCodeEnCryptKeyNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	m_tTpEncryptKey = *(TTpEncryptKey*)(cTpMsg.GetBody());

	PrtMsg( ev_tppCodecEncryptKey_Nty, emEventTypeCnsRecv, "Key:%s, EmTPEncryptType:%d, Length:%d", m_tTpEncryptKey.byKey, m_tTpEncryptKey.emTPEncryptType, m_tTpEncryptKey.byLen );

	PostEvent( UI_CNS_DUAL_KEY_NOTIFY, (WPARAM)&m_tTpEncryptKey, 0  );
}

void CTpadConfCtrl::OnConfStateNty( const CMessage &cMsg )
{    
	CTpMsg cTpMsg(&cMsg); 

	TTPCnsConfStatus tConfStatus = *reinterpret_cast<TTPCnsConfStatus*>(cTpMsg.GetBody());

	PrtMsg( ev_CnConfState_Nty, emEventTypeCnsRecv, "TTPCnsConfStatus: ConfName: %s, ConfID: %d, State: %d \
													(%d:em_CALL_IDLE, %d:em_CALL_CALLING, %d:em_CALL_CONNECTED),\
													ConfType: %d (%d:emCallType_P2P, %d:emCallType_Conf),  bMixMotive:%d  ", 
													tConfStatus.achConfName, tConfStatus.wConfID, tConfStatus.emState, 
													em_CALL_IDLE, em_CALL_CALLING, em_CALL_CONNECTED, tConfStatus.m_emCallType, emCallType_P2P, emCallType_Conf, tConfStatus.m_bMixMotive );

	m_tCnsConfStatus = tConfStatus;

	PostEvent( UI_CONFSTATE_NTY, 0, 0 ); 
}


TTPCnsConfStatus CTpadConfCtrl::GetCnsConfStatus() const
{
	return m_tCnsConfStatus;
}


void CTpadConfCtrl::SetDataServerInfoCmd( u32 dwIp )
{
	CTpMsg *pcTpMsg = m_pTpadSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( 1 );
	pcTpMsg->SetEvent( ev_tppSetDataServerInfo_Cmd );

	TTPDataConfInfo tDCInfo;
	tDCInfo.dwSerIP = dwIp;

	pcTpMsg->SetBody( &tDCInfo, sizeof(TTPDataConfInfo) );

	u16 wRet = m_pTpadSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppSetDataServerInfo_Cmd, emEventTypeCnsSend, "dwIp:%d", dwIp );
}

//白板服务器ip配置修改后通知所有客户端
void CTpadConfCtrl::OnSetDataServerInfoInd( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg);  

	m_tTPDataConfInfo = *reinterpret_cast<TTPDataConfInfo*>(cTpMsg.GetBody());
	BOOL bIsSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPDataConfInfo) );

	in_addr tAddr;
	tAddr.S_un.S_addr = m_tTPDataConfInfo.dwSerIP;
	PrtMsg( ev_tppSetDataServerInfo_Ind, emEventTypeCnsRecv, "数据会议服务器IP修改结果：%d IP:%s", bIsSuccess ,inet_ntoa(tAddr));

	PostEvent( UI_SETWBSERVERIP_NTY, (WPARAM)bIsSuccess);
}

void CTpadConfCtrl::OnSetDataServerInfoNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 

	m_tTPDataConfInfo = *reinterpret_cast<TTPDataConfInfo*>(cTpMsg.GetBody());
	in_addr tAddr;
	tAddr.S_un.S_addr = m_tTPDataConfInfo.dwSerIP;
	PrtMsg( ev_tppSetDataServerInfo_Nty, emEventTypeCnsRecv, "数据服务器配置信息 IP:%s", inet_ntoa(tAddr) );

	PostEvent( UI_TPPSETDATASERVERINFONTY );
}

void CTpadConfCtrl::OnSelfMakeCallCmd( const CMessage &cMsg )
{    
	PrtMsg( ev_TppMakeCall_Cmd, emEventTypeCmsWindow, "本端开启视频会议" );

	PostEvent( UI_SELFSTARTCONF_CMD, NULL, NULL );
}

void CTpadConfCtrl::OnSetDataConfNameNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 

	m_tWBConfStatus = *reinterpret_cast<TTPCnsConfStatus*>(cTpMsg.GetBody());

	PrtMsg( ev_tpp_DataConfName_Nty, emEventTypeCnsRecv, "点对点会议数据会议名称%s", m_tWBConfStatus.achConfName );

	PostEvent( UI_TPPSETDATACONFNAMENTY );
}


void CTpadConfCtrl::WBConfStateNty( BOOL bIsInWBConf )
{
	//告知cnc数据会议是否在会议中
	CMessage cMsg;
	u8 abyTemp[sizeof(BOOL) + 1] = {0};
	ZeroMemory(&cMsg, sizeof(CMessage));

	cMsg.event = ev_WBConfStateNty;
	cMsg.length = sizeof(BOOL);
	memcpy( abyTemp, &bIsInWBConf, sizeof(BOOL) );
	cMsg.content = abyTemp;
	PrtMsg( ev_WBConfStateNty, emEventTypeCnsSend, "bIsInWBConf:%d", bIsInWBConf );
	MsgTransDriver->DispatchMsg( &cMsg );

	//告知cns数据会议是否在会议中
	CTpMsg *pcTpMsg = m_pTpadSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( 1 );
	pcTpMsg->SetEvent( ev_tppDataConfState_Nty );
	pcTpMsg->SetBody( &bIsInWBConf, sizeof(BOOL) );

	u16 wRet = m_pTpadSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppDataConfState_Nty, emEventTypeCnsSend, "数据会议是否在会:%d" ,bIsInWBConf);

}

void CTpadConfCtrl::WBConfStartNty( bool bIsSelfStart, bool bIsSuccess  )
{
	//界面感知本端数据会议已经开启或加入成功
	PostEvent( UI_SELFSTARTWBCONFNTY, (WPARAM)bIsSuccess, (LPARAM)bIsSelfStart ); 
	PrtMsg( ev_tpp_DSIPAddr_Nty, emEventTypeCnsSend, "开启数据会议 bIsSuccess:%d bIsSelfStart:%d ",bIsSuccess , bIsSelfStart );

	//非本端开启数据会议，即为加入成功，不通知cns
	if ( !bIsSelfStart )
	{
		return;
	}

	CTpMsg *pcTpMsg = m_pTpadSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( 1 );
	pcTpMsg->SetEvent( ev_tpp_DSIPAddr_Nty );
	//pcTpMsg->SetBody( &dwIp, sizeof(u32) );

	u16 wRet = m_pTpadSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tpp_DSIPAddr_Nty, emEventTypeCnsSend, "本地开启数据会议" );

}

// void CTpadConfCtrl::NewConfCallRsp( BOOL bIsJoinWBConf )
// {
//     CTpMsg *pcTpMsg = m_pTpadSession->GetKdvMsgPtr();
//     pcTpMsg->SetUserData( 1 );
//     pcTpMsg->SetEvent( ev_tpp_NewConfCall_Rsp );
//     pcTpMsg->SetBody( &bIsJoinWBConf, sizeof(BOOL) );
//     
//     u16 wRet = m_pTpadSession->PostMsg(TYPE_TPMSG);
//     PrtMsg( ev_tpp_NewConfCall_Rsp, emEventTypeCnsSend, "新数据会议呼进来Tpad是否加入响应:%d", bIsJoinWBConf );
// }

void CTpadConfCtrl::OnJoinWBConfCmd( const CMessage &cMsg )
{

	CTpMsg cTpMsg(&cMsg);

	m_tTPDataConfInfo = *reinterpret_cast<TTPDataConfInfo*>(cTpMsg.GetBody());
	m_tWBConfStatus = *(TTPCnsConfStatus*)( cTpMsg.GetBody() + sizeof(TTPDataConfInfo) );

	in_addr tAddr;
	tAddr.S_un.S_addr = m_tTPDataConfInfo.dwSerIP;
	PrtMsg( ev_tpp_JoinWBConf_Cmd, emEventTypeCnsRecv, "加入白板会议 会议名:%s IP:%s", m_tWBConfStatus.achConfName, inet_ntoa(tAddr) );

	PostEvent( UI_JOINWBCONF_CMD );    
}

void CTpadConfCtrl::OnLeaveWBConfNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 

	m_tTPDataConfInfo = *reinterpret_cast<TTPDataConfInfo*>(cTpMsg.GetBody());
	m_tWBConfStatus = *(TTPCnsConfStatus*)( cTpMsg.GetBody() + sizeof(TTPDataConfInfo) );

	in_addr tAddr;
	tAddr.S_un.S_addr = m_tTPDataConfInfo.dwSerIP;
	PrtMsg( ev_tpp_LeaveWBConf_Nty, emEventTypeCnsRecv, "网呈会议结束，离开数据会议的IP：%s", inet_ntoa(tAddr));

	PostEvent( UI_LEAVEWBCONF_NTY );
}

void CTpadConfCtrl::OnNewConfCallReq( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 

	m_tWBConfStatus = *reinterpret_cast<TTPCnsConfStatus*>(cTpMsg.GetBody());

	PrtMsg( ev_tpp_NewConfCall_Req, emEventTypeCnsRecv, "WB新会议呼进请求Tpad加入" );

	PostEvent( UI_NEWWBCONFCALL_REQ );
}


void CTpadConfCtrl::OnCnsInfoNty( const CMessage &cMsg )
{

	CTpMsg cTpMsg(&cMsg);    
	m_tCnsInfo = *reinterpret_cast<TTPCnsInfo*>(cTpMsg.GetBody());

	PrtMsg( ev_CnCfgCnsInfo_Ind, emEventTypeCnsRecv, "获得会场名称" );

	PostEvent( UI_CONFROOMNAME_NTY);
}


u16 CTpadConfCtrl::StartDualCodeStream( const TTPCnMediaTransPort  &tVideoTransAddr , const TTPCnMediaTransPort  &tAudioTransAddr ) const
{ 	
	CTpMsg *pcTpMsg = m_pTpadSession->GetKdvMsgPtr();

	pcTpMsg->SetUserData(1);
	pcTpMsg->SetEvent( ev_TppAddDualRcvAddr_Cmd ); 
	pcTpMsg->SetBody( &tVideoTransAddr, sizeof(TTPCnMediaTransPort) );  
	pcTpMsg->CatBody( &tAudioTransAddr, sizeof(TTPCnMediaTransPort) );

	u16 wRet = m_pTpadSession->PostMsg(TYPE_TPMSG);

	in_addr tAddr;
	tAddr.S_un.S_addr = tVideoTransAddr.m_tRtpPort.m_tIP.dwIPV4;

	PrtMsg( ev_TppAddDualRcvAddr_Cmd, emEventTypeCnsSend, "VideoAddr: %s, Port: %d", inet_ntoa(tAddr), tVideoTransAddr.m_tRtpPort.m_wPort );
	return wRet;

}


u16 CTpadConfCtrl::StopDualCodeStream() const 
{   
	CTpMsg *pcTpMsg = m_pTpadSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(1);
	pcTpMsg->SetEvent( ev_TppDelDualRcvAddr_Cmd );  
	pcTpMsg->SetBody( &m_nVideoNode, sizeof(u16) );


	u16 wRet = m_pTpadSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TppDelDualRcvAddr_Cmd, emEventTypeCnsSend,"" ); 


	pcTpMsg->SetBody( &m_nAudioNode, sizeof(u16)  );
	wRet = m_pTpadSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TppDelDualRcvAddr_Cmd, emEventTypeCnsSend,"" );


	return wRet;
}

u16 CTpadConfCtrl::ReqKeyFrame( BOOL32 bForce ) const 
{
	CTpMsg *pcTpMsg = m_pTpadSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(1);
	pcTpMsg->SetEvent( ev_TppPadDualKeyFrame_Req  );  
	pcTpMsg->SetBody( &m_nVideoNode, sizeof(u16) );
	pcTpMsg->CatBody( &bForce, sizeof(BOOL32) );

	u16 wRet = m_pTpadSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TppPadDualKeyFrame_Req , emEventTypeCnsSend ,"");
	return wRet;
}