/** @defgroup cnc������Ƶ���ؽӿ� 
 *  @version V1.1.4
 *  @author  Ф��Ȼ
 *  @date    2014.9.23
 */

#include "stdafx.h"
#include "commoninterface.h"
#include "messageboxlogic.h"

/**
* ����:  ��ȡ����cns����״̬
* @param [out]tConfInfo  ����cns�μӵĻ�����Ϣ
* @return �ɹ�����TRUE,ʧ�ܷ���FALSE
* @remarks 
*/
TTPCnsConfStatus CCommonInterface::GetLocalCnsConfState() const
{  
    TTPCnsConfStatus tConfStatus;
    if ( NULL == m_pCnsConfCtrl )
    {
        return tConfStatus;
    }
#ifdef INCONF
    TTPCnsConfStatus tTTPCnsConfStatus;
    tTTPCnsConfStatus.emState = em_CALL_CONNECTED;
    tTTPCnsConfStatus.m_emCallType = emCallType_Conf;
    tTTPCnsConfStatus.m_bMixMotive = true;
    tTTPCnsConfStatus.m_emConfProtocal = emTpH320;
    tTTPCnsConfStatus.m_emTPEncryptType = emTPEncryptTypeNone;
    return tTTPCnsConfStatus;
#else
    return m_pCnsConfCtrl->GetCnsConfStatus();    
#endif
}


BOOL32 CCommonInterface::IsInConf( TCMSConf *pConf/* = NULL*/ )
{   
#ifdef INCONF
    BOOL32 bIn = TRUE;
    if ( pConf != NULL )
    {
        pConf->m_emConfType = emCallType_Conf;
        pConf->m_bStartAudmix = true;
        pConf->m_bVacOn = true;
        strncpy(pConf->m_achConfName, "meeting",TP_MAX_ALIAS_LEN);

        //pConf->m_emConfType = emCallType_Conf; emCallType_P2P
    }
    return bIn;
#else
    BOOL32 bIn = FALSE;    
#endif

	TTPCnsConfStatus status = GetLocalCnsConfState() ;
	if ( status.emState == em_CALL_CONNECTED )
	{
		if ( pConf != NULL )
		{
			m_pUmsConfCtrl->GetConf( *pConf );
		}

		bIn = TRUE;
	}

	return bIn;
}

/** 
* ����  ����/ֹͣ˫��
* @param [in]  bStart   true:������false���ر�
* @return  
* @remarks 
*/
u16 CCommonInterface::StartDual( BOOL32 bStart )
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	u16 wRe = m_pCnsConfCtrl->StartDual( bStart );

	return wRe;
}

BOOL CCommonInterface::IsLocalCnsDual() const
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}
	return  m_pCnsConfCtrl->IsLocalCnsDual();
}

BOOL CCommonInterface::IsLocalPTPSeatArouse() const
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	return m_pCnsConfCtrl->IsLocalPTPSeatArouse();
}

//��������
u16 CCommonInterface::StartDualCodeStream( const TTPCnMediaTransPort &tVedioTransAddr, const TTPCnMediaTransPort &tAudioTransAddr ) const  
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}  

	u16 wRe = m_pCnsConfCtrl->StartDualCodeStream( tVedioTransAddr , tAudioTransAddr);

	return wRe;
}

u16 CCommonInterface::StopDualCodeStream() const
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}  

	u16 wRe = m_pCnsConfCtrl->StopDualCodeStream( );

	return wRe;
}

u16 CCommonInterface::ReqKeyFrame( BOOL32 bForce ) const
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}  

	u16 wRe = m_pCnsConfCtrl->ReqKeyFrame( bForce );

	return wRe;
}

TTPCnMediaTransPort CCommonInterface::GetVedioTransAddr() const  
{
	TTPCnMediaTransPort tAdddr;
	if( NULL == m_pCnsConfCtrl )
	{
		return  tAdddr;
	} 

	tAdddr = m_pCnsConfCtrl->GetVedioTransAddr( );

	return tAdddr;
}


TTPCnMediaTransPort CCommonInterface::GetAudioTransAddr() const  
{
	TTPCnMediaTransPort tAdddr;
	if( NULL == m_pCnsConfCtrl )
	{
		return  tAdddr;
	} 

	tAdddr = m_pCnsConfCtrl->GetAudioTransAddr( );

	return tAdddr;
}

/** 
* ����  ����/ֹͣ��ѯ   ��ʼ��ѯ �ڻ����еĿ���
* @param [in]  bStart   true:������false���ر�
* @return  
* @remarks 
*/
u16 CCommonInterface::StartPoll( BOOL32 bStart )
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	u16 re  = m_pCnsConfCtrl->StartPoll( bStart );

	return re;

}

//��������
u16 CCommonInterface::StartRoll( TTpConfRollCallInfo tTpConfRollCallInfo )
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	u16 re  = m_pCnsConfCtrl->StartRoll( tTpConfRollCallInfo );

	return re;

}

