#include "StdAfx.h"
#include "cnccenterctrl.h"

CCncCenterCtrl::CCncCenterCtrl(CCnsSession &cSession):CCncCenterCtrlIF()
{
    m_aemComType[0] = emDFScreen;
    m_aemComType[1] = emDCam;

	m_pSession = &cSession;
	BuildEventsMap();
    m_bIsMatrixOnline = FALSE;
}

CCncCenterCtrl::~CCncCenterCtrl()
{

}

void CCncCenterCtrl::BuildEventsMap()
{ 
    REG_PFUN( ev_cns_centreSchStateNty, CCncCenterCtrl::OnSchStateNty );
    REG_PFUN( ev_Cn_Sch_Temp_FB_Notify, CCncCenterCtrl::OnSchTempNty );
    
    REG_PFUN( ev_Cn_Sch_Power_Ind, CCncCenterCtrl::OnSchPowerInd );
    REG_PFUN( ev_Cn_Sch_Power_FB_Notify, CCncCenterCtrl::OnSchPowerNty );
    REG_PFUN( ev_Cn_Sch_Light_Ind, CCncCenterCtrl::OnSchLightInd );
    REG_PFUN( ev_Cn_Sch_Light_FB_Notify, CCncCenterCtrl::OnSchLightNty );
    REG_PFUN( ev_Cn_Sch_MidLight_Ind, CCncCenterCtrl::OnSchMainLightInd );
    REG_PFUN( ev_Cn_Sch_ScrLight_Ind, CCncCenterCtrl::OnSchAuxiLightInd );

    REG_PFUN( ev_cns_centreTVStateNty, CCncCenterCtrl::OnTvStateNty );
	REG_PFUN( ev_Cn_centreTVModleInd, CCncCenterCtrl::OnTvModeNty );
    REG_PFUN( ev_cns_centreselectTV_Ind, CCncCenterCtrl::OnSeleteTvInd );
    REG_PFUN( ev_cns_centreTVMode_Ind, CCncCenterCtrl::OnTvPowerModeInd );
    REG_PFUN( ev_cns_centreTVAudVisMode_Ind, CCncCenterCtrl::OnTvAudVisModeInd );
    REG_PFUN( ev_cns_centreTVDisMode_Ind, CCncCenterCtrl::OnTvDisModeInd );  
    REG_PFUN( ev_cns_centreTVInpSelect_Ind, CCncCenterCtrl::OnTvAudInpSelectInd );  

    REG_PFUN( ev_Cns_DCamCurIdxNty, CCncCenterCtrl::SetDCamSelectIndexNty );
    REG_PFUN( ev_Cns_DCamSelectInd, CCncCenterCtrl::SetDCamSelectIndexInd );
    REG_PFUN( ev_Cn_DCamPower_Ind, CCncCenterCtrl::OnDCamPowerInd );
    REG_PFUN( ev_Cn_DCamAFMode_Ind, CCncCenterCtrl::OnDCamAFModeInd );
    REG_PFUN( ev_Cn_DCamWBMode_Ind, CCncCenterCtrl::OnDCamWBModeInd );
    REG_PFUN( ev_Cn_DCamZoom_Ind, CCncCenterCtrl::OnDCamZoomInd );
    REG_PFUN( ev_Cn_DCamPreset_Ind, CCncCenterCtrl::OnDCamPresetInd );
    REG_PFUN( ev_Cn_DCamRecall_Ind, CCncCenterCtrl::OnDCamRecallInd );
	REG_PFUN( ev_Cn_DocSetTypeInd, CCncCenterCtrl::OnDCamTypeInd );

    REG_PFUN( ev_cns_centreDCamStateNty, CCncCenterCtrl::OnDCamStateNty );

    REG_PFUN( ev_cns_centreACStateNty, CCncCenterCtrl::OnACStateNty );
    REG_PFUN( ev_Cn_CentreSetACTempInd, CCncCenterCtrl::OnACTempInd );
    REG_PFUN( ev_Cn_CentreSetACModeInd, CCncCenterCtrl::OnACModeInd );
    REG_PFUN( ev_Cn_CentreSetAirVolInd, CCncCenterCtrl::OnACAirVolInd );
	REG_PFUN( ev_Cn_CentreSetACPowerInd, CCncCenterCtrl::OnAirPowerInd );
	REG_PFUN( ev_cns_centreSelectAC_Ind, CCncCenterCtrl::OnSeleteAirInd );
	REG_PFUN( ev_cns_centreACCopyInd, CCncCenterCtrl::OnApplyToAllInd);
 
	REG_PFUN( ev_Cn_CamPowerStateNty, CCncCenterCtrl::OnCamStateNty );

	REG_PFUN( ev_CnCfgDisplay_Ind, CCncCenterCtrl::OnDisplayInd );

	//REG_PFUN( ev_Cn_CentreSleepNty, OnCentreSleepNty ); //在cnssession中响应
	REG_PFUN( ev_Cn_centreCurInfoNty, CCncCenterCtrl::OnCurtainStateNty );
	REG_PFUN( ev_Cn_centreCurActInd, CCncCenterCtrl::OnCurtainActInd );
	//辅视频源  如果选了第二个 进行限制
	REG_PFUN( ev_CnMinVedioInfo_Nty, CCncCenterCtrl::OnMinVedioInfo );

    //显示器显示
    REG_PFUN( ev_CnCfgDisplayShow_Nty, CCncCenterCtrl::OnDisplayShowNty );
    REG_PFUN( ev_CnCfgDisplayShow_Ind, CCncCenterCtrl::OnDisplayShowInd );

    //矩阵
    REG_PFUN( ev_CnMatrixConfigInfo_Nty, CCncCenterCtrl::OnMatrixConfigNty );
    REG_PFUN( ev_CnSetMatrixConfig_Ind, CCncCenterCtrl::OnMatrixConfigNty );
    REG_PFUN( ev_CnMatrixOnlineState_Nty, CCncCenterCtrl::OnMatrixOnlineStateNty );
    REG_PFUN( ev_CnMatrixSceneInfo_Nty, CCncCenterCtrl::OnMatrixSceneInfoNty );
    REG_PFUN( ev_CnCurMatrixInfo_Nty, CCncCenterCtrl::OnCurMatrixInfoNty );
    REG_PFUN( ev_CnSaveMatrixScence_Ind, CCncCenterCtrl::OnSaveMatrixSceneInd );
    REG_PFUN( ev_CnRenameMatrixScence_Ind, CCncCenterCtrl::OnReNameMatrixSceneInd );
    REG_PFUN( ev_CnDeleteMatrixScence_Ind, CCncCenterCtrl::OnDeleteMatrixSceneInd );
    REG_PFUN( ev_CnUseMatrixScence_Ind, CCncCenterCtrl::OnApplyMatrixSceneInd );
    REG_PFUN( ev_CnMatrixOutInRelation_Ind, CCncCenterCtrl::OnChangeMatrixOutInRelationInd );
    REG_PFUN( ev_Cn_MatrixInOutRelation_Nty, CCncCenterCtrl::OnMatrixOutInRelationNty );

    //串口
    REG_PFUN( ev_Cn_SelectCom_Nty, CCncCenterCtrl::OnSelectComNty);
    REG_PFUN( ev_Cn_SelectCom_Ind, CCncCenterCtrl::OnSelectComInd);

    //升降屏
    REG_PFUN( ev_Cn_CentreDFScreenConfig_Nty, CCncCenterCtrl::OnCentreDFScreenConfigNty);
    REG_PFUN( ev_cns_SelectDFScreen_Nty, CCncCenterCtrl::OnSelectDFScreenNty);
    REG_PFUN( ev_Cn_ModifyDFScreenGroup_Ind, CCncCenterCtrl::OnCentreModifydDFScreenGroupInd );
    REG_PFUN( ev_Cn_DFScreenCommand_Ind, CCncCenterCtrl::OnCentreDFScreenCommandInd);
    REG_PFUN( ev_cns_SelectDFScreen_Ind, CCncCenterCtrl::OnSelectDFScreenInd );

	//断链通知
	REG_PFUN( OSP_DISCONNECT, CCncCenterCtrl::OnLinkBreak );
}

void CCncCenterCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN(CCncCenterCtrl, cMsg);
}

