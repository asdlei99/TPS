#include "StdAfx.h"
#include "srcselwatch.h"
#include "messageboxlogic.h"
#include "confmsglogic.h"

template<> CSrcSelWatchLogic* Singleton<CSrcSelWatchLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CSrcSelWatchLogic,CNotifyUIImpl)

	MSG_CREATEWINDOW(_T("SrcSelWatchLayout"), OnCreate)
	MSG_INIWINDOW(_T("SrcSelWatchLayout"), OnInit)
	
	MSG_ITEMSELECTD(_T("ConfInfoList"), OnCnsInfoListItemClick)
	MSG_ITEMSELECTD(_T("SelConfInfoList"), OnSelConfInfoListItemClick)
	MSG_ITEMSELECTD(_T("ScreenSlectList"), OnScreenSlectListItemClick)

	MSG_SELECTCHANGE(_T("CheckShowSel"), OnBtnShowSel)	

	MSG_CLICK(_T("BtnCancel"), OnBtnCancel)
	MSG_CLICK(_T("BtnOK"), OnBtnOK)
	MSG_CLICK(_T("BtnSetWatch1"), OnBtnSetWatch1)
	MSG_CLICK(_T("BtnSetWatch2"), OnBtnSetWatch2)
	MSG_CLICK(_T("BtnSetWatch3"), OnBtnSetWatch3)
	MSG_CLICK(_T("BtnShowSel"), OnGetSelItemInMainList)
	MSG_CLICK(_T("BtnCancelCurWatch"), OnBtnCancelCurWatch)
	MSG_CLICK(_T("BtnCancelWatch"), OnBtnCancelWatch)
	MSG_CLICK(_T("BtnShowScreenOption"), OnBtnShowScreenOption)
	MSG_CLICK(_T("BtnHideScreenOption"), OnBtnHideScreenOption)
	MSG_CLICK(_T("BtnRoomWatch"), OnBtnRoomWatch)
	MSG_CLICK(_T("BtnRoomSel"), OnListBtnRoomSel)
	

	MSG_EDITCHANGE(_T("EdtSearch"), OnSearchEditChange)	

    MSG_DRAGSTART(_T("SelWatchItem"), OnDragIsStart)
    MSG_DRAGDONE(_T("SelWatchItem"), OnDragIsOver)
    MSG_DRAGCANCEL(_T("SelWatchItem"), OnDragIsOver)
	MSG_DRAGDROP(_T("SelectedItem"), OnDragDrop)
	MSG_DRAGENTER(_T("SelectedItem"), OnDragEnter)
	MSG_DRAGLEAVE(_T("SelectedItem"), OnDragLeave)
	MSG_DRAGDONE(_T("SelectedItem"), OnDragDone)	

	USER_MSG(UI_UMS_REFRESH_CONFCNS_LIST,OnRefreshCnsInfoList) 
	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)
	
	USER_MSG(UI_CNS_SEL_VIEW_NTY,OnSelViewNty) //成功只有nty 
	USER_MSG(UI_CNS_SEL_VIEW_IND,OnSelViewNty)//失败只有ind 在此更新一下列表

	MSG_LETTERINDEX_CLICK(_T("ListIndex"),OnLetterIndex)  
	USER_MSG( UI_CNS_CONFSTATE_NOTIFY, OnConfStateNty )

    USER_MSG(WM_DUI_EDITSETFOCUS, OnEditSetFocus)

APP_END_MSG_MAP()

const String CSrcSelWatchLogic::m_strCnsInfoList = _T("ConfInfoList");
const String CSrcSelWatchLogic::m_strCnsInfoListItem = _T("SelWatchItem");
const String CSrcSelWatchLogic::m_strSeachEdit = _T("EdtSearch");

CSrcSelWatchLogic::CSrcSelWatchLogic(void):m_wCurrentSelIndex(-1),m_bIsGetScreenState(false),m_bIsVideoMix(false),m_bIsClickBtnCancelWatch(false),m_bIsDraging(false),m_bIsNeedUpdate(false)
{
	m_bSearchEdit = FALSE;
}


CSrcSelWatchLogic::~CSrcSelWatchLogic(void)
{
}

bool CSrcSelWatchLogic::OnCreate( TNotifyUI& msg )
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
	return false;
}

bool CSrcSelWatchLogic::OnInit( TNotifyUI& msg )
{
	UpdateCnsInfoList();

	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("SelConfInfoList") );
	if ( pTileLayoutUI == NULL )
	{
		return false;
	}

	pTileLayoutUI->RemoveAll();
	for ( int i = 0; i <  3; i++ )
	{
		CListContainerElementUI *pListContainer = 
			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("SelectedItem"));

		ICncCommonOp::SetControlText( _T("无选看"), m_pm, _T("lbName"), pListContainer );
		CControlUI* pControl = ICncCommonOp::FindControl(m_pm,_T("BtnShowSel"), pListContainer);
		if (pControl)
		{
			ICncCommonOp::SetTag(pControl, -1);
		}
		pTileLayoutUI->Add(pListContainer);
	}
	CCheckBoxUI* pcheck = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckShowSel") ); 
	if (pcheck)
	{
		pcheck->Selected(true);//默认开启
	}

	//第一次从会议控制里开启会议选看时需要更新一下界面
	bool bHandle = false;
	OnSelViewNty( 0, 0, bHandle);
	return true;
}

bool CSrcSelWatchLogic::OnRefreshCnsInfoList( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	if (m_vctSearchLst.size() != 0)
	{
		m_vctSearchLst.clear();
		ICncCommonOp::SetControlText(_T(""), m_pm,  _T("EdtSearch"));
	}

	UpdateCnsInfoList();
	return true;
}

