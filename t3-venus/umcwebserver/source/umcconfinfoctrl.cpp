#include "umcglodef.h"
#include "umcconfinfoctrl.h"

CUmcConfinfoCtrl::CUmcConfinfoCtrl()
{
	ClearData();

    BuildEventsMap();
}

CUmcConfinfoCtrl::~CUmcConfinfoCtrl()
{
	ClearData();
}

void CUmcConfinfoCtrl::ClearData()
{
	m_vecTConfinfo.clear();
}

void CUmcConfinfoCtrl::BuildEventsMap()
{
	REG_PFUN(evtp_HungUpConf_result, &CUmcConfinfoCtrl::OnHungUpConfRsp ); 
	
	REG_PFUN(evtp_AddConfList_Notify, &CUmcConfinfoCtrl::OnAddConfListNotify );
	REG_PFUN(evtp_DelConflist_Notify, &CUmcConfinfoCtrl::OnDelConfListNotify );
	
	REG_PFUN(evtp_UpdateConfCnsList_Notify, &CUmcConfinfoCtrl::OnUpdateConfCnsListNotify );

	//会场操作
	REG_PFUN(evtp_StartDual_Ind, &CUmcConfinfoCtrl::OnStartdualRsp );
	REG_PFUN(evtp_StopDual_Ind, &CUmcConfinfoCtrl::OnStopdualRsp );
	REG_PFUN(evtp_DualEp_Notify, &CUmcConfinfoCtrl::OnDualNotify );
	REG_PFUN(evtp_ApplySpeaker_result, &CUmcConfinfoCtrl::OnSpeakerRsp );
	REG_PFUN(evtp_SpeakerChange_Notify, &CUmcConfinfoCtrl::OnSpeakerNotify );
	REG_PFUN(evtp_QuietEp_Ind, &CUmcConfinfoCtrl::OnQuietRsp );
	REG_PFUN(evtp_MuteEp_Ind, &CUmcConfinfoCtrl::OnMuteRsp );
	REG_PFUN(evtp_DropEp_Ind, &CUmcConfinfoCtrl::OnDropRsp );
	REG_PFUN(evtp_CallExistEP_result, &CUmcConfinfoCtrl::OnCallRsp );

	//选看
	REG_PFUN(ev_UMS_UMC_SelView_Ntfy, &CUmcConfinfoCtrl::OnSelViewNotify );
	REG_PFUN(ev_UMS_UMC_SelView_Ind, &CUmcConfinfoCtrl::OnSelViewRsp );

	//会议轮询
	REG_PFUN( evtp_UpdateConfTurnlist_Notify, &CUmcConfinfoCtrl::OnUpdateConfTurnlistNotify );
	REG_PFUN( evtp_UpdateTurn_ind, &CUmcConfinfoCtrl::OnUpdateTurnInd );
	REG_PFUN( evtp_StartTurn_ind, &CUmcConfinfoCtrl::OnStartTurnInd );
	REG_PFUN( evtp_StopTurn_ind, &CUmcConfinfoCtrl::OnStopTurnInd );
	REG_PFUN( evtp_SuspendTurn_ind, &CUmcConfinfoCtrl::OnSuspendTurnInd );
	REG_PFUN( evtp_TurnStat_ntfy, &CUmcConfinfoCtrl::OnTurnStatNotify );

	//会议讨论
	REG_PFUN( evtp_AuxMixInfo_Notify, &CUmcConfinfoCtrl::OnAuxMixInfoNotify );
	REG_PFUN( evtp_UpdateAudMixInfo_Ind, &CUmcConfinfoCtrl::OnUpdateAudMixInfoInd );
	REG_PFUN( evtp_StartAuxMix_ind, &CUmcConfinfoCtrl::OnStartAuxMixInd );
	REG_PFUN( ev_AuxMixVacSwitchInd, &CUmcConfinfoCtrl::OnAuxMixVacSwitchInd );
	
	
	//断链清空资源
	REG_PFUN( OSP_DISCONNECT, &CUmcConfinfoCtrl::OnLinkBreak ); 

	BuildReqEventsMap();
}

void CUmcConfinfoCtrl::BuildReqEventsMap()
{
	REG_REQ_PFUN( ev_umcweb_confmng_listconf_get_req, &CUmcConfinfoCtrl::OnUmcwebListconfGetReq );
	REG_REQ_PFUN( ev_umcweb_list_meetingroom_get_req, &CUmcConfinfoCtrl::OnUmcListMtGetReq );
	REG_REQ_PFUN( ev_umcweb_hangupconf_req, &CUmcConfinfoCtrl::OnUmcwebHangupconfReq );

	REG_REQ_PFUN( ev_umcweb_RefreshConfinfoInfo_nty_req, &CUmcConfinfoCtrl::OnUmcwebRefreshConfinfoInfoNtyReq );
	REG_REQ_PFUN( ev_umcweb_RefreshConfinfo_PollingList_nty_req, &CUmcConfinfoCtrl::OnUmcwebRefreshConfinfoPollingListNtyReq );
	REG_REQ_PFUN( ev_umcweb_RefreshConfinfo_DiscussList_nty_req, &CUmcConfinfoCtrl::OnUmcwebRefreshConfinfoDiscussListNtyReq );

	//会场操作
	REG_REQ_PFUN( ev_umcweb_epoper_startdual_req, &CUmcConfinfoCtrl::OnUmcEpoperStartdualReq );
	REG_REQ_PFUN( ev_umcweb_epoper_stopdual_req, &CUmcConfinfoCtrl::OnUmcEpoperStopdualReq );
	REG_REQ_PFUN( ev_umcweb_epoper_applyspeaker_req, &CUmcConfinfoCtrl::OnUmcEpoperApplyspeakerReq );
	REG_REQ_PFUN( ev_umcweb_epoper_quiet_req, &CUmcConfinfoCtrl::OnUmcEpoperQuietReq );
	REG_REQ_PFUN( ev_umcweb_epoper_mute_req, &CUmcConfinfoCtrl::OnUmcEpoperMuteReq );
	REG_REQ_PFUN( ev_umcweb_epoper_drop_req, &CUmcConfinfoCtrl::OnUmcEpoperDropReq );
	REG_REQ_PFUN( ev_umcweb_epoper_call_req, &CUmcConfinfoCtrl::OnUmcEpoperCallReq );
	REG_REQ_PFUN( ev_umcweb_epoper_selview_req, &CUmcConfinfoCtrl::OnUmcEpoperSelviewReq );

	REG_REQ_PFUN( ev_umcweb_selviewinfo_get_req, &CUmcConfinfoCtrl::OnUmcSelviewInfoGetReq );

	//会议轮询
	REG_REQ_PFUN( ev_umcweb_SuspendTurn_req, &CUmcConfinfoCtrl::OnUmcwebSuspendTurnReq );
	REG_REQ_PFUN( ev_umcweb_StartTurn_req, &CUmcConfinfoCtrl::OnUmcwebStartTurnReq );
	REG_REQ_PFUN( ev_umcweb_UpdateTurn_req, &CUmcConfinfoCtrl::OnUmcwebUpdateTurnReq );
	
	//会议讨论
	REG_REQ_PFUN( ev_umcweb_AuxMixVacSwitch_req, &CUmcConfinfoCtrl::OnUmcwebAuxMixVacSwitchReq );
	REG_REQ_PFUN( ev_umcweb_UpdateAudMixInfo_req, &CUmcConfinfoCtrl::OnUmcwebUpdateAudMixInfoReq );
	REG_REQ_PFUN( ev_umcweb_StartAuxMix_req, &CUmcConfinfoCtrl::OnUmcwebStartAuxMixReq );
}

void CUmcConfinfoCtrl::DispEvent(const CMessage &cMsg)
{
    DISP_FUN( CUmcConfinfoCtrl, cMsg );
}

void CUmcConfinfoCtrl::DispReqEvent( u16 wEvent, const boost::any& arg )
{
    DISP_REQ_FUN( CUmcConfinfoCtrl, wEvent, arg );
}

void CUmcConfinfoCtrl::OnLinkBreak( const CMessage& cMsg )
{
	ClearData();

	PrtMsg( OSP_DISCONNECT, emEventTypeServerRecv,"CUmcConfinfoCtrl::OnLinkBreak"); 
}

void CUmcConfinfoCtrl::OnAddConfListNotify( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	TAddConfList tAddList = *reinterpret_cast<TAddConfList*>( cTpMsg.GetBody() );

	for ( int i = 0; i < tAddList.m_wRefreshNum; i++ ) 
	{
		TConfinfo tConfinfo= tAddList.m_atTmpList[i];
		m_vecTConfinfo.push_back( tConfinfo ); 
		
		PrtMsg( evtp_AddConfList_Notify, emEventTypeServerRecv, "(ID=%d, confName=%s, speakerID = %d DualID=%d)",
			tConfinfo.m_wConfID, tConfinfo.m_achConfName, tConfinfo.m_wSpeaker,tConfinfo.m_wDual );

		//主格式数量
		PrtMsg( "主格式:\n" );
		for ( int n = 0; n < tConfinfo.m_wMainNum; n++ )
		{
			TUmsVidFormat tUmsVidFormatMain = tConfinfo.m_atTpMainVideoRes[n];
			
			PrtMsg( "ConfID=%d, tUmsVidFormatMain[%d]: m_emFormat:%d, m_emRes:%d, m_wFrameRate:%d, m_wBitrate:%d, m_emQualityLvl:%d\n"
				, tConfinfo.m_wConfID, n, tUmsVidFormatMain.m_emFormat, tUmsVidFormatMain.m_emRes, tUmsVidFormatMain.m_wFrameRate, tUmsVidFormatMain.m_wBitrate, tUmsVidFormatMain.m_emQualityLvl );
		}
		
		//双流格式数量
		PrtMsg( "双流格式:\n" );
		for ( int m = 0; m < tConfinfo.m_wMinorNum; m++ )
		{
			TUmsVidFormat tUmsVidFormatDual = tConfinfo.m_atTpMinorVideoRes[m];
			
			PrtMsg( "ConfID=%d, tUmsVidFormatDual[%d]: m_emFormat:%d, m_emRes:%d, m_wFrameRate:%d, m_wBitrate:%d, m_emQualityLvl:%d\n"
				, tConfinfo.m_wConfID, m, tUmsVidFormatDual.m_emFormat, tUmsVidFormatDual.m_emRes, tUmsVidFormatDual.m_wFrameRate, tUmsVidFormatDual.m_wBitrate, tUmsVidFormatDual.m_emQualityLvl );
		}
	}
}

