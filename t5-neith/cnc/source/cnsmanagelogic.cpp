#include "StdAfx.h"
#include "cnsmanagelogic.h"
#include "mainframelogic.h"
#include "confmsglogic.h"
#include "srcselwatch.h"

template<> CCnsManageLogic* Singleton<CCnsManageLogic>::ms_pSingleton  = NULL;

const String CCnsManageLogic::strCnsScreenList = _T("CnsScreenList");
const String CCnsManageLogic::strCnsScreenListItem = _T("CnsScreenListItem");

u16  g_wConfTimerID = 0; 
u16  g_wSpareDualStateTimerID = 0; 
static UINT g_nTVWallLWaiting = 0;//电视墙发送开启后3s不能点击
static UINT g_nTVWallRWaiting = 0;//电视墙发送开启后3s不能点击


#define  MARGIN_RIGHT        35
#define  MARGIN_TOP          117
#define  LABLE_INTERVAL      20

APP_BEGIN_MSG_MAP(CCnsManageLogic, CNotifyUIImpl)
	MSG_ITEMCLICK(_T("CnsScreenListItem"), OnCnsScreenItemClick)  
	MSG_CLICK(_T("BtnScrSelWatch"), OnBtnScrSelWatch)
	MSG_CLICK(_T("BtnCancelSelWatch"), OnBtnCancelSelWatch)

	MSG_CLICK(_T("btnSpeakSeat1"), OnBtnSpeakSeat1)
	MSG_CLICK(_T("btnSpeakSeat2"), OnBtnSpeakSeat2)
	MSG_CLICK(_T("btnSpeakSeat3"), OnBtnSpeakSeat3)
	//回显
	MSG_SELECTCHANGE(_T("BtnScrLocal"), OnCheckScrLocal)
	USER_MSG(UI_CNS_SCRN_DISPLAY_LOCAL_RSP,OnSelLocalRsp)
	USER_MSG(UI_CNS_STOP_SCRN_DISPLAY_LOCAL_RSP,OnCancleSelLocalRsp)
	//双流
	MSG_SELECTCHANGE(_T("BtnScrDual"), OnCheckDualView)
	USER_MSG(UI_CNS_SCRN_DISPLAY_DUAL_RSP,OnSelDualViewRsp)
	USER_MSG(UI_CNS_STOP_SCRN_DISPLAY_DUAL_RSP ,OnCancleDualViewRsp)
	//空闲时双流
	USER_MSG(UI_CNS_SPAREDUAL_IND,OnSpareSelDualViewInd)
	USER_MSG(UI_CNS_SPAREDUAL_NTY,OnSpareSelDualViewNty)
	//电视墙
	MSG_SELECTCHANGE(_T("BtnTVWall"), OnCheckTVWView)
	USER_MSG(UI_CNS_SEL_TVSVIEW_RSP,OnSelTVSViewRsp)
	USER_MSG(UI_CNS_CANCLE_SEL_TVSVIEW_RSP,OnCancleSelTVSViewRsp)

	USER_MSG(UI_CNS_CONFSTATE_NOTIFY,OnConfStateNotify)
	USER_MSG(UI_UMS_REFRESH_CONFCNS_LIST,OnRefreshConfCnsList)
    
	USER_MSG(UI_CNS_SEL_VIEW_IND,OnSelViewInd)

	//USER_MSG(UI_CNS_SEL_VIEW_NTY,OnCancelSelViewRsp) 

	USER_MSG(UI_CNS_SCREEN_STATE_NOTIFY,OnScreenStateNty)
	USER_MSG(UI_CNS_SPOKES_SEAT_NOTIFY,OnSpokesManNotify)
	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)

	USER_MSG(UI_CNS_QUITE_MUTE,OnMuteOrSilencNty)
	//USER_MSG(UI_CNS_CONFMIX_NTY,OnConfMixStateNty)

	USER_MSG(UI_CNC_INAUDMIX_NTY,OnEpInAudMixNty)

APP_END_MSG_MAP()




VOID  CALLBACK  CBTimerFun( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{  
	if ( idEvent == g_wConfTimerID)
	{
		CCnsManageLogic::GetSingletonPtr()->UpdateConfTime();
	}
	if ( idEvent == g_wSpareDualStateTimerID)
	{
		CCnsManageLogic::GetSingletonPtr()->RefreshScreenDual(0);
		CCnsManageLogic::GetSingletonPtr()->RefreshScreenDual(1);
		CCnsManageLogic::GetSingletonPtr()->RefreshScreenDual(2);

		KillTimer(NULL,g_wSpareDualStateTimerID);
		g_wSpareDualStateTimerID = 0;
	}
	if ( idEvent == g_nTVWallRWaiting)
	{
		KillTimer(NULL,g_nTVWallRWaiting);
		g_nTVWallRWaiting = 0;
		CCnsManageLogic::GetSingletonPtr()->EnableTVWall(2);
	}
	if ( idEvent == g_nTVWallLWaiting)
	{
		KillTimer(NULL,g_nTVWallLWaiting);
		g_nTVWallLWaiting = 0;
		CCnsManageLogic::GetSingletonPtr()->EnableTVWall(0);
	}
}


CCnsManageLogic::CCnsManageLogic(void) : m_pSrceenList(NULL)
{
	m_nSelIndex = -1;
    m_bInConf = false;
    m_dwConfStartTime = 0;
	m_bIsSpareDual = false;
}


CCnsManageLogic::~CCnsManageLogic(void)
{
}

void CCnsManageLogic::UnSelScreenList()
{
	CTouchListUI *pScreenList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("CnsScreenList") ); 
	if (pScreenList && pScreenList->GetCurSel() != -1)
	{
		if (pScreenList->GetItemAt(pScreenList->GetCurSel()))
		{
			m_pm->DoCase( _T("caseScreenNoSel"), pScreenList->GetItemAt(pScreenList->GetCurSel()) );
			m_nSelIndex = -1;
			pScreenList->SelectItem(-1);
		}
	}
}

bool CCnsManageLogic::OnCnsScreenItemClick(TNotifyUI& msg)
{
	if ( const CListContainerElementUI *pItem = dynamic_cast<const CListContainerElementUI*>(msg.pSender) )
	{
		int nIndex = pItem->GetIndex();
		if ( m_nSelIndex == -1 )
		{
            UpdateScreenMenu( nIndex, msg.pSender );
			m_pm->DoCase( _T("caseScreenSel"), msg.pSender );
			m_nSelIndex = nIndex;
		}
		else
		{
			if ( m_nSelIndex == nIndex )
			{
				m_pm->DoCase( _T("caseScreenNoSel"), msg.pSender );
 				m_nSelIndex = -1;
			}
			else
			{
				CControlUI *pLastSel = m_pSrceenList->GetItemAt(m_nSelIndex);
				m_pm->DoCase( _T("caseScreenNoSel"), pLastSel );

                UpdateScreenMenu( nIndex, msg.pSender );
				m_pm->DoCase( _T("caseScreenSel"), msg.pSender );
				m_nSelIndex = nIndex;
			}
		}
	}
	return true;
}


void CCnsManageLogic::InitCnsScreenList()
{
	m_pSrceenList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, strCnsScreenList.c_str() );
	if ( m_pSrceenList == NULL )
	{
		return;
	}

	for ( u16 i = 0; i < 3; i++ )
	{
		CListContainerElementUI *pListContainer = 
			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( strCnsScreenListItem.c_str() );

        if ( UIDATAMGR->IsPcVersion() )
        {
            m_pm->DoCase(_T("caseIsPc"), pListContainer);
        }
        else
        {
            m_pm->DoCase(_T("caseIsPad"), pListContainer);
        }

		m_pSrceenList->Add(pListContainer);
	}
}


void CCnsManageLogic::UpdateScreenMenu( u8 bSrcnID, CControlUI *pParent )
{   
    TScreenInfo tScrnInfo;

    u16 re = ComInterface->GetCnsScreenInfoByID( bSrcnID, tScrnInfo );

	CString strScreenPic = _T("res/cnsmanage/screenperson.png");
	CString strlbscreentip = _T("");
	if ( NO_ERROR == re )
	{
		if (!m_bInConf)//空闲 双流
		{
			if (tScrnInfo.emPosPic == emPic_SelDual || tScrnInfo.emPosPic == emPic_Dual)//nlf确认 sel的和没sel的是一样的 dyy 2015-6-24
			{   
				strScreenPic = _T("res/cnsmanage/screendual.png");
				strlbscreentip = _T("双流");
			}
		}
		else
		{
			BOOL32 bIsTVWALL = ComInterface->GetDisplayState();

			if ( bIsTVWALL )
			{
				if ( tScrnInfo.byScreenID != 1 && emPic_SelTVS ==  tScrnInfo.emPosPic)
				{
					strScreenPic = _T("res/cnsmanage/screentvwall.png");
					strlbscreentip = _T("电视墙");
				}
			}

			//BOOL32 bIsRcvDual = ComInterface->IsRcvDual();//会场选看时是0
			if ( /*bIsRcvDual &&*/ tScrnInfo.emPosPic == emPic_SelDual || tScrnInfo.emPosPic == emPic_Dual)
			{   
				strScreenPic = _T("res/cnsmanage/screendual.png");
				strlbscreentip = _T("双流");
			}

			//选看
			TCMSConf tConfInfo;
			BOOL32 bInconf = ComInterface->IsInConf( &tConfInfo );
			if ( bInconf )
			{
				if ( tConfInfo.m_emConfType != emCallType_P2P )
				{
					/*BOOL32 bChairCns = ComInterface->IsLocalCnsChairMan();*/
					if ( /*bChairCns &&*/ tScrnInfo.emPosPic == emPic_SelView )
					{
						strScreenPic = _T("res/cnsmanage/screenselwatch.png");
						strlbscreentip = _T("选看");
					}
				}
			}
		}
	}

	ICncCommonOp::SetControlBkImg(strScreenPic,m_pm,_T("imgScreenPic"),pParent);
	ICncCommonOp::SetControlText(strlbscreentip,m_pm,_T("lbscreentip"),pParent);

	if ( !m_bInConf )
	{
		m_pm->DoCase( _T("caseScrNoLocal"), pParent );
		m_pm->DoCase( _T("caseNoSelWatch"), pParent );
		m_pm->DoCase( _T("caseNoTVWall"), pParent );

		//演示
		if ( tScrnInfo.emPosPic == emPic_SelDual  || tScrnInfo.emPosPic == emPic_Dual)
		{
			m_pm->DoCase( _T("caseScrCancelDual"), pParent );
		}
		else
		{
			m_pm->DoCase( _T("caseScrDual"), pParent );
		}
		
		return ;
		
	}
    if ( NO_ERROR == re )
    {
		//电视墙
		BOOL32 bIsTVWALL = ComInterface->GetDisplayState();
		
		if ( bIsTVWALL )
		{			
            TCentreTVCfg  atTVCfg[MAX_CENTRETV_NUM];
            memcpy( atTVCfg , ComInterface->GetCentreTVCfg(), sizeof(TCentreTVCfg) * MAX_CENTRETV_NUM );

			if ( tScrnInfo.byScreenID == 1 || atTVCfg->emTvModle == emSharp70LX565A)		//只有1、3屏幕选看按钮才可用 || emSharp70LX565A不支持
			{
				m_pm->DoCase( _T("caseDisabledTVWall"), pParent );
			}
			else
			{
                CCheckBoxUI* pCheck = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("BtnTVWall"),pParent);
                if (pCheck)
                {
                    bool bIsCheck = pCheck->IsSelected();
                    if (bIsCheck != (emPic_SelTVS ==  tScrnInfo.emPosPic))
                    {
                        pCheck->SetEnabled(false);
                        if (bSrcnID == 0)
                        {
                            KillTimer(NULL,g_nTVWallLWaiting);
                            g_nTVWallLWaiting = SetTimer( NULL, bSrcnID, 4000, CBTimerFun); //操作成功后 等待4秒
                        }
                        if (bSrcnID == 2)
                        {
                            KillTimer(NULL,g_nTVWallRWaiting);
                            g_nTVWallRWaiting = SetTimer( NULL, bSrcnID, 4000, CBTimerFun); //操作成功后 等待4秒
                        }
                    }
                }

                if ( emPic_SelTVS ==  tScrnInfo.emPosPic )
                {
                    m_pm->DoCase( _T("caseCancelSelTVWall"), pParent );
                }
                else
                {
                    m_pm->DoCase( _T("caseSelTVWall"), pParent );
                }
			}
		}
		else
		{
			m_pm->DoCase( _T("caseNoTVWall"), pParent );
		}
		

        //演示
		BOOL32 bIsRcvDual = ComInterface->IsRcvDual();
		if ( bIsRcvDual )
		{   
			if ( tScrnInfo.emPosPic == emPic_SelDual  || tScrnInfo.emPosPic == emPic_Dual)
			{
				m_pm->DoCase( _T("caseScrCancelDual"), pParent );
			}
			else
			{
				m_pm->DoCase( _T("caseScrDual"), pParent );
			}
		}
        else
        {
            m_pm->DoCase( _T("caseScrNoDual"), pParent ); 
        }
        //回显
        if ( tScrnInfo.emPosPic == emPic_SelLocal /*|| tScrnInfo.emPosPic == emPic_Local*/)
        {
            m_pm->DoCase( _T("caseScrCancelLocal"), pParent );
        }
		else
		{
			m_pm->DoCase( _T("caseScrLocal"), pParent );
		} 
        //选看
        TCMSConf tConfInfo;
        BOOL32 bInconf = ComInterface->IsInConf( &tConfInfo );
        if ( bInconf )
        {
            if ( tConfInfo.m_emConfType == emCallType_P2P )
            {
                m_pm->DoCase( _T("caseNoSelWatch"), pParent );
            }
            else
            {
				if ( tScrnInfo.emPosPic == emPic_SelView )
				{
					m_pm->DoCase( _T("caseCancelSelWatch"), pParent );
				}
				else
				{
					m_pm->DoCase( _T("caseScrSelWatch"), pParent );
				} 
     //           BOOL32 bChairCns = ComInterface->IsLocalCnsChairMan();
     //           if ( !bChairCns )
     //           {
     //               m_pm->DoCase( _T("caseNoSelWatch"), pParent );
     //           }
     //           else
     //           {
     //               //如果本地为主席会场，则允许选看，否则不允许进行选看操作			
     //               if ( tScrnInfo.emPosPic == emPic_SelView )
					//{
					//	m_pm->DoCase( _T("caseCancelSelWatch"), pParent );
					//}
					//else
					//{
					//	m_pm->DoCase( _T("caseScrSelWatch"), pParent );
					//} 
     //           }
            }
        }
    }
}



bool CCnsManageLogic::OnBtnScrSelWatch( TNotifyUI& msg )
{
	CSrcSelWatchLogic::GetSingletonPtr()->UpdateCnsInfoList();
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight( g_strSrcSelWatchDlg.c_str() );
	CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("会议选看"));
	CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgSelWatch.png"));
    CListContainerElementUI* pListContainer = (CListContainerElementUI*)msg.pSender->GetParent()->GetParent()->GetParent()->GetParent();
    if (pListContainer)
    {
        m_pm->DoCase( _T("caseScreenNoSel"), pListContainer );
        m_nSelIndex = -1;
    }
    CSrcSelWatchLogic::GetSingletonPtr()->ReSetSelScreen();
	WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
	UIDATAMGR->SetCurShowWndName( g_strSrcSelWatchDlg );
	return true;
}

bool CCnsManageLogic::OnBtnCancelSelWatch( TNotifyUI& msg )
{
	if (CTouchListUI *pTouch = (CTouchListUI*)msg.pSender->GetParent()->GetParent()->GetParent()->GetParent()->GetParent())
	{
		int nIndex = pTouch->GetItemIndex(msg.pSender->GetParent()->GetParent()->GetParent()->GetParent());
		CSrcSelWatchLogic::GetSingletonPtr()->CancelSelWatch(nIndex);
	}

	return true;
}

bool CCnsManageLogic::OnConfStateNotify( WPARAM wParam, LPARAM lParam, bool& bHandle  )
{
	TCMSConf tConfInfo ;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo ); 

	if ( bInConf  )
	{	
        if ( tConfInfo.m_emConfType == emCallType_Conf )
        {
            ICncCommonOp::SetControlText( CA2T(tConfInfo.m_achConfName), m_pm, _T("StcConfName") );
        } 
		else
		{
			ICncCommonOp::SetControlText( _T(""), m_pm, _T("StcConfName") );
            ICncCommonOp::SetControlText( _T("2/2"), m_pm, _T("StcConfNum") );
		}

        m_bInConf = true;
        m_pm->DoCase( _T("caseCnsInConf") );

		if ( m_dwConfStartTime != tConfInfo.m_tStartTime  )
        {
            m_dwConfStartTime = tConfInfo.m_tStartTime;
            AdjustTime( m_dwConfStartTime );
            CTime tmStart( m_dwConfStartTime );
            m_tmConfDuration = 0;
            PrtMsg( 0, emEventTypeCmsWindow, "会议( %s ) 开始时间：%.4d-%.2d-%.2d %.2d:%.2d:%.2d", 
                tConfInfo.m_achConfName,tmStart.GetYear(), tmStart.GetMonth(),tmStart.GetDay(), tmStart.GetHour(),tmStart.GetMinute(),tmStart.GetSecond() );
            //开始计时
            KillTimer( NULL, g_wConfTimerID );
            UpdateConfTime();
            g_wConfTimerID = SetTimer( NULL, NULL, 1000, CBTimerFun ); 
        }

        TTPCnsConfStatus tStatus = ComInterface->GetLocalCnsConfState();
        if ( tStatus.m_emTPEncryptType != emTPEncryptTypeNone )
        {
            ICncCommonOp::ShowControl( true, m_pm, _T("EncryptLogo") );
            ICncCommonOp::ShowControl( true, m_pm, _T("StcEncrypt") );

			if (tStatus.m_emTPEncryptType == emTPEncryptTypeQt)
			{
				ICncCommonOp::SetControlBkImg(_T("res/cnsmanage/qtencryptlogo.png"),m_pm,_T("EncryptLogo"));
				ICncCommonOp::SetControlText(_T("量子加密"), m_pm, _T("StcEncrypt"));
			}
			else
			{
				ICncCommonOp::SetControlBkImg(_T("res/cnsmanage/encryptlogo.png"),m_pm,_T("EncryptLogo"));
				ICncCommonOp::SetControlText(_T("加密"), m_pm, _T("StcEncrypt"));
			}

        }
        else
        {
            ICncCommonOp::ShowControl( false, m_pm, _T("EncryptLogo") );
            ICncCommonOp::ShowControl( false, m_pm, _T("StcEncrypt") );
        }

		RefreshCnsScreen();
	}
	else
	{   
		bool bIsInconf = m_bInConf;
        m_bInConf = false;
        m_pm->DoCase( _T("caseCnsNotInConf") );
        ICncCommonOp::SetControlText( _T("无会议"), m_pm, _T("StcConfName") );
		if (m_nSelIndex != -1)
		{

			m_pSrceenList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, strCnsScreenList.c_str() );
			if ( m_pSrceenList == NULL )
			{
				return false;
			}
			CListContainerElementUI *pItem = (CListContainerElementUI*)m_pSrceenList->GetItemAt(m_nSelIndex);
			if (pItem)
			{
				m_pm->DoCase( _T("caseScreenNoSel"), pItem );
				m_nSelIndex = -1;
			}
		}

		if (bIsInconf)//不是结会 不清空状态
		{
			//清空屏幕会议名
			vector<TScreenInfo> vctScreenInfo;
			ComInterface->GetCnsScreenInfo( vctScreenInfo );
			for ( int i = 0; i < vctScreenInfo.size(); i++ )
			{		
				CListContainerElementUI *pListContainer = (CListContainerElementUI*)m_pSrceenList->GetItemAt(vctScreenInfo[i].byScreenID);
				if (pListContainer)
				{
					TScreenInfo tScrnInfo;
					ICncCommonOp::SetControlText(_T(""),m_pm, _T("lbScreenText"), pListContainer);
					ICncCommonOp::SetControlBkImg(_T("res/cnsmanage/screenperson.png"),m_pm,_T("imgScreenPic"));
				}
			
				//情空屏幕状态
				CString strScreenPic = _T("res/cnsmanage/screenperson.png");
				CString strlbscreentip = _T("");
				ICncCommonOp::SetControlBkImg(strScreenPic,m_pm,_T("imgScreenPic"),pListContainer);
				ICncCommonOp::SetControlText(strlbscreentip,m_pm,_T("lbscreentip"),pListContainer);
			}
		
			ComInterface->ClearCnsScreenName();//清空屏名称
		}
		m_pm->DoCase( _T("caseSeatNoConf") );
	}

	return true;
}

bool CCnsManageLogic::OnRefreshConfCnsList( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    TCMSConf tConfInfo ;
    BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo ); 

    if ( bInConf  )
    {
        int nTotalNum = 0;
        int nOnlineNum = 0;
        for ( int i = 0; i< tConfInfo.m_vctCnsList.size(); i++ )
        {
            TCnsInfo tInfo = tConfInfo.m_vctCnsList.at(i);
            if ( tInfo.m_emEpType != emTPEndpointTypeUMS && tInfo.m_emEpType != emTPEndpointH323MCU )
            {
                nTotalNum++;
                if ( tInfo.m_bOnline )
                {
                    nOnlineNum++;
                }
            }         
        } 
        CString strNum;
        strNum.Format( _T("%d/%d"), nOnlineNum, nTotalNum );
        ICncCommonOp::SetControlText( strNum, m_pm, _T("StcConfNum") );
    }
    return true;
}


void CCnsManageLogic::RefreshCnsScreen()
{
	vector<TScreenInfo> vctScreenInfo;
	ComInterface->GetCnsScreenInfo( vctScreenInfo );

	TTPCnsInfo tCnsInfo;
	ComInterface->GetLocalCnsInfo( tCnsInfo );

	m_pSrceenList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, strCnsScreenList.c_str() );
	if ( m_pSrceenList == NULL )
	{
		return;
	}

	for ( int i = 0; i < vctScreenInfo.size(); i++ )
	{		
		CListContainerElementUI *pListContainer = (CListContainerElementUI*)m_pSrceenList->GetItemAt(vctScreenInfo[i].byScreenID);
		if (pListContainer)
		{
			TScreenInfo tScrnInfo;
			u16 re = ComInterface->GetCnsScreenInfoByID( vctScreenInfo[i].byScreenID, tScrnInfo );
			if ( NO_ERROR == re )
			{
				CString strCnsName(tScrnInfo.achCnsName);
				ICncCommonOp::SetControlText(strCnsName,m_pm, _T("lbScreenText"), pListContainer);
			
// 				//如果没选中 会议中不会变化 避免一直刷新 第一次开会 若屏幕有空闲双流状态 进行刷新
// 				if ( m_nSelIndex == vctScreenInfo[i].byScreenID || m_bIsSpareDual)
// 				{
// 					UpdateScreenMenu( m_nSelIndex, pListContainer);
// 				}

				UpdateScreenMenu( i, pListContainer);//由于可能是会议控制中进行了会场选看 此时必须所以都刷新 2015-7-3 
			}
		}
	}
}

bool CCnsManageLogic::OnSelViewInd(  WPARAM wParam, LPARAM lParam, bool& bHandle  )
{
	BOOL32 bInConf = ComInterface->IsInConf();
	if ( bInConf )
	{   
		TTPSelViewInd tTPSelViewInd = *(TTPSelViewInd*)wParam;

		EmViewRetReason emRe = ( EmViewRetReason ) lParam;  
		if ( emRe != EmViewRetReason_Success )
		{           
			CString msg = _T("");

			switch ( emRe )
			{
			case EmViewRetReason_Selected:
				msg = _T("当前屏已经选看中"); 
				break;
			case EmViewRetReason_UnSelected:
				msg = _T("取消选看时，当前屏未选看");
				break;
			case EmViewRetReason_EpNotLine:       
				msg =  _T("选看会场不在线");
				break;

			case EmViewRetReason_DstEpNotLine:         
				msg =  _T("被选看会场不在线");
				break;
			case EmViewRetReason_DstEqpNoExists:
				msg = _T("被选看外设不存在");
				break;
			case EmViewRetReason_SelFull:        
				msg =  _T("选看资源满");
				break;
			case EmViewRetReason_EpTypeError:        
				msg =  _T("被选看目标类型错误：终端、外设");
				break;
			case EmViewRetReason_SelDstNoVid:         
				msg =  _T("被选看目标无视频源");
				break;
			case EmViewRetReason_SelNoVid:
				msg = _T("选看会场无视频接收");
				break;
			case EmViewRetReason_SelDstNotLvl:        
				msg =  _T("选看会场和被选看会场不在一个同一个级");
				break;
			case EmViewRetReason_NoBasRes:        
				msg =  _T("无适配资源");
				break;
			case EmViewRetReason_InValidEp:        
				msg =  _T("选看会场无效");
				break;			
			case EmViewRetReason_NoBwRes:        
				msg =  _T("选看带宽不足");
				break;
			default:
				msg = _T("未知原因");
				break;                
			}

// 			TTPCnsInfo tCnsInfo;
// 			ComInterface->GetLocalCnsInfo( tCnsInfo );
// 			if ( tCnsInfo.m_emLevel == emTPSipProvince )
// 			{
// 				byScreenID += 2;
// 			}
// 			else
// 			{
// 				byScreenID += 1;
// 			}
			u8 byScreenID = tTPSelViewInd.m_tSelView.m_wScreenIndx;
			CString strId = _T("");
			switch(byScreenID)
			{
			case 0:
				{
					strId = _T("左屏");
				}
				break;
			case 1:
				{
					strId = _T("中屏");
				}
				break;
			case 2:
				{
					strId = _T("右屏");
				}
				break;
			}
			CString tip;
			if(tTPSelViewInd.m_tSelView.m_bSel)
			{				
				if (byScreenID == TP_MAX_STREAMNUM)
				{
					tip.Format( _T("会场选看失败: %s"), msg );
				}
				else
				{
					tip.Format( _T("%s选看失败:"), strId );
					tip = tip + msg;
				}
			}
			else
			{
				if (byScreenID == TP_MAX_STREAMNUM)
				{
					tip.Format( _T("会场取消选看失败: %s"), msg );
				}
				else
				{
					tip.Format( _T("%s取消选看失败:"), strId );
					tip = tip + msg;
				}
			}

			ShowPopMsg(tip);
		} 
	}

	return S_OK;
}

bool CCnsManageLogic::OnCancelSelViewRsp(  WPARAM wParam, LPARAM lParam, bool& bHandle  )
{
	BOOL32 bInConf = ComInterface->IsInConf();
	if ( bInConf )
	{   
		TTPCnsInfo tCnsInfo;
		ComInterface->GetLocalCnsInfo( tCnsInfo );

		u8 byScreenID = (u8)wParam;
		EmTPViewResult emRe = ( EmTPViewResult ) lParam; 
		if ( emRe != emViewSucceed )
		{  

			CString msg;
			switch ( emRe )
			{
			case emViewFailStatusError:
				msg = "当前未处于选看状态";  //不加提示，直接变化状态

				if ( tCnsInfo.m_emLevel == emTPSipProvince )
				{
					byScreenID += 1;
				}

				return S_OK;
				break;
			case emViewFailOffline:
				msg = "选看会场不在线";
				break;
			default:
				msg = "未知原因";
				break; 
			}

			if ( tCnsInfo.m_emLevel == emTPSipProvince )
			{
				byScreenID += 2;
			}
			else
			{
				byScreenID += 1;
			}

			CString strId = _T("");
			switch(byScreenID)
			{
			case 0:
				{
					strId = _T("左屏");
				}
				break;
			case 1:
				{
					strId = _T("中屏");
				}
				break;
			case 2:
				{
					strId = _T("右屏");
				}
				break;
			}
			CString tip;
			tip.Format(_T("%s取消选看失败:%s"),strId);
			tip = tip + msg;
			ShowPopMsg(tip);
		} 


		//解决选看后 再切换发言人，ums先发送屏未处于激活状态，再发送取消选看消息  2011-12-27 by yjj
		//OnScreenStateNotify( wParam,0);  根据屏状态的notify消息进行更新 2012-3-15
	}

	return S_OK;
}

bool CCnsManageLogic::OnSelTVSViewRsp(  WPARAM wParam, LPARAM lParam, bool& bHandle  )
{
	u8 byScreenID = (u8)wParam;
	BOOL32 bInConf = ComInterface->IsInConf();
	if ( bInConf )
	{   
		TTPCnsInfo tCnsInfo;
		ComInterface->GetLocalCnsInfo( tCnsInfo );

		BOOL bSuccess = (BOOL) lParam;  
		if ( !bSuccess )
		{    

// 			if ( tCnsInfo.m_emLevel == emTPSipProvince )
// 			{
// 				byScreenID += 2;
// 			}
// 			else
// 			{
// 				byScreenID += 1;
// 			}

			CString strId = _T("");
			switch(byScreenID)
			{
			case 0:
				{
					strId = _T("左屏");
				}
				break;
			case 1:
				{
					strId = _T("中屏");
				}
				break;
			case 2:
				{
					strId = _T("右屏");
				}
				break;
			}
			CString tip;
			tip.Format(_T("%s选看电视墙失败"),strId);

			ShowPopMsg(tip);

			UpDateCheckBoxState(_T("BtnTVWall"),byScreenID,false);
		} 
		else//成功了更新一下 和zj确认 收到此消息不一定收到更新消息
		{
			CListContainerElementUI *pListContainer = (CListContainerElementUI*)m_pSrceenList->GetItemAt(byScreenID);
			if (!pListContainer)
			{
				return false;
			}
			UpdateScreenMenu(byScreenID, pListContainer);
		}
	}

	return S_OK;
}

bool CCnsManageLogic::OnCancleSelTVSViewRsp(  WPARAM wParam, LPARAM lParam, bool& bHandle  )
{
	u8 byScreenID = (u8)wParam;
	BOOL32 bInConf = ComInterface->IsInConf();
	if ( bInConf )
	{   
		TTPCnsInfo tCnsInfo;
		ComInterface->GetLocalCnsInfo( tCnsInfo );

		BOOL bSuccess = (BOOL) lParam;  
		if ( !bSuccess )
		{  		
// 			if ( tCnsInfo.m_emLevel == emTPSipProvince )
// 			{
// 				byScreenID += 2;
// 			}
// 			else
// 			{
// 				byScreenID += 1;
// 			}

			CString strId = _T("");
			switch(byScreenID)
			{
			case 0:
				{
					strId = _T("左屏");
				}
				break;
			case 1:
				{
					strId = _T("中屏");
				}
				break;
			case 2:
				{
					strId = _T("右屏");
				}
				break;
			}
			CString tip;
			tip.Format(_T("%s取消选看电视墙失败"),strId);

			ShowPopMsg(tip);

			UpDateCheckBoxState(_T("BtnTVWall"),byScreenID,true);
		} 
		else//成功了更新一下 和zj确认 收到此消息不一定收到更新消息
		{
			CListContainerElementUI *pListContainer = (CListContainerElementUI*)m_pSrceenList->GetItemAt(byScreenID);
			if (!pListContainer)
			{
				return false;
			}
			UpdateScreenMenu(byScreenID, pListContainer);
		}
	}

	return S_OK;
}

/* 静音哑音通知  
	wparam = bQuite 	是静音还是哑音.TRUE 静音， FALSE 哑音
	lparam = bOn		是开启还是关闭.开启静音使当前没有音频输出,反之是关闭静音
*/
bool CCnsManageLogic::OnMuteOrSilencNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL32 bQuiet = (BOOL32)wParam;
	BOOL32 bSucess = (BOOL32)lParam;
		
	if (bQuiet)
	{
		if (bSucess)
		{
			ICncCommonOp::ShowControl( true, m_pm, _T("imgLocalQuite") );  
		}
		else
		{
			ICncCommonOp::ShowControl( false, m_pm, _T("imgLocalQuite") );  
		}
	}
	else
	{
		ICncCommonOp::ShowControl( false, m_pm, _T("imgLocalMute") );  

		if (bSucess)
		{
			ICncCommonOp::ShowControl( true, m_pm, _T("imgLocalMute") );  
		}
		else
		{
			ICncCommonOp::ShowControl( false, m_pm, _T("imgLocalMute") );  
		}
	}

	return true;
}

bool CCnsManageLogic::OnConfMixStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TTpAudMixInfo tTpAudMixInfo;//混音状态
	ComInterface->GetConfMixState( tTpAudMixInfo );

	if (tTpAudMixInfo.m_emMode == em_umsaudmixmode_idle)
	{
		ICncCommonOp::ShowControl( false, m_pm, _T("imgLocalMix") );  
	}
	else
	{
		ICncCommonOp::ShowControl( true, m_pm, _T("imgLocalMix") );  
	}

	return S_OK;
}

bool CCnsManageLogic::OnEpInAudMixNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	BOOL bInAudMix = (BOOL)wParam;
	if (bInAudMix)
	{
		ICncCommonOp::ShowControl( true, m_pm, _T("imgLocalMix") );  
	}
	else
	{
		ICncCommonOp::ShowControl( false, m_pm, _T("imgLocalMix") );  
	}

	return S_OK;
}

bool CCnsManageLogic::OnScreenStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_pSrceenList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, strCnsScreenList.c_str() );
	if ( m_pSrceenList == NULL )
	{
		return false;
	}

	CListContainerElementUI *pListContainer = (CListContainerElementUI*)m_pSrceenList->GetItemAt(wParam);
	if (pListContainer)
	{
		TScreenInfo tScrnInfo;
		u16 re = ComInterface->GetCnsScreenInfoByID( wParam, tScrnInfo );
		if ( NO_ERROR == re )
		{
			//更新屏名 去掉回放时的后缀 dyy 2013年9月2日
			CString strCnsName(tScrnInfo.achCnsName);
			//strCnsName = strCnsName.Left(strCnsName.Find(_T("_255_")));

			ICncCommonOp::SetControlText(strCnsName,m_pm, _T("lbScreenText"), pListContainer);

			//if ( m_nSelIndex == wParam )//来了就刷新 避免本地开了双流 然后开会的时候界面不更新的问题
			{
				UpdateScreenMenu( wParam/*m_nSelIndex*/, pListContainer);
			}
		}

	}

	return NO_ERROR;
}

void CCnsManageLogic::UpdateConfTime()
{    
    if ( 0 == m_tmConfDuration.GetTotalSeconds() )
    {
        CTime tmStart( m_dwConfStartTime );
        m_tmConfDuration = CTime::GetCurrentTime() - tmStart ;  
        if ( m_tmConfDuration < 0 )
        {
            m_tmConfDuration = 0;
        }
    }
    else
    {  
        m_tmConfDuration += 1;
    } 

    s8 strTime[64] = {0};
    u32 nday = m_tmConfDuration.GetDays();
    u32 nhor = m_tmConfDuration.GetHours();
    u32 nmin = m_tmConfDuration.GetMinutes();
    u32 nsec = m_tmConfDuration.GetSeconds();
    if (nday == 0)
    {
        sprintf( strTime, "%.2d:%.2d:%.2d",nhor,nmin,nsec/*m_tmConfDuration.GetDays(), m_tmConfDuration.GetHours(), m_tmConfDuration.GetMinutes(), m_tmConfDuration.GetSeconds()*/ );
    }
    else
    {
        sprintf( strTime, "%d天%.2d:%.2d:%.2d",nday,nhor,nmin,nsec/*m_tmConfDuration.GetDays(), m_tmConfDuration.GetHours(), m_tmConfDuration.GetMinutes(), m_tmConfDuration.GetSeconds()*/ );
    }

    ICncCommonOp::SetControlText( CA2T(strTime), m_pm, _T("StcConfTime") );
}

void CCnsManageLogic::AdjustTime( time_t &time )
{
    CTime tmAdust( time );
    CTime tmCur( CTime::GetCurrentTime() );
    if (  tmCur < tmAdust )
    {    
        time = tmCur.GetTime(); 
    }
}

bool CCnsManageLogic::OnCheckDualView( TNotifyUI& msg )
{
	if ( m_nSelIndex == -1)
	{
		return false;
	}

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

	CListContainerElementUI *pItem = (CListContainerElementUI*)msg.pSender->GetParent()->GetParent()->GetParent()->GetParent();
	if (pItem)
	{
		int nIndex = pItem->GetIndex();
		if (nIndex != m_nSelIndex)//此时表示是消息控制的状态更新 不进行逻辑控制
		{
			return true;
		}
	}

	TScreenInfo tScrnInfo;
	u16 re = ComInterface->GetCnsScreenInfoByID( m_nSelIndex, tScrnInfo );
	if ((tScrnInfo.emPosPic == emPic_SelDual  || tScrnInfo.emPosPic == emPic_Dual )&& bIsSet)
	{
		return true;
	}
	if (tScrnInfo.emPosPic != emPic_SelDual && tScrnInfo.emPosPic != emPic_Dual && !bIsSet)
	{
		return true;
	}

	if ( m_bInConf )//会议中
	{
		if (bIsSet)
		{
			ComInterface->ScrnDisplayDual( m_nSelIndex );
		}
		else
		{
			ComInterface->ScrnStopDisplayDual( m_nSelIndex );
		}
	}
	else//空闲时
	{
		if (m_nSelIndex > 2)
		{
			return false;
		}

		ComInterface->ScrnSpareTimeDisplayDual( m_nSelIndex, bIsSet );
	}

	return true;
}

bool CCnsManageLogic::OnCheckScrLocal( TNotifyUI& msg )
{
	CListContainerElementUI *pItem = (CListContainerElementUI*)msg.pSender->GetParent()->GetParent()->GetParent()->GetParent();
	if (pItem)
	{
		int nIndex = pItem->GetIndex();
		if (nIndex != m_nSelIndex)//此时表示是消息控制的状态更新 不进行逻辑控制
		{
			return true;
		}
	}

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

	TScreenInfo tScrnInfo;
	u16 re = ComInterface->GetCnsScreenInfoByID( m_nSelIndex, tScrnInfo );
	if ((tScrnInfo.emPosPic == emPic_SelLocal  /*|| tScrnInfo.emPosPic == emPic_Local*/ )&& bIsSet)
	{
		return true;
	}
	if (tScrnInfo.emPosPic != emPic_SelLocal /*&& tScrnInfo.emPosPic != emPic_Local*/ && !bIsSet)
	{
		return true;
	}

	if (bIsSet)
	{
		ComInterface->ScrnDisplayLocal( m_nSelIndex );
	}
	else
	{
		ComInterface->ScrnStopDisplayLocal( m_nSelIndex );
	}

	return true;
}

bool CCnsManageLogic::OnSelLocalRsp( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL32 bIsInconf  =  ComInterface->IsInConf();
	if ( bIsInconf )
	{
		u8 sCrnID =  (u8)wParam;
		EmTPViewLocalResult em =  (EmTPViewLocalResult)lParam;
		switch( em )
		{
		case  emViewLocalFailUnKown:
			ShowPopMsg(_T("回显失败")); //：未知错误");2012-8-7 SE石文娟确认未知错误不做提示 by yjj
			break;
		case emViewLocalFailStatusError:       //状态错误，取消时表示当前屏不在VIEW LOCAL，选看时表示已在看本地状态
			// ShowPopMsg(_T("回显失败：当前正在看本地"));
			break;
		case emViewLocalFailOffline:
			ShowPopMsg(_T("回显失败：本地会场不在线"));
			break;

		case emViewLocalFailIllegalPos:
			ShowPopMsg(_T("回显失败：非法位置"));
			break;
		}

		if (em != emViewLocalSucceed)
		{
			UpDateCheckBoxState(_T("BtnScrLocal"),sCrnID,false);
		}
	}

	return S_OK;
}

bool CCnsManageLogic::OnCancleSelLocalRsp( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL32 bIsInconf  =  ComInterface->IsInConf();
	if ( bIsInconf )
	{
		u8 sCrnID =  (u8)wParam;
		EmTPViewLocalResult em =  (EmTPViewLocalResult)lParam;
		switch( em )
		{
		case  emViewLocalFailUnKown:
			ShowPopMsg(_T("取消回显失败")); //：未知错误");2012-8-7 SE石文娟确认未知错误不做提示 by yjj
			break;
		case emViewLocalFailStatusError:       //状态错误，取消时表示当前屏不在VIEW LOCAL，选看时表示已在看本地状态
			// ShowPopMsg(_T("回显失败：当前正在看本地"));
			break;
		case emViewLocalFailOffline:
			ShowPopMsg(_T("取消回显失败：本地会场不在线"));
			break;

		case emViewLocalFailIllegalPos:
			ShowPopMsg(_T("取消回显失败：非法位置"));
			break;
		}

		if (em != emViewLocalSucceed)
		{
			UpDateCheckBoxState(_T("BtnScrLocal"),sCrnID,true);
		}
	}
	return S_OK;
}

bool CCnsManageLogic::OnSelDualViewRsp( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL32 bIsInconf  =  ComInterface->IsInConf();
	if ( bIsInconf )
	{
		u8 wScrnID =  (u8)wParam;
		EmTPAddDualRcvResult em =  (EmTPAddDualRcvResult)lParam;
		switch( em )
		{
		case emAddDualRcvFailNoDual:
			ShowPopMsg(_T("看演示失败：当前未处于接收双流状态"));
			break;

		case emAddDualRcvFailIllegalPos:
			ShowPopMsg(_T("看演示失败：通道非法"));
			break;
		case emAddDualRcvFailNoPos:
			ShowPopMsg(_T("看演示失败：无空闲通道"));
			break;
		case emAddDualRcvFailUnKown:
			ShowPopMsg(_T("看演示失败"));
			break;
		}

		if (em != emAddDualRcvSucceed)
		{
			UpDateCheckBoxState(_T("BtnScrDual"),wScrnID,false);
		}
		else
		{
			UpDateCheckBoxState(_T("BtnScrDual"),wScrnID,true);
		}

		RefreshScreenDual(wScrnID);
	}

	return S_OK;
}

bool CCnsManageLogic::OnCancleDualViewRsp( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL32 bIsInconf  =  ComInterface->IsInConf();
	if ( bIsInconf )
	{
		u16  wScrnID = wParam;
		CString strId = _T("");
		switch(wScrnID)
		{
		case 0:
			{
				strId = _T("左屏");
			}
			break;
		case 1:
			{
				strId = _T("中屏");
			}
			break;
		case 2:
			{
				strId = _T("右屏");
			}
			break;
		}

		CString strtip;
		strtip.Format(_T("%s取消演示失败"),strId);

		EmTPDeleteDualRcvResult emRe = (EmTPDeleteDualRcvResult)(lParam);
		switch( emRe )
		{
		case emDeleteDualRcvFailNoDual:
			ShowPopMsg(strtip + _T("：当前未处于接收双流状态"));
			break;

		case emDeleteDualRcvFailIllegalPos:
			ShowPopMsg(strtip + _T("：通道非法"));
			break;
		case emDeleteDualRcvFailUnKown:
			ShowPopMsg(strtip);
			break;
		}

		if (emRe != emDeleteDualRcvSucceed)  //选择会场控制的是 不是界面操作 不能用是否成功判断 界面操作才能用是否成功判断 成功了也要刷新一下 2015-7-3 
		{
			UpDateCheckBoxState(_T("BtnScrDual"),wScrnID,true);
		}
		else
		{
			UpDateCheckBoxState(_T("BtnScrDual"),wScrnID,false);
		}

		RefreshScreenDual(wScrnID);//并且要刷新屏幕图片
	}
	return S_OK;
}

bool CCnsManageLogic::OnCheckTVWView( TNotifyUI& msg )
{
	CListContainerElementUI *pItem = (CListContainerElementUI*)msg.pSender->GetParent()->GetParent()->GetParent()->GetParent();
	if (pItem)
	{
		int nIndex = pItem->GetIndex();
		if (nIndex != m_nSelIndex)//此时表示是消息控制的状态更新 不进行逻辑控制
		{
			return true;
		}
	}

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

	TScreenInfo tScrnInfo;
	u16 re = ComInterface->GetCnsScreenInfoByID( m_nSelIndex, tScrnInfo );
	if ((tScrnInfo.emPosPic == emPic_SelTVS )&& bIsSet)
	{
		return true;
	}
	if (tScrnInfo.emPosPic != emPic_SelTVS && !bIsSet)
	{
		return true;
	}

	BOOL bIsTVWALL = ComInterface->GetDisplayState();

	if (bIsSet)
	{
		//电视墙配置开启后,在点击显示器1、3屏选看后,直接发送消息通知cns切换输出信号源  ----JYY  2014.5.14
		if ( m_nSelIndex == 0 || m_nSelIndex == 2 )
		{
			if ( bIsTVWALL )
			{
				u16 wRe = ComInterface->SetSelTVSView( m_nSelIndex );
				if ( wRe != NO_ERROR )
				{
					ShowPopMsg(_T("电视墙开启设置失败"));
					pCheckBox->SetCheckNoMsg(false);
					return false;
				}

				pCheckBox->SetEnabled(false);
				CLabelUI* plb = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbTVWal"), pItem);
				if (plb)
				{
					plb->SetText(_T("取消电视墙"));
				}
			}
		}
	}
	else
	{
		if ( bIsTVWALL )
		{
			u16 wRe = ComInterface->CancleSelTVSView( m_nSelIndex );
			if ( wRe != NO_ERROR )
			{
				ShowPopMsg(_T("电视墙关闭设置失败"));
				pCheckBox->SetCheckNoMsg(true);
				return false;
			}

			pCheckBox->SetEnabled(false);
			CLabelUI* plb = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbTVWal"), pItem);
			if (plb)
			{
				plb->SetText(_T("电视墙"));
			}
		}
	}
	if (m_nSelIndex == 0)
	{
		g_nTVWallLWaiting = SetTimer( NULL, m_nSelIndex, 4000, CBTimerFun); //操作成功后 等待4秒
	}
	if (m_nSelIndex == 2)
	{
		g_nTVWallRWaiting = SetTimer( NULL, m_nSelIndex, 4000, CBTimerFun); //操作成功后 等待4秒
	}
	
	return true;
}

bool CCnsManageLogic::OnBtnSpeakSeat1(TNotifyUI& msg)
{
	u16 wRet = ComInterface->SetCnsInnerSpeaker( 0 );
	return true;
}

bool CCnsManageLogic::OnBtnSpeakSeat2(TNotifyUI& msg)
{
	u16 wRet = ComInterface->SetCnsInnerSpeaker( 1 );
	return true;
}

bool CCnsManageLogic::OnBtnSpeakSeat3(TNotifyUI& msg)
{
	u16 wRet = ComInterface->SetCnsInnerSpeaker( 2 );
	return true;
}

void CCnsManageLogic::UpDateCheckBoxState(String strCheckName, u16 wId, bool bCheck )
{
	m_pSrceenList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, strCnsScreenList.c_str() );
	if ( m_pSrceenList == NULL )
	{
		return;
	}

	CListContainerElementUI *pListContainer = (CListContainerElementUI*)m_pSrceenList->GetItemAt(wId);
	if (pListContainer)
	{
		CCheckBoxUI* pCheck = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, strCheckName.c_str(), pListContainer);
		if (pCheck)
		{
			if (pCheck->GetCheck() != bCheck)
			{
				pCheck->SetCheckNoMsg(bCheck);
			}
		}
	}
}

bool CCnsManageLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_pSrceenList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, strCnsScreenList.c_str() );
	if ( m_pSrceenList == NULL )
	{
		return false;
	}

	for ( int i = 0; i < m_pSrceenList->GetCount(); i++ )
	{	
		CListContainerElementUI *pListContainer = (CListContainerElementUI*)m_pSrceenList->GetItemAt(i);
		if (pListContainer)
		{
			ICncCommonOp::SetControlText(_T(""),m_pm, _T("lbScreenText"), pListContainer);
			ICncCommonOp::SetControlBkImg(_T("res/cnsmanage/screenperson.png"),m_pm,_T("imgScreenPic"));
		}

		//清空屏幕状态
		CString strScreenPic = _T("res/cnsmanage/screenperson.png");
		CString strlbscreentip = _T("");
		ICncCommonOp::SetControlBkImg(strScreenPic,m_pm,_T("imgScreenPic"),pListContainer);
		ICncCommonOp::SetControlText(strlbscreentip,m_pm,_T("lbscreentip"),pListContainer);
	}

	CListContainerElementUI *pListContainer = (CListContainerElementUI*)m_pSrceenList->GetItemAt(m_nSelIndex);
	if (pListContainer)
	{
		m_pm->DoCase( _T("caseScreenNoSel"), pListContainer );
	}
	m_nSelIndex = -1;
	m_bInConf = false;
	m_dwConfStartTime = 0;
	m_bIsSpareDual = false;

	m_pm->DoCase( _T("caseSeatAllNotSpk") );

	//断链时隐藏静音、哑音、混音图标 --add by wangkui 2016-9-19
	ICncCommonOp::ShowControl( false, m_pm, _T("imgLocalQuite") );  
	ICncCommonOp::ShowControl( false, m_pm, _T("imgLocalMute") );  
	ICncCommonOp::ShowControl( false, m_pm, _T("imgLocalMix") );  
	return true;
}

bool CCnsManageLogic::OnSpareSelDualViewInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	if (lParam > 2)
	{
		return false;
	}

	BOOL32 bInConf = ComInterface->IsInConf();
	if ( !bInConf )
	{   
		u8 byScreenID = (u8)lParam;
		EmTpDualIdleReason emTpDualIdleReason = (EmTpDualIdleReason)wParam ;  
		if ( emTpDualIdleReason != emTpSuccess)
		{  	
			CString strId = _T("");
			switch(byScreenID)
			{
			case 0:
				{
					strId = _T("左屏");
				}
				break;
			case 1:
				{
					strId = _T("中屏");
				}
				break;
			case 2:
				{
					strId = _T("右屏");
				}
				break;
			}

			CString tip;
			tip.Format(_T("%s双流操作失败"),strId);
			if ( emTpNoSource == emTpDualIdleReason)
			{
				tip = tip + _T(":开启失败，无视频源");
			}
			else if ( emTpBussyNow == emTpDualIdleReason)
			{
				tip = tip + _T(":开启失败，会场忙，在会议中");
			}

			ShowPopMsg(tip);
		} 
		else
		{
			RefreshScreenDual(byScreenID);
		}

		TScreenInfo tScrnInfo;
		u16 re = ComInterface->GetCnsScreenInfoByID( byScreenID, tScrnInfo );
		if ( NO_ERROR == re )
		{
			if (tScrnInfo.emPosPic == emPic_SelDual  || tScrnInfo.emPosPic == emPic_Dual)
			{ 
				UpDateCheckBoxState(_T("BtnScrDual"),byScreenID,true);
			}
			else
			{
				UpDateCheckBoxState(_T("BtnScrDual"),byScreenID,false);
			}
		}
	}
	return true;
}

bool CCnsManageLogic::OnSpareSelDualViewNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_bInConf = ComInterface->IsInConf();
	if ( !m_bInConf )
	{   
		u8 byScreenID = (u8)lParam ;
		BOOL bSuccess = (BOOL)wParam ;  
			
		UpDateCheckBoxState(_T("BtnScrDual"),byScreenID,bSuccess);

		RefreshScreenDual(byScreenID);
// 		if (g_wSpareDualStateTimerID == 0 && bSuccess)//登录时收到消息 屏进行了双流显示 1s后刷新 直接刷新不显示
// 		{
// 			g_wSpareDualStateTimerID = SetTimer( NULL, NULL, 1000, CBTimerFun ); 
// 		}
	}

	return true;
}

void CCnsManageLogic::RefreshScreenDual(u16 wScreenID)
{
	m_pSrceenList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, strCnsScreenList.c_str() );
	if ( m_pSrceenList == NULL )
	{
		return ;
	}
	CListContainerElementUI *pItem = (CListContainerElementUI*)m_pSrceenList->GetItemAt(wScreenID);
	if (!pItem)
	{
		return ;
	}

	CString strScreenPic = _T("res/cnsmanage/screenperson.png");
	CString strlbscreentip = _T("");
	TScreenInfo tScrnInfo;
	u16 re = ComInterface->GetCnsScreenInfoByID( wScreenID, tScrnInfo );
	if ( NO_ERROR == re )
	{
		//if (!m_bInConf)//空闲 双流
		{
			if (tScrnInfo.emPosPic == emPic_SelDual  || tScrnInfo.emPosPic == emPic_Dual)
			{   
				strScreenPic = _T("res/cnsmanage/screendual.png");
				strlbscreentip = _T("双流");
				//空闲时 成功显示双流 屏状态改变
				if (!m_bIsSpareDual)
				{
					m_bIsSpareDual = true;
				}

				m_pm->DoCase( _T("caseScrCancelDual"), pItem );
			}
			else
			{
				m_pm->DoCase( _T("caseScrDual"), pItem );
			}
		}
	}

	ICncCommonOp::SetControlBkImg(strScreenPic,m_pm,_T("imgScreenPic"),pItem);
	ICncCommonOp::SetControlText(strlbscreentip,m_pm,_T("lbscreentip"),pItem);
}

bool CCnsManageLogic::OnSpokesManNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	RefreshSpeakSeat();
	return S_OK;
}

void CCnsManageLogic::RefreshSpeakSeat()
{
	u8 bySeatId = ComInterface->GetCnsInnerSpeaker();

	TCMSConf  tConfInfo;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
	if ( !bInConf  )
	{
		return ;
	} 

	if ( CN_INNERSPEAKER_ALL == bySeatId  )
	{	//三个坐席全亮
		m_pm->DoCase( _T("CaseSeatAllSpk") );
	}
	else if( CN_INNERSPEAKER_NONE == bySeatId )
	{
		//全不亮
		m_pm->DoCase( _T("caseSeatAllNotSpk") );
	}
	else
	{	//先把三个坐席都置为非亮的
		m_pm->DoCase( _T("caseSeatAllNotSpk") );

		if ( bySeatId < 0 || bySeatId >= MAX_SEAT_COUNT )
		{
			return  ;
		} 
		CString strBtnName = _T("");
		strBtnName.Format(_T("btnSpeakSeat%d"),bySeatId+1);
		CButtonUI *pBtn = (CButtonUI*)ICncCommonOp::FindControl( m_pm, strBtnName );
		if (pBtn)
		{
			pBtn->SetAttribute(_T("normalimage"),_T("res/cnsmanage/speakseaton.png"));
		}		
	}
	
}

void CCnsManageLogic::EnableTVWall(int nSelIndex)
{
	CListContainerElementUI *pListContainer = (CListContainerElementUI*)m_pSrceenList->GetItemAt(nSelIndex);
	if (pListContainer)
	{
		CCheckBoxUI* pCheck = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm,_T("BtnTVWall"), pListContainer);
		if (pCheck)
		{
			pCheck->SetEnabled(true);
		}
	}
}