void CSrcSelWatchLogic::UpdateCnsInfoList()
{
    if (m_bIsDraging)//拖拽中不刷新
    {
        m_bIsNeedUpdate = true;
        return;
    }
    m_bIsNeedUpdate = false;

	TCMSConf tConfInfo ;
	bool bIn = ComInterface->IsInConf( &tConfInfo );
	if (!bIn)
	{
		m_tConfInfo.Clear();
		return;
	}
	m_tConfInfo = tConfInfo;

	TTPCnsInfo tlocalCnsInfo;
	ComInterface->GetLocalCnsInfo(tlocalCnsInfo);

	TCnsInfo *tCnsInfoLocal = tConfInfo.GetLocalCnsInfo( tlocalCnsInfo );
	if (tCnsInfoLocal == NULL)
	{
		return;
	}

	m_vctCnsInfoList.clear();
	m_tCurSelectViewInfo.Clear();
	for (int i = 0; i < tConfInfo.m_vctCnsList.size(); i++)
	{
		TCnsInfo tCnsInfo = tConfInfo.m_vctCnsList.at(i);
		if ( tCnsInfo.m_emEpType == emTPEndpointTypeUMS || tCnsInfo.m_emEpType == emTPEndpointH323MCU )
		{            
			continue;
		}

		if (tCnsInfo.m_bOnline
			&& tConfInfo.m_vctCnsList.at(i).m_wEpID != tCnsInfoLocal->m_wEpID)//只显示在线 不显示自己 2015-7-15
		{
			TSelViewInfo tSelViewInfo;
			tSelViewInfo.m_wConfID = tConfInfo.m_wConfID;
			tSelViewInfo.m_wEpID = tCnsInfoLocal->m_wEpID;
			tSelViewInfo.m_emType = EmEpType_Ter;
			tSelViewInfo.m_emEpType = tConfInfo.m_vctCnsList.at(i).m_emEpType;
			tSelViewInfo.m_wDstID = tConfInfo.m_vctCnsList.at(i).m_wEpID;
			tSelViewInfo.m_wSpeakerNum = tConfInfo.m_vctCnsList.at(i).m_wSpeakerNum;
			memcpy(tSelViewInfo.m_achRoomName, tConfInfo.m_vctCnsList.at(i).m_achRoomName, TP_MAX_ALIAS_LEN);

			m_vctCnsInfoList.push_back(tSelViewInfo);
		}
	}

	sort( m_vctCnsInfoList.begin(), m_vctCnsInfoList.end(), CUIDataMgr::SelViewCompare );

	vector<TBrdVmpResNtfy> vctBrdVmpArray = ComInterface->GetBrdVmpStatus();
	m_bIsVideoMix = false;//是否开启画面合成

	CString strVideoMixName;
	for (int i=0; i<vctBrdVmpArray.size(); i++)//所有的都添加进来
	{
        TBrdVmpResNtfy tBrdVmpInfo = vctBrdVmpArray.at(i);
		if (tBrdVmpInfo.m_emStat == EmBrdVmpStat_Normal
			|| tBrdVmpInfo.m_emStat == EmBrdVmpStat_Brd )
		{
			m_bIsVideoMix = true;

			CString str(tBrdVmpInfo.m_tEqpInfo.m_szEqpAlias);

			TSelViewInfo tSelViewInfo;
			tSelViewInfo.m_wConfID = tConfInfo.m_wConfID;
			tSelViewInfo.m_wEpID = tCnsInfoLocal->m_wEpID;;//本会场的会场号
			tSelViewInfo.m_emType = EmEpType_Eqp;
			tSelViewInfo.m_wDstID = tBrdVmpInfo.m_tEqpInfo.m_byEqpID ;
			memcpy(tSelViewInfo.m_achRoomName,tBrdVmpInfo.m_tEqpInfo.m_szEqpAlias,TP_MAXLEN_EQP_ALIAS);

			m_vctCnsInfoList.insert(m_vctCnsInfoList.begin(),tSelViewInfo);
		}
	}

	CTouchListUI* pAdrList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, m_strCnsInfoList.c_str() );
	if ( pAdrList == NULL )
	{
		return;
	}

	pAdrList->RemoveAll();
	if (m_bSearchEdit)
	{
		TNotifyUI msg; 
		OnSearchEditChange(msg);
		return;
	}

	for ( u16 i = 0; i < m_vctCnsInfoList.size(); i++ )
	{
		CListContainerElementUI *pListContainer = 
			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( m_strCnsInfoListItem.c_str() );

		if ( m_vctCnsInfoList.at(i).m_emType == EmEpType_Eqp)
		{
			ICncCommonOp::SetControlBkImg(_T("res\\list\\imgVidMix.png"), m_pm, _T("imgAddrLabel"), pListContainer);
		}

		TSelViewInfo tCnsInfo = m_vctCnsInfoList.at(i); 
		ICncCommonOp::SetControlText( CA2T(tCnsInfo.m_achRoomName), m_pm, _T("AddrEntryName"), pListContainer );
		if ( tCnsInfo.m_emType == EmEpType_Eqp)
		{
			ICncCommonOp::SetControlBkImg(_T("res\\list\\imgVidMix.png"), m_pm, _T("imgAddrLabel"), pListContainer);
		}
		else if (tCnsInfo.m_emEpType == emTPEndpointH323G400)
		{
			ICncCommonOp::SetControlBkImg(_T("res\\list\\imgMonitor.png"), m_pm, _T("imgAddrLabel"), pListContainer);
		}
		else if (tCnsInfo.m_emEpType == emTPEndpointTypeVRS)
		{
			ICncCommonOp::SetControlBkImg(_T("res\\list\\imgStudio.png"), m_pm, _T("imgAddrLabel"), pListContainer);
		}
		else if (tCnsInfo.m_emEpType != emTPEndpointTypeCNS)
		{
			ICncCommonOp::SetControlBkImg(_T("res\\list\\imgOrdinary.png"), m_pm, _T("imgAddrLabel"), pListContainer);
		}


		//三屏会场显示屏幕选项按钮
		if ((EmEpType_Ter == tCnsInfo.m_emType) && (3 == tCnsInfo.m_wSpeakerNum))
		{
			m_pm->DoCase(_T("caseHideScreeOption"), pListContainer);
		}
		else
		{
			ICncCommonOp::ShowControl(false, m_pm, _T("BtnScreenOption"), pListContainer);
		}

		//会场列表选择按钮checkbox
		if (EmEpType_Ter == tCnsInfo.m_emType)
		{
			ICncCommonOp::ShowControl(true, m_pm, _T("BtnRoomSel"), pListContainer);
		}
		else
		{
			ICncCommonOp::ShowControl(false, m_pm, _T("BtnRoomSel"), pListContainer);
		}
		
		pAdrList->Add(pListContainer);
	}
	
	m_wCurrentSelIndex = -1;
}

void CSrcSelWatchLogic::ReSetSelScreen()
{
    CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("SelConfInfoList") );
    if ( pTileLayoutUI == NULL )
    {
        return;
    }
    for ( int i = 0 ; i < TP_MAX_STREAMNUM ; i++ )
    {
        CListContainerElementUI *pItem = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(i);
        if (pItem)
        {
            pItem->Select(false);
        }
    }
}