void CUmcConfinfoCtrl::OnUpdateConfCnsListNotify( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	TConfCnsInfo tConfCns = *reinterpret_cast<TConfCnsInfo*>( cTpMsg.GetBody() );

	PrtMsg( evtp_UpdateConfCnsList_Notify, emEventTypeServerRecv, "confID=%d, CNS count=%d, operateType=%d (0:Add, 1: Del, 2: Update )",
		tConfCns.m_wConfID, tConfCns.m_wNum,tConfCns.m_emOpr );

	if ( tConfCns.m_wNum <= 0 ) 
	{
		return;
	}

	TConfinfo* pTConfinfo = GetConfInfoByID( tConfCns.m_wConfID );
	if ( pTConfinfo == NULL )
	{
		return;
	}

	switch( tConfCns.m_emOpr ) 
	{
	case tp_OprType_Add:			//增加
        {
			for ( int n = 0; n < tConfCns.m_wNum; n++ )
			{
				pTConfinfo->m_vecTMtInfo.push_back( tConfCns.m_tConfCnsList[n] );
			}
        }
		break;
	case tp_OprType_Del:			//删除
        {   
			for ( int n = 0; n < tConfCns.m_wNum; n++ )
			{
				pTConfinfo->DelTCnsInfo( tConfCns.m_tConfCnsList[n].m_wEpID );
			}
		 
		}
		break;
	case tp_OprType_Update:			// 更新
        {   
			for ( int n = 0; n < tConfCns.m_wNum; n++ )
			{
				pTConfinfo->UpdTCnsInfo( tConfCns.m_tConfCnsList[n] );
			}
		}
		break;
	default:
		break;
	}


	for ( int n = 0; n < tConfCns.m_wNum; n++ )
	{
		PrtMsg(evtp_UpdateConfCnsList_Notify,emEventTypeServerRecv
			, "msginfo: confID=%d ,cnsID= %d ,cnsRoomName=%s, bOnLine=%d, emCallReason:%d,"
			, tConfCns.m_wConfID, tConfCns.m_tConfCnsList[n].m_wEpID, tConfCns.m_tConfCnsList[n].m_achRoomName, tConfCns.m_tConfCnsList[n].m_bOnline, tConfCns.m_tConfCnsList[n].m_emCallReason );
	}
}

TConfinfo* CUmcConfinfoCtrl::GetConfInfoByID( u16 wConfID )
{
	vector<TConfinfo>::iterator it = m_vecTConfinfo.begin();
	for ( ; it != m_vecTConfinfo.end(); it++ )
	{
		if ( wConfID == it->m_wConfID )
		{
			return &(*it);
		}
	}

	PrtMsg("\n[CUmcConfinfoCtrl::GetConfInfoByID] conf(id=%d) is not exist \n", wConfID);
	
	return NULL;
}

BOOL CUmcConfinfoCtrl::DelConfInfoByID( u16 wConfID )
{
	vector<TConfinfo>::iterator it = m_vecTConfinfo.begin();
	for ( ; it != m_vecTConfinfo.end(); it++ )
	{
		if ( wConfID == it->m_wConfID )
		{
			m_vecTConfinfo.erase(it);

			return TRUE;
		}
	}
	
	return FALSE;
}

void CUmcConfinfoCtrl::OnHungUpConfRsp( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	u16 wConfID = *reinterpret_cast<u16*>( cTpMsg.GetBody() );
	EmTpDropConfRet emRet = *reinterpret_cast<EmTpDropConfRet*>( cTpMsg.GetBody() + sizeof(u16) );
	
	PrtMsg( evtp_HungUpConf_result, emEventTypeServerRecv, "ConfID=%d, emRet=%d ( %d:Success, %d:ConfUnExit )",
		wConfID, emRet, TP_DropConf_Success, TP_DropConf_ConfUnExit );

	//fcgi 应答（json到前端）
	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_hangupconf_res\",\"emRet\":\"%d\"}", emRet );
	
	PrtMsg( ev_umcweb_hangupconf_res, emEventTypeClientSend, "emRet:%d", emRet );
}

void CUmcConfinfoCtrl::OnDelConfListNotify( const CMessage& cMsg )
{
	CTpMsg cTpMsg( &cMsg );
	TDelConfList tAddList = *reinterpret_cast<TDelConfList*>( cTpMsg.GetBody() );

	string strPrt;
	
	for ( int i = 0; i< tAddList.m_wRefreshNum; i++ )
	{
		char arrTemp[50];
		sprintf( arrTemp, "(ConfID=%d ) ",tAddList.m_awConfIDList[i] );
		strPrt += arrTemp;
		
		BOOL bRet = DelConfInfoByID( tAddList.m_awConfIDList[i] );
		if ( !bRet )
		{
            strPrt += "未找到；";
        } 
	}
	
	PrtMsg( evtp_DelConflist_Notify, emEventTypeServerRecv, "%s", strPrt.c_str() );
}

void CUmcConfinfoCtrl::OnStartdualRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
    TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() ); 
    EmTPDualReason emRet = * reinterpret_cast<EmTPDualReason*>( kdvMsg.GetBody() + sizeof(TConfEpID) );
    PrtMsg(evtp_StartDual_Ind,emEventTypeServerRecv,"ConfID=%d, EpID=%d ,erroCode=%d \
        (%d:Accept, %d:DualBusy,%d:Preemptive, %d:PeerReject, %d:PeerStop,%d:NoVideo)",
        tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID,emRet ,emTpDualAccept,
        emTpDualBusy,emTpDualPreemptive,emTpDualPeerReject,emTpDualPeerStop,emTpDualNoVideo) ; 

	TConfinfo* pTConfinfo =  GetConfInfoByID(tConfEpInfo.m_wConfID);
    if ( pTConfinfo != NULL )
    {
        pTConfinfo->m_wDual = tConfEpInfo.m_wEpID;
    }
	
    //fcgi 应答（json到前端）
	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_epoper_startdual_res\",\"emRet\":\"%d\"}", emRet );
	
	PrtMsg( ev_umcweb_epoper_startdual_res, emEventTypeClientSend, "emRet:%d", emRet );
}

void CUmcConfinfoCtrl::OnStopdualRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
    TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() ); 
    EmTPDualReason emRet = * reinterpret_cast<EmTPDualReason*>( kdvMsg.GetBody() + sizeof(TConfEpID) );
    PrtMsg(evtp_StopDual_Ind,emEventTypeServerRecv,"ConfID=%d, EpID=%d ,erroCode=%d \
        (%d:Accept, %d:DualBusy,%d:Preemptive, %d:PeerReject, %d:PeerStop,%d:NoVideo)",
        tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID,emRet ,emTpDualAccept,
        emTpDualBusy,emTpDualPreemptive,emTpDualPeerReject,emTpDualPeerStop,emTpDualNoVideo) ; 

	TConfinfo* pTConfinfo =  GetConfInfoByID(tConfEpInfo.m_wConfID);
    if ( pTConfinfo != NULL )
    {
        pTConfinfo->m_wDual = TP_INVALID_INDEX;
    }

	
    //fcgi 应答（json到前端）
	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_epoper_stopdual_res\",\"emRet\":\"%d\"}", emRet );
	
	PrtMsg( ev_umcweb_epoper_stopdual_res, emEventTypeClientSend, "emRet:%d", emRet );
}

void CUmcConfinfoCtrl::OnDualNotify( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
    TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() );  
    PrtMsg(evtp_DualEp_Notify,emEventTypeServerRecv,"ConfID=%d, EpID=%d ",
        tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID ) ; 
    
    TConfinfo* pTConfinfo =  GetConfInfoByID(tConfEpInfo.m_wConfID);
    if ( pTConfinfo != NULL )
    {
        pTConfinfo->m_wDual = tConfEpInfo.m_wEpID;
    }
}

void CUmcConfinfoCtrl::OnSpeakerRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
	TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() ); 
	EmTpApplySpeakerRet emRet = * reinterpret_cast<EmTpApplySpeakerRet*>( kdvMsg.GetBody() + sizeof(TConfEpID) );

    PrtMsg(evtp_ApplySpeaker_result,emEventTypeServerRecv,"ConfID=%d, EpID=%d , \
		result=%d (%d:Success, %d:ConfUnExist, %d:EpIDError, %d:EpStateError)",
		tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID,emRet,TP_ApplySpeaker_Success,
		TP_ApplySpeaker_ConfUnExist,TP_ApplySpeaker_EpIDError,TP_ApplySpeaker_EpStateError) ; 

	TConfinfo* pTConfinfo =  GetConfInfoByID(tConfEpInfo.m_wConfID);
    if ( pTConfinfo != NULL )
    {
        pTConfinfo->m_wSpeaker = tConfEpInfo.m_wEpID;
    }
	
	//fcgi 应答（json到前端）
	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_epoper_applyspeaker_res\",\"emRet\":\"%d\"}", emRet );
	
	PrtMsg( ev_umcweb_epoper_applyspeaker_res, emEventTypeClientSend, "emRet:%d", emRet );
}

void CUmcConfinfoCtrl::OnSpeakerNotify( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
    TConfEpID tConfEp = *reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() );
    
    PrtMsg( evtp_SpeakerChange_Notify,emEventTypeServerRecv,"ConfID=%d, SpeakerCnsID=%d",
        tConfEp.m_wConfID, tConfEp.m_wEpID );
    
	TConfinfo* pTConfinfo =  GetConfInfoByID(tConfEp.m_wConfID);
    if ( pTConfinfo != NULL )
    {
        pTConfinfo->m_wSpeaker = tConfEp.m_wEpID;
    }
}

void CUmcConfinfoCtrl::OnQuietRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
    TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() ); 
    BOOL32 bRet = * reinterpret_cast<BOOL32*>( kdvMsg.GetBody() + sizeof(TConfEpID) );
    PrtMsg(evtp_QuietEp_Ind,emEventTypeServerRecv,"ConfID=%d, EpID=%d ,bQuiet=%d",
        tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID,bRet ) ; 
	
    TConfinfo* pTConfinfo =  GetConfInfoByID(tConfEpInfo.m_wConfID);
    if ( pTConfinfo != NULL )
    {
        TUMCMtInfo* pTUMCMtInfo = pTConfinfo->GetCnsInfoByID(tConfEpInfo.m_wEpID);
		if ( pTUMCMtInfo == NULL )
		{
			return;
		}

		pTUMCMtInfo->m_bQuiet = bRet; 
    }
	
	//fcgi 应答（json到前端）
	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_epoper_quiet_res\",\"bRet\":\"%d\"}", TRUE );
	
	PrtMsg( ev_umcweb_epoper_quiet_res, emEventTypeClientSend, "bRet:%d", TRUE );
}

void CUmcConfinfoCtrl::OnMuteRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
    TConfEpID  tConfEpInfo  = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() ); 
    BOOL32 bRet = * reinterpret_cast<BOOL32*>( kdvMsg.GetBody() + sizeof(TConfEpID) );
    PrtMsg(evtp_MuteEp_Ind,emEventTypeServerRecv,"ConfID=%d, EpID=%d ,bMute=%d  ",
        tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID,bRet ) ; 
    
	TConfinfo* pTConfinfo =  GetConfInfoByID(tConfEpInfo.m_wConfID);
    if ( pTConfinfo != NULL )
    {
        TUMCMtInfo* pTUMCMtInfo = pTConfinfo->GetCnsInfoByID(tConfEpInfo.m_wEpID);
		if ( pTUMCMtInfo == NULL )
		{
			return;
		}
		
		pTUMCMtInfo->m_bMute = bRet; 
    }
    
    //fcgi 应答（json到前端）
	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_epoper_mute_res\",\"bRet\":\"%d\"}", TRUE );
	
	PrtMsg( ev_umcweb_epoper_mute_res, emEventTypeClientSend, "bRet:%d", TRUE );
}

void CUmcConfinfoCtrl::OnDropRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
    TConfEpID  tConfEpInfo  = *reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() ); 
    EmCnsCallReason emRet = *reinterpret_cast<EmCnsCallReason*>( kdvMsg.GetBody() + sizeof(TConfEpID) );
	
	//ums确认，只有以下三种情况 -- 20140625 by xhx
	PrtMsg( evtp_DropEp_Ind, emEventTypeServerRecv, "ConfID=%d, CNSID=%d, errCode=%d ( \
		%d:hungup, %d:dstnotfind, %d:NoConf )",
		tConfEpInfo.m_wConfID, tConfEpInfo.m_wEpID, emRet,
		EmCnsCallReason_hungup, EmCnsCallReason_dstnotfind, EmCnsCallReason_NoConf );
	
	//fcgi 应答（json到前端）
	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_epoper_drop_res\",\"emRet\":\"%d\"}", emRet );
	
	PrtMsg( ev_umcweb_epoper_drop_res, emEventTypeClientSend, "emRet:%d", emRet );
}

