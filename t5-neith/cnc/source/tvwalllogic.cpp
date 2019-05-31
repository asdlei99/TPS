#include "StdAfx.h"
#include "tvwalllogic.h"
#include "confmsglogic.h"

template<> CTvWallLogic* Singleton<CTvWallLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CTvWallLogic, CNotifyUIImpl)

	MSG_CLICK(_T("BtnTvWallSet"), OnBtnSetTvWall)
	MSG_CLICK(_T("BtnMuteView"), OnBtnOpenMuteView)
	MSG_CLICK(_T("BtnCancelMuteView"), OnBtnCloseMuteView)

	MSG_CLICK(_T("BtnDelete"), OnBtnStopPlay)
	MSG_CLICK(_T("BtnDelView1"), OnBtnStopPlay)
	MSG_CLICK(_T("BtnDelView2"), OnBtnStopPlay)
	MSG_CLICK(_T("BtnDelView3"), OnBtnStopPlay)
	MSG_CLICK(_T("BtnDelView4"), OnBtnStopPlay)

	MSG_CLICK(_T("BtnAdd1"), OnBtnAddTvWall)
	MSG_CLICK(_T("BtnAdd2"), OnBtnAddTvWall)
	MSG_CLICK(_T("BtnAdd3"), OnBtnAddTvWall)
	MSG_CLICK(_T("BtnAdd4"), OnBtnAddTvWall)
	MSG_CLICK(_T("BtnEnable"), OnBtnAddTvWall)
    MSG_ITEMCLICK(_T("TvWallCfgItem"), OnBtnTvWallItem)

	MSG_CLICK(_T("BtnSetVoice"), OnBtnSetVoice)
	MSG_CLICK(_T("BtnConfirm"), OnBtnConfirm)
	MSG_CLICK(_T("BtnCancel"), OnBtnCancel)

	MSG_CLICK(_T("BtnShowScreenOption"), OnBtnShowScreenOption)
	MSG_CLICK(_T("BtnHideScreenOption"), OnBtnHideScreenOption)

	MSG_SELECTCHANGE(_T("BtnRoomSel"), OnListBtnRoomSel)

//	MSG_ITEMSELECTD(_T("ConfList"), OnConfCnsItemClick)

	MSG_VALUECHANGED(_T("sldTvWallVol"),onHduVolChanged)
	MSG_VALUECHANGING(_T("sldTvWallVol"),onHduVolChanging)
	MSG_SELECTCHANGE(_T("CheckTvWallSlient"), OnCheckSlient)
	MSG_SELECTCHANGE(_T("CheckTvWallShot"), OnCheckTvWallShortCut)

	MSG_SELECTCHANGE(_T("CheckSrceen1"), OnCheckSrceen1)
	MSG_SELECTCHANGE(_T("CheckSrceen2"), OnCheckSrceen2)
	MSG_SELECTCHANGE(_T("CheckSrceen3"), OnCheckSrceen3)

	MSG_ITEMSELECTD(_T("ComboConfCtrlShowType"), OnComboShowEx)

	MSG_EDITCHANGE(_T("ConfListSearch"), OnSearchEditChange)	
	MSG_LETTERINDEX_CLICK(_T("ConfIndexletter"),OnLetterIndex)

	USER_MSG(UI_HDUPLAN_NTY,OnHduPlanNty)
	USER_MSG(UI_HDUSTOPPLAY_IND,OnHduStopPlayInd)
	USER_MSG(UI_HDUVOLUME_IND,OnHduVolumeInd)
	USER_MSG(UI_HDUCHANGEMODE_IND,OnHduChangeModeInd)
	USER_MSG(UI_CNC_HIDE_TVWALLCHILDDLG_NTY,OnHideChildWindowNty)
	USER_MSG(UI_UMS_REFRESH_CONFCNS_LIST,OnRefreshCnsList)
	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)
	USER_MSG(UI_CNS_CONFSTATE_NOTIFY,OnConfStateNty) 
	USER_MSG(UI_HDUPLAY_IND,onHduPlayInd)

APP_END_MSG_MAP()

CTvWallLogic::CTvWallLogic(void)
:m_strSetTvWallBtn(_T("BtnTvWallSet"))
,m_strMuteViewLayout(_T("MuteViewLayout"))
,m_strSrceenDesc(_T("LebDescribe"))
,m_strChannelDesc(_T("TxtDescribe"))
,m_strSetTvWallLayout(_T("SetTvWallLayout"))
,m_strBtnSetVoice(_T("BtnSetVoice"))
,m_strBtnMuteView(_T("BtnMuteView"))
,m_strBtnDelMuteView(_T("BtnDelMuteView"))
,m_emCnsShowState(emShowAll)
,m_nSelIndex(-1)
,m_strChannelAlias("")
{
	clear();
	m_strArrayScreen[0] = _T("(左)");
	m_strArrayScreen[1] = _T("(中)");
	m_strArrayScreen[2] = _T("(右)");
}

bool CTvWallLogic::init()
{
	CComboUI* pComboEx = (CComboUI*)ICncCommonOp::FindControl( m_pm, _T("ComboConfCtrlShowType") );
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
	}

	return true;
}

CTvWallLogic::~CTvWallLogic(void)
{
	clear();
}

bool CTvWallLogic::OnBtnSetTvWall( TNotifyUI& msg )
{
	/*CControlUI *pParent = msg.pSender->GetParent();
	CListContainerElementUI *pContainer= dynamic_cast<CListContainerElementUI*>(pParent);
	u8 bCfg = GetStatus(msg.pSender);
	CButtonUI* pBtnVolCtrl = (CButtonUI*)ICncCommonOp::FindControl( m_pm, m_strBtnSetVoice.c_str(), pContainer);

	TTpHduPlanUnit tHduPlanUnit = *(TTpHduPlanUnit*)pBtnVolCtrl->GetTag();

	if ( bCfg == 0 )
	{
		SetStatus(msg.pSender,1);
	}
	else
	{
		SetStatus(msg.pSender,0);
	}
	updateItem(pContainer,tHduPlanUnit);*/

    
    CControlUI *pParent = msg.pSender->GetParent();
    if ( CListContainerElementUI *pContainer= dynamic_cast<CListContainerElementUI*>(pParent) )
    {
        int nIndex = pContainer->GetIndex();

        CButtonUI* pBtnVolCtrl = (CButtonUI*)ICncCommonOp::FindControl( m_pm, m_strBtnSetVoice.c_str(), pContainer);
        TTpHduPlanUnit tHduPlanUnit = *(TTpHduPlanUnit*)pBtnVolCtrl->GetTag();

		//如果通道不在线或者不可用就返回
		if (!tHduPlanUnit.m_byValid || !tHduPlanUnit.m_byReged)
		{
			return false;
		}

        if ( m_nCtrlIndex == -1 )
        {
            SetStatus(msg.pSender, 1);
            m_nCtrlIndex = nIndex;   

            updateItem(pContainer,tHduPlanUnit);
        }
        else
        {
            if ( m_nCtrlIndex == nIndex )
            {
                SetStatus(msg.pSender, 0);
                m_nCtrlIndex = -1;

                updateItem(pContainer,tHduPlanUnit);
            }
            else
            {
                CTouchListUI* pTvWallList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("TvWallList") );
                CListContainerElementUI *pLastSel = (CListContainerElementUI*)pTvWallList->GetItemAt(m_nCtrlIndex);
                
                if ( pLastSel != NULL )
                {
                    CControlUI* pBtnSet = ICncCommonOp::FindControl( m_pm, m_strSetTvWallBtn.c_str(), pLastSel);

                    SetStatus(pBtnSet, 0);

                    CButtonUI* pBtnVolCtrl1 = (CButtonUI*)ICncCommonOp::FindControl( m_pm, m_strBtnSetVoice.c_str(), pLastSel);

                    TTpHduPlanUnit tHduPlanUnit1 = *(TTpHduPlanUnit*)pBtnVolCtrl1->GetTag();
                   
                    updateItem(pLastSel,tHduPlanUnit1);
                }             

                SetStatus(msg.pSender, 1);
                m_nCtrlIndex = nIndex;
                updateItem(pContainer,tHduPlanUnit);
            }
        }
    }

	return true;
}

bool CTvWallLogic::OnBtnOpenMuteView( TNotifyUI& msg )
{
	CControlUI *pParent = msg.pSender->GetParent();
	CListContainerElementUI *pContainer= dynamic_cast<CListContainerElementUI*>(pParent->GetParent());
	if ( pContainer == NULL  )
	{
		return false;
	}
	u8 byIndex = (u8)pContainer->GetTag();

	u16 wRe = ComInterface->ChangeChanModeReq(byIndex,1);
	return true;
}

bool CTvWallLogic::OnComboShowEx(TNotifyUI& msg)
{
	int nSel = msg.wParam;
	m_nSelIndex = -1;
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
	UpdateCnsList();
	UpdateShowList();
	return true;
}

void CTvWallLogic::UpdateShowList()
{
	CTouchListUI* pConfCnsList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("ConfList") );

	if ( pConfCnsList == NULL )
	{
		return;
	}

	if (m_vctCnsInfoList.size() == 0)
	{
		return;
	}

	pConfCnsList->RemoveAll();

	m_vctShowCnsList.clear();
	for ( u16 i = 0; i < m_vctCnsInfoList.size(); i++ )
	{
		m_vctShowCnsList.push_back(m_vctCnsInfoList.at(i));
		CListContainerElementUI *pListContainer = 
			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("ScreenSelWatchItem") );

		TSelViewInfo tCnsInfo = m_vctCnsInfoList.at(i); 
		ICncCommonOp::SetControlText( CA2T(tCnsInfo.m_achRoomName), m_pm, _T("AddrEntryName"), pListContainer );
		if ( m_vctCnsInfoList.at(i).m_emType == EmEpType_Eqp)
		{
			ICncCommonOp::SetControlBkImg(_T("res\\list\\imgVidMix.png"), m_pm, _T("imgAddrLabel"), pListContainer);
		}
		else if (m_vctCnsInfoList.at(i).m_emEpType ==  emTPEndpointH323G400)
		{
			ICncCommonOp::SetControlBkImg(_T("res\\list\\imgMonitor.png"), m_pm, _T("imgAddrLabel"), pListContainer);
		}
		else if (m_vctCnsInfoList.at(i).m_emEpType == emTPEndpointTypeVRS)
		{
			ICncCommonOp::SetControlBkImg(_T("res\\list\\imgStudio.png"), m_pm, _T("imgAddrLabel"), pListContainer);
		}
		else if (m_vctCnsInfoList.at(i).m_emEpType !=  emTPEndpointTypeCNS)
		{
			ICncCommonOp::SetControlBkImg(_T("res\\list\\imgOrdinary.png"), m_pm, _T("imgAddrLabel"), pListContainer);
		}

		//三屏会场显示屏幕
		if ((EmEpType_Ter == tCnsInfo.m_emType) && (3 == tCnsInfo.m_wSpeakerNum))
		{
			m_pm->DoCase(_T("caseHideScreenOption"), pListContainer);
		}
		else
		{
			ICncCommonOp::ShowControl(false, m_pm, _T("BtnScreenOption"), pListContainer);
		}

		//会场列表选择按钮checkbox
        ICncCommonOp::ShowControl(true, m_pm, _T("BtnRoomSel"), pListContainer);
// 		if (EmEpType_Ter == tCnsInfo.m_emType)
// 		{
// 			ICncCommonOp::ShowControl(true, m_pm, _T("BtnRoomSel"), pListContainer);
// 		}
// 		else
// 		{
// 			ICncCommonOp::ShowControl(false, m_pm, _T("BtnRoomSel"), pListContainer);
// 		}

		pListContainer->SetTag( (UINT_PTR)&m_vctCnsInfoList.at(i));
        pConfCnsList->Add(pListContainer);
		if (strcmp(m_strChannelAlias.c_str(), tCnsInfo.m_achRoomName) == 0)
		{
            pListContainer->SetInternVisible(true);
			pListContainer->Select();
		}
	}

}

bool CTvWallLogic::OnSearchEditChange(TNotifyUI& msg)
{
	CEditUI* pEditSearch = (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("ConfListSearch") );
	if ( !pEditSearch )
	{
		return false;
	}

	CString strSearch = pEditSearch->GetText();
	if ( strSearch.IsEmpty() )
	{
		m_vctShowCnsList.clear();
		UpdateCnsList();
		UpdateShowList();
	}
	else
	{
		CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("ConfList") );
		if ( pTileLayoutUI == NULL )
		{
			return false;
		}

		pTileLayoutUI->RemoveAll();

		for ( int i = 0; i < m_vctCnsInfoList.size(); i++ )
		{
			CString strConfTempName;
			strConfTempName.Format( _T("%s"),CA2T( m_vctCnsInfoList.at(i).m_achRoomName));
			BOOL bFind = FALSE;			
			bFind = UIDATAMGR->HZPYMatchList( strSearch, strConfTempName );
			if ( bFind )
			{
				m_vctShowCnsList.push_back( m_vctCnsInfoList.at(i));
				CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("ScreenSelWatchItem") );
				TSelViewInfo tSelViewInfo = m_vctCnsInfoList.at(i); 

				ICncCommonOp::SetControlText( CA2T(tSelViewInfo.m_achRoomName), m_pm, _T("AddrEntryName"), pListContainer );
				if (m_vctCnsInfoList.at(i).m_emType == EmEpType_Eqp) //若画面合成开启并且搜索后第一个元素被搜索到，更换显示的图片
				{
					ICncCommonOp::SetControlBkImg(_T("res\\list\\imgVidMix.png"), m_pm, _T("imgAddrLabel"), pListContainer);
				}
				else if (m_vctCnsInfoList.at(i).m_emEpType ==  emTPEndpointH323G400)
				{
					ICncCommonOp::SetControlBkImg(_T("res\\list\\imgMonitor.png"), m_pm, _T("imgAddrLabel"), pListContainer);
				}
				else if (m_vctCnsInfoList.at(i).m_emEpType == emTPEndpointTypeVRS)
				{
					ICncCommonOp::SetControlBkImg(_T("res\\list\\imgStudio.png"), m_pm, _T("imgAddrLabel"), pListContainer);
				}
				else if (m_vctCnsInfoList.at(i).m_emEpType !=  emTPEndpointTypeCNS)
				{
					ICncCommonOp::SetControlBkImg(_T("res\\list\\imgOrdinary.png"), m_pm, _T("imgAddrLabel"), pListContainer);
				}

				//三屏会场显示屏幕
				if ((EmEpType_Ter == tSelViewInfo.m_emType) && (3 == tSelViewInfo.m_wSpeakerNum))
				{
					m_pm->DoCase(_T("caseHideScreenOption"), pListContainer);
				}
				else
				{
					ICncCommonOp::ShowControl(false, m_pm, _T("BtnScreenOption"), pListContainer);
				}

				//会场列表选择按钮checkbox
                ICncCommonOp::ShowControl(true, m_pm, _T("BtnRoomSel"), pListContainer);
// 				if (EmEpType_Ter == tSelViewInfo.m_emType)
// 				{
// 					ICncCommonOp::ShowControl(true, m_pm, _T("BtnRoomSel"), pListContainer);
// 				}
// 				else
// 				{
// 					ICncCommonOp::ShowControl(false, m_pm, _T("BtnRoomSel"), pListContainer);
// 				}

                pListContainer->SetTag( (UINT_PTR)&m_vctCnsInfoList.at(i));

				pTileLayoutUI->Add(pListContainer);
			}
		}
	}
	return false;
}

bool CTvWallLogic::OnBtnCloseMuteView( TNotifyUI& msg )
{
	CControlUI *pParent = msg.pSender->GetParent();
	CListContainerElementUI *pContainer= dynamic_cast<CListContainerElementUI*>(pParent->GetParent());
	if ( pContainer == NULL  )
	{
		return false;
	}
	
	u8 byIndex = (u8)pContainer->GetTag();

	u16 wRe = ComInterface->ChangeChanModeReq(byIndex,0);

	//if ( wRe != NO_ERROR )
	//{

	//}
	return true;
}

bool CTvWallLogic::onHduVolChanged(TNotifyUI& msg )
{
	int dwVol = 0;
	BOOL32 bMute = FALSE;
	u8  bIndex = 0;
	u16 wRe;
	CString strVol=_T("");

	if (msg.sType == _T("valuechanged"))
	{
		dwVol = (static_cast<CSliderUI*>(msg.pSender))->GetValue();
	}

	strVol.Format(_T("%d%%"),dwVol);
	ICncCommonOp::SetControlText(strVol,m_pm,_T("lbTvWallvol"));

	u8 byVolume = dwVol*31/100;

	CCheckBoxUI* pMuteCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckTvWallSlient"));
	if ( pMuteCheckBox != NULL )
	{
		if ( pMuteCheckBox->GetCheck() == true )
		{
			pMuteCheckBox->SetCheckNoMsg(false);
		}
		bIndex = pMuteCheckBox->GetTag();

		wRe =  ComInterface->SetHduVolReq( bIndex,byVolume,bMute);
	}
	else
	{
		return false;
	}
	return wRe;
}

bool CTvWallLogic::onHduVolChanging( TNotifyUI& msg )
{
	CString strVol=_T("");
	strVol.Format(_T("%d%%"),(static_cast<CSliderUI*>(msg.pSender))->GetValue());
	ICncCommonOp::SetControlText(strVol,m_pm,_T("lbTvWallvol"));

	CCheckBoxUI* pMuteCheck = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckTvWallSlient"));

	if ( pMuteCheck != NULL && pMuteCheck->GetCheck() == true )
	{
		pMuteCheck->SetCheckNoMsg(false);
	}

	return true;
}

bool CTvWallLogic::OnCheckSlient( TNotifyUI& msg )
{
	int dwVol = 0;
	BOOL32 bMute = FALSE;
	u8  bIndex = 0;
	u16 wRe;

	CSliderUI* pSilder = (CSliderUI*)ICncCommonOp::FindControl( m_pm, _T("sldTvWallVol") );
	if ( pSilder != NULL )
	{
		dwVol = pSilder->GetValue();
	}

	u8 byVolume = dwVol*31/100;

	CCheckBoxUI* pMuteCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckTvWallSlient"));
	if ( pMuteCheckBox != NULL )
	{
		if ( pMuteCheckBox->GetCheck() == true )
		{
			bMute = TRUE;
		}

		bIndex = pMuteCheckBox->GetTag();

		wRe =  ComInterface->SetHduVolReq( bIndex,byVolume,bMute);
	}
	else
	{
		return false;
	}
	return wRe;
}

bool CTvWallLogic::OnCheckSrceen1( TNotifyUI& msg )
{
	CCheckBoxUI* pControl = (CCheckBoxUI*)msg.pSender;
	if (pControl->GetCheck())
	{
		vector<int>::iterator it = find(m_vctSelSrceen.begin(),m_vctSelSrceen.end(),0);
		if (it == m_vctSelSrceen.end())
		{
			m_vctSelSrceen.push_back(0);
		}
	}
	else
	{
		for(vector<int>::iterator it = m_vctSelSrceen.begin(); it != m_vctSelSrceen.end(); )
		{
			if(*it == 0)
			{
				it  =  m_vctSelSrceen.erase(it); 
			}
			else
			{
				++it;
			}
		}
	}
	SetBtnRoomSelStatus(msg);
	return true;
}

bool CTvWallLogic::OnCheckSrceen2( TNotifyUI& msg )
{
	CCheckBoxUI* pControl = (CCheckBoxUI*)msg.pSender;
	if (pControl->GetCheck())
	{
		vector<int>::iterator it = find(m_vctSelSrceen.begin(),m_vctSelSrceen.end(),1);
		if (it == m_vctSelSrceen.end())
		{
			m_vctSelSrceen.push_back(1);
		}
	}
	else
	{
		for(vector<int>::iterator it = m_vctSelSrceen.begin(); it != m_vctSelSrceen.end(); )
		{
			if(*it == 1)
			{
				it  =  m_vctSelSrceen.erase(it); 
			}
			else
			{
				++it;
			}
		}
	}
	SetBtnRoomSelStatus(msg);
	return true;
}

bool CTvWallLogic::OnCheckSrceen3( TNotifyUI& msg )
{
	CCheckBoxUI* pControl = (CCheckBoxUI*)msg.pSender;
	if (pControl->GetCheck())
	{
		vector<int>::iterator it = find(m_vctSelSrceen.begin(),m_vctSelSrceen.end(),2);
		if (it == m_vctSelSrceen.end())
		{
			m_vctSelSrceen.push_back(2);
		}
	}
	else
	{
		for(vector<int>::iterator it = m_vctSelSrceen.begin(); it != m_vctSelSrceen.end(); )
		{
			if(*it == 2)
			{
				it  =  m_vctSelSrceen.erase(it); 
			}
			else
			{
				++it;
			}
		}
	}
	SetBtnRoomSelStatus(msg);
	return true;
}

void CTvWallLogic::SetBtnRoomSelStatus( TNotifyUI& msg )
{
    CTouchListUI* pList = (CTouchListUI*)ICncCommonOp::FindControl(m_pm,_T("ConfList"));
    if (!pList)
    {
        return ;
    }
    CListContainerElementUI *pListContainer = (CListContainerElementUI*)msg.pSender->GetParent()->GetParent()->GetParent();
    if (!pListContainer)
    {
        return ;
    }

    m_nSelIndex = pList->GetItemIndex(pListContainer);

	CCheckBoxUI* pCheckBoxRoomSel = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("BtnRoomSel"), pListContainer);
	if (pCheckBoxRoomSel)
	{
		if (m_vctSelSrceen.size() == 3)
		{
			pCheckBoxRoomSel->SetCheckNoMsg(true);
		}
		else
		{
			pCheckBoxRoomSel->SetCheckNoMsg(false);
		}
	}
}

bool CTvWallLogic::OnLetterIndex( TNotifyUI& msg )
{
	CEditUI* pEditSearch = (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("BtnSearch") );
	if ( !pEditSearch )
	{
		return false;
	}

	vector<TSelViewInfo>  vctCnsInfoList; 

	CString strSearch = pEditSearch->GetText();
	if ( strSearch.IsEmpty() )
	{
		vctCnsInfoList = m_vctCnsInfoList;
	}
	else
	{
		vctCnsInfoList = m_vctShowCnsList;
	}

	if (vctCnsInfoList.size() == 0)
	{
		return false;
	}

	int nLetterIndex = (int)msg.wParam;
	CTouchListUI* pTouch = (CTouchListUI*)ICncCommonOp::FindControl(m_pm, _T("ConfList"));
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
	int nItemCount = vctCnsInfoList.size();

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
		UIDATAMGR->GetFirstLetter( vctCnsInfoList.at(swMidIndex).m_achRoomName, strLetter ); 

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
		UIDATAMGR->GetFirstLetter(vctCnsInfoList.at(swMidIndex).m_achRoomName, strLetter ); 

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

bool CTvWallLogic::OnBtnSetVoice( TNotifyUI& msg )
{
	CControlUI *pControl = msg.pSender;
	TTpHduPlanUnit tpHduPlanUnit =*(TTpHduPlanUnit *)pControl->GetTag();

	u8 vol = tpHduPlanUnit.m_byVol*100/31;

	CSliderUI* pSilder = (CSliderUI*)ICncCommonOp::FindControl( m_pm, _T("sldTvWallVol") );
	if (pSilder)
	{
		pSilder->SetValue(vol);
	}
	CString strVol=_T("");
	strVol.Format(_T("%d%%"),vol);
	ICncCommonOp::SetControlText(strVol,m_pm,_T("lbTvWallvol"));
	CCheckBoxUI* pMuteCheck = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckTvWallSlient"));

	if ( pMuteCheck == NULL )
	{
		return false;
	}

	if (tpHduPlanUnit.m_byMute == 1 )
	{
		pMuteCheck->SetCheckNoMsg(true);
	}
	else
	{
		pMuteCheck->SetCheckNoMsg(false);
	}
	u8  Index = ( pControl->GetParent()->GetParent())->GetTag();
	pMuteCheck->SetTag(Index);

	UIDATAMGR->SetCurShowWndName( g_stcStrTvWallChildDlg );
	ICncCommonOp::ShowControl( true, m_pm, _T("PageVolCtrl") );
	return true;
}

bool CTvWallLogic::OnBtnTvWallItem( TNotifyUI& msg )
{
    if ( CListContainerElementUI *pContainer= dynamic_cast<CListContainerElementUI*>(msg.pSender) )
    {
        int nIndex = pContainer->GetIndex();
        if ( m_nCtrlIndex == nIndex )
        {
            return true;
        }
        else
        {
            //点击框直接添加会场
            OnBtnAddTvWall(msg);
        }
    }
    return true;
}

bool CTvWallLogic::OnBtnAddTvWall( TNotifyUI& msg )
{
	m_bySubIndex =0;
	m_vctSelSrceen.clear();

    CListContainerElementUI *pContainer = NULL;

	CDuiString strName = msg.pSender->GetName();
	m_strChannelAlias = "";
	if ( strName==_T("TvWallCfgItem") )
	{
		m_bySubIndex = 0;
        pContainer = dynamic_cast<CListContainerElementUI*>(msg.pSender);

        if ( pContainer != NULL )
        {
            CButtonUI* pBtnVolCtrl = (CButtonUI*)ICncCommonOp::FindControl( m_pm, m_strBtnSetVoice.c_str(), pContainer);
			//如果通道不可用或者通道不在线就返回
            TTpHduPlanUnit tHduPlanUnit =*(TTpHduPlanUnit *)pBtnVolCtrl->GetTag();
			m_strChannelAlias = tHduPlanUnit.m_atPlayInfo->m_achAlias;
            if ( !tHduPlanUnit.m_byValid || !tHduPlanUnit.m_byReged)
            {
                return false;
            }
        }       
	}
	else
    {    
        if ( strName==_T("BtnEnable") )
        {
            m_bySubIndex = 0;
        }
        else if( strName == _T("BtnAdd1"))
	    {
		    m_bySubIndex = 0;
			m_strChannelAlias = CW2A(msg.pSender->GetText());
	    }
	    else if(strName == _T("BtnAdd2") )
	    {
		    m_bySubIndex = 1;
			m_strChannelAlias = CW2A(msg.pSender->GetText());
	    }
	    else if( strName == _T("BtnAdd3"))
	    {
		    m_bySubIndex = 2;
			m_strChannelAlias = CW2A(msg.pSender->GetText());
	    }
	    else if( strName == _T("BtnAdd4"))
	    {
		    m_bySubIndex = 3;
			m_strChannelAlias = CW2A(msg.pSender->GetText());
	    }

        pContainer = dynamic_cast<CListContainerElementUI*>(msg.pSender->GetParent()->GetParent());
		//如果通道不可用或者通道不在线就返回
		CButtonUI* pBtnVolCtrl = (CButtonUI*)ICncCommonOp::FindControl( m_pm, m_strBtnSetVoice.c_str(), pContainer);
		TTpHduPlanUnit tHduPlanUnit =*(TTpHduPlanUnit *)pBtnVolCtrl->GetTag();
		//m_strChannelAlias = tHduPlanUnit.m_atPlayInfo->m_achAlias;
		if ( !tHduPlanUnit.m_byValid || !tHduPlanUnit.m_byReged)
		{
			return false;
		}
    }

	if ( pContainer != NULL )
    {
	    m_nSelectIndex = pContainer->GetTag();
    }
	//UIDATAMGR->SetCurShowWndName( g_stcStrTvWallChildDlg );

	CEditUI* pEditSearch = (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("ConfListSearch") );
    if ( pEditSearch != NULL )
    {
        pEditSearch->SetText(_T(""));
    }
	
	UpdateCnsList();
	UpdateShowList();

	m_emCnsShowState = emShowAll;
	m_nSelIndex = -1;
	ICncCommonOp::ShowControl( true, m_pm, _T("PageSelConfList") );
	return true;
}

bool CTvWallLogic::OnBtnConfirm( TNotifyUI& msg )
{
	if ( m_nSelIndex == -1 )
	{
		showMessageBox(_T("请先选择会场"));
		return false;
	}
	TSelViewInfo tSelInfo = m_vctShowCnsList.at(m_nSelIndex);
	if ( (EmEpType_Ter == tSelInfo.m_emType) && (3 == tSelInfo.m_wSpeakerNum) &&  m_vctSelSrceen.empty() )
	{
		showMessageBox(_T("请选择屏幕"));
		return false;
	}

	SetCnsInTvw();
	UIDATAMGR->SetCurShowWndName( g_strConfCtrlDlg );
	ICncCommonOp::ShowControl( false, m_pm, _T("PageSelConfList") );
	return true;
}

bool CTvWallLogic::OnBtnStopPlay( TNotifyUI& msg )
{
	u8 bySubIndex = 0;

	CDuiString strName = msg.pSender->GetName();
	if ( strName==_T("BtnDelete") )
	{
		bySubIndex = 0;
	}
	else if( strName == _T("BtnDelView1"))
	{
		bySubIndex = 0;
	}
	else if(strName == _T("BtnDelView2") )
	{
		bySubIndex = 1;
	}
	else if( strName == _T("BtnDelView3"))
	{
		bySubIndex = 2;
	}
	else if( strName == _T("BtnDelView4"))
	{
		bySubIndex = 3;
	}

	CControlUI *pParent = msg.pSender->GetParent();
	CListContainerElementUI *pContainer = NULL;
	if ( strName == _T("BtnDelete") )
	{
		pContainer = dynamic_cast<CListContainerElementUI*>(pParent);
	}
	else
	{
		pContainer= dynamic_cast<CListContainerElementUI*>(pParent->GetParent());
	}

	if ( pContainer == NULL )
	{
		return true;
	}

	m_nSelectIndex = pContainer->GetTag();
	CButtonUI* pBtnVoice = (CButtonUI*)ICncCommonOp::FindControl( m_pm, m_strBtnSetVoice.c_str(), pContainer);
	TTpHduPlanUnit tHduPlanUnit = *(TTpHduPlanUnit*)pBtnVoice->GetTag();


	TTpHduPlayReq tTvwInfo;

	tTvwInfo.m_emType = tHduPlanUnit.m_atPlayInfo[bySubIndex].m_emType;
	tTvwInfo.m_wConfID = tHduPlanUnit.m_atPlayInfo[bySubIndex].m_wConfID;
	tTvwInfo.m_wDstID = tHduPlanUnit.m_atPlayInfo[bySubIndex].m_wDstID;
	tTvwInfo.m_wScreenNum = tHduPlanUnit.m_atPlayInfo[bySubIndex].m_wScreenNum;	//屏号从0开始
	tTvwInfo.m_wIndex = m_nSelectIndex;
	tTvwInfo.m_bySubIndex = bySubIndex;
	tTvwInfo.m_bVmp = (BOOL32)tHduPlanUnit.m_byVmp;
	tTvwInfo.SetAlias(tHduPlanUnit.m_atPlayInfo[bySubIndex].m_achAlias);

	ComInterface->StopPlayHdu(tTvwInfo);

	return true;
}

void CTvWallLogic::clear()
{
	m_emCnsShowState = emShowAll;
	m_nSelectIndex = -1;
	m_nCtrlIndex = -1;
	m_nSelIndex = -1;
}

void CTvWallLogic::UpdateTvWall( )
{
	CTouchListUI* pTvWallList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("TvWallList") );

	if ( pTvWallList == NULL )
	{
		return ;
	}
	s32 nCount = pTvWallList->GetCount();
	int nCol = pTvWallList->GetColumns();

	if (( nCount == m_tHduPlanData[0].m_wNum )&& (nCol == m_tHduPlanData[0].m_byCol ) )
	{
		for( u8 byNum = 0; byNum < m_tHduPlanData[0].m_wNum ;byNum ++ )
		{
			CListContainerElementUI *pListContainer =(CListContainerElementUI *)pTvWallList->GetItemAt(byNum);

			CButtonUI* pBtnTvWallSet = (CButtonUI*)ICncCommonOp::FindControl( m_pm, m_strSetTvWallBtn.c_str(), pListContainer);
			CButtonUI* pBtnVolCtrl = (CButtonUI*)ICncCommonOp::FindControl( m_pm, m_strBtnSetVoice.c_str(), pListContainer);

			if ( pBtnTvWallSet == NULL )
			{
				return ;
			}

			s32 nRow = byNum/TP_STYLE_DATA_PACK_NUM;
			s32 nCol = byNum%TP_STYLE_DATA_PACK_NUM;

			TTpHduPlanUnit tHduPlanUnit =*(TTpHduPlanUnit *)pBtnVolCtrl->GetTag();

			bool  bChange = false;

			for( u8 byIndex = 0; byIndex < HDU_MAX_VMP_SUBCHAN ; byIndex ++ )
			{
				if ( memcmp(&tHduPlanUnit.m_atPlayInfo[byIndex],&m_tOldHduPlanData[nRow].m_atUnits[nCol].m_atPlayInfo[byIndex],sizeof(TTpHduUnitPlayInfo)-sizeof(EmCnsHduRunStatus)) != 0 )
				{
					bChange = true;
					break;
				}
			}

			if (( tHduPlanUnit.m_byVmp != m_tOldHduPlanData[nRow].m_atUnits[nCol].m_byVmp  ) || ( tHduPlanUnit.m_byReged != m_tOldHduPlanData[nRow].m_atUnits[nCol].m_byReged)
				|| (tHduPlanUnit.m_byValid != m_tOldHduPlanData[nRow].m_atUnits[nCol].m_byValid) || ( strcmp( tHduPlanUnit.m_achAlias,m_tOldHduPlanData[nRow].m_atUnits[nCol].m_achAlias) != 0 )
				|| ( tHduPlanUnit.m_byMute!= m_tOldHduPlanData[nRow].m_atUnits[nCol].m_byMute)||( bChange != false ))
			{
				SetStatus(pBtnTvWallSet,0);
                m_nCtrlIndex = -1;
			}

			//pBtnTvWallSet->SetTag((UINT_PTR)(0));
			//pListContainer->SetTag((UINT_PTR)(byNum));
			pBtnVolCtrl->SetTag((UINT_PTR)(&m_tHduPlanData[nRow].m_atUnits[nCol]));

			updateItem(pListContainer,m_tHduPlanData[nRow].m_atUnits[nCol]);
		}
	}
	else
	{
		pTvWallList->RemoveAll();

		pTvWallList->SetColumns(m_tHduPlanData[0].m_byCol);

		for( u8 byNum = 0; byNum < m_tHduPlanData[0].m_wNum ;byNum ++ )
		{
			CListContainerElementUI *pListContainer = 
				(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("TvWallCfgItem") );

			CButtonUI* pBtnTvWallSet = (CButtonUI*)ICncCommonOp::FindControl( m_pm, m_strSetTvWallBtn.c_str(), pListContainer);
			CButtonUI* pBtnVolCtrl = (CButtonUI*)ICncCommonOp::FindControl( m_pm, m_strBtnSetVoice.c_str(), pListContainer);

			if ( pBtnTvWallSet == NULL )
			{
				return ;
			}

			s32 nLeft = byNum/TP_STYLE_DATA_PACK_NUM;
			s32 nIndex = byNum%TP_STYLE_DATA_PACK_NUM;

			SetStatus(pBtnTvWallSet,0);
			pListContainer->SetTag((UINT_PTR)(byNum));
			pBtnVolCtrl->SetTag((UINT_PTR)(&m_tHduPlanData[nLeft].m_atUnits[nIndex]));

			pTvWallList->Add(pListContainer);
			updateItem(pListContainer,m_tHduPlanData[nLeft].m_atUnits[nIndex]);
		}
	}
}

bool CTvWallLogic::OnHduPlanNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	memcpy(m_tHduPlanData,(TTpHduPlanPackData * )(wParam),sizeof(m_tHduPlanData));
	UpdateTvWall();
	memcpy(m_tOldHduPlanData,(TTpHduPlanPackData * )(wParam),sizeof(m_tOldHduPlanData));
	return true;
}

void CTvWallLogic::updateItem( CListContainerElementUI * pListContainer , TTpHduPlanUnit & tHduPlanUnit )
{
	s8 chBuffer[10]= {0};
	bool byUsed = false;
	string strName = "";

	u16 wPlayMaxNum = HDU_MAX_VMP_SUBCHAN;
	if ( 0 == tHduPlanUnit.m_byVmp )
	{
		wPlayMaxNum = 1;
	}

	CButtonUI* pBtnTvWallSet = (CButtonUI*)ICncCommonOp::FindControl( m_pm, m_strSetTvWallBtn.c_str(), pListContainer);

	u8 bCfg = GetStatus(pBtnTvWallSet);

	for ( u16 wPlayIndex1 = 0; wPlayIndex1 < wPlayMaxNum; wPlayIndex1++ )
	{
		if ( tHduPlanUnit.m_atPlayInfo[wPlayIndex1].m_wDstID != TP_INVALID_INDEX )
		{
			byUsed = true;
			break;
		}
	}

	ICncCommonOp::ShowControl( false, m_pm, _T("imgTvWallQuiet"), pListContainer );

	if ( tHduPlanUnit.m_byVmp == 0 )
	{
		if ( tHduPlanUnit.m_byValid == 1 )
		{
			if ( bCfg == 0 )
			{
				if ( tHduPlanUnit.m_byMute == 1)
				{
					ICncCommonOp::ShowControl( true, m_pm, _T("imgTvWallQuiet"), pListContainer );
				}

				m_pm->DoCase( _T("caseNormal"), pListContainer );

                if ( tHduPlanUnit.m_byReged == 0 )
                {
                    pListContainer->SetBkImage( _T("res/confctrl/tvwall/bg.png") );
					byUsed = false;
                }

				if ( tHduPlanUnit.m_byReged == 0 )
				{
					ICncCommonOp::ShowControl( false, m_pm, _T("BtnTvWallSet"), pListContainer );
				}
				else
				{
					ICncCommonOp::ShowControl( true, m_pm, _T("BtnTvWallSet"), pListContainer );
				}
			}
			else
			{
				if ( byUsed == true )
				{
					m_pm->DoCase( _T("caseHduExistCfg"), pListContainer );
				}
				else
				{
					m_pm->DoCase( _T("caseSetTvWall"), pListContainer );
				}
			}

			if ( byUsed == false )
			{
				memset(chBuffer,0,sizeof(chBuffer));
				strName = tHduPlanUnit.m_achAlias;
				sprintf(chBuffer,"-%d",tHduPlanUnit.m_byChanIndex);
				strName = strName + chBuffer;

				ICncCommonOp::SetControlText( (CA2T)( strName.c_str()), m_pm, m_strChannelDesc.c_str(), pListContainer );
				m_pm->DoCase( _T("caseSrceenIndexHide"), pListContainer );
			}
			else
			{
				CTextUI* pText = (CTextUI*)ICncCommonOp::FindControl( m_pm, m_strChannelDesc.c_str(), pListContainer);
				ICncCommonOp::SetControlText( (CA2T)( tHduPlanUnit.m_atPlayInfo[0].m_achAlias ), m_pm, m_strChannelDesc.c_str(), pListContainer );	
				TCMSConf tConfInfoTemp;
				BOOL32 bInConf =  ComInterface->IsInConf( &tConfInfoTemp );
				if (bInConf)
				{
					TCnsInfo* tCnsInfo = tConfInfoTemp.GetCnsInfoByID(tHduPlanUnit.m_atPlayInfo[0].m_wDstID);
					if (tCnsInfo && (3 == tCnsInfo->m_wSpeakerNum) && (tHduPlanUnit.m_atPlayInfo[0].m_wScreenNum < MAX_SEAT_COUNT))
					{
						ICncCommonOp::SetControlText( m_strArrayScreen[tHduPlanUnit.m_atPlayInfo[0].m_wScreenNum].c_str(), 
							                          m_pm, m_strSrceenDesc.c_str(), pListContainer );
						m_pm->DoCase( _T("caseSrceenIndexShow"), pListContainer );
					}
					else
					{
						ICncCommonOp::SetControlText( _T(""), m_pm, m_strSrceenDesc.c_str(), pListContainer );	
						m_pm->DoCase( _T("caseSrceenIndexHide"), pListContainer );
					}
				}
			}
		}
		else
		{
			ICncCommonOp::SetControlText( _T("不可用"), m_pm,_T("TxtDescribe"), pListContainer );
			m_pm->DoCase( _T("caseInvalid"), pListContainer );
			m_pm->DoCase( _T("caseSrceenIndexHide"), pListContainer );
		}		
	}
	else
	{
		if (bCfg == 0 )
		{
			m_pm->DoCase( _T("caseMuteView"), pListContainer );
		}
		else
		{
			m_pm->DoCase( _T("caseMuteViewCfg"), pListContainer );
		}

		s8 chLebBuffer[20] = {0};
        s8 chBtnBuffer[20] = {0};
        s8 chBtnDelBuffer[20] = {0};
		s8 chChannelSrceenShow[32] = {0};
		s8 chChannelSrceenHide[32] = {0};
		for( u8 byIndex = 0; byIndex < HDU_MAX_VMP_SUBCHAN ; byIndex ++ )
		{			
			memset(chLebBuffer,0,sizeof(chLebBuffer));
			sprintf(chLebBuffer,"LebSrceen%d",(byIndex+1));

			memset(chBtnBuffer,0,sizeof(chBtnBuffer));
			sprintf(chBtnBuffer,"BtnAdd%d",(byIndex+1));
		
			memset(chBtnDelBuffer,0,sizeof(chBtnDelBuffer));
			sprintf(chBtnDelBuffer,"BtnDelView%d",(byIndex+1));

			memset(chChannelSrceenShow,0,sizeof(chBtnDelBuffer));
			sprintf(chChannelSrceenShow,"caseChannelSrceenIndexShow%d",(byIndex+1));

			memset(chChannelSrceenHide,0,sizeof(chBtnDelBuffer));
			sprintf(chChannelSrceenHide,"caseChannelSrceenIndexHide%d",(byIndex+1));

			if ( tHduPlanUnit.m_atPlayInfo[byIndex].m_wDstID != TP_INVALID_INDEX )
			{
				if ( bCfg == 1 )
				{
					ICncCommonOp::EnableControl( true, m_pm, (CA2T)(chBtnDelBuffer), pListContainer );
					m_pm->DoCase( (CA2T)(chChannelSrceenHide), pListContainer );
				}
				else
				{
					TCMSConf tConfInfoTemp;
					ICncCommonOp::SetControlText( (CA2T)( tHduPlanUnit.m_atPlayInfo[byIndex].m_achAlias ), m_pm, (CA2T)(chBtnBuffer), pListContainer );
					BOOL32 bInConf =  ComInterface->IsInConf( &tConfInfoTemp );
					if (bInConf)
					{
						TCnsInfo* tCnsInfo = tConfInfoTemp.GetCnsInfoByID(tHduPlanUnit.m_atPlayInfo[byIndex].m_wDstID);
						if (tCnsInfo && (3 == tCnsInfo->m_wSpeakerNum) && (tHduPlanUnit.m_atPlayInfo[byIndex].m_wScreenNum < MAX_SEAT_COUNT))
						{
							m_pm->DoCase( (CA2T)(chChannelSrceenShow), pListContainer );
							ICncCommonOp::SetControlText( m_strArrayScreen[tHduPlanUnit.m_atPlayInfo[byIndex].m_wScreenNum].c_str(),
								                          m_pm, (CA2T)(chLebBuffer), pListContainer );
						}
						else
						{
							m_pm->DoCase( (CA2T)(chChannelSrceenHide), pListContainer );
							ICncCommonOp::SetControlText( _T(""), m_pm, (CA2T)(chLebBuffer), pListContainer );
						}
					}
				}
			}
			else
			{
				m_pm->DoCase( (CA2T)(chChannelSrceenHide), pListContainer );
				ICncCommonOp::SetControlText( _T(""), m_pm, (CA2T)(chBtnBuffer), pListContainer );
				if ( bCfg == 1 )
				{
					ICncCommonOp::EnableControl( false, m_pm, (CA2T)(chBtnDelBuffer), pListContainer );
				}
			}
		}
	}
}

bool CTvWallLogic::OnHideChildWindowNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_nSelIndex = -1;

	ICncCommonOp::ShowControl( false, m_pm, _T("PageVolCtrl") );
	ICncCommonOp::ShowControl( false, m_pm, _T("PageSelConfList") );
	UIDATAMGR->SetCurShowWndName( g_strConfCtrlDlg.c_str());
	return true;
}

void CTvWallLogic::HideChildWindow()
{
    m_nSelIndex = -1;

    ICncCommonOp::ShowControl( false, m_pm, _T("PageVolCtrl") );
    ICncCommonOp::ShowControl( false, m_pm, _T("PageSelConfList") );
    UIDATAMGR->SetCurShowWndName( g_strConfCtrlDlg.c_str() );
}


bool CTvWallLogic::OnHduVolumeInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TTpHduSetVolInfo  tHduSetVolInfo = *( TTpHduSetVolInfo *)(wParam);
	EmCnsHduSetVolRes emHduSetVolRes = *(EmCnsHduSetVolRes*)(lParam);

	if ( emHduSetVolRes == em_Cnshdu_SetVol_Success )
	{
		CTouchListUI* pTvWallList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("TvWallList") );
		CListContainerElementUI * pListContainer = (CListContainerElementUI*)pTvWallList->GetItemAt(tHduSetVolInfo.m_tInfo.m_wIndex);
		CButtonUI* pBtnVolCtrl = (CButtonUI*)ICncCommonOp::FindControl( m_pm, m_strBtnSetVoice.c_str(), pListContainer);

		s32 nRow = tHduSetVolInfo.m_tInfo.m_wIndex/TP_STYLE_DATA_PACK_NUM;
		s32 nCol = tHduSetVolInfo.m_tInfo.m_wIndex%TP_STYLE_DATA_PACK_NUM;

		m_tHduPlanData[nRow].m_atUnits[nCol].m_byMute =(( tHduSetVolInfo.m_bMute == TRUE )? 1:0 );
		m_tHduPlanData[nRow].m_atUnits[nCol].m_byVol = tHduSetVolInfo.m_byVol;

        if ( pBtnVolCtrl )
        {
		    pBtnVolCtrl->SetTag((UINT_PTR)(&m_tHduPlanData[nRow].m_atUnits[nCol]));
        }
	}
	else
	{
		CString strTip = _T("设置电视墙音量失败：");
		switch( emHduSetVolRes )
		{
		case em_Cnshdu_SetVol_Invalid_Index:
			strTip += _T("无效的索引");
			break;
		case em_Cnshdu_SetVol_UnReg:
			strTip += _T("该通道未上线");
			break;
		case em_Cnshdu_SetVol_VmpChan:
			strTip += _T("多画面合成模式不能调节音量");
			break;
		default:
			break;
		}
		if ( strTip.GetLength()!= 0 )
		{
			ShowPopMsg(strTip);
		}

		u8 vol = tHduSetVolInfo.m_byVol*100/31;

		CSliderUI* pSilder = (CSliderUI*)ICncCommonOp::FindControl( m_pm, _T("sldTvWallVol") );
		if (pSilder)
		{
			pSilder->SetValue(vol);
		}
		CString strVol=_T("");
		strVol.Format(_T("%d%%"),vol);
		ICncCommonOp::SetControlText(strVol,m_pm,_T("lbspeakervol"));
		CCheckBoxUI* pMuteCheck = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckTvWallSlient"));
        if ( pMuteCheck != NULL )
        {
		    if (tHduSetVolInfo.m_bMute == TRUE )
		    {
			    pMuteCheck->SetCheck(true);
		    }
		    else
		    {
			    pMuteCheck->SetCheck(false);
		    }
        }
	}
	return true;
}

bool CTvWallLogic::OnHduChangeModeInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TTpHduChanModeSetInfo tHduChaModeInfo = *( TTpHduChanModeSetInfo *)(wParam);
	EmCnsHduChangeChanModeRes emHduChangeModeRes = *(EmCnsHduChangeChanModeRes*)(lParam);

	CString strTip = _T("");
	if ( tHduChaModeInfo.m_byMode == 0 )
	{
		strTip = _T("关闭电视墙多画面失败:");
	}
	else
	{
		strTip = _T("开启电视墙多画面失败:");

	}

	switch(emHduChangeModeRes )
	{
	case em_Cnshdu_change_mode_success:
		{
			u8 byRow = tHduChaModeInfo.m_wIndex/TP_STYLE_DATA_PACK_NUM;
			u8 byCol = tHduChaModeInfo.m_wIndex%TP_STYLE_DATA_PACK_NUM;

			strTip = _T("");
			CTouchListUI* pTvWallList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("TvWallList") );
			CListContainerElementUI * pListContainer = (CListContainerElementUI*)pTvWallList->GetItemAt(tHduChaModeInfo.m_wIndex);
			CButtonUI* pBtnTvWallSet = (CButtonUI*)ICncCommonOp::FindControl( m_pm, m_strSetTvWallBtn.c_str(), pListContainer);
			CButtonUI* pBtnVolCtrl = (CButtonUI*)ICncCommonOp::FindControl( m_pm, m_strBtnSetVoice.c_str(), pListContainer);

			//if ( pListContainer != NULL  )
			//{
			//	//SetStatus(pBtnTvWallSet,0);
			//	if ( tHduChaModeInfo.m_byMode == 0 )
			//	{
			//		m_tHduPlanData[byRow].m_atUnits[byCol].m_byVmp=0;
			//	}
			//	else
			//	{
			//		m_tHduPlanData[byRow].m_atUnits[byCol].m_byVmp=1;
			//	}
			//	pBtnVolCtrl->SetTag((UINT_PTR)(&m_tHduPlanData[byRow].m_atUnits[byCol]));

			//	//updateItem(pListContainer,m_tHduPlanData[byRow].m_atUnits[byCol]);
			//}
		}
		break;
	case em_Cnshdu_change_mode_error_index:
		strTip += _T("无效的通道");
		break;
	case em_Cnshdu_change_mode_error_param:
		strTip += _T("参数错误");
		break;
	case em_Cnshdu_change_mode_error_regstate:
		strTip += _T("通道未注册");
		break;
	case em_Cnshdu_change_mode_error_onlyoneVmp:
		strTip += _T("电视墙通道只能有一个是多画面模式");
		break;
	case em_Cnshdu_change_mode_error_workingstate:
		strTip += _T("通道处于繁忙状态");
		break;
	case em_Cnshdu_change_mode_error_fromhdu:
		strTip += _T("返回切换模式出错");
		break;
	default:
		strTip = _T("");
		break;
	}
	
	if ( strTip.GetLength()!= 0 )
	{
		ShowPopMsg(strTip);
	}

	return true;
}

bool CTvWallLogic::OnHduStopPlayInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TTpHduBaseInfo tHduBaseInfo = *( TTpHduBaseInfo *)(wParam);
	u16 wRet = *(u16*)(lParam);

	CTouchListUI* pTvWallList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("TvWallList") );
	CListContainerElementUI * pListContainer = (CListContainerElementUI*)pTvWallList->GetItemAt(tHduBaseInfo.m_wIndex);
	CButtonUI* pBtnTvWallSet = (CButtonUI*)ICncCommonOp::FindControl( m_pm, m_strSetTvWallBtn.c_str(), pListContainer);

	if ( pBtnTvWallSet != NULL  )
	{
		//pBtnTvWallSet->SetTag(0);
	}
	return true;
}

void CTvWallLogic::UpdateCnsList()
{
	TCMSConf tConfInfoTemp;
	BOOL32 bInConf =  ComInterface->IsInConf( &tConfInfoTemp );
	if ( !bInConf )
	{  
		//还原显示选项
		//InitLst();
		PrtMsg(0,emEventTypeCmsWindow,"[CConfCnsLstLogic::UpdateCnsLst]: 本地cns不在会议中，不刷新cns列表，隐藏cns列表界面");
		return;
	}

	m_vctCnsInfoList.clear();
	for (int i = 0; i < tConfInfoTemp.m_vctCnsList.size(); i++)
	{
		if ( tConfInfoTemp.m_vctCnsList.at(i).m_bOnline == false )
		{
			continue;
		}

		if ( emTPEndpointTypeCNS != tConfInfoTemp.m_vctCnsList.at(i).m_emEpType 
			&& emTPEndpointH323MT != tConfInfoTemp.m_vctCnsList.at(i).m_emEpType 
			&& emTPEndpointH323SingleMCU != tConfInfoTemp.m_vctCnsList.at(i).m_emEpType 
			&& emTPEndpointH323G400 != tConfInfoTemp.m_vctCnsList.at(i).m_emEpType )
		{
			//类型不是cns则过滤掉，不显示
			continue;
		}

		TSelViewInfo tSelViewInfo;
		tSelViewInfo.m_wConfID = tConfInfoTemp.m_wConfID;
		tSelViewInfo.m_wEpID = tConfInfoTemp.m_vctCnsList.at(i).m_wEpID;
		tSelViewInfo.m_emType = EmEpType_Ter;
		tSelViewInfo.m_emEpType = tConfInfoTemp.m_vctCnsList.at(i).m_emEpType;
		tSelViewInfo.m_wSpeakerNum = tConfInfoTemp.m_vctCnsList.at(i).m_wSpeakerNum;

		if( strcmp( tConfInfoTemp.m_vctCnsList.at(i).m_achRoomName, "" ) == 0 )
		{
			if ( strcmp( tConfInfoTemp.m_vctCnsList.at(i).m_achRoomE164, "" ) == 0 )
			{
				in_addr tAddr;
				tAddr.S_un.S_addr =tConfInfoTemp.m_vctCnsList.at(i).m_dwRoomIp;
				String strIp = CA2T(inet_ntoa(tAddr));
				if ( strIp == _T("0.0.0.0") )
				{
					strIp = _T("");
				}
				memcpy(tSelViewInfo.m_achRoomName, strIp.c_str(), strIp.size());
			}
			else
			{
				memcpy(tSelViewInfo.m_achRoomName, tConfInfoTemp.m_vctCnsList.at(i).m_achRoomE164, TP_MAX_ALIAS_LEN);
			}
		}
		else
		{
			memcpy(tSelViewInfo.m_achRoomName, tConfInfoTemp.m_vctCnsList.at(i).m_achRoomName, TP_MAX_ALIAS_LEN);
		}

		m_vctCnsInfoList.push_back(tSelViewInfo);
	}

	sort( m_vctCnsInfoList.begin(), m_vctCnsInfoList.end(), CUIDataMgr::SelViewCompare );

	vector<TBrdVmpResNtfy> vctBrdVmpArray = ComInterface->GetBrdVmpStatus();

	CString strVideoMixName;
	for (int i=0; i<vctBrdVmpArray.size(); i++)//所有的都添加进来
	{
		TBrdVmpResNtfy tBrdVmpInfo = vctBrdVmpArray.at(i);
		if (( tBrdVmpInfo.m_wConfID == tConfInfoTemp.m_wConfID )&&( (tBrdVmpInfo.m_emStat == EmBrdVmpStat_Normal)||( tBrdVmpInfo.m_emStat == EmBrdVmpStat_Brd)))
		{
			CString str(tBrdVmpInfo.m_tEqpInfo.m_szEqpAlias);

			TSelViewInfo tSelViewInfo;
			tSelViewInfo.m_wConfID = tConfInfoTemp.m_wConfID;
			tSelViewInfo.m_wEpID = tBrdVmpInfo.m_tEqpInfo.m_byEqpID;
			tSelViewInfo.m_emType = EmEpType_Eqp;
			//tSelViewInfo.m_wDstID = tBrdVmpInfo.m_tEqpInfo.m_byEqpID ;
			memcpy(tSelViewInfo.m_achRoomName,tBrdVmpInfo.m_tEqpInfo.m_szEqpAlias,TP_MAXLEN_EQP_ALIAS);

			m_vctCnsInfoList.insert(m_vctCnsInfoList.begin(),tSelViewInfo);
		}
	}

	//m_tConfInfo = tConfInfoTemp;
	//m_vctCnsList.clear();

	//switch( m_emCnsShowState )
	//{
	//case emShowAll:
	//	{
	//		for ( int i = 0; i< tConfInfoTemp.m_tplCnsList.Size(); i++ )
	//		{
	//			m_vctCnsList.push_back( tConfInfoTemp.m_tplCnsList.GetAt(i) );
	//		}
	//	}
	//	break;
	//case emShowOnLine:
	//	{
	//		for ( int i = 0; i< tConfInfoTemp.m_tplCnsList.Size(); i++ )
	//		{
	//			if ( tConfInfoTemp.m_tplCnsList.GetAt(i).m_bOnline )
	//			{
	//				m_vctCnsList.push_back( tConfInfoTemp.m_tplCnsList.GetAt(i) );
	//			}
	//		} 
	//	}
	//	break;
	//case emShowOffLine:
	//	{
	//		for ( int i = 0; i< tConfInfoTemp.m_tplCnsList.Size(); i++ )
	//		{
	//			if ( !tConfInfoTemp.m_tplCnsList.GetAt(i).m_bOnline )
	//			{
	//				m_vctCnsList.push_back( tConfInfoTemp.m_tplCnsList.GetAt(i) );
	//			}
	//		} 
	//	}
	//	break;
	//default:
	//	break;   
	//} 

	//如果有选中项，更新选中项内容
	//if (!m_vctSelectList.empty())
	//{
	//	for (int i=0; i<m_vctSelectList.size();i++)
	//	{
	//		for(int j=0; j<tConfInfoTemp.m_tplCnsList.Size();j++)
	//		{
	//			if (tConfInfoTemp.m_tplCnsList.GetAt(j).m_wEpID == m_vctSelectList.at(i).m_wEpID)
	//			{
	//				m_vctSelectList.at(i) = tConfInfoTemp.m_tplCnsList.GetAt(j);
	//			}
	//		}
	//	}
	//}
}

bool CTvWallLogic::OnRefreshCnsList( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL32 bInConf = ComInterface->IsInConf();
	if( bInConf )
	{
		UpdateCnsList(); 
		UpdateShowList();
	}

	return true;
}

bool CTvWallLogic::OnBtnCancel(TNotifyUI& msg)
{
	ICncCommonOp::ShowControl( false, m_pm, _T("PageSelConfList") );
	UIDATAMGR->SetCurShowWndName( g_strConfCtrlDlg.c_str());
	UpdateCnsList();
	return true;
}

bool CTvWallLogic::OnBtnShowScreenOption(TNotifyUI& msg)
{
	CTouchListUI* pList = (CTouchListUI*)ICncCommonOp::FindControl(m_pm,_T("ConfList"));
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

	m_pm->DoCase(_T("caseShowScreenOption"), pListContainer);
	return true;
}

bool CTvWallLogic::OnBtnHideScreenOption(TNotifyUI& msg)
{
	CTouchListUI* pList = (CTouchListUI*)ICncCommonOp::FindControl(m_pm,_T("ConfList"));
	if (!pList)
	{
		return false;
	}
	CListContainerElementUI *pListContainer = (CListContainerElementUI*)msg.pSender->GetParent();
	if (!pListContainer)
	{
		return false;
	}
	CTouchListUI* pListScreenSlect = (CTouchListUI*)ICncCommonOp::FindControl(m_pm, _T("ScreenSlectList"), pListContainer);
	if (!pListScreenSlect)
	{
		return false;
	}

	pListScreenSlect->SelectItem(-1);
	m_pm->DoCase(_T("caseHideScreenOption"), pListContainer);
	
	return true;
}

bool CTvWallLogic::OnListBtnRoomSel(TNotifyUI& msg)
{
	CTouchListUI* pList = (CTouchListUI*)ICncCommonOp::FindControl(m_pm,_T("ConfList"));
	if (!pList)
	{
		return false;
	}
	CListContainerElementUI *pListContainer = (CListContainerElementUI*)msg.pSender->GetParent();
	if (!pListContainer)
	{
		return false;
	}

	int nSelIndex = pList->GetItemIndex(pListContainer);
	//pList->SelectItem(nSelIndex);
    ListBtnRoomSel(nSelIndex);

    CCheckBoxUI* pCheckBoxRoomSel = (CCheckBoxUI*)msg.pSender;
    if (!pCheckBoxRoomSel)
    {
        return false;
    }
    bool bIsChecked = pCheckBoxRoomSel->GetCheck();
    if (bIsChecked)
    {
        m_nSelIndex = nSelIndex;
        pListContainer->SetBkImage( _T("res\\list\\item_sel.png") );
    }
    else
    {
        m_nSelIndex = -1;
        pListContainer->SetBkImage( _T("res\\list\\item_normal.png") );
    }
    
	if (nSelIndex != -1)
	{
		TSelViewInfo pTSelViewInfo = *(TSelViewInfo*)pListContainer->GetTag();
		if ((EmEpType_Ter == pTSelViewInfo.m_emType) && ( 3 == pTSelViewInfo.m_wSpeakerNum))
		{
			CCheckBoxUI* pCheckSrceen1 = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckSrceen1"), pListContainer);
			if (pCheckSrceen1)
			{
				pCheckSrceen1->SetCheck(bIsChecked);
			}
			CCheckBoxUI* pCheckSrceen2 = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckSrceen2"), pListContainer);
			if (pCheckSrceen2)
			{
				pCheckSrceen2->SetCheck(bIsChecked);
			}
			CCheckBoxUI* pCheckSrceen3 = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckSrceen3"), pListContainer);
			if (pCheckSrceen3)
			{
				pCheckSrceen3->SetCheck(bIsChecked);
			}
		}
	}

	return true;
}

void CTvWallLogic::ListBtnRoomSel(int nSelIndex)
{
    CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("ConfList") );
    if (!pTileLayoutUI)
    {
        return ;
    }

    if (m_nSelIndex != nSelIndex)
    {
        m_vctSelSrceen.clear();
        CListContainerElementUI *pLastListContainerElement = (CListContainerElementUI *)pTileLayoutUI->GetItemAt(m_nSelIndex);
        if (pLastListContainerElement)
        {
            TSelViewInfo *pTSelViewInfo = &m_vctShowCnsList.at(m_nSelIndex);

            if ((EmEpType_Ter == pTSelViewInfo->m_emType) && ( 3 == pTSelViewInfo->m_wSpeakerNum))
            {
                m_pm->DoCase(_T("caseHideScreenOption"), pLastListContainerElement);
                CCheckBoxUI* pCheckSrceen1 = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckSrceen1"), pLastListContainerElement);
                if (pCheckSrceen1)
                {
                    pCheckSrceen1->SetCheckNoMsg(false);
                }
                CCheckBoxUI* pCheckSrceen2 = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckSrceen2"), pLastListContainerElement);
                if (pCheckSrceen2)
                {
                    pCheckSrceen2->SetCheckNoMsg(false);
                }
                CCheckBoxUI* pCheckSrceen3 = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckSrceen3"), pLastListContainerElement);
                if (pCheckSrceen3)
                {
                    pCheckSrceen3->SetCheckNoMsg(false);
                }
            }
            //if (EmEpType_Ter == pTSelViewInfo->m_emType)
            {
                CCheckBoxUI* pCheckBoxRoomSel = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("BtnRoomSel"), pLastListContainerElement);
                if (pCheckBoxRoomSel)
                {
                    pCheckBoxRoomSel->SetCheckNoMsg(false);
                    pLastListContainerElement->SetBkImage( _T("res\\list\\item_normal.png") );
                }
            }
            pTSelViewInfo = NULL;
        }
        //m_nSelIndex = wCurrentSelIndex;
    }
}


bool CTvWallLogic::OnConfStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL32 bInConf = ComInterface->IsInConf();

	//结会后清空状态
	if ( !bInConf )
	{
        m_nCtrlIndex = -1;
		m_vctCnsInfoList.clear();
	}

	return true;
}

bool CTvWallLogic::onHduPlayInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	EmCnsHduPlayNackReason emHduPlayReason = *( EmCnsHduPlayNackReason * )lParam;
	CString strTip = _T("请求电视墙播放失败：");
	switch( emHduPlayReason )
	{
	case em_Cnshdu_play_success:
		strTip = _T("");
		break;
	case em_CnsHdu_Invalid_Index:
		strTip += _T("无效的位置索引");
		break;
	case em_CnsHdu_Invalid_ID:
		strTip +=_T("无效的ID");
		break;
	case em_CnsHdu_No_Reged:
		strTip += _T("电视墙未注册");
		break;
	case em_CnsHdu_Illegal:
		strTip += _T("无效的电视墙");
		break;
	case em_CnsAlias_Illegal:
		strTip += _T("无效的别名");
		break;
	case em_CnsMonitor_Fail:
		strTip += _T("上墙失败");
		break;
	case em_CnsHdu_PlayNack:
		strTip += _T("电视墙服务器拒绝");
		break;
	case em_CnsSame_Alias:
		strTip += _T("重名");
		break;
	case em_CnsSame_Info:
		//strTip += _T("相同的信息");   无需提示
        strTip = _T("");
		break;
	case em_Cnsunknown:
		strTip += _T("未知的错误");
		break;		
	default:
		break;
	}

	if ( strTip.GetLength()!= 0 )
	{
		ShowPopMsg(strTip);
	}
	else
	{
		//UpdateTvWall();
	}

	return true;
}


bool CTvWallLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_nSelectIndex = -1;
    m_nCtrlIndex = -1;
	m_vctCnsInfoList.clear();
	m_vctShowCnsList.clear();

	CTouchListUI* pTvWallList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("TvWallList") );

	if ( pTvWallList == NULL )
	{
		return false;
	}

	pTvWallList->RemoveAll();

	CTouchListUI* pConfCnsList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("ConfList") );
	if ( pConfCnsList == NULL )
	{
		return false;
	}
	pConfCnsList->RemoveAll();

    ICncCommonOp::ShowControl( false, m_pm, _T("PageSelConfList") );
    ICncCommonOp::ShowControl( false, m_pm, _T("PageVolCtrl") );

	clear();
	return true;
}

bool CTvWallLogic::OnCheckTvWallShortCut(TNotifyUI& msg)
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

	EM_ShortcutType em = emShortcutTVWall;
	NOTIFY_MSG( UI_CNC_SET_SHORTCUT_NTY, em, bIsSet );
	return true;
}

// bool CTvWallLogic::OnConfCnsItemClick(TNotifyUI& msg)
// {
// 	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("ConfList") );
// 	if (!pTileLayoutUI)
// 	{
// 		return false;
// 	}
// 	int wCurrentSelIndex = msg.wParam;
// 
// 	if (m_nSelIndex != wCurrentSelIndex)
// 	{
// 		m_vctSelSrceen.clear();
// 		CListContainerElementUI *pLastListContainerElement = (CListContainerElementUI *)pTileLayoutUI->GetItemAt(m_nSelIndex);
// 		if (pLastListContainerElement)
// 		{
// 			TSelViewInfo *pTSelViewInfo = &m_vctShowCnsList.at(m_nSelIndex);
// 
// 			if ((EmEpType_Ter == pTSelViewInfo->m_emType) && ( 3 == pTSelViewInfo->m_wSpeakerNum))
// 			{
// 				m_pm->DoCase(_T("caseHideScreenOption"), pLastListContainerElement);
// 				CCheckBoxUI* pCheckSrceen1 = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckSrceen1"), pLastListContainerElement);
// 				if (pCheckSrceen1)
// 				{
// 					pCheckSrceen1->SetCheckNoMsg(false);
// 				}
// 				CCheckBoxUI* pCheckSrceen2 = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckSrceen2"), pLastListContainerElement);
// 				if (pCheckSrceen2)
// 				{
// 					pCheckSrceen2->SetCheckNoMsg(false);
// 				}
// 				CCheckBoxUI* pCheckSrceen3 = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckSrceen3"), pLastListContainerElement);
// 				if (pCheckSrceen3)
// 				{
// 					pCheckSrceen3->SetCheckNoMsg(false);
// 				}
// 			}
// 			//if (EmEpType_Ter == pTSelViewInfo->m_emType)
// 			{
// 				CCheckBoxUI* pCheckBoxRoomSel = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("BtnRoomSel"), pLastListContainerElement);
// 				if (pCheckBoxRoomSel)
// 				{
// 					pCheckBoxRoomSel->SetCheckNoMsg(false);
// 				}
// 			}
// 			pTSelViewInfo = NULL;
// 		}
// 		//m_nSelIndex = wCurrentSelIndex;
// 	}
// 
//  	return true;
// }

void CTvWallLogic::SetCnsInTvw( )
{
	if ( m_nSelectIndex < 0 || m_nSelectIndex >= HDU_STYLE_MAX_NUM )
	{
		return;
	}

	CTouchListUI* pTvWallList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("TvWallList") );
	CListContainerElementUI *pContainer = NULL; 
	if ( m_nSelectIndex != -1 )
	{
		pContainer = dynamic_cast<CListContainerElementUI*>( pTvWallList->GetItemAt(m_nSelectIndex));
	}
	else
	{
		return ;
	}

	if( pContainer == NULL )
	{
		return ;
	}

	CButtonUI* pBtnVolCtrl = (CButtonUI*)ICncCommonOp::FindControl( m_pm, m_strBtnSetVoice.c_str(), pContainer);

	TTpHduPlanUnit tHduPlanunit = *(TTpHduPlanUnit*)pBtnVolCtrl->GetTag();

	if ( 0 == tHduPlanunit.m_byValid )
	{
		return;
	}

	CTouchListUI* pConfList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("ConfList") );
	if ( m_nSelIndex == -1 )
	{
		return;
	}

	CListContainerElementUI * pConfListContainer = dynamic_cast<CListContainerElementUI*>( pConfList->GetItemAt(m_nSelIndex));
    if ( pConfListContainer == NULL || pConfListContainer->GetTag() == NULL )
    {
        return;
    }
	TSelViewInfo tSelInfo = *(TSelViewInfo*)pConfListContainer->GetTag();

	TCnsInfo* pTCnsInfo = NULL;
	TCMSConf tConfInfo;
	ComInterface->IsInConf(&tConfInfo);

	if ( EmEpType_Ter == tSelInfo.m_emType )
	{
		pTCnsInfo = tConfInfo.GetCnsInfoByID(tSelInfo.m_wEpID);
		if ( NULL == pTCnsInfo )
		{
			return;
		}

		//与ums确认，放像室 type为EmEpType_Ter; 屏数为0. 提示:通道未建立 - 20150812 by xhx
		if ( pTCnsInfo->m_wSpeakerNum == 0 )
		{
			ShowPopMsg(_T("请求电视墙播放失败：通道未建立"));
			//暂时用 emReason==22 代表 操作失败:通道未建立
			//PTR_FCGIPRINTF( "{\"event\":\"ev_umcweb_HduOperate_res\",\"wIndex\":\"%d\",\"emReason\":\"%d\"}", wIndex, 22 );
			//PrtMsg( ev_umcweb_HduOperate_res, emEventTypeClientSend, "wIndex= %d, EmTpHduPlayNackReason= %d", wIndex, 22 );
			return;
		}
	}

	BOOL bSingleScreen = FALSE;
	if ( NULL == pTCnsInfo )
	{
		if ( EmEpType_Eqp == tSelInfo.m_emType )
		{
			bSingleScreen = TRUE;
            //多通道时不能选择画面合成
            if ( tHduPlanunit.m_byVmp )
            {
                ShowPopMsg( _T("请求电视墙播放失败:类型不匹配") );
                return;
            }
		}
		else
		{
			return;
		}
	}
	else
	{
		if ( pTCnsInfo->m_wSpeakerNum == 1 )
		{
			bSingleScreen = TRUE;
		}
	}

	if ( bSingleScreen )
	{
		TTpHduPlayReq  tTvwInfo;
		tTvwInfo.m_emType = tSelInfo.m_emType;
		tTvwInfo.m_wConfID =  tSelInfo.m_wConfID;
		tTvwInfo.m_wDstID = tSelInfo.m_wEpID;
		tTvwInfo.SetAlias( tSelInfo.m_achRoomName );

		//if ( EmEpType_Ter == tSelInfo.m_emType )
		//{
		//	tTvwInfo.SetAlias( pTCnsInfo->m_achRoomName );
		//}
		//else
		//{
		//	tTvwInfo.SetAlias( tSelInfo.m_achRoomName );
		//}

		tTvwInfo.m_wScreenNum = 1;	//与ums确认，单屏会场屏号为1 - 20150625 by xhx
		tTvwInfo.m_wIndex = m_nSelectIndex;
		if ( 1 == tHduPlanunit.m_byVmp )
		{
			tTvwInfo.m_bySubIndex = m_bySubIndex;
			tTvwInfo.m_bVmp = TRUE;
		}
		else
		{
			tTvwInfo.m_bySubIndex = 0;	//与ums确认，未开启多画面m_bySubIndex为0 - 20150723 by xhx
			tTvwInfo.m_bVmp = FALSE;
		}

		u16 re = ComInterface->PlayHduReq( tTvwInfo );
		if ( re != NO_ERROR )
		{
			//HANDLE_ERROR( re );
		}
	}
	else if ( pTCnsInfo->m_wSpeakerNum == 3 && tHduPlanunit.m_byVmp == 0 )
	{
		u8 byMaxCol = m_tHduPlanData[0].m_byCol;
		u8 byMaxRow = m_tHduPlanData[0].m_byRow;
		if ( byMaxCol == 0 || byMaxRow == 0 )
		{
			//PrtMsg( "\nSetCnsInTvw error: byMaxCol= %d, byMaxRow= %d", byMaxCol, byMaxRow );
			return;
		}

		// 		u8 byCurtCol = wIndex % byMaxCol;
		// 		u8 byCurtRow = wIndex / byMaxCol;

		//int anChannel[3] = { 0 };
		vector<int> vctChannel;

		u8 byFirstIndex = 0;
		u8 byLastIndex = 0;
		//大于等于3列的电视墙方案，只能进入当前行的电视墙中
		//小于3列的电视墙，支持自动换行
		// 		if ( byMaxCol >= 3 )
		// 		{
		// 			//找出这一行中配置过的电视墙
		// 			byFirstIndex = byCurtRow * byMaxCol;
		// 			byLastIndex = ( byCurtRow + 1 ) * byMaxCol - 1;
		// 		}
		// 		else
		//		{
		byFirstIndex = 0;
		byLastIndex = m_tHduPlanData[0].m_wNum - 1;
		//		}

		vector<u8> vctValidIndex;
		int nIndexInVct = 0; //wIndex在vctValidIndex中的索引
		int nValidSize = 0;  //vctValidIndex的size
		for ( u8 n = byFirstIndex; n <= byLastIndex; n++ )
		{
			u8 byCol = n/TP_STYLE_DATA_PACK_NUM;
			u8 byRow = n%TP_STYLE_DATA_PACK_NUM;
			TTpHduPlanUnit tHduPlanUnit = m_tHduPlanData[byCol].m_atUnits[byRow];
			if ( 1 == tHduPlanUnit.m_byValid && 0 == tHduPlanUnit.m_byVmp && 0 != tHduPlanUnit.m_byReged )
			{
				vctValidIndex.push_back( n );
				if ( n == m_nSelectIndex )
				{
					nIndexInVct = nValidSize;
				}
				nValidSize++;
			}
		}
		if ( nValidSize < m_vctSelSrceen.size() )
		{
			ShowPopMsg(_T("请求电视墙播放失败：电视墙资源不足"));
			return;
		}

		if ( nIndexInVct == (nValidSize - 1) )
		{
// 			anChannel[0] = vctValidIndex.at( nIndexInVct - 2 );
// 			anChannel[1] = vctValidIndex.at( nIndexInVct - 1 );
// 			anChannel[2] = m_nSelectIndex;

			for (int i = 0 , nIndex = nIndexInVct; i < m_vctSelSrceen.size() ; i++)
			{
				vctChannel.push_back(vctValidIndex.at( nIndex-- ));
			}
		}
		else if ( nIndexInVct == (nValidSize - 2) )
		{
// 			anChannel[0] = vctValidIndex.at( nIndexInVct - 1 );
// 			anChannel[1] = m_nSelectIndex;
// 			anChannel[2] = vctValidIndex.at( nIndexInVct + 1 );

			if (m_vctSelSrceen.size() <= 2)
			{
				for (int i = 0 , nIndex = nIndexInVct; i < m_vctSelSrceen.size() ; i++)
				{
					vctChannel.push_back(vctValidIndex.at( nIndex++ ));
				}
			}
			else
			{
				for (int i = 0 , nIndex = nIndexInVct-1; i < m_vctSelSrceen.size() ; i++)
				{
					vctChannel.push_back(vctValidIndex.at( nIndex++ ));
				}
			}

		}
		else
		{
// 			anChannel[0] = m_nSelectIndex;
// 			anChannel[1] = vctValidIndex.at( nIndexInVct + 1 );
// 			anChannel[2] = vctValidIndex.at( nIndexInVct + 2 );

			for (int i = 0 , nIndex = nIndexInVct; i < m_vctSelSrceen.size() ; i++)
			{
				vctChannel.push_back(vctValidIndex.at( nIndex++ ));
			}
		}

		for ( int i = 0; i < m_vctSelSrceen.size(); i++ )
		{
			int nChannel = vctChannel.at(i)/*anChannel[i]*/;

			TTpHduPlayReq tTvwInfo;
			tTvwInfo.m_emType = tSelInfo.m_emType;
			tTvwInfo.m_wConfID = tSelInfo.m_wConfID;
			tTvwInfo.m_wDstID = tSelInfo.m_wEpID;
			tTvwInfo.SetAlias( tSelInfo.m_achRoomName );
			tTvwInfo.m_wScreenNum = m_vctSelSrceen.at(i)/*i*/;
			tTvwInfo.m_wIndex = nChannel;
			tTvwInfo.m_bySubIndex = 0;	//与ums确认，未开启多画面m_bySubIndex为0 - 20150723 by xhx
			tTvwInfo.m_bVmp = FALSE;

			u16 re = ComInterface->PlayHduReq( tTvwInfo );
			if ( re != NO_ERROR )
			{
				//HANDLE_ERROR( re );
			}
		}
	}
	else if ( pTCnsInfo->m_wSpeakerNum == 3 && tHduPlanunit.m_byVmp == 1 )
	{
		//int anSubChannel[3] = { 4 };	//HDU_MAX_VMP_SUBCHAN
		vector<int> vctSubChannel;
		if ( m_bySubIndex == 0 || m_bySubIndex == 1 )
		{
// 			anSubChannel[0] = 0;
// 			anSubChannel[1] = 1;
// 			anSubChannel[2] = 2;

			for (int i = 0, nIndex = m_bySubIndex ; i < m_vctSelSrceen.size() ; i++)
			{
				vctSubChannel.push_back(nIndex++);
			}
		} 
		else if (/* m_bySubIndex == 1 ||*/ m_bySubIndex == 2 /*|| m_bySubIndex == 3*/ )
		{
// 			anSubChannel[0] = 1;
// 			anSubChannel[1] = 2;
// 			anSubChannel[2] = 3;

			if (m_vctSelSrceen.size() <= 2)
			{
				for (int i = 0 , nIndex = m_bySubIndex; i < m_vctSelSrceen.size() ; i++)
				{
					vctSubChannel.push_back( nIndex++ );
				}
			}
			else
			{
				for (int i = 0 , nIndex = m_bySubIndex-1; i < m_vctSelSrceen.size() ; i++)
				{
					vctSubChannel.push_back( nIndex++ );
				}
			}
		}
		else if ( m_bySubIndex == 3 )
		{
			for (int i = 0, nIndex = m_bySubIndex ; i < m_vctSelSrceen.size() ; i++)
			{
				vctSubChannel.push_back(nIndex--);
			}
		}

		for ( int i = 0; i < m_vctSelSrceen.size(); i++ )
		{
			int nChannel = vctSubChannel.at(i)/*anSubChannel[i]*/;

			TTpHduPlayReq tTvwInfo;
			tTvwInfo.m_emType = tSelInfo.m_emType;
			tTvwInfo.m_wConfID = tSelInfo.m_wConfID;
			tTvwInfo.m_wDstID = tSelInfo.m_wEpID;
			tTvwInfo.SetAlias( pTCnsInfo->m_achRoomName );
			tTvwInfo.m_wScreenNum = m_vctSelSrceen.at(i)/*i*/;
			tTvwInfo.m_wIndex = m_nSelectIndex;
			tTvwInfo.m_bySubIndex = nChannel;
			tTvwInfo.m_bVmp = TRUE;

			u16 re = ComInterface->PlayHduReq( tTvwInfo );
			if ( re != NO_ERROR )
			{
				//HANDLE_ERROR( re );
			}
		}
	}
}

u8 CTvWallLogic::GetStatus( CControlUI *pControl )
{
	if ( pControl != NULL )
	{
		return pControl->GetTag();
	}
	return -1;
}

void CTvWallLogic::SetStatus( CControlUI *pControl, u8 byTag )
{
	if ( pControl != NULL )
	{
		pControl->SetTag((UINT_PTR)byTag);
	}
	return ;
}