bool CSrcSelWatchLogic::OnCnsInfoListItemClick( TNotifyUI& msg )
{
	//m_wCurrentSelIndex = msg.wParam;
// 	CTouchListUI* pTouchList = (CTouchListUI*)ICncCommonOp::FindControl(m_pm,_T("SelConfInfoList")); //这样的话选择显示已选条目时有问题
// 	if (pTouchList)
// 	{
// 		pTouchList->SelectItem(-1);
// 	}
	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("ConfInfoList") );
	if (!pTileLayoutUI)
	{
		return false;
	}

	ICncCommonOp::EnableControl(true,m_pm,_T("BtnSetWatch1"));
	ICncCommonOp::EnableControl(true,m_pm,_T("BtnSetWatch2"));
	ICncCommonOp::EnableControl(true,m_pm,_T("BtnSetWatch3"));

	u16 wCurrentSelIndex = msg.wParam;
	if (m_wCurrentSelIndex != wCurrentSelIndex)
	{
		CListContainerElementUI *pLastListContainerElement = (CListContainerElementUI *)pTileLayoutUI->GetItemAt(m_wCurrentSelIndex);
		if (pLastListContainerElement)
		{
			TSelViewInfo *pTSelViewInfo = NULL;
			if (m_bSearchEdit)
			{
				pTSelViewInfo = &m_vctSearchLst.at(m_wCurrentSelIndex);
			}
			else
			{
				pTSelViewInfo = &m_vctCnsInfoList.at(m_wCurrentSelIndex);
			}

			if ((EmEpType_Ter == pTSelViewInfo->m_emType) && ( 3 == pTSelViewInfo->m_wSpeakerNum))
			{
				CTouchListUI* pListScreenSlect = (CTouchListUI*)ICncCommonOp::FindControl(m_pm, _T("ScreenSlectList"), pLastListContainerElement);
				if (pListScreenSlect)
				{
					pListScreenSlect->SelectItem(-1);
				}
				pTSelViewInfo->m_wDstScrIndx = TP_MAX_STREAMNUM;
				m_pm->DoCase(_T("caseHideScreeOption"), pLastListContainerElement);
			}
			if (EmEpType_Ter == pTSelViewInfo->m_emType)
			{
				CCheckBoxUI* pCheckBoxRoomSel = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("BtnRoomSel"), pLastListContainerElement);
				if (pCheckBoxRoomSel)
				{
					pCheckBoxRoomSel->SetCheck(false);
					m_tCurSelectViewInfo.Clear();
				}
			}
			pTSelViewInfo = NULL;
		}
		m_wCurrentSelIndex = wCurrentSelIndex;
	}

	return true;
}

bool CSrcSelWatchLogic::OnSearchEditChange( TNotifyUI& msg )
{
 	CEditUI* pEditSearch = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strSeachEdit.c_str() );
	if ( !pEditSearch )
	{
		return false;
	}

	m_vctSearchLst.clear();
	m_tCurSelectViewInfo.Clear();
	CString strSearch = pEditSearch->GetText();
	if ( strSearch.IsEmpty() )
	{
		m_bSearchEdit = FALSE;
		UpdateCnsInfoList();
	}
	else
	{
		m_bSearchEdit = TRUE;
		CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("ConfInfoList") );
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
				m_vctSearchLst.push_back( m_vctCnsInfoList.at(i));
				CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( m_strCnsInfoListItem.c_str() );
				TSelViewInfo tSelViewInfo = m_vctCnsInfoList.at(i); 

				ICncCommonOp::SetControlText( CA2T(tSelViewInfo.m_achRoomName), m_pm, _T("AddrEntryName"), pListContainer );

				//设置监控终端图标
				if (m_vctCnsInfoList.at(i).m_emType == EmEpType_Eqp) //若画面合成开启并且搜索后第一个元素被搜索到，更换显示的图片
				{
					ICncCommonOp::SetControlBkImg(_T("res\\list\\imgVidMix.png"), m_pm, _T("imgAddrLabel"), pListContainer);
				}
				else if (m_vctCnsInfoList.at(i).m_emEpType == emTPEndpointH323G400)
				{
					ICncCommonOp::SetControlBkImg(_T("res\\list\\imgMonitor.png"), m_pm, _T("imgAddrLabel"), pListContainer);
				}
				else if (m_vctCnsInfoList.at(i).m_emEpType == emTPEndpointTypeVRS)
				{
					ICncCommonOp::SetControlBkImg(_T("res\\list\\imgStudio.png"), m_pm, _T("imgAddrLabel"), pListContainer);
				}
				else if (m_vctCnsInfoList.at(i).m_emEpType != emTPEndpointTypeCNS)
				{
					ICncCommonOp::SetControlBkImg(_T("res\\list\\imgOrdinary.png"), m_pm, _T("imgAddrLabel"), pListContainer);
				}

				//三屏会场显示屏幕选项按钮
				if ((EmEpType_Ter == tSelViewInfo.m_emType) && (3 == tSelViewInfo.m_wSpeakerNum))
				{
					m_pm->DoCase(_T("caseHideScreeOption"), pListContainer);
				}
				else
				{
					ICncCommonOp::ShowControl(false, m_pm, _T("BtnScreenOption"), pListContainer);
				}

				//会场列表选择按钮checkbox
				if (EmEpType_Ter == tSelViewInfo.m_emType)
				{
					ICncCommonOp::ShowControl(true, m_pm, _T("BtnRoomSel"), pListContainer);
				}
				else
				{
					ICncCommonOp::ShowControl(false, m_pm, _T("BtnRoomSel"), pListContainer);
				}

				pTileLayoutUI->Add(pListContainer);
			}
		}

		m_wCurrentSelIndex = -1;
	}

	return false;
}

bool CSrcSelWatchLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	CEditUI* pEditSearch = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strSeachEdit.c_str() );
	if ( pEditSearch )
	{
		pEditSearch->SetText(_T(""));
	}

	m_vctCnsInfoList.clear();
	m_tConfInfo.Clear();
	m_tCurSelectViewInfo.Clear();
	m_bSearchEdit = FALSE;
	
	m_aSelWatch[0].Clear();
	m_aSelWatch[1].Clear();
	m_aSelWatch[2].Clear();

	m_vctSearchLst.clear();
	m_wCurrentSelIndex = -1;
	m_bIsGetScreenState = false;
	m_bIsVideoMix = false;
	m_bIsClickBtnCancelWatch = false;

	CCheckBoxUI* pcheck = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckShowSel") ); 
	if (pcheck)
	{
		pcheck->Selected(true);//默认开启
	}
	//恢复初始界面
	RestoreInitUI();

	return true;
}