void CUmcConfinfoCtrl::OnCallRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
	TConfEpID tConfEpID = * reinterpret_cast<TConfEpID*>( kdvMsg.GetBody() );
	EmCnsCallReason emRet = * reinterpret_cast<EmCnsCallReason*>( kdvMsg.GetBody() + sizeof(TConfEpID) );
	
    PrtMsg( evtp_CallExistEP_result, emEventTypeServerRecv, "ConfID=%d, EpID=%d, errCode=%d ( \
		 %d:success, %d:hungup, %d:Unreachable, %d:resourcefull, %d:dstnotfind, %d:Busy, %d:LocalReason, %d:NoConf, %d:Existe \
		 %d:Rejected, %d:peerhungup, %d:Abnormal, %d:PeerAbnormal, %d:ConfOver, %d:cncallexception, %d:ConfExist, %d:unknown )",
		 tConfEpID.m_wConfID, tConfEpID.m_wEpID, emRet,
		 EmCnsCallReason_success, EmCnsCallReason_hungup, 
		 EmCnsCallReason_Unreachable, EmCnsCallReason_resourcefull, EmCnsCallReason_dstnotfind,
		 EmCnsCallReason_Busy, EmCnsCallReason_Local,EmCnsCallReason_NoConf,EmCnsCallReason_Exist,
		 EmCnsCallReason_Rejected, EmCnsCallReason_peerhungup, EmCnsCallReason_Abnormal, EmCnsCallReason_PeerAbnormal,
		 EmCnsCallReason_ConfOver, EmCnsCallReason_cncallexception, EmCnsCallReason_ConfExist, EmCnsCallReason_unknown);

	//fcgi 应答（json到前端）
	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_epoper_call_res\",\"emRet\":\"%d\"}", emRet );
	
	PrtMsg( ev_umcweb_epoper_call_res, emEventTypeClientSend, "emRet:%d", emRet );
}

void CUmcConfinfoCtrl::OnSelViewNotify( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
    TTPSelViewNtfy tTPSelViewNtfy = *reinterpret_cast<TTPSelViewNtfy*>( kdvMsg.GetBody() );
    
	TTPSelViewReq tTPSelViewReq = tTPSelViewNtfy.m_tSelView;
	EmTpOprType emTpOprType = tTPSelViewNtfy.m_emOpr;

	PrtMsg( ev_UMS_UMC_SelView_Ntfy,emEventTypeServerRecv,"ConfID=%d, EpID=%d, ScreenIndx=%d, Type%d(%d:画面合成,%d:会场) \
		, DstID:%d, bSel:%d, emTpOprType=%d(%d:add, %d:del, %d:upd, %d:clear)"
		, tTPSelViewReq.m_wConfID, tTPSelViewReq.m_wEpID, tTPSelViewReq.m_wScreenIndx, tTPSelViewReq.m_emType, EmEpType_Ter, EmEpType_Eqp
		, tTPSelViewReq.m_wDstID, tTPSelViewReq.m_bSel, emTpOprType, tp_OprType_Add, tp_OprType_Del, tp_OprType_Update, tp_OprType_NULL );

	TConfinfo* pTConfinfo = GetConfInfoByID(tTPSelViewReq.m_wConfID);
	if ( pTConfinfo == NULL )
	{
		return;
	}
	
	TUMCMtInfo* pTUMCMtInfo = pTConfinfo->GetCnsInfoByID(tTPSelViewReq.m_wEpID);
	if ( pTUMCMtInfo == NULL )
	{
		return;
	}

	switch( emTpOprType )
	{
	case tp_OprType_Add:
		{
			pTUMCMtInfo->m_tUMCSelViewInfo[tTPSelViewReq.m_wScreenIndx].m_emType = tTPSelViewReq.m_emType;
			pTUMCMtInfo->m_tUMCSelViewInfo[tTPSelViewReq.m_wScreenIndx].m_wID = tTPSelViewReq.m_wDstID;

			break;
		}
	case tp_OprType_Del:
		{
			pTUMCMtInfo->m_tUMCSelViewInfo[tTPSelViewReq.m_wScreenIndx].Clear();

			break;
		}
	case tp_OprType_Update:
		{
			pTUMCMtInfo->m_tUMCSelViewInfo[tTPSelViewReq.m_wScreenIndx].m_emType = tTPSelViewReq.m_emType;
			pTUMCMtInfo->m_tUMCSelViewInfo[tTPSelViewReq.m_wScreenIndx].m_wID = tTPSelViewReq.m_wDstID;

			break;
		}
	case tp_OprType_NULL:
		{
			for ( int i = 0; i < UMC_MAX_SCREENNUM; i++ )
			{
				pTUMCMtInfo->m_tUMCSelViewInfo[i].Clear();
			}

			break;
		}
	default:
		break;
	}
}

void CUmcConfinfoCtrl::OnSelViewRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
	TTPSelViewInd tTPSelViewInd = * reinterpret_cast<TTPSelViewInd*>( kdvMsg.GetBody() );
	
    PrtMsg( ev_UMS_UMC_SelView_Ind, emEventTypeServerRecv, "confid:%d, epid:%d, screenIndex:%d, bSel:%d, emType:%d, dstEpID:%d, emRet:%d"
		, tTPSelViewInd.m_tSelView.m_wConfID, tTPSelViewInd.m_tSelView.m_wEpID, tTPSelViewInd.m_tSelView.m_wScreenIndx
		, tTPSelViewInd.m_tSelView.m_bSel, tTPSelViewInd.m_tSelView.m_emType, tTPSelViewInd.m_tSelView.m_wDstID, tTPSelViewInd.m_emRet );

	//fcgi 应答（json到前端）
	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_epoper_selview_res\",\"emRet\":\"%d\"}", tTPSelViewInd.m_emRet );
	
	PrtMsg( ev_umcweb_epoper_selview_res, emEventTypeClientSend, "emRet:%d", tTPSelViewInd.m_emRet );
}

void CUmcConfinfoCtrl::OnUpdateConfTurnlistNotify( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
    TTpPollListNtfy tTpPollListNtfy = *reinterpret_cast<TTpPollListNtfy*>( kdvMsg.GetBody() );
	
	PrtMsg( evtp_UpdateConfTurnlist_Notify, emEventTypeServerRecv, "wConfID= %d, nFlag= %d, wTotalNum= %d, wCurNum= %d", 
		tTpPollListNtfy.m_wConfID, tTpPollListNtfy.m_nFlag, tTpPollListNtfy.m_wTotalNum, tTpPollListNtfy.m_wCurNum );
	
	if ( tTpPollListNtfy.m_wCurNum <= 0 ) 
	{ 
		return;
	}
    
	TConfinfo* pTConfinfo = GetConfInfoByID( tTpPollListNtfy.m_wConfID );
	if ( pTConfinfo == NULL )
	{
		return;
	}

	if ( tTpPollListNtfy.m_nFlag != pTConfinfo->m_nFlag )
	{
		pTConfinfo->m_vecPollList.clear();
	}

	pTConfinfo->m_nFlag = tTpPollListNtfy.m_nFlag;
	pTConfinfo->m_wInterval = tTpPollListNtfy.m_wInterval;

	for ( u16 wIndex = 0; wIndex < tTpPollListNtfy.m_wCurNum; wIndex++ )
	{
		pTConfinfo->m_vecPollList.push_back( tTpPollListNtfy.m_awList[wIndex] );
	}
    
	u16 wCurPollSize = pTConfinfo->m_vecPollList.size();
	if ( PTR_SESSION->m_bRefresh && wCurPollSize == tTpPollListNtfy.m_wTotalNum )
	{
		UmcwebRefreshConfinfoPollingList( tTpPollListNtfy.m_wConfID );
		
		PTR_SESSION->m_bRefresh = FALSE; 
		//操作成功，手动释放锁
		PTR_MSGDRIVER->ReleaseLock();
	}
}

u16 CUmcConfinfoCtrl::UpdateTurnReq( const TConfTurnInfo &tConfTurnInfo )
{
	CTpMsg *pkdvMsg = PTR_MSGDRIVER->GetKdvMsgPtr(); 
    pkdvMsg->SetEvent( evtp_UpdateTurn_cmd );
	pkdvMsg->SetBody( &tConfTurnInfo, sizeof(TConfTurnInfo) );
	
	PrtMsg( evtp_UpdateTurn_cmd, emEventTypeServerSend, "wConfID= %d, wPollCount= %d", 
		tConfTurnInfo.m_wConfID, tConfTurnInfo.m_atTurnList.m_wNum);

	PTR_SESSION->m_bRefresh = TRUE;
	//OSP_RSP_SELF_HANDLE:自己处理锁释放
	u16 wRe = PTR_MSGDRIVER->PostCommand(this, OSP_RSP_SELF_HANDLE,TYPE_TPMSG);
	return wRe;
}

void CUmcConfinfoCtrl::OnUpdateTurnInd( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
    TTpPollListInd tTpPollListInd = *reinterpret_cast<TTpPollListInd*>( kdvMsg.GetBody() );

    PrtMsg( evtp_UpdateTurn_ind, emEventTypeServerRecv, "wConfID= %d, nFlag= %d, wRet= %d ",
		tTpPollListInd.m_wConfID, tTpPollListInd.m_nFlag, tTpPollListInd.m_wRet );
}

u16 CUmcConfinfoCtrl::StartTurnReq( const u16 wConfID )
{
	CTpMsg *pkdvMsg = PTR_MSGDRIVER->GetKdvMsgPtr(); 
    pkdvMsg->SetEvent( evtp_StartTurn_cmd );
	pkdvMsg->SetBody( &wConfID, sizeof(u16) );
	
	PrtMsg( evtp_StartTurn_cmd, emEventTypeServerSend, "wConfID= %d", wConfID );
	
	u16 wRe = PTR_MSGDRIVER->PostCommand(this, evtp_StartTurn_ind, TYPE_TPMSG);
	return wRe;
}

void CUmcConfinfoCtrl::OnStartTurnInd( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
    u16 nConfID  = *reinterpret_cast<u16*>( kdvMsg.GetBody() );
	EmTPPollResult ret = *reinterpret_cast<EmTPPollResult*>( kdvMsg.GetBody() + sizeof(u16) );

    PrtMsg( evtp_StartTurn_ind, emEventTypeServerRecv, "wConfID= %d, ret= %d ", nConfID, ret );

	TConfinfo* pTConfinfo = GetConfInfoByID( nConfID );
	if ( pTConfinfo == NULL )
	{
		return;
	}

	PrtMsg( ev_umcweb_StartTurn_res, emEventTypeClientSend, "wConfID= %d, ret= %d(0:emPollSucceed; 1:emPollFailUnKown; 2:emPollInvalidEp; 3:emPollResFull; 4:emPollNoChair; 5:emPollChairNoLine; 6:emPollServerBusy)", nConfID, ret );	
	
	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_StartTurn_res\",\"bStart\":\"%d\",\"emTPPollResult\":\"%d\"}", 1, ret);
}

