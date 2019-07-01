// cncconfctrl.cpp: implementation of the CCncConfCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cncconfctrl.h"
#include "tptype.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCncConfCtrl::CCncConfCtrl(CCnsSession &cSession) : CCncConfCtrlIF(), 
                                                    m_bRecvDual(FALSE),
                                                    m_nVideoNode(TP_INVALID_INDEX),
                                                    m_nAudioNode(TP_INVALID_INDEX)
{
	m_pSession = &cSession;
	m_bMute = FALSE;
	m_bQuite = FALSE;
	m_byInputVol = 0;
	m_byOutputVol = 0;
	m_bySpeakSeat = 0;
    m_bDual = FALSE;
	m_bLocalPIP = FALSE;
	m_bPTPSeatArouse = FALSE;
	m_bInAudMix = FALSE;

	BuildEventsMap();
}

CCncConfCtrl::~CCncConfCtrl()
{
	
}


void CCncConfCtrl::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CCncConfCtrl, cMsg);
}


void CCncConfCtrl::BuildEventsMap()
{
    REG_PFUN( ev_CnConfState_Nty, CCncConfCtrl::OnConfStateNty );
    REG_PFUN( ev_tppQuietInd, CCncConfCtrl::OnQuietInd );
    REG_PFUN( ev_tppMuteInd, CCncConfCtrl::OnMuteInd );
    REG_PFUN( ev_tppInputVolumeInd, CCncConfCtrl::OnInputVolInd );
    REG_PFUN( ev_tppOutputVolumeInd, CCncConfCtrl::OnOutPutVolInd );
    REG_PFUN( ev_CnSetInnerSpeaker_Ind, CCncConfCtrl::OnSetInnerSpeaker );
  //  REG_PFUN( ev_CnYouAreSeeing_Ind, OnScreenDisplayInd );	改用ev_CnPosAllStatus_Nty，2012-3-15 yjj
  //  REG_PFUN( ev_CnActivePos_Nty, OnScreenStateNotify );  改用ev_CnPosAllStatus_Nty，2012-3-15 yjj

    REG_PFUN( ev_CnPosAllStatus_Nty, CCncConfCtrl::OnScreenStateNotify );
   
    REG_PFUN( ev_TppStartDual_Ind, CCncConfCtrl::OnStartDualRsp );
    REG_PFUN( ev_TppStopDual_Ind, CCncConfCtrl::OnStartDualRsp );
    REG_PFUN( ev_TppIsDual_Nty, CCncConfCtrl::OnDualStatusNty );
    
    REG_PFUN( ev_CnStartPoll_Ind, CCncConfCtrl::OnStartPollRsp );
    REG_PFUN( ev_CnStopPoll_Ind,  CCncConfCtrl::OnStartPollRsp );  

	REG_PFUN( ev_TppHangUp_Ind,  CCncConfCtrl::OnHungupNotify );

    REG_PFUN( ev_TppAddDualRcvAddr_Ind, CCncConfCtrl::OnStartDualCdStrmRsp );
    REG_PFUN( ev_TppDelDualRcvAddr_Ind, CCncConfCtrl::OnStopDualCdStrmRsp );

    REG_PFUN( ev_TppIsRcvDual_Nty, CCncConfCtrl::OnRecvDualNty );

//     REG_PFUN( ev_CnSingleView_Ind, CCncConfCtrl::OnSetSelViewRsp );//b4 不用此消息 dyy 2015-5-28 
//     REG_PFUN( ev_CnCancelSingleView_Ind, CCncConfCtrl::OnSetSelViewRsp);  

	REG_PFUN( ev_Cn_SelView_Ind, CCncConfCtrl::OnSetSelViewInd );//nlf确认此消息 ev_UMS_CNC_ByCNS_SelView_Ind由ev_Cn_SelView_Ind转到界面
	REG_PFUN( ev_UMS_CNC_ByCNS_SelView_Ntfy, CCncConfCtrl::OnSetSelViewNty);  

    REG_PFUN( ev_TppSelDualView_Ind, CCncConfCtrl::OnScrnDisplayDualRsp );
    REG_PFUN( ev_TppCancelSelDualView_Ind, CCncConfCtrl::OnStopScrnDisplayDualRsp );

    REG_PFUN( ev_CnViewLocal_Ind, CCncConfCtrl::OnScrnDisplayLocalRsp );
    REG_PFUN( ev_CnCancelViewLocal_Ind, CCncConfCtrl::OnStopDisplayLocalRsp );

	REG_PFUN( ev_tpCnRoomDualOffline_Nty, CCncConfCtrl::OnCnDualOfflineNty );	
    REG_PFUN( ev_TppDualRcvInterrupt_Nty, CCncConfCtrl::OnDualRcvInterruptNty );

	REG_PFUN( ev_CnViewLocalPIP_Ind, CCncConfCtrl::OnViewLocalPIPInd );
	REG_PFUN( ev_CnViewLocalPIP_Nty, CCncConfCtrl::OnViewLocalPIPNty );
	
    REG_PFUN( ev_CnSelTVSView_Ind, CCncConfCtrl::OnSetSelTVSViewRsp );
    REG_PFUN( ev_CnCancelSelTVSView_Ind, CCncConfCtrl::OnSetSelTVSViewRsp);  

    REG_PFUN( OSP_DISCONNECT, CCncConfCtrl::OnLinkBreak ); 

	//空闲状态双流设置
	REG_PFUN( ev_tppSetShowDual_Ind, CCncConfCtrl::OnSpareDualSetInd );
	REG_PFUN( ev_tppSetShowDual_Nty, CCncConfCtrl::OnSpareDualSetNty );	

	//单独控制坐席激励消息回复
	REG_PFUN( ev_CnMixIsUsed_Ind, CCncConfCtrl::OnCnAuxMixInd );	
	//会议点名
	REG_PFUN( evConfRollCallUpdate_Nty, CCncConfCtrl::OnStartRollNty );
	REG_PFUN( evConfRollCallUpdate_Ind, CCncConfCtrl::OnStartRollInd );
	REG_PFUN( evConfRollCallNextEp_Ind, CCncConfCtrl::OnRollNextInd );
	REG_PFUN( evtpRoll_PresentState_Nty, CCncConfCtrl::OnRollAttendNty );
	REG_PFUN( evConfRollCallUpdataList_Ind, CCncConfCtrl::OnRollListFixedInd );

	//会议混音
	REG_PFUN( evtpConfAudMixMode_Nty, CCncConfCtrl::OnConfMixStateNty );
	REG_PFUN( evConfAudMixMode_Ind, CCncConfCtrl::OnStarConfMixInd );
	REG_PFUN( evConfAudMixList_Ind, CCncConfCtrl::OnConfMixFixInd );
	//当前会场是否在会议混音中
	REG_PFUN( ev_EpInAudMix_Nty, CCncConfCtrl::OnEpInAudMixNty );
	//麦克风
	REG_PFUN( ev_CnSetDesktopMicInfo_Nty, CCncConfCtrl::OnCnSetDesktopMicInfoNty);
	REG_PFUN( ev_CnSetDesktopMicInfo_Ind, CCncConfCtrl::OnCnSetDesktopMicInfoInd);
	REG_PFUN( ev_CnMicPowerStyle_Nty, CCncConfCtrl::OnCnMicPowerStyleNty);
	REG_PFUN( ev_CnMicPower_Nty, CCncConfCtrl::OnCnMicPowerNty);
	REG_PFUN( ev_CnSetMicPower_Rsp, CCncConfCtrl::OnCnSetMicPowerRsp);

    REG_PFUN( ev_CnGetTempPwd_Cmd, CCncConfCtrl::OnCnGetTempPwdCmd);
}


void CCncConfCtrl::ClearCnsScreenInfo()
{
	for (int i=0; i<m_vctScreenInfo.size(); i++)
	{
		ZeroMemory( m_vctScreenInfo.at(i).achCnsName, sizeof(m_vctScreenInfo.at(i).achCnsName) );
	}
}


