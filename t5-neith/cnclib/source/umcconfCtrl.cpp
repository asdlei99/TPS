// confCtrl.cpp: implementation of the CConfCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "umcconfCtrl.h"
#include "cncConst.h"
#include "eventoutcnssipdual.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
 
CUmcConfCtrl::CUmcConfCtrl(CCnsSession &cUmsSession)
          :CUmcConfCtrlIF(), m_pCncSession(NULL), m_tConfInfo(),m_bIsAllQuite(false),m_bIsAllMute(false),m_tConfEpInfo(),
		  m_bIsFirstPollListNty(true)							
{
	m_pCncSession = &cUmsSession;
	m_vctPollList.clear();
	
	m_nPollListFlag = 0;
    m_nSaveCfgIndex = 0;
    m_nRevCfgIndex = 0;
    m_bPackDataIndex = 0;

    BuildEventsMap();
}
 
void CUmcConfCtrl::BuildEventsMap()
{
	REG_PFUN( ev_CnConfState_Nty, CUmcConfCtrl::OnConfStateNty );

    REG_PFUN( ev_CnConfEpList_Nty, CUmcConfCtrl::OnUpdateConfCnsListNotify ); 
    REG_PFUN( ev_TppConfAMixUpdate_Nty, CUmcConfCtrl::OnUpdateConfAuxMixlistNotify ); 
    REG_PFUN( ev_TppConfAMixUpdate_Ind, CUmcConfCtrl::OnUpdateConfAuxMixlistInd ); 

	REG_PFUN( ev_TppAudMixDisListOpr_Ind, CUmcConfCtrl::OnAudMixDisListOprNotify );
	REG_PFUN( ev_Cn_ConfAMixVacSwitch_Ind, CUmcConfCtrl::OnAMixVacNotify );

    REG_PFUN( ev_TppInviteCnsByAlias_Ind, CUmcConfCtrl::OnInviteCnsRsp );
    REG_PFUN( ev_TppInviteCnsByEpId_Ind, CUmcConfCtrl::OnCallConfCnsRsp ); 

    REG_PFUN( ev_TppHangupCns_Ind, CUmcConfCtrl::OnHangupCnsInd );
    //	REG_PFUN(evtp_HungUpConf_result, OnHungUpConfRsp ); 
    // 	REG_PFUN(evtp_UpdateConfTurnlist_Notify, OnUpdateConfPolllistNotify ); 

    REG_PFUN(ev_TppConfMute_Ind, CUmcConfCtrl::OnSetMuteCnsRsp ); 
    REG_PFUN(ev_TppConfQuiet_Ind, CUmcConfCtrl::OnSetSilenceCnsRsp ); 
    
    REG_PFUN(ev_TppConfStartDual_Ind, CUmcConfCtrl::OnSetDualCnsRsp ); 
    REG_PFUN(ev_TppConfStopDual_Ind, CUmcConfCtrl::OnSetDualCnsRsp ); 

    REG_PFUN( ev_TppConfDualEp_Nty, CUmcConfCtrl::OnDualCnsNotify );  

    REG_PFUN(ev_TppConfApplySpeaker_Nty, CUmcConfCtrl::OnUpdateConfSpeakerNotify ); 
    
    REG_PFUN(ev_TppConfApplySpeaker_Ind, CUmcConfCtrl::OnSetSpokeCnsRsp ); 
    
    REG_PFUN(ev_TppChairConfInfo_Nty, CUmcConfCtrl::OnChairCnsNotify ); 

    REG_PFUN( ev_TppModuleterminalLeftConf, CUmcConfCtrl::OnCnsLeaveNotify ); 

    REG_PFUN( ev_TppUmsCommonReasonToUI_Ind, CUmcConfCtrl::OnUmsCommonReasonInd );

    //断链清空资源
    REG_PFUN(OSP_DISCONNECT, CUmcConfCtrl::OnLinkBreak); 

	//REG_PFUN( ev_CnCfgConfDis_Ind, CUmcConfCtrl::OnConfDisInd );
	
	//会议轮询
	//REG_PFUN( ev_CnCfgConfPoll_Ind, CUmcConfCtrl::OnConfPollInd );
	REG_PFUN( ev_Cn_Conf_SuspendPoll_Ind, CUmcConfCtrl::OnPollPauseInd );
	REG_PFUN( ev_Cn_UpdateConfTurnlist_Nty, CUmcConfCtrl::OnPollListNty );
	REG_PFUN( ev_Cn_UpdateConfTurnlist_Ind, CUmcConfCtrl::OnPollListInd );
	REG_PFUN( ev_CnPollStatus_Nty,  CUmcConfCtrl::OnPollStatusNty ); 

    //画面合成
    REG_PFUN( ev_Cn_RervesBrdVmp_Ind, CUmcConfCtrl::OnRervesBrdVmpInd );
    REG_PFUN( ev_Cn_SetBrdVmp_Ind, CUmcConfCtrl::OnSetBrdVmpInd );
    REG_PFUN( ev_Cn_BrdVmp_Ind, CUmcConfCtrl::OnBrdVmpInd );
    REG_PFUN( ev_Cn_BrdVmp_Ntfy, CUmcConfCtrl::OnBrdVmpNty );
    REG_PFUN( ev_Cn_SaveVmpCfg_Cmd, CUmcConfCtrl::OnSaveVmpCfgCmd );
    REG_PFUN( ev_CnSaveVmpCfg_Ind, CUmcConfCtrl::OnSaveVmpCfgInd );

	//会场选看
	REG_PFUN( ev_UMS_CNC_ByCNS_SelView_Ntfy, CUmcConfCtrl::OnSetSelViewNty);  
	//终端会场入会请求
	REG_PFUN( ev_UmsToCncJoinConf_Req, CUmcConfCtrl::OnJoinConfReq); 

    //电视墙消息通知
    REG_PFUN( ev_TpUMS_CNS_HduPlan_Nty, CUmcConfCtrl::OnHduPlanNty );	
    REG_PFUN( ev_TpHduChangeChanMode_Ind, CUmcConfCtrl::OnHduChangeModeInd );	
    REG_PFUN( ev_TpUMS_CNS_HduSetVol_Ind, CUmcConfCtrl::OnHduVolInd );	
    REG_PFUN( ev_TpUMS_CNS_HduPlay_Ind, CUmcConfCtrl::OnHduPlayInd );	
    REG_PFUN( ev_TpUMS_CNS_HduStopPlay_Ind, CUmcConfCtrl::OnHduStopPlayInd );

	REG_PFUN( ev_TppConfMute_Nty, CUmcConfCtrl::SetAllMute );
	REG_PFUN( ev_TppConfQuiet_Nty, CUmcConfCtrl::SetAllQuiet );
	//点对点323终端上报视频源类型消息
	REG_PFUN( ev_H323SendVideoInfo_Nty, CUmcConfCtrl::OnP2PH323VideoInfo );
	//点对点323终端上报当前视频源和是否可远摇
	REG_PFUN( ev_H323SendVideoFeccInfo_Nty, CUmcConfCtrl::OnP2PH323VideoFeccInfo );
	//多点323终端上报视频源类型消息
	REG_PFUN( ev_SendFeccVidSrcInfo_Nty, CUmcConfCtrl::OnMulConfH323VideoInfoNty );
    REG_PFUN( ev_SendFeccVidSrcInfo_Ind, CUmcConfCtrl::OnMulConfH323VideoInfoInd );
}

void CUmcConfCtrl::OnLinkBreak( const CMessage& cMsg )
{	
    m_tConfInfo.Clear();
    m_tConfInfo.m_wConfID = INVALID_WORD;
	m_bIsFirstPollListNty = true;
	m_vctPollList.clear();
	m_nPollListFlag = 0;
    m_vctBrdVmpInfo.clear();
    m_tVmpCurrentCfg.Clear();

	m_tTPSelViewNtfy.Clear();
	m_tDiscussListOpr.Clear();
	m_tpConfEpInfo.m_wConfID = TP_INVALID_INDEX;
	m_tpConfEpInfo.m_tCallAddr.Clear();
	m_tpConfEpInfo.m_Index = TP_INVALID_INDEX;
	m_tpConfEpInfo.m_bPermit = FALSE;

    m_nSaveCfgIndex = 0;
    m_nRevCfgIndex = 0;

    m_bPackDataIndex = 0;
    memset(m_tHduPlanPackData,0,sizeof(m_tHduPlanPackData));

	m_bIsAllQuite = false;
	m_bIsAllMute = false; 

	m_tConfEpInfo.Clear();
	m_vctConf323VidInfo.clear();

    PrtMsg( OSP_DISCONNECT, emEventTypeCnsRecv,"[CUmcConfCtrl::OnLinkBreak]清空会议信息" );
}

u16 CUmcConfCtrl::GetConf( TCMSConf &tplConfList )  const
{      
    tplConfList = m_tConfInfo; 

	return NO_ERROR;
} 

u16 CUmcConfCtrl::GetConfCnsList( vector<TCnsInfo> &vctConfCnsList )  const
{ 
    vctConfCnsList = m_tConfInfo.m_vctCnsList;
    return NO_ERROR;	
}


u16 CUmcConfCtrl::GetConfAudmixList(  TAuxMixList&tConfAudmixList )  const
{	 
    tConfAudmixList = m_tConfInfo.m_tAudmixList;
    return NO_ERROR;	
}


// u16 CUmcConfCtrl::GetConfPollList(   TplArray<u16> &tplConfPollList )  const
// { 
// 	
// 	tplConfPollList = m_tConfInfo.m_tplPollList ;
//     return NO_ERROR;	
// }

 

u16 CUmcConfCtrl::InviteCnsReq( const TTpCallAddr &tAddr )  
{
	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}

    CTpMsg *pcTpMsg = m_pCncSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pCncSession->GetInst() );
    pcTpMsg->SetEvent( ev_TppInviteCnsByAlias_Cmd );
    pcTpMsg->SetBody( &tAddr, sizeof(TTpCallAddr) );

    u16 wRet = m_pCncSession->PostMsg(TYPE_TPMSG); 
	
    in_addr inAddr;
    inAddr.S_un.S_addr = tAddr.m_dwIP;
	PrtMsg( ev_TppInviteCnsByAlias_Cmd,emEventTypeCnsSend,"m_tAlias: %s, m_tE164: %s, m_dwIP: %s, m_bAliasIP: %d",
		tAddr.m_tAlias.m_abyAlias, tAddr.m_tE164.m_abyAlias, inet_ntoa(inAddr), tAddr.m_bAliasIP  );

	return  wRet;
}


u16 CUmcConfCtrl::CallConfCnsReq( const TConfEpID &tEp )
{
    if ( NULL == m_pCncSession ) 
    {
        return ERR_CMS;
    }
    
    CTpMsg *pcTpMsg = m_pCncSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pCncSession->GetInst() );
    pcTpMsg->SetEvent( ev_TppInviteCnsByEpId_Cmd );
    pcTpMsg->SetBody( &tEp.m_wEpID, sizeof(u16) );
    
    u16 wRet = m_pCncSession->PostMsg(TYPE_TPMSG); 
    
    PrtMsg( ev_TppInviteCnsByEpId_Cmd, emEventTypeCnsSend, "confID=%d, CnsID=%d", tEp.m_wConfID,tEp.m_wEpID );
    
	return 0 ;//wRe;
}


u16 CUmcConfCtrl::HangupConfReq(  )
{
	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	
    
    CTpMsg *pcTpMsg = m_pCncSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pCncSession->GetInst() );
    pcTpMsg->SetEvent( ev_TppHangupConf_Cmd ); 
    
    u16 wRet = m_pCncSession->PostMsg(TYPE_TPMSG); 
    
   	PrtMsg( ev_TppHangupConf_Cmd, emEventTypeCnsSend," " );
 

	return  wRet;
}


u16 CUmcConfCtrl::HangupCNSReq( const TConfEpID &tConfEpInfo )
{
	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	
    CTpMsg *pcTpMsg = m_pCncSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pCncSession->GetInst() );
    pcTpMsg->SetEvent( ev_TppHangupCns_Cmd ); 
    pcTpMsg->SetBody( &tConfEpInfo.m_wEpID, sizeof(u16) );
    
    u16 wRet = m_pCncSession->PostMsg(TYPE_TPMSG); 
    
   	PrtMsg( ev_TppHangupCns_Cmd, emEventTypeCnsSend,"CnsID = %d",tConfEpInfo.m_wEpID );
	
	return  wRet;
}

//摄像机远摇
u16 CUmcConfCtrl::SetFeccConfEpInfo( const TConfEpID &tConfEpInfo )
{
	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	m_tConfEpInfo = tConfEpInfo;

	//更新界面远摇会场视频源信息
	if (m_tConfInfo.m_emConfType != emCallType_P2P)
	{
		m_tVidFeccInfo.Clear();
		for (int i = 0 ; i < m_vctConf323VidInfo.size() ; i++)
		{
			if (m_vctConf323VidInfo.at(i).m_wEpID == m_tConfEpInfo.m_wEpID)
			{
				m_tVidFeccInfo = m_vctConf323VidInfo.at(i);
				break;
			}
		}
	}
	else
	{
		if (m_tConfEpInfo.m_wEpID == TP_INVALID_INDEX)
		{
			m_tVidFeccInfo.Clear();
		}
	}
	PostEvent( UI_CNS_323VEDIOSOR_NOTIFY, (WPARAM)(&m_tVidFeccInfo), NULL );

	return  NO_ERROR;
}

u16 CUmcConfCtrl::GetFeccConfEpInfo( TConfEpID &tConfEpInfo )
{
	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	tConfEpInfo = m_tConfEpInfo;
	return  NO_ERROR;
}

u16 CUmcConfCtrl::ChangeFeccSource(u8 SourceId)
{
	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	CTpMsg *pcTpMsg = m_pCncSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pCncSession->GetInst() );

	pcTpMsg->SetEvent( ev_Cn_FeccChangeSrc_Cmd ); 
	pcTpMsg->SetBody( &m_tConfEpInfo, sizeof(m_tConfEpInfo) );
	pcTpMsg->CatBody( &SourceId, sizeof(u8) );

	u16 wRet = m_pCncSession->PostMsg(TYPE_TPMSG); 
	PrtMsg( ev_Cn_FeccChangeSrc_Cmd, emEventTypeCnsSend, "ChangeSource:SourceId = %d" ,SourceId);
	return  NO_ERROR;
}