u16 CUmcConfinfoCtrl::StopTurnReq( const u16 wConfID )
{
	CTpMsg *pkdvMsg = PTR_MSGDRIVER->GetKdvMsgPtr(); 
    pkdvMsg->SetEvent( evtp_StopTurn_cmd );
	pkdvMsg->SetBody( &wConfID, sizeof(u16) );
	
	PrtMsg( evtp_StopTurn_cmd, emEventTypeServerSend, "wConfID= %d", wConfID );
	
	u16 wRe = PTR_MSGDRIVER->PostCommand(this, evtp_StopTurn_ind, TYPE_TPMSG);
	return wRe;
}

void CUmcConfinfoCtrl::OnStopTurnInd( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
    u16 nConfID  = *reinterpret_cast<u16*>( kdvMsg.GetBody() );
	EmTPPollResult ret = *reinterpret_cast<EmTPPollResult*>( kdvMsg.GetBody() + sizeof(u16) );

    PrtMsg( evtp_StopTurn_ind, emEventTypeServerRecv, "wConfID= %d, ret= %d ", nConfID, ret );
    
	TConfinfo* pTConfinfo = GetConfInfoByID( nConfID );
	if ( pTConfinfo == NULL )
	{
		return;
	}

	PrtMsg( ev_umcweb_StartTurn_res, emEventTypeClientSend, "wConfID= %d, ret= %d(0:emPollSucceed; 1:emPollFailUnKown; 2:emPollInvalidEp; 3:emPollResFull; 4:emPollNoChair; 5:emPollChairNoLine; 6:emPollServerBusy)", nConfID, ret );	
	
	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_StartTurn_res\",\"bStart\":\"%d\",\"emTPPollResult\":\"%d\"}", 0, ret);
}

u16 CUmcConfinfoCtrl::SuspendTurnReq( const u16 wConfID, const BOOL32 bSuspend )
{
	CTpMsg *pkdvMsg = PTR_MSGDRIVER->GetKdvMsgPtr(); 
    pkdvMsg->SetEvent( evtp_SuspendTurn_cmd );
	pkdvMsg->SetBody( &wConfID, sizeof(u16) );
	pkdvMsg->CatBody( &bSuspend, sizeof(BOOL32) );
	
	PrtMsg( evtp_SuspendTurn_cmd, emEventTypeServerSend, "wConfID= %d, bSuspend= %d", wConfID, bSuspend );
	
	u16 wRe = PTR_MSGDRIVER->PostCommand(this, evtp_SuspendTurn_ind, TYPE_TPMSG);
	return wRe;
}

void CUmcConfinfoCtrl::OnSuspendTurnInd( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
    u16 nConfID  = *reinterpret_cast<u16*>( kdvMsg.GetBody() );
	EmTPPollResult ret = *reinterpret_cast<EmTPPollResult*>( kdvMsg.GetBody() + sizeof(u16) );
	
    PrtMsg( evtp_SuspendTurn_ind, emEventTypeServerRecv, "wConfID= %d, ret= %d ", nConfID, ret );
    
	TConfinfo* pTConfinfo = GetConfInfoByID( nConfID );
	if ( pTConfinfo == NULL )
	{
		return;
	}

	PrtMsg( ev_umcweb_SuspendTurn_res, emEventTypeClientSend, "wConfID= %d, ret= %d(0:emPollSucceed; 1:emPollFailUnKown; 2:emPollInvalidEp; 3:emPollResFull; 4:emPollNoChair; 5:emPollChairNoLine; 6:emPollServerBusy)", nConfID, ret );	
	
	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_SuspendTurn_res\",\"emTPPollResult\":\"%d\"}", ret);
}

void CUmcConfinfoCtrl::OnTurnStatNotify( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
    TTpPollStat tTpPollStat  = *reinterpret_cast<TTpPollStat*>( kdvMsg.GetBody() );
	
    PrtMsg( evtp_TurnStat_ntfy, emEventTypeServerRecv, "wConfID= %d, emStat= %d ", tTpPollStat.m_wConfID, tTpPollStat.m_emStat );
    
	TConfinfo* pTConfinfo = GetConfInfoByID( tTpPollStat.m_wConfID );
	if ( pTConfinfo == NULL )
	{
		return;
	}	

	pTConfinfo->m_emStat = tTpPollStat.m_emStat;
}

void CUmcConfinfoCtrl::OnAuxMixInfoNotify( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
	TConfAuxMixInfo tConfAuxMixInfo = *reinterpret_cast<TConfAuxMixInfo*>( kdvMsg.GetBody() );

	PrtMsg( evtp_AuxMixInfo_Notify, emEventTypeServerRecv, "ConfID= %d, bStart= %d, bVacOn= %d, wSpeakerIndex= %d", 
		tConfAuxMixInfo.m_wConfID, tConfAuxMixInfo.m_bStart, tConfAuxMixInfo.m_bVacOn, tConfAuxMixInfo.m_atAuxMixList.m_wSpeakerIndex );

	TConfinfo* pTConfinfo = GetConfInfoByID( tConfAuxMixInfo.m_wConfID );
	if ( pTConfinfo == NULL )
	{
		return;
	}

	pTConfinfo->m_tConfAuxMixInfo.Clear();
	memcpy( &(pTConfinfo->m_tConfAuxMixInfo), &tConfAuxMixInfo, sizeof(TConfAuxMixInfo) );

	pTConfinfo->m_wSpeaker = tConfAuxMixInfo.m_atAuxMixList.m_wSpeakerIndex;

	if ( PTR_SESSION->m_bRefresh )
	{
		UmcwebRefreshConfinfoDiscussList( tConfAuxMixInfo.m_wConfID );
		
		PTR_SESSION->m_bRefresh = FALSE; 
		//操作成功，手动释放锁
		PTR_MSGDRIVER->ReleaseLock();
	}
}

u16 CUmcConfinfoCtrl::UpdateAudMixInfoReq( const TDiscussListOpr& tDiscussListOpr )
{	
	CTpMsg *pkdvMsg = PTR_MSGDRIVER->GetKdvMsgPtr(); 
    pkdvMsg->SetEvent( evtp_UpdateAudMixInfo_cmd );
	pkdvMsg->SetBody( &tDiscussListOpr, sizeof(TDiscussListOpr) );

	PrtMsg( evtp_UpdateAudMixInfo_cmd, emEventTypeServerSend, "wConfId= %d, wNum= %d, emOprType= %d(0:em_DisListOpr_Add, 1:em_DisListOpr_Del)",
		tDiscussListOpr.m_wConfId, tDiscussListOpr.m_wNum, tDiscussListOpr.m_emOprType );

	PTR_SESSION->m_bRefresh = TRUE;
	//OSP_RSP_SELF_HANDLE:自己处理锁释放
    u16 wRe = PTR_MSGDRIVER->PostCommand(this, OSP_RSP_SELF_HANDLE,TYPE_TPMSG);
	return wRe;
}

void CUmcConfinfoCtrl::OnUpdateAudMixInfoInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	TDiscussListOpr tDiscussListOpr = *reinterpret_cast<TDiscussListOpr*>( cTpMsg.GetBody() );
	
	PrtMsg( evtp_UpdateAudMixInfo_Ind, emEventTypeServerRecv, "wConfId= %d, wNum= %d, emOprType= %d, emOprReslt= %d",
		tDiscussListOpr.m_wConfId, tDiscussListOpr.m_wNum, tDiscussListOpr.m_emOprType, tDiscussListOpr.m_emOprReslt );
}

u16 CUmcConfinfoCtrl::StartAuxMixReq( const TConfAuxMixInfo& tConfAuxMixInfo )
{
	CTpMsg *pkdvMsg = PTR_MSGDRIVER->GetKdvMsgPtr(); 
    pkdvMsg->SetEvent( evtp_StartAuxMix_cmd );
	pkdvMsg->SetBody( &tConfAuxMixInfo, sizeof(TConfAuxMixInfo) );

	PrtMsg( evtp_StartAuxMix_cmd, emEventTypeServerSend, "wConfID= %d, bStart= %d, bVacOn= %d",
		tConfAuxMixInfo.m_wConfID, tConfAuxMixInfo.m_bStart, tConfAuxMixInfo.m_bVacOn );
	
	PTR_SESSION->m_bRefresh = TRUE;
	//OSP_RSP_SELF_HANDLE:自己处理锁释放
    u16 wRe = PTR_MSGDRIVER->PostCommand(this, OSP_RSP_SELF_HANDLE,TYPE_TPMSG);
	return wRe;
}

void CUmcConfinfoCtrl::OnStartAuxMixInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
    TConfAuxMixInfo tConfAuxMixInfo = *reinterpret_cast<TConfAuxMixInfo*>( cTpMsg.GetBody() );
	
	PrtMsg( evtp_StartAuxMix_ind, emEventTypeServerRecv, "wConfID= %d, bStart= %d, bVacOn= %d",
		tConfAuxMixInfo.m_wConfID, tConfAuxMixInfo.m_bStart, tConfAuxMixInfo.m_bVacOn );	
}

u16 CUmcConfinfoCtrl::AuxMixVacSwitchReq( const TConfAuxMixVacOpr& tConfAuxMixVacOpr )
{
	CTpMsg *pkdvMsg = PTR_MSGDRIVER->GetKdvMsgPtr(); 
    pkdvMsg->SetEvent( ev_AuxMixVacSwitch );
	pkdvMsg->SetBody( &tConfAuxMixVacOpr, sizeof(TConfAuxMixVacOpr) );
	
	PrtMsg( ev_AuxMixVacSwitch, emEventTypeServerSend, "wConfID= %d, bVacOn= %d, wOprRet= %d",
		tConfAuxMixVacOpr.m_wConfID, tConfAuxMixVacOpr.m_bVacOn, tConfAuxMixVacOpr.m_wOprRet );
	
	u16 wRe = PTR_MSGDRIVER->PostCommand(this, ev_AuxMixVacSwitchInd, TYPE_TPMSG);
	return wRe;
}

void CUmcConfinfoCtrl::OnAuxMixVacSwitchInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	
    TConfAuxMixVacOpr tConfAuxMixVacOpr = *reinterpret_cast<TConfAuxMixVacOpr*>( cTpMsg.GetBody() );
	
	PrtMsg( ev_AuxMixVacSwitchInd, emEventTypeServerRecv, "wConfID= %d, bVacOn= %d, wOprRet= %d",
		tConfAuxMixVacOpr.m_wConfID, tConfAuxMixVacOpr.m_bVacOn, tConfAuxMixVacOpr.m_wOprRet );	

	PrtMsg( ev_umcweb_AuxMixVacSwitch_res, emEventTypeClientSend, "wConfID= %d, bVacOn= %d, wOprRet= %d",
		tConfAuxMixVacOpr.m_wConfID, tConfAuxMixVacOpr.m_bVacOn, tConfAuxMixVacOpr.m_wOprRet );	

	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_AuxMixVacSwitch_res\",\"bVacOn\":\"%d\",\"wOprRet\":\"%d\"}",
		tConfAuxMixVacOpr.m_bVacOn, tConfAuxMixVacOpr.m_wOprRet );
}