void CCncCenterCtrl::OnLinkBreak(const CMessage& cMsg)
{
	m_bDisplay = FALSE;
	memset( &m_tDisplayType1, 0, sizeof(m_tDisplayType1) );
	memset( &m_tDisplayType3, 0, sizeof(m_tDisplayType3) );
	memset( m_atbIsCtrl, 0, sizeof(m_atbIsCtrl) );
	memset( &m_tCentreSchCfg, 0, sizeof(m_tCentreSchCfg) );
	//memset( &m_tDCamCfg, 0, sizeof(m_tDCamCfg) );
	memset( &m_tCentreCurInfo, 0, sizeof(m_tCentreCurInfo) );

	memset( m_bIsCtrl, 0, sizeof(m_bIsCtrl) );
	memset( m_atTVCfg, 0, sizeof(m_atTVCfg) );
    memset( &m_tTPMatrixConfig, 0, sizeof(m_tTPMatrixConfig) );
    memset( m_atTPMatrixSceneInfo, 0, sizeof(m_atTPMatrixSceneInfo) );
    memset( &m_tTPCurMatrixInfo, 0, sizeof(m_tTPCurMatrixInfo) );
    m_bIsMatrixOnline = FALSE;
	m_vecTCentreCurName.clear();
	m_vecTCentreACCfg.clear();
    m_mapDCamCfg.clear();

    memset( &m_tCenDownOrFlipScreenInfo, 0, sizeof(m_tCenDownOrFlipScreenInfo) );
    memset( m_abSelectDFScreen, 0, sizeof(m_abSelectDFScreen));
	
    PrtMsg( OSP_DISCONNECT, emEventTypecnstoolRecv,"[CCncCenterCtrl::OnLinkBreak]清空配置信息" );
}

void CCncCenterCtrl::OnTimeOut(u16 wEvent)
{
	
}

//系统电源
u16 CCncCenterCtrl::SetSysPower( EmSchPower emPower )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_Sch_Power_Cmd );
    pcTpMsg->SetBody( &emPower, sizeof(EmSchPower) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_Sch_Power_Cmd, emEventTypeCnsSend, "EmSchPower: %d", emPower );
    
    return wRet;
}

void CCncCenterCtrl::OnSchPowerInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);

    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );

    EmSchPower emPower = *(EmSchPower*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
	if (bOk)
	{
		m_tCentreSchCfg.emSchPower = emPower;
	}
    PrtMsg( ev_Cn_Sch_Power_Ind, emEventTypeCnsRecv, "BOOL: %d, EmSchPower: %d", bOk, emPower );

    PostEvent( UI_CNS_SCHPOWER_IND, bOk, emPower );
}

void CCncCenterCtrl::OnSchPowerNty( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    EmSchPower emPower = *(EmSchPower*)( cTpMsg.GetBody() );
    m_tCentreSchCfg.emSchPower = emPower;

    PrtMsg( ev_Cn_Sch_Power_FB_Notify, emEventTypeCnsRecv, "EmSchPower: %d", emPower );
}



u16 CCncCenterCtrl::SetSysAllLight( EmSchLight emLight )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_Sch_Light_Cmd );
    pcTpMsg->SetBody( &emLight, sizeof(EmSchLight) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_Sch_Light_Cmd, emEventTypeCnsSend, "EmSchLight: %d", emLight );
    
    return wRet;
}

void CCncCenterCtrl::OnSchLightInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmSchLight emLight = *(EmSchLight*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
	if (bOk)
	{
		m_tCentreSchCfg.emSchLight = emLight;
	}
    PrtMsg( ev_Cn_Sch_Light_Ind, emEventTypeCnsRecv, "BOOL: %d, EmSchLight: %d", bOk, emLight );

    PostEvent( UI_CNS_SCHALLLIGHT_IND, bOk, emLight );
}

void CCncCenterCtrl::OnSchLightNty( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    EmSchLight emLight = *(EmSchLight*)( cTpMsg.GetBody() );
    m_tCentreSchCfg.emSchLight = emLight;

    PrtMsg( ev_Cn_Sch_Light_FB_Notify, emEventTypeCnsRecv, "EmSchLight: %d", emLight );

    PostEvent( UI_CNS_SCHLIGHT_NTY, emLight );
}

//fxb去掉 2015-8-20 预留中控其他开关控制 dyy
u16 CCncCenterCtrl::SetMainLight( EmSchMidLight emMidLight )
{
//     CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
//     pcTpMsg->SetUserData( m_pSession->GetInst() );
//     pcTpMsg->SetEvent( ev_Cn_Sch_MidLight_Cmd );
//     pcTpMsg->SetBody( &emMidLight, sizeof(EmSchMidLight) );
//     
//     u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
//    PrtMsg( ev_Cn_Sch_MidLight_Cmd, emEventTypeCnsSend, "EmSchMidLight: %d", emMidLight );
    
    return true;
}

void CCncCenterCtrl::OnSchMainLightInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmSchMidLight emLight = *(EmSchMidLight*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
	if (bOk)
	{
		m_tCentreSchCfg.emSchMidLight = emLight;
	}
    PrtMsg( ev_Cn_Sch_MidLight_Ind, emEventTypeCnsRecv, "BOOL: %d, EmSchMidLight: %d", bOk, emLight );

    PostEvent( UI_CNS_SCHMIDLIGHT_IND, bOk, emLight );
}

//用于补光灯 2015-8-19 
u16 CCncCenterCtrl::SetAuxiLight( EmSchScrLight emScrLight )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_Sch_ScrLight_Cmd );
    pcTpMsg->SetBody( &emScrLight, sizeof(EmSchScrLight) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_Sch_ScrLight_Cmd, emEventTypeCnsSend, "EmSchScrLight: %d", emScrLight );
    
    return wRet;
}

void CCncCenterCtrl::OnSchAuxiLightInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmSchScrLight emLight = *(EmSchScrLight*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
	if (bOk)
	{
		m_tCentreSchCfg.emSchScrLight = emLight;
	}
    PrtMsg( ev_Cn_Sch_ScrLight_Ind, emEventTypeCnsRecv, "BOOL: %d, EmSchScrLight: %d", bOk, emLight );

    PostEvent( UI_CNS_SCHSCRLIGHT_IND, bOk, emLight );
}

void CCncCenterCtrl::OnSchTempNty( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    u16 wTemp = *(u16*)( cTpMsg.GetBody() );
    m_tCentreSchCfg.wSchTem = wTemp;
    PrtMsg( ev_Cn_Sch_Temp_FB_Notify, emEventTypeCnsRecv, "Temp: %d", wTemp );

    PostEvent( UI_CNS_SCHTEMP_NTY, wTemp );
}

void CCncCenterCtrl::OnSchStateNty( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    
    m_tCentreSchCfg = *(TCentreSchCfg*)( cTpMsg.GetBody() );
    
    PrtMsg( ev_cns_centreSchStateNty, emEventTypeCnsRecv, "EmSchPower: %d, EmSchLight: %d, EmSchMidLight: %d, EmSchScrLight: %d, Temp: %d",
        m_tCentreSchCfg.emSchPower, m_tCentreSchCfg.emSchLight, m_tCentreSchCfg.emSchMidLight, m_tCentreSchCfg.emSchScrLight, m_tCentreSchCfg.wSchTem );

    PostEvent( UI_CNS_SCHSTATE_NTY, NULL, NULL );
}

void CCncCenterCtrl::GetCentreSchCfg( TCentreSchCfg &tCentreSchCfg ) const
{
	tCentreSchCfg = m_tCentreSchCfg;
}

//电视机
u16 CCncCenterCtrl::SelectTV( u8 byIndex )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_cns_centreselectTV_cmd );
    pcTpMsg->SetBody( &byIndex, sizeof(u8) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_cns_centreselectTV_cmd, emEventTypeCnsSend, "Index: %d", byIndex );
    
	return wRet;
}

u16 CCncCenterCtrl::SetTVPowerMode( u8 byIndex, EmTvPowerMode emMode )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_cns_centreTVMode_cmd );  
    pcTpMsg->SetBody( &emMode, sizeof(EmTvPowerMode) );
    pcTpMsg->CatBody( &byIndex, sizeof(u8) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_cns_centreTVMode_cmd, emEventTypeCnsSend, "Index: %d, EmTvPowerMode: %d", byIndex, emMode );
    
	return wRet;
}

u16 CCncCenterCtrl::SetTVAudVisMode( EmTVAudVisMode emMode )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_cns_centreTVAudVisMode_cmd );
    pcTpMsg->SetBody( &emMode, sizeof(EmTVAudVisMode) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_cns_centreTVAudVisMode_cmd, emEventTypeCnsSend, "EmAudVisMode: %d", emMode );
    
    return wRet;
}

u16 CCncCenterCtrl::SetTVDisMode( EmTVDisplayMode emMode )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_cns_centreTVDisMode_cmd );
    pcTpMsg->SetBody( &emMode, sizeof(EmTVDisplayMode) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_cns_centreTVDisMode_cmd, emEventTypeCnsSend, "EmDisplayMode: %d", emMode );
    
    return wRet;
}

