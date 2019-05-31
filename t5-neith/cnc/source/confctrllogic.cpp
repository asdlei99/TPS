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
	MSG_SELECTCHANGE(_T("CheckVoiceArouse"), OnCheckPTPVoiceArouse)//��Ե���������
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
	//�������趨 dyy2015-6-25
	USER_MSG(UI_UMS_CHANGE_SPEAKER_NOTIFY,OnSpeakerNty)
	USER_MSG(UI_UMS_SET_SPEAKER_IND,OnSpeakerInd)
	//�᳡˫�� 2015-6-26
	USER_MSG(UI_UMS_SET_DUAL_CNS_RSP,OnItemDualInd)//��ʾ
	USER_MSG(UI_UMS_DUAL_CNS_NOTIFY,OnItemDualNty)//״̬
	//����ѡ��֪ͨ
	USER_MSG(UI_CNS_SEL_VIEW_NTY,OnItemSelViewNty) 
	//���в����߻᳡��Ӧ
	USER_MSG(UI_UMS_INVITE_CNS_RSP,OnCallOffCnsInd) 

	//�������������������ػ�Ӧ
	USER_MSG( UI_CNS_CNAUXMIX_IND, OnCnAuxInd )
	//��ϯ���� ��ֹ���յ�����״̬ʱ��û�յ���ϯ
	USER_MSG( UI_CNS_CHAIRCONFINFO_NTY, OnConfStateNty )
	//ȫ������/����
	USER_MSG(UI_CNC_SHORTCUT_QUITEALL,OnShortCutQuiteAll)
	USER_MSG(UI_CNC_SHORTCUT_MUTEALL,OnShortCutMuteAll)

	//��ƵԴ״̬֪ͨ
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

static UINT g_nDualWaiting = 0;//����˫���������1s
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
	m_vctSelectList.clear();//������� dyy 2015-6-30
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
        pListLabelElement1->SetText(_T("ȫ  ��"));
        pComboEx->Add(pListLabelElement1);

        CListLabelElementUI *pListLabelElement2 = 
            (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
        pListLabelElement2->SetText(_T("��  ��"));
        pComboEx->Add(pListLabelElement2);

        CListLabelElementUI *pListLabelElement3 = 
            (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
        pListLabelElement3->SetText(_T("������"));
        pComboEx->Add(pListLabelElement3);

        CListLabelElementUI *pListLabelElement4 = 
            (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
        pListLabelElement4->SetText(_T("���Ի᳡"));
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
		ShowMessageBox(_T("����ѡ��������õĻ᳡"));
        return false;
    }
    TCnsInfo tCnsInfo = m_vctSelectList.at(0);

	if (m_tConfInfo.m_wSpeaker == tCnsInfo.m_wEpID)
	{
		return true;//�Ѿ��Ƿ����˲��ظ�������Ϣ
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
		ShowMessageBox(_T("����ѡ��������õĻ᳡"));
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
		ShowMessageBox(_T("����ѡ��������õĻ᳡"));
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

	if (tCnsInfoLocal->m_wEpID == tCnsInfo.m_wEpID)//������ѡ���Լ�
	{
		ShowMessageBox(_T("�᳡ѡ������ʧ�ܣ�������ѡ�����᳡"));
		return false;
	}

	TTPSelViewReq tTPSelViewReq;
	tTPSelViewReq.m_emType = EmEpType_Ter;
	tTPSelViewReq.m_emUIType = EmUI_CNC;
	tTPSelViewReq.m_wConfID = m_tConfInfo.m_wConfID;
	tTPSelViewReq.m_wScreenIndx = TP_MAX_STREAMNUM;//�᳡ѡ��
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
		str.Format(_T("�᳡ѡ������ʧ��"));
		ShowMessageBox(str);
	}
	
	return true;
}

bool CConfCtrlLogic::OnBtnSetQuiet(TNotifyUI& msg)
{
    if( m_vctSelectList.empty() )
    {
		ShowMessageBox(_T("����ѡ��������õĻ᳡"));
        return false;
    }

	//��һ�����Ǿ��� �ͽ����Ǿ�������Ϊ����,ȫ�Ǿ��� ��ȫ���ò��Ǿ��� xcrȷ�� 2015-6-25 dyy
	bool bIsAllQuiet = true;//�Ƿ�ȫ���Ѿ��Ǿ���״̬
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

	if (bIsAllQuiet)//ȫ�Ǿ��� ȫȡ������
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
		ShowMessageBox(_T("����ѡ��������õĻ᳡"));
        return false;
    }

	//��һ���������� �ͽ�������������Ϊ����,ȫ������ ��ȫ���ò������� xcrȷ�� 2015-6-25 dyy
	bool bIsAllMute = true;//�Ƿ�ȫ���Ѿ��Ǿ���״̬
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

	if (bIsAllMute)//ȫ������ ȫȡ������
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
		ShowMessageBox(_T("����ѡ��������õĻ᳡"));
        return false;
    }

	//ѡ�������ߵ�ȫ���Ҷ� xcrȷ�� 2015-6-25 dyy
	for (int i=0; i<m_vctSelectList.size(); i++)
	{
		TCnsInfo tCnsInfo = m_vctSelectList.at(i);
		if ( tCnsInfo.m_bOnline )
		{
			//��������᳡������Ҫ�û�ȷ��
			if ( tCnsInfo.m_wEpID == m_tConfInfo.GetChairCnsID()  )
			{
				UIDATAMGR->setLocalCnsState( emLocalCnsWillHungup );
				int nReslut = ShowMessageBox(  _T("�Ҷ���ϯ�᳡���������飬�Ƿ��������"), true );
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
	//����������Ҳ��������ͬ���б�����б��������ж� dyy 2015-3-27
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
            //�����¼��б�
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

            if (!ComInterface->IsLocalCnsChairMan())//������ϯ���ܿ���
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
                    //�����˲�����
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
                    if (m_vctShowList.at(m_nSelIndex).m_bOnline)//����
                    {
                        m_pm->DoCase( _T("caseListNoSel"), pLastSel );
                    }
                    else//������
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
                        //�����˲�����
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
	//����������Ҳ��������ͬ���б�����б��������ж� dyy 2015-3-27
	if (msg.pSender->GetParent()->GetParent()->GetName() != _T("ConfCnsList"))
	{
		return false;
	}

	//if (!ComInterface->IsLocalCnsChairMan())//������ϯ���ܿ���
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
	if (m_vctSelectList.size() == 1 && m_vctSelectList.at(0).m_bOnline)//ֻѡһ�����ߵ�ʱ�� ѡ���Ȱ�ť���� ��������������
	{
		bIsEnable = true;
	}

	if (!ComInterface->IsLocalCnsChairMan())//������ϯҲ֧��ѡ����ť
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
			str.Format(_T("�᳡Զҡʧ��"));
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
			str.Format(_T("�᳡˫������ʧ��"));
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
			return true;//�Ѿ��Ƿ����˲��ظ�������Ϣ
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

		if (tCnsInfoLocal->m_wEpID == tCnsInfo.m_wEpID)//������ѡ���Լ�
		{
			ShowMessageBox(_T("�᳡ѡ������ʧ�ܣ�������ѡ�����᳡"));
			return false;
		}

		TTPSelViewReq tTPSelViewReq;
		tTPSelViewReq.m_emType = EmEpType_Ter;
		tTPSelViewReq.m_emUIType = EmUI_CNC;
		tTPSelViewReq.m_wConfID = m_tConfInfo.m_wConfID;
		tTPSelViewReq.m_wScreenIndx = TP_MAX_STREAMNUM;//�᳡ѡ��
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
			str.Format(_T("�᳡ѡ������ʧ��"));
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

        //��������᳡������Ҫ�û�ȷ��
        if ( tCnsInfo.m_wEpID == m_tConfInfo.GetChairCnsID()  )
        {
            UIDATAMGR->setLocalCnsState( emLocalCnsWillHungup );
            int nReslut = ShowMessageBox(  _T("�Ҷ���ϯ�᳡���������飬�Ƿ��������"), true );
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

    if ( msg.lParam != 1 )//ֻ��������ʱ����ˢ��
    {
        UpdateShowList();
    }  

    return true;
}

bool CConfCtrlLogic::OnConfStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	//��û���״̬���Ի���б�������ƣ���Ե���飬ֻ��˫���ͻ��л� dyy 2015-5-13 
	TCMSConf tConfInfo;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
	//���ݻ���״̬����ȫ����������ʾ״̬
	EM_ShortcutType em = emShortcutQuiteAll;
	NOTIFY_MSG( UI_CNC_SET_SHORTCUT_NTY, em, bInConf );
	em = emShortcutMuteAll;
	NOTIFY_MSG( UI_CNC_SET_SHORTCUT_NTY, em, bInConf );

	if ( !bInConf )
	{
		m_tConfInfo.Clear();
		m_vctSelectList.clear();//������ dyy 2015-6-30
        m_tParentCns.Clear();
        UpdateListPath();
        m_bSearchEdit = FALSE;
        ICncCommonOp::SetControlText( _T(""), m_pm, _T("ConfCtrlEdtSearch") );

		//����������ص�������ƽ��� dyy 2015-5-13
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
		//�ر�˫��
		CCheckBoxUI* pCheckCnsDual = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckCnsDual"));
		if ( pCheckCnsDual )
		{
			pCheckCnsDual->SetCheckNoMsg(ComInterface->IsLocalCnsDual());
		}
		//�ر�Զҡ
		TConfEpID  tConfEpInfo ;
		tConfEpInfo.Clear();
		ComInterface->SetFeccConfEpInfo( tConfEpInfo );
		ICncCommonOp::ShowControl( false, m_pm, _T("ConfroomCramerLayout") );
	}
	else
	{
		//��Ե�Զҡ����
		m_pm->DoCase(_T("caseP2PFeccCam"));

		if (tConfInfo.m_emConfType == emCallType_P2P)//��Ե����
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
					str.Format(_T("�᳡Զҡʧ��"));
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
			//���Զҡ����
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
		ShowMessageBox(_T("û���κλ᳡"));
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
		ShowMessageBox(_T("û���κλ᳡"));
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
		//��ԭ��ʾѡ��
		//InitLst();
		m_tConfInfo.Clear();
		PrtMsg(0,emEventTypeCmsWindow,"[CConfCnsLstLogic::UpdateCnsLst]: ����cns���ڻ����У���ˢ��cns�б�����cns�б����");
		return;
	}

    m_tConfInfo = tConfInfoTemp;
	m_vctCnsList.clear();

	//����ڼ����б��� ���¼����б��е�״̬��Ϣ 2016-11-15 dyy
	bool bIsIn = false;//�Ƿ�ǰ�ڼ����б���
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

	//�����ѡ�������ѡ��������
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
        msg.lParam = 1; //ֻ����m_vctSearchList����
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

	//���Զҡ�᳡��Ϣ
	TConfEpID tFeccConfEpID;
	ComInterface->GetFeccConfEpInfo(tFeccConfEpID);

    //�������ɸѡ�����Ŀ
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

		//ѡ������ �������߲�����
		vector<TCnsInfo>::iterator itfind = find( m_vctSelectList.begin(), m_vctSelectList.end(), tCnsInfo );
		if ( itfind != m_vctSelectList.end() )
		{
			itfind->m_bOnline = tCnsInfo.m_bOnline;//��������״̬
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
			//���ͼ��
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
			
			if (tCnsInfo.m_bOnline)//���߲���ʾ״̬ͼ��
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

			    //ѡ������ ���߱�������ѡ��״̬ ��������ѡ��״̬
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
		    else//������
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
			ShowMessageBox(_T("����ʧ��"));
			pCheckBox->SetCheckNoMsg(false);
		}
	}
	else
	{
		ShowMessageBox(_T("���ڻ����У����ܿ���"));
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
			ShowPopMsg(_T("������������ʧ��"));
		}
		else
		{
			ShowPopMsg(_T("�ر���������ʧ��"));
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
			ShowPopMsg(_T("˫����Ϣ����ʧ��"));
		}
		else
		{
			//��ӱ�����һ��֮�ڲ����ٲ���˫��
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
			strTemp = _T("���Ų���1");
			break;
		case  emViewLocalFailOffline:
			strTemp = _T("�᳡����");
			break;
		default:
			strTemp = _T("δ֪ԭ��");
			break; 
		}

		BOOL bPIP = ComInterface->IsViewLocalPIP();
		if ( bPIP )
		{
			strErr = _T("�رջ��л�ʧ�ܣ�") + strTemp;
		}
		else
		{
			strErr = _T("�������л�ʧ�ܣ�") + strTemp;
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
	BOOL bStart = (BOOL)wParam; //�������ǹرղ���
	EmTPDualReason emRe = (EmTPDualReason)lParam;

	CString strErr = _T("");
	if ( emRe != emTpDualAccept )
	{  
		CString strTemp = _T("");
		switch ( emRe )
		{
		case emTpDualBusy:
			strTemp = _T("˫��Դæ");
			break;
		case emTpDualPreemptive:
			strTemp = _T("δ֪ԭ��");
			break;
		case emTpDualPeerReject:
			strTemp = _T("�Զ˾ܾ�");
			break;
		case emTpDualPeerStop:
			strTemp = _T("�Զ�ֹͣ��ʾ");
			break;
		case emTpDualNoVideo:
			strTemp = _T("����ƵԴ");
			break;
		case emTpDualLocalStop:
			strTemp = _T("����ֹͣ��ʾ");
			break;
		case emTpDualSndFail:
			strTemp = _T("����˫��ʧ��");
			break;
		case emTpDualInit:
			strTemp = _T("˫����ʼ���У����Ժ�����");
			break;
		case emTpDualBitrateIs0:
			strTemp = _T("��ʾ����ʧ�ܣ�����Ϊ0");
			break;
		default:
			strTemp = _T("δ֪ԭ��");
			break; 
		}

		if ( bStart )
		{
			strErr = _T("������ʾʧ�ܣ�") + strTemp;
		}
		else
		{
			strErr = _T("�ر���ʾʧ�ܣ�") + strTemp;
		}

		if (!(!bStart && (emRe == emTpDualPeerStop || emRe == emTpDualLocalStop))) //�رղ��ұ��˻�Զ�ֹͣ��ʾ������ʾ nlfȷ��
		{
			ShowPopMsg( strErr );

			//ʧ���� ��������
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
		ShowPopMsg( _T("������ʾ�ɹ�"));
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
	ShowPopMsg( _T("˫��Դ����"));	
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
		str = _T("ͨ���쳣�Ͽ�");
		break;
	case emTPDualOffLine:
		str = _T("˫��Դ����");
		break;
	case emTPForceStop:
		str = _T("˫��Դ������");
		break;
	default:
		str = _T("δ֪ԭ��");
	}

	ShowPopMsg( _T("����˫����ֹ:") + str );	
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
		//TPad��cnc�������ɼ�ʱ����ʾ dyy 2013��8��2��
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

	//�����Ŀ����ʱ�������ĸ�Ῠ������ ��ʹ�ö��ַ�
	int swLowIndex = 0;
	int swHighIndex = nItemCount;
	int swMidIndex = 0;   //�õ�ǰ���������ϡ��½�ĳ�ֵ 

	while( swLowIndex < swHighIndex )
	{   
		int nMidIndex = swMidIndex;
		//��ǰ��������R[low..high]�ǿ� 
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
			swHighIndex = swMidIndex;  //��ǰ��������R[low..mid]  
		}
		else
		{   
			swLowIndex = swMidIndex + 1;//��ǰ��������R[mid..heith] 
		}						 

	} 

	//swLowIndex��swHighIndex���ʱ����swMidIndex�Ƚ�
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

	//ȡswLowIndex��swHighIndex�е�һ����strIndex��ķ���
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
// 		UpdateCnsItem( wOldSpeaker );//����֮ǰ��ѡ����
// 	}	
// 	
// 	UpdateCnsItem( wNewSpeaker );//����Ŀǰ��ѡ����
	UpdateCnsList();
	UpdateShowList();
	return true;
}

bool CConfCtrlLogic::OnSpeakerInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	//��Ӧnty
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
		CString strErr = _T("�᳡˫������ʧ��");
		switch(emRe)
		{
		case emTpDualBusy:
			{
				strErr = _T("�᳡˫������ʧ�ܣ�˫��æ");
			}
			break;
		case emTpDualPreemptive:
			{
				strErr = _T("�᳡˫������ʧ�ܣ�");
			}
			break;
		case emTpDualPeerReject:
			{
				strErr = _T("�᳡˫������ʧ�ܣ��Զ˾ܾ�");
			}
			break;
		case emTpDualPeerStop:
			{
				strErr = _T("�᳡˫������ʧ�ܣ��Զ�ֹͣ");
			}
			break;
		case emTpDualNoVideo:
			{
				strErr = _T("�᳡˫������ʧ�ܣ�û����ƵԴ");
			}
			break;
		case emTpDualLocalStop:
			{
				strErr = _T("�᳡˫������ʧ�ܣ�˫��ֹͣ");
			}
			break;
		case emTpDualSndFail:
			{
				strErr = _T("�᳡˫������ʧ�ܣ�����˫��ʧ��");
			}
			break;
		case emTpDualInit:
			{
				strErr = _T("�᳡˫������ʧ�ܣ�˫����ʼ����");
			}
			break;
		case emTpDualBitrateIs0:
			{
				strErr = _T("��ʾ����ʧ�ܣ�����Ϊ0");
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
// 	//if (wConfID == m_tConfInfo.m_wConfID) ��һ������ô
// 	{
// 		int wOldDual = m_tConfInfo.m_wDual;
// 		UpdateCnsList();
// 		int wNewDual = m_tConfInfo.m_wDual;
// 		if (wOldDual != wNewDual)
// 		{
// 			UpdateCnsItem( wOldDual );//����֮ǰ��˫����
// 		}	
// 
// 		UpdateCnsItem( wNewDual );//����Ŀǰ��˫����
// 	}
	UpdateCnsList();
	UpdateShowList();
	return true;
}

bool CConfCtrlLogic::OnItemSelViewNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{	
	TTPSelViewNtfy tTPSelViewNtfy = ComInterface->GetSelWatchStatus();	

	if (tTPSelViewNtfy.m_atSelView[0].m_wScreenIndx == TP_MAX_STREAMNUM)//�᳡ѡ��
	{
// 		int wOldSV = m_tConfInfo.m_wSelViewConfID;
// 		UpdateCnsList();
// 		int wNewSV = m_tConfInfo.m_wSelViewConfID;
// 		if (wOldSV != wNewSV)
// 		{
// 			UpdateCnsItem( wOldSV );//����֮ǰ��ѡ����
// 		}	
// 
// 		UpdateCnsItem( wNewSV );//����Ŀǰ��ѡ����
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
				ShowMessageBox(_T("�᳡����ʧ��"));
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
			strError = _T("����ʧ�ܣ��Զ˲�����");
			break;
		case ERR_CMS_CALLCNS_UNREACHABLE:
			strError = _T("����ʧ�ܣ��Զ˲��ɴ�");
			break;
		case ERR_UMC_CALLCNS_RESOURCE_FULL:
			strError = _T("����ʧ�ܣ��Զ��޿�����Դ");
			break;
		case ERR_UMC_CALLCNS_DST_NOT_FOUND:
			strError = _T("����ʧ�ܣ��Զ˲�����");
			break;
		case ERR_UMC_CALLCNS_BUSY:
			strError = _T("����ʧ�ܣ��Զ�æ");
			break;
		case ERR_UMC_CALLCNS_LOCAL:
			strError = _T("����ʧ�ܣ�����ԭ��");
			break;
		case ERR_CMS_CALLCNS_NO_CONF:
			strError = _T("����ʧ�ܣ����鲻����");
			break;
		case ERR_UMC_CALLCNS_CNS_EXIST:
			strError = _T("����ʧ�ܣ��Զ����ڻ�����");
			break;
		case ERR_UMC_CALLCNS_CNS_REJECTED:
			strError = _T("����ʧ�ܣ��Զ˾ܾ�");
			break;
		case ERR_UMC_CALLCNS_CNS_PEERHUNGUP:
			strError = _T("����ʧ�ܣ��Զ˹Ҷ�");
			break;
		case ERR_UMC_CALLCNS_CNS_ABNORMAL:
			strError = _T("����ʧ�ܣ����ص��߹Ҷ�");
			break;
		case ERR_UMC_CALLCNS_CNS_PEERABNORMAL:
			strError = _T("����ʧ�ܣ��Զ˵��߹Ҷ�");
			break;
		case ERR_UMC_CALLCNS_CNS_CONFOVER:
			strError = _T("����ʧ�ܣ��������");
			break;
		case ERR_UMC_CALLCNS_CNS_CALLEXCEPTION:
			strError = _T("����ʧ�ܣ�����ģ�����");
			break;
		case ERR_UMC_CALLCNS_CNS_CONFEXIST:
			strError = _T("����ʧ�ܣ������Ѵ���");
			break;
		case ERR_UMC_CALLCNS_CNS_UNKNOWN:
			strError = _T("����ʧ�ܣ�δ֪ԭ��");
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
		ICncCommonOp::SetControlText(_T(""),m_pm,_T("lbvediosrc"),pListContainerOld);//Դ״̬��գ�ѡ��ĵȴ���Ϣ��������
	}

	if (pListContainer)
	{
		ICncCommonOp::SetControlBkImg( _T("res/roomctrl/btnVedioSel.png"), m_pm, _T("btnSet"), pListContainer );
		ICncCommonOp::SetControlBkImg( _T("res/roomctrl/VedioSource_select.png"), m_pm, _T("picLayout"), pListContainer );

		//ICncCommonOp::SetControlTextColor( _T("#CC379FDB"), m_pm, _T("vedioItemName"), pListContainer );
	}

	if (m_bSetVedioSourc)//�ڷ���Ϣδ��Ӧ�����Լ�������
	{
		return true;
	}

	TVgaInfo tVgaInfo;
	tVgaInfo = m_tDualSrcInfo.vctVgaInfo.at(msg.wParam);

	BOOL32 bIsInconf = ComInterface->IsInConf();
	if (bIsInconf)
	{
		//������ �л���ǰ��ʾԴ
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
			//����ʱ �л�Ĭ����ʾԴ
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

	CString str = _T("��");
	if (bIsSuccess)
	{
		str = _T("[��Դ]");
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

			for ( u32 i = 0; i < m_tDualSrcInfo.vctVgaInfo.size(); i++ )//ȫ��ˢһ��
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
		ShowPopMsg(_T("�л���ʾԴʧ��"));
		//Ĭ������û��nty֪ͨ nlfȷ�� �����Լ����� dyy 2015-6-9
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

	CString strError = _T( "�л���ʾԴʧ��" );
	if ( emResult == em_CurVgaNoSignal )
	{
		strError = _T( "��ǰ��ʾԴ������" );
	}
	else if ( emResult == em_TpNoDual )
	{
		strError = _T( "��ǰ��ʾԴ��˫���ն�" );
	}
	else if ( emResult == em_VgaBusying )
	{
		strError = _T( "�л���ʾԴʧ�ܣ�������æ���Ժ�����" );
	}
	else if ( emResult == em_VgaSwitchInvalid )
	{
		strError = _T( "��ǰ��ʾԴ��Ч" );
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
	if (!m_bIsVSListExt)//δ����
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
	else//��������и���
	{
		for ( u32 i = 0; i < m_tDualSrcInfo.vctVgaInfo.size(); i++ )
		{
			CListContainerElementUI *pListContainer = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(i);
			ICncCommonOp::SetControlText( CA2T(m_tDualSrcInfo.vctVgaInfo.at(i).m_achAlias), m_pm, _T("vedioItemName"), pListContainer );
		}
	}

	pTileLayoutUI->SelectItem((int)m_tDualSrcInfo.emCurrentType,false);
}