void CCncConfCtrl::OnTimeOut(u16 wEvent)
{
    //PostEvent(MTC_UI_CMD_TIMEOUT, wEvent);
}

 
const u16 CCncConfCtrl::MakeCall( TTPDialParam &tDialParam )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_TppMakeCall_Cmd );
    pcTpMsg->SetBody( &tDialParam, sizeof(TTPDialParam) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TppMakeCall_Cmd, emEventTypeCnsSend, "callingType: %d, tCalledAddr.achAlias: %s, tCalledAddr.achE164: %s, calledType: %d(%d:emTpAlias, %d:emTpE164Num), \
bCreateConf: %d, ConfName: %s, TerNum:%d", 
		tDialParam.tCallingAddr.emType, tDialParam.tCalledAddr.achAlias, tDialParam.tCalledAddr.achE164, 
        tDialParam.tCalledAddr.emType, emTpAlias, emTpE164Num, tDialParam.bCreateConf, tDialParam.tConfInfo.achConfName, tDialParam.byTerNum );
    return wRet;
}

void CCncConfCtrl::OnCnGetTempPwdCmd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg); 

    PrtMsg( ev_CnGetTempPwd_Cmd, emEventTypeCnsRecv, "询问会议模板密码");

    PostEvent( UI_GETTEMPPWD_CMD ); 
}

u16 CCncConfCtrl::GetCnTempPwdInd(s8 achPwd[])
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();

    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_CnGetTempPwd_Ind );
    pcTpMsg->SetBody( achPwd, sizeof(s8)*(MT_MAX_TEMP_PWD_LEN + 1) );

    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_CnGetTempPwd_Ind, emEventTypeCnsSend, "Pwd: %s", achPwd );
    return wRet;
}

const u16 CCncConfCtrl::HungupPtpConf()
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_TppHangUp_Cmd ); 
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TppHangUp_Cmd, emEventTypeCnsSend, "hungup ptp conf" );
    return wRet;
}


const TTPCnsConfStatus& CCncConfCtrl::GetCnsConfStatus() const
{
	return m_tCnsConfStatus;
}


u16 CCncConfCtrl::SetInnerSpeaker( u8 byIndex )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_CnSetInnerSpeaker_Cmd );
	pcTpMsg->SetBody( &byIndex, sizeof(u8) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnSetInnerSpeaker_Cmd, emEventTypeCnsSend, "SpeakerIndex: %d", byIndex );
    return wRet;
}

u8 CCncConfCtrl::GetInnerSpeaker() const
{
	return m_bySpeakSeat;
}


BOOL CCncConfCtrl::IsLocalCnsMute() const
{
	return m_bMute;
}

BOOL CCncConfCtrl::IsLocalCnsQuite() const
{
	return m_bQuite;
}

u16 CCncConfCtrl::SetCnsMute( BOOL bMute /* = TRUE */ )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_tppMute_Cmd );
	pcTpMsg->SetBody( &bMute, sizeof(BOOL) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppMute_Cmd, emEventTypeCnsSend, "bMute: %d", bMute );
    return wRet;
}

u16 CCncConfCtrl::SetCnsQutie( BOOL bQutie /* = TRUE */ )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_tppQuiet_Cmd );
	pcTpMsg->SetBody( &bQutie, sizeof(BOOL) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppQuiet_Cmd, emEventTypeCnsSend, "bQutie: %d", bQutie );
    return wRet;
}

const u8& CCncConfCtrl::GetInputVol() const
{
	return m_byInputVol;
}

u16 CCncConfCtrl::AdjustInputVol( u8 byVolume )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_tppInputVolumeCmd );	
	pcTpMsg->SetBody( &byVolume, sizeof(u8) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppInputVolumeCmd, emEventTypeCnsSend, "Volume: %d", byVolume );
	return wRet;
}

const u8& CCncConfCtrl::GetOutputVol() const 
{
	return m_byOutputVol;
}

u16 CCncConfCtrl::AdjustOutputVol( u8 byVolume )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_tppOutputVolumeCmd );
	pcTpMsg->SetBody( &byVolume, sizeof(u8) );
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_tppOutputVolumeCmd, emEventTypeCnsSend, "Volume: %d", byVolume );
	return wRet;
}

    
u16 CCncConfCtrl::SetSelView( TTPSelViewReq tTPSelViewReq )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_SelView_Req );   
    pcTpMsg->SetBody( &tTPSelViewReq, sizeof(TTPSelViewReq) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_Cn_SelView_Req, emEventTypeCnsSend, "m_wConfID:%d, screenID: %d, m_bSel:%d DstID: %d EpID:%d,Type:%d,DstScrIndx:%d",
		tTPSelViewReq.m_wConfID, tTPSelViewReq.m_wScreenIndx, tTPSelViewReq.m_bSel, tTPSelViewReq.m_wDstID,tTPSelViewReq.m_wEpID,tTPSelViewReq.m_emType,tTPSelViewReq.m_wDstScrIndx );
	return wRet;
}
 

u16 CCncConfCtrl::CancleSelView( u8 byScreenID )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_CnCancelSingleView_Cmd );
    pcTpMsg->SetBody( &byScreenID, sizeof(u8) ); 
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_CnCancelSingleView_Cmd, emEventTypeCnsSend, "screenID: %d ", byScreenID );
    return wRet;
}

//开始轮询 在会议中的控制  nlf确认
u16 CCncConfCtrl::StartPoll( BOOL bStart )
{   
	u16 wEvent = ev_CnStartPoll_Cmd;
	if ( !bStart )
	{
		wEvent = ev_CnStopPoll_Cmd;
	}
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( wEvent ); 
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( wEvent, emEventTypeCnsSend, "bStart: %d", bStart );
	return wRet;
}

//开始点名 在会议中的控制
u16 CCncConfCtrl::StartRoll( TTpConfRollCallInfo tTpConfRollCallInfo )
{   
	u16 wRet = 0;

    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( evConfRollCallUpdate_Cmd );    
	pcTpMsg->SetBody( &tTpConfRollCallInfo, sizeof(TTpConfRollCallInfo) ); 
    
	wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( evConfRollCallUpdate_Cmd, emEventTypeCnsSend, "m_wConfID:%d, m_bStart:%d, RollCaller:%d, m_emRet:%d, m_wNum:%d", 
		tTpConfRollCallInfo.m_wConfID, tTpConfRollCallInfo.m_bStart, tTpConfRollCallInfo.m_atRollCallMemList.GetRollCaller(), tTpConfRollCallInfo.m_emRet, tTpConfRollCallInfo.m_atRollCallMemList.m_wNum );
	return wRet;
}

void CCncConfCtrl::OnStartRollNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 

	TTpConfRollCallInfo tTpConfRollCallInfo = *(TTpConfRollCallInfo*)(cTpMsg.GetBody());
	PrtMsg( evConfRollCallUpdate_Nty, emEventTypeCnsRecv, "m_wConfID:%d, m_bStart:%d, RollCaller:%d, m_emRet:%d, m_wNum:%d, m_wCallTarget:%d", 
		tTpConfRollCallInfo.m_wConfID, tTpConfRollCallInfo.m_bStart, tTpConfRollCallInfo.m_atRollCallMemList.GetRollCaller(), 
		tTpConfRollCallInfo.m_emRet, tTpConfRollCallInfo.m_atRollCallMemList.m_wNum, tTpConfRollCallInfo.m_atRollCallMemList.GetRollCallTarget());
	m_tTpConfRollCallInfo = tTpConfRollCallInfo;

	if (!m_tTpConfRollCallInfo.m_bStart)//点名关闭时 清空点名状态 //点名关闭 数据恢复为初始状态
	{
		m_tTpRollCallPresentStateMsg.Clear();
		m_tTpConfRollCallInfo.Clear();//与umc统一 界面直接清空数据 2017-2-20
	}
	PostEvent( UI_CNS_CONFROLL_NTY); 
}

void CCncConfCtrl::OnStartRollInd( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 

	TTpConfRollCallInfo tTpConfRollCallInfo = *(TTpConfRollCallInfo*)(cTpMsg.GetBody());
	PrtMsg( evConfRollCallUpdate_Ind, emEventTypeCnsRecv, "m_wConfID:%d, m_bStart:%d, m_emRet:%d", 
		tTpConfRollCallInfo.m_wConfID, tTpConfRollCallInfo.m_bStart,tTpConfRollCallInfo.m_emRet );
	if (tTpConfRollCallInfo.m_emRet != em_RollCallOprRsp_Ok)
	{
		PostEvent( UI_CNS_CONFROLL_IND, (WPARAM)tTpConfRollCallInfo.m_bStart, (LPARAM)tTpConfRollCallInfo.m_emRet); 
	}
}