u16 CCncCenterCtrl::SetTVInpSelect( u8 byIndex,  EmTVInputSelect emSelect )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_cns_centreTVInpSelect_cmd );
    pcTpMsg->SetBody( &byIndex, sizeof(u8) );
	pcTpMsg->CatBody( &emSelect, sizeof(EmTVInputSelect) );
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_cns_centreTVInpSelect_cmd, emEventTypeCnsSend,  "Index: %d, EmInputSelect: %d", byIndex, emSelect );
    
    return wRet;
}

void CCncCenterCtrl::OnTvStateNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    TCentreTVCfg *ptCentreTVCfg = reinterpret_cast<TCentreTVCfg *>(cTpMsg.GetBody());

    memcpy( m_atTVCfg, ptCentreTVCfg, sizeof(TCentreTVCfg)*MAX_CENTRETV_NUM );
    
    PrtMsg( ev_cns_centreTVStateNty, emEventTypeCnsRecv, "TvPowerMode1: %d, TvPowerMode2: %d, TvPowerMode3: %d",
        m_atTVCfg[0].emTvPowerMode, m_atTVCfg[1].emTvPowerMode, m_atTVCfg[2].emTvPowerMode );

    PostEvent( UI_CNS_TVSTATE_NTY );
}

void CCncCenterCtrl::OnTvModeNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	EmTVModle emTVModle = *(EmTVModle*)( cTpMsg.GetBody() );
	BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmTVModle) );

	PrtMsg( ev_Cn_centreTVModleInd, emEventTypeCnsRecv, "EmTVModle: %d, BOOL: %d", emTVModle, bOk );
	if (bOk == TRUE)
	{
		m_atTVCfg->emTvModle = emTVModle;
		PostEvent( UI_CNS_TVSTATE_NTY );
	}
	
}

TCentreTVCfg* CCncCenterCtrl::GetCentreTVCfg()
{
    return m_atTVCfg;
}


void CCncCenterCtrl::OnSeleteTvInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    u8 byIndex = *(u8*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );

    PrtMsg( ev_cns_centreselectTV_Ind, emEventTypeCnsRecv, "Index: %d, bOk: %d", byIndex, bOk );
	PostEvent( UI_CNS_SELETETV_IND, byIndex, bOk);
}

void CCncCenterCtrl::OnTvPowerModeInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    EmTvPowerMode emMode = *(EmTvPowerMode*)( cTpMsg.GetBody() );
    u8 byIndex = *(u8*)( cTpMsg.GetBody() + sizeof(EmTvPowerMode) );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmTvPowerMode) + sizeof(u8) );
    
    PrtMsg( ev_cns_centreTVMode_Ind, emEventTypeCnsRecv, "EmTvPowerMode: %d, Index: %d, bOK: %d", emMode, byIndex, bOk );

    if ( !bOk )
    {
        PostEvent( UI_CNS_TVPOWERMODE_IND, byIndex, emMode );
    }   
}

void CCncCenterCtrl::OnTvAudVisModeInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    EmTVAudVisMode emMode = *(EmTVAudVisMode*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmTVAudVisMode) );
    
    PrtMsg( ev_cns_centreTVAudVisMode_Ind, emEventTypeCnsRecv, "EmTVAudVisMode: %d, bOK: %d", emMode, bOk );
}

void CCncCenterCtrl::OnTvDisModeInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    EmTVDisplayMode emMode = *(EmTVDisplayMode*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmTVDisplayMode) );
    
    PrtMsg( ev_cns_centreTVDisMode_Ind, emEventTypeCnsRecv, "EmTVDisplayMode: %d, bOK: %d", emMode, bOk );
}

void CCncCenterCtrl::OnTvAudInpSelectInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
	u8 byIndex = *(u8*)( cTpMsg.GetBody() );
    EmTVInputSelect emMode = *(EmTVInputSelect*)( cTpMsg.GetBody() + sizeof(u8) );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmTVInputSelect) + sizeof(u8) );
    
    PrtMsg( ev_cns_centreTVInpSelect_Ind, emEventTypeCnsRecv, "Index: %d, EmTVInputSelect: %d, bOK: %d", byIndex, emMode, bOk );
}


//文档摄像机
u16 CCncCenterCtrl::SetDCamPower( EmDCamPower emPower )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamPower_Cmd );
    pcTpMsg->SetBody( &emPower, sizeof(EmDCamPower) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_DCamPower_Cmd, emEventTypeCnsSend, "EmDCamPower: %d", emPower );

    return wRet;
}

//文档摄像机切换
u16 CCncCenterCtrl::SetDCamSelectIndex( u8 byIndex )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cns_DCamSelectCmd );
    pcTpMsg->SetBody( &byIndex, sizeof(u8) );

    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

    PrtMsg( ev_Cns_DCamSelectCmd, emEventTypeCnsSend, "byIndex: %d", byIndex );

    return wRet;
}

//自动焦距
u16 CCncCenterCtrl::SetDCamAFMode( EmDCamAFMode emMode )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamAFMode_Cmd );
    pcTpMsg->SetBody( &emMode, sizeof(EmDCamAFMode) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_DCamAFMode_Cmd, emEventTypeCnsSend, "EmDCamAFMode: %d", emMode );
    
    return wRet;
}

//白平衡模式
u16 CCncCenterCtrl::SetDCamWBMode( EmDCamWBMode emMode )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamWBMode_Cmd );
    pcTpMsg->SetBody( &emMode, sizeof(EmDCamWBMode) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_DCamWBMode_Cmd, emEventTypeCnsSend, "EmDCamWBMode: %d", emMode );
    
    return wRet;
}

//视野调节
u16 CCncCenterCtrl::SetDCamZoom( EmDCamZoom emZoom, EmCnAction emAction )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamZoom_Cmd );
    pcTpMsg->SetBody( &emAction, sizeof(EmCnAction) );
    pcTpMsg->CatBody( &emZoom, sizeof(EmDCamZoom) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);

    PrtMsg( ev_Cn_DCamZoom_Cmd, emEventTypeCnsSend,"EmCnAction: %d,EmZoom: %d",emAction, emZoom );
    
    return wRet;
}

//预置位
u16 CCncCenterCtrl::SetDCamPreset( EmDCamPresetNum emNum )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamPreset_Cmd );
    pcTpMsg->SetBody( &emNum, sizeof(EmDCamPresetNum) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_DCamPreset_Cmd, emEventTypeCnsSend, "EmDCamPresetNum: %d", emNum  );
    
    return wRet;
}

u16 CCncCenterCtrl::SetDCamRecall( EmDCamRecallNum emNum )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_DCamRecall_Cmd );
    pcTpMsg->SetBody( &emNum, sizeof(EmDCamRecallNum) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_DCamRecall_Cmd, emEventTypeCnsSend, "EmDCamPresetNum: %d", emNum  );
    
    return wRet;
}

void CCncCenterCtrl::SetDCamSelectIndexNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    u8 byIndex = *(u8*)(cTpMsg.GetBody());

    PrtMsg( ev_Cns_DCamCurIdxNty, emEventTypeCnsRecv, "byIndex : %d", byIndex );

    PostEvent( UI_CNS_DCAMSELECTED_IND, 1, byIndex );
}

void CCncCenterCtrl::SetDCamSelectIndexInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    u8 byIndex = *(u8*)(cTpMsg.GetBody());
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );

    PrtMsg( ev_Cns_DCamSelectInd, emEventTypeCnsRecv, "byIndex : %d, bOk: %d", byIndex, bOk );

    PostEvent( UI_CNS_DCAMSELECTED_IND, bOk, byIndex );
}

void CCncCenterCtrl::OnDCamPowerInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmDCamPower emPower = *(EmDCamPower*)( cTpMsg.GetBody() + sizeof(BOOL) );
    u8 byIndex = *(u8*)(cTpMsg.GetBody() + sizeof(BOOL) + sizeof(EmDCamPower));
    if (bOk && m_mapDCamCfg.find(byIndex) != m_mapDCamCfg.end())
    {
        m_mapDCamCfg[byIndex].emDCamPowerMode = emPower;
    }

    PrtMsg( ev_Cn_DCamPower_Ind, emEventTypeCnsRecv, "byIndex : %d, bOk: %d, EmDCamPower: %d", byIndex, bOk, emPower );

    PostEvent( UI_CNS_DCAMPOWER_IND, bOk, byIndex );
}

