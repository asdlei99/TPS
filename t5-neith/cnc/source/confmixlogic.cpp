#include "StdAfx.h"
#include "confmixlogic.h"
#include "confmsglogic.h"
#include "mainmenulogic.h"

template<> CConfMixLogic* Singleton<CConfMixLogic>::ms_pSingleton  = NULL;
APP_BEGIN_MSG_MAP(CConfMixLogic, CNotifyUIImpl)
	//会议轮询控制
	MSG_CLICK(_T("BtnConfMixStart"), OnBtnConfMixStart)

	MSG_SELECTCHANGE(_T("CheckConfMixShortCut"), OnCheckConfMixShortCut)

	MSG_ITEMSELECTD(_T("MixList"), OnMixListClick)

	MSG_CLICK(_T("BtnMixSelOK"), OnBtnMixSelRoomOK)
	MSG_CLICK(_T("BtnMixSelAll"), OnBtnMixSelAll)
	MSG_CLICK(_T("BtnMixSelCancel"), OnBtnMixSelCancel)
	MSG_SELECTCHANGE(_T("BtnConfCnsSel"), OnCheckMixConfItem)
	
	MSG_EDITCHANGE(_T("EdtMixSearch"), OnMixSearchEditChange)	

	MSG_CLICK(_T("BtnAddMix"), OnBtnAddMix)
	MSG_CLICK(_T("BtnDelMix"), OnBtnMixDel)

	MSG_SELECTCHANGE(_T("OpAutoMix"), OnOpAutoMix)
	MSG_SELECTCHANGE(_T("OpManMix"), OnOpManMix)

 	USER_MSG(UI_CNS_CONFMIX_NTY,OnConfMixStateNty)
 	USER_MSG(UI_CNS_CONFMIX_IND,OnConfMixInd)
 	USER_MSG(UI_CNS_CONFMIX_FIX_IND,OnMixFixInd)
	USER_MSG( UI_UMS_REFRESH_CONFCNS_LIST, OnRefreshCnsLstNotify )
	USER_MSG(UI_CNC_SHORTCUT_CONFMIX,OnShortCutConfMix)

	USER_MSG( UI_CNS_CONFSTATE_NOTIFY, OnConfStateNotify )
	
APP_END_MSG_MAP()

CConfMixLogic::CConfMixLogic(void) 
{
	m_bIsSelAll = false;
	m_bIsSearch = false;
}

CConfMixLogic::~CConfMixLogic(void)
{
}

bool CConfMixLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_bIsSelAll = false;

	ICncCommonOp::SetControlText(_T(""),m_pm,_T("EdtMixSearch"));
	m_bIsSearch = false;

	m_vctCurrentCnsList.clear();
	m_vctSelConf.clear();
	m_vctMixList.clear();
	m_vctFixMixList.clear();
	m_vctSearchCnsList.clear();
	UpdateCnsList();
	UpdateMixList();
	ICncCommonOp::ShowControl( false, m_pm, _T("PageMixSelConfList") );
	m_tTpAudMixInfo.Clear();
	return true;
}

//会议轮询
bool CConfMixLogic::OnBtnConfMixStart( TNotifyUI& msg )
{
	TCMSConf tConfInfo;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
	if ( ! bInConf )
	{
		return NO_ERROR;
	}

	TTpAudMixInfo tTpAudMixInfo;
	tTpAudMixInfo.m_wConfId = tConfInfo.m_wConfID;
	if (m_tTpAudMixInfo.m_emMode == em_umsaudmixmode_idle)//当前混音关闭，点击开始
	{
		EmAudMixMode em = em_umsaudmixmode_smart;
		CCheckBoxUI *pControl = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("OpAutoMix") );
		if (pControl && !pControl->IsSelected())
		{
			em = em_umsaudmixmode_custom;
		}

		tTpAudMixInfo.m_emMode = em;

		if (em == em_umsaudmixmode_custom)
		{
			if(find(m_vctMixList.begin(), m_vctMixList.end(), tConfInfo.m_wSpeaker) == m_vctMixList.end())//列表中没有发言人
			{
				m_vctMixList.insert(m_vctMixList.begin(),tConfInfo.m_wSpeaker);//自动添加发言人
				UpdateMixList();
			}

			for(int i=0; i<m_vctMixList.size(); i++)
			{
				tTpAudMixInfo.m_tMixList.AddID(m_vctMixList.at(i));
			}
		}
	}
	else//当前混音已开启，点击关闭
	{
		tTpAudMixInfo.m_emMode = em_umsaudmixmode_idle;
	}
	
	u16 wRet = ComInterface->StartConfMix(tTpAudMixInfo);
	if (wRet != NO_ERROR)
	{
		ShowMessageBox(_T("会议混音设置请求发送失败"));
		return false;
	}

	return true;

}

bool CConfMixLogic::OnCheckConfMixShortCut( TNotifyUI& msg )
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

	EM_ShortcutType em = emShortcutCofMix;
	NOTIFY_MSG( UI_CNC_SET_SHORTCUT_NTY, em, bIsSet );
	return true;
}

bool CConfMixLogic::OnConfMixStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	bool bIsStart = true;//当前进行的是否是开启操作
	if (m_tTpAudMixInfo.m_emMode != em_umsaudmixmode_idle)
	{
		bIsStart = false;
	}
	ComInterface->GetConfMixState( m_tTpAudMixInfo );

	bool bStart = true;
	if (m_tTpAudMixInfo.m_emMode == em_umsaudmixmode_idle)
	{
		bStart = false;
	}
	else if (m_tTpAudMixInfo.m_emMode == em_umsaudmixmode_smart)
	{
		CCheckBoxUI *pControl = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("OpAutoMix") );
		if (pControl)
		{
			pControl->SetCheck(true);
		}
	}
	else
	{
		CCheckBoxUI *pControl = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("OpManMix") );
		if (pControl)
		{
			pControl->SetCheck(true);
		}
	}

	CButtonUI *pBtnConfMixStart = (CButtonUI*)ICncCommonOp::FindControl( m_pm, _T("BtnConfMixStart") );
	if (pBtnConfMixStart)
	{
		if (bStart)
		{
			
			pBtnConfMixStart->SetAttribute(_T("pushedimage"),_T("res/confctrl/confmix/stop_normal.png"));
			pBtnConfMixStart->SetAttribute(_T("normalimage"),_T("res/confctrl/confmix/stop_select.png"));
		}
		else
		{			
			pBtnConfMixStart->SetAttribute(_T("pushedimage"),_T("res/confctrl/confmix/start_normal.png"));
			pBtnConfMixStart->SetAttribute(_T("normalimage"),_T("res/confctrl/confmix/start_select.png"));
		}

	}

	if (bStart)//开启
	{
		//禁用混音模式选择和删除
		ICncCommonOp::EnableControl( false, m_pm,  _T("OpManMix") );
		ICncCommonOp::EnableControl( false, m_pm,  _T("OpAutoMix") );
		//ICncCommonOp::EnableControl( false, m_pm,  _T("BtnDelMix") );
	}
	else//关闭
	{
		//禁用混音模式选择
		ICncCommonOp::EnableControl( true, m_pm,  _T("OpManMix") );
		ICncCommonOp::EnableControl( true, m_pm,  _T("OpAutoMix") );
	}

	if (bIsStart && !bStart)//开启操作并且开启失败不清空列表
	{
		return S_OK;
	}
	else
	{
		m_vctMixList.clear();
		for (int i=0; i<m_tTpAudMixInfo.m_tMixList.m_wNum; i++)
		{
			m_vctMixList.push_back(m_tTpAudMixInfo.m_tMixList.m_awMixEp[i]);
		}
	}

	UpdateMixList();
	return S_OK;
}

bool CConfMixLogic::OnMixFixInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TTpAudMixListCmdRes tTpAudMixListCmdRes;
	ComInterface->GetConfMixIndFix( tTpAudMixListCmdRes );

	CString strError = _T("");
	for (int i=0; i<tTpAudMixListCmdRes.m_tList.m_wNum; i++)
	{
		if (tTpAudMixListCmdRes.m_aemRes[i] != em_umsaudmixres_sucess)
		{
			strError = _T("混音列表操作部分失败");
			switch(tTpAudMixListCmdRes.m_aemRes[i])
			{
			case em_umsaudmixres_add_invalidep:
				{
					strError = _T("混音列表更新部分失败:无效会场");
				}
				break;
			case em_umsaudmixres_add_getaudfail:
				{
					strError = _T("混音列表更新部分失败:上调会场音频失败");
				}
				break;
			case em_umsaudmixres_add_assignaudfail:
				{
					strError = _T("混音列表更新部分失败:建立到混音会场N-1音频通道失败");
				}
				break;
			case em_umsaudmixres_add_mixchanfull:
				{
					strError = _T("混音列表更新部分失败:资源不足，开启混音失败");
				}
				break;
			case em_umsaudmixres_add_repeatadd:
				{
					strError = _T("混音列表更新部分失败:已经在通道中");
				}
				break;
			case em_umsaudmixres_del_notfind:
				{
					strError = _T("混音列表更新部分失败:要删除混音通道不在混音通道中");
				}
				break;
			case em_umsaudmixres_start_nomix:
				{
					strError = _T("混音列表更新部分失败:开启混音，没有混音器, 会议混音不能正常开启");
				}
				break;
			case em_umsaudmixres_start_novalidep:
				{
					strError = _T("混音列表更新部分失败:开启混音，无有效混音会场，混音不能正常开启");
				}
				break;
			case em_umsaudmixres_samemode:
				{
					strError = _T("混音列表更新部分失败:开启混音，模式未改变，操作无效");
				}
				break;
			case em_umsaudmixres_unauthorized:
				{
					strError = _T("混音列表更新部分失败:开启混音，没有权限，操作无效, 上级ums和主席才能操作");
				}
				break;
			case em_umsaudmixres_dismode:
				{
					strError = _T("讨论已开启，开启混音失败，请关闭讨论");
				}
				break;
			case em_umsaudmixres_rollcallmode:
				{
					strError = _T("点名已开启，开启混音失败，请关闭点名");
				}
				break;
			case em_umsaudmixres_unkown:
				{
					strError = _T("混音操作失败:系统异常，请检查");
				}
				break;
			default:
				break;
			}
		}
	}

	if (strError.IsEmpty())
	{
		return S_OK;
	}

	ShowPopMsg(strError);
	
	return true;
}

bool CConfMixLogic::OnConfMixInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	EmAudMixMode emAudMixMode = (EmAudMixMode)wParam;
	EmAudMixRes emAudMixRes = (EmAudMixRes)lParam;
	if (emAudMixRes == em_umsaudmixres_sucess)
	{
		return true;
	}

	CString strError = _T("");
	switch(emAudMixRes)
	{
	case em_umsaudmixres_add_invalidep:
		{
			strError = _T("混音操作失败:无效会场");
		}
		break;
	case em_umsaudmixres_add_getaudfail:
		{
			strError = _T("混音操作失败:上调会场音频失败");
		}
		break;
	case em_umsaudmixres_add_assignaudfail:
		{
			strError = _T("混音操作失败:建立到混音会场N-1音频通道失败");
		}
		break;
	case em_umsaudmixres_add_mixchanfull:
		{
			strError = _T("资源不足，开启混音失败");
		}
		break;
	case em_umsaudmixres_add_repeatadd:
		{
			strError = _T("混音操作失败:已经在通道中");
		}
		break;
	case em_umsaudmixres_del_notfind:
		{
			strError = _T("混音操作失败:要删除混音通道不在混音通道中");
		}
		break;
	case em_umsaudmixres_start_nomix:
		{
			strError = _T("混音操作失败:开启混音，没有混音器, 会议混音不能正常开启");
		}
		break;
	case em_umsaudmixres_start_novalidep:
		{
			strError = _T("混音操作失败:开启混音，无有效混音会场，混音不能正常开启");
		}
		break;
	case em_umsaudmixres_samemode:
		{
			strError = _T("混音操作失败:开启混音，模式未改变，操作无效");
		}
		break;
	case em_umsaudmixres_unauthorized:
		{
			strError = _T("混音操作失败:开启混音，没有权限，操作无效, 上级ums和主席才能操作");
		}
		break;
	case em_umsaudmixres_dismode:
		{
			strError = _T("讨论已开启，开启混音失败，请关闭讨论");
		}
		break;
	case em_umsaudmixres_rollcallmode:
		{
			strError = _T("点名已开启，开启混音失败，请关闭点名");
		}
		break;
	case em_umsaudmixres_unkown:
		{
			strError = _T("混音操作失败:系统异常，请检查");
		}
		break;
	default:
		break;
	}

	if (strError.IsEmpty())
	{
		return S_OK;
	}

	ShowPopMsg(strError);

	return S_OK;
}

void CConfMixLogic::UpdateMixList(vector<u16>  vctMixList)
{
	TCMSConf tCMSConf;
	BOOL32 bIsInconf = ComInterface->IsInConf(&tCMSConf); 
	CListUI* pPollList = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("MixList"));
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

	for ( u16 i = 0; i < vctMixList.size(); i++ )
	{
		ptCnsInfo =  tCMSConf.GetCnsInfoByID(vctMixList.at(i));
		if (ptCnsInfo == NULL)
		{
			continue;
		}
		
		CListContainerElementUI *pListContainer = 
			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("MixListItem"));

		bool bOnline = ptCnsInfo->m_bOnline;
		if (bOnline)
		{
			pListContainer->SetAttribute(_T("bkcolor"), _T(""));
		}
		else
		{
			pListContainer->SetAttribute(_T("bkcolor"), _T("#FF40546C"));
		}

		strRoomName = ptCnsInfo->m_achRoomName;
 		strNum.Format(_T("%d"),i+1);
		ICncCommonOp::SetControlText( strRoomName, m_pm, _T("lbMixName"), pListContainer );
		ICncCommonOp::SetControlText( strNum, m_pm,  _T("lbMixNum"), pListContainer );

		pPollList->Add(pListContainer);
	}

}

void CConfMixLogic::UpdateMixList()
{
	m_vctFixMixList.clear();
	UpdateMixList(m_vctMixList);
}


bool CConfMixLogic::UpdateMixList(u16 wIndex, bool bSel)
{
	CListUI* pPollList = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("MixList"));
	if ( pPollList == NULL )
	{
		return false;
	}

	CListContainerElementUI *pListContainer = (CListContainerElementUI*)pPollList->GetItemAt(wIndex);
	if (pListContainer)
	{
		if (bSel)
		{
			ICncCommonOp::SetControlBkImg(_T("res\\confctrl\\confmix\\item_select.png"), m_pm, _T("MixItemContainer"), pListContainer);
		}
		else
		{
			ICncCommonOp::SetControlBkImg(_T(""), m_pm, _T("MixItemContainer"), pListContainer);
		}
		
	}

	return true;
}

bool CConfMixLogic::IsAutoMix()
{
	COptionUI *pAuto = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("OpAutoMix") );
	if (pAuto && pAuto->IsSelected())
	{
		return true;
	}
	
	return false;
}

bool CConfMixLogic::OnMixListClick( TNotifyUI& msg )
{
	m_vctFixMixList.clear();
	m_vctFixMixList.push_back(m_vctMixList.at(msg.wParam));
	
	//修改为可以删除
	ICncCommonOp::EnableControl(true, m_pm, _T("BtnDelMix"));
	//if (m_tTpAudMixInfo.m_emMode == em_umsaudmixmode_idle)//开启之后不能删除
	//{
	//	ICncCommonOp::EnableControl(true, m_pm, _T("BtnDelMix"));
	//}
	//新规格不进行多选
// 	bool bSeled = false;//是否已经被选
// 	bool bSel = true;
// 	for (int i=0; i<m_vctFixMixList.size(); i++)
// 	{
// 		if (m_vctFixMixList.at(i) == m_vctMixList.at(msg.wParam))
// 		{
// 			bSeled = true;//已经选过 删除
// 			m_vctFixMixList.erase(m_vctFixMixList.begin() + i );
// 			
// 			bSel = false;
// 			break;
// 		}
// 	}
// 
// 	if (!bSeled)//没被选过 添加
// 	{
// 		m_vctFixMixList.push_back(m_vctMixList.at(msg.wParam));
// 	}
// 	
// 	UpdateMixList(msg.wParam, bSel);
	return true;
}

bool CConfMixLogic::OnOpManMix(TNotifyUI& msg)
{
	m_pm->DoCase(_T("caseShowListLayout"));
	CMainMenuLogic::GetSingletonPtr()->UpdateConfMixState();
	return true;
}

bool CConfMixLogic::OnOpAutoMix(TNotifyUI& msg)
{
	m_pm->DoCase(_T("caseShowNoListLayout"));
	CMainMenuLogic::GetSingletonPtr()->UpdateConfMixState();
	return true;
}

bool CConfMixLogic::OnBtnAddMix( TNotifyUI& msg )
{
	bool bHandle  = false;
	OnRefreshCnsLstNotify(NULL,NULL,bHandle);
	m_bIsSelAll = false;
	m_vctSelConf.clear();
	ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnMixSelAll"));
	
	ICncCommonOp::SetControlText(_T(""),m_pm,_T("EdtMixSearch"));
	m_bIsSearch = false;
	m_vctSearchCnsList.clear();

	ICncCommonOp::ShowControl( true, m_pm, _T("PageMixSelConfList") );
	return true;
}

bool CConfMixLogic::OnBtnMixDel( TNotifyUI& msg )
{
	TCMSConf tConfInfo;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
	if ( ! bInConf )
	{
		return NO_ERROR;
	}

	if(m_vctFixMixList.size() == 0)
	{
		ShowMessageBox(_T("请先选择要删除的会场"));
		return false;
	}

	int ret = ShowMessageBox(_T("是否删除此会场"),true);
	if ( IDOK != ret )
	{
		return true;
	}

	for (int i=0; i<m_vctFixMixList.size(); i++)
	{
		if (tConfInfo.m_wSpeaker == m_vctFixMixList.at(i))
		{
			ShowMessageBox(_T("发言会场必须参加混音"));
			continue;
		}

		int nCount = m_vctMixList.size();
		for (int j=0;j<nCount;j++)
		{
			if (m_vctMixList.at(j) == m_vctFixMixList.at(i))
			{
				m_vctMixList.erase(m_vctMixList.begin() + j);
				break;
			}
		}
	}

	FixMixlist(false);
	UpdateMixList();
	return true;
}

bool CConfMixLogic::FixMixlist( bool bIsAdd )
{
	if (m_tTpAudMixInfo.m_emMode != em_umsaudmixmode_idle)//已经开启 发消息
	{
		TCMSConf tConfInfo;
		BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
		if ( ! bInConf )
		{
			return NO_ERROR;
		}

		TTpAudMixListCmd tpAudMixListCmd;
		if (bIsAdd)
		{
			tpAudMixListCmd.m_emOpr = em_umsaudmixlistopr_add;
		}
		else
		{
			tpAudMixListCmd.m_emOpr = em_umsaudmixlistopr_del;
		}
		
		TTpAudMixList tTpAudMixList;
		for (int i=0; i<m_vctFixMixList.size(); i++)
		{
			tTpAudMixList.AddID(m_vctFixMixList.at(i));
		}

		tpAudMixListCmd.m_wConfId = tConfInfo.m_wConfID;
		tpAudMixListCmd.m_tList = tTpAudMixList;
		ComInterface->FixConfMix(tpAudMixListCmd);
	}
	m_vctFixMixList.clear();

	return true;
}

bool CConfMixLogic::OnBtnMixSelCancel( TNotifyUI& msg )
{
	ICncCommonOp::ShowControl( false, m_pm, _T("PageMixSelConfList") );
	m_bIsSelAll = false;
	ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnPSelAll"));
	m_vctSelConf.clear();

	return true;
}