//点名下一个
u16 CCncConfCtrl::RollNext( TTpRollCallNextEpInfo tTpRollCallNextEpInfo )
{   
	u16 wRet = 0;

	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( evConfRollCallNextEp_Cmd );    
	pcTpMsg->SetBody( &tTpRollCallNextEpInfo, sizeof(TTpRollCallNextEpInfo) ); 

	wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( evConfRollCallNextEp_Cmd, emEventTypeCnsSend, "m_wCallTarget: %d", tTpRollCallNextEpInfo.m_wCallTarget );
	return wRet;
}

void CCncConfCtrl::OnRollNextInd( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 

	TTpRollCallNextEpInfo tTpRollCallNextEpInfo = *(TTpRollCallNextEpInfo*)(cTpMsg.GetBody());
	PrtMsg( evConfRollCallNextEp_Ind, emEventTypeCnsRecv, "m_wConfID:%d, m_wCallTarget:%d, m_emRet:%d", 
		tTpRollCallNextEpInfo.m_wConfID, tTpRollCallNextEpInfo.m_wCallTarget,tTpRollCallNextEpInfo.m_emRet );

	if (tTpRollCallNextEpInfo.m_emRet != em_RollCallOprRsp_Ok)
	{
		PostEvent( UI_CNS_CONFROLLNEXT_IND, (WPARAM)tTpRollCallNextEpInfo.m_wCallTarget, (LPARAM)tTpRollCallNextEpInfo.m_emRet); 
	}
}

//被点名者与会状态发送
u16 CCncConfCtrl::RollAttendState( TTpRollCallPresentStateMsg tTpRollCallPresentStateMsg )
{   
	u16 wRet = 0;

	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( evtpRollUpdate_PresentState );    
	pcTpMsg->SetBody( &tTpRollCallPresentStateMsg, sizeof(TTpRollCallPresentStateMsg) ); 

	wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( evtpRollUpdate_PresentState, emEventTypeCnsSend, "m_wValidNum: %d, m_wEpID:%d, state:%d(em_RollCallPresentState_Ok=0,em_RollCallPresentState_Absent=1",
		tTpRollCallPresentStateMsg.m_wValidNum, tTpRollCallPresentStateMsg.m_atEpState[0].m_wEpID, tTpRollCallPresentStateMsg.m_atEpState[0].m_wEpState);

	return wRet;
}

//开启会议后被点名者列表更新
u16 CCncConfCtrl::RollListFixedCmd(TTpUpdataRollCallList tTpUpdataRollCallList)
{
	u16 wRet = 0;

	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( evConfRollCallUpdataList_Cmd );    
	pcTpMsg->SetBody( &tTpUpdataRollCallList, sizeof(TTpUpdataRollCallList) ); 

	wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( evConfRollCallUpdataList_Cmd, emEventTypeCnsSend, "m_bAdd: %d, m_wNum:%d, EpID:%d",
		tTpUpdataRollCallList.m_bAdd, tTpUpdataRollCallList.m_atRollCallMemList.m_wNum, tTpUpdataRollCallList.m_atRollCallMemList.m_awList[0] );

	return wRet;
}
void CCncConfCtrl::OnRollListFixedInd(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg); 

	TTpUpdataRollCallListRes tTpUpdataRollCallListRes = *(TTpUpdataRollCallListRes*)(cTpMsg.GetBody());
	PrtMsg( evConfRollCallUpdataList_Ind, emEventTypeCnsRecv, "m_wConfID:%d, m_bAdd:%d, m_emRet:%d", 
		tTpUpdataRollCallListRes.m_wConfID, tTpUpdataRollCallListRes.m_bAdd,tTpUpdataRollCallListRes.m_emRet[0] );

	EmRollCallRspRet emRet = em_RollCallOprRsp_Ok;
	for (int i=0; i<tTpUpdataRollCallListRes.m_atRollCallMemList.m_wNum; i++)
	{
		if (tTpUpdataRollCallListRes.m_emRet[i] != em_RollCallOprRsp_Ok && tTpUpdataRollCallListRes.m_emRet[i] != em_StartRollCall_begin
			&& tTpUpdataRollCallListRes.m_emRet[i] != em_UpdateRollCalList_begin && tTpUpdataRollCallListRes.m_emRet[i] != em_RollCallNextEp_begin 
			&& tTpUpdataRollCallListRes.m_emRet[i] != em_RollcallNotify_begin && tTpUpdataRollCallListRes.m_emRet[i] != em_RollCallOprRsp_End )
		{
			emRet = tTpUpdataRollCallListRes.m_emRet[i];
		}
	}

	if (emRet != em_RollCallOprRsp_Ok)
	{
		PostEvent( UI_CNS_CONFROLL_LISTFIXED_IND, (WPARAM)emRet); 
	}
}

//被点名者与会状态回应；整体列表中与会状态登陆时通知
void CCncConfCtrl::OnRollAttendNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 

	TTpRollCallPresentStateMsg tTpRollCallPresentStateMsg = *(TTpRollCallPresentStateMsg*)(cTpMsg.GetBody());
	PrtMsg( evtpRoll_PresentState_Nty, emEventTypeCnsRecv, "m_wConfID:%d, m_wValidNum:%d", 
		tTpRollCallPresentStateMsg.m_wConfID, tTpRollCallPresentStateMsg.m_wValidNum );

	for (int i=0; i<tTpRollCallPresentStateMsg.m_wValidNum; i++)
	{
		PrtMsg( evtpConfAudMixMode_Nty, emEventTypeCnsRecv, "listitem%d:m_wEpID:%d m_wEpState:%d,", 
			i,tTpRollCallPresentStateMsg.m_atEpState[i].m_wEpID, tTpRollCallPresentStateMsg.m_atEpState[i].m_wEpState );
	}
	//2016-11-29 更新为每次都发全部的状态列表 并进行保存更新 之前只有登录的时候发全部
	m_tTpRollCallPresentStateMsg = tTpRollCallPresentStateMsg;
	PostEvent( UI_CNS_CONFROLL_ATTEND_NTY); 
}

//开始混音
u16 CCncConfCtrl::StartConfMix( TTpAudMixInfo tTpAudMixInfo )
{   
	u16 wRet = 0;

	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( evConfAudMixMode_Cmd );    
	pcTpMsg->SetBody( &tTpAudMixInfo, sizeof(TTpAudMixInfo) ); 

	wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( evConfAudMixMode_Cmd, emEventTypeCnsSend, "m_emMode: %d m_tMixList.m_wNum:%d", tTpAudMixInfo.m_emMode, tTpAudMixInfo.m_tMixList.m_wNum );
	return wRet;
}

void CCncConfCtrl::OnConfMixStateNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 

	TTpAudMixInfo tTpAudMixInfo = *(TTpAudMixInfo*)(cTpMsg.GetBody());
	m_tTpAudMixInfo = tTpAudMixInfo;

	PrtMsg( evtpConfAudMixMode_Nty, emEventTypeCnsRecv, "m_wConfId:%d, m_tMixList.m_wNum:%d, m_emMode:%d", 
		tTpAudMixInfo.m_wConfId, tTpAudMixInfo.m_tMixList.m_wNum,tTpAudMixInfo.m_emMode );
	for (int i=0; i<tTpAudMixInfo.m_tMixList.m_wNum; i++)//混音列表全部打印
	{
		PrtMsg( evtpConfAudMixMode_Nty, emEventTypeCnsRecv, "m_tMixList item%d:%d,", 
			i,tTpAudMixInfo.m_tMixList.m_awMixEp[i] );
	}

	PostEvent( UI_CNS_CONFMIX_NTY); 
}

void CCncConfCtrl::OnStarConfMixInd( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 

	TTpAudMixModeCmdRes tTpAudMixModeCmdRes = *(TTpAudMixModeCmdRes*)(cTpMsg.GetBody());

	PrtMsg( evConfAudMixMode_Ind, emEventTypeCnsRecv, "m_wConfID:%d, m_emCmdMode:%d, m_emRet:%d", 
		tTpAudMixModeCmdRes.m_wConfId, tTpAudMixModeCmdRes.m_emCmdMode,tTpAudMixModeCmdRes.m_emRes );

	if (tTpAudMixModeCmdRes.m_emRes != em_umsaudmixres_sucess)
	{
		PostEvent( UI_CNS_CONFMIX_IND, (WPARAM)tTpAudMixModeCmdRes.m_emCmdMode, (LPARAM)tTpAudMixModeCmdRes.m_emRes); 
	}
}