u16 CUmcConfCtrl::SetFeccCamPT( EmDirection emDirection, EmCnAction emCnAction )
{
	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}

	CTpMsg *pcTpMsg = m_pCncSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pCncSession->GetInst() );
	pcTpMsg->SetEvent( ev_Cn_FeccCamPT_Cmd ); 
	pcTpMsg->SetBody( &m_tConfEpInfo, sizeof(m_tConfEpInfo) );
	pcTpMsg->CatBody( &emDirection, sizeof(EmDirection) );
	pcTpMsg->CatBody( &emCnAction, sizeof(EmCnAction) );

	u16 wRet = m_pCncSession->PostMsg(TYPE_TPMSG); 
	PrtMsg( ev_Cn_FeccCamPT_Cmd, emEventTypeCnsSend, "Direction:%d, Action:%d", emDirection, emCnAction );
	return wRet;
}

u16 CUmcConfCtrl::SetFeccCamView( EmZoom emZoom, EmCnAction emCnAction )
{
	CTpMsg *pcTpMsg = m_pCncSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pCncSession->GetInst() );

	pcTpMsg->SetEvent( ev_Cn_FeccCamZoom_Cmd ); 
	pcTpMsg->SetBody( &m_tConfEpInfo, sizeof(m_tConfEpInfo) );
	pcTpMsg->CatBody( &emZoom, sizeof(EmZoom) );
	pcTpMsg->CatBody( &emCnAction, sizeof(EmCnAction) );

	u16 wRet = m_pCncSession->PostMsg(TYPE_TPMSG); 
	PrtMsg( ev_Cn_FeccCamZoom_Cmd, emEventTypeCnsSend, "Zoom:%d, Action:%d", emZoom, emCnAction );
	return wRet;
}

u16 CUmcConfCtrl::SetFeccCamBright( EmPanCamBright emPanCamBright, EmCnAction emCnAction )
{
	CTpMsg *pcTpMsg = m_pCncSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pCncSession->GetInst() );

	pcTpMsg->SetEvent( ev_Cn_FeccCamBackLight_Cmd ); 
	pcTpMsg->SetBody( &m_tConfEpInfo, sizeof(m_tConfEpInfo) );
	pcTpMsg->CatBody( &emPanCamBright, sizeof(EmPanCamBright) );
	pcTpMsg->CatBody( &emCnAction, sizeof(EmCnAction) );

	u16 wRet = m_pCncSession->PostMsg(TYPE_TPMSG); 
	PrtMsg( ev_Cn_FeccCamBackLight_Cmd, emEventTypeCnsSend, "PanCamBright:%d, Action:%d", emPanCamBright, emCnAction );
	return wRet;
}

u16 CUmcConfCtrl::SetFeccCamFocus( EmFocus emFocus, EmCnAction emCnAction )
{
	CTpMsg *pcTpMsg = m_pCncSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pCncSession->GetInst() );

	pcTpMsg->SetEvent( ev_Cn_FeccCamFocus_Cmd ); 
	pcTpMsg->SetBody( &m_tConfEpInfo, sizeof(m_tConfEpInfo) );
	pcTpMsg->CatBody( &emFocus, sizeof(EmFocus) );
	pcTpMsg->CatBody( &emCnAction, sizeof(EmCnAction) );

	u16 wRet = m_pCncSession->PostMsg(TYPE_TPMSG); 
	PrtMsg( ev_Cn_FeccCamFocus_Cmd, emEventTypeCnsSend, "Focus:%d, Action:%d", emFocus, emCnAction );
	return wRet;
}

u16 CUmcConfCtrl::SetFeccCamAotoFocus()
{
	CTpMsg *pcTpMsg = m_pCncSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pCncSession->GetInst() );

	pcTpMsg->SetEvent( ev_Cn_FeccCamAutoFocus_Cmd ); 
	pcTpMsg->SetBody( &m_tConfEpInfo, sizeof(m_tConfEpInfo) );

	u16 wRet = m_pCncSession->PostMsg(TYPE_TPMSG); 
	PrtMsg( ev_Cn_FeccCamAutoFocus_Cmd, emEventTypeCnsSend, "AotoFocus" );
	return wRet;
}


u16 CUmcConfCtrl::RemoveCNSReq( const TConfEpID &tConfEpInfo )
{
	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	
	
	return 0; 
}


u16 CUmcConfCtrl::SetSpokeCnsReq( const TConfEpID &tConfEpInfo )  
{
	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
    pMsg->SetUserData( m_pCncSession->GetInst() );
	pMsg->SetEvent( ev_TppConfApplySpeaker_Cmd );
	pMsg->SetBody(&tConfEpInfo,sizeof(tConfEpInfo));

	u16 awEvent[1];
    awEvent[0] = ev_TppConfApplySpeaker_Ind;   

	u16 wRe = m_pCncSession->PostCommand( this,awEvent,1,TYPE_TPMSG );
 
	
	PrtMsg( ev_TppConfApplySpeaker_Cmd, emEventTypeCnsSend, "confID=%d, CNSID=%d", tConfEpInfo.m_wConfID,tConfEpInfo.m_wEpID );
	
    return wRe;
    
}



u16 CUmcConfCtrl::SetQuietCnsReq( const TConfEpID &tConfEpInfo, BOOL32 bQuiet)
{
    if ( NULL == m_pCncSession ) 
    {
        return ERR_CMS;
    }
    
    CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
    pMsg->SetUserData( m_pCncSession->GetInst() );
    pMsg->SetEvent( ev_TppConfQuiet_Cmd );
    pMsg->SetBody( &tConfEpInfo,sizeof(TConfEpID) );
    pMsg->CatBody(&bQuiet,sizeof(BOOL32));
    
    u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 
    
    PrtMsg( ev_TppConfQuiet_Cmd, emEventTypeCnsSend, "confID=%d , cnsID=%d,isStart=%d", 
        tConfEpInfo.m_wConfID,tConfEpInfo.m_wEpID,bQuiet); 
	return wRe; 
}


u16 CUmcConfCtrl::SetMuteCnsReq( const TConfEpID &tConfEpInfo , BOOL32 bMute)
{
    if ( NULL == m_pCncSession ) 
    {
        return ERR_CMS;
    }
    
    CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
    pMsg->SetUserData( m_pCncSession->GetInst() );
    pMsg->SetEvent( ev_TppConfMute_Cmd );
    pMsg->SetBody( &tConfEpInfo,sizeof(TConfEpID) );
    pMsg->CatBody(&bMute,sizeof(BOOL32));
    
    u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 
    
    PrtMsg( ev_TppConfMute_Cmd, emEventTypeCnsSend, "confID=%d , cnsID=%d,isStart=%d", 
        tConfEpInfo.m_wConfID,tConfEpInfo.m_wEpID,bMute); 
	return wRe; 
}


u16 CUmcConfCtrl::SetDualCnsReq( const TConfEpID &tConfEpInfo, BOOL32 bStart )
{
    if ( NULL == m_pCncSession ) 
    {
        return ERR_CMS;
    }
    
    u16 wCmd = ev_TppConfStopDual_Cmd; 
    if ( bStart )
    {
        wCmd = ev_TppConfStartDual_Cmd;
    }

    CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
    pMsg->SetUserData( m_pCncSession->GetInst() );
    pMsg->SetEvent( wCmd );
    pMsg->SetBody( &tConfEpInfo,sizeof(TConfEpID) );
     
    
    u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 
    
    PrtMsg( wCmd, emEventTypeCnsSend, "confID=%d , cnsID=%d ", 
        tConfEpInfo.m_wConfID,tConfEpInfo.m_wEpID ); 
	return wRe; 
}



u16 CUmcConfCtrl::UpdateAudMixListReq( const TConfAuxMixInfo &tMixInfoList )
{
	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	
	CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
	pMsg->SetUserData( m_pCncSession->GetInst() );
	pMsg->SetEvent( ev_TppConfAMixUpdate_Cmd );
	pMsg->SetBody( &tMixInfoList, sizeof(TConfAuxMixInfo) );
 
	u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 
	
	PrtMsg( ev_TppConfAMixUpdate_Cmd, emEventTypeCnsSend, "confID= %d, bStart= %d bVacOn=%d", tMixInfoList.m_wConfID, tMixInfoList.m_bStart, tMixInfoList.m_bVacOn );

	PrtMsg( "AudListCmd :%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",  tMixInfoList.m_atAuxMixList.m_awList[0], tMixInfoList.m_atAuxMixList.m_awList[1], 
		tMixInfoList.m_atAuxMixList.m_awList[2], tMixInfoList.m_atAuxMixList.m_awList[3], tMixInfoList.m_atAuxMixList.m_awList[4],tMixInfoList.m_atAuxMixList.m_awList[5], tMixInfoList.m_atAuxMixList.m_awList[6],
		tMixInfoList.m_atAuxMixList.m_awList[7], tMixInfoList.m_atAuxMixList.m_awList[8], tMixInfoList.m_atAuxMixList.m_awList[9],tMixInfoList.m_atAuxMixList.m_awList[10], tMixInfoList.m_atAuxMixList.m_awList[11],
		tMixInfoList.m_atAuxMixList.m_awList[12], tMixInfoList.m_atAuxMixList.m_awList[13], tMixInfoList.m_atAuxMixList.m_awList[14],tMixInfoList.m_atAuxMixList.m_awList[15], tMixInfoList.m_atAuxMixList.m_awList[16],
		tMixInfoList.m_atAuxMixList.m_awList[17], tMixInfoList.m_atAuxMixList.m_awList[18], tMixInfoList.m_atAuxMixList.m_awList[19],tMixInfoList.m_atAuxMixList.m_awList[20], tMixInfoList.m_atAuxMixList.m_awList[21],
		tMixInfoList.m_atAuxMixList.m_awList[22], tMixInfoList.m_atAuxMixList.m_awList[23], tMixInfoList.m_atAuxMixList.m_awList[24],tMixInfoList.m_atAuxMixList.m_awList[25], tMixInfoList.m_atAuxMixList.m_awList[26]);		

	
	return wRe;
}

u16 CUmcConfCtrl::AudMixDisListOprCmd( const TDiscussListOpr &tDisListOpr )
{
	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
	pMsg->SetUserData( m_pCncSession->GetInst() );
	pMsg->SetEvent( ev_TppAudMixDisListOpr_Cmd );
	pMsg->SetBody( &tDisListOpr, sizeof(TDiscussListOpr) );

	u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 

	PrtMsg( ev_TppAudMixDisListOpr_Cmd, emEventTypeCnsSend, "confID= %d,  m_wNum= %d, OprType= %d (%d:DisListOpr_Add, %d:em_DisListOpr_Del ) m_awEpId:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		tDisListOpr.m_wConfId, tDisListOpr.m_wNum, tDisListOpr.m_emOprType, em_DisListOpr_Add, em_DisListOpr_Del, tDisListOpr.m_awEpId[0],tDisListOpr.m_awEpId[1],tDisListOpr.m_awEpId[2],
		tDisListOpr.m_awEpId[3],tDisListOpr.m_awEpId[4],tDisListOpr.m_awEpId[5],tDisListOpr.m_awEpId[6],tDisListOpr.m_awEpId[7],tDisListOpr.m_awEpId[8],tDisListOpr.m_awEpId[9],tDisListOpr.m_awEpId[10],
		tDisListOpr.m_awEpId[11],tDisListOpr.m_awEpId[12],tDisListOpr.m_awEpId[13],tDisListOpr.m_awEpId[14],tDisListOpr.m_awEpId[15],tDisListOpr.m_awEpId[16],tDisListOpr.m_awEpId[17],tDisListOpr.m_awEpId[18],
		tDisListOpr.m_awEpId[19],tDisListOpr.m_awEpId[20],tDisListOpr.m_awEpId[21],tDisListOpr.m_awEpId[22],tDisListOpr.m_awEpId[23],tDisListOpr.m_awEpId[24],tDisListOpr.m_awEpId[25],tDisListOpr.m_awEpId[26]	
	);

	return wRe;
}


u16 CUmcConfCtrl::AuxMixVacOpr( const TConfAuxMixVacOpr tConfAuxMixVacOpr)
{
	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
	pMsg->SetUserData( m_pCncSession->GetInst() );
	pMsg->SetEvent( ev_Cn_ConfAMixVacSwitch_Cmd );
	pMsg->SetBody( &tConfAuxMixVacOpr, sizeof(TConfAuxMixVacOpr) );

	u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 

	PrtMsg( ev_Cn_ConfAMixVacSwitch_Cmd, emEventTypeCnsSend, "confID= %d, bVacOn= %d",tConfAuxMixVacOpr.m_wConfID, tConfAuxMixVacOpr.m_bVacOn );

	return wRe;
}

u16 CUmcConfCtrl::UpdatePollListReq( const TConfTurnInfo &tTurnInfoList )
{
   	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	
// 	CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
// 	pMsg->SetEvent( evtp_UpdateTurn_cmd );
// 	pMsg->SetBody( &tTurnInfoList,sizeof(TConfTurnInfo) );
// 	
// 	u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 
// 	
// 	PrtMsg( evtp_UpdateTurn_cmd, emEventTypeUmsSend, "confID=%d, PollCount=%d", tTurnInfoList.m_wConfID,tTurnInfoList.m_atTurnList.m_wNum);
	
	return 0 ;//wRe;
}



u16 CUmcConfCtrl::StartAuxMixReq( const u16 wConfID )
{
   	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	
// 	CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
// 	pMsg->SetEvent( ev_TppConfAMixUpdate_Cmd );
// 	pMsg->SetBody( &wConfID,sizeof(u16) );
//     BOOL32 bStart = TRUE;
// 	pMsg->CatBody(&bStart,sizeof(BOOL32));
// 	u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 
// 	
//  	PrtMsg( evtp_StartAuxMix_cmd, emEventTypeUmsSend, "confID=%d ", wConfID);
	
	return 0 ; //wRe;
}

u16 CUmcConfCtrl::StopAuxMixReq( const u16 wConfID )
{
    if ( NULL == m_pCncSession ) 
    {
        return ERR_CMS;
    }
    
//     CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
//     pMsg->SetEvent( evtp_UpdateAudMixInfo_cmd );
//     pMsg->SetBody( &wConfID,sizeof(u16) );
//     BOOL32 bStart = FALSE;
//     pMsg->CatBody(&bStart,sizeof(BOOL32));
//     u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 
    
//    PrtMsg( evtp_StartAuxMix_cmd, emEventTypeUmsSend, "confID=%d ", wConfID);
    
	return 0 ; //wRe; 
}


u16 CUmcConfCtrl::StartPollReq( const u16 wConfID )
{
	if ( NULL == m_pCncSession ) 
	{
		return ERR_CMS;
	}
	
// 	CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
// 	pMsg->SetEvent( evtp_StartTurn_cmd );
// 	pMsg->SetBody( &wConfID,sizeof(u16) );
// 	
// 	u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 
// 	
// 	PrtMsg( evtp_StartTurn_cmd, emEventTypeUmsSend, "confID=%d ", wConfID);
	
	return 0;//wRe;
}