u16 CCommonInterface::RollNext( TTpRollCallNextEpInfo tTpRollCallNextEpInfo )
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	u16 re  = m_pCnsConfCtrl->RollNext( tTpRollCallNextEpInfo );

	return re;

}

u16 CCommonInterface::RollAttendState( TTpRollCallPresentStateMsg tTpRollCallPresentStateMsg )
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	u16 re  = m_pCnsConfCtrl->RollAttendState( tTpRollCallPresentStateMsg );

	return re;

}

u16 CCommonInterface::RollListFixedCmd( TTpUpdataRollCallList tTpUpdataRollCallList )
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	u16 re  = m_pCnsConfCtrl->RollListFixedCmd( tTpUpdataRollCallList );

	return re;

}

//��������
u16 CCommonInterface::StartConfMix( TTpAudMixInfo tTpAudMixInfo )
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	u16 re  = m_pCnsConfCtrl->StartConfMix( tTpAudMixInfo );

	return re;

}

u16 CCommonInterface::FixConfMix( TTpAudMixListCmd tpAudMixListCmd )
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	u16 re  = m_pCnsConfCtrl->ConfMixFixCmd( tpAudMixListCmd );

	return re;

}

u16 CCommonInterface::ScrnCancleSelView( u8 byScreenID ) 
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	u16 re  = m_pCnsConfCtrl->CancleSelView( byScreenID );

	return re;
}

u16 CCommonInterface::ScrnDisplayDual( const u16 wScrnID ) const  
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}  

	u16 wRe = m_pCnsConfCtrl->ScrnDisplayDual( wScrnID );

	return wRe;
}

u16 CCommonInterface::ScrnStopDisplayDual( const u16 wScrnID ) const 
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}  

	u16 wRe = m_pCnsConfCtrl->ScrnStopDisplayDual( wScrnID );

	return wRe;
}


u16 CCommonInterface::ScrnSpareTimeDisplayDual( u16 wScrnID, BOOL bIsShow )
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}  

	u16 wRe = m_pCnsConfCtrl->SpareTimeScreenDualSet( wScrnID, bIsShow );

	return wRe;
}

u16 CCommonInterface::ScrnDisplayLocal( const u16 wScrnID ) const  
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}  

	u16 wRe = m_pCnsConfCtrl->ScrnDisplayLocal( wScrnID );

	return wRe;
}

u16 CCommonInterface::ScrnStopDisplayLocal( const u16 wScrnID ) const 
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}  

	u16 wRe = m_pCnsConfCtrl->ScrnStopDisplayLocal( wScrnID );

	return wRe;
}

const vector<TTPAlias>& CCommonInterface::GetConfTempList()
{
	return m_pCnsConfigCtrl->GetUmsRegInfo();
}

u16 CCommonInterface::UpdateConfTemplate()
{
	if ( NULL == m_pCnsConfigCtrl ) 
	{
		return ERR_CMS;
	}

	return m_pCnsConfigCtrl->ReqSipRegInfo( emGetRegInfoType_UMS );
}

u16 CCommonInterface::StartTemplateConf( const TTPAlias& tTemp )  
{  
	if ( ComInterface->GetWBConfState() )
	{
		CString strMsg = _T("�����µĻ�����Զ�������ǰ�����ݻ��飬�Ƿ������");

		int nResult = ShowMessageBox(strMsg,true);
		if ( IDOK != nResult )
		{
			return ERR_CMS;
		}

	}

	//return	MakeCall( tTemp ); 
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	} 

	TTPDialParam  tTPDialParam;


	switch ( tTemp.m_byType )
	{
	case tp_Alias_h323:
		tTPDialParam.tCalledAddr.emType = emTpAlias; 
		_snprintf( tTPDialParam.tCalledAddr.achAlias, sizeof(tTPDialParam.tCalledAddr.achAlias), "%s", tTemp.m_abyAlias );
		break;
	case tp_Alias_e164:
		tTPDialParam.tCalledAddr.emType = emTpE164Num;
		_snprintf( tTPDialParam.tCalledAddr.achE164, sizeof(tTPDialParam.tCalledAddr.achE164), "%s", tTemp.m_abyAlias );
		break;
	default:
		break;
	} 

	tTPDialParam.emProtocol = emTpSIP;
	tTPDialParam.emCallType = emTpInvite;

	//��ums����
	tTPDialParam.m_emEndpointType = emTPEndpointTypeUMS;

	//  strncpy( (char*)tTPDialParam.tCalledAddr.achAlias, (char*)achIp, TP_MAX_H323ALIAS_LEN ); 
	tTPDialParam.tCalledAddr.wPort = TP_UMS_SIP_LISTIEN_PORT;

	tTPDialParam.tCallingAddr.emType = emTpAlias; 
	tTPDialParam.tCallingAddr.wPort = CNS_SIP_STACK_LISTION_PORT; 
    tTPDialParam.bModuleConf = TRUE;
	u16 wRe  = m_pCnsConfCtrl->MakeCall( tTPDialParam ); 

	return wRe;
}

