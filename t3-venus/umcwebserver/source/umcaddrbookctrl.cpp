#include "umcglodef.h"
#include "umcaddrbookctrl.h"

CUmcAddrbookCtrl::CUmcAddrbookCtrl()
{
	m_bIsEndSip = FALSE;
	m_bIsEndGk = FALSE;

	BuildEventsMap();
}

CUmcAddrbookCtrl::~CUmcAddrbookCtrl()
{
    ClearData();
}

void  CUmcAddrbookCtrl::BuildEventsMap()
{
	REG_PFUN( ev_umsGetRegInfo_UmsRspEx, &CUmcAddrbookCtrl::OnAddrbookGlobleUmsRsp );
	REG_PFUN( ev_umsGetRegInfo_CnsRspEx, &CUmcAddrbookCtrl::OnAddrbookGlobleCnsRsp );
	REG_PFUN( ev_umsGetRegInfo_MtRspEx, &CUmcAddrbookCtrl::OnAddrbookGlobleMtRsp );
	REG_PFUN( ev_umsGetRegInfo_McuRspEx, &CUmcAddrbookCtrl::OnAddrbookGlobleMcuRsp );

	REG_PFUN( OSP_DISCONNECT, &CUmcAddrbookCtrl::OnLinkBreak ); 
	
	BuildReqEventsMap();
}

void CUmcAddrbookCtrl::BuildReqEventsMap()
{
	REG_REQ_PFUN( ev_umcweb_addrbook_globle_refresh_req, &CUmcAddrbookCtrl::OnAddrbookGlobleRefreshReq );
	REG_REQ_PFUN( ev_umcweb_addrbook_globle_get_req, &CUmcAddrbookCtrl::OnAddrbookGlobleGetReq );

	REG_REQ_PFUN( ev_umcweb_addrbook_item_add_req, &CUmcAddrbookCtrl::OnAddrbookItemAddReq );
	REG_REQ_PFUN( ev_umcweb_addrbook_item_mod_req, &CUmcAddrbookCtrl::OnAddrbookItemModReq );
	REG_REQ_PFUN( ev_umcweb_addrbook_item_del_req, &CUmcAddrbookCtrl::OnAddrbookItemDelReq );

	REG_REQ_PFUN( ev_umcweb_addrbook_itemgroup_get_req, &CUmcAddrbookCtrl::OnAddrbookItemgroupGetReq );
	REG_REQ_PFUN( ev_umcweb_addrbook_itemgroup_search_req, &CUmcAddrbookCtrl::OnAddrbookItemgroupSearchReq );

	REG_REQ_PFUN( ev_umcweb_addrbook_item_get_req, &CUmcAddrbookCtrl::OnAddrbookItemGetReq );
	REG_REQ_PFUN( ev_umcweb_addrbook_item_number_req, &CUmcAddrbookCtrl::OnAddrbookItemNumberReq );

	REG_REQ_PFUN( ev_umcweb_addrbook_group_add_req, &CUmcAddrbookCtrl::OnAddrbookGroupAddReq );
	REG_REQ_PFUN( ev_umcweb_addrbook_group_mod_req, &CUmcAddrbookCtrl::OnAddrbookGroupModReq );
	REG_REQ_PFUN( ev_umcweb_addrbook_group_del_req, &CUmcAddrbookCtrl::OnAddrbookGroupDelReq );

	REG_REQ_PFUN( ev_umcweb_addrbook_group_get_req, &CUmcAddrbookCtrl::OnAddrbookGroupGetReq );

	REG_REQ_PFUN( ev_umcweb_addrbook_ig_add_req, &CUmcAddrbookCtrl::OnAddrbookIgAddReq );
	REG_REQ_PFUN( ev_umcweb_addrbook_ig_del_req, &CUmcAddrbookCtrl::OnAddrbookIgDelReq );

	REG_REQ_PFUN( ev_umcweb_addrbook_gg_add_req, &CUmcAddrbookCtrl::OnAddrbookGgAddReq );
	REG_REQ_PFUN( ev_umcweb_addrbook_gg_del_req, &CUmcAddrbookCtrl::OnAddrbookGgDelReq );
}

void CUmcAddrbookCtrl::ClearData()
{
	m_bIsEndSip = FALSE;
	m_bIsEndGk = FALSE;
}

void CUmcAddrbookCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN(CUmcAddrbookCtrl,cMsg);
}

void CUmcAddrbookCtrl::DispReqEvent( u16 wEvent, const boost::any& arg )
{
    DISP_REQ_FUN( CUmcAddrbookCtrl, wEvent, arg );
}

u16 CUmcAddrbookCtrl::OnAddrbookGlobleRefreshReq(const boost::any& arg)
{
	PrtMsg( ev_umcweb_addrbook_globle_refresh_req, emEventTypeClientRecv, "" );

	EmGetRegInfoType emType = emGetRegInfoType_ALL;

	CMessage* pCMsg = PTR_MSGDRIVER->GetCMsgPtr();
	pCMsg->event = ev_umsGetRegInfo_Req;
	pCMsg->content =  (u8*)&emType;
	pCMsg->length = sizeof(EmGetRegInfoType);
	
    PrtMsg( ev_umsGetRegInfo_Req, emEventTypeServerSend, "emType:%d", emType );

	m_bIsEndSip = FALSE;
	m_bIsEndGk = FALSE;

	char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chSQL, "delete from %s", TB_ADDRBOOK_GLOBLE_NAME );
	PTR_DBSTORAGE->ExecuteDML(chSQL);
	
	PTR_SESSION->m_bRefresh = TRUE;

	//OSP_RSP_SELF_HANDLE:自己处理锁释放
	PTR_MSGDRIVER->PostCommand(this, OSP_RSP_SELF_HANDLE);

	return NO_ERROR;
}

void CUmcAddrbookCtrl::OnAddrbookGlobleUmsRsp( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	TUmsRegPackEx tUmsRegPackEx = *reinterpret_cast<TUmsRegPackEx*>(cTpMsg.GetBody());
	
	PrtMsg( ev_umsGetRegInfo_UmsRspEx, emEventTypeServerRecv
		, "m_wSize: %d, m_bIsEnd: %d, RegInfoType: %d(CNS: 1, UMS: 2, MT: 4, MCU:5)"
		, tUmsRegPackEx.m_wSize, tUmsRegPackEx.m_bIsEnd, emTPEndpointTypeUMS );


	for ( int m = 0; m < tUmsRegPackEx.m_wSize; m++ )
	{
		for ( int n = 0; n < tUmsRegPackEx.m_atRegInfo[m].m_wAliasNum; n++ )
		{		
			//地址名称和号码未对应
			TTPAlias tTPAlias = tUmsRegPackEx.m_atRegInfo[m].m_atAlias[n];

			char chName[TP_MAX_ALIAS_LEN + 1]={0};
			char chNumber[TP_MAX_ALIAS_LEN + 1]={0};
			char chIp[TP_MAX_ALIAS_LEN + 1]={0};
			
			GetItemInfo( tTPAlias, chName, chNumber, chIp );

			char chSQL[MAX_SQL_SENTENCE_LENTH]={0};
			
			sprintf( chSQL, "insert into %s(%s,%s,%s,%s) values(\"%d\",\"%s\",\"%s\",\"%s\");"
				, TB_ADDRBOOK_GLOBLE_NAME
				, TB_ADDRBOOK_GLOBLE_FIELD_TYPE, TB_ADDRBOOK_GLOBLE_FIELD_NAME, TB_ADDRBOOK_GLOBLE_FIELD_NUMBER, TB_ADDRBOOK_GLOBLE_FIELD_IP
				, ADDR_TYPE_SIP, chName, chNumber, chIp );

			PTR_DBSTORAGE->ExecuteDML(chSQL);
		}
	}
	
	m_bIsEndSip = tUmsRegPackEx.m_bIsEnd;
	
	if ( m_bIsEndSip && m_bIsEndGk )
	{
		updAddrbookLocalState();

		if ( PTR_SESSION->m_bRefresh == TRUE )
		{
			PTR_FCGIPRINTF("{\"event\":\"ev_umcweb_addrbook_globle_refresh_res\",\"bRet\":\"%d\"}", TRUE );
			PrtMsg( ev_umcweb_addrbook_globle_refresh_res, emEventTypeClientSend, "bRet:%d", TRUE );
			
			PTR_SESSION->m_bRefresh = FALSE;			
			
			//刷新完成手动释放锁
			PTR_MSGDRIVER->ReleaseLock();
		}
	}
}

void CUmcAddrbookCtrl::OnAddrbookGlobleCnsRsp( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	TCnsRegPackEx tCnsRegPackEx = *reinterpret_cast<TCnsRegPackEx*>(cTpMsg.GetBody());
	
	PrtMsg( ev_umsGetRegInfo_CnsRspEx, emEventTypeServerRecv
		, "m_wSize: %d, m_bIsEnd: %d, RegInfoType: %d(CNS: 1, UMS: 2, MT: 4, MCU:5)"
		, tCnsRegPackEx.m_wSize, tCnsRegPackEx.m_bIsEnd, emTPEndpointTypeCNS );


	for ( int m = 0; m < tCnsRegPackEx.m_wSize; m++ )
	{
		char chName[TP_MAX_ALIAS_LEN + 1]={0};
		char chNumber[TP_MAX_ALIAS_LEN + 1]={0};
		char chIp[TP_MAX_ALIAS_LEN + 1]={0};

		for ( int n = 0; n < tCnsRegPackEx.m_atRegInfo[m].m_wAliasNum; n++ )
		{
			TTPAlias tTPAlias = tCnsRegPackEx.m_atRegInfo[m].m_atAlias[n];
			GetItemInfo( tTPAlias, chName, chNumber, chIp );
		}

		char chSQL[MAX_SQL_SENTENCE_LENTH]={0};
		
		sprintf( chSQL, "insert into %s(%s,%s,%s,%s) values(\"%d\",\"%s\",\"%s\",\"%s\");"
			, TB_ADDRBOOK_GLOBLE_NAME
			, TB_ADDRBOOK_GLOBLE_FIELD_TYPE, TB_ADDRBOOK_GLOBLE_FIELD_NAME, TB_ADDRBOOK_GLOBLE_FIELD_NUMBER, TB_ADDRBOOK_GLOBLE_FIELD_IP
			, ADDR_TYPE_SIP, chName, chNumber, chIp );
		
		PTR_DBSTORAGE->ExecuteDML(chSQL);
	}
	
	m_bIsEndSip = tCnsRegPackEx.m_bIsEnd;

	if ( m_bIsEndSip && m_bIsEndGk )
	{
		updAddrbookLocalState();

		if ( PTR_SESSION->m_bRefresh == TRUE)
		{
			PTR_FCGIPRINTF("{\"event\":\"ev_umcweb_addrbook_globle_refresh_res\",\"bRet\":\"%d\"}", TRUE );
			PrtMsg( ev_umcweb_addrbook_globle_refresh_res, emEventTypeClientSend, "bRet:%d", TRUE );
			
			PTR_SESSION->m_bRefresh = FALSE;
			
			//刷新完成手动释放锁
			PTR_MSGDRIVER->ReleaseLock();
		}
	}
}

void CUmcAddrbookCtrl::OnAddrbookGlobleMtRsp( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	TTPMtRegInfo tTPMtRegInfo = *reinterpret_cast<TTPMtRegInfo*>(cTpMsg.GetBody());

	PrtMsg( ev_umsGetRegInfo_MtRspEx, emEventTypeServerRecv
		, "m_wListNum: %d, m_bIsEnd: %d, RegInfoType: %d(CNS: 1, UMS: 2, MT: 4, MCU:5)"
		, tTPMtRegInfo.m_wListNum, tTPMtRegInfo.m_bIsEnd, emTPEndpointH323MT );

		
	for ( int m = 0; m < tTPMtRegInfo.m_wListNum; m++ )
	{
		TTPMtTerminal tTPMtTerminal = tTPMtRegInfo.m_atTerminal[m];

		char chName[TP_MAX_ALIAS_LEN + 1]={0};
		char chNumber[TP_MAX_ALIAS_LEN + 1]={0};
		char chIp[TP_MAX_ALIAS_LEN + 1]={0};

		for ( int n = 0; n < MAX_MT_ALIAS_NUM; n++ )
		{
			TTPAlias tTPAlias = tTPMtRegInfo.m_atTerminal[m].m_atAlias[n];
			GetItemInfo( tTPAlias, chName, chNumber, chIp );
		}

		char chSQL[MAX_SQL_SENTENCE_LENTH]={0};
		
		sprintf( chSQL, "insert into %s(%s,%s,%s,%s) values(\"%d\",\"%s\",\"%s\",\"%s\");"
			, TB_ADDRBOOK_GLOBLE_NAME
			, TB_ADDRBOOK_GLOBLE_FIELD_TYPE, TB_ADDRBOOK_GLOBLE_FIELD_NAME, TB_ADDRBOOK_GLOBLE_FIELD_NUMBER, TB_ADDRBOOK_GLOBLE_FIELD_IP
			, ADDR_TYPE_GK, chName, chNumber, chIp );
		
		PTR_DBSTORAGE->ExecuteDML(chSQL);
	}

	m_bIsEndGk = tTPMtRegInfo.m_bIsEnd;
	
	if ( m_bIsEndSip && m_bIsEndGk )
	{
		updAddrbookLocalState();

		if ( PTR_SESSION->m_bRefresh == TRUE )
		{
			PTR_FCGIPRINTF("{\"event\":\"ev_umcweb_addrbook_globle_refresh_res\",\"bRet\":\"%d\"}", TRUE );
			PrtMsg( ev_umcweb_addrbook_globle_refresh_res, emEventTypeClientSend, "bRet:%d", TRUE );

			PTR_SESSION->m_bRefresh = FALSE;
			
			//刷新完成手动释放锁
			PTR_MSGDRIVER->ReleaseLock();
		}
	}
}

void CUmcAddrbookCtrl::OnAddrbookGlobleMcuRsp( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	TTPMcuRegInfo tTPMcuRegInfo = *reinterpret_cast<TTPMcuRegInfo*>(cTpMsg.GetBody());

	PrtMsg( ev_umsGetRegInfo_McuRspEx, emEventTypeServerRecv
		, "m_wListNum: %d, m_bIsEnd: %d, RegInfoType: %d(CNS: 1, UMS: 2, MT: 4, MCU:5)"
		, tTPMcuRegInfo.m_wListNum, tTPMcuRegInfo.m_bIsEnd, emTPEndpointH323MCU );

	char chName[TP_MAX_ALIAS_LEN + 1]={0};
	char chNumber[TP_MAX_ALIAS_LEN + 1]={0};
	char chIp[TP_MAX_ALIAS_LEN + 1]={0};

	for ( int n = 0; n < tTPMcuRegInfo.m_wListNum; n++ )
	{
		TTPAlias tTPAlias = tTPMcuRegInfo.m_atAlias[n];
		
		GetItemInfo( tTPAlias, chName, chNumber, chIp );
	}

	if ( tTPMcuRegInfo.m_wListNum > 0 )
	{
		char chSQL[MAX_SQL_SENTENCE_LENTH]={0};
		
		sprintf( chSQL, "insert into %s(%s,%s,%s,%s) values(\"%d\",\"%s\",\"%s\",\"%s\");"
			, TB_ADDRBOOK_GLOBLE_NAME
			, TB_ADDRBOOK_GLOBLE_FIELD_TYPE, TB_ADDRBOOK_GLOBLE_FIELD_NAME, TB_ADDRBOOK_GLOBLE_FIELD_NUMBER, TB_ADDRBOOK_GLOBLE_FIELD_IP
			, ADDR_TYPE_GK, chName, chNumber, chIp );
		
		PTR_DBSTORAGE->ExecuteDML(chSQL);
	}

	m_bIsEndGk = tTPMcuRegInfo.m_bIsEnd;
	
	if ( m_bIsEndSip && m_bIsEndGk )
	{
		updAddrbookLocalState();

		if ( PTR_SESSION->m_bRefresh == TRUE )
		{
			PTR_FCGIPRINTF("{\"event\":\"ev_umcweb_addrbook_globle_refresh_res\",\"bRet\":\"%d\"}", TRUE );
			PrtMsg( ev_umcweb_addrbook_globle_refresh_res, emEventTypeClientSend, "bRet:%d", TRUE );

			PTR_SESSION->m_bRefresh = FALSE;
			
			//刷新完成手动释放锁
			PTR_MSGDRIVER->ReleaseLock();
		}
	}
}

u16 CUmcAddrbookCtrl::OnAddrbookGlobleGetReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pte = COwsCommon::GetPropertyTree(strData);
	std::string strSearch = COwsCommon::GetPropertyTreeVar( pte, "search" );

	PrtMsg( ev_umcweb_addrbook_globle_get_req, emEventTypeClientRecv, "strSearch:%s", strSearch.c_str() );

	char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chSQL, "select * from %s where %s like \"%%%s\%\" order by %s asc;"
		, TB_ADDRBOOK_GLOBLE_NAME, TB_ADDRBOOK_GLOBLE_FIELD_NAME , strSearch.c_str(), TB_ADDRBOOK_GLOBLE_FIELD_NAME );
	
	std::vector<ROW> vecRes;
	BOOL bRet = PTR_DBSTORAGE->ExecuteDQL(chSQL, vecRes);
	if ( !bRet )
	{
		return NO_ERROR;
	}

	std::string strJson;

	if ( vecRes.size() == 0 )
	{
		strJson = "{\"event\":\"ev_umcweb_addrbook_globle_get_res\",\"count\":\"0\"}";
	}
	else
	{
		string strJsonHead = "{\"event\":\"ev_umcweb_addrbook_globle_get_res\",\"items\":";
		
		vector<string> vecStrJson;
		
		std::vector<ROW>::iterator it = vecRes.begin();
		for ( ; it != vecRes.end(); it++ )
		{
			ROW row = *it;
			std::string strId = row[ROW_TB_ADDRBOOK_GLOBLE_FIELD_ID];
			std::string strType = row[ROW_TB_ADDRBOOK_GLOBLE_FIELD_TYPE];
			std::string strName = row[ROW_TB_ADDRBOOK_GLOBLE_FIELD_NAME];
			std::string strNumber = row[ROW_TB_ADDRBOOK_GLOBLE_FIELD_NUMBER];
			std::string strIp = row[ROW_TB_ADDRBOOK_GLOBLE_FIELD_IP];
			
			char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
			sprintf( chItem, "{\"id\":\"%s\",\"type\":\"%s\",\"name\":\"%s\",\"number\":\"%s\",\"ip\":\"%s\"}"
				, strId.c_str(), strType.c_str(), strName.c_str(), strNumber.c_str(), strIp.c_str() );
			
			vecStrJson.push_back(chItem);
		}
		
		strJson = COwsCommon::CreateStringJson( strJsonHead, vecStrJson );
	}

	PTR_FCGIPRINTF( strJson.c_str() );
	PrtMsg( ev_umcweb_addrbook_globle_get_res, emEventTypeClientSend, "strJson:%s", strJson.c_str() );

	return NO_ERROR;
}

u16 CUmcAddrbookCtrl::OnAddrbookItemAddReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strName = COwsCommon::GetPropertyTreeVar( pt, "name" );
	std::string strNumber = COwsCommon::GetPropertyTreeVar( pt, "number" );
	std::string strIp = COwsCommon::GetPropertyTreeVar( pt, "ip" );
	
	PrtMsg( ev_umcweb_addrbook_item_add_req, emEventTypeClientRecv, "strName:%s, strNumber:%s, strIp:%s"
		, strName.c_str(), strNumber.c_str(), strIp.c_str() );

	char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
	BOOL bRet = FALSE;
	std::vector<ROW> vecRow;

	if ( strName != "" )
	{
		sprintf( chSQL, "select * from %s where %s=\"%s\";", TB_ADDRBOOK_ITEM_NAME, TB_ADDRBOOK_ITEM_FIELD_NAME, strName.c_str() );
		
		bRet = PTR_DBSTORAGE->ExecuteDQL(chSQL, vecRow);
		if ( !bRet )
		{
			return NO_ERROR;
		}
		
		if (vecRow.size() > 0)
		{
			string strTemp = "名称已存在";
			PTR_FCGIPRINTF("{\"event\":\"ev_umcweb_addrbook_item_add_res\",\"nIID\":\"%s\"}", strTemp.c_str() );
			PrtMsg( ev_umcweb_addrbook_item_add_res, emEventTypeClientSend, "nIID:%s", strTemp.c_str() );
			
			return NO_ERROR;
		}
	}

	if ( strNumber != "" )
	{
		sprintf( chSQL, "select * from %s where %s=\"%s\";", TB_ADDRBOOK_ITEM_NAME, TB_ADDRBOOK_ITEM_FIELD_NUMBER, strNumber.c_str() );
		
		bRet = PTR_DBSTORAGE->ExecuteDQL(chSQL, vecRow);
		if ( !bRet )
		{
			return NO_ERROR;
		}
		
		if (vecRow.size() > 0)
		{
			string strTemp = "号码已存在";
			PTR_FCGIPRINTF("{\"event\":\"ev_umcweb_addrbook_item_add_res\",\"nIID\":\"%s\"}", strTemp.c_str() );
			PrtMsg( ev_umcweb_addrbook_item_add_res, emEventTypeClientSend, "nIID:%s", strTemp.c_str() );
			
			return NO_ERROR;
		}
	}

	if ( strIp != "" )
	{
		sprintf( chSQL, "select * from %s where %s=\"%s\";", TB_ADDRBOOK_ITEM_NAME, TB_ADDRBOOK_ITEM_FIELD_IP, strIp.c_str() );
		
		bRet = PTR_DBSTORAGE->ExecuteDQL(chSQL, vecRow);
		if ( !bRet )
		{
			return NO_ERROR;
		}
		
		if (vecRow.size() > 0)
		{
			string strTemp = "ip已存在";
			PTR_FCGIPRINTF("{\"event\":\"ev_umcweb_addrbook_item_add_res\",\"nIID\":\"%s\"}", strTemp.c_str() );
			PrtMsg( ev_umcweb_addrbook_item_add_res, emEventTypeClientSend, "nIID:%s", strTemp.c_str() );
			
			return NO_ERROR;
		}
	};
	

	sprintf( chSQL, "insert into %s(%s,%s,%s,%s,%s) values(\"%s\",\"%s\",\"%s\",%d,%d);"
		, TB_ADDRBOOK_ITEM_NAME
		, TB_ADDRBOOK_ITEM_FIELD_NAME, TB_ADDRBOOK_ITEM_FIELD_NUMBER, TB_ADDRBOOK_ITEM_FIELD_IP
		, TB_ADDRBOOK_ITEM_FIELD_TYPE, TB_ADDRBOOK_ITEM_FIELD_ONLINE
		, strName.c_str(), strNumber.c_str(), strIp.c_str(), FALSE, FALSE );

	bRet = PTR_DBSTORAGE->ExecuteDML(chSQL);

	if ( !bRet)
	{
		return NO_ERROR;
	}

	updAddrbookLocalState();

	sprintf( chSQL, "select %s from %s where %s=\"%s\";"
		, TB_ADDRBOOK_ITEM_FIELD_ID, TB_ADDRBOOK_ITEM_NAME, TB_ADDRBOOK_ITEM_FIELD_NAME, strName.c_str() );
	
	bRet = PTR_DBSTORAGE->ExecuteDQL(chSQL, vecRow);
	if ( !bRet )
	{
		return NO_ERROR;
	}
	
	string strTemp;
	vector<ROW>::iterator itRow = vecRow.begin();
	for ( ; itRow != vecRow.end(); itRow++ )
	{
		ROW row = *itRow;
		strTemp = row[ROW_TB_ADDRBOOK_ITEM_FIELD_ID];
	}

	PTR_FCGIPRINTF("{\"event\":\"ev_umcweb_addrbook_item_add_res\",\"nIID\":\"%s\"}", strTemp.c_str() );
	PrtMsg( ev_umcweb_addrbook_item_add_res, emEventTypeClientSend, "nIID:%s", strTemp.c_str() );

	return NO_ERROR;
}

u16 CUmcAddrbookCtrl::OnAddrbookItemModReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strId = COwsCommon::GetPropertyTreeVar( pt, "id" );
	std::string strName = COwsCommon::GetPropertyTreeVar( pt, "name" );
	std::string strNumber = COwsCommon::GetPropertyTreeVar( pt, "number" );
	std::string strIp = COwsCommon::GetPropertyTreeVar( pt, "ip" );
	
	PrtMsg( ev_umcweb_addrbook_item_mod_req, emEventTypeClientRecv, "strId:%s, strName:%s, strNumber:%s, strIp:%s"
		, strId.c_str(), strName.c_str(), strNumber.c_str(), strIp.c_str() );
	
	
	char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chSQL, "update %s set %s = \"%s\", %s=\"%s\", %s=\"%s\", %s=%d, %s=%d where %s=%s;"
		, TB_ADDRBOOK_ITEM_NAME
		, TB_ADDRBOOK_ITEM_FIELD_NAME, strName.c_str()
		, TB_ADDRBOOK_ITEM_FIELD_NUMBER, strNumber.c_str()
		, TB_ADDRBOOK_ITEM_FIELD_IP, strIp.c_str()
		, TB_ADDRBOOK_ITEM_FIELD_TYPE, FALSE
		, TB_ADDRBOOK_ITEM_FIELD_ONLINE, FALSE
		, TB_ADDRBOOK_ITEM_FIELD_ID, strId.c_str() );

	BOOL bRet = PTR_DBSTORAGE->ExecuteDML(chSQL);

	updAddrbookLocalState();
	
	PTR_FCGIPRINTF("{\"event\":\"ev_umcweb_addrbook_item_mod_res\",\"bRet\":\"%d\"}", bRet );
	PrtMsg( ev_umcweb_addrbook_item_mod_res, emEventTypeClientSend, "bRet:%d", bRet );
	
	return NO_ERROR;
}

u16 CUmcAddrbookCtrl::OnAddrbookItemDelReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strId = COwsCommon::GetPropertyTreeVar( pt, "id" );
	
	PrtMsg( ev_umcweb_addrbook_item_del_req, emEventTypeClientRecv, "strId:%s", strId.c_str() );
	
	
	char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chSQL, "delete from %s where %s=%s;", TB_ADDRBOOK_ITEM_NAME, TB_ADDRBOOK_ITEM_FIELD_ID, strId.c_str() );
	BOOL bRet = PTR_DBSTORAGE->ExecuteDML(chSQL);
	
	PTR_FCGIPRINTF("{\"event\":\"ev_umcweb_addrbook_item_del_res\",\"bRet\":\"%d\"}", bRet );
	PrtMsg( ev_umcweb_addrbook_item_del_res, emEventTypeClientSend, "bRet:%d", bRet );
	
	return NO_ERROR;
}

void CUmcAddrbookCtrl::GetItemInfo( TTPAlias tTPAlias, char *pChName, char *pChNumber, char *pChIp )
{
	switch ( tTPAlias.m_byType )
	{
	case tp_Alias_h323:
		{
			strncpy( pChName, tTPAlias.m_abyAlias, TP_MAX_ALIAS_LEN );
			break;
		}
	case tp_Alias_e164:
		{
			strncpy( pChNumber, tTPAlias.m_abyAlias, TP_MAX_ALIAS_LEN );
			break;
		}
	case tp_Alias_IP:
		{
			strncpy( pChIp, tTPAlias.m_abyAlias, TP_MAX_ALIAS_LEN );
			break;
		}
	default:
		break;
	}
}

u16 CUmcAddrbookCtrl::OnAddrbookItemGetReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pte = COwsCommon::GetPropertyTree(strData);
	std::string strGid = COwsCommon::GetPropertyTreeVar( pte, "gid" );

	PrtMsg( ev_umcweb_addrbook_item_get_req, emEventTypeClientRecv, "strGid:%s", strGid.c_str() );


	char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chSQL, "select %s from %s where %s=%s;"
		, TB_ADDRBOOK_IG_FIELD_IID, TB_ADDRBOOK_IG_NAME, TB_ADDRBOOK_IG_FIELD_GID, strGid.c_str() );
	
	std::vector<ROW> vecRow;
	BOOL bRet = PTR_DBSTORAGE->ExecuteDQL(chSQL, vecRow);
	if ( !bRet )
	{
		return NO_ERROR;
	}

	string strTemp;
	vector<ROW>::iterator itRow = vecRow.begin();
	for ( ; itRow != vecRow.end(); itRow++ )
	{
		ROW row = *itRow;
		strTemp += row[ROW_TB_ADDRBOOK_IG_FIELD_IID];
		strTemp += ",";
	}
	strTemp = strTemp.substr(0,strTemp.length()-1);


	sprintf( chSQL, "select * from %s where %s in (%s) order by %s asc;"
		, TB_ADDRBOOK_ITEM_NAME, TB_ADDRBOOK_ITEM_FIELD_ID, strTemp.c_str(), TB_ADDRBOOK_ITEM_FIELD_NAME );

	
	std::vector<ROW> vecRes;
	bRet = PTR_DBSTORAGE->ExecuteDQL(chSQL, vecRes);
	if ( !bRet )
	{
		string strJson = "{\"event\":\"ev_umcweb_addrbook_item_get_res\",\"count\":\"0\"}";
		
		PTR_FCGIPRINTF( strJson.c_str() );
		PrtMsg( ev_umcweb_addrbook_item_get_res, emEventTypeClientSend, "strJson:%s", strJson.c_str() );

		return NO_ERROR;
	}

	
	string strJsonHead = "{\"event\":\"ev_umcweb_addrbook_item_get_res\",\"items\":";
	
	vector<string> vecStrJson;
	
	std::vector<ROW>::iterator it = vecRes.begin();
	for ( ; it != vecRes.end(); it++ )
	{
		ROW row = *it;
		std::string strId = row[ROW_TB_ADDRBOOK_ITEM_FIELD_ID];
		std::string strName = row[ROW_TB_ADDRBOOK_ITEM_FIELD_NAME];
		std::string strNumber = row[ROW_TB_ADDRBOOK_ITEM_FIELD_NUMBER];
		std::string strIp = row[ROW_TB_ADDRBOOK_ITEM_FIELD_IP];
		std::string strType = row[ROW_TB_ADDRBOOK_ITEM_FIELD_TYPE];
		std::string strOnline = row[ROW_TB_ADDRBOOK_ITEM_FIELD_ONLINE];
		
		char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
		sprintf( chItem, "{\"id\":\"%s\",\"name\":\"%s\",\"number\":\"%s\",\"ip\":\"%s\",\"type\":\"%s\",\"online\":\"%s\"}"
			, strId.c_str(), strName.c_str(), strNumber.c_str(), strIp.c_str(), strType.c_str(), strOnline.c_str() );
		
		vecStrJson.push_back(chItem);
	}
	
	std::string strJson = COwsCommon::CreateStringJson( strJsonHead, vecStrJson );
	
	
	PTR_FCGIPRINTF( strJson.c_str() );
	PrtMsg( ev_umcweb_addrbook_item_get_res, emEventTypeClientSend, "strJson:%s", strJson.c_str() );
	
	return NO_ERROR;
}

u16 CUmcAddrbookCtrl::OnAddrbookItemgroupGetReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pte = COwsCommon::GetPropertyTree(strData);
	std::string strGid = COwsCommon::GetPropertyTreeVar( pte, "gid" );
	
	PrtMsg( ev_umcweb_addrbook_itemgroup_get_req, emEventTypeClientRecv, "strGid:%s", strGid.c_str() );
	
	//查找条目
	string strItem;

	char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chSQL, "select %s from %s where %s=%s;"
		, TB_ADDRBOOK_IG_FIELD_IID, TB_ADDRBOOK_IG_NAME, TB_ADDRBOOK_IG_FIELD_GID, strGid.c_str() );
	
	std::vector<ROW> vecRow;
	BOOL bRet = PTR_DBSTORAGE->ExecuteDQL(chSQL, vecRow);
	if ( !bRet )
	{
		return NO_ERROR;
	}
	else
	{
		string strTemp;
		vector<ROW>::iterator itRow = vecRow.begin();
		for ( ; itRow != vecRow.end(); itRow++ )
		{
			ROW row = *itRow;
			strTemp += row[ROW_TB_ADDRBOOK_IG_FIELD_IID];
			strTemp += ",";
		}
		strTemp = strTemp.substr(0,strTemp.length()-1);
		
		
		sprintf( chSQL, "select * from %s where %s in (%s) order by %s asc;"
			, TB_ADDRBOOK_ITEM_NAME, TB_ADDRBOOK_ITEM_FIELD_ID, strTemp.c_str(), TB_ADDRBOOK_ITEM_FIELD_NAME );
		
		
		std::vector<ROW> vecRes;
		bRet = PTR_DBSTORAGE->ExecuteDQL(chSQL, vecRes);
		if ( !bRet )
		{
			strItem = "\"count\":\"0\"";
		}
		else
		{
			strItem = "\"items\":[";
			
			std::vector<ROW>::iterator it = vecRes.begin();
			for ( ; it != vecRes.end(); it++ )
			{
				ROW row = *it;
				std::string strId = row[ROW_TB_ADDRBOOK_ITEM_FIELD_ID];
				std::string strName = row[ROW_TB_ADDRBOOK_ITEM_FIELD_NAME];
				std::string strNumber = row[ROW_TB_ADDRBOOK_ITEM_FIELD_NUMBER];
				std::string strIp = row[ROW_TB_ADDRBOOK_ITEM_FIELD_IP];
				std::string strType = row[ROW_TB_ADDRBOOK_ITEM_FIELD_TYPE];
				std::string strOnline = row[ROW_TB_ADDRBOOK_ITEM_FIELD_ONLINE];
				
				char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
				sprintf( chItem, "{\"id\":\"%s\",\"name\":\"%s\",\"number\":\"%s\",\"ip\":\"%s\",\"type\":\"%s\",\"online\":\"%s\"},"
					, strId.c_str(), strName.c_str(), strNumber.c_str(), strIp.c_str(), strType.c_str(), strOnline.c_str() );
				
				strItem += chItem;
			}

			strItem = strItem.substr(0,strItem.length()-1);
			
			strItem += "]";
			
			char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
			sprintf( chItem, ",\"count\":\"%d\"", vecRes.size() );
			
			strItem += chItem;
		}
	}
	
	
	
	//查找组
	string strGroup;

	sprintf( chSQL, "select * from %s where %s=%s;"
		, TB_ADDRBOOK_GG_NAME, TB_ADDRBOOK_GG_FIELD_GPID, strGid.c_str() );
	
	std::vector<ROW> vecRowGroup;
	bRet = PTR_DBSTORAGE->ExecuteDQL(chSQL, vecRowGroup);
	if ( !bRet )
	{
		return NO_ERROR;
	}
	else
	{
		string strTemp;
		
		vector<ROW>::iterator itRow = vecRowGroup.begin();
		for ( ; itRow != vecRowGroup.end(); itRow++ )
		{
			ROW row = *itRow;
			strTemp += row[ROW_TB_ADDRBOOK_GG_FIELD_GID];
			strTemp += ",";
		}
		strTemp = strTemp.substr(0,strTemp.length()-1);
		
		sprintf( chSQL, "select * from %s where %s in (%s) order by %s asc;"
			, TB_ADDRBOOK_GROUP_NAME, TB_ADDRBOOK_GROUP_FIELD_ID, strTemp.c_str(), TB_ADDRBOOK_GROUP_FIELD_NAME );
		
		std::vector<ROW> vecRes;
		bRet = PTR_DBSTORAGE->ExecuteDQL(chSQL, vecRes);
		if ( !bRet )
		{
			strGroup = "\"groupcount\":\"0\"";
		}
		else
		{
			strGroup = "\"groupitems\":[";
			
			std::vector<ROW>::iterator it = vecRes.begin();
			for ( ; it != vecRes.end(); it++ )
			{
				ROW row = *it;
				std::string strId = row[ROW_TB_ADDRBOOK_GROUP_FIELD_ID];
				std::string strName = row[ROW_TB_ADDRBOOK_GROUP_FIELD_NAME];
				
				char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
				sprintf( chItem, "{\"id\":\"%s\",\"name\":\"%s\"},", strId.c_str(), strName.c_str() );
				
				strGroup += chItem;
			}

			strGroup = strGroup.substr(0,strGroup.length()-1);
			
			strGroup += "]";
			
			char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
			sprintf( chItem, ",\"groupcount\":\"%d\"", vecRes.size() );
			
			strGroup += chItem;
		}
	}
	
	
	string strJson;
	strJson = "{\"event\":\"ev_umcweb_addrbook_itemgroup_get_res\"," + strItem + "," + strGroup + "}";
	
	PTR_FCGIPRINTF( strJson.c_str() );
	PrtMsg( ev_umcweb_addrbook_itemgroup_get_res, emEventTypeClientSend, "strJson:%s", strJson.c_str() );
	
	return NO_ERROR;
}

u16 CUmcAddrbookCtrl::OnAddrbookItemgroupSearchReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pte = COwsCommon::GetPropertyTree(strData);
	std::string strGid = COwsCommon::GetPropertyTreeVar( pte, "gid" );
	std::string strSearch = COwsCommon::GetPropertyTreeVar( pte, "search" );
	
	PrtMsg( ev_umcweb_addrbook_itemgroup_search_req, emEventTypeClientRecv, "strGid:%s,strSearch:%s", strGid.c_str(), strSearch.c_str() );

	//查找条目
	string strItem;
	
	char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chSQL, "select %s.%s, %s, %s, %s, %s, %s from %s, %s where (%s.%s=%s.%s) and (%s=%s) and (%s like \"%%%s\%\") order by %s asc;"
		, TB_ADDRBOOK_ITEM_NAME, TB_ADDRBOOK_ITEM_FIELD_ID, TB_ADDRBOOK_ITEM_FIELD_NAME, TB_ADDRBOOK_ITEM_FIELD_NUMBER, TB_ADDRBOOK_ITEM_FIELD_IP, TB_ADDRBOOK_ITEM_FIELD_TYPE, TB_ADDRBOOK_ITEM_FIELD_ONLINE
		, TB_ADDRBOOK_ITEM_NAME, TB_ADDRBOOK_IG_NAME, TB_ADDRBOOK_ITEM_NAME, TB_ADDRBOOK_ITEM_FIELD_ID, TB_ADDRBOOK_IG_NAME, TB_ADDRBOOK_IG_FIELD_IID
		, TB_ADDRBOOK_IG_FIELD_GID, strGid.c_str(), TB_ADDRBOOK_ITEM_FIELD_NAME, strSearch.c_str(), TB_ADDRBOOK_ITEM_FIELD_NAME );

	
	std::vector<ROW> vecRow;
	BOOL bRet = PTR_DBSTORAGE->ExecuteDQL(chSQL, vecRow);
	if ( !bRet )
	{
		return NO_ERROR;
	}
	else
	{
		if ( vecRow.size() == 0 )
		{
			strItem = "\"count\":\"0\"";
		}
		else
		{
			strItem = "\"items\":[";
			
			std::vector<ROW>::iterator it = vecRow.begin();
			for ( ; it != vecRow.end(); it++ )
			{
				ROW row = *it;

				std::string strId = row[ROW_TB_ADDRBOOK_ITEM_FIELD_ID];
				std::string strName = row[ROW_TB_ADDRBOOK_ITEM_FIELD_NAME];
				std::string strNumber = row[ROW_TB_ADDRBOOK_ITEM_FIELD_NUMBER];
				std::string strIp = row[ROW_TB_ADDRBOOK_ITEM_FIELD_IP];
				std::string strType = row[ROW_TB_ADDRBOOK_ITEM_FIELD_TYPE];
				std::string strOnline = row[ROW_TB_ADDRBOOK_ITEM_FIELD_ONLINE];
				
				char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
				sprintf( chItem, "{\"id\":\"%s\",\"name\":\"%s\",\"number\":\"%s\",\"ip\":\"%s\",\"type\":\"%s\",\"online\":\"%s\"},"
					, strId.c_str(), strName.c_str(), strNumber.c_str(), strIp.c_str(), strType.c_str(), strOnline.c_str() );
				
				strItem += chItem;
			}
			
			strItem = strItem.substr(0,strItem.length()-1);
			
			strItem += "]";
			
			char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
			sprintf( chItem, ",\"count\":\"%d\"", vecRow.size() );
			
			strItem += chItem;
		}
	}
	
	//查找组
	string strGroup;
	
	sprintf( chSQL, "select %s.%s, %s from %s, %s where (%s.%s=%s.%s) and (%s=%s) and (%s like \"%%%s\%\") order by %s asc;"
		, TB_ADDRBOOK_GROUP_NAME, TB_ADDRBOOK_GROUP_FIELD_ID, TB_ADDRBOOK_GROUP_FIELD_NAME
		, TB_ADDRBOOK_GROUP_NAME, TB_ADDRBOOK_GG_NAME, TB_ADDRBOOK_GROUP_NAME, TB_ADDRBOOK_GROUP_FIELD_ID
		, TB_ADDRBOOK_GG_NAME, TB_ADDRBOOK_GG_FIELD_GID, TB_ADDRBOOK_GG_FIELD_GPID, strGid.c_str()
		, TB_ADDRBOOK_GROUP_FIELD_NAME, strSearch.c_str(), TB_ADDRBOOK_GROUP_FIELD_NAME );
	
	std::vector<ROW> vecRowGroup;
	bRet = PTR_DBSTORAGE->ExecuteDQL(chSQL, vecRowGroup);
	if ( !bRet )
	{
		return NO_ERROR;
	}
	else
	{
		if ( vecRowGroup.size() == 0 )
		{
			strGroup = "\"groupcount\":\"0\"";
		}
		else
		{
			strGroup = "\"groupitems\":[";
			
			std::vector<ROW>::iterator it = vecRowGroup.begin();
			for ( ; it != vecRowGroup.end(); it++ )
			{
				ROW row = *it;
				std::string strId = row[ROW_TB_ADDRBOOK_GROUP_FIELD_ID];
				std::string strName = row[ROW_TB_ADDRBOOK_GROUP_FIELD_NAME];
				
				char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
				sprintf( chItem, "{\"id\":\"%s\",\"name\":\"%s\"},", strId.c_str(), strName.c_str() );
				
				strGroup += chItem;
			}
			
			strGroup = strGroup.substr(0,strGroup.length()-1);
			
			strGroup += "]";
			
			char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
			sprintf( chItem, ",\"groupcount\":\"%d\"", vecRowGroup.size() );
			
			strGroup += chItem;
		}
	}
	
	
	string strJson;
	strJson = "{\"event\":\"ev_umcweb_addrbook_itemgroup_search_res\"," + strItem + "," + strGroup + "}";
	
	PTR_FCGIPRINTF( strJson.c_str() );
	PrtMsg( ev_umcweb_addrbook_itemgroup_search_res, emEventTypeClientSend, "strJson:%s", strJson.c_str() );
	
	return NO_ERROR;
}

u16 CUmcAddrbookCtrl::OnAddrbookItemNumberReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pte = COwsCommon::GetPropertyTree(strData);
	std::string strGid = COwsCommon::GetPropertyTreeVar( pte, "gid" );
	
	PrtMsg( ev_umcweb_addrbook_item_number_req, emEventTypeClientRecv, "strGid:%s", strGid.c_str() );
	
	
	char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chSQL, "select * from %s where %s=%s;", TB_ADDRBOOK_IG_NAME, TB_ADDRBOOK_IG_FIELD_GID, strGid.c_str() );
	
	int nNumber = PTR_DBSTORAGE->GetCount(chSQL);
	

	char chJson[MAX_JSON_SENTENCE_LENTH] = {0};
	sprintf( chJson, "{\"event\":\"ev_umcweb_addrbook_item_number_res\",\"number\":\"%d\"}", nNumber );
	
	PTR_FCGIPRINTF( chJson );
	PrtMsg( ev_umcweb_addrbook_item_get_res, emEventTypeClientSend, "strJson:%s", chJson );
	
	return NO_ERROR;
}

u16 CUmcAddrbookCtrl::OnAddrbookGroupAddReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strName = COwsCommon::GetPropertyTreeVar( pt, "name" );
	
	PrtMsg( ev_umcweb_addrbook_group_add_req, emEventTypeClientRecv, "strName:%s", strName.c_str() );
	
	
	char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chSQL, "insert into %s(%s) values(\"%s\");", TB_ADDRBOOK_GROUP_NAME, TB_ADDRBOOK_GROUP_FIELD_NAME, strName.c_str() );
	BOOL bRet = PTR_DBSTORAGE->ExecuteDML(chSQL);

	if ( !bRet)
	{
		return NO_ERROR;
	}
	
	chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chSQL, "select %s from %s where %s=\"%s\";"
		, TB_ADDRBOOK_GROUP_FIELD_ID, TB_ADDRBOOK_GROUP_NAME, TB_ADDRBOOK_GROUP_FIELD_NAME, strName.c_str() );
	
	std::vector<ROW> vecRow;
	bRet = PTR_DBSTORAGE->ExecuteDQL(chSQL, vecRow);
	if ( !bRet )
	{
		return NO_ERROR;
	}
	
	string strTemp;
	vector<ROW>::iterator itRow = vecRow.begin();
	for ( ; itRow != vecRow.end(); itRow++ )
	{
		ROW row = *itRow;
		strTemp = row[ROW_TB_ADDRBOOK_GROUP_FIELD_ID];
	}
	
	
	PTR_FCGIPRINTF("{\"event\":\"ev_umcweb_addrbook_group_add_res\",\"nGID\":\"%s\"}", strTemp.c_str() );
	PrtMsg( ev_umcweb_addrbook_group_add_res, emEventTypeClientSend, "nGID:%s", strTemp.c_str() );
	
	return NO_ERROR;
}

u16 CUmcAddrbookCtrl::OnAddrbookGroupModReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strId = COwsCommon::GetPropertyTreeVar( pt, "id" );
	std::string strName = COwsCommon::GetPropertyTreeVar( pt, "name" );
	
	PrtMsg( ev_umcweb_addrbook_group_mod_req, emEventTypeClientRecv, "strId:%s, strName:%s", strId.c_str(), strName.c_str() );
	
	
	char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chSQL, "update %s set %s = \"%s\" where %s=%s;"
		, TB_ADDRBOOK_GROUP_NAME
		, TB_ADDRBOOK_GROUP_FIELD_NAME, strName.c_str()
		, TB_ADDRBOOK_GROUP_FIELD_ID, strId.c_str() );
	BOOL bRet = PTR_DBSTORAGE->ExecuteDML(chSQL);
	
	PTR_FCGIPRINTF("{\"event\":\"ev_umcweb_addrbook_group_mod_res\",\"bRet\":\"%d\"}", bRet );
	PrtMsg( ev_umcweb_addrbook_group_mod_res, emEventTypeClientSend, "bRet:%d", bRet );
	
	return NO_ERROR;
}

u16 CUmcAddrbookCtrl::OnAddrbookGroupDelReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strId = COwsCommon::GetPropertyTreeVar( pt, "id" );
	
	PrtMsg( ev_umcweb_addrbook_group_del_req, emEventTypeClientRecv, "strId:%s", strId.c_str() );
	
	
	char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chSQL, "delete from %s where %s=%s;", TB_ADDRBOOK_GROUP_NAME, TB_ADDRBOOK_GROUP_FIELD_ID, strId.c_str() );
	BOOL bRet = PTR_DBSTORAGE->ExecuteDML(chSQL);
	
	PTR_FCGIPRINTF("{\"event\":\"ev_umcweb_addrbook_group_del_res\",\"bRet\":\"%d\"}", bRet );
	PrtMsg( ev_umcweb_addrbook_group_del_res, emEventTypeClientSend, "bRet:%d", bRet );
	
	return NO_ERROR;
}

u16 CUmcAddrbookCtrl::OnAddrbookIgAddReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strIid = COwsCommon::GetPropertyTreeVar( pt, "iid" );
	std::string strGid = COwsCommon::GetPropertyTreeVar( pt, "gid" );
	
	PrtMsg( ev_umcweb_addrbook_ig_add_req, emEventTypeClientRecv, "strIid:%s, strGid=%s", strIid.c_str(), strGid.c_str() );
	
	
	char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chSQL, "insert into %s(%s,%s) values(%s,%s);"
		, TB_ADDRBOOK_IG_NAME, TB_ADDRBOOK_IG_FIELD_IID, TB_ADDRBOOK_IG_FIELD_GID
		, strIid.c_str(), strGid.c_str() );
	BOOL bRet = PTR_DBSTORAGE->ExecuteDML(chSQL);
	
	
	PTR_FCGIPRINTF("{\"event\":\"ev_umcweb_addrbook_ig_add_res\",\"bRet\":\"%d\"}", bRet );
	PrtMsg( ev_umcweb_addrbook_ig_add_res, emEventTypeClientSend, "bRet:%d", bRet );
	
	return NO_ERROR;
}

u16 CUmcAddrbookCtrl::OnAddrbookIgDelReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strIid = COwsCommon::GetPropertyTreeVar( pt, "iid" );
	std::string strGid = COwsCommon::GetPropertyTreeVar( pt, "gid" );
	
	PrtMsg( ev_umcweb_addrbook_ig_del_req, emEventTypeClientRecv, "strIid:%s, strGid=%s", strIid.c_str(), strGid.c_str() );
	
	
	char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chSQL, "delete from %s where %s=%s and %s=%s;", TB_ADDRBOOK_IG_NAME, TB_ADDRBOOK_IG_FIELD_IID, strIid.c_str()
		, TB_ADDRBOOK_IG_FIELD_GID, strGid.c_str() );
	BOOL bRet = PTR_DBSTORAGE->ExecuteDML(chSQL);
	
	PTR_FCGIPRINTF("{\"event\":\"ev_umcweb_addrbook_ig_del_res\",\"bRet\":\"%d\"}", bRet );
	PrtMsg( ev_umcweb_addrbook_ig_del_res, emEventTypeClientSend, "bRet:%d", bRet );
	
	return NO_ERROR;
}

u16 CUmcAddrbookCtrl::OnAddrbookGgAddReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strId = COwsCommon::GetPropertyTreeVar( pt, "id" );
	std::string strPid = COwsCommon::GetPropertyTreeVar( pt, "pid" );
	
	PrtMsg( ev_umcweb_addrbook_gg_add_req, emEventTypeClientRecv, "strId:%s, strPid=%s", strId.c_str(), strPid.c_str() );
	
	
	char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chSQL, "insert into %s(%s,%s) values(%s,%s);"
		, TB_ADDRBOOK_GG_NAME, TB_ADDRBOOK_GG_FIELD_GID, TB_ADDRBOOK_GG_FIELD_GPID
		, strId.c_str(), strPid.c_str() );
	BOOL bRet = PTR_DBSTORAGE->ExecuteDML(chSQL);
	
	
	PTR_FCGIPRINTF("{\"event\":\"ev_umcweb_addrbook_gg_add_res\",\"bRet\":\"%d\"}", bRet );
	PrtMsg( ev_umcweb_addrbook_gg_add_res, emEventTypeClientSend, "bRet:%d", bRet );
	
	return NO_ERROR;
}

u16 CUmcAddrbookCtrl::OnAddrbookGgDelReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strId = COwsCommon::GetPropertyTreeVar( pt, "id" );
	std::string strPid = COwsCommon::GetPropertyTreeVar( pt, "pid" );
	
	PrtMsg( ev_umcweb_addrbook_gg_del_req, emEventTypeClientRecv, "strId:%s, strPid=%s", strId.c_str(), strPid.c_str() );
	
	
	char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chSQL, "delete from %s where %s=%s and %s=%s;", TB_ADDRBOOK_GG_NAME, TB_ADDRBOOK_GG_FIELD_GID, strId.c_str()
		, TB_ADDRBOOK_GG_FIELD_GPID, strPid.c_str() );
	BOOL bRet = PTR_DBSTORAGE->ExecuteDML(chSQL);
	
	PTR_FCGIPRINTF("{\"event\":\"ev_umcweb_addrbook_gg_del_res\",\"bRet\":\"%d\"}", bRet );
	PrtMsg( ev_umcweb_addrbook_gg_del_res, emEventTypeClientSend, "bRet:%d", bRet );
	
	return NO_ERROR;
}

u16 CUmcAddrbookCtrl::OnAddrbookGroupGetReq(const boost::any& arg)
{
	std::string strData = boost::any_cast<std::string>(arg);
	//获取json结构数据
	ptree pt = COwsCommon::GetPropertyTree(strData);
	std::string strPid = COwsCommon::GetPropertyTreeVar( pt, "pid" );
	std::string strSearch = COwsCommon::GetPropertyTreeVar( pt, "search" );

	PrtMsg( ev_umcweb_addrbook_group_get_req, emEventTypeClientRecv, "strPid=%s,strSearch=%s", strPid.c_str(), strSearch.c_str() );

	char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chSQL, "select * from %s where %s=%s;"
		, TB_ADDRBOOK_GG_NAME, TB_ADDRBOOK_GG_FIELD_GPID, strPid.c_str() );
	
	std::vector<ROW> vecRow;
	BOOL bRet = PTR_DBSTORAGE->ExecuteDQL(chSQL, vecRow);
	if ( !bRet )
	{
		return NO_ERROR;
	}

	string strTemp;

	vector<ROW>::iterator itRow = vecRow.begin();
	for ( ; itRow != vecRow.end(); itRow++ )
	{
		ROW row = *itRow;
		strTemp += row[ROW_TB_ADDRBOOK_GG_FIELD_GID];
		strTemp += ",";
	}
	strTemp = strTemp.substr(0,strTemp.length()-1);
	
	sprintf( chSQL, "select * from %s where %s in (%s) and (%s like \"%%%s\%\") order by %s asc;"
		, TB_ADDRBOOK_GROUP_NAME, TB_ADDRBOOK_GROUP_FIELD_ID, strTemp.c_str()
		, TB_ADDRBOOK_GROUP_FIELD_NAME, strSearch.c_str()
		, TB_ADDRBOOK_GROUP_FIELD_NAME );
	
	
	std::vector<ROW> vecRes;
	bRet = PTR_DBSTORAGE->ExecuteDQL(chSQL, vecRes);
	if ( !bRet )
	{
		string strJson = "{\"event\":\"ev_umcweb_addrbook_group_get_res\",\"count\":\"0\"}";
		
		PTR_FCGIPRINTF( strJson.c_str() );
		PrtMsg( ev_umcweb_addrbook_group_get_res, emEventTypeClientSend, "strJson:%s", strJson.c_str() );

		return NO_ERROR;
	}

	std::string strJson;
	if ( vecRes.size() == 0 )
	{
		strJson = "{\"event\":\"ev_umcweb_addrbook_group_get_res\",\"count\":\"0\"}";
	}
	else
	{
		string strJsonHead = "{\"event\":\"ev_umcweb_addrbook_group_get_res\",\"items\":";
		
		vector<string> vecStrJson;
		
		std::vector<ROW>::iterator it = vecRes.begin();
		for ( ; it != vecRes.end(); it++ )
		{
			ROW row = *it;
			std::string strId = row[ROW_TB_ADDRBOOK_GROUP_FIELD_ID];
			std::string strName = row[ROW_TB_ADDRBOOK_GROUP_FIELD_NAME];
			
			char chItem[MAX_SQL_SENTENCE_LENTH] = {0};
			sprintf( chItem, "{\"id\":\"%s\",\"name\":\"%s\"}", strId.c_str(), strName.c_str() );
			
			vecStrJson.push_back(chItem);
		}
		
		strJson = COwsCommon::CreateStringJson( strJsonHead, vecStrJson );
	}
	
	PTR_FCGIPRINTF( strJson.c_str() );
	PrtMsg( ev_umcweb_addrbook_group_get_res, emEventTypeClientSend, "strJson:%s", strJson.c_str() );
	
	return NO_ERROR;
}

void CUmcAddrbookCtrl::OnLinkBreak( const CMessage& cMsg )
{
	ClearData();

	char chSQL[MAX_SQL_SENTENCE_LENTH]={0};
	sprintf( chSQL, "delete from %s;", TB_ADDRBOOK_GLOBLE_NAME );
	PTR_DBSTORAGE->ExecuteDML(chSQL);
	
	PrtMsg( OSP_DISCONNECT, emEventTypeServerRecv,"CUmcAddrbookCtrl::OnLinkBreak"); 
}

void CUmcAddrbookCtrl::updAddrbookLocalState()
{
	char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chSQL, "update %s, %s set %s.%s = %s.%s, %s=%d where %s.%s=%s.%s and %s.%s=%s.%s and %s.%s=%s.%s;"
		, TB_ADDRBOOK_ITEM_NAME, TB_ADDRBOOK_GLOBLE_NAME
		, TB_ADDRBOOK_ITEM_NAME, TB_ADDRBOOK_ITEM_FIELD_TYPE, TB_ADDRBOOK_GLOBLE_NAME, TB_ADDRBOOK_GLOBLE_FIELD_TYPE
		, TB_ADDRBOOK_ITEM_FIELD_ONLINE, TRUE
		, TB_ADDRBOOK_ITEM_NAME, TB_ADDRBOOK_ITEM_FIELD_NAME, TB_ADDRBOOK_GLOBLE_NAME, TB_ADDRBOOK_GLOBLE_FIELD_NAME
		, TB_ADDRBOOK_ITEM_NAME, TB_ADDRBOOK_ITEM_FIELD_NUMBER, TB_ADDRBOOK_GLOBLE_NAME, TB_ADDRBOOK_GLOBLE_FIELD_NUMBER
		, TB_ADDRBOOK_ITEM_NAME, TB_ADDRBOOK_ITEM_FIELD_IP, TB_ADDRBOOK_GLOBLE_NAME, TB_ADDRBOOK_GLOBLE_FIELD_IP);

	PTR_DBSTORAGE->ExecuteDML(chSQL);

	PrtMsg( chSQL );
}