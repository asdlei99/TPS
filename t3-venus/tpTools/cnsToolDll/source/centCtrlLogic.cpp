// centCtrlLogic.cpp: implementation of the CCentCtrlLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "centCtrlLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//状态信息
CCentCfgStatusMesDlg::CCentCfgStatusMesDlg()
{
	
}

CCentCfgStatusMesDlg::~CCentCfgStatusMesDlg()
{
	
}

void CCentCfgStatusMesDlg::RegCBFun()
{
	CCentCfgStatusMesDlg *pThis = GetSingletonPtr();
    REG_GOBAL_MEMBER_FUNC( "CCentCfgStatusMesDlg::InitWnd", CCentCfgStatusMesDlg::InitWnd, pThis, CCentCfgStatusMesDlg );
}

void CCentCfgStatusMesDlg::RegMsg()
{
	CCentCfgStatusMesDlg *pThis =  GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CamPowerState_NTY, CCentCfgStatusMesDlg::OnCameraInfoNty, pThis, CCentCfgStatusMesDlg );
	REG_MSG_HANDLER( UI_CNS_DCAMSTATE_NTY, CCentCfgStatusMesDlg::OnDocCamInfoNty, pThis, CCentCfgStatusMesDlg );
	REG_MSG_HANDLER( UI_CNS_TVSTATE_NTY, CCentCfgStatusMesDlg::OnDisplayInfoNty, pThis, CCentCfgStatusMesDlg );
	REG_MSG_HANDLER( UI_CNS_ACSTATE_NTY, CCentCfgStatusMesDlg::OnUpdateAirInfoNty, pThis, CCentCfgStatusMesDlg );
	REG_MSG_HANDLER( UI_CNS_SCHSTATE_NTY, CCentCfgStatusMesDlg::OnLightInfoNty, pThis, CCentCfgStatusMesDlg );
	REG_MSG_HANDLER( UI_CNS_SCHTEMP_NTY, CCentCfgStatusMesDlg::OnAirInfoNty, pThis, CCentCfgStatusMesDlg );		//空调消息通过灯光消息传过来
}

void CCentCfgStatusMesDlg::UnRegFunc()
{
	
}

bool CCentCfgStatusMesDlg::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	
	string strstate("关");
	string strShotDown("关机");
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateofXinFeng", "关闭", NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcAirConditionState", strShotDown, NULL, TRUE);
	
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight1", strstate, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight2", strstate, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight3", strstate, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight4", strstate, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight5", strstate, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight6", strstate, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight7", strstate, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight8", strstate, NULL, TRUE);
	
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfDisplay1", strShotDown, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfDisplay2", strShotDown, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfDisplay3", strShotDown, NULL, TRUE);
	
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfCamera1", strShotDown, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfCamera2", strShotDown, NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfCamera3", strShotDown, NULL, TRUE);
	
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfDocCamera", strShotDown, NULL, TRUE);
	return true;
}

void CCentCfgStatusMesDlg::Clear()
{
	
}

LRESULT CCentCfgStatusMesDlg::OnCameraInfoNty( WPARAM wParam, LPARAM lParam )
{
	EmCamPowerMode aemCam[MAX_CNCAMERA_NUM];
	for (int i=0;i<3;i++)
	{
		aemCam[i] =  *((EmCamPowerMode*)wParam + i);
	}
	
	String strCamera1Info;
	strCamera1Info += CamStateToString(aemCam[0]);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfCamera1", strCamera1Info, NULL, TRUE );
	
	String strCamera2Info;
	strCamera2Info += CamStateToString(aemCam[1]);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfCamera2", strCamera2Info, NULL, TRUE );
	
	String strCamera3Info;
	strCamera3Info += CamStateToString(aemCam[2]);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfCamera3", strCamera3Info, NULL, TRUE);
	
	return S_OK;
}

String CCentCfgStatusMesDlg::CamStateToString( EmCamPowerMode& emSwitchState )
{
	String strState;
	switch(emSwitchState)
	{
	case emCamPowerOn:
		strState = "开机";
		break;
	case emCamPowerOff:
		strState = "待机";
		break;
	default:
		strState = "关机";
		break;
	}
	return strState;
}

LRESULT CCentCfgStatusMesDlg::OnDocCamInfoNty( WPARAM wParam, LPARAM lParam )
{
	String strState;
	TCentreDCamCfg tDCamCfg;
	LIBDATAMGRPTR->GetDCamState(tDCamCfg, 0);
	
	String strDocCamera;
	
	switch(tDCamCfg.emDCamPowerMode)
	{
	case emDCamPowerOn:
		strState = "开机";
		break;
	case emDCamPowerOff:
		strState = "关机";
		break;
	case emDCamPowerToggle:
		strState = "待机";
		break;
	default:
		strState = "关闭";
	}
	strDocCamera += strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfDocCamera", strDocCamera, NULL, TRUE );
	
	return S_OK;
}

LRESULT CCentCfgStatusMesDlg::OnDisplayInfoNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	TCentreTVCfg atCentreTVCfg[MAX_CENTRETV_NUM];
	memcpy( atCentreTVCfg, LIBDATAMGRPTR->GetCentreTVCfg(), sizeof(atCentreTVCfg)) ;
	
	String strDisplay1Info;
	strDisplay1Info += StateToString(atCentreTVCfg[0].emTvPowerMode);
	UIFACTORYMGR_PTR->SetCaption("CentCfgStatusMesDlg/StcStateOfDisplay1", strDisplay1Info, NULL, TRUE);
	
	String strDisplay2Info;
	strDisplay2Info += StateToString(atCentreTVCfg[1].emTvPowerMode);
	UIFACTORYMGR_PTR->SetCaption("CentCfgStatusMesDlg/StcStateOfDisplay2", strDisplay2Info, NULL, TRUE);
	
	String strDisplay3Info;
	strDisplay3Info += StateToString(atCentreTVCfg[2].emTvPowerMode);
	UIFACTORYMGR_PTR->SetCaption("CentCfgStatusMesDlg/StcStateOfDisplay3", strDisplay3Info, NULL, TRUE);
	
	return S_OK;
}

String CCentCfgStatusMesDlg::StateToString( EmTvPowerMode& emSwitchState )
{
	String strState;
	switch(emSwitchState)
	{
	case emTVPowerON:
		strState = "开机";
		break;
	case emTVPowerOFF:
		strState = "待机";
		break;
	case emTVPowerDown:
		strState = "关机";
		break;
	default:
		strState = "关机";
		break;
	}
	return strState;
}

LRESULT CCentCfgStatusMesDlg::OnUpdateAirInfoNty( WPARAM wParam, LPARAM lParam )
{
	vector<TCentreACCfg> vecCentreAcCfg;
	LIBDATAMGRPTR->GetCentreACCfg(vecCentreAcCfg);
	if ( vecCentreAcCfg.size() > 0 )
	{
		String strAirInfo;
		s8 chAirTemP[8] = {0};
		sprintf( chAirTemP, "%u", vecCentreAcCfg[0].bySetTemp );
		strAirInfo += chAirTemP;
		strAirInfo += "℃";
		
		UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcAirConditionState", "开机", NULL, TRUE);
		UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcTemperateDeg",strAirInfo, NULL, TRUE);
		if ( vecCentreAcCfg[0].emACMode == emCenACChaAir )
		{
			UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateofXinFeng", "开启", NULL, TRUE);
		}
		else
		{
			UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateofXinFeng", "关闭", NULL, TRUE);
		}
	}
	else
	{
		UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcAirConditionState", "关机", NULL, TRUE);
		UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateofXinFeng", "关闭", NULL, TRUE);
	}
	
	return S_OK;
}

LRESULT CCentCfgStatusMesDlg::OnLightInfoNty( WPARAM wParam, LPARAM lParam )
{
	TCentreSchCfg tSchCfg = *(TCentreSchCfg*)wParam;
	//当前不能获得空调开关,只有温度
	String strAirInfo;	
	s8 chAirTemP[8] = {0};
	sprintf( chAirTemP, "%u", tSchCfg.wSchTem );
	strAirInfo += chAirTemP;
	strAirInfo += "℃";
	String strState;

	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcTemperateDeg", strAirInfo, NULL, TRUE);
	
	//设置灯光状态信息

	String strLight1, strLight2, strLight3, strLight4, strLight5, strLight6, strLight7, strLight8;
	switch( tSchCfg.emSchMidLight )
	{
	case emSchMidLightOn:
		strLight1 += "开";
		break;
	case emSchMidLightOff:
		strLight1 += "关";
		break;
	case emSchMidLightInvalid:
		strLight1 += "关";
		break;
	default:
		break;
	}

//	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcLight1", "顶灯 ：", NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight1", strLight1, NULL, TRUE);

	switch( tSchCfg.emSchScrLight )
	{
	case emSchScrLightOn:
		strLight2 += "开";
		break;
	case emSchScrLightOff:
		strLight2 += "关";
		break;
	case emSchScrLightInvalid:
		strLight2 += "关";
		break;
	default:
		break;
	}

//	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcLight2", "机柜灯 ：", NULL, TRUE);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight2", strLight2, NULL, TRUE);
	
	switch( tSchCfg.emSchLight )
	{
	case emSchLightOn:
		strState += "开";
		break;
	case emSchLightOff:
		strState += "关";
		break;
	case emSchLightInvalid:
		strState += "关";
		break;
	default:
		break;
	}

	strLight3 = strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight3", strLight3, NULL, TRUE);
	strLight4 = strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight4", strLight4, NULL, TRUE);
	strLight5 = strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight5", strLight5, NULL, TRUE);
/*	strLight6 = strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight6", strLight6, NULL, TRUE);
	strLight7 = strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight7", strLight7, NULL, TRUE);
	strLight8 = strState;
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcStateOfLight8", strLight8, NULL, TRUE);*/
	//Value_ItemLight LightState( &tSchCfg );
	//UIFACTORYMGR_PTR->SetPropertyValue( LightState, "CentCfgLightDlg/StcTPbg", NULL );	
	return S_OK;
}

LRESULT CCentCfgStatusMesDlg::OnAirInfoNty( WPARAM wParam, LPARAM lParam )
{
//	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcAirConditionState", "开机", NULL, TRUE);
	u16 wSchTem = (u16)wParam;
    //当前不能获得空调开关,只有温度
	String strAirInfo = "";
	
	s8 chAirTemP[8] = {0};
	sprintf( chAirTemP, "%u", wSchTem );
	strAirInfo += chAirTemP;
	strAirInfo += "℃";
	
	UIFACTORYMGR_PTR->SetCaption( "CentCfgStatusMesDlg/StcTemperateDeg", strAirInfo, NULL, TRUE);
	return S_OK;
}

//窗帘
CCentCfgCurtainDlg::CCentCfgCurtainDlg()
{
	
}

CCentCfgCurtainDlg::~CCentCfgCurtainDlg()
{
	
}

void CCentCfgCurtainDlg::RegMsg()
{
	CCentCfgCurtainDlg* pThis = GetSingletonPtr();
	REG_MSG_HANDLER( UI_TPAD_CURTAINSTATE_NTY, CCentCfgCurtainDlg::OnUpdateCurNty, pThis, CCentCfgCurtainDlg ); 
	REG_MSG_HANDLER( UI_CNSTOOL_CENTRE_CurRename_Nty, CCentCfgCurtainDlg::OnUpdateCurName, pThis, CCentCfgCurtainDlg ); 
	REG_MSG_HANDLER( UI_CNSTOOL_CENTRE_CurOpen_Nty, CCentCfgCurtainDlg::OnCurtainInd, pThis, CCentCfgCurtainDlg ); 
	REG_MSG_HANDLER( UI_CNSTOOL_CENTRE_CurNumSet_Nty, CCentCfgCurtainDlg::OnCurtainNumInd, pThis, CCentCfgCurtainDlg ); 
}

void CCentCfgCurtainDlg::RegCBFun()
{
	CCentCfgCurtainDlg *pThis = GetSingletonPtr();
    REG_GOBAL_MEMBER_FUNC( "CCentCfgCurtainDlg::InitWnd", CCentCfgCurtainDlg::InitWnd, pThis, CCentCfgCurtainDlg );

	REG_LIST_CALLFUNC( "CCentCfgCurtainDlg::OnClickCurList", CCentCfgCurtainDlg::OnClickCurList, pThis, CCentCfgCurtainDlg );

	REG_GOBAL_MEMBER_FUNC( "CCentCfgCurtainDlg::OnBtnOptRenameDlg", CCentCfgCurtainDlg::OnBtnOptRenameDlg, pThis, CCentCfgCurtainDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCurtainDlg::OnCurNumCfg", CCentCfgCurtainDlg::OnCurNumCfg, pThis, CCentCfgCurtainDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCurtainDlg::OnBtnSwitchCurtain", CCentCfgCurtainDlg::OnBtnSwitchCurtain, pThis, CCentCfgCurtainDlg );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgCurtainDlg::OnClickCurLstBlack", CCentCfgCurtainDlg::OnClickCurLstBlack, pThis, CCentCfgCurtainDlg );
}

void CCentCfgCurtainDlg::UnRegFunc()
{
	
}

bool CCentCfgCurtainDlg::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	
	CString strCurId;

	m_nSelIndex = -1;
	vector<CString> vecCurtainName;
	for ( s32 nIndex = 0 ; nIndex < MAX_CURTAIN_NUM  ; nIndex ++ )
	{
		strCurId.Format( "%d",nIndex+1);
		vecCurtainName.push_back( strCurId);
	}

	UIFACTORYMGR_PTR->SetComboListData( "CentCfgCurtainDlg/ComboboxCurNum", vecCurtainName, m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme("SchmCurDefault",m_pWndTree);
	return true;
}

void CCentCfgCurtainDlg::SetDefaultCurName( )
{
	StrCpy(m_tTempCenCurInfo.tCenCurName[0].achCurName,"窗帘1");
	StrCpy(m_tTempCenCurInfo.tCenCurName[1].achCurName,"窗帘2");
	StrCpy(m_tTempCenCurInfo.tCenCurName[2].achCurName,"窗帘3");
	StrCpy(m_tTempCenCurInfo.tCenCurName[3].achCurName,"窗帘4");
	StrCpy(m_tTempCenCurInfo.tCenCurName[4].achCurName,"窗帘5");
	StrCpy(m_tTempCenCurInfo.tCenCurName[5].achCurName,"窗帘6");
}

void CCentCfgCurtainDlg::Clear()
{
	m_nSelIndex = -1;
	UIFACTORYMGR_PTR->LoadScheme("SchmCurDefault",m_pWndTree);
}

bool CCentCfgCurtainDlg::OnBtnSwitchCurtain( const IArgs& args )
{
	string strCurtainNum;
	bool bOpen;

	UIFACTORYMGR_PTR->GetSwitchState("CentCfgCurtainDlg/CurtainSwitch",bOpen,m_pWndTree);

	u16 nRet = COMIFMGRPTR->SetCurtainOpenCmd( bOpen == true ? TRUE : FALSE );

	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "窗帘开启请求发送失败" );
		UIFACTORYMGR_PTR->SetSwitchState("CentCfgCurtainDlg/CurtainSwitch",!bOpen,m_pWndTree);
	}

//	UIFACTORYMGR_PTR->LoadScheme( "SchmCurExist", m_pWndTree );
	//if ()
	return true;
}

bool CCentCfgCurtainDlg::OnBtnOptRenameDlg( const IArgs& args )
{
	if ( (m_tCentreCurInfo.byCurNum < 1 ) || (m_tCentreCurInfo.byCurNum > MAX_CURTAIN_NUM) || ( m_nSelIndex >= MAX_CURTAIN_NUM ))
	{
		return false;
	}

	if ( m_nSelIndex >= 0 )
	{
		CMsgDispatch::SendMessage( UI_CNSTOOL_CurtainRename_Nty, (WPARAM)&m_tCentreCurInfo,(LPARAM)&m_nSelIndex);
	}
	else
	{
		CMsgDispatch::SendMessage( UI_CNSTOOL_CurtainRename_Nty, (WPARAM)&m_tCentreCurInfo,NULL);
	}

	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_strRenameOptDlg );

	return true;
}

bool CCentCfgCurtainDlg::OnCurNumCfg( const IArgs& args )
{
	string strCurNum;
	u8	   byCurNumber;
	s8	   chValue[5] = "";

	UIFACTORYMGR_PTR->GetComboText("CentCfgCurtainDlg/ComboboxCurNum",strCurNum,m_pWndTree );
	byCurNumber = atoi(strCurNum.c_str());

	u16 nRet = COMIFMGRPTR->SetCurtainNumber( byCurNumber );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "窗帘数量设置请求发送失败" );
		itoa(m_tCentreCurInfo.byCurNum +1,chValue,10);
		UIFACTORYMGR_PTR->SetComboText( "CentCfgCurtainDlg/ComboboxCurNum",chValue,m_pWndTree );
	}	
	return true;
}

HRESULT CCentCfgCurtainDlg::OnUpdateCurNty( WPARAM wparam, LPARAM lparam )
{
	TCentreCurInfo tCurtainInfo;
	s8	   chValue[5] = "";

	tCurtainInfo = LIBDATAMGRPTR->GetCurtainInfo( );

	m_tCentreCurInfo = tCurtainInfo;

	itoa(m_tCentreCurInfo.byCurNum,chValue,10);

	UIFACTORYMGR_PTR->SetComboText("CentCfgCurtainDlg/ComboboxCurNum",chValue,m_pWndTree );

	vector< TCentreCurName > vec_CurName;
	for( s32 nIndex = 0 ; nIndex < tCurtainInfo.byCurNum; nIndex ++ )
	{
		vec_CurName.push_back(tCurtainInfo.tCenCurName[nIndex]);
	}
	
	Value_CurtainList CCurtainNameList( &vec_CurName );
	UIFACTORYMGR_PTR->SetPropertyValue( CCurtainNameList, "CurtainLstDlg/CurtainList", m_pWndTree);

	if ( tCurtainInfo.bCurOpen == FALSE )
	//if ( tCurtainInfo.byCurNum < 1 )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmCurNotExist", m_pWndTree );
		return S_FALSE;
	}
	
	UIFACTORYMGR_PTR->LoadScheme( "SchmCurExist", m_pWndTree );

	if ( tCurtainInfo.byCurNum < 1)
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmEnable", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmAvaliable", m_pWndTree );
	}
	return S_OK;
}

HRESULT CCentCfgCurtainDlg::OnUpdateCurName( WPARAM wparam, LPARAM lparam )
{
	BOOL bSuccess = *(BOOL*)lparam;
	m_tCentreCurInfo = *( TCentreCurInfo* )wparam;
	
	if ( bSuccess == FALSE )
	{
		WARNMESSAGE( "设置窗帘名称失败" );
		return S_FALSE;
	}

	vector< TCentreCurName > vec_CurName;
	for( s32 nIndex = 0 ; nIndex < m_tCentreCurInfo.byCurNum; nIndex ++ )
	{
		vec_CurName.push_back(m_tCentreCurInfo.tCenCurName[nIndex]);
	}
	
	Value_CurtainList CCurtainNameList( &vec_CurName );
	UIFACTORYMGR_PTR->SetPropertyValue( CCurtainNameList, "CurtainLstDlg/CurtainList", m_pWndTree);

	return S_OK;
}

HRESULT CCentCfgCurtainDlg::OnCurtainInd( WPARAM wparam, LPARAM lparam )
{
	BOOL bOpen = *(BOOL *)wparam;
	BOOL bSuccess = *(BOOL*)lparam;
	
	if ( bSuccess == FALSE )
	{
		WARNMESSAGE( "配置窗帘失败" );
		//	return S_FALSE;
	}
	else
	{
		m_tCentreCurInfo.bCurOpen = bOpen;
	}
	
	if ( m_tCentreCurInfo.bCurOpen == false )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmCurNotExist", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmCurExist", m_pWndTree );
		//	UIFACTORYMGR_PTR->LoadScheme( "SchmAvaliable", m_pWndTree );
	}
	
	return S_OK;
}

HRESULT CCentCfgCurtainDlg::OnCurtainNumInd( WPARAM wparam, LPARAM lparam )
{
	u8 byCurtainNum = *(BOOL *)wparam;
	BOOL bSuccess = *(BOOL*)lparam;
	
	if ( bSuccess == FALSE )
	{
		WARNMESSAGE( "配置窗帘数量失败" );
		return S_FALSE;
	}
	else
	{
		m_tCentreCurInfo.byCurNum = byCurtainNum;
	}
	
	vector< TCentreCurName > vec_CurName;
	for( s32 nIndex = 0 ; nIndex < m_tCentreCurInfo.byCurNum; nIndex ++ )
	{
		vec_CurName.push_back(m_tCentreCurInfo.tCenCurName[nIndex]);
	}
	
	Value_CurtainList CCurtainNameList( &vec_CurName );
	UIFACTORYMGR_PTR->SetPropertyValue( CCurtainNameList, "CurtainLstDlg/CurtainList", m_pWndTree);
	UIFACTORYMGR_PTR->LoadScheme( "SchmCurDefault", m_pWndTree );

	return S_OK;
}

bool CCentCfgCurtainDlg::OnClickCurList( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
		const IData *pIData = pClickInfo->m_pClickList->GetItemData()->GetUserData();
		if ( const Data_CurName * pDataTemp = dynamic_cast< const Data_CurName*>(pIData) )
		{
			TCentreCurName tCurtainName = pDataTemp->m_tCurtainName;
			m_nSelIndex = GetSelItemIndex(tCurtainName);
			return true;
		}
	}

	m_nSelIndex = -1;
	return false;
}

s32 CCentCfgCurtainDlg::GetSelItemIndex( TCentreCurName &tCurtainName )
{
	for( s32 nIndex = 0 ; nIndex < m_tCentreCurInfo.byCurNum; nIndex ++ )
	{
		if ( strcmp(tCurtainName.achCurName,m_tCentreCurInfo.tCenCurName[nIndex].achCurName ) == 0 )
		{
			return nIndex;
		}
	}
	return -1;
}

bool CCentCfgCurtainDlg::OnClickCurLstBlack( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return S_FALSE;
	}
	m_nSelIndex = -1;

	return true;
}


//空调新风

CCentCfgAirCondition::CCentCfgAirCondition()
{
	
}

CCentCfgAirCondition::~CCentCfgAirCondition()
{
	
}

void CCentCfgAirCondition::RegCBFun()
{
	CCentCfgAirCondition *pThis = GetSingletonPtr();
    REG_GOBAL_MEMBER_FUNC( "CCentCfgAirCondition::InitWnd", CCentCfgAirCondition::InitWnd, pThis, CCentCfgAirCondition );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgAirCondition::OnSwitchAirCondition", CCentCfgAirCondition::OnSwitchAirCondition, pThis, CCentCfgAirCondition );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgAirCondition::OnBtnSave", CCentCfgAirCondition::OnBtnSave, pThis, CCentCfgAirCondition );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgAirCondition::OnBtnCancel", CCentCfgAirCondition::OnBtnCancel, pThis, CCentCfgAirCondition );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgAirCondition::OnACNumCfg", CCentCfgAirCondition::OnACNumCfg, pThis, CCentCfgAirCondition );

}

void CCentCfgAirCondition::RegMsg()
{
	CCentCfgAirCondition *pThis =  GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNSTOOL_AirCondtition_Nty, CCentCfgAirCondition::OnAirConditionNty, pThis, CCentCfgAirCondition );
	REG_MSG_HANDLER( UI_CNS_ACSTATE_NTY, CCentCfgAirCondition::OnUpdateAirInfoNty, pThis, CCentCfgAirCondition );
}

void CCentCfgAirCondition::UnRegFunc()
{

}

bool CCentCfgAirCondition::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	
	
	CString strACNum;
	
	vector<CString> vecAcNum;
	for ( s32 nIndex = 1 ; nIndex <= MAX_AC_NUM  ; nIndex ++ )
	{
		strACNum.Format( "%d",nIndex);
		vecAcNum.push_back( strACNum);
	}
	
	UIFACTORYMGR_PTR->SetComboListData( "CentCfgAirConditionDlg/ComboboxACNum", vecAcNum, m_pWndTree );

	m_vctWndName.clear();
	UpBtnState();
//	UIFACTORYMGR_PTR->ShowWindow( g_strRenameOptDlg,false );
	return true;
}

void CCentCfgAirCondition::Clear()
{
	
}

bool CCentCfgAirCondition::OnSwitchAirCondition( const IArgs & arg )
{
	bool bOpen = false;
	string   strScheme;
	string   strAcNum;
	
	UIFACTORYMGR_PTR->GetSwitchState("CentCfgAirConditionDlg/AirConditionButton",bOpen,m_pWndTree);

	if ( bOpen == true )
	{
		strScheme = "SchmACExist";
	}
	else
	{
		strScheme = "SchmACNotExist";
	}

	UIFACTORYMGR_PTR->LoadScheme(strScheme,m_pWndTree);

	UIFACTORYMGR_PTR->GetComboText("CentCfgAirConditionDlg/ComboboxACNum",strAcNum, m_pWndTree);

	if ( strAcNum == "" )
	{
		UIFACTORYMGR_PTR->SetComboText("CentCfgAirConditionDlg/ComboboxACNum","1", m_pWndTree);
	}
	
	UpdateState();
	return true;
}

void CCentCfgAirCondition::UpdateState()
{
	string   strAcNum;
	u8       byAcNum;
	bool bOpen = false;
	bool bChange = false;

	UIFACTORYMGR_PTR->GetSwitchState("CentCfgAirConditionDlg/AirConditionButton",bOpen,m_pWndTree);
	
	if ( bOpen == false )
	{
		byAcNum = 0;
	}
	else
	{
		UIFACTORYMGR_PTR->GetComboText("CentCfgAirConditionDlg/ComboboxACNum",strAcNum, m_pWndTree);
		byAcNum = atoi(strAcNum.c_str());
	}
	
	if ( byAcNum != m_byAcNum )
	{
		bChange = true;
	}

	CheckData("CentCfgAirConditionDlg/ComboboxACNum",bChange);
}

bool CCentCfgAirCondition::OnBtnSave( const IArgs & arg )
{
	bool bOpen = false;
	u8 byAcNum ;
	string strAcNum;

	UIFACTORYMGR_PTR->GetSwitchState("CentCfgAirConditionDlg/AirConditionButton",bOpen,m_pWndTree);

	if ( bOpen == false )
	{
		byAcNum = 0;
	}
	else
	{
		UIFACTORYMGR_PTR->GetComboText("CentCfgAirConditionDlg/ComboboxACNum",strAcNum,m_pWndTree );
		byAcNum = atoi(strAcNum.c_str());
	}
	u16 nRet = COMIFMGRPTR->SetAirConditionCmd( byAcNum );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "空调配置消息发送失败" );
		return false;
	}
	return true;
}

bool CCentCfgAirCondition::OnBtnCancel( const IArgs & arg )
{
	bool bOpen = false;
	
	UpdateAcState();
	m_vctWndName.clear();
	UpBtnState();
/*
	UIFACTORYMGR_PTR->GetSwitchState("CentCfgAirConditionDlg/AirConditionButton",bOpen,m_pWndTree);
	u16 nRet = COMIFMGRPTR->SetAirConditionCmd( bOpen == true ? TRUE : FALSE );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "空调配置消息发送失败" );
		return false;
	}*/
	return true;
}

bool CCentCfgAirCondition::IsACChange()
{
	s32 n = m_vctWndName.size();
	if ( n > 0 )
	{
		return SaveMsgBox();
	}
	return true;
}

bool CCentCfgAirCondition::SaveMsgBox()
{
	IArgs args("");
	MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
	MSG_BOX( nMsgBoxRet, "配置项已修改，是否保存配置？" );	
	if ( MSGBOX_OK == nMsgBoxRet )
	{
		return OnBtnSave(args);		 
	}
	else
	{	
		OnBtnCancel(args);
	}
	return true;
}

bool CCentCfgAirCondition::OnACNumCfg( const IArgs & arg )
{
	UpdateState();

	return true;
}

LRESULT CCentCfgAirCondition::OnAirConditionNty( WPARAM wParam, LPARAM lParam )
{
	BOOL bSuccess = FALSE;
	u8 byAcNum ;

	byAcNum = *( u8 *)wParam;
	bSuccess = *( BOOL *)lParam;

	if ( bSuccess == FALSE )
	{
		WARNMESSAGE( "空调配置失败" );
		return S_FALSE;
	} 
	else
	{
		m_byAcNum = byAcNum;
	}
	
	UpdateAcState();

	m_vctWndName.clear();
	UpBtnState();
	return S_OK;
}

LRESULT CCentCfgAirCondition::OnUpdateAirInfoNty( WPARAM wParam, LPARAM lParam )
{
	m_byAcNum = *(u8*)wParam;
	UpdateAcState();

	m_vctWndName.clear();
	UpBtnState();
	return S_OK;
}

void CCentCfgAirCondition::UpdateAcState()
{
	string   strScheme;
	CString  cstrAcNum;

	UIFACTORYMGR_PTR->SetSwitchState( "CentCfgAirConditionDlg/AirConditionButton" , m_byAcNum > 0 ? true : false, m_pWndTree);
	
	if ( m_byAcNum > 0 )
	{
		strScheme = "SchmACExist";
		cstrAcNum.Format("%d",m_byAcNum);
	}
	else
	{
		strScheme = "SchmACNotExist";
		cstrAcNum = "";
	}
	UIFACTORYMGR_PTR->LoadScheme(strScheme,m_pWndTree);
	UIFACTORYMGR_PTR->SetComboText("CentCfgAirConditionDlg/ComboboxACNum",cstrAcNum.GetBuffer(cstrAcNum.GetLength()), m_pWndTree);
}

//双流演示源
CCentCfgDuoVideo::CCentCfgDuoVideo()
{
	
}

CCentCfgDuoVideo::~CCentCfgDuoVideo()
{
	
}

void CCentCfgDuoVideo::RegMsg()
{
	CCentCfgDuoVideo *pThis =  GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNSTOOL_DUALSCREEN_Nty, CCentCfgDuoVideo::OnDuoVideoNty, pThis, CCentCfgDuoVideo );
}

void CCentCfgDuoVideo::RegCBFun()
{
	CCentCfgDuoVideo *pThis = GetSingletonPtr();
    REG_GOBAL_MEMBER_FUNC( "CCentCfgDuoVideo::InitWnd", CCentCfgDuoVideo::InitWnd, pThis, CCentCfgDuoVideo );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgDuoVideo::OnBtnDuoVideo", CCentCfgDuoVideo::OnBtnDuoVideo, pThis, CCentCfgDuoVideo );
}

void CCentCfgDuoVideo::UnRegFunc()
{
}

bool CCentCfgDuoVideo::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	

	m_bOpen = FALSE;
	//	UIFACTORYMGR_PTR->ShowWindow( g_strRenameOptDlg,false );
	return true;
}

bool CCentCfgDuoVideo::OnBtnDuoVideo( const IArgs & arg )
{
/*	CLogicBase::InitWnd( arg );	*/
	bool bOpen = false;
	
	UIFACTORYMGR_PTR->GetSwitchState("CentCfgDuoVideo/DuoVideoSwitchButton",bOpen,m_pWndTree);
	u16 nRet = COMIFMGRPTR->SetDuoVideoCmd( bOpen == true ? TRUE : FALSE );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "双流屏配置消息发送失败" );
		return false;
	}
	return true;
}

void CCentCfgDuoVideo::Clear()
{
	
}

LRESULT CCentCfgDuoVideo::OnDuoVideoNty( WPARAM wParam, LPARAM lParam )
{
/*	if ( NULL == m_pWndTree )
	{
		return S_FALSE;
	} 
	BOOL bDual = FALSE;
	TTPCnsInfo tCnsInfo;
	LIBDATAMGRPTR->GetLocalCnsInfo( tCnsInfo );

	if ( 255 == tCnsInfo.m_byDualPos)
	{
		bDual = FALSE;
	} 
	else
	{
		bDual = TRUE;
	}
*/
	BOOL bSuccess = FALSE;
	BOOL bOpen = FALSE;

	bOpen = *( BOOL *)wParam;
	bSuccess = *( BOOL *)lParam;

	if ( bSuccess == FALSE )
	{
		WARNMESSAGE( "双流屏配置失败" );
	}
	else
	{
		m_bOpen = bOpen;
	}
	
	UIFACTORYMGR_PTR->SetSwitchState( "CentCfgDuoVideo/DuoVideoSwitchButton" , m_bOpen == TRUE ? true : false, m_pWndTree);
	return S_OK;
}


//矩阵
CCentCfgMatrix::CCentCfgMatrix()
{

}

CCentCfgMatrix::~CCentCfgMatrix()
{

}

void CCentCfgMatrix::RegCBFun()
{
	CCentCfgMatrix *pThis = GetSingletonPtr();
    REG_GOBAL_MEMBER_FUNC( "CCentCfgMatrix::InitWnd", CCentCfgMatrix::InitWnd, pThis, CCentCfgMatrix );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgMatrix::OnChangedMatrixName", CCentCfgMatrix::OnChangedMatrixName, pThis, CCentCfgMatrix );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgMatrix::OnChangedMatrixStore", CCentCfgMatrix::OnChangedMatrixStore, pThis, CCentCfgMatrix );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgMatrix::OnChangedMatrixModel", CCentCfgMatrix::OnChangedMatrixModel, pThis, CCentCfgMatrix );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgMatrix::OnChangedMatrixServer", CCentCfgMatrix::OnChangedMatrixServer, pThis, CCentCfgMatrix );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgMatrix::OnChangedMatrixSwitch", CCentCfgMatrix::OnChangedMatrixSwitch, pThis, CCentCfgMatrix );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgMatrix::OnBtnSave", CCentCfgMatrix::OnBtnSave, pThis, CCentCfgMatrix );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgMatrix::OnBtnCancel", CCentCfgMatrix::OnBtnCancel, pThis, CCentCfgMatrix );
}

void CCentCfgMatrix::RegMsg()
{
	CCentCfgMatrix *pThis =  GetSingletonPtr();
	REG_MSG_HANDLER( UI_MATRIXCONFIG_NTY, CCentCfgMatrix::OnMatrixConfigNty, pThis, CCentCfgMatrix );
}

void CCentCfgMatrix::UnRegFunc()
{
	
}

bool CCentCfgMatrix::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	
	vector<CString> vecStrCombo;
	//矩阵厂商
	vecStrCombo.push_back("KEDACOM");
	UIFACTORYMGR_PTR->SetComboListData( "CentCfgMatrixDlg/ComboboxInMatrixStore", vecStrCombo, m_pWndTree );
	vecStrCombo.clear();
	//矩阵型号
	vecStrCombo.push_back("KMX2000");
	vecStrCombo.push_back("KMX4000");
	UIFACTORYMGR_PTR->SetComboListData( "CentCfgMatrixDlg/ComboboxInMatrixModel", vecStrCombo, m_pWndTree );
	vecStrCombo.clear();
	
	m_vctWndName.clear();
	UpBtnState();
	return true;
}

bool CCentCfgMatrix::OnChangedMatrixName( const IArgs & arg )
{
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( "CentCfgMatrixDlg/MatrixNameEdit", strCaption, m_pWndTree);
	
	bool bChange = false;
	if( strCaption != m_tTPMatrixConfig.m_achMatrixName )
	{
		bChange = true;
	}
	
	CheckData( "CentCfgMatrixDlg/MatrixNameEdit", bChange );
	return true;
}

bool CCentCfgMatrix::OnChangedMatrixStore( const IArgs & arg )
{
	String strCaption;
	UIFACTORYMGR_PTR->GetComboText( "CentCfgMatrixDlg/ComboboxInMatrixStore", strCaption, m_pWndTree);

	EmMatrixFirmType emMatrixFirmType = emKedacom;
	if (strCaption == "KEDACOM")
	{
		emMatrixFirmType = emKedacom;
	}
	
	bool bChange = false;
	if( emMatrixFirmType != m_tTPMatrixConfig.m_emMatrixFirmType )
	{
		bChange = true;
	}
	
	CheckData( "CentCfgMatrixDlg/ComboboxInMatrixStore", bChange );
	return true;
}

bool CCentCfgMatrix::OnChangedMatrixModel( const IArgs & arg )
{
	String strCaption;
	UIFACTORYMGR_PTR->GetComboText( "CentCfgMatrixDlg/ComboboxInMatrixModel", strCaption, m_pWndTree);
	
	EmMatrixModel emMatrixModel = emKMX4000;
	if (strCaption == "KMX4000")
	{
		emMatrixModel = emKMX4000;
	}
	
	bool bChange = false;
	if( emMatrixModel != m_tTPMatrixConfig.m_emMatrixModel )
	{
		bChange = true;
	}
	
	CheckData( "CentCfgMatrixDlg/ComboboxInMatrixModel", bChange );
	return true;
}

bool CCentCfgMatrix::OnChangedMatrixServer( const IArgs & arg )
{
	in_addr tAddr;
	tAddr.S_un.S_addr = m_tTPMatrixConfig.m_tMatrixAddr.GetIP().dwIPV4;
	String strOldIP = inet_ntoa(tAddr);
	if ( "0.0.0.0" == strOldIP )
	{
		strOldIP = "";
	}

	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( "CentCfgMatrixDlg/MatrixServerEdit", strCaption, m_pWndTree);
	
	bool bChange = false;
	if (strCaption != strOldIP)
	{
		bChange = true;
	}

	CheckData( "CentCfgMatrixDlg/MatrixServerEdit", bChange );
	return true;
}

bool CCentCfgMatrix::OnChangedMatrixSwitch( const IArgs & arg )
{
	bool bSwitch = false;
	UIFACTORYMGR_PTR->GetSwitchState("CentCfgMatrixDlg/MatrixSwitchButton",bSwitch,m_pWndTree);

	bool bChange = false;
	if (bSwitch != m_tTPMatrixConfig.m_bOpenUI)
	{
		bChange = true;
	}
	
	CheckData( "CentCfgMatrixDlg/MatrixSwitchButton", bChange );
	return true;
}

bool CCentCfgMatrix::OnBtnSave( const IArgs & arg )
{
	TTPMatrixConfig tTPMatrixConfig;
	//矩阵名称
	String strMatrixName = "";
	UIFACTORYMGR_PTR->GetCaption( "CentCfgMatrixDlg/MatrixNameEdit", strMatrixName, m_pWndTree);
	strncpy( tTPMatrixConfig.m_achMatrixName, strMatrixName.c_str(), sizeof( tTPMatrixConfig.m_achMatrixName ) );
	//矩阵厂商
	String strMatrixFirm = "";
	UIFACTORYMGR_PTR->GetComboText( "CentCfgMatrixDlg/ComboboxInMatrixStore", strMatrixFirm, m_pWndTree);
	if (strMatrixFirm == "KEDACOM")
	{
		tTPMatrixConfig.m_emMatrixFirmType = emKedacom;
	}
	//矩阵型号
	String MatrixModel = "";
	UIFACTORYMGR_PTR->GetComboText( "CentCfgMatrixDlg/ComboboxInMatrixModel", MatrixModel, m_pWndTree);
	if (MatrixModel == "KMX4000")
	{
		tTPMatrixConfig.m_emMatrixModel = emKMX4000;
	}
	//矩阵服务器地址
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( "CentCfgMatrixDlg/MatrixServerEdit" , strCaption , m_pWndTree );
	Value_IpEditData valServerIP;
    UIFACTORYMGR_PTR->GetPropertyValue(valServerIP, "CentCfgMatrixDlg/MatrixServerEdit", m_pWndTree); 
	if ( !CCallAddr::IsValidIpV4(valServerIP.dwIP ) && strCaption.empty() == false)
	{
		MSG_BOX_OK( "矩阵服务器地址非法" );
		UIFACTORYMGR_PTR->SetFocus( "CentCfgMatrixDlg/MatrixServerEdit", m_pWndTree );
		return false;
	}
	tagTTPIPAddress tIP;
	tIP.dwIPV4 = htonl(valServerIP.dwIP);
	tTPMatrixConfig.m_tMatrixAddr.SetIP(tIP);
	//矩阵配置界面
	bool bSwitch = false;
	UIFACTORYMGR_PTR->GetSwitchState("CentCfgMatrixDlg/MatrixSwitchButton",bSwitch,m_pWndTree);
	tTPMatrixConfig.m_bOpenUI = bSwitch;
	//端口写死
	tTPMatrixConfig.m_tMatrixAddr.m_wPort = 5000;

	COMIFMGRPTR->SetMatrixConfig(tTPMatrixConfig);
	return true;
}

bool CCentCfgMatrix::OnBtnCancel( const IArgs & arg )
{
	OnMatrixConfigNty( 0, 0 );
	return true;
}

void CCentCfgMatrix::Clear()
{
	
}

LRESULT CCentCfgMatrix::OnMatrixConfigNty( WPARAM wParam, LPARAM lParam )
{
	memset(&m_tTPMatrixConfig,0,sizeof(TTPMatrixConfig));
	LIBDATAMGRPTR->GetMatrixConfig(m_tTPMatrixConfig);

	//矩阵名称
	String strMatrixName(m_tTPMatrixConfig.m_achMatrixName);
	UIFACTORYMGR_PTR->SetCaption( "CentCfgMatrixDlg/MatrixNameEdit", strMatrixName, m_pWndTree);
	//矩阵厂商
	String strMatrixStore("");
	switch(m_tTPMatrixConfig.m_emMatrixFirmType)
	{
	case emKedacom:
		strMatrixStore = "KEDACOM";
		break;
	default:
		break;
	}
	UIFACTORYMGR_PTR->SetComboText( "CentCfgMatrixDlg/ComboboxInMatrixStore", strMatrixStore, m_pWndTree );
	//矩阵型号
	String strMatrixModel("");
	switch(m_tTPMatrixConfig.m_emMatrixModel)
	{
	case emKMX4000:
		strMatrixModel = "KMX4000";
		break;
	default:
		break;
	}
	UIFACTORYMGR_PTR->SetComboText( "CentCfgMatrixDlg/ComboboxInMatrixModel", strMatrixModel, m_pWndTree );
	//矩阵服务器地址
	Value_IpEditData valIp;
	valIp.dwIP = ntohl(m_tTPMatrixConfig.m_tMatrixAddr.GetIP().dwIPV4);
	UIFACTORYMGR_PTR->SetPropertyValue( valIp, "CentCfgMatrixDlg/MatrixServerEdit", m_pWndTree ); 
	//矩阵配置界面
	UIFACTORYMGR_PTR->SetSwitchState("CentCfgMatrixDlg/MatrixSwitchButton",m_tTPMatrixConfig.m_bOpenUI,m_pWndTree);

	m_vctWndName.clear();
	UpBtnState();
	return S_OK;
}

bool CCentCfgMatrix::IsMatrixChange()
{
	s32 n = m_vctWndName.size();
	if ( n > 0 )
	{
		return SaveMsgBox();
	}
	return true;
}

bool CCentCfgMatrix::SaveMsgBox()
{
	IArgs args("");
	MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
	MSG_BOX( nMsgBoxRet, "配置项已修改，是否保存配置？" );	
	if ( MSGBOX_OK == nMsgBoxRet )
	{
		return OnBtnSave(args);		 
	}
	else
	{	
		OnBtnCancel(args);
	}
	return true;
}

//升降屏
CCentCfgSrceen::CCentCfgSrceen()
{
	m_nGroupNum = 0;
}

CCentCfgSrceen::~CCentCfgSrceen()
{
	
}

void CCentCfgSrceen::RegCBFun()
{
	CCentCfgSrceen *pThis = GetSingletonPtr();
    REG_GOBAL_MEMBER_FUNC( "CCentCfgSrceen::InitWnd", CCentCfgSrceen::InitWnd, pThis, CCentCfgSrceen );
	REG_GOBAL_MEMBER_FUNC( "CCentCfgSrceen::OnChangedGroupCount", CCentCfgSrceen::OnChangedGroupCount, pThis, CCentCfgSrceen );
    REG_GOBAL_MEMBER_FUNC( "CCentCfgSrceen::OnBtnSave", CCentCfgSrceen::OnBtnSave, pThis, CCentCfgSrceen );
    REG_GOBAL_MEMBER_FUNC( "CCentCfgSrceen::OnBtnCancel", CCentCfgSrceen::OnBtnCancel, pThis, CCentCfgSrceen );

}

void CCentCfgSrceen::RegMsg()
{
	CCentCfgSrceen *pThis =  GetSingletonPtr();
}

void CCentCfgSrceen::UnRegFunc()
{
	
}

bool CCentCfgSrceen::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	
	
	CString strACNum;
	vector<CString> vecAcNum;
	for ( s32 nIndex = 1 ; nIndex <= CNS_VGA_TYPE_NUM  ; nIndex ++ )
	{
		strACNum.Format( "%d",nIndex);
		vecAcNum.push_back( strACNum);
	}
	UIFACTORYMGR_PTR->SetComboListData( "CentCfgSrceenDlg/ComboboxInGroupCount", vecAcNum, m_pWndTree );

	vector<CString> vecStrCombo;
	//升降屏类型
	vecStrCombo.push_back("宣德升降屏");
	vecStrCombo.push_back("宣德翻转屏");
	UIFACTORYMGR_PTR->SetComboListData( "CentCfgSrceenDlg/ComboboxInSrceenType", vecStrCombo, m_pWndTree );
	vecStrCombo.clear();
	//升降屏波特率
	vecStrCombo.push_back("300");
	vecStrCombo.push_back("600");
	vecStrCombo.push_back("1200");
	vecStrCombo.push_back("2400");
	vecStrCombo.push_back("4800");
	vecStrCombo.push_back("9600");
	vecStrCombo.push_back("19200");
	vecStrCombo.push_back("38400");
	vecStrCombo.push_back("43000");
	vecStrCombo.push_back("56000");
	vecStrCombo.push_back("57600");
	vecStrCombo.push_back("115200");
	UIFACTORYMGR_PTR->SetComboListData( "CentCfgSrceenDlg/ComboboxInBaudRate", vecStrCombo, m_pWndTree );
	vecStrCombo.clear();
	//升降屏数据位
	vecStrCombo.push_back("6");
	vecStrCombo.push_back("7");
	vecStrCombo.push_back("8");
	UIFACTORYMGR_PTR->SetComboListData( "CentCfgSrceenDlg/ComboboxInDataBits", vecStrCombo, m_pWndTree );
	vecStrCombo.clear();
	//升降屏校验位
	vecStrCombo.push_back("none");
	vecStrCombo.push_back("odd");
	vecStrCombo.push_back("even");
	UIFACTORYMGR_PTR->SetComboListData( "CentCfgSrceenDlg/ComboboxInCheckBits", vecStrCombo, m_pWndTree );
	vecStrCombo.clear();
	//升降屏停止位
	vecStrCombo.push_back("1");
	vecStrCombo.push_back("1.5");
	vecStrCombo.push_back("2");
	UIFACTORYMGR_PTR->SetComboListData( "CentCfgSrceenDlg/ComboboxInStopBits", vecStrCombo, m_pWndTree );
	vecStrCombo.clear();

	//组号
	vecStrCombo.push_back("01");
	vecStrCombo.push_back("02");
	vecStrCombo.push_back("03");
	vecStrCombo.push_back("04");
	vecStrCombo.push_back("05");
 	UIFACTORYMGR_PTR->SetComboListData( "CentCfgSrceenDlg/ComboboxInAddrCode1", vecStrCombo, m_pWndTree );
 	UIFACTORYMGR_PTR->SetComboListData( "CentCfgSrceenDlg/ComboboxInAddrCode2", vecStrCombo, m_pWndTree );
 	UIFACTORYMGR_PTR->SetComboListData( "CentCfgSrceenDlg/ComboboxInAddrCode3", vecStrCombo, m_pWndTree );
 	UIFACTORYMGR_PTR->SetComboListData( "CentCfgSrceenDlg/ComboboxInAddrCode4", vecStrCombo, m_pWndTree );
 	UIFACTORYMGR_PTR->SetComboListData( "CentCfgSrceenDlg/ComboboxInAddrCode5", vecStrCombo, m_pWndTree );
	vecStrCombo.clear();
    m_nGroupNum = 0;

	m_vctWndName.clear();
	UpBtnState();
	return true;
}

void CCentCfgSrceen::Clear()
{
	
}

bool CCentCfgSrceen::OnChangedGroupCount( const IArgs & arg )
{
	String strInCount = "";
	UIFACTORYMGR_PTR->GetComboText( "CentCfgSrceenDlg/ComboboxInGroupCount", strInCount, m_pWndTree );
	EmGroupNum emNum = (EmGroupNum)atoi(strInCount.c_str());
	switch (emNum)
	{
	case emOneGroup:
		UIFACTORYMGR_PTR->LoadScheme( "SchmOneGroup", m_pWndTree );
		break;
	case emTweGroup:
		UIFACTORYMGR_PTR->LoadScheme( "SchmTweGroup", m_pWndTree );
		break;
	case emThreeGroup:
		UIFACTORYMGR_PTR->LoadScheme( "SchmThreeGroup", m_pWndTree );
		break;
	case emFourGroup:
		UIFACTORYMGR_PTR->LoadScheme( "SchmFourGroup", m_pWndTree );
		break;
	case emFiveGroup:
		UIFACTORYMGR_PTR->LoadScheme( "SchmFiveGroup", m_pWndTree );
		break;
	default:
		break;
	}
	bool bChange = false;
	if (emNum != m_nGroupNum)
	{
		m_nGroupNum = emNum;
		bChange = true;
	}

	CheckData("CentCfgSrceenDlg/ComboboxInGroupCount",bChange);
	return true;
}

bool CCentCfgSrceen::OnBtnSave( const IArgs & arg )
{
    TCenDownOrFlipScreenInfo tCenDownOrFlipScreenInfo;
    //设备类型
    String strSrceenType = "";
    UIFACTORYMGR_PTR->GetComboText( "CentCfgSrceenDlg/ComboboxInSrceenType", strSrceenType, m_pWndTree);
    if (strSrceenType == "宣德升降屏")
    {
        tCenDownOrFlipScreenInfo.emDeviceType = emDefault;
    }
    else
    {
        tCenDownOrFlipScreenInfo.emDeviceType = emXuanDeDFScreen;
    }
    //波特率
    String strBaudRate = "";
    UIFACTORYMGR_PTR->GetComboText( "CentCfgSrceenDlg/ComboboxInBaudRate", strBaudRate, m_pWndTree);
    u32 dwBaudRate = (u32)atoi(strBaudRate.c_str());
    tCenDownOrFlipScreenInfo.tSerialCfg.dwBaudRate = dwBaudRate;
    //数据位
    String strDataBits = "";
    UIFACTORYMGR_PTR->GetComboText( "CentCfgSrceenDlg/ComboboxInDataBits", strDataBits, m_pWndTree);
    u8 byDataBits = (u32)atoi(strDataBits.c_str());
    tCenDownOrFlipScreenInfo.tSerialCfg.byByteSize = byDataBits;
    //校验位
    String strCheckBits = "";
    UIFACTORYMGR_PTR->GetComboText( "CentCfgSrceenDlg/ComboboxInCheckBits", strCheckBits, m_pWndTree);
    if (strCheckBits == "none")
    {
        tCenDownOrFlipScreenInfo.tSerialCfg.emCheck = emNoCheck;
    }
    else if (strCheckBits == "odd")
    {
        tCenDownOrFlipScreenInfo.tSerialCfg.emCheck = emOddCheck;
    }
    else
    {
        tCenDownOrFlipScreenInfo.tSerialCfg.emCheck = emEvenCheck;
    }
    //停止位
    String strStopBits = "";
    UIFACTORYMGR_PTR->GetComboText( "CentCfgSrceenDlg/ComboboxInStopBits", strStopBits, m_pWndTree);
    EmStopBits emStopBits = (EmStopBits)atoi(strStopBits.c_str());
    tCenDownOrFlipScreenInfo.tSerialCfg.emStopBits = emStopBits;
    //分组数
    String strGroupCount = "";
    UIFACTORYMGR_PTR->GetComboText( "CentCfgSrceenDlg/ComboboxInGroupCount", strGroupCount, m_pWndTree);
    u32 dwGroupCount = (u32)atoi(strGroupCount.c_str());
    tCenDownOrFlipScreenInfo.dwGroupNum = dwGroupCount;
    m_nGroupNum = dwGroupCount;
    //升降屏组信息
    if (m_nGroupNum > 0)
    {
        string strGroupNameEdit = "CentCfgMatrixDlg/GroupNameEdit";
        string strAddrCodeEdit = "CentCfgMatrixDlg/ComboboxInAddrCode";
        s8 byGroupNum[4];
        for (u32 dwIndex = 0; dwIndex < m_nGroupNum; dwIndex++)
        {
            //组名称
            String strGroupName = "";
            memset(byGroupNum, 0, sizeof(u8)*4);
            itoa(dwIndex+1, byGroupNum, 10);
            UIFACTORYMGR_PTR->GetCaption( strGroupNameEdit+byGroupNum, strGroupName, m_pWndTree);
            strncpy( tCenDownOrFlipScreenInfo.tCenDownOrFlipScreenCfg[dwIndex].achGroupName,
                strGroupName.c_str(), MAX_CENTREDFSCREEN_GROUPNAME_LEN );
            //地址码
            String strAddrCode = "";
            UIFACTORYMGR_PTR->GetComboText( strAddrCodeEdit+byGroupNum, strAddrCode, m_pWndTree);
            EmAddrCode emAddrCode = (EmAddrCode)( atoi(strAddrCode.c_str()) - 1 );
            tCenDownOrFlipScreenInfo.tCenDownOrFlipScreenCfg[dwIndex].emAddrCode = emAddrCode;
        }
        COMIFMGRPTR->SetDFScreenGroupCmd(tCenDownOrFlipScreenInfo.dwGroupNum, tCenDownOrFlipScreenInfo.tCenDownOrFlipScreenCfg);
    }

	COMIFMGRPTR->SetDFScreenConfigCmd(tCenDownOrFlipScreenInfo.emDeviceType, tCenDownOrFlipScreenInfo.tSerialCfg);
    //COMIFMGRPTR->SetDFScreenGroupCmd(tCenDownOrFlipScreenInfo.dwGroupNum, tCenDownOrFlipScreenInfo.tCenDownOrFlipScreenCfg);

    return true;
}

bool CCentCfgSrceen::OnBtnCancel( const IArgs & arg )
{
    //
    return true;
}
