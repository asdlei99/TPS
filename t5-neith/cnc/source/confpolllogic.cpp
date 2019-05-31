#include "StdAfx.h"
#include "confpolllogic.h"
#include "audmixlogic.h"
#include "confmsglogic.h"

template<> CConfPollLogic* Singleton<CConfPollLogic>::ms_pSingleton  = NULL;
APP_BEGIN_MSG_MAP(CConfPollLogic, CNotifyUIImpl)
	//会议轮询控制
	MSG_CLICK(_T("BtnCheckConfPoll"), OnBtnCheckConfPoll)
	MSG_CLICK(_T("BtnCheckPause"), OnBtnCheckPause)

	MSG_SELECTCHANGE(_T("CheckConfPollShortCut"), OnCheckConfPollShortCut)

	MSG_ITEMSELECTD(_T("PollList"), OnPollListClick)

	MSG_CLICK(_T("BtnPSelOK"), OnBtnPSelRoomOK)
	MSG_CLICK(_T("BtnPSelAll"), OnBtnPSelAll)
	MSG_CLICK(_T("BtnPSelCancel"), OnBtnPSelCancel)
	MSG_SELECTCHANGE(_T("BtnConfCnsSel"), OnCheckPConfItem)
	
	MSG_EDITCHANGE(_T("EdtPSearch"), OnSearchEditChange)	

	MSG_CLICK(_T("BtnAddPoll"), OnBtnAddPoll)
	MSG_CLICK(_T("BtnTop"), OnBtnPollTop)
	MSG_CLICK(_T("BtnUp"), OnBtnPollUp)
	MSG_CLICK(_T("BtnDown"), OnBtnPollDown)
	MSG_CLICK(_T("BtnBottom"), OnBtnPollBottom)
	MSG_CLICK(_T("BtnDel"), OnBtnPollDel)

	USER_MSG(UI_CNS_POLL_STATE_NOTIFY,OnPollStateNty)
	USER_MSG(UI_CNSPOLLPAUSE_IND,OnPollPauseInd)
	USER_MSG(UI_CNSPOLLLIST_IND,OnPollListInd)
	USER_MSG(UI_CNSPOLLLIST_NTY,OnPollListNty)
	USER_MSG(UI_DISCONNECTED_CLEARDATA, OnDisconnect)
	USER_MSG( UI_UMS_REFRESH_CONFCNS_LIST, OnRefreshCnsLstNotify )
	USER_MSG(UI_CNS_CONFSTATE_NOTIFY,OnConfStateNotify)
	USER_MSG(UI_CNS_START_POLL_RSP,OnStartPollRsp)
	
	USER_MSG(UI_CNC_SHORTCUT_POLL,OnShortCutPoll)
	
APP_END_MSG_MAP()

CConfPollLogic::CConfPollLogic(void) 
{
	m_dwSelPollItemId = -1;
	m_bIsSelAll = false;
	m_nPollFlagInd = 0;
	m_bIsFirstPollListInd = true;
	m_bIsFixed = false;
	m_bIsSearch = false;

    m_bIsSetPause = false;
}

CConfPollLogic::~CConfPollLogic(void)
{
}

bool CConfPollLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_dwSelPollItemId = -1;
	m_bIsSelAll = false;
	m_nPollFlagInd = 0;
	m_bIsFirstPollListInd = true;
	m_bIsFixed = false;

	m_bIsSearch = false;
	ICncCommonOp::SetControlText(_T(""), m_pm,  _T("EdtPSearch"));
	m_vctSearchCnsList.clear();

	m_vctCurrentCnsList.clear();
	m_vctSelConf.clear();
	m_vctPollList.clear();
	m_vctFixedPollList.clear();
	UpdateCnsList();
	UpdatePollList();

	return true;
}

bool CConfPollLogic::OnBtnCheckPause( TNotifyUI& msg )
{
	BOOL32 bPause = FALSE;
	TTpPollStat tTpPollStat = ComInterface->GetPollState();	
	if (tTpPollStat.m_emStat == EmPollStat_Suspend )
	{
		bPause = TRUE;
	}
    m_bIsSetPause = !bPause;
	u16 wRet = ComInterface->PollPauseCmd(!bPause);
	if (wRet != NO_ERROR)
	{
		ShowPopMsg(_T("暂停控制失败"));
	}

	return true;
}

//会议轮询
bool CConfPollLogic::OnBtnCheckConfPoll( TNotifyUI& msg )
{
	BOOL32 bStart = FALSE;
	TTpPollStat tTpPollStat = ComInterface->GetPollState();	
	if (tTpPollStat.m_emStat == EmPollStat_Start || tTpPollStat.m_emStat == EmPollStat_Suspend)
	{
		bStart = TRUE;
	}

	if (!bStart)//当前是关闭状态，要开启，先更新列表，列表传完收到ind后，直接发送开启消息
	{
		UpdateCnsPollList(0);
	}
	else//当前是开启状态，要关闭，直接发送关闭状态，列表不发送
	{
		u16 wRet = ComInterface->StartPoll(FALSE);
		if (wRet != NO_ERROR)
		{
			showMessageBox(_T("保存会议轮询设置请求发送失败"));
			return false;
		}
	}

	return true;

}

bool CConfPollLogic::OnCheckConfPollShortCut( TNotifyUI& msg )
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

	EM_ShortcutType em = emShortcutCofPoll;
	NOTIFY_MSG( UI_CNC_SET_SHORTCUT_NTY, em, bIsSet );
	return true;
}

bool CConfPollLogic::OnPollStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL32 bStart = FALSE;
	TTpPollStat tTpPollStat = ComInterface->GetPollState();	
	if (tTpPollStat.m_emStat == EmPollStat_Start || tTpPollStat.m_emStat == EmPollStat_Suspend)
	{
		ICncCommonOp::ShowControl(true,m_pm,_T("pauselayout"));
		CButtonUI *pBtnCheckPause = (CButtonUI*)ICncCommonOp::FindControl( m_pm, _T("BtnCheckPause") );
		bStart = TRUE;
		if (tTpPollStat.m_emStat == EmPollStat_Start)
		{
			
			pBtnCheckPause->SetAttribute(_T("pushedimage"),_T("res/confctrl/confpoll/pausepoll_select.png"));
			pBtnCheckPause->SetAttribute(_T("normalimage"),_T("res/confctrl/confpoll/pausepoll.png"));
		}
		else
		{

			pBtnCheckPause->SetAttribute(_T("pushedimage"),_T("res/confctrl/confpoll/restartpoll_select.png"));
			pBtnCheckPause->SetAttribute(_T("normalimage"),_T("res/confctrl/confpoll/restartpoll_select.png"));	
		}
	}

	CButtonUI *pBtnCheckConfPoll = (CButtonUI*)ICncCommonOp::FindControl( m_pm, _T("BtnCheckConfPoll") );
	if (pBtnCheckConfPoll)
	{
		if (bStart)
		{
			
			pBtnCheckConfPoll->SetAttribute(_T("pushedimage"),_T("res/confctrl/confpoll/stoppoll_select.png"));
			pBtnCheckConfPoll->SetAttribute(_T("normalimage"),_T("res/confctrl/confpoll/stoppoll.png"));
		}
		else
		{
			ICncCommonOp::ShowControl(false,m_pm,_T("pauselayout"));
			
			pBtnCheckConfPoll->SetAttribute(_T("pushedimage"),_T("res/confctrl/confpoll/beginpoll_select.png"));
			pBtnCheckConfPoll->SetAttribute(_T("normalimage"),_T("res/confctrl/confpoll/beginpoll.png"));
		}

	}

	if (bStart)//开启
	{
		//禁用调整按钮 更新列表
		ICncCommonOp::EnableControl( false, m_pm,  _T("BtnAddPoll") );
		ICncCommonOp::EnableControl( true, m_pm,  _T("BtnCheckPause") );
		EnablePollBtn(false);
		ICncCommonOp::EnableControl( false, m_pm,  _T("edtPollInterval") );

		ICncCommonOp::ShowControl( false, m_pm, _T("PagePollSelConfList") );

		m_bIsFixed = false;//开启后，fixlist和list一致
		m_vctFixedPollList = m_vctPollList;
	}
	else//关闭
	{
		//开启调整按钮
		ICncCommonOp::EnableControl( true, m_pm,  _T("BtnAddPoll") );
		ICncCommonOp::EnableControl( false, m_pm,  _T("BtnCheckPause") );
		if (m_dwSelPollItemId != -1)
		{
			EnablePollBtn(true);
		}
		ICncCommonOp::EnableControl( true, m_pm,  _T("edtPollInterval") );
	}

	return S_OK;
}

bool CConfPollLogic::OnPollPauseInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	EmTPPollResult em = (EmTPPollResult)wParam;

	CButtonUI *pBtnCheckPause = (CButtonUI*)ICncCommonOp::FindControl( m_pm, _T("BtnCheckPause") );
	if (!pBtnCheckPause)
	{
		return false;
	}

	if (em == emPollSucceed)
	{
		return true;
	}

	CString str = _T("");
    if (m_bIsSetPause)
    {
        str = _T("暂停轮询失败");
    }
    else
    {
        str = _T("恢复轮询失败");
    }
	switch (em)
	{
	case emPollInvalidEp:
		{
			str = str + _T(":无有效轮询会场");
		}
		break; 
	case emPollResFull://资源不足：带宽、适配
		{
			str = str + _T(":资源不足");
		}
		break;
	case emPollResFull_Bw:
		{
			str = str + _T(":带宽资源不足");
		}
		break; 
	case emPollResFull_Bas:
		{
			str = str + _T(":适配资源不足");
		}
		break; 
	case emPollNoChair:
		{
			str = str + _T(":无主席权限");
		}
		break;
	case emPollChairNoLine:
		{
			str = str + _T(":主席不在线");
		}
		break;
	case emPollServerBusy:
		{
			str = str + _T(":服务器忙");
		}
		break;
	case emPollFailUnKown:
		{
			str = str + _T(":未知错误");
		}
	}

	ShowPopMsg(str);

	TTpPollStat tTpPollStat = ComInterface->GetPollState();	
	if (tTpPollStat.m_emStat == EmPollStat_Start)
	{
		pBtnCheckPause->SetAttribute(_T("pushedimage"),_T("res/confctrl/confpoll/pausepoll_select.png"));
		pBtnCheckPause->SetAttribute(_T("normalimage"),_T("res/confctrl/confpoll/pausepoll.png"));
	}
	else
	{
		pBtnCheckPause->SetAttribute(_T("pushedimage"),_T("res/confctrl/confpoll/restartpoll_select.png"));
		pBtnCheckPause->SetAttribute(_T("normalimage"),_T("res/confctrl/confpoll/restartpoll.png"));
	}


	return true;
}

bool CConfPollLogic::OnPollListNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	ComInterface->GetPollList( m_vctPollList );
	UpdatePollList(m_vctPollList);
	if (!m_bIsFixed)
	{
		m_vctFixedPollList = m_vctPollList;
	}
	m_dwSelPollItemId = -1;

	//设置界面轮询时间
	CString str = _T("");
	str.Format(_T("%d"), wParam);
	ICncCommonOp::SetControlText(str, m_pm, _T("edtPollInterval"));

	return true;
}

bool CConfPollLogic::OnPollListInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TTpPollListInd tTpPollListInd = *(TTpPollListInd*)lParam;
	if (m_bIsFirstPollListInd)
	{
		m_bIsFirstPollListInd = false;
		m_nPollFlagInd = tTpPollListInd.m_nFlag;
	}

	if (tTpPollListInd.m_wRet != TP_RET_OK)
	{
		ShowPopMsg(_T("列表更新失败,请稍后再试"));
		m_vctFixedPollList = m_vctPollList;
		m_bIsFixed = false;
		UpdatePollList();
		m_bIsFirstPollListInd = true;
		m_nPollFlagInd = 0;
		return false;
	}
	else
	{
		if (tTpPollListInd.m_wCurRcvNum == m_vctFixedPollList.size())
		{
			m_vctFixedPollList = m_vctPollList;
			m_bIsFixed = false;
			m_bIsFirstPollListInd = true;
			m_nPollFlagInd = 0;

			//发送完毕再发送开启消息
			TCMSConf tConf;
			BOOL32 bInConf = ComInterface->IsInConf( &tConf );
			if (!bInConf)
			{
				ShowMessageBox(_T("不在会议中，不可进行此操作"),FALSE);
				return false;
			}

			u16 wRet = ComInterface->StartPoll(TRUE);
			if (wRet != NO_ERROR)
			{
				ShowPopMsg(_T("保存会议轮询设置请求发送失败"));
				return false;
			}

		}
		else
		{
			if (m_dwSelPollItemId != -1)
			{
				m_dwSelPollItemId = -1;
			}
			m_bIsFixed = false;

			if (tTpPollListInd.m_wCurRcvNum >= m_vctFixedPollList.size())
			{
				return false;
			}
			UpdateCnsPollList(tTpPollListInd.m_wCurRcvNum);

		}
	}
	
	return true;
}

void CConfPollLogic::UpdatePollList(vector<u16>  vctPollList)
{
	TCMSConf tCMSConf;
	BOOL32 bIsInconf = ComInterface->IsInConf(&tCMSConf); 
	CListUI* pPollList = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("PollList"));
	if ( pPollList == NULL )
	{
		return ;
	}

	TCnsInfo* ptCnsInfo = NULL;
	CString strRoomName = _T("");
	CString strNum = _T("");
	pPollList->RemoveAll();
	
	if (!bIsInconf)
	{
		return;
	}

	for ( u16 i = 0; i < vctPollList.size(); i++ )
	{
		ptCnsInfo =  tCMSConf.GetCnsInfoByID(vctPollList.at(i));
		if (ptCnsInfo == NULL)
		{
			continue;
		}

		CListContainerElementUI *pListContainer = 
			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("PolListItem"));
		strRoomName = ptCnsInfo->m_achRoomName;
 		strNum.Format(_T("%d"),i+1);
		ICncCommonOp::SetControlText( strRoomName, m_pm, _T("lbPollName"), pListContainer );
		ICncCommonOp::SetControlText( strNum, m_pm,  _T("lbPollNum"), pListContainer );
		if (!ptCnsInfo->m_bOnline)
		{
			pListContainer->SetAttribute(_T("bkcolor"), _T("#FF40546C"));
		}
		pPollList->Add(pListContainer);
	}

	EnablePollBtn(false);
}

void CConfPollLogic::UpdatePollList()
{
	UpdatePollList(m_vctPollList);
	m_dwSelPollItemId = -1;
}

void CConfPollLogic::UpdatePollList( EMPollItemMoveMode emMode )
{
	CListUI* pPollList = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("PollList"));
	if ( pPollList == NULL )
	{
		return ;
	}

	if (emMode == emMoveTop)
	{
		m_dwSelPollItemId = 0;
		UpdatePollList(m_vctFixedPollList);
	}
	else if ( emMode == emMoveBottom)
	{
		m_dwSelPollItemId = m_vctFixedPollList.size() - 1;
		UpdatePollList(m_vctFixedPollList);
	}
	else
	{
		CListContainerElementUI *pListContainerSel = (CListContainerElementUI*)pPollList->GetItemAt(m_dwSelPollItemId);
		if (pListContainerSel == NULL)
		{
			return;
		}

		TCMSConf tCMSConf;
		BOOL32 bIsInconf = ComInterface->IsInConf(&tCMSConf); 
		TCnsInfo* ptCnsInfo = NULL;
		ptCnsInfo =  tCMSConf.GetCnsInfoByID(m_vctFixedPollList.at(m_dwSelPollItemId));
		if (ptCnsInfo != NULL)
		{
			if (ptCnsInfo->m_bOnline)
			{
				pListContainerSel->SetAttribute(_T("bkcolor"), _T(""));
			}
			else
			{
				pListContainerSel->SetAttribute(_T("bkcolor"), _T("#FF40546C"));
			}
		}

		if (emMode == emMoveUp)
		{
			m_dwSelPollItemId = m_dwSelPollItemId - 1;
		}
		else if (emMode == emMoveDown)
		{
			m_dwSelPollItemId = m_dwSelPollItemId + 1;
		}

		CListContainerElementUI *pListContainerOri = (CListContainerElementUI*)pPollList->GetItemAt(m_dwSelPollItemId);
		if (pListContainerOri == NULL)
		{
			return;
		}

		ptCnsInfo =  tCMSConf.GetCnsInfoByID(m_vctFixedPollList.at(m_dwSelPollItemId));
		if (ptCnsInfo != NULL)
		{
			if (ptCnsInfo->m_bOnline)
			{
				pListContainerOri->SetAttribute(_T("bkcolor"), _T(""));
			}
			else
			{
				pListContainerOri->SetAttribute(_T("bkcolor"), _T("#FF40546C"));
			}
		}

		String strSel = ICncCommonOp::GetControlText(m_pm, _T("lbPollName"), pListContainerSel );
		String strOri = ICncCommonOp::GetControlText(m_pm, _T("lbPollName"), pListContainerOri );

		ICncCommonOp::SetControlText( strOri.c_str(), m_pm, _T("lbPollName"), pListContainerSel );
		ICncCommonOp::SetControlText( strSel.c_str(), m_pm,  _T("lbPollName"), pListContainerOri );
	}

	pPollList->SelectItem(m_dwSelPollItemId);

}

bool CConfPollLogic::OnPollListClick( TNotifyUI& msg )
{
	m_dwSelPollItemId = msg.wParam;

	BOOL32 bStart = FALSE;
	TTpPollStat tTpPollStat = ComInterface->GetPollState();	
	if (tTpPollStat.m_emStat == EmPollStat_Suspend || tTpPollStat.m_emStat == EmPollStat_Start )
	{
		bStart = TRUE;
	}

	EnablePollBtn(!bStart);//轮询未开启才可以调整
	return true;
}


void CConfPollLogic::EnablePollBtn( bool bIsEnable )
{
	//ICncCommonOp::EnableControl( bIsEnable, m_pm,  _T("BtnAddPoll") );
	ICncCommonOp::EnableControl( bIsEnable, m_pm,  _T("BtnTop") );
	ICncCommonOp::EnableControl( bIsEnable, m_pm,  _T("BtnUp") );
	ICncCommonOp::EnableControl( bIsEnable, m_pm,  _T("BtnDown") );
	ICncCommonOp::EnableControl( bIsEnable, m_pm,  _T("BtnBottom") );
	ICncCommonOp::EnableControl( bIsEnable, m_pm,  _T("BtnDel") );
}

bool CConfPollLogic::OnBtnAddPoll( TNotifyUI& msg )
{
	bool bHandle  = false;
	OnRefreshCnsLstNotify(NULL,NULL,bHandle);
	m_bIsSelAll = false;
	m_vctSelConf.clear();
	ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnPSelAll"));
	m_bIsSearch = false;
	m_vctSearchCnsList.clear();
	ICncCommonOp::SetControlText(_T(""), m_pm,  _T("EdtPSearch"));
	ICncCommonOp::ShowControl( true, m_pm, _T("PagePollSelConfList") );
	return true;
}

bool CConfPollLogic::OnBtnPollTop( TNotifyUI& msg )
{
	if(m_dwSelPollItemId == -1 || m_vctFixedPollList.size() <= 1 ||  m_dwSelPollItemId == 0)
	{
		return false;
	}

	if (!m_bIsFixed)
	{
		m_bIsFixed = true;
	}
	
	u16 wId = m_vctFixedPollList.at(m_dwSelPollItemId);
	m_vctFixedPollList.erase(m_vctFixedPollList.begin() + m_dwSelPollItemId);
	m_vctFixedPollList.insert(m_vctFixedPollList.begin(),wId);

	UpdatePollList(emMoveTop);
	return true;
}

bool CConfPollLogic::OnBtnPollUp( TNotifyUI& msg )
{
	if(m_dwSelPollItemId == -1 || m_vctFixedPollList.size() <= 1 || m_dwSelPollItemId == 0)
	{
		return false;
	}

	if (!m_bIsFixed)
	{
		m_bIsFixed = true;
	}

	u16 wId = m_vctFixedPollList.at(m_dwSelPollItemId);
	m_vctFixedPollList.erase(m_vctFixedPollList.begin() + m_dwSelPollItemId);
	m_vctFixedPollList.insert(m_vctFixedPollList.begin() + m_dwSelPollItemId - 1,wId);

	UpdatePollList(emMoveUp);

	return true;
}

bool CConfPollLogic::OnBtnPollDown( TNotifyUI& msg )
{
	if(m_dwSelPollItemId == -1 || m_vctFixedPollList.size() <= 1 || m_dwSelPollItemId == m_vctFixedPollList.size()-1)
	{
		return false;
	}

	if (!m_bIsFixed)
	{
		m_bIsFixed = true;
	}

	u16 wId = m_vctFixedPollList.at(m_dwSelPollItemId);
	m_vctFixedPollList.erase(m_vctFixedPollList.begin() + m_dwSelPollItemId);
	m_vctFixedPollList.insert(m_vctFixedPollList.begin() + m_dwSelPollItemId + 1,wId);

	UpdatePollList(emMoveDown);
	return true;
}

bool CConfPollLogic::OnBtnPollBottom( TNotifyUI& msg )
{
	if(m_dwSelPollItemId == -1 || m_vctFixedPollList.size() <= 1 ||  m_dwSelPollItemId == m_vctFixedPollList.size()-1)
	{
		return false;
	}

	if (!m_bIsFixed)
	{
		m_bIsFixed = true;
	}

	u16 wId = m_vctFixedPollList.at(m_dwSelPollItemId);
	m_vctFixedPollList.erase(m_vctFixedPollList.begin() + m_dwSelPollItemId);
	m_vctFixedPollList.insert(m_vctFixedPollList.end(),wId);

	UpdatePollList(emMoveBottom);
	return true;
}

bool CConfPollLogic::OnBtnPollDel( TNotifyUI& msg )
{
	if(m_dwSelPollItemId == -1)
	{
		return false;
	}

	int ret = ShowMessageBox(_T("是否确认删除"),true);
	if ( IDOK != ret )
	{
		return true;
	}
	if (!m_bIsFixed)
	{
		m_bIsFixed = true;
	}
	m_vctFixedPollList.erase(m_vctFixedPollList.begin() + m_dwSelPollItemId);
	UpdatePollList(m_vctFixedPollList);
	m_dwSelPollItemId = -1;
	return true;
}

bool CConfPollLogic::OnBtnPSelCancel( TNotifyUI& msg )
{
	ICncCommonOp::ShowControl( false, m_pm, _T("PagePollSelConfList") );
	m_bIsSelAll = false;
	ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnPSelAll"));
	m_vctSelConf.clear();

	m_bIsSearch = false;
	m_vctSearchCnsList.clear();
	ICncCommonOp::SetControlText(_T(""), m_pm,  _T("EdtPSearch"));
	return true;
}

bool CConfPollLogic::OnCheckPConfItem( TNotifyUI& msg )
{
	if (msg.pSender->GetParent()->GetParent()->GetName() != _T("PollCnsConfList"))
	{
		return false;
	}
	
	if ( CListContainerElementUI *pItem = dynamic_cast<CListContainerElementUI*>(msg.pSender->GetParent()) )
	{
		int nIndex = pItem->GetIndex();
		TCnsInfo tCnsInfo;
		if (m_bIsSearch)
		{
			tCnsInfo = m_vctSearchCnsList.at(nIndex);
		}
		else
		{
			tCnsInfo = m_vctCurrentCnsList.at(nIndex);
		}
		
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

	CString str(ICncCommonOp::GetControlText(m_pm,_T("BtnPSelAll")).c_str());
	if (m_bIsSearch)
	{
		if (m_vctSelConf.size() == m_vctSearchCnsList.size() && str != _T("取消全选"))
		{
			m_bIsSelAll = true;
			ICncCommonOp::SetControlText(_T("取消全选"),m_pm,_T("BtnPSelAll"));
		}
		if (m_vctSelConf.size() != m_vctSearchCnsList.size() && str != _T("全 选"))
		{
			m_bIsSelAll = false;
			ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnPSelAll"));
		}
	}
	else
	{
		if (m_vctSelConf.size() == m_vctCurrentCnsList.size() && str != _T("取消全选"))
		{
			m_bIsSelAll = true;
			ICncCommonOp::SetControlText(_T("取消全选"),m_pm,_T("BtnPSelAll"));
		}
		if (m_vctSelConf.size() != m_vctCurrentCnsList.size() && str != _T("全 选"))
		{
			m_bIsSelAll = false;
			ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnPSelAll"));
		}
	}

	return true;
}

bool CConfPollLogic::OnBtnPSelAll( TNotifyUI& msg )
{
	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("PollCnsConfList") );
	if ( pTileLayoutUI == NULL )
	{
		return false;
	}
	m_bIsSelAll = !m_bIsSelAll;
	if ( m_bIsSelAll )
	{
		ICncCommonOp::SetControlText(_T("取消全选"),m_pm,_T("BtnPSelAll"));
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
		ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnPSelAll"));
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

void CConfPollLogic::UpdateCnsList()
{
	m_vctSelConf.clear();
	CTouchListUI* pConfCnsList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("PollCnsConfList") );
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
		//pListContainer->SetTag( (UINT_PTR)&m_vctCurrentCnsList.at(i) );

		pConfCnsList->Add(pListContainer);
	}

	m_bIsSelAll = false;
	ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnPSelAll"));
}

bool CConfPollLogic::OnRefreshCnsLstNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TCMSConf tConfInfo ;
	bool bIn = ComInterface->IsInConf( &tConfInfo );
	
	TTPCnsInfo tlocalCnsInfo;
	ComInterface->GetLocalCnsInfo( tlocalCnsInfo );
	TCnsInfo *tCnsInfoLocal = tConfInfo.GetLocalCnsInfo( tlocalCnsInfo );
	if (tCnsInfoLocal == NULL)
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
			if (tCnsInfo.m_wEpID == tCnsInfoLocal->m_wEpID)//不轮询自己
			{
				continue;
			}
			m_vctCurrentCnsList.push_back(tConfInfo.m_vctCnsList.at(i));
		}
	}

	if (m_bIsSearch)
	{
		m_bIsSearch = false;
		m_vctSearchCnsList.clear();
		ICncCommonOp::SetControlText(_T(""), m_pm,  _T("EdtPSearch"));
	}

	UpdateCnsList();	
	UpdatePollList(m_vctFixedPollList);
	return true;
}

bool CConfPollLogic::OnBtnPSelRoomOK( TNotifyUI& msg )
{
	if (m_vctSelConf.size() == 0)
	{
		ShowMessageBox(_T("请选择要添加的会场"));
		return false;
	}

	if (!m_bIsFixed)
	{
		m_bIsFixed = true;
	}

	for (int i=0; i<m_vctSelConf.size(); i++)//不重复添加
	{
		bool bInclude = false;
		for (int j=0; j<m_vctFixedPollList.size(); j++)
		{
			if (m_vctSelConf.at(i).m_wEpID == m_vctFixedPollList.at(j))
			{
				bInclude = true;
				break;
			}
		}

		if (!bInclude)
		{
			m_vctFixedPollList.push_back(m_vctSelConf.at(i).m_wEpID);
		}
	}

	UpdatePollList(m_vctFixedPollList);
	ICncCommonOp::ShowControl( false, m_pm, _T("PagePollSelConfList") );
	CListUI* pPollList = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("PollList"));
	if (pPollList)
	{
		pPollList->SelectItem(m_vctFixedPollList.size() -1);
	}

	m_bIsSearch = false;
	m_vctSearchCnsList.clear();
	ICncCommonOp::SetControlText(_T(""), m_pm,  _T("EdtPSearch"));
	return true;
}

bool CConfPollLogic::UpdateCnsPollList(u16 wPollLstPos)
{
	if (m_vctFixedPollList.size() == 0)
	{
		ShowMessageBox(_T("请先添加会议轮询列表"));
		return false;
	}

	TCMSConf tConf;
	BOOL32 bInConf = ComInterface->IsInConf( &tConf );
	if ( !bInConf )
	{
		return false;
	}

	TTpPollListNtfy tTpPollListNtfy;
	tTpPollListNtfy.m_wConfID = tConf.m_wConfID;

	String strCaption = ICncCommonOp::GetControlText(m_pm, _T("edtPollInterval"));
	u16 wVal = _wtoi( strCaption.c_str() );
	if ( wVal < 5 || wVal > 7200 )
	{
		ShowMessageBox(_T("轮询间隔为 5 ~ 7200 间的整数"));
		return false;
	}

	tTpPollListNtfy.m_wInterval = wVal;
	tTpPollListNtfy.m_nFlag = m_nPollFlagInd;

	if (m_vctFixedPollList.size() - wPollLstPos > TP_CONF_MAX_TURNNUM)
	{
		tTpPollListNtfy.m_wCurNum = TP_CONF_MAX_TURNNUM;
	}
	else
	{
		tTpPollListNtfy.m_wCurNum = m_vctFixedPollList.size() - wPollLstPos;
	}

	for (int i=0; i<tTpPollListNtfy.m_wCurNum; i++)
	{
		tTpPollListNtfy.m_awList[i] = m_vctFixedPollList.at(wPollLstPos+i);
	}

	tTpPollListNtfy.m_wTotalNum = m_vctFixedPollList.size();

	ComInterface->PollListUpdateCmd( tTpPollListNtfy );
	
	return true;
}

bool CConfPollLogic::OnSearchEditChange( TNotifyUI& msg )
{
	CEditUI* pEditSearch = (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("EdtPSearch") );
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
		ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnPSelAll"));
		CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("PollCnsConfList") );
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
				//pListContainer->SetTag( (UINT_PTR)&m_vctCurrentCnsList.at(i) );

				pTileLayoutUI->Add(pListContainer);

			}
		}
	}
	return false;
}

bool CConfPollLogic::OnConfStateNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bInConf = ComInterface->IsInConf();
	if ( !bInConf )
	{
		m_dwSelPollItemId = -1;
		m_bIsSelAll = false;
		m_nPollFlagInd = 0;
		m_bIsFirstPollListInd = true;
		m_bIsFixed = false;

		m_bIsSearch = false;
		ICncCommonOp::SetControlText(_T(""), m_pm,  _T("EdtPSearch"));
		m_vctSearchCnsList.clear();

		m_vctCurrentCnsList.clear();
		m_vctSelConf.clear();
		m_vctPollList.clear();
		m_vctFixedPollList.clear();
		UpdatePollList();
	}
	return false;
}

bool CConfPollLogic::OnStartPollRsp( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	EmTPPollResult em = (EmTPPollResult)lParam;
	bool bIsPoll = (BOOL)wParam;
	CString strError = _T("");
	if (bIsPoll)
	{
		strError = _T("开启轮询失败");
	}
	else
	{
		strError = _T("关闭轮询失败");
	}

	switch (em)
	{
	case emPollInvalidEp:
		{
			strError = strError + _T(":无有效轮询会场");
		}
		break; 
	case emPollResFull://资源不足：带宽、适配
		{
			strError = strError + _T(":资源不足");
		}
		break;
	case emPollResFull_Bw:
		{
			strError = strError + _T(":带宽资源不足");
		}
		break; 
	case emPollResFull_Bas:
		{
			strError = strError + _T(":适配资源不足");
		}
		break; 
	case emPollNoChair:
		{
			strError = strError + _T(":无主席权限");
		}
		break;
	case emPollChairNoLine:
		{
			strError = strError + _T(":主席不在线");
		}
		break;
	case emPollServerBusy:
		{
			strError = strError + _T(":服务器忙");
		}
		break;
	case emPollFailUnKown:
		{
			strError = strError + _T(":未知错误");
		}
	}
	if (em != emPollSucceed)
	{
		ShowPopMsg(strError);
	}

	return true;

}

bool CConfPollLogic::OnShortCutPoll( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TNotifyUI msg;
	OnBtnCheckConfPoll( msg );

	return true;
}
