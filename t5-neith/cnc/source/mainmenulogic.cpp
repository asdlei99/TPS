#include "StdAfx.h"
#include "mainmenulogic.h"
#include "mainframelogic.h"
#include "conftemplogic.h"
#include "messageboxlogic.h"
#include "confmsglogic.h"
#include "PanCamlogic.h"
#include "confctrllogic.h"
#include "cnsmanagelogic.h"
#include "confmixlogic.h"
#include "addrbooklogic.h"

#define  MAINMENU_INITHEIGHT   279   //mainmenu初始高度

template<> CMainMenuLogic* Singleton<CMainMenuLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CMainMenuLogic, CNotifyUIImpl)
	MSG_CREATEWINDOW(_T("MainMenuLayout"), OnCreate)
	MSG_INIWINDOW(_T("MainMenuLayout"), OnInit)

	MSG_CLICK(_T("BtnExtend"), OnBtnExtend)
	MSG_CLICK(_T("BtnAddrBook"), OnBtnAddrBook)
	MSG_CLICK(_T("BtnConfTemp"), OnBtnConfTemp)
	MSG_CLICK(_T("BtnRoomCtrl"), OnBtnRoomCtrl)
	MSG_CLICK(_T("BtnConfCtrl"), OnBtnConfCtrl)
	MSG_CLICK(_T("BtnSysCfg"), OnBtnSysCfg)
//	MSG_CLICK(_T("BtnCenterCtrl"), OnBtnCenterCtrl)
    MSG_CLICK(_T("BtnInviteCns"), OnBtnInviteCns)
    MSG_CLICK(_T("BtnEndConf"), OnBtnEndConf)
	MSG_CLICK(_T("BtnShortCutListSet"), OnBtnShortCutListSet)
	MSG_CLICK(_T("BtnMsg"), OnBtnMsg)
	MSG_CLICK(_T("BtnShortCutState"), OnBtnShortCutState)
	MSG_CLICK(_T("BtnIsPause"), OnBtnPollPause)

	MSG_BUTTONDOWN(_T("MainMenuInitLayout"), OnContainerClick)

	USER_MSG(UI_CNC_SET_SHORTCUT_NTY,OnShortCutNty)

	USER_MSG(UI_CNS_CONFSTATE_NOTIFY,OnConfStateNty)
	USER_MSG(UI_CNS_ALLMUTE_ALLQUITE_NOTIFY,OnShortCutStateNty)
	USER_MSG(UI_UMS_REFRESH_CONFAUDMIX_LIST,OnStartConfDiscNty)

	USER_MSG(UI_CNS_PANCAMINFO_NTY,OnPanCamStartNty)
	USER_MSG(UI_CNS_PANCAMSTART_RSP,OnPanCamStartNty)
	USER_MSG(UI_CNS_QUITE_MUTE,OnMuteOrSliencNty)
	USER_MSG(UI_CNS_POLL_STATE_NOTIFY,OnPollStateNty)
	USER_MSG(UI_DISCONNECTED_CLEARDATA, OnDisconnect)
	USER_MSG(UI_CNSPOLLPAUSE_IND,OnPollPauseInd)
	//USER_MSG(UI_CNS_VIEWLOCALPIP_IND,OnPIPInd) nty更新
	USER_MSG(UI_CNS_VIEWLOCALPIP_NTY,OnPIPNty)
	//USER_MSG(UI_CNS_START_DUAL_RSP,OnCnsDualRsp)
	USER_MSG(UI_CNS_DUAL_STATE_NOTIFY,OnCnsDualRsp)
	//单独控制语音激励开关通知、回应
    USER_MSG( UI_CNC_VOICEAROUSE_NTY, OnVoiceArouseInd )
	USER_MSG( UI_CNC_VOICEAROUSE_IND, OnVoiceArouseInd )
	//混音状态通知
	USER_MSG(UI_CNS_CONFMIX_NTY,OnConfMixStateNty)
	//点名状态
	USER_MSG(UI_CNS_CONFROLL_NTY,OnRollStateNty)
	USER_MSG(UI_CNS_CHAIRCONFINFO_NTY,OnConfStateNty)

    USER_MSG(UI_CNC_VIDMIXSTATUS_NTY,OnVidMIxStatusNty)  

APP_END_MSG_MAP()


static UINT g_nExtendTimerID = 0;