//修改混音列表
u16 CCncConfCtrl::ConfMixFixCmd( TTpAudMixListCmd tTpAudMixListCmd )
{   
	u16 wRet = 0;

	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( evConfAudMixList_Cmd );    
	pcTpMsg->SetBody( &tTpAudMixListCmd, sizeof(TTpAudMixListCmd) ); 

	wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( evConfAudMixList_Cmd, emEventTypeCnsSend, "m_emOpr: %d, m_tMixList.m_wNum:%d", tTpAudMixListCmd.m_emOpr, tTpAudMixListCmd.m_tList.m_wNum );
	m_tTpAudMixListCmdRes.Clear();
	return wRet;
}

//////////////////////////////////////////////////////////////////////////
// 	收到的结构体TTpAudMixListCmdRes中 与汪团结确认
// 	TTpAudMixList		m_tList;//不是全部的list，是操作添加或删除的那次操作的LIST
// 	EmAudMixRes		    m_aemRes[TP_APU2_MAX_CHAN_NUM];// 要根据m_tList里面的大小 来取m_aemRes数组里面对应的每一个的枚举值来看对应的那个会场是不是添加进去

void CCncConfCtrl::OnConfMixFixInd( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 
	m_tTpAudMixListCmdRes = *(TTpAudMixListCmdRes*)(cTpMsg.GetBody());

	PrtMsg( evConfAudMixList_Ind, emEventTypeCnsRecv, "m_wConfID:%d, m_tList.m_wNum:%d", 
		m_tTpAudMixListCmdRes.m_wConfId, m_tTpAudMixListCmdRes.m_tList.m_wNum );
	
	PostEvent( UI_CNS_CONFMIX_FIX_IND); 
	
}

void CCncConfCtrl::OnEpInAudMixNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg); 

	u8 uInst = cTpMsg.GetHomeplace();

	BOOL bInAudMix = *(BOOL*)(cTpMsg.GetBody());
	PrtMsg( ev_EpInAudMix_Nty, emEventTypeCnsRecv, "bInAudMix: %d, Inst: %d", bInAudMix, uInst );

	if ( m_bInAudMix != bInAudMix )
	{
		m_bInAudMix = bInAudMix;
		PostEvent( UI_CNC_INAUDMIX_NTY, m_bInAudMix );
	}			
}

BOOL CCncConfCtrl::IsLocalCnsDual() const
{
	return m_bDual;
}

BOOL CCncConfCtrl::IsLocalPTPSeatArouse() const
{
	return m_bPTPSeatArouse;
}
 
u16 CCncConfCtrl::StartDualCodeStream( const TTPCnMediaTransPort &tVideoTransAddr, const TTPCnMediaTransPort &tAudioTransAddr ) const
{     
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
   
    pcTpMsg->SetEvent( ev_TppAddDualRcvAddr_Cmd ); 
    pcTpMsg->SetBody( &tVideoTransAddr, sizeof(TTPCnMediaTransPort) );  
    pcTpMsg->CatBody( &tAudioTransAddr, sizeof(TTPCnMediaTransPort) );
   
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    in_addr tAddr;
    tAddr.S_un.S_addr = tVideoTransAddr.m_tRtpPort.m_tIP.dwIPV4;
    in_addr tAudioAddr;
    tAudioAddr.S_un.S_addr = tAudioTransAddr.m_tRtpPort.m_tIP.dwIPV4;

    PrtMsg( ev_TppAddDualRcvAddr_Cmd, emEventTypeCnsSend, "VideoAddr: %s, Port: %d, AudioAddr: %s, Port: %d", inet_ntoa(tAddr), tVideoTransAddr.m_tRtpPort.m_wPort
        ,inet_ntoa(tAudioAddr), tAudioTransAddr.m_tRtpPort.m_wPort );

	return wRet;
}


u16 CCncConfCtrl::StopDualCodeStream() const 
{   
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    
    pcTpMsg->SetEvent( ev_TppDelDualRcvAddr_Cmd );  
    pcTpMsg->SetBody( &m_nVideoNode, sizeof(u16) );
    
     
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TppDelDualRcvAddr_Cmd, emEventTypeCnsSend,"" ); 
     

    pcTpMsg->SetBody( &m_nAudioNode, sizeof(u16)  );
    wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TppDelDualRcvAddr_Cmd, emEventTypeCnsSend,"" );

   
	return wRet;
}

u16 CCncConfCtrl::ReqKeyFrame( BOOL32 bForce ) const 
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    
    pcTpMsg->SetEvent( ev_TppPadDualKeyFrame_Req  );  
    pcTpMsg->SetBody( &m_nVideoNode, sizeof(u16) );
	pcTpMsg->CatBody( &bForce, sizeof(BOOL32) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TppPadDualKeyFrame_Req , emEventTypeCnsSend ,"");
	return wRet;
}

u16 CCncConfCtrl::ScrnDisplayDual( const u16 wScrnID ) const 
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    
    pcTpMsg->SetEvent( ev_TppSelDualView_Cmd  );  
    pcTpMsg->SetBody( &wScrnID, sizeof(u16) ); 
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TppSelDualView_Cmd , emEventTypeCnsSend ,"scrnID: %d", wScrnID);
	return wRet;
}


u16 CCncConfCtrl::ScrnStopDisplayDual( const u16 wScrnID ) const
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    
    pcTpMsg->SetEvent( ev_TppCancelSelDualView_Cmd  );  
    pcTpMsg->SetBody( &wScrnID, sizeof(u16) ); 
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_TppCancelSelDualView_Cmd  , emEventTypeCnsSend ,"scrnID:%d", wScrnID);

	return wRet;
}

/** 
* 功能  屏幕回显
* @return    
* @remarks 
*/
u16 CCncConfCtrl::ScrnDisplayLocal( const u16 wScrnID ) const  
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    
    pcTpMsg->SetEvent( ev_CnViewLocal_Cmd  );  
    pcTpMsg->SetBody( &wScrnID, sizeof(u16) ); 
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_CnViewLocal_Cmd  , emEventTypeCnsSend ,"wScrnID:%d",wScrnID);
    return wRet;
}

/** 
* 功能  取消屏幕回显
* @return    
* @remarks 
*/
u16 CCncConfCtrl::ScrnStopDisplayLocal( const u16 wScrnID ) const  
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    
    pcTpMsg->SetEvent(  ev_CnCancelViewLocal_Cmd  );  
    pcTpMsg->SetBody( &wScrnID, sizeof(u16) ); 
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg(  ev_CnCancelViewLocal_Cmd  , emEventTypeCnsSend ,"wScrnID:%d",wScrnID);
    return wRet;
}



u16 CCncConfCtrl::StartDual( BOOL  bStart )
{
    u16 msgID = ev_TppStartDual_Cmd;
    if ( !bStart )
    {
        msgID = ev_TppStopDual_Cmd;
    }
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( msgID );
    pcTpMsg->SetBody( &bStart, sizeof(BOOL) ); 
   
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( msgID, emEventTypeCnsSend, "bStart: %d", bStart );
	return wRet;
}

const vector<TScreenInfo>& CCncConfCtrl::GetCnsScreenInfo() const
{
	return m_vctScreenInfo;
}


void CCncConfCtrl::OnConfStateNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
				
    TTPCnsConfStatus tConfStatus = *reinterpret_cast<TTPCnsConfStatus*>(cTpMsg.GetBody());

	PrtMsg( ev_CnConfState_Nty, emEventTypeCnsRecv, "TTPCnsConfStatus: ConfName: %s, ConfID: %d, State: %d \
 (%d:em_CALL_IDLE, %d:em_CALL_CALLING, %d:em_CALL_CONNECTED),\
 ConfType: %d (%d:emCallType_P2P, %d:emCallType_Conf),  bMixMotive:%d  EncryptType:%d  ", 
		tConfStatus.achConfName, tConfStatus.wConfID, tConfStatus.emState, 
        em_CALL_IDLE, em_CALL_CALLING, em_CALL_CONNECTED, tConfStatus.m_emCallType, emCallType_P2P, emCallType_Conf, tConfStatus.m_bMixMotive, tConfStatus.m_emTPEncryptType );

	m_tCnsConfStatus = tConfStatus;

	//会议状态的信息结会时cnc手动清除
	if (tConfStatus.emState != em_CALL_CONNECTED)
	{
		m_bInAudMix = FALSE;
	}
	
    /*在CUmcConfCtrl中统一通知界面
    if ( m_tCnsConfStatus.emState != em_CALL_CALLING )
    {
	    PostEvent( UI_CNS_CONFSTATE_NOTIFY, bInConf, (LPARAM)&m_tCnsConfStatus );
    }*/
}

