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
static UINT g_nTVWallLWaiting = 0;//����ǽ���Ϳ�����3s���ܵ��
static UINT g_nTVWallRWaiting = 0;//����ǽ���Ϳ�����3s���ܵ��


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
	//����
	MSG_SELECTCHANGE(_T("BtnScrLocal"), OnCheckScrLocal)
	USER_MSG(UI_CNS_SCRN_DISPLAY_LOCAL_RSP,OnSelLocalRsp)
	USER_MSG(UI_CNS_STOP_SCRN_DISPLAY_LOCAL_RSP,OnCancleSelLocalRsp)
	//˫��
	MSG_SELECTCHANGE(_T("BtnScrDual"), OnCheckDualView)
	USER_MSG(UI_CNS_SCRN_DISPLAY_DUAL_RSP,OnSelDualViewRsp)
	USER_MSG(UI_CNS_STOP_SCRN_DISPLAY_DUAL_RSP ,OnCancleDualViewRsp)
	//����ʱ˫��
	USER_MSG(UI_CNS_SPAREDUAL_IND,OnSpareSelDualViewInd)
	USER_MSG(UI_CNS_SPAREDUAL_NTY,OnSpareSelDualViewNty)
	//����ǽ
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
		if (!m_bInConf)//���� ˫��
		{
			if (tScrnInfo.emPosPic == emPic_SelDual || tScrnInfo.emPosPic == emPic_Dual)//nlfȷ�� sel�ĺ�ûsel����һ���� dyy 2015-6-24
			{   
				strScreenPic = _T("res/cnsmanage/screendual.png");
				strlbscreentip = _T("˫��");
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
					strlbscreentip = _T("����ǽ");
				}
			}

			//BOOL32 bIsRcvDual = ComInterface->IsRcvDual();//�᳡ѡ��ʱ��0
			if ( /*bIsRcvDual &&*/ tScrnInfo.emPosPic == emPic_SelDual || tScrnInfo.emPosPic == emPic_Dual)
			{   
				strScreenPic = _T("res/cnsmanage/screendual.png");
				strlbscreentip = _T("˫��");
			}

			//ѡ��
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
						strlbscreentip = _T("ѡ��");
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

		//��ʾ
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
		//����ǽ
		BOOL32 bIsTVWALL = ComInterface->GetDisplayState();
		
		if ( bIsTVWALL )
		{			
            TCentreTVCfg  atTVCfg[MAX_CENTRETV_NUM];
            memcpy( atTVCfg , ComInterface->GetCentreTVCfg(), sizeof(TCentreTVCfg) * MAX_CENTRETV_NUM );

			if ( tScrnInfo.byScreenID == 1 || atTVCfg->emTvModle == emSharp70LX565A)		//ֻ��1��3��Ļѡ����ť�ſ��� || emSharp70LX565A��֧��
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
                            g_nTVWallLWaiting = SetTimer( NULL, bSrcnID, 4000, CBTimerFun); //�����ɹ��� �ȴ�4��
                        }
                        if (bSrcnID == 2)
                        {
                            KillTimer(NULL,g_nTVWallRWaiting);
                            g_nTVWallRWaiting = SetTimer( NULL, bSrcnID, 4000, CBTimerFun); //�����ɹ��� �ȴ�4��
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
		

        //��ʾ
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
        //����
        if ( tScrnInfo.emPosPic == emPic_SelLocal /*|| tScrnInfo.emPosPic == emPic_Local*/)
        {
            m_pm->DoCase( _T("caseScrCancelLocal"), pParent );
        }
		else
		{
			m_pm->DoCase( _T("caseScrLocal"), pParent );
		} 
        //ѡ��
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
     //               //�������Ϊ��ϯ�᳡��������ѡ���������������ѡ������			
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
	CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("����ѡ��"));
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
            PrtMsg( 0, emEventTypeCmsWindow, "����( %s ) ��ʼʱ�䣺%.4d-%.2d-%.2d %.2d:%.2d:%.2d", 
                tConfInfo.m_achConfName,tmStart.GetYear(), tmStart.GetMonth(),tmStart.GetDay(), tmStart.GetHour(),tmStart.GetMinute(),tmStart.GetSecond() );
            //��ʼ��ʱ
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
				ICncCommonOp::SetControlText(_T("���Ӽ���"), m_pm, _T("StcEncrypt"));
			}
			else
			{
				ICncCommonOp::SetControlBkImg(_T("res/cnsmanage/encryptlogo.png"),m_pm,_T("EncryptLogo"));
				ICncCommonOp::SetControlText(_T("����"), m_pm, _T("StcEncrypt"));
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
        ICncCommonOp::SetControlText( _T("�޻���"), m_pm, _T("StcConfName") );
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

		if (bIsInconf)//���ǽ�� �����״̬
		{
			//�����Ļ������
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
			
				//�����Ļ״̬
				CString strScreenPic = _T("res/cnsmanage/screenperson.png");
				CString strlbscreentip = _T("");
				ICncCommonOp::SetControlBkImg(strScreenPic,m_pm,_T("imgScreenPic"),pListContainer);
				ICncCommonOp::SetControlText(strlbscreentip,m_pm,_T("lbscreentip"),pListContainer);
			}
		
			ComInterface->ClearCnsScreenName();//���������
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
			
// 				//���ûѡ�� �����в���仯 ����һֱˢ�� ��һ�ο��� ����Ļ�п���˫��״̬ ����ˢ��
// 				if ( m_nSelIndex == vctScreenInfo[i].byScreenID || m_bIsSpareDual)
// 				{
// 					UpdateScreenMenu( m_nSelIndex, pListContainer);
// 				}

				UpdateScreenMenu( i, pListContainer);//���ڿ����ǻ�������н����˻᳡ѡ�� ��ʱ�������Զ�ˢ�� 2015-7-3 
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
				msg = _T("��ǰ���Ѿ�ѡ����"); 
				break;
			case EmViewRetReason_UnSelected:
				msg = _T("ȡ��ѡ��ʱ����ǰ��δѡ��");
				break;
			case EmViewRetReason_EpNotLine:       
				msg =  _T("ѡ���᳡������");
				break;

			case EmViewRetReason_DstEpNotLine:         
				msg =  _T("��ѡ���᳡������");
				break;
			case EmViewRetReason_DstEqpNoExists:
				msg = _T("��ѡ�����費����");
				break;
			case EmViewRetReason_SelFull:        
				msg =  _T("ѡ����Դ��");
				break;
			case EmViewRetReason_EpTypeError:        
				msg =  _T("��ѡ��Ŀ�����ʹ����նˡ�����");
				break;
			case EmViewRetReason_SelDstNoVid:         
				msg =  _T("��ѡ��Ŀ������ƵԴ");
				break;
			case EmViewRetReason_SelNoVid:
				msg = _T("ѡ���᳡����Ƶ����");
				break;
			case EmViewRetReason_SelDstNotLvl:        
				msg =  _T("ѡ���᳡�ͱ�ѡ���᳡����һ��ͬһ����");
				break;
			case EmViewRetReason_NoBasRes:        
				msg =  _T("��������Դ");
				break;
			case EmViewRetReason_InValidEp:        
				msg =  _T("ѡ���᳡��Ч");
				break;			
			case EmViewRetReason_NoBwRes:        
				msg =  _T("ѡ��������");
				break;
			default:
				msg = _T("δ֪ԭ��");
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
					strId = _T("����");
				}
				break;
			case 1:
				{
					strId = _T("����");
				}
				break;
			case 2:
				{
					strId = _T("����");
				}
				break;
			}
			CString tip;
			if(tTPSelViewInd.m_tSelView.m_bSel)
			{				
				if (byScreenID == TP_MAX_STREAMNUM)
				{
					tip.Format( _T("�᳡ѡ��ʧ��: %s"), msg );
				}
				else
				{
					tip.Format( _T("%sѡ��ʧ��:"), strId );
					tip = tip + msg;
				}
			}
			else
			{
				if (byScreenID == TP_MAX_STREAMNUM)
				{
					tip.Format( _T("�᳡ȡ��ѡ��ʧ��: %s"), msg );
				}
				else
				{
					tip.Format( _T("%sȡ��ѡ��ʧ��:"), strId );
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
				msg = "��ǰδ����ѡ��״̬";  //������ʾ��ֱ�ӱ仯״̬

				if ( tCnsInfo.m_emLevel == emTPSipProvince )
				{
					byScreenID += 1;
				}

				return S_OK;
				break;
			case emViewFailOffline:
				msg = "ѡ���᳡������";
				break;
			default:
				msg = "δ֪ԭ��";
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
					strId = _T("����");
				}
				break;
			case 1:
				{
					strId = _T("����");
				}
				break;
			case 2:
				{
					strId = _T("����");
				}
				break;
			}
			CString tip;
			tip.Format(_T("%sȡ��ѡ��ʧ��:%s"),strId);
			tip = tip + msg;
			ShowPopMsg(tip);
		} 


		//���ѡ���� ���л������ˣ�ums�ȷ�����δ���ڼ���״̬���ٷ���ȡ��ѡ����Ϣ  2011-12-27 by yjj
		//OnScreenStateNotify( wParam,0);  ������״̬��notify��Ϣ���и��� 2012-3-15
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
					strId = _T("����");
				}
				break;
			case 1:
				{
					strId = _T("����");
				}
				break;
			case 2:
				{
					strId = _T("����");
				}
				break;
			}
			CString tip;
			tip.Format(_T("%sѡ������ǽʧ��"),strId);

			ShowPopMsg(tip);

			UpDateCheckBoxState(_T("BtnTVWall"),byScreenID,false);
		} 
		else//�ɹ��˸���һ�� ��zjȷ�� �յ�����Ϣ��һ���յ�������Ϣ
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
					strId = _T("����");
				}
				break;
			case 1:
				{
					strId = _T("����");
				}
				break;
			case 2:
				{
					strId = _T("����");
				}
				break;
			}
			CString tip;
			tip.Format(_T("%sȡ��ѡ������ǽʧ��"),strId);

			ShowPopMsg(tip);

			UpDateCheckBoxState(_T("BtnTVWall"),byScreenID,true);
		} 
		else//�ɹ��˸���һ�� ��zjȷ�� �յ�����Ϣ��һ���յ�������Ϣ
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

/* ��������֪ͨ  
	wparam = bQuite 	�Ǿ�����������.TRUE ������ FALSE ����
	lparam = bOn		�ǿ������ǹر�.��������ʹ��ǰû����Ƶ���,��֮�ǹرվ���
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
	TTpAudMixInfo tTpAudMixInfo;//����״̬
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
			//�������� ȥ���ط�ʱ�ĺ�׺ dyy 2013��9��2��
			CString strCnsName(tScrnInfo.achCnsName);
			//strCnsName = strCnsName.Left(strCnsName.Find(_T("_255_")));

			ICncCommonOp::SetControlText(strCnsName,m_pm, _T("lbScreenText"), pListContainer);

			//if ( m_nSelIndex == wParam )//���˾�ˢ�� ���Ȿ�ؿ���˫�� Ȼ�󿪻��ʱ����治���µ�����
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
        sprintf( strTime, "%d��%.2d:%.2d:%.2d",nday,nhor,nmin,nsec/*m_tmConfDuration.GetDays(), m_tmConfDuration.GetHours(), m_tmConfDuration.GetMinutes(), m_tmConfDuration.GetSeconds()*/ );
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
		if (nIndex != m_nSelIndex)//��ʱ��ʾ����Ϣ���Ƶ�״̬���� �������߼�����
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

	if ( m_bInConf )//������
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
	else//����ʱ
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
		if (nIndex != m_nSelIndex)//��ʱ��ʾ����Ϣ���Ƶ�״̬���� �������߼�����
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
			ShowPopMsg(_T("����ʧ��")); //��δ֪����");2012-8-7 SEʯ�ľ�ȷ��δ֪��������ʾ by yjj
			break;
		case emViewLocalFailStatusError:       //״̬����ȡ��ʱ��ʾ��ǰ������VIEW LOCAL��ѡ��ʱ��ʾ���ڿ�����״̬
			// ShowPopMsg(_T("����ʧ�ܣ���ǰ���ڿ�����"));
			break;
		case emViewLocalFailOffline:
			ShowPopMsg(_T("����ʧ�ܣ����ػ᳡������"));
			break;

		case emViewLocalFailIllegalPos:
			ShowPopMsg(_T("����ʧ�ܣ��Ƿ�λ��"));
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
			ShowPopMsg(_T("ȡ������ʧ��")); //��δ֪����");2012-8-7 SEʯ�ľ�ȷ��δ֪��������ʾ by yjj
			break;
		case emViewLocalFailStatusError:       //״̬����ȡ��ʱ��ʾ��ǰ������VIEW LOCAL��ѡ��ʱ��ʾ���ڿ�����״̬
			// ShowPopMsg(_T("����ʧ�ܣ���ǰ���ڿ�����"));
			break;
		case emViewLocalFailOffline:
			ShowPopMsg(_T("ȡ������ʧ�ܣ����ػ᳡������"));
			break;

		case emViewLocalFailIllegalPos:
			ShowPopMsg(_T("ȡ������ʧ�ܣ��Ƿ�λ��"));
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
			ShowPopMsg(_T("����ʾʧ�ܣ���ǰδ���ڽ���˫��״̬"));
			break;

		case emAddDualRcvFailIllegalPos:
			ShowPopMsg(_T("����ʾʧ�ܣ�ͨ���Ƿ�"));
			break;
		case emAddDualRcvFailNoPos:
			ShowPopMsg(_T("����ʾʧ�ܣ��޿���ͨ��"));
			break;
		case emAddDualRcvFailUnKown:
			ShowPopMsg(_T("����ʾʧ��"));
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
				strId = _T("����");
			}
			break;
		case 1:
			{
				strId = _T("����");
			}
			break;
		case 2:
			{
				strId = _T("����");
			}
			break;
		}

		CString strtip;
		strtip.Format(_T("%sȡ����ʾʧ��"),strId);

		EmTPDeleteDualRcvResult emRe = (EmTPDeleteDualRcvResult)(lParam);
		switch( emRe )
		{
		case emDeleteDualRcvFailNoDual:
			ShowPopMsg(strtip + _T("����ǰδ���ڽ���˫��״̬"));
			break;

		case emDeleteDualRcvFailIllegalPos:
			ShowPopMsg(strtip + _T("��ͨ���Ƿ�"));
			break;
		case emDeleteDualRcvFailUnKown:
			ShowPopMsg(strtip);
			break;
		}

		if (emRe != emDeleteDualRcvSucceed)  //ѡ��᳡���Ƶ��� ���ǽ������ �������Ƿ�ɹ��ж� ��������������Ƿ�ɹ��ж� �ɹ���ҲҪˢ��һ�� 2015-7-3 
		{
			UpDateCheckBoxState(_T("BtnScrDual"),wScrnID,true);
		}
		else
		{
			UpDateCheckBoxState(_T("BtnScrDual"),wScrnID,false);
		}

		RefreshScreenDual(wScrnID);//����Ҫˢ����ĻͼƬ
	}
	return S_OK;
}

bool CCnsManageLogic::OnCheckTVWView( TNotifyUI& msg )
{
	CListContainerElementUI *pItem = (CListContainerElementUI*)msg.pSender->GetParent()->GetParent()->GetParent()->GetParent();
	if (pItem)
	{
		int nIndex = pItem->GetIndex();
		if (nIndex != m_nSelIndex)//��ʱ��ʾ����Ϣ���Ƶ�״̬���� �������߼�����
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
		//����ǽ���ÿ�����,�ڵ����ʾ��1��3��ѡ����,ֱ�ӷ�����Ϣ֪ͨcns�л�����ź�Դ  ----JYY  2014.5.14
		if ( m_nSelIndex == 0 || m_nSelIndex == 2 )
		{
			if ( bIsTVWALL )
			{
				u16 wRe = ComInterface->SetSelTVSView( m_nSelIndex );
				if ( wRe != NO_ERROR )
				{
					ShowPopMsg(_T("����ǽ��������ʧ��"));
					pCheckBox->SetCheckNoMsg(false);
					return false;
				}

				pCheckBox->SetEnabled(false);
				CLabelUI* plb = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbTVWal"), pItem);
				if (plb)
				{
					plb->SetText(_T("ȡ������ǽ"));
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
				ShowPopMsg(_T("����ǽ�ر�����ʧ��"));
				pCheckBox->SetCheckNoMsg(true);
				return false;
			}

			pCheckBox->SetEnabled(false);
			CLabelUI* plb = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbTVWal"), pItem);
			if (plb)
			{
				plb->SetText(_T("����ǽ"));
			}
		}
	}
	if (m_nSelIndex == 0)
	{
		g_nTVWallLWaiting = SetTimer( NULL, m_nSelIndex, 4000, CBTimerFun); //�����ɹ��� �ȴ�4��
	}
	if (m_nSelIndex == 2)
	{
		g_nTVWallRWaiting = SetTimer( NULL, m_nSelIndex, 4000, CBTimerFun); //�����ɹ��� �ȴ�4��
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

		//�����Ļ״̬
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

	//����ʱ���ؾ���������������ͼ�� --add by wangkui 2016-9-19
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
					strId = _T("����");
				}
				break;
			case 1:
				{
					strId = _T("����");
				}
				break;
			case 2:
				{
					strId = _T("����");
				}
				break;
			}

			CString tip;
			tip.Format(_T("%s˫������ʧ��"),strId);
			if ( emTpNoSource == emTpDualIdleReason)
			{
				tip = tip + _T(":����ʧ�ܣ�����ƵԴ");
			}
			else if ( emTpBussyNow == emTpDualIdleReason)
			{
				tip = tip + _T(":����ʧ�ܣ��᳡æ���ڻ�����");
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
// 		if (g_wSpareDualStateTimerID == 0 && bSuccess)//��¼ʱ�յ���Ϣ ��������˫����ʾ 1s��ˢ�� ֱ��ˢ�²���ʾ
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
		//if (!m_bInConf)//���� ˫��
		{
			if (tScrnInfo.emPosPic == emPic_SelDual  || tScrnInfo.emPosPic == emPic_Dual)
			{   
				strScreenPic = _T("res/cnsmanage/screendual.png");
				strlbscreentip = _T("˫��");
				//����ʱ �ɹ���ʾ˫�� ��״̬�ı�
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
	{	//������ϯȫ��
		m_pm->DoCase( _T("CaseSeatAllSpk") );
	}
	else if( CN_INNERSPEAKER_NONE == bySeatId )
	{
		//ȫ����
		m_pm->DoCase( _T("caseSeatAllNotSpk") );
	}
	else
	{	//�Ȱ�������ϯ����Ϊ������
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