u16 CCommonInterface::GetCnTempPwdInd( s8 achPwd[] )
{
    if ( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;
    }
    return m_pCnsConfCtrl->GetCnTempPwdInd( achPwd );
}

/*��  ��  ����һ����ʱ���飨��ʱ�����飩
��  ��	tCnsList :�����ն��б� ,���᳡Ϊ��һ����Ա��������Ϊ���᳡
����ֵ  �ɹ�����0��ʧ�ܷ��ش�����
˵  ��	umsԤ��һ�����ڿ�����ʱ����Ļ���ģ�壨IDΪ0�����û���ģ����治��ʾ*/
u16 CCommonInterface::StartInstantConf( const vector<TCnAddr>& tCnsList ) 
{   
     
	if ( ComInterface->GetWBConfState() )
	{
		CString strMsg = _T("�����µĻ�����Զ�������ǰ�����ݻ��飬�Ƿ������");
		
		int nResult = ShowMessageBox(strMsg,true);
		if ( IDOK != nResult )
		{
			return ERR_CMS;
		}

	}

	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	TTPCnsInfo tCnsInfo;
	GetLocalCnsInfo( tCnsInfo );
    
    TTPDialParam  tTPDialParam;
    _snprintf( tTPDialParam.tConfInfo.achConfName, sizeof(tTPDialParam.tConfInfo.achConfName), "%s%s", tCnsInfo.m_achRoomName, INSTANT_CONFTEMPLATE_NAME );
  
    tTPDialParam.bCreateConf = TRUE;
    tTPDialParam.emProtocol = emTpSIP;
    tTPDialParam.emCallType = emTpCreate;
    tTPDialParam.tCalledAddr.emType = emTpIPAddr; 
    //  strncpy( (char*)tTPDialParam.tCalledAddr.achAlias, (char*)achIp, TP_MAX_H323ALIAS_LEN ); 
    tTPDialParam.tCalledAddr.wPort = TP_UMS_SIP_LISTIEN_PORT ;
    //��ums����
    tTPDialParam.m_emEndpointType = emTPEndpointTypeUMS;

	TTPCallSerInfo tCallSerInfo;
	GetCallServerInfo( tCallSerInfo );
    tTPDialParam.tCalledAddr.emProtocolVersion = emIPV4;
	tTPDialParam.tCalledAddr.tIP.dwIPV4 = tCallSerInfo.dwCallServiceIP;
    
    tTPDialParam.tCallingAddr.emType = emTpAlias; 
    tTPDialParam.tCallingAddr.wPort = CNS_SIP_STACK_LISTION_PORT ; 
    
    tTPDialParam.byTerNum = tCnsList.size(); 
    
    for ( int i = 0; i < tCnsList.size() ; i++ )
    {   
        /*
        if ( tCnsList.m_tCnsList[i].m_tAlias.m_byType == tp_Alias_h323 )
        {
            tTPDialParam.atList[i].emType = emTpAlias;
        }
        else
        {
            tTPDialParam.atList[i].emType = emTpE164Num;
        }
        _snprintf( tTPDialParam.atList[i].achAlias, sizeof( tTPDialParam.atList[i].achAlias ) ,tCnsList.m_tCnsList[i].m_tAlias.m_abyAlias );
        */

        tTPDialParam.atList[i] = tCnsList[i];           
    }

	tTPDialParam.tConfInfo.emTpVideoFormat = emTPVH264;
	tTPDialParam.tConfInfo.emTpAudioFormat = GetAudioFormatInfo();

	TTPVidForamt tVidForamt, tDualVidForamt; 
	GetVideoFormatInfo( tVidForamt );
	GetDualVideoFormatInfo( tDualVidForamt );
	tTPDialParam.tConfInfo.byPriVidFps = tVidForamt.wVidFrameRate;
	tTPDialParam.tConfInfo.bySecVidFps = tDualVidForamt.wVidFrameRate;
	tTPDialParam.tConfInfo.emDualVideoQualityLevel = emTPH264HP;		//���治������HP��BP,�˴��̶�HP  ---2014.5.21 JYY
	tTPDialParam.tConfInfo.emPriVideoQualityLevel = emTPH264HP;
	tTPDialParam.tConfInfo.emTpResolution = tVidForamt.emTpVideoResolution;
	tTPDialParam.tConfInfo.emTpSecVidRes = tDualVidForamt.emTpVideoResolution;

	GetCallRateInfo( tTPDialParam.tConfInfo.wCallRate );
	GetDualCallRateInfo( tTPDialParam.tConfInfo.wDualCallRate );
	GetConfPollInfo( tTPDialParam.tConfInfo.tPollInfo );
	GetConfDisInfo( tTPDialParam.tConfInfo.tConfAudMixInfo.m_atAuxMixList.m_bAudMixOn );
	if ( tTPDialParam.tConfInfo.tConfAudMixInfo.m_atAuxMixList.m_bAudMixOn )
	{
		tTPDialParam.tConfInfo.tConfAudMixInfo.m_atAuxMixList.m_awList[0] = 0;
	} 
	else
	{
		tTPDialParam.tConfInfo.tConfAudMixInfo.m_atAuxMixList.m_awList[0] = TP_INVALID_INDEX;
	}
	tTPDialParam.tConfInfo.tConfAudMixInfo.m_atAuxMixList.m_awList[1] = TP_INVALID_INDEX;
	tTPDialParam.tConfInfo.tConfAudMixInfo.m_atAuxMixList.m_awList[2] = TP_INVALID_INDEX;
	tTPDialParam.tConfInfo.tConfAudMixInfo.m_atAuxMixList.m_awList[3] = TP_INVALID_INDEX;

    u16 wRe  = m_pCnsConfCtrl->MakeCall( tTPDialParam);
    return wRe;
   
}