u16 CUmcConfCtrl::StopPollReq( const u16 wConfID )
{	
	//wait 
	return NO_ERROR;
}


 
void CUmcConfCtrl::OnConfStateNty( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    TTPCnsConfStatus tConfStatus = *reinterpret_cast<TTPCnsConfStatus*>(cTpMsg.GetBody()); 
    
    if ( tConfStatus.emState == em_CALL_CONNECTED )
    {
        m_tConfInfo.m_wConfID = tConfStatus.wConfID;
        m_tConfInfo.m_emConfType = tConfStatus.m_emCallType;
        _snprintf( m_tConfInfo.m_achConfName , sizeof( m_tConfInfo.m_achConfName ), tConfStatus.achConfName );
        //m_tConfInfo.m_tStartTime = tConfStatus.m_tmStartTime;
        //tConfStatus.m_tmStartTime值改为会议持续时间，与本地当前时间换算后，得到相对本地的开始会议时间传出 dyy 2013-9-11
        time_t tCurTime = time(NULL);
        m_tConfInfo.m_tStartTime = (long)difftime( tCurTime, tConfStatus.m_dwStartTime ); 
        //防止time_t越界
        if ( m_tConfInfo.m_tStartTime < 0 )
        {
            m_tConfInfo.m_tStartTime = 0;
        }
    }
    else
    {
        m_tConfInfo.Clear();
        m_tConfInfo.m_wConfID = INVALID_WORD;
       
        m_vctBrdVmpInfo.clear(); //结会时清空合成器信息
        m_tVmpCurrentCfg.Clear();
        m_vctConf323VidInfo.clear();
    } 
 
    //em_CALL_CALLING状态界面不需要刷新
	if ( tConfStatus.emState != em_CALL_CALLING )
	{
		PostEvent( UI_CNS_CONFSTATE_NOTIFY, NULL, NULL );
	}

}
 
/*
//挂断会议结果
enum EmTpDropConfRet
{
TP_DropConf_Success,
TP_DropConf_ConfUnExit,	//会议模板不存在
};*/
void CUmcConfCtrl::OnHungUpConfRsp( const CMessage& cMsg )
{  
// 	CTpMsg kdvMsg(&cMsg);
// 	u16 wConfID = * reinterpret_cast<u16*>( kdvMsg.GetBody() );
// 	EmTpDropConfRet emRe = *reinterpret_cast<EmTpDropConfRet*>( kdvMsg.GetBody() + sizeof(u16) );
// 
//     PrtMsg(evtp_HungUpConf_result,emEventTypeUmsRecv,"ConfID=%d, errCode=%d ( %d:Success, %d:ConfUnExit )",
//                      wConfID, emRe,TP_DropConf_Success,TP_DropConf_ConfUnExit) ; 
//     
//     u32 dwErrID = NO_ERROR;
//     if ( emRe == TP_DropConf_ConfUnExit )
//     {
//         dwErrID= ERR_UMC_HUNGUP_CONF_UNEXIST;
//     }
//     else
//     {  
//             
//        PrtMsg(evtp_HungUpConf_result,emEventTypeUmsRecv,"[CConfCtrl::OnHungUpConfRsp] umcLib 删除 ConfID=%d 的会议", wConfID ) ; 
//         
//     }
   
//	PostEvent(UI_UMS_HANGUP_CONF_RSP,wConfID,dwErrID);
}


void CUmcConfCtrl::OnHangupCnsInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);  

    u16 wCnsId = *reinterpret_cast<u16*>(cTpMsg.GetBody()); 
    EmCnsCallReason emReason = *reinterpret_cast<EmCnsCallReason*>(cTpMsg.GetBody() + sizeof(u16) );
    
    PrtMsg( ev_TppHangupCns_Ind, emEventTypeCnsRecv, "CnsId: %d, EmCnsCallReason: %d",wCnsId, emReason );   
}


/*
//呼叫结果
enum EmCnsCallReason	
{
EmCnsCallReason_success,
EmCnsCallReason_hungup,			//对端不接受或者主动挂断
EmCnsCallReason_Unreachable,	//对端不在线，无法呼叫
EmCnsCallReason_resourcefull,	//对端无可用资源
EmCnsCallReason_dstnotfind,		//目标不存在
EmCnsCallReason_Busy,			//对端忙
EmCnsCallReason_Local,			//本地原因
EmCnsCallReason_NoConf,			//会议不存在
EmCnsCallReason_Exist,			//对端已在本会议中
EmCnsCallReason_Rejected,		//对端拒绝
EmCnsCallReason_peerhungup,		//对端挂断
EmCnsCallReason_Abnormal,       //本地掉线挂断
EmCnsCallReason_PeerAbnormal,   //对端掉线挂断
EmCnsCallReason_unknown,   
};
*/
void CUmcConfCtrl::OnInviteCnsRsp( const CMessage& cMsg )
{   

	CTpMsg kdvMsg(&cMsg);

	TTpCallAddr tInviteInfo = * reinterpret_cast<TTpCallAddr*>( kdvMsg.GetBody() );

	EmCnsCallReason emRe = * reinterpret_cast<EmCnsCallReason*>( kdvMsg.GetBody() + sizeof(TTpCallAddr) );

    PrtMsg( ev_TppInviteCnsByAlias_Ind, emEventTypeCnsRecv," m_tAlias=%s, m_tE164=%s, errCode=%d ( \
%d:success, %d:hungup, %d:Unreachable, %d:resourcefull, %d:dstnotfind, %d:Busy, %d:Local, %d:NoConf, %d:Existed, \
%d:Rejected, %d:peerhungup, %d:Abnormal, %d:PeerAbnormal, %d:ConfOver, %d:cncallexception, %d:ConfExist, %d:unknown )",
                                                        tInviteInfo.m_tAlias.m_abyAlias, tInviteInfo.m_tE164.m_abyAlias, emRe,
                                                        EmCnsCallReason_success, EmCnsCallReason_hungup, 
                                                        EmCnsCallReason_Unreachable, EmCnsCallReason_resourcefull, EmCnsCallReason_dstnotfind,
                                                        EmCnsCallReason_Busy, EmCnsCallReason_Local,EmCnsCallReason_NoConf,EmCnsCallReason_Exist,
														EmCnsCallReason_Rejected, EmCnsCallReason_peerhungup, EmCnsCallReason_Abnormal, EmCnsCallReason_PeerAbnormal,
														EmCnsCallReason_ConfOver, EmCnsCallReason_cncallexception, EmCnsCallReason_ConfExist, EmCnsCallReason_unknown);
    u32 dwErrID = NO_ERROR;
    switch( emRe )
    {
    case EmCnsCallReason_hungup:
        dwErrID = ERR_UMC_CALLCNS_HUNGUP;
        break;
    case EmCnsCallReason_Unreachable:
        dwErrID = ERR_CMS_CALLCNS_UNREACHABLE;
        break;
    case EmCnsCallReason_resourcefull:
        dwErrID = ERR_UMC_CALLCNS_RESOURCE_FULL;
        break;
    case EmCnsCallReason_dstnotfind:
        dwErrID = ERR_UMC_CALLCNS_DST_NOT_FOUND;
        break;
    case EmCnsCallReason_Busy:
        dwErrID = ERR_UMC_CALLCNS_BUSY;
        break;
    case EmCnsCallReason_Local:
        dwErrID = ERR_UMC_CALLCNS_LOCAL;
        break;
    case EmCnsCallReason_NoConf:
        dwErrID = ERR_CMS_CALLCNS_NO_CONF;
        break;
    case EmCnsCallReason_Exist:
        dwErrID = ERR_UMC_CALLCNS_CNS_EXIST;
        break;
	case EmCnsCallReason_Rejected:
        dwErrID = ERR_UMC_CALLCNS_CNS_REJECTED;
        break;
	case EmCnsCallReason_peerhungup:
        dwErrID = ERR_UMC_CALLCNS_CNS_PEERHUNGUP;
        break;
	case EmCnsCallReason_Abnormal:
        dwErrID = ERR_UMC_CALLCNS_CNS_ABNORMAL;
        break;
	case EmCnsCallReason_PeerAbnormal:
        dwErrID = ERR_UMC_CALLCNS_CNS_PEERABNORMAL;
        break;
	case EmCnsCallReason_ConfOver:
        dwErrID = ERR_UMC_CALLCNS_CNS_CONFOVER;
        break;
	case EmCnsCallReason_cncallexception:
        dwErrID = ERR_UMC_CALLCNS_CNS_CALLEXCEPTION;
        break;
	case EmCnsCallReason_ConfExist:
        dwErrID = ERR_UMC_CALLCNS_CNS_CONFEXIST;
        break;
	case EmCnsCallReason_unknown:
		dwErrID = ERR_UMC_CALLCNS_CNS_UNKNOWN;
        break;
	default:
		break;
    }
   
	PostEvent( UI_UMS_INVITE_CNS_RSP, (WPARAM)&tInviteInfo, dwErrID );
} 

 
void CUmcConfCtrl::OnCallConfCnsRsp( const CMessage& cMsg )
{
    CTpMsg kdvMsg(&cMsg);

    u16 wID = * reinterpret_cast<u16*>( kdvMsg.GetBody() );
    
    EmCnsCallReason emRe = * reinterpret_cast<EmCnsCallReason*>( kdvMsg.GetBody() + sizeof(u16) );
     
    TCnsInfo *pTCnsInfo = m_tConfInfo.GetCnsInfoByID( wID );
    if ( pTCnsInfo == NULL )
    {
        PrtMsg( ev_TppInviteCnsByEpId_Ind,emEventTypeCnsRecv," EpID=%d, 会议中不存在该ID",  wID );    
        return;
    }
     
    
    CString cnsInfo;
    cnsInfo.Format("%s",pTCnsInfo->m_achRoomName );
    
    PrtMsg( ev_TppInviteCnsByEpId_Ind,emEventTypeCnsRecv," EPAlias=%s, errCode=%d ( \
%d:success, %d:hungup, %d:Unreachable, %d:resourcefull, %d:dstnotfind, %d:Busy, %d:LocalReason, %d:NoConf, %d:Existe \
%d:Rejected, %d:peerhungup, %d:Abnormal, %d:PeerAbnormal, %d:ConfOver, %d:cncallexception, %d:ConfExist, %d:unknown )",
        cnsInfo, emRe,
        EmCnsCallReason_success, EmCnsCallReason_hungup, 
        EmCnsCallReason_Unreachable, EmCnsCallReason_resourcefull, EmCnsCallReason_dstnotfind,
        EmCnsCallReason_Busy, EmCnsCallReason_Local,EmCnsCallReason_NoConf,EmCnsCallReason_Exist,
		EmCnsCallReason_Rejected, EmCnsCallReason_peerhungup, EmCnsCallReason_Abnormal, EmCnsCallReason_PeerAbnormal,
		EmCnsCallReason_ConfOver, EmCnsCallReason_cncallexception, EmCnsCallReason_ConfExist, EmCnsCallReason_unknown);
    u32 dwErrID = NO_ERROR;
    switch( emRe )
    {
    case EmCnsCallReason_hungup:
        dwErrID = ERR_UMC_CALLCNS_HUNGUP;
        break;
    case EmCnsCallReason_Unreachable:
        dwErrID = ERR_CMS_CALLCNS_UNREACHABLE;
        break;
    case EmCnsCallReason_resourcefull:
        dwErrID = ERR_UMC_CALLCNS_RESOURCE_FULL;
        break;
    case EmCnsCallReason_dstnotfind:
        dwErrID = ERR_UMC_CALLCNS_DST_NOT_FOUND;
        break;
    case EmCnsCallReason_Busy:
        dwErrID = ERR_UMC_CALLCNS_BUSY;
        break;
    case EmCnsCallReason_Local:
        dwErrID = ERR_UMC_CALLCNS_LOCAL;
        break;
    case EmCnsCallReason_NoConf:
        dwErrID = ERR_CMS_CALLCNS_NO_CONF;
        break;
    case EmCnsCallReason_Exist:
        dwErrID = ERR_UMC_CALLCNS_CNS_EXIST;
        break;
	case EmCnsCallReason_Rejected:
        dwErrID = ERR_UMC_CALLCNS_CNS_REJECTED;
        break;
	case EmCnsCallReason_peerhungup:
        dwErrID = ERR_UMC_CALLCNS_CNS_PEERHUNGUP;
        break;
	case EmCnsCallReason_Abnormal:
        dwErrID = ERR_UMC_CALLCNS_CNS_ABNORMAL;
        break;
	case EmCnsCallReason_PeerAbnormal:
        dwErrID = ERR_UMC_CALLCNS_CNS_PEERABNORMAL;
        break;
	case EmCnsCallReason_ConfOver:
        dwErrID = ERR_UMC_CALLCNS_CNS_CONFOVER;
        break;
	case EmCnsCallReason_cncallexception:
        dwErrID = ERR_UMC_CALLCNS_CNS_CALLEXCEPTION;
        break;
	case EmCnsCallReason_ConfExist:
        dwErrID = ERR_UMC_CALLCNS_CNS_CONFEXIST;
        break;
	case EmCnsCallReason_unknown:
		dwErrID = ERR_UMC_CALLCNS_CNS_UNKNOWN;
        break;
	default:
		break;
    }
    
	PostEvent( UI_UMS_INVITE_CNS_RSP, (WPARAM)&cnsInfo, dwErrID );
}
 