bool CConfMixLogic::OnCheckMixConfItem( TNotifyUI& msg )
{
	if (msg.pSender->GetParent()->GetParent()->GetName() != _T("MixCnsConfList"))
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

bool CConfMixLogic::OnBtnMixSelAll( TNotifyUI& msg )
{
	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MixCnsConfList") );
	if ( pTileLayoutUI == NULL )
	{
		return false;
	}
	m_bIsSelAll = !m_bIsSelAll;
	if ( m_bIsSelAll )
	{
		ICncCommonOp::SetControlText(_T("取消全选"),m_pm,_T("BtnMixSelAll"));
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
		ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnMixSelAll"));
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

void CConfMixLogic::UpdateCnsList()
{
	m_vctSelConf.clear();
	CTouchListUI* pConfCnsList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MixCnsConfList") );
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

bool CConfMixLogic::OnRefreshCnsLstNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TCMSConf tConfInfo ;
	bool bIn = ComInterface->IsInConf( &tConfInfo );	
	if (!bIn)
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
		ICncCommonOp::SetControlText(_T(""), m_pm,  _T("EdtMixSearch"));
	}

	UpdateCnsList();

	CCheckBoxUI *pControl = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("OpManMix") );
	if (pControl)
	{
		if(pControl->GetCheck())//手动模式下才进行列表更新
		{
			UpdateConfMixState();
		}
	}

	return true;
}

void CConfMixLogic::UpdateConfMixState()
{
	TCMSConf tConfInfo ;
	bool bIn = ComInterface->IsInConf( &tConfInfo );
	if (!bIn)
	{
		return;
	}

	CListUI* pMixList = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("MixList"));
	if ( pMixList == NULL )
	{
		return ;
	}

	for (int i=0; i<m_vctMixList.size(); i++)
	{
		CListContainerElementUI *pListContainer = (CListContainerElementUI*)pMixList->GetItemAt(i);
		if (pListContainer == NULL)
		{
			return;
		}

		TCnsInfo* ptCnsInfo =  tConfInfo.GetCnsInfoByID(m_vctMixList.at(i));
		if (ptCnsInfo == NULL)
		{
			continue;
		}
		bool bOnline = ptCnsInfo->m_bOnline;
		if (bOnline)
		{
			pListContainer->SetAttribute(_T("bkcolor"), _T(""));
		}
		else
		{
			pListContainer->SetAttribute(_T("bkcolor"), _T("#FF40546C"));
		}
	}
}

bool CConfMixLogic::OnBtnMixSelRoomOK( TNotifyUI& msg )
{
	if (m_vctSelConf.size() == 0)
	{
		ShowMessageBox(_T("请选择要添加的会场"));
		return false;
	}

	if (m_tTpAudMixInfo.m_emMode != em_umsaudmixmode_idle)//开启了才发送修改
	{
		m_vctFixMixList.clear();
	}
	
	ICncCommonOp::ShowControl( false, m_pm, _T("PageMixSelConfList") );
	for (int i=0; i<m_vctSelConf.size(); i++)//不重复添加
	{
		bool bInclude = false;
		for (int j=0; j<m_vctMixList.size(); j++)
		{
			if (m_vctSelConf.at(i).m_wEpID == m_vctMixList.at(j))
			{
				bInclude = true;
				break;
			}
		}

		if (!bInclude)
		{
			m_vctMixList.push_back(m_vctSelConf.at(i).m_wEpID);
			if (m_tTpAudMixInfo.m_emMode != em_umsaudmixmode_idle)//开启了才发送修改
			{
				m_vctFixMixList.push_back(m_vctSelConf.at(i).m_wEpID);
			}	
		}
	}

	if (m_tTpAudMixInfo.m_emMode != em_umsaudmixmode_idle)//开启了才发送修改
	{
		if (0 == m_vctFixMixList.size())
		{
			return true;
		}
		FixMixlist(true);
	}
	
	UpdateMixList();

	CListUI* pPollList = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("MixList"));
	if (pPollList)
	{
		pPollList->SelectItem(m_vctMixList.size() -1);
	}
	return true;
}

bool CConfMixLogic::OnMixSearchEditChange( TNotifyUI& msg )
{
	CEditUI* pEditSearch = (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("EdtMixSearch") );
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
		ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnMixSelAll"));
		CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MixCnsConfList") );
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

bool CConfMixLogic::OnConfStateNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bInConf = ComInterface->IsInConf();
	if ( !bInConf )
	{
		OnDisconnect( wParam, lParam, bHandle );
	}

	return false;
}

bool CConfMixLogic::OnShortCutConfMix( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TNotifyUI msg;
	OnBtnConfMixStart( msg );

	return true;
}