void CCncCenterCtrl::OnDCamAFModeInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmDCamAFMode emMode = *(EmDCamAFMode*)( cTpMsg.GetBody() + sizeof(BOOL) );   
    u8 byIndex = *(u8*)(cTpMsg.GetBody() + sizeof(BOOL) + sizeof(EmDCamAFMode));
    if (bOk && m_mapDCamCfg.find(byIndex) != m_mapDCamCfg.end())
    {
        m_mapDCamCfg[byIndex].tDCamCurPresetInfo.emDCamAFMode = emMode;
    }

    PrtMsg( ev_Cn_DCamAFMode_Ind, emEventTypeCnsRecv, "byIndex : %d, bOk: %d, EmDCamAFMode: %d", byIndex, bOk, emMode );
}

void CCncCenterCtrl::OnDCamWBModeInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmDCamWBMode emMode = *(EmDCamWBMode*)( cTpMsg.GetBody() + sizeof(BOOL) );
    u8 byIndex = *(u8*)(cTpMsg.GetBody() + sizeof(BOOL) + sizeof(EmDCamWBMode));
    if (bOk && m_mapDCamCfg.find(byIndex) != m_mapDCamCfg.end())
    {
        m_mapDCamCfg[byIndex].tDCamCurPresetInfo.emDCamWBMode = emMode;
    }
    PrtMsg( ev_Cn_DCamWBMode_Ind, emEventTypeCnsRecv, "byIndex : %d, bOk: %d, EmDCamWBMode: %d", byIndex, bOk, emMode );
}

void CCncCenterCtrl::OnDCamZoomInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmDCamZoom emZoom = *(EmDCamZoom*)( cTpMsg.GetBody() + sizeof(BOOL) );
    
    PrtMsg( ev_Cn_DCamZoom_Ind, emEventTypeCnsRecv, "bOk: %d, EmDCamZoom: %d", bOk, emZoom );
	PostEvent( UI_CNS_DCAMZOOM_IND, bOk, emZoom );
}

void CCncCenterCtrl::OnDCamPresetInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmDCamPresetNum emNum = *(EmDCamPresetNum*)( cTpMsg.GetBody() + sizeof(BOOL) );

    PrtMsg( ev_Cn_DCamPreset_Ind, emEventTypeCnsRecv, "bOk: %d, EmDCamPresetNum: %d", bOk, emNum );
}

void CCncCenterCtrl::OnDCamRecallInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() );
    EmDCamRecallNum emNum = *(EmDCamRecallNum*)( cTpMsg.GetBody() + sizeof(BOOL) );
    u8 byIndex = *(u8*)(cTpMsg.GetBody() + sizeof(BOOL) + sizeof(EmDCamRecallNum));
    if (bOk && m_mapDCamCfg.find(byIndex) != m_mapDCamCfg.end())
    {
        m_mapDCamCfg[byIndex].emDCamRecallNum = emNum;
    }

    PrtMsg( ev_Cn_DCamRecall_Ind, emEventTypeCnsRecv, "bOk: %d, EmDCamRecallNum: %d", bOk, emNum );
	PostEvent( UI_CNS_DCAMPREPOS_IND, bOk, emNum );
}

void CCncCenterCtrl::OnDCamTypeInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	EmDCamProType emDcCamType = *(EmDCamProType*)( cTpMsg.GetBody());
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() +sizeof(EmDCamProType) );
    u8 byIndex = *(u8*)( cTpMsg.GetBody() +sizeof(emDcCamType) +sizeof(BOOL) );

    map<u8, TCentreDCamCfg>::iterator itDcamMap = m_mapDCamCfg.find(byIndex); 
    if (bSuccess && itDcamMap != m_mapDCamCfg.end())
    {
        itDcamMap->second.emDcamProType = emDcCamType;
    }

	PrtMsg( ev_Cn_DocSetTypeInd, emEventTypecnstoolRecv,"DC Camera Type :%d< Invalid %d , PRS200 %d , IPC822 %d >  Success: %d", 
		emDcCamType,emDcamInvalid,emVISCAPro,emPELCOPro ,bSuccess);

	PostEvent( UI_CNS_DCAMTYPE_IND,(WPARAM)&emDcCamType,(LPARAM)&bSuccess);
}

void CCncCenterCtrl::OnDCamStateNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    TCentreDCamCfg tDCamCfg = *(TCentreDCamCfg*)( cTpMsg.GetBody() );
    u8 byIndex = *(u8*)( cTpMsg.GetBody() +sizeof(TCentreDCamCfg) );

    map<u8, TCentreDCamCfg>::iterator itDcamMap = m_mapDCamCfg.find(byIndex); 
    if (itDcamMap != m_mapDCamCfg.end())
    {
        m_mapDCamCfg[byIndex] = tDCamCfg;
    }
    else
    {
        m_mapDCamCfg.insert(pair<u8, TCentreDCamCfg>( byIndex, tDCamCfg));
    }

    PrtMsg( ev_cns_centreDCamStateNty, emEventTypeCnsRecv, "ByIndex : %d, bDCamUsed : %d, EmDCamPower: %d, EmDCamRecallNum: %d bDCamUsed:%d",
        byIndex, tDCamCfg.bDCamUsed, tDCamCfg.emDCamPowerMode, tDCamCfg.emDCamRecallNum, tDCamCfg.bDCamUsed);

    PostEvent( UI_CNS_DCAMSTATE_NTY );
}

void CCncCenterCtrl::GetDCamStateMap( map<u8, TCentreDCamCfg> &mapDCamCfg ) const
{
    mapDCamCfg = m_mapDCamCfg;
}

void CCncCenterCtrl::GetDCamState( TCentreDCamCfg &tCentreDCamCfg, u8 byIndex ) const
{
    map<u8, TCentreDCamCfg>::const_iterator itDcamMap = m_mapDCamCfg.find(byIndex);
    if (itDcamMap != m_mapDCamCfg.end())
    {
        tCentreDCamCfg = itDcamMap->second;
    }
}

//显示器显示
void CCncCenterCtrl::OnDisplayShowNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    BOOL bIsShow  = *(bool*)( cTpMsg.GetBody() );

    PrtMsg( ev_CnCfgDisplayShow_Nty, emEventTypeCnsRecv, "IsShow: %d", bIsShow );

    PostEvent( UI_CNDISPLAYSHOW, (WPARAM)bIsShow , 0 );
}

void CCncCenterCtrl::OnDisplayShowInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    BOOL bIsShow  = *(bool*)( cTpMsg.GetBody() );
    BOOL bIsSuccess  = *(bool*)( cTpMsg.GetBody() + sizeof(BOOL) );

    PrtMsg( ev_CnCfgDisplayShow_Ind, emEventTypeCnsRecv, "IsShow: %d, IsSuccess: %d ", bIsShow, bIsSuccess );

    if (!bIsSuccess)
    {
        bIsShow = !bIsShow;
    }

    PostEvent( UI_CNDISPLAYSHOW, (WPARAM)bIsShow , 0 );
}

//空调
u16 CCncCenterCtrl::SetACTemp( u8 byTemp )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_CentreSetACTempCmd );
    pcTpMsg->SetBody( &byTemp, sizeof(u8) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_CentreSetACTempCmd, emEventTypeCnsSend, "Temp: %d", byTemp  );
    
    return wRet;
}

void CCncCenterCtrl::OnACTempInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    u8 byTemp = *(u8*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );
    
    PrtMsg( ev_Cn_CentreSetACTempInd, emEventTypeCnsRecv, "Temp: %d, bOk: %d", byTemp, bOk );
}

u16 CCncCenterCtrl::SetACMode( EmCentreACMode emMode )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_CentreSetACModeCmd );
    pcTpMsg->SetBody( &emMode, sizeof(EmCentreACMode) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_CentreSetACModeCmd, emEventTypeCnsSend, "EmCentreACMode: %d", emMode  );
    
    return wRet;
}

void CCncCenterCtrl::OnACModeInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    EmCentreACMode emMode = *(EmCentreACMode*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmCentreACMode) );
    
    PrtMsg( ev_Cn_CentreSetACModeInd, emEventTypeCnsRecv, "EmCentreACMode: %d, bOk: %d", emMode, bOk );
}

u16 CCncCenterCtrl::SetACAirVol( EmCentreACAirVol emAirVol )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_CentreSetACAirVolCmd );
    pcTpMsg->SetBody( &emAirVol, sizeof(EmCentreACAirVol) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_CentreSetACAirVolCmd, emEventTypeCnsSend, "EmCentreACAirVol: %d", emAirVol );
    
    return wRet;
}

void CCncCenterCtrl::OnACAirVolInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    EmCentreACAirVol emAirVol = *(EmCentreACAirVol*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmCentreACAirVol) );
    
    PrtMsg( ev_Cn_CentreSetAirVolInd, emEventTypeCnsRecv, "EmCentreACAirVol: %d, bOk: %d", emAirVol, bOk );
}