void CUmcConfCtrl::OnUpdateConfCnsListNotify( const CMessage& cMsg )
{   
    CTpMsg kdvMsg(&cMsg);
    BOOL bRefreshUI = FALSE;

	
    TConfCnsInfo tConfCns = *reinterpret_cast<TConfCnsInfo*>( kdvMsg.GetBody() );
/*    
    PrtMsg( evtp_UpdateConfCnsList_Notify,emEventTypeUmsRecv,"ConfID=%d, CNS Count=%d, operateType=%d (0:Add, 1: Del, 2: Update ) ",
		                                                         tConfCns.m_wConfID, tConfCns.m_wNum,tConfCns.m_emOpr);

//#ifdef _DEBUG
    for ( int j = 0; j< tConfCns.m_wNum; j++ )
    {
        PrtMsg("\n[CConfCtrl::OnUpdateConfCnsListNotify]msginfo: confID=%d ,cnsID= %d ,cnsAliars=%s, bOnLine=%d \n",tConfCns.m_wConfID,
            tConfCns.m_tConfCnsList[j].m_wEpID,
            tConfCns.m_tConfCnsList[j].m_achRoomName,tConfCns.m_tConfCnsList[j].m_bOnline);
      }
//#endif
*/

	if ( tConfCns.m_wNum <= 0 || tConfCns.m_wNum > TP_REFRESH_LIST_THREE ) 
	{  
		PrtMsg("\n[CConfCtrl::OnUpdateConfCnsListNotify]msginfo: confID=%d, m_wNum =%d , m_wNum 非法， return\n", 
			tConfCns.m_wConfID, tConfCns.m_wNum );
		return;
	}

  
	u16 wAddNum = tConfCns.m_wNum;
	switch( tConfCns.m_emOpr ) 
	{
	case tp_OprType_Del:			//删除
        {   
            bRefreshUI = TRUE;
			for ( int i = 0; i< tConfCns.m_wNum; i++ )
			{   
                vector<TCnsInfo>::iterator iter = m_tConfInfo.m_vctCnsList.begin();
                while( iter != m_tConfInfo.m_vctCnsList.end() )
                {					  
                    if ( iter->m_wEpID == tConfCns.m_tConfCnsList[i].m_wEpID )
                    {
                        m_tConfInfo.m_vctCnsList.erase(iter);
                        break;
                    }		
                    iter++;
                }				
			}
			
            //处理视频源信息中不存在的会场
            for ( vector<TVidFeccInfo>::iterator iter = m_vctConf323VidInfo.begin() ;
                iter != m_vctConf323VidInfo.end() ; )
            {
                bool bFind = false;
                for (int i = 0 ; i < m_tConfInfo.m_vctCnsList.size() ; i++)
                {
                    if (m_tConfInfo.m_vctCnsList.at(i).m_wEpID == iter->m_wEpID)
                    {
                        bFind = true;
                        break;
                    }
                }
                if (!bFind)
                {
                    iter = m_vctConf323VidInfo.erase(iter);
                }
                else
                {
                    iter++;
                }
            }
		}
		break;
	case tp_OprType_Add:			//增加
//         {
// 		    m_tConfInfo.m_tplCnsList.Add(tConfCns.m_tConfCnsList,tConfCns.m_wNum);	
//             bRefreshUI = TRUE;
//         }
// 		break;

	case tp_OprType_Update:   // 更新
        {   
            
			for ( int i = 0; i< tConfCns.m_wNum ;  i++ )
			{   
                //if ( m_tConfInfo.m_wConfID == INVALID_WORD ) 
                //{
                //    return ;
                //}


				s32 Index =	m_tConfInfo.GetCnsIndexFrmCnsLst( tConfCns.m_tConfCnsList[i].m_wEpID );
				if ( Index >= 0 ) 
                {  
                    if (    m_tConfInfo.m_vctCnsList.at( Index ).m_bOnline != tConfCns.m_tConfCnsList[i].m_bOnline 
                         || strcmp( m_tConfInfo.m_vctCnsList.at( Index ).m_achRoomName, tConfCns.m_tConfCnsList[i].m_achRoomName ) != 0  
                         || m_tConfInfo.m_vctCnsList.at( Index ).m_bMute != tConfCns.m_tConfCnsList[i].m_bMute 
                         || m_tConfInfo.m_vctCnsList.at( Index ).m_bQuiet != tConfCns.m_tConfCnsList[i].m_bQuiet
						 || m_tConfInfo.m_vctCnsList.at( Index ).m_emEpType != tConfCns.m_tConfCnsList[i].m_emEpType )
                    {
						
                        bRefreshUI = TRUE;
                        m_tConfInfo.m_vctCnsList[Index] = tConfCns.m_tConfCnsList[i];
                        //m_tConfInfo.m_tplCnsList.SetAt( Index, &tConfCns.m_tConfCnsList[i] );						                       
                    }	
					else
					{
                        m_tConfInfo.m_vctCnsList[Index] = tConfCns.m_tConfCnsList[i];
						//m_tConfInfo.m_tplCnsList.SetAt( Index, &tConfCns.m_tConfCnsList[i] );
					}
				}
				else
				{
					bRefreshUI = TRUE;
					if (tConfCns.m_tConfCnsList[i].m_emEpType == emTPEndpointTypeCNS || tConfCns.m_tConfCnsList[i].m_emEpType == emTPEndpointH323MT 
						|| tConfCns.m_tConfCnsList[i].m_emEpType == emTPEndpointH323SingleMCU || tConfCns.m_tConfCnsList[i].m_emEpType == emTPEndpointH323G400
                        || tConfCns.m_tConfCnsList[i].m_emEpType == emTPEndpointTypeUMS || tConfCns.m_tConfCnsList[i].m_emEpType == emTPEndpointH323MCU 
						|| tConfCns.m_tConfCnsList[i].m_emEpType == emTPEndpointTypeVRS )//B5显示级联会议||新添加录放室类型
					{
                        m_tConfInfo.m_vctCnsList.push_back( tConfCns.m_tConfCnsList[i] );

					}
				}
			}
		}
		break;
	default:
		 ;
	}

/*
#ifdef _DEBUG
    for ( int i = 0; i< m_tplConfList.Size(); i++ )
    {
        for ( int j = 0; j< m_tplConfList.GetAt(i).m_tplCnsList.Size(); j++ )
        {
            TRACE("\n[CConfCtrl::OnUpdateConfCnsListNotify]afterUpdate confID=%d ,cnsID= %d ,cnsAliars=%s, bOnLine=%d \n",m_tplConfList.GetAt(i).m_wConfID,
                m_tplConfList.GetAt(i).m_tplCnsList.GetAt(j).m_wEpID,
                m_tplConfList.GetAt(i).m_tplCnsList.GetAt(j).m_achRoomName, m_tplConfList.GetAt(i).m_tplCnsList.GetAt(j).m_bOnline);
        }
    }
#endif
*/
	if ( bRefreshUI )
	{
		PrtMsg( ev_CnConfEpList_Nty,emEventTypeCnsRecv,"ConfID=%d, CNS Count=%d, operateType=%d (0: Add, 1: Del, 2: Update ) ",
		                                                         tConfCns.m_wConfID, tConfCns.m_wNum,tConfCns.m_emOpr);

		for ( int j = 0; j< tConfCns.m_wNum; j++ )
		{
			PrtMsg("\n[CConfCtrl::OnUpdateConfCnsListNotify]msginfo: confID=%d, cnsID= %d, EpType=%d, cnsRoomName=%s, bOnLine=%d, emCallReason=%d , bIsSpeaker=%d, SpeakerNum=%d\n", 
				tConfCns.m_wConfID,tConfCns.m_tConfCnsList[j].m_wEpID, tConfCns.m_tConfCnsList[j].m_emEpType,tConfCns.m_tConfCnsList[j].m_achRoomName, 
				tConfCns.m_tConfCnsList[j].m_bOnline,tConfCns.m_tConfCnsList[j].m_emCallReason,tConfCns.m_tConfCnsList[j].m_bIsSpeaker,tConfCns.m_tConfCnsList[j].m_wSpeakerNum );
		}

        PostEvent( UI_UMS_REFRESH_CONFCNS_LIST, tConfCns.m_wConfID ); 

        //更新cns信息 如果是被抢 需要有提示
        if ( tp_OprType_Update == tConfCns.m_emOpr )
        {
            PostEvent( UI_UMS_UPDATE_CONFCNS_LIST, tConfCns.m_wConfID, (LPARAM)&tConfCns );
        }
	}
	  
} 


void CUmcConfCtrl::OnUpdateConfAuxMixlistNotify( const CMessage& cMsg )
{   
 	CTpMsg cTpMsg(&cMsg);

    TConfAuxMixInfo tConfAudList = *reinterpret_cast<TConfAuxMixInfo*>( cTpMsg.GetBody() );
 
 	PrtMsg( ev_TppConfAMixUpdate_Nty, emEventTypeCnsRecv, "ConfID= %d, bStart= %d bVacOn=%d, emRet:%d",
 		                                                  tConfAudList.m_wConfID, tConfAudList.m_bStart, tConfAudList.m_bVacOn, tConfAudList.m_emRet );
 
 	PrtMsg( "\tAudListNty :%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",  tConfAudList.m_atAuxMixList.m_awList[0], tConfAudList.m_atAuxMixList.m_awList[1], 
 			tConfAudList.m_atAuxMixList.m_awList[2], tConfAudList.m_atAuxMixList.m_awList[3], tConfAudList.m_atAuxMixList.m_awList[4],tConfAudList.m_atAuxMixList.m_awList[5], tConfAudList.m_atAuxMixList.m_awList[6],
			tConfAudList.m_atAuxMixList.m_awList[7], tConfAudList.m_atAuxMixList.m_awList[8], tConfAudList.m_atAuxMixList.m_awList[9],tConfAudList.m_atAuxMixList.m_awList[10], tConfAudList.m_atAuxMixList.m_awList[11],
			tConfAudList.m_atAuxMixList.m_awList[12], tConfAudList.m_atAuxMixList.m_awList[13], tConfAudList.m_atAuxMixList.m_awList[14],tConfAudList.m_atAuxMixList.m_awList[15], tConfAudList.m_atAuxMixList.m_awList[16],
			tConfAudList.m_atAuxMixList.m_awList[17], tConfAudList.m_atAuxMixList.m_awList[18], tConfAudList.m_atAuxMixList.m_awList[19],tConfAudList.m_atAuxMixList.m_awList[20], tConfAudList.m_atAuxMixList.m_awList[21],
			tConfAudList.m_atAuxMixList.m_awList[22], tConfAudList.m_atAuxMixList.m_awList[23], tConfAudList.m_atAuxMixList.m_awList[24],tConfAudList.m_atAuxMixList.m_awList[25], tConfAudList.m_atAuxMixList.m_awList[26]);		
 
     
	m_tConfInfo.m_bStartAudmix = tConfAudList.m_bStart;
	m_tConfInfo.m_bVacOn = tConfAudList.m_bVacOn;
	memcpy( &m_tConfInfo.m_tAudmixList, &tConfAudList.m_atAuxMixList, sizeof(TAuxMixList) );

	PostEvent( UI_UMS_REFRESH_CONFAUDMIX_LIST, tConfAudList.m_bVacOn, tConfAudList.m_bStart );   
} 


void CUmcConfCtrl::OnUpdateConfAuxMixlistInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

    TConfAuxMixInfo tConfAudList = *reinterpret_cast<TConfAuxMixInfo*>( cTpMsg.GetBody() );
	
	PrtMsg( ev_TppConfAMixUpdate_Ind, emEventTypeCnsRecv, "ConfID= %d, bStart= %d",
		tConfAudList.m_wConfID, tConfAudList.m_bStart );

    //收到Ind时不更新界面,失败了界面进行提示
	if (tConfAudList.m_emRet != em_DiscussOprRsp_Ok)
	{
		PostEvent( UI_UMS_AUDMIXIND, (WPARAM)tConfAudList.m_emRet, NULL);   
	}
	   

}

void CUmcConfCtrl::OnAudMixDisListOprNotify( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	m_tDiscussListOpr = *reinterpret_cast<TDiscussListOpr*>( cTpMsg.GetBody() );

	PostEvent(UI_UMS_AUDMIX_DISLISTOPR_IND,NULL,NULL);

	PrtMsg( ev_TppAudMixDisListOpr_Ind, emEventTypeCnsRecv, "confID= %d, OprType= %d wNum=%d (%d:DisListOpr_Add, %d:em_DisListOpr_Del ) m_awEpId:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
		m_tDiscussListOpr.m_wConfId, m_tDiscussListOpr.m_emOprType,m_tDiscussListOpr.m_wNum, em_DisListOpr_Add, em_DisListOpr_Del, m_tDiscussListOpr.m_awEpId[0],
		m_tDiscussListOpr.m_awEpId[1],m_tDiscussListOpr.m_awEpId[2],m_tDiscussListOpr.m_awEpId[3],m_tDiscussListOpr.m_awEpId[4],m_tDiscussListOpr.m_awEpId[5],
		m_tDiscussListOpr.m_awEpId[6],m_tDiscussListOpr.m_awEpId[7],m_tDiscussListOpr.m_awEpId[8],m_tDiscussListOpr.m_awEpId[9],m_tDiscussListOpr.m_awEpId[10],
		m_tDiscussListOpr.m_awEpId[11],m_tDiscussListOpr.m_awEpId[12],m_tDiscussListOpr.m_awEpId[13],m_tDiscussListOpr.m_awEpId[14],m_tDiscussListOpr.m_awEpId[15],
		m_tDiscussListOpr.m_awEpId[16],m_tDiscussListOpr.m_awEpId[17],m_tDiscussListOpr.m_awEpId[18],m_tDiscussListOpr.m_awEpId[19],m_tDiscussListOpr.m_awEpId[20],
		m_tDiscussListOpr.m_awEpId[21],m_tDiscussListOpr.m_awEpId[22],m_tDiscussListOpr.m_awEpId[23],m_tDiscussListOpr.m_awEpId[24],m_tDiscussListOpr.m_awEpId[25],m_tDiscussListOpr.m_awEpId[26]);
}

void CUmcConfCtrl::OnAMixVacNotify( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	TConfAuxMixVacOpr tConfAuxMixVacOpr = *reinterpret_cast<TConfAuxMixVacOpr*>( cTpMsg.GetBody() );

	PostEvent(UI_UMS_AUDMIXVAC_IND,NULL,tConfAuxMixVacOpr.m_wOprRet);

	PrtMsg( ev_Cn_ConfAMixVacSwitch_Ind, emEventTypeCnsRecv, "confID= %d,VacOn=%d, Ret= %d",
		tConfAuxMixVacOpr.m_wConfID, tConfAuxMixVacOpr.m_bVacOn, tConfAuxMixVacOpr.m_wOprRet );
}

void CUmcConfCtrl::OnUpdateConfPolllistNotify( const CMessage& cMsg )
{
 
// 	CTpMsg kdvMsg(&cMsg);
//     TConfTurnInfo tConfPollList = *reinterpret_cast<TConfTurnInfo*>( kdvMsg.GetBody() );
// 	
// 	PrtMsg( evtp_UpdateTurn_cmd,emEventTypeUmsRecv,"ConfID=%d, pollMemCount=%d",
// 		tConfPollList.m_wConfID, tConfPollList.m_atTurnList.m_wNum );
// 	
// 	if ( tConfPollList.m_atTurnList.m_wNum <= 0 ) 
// 	{ 
// 		return;
// 	}
//     
// 	s32 nIndex = GetConfIndexByID( tConfPollList.m_wConfID );
// 	if ( nIndex < 0 ) 
// 	{
// 		return;
// 	}
// 	
//     
// 	m_tplConfList.at( nIndex ).m_tplPollList.Clear();
//     m_tplConfList.at( nIndex ).m_tplPollList.Add(tConfPollList.m_atTurnList.m_awList,tConfPollList.m_atTurnList.m_wNum);
// 	
//     
// 	PostEvent(UI_UMS_REFRESH_CONFPOLL_LIST,tConfPollList.m_wConfID);
} 