VOID CALLBACK CExtendMainMenuFun( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{
	if ( idEvent == g_nExtendTimerID )
	{
		CMainMenuLogic::GetSingletonPtr()->OnExtendMainMenu();
	}
}


CMainMenuLogic::CMainMenuLogic(void)  : m_hWnd(NULL), m_bExtend(FALSE),m_nMainMenuInitHeight(0)
{
	m_pBtnMsg = NULL;
	m_pBtnSysCfg = NULL;
	m_pContainerElementUI = NULL;
}


CMainMenuLogic::~CMainMenuLogic(void)
{
}

bool CMainMenuLogic::OnCreate( TNotifyUI& msg )
{
	REG_CNC_MSG_WND_OB(m_pm->GetPaintWindow());

	HWND hWnd = m_pm->GetPaintWindow();
	LONG styleValue = ::GetWindowLong(hWnd, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(hWnd, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_nMainMenuInitHeight = MAINMENU_INITHEIGHT;
	if ( CPaintManagerUI::IsSelfAdaption() )
	{
		float fAdpX, fAdpY;
		CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
		m_nMainMenuInitHeight = s32(m_nMainMenuInitHeight * fAdpY);
	}

	//读ini文件 配置(Tpad调用cnc界面初始化会延迟，所以将读取配置文件移到创建窗口处)
	int dwSize=-1;
	CString strIniPath = CMainFrameLogic::GetSingletonPtr()->GetIniFilePath();
	dwSize = GetPrivateProfileInt(_T("ShortCutInfo"),_T("Size"), -1, strIniPath);
	CString strName = _T("");
	m_vctShortCutList.clear();
	if (dwSize == -1)
	{
		for(int em = 0; em < 12; em++)
		{			
			if (emShortcutCofMix == (EM_ShortcutType)em || emShortcutCofRoll == (EM_ShortcutType)em)//点名、混音默认关闭
			{
				continue;
			}
			m_vctShortCutList.push_back((EM_ShortcutType)em);
			//			NOTIFY_MSG( UI_CNC_SHORTCUTCHECK_NTY, (EM_ShortcutType)em, NULL );//窗口未初始化，收不到消息，在init时发送
		}
	}
	else
	{
		for(int i = 0; i < dwSize; i++)
		{
			int em = -1;
			strName.Format(_T("Shortcut%d"),i);
			em = GetPrivateProfileInt(_T("ShortCutInfo"),strName, -1, strIniPath);
			if (em != -1 && em != emShortcutMuteAll && em != emShortcutQuiteAll)//全场静音哑音不需要读取配置文件
			{
				bool bIsExist = false;
				for ( std::vector< EM_ShortcutType >::const_iterator iter = m_vctShortCutList.begin(); iter != m_vctShortCutList.end(); ++iter)
				{
					if (*iter == em )
					{
						bIsExist = true;
						break;
					}
				}	
				if (!bIsExist)
				{
					m_vctShortCutList.push_back((EM_ShortcutType)em);
					//NOTIFY_MSG( UI_CNC_SHORTCUTCHECK_NTY, (EM_ShortcutType)em, NULL );//窗口未初始化，收不到消息，在init时发送
				}
			}			
		}
	}

	return false;
}

bool CMainMenuLogic::OnInit(TNotifyUI& msg)
{
	Window* pWnd = IWindowManager::GetSingletonPtr()->GetWindow( g_strMainMenuDlg.c_str() );
	if ( pWnd != NULL )
	{
		m_hWnd = pWnd->GetHWND();
		RECT rcWnd;
		::GetClientRect(m_hWnd, &rcWnd);

// 		RECT rcParentWnd;
// 		::GetClientRect(GetParent(m_hWnd), &rcParentWnd);

//		int nTop = rcParentWnd.bottom - m_nMainMenuInitHeight;
        int nTop = UIDATAMGR->GetCncMainPos().cy - m_nMainMenuInitHeight;
		SetWindowPos( m_hWnd, NULL, rcWnd.left, nTop, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );

		m_bExtend = FALSE;
	}

	m_pBtnMsg = ICncCommonOp::FindControl( m_pm, _T("BtnMsg") );
	m_pBtnSysCfg = ICncCommonOp::FindControl( m_pm, _T("BtnSysCfg") );

	//发送快捷键状态消息
	for ( std::vector< EM_ShortcutType >::const_iterator iter = m_vctShortCutList.begin(); iter != m_vctShortCutList.end(); ++iter)
	{
		NOTIFY_MSG( UI_CNC_SHORTCUTCHECK_NTY, (EM_ShortcutType)*iter, NULL );
	}

	UpdateShortCutLst();

	m_rectBtnMsg = m_pBtnMsg->GetPos();
	m_rectBtnCfg = m_pBtnSysCfg->GetPos();
	return true;
}

bool CMainMenuLogic::OnBtnExtend(TNotifyUI& msg)
{

	if ( m_hWnd == NULL || GetParent(m_hWnd) == NULL )
	{
		return false;
	}

	g_nExtendTimerID = SetTimer( NULL, 0, WINDOW_TIMER_ELAPSE, CExtendMainMenuFun );

	if( !m_bExtend )
	{
		m_pm->DoCase( _T("caseMainMenuExtend") );
	}

	//m_pBtnMsg->SetVisible( false );

	return true;
}

void CMainMenuLogic::OnExtendMainMenu()
{
	RECT rcWnd;
	//::GetClientRect(m_hWnd, &rcWnd);
	::GetWindowRect(m_hWnd, &rcWnd);
	POINT point;
	point.x = rcWnd.left;
	point.y = rcWnd.top;
	ScreenToClient( GetParent(m_hWnd), &point );

// 	RECT rcParentWnd;
// 	::GetClientRect( GetParent(m_hWnd), &rcParentWnd);

	int nStepLen = ( rcWnd.bottom - rcWnd.top ) / WINDOW_MOVESTEP_COUNT;

	if ( !m_bExtend )
	{
//		int nBottomOut = point.y + rcWnd.bottom - rcWnd.top - rcParentWnd.bottom;
        int nBottomOut = point.y + rcWnd.bottom - rcWnd.top - UIDATAMGR->GetCncMainPos().cy;
		point.y -= nStepLen;
		nBottomOut -= nStepLen;


		RECT rect = m_pBtnMsg->GetPos();
		rect.top += nStepLen;
		rect.bottom += nStepLen;
		RECT rect1 = m_pBtnSysCfg->GetPos();
		rect1.top += nStepLen;
		rect1.bottom += nStepLen;

		if ( nBottomOut <= 0 ) 
		{
			point.y -= nBottomOut;
			rect.top += nBottomOut;
			rect.bottom += nBottomOut;
			rect1.top += nBottomOut;
			rect1.bottom += nBottomOut;
			KillTimer( NULL, g_nExtendTimerID );
			g_nExtendTimerID = 0;
			m_bExtend = TRUE;		

			//m_pBtnMsg->SetVisible( true );
		}

		SetWindowPos( m_hWnd, NULL, point.x, point.y, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );
		
		m_pBtnMsg->SetPos( rect );
		m_pBtnSysCfg->SetPos( rect1 );
	}
	else
	{
		//int nBottomHeight = rcParentWnd.bottom - m_nMainMenuInitHeight;
        int nBottomHeight = UIDATAMGR->GetCncMainPos().cy - m_nMainMenuInitHeight;
		point.y += nStepLen;

		RECT rect = m_pBtnMsg->GetPos();
		rect.top -= nStepLen;
		rect.bottom -= nStepLen;
		RECT rect1 = m_pBtnSysCfg->GetPos();
		rect1.top -= nStepLen;
		rect1.bottom -= nStepLen;

		if ( point.y >= nBottomHeight ) 
		{
			int nOffset = point.y - nBottomHeight;
			point.y = nBottomHeight;

			rect.top += nOffset;
			rect.bottom += nOffset;
			rect1.top += nOffset;
			rect1.bottom += nOffset;

			KillTimer( NULL, g_nExtendTimerID );
			g_nExtendTimerID = 0;
			m_bExtend = FALSE;
			m_pm->DoCase( _T("caseMainMenuBack") );

			//m_pBtnMsg->SetVisible( true );
		}

		SetWindowPos( m_hWnd, NULL, point.x, point.y, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );
	
		m_pBtnMsg->SetPos( rect );
		m_pBtnSysCfg->SetPos( rect1 );
	}
}

bool CMainMenuLogic::OnBtnAddrBook(TNotifyUI& msg)
{
	//WINDOW_MGR_PTR->ShowWindowFromLeftToRight( g_strConfCallCfgDlg.c_str() );
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight( g_strAddrbookDlg.c_str() );

	CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("地址簿"));
	CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgAddrbook.png"));

    CPaintManagerUI* pm = CAddrBookLogic::GetSingletonPtr()->GetPaintManagerUI();
    if (pm)
    {
        ICncCommonOp::ShowControl( false, pm, _T("TemporaryCallLayout") );
    }

	WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
	UIDATAMGR->SetCurShowWndName( g_strAddrbookDlg );
	return true;
}

bool CMainMenuLogic::OnBtnInviteCns(TNotifyUI& msg)
{
    WINDOW_MGR_PTR->ShowWindowFromLeftToRight( g_strAddrbookDlg.c_str() );

    CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("邀请会场"));
    CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgInvite.png"));
    CMainFrameLogic::GetSingletonPtr()->SetTitleTab( true, g_strInviteCnsDlg.c_str() );

    WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
    UIDATAMGR->SetCurShowWndName( g_strInviteCnsDlg );
    return true;
}

bool CMainMenuLogic::OnBtnConfTemp( TNotifyUI& msg )
{
	//ComInterface->UpdateConfTemplate(); 不用主动发消息刷新 2015-5-5 
	CConfTempLogic::GetSingletonPtr()->UpdateConfTempList();
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight(g_strConfTempDlg.c_str() );

	CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("会议模板"));
	CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgConfTemp.png"));

	WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
	UIDATAMGR->SetCurShowWndName( g_strConfTempDlg );
	return true;
}

