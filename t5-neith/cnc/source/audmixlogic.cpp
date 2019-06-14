#include "StdAfx.h"
#include "audmixlogic.h"
#include "messageboxlogic.h"
#include "confmsglogic.h"


template<> CAudMixLogic* Singleton<CAudMixLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CAudMixLogic, CNotifyUIImpl)

	//MSG_ITEMSELECTD(_T("DicListItem"), OnDiscussItemClick)
	MSG_ITEMCLICK(_T("SelDisCnsConfList"), OnSelConfItemClick)
	MSG_ITEMCLICK(_T("DiscussListItem"), OnDiscussListItem)

	MSG_SELECTCHANGE(_T("BtnConfCnsSel"), OnCheckConfItem)

	MSG_CLICK(_T("BtnSelOK"), OnBtnSelRoomOK)
	MSG_CLICK(_T("BtnSelAll"), OnBtnSelAll)
	MSG_CLICK(_T("BtnSelCancel"), OnBtnSelCancel)

	MSG_EDITCHANGE(_T("EdtConfSearch"), OnSearchEditChange)	

	MSG_ITEMSELECTD(_T("ComboAddrShowEx"), OnComboAddrShowEx)

	MSG_CLICK(_T("btnSpeaker"), OnBtnSpeaker)
	MSG_CLICK(_T("btnDelDisc"), OnBtnDelDisc)
	MSG_CLICK(_T("btnChange"), OnBtnChangeConf)

 	MSG_CLICK(_T("btnListLeft"), OnBtnListLeft)
 	MSG_CLICK(_T("btnListRight"), OnBtnListRight)	

	MSG_CLICK(_T("BtnAdd"), OnBtnAddConf)

	MSG_SELECTCHANGE(_T("CheckAudioExcitation"), OnCheckAudioExc)
	MSG_SELECTCHANGE(_T("CheckConfDiscussShortCut"), OnCheckDisShortCut)
	MSG_SELECTCHANGE(_T("CheckStartDicsuss"), OnCheckStartDisc)

	USER_MSG(UI_CNS_CONFSTATE_NOTIFY,OnConfStateNotify)
	USER_MSG(UI_UMS_REFRESH_CONFAUDMIX_LIST,RefreshAudMixList)
	USER_MSG(UI_UMS_REFRESH_CONFCNS_LIST,OnRefreshCnsList)
	USER_MSG(UI_UMS_AUDMIX_DISLISTOPR_IND,OnAudMixDisListOprInd)
	USER_MSG(UI_UMS_AUDMIXVAC_IND,OnAudMixVacOprInd)
	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)
	USER_MSG(UI_UMS_AUDMIXIND,OnStartAudMixInd)
	//切换发言人回应nty消息来直接 直接刷新列表
	USER_MSG(UI_UMS_CHANGE_SPEAKER_NOTIFY,OnSpeakerNty)
	USER_MSG(UI_UMS_SET_SPEAKER_IND,OnSpeakerInd)
	
	USER_MSG( UI_CNS_CONNECTED, OnConnectRsp )

APP_END_MSG_MAP()

CAudMixLogic::CAudMixLogic(void)
{
	m_wCurPageIndex = 0;
	//非操作的变成0页，翻页按钮要重新设置enable
	ICncCommonOp::EnableControl(false,m_pm,_T("btnListLeft"));
	ICncCommonOp::EnableControl(true,m_pm,_T("btnListRight"));
	m_bIsSelAll = false;
	m_dwSelItemId = -1;
	m_bIsSearch = false;
	m_bIsDel = false;
	m_nSpeakerCount = 0;
	m_vctAudmix.clear();
	m_bIsFirstLogin = false;
	m_bIsChangeConf = false;
	m_dwChangeItemIndex = -1;
}

bool CAudMixLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_wCurPageIndex = 0;
	//非操作的变成0页，翻页按钮要重新设置enable
	ICncCommonOp::EnableControl(false,m_pm,_T("btnListLeft"));
	ICncCommonOp::EnableControl(true,m_pm,_T("btnListRight"));

	m_bIsSelAll = false;
	m_dwSelItemId = -1;

	m_bIsSearch = false;
	m_bIsDel = false;
	ICncCommonOp::SetControlText(_T(""), m_pm, _T("EdtConfSearch"));
	m_vctSearchCnsList.clear();

	m_nSpeakerCount = 0;

	m_bIsFirstLogin = false;
	m_bIsChangeConf = false;
	m_dwChangeItemIndex = -1;

	ICncCommonOp::ShowControl( false, m_pm, _T("PageDiscSelConfList") );
	ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnSelAll"));
	m_vctSelConf.clear();
	m_vctAudmix.clear();	
	m_vctCurrentCnsList.clear();

	UpdateCnsList();
	UpdateList();

	return true;
}

CAudMixLogic::~CAudMixLogic(void)
{
}

void CAudMixLogic::UpdateCnsList()
{
	m_bIsSelAll = false;
	m_vctSelConf.clear();
	ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnSelAll"));

	CTouchListUI* pConfCnsList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("OnlinCnsConfList") );
	if ( pConfCnsList == NULL )
	{
		return;
	}
	pConfCnsList->RemoveAll();
	
	sort( m_vctCurrentCnsList.begin(), m_vctCurrentCnsList.end(), CUIDataMgr::CnsInfoCompare );

	for ( int i = 0; i < m_vctCurrentCnsList.size(); i++ )
	{
		CListContainerElementUI *pListContainer = 
			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("ConfCnsListItem") );

		CString strConfName;
		strConfName.Format( _T("%s"),CA2T( m_vctCurrentCnsList.at(i).m_achRoomName));

		ICncCommonOp::SetControlText( strConfName, m_pm, _T("ConfCnsName"), pListContainer );
		if (m_vctCurrentCnsList.at(i).m_emEpType == emTPEndpointH323G400)
		{
			m_pm->DoCase( _T("caseMonitor"), pListContainer ); 
		}
		else if (m_vctCurrentCnsList.at(i).m_emEpType == emTPEndpointTypeVRS)
		{
			m_pm->DoCase( _T("caseStudio"), pListContainer ); 
		}
		else if (m_vctCurrentCnsList.at(i).m_emEpType != emTPEndpointTypeCNS)
		{
			m_pm->DoCase( _T("caseOrdinary"), pListContainer ); 
		}

		pListContainer->SetTag( (UINT_PTR)&m_vctCurrentCnsList.at(i) );

		pConfCnsList->Add(pListContainer);
	}
}

bool CAudMixLogic::UpdateList()
{
	//PrtMsg( "\n[CAudMixLogic::UpdateList]:begin \n");
	m_dwSelItemId = -1;
	m_nSpeakerCount = 0;

	CSlideTabLayoutUI *pSlideTabLayout = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, _T("ConfDiscussSlidetab") );
	if (!pSlideTabLayout)
	{
		return false;
	}

	if (pSlideTabLayout->GetCount() > 0)
	{
		for (int i=0; i<pSlideTabLayout->GetCount(); i++)
		{
			CTouchListUI *pTouchListLayoutUI = (CTouchListUI*)pSlideTabLayout->GetItemAt(i);
			if (pTouchListLayoutUI)
			{
				pTouchListLayoutUI->RemoveAll();
			}
		}

		pSlideTabLayout->RemoveAll();
	}

	u16 wMaxPage = (m_vctAudmix.size()/6)+1; //正好是6的倍数的时候 也要有一页用来放加号	
 	bool bShowBtn = false;
 	if (wMaxPage > 1)
 	{
 		bShowBtn = true;
 	}

	ICncCommonOp::ShowControl(bShowBtn,m_pm,_T("btnListLeft"));
	ICncCommonOp::ShowControl(bShowBtn,m_pm,_T("btnListRight"));

	TCMSConf tConfInfo;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
	if (!bInConf)
	{
		return false;
	}
	bool bStart = (bool)tConfInfo.IsStartAudMix();

	for ( u16 wPage = 0; wPage < wMaxPage ; wPage++ )
	{
		CTouchListUI *pTouchListLayoutUI = NULL;		
		pTouchListLayoutUI = (CTouchListUI*)CONTROLFACTORY()->GetControl( _T("DicListItem") );
		if ( pTouchListLayoutUI == NULL )
		{
			return false;
		}

		for ( u16 wId = 0; wId < 6 ; wId++ )
		{

			CListContainerElementUI *pListContainer = 
				(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("DiscussListItem") );

			u16 index = wPage * 6 + wId;
			if (index >= m_vctAudmix.size())
			{
				if (m_nSpeakerCount >= 27)//大于27 不可添加
				{
                    delete pListContainer;
                    pListContainer = NULL;
					break;
				}

				m_pm->DoCase( _T("caseDiscListNoSel"), pListContainer );    
				pTouchListLayoutUI->Add(pListContainer);
				continue; 
			}

			m_nSpeakerCount = m_nSpeakerCount + m_vctAudmix.at(index).wSpeakerNum;
			ICncCommonOp::SetControlText( m_vctAudmix.at(index).strConfName, m_pm, _T("lbconfName"), pListContainer );
            if (m_vctAudmix.at(index).m_emEpType != emTPEndpointTypeCNS)
            {
                ICncCommonOp::SetControlBkImg(_T("res/list/imgOrdinary.png"), m_pm, _T("lbImg"), pListContainer);
            }
            else
            {
                ICncCommonOp::SetControlBkImg(_T("res/confctrl/confdiscuss/discuss.png"), m_pm, _T("lbImg"), pListContainer);
            }

			CButtonUI* pBtnSpeaker = (CButtonUI*)ICncCommonOp::FindControl( m_pm, _T("btnSpeaker"), pListContainer);
			CButtonUI* pBtnDel = (CButtonUI*)ICncCommonOp::FindControl( m_pm, _T("btnDelDisc"), pListContainer);
			if ( pBtnDel )
			{
				pBtnDel->SetTag( (UINT_PTR)m_vctAudmix.at(index).wCnsID);
			}
			if (pBtnSpeaker)
			{
				if (bStart)
				{
					m_pm->DoCase(_T("caseSpeaker"),pListContainer);
					pBtnSpeaker->SetTag( (UINT_PTR)m_vctAudmix.at(index).wCnsID);
					if (m_vctAudmix.at(index).bIsSpeaker)
					{
						pBtnSpeaker->SetAttribute(_T("focusedimage"),_T("res/confctrl/confdiscuss/cancel_select.png"));
						pBtnSpeaker->SetAttribute(_T("pushedimage"),_T("res/confctrl/confdiscuss/cancel_select.png"));
						pBtnSpeaker->SetAttribute(_T("normalimage"),_T("res/confctrl/confdiscuss/cancel_normal.png"));		
					}
				}
				else
				{
					m_pm->DoCase(_T("caseNoSpeaker"),pListContainer);
				}
			}

			//on状态,只有一个会场不能删除该会场 ；off状态随意删除
			if ( m_vctAudmix.size() == 1)
			{
				if (tConfInfo.IsStartAudMix())
				{
					pBtnDel->SetEnabled(false);
				}
			}

			pTouchListLayoutUI->Add(pListContainer); 
			
		}

		pSlideTabLayout->Add((pTouchListLayoutUI));
	}

    if ( m_wCurPageIndex >= pSlideTabLayout->GetCount() )
    {
        m_wCurPageIndex = pSlideTabLayout->GetCount() - 1;
    }
 	CString strPageIndex = _T("");
 	strPageIndex.Format(_T("%d"),m_wCurPageIndex);
 
 	pSlideTabLayout->SetAttribute(_T("selectedid"), strPageIndex);
	pSlideTabLayout->SetAttribute(_T("pos"), _T("150,0,1586,600"));

    if (m_wCurPageIndex == 0)
    {
        ICncCommonOp::EnableControl(false,m_pm,_T("btnListLeft"));
    }
    else
    {
        ICncCommonOp::EnableControl(true,m_pm,_T("btnListLeft"));
    }
    if ( (m_wCurPageIndex+1)*6 > m_vctAudmix.size())
    {
        ICncCommonOp::EnableControl(false,m_pm,_T("btnListRight"));
    }
    else
    {
        ICncCommonOp::EnableControl(true,m_pm,_T("btnListRight"));
    }

	//PrtMsg( "\n[CAudMixLogic::UpdateList]:end \n");
	return true;
}

bool CAudMixLogic::UpdateList( CString strPresetName, u8 wPageID, u8 wItemID)
{
	CSlideTabLayoutUI *pSlideTabLayout = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, _T("preListSlidetab") );
	if (!pSlideTabLayout)
	{
		return false;
	}

	CTouchListUI *pTileLayoutUI = (CTouchListUI*)pSlideTabLayout->GetItemAt(wPageID);
	if ( pTileLayoutUI == NULL )
	{
		return false;
	}
	CListContainerElementUI *pListContainer = (CListContainerElementUI *)pTileLayoutUI->GetItemAt(wItemID);

	if (pListContainer)
	{
		ICncCommonOp::SetControlText( strPresetName, m_pm, _T("PresetName"), pListContainer );
	}	

	ICncCommonOp::SetControlBkImg(_T(""), m_pm, _T("PresetListItem"), pListContainer );

	return true;
}

bool CAudMixLogic::OnConfStateNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bInConf = ComInterface->IsInConf();
	if ( !bInConf )//结会
	{
		m_vctAudmix.clear();
		m_wCurPageIndex = 0;
		//非操作的变成0页，翻页按钮要重新设置enable
		ICncCommonOp::EnableControl(false,m_pm,_T("btnListLeft"));
		ICncCommonOp::EnableControl(true,m_pm,_T("btnListRight"));

		m_bIsSelAll = false;
		ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnSelAll"));
		m_dwSelItemId = -1;

		m_bIsSearch = false;
		m_bIsDel = false;
		ICncCommonOp::SetControlText(_T(""), m_pm, _T("EdtConfSearch"));
		m_vctSearchCnsList.clear();

		UpdateList();

	}
	else
	{
        //不使用tConfStatus.m_bMixMotive设置会议讨论语音激励状态
		/*TTPCnsConfStatus tConfStatus = ComInterface->GetLocalCnsConfState();
		bool bVacStart = (bool)tConfStatus.m_bMixMotive;
		bool bVacState = false;
		CCheckBoxUI* pVacCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckAudioExcitation"));
		if ( !pVacCheckBox )
		{
			return false;
		}
		if ( pVacCheckBox->GetCheck() )
		{
			bVacState = true;
		}
		if ( bVacState != bVacStart )
		{
			//m_bIsVacInd = true;
			pVacCheckBox->SetCheckNoMsg(bVacStart);
		}*/
	}
	return NO_ERROR;
}

bool CAudMixLogic::OnCheckDisShortCut( TNotifyUI& msg )
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

	EM_ShortcutType em = emShortcutCofDiscuss;
	NOTIFY_MSG( UI_CNC_SET_SHORTCUT_NTY, em, bIsSet );
	return true;
}

bool CAudMixLogic::OnCheckStartDisc( TNotifyUI& msg )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	BOOL32 bIsSet = FALSE;
	if ( pCheckBox->GetCheck() )
	{
		bIsSet = TRUE;
	}

	PrtMsg( "\n[CAudMixLogic::OnCheckStartDisc]:%d \n",bIsSet);

	ICncCommonOp::EnableControl((bool)bIsSet,m_pm,_T("CheckAudioExcitation"));

	TCMSConf tConf;
	BOOL32 bInConf = ComInterface->IsInConf( &tConf );
	if (!bInConf)
	{
		return false;
	}
	if (bIsSet == tConf.IsStartAudMix())
	{
		return true;
	}

	if (bIsSet)
	{
		if ( bInConf )
		{
			if ( m_vctAudmix.size() == 0 )
			{
				u16 wSpeaker = TP_INVALID_INDEX;
				if ( tConf.m_wSpeaker != TP_INVALID_INDEX )
				{
					wSpeaker = tConf.m_wSpeaker;
				}
				else
				{
					wSpeaker = tConf.GetChairCnsID();
				}
				String strCaption;
				TCnsInfo* tCnsInfo = tConf.GetCnsInfoByID( wSpeaker );
				if ( tCnsInfo != NULL )
				{			
					TAudMixCtrls tAudMixCtrls;
					tAudMixCtrls.bIsSpeaker = true;
					tAudMixCtrls.wCnsID = tCnsInfo->m_wEpID;
					tAudMixCtrls.strConfName = tCnsInfo->m_achRoomName;
					m_vctAudmix.insert(m_vctAudmix.begin(),tAudMixCtrls);

					UpdateAudMixLst();
				}
				else
				{
					ShowMessageBox(_T("当前不能开启会议讨论，没有主席"));
					pCheckBox->SetCheckNoMsg(false);
					ICncCommonOp::EnableControl(false,m_pm,_T("CheckAudioExcitation"));
				}
			}
			else
			{
				UpdateAudMixLst();
			}
		}
	}
	else
	{
		if ( bInConf )
		{
			u16 wConfID = tConf.m_wConfID;

			TConfAuxMixInfo tMixInfoList;
			tMixInfoList.m_wConfID = wConfID;
			tMixInfoList.m_bStart = FALSE;
			tMixInfoList.m_atAuxMixList = tConf.m_tAudmixList;

			u16 wRe =  ComInterface->UpdateAudMixList( tMixInfoList );
			if ( wRe != NO_ERROR )
			{
				ShowPopMsg(_T("会议讨论操作失败"));
				pCheckBox->SetCheckNoMsg(!bIsSet);
			}
		}
	}

	return true;
}

bool CAudMixLogic::UpdateAudMixLst()
{
	PrtMsg( "\n[CAudMixLogic::UpdateAudMixLst]:begin \n");
	TCMSConf tConf;
	BOOL32 bInConf = ComInterface->IsInConf( &tConf );
	if ( bInConf )
	{
		u16 wConfID = tConf.m_wConfID;
		TConfAuxMixInfo tMixInfoList;
		tMixInfoList.m_wConfID = wConfID;

		// 获取当前状态下的会议讨论按钮的开关状态 
		bool bState ;
		CCheckBoxUI* pCheckDicsuss = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckStartDicsuss"));
		if ( !pCheckDicsuss )
		{
			return false;
		}
		bState = pCheckDicsuss->GetCheck();
		tMixInfoList.m_bStart = (BOOL32)bState;

		for ( u16 i = 0; i < m_vctAudmix.size(); i++ )
		{ 
			tMixInfoList.m_atAuxMixList.m_awList[i] = m_vctAudmix.at(i).wCnsID;
		}		

		u16 wRe =  ComInterface->UpdateAudMixList( tMixInfoList );
		if ( wRe != NO_ERROR )
		{
			ShowPopMsg(_T("会议讨论控制失败"));
			return false;
		}
	}

	PrtMsg( "\n[CAudMixLogic::UpdateAudMixLst]:end \n");
	return true;
}

BOOL CAudMixLogic::IsInAudMixList( u16 wCnsId )
{
	for ( s32 i = 0; i < m_vctAudmix.size(); i++ )
	{
		if ( m_vctAudmix[i].wCnsID == wCnsId )
		{
			return TRUE;
		}
	}
	return FALSE;
}

bool CAudMixLogic::OnRefreshCnsList( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TCMSConf tConfInfo ;
	bool bInConf = ComInterface->IsInConf( &tConfInfo );
	if (!bInConf)
	{
		return false;
	}
	m_vctCurrentCnsList.clear();
	for (int i = 0; i < tConfInfo.m_vctCnsList.size(); i++)
	{
		TCnsInfo tCnsInfo = tConfInfo.m_vctCnsList.at(i);
		if ( tCnsInfo.m_emEpType == emTPEndpointTypeUMS || tCnsInfo.m_emEpType == emTPEndpointH323MCU )
		{            
			continue;
		}

		if (tCnsInfo.m_bOnline)//只显示在线
		{
			m_vctCurrentCnsList.push_back(tConfInfo.m_vctCnsList.at(i));
		}	
	}

	if (m_bIsSearch)
	{
		m_bIsSearch = false;
		m_vctSearchCnsList.clear();
		ICncCommonOp::SetControlText(_T(""), m_pm,  _T("EdtConfSearch"));
	}

	UpdateCnsList(); 
	RefreshAudMixList(wParam,lParam,bHandle);
	return NO_ERROR;
}

bool CAudMixLogic::OnBtnSelRoomOK(TNotifyUI& msg )
{
	if (m_vctSelConf.size() == 0)
	{
		if (m_bIsChangeConf)
		{
			ShowMessageBox(_T("请选择替换的会场"));
		}
		else
		{
			ShowMessageBox(_T("请选择添加的会场"));
		}
		
		return false;
	}

	if (m_bIsChangeConf && m_vctSelConf.size() > 1)
	{
		ShowMessageBox(_T("替换的会场不能多选"));
		return false;
	}

	if ( m_bIsChangeConf && IsInAudMixList(m_vctSelConf.at(0).m_wEpID) )//要替换的会场不在讨论列表中 才进行替换 xcr确认
	{
		ShowMessageBox(_T("要替换的会场已在列表中，请重新选择"));
		return false;
	}

	bool bState = false;
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckStartDicsuss"));
	if ( !pCheckBox )
	{
		return false;
	}
	if ( pCheckBox->GetCheck() )
	{
		bState = true;
	}

	if (m_bIsChangeConf)//替换
	{
		TAudMixCtrls tAudMixCtrls;
		CString strName(m_vctSelConf.at(0).m_achRoomName);
		tAudMixCtrls.strConfName = strName;
		tAudMixCtrls.wCnsID = m_vctSelConf.at(0).m_wEpID;
		tAudMixCtrls.bIsSpeaker = m_vctSelConf.at(0).m_bIsSpeaker;
		tAudMixCtrls.wSpeakerNum = m_vctSelConf.at(0).m_wSpeakerNum;

		m_vctAudmix.at(m_dwChangeItemIndex) = tAudMixCtrls;

		UpdateAudMixLst();//不管开没开 都发此消息 列表发替换后列表 gy确认 2016-8-8

		m_bIsChangeConf = false;
		m_dwChangeItemIndex = -1;
	}
	else//添加
	{
		int nSpeakerCount = m_nSpeakerCount;
		if ( bState )
		{
			TDiscussListOpr tListOpr;
			tListOpr.m_emOprType = em_DisListOpr_Add;

			int nNum = 0;
			for ( int i = 0; i< m_vctSelConf.size(); i++ )
			{
				if (IsInAudMixList(m_vctSelConf.at(i).m_wEpID))
				{
					continue;
				}
				nSpeakerCount = nSpeakerCount + m_vctSelConf.at(i).m_wSpeakerNum;
				tListOpr.m_awEpId[nNum] = m_vctSelConf.at(i).m_wEpID;
				nNum ++;
			}

			if (nNum != 0)//列表有变化才发
			{
				tListOpr.m_wNum = nNum;

				TCMSConf tConfInfo;
				BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
				if (!bInConf)
				{
					return false;
				}
				tListOpr.m_wConfId = tConfInfo.m_wConfID;

				OprAudMixCtrl( tListOpr );
			}

		} 
		else
		{
			for (int i = 0; i<m_vctSelConf.size();i++)
			{
				if (IsInAudMixList(m_vctSelConf.at(i).m_wEpID))
				{
					continue;
				}

				nSpeakerCount = nSpeakerCount + m_vctSelConf.at(i).m_wSpeakerNum;

				TAudMixCtrls tAudMixCtrls;
				CString strName(m_vctSelConf.at(i).m_achRoomName);
				tAudMixCtrls.strConfName = strName;
				tAudMixCtrls.wCnsID = m_vctSelConf.at(i).m_wEpID;
				tAudMixCtrls.bIsSpeaker = m_vctSelConf.at(i).m_bIsSpeaker;
				tAudMixCtrls.wSpeakerNum = m_vctSelConf.at(i).m_wSpeakerNum;
                tAudMixCtrls.m_emEpType = m_vctSelConf.at(i).m_emEpType;
				m_vctAudmix.push_back(tAudMixCtrls);//收到ind再更新
			}
			if (nSpeakerCount != m_nSpeakerCount)//一样说明未添加就不更新
			{
				UpdateAudMixLst();
			}
		}

		if (nSpeakerCount > 27)//提示 但是要添加到列表中发给UMS 不然没有重复的会议将不被添加 2015-8-24 dyy
		{
			ShowMessageBox(_T("超过27个屏的部分，将不会添加到会议讨论"));
		}
	}

	ICncCommonOp::ShowControl( false, m_pm, _T("PageDiscSelConfList") );
	m_bIsSelAll = false;
	ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnSelAll"));
	m_vctSelConf.clear();

	return true;
}

void CAudMixLogic::OprAudMixCtrl( TDiscussListOpr tListOpr )
{
	TCMSConf tConf;
	BOOL32 bInConf = ComInterface->IsInConf( &tConf );	
	if ( bInConf )
	{
		u16 wRe = ComInterface->AudMixDisListOpr( tListOpr );

		if ( wRe != NO_ERROR )
		{
			ShowPopMsg(_T("设置会议讨论失败"));
			return;
		}
	}
}

bool CAudMixLogic::RefreshAudMixList( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_bIsDel = false;

	TCMSConf tConfInfo;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
	if ( ! bInConf )
	{
	    return NO_ERROR;
	}

	bool bStart = (bool)tConfInfo.IsVacOn();
	CCheckBoxUI* pCheck = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckAudioExcitation"));
	if ( !pCheck )
	{
		return false;
	}

	if ( pCheck->GetCheck() != bStart )
	{
		pCheck->SetCheckNoMsg(bStart);
	}

	//更新控件
	bStart = (bool)tConfInfo.IsStartAudMix();

	bool bState = false;
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckStartDicsuss"));
	if ( !pCheckBox )
	{
		return false;
	}
	if ( pCheckBox->GetCheck() )
	{
		bState = TRUE;
	}
	if ( bState != bStart )
	{
		pCheckBox->SetCheckNoMsg(bStart);
	}
	ICncCommonOp::EnableControl((bool)bStart,m_pm,_T("CheckAudioExcitation"));

	m_vctAudmix.clear();
	for ( int i = 0; i< TP_CONF_MAX_AUDMIXNUM; i++ )
	{ 
		int wCnsID = tConfInfo.m_tAudmixList.m_awList[i];
		if ( wCnsID == TP_INVALID_INDEX )
		{   
			continue;
		}
		else 
		{  
			TAudMixCtrls tAudMixCtrls;

			TCnsInfo* tCnsInfo = tConfInfo.GetCnsInfoByID( wCnsID );
			if ( tCnsInfo != NULL )
			{
				CString strName(tCnsInfo->m_achRoomName);
				tAudMixCtrls.strConfName = strName;
				tAudMixCtrls.wSpeakerNum = tCnsInfo->m_wSpeakerNum;
				if (tConfInfo.m_wSpeaker == tCnsInfo->m_wEpID)
				{
					tAudMixCtrls.bIsSpeaker = true;
				}
                tAudMixCtrls.m_emEpType = tCnsInfo->m_emEpType;
				//tAudMixCtrls.bIsSpeaker = tCnsInfo->m_bIsSpeaker;//lst若不更新 此项直接取有误
			}

			tAudMixCtrls.wCnsID = wCnsID;
			m_vctAudmix.push_back(tAudMixCtrls);
		} 
	}

	UpdateList();
	return NO_ERROR;
}

bool CAudMixLogic::OnCheckAudioExc( TNotifyUI& msg )
{
	TCMSConf tConfInfo;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
	if ( ! bInConf )
	{
		return NO_ERROR;
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

	if (bIsSet == (bool)tConfInfo.IsVacOn())
	{
		return true;
	}

	//开讨论的消息可以控制开或者关激励 关会议讨论的消息对于语音激励是没用的  单独控制激励的 是一直有用的
	if ( bInConf )
	{
		u16 wConfID = tConfInfo.m_wConfID;

		TConfAuxMixVacOpr tConfAuxMixVacOpr;
		tConfAuxMixVacOpr.m_wConfID = wConfID;
		tConfAuxMixVacOpr.m_bVacOn = bIsSet;

		u16 wRe =  ComInterface->AuxMixVacOpr( tConfAuxMixVacOpr );
		if ( wRe != NO_ERROR )
		{
			ShowPopMsg(_T("语音激励设置失败"));
			pCheckBox->SetCheckNoMsg(false);
		}
	}

	return true;
}

bool CAudMixLogic::OnBtnListLeft( TNotifyUI& msg )
{
	UpdateShowSliderList(true);
	return true;
}

bool CAudMixLogic::OnBtnListRight( TNotifyUI& msg )
{
	UpdateShowSliderList(false);
	return true;
}

void CAudMixLogic::UpdateShowSliderList( bool bLeft )
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, _T("ConfDiscussSlidetab") );
	if (!pControl)
	{
		return;
	}

	CTouchListUI *pTouchList = (CTouchListUI*)pControl->GetItemAt(m_wCurPageIndex);
	if (pTouchList)
	{
		int dwCurSel = pTouchList->GetCurSel();
		int nIndexNo = m_wCurPageIndex*6 + dwCurSel; //从第0页算起的索引号

		//上次点击的不是"+"号则恢复
		if (dwCurSel != -1 && (nIndexNo < m_vctAudmix.size()))
		{
			m_pm->DoCase( _T("caseDiscListNormal"), pTouchList->GetItemAt(dwCurSel) );
		}
		
		m_dwSelItemId = -1;
		pTouchList->SelectItem(-1);
	}

	if (!bLeft)
	{
		m_wCurPageIndex ++;
	}
	else
	{
		m_wCurPageIndex --;
	}

	pControl->SelectItem(m_wCurPageIndex);
	if (m_wCurPageIndex == 0)
	{
		ICncCommonOp::EnableControl(false,m_pm,_T("btnListLeft"));
	}
	else
	{
		ICncCommonOp::EnableControl(true,m_pm,_T("btnListLeft"));
	}
	if ( (m_wCurPageIndex+1)*6 > m_vctAudmix.size())
	{
		ICncCommonOp::EnableControl(false,m_pm,_T("btnListRight"));
	}
	else
	{
		ICncCommonOp::EnableControl(true,m_pm,_T("btnListRight"));
	}
}

bool CAudMixLogic::OnDiscussItemClick( TNotifyUI& msg )
{
	TCMSConf tConfInfo;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
	if (!bInConf)
	{
		return false;
	}

	if ( m_vctAudmix.empty() || tConfInfo.m_tAudmixList.m_awList[0] == TP_INVALID_INDEX )
	{
		return true;
	}

	if ( const CTouchListUI *pList = dynamic_cast<const CTouchListUI*>(msg.pSender) )
	{
		int nIndex = m_wCurPageIndex*6 + msg.wParam/*pItem->GetIndex()*/; 
		if (nIndex >= m_vctAudmix.size())
		{
			m_dwSelItemId = -1;
			if (m_wCurPageIndex*6 + msg.lParam < m_vctAudmix.size() && msg.lParam != -1)
			{
				m_pm->DoCase( _T("caseDiscListNormal"),pList->GetItemAt(msg.lParam) );
			}
			return true;
		}
		if ( m_dwSelItemId == -1 )
		{
			m_pm->DoCase( _T("caseDiscListSel"), pList->GetItemAt(msg.wParam));    
			m_dwSelItemId = nIndex;
		}
		else
		{
			if ( m_dwSelItemId == nIndex )
			{
				m_pm->DoCase( _T("caseDiscListNormal"), pList->GetItemAt(msg.wParam) );
				m_dwSelItemId = -1;
			}
			else
			{
				CTouchListUI* pDicList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("DicListItem"));
				CControlUI *pLastSel = pDicList->GetItemAt(m_dwSelItemId);
				m_pm->DoCase( _T("caseDiscListNormal"),pList->GetItemAt(msg.lParam) );
				m_pm->DoCase( _T("caseDiscListSel"),pList->GetItemAt(msg.wParam)/*, dynamic_cast<CControlUI*>(pItem)*//*msg.pSender*/ );
				m_dwSelItemId = nIndex;
			}
		}
	}
	return true;
}

bool CAudMixLogic::OnBtnAddConf( TNotifyUI& msg )
{
	UpdateCnsList();
	m_bIsChangeConf = false;
	m_bIsSearch = false;
	ICncCommonOp::SetControlText(_T(""), m_pm, _T("EdtConfSearch"));
	m_vctSearchCnsList.clear();

	ICncCommonOp::ShowControl( true, m_pm, _T("PageDiscSelConfList") );
	return true;
}

bool CAudMixLogic::OnBtnChangeConf(TNotifyUI& msg)
{
	UpdateCnsList();
	CListContainerElementUI* pItem = (CListContainerElementUI*)msg.pSender->GetParent()->GetParent()->GetParent();
	if (pItem)
	{
		m_dwChangeItemIndex = pItem->GetIndex();
	}
	m_bIsChangeConf = true;
	ICncCommonOp::ShowControl( true, m_pm, _T("PageDiscSelConfList") );
	return true;
}

bool CAudMixLogic::OnBtnSelCancel( TNotifyUI& msg )
{
	ICncCommonOp::ShowControl( false, m_pm, _T("PageDiscSelConfList") );
	m_bIsSelAll = false;
	ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnSelAll"));
	m_vctSelConf.clear();
	return true;
}

bool CAudMixLogic::OnSelConfItemClick( TNotifyUI& msg )
{
	return true;
}

bool CAudMixLogic::OnCheckConfItem( TNotifyUI& msg )
{
	if (msg.pSender->GetParent()->GetParent()->GetName() != _T("OnlinCnsConfList"))  
	{
		return false;
	}

	CControlUI *pParent = msg.pSender->GetParent();
	if ( CListContainerElementUI *pItem = dynamic_cast<CListContainerElementUI*>(pParent) )
	{
		TCnsInfo tCnsInfo = *(TCnsInfo*)pItem->GetTag();
		CCheckBoxUI *pCheckBox = (CCheckBoxUI*)msg.pSender;
		bool bCheck = pCheckBox->GetCheck();

		if ( bCheck )
		{
			if (CTouchListUI *pTouchlist = dynamic_cast<CTouchListUI*>(msg.pSender->GetParent()->GetParent()))
			{
				pTouchlist->SelectItem(-1);
			}

			pItem->SetBkImage( _T("res\\list\\item_sel.png") );

			m_vctSelConf.push_back( tCnsInfo );
		}
		else
		{
			pItem->SetBkImage( _T("res\\list\\item_normal.png") );

			vector<TCnsInfo>::iterator iter = m_vctSelConf.begin();
			while( iter != m_vctSelConf.end() )
			{					  
				if ( *iter == tCnsInfo )
				{
					m_vctSelConf.erase(iter);
					break;
				}		
				iter++;
			}
		}	
	}

	CString str(ICncCommonOp::GetControlText(m_pm,_T("BtnSelAll")).c_str());
	if (m_bIsSearch)
	{
		if (m_vctSelConf.size() == m_vctSearchCnsList.size() && str != _T("取消全选"))
		{
			m_bIsSelAll = true;
			ICncCommonOp::SetControlText(_T("取消全选"),m_pm,_T("BtnSelAll"));
		}
		if (m_vctSelConf.size() != m_vctSearchCnsList.size() && str != _T("全 选"))
		{
			m_bIsSelAll = false;
			ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnSelAll"));
		}
	}
	else
	{
		if (m_vctSelConf.size() == m_vctCurrentCnsList.size() && str != _T("取消全选"))
		{
			m_bIsSelAll = true;
			ICncCommonOp::SetControlText(_T("取消全选"),m_pm,_T("BtnSelAll"));
		}
		if (m_vctSelConf.size() != m_vctCurrentCnsList.size() && str != _T("全 选"))
		{
			m_bIsSelAll = false;
			ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnSelAll"));
		}
	}

	return true;
}

bool CAudMixLogic::OnBtnSelAll( TNotifyUI& msg )
{
	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("OnlinCnsConfList") );
	if ( pTileLayoutUI == NULL )
	{
		return false;
	}
	m_bIsSelAll = !m_bIsSelAll;
	if ( m_bIsSelAll )
	{
		ICncCommonOp::SetControlText(_T("取消全选"),m_pm,_T("BtnSelAll"));
		for ( int i = 0; i <  pTileLayoutUI->GetCount(); i++ )
		{		
			CListContainerElementUI *pListContainer = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(i);
			CCheckBoxUI* pCheckBoxItemSel = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("BtnConfCnsSel"), pListContainer);

			if ( pCheckBoxItemSel && !pCheckBoxItemSel->GetCheck())
			{
				pCheckBoxItemSel->SetCheck(true);
			}
		}
	}
	else
	{
		ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnSelAll"));
		for ( int i = 0; i <  pTileLayoutUI->GetCount(); i++ )
		{		
			CListContainerElementUI *pListContainer = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(i);
			CCheckBoxUI* pCheckBoxItemSel = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("BtnConfCnsSel"), pListContainer);

			if ( pCheckBoxItemSel )
			{
				pCheckBoxItemSel->SetCheck(false);
			}

		}
	}

	return true;
}

bool CAudMixLogic::OnBtnSpeaker( TNotifyUI& msg )
{
	bool bIsSpeaker = false;

	if (CTouchListUI *pTouchList = dynamic_cast<CTouchListUI*>(msg.pSender->GetParent()->GetParent()->GetParent()->GetParent()) )
	{
		int dwId = pTouchList->GetCurSel();
		if (m_vctAudmix.at( m_wCurPageIndex * 6 + dwId).bIsSpeaker == true)
		{
			bIsSpeaker = true;
		}
		
	}

	if (!bIsSpeaker)//不是发言人进行此操作
	{
		TCMSConf tCMSConf;
		BOOL32 bInConf =  ComInterface->IsInConf( &tCMSConf );
		if (!bInConf)
		{
			return false;
		}

		TConfEpID  tConfEpInfo ;
		tConfEpInfo.m_wConfID = tCMSConf.m_wConfID;
		tConfEpInfo.m_wEpID = msg.pSender->GetTag() ;
		u16 wRe = ComInterface->SetSpokeCns( tConfEpInfo );
	}

	return true;
}

bool CAudMixLogic::OnBtnDelDisc( TNotifyUI& msg )
{
	if (m_bIsDel)
	{
		return true;
	}
	m_bIsDel = true;

	int dwConfID = msg.pSender->GetTag();
	int dwItemID;
	if (CTouchListUI *pTouchList = dynamic_cast<CTouchListUI*>(msg.pSender->GetParent()->GetParent()->GetParent()->GetParent()))
	{
		dwItemID = pTouchList->GetCurSel() + m_wCurPageIndex*6;
	}
	bool bState = false ;
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckStartDicsuss"));
	if ( !pCheckBox )
	{
		return false;
	}
	if ( pCheckBox->GetCheck() )
	{
		bState = true;
	}

	if ( dwConfID != TP_INVALID_INDEX )
	{		
		if ( bState )
		{
			TDiscussListOpr tListOpr;
			tListOpr.m_wNum = 1;
			tListOpr.m_emOprType = em_DisListOpr_Del;
			tListOpr.m_awEpId[0] = dwConfID;

			TCMSConf tConfInfo;
			BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
			if (!bInConf)
			{
				return false;
			}
			tListOpr.m_wConfId = tConfInfo.m_wConfID;

			OprAudMixCtrl( tListOpr );
		} 
		else
		{
			//m_vctAudmix[dwItemID].wCnsID = TP_INVALID_INDEX;
			if (m_vctAudmix.size() == 0)
			{
				return false;
			}
			if (m_vctAudmix.size() > dwItemID)
			{
				vector<TAudMixCtrls>::const_iterator iter = m_vctAudmix.begin(); //收到ind再更新
				m_vctAudmix.erase(iter+dwItemID);
			}
			UpdateAudMixLst();
		}
	}

	return true;
}

//收到反馈消息后更新
bool CAudMixLogic::OnAudMixDisListOprInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TDiscussListOpr tDisListOpr = ComInterface->GetDiscussList();
	bool bIsError = false;
	for (int i=0; i<tDisListOpr.m_wNum; i++)
	{	
		if (tDisListOpr.m_aemRet[i] == em_Disucss_Opr_Successed)
		{
			TAudMixCtrls tAudMixCtrls;
			TCMSConf tConfInfo;
			BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
			if (!bInConf)
			{
				return false;
			}
			TCnsInfo* tCnsInfo = tConfInfo.GetCnsInfoByID( tDisListOpr.m_awEpId[i] );
			if ( tCnsInfo != NULL )
			{
				CString strName(tCnsInfo->m_achRoomName);
				tAudMixCtrls.strConfName = strName;
			}
			else
			{
				return false;
			}

			tAudMixCtrls.wCnsID = tDisListOpr.m_awEpId[i];
			tAudMixCtrls.wSpeakerNum = tCnsInfo->m_wSpeakerNum;
			if (tConfInfo.m_wSpeaker == tCnsInfo->m_wEpID)
			{
				tAudMixCtrls.bIsSpeaker = true;
			}
            tAudMixCtrls.m_emEpType = tCnsInfo->m_emEpType;
			//tAudMixCtrls.bIsSpeaker = tCnsInfo->m_bIsSpeaker;

			if (tDisListOpr.m_emOprType == em_DisListOpr_Add)
			{
				m_vctAudmix.push_back(tAudMixCtrls);
			}
			else
			{
				int nCount = m_vctAudmix.size();
				for (int j=0;j<nCount;j++)
				{
					if (m_vctAudmix.at(j).wCnsID == tAudMixCtrls.wCnsID)
					{
						m_vctAudmix.erase(m_vctAudmix.begin() + j);
						break;
					}
				}
				
			}
		}
		else
		{
			if (bIsError)//只提示一次
			{
				continue;
			}

			bIsError = true;
			if (tDisListOpr.m_emOprType == em_DisListOpr_Del)
			{
				if (tDisListOpr.m_aemRet[i] == em_Discuss_OtherFail)
				{
					ShowPopMsg(_T("删除会议讨论失败"));
				}
			}
			else
			{
				switch(tDisListOpr.m_aemRet[i])
				{
				case em_Discuss_Invalid_Ep:
					{
						ShowPopMsg(_T("添加会议讨论失败：会场无效"));
					}
					break;
				case em_Discuss_Screen_Full:
					{
						ShowPopMsg(_T("添加会议讨论失败：屏数不足"));
					}
					break;
				case em_Disccuss_GetVid_Error:
					{
						ShowPopMsg(_T("添加会议讨论失败：调码流出错"));
					}
					break;
				case em_Discuss_No_BandWith:
					{
						ShowPopMsg(_T("添加会议讨论失败：级联间宽带不足"));
					}
					break;
				case em_Discuss_AssignAudChan_Error:
					{
						ShowPopMsg(_T("添加会议讨论失败：给下级会场分配下传音频通道失败"));
					}
					break;
				case em_Discuss_No_MixChan:
					{
						ShowPopMsg(_T("添加会议讨论失败：会议讨论通道不足"));
					}
                    break;
				default:
					{
						ShowPopMsg(_T("添加会议讨论失败"));
					}
					break;
				}
			}
		}
	}

	UpdateList();

	return true;
}

bool CAudMixLogic::OnAudMixVacOprInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	u16 OprReslt = (u16)lParam; 
	if (OprReslt == TP_RET_ERROR)
	{
		TCMSConf tConfInfo;
		BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
		if (!bInConf)
		{
			return false;
		}
		if ((tConfInfo.m_emConfType != emCallType_P2P && bInConf) && m_bIsFirstLogin)//多点会议 登录时的第一次收到时不提示 nlf确认 2015-7-8
		{
			m_bIsFirstLogin = false;
			return false;
		}
		else
		{
			ShowPopMsg(_T("语音激励设置失败")); 			
		}

		CCheckBoxUI* pCheckVac = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckAudioExcitation"));
		if ( pCheckVac )
		{
			bool bSet = pCheckVac->GetCheck();
			pCheckVac->SetCheckNoMsg(!bSet);
		}
	}

	return true;
}

bool CAudMixLogic::OnSearchEditChange( TNotifyUI& msg )
{
	CEditUI* pEditSearch = (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("EdtConfSearch") );
	if ( !pEditSearch )
	{
		return false;
	}

	m_vctSearchCnsList.clear();
	CString strSearch = pEditSearch->GetText();
	if ( strSearch.IsEmpty() )
	{
		m_bIsSearch = false;
		UpdateCnsList();
	}
	else
	{
		m_bIsSearch = true;
		m_bIsSelAll = false;
		m_vctSelConf.clear();
		ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnSelAll"));
		CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("OnlinCnsConfList") );
		if ( pTileLayoutUI == NULL )
		{
			return false;
		}

		pTileLayoutUI->RemoveAll();

		for ( u32 i = 0; i < m_vctCurrentCnsList.size(); i++ )
		{
			CString strConfName;
			strConfName.Format( _T("%s"),CA2T( m_vctCurrentCnsList.at(i).m_achRoomName));
			BOOL bFind = FALSE;			
			bFind = UIDATAMGR->HZPYMatchList( strSearch, strConfName );
			if ( bFind )
			{
				m_vctSearchCnsList.push_back(m_vctCurrentCnsList.at(i));

				CListContainerElementUI *pListContainer = 
					(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("ConfCnsListItem") );

				ICncCommonOp::SetControlText( strConfName, m_pm, _T("ConfCnsName"), pListContainer );
				if (m_vctCurrentCnsList.at(i).m_emEpType == emTPEndpointH323G400)
				{
					m_pm->DoCase( _T("caseMonitor"), pListContainer ); 
				}
				else if (m_vctCurrentCnsList.at(i).m_emEpType == emTPEndpointTypeVRS)
				{
					m_pm->DoCase( _T("caseStudio"), pListContainer ); 
				}
				else if (m_vctCurrentCnsList.at(i).m_emEpType != emTPEndpointTypeCNS)
				{
					m_pm->DoCase( _T("caseOrdinary"), pListContainer ); 
				}

				pListContainer->SetTag( (UINT_PTR)&m_vctCurrentCnsList.at(i) );

				pTileLayoutUI->Add(pListContainer);

			}
		}
	}
	return false;
}

bool CAudMixLogic::OnComboAddrShowEx( TNotifyUI& msg )
{
	switch((EmCncListState)msg.wParam)
	{
// 	case emCncListState_all:
// 		{
// 			TCMSConf tConfInfo;
// 			BOOL32 re = ComInterface->IsInConf( &tConfInfo );
// 			m_vctCurrentCnsList.clear();
// 			m_vctCurrentCnsList = tConfInfo.m_tplCnsList; 
// 		}
// 		break;
// 	case emCncListState_group:
// 		{
// 			TCMSConf tConfInfo;
// 			BOOL32 re = ComInterface->IsInConf( &tConfInfo );
// 			m_vctCurrentCnsList.clear();
// 			m_vctCurrentCnsList = tConfInfo.m_tplCnsList; 
// 		}
// 		break;
// 	case emCncListState_inline:
// 		{
// 			TCMSConf tConfInfo;
// 			BOOL32 re = ComInterface->IsInConf( &tConfInfo );
// 			m_vctCurrentCnsList.clear();
// 			m_vctCurrentCnsList = tConfInfo.m_tplCnsList; 
// 		}
// 		break;
// 	case emCncListState_outline:
// 		{
// 			TCMSConf tConfInfo;
// 			BOOL32 re = ComInterface->IsInConf( &tConfInfo );
// 			m_vctCurrentCnsList.clear();
// 			m_vctCurrentCnsList = tConfInfo.m_tplCnsList; 
// 		}
// 		break;

	}

	//UpdateCnsList();
	return true;
}