void CUmcConfinfoCtrl::ShowConfinfo()
{
	PrtMsg( "\n--------------------会议信息---------------------\n" );

	vector<TConfinfo>::iterator it = m_vecTConfinfo.begin();
	for ( ; it != m_vecTConfinfo.end(); it++ )
	{
		TConfinfo tConfinfo = *it;

		//基本信息
		PrtMsg( "\n----------------------------ConfId:%d, ConfName:%s, ConfE164:%s, MainNum:%d, MinorNum:%d, speakerID:%d, DualID=%d-------------------------------\n"
			, tConfinfo.m_wConfID, tConfinfo.m_achConfName, tConfinfo.m_achConfE164, tConfinfo.m_wMainNum, tConfinfo.m_wMinorNum, tConfinfo.m_wSpeaker,tConfinfo.m_wDual );

		//主格式数量
		PrtMsg( "主格式:\n" );
		for ( int n = 0; n < tConfinfo.m_wMainNum; n++ )
		{
			TUmsVidFormat tUmsVidFormatMain = tConfinfo.m_atTpMainVideoRes[n];
			
			PrtMsg( "ConfID=%d, tUmsVidFormatMain[%d]: m_emFormat:%d, m_emRes:%d, m_wFrameRate:%d, m_wBitrate:%d, m_emQualityLvl:%d\n"
				, tConfinfo.m_wConfID, n, tUmsVidFormatMain.m_emFormat, tUmsVidFormatMain.m_emRes, tUmsVidFormatMain.m_wFrameRate, tUmsVidFormatMain.m_wBitrate, tUmsVidFormatMain.m_emQualityLvl );
		}
		
		//双流格式数量
		PrtMsg( "双流格式:\n" );
		for ( int m = 0; m < tConfinfo.m_wMinorNum; m++ )
		{
			TUmsVidFormat tUmsVidFormatDual = tConfinfo.m_atTpMinorVideoRes[m];
			
			PrtMsg( "ConfID=%d, tUmsVidFormatDual[%d]: m_emFormat:%d, m_emRes:%d, m_wFrameRate:%d, m_wBitrate:%d, m_emQualityLvl:%d\n"
				, tConfinfo.m_wConfID, m, tUmsVidFormatDual.m_emFormat, tUmsVidFormatDual.m_emRes, tUmsVidFormatDual.m_wFrameRate, tUmsVidFormatDual.m_wBitrate, tUmsVidFormatDual.m_emQualityLvl );
		}

		//会场信息
		PrtMsg( "会场信息:\n" );
		vector<TUMCMtInfo>::iterator itEp = tConfinfo.m_vecTMtInfo.begin();
		for ( ; itEp != tConfinfo.m_vecTMtInfo.end(); itEp++ )
		{
			TUMCMtInfo tUMCMtInfo = *itEp;

			PrtMsg("ConfID=%d ,cnsID= %d ,cnsRoomName=%s, bOnLine=%d, emCallReason:%d\n"
				, tConfinfo.m_wConfID, tUMCMtInfo.m_wEpID, tUMCMtInfo.m_achRoomName, tUMCMtInfo.m_bOnline, tUMCMtInfo.m_emCallReason );
		}
	}
}

u16 CUmcConfinfoCtrl::OnUmcwebListconfGetReq(const boost::any& arg)
{
	PrtMsg( ev_umcweb_confmng_listconf_get_req, emEventTypeClientRecv, "" );

	std::string strJson;

	if ( m_vecTConfinfo.size() == 0 )
	{
		strJson = "{\"event\":\"ev_umcweb_confmng_listconf_get_res\",\"count\":\"0\"}";
	}
	else
	{
		string strJsonHead = "{\"event\":\"ev_umcweb_confmng_listconf_get_res\",\"items\":";
		
		vector<string> vecStrJson;
		
		vector<TConfinfo>::iterator it = m_vecTConfinfo.begin();
		for ( ; it != m_vecTConfinfo.end(); it++ )
		{
			TConfinfo tConfinfo = *it;

			int nId = tConfinfo.m_wConfID;
			string strConfName = tConfinfo.m_achConfName;

			char str_time[100];
			struct tm *local_time = NULL;
			local_time = localtime(&tConfinfo.m_tStartTime);
			strftime(str_time, sizeof(str_time), "%Y-%m-%d %H:%M:%S", local_time);

			string strChairroomName = tConfinfo.GetChairManAliars();

			int nRoom = tConfinfo.m_vecTMtInfo.size();

			time_t now;
			struct tm *timenow;
			time(&now);
			timenow = localtime(&now);

			int nInterval = now - tConfinfo.m_tStartTime;
			
			char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
			sprintf( chItem, "{\"confId\":\"%d\",\"confName\":\"%s\",\"startTime\":\"%s\",\"chairroomName\":\"%s\",\"roomNumber\":\"%d\",\"interval\":\"%d\"}"
				, nId, strConfName.c_str(), str_time, strChairroomName.c_str(), nRoom, nInterval );
			
			vecStrJson.push_back(chItem);
		}
		
		strJson = COwsCommon::CreateStringJson( strJsonHead, vecStrJson );
	}
	
	PTR_FCGIPRINTF( strJson.c_str() );
	PrtMsg( ev_umcweb_confmng_listconf_get_res, emEventTypeClientSend, "strJson:%s", strJson.c_str() );
	
	return NO_ERROR;
}

u16 CUmcConfinfoCtrl::OnUmcListMtGetReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strConfID = COwsCommon::GetPropertyTreeVar( pt, "confid" );
	std::string strSearch = COwsCommon::GetPropertyTreeVar( pt, "search" );
	

	PrtMsg( ev_umcweb_list_meetingroom_get_req, emEventTypeClientRecv, "confid:%s, search:%s", strConfID.c_str(), strSearch.c_str() );

	int nConfID = atoi(strConfID.c_str());

	std::string strJson;

	TConfinfo* pTConfinfo = GetConfInfoByID(nConfID);
	if ( pTConfinfo == NULL )
	{
		strJson = "{\"event\":\"ev_umcweb_list_meetingroom_get_res\",\"count\":\"0\"}";
	}
	else
	{
		string strJsonHead = "{\"event\":\"ev_umcweb_list_meetingroom_get_res\",\"items\":";
		
		vector<string> vecStrJson;
		
		vector<TUMCMtInfo>::iterator it = pTConfinfo->m_vecTMtInfo.begin();
		for ( ; it != pTConfinfo->m_vecTMtInfo.end(); it++ )
		{
			TUMCMtInfo tUMCMtInfo = *it;

			string strMTName = tUMCMtInfo.m_achRoomName;

			if ( strSearch != "" )
			{
				if ( strMTName.find(strSearch.c_str()) == -1 )
				{
					continue;
				}
			}
			
			
			std::string strIp;
			in_addr tAddr;
			tAddr.s_addr = tUMCMtInfo.m_dwRoomIp;
			strIp = inet_ntoa(tAddr);

			BOOL bDual = FALSE;
			if ( pTConfinfo->m_wDual == tUMCMtInfo.m_wEpID )
			{
				bDual = TRUE;
			}

			BOOL bSpeaker = FALSE;
			if ( pTConfinfo->m_wSpeaker == tUMCMtInfo.m_wEpID )
			{
				bSpeaker = TRUE;
			}

			BOOL bSelview = FALSE;
			if ( tUMCMtInfo.m_tUMCSelViewInfo[0] != TP_INVALID_INDEX )
			{
				bSelview = TRUE;
			}
			
			char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
			sprintf( chItem, "{\"epId\":\"%d\",\"achMeetName\":\"%s\",\"achE164\":\"%s\",\"achMeetIp\":\"%s\",\"bOnline\":\"%d\",\"bDual\":\"%d\",\"bSpeaker\":\"%d\",\"bQuiet\":\"%d\",\"bMute\":\"%d\",\"bSelview\":\"%d\"}"
				, tUMCMtInfo.m_wEpID, tUMCMtInfo.m_achRoomName, tUMCMtInfo.m_achRoomE164, strIp.c_str(), tUMCMtInfo.m_bOnline, bDual
				, bSpeaker, tUMCMtInfo.m_bQuiet, tUMCMtInfo.m_bMute, bSelview );
			
			vecStrJson.push_back(chItem);
		}
		
		strJson = COwsCommon::CreateStringJson( strJsonHead, vecStrJson );
	}
	
	PTR_FCGIPRINTF( strJson.c_str() );
	PrtMsg( ev_umcweb_list_meetingroom_get_res, emEventTypeClientSend, "strJson:%s", strJson.c_str() );
	
	return NO_ERROR;
}

u16 CUmcConfinfoCtrl::OnUmcwebHangupconfReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strConfID = COwsCommon::GetPropertyTreeVar( pt, "confid" );
	
	PrtMsg( ev_umcweb_hangupconf_req, emEventTypeClientRecv, "confid:%s", strConfID.c_str() );

	u16 nConfID = atoi(strConfID.c_str());
	
	CTpMsg *pMsg = PTR_MSGDRIVER->GetKdvMsgPtr();
	pMsg->SetEvent( evtp_HungUpConf_cmd );
	pMsg->SetBody(&nConfID,sizeof(u16));
	
	
    PrtMsg( evtp_HungUpConf_cmd, emEventTypeServerSend, "confid:%d", nConfID );

	PTR_MSGDRIVER->PostCommand(this, evtp_HungUpConf_result, TYPE_TPMSG);
	
	return NO_ERROR;
}

u16 CUmcConfinfoCtrl::OnUmcEpoperStartdualReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strConfID = COwsCommon::GetPropertyTreeVar( pt, "confid" );
	std::string strEpID = COwsCommon::GetPropertyTreeVar( pt, "epid" );
	
	PrtMsg( ev_umcweb_epoper_startdual_req, emEventTypeClientRecv, "confid:%s, epid:%s", strConfID.c_str(), strEpID.c_str() );
	
	u16 nConfID = atoi(strConfID.c_str());
	u16 nEpID = atoi(strEpID.c_str());

	TConfEpID tConfEpID;
	tConfEpID.m_wConfID = nConfID;
	tConfEpID.m_wEpID = nEpID;
	
	CTpMsg *pMsg = PTR_MSGDRIVER->GetKdvMsgPtr();
	pMsg->SetEvent( evtp_StartDual_Cmd );
	pMsg->SetBody(&tConfEpID,sizeof(TConfEpID));
	
	
    PrtMsg( evtp_StartDual_Cmd, emEventTypeServerSend, "confid:%d, epid:%d", nConfID, nEpID );
	
	PTR_MSGDRIVER->PostCommand(this, evtp_StartDual_Ind, TYPE_TPMSG);
	
	return NO_ERROR;
}

u16 CUmcConfinfoCtrl::OnUmcEpoperStopdualReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strConfID = COwsCommon::GetPropertyTreeVar( pt, "confid" );
	std::string strEpID = COwsCommon::GetPropertyTreeVar( pt, "epid" );
	
	PrtMsg( ev_umcweb_epoper_stopdual_req, emEventTypeClientRecv, "confid:%s, epid:%s", strConfID.c_str(), strEpID.c_str() );
	
	u16 nConfID = atoi(strConfID.c_str());
	u16 nEpID = atoi(strEpID.c_str());
	
	TConfEpID tConfEpID;
	tConfEpID.m_wConfID = nConfID;
	tConfEpID.m_wEpID = nEpID;
	
	CTpMsg *pMsg = PTR_MSGDRIVER->GetKdvMsgPtr();
	pMsg->SetEvent( evtp_StopDual_Cmd );
	pMsg->SetBody(&tConfEpID,sizeof(TConfEpID));
	
	
    PrtMsg( evtp_StopDual_Cmd, emEventTypeServerSend, "confid:%d, epid:%d", nConfID, nEpID );
	
	PTR_MSGDRIVER->PostCommand(this, evtp_StopDual_Ind, TYPE_TPMSG);
	
	return NO_ERROR;
}