void CUmcConfCtrl::OnUpdateConfSpeakerNotify( const CMessage& cMsg )
{
    
    CTpMsg kdvMsg(&cMsg); 

    TConfEpID tConfEp = *reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() );
    
    PrtMsg( ev_TppConfApplySpeaker_Nty,emEventTypeCnsRecv,"ConfID=%d, SpeakerCnsID=%d",
        tConfEp.m_wConfID, tConfEp.m_wEpID );
     
    m_tConfInfo.m_wSpeaker = tConfEp.m_wEpID;
    
    
	PostEvent(UI_UMS_CHANGE_SPEAKER_NOTIFY,tConfEp.m_wConfID,tConfEp.m_wEpID);
} 

 
/*
enum EmTpApplySpeakerRet
{
TP_ApplySpeaker_Success,		
TP_ApplySpeaker_ConfUnExist,		//会议不存在
TP_ApplySpeaker_EpIDError,			//会场不存在
TP_ApplySpeaker_EpStateError,		//会场未在线或通道不未建立
};
*/
void CUmcConfCtrl::OnSetSpokeCnsRsp( const CMessage& cMsg )
{
	
 	CTpMsg kdvMsg(&cMsg);

 	TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() ); 
 	EmTpApplySpeakerRet emRe = * reinterpret_cast<EmTpApplySpeakerRet*>( kdvMsg.GetBody() + sizeof(TConfEpID) );
    PrtMsg(ev_TppConfApplySpeaker_Ind,emEventTypeCnsRecv,"ConfID=%d, CNSID=%d , \
         result=%d (%d:Success, %d:ConfUnExist, %d:EpIDError, %d:EpStateError)",
         tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID,emRe,TP_ApplySpeaker_Success,TP_ApplySpeaker_ConfUnExist,TP_ApplySpeaker_EpIDError,TP_ApplySpeaker_EpStateError) ; 
 	
    if ( emRe == TP_ApplySpeaker_Success )
    {      
       m_tConfInfo.m_wSpeaker = tConfEpInfo.m_wEpID;
    }

 	PostEvent(UI_UMS_SET_SPEAKER_IND,tConfEpInfo.m_wEpID,emRe);	
	return;
} 

void CUmcConfCtrl::OnSetMuteCnsRsp( const CMessage& cMsg ) 
{ 
    CTpMsg kdvMsg(&cMsg);

    TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() ); 
    BOOL32 bRe = * reinterpret_cast<BOOL32*>( kdvMsg.GetBody() + sizeof(TConfEpID) );
    PrtMsg(ev_TppConfMute_Ind,emEventTypeCnsRecv,"ConfID=%d, CNSID=%d ,bStart=%d  ",
        tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID,bRe ) ; 
    
    int CnsIndex = m_tConfInfo.GetCnsIndexFrmCnsLst( tConfEpInfo.m_wEpID );
	if (CnsIndex == -1)
	{
		PrtMsg(ev_TppConfMute_Ind,emEventTypeCnsRecv,"GetCnsIndexFrmCnsLst = -1 return");
		return;
	}

    m_tConfInfo.m_vctCnsList.at(CnsIndex).m_bMute = bRe;

    PostEvent( UI_UMS_SET_MUTE_CNS_RSP, tConfEpInfo.m_wEpID, bRe );	
    return;
} 
 
void CUmcConfCtrl::OnSetSilenceCnsRsp( const CMessage& cMsg )
{
    CTpMsg kdvMsg(&cMsg);

    TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() ); 
    BOOL32 bRe = * reinterpret_cast<BOOL32*>( kdvMsg.GetBody() + sizeof(TConfEpID) );
    PrtMsg(ev_TppConfQuiet_Ind,emEventTypeCnsRecv,"ConfID=%d, CNSID=%d ,bStart=%d  ",
        tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID,bRe ) ; 
 
    int CnsIndex = m_tConfInfo.GetCnsIndexFrmCnsLst( tConfEpInfo.m_wEpID );
	if ( -1 == CnsIndex )
	{
		return;
	}
    m_tConfInfo.m_vctCnsList.at(CnsIndex).m_bQuiet = bRe; 

    PostEvent(UI_UMS_SET_QUIET_CNS_RSP, tConfEpInfo.m_wEpID, bRe );	
    return;   
} 


/*
enum EmTPDualReason
{
emTpDualAccept,
		emTpDualBusy,
		emTpDualPreemptive,
		emTpDualPeerReject,
		emTpDualPeerStop,
        emTpDualNoVideo,
        emTpDualLocalStop,
		emTpDualSndFail,       //发送双流失败
};
*/
void CUmcConfCtrl::OnSetDualCnsRsp( const CMessage& cMsg )
{
    CTpMsg kdvMsg(&cMsg);

	u16 wEvent = kdvMsg.GetEvent();
    TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() ); 
    EmTPDualReason emRe = * reinterpret_cast<EmTPDualReason*>( kdvMsg.GetBody() + sizeof(TConfEpID) );
    PrtMsg(kdvMsg.GetEvent(),emEventTypeCnsRecv,"ConfID=%d, CNSID=%d ,erroCode=%d \
        (%d:Accept, %d:DualBusy,%d:Preemptive, %d:PeerReject, %d:PeerStop,%d:NoVideo,%d:lLocalStop,%d:SndFail)",
        tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID,emRe ,emTpDualAccept,
        emTpDualBusy,emTpDualPreemptive,emTpDualPeerReject,emTpDualPeerStop,emTpDualNoVideo,emTpDualLocalStop,emTpDualSndFail) ; 
    /* 不通过此消息设置会议中的双流ID -2013.7.5 xcr
    if ( emRe == emTpDualAccept )
    {
         
        if ( ev_TppConfStartDual_Ind == wEvent )
        {
			m_tConfInfo.m_wDual = tConfEpInfo.m_wEpID;
        }
		else
		{
			m_tConfInfo.m_wDual = INVALID_WORD;
		}
    }*/

    PostEvent( UI_UMS_SET_DUAL_CNS_RSP, tConfEpInfo.m_wConfID, emRe );	
    return;
    
}  

void CUmcConfCtrl::OnDualCnsNotify( const CMessage& cMsg )
{
    CTpMsg kdvMsg(&cMsg);

    TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() );  
    PrtMsg(ev_TppConfDualEp_Nty,emEventTypeCnsRecv,"ConfID=%d, CNSID=%d ",
        tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID ) ; 
    
    
    m_tConfInfo.m_wDual = tConfEpInfo.m_wEpID;

    PostEvent(UI_UMS_DUAL_CNS_NOTIFY,tConfEpInfo.m_wConfID,tConfEpInfo.m_wEpID);	
    return;
    
}  

  

void CUmcConfCtrl::OnChairCnsNotify( const CMessage& cMsg )
{
    CTpMsg kdvMsg(&cMsg);
    
    TChairConfInfo tChairInfo = *reinterpret_cast<TChairConfInfo*>( kdvMsg.GetBody() );
    
    PrtMsg( ev_TppChairConfInfo_Nty, emEventTypeCnsRecv, "ConfID:%d, ConfName:%s, ChairName:%s",tChairInfo.m_wConfID, tChairInfo.m_tConfName.m_abyAlias, tChairInfo.m_tChairName.m_abyAlias);  
       
    if ( m_tConfInfo.m_wConfID == tChairInfo.m_wConfID )
    {
        //只更新主席名称
        m_tConfInfo.SetChairInfo( tChairInfo.m_tChairName );
    }

	//_snprintf( m_tConfInfo.m_achConfName, sizeof(m_tConfInfo.m_achConfName), tChairInfo.m_tConfName.m_abyAlias);
    
    PostEvent(UI_CNS_CHAIRCONFINFO_NTY);	
    return;
  
}

 
void CUmcConfCtrl::OnCnsLeaveNotify( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
    
    TCnsInfo tInfo = *reinterpret_cast<TCnsInfo*>( kdvMsg.GetBody() );
    
    PrtMsg( ev_TppModuleterminalLeftConf, emEventTypeCnsRecv, "ID=%d, 会场名=%s",tInfo.m_wEpID, tInfo.m_achRoomName );  
     
    PostEvent(UI_CNS_LEAVECONF_NOTIFY, tInfo.m_wEpID,(LPARAM)tInfo.m_achRoomName );	
    return;
}


void CUmcConfCtrl::OnUmsCommonReasonInd( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);

	m_tTPUmsReasonInd = *reinterpret_cast<TTPUmsReasonInd*>( kdvMsg.GetBody() );

	PrtMsg( ev_TppUmsCommonReasonToUI_Ind, emEventTypeCnsRecv, "ReasonId: %d", m_tTPUmsReasonInd.m_dwReason );  

	PostEvent( UI_CNS_UMSREASON_IND, 0, 0 );

	return;
}

const TTPUmsReasonInd CUmcConfCtrl::GetUmsReason() const
{
	return m_tTPUmsReasonInd;
}

void CUmcConfCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN(CUmcConfCtrl, cMsg);
}

void CUmcConfCtrl::OnTimeOut(u16 wEvent)
{
    // 发送超时事件通知
    PostEvent(UI_UMS_CMD_TIMEOUT, wEvent);
}


//会议轮询暂停
u16 CUmcConfCtrl::PollPauseCmd( const BOOL32& bIsPause )
{
	CTpMsg *pcTpMsg = m_pCncSession->GetKdvMsgPtr();  
	pcTpMsg->SetUserData( m_pCncSession->GetInst() );
	pcTpMsg->SetBody( &bIsPause, sizeof(BOOL32) );
	pcTpMsg->SetEvent( ev_Cn_Conf_SuspendPoll_Req );

	u16 wRet = m_pCncSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_Conf_SuspendPoll_Req, emEventTypecnstoolSend, _T( "bIsPause:%d" ), bIsPause );
	return wRet;
}
//会议轮询暂停反馈
void CUmcConfCtrl::OnPollPauseInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	EmTPPollResult emTPPollResult = *(EmTPPollResult*)( cTpMsg.GetBody() );

	PostEvent( UI_CNSPOLLPAUSE_IND, (WPARAM)emTPPollResult, NULL );

	PrtMsg( ev_Cn_Conf_SuspendPoll_Ind, emEventTypecnstoolRecv, _T( "EmTPPollResult:%d" )
		, emTPPollResult );
}

//会议轮询列表更新
u16 CUmcConfCtrl::PollListUpdateCmd( const TTpPollListNtfy& tTpPollListNtfy )
{
	CTpMsg *pcTpMsg = m_pCncSession->GetKdvMsgPtr();  
	pcTpMsg->SetUserData( m_pCncSession->GetInst() );
	pcTpMsg->SetBody( &tTpPollListNtfy, sizeof(TTpPollListNtfy) );
	pcTpMsg->SetEvent( ev_Cn_UpdateConfTurnlist_Nty );

	u16 wRet = m_pCncSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_Cn_UpdateConfTurnlist_Nty, emEventTypecnstoolSend, _T( "TTpPollListNtfy m_wCurNum:%d, m_wTotalNum:%d,m_nFlag:%d,m_wInterval:%d" )
		, tTpPollListNtfy.m_wCurNum,tTpPollListNtfy.m_wTotalNum, tTpPollListNtfy.m_nFlag, tTpPollListNtfy.m_wInterval );
	for (int i = 0; i < tTpPollListNtfy.m_wCurNum; i++)
	{
		OspPrintf(TRUE,FALSE,_T( "-Cmd-EpID%d:%d\n" ),i, tTpPollListNtfy.m_awList[i]);
	}
	return wRet;
}
/*
//会议讨论
u16 CUmcConfCtrl::ConfDisCmd( const BOOL& bDis )
{
	CTpMsg *pcTpMsg = m_pCncSession->GetKdvMsgPtr();  
	pcTpMsg->SetUserData( m_pCncSession->GetInst() );
	pcTpMsg->SetBody( &bDis, sizeof(BOOL) );
	pcTpMsg->SetEvent( ev_CnCfgConfDis_Cmd );

	u16 wRet = m_pCncSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnCfgConfDis_Cmd, emEventTypecnstoolSend, _T( "bDis:%d" ), bDis );
	return wRet;
}

void CUmcConfCtrl::OnConfDisInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	BOOL bDis = *(BOOL*)( cTpMsg.GetBody() );
	m_tConfInfo.m_bStartAudmix = bDis;

	PostEvent( UI_CNSTOOL_CONFDIS_IND, 0, 0 );
	PrtMsg( ev_CnCfgConfDis_Ind, emEventTypecnstoolRecv, _T( "bDis:%d" ), bDis );
}

const BOOL& CUmcConfCtrl::GetConfDisInfo() const
{
	return m_tConfInfo.m_bStartAudmix;
}*/
 
void CUmcConfCtrl::OnPollListInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	TTpPollListInd tTpPollListInd = *(TTpPollListInd*)( cTpMsg.GetBody() );

	PostEvent( UI_CNSPOLLLIST_IND, NULL, (LPARAM)&tTpPollListInd );

	PrtMsg( ev_Cn_UpdateConfTurnlist_Ind, emEventTypecnstoolRecv, _T( "PollListInd Flag:%d m_wConfID:%d,m_wCurRcvNum:%d, m_wRet:%d" )
		, tTpPollListInd.m_nFlag, tTpPollListInd.m_wConfID,tTpPollListInd.m_wCurRcvNum,tTpPollListInd.m_wRet );
}

void CUmcConfCtrl::OnPollListNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	TTpPollListNtfy tTpPollList = *(TTpPollListNtfy*)( cTpMsg.GetBody() );
	if (m_bIsFirstPollListNty)
	{
		m_bIsFirstPollListNty = false;
		m_nPollListFlag = tTpPollList.m_nFlag;
		m_vctPollList.clear();
	}

	if (m_nPollListFlag != tTpPollList.m_nFlag)
	{
		m_nPollListFlag = tTpPollList.m_nFlag;
		m_vctPollList.clear();
	}

	for (int i = 0; i<tTpPollList.m_wCurNum; i++)
	{
		m_vctPollList.push_back(tTpPollList.m_awList[i]);
	}

	if ( m_vctPollList.size() == tTpPollList.m_wTotalNum )
	{
		m_bIsFirstPollListNty = true;
		PostEvent( UI_CNSPOLLLIST_NTY, (WPARAM)tTpPollList.m_wInterval, NULL );//轮询间隔发送到界面
	}
	

	PrtMsg( ev_Cn_UpdateConfTurnlist_Nty, emEventTypecnstoolRecv,  _T( "PollListCurNum:%d" ), tTpPollList.m_wCurNum);
	for (int i = 0; i < tTpPollList.m_wCurNum; i++)
	{
		OspPrintf(TRUE,FALSE,_T( "-nty-EpID%d:%d\n" ),i, tTpPollList.m_awList[i]);
	}
}

