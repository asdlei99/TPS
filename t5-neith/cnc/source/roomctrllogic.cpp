#include "StdAfx.h"
#include "roomctrllogic.h"
#include "confmsglogic.h"
#include "messageboxlogic.h"

APP_BEGIN_MSG_MAP(CRoomCtrlLogic,CNotifyUIImpl)
	MSG_CREATEWINDOW(_T("RoomCtrlLayout"), OnCreate)
	MSG_INIWINDOW(_T("RoomCtrlLayout"), OnInit)

	MSG_CLICK(_T("BtnBack"), OnBtnBack)
	MSG_CLICK(_T("BtnExit"), OnBtnExit)

	MSG_CLICK(_T("btnSet"), OnBtnVedioItemSel)
	MSG_CLICK(_T("micControlBtn"), OnBtnMicControl)
 	MSG_ITEMSELECTD(_T("VedioSourceList"), OnVedioItemSel)

	MSG_ITEMSELECTD(_T("ComboCamSel"), OnComboItemSel) 

	MSG_SELECTCHANGE(_T("CheckMicShortCut"), OnCheckMicShortCut)
	MSG_SELECTCHANGE(_T("CheckSpeakerShortCut"), OnCheckSpeakerShortCut)
	MSG_SELECTCHANGE(_T("CheckMute"), OnCheckMute)
	MSG_SELECTCHANGE(_T("CheckSlient"), OnCheckSlient)

	MSG_SELECTCHANGE(_T("camera"), OnTabCamera)
	MSG_SELECTCHANGE(_T("speaker"), OnTabSpeaker)
	MSG_SELECTCHANGE(_T("mic"), OnTabMic)
//	MSG_SELECTCHANGE(_T("vediosource"), OnTabVedioSource)
	MSG_SELECTCHANGE(_T("mainvedio"), OnTabMainVedio) 

	//摄像机相关
	MSG_SELECTCHANGE(_T("OptionFullCam"), OnTabFullCamera)
	MSG_SELECTCHANGE(_T("OptionFileCam"), OnTabFileCamera)
	
	MSG_SELECTCHANGE(_T("Vedio1Op1"), OnTabVedio1Op1)
	MSG_SELECTCHANGE(_T("Vedio1Op2"), OnTabVedio1Op2)
	MSG_SELECTCHANGE(_T("Vedio2Op1"), OnTabVedio2Op1)
	MSG_SELECTCHANGE(_T("Vedio2Op2"), OnTabVedio2Op2)
	MSG_SELECTCHANGE(_T("Vedio2Op3"), OnTabVedio2Op3)
	MSG_SELECTCHANGE(_T("Vedio3Op1"), OnTabVedio3Op1)
	MSG_SELECTCHANGE(_T("Vedio3Op2"), OnTabVedio3Op2)

    //升降屏相关
    MSG_SELECTCHANGE(_T("OptIsControl1"), OnCheckSrceenControl)
    MSG_SELECTCHANGE(_T("OptIsControl2"), OnCheckSrceenControl)
    MSG_SELECTCHANGE(_T("OptIsControl3"), OnCheckSrceenControl)
    MSG_SELECTCHANGE(_T("OptIsControl4"), OnCheckSrceenControl)
    MSG_SELECTCHANGE(_T("OptIsControl5"), OnCheckSrceenControl)
    MSG_SELECTCHANGE(_T("OptIsControlAll"), OnCheckSrceenControl)
    MSG_CLICK(_T("BtnLiftSrceenUp"), OnBtnLiftSrceenUp)
    MSG_CLICK(_T("BtnLiftSrceenDown"), OnBtnLiftSrceenDown)
    MSG_CLICK(_T("BtnLiftSrceenStop"), OnBtnLiftSrceenStop)
    MSG_CLICK(_T("BtnFlipSrceenOpen"), OnBtnFlipSrceenOpen)
    MSG_CLICK(_T("BtnFlipSrceenClose"), OnBtnFlipSrceenClose)
    MSG_CLICK(_T("BtnFlipSrceenStop"), OnBtnFlipSrceenStop)

	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)

	USER_MSG(UI_CNS_INVOL_UPDATE,OnMicVolNty)
	USER_MSG(UI_CNS_OUTVOL_UPDATE,OnSpeakerVolNty)
	USER_MSG(UI_CNS_QUITE_MUTE,OnMuteOrSilencNty)
	USER_MSG(UI_CNS_VGAINFO_NOTIFY,OnVgaInfoNotify)
	USER_MSG(UI_CNS_CONFVGAINFO_NOTIFY,OnVgaInfoNotify)
	USER_MSG(UI_CNS_SELDUALPORT_IND,OnSelDualPortInd)    
	USER_MSG(UI_CNS_SELDEFAULTDUALPORT_IND,OnSelDefaultDualPortInd)   
	USER_MSG(UI_CNC_SHOW_SHORTCUTDLG_NTY,OnSetTabShow)
	USER_MSG(UI_CNC_SHORTCUTCHECK_NTY,OnSetShortCheck)

	USER_MSG(UI_CNS_SETMAINVEDIO_IND,OnMainVedioSetInd)
	//视频源状态通知 dyy 2015-6-17
	USER_MSG(UI_CNS_VIDSRC_NTY,OnVidSrcNty)
	//辅视频是否被选后cnc要禁用部分选项
	USER_MSG(UI_CNS_MINVEDIOINFO_NTY,OnMinVedioInfoNty)
	//主视频设置
	USER_MSG(UI_CNS_SETVEDIOINFO_NTY,OnSetVedioInfoNty)
	//麦克风相关
	USER_MSG(UI_CNC_CNDESKTOPMICINFO_NTY,OnCnDesktopMicInfoNty)
	USER_MSG(UI_CNC_CNMICPOWERSTYLE_NTY,OnCnMicPowerStyleNty)
	USER_MSG(UI_CNC_CNMICPOWER_NTY,OnCnMicPowerNty)
	USER_MSG(UI_CNC_CNSETMICPOWER_RSP,OnCnSetMicPowerRsp)
    //升降屏相关
    USER_MSG(UI_CNC_CENTREDFSCREENCONFIG_NTY,OnCentreDFScreenConfigNty)
    USER_MSG(UI_CNC_CENTRESELECTDFSCREEN_NTY,OnCentreSelectDFScreenNty)
    USER_MSG(UI_CNC_CENTREMODIFYDFSCREENGROUP_IND, OnCentreDFScreenConfigNty)
    USER_MSG(UI_CNC_CENTREDFSCREENCMD_IND,OnCentreDFScreenCmdInd)
    USER_MSG(UI_CNC_SELECTDFSCREEN_IND, OnSelectDFScreenInd)

	MSG_VALUECHANGED(_T("sldSpeaker"),onSpeakerVolChanged)
	MSG_VALUECHANGING(_T("sldSpeaker"),onSpeakerVolChanging)
	MSG_VALUECHANGED(_T("sldMic"),onMicVolChanged)
	MSG_VALUECHANGING(_T("sldMic"),onMicVolChanging)

APP_END_MSG_MAP()

const String CRoomCtrlLogic::m_strBtnFixOrCancel = _T("BtnFixOrCancel");
const String CRoomCtrlLogic::m_strBtnOk = _T("BtnOk");
const String CRoomCtrlLogic::m_strSldTab = _T("slidetab");
const String CRoomCtrlLogic::m_strFullCamera = _T("OptionFullCam");
const String CRoomCtrlLogic::m_strSldSpeaker = _T("sldSpeaker");
const String CRoomCtrlLogic::m_strSldMic = _T("sldMic"); 
const String CRoomCtrlLogic::m_strBtnMute = _T("BtnMute");
const String CRoomCtrlLogic::m_strBtnSlience = _T("BtnSlient");

const int CRoomCtrlLogic::m_nFirstLineMic[NUM_MIC_FIRLINE] = {6,3,0};
const int CRoomCtrlLogic::m_nSecondLineMic[NUM_MIC_SECLINE] = {7,8,4,5,1,2};


CRoomCtrlLogic::CRoomCtrlLogic(void)
{
	m_bIsVSListExt = false;
	m_bSetVedioSourc = false;
	m_bIsIni = false;
	m_em = emShortcutPanCam;
	m_bIsNonDesktopMic = FALSE;
	m_bIsFullState = FALSE;

	memset(m_byMicStyle, 0, TP_MIC_NUM*sizeof(BOOL));
	memset(m_byMicState, 0, TP_MIC_NUM*sizeof(BOOL));

    m_dwGroupNum = 0;
    m_byScreenControl = 0;
    m_byAllScreenCtrlSel = 0;
}


CRoomCtrlLogic::~CRoomCtrlLogic(void)
{
}

bool CRoomCtrlLogic::OnCreate( TNotifyUI& msg )
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

bool CRoomCtrlLogic::OnInit( TNotifyUI& msg )
{
	ICncCommonOp::ShowControl( false, m_pm, _T("PageNameSet") );
	ICncCommonOp::ShowControl( false, m_pm, _T("PagePresetList") );
	m_bIsIni = true;
	if (m_em != emShortcutPanCam)
	{
		if ( m_em == emShortcutMute )
		{
			ICncCommonOp::OptionSelect(true,m_pm,_T("mic"));
		}
		else if ( m_em == emShortcutSilence )
		{
			ICncCommonOp::OptionSelect(true,m_pm,_T("speaker"));
		}
	}

	UpdateSourceName();
    NOTIFY_MSG(UI_CNC_CENTREDFSCREENCONFIG_NTY, 0,0);
	return true;
}


bool CRoomCtrlLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_tDualSrcInfo.Clear();
	m_bSetVedioSourc = false;
	m_bIsVSListExt = false;
	m_bIsFullState = FALSE;

	memset(m_byMicStyle, 0, TP_MIC_NUM*sizeof(BOOL));
	memset(m_byMicState, 0, TP_MIC_NUM*sizeof(BOOL));

    m_byScreenControl = 0;
    m_byAllScreenCtrlSel = 0;

	CCheckBoxUI* pCheck = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckSlient")); 
	if (pCheck)
	{
		pCheck->SetCheckNoMsg(false);
	}

	pCheck = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckMute")); 
	if (pCheck)
	{
		pCheck->SetCheckNoMsg(false);
	}

	return true;
}

bool CRoomCtrlLogic::OnBtnBack( TNotifyUI& msg )
{
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight(g_strRoomControlDlg.c_str(),false );
	return true;
}

bool CRoomCtrlLogic::OnBtnExit( TNotifyUI& msg )
{
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight(g_strRoomControlDlg.c_str(),false );
	return true;
}


bool CRoomCtrlLogic::OnTabCamera( TNotifyUI& msg )
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, m_strSldTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(ID_CAMERA);
	}
	return true;
}

bool CRoomCtrlLogic::OnTabSpeaker( TNotifyUI& msg )
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, m_strSldTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(ID_SPEAKER);
	}
	return true;
}

bool CRoomCtrlLogic::OnTabMic( TNotifyUI& msg )
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, m_strSldTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(ID_MIC);
	}

	return true;
}

/*bool CRoomCtrlLogic::OnTabVedioSource( TNotifyUI& msg )
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, m_strSldTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(ID_VEDIOSOURCE);
	}

	CListUI *pTileLayoutUI = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("VedioSourceList") );
	if ( pTileLayoutUI != NULL )
	{
		pTileLayoutUI->SelectItem((int)m_tDualSrcInfo.emCurrentType);
	}

	return true;
}*/

bool CRoomCtrlLogic::OnTabMainVedio( TNotifyUI& msg )
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, m_strSldTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(ID_MAINVEDIO);
	}
	return true;
}


bool CRoomCtrlLogic::OnCheckSlient( TNotifyUI& msg )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	bool bIsSet = false;
	if ( pCheckBox->GetCheck() )
	{
		bIsSet = true;
	}

	ComInterface->SetLocalCnsQuite(bIsSet);

	return true;
}

bool CRoomCtrlLogic::OnCheckSpeakerShortCut( TNotifyUI& msg )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	bool bIsSet = false;
	if ( pCheckBox->GetCheck() )
	{
		bIsSet = true;
	}

	EM_ShortcutType em = emShortcutSilence;
	NOTIFY_MSG( UI_CNC_SET_SHORTCUT_NTY, em, bIsSet );
	return true;
}

bool CRoomCtrlLogic::OnCheckMute( TNotifyUI& msg )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	bool bIsSet = false;
	if ( pCheckBox->GetCheck() )
	{
		bIsSet = true;
	}

	ComInterface->SetLocalCnsMute(bIsSet);

	return true;
}

bool CRoomCtrlLogic::OnCheckMicShortCut( TNotifyUI& msg )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	bool bIsSet = false;
	if ( pCheckBox->GetCheck() )
	{
		bIsSet = true;
	}

	EM_ShortcutType em = emShortcutMute;
	NOTIFY_MSG( UI_CNC_SET_SHORTCUT_NTY, em, bIsSet );
	return true;
}

bool CRoomCtrlLogic::OnTabVedio1Op1( TNotifyUI& msg )
{
	if (m_mapEmTPMtVideoPort[0] == emTPC1Vid)
	{
		return true;
	}
	m_pm->DoCase(_T("caseNull1"));
	ComInterface->SetMainVideoPort( emTPC1Vid, 0 );
	return true;
}

bool CRoomCtrlLogic::OnTabVedio1Op2( TNotifyUI& msg )
{
	if (m_mapEmTPMtVideoPort[0] == emTPC2Vid)
	{
		return true;
	}

	m_pm->DoCase(_T("caseNull1"));
	ComInterface->SetMainVideoPort( emTPC2Vid, 0 );
	return true;
}

bool CRoomCtrlLogic::OnTabVedio2Op1( TNotifyUI& msg )
{
	if (m_mapEmTPMtVideoPort[1] == emTPC3Vid)
	{
		return true;
	}

	m_pm->DoCase(_T("caseNull2"));
	ComInterface->SetMainVideoPort( emTPC3Vid, 1 );
	
	return true;
}

bool CRoomCtrlLogic::OnTabVedio2Op2( TNotifyUI& msg )
{
	if (m_mapEmTPMtVideoPort[1] == emTPC4Vid)
	{
		return true;
	}

	m_pm->DoCase(_T("caseNull2"));
	ComInterface->SetMainVideoPort( emTPC4Vid, 1 );
	
	return true;
}

bool CRoomCtrlLogic::OnTabVedio2Op3( TNotifyUI& msg )
{
	if (m_mapEmTPMtVideoPort[1] == emTPC7Vid)
	{
		return true;
	}

	m_pm->DoCase(_T("caseNull2"));
	ComInterface->SetMainVideoPort( emTPC7Vid, 1 );
	
	return true;
}

bool CRoomCtrlLogic::OnTabVedio3Op1( TNotifyUI& msg )
{
	if (m_mapEmTPMtVideoPort[2] == emTPC5Vid)
	{
		return true;
	}

	m_pm->DoCase(_T("caseNull3"));
	ComInterface->SetMainVideoPort( emTPC5Vid, 2 );
	
	return true;
}

bool CRoomCtrlLogic::OnTabVedio3Op2( TNotifyUI& msg )
{
	if (m_mapEmTPMtVideoPort[2] == emTPC6Vid)
	{
		return true;
	}

	m_pm->DoCase(_T("caseNull3"));
	ComInterface->SetMainVideoPort( emTPC6Vid, 2 );
	
	return true;
}

bool CRoomCtrlLogic::OnCheckSrceenControl(TNotifyUI& msg)
{
    CCheckBoxUI *pCheckBox = (CCheckBoxUI*)msg.pSender;
    if (pCheckBox == NULL)
    {
        return false;
    }

    CDuiString strCaseTemp = _T("");
    int nCheckBoxTag = pCheckBox->GetnTag();

    if ( nCheckBoxTag == 0 )//点击全选
    {
        if (pCheckBox->GetCheck())//选中 全部勾选
        {
            m_byScreenControl = m_byAllScreenCtrlSel;
            m_pm->DoCase(_T("caseCheckSelectAll"));
        }
        else//取消选中 全部不勾选
        {
            m_byScreenControl = 0;
            m_pm->DoCase(_T("caseCheckSelectNone"));
        }
    }
    else if ( nCheckBoxTag > 0 && nCheckBoxTag <= NUM_SRCEEN_COUNT )//点击位置
    {
        if (pCheckBox->GetCheck())
        {
            m_byScreenControl |= adwTagArray[nCheckBoxTag -1];
            strCaseTemp.Format(_T("caseCheckSelect%d"), nCheckBoxTag);
            m_pm->DoCase(strCaseTemp);
        }
        else
        {
            m_byScreenControl &= ~adwTagArray[nCheckBoxTag -1];
            strCaseTemp.Format(_T("caseCheckNotSelect%d"), nCheckBoxTag);
            m_pm->DoCase(strCaseTemp);
        }

        //全选按钮状态
        CCheckBoxUI* pCheckBoxAll = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("OptIsControlAll"));
        if (pCheckBoxAll == NULL)
        {
            return false;
        }

        if (m_byScreenControl == m_byAllScreenCtrlSel)
        {
            pCheckBoxAll->SetCheckNoMsg(true);
        }
        else
        {
            pCheckBoxAll->SetCheckNoMsg(false);
        }
    }

    ComInterface->SelectCentreDFScreen( m_byScreenControl );
    return true;
}

bool CRoomCtrlLogic::OnBtnLiftSrceenUp(TNotifyUI& msg)
{
    ComInterface->SetCentreDFScreenCmd( emScreenUP );
    return true;
}

bool CRoomCtrlLogic::OnBtnLiftSrceenDown(TNotifyUI& msg)
{
    ComInterface->SetCentreDFScreenCmd( emScrrenDown );
    return true;
}

bool CRoomCtrlLogic::OnBtnLiftSrceenStop(TNotifyUI& msg)
{
    ComInterface->SetCentreDFScreenCmd( emScrrenStop );
    return true;
}

bool CRoomCtrlLogic::OnBtnFlipSrceenOpen(TNotifyUI& msg)
{
    ComInterface->SetCentreDFScreenCmd( emScreenUP );
    return true;
}

bool CRoomCtrlLogic::OnBtnFlipSrceenClose(TNotifyUI& msg)
{
    ComInterface->SetCentreDFScreenCmd( emScrrenDown );
    return true;
}

bool CRoomCtrlLogic::OnBtnFlipSrceenStop(TNotifyUI& msg)
{
    ComInterface->SetCentreDFScreenCmd( emScrrenStop );
    return true;
}


bool CRoomCtrlLogic::OnTabFullCamera( TNotifyUI& msg )
{
	m_pm->DoCase(_T("caseFullCameraSel"));
    //全景摄像机Option隐藏
    ICncCommonOp::ShowControl(false, m_pm, _T("OptionFullCam"));

    //文档摄像机信息
    map<u8, TCentreDCamCfg> mapDCamCfg;
    ComInterface->GetDCamStateMap(mapDCamCfg);
    //判断文档摄像机是否全部可用
    BOOL bIsDCamUsed = FALSE;
    map<u8, TCentreDCamCfg>::iterator itor = mapDCamCfg.begin();
    for ( ; itor != mapDCamCfg.end() ; itor++ )
    {
        if ( itor->second.bDCamUsed )
        {
            bIsDCamUsed = TRUE;
            break;
        }
    }
    //文档摄像机Option显示
    if (bIsDCamUsed)
    {
        ICncCommonOp::ShowControl(true, m_pm, _T("OptionFileCam"));
    }
	return true;
}

bool CRoomCtrlLogic::OnTabFileCamera( TNotifyUI& msg )
{
    m_pm->DoCase(_T("caseFileCameraSel"));
    TPanCamInfo tPanCamInfo;
    ComInterface->GetPanCamList( tPanCamInfo );
    //全景摄像机Option显示
    if ( tPanCamInfo.byPanCamNum != 0)
    {
        ICncCommonOp::ShowControl(true, m_pm, _T("OptionFullCam"));
    }
    //文档摄像机Option隐藏
    ICncCommonOp::ShowControl(false, m_pm, _T("OptionFileCam"));
    return true;
}

bool CRoomCtrlLogic::onSpeakerVolChanged(TNotifyUI& msg )
{
	int dwVol = 0;
	if (msg.sType == _T("valuechanged"))
	{
		dwVol = (static_cast<CSliderUI*>(msg.pSender))->GetValue();
	}

	CString strVol=_T("");
	strVol.Format(_T("%d%%"),dwVol);
	ICncCommonOp::SetControlText(strVol,m_pm,_T("lbspeakervol"));

	u8 byVolume = dwVol*31/100;
	u16 wRe = NO_ERROR;
	if ( ComInterface->GetOutputVol() == dwVol)
	{
		return wRe;
	}

	BOOL bQuite = ComInterface->IsLocalCnsQuite();
	if ( bQuite )
	{
		ComInterface->SetLocalCnsQuite( FALSE );
	}

	wRe =  ComInterface->AdjustOutputVol( byVolume );
	return wRe;
}

bool CRoomCtrlLogic::onMicVolChanged( TNotifyUI& msg )
{
	int dwVol = 0;
	if (msg.sType == _T("valuechanged"))
	{
		dwVol = (static_cast<CSliderUI*>(msg.pSender))->GetValue();
	}
	
	CString strVol=_T("");
	strVol.Format(_T("%d%%"),dwVol);
	ICncCommonOp::SetControlText(strVol,m_pm,_T("lbmicvol"));

	u8 byVolume = dwVol*31/100;
	u16 wRe = NO_ERROR;
	if ( ComInterface->GetInputVol() == dwVol)
	{
		return wRe;
	}

	BOOL bMute = ComInterface->IsLocalCnsMute();
	if ( bMute )
	{
		ComInterface->SetLocalCnsMute( FALSE );
	} 

	wRe =  ComInterface->AdjustInputVol(byVolume );
	return wRe;
}

bool CRoomCtrlLogic::OnSpeakerVolNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	u8 byVolume = ComInterface->GetOutputVol();
	u8 vol = byVolume*100/31;
	CSliderUI* pSilder = (CSliderUI*)ICncCommonOp::FindControl( m_pm, m_strSldSpeaker.c_str() );
	if (pSilder)
	{
		pSilder->SetValue(vol);
	}
	CString strVol=_T("");
	strVol.Format(_T("%d%%"),vol);
	ICncCommonOp::SetControlText(strVol,m_pm,_T("lbspeakervol"));
	return true;
}

bool CRoomCtrlLogic::OnMicVolNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	u8 byVolume = ComInterface->GetInputVol();
	u8 vol = byVolume*100/31;
	CSliderUI* pSilder = (CSliderUI*)ICncCommonOp::FindControl( m_pm, m_strSldMic.c_str() );
	if (pSilder)
	{
		pSilder->SetValue(vol);
	}
	CString strVol=_T("");
	strVol.Format(_T("%d%%"),vol);
	ICncCommonOp::SetControlText(strVol,m_pm,_T("lbmicvol"));
	return true;
}

/* 静音哑音通知  
	wparam = bQuite 	是静音还是哑音.TRUE 静音， FALSE 哑音
	lparam = bOn		是开启还是关闭.开启静音使当前没有音频输出,反之是关闭静音
*/
bool CRoomCtrlLogic::OnMuteOrSilencNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL32 bQuiet = (BOOL32)wParam;
	BOOL32 bSucess = (BOOL32)lParam;

	CCheckBoxUI* pCheck = NULL;

	if (bQuiet)
	{
		CCheckBoxUI* pCheck = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckSlient")); 
		if (pCheck)
		{
			if (pCheck->GetCheck() != bSucess)
			{
				pCheck->SetCheckNoMsg(bSucess);
			}
		}
	}
	else
	{
		CCheckBoxUI* pCheck = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckMute")); 
		if (pCheck)
		{
			if (pCheck->GetCheck() != bSucess)
			{
				pCheck->SetCheckNoMsg(bSucess);
			}
		}
	}

	return true;
}

bool CRoomCtrlLogic::OnVgaInfoNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	UpdateVedioSourceList();
	return NO_ERROR;
}


bool CRoomCtrlLogic::OnSelDefaultDualPortInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bOk = (BOOL)wParam;
	if (!bOk)
	{
		ShowPopMsg(_T("切换演示源失败"));
		//默认设置没有nty通知 nlf确定 界面自己更新 dyy 2015-6-9
		UpdateVedioSourceList();
	}
	else
	{
		ComInterface->GetDualSrcInfo( m_tDualSrcInfo );
	}

	return true;
}

bool CRoomCtrlLogic::OnSelDualPortInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	ICncCommonOp::EnableControl(true,m_pm,_T("VedioSourceList"));
	if (m_bSetVedioSourc)
	{
		m_bSetVedioSourc = false;
	}

	EmVgaType emType = (EmVgaType)wParam;
	EmVgaSwitchResult emResult = (EmVgaSwitchResult)lParam;
	if (emResult == em_VgaSwitchSucc)
	{
		ComInterface->GetDualSrcInfo( m_tDualSrcInfo );
		return NO_ERROR;
	}

	CString strError = _T( "切换演示源失败" );
	if ( emResult == em_CurVgaNoSignal )
	{
		strError = _T( "当前演示源无输入" );
	}
	else if ( emResult == em_TpNoDual )
	{
		strError = _T( "当前演示源无双流终端" );
	}
	else if ( emResult == em_VgaBusying )
	{
		strError = _T( "切换演示源失败：服务器忙，稍候再试" );
	}
	else if ( emResult == em_VgaSwitchInvalid )
	{
		strError = _T( "当前演示源无效" );
	}

	ShowPopMsg(strError);

	CListUI *pTileLayoutUI = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("VedioSourceList") );
	if ( pTileLayoutUI != NULL )
	{
		if (m_tDualSrcInfo.emCurrentType != emVgaTypeInValid)
		{
			pTileLayoutUI->SelectItem((int)m_tDualSrcInfo.emCurrentType,false);
		}
		else
		{
			pTileLayoutUI->SelectItem((int)m_tDualSrcInfo.emDefaultType,false);
		}
	}
	
	return NO_ERROR;
}

void CRoomCtrlLogic::UpdateVedioSourceList()
{
	ComInterface->GetDualSrcInfo( m_tDualSrcInfo );

	CListUI *pTileLayoutUI = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("VedioSourceList") );
	if ( pTileLayoutUI == NULL )
	{
		return;
	}
	if (!m_bIsVSListExt)//未创建
	{
		m_bIsVSListExt = true;
		pTileLayoutUI->RemoveAll();
		for ( u32 i = 0; i < m_tDualSrcInfo.vctVgaInfo.size(); i++ )
		{
			CListContainerElementUI *pListContainer = 
				(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("VedioSourceListItem") );

			ICncCommonOp::SetControlText( CA2T(m_tDualSrcInfo.vctVgaInfo.at(i).m_achAlias), m_pm, _T("vedioItemName"), pListContainer );
			CButtonUI* pBtnVedioItemSel = (CButtonUI*)ICncCommonOp::FindControl( m_pm, _T("btnSet"), pListContainer);
			if ( pBtnVedioItemSel )
			{
				pBtnVedioItemSel->SetTag((UINT_PTR)i/*(LPCTSTR)&(m_tDualSrcInfo.vctVgaInfo.at(i))*/);
			}

			pTileLayoutUI->Add(pListContainer);
		}
	}
	else//创建后进行更新
	{
		for ( u32 i = 0; i < m_tDualSrcInfo.vctVgaInfo.size(); i++ )
		{
			CListContainerElementUI *pListContainer = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(i);
			ICncCommonOp::SetControlText( CA2T(m_tDualSrcInfo.vctVgaInfo.at(i).m_achAlias), m_pm, _T("vedioItemName"), pListContainer );
		}
	}

	pTileLayoutUI->SelectItem((int)m_tDualSrcInfo.emCurrentType,false);
}

bool CRoomCtrlLogic::OnBtnVedioItemSel( TNotifyUI& msg )
{
	if (m_bSetVedioSourc)//在发消息未回应不可以继续操作
	{
		return false;
	}
	int index = msg.pSender->GetTag();
	CListUI *pTileLayoutUI = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("VedioSourceList") );
	if ( pTileLayoutUI == NULL )
	{
		return false;
	}

	pTileLayoutUI->SelectItem(index);

	return true;
}

bool CRoomCtrlLogic::OnBtnMicControl( TNotifyUI& msg )
{
    if (ComInterface->IsLocalCnsMute())
    {
        return false;
    }
	int nIndex = msg.pSender->GetTag();
	u16 wRet = 0;
	if (m_byMicState[nIndex])
	{
		ComInterface->SetMicStateCmd( nIndex, FALSE);
	}
	else
	{
		ComInterface->SetMicStateCmd( nIndex, TRUE);
	}
	
	return true;
}

bool CRoomCtrlLogic::OnSetTabShow( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	EM_ShortcutType em = (EM_ShortcutType)wParam;

	TNotifyUI msg;
	memset(&msg,0,sizeof(TNotifyUI));

	if (!m_bIsIni)
	{
		m_em = em;
		return true;
	}

	if ( em == emShortcutMute )
	{
		ICncCommonOp::OptionSelect(true,m_pm,_T("mic"));
	}
	else if ( em == emShortcutSilence )
	{
		ICncCommonOp::OptionSelect(true,m_pm,_T("speaker"));
	}
	else if ( em == emShortcutPanCam )
	{
		ICncCommonOp::OptionSelect(true,m_pm,_T("camera"));
		ICncCommonOp::OptionSelect(true,m_pm,_T("OptionFullCam"));
	}
	return true;
}

bool CRoomCtrlLogic::OnVedioItemSel( TNotifyUI& msg )
{
	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("VedioSourceList") );
	if ( pTileLayoutUI == NULL )
	{
		return false;
	}
	//如果前一个选中项为-1，则全部刷新一下
	if (msg.lParam == -1)
	{
		for ( u32 i = 0; i < m_tDualSrcInfo.vctVgaInfo.size(); i++ )//全部刷一下
		{
			CListContainerElementUI *pListContainer = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(i);
			ICncCommonOp::SetControlText(_T(""),m_pm,_T("lbvediosrc"),pListContainer);

			ICncCommonOp::SetControlBkImg( _T("res/roomctrl/btnVedioSel_disable.png"), m_pm, _T("btnSet"), pListContainer );
			ICncCommonOp::SetControlBkImg( _T("res/roomctrl/VedioSource_normal.png"), m_pm, _T("picLayout"), pListContainer );
		}
	}

	CListContainerElementUI *pListContainer = (CListContainerElementUI *)pTileLayoutUI->GetItemAt(msg.wParam);
	CListContainerElementUI *pListContainerOld = (CListContainerElementUI *)pTileLayoutUI->GetItemAt(msg.lParam);
	
	if (pListContainerOld)
	{
		ICncCommonOp::SetControlBkImg( _T("res/roomctrl/btnVedioSel_disable.png"), m_pm, _T("btnSet"), pListContainerOld );
		ICncCommonOp::SetControlBkImg( _T("res/roomctrl/VedioSource_normal.png"), m_pm, _T("picLayout"), pListContainerOld );

		//ICncCommonOp::SetControlTextColor( _T("#CCD5DEEB"), m_pm, _T("vedioItemName"), pListContainer );
		ICncCommonOp::SetControlText(_T(""),m_pm,_T("lbvediosrc"),pListContainerOld);//源状态清空，选择的等待消息进行设置
	}

	if (pListContainer)
	{
		ICncCommonOp::SetControlBkImg( _T("res/roomctrl/btnVedioSel.png"), m_pm, _T("btnSet"), pListContainer );
		ICncCommonOp::SetControlBkImg( _T("res/roomctrl/VedioSource_select.png"), m_pm, _T("picLayout"), pListContainer );
		
		//ICncCommonOp::SetControlTextColor( _T("#CC379FDB"), m_pm, _T("vedioItemName"), pListContainer );
	}

	if (m_bSetVedioSourc)//在发消息未回应不可以继续操作
	{
		return true;
	}

    if (m_tDualSrcInfo.vctVgaInfo.size() <= msg.wParam)
    {
        return false;
    }
	TVgaInfo tVgaInfo;
	tVgaInfo = m_tDualSrcInfo.vctVgaInfo.at(msg.wParam);

	BOOL32 bIsInconf = ComInterface->IsInConf();
	if (bIsInconf)
	{
		//会议中 切换当前演示源
		if ( tVgaInfo.m_emVgaType != m_tDualSrcInfo.emCurrentType )
		{
			m_bSetVedioSourc = true;
			pTileLayoutUI->SetEnabled(false);
			ComInterface->SelDualInputPort( tVgaInfo.m_emVgaType );	
		}
	}
	else
	{
		if ( tVgaInfo.m_emVgaType != m_tDualSrcInfo.emCurrentType )
		{
			//空闲时 切换默认演示源
			m_bSetVedioSourc = true;
			pTileLayoutUI->SetEnabled(false);
			ComInterface->SetDualPortInfo( tVgaInfo, true);		
		}
	}

	return true;
}

bool CRoomCtrlLogic::OnComboItemSel( TNotifyUI& msg )
{
	msg.pSender;
	return true;
}

bool CRoomCtrlLogic::onSpeakerVolChanging( TNotifyUI& msg )
{
	CString strVol=_T("");
	strVol.Format(_T("%d%%"),(static_cast<CSliderUI*>(msg.pSender))->GetValue());
	ICncCommonOp::SetControlText(strVol,m_pm,_T("lbspeakervol"));
	return true;
}

bool CRoomCtrlLogic::onMicVolChanging( TNotifyUI& msg )
{
	CString strVol=_T("");
	strVol.Format(_T("%d%%"),(static_cast<CSliderUI*>(msg.pSender))->GetValue());
	ICncCommonOp::SetControlText(strVol,m_pm,_T("lbmicvol"));
	return true;
}

bool CRoomCtrlLogic::OnMainVedioSetInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bIsSucsess = (BOOL)wParam;
	u8 wIndex = (u8)lParam;

	ComInterface->GetMainVideoPort( m_mapEmTPMtVideoPort );

	switch (wIndex)
	{
	case 0:
		{
			if (m_mapEmTPMtVideoPort[0] == emTPC1Vid)
			{
				ICncCommonOp::OptionSelect(true,m_pm,_T("Vedio1Op1"));
			}
			else
			{
				ICncCommonOp::OptionSelect(true,m_pm,_T("Vedio1Op2"));
			}
		}
		break;
	case 1:
		{
			if (m_mapEmTPMtVideoPort[1] == emTPC3Vid)
			{
				ICncCommonOp::OptionSelect(true,m_pm,_T("Vedio2Op1"));
			}
			else if (m_mapEmTPMtVideoPort[1] == emTPC4Vid)
			{
				ICncCommonOp::OptionSelect(true,m_pm,_T("Vedio2Op2"));
			}
			else
			{
				ICncCommonOp::OptionSelect(true,m_pm,_T("Vedio2Op3"));
			}
		}
		break;
	case 2:
		{
			if (m_mapEmTPMtVideoPort[2] == emTPC5Vid)
			{
				ICncCommonOp::OptionSelect(true,m_pm,_T("Vedio3Op1"));
			}
			else
			{
				ICncCommonOp::OptionSelect(true,m_pm,_T("Vedio3Op2"));
			}
		}
		break;
	}

	if (!bIsSucsess)
	{
		CString strMsg = _T("");
		strMsg.Format(_T("主视频源%d号设置失败"), wIndex+1 );
		ShowPopMsg(strMsg);
	}
	return true;
}

bool CRoomCtrlLogic::OnSetShortCheck( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	EM_ShortcutType em = (EM_ShortcutType)wParam;

	if ( em == emShortcutMute )
	{
		CCheckBoxUI *pControl = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckMicShortCut") );
		if (pControl)
		{
			pControl->SetCheckNoMsg(true);
		}
	}
	else if ( em == emShortcutSilence )
	{
		CCheckBoxUI *pControl = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckSpeakerShortCut") );
		if (pControl)
		{
			pControl->SetCheckNoMsg(true);
		}
	}
	return true;
}

bool CRoomCtrlLogic::OnVidSrcNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	u8 wSrcID = lParam;
	BOOL bIsSuccess = wParam;

	CString str = _T("空");
	if (bIsSuccess)
	{
		str = _T("[有源]");
	}

	switch (wSrcID)
	{
	case 0:
		{
			ICncCommonOp::SetControlText(_T(""),m_pm,_T("lbVedio1Op1"));
			ICncCommonOp::SetControlText(_T(""),m_pm,_T("lbVedio1Op2"));

			if (m_mapEmTPMtVideoPort[0] == emTPC1Vid)
			{
				ICncCommonOp::SetControlText(str,m_pm,_T("lbVedio1Op1"));
			}
			else
			{
				ICncCommonOp::SetControlText(str,m_pm,_T("lbVedio1Op2"));
			}
		}
		break;
	case 1:
		{
			ICncCommonOp::SetControlText(_T(""),m_pm,_T("lbVedio2Op1"));
			ICncCommonOp::SetControlText(_T(""),m_pm,_T("lbVedio2Op2"));
			ICncCommonOp::SetControlText(_T(""),m_pm,_T("lbVedio2Op3"));

			if (m_mapEmTPMtVideoPort[1] == emTPC3Vid)
			{
				ICncCommonOp::SetControlText(str,m_pm,_T("lbVedio2Op1"));
			}
			else if (m_mapEmTPMtVideoPort[1] == emTPC4Vid)
			{
				ICncCommonOp::SetControlText(str,m_pm,_T("lbVedio2Op2"));
			}
			else
			{
				ICncCommonOp::SetControlText(str,m_pm,_T("lbVedio2Op3"));
			}
		}
		break;
	case 2:
		{
			ICncCommonOp::SetControlText(_T(""),m_pm,_T("lbVedio3Op1"));
			ICncCommonOp::SetControlText(_T(""),m_pm,_T("lbVedio3Op2"));

			if (m_mapEmTPMtVideoPort[2] == emTPC5Vid)
			{
				ICncCommonOp::SetControlText(str,m_pm,_T("lbVedio3Op1"));
			}
			else
			{
				ICncCommonOp::SetControlText(str,m_pm,_T("lbVedio3Op2"));
			}
		}
		break;
	case 3:
		{
			CListUI *pTileLayoutUI = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("VedioSourceList") );
			if ( pTileLayoutUI == NULL )
			{
				return false;
			}

			for ( u32 i = 0; i < m_tDualSrcInfo.vctVgaInfo.size(); i++ )//全部刷一下
			{
				CListContainerElementUI *pListContainer = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(i);
				ICncCommonOp::SetControlText(_T(""),m_pm,_T("lbvediosrc"),pListContainer);

				ICncCommonOp::SetControlBkImg( _T("res/roomctrl/btnVedioSel_disable.png"), m_pm, _T("btnSet"), pListContainer );
				ICncCommonOp::SetControlBkImg( _T("res/roomctrl/VedioSource_normal.png"), m_pm, _T("picLayout"), pListContainer );
			}

			CListContainerElementUI *pListContainer = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(m_tDualSrcInfo.emCurrentType);
			ICncCommonOp::SetControlText(str,m_pm,_T("lbvediosrc"),pListContainer);
			ICncCommonOp::SetControlBkImg( _T("res/roomctrl/btnVedioSel.png"), m_pm, _T("btnSet"), pListContainer );
			ICncCommonOp::SetControlBkImg( _T("res/roomctrl/VedioSource_select.png"), m_pm, _T("picLayout"), pListContainer );

			pTileLayoutUI->SelectItem(m_tDualSrcInfo.emCurrentType);

		}
		break;
	}
	return true;
}

bool CRoomCtrlLogic::OnMinVedioInfoNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	EmTPMtVideoPort em = (EmTPMtVideoPort)wParam;

	if (em == emTPC4Vid)
	{
		ICncCommonOp::EnableControl(true,m_pm,_T("Vedio2Op1"));
		ICncCommonOp::EnableControl(true,m_pm,_T("Vedio2Op2"));
		ICncCommonOp::EnableControl(false,m_pm,_T("Vedio2Op3"));
	}
	else if ( em == emTPC7Vid)
	{
		ICncCommonOp::EnableControl(true,m_pm,_T("Vedio2Op1"));
		ICncCommonOp::EnableControl(false,m_pm,_T("Vedio2Op2"));
		ICncCommonOp::EnableControl(true,m_pm,_T("Vedio2Op3"));
	}
	else
	{
		ICncCommonOp::EnableControl(true,m_pm,_T("Vedio2Op1"));
		ICncCommonOp::EnableControl(true,m_pm,_T("Vedio2Op2"));
		ICncCommonOp::EnableControl(true,m_pm,_T("Vedio2Op3"));
	}


	return true;
}

bool CRoomCtrlLogic::OnSetVedioInfoNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	ComInterface->GetVedioInfo( m_tTPVideoInfoTool );
	UpdateSourceName();
	return NO_ERROR;
}

void CRoomCtrlLogic::UpdateSourceName()
{
	CString strlb = _T("");
	for (int i=0; i<emTPC7Vid + 1; i++)
	{
		strlb.Format(_T("lbVSource%d"),i);
		CString strName(CA2T(m_tTPVideoInfoTool.m_atVideoSourceName[i].m_achSourceName));
		if (!strName.IsEmpty())
		{
			ICncCommonOp::SetControlText(CA2T(m_tTPVideoInfoTool.m_atVideoSourceName[i].m_achSourceName), m_pm, strlb);
		}	
	}
}

bool CRoomCtrlLogic::OnCnDesktopMicInfoNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	BOOL bState = wParam;
	if (bState)
	{
		m_pm->DoCase(_T("NonDesktopMic"));
		m_bIsNonDesktopMic = TRUE;
	}
	else
	{
		m_pm->DoCase(_T("DesktopMic"));
		m_bIsNonDesktopMic = FALSE;
		//更新下桌面麦克风风格和状态
		UpdateMicStyle();
		UpdateMicState();
	}
	return NO_ERROR;
}

bool CRoomCtrlLogic::OnCnMicPowerStyleNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	TTpMicState tTpMicState = *(TTpMicState*)(wParam);
	for (int i = 0 ; i < TP_MIC_NUM ; i++)
	{
		m_byMicStyle[i] = tTpMicState.m_byMicState[i];
	}
	//如果是非桌面麦克风
	if(m_bIsNonDesktopMic)
	{
		return false;
	}
	//更新显示和状态
	UpdateMicStyle();
	UpdateMicState();
	return NO_ERROR;
}

bool CRoomCtrlLogic::OnCnMicPowerNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	TTpMicState tTpMicState = *(TTpMicState*)(wParam);
	for (int i = 0 ; i < TP_MIC_NUM ; i++)
	{
		m_byMicState[i] = tTpMicState.m_byMicState[i];
	}
	//如果是非桌面麦克风
	if(m_bIsNonDesktopMic)
	{
		return false;
	}
	//更新状态
	UpdateMicState();
	return NO_ERROR;
}

bool CRoomCtrlLogic::OnCnSetMicPowerRsp(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	u8 nIndex = wParam;
	BOOL bState = lParam;
	if (m_bIsFullState && !(0 == nIndex || 3 == nIndex || 6 == nIndex))
	{
		if (1 == nIndex || 4 == nIndex || 7 == nIndex)
		{
			if (bState != m_byMicState[nIndex] || bState != m_byMicState[nIndex+1])
			{
				m_byMicState[nIndex] = bState;
				m_byMicState[nIndex+1] = bState;
			}
		}
		else if (2 == nIndex || 5 == nIndex || 8 == nIndex)
		{
			if (bState != m_byMicState[nIndex] || bState != m_byMicState[nIndex-1])
			{
				m_byMicState[nIndex] = bState;
				m_byMicState[nIndex-1] = bState;
			}
		}
	}
	else
	{
		if (bState != m_byMicState[nIndex])
		{
			m_byMicState[nIndex] = bState;
		}
	}
	if(!m_bIsNonDesktopMic)
	{
		UpdateMicState();
	}
	
	return NO_ERROR;
}

bool CRoomCtrlLogic::OnCentreDFScreenConfigNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    TCenDownOrFlipScreenInfo tScreenInfo;
    ComInterface->GetCenDownOrFlipScreenInfo(tScreenInfo);
#ifndef LOGIN
    tScreenInfo.emDeviceType = emDefault;  //emXuanDeDFScreen
    tScreenInfo.dwGroupNum = 4;
    strcpy( tScreenInfo.tCenDownOrFlipScreenCfg[0].achGroupName, ("第五排会议桌") );
    tScreenInfo.tCenDownOrFlipScreenCfg[0].emAddrCode = emAddrCode_05;
    strcpy( tScreenInfo.tCenDownOrFlipScreenCfg[1].achGroupName, ("第四排会议桌") );
    tScreenInfo.tCenDownOrFlipScreenCfg[1].emAddrCode = emAddrCode_04;
    strcpy( tScreenInfo.tCenDownOrFlipScreenCfg[2].achGroupName, ("第三排会议桌") );
    tScreenInfo.tCenDownOrFlipScreenCfg[2].emAddrCode = emAddrCode_03;
    strcpy( tScreenInfo.tCenDownOrFlipScreenCfg[3].achGroupName, ("第二排会议桌") );
    tScreenInfo.tCenDownOrFlipScreenCfg[3].emAddrCode = emAddrCode_02;
    strcpy( tScreenInfo.tCenDownOrFlipScreenCfg[4].achGroupName, ("第一排会议桌") );
    tScreenInfo.tCenDownOrFlipScreenCfg[4].emAddrCode = emAddrCode_01;
#endif
    m_dwGroupNum = tScreenInfo.dwGroupNum;

    //界面显示
    CDuiString strHorLineSyle = _T("");
    CDuiString strSrceenLayout = _T("");
    CDuiString strLabGroup = _T("");
    u32 dwSerial = 0;  //标识指定控件序号
    //m_pm->DoCase(_T("caseScreenGrpHide"));
    for (u32 dwIndex = 0; dwIndex < NUM_SRCEEN_COUNT; dwIndex++)
    {
        dwSerial = dwIndex + 1;
        strHorLineSyle.Format(_T("HorLineStyle%d"), dwSerial);
        strSrceenLayout.Format(_T("SrceenLayout%d"), dwSerial);
        strLabGroup.Format(_T("LabGroup%d"), dwSerial);

        //选择 HorLineStyle
        if ( dwSerial == tScreenInfo.dwGroupNum )
        {
            ICncCommonOp::ShowControl(TRUE, m_pm, strHorLineSyle);
        }
        else
        {
            ICncCommonOp::ShowControl(FALSE, m_pm, strHorLineSyle);
        }

        //选择 SrceenLayout
        if (dwIndex < tScreenInfo.dwGroupNum)
        {
            ICncCommonOp::ShowControl(TRUE, m_pm, strSrceenLayout);
            ICncCommonOp::SetControlText( (CA2T)tScreenInfo.tCenDownOrFlipScreenCfg[dwIndex].achGroupName, m_pm, strLabGroup );
            m_byAllScreenCtrlSel |= dwIndex;
        }
        else
        {
            ICncCommonOp::ShowControl(FALSE, m_pm, strSrceenLayout);
        }
    }

    //选择屏幕操作类型
    if (tScreenInfo.emDeviceType == emXuanDeDFScreen)
    {
        m_pm->DoCase(_T("caseIsFlipSrceen"));
        ICncCommonOp::SetControlText(_T("翻转屏控制"), m_pm, _T("Screen"));
    }
    else
    {
        m_pm->DoCase(_T("caseIsLiftSrceen"));
        ICncCommonOp::SetControlText(_T("升降屏控制"), m_pm, _T("Screen"));
    }

    //升降旋转屏选择初始化
    m_pm->DoCase(_T("caseScreenIni"));

    return NO_ERROR;
}

bool CRoomCtrlLogic::OnCentreSelectDFScreenNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    memset(m_abSelectDFScreen, 0, sizeof(BOOL)*MAX_CENTREDFSCREEN_GROUP_NUM);
    memcpy(m_abSelectDFScreen, ComInterface->GetCenSelectDFScreen(), sizeof(BOOL)*MAX_CENTREDFSCREEN_GROUP_NUM);
    
    //当前升降屏排数勾选状态
    CDuiString strCaseTemp = _T("");
    u32 dwSerial = 0;
    for (u32 dwIndex = 0; dwIndex < m_dwGroupNum; dwIndex++)
    {
        dwSerial = dwIndex + 1;
        if ( m_abSelectDFScreen[dwIndex] )
        {
            strCaseTemp.Format(_T("caseCheckSelect%d"), dwSerial);
            m_pm->DoCase(strCaseTemp);
        }
        else
        {
            strCaseTemp.Format(_T("caseCheckNotSelect%d"), dwSerial);
            m_pm->DoCase(strCaseTemp);
        }
    }

    return true;
}

bool CRoomCtrlLogic::OnCentreDFScreenCmdInd(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    BOOL bSuccess = (BOOL)wParam;
    if (!bSuccess)
    {
        ShowMessageBox( _T("操作升降旋转屏失败") );
        return false;
    }

    return NO_ERROR;
}

bool CRoomCtrlLogic::OnSelectDFScreenInd(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    BOOL bSuccess = (BOOL)wParam;
    if (!bSuccess)
    {
        ShowMessageBox( _T("升降旋转屏排数勾选失败") );
        return false;
    }

    OnCentreSelectDFScreenNty(0, 0, bHandle);
    return NO_ERROR;
}

void CRoomCtrlLogic::UpdateMicStyle()
{
	m_bIsFullState = TRUE;//先将全状态置为TRUE，有缺少就置FALSE

	CHorizontalLayoutUI* pList1 = (CHorizontalLayoutUI*)ICncCommonOp::FindControl( m_pm, L"FirstRowList" );
	CHorizontalLayoutUI* pList2 = (CHorizontalLayoutUI*)ICncCommonOp::FindControl( m_pm, L"SecondRowList" );
    vector<int> vecFirstMicRow;
	vector<int> vecSecondMicRow;
	if (NULL != pList1 && NULL != pList2)
	{
		pList1->RemoveAll();
		pList2->RemoveAll();
		for (int i = 0 ; i < TP_MIC_NUM  ; i++)
		{
			if (0 == i || 3 == i || 6 == i)//第一排直接显示1 4 7号麦克风
			{
                vecFirstMicRow.push_back(i);
			}
			else//第二排
			{
				if (m_byMicStyle[i] == TRUE)
				{
					vecSecondMicRow.push_back(i);
				}
				else
				{
					m_bIsFullState = FALSE;
				}
			}
		}
        //显示第一排
        for (int i = 0 ; i < NUM_MIC_FIRLINE ; i++)
        {
            vector<int>::iterator it = vecFirstMicRow.begin();
            for ( ; it != vecFirstMicRow.end() ; it++ )
            {
                if (m_nFirstLineMic[i] == *it)
                {
                    CVerticalLayoutUI *pListContainer = (CVerticalLayoutUI*)CONTROLFACTORY()->GetControl( _T("MicItem") );
                    CButtonUI* pButtonMic = (CButtonUI*)ICncCommonOp::FindControl( m_pm, _T("micControlBtn"), pListContainer);
                    if (pButtonMic)
                    {
                        pButtonMic->SetTag(*it);
                        pButtonMic->SetEnabled(m_byMicStyle[*it]);
                    }
                    pList1->Add(pListContainer);
                    vecFirstMicRow.erase(it);
                    if (!vecFirstMicRow.empty())
                    {
                        CVerticalLayoutUI *pListline = (CVerticalLayoutUI*)CONTROLFACTORY()->GetControl( _T("MicItemLine") );
                        pList1->Add(pListline);
                    }
                    break;
                }
            }
        }
		//显示第二排
		if (vecSecondMicRow.empty())
		{
			m_pm->DoCase(_T("caseSingleRow"));
		}
		else
		{
			m_pm->DoCase(_T("caseDoubleRow"));
			if (vecSecondMicRow.size() <= 3)
			{
				m_pm->DoCase(_T("caseThreeMic"));
			}
			else
			{
				m_pm->DoCase(_T("caseSixMic"));
			}
            for (int i = 0 ; i < NUM_MIC_SECLINE ; i++)
            {
                vector<int>::iterator it = vecSecondMicRow.begin();
                for ( ; it != vecSecondMicRow.end() ; it++ )
                {
                    if (m_nSecondLineMic[i] == *it)
                    {
                        CVerticalLayoutUI *pListContainer = (CVerticalLayoutUI*)CONTROLFACTORY()->GetControl( _T("MicItem") );
                        CButtonUI* pButtonMic = (CButtonUI*)ICncCommonOp::FindControl( m_pm, _T("micControlBtn"), pListContainer);
                        if (pButtonMic)
                        {
                            pButtonMic->SetTag(*it);
                        }
                        pList2->Add(pListContainer);
                        vecSecondMicRow.erase(it);
                        if ( !vecSecondMicRow.empty() && !(m_bIsFullState && (i == 0 || i == 2 || i == 4)))
                        {
                            CVerticalLayoutUI *pListline = (CVerticalLayoutUI*)CONTROLFACTORY()->GetControl( _T("MicItemLine") );
                            pList2->Add(pListline);
                        }
                        break;
                    }
                }
            }
		}
	}
}

void CRoomCtrlLogic::UpdateMicState()
{
	CHorizontalLayoutUI* pList1 = (CHorizontalLayoutUI*)ICncCommonOp::FindControl( m_pm, L"FirstRowList" );
	CHorizontalLayoutUI* pList2 = (CHorizontalLayoutUI*)ICncCommonOp::FindControl( m_pm, L"SecondRowList" );
	if (NULL != pList1 && NULL != pList2)
	{
		for (int i = 0 ; i < pList1->GetCount() ; i++)
		{
			CVerticalLayoutUI *pListContainer = (CVerticalLayoutUI*)pList1->GetItemAt(i);
			if (pListContainer)
			{
				CButtonUI* pButtonMic = (CButtonUI*)ICncCommonOp::FindControl( m_pm, _T("micControlBtn"), pListContainer);
				if (pButtonMic && pButtonMic->IsEnabled())
				{
					int nIndex = pButtonMic->GetTag();
					if (m_byMicState[nIndex])
					{
						pButtonMic->SetBkImage(_T("res/roomctrl/micYes.png"));
					}
					else
					{
						pButtonMic->SetBkImage(_T("res/roomctrl/micNo.png"));
					}
				}
			}
		}
		for (int i = 0 ; i < pList2->GetCount() ; i++)
		{
			CVerticalLayoutUI *pListContainer = (CVerticalLayoutUI*)pList2->GetItemAt(i);
			if (pListContainer)
			{
				CButtonUI* pButtonMic = (CButtonUI*)ICncCommonOp::FindControl( m_pm, _T("micControlBtn"), pListContainer);
				if (pButtonMic)
				{
					int nIndex = pButtonMic->GetTag();
					if (m_byMicState[nIndex])
					{
						pButtonMic->SetBkImage(_T("res/roomctrl/micYes.png"));
					}
					else
					{
						pButtonMic->SetBkImage(_T("res/roomctrl/micNo.png"));
					}
				}
			}
		}
	}
}