// void CCncCenterCtrl::OnACStateNty(const CMessage& cMsg)
// {
//     CTpMsg cTpMsg(&cMsg);
//     
//     TCentreACCfg tACCfg = *(TCentreACCfg*)( cTpMsg.GetBody() );
//     
//     PrtMsg( ev_cns_centreACStateNty, emEventTypeCnsRecv, "ACPower:%d, EmCentreACMode: %d, SetTemp: %d, CurTemp: %d, AirVol: %d",
//         tACCfg.emACPower ,tACCfg.emACMode, tACCfg.bySetTemp, tACCfg.byCurTemp, tACCfg.emACAirVol );
//     
//     PostEvent( UI_CNS_ACSTATE_NTY, (WPARAM)&tACCfg );
// }

//空调界面电源开关控制 by wqq
// u16 CCncCenterCtrl::SetAirPower( EmCentreACPower emPower )
// {
//     CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
//     pcTpMsg->SetUserData( m_pSession->GetInst() );
//     pcTpMsg->SetEvent( ev_Cn_CentreSetACPowerCmd );
//     pcTpMsg->SetBody( &emPower, sizeof( EmCentreACPower ) );
//     
//     u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
//     
//     PrtMsg( ev_Cn_CentreSetACPowerCmd, emEventTypeCnsSend, "EmCentreACPower: %d", emPower );
// 	
//     return wRet;
// }

u16 CCncCenterCtrl::SelectAir( u8 byIndex )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_cns_centreSelectAC_Cmd );
    pcTpMsg->SetBody( &byIndex, sizeof(u8) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_cns_centreSelectAC_Cmd, emEventTypeCnsSend, "Index: %d", byIndex );
    
	return wRet;
}

//选择空调项回复消息
void CCncCenterCtrl::OnSeleteAirInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
	
    u8 byIndex = *(u8*)( cTpMsg.GetBody() );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() + sizeof(u8) );
	
    PrtMsg( ev_cns_centreSelectAC_Ind, emEventTypeCnsRecv, "Index: %d, bOk: %d", byIndex, bOk );

	PostEvent( UI_CNS_SELECTAIR_IND, byIndex, bOk );
}

void CCncCenterCtrl::OnACStateNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
	
	TCentreACInfo tCentreACInfo = *reinterpret_cast<TCentreACInfo *>(cTpMsg.GetBody());
	m_vecTCentreACCfg.clear();
	for ( int i = 0; i < MAX_AC_NUM; i++ )
	{
		TCentreACCfg tCentreACCfg = tCentreACInfo.tCentreACCfg[i];//*reinterpret_cast<TCentreACCfg *>(cTpMsg.GetBody() + sizeof(TCentreACCfg)*i);
		
		BOOL bIsExist = tCentreACInfo.bACFlag[i];//*(BOOL *)(cTpMsg.GetBody() + sizeof(TCentreACCfg)*MAX_AC_NUM + sizeof(BOOL)*i);
		
		
		if ( bIsExist == TRUE)
		{
			m_vecTCentreACCfg.push_back( tCentreACCfg );
		}
	}
    
    PrtMsg( ev_cns_centreACStateNty, emEventTypeCnsRecv, "tCentreACInfo.byACNum=%d", tCentreACInfo.byACNum );
	
	PostEvent( UI_CNS_ACSTATE_NTY, tCentreACInfo.byACNum, NULL );
}

void CCncCenterCtrl::GetCentreACCfg( vector<TCentreACCfg> &vecTCentreACCfg )const
{
     vecTCentreACCfg = m_vecTCentreACCfg;
	 return;
}

u16 CCncCenterCtrl::SetACPowerMode( u8 byIndex, EmCentreACPower emMode )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_Cn_CentreSetACPowerCmd );  
	pcTpMsg->SetBody( &byIndex, sizeof(u8) );
    pcTpMsg->CatBody( &emMode, sizeof(EmCentreACPower) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_Cn_CentreSetACPowerCmd, emEventTypeCnsSend, "Index: %d, EmCentreACPower: %d", byIndex, emMode );
    
	return wRet;
}

void CCncCenterCtrl::OnAirPowerInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
	u8 byIndex = *(u8*)( cTpMsg.GetBody() );
	EmCentreACPower emPower = *(EmCentreACPower*)( cTpMsg.GetBody() + sizeof( u8 ) );
    BOOL bOk = *(BOOL*)( cTpMsg.GetBody() +sizeof(u8) +sizeof( EmCentreACPower ) );
	
    PrtMsg( ev_Cn_CentreSetACPowerInd, emEventTypeCnsRecv, "Index: %d, EmCentreACPower: %d, bOk: %d", byIndex, emPower, bOk );
	
	if (!bOk)//失败发
	{
		PostEvent( UI_CNS_ACPOWERSTATE_IND, emPower, byIndex );
	}
    
}

u16 CCncCenterCtrl::SetApplyToAll( u8 byIndex, BOOL** atbIsCtrl )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr(); 
	pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_cns_centreACCopyCmd ); 
	pcTpMsg->SetBody( &byIndex, sizeof(u8) );
	pcTpMsg->CatBody( *atbIsCtrl, sizeof(BOOL) );
	pcTpMsg->CatBody( (*atbIsCtrl)+1, sizeof(BOOL) );
	pcTpMsg->CatBody( (*atbIsCtrl)+2, sizeof(BOOL) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_cns_centreACCopyCmd, emEventTypeCnsSend,"Index: %d, SetApplyToAll", byIndex );
	return wRet;
}

void CCncCenterCtrl::OnApplyToAllInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	for ( int i = 0; i < MAX_AC_NUM; i++ )
	{
		BOOL bIsInCtrl = *(BOOL*)( cTpMsg.GetBody()+sizeof(BOOL)*i );
		m_atbIsCtrl[i] = bIsInCtrl;
		BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody()+3*sizeof(BOOL)+sizeof(BOOL)*i );
	}
	PrtMsg( ev_cns_centreACCopyInd, emEventTypeCnsRecv,"OnApplyToAllInd" );

//	PostEvent( UI_CNS_APPLYTOALL_IND );
}

BOOL* CCncCenterCtrl::GetApplyToAllInfo()
{
	return m_atbIsCtrl;
}

//摄像机
void CCncCenterCtrl::OnCamStateNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	EmCamPowerMode aemCam[MAX_CNCAMERA_NUM];
	for ( int i=0; i<MAX_CNCAMERA_NUM; i++ )
	{
		aemCam[i] = *(EmCamPowerMode*)( cTpMsg.GetBody() + i*sizeof(EmCamPowerMode) );
	}
     
    PrtMsg( ev_Cn_CamPowerStateNty, emEventTypeCnsRecv, "Cam1: %d, Cam2: %d, Cam3: %d", aemCam[0], aemCam[1], aemCam[2] );
	
    PostEvent( UI_CNSTOOL_MSG_CamPowerState_NTY, (WPARAM)aemCam );
}


void CCncCenterCtrl::OnCentreSleepNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    PrtMsg( ev_Cn_CentreSleepNty, emEventTypeCnsRecv, "" );
    
    PostEvent( UI_TPAD_CENTRESLEEP_NTY );
}

//中控电视墙
u16 CCncCenterCtrl::SetDisplayCmd( BOOL bDisplay, const TTPDisplayType& tDisplayType1, const TTPDisplayType& tDisplayType3 )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();  
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_CnCfgDisplay_Cmd );  
	pcTpMsg->SetBody( &bDisplay, sizeof(BOOL) );
    pcTpMsg->CatBody( &tDisplayType1, sizeof(TTPDisplayType) );
    pcTpMsg->CatBody( &tDisplayType3, sizeof(TTPDisplayType) );
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    
    PrtMsg( ev_CnCfgDisplay_Cmd, emEventTypeCnsSend, "bDisplay: %d, tDisplayType1: %d,%d, tDisplayType3: %d,%d \
<emTVHDMI1:%d,emTVHDMI2:%d,emTVHDMI3:%d,emTVHDMI4:%d,emTVYpbPr:%d,emTVCVBS1:%d,emTVCVBS2:%d,emTVComputer:%d>", 
bDisplay, tDisplayType1.emTPT300Type, tDisplayType1.emTPHduType, tDisplayType3.emTPT300Type, tDisplayType3.emTPHduType, \
emTVHDMI1, emTVHDMI2, emTVHDMI3, emTVHDMI4, emTVYpbPr, emTVCVBS1, emTVCVBS2, emTVComputer );
    
	return wRet;
}

const BOOL& CCncCenterCtrl::GetDisplayState() const
{
	return m_bDisplay;
}