u16 CUmcConfCtrl::GetPollList( vector<u16>& vctPollList )
{
	vctPollList = m_vctPollList;
	return NO_ERROR;
}

TTpPollStat CUmcConfCtrl::GetPollState()
{
	return m_tConfInfo.m_tPollStat;
}

//画面合成
u16 CUmcConfCtrl::RervesBrdVmpReq( TRersvesEqpReq tRersvesEqp )
{
    if ( NULL == m_pCncSession ) 
    {
        return ERR_CMS;
    }

    CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
    pMsg->SetUserData( m_pCncSession->GetInst() );
    pMsg->SetEvent( ev_Cn_RervesBrdVmp_Req );
    pMsg->SetBody( &tRersvesEqp,sizeof(TRersvesEqpReq) );

    u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 

    PrtMsg( ev_Cn_RervesBrdVmp_Req, emEventTypeCnsSend, "m_wConfID:%d, m_bRersves:%d, EqpID:%d, EqpAlias:%s ", 
        tRersvesEqp.m_wConfID,tRersvesEqp.m_bRersves, tRersvesEqp.m_tEqp.m_byEqpID, tRersvesEqp.m_tEqp.m_szEqpAlias ); 
    return wRe; 
}

void CUmcConfCtrl::OnRervesBrdVmpInd( const CMessage& cMsg )
{
    CTpMsg kdvMsg(&cMsg); 

    TRersvesEqpRsp tRersvesEqp = *reinterpret_cast<TRersvesEqpRsp*>( kdvMsg.GetBody() );

    PrtMsg( ev_Cn_RervesBrdVmp_Ind,emEventTypeCnsRecv,"m_wConfID:%d, m_bRersves:%d, EmRervesVmpRet:%d (2:EmRervesVmpRet_ResFull,3:EmRervesVmpRet_Busy) ",
        tRersvesEqp.m_wConfID, tRersvesEqp.m_tRersvesReq.m_bRersves, tRersvesEqp.m_emRet );

    BOOL bRersves = tRersvesEqp.m_tRersvesReq.m_bRersves;
    EmRervesVmpRet  emRet = tRersvesEqp.m_emRet;

    PostEvent( UI_CNS_RERVESBRDVMP_IND, (WPARAM)bRersves, emRet );
}

u16 CUmcConfCtrl::SetBrdVmpReq( TSetVmpInfoReq tVmpInfo )
{
    CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
    pMsg->SetUserData( m_pCncSession->GetInst() );
    pMsg->SetEvent( ev_Cn_SetBrdVmp_Req );
    pMsg->SetBody( &tVmpInfo,sizeof(TSetVmpInfoReq) );

    u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 

    PrtMsg( ev_Cn_SetBrdVmp_Req, emEventTypeCnsSend, "m_wConfID:%d, EqpID:%d, m_tStyle:%d, wDualIndx:%d, wSpeakerIndx:%d, wChnlNum:%d", 
        tVmpInfo.m_wConfID,tVmpInfo.m_tEqp.m_byEqpID, tVmpInfo.m_tStyle.m_emVmpStyle, tVmpInfo.m_tStyle.m_wDualIndx, tVmpInfo.m_tStyle.m_wSpeakerIndx, tVmpInfo.m_tStyle.m_wChnlNum );
    for ( u16 wIndex = 0; wIndex < tVmpInfo.m_tStyle.m_wChnlNum; wIndex++ )
    {	
        PrtMsg( "\n m_atVmpChnl: index:%d, m_wEpID: %d, m_wScrIndx:%d", wIndex, tVmpInfo.m_tStyle.m_atVmpChnl[wIndex].m_wEpID, tVmpInfo.m_tStyle.m_atVmpChnl[wIndex].m_wScrIndx );
    }

    return wRe; 
}


void CUmcConfCtrl::OnSetBrdVmpInd( const CMessage& cMsg )
{
    CTpMsg kdvMsg(&cMsg); 

    TSetVmpInfoRsp tVmpInfo = *reinterpret_cast<TSetVmpInfoRsp*>( kdvMsg.GetBody() );

    PrtMsg( ev_Cn_SetBrdVmp_Ind,emEventTypeCnsRecv,"m_wConfID:%d, EmBrdVmpRet:%d ",
        tVmpInfo.m_wConfID, tVmpInfo.m_emRet );
}

u16 CUmcConfCtrl::SetBroadcastVmpReq( TBrdVmpReq tBrdVmp )
{
    CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
    pMsg->SetUserData( m_pCncSession->GetInst() );
    pMsg->SetEvent( ev_Cn_BrdVmp_Req );
    pMsg->SetBody( &tBrdVmp,sizeof(TBrdVmpReq) );

    u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 

    PrtMsg( ev_Cn_BrdVmp_Req, emEventTypeCnsSend, "m_wConfID:%d, EqpID:%d, m_bBrd:%d ", 
        tBrdVmp.m_wConfID,tBrdVmp.m_tEqp.m_byEqpID, tBrdVmp.m_bBrd ); 
    return wRe; 
}

void CUmcConfCtrl::OnBrdVmpInd( const CMessage& cMsg )
{
    CTpMsg kdvMsg(&cMsg); 

    TBrdVmpRsp tVmpRsp = *reinterpret_cast<TBrdVmpRsp*>( kdvMsg.GetBody() );

    PrtMsg( ev_Cn_BrdVmp_Ind,emEventTypeCnsRecv,"m_wConfID:%d, EmBrdVmpRet:%d ",
        tVmpRsp.m_wConfID, tVmpRsp.m_emRet );
}

void CUmcConfCtrl::OnBrdVmpNty( const CMessage& cMsg )
{
    CTpMsg kdvMsg(&cMsg); 

    TBrdVmpResArray tBrdVmpArray = *reinterpret_cast<TBrdVmpResArray*>( kdvMsg.GetBody() );

    PrtMsg( ev_Cn_BrdVmp_Ntfy,emEventTypeCnsRecv,"m_wNum:%d ", tBrdVmpArray.m_wNum );

    u8 byEqpID = 0;
    EmTpOprType emOprType;

    for ( int i = 0; i < tBrdVmpArray.m_wNum && i < CNS_MAX_CONF_NODE_NUM; i++ )
    {
        TBrdVmpResNtfy tBrdVmp = tBrdVmpArray.m_atVmpNtfy[i];
        PrtMsg( ev_Cn_BrdVmp_Ntfy,emEventTypeCnsRecv,"confId:%d, emOpr:%d(0:add,1:del,2:upd),byEqpID:%d,szEqpAlias:%s,m_emStat:%d(1:空闲;2,3:占用;0,4:错误)",
            tBrdVmp.m_wConfID, tBrdVmp.m_emOpr, tBrdVmp.m_tEqpInfo.m_byEqpID, tBrdVmp.m_tEqpInfo.m_szEqpAlias, tBrdVmp.m_emStat);

        byEqpID = tBrdVmp.m_tEqpInfo.m_byEqpID;
        emOprType = tBrdVmp.m_emOpr;
        if ( tBrdVmp.m_emOpr == tp_OprType_Add )
        {
            BOOL bFind = FALSE;
            for ( int i = 0; i < m_vctBrdVmpInfo.size(); i++ )
            {
                TBrdVmpResNtfy tBrdVmpNty = m_vctBrdVmpInfo.at(i);
                if ( tBrdVmpNty.m_tEqpInfo.m_byEqpID == tBrdVmp.m_tEqpInfo.m_byEqpID )
                {
                    bFind = TRUE;
                    if( strcmp( tBrdVmp.m_tEqpInfo.m_szEqpAlias, "" ) != 0 )
                    {
                        m_vctBrdVmpInfo.at(i) = tBrdVmp;
                    }
                    break;
                }
            }

            if (!bFind)
            {
                m_vctBrdVmpInfo.push_back( tBrdVmp );
            }
        }
        else if ( tBrdVmp.m_emOpr == tp_OprType_Update )
        {           
            BOOL bFind = FALSE;
            for ( int i = 0; i < m_vctBrdVmpInfo.size(); i++ )
            {
                TBrdVmpResNtfy tBrdVmpNty = m_vctBrdVmpInfo.at(i);
                if ( tBrdVmpNty.m_tEqpInfo.m_byEqpID == tBrdVmp.m_tEqpInfo.m_byEqpID )
                {
                    bFind = TRUE;                 
                    m_vctBrdVmpInfo.at(i) = tBrdVmp;
                    break;
                }
            }

            if (!bFind)
            {
                m_vctBrdVmpInfo.push_back( tBrdVmp );
            }
        }
        else if ( tBrdVmp.m_emOpr == tp_OprType_Del )
        {
            vector<TBrdVmpResNtfy>::iterator it = m_vctBrdVmpInfo.begin();
            while ( it != m_vctBrdVmpInfo.end() )
            {
                if ( it->m_tEqpInfo.m_byEqpID == tBrdVmp.m_tEqpInfo.m_byEqpID )
                {
                    m_vctBrdVmpInfo.erase(it);
                    break;
                }
                it++;
            }
        }
    }

    PostEvent( UI_CNS_BRDVMP_NTY, byEqpID, emOprType );
}

const vector<TBrdVmpResNtfy>& CUmcConfCtrl::GetBrdVmpStatus() const
{
    return m_vctBrdVmpInfo;
}


u16 CUmcConfCtrl::SaveVmpCfgReq( TBrdVmpResNtfy &tBrdVmp )
{
    m_tVmpSaveCfg = tBrdVmp;

    m_nSaveCfgIndex = 0;

    //发送第一包
    TTpVmpMemberCfg  tVmpMemberCfg;
    tVmpMemberCfg.m_wConfID = m_tVmpSaveCfg.m_wConfID;
    tVmpMemberCfg.m_emStyle = m_tVmpSaveCfg.m_tVmpStyle.m_emVmpStyle;
    tVmpMemberCfg.m_wSpeakerIndx = m_tVmpSaveCfg.m_tVmpStyle.m_wSpeakerIndx;
    tVmpMemberCfg.m_wDualIndx = m_tVmpSaveCfg.m_tVmpStyle.m_wDualIndx;
    tVmpMemberCfg.m_wTotalNum = TP_VMP_MAX_IN_CHN_NUM;
    tVmpMemberCfg.m_wEpNum = TP_REFRESH_LIST_EIGHT;
    tVmpMemberCfg.m_bFirst = TRUE;

    PrtMsg( ev_Cn_SaveVmpCfg_Cmd, emEventTypeCnsSend, "m_wConfID:%d, m_emStyle:%d, m_wFlag:%d, m_wEpNum:%d, m_wSpeakerIndx:%d, m_wDualIndx:%d ", 
        tVmpMemberCfg.m_wConfID,tVmpMemberCfg.m_emStyle, tVmpMemberCfg.m_wFlag, tVmpMemberCfg.m_wEpNum, tVmpMemberCfg.m_wSpeakerIndx, tVmpMemberCfg.m_wDualIndx ); 

    for ( u16 i = 0; i < TP_REFRESH_LIST_EIGHT; i++ )
    {
        TBrdVmpChnl tVmpChnl = m_tVmpSaveCfg.m_tVmpStyle.m_atVmpChnl[i];
	    
        if ( tVmpChnl.m_wEpID != TP_INVALID_INDEX )
        {
            TCnsInfo *pTCnsInfo = m_tConfInfo.GetCnsInfoByID( tVmpChnl.m_wEpID );
            if ( pTCnsInfo != NULL )
            {
                tVmpMemberCfg.m_atEpList[i].m_tEpAlias.SetAlias( pTCnsInfo->m_achRoomName );
                tVmpMemberCfg.m_atEpList[i].m_wScrIndx = tVmpChnl.m_wScrIndx;
            }
            else
            {
                PrtMsg( ev_Cn_SaveVmpCfg_Cmd, emEventTypeCnsSend,"EpID=%d, 会议中不存在该ID", tVmpChnl.m_wEpID ); 
            }
        }        
        PrtMsg( "\n tVmpMemberCfg.m_atEpList: index:%d, Alias: %s, ScrId:%d", i, tVmpMemberCfg.m_atEpList[i].m_tEpAlias.m_abyAlias, tVmpMemberCfg.m_atEpList[i].m_wScrIndx );
    }

    m_nSaveCfgIndex += TP_REFRESH_LIST_EIGHT;

    CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
    pMsg->SetUserData( m_pCncSession->GetInst() );
    pMsg->SetEvent( ev_Cn_SaveVmpCfg_Cmd );
    pMsg->SetBody( &tVmpMemberCfg,sizeof(TTpVmpMemberCfg) );

    u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 
    return wRe;
}