u16 CUmcConfinfoCtrl::OnUmcEpoperApplyspeakerReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strConfID = COwsCommon::GetPropertyTreeVar( pt, "confid" );
	std::string strEpID = COwsCommon::GetPropertyTreeVar( pt, "epid" );
	
	PrtMsg( ev_umcweb_epoper_applyspeaker_req, emEventTypeClientRecv, "confid:%s, epid:%s", strConfID.c_str(), strEpID.c_str() );
	
	u16 nConfID = atoi(strConfID.c_str());
	u16 nEpID = atoi(strEpID.c_str());
	
	TConfEpID tConfEpID;
	tConfEpID.m_wConfID = nConfID;
	tConfEpID.m_wEpID = nEpID;
	
	CTpMsg *pMsg = PTR_MSGDRIVER->GetKdvMsgPtr();
	pMsg->SetEvent( evtp_ApplySpeaker_cmd );
	pMsg->SetBody(&tConfEpID,sizeof(TConfEpID));
	
	
    PrtMsg( evtp_ApplySpeaker_cmd, emEventTypeServerSend, "confid:%d, epid:%d", nConfID, nEpID );
	
	PTR_MSGDRIVER->PostCommand(this, evtp_ApplySpeaker_result, TYPE_TPMSG);
	
	return NO_ERROR;
}

u16 CUmcConfinfoCtrl::OnUmcEpoperQuietReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strConfID = COwsCommon::GetPropertyTreeVar( pt, "confid" );
	std::string strEpID = COwsCommon::GetPropertyTreeVar( pt, "epid" );
	std::string strbQuiet = COwsCommon::GetPropertyTreeVar( pt, "bquiet" );
	
	PrtMsg( ev_umcweb_epoper_quiet_req, emEventTypeClientRecv, "confid:%s, epid:%s, bquiet:%s", strConfID.c_str(), strEpID.c_str(), strbQuiet.c_str() );
	
	u16 nConfID = atoi(strConfID.c_str());
	u16 nEpID = atoi(strEpID.c_str());
	BOOL32 bQuiet = (BOOL32)(atoi(strbQuiet.c_str()));
	
	TConfEpID tConfEpID;
	tConfEpID.m_wConfID = nConfID;
	tConfEpID.m_wEpID = nEpID;
	
	CTpMsg *pMsg = PTR_MSGDRIVER->GetKdvMsgPtr();
    pMsg->SetEvent( evtp_QuietEp_cmd );
    pMsg->SetBody( &tConfEpID,sizeof(TConfEpID) );
    pMsg->CatBody(&bQuiet,sizeof(BOOL32));
	
    PrtMsg( evtp_QuietEp_cmd, emEventTypeServerSend, "confid:%d, epid:%d, bquiet:%d", nConfID, nEpID, bQuiet );
	
	PTR_MSGDRIVER->PostCommand(this, evtp_QuietEp_Ind, TYPE_TPMSG);
	
	return NO_ERROR;
}

u16 CUmcConfinfoCtrl::OnUmcEpoperMuteReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strConfID = COwsCommon::GetPropertyTreeVar( pt, "confid" );
	std::string strEpID = COwsCommon::GetPropertyTreeVar( pt, "epid" );
	std::string strbMute = COwsCommon::GetPropertyTreeVar( pt, "bmute" );
	
	PrtMsg( ev_umcweb_epoper_mute_req, emEventTypeClientRecv, "confid:%s, epid:%s, bmute:%s", strConfID.c_str(), strEpID.c_str(), strbMute.c_str() );
	
	u16 nConfID = atoi(strConfID.c_str());
	u16 nEpID = atoi(strEpID.c_str());
	BOOL32 bMute = (BOOL32)(atoi(strbMute.c_str()));
	
	TConfEpID tConfEpID;
	tConfEpID.m_wConfID = nConfID;
	tConfEpID.m_wEpID = nEpID;
	
	CTpMsg *pMsg = PTR_MSGDRIVER->GetKdvMsgPtr();
    pMsg->SetEvent( evtp_MuteEp_cmd );
    pMsg->SetBody( &tConfEpID,sizeof(TConfEpID) );
    pMsg->CatBody(&bMute,sizeof(BOOL32));
	
    PrtMsg( evtp_MuteEp_cmd, emEventTypeServerSend, "confid:%d, epid:%d, bMute:%d", nConfID, nEpID, bMute );
	
	PTR_MSGDRIVER->PostCommand(this, evtp_MuteEp_Ind, TYPE_TPMSG);
	
	return NO_ERROR;
}

u16 CUmcConfinfoCtrl::OnUmcEpoperDropReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strConfID = COwsCommon::GetPropertyTreeVar( pt, "confid" );
	std::string strEpID = COwsCommon::GetPropertyTreeVar( pt, "epid" );
	
	PrtMsg( ev_umcweb_epoper_drop_req, emEventTypeClientRecv, "confid:%s, epid:%s", strConfID.c_str(), strEpID.c_str() );
	
	u16 nConfID = atoi(strConfID.c_str());
	u16 nEpID = atoi(strEpID.c_str());
	
	TConfEpID tConfEpID;
	tConfEpID.m_wConfID = nConfID;
	tConfEpID.m_wEpID = nEpID;
	
	CTpMsg *pMsg = PTR_MSGDRIVER->GetKdvMsgPtr();
    pMsg->SetEvent( evtp_DropEp_cmd );
    pMsg->SetBody( &tConfEpID,sizeof(TConfEpID) );
	
    PrtMsg( evtp_DropEp_cmd, emEventTypeServerSend, "confid:%d, epid:%d", nConfID, nEpID );
	
	PTR_MSGDRIVER->PostCommand(this, evtp_DropEp_Ind, TYPE_TPMSG);
	
	return NO_ERROR;
}

u16 CUmcConfinfoCtrl::OnUmcEpoperCallReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strConfID = COwsCommon::GetPropertyTreeVar( pt, "confid" );
	std::string strEpID = COwsCommon::GetPropertyTreeVar( pt, "epid" );
	
	PrtMsg( ev_umcweb_epoper_call_req, emEventTypeClientRecv, "confid:%s, epid:%s", strConfID.c_str(), strEpID.c_str() );
	
	u16 nConfID = atoi(strConfID.c_str());
	u16 nEpID = atoi(strEpID.c_str());
	
	TConfEpID tConfEpID;
	tConfEpID.m_wConfID = nConfID;
	tConfEpID.m_wEpID = nEpID;
	
	CTpMsg *pMsg = PTR_MSGDRIVER->GetKdvMsgPtr();
    pMsg->SetEvent( evtp_CallExistEP_cmd );
    pMsg->SetBody( &tConfEpID,sizeof(TConfEpID) );
	
    PrtMsg( evtp_CallExistEP_cmd, emEventTypeServerSend, "confid:%d, epid:%d", nConfID, nEpID );
	
	PTR_MSGDRIVER->PostCommand(this, evtp_CallExistEP_result, TYPE_TPMSG);
	
	return NO_ERROR;
}

u16 CUmcConfinfoCtrl::OnUmcEpoperSelviewReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strConfID = COwsCommon::GetPropertyTreeVar( pt, "confid" );
	std::string strEpID = COwsCommon::GetPropertyTreeVar( pt, "epid" );
	std::string strScreenIndex = COwsCommon::GetPropertyTreeVar( pt, "screenIndex" );
	std::string strSel = COwsCommon::GetPropertyTreeVar( pt, "bSel" );
	std::string strType = COwsCommon::GetPropertyTreeVar( pt, "emType" );
	std::string strDstEpID = COwsCommon::GetPropertyTreeVar( pt, "dstEpID" );
	
	PrtMsg( ev_umcweb_epoper_selview_req, emEventTypeClientRecv, "confid:%s, epid:%s, screenIndex:%s, bSel:%s, emType:%s, dstEpID:%s"
		, strConfID.c_str(), strEpID.c_str(), strScreenIndex.c_str(), strSel.c_str(), strType.c_str(), strDstEpID.c_str() );
	
	u16 nConfID = atoi(strConfID.c_str());
	u16 nEpID = atoi(strEpID.c_str());
	u16 nScreenIndex = atoi(strScreenIndex.c_str());
	BOOL32 bSel = atoi(strSel.c_str());
	EmViewEpType emType = (EmViewEpType)(atoi(strType.c_str()));
	u16 nDstEpID = atoi(strDstEpID.c_str());
	
	TTPSelViewReq tTPSelViewReq;
	tTPSelViewReq.m_emUIType = EmUI_UMC;
	tTPSelViewReq.m_bSel = bSel;
	tTPSelViewReq.m_wConfID = nConfID;
	tTPSelViewReq.m_wEpID = nEpID;
	tTPSelViewReq.m_wScreenIndx = nScreenIndex;
	tTPSelViewReq.m_emType = emType;
	tTPSelViewReq.m_wDstID = nDstEpID;

	
	CTpMsg *pMsg = PTR_MSGDRIVER->GetKdvMsgPtr();
    pMsg->SetEvent( ev_UMC_UMS_SelView_Req );
    pMsg->SetBody( &tTPSelViewReq,sizeof(TTPSelViewReq) );
	
    PrtMsg( ev_UMC_UMS_SelView_Req, emEventTypeServerSend, "confid:%d, epid:%d, screenIndex:%d, bSel:%d, emType:%d, dstEpID:%d"
		, nConfID, nEpID, nScreenIndex, bSel, emType, nDstEpID );
	
	PTR_MSGDRIVER->PostCommand(this, ev_UMS_UMC_SelView_Ind, TYPE_TPMSG);
	
	return NO_ERROR;
}

u16 CUmcConfinfoCtrl::OnUmcSelviewInfoGetReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strConfID = COwsCommon::GetPropertyTreeVar( pt, "confid" );
	std::string strEpID = COwsCommon::GetPropertyTreeVar( pt, "epid" );
	
	PrtMsg( ev_umcweb_selviewinfo_get_req, emEventTypeClientRecv, "confid:%s, epid:%s", strConfID.c_str(), strEpID.c_str() );
	
	u16 nConfID = atoi(strConfID.c_str());
	u16 nEpID = atoi(strEpID.c_str());
	
	std::string strJson;
	
	TConfinfo* pTConfinfo = GetConfInfoByID(nConfID);
	if ( pTConfinfo == NULL )
	{
		strJson = "{\"event\":\"ev_umcweb_selviewinfo_get_res\",\"count\":\"0\"},\"error\":\"no_conf\"}";
	}
	else
	{
		TUMCMtInfo* pTUMCMtInfo = pTConfinfo->GetCnsInfoByID(nEpID);
		if ( pTUMCMtInfo == NULL )
		{
			strJson = "{\"event\":\"ev_umcweb_selviewinfo_get_res\",\"count\":\"0\"},\"error\":\"no_mt\"}";
		}
		else
		{
			string strJsonHead = "{\"event\":\"ev_umcweb_selviewinfo_get_res\",\"items\":";
			
			vector<string> vecStrJson;
			
			for ( int i = 0; i < pTUMCMtInfo->m_wSpeakerNum; i++ )
			{
				TUMCSelViewInfo tUMCSelViewInfo = pTUMCMtInfo->m_tUMCSelViewInfo[i];
				if ( tUMCSelViewInfo.m_wID == TP_INVALID_INDEX )
				{
					break;
				}

				string strSelName;
				if ( tUMCSelViewInfo.m_emType == EmEpType_Ter )
				{
					//画面合成
				}
				else if ( tUMCSelViewInfo.m_emType == EmEpType_Eqp )
				{
					strSelName = pTConfinfo->GetMTNameByID(tUMCSelViewInfo.m_wID);
				}

				char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
				sprintf( chItem, "{\"selId\":\"%d\",\"selType\":\"%d\",\"selName\":\"%s\"}"
					, tUMCSelViewInfo.m_wID, tUMCSelViewInfo.m_emType, strSelName.c_str() );
				
				vecStrJson.push_back(chItem);
			}
			
			strJson = COwsCommon::CreateStringJson( strJsonHead, vecStrJson );
		}
	}
	
	PTR_FCGIPRINTF( strJson.c_str() );
	PrtMsg( ev_umcweb_selviewinfo_get_res, emEventTypeClientSend, "strJson:%s", strJson.c_str() );
	
	return NO_ERROR;
}

u16 CUmcConfinfoCtrl::OnUmcwebRefreshConfinfoInfoNtyReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strConfID = COwsCommon::GetPropertyTreeVar( pt, "wCurConfID" );
	
	PrtMsg( ev_umcweb_RefreshConfinfoInfo_nty_req, emEventTypeClientRecv, "wCurConfID= %s", strConfID.c_str() );

	u16 wConfID = atoi( strConfID.c_str() );
	TConfinfo* pTConfinfo = GetConfInfoByID( wConfID );
	if ( NULL == pTConfinfo )
	{
		PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_RefreshConfinfoInfo_nty_res\",\"wConfTempID\":\"%s\"}", "");
		return NO_ERROR;
	}

	std::string strJsonHead = "{\"event\":\"ev_umcweb_RefreshConfinfoInfo_nty_res\",";

	std::string strTime;
	CUmcwebCommon::ChangeTimeToString( pTConfinfo->m_tStartTime, strTime );

	u16 wResNum = CComInterface::GetNeedBasNum(*pTConfinfo);
	u16 wResUsedCount = PTR_SESSION->GetUmcConfTemplateCtrl()->GetResUsedCount();

	char chConfInfo[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chConfInfo, "\"wConfTempID\":\"%d\",\"achConfName\":\"%s\",\"achConfNum\":\"%s\",\"achStartTime\":\"%s\",\"nSingleRate\":\"%d\",\"nShowRate\":\"%d\",\"nUpBandWidth\":\"%d\",\"nDownBandWidth\":\"%d\",\"emEncryptModel\":\"%d\",\"achEncrypt\":\"%s\",\"nPollingTime\":\"%d\",\"wResNum\":\"%d\",\"wResUsedCount\":\"%d\",",
		pTConfinfo->m_wConfID, pTConfinfo->m_achConfName, pTConfinfo->m_achConfE164, strTime.c_str(), pTConfinfo->m_wConfBitRate, pTConfinfo->m_wHpDualBitRate, pTConfinfo->m_wUpBandWid,
		pTConfinfo->m_wDownBandWid, pTConfinfo->m_tEncrypt.m_emEncryptModel, pTConfinfo->m_tEncrypt.m_achEncKey, pTConfinfo->m_wInterval,
		wResNum, wResUsedCount );

	strJsonHead += chConfInfo;

	int wIndex = 0;
	char chFormatName[50] = {0};

	//主视频格式
	std::string strMainVideoRes = "\"atTpMainVideoRes\":[";
	for ( wIndex = 0; wIndex < pTConfinfo->m_wMainNum; wIndex++ )
	{
		std::string strMainFormat;
		CUmcwebCommon::ChangeMainVideoToName( pTConfinfo->m_atTpMainVideoRes[wIndex], strMainFormat );

		memset( chFormatName, 0, sizeof(chFormatName) );
		sprintf( chFormatName, "{\"chFormatName\":\"%s\"},", strMainFormat.c_str() );

		strMainVideoRes += chFormatName;
	}

	strMainVideoRes = strMainVideoRes.substr( 0, strMainVideoRes.length() - 1 );
	strMainVideoRes += "]";

	char chMainVideoNum[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chMainVideoNum, ",\"wMainNum\":\"%d\"", pTConfinfo->m_wMainNum );

	strMainVideoRes += chMainVideoNum;

	//辅视频格式
	std::string strMinorVideoRes = "\"atTpMinorVideoRes\":[";
	for ( wIndex = 0; wIndex < pTConfinfo->m_wMinorNum; wIndex++ )
	{
		std::string strMinorFormat;
		CUmcwebCommon::ChangeMinorVideoToName( pTConfinfo->m_atTpMinorVideoRes[wIndex], strMinorFormat );

		memset( chFormatName, 0, sizeof(chFormatName) );
		sprintf( chFormatName, "{\"chFormatName\":\"%s\"},", strMinorFormat.c_str() );

		strMinorVideoRes += chFormatName;
	}

	strMinorVideoRes = strMinorVideoRes.substr( 0, strMinorVideoRes.length() - 1 );
	strMinorVideoRes += "]";

	char chMinorVideoNum[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chMinorVideoNum, ",\"wMinorNum\":\"%d\"", pTConfinfo->m_wMinorNum );

	strMinorVideoRes += chMinorVideoNum;

	//音频格式
	std::string strAudFmt = "\"atAudFmt\":[";
	for ( wIndex = 0; wIndex < pTConfinfo->m_wAudFmtNum; wIndex++ )
	{
		std::string strAudioFormat;
		CUmcwebCommon::ChangeAudioFormatToName( pTConfinfo->m_atAudFmt[wIndex].m_emFormat, strAudioFormat );
		
		memset( chFormatName, 0, sizeof(chFormatName) );
		sprintf( chFormatName, "{\"chFormatName\":\"%s\"},", strAudioFormat.c_str() );
		
		strAudFmt += chFormatName;
	}
	
	strAudFmt = strAudFmt.substr( 0, strAudFmt.length() - 1 );
	strAudFmt += "]";
	
	char chAudioFormatNum[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chAudioFormatNum, ",\"wAudFmtNum\":\"%d\"", pTConfinfo->m_wAudFmtNum );
	
	strAudFmt += chAudioFormatNum;

	//拼接json字符串
	string strJson;
	strJson = strJsonHead + strMainVideoRes + "," + strMinorVideoRes + strAudFmt + "}";

	PrtMsg( ev_umcweb_RefreshConfinfoInfo_nty_res, emEventTypeClientSend, "strJson:%s", strJson.c_str() );
	PTR_FCGIPRINTF( strJson.c_str() );
	
	return NO_ERROR;
}

u16 CUmcConfinfoCtrl::OnUmcwebRefreshConfinfoPollingListNtyReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strConfID = COwsCommon::GetPropertyTreeVar( pt, "wCurConfID" );
	
	PrtMsg( ev_umcweb_RefreshConfinfo_PollingList_nty_req, emEventTypeClientRecv, "wCurConfID= %s", strConfID.c_str() );

	u16 wRe = UmcwebRefreshConfinfoPollingList( atoi( strConfID.c_str() ) );
	return wRe;
}

u16 CUmcConfinfoCtrl::OnUmcwebRefreshConfinfoDiscussListNtyReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strConfID = COwsCommon::GetPropertyTreeVar( pt, "wCurConfID" );
	
	PrtMsg( ev_umcweb_RefreshConfinfo_DiscussList_nty_req, emEventTypeClientRecv, "wCurConfID= %s", strConfID.c_str() );
	
	u16 wRe = UmcwebRefreshConfinfoDiscussList( atoi( strConfID.c_str() ) );	
	return wRe;
}

u16 CUmcConfinfoCtrl::OnUmcwebSuspendTurnReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strConfID = COwsCommon::GetPropertyTreeVar( pt, "wCurConfID" );
	std::string strSuspend = COwsCommon::GetPropertyTreeVar( pt, "bSuspend" );
	
	PrtMsg( ev_umcweb_SuspendTurn_req, emEventTypeClientRecv, "wCurConfID= %s, bSuspend= %s", strConfID.c_str(), strSuspend.c_str() );
	
	BOOL32 bSuspend = TRUE;
	if ( strcmp( "0", strSuspend.c_str() ) == 0 )
	{
		bSuspend = FALSE;
	}

	u16 wRe = SuspendTurnReq( atoi(strConfID.c_str()), bSuspend );
	return wRe;
}

u16 CUmcConfinfoCtrl::OnUmcwebStartTurnReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strConfID = COwsCommon::GetPropertyTreeVar( pt, "wCurConfID" );
	std::string strStart = COwsCommon::GetPropertyTreeVar( pt, "bStart" );
	
	PrtMsg( ev_umcweb_StartTurn_req, emEventTypeClientRecv, "wCurConfID= %s, bStart= %s", strConfID.c_str(), strStart.c_str() );
	
	u16 wRe = NO_ERROR;
	if ( strcmp( "0", strStart.c_str() ) == 0 )
	{
		wRe = StopTurnReq( atoi(strConfID.c_str()) );
	}
	else
	{
		wRe = StartTurnReq( atoi(strConfID.c_str()) );
	}

	return wRe;
}

u16 CUmcConfinfoCtrl::OnUmcwebUpdateTurnReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strConfID = COwsCommon::GetPropertyTreeVar( pt, "wCurConfID" );
	std::string strInterval = COwsCommon::GetPropertyTreeVar( pt, "wInterval" );
	std::string strPollingCount = COwsCommon::GetPropertyTreeVar( pt, "wPollingCount" );

	PrtMsg( ev_umcweb_UpdateTurn_req, emEventTypeClientRecv, "wCurConfID= %s, wInterval= %s, wPollingCount= %s",
		strConfID.c_str(), strInterval.c_str(), strPollingCount.c_str() );

	TConfTurnInfo tConfTurnInfo;
	tConfTurnInfo.m_wConfID = atoi( strConfID.c_str() );
	tConfTurnInfo.m_atTurnList.SetInterval( atoi(strPollingCount.c_str()) );
	tConfTurnInfo.m_atTurnList.m_bPollOn = TRUE;

	u16 wPollingCount = atoi( strPollingCount.c_str() );
	tConfTurnInfo.m_atTurnList.m_wNum = wPollingCount;

	//先发个空的 m_awList
	//UpdateTurnReq( tConfTurnInfo );
	
	u16 wCurNum = 0;
	vector<ptree> vecPtePollingList = COwsCommon::GetPropertyTreeChildren( pt, "arrPolling" );
	for ( u16 wIndex = 0; wIndex < wPollingCount; wIndex++ )
	{
		if ( wCurNum >= TP_CONF_MAX_TURNNUM )
		{
			UpdateTurnReq( tConfTurnInfo );

			for ( u16 i = 0; i < TP_CONF_MAX_TURNNUM; i++ )
			{
				tConfTurnInfo.m_atTurnList.m_awList[i] = TP_INVALID_INDEX;
			}

			wCurNum = 0;
		}

		std::string strEpId = COwsCommon::GetPropertyTreeVar( vecPtePollingList[wIndex], "epId" );
		u16 wPollingId = atoi( strEpId.c_str() );
		tConfTurnInfo.m_atTurnList.m_awList[wCurNum] = wPollingId;
		++wCurNum;
		
		//test:
		std::string strMeetName = COwsCommon::GetPropertyTreeVar( vecPtePollingList[wIndex], "achMeetName" );
		std::string strMeetNum = COwsCommon::GetPropertyTreeVar( vecPtePollingList[wIndex], "achE164" );
		std::string strMeetIp = COwsCommon::GetPropertyTreeVar( vecPtePollingList[wIndex], "achMeetIp" );
		PrtMsg( "confctrl pollinglist: wPollingId = %d, strMeetName = %s, strMeetNum = %s, strMeetIp = %s\n",
			wPollingId, strMeetName.c_str(), strMeetNum.c_str(), strMeetIp.c_str() );
	}

	return NO_ERROR;
}

u16 CUmcConfinfoCtrl::OnUmcwebAuxMixVacSwitchReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strConfID = COwsCommon::GetPropertyTreeVar( pt, "wCurConfID" );
	std::string strVacOn = COwsCommon::GetPropertyTreeVar( pt, "bVacOn" );
	
	PrtMsg( ev_umcweb_AuxMixVacSwitch_req, emEventTypeClientRecv, "wCurConfID= %s, bVacOn= %s", strConfID.c_str(), strVacOn.c_str() );
	
	TConfAuxMixVacOpr tConfAuxMixVacOpr;
	tConfAuxMixVacOpr.m_wConfID = atoi( strConfID.c_str() );
	tConfAuxMixVacOpr.m_bVacOn = FALSE;
	if ( strcmp( "1", strVacOn.c_str() ) == 0 )
	{
		tConfAuxMixVacOpr.m_bVacOn = TRUE;
	}

	u16 wRe = AuxMixVacSwitchReq( tConfAuxMixVacOpr );	
	return wRe;
}

u16 CUmcConfinfoCtrl::OnUmcwebUpdateAudMixInfoReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strConfID = COwsCommon::GetPropertyTreeVar( pt, "wCurConfID" );
	std::string strOprType = COwsCommon::GetPropertyTreeVar( pt, "emOprType" );
	std::string strDiscussCount = COwsCommon::GetPropertyTreeVar( pt, "wDiscussCount" );
	
	PrtMsg( ev_umcweb_UpdateAudMixInfo_req, emEventTypeClientRecv, "wCurConfID= %s, wNum= %s, emOprType= %s(0:em_DisListOpr_Add; 1:em_DisListOpr_Del)",
		strConfID.c_str(), strDiscussCount.c_str(), strOprType.c_str() );

	TDiscussListOpr tDiscussListOpr;
	tDiscussListOpr.m_wConfId = atoi( strConfID.c_str() );
	tDiscussListOpr.m_emOprType = (EmDisListOprType)( atoi(strOprType.c_str()) );

	u16 wDiscussCount = atoi( strDiscussCount.c_str() );
	tDiscussListOpr.m_wNum = wDiscussCount;
	
	vector<ptree> vecPteDiscussList = COwsCommon::GetPropertyTreeChildren( pt, "arrDiscuss" );
	for ( u16 wIndex = 0; wIndex < wDiscussCount; wIndex++ )
	{		
		std::string strEpId = COwsCommon::GetPropertyTreeVar( vecPteDiscussList[wIndex], "epId" );
		u16 wDiscussId = atoi( strEpId.c_str() );
		tDiscussListOpr.m_awEpId[wIndex] = wDiscussId;
		
		//test:
		PrtMsg( "confctrl discusslist: wDiscussId = %d\n", wDiscussId );
	}

	u16 wRet = UpdateAudMixInfoReq( tDiscussListOpr );
	return wRet;
}

u16 CUmcConfinfoCtrl::OnUmcwebStartAuxMixReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strConfID = COwsCommon::GetPropertyTreeVar( pt, "wCurConfID" );
	std::string strStart = COwsCommon::GetPropertyTreeVar( pt, "bStart" );
	std::string strVacOn = COwsCommon::GetPropertyTreeVar( pt, "bVacOn" );
	std::string strSpeakerIndex = COwsCommon::GetPropertyTreeVar( pt, "wSpeakerIndex" );
	std::string strDiscussCount = COwsCommon::GetPropertyTreeVar( pt, "wDiscussCount" );
	
	PrtMsg( ev_umcweb_StartAuxMix_req, emEventTypeClientRecv, "wCurConfID= %s, bStart= %s, bVacOn= %s, wSpeakerIndex= %s",
		strConfID.c_str(), strStart.c_str(), strVacOn.c_str(), strSpeakerIndex.c_str() );

	TConfAuxMixInfo tConfAuxMixInfo;
	tConfAuxMixInfo.m_wConfID = atoi( strConfID.c_str() );
	tConfAuxMixInfo.m_bStart = (BOOL32)( atoi(strStart.c_str()) );
	tConfAuxMixInfo.m_bVacOn = (BOOL32)( atoi(strVacOn.c_str()) );
	tConfAuxMixInfo.m_atAuxMixList.SetSpeakerIndex( atoi(strSpeakerIndex.c_str()) );
	
	u16 wDiscussCount = atoi( strDiscussCount.c_str() );

	vector<ptree> vecPteDiscussList = COwsCommon::GetPropertyTreeChildren( pt, "arrDiscuss" );
	for ( u16 wIndex = 0; wIndex < wDiscussCount; wIndex++ )
	{		
		std::string strEpId = COwsCommon::GetPropertyTreeVar( vecPteDiscussList[wIndex], "epId" );
		u16 wDiscussId = atoi( strEpId.c_str() );
		tConfAuxMixInfo.m_atAuxMixList.m_awList[wIndex] = wDiscussId;
		
		//test:
		std::string strMeetName = COwsCommon::GetPropertyTreeVar( vecPteDiscussList[wIndex], "achMeetName" );
		std::string strMeetNum = COwsCommon::GetPropertyTreeVar( vecPteDiscussList[wIndex], "achE164" );
		std::string strMeetIp = COwsCommon::GetPropertyTreeVar( vecPteDiscussList[wIndex], "achMeetIp" );
		PrtMsg( "confctrl discusslist: wDiscussId = %d, strMeetName = %s, strMeetNum = %s, strMeetIp = %s\n",
			wDiscussId, strMeetName.c_str(), strMeetNum.c_str(), strMeetIp.c_str() );
	}

	u16 wRet = StartAuxMixReq( tConfAuxMixInfo );
	return wRet;
}

u16 CUmcConfinfoCtrl::UmcwebRefreshConfinfoPollingList(const u16 wConfID)
{
	TConfinfo* pTConfinfo = GetConfInfoByID( wConfID );
	if ( NULL == pTConfinfo )
	{
		PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_RefreshConfinfo_PollingList_nty_res\",\"count\":\"0\"}" );
		return NO_ERROR;
	}
	
	std::string strJsonHead = "{\"event\":\"ev_umcweb_RefreshConfinfo_PollingList_nty_res\",";
	std::vector<std::string> vecStrJson;
	
	char chPollingInfo[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chPollingInfo, "\"emStat\":\"%d\",\"wInterval\":\"%d\",\"items\":",
		pTConfinfo->m_emStat, pTConfinfo->m_wInterval );
	
	strJsonHead += chPollingInfo;
	
	vector<u16>::iterator iter = pTConfinfo->m_vecPollList.begin();
	for ( ; iter != pTConfinfo->m_vecPollList.end(); iter++ )
	{
		u16 wPollingId = *iter;
		PrtMsg( "wPollingId = %d\n", wPollingId );
		
		TUMCMtInfo* ptUMCMtInfo = pTConfinfo->GetCnsInfoByID( wPollingId );
		if ( NULL == ptUMCMtInfo )
		{
			continue;
		}
		
		in_addr tAddr;
		tAddr.s_addr = htonl( ptUMCMtInfo->m_dwRoomIp );
		
		PrtMsg( "wPollingId = %d, name = %s, num = %s, ip = %s, bOnline = %d\n",
			wPollingId, ptUMCMtInfo->m_achRoomName, ptUMCMtInfo->m_achRoomE164, inet_ntoa(tAddr), ptUMCMtInfo->m_bOnline );
		
		char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
		sprintf( chItem, "{\"epId\":\"%d\",\"achMeetName\":\"%s\",\"achE164\":\"%s\",\"achMeetIp\":\"%s\",\"bOnline\":\"%d\"}",
			wPollingId, ptUMCMtInfo->m_achRoomName, ptUMCMtInfo->m_achRoomE164, inet_ntoa(tAddr), ptUMCMtInfo->m_bOnline );	
		vecStrJson.push_back(chItem);
	}
	
	std::string strJson = COwsCommon::CreateStringJson( strJsonHead, vecStrJson );
	
	PTR_FCGIPRINTF( strJson.c_str() );
	PrtMsg( ev_umcweb_RefreshConfinfo_PollingList_nty_res, emEventTypeClientSend, "strJson: %s", strJson.c_str() );

	return NO_ERROR;
}

u16 CUmcConfinfoCtrl::UmcwebRefreshConfinfoDiscussList(const u16 wConfID)
{
	TConfinfo* pTConfinfo = GetConfInfoByID( wConfID );
	if ( NULL == pTConfinfo )
	{
		PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_RefreshConfinfo_DiscussList_nty_res\",\"count\":\"0\"}" );
		return NO_ERROR;
	}
	
	std::string strJsonHead = "{\"event\":\"ev_umcweb_RefreshConfinfo_DiscussList_nty_res\",";
	std::vector<std::string> vecStrJson;
	
	char chDiscussInfo[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chDiscussInfo, "\"bDiscussOn\":\"%d\",\"bVacOn\":\"%d\",\"wSpeakerIndex\":\"%d\",\"items\":",
		pTConfinfo->m_tConfAuxMixInfo.m_bStart, pTConfinfo->m_tConfAuxMixInfo.m_bVacOn, pTConfinfo->m_tConfAuxMixInfo.m_atAuxMixList.m_wSpeakerIndex );
	
	strJsonHead += chDiscussInfo;
	
	for ( u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++ )
	{
		u16 wDiscussId = pTConfinfo->m_tConfAuxMixInfo.m_atAuxMixList.m_awList[wIndex];
		PrtMsg( "wDiscussId = %d\n", wDiscussId );
		
		TUMCMtInfo* ptUMCMtInfo = pTConfinfo->GetCnsInfoByID( wDiscussId );
		if ( NULL == ptUMCMtInfo )
		{
			continue;
		}
		
		in_addr tAddr;
		tAddr.s_addr = htonl( ptUMCMtInfo->m_dwRoomIp );
		
		PrtMsg( "wDiscussId = %d, name = %s, num = %s, ip = %s, bOnline = %d\n",
			wDiscussId, ptUMCMtInfo->m_achRoomName, ptUMCMtInfo->m_achRoomE164, inet_ntoa(tAddr), ptUMCMtInfo->m_bOnline );
		
		char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
		sprintf( chItem, "{\"epId\":\"%d\",\"achMeetName\":\"%s\",\"achE164\":\"%s\",\"achMeetIp\":\"%s\,\"bOnline\":\"%d\"}",
			wDiscussId, ptUMCMtInfo->m_achRoomName, ptUMCMtInfo->m_achRoomE164, inet_ntoa(tAddr), ptUMCMtInfo->m_bOnline );	
		vecStrJson.push_back(chItem);
	}
	
	std::string strJson = COwsCommon::CreateStringJson( strJsonHead, vecStrJson );
	
	PTR_FCGIPRINTF( strJson.c_str() );
	PrtMsg( ev_umcweb_RefreshConfinfo_DiscussList_nty_res, emEventTypeClientSend, "strJson: %s", strJson.c_str() );

	return NO_ERROR;
}