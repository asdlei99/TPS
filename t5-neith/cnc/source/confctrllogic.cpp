#include "StdAfx.h"
#include "confctrllogic.h"
#include "audmixlogic.h"
#include "confpolllogic.h"
#include "videomixlogic.h"
#include "confmsglogic.h"
#include "confmixlogic.h"
#include "confrolllogic.h"
#include "mainframelogic.h"
#include "srcselwatch.h"
#include "eventoutcnssipdual.h"

APP_BEGIN_MSG_MAP(CConfCtrlLogic, CNotifyUIImpl)
	MSG_CREATEWINDOW(_T("ConfCtrlLayout"), OnCreate)
	MSG_INIWINDOW(_T("ConfCtrlLayout"), OnInit)
	
	MSG_SELECTCHANGE(_T("confcns"), OnTabConfCns)
	MSG_SELECTCHANGE(_T("vidmix"), OnTabVideoMix)
	MSG_SELECTCHANGE(_T("confMix"), OnTabConfMix)
	MSG_SELECTCHANGE(_T("confpoll"), OnTabConfPoll)
	MSG_SELECTCHANGE(_T("confroll"), OnTabConfRoll)
	MSG_SELECTCHANGE(_T("audmix"), OnTabAudioMix) 
	MSG_SELECTCHANGE(_T("confdual"), OnTabConfDual)
	MSG_SELECTCHANGE(_T("mixmotive"), OnTabMixMotive)
	MSG_SELECTCHANGE(_T("pip"), OnTabPIP)
	MSG_SELECTCHANGE(_T("tvwall"), OnTabTVWall)
	MSG_SELECTCHANGE(_T("FeccCam"), OnTabFeccCam)

	MSG_CLICK(_T("btnSet"), OnBtnVedioItemSel)
	MSG_ITEMSELECTD(_T("VedioSourceList"), OnVedioItemSel)

	MSG_CLICK(_T("btnGoLeft"), OnBtnGoLeft)
	MSG_CLICK(_T("btnGoRight"), OnBtnGoRight)

	MSG_CLICK(_T("BtnSetSpeaker"), OnBtnSetSpeaker)
	MSG_CLICK(_T("BtnSetDual"), OnBtnSetDual)
	MSG_CLICK(_T("BtnSetQuiet"), OnBtnSetQuiet)
	MSG_CLICK(_T("BtnSetMute"), OnBtnSetMute)	
	MSG_CLICK(_T("BtnHungupCns"), OnBtnHungupCns)
	MSG_CLICK(_T("BtnSelectPlay"), OnBtnSelectPlay)
	MSG_CLICK(_T("BtnCancelSelView"), OnBtnCancelSelView)
	MSG_ITEMCLICK(_T("ConfCnsListItem"), OnConfCnsItemClick)
	MSG_SELECTCHANGE(_T("BtnConfCnsSel"), OnCheckConfCnsItem)
    MSG_EDITCHANGE(_T("ConfCtrlEdtSearch"), OnSearchEditChange)  
    MSG_ITEMSELECTD(_T("ComboConfCtrlShowEx"), OnComboShowEx)
	
	MSG_CLICK(_T("ListBtnSetCam"), OnBtnItemSetCam)
	MSG_CLICK(_T("ListBtnSetDual"), OnBtnItemSetDual)
	MSG_CLICK(_T("ListBtnSetSpeaker"), OnBtnItemSetSpeaker)
	MSG_CLICK(_T("ListBtnSelectPlay"), OnBtnItemSelectPlay)
	MSG_CLICK(_T("ListBtnSetQuiet"), OnBtnItemSetQuiet)
	MSG_CLICK(_T("ListBtnSetMute"), OnBtnItemSetMute)
	MSG_CLICK(_T("ListBtnHangUp"), OnBtnItemHangUp)
	
	MSG_CLICK(_T("BtnConfCall"), OnBtnItemCall)

    MSG_CLICK(_T("BtnListMainPath"), OnBtnListMainPath)
    MSG_CLICK(_T("txtMainPath"), OnBtnListMainPath)

	MSG_SELECTCHANGE(_T("CheckCnsDual"), OnCheckLocalCnsDual)
	MSG_SELECTCHANGE(_T("CheckDualShotCut"), OnCheckDualShotCut)
	MSG_SELECTCHANGE(_T("CheckVoiceArouse"), OnCheckPTPVoiceArouse)//点对点语音激励
	MSG_SELECTCHANGE(_T("CheckVSShortCut"), OnCheckVSShortCut)
	MSG_SELECTCHANGE(_T("CheckPIP"), OnCheckPIP)
	MSG_SELECTCHANGE(_T("CheckPIPShortCut"), OnCheckPIPShortCut)

    USER_MSG(UI_UMS_SET_MUTE_CNS_RSP,OnSetMuteCnsRsp)
    USER_MSG(UI_UMS_SET_QUIET_CNS_RSP,OnSetQuietCnsRsp)

	//USER_MSG(UI_UMS_AUDMIXVAC_IND,OnVoiceArouseInd)
	USER_MSG(UI_CNS_VIEWLOCALPIP_IND,OnPIPInd)
	USER_MSG(UI_CNS_VIEWLOCALPIP_NTY,OnPIPNty)
	USER_MSG(UI_CNS_START_DUAL_RSP,OnCnsDualRsp)
	USER_MSG(UI_CNS_RECV_DUAL_NOTIFY,OnRecvDualNty)
	USER_MSG(UI_CNS_DUALOFFLINE_NOTIFY,OnDualOffLineNotify)
	USER_MSG(UI_RECV_DUAL_INTERRUPT,OnDualRcvInterruptNotify)
	USER_MSG(UI_CNS_DUAL_STATE_NOTIFY,OnCnsDualNty)
	USER_MSG( UI_CNS_CONFSTATE_NOTIFY, OnConfStateNty )
	USER_MSG( UI_UMS_REFRESH_CONFCNS_LIST, OnRefreshCnsLstNotify )

	USER_MSG(UI_CNC_SHOW_SHORTCUTDLG_NTY,OnSetTabShow)
	USER_MSG(UI_CNC_SHORTCUTCHECK_NTY,OnSetShortCheck)

	USER_MSG(UI_DISCONNECTED_CLEARDATA, OnDisconnect)

	MSG_LETTERINDEX_CLICK(_T("ConfCnsListIndex"),OnLetterIndex)
	//发言人设定 dyy2015-6-25
	USER_MSG(UI_UMS_CHANGE_SPEAKER_NOTIFY,OnSpeakerNty)
	USER_MSG(UI_UMS_SET_SPEAKER_IND,OnSpeakerInd)
	//会场双流 2015-6-26
	USER_MSG(UI_UMS_SET_DUAL_CNS_RSP,OnItemDualInd)//提示
	USER_MSG(UI_UMS_DUAL_CNS_NOTIFY,OnItemDualNty)//状态
	//会议选看通知
	USER_MSG(UI_CNS_SEL_VIEW_NTY,OnItemSelViewNty) 
	//呼叫不在线会场回应
	USER_MSG(UI_UMS_INVITE_CNS_RSP,OnCallOffCnsInd) 

	//单独控制语音激励开关回应
	USER_MSG( UI_CNS_CNAUXMIX_IND, OnCnAuxInd )
	//主席设置 防止先收到会议状态时还没收到主席
	USER_MSG( UI_CNS_CHAIRCONFINFO_NTY, OnConfStateNty )
	//全场哑音/静音
	USER_MSG(UI_CNC_SHORTCUT_QUITEALL,OnShortCutQuiteAll)
	USER_MSG(UI_CNC_SHORTCUT_MUTEALL,OnShortCutMuteAll)

	//视频源状态通知
	USER_MSG(UI_CNS_VIDSRC_NTY,OnVidSrcNty)
	USER_MSG(UI_CNS_VGAINFO_NOTIFY,OnVgaInfoNotify)
	USER_MSG(UI_CNS_CONFVGAINFO_NOTIFY,OnVgaInfoNotify)
	USER_MSG(UI_CNS_SELDUALPORT_IND,OnSelDualPortInd)    
	USER_MSG(UI_CNS_SELDEFAULTDUALPORT_IND,OnSelDefaultDualPortInd)

    USER_MSG(WM_DUI_EDITSETFOCUS, OnEditSetFocus)	
APP_END_MSG_MAP()


const String CConfCtrlLogic::strConfCtrlSlideTab = _T("ConfCtrlSlideTab");
const String CConfCtrlLogic::strConfCnsList = _T("ConfCnsList");
const String CConfCtrlLogic::strConfCnsItem = _T("ConfCnsListItem");

static UINT g_nDualWaiting = 0;//控制双流操作间隔1s
VOID  CALLBACK  CBDualWaitingFun( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{   
	if ( idEvent == g_nDualWaiting )
	{
		::KillTimer( NULL, g_nDualWaiting );
		g_nDualWaiting = 0;
		CConfCtrlLogic::GetSingletonPtr()->OnDualWaitOverTime();
	} 
}

template<> CConfCtrlLogic* Singleton<CConfCtrlLogic>::ms_pSingleton = NULL;
CConfCtrlLogic::CConfCtrlLogic(void) : m_pConfCnsList(NULL), m_emCnsShowState(emShowAll)
{
	m_nSelIndex = -1;

	m_nPollFlag = 0;
	m_wPollTotalNum = 0;
	m_bIsFirstPollListNty = true;
	m_CurPollItemId = -1;

	m_bIsIni = false;
	m_nEmShort = -1;
    m_bSearchEdit = FALSE;
	g_nDualWaiting = 0;

	m_bIsVSListExt = false;
	m_bSetVedioSourc = false;
}

CConfCtrlLogic::~CConfCtrlLogic(void)
{
}

bool CConfCtrlLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_nSelIndex = -1;

	m_nPollFlag = 0;
	m_wPollTotalNum = 0;
	m_bIsFirstPollListNty = true;
	m_CurPollItemId = -1;

    m_bSearchEdit = FALSE;
	m_vctCnsList.clear();
	m_vctSearchList.clear();
	m_vctSelectList.clear();//断链清空 dyy 2015-6-30
    m_vctChildCnsList.clear();
    m_vctShowList.clear();
    m_tParentCns.Clear();

	m_tDualSrcInfo.Clear();
	m_bIsVSListExt = false;
	m_bSetVedioSourc = false;

	UpdateShowList();
    UpdateListPath();
	
	CComboBoxUI *pCombo = (CComboBoxUI*)ICncCommonOp::FindControl(m_pm,_T("ComboConfCtrlShowEx"));
	if (pCombo)
	{
		pCombo->SelectItem(0);
	}

	CCheckBoxUI* pCheckPIP = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckPIP"));
	if ( pCheckPIP )
	{
		pCheckPIP->SetCheckNoMsg(false);
	}
	pCheckPIP = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckCnsDual"));
	if ( pCheckPIP )
	{
		pCheckPIP->SetCheckNoMsg(false);
	}
	pCheckPIP = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckVoiceArouse"));
	if ( pCheckPIP )
	{
		pCheckPIP->SetCheckNoMsg(false);
	}

	if (g_nDualWaiting != 0)
	{
		::KillTimer( NULL, g_nDualWaiting );
		g_nDualWaiting = 0;
		OnDualWaitOverTime();
	}

	ICncCommonOp::SetControlText( _T(""), m_pm, _T("ConfCtrlEdtSearch") );
	return true;
}

bool CConfCtrlLogic::OnCreate( TNotifyUI& msg )
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

    m_pConfCnsList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, strConfCnsList.c_str() );
    if ( m_pConfCnsList == NULL )
    {
        return false;
    }

	return false;
}

bool CConfCtrlLogic::OnInit(TNotifyUI& msg)
{
    CComboUI* pComboEx = (CComboUI*)ICncCommonOp::FindControl( m_pm, _T("ComboConfCtrlShowEx") );
    if ( pComboEx != NULL )
    {	
        CListLabelElementUI *pListLabelElement1 = 
            (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
        pListLabelElement1->SetText(_T("全  部"));
        pComboEx->Add(pListLabelElement1);

        CListLabelElementUI *pListLabelElement2 = 
            (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
        pListLabelElement2->SetText(_T("在  线"));
        pComboEx->Add(pListLabelElement2);

        CListLabelElementUI *pListLabelElement3 = 
            (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
        pListLabelElement3->SetText(_T("不在线"));
        pComboEx->Add(pListLabelElement3);

        CListLabelElementUI *pListLabelElement4 = 
            (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
        pListLabelElement4->SetText(_T("发言会场"));
        pComboEx->Add(pListLabelElement4);
    }


    CVideoMixLogic::GetSingletonPtr()->InitVideoMixPage();
	CAudMixLogic::GetSingletonPtr()->UpdateList();

	m_bIsIni = true;
	if (m_nEmShort != -1)
	{
		SetShortCutShow((EM_ShortcutType)m_nEmShort);
	}
	
	UpdateCnsList();
	UpdateShowList();
	return true;
}

bool CConfCtrlLogic::OnTabConfCns(TNotifyUI& msg)
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, strConfCtrlSlideTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(emTabID_ConfCns);
	}

    String strCurWnd = UIDATAMGR->GetCurShowWndName();
    if ( strCurWnd == g_stcStrTvWallChildDlg )
    {
        NOTIFY_MSG( UI_CNC_HIDE_TVWALLCHILDDLG_NTY, NULL, NULL );
    }
	return true;
}


bool CConfCtrlLogic::OnTabConfMix(TNotifyUI& msg)
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, strConfCtrlSlideTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(emTabID_ConfMix);
	}

	CConfMixLogic::GetSingletonPtr()->UpdateMixList();

    String strCurWnd = UIDATAMGR->GetCurShowWndName();
    if ( strCurWnd == g_stcStrTvWallChildDlg )
    {
        NOTIFY_MSG( UI_CNC_HIDE_TVWALLCHILDDLG_NTY, NULL, NULL );
    }
	return true;
}

bool CConfCtrlLogic::OnTabVideoMix(TNotifyUI& msg)
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, strConfCtrlSlideTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(emTabID_VideoMix);
	}

    String strCurWnd = UIDATAMGR->GetCurShowWndName();
    if ( strCurWnd == g_stcStrTvWallChildDlg )
    {
        NOTIFY_MSG( UI_CNC_HIDE_TVWALLCHILDDLG_NTY, NULL, NULL );
    }
	return true;
}
	
bool CConfCtrlLogic::OnTabConfPoll(TNotifyUI& msg)
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, strConfCtrlSlideTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(emTabID_ConfPoll);
	}

    String strCurWnd = UIDATAMGR->GetCurShowWndName();
    if ( strCurWnd == g_stcStrTvWallChildDlg )
    {
        NOTIFY_MSG( UI_CNC_HIDE_TVWALLCHILDDLG_NTY, NULL, NULL );
    }
	return true;
}

bool CConfCtrlLogic::OnTabConfRoll(TNotifyUI& msg)
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, strConfCtrlSlideTab.c_str() );
	if (pControl)
	{
		CConfRollLogic::GetSingletonPtr()->UpdateRoller();
		pControl->SelectItem(emTabID_ConfRoll);
	}

    String strCurWnd = UIDATAMGR->GetCurShowWndName();
    if ( strCurWnd == g_stcStrTvWallChildDlg )
    {
        NOTIFY_MSG( UI_CNC_HIDE_TVWALLCHILDDLG_NTY, NULL, NULL );
    }
	return true;
}

bool CConfCtrlLogic::OnTabAudioMix(TNotifyUI& msg)
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, strConfCtrlSlideTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(emTabID_AudioMix);
	}

    String strCurWnd = UIDATAMGR->GetCurShowWndName();
    if ( strCurWnd == g_stcStrTvWallChildDlg )
    {
        NOTIFY_MSG( UI_CNC_HIDE_TVWALLCHILDDLG_NTY, NULL, NULL );
    }
	return true;
}

bool CConfCtrlLogic::OnTabConfDual(TNotifyUI& msg)
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, strConfCtrlSlideTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(emTabID_ConfDual);
	}

    String strCurWnd = UIDATAMGR->GetCurShowWndName();
    if ( strCurWnd == g_stcStrTvWallChildDlg )
    {
        NOTIFY_MSG( UI_CNC_HIDE_TVWALLCHILDDLG_NTY, NULL, NULL );
    }
	return true;
}

bool CConfCtrlLogic::OnTabMixMotive(TNotifyUI& msg)
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, strConfCtrlSlideTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(emTabID_MixMotive);
	}

    String strCurWnd = UIDATAMGR->GetCurShowWndName();
    if ( strCurWnd == g_stcStrTvWallChildDlg )
    {
        NOTIFY_MSG( UI_CNC_HIDE_TVWALLCHILDDLG_NTY, NULL, NULL );
    }
	return true;
}
	
bool CConfCtrlLogic::OnTabPIP(TNotifyUI& msg)
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, strConfCtrlSlideTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(emTabID_PIP);
	}

    String strCurWnd = UIDATAMGR->GetCurShowWndName();
    if ( strCurWnd == g_stcStrTvWallChildDlg )
    {
        NOTIFY_MSG( UI_CNC_HIDE_TVWALLCHILDDLG_NTY, NULL, NULL );
    }
	return true;
}

bool CConfCtrlLogic::OnTabTVWall(TNotifyUI& msg)
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, strConfCtrlSlideTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(emTabID_TvWall);
	}
	return true;
}

bool CConfCtrlLogic::OnTabFeccCam(TNotifyUI& msg)
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, strConfCtrlSlideTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(emTabID_ConfCns);
	}
	ICncCommonOp::ShowControl( true, m_pm, _T("ConfroomCramerLayout") );
	//ICncCommonOp::SetControlText(CA2T(tCnsInfo.m_achRoomName), m_pm, _T("LabConfName"));
	m_pm->DoCase(_T("caseP2PFeccCam"));

	return true;
}

bool CConfCtrlLogic::OnBtnGoLeft(TNotifyUI& msg)
{
	m_pm->DoCase(_T("caseMultyIni"));
	return true;
}

bool CConfCtrlLogic::OnBtnGoRight(TNotifyUI& msg)
{
	m_pm->DoCase(_T("caseMultyExta"));
	return true;
}

bool CConfCtrlLogic::OnBtnSetSpeaker(TNotifyUI& msg)
{
    if( m_vctSelectList.empty() )
    {
		ShowMessageBox(_T("请先选择进行设置的会场"));
        return false;
    }
    TCnsInfo tCnsInfo = m_vctSelectList.at(0);

	if (m_tConfInfo.m_wSpeaker == tCnsInfo.m_wEpID)
	{
		return true;//已经是发言人不重复发送消息
	}

    TConfEpID  tConfEpInfo ;
    tConfEpInfo.m_wConfID = m_tConfInfo.m_wConfID;
    tConfEpInfo.m_wEpID = tCnsInfo.m_wEpID;
    u16 wRe = ComInterface->SetSpokeCns( tConfEpInfo );

	return true;
}

bool CConfCtrlLogic::OnBtnSetDual(TNotifyUI& msg)
{
    if( m_vctSelectList.empty() )
    {
		ShowMessageBox(_T("请先选择进行设置的会场"));
        return false;
    }
    TCnsInfo tCnsInfo = m_vctSelectList.at(0);

    TConfEpID  tConfEpInfo ;
    tConfEpInfo.m_wConfID = m_tConfInfo.m_wConfID;
    tConfEpInfo.m_wEpID = tCnsInfo.m_wEpID;

    u16 wRe = ComInterface->SetDualCns( tConfEpInfo,TRUE );

	return true;
}

bool CConfCtrlLogic::OnBtnSelectPlay( TNotifyUI& msg )
{
	if( m_vctSelectList.empty() )
	{
		ShowMessageBox(_T("请先选择进行设置的会场"));
		return false;
	}
	TCnsInfo tCnsInfo = m_vctSelectList.at(0);

	TTPCnsInfo tlocalCnsInfo;
	ComInterface->GetLocalCnsInfo(tlocalCnsInfo);

	TCnsInfo *tCnsInfoLocal = m_tConfInfo.GetLocalCnsInfo( tlocalCnsInfo );
	if (tCnsInfoLocal == NULL)
	{
		return false;
	}

	if (tCnsInfoLocal->m_wEpID == tCnsInfo.m_wEpID)//不可以选看自己
	{
		ShowMessageBox(_T("会场选看设置失败：不可以选看本会场"));
		return false;
	}

	TTPSelViewReq tTPSelViewReq;
	tTPSelViewReq.m_emType = EmEpType_Ter;
	tTPSelViewReq.m_emUIType = EmUI_CNC;
	tTPSelViewReq.m_wConfID = m_tConfInfo.m_wConfID;
	tTPSelViewReq.m_wScreenIndx = TP_MAX_STREAMNUM;//会场选看
	tTPSelViewReq.m_wEpID = tCnsInfoLocal->m_wEpID;
	tTPSelViewReq.m_wDstID = tCnsInfo.m_wEpID;
	if ( tCnsInfo.m_wEpID == m_tConfInfo.m_wSelViewConfID )
	{
		tTPSelViewReq.m_bSel = false;
	}
	else
	{
		tTPSelViewReq.m_bSel = true;
	}

	u16 wRe = ComInterface->SetSelView( tTPSelViewReq);
	if ( wRe != NO_ERROR )
	{
		CString str;
		str.Format(_T("会场选看设置失败"));
		ShowMessageBox(str);
	}
	
	return true;
}

bool CConfCtrlLogic::OnBtnSetQuiet(TNotifyUI& msg)
{
    if( m_vctSelectList.empty() )
    {
		ShowMessageBox(_T("请先选择进行设置的会场"));
        return false;
    }

	//有一个不是静音 就将不是静音的设为静音,全是静音 就全设置不是静音 xcr确认 2015-6-25 dyy
	bool bIsAllQuiet = true;//是否全部已经是静音状态
	for (int i=0; i<m_vctSelectList.size(); i++)
	{
		TCnsInfo tCnsInfo = m_vctSelectList.at(i);
		if ( !tCnsInfo.m_bQuiet && tCnsInfo.m_bOnline)
		{
			TConfEpID  tConfEpInfo ;
			tConfEpInfo.m_wConfID = m_tConfInfo.m_wConfID;
			tConfEpInfo.m_wEpID = tCnsInfo.m_wEpID;

			u16 wRe = ComInterface->SetQuietCns( tConfEpInfo, TRUE );

			bIsAllQuiet = false;
		}
	}

	if (bIsAllQuiet)//全是静音 全取消静音
	{
		for (int i=0; i<m_vctSelectList.size(); i++)
		{
			TCnsInfo tCnsInfo = m_vctSelectList.at(i);
			
			TConfEpID  tConfEpInfo ;
			tConfEpInfo.m_wConfID = m_tConfInfo.m_wConfID;
			tConfEpInfo.m_wEpID = tCnsInfo.m_wEpID;

			u16 wRe = ComInterface->SetQuietCns( tConfEpInfo, FALSE );			
		}
	}

	return true;
}

bool CConfCtrlLogic::OnBtnSetMute(TNotifyUI& msg)
{
    if( m_vctSelectList.empty() )
    {
		ShowMessageBox(_T("请先选择进行设置的会场"));
        return false;
    }

	//有一个不是哑音 就将不是哑音的设为静音,全是哑音 就全设置不是哑音 xcr确认 2015-6-25 dyy
	bool bIsAllMute = true;//是否全部已经是静音状态
	for (int i=0; i<m_vctSelectList.size(); i++)
	{
		TCnsInfo tCnsInfo = m_vctSelectList.at(i);
		if ( !tCnsInfo.m_bMute  && tCnsInfo.m_bOnline)
		{
			TConfEpID  tConfEpInfo ;
			tConfEpInfo.m_wConfID = m_tConfInfo.m_wConfID;
			tConfEpInfo.m_wEpID = tCnsInfo.m_wEpID;

			u16 wRe = ComInterface->SetMuteCns( tConfEpInfo, TRUE );

			bIsAllMute = false;
		}
	}

	if (bIsAllMute)//全是哑音 全取消哑音
	{
		for (int i=0; i<m_vctSelectList.size(); i++)
		{
			TCnsInfo tCnsInfo = m_vctSelectList.at(i);

			TConfEpID  tConfEpInfo ;
			tConfEpInfo.m_wConfID = m_tConfInfo.m_wConfID;
			tConfEpInfo.m_wEpID = tCnsInfo.m_wEpID;

			u16 wRe = ComInterface->SetMuteCns( tConfEpInfo, FALSE );
		}
	}

	return true;
}

bool CConfCtrlLogic::OnBtnHungupCns(TNotifyUI& msg)
{
    if( m_vctSelectList.empty() )
    {
		ShowMessageBox(_T("请先选择进行设置的会场"));
        return false;
    }

	//选中中在线的全部挂断 xcr确认 2015-6-25 dyy
	for (int i=0; i<m_vctSelectList.size(); i++)
	{
		TCnsInfo tCnsInfo = m_vctSelectList.at(i);
		if ( tCnsInfo.m_bOnline )
		{
			//如果是主会场，则需要用户确认
			if ( tCnsInfo.m_wEpID == m_tConfInfo.GetChairCnsID()  )
			{
				UIDATAMGR->setLocalCnsState( emLocalCnsWillHungup );
				int nReslut = ShowMessageBox(  _T("挂断主席会场将结束会议，是否结束会议"), true );
				if ( IDOK == nReslut )
				{
					u16 wRe = NO_ERROR;
					if ( m_tConfInfo.m_emConfType == emCallType_Conf )
					{
						wRe = ComInterface->HangupConf();
					}
					else
					{                 
						wRe = ComInterface->HungupPtpConf();
					}
				}
			}
			else
			{
				TConfEpID  tConfEpInfo ;
				tConfEpInfo.m_wConfID = m_tConfInfo.m_wConfID;
				tConfEpInfo.m_wEpID = tCnsInfo.m_wEpID;

				u16 wRe = ComInterface->HangupCns( tConfEpInfo );
			}
		}
	}

	return true;
}

bool CConfCtrlLogic::OnConfCnsItemClick(TNotifyUI& msg)
{
	//会议讨论中也调用了相同的列表项，用列表名进行判断 dyy 2015-3-27
	if (msg.pSender->GetParent()->GetName() != _T("ConfCnsList"))
	{
		return false;
	}

	if ( const CListContainerElementUI *pItem = dynamic_cast<const CListContainerElementUI*>(msg.pSender) )
	{
        TCnsInfo tCnsInfo = *(TCnsInfo*)pItem->GetTag();
        if (!tCnsInfo.m_bOnline)
        {
            return true;
        }

        if ( tCnsInfo.m_emEpType == emTPEndpointTypeUMS || tCnsInfo.m_emEpType == emTPEndpointH323MCU )
        {
            //进入下级列表
            m_tParentCns = tCnsInfo;

            m_vctChildCnsList.clear();
			m_bSearchEdit = FALSE;
			ICncCommonOp::SetControlText(_T(""), m_pm, _T("ConfCtrlEdtSearch"));

            for ( int i = 0; i < m_vctCnsList.size(); i++ )
            {
                if ( m_vctCnsList.at(i).m_wParentEpID == m_tParentCns.m_wEpID )
                {
                    m_vctChildCnsList.push_back( m_vctCnsList.at(i) );
                }
            }         
            UpdateShowList();
            UpdateListPath();
        }
        else
        {
            if ( !m_vctSelectList.empty() )
            {
                return true;
            }

            if (!ComInterface->IsLocalCnsChairMan())//不是主席不能控制
            {
                return true;
            }

            int nIndex = pItem->GetIndex();
            if ( m_nSelIndex == -1 )
            {
				if( tCnsInfo.m_emEpType == emTPEndpointH323MT )
				{
					m_pm->DoCase( _T("caseListSel323"), msg.pSender );
				}
				else
				{
					m_pm->DoCase( _T("caseListSel"), msg.pSender );
				}

                if ( tCnsInfo.m_wEpID == m_tConfInfo.m_wSpeaker )
                {
                    //发言人不可用
                    ICncCommonOp::EnableControl( false, m_pm, _T("ListBtnSetSpeaker"), (CControlUI*)pItem );
                }
                else
                {
                    ICncCommonOp::EnableControl( true, m_pm, _T("ListBtnSetSpeaker"), (CControlUI*)pItem );
                }
                m_nSelIndex = nIndex;
            }
            else
            {
                if ( m_nSelIndex == nIndex )
                {
                    m_pm->DoCase( _T("caseListNoSel"), msg.pSender );
                    m_nSelIndex = -1;
                }
                else
                {
                    CControlUI *pLastSel = m_pConfCnsList->GetItemAt(m_nSelIndex);
                    if (m_vctShowList.at(m_nSelIndex).m_bOnline)//在线
                    {
                        m_pm->DoCase( _T("caseListNoSel"), pLastSel );
                    }
                    else//不在线
                    {
                        m_pm->DoCase( _T("caseListDisabled"), pLastSel );
                    }

                    //m_pm->DoCase( _T("caseListSel"), msg.pSender );
                    TCnsInfo tCnsInfo = *(TCnsInfo*)pItem->GetTag();
					if( tCnsInfo.m_emEpType == emTPEndpointH323MT )
					{
						m_pm->DoCase( _T("caseListSel323"), msg.pSender );
					}
					else
					{
						m_pm->DoCase( _T("caseListSel"), msg.pSender );
					}

                    if ( tCnsInfo.m_wEpID == m_tConfInfo.m_wSpeaker )
                    {
                        //发言人不可用
                        ICncCommonOp::EnableControl( false, m_pm, _T("ListBtnSetSpeaker"), (CControlUI*)msg.pSender );
                    }
                    else
                    {
                        ICncCommonOp::EnableControl( true, m_pm, _T("ListBtnSetSpeaker"), (CControlUI*)msg.pSender );
                    }
                    m_nSelIndex = nIndex;
                }
            }
        }		
	}
	return true;
}

bool CConfCtrlLogic::OnCheckConfCnsItem(TNotifyUI& msg)
{	
	//会议讨论中也调用了相同的列表项，用列表名进行判断 dyy 2015-3-27
	if (msg.pSender->GetParent()->GetParent()->GetName() != _T("ConfCnsList"))
	{
		return false;
	}

	//if (!ComInterface->IsLocalCnsChairMan())//不是主席不能控制
	//{
	//	return true;
	//}

	CControlUI *pParent = msg.pSender->GetParent();
	if ( CListContainerElementUI *pItem = dynamic_cast<CListContainerElementUI*>(pParent) )
	{
		TCnsInfo tCnsInfo = *(TCnsInfo*)pItem->GetTag();

		CCheckBoxUI *pCheckBox = (CCheckBoxUI*)msg.pSender;
		bool bCheck = pCheckBox->GetCheck();

		if ( bCheck )
		{
			if ( m_nSelIndex != -1 )
			{
				CControlUI *pLastSel = m_pConfCnsList->GetItemAt(m_nSelIndex);
				m_pm->DoCase( _T("caseListNoSel"), pLastSel );
				m_nSelIndex = -1;
			}

			if (tCnsInfo.m_bOnline)
			{
				pItem->SetBkImage( _T("res\\list\\item_sel.png") );
			}
			else
			{
				pItem->SetBkImage( _T("res\\list\\item_disabled.png") );
			}
			
			m_vctSelectList.push_back( tCnsInfo );
	
		}
		else
		{
			if (tCnsInfo.m_bOnline)
			{
				pItem->SetBkImage( _T("res\\list\\item_normal.png") );
			}
			else
			{
				pItem->SetBkImage( _T("res\\list\\item_disabled.png") );
			}

			vector<TCnsInfo>::iterator iter = m_vctSelectList.begin();
			while( iter != m_vctSelectList.end() )
			{					  
				if ( *iter == tCnsInfo )
				{
					m_vctSelectList.erase(iter);
					break;
				}		
				iter++;
			}
		}	
	}

	bool bIsEnable = false;
	if (m_vctSelectList.size() == 1 && m_vctSelectList.at(0).m_bOnline)//只选一个在线的时候 选看等按钮可用 其他个数不可用
	{
		bIsEnable = true;
	}

	if (!ComInterface->IsLocalCnsChairMan())//不是主席也支持选看按钮
	{
		ICncCommonOp::EnableControl(bIsEnable, m_pm, _T("BtnSelectPlay"));
		return true;
	}

	ICncCommonOp::EnableControl(bIsEnable, m_pm, _T("BtnSetSpeaker"));
	ICncCommonOp::EnableControl(bIsEnable, m_pm, _T("BtnSetDual"));
	ICncCommonOp::EnableControl(bIsEnable, m_pm, _T("BtnSelectPlay"));

	return true;
}

bool CConfCtrlLogic::OnBtnItemSetCam(TNotifyUI& msg)
{
	CControlUI *pParent = msg.pSender->GetParent();
	if ( const CListContainerElementUI *pContainer = dynamic_cast<const CListContainerElementUI*>(pParent) )
	{
		TCnsInfo tCnsInfo = *(TCnsInfo*)pContainer->GetTag();

		TConfEpID  tConfEpInfo ;
		tConfEpInfo.m_wConfID = m_tConfInfo.m_wConfID;
		tConfEpInfo.m_wEpID = tCnsInfo.m_wEpID;

		u16 wRe = NO_ERROR;
		wRe = ComInterface->SetFeccConfEpInfo( tConfEpInfo );

		if ( wRe != NO_ERROR )
		{
			CString str;
			str.Format(_T("会场远摇失败"));
			ShowMessageBox(str);
		} 
		else
		{
			ICncCommonOp::ShowControl( true, m_pm, _T("ConfroomCramerLayout") );
			ICncCommonOp::SetControlText(CA2T(tCnsInfo.m_achRoomName), m_pm, _T("LabConfName"));
			m_pm->DoCase(_T("caseMultyFeccCam"));
		}
	}

	return true;
}

bool CConfCtrlLogic::OnBtnItemSetDual(TNotifyUI& msg)
{
    CControlUI *pParent = msg.pSender->GetParent();
    if ( const CListContainerElementUI *pContainer = dynamic_cast<const CListContainerElementUI*>(pParent) )
    {
        TCnsInfo tCnsInfo = *(TCnsInfo*)pContainer->GetTag();

        TConfEpID  tConfEpInfo ;
        tConfEpInfo.m_wConfID = m_tConfInfo.m_wConfID;
        tConfEpInfo.m_wEpID = tCnsInfo.m_wEpID;

		u16 wRe = NO_ERROR;
		if (m_tConfInfo.m_wDual == tCnsInfo.m_wEpID)
		{
			wRe = ComInterface->SetDualCns( tConfEpInfo,FALSE );
		}
		else
		{
			wRe = ComInterface->SetDualCns( tConfEpInfo,TRUE );
		}

		if ( wRe != NO_ERROR )
		{
			CString str;
			str.Format(_T("会场双流设置失败"));
			ShowMessageBox(str);
		}
    }

	return true;
}

bool CConfCtrlLogic::OnBtnItemSetSpeaker(TNotifyUI& msg)
{
    CControlUI *pParent = msg.pSender->GetParent();
    if ( const CListContainerElementUI *pContainer = dynamic_cast<const CListContainerElementUI*>(pParent) )
    {
		m_pm->DoCase( _T("caseListNoSel"), pParent );
		m_nSelIndex = -1;

        TCnsInfo tCnsInfo = *(TCnsInfo*)pContainer->GetTag();
		if (m_tConfInfo.m_wSpeaker == tCnsInfo.m_wEpID)
		{
			return true;//已经是发言人不重复发送消息
		}

        TConfEpID  tConfEpInfo ;
        tConfEpInfo.m_wConfID = m_tConfInfo.m_wConfID;
        tConfEpInfo.m_wEpID = tCnsInfo.m_wEpID;

        u16 wRe = ComInterface->SetSpokeCns( tConfEpInfo );
    }
	return true;
}

bool CConfCtrlLogic::OnBtnItemSelectPlay(TNotifyUI& msg)
{
	CControlUI *pParent = msg.pSender->GetParent();
	if ( const CListContainerElementUI *pContainer = dynamic_cast<const CListContainerElementUI*>(pParent) )
	{
		TCnsInfo tCnsInfo = *(TCnsInfo*)pContainer->GetTag();

		TTPCnsInfo tlocalCnsInfo;
		ComInterface->GetLocalCnsInfo(tlocalCnsInfo);

		TCnsInfo *tCnsInfoLocal = m_tConfInfo.GetLocalCnsInfo( tlocalCnsInfo );
		if (tCnsInfoLocal == NULL)
		{
			return false;
		}

		if (tCnsInfoLocal->m_wEpID == tCnsInfo.m_wEpID)//不可以选看自己
		{
			ShowMessageBox(_T("会场选看设置失败：不可以选看本会场"));
			return false;
		}

		TTPSelViewReq tTPSelViewReq;
		tTPSelViewReq.m_emType = EmEpType_Ter;
		tTPSelViewReq.m_emUIType = EmUI_CNC;
		tTPSelViewReq.m_wConfID = m_tConfInfo.m_wConfID;
		tTPSelViewReq.m_wScreenIndx = TP_MAX_STREAMNUM;//会场选看
		tTPSelViewReq.m_wEpID = tCnsInfoLocal->m_wEpID;
		tTPSelViewReq.m_wDstID = tCnsInfo.m_wEpID;
		if ( tCnsInfo.m_wEpID == m_tConfInfo.m_wSelViewConfID )
		{
			tTPSelViewReq.m_bSel = false;
		}
		else
		{
			tTPSelViewReq.m_bSel = true;
		}

		u16 wRe = ComInterface->SetSelView( tTPSelViewReq);
		if ( wRe != NO_ERROR )
		{
			CString str;
			str.Format(_T("会场选看设置失败"));
			ShowMessageBox(str);
		}
	}

	return true;
}

bool CConfCtrlLogic::OnBtnItemSetQuiet(TNotifyUI& msg)
{
    CControlUI *pParent = msg.pSender->GetParent();
    if ( const CListContainerElementUI *pContainer = dynamic_cast<const CListContainerElementUI*>(pParent) )
    {
        TCnsInfo tCnsInfo = *(TCnsInfo*)pContainer->GetTag();

        TConfEpID  tConfEpInfo ;
        tConfEpInfo.m_wConfID = m_tConfInfo.m_wConfID;
        tConfEpInfo.m_wEpID = tCnsInfo.m_wEpID;

        if ( tCnsInfo.m_bQuiet )
        {
            ComInterface->SetQuietCns( tConfEpInfo, FALSE );
        }
        else
        {
            ComInterface->SetQuietCns( tConfEpInfo, TRUE );
        }
    }

	return true;
}

bool CConfCtrlLogic::OnBtnItemSetMute(TNotifyUI& msg)
{
    CControlUI *pParent = msg.pSender->GetParent();
    if ( const CListContainerElementUI *pContainer = dynamic_cast<const CListContainerElementUI*>(pParent) )
    {
        TCnsInfo tCnsInfo = *(TCnsInfo*)pContainer->GetTag();

        TConfEpID  tConfEpInfo ;
        tConfEpInfo.m_wConfID = m_tConfInfo.m_wConfID;
        tConfEpInfo.m_wEpID = tCnsInfo.m_wEpID;

        if ( tCnsInfo.m_bMute )
        {
            ComInterface->SetMuteCns( tConfEpInfo, FALSE );
        }
        else
        {
            ComInterface->SetMuteCns( tConfEpInfo, TRUE );
        }
    }
	return true;
}
bool CConfCtrlLogic::OnBtnItemHangUp(TNotifyUI& msg)
{
    CControlUI *pParent = msg.pSender->GetParent();
    if ( const CListContainerElementUI *pContainer = dynamic_cast<const CListContainerElementUI*>(pParent) )
    {
        TCnsInfo tCnsInfo = *(TCnsInfo*)pContainer->GetTag();

        TConfEpID  tConfEpInfo ;
        tConfEpInfo.m_wConfID = m_tConfInfo.m_wConfID;
        tConfEpInfo.m_wEpID = tCnsInfo.m_wEpID;

        //如果是主会场，则需要用户确认
        if ( tCnsInfo.m_wEpID == m_tConfInfo.GetChairCnsID()  )
        {
            UIDATAMGR->setLocalCnsState( emLocalCnsWillHungup );
            int nReslut = ShowMessageBox(  _T("挂断主席会场将结束会议，是否结束会议"), true );
            if ( IDOK == nReslut )
            {
                u16 wRe = NO_ERROR;
                if ( m_tConfInfo.m_emConfType == emCallType_Conf )
                {
                    wRe = ComInterface->HangupConf();
                }
                else
                {                 
                    wRe = ComInterface->HungupPtpConf();
                }
            }
        }
        else
        {
            TConfEpID  tConfEpInfo ;
            tConfEpInfo.m_wConfID = m_tConfInfo.m_wConfID;
            tConfEpInfo.m_wEpID = tCnsInfo.m_wEpID;

            u16 wRe = ComInterface->HangupCns( tConfEpInfo );
        }
    }

	return true;
}	


bool CConfCtrlLogic::OnComboShowEx(TNotifyUI& msg)
{
    int nSel = msg.wParam;

    if ( nSel == 0 )
    {
        m_emCnsShowState = emShowAll;
    }
    else if ( nSel == 1 )
    {
        m_emCnsShowState = emShowOnLine;
    }
	else if ( nSel == 2 )
	{
		m_emCnsShowState = emShowOffLine;      
	}
	else if ( nSel == 3 )
	{
		m_emCnsShowState = emShowSpeaker;      
	}
    UpdateCnsList();
    UpdateShowList();
    return true;
}


bool CConfCtrlLogic::OnSearchEditChange(TNotifyUI& msg)
{
    tstring strCaption = ICncCommonOp::GetControlText( m_pm, _T("ConfCtrlEdtSearch") );
    if ( strCaption.empty() )
    {
        m_bSearchEdit = FALSE;
        UpdateShowList();
        return false;
    }

    m_bSearchEdit = TRUE;
    CString strSearchName;
    strSearchName.Format( _T("%s"), strCaption.c_str() );

    m_vctSearchList.clear();

    vector<TCnsInfo> vctShowList;
    if ( m_tParentCns.m_wEpID != TP_INVALID_INDEX )
    {
        vctShowList = m_vctChildCnsList;
    }
    else
    {
        vctShowList.clear();
        for ( int i = 0; i < m_vctCnsList.size(); i++ )
        {
            if ( m_vctCnsList.at(i).m_wParentEpID == TP_INVALID_INDEX )
            {
                vctShowList.push_back( m_vctCnsList.at(i) );
            }
        }
    }

    for ( u16 i = 0; i < vctShowList.size(); i++ )
    {
        BOOL bMatchNum = FALSE;
        CString strItemName;
        TCnsInfo tInfo = vctShowList.at(i);
        
        strItemName = tInfo.m_achRoomName;

        BOOL bFind = FALSE;			
        bFind = UIDATAMGR->HZPYMatchList( strSearchName, strItemName );
        if ( bFind )
        {		
            m_vctSearchList.push_back( tInfo );
        }
    }

    if ( msg.lParam != 1 )//只更新数据时无需刷新
    {
        UpdateShowList();
    }  

    return true;
}

bool CConfCtrlLogic::OnConfStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	//获得会议状态，对会控列表进行限制，点对点会议，只有双流和画中画 dyy 2015-5-13 
	TCMSConf tConfInfo;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
	//根据会议状态设置全场静哑音显示状态
	EM_ShortcutType em = emShortcutQuiteAll;
	NOTIFY_MSG( UI_CNC_SET_SHORTCUT_NTY, em, bInConf );
	em = emShortcutMuteAll;
	NOTIFY_MSG( UI_CNC_SET_SHORTCUT_NTY, em, bInConf );

	if ( !bInConf )
	{
		m_tConfInfo.Clear();
		m_vctSelectList.clear();//结会清空 dyy 2015-6-30
        m_tParentCns.Clear();
        UpdateListPath();
        m_bSearchEdit = FALSE;
        ICncCommonOp::SetControlText( _T(""), m_pm, _T("ConfCtrlEdtSearch") );

		//会议结束隐藏掉会议控制界面 dyy 2015-5-13
		String strCurWnd = UIDATAMGR->GetCurShowWndName();
		if(WINDOW_MGR_PTR->IsWindowVisible(g_strConfCtrlDlg.c_str()) &&
		(strCurWnd == g_strConfCtrlDlg ||  strCurWnd ==  g_stcStrTvWallChildDlg ))
		{
			if ( strCurWnd == g_stcStrTvWallChildDlg )
			{
				NOTIFY_MSG( UI_CNC_HIDE_TVWALLCHILDDLG_NTY, NULL, NULL );
			}

			WINDOW_MGR_PTR->ShowWindow( g_strConfCtrlDlg.c_str(), false );
			WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowCnsManage"));
			UIDATAMGR->SetCurShowWndName( _T("") );
		}
		//关闭双流
		CCheckBoxUI* pCheckCnsDual = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckCnsDual"));
		if ( pCheckCnsDual )
		{
			pCheckCnsDual->SetCheckNoMsg(ComInterface->IsLocalCnsDual());
		}
		//关闭远摇
		TConfEpID  tConfEpInfo ;
		tConfEpInfo.Clear();
		ComInterface->SetFeccConfEpInfo( tConfEpInfo );
		ICncCommonOp::ShowControl( false, m_pm, _T("ConfroomCramerLayout") );
	}
	else
	{
		//点对点远摇界面
		m_pm->DoCase(_T("caseP2PFeccCam"));

		if (tConfInfo.m_emConfType == emCallType_P2P)//点对点会议
		{
			TTPCnsConfStatus tStatus = ComInterface->GetLocalCnsConfState();
			if (tStatus.m_emConfProtocal == emTpH323)
			{
				TConfEpID  tConfEpInfo ;
				tConfEpInfo.m_wConfID = 0;
				tConfEpInfo.m_wEpID = 0;

				u16 wRe = NO_ERROR;
				wRe = ComInterface->SetFeccConfEpInfo( tConfEpInfo );

				if ( wRe != NO_ERROR )
				{
					CString str;
					str.Format(_T("会场远摇失败"));
					ShowMessageBox(str);
					m_pm->DoCase(_T("caseP2PConfCtrl"));
				} 
				else
				{
					ICncCommonOp::ShowControl( true, m_pm, _T("ConfroomCramerLayout") );
					ICncCommonOp::SetControlText(CA2T(tConfInfo.m_achConfName), m_pm, _T("LabConfName"));
					m_pm->DoCase(_T("caseP2P323ConfCtrl"));
				}
			}
			else
			{
				m_pm->DoCase(_T("caseP2PConfCtrl"));
			}
			
			COptionUI *pMV = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("mixmotive") );
			COptionUI *pPip = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("pip") );
			COptionUI *pDual = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("confdual") );
			if (pMV && pMV->IsSelected() || pPip&&pPip->IsSelected() || pDual&&pDual->IsSelected())
			{
				return true;
			}

			if (pDual)
			{
				pDual->Selected(true);
			}
		}
		else
		{
			//多点远摇界面
			m_pm->DoCase(_T("caseMultyFeccCam"));

			if (ComInterface->IsLocalCnsChairMan())
			{
				m_pm->DoCase(_T("caseMultyConfChairCtrl"));
				m_pm->DoCase(_T("caseMultyIni"));
			}
			else
			{
				COptionUI *pVM = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("vidmix") );
				COptionUI *pPoll = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("confpoll") );
				COptionUI *pAU = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("audmix") );
				
				COptionUI *pRoll = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("confroll") );
				COptionUI *pConfMix = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("confMix") );
				COptionUI *pTVWall = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("tvwall") );

				if (pVM && pVM->IsSelected() || pPoll&&pPoll->IsSelected() || pAU&&pAU->IsSelected()
					||pRoll && pRoll->IsSelected() || pConfMix&&pConfMix->IsSelected() || pTVWall&&pTVWall->IsSelected())
				{
					COptionUI *pControl = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("confcns") );
					pControl->Selected(true);
				}

				m_pm->DoCase(_T("caseMultyConfCtrl"));
			}

			UpdateCnsList();
			UpdateShowList();
		}
	} 

	return true;
}

bool CConfCtrlLogic::OnRefreshCnsLstNotify(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	BOOL32 bInConf = ComInterface->IsInConf();
	if( bInConf )
	{
		UpdateCnsList(); 
        UpdateShowList();
	}

	return true;
}

bool CConfCtrlLogic::OnShortCutQuiteAll(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	if( m_vctCnsList.empty() )
	{
		ShowMessageBox(_T("没有任何会场"));
		return false;
	}

	TConfEpID  tConfEpInfo ;
	tConfEpInfo.m_wConfID = m_tConfInfo.m_wConfID;
	tConfEpInfo.m_wEpID = TP_ALLEP_INDEX;

	bool bIsAllQuite = ComInterface->IsAllQuite();
	u16 wRe = ComInterface->SetQuietCns( tConfEpInfo, !bIsAllQuite );

	return true;
}

bool CConfCtrlLogic::OnShortCutMuteAll(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	if( m_vctCnsList.empty() )
	{
		ShowMessageBox(_T("没有任何会场"));
		return false;
	}

	TConfEpID  tConfEpInfo ;
	tConfEpInfo.m_wConfID = m_tConfInfo.m_wConfID;
	tConfEpInfo.m_wEpID = TP_ALLEP_INDEX;

	bool bIsAllMute = ComInterface->IsAllMute();
	u16 wRe = ComInterface->SetMuteCns( tConfEpInfo, !bIsAllMute );
	
	return true;
}

void CConfCtrlLogic::UpdateCnsList()
{
	TCMSConf tConfInfoTemp;
	BOOL32 bInConf =  ComInterface->IsInConf( &tConfInfoTemp );
	if ( !bInConf )
	{  
		//还原显示选项
		//InitLst();
		m_tConfInfo.Clear();
		PrtMsg(0,emEventTypeCmsWindow,"[CConfCnsLstLogic::UpdateCnsLst]: 本地cns不在会议中，不刷新cns列表，隐藏cns列表界面");
		return;
	}

    m_tConfInfo = tConfInfoTemp;
	m_vctCnsList.clear();

	//如果在级联列表中 更新级联列表中的状态信息 2016-11-15 dyy
	bool bIsIn = false;//是否当前在级联列表中
	if ( m_tParentCns.m_wEpID != TP_INVALID_INDEX )
	{
		bIsIn = true;
		m_vctChildCnsList.clear();
	}

    for ( int i = 0; i< tConfInfoTemp.m_vctCnsList.size(); i++ )
    {
        m_vctCnsList.push_back( tConfInfoTemp.m_vctCnsList.at(i) );
		if (bIsIn)
		{
			if ( tConfInfoTemp.m_vctCnsList.at(i).m_wParentEpID == m_tParentCns.m_wEpID )
			{
				m_vctChildCnsList.push_back( m_vctCnsList.at(i) );
			}
		}
    }

	//如果有选中项，更新选中项内容
	if (!m_vctSelectList.empty())
	{
		for (int i=0; i<m_vctSelectList.size();i++)
		{
			for(int j=0; j<tConfInfoTemp.m_vctCnsList.size();j++)
			{
				if (tConfInfoTemp.m_vctCnsList.at(j).m_wEpID == m_vctSelectList.at(i).m_wEpID)
				{
					m_vctSelectList.at(i) = tConfInfoTemp.m_vctCnsList.at(j);
				}
			}
		}
	}

    if ( m_bSearchEdit )
    {
        TNotifyUI msg; 
        msg.lParam = 1; //只更新m_vctSearchList数据
        OnSearchEditChange(msg);
    }
}


void CConfCtrlLogic::GetOptnShowList( vector<TCnsInfo>& vctCurrentList )
{
    if ( m_emCnsShowState == emShowAll )
    {
        return;
    }
    vector<TCnsInfo> vctList = vctCurrentList;
    vctCurrentList.clear();

    switch( m_emCnsShowState )
    {
    case emShowOnLine:
        {
            for ( int i = 0; i< vctList.size(); i++ )
            {
                if ( vctList.at(i).m_bOnline )
                {
                    vctCurrentList.push_back( vctList.at(i) );
                }
            } 
        }
        break;
    case emShowQuiet:
        {
            for ( int i = 0; i< vctList.size(); i++ )
            {
                if ( vctList.at(i).m_bQuiet && vctList.at(i).m_bOnline )
                {
                    vctCurrentList.push_back( vctList.at(i) );
                }
            }
        }
        break; 
    case emShowMute:
        {
            for ( int i = 0; i< vctList.size(); i++ )
            {
                if (vctList.at(i).m_bMute && vctList.at(i).m_bOnline )
                {
                    vctCurrentList.push_back( vctList.at(i) );
                }
            }
        }
        break;
    case emShowOffLine:
        {
            for ( int i = 0; i< vctList.size(); i++ )
            {
                if ( !vctList.at(i).m_bOnline )
                {
                    vctCurrentList.push_back( vctList.at(i) );
                }
            } 
        }
        break;
    case emShowSpeaker:
        {
            TCMSConf tConfInfoTemp;
            BOOL32 bInConf =  ComInterface->IsInConf( &tConfInfoTemp );
            if ( bInConf )
            {  
                for ( int i = 0; i< vctList.size(); i++ )
                {
                    if ( vctList.at(i).m_wEpID == tConfInfoTemp.m_wSpeaker )
                    {
                        vctCurrentList.push_back( vctList.at(i) );
                    }
                } 
            }
        }
        break;
    default:
        break;   
    } 
}


void CConfCtrlLogic::UpdateShowList()
{
    if ( m_pConfCnsList == NULL )
    {
		return;
	}

    if( m_bSearchEdit )
    {
        m_vctShowList = m_vctSearchList;
    }
    else
    {
        if ( m_tParentCns.m_wEpID != TP_INVALID_INDEX )
        {
            m_vctShowList = m_vctChildCnsList;
        }
        else
        {
            m_vctShowList.clear();
            for ( int i = 0; i < m_vctCnsList.size(); i++ )
            {
                if ( m_vctCnsList.at(i).m_wParentEpID == TP_INVALID_INDEX )
                {
                    m_vctShowList.push_back( m_vctCnsList.at(i) );
                }
            }
        }        
    }

	//获得远摇会场信息
	TConfEpID tFeccConfEpID;
	ComInterface->GetFeccConfEpInfo(tFeccConfEpID);

    //获得条件筛选后的条目
    GetOptnShowList( m_vctShowList );

    sort( m_vctShowList.begin(), m_vctShowList.end(), CUIDataMgr::CnsInfoCompare );

    m_pConfCnsList->RemoveAll();

    for ( int i = 0; i < m_vctShowList.size(); i++ )
    {
        CListContainerElementUI *pListContainer = 
            (CListContainerElementUI*)CONTROLFACTORY()->GetControl( strConfCnsItem.c_str() );

        TCnsInfo tCnsInfo = m_vctShowList.at(i);

		if( strcmp( tCnsInfo.m_achRoomName, "" ) == 0 )
		{
			if ( strcmp( tCnsInfo.m_achRoomE164, "" ) == 0 )
			{
				in_addr tAddr;
				tAddr.S_un.S_addr = tCnsInfo.m_dwRoomIp;
				String strIp = CA2T(inet_ntoa(tAddr));
				if ( strIp == _T("0.0.0.0") )
				{
					strIp = _T("");
				}
				ICncCommonOp::SetControlText( strIp.c_str(), m_pm, _T("ConfCnsName"), pListContainer );
			}
			else
			{
				ICncCommonOp::SetControlText( CA2T(tCnsInfo.m_achRoomE164), m_pm, _T("ConfCnsName"), pListContainer );
			}
		}
		else
		{
			ICncCommonOp::SetControlText( CA2T(tCnsInfo.m_achRoomName), m_pm, _T("ConfCnsName"), pListContainer );
		}

		//选中项不清空 不管在线不在线
		vector<TCnsInfo>::iterator itfind = find( m_vctSelectList.begin(), m_vctSelectList.end(), tCnsInfo );
		if ( itfind != m_vctSelectList.end() )
		{
			itfind->m_bOnline = tCnsInfo.m_bOnline;//更新在线状态
			CCheckBoxUI *pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("BtnConfCnsSel"), pListContainer );
			if ( pCheckBox != NULL )
			{
				pCheckBox->SetCheck(true);
			}
		}

        if ( tCnsInfo.m_emEpType == emTPEndpointTypeUMS || tCnsInfo.m_emEpType == emTPEndpointH323MCU )
        {            
            m_pm->DoCase( _T("caseParentItem"), pListContainer );
            if ( !tCnsInfo.m_bOnline )
            {
                pListContainer->SetBkImage( _T("res\\list\\item_disabled.png") );
            }
        }
        else
        {
			//监控图标
			if (tCnsInfo.m_emEpType == emTPEndpointH323G400)
			{
				m_pm->DoCase( _T("caseMonitor"), pListContainer ); 
			}
			else if (tCnsInfo.m_emEpType == emTPEndpointTypeVRS)
			{
				m_pm->DoCase( _T("caseStudio"), pListContainer ); 
			}
			else if (tCnsInfo.m_emEpType != emTPEndpointTypeCNS)
			{
				m_pm->DoCase( _T("caseOrdinary"), pListContainer ); 
			}
			
			if (tCnsInfo.m_bOnline)//在线才显示状态图标
		    {
			    if ( tCnsInfo.m_wEpID == m_tConfInfo.m_wSpeaker )
			    {
				    ICncCommonOp::ShowControl( true, m_pm, _T("imgSpeaker"), pListContainer );
			    }

			    if ( tCnsInfo.m_bQuiet )
			    {
				    ICncCommonOp::ShowControl( true, m_pm, _T("imgQuiet"), pListContainer );
				    m_pm->DoCase(_T("caseQuiet"),pListContainer);
			    }
			    else
			    {
				    m_pm->DoCase(_T("caseSetQuiet"),pListContainer);
			    }

			    if ( tCnsInfo.m_bMute )
			    {
				    ICncCommonOp::ShowControl( true, m_pm, _T("imgMute"), pListContainer );
				    m_pm->DoCase(_T("caseMute"),pListContainer);
			    }
			    else
			    {
				    m_pm->DoCase(_T("caseSetMute"),pListContainer);
			    }

			    //选中项不清空 在线背景会是选中状态 不在线无选中状态
			    if ( itfind != m_vctSelectList.end() )
			    {
				    pListContainer->SetBkImage( _T("res\\list\\item_sel.png") );
			    }

			    if ( m_tConfInfo.m_wDual == tCnsInfo.m_wEpID )
			    {
				    m_pm->DoCase(_T("caseCancelDual"),pListContainer);
			    }
			    else
			    {
				    m_pm->DoCase(_T("caseDual"),pListContainer);
			    }

			    if ( tCnsInfo.m_wEpID == m_tConfInfo.m_wSelViewConfID )
			    {
				    m_pm->DoCase(_T("caseCancelSelectPlay"),pListContainer);
			    }
			    else
			    {
				    m_pm->DoCase(_T("caseSelectPlay"),pListContainer);
			    }
		    }
		    else//不在线
		    {
			    m_pm->DoCase( _T("caseListDisabled"), pListContainer ); 
				if ( tFeccConfEpID.m_wEpID == tCnsInfo.m_wEpID)
				{
					tFeccConfEpID.Clear();
					ComInterface->SetFeccConfEpInfo(tFeccConfEpID);
				}
		    }
        }

		if ( tFeccConfEpID.m_wEpID == TP_INVALID_INDEX )
		{
			ICncCommonOp::ShowControl( false, m_pm, _T("ConfroomCramerLayout") );
			ICncCommonOp::SetControlText(_T(""), m_pm, _T("LabConfName"));
		}

		pListContainer->SetTag( (UINT_PTR)&m_vctShowList.at(i) );
        m_pConfCnsList->Add(pListContainer);
    }

	m_nSelIndex = -1;
}


void CConfCtrlLogic::OnDualWaitOverTime()
{
	ICncCommonOp::EnableControl(true, m_pm, _T("CheckCnsDual"));
}

bool CConfCtrlLogic::OnSetMuteCnsRsp( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	u16 wEpId = (u16)wParam;
	UpdateCnsList();
	UpdateCnsItem( wEpId );
	return true;
}

bool CConfCtrlLogic::OnSetQuietCnsRsp( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	u16 wEpId = (u16)wParam;
	UpdateCnsList(); 
	UpdateCnsItem( wEpId );
	return true;
}

void CConfCtrlLogic::UpdateCnsItem( u16 wEpId )
{
	TCnsInfo* pCnsInfo = m_tConfInfo.GetCnsInfoByID( wEpId );
	if ( pCnsInfo == NULL )
	{
		return;
	}

	for( u16 i = 0; i < m_vctShowList.size(); i++ )
	{
		TCnsInfo tCnsInfo = m_vctShowList.at(i);
        if ( tCnsInfo.m_wEpID == wEpId )
        {
            if ( i >= m_pConfCnsList->GetCount() )
            {
                return;
            }

            CControlUI *pItem = m_pConfCnsList->GetItemAt(i);

            m_vctShowList.at(i) = *pCnsInfo;
			pItem->SetTag( (UINT_PTR)&m_vctShowList.at(i));

			if ( tCnsInfo.m_wEpID == m_tConfInfo.m_wSpeaker )
			{
				ICncCommonOp::ShowControl( true, m_pm, _T("imgSpeaker"), pItem );
			}
			else
			{
				ICncCommonOp::ShowControl( false, m_pm, _T("imgSpeaker"), pItem );
			}

            if ( pCnsInfo->m_bQuiet )
            {
                ICncCommonOp::ShowControl( true, m_pm, _T("imgQuiet"), pItem );
				m_pm->DoCase(_T("caseQuiet"),pItem);
            }
			else
			{
				ICncCommonOp::ShowControl( false, m_pm, _T("imgQuiet"), pItem );
				m_pm->DoCase(_T("caseSetQuiet"),pItem);
			}

            if ( pCnsInfo->m_bMute )
            {
                ICncCommonOp::ShowControl( true, m_pm, _T("imgMute"), pItem );
				m_pm->DoCase(_T("caseMute"),pItem);
            }
			else
			{
				ICncCommonOp::ShowControl( false, m_pm, _T("imgMute"), pItem );
				m_pm->DoCase(_T("caseSetMute"),pItem);
			}

			if ( m_tConfInfo.m_wDual == pCnsInfo->m_wEpID )
			{
				m_pm->DoCase(_T("caseCancelDual"),pItem);
			}
			else
			{
				m_pm->DoCase(_T("caseDual"),pItem);
			}

			if ( pCnsInfo->m_wEpID == m_tConfInfo.m_wSelViewConfID )
			{
				m_pm->DoCase(_T("caseCancelSelectPlay"),pItem);
			}
			else
			{
				m_pm->DoCase(_T("caseSelectPlay"),pItem);
			}

            break;
        }
    }
}



bool CConfCtrlLogic::OnSetTabShow( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	EM_ShortcutType em = (EM_ShortcutType)wParam;
	if (!m_bIsIni)
	{
		m_nEmShort = em;
	}
	else
	{
		SetShortCutShow(em);
	}

	return true;
}

void CConfCtrlLogic::SetShortCutShow(EM_ShortcutType em)
{
	if (ComInterface->IsLocalCnsChairMan())
	{
		if (em == emShortcutVoiceAct || em == emShortcutPIP || em == emShortcutTVWall)
		{
			m_pm->DoCase(_T("caseMultyExta"));
		}
		else if (em == emShortcutCofRoll || em == emShortcutCofMix)
		{
			m_pm->DoCase(_T("caseMultyIni"));
		}
	}

	if ( em == emShortcutCofDiscuss )
	{
		ICncCommonOp::OptionSelect(true,m_pm,_T("audmix"));
	}
	else if ( em == emShortcutCofPoll )
	{
		ICncCommonOp::OptionSelect(true,m_pm,_T("confpoll"));
	}
	else if ( em == emShortcutPIP )
	{
		ICncCommonOp::OptionSelect(true,m_pm,_T("pip"));
	}
	else if ( em == emShortcutDulDisplay )
	{
		ICncCommonOp::OptionSelect(true,m_pm,_T("confdual"));
	}
	else if ( em == emShortcutVoiceAct )
	{
		ICncCommonOp::OptionSelect(true,m_pm,_T("mixmotive"));
	}
	else if ( em == emShortcutPicSynthesis )
	{
		ICncCommonOp::OptionSelect(true,m_pm,_T("vidmix"));
	}
	else if ( em == emShortcutCofRoll )
	{
		ICncCommonOp::OptionSelect(true,m_pm,_T("confroll"));
	}
	else if ( em == emShortcutCofMix )
	{
		ICncCommonOp::OptionSelect(true,m_pm,_T("confMix"));
	}
	else if ( em == emShortcutTVWall )
	{
		ICncCommonOp::OptionSelect(true,m_pm,_T("tvwall"));
	}
}

bool CConfCtrlLogic::OnSetShortCheck( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	EM_ShortcutType em = (EM_ShortcutType)wParam;

	if ( em == emShortcutCofDiscuss )
	{
		CCheckBoxUI *pControl = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckConfDiscussShortCut") );
		if (pControl)
		{
			pControl->SetCheckNoMsg(true);
		}
	}
	else if ( em == emShortcutCofPoll )
	{
		CCheckBoxUI *pControl = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckConfPollShortCut") );
		if (pControl)
		{
			pControl->SetCheckNoMsg(true);
		}
	}
	else if ( em == emShortcutPIP )
	{
		CCheckBoxUI *pControl = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckPIPShortCut") );
		if (pControl)
		{
			pControl->SetCheckNoMsg(true);
		}
	}
	else if ( em == emShortcutDulDisplay )
	{
		CCheckBoxUI *pControl = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckDualShotCut") );
		if (pControl)
		{
			pControl->SetCheckNoMsg(true);
		}
	}
	else if ( em == emShortcutVoiceAct )
	{
		CCheckBoxUI *pControl = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckVSShortCut") );
		if (pControl)
		{
			pControl->SetCheckNoMsg(true);
		}
	}
	else if ( em == emShortcutPicSynthesis )
	{
		CCheckBoxUI *pControl = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckVideoMixShortCut") );
		if (pControl)
		{
			pControl->SetCheckNoMsg(true);
		}
	}
	else if ( em == emShortcutCofMix )
	{
		CCheckBoxUI *pControl = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckConfMixShortCut") );
		if (pControl)
		{
			pControl->SetCheckNoMsg(true);
		}
	}
	else if ( em == emShortcutCofRoll )
	{
		CCheckBoxUI *pControl = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckConfrollShortCut") );
		if (pControl)
		{
			pControl->SetCheckNoMsg(true);
		}
	}
    else if ( em == emShortcutTVWall )
    {
        CCheckBoxUI *pControl = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckTvWallShot") );
        if (pControl)
        {
            pControl->SetCheckNoMsg(true);
        }
    }

	return true;
}

bool CConfCtrlLogic::OnCheckPTPVoiceArouse( TNotifyUI& msg )
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

	BOOL bIs = ComInterface->IsLocalPTPVoiceArouse();
	if (bIs == bIsSet)
	{
		return true;
	}

	TCMSConf tConf;
	BOOL32 bInConf = ComInterface->IsInConf( &tConf );

	if ( bInConf )
	{
		u16 wRe =  ComInterface->SetCnAuxMix( bIsSet );
		if ( wRe != NO_ERROR )
		{
			ShowMessageBox(_T("开启失败"));
			pCheckBox->SetCheckNoMsg(false);
		}
	}
	else
	{
		ShowMessageBox(_T("不在会议中，不能开启"));
		pCheckBox->SetCheckNoMsg(false);
	}

	return true;
}

bool CConfCtrlLogic::OnCnAuxInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bIsMix = wParam;
	BOOL bIsSuccess = lParam;
	if (!bIsSuccess)
	{
		if (bIsMix)
		{
			ShowPopMsg(_T("开启语音激励失败"));
		}
		else
		{
			ShowPopMsg(_T("关闭语音激励失败"));
		}
	}

	CCheckBoxUI* pCheck = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckVoiceArouse"));
	if (pCheck)
	{
		pCheck->SetCheckNoMsg(ComInterface->IsLocalPTPVoiceArouse());
	}

	return true;
}

bool CConfCtrlLogic::OnCheckVSShortCut( TNotifyUI& msg )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	bool bIsSet = false;
	if ( pCheckBox->IsSelected() )
	{
		bIsSet = true;
	}

	EM_ShortcutType em = emShortcutVoiceAct;
	NOTIFY_MSG( UI_CNC_SET_SHORTCUT_NTY, em, bIsSet );
	return true;
}

bool CConfCtrlLogic::OnCheckLocalCnsDual( TNotifyUI& msg )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	bool bIsSet = false;
	if ( pCheckBox->IsSelected() )
	{
		bIsSet = true;
	}

	BOOL bDual = ComInterface->IsLocalCnsDual();
	if ( bDual != bIsSet )
	{
		u16 wRet = ComInterface->StartDual( bIsSet );
		if (NO_ERROR != wRet)
		{
			ShowPopMsg(_T("双流消息发送失败"));
		}
		else
		{
			//添加保护，一秒之内不能再操作双流
			ICncCommonOp::EnableControl(false, m_pm, _T("CheckCnsDual"));
			g_nDualWaiting = SetTimer( NULL, 0, 1000, CBDualWaitingFun );
		}
	}


	return true;
}

bool CConfCtrlLogic::OnCheckDualShotCut( TNotifyUI& msg )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	bool bIsSet = false;
	if ( pCheckBox->IsSelected() )
	{
		bIsSet = true;
	}

	EM_ShortcutType em = emShortcutDulDisplay;
	NOTIFY_MSG( UI_CNC_SET_SHORTCUT_NTY, em, bIsSet );
	return true;
}

bool CConfCtrlLogic::OnCheckPIP( TNotifyUI& msg )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	bool bIsSet = false;
	if ( pCheckBox->IsSelected() )
	{
		bIsSet = true;
	}

	BOOL bPIP = ComInterface->IsViewLocalPIP();

	if ( bPIP != (BOOL)bIsSet )
	{
		ComInterface->ViewLocalPIPCmd( 1, bIsSet );
	}

	return true;
}

bool CConfCtrlLogic::OnCheckPIPShortCut( TNotifyUI& msg )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	bool bIsSet = false;
	if ( pCheckBox->IsSelected() )
	{
		bIsSet = true;
	}

	EM_ShortcutType em = emShortcutPIP;
	NOTIFY_MSG( UI_CNC_SET_SHORTCUT_NTY, em, bIsSet );
	return true;
}

// bool CConfCtrlLogic::OnVoiceArouseInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
// {
// 	int OprReslt = (int)lParam; 
// 	if (OprReslt == TP_RET_ERROR)
// 	{
// 		CCheckBoxUI* pCheckVac = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckAudioExcitation"));
// 		if ( pCheckVac )
// 		{
// 			bool bSet = pCheckVac->GetCheck();
// 			m_bIsVaInd = true;
// 			pCheckVac->SetCheck(!bSet);
// 		}
// 	}
// 
// 	return true;
// }

bool CConfCtrlLogic::OnPIPInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	u8 byScrnID = (u8)wParam; 
	EmTPViewLocalResult emRe = (EmTPViewLocalResult)lParam;

	CString strErr = _T("");
	if ( emRe != emViewLocalSucceed )
	{  
		CString strTemp;
		switch ( emRe )
		{
		case  emViewLocalFailIllegalPos:
			strTemp = _T("屏号不是1");
			break;
		case  emViewLocalFailOffline:
			strTemp = _T("会场掉线");
			break;
		default:
			strTemp = _T("未知原因");
			break; 
		}

		BOOL bPIP = ComInterface->IsViewLocalPIP();
		if ( bPIP )
		{
			strErr = _T("关闭画中画失败：") + strTemp;
		}
		else
		{
			strErr = _T("开启画中画失败：") + strTemp;
		}

		ShowPopMsg( strErr );
	}

	CCheckBoxUI* pCheckPIP = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckPIP"));
	if ( pCheckPIP && pCheckPIP->GetCheck() != ComInterface->IsViewLocalPIP())
	{
		pCheckPIP->SetCheckNoMsg(ComInterface->IsViewLocalPIP());
	}
	return S_OK;
}

bool CConfCtrlLogic::OnPIPNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	u8 byScrnID = (u8)wParam; 
	BOOL bLocalPIP = (BOOL)lParam;

	CCheckBoxUI* pCheckPIP = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckPIP"));
	if ( pCheckPIP&& pCheckPIP->GetCheck() != ComInterface->IsViewLocalPIP())
	{
		pCheckPIP->SetCheckNoMsg(bLocalPIP);
	}
	return S_OK;
}

bool CConfCtrlLogic::OnCnsDualRsp( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bStart = (BOOL)wParam; //开启还是关闭操作
	EmTPDualReason emRe = (EmTPDualReason)lParam;

	CString strErr = _T("");
	if ( emRe != emTpDualAccept )
	{  
		CString strTemp = _T("");
		switch ( emRe )
		{
		case emTpDualBusy:
			strTemp = _T("双流源忙");
			break;
		case emTpDualPreemptive:
			strTemp = _T("未知原因");
			break;
		case emTpDualPeerReject:
			strTemp = _T("对端拒绝");
			break;
		case emTpDualPeerStop:
			strTemp = _T("对端停止演示");
			break;
		case emTpDualNoVideo:
			strTemp = _T("无视频源");
			break;
		case emTpDualLocalStop:
			strTemp = _T("本地停止演示");
			break;
		case emTpDualSndFail:
			strTemp = _T("发送双流失败");
			break;
		case emTpDualInit:
			strTemp = _T("双流初始化中，请稍后再试");
			break;
		case emTpDualBitrateIs0:
			strTemp = _T("演示开启失败：码率为0");
			break;
		default:
			strTemp = _T("未知原因");
			break; 
		}

		if ( bStart )
		{
			strErr = _T("开启演示失败：") + strTemp;
		}
		else
		{
			strErr = _T("关闭演示失败：") + strTemp;
		}

		if (!(!bStart && (emRe == emTpDualPeerStop || emRe == emTpDualLocalStop))) //关闭并且本端或对端停止演示，不提示 nlf确认
		{
			ShowPopMsg( strErr );

			//失败了 进行重置
			CCheckBoxUI* pCheckCnsDual = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckCnsDual"));
			if ( pCheckCnsDual )
			{
				pCheckCnsDual->SetCheckNoMsg(ComInterface->IsLocalCnsDual());
			}
		}
	}
	else
	{
		//NOTIFY_MSG( WM_CMS_SHOWVIDEO, 1 , 0 );
		ShowPopMsg( _T("开启演示成功"));
	}

// 	if (g_nDualWaiting != 0)
// 	{
// 		::KillTimer( NULL, g_nDualWaiting );
// 		g_nDualWaiting = 0;
// 		OnDualWaitOverTime();
// 	}
	return NO_ERROR;
}


bool CConfCtrlLogic::OnDualOffLineNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	ShowPopMsg( _T("双流源掉线"));	
	CCheckBoxUI* pCheckCnsDual = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckCnsDual"));
	if ( pCheckCnsDual )
	{
		pCheckCnsDual->SetCheckNoMsg(ComInterface->IsLocalCnsDual());
	}
	return NO_ERROR;
}

bool CConfCtrlLogic::OnDualRcvInterruptNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	EmTPChannelReason reason = (EmTPChannelReason)wParam;
	CString str = _T("");
	switch( reason )
	{
	case emTPChannelReasonBegin:
		str = _T("");
		break;
	case emTPChannelDisconnectNormal:
		str = _T("通道异常断开");
		break;
	case emTPDualOffLine:
		str = _T("双流源掉线");
		break;
	case emTPForceStop:
		str = _T("双流源被抢断");
		break;
	default:
		str = _T("未知原因");
	}

	ShowPopMsg( _T("接收双流终止:") + str );	
	CCheckBoxUI* pCheckCnsDual = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckCnsDual"));
	if ( pCheckCnsDual )
	{
		pCheckCnsDual->SetCheckNoMsg(ComInterface->IsLocalCnsDual());
	}

return NO_ERROR;
}

bool CConfCtrlLogic::OnRecvDualNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL32 bDual = (BOOL32)wParam;
	if ( bDual )
	{
		//TPad版cnc主窗不可见时不显示 dyy 2013年8月2日
		if ( !UIDATAMGR->IsPcVersion() )
		{
			if ( !WINDOW_MGR_PTR->IsWindowVisible(g_stcStrMainFrameDlg.c_str()) ) 			
			{
				return S_OK;
			}
		}

		//NOTIFY_MSG( WM_CMS_SHOWVIDEO, 1 , 0 );
	}
	else
	{
		//NOTIFY_MSG( WM_CMS_HIDE_VEDIO, 0 , 0 );
	}

	return S_OK;
}

bool CConfCtrlLogic::OnLetterIndex( TNotifyUI& msg )
{
	int nLetterIndex = (int)msg.wParam;
	CTouchListUI* pTouch = (CTouchListUI*)ICncCommonOp::FindControl(m_pm, _T("ConfCnsList"));
	if (!pTouch)
	{
		return false;
	}

	if (nLetterIndex == 0)
	{
		pTouch->ScrollToIndexLetter(0);
		return true;
	}

	CString strIndex;
	nLetterIndex = 'A' + nLetterIndex -1;
	strIndex.Format( _T("%c"), (char)nLetterIndex );
	int nYOffset = 0;
	int nItemCount = m_vctShowList.size();

	//解决条目过多时，点击字母会卡的问题 ，使用二分法
	int swLowIndex = 0;
	int swHighIndex = nItemCount;
	int swMidIndex = 0;   //置当前查找区间上、下界的初值 

	while( swLowIndex < swHighIndex )
	{   
		int nMidIndex = swMidIndex;
		//当前查找区间R[low..high]非空 
		swMidIndex =( swLowIndex + swHighIndex )/2; 
		if ( nMidIndex == swMidIndex )
		{
			break;
		}

		CString strLetter = _T("");
		UIDATAMGR->GetFirstLetter(m_vctShowList.at(swMidIndex).m_achRoomName, strLetter ); 

		int nRe = strIndex.Compare( strLetter );
		if(  nRe == 0 )  
		{        
			break;   
		} 
		else if ( nRe < 0 )
		{   
			swHighIndex = swMidIndex;  //当前查找区间R[low..mid]  
		}
		else
		{   
			swLowIndex = swMidIndex + 1;//当前查找区间R[mid..heith] 
		}						 

	} 

	//swLowIndex与swHighIndex相等时，跟swMidIndex比较
	if ( swLowIndex == swHighIndex )
	{
		if ( swMidIndex < swHighIndex )
		{
			swHighIndex = swMidIndex;
		}
		else
		{
			swLowIndex = swMidIndex;
		}
	}

	//取swLowIndex和swHighIndex中第一个比strIndex大的返回
	if ( swLowIndex > swHighIndex )
	{
		CString strLetter = _T("");
		UIDATAMGR->GetFirstLetter( m_vctShowList.at(swMidIndex).m_achRoomName, strLetter ); 

		int nRe = strIndex.Compare( strLetter );
		if( nRe > 0 )		 
		{
			swMidIndex = swLowIndex;
		}
		else
		{
			swMidIndex = swHighIndex;
		}

	}

	pTouch->ScrollToIndexLetter(swMidIndex);

	return true;
}

bool CConfCtrlLogic::OnSpeakerNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
// 	u16	wEpID = (u16)lParam;
// 	int wOldSpeaker = m_tConfInfo.m_wSpeaker;
// 	UpdateCnsList();
// 	int wNewSpeaker = m_tConfInfo.m_wSpeaker;
// 	if (wOldSpeaker != wNewSpeaker)
// 	{
// 		UpdateCnsItem( wOldSpeaker );//更新之前的选看项
// 	}	
// 	
// 	UpdateCnsItem( wNewSpeaker );//更新目前的选看项
	UpdateCnsList();
	UpdateShowList();
	return true;
}

bool CConfCtrlLogic::OnSpeakerInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	//响应nty
// 	u16	wEpID = (u16)wParam;
// 	EmTpApplySpeakerRet emRe = (EmTpApplySpeakerRet)lParam;
// 	if (emRe == TP_ApplySpeaker_Success)
// 	{
// 		UpdateCnsList();
// 		UpdateCnsItem( wEpID );
// 	}

	return true;
}

bool CConfCtrlLogic::OnItemDualInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	u16	wEpID = (u16)wParam;
	EmTPDualReason emRe = (EmTPDualReason)lParam;
	if (emRe != TP_ApplySpeaker_Success)
	{
		CString strErr = _T("会场双流操作失败");
		switch(emRe)
		{
		case emTpDualBusy:
			{
				strErr = _T("会场双流操作失败：双流忙");
			}
			break;
		case emTpDualPreemptive:
			{
				strErr = _T("会场双流操作失败：");
			}
			break;
		case emTpDualPeerReject:
			{
				strErr = _T("会场双流操作失败：对端拒绝");
			}
			break;
		case emTpDualPeerStop:
			{
				strErr = _T("会场双流操作失败：对端停止");
			}
			break;
		case emTpDualNoVideo:
			{
				strErr = _T("会场双流操作失败：没有视频源");
			}
			break;
		case emTpDualLocalStop:
			{
				strErr = _T("会场双流操作失败：双流停止");
			}
			break;
		case emTpDualSndFail:
			{
				strErr = _T("会场双流操作失败：发送双流失败");
			}
			break;
		case emTpDualInit:
			{
				strErr = _T("会场双流操作失败：双流初始化中");
			}
			break;
		case emTpDualBitrateIs0:
			{
				strErr = _T("演示开启失败：码率为0");
			}
			break;
		}

		ShowPopMsg(strErr);
	}

	return true;
}

bool CConfCtrlLogic::OnItemDualNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{	
// 	u16	wConfID = (u16)wParam;
// 	u16	wEpID = (u16)lParam;
// 
// 	//if (wConfID == m_tConfInfo.m_wConfID) 不一样可以么
// 	{
// 		int wOldDual = m_tConfInfo.m_wDual;
// 		UpdateCnsList();
// 		int wNewDual = m_tConfInfo.m_wDual;
// 		if (wOldDual != wNewDual)
// 		{
// 			UpdateCnsItem( wOldDual );//更新之前的双流项
// 		}	
// 
// 		UpdateCnsItem( wNewDual );//更新目前的双流项
// 	}
	UpdateCnsList();
	UpdateShowList();
	return true;
}

bool CConfCtrlLogic::OnItemSelViewNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{	
	TTPSelViewNtfy tTPSelViewNtfy = ComInterface->GetSelWatchStatus();	

	if (tTPSelViewNtfy.m_atSelView[0].m_wScreenIndx == TP_MAX_STREAMNUM)//会场选看
	{
// 		int wOldSV = m_tConfInfo.m_wSelViewConfID;
// 		UpdateCnsList();
// 		int wNewSV = m_tConfInfo.m_wSelViewConfID;
// 		if (wOldSV != wNewSV)
// 		{
// 			UpdateCnsItem( wOldSV );//更新之前的选看项
// 		}	
// 
// 		UpdateCnsItem( wNewSV );//更新目前的选看项
		UpdateCnsList();
		UpdateShowList();
	}

	return true;
}

bool CConfCtrlLogic::OnBtnItemCall( TNotifyUI& msg )
{
	CControlUI *pParent = msg.pSender->GetParent();
	if ( CListContainerElementUI *pItem = dynamic_cast<CListContainerElementUI*>(pParent) )
	{
		TCnsInfo tCnsInfo = *(TCnsInfo*)pItem->GetTag();

		if ( !tCnsInfo.m_bOnline )
		{   
			TConfEpID tEp;
			tEp.m_wConfID = m_tConfInfo.m_wConfID;
			tEp.m_wEpID = tCnsInfo.m_wEpID;
			u16 wRe =  ComInterface->CallConfCns(tEp);  
			if (wRe != NO_ERROR)
			{
				ShowMessageBox(_T("会场呼叫失败"));
			}
		}
	}

	return true;
}

bool CConfCtrlLogic::OnBtnCancelSelView(TNotifyUI& msg)
{
	for (int i=0; i<3; i++)
	{
		CSrcSelWatchLogic::GetSingletonPtr()->CancelSelWatch(i);
	}

	return true;
}

bool CConfCtrlLogic::OnCnsDualNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	CCheckBoxUI* pCheckCnsDual = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckCnsDual"));
	if ( pCheckCnsDual )
	{
		pCheckCnsDual->SetCheckNoMsg(ComInterface->IsLocalCnsDual());
	}
	return true;
}

bool CConfCtrlLogic::OnCallOffCnsInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	u32 dwErrID = lParam;
	if (dwErrID != NO_ERROR)
	{
		CString strError = _T("");
		switch( dwErrID )
		{
		case ERR_UMC_CALLCNS_HUNGUP:
			strError = _T("呼叫失败：对端不接收");
			break;
		case ERR_CMS_CALLCNS_UNREACHABLE:
			strError = _T("呼叫失败：对端不可达");
			break;
		case ERR_UMC_CALLCNS_RESOURCE_FULL:
			strError = _T("呼叫失败：对端无可用资源");
			break;
		case ERR_UMC_CALLCNS_DST_NOT_FOUND:
			strError = _T("呼叫失败：对端不存在");
			break;
		case ERR_UMC_CALLCNS_BUSY:
			strError = _T("呼叫失败：对端忙");
			break;
		case ERR_UMC_CALLCNS_LOCAL:
			strError = _T("呼叫失败：本地原因");
			break;
		case ERR_CMS_CALLCNS_NO_CONF:
			strError = _T("呼叫失败：会议不存在");
			break;
		case ERR_UMC_CALLCNS_CNS_EXIST:
			strError = _T("呼叫失败：对端已在会议中");
			break;
		case ERR_UMC_CALLCNS_CNS_REJECTED:
			strError = _T("呼叫失败：对端拒绝");
			break;
		case ERR_UMC_CALLCNS_CNS_PEERHUNGUP:
			strError = _T("呼叫失败：对端挂断");
			break;
		case ERR_UMC_CALLCNS_CNS_ABNORMAL:
			strError = _T("呼叫失败：本地掉线挂断");
			break;
		case ERR_UMC_CALLCNS_CNS_PEERABNORMAL:
			strError = _T("呼叫失败：对端掉线挂断");
			break;
		case ERR_UMC_CALLCNS_CNS_CONFOVER:
			strError = _T("呼叫失败：会议结束");
			break;
		case ERR_UMC_CALLCNS_CNS_CALLEXCEPTION:
			strError = _T("呼叫失败：接入模块掉线");
			break;
		case ERR_UMC_CALLCNS_CNS_CONFEXIST:
			strError = _T("呼叫失败：会议已存在");
			break;
		case ERR_UMC_CALLCNS_CNS_UNKNOWN:
			strError = _T("呼叫失败：未知原因");
			break;
		default:
			break;
		}

		ShowPopMsg(strError);
	}

	return true;
}

void CConfCtrlLogic::UpdateListPath()
{
    if ( m_tParentCns.m_wEpID == TP_INVALID_INDEX )
    {
        ICncCommonOp::ShowControl( false, m_pm, _T("LayoutGroupPath1") );
    }
    else
    {
        ICncCommonOp::ShowControl( true, m_pm, _T("LayoutGroupPath1") );
        ICncCommonOp::SetControlText( CA2T(m_tParentCns.m_achRoomName), m_pm, _T("txtGroupPath1") );
    }
}

bool CConfCtrlLogic::OnBtnListMainPath(TNotifyUI& msg)
{
    m_tParentCns.Clear();
	m_bSearchEdit = FALSE;
	ICncCommonOp::SetControlText(_T(""), m_pm, _T("ConfCtrlEdtSearch"));

    UpdateShowList();
    UpdateListPath();
    return true;
}

bool CConfCtrlLogic::OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    ComInterface->ShowKeyboard();
    return true;
}

bool CConfCtrlLogic::OnBtnVedioItemSel( TNotifyUI& msg )
{
	int index = msg.pSender->GetTag();
	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("VedioSourceList") );
	if ( pTileLayoutUI == NULL )
	{
		return false;
	}

	pTileLayoutUI->SelectItem(index);

	return true;
}

bool CConfCtrlLogic::OnVedioItemSel( TNotifyUI& msg )
{
	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("VedioSourceList") );
	if ( pTileLayoutUI == NULL )
	{
		return false;
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

bool CConfCtrlLogic::OnVidSrcNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
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
	default:
		break;
	case 3:
		{
			CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("VedioSourceList") );
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

bool CConfCtrlLogic::OnVgaInfoNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	UpdateVedioSourceList();
	return NO_ERROR;
}

bool CConfCtrlLogic::OnSelDefaultDualPortInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
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

bool CConfCtrlLogic::OnSelDualPortInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
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

void CConfCtrlLogic::UpdateVedioSourceList()
{
	ComInterface->GetDualSrcInfo( m_tDualSrcInfo );

	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("VedioSourceList") );
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
				(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("VedioSourceTouchListItem") );

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