#include "StdAfx.h"
#include "confcallcfglogic.h"
#include "messageboxlogic.h"
#include "confmsglogic.h"

APP_BEGIN_MSG_MAP(CConfCallCfgLogic,CNotifyUIImpl)

	MSG_CREATEWINDOW(_T("ConfCallCfgLayout"), OnCreate)
	MSG_INIWINDOW(_T("ConfCallCfgLayout"), OnInit)

	MSG_CLICK(_T("BtnBack"), OnBtnBack)
	MSG_CLICK(_T("BtnExit"), OnBtnExit)
	MSG_CLICK(_T("BtnOk"), OnBtnOk)
	MSG_CLICK(_T("BtnFixOrCancel"), OnBtnFixOrCancel)
	
	MSG_CLICK(_T("BtnSingleRateMinus"), OnBtnSingleRateMinus)
	MSG_CLICK(_T("BtnSingleRateAdd"), OnBtnSingleRateAdd)
	MSG_CLICK(_T("BtnDulRateMinus"), OnBtnDulRateMinus)
	MSG_CLICK(_T("BtnDulRateAdd"), OnBtnDulRateAdd)
	MSG_CLICK(_T("BtnPollTimeMinus"), OnBtnPollTimeMinus)
	MSG_CLICK(_T("BtnPollTimeAdd"), OnBtnPollTimeAdd)
	

	MSG_SELECTCHANGE(_T("op1080"), Onop1080)
	MSG_SELECTCHANGE(_T("op720"), Onop720)
	MSG_SELECTCHANGE(_T("op4CIF"), Onop4CIF)
	MSG_SELECTCHANGE(_T("op60fps"), Onop60fps)
	MSG_SELECTCHANGE(_T("op50fps"), Onop50fps)
	MSG_SELECTCHANGE(_T("op30fps"), Onop30fps)
	MSG_SELECTCHANGE(_T("op25fps"), Onop25fps)
	MSG_SELECTCHANGE(_T("opN1080"), OnopN1080)
	MSG_SELECTCHANGE(_T("opN720"), OnopN720)
	MSG_SELECTCHANGE(_T("opN4CIF"), OnopN4CIF)
	MSG_SELECTCHANGE(_T("opUXGA"), OnopUXGA)
	MSG_SELECTCHANGE(_T("opWXGA"), OnopWXGA)
	MSG_SELECTCHANGE(_T("opSXGA"), OnopSXGA)
	MSG_SELECTCHANGE(_T("opXGA"), OnopXGA)
	MSG_SELECTCHANGE(_T("opN60fps"), OnopN60fps)
	MSG_SELECTCHANGE(_T("opN50fps"), OnopN50fps)        
	MSG_SELECTCHANGE(_T("opN30fps"), OnopN30fps)
	MSG_SELECTCHANGE(_T("opN25fps"), OnopN25fps)
	MSG_SELECTCHANGE(_T("opN5fps"), OnopN5fps)
	MSG_SELECTCHANGE(_T("opMPEG4"), OnopMPEG4)
	MSG_SELECTCHANGE(_T("opG711A"), OnopG711A)
	MSG_SELECTCHANGE(_T("opG711U"), OnopG711U)
	MSG_SELECTCHANGE(_T("opG719"), OnopG719)
	MSG_SELECTCHANGE(_T("opMP3"), OnopMP3)
	MSG_SELECTCHANGE(_T("opMP4"), OnopMP4)
	MSG_SELECTCHANGE(_T("opG772"), OnopG772)

	MSG_SELECTCHANGE(_T("opAESEncrypt"), OnopAESEncrypt)
	MSG_SELECTCHANGE(_T("opQTEncrypt"), OnopQTEncrypt)
	MSG_SELECTCHANGE(_T("opNoEncrypt"), OnopNoEncrypt)

	MSG_SELECTCHANGE(_T("CheckIsAESPassword"), OnCheckIsAESPassword)
	MSG_SELECTCHANGE(_T("CheckIsPoll"), OnCheckIsPoll)
	MSG_SELECTCHANGE(_T("CheckIsConfDisc"), OnCheckIsConfDisc)

	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)
	USER_MSG(UI_CNSTOOL_AUDIOFORMAT_IND,OnUpdateAudioFormat)
	USER_MSG(UI_CNSTOOL_CONFPOOL_IND,OnUpdateConfPoll)
	USER_MSG(UI_CNSTOOL_CONFDIS_IND,OnUpdateConfDis)
	USER_MSG(UI_CNSTOOL_DUALCALLRATE_IND,OnUpdateDualCallRate)
	USER_MSG(UI_CNSTOOL_CALLRATE_IND,OnUpdateCallRate)
	USER_MSG(UI_CNSTOOL_DUALVIDEOFORMAT_IND,OnUpdateDualVideoFormat)
	USER_MSG(UI_CNSTOOL_VIDEOFORMAT_IND,OnUpdateVideoFormat)
	USER_MSG(UI_ENCRYPTINFO_IND,OnEncryptInfoInd)
	USER_MSG(UI_ENCRYPTINFO_NTY,OnEncryptInfoNty)

    USER_MSG(WM_DUI_EDITSETFOCUS, OnEditSetFocus)

APP_END_MSG_MAP()

const String CConfCallCfgLogic::m_strBtnFixOrCancel = _T("BtnFixOrCancel");
const String CConfCallCfgLogic::m_strBtnOk = _T("BtnOk");

const String CConfCallCfgLogic::m_strEdtOldPassword = _T("edtOldPassword");
const String CConfCallCfgLogic::m_strEdtNewPassword = _T("edtNewPassword");
const String CConfCallCfgLogic::m_strEdtCheckPassword = _T("edtCheckPassword");
const String CConfCallCfgLogic::m_strEdtLockPassword = _T("edtLockPassword");
const String CConfCallCfgLogic::m_strEdtAESPassword = _T("edtAESPassword");
const String CConfCallCfgLogic::m_strCheckIsAESPassword = _T("CheckIsAESPassword");

CConfCallCfgLogic::CConfCallCfgLogic(void)
{
	m_bIsFix = false;
	m_bIsConfDisc = false;
	m_bIsPoll = false;
}


CConfCallCfgLogic::~CConfCallCfgLogic(void)
{
}

bool CConfCallCfgLogic::OnCreate( TNotifyUI& msg )
{
	REG_CNC_MSG_WND_OB(m_pm->GetPaintWindow());

	s32 nTop = DEFAULT_TITLE_HEIGHT;
	if ( CPaintManagerUI::IsSelfAdaption() )
	{
		float fAdpX, fAdpY;
		CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
		nTop = s32(nTop * fAdpY);
	}
	SetWindowPos( m_pm->GetPaintWindow(), NULL, 0, nTop, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );
	return false;
}

bool CConfCallCfgLogic::OnInit( TNotifyUI& msg )
{
	memset( &m_tVidForamt, 0, sizeof(m_tVidForamt) );
	memset( &m_tDualVidForamt, 0, sizeof(m_tDualVidForamt) );
	m_emAudioFormat = emTPAEnd;
	m_bIsFix = false;
	m_bIsConfDisc = false;
	m_bIsPoll = false;
	return true;
}


bool CConfCallCfgLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	memset( &m_tVidForamt, 0, sizeof(m_tVidForamt) );
	memset( &m_tDualVidForamt, 0, sizeof(m_tDualVidForamt) );
	m_tEncryptInfo.Clear();
	m_emAudioFormat = emTPAEnd;
	m_bIsFix = false;
	m_bIsConfDisc = false;
	m_bIsPoll = false;
	m_pm->DoCase(_T("caseSetCancel"));
	ICncCommonOp::ShowControl(false,m_pm,_T("BtnOk"));
	ICncCommonOp::SetControlText(_T("修 改"),m_pm,_T("BtnFixOrCancel"));

	return true;
}

bool CConfCallCfgLogic::OnBtnOk( TNotifyUI& msg )
{
	BOOL bInConf = ComInterface->IsInConf();
	if ( bInConf )
	{		
		ShowMessageBox(_T("会议中，不能进行会议呼叫设置"));
		return false;
	}

	if ( !SaveRate()|| !SaveVideoFormat() || !SaveDualVideoFormat() 
		|| !SaveConfDis() || !SaveConfPoll() || !SaveAudioFormat() || !SaveConfEncryptInfo())
	{
		return false;
	}

	OnBtnFixOrCancel(msg);
	return true;
}

bool CConfCallCfgLogic::OnBtnFixOrCancel( TNotifyUI& msg )
{
	BOOL bInConf = ComInterface->IsInConf();
	bool bHandle = true;
	if ( bInConf && !m_bIsFix)
	{		
		ShowMessageBox(_T("会议中，不能进行会议呼叫设置"));
		return false;
	}

	m_bIsFix = !m_bIsFix;

	if ( m_bIsFix )
	{
		ICncCommonOp::ShowControl(true,m_pm,_T("BtnOk"));
		ICncCommonOp::SetControlText(_T("取 消"),m_pm,_T("BtnFixOrCancel"));
	}
	else
	{		
		ICncCommonOp::ShowControl(false,m_pm,_T("BtnOk"));
		ICncCommonOp::SetControlText(_T("修 改"),m_pm,_T("BtnFixOrCancel"));
	}

	setFixEnable(m_bIsFix);
	OnUpdateVideoFormat(NULL,NULL,bHandle);
	OnUpdateDualVideoFormat(NULL,NULL,bHandle);
	OnUpdateAudioFormat(NULL,NULL,bHandle);
	OnUpdateCallRate(NULL,NULL,bHandle);
	OnUpdateDualCallRate(NULL,NULL,bHandle);
	OnEncryptInfoNty(NULL,NULL,bHandle);
	OnUpdateConfDis(NULL,NULL,bHandle);
	OnUpdateConfPoll(NULL,NULL,bHandle);
	return true;
}

bool CConfCallCfgLogic::OnBtnBack( TNotifyUI& msg )
{
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight(g_strConfCallCfgDlg.c_str(),false );
	return true;
}

bool CConfCallCfgLogic::OnBtnExit( TNotifyUI& msg )
{
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight(g_strConfCallCfgDlg.c_str(),false );
	return true;
}

bool CConfCallCfgLogic::setFixEnable(bool bIsEnable)
{
	if ( bIsEnable )
	{
		m_pm->DoCase(_T("caseSet"));
	}
	else
	{
		m_pm->DoCase(_T("caseSetCancel"));
	}
	return true;
}


bool CConfCallCfgLogic::OnBtnSingleRateMinus( TNotifyUI& msg )
{
	CString str = (ICncCommonOp::GetControlText(m_pm,_T("edtSingleRate"))).c_str();
	int dwNum = _ttoi(str);
	if ( dwNum == 512)
	{
		return NO_ERROR;
	}
	dwNum  = GetRateFixed(dwNum,false);
	str.Format(_T("%d"), dwNum);

	ICncCommonOp::SetControlText(str,m_pm,_T("edtSingleRate"));
	
	return NO_ERROR;
}

bool CConfCallCfgLogic::OnBtnSingleRateAdd( TNotifyUI& msg )
{
	CString str = (ICncCommonOp::GetControlText(m_pm,_T("edtSingleRate"))).c_str();
	int dwNum = _ttoi(str);
	if ( dwNum == 8192)
	{
		return NO_ERROR;
	}

	dwNum  = GetRateFixed(dwNum,true);
	str.Format(_T("%d"), dwNum);

	ICncCommonOp::SetControlText(str,m_pm,_T("edtSingleRate"));
	return NO_ERROR;
}

bool CConfCallCfgLogic::OnBtnDulRateMinus( TNotifyUI& msg )
{
	CString str = (ICncCommonOp::GetControlText(m_pm,_T("edtDulRate"))).c_str();
	int dwNum = _ttoi(str);
	if ( dwNum == 512 )
	{
		return NO_ERROR;
	}
	dwNum = GetRateFixed(dwNum,false);
	str.Format(_T("%d"), dwNum);

	ICncCommonOp::SetControlText(str,m_pm,_T("edtDulRate"));
	return NO_ERROR;
}

bool CConfCallCfgLogic::OnBtnDulRateAdd( TNotifyUI& msg )
{
	CString str = (ICncCommonOp::GetControlText(m_pm,_T("edtDulRate"))).c_str();
	int dwNum = _ttoi(str);
	if ( dwNum == 8192)
	{
		return NO_ERROR;
	}
	dwNum  = GetRateFixed(dwNum,true);
	str.Format(_T("%d"), dwNum);
	
	ICncCommonOp::SetControlText(str,m_pm,_T("edtDulRate"));
	return NO_ERROR;
}

bool CConfCallCfgLogic::OnBtnPollTimeMinus( TNotifyUI& msg )
{	
	CString str = (ICncCommonOp::GetControlText(m_pm,_T("edtPollTime"))).c_str();
	int dwNum = _ttoi(str);
	dwNum --;
	if ( dwNum < 5)
	{
		return NO_ERROR;
	}
	str.Format(_T("%d"), dwNum);
	
	ICncCommonOp::SetControlText(str,m_pm,_T("edtPollTime"));
	return NO_ERROR;
}

bool CConfCallCfgLogic::OnBtnPollTimeAdd( TNotifyUI& msg )
{
	CString str = (ICncCommonOp::GetControlText(m_pm,_T("edtPollTime"))).c_str();
	int dwNum = _ttoi(str);
	dwNum ++;
	if ( dwNum > 7200)
	{
		return NO_ERROR;
	}
	str.Format(_T("%d"), dwNum);
	
	ICncCommonOp::SetControlText(str,m_pm,_T("edtPollTime"));
	return NO_ERROR;
}

bool CConfCallCfgLogic::OnCheckIsPoll( TNotifyUI& msg )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	if ( pCheckBox->IsSelected() )
	{
		m_bIsPoll = true;
		ICncCommonOp::EnableControl(true,m_pm,_T("BtnPollTimeMinus")); 
		ICncCommonOp::EnableControl(true,m_pm,_T("BtnPollTimeAdd")); 
		ICncCommonOp::EnableControl(true,m_pm,_T("edtPollTime")); 
	}
	else
	{
		m_bIsPoll = false;
		ICncCommonOp::EnableControl(false,m_pm,_T("BtnPollTimeMinus")); 
		ICncCommonOp::EnableControl(false,m_pm,_T("BtnPollTimeAdd")); 
		ICncCommonOp::EnableControl(false,m_pm,_T("edtPollTime")); 
	}

	return true;
}

bool CConfCallCfgLogic::OnCheckIsConfDisc( TNotifyUI& msg )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	if ( pCheckBox->IsSelected() )
	{
		m_bIsConfDisc = true;
	}
	else
	{
		m_bIsConfDisc = false;
	}
	return true;
}

bool CConfCallCfgLogic::OnUpdateAudioFormat( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
	m_emAudioFormat = ComInterface->GetAudioFormatInfo();
	SetAudioFormat();
	return S_OK;
}

bool CConfCallCfgLogic::OnUpdateDualVideoFormat( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
	ComInterface->GetDualVideoFormatInfo(m_tDualVidForamt);
	SetCallServerShowMode();
	return S_OK;
}

bool CConfCallCfgLogic::OnUpdateCallRate( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
	u16 wCallRate;
	ComInterface->GetCallRateInfo( wCallRate );
	s8 chCallRate[8] = {0};
	sprintf( chCallRate, "%u", wCallRate );

	ICncCommonOp::SetControlText(CA2T(chCallRate),m_pm,_T("lbSingleRate"));
	ICncCommonOp::SetControlText(CA2T(chCallRate),m_pm,_T("edtSingleRate"));
	return S_OK;
}

bool CConfCallCfgLogic::OnUpdateDualCallRate( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
	u16 wDualCallRate;
	ComInterface->GetDualCallRateInfo( wDualCallRate );
	s8 chDualCallRate[8] = {0};
	sprintf( chDualCallRate, "%u", wDualCallRate );

	ICncCommonOp::SetControlText(CA2T(chDualCallRate),m_pm, _T("lbDulRate"));
	ICncCommonOp::SetControlText(CA2T(chDualCallRate),m_pm, _T("edtDulRate"));
	return S_OK;
}

bool CConfCallCfgLogic::OnUpdateConfDis( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
	BOOL bDis;
	ComInterface->GetConfDisInfo( bDis );

	CButtonUI *pBtnPollTimeMinus = (CButtonUI*)ICncCommonOp::FindControl( m_pm, _T("BtnPollTimeMinus") ); 

	CLabelUI *plbIsConfDisc = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbIsConfDisc") );
	if(plbIsConfDisc)
	{
		CString str = _T("关");
		if (bDis)
		{
			str = _T("开");
		}
		plbIsConfDisc->SetText(str);
	}
	CCheckBoxUI *pCheckIsConfDisc = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckIsConfDisc") );
	if(pCheckIsConfDisc)
	{
		pCheckIsConfDisc->Selected(bDis);
	}
	return S_OK;
}

bool CConfCallCfgLogic::OnUpdateConfPoll( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
	TTPPollInfo tPollInfo;
	ComInterface->GetConfPollInfo( tPollInfo );

	s8 chPollTime[8] = {0};
	sprintf( chPollTime, "%u", tPollInfo.wPollExpire );
	CString strTime(chPollTime);

	ICncCommonOp::SetControlText(strTime,m_pm,_T("lbPollTime"));
	ICncCommonOp::SetControlText(strTime,m_pm,_T("edtPollTime"));

	CCheckBoxUI *pCheckIsPoll = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckIsPoll") );
	if(pCheckIsPoll)
	{
		pCheckIsPoll->Selected(tPollInfo.bIsPoll);
	}

	ICncCommonOp::EnableControl(tPollInfo.bIsPoll,m_pm,_T("edtPollTime")); 
	if (tPollInfo.bIsPoll)
	{
		ICncCommonOp::SetControlText(_T("开"),m_pm,_T("lbIsPoll"));
	}
	else
	{
		ICncCommonOp::SetControlText(_T("关"),m_pm,_T("lbIsPoll"));
	}
	
	return S_OK;
}

void CConfCallCfgLogic::SetCallServerMode()
{
	CString strMode = _T("");
	CString strOp = _T("");

	switch ( m_tVidForamt.emTpVideoResolution )
	{
	case emTPVHD1080p1920x1080:
		{
			strMode += _T("1080P");
			strOp = _T("op1080");
			break;
		}
	case emTPVHD720p1280x720:
		{
			strMode += _T("720P");
			strOp = _T("op720");
			break;
		}
	case emTPV4CIF:
		{
			strMode += _T("4CIF");
			strOp = _T("op4CIF");


			break;
		}
	default:
		break;		
	}

	ICncCommonOp::SetControlText(strMode,m_pm,_T("lb1080"));
	COptionUI *pOp = (COptionUI*)ICncCommonOp::FindControl( m_pm, strOp );
	if (pOp)
	{
		pOp->Selected(true);
	}
	

	CString strRate = _T("");
	CString strOpRate = _T("");
	switch ( m_tVidForamt.wVidFrameRate )
	{
	case 60:
		{
			strRate += _T("60fps");
			strOpRate = _T("op60fps");
			break;
		}
	case 50:
		{
			strRate += _T("50fps");
			strOpRate = _T("op50fps");
			break;
		}
	case 30:
		{
			strRate += _T("30fps");
			strOpRate = _T("op30fps");
			break;
		}
	case 25:
		{
			strRate += _T("25fps");
			strOpRate = _T("op25fps");
			break;
		}
	default:
		break;		
	}

	ICncCommonOp::SetControlText(strRate,m_pm,_T("lb60fps"));
	COptionUI *pOpRate = (COptionUI*)ICncCommonOp::FindControl( m_pm, strOpRate );
	if (pOpRate)
	{
		pOpRate->Selected(true);
	}
}

void CConfCallCfgLogic::SetCallServerShowMode()
{
	CString strMode = _T("");
	CString strOp = _T("");
	switch ( m_tDualVidForamt.emTpVideoResolution )
	{
	case emTPVHD1080p1920x1080:
		{
			strMode += _T("1080P");
			strOp = _T("opN1080");
			break;
		}
	case emTPVHD720p1280x720:
		{
			strMode += _T("720P");
			strOp = _T("opN720");
			break;
		}
	case emTPVGA1600x1200:
		{
			strMode += _T("UXGA");
			strOp = _T("opUXGA");
			break;
		}
	case emTPVGA1280x800:
		{
			strMode += _T("WXGA");
			strOp = _T("opWXGA");
			break;
		}
	case emTPVGA1280x1024:
		{
			strMode += _T("SXGA");
			strOp = _T("opSXGA");
			break;
		}
	case emTPVGA1024x768:
		{
			strMode += _T("XGA");
			strOp = _T("opXGA");
			break;
		}
	case emTPV4CIF:
		{
			strMode += _T("4CIF");
			strOp = _T("opN4CIF");
			break;
		}
	default:
		break;		
	}

	ICncCommonOp::SetControlText(strMode,m_pm,_T("lbN1080"));
	COptionUI *pOp = (COptionUI*)ICncCommonOp::FindControl( m_pm, strOp );
	if (pOp)
	{
		pOp->Selected(true);
	}


	CString strRate = _T("");
	CString strRateOp = _T("");
	switch ( m_tDualVidForamt.wVidFrameRate )
	{
	case 60:
		{
			strRate += _T("60fps");
			strRateOp = _T("opN60fps");
			break;
		}
	case 50:
		{
			strRate += _T("50fps");
			strRateOp = _T("opN50fps");
			break;
		}
	case 30:
		{
			strRate += _T("30fps");
			strRateOp = _T("opN30fps");
			break;
		}
	case 25:
		{
			strRate += _T("25fps");
			strRateOp = _T("opN25fps");
			break;
		}
	case 5:
		{
			strRate += _T("5fps");
			strRateOp = _T("opN5fps");
			break;
		}
	default:
		break;		
	}

	ICncCommonOp::SetControlText(strRate,m_pm,_T("lbN60fps"));
	COptionUI *pRateOp = (COptionUI*)ICncCommonOp::FindControl( m_pm, strRateOp );
	if (pRateOp)
	{
		pRateOp->Selected(true);
	}
}

void CConfCallCfgLogic::SetAudioFormat()
{
	CString strFormat = _T("");
	CString strFormatOp = _T("");
	switch ( m_emAudioFormat )
	{
	case emTPAMpegAACLD:
		{
			strFormat += _T("MPEG4 AAC-LD单声道");
			strFormatOp = _T("opMPEG4");
			break;
		}
	case emTPAG711a:
		{
			strFormat += _T("G.711A");
			strFormatOp = _T("opG711A");
			break;
		}
	case emTPAG711u:
		{
			strFormat += _T("G.711U");
			strFormatOp = _T("opG711U");
			break;
		}
	case emTPAG719:
		{
			strFormat += _T("G.719");
			strFormatOp = _T("opG719");
			break;
		}
	case emTPAG7221:
		{
			strFormat += _T("G.722.1 Annex C Polycom Siren14");
			strFormatOp = _T("opG772");
			break;
		}
	case emTPAMP3:
		{
			strFormat += _T("MP3");
			strFormatOp = _T("opMP3");
			break;
		}
	case emTPAMpegAACLC:
		{
			strFormat += _T("MPEG4 AAC-LC单声道");
			strFormatOp = _T("opMP4");
			break;
		}
	default:
		break;
	}

	ICncCommonOp::SetControlText(strFormat,m_pm,_T("lbMPEG4"));
	COptionUI *pRateOp = (COptionUI*)ICncCommonOp::FindControl( m_pm, strFormatOp );
	if (pRateOp)
	{
		pRateOp->Selected(true);
	}
}


bool CConfCallCfgLogic::OnUpdateVideoFormat( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
	ComInterface->GetVideoFormatInfo(m_tVidForamt);
	SetCallServerMode();
	return S_OK;
}

bool CConfCallCfgLogic::SaveVideoFormat()
{
	bool bChange = false;
	bChange = IsVideoFomatChange();
	if ( bChange )
	{
		u16 wRet = ComInterface->VideoFormatCmd( m_tVidForamt );
		if (wRet != NO_ERROR)
		{
			ShowMessageBox((_T("保存会议优选格式请求发送失败")),false);
			return false;
		}
	} 
	return true;
}

bool CConfCallCfgLogic::SaveDualVideoFormat()
{
	bool bChange = false;
	bChange = IsDualVideoFomatChange();
	if ( bChange )
	{
		u16 wRet = ComInterface->DualVideoFormatCmd( m_tDualVidForamt );
		if (wRet != NO_ERROR)
		{
			ShowMessageBox((_T("保存演示优选格式请求发送失败")),false);
			return false;
		}
	} 
	return true;
}

bool CConfCallCfgLogic::SaveConfDis()
{
	bool bChange = false;
	bChange = IsConfDisChange();
	if ( bChange )
	{
		bool bUse = false;
		CCheckBoxUI* pCheckBox= (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckIsConfDisc") );
		if (pCheckBox)
		{
			bUse = pCheckBox->GetCheck();
		}

		u16 wRet = ComInterface->ConfDisCmd(bUse);
		if (wRet != NO_ERROR)
		{
			ShowMessageBox((_T("保存会议讨论设置请求发送失败")),false);
			return false;
		}
	} 
	return true;
}

bool CConfCallCfgLogic::SaveConfPoll()
{
	bool bChange = false;
	bChange = IsConfPollChange();
	if ( bChange )
	{
		bool bUse = false;
		String strPollTime;
		TTPPollInfo tPollInfo;
		CCheckBoxUI* pCheckBox= (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckIsPoll") );
		if (pCheckBox)
		{
			bUse = pCheckBox->GetCheck();
		}

		strPollTime = ICncCommonOp::GetControlText(m_pm,_T("edtPollTime"));
		tPollInfo.wPollExpire = _ttoi( strPollTime.c_str() );
		CEditUI* pEdit= (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("edtPollTime") );

		if (( tPollInfo.wPollExpire > 7200 ) || ( tPollInfo.wPollExpire < 5 ))
		{
			ShowMessageBox(_T("会议轮询时间范围是5-7200s"));
			if ( ( pEdit != NULL )&& ( bUse == true ))
			{
				pEdit->SetFocusX();
			}
			else if ( ( pEdit != NULL ) && ( bUse == false ))
			{
				bool bHandle  = false;
				OnUpdateConfPoll(NULL,NULL,bHandle);
			}
			return false;
		}

		tPollInfo.bIsPoll = (BOOL)bUse;
		u16 wRet = ComInterface->ConfPollCmd(tPollInfo);
		if (wRet != NO_ERROR)
		{
			ShowMessageBox(_T("保存会议轮询设置请求发送失败"));
			return false;
		}
	} 
	return true;
}

bool CConfCallCfgLogic::SaveAudioFormat()
{
	bool bChange = false;
	bChange = IsAudioFormatChange();
	if ( bChange )
	{
		u16 wRet = ComInterface->AudioFormatCmd(m_emAudioFormat);
		if (wRet != NO_ERROR)
		{
			ShowMessageBox((_T("保存音频格式设置请求发送失败")),false);
			return false;
		}
	}
	return true;
}


//bool CConfCallCfgLogic::SaveAESPassWord()
//{
//	TTpEncryptKey tEncrytOri;
//	TTpEncryptKey tEncryt;
//	ComInterface->GetEncrytInfo( tEncrytOri );
//
//    bool bCheckAes = false;
//    CCheckBoxUI* pcheck = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckIsAESPassword"));
//    if ( pcheck != NULL )
//    {
//        bCheckAes = pcheck->GetCheck();
//    }
//
//	if ( bCheckAes )
//	{
//		tEncryt = tEncrytOri;
//		tEncryt.emTPEncryptType = emTPEncryptTypeAES;
//
////2015-6-9  去掉密码 xcr确认 dyy
//// 		String strAESPass = ICncCommonOp::GetControlText(m_pm,_T("edtAESPassword"));
//// 		if ( strAESPass.empty())
//// 		{
//// 			ShowMessageBox(_T("AES密码不能为空"),false);
//// 			CEditUI* pEditUI= (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("edtAESPassword") );
//// 			if (pEditUI)
//// 			{
//// 				pEditUI->SetFocus();
//// 			}
//// 			return false;
//// 		}
//// 		tEncryt.byLen = strAESPass.length();
//// 		memcpy(tEncryt.byKey,CT2A(strAESPass.c_str()),strAESPass.length());
//// 
//// 		tEncryt.byKey[TP_MAXLEN_ENCRYPTKEY-1]='\0';			
//	}
//	else
//	{
//		tEncryt.emTPEncryptType = emTPEncryptTypeNone;
//	}
//
//// 	s8 achOri[TP_MAXLEN_ENCRYPTKEY];
//// 	s8 ach[TP_MAXLEN_ENCRYPTKEY];
//// 	memcpy(achOri,tEncryt.byKey,sizeof(tEncryt.byKey));
//// 	memcpy(ach,tEncrytOri.byKey,sizeof(tEncrytOri.byKey));
//
//	if ( tEncryt.emTPEncryptType != tEncrytOri.emTPEncryptType /*|| (m_bIsAESPassWord && strcmp(achOri,ach) != 0) */)
//	{
//		u16 wRet = ComInterface->EncrytCmd(tEncryt);
//		if (wRet != NO_ERROR)
//		{
//			ShowMessageBox((_T("保存密码设置失败")),false);
//			return false;
//		}
//	}
//	return true;
//}

bool CConfCallCfgLogic::IsVideoFomatChange()
{
	bool bChange = false;
	TTPVidForamt tVidForamt;
	ComInterface->GetVideoFormatInfo(tVidForamt);

	COptionUI* pOpt = NULL;

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("op1080"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tVidForamt.emTpVideoResolution = emTPVHD1080p1920x1080;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("op720"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tVidForamt.emTpVideoResolution = emTPVHD720p1280x720;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("op4CIF"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tVidForamt.emTpVideoResolution = emTPV4CIF;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("op60fps"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tVidForamt.wVidFrameRate = 60;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("op50fps"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tVidForamt.wVidFrameRate = 50;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("op30fps"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tVidForamt.wVidFrameRate = 30;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("op25fps"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tVidForamt.wVidFrameRate = 25;
	}

	if ( m_tVidForamt.emTpVideoResolution != tVidForamt.emTpVideoResolution || m_tVidForamt.emTpVideoQualityLevel != tVidForamt.emTpVideoQualityLevel
		|| m_tVidForamt.wVidFrameRate != tVidForamt.wVidFrameRate)
	{
		bChange = true;	
	}	
	return bChange;
}

bool CConfCallCfgLogic::IsDualVideoFomatChange()
{
	bool bChange = false;
	TTPVidForamt tDualVidForamt;
	ComInterface->GetDualVideoFormatInfo(tDualVidForamt);

	COptionUI* pOpt = NULL;

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opN1080"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tDualVidForamt.emTpVideoResolution = emTPVHD1080p1920x1080;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opN720"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tDualVidForamt.emTpVideoResolution = emTPVHD720p1280x720;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opN4CIF"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tDualVidForamt.emTpVideoResolution = emTPV4CIF;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opUXGA"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tDualVidForamt.emTpVideoResolution = emTPVGA1600x1200;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opWXGA"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tDualVidForamt.emTpVideoResolution = emTPVGA1280x800;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opSXGA"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tDualVidForamt.emTpVideoResolution = emTPVGA1280x1024;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opXGA"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tDualVidForamt.emTpVideoResolution = emTPVGA1024x768;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opN60fps"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tDualVidForamt.wVidFrameRate = 60;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opN50fps"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tDualVidForamt.wVidFrameRate = 50;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opN30fps"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tDualVidForamt.wVidFrameRate = 30;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opN25fps"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tDualVidForamt.wVidFrameRate = 25;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opN5fps"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tDualVidForamt.wVidFrameRate = 5;
	}

	if ( m_tDualVidForamt.emTpVideoResolution != tDualVidForamt.emTpVideoResolution || m_tDualVidForamt.emTpVideoQualityLevel != tDualVidForamt.emTpVideoQualityLevel
		|| m_tDualVidForamt.wVidFrameRate != tDualVidForamt.wVidFrameRate)
	{
		bChange = true;	
	}	
	return bChange;
}

bool CConfCallCfgLogic::IsCallRateChange()
{
	bool bChange = false;
	String strCaption;
	u16 wCallRate;
	ComInterface->GetCallRateInfo( wCallRate );		

	strCaption = ICncCommonOp::GetControlText(m_pm,_T("edtSingleRate"));
	u32 nVal = _ttoi( strCaption.c_str() );
	if ( wCallRate != nVal )
	{
		bChange = true;
	}
	return bChange;
}

bool CConfCallCfgLogic::IsDualCallRateChange()
{
	bool bChange = false;
	String strCaption;
	u16 wShowRate;
	ComInterface->GetDualCallRateInfo( wShowRate );

	strCaption = ICncCommonOp::GetControlText(m_pm,_T("edtDulRate"));
	u32 nVal = _ttoi( strCaption.c_str() );
	//演示码率为0，再删成空,edit框内值置为0，防止能保存空值 
	if ( strCaption.empty() )
	{
		s8 pVal[5] = {0} ;
		sprintf( pVal, "%d", nVal );
		ICncCommonOp::SetControlText((LPCTSTR)pVal, m_pm,_T("edtDulRate"));
	}
	if ( wShowRate != nVal ) 
	{
		bChange = true;
	}	
	return bChange;
}

bool CConfCallCfgLogic::IsConfDisChange()
{
	bool bChange = false; 
	bool bUse = false;
	BOOL bDis;
	ComInterface->GetConfDisInfo( bDis );		

	CCheckBoxUI* pCheckBox= (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckIsConfDisc") );
	if (pCheckBox)
	{
		bUse = pCheckBox->GetCheck();
	}

	if ( bDis != (BOOL)bUse )
	{
		bChange = true;
	}
	return bChange;
}

bool CConfCallCfgLogic::IsConfPollChange()
{
	bool bChange = false; 
	bool bUse = false;
	String strCaption;
	TTPPollInfo tPollInfo;
	ComInterface->GetConfPollInfo( tPollInfo );

	CCheckBoxUI* pCheckBox= (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckIsPoll") );
	if (pCheckBox)
	{
		bUse = pCheckBox->GetCheck();
	}
	strCaption = ICncCommonOp::GetControlText(m_pm,_T("edtPollTime"));
	u16 wVal = _ttoi( strCaption.c_str() );
	if ( tPollInfo.wPollExpire != wVal ||  tPollInfo.bIsPoll != (BOOL)bUse  )
	{
		bChange = true;
	}
	return bChange;
}

bool CConfCallCfgLogic::IsAudioFormatChange()
{
	bool bChange = false; 
	EmTpAudioFormat emAudioFormat;
	emAudioFormat = ComInterface->GetAudioFormatInfo();

	COptionUI* pOpt = NULL;

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opMPEG4"));
	if (pOpt && pOpt->IsSelected())
	{
		m_emAudioFormat = emTPAMpegAACLD;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opG711A"));
	if (pOpt && pOpt->IsSelected())
	{
		m_emAudioFormat = emTPAG711a;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opG711U"));
	if (pOpt && pOpt->IsSelected())
	{
		m_emAudioFormat = emTPAG711u;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opG719"));
	if (pOpt && pOpt->IsSelected())
	{
		m_emAudioFormat = emTPAG719;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opMP3"));
	if (pOpt && pOpt->IsSelected())
	{
		m_emAudioFormat = emTPAMP3;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opMP4"));
	if (pOpt && pOpt->IsSelected())
	{
		m_emAudioFormat = emTPAMpegAACLC;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opG772"));
	if (pOpt && pOpt->IsSelected())
	{
		m_emAudioFormat = emTPAG7221;
	}

	if ( emAudioFormat != m_emAudioFormat )
	{
		bChange = true;
	}	
	return bChange;
}

bool CConfCallCfgLogic::OnCheckIsAESPassword( TNotifyUI& msg )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	if ( pCheckBox->IsSelected() )
	{
		ICncCommonOp::EnableControl(true,m_pm,_T("edtAESPassword"));
	}
	else
	{
		ICncCommonOp::EnableControl(false,m_pm,_T("edtAESPassword"));
	}
	return true; 
}

bool CConfCallCfgLogic::OnEncryptInfoInd( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
	BOOL bSuc = BOOL(wparam);
	if (!bSuc)
	{
		ShowPopMsg(_T("加密方式设置失败"));
	}

	return OnEncryptInfoNty(wparam,lparam,bHandle);
}

bool CConfCallCfgLogic::OnEncryptInfoNty( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
	//nlf确定 TTpEncryptKey中：开启emTPEncryptTypeAES 不开启的时候赋值emTPEncryptTypeNone
	TTpEncryptKey tEncryt;
	ComInterface->GetEncrytInfo( tEncryt );
	m_tEncryptInfo = tEncryt;

	EmTPEncryptType emType = tEncryt.emTPEncryptType;
	if (emType == emTPEncryptTypeAES)
	{
		ICncCommonOp::OptionSelect( true, m_pm, _T("opAESEncrypt") );
		ICncCommonOp::SetControlText(_T("AES加密"),m_pm,_T("lbEncryptType"));

		m_pm->DoCase(_T("caseAESEncrpt"));
	}
	else if ( emType == emTPEncryptTypeQt )
	{
		ICncCommonOp::OptionSelect( true, m_pm, _T("opQTEncrypt") );
		ICncCommonOp::SetControlText(_T("量子加密"),m_pm,_T("lbEncryptType"));	

		m_pm->DoCase(_T("caseQTEncrpt"));
		
		if (tEncryt.emQtKeyFrequency == emQtFrequencyEverySeconds)
		{
			ICncCommonOp::OptionSelect( true, m_pm, _T("opQTEverySecond") );
			ICncCommonOp::SetControlText(_T("一秒一密"),m_pm,_T("lbQTEncryptLevel"));
		}
		else if (tEncryt.emQtKeyFrequency == emQtFrequencyEveryMinutes)
		{
			ICncCommonOp::OptionSelect( true, m_pm, _T("opQTEveryMinute") );
			ICncCommonOp::SetControlText(_T("一分一密"),m_pm,_T("lbQTEncryptLevel"));
		}
		else if (tEncryt.emQtKeyFrequency == emQtFrequencyEveryConf)
		{
			ICncCommonOp::OptionSelect( true, m_pm, _T("opQTEveryConf") );
			ICncCommonOp::SetControlText(_T("一会一密"),m_pm,_T("lbQTEncryptLevel"));
		}

		m_pm->DoCase(_T("caseQTEncrpt"));
	}
	else if ( emType == emTPEncryptTypeNone )
	{
		ICncCommonOp::OptionSelect( true, m_pm, _T("opNoEncrypt") );
		ICncCommonOp::SetControlText(_T("不加密"),m_pm,_T("lbEncryptType"));	

		m_pm->DoCase(_T("caseNoEncrpt"));
	}
	

	/*bool bIsShow = false;
	if(tEncryt.emTPEncryptType == emTPEncryptTypeAES)
	{
		bIsShow = true;
	}

	CCheckBoxUI* pcheck = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckIsAESPassword"));
	if (!pcheck)
	{
		return false;
	}
	pcheck->Selected(bIsShow);
	ICncCommonOp::EnableControl(bIsShow,m_pm,_T("edtAESPassword"));	
	if (bIsShow)
	{
		ICncCommonOp::SetControlText(_T("开"),m_pm,_T("lbIsAESPassword"));	
		ICncCommonOp::SetControlText(_T("******"),m_pm,_T("lbAESPassword"));
		ICncCommonOp::SetControlText(_T("******"),m_pm,_T("edtAESPassword"));
	}
	else
	{
		ICncCommonOp::SetControlText(_T("关"),m_pm,_T("lbIsAESPassword"));	
		ICncCommonOp::SetControlText(_T(""),m_pm,_T("lbAESPassword"));
		ICncCommonOp::SetControlText(_T(""),m_pm,_T("edtAESPassword"));
	}*/

	return S_OK;
}

int CConfCallCfgLogic::GetRateFixed( int wNum, bool bIsBtnPlus /*= true*/ )
{
	int wFixedNum = wNum;
	if (bIsBtnPlus)// 加操作
	{
// 		if (wNum < 512)
// 		{
// 			wFixedNum = 512;
// 		}
		if (/*wNum>=512 &&*/ wNum<1024)
		{
			wFixedNum = 1024;
		}
		else if (wNum>=1024 && wNum<2048)
		{
			wFixedNum = 2048;
		}
		else if (wNum>=2048 && wNum<3072)
		{
			wFixedNum = 3072;
		}
		else if (wNum>=3072 && wNum<4096)
		{
			wFixedNum = 4096;
		}
		else if (wNum>=4096 && wNum<5120)
		{
			wFixedNum = 5120;
		}
		else if (wNum>=5120 && wNum<6144)
		{
			wFixedNum = 6144;
		}
		else if (wNum>=6144 && wNum<7168)
		{
			wFixedNum = 7168;
		}
		else if (wNum>=7168 )
		{
			wFixedNum = 8192;
		}
	}
	else
	{
		if (wNum <= 1024)
		{
			wFixedNum = 0/*512*/;
		}
		else if (wNum>1024 && wNum<=2048)
		{
			wFixedNum = 1024;
		}
		else if (wNum>2048 && wNum<=3072)
		{
			wFixedNum = 2048;
		}
		else if (wNum>3072 && wNum<=4096)
		{
			wFixedNum = 3072;
		}
		else if (wNum>4096 && wNum<=5120)
		{
			wFixedNum = 4096;
		}
		else if (wNum>5120 && wNum<=6144)
		{
			wFixedNum = 5120;
		}
		else if (wNum>6144 && wNum<=7168)
		{
			wFixedNum = 6144;
		}
		else if (wNum>7168 )
		{
			wFixedNum = 7168;
		}
	}

	return wFixedNum;
}

bool CConfCallCfgLogic::SaveRate()
{
	String strCaption = ICncCommonOp::GetControlText(m_pm,_T("edtSingleRate"));
	u16 wVal = _ttoi( strCaption.c_str() );

	strCaption = ICncCommonOp::GetControlText(m_pm,_T("edtDulRate"));
	u16 wDualVal = _ttoi( strCaption.c_str() );
	s8 chCallRate[8] = {0};

	if ( IsCallRateChange() )
	{
		if (wVal>8192)
		{
			wVal = 8192;
			ShowPopMsg((_T("单屏码率最大为8192")));
		}
		if (wVal<64)
		{
			wVal = 64;
			ShowPopMsg((_T("单屏码率最小为64")));
		}

		if (wVal%64 != 0)
		{
			wVal = 64*(wVal/64) + 64;
			ShowPopMsg((_T("单屏码率已经自动保存为64倍数")));
		}

		sprintf( chCallRate, "%u", wVal );
		ICncCommonOp::SetControlText(CA2T(chCallRate), m_pm,_T("edtSingleRate"));
	} 

	if ( IsDualCallRateChange() )
	{
		if (wDualVal>8192)
		{
			wDualVal = 8192;
			ShowPopMsg((_T("演示码率最大为8192")));
		}
		if (wDualVal<0)
		{
			wDualVal = 0;
			ShowPopMsg((_T("演示码率最小为0")));
		}

		if (wDualVal%64 != 0)
		{
			wDualVal = 64*(wDualVal/64) + 64;
			ShowPopMsg((_T("演示码率已经自动保存为64倍数")));
		}
		memset(chCallRate,0,sizeof( chCallRate));
		sprintf( chCallRate, "%u", wDualVal );
		ICncCommonOp::SetControlText(CA2T(chCallRate), m_pm,_T("edtDulRate"));
	} 
	
	if ( wVal + wDualVal > 8192 )
	{
		ShowMessageBox((_T("单屏码率+演示码率必须小于等于8192Kbps")));
		CEditUI *pEdit = (CEditUI*)ICncCommonOp::FindControl(m_pm,_T("edtSingleRate"));
		if (pEdit)
		{
			pEdit->SetFocusX();
		}

		return false;
	}
	if ( wVal + wDualVal < 64 )
	{
		ShowMessageBox((_T("单屏码率+演示码率必须大于等于64Kbps")));
		CEditUI *pEdit = (CEditUI*)ICncCommonOp::FindControl(m_pm,_T("edtSingleRate"));
		if (pEdit)
		{
			pEdit->SetFocusX();
		}

		return false;
	}

	if ( IsCallRateChange() )
	{
		u16 wRet = ComInterface->CallRateCmd(wVal);
		if (wRet != NO_ERROR)
		{
			ShowMessageBox((_T("保存单屏码率请求发送失败")));
			return false;
		}
	}

	if (IsDualCallRateChange())
	{
		u16 wRet = ComInterface->DualCallRateCmd(wDualVal);
		if (wRet != NO_ERROR)
		{
			ShowMessageBox((_T("保存演示码率请求发送失败")),false);
			return false;
		}
	}

	return true;
}

bool CConfCallCfgLogic::Onop1080( TNotifyUI& msg )
{
	ICncCommonOp::EnableControl(true,m_pm,_T("op60fps"));
	ICncCommonOp::EnableControl(true,m_pm,_T("op50fps"));
	ICncCommonOp::EnableControl(true,m_pm,_T("op30fps"));

	return true;
}

bool CConfCallCfgLogic::Onop720( TNotifyUI& msg )
{
	ICncCommonOp::EnableControl(true,m_pm,_T("op60fps"));
	ICncCommonOp::EnableControl(true,m_pm,_T("op50fps"));
	ICncCommonOp::EnableControl(true,m_pm,_T("op30fps"));

	return true;
}

bool CConfCallCfgLogic::Onop4CIF( TNotifyUI& msg )
{
	ICncCommonOp::EnableControl(false,m_pm,_T("op60fps"));
	ICncCommonOp::EnableControl(false,m_pm,_T("op50fps"));
	ICncCommonOp::EnableControl(false,m_pm,_T("op30fps"));

	COptionUI* pOp = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("op25fps"));
	if (pOp)
	{
		pOp->Selected(true);
	}
	return true;
}

bool CConfCallCfgLogic::Onop60fps( TNotifyUI& msg )
{
	return true;
}

bool CConfCallCfgLogic::Onop50fps( TNotifyUI& msg )
{
	return true;
}

bool CConfCallCfgLogic::Onop30fps( TNotifyUI& msg )
{
	return true;
}

bool CConfCallCfgLogic::Onop25fps( TNotifyUI& msg )
{
	return true;
}

bool CConfCallCfgLogic::OnopN1080( TNotifyUI& msg )
{     
	EnableOp();
	return true;
}
bool CConfCallCfgLogic::OnopN720( TNotifyUI& msg )
{
	EnableOp();
	return true;
}
bool CConfCallCfgLogic::OnopN4CIF( TNotifyUI& msg )
{
	ICncCommonOp::EnableControl(false,m_pm,_T("opN60fps"));
	ICncCommonOp::EnableControl(false,m_pm,_T("opN50fps"));
	ICncCommonOp::EnableControl(false,m_pm,_T("opN30fps"));
	ICncCommonOp::EnableControl(true,m_pm,_T("opN25fps"));
	ICncCommonOp::EnableControl(false,m_pm,_T("opN5fps"));

	COptionUI* pOp = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opN25fps"));
	if (pOp)
	{
		pOp->Selected(true);
	}
	return true;
}
bool CConfCallCfgLogic::OnopUXGA( TNotifyUI& msg )
{
	ICncCommonOp::EnableControl(true,m_pm,_T("opN60fps"));
	ICncCommonOp::EnableControl(false,m_pm,_T("opN50fps"));
	ICncCommonOp::EnableControl(false,m_pm,_T("opN30fps"));
	ICncCommonOp::EnableControl(false,m_pm,_T("opN25fps"));
	ICncCommonOp::EnableControl(false,m_pm,_T("opN5fps"));

	COptionUI* pOp = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opN60fps"));
	if (pOp)
	{
		pOp->Selected(true);
	}

	return true;
}
bool CConfCallCfgLogic::OnopWXGA( TNotifyUI& msg )
{
	ICncCommonOp::EnableControl(false,m_pm,_T("opN60fps"));
	ICncCommonOp::EnableControl(false,m_pm,_T("opN50fps"));
	ICncCommonOp::EnableControl(true,m_pm,_T("opN30fps"));
	ICncCommonOp::EnableControl(false,m_pm,_T("opN25fps"));
	ICncCommonOp::EnableControl(true,m_pm,_T("opN5fps"));

	COptionUI* pOp = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opN30fps"));
	if (pOp)
	{
		pOp->Selected(true);
	}
	return true;
}
bool CConfCallCfgLogic::OnopSXGA( TNotifyUI& msg )
{
	ICncCommonOp::EnableControl(false,m_pm,_T("opN60fps"));
	ICncCommonOp::EnableControl(false,m_pm,_T("opN50fps"));
	ICncCommonOp::EnableControl(true,m_pm,_T("opN30fps"));
	ICncCommonOp::EnableControl(false,m_pm,_T("opN25fps"));
	ICncCommonOp::EnableControl(true,m_pm,_T("opN5fps"));

	COptionUI* pOp = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opN30fps"));
	if (pOp)
	{
		pOp->Selected(true);
	}
	return true;
}
bool CConfCallCfgLogic::OnopXGA( TNotifyUI& msg )
{
	ICncCommonOp::EnableControl(false,m_pm,_T("opN60fps"));
	ICncCommonOp::EnableControl(false,m_pm,_T("opN50fps"));
	ICncCommonOp::EnableControl(false,m_pm,_T("opN30fps"));
	ICncCommonOp::EnableControl(false,m_pm,_T("opN25fps"));
	ICncCommonOp::EnableControl(true,m_pm,_T("opN5fps"));

	COptionUI* pOp = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opN5fps"));
	if (pOp)
	{
		pOp->Selected(true);
	}
	return true;
}
bool CConfCallCfgLogic::OnopN60fps( TNotifyUI& msg )
{
	return true;
}
bool CConfCallCfgLogic::OnopN50fps( TNotifyUI& msg )
{
	return true;
}
bool CConfCallCfgLogic::OnopN30fps( TNotifyUI& msg )
{
	return true;
}
bool CConfCallCfgLogic::OnopN25fps( TNotifyUI& msg )
{
	return true;
}
bool CConfCallCfgLogic::OnopN5fps( TNotifyUI& msg )
{
	return true;
}
bool CConfCallCfgLogic::OnopMPEG4( TNotifyUI& msg )
{
	return true;
}
bool CConfCallCfgLogic::OnopG711A( TNotifyUI& msg )
{
	return true;
}
bool CConfCallCfgLogic::OnopG711U( TNotifyUI& msg )
{
	return true;
}
bool CConfCallCfgLogic::OnopG719( TNotifyUI& msg )
{
	return true;
}
bool CConfCallCfgLogic::OnopMP3( TNotifyUI& msg )
{
	return true;
}
bool CConfCallCfgLogic::OnopMP4( TNotifyUI& msg )
{
	return true;
}
bool CConfCallCfgLogic::OnopG772( TNotifyUI& msg )
{
	return true;
}

void CConfCallCfgLogic::EnableOp()
{
	ICncCommonOp::EnableControl(true,m_pm,_T("opN60fps"));
	ICncCommonOp::EnableControl(true,m_pm,_T("opN50fps"));
	ICncCommonOp::EnableControl(true,m_pm,_T("opN30fps"));
	ICncCommonOp::EnableControl(true,m_pm,_T("opN25fps"));
	ICncCommonOp::EnableControl(true,m_pm,_T("opN5fps"));
}

bool CConfCallCfgLogic::OnopAESEncrypt( TNotifyUI& msg )
{
	m_pm->DoCase(_T("caseAESEncrpt"));
	return true;
}

bool CConfCallCfgLogic::OnopQTEncrypt( TNotifyUI& msg )
{
	//编辑状态有效
	if (m_bIsFix)
	{
		m_pm->DoCase(_T("caseQTEncrpt"));
	}
	
	return true;
}

bool CConfCallCfgLogic::OnopNoEncrypt( TNotifyUI& msg )
{
	m_pm->DoCase(_T("caseNoEncrpt"));
	return true;
}

bool CConfCallCfgLogic::IsConfEncryptChange()
{
	bool bChange = false;
	TTpEncryptKey tEncrytOri;
	ComInterface->GetEncrytInfo( tEncrytOri );

	COptionUI* pOpt = NULL;

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opAESEncrypt"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tEncryptInfo.emTPEncryptType = emTPEncryptTypeAES;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opQTEncrypt"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tEncryptInfo.emTPEncryptType = emTPEncryptTypeQt;
	}

	pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opNoEncrypt"));
	if (pOpt && pOpt->IsSelected())
	{
		m_tEncryptInfo.emTPEncryptType = emTPEncryptTypeNone;
	}

	if (m_tEncryptInfo.emTPEncryptType != tEncrytOri.emTPEncryptType)
	{
		bChange = true;	
		if (m_tEncryptInfo.emTPEncryptType == emTPEncryptTypeQt)
		{
			pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opQTEverySecond"));
			if (pOpt && pOpt->IsSelected())
			{
				m_tEncryptInfo.emQtKeyFrequency = emQtFrequencyEverySeconds;
			}

			pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opQTEveryMinute"));
			if (pOpt && pOpt->IsSelected())
			{
				m_tEncryptInfo.emQtKeyFrequency = emQtFrequencyEveryMinutes;
			}

			pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opQTEveryConf"));
			if (pOpt && pOpt->IsSelected())
			{
				m_tEncryptInfo.emQtKeyFrequency = emQtFrequencyEveryConf;
			}
		}
		else if (m_tEncryptInfo.emTPEncryptType == emTPEncryptTypeAES)
		{
			String strAESPass = ICncCommonOp::GetControlText(m_pm,_T("edtAESPassword"));
			m_tEncryptInfo.byLen = strAESPass.length();
			memset(m_tEncryptInfo.byKey, 0, sizeof(m_tEncryptInfo.byKey));
			memcpy(m_tEncryptInfo.byKey,CT2A(strAESPass.c_str()),strAESPass.length());
			m_tEncryptInfo.byKey[TP_MAXLEN_ENCRYPTKEY-1]='\0';			
		}
	}
	else //相等且是量子加密
	{
		if (m_tEncryptInfo.emTPEncryptType == emTPEncryptTypeQt)
		{
			pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opQTEverySecond"));
			if (pOpt && pOpt->IsSelected())
			{
				m_tEncryptInfo.emQtKeyFrequency = emQtFrequencyEverySeconds;
			}

			pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opQTEveryMinute"));
			if (pOpt && pOpt->IsSelected())
			{
				m_tEncryptInfo.emQtKeyFrequency = emQtFrequencyEveryMinutes;
			}

			pOpt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("opQTEveryConf"));
			if (pOpt && pOpt->IsSelected())
			{
				m_tEncryptInfo.emQtKeyFrequency = emQtFrequencyEveryConf;
			}

			if (m_tEncryptInfo.emQtKeyFrequency != tEncrytOri.emQtKeyFrequency)
			{
				bChange = true;	
			}
		}
		else if (m_tEncryptInfo.emTPEncryptType == emTPEncryptTypeAES)
		{
			String strAESPass = ICncCommonOp::GetControlText(m_pm,_T("edtAESPassword"));
			m_tEncryptInfo.byLen = strAESPass.length();
			memset(m_tEncryptInfo.byKey, 0, sizeof(m_tEncryptInfo.byKey));
			memcpy(m_tEncryptInfo.byKey,CT2A(strAESPass.c_str()),strAESPass.length());
			m_tEncryptInfo.byKey[TP_MAXLEN_ENCRYPTKEY-1]='\0';	
			if ( (m_tEncryptInfo.byLen != tEncrytOri.byLen) || memcmp(m_tEncryptInfo.byKey, tEncrytOri.byKey, m_tEncryptInfo.byLen))
			{
				bChange = true;
			}
		}
	}

	return bChange;
}

bool CConfCallCfgLogic::SaveConfEncryptInfo()
{
	bool bChange = false;
	bChange = IsConfEncryptChange();
	if ( bChange )
	{
// 		if (m_tEncryptInfo.emTPEncryptType == emTPEncryptTypeAES && m_tEncryptInfo.byLen == 0)
// 		{
// 			ShowMessageBox(_T("AES密码不能为空"),false);
// 			CEditUI* pEditUI= (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("edtAESPassword") );
// 			if (pEditUI)
// 			{
// 				pEditUI->SetFocus();
// 			}
// 			return false;
// 		}
		u16 wRet = ComInterface->EncrytCmd(m_tEncryptInfo);
		if (wRet != NO_ERROR)
		{
			ShowMessageBox((_T("保存密码设置失败")),false);
			return false;
		}
	}

	return true;
}

bool CConfCallCfgLogic::OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    ComInterface->ShowKeyboard();
    return true;
}