const TTPDisplayType& CCncCenterCtrl::GetDisplayType1() const
{
	return m_tDisplayType1;
}

const TTPDisplayType& CCncCenterCtrl::GetDisplayType3() const
{
	return m_tDisplayType3;
}

void CCncCenterCtrl::OnDisplayInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	m_bDisplay = *(BOOL*)cTpMsg.GetBody();
	m_tDisplayType1 = *(TTPDisplayType*)( cTpMsg.GetBody() + sizeof(BOOL) );
	m_tDisplayType3 = *(TTPDisplayType*)( cTpMsg.GetBody() + sizeof(TTPDisplayType) + sizeof(BOOL) );
	BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPDisplayType)*2 + sizeof(BOOL) );

    PrtMsg( ev_CnCfgDisplay_Ind, emEventTypeCnsRecv, "bDisplay: %d, tDisplayType1: %d,%d, tDisplayType3: %d,%d \
<emTVHDMI1:%d,emTVHDMI2:%d,emTVHDMI3:%d,emTVHDMI4:%d,emTVYpbPr:%d,emTVCVBS1:%d,emTVCVBS2:%d,emTVComputer:%d>", 
m_bDisplay, m_tDisplayType1.emTPT300Type, m_tDisplayType1.emTPHduType, m_tDisplayType3.emTPT300Type, m_tDisplayType3.emTPHduType, \
emTVHDMI1, emTVHDMI2, emTVHDMI3, emTVHDMI4, emTVYpbPr, emTVCVBS1, emTVCVBS2, emTVComputer );
	
    PostEvent( UI_CNSTOOL_MSG_DISPLAY_IND, bSuccess, 0 );
}

//577 3/10
void CCncCenterCtrl::GetCentreCurName( vector<TCentreCurName> &vecTCentreCurName ) const
{
	vecTCentreCurName = m_vecTCentreCurName;
}

void CCncCenterCtrl::OnCurtainStateNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);

	m_vecTCentreCurName.clear();
	m_tCentreCurInfo = *(TCentreCurInfo*)(cTpMsg.GetBody());
// 	for ( int i=0; i < m_tCentreCurInfo.byCurNum; i++ )   //B4消息不用数组了 暂时保存
// 	{
// 		m_vecTCentreCurName.push_back( tCentreCurInfo.tCenCurName[i] );
// 		PrtMsg( ev_Cn_centreCurInfoNty, emEventTypeCnsRecv, "%s ",tCentreCurInfo.tCenCurName[i] );
// 	}

	PrtMsg( ev_Cn_centreCurInfoNty, emEventTypeCnsRecv, "\n CurtainNum: %d  bOpen：%d", m_tCentreCurInfo.byCurNum, m_tCentreCurInfo.bCurOpen );

	PostEvent( UI_TPAD_CURTAINSTATE_NTY );
}


void CCncCenterCtrl::GetCentreCurInfor( TCentreCurInfo &tCentreCurInfo ) const
{
	tCentreCurInfo = m_tCentreCurInfo;
}

u16 CCncCenterCtrl::SetCurtainState( BOOL** bIsCtrl, EmCurAction emCurAction )
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr(); 
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	
	pcTpMsg->SetEvent( ev_Cn_centreCurActCmd ); 
	pcTpMsg->SetBody( *bIsCtrl, sizeof(BOOL) );
	pcTpMsg->CatBody( (*bIsCtrl)+1, sizeof(BOOL) );
	pcTpMsg->CatBody( (*bIsCtrl)+2, sizeof(BOOL) );
	pcTpMsg->CatBody( (*bIsCtrl)+3, sizeof(BOOL) );
	pcTpMsg->CatBody( (*bIsCtrl)+4, sizeof(BOOL) );
	pcTpMsg->CatBody( (*bIsCtrl)+5, sizeof(BOOL) );
	pcTpMsg->CatBody( &emCurAction, sizeof(EmCurAction));
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_centreCurActCmd, emEventTypeCnsSend,"SetCurtainState:%d",emCurAction );
	return wRet;
}

void CCncCenterCtrl::OnCurtainActInd(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	for ( int i = 0; i < MAX_CURTAIN_NUM; i++ )
	{
		BOOL bIsCtrl = *(BOOL*)( cTpMsg.GetBody()+sizeof(BOOL)*i );
		m_bIsCtrl[i] = bIsCtrl;
		EmCurAction emCurAction = *(EmCurAction*)( cTpMsg.GetBody() + 6*sizeof(BOOL) );
		BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody()+6*sizeof(BOOL)+sizeof(EmCurAction)+sizeof(BOOL)*i );
	}
	PrtMsg( ev_Cn_centreCurActInd, emEventTypeCnsRecv,"IsCtrl1: %d, IsCtrl2: %d, IsCtrl3: %d, IsCtrl4: %d, IsCtrl5: %d, IsCtrl6: %d", m_bIsCtrl[0], m_bIsCtrl[1], m_bIsCtrl[2], m_bIsCtrl[3], m_bIsCtrl[4], m_bIsCtrl[5] );
}

//文档摄像机快照
u16 CCncCenterCtrl::SetDocSnapShot()
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr(); 
	pcTpMsg->SetUserData( m_pSession->GetInst() );

	pcTpMsg->SetEvent( ev_Cn_DocSetSnapShotCmd ); 
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_Cn_DocSetSnapShotCmd, emEventTypeCnsSend,"SetDocSetSnapShotCmd");
	return wRet;
}

//废弃  范小波确认 ev_tppSetSnapShotInd代替 2015-6-1
void CCncCenterCtrl::OnDocSetSnapShotInd( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	BOOL bSuccess = *(BOOL*)cTpMsg.GetBody();
	PrtMsg( ev_Cn_DocSetSnapShotInd, emEventTypeCnsRecv, "DocSetSnapShot bSuccess: %d", bSuccess );

	PostEvent( UI_CNS_DOCSNAPSHOT_IND, bSuccess, 0 );
}

void CCncCenterCtrl::OnMinVedioInfo( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	u8 byId = *(u8*)cTpMsg.GetBody();
	EmTPMtVideoPort em = *(EmTPMtVideoPort*)( cTpMsg.GetBody() + sizeof(u8) );

	PrtMsg( ev_CnMinVedioInfo_Nty, emEventTypeCnsRecv, "byId: %d em:%d", byId, em );
	if (byId != 1)
	{
		return;
	}

	PostEvent( UI_CNS_MINVEDIOINFO_NTY, em, 0 );
}

//矩阵
void CCncCenterCtrl::OnMatrixConfigNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    m_tTPMatrixConfig = *(TTPMatrixConfig*)( cTpMsg.GetBody() );

    PrtMsg( ev_CnMatrixConfigInfo_Nty, emEventTypecnstoolRecv,"Matrix config notify.");

    PostEvent( UI_MATRIXCONFIG_NTY);
}

void CCncCenterCtrl::OnMatrixOnlineStateNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    m_bIsMatrixOnline = *(BOOL*)( cTpMsg.GetBody());

    PrtMsg( ev_CnMatrixOnlineState_Nty, emEventTypeCnsRecv, "bIsOnline：%d", m_bIsMatrixOnline);

    PostEvent( UI_MATRIXCONFIG_NTY );
}

BOOL CCncCenterCtrl::GetMatrixOnlineState()
{
    return m_bIsMatrixOnline;
}

void CCncCenterCtrl::OnMatrixSceneInfoNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    TTPMatrixSceneInfo *ptTPMatrixSceneInfo = reinterpret_cast<TTPMatrixSceneInfo*>( cTpMsg.GetBody());
    memcpy(m_atTPMatrixSceneInfo, ptTPMatrixSceneInfo, sizeof(TTPMatrixSceneInfo)*TP_MATRIX_SCENENUM_MAX);

    for (int i = 0 ; i < TP_MATRIX_SCENENUM_MAX ; i++)
    {
        PrtMsg( ev_CnMatrixSceneInfo_Nty, emEventTypeCnsRecv, "Index: %d, name= %s, bUsed：%d,               \
                CurMatrixInfo:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
                i, m_atTPMatrixSceneInfo[i].achSceneName, m_atTPMatrixSceneInfo[i].bUsed,
                m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[0],m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[1],
                m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[2],m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[3],
                m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[4],m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[5],
                m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[6],m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[7],
                m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[8],m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[9],
                m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[10],m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[11],
                m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[12],m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[13],
                m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[14],m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[15],
                m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[16],m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[17],
                m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[18],m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[19],
                m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[20],m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[21],
                m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[22],m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[23],
                m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[24],m_atTPMatrixSceneInfo[i].m_achMatrixInOutRelation[25]);
    }

    PostEvent( UI_MATRIXSCENE_NTY );
}