bool CMainMenuLogic::OnBtnRoomCtrl( TNotifyUI& msg )
{
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight( g_strRoomControlDlg.c_str() );

	CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("会场管理"));
	CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgRoomCtrl.png"));

	WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
	UIDATAMGR->SetCurShowWndName( g_strRoomControlDlg );
	return true;
}

bool CMainMenuLogic::OnBtnConfCtrl( TNotifyUI& msg )
{
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight( g_strConfCtrlDlg.c_str() );

	CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("会议管理"));
	CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgConfCtrl.png"));

	WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
	UIDATAMGR->SetCurShowWndName( g_strConfCtrlDlg );

	CConfCtrlLogic::GetSingletonPtr()->UpdateShowList();
	return true;
}

bool CMainMenuLogic::OnBtnSysCfg( TNotifyUI& msg )
{
	WINDOW_MGR_PTR->ShowWindowFromBottomToTop(g_strSysConfigDlg.c_str() );

	CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("系统设置"));
	CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgSysCfg.png"));

	WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
	UIDATAMGR->SetCurShowWndName( g_strSysConfigDlg );
	return true;
}

bool CMainMenuLogic::OnBtnCenterCtrl( TNotifyUI& msg )
{
 	WINDOW_MGR_PTR->ShowWindowFromLeftToRight( g_stcStrCenterCtrlDlg.c_str() );

 	CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("中控管理"));
 	CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgCenterCtrl.png"));

 	WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
 	UIDATAMGR->SetCurShowWndName( g_stcStrCenterCtrlDlg );
	return true;
}

bool CMainMenuLogic::OnBtnEndConf(TNotifyUI& msg)
{
	TCMSConf tConfInfo;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );

	CString strMsg;
	if (ComInterface->IsLocalCnsChairMan() || tConfInfo.m_emConfType == emCallType_P2P)
	{
		strMsg.Format( _T("是否要结束会议") );
	}
	else
	{
		strMsg.Format( _T("是否要退出会议") );
	}
    

    UIDATAMGR->setLocalCnsState(emLocalCnsWillHungup); 
    int nReslut = ShowMessageBox( strMsg ,true ); 
    if ( IDOK == nReslut )
    {
        HungupConf();
    }

    return true;
}

bool CMainMenuLogic::HungupConf()
{ 
    TCMSConf ConfInfo ;
    BOOL32 bInConf = ComInterface->IsInConf( &ConfInfo );

    if ( !bInConf  )
    {
        PrtMsg( 0, emEventTypeCmsWindow,"[CConfCnsLstLogic::HungupConf]本地CNS不在会议中");
        return false;
    } 

    u16 wRe = NO_ERROR;

    if ( ConfInfo.m_emConfType == emCallType_Conf )
    {
		if (ComInterface->IsLocalCnsChairMan())
		{
			wRe = ComInterface->HangupConf();
		}
		else
		{

			TConfEpID  tConfEpInfo;
			tConfEpInfo.m_wConfID = ConfInfo.m_wConfID;

			TTPCnsInfo tCnsInfo;
			ComInterface->GetLocalCnsInfo( tCnsInfo );
			tConfEpInfo.m_wEpID = ConfInfo.GetCnsIDByAlias( tCnsInfo.m_achRoomName );

			wRe = ComInterface->HangupCns( tConfEpInfo );
		}
        
    }
    else
    {       
        wRe = ComInterface->HungupPtpConf();        
    }

    return true;
}


bool CMainMenuLogic::OnBtnMsg( TNotifyUI& msg )
{
	CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("消息提示"));
	CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgMessage.png"));
	CMainFrameLogic::GetSingletonPtr()->HideTipBtn();

	WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
	UIDATAMGR->SetCurShowWndName( g_strConfMsgDlg );
	WINDOW_MGR_PTR->ShowWindowFromBottomToTop(g_strConfMsgDlg.c_str() );

	return true;
}

bool CMainMenuLogic::OnShortCutNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	EM_ShortcutType em = (EM_ShortcutType)wParam;
	bool bIsShow = lParam;

	if ( bIsShow )
	{
		bool bIsExist = false;
		for ( std::vector< EM_ShortcutType >::const_iterator iter = m_vctShortCutList.begin(); iter != m_vctShortCutList.end(); ++iter)
		{
			if (*iter == em )
			{
				bIsExist = true;
				break;
			}
		}	
		if (!bIsExist)
		{
			m_vctShortCutList.push_back(em);
		}
	}
	else
	{	
		for ( std::vector< EM_ShortcutType >::const_iterator iter = m_vctShortCutList.begin(); iter != m_vctShortCutList.end(); ++iter)
		{
			if (*iter == em )
			{
				m_vctShortCutList.erase(iter);
				break;
			}
		}	
	}
	
	UpdateShortCutLst();
	return true;
}

bool CMainMenuLogic::OnShortCutStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	UpdateShortCutLst();
	return true;
}

void CMainMenuLogic::UpdateShortCutLst()
{
	CTouchListUI* pShortCutList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("ShortCutList") );
	if ( pShortCutList == NULL )
	{
		return;
	}
	if ( pShortCutList->GetCount() >= 0)
	{
		pShortCutList->RemoveAll();
	}

	TCMSConf tConfInfo;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
	bool bIsPTP = false;
	if (tConfInfo.m_emConfType == emCallType_P2P)
	{
		bIsPTP = true;
	}
	BOOL32 bChairCns = ComInterface->IsLocalCnsChairMan();

	for ( u32 i = 0; i < m_vctShortCutList.size(); i++ )
	{
		CListContainerElementUI *pListContainer = 
			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("ShortCutListItem") );

		EM_ShortcutType emShortcutType = m_vctShortCutList.at(i); 
		CString strName = _T("");
		CString strPic = _T("");
		switch(emShortcutType)
		{
		case emShortcutMute:
			{
				//strName = _T("哑音");
				if (ComInterface->IsLocalCnsMute())
				{
                    strName = _T("开启麦克风");
					strPic = _T("res\\mainmenu\\MuteOn.png");				
				}
				else
				{
                    strName = _T("关闭麦克风");
					strPic = _T("res\\mainmenu\\MuteOff.png");	
				}
			}
			break;
		case emShortcutSilence:
			{
				//strName = _T("静音");
				if (ComInterface->IsLocalCnsQuite())
				{
                    strName = _T("开启扬声器");
					strPic = _T("res\\mainmenu\\SilenceOn.png");				
				}
				else
				{
                    strName = _T("关闭扬声器");
					strPic = _T("res\\mainmenu\\SilenceOff.png");	
				}
			}
			break;
		case emShortcutMuteAll:
			{
				if (!bInConf || bIsPTP)//不在会议或者点对点会议不显示
				{
					delete pListContainer;
					continue;
				}
				if (!bChairCns)//不是主席不显示
				{
					delete pListContainer;
					continue;
				}
				//strName = _T("全场哑音");
				if (ComInterface->IsAllMute())
				{
                    strName = _T("开启全场麦克风");
					strPic = _T("res\\mainmenu\\MuteOn.png");				
				}
				else
				{
                    strName = _T("关闭全场麦克风");
					strPic = _T("res\\mainmenu\\MuteOff.png");	
				}
			}
			break;
		case emShortcutQuiteAll:
			{
				if (!bInConf || bIsPTP)//不在会议或者点对点会议不显示
				{
					delete pListContainer;
					continue;
				}
				if (!bChairCns)//不是主席不显示
				{
					delete pListContainer;
					continue;
				}
				//strName = _T("全场静音");
				if (ComInterface->IsAllQuite())
				{
                    strName = _T("开启全场扬声器");
					strPic = _T("res\\mainmenu\\SilenceOn.png");				
				}
				else
				{
                    strName = _T("关闭全场扬声器");
					strPic = _T("res\\mainmenu\\SilenceOff.png");	
				}
			}
			break;
		case emShortcutPanCam:
			{
				
				if (ComInterface->IsLocalCnsPanCam())
				{
					strName = _T("关闭全景摄像机");
					strPic = _T("res\\mainmenu\\PanCamOn.png");		
				}
				else
				{
					strName = _T("开启全景摄像机");
					strPic = _T("res\\mainmenu\\PanCamOff.png");	
				}
			}
			break;
		case emShortcutPicSynthesis:
			{
				if (!bInConf || bIsPTP)//不在会议或者点对点会议不显示
				{
					delete pListContainer;
					continue;
				}
				if (!bChairCns)//不是主席不显示
				{
					delete pListContainer;
					continue;
				}
				if (ComInterface->IsCurtVidMixOpen())
				{
					strName = _T("关闭画面合成");
					strPic = _T("res\\mainmenu\\PicSynthesisOn.png");				
				}
				else
				{
					strName = _T("开启画面合成");
					strPic = _T("res\\mainmenu\\PicSynthesisOff.png");	
				}	
			}
			break;
		case emShortcutCofPoll:
			{
				if (!bInConf || bIsPTP)//不在会议或者点对点会议不显示
				{
					delete pListContainer;
					continue;
				}
				if (!bChairCns)//不是主席不显示
				{
					delete pListContainer;
					continue;
				}
				TTpPollStat tTpPollStat = ComInterface->GetPollState();	
				if (tTpPollStat.m_emStat == EmPollStat_Start || tTpPollStat.m_emStat == EmPollStat_Suspend)
				{
					strName = _T("关闭会议轮询");
					strPic = _T("res\\mainmenu\\CofPollOn.png");
					ICncCommonOp::ShowControl( true, m_pm, _T("BtnIsPause"), pListContainer );

					CButtonUI* pBtn = (CButtonUI*)ICncCommonOp::FindControl(m_pm,_T("BtnIsPause"),pListContainer);
					if (!pBtn)
					{
						return;
					}
					if (tTpPollStat.m_emStat == EmPollStat_Start)
					{
						pBtn->SetAttribute(_T("normalimage"),_T("res\\mainmenu\\pause.png"));
						pBtn->SetAttribute(_T("pushedimage"),_T("res\\mainmenu\\pause.png"));
					}
					else
					{
						pBtn->SetAttribute(_T("normalimage"),_T("res\\mainmenu\\continue.png"));
						pBtn->SetAttribute(_T("pushedimage"),_T("res\\mainmenu\\continue.png"));
					}
				}
				else
				{
					strName = _T("开启会议轮询");
					ICncCommonOp::ShowControl( false, m_pm, _T("BtnIsPause"), pListContainer );
					strPic = _T("res\\mainmenu\\CofPollOff.png");
				}

			}
			break;
		case emShortcutCofRoll:
			{
				if (!bInConf || bIsPTP)//不在会议或者点对点会议不显示
				{
					delete pListContainer;
					continue;
				}
				if (!bChairCns)//不是主席不显示
				{
					delete pListContainer;
					continue;
				}

				TTpConfRollCallInfo tTpConfRollCallInfo;
				ComInterface->GetRollState( tTpConfRollCallInfo );
				if (tTpConfRollCallInfo.m_bStart)
				{
					strName = _T("关闭会议点名");
					strPic = _T("res\\mainmenu\\CofPollOn.png");
				}
				else
				{
					strName = _T("开启会议点名");
					strPic = _T("res\\mainmenu\\CofPollOff.png");
				}

			}
			break;
		case emShortcutCofDiscuss:
			{
				if (!bInConf || bIsPTP)//不在会议或者点对点会议不显示
				{
					delete pListContainer;
					continue;
				}
				if (!bChairCns)//不是主席不显示
				{
					delete pListContainer;
					continue;
				}
				TCMSConf tConfInfo;
				BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
				bool bStart = (bool)tConfInfo.IsStartAudMix();

				if (bStart && bInConf)
				{
					strName = _T("关闭会议讨论");
					strPic = _T("res\\mainmenu\\CofDiscussOn.png");				
				}
				else
				{
					strName = _T("开启会议讨论");
					strPic = _T("res\\mainmenu\\CofDiscussOff.png");	
				}
			}
			break;
		case emShortcutTVWall:
			{
				if (!bInConf || bIsPTP)//不在会议或者点对点会议不显示
				{
					delete pListContainer;
					continue;
				}
				if (!bChairCns)//不是主席不显示
				{
					delete pListContainer;
					continue;
				}

				strName = _T("电视墙");
				//if (ComInterface->IsLocalCnsMute())
				{
					strPic = _T("res\\mainmenu\\TVWallOn.png");				
				}
// 				else
// 				{
// 					strPic = _T("res\\mainmenu\\TVWallOff.png");	
// 				}
			}
			break;
		case emShortcutVoiceAct:
			{
				if (!bInConf )//不在会议不显示
				{
					delete pListContainer;
					continue;
				}

				if (ComInterface->IsLocalMultiVoiceArouse())
				{
					strName = _T("关闭语音激励");
					strPic = _T("res\\mainmenu\\VoiceActOn.png");				
				}
				else
				{
					strName = _T("开启语音激励");
					strPic = _T("res\\mainmenu\\VoiceActOff.png");	
				}
			}
			break;
		case emShortcutPIP:
			{
				if (!bInConf )//不在会议不显示
				{
					delete pListContainer;
					continue;
				}

				if (ComInterface->IsViewLocalPIP())
				{
					strName = _T("关闭画中画");
					strPic = _T("res\\mainmenu\\PIPOn.png");				
				}
				else
				{
					strName = _T("开启画中画");
					strPic = _T("res\\mainmenu\\PIPOff.png");	
				}
			}
			break;
		case emShortcutDulDisplay:
			{	
				if (!bInConf )//不在会议不显示
				{
					delete pListContainer;
					continue;
				}
				if (ComInterface->IsLocalCnsDual())
				{
					strName = _T("关闭双流演示");
					strPic = _T("res\\mainmenu\\DulDisplayOn.png");				
				}
				else
				{
					strName = _T("开启双流演示");
					strPic = _T("res\\mainmenu\\DulDisplayOff.png");	
				}
			}
			break;
		case emShortcutCofMix:
			{	
				if (!bInConf || bIsPTP)//不在会议或者点对点会议不显示
				{
					delete pListContainer;
					continue;
				}
				if (!bChairCns)//不是主席不显示
				{
					delete pListContainer;
					continue;
				}

				TTpAudMixInfo tTpAudMixInfo;
				ComInterface->GetConfMixState( tTpAudMixInfo );

				bool bIsAutoMix = CConfMixLogic::GetSingletonPtr()->IsAutoMix();

				if (tTpAudMixInfo.m_emMode != em_umsaudmixmode_idle)//已经开启
				{
					if (bIsAutoMix)
					{
						strName = _T("关闭智能混音");
					}
					else
					{
						strName = _T("关闭定制混音");
					}
					
					strPic = _T("res\\mainmenu\\ConfMixOn.png");				
				}
				else
				{
					if (bIsAutoMix)
					{
						strName = _T("开启智能混音");
					}
					else
					{
						strName = _T("开启定制混音");
					}
 					strPic = _T("res\\mainmenu\\ConfMixOff.png");	
 				}
			}
			break;
		}

		ICncCommonOp::SetControlText( strName, m_pm, _T("lbName"), pListContainer );
		ICncCommonOp::SetControlBkImg( strPic, m_pm, _T("BtnShortCutState"), pListContainer );
		pListContainer->SetTag(emShortcutType);
		pShortCutList->Add(pListContainer);
	}
}

bool CMainMenuLogic::OnBtnPollPause( TNotifyUI& msg )
{
	TTpPollStat tTTpPollStat = ComInterface->GetPollState();
	bool bPause = false;
	if (tTTpPollStat.m_emStat == EmPollStat_Suspend)
	{
		bPause = true;
	}

	u16 wRet = ComInterface->PollPauseCmd(!bPause);
	if (wRet != NO_ERROR)
	{
		ShowMessageBox(_T("暂停控制失败"));
		return false;
	}
	return true;
}

bool CMainMenuLogic::OnBtnShortCutListSet( TNotifyUI& msg )
{
	EM_ShortcutType emShortcutType;
	if (CListContainerElementUI* pList = (CListContainerElementUI*)msg.pSender->GetParent()->GetParent()->GetParent())
	{
		emShortcutType = (EM_ShortcutType)pList->GetTag();
	}

	NOTIFY_MSG( UI_CNC_SHOW_SHORTCUTDLG_NTY, emShortcutType, NULL );
	switch(emShortcutType)
	{
	case emShortcutMute:
	case emShortcutSilence:
	case emShortcutPanCam:
		{
			CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("会场管理"));
			CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgRoomCtrl.png"));
			WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
			UIDATAMGR->SetCurShowWndName( g_strRoomControlDlg );
			WINDOW_MGR_PTR->ShowWindowFromLeftToRight(g_strRoomControlDlg.c_str() );
		}
		break;

	case emShortcutPicSynthesis:
	case emShortcutCofPoll:
	case emShortcutCofDiscuss:
	case emShortcutVoiceAct:
	case emShortcutPIP:
	case emShortcutDulDisplay:
	case emShortcutCofRoll:
	case emShortcutCofMix:
    case emShortcutTVWall:
		{
			CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("会议管理"));
			CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgConfCtrl.png"));
			WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
			UIDATAMGR->SetCurShowWndName( g_strConfCtrlDlg );
			WINDOW_MGR_PTR->ShowWindowFromLeftToRight(g_strConfCtrlDlg.c_str() );
		}
		break;
	}

	return true;

}

bool CMainMenuLogic::OnConfStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	TCMSConf tConfInfo;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
	if ( bInConf )
	{  

		bool bIsPTP = false;
		if (tConfInfo.m_emConfType == emCallType_P2P)
		{
			m_pm->DoCase( _T("caseMenuInConf") );
		}
		else
		{
			if (ComInterface->IsLocalCnsChairMan())
			{
				m_pm->DoCase( _T("caseMenuInConf") );
			}
			else
			{
				m_pm->DoCase( _T("caseMenuInConfMultNoChair") );
			}
		}  
    }
    else
    {
        m_pm->DoCase( _T("caseMenuNotInConf") );
    }

	UpdateShortCutLst();
	return true;
}

bool CMainMenuLogic::OnPanCamStartNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	GetItemContainer(emShortcutPanCam);
	if (!m_pContainerElementUI)
	{
		return false;
	}
	if ( ComInterface->IsLocalCnsPanCam() )
	{
		ICncCommonOp::SetControlBkImg( _T("res\\mainmenu\\PanCamOn.png"), m_pm, _T("BtnShortCutState"), m_pContainerElementUI );
		ICncCommonOp::SetControlText( _T("关闭全景摄像机"), m_pm, _T("lbName"), m_pContainerElementUI );
	}
	else
	{
		ICncCommonOp::SetControlBkImg( _T("res\\mainmenu\\PanCamOff.png"), m_pm, _T("BtnShortCutState"), m_pContainerElementUI );
		ICncCommonOp::SetControlText( _T("开启全景摄像机"), m_pm, _T("lbName"), m_pContainerElementUI );
	}
	m_pContainerElementUI = NULL;
	return true;
}


bool CMainMenuLogic::OnPIPInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	u8 byScrnID = (u8)wParam; 
	EmTPViewLocalResult emRe = (EmTPViewLocalResult)lParam;
	GetItemContainer(emShortcutPIP);
	if (!m_pContainerElementUI)
	{
		return false;
	}
	if ( emRe == emViewLocalSucceed )
	{
		CString strName = _T("");
		CString strPic = _T("");
		if (ComInterface->IsViewLocalPIP())
		{
			strName = _T("关闭画中画");
			strPic = _T("res\\mainmenu\\PIPOn.png");				
		}
		else
		{
			strName = _T("开启画中画");
			strPic = _T("res\\mainmenu\\PIPOff.png");	
		}

		ICncCommonOp::SetControlBkImg( strPic, m_pm, _T("BtnShortCutState"), m_pContainerElementUI );
		ICncCommonOp::SetControlText( strName, m_pm, _T("lbName"), m_pContainerElementUI );
	}

	return S_OK;
}

bool CMainMenuLogic::OnPIPNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	u8 byScrnID = (u8)wParam; 
	BOOL bLocalPIP = (BOOL)lParam;

	GetItemContainer(emShortcutPIP);
	if (!m_pContainerElementUI)
	{
		return false;
	}
	CString strName = _T("");
	CString strPic = _T("");
	if (ComInterface->IsViewLocalPIP())
	{
		strName = _T("关闭画中画");
		strPic = _T("res\\mainmenu\\PIPOn.png");				
	}
	else
	{
		strName = _T("开启画中画");
		strPic = _T("res\\mainmenu\\PIPOff.png");	
	}

	ICncCommonOp::SetControlBkImg( strPic, m_pm, _T("BtnShortCutState"), m_pContainerElementUI );
	ICncCommonOp::SetControlText( strName, m_pm, _T("lbName"), m_pContainerElementUI );

	return S_OK;
}

bool CMainMenuLogic::OnCnsDualRsp( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	GetItemContainer(emShortcutDulDisplay);

	if (!m_pContainerElementUI)
	{
		return false;
	}

	CString strName = _T("");
	CString strPic = _T("");
	if (ComInterface->IsLocalCnsDual())
	{
		strName = _T("关闭双流演示");
		strPic = _T("res\\mainmenu\\DulDisplayOn.png");				
	}
	else
	{
		strName = _T("开启双流演示");
		strPic = _T("res\\mainmenu\\DulDisplayOff.png");	
	}

	ICncCommonOp::SetControlBkImg( strPic, m_pm, _T("BtnShortCutState"), m_pContainerElementUI );
	ICncCommonOp::SetControlText( strName, m_pm, _T("lbName"), m_pContainerElementUI );
	

	return S_OK;
}

bool CMainMenuLogic::OnRollStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TTpConfRollCallInfo tTpConfRollCallInfo;//点名状态信息
	ComInterface->GetRollState( tTpConfRollCallInfo );

	GetItemContainer(emShortcutCofRoll);
	if (!m_pContainerElementUI)
	{
		return false;
	}
	if ( tTpConfRollCallInfo.m_bStart )
	{
		ICncCommonOp::SetControlBkImg( _T("res\\mainmenu\\CofPollOn.png"), m_pm, _T("BtnShortCutState"), m_pContainerElementUI );
		ICncCommonOp::SetControlText( _T("关闭会议点名"), m_pm, _T("lbName"), m_pContainerElementUI );
	}
	else
	{
		ICncCommonOp::SetControlBkImg( _T("res\\mainmenu\\CofPollOff.png"), m_pm, _T("BtnShortCutState"), m_pContainerElementUI );	
		ICncCommonOp::SetControlText( _T("开启会议点名"), m_pm, _T("lbName"), m_pContainerElementUI );
	}

	m_pContainerElementUI = NULL;
	return true;
}

bool CMainMenuLogic::OnConfMixStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	UpdateConfMixState();
	return true;
}

void CMainMenuLogic::UpdateConfMixState()
{
	TTpAudMixInfo tTpAudMixInfo;//混音状态信息
	ComInterface->GetConfMixState( tTpAudMixInfo );

	GetItemContainer(emShortcutCofMix);
	if (!m_pContainerElementUI)
	{
		return;
	}

	bool bIsAutoMix = CConfMixLogic::GetSingletonPtr()->IsAutoMix();
	if (tTpAudMixInfo.m_emMode != em_umsaudmixmode_idle)//已经开启
	{
		ICncCommonOp::SetControlBkImg( _T("res\\mainmenu\\ConfMixOn.png"), m_pm, _T("BtnShortCutState"), m_pContainerElementUI );
		if (bIsAutoMix)
		{
			ICncCommonOp::SetControlText( _T("关闭智能混音"), m_pm, _T("lbName"), m_pContainerElementUI );
		}
		else
		{
			ICncCommonOp::SetControlText( _T("关闭定制混音"), m_pm, _T("lbName"), m_pContainerElementUI );
		}
	}
	else
	{
		ICncCommonOp::SetControlBkImg( _T("res\\mainmenu\\ConfMixOff.png"), m_pm, _T("BtnShortCutState"), m_pContainerElementUI );
		if (bIsAutoMix)
		{
			ICncCommonOp::SetControlText( _T("开启智能混音"), m_pm, _T("lbName"), m_pContainerElementUI );	
		}
		else
		{
			ICncCommonOp::SetControlText( _T("开启定制混音"), m_pm, _T("lbName"), m_pContainerElementUI );	
		}
	}

	m_pContainerElementUI = NULL;
}

bool CMainMenuLogic::OnMuteOrSliencNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL32 bQuiet = (BOOL32)wParam;
	BOOL32 bSucess = (BOOL32)lParam;

	if (bQuiet)
	{
		GetItemContainer(emShortcutSilence);
		if (!m_pContainerElementUI)
		{
			return false;
		}
		if ( bSucess)
		{
            ICncCommonOp::SetControlText( _T("开启扬声器"), m_pm, _T("lbName"), m_pContainerElementUI );
			ICncCommonOp::SetControlBkImg( _T("res\\mainmenu\\SilenceOn.png"), m_pm, _T("BtnShortCutState"), m_pContainerElementUI );
		}
		else
		{
            ICncCommonOp::SetControlText( _T("关闭扬声器"), m_pm, _T("lbName"), m_pContainerElementUI );
			ICncCommonOp::SetControlBkImg( _T("res\\mainmenu\\SilenceOff.png"), m_pm, _T("BtnShortCutState"), m_pContainerElementUI );	
		}
	}
	else
	{
		GetItemContainer(emShortcutMute);
		if (!m_pContainerElementUI)
		{
			return false;
		}
		if ( bSucess)
		{
            ICncCommonOp::SetControlText( _T("开启麦克风"), m_pm, _T("lbName"), m_pContainerElementUI );
			ICncCommonOp::SetControlBkImg( _T("res\\mainmenu\\MuteOn.png"), m_pm, _T("BtnShortCutState"), m_pContainerElementUI );
		}
		else
		{
            ICncCommonOp::SetControlText( _T("关闭麦克风"), m_pm, _T("lbName"), m_pContainerElementUI );
			ICncCommonOp::SetControlBkImg( _T("res\\mainmenu\\MuteOff.png"), m_pm, _T("BtnShortCutState"), m_pContainerElementUI );
		}
	}

	m_pContainerElementUI = NULL;
	return true;
}

bool CMainMenuLogic::OnPollStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL32 bIsSuccess = FALSE;
	TTpPollStat tTpPollStat = ComInterface->GetPollState();	
	GetItemContainer(emShortcutCofPoll);
	if (!m_pContainerElementUI)
	{
		return false;
	}
	if (tTpPollStat.m_emStat == EmPollStat_Start || tTpPollStat.m_emStat == EmPollStat_Suspend)
	{
		ICncCommonOp::ShowControl( true, m_pm, _T("BtnIsPause"), m_pContainerElementUI );
		bIsSuccess = TRUE;
		CButtonUI* pBtn = (CButtonUI*)ICncCommonOp::FindControl(m_pm,_T("BtnIsPause"),m_pContainerElementUI);
		if (!pBtn)
		{
			return false;
		}
		if (tTpPollStat.m_emStat == EmPollStat_Start)
		{
			pBtn->SetAttribute(_T("normalimage"),_T("res\\mainmenu\\pause.png"));
			pBtn->SetAttribute(_T("pushedimage"),_T("res\\mainmenu\\pause.png"));
		}
		else
		{
			pBtn->SetAttribute(_T("normalimage"),_T("res\\mainmenu\\continue.png"));
			pBtn->SetAttribute(_T("pushedimage"),_T("res\\mainmenu\\continue.png"));
		}
	}
	
	if (!m_pContainerElementUI)
	{
		return false;
	}
	if ( bIsSuccess)
	{
		ICncCommonOp::SetControlBkImg( _T("res\\mainmenu\\CofPollOn.png"), m_pm, _T("BtnShortCutState"), m_pContainerElementUI );
		ICncCommonOp::SetControlText( _T("关闭会议轮询"), m_pm, _T("lbName"), m_pContainerElementUI );
	}
	else
	{
		ICncCommonOp::ShowControl( false, m_pm, _T("BtnIsPause"), m_pContainerElementUI );
		ICncCommonOp::SetControlBkImg( _T("res\\mainmenu\\CofPollOff.png"), m_pm, _T("BtnShortCutState"), m_pContainerElementUI );
		ICncCommonOp::SetControlText( _T("开启会议轮询"), m_pm, _T("lbName"), m_pContainerElementUI );
	}
	m_pContainerElementUI = NULL;
	return true;
}

bool CMainMenuLogic::OnPollPauseInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	EmTPPollResult em = (EmTPPollResult)wParam;
	if (em == emPollSucceed)
	{
		return true;
	}
	
	TTpPollStat tTpPollStat = ComInterface->GetPollState();	
	GetItemContainer( emShortcutCofPoll );
	if (!m_pContainerElementUI)
	{
		return false;
	}
	CButtonUI* pBtn = (CButtonUI*)ICncCommonOp::FindControl(m_pm,_T("BtnIsPause"),m_pContainerElementUI);
	if (!pBtn)
	{
		return false;
	}
	if (tTpPollStat.m_emStat == EmPollStat_Start)
	{
		pBtn->SetAttribute(_T("normalimage"),_T("res\\mainmenu\\pause.png"));
		pBtn->SetAttribute(_T("pushedimage"),_T("res\\mainmenu\\pause.png"));
	}
	else
	{
		pBtn->SetAttribute(_T("normalimage"),_T("res\\mainmenu\\continue.png"));
		pBtn->SetAttribute(_T("pushedimage"),_T("res\\mainmenu\\continue.png"));
	}

	return true;
}

void CMainMenuLogic::GetItemContainer( EM_ShortcutType emShortcutType )
{
	m_pContainerElementUI = NULL;
	CTouchListUI* pShortCutList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("ShortCutList") );
	if ( pShortCutList == NULL )
	{
		return ;
	}

	for ( int dwIndex = 0; dwIndex < pShortCutList->GetCount(); dwIndex++)
	{
		CListContainerElementUI* pList = (CListContainerElementUI*)pShortCutList->GetItemAt(dwIndex);
		if (pList->GetTag() == emShortcutType )
		{
			m_pContainerElementUI = pList;
			break;
		}
	}
}

bool CMainMenuLogic::OnStartConfDiscNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TCMSConf tConfInfo;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
	if ( ! bInConf )
	{
		return NO_ERROR;
	}

	//更新控件
	bool bStart = (bool)tConfInfo.IsStartAudMix();	
	GetItemContainer(emShortcutCofDiscuss);
	if (!m_pContainerElementUI)
	{
		return false;
	}
	if ( bStart)
	{
		ICncCommonOp::SetControlBkImg( _T("res\\mainmenu\\CofDiscussOn.png"), m_pm, _T("BtnShortCutState"), m_pContainerElementUI );
		ICncCommonOp::SetControlText( _T("关闭会议讨论"), m_pm, _T("lbName"), m_pContainerElementUI );
	}
	else
	{
		ICncCommonOp::SetControlBkImg( _T("res\\mainmenu\\CofDiscussOff.png"), m_pm, _T("BtnShortCutState"), m_pContainerElementUI );	
		ICncCommonOp::SetControlText( _T("开启会议讨论"), m_pm, _T("lbName"), m_pContainerElementUI );
	}
	

	m_pContainerElementUI = NULL;
	return true;
}

void CMainMenuLogic::SaveShortCutToIni()
{
	//全场静音哑音不需要保存到配置文件
	for ( std::vector< EM_ShortcutType >::const_iterator iter = m_vctShortCutList.begin(); iter != m_vctShortCutList.end(); )
	{
		if ( *iter == emShortcutMuteAll || *iter == emShortcutQuiteAll )
		{
			iter = m_vctShortCutList.erase(iter);
		}
		else
		{
			iter++;
		}
	}	
	//记录到ini文件 
	CString strIniPath = CMainFrameLogic::GetSingletonPtr()->GetIniFilePath();
	CString strId = _T("");
	CString strName = _T("");
	u32 dwSize = m_vctShortCutList.size();
	CString strSize = _T("");
	strSize.Format(_T("%d"),dwSize);
	WritePrivateProfileString(_T("ShortCutInfo"),_T("Size"),strSize,strIniPath);

	for (int i = 0; i < m_vctShortCutList.size(); i++)
	{
		strName.Format(_T("Shortcut%d"),i);
		strId.Format(_T("%d"), m_vctShortCutList.at(i));
		WritePrivateProfileString(_T("ShortCutInfo"), strName, strId, strIniPath);
	}
}

bool CMainMenuLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	if (m_bExtend)
	{
		if (g_nExtendTimerID != 0)
		{
			KillTimer( NULL, g_nExtendTimerID );
			g_nExtendTimerID = 0;
		}

		RECT rcWnd;
		::GetClientRect(m_hWnd, &rcWnd);

// 		RECT rcParentWnd;
// 		::GetClientRect(GetParent(m_hWnd), &rcParentWnd);

//		int nTop = rcParentWnd.bottom - m_nMainMenuInitHeight;
        int nTop = UIDATAMGR->GetCncMainPos().cy - m_nMainMenuInitHeight;
		SetWindowPos( m_hWnd, NULL, rcWnd.left, nTop, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );

		m_bExtend = FALSE;
        m_pm->DoCase( _T("caseMainMenuBack") );
		m_pBtnMsg->SetPos(m_rectBtnMsg);
		m_pBtnSysCfg->SetPos(m_rectBtnCfg);
	}
	m_pContainerElementUI = NULL;

	//断链恢复无会议的menu方案，更新快捷方式
	m_pm->DoCase( _T("caseMenuNotInConf") );
	UpdateShortCutLst();
	WINDOW_MGR_PTR->ShowWindow( g_strMainMenuDlg.c_str(), false );
	return true;
}

bool CMainMenuLogic::OnBtnShortCutState( TNotifyUI& msg )
{
	EM_ShortcutType emShortcutType;
	if (CListContainerElementUI* pList = (CListContainerElementUI*)msg.pSender->GetParent()->GetParent()->GetParent())
	{
		emShortcutType = (EM_ShortcutType)pList->GetTag();
	}

	BOOL32 bIsSet;
	u16 wRe =  NO_ERROR;
	switch(emShortcutType)
	{
	case emShortcutMute:
		{
			bIsSet = ComInterface->IsLocalCnsMute();	
			wRe =  ComInterface->SetLocalCnsMute(!bIsSet);
		}
		break;
	case emShortcutSilence:
		{
			bIsSet = ComInterface->IsLocalCnsQuite();
			wRe =  ComInterface->SetLocalCnsQuite(!bIsSet);
		}
		break;
	case emShortcutPanCam:
		{
			bIsSet = ComInterface->IsLocalCnsPanCam();
			int nCamID = CPanCamLogic::GetSingletonPtr()->GetCamID(); 
			wRe =  ComInterface->SetLocalCnsPanCam(nCamID,!bIsSet);
		}
		break;
	case emShortcutPicSynthesis:
		{
			TCMSConf tConf;
			BOOL32 bInConf = ComInterface->IsInConf( &tConf );
			if (!bInConf)
			{
				ShowMessageBox(_T("不在会议中，不可进行此操作"),false);
				break;
			}

			NOTIFY_MSG( UI_CNC_SHORTCUT_VMIX, NULL, NULL );		
		}
		break;
	case emShortcutCofPoll:
		{
			TCMSConf tConf;
			BOOL32 bInConf = ComInterface->IsInConf( &tConf );
			if (!bInConf)
			{
				ShowMessageBox(_T("不在会议中，不可进行此操作"),false);
				break;
			}

			NOTIFY_MSG( UI_CNC_SHORTCUT_POLL, NULL, NULL );			
		}
		break;
	case emShortcutCofRoll:
		{
			TCMSConf tConf;
			BOOL32 bInConf = ComInterface->IsInConf( &tConf );
			if (!bInConf)
			{
				ShowMessageBox(_T("不在会议中，不可进行此操作"),false);
				break;
			}

			NOTIFY_MSG( UI_CNC_SHORTCUT_ROLL, NULL, NULL );			
		}
		break;
	case emShortcutCofDiscuss:
		{

			TCMSConf tConf;
			BOOL32 bInConf = ComInterface->IsInConf( &tConf );
			bIsSet = tConf.IsStartAudMix();	
			if (!bInConf)
			{
				ShowMessageBox(_T("不在会议中，不可进行此操作"),false);
				break;
			}

			//TTPCnsConfStatus tConfStatus = ComInterface->GetLocalCnsConfState();
			//BOOL bVacStart = tConf.IsVacOn();//(bool)tConfStatus.m_bMixMotive;

			u16 wConfID = tConf.m_wConfID;
			TConfAuxMixInfo tMixInfoList;
			tMixInfoList.m_wConfID = wConfID;
			tMixInfoList.m_bStart = !bIsSet;
			tMixInfoList.m_bVacOn = FALSE;
			tMixInfoList.m_atAuxMixList = tConf.m_tAudmixList;
			wRe =  ComInterface->UpdateAudMixList( tMixInfoList );
		}
		break;
// 	case emShortcutTVWall:
// 		{
// 		}
// 		break;
	case emShortcutVoiceAct:
		{
			TCMSConf tConf;
			BOOL32 bInConf = ComInterface->IsInConf( &tConf );
			if (!bInConf)
			{
				ShowMessageBox(_T("不在会议中，不可进行此操作"),false);
				break;
			}
            TTPVacInfo tTPVacInfo;
			bIsSet = ComInterface->IsLocalMultiVoiceArouse();
            tTPVacInfo.m_wConfId = tConf.m_tPollStat.m_wConfID;
            tTPVacInfo.m_bVoiceMotivation = !bIsSet;
			wRe =  ComInterface->SetVoiceArouse( tTPVacInfo );
		}
		break;
	case emShortcutPIP:
		{
			bIsSet = ComInterface->IsViewLocalPIP();	
			wRe =  ComInterface->ViewLocalPIPCmd(1,!bIsSet);
		}
		break;
	case emShortcutDulDisplay:
		{
			TCMSConf tConf;
			BOOL32 bInConf = ComInterface->IsInConf( &tConf );
			if (!bInConf)
			{
				ShowMessageBox(_T("不在会议中，不可进行此操作"),false);
				break;
			}
			bIsSet = ComInterface->IsLocalCnsDual();	
			wRe =  ComInterface->StartDual(!bIsSet);	
		}
		break;
	case emShortcutCofMix:
		{
			TCMSConf tConf;
			BOOL32 bInConf = ComInterface->IsInConf( &tConf );
			if (!bInConf)
			{
				ShowMessageBox(_T("不在会议中，不可进行此操作"),false);
				break;
			}

			NOTIFY_MSG( UI_CNC_SHORTCUT_CONFMIX, NULL, NULL );			
		}
		break;
	case emShortcutMuteAll:
		{
			TCMSConf tConf;
			BOOL32 bInConf = ComInterface->IsInConf( &tConf );
			if (!bInConf || tConf.m_emConfType == emCallType_P2P)
			{
				ShowMessageBox(_T("不可进行此操作"),FALSE);
				break;
			}
			NOTIFY_MSG( UI_CNC_SHORTCUT_MUTEALL, NULL, NULL );
		}
		break;
	case emShortcutQuiteAll:
		{
			TCMSConf tConf;
			BOOL32 bInConf = ComInterface->IsInConf( &tConf );
			if (!bInConf || tConf.m_emConfType == emCallType_P2P)
			{
				ShowMessageBox(_T("不可进行此操作"),FALSE);
				break;
			}
			NOTIFY_MSG( UI_CNC_SHORTCUT_QUITEALL, NULL, NULL );
		}
		break;
	}

	if ( wRe != NO_ERROR )
	{
		ShowMessageBox(_T("操作失败"));
	}
	return true;
}

bool CMainMenuLogic::OnVoiceArouseInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	GetItemContainer(emShortcutVoiceAct);
	if (!m_pContainerElementUI)
	{
		return false;
	}
	CString strName = _T("");
	CString strPic = _T("");
	if (ComInterface->IsLocalMultiVoiceArouse())
	{
		strName = _T("关闭语音激励");
		strPic = _T("res\\mainmenu\\VoiceActOn.png");				
	}
	else
	{
		strName = _T("开启语音激励");
		strPic = _T("res\\mainmenu\\VoiceActOff.png");	
	}

	ICncCommonOp::SetControlBkImg( strPic, m_pm, _T("BtnShortCutState"), m_pContainerElementUI );
	ICncCommonOp::SetControlText( strName, m_pm, _T("lbName"), m_pContainerElementUI );


	return S_OK;
}

bool CMainMenuLogic::OnVidMIxStatusNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    //更新控件
    bool bOpen = ComInterface->IsCurtVidMixOpen();	
    GetItemContainer(emShortcutPicSynthesis);
    if (!m_pContainerElementUI)
    {
        return false;
    }
    if ( bOpen)
    {
        ICncCommonOp::SetControlBkImg( _T("res\\mainmenu\\PicSynthesisOn.png"), m_pm, _T("BtnShortCutState"), m_pContainerElementUI );
		ICncCommonOp::SetControlText( _T("关闭画面合成"), m_pm, _T("lbName"), m_pContainerElementUI );
    }
    else
    {
        ICncCommonOp::SetControlBkImg( _T("res\\mainmenu\\PicSynthesisOff.png"), m_pm, _T("BtnShortCutState"), m_pContainerElementUI );	
		ICncCommonOp::SetControlText( _T("开启画面合成"), m_pm, _T("lbName"), m_pContainerElementUI );
    }
    m_pContainerElementUI = NULL;
    return true;
}

bool CMainMenuLogic::OnContainerClick( TNotifyUI& msg )
{
	CCnsManageLogic::GetSingletonPtr()->UnSelScreenList();
	return true;
}