u16 CCommonInterface::HangupConf()
{
    if ( NULL == m_pUmsConfCtrl ) 
    {
        return ERR_CMS;
    }

    u16 wRe = m_pUmsConfCtrl->HangupConfReq();
    return wRe;
}


/**��Ե����
*  @param[in] 
*  @return  
*/
u16 CCommonInterface::StartP2PConf( TCnAddr& tCnAddr )
{
	if ( ComInterface->GetWBConfState() )
	{
		CString strMsg = _T("�����µĻ�����Զ�������ǰ�����ݻ��飬�Ƿ������");

		int nResult = ShowMessageBox(strMsg,true);
		if ( IDOK != nResult )
		{
			return ERR_CMS;
		}

	}

	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	TTPDialParam tTPDialParam;

	tTPDialParam.tCalledAddr = tCnAddr;

	//tTPDialParam.emProtocol = emTpSIP;
    tTPDialParam.emProtocol = tCnAddr.emTpConfProtocol;
	tTPDialParam.emCallType = emTpInvite;

	//����Ե����
	tTPDialParam.m_emEndpointType = emTPEndpointTypeCNS;

	//tTPDialParam.tCalledAddr.emType = emTpAlias; 
	//strncpy( (char*)tTPDialParam.tCalledAddr.achAlias, (char*)achIp, TP_MAX_H323ALIAS_LEN ); 
	tTPDialParam.tCalledAddr.wPort = TP_UMS_SIP_LISTIEN_PORT;

	tTPDialParam.tCallingAddr.emType = emTpAlias; 
	tTPDialParam.tCallingAddr.wPort = CNS_SIP_STACK_LISTION_PORT; 

	u16 re  = m_pCnsConfCtrl->MakeCall( tTPDialParam );

	return re;
}

u16 CCommonInterface::StartIpv6P2PConf( TCnAddr& tCnAddr )
{
    if ( ComInterface->GetWBConfState() )
    {
        CString strMsg = _T("�����µĻ�����Զ�������ǰ�����ݻ��飬�Ƿ������");

        int nResult = ShowMessageBox(strMsg,true);
        if ( IDOK != nResult )
        {
            return ERR_CMS;
        }

    }

    if( NULL == m_pCnsConfCtrl )
    {
        return ERR_CMS;
    }

    TTPDialParam tTPDialParam;

    tTPDialParam.tCalledAddr = tCnAddr;

    tTPDialParam.emProtocol = emTpSIP;
    tTPDialParam.emCallType = emTpInvite;

    //����Ե����
    tTPDialParam.m_emEndpointType = emTPEndpointTypeCNS;

    //tTPDialParam.tCalledAddr.emType = emTpAlias; 
    //strncpy( (char*)tTPDialParam.tCalledAddr.achAlias, (char*)achIp, TP_MAX_H323ALIAS_LEN ); 
    tTPDialParam.tCalledAddr.wPort = TP_UMS_SIP_LISTIEN_PORT;
    tTPDialParam.tCalledAddr.emType = emTpIP6Addr;

    tTPDialParam.tCallingAddr.emProtocolVersion = emIPV6;
    tTPDialParam.tCallingAddr.emType = emTpIP6Addr; 
    tTPDialParam.tCallingAddr.wPort = CNS_SIP_STACK_LISTION_PORT; 

    u16 re  = m_pCnsConfCtrl->MakeCall( tTPDialParam );

    return re;
}


u16 CCommonInterface::HungupPtpConf(  )
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	return m_pCnsConfCtrl->HungupPtpConf();
}

BOOL32 CCommonInterface::IsViewLocalPIP()
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}
	return m_pCnsConfCtrl->IsViewLocalPIP();
}
	
BOOL32 CCommonInterface::GetRollState(TTpConfRollCallInfo &tTpConfRollCallInfo)
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	tTpConfRollCallInfo = m_pCnsConfCtrl->GetRollState();
	return NO_ERROR;
}