bool CSrcSelWatchLogic::OnBtnCancel( TNotifyUI& msg )
{	
	CEditUI* pEditSearch = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strSeachEdit.c_str() );
	if ( pEditSearch )
	{
		pEditSearch->SetText(_T(""));
	}

	WINDOW_MGR_PTR->ShowWindowFromLeftToRight( g_strSrcSelWatchDlg.c_str(), false );
	if (UIDATAMGR->GetCurShowWndName() == g_strSrcSelWatchDlg && WINDOW_MGR_PTR->IsWindowVisible(g_strSrcSelWatchDlg.c_str()))
	{
		WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowCnsManage"));
		UIDATAMGR->SetCurShowWndName( _T("") );
	}
// 	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckShowSel") );
// 	if ( !pCheckBox )
// 	{
// 		return false;
// 	}
// 	pCheckBox->SetCheck(false);

	m_wCurrentSelIndex = -1;
	m_bIsGetScreenState = false;

	bool bHandle = false;
	OnSelViewNty( NULL, NULL, bHandle );
	return true;
}


bool CSrcSelWatchLogic::SetScreenWatch( int nScreenID )
{
	if (!m_aSelWatch[nScreenID].IsValid())
	{
		return false;
	}

	TTPSelViewReq tTPSelViewReq;
	tTPSelViewReq.m_bSel = true;
	tTPSelViewReq.m_emType = m_aSelWatch[nScreenID].m_emType;
	tTPSelViewReq.m_emUIType = EmUI_CNC;
	tTPSelViewReq.m_wConfID = m_aSelWatch[nScreenID].m_wConfID;
	tTPSelViewReq.m_wScreenIndx = nScreenID;
	tTPSelViewReq.m_wEpID = m_aSelWatch[nScreenID].m_wEpID;
	tTPSelViewReq.m_wDstID = m_aSelWatch[nScreenID].m_wDstID;
	tTPSelViewReq.m_wDstScrIndx = m_aSelWatch[nScreenID].m_wDstScrIndx;

	u16 wRe = ComInterface->SetSelView( tTPSelViewReq);
	if ( wRe != NO_ERROR )
	{
		CString str;
		str.Format(_T("屏%d选看设置失败"),nScreenID);
		ShowPopMsg(str);
	}

	return true;
}

void CSrcSelWatchLogic::RestoreInitUI()
{
	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("SelConfInfoList") );
	if ( pTileLayoutUI == NULL )
	{
		return;
	}

	for ( int i = 0; i <  3; i++ )
	{
		CListContainerElementUI *pItem = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(i);
		if (pItem)
		{
			ICncCommonOp::SetControlText( _T("无选看"), m_pm, _T("lbName"), pItem );
		}
	}

	ICncCommonOp::ShowControl( false, m_pm, _T("BtnCancelWatch") );

	CTouchListUI* pAdrList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, m_strCnsInfoList.c_str() );
	if ( pAdrList == NULL )
	{
		return;
	}

	pAdrList->RemoveAll();
}

bool CSrcSelWatchLogic::OnBtnOK( TNotifyUI& msg )
{
	TTPSelViewNtfy tTPSelViewNtfy = ComInterface->GetSelWatchStatus();	
	for ( int i = 0; i < 3; i++)
	{		
		if (m_aSelWatch[i].m_wDstID == tTPSelViewNtfy.m_atSelView[i].m_wDstID)
		{
			continue;//gy确认 一样不发
		}

		if (!m_aSelWatch[i].IsValid())
		{
			continue;
		}
		
		TTPSelViewReq tTPSelViewReq;
		tTPSelViewReq.m_bSel = true;
		tTPSelViewReq.m_emType = m_aSelWatch[i].m_emType;
		tTPSelViewReq.m_emUIType = EmUI_CNC;
		tTPSelViewReq.m_wConfID = m_aSelWatch[i].m_wConfID;
		tTPSelViewReq.m_wScreenIndx = i;
		tTPSelViewReq.m_wEpID = m_aSelWatch[i].m_wEpID;
		tTPSelViewReq.m_wDstID = m_aSelWatch[i].m_wDstID;
		tTPSelViewReq.m_wDstScrIndx = m_aSelWatch[i].m_wDstScrIndx;

		u16 wRe = ComInterface->SetSelView( tTPSelViewReq);
		if ( wRe != NO_ERROR )
		{
			CString str;
			str.Format(_T("屏%d选看设置失败"),i);
			ShowMessageBox(str);
		}
	}
	return true;
}

bool CSrcSelWatchLogic::OnBtnShowSel( TNotifyUI& msg )
{
	if (!m_bIsGetScreenState)
	{
		m_bIsGetScreenState = true;
		UpdateSelList();
	}

	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("SelConfInfoList") );
	if ( pTileLayoutUI == NULL )
	{
		return false;
	}
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}
	if ( pCheckBox->IsSelected() )
	{
		pTileLayoutUI->SetVisible(true);
	}
	else
	{
		pTileLayoutUI->SetVisible(false);
		return true;
	}

	for ( int i = 0; i <  3; i++ )
	{
		CListContainerElementUI *pListContainer = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(i);
		if (!pTileLayoutUI)
		{
			return false;
		}

		if (m_aSelWatch[i].m_wEpID == TP_INVALID_INDEX)
		{
			ICncCommonOp::SetControlText( _T("无选看"), m_pm, _T("lbName"), pListContainer );
		}
		else
		{
			ICncCommonOp::SetControlText( CA2T(m_aSelWatch[i].m_achRoomName), m_pm, _T("lbName"), pListContainer );
		}

	}
	return true;
}



bool CSrcSelWatchLogic::OnSelConfInfoListItemClick( TNotifyUI& msg )
{
// 	int dwSelIndex = msg.wParam;
// 
// 	TCnsInfo tCnsInfo = m_aSelWatch[dwSelIndex];
// 
// 	int wIndex = 0;
// 	bool bIs = false;
// 	for ( wIndex; wIndex < m_vctCnsInfoList.size(); wIndex++)
// 	{
// 		if ( strncmp(m_vctCnsInfoList.at(wIndex).m_achRoomE164,tCnsInfo.m_achRoomE164, TP_MAX_ALIAS_LEN+1) == 0)
// 		{
// 			bIs = true;
// 			break;
// 		}
// 	}
// 	CTouchListUI* pList = (CTouchListUI*)ICncCommonOp::FindControl(m_pm,_T("ConfInfoList"));
// 	if (!pList)
// 	{
// 		return false;
// 	}
// 	if (bIs)
// 	{
// 		pList->SelectItem(wIndex);
// 	}
// 	else
// 	{
// 		pList->SelectItem(-1);
// 		ICncCommonOp::EnableControl(false,m_pm,_T("BtnSetWatch1"));
// 		ICncCommonOp::EnableControl(false,m_pm,_T("BtnSetWatch2"));
// 		ICncCommonOp::EnableControl(false,m_pm,_T("BtnSetWatch3"));
// 	}

	return true;
}

bool CSrcSelWatchLogic::OnGetSelItemInMainList( TNotifyUI& msg )
{
	if (m_vctSearchLst.size() >0)//搜索状态下先清空搜索
	{
		ICncCommonOp::SetControlText(_T(""),m_pm,m_strSeachEdit.c_str());
	}

	int dwSelIndex = msg.pSender->GetTag();
	CTouchListUI* pTouchList = (CTouchListUI*)ICncCommonOp::FindControl(m_pm,_T("SelConfInfoList"));
	if (pTouchList)
	{
		CTouchListUI* plist = (CTouchListUI*)msg.pSender->GetParent()->GetParent();
		int nID = plist->GetItemIndex(msg.pSender->GetParent());
		pTouchList->SelectItem(nID);
	}

	CTouchListUI* pList = (CTouchListUI*)ICncCommonOp::FindControl(m_pm,_T("ConfInfoList"));
	if (!pList)
	{
		return false;
	}

	pList->SelectItem(dwSelIndex);

	if (dwSelIndex == -1)
	{
		ICncCommonOp::EnableControl(false,m_pm,_T("BtnSetWatch1"));
		ICncCommonOp::EnableControl(false,m_pm,_T("BtnSetWatch2"));
		ICncCommonOp::EnableControl(false,m_pm,_T("BtnSetWatch3"));
	}

	return true;
}

bool CSrcSelWatchLogic::OnBtnCancelCurWatch(TNotifyUI& msg)
{
	CTouchListUI* pTouchList = (CTouchListUI*)ICncCommonOp::FindControl(m_pm,_T("SelConfInfoList"));
	if (!pTouchList)
	{
		return false;
	}

	int nIndex = pTouchList->GetItemIndex(msg.pSender->GetParent());
	pTouchList->SelectItem(nIndex);
	CSrcSelWatchLogic::GetSingletonPtr()->CancelSelWatch(nIndex);

	return true;
}

bool CSrcSelWatchLogic::OnBtnCancelWatch(TNotifyUI& msg)
{
	m_bIsClickBtnCancelWatch = true;
	
	for (int i=0; i<3; i++)
	{
		CSrcSelWatchLogic::GetSingletonPtr()->CancelSelWatch(i);
	}

	return true;
}

bool CSrcSelWatchLogic::OnBtnShowScreenOption(TNotifyUI& msg)
{
	CTouchListUI* pList = (CTouchListUI*)ICncCommonOp::FindControl(m_pm,_T("ConfInfoList"));
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

	m_pm->DoCase(_T("caseShowScreeOption"), pListContainer);
	return true;
}

bool CSrcSelWatchLogic::OnBtnHideScreenOption(TNotifyUI& msg)
{
	CTouchListUI* pList = (CTouchListUI*)ICncCommonOp::FindControl(m_pm,_T("ConfInfoList"));
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

	//恢复为初始状态
	TSelViewInfo *pTSelViewInfo = NULL;
	if ( m_bSearchEdit)
	{
		pTSelViewInfo = &m_vctSearchLst.at(m_wCurrentSelIndex);
	}
	else
	{
		pTSelViewInfo = &m_vctCnsInfoList.at(m_wCurrentSelIndex);
	}
	if (pTSelViewInfo)
	{
		pTSelViewInfo->m_wDstScrIndx = TP_MAX_STREAMNUM;
	}
	
	pListScreenSlect->SelectItem(-1);
	m_pm->DoCase(_T("caseHideScreeOption"), pListContainer);

	pTSelViewInfo = NULL;

	return true;
}

bool CSrcSelWatchLogic::OnBtnRoomWatch(TNotifyUI& msg)
{
	if(!m_tCurSelectViewInfo.IsValid())
	{
		ShowMessageBox(_T("请先选择进行设置的会场"));
		return false;
	}

	TTPSelViewReq tTPSelViewReq;
	tTPSelViewReq.m_bSel = true;
	tTPSelViewReq.m_emType = EmEpType_Ter;
	tTPSelViewReq.m_emUIType = EmUI_CNC;
	tTPSelViewReq.m_wConfID = m_tCurSelectViewInfo.m_wConfID;
	tTPSelViewReq.m_wScreenIndx = TP_MAX_STREAMNUM;//会场选看
	tTPSelViewReq.m_wEpID = m_tCurSelectViewInfo.m_wEpID;
	tTPSelViewReq.m_wDstID = m_tCurSelectViewInfo.m_wDstID;

	u16 wRe = ComInterface->SetSelView( tTPSelViewReq);
	if ( wRe != NO_ERROR )
	{
		CString str;
		str.Format(_T("会场选看设置失败"));
		ShowMessageBox(str);
	}
	
	return true;
}

bool CSrcSelWatchLogic::OnListBtnRoomSel(TNotifyUI& msg)
{
	CTouchListUI* pList = (CTouchListUI*)ICncCommonOp::FindControl(m_pm,_T("ConfInfoList"));
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

	//这里的checkbox响应的是MSG_CLICK消息，选中情况的判断与MSG_SELECTCHANGE情况相反
	CCheckBoxUI *pCheckBox = (CCheckBoxUI*)msg.pSender;
	bool bCheck = pCheckBox->GetCheck();
	if ( !bCheck )//选中
	{
		if ( m_bSearchEdit)
		{
			m_tCurSelectViewInfo = m_vctSearchLst.at(m_wCurrentSelIndex);
		}
		else
		{
			m_tCurSelectViewInfo = m_vctCnsInfoList.at(m_wCurrentSelIndex);
		}
	}
	else
	{
		m_tCurSelectViewInfo.Clear();
	}	

	return true;
}

bool CSrcSelWatchLogic::OnScreenSlectListItemClick(TNotifyUI& msg)
{
	if (-1 == m_wCurrentSelIndex)
	{
		return false;
	}
	
	u16 wIndex = msg.wParam;
	TSelViewInfo *pTSelViewInfo = NULL;
	if (m_bSearchEdit)
	{
		pTSelViewInfo = &m_vctSearchLst.at(m_wCurrentSelIndex);
	}
	else
	{
		pTSelViewInfo = &m_vctCnsInfoList.at(m_wCurrentSelIndex);
	}

	if (pTSelViewInfo)
	{
		pTSelViewInfo->m_wDstScrIndx = wIndex;
	}
	
	pTSelViewInfo = NULL;
	return true;
}

bool CSrcSelWatchLogic::OnBtnSetWatch1( TNotifyUI& msg )
{
	if (m_wCurrentSelIndex == -1)
	{
		ShowMessageBox(_T("请先选择选看会场"));
		return false;
	}

	if (!m_bIsGetScreenState)
	{
		m_bIsGetScreenState = true;
		UpdateSelList();
	}

	if ( m_vctSearchLst.size() == 0)
	{
		m_aSelWatch[0] = m_vctCnsInfoList.at(m_wCurrentSelIndex);
	}
	else
	{
		m_aSelWatch[0] = m_vctSearchLst.at(m_wCurrentSelIndex);
	}
	
	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("SelConfInfoList") );
	if ( pTileLayoutUI == NULL )
	{
		return false;
	}
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckShowSel") );
	if ( !pCheckBox )
	{
		return false;
	}

	CString str(m_aSelWatch[0].m_achRoomName);
	if ((EmEpType_Ter == m_aSelWatch[0].m_emType) && (3 == m_aSelWatch[0].m_wSpeakerNum)
		&& (m_aSelWatch[0].m_wDstScrIndx != TP_MAX_STREAMNUM) )
	{
		switch (m_aSelWatch[0].m_wDstScrIndx)
		{
		case 0:
			{
				str += _T("(左)");
			}
			break;
		case 1:
			{
				str += _T("(中)");
			}
			break;
		case 2:
			{
				str += _T("(右)");
			}
			break;
		}
	}
	CListContainerElementUI *pItem = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(0);
	if ( pCheckBox->IsSelected() )
	{
		ICncCommonOp::SetControlText( str, m_pm, _T("lbName"), pItem );
	}
	
	CControlUI* pControl = ICncCommonOp::FindControl(m_pm,_T("BtnShowSel"), pItem);
	if (pControl)
	{
		ICncCommonOp::SetTag(pControl, m_wCurrentSelIndex);
	}

	SetScreenWatch(0);
	return true;
}

bool CSrcSelWatchLogic::OnBtnSetWatch2( TNotifyUI& msg )
{
	if (m_wCurrentSelIndex == -1)
	{
		ShowMessageBox(_T("请先选择选看会场"));
		return false;
	}

	if (!m_bIsGetScreenState)
	{
		m_bIsGetScreenState = true;
		UpdateSelList();
	}

	if ( m_vctSearchLst.size() == 0)
	{
		m_aSelWatch[1] = m_vctCnsInfoList.at(m_wCurrentSelIndex);
	}
	else
	{
		m_aSelWatch[1] = m_vctSearchLst.at(m_wCurrentSelIndex);
	}

	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("SelConfInfoList") );
	if ( pTileLayoutUI == NULL )
	{
		return false;
	}
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckShowSel") );
	if ( !pCheckBox )
	{
		return false;
	}

	CString str(m_aSelWatch[1].m_achRoomName);
	if ((EmEpType_Ter == m_aSelWatch[1].m_emType) && (3 == m_aSelWatch[1].m_wSpeakerNum)
		&& (m_aSelWatch[1].m_wDstScrIndx != TP_MAX_STREAMNUM) )
	{
		switch (m_aSelWatch[1].m_wDstScrIndx)
		{
		case 0:
			{
				str += _T("(左)");
			}
			break;
		case 1:
			{
				str += _T("(中)");
			}
			break;
		case 2:
			{
				str += _T("(右)");
			}
			break;
		}
	}
	CListContainerElementUI *pItem = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(1);
	if ( pCheckBox->IsSelected() )
	{
		ICncCommonOp::SetControlText( str, m_pm, _T("lbName"), pItem );
	}

	CControlUI* pControl = ICncCommonOp::FindControl(m_pm,_T("BtnShowSel"), pItem);
	if (pControl)
	{
		ICncCommonOp::SetTag(pControl, m_wCurrentSelIndex);
	}
	SetScreenWatch(1);
	return true;
}

bool CSrcSelWatchLogic::OnBtnSetWatch3( TNotifyUI& msg )
{
	if (m_wCurrentSelIndex == -1)
	{
		ShowMessageBox(_T("请先选择选看会场"));
		return false;
	}

	if (!m_bIsGetScreenState)
	{
		m_bIsGetScreenState = true;
		UpdateSelList();
	}

	if ( m_vctSearchLst.size() == 0)
	{
		m_aSelWatch[2] = m_vctCnsInfoList.at(m_wCurrentSelIndex);
	}
	else
	{
		m_aSelWatch[2] = m_vctSearchLst.at(m_wCurrentSelIndex);
	}

	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("SelConfInfoList") );
	if ( pTileLayoutUI == NULL )
	{
		return false;
	}
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckShowSel") );
	if ( !pCheckBox )
	{
		return false;
	}
	
	CString str(m_aSelWatch[2].m_achRoomName);
	if ((EmEpType_Ter == m_aSelWatch[2].m_emType) && (3 == m_aSelWatch[2].m_wSpeakerNum)
		&& (m_aSelWatch[2].m_wDstScrIndx != TP_MAX_STREAMNUM) )
	{
		switch (m_aSelWatch[2].m_wDstScrIndx)
		{
		case 0:
			{
				str += _T("(左)");
			}
			break;
		case 1:
			{
				str += _T("(中)");
			}
			break;
		case 2:
			{
				str += _T("(右)");
			}
			break;
		}
	}
	CListContainerElementUI *pItem = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(2);
	if ( pCheckBox->IsSelected() )
	{
		ICncCommonOp::SetControlText( str, m_pm, _T("lbName"), pItem );
	}

	CControlUI* pControl = ICncCommonOp::FindControl(m_pm,_T("BtnShowSel"), pItem);
	if (pControl)
	{
		ICncCommonOp::SetTag(pControl, m_wCurrentSelIndex);
	}
	SetScreenWatch(2);
	return NO_ERROR;
}

bool CSrcSelWatchLogic::OnDragIsStart( TNotifyUI& msg )
{
    m_bIsDraging = true;
    return true;
}

bool CSrcSelWatchLogic::OnDragIsOver( TNotifyUI& msg )
{
    m_bIsDraging = false;
    if (m_bIsNeedUpdate)
    {
        UpdateCnsInfoList();
    }
    return true;
}

bool CSrcSelWatchLogic::OnDragDrop( TNotifyUI& msg )
{
	CListContainerElementUI* pItem = static_cast<CListContainerElementUI*>(msg.pSender);
	if (!pItem)
	{
		return false;
	}
	if (-1 == m_wCurrentSelIndex)
	{
		return false;
	}
	
	int nIndex = pItem->GetIndex();
	if (nIndex >= 3 || nIndex <0)
	{
		return false;
	}

	if (m_bSearchEdit)
	{
		m_aSelWatch[nIndex] = m_vctSearchLst.at(m_wCurrentSelIndex);
	}
	else
	{
		m_aSelWatch[nIndex] = m_vctCnsInfoList.at(m_wCurrentSelIndex);
	}
	
	//三屏会场区分拖的是整体还是三屏中的小屏
	if ((EmEpType_Ter == m_aSelWatch[nIndex].m_emType) && ( 3 == m_aSelWatch[nIndex].m_wSpeakerNum))
	{
		CDuiString strName = ((CControlUI*)msg.wParam)->GetName();
		if (strName == _T("SelWatchItem"))
		{
			m_aSelWatch[nIndex].m_wDstScrIndx = TP_MAX_STREAMNUM;
		}
	}
	
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckShowSel") );
	if ( !pCheckBox )
	{
		return false;
	}

	CString str(m_aSelWatch[nIndex].m_achRoomName);
	if ((EmEpType_Ter == m_aSelWatch[nIndex].m_emType) && (3 == m_aSelWatch[nIndex].m_wSpeakerNum)
		&& (m_aSelWatch[nIndex].m_wDstScrIndx != TP_MAX_STREAMNUM) )
	{
		switch (m_aSelWatch[nIndex].m_wDstScrIndx)
		{
		case 0:
			{
				str += _T("(左)");
			}
			break;
		case 1:
			{
				str += _T("(中)");
			}
			break;
		case 2:
			{
				str += _T("(右)");
			}
			break;
		}
	}

	if ( pCheckBox->IsSelected() )
	{
		ICncCommonOp::SetControlText( str, m_pm, _T("lbName"), pItem );
	}
	
	CControlUI* pControl = ICncCommonOp::FindControl(m_pm,_T("BtnShowSel"), pItem);
	if (pControl)
	{
		ICncCommonOp::SetTag(pControl, m_wCurrentSelIndex);
	}

	SetScreenWatch(nIndex);
	return NO_ERROR;
}

bool CSrcSelWatchLogic::OnDragEnter( TNotifyUI& msg )
{
	CListContainerElementUI* pItem = static_cast<CListContainerElementUI*>(msg.pSender);
	pItem->SetBkImage(_T("res\\list\\item_down.png"));
	return NO_ERROR;
}

bool CSrcSelWatchLogic::OnDragLeave( TNotifyUI& msg )
{
	CListContainerElementUI* pItem = static_cast<CListContainerElementUI*>(msg.pSender);
	pItem->SetBkImage(_T(""));
	return NO_ERROR;
}

bool CSrcSelWatchLogic::OnDragDone( TNotifyUI& msg )
{
	CListContainerElementUI* pItem = static_cast<CListContainerElementUI*>(msg.pSender);
	pItem->SetBkImage(_T(""));
	pItem->Select(true);
	return NO_ERROR;
}

void CSrcSelWatchLogic::UpdateSelList()
{
	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("SelConfInfoList") );
	if ( pTileLayoutUI == NULL )
	{
		return ;
	}

	for ( int i = 0; i <  3; i++ )
	{
		CListContainerElementUI *pListContainer = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(i);
		if (!pTileLayoutUI)
		{
			return ;
		}

		TScreenInfo tScrnInfo;
		u16 re = ComInterface->GetCnsScreenInfoByID( i, tScrnInfo );
		CString strName(tScrnInfo.achCnsName);

		if (strName.IsEmpty())
		{
			strName = _T("无选看");
		}
		ICncCommonOp::SetControlText( strName, m_pm, _T("lbName"), pListContainer );
		CControlUI* pControl = ICncCommonOp::FindControl(m_pm,_T("BtnShowSel"), pListContainer);
		if (!pControl)
		{
			return;
		}

		bool bIsIn = false;
		for(int j=0; j<m_vctCnsInfoList.size(); j++)
		{
			CString strConfName(m_vctCnsInfoList.at(j).m_achRoomName);
			if (strConfName == strName)
			{				
				ICncCommonOp::SetTag(pControl, j);
				bIsIn = true;
				break;	
			}
		}

		if (!bIsIn)
		{
			ICncCommonOp::SetTag(pControl, -1);
		}
	}
}

bool CSrcSelWatchLogic::OnLetterIndex( TNotifyUI& msg )
{
	vector<TSelViewInfo>  vctCnsInfoList; 
	if (m_vctSearchLst.size() != 0 )
	{
		vctCnsInfoList = m_vctSearchLst;
	}
	else
	{
		vctCnsInfoList = m_vctCnsInfoList;
	}

	if (vctCnsInfoList.size() == 0)
	{
		return false;
	}

	int nLetterIndex = (int)msg.wParam;
	CTouchListUI* pTouch = (CTouchListUI*)ICncCommonOp::FindControl(m_pm, _T("ConfInfoList"));
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
		UIDATAMGR->GetFirstLetter( vctCnsInfoList.at(swMidIndex).m_achRoomName, strLetter ); 

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

void CSrcSelWatchLogic::CancelSelWatch( int nIndex )
{
	CString str(m_aSelWatch[nIndex].m_achRoomName);
	if (m_aSelWatch[nIndex].m_wEpID == TP_INVALID_INDEX)
	{
		return;
	}

	TTPSelViewReq tTPSelViewReq;
	tTPSelViewReq.m_bSel = false;
	tTPSelViewReq.m_emType = m_aSelWatch[nIndex].m_emType;
	tTPSelViewReq.m_emUIType = EmUI_CNC;
	tTPSelViewReq.m_wConfID = m_aSelWatch[nIndex].m_wConfID;
	tTPSelViewReq.m_wScreenIndx = nIndex;
	tTPSelViewReq.m_wEpID = m_aSelWatch[nIndex].m_wEpID;
	tTPSelViewReq.m_wDstID = m_aSelWatch[nIndex].m_wDstID;
	tTPSelViewReq.m_wDstScrIndx = m_aSelWatch[nIndex].m_wDstScrIndx;

	u16 wRe = ComInterface->SetSelView( tTPSelViewReq);
	if ( wRe != NO_ERROR )
	{
		CString str;
		str.Format(_T("屏%取消选看设置失败"),nIndex);
		ShowMessageBox(str);
	}
}

bool CSrcSelWatchLogic::OnSelViewNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TTPSelViewNtfy tTPSelViewNtfy = ComInterface->GetSelWatchStatus();	

	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("SelConfInfoList") );
	if ( pTileLayoutUI == NULL )
	{
		return false;
	}
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckShowSel") );
	if ( !pCheckBox )
	{
		return false;
	}

	for (int i=0 ; i<TP_MAX_STREAMNUM; i++)
	{
		if ( !tTPSelViewNtfy.m_atSelView[i].IsValid())
		{
			m_aSelWatch[i].Clear();
		}
		else
		{
			if (!tTPSelViewNtfy.m_atSelView[i].m_bSel)//界面已经取消选看，更新选看列表状态
			{
				m_aSelWatch[i].Clear();
			}
			else
			{
				m_aSelWatch[i].m_emType = tTPSelViewNtfy.m_atSelView[i].m_emType;
				m_aSelWatch[i].m_wConfID = tTPSelViewNtfy.m_atSelView[i].m_wConfID;
				m_aSelWatch[i].m_wDstID = tTPSelViewNtfy.m_atSelView[i].m_wDstID;
				m_aSelWatch[i].m_wEpID = tTPSelViewNtfy.m_atSelView[i].m_wEpID;
				m_aSelWatch[i].m_wDstScrIndx = tTPSelViewNtfy.m_atSelView[i].m_wDstScrIndx;
			}
		}

		int nIndex = -1;
		for (int j=0; j<m_vctCnsInfoList.size(); j++)
		{
			/*if (m_vctCnsInfoList.size()<=i)
			{
			break;
			}*/

			if (tTPSelViewNtfy.m_atSelView[i].m_wDstID == m_vctCnsInfoList.at(j).m_wDstID)
			{
				m_aSelWatch[i].m_wSpeakerNum = m_vctCnsInfoList.at(j).m_wSpeakerNum;
				
				if (tTPSelViewNtfy.m_atSelView[i].m_emType == EmEpType_Ter)
				{
					memcpy(m_aSelWatch[i].m_achRoomName, m_vctCnsInfoList.at(j).m_achRoomName, TP_MAX_ALIAS_LEN);	
				}
				else
				{
					memcpy(m_aSelWatch[i].m_achRoomName, m_vctCnsInfoList.at(j).m_achRoomName,TP_MAXLEN_EQP_ALIAS);
				}
				
				nIndex = j;
				break;
			}
		}

		CListContainerElementUI *pItem = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(i);
		CString str(m_aSelWatch[i].m_achRoomName);
		if ( TP_MAX_STREAMNUM == tTPSelViewNtfy.m_atSelView[i].m_wScreenIndx)
		{
			str = _T("无选看");
		}
		else
		{
			if ((EmEpType_Ter == m_aSelWatch[i].m_emType) && (3 == m_aSelWatch[i].m_wSpeakerNum)
				 && (m_aSelWatch[i].m_wDstScrIndx != TP_MAX_STREAMNUM) )
			{
				switch (m_aSelWatch[i].m_wDstScrIndx)
				{
				case 0:
					{
						str += _T("(左)");
					}
					break;
				case 1:
					{
						str += _T("(中)");
					}
					break;
				case 2:
					{
						str += _T("(右)");
					}
					break;
				}
			}
		}
		if ( pCheckBox->IsSelected() )
		{
			ICncCommonOp::SetControlText( str, m_pm, _T("lbName"), pItem );
		}

		CControlUI* pControl = ICncCommonOp::FindControl(m_pm,_T("BtnShowSel"), pItem);
		if (pControl)
		{
			ICncCommonOp::SetTag(pControl, nIndex);
		}
	}

	//判断“取消选看”按钮是否显示--add by wangkui 2016-11-8
	bool bShow = false;
	for (int i=0 ; i<TP_MAX_STREAMNUM; i++)
	{
		if ( tTPSelViewNtfy.m_atSelView[i].IsValid() && tTPSelViewNtfy.m_atSelView[i].m_bSel)
		{
			bShow = true;
			break;
		}
	}
	if (m_bIsClickBtnCancelWatch && !bShow)
	{
		pTileLayoutUI->SelectItem(-1);
		m_bIsClickBtnCancelWatch = false;
	}
	ICncCommonOp::ShowControl( bShow, m_pm, _T("BtnCancelWatch") );

	return true;
}

bool CSrcSelWatchLogic::OnConfStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TCMSConf tConfInfo ;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo ); 

	if ( !bInConf  )//结会时清空并隐藏
	{	
		if (UIDATAMGR->GetCurShowWndName() == g_strSrcSelWatchDlg && WINDOW_MGR_PTR->IsWindowVisible(g_strSrcSelWatchDlg.c_str()))
		{
			WINDOW_MGR_PTR->ShowWindowFromLeftToRight( g_strSrcSelWatchDlg.c_str(), false );
			WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowCnsManage"));
			UIDATAMGR->SetCurShowWndName( _T("") );
		}

		OnDisconnect(wParam,lParam,bHandle);
	}

	return true;
}

bool CSrcSelWatchLogic::OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    ComInterface->ShowKeyboard();
    return true;
}