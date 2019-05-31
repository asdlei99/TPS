#include "umcglodef.h"
#include "umcconftemplatectrl.h"

CUmcConfTemplateCtrl::CUmcConfTemplateCtrl()
{
	ClearData();

    BuildEventsMap();
}

CUmcConfTemplateCtrl::~CUmcConfTemplateCtrl()
{
	ClearData();
}

void CUmcConfTemplateCtrl::ClearData()
{
	m_vecConfTempList.clear();
	m_wResUsedCount = 0;
}

void CUmcConfTemplateCtrl::BuildEventsMap()
{	
	REG_PFUN( evtp_AddConftemplate_Notify, &CUmcConfTemplateCtrl::OnAddConfTempNotify );
	REG_PFUN( evtp_Updateconftemplate_Notify, &CUmcConfTemplateCtrl::OnUpdateConfTempNotify );
	REG_PFUN( evtp_Delconftemplate_Notify, &CUmcConfTemplateCtrl::OnDelConfTempNotify );
	REG_PFUN( ev_del_all_conftemp_rsp, &CUmcConfTemplateCtrl::OnDelAllConfTempRsp );
	REG_PFUN( evpt_OperatorConfTemplate_Ret, &CUmcConfTemplateCtrl::OnOperateConfTempRsp );
	REG_PFUN( evtp_StartConfTemplate_Ret, &CUmcConfTemplateCtrl::OnStartConfTemplateRsp );
	REG_PFUN( ev_conf_bas_used_nty, &CUmcConfTemplateCtrl::OnUpdateResUsedCountNotify );

	//断链清空资源
	REG_PFUN( OSP_DISCONNECT, &CUmcConfTemplateCtrl::OnLinkBreak ); 

	BuildReqEventsMap();
}

void CUmcConfTemplateCtrl::BuildReqEventsMap()
{
	REG_REQ_PFUN( ev_umcweb_AddConftemplate_req, &CUmcConfTemplateCtrl::OnUmcwebAddConftemplateReq );
	REG_REQ_PFUN( ev_umcweb_UpdateConftemplate_req, &CUmcConfTemplateCtrl::OnUmcwebUpdateConftemplateReq );
	REG_REQ_PFUN( ev_umcweb_DelConftemplate_req, &CUmcConfTemplateCtrl::OnUmcwebDelConftemplateReq );
	REG_REQ_PFUN( ev_umcweb_DelAllConftemp_req, &CUmcConfTemplateCtrl::OnUmcwebDelAllConftempReq );
	REG_REQ_PFUN( ev_umcweb_StartConfTemplate_req, &CUmcConfTemplateCtrl::OnUmcwebStartConfTemplateReq );
	REG_REQ_PFUN( ev_umcweb_RefreshConftempList_nty_req, &CUmcConfTemplateCtrl::OnUmcwebRefreshConftempListNtyReq );
	REG_REQ_PFUN( ev_umcweb_RefreshConftempInfo_nty_req, &CUmcConfTemplateCtrl::OnUmcwebRefreshConftempInfoNtyReq );
	REG_REQ_PFUN( ev_umcweb_RefreshConftemp_MeetNameList_nty_req, &CUmcConfTemplateCtrl::OnUmcwebRefreshConftempMeetNameListNtyReq );
	REG_REQ_PFUN( ev_umcweb_RefreshConftemp_PollingList_nty_req, &CUmcConfTemplateCtrl::OnUmcwebRefreshConftempPollingListNtyReq );
	REG_REQ_PFUN( ev_umcweb_RefreshConftemp_DiscussList_nty_req, &CUmcConfTemplateCtrl::OnUmcwebRefreshConftempDiscussListNtyReq );
	REG_REQ_PFUN( ev_umcweb_ConfBasUsed_nty_req, &CUmcConfTemplateCtrl::OnUmcwebConfBasUsedNtyReq );
	REG_REQ_PFUN( ev_umcweb_confmng_listconfbook_get_req, &CUmcConfTemplateCtrl::OnUmcwebConfmngListconfbookGetReq );
	REG_REQ_PFUN( ev_umcweb_CheckConftempRepeat_req, &CUmcConfTemplateCtrl::OnUmcwebCheckConftempRepeatReq );
}

void CUmcConfTemplateCtrl::DispEvent(const CMessage &cMsg)
{
    DISP_FUN( CUmcConfTemplateCtrl, cMsg );
}

void CUmcConfTemplateCtrl::DispReqEvent( u16 wEvent, const boost::any& arg )
{
    DISP_REQ_FUN( CUmcConfTemplateCtrl, wEvent, arg );
}

void CUmcConfTemplateCtrl::OnLinkBreak( const CMessage& cMsg )
{
	ClearData();

	PrtMsg( OSP_DISCONNECT, emEventTypeServerRecv, "CUmcConfTemplateCtrl::OnLinkBreak"); 
}

void CUmcConfTemplateCtrl::OnAddConfTempNotify( const CMessage& cMsg )
{   
	CTpMsg msg( &cMsg ); 
	TTPConfTemplate tTemplate = *reinterpret_cast<TTPConfTemplate*>(msg.GetBody());
	BOOL32 bIsEnd = *reinterpret_cast<BOOL32*>(msg.GetBody() + sizeof(TTPConfTemplate));
	
	PrtMsg( evtp_AddConftemplate_Notify, emEventTypeServerRecv, "ConfTemplateID=%d, name=%s, E164=%s, bIsEnd=%d",
		tTemplate.m_wID, tTemplate.m_achConfName, tTemplate.m_achConfE164, bIsEnd );

	m_vecConfTempList.push_back( tTemplate );
	
	if ( bIsEnd && PTR_SESSION->m_bRefresh )
	{
		PrtMsg( ev_umcweb_RefreshConfTempResult_res, emEventTypeClientSend, "conftTempID: %d", tTemplate.m_wID );
		PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_RefreshConfTempResult_res\",\"wConfTempID\":\"%d\"}", tTemplate.m_wID );
 
		PTR_SESSION->m_bRefresh = FALSE; 
		//操作成功，手动释放锁
		PTR_MSGDRIVER->ReleaseLock();
	}
}

void CUmcConfTemplateCtrl::OnUpdateConfTempNotify( const CMessage& cMsg )
{
	CTpMsg msg( &cMsg ); 
	TTPConfTemplate tTemplate = *reinterpret_cast<TTPConfTemplate*>(msg.GetBody());
	BOOL32 bIsEnd = *reinterpret_cast<BOOL32*>(msg.GetBody() + sizeof(TTPConfTemplate));
	
	PrtMsg( evtp_Updateconftemplate_Notify, emEventTypeServerRecv, "ConfTemplateID=%d, name=%s, E164=%s, bIsEnd=%d",
        tTemplate.m_wID, tTemplate.m_achConfName, tTemplate.m_achConfE164, bIsEnd );

	std::vector<TTPConfTemplate>::iterator iter = m_vecConfTempList.begin();
	while ( iter != m_vecConfTempList.end() )
	{
		if ( iter->m_wID == tTemplate.m_wID )
		{
			*iter = tTemplate;
			break;
		}
		iter++;
	}

	if ( bIsEnd && PTR_SESSION->m_bRefresh )
	{
		PrtMsg( ev_umcweb_RefreshConfTempResult_res, emEventTypeClientSend, "conftTempID: %d", tTemplate.m_wID );
		PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_RefreshConfTempResult_res\",\"wConfTempID\":\"%d\"}", tTemplate.m_wID );
		
		PTR_SESSION->m_bRefresh = FALSE;
		//操作成功，手动释放锁
		PTR_MSGDRIVER->ReleaseLock();
	}
}

void CUmcConfTemplateCtrl::OnDelConfTempNotify( const CMessage& cMsg )
{
    CTpMsg msg(&cMsg); 
	TDelRefreshConfTemplate tDelTemplateList = *reinterpret_cast<TDelRefreshConfTemplate*>(msg.GetBody());
	
	PrtMsg( evtp_Delconftemplate_Notify, emEventTypeServerRecv, "DeleteNum=%d, first confTemplateID=%d",
		tDelTemplateList.m_wRefreshNum, tDelTemplateList.m_awTmpList[0]);
	
    for ( int i = 0; i < tDelTemplateList.m_wRefreshNum; i++ ) 
	{   
		std::vector<TTPConfTemplate>::iterator iter = m_vecConfTempList.begin();
		while ( iter != m_vecConfTempList.end() )
		{
			if ( tDelTemplateList.m_awTmpList[i] == iter->m_wID )
			{
				m_vecConfTempList.erase(iter);
				break;
			}
			iter++;
		}
    }
	
	if ( PTR_SESSION->m_bRefresh )
	{
		PrtMsg( ev_umcweb_RefreshConfTempResult_res, emEventTypeClientSend, "conftTempID: %d", tDelTemplateList.m_awTmpList[0] );
		PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_RefreshConfTempResult_res\",\"wConfTempID\":\"%d\"}", tDelTemplateList.m_awTmpList[0] );

		PTR_SESSION->m_bRefresh = FALSE;
		//操作成功，手动释放锁
		PTR_MSGDRIVER->ReleaseLock();
	}
}

void CUmcConfTemplateCtrl::OnDelAllConfTempRsp( const CMessage& cMsg )
{
	CTpMsg msg(&cMsg);
    TOprConfTmpResult tTemplate = *reinterpret_cast<TOprConfTmpResult*>(msg.GetBody());
	
	if ( TP_ConfTemplate_DelSuccess == tTemplate.m_emReason )
	{
		m_vecConfTempList.clear();
		PrtMsg( ev_del_all_conftemp_rsp, emEventTypeServerRecv, "del all conftemp success");
	} 
	else
	{
		PrtMsg( ev_del_all_conftemp_rsp, emEventTypeServerRecv, "del all conftemp fail");
	}

	PrtMsg( ev_umcweb_DelAllConftemp_res, emEventTypeClientSend, "emReason: %d", tTemplate.m_emReason );
	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_DelAllConftemp_res\",\"emReason\":\"%d\"}", tTemplate.m_emReason );
}

void CUmcConfTemplateCtrl::OnOperateConfTempRsp( const CMessage& cMsg )
{  
	CTpMsg msg(&cMsg);
    TOprConfTmpResult tTemplate = *reinterpret_cast<TOprConfTmpResult*>(msg.GetBody());
	
	PrtMsg( evpt_OperatorConfTemplate_Ret, emEventTypeServerRecv, "ConfTemplateID=%d, opReslt=%d ( \
		0:UnKonw, 1:AddSuccess, 2:DelSuccess, 3:UpdateSuccess, 4:MaxNum, 5:E164Repeat, 6:UnFindConf, 7:ParamInValid )",
		tTemplate.m_wID, tTemplate.m_emReason );
	
    //PostEvent(UI_UMS_OPERATE_CONFTEMP_RET, tTemplate.m_emReason, tTemplate.m_wID );
	switch( tTemplate.m_emReason )
    {
	case TP_ConfTemplate_UnKonw:
	case TP_ConfTemplate_MaxNum:
	case TP_ConfTemplate_E164Repeat:
	case TP_ConfTemplate_UnFindConf:
	case TP_ConfTemplate_ParamInValid:
		{
			if ( PTR_SESSION->m_bRefresh )
			{
				PrtMsg( ev_umcweb_OperatorConfTemplate_res, emEventTypeClientSend, "emReason: %d", tTemplate.m_emReason );
				PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_OperatorConfTemplate_res\",\"emReason\":\"%d\"}", tTemplate.m_emReason );
				
				PTR_SESSION->m_bRefresh = FALSE;
				//操作失败，手动释放锁
				PTR_MSGDRIVER->ReleaseLock();
			}
		}
		break;
	case TP_ConfTemplate_AddSuccess:
	case TP_ConfTemplate_DelSuccess:
	case TP_ConfTemplate_UpdateSuccess:
		{
			//操作成功
		}
		break;
	default:
		break;
    }
}

void CUmcConfTemplateCtrl::OnStartConfTemplateRsp( const CMessage& cMsg )
{
	CTpMsg kdvMsg(&cMsg);
	TStartConfResult tRe = *reinterpret_cast<tagTStartConfResult*>( kdvMsg.GetBody() );
	
	PrtMsg( evtp_StartConfTemplate_Ret, emEventTypeServerRecv, "ConfID=%d, conftemplateID=%d, errCode=%d ( \
		0:UnKonw, 1:Success, 2:ConfTemplateUnExit, 3:ConfFull, 4:ConfExist, 5:SipUnReg, 6:ResourceFull )",
		tRe.m_wConfID, tRe.m_wConfTemplateID, tRe.m_emReason );
    
	PrtMsg( ev_umcweb_StartConfTemplate_res, emEventTypeClientSend, "emReason: %d", tRe.m_emReason );
	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_StartConfTemplate_res\",\"emReason\":\"%d\"}", tRe.m_emReason );
}

void CUmcConfTemplateCtrl::OnUpdateResUsedCountNotify( const CMessage& cMsg )
{
	CTpMsg msg(&cMsg); 
	u16* wUsedCount = (u16*)(msg.GetBody());
	if ( NULL != wUsedCount )
	{
		m_wResUsedCount = *wUsedCount;
		PrtMsg( ev_conf_bas_used_nty, emEventTypeServerRecv, "res used count=%d", *wUsedCount);
		
		//PostEvent( UI_UMS_CONFTMPRESUSEDCOUNT_NOTIFY,(WPARAM)wUsedCount);	
	}
	else
	{
		PrtMsg( ev_conf_bas_used_nty, emEventTypeServerRecv, "invlid res used count data" );
	}
} 

u16 CUmcConfTemplateCtrl::AddConfTemplateReq( const TTPConfTemplate &tConfTemp )    
{    
	CTpMsg *pkdvMsg = PTR_MSGDRIVER->GetKdvMsgPtr(); 
    pkdvMsg->SetEvent( evtp_AddConfTemplate_req );
	pkdvMsg->SetBody( &tConfTemp, sizeof(TTPConfTemplate) );

	PrtMsg( evtp_AddConfTemplate_req, emEventTypeServerSend, "ConfTemplateID=%d, name=%s, E164=%s",
		tConfTemp.m_wID, tConfTemp.m_achConfName, tConfTemp.m_achConfE164);

	PTR_SESSION->m_bRefresh = TRUE;

	//OSP_RSP_SELF_HANDLE:自己处理锁释放
	u16 wRe = PTR_MSGDRIVER->PostCommand(this, OSP_RSP_SELF_HANDLE, TYPE_TPMSG);
	return wRe;
}

u16 CUmcConfTemplateCtrl::ModifyConfTemplateReq( const TTPConfTemplate &tConfTemp )    
{    
	CTpMsg *pkdvMsg = PTR_MSGDRIVER->GetKdvMsgPtr();
    pkdvMsg->SetEvent( evtp_Updateconftemplate_Req );
	pkdvMsg->SetBody( &tConfTemp, sizeof(TTPConfTemplate) );

	PrtMsg( evtp_Updateconftemplate_Req, emEventTypeServerSend, "ConfTemplateID=%d, name=%s, E164=%s",
		tConfTemp.m_wID, tConfTemp.m_achConfName, tConfTemp.m_achConfE164);

	PTR_SESSION->m_bRefresh = TRUE;

	//OSP_RSP_SELF_HANDLE:自己处理锁释放
    u16 wRe = PTR_MSGDRIVER->PostCommand(this, OSP_RSP_SELF_HANDLE, TYPE_TPMSG);
	return wRe;
}

u16 CUmcConfTemplateCtrl::DeleteConfTemplateReq( const u16 wConfTempID )   
{    
	CTpMsg *pkdvMsg = PTR_MSGDRIVER->GetKdvMsgPtr();
    pkdvMsg->SetEvent( evtp_DelConftemplate_Req );
	pkdvMsg->SetBody( &wConfTempID, sizeof(u16) );

	PrtMsg( evtp_DelConftemplate_Req, emEventTypeServerSend, "ConfTemplateID=%d", wConfTempID );

	PTR_SESSION->m_bRefresh = TRUE;

	//OSP_RSP_SELF_HANDLE:自己处理锁释放
    u16 wRe = PTR_MSGDRIVER->PostCommand(this, OSP_RSP_SELF_HANDLE,TYPE_TPMSG);
	return wRe;
}

u16 CUmcConfTemplateCtrl::DelAllConfTempReq()   
{
	CTpMsg *pkdvMsg = PTR_MSGDRIVER->GetKdvMsgPtr();
    pkdvMsg->SetEvent( ev_del_all_conftemp_req );

	PrtMsg( ev_del_all_conftemp_req, emEventTypeServerSend, "del all conftemp req" );

    u16 wRe = PTR_MSGDRIVER->PostCommand(this, ev_del_all_conftemp_rsp, TYPE_TPMSG);
	return wRe;
}

u16 CUmcConfTemplateCtrl::StartTemplateConfReq( const u16 wConfTemplateID ) 
{
	CTpMsg *pMsg = PTR_MSGDRIVER->GetKdvMsgPtr();
	pMsg->SetEvent( evtp_StartConfTemplate_Req );
	pMsg->SetBody( &wConfTemplateID, sizeof(u16) );

	PrtMsg( evtp_StartConfTemplate_Req, emEventTypeServerSend, "conftemplateID=%d", wConfTemplateID );

	u16 wRe = PTR_MSGDRIVER->PostCommand(this, evtp_StartConfTemplate_Ret, TYPE_TPMSG);
	return wRe;
}

u16 CUmcConfTemplateCtrl::OnUmcwebAddConftemplateReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	ptree pte = COwsCommon::GetPropertyTree(strData);
	std::string strConfName = COwsCommon::GetPropertyTreeVar( pte, "achConfName" );
	
	PrtMsg( ev_umcweb_AddConftemplate_req, emEventTypeClientRecv, "achConfName=%s", strConfName.c_str() );

	TTPConfTemplate tTemplate;
	bool bRet = ChangePtreeToTTPConfTemplate( pte, tTemplate );
	if ( bRet )
	{
		AddConfTemplateReq( tTemplate );
	}
		
	return NO_ERROR;
}

u16 CUmcConfTemplateCtrl::OnUmcwebUpdateConftemplateReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	ptree pte = COwsCommon::GetPropertyTree(strData);
	std::string strConfName = COwsCommon::GetPropertyTreeVar( pte, "achConfName" );
	
	PrtMsg( ev_umcweb_UpdateConftemplate_req, emEventTypeClientRecv, "achConfName=%s", strConfName.c_str() );

	TTPConfTemplate tTemplate;
	bool bRet = ChangePtreeToTTPConfTemplate( pte, tTemplate );
	if ( bRet )
	{
		ModifyConfTemplateReq( tTemplate );
	}

	return NO_ERROR;
}

u16 CUmcConfTemplateCtrl::OnUmcwebDelConftemplateReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	ptree pte = COwsCommon::GetPropertyTree(strData);
	std::string strConfTempID = COwsCommon::GetPropertyTreeVar( pte, "wConfTempID" );
	
	PrtMsg( ev_umcweb_DelConftemplate_req, emEventTypeClientRecv, "wConfTempID=%s", strConfTempID.c_str() );
	
	u16 wCurTmpId = atoi( strConfTempID.c_str() );	
	DeleteConfTemplateReq(wCurTmpId);
	
	return NO_ERROR;
}

u16 CUmcConfTemplateCtrl::OnUmcwebDelAllConftempReq(const boost::any& arg)
{
	PrtMsg( ev_umcweb_DelAllConftemp_req, emEventTypeClientRecv, "" );

	DelAllConfTempReq();

	return NO_ERROR;
}

u16 CUmcConfTemplateCtrl::OnUmcwebStartConfTemplateReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	ptree pte = COwsCommon::GetPropertyTree(strData);
	std::string strConfTempID = COwsCommon::GetPropertyTreeVar( pte, "wConfTempID" );
	
	PrtMsg( ev_umcweb_StartConfTemplate_req, emEventTypeClientRecv, "wConfTempID=%s", strConfTempID.c_str() );

	u16 wCurTmpId = atoi( strConfTempID.c_str() );
	StartTemplateConfReq(wCurTmpId);

	return NO_ERROR;
}

u16 CUmcConfTemplateCtrl::OnUmcwebRefreshConftempListNtyReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strSearch = COwsCommon::GetPropertyTreeVar( pt, "strSearch" );

	PrtMsg( ev_umcweb_RefreshConftempList_nty_req, emEventTypeClientRecv, "strSearch= %s", strSearch );

	std::string strJsonHead = "{\"event\":\"ev_umcweb_RefreshConftempList_nty_res\",\"items\":";
	std::vector<std::string> vecStrJson;
	
	std::vector<TTPConfTemplate>::iterator iter = m_vecConfTempList.begin();
	for ( ; iter != m_vecConfTempList.end(); iter++ )
	{
		std::string strConfName = iter->m_achConfName;
		if ( strSearch != "" )
		{
			if ( strConfName.find( strSearch.c_str() ) == -1 )
			{
				continue;
			}
		}

		std::string strHomeMeetingName;
		TEpAddrList tTeAddrList = iter->m_atEpList;
		strHomeMeetingName = tTeAddrList.m_tCnsList[0].m_tEpAddr.m_tAlias.m_abyAlias;
		if ( strHomeMeetingName.empty() )
		{
			strHomeMeetingName = tTeAddrList.m_tCnsList[0].m_tEpAddr.m_tE164.m_abyAlias;
		}

		std::string strTime;
		CUmcwebCommon::ChangeTimeToString( iter->m_tStartTime, strTime );

		char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
		sprintf( chItem, "{\"wConfTempID\":\"%d\",\"achConfName\":\"%s\",\"achStartTime\":\"%s\",\"nMeetNum\":\"%d\",\"achHomeMeetName\":\"%s\"}",
			iter->m_wID, iter->m_achConfName, strTime.c_str(), tTeAddrList.m_wNum, strHomeMeetingName.c_str() );
		
		vecStrJson.push_back(chItem);
	}
	
	std::string strJson = COwsCommon::CreateStringJson( strJsonHead, vecStrJson );
	
	PTR_FCGIPRINTF( strJson.c_str() );
	PrtMsg( ev_umcweb_RefreshConftempList_nty_res, emEventTypeClientSend, "strJson: %s", strJson.c_str() );

	return NO_ERROR;
}

u16 CUmcConfTemplateCtrl::OnUmcwebRefreshConftempInfoNtyReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	ptree pte = COwsCommon::GetPropertyTree(strData);
	std::string strConfTempID = COwsCommon::GetPropertyTreeVar( pte, "wConfTempID" );
	
	PrtMsg( ev_umcweb_RefreshConftempInfo_nty_req, emEventTypeClientRecv, "wConfTempID=%s", strConfTempID.c_str() );

	TTPConfTemplate tTemplate;
	u16 wConfTempID = atoi( strConfTempID.c_str() );
	bool bFind = FindConfTempInfoByID( wConfTempID, tTemplate );
	if ( bFind )
	{
		std::string strJsonHead = "{\"event\":\"ev_umcweb_RefreshConftempInfo_nty_res\",";

		std::string strTime;
		CUmcwebCommon::ChangeTimeToString( tTemplate.m_tStartTime, strTime );

		u16 wResNum = CComInterface::GetNeedBasNum(tTemplate);

		char chConfInfo[MAX_SQL_SENTENCE_LENTH] = {0};
		sprintf( chConfInfo, "\"wConfTempID\":\"%d\",\"achConfName\":\"%s\",\"achConfNum\":\"%s\",\"achStartTime\":\"%s\",\"nSingleRate\":\"%d\",\"nShowRate\":\"%d\",\"nUpBandWidth\":\"%d\",\"nDownBandWidth\":\"%d\",\"emEncryptModel\":\"%d\",\"achEncrypt\":\"%s\",\"nPollingTime\":\"%d\",\"wResNum\":\"%d\",\"wResUsedCount\":\"%d\",",
			tTemplate.m_wID, tTemplate.m_achConfName, tTemplate.m_achConfE164, strTime.c_str(), tTemplate.m_wConfBitRate, tTemplate.m_wHpDualBitRate, tTemplate.m_wUpBandWid,
			tTemplate.m_wDownBandWid, tTemplate.m_tEncrypt.m_emEncryptModel, tTemplate.m_tEncrypt.m_achEncKey, tTemplate.m_tTurnList.m_wInterval,
			wResNum, m_wResUsedCount );

		strJsonHead += chConfInfo;

		u16 wIndex = 0;
		char chFormatName[50] = {0};

		//主视频格式
		std::string strMainVideoRes = "\"atTpMainVideoRes\":[";
		for ( wIndex = 0; wIndex < tTemplate.m_wMainNum; wIndex++ )
		{
			std::string strMainFormat;
			CUmcwebCommon::ChangeMainVideoToName( tTemplate.m_atTpMainVideoRes[wIndex], strMainFormat );
			
			memset( chFormatName, 0, sizeof(chFormatName) );
			sprintf( chFormatName, "{\"chFormatName\":\"%s\"},", strMainFormat.c_str() );
			
			strMainVideoRes += chFormatName;
		}

		strMainVideoRes = strMainVideoRes.substr( 0, strMainVideoRes.length() - 1 );
		strMainVideoRes += "]";
		
		char chMainVideoNum[MAX_SQL_SENTENCE_LENTH] = {0};
		sprintf( chMainVideoNum, ",\"wMainNum\":\"%d\"", tTemplate.m_wMainNum );
		
		strMainVideoRes += chMainVideoNum;

		//辅视频格式
		std::string strMinorVideoRes = "\"atTpMinorVideoRes\":[";
		for ( wIndex = 0; wIndex < tTemplate.m_wMinorNum; wIndex++ )
		{
			std::string strMinorFormat;
			CUmcwebCommon::ChangeMinorVideoToName( tTemplate.m_atTpMinorVideoRes[wIndex], strMinorFormat );
			
			memset( chFormatName, 0, sizeof(chFormatName) );
			sprintf( chFormatName, "{\"chFormatName\":\"%s\"},", strMinorFormat.c_str() );
			
			strMinorVideoRes += chFormatName;
		}
		
		strMinorVideoRes = strMinorVideoRes.substr( 0, strMinorVideoRes.length() - 1 );
		strMinorVideoRes += "]";
		
		char chMinorVideoNum[MAX_SQL_SENTENCE_LENTH] = {0};
		sprintf( chMinorVideoNum, ",\"wMinorNum\":\"%d\"", tTemplate.m_wMinorNum );
		
		strMinorVideoRes += chMinorVideoNum;

		//音频格式
		std::string strAudFmt = "\"atAudFmt\":[";
		for ( wIndex = 0; wIndex < tTemplate.m_wAudFmtNum; wIndex++ )
		{
			std::string strAudioFormat;
			CUmcwebCommon::ChangeAudioFormatToName( tTemplate.m_atAudFmt[wIndex].m_emFormat, strAudioFormat );
			
			memset( chFormatName, 0, sizeof(chFormatName) );
			sprintf( chFormatName, "{\"chFormatName\":\"%s\"},", strAudioFormat.c_str() );
			
			strAudFmt += chFormatName;
		}
		
		strAudFmt = strAudFmt.substr( 0, strAudFmt.length() - 1 );
		strAudFmt += "]";
		
		char chAudioFormatNum[MAX_SQL_SENTENCE_LENTH] = {0};
		sprintf( chAudioFormatNum, ",\"wAudFmtNum\":\"%d\"", tTemplate.m_wAudFmtNum );
		
		strAudFmt += chAudioFormatNum;

		//拼接json字符串
		string strJson;
		strJson = strJsonHead + strMainVideoRes + "," + strMinorVideoRes + strAudFmt + "}";
		
		PrtMsg( ev_umcweb_RefreshConftempInfo_nty_res, emEventTypeClientSend, "strJson:%s", strJson.c_str() );
		PTR_FCGIPRINTF( strJson.c_str() );
	}
	else
	{
		PrtMsg( ev_umcweb_RefreshConftempInfo_nty_res, emEventTypeClientSend, "fail to find this conftemplate info" );
		PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_RefreshConftempInfo_nty_res\",\"wConfTempID\":\"%s\"}", "");
	}

	return NO_ERROR;
}

u16 CUmcConfTemplateCtrl::OnUmcwebRefreshConftempMeetNameListNtyReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	ptree pte = COwsCommon::GetPropertyTree(strData);
	std::string strConfTempID = COwsCommon::GetPropertyTreeVar( pte, "wConfTempID" );
	std::string strSearch = COwsCommon::GetPropertyTreeVar( pte, "strSearch" );
	
	PrtMsg( ev_umcweb_RefreshConftemp_MeetNameList_nty_req, emEventTypeClientRecv, "wConfTempID= %s, strSearch= %s",
		strConfTempID.c_str(), strSearch.c_str() );
	
	std::string strJsonHead = "{\"event\":\"ev_umcweb_RefreshConftemp_MeetNameList_nty_res\",\"items\":";
	std::vector<std::string> vecStrJson;
	
	TTPConfTemplate tTPConfTemplate;
	u16 wConfTempID = atoi( strConfTempID.c_str() );
	bool bFind = FindConfTempInfoByID( wConfTempID, tTPConfTemplate );	
	if ( bFind )
	{
		TEpAddrList tEpAddrList = tTPConfTemplate.m_atEpList;
		for ( u16 wIndex = 0; wIndex < tEpAddrList.m_wNum; wIndex++ )
		{
			TEpAddr tTeAddr = tEpAddrList.m_tCnsList[wIndex];
			
			in_addr tAddr;
			tAddr.s_addr = htonl( tTeAddr.m_tEpAddr.m_dwIP );

			std::string strMeetName = tTeAddr.m_tEpAddr.m_tAlias.m_abyAlias;
			std::string strE164 = tTeAddr.m_tEpAddr.m_tE164.m_abyAlias;
			std::string strMeetIp = inet_ntoa(tAddr);
			if ( strSearch != "" )
			{
				if ( strMeetName.find( strSearch.c_str() ) == -1 &&
					 strE164.find( strSearch.c_str() ) == -1 &&
					 strMeetIp.find( strSearch.c_str() ) == -1 )
				{
					continue;
				}
			}

			//1: 呼叫会场终端; 2: 呼叫监控终端
			u16 wCallType = 1;
			if ( tTeAddr.m_tEpAddr.m_bAliasIP )
			{
				wCallType = 2;
			}

			char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
			sprintf( chItem, "{\"epId\":\"%d\",\"calltype\":\"%d\",\"achMeetName\":\"%s\",\"achE164\":\"%s\",\"achMeetIp\":\"%s\"}",
				tTeAddr.m_wEpID, wCallType, tTeAddr.m_tEpAddr.m_tAlias.m_abyAlias, tTeAddr.m_tEpAddr.m_tE164.m_abyAlias, inet_ntoa(tAddr) );	
			vecStrJson.push_back(chItem);
		}
	}
	
	std::string strJson = COwsCommon::CreateStringJson( strJsonHead, vecStrJson );
	
	PTR_FCGIPRINTF( strJson.c_str() );
	PrtMsg( ev_umcweb_RefreshConftemp_MeetNameList_nty_res, emEventTypeClientSend, "strJson: %s", strJson.c_str() );
	
	return NO_ERROR;
}

u16 CUmcConfTemplateCtrl::OnUmcwebRefreshConftempPollingListNtyReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	ptree pte = COwsCommon::GetPropertyTree(strData);
	std::string strConfTempID = COwsCommon::GetPropertyTreeVar( pte, "wConfTempID" );

	PrtMsg( ev_umcweb_RefreshConftemp_PollingList_nty_req, emEventTypeClientRecv, "wConfTempID=%s", strConfTempID.c_str() );
	
	std::string strJsonHead = "{\"event\":\"ev_umcweb_RefreshConftemp_PollingList_nty_res\",";
	std::vector<std::string> vecStrJson;

	TTPConfTemplate tTPConfTemplate;
	u16 wConfTempID = atoi( strConfTempID.c_str() );
	bool bFind = FindConfTempInfoByID( wConfTempID, tTPConfTemplate );

	char chPollingInfo[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chPollingInfo, "\"bPollOn\":\"%d\",\"wInterval\":\"%d\",\"items\":",
		tTPConfTemplate.m_tTurnList.m_bPollOn, tTPConfTemplate.m_tTurnList.m_wInterval );
	
	strJsonHead += chPollingInfo;

	if ( bFind )
	{
		for ( u16 wIndex = 0; wIndex < tTPConfTemplate.m_tTurnList.m_wNum; wIndex++ )
		{
			u16 wPollingId = tTPConfTemplate.m_tTurnList.m_awList[wIndex];
			PrtMsg( "wPollingId = %d\n", wPollingId );
			if ( 0 == wPollingId )
			{
				continue;
			}

			TTpCallAddr tTpCallAddr;
			FindMeetInfoByID( tTPConfTemplate, wPollingId, tTpCallAddr );

			in_addr tAddr;
			tAddr.s_addr = htonl( tTpCallAddr.m_dwIP );

			PrtMsg( "wPollingId = %d, name = %s, num = %s, ip = %s\n",
				wPollingId, tTpCallAddr.m_tAlias.m_abyAlias, tTpCallAddr.m_tE164.m_abyAlias, inet_ntoa(tAddr) );

			char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
			sprintf( chItem, "{\"epId\":\"%d\",\"achMeetName\":\"%s\",\"achE164\":\"%s\",\"achMeetIp\":\"%s\"}",
				wPollingId, tTpCallAddr.m_tAlias.m_abyAlias, tTpCallAddr.m_tE164.m_abyAlias, inet_ntoa(tAddr) );	
			vecStrJson.push_back(chItem);
		}
	}

	std::string strJson = COwsCommon::CreateStringJson( strJsonHead, vecStrJson );
	
	PTR_FCGIPRINTF( strJson.c_str() );
	PrtMsg( ev_umcweb_RefreshConftemp_PollingList_nty_res, emEventTypeClientSend, "strJson: %s", strJson.c_str() );

	return NO_ERROR;
}

u16 CUmcConfTemplateCtrl::OnUmcwebRefreshConftempDiscussListNtyReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	ptree pte = COwsCommon::GetPropertyTree(strData);
	std::string strConfTempID = COwsCommon::GetPropertyTreeVar( pte, "wConfTempID" );

	PrtMsg( ev_umcweb_RefreshConftemp_DiscussList_nty_req, emEventTypeClientRecv, "wConfTempID=%s", strConfTempID.c_str() );
	
	std::string strJsonHead = "{\"event\":\"ev_umcweb_RefreshConftemp_DiscussList_nty_res\",";
	std::vector<std::string> vecStrJson;

	TTPConfTemplate tTPConfTemplate;
	u16 wConfTempID = atoi( strConfTempID.c_str() );
	bool bFind = FindConfTempInfoByID( wConfTempID, tTPConfTemplate );

	char chDiscussInfo[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chDiscussInfo, "\"bDiscussOn\":\"%d\",\"items\":", tTPConfTemplate.m_atAuxMixList.m_bAudMixOn );
	
	strJsonHead += chDiscussInfo;

	if ( bFind )
	{
		for ( u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++ )
		{
			u16 wDiscussId = tTPConfTemplate.m_atAuxMixList.m_awList[wIndex];
			PrtMsg( "wDiscussId = %d\n", wDiscussId );

			TTpCallAddr tTpCallAddr;
			FindMeetInfoByID( tTPConfTemplate, wDiscussId, tTpCallAddr );

			in_addr tAddr;
			tAddr.s_addr = htonl( tTpCallAddr.m_dwIP );

			PrtMsg( "wDiscussId = %d, name = %s, num = %s, ip = %s\n",
				wDiscussId, tTpCallAddr.m_tAlias.m_abyAlias, tTpCallAddr.m_tE164.m_abyAlias, inet_ntoa(tAddr) );

			char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
			sprintf( chItem, "{\"epId\":\"%d\",\"achMeetName\":\"%s\",\"achE164\":\"%s\",\"achMeetIp\":\"%s\"}",
				wDiscussId, tTpCallAddr.m_tAlias.m_abyAlias, tTpCallAddr.m_tE164.m_abyAlias, inet_ntoa(tAddr) );	
			vecStrJson.push_back(chItem);
		}
	}
	
	std::string strJson = COwsCommon::CreateStringJson( strJsonHead, vecStrJson );
	
	PTR_FCGIPRINTF( strJson.c_str() );
	PrtMsg( ev_umcweb_RefreshConftemp_DiscussList_nty_res, emEventTypeClientSend, "strJson: %s", strJson.c_str() );

	return NO_ERROR;
}

u16 CUmcConfTemplateCtrl::OnUmcwebConfBasUsedNtyReq(const boost::any& arg)
{	
	PrtMsg( ev_umcweb_ConfBasUsed_nty_req, emEventTypeClientRecv, "req Conf Bas Used" );

	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_ConfBasUsed_nty_res\",\"wResUsedCount\":\"%d\"}", m_wResUsedCount );

	PrtMsg( ev_umcweb_ConfBasUsed_nty_res, emEventTypeClientSend, "wResUsedCount: %d", m_wResUsedCount );
	
	return NO_ERROR;
}

u16 CUmcConfTemplateCtrl::OnUmcwebConfmngListconfbookGetReq(const boost::any& arg)
{	
	PrtMsg( ev_umcweb_confmng_listconfbook_get_req, emEventTypeClientRecv, "" );
	
	std::string strJson;

	vector<TTPConfTemplate> vecListConfbook;

	vector<TTPConfTemplate>::iterator it = m_vecConfTempList.begin();
	for ( ; it != m_vecConfTempList.end(); it++ )
	{
		TTPConfTemplate tTPConfTemplate = *it;
		if ( tTPConfTemplate.m_tStartTime == 0 )
		{
			continue;
		}
		vecListConfbook.push_back(tTPConfTemplate);
	}
	
	if ( vecListConfbook.size() == 0 )
	{
		strJson = "{\"event\":\"ev_umcweb_confmng_listconfbook_get_res\",\"count\":\"0\"}";
	}
	else
	{
		string strJsonHead = "{\"event\":\"ev_umcweb_confmng_listconfbook_get_res\",\"items\":";
		
		vector<string> vecStrJson;
		
		vector<TTPConfTemplate>::iterator it = vecListConfbook.begin();
		for ( ; it != vecListConfbook.end(); it++ )
		{
			TTPConfTemplate tConfinfo = *it;
			
			int nId = tConfinfo.m_wID;
			string strConfName = tConfinfo.m_achConfName;
			
			char str_starttime[100];
			struct tm *start_time = NULL;
			start_time = localtime(&tConfinfo.m_tStartTime);
			strftime(str_starttime, sizeof(str_starttime), "%Y-%m-%d %H:%M:%S", start_time);

			TTpCallAddr tTpCallAddr;
			FindMeetInfoByID( tConfinfo, tConfinfo.m_wDefaultChairMan, tTpCallAddr );

			string strChair = tTpCallAddr.m_tAlias.m_abyAlias;
			if ( strChair.empty() )
			{
				strChair = tTpCallAddr.m_tE164.m_abyAlias;
			}			
			
			int nRoom = tConfinfo.m_atEpList.m_wNum;
			
			time_t now;
			struct tm *timenow;
			time(&now);
			timenow = localtime(&now);
			
			int nInterval = tConfinfo.m_tStartTime - now;
			
			char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
			sprintf( chItem, "{\"confId\":\"%d\",\"confName\":\"%s\",\"startTime\":\"%s\",\"chairroomName\":\"%s\",\"roomNumber\":\"%d\",\"interval\":\"%d\"}"
				, nId, strConfName.c_str(), str_starttime, strChair.c_str(), nRoom, nInterval );
			
			vecStrJson.push_back(chItem);
		}
		
		strJson = COwsCommon::CreateStringJson( strJsonHead, vecStrJson );
	}
	
	PTR_FCGIPRINTF( strJson.c_str() );
	PrtMsg( ev_umcweb_confmng_listconfbook_get_res, emEventTypeClientSend, "strJson:%s", strJson.c_str() );
	
	return NO_ERROR;
}

u16 CUmcConfTemplateCtrl::OnUmcwebCheckConftempRepeatReq(const boost::any& arg)
{	
	std::string strData = boost::any_cast<std::string>(arg);
	ptree pte = COwsCommon::GetPropertyTree(strData);
	std::string strConfTempID = COwsCommon::GetPropertyTreeVar( pte, "wConfTempID" );
	std::string strConfName = COwsCommon::GetPropertyTreeVar( pte, "achConfName" );
	std::string strConfNum = COwsCommon::GetPropertyTreeVar( pte, "achConfNum" );

	PrtMsg( ev_umcweb_CheckConftempRepeat_req, emEventTypeClientRecv, "wConfTempID= %s, achConfName= %s, achConfNum= %s",
		strConfTempID.c_str(), strConfName.c_str(), strConfNum.c_str() );

	u16 wConfTempID = atoi( strConfTempID.c_str() );

	TTPConfTemplate tTPConfTemplate;
	std::string strCurTmpName, strCurTmpNum;
	if ( wConfTempID > 0 )		//编辑
	{
		bool bRet = FindConfTempInfoByID( wConfTempID, tTPConfTemplate );
		if ( !bRet )
		{
			PrtMsg( "fail to find this template, wConfTempID= %d", wConfTempID );
			PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_CheckConftempRepeat_res\",\"wNameRet\":\"%d\",\"wNumRet\":\"%d\"}", 2, 2 );
			PrtMsg( ev_umcweb_CheckConftempRepeat_res, emEventTypeClientSend, "wNameRet= %d, wNumRet= %d(0:noRepeat; 1:Repeat; 2:fail)", 2, 2 );
			return NO_ERROR;
		}

		strCurTmpName = tTPConfTemplate.m_achConfName;
		strCurTmpNum = tTPConfTemplate.m_achConfE164;
	}

	std::vector<TTPConfTemplate>::iterator iter;

	u16 wNameRet = 0;	//0: noRepeat; 1: Repeat; 2: fail
	for( iter = m_vecConfTempList.begin(); iter != m_vecConfTempList.end(); iter++ )
	{
		if( wConfTempID > 0 )	//编辑
		{
			if ( strcmp( iter->m_achConfName, strConfName.c_str() ) == 0 && 
				 strcmp( strCurTmpName.c_str(), strConfName.c_str() ) != 0 )
			{
				wNameRet = 1;
				break;
			}
		}
		else					//新建
		{
			if ( strcmp( iter->m_achConfName, strConfName.c_str() ) == 0 )
			{
				wNameRet = 1;
				break;
			}
		}
	}

	u16 wNumRet = 0;	//0: noRepeat; 1: Repeat; 2: fail
	if ( !strConfNum.empty() )
	{
		for( iter = m_vecConfTempList.begin(); iter != m_vecConfTempList.end(); iter++ )
		{
			if ( strcmp( iter->m_achConfE164, strConfNum.c_str() ) == 0 &&
				strcmp( strCurTmpNum.c_str(), strConfNum.c_str() ) != 0 )
			{
				wNumRet = 1;
				break;
			}
		}
	}

	
	PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_CheckConftempRepeat_res\",\"wNameRet\":\"%d\",\"wNumRet\":\"%d\"}", wNameRet, wNumRet );	
	PrtMsg( ev_umcweb_CheckConftempRepeat_res, emEventTypeClientSend, "wNameRet= %d, wNumRet= %d(0:noRepeat; 1:Repeat; 2:fail)", wNameRet, wNumRet );
	
	return NO_ERROR;
}

bool CUmcConfTemplateCtrl::ChangePtreeToTTPConfTemplate( /*const*/ ptree& pte, TTPConfTemplate& tTPConfTemplate )
{
	tTPConfTemplate.Clear();

	std::string strConfTempID = COwsCommon::GetPropertyTreeVar( pte, "wConfTempID" );
	std::string strConfName = COwsCommon::GetPropertyTreeVar( pte, "achConfName" );
	std::string strConfNum = COwsCommon::GetPropertyTreeVar( pte, "achConfNum" );
	std::string strStartTime = COwsCommon::GetPropertyTreeVar( pte, "achStartTime" );
	//std::string strArrTpMainVideoRes = COwsCommon::GetPropertyTreeVar( pte, "atTpMainVideoRes" );
	std::string strMainNum = COwsCommon::GetPropertyTreeVar( pte, "wMainNum" );
	//std::string strArrTpMinorVideoRes = COwsCommon::GetPropertyTreeVar( pte, "atTpMinorVideoRes" );
	std::string strMinorNum = COwsCommon::GetPropertyTreeVar( pte, "wMinorNum" );
	//std::string strArrAudFmt = COwsCommon::GetPropertyTreeVar( pte, "atAudFmt" );
	std::string strAudFmtNum = COwsCommon::GetPropertyTreeVar( pte, "wAudFmtNum" );
	std::string strSingleRate = COwsCommon::GetPropertyTreeVar( pte, "nSingleRate" );
	std::string strShowRate = COwsCommon::GetPropertyTreeVar( pte, "nShowRate" );
	std::string strUpBandWidth = COwsCommon::GetPropertyTreeVar( pte, "nUpBandWidth" );
	std::string strDownBandWidth = COwsCommon::GetPropertyTreeVar( pte, "nDownBandWidth" );
	std::string strEncryptModel = COwsCommon::GetPropertyTreeVar( pte, "emEncryptModel" );
	std::string strEncrypt = COwsCommon::GetPropertyTreeVar( pte, "achEncrypt" );
	std::string strArrMeetList = COwsCommon::GetPropertyTreeVar( pte, "arrMeetList" );
	std::string strMeetCount = COwsCommon::GetPropertyTreeVar( pte, "wMeetCount" );
	std::string strPollOn = COwsCommon::GetPropertyTreeVar( pte, "bPollOn" );
	std::string strInterval = COwsCommon::GetPropertyTreeVar( pte, "wInterval" );
	//std::string strArrPolling = COwsCommon::GetPropertyTreeVar( pte, "arrPolling" );
	std::string strPollingCount = COwsCommon::GetPropertyTreeVar( pte, "wPollingCount" );
	std::string strDiscussOn = COwsCommon::GetPropertyTreeVar( pte, "bDiscussOn" );
	//std::string strArrDiscuss = COwsCommon::GetPropertyTreeVar( pte, "arrDiscuss" );
	std::string strDiscussCount = COwsCommon::GetPropertyTreeVar( pte, "wDiscussCount" );

	//模板ID
	u16 wConfTempID = atoi( strConfTempID.c_str() );
	if ( wConfTempID > 0 )
	{
		tTPConfTemplate.m_wID = wConfTempID;		//编辑
	}
	else
	{
		tTPConfTemplate.m_wID = TP_INVALID_INDEX;	//新建
	}

	//模板名称、号码
	sprintf( tTPConfTemplate.m_achConfName, "%s", strConfName.c_str() );
	sprintf( tTPConfTemplate.m_achConfE164, "%s", strConfNum.c_str() );

	//开始时间(0为即时会议)
	time_t starttime = 0;
	CUmcwebCommon::ChangeStringToTime( strStartTime, starttime );
	tTPConfTemplate.m_tStartTime = starttime;

	//单屏码率、演示码率
	tTPConfTemplate.m_wConfBitRate = atoi( strSingleRate.c_str() );
	tTPConfTemplate.m_wBpConfBitRate = atoi( strSingleRate.c_str() );
	
	tTPConfTemplate.m_wHpDualBitRate = atoi( strShowRate.c_str() );
	tTPConfTemplate.m_wBpDualBitRate = atoi( strShowRate.c_str() );

	//上行带宽、下行带宽
	tTPConfTemplate.m_wUpBandWid = atoi( strUpBandWidth.c_str() );
	tTPConfTemplate.m_wDownBandWid = atoi( strDownBandWidth.c_str() );

	//模板加密信息
	if ( "2" == strEncryptModel.c_str() )		//开启AES加密
	{
		tTPConfTemplate.m_tEncrypt.m_emEncryptModel = emTPEncryptTypeAES;

		if ( "" == strEncrypt.c_str() )	//默认AES密钥
		{
			tTPConfTemplate.m_tEncrypt.m_byKeyLen = 0;
		}
		else							//自定义AES密钥
		{
			sprintf( tTPConfTemplate.m_tEncrypt.m_achEncKey, "%s", strEncrypt.c_str() );
		}
	}
	else										//关闭AES加密
	{
		tTPConfTemplate.m_tEncrypt.m_emEncryptModel = emTPEncryptTypeNone;
	}

	//会议格式、演示格式、音频格式
	tTPConfTemplate.m_wMainNum = atoi( strMainNum.c_str() );
	tTPConfTemplate.m_wMinorNum = atoi( strMinorNum.c_str() );
	tTPConfTemplate.m_wAudFmtNum = atoi( strAudFmtNum.c_str() );
	if ( tTPConfTemplate.m_wMainNum < 1 || tTPConfTemplate.m_wMinorNum < 1 || tTPConfTemplate.m_wAudFmtNum < 1 )
	{
		PrtMsg( "error: wMainNum = %s, wMinorNum = %s, wAudFmtNum = %s\n", strMainNum.c_str(), strMinorNum.c_str(), strAudFmtNum.c_str() );
		return false;
	}

	u16 wVideoIndex = 0;
	vector<ptree> vecPteTpMainVideoRes = COwsCommon::GetPropertyTreeChildren( pte, "atTpMainVideoRes" );
	for ( wVideoIndex = 0; wVideoIndex < tTPConfTemplate.m_wMainNum; wVideoIndex++ )
	{
		std::string strMainVideo = COwsCommon::GetPropertyTreeVar( vecPteTpMainVideoRes[wVideoIndex], "chFormatName" );
		PrtMsg( "strMainVideo = %s\n", strMainVideo.c_str() );
		ChangeNameToMainVideo( wVideoIndex, strMainVideo, tTPConfTemplate );
	}

	vector<ptree> vecPteTpMinorVideoRes = COwsCommon::GetPropertyTreeChildren( pte, "atTpMinorVideoRes" );
	for ( wVideoIndex = 0; wVideoIndex < tTPConfTemplate.m_wMinorNum; wVideoIndex++ )
	{
		std::string strMinorVideo = COwsCommon::GetPropertyTreeVar( vecPteTpMinorVideoRes[wVideoIndex], "chFormatName" );
		PrtMsg( "strMinorVideo = %s\n", strMinorVideo.c_str() );
		ChangeNameToMinorVideo( wVideoIndex, strMinorVideo, tTPConfTemplate );
	}

	vector<ptree> vecPteAudFmt = COwsCommon::GetPropertyTreeChildren( pte, "atAudFmt" );
	for ( wVideoIndex = 0; wVideoIndex < tTPConfTemplate.m_wAudFmtNum; wVideoIndex++ )
	{
		std::string strAudioFormat = COwsCommon::GetPropertyTreeVar( vecPteAudFmt[wVideoIndex], "chFormatName" );
		PrtMsg( "strAudioFormat = %s\n", strAudioFormat.c_str() );
		ChangeNameToAudioFormat( wVideoIndex, strAudioFormat, tTPConfTemplate );
	}

	u16 wCheckResNum = CComInterface::GetNeedBasNum(tTPConfTemplate);
	if ( wCheckResNum > m_wResUsedCount )
	{
		//媒体资源数大于选中资源数，媒体资源数不足
		PrtMsg( "error: wCheckResNum = %d, m_wResUsedCount = %d, wCheckResNum > m_wResUsedCount\n", wCheckResNum, m_wResUsedCount );
		return false;
	}

	u16 wIndex = 0;
	//与会会场
	tTPConfTemplate.m_wDefaultChairMan = 0; //目前暂设置主席id为0
	
	u16 wMeetCount = atoi( strMeetCount.c_str() );
	
	vector<ptree> vecPteMeetList = COwsCommon::GetPropertyTreeChildren( pte, "arrMeetList" );
	for ( wIndex = 0; wIndex < wMeetCount; wIndex++ )
	{
		std::string strMeetID = COwsCommon::GetPropertyTreeVar( vecPteMeetList[wIndex], "epId" );
		std::string strCallType = COwsCommon::GetPropertyTreeVar( vecPteMeetList[wIndex], "calltype" );
		std::string strMeetName = COwsCommon::GetPropertyTreeVar( vecPteMeetList[wIndex], "achMeetName" );
		std::string strMeetNum = COwsCommon::GetPropertyTreeVar( vecPteMeetList[wIndex], "achE164" );
		std::string strMeetIp = COwsCommon::GetPropertyTreeVar( vecPteMeetList[wIndex], "achMeetIp" );
		
		PrtMsg( "strMeetID = %s, strMeetName = %s, strMeetNum = %s, strMeetIp = %s\n",
			strMeetID.c_str(), strMeetName.c_str(), strMeetNum.c_str(), strMeetIp.c_str() );

		TTpCallAddr tTpCallAddr;
		tTpCallAddr.m_tAlias.SetAlias( tp_Alias_h323, strMeetName.c_str() );
		tTpCallAddr.m_tE164.SetAlias( tp_Alias_e164, strMeetNum.c_str() );
		tTpCallAddr.m_dwIP = ntohl( inet_addr( strMeetIp.c_str() ) );
		//1: 呼叫会场终端; 2: 呼叫监控终端
		tTpCallAddr.m_bAliasIP = FALSE;
		if ( strcmp( "2", strCallType.c_str() ) == 0 )
		{
			tTpCallAddr.m_bAliasIP = TRUE;
		}

		EmConfAddEpRet emAddFlag = tTPConfTemplate.m_atEpList.Add( tTpCallAddr );
		if ( TP_ConfAddEpRet_Success != emAddFlag )
		{
			PrtMsg( "error: m_atEpList.Add() - emAddFlag : %d (1:TP_ConfAddEpRet_Success; 2:TP_ConfAddEpRet_MaxNum; 3:TP_ConfAddEpRet_AliasReapeat; 4:TP_ConfAddEpRet_ParamError)", emAddFlag );
			return false;
		}
	}

	//会议轮询
	u16 bPollOn = atoi( strPollOn.c_str() );
	tTPConfTemplate.m_tTurnList.m_bPollOn = TRUE;
	if ( 0 == bPollOn )
	{
		tTPConfTemplate.m_tTurnList.m_bPollOn = FALSE;
	}
	tTPConfTemplate.m_tTurnList.SetInterval( atoi(strInterval.c_str()) );
	
	u16 wPollingCount = atoi( strPollingCount.c_str() );
	tTPConfTemplate.m_tTurnList.m_wNum = wPollingCount;

	vector<ptree> vecPtePollingList = COwsCommon::GetPropertyTreeChildren( pte, "arrPolling" );
	for ( wIndex = 0; wIndex < wPollingCount; wIndex++ )
	{
		std::string strEpId = COwsCommon::GetPropertyTreeVar( vecPtePollingList[wIndex], "epId" );
		u16 wPollingId = atoi( strEpId.c_str() );
		tTPConfTemplate.m_tTurnList.m_awList[wIndex] = wPollingId;

		//test:
		std::string strMeetName = COwsCommon::GetPropertyTreeVar( vecPtePollingList[wIndex], "achMeetName" );
		std::string strMeetNum = COwsCommon::GetPropertyTreeVar( vecPtePollingList[wIndex], "achE164" );
		std::string strMeetIp = COwsCommon::GetPropertyTreeVar( vecPtePollingList[wIndex], "achMeetIp" );
		PrtMsg( "pollinglist: wPollingId = %d, strMeetName = %s, strMeetNum = %s, strMeetIp = %s\n",
			wPollingId, strMeetName.c_str(), strMeetNum.c_str(), strMeetIp.c_str() );
	}

	//会议讨论
	u16 bDiscussOn = atoi( strDiscussOn.c_str() );
	tTPConfTemplate.m_atAuxMixList.m_bAudMixOn = FALSE;
	if ( 1 == bDiscussOn )
	{
		tTPConfTemplate.m_atAuxMixList.m_bAudMixOn = TRUE;
	}
	
	u16 wDiscussCount = atoi( strDiscussCount.c_str() );
	
	vector<ptree> vecPteDiscussList = COwsCommon::GetPropertyTreeChildren( pte, "arrDiscuss" );
	for ( wIndex = 0; wIndex < wDiscussCount; wIndex++ )
	{
		std::string strEpId = COwsCommon::GetPropertyTreeVar( vecPteDiscussList[wIndex], "epId" );
		u16 wDiscussId = atoi( strEpId.c_str() );
		tTPConfTemplate.m_atAuxMixList.m_awList[wIndex] = wDiscussId;
		
		//test:
		std::string strMeetName = COwsCommon::GetPropertyTreeVar( vecPteDiscussList[wIndex], "achMeetName" );
		std::string strMeetNum = COwsCommon::GetPropertyTreeVar( vecPteDiscussList[wIndex], "achE164" );
		std::string strMeetIp = COwsCommon::GetPropertyTreeVar( vecPteDiscussList[wIndex], "achMeetIp" );
		PrtMsg( "discusslist: wDiscussId = %d, strMeetName = %s, strMeetNum = %s, strMeetIp =%s\n",
			wDiscussId, strMeetName.c_str(), strMeetNum.c_str(), strMeetIp.c_str() );
	}
	
	return true;
}

bool CUmcConfTemplateCtrl::FindConfTempInfoByID( const u16 wID, TTPConfTemplate& tTPConfTemplate )
{
	bool bFind = false;
	tTPConfTemplate.Clear();
	
	if ( TP_INVALID_INDEX == wID )
	{
		return false;
	}
	
	std::vector<TTPConfTemplate>::iterator iter = m_vecConfTempList.begin();
	for( ; iter != m_vecConfTempList.end(); iter++ )
	{
		if ( wID == iter->m_wID )
		{
			tTPConfTemplate = *iter;
			bFind = true;
			break;
		}
	}
	
	return bFind;
}

// u16 CUmcConfTemplateCtrl::FindMeetIDByName( const TTPConfTemplate& tTPConfTemplate, const std::string& strMeetName, const std::string& strMeetNum )
// {
// 	u16 wEpID = TP_INVALID_INDEX;
// 
// 	if ( strMeetName == "" && strMeetNum == "" )
// 	{
// 		return wEpID;
// 	}
// 
// 	TEpAddrList tEpAddrList = tTPConfTemplate.m_atEpList;
// 	for ( u16 wIndex = 0; wIndex < tEpAddrList.m_wNum; wIndex++ )
// 	{
// 		TEpAddr tEpAddr = tEpAddrList.m_tCnsList[wIndex];
// 
// 		if ( strcmp( tEpAddr.m_tEpAddr.m_tAlias.m_abyAlias, strMeetName.c_str() ) == 0 && 
// 			 strcmp( tEpAddr.m_tEpAddr.m_tE164.m_abyAlias, strMeetNum.c_str() ) == 0 )
// 		{
// 			wEpID = tEpAddr.m_wEpID;
// 			break;
// 		}
// 	}
// 	
// 	return wEpID;
// }

bool CUmcConfTemplateCtrl::FindMeetInfoByID( const TTPConfTemplate& tTPConfTemplate, const u16 wEpID, TTpCallAddr& tTpCallAddr )
{
	bool bFind = false;
	tTpCallAddr.Clear();

	if ( TP_INVALID_INDEX == wEpID )
	{
		return bFind;
	}

	TEpAddrList tEpAddrList = tTPConfTemplate.m_atEpList;
	for ( u16 wIndex = 0; wIndex < tEpAddrList.m_wNum; wIndex++ )
	{
		TEpAddr tEpAddr = tEpAddrList.m_tCnsList[wIndex];
		
		if ( wEpID == tEpAddr.m_wEpID )
		{
			tTpCallAddr = tEpAddr.m_tEpAddr;
			bFind = true;
			break;
		}
	}

	return bFind;
}

//格式名称(std::string) - 主视频格式(TUmsVidFormat) 转换
void CUmcConfTemplateCtrl::ChangeNameToMainVideo( const u16 wMainCheckCount, const std::string& strFormatName, TTPConfTemplate& tTPConfTemplate )
{
	if ( wMainCheckCount >= TP_CONF_MAX_MAIN_VIDEO_RES_NUM )
	{
		return;
	}

	//主视频格式
	if ( strcmp( "HP 1080P@50/60fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_emRes = emTPVHD1080p1920x1080;
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_wFrameRate = 60;
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_emQualityLvl = emTPH264HP;
	}

	if ( strcmp( "HP 1080P@25/30fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_emRes = emTPVHD1080p1920x1080;
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_wFrameRate = 30;
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_emQualityLvl = emTPH264HP;
	}

	if ( strcmp( "HP 720P@50/60fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_emRes = emTPVHD720p1280x720;
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_wFrameRate = 60;
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_emQualityLvl = emTPH264HP;
	}

	if ( strcmp( "HP 720P@25/30fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_emRes = emTPVHD720p1280x720;
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_wFrameRate = 30;
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_emQualityLvl = emTPH264HP;
	}

	if ( strcmp( "BP 1080P@50/60fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_emRes = emTPVHD1080p1920x1080;
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_wFrameRate = 60;
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_emQualityLvl = emTPH264BP;
	}

	if ( strcmp( "BP 1080P@25/30fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_emRes = emTPVHD1080p1920x1080;
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_wFrameRate = 30;
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_emQualityLvl = emTPH264BP;
	}

	if ( strcmp( "BP 720P@50/60fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_emRes = emTPVHD720p1280x720;
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_wFrameRate = 60;
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_emQualityLvl = emTPH264BP;
	}

	if ( strcmp( "BP 720P@25/30fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_emRes = emTPVHD720p1280x720;
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_wFrameRate = 30;
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_emQualityLvl = emTPH264BP;
	}

	if ( strcmp( "BP 4CIF@25fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_emRes = emTPV4CIF;
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_wFrameRate = 25;
		tTPConfTemplate.m_atTpMainVideoRes[wMainCheckCount].m_emQualityLvl = emTPH264BP;
	}

	tTPConfTemplate.m_wMainNum = wMainCheckCount + 1;
}

//格式名称(std::string) - 辅视频格式(TUmsVidFormat) 转换
void CUmcConfTemplateCtrl::ChangeNameToMinorVideo( const u16 wMinorCheckCount, const std::string& strFormatName, TTPConfTemplate& tTPConfTemplate )
{
	if ( wMinorCheckCount >= TP_CONF_MAX_MINOR_VIDEO_RES_NUM )
	{
		return;
	}
	
	//辅视频格式
	if ( strcmp( "HP 1080P@50/60fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emRes = emTPVHD1080p1920x1080;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_wFrameRate = 60;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emQualityLvl = emTPH264HP;
	}
	
	if ( strcmp( "HP 1080P@25/30fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emRes = emTPVHD1080p1920x1080;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_wFrameRate = 30;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emQualityLvl = emTPH264HP;
	}
	
	if ( strcmp( "HP 720P@50/60fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emRes = emTPVHD720p1280x720;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_wFrameRate = 60;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emQualityLvl = emTPH264HP;
	}
	
	if ( strcmp( "HP 720P@25/30fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emRes = emTPVHD720p1280x720;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_wFrameRate = 30;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emQualityLvl = emTPH264HP;
	}
	
	if ( strcmp( "BP 1080P@50/60fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emRes = emTPVHD1080p1920x1080;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_wFrameRate = 60;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emQualityLvl = emTPH264BP;
	}
	
	if ( strcmp( "BP 1080P@25/30fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emRes = emTPVHD1080p1920x1080;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_wFrameRate = 30;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emQualityLvl = emTPH264BP;
	}
	
	if ( strcmp( "BP 720P@50/60fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emRes = emTPVHD720p1280x720;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_wFrameRate = 60;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emQualityLvl = emTPH264BP;
	}
	
	if ( strcmp( "BP 720P@25/30fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emRes = emTPVHD720p1280x720;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_wFrameRate = 30;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emQualityLvl = emTPH264BP;
	}
	
	if ( strcmp( "BP 4CIF@25fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emRes = emTPV4CIF;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_wFrameRate = 25;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emQualityLvl = emTPH264BP;
	}

	if ( strcmp( "BP UXGA@60fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emRes = emTPVGA1600x1200;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_wFrameRate = 60;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emQualityLvl = emTPH264BP;
	}
	
	if ( strcmp( "BP WXGA@30fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emRes = emTPVGA1280x800;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_wFrameRate = 30;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emQualityLvl = emTPH264BP;	
	}
	
	if ( strcmp( "BP SXGA@30fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emRes = emTPVGA1280x1024;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_wFrameRate = 30;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emQualityLvl = emTPH264BP;	
	}
	
	if ( strcmp( "BP WXGA@5fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emRes = emTPVGA1280x800;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_wFrameRate = 5;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emQualityLvl = emTPH264BP;
	}
	
	if ( strcmp( "BP SXGA@5fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emRes = emTPVGA1280x1024;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_wFrameRate = 5;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emQualityLvl = emTPH264BP;	
	}
	
	if ( strcmp( "BP XGA@5fps", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emRes = emTPVGA1024x768;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_wFrameRate = 5;
		tTPConfTemplate.m_atTpMinorVideoRes[wMinorCheckCount].m_emQualityLvl = emTPH264BP;	
	}
	
	tTPConfTemplate.m_wMinorNum = wMinorCheckCount + 1;
}

//格式名称(std::string) - 音频格式(EmTpAudioFormat) 转换
void CUmcConfTemplateCtrl::ChangeNameToAudioFormat( const u16 wAudFmtNum, const std::string& strFormatName, TTPConfTemplate& tTPConfTemplate )
{
	if ( wAudFmtNum >= TP_CONF_MAX_AUD_FMT_NUM )
	{
		return;
	}
	
	if ( strcmp( "MPEG4 AAC-LD单声道", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atAudFmt[wAudFmtNum].m_emFormat = emTPAMpegAACLD;
	} 
	else if ( strcmp( "G.711A", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atAudFmt[wAudFmtNum].m_emFormat = emTPAG711a;
	}
	else if ( strcmp( "G.711U", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atAudFmt[wAudFmtNum].m_emFormat = emTPAG711u;
	}
	else if ( strcmp( "G.719", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atAudFmt[wAudFmtNum].m_emFormat = emTPAG719;
	}
	else if ( strcmp( "G.722.1 Annex C Polycom Siren14", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atAudFmt[wAudFmtNum].m_emFormat = emTPAG7221;
	}
	else if ( strcmp( "MP3", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atAudFmt[wAudFmtNum].m_emFormat = emTPAMP3;
	}
	else if ( strcmp( "MPEG4 AAC-LC单声道", strFormatName.c_str() ) == 0 )
	{
		tTPConfTemplate.m_atAudFmt[wAudFmtNum].m_emFormat = emTPAMpegAACLC;
	}

	tTPConfTemplate.m_wAudFmtNum = wAudFmtNum + 1;
}