BOOL32 CCommonInterface::GetRollAttendState(TTpRollCallPresentStateMsg &tTpRollCallPresentStateMsg)
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	tTpRollCallPresentStateMsg = m_pCnsConfCtrl->GetRollAttendState();
	return NO_ERROR;
}

BOOL32 CCommonInterface::GetConfMixState(TTpAudMixInfo &tTpAudMixInfo)
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	tTpAudMixInfo = m_pCnsConfCtrl->GetConfMixState();
	return NO_ERROR;
}

BOOL32 CCommonInterface::GetConfMixIndFix(TTpAudMixListCmdRes &tTpAudMixListCmdRes)
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	tTpAudMixListCmdRes = m_pCnsConfCtrl->GetConfMixIndFix();
	return NO_ERROR;
}

u16 CCommonInterface::ViewLocalPIPCmd( const u8 byScrnID, const BOOL bLocalP ) 
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return 0;
	}
	return m_pCnsConfCtrl->ViewLocalPIPCmd( byScrnID, bLocalP );
}

u16 CCommonInterface::SetCnsInnerSpeaker( u8 bySeatId )
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return 0;
	}
	return m_pCnsConfCtrl->SetInnerSpeaker( bySeatId );
}

u8 CCommonInterface::GetCnsInnerSpeaker()
{
	if ( NULL == m_pCnsConfCtrl )
	{
		return 0;
	}
	return m_pCnsConfCtrl->GetInnerSpeaker();
}

u16 CCommonInterface::GetCnsScreenInfo( vector<TScreenInfo>& vctScreenInfo ) const
{	
	if ( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;	
	}

	vctScreenInfo = m_pCnsConfCtrl->GetCnsScreenInfo();
	return NO_ERROR;
}


u16 CCommonInterface::GetCnsScreenInfoByID( u8 screenID, TScreenInfo& tScreenInfo ) const
{	
	if ( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;	
	}

	vector<TScreenInfo> vctScreenInfo = m_pCnsConfCtrl->GetCnsScreenInfo();

	vector<TScreenInfo>::iterator it = vctScreenInfo.begin();
	while ( it != vctScreenInfo.end() )
	{
		if ( it->byScreenID == screenID )
		{
			tScreenInfo = *it;
			return NO_ERROR;
		}

		it++;
	}

	return ERR_CMS_NOT_FIND;
}


void CCommonInterface::ClearCnsScreenName()
{
    if ( NULL == m_pCnsConfCtrl )
    {
        return ;	
    }

    m_pCnsConfCtrl->ClearCnsScreenInfo();
}


BOOL32 CCommonInterface::IsRcvDual() const 
{
    if( NULL == m_pCnsConfCtrl )
    {
        return FALSE;
    }  

    return  m_pCnsConfCtrl->IsRcvDual();
}



u16 CCommonInterface::CancleSelView( u8 byScreenID ) 
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	u16 re  = m_pCnsConfCtrl->CancleSelView( byScreenID );

	return re;
}

u16 CCommonInterface::SetSelView( TTPSelViewReq tTPSelViewReq ) 
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	u16 re  = m_pCnsConfCtrl->SetSelView(tTPSelViewReq);

	return re;
}

BOOL CCommonInterface::GetDisplayState() const
{
	if ( NULL == m_pCenterCtrlIF )
	{
		return FALSE;
	}
	return m_pCenterCtrlIF->GetDisplayState();
}

u16 CCommonInterface::SetSelTVSView( u8 byScreenID )
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	u16 re  = m_pCnsConfCtrl->SelTVSView( byScreenID );

	return re;
}

u16 CCommonInterface::CancleSelTVSView( u8 byScreenID )
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	u16 re  = m_pCnsConfCtrl->CancelSelTVSView( byScreenID );

	return re;
}

u16 CCommonInterface::FreshConf()
{
	NOTIFY_MSG( UI_CNS_CONFSTATE_NOTIFY, 0, 0 );
	NOTIFY_MSG( UI_CNS_SCREEN_STATE_NOTIFY, 0, 0 );
	NOTIFY_MSG( UI_CNS_SCREEN_STATE_NOTIFY, 1, 0 );
	NOTIFY_MSG( UI_CNS_SCREEN_STATE_NOTIFY, 2, 0 );
	return 0;
}

u16 CCommonInterface::SetCnAuxMix( BOOL bIsAudMix )
{
	if( NULL == m_pCnsConfCtrl )
	{
		return ERR_CMS;
	}

	u16 re  = m_pCnsConfCtrl->SetCnAuxMix( bIsAudMix );

	return re;
}

BOOL32 CCommonInterface::IsLocalCnsChairMan()  
{

	if( !IsInConf() )
	{
		return FALSE;
	}

#ifndef LOGIN
#ifdef CHAIR
    return TRUE;
#else
    return FALSE;
#endif
#endif

	TTPCnsInfo tCnsInfo;
	GetLocalCnsInfo(tCnsInfo);  
	//TCnsInfo* pCns = m_tConfInfo.GetCnsInfoByID( m_tConfInfo.m_wDefaultChairMan );

	TCMSConf tConfInfo ;
	m_pUmsConfCtrl->GetConf( tConfInfo );
	
	if ( strcmp(tConfInfo.m_tChairName.m_abyAlias, tCnsInfo.m_achRoomName) == 0 )
	{
		return TRUE;
	}	

	return FALSE;  
}

/*��  ��	���»����б�����
��  ��	tMixInfo	 �����б�
����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
˵  ��	 */
u16 CCommonInterface::UpdateAudMixList( const TConfAuxMixInfo &tMixInfoList ) 
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pUmsConfCtrl->UpdateAudMixListReq(tMixInfoList);
	return wRe;
}



u16 CCommonInterface::AudMixDisListOpr( const TDiscussListOpr &tDisListOpr )
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}

	u16 wRe = m_pUmsConfCtrl->AudMixDisListOprCmd( tDisListOpr );
	return wRe;
}

u16 CCommonInterface::AuxMixVacOpr( const TConfAuxMixVacOpr tConfAuxMixVacOpr )
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}

	u16 wRe = m_pUmsConfCtrl->AuxMixVacOpr( tConfAuxMixVacOpr );
	return wRe;
}


/**
* ����:  �������᳡������� 
* @param [in] tEp:�᳡��Ϣ
* @return �ɹ�����0��ʧ�ܷ��ش�����
* @remarks �����᳡Ϊ���᳡ʱ���ɲ���
*/
u16 CCommonInterface::InviteCns( const TConfCallEpAddrList &tEp )
{  
    if ( tEp.m_wConfID == INVALID_WORD )
    {
        return ERR_CMS;
    }

    for ( u16 i = 0 ; i< tEp.m_tEpAdrLst.m_wNum; i++)
    {
        InviteCns( tEp.m_tEpAdrLst.m_tCnsList[i].m_tEpAddr );
    }

    return NO_ERROR;
}

/*��  ��  ����ĳ�᳡�������
��  ��	tEp:�᳡��Ϣ
����ֵ  �ɹ�����0��ʧ�ܷ��ش�����
˵  ��	�����᳡Ϊ���᳡ʱ���ɲ��� */
u16 CCommonInterface::InviteCns( const TTpCallAddr &tEp ) 
{
    if ( NULL == m_pUmsConfCtrl ) 
    {
        return ERR_CMS;
    }

    u16 wRe = m_pUmsConfCtrl->InviteCnsReq(tEp);
    return wRe;
}
/**
* ����:	���л������Ѿ����ڵ�cns�᳡����ĳ����
* @param [int]  tEp	 ����ͻ᳡��Ϣ
* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
* @remarks ��Ϣ��cms->ums  evtp_CallEP_cmd  \n
Ӧ�ظ���ums->cms evtp_CallEP_result   \n
���ɹ�����Ӧ����ums->cms evtp_UpdateConfCnsList_Notify
*/ 
u16 CCommonInterface::CallConfCns( const TConfEpID &tEp )
{
    if ( NULL == m_pUmsConfCtrl ) 
    {
        return ERR_CMS;
    }
    
    u16 wRe = m_pUmsConfCtrl->CallConfCnsReq(tEp);
	return wRe;
}

/*��  ��	�Ҷ�ĳ�᳡
��  ��	tConfEpInfo: eqID ����ID
����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
˵  ��	�����б�����Ȼ���ڸû᳡��ֻ�ǲ�����*/
u16 CCommonInterface::HangupCns( const TConfEpID &tConfEpInfo ) 
{
    if ( NULL == m_pUmsConfCtrl ) 
    {
        return ERR_CMS;
    }

    u16 wRe = m_pUmsConfCtrl->HangupCNSReq(tConfEpInfo);
    return wRe;
}

/**��  ��	�᳡���������
��  ��	tConfEpInfo: eqID ����ID
����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
˵  ��	�����Զҡ����������Զҡ�᳡��Ϣ*/
u16 CCommonInterface::SetFeccConfEpInfo( const TConfEpID &tConfEpInfo )
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}
	u16 wRe = m_pUmsConfCtrl->SetFeccConfEpInfo(tConfEpInfo);
	return wRe;
}

/*��  ��	�᳡���������
��  ��	tConfEpInfo: eqID ����ID
����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
˵  ��	�����Զҡ��������ȡԶҡ�᳡��Ϣ*/
u16 CCommonInterface::GetFeccConfEpInfo( TConfEpID &tConfEpInfo )
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}
	u16 wRe = m_pUmsConfCtrl->GetFeccConfEpInfo(tConfEpInfo);
	return wRe;
}

/**
* ����:	�᳡���������
* @param [int]  
* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
* @remarks �᳡������������л�Զҡ�᳡��ƵԴ
*/
u16 CCommonInterface::ChangeFeccSource(u8 SourceId)
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}

	u16 wRe = m_pUmsConfCtrl->ChangeFeccSource(SourceId);
	return wRe;
}

u16 CCommonInterface::SetFeccCamPT( EmDirection emDirection, EmCnAction emCnAction )
{
	if ( NULL == m_pUmsConfCtrl )
	{
		return ERR_CMS;
	}

	return m_pUmsConfCtrl->SetFeccCamPT( emDirection, emCnAction );
}

u16 CCommonInterface::SetFeccCamView( EmZoom emZoom, EmCnAction emCnAction )
{
	if ( NULL == m_pUmsConfCtrl )
	{
		return ERR_CMS;
	}

	return m_pUmsConfCtrl->SetFeccCamView( emZoom, emCnAction );
}

u16 CCommonInterface::SetFeccCamBright( EmPanCamBright emPanCamBright, EmCnAction emCnAction )
{
	if ( NULL == m_pUmsConfCtrl )
	{
		return ERR_CMS;
	}

	return m_pUmsConfCtrl->SetFeccCamBright( emPanCamBright, emCnAction );
}

u16 CCommonInterface::SetFeccCamFocus( EmFocus emFocus, EmCnAction emCnAction )
{
	if ( NULL == m_pUmsConfCtrl )
	{
		return ERR_CMS;
	}

	return m_pUmsConfCtrl->SetFeccCamFocus( emFocus, emCnAction );
}

u16 CCommonInterface::SetFeccCamAotoFocus( )
{
	if ( NULL == m_pUmsConfCtrl )
	{
		return ERR_CMS;
	}

	return m_pUmsConfCtrl->SetFeccCamAotoFocus( );
}


/*��  �� ���÷��Ի᳡
��  ��	wConfID	 ����ID
����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
˵  ��	 */
u16 CCommonInterface::SetSpokeCns( const TConfEpID &tConfEpInfo ) 
{
    if ( NULL == m_pUmsConfCtrl ) 
    {
        return ERR_CMS;
    }

    u16 wRe = m_pUmsConfCtrl->SetSpokeCnsReq(tConfEpInfo);
    return wRe;
}

u16 CCommonInterface::SetQuietCns( const TConfEpID &tConfEpInfo, BOOL32 bQuiet)
{
    if ( NULL == m_pUmsConfCtrl ) 
    {
        return ERR_CMS;
    }

    u16 wRe = m_pUmsConfCtrl->SetQuietCnsReq(tConfEpInfo,bQuiet);
    return wRe;
}

u16 CCommonInterface::SetMuteCns( const TConfEpID &tConfEpInfo, BOOL32 bMute )
{
    if ( NULL == m_pUmsConfCtrl ) 
    {
        return ERR_CMS;
    }

    u16 wRe = m_pUmsConfCtrl->SetMuteCnsReq(tConfEpInfo,bMute);
    return wRe;
}

u16 CCommonInterface::SetDualCns( const TConfEpID &tConfEpInfo, BOOL32 bStart )
{
    if ( NULL == m_pUmsConfCtrl ) 
    {
        return ERR_CMS;
    }

    u16 wRe = m_pUmsConfCtrl->SetDualCnsReq(tConfEpInfo,bStart);
    return wRe;
}


TTpPollStat CCommonInterface::GetPollState()
{
	TTpPollStat tTpPollStat;
	if ( NULL == m_pUmsConfCtrl )
	{
		return tTpPollStat;
	}

	return m_pUmsConfCtrl->GetPollState();
}

u16 CCommonInterface::PollPauseCmd( const BOOL32& bPollPause )
{
	if ( NULL == m_pUmsConfCtrl )
	{
		return ERR_CMS;
	}

	m_pUmsConfCtrl->PollPauseCmd(bPollPause);
	return NO_ERROR;
}

u16 CCommonInterface::PollListUpdateCmd( const TTpPollListNtfy& tTpPollListNtfy )
{
	if ( NULL == m_pUmsConfCtrl )
	{
		return ERR_CMS;
	}

	m_pUmsConfCtrl->PollListUpdateCmd(tTpPollListNtfy);
	return NO_ERROR;
}

u16 CCommonInterface::GetPollList(  vector<u16>& vctPollList  )
{
	if ( NULL == m_pUmsConfCtrl )
	{
		return ERR_CMS;
	}
	m_pUmsConfCtrl->GetPollList(vctPollList);
	return NO_ERROR;
}


u16 CCommonInterface::GetConfPollInfo( TTPPollInfo& tPollInfo ) const
{
	if ( NULL == m_pPortDiagCtrl )
	{
		return ERR_CMS;
	}

	tPollInfo = m_pPortDiagCtrl->GetConfPollInfo();
	return NO_ERROR;
}

u16 CCommonInterface::ConfPollCmd( const TTPPollInfo& tPollInfo )
{
	if ( NULL == m_pPortDiagCtrl )
	{
		return ERR_CMS;
	}

	m_pPortDiagCtrl->ConfPollCmd(tPollInfo);
	return NO_ERROR;
}

u16 CCommonInterface::GetConfDisInfo( BOOL& bDis ) const
{
	if ( NULL == m_pPortDiagCtrl )
	{
		return ERR_CMS;
	}

	bDis = m_pPortDiagCtrl->GetConfDisInfo();
	return NO_ERROR;
}

u16 CCommonInterface::ConfDisCmd( const BOOL& bDis )
{
	if ( NULL == m_pPortDiagCtrl )
	{
		return ERR_CMS;
	}

	m_pPortDiagCtrl->ConfDisCmd(bDis);
	return NO_ERROR;
}


const vector<TBrdVmpResNtfy>& CCommonInterface::GetBrdVmpStatus()
{
	return m_pUmsConfCtrl->GetBrdVmpStatus();
}

const TTPSelViewNtfy CCommonInterface::GetSelWatchStatus()
{
	return m_pUmsConfCtrl->GetSelWatchStatus();
}

const TTPUmsReasonInd CCommonInterface::GetUmsReason()
{
	return m_pUmsConfCtrl->GetUmsReason();
}

const TDiscussListOpr CCommonInterface::GetDiscussList()
{
	return m_pUmsConfCtrl->GetDiscussList();
}

const TTpConfEpInfo CCommonInterface::GetJoinConfInfo()
{
	return m_pUmsConfCtrl->GetJoinConfInfo();
}


u16 CCommonInterface::SetJoinConfInfo( TTpConfEpInfo tpConfEpInfo )
{
	if ( NULL == m_pUmsConfCtrl )
	{
		return ERR_CMS;
	}

	return m_pUmsConfCtrl->SetJoinConfInfo(tpConfEpInfo);
}

bool CCommonInterface::IsAllQuite()
{
	if ( NULL == m_pUmsConfCtrl )
	{
		return false;
	}

	return m_pUmsConfCtrl->IsAllQuite();
}
bool CCommonInterface::IsAllMute()
{
	if ( NULL == m_pUmsConfCtrl )
	{
		return false;
	}

	return m_pUmsConfCtrl->IsAllMute();
}


u16 CCommonInterface::RervesBrdVmpReq( TRersvesEqpReq tRersvesEqp )
{
    if ( NULL == m_pUmsConfCtrl )
    {
        return ERR_CMS;
    }

    return m_pUmsConfCtrl->RervesBrdVmpReq(tRersvesEqp);
}

u16 CCommonInterface::SetBrdVmpReq( TSetVmpInfoReq tVmpInfo )
{
    if ( NULL == m_pUmsConfCtrl )
    {
        return ERR_CMS;
    }

    return m_pUmsConfCtrl->SetBrdVmpReq(tVmpInfo);
}

u16 CCommonInterface::SetBroadcastVmpReq( TBrdVmpReq tBrdVmp )
{
    if ( NULL == m_pUmsConfCtrl )
    {
        return ERR_CMS;
    }

    return m_pUmsConfCtrl->SetBroadcastVmpReq(tBrdVmp);
}

u16 CCommonInterface::SaveVmpCfgReq( TBrdVmpResNtfy &tBrdVmp )
{
    if ( NULL == m_pUmsConfCtrl )
    {
        return ERR_CMS;
    }

    return m_pUmsConfCtrl->SaveVmpCfgReq(tBrdVmp);
}

u16 CCommonInterface::CallVmpCfgReq( TEqpInfo &tEqp )
{
    if ( NULL == m_pUmsConfCtrl )
    {
        return ERR_CMS;
    }

    return m_pUmsConfCtrl->CallVmpCfgReq(tEqp);
}

u16 CCommonInterface::ChangeChanModeReq( u16 wIndex, u8 byMode )
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}

	u16 wRe = m_pUmsConfCtrl->ChangeChanModeReq( wIndex, byMode );
	return wRe;
}

u16 CCommonInterface::SetHduVolReq( u16 wIndex,u8 byVol, BOOL32 bMute )
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}

	u16 wRe = m_pUmsConfCtrl->SetHduVolReq( wIndex, byVol, bMute );
	return wRe;
}

u16 CCommonInterface::StopPlayHdu( TTpHduPlayReq &tTvwInfo )
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}

	u16 wRe = m_pUmsConfCtrl->StopPlayHdu( tTvwInfo );
	return wRe;
}

u16 CCommonInterface::PlayHduReq( TTpHduPlayReq &tTvwInfo )
{
	if ( NULL == m_pUmsConfCtrl ) 
	{
		return ERR_CMS;
	}

	u16 wRe = m_pUmsConfCtrl->PlayHduReq( tTvwInfo );
	return wRe;
}
