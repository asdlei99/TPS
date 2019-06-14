#include "StdAfx.h"
#include "videomixlogic.h"
#include "confmsglogic.h"

template<> CVideoMixLogic* Singleton<CVideoMixLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CVideoMixLogic, CNotifyUIImpl)

    MSG_ITEMSELECTD(_T("ComboSelMix"), OnComboSelMix)
    MSG_CLICK(_T("BtnChooseMixStyle"), OnChooseMixStyle)  

    MSG_ITEMCLICK(_T("VideoMixStyleItem"), OnVideoMixStyleClick)
    MSG_CLICK(_T("BtnVidMixStyleOK"), OnBtnVidMixStyleOK)  
    MSG_CLICK(_T("BtnVidMixStyleCancle"), OnBtnVidMixStyleCancel)  
    
    MSG_CLICK(_T("BtnVideoMixCfg"), OnBtnVideoMixCfg) 

    MSG_CLICK(_T("BtnDeleteAll"), OnBtnVmpDeleteAll) 
    MSG_CLICK(_T("BtnSaveVmpCfg"), OnBtnSaveVmpCfg) 
    MSG_CLICK(_T("BtnCallVmpCfg"), OnBtnCallVmpCfg) 
    
    MSG_CLICK(_T("BtnVidMixAddCns"), OnBtnVidMixAddCns) 
    MSG_CLICK(_T("BtnFollowSpeaker"), OnBtnFollowSpeaker)
    MSG_CLICK(_T("BtnFollowDual"), OnBtnFollowDual)    
    MSG_CLICK(_T("BtnMixSelCns"), OnBtnMixSelCns)
    MSG_CLICK(_T("BtnMixDelete"), OnBtnMixDelete)
    
    MSG_CLICK(_T("BtnVidMixSelOK"), OnBtnSelRoomOK)
    MSG_CLICK(_T("BtnVidMixSelAll"), OnBtnSelAll)
    MSG_CLICK(_T("BtnVidMixSelCancel"), OnBtnSelCancel)
	MSG_CLICK(_T("BtnMixShowScreen"), OnBtnMixShowScreen)
	MSG_CLICK(_T("BtnMixHideScreen"), OnBtnMixHideScreen)
    MSG_SELECTCHANGE(_T("BtnMixRoomSel"), OnCheckConfCnsItem)
	MSG_SELECTCHANGE(_T("MixCheckSrceen"), OnMixCheckSrceen)

    MSG_SELECTCHANGE(_T("CheckOpenVidMix"), OnCheckOpenVidMix)
    MSG_SELECTCHANGE(_T("CheckMixBroadcast"),  OnCheckMixBroadcast)
    MSG_SELECTCHANGE(_T("CheckVideoMixShortCut"), OnCheckVideoMixShortCut)

    MSG_LETTERINDEX_CLICK(_T("VidMixListIndex"),OnLetterIndex)
    MSG_EDITCHANGE(_T("EdtSearch"), OnSearchEditChange)	

    USER_MSG(UI_CNS_BRDVMP_NTY, OnBrdVmpNty)
    USER_MSG(UI_UMS_REFRESH_CONFCNS_LIST,OnRefreshCnsList)
	USER_MSG(UI_CNS_RERVESBRDVMP_IND,OnRervesBrdVmpInd)
    USER_MSG(UI_CNS_SAVEVMPCFG_IND,OnSaveVmpCfgInd) 
    USER_MSG(UI_CNS_CONFSTATE_NOTIFY,OnConfStateNty) 
    
    USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)
	USER_MSG(UI_CNC_SHORTCUT_VMIX,OnShortCutVMix)	

APP_END_MSG_MAP()

CVideoMixLogic::CVideoMixLogic(void)
{
    m_pMixCfgList = NULL;
    //m_emVmpStyle = tp_VmpStyle_DYNAMIC;
    m_nCtrlIndex = -1;
    m_nCurrentVmpIndex = -1;
    m_bVmpAuto = TRUE;
    m_bWaitRerves = FALSE;

    m_bIsSelAll = false;

	m_strArrayScreen[0] = _T("(左)");
	m_strArrayScreen[1] = _T("(中)");
	m_strArrayScreen[2] = _T("(右)");
}


CVideoMixLogic::~CVideoMixLogic(void)
{
}



bool CVideoMixLogic::OnComboSelMix(TNotifyUI& msg)
{
    if (m_nCurrentVmpIndex != msg.wParam )
    {
        m_nCurrentVmpIndex = msg.wParam;

        if ( m_nCurrentVmpIndex > m_vctBrdVmpInfo.size() )
        {
            return false;
        }

        m_tCurrentBrdVmp = m_vctBrdVmpInfo.at(m_nCurrentVmpIndex);

        //占用画面合成器
        //ComInterface->RervesBrdVmpReq( m_tCurrentBrdVmp.m_tEqpInfo );
        UpdateVmpUIState();

        m_tLocalVmpStyle = m_tCurrentBrdVmp.m_tVmpStyle;

        m_bVmpAuto = m_tCurrentBrdVmp.m_bVmpAuto;

        UpdateVmpCfgLayout( );
    }

    if ( m_nCurrentVmpIndex == -1 )
    {
        m_pm->DoCase( _T("caseVidMixNoSelMix") );
    }
    else
    {
        m_pm->DoCase( _T("caseVidMixSelMix") );
    }    
    return true;
}



bool CVideoMixLogic::OnChooseMixStyle(TNotifyUI& msg)
{
    if ( m_nCurrentVmpIndex == -1 )
    {
        ShowMessageBox( _T("请先选择画面合成器") );
        return false;
    }

    if ( m_tCurrentBrdVmp.m_emStat != EmBrdVmpStat_Normal && m_tCurrentBrdVmp.m_emStat != EmBrdVmpStat_Brd )
    {
        ShowMessageBox( _T("请先开启画面合成器") );
        return false;
    }

    ICncCommonOp::ShowControl( true, m_pm, _T("PageVidMixStyle") );

    //选中当前Style
    for( int i = 0; i < m_vctMixStyleInfo.size(); i++ )
    {
        TVidMixStyleInfo tStyle = m_vctMixStyleInfo.at(i);
        if ( tStyle.emVmpStyle == m_tCurrentBrdVmp.m_tVmpStyle.m_emVmpStyle )
        {
            CTouchListUI* pMixStyleList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MixStyleList") );
            if ( pMixStyleList != NULL )
            {
                pMixStyleList->SelectItem(i);
            }
            break;
        }
    } 
    
    return true;
}

bool CVideoMixLogic::OnCheckOpenVidMix(TNotifyUI& msg)
{
    CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
    if ( pCheckBox == NULL )
    {
        return false;
    }

    BOOL32 bOpen = FALSE;
    if ( pCheckBox->GetCheck() )
    {
        bOpen = TRUE;
    }

    if ( bOpen && ( m_tCurrentBrdVmp.m_emStat == EmBrdVmpStat_Normal || m_tCurrentBrdVmp.m_emStat == EmBrdVmpStat_Brd ) )
    {
        return true;
    }
    if ( !bOpen && (m_tCurrentBrdVmp.m_emStat !=  EmBrdVmpStat_Normal && m_tCurrentBrdVmp.m_emStat != EmBrdVmpStat_Brd ) )
    {
        return true;
    }

    TRersvesEqpReq tRersvesEqp;
    tRersvesEqp.m_wConfID =  m_tCurrentBrdVmp.m_wConfID;
    tRersvesEqp.m_tEqp = m_tCurrentBrdVmp.m_tEqpInfo;
    tRersvesEqp.m_bRersves = bOpen;
    ComInterface->RervesBrdVmpReq( tRersvesEqp );

    if ( bOpen )
    {
        m_bWaitRerves = TRUE;
    }   

    return true;
}

bool CVideoMixLogic::OnCheckMixBroadcast(TNotifyUI& msg)
{
    CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
    if ( pCheckBox == NULL )
    {
        return false;
    }

    BOOL32 bOpen = FALSE;
    if ( pCheckBox->GetCheck() )
    {
        bOpen = TRUE;
    }

    if ( bOpen && m_tCurrentBrdVmp.m_emStat == EmBrdVmpStat_Brd )
    {
        return true;
    }
    if ( !bOpen && m_tCurrentBrdVmp.m_emStat != EmBrdVmpStat_Brd )
    {
        return true;
    }

    if ( bOpen && (m_tCurrentBrdVmp.m_emStat !=  EmBrdVmpStat_Normal && m_tCurrentBrdVmp.m_emStat != EmBrdVmpStat_Brd ) )
    {
        pCheckBox->SetCheckNoMsg( false );
        ShowMessageBox( _T("请先开启画面合成器") );      
        return true;
    }

    TBrdVmpReq tBrdVmp;
    tBrdVmp.m_wConfID = m_tCurrentBrdVmp.m_wConfID;
    tBrdVmp.m_tEqp = m_tCurrentBrdVmp.m_tEqpInfo;
    tBrdVmp.m_bBrd = bOpen;

    ComInterface->SetBroadcastVmpReq(tBrdVmp);

    return true;
}

bool CVideoMixLogic::OnCheckVideoMixShortCut(TNotifyUI& msg)
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

	EM_ShortcutType em = emShortcutPicSynthesis;
	NOTIFY_MSG( UI_CNC_SET_SHORTCUT_NTY, em, bIsSet );
    return true;
}


bool CVideoMixLogic::OnVideoMixStyleClick(TNotifyUI& msg)
{
    if ( const CListContainerElementUI *pItem = dynamic_cast<const CListContainerElementUI*>(msg.pSender) )
    {
        int nIndex = pItem->GetIndex();

        if ( nIndex < m_vctMixStyleInfo.size() )
        {
            m_tChooseStyleInfo = m_vctMixStyleInfo.at(nIndex);
        }
    }

    return true;
}


bool CVideoMixLogic::OnBtnVidMixStyleOK(TNotifyUI& msg)
{
    if ( (m_tLocalVmpStyle.m_emVmpStyle != m_tChooseStyleInfo.emVmpStyle) || ( m_bVmpAuto && m_tChooseStyleInfo.emVmpStyle != tp_VmpStyle_DYNAMIC ) )
    {
        //m_emVmpStyle = m_tChooseStyleInfo.emVmpStyle;
        m_tLocalVmpStyle.m_emVmpStyle = m_tChooseStyleInfo.emVmpStyle;
        m_tLocalVmpStyle.m_wChnlNum = m_tChooseStyleInfo.nChnlNum;

        if ( m_bVmpAuto && m_tLocalVmpStyle.m_emVmpStyle != tp_VmpStyle_DYNAMIC )
        {
            m_bVmpAuto = FALSE;
        }

        if ( !m_bVmpAuto )//
        {
            for ( int i = 0; i < TP_VMP_MAX_IN_CHN_NUM; i++ )
            {
                if ( i >= m_tLocalVmpStyle.m_wChnlNum )
                {
                    m_tLocalVmpStyle.m_atVmpChnl[i].Clear();
                }
            }
        }      

        ICncCommonOp::SetControlText( m_tChooseStyleInfo.achStyleName, m_pm, _T("BtnChooseMixStyle") );

        if( m_tCurrentBrdVmp.m_emStat == EmBrdVmpStat_Normal || m_tCurrentBrdVmp.m_emStat == EmBrdVmpStat_Brd )
        {
            SetBrdVmpReq();
        }
        else
        {
            UpdateVmpCfgLayout();
        }
    }

    ICncCommonOp::ShowControl( false, m_pm, _T("PageVidMixStyle") );

    return true;
}

bool CVideoMixLogic::OnBtnVidMixStyleCancel(TNotifyUI& msg)
{
    ICncCommonOp::ShowControl( false, m_pm, _T("PageVidMixStyle") );
    return true;
}


bool CVideoMixLogic::OnBtnVmpDeleteAll(TNotifyUI& msg)
{
    if ( m_nCurrentVmpIndex == -1 )
    {
        return false;
    }

    //自动模式不能操作
    if ( m_bVmpAuto || m_tLocalVmpStyle.m_emVmpStyle == tp_VmpStyle_DYNAMIC )
    {
        return true;
    }

    m_tLocalVmpStyle.m_wSpeakerIndx = TP_INVALID_INDEX;
    m_tLocalVmpStyle.m_wDualIndx = TP_INVALID_INDEX;
    for ( u16 wIndex = 0; wIndex < TP_VMP_MAX_IN_CHN_NUM; wIndex ++ )
    {
        m_tLocalVmpStyle.m_atVmpChnl[wIndex].Clear();
    }

    if( m_tCurrentBrdVmp.m_emStat == EmBrdVmpStat_Normal || m_tCurrentBrdVmp.m_emStat == EmBrdVmpStat_Brd )
    {
        SetBrdVmpReq();
    }
    else
    {
        UpdateVmpCfgLayout();
    }

    return true;
}


bool CVideoMixLogic::OnBtnFollowSpeaker(TNotifyUI& msg)
{
    CControlUI *pParent = msg.pSender->GetParent()->GetParent();
    if ( CListContainerElementUI *pContainer = dynamic_cast<CListContainerElementUI*>(pParent) )
    {
        int nIndex = pContainer->GetIndex();

        m_tLocalVmpStyle.m_wSpeakerIndx = nIndex;

        if ( m_tLocalVmpStyle.m_wDualIndx == nIndex )
        {
            m_tLocalVmpStyle.m_wDualIndx = TP_INVALID_INDEX;
        }

        if( m_tCurrentBrdVmp.m_emStat == EmBrdVmpStat_Normal || m_tCurrentBrdVmp.m_emStat == EmBrdVmpStat_Brd )
        {
            SetBrdVmpReq();
        }
        else
        {
            UpdateVmpCfgLayout();
        }
    }
    return true;
}

bool CVideoMixLogic::OnBtnFollowDual(TNotifyUI& msg)
{
    CControlUI *pParent = msg.pSender->GetParent()->GetParent();
    if ( CListContainerElementUI *pContainer = dynamic_cast<CListContainerElementUI*>(pParent) )
    {
        int nIndex = pContainer->GetIndex();

        m_tLocalVmpStyle.m_wDualIndx = nIndex;

        if ( m_tLocalVmpStyle.m_wSpeakerIndx == nIndex )
        {
            m_tLocalVmpStyle.m_wSpeakerIndx = TP_INVALID_INDEX;
        }

        if( m_tCurrentBrdVmp.m_emStat == EmBrdVmpStat_Normal || m_tCurrentBrdVmp.m_emStat == EmBrdVmpStat_Brd )
        {
            SetBrdVmpReq();
        }
        else
        {
            UpdateVmpCfgLayout();
        }
    }
    return true;
}

bool CVideoMixLogic::OnBtnVidMixAddCns(TNotifyUI& msg)
{
    CControlUI *pParent = msg.pSender->GetParent();
    if ( CListContainerElementUI *pContainer= dynamic_cast<CListContainerElementUI*>(pParent) )
    {
        m_nCtrlIndex = pContainer->GetIndex();

        ICncCommonOp::SetControlText( _T(""), m_pm, _T("EdtSearch") );

        ICncCommonOp::ShowControl( true, m_pm, _T("PageVidMixSelConfList") );
    }
    return true;
}


bool CVideoMixLogic::OnBtnMixSelCns(TNotifyUI& msg)
{
    CControlUI *pParent = msg.pSender->GetParent()->GetParent();
    if ( CListContainerElementUI *pContainer= dynamic_cast<CListContainerElementUI*>(pParent) )
    {
        m_nCtrlIndex = pContainer->GetIndex();

        ICncCommonOp::SetControlText( _T(""), m_pm, _T("EdtSearch") );

        ICncCommonOp::ShowControl( true, m_pm, _T("PageVidMixSelConfList") );
    }
    return true;
}

bool CVideoMixLogic::OnBtnMixDelete(TNotifyUI& msg)
{
    CControlUI *pParent = msg.pSender->GetParent()->GetParent();
    if ( CListContainerElementUI *pContainer= dynamic_cast<CListContainerElementUI*>(pParent) )
    {
        int nIndex = pContainer->GetIndex();

        if ( m_tLocalVmpStyle.m_wSpeakerIndx == nIndex )
        {
            m_tLocalVmpStyle.m_wSpeakerIndx = TP_INVALID_INDEX;
        }
        if ( m_tLocalVmpStyle.m_wDualIndx == nIndex )
        {
            m_tLocalVmpStyle.m_wDualIndx = TP_INVALID_INDEX;
        }
        if ( nIndex < m_tLocalVmpStyle.m_wChnlNum )
        {
            m_tLocalVmpStyle.m_atVmpChnl[nIndex].Clear();
        }
        
        if( m_tCurrentBrdVmp.m_emStat == EmBrdVmpStat_Normal || m_tCurrentBrdVmp.m_emStat == EmBrdVmpStat_Brd )
        {
            SetBrdVmpReq();
        }
        else
        {
            UpdateVmpCfgLayout();
        }
    }
    return true;
}


bool CVideoMixLogic::OnBtnSelRoomOK(TNotifyUI& msg)
{
    if ( 0 == m_vctSelCnsList.size() )
    {
        ShowMessageBox(_T("请选择要添加的会场"));
        return false;
    }
    int nCurrentIndex = m_nCtrlIndex;
    //TBrdVmpStyle tVmpStyle = m_tCurrentBrdVmp.m_tVmpStyle;
    for ( u16 i = 0; i < m_vctSelCnsList.size(); i++ )
    {
        if ( nCurrentIndex >= m_tLocalVmpStyle.m_wChnlNum )
        {
            break;
        }
        TCnsInfo tCnsInfo = m_vctSelCnsList.at(i).first;
		vector<int> vctSrceen = m_vctSelCnsList.at(i).second;
        if ( tCnsInfo.m_wSpeakerNum == 0 )
        {
            continue;
        }
        if ( tCnsInfo.m_wSpeakerNum == 1 )
        {
            m_tLocalVmpStyle.m_atVmpChnl[nCurrentIndex].m_wEpID = tCnsInfo.m_wEpID;
            m_tLocalVmpStyle.m_atVmpChnl[nCurrentIndex].m_wScrIndx = 1;

            if ( m_tLocalVmpStyle.m_wSpeakerIndx == nCurrentIndex )
            {
                m_tLocalVmpStyle.m_wSpeakerIndx = TP_INVALID_INDEX;
            }
            if ( m_tLocalVmpStyle.m_wDualIndx == nCurrentIndex )
            {
                m_tLocalVmpStyle.m_wDualIndx = TP_INVALID_INDEX;
            }

            nCurrentIndex++;
        }
        else
        {
            u16 wChnlNum = m_tLocalVmpStyle.m_wChnlNum;
            if ( wChnlNum - nCurrentIndex >= vctSrceen.size() )
		    {		
                for ( u16 j = 0; j < vctSrceen.size() ; j++ )
                {
                    if ( nCurrentIndex >= wChnlNum )
                    {
                        break;
                    }
                    m_tLocalVmpStyle.m_atVmpChnl[nCurrentIndex].m_wEpID = tCnsInfo.m_wEpID;
                    m_tLocalVmpStyle.m_atVmpChnl[nCurrentIndex].m_wScrIndx = vctSrceen.at(j);

                    if ( m_tLocalVmpStyle.m_wSpeakerIndx == nCurrentIndex )
                    {
                        m_tLocalVmpStyle.m_wSpeakerIndx = TP_INVALID_INDEX;
                    }
                    if ( m_tLocalVmpStyle.m_wDualIndx == nCurrentIndex )
                    {
                        m_tLocalVmpStyle.m_wDualIndx = TP_INVALID_INDEX;
                    }

                    nCurrentIndex++;
                }
		    }
		    else
		    {
				nCurrentIndex = wChnlNum - vctSrceen.size();
                if (nCurrentIndex < 0)
                {
                    nCurrentIndex = 0;
                }
				for ( u16 j = 0; j < vctSrceen.size() ; j++ )
				{
					if ( nCurrentIndex >= wChnlNum )
					{
						break;
					}
					m_tLocalVmpStyle.m_atVmpChnl[nCurrentIndex].m_wEpID = tCnsInfo.m_wEpID;
					m_tLocalVmpStyle.m_atVmpChnl[nCurrentIndex].m_wScrIndx = vctSrceen.at(j);

					if ( m_tLocalVmpStyle.m_wSpeakerIndx == nCurrentIndex )
					{
						m_tLocalVmpStyle.m_wSpeakerIndx = TP_INVALID_INDEX;
					}
					if ( m_tLocalVmpStyle.m_wDualIndx == nCurrentIndex )
					{
						m_tLocalVmpStyle.m_wDualIndx = TP_INVALID_INDEX;
					}

					nCurrentIndex++;
				}

//                 if ( wChnlNum > 2 )
// 			    {
// 				    if  ( nCurrentIndex == wChnlNum -1 )
// 				    {
//                         int nIndex = nCurrentIndex - 2;
//                         for ( u16 j = 0; j < 3; j++ )
//                         {
//                             if ( nIndex >= wChnlNum )
//                             {
//                                 break;
//                             }
//                             m_tLocalVmpStyle.m_atVmpChnl[nIndex].m_wEpID = tCnsInfo.m_wEpID;
//                             m_tLocalVmpStyle.m_atVmpChnl[nIndex].m_wScrIndx = j;
// 
//                             if ( m_tLocalVmpStyle.m_wSpeakerIndx == nIndex )
//                             {
//                                 m_tLocalVmpStyle.m_wSpeakerIndx = TP_INVALID_INDEX;
//                             }
//                             if ( m_tLocalVmpStyle.m_wDualIndx == nIndex )
//                             {
//                                 m_tLocalVmpStyle.m_wDualIndx = TP_INVALID_INDEX;
//                             }
// 
//                             nIndex++;
//                         }
//                         nCurrentIndex++;
// 				    }
// 				    else if ( nCurrentIndex == wChnlNum -2 )
// 				    {
//                         int nIndex = nCurrentIndex - 1;
//                         for ( u16 j = 0; j < 3; j++ )
//                         {
//                             if ( nIndex >= wChnlNum )
//                             {
//                                 break;
//                             }
//                             m_tLocalVmpStyle.m_atVmpChnl[nIndex].m_wEpID = tCnsInfo.m_wEpID;
//                             m_tLocalVmpStyle.m_atVmpChnl[nIndex].m_wScrIndx = j;
// 
//                             if ( m_tLocalVmpStyle.m_wSpeakerIndx == nIndex )
//                             {
//                                 m_tLocalVmpStyle.m_wSpeakerIndx = TP_INVALID_INDEX;
//                             }
//                             if ( m_tLocalVmpStyle.m_wDualIndx == nIndex )
//                             {
//                                 m_tLocalVmpStyle.m_wDualIndx = TP_INVALID_INDEX;
//                             }
// 
//                             nIndex++;
//                         }
//                         nCurrentIndex+=2;
// 				    }
// 			    }
// 			    else if ( wChnlNum == 2 )
// 			    {
// 				    m_tLocalVmpStyle.m_atVmpChnl[0].m_wEpID = tCnsInfo.m_wEpID;
//                     m_tLocalVmpStyle.m_atVmpChnl[0].m_wScrIndx = 0;
//                     m_tLocalVmpStyle.m_atVmpChnl[1].m_wEpID = tCnsInfo.m_wEpID;
//                     m_tLocalVmpStyle.m_atVmpChnl[1].m_wScrIndx = 1;
// 				
// 				    m_tLocalVmpStyle.m_wSpeakerIndx = TP_INVALID_INDEX;
//                     m_tLocalVmpStyle.m_wDualIndx = TP_INVALID_INDEX;
//                     nCurrentIndex = 2;
// 			    }
// 			    else if ( wChnlNum == 1 )
// 			    {
//                     m_tLocalVmpStyle.m_atVmpChnl[0].m_wEpID = tCnsInfo.m_wEpID;
//                     m_tLocalVmpStyle.m_atVmpChnl[0].m_wScrIndx = 0;
//                     nCurrentIndex++;
// 			    }
            }
        }
    }

    if ( m_vctSelCnsList.size() > 0 )
    {
        if( m_tCurrentBrdVmp.m_emStat == EmBrdVmpStat_Normal || m_tCurrentBrdVmp.m_emStat == EmBrdVmpStat_Brd )
        {
            SetBrdVmpReq(); 
        }
        else
        {
            UpdateVmpCfgLayout();
        }
    }
    
    m_vctSelCnsList.clear();
    UpdateShowList();
    ICncCommonOp::ShowControl( false, m_pm, _T("PageVidMixSelConfList") );

    if ( m_nCtrlIndex != -1 )
    {
        CListContainerElementUI *pLastSel = (CListContainerElementUI*)m_pMixCfgList->GetItemAt(m_nCtrlIndex);
        if ( pLastSel != NULL )
        {
            UpdateVmpCfgItem( m_nCtrlIndex, pLastSel );
            CString strLastSel = pLastSel->GetUserData();
            int j = _ttoi(strLastSel);
            TVidMixBkgImg tLastBkgImg;
            if ( j < m_vctMixBkgImg.size() )
            {
                tLastBkgImg = m_vctMixBkgImg.at(j);
            }
            pLastSel->SetBkImage( tLastBkgImg.achVidNormalImgPath  );
        }
    } 

    return true;
}