void CCncConfCtrl::OnQuietInd(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);

    u8 uInst = cTpMsg.GetHomeplace();

	BOOL bQuiet = *(BOOL*)(cTpMsg.GetBody());
	PrtMsg( ev_tppQuietInd, emEventTypeCnsRecv, "bQuite: %d, Inst: %d", bQuiet, uInst );

	if ( m_bQuite != bQuiet )
	{
		m_bQuite = bQuiet;
		PostEvent( UI_CNS_QUITE_MUTE, TRUE, m_bQuite );
	}			
}

void CCncConfCtrl::OnMuteInd(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);
    u8 uInst = cTpMsg.GetHomeplace();

	BOOL bMute = *(BOOL*)(cTpMsg.GetBody());
	PrtMsg( ev_tppMuteInd, emEventTypeCnsRecv, "bMute: %d, Inst: %d", bMute, uInst );

	if ( m_bMute != bMute )
	{
		m_bMute = bMute;
		PostEvent( UI_CNS_QUITE_MUTE, FALSE, m_bMute );
	}			
}

void CCncConfCtrl::OnInputVolInd(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	u8 uInst = cTpMsg.GetHomeplace();
	if ( m_pSession->GetInst() == uInst )
	{
		m_byInputVol = *(u8*)(cTpMsg.GetBody());
		
		PostEvent( UI_CNS_INVOL_UPDATE , m_byInputVol, 0 );
	}
	
	PrtMsg( ev_tppInputVolumeInd, emEventTypeCnsRecv, "InputVol: %d, Inst: %d", m_byInputVol, uInst );
}

void CCncConfCtrl::OnOutPutVolInd(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	u8 uInst = cTpMsg.GetHomeplace();
	if ( m_pSession->GetInst() == uInst )
	{
		m_byOutputVol = *(u8*)(cTpMsg.GetBody());

		PostEvent( UI_CNS_OUTVOL_UPDATE );
	}

	PrtMsg( ev_tppOutputVolumeInd, emEventTypeCnsRecv, "OutputVol: %d, Inst: %d", m_byOutputVol, uInst );
}

void CCncConfCtrl::OnSetInnerSpeaker(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	
	u8 uInst = cTpMsg.GetHomeplace();
	if ( m_pSession->GetInst() == uInst )
	{
		m_bySpeakSeat = *(u8*)(cTpMsg.GetBody());
		PostEvent( UI_CNS_SPOKES_SEAT_NOTIFY, m_bySpeakSeat );

		PrtMsg( ev_CnSetInnerSpeaker_Ind, emEventTypeCnsRecv, "SpeakSeat: %d, Inst: %d", m_bySpeakSeat, uInst );
	}
	
	
}

void CCncConfCtrl::OnScreenDisplayInd(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	u8 byScreen = *(u8*)(cTpMsg.GetBody());	
	if ( byScreen >= 3 )
	{
		return;
	}	
	s8 achCnsName[TP_MAX_ALIAS_LEN + 1] = {0};
	strncpy( achCnsName, (s8*)(cTpMsg.GetBody()+sizeof(u8)), TP_MAX_ALIAS_LEN );

	u8 uInst = cTpMsg.GetHomeplace();

	if ( m_pSession->GetInst() == uInst )
	{
		UpdateScreenInfo( byScreen, achCnsName );
		PostEvent( UI_CNS_SCREEN_NAME_NOTIFY, byScreen, (LPARAM)achCnsName );

		PrtMsg( ev_CnYouAreSeeing_Ind, emEventTypeCnsRecv, "Screen: %d, CnsName: %s, Inst: %d", byScreen, achCnsName, uInst );
	}	
}

void CCncConfCtrl::OnScreenStateNotify( const CMessage &cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
	u8 byScreenID = *(u8*)(cTpMsg.GetBody());	

    EMPosPic emPic = *(EMPosPic*)( cTpMsg.GetBody() + sizeof(u8));
    
    s8 achCnsName[TP_MAX_ALIAS_LEN + 1] = {0};
	strncpy( achCnsName, (s8*)(cTpMsg.GetBody()+sizeof(u8)) + sizeof(EMPosPic), TP_MAX_ALIAS_LEN );

  /* 
    EmTPPosStatus emState = *(EmTPPosStatus*)( cTpMsg.GetBody() + sizeof(u8) );	
	EMPosPic emPos = *(EMPosPic*)( cTpMsg.GetBody() + sizeof(u8) + sizeof(EmTPPosStatus) );

    PrtMsg( ev_CnActivePos_Nty, emEventTypeCnsRecv, "Screen: %d, emState: %d, emPosPic: %d ", byScreen, emState, emPos );
    ev_CnPosAllStatus_Nty*/

    PrtMsg( ev_CnPosAllStatus_Nty, emEventTypeCnsRecv, "Screen: %d, emPosPic: %d , scrnName: %s", byScreenID,emPic ,achCnsName);
	UpdateScreenInfo( byScreenID, achCnsName, emPic );
	PostEvent( UI_CNS_SCREEN_STATE_NOTIFY, byScreenID, emPic ); 
}

// TScreenInfo *CCncConfCtrl::GetScreenInfoByID( const u8 byeScreenID ) 
// {
//     vector<TScreenInfo>::iterator it = m_vctScreenInfo.begin();
//     while ( it != m_vctScreenInfo.end() )
//     {
//         if ( it->byScreenID == byeScreenID )
//         {
//             return (TScreenInfo*)(&it);
//         }
// 		it++;
//     }
//     return NULL;
// }

void CCncConfCtrl::UpdateScreenInfo( u8 byScreen, s8* achCnsName )
{
	TScreenInfo tInfo;
	for ( u8 i = 0; i < m_vctScreenInfo.size(); i++ )
	{
		tInfo = m_vctScreenInfo.at(i);
		if ( tInfo.byScreenID == byScreen )
		{
			strncpy( m_vctScreenInfo[i].achCnsName, achCnsName, TP_MAX_ALIAS_LEN );
			return;
		}
	}
	tInfo.byScreenID = byScreen;
	strncpy( tInfo.achCnsName, achCnsName, TP_MAX_ALIAS_LEN );
	m_vctScreenInfo.push_back( tInfo );
}


void CCncConfCtrl::UpdateScreenInfo( u8 byScreen, s8* achCnsName,EMPosPic emPic )
{
    TScreenInfo tInfo;
    for ( u8 i = 0; i < m_vctScreenInfo.size(); i++ )
    {
        tInfo = m_vctScreenInfo.at(i);
        if ( tInfo.byScreenID == byScreen )
        {
            strncpy( m_vctScreenInfo[i].achCnsName, achCnsName, TP_MAX_ALIAS_LEN );
            m_vctScreenInfo[i].emPosPic = emPic; 

            return;
        }
    }
	tInfo.byScreenID = byScreen;
	strncpy( tInfo.achCnsName, achCnsName, TP_MAX_ALIAS_LEN );
	tInfo.emPosPic = emPic;
	m_vctScreenInfo.push_back( tInfo );
}

void CCncConfCtrl::UpdateScreenInfo( u8 byScreen, EmTPPosStatus emStatus, EMPosPic emPos )
{
	TScreenInfo tInfo;
	for ( u8 i = 0; i < m_vctScreenInfo.size(); i++ )
	{
		tInfo = m_vctScreenInfo.at(i);
		if ( tInfo.byScreenID == byScreen )
		{
			m_vctScreenInfo[i].emScreenState = emStatus;
			m_vctScreenInfo[i].emPosPic = emPos;
			return;
		}
	}
	tInfo.byScreenID = byScreen;
	tInfo.emScreenState = emStatus;
	tInfo.emPosPic = emPos;
	m_vctScreenInfo.push_back( tInfo );
}


void CCncConfCtrl::OnSetSelViewInd( const CMessage &cMsg )
{ 
    CTpMsg cTpMsg(&cMsg);  
    TTPSelViewInd tTPSelViewInd = *(TTPSelViewInd*)(cTpMsg.GetBody());	

    PrtMsg( ev_Cn_SelView_Ind, emEventTypeCnsRecv, "Screen: %d, errorCode: %d",tTPSelViewInd.m_tSelView.m_wScreenIndx, tTPSelViewInd.m_emRet );

// 	if ( emRe == EmViewRetReason_Success  ) //ind只提示 不保存状态 nty保存
// 	{
// 		if (tTPSelViewInd.m_tSelView.m_bSel)
// 		{
// 			UpdateScreenInfo( tTPSelViewInd.m_tSelView.m_wScreenIndx, emPosAcitve, emPic_SelView );
// 		}
// 	}

    PostEvent( UI_CNS_SEL_VIEW_IND, (WPARAM)&tTPSelViewInd, tTPSelViewInd.m_emRet );     
}

void CCncConfCtrl::OnSetSelViewNty( const CMessage &cMsg )
{ 
	CTpMsg cTpMsg(&cMsg);  
	TTPSelViewNtfy tTPSelViewNtfy = *(TTPSelViewNtfy*)(cTpMsg.GetBody());	

	PrtMsg( ev_UMS_CNC_ByCNS_SelView_Ntfy, emEventTypeCnsRecv, "m_wConfID: %d m_wEpID:%d m_wDstID1:%d m_wDstID2:%d m_wDstID3:%d DstScrIndx0:%d DstScrIndx1:%d DstScrIndx2:%d", tTPSelViewNtfy.m_wConfID, tTPSelViewNtfy.m_wEpID,
		tTPSelViewNtfy.m_atSelView[0].m_wDstID, tTPSelViewNtfy.m_atSelView[1].m_wDstID,tTPSelViewNtfy.m_atSelView[2].m_wDstID,tTPSelViewNtfy.m_atSelView[0].m_wDstScrIndx,
		tTPSelViewNtfy.m_atSelView[1].m_wDstScrIndx,tTPSelViewNtfy.m_atSelView[2].m_wDstScrIndx);

	for (int i=0; i<TP_MAX_STREAMNUM; i++)
	{
		if (tTPSelViewNtfy.m_atSelView[i].m_bSel && tTPSelViewNtfy.m_atSelView[i].IsValid())
		{
			UpdateScreenInfo( tTPSelViewNtfy.m_atSelView[i].m_wScreenIndx, emPosAcitve, emPic_SelView );
		}
	}
	//cnclib不发消息 更新屏状态 UMC里面发消息更新 dyy 2015-6-26 
	//PostEvent( UI_CNS_SEL_VIEW_NTY, (WPARAM)&tTPSelViewNtfy, NULL ); 
}

void CCncConfCtrl::OnStartPollRsp( const CMessage &cMsg )
{
    CTpMsg cTpMsg(&cMsg); 
    
    u16 wEvent = cTpMsg.GetEvent();

	EmTPPollResult emRe = *(EmTPPollResult*)( cTpMsg.GetBody() ); 
    PrtMsg( wEvent, emEventTypeCnsRecv, " emResult: %d ", emRe );
    
	BOOL bPoll = FALSE;
    if ( wEvent == ev_CnStartPoll_Ind )
    {       
        bPoll = TRUE;      
    }
    else if( wEvent == ev_CnStopPoll_Ind )
    {     
		bPoll = FALSE;
    } 

	//界面响应ev_CnPollStatus_Nty消息即可 此消息只进行错误提示
	PostEvent( UI_CNS_START_POLL_RSP, (WPARAM)bPoll, (LPARAM)emRe ); 
}

/*
enum EmCnsCallReason	
{
	EmCnsCallReason_success,
	EmCnsCallReason_hungup,			//本地挂断
	EmCnsCallReason_Unreachable,	//对端不在线，无法呼叫
	EmCnsCallReason_resourcefull,	//对端无可用资源
	EmCnsCallReason_dstnotfind,		//目标不存在
	EmCnsCallReason_Busy,			//对端忙
	EmCnsCallReason_Local,			//本地原因
	EmCnsCallReason_NoConf,			//会议不存在
	EmCnsCallReason_Exist,			//对端已在本会议中
	EmCnsCallReason_Rejected,		//对端拒绝
	EmCnsCallReason_peerhungup,		//对端挂断
//	EmCnsCallReason_AlreadyDual,    //对端在双流
	EmCnsCallReason_Abnormal,       //本地掉线挂断
	EmCnsCallReason_PeerAbnormal,   //对端掉线挂断
	EmCnsCallReason_ConfOver,	//会议结束
	EmCnsCallReason_cncallexception,	//接入模块(cncall)掉线
	EmCnsCallReason_ConfExist,		//会议已存在
	EmCnsCallReason_unknown,  
	
	  
}; 
*/
void CCncConfCtrl::OnHungupNotify( const CMessage &cMsg )
{
    CTpMsg cTpMsg(&cMsg); 
    
    u8 uInst = cTpMsg.GetHomeplace();
    
    EmCnsCallReason emRe = *(EmCnsCallReason*)(cTpMsg.GetBody()); 

    PrtMsg( ev_TppHangUp_Ind, emEventTypeCnsRecv, "Inst: %d, emReason:%d ",uInst, emRe );

	if ( emRe != EmCnsCallReason_success )
	{
		PrtMsg( " ( %d:EmCnsCallReason_success, %d:EmCnsCallReason_hungup, %d:EmCnsCallReason_Unreachable, %d:EmCnsCallReason_resourcefull \
%d:EmCnsCallReason_dstnotfind, %d:EmCnsCallReason_Busy, %d:EmCnsCallReason_Local, %d:EmCnsCallReason_NoConf, \
%d:EmCnsCallReason_Exist, %d:EmCnsCallReason_Rejected, %d:EmCnsCallReason_peerhungup, %d:EmCnsCallReason_Abnormal, \
%d:EmCnsCallReason_PeerAbnormal, %d:EmCnsCallReason_ConfOver ,  %d:EmCnsCallReason_cncallexception , \
%d:EmCnsCallReason_ConfExist ,%d:EmCnsCallReason_unknown ) ",  
             EmCnsCallReason_success,EmCnsCallReason_hungup,EmCnsCallReason_Unreachable, EmCnsCallReason_resourcefull,
			 EmCnsCallReason_dstnotfind, EmCnsCallReason_Busy, EmCnsCallReason_Local,EmCnsCallReason_NoConf,EmCnsCallReason_Exist,
			 EmCnsCallReason_Rejected,EmCnsCallReason_peerhungup,EmCnsCallReason_Abnormal,EmCnsCallReason_PeerAbnormal,
			 EmCnsCallReason_ConfOver,EmCnsCallReason_cncallexception,EmCnsCallReason_ConfExist,EmCnsCallReason_unknown );
	}
    
    PostEvent( UI_CNS_HUNGUP_P2P_NOTIFY, emRe, 0 ); 
}

void CCncConfCtrl::OnStartDualCdStrmRsp( const CMessage &cMsg )
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
    
    PrtMsg( ev_TppAddDualRcvAddr_Ind, emEventTypeCnsRecv, "Inst: %d, emVideoReason:%d , emAudioReaso=%d  \
( %d:emAddDualRcvSucceed,%d:emAddDualRcvFailNoDual,%d:emAddDualRcvFailIllegalPos，%d:emAddDualRcvFailNoPos, \
%d:emAddDualRcvFailUnKown)",uInst, emReVideo,emReAudio, emAddDualRcvSucceed,emAddDualRcvFailNoDual,
emAddDualRcvFailIllegalPos,emAddDualRcvFailNoPos,emAddDualRcvFailUnKown );
     
    
    
    PostEvent( UI_CNSINS_START_DUALCODESTREAM_RSP,  emReVideo , emReAudio ); 
}
 

 
void CCncConfCtrl::OnStopDualCdStrmRsp( const CMessage &cMsg )
{
    CTpMsg cTpMsg(&cMsg); 

    m_nVideoNode = TP_INVALID_INDEX;
    m_nAudioNode = TP_INVALID_INDEX;

	EmTPDeleteDualRcvResult emReVideo = *(EmTPDeleteDualRcvResult*)(cTpMsg.GetBody());

	PrtMsg( ev_TppDelDualRcvAddr_Ind, emEventTypeCnsRecv, "" );
}

void CCncConfCtrl::OnScrnDisplayDualRsp( const CMessage &cMsg )
{
    CTpMsg cTpMsg(&cMsg);    

	u16 wScrnID =  *(u16*)( cTpMsg.GetBody() );
    EmTPAddDualRcvResult emRe = *(EmTPAddDualRcvResult*)( cTpMsg.GetBody() + sizeof(u16) );
    
    PrtMsg( ev_TppSelDualView_Ind, emEventTypeCnsRecv, "scrnID: %d, result: %d", wScrnID,emRe );

    PostEvent( UI_CNS_SCRN_DISPLAY_DUAL_RSP, wScrnID, emRe );  
}

void CCncConfCtrl::OnStopScrnDisplayDualRsp( const CMessage &cMsg )
{
    CTpMsg cTpMsg(&cMsg); 
    
	u16  wScrnID =  *(u16*)( cTpMsg.GetBody() );
    EmTPDeleteDualRcvResult emRe = *(EmTPDeleteDualRcvResult*)( cTpMsg.GetBody() + sizeof(u16) );
    
    
    PrtMsg( ev_TppCancelSelDualView_Ind, emEventTypeCnsRecv, "scrnID:%d, result: %d", wScrnID,emRe);
    
    PostEvent( UI_CNS_STOP_SCRN_DISPLAY_DUAL_RSP, wScrnID, emRe );  
}


void CCncConfCtrl::OnScrnDisplayLocalRsp( const CMessage &cMsg )
{
    CTpMsg cTpMsg(&cMsg); 
    
	u16 wScrnID = *(u16*)( cTpMsg.GetBody() );
    EmTPViewLocalResult emRe = *(EmTPViewLocalResult*)( cTpMsg.GetBody() + sizeof(u16) );    
    
    PrtMsg( ev_CnViewLocal_Ind, emEventTypeCnsRecv, "scrnID:%d, result: %d", wScrnID, emRe );
    
    PostEvent( UI_CNS_SCRN_DISPLAY_LOCAL_RSP, wScrnID, emRe );  
}


void CCncConfCtrl::OnStopDisplayLocalRsp( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 
    
	u16  wScrnID = *(u16*)( cTpMsg.GetBody() );
    EmTPViewLocalResult emRe = *(EmTPViewLocalResult*)( cTpMsg.GetBody() + sizeof(u16) );
       
    PrtMsg( ev_CnCancelViewLocal_Ind, emEventTypeCnsRecv, "scrnID:%d, result: %d", wScrnID, emRe );
    
    PostEvent( UI_CNS_STOP_SCRN_DISPLAY_LOCAL_RSP, wScrnID, emRe );  
}


void CCncConfCtrl::OnStartDualRsp( const CMessage &cMsg )
{
    CTpMsg cTpMsg(&cMsg); 
    EmTPDualReason emSuc = *(EmTPDualReason*)(cTpMsg.GetBody()); 
    u16 wEvent = cTpMsg.GetEvent();

	BOOL bStart = FALSE;
    if ( wEvent == ev_TppStartDual_Ind )
    {
		bStart = TRUE;       	
    }
    else
    {
		bStart = FALSE;    
    } 

	PrtMsg( wEvent, emEventTypeCnsRecv, "bStart:%d, result: %d ( bStart==TRUE,emTpDualAccept:%d, \
emTpDualBusy:%d, emTpDualPreemptive:%d, emTpDualPeerReject:%d, emTpDualPeerStop:%d, emTpDualNoVideo:%d, emTpDualLocalStop:%d, emTpDualSndFail:%d )", 
			bStart==TRUE,emSuc, emTpDualAccept, emTpDualBusy, emTpDualPreemptive, emTpDualPeerReject, emTpDualPeerStop, emTpDualNoVideo, emTpDualLocalStop, emTpDualSndFail );

	PostEvent( UI_CNS_START_DUAL_RSP, bStart, (LPARAM)emSuc );  
}

void CCncConfCtrl::OnDualStatusNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 
    
    u8 uInst = cTpMsg.GetHomeplace();
     
	BOOL bDual = *(BOOL*)(cTpMsg.GetBody());
	PrtMsg( ev_TppIsDual_Nty, emEventTypeCnsRecv, "bDual: %d, Inst: %d ", bDual, uInst );
	 
	if ( m_bDual != bDual )
	{
		m_bDual = bDual;
	}

	PostEvent( UI_CNS_DUAL_STATE_NOTIFY, m_bDual, 0 ); 
}


void CCncConfCtrl::OnRecvDualNty( const CMessage &cMsg )
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

void CCncConfCtrl::OnCnDualOfflineNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 

	PrtMsg( ev_tpCnRoomDualOffline_Nty, emEventTypeCnsRecv, "" );
	
	PostEvent( UI_CNS_DUALOFFLINE_NOTIFY, 0, 0 ); 
}

void CCncConfCtrl::OnDualRcvInterruptNty( const CMessage &cMsg )
{    
    CTpMsg cTpMsg(&cMsg); 

    EmTPChannelReason emReason = *(EmTPChannelReason*)(cTpMsg.GetBody()); 
    PrtMsg( ev_TppDualRcvInterrupt_Nty, emEventTypeCnsRecv, "reason:%d" ,emReason);
    
    PostEvent( UI_RECV_DUAL_INTERRUPT, emReason, 0 ); 
}

void CCncConfCtrl::OnCnSetDesktopMicInfoNty(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);  	
	BOOL bState = *(BOOL*)( cTpMsg.GetBody());

	PostEvent( UI_CNC_CNDESKTOPMICINFO_NTY, bState, 0 ); 
	PrtMsg( ev_CnSetDesktopMicInfo_Nty, emEventTypeCnsRecv, "bState:%d", bState);
}

void CCncConfCtrl::OnCnSetDesktopMicInfoInd(const CMessage &cMsg)
{
	CTpMsg cTpMsg(&cMsg);  	
	BOOL bState = *(BOOL*)( cTpMsg.GetBody());
	BOOL bIsOK = *(BOOL*)( cTpMsg.GetBody() + sizeof(BOOL));
	if (!bIsOK)
	{
		bState = !bState;
	}

	PostEvent( UI_CNC_CNDESKTOPMICINFO_NTY, bState, 0 ); 
	PrtMsg( ev_CnSetDesktopMicInfo_Ind, emEventTypeCnsRecv, "bState:%d, bIsOk:%d", bState, bIsOK);
}

void CCncConfCtrl::OnCnMicPowerStyleNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg);  	
	m_tTpMicStyle = *(TTpMicState*)( cTpMsg.GetBody());

	PostEvent( UI_CNC_CNMICPOWERSTYLE_NTY, (WPARAM)(&m_tTpMicStyle), 0 ); 
	PrtMsg( ev_CnMicPowerStyle_Nty, emEventTypeCnsRecv, "" );
}

void CCncConfCtrl::OnCnMicPowerNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg);  	
	m_tTpMicState = *(TTpMicState*)( cTpMsg.GetBody());

	PostEvent( UI_CNC_CNMICPOWER_NTY, (WPARAM)(&m_tTpMicState), 0 );
	PrtMsg( ev_CnMicPower_Nty, emEventTypeCnsRecv, "" );
}

void CCncConfCtrl::OnCnSetMicPowerRsp( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg);  	
	u8 nIndex = *reinterpret_cast<u8*>( cTpMsg.GetBody());
	BOOL bState = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() + sizeof(u8) );
	BOOL bIsOK = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() + sizeof(u8) + sizeof(BOOL) );
	if (!bIsOK)
	{
		bState = !bState;
	}

	PrtMsg( ev_CnSetMicPower_Rsp, emEventTypeCnsRecv, "nIndex:%d, bState:%d, bIsOK:%d", nIndex, bState, bIsOK );
	PostEvent( UI_CNC_CNSETMICPOWER_RSP, nIndex, bState ); 
}

u16 CCncConfCtrl::SetMicStateCmd( u8 nIndex, BOOL bCheck )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_CnSetMicPower_Cmd ); 
	pcTpMsg->SetBody( &nIndex, sizeof(u8) );
	pcTpMsg->CatBody( &bCheck, sizeof(BOOL) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
	PrtMsg( ev_CnSetMicPower_Cmd, emEventTypeCnsSend, "nIndex:%d, bState:%d", nIndex, bCheck );
	return wRet;
} 

// 断链清空数据
void CCncConfCtrl::OnLinkBreak(const CMessage& cMsg)
{ 
	memset( &m_tCnsConfStatus, 0, sizeof(m_tCnsConfStatus) );
	m_bMute = FALSE;
	m_bQuite = FALSE;
	m_bDual = FALSE;
	m_byInputVol = 0;
	m_byOutputVol = 0;
	m_bySpeakSeat = 0;
	m_vctScreenInfo.clear();
	m_bLocalPIP = FALSE;
	m_bPTPSeatArouse = FALSE;
	m_bInAudMix = FALSE;

    m_bRecvDual = FALSE ;
    m_nVideoNode = TP_INVALID_INDEX;
    m_nAudioNode = TP_INVALID_INDEX;

	m_tVideoTranAddr.clear();
	m_tAudioTranAddr.clear();
	m_tTpConfRollCallInfo.Clear();
	m_tTpRollCallPresentStateMsg.Clear();
	m_tTpAudMixInfo.Clear();
	m_tTpAudMixListCmdRes.Clear();

    PrtMsg( OSP_DISCONNECT, emEventTypeCnsRecv,"[CCncConfCtrl::OnLinkBreak]清空会议状态信息" );   
}

//开启画中画
u16 CCncConfCtrl::ViewLocalPIPCmd( const u8 byScrnID, const BOOL bLocalP )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_CnViewLocalPIP_Cmd );
	pcTpMsg->SetBody( &byScrnID, sizeof(u8) ); 
	pcTpMsg->CatBody( &bLocalP, sizeof(BOOL) ); 

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnViewLocalPIP_Cmd, emEventTypeCnsSend, "byScrnID: %d, bViewPIP:%d", byScrnID, bLocalP );
	return wRet;
}

void CCncConfCtrl::OnViewLocalPIPInd( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 
	
    u8 byScrnID = *(u8*)(cTpMsg.GetBody());			//B3版本中只有中间屏开启画中画,屏号为1
	EmTPViewLocalResult emViewRes = *(EmTPViewLocalResult*)( cTpMsg.GetBody() + sizeof(u8) );
    PrtMsg( ev_CnViewLocalPIP_Ind, emEventTypeCnsRecv, "byScrnID:%d, emViewRes:%d( emViewLocalSucceed:%d, \
emViewLocalFailUnKown:%d, emViewLocalFailStatusError:%d, emViewLocalFailOffline:%d, emViewLocalFailIllegalPos:%d )",
byScrnID, emViewRes, emViewLocalSucceed,emViewLocalFailUnKown,emViewLocalFailStatusError,emViewLocalFailOffline,emViewLocalFailIllegalPos );

	PostEvent( UI_CNS_VIEWLOCALPIP_IND, (WPARAM)byScrnID, emViewRes ); 
	
}

BOOL CCncConfCtrl::IsViewLocalPIP() const
{
	return m_bLocalPIP;
}

void CCncConfCtrl::OnViewLocalPIPNty( const CMessage &cMsg )
{
	CTpMsg cTpMsg(&cMsg); 
	
    u8 byScrnID = *(u8*)(cTpMsg.GetBody());			//B3版本中只有中间屏开启画中画,屏号为1
	BOOL bLocalPIP = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );
    PrtMsg( ev_CnViewLocalPIP_Nty, emEventTypeCnsRecv, "byScrnID:%d, bLocalPIP:%d", byScrnID, bLocalPIP );

	if ( m_bLocalPIP != bLocalPIP )
	{
		m_bLocalPIP = bLocalPIP;
		PostEvent( UI_CNS_VIEWLOCALPIP_NTY, (WPARAM)byScrnID, bLocalPIP); 
	}	
}

//选看电视墙
u16 CCncConfCtrl::SelTVSView( u8 byScreenID )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_CnSelTVSView_Cmd );
    pcTpMsg->SetBody( &byScreenID, sizeof(u8) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_CnSelTVSView_Cmd, emEventTypeCnsSend, "screenID: %d", byScreenID );
	return wRet;
}

u16 CCncConfCtrl::CancelSelTVSView( u8 byScreenID )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_CnCancelSelTVSView_Cmd );
    pcTpMsg->SetBody( &byScreenID, sizeof(u8) ); 
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_CnCancelSelTVSView_Cmd, emEventTypeCnsSend, "screenID: %d ", byScreenID );
    return wRet;	
}

void CCncConfCtrl::OnSetSelTVSViewRsp( const CMessage &cMsg )
{	
    CTpMsg cTpMsg(&cMsg);  
    u8 byScreenID = *(u8*)(cTpMsg.GetBody());	
    BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );
    u16 wEvent = cTpMsg.GetEvent();
	
    PrtMsg( wEvent, emEventTypeCnsRecv, "Screen: %d, bSuccess: %d", byScreenID, bSuccess );
	
    //如果当前屏未处于激活状态，则不相应该消息  2011-12-27 by yjj
    //TScreenInfo *tScreen = GetScreenInfoByID( byScreenID );
    //if ( tScreen == NULL /*|| tScreen->emScreenState != emPosAcitve*/ )//emPosAcitve 状态不用了，用EMPosPic消息统一管理  dyy 2013-10-10 
    //{
	//	return;
    //}
	
    if ( wEvent ==  ev_CnCancelSelTVSView_Ind )
    {
        PostEvent( UI_CNS_CANCLE_SEL_TVSVIEW_RSP, byScreenID, bSuccess ); 
    }
    else
    {
        PostEvent( UI_CNS_SEL_TVSVIEW_RSP, byScreenID, bSuccess ); 
    }
}

//空闲时选看双流

u16 CCncConfCtrl::SpareTimeScreenDualSet( u8 wID ,BOOL bIsShow )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_tppSetShowDual_Cmd ); 
	pcTpMsg->SetBody( &wID, sizeof(u8) );
	pcTpMsg->CatBody( &bIsShow, sizeof(BOOL) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
	PrtMsg( ev_tppSetShowDual_Cmd, emEventTypeCnsSend, "ID:%d IsShow：%d", wID, bIsShow );
	return wRet;
}


void CCncConfCtrl::OnSpareDualSetNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	u8 wScreenID = *reinterpret_cast<u8 *>( cTpMsg.GetBody() );
	BOOL bIsShow = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() + sizeof(u8) );

	if ( bIsShow  )
	{
		UpdateScreenInfo( wScreenID, emPosAcitve, emPic_SelDual );
	}
	else
	{
		UpdateScreenInfo( wScreenID, emPosAcitve, emPic_Local );
	}

	PrtMsg( ev_tppSetShowDual_Nty, emEventTypeCnsRecv, _T( "SpareDualNty IsShow:%d ScreenID:%d"),bIsShow, wScreenID );
	PostEvent( UI_CNS_SPAREDUAL_NTY, bIsShow, wScreenID );
}

void CCncConfCtrl::OnSpareDualSetInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	u8 wScreenID = *reinterpret_cast<u8 *>( cTpMsg.GetBody() );
	if (wScreenID > 2)
	{
		return;
	}

	BOOL bIsSuccess = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() + sizeof(u8) );
	EmTpDualIdleReason emTpDualIdleReason = *reinterpret_cast<EmTpDualIdleReason *>( cTpMsg.GetBody() + sizeof(u8) + sizeof(BOOL) );
	if ( bIsSuccess  )
	{
		if (m_vctScreenInfo[wScreenID].emPosPic == emPic_SelDual)
		{
			UpdateScreenInfo( wScreenID, emPosAcitve, emPic_Local );
		}
		else
		{
			UpdateScreenInfo( wScreenID, emPosAcitve, emPic_SelDual );
		}
	}

	PrtMsg( ev_tppSetShowDual_Ind, emEventTypeCnsRecv, _T( "SpareDualInd Success:%d ScreenID:%d emTpDualIdleReason:%d"),bIsSuccess, wScreenID,emTpDualIdleReason );
	PostEvent( UI_CNS_SPAREDUAL_IND, emTpDualIdleReason, wScreenID );

}
//会议控制语音激励
u16 CCncConfCtrl::SetCnAuxMix( BOOL bIsAudMix )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_CnMixIsUsed_Cmd ); 
	pcTpMsg->SetBody( &bIsAudMix, sizeof(BOOL) );

	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG); 
	PrtMsg( ev_CnMixIsUsed_Cmd, emEventTypeCnsSend, "bIsAudMix：%d", bIsAudMix );
	return wRet;
}

void CCncConfCtrl::OnCnAuxMixInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	BOOL bIsMix = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() );
	BOOL bIsSuccess = *reinterpret_cast<BOOL *>( cTpMsg.GetBody() + sizeof(BOOL) );
	if (bIsSuccess)
	{
		m_bPTPSeatArouse = bIsMix;
	}

	PrtMsg( ev_CnMixIsUsed_Ind, emEventTypeCnsRecv, _T( "IsCnMix:%d IsSuccess:%d"),bIsMix, bIsSuccess );
	PostEvent( UI_CNS_CNAUXMIX_IND, bIsMix, bIsSuccess );
}