void CUmcConfCtrl::OnSaveVmpCfgInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg); 

    TTpVmpMemberCfgInd tCfgInd = *reinterpret_cast<TTpVmpMemberCfgInd*>( cTpMsg.GetBody() );

    PrtMsg( ev_CnSaveVmpCfg_Ind,emEventTypeCnsRecv,"m_wFlag:%d, m_bRet:%d ", tCfgInd.m_wFlag, tCfgInd.m_bRet );  

    PostEvent( UI_CNS_SAVEVMPCFG_IND, tCfgInd.m_bRet, m_nSaveCfgIndex );

    if ( !tCfgInd.m_bRet )//失败不再发送
    {
        return;
    }

    while ( m_nSaveCfgIndex < TP_VMP_MAX_IN_CHN_NUM )
    {  
        //发送第二包
        TTpVmpMemberCfg  tVmpMemberCfg;
        tVmpMemberCfg.m_wConfID = m_tVmpSaveCfg.m_wConfID;
        tVmpMemberCfg.m_wFlag = tCfgInd.m_wFlag;
        tVmpMemberCfg.m_emStyle = m_tVmpSaveCfg.m_tVmpStyle.m_emVmpStyle;
        tVmpMemberCfg.m_wSpeakerIndx = m_tVmpSaveCfg.m_tVmpStyle.m_wSpeakerIndx;
        tVmpMemberCfg.m_wDualIndx = m_tVmpSaveCfg.m_tVmpStyle.m_wDualIndx;
        tVmpMemberCfg.m_wTotalNum = TP_VMP_MAX_IN_CHN_NUM;
        if ( m_nSaveCfgIndex < TP_VMP_MAX_IN_CHN_NUM - 1 )
        {
            tVmpMemberCfg.m_wEpNum = TP_REFRESH_LIST_EIGHT;
        }
        else
        {
            tVmpMemberCfg.m_wEpNum = TP_VMP_MAX_IN_CHN_NUM - m_nSaveCfgIndex;
        }

        for ( u16 i = 0; i < tVmpMemberCfg.m_wEpNum; i++ )
        {
            TBrdVmpChnl tVmpChnl = m_tVmpSaveCfg.m_tVmpStyle.m_atVmpChnl[m_nSaveCfgIndex];
	    
            if ( tVmpChnl.m_wEpID != TP_INVALID_INDEX )
            {
                TCnsInfo *pTCnsInfo = m_tConfInfo.GetCnsInfoByID( tVmpChnl.m_wEpID );
                if ( pTCnsInfo != NULL )
                {
                    tVmpMemberCfg.m_atEpList[i].m_tEpAlias.SetAlias( pTCnsInfo->m_achRoomName );
                    tVmpMemberCfg.m_atEpList[i].m_wScrIndx = tVmpChnl.m_wScrIndx;
                }
            }    

            PrtMsg( "\n tVmpMemberCfg.m_atEpList: index:%d, Alias: %s, ScrId:%d", m_nSaveCfgIndex, tVmpMemberCfg.m_atEpList[i].m_tEpAlias.m_abyAlias, tVmpMemberCfg.m_atEpList[i].m_wScrIndx );

            m_nSaveCfgIndex++;
        }

        PrtMsg( ev_Cn_SaveVmpCfg_Cmd, emEventTypeCnsSend, "m_wConfID:%d, m_emStyle:%d, m_wFlag:%d, m_wEpNum:%d ", 
            tVmpMemberCfg.m_wConfID, tVmpMemberCfg.m_emStyle, tVmpMemberCfg.m_wFlag, tVmpMemberCfg.m_wEpNum ); 

        CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
        pMsg->SetUserData( m_pCncSession->GetInst() );
        pMsg->SetEvent( ev_Cn_SaveVmpCfg_Cmd );
        pMsg->SetBody( &tVmpMemberCfg,sizeof(TTpVmpMemberCfg) );

        u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG); 
    }
}

void CUmcConfCtrl::OnSaveVmpCfgCmd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg); 

    TTpVmpMemberCfg tVmpCfg = *reinterpret_cast<TTpVmpMemberCfg*>( cTpMsg.GetBody() );

    PrtMsg( ev_Cn_SaveVmpCfg_Cmd, emEventTypeCnsRecv, "m_wConfID:%d, m_emStyle:%d, m_wFlag:%d, m_bFirst:%d, m_wTotalNum:%d, m_wEpNum:%d",
        tVmpCfg.m_wConfID, tVmpCfg.m_emStyle, tVmpCfg.m_wFlag, tVmpCfg.m_bFirst, tVmpCfg.m_wTotalNum, tVmpCfg.m_wEpNum );  

    TVmpMemberCfg tBrdVmp;
    tBrdVmp = m_tVmpCurrentCfg;
 
    if ( tVmpCfg.m_bFirst )
    {
        tBrdVmp.Clear();
        m_nRevCfgIndex = 0;

        tBrdVmp.m_wConfID = tVmpCfg.m_wConfID;
        tBrdVmp.m_emStyle = tVmpCfg.m_emStyle;
        tBrdVmp.m_wDualIndx = tVmpCfg.m_wDualIndx;
        tBrdVmp.m_wSpeakerIndx = tVmpCfg.m_wSpeakerIndx;
    }

    for ( u16 j = 0; j < tVmpCfg.m_wEpNum; j++ )
    {
        if ( m_nRevCfgIndex >= TP_VMP_MAX_IN_CHN_NUM )
        {
            return;
        }

        tBrdVmp.m_atEpList[m_nRevCfgIndex] = tVmpCfg.m_atEpList[j];

        PrtMsg( "\n tVmpCfg.m_atEpList: index:%d, Alias: %s, ScrId:%d", m_nRevCfgIndex, tVmpCfg.m_atEpList[j].m_tEpAlias.m_abyAlias
            , tVmpCfg.m_atEpList[j].m_wScrIndx );

        m_nRevCfgIndex++;       
    }

    m_tVmpCurrentCfg = tBrdVmp;
}


u16 CUmcConfCtrl::CallVmpCfgReq( TEqpInfo &tEqp )
{
    TBrdVmpStyle tVmpStyle;

    tVmpStyle.m_emVmpStyle = m_tVmpCurrentCfg.m_emStyle;
    tVmpStyle.m_wSpeakerIndx = m_tVmpCurrentCfg.m_wSpeakerIndx;
    tVmpStyle.m_wDualIndx = m_tVmpCurrentCfg.m_wDualIndx;
    tVmpStyle.m_wChnlNum = TP_VMP_MAX_IN_CHN_NUM;

    for ( int i = 0; i < TP_VMP_MAX_IN_CHN_NUM; i++ )
    {                  
        TTPVmpCfgChnl tVmpChnl = m_tVmpCurrentCfg.m_atEpList[i];
        if ( strlen( tVmpChnl.m_tEpAlias.m_abyAlias ) != 0 )
        {
            TCnsInfo *pTCnsInfo = m_tConfInfo.GetCnsInfoByAlias(tVmpChnl.m_tEpAlias.m_abyAlias);
            if ( pTCnsInfo != NULL )
            {
                tVmpStyle.m_atVmpChnl[i].m_wEpID = pTCnsInfo->m_wEpID;
                tVmpStyle.m_atVmpChnl[i].m_wScrIndx = tVmpChnl.m_wScrIndx;
            }
            else
            {
                tVmpStyle.m_atVmpChnl[i].m_wEpID = TP_INVALID_INDEX;
            }
        }    
        else
        {
            tVmpStyle.m_atVmpChnl[i].Clear();
        }
    }

    TSetVmpInfoReq tVmpInfo;
    tVmpInfo.m_wConfID = m_tVmpCurrentCfg.m_wConfID;
    tVmpInfo.m_tEqp = tEqp;
    tVmpInfo.m_tStyle = tVmpStyle;

    CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
    pMsg->SetUserData( m_pCncSession->GetInst() );
    pMsg->SetEvent( ev_Cn_SetBrdVmp_Req );
    pMsg->SetBody( &tVmpInfo,sizeof(TSetVmpInfoReq) );

    PrtMsg( ev_Cn_SetBrdVmp_Req, emEventTypeCnsSend, "CallVmpCfgReq m_wConfID:%d, EqpID:%d, m_tStyle:%d, wDualIndx:%d, wSpeakerIndx:%d, wChnlNum:%d", 
        tVmpInfo.m_wConfID,tVmpInfo.m_tEqp.m_byEqpID, tVmpInfo.m_tStyle.m_emVmpStyle, tVmpInfo.m_tStyle.m_wDualIndx, tVmpInfo.m_tStyle.m_wSpeakerIndx, tVmpInfo.m_tStyle.m_wChnlNum );

    u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG );
    return wRe;
}

const TVmpMemberCfg CUmcConfCtrl::GetCurrentVmpCfg() const
{
    return m_tVmpCurrentCfg;
}


void CUmcConfCtrl::OnPollStatusNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg);  

	TTpPollStat tTpPollStat = *(TTpPollStat*)(cTpMsg.GetBody());
	m_tConfInfo.m_tPollStat = tTpPollStat;
	PrtMsg( ev_CnPollStatus_Nty, emEventTypeCnsRecv, " PollState.m_emStat: %d, Inst: %d ", tTpPollStat.m_emStat, tTpPollStat.m_wConfID );

	PostEvent( UI_CNS_POLL_STATE_NOTIFY, 0, 0 ); 
}

void CUmcConfCtrl::OnSetSelViewNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg);  
	m_tTPSelViewNtfy = *(TTPSelViewNtfy*)(cTpMsg.GetBody());	
	if (m_tTPSelViewNtfy.m_atSelView->m_wScreenIndx == TP_MAX_STREAMNUM && m_tTPSelViewNtfy.m_atSelView[0].IsValid())//会场选看
	{
		m_tConfInfo.m_wSelViewConfID = m_tTPSelViewNtfy.m_atSelView[0].m_wDstID;
	}

	//保存会场选看状态 cnclib不发通知 统一在umc里发通知  dyy 2015-6-26 
	PostEvent( UI_CNS_SEL_VIEW_NTY, NULL, NULL ); 
}

const TTPSelViewNtfy CUmcConfCtrl::GetSelWatchStatus() const
{
	return m_tTPSelViewNtfy;
}

const TDiscussListOpr CUmcConfCtrl::GetDiscussList() const
{
	return m_tDiscussListOpr;
}

void CUmcConfCtrl::OnJoinConfReq( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg);  

	m_tpConfEpInfo = *(TTpConfEpInfo*)(cTpMsg.GetBody());
	PrtMsg( ev_UmsToCncJoinConf_Req, emEventTypeCnsRecv, "m_Index: %d, m_wConfID:%d", m_tpConfEpInfo.m_Index, m_tpConfEpInfo.m_wConfID );

	PostEvent( UI_UMS_JOINCONF_REG, 0, 0 ); 
}

const TTpConfEpInfo CUmcConfCtrl::GetJoinConfInfo() const
{
	return m_tpConfEpInfo;
}

u16 CUmcConfCtrl::SetJoinConfInfo( TTpConfEpInfo tpConfEpInfo )
{
	CTpMsg *pMsg = m_pCncSession->GetKdvMsgPtr();
	pMsg->SetUserData( m_pCncSession->GetInst() );
	pMsg->SetEvent( ev_UmsToCncJoinConf_Rsp );
	pMsg->SetBody( &tpConfEpInfo,sizeof(TTpConfEpInfo) );

	u16 wRe = m_pCncSession->PostMsg(TYPE_TPMSG ); 

	PrtMsg( ev_UmsToCncJoinConf_Rsp, emEventTypeCnsSend, "m_wConfID:%d, m_Index:%d, m_bPermit:%d ", 
		tpConfEpInfo.m_wConfID,tpConfEpInfo.m_Index, tpConfEpInfo.m_bPermit ); 
	return wRe; 
}


void CUmcConfCtrl::OnHduPlanNty( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    s32 nNum = 0; 
    s32 nLeft = 0;

    TTpHduPlanPackData tHduPlanPackData = *reinterpret_cast<TTpHduPlanPackData *>( cTpMsg.GetBody() );

    if ( tHduPlanPackData.m_byFirst == 1 )
    {
        m_bPackDataIndex = 0;

        for( s32 nIndex = 0; nIndex < TP_STYLE_DATA_AllPACK_NUM ; nIndex ++ )
        {
            m_tHduPlanPackData[nIndex].Clear();
        }
    }

    if ( m_bPackDataIndex < TP_STYLE_DATA_AllPACK_NUM )
    {
        m_tHduPlanPackData[m_bPackDataIndex] = tHduPlanPackData;
    }

    m_bPackDataIndex++;
    nNum = tHduPlanPackData.m_wNum/TP_STYLE_DATA_PACK_NUM;
    nLeft = tHduPlanPackData.m_wNum%TP_STYLE_DATA_PACK_NUM;

    PrtMsg( ev_TpUMS_CNS_HduPlan_Nty, emEventTypeCnsRecv, _T( "Is first Packet:%d"),tHduPlanPackData.m_byFirst );

    if ( ( (m_bPackDataIndex == nNum )&&( nLeft == 0 ) ) ||( ( m_bPackDataIndex == (nNum+1) )&&( nLeft > 0 ) ) )
    {
        PostEvent( UI_HDUPLAN_NTY, (WPARAM)(m_tHduPlanPackData),NULL);
    }
}

u16 CUmcConfCtrl::ChangeChanModeReq( u16 wIndex, u8 byMode  )
{
    TTpHduChanModeSetInfo tHduPlanInfo;
    tHduPlanInfo.m_wIndex = wIndex;
    tHduPlanInfo.m_byMode = byMode;

    CTpMsg *pcTpMsg = m_pCncSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pCncSession->GetInst() );
    pcTpMsg->SetEvent( ev_TpHduChangeChanMode_Req );
    pcTpMsg->SetBody( &tHduPlanInfo, sizeof(TTpHduChanModeSetInfo) ); 

    u16 wRet = m_pCncSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TpHduChangeChanMode_Req, emEventTypeCnsSend, "Index : %d ;Mode %d ", tHduPlanInfo.m_wIndex,tHduPlanInfo.m_byMode );
    return wRet;
}

void CUmcConfCtrl::OnHduChangeModeInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);

    TTpHduChanModeSetInfo tHduChaModeInfo = *reinterpret_cast<TTpHduChanModeSetInfo *>( cTpMsg.GetBody() );
    EmCnsHduChangeChanModeRes emHduChangeModeRes = *reinterpret_cast<EmCnsHduChangeChanModeRes *>( cTpMsg.GetBody() +sizeof(TTpHduChanModeSetInfo));

    PrtMsg( ev_TpHduChangeChanMode_Ind, emEventTypeCnsRecv, "Index : %d ;Mode %d ; error ID %d", tHduChaModeInfo.m_wIndex,tHduChaModeInfo.m_byMode,emHduChangeModeRes );
    PostEvent( UI_HDUCHANGEMODE_IND, (WPARAM)(&tHduChaModeInfo),(LPARAM)(&emHduChangeModeRes));
}

u16 CUmcConfCtrl::SetHduVolReq( u16 wIndex, u8 byVol ,BOOL32 bMute )
{
    TTpHduSetVolInfo tHduSetVolInfo;
    tHduSetVolInfo.m_tInfo.m_wIndex = wIndex;
    tHduSetVolInfo.m_byVol = byVol;
    tHduSetVolInfo.m_bMute = bMute;

    CTpMsg *pcTpMsg = m_pCncSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pCncSession->GetInst() );
    pcTpMsg->SetEvent( ev_TpCNS_UMS_HduSetVol_Req );
    pcTpMsg->SetBody( &tHduSetVolInfo, sizeof(tHduSetVolInfo) ); 

    u16 wRet = m_pCncSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TpCNS_UMS_HduSetVol_Req, emEventTypeCnsSend, "Index : %d ; Volume %d ;IsMute %d ", wIndex,byVol,bMute );
    return wRet;
}

void CUmcConfCtrl::OnHduVolInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);

    TTpHduSetVolInfo tHduSetVolInfo = *reinterpret_cast<TTpHduSetVolInfo *>( cTpMsg.GetBody() );
    EmCnsHduSetVolRes emHduSetVolRes = *reinterpret_cast<EmCnsHduSetVolRes *>( cTpMsg.GetBody() +sizeof(TTpHduSetVolInfo));

    PrtMsg( ev_TpUMS_CNS_HduSetVol_Ind, emEventTypeCnsRecv, "Index : %d ; Volume %d ;IsMute %d ;EmCnsHduSetVolRes %d", tHduSetVolInfo.m_tInfo.m_wIndex,tHduSetVolInfo.m_byVol,tHduSetVolInfo.m_bMute,emHduSetVolRes);

    PostEvent( UI_HDUVOLUME_IND, (WPARAM)(&tHduSetVolInfo),(LPARAM)(&emHduSetVolRes));
}

u16 CUmcConfCtrl::StopPlayHdu( TTpHduPlayReq &tTvwInfo )
{
    CTpMsg *pcTpMsg = m_pCncSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pCncSession->GetInst() );
    pcTpMsg->SetEvent( ev_TpCNS_UMS_HduStopPlay_Req );
    pcTpMsg->SetBody( &tTvwInfo, sizeof(TTpHduPlayReq) ); 

    u16 wRet = m_pCncSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TpCNS_UMS_HduStopPlay_Req, emEventTypeCnsSend, "emType=%d, wConfID=%d, wDstID=%d, wScreenNum=%d, wIndex=%d, bySubIndex=%d, bVmp=%d alias = %s", 
        tTvwInfo.m_emType, tTvwInfo.m_wConfID, tTvwInfo.m_wDstID, 
        tTvwInfo.m_wScreenNum, tTvwInfo.m_wIndex, tTvwInfo.m_bySubIndex, tTvwInfo.m_bVmp,tTvwInfo.m_achAlias);
    return wRet;
}

void CUmcConfCtrl::OnHduStopPlayInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);

    TTpHduBaseInfo tHduBaseInfo = *reinterpret_cast<TTpHduBaseInfo *>( cTpMsg.GetBody() );
    u16 wRet = *reinterpret_cast<u16 *>( cTpMsg.GetBody() +sizeof(TTpHduBaseInfo));

    PrtMsg( ev_TpUMS_CNS_HduStopPlay_Ind, emEventTypeCnsRecv, "Index : %d ; SubIndex %d ;Success %d", tHduBaseInfo.m_wIndex,tHduBaseInfo.m_bySubIndex,wRet);

    PostEvent( UI_HDUSTOPPLAY_IND, (WPARAM)(&tHduBaseInfo),(LPARAM)(&wRet));
}
u16 CUmcConfCtrl::PlayHduReq( const TTpHduPlayReq & tTvwInfo )
{	
    CTpMsg *pcTpMsg = m_pCncSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pCncSession->GetInst() );
    pcTpMsg->SetEvent( ev_TpCNS_UMS_HduPlay_Req );
    pcTpMsg->SetBody( &tTvwInfo, sizeof(TTpHduPlayReq) ); 

    u16 wRet = m_pCncSession->PostMsg(TYPE_TPMSG);

    PrtMsg( ev_TpCNS_UMS_HduPlay_Req, emEventTypeCnsSend, "emType=%d, wConfID=%d, wDstID=%d, wScreenNum=%d, wIndex=%d, bySubIndex=%d, bVmp=%d alias = %s", 
        tTvwInfo.m_emType, tTvwInfo.m_wConfID, tTvwInfo.m_wDstID, 
        tTvwInfo.m_wScreenNum, tTvwInfo.m_wIndex, tTvwInfo.m_bySubIndex, tTvwInfo.m_bVmp,tTvwInfo.m_achAlias);

    return NO_ERROR;
}

void CUmcConfCtrl::OnHduPlayInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);

    TTpHduBaseInfo tHduBaseInfo = *reinterpret_cast<TTpHduBaseInfo *>( cTpMsg.GetBody() );
    EmCnsHduPlayNackReason emHduPlayReason = *reinterpret_cast<EmCnsHduPlayNackReason *>( cTpMsg.GetBody() +sizeof(TTpHduBaseInfo));

    PrtMsg( ev_TpUMS_CNS_HduPlay_Ind, emEventTypeCnsRecv, "Index : %d ; SubIndex %d, EmCnsHduPlayNackReason: %d", tHduBaseInfo.m_wIndex,tHduBaseInfo.m_bySubIndex, emHduPlayReason);

    PostEvent( UI_HDUPLAY_IND, (WPARAM)(&tHduBaseInfo),(LPARAM)(&emHduPlayReason));
}

void CUmcConfCtrl::OnP2PH323VideoInfo( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	TVidSourceInfo tVidSourceInfo = *reinterpret_cast<TVidSourceInfo *>( cTpMsg.GetBody() );

	PrtMsg( ev_H323SendVideoInfo_Nty, emEventTypeCnsRecv, "byNum: %d", tVidSourceInfo.m_byNum );

	m_vctConf323VidInfo.clear();
	m_tVidFeccInfo.m_tVidSourceInfo = tVidSourceInfo;

    PostEvent( UI_CNS_323VEDIOSOR_NOTIFY, (WPARAM)(&m_tVidFeccInfo), NULL );
}

void CUmcConfCtrl::OnP2PH323VideoFeccInfo( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	BOOL32 bAllowFecc = *(BOOL32*)( cTpMsg.GetBody() );
	u8 nVidno = *(u8*)(cTpMsg.GetBody() + sizeof(BOOL32));

	PrtMsg( ev_H323SendVideoFeccInfo_Nty, emEventTypeCnsRecv, "AllowFecc: %d, nVidno: %d", bAllowFecc, nVidno );

	m_tVidFeccInfo.m_wEpID = m_tConfEpInfo.m_wEpID;
	m_tVidFeccInfo.m_bAllowFecc = bAllowFecc;
	m_tVidFeccInfo.m_byVidno = nVidno;

	PostEvent( UI_CNS_323VEDIOSOR_NOTIFY, (WPARAM)(&m_tVidFeccInfo), NULL );
}

void CUmcConfCtrl::OnMulConfH323VideoInfoNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	TConfVidFeccInfo tConfVidFeccInfo = *reinterpret_cast<TConfVidFeccInfo *>( cTpMsg.GetBody() );

	PrtMsg( ev_SendFeccVidSrcInfo_Nty, emEventTypeCnsRecv, "byNum: %d", tConfVidFeccInfo.m_wNum );

	for ( int i = 0 ; i < tConfVidFeccInfo.m_wNum && i < TP_REFRESH_LIST_THREE ; i++)
	{
		TVidFeccInfo tVidFeccInfoTmp = tConfVidFeccInfo.m_atVidFeccList[i];
        PrtMsg( ev_SendFeccVidSrcInfo_Nty, emEventTypeCnsRecv, "Num: %d EpID: %d", i ,tVidFeccInfoTmp.m_wEpID );
		switch(tConfVidFeccInfo.m_emOpr)
		{
// 		case tp_OprType_Add:
// 			{
// 				BOOL bFind = FALSE;
// 				for ( int i = 0; i < m_vctConf323VidInfo.size(); i++ )
// 				{
// 					TVidFeccInfo tVidFeccInfo = m_vctConf323VidInfo.at(i);
// 					if ( tVidFeccInfo.m_wEpID == tVidFeccInfoTmp.m_wEpID )
// 					{
// 						bFind = TRUE;
// 						break;
// 					}
// 				}
// 				if (!bFind)
// 				{
// 					m_vctConf323VidInfo.push_back(tVidFeccInfoTmp);
// 				}
// 			}
// 			break;
// 		case tp_OprType_Del:
// 			{
// 				vector<TVidFeccInfo>::iterator it = m_vctConf323VidInfo.begin();
// 				while ( it != m_vctConf323VidInfo.end() )
// 				{
// 					if ( it->m_wEpID == tVidFeccInfoTmp.m_wEpID )
// 					{
// 						m_vctConf323VidInfo.erase(it);
// 						break;
// 					}
// 					it++;
// 				}
// 			}
// 			break;
		case tp_OprType_Update:
			{
				BOOL bFind = FALSE;
				for ( int i = 0; i < m_vctConf323VidInfo.size(); i++ )
				{
					TVidFeccInfo tVidFeccInfo = m_vctConf323VidInfo.at(i);
					if ( tVidFeccInfo.m_wEpID == tVidFeccInfoTmp.m_wEpID )
					{                
						m_vctConf323VidInfo.at(i) = tVidFeccInfoTmp;
						bFind = TRUE;
						break;
					}
				}
				if (!bFind)
				{
                    if (tVidFeccInfoTmp.m_tVidSourceInfo.m_byNum <= UMS_MAX_VID_SOURCE_NUM)
                    {
                        m_vctConf323VidInfo.push_back(tVidFeccInfoTmp);
                    }
				}
			}
			break;
// 		case tp_OprType_NULL:
// 			m_vctConf323VidInfo.clear();
// 			break;
		default:
			break;
		}
		
	}

	//更新界面远摇会场视频源信息
	for (int i = 0 ; i < m_vctConf323VidInfo.size() ; i++)
	{
        TVidFeccInfo tInfo = m_vctConf323VidInfo.at(i);
        if (tInfo.m_wEpID == m_tConfEpInfo.m_wEpID )
        {
            m_tVidFeccInfo = m_vctConf323VidInfo.at(i);
            PostEvent( UI_CNS_323VEDIOSOR_NOTIFY, (WPARAM)(&m_tVidFeccInfo), NULL );
            break;
        }
	}

}

void CUmcConfCtrl::OnMulConfH323VideoInfoInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);

    TConfVidFeccInfo tConfVidFeccInfo = *reinterpret_cast<TConfVidFeccInfo *>( cTpMsg.GetBody() );

    PrtMsg( ev_SendFeccVidSrcInfo_Ind, emEventTypeCnsRecv, "byNum: %d", tConfVidFeccInfo.m_wNum );

    for ( int i = 0 ; i < tConfVidFeccInfo.m_wNum && i < TP_REFRESH_LIST_THREE ; i++)
    {
        TVidFeccInfo tVidFeccInfoTmp = tConfVidFeccInfo.m_atVidFeccList[i];
        PrtMsg( ev_SendFeccVidSrcInfo_Ind, emEventTypeCnsRecv, "Num: %d EpID: %d", i ,tVidFeccInfoTmp.m_wEpID );

        switch(tConfVidFeccInfo.m_emOpr)
        {
            // 		case tp_OprType_Add:
            // 			{
            // 				BOOL bFind = FALSE;
            // 				for ( int i = 0; i < m_vctConf323VidInfo.size(); i++ )
            // 				{
            // 					TVidFeccInfo tVidFeccInfo = m_vctConf323VidInfo.at(i);
            // 					if ( tVidFeccInfo.m_wEpID == tVidFeccInfoTmp.m_wEpID )
            // 					{
            // 						bFind = TRUE;
            // 						break;
            // 					}
            // 				}
            // 				if (!bFind)
            // 				{
            // 					m_vctConf323VidInfo.push_back(tVidFeccInfoTmp);
            // 				}
            // 			}
            // 			break;
            // 		case tp_OprType_Del:
            // 			{
            // 				vector<TVidFeccInfo>::iterator it = m_vctConf323VidInfo.begin();
            // 				while ( it != m_vctConf323VidInfo.end() )
            // 				{
            // 					if ( it->m_wEpID == tVidFeccInfoTmp.m_wEpID )
            // 					{
            // 						m_vctConf323VidInfo.erase(it);
            // 						break;
            // 					}
            // 					it++;
            // 				}
            // 			}
            // 			break;
        case tp_OprType_Update:
            {
                BOOL bFind = FALSE;
                for ( int i = 0; i < m_vctConf323VidInfo.size(); i++ )
                {
                    TVidFeccInfo tVidFeccInfo = m_vctConf323VidInfo.at(i);
                    if ( tVidFeccInfo.m_wEpID == tVidFeccInfoTmp.m_wEpID )
                    {                
                        m_vctConf323VidInfo.at(i) = tVidFeccInfoTmp;
                        bFind = TRUE;
                        break;
                    }
                }
                if (!bFind)
                {
                    if (tVidFeccInfoTmp.m_tVidSourceInfo.m_byNum <= UMS_MAX_VID_SOURCE_NUM)
                    {
                        m_vctConf323VidInfo.push_back(tVidFeccInfoTmp);
                    }
                }
            }
            break;
            // 		case tp_OprType_NULL:
            // 			m_vctConf323VidInfo.clear();
            // 			break;
        default:
            break;
        }

    }

    //更新界面远摇会场视频源信息
    for (int i = 0 ; i < m_vctConf323VidInfo.size() ; i++)
    {
//         m_tVidFeccInfo = m_vctConf323VidInfo.at(i);
//         if (m_tVidFeccInfo.m_wEpID == m_tConfEpInfo.m_wEpID)
//         {
//             PostEvent( UI_CNS_323VEDIOSOR_NOTIFY, (WPARAM)(&m_tVidFeccInfo), NULL );
//             break;
//         }

        TVidFeccInfo tInfo = m_vctConf323VidInfo.at(i);
        if (tInfo.m_wEpID == m_tConfEpInfo.m_wEpID)
        {
            m_tVidFeccInfo = m_vctConf323VidInfo.at(i);
            PostEvent( UI_CNS_323VEDIOSOR_NOTIFY, (WPARAM)(&m_tVidFeccInfo), NULL );
            break;
        }
    }

}

void CUmcConfCtrl::SetAllQuiet( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);

	TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() ); 
	BOOL32 bRe = * reinterpret_cast<BOOL32*>( kdvMsg.GetBody() + sizeof(TConfEpID) );
	PrtMsg(ev_TppConfMute_Ind,emEventTypeCnsRecv,"ConfID=%d, CNSID=%d ,bQuiet=%d  ",
		tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID,bRe ) ; 

	if (tConfEpInfo.m_wEpID == TP_ALLEP_INDEX)
	{
		m_bIsAllQuite = bRe;
	}
	
	PostEvent( UI_CNS_ALLMUTE_ALLQUITE_NOTIFY, 0, 0 );	
	return;
}
bool CUmcConfCtrl::IsAllQuite()
{
	return m_bIsAllQuite;
}
void CUmcConfCtrl::SetAllMute( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);

	TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() ); 
	BOOL32 bRe = * reinterpret_cast<BOOL32*>( kdvMsg.GetBody() + sizeof(TConfEpID) );
	PrtMsg(ev_TppConfMute_Ind,emEventTypeCnsRecv,"ConfID=%d, CNSID=%d ,bMute=%d  ",
		tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID,bRe ) ; 

	if (tConfEpInfo.m_wEpID == TP_ALLEP_INDEX)
	{
		m_bIsAllMute = bRe;
	}

	PostEvent( UI_CNS_ALLMUTE_ALLQUITE_NOTIFY, 0, 0 );	
	return;
}
bool CUmcConfCtrl::IsAllMute()
{
	return m_bIsAllMute;
}