bool CVideoMixLogic::OnBtnSelCancel(TNotifyUI& msg)
{
    ICncCommonOp::ShowControl( false, m_pm, _T("PageVidMixSelConfList") );
    m_vctSelCnsList.clear();
    UpdateShowList();
    return true;
}

bool CVideoMixLogic::OnBtnSelAll(TNotifyUI& msg)
{
//     m_vctSelCnsList = m_vctCnsList;
//     UpdateCnsList();

	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("VidMixCnsConfList") );
	if ( pTileLayoutUI == NULL )
	{
		return false;
	}
	m_bIsSelAll = !m_bIsSelAll;
	if ( m_bIsSelAll )
	{
		ICncCommonOp::SetControlText(_T("取消全选"),m_pm,_T("BtnVidMixSelAll"));
		for ( int i = 0; i <  pTileLayoutUI->GetCount(); i++ )
		{		
			CListContainerElementUI *pListContainer = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(i);
			CCheckBoxUI* pCheckBoxItemSel = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("BtnMixRoomSel"), pListContainer);

			if ( pCheckBoxItemSel && !pCheckBoxItemSel->GetCheck())
			{
				pCheckBoxItemSel->SetCheck(true);
			}
		}
	}
	else
	{
		ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnVidMixSelAll"));
		for ( int i = 0; i <  pTileLayoutUI->GetCount(); i++ )
		{		
			CListContainerElementUI *pListContainer = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(i);
			CCheckBoxUI* pCheckBoxItemSel = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("BtnMixRoomSel"), pListContainer);

			if ( pCheckBoxItemSel )
			{
				pCheckBoxItemSel->SetCheck(false);
			}

		}
	}

    return true;
}


bool CVideoMixLogic::OnBtnMixShowScreen(TNotifyUI& msg)
{
	CTouchListUI* pList = (CTouchListUI*)ICncCommonOp::FindControl(m_pm,_T("VidMixCnsConfList"));
	if (!pList)
	{
		return false;
	}
	CListContainerElementUI *pListContainer = (CListContainerElementUI*)msg.pSender->GetParent();
	if (!pListContainer)
	{
		return false;
	}
	//设置选中,条目改变会自动调用OnCnsInfoListItemClick
	int dwSelIndex = pList->GetItemIndex(pListContainer);
	pList->SelectItem(dwSelIndex);
	if (dwSelIndex == -1)
	{
		ICncCommonOp::EnableControl(false,m_pm,_T("BtnSetWatch1"));
		ICncCommonOp::EnableControl(false,m_pm,_T("BtnSetWatch2"));
		ICncCommonOp::EnableControl(false,m_pm,_T("BtnSetWatch3"));
	}
	else
	{
		ICncCommonOp::EnableControl(true,m_pm,_T("BtnSetWatch1"));
		ICncCommonOp::EnableControl(true,m_pm,_T("BtnSetWatch2"));
		ICncCommonOp::EnableControl(true,m_pm,_T("BtnSetWatch3"));
	}

	m_pm->DoCase(_T("caseMixShowScreenOption"), pListContainer);
	return true;
}

bool CVideoMixLogic::OnBtnMixHideScreen(TNotifyUI& msg)
{
	CTouchListUI* pList = (CTouchListUI*)ICncCommonOp::FindControl(m_pm,_T("VidMixCnsConfList"));
	if (!pList)
	{
		return false;
	}
	CListContainerElementUI *pListContainer = (CListContainerElementUI*)msg.pSender->GetParent();
	if (!pListContainer)
	{
		return false;
	}
	CTouchListUI* pListScreenSlect = (CTouchListUI*)ICncCommonOp::FindControl(m_pm, _T("MixScreenSlectList"), pListContainer);
	if (!pListScreenSlect)
	{
		return false;
	}

	pListScreenSlect->SelectItem(-1);
	m_pm->DoCase(_T("caseMixHideScreenOption"), pListContainer);

	return true;
}

bool CVideoMixLogic::OnCheckConfCnsItem(TNotifyUI& msg)
{
    if (msg.pSender->GetParent()->GetParent()->GetName() != _T("VidMixCnsConfList"))
    {
        return false;
    }
    CControlUI *pParent = msg.pSender->GetParent();
    if ( CListContainerElementUI *pItem = dynamic_cast<CListContainerElementUI*>(pParent) )
    {
        TCnsInfo tCnsInfo = *(TCnsInfo*)pItem->GetTag();

        CCheckBoxUI *pCheckBox = (CCheckBoxUI*)msg.pSender;
        bool bCheck = pCheckBox->GetCheck();

//         if ( bCheck )
//         {
//             pItem->SetBkImage( _T("res\\list\\item_sel.png") );
// 
// 			if (m_vctSelCnsList.size() == m_vctCurrentCnsList.size())
// 			{
// 				ICncCommonOp::SetControlText(_T("取消全选"),m_pm,_T("BtnVidMixSelAll"));
// 				m_bIsSelAll = true;
// 			}
// 
//         }
//         else
//         {
//             pItem->SetBkImage( _T("res\\list\\item_normal.png") );
// 
// 			if (m_vctSelCnsList.size() == (m_vctCurrentCnsList.size() - 1))
// 			{
// 				ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnVidMixSelAll"));
// 				m_bIsSelAll = false;
// 			}
// 
//         }	

		//屏幕按钮设置tag表示哪一个屏
		CTouchListUI* pTouchList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MixScreenSlectList"), pItem);
		if (pTouchList)
		{
			for (int i = 0 ; i < tCnsInfo.m_wSpeakerNum ; i++)
			{
				CListContainerElementUI *pItem = (CListContainerElementUI*)pTouchList->GetItemAt(i);
				CCheckBoxUI* pCheckSrceen = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("MixCheckSrceen"), pItem);
				if (pCheckSrceen)
				{
					pCheckSrceen->SetCheck(bCheck);
				}
			}
		}
    }
    return true;
}

bool CVideoMixLogic::OnMixCheckSrceen( TNotifyUI& msg )
{
	CCheckBoxUI* pControl = (CCheckBoxUI*)msg.pSender;
	int nSrceenSel = pControl->GetTag();
	CListContainerElementUI* pListContainerElement = (CListContainerElementUI*)msg.pSender->GetParent()->GetParent()->GetParent();
	if (!pListContainerElement || pListContainerElement->GetName() != _T("MixScreenSelWatchItem"))
	{
		return false;
	}
	TCnsInfo tCnsInfo = *(TCnsInfo*)pListContainerElement->GetTag();
	//查看已选列表中是否存在改会场
	int nSelIndex = -1;//-1表示不存在，其它表示存在的位置
	for (int i = 0 ; i < m_vctSelCnsList.size() ; i++)
	{
		if ( m_vctSelCnsList.at(i).first == tCnsInfo )
		{
			nSelIndex = i;
			break;
		}		
	}

	if (pControl->GetCheck())
	{
		pListContainerElement->SetBkImage( _T("res\\list\\item_sel.png") );
		if (nSelIndex == -1)//不存在则新加
		{
			vector<int> vctSrceenTmp;
			vctSrceenTmp.push_back(nSrceenSel);
			m_vctSelCnsList.push_back(pair<TCnsInfo,vector<int>>(tCnsInfo,vctSrceenTmp));
		}
		else//存在则新加屏幕
		{
			vector<int>::iterator it = find(m_vctSelCnsList.at(nSelIndex).second.begin(),m_vctSelCnsList.at(nSelIndex).second.end(),nSrceenSel);
			if (it == m_vctSelCnsList.at(nSelIndex).second.end())
			{
				m_vctSelCnsList.at(nSelIndex).second.push_back(nSrceenSel);
			}
			//会场选中按钮重置
			if (m_vctSelCnsList.at(nSelIndex).second.size() == 3)
			{
				CCheckBoxUI* pCheckBoxRoomSel = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("BtnMixRoomSel"), pListContainerElement);
				if (pCheckBoxRoomSel)
				{
					pCheckBoxRoomSel->SetCheckNoMsg(true);
				}
			}
		}
		//判断是否全选
		bool isSelAll = true;
		if (m_vctSelCnsList.size() == m_vctCurrentCnsList.size())
		{
			for (int i = 0 ; i < m_vctSelCnsList.size() ; i++)
			{
				TCnsInfo tCnsInfo = m_vctSelCnsList.at(i).first;
				vector<int> vctSrceen = m_vctSelCnsList.at(i).second;
				if (tCnsInfo.m_wSpeakerNum == 3 && vctSrceen.size() < 3)
				{
					isSelAll = false;
					break;
				}
			}
		}
		else
		{
			isSelAll = false;
		}
		if (isSelAll)
		{
			ICncCommonOp::SetControlText(_T("取消全选"),m_pm,_T("BtnVidMixSelAll"));
			m_bIsSelAll = true;
		}
	}
	else
	{
		for(vector<int>::iterator it = m_vctSelCnsList.at(nSelIndex).second.begin(); it != m_vctSelCnsList.at(nSelIndex).second.end(); )
		{
			if(*it == nSrceenSel)
			{
				it  =  m_vctSelCnsList.at(nSelIndex).second.erase(it); 
			}
			else
			{
				++it;
			}
		}
		if (m_vctSelCnsList.at(nSelIndex).second.empty())//删除后为空
		{
			m_vctSelCnsList.erase(m_vctSelCnsList.begin()+nSelIndex);
			pListContainerElement->SetBkImage( _T("res\\list\\item_normal.png") );
		}
		//会场选中按钮重置
		CCheckBoxUI* pCheckBoxRoomSel = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("BtnMixRoomSel"), pListContainerElement);
		if (pCheckBoxRoomSel)
		{
			pCheckBoxRoomSel->SetCheckNoMsg(false);
			//是否全选
			if (m_bIsSelAll)
			{
				ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnVidMixSelAll"));
				m_bIsSelAll = false;
			}
		}
	}
	return true;
}


bool CVideoMixLogic::OnBtnVideoMixCfg(TNotifyUI& msg)
{
    //自动模式不能操作
    if ( m_bVmpAuto || m_tLocalVmpStyle.m_emVmpStyle == tp_VmpStyle_DYNAMIC )
    {
        return true;
    }

    CControlUI *pParent = msg.pSender->GetParent();
    if ( CListContainerElementUI *pContainer= dynamic_cast<CListContainerElementUI*>(pParent) )
    {
        int nIndex = pContainer->GetIndex();
        //TVidMixBkgImg tBkgImg = *(TVidMixBkgImg*)pContainer->GetTag();
        CString str = pContainer->GetUserData();
        int i = _ttoi(str);
        TVidMixBkgImg tBkgImg;
        if ( i < m_vctMixBkgImg.size() )
        {
            tBkgImg = m_vctMixBkgImg.at(i);
        }

        if ( m_nCtrlIndex == -1 )
        {
            m_pm->DoCase( _T("caseVidMixCtrl"), pContainer );
            
            pContainer->SetBkImage( tBkgImg.achVidSelImgPath  );
            m_nCtrlIndex = nIndex;          
        }
        else
        {
            if ( m_nCtrlIndex == nIndex )
            {
                //m_pm->DoCase( _T("caseVidMixNormal"), pContainer );
                UpdateVmpCfgItem( nIndex, pContainer );
                pContainer->SetBkImage( tBkgImg.achVidNormalImgPath  );
                m_nCtrlIndex = -1;
            }
            else
            {
                CListContainerElementUI *pLastSel = (CListContainerElementUI*)m_pMixCfgList->GetItemAt(m_nCtrlIndex);
                //m_pm->DoCase( _T("caseVidMixNormal"), pLastSel );
                if ( pLastSel != NULL )
                {
                    UpdateVmpCfgItem( m_nCtrlIndex, pLastSel );

                    CString strLastSel = pLastSel->GetUserData();
                    int j = _ttoi(strLastSel);
                    TVidMixBkgImg tLastBkgImg;
                    if ( j < m_vctMixBkgImg.size() )
                    {
                        tLastBkgImg = m_vctMixBkgImg.at(j);
                    }
                    pLastSel->SetBkImage( tLastBkgImg.achVidNormalImgPath  );
                }             

                m_pm->DoCase( _T("caseVidMixCtrl"), pContainer );
                pContainer->SetBkImage( tBkgImg.achVidSelImgPath  );
                m_nCtrlIndex = nIndex;
            }
        }
    }
    return true;
}



bool CVideoMixLogic::OnBrdVmpNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    if ( m_bWaitRerves ) //占用合成器时会收到BrdVmpNty消息，此时不更新
    {
        return true;
    }

	m_vctBrdVmpInfo.clear();
    m_vctBrdVmpInfo = ComInterface->GetBrdVmpStatus();

    u8 byEqpID = u8(wParam); //更新的合成器ID
    EmTpOprType emOprType = EmTpOprType(lParam);

    CComboUI* pCombo = (CComboUI*)ICncCommonOp::FindControl( m_pm, _T("ComboSelMix") );
    if ( pCombo == NULL )
    {
        return false;
    }
    pCombo->RemoveAll();
    for ( int i = 0; i < m_vctBrdVmpInfo.size(); i++ )
    {
        CListLabelElementUI *pListLabelElement = 
            (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );

        TBrdVmpResNtfy tBrdVmp = m_vctBrdVmpInfo.at(i);
        pListLabelElement->SetText(  CA2T(tBrdVmp.m_tEqpInfo.m_szEqpAlias) );
        pCombo->Add(pListLabelElement);
    }

    if (m_nCurrentVmpIndex != -1 )
    {
        if ( m_nCurrentVmpIndex >= m_vctBrdVmpInfo.size() )
        {
            m_nCurrentVmpIndex = -1;
            m_tCurrentBrdVmp.Clear();
            m_tLocalVmpStyle.Clear();
            m_bVmpAuto = FALSE;
            UpdateVmpUIState();
            UpdateVmpCfgLayout();
            return false;
        }

        pCombo->SelectItem(m_nCurrentVmpIndex);

        m_tCurrentBrdVmp = m_vctBrdVmpInfo.at(m_nCurrentVmpIndex);

        m_tLocalVmpStyle = m_tCurrentBrdVmp.m_tVmpStyle;

        m_bVmpAuto = m_tCurrentBrdVmp.m_bVmpAuto;

        if ( m_tCurrentBrdVmp.m_tEqpInfo.m_byEqpID == byEqpID || emOprType == tp_OprType_Del )
        {
            UpdateVmpUIState();
            UpdateVmpCfgLayout();
        }        
    }
    else
    {
        //没有选中时，默认选中第一个
        if ( m_vctBrdVmpInfo.size() > 0 )
        {
            m_nCurrentVmpIndex = 0;
            pCombo->SelectItem(m_nCurrentVmpIndex);
            m_tCurrentBrdVmp = m_vctBrdVmpInfo.at(m_nCurrentVmpIndex);
            m_tLocalVmpStyle = m_tCurrentBrdVmp.m_tVmpStyle;

            m_bVmpAuto = m_tCurrentBrdVmp.m_bVmpAuto;

            UpdateVmpUIState();
            UpdateVmpCfgLayout( );
        }
    }

    return true;
}


bool CVideoMixLogic::OnRervesBrdVmpInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    m_bWaitRerves = FALSE;

    BOOL bRersves = (BOOL)wParam;
    EmRervesVmpRet emRet = (EmRervesVmpRet)lParam;
    
    //PrtMsg( "OnRervesBrdVmpInd: m_bRersves:%d, EmRervesVmpRet:%d (2:EmRervesVmpRet_ResFull,3:EmRervesVmpRet_Busy) ",
    //    bRersves, emRet );

    if ( bRersves && emRet == EmRervesVmpRet_Success )
    {
        SetBrdVmpReq();
    }

    if ( emRet != EmRervesVmpRet_Success )
    {
        CString msg;
        switch( emRet )
        {
        case EmRervesVmpRet_DisCnnt:
            msg = _T("断开链接"); 
            break;
        case EmRervesVmpRet_ResFull:
            msg = _T("资源不足");
            break;
        case EmRervesVmpRet_Busy:       
            msg = _T("合成器忙");
            break;
        case EmRervesVmpRet_NoExist:       
            msg = _T("合成器不存在");
            break;
        case EmRervesVmpRet_unKnow:       
            msg = _T("未知原因");
            break;    
        default:
            msg = _T("未知原因");
            break;
        }
        msg = _T("占用画面合成器失败：") + msg;
        ShowPopMsg( msg );

        CCheckBoxUI* pCheckVidMixOpen = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckOpenVidMix"));
        if ( pCheckVidMixOpen != NULL )
        {
            pCheckVidMixOpen->SetCheckNoMsg( false );
        }

        ComInterface->SetCurtVidMixOpen( FALSE );
        NOTIFY_MSG( UI_CNC_VIDMIXSTATUS_NTY );
    }
    
    return true;
}

void CVideoMixLogic::SetBrdVmpReq()
{
    TSetVmpInfoReq tVmpInfo;
    tVmpInfo.m_wConfID = m_tCurrentBrdVmp.m_wConfID;
    tVmpInfo.m_tEqp = m_tCurrentBrdVmp.m_tEqpInfo;
    tVmpInfo.m_tStyle = m_tLocalVmpStyle;
    if ( m_bVmpAuto )
    {
        tVmpInfo.m_tStyle.m_emVmpStyle = tp_VmpStyle_DYNAMIC;
    }
    ComInterface->SetBrdVmpReq( tVmpInfo );
}

void CVideoMixLogic::UpdateVmpUIState()
{
    CCheckBoxUI* pCheckVidMixOpen = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckOpenVidMix"));
    CCheckBoxUI* pCheckBroadcast = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckMixBroadcast"));
    if ( pCheckVidMixOpen == NULL || pCheckBroadcast == NULL )
    {
        return;
    }
    if( m_tCurrentBrdVmp.m_emStat == EmBrdVmpStat_Normal || m_tCurrentBrdVmp.m_emStat == EmBrdVmpStat_Brd )
    {
        pCheckVidMixOpen->SetCheckNoMsg( true );
        if (  m_tCurrentBrdVmp.m_emStat == EmBrdVmpStat_Brd )
        {
            pCheckBroadcast->SetCheckNoMsg( true );
        }
        else 
        {
            pCheckBroadcast->SetCheckNoMsg( false );
        }
        m_pm->DoCase( _T("caseVidMixOn") );

        ComInterface->SetCurtVidMixOpen( TRUE );
    }
    else 
    {
        pCheckVidMixOpen->SetCheckNoMsg( false );
        pCheckBroadcast->SetCheckNoMsg( false );

        m_pm->DoCase( _T("caseVidMixOff") );

        ComInterface->SetCurtVidMixOpen( FALSE );
    }

    NOTIFY_MSG( UI_CNC_VIDMIXSTATUS_NTY );

    if ( m_tCurrentBrdVmp.m_bVmpAuto )
    {
        ICncCommonOp::SetControlText( _T("自动"), m_pm, _T("BtnChooseMixStyle") );
    }
    else
    {
        for( int i = 0; i < m_vctMixStyleInfo.size(); i++ )
        {
            TVidMixStyleInfo tStyle = m_vctMixStyleInfo.at(i);
            if ( tStyle.emVmpStyle == m_tCurrentBrdVmp.m_tVmpStyle.m_emVmpStyle )
            {
                ICncCommonOp::SetControlText( tStyle.achStyleName, m_pm, _T("BtnChooseMixStyle") );
                break;
            }
        }        
    }

}


void CVideoMixLogic::UpdateVmpCfgLayout( )
{
    if ( m_pMixCfgList == NULL )
    {
        return;
    }
    m_pMixCfgList->RemoveAll();
    m_nCtrlIndex = -1;

    BOOL bInConf = ComInterface->IsInConf( &m_tConfInfo );

    switch( m_tLocalVmpStyle.m_emVmpStyle )
    {
    case tp_VmpStyle_DYNAMIC:
        {
            m_pMixCfgList->SetColumns( 1 );
            CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("VideoMixAutoItem") );
            m_pMixCfgList->Add(pListContainer);
        }
        break;
    case tp_VmpStyle_ONE:
        {
            m_pMixCfgList->SetColumns( 1 );
            CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("VideoMixCfgItem") );
            m_pm->DoCase( _T("caseVidMixItem1"), pListContainer );
            pListContainer->SetUserData( _T("1") ); //背景图片类型
            UpdateVmpCfgItem( 0, pListContainer );           
            m_pMixCfgList->Add(pListContainer);
        }
        break;
    case tp_VmpStyle_VTWO:
        {
            m_pMixCfgList->SetColumns( 2 );
            for ( int i = 0; i < 2; i++ ) 
            {
                CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("VideoMixCfgItem") );
                RECT rcPadding = { 0 };
                rcPadding.top = 187;
                pListContainer->SetPadding( rcPadding );
                pListContainer->SetUserData( _T("0") ); //背景图片类型
                UpdateVmpCfgItem( i, pListContainer ); 
                m_pMixCfgList->Add(pListContainer);
            }
        }
        break;
    case tp_VmpStyle_HTWO:
        {
            for ( int i = 0; i < 2; i++ ) 
            {
                CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("VideoMixCfgItem") );
                pListContainer->SetFloat(true);
                if ( i == 0 )
                {              
                    m_pm->DoCase( _T("caseVidMixItem2"), pListContainer );
                    SIZE szXY = { 0, 0 };
                    pListContainer->SetFixedXY(szXY);   
                    pListContainer->SetUserData( _T("5") ); //背景图片类型
                }
                else if ( i == 1 )
                {
                    SIZE szXY = { 613, 373 };
                    pListContainer->SetFixedXY(szXY); 
                    pListContainer->SetUserData( _T("0") );
                }
                UpdateVmpCfgItem( i, pListContainer );
                m_pMixCfgList->Add(pListContainer);
            }
        }
        break;
    case tp_VmpStyle_THREE:
        {
            for ( int i = 0; i < 3; i++ ) 
            {
                CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("VideoMixCfgItem") );
                pListContainer->SetFloat(true);
                if ( i == 0 )
                {              
                    SIZE szXY = { 306, 0 };
                    pListContainer->SetFixedXY(szXY);                                    
                }
                else if ( i == 1 )
                {
                    SIZE szXY = { 0, 373 };
                    pListContainer->SetFixedXY(szXY); 
                }
                else if ( i == 2 )
                {
                    SIZE szXY = { 613, 373 };
                    pListContainer->SetFixedXY(szXY); 
                }
                pListContainer->SetFixedWidth(613);
                pListContainer->SetFixedHeight(373); 
                pListContainer->SetUserData( _T("0") ); //背景图片类型
                UpdateVmpCfgItem( i, pListContainer );
                m_pMixCfgList->Add(pListContainer);
            }
        }
        break;
    case tp_VmpStyle_FOUR:
        {           
            m_pMixCfgList->SetColumns( 2 );
            for ( int i = 0; i < 4; i++ ) 
            {
                CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("VideoMixCfgItem") );
                pListContainer->SetUserData( _T("0") ); //背景图片类型
                UpdateVmpCfgItem( i, pListContainer );
                m_pMixCfgList->Add(pListContainer);
            }
        }
        break;
    case tp_VmpStyle_SPECFOUR:
        {
            UpdateVmpLayoutStyleSpecFour();
        }
        break;
    case tp_VmpStyle_SIX:
        {
            UpdateVmpLayoutStyleSix();         
        }
        break;
    case tp_VmpStyle_SEVEN:
        {
            UpdateVmpLayoutStyleSeven();         
        }
        break;
    case tp_VmpStyle_EIGHT:
        {
            UpdateVmpLayoutStyleEight();         
        }
        break;
    case tp_VmpStyle_NINE:
        {           
            m_pMixCfgList->SetColumns( 3 );
            for ( int i = 0; i < 9; i++ ) 
            {
                CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("VideoMixCfgItem") );              
                m_pm->DoCase( _T("caseVidMixItem9"), pListContainer );
                pListContainer->SetUserData( _T("2") ); //背景图片类型
                UpdateVmpCfgItem( i, pListContainer );
                m_pMixCfgList->Add(pListContainer);
            }
        }
        break;
    case tp_VmpStyle_TEN:
        {
            UpdateVmpLayoutStyleTen();
        }
        break;
    case tp_VmpStyle_TEN_M:
        {
            UpdateVmpLayoutStyleTenM();
        }
        break;
    case tp_VmpStyle_THIRTEEN:
        {
            UpdateVmpLayoutStyleThirteen();
        }
        break;
    case tp_VmpStyle_THIRTEEN_M:
        {
            UpdateVmpLayoutStyleThirteenM();
        }
        break;
    case tp_VmpStyle_SIXTEEN:
        {           
            m_pMixCfgList->SetColumns( 4 );
            for ( int i = 0; i < 16; i++ )
            {
                CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("VideoMixCfgItem") );

                m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
                pListContainer->SetUserData( _T("3") ); //背景图片类型
                UpdateVmpCfgItem( i, pListContainer );
                m_pMixCfgList->Add(pListContainer);
            }
        }
        break;
    case tp_VmpStyle_TWENTY:
        {           
            m_pMixCfgList->SetColumns( 5 );
            for ( int i = 0; i < 20; i++ )
            {
                CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("VideoMixCfgItem") );

                m_pm->DoCase( _T("caseVidMixItem25"), pListContainer );
                pListContainer->SetUserData( _T("4") ); //背景图片类型
                UpdateVmpCfgItem( i, pListContainer );
                m_pMixCfgList->Add(pListContainer);
            }
        }
        break;
    case tp_VmpStyle_TWENTYFIVE:
        {           
            m_pMixCfgList->SetColumns( 5 );
            for ( int i = 0; i < 25; i++ )
            {
                CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("VideoMixCfgItem") );

                m_pm->DoCase( _T("caseVidMixItem25"), pListContainer );
                pListContainer->SetUserData( _T("4") ); //背景图片类型
                UpdateVmpCfgItem( i, pListContainer );
                m_pMixCfgList->Add(pListContainer);
            }
        }
        break;
    default:
        break;
    }
}

void CVideoMixLogic::UpdateVmpCfgItem( u16 wIndex, CListContainerElementUI* pContainerElementUI )
{
    CLabelUI* pLabel =  (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("labMixImg"), pContainerElementUI );
    CLabelUI* pText =  (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("txtMixName"), pContainerElementUI );
	CLabelUI* pScreen =  (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("txtSrceenIndex"), pContainerElementUI );
    if ( pLabel == NULL || pText == NULL || pScreen == NULL )
    {
        return;
    }

    if ( m_bVmpAuto ) //自动模式时不能配置
    {
        m_pm->DoCase( _T("caseVidMixAutoStyle"), pContainerElementUI );
    }

    if ( m_tLocalVmpStyle.m_wSpeakerIndx == wIndex )
    {     
        m_pm->DoCase( _T("caseVidMixInfo"), pContainerElementUI );
        pLabel->SetBkImage( _T("res\\confctrl\\videomix\\imgFolSpk.png") );       
        pText->SetText( _T("发言人跟随") );
    }
    else if ( m_tLocalVmpStyle.m_wDualIndx == wIndex )
    {
        m_pm->DoCase( _T("caseVidMixInfo"), pContainerElementUI );
        pLabel->SetBkImage( _T("res\\confctrl\\videomix\\imgFolDual.png") );
        pText->SetText( _T("双流跟随") );
    }
    else
    {
        if ( wIndex >= m_tLocalVmpStyle.m_wChnlNum )
        {
            return;
        }
        if ( m_tLocalVmpStyle.m_atVmpChnl[wIndex].m_wEpID != TP_INVALID_INDEX )
        {
            m_pm->DoCase( _T("caseVidMixInfo"), pContainerElementUI );
            TCnsInfo *ptCnsInfo = m_tConfInfo.GetCnsInfoByID( m_tLocalVmpStyle.m_atVmpChnl[wIndex].m_wEpID );		
            if ( ptCnsInfo != NULL )
            {
				pText->SetText( CA2T(ptCnsInfo->m_achRoomName) );
                if (ptCnsInfo->m_emEpType != emTPEndpointTypeCNS)
                {
                    pLabel->SetBkImage( _T("res\\confctrl\\videomix\\imgSelOrd.png") );
                }
                else
                {
                    pLabel->SetBkImage( _T("res\\confctrl\\videomix\\imgSelCns.png") );
                }
				if (ptCnsInfo->m_wSpeakerNum == 3)
				{
					u16 wScrIndex = m_tLocalVmpStyle.m_atVmpChnl[wIndex].m_wScrIndx;
					if ( wScrIndex < MAX_SEAT_COUNT )
					{	
						pScreen->SetText( m_strArrayScreen[wScrIndex].c_str() );
					}					
				}
            }
        }
        else
        {
            m_pm->DoCase( _T("caseVidMixNormal"), pContainerElementUI );
        }
    }
    pContainerElementUI->SetTag( (UINT_PTR)&m_tLocalVmpStyle.m_atVmpChnl[wIndex] );
}


void CVideoMixLogic::UpdateVmpLayoutStyleSpecFour()
{
    for ( int i = 0; i < 4; i++ ) 
    {
        CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("VideoMixCfgItem") );
        pListContainer->SetFloat(true);
        if ( i == 0 )
        {              
            SIZE szXY = { 0, 187 };
            pListContainer->SetFixedXY(szXY);    
            pListContainer->SetUserData( _T("0") );
        }
        else if ( i == 1 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613, 113 };         
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 2 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613, 187+113 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 3 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613, 374+113 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        UpdateVmpCfgItem( i, pListContainer );
        m_pMixCfgList->Add(pListContainer);
    }
}


void CVideoMixLogic::UpdateVmpLayoutStyleSix()
{
    for ( int i = 0; i < 6; i++ ) 
    {
        CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("VideoMixCfgItem") );
        pListContainer->SetFloat(true);
        if ( i == 0 )
        {              
            SIZE szXY = { 0, 113 };
            pListContainer->SetFixedXY(szXY);    
            pListContainer->SetFixedWidth(613);
            pListContainer->SetFixedHeight(373);
            pListContainer->SetUserData( _T("0") );
        }
        else if ( i == 1 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613, 113 };         
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 2 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613, 187+113 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 5 )//6画面3、5颠倒
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 0, 373+113 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 4 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307, 373+113 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 3 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613, 373+113 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        UpdateVmpCfgItem( i, pListContainer );
        m_pMixCfgList->Add(pListContainer);
    }
}


bool CVideoMixLogic::OnRefreshCnsList( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    TCMSConf tConfInfo ;
    bool bIn = ComInterface->IsInConf( &tConfInfo );
    m_vctCnsList.clear();
    for (int i = 0; i < tConfInfo.m_vctCnsList.size(); i++)
    {
		TCnsInfo tCnsInfo = tConfInfo.m_vctCnsList.at(i);
		if ( tCnsInfo.m_emEpType == emTPEndpointTypeUMS || tCnsInfo.m_emEpType == emTPEndpointH323MCU )
		{            
			continue;
		}

		if (tCnsInfo.m_bOnline)//只显示在线
		{
            m_vctCnsList.push_back(tConfInfo.m_vctCnsList.at(i));
        }	
    }

    UpdateShowList(); 
    //同时刷新合成列表，防止无会场名称显示的问题
    UpdateVmpCfgLayout();
    return NO_ERROR;
}


void CVideoMixLogic::UpdateCnsList()
{
   
}

void CVideoMixLogic::UpdateShowList()
{
	CTouchListUI* pConfCnsList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("VidMixCnsConfList") );
	if ( pConfCnsList == NULL )
	{
		return;
	}
	pConfCnsList->RemoveAll();
	ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnVidMixSelAll"));
	m_bIsSelAll = false;
	sort( m_vctCnsList.begin(), m_vctCnsList.end(), CUIDataMgr::CnsInfoCompare );

	m_vctCurrentCnsList.clear();
	m_vctCurrentCnsList = m_vctCnsList;

	for ( int i = 0; i < m_vctCnsList.size(); i++ )
	{
		//屏蔽下级会场
		if ( m_vctCnsList.at(i).m_emEpType == emTPEndpointTypeUMS || m_vctCnsList.at(i).m_emEpType == emTPEndpointH323MCU )
		{            
			continue;
		}

		CListContainerElementUI *pListContainer = 
			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("MixScreenSelWatchItem") );

		TCnsInfo tCnsInfo = m_vctCnsList.at(i);

		ICncCommonOp::SetControlText( CA2T(tCnsInfo.m_achRoomName), m_pm, _T("MixAddrEntryName"), pListContainer );
		if (tCnsInfo.m_emEpType == emTPEndpointH323G400)
		{
			ICncCommonOp::SetControlBkImg(_T("res\\list\\imgMonitor.png"), m_pm, _T("MiximgAddrLabel"), pListContainer);
		}
		else if (tCnsInfo.m_emEpType == emTPEndpointTypeVRS)
		{
			ICncCommonOp::SetControlBkImg(_T("res\\list\\imgStudio.png"), m_pm, _T("MiximgAddrLabel"), pListContainer);
		}
		else if (tCnsInfo.m_emEpType != emTPEndpointTypeCNS)
		{
			ICncCommonOp::SetControlBkImg(_T("res\\list\\imgOrdinary.png"), m_pm, _T("MiximgAddrLabel"), pListContainer);
		}
		//屏幕按钮设置tag表示哪一个屏
		CTouchListUI* pTouchList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MixScreenSlectList"), pListContainer);
		if (pTouchList)
		{
			for (int i = 0 ; i < pTouchList->GetCount() ; i++)
			{
				CListContainerElementUI *pItem = (CListContainerElementUI*)pTouchList->GetItemAt(i);
				CCheckBoxUI* pCheckSrceen = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("MixCheckSrceen"), pItem);
				if (pCheckSrceen)
				{
					pCheckSrceen->SetTag(i);
				}
			}
		}

		//三屏会场显示屏幕
		if (3 == tCnsInfo.m_wSpeakerNum)
		{
			m_pm->DoCase(_T("caseMixHideScreenOption"), pListContainer);
		}

		pListContainer->SetTag( (UINT_PTR)&m_vctCnsList.at(i) );

		for (int i = 0 ; i < m_vctSelCnsList.size() ; i++)
		{
			if (m_vctSelCnsList.at(i).first == tCnsInfo)
			{
				CCheckBoxUI *pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("BtnMixConfCnsSel"), pListContainer );
				if ( pCheckBox != NULL )
				{
					pCheckBox->SetCheck(true);
				}
				break;
			}
		}
// 		vector<TCnsInfo>::iterator itfind = find( m_vctSelCnsList.begin(), m_vctSelCnsList.end(), tCnsInfo );
// 		if ( itfind != m_vctSelCnsList.end() )
// 		{
// 			CCheckBoxUI *pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("BtnConfCnsSel"), pListContainer );
// 			if ( pCheckBox != NULL )
// 			{
// 				pCheckBox->SetCheck(true);
// 			}
// 		}

		pConfCnsList->Add(pListContainer);
	}
}



void CVideoMixLogic::InitVideoMixPage()
{
    m_pMixCfgList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MixCfgList") );
    if ( m_pMixCfgList == NULL )
    {
        return;
    }

    CTouchListUI* m_pMixStyleList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MixStyleList") );
    if ( m_pMixStyleList == NULL )
    {
        return;
    }

    for ( int i = 0; i < 18; i++ )
    {
        TVidMixStyleInfo tMixStyleInfo;

        CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("VideoMixStyleItem") );

        CLabelUI* m_pLabel = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("MixStyleImg"), pListContainer );
        switch( i )
        {
        case 0:
            {        
                tMixStyleInfo.emVmpStyle = tp_VmpStyle_DYNAMIC;
                lstrcpyW( tMixStyleInfo.achStyleName, _T("自动") );
                m_pLabel->SetBkImage( _T("res/confctrl/videomix/vidmixstyle/auto.png") );
            }
            break;
        case 1:
            {
                tMixStyleInfo.emVmpStyle = tp_VmpStyle_ONE;
                lstrcpyW( tMixStyleInfo.achStyleName, _T("一画面") );
                tMixStyleInfo.nChnlNum = 1;
                m_pLabel->SetBkImage( _T("res/confctrl/videomix/vidmixstyle/1.png") );
            }         
            break;
        case 2:
            {
                tMixStyleInfo.emVmpStyle = tp_VmpStyle_VTWO;
                lstrcpyW( tMixStyleInfo.achStyleName, _T("二画面") );
                tMixStyleInfo.nChnlNum = 2;
                m_pLabel->SetBkImage( _T("res/confctrl/videomix/vidmixstyle/2-1.png") );
            }       
            break;
        case 3:
            {
                tMixStyleInfo.emVmpStyle = tp_VmpStyle_HTWO;
                lstrcpyW( tMixStyleInfo.achStyleName, _T("二画面") );
                tMixStyleInfo.nChnlNum = 2;
                m_pLabel->SetBkImage( _T("res/confctrl/videomix/vidmixstyle/2-2.png") );
            }
            break;
        case 4:
            {
                tMixStyleInfo.emVmpStyle = tp_VmpStyle_THREE;
                lstrcpyW( tMixStyleInfo.achStyleName, _T("三画面") );
                tMixStyleInfo.nChnlNum = 3;
                m_pLabel->SetBkImage( _T("res/confctrl/videomix/vidmixstyle/3.png") );
            }
            break;
        case 5:
            {
                tMixStyleInfo.emVmpStyle = tp_VmpStyle_FOUR;
                lstrcpyW( tMixStyleInfo.achStyleName, _T("四画面") );
                tMixStyleInfo.nChnlNum = 4;
                m_pLabel->SetBkImage( _T("res/confctrl/videomix/vidmixstyle/4-1.png") );
            }
            break;
        case 6:
            {
                tMixStyleInfo.emVmpStyle = tp_VmpStyle_SPECFOUR;
                lstrcpyW( tMixStyleInfo.achStyleName, _T("四画面") );
                tMixStyleInfo.nChnlNum = 4;
                m_pLabel->SetBkImage( _T("res/confctrl/videomix/vidmixstyle/4-2.png") );
            }
            break;
        case 7:
            {
                tMixStyleInfo.emVmpStyle = tp_VmpStyle_SIX;
                lstrcpyW( tMixStyleInfo.achStyleName, _T("六画面") );
                tMixStyleInfo.nChnlNum = 6;
                m_pLabel->SetBkImage( _T("res/confctrl/videomix/vidmixstyle/6.png") );
            }
            break;
        case 8:
            {
                tMixStyleInfo.emVmpStyle = tp_VmpStyle_SEVEN;
                lstrcpyW( tMixStyleInfo.achStyleName, _T("七画面") );
                tMixStyleInfo.nChnlNum = 7;
                m_pLabel->SetBkImage( _T("res/confctrl/videomix/vidmixstyle/7.png") );
            }
            break;
        case 9:
            {
                tMixStyleInfo.emVmpStyle = tp_VmpStyle_EIGHT;
                lstrcpyW( tMixStyleInfo.achStyleName, _T("八画面") );
                tMixStyleInfo.nChnlNum = 8;
                m_pLabel->SetBkImage( _T("res/confctrl/videomix/vidmixstyle/8.png") );
            }
            break;
        case 10:
            {
                tMixStyleInfo.emVmpStyle = tp_VmpStyle_NINE;
                lstrcpyW( tMixStyleInfo.achStyleName, _T("九画面") );
                tMixStyleInfo.nChnlNum = 9;
                m_pLabel->SetBkImage( _T("res/confctrl/videomix/vidmixstyle/9.png") );
            }
            break;
        case 11:
            {
                tMixStyleInfo.emVmpStyle = tp_VmpStyle_TEN;
                lstrcpyW( tMixStyleInfo.achStyleName, _T("十画面") );
                tMixStyleInfo.nChnlNum = 10;
                m_pLabel->SetBkImage( _T("res/confctrl/videomix/vidmixstyle/10-1.png") );
            }
            break;
        case 12:
            {
                tMixStyleInfo.emVmpStyle = tp_VmpStyle_TEN_M;
                lstrcpyW( tMixStyleInfo.achStyleName, _T("十画面") );
                tMixStyleInfo.nChnlNum = 10;
                m_pLabel->SetBkImage( _T("res/confctrl/videomix/vidmixstyle/10-2.png") );
            }
            break;
        case 13:
            {
                tMixStyleInfo.emVmpStyle = tp_VmpStyle_THIRTEEN;
                lstrcpyW( tMixStyleInfo.achStyleName, _T("十三画面") );
                tMixStyleInfo.nChnlNum = 13;
                m_pLabel->SetBkImage( _T("res/confctrl/videomix/vidmixstyle/13-1.png") );
            }
            break;
        case 14:
            {
                tMixStyleInfo.emVmpStyle = tp_VmpStyle_THIRTEEN_M;
                lstrcpyW( tMixStyleInfo.achStyleName, _T("十三画面") );
                tMixStyleInfo.nChnlNum = 13;
                m_pLabel->SetBkImage( _T("res/confctrl/videomix/vidmixstyle/13-2.png") );
            }
            break;
        case 15:
            {
                tMixStyleInfo.emVmpStyle = tp_VmpStyle_SIXTEEN;
                lstrcpyW( tMixStyleInfo.achStyleName, _T("十六画面") );
                tMixStyleInfo.nChnlNum = 16;
                m_pLabel->SetBkImage( _T("res/confctrl/videomix/vidmixstyle/16.png") );              
            }
            break;
        case 16:
            {
                tMixStyleInfo.emVmpStyle = tp_VmpStyle_TWENTY;
                lstrcpyW( tMixStyleInfo.achStyleName, _T("二十画面") );
                tMixStyleInfo.nChnlNum = 20;
                m_pLabel->SetBkImage( _T("res/confctrl/videomix/vidmixstyle/20.png") );
            }
            break;
        case 17:
            {
                tMixStyleInfo.emVmpStyle = tp_VmpStyle_TWENTYFIVE;
                lstrcpyW( tMixStyleInfo.achStyleName, _T("二十五画面") );
                tMixStyleInfo.nChnlNum = 25;
                m_pLabel->SetBkImage( _T("res/confctrl/videomix/vidmixstyle/25.png") );
            }
            break;
        default:
            break;
        }

        m_vctMixStyleInfo.push_back( tMixStyleInfo );

        //pListContainer->SetTag( (UINT_PTR)&m_vctMixStyleInfo.at(i) );

        m_pMixStyleList->Add(pListContainer);
    }

    //所有背景图片类型
    TVidMixBkgImg tBkgImg;
    tBkgImg.nIndex = 0;
    lstrcpyW( tBkgImg.achVidNormalImgPath, _T("res/confctrl/videomix/4-4bkg.png") );
    lstrcpyW( tBkgImg.achVidSelImgPath, _T("res/confctrl/videomix/4-4selbkg.png") );
    m_vctMixBkgImg.push_back( tBkgImg );

    memset( &tBkgImg, 0, sizeof(tBkgImg) );
    tBkgImg.nIndex = 1;
    lstrcpyW( tBkgImg.achVidNormalImgPath, _T("res/confctrl/videomix/1-1bkg.png") );
    lstrcpyW( tBkgImg.achVidSelImgPath, _T("res/confctrl/videomix/1-1selbkg.png") );
    m_vctMixBkgImg.push_back( tBkgImg );

    memset( &tBkgImg, 0, sizeof(tBkgImg) );
    tBkgImg.nIndex = 2;
    lstrcpyW( tBkgImg.achVidNormalImgPath, _T("res/confctrl/videomix/9-9bkg.png") );
    lstrcpyW( tBkgImg.achVidSelImgPath, _T("res/confctrl/videomix/9-9selbkg.png") );
    m_vctMixBkgImg.push_back( tBkgImg );

    memset( &tBkgImg, 0, sizeof(tBkgImg) );
    tBkgImg.nIndex = 3;
    lstrcpyW( tBkgImg.achVidNormalImgPath, _T("res/confctrl/videomix/16-16bkg.png") );
    lstrcpyW( tBkgImg.achVidSelImgPath, _T("res/confctrl/videomix/16-16selbkg.png") );
    m_vctMixBkgImg.push_back( tBkgImg );

    memset( &tBkgImg, 0, sizeof(tBkgImg) );
    tBkgImg.nIndex = 4;
    lstrcpyW( tBkgImg.achVidNormalImgPath, _T("res/confctrl/videomix/25-25bkg.png") );
    lstrcpyW( tBkgImg.achVidSelImgPath, _T("res/confctrl/videomix/25-25selbkg.png") );
    m_vctMixBkgImg.push_back( tBkgImg );

    memset( &tBkgImg, 0, sizeof(tBkgImg) );
    tBkgImg.nIndex = 5;
    lstrcpyW( tBkgImg.achVidNormalImgPath, _T("res/confctrl/videomix/2-2bkg.png") );
    lstrcpyW( tBkgImg.achVidSelImgPath, _T("res/confctrl/videomix/2-2selbkg.png") );
    m_vctMixBkgImg.push_back( tBkgImg );

    memset( &tBkgImg, 0, sizeof(tBkgImg) );
    tBkgImg.nIndex = 6;
    lstrcpyW( tBkgImg.achVidNormalImgPath, _T("res/confctrl/videomix/8-8bkg.png") );
    lstrcpyW( tBkgImg.achVidSelImgPath, _T("res/confctrl/videomix/8-8selbkg.png") );
    m_vctMixBkgImg.push_back( tBkgImg );

    UpdateVmpCfgLayout();
    UpdateVmpUIState();
}

void CVideoMixLogic::HideVideoMixStylePage()
{
	ICncCommonOp::ShowControl( false, m_pm, _T("PageVidMixStyle") );
}

void CVideoMixLogic::UpdateVmpLayoutStyleSeven()
{
    for ( int i = 0; i < 7; i++ ) 
    {
        CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("VideoMixCfgItem") );
        pListContainer->SetFloat(true);
        if ( i == 0 )
        {              
            SIZE szXY = { 0, 0 };
            pListContainer->SetFixedXY(szXY);    
            pListContainer->SetUserData( _T("0") );
        }
        else if ( i == 1 )
        {
            SIZE szXY = { 613, 0 };
            pListContainer->SetFixedXY(szXY);    
            pListContainer->SetUserData( _T("0") );
            
        }
        else if ( i == 2 )
        {
            SIZE szXY = { 0, 373 };
            pListContainer->SetFixedXY(szXY);    
            pListContainer->SetUserData( _T("0") );
        }
        else if ( i == 3 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613, 373 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 4 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613+307, 373 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 5 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613, 373+187 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 6 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613+307, 373+187 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        UpdateVmpCfgItem( i, pListContainer );
        m_pMixCfgList->Add(pListContainer);
    }
}

void CVideoMixLogic::UpdateVmpLayoutStyleEight()
{
    for ( int i = 0; i < 8; i++ ) 
    {
        CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("VideoMixCfgItem") );
        pListContainer->SetFloat(true);
        if ( i == 0 )
        {       
            m_pm->DoCase( _T("caseVidMixItem8"), pListContainer );
            SIZE szXY = { 0, 0 };
            pListContainer->SetFixedXY(szXY);    
            pListContainer->SetUserData( _T("6") );
        }
        else if ( i == 1 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 921, 0 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 2 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 921, 187 };
            pListContainer->SetFixedXY(szXY);    
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 3 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 921, 187*2 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 7 )//八画面4,5,6,7颠倒
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 0, 560 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 6 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307, 560 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 5 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307*2, 560 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 4 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307*3, 560 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        UpdateVmpCfgItem( i, pListContainer );
        m_pMixCfgList->Add(pListContainer);
    }
}

void CVideoMixLogic::UpdateVmpLayoutStyleTen()
{
    for ( int i = 0; i < 10; i++ ) 
    {
        CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("VideoMixCfgItem") );
        pListContainer->SetFloat(true);
        if ( i == 0 )
        {              
            SIZE szXY = { 0, 0 };
            pListContainer->SetFixedXY(szXY);    
            pListContainer->SetUserData( _T("0") );
        }
        else if ( i == 5 )
        {
            SIZE szXY = { 0, 373 };
            pListContainer->SetFixedXY(szXY);    
            pListContainer->SetUserData( _T("0") );

        }
        else if ( i == 1 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613, 0 };
            pListContainer->SetFixedXY(szXY);    
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 2 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613+307, 0 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 3 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613, 187 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 4 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613+307, 187 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 6 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613, 373 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 7 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613+307, 373 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 8 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613, 187+373 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 9 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613+307, 187+373 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }

        UpdateVmpCfgItem( i, pListContainer );
        m_pMixCfgList->Add(pListContainer);
    }
}

void CVideoMixLogic::UpdateVmpLayoutStyleTenM()
{
    for ( int i = 0; i < 10; i++ ) 
    {
        CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("VideoMixCfgItem") );
        pListContainer->SetFloat(true);
        if ( i == 0 )
        {              
            SIZE szXY = { 0, 187 };
            pListContainer->SetFixedXY(szXY);    
            pListContainer->SetUserData( _T("0") );
        }
        else if ( i == 1 )
        {
            SIZE szXY = { 613, 187 };
            pListContainer->SetFixedXY(szXY);    
            pListContainer->SetUserData( _T("0") );
        }
        else if ( i == 2 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 0, 0 };
            pListContainer->SetFixedXY(szXY);    
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 3 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307, 0 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 4 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307*2, 0 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 5 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307*3, 0 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 6 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 0, 373+187 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 7 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307, 373+187 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 8 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307*2, 373+187 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 9 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307*3, 373+187 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        UpdateVmpCfgItem( i, pListContainer );
        m_pMixCfgList->Add(pListContainer);
    }
}

void CVideoMixLogic::UpdateVmpLayoutStyleThirteen()
{
    for ( int i = 0; i < 13; i++ ) 
    {
        CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("VideoMixCfgItem") );
        pListContainer->SetFloat(true);
        if ( i == 0 )
        {              
            SIZE szXY = { 0, 0 };
            pListContainer->SetFixedXY(szXY);    
            pListContainer->SetUserData( _T("0") );
        }
        else if ( i == 1 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613, 0 };
            pListContainer->SetFixedXY(szXY);    
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 2 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613+307, 0 };
            pListContainer->SetFixedXY(szXY);    
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 3 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613, 187 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 4 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 613+307, 187 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 5 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 0, 373 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 6 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307, 373 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 7 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307*2, 373 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 8 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307*3, 373 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 9 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 0, 373+187 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 10 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307, 373+187 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 11 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307*2, 373+187 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 12 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307*3, 373+187 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        UpdateVmpCfgItem( i, pListContainer );
        m_pMixCfgList->Add(pListContainer);
    }
}

void CVideoMixLogic::UpdateVmpLayoutStyleThirteenM()
{
    for ( int i = 0; i < 13; i++ ) 
    {
        CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("VideoMixCfgItem") );
        pListContainer->SetFloat(true);
        if ( i == 0 )
        {              
            SIZE szXY = { 307, 187 };
            pListContainer->SetFixedXY(szXY);    
            pListContainer->SetUserData( _T("0") );
        }
        else if ( i == 1 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 0, 0 };
            pListContainer->SetFixedXY(szXY);    
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 2 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307, 0 };
            pListContainer->SetFixedXY(szXY);    
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 3 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307*2, 0 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 4 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307*3, 0 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 5 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 0, 187 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 6 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307+613, 187 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 7 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 0, 187*2 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 8 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307+613, 187*2 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 9 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 0, 373+187 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 10 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307, 373+187 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 11 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307*2, 373+187 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        else if ( i == 12 )
        {
            m_pm->DoCase( _T("caseVidMixItem16"), pListContainer );
            SIZE szXY = { 307*3, 373+187 };
            pListContainer->SetFixedXY(szXY); 
            pListContainer->SetUserData( _T("3") );
        }
        UpdateVmpCfgItem( i, pListContainer );
        m_pMixCfgList->Add(pListContainer);
    }
}

bool CVideoMixLogic::OnLetterIndex( TNotifyUI& msg )
{
	int nLetterIndex = (int)msg.wParam;
	CTouchListUI* pTouch = (CTouchListUI*)ICncCommonOp::FindControl(m_pm, _T("VidMixCnsConfList"));
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
	int nItemCount = m_vctCnsList.size();

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
		UIDATAMGR->GetFirstLetter( m_vctCnsList.at(swMidIndex).m_achRoomName, strLetter ); 

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
		UIDATAMGR->GetFirstLetter(m_vctCnsList.at(swMidIndex).m_achRoomName, strLetter ); 

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

bool CVideoMixLogic::OnShortCutVMix( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckOpenVidMix"));
	if ( pCheckBox == NULL )
	{
		return false;
	}

    BOOL32 bOpen = FALSE;
    if ( !pCheckBox->GetCheck() )
    {
        bOpen = TRUE;
    }

    if ( bOpen && ( m_tCurrentBrdVmp.m_emStat == EmBrdVmpStat_Normal || m_tCurrentBrdVmp.m_emStat == EmBrdVmpStat_Brd ) )
    {
        return true;
    }
    if ( !bOpen && (m_tCurrentBrdVmp.m_emStat !=  EmBrdVmpStat_Normal && m_tCurrentBrdVmp.m_emStat != EmBrdVmpStat_Brd ) )
    {
        return true;
    }

    TRersvesEqpReq tRersvesEqp;
    tRersvesEqp.m_wConfID =  m_tCurrentBrdVmp.m_wConfID;
    tRersvesEqp.m_tEqp = m_tCurrentBrdVmp.m_tEqpInfo;
    tRersvesEqp.m_bRersves = bOpen;
    ComInterface->RervesBrdVmpReq( tRersvesEqp );

    if ( bOpen )
    {
        m_bWaitRerves = TRUE;
    } 

	return true;
}

bool CVideoMixLogic::OnConfStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    BOOL32 bInConf = ComInterface->IsInConf();

    //结会后清空状态
    if ( !bInConf )
    {
        m_nCtrlIndex = -1;
        m_nCurrentVmpIndex = -1;
        m_bVmpAuto = TRUE;
        m_bWaitRerves = FALSE;
        m_vctBrdVmpInfo.clear();
        m_vctCnsList.clear();
        m_vctSelCnsList.clear();

        m_tLocalVmpStyle.Clear();
        m_tLocalVmpStyle.m_emVmpStyle = tp_VmpStyle_DYNAMIC;
        UpdateVmpCfgLayout();

        CComboUI* pCombo = (CComboUI*)ICncCommonOp::FindControl( m_pm, _T("ComboSelMix") );
        if ( pCombo != NULL )
        {
            pCombo->RemoveAll();
        }

        ICncCommonOp::SetControlText( _T("自动"), m_pm, _T("BtnChooseMixStyle") );

        CCheckBoxUI* pCheckVidMixOpen = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckOpenVidMix"));
        CCheckBoxUI* pCheckBroadcast = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckMixBroadcast"));
        if ( pCheckVidMixOpen != NULL && pCheckBroadcast != NULL )
        {
            pCheckVidMixOpen->SetCheckNoMsg(false);
            pCheckBroadcast->SetCheckNoMsg(false);
        }
        m_pm->DoCase( _T("caseVidMixNoSelMix") );

        ComInterface->SetCurtVidMixOpen( FALSE );

		ICncCommonOp::ShowControl( false, m_pm, _T("PageVidMixStyle") );//结会隐藏选看样式界面

        NOTIFY_MSG( UI_CNC_VIDMIXSTATUS_NTY );
    }

    return true;
}


bool CVideoMixLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    m_nCtrlIndex = -1;
    m_nCurrentVmpIndex = -1;
    m_bVmpAuto = TRUE;
    m_bWaitRerves = FALSE;
    m_vctBrdVmpInfo.clear();
    m_vctCnsList.clear();
    m_vctSelCnsList.clear();
	UpdateShowList();//清空cnc列表

    m_tLocalVmpStyle.Clear();
    m_tLocalVmpStyle.m_emVmpStyle = tp_VmpStyle_DYNAMIC;
    UpdateVmpCfgLayout();

    CComboUI* pCombo = (CComboUI*)ICncCommonOp::FindControl( m_pm, _T("ComboSelMix") );
    if ( pCombo != NULL )
    {
        pCombo->RemoveAll();
    }

    ICncCommonOp::SetControlText( _T("自动"), m_pm, _T("BtnChooseMixStyle") );

    CCheckBoxUI* pCheckVidMixOpen = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckOpenVidMix"));
    CCheckBoxUI* pCheckBroadcast = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckMixBroadcast"));
    if ( pCheckVidMixOpen != NULL && pCheckBroadcast != NULL )
    {
        pCheckVidMixOpen->SetCheckNoMsg(false);
        pCheckBroadcast->SetCheckNoMsg(false);
    }

    m_pm->DoCase( _T("caseVidMixNoSelMix") );

    ComInterface->SetCurtVidMixOpen( FALSE );

    return true;
}

bool CVideoMixLogic::OnBtnSaveVmpCfg(TNotifyUI& msg)
{
    if ( m_nCurrentVmpIndex == -1 )
    {
        ShowMessageBox( _T("请先选择画面合成器") );
        return false;
    }

    if ( m_tCurrentBrdVmp.m_emStat != EmBrdVmpStat_Normal && m_tCurrentBrdVmp.m_emStat != EmBrdVmpStat_Brd )
    {
        ShowMessageBox( _T("请先开启画面合成器") );
        return false;
    }

    TBrdVmpResNtfy tBrdVmp;
    tBrdVmp.m_wConfID = m_tCurrentBrdVmp.m_wConfID;
    tBrdVmp.m_tEqpInfo = m_tCurrentBrdVmp.m_tEqpInfo;
    tBrdVmp.m_tVmpStyle = m_tLocalVmpStyle;
    if ( m_bVmpAuto )
    {
        tBrdVmp.m_tVmpStyle.m_emVmpStyle = tp_VmpStyle_DYNAMIC;
    }

    ComInterface->SaveVmpCfgReq( tBrdVmp );

    return true;
}

bool CVideoMixLogic::OnBtnCallVmpCfg(TNotifyUI& msg)
{
    if ( m_nCurrentVmpIndex == -1 )
    {
        ShowMessageBox( _T("请先选择画面合成器") );
        return false;
    }

    if ( m_tCurrentBrdVmp.m_emStat != EmBrdVmpStat_Normal && m_tCurrentBrdVmp.m_emStat != EmBrdVmpStat_Brd )
    {
        ShowMessageBox( _T("请先开启画面合成器") );
        return false;
    }

    ComInterface->CallVmpCfgReq( m_tCurrentBrdVmp.m_tEqpInfo );

    return true;
}

bool CVideoMixLogic::OnSaveVmpCfgInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    BOOL bRet = (BOOL)wParam; 

    if ( !bRet )
    {
        ShowPopMsg( _T("保存预案失败") );
    }
	int nSaveIndex = (int)lParam;
	if (nSaveIndex == TP_VMP_MAX_IN_CHN_NUM)
	{
		ShowMessageBox( _T("保存预案成功") );
	}

    return true;
}


bool CVideoMixLogic::OnSearchEditChange( TNotifyUI& msg )
{
	m_vctSelCnsList.clear();
	ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnVidMixSelAll"));
	m_bIsSelAll = false;

    tstring strCaption = ICncCommonOp::GetControlText( m_pm, _T("EdtSearch") );
    if ( strCaption.empty() )
    {
        UpdateShowList();
        return false;
    }

    CString strSearchName;
    strSearchName.Format( _T("%s"), strCaption.c_str() );
   
    CTouchListUI *pConfCnsList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("VidMixCnsConfList") );
    if ( pConfCnsList == NULL )
    {
        return false;
    }
   
    pConfCnsList->RemoveAll();
	m_vctCurrentCnsList.clear();

    for ( u32 i = 0; i < m_vctCnsList.size(); i++ )
    {
        CString strConfName;
        strConfName.Format( _T("%s"),CA2T( m_vctCnsList.at(i).m_achRoomName));
        BOOL bFind = FALSE;			
        bFind = UIDATAMGR->HZPYMatchList( strSearchName, strConfName );
        if ( bFind )
        {
            CListContainerElementUI *pListContainer = 
                (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("MixScreenSelWatchItem") );

            ICncCommonOp::SetControlText( strConfName, m_pm, _T("MixAddrEntryName"), pListContainer );
			if (m_vctCnsList.at(i).m_emEpType == emTPEndpointH323G400)
			{
				ICncCommonOp::SetControlBkImg(_T("res\\list\\imgMonitor.png"), m_pm, _T("MiximgAddrLabel"), pListContainer);
			}
			else if (m_vctCnsList.at(i).m_emEpType == emTPEndpointTypeVRS)
			{
				ICncCommonOp::SetControlBkImg(_T("res\\list\\imgStudio.png"), m_pm, _T("MiximgAddrLabel"), pListContainer);
			}
			else if (m_vctCnsList.at(i).m_emEpType != emTPEndpointTypeCNS)
			{
				ICncCommonOp::SetControlBkImg(_T("res\\list\\imgOrdinary.png"), m_pm, _T("MiximgAddrLabel"), pListContainer);
			}
			//屏幕按钮设置tag表示哪一个屏
			CTouchListUI* pTouchList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MixScreenSlectList"), pListContainer);
			if (pTouchList)
			{
				for (int i = 0 ; i < pTouchList->GetCount() ; i++)
				{
					CListContainerElementUI *pItem = (CListContainerElementUI*)pTouchList->GetItemAt(i);
					CCheckBoxUI* pCheckSrceen = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("MixCheckSrceen"), pItem);
					if (pCheckSrceen)
					{
						pCheckSrceen->SetTag(i);
					}
				}
			}

			//三屏会场显示屏幕
			if (3 == m_vctCnsList.at(i).m_wSpeakerNum)
			{
				m_pm->DoCase(_T("caseMixHideScreenOption"), pListContainer);
			}

            pListContainer->SetTag( (UINT_PTR)&m_vctCnsList.at(i) );

            pConfCnsList->Add(pListContainer);

			m_vctCurrentCnsList.push_back(m_vctCnsList.at(i));
        }
    }

    return true;
}