bool CAudMixLogic::OnDiscussListItem( TNotifyUI& msg )
{
	TCMSConf tConfInfo;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
	if (!bInConf)
	{
		return false;
	}
	if ( m_vctAudmix.empty() || tConfInfo.m_tAudmixList.m_awList[0] == TP_INVALID_INDEX)
	{
		return true;
	}

	CListContainerElementUI* pItem = (CListContainerElementUI*)msg.pSender;
	CTouchListUI *pList = (CTouchListUI*)msg.pSender->GetParent();
	if ( pItem && pList)
	{
		int nIndex = pItem->GetIndex(); //当前页索引号
		int nIndexNo = m_wCurPageIndex*6 + nIndex; //从第0页算起的索引号
		
		//点击了“+”号
		if (nIndexNo >= m_vctAudmix.size())
		{
			//上次已经点过则恢复
			if ((m_wCurPageIndex*6 + m_dwSelItemId < m_vctAudmix.size()) && m_dwSelItemId != -1)
			{
				m_pm->DoCase( _T("caseDiscListNormal"),pList->GetItemAt(m_dwSelItemId) );
			}
			m_dwSelItemId = -1;
			return true;
		}
		if ( m_dwSelItemId == -1 )
		{
			m_pm->DoCase( _T("caseDiscListSel"), pItem);    
			m_dwSelItemId = nIndex;
		}
		else
		{
			if ( m_dwSelItemId == nIndex )
			{
				m_pm->DoCase( _T("caseDiscListNormal"), pItem );
				m_dwSelItemId = -1;
			}
			else
			{
				m_pm->DoCase( _T("caseDiscListNormal"),pList->GetItemAt(m_dwSelItemId) );
				m_pm->DoCase( _T("caseDiscListSel"),pItem );
				m_dwSelItemId = nIndex;
			}
		}
	}

	return true;
}

bool CAudMixLogic::OnStartAudMixInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_bIsDel = false;

	EmDiscussRspRet emRet = (EmDiscussRspRet)wParam;
	CString strErr = _T("");
	switch ( emRet )
	{
	case  em_Start_AssginVmpFail:
		strErr = _T("合成资源不足，开启讨论失败");
		break;
	case  em_Start_AssignMixFail:
		strErr = _T("混音资源不足，开启讨论失败");
		break;
	case em_Start_AssignBasFail:
		strErr = _T("适配资源不足，开启讨论失败");
		break; 
	case em_Start_OtherFail:
		strErr = _T("开启讨论失败");
		break;
	case em_Start_RollCall_Mode:
		strErr = _T("当前为会议点名模式，开启讨论失败");
		break;
	case em_Start_ConfAudMix_Mode:
		strErr = _T("当前为会议混音模式，开启讨论失败");
		break;
	}
	ShowPopMsg(strErr);

	return true;
}

bool CAudMixLogic::OnSpeakerNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	if (m_vctAudmix.size() == 0)
	{
		return false;
	}

	u16	wEpID = (u16)lParam;

	int nOriSpeakerID = -1;
	int nCurSpeakerID = -1;
	for (int i = 0; i<m_vctAudmix.size(); i++)
	{
		if (m_vctAudmix.at(i).bIsSpeaker)
		{
			nOriSpeakerID = i;
		}
		if (m_vctAudmix.at(i).wCnsID == wEpID)
		{
			nCurSpeakerID = i;
		}
	}
	
	CSlideTabLayoutUI *pSlideTabLayout = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, _T("ConfDiscussSlidetab") );
	if (!pSlideTabLayout)
	{
		return false;
	}

	if (nCurSpeakerID != nOriSpeakerID)
	{
		if (nOriSpeakerID < m_vctAudmix.size() && nOriSpeakerID != -1)
		{
			m_vctAudmix.at(nOriSpeakerID).bIsSpeaker = false;
		}

		if ( nCurSpeakerID < m_vctAudmix.size() && nCurSpeakerID != -1)
		{
			m_vctAudmix.at(nCurSpeakerID).bIsSpeaker = true;
		}

		int nPageId = nOriSpeakerID/6;

		CTouchListUI *pTouchListLayoutUI = (CTouchListUI*)pSlideTabLayout->GetItemAt(nPageId);
		if (pTouchListLayoutUI)
		{
			CListContainerElementUI *pListContainer = (CListContainerElementUI*)pTouchListLayoutUI->GetItemAt(nOriSpeakerID%6);
			if (pListContainer)
			{
				CButtonUI* pBtnSpeaker = (CButtonUI*)ICncCommonOp::FindControl( m_pm, _T("btnSpeaker"), pListContainer);
				if (pBtnSpeaker)
				{
					pBtnSpeaker->SetAttribute(_T("focusedimage"),_T("res/confctrl/confdiscuss/appoint_select.png"));
					pBtnSpeaker->SetAttribute(_T("pushedimage"),_T("res/confctrl/confdiscuss/appoint_select.png"));
					pBtnSpeaker->SetAttribute(_T("normalimage"),_T("res/confctrl/confdiscuss/appoint_normal.png"));		
				}
			}
		}
	}

	int nPageId = nCurSpeakerID/6;

	CTouchListUI *pTouchList = (CTouchListUI*)pSlideTabLayout->GetItemAt(nPageId);
	if (pTouchList)
	{
		CListContainerElementUI *pListContainer = (CListContainerElementUI*)pTouchList->GetItemAt(nCurSpeakerID%6);
		if (pListContainer)
		{
			CButtonUI* pBtnSpeaker = (CButtonUI*)ICncCommonOp::FindControl( m_pm, _T("btnSpeaker"), pListContainer);
			if (pBtnSpeaker)
			{
				pBtnSpeaker->SetAttribute(_T("focusedimage"),_T("res/confctrl/confdiscuss/cancel_select.png"));
				pBtnSpeaker->SetAttribute(_T("pushedimage"),_T("res/confctrl/confdiscuss/cancel_select.png"));
				pBtnSpeaker->SetAttribute(_T("normalimage"),_T("res/confctrl/confdiscuss/cancel_normal.png"));		
			}
		}
	}

	return true;
}

bool CAudMixLogic::OnSpeakerInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	u16	wEpID = (u16)wParam;
	EmTpApplySpeakerRet emRe = (EmTpApplySpeakerRet)lParam;
	//会场列表里面的消息回复时候 均在此处提示
	if (emRe != TP_ApplySpeaker_Success)
	{
		CString strError = _T("发言人设置失败");
		if (emRe == TP_ApplySpeaker_EpStateError)//ums不能加枚举 影响协议 cnc判断点名时自己添加提示信息
		{
			TTpConfRollCallInfo tTpConfRollCallInfo;//点名状态信息
			ComInterface->GetRollState( tTpConfRollCallInfo );
			if (tTpConfRollCallInfo.m_bStart)//如果点名开启了
			{
				strError = strError + _T("：模式错误，点名模式，发言人不能切换成功");
			}
		}

		ShowPopMsg(strError);
		return true;
	}

	return true;
}

bool CAudMixLogic::OnConnectRsp( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_bIsFirstLogin = true;
	return true;
}