TTPMatrixSceneInfo* CCncCenterCtrl::GetMatrixScneInfo()
{
    return m_atTPMatrixSceneInfo;
}

void CCncCenterCtrl::OnCurMatrixInfoNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    m_tTPCurMatrixInfo = *(TTPCurMatrixInfo*)( cTpMsg.GetBody());

    PrtMsg( ev_CnCurMatrixInfo_Nty, emEventTypeCnsRecv, 
            "CurMatrixInfo:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", 
            m_tTPCurMatrixInfo.m_achMatrixInOutRelation[0],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[1],
            m_tTPCurMatrixInfo.m_achMatrixInOutRelation[2],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[3],
            m_tTPCurMatrixInfo.m_achMatrixInOutRelation[4],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[5],
            m_tTPCurMatrixInfo.m_achMatrixInOutRelation[6],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[7],
            m_tTPCurMatrixInfo.m_achMatrixInOutRelation[8],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[9],
            m_tTPCurMatrixInfo.m_achMatrixInOutRelation[10],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[11],
            m_tTPCurMatrixInfo.m_achMatrixInOutRelation[12],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[13],
            m_tTPCurMatrixInfo.m_achMatrixInOutRelation[14],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[15],
            m_tTPCurMatrixInfo.m_achMatrixInOutRelation[16],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[17],
            m_tTPCurMatrixInfo.m_achMatrixInOutRelation[18],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[19],
            m_tTPCurMatrixInfo.m_achMatrixInOutRelation[20],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[21],
            m_tTPCurMatrixInfo.m_achMatrixInOutRelation[22],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[23],
            m_tTPCurMatrixInfo.m_achMatrixInOutRelation[24],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[25]);

    PostEvent( UI_CURMATRIXSCENE_NTY ,TRUE);
}

TTPCurMatrixInfo CCncCenterCtrl::GetCurMatrixInfo()
{
    return m_tTPCurMatrixInfo;
}

TTPMatrixConfig CCncCenterCtrl::GetMatrixConfig()
{
    return m_tTPMatrixConfig;
}

u16 CCncCenterCtrl::SetMatrixInOutCmd( u32 dwIn, u32 dwOut )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr(); 
    pcTpMsg->SetUserData( m_pSession->GetInst() );

    pcTpMsg->SetEvent( ev_CnChangeMatrixOutInRelation_Cmd ); 
    pcTpMsg->SetBody( &dwOut, sizeof(u32) );
    pcTpMsg->CatBody( &dwIn, sizeof(u32) );

    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_CnChangeMatrixOutInRelation_Cmd, emEventTypeCnsSend,"In : %d, Out : %d", dwIn, dwOut);
    return wRet;
}

void CCncCenterCtrl::OnChangeMatrixOutInRelationInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    TTPMatrixSceneInfo tTPMatrixSceneInfo = *(TTPMatrixSceneInfo*)( cTpMsg.GetBody());
    memcpy(m_tTPCurMatrixInfo.m_achMatrixInOutRelation, tTPMatrixSceneInfo.m_achMatrixInOutRelation, sizeof(s32)*MT_MAX_MATRIX_CHANNEL_LEN);
    BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(TTPMatrixSceneInfo));

    PrtMsg( ev_CnMatrixOutInRelation_Ind, emEventTypeCnsRecv, 
        "bSuccess:%d, CurMatrixInfo:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", bSuccess,
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[0],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[1],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[2],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[3],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[4],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[5],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[6],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[7],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[8],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[9],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[10],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[11],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[12],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[13],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[14],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[15],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[16],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[17],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[18],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[19],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[20],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[21],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[22],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[23],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[24],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[25]);

    PostEvent( UI_CURMATRIXSCENE_NTY, FALSE );
}

void CCncCenterCtrl::OnMatrixOutInRelationNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    TTPMatrixSceneInfo tTPMatrixSceneInfo = *(TTPMatrixSceneInfo*)( cTpMsg.GetBody());
    memcpy(m_tTPCurMatrixInfo.m_achMatrixInOutRelation, tTPMatrixSceneInfo.m_achMatrixInOutRelation, sizeof(s32)*MT_MAX_MATRIX_CHANNEL_LEN);

    PrtMsg( ev_Cn_MatrixInOutRelation_Nty, emEventTypeCnsRecv, 
        "CurMatrixInfo:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", 
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[0],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[1],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[2],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[3],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[4],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[5],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[6],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[7],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[8],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[9],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[10],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[11],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[12],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[13],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[14],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[15],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[16],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[17],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[18],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[19],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[20],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[21],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[22],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[23],
        m_tTPCurMatrixInfo.m_achMatrixInOutRelation[24],m_tTPCurMatrixInfo.m_achMatrixInOutRelation[25]);

    PostEvent( UI_CURMATRIXSCENE_NTY, FALSE );
}

u16 CCncCenterCtrl::SaveMatrixScenceCmd( s32 dwIndex, s8* achName )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr(); 
    pcTpMsg->SetUserData( m_pSession->GetInst() );

    pcTpMsg->SetEvent( ev_CnSaveMatrixScence_Cmd ); 
    pcTpMsg->SetBody( &dwIndex, sizeof(s32) );
    pcTpMsg->CatBody( achName, sizeof(s8)*(TP_MATRIX_SCENENAME_LEN + 1) );

    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_CnSaveMatrixScence_Cmd, emEventTypeCnsSend,"Index : %d, Name : %s", dwIndex, achName);
    return wRet;
}

void CCncCenterCtrl::OnSaveMatrixSceneInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    //index
    s32 dwIndex = *(s32*)( cTpMsg.GetBody());
    //name
    s8 achName[TP_MATRIX_SCENENAME_LEN + 1] = {0};
    s8 *chName = reinterpret_cast<s8*>( cTpMsg.GetBody() + sizeof(s32));
    memcpy(achName, chName, sizeof(s8)*(TP_MATRIX_SCENENAME_LEN + 1));
    //success
    BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(s32) + sizeof(s8)*(TP_MATRIX_SCENENAME_LEN + 1));

    PrtMsg( ev_CnSaveMatrixScence_Ind, emEventTypeCnsRecv, "Index: %d, Success：%d", dwIndex ,bSuccess);

    PostEvent( UI_SAVEMATRIXSCENE_IND ,bSuccess, dwIndex);
}

u16 CCncCenterCtrl::ReNameMatrixScenceCmd( u32 dwIndex, s8* achName )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr(); 
    pcTpMsg->SetUserData( m_pSession->GetInst() );

    pcTpMsg->SetEvent( ev_CnRenameMatrixScence_Cmd ); 
    pcTpMsg->SetBody( &dwIndex, sizeof(u32) );
    pcTpMsg->CatBody( achName, sizeof(s8)*(TP_MATRIX_SCENENAME_LEN + 1) );

    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_CnRenameMatrixScence_Cmd, emEventTypeCnsSend,"Index : %d, Name : %s", dwIndex, achName);
    return wRet;
}

void CCncCenterCtrl::OnReNameMatrixSceneInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    //name
    s8 achName[TP_MATRIX_SCENENAME_LEN + 1] = {0};
    s8 *chName = reinterpret_cast<s8*>( cTpMsg.GetBody());
    memcpy(achName, chName, sizeof(s8)*(TP_MATRIX_SCENENAME_LEN + 1));
    //index
    u32 dwIndex = *(u32*)( cTpMsg.GetBody()  + sizeof(s8)*(TP_MATRIX_SCENENAME_LEN + 1));
    //success
    BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(s8)*(TP_MATRIX_SCENENAME_LEN + 1) + sizeof(u32) );

    PrtMsg( ev_CnRenameMatrixScence_Ind, emEventTypeCnsRecv, "Index: %d, Success：%d", dwIndex ,bSuccess);

    PostEvent( UI_RENAMEMATRIXSCENE_IND ,bSuccess, dwIndex);
}

u16 CCncCenterCtrl::DeleteMatrixScenceCmd( u32 dwIndex )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr(); 
    pcTpMsg->SetUserData( m_pSession->GetInst() );

    pcTpMsg->SetEvent( ev_CnDeleteMatrixScence_Cmd ); 
    pcTpMsg->SetBody( &dwIndex, sizeof(u32) );

    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_CnDeleteMatrixScence_Cmd, emEventTypeCnsSend,"Index : %d", dwIndex);
    return wRet;
}

void CCncCenterCtrl::OnDeleteMatrixSceneInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    //index
    u32 dwIndex = *(u32*)( cTpMsg.GetBody() );
    //success
    BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(u32) );

    PrtMsg( ev_CnDeleteMatrixScence_Ind, emEventTypeCnsRecv, "Index: %d, Success：%d", dwIndex ,bSuccess);

    PostEvent( UI_DELETEMATRIXSCENE_IND ,bSuccess, dwIndex);
}

u16 CCncCenterCtrl::ApplyMatrixScenceCmd( s32 dwIndex )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr(); 
    pcTpMsg->SetUserData( m_pSession->GetInst() );

    pcTpMsg->SetEvent( ev_CnUseMatrixScence_Cmd ); 
    pcTpMsg->SetBody( &dwIndex, sizeof(s32) );

    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_CnUseMatrixScence_Cmd, emEventTypeCnsSend,"Index : %d", dwIndex);
    return wRet;
}

void CCncCenterCtrl::OnApplyMatrixSceneInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    //index
    s32 dwIndex = *(s32*)( cTpMsg.GetBody() );
    //success
    BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(s32) );

    PrtMsg( ev_CnUseMatrixScence_Ind, emEventTypeCnsRecv, "Index: %d, Success：%d", dwIndex ,bSuccess);

    PostEvent( UI_APPLYMATRIXSCENE_IND ,bSuccess, dwIndex);
}

void CCncCenterCtrl::OnSelectComNty( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    EmComType emComType2 = *(EmComType*)( cTpMsg.GetBody());
    EmComType emComType3 = *(EmComType*)( cTpMsg.GetBody() + sizeof(EmComType));
    m_aemComType[0]= emComType2;
    m_aemComType[1]= emComType3;
    PrtMsg( ev_Cn_SelectCom_Nty, emEventTypecnstoolRecv, "emComType2:%d emComType3:%d", emComType2, emComType3 );

    PostEvent( UI_SELECTCOMG_IND );
}

void CCncCenterCtrl::OnSelectComInd( const CMessage& cMsg )
{
    CTpMsg cTpMsg(&cMsg);
    EmComType emComType2 = *(EmComType*)( cTpMsg.GetBody());
    EmComType emComType3 = *(EmComType*)( cTpMsg.GetBody() + sizeof(EmComType));
    BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(EmComType) + sizeof(EmComType));

    PrtMsg( ev_Cn_SelectCom_Ind, emEventTypecnstoolRecv, "bSuccess = %d, emComType2:%d emComType3:%d",bSuccess, emComType2, emComType3 );

    if (bSuccess)
    {
        m_aemComType[0]= emComType2;
        m_aemComType[1]= emComType3;
        PostEvent( UI_SELECTCOMG_IND );
    }
}

EmComType* CCncCenterCtrl::GetComType()
{
    return m_aemComType;
}

void CCncCenterCtrl::OnCentreDFScreenConfigNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    m_tCenDownOrFlipScreenInfo = *(TCenDownOrFlipScreenInfo*)(  cTpMsg.GetBody() );

    PrtMsg( ev_Cn_CentreDFScreenConfig_Nty, emEventTypeCnsRecv, "EmComConfigType:%d dwGroupNum:%d",
        m_tCenDownOrFlipScreenInfo.emDeviceType, m_tCenDownOrFlipScreenInfo.dwGroupNum);

    PostEvent( UI_CNC_CENTREDFSCREENCONFIG_NTY );
}

void CCncCenterCtrl::OnSelectDFScreenNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    BOOL *ptSelectDFScreen = reinterpret_cast<BOOL*>( cTpMsg.GetBody());
    memcpy(m_abSelectDFScreen, ptSelectDFScreen, sizeof(BOOL)*MAX_CENTREDFSCREEN_GROUP_NUM);

    PrtMsg( ev_cns_SelectDFScreen_Nty, emEventTypeCnsRecv, "SelectDFScreen:<%d, %d, %d, %d, %d>",
        m_abSelectDFScreen[0], m_abSelectDFScreen[1], m_abSelectDFScreen[2], m_abSelectDFScreen[3], m_abSelectDFScreen[4] );

    PostEvent( UI_CNC_CENTRESELECTDFSCREEN_NTY );
}

void CCncCenterCtrl::OnCentreModifydDFScreenGroupInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);

    u32 dwGroupNum = *(u32*)(  cTpMsg.GetBody() );
    TCenDownOrFlipScreenCfg *ptScreenCfg = reinterpret_cast<TCenDownOrFlipScreenCfg *>( cTpMsg.GetBody() + sizeof(u32) );
    BOOL bSuccess = *(BOOL*)( cTpMsg.GetBody() + sizeof(u32) + sizeof(TCenDownOrFlipScreenCfg)*MAX_CENTREDFSCREEN_GROUP_NUM );
    if (bSuccess)
    {
        m_tCenDownOrFlipScreenInfo.dwGroupNum = dwGroupNum;
        memcpy(m_tCenDownOrFlipScreenInfo.tCenDownOrFlipScreenCfg, ptScreenCfg, sizeof(TCenDownOrFlipScreenCfg)*MAX_CENTREDFSCREEN_GROUP_NUM);
    }

    PrtMsg( ev_Cn_ModifyDFScreenGroup_Ind, emEventTypeCnsRecv, "dwGroupNum:%d <%s, %d>",
        dwGroupNum, m_tCenDownOrFlipScreenInfo.tCenDownOrFlipScreenCfg->achGroupName, m_tCenDownOrFlipScreenInfo.tCenDownOrFlipScreenCfg->emAddrCode+1);

    PostEvent( UI_CNC_CENTREMODIFYDFSCREENGROUP_IND, bSuccess );
}

u16 CCncCenterCtrl::SelectCentreDFScreenCmd( u8 bySrceenControl )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr(); 
    pcTpMsg->SetUserData( m_pSession->GetInst() );

    pcTpMsg->SetEvent( ev_cns_SelectDFScreen_Cmd );

    BOOL bSelect[MAX_CENTREDFSCREEN_GROUP_NUM] = {0};
    for (u16 wIndex = 0; wIndex < MAX_CENTREDFSCREEN_GROUP_NUM; wIndex++)
    {
        bSelect[wIndex] = bySrceenControl & adwTagArray[wIndex];
    }

    pcTpMsg->SetBody( bSelect, sizeof(BOOL)*MAX_CENTREDFSCREEN_GROUP_NUM );

    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_cns_SelectDFScreen_Cmd, emEventTypeCnsSend,"bySrceenControl : %d", bySrceenControl);
    return wRet;
}

u16 CCncCenterCtrl::SetCentreDFScreenCmd( EmCommandType emCommand )
{
    CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr(); 
    pcTpMsg->SetUserData( m_pSession->GetInst() );

    pcTpMsg->SetEvent( ev_Cn_DFScreenCommand_Cmd );
    pcTpMsg->SetBody( &emCommand, sizeof(EmCommandType) );

    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
    PrtMsg( ev_Cn_DFScreenCommand_Cmd, emEventTypeCnsSend,"EmCommandType : %d", emCommand);
    return wRet;
}

void CCncCenterCtrl::OnCentreDFScreenCommandInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    //EmCommandType
    //BOOL
    BOOL bSuccess = *(BOOL*)(cTpMsg.GetBody() + sizeof(EmCommandType));

    PrtMsg( ev_Cn_DFScreenCommand_Ind, emEventTypeCnsRecv, "Success: %d", bSuccess);

    PostEvent( UI_CNC_CENTREDFSCREENCMD_IND, bSuccess);
}

void CCncCenterCtrl::OnSelectDFScreenInd(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    BOOL *ptSelectDFScreen = reinterpret_cast<BOOL*>( cTpMsg.GetBody());
    BOOL bSuccess = *(BOOL*)(cTpMsg.GetBody() + sizeof(BOOL)*MAX_CENTREDFSCREEN_GROUP_NUM);
    memcpy(m_abSelectDFScreen, ptSelectDFScreen, sizeof(BOOL)*MAX_CENTREDFSCREEN_GROUP_NUM);

    PrtMsg( ev_cns_SelectDFScreen_Ind, emEventTypeCnsRecv, "Success: %d,SelectDFScreen:<%d, %d, %d, %d, %d>",
        bSuccess, m_abSelectDFScreen[0], m_abSelectDFScreen[1], m_abSelectDFScreen[2], m_abSelectDFScreen[3], m_abSelectDFScreen[4] );

    PostEvent( UI_CNC_SELECTDFSCREEN_IND, bSuccess );
}

TCenDownOrFlipScreenInfo CCncCenterCtrl::GetCenDownOrFlipScreenInfo()
{
    return m_tCenDownOrFlipScreenInfo;
}

BOOL* CCncCenterCtrl::GetCenSelectDFScreen()
{
    return m_abSelectDFScreen;
}