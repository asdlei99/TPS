#include "StdAfx.h"
#include "confrolllogic.h"
#include "audmixlogic.h"
#include "confmsglogic.h"
#include "cncstruct.h"

static UINT g_nRollSelTimerID;      //timer 的id,用于更新点名列表后的被点名者选中
static UINT g_nRollSelInterval;     //定时器时间间隔

template<> CConfRollLogic* Singleton<CConfRollLogic>::ms_pSingleton  = NULL;
APP_BEGIN_MSG_MAP(CConfRollLogic, CNotifyUIImpl)

	MSG_SELECTCHANGE(_T("CheckStartConfroll"), OnCheckConfRoll)
//	MSG_SELECTCHANGE(_T("CheckRollImpel"), OnCheckRollImpel)
	MSG_SELECTCHANGE(_T("CheckConfrollShortCut"), OnCheckConfRollShortCut)

	MSG_ITEMSELECTD(_T("RollList"), OnRollItemClicked)

	MSG_TIMER(_T("RollList"), OnTimerRollList)

	MSG_CLICK(_T("BtnSelect"), OnBtnItemSelect)
	MSG_CLICK(_T("BtnAttend"), OnBtnAttend)
	MSG_CLICK(_T("BtnAbsent"), OnBtnAbsent)	

	MSG_CLICK(_T("BtnSetLeftSpeaker"), OnBtnSetLeftSpeaker)
	MSG_CLICK(_T("BtnSetCenterSpeaker"), OnBtnSetCenterSpeaker)
	MSG_CLICK(_T("BtnSetRightSpeaker"), OnBtnSetRightSpeaker)

	MSG_CLICK(_T("BtnRollPSelOK"), OnBtnRollSelRoomOK)
	MSG_CLICK(_T("BtnRollPSelAll"), OnBtnRollSelAll)
	MSG_CLICK(_T("BtnRollPSelCancel"), OnBtnRollSelCancel)
	MSG_SELECTCHANGE(_T("BtnConfCnsSel"), OnCheckConfItem)

	MSG_EDITCHANGE(_T("EdtRollPSearch"), OnRollSearchEditChange)	

	MSG_CLICK(_T("BtnAddRoller"), OnBtnAddRoller)

	MSG_CLICK(_T("BtnRollAdd"), OnBtnAdd)
	MSG_CLICK(_T("BtnRollTop"), OnBtnRollTop)
	MSG_CLICK(_T("BtnRollUp"), OnBtnRollUp)
	MSG_CLICK(_T("BtnRollDown"), OnBtnRollDown)
	MSG_CLICK(_T("BtnRollBottom"), OnBtnRollBottom)
	MSG_CLICK(_T("BtnRollDel"), OnBtnRollDel)
	MSG_CLICK(_T("BtnPreConf"), OnBtnRollPre)
	MSG_CLICK(_T("BtnNextConf"), OnBtnRollNext)

	USER_MSG(UI_CNS_CONFROLLNEXT_IND,OnRollNextInd)
	USER_MSG(UI_CNS_CONFROLL_IND,OnRollStateInd)
	USER_MSG(UI_CNS_CONFROLL_NTY,OnRollStateNty)
	USER_MSG(UI_CNS_CONFROLL_ATTEND_NTY,OnRolleeAttendStateNty)
	USER_MSG(UI_DISCONNECTED_CLEARDATA, OnDisconnect)

	USER_MSG( UI_UMS_REFRESH_CONFCNS_LIST, OnRefreshCnsLstNotify )
	//修改被点名列表回复
	USER_MSG( UI_CNS_CONFROLL_LISTFIXED_IND, OnRollLstFixedInd )
	USER_MSG(UI_CNC_SHORTCUT_ROLL,OnShortCutRoll)
	//收到主席信息，直接设定为发言人
	USER_MSG( UI_CNS_CHAIRCONFINFO_NTY, OnChairNty )
	//退出会议 状态清空
	USER_MSG( UI_CNS_CONFSTATE_NOTIFY, OnConfStateNty )

APP_END_MSG_MAP()

CConfRollLogic::CConfRollLogic(void) 
{
	g_nRollSelTimerID  = 100;
	g_nRollSelInterval = 1;

	m_dwSelRollItemId = -1;
	m_bIsSelAll = false;
	m_bIsSearch = false;
	m_emSelConf = emSelConfNo;
	m_dwCallTargetItemId = -1;
}

CConfRollLogic::~CConfRollLogic(void)
{
}

bool CConfRollLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_dwSelRollItemId = -1;
	EnableRollBtn(false);
	m_bIsSelAll = false;
	m_emSelConf = emSelConfNo;
	m_bIsSearch = false;
	m_dwCallTargetItemId = -1;
	CEditUI* pEditSearch = (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("EdtPSearch") );
	if ( pEditSearch )
	{
		pEditSearch->SetText(_T(""));
	}
	m_vctSearchCnsList.clear();

	m_vctCnsList.clear();
	m_vctCnsNoChildList.clear();
	m_vctCurrentCnsList.clear();
	m_vctSelConf.clear();
	m_vctRollList.clear();
	UpdateCnsList();
	UpdateRollList(m_vctRollList);
	ICncCommonOp::ShowControl( false, m_pm, _T("PageRollSelConfList") );
	m_tTpConfRollCallInfo.Clear();
	m_tRollerInfo.Clear();
	CCheckBoxUI* pControl = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm, _T("CheckStartConfroll"));
	if (pControl)
	{
		pControl->SetCheckNoMsg(false);
	}
	ICncCommonOp::EnableControl( true, m_pm, _T("BtnAddRoller") );
	ICncCommonOp::SetControlText( _T("点名人"), m_pm, _T("lbRollerName"));
	//OspPrintf(TRUE,false,"m_tRollerInfo:OnDisconnect %d",m_tRollerInfo.m_wEpID);
	return true;
}

// bool CConfRollLogic::OnCheckRollImpel( TNotifyUI& msg )
// {
// 	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
// 	if ( !pCheckBox )
// 	{
// 		return false;
// 	}
// 
// 	bool bIsSet = false;
// 	if ( pCheckBox->IsSelected() )
// 	{
// 		bIsSet = true;
// 	}
// 
// 	ICncCommonOp::EnableControl(!bIsSet,m_pm,_T("BtnSetCenterSpeaker"));
// 	ICncCommonOp::EnableControl(!bIsSet,m_pm,_T("BtnSetLeftSpeaker"));
// 	ICncCommonOp::EnableControl(!bIsSet,m_pm,_T("BtnSetRightSpeaker"));
// 
// 	return true;
// }

//开启会议点名
bool CConfRollLogic::OnCheckConfRoll( TNotifyUI& msg )
{
	if (m_tRollerInfo.m_wEpID == TP_INVALID_INDEX)
	{
		bool bHandle = false;
		OnChairNty(NULL,NULL,bHandle);
		if (m_tRollerInfo.m_wEpID == TP_INVALID_INDEX)
		{
			ShowMessageBox(_T("请先设置点名人会场"));
			CCheckBoxUI *pControl = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckStartConfroll") );
			if (pControl)
			{
				pControl->SetCheckNoMsg(false);
			}
			return false;
		}
	}

	if (m_vctRollList.size() == 0)
	{
		ShowMessageBox(_T("无被点名人，开启点名失败"));
		CCheckBoxUI *pControl = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckStartConfroll") );
		if (pControl)
		{
			pControl->SetCheckNoMsg(false);
		}
		return false;
	}

	TCMSConf tConfInfo;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
	if ( ! bInConf )
	{
		ShowMessageBox(_T("不在会议中，不能进行点名设置"));
		return NO_ERROR;
	}

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

	TTpConfRollCallInfo tTpConfRollCallInfo;
	tTpConfRollCallInfo.m_bStart = bIsSet;
	tTpConfRollCallInfo.m_wConfID = tConfInfo.m_wConfID;

	TTpRollCallList tTpRollCallList;
	for(int i=0; i<m_vctRollList.size(); i++)
	{
		tTpRollCallList.AddRollCallTarget(m_vctRollList.at(i).m_wEpID);
	}

	tTpRollCallList.SetRollCaller(m_tRollerInfo.m_wEpID);
	tTpConfRollCallInfo.m_atRollCallMemList = tTpRollCallList;
	ComInterface->StartRoll(tTpConfRollCallInfo);
	return true;
}

bool CConfRollLogic::OnCheckConfRollShortCut( TNotifyUI& msg )
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

	EM_ShortcutType em = emShortcutCofRoll;
	NOTIFY_MSG( UI_CNC_SET_SHORTCUT_NTY, em, bIsSet );
	return true;
}

bool CConfRollLogic::OnRollStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	ComInterface->GetRollState( m_tTpConfRollCallInfo );
	TTpRollCallList tTpRollCallList = m_tTpConfRollCallInfo.m_atRollCallMemList;

	TCMSConf tConf;
	BOOL32 bInConf = ComInterface->IsInConf( &tConf );
	if ( !bInConf )
	{
		EnableRollBtn(true);
		return false;
	}

	//OspPrintf(TRUE,false,"m_tRollerInfo:OnRollStateNty begin %d",m_tRollerInfo.m_wEpID);
	//OspPrintf(TRUE,false,"m_tRollerInfo:OnRollStateNty tTpRollCallList.m_wRollCaller %d",tTpRollCallList.m_wRollCaller);
	if (tTpRollCallList.m_wRollCaller != TP_INVALID_INDEX)
	{
		TCnsInfo* tInfor = tConf.GetCnsInfoByID(tTpRollCallList.m_wRollCaller);
		if (tInfor != NULL)
		{
			m_tRollerInfo = *(TCnsInfo*)tConf.GetCnsInfoByID(tTpRollCallList.m_wRollCaller);
			ICncCommonOp::EnableControl(true,m_pm,_T("CheckStartConfroll"));
			ICncCommonOp::SetControlText( CA2T(m_tRollerInfo.m_achRoomName), m_pm, _T("lbRollerName"));
            if (m_tRollerInfo.m_emEpType != emTPEndpointTypeCNS)
            {
                ICncCommonOp::SetControlBkImg(_T("res/list/imgOrdinary.png"), m_pm, _T("UserItemPic"));
            }
            else
            {
                ICncCommonOp::SetControlBkImg(_T("res/confctrl/confroll/roller.png"), m_pm, _T("UserItemPic"));
            }
			//OspPrintf(TRUE,false,"m_tRollerInfo:OnRollStateNty %d",m_tRollerInfo.m_wEpID);
		}
	}
	else
	{
		if (!m_tTpConfRollCallInfo.m_bStart)//关闭了点名 点名者变为默认 与umc统一 2017-2-20
		{
			m_tRollerInfo.Clear();
		}
		OnChairNty(wParam,lParam,bHandle);
	}

	//添加umc选中被点名人的时候 cnc同步当前被点名的人 界面上面当前选中的被点名人进行切换 gy添加通知 2016-11-29
	//nty收到列表刷新 被选中条目id为-1
	//m_dwSelRollItemId = -1;//防止选中项重新定位后会跳回来
	m_dwCallTargetItemId = -1;
	u16 wCallTarget = m_tTpConfRollCallInfo.m_atRollCallMemList.GetRollCallTarget();//当前被点名人

	m_vctRollList.clear();
	for (int i=0; i<tTpRollCallList.m_wNum; i++)
	{
		TRolleeState tRolleeState;
		tRolleeState.m_wEpID = tTpRollCallList.m_awList[i];
		TCnsInfo* tCnsInfo = tConf.GetCnsInfoByID(tTpRollCallList.m_awList[i]);
		if (tCnsInfo != NULL)
		{
			tRolleeState.m_bOnline = tCnsInfo->m_bOnline;
			memcpy(tRolleeState.m_achRoomName, tCnsInfo->m_achRoomName,sizeof(tCnsInfo->m_achRoomName));
            tRolleeState.m_emEpType = tCnsInfo->m_emEpType;

			m_vctRollList.push_back(tRolleeState);
			if (wCallTarget != TP_INVALID_INDEX && tTpRollCallList.m_awList[i] == wCallTarget)
			{
				m_dwCallTargetItemId = m_vctRollList.size()-1;
				//m_dwSelRollItemId = m_vctRollList.size()-1;
			}
		}
	}

	EmRollCallRspRet em = (EmRollCallRspRet)m_tTpConfRollCallInfo.m_emRet;

	CString strError;
	switch(em)
	{
	case em_Error_StopRollCall:
		{
			strError = _T("出错，终止点名");
		}
		break;
	case em_RollCallMixer_Error:
		{
			strError = _T("点名混音出错，终止点名");
		}
		break;
	case em_RollCaller_OffLine:
		{
			strError = _T("点名者掉线，终止点名");
		}
		break;
	case em_RollCallTarget_OffLine:
		{
			strError = _T("被点者掉线");//wtj确认
		}
		break;
	case em_CallTarget_ReConnect_Success://wtj确认
		{
			strError = _T("被点名者重新连接成功");
		}
		break;
	case em_Chair_ReConnect_notice:
		{
			strError = _T("主席掉线后重新上线，点名状态同步");
		}
		break;
	default:
		break;
	}

	if (!strError.IsEmpty())
	{
		ShowPopMsg(strError);
	}

	CCheckBoxUI* pControl = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm, _T("CheckStartConfroll"));
	if (pControl)
	{
		if (pControl->GetCheck() != m_tTpConfRollCallInfo.m_bStart)
		{
			pControl->SetCheckNoMsg(m_tTpConfRollCallInfo.m_bStart);
		}

	}

	//开启成功后，调整按钮不可用，加入一直可用
	if (m_tTpConfRollCallInfo.m_bStart)
	{
		EnableRollBtn(false);
		ICncCommonOp::EnableControl( false, m_pm, _T("BtnAddRoller") );	
	}
	else
	{
		ICncCommonOp::EnableControl( true, m_pm, _T("BtnAddRoller") );	
	}

	//更新与会状态后直接更新了列表
	OnRolleeAttendStateNty(wParam,lParam,bHandle);

	if (m_dwSelRollItemId == -1)
	{
		return S_OK;
	}

	CListUI* pRollList = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("RollList"));
	if ( pRollList != NULL )
	{
		CListContainerElementUI *pListContainer = (CListContainerElementUI*)pRollList->GetItemAt(m_dwSelRollItemId);
		if (pListContainer != NULL && m_dwCallTargetItemId == m_dwSelRollItemId )
		{
			ICncCommonOp::ShowControl(false, m_pm, _T("BtnSelect"),pListContainer);
			ICncCommonOp::ShowControl(true, m_pm, _T("RollCtrl"),pListContainer);
			ICncCommonOp::ShowControl(false, m_pm, _T("ctrlpos"),pListContainer);
		}
		//pRollList->SelectItem(m_dwSelRollItemId);
		m_pm->SetTimer(pRollList,g_nRollSelTimerID,g_nRollSelInterval);
	}

	return S_OK;
}

bool CConfRollLogic::OnRolleeAttendStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	//if (lParam == NULL && wParam == NULL)
	{
		TTpRollCallPresentStateMsg tTpRollCallPresentStateMsg;
		ComInterface->GetRollAttendState( tTpRollCallPresentStateMsg );
		if( tTpRollCallPresentStateMsg.m_wValidNum != 0 )
		{
			for (int i=0; i<m_vctRollList.size(); i++)//wtj确认 第一次登陆发送两个nty的会议列表顺序是对应的 先发点名状态nty后发与会状态nty
			{
				if (m_vctRollList.at(i).m_wEpID == tTpRollCallPresentStateMsg.m_atEpState[i].m_wEpID)
				{
					EMAttend eMAttend = emAttendNo;
					if (tTpRollCallPresentStateMsg.m_atEpState[i].m_wEpState == em_RollCallPresentState_Ok)
					{
						eMAttend = emAttend;
					}
					else if (tTpRollCallPresentStateMsg.m_atEpState[i].m_wEpState == em_RollCallPresentState_Absent )
					{
						eMAttend = emAbsent;
					}
					m_vctRollList.at(i).m_emAttend = eMAttend;
				}
				else//如果没有对应相等
				{
					//两遍循环
					for (int j=0; j<tTpRollCallPresentStateMsg.m_wValidNum; j++)
					{
						if (m_vctRollList.at(i).m_wEpID == tTpRollCallPresentStateMsg.m_atEpState[j].m_wEpID)
						{
							EMAttend eMAttend = emAttendNo;
							if (tTpRollCallPresentStateMsg.m_atEpState[j].m_wEpState == em_RollCallPresentState_Ok)
							{
								eMAttend = emAttend;
							}
							else if (tTpRollCallPresentStateMsg.m_atEpState[i].m_wEpState == em_RollCallPresentState_Absent )
							{
								eMAttend = emAbsent;
							}

							m_vctRollList.at(i).m_emAttend = eMAttend;
							break;
						}
					}

				}
			}
		}

		UpdateRollList(m_vctRollList);
		CListUI* pRollList = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("RollList"));
		if ( pRollList != NULL && m_dwSelRollItemId != -1)
		{
			//pRollList->SelectItem(m_dwSelRollItemId);
			m_pm->SetTimer(pRollList,g_nRollSelTimerID,g_nRollSelInterval);
		}
	}
// 	else //改成都更新全部列表 2016-11-29 
// 	{
// 		u16 wEpID = wParam;
// 		EmRollCallPresentState em = (EmRollCallPresentState)lParam;
// 
// 		EMAttend eMAttend = emAttendNo;
// 		bool bChange = true;
// 		//更新单个状态
// 		int dwItemID = -1;
// 		for (int i=0; i<m_vctRollList.size(); i++)
// 		{
// 			if (m_vctRollList.at(i).m_wEpID == wEpID)
// 			{
// 				dwItemID = i;
// 				
// 				if (em == em_RollCallPresentState_Ok)
// 				{
// 					eMAttend = emAttend;
// 				}
// 				else  if (em == em_RollCallPresentState_Absent )
// 				{
// 					eMAttend = emAbsent;
// 				}
// 
// 				if (m_vctRollList.at(i).m_emAttend != eMAttend)//状态改变了
// 				{
// 					m_vctRollList.at(i).m_emAttend = eMAttend;
// 				}
// 				else//状态没改变 不处理
// 				{
// 					return false;
// 				}
// 
// 				break;
// 			}
// 		}
// 
// 		if (dwItemID != -1)
// 		{
// 			UpdateRollItem(dwItemID,eMAttend);
// 		}
// 	}

	return true;
}

bool CConfRollLogic::OnRollNextInd(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	u16 wCallTarget = wParam;
	EmRollCallRspRet em = (EmRollCallRspRet)lParam;

	CString strError;
	switch(em)
	{
		// 开启点名的结果，注：关闭点名，只回复Ok或者OtherFail
	case em_StartRollCall_AssignMixFail:
		{
			strError = _T("资源不足，开启点名失败");
		}
		break;
	case em_StartRollCall_ConfAudMixMode:
		{
			strError = _T("混音已开启，开启点名失败，请关闭混音");
		}
		break;
	case em_StartRollCall_DisMode:
		{
			strError = _T("讨论已开启，开启点名失败，请关闭讨论");
		}
		break;
	case em_StartRollCall_AlreadyStart:
		{
			strError = _T("重复开启点名，当前已是点名模式");
		}
		break;
	case em_StartRollCall_AssignAddrFail:
		{
			strError = _T("点名开启失败，申请地址错误，不能开启点名");
		}
		break;
	case em_StartRollCall_NotTopUms:
		{
			strError = _T("当前操作的不是顶级UMS，操作无效");
		}
		break;
	case em_StartRollCall_CreateChanFail:
		{
			strError = _T("上调点名者音频或PUT点名者音频失败,不能开启点名");
		}
		break;
	case em_StartRollCall_OtherFail:
		{
			strError = _T("终止点名");
		}
		break;
	case em_UpdateRollCalList_ListFull:
		{
			strError = _T("更新点名列表点名列表满");
		}
		break;
	case em_UpdateRollCalList_NotTopUms:
		{
			strError = _T("更新点名列表，当前操作的不是顶级UMS，操作无效");
		}
		break;
	case em_UpdateRollCalList_InvalidEp:
		{
			strError = _T("更新点名列表, 无效会场");
		}
		break;
	case em_UpdateRollCalList_EpoffLine:
		{
			strError = _T("更新点名列表, 会场不在线");
		}
		break;
	case em_UpdateRollCalList_Fail:
		{
			strError = _T("更新点名列表出错，不能开启点名");
		}
		break;
	case em_RollCallNextEp_NotStart:
		{
			strError = _T("点名下一个时，尚未开启点名模式，操作无效");
		}
		break;
	case em_RollCallNextEp_NotTopUms:
		{
			strError = _T("点名下一个时，当前操作的不是顶级UMS，操作无效");
		}
		break;
	case em_RollCallNextEp_CallerChg:
		{
			strError = _T("点名下一个时，点名者发生了变化，终止点名");
		}
		break;
	case em_RollCallNextEp_EpError:
		{
			strError = _T("点名下一个时，会场错误，终止点名");
		}
		break;
	case em_RollCallNextEp_CreateChanFail:
		{
			strError = _T("上调被名者音频或PUT被名者音频失败，退出点名");
		}
		break;
	case em_RollCallNextEp_OtherFail:
		{
			strError = _T("系统异常");
		}
		break;

	default:
		break;
	}

	if (!strError.IsEmpty())
	{
		ShowPopMsg(strError);
	}

	return S_OK;
}


bool CConfRollLogic::OnRollStateInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL32 bStartRoll = wParam;
	EmRollCallRspRet em = (EmRollCallRspRet)lParam;

	CString strError;
	switch(em)
	{
		// 开启点名的结果，注：关闭点名，只回复Ok或者OtherFail
	case em_StartRollCall_AssignMixFail:
		{
			strError = _T("资源不足，开启点名失败");
		}
		break;
	case em_StartRollCall_ConfAudMixMode:
		{
			strError = _T("混音已开启，开启点名失败，请关闭混音");
		}
		break;
	case em_StartRollCall_DisMode:
		{
			strError = _T("讨论已开启，开启点名失败，请关闭讨论");
		}
		break;
	case em_StartRollCall_AlreadyStart:
		{
			strError = _T("重复开启点名，当前已是点名模式");
		}
		break;
	case em_StartRollCall_AssignAddrFail:
		{
			strError = _T("点名开启失败，申请地址错误，不能开启点名");
		}
		break;
	case em_StartRollCall_NotTopUms:
		{
			strError = _T("当前操作的不是顶级UMS，操作无效");
		}
		break;
	case em_StartRollCall_CreateChanFail:
		{
			strError = _T("上调点名者音频或PUT点名者音频失败,不能开启点名");
		}
		break;
	case em_StartRollCall_OtherFail:
		{
			strError = _T("终止点名");
		}
		break;
	case em_UpdateRollCalList_ListFull:
		{
			strError = _T("更新点名列表点名列表满");
		}
		break;
	case em_UpdateRollCalList_NotTopUms:
		{
			strError = _T("更新点名列表，当前操作的不是顶级UMS，操作无效");
		}
		break;
	case em_UpdateRollCalList_InvalidEp:
		{
			strError = _T("更新点名列表, 无效会场");
		}
		break;
	case em_UpdateRollCalList_EpoffLine:
		{
			strError = _T("更新点名列表, 会场不在线");
		}
		break;
	case em_UpdateRollCalList_Fail:
		{
			strError = _T("更新点名列表出错，不能开启点名");
		}
		break;
	case em_RollCallNextEp_NotStart:
		{
			strError = _T("点名下一个时，尚未开启点名模式，操作无效");
		}
		break;
	case em_RollCallNextEp_NotTopUms:
		{
			strError = _T("点名下一个时，当前操作的不是顶级UMS，操作无效");
		}
		break;
	case em_RollCallNextEp_CallerChg:
		{
			strError = _T("点名下一个时，点名者发生了变化，终止点名");
		}
		break;
	case em_RollCallNextEp_EpError:
		{
			strError = _T("点名下一个时，会场错误，终止点名");
		}
		break;
	case em_RollCallNextEp_CreateChanFail:
		{
			strError = _T("上调被名者音频或PUT被名者音频失败，退出点名");
		}
		break;
	case em_RollCallNextEp_OtherFail:
		{
			strError = _T("系统异常");
		}
		break;

	default:
		break;
	}

	if (!strError.IsEmpty())
	{
		ShowPopMsg(strError);
	}

	CCheckBoxUI* pControl = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm, _T("CheckStartConfroll"));
	if (pControl)
	{
		if (pControl->GetCheck() != bStartRoll)
		{
			pControl->SetCheckNoMsg(bStartRoll);
		}

	}

	return true;
}

void CConfRollLogic::UpdateRollList(vector<TRolleeState>  vctRollList)
{
	TCMSConf tCMSConf;
	BOOL32 bIsInconf = ComInterface->IsInConf(&tCMSConf); 
	CListUI* pRollList = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("RollList"));
	if ( pRollList == NULL )
	{
		return ;
	}

	TRolleeState ptCnsInfo;
	CString strRoomName = _T("");
	CString strNum = _T("");
	pRollList->RemoveAll();

	if (!bIsInconf)
	{
		return;
	}

	for ( u16 i = 0; i < vctRollList.size(); i++ )
	{
		CListContainerElementUI *pListContainer = 
			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("RollistItem"));
		ptCnsInfo = vctRollList.at(i);
		strRoomName = ptCnsInfo.m_achRoomName;
		strNum.Format(_T("%d"),i+1);
		ICncCommonOp::SetControlText( strRoomName, m_pm, _T("lbRollName"), pListContainer );

        if (ptCnsInfo.m_emEpType != emTPEndpointTypeCNS)
        {
            ICncCommonOp::SetControlBkImg(_T("res/list/imgOrdinary.png"), m_pm, _T("lbicom"),pListContainer);
        }

		if (ptCnsInfo.m_emAttend == emAttend)
		{
			ICncCommonOp::SetControlBkImg(_T("res/confctrl/confroll/attend.png"), m_pm, _T("lbstateicon"),pListContainer);
		}
		else if (ptCnsInfo.m_emAttend == emAbsent)
		{
			ICncCommonOp::SetControlBkImg(_T("res/confctrl/confroll/absent.png"), m_pm, _T("lbstateicon"),pListContainer);
		}
		else
		{
			ICncCommonOp::SetControlBkImg(_T(""), m_pm, _T("lbstateicon"),pListContainer);
		}

		if (!ptCnsInfo.m_bOnline)
		{
			pListContainer->SetAttribute(_T("bkcolor"), _T("#FF40546C"));
		}

		pRollList->Add(pListContainer);
	}
}

void CConfRollLogic::UpdateRollList( EMRollItemMoveMode emMode )
{
	CListUI* pRollList = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("RollList"));
	if ( pRollList == NULL )
	{
		return ;
	}

	if (emMode == emRollMoveTop)
	{
		m_dwSelRollItemId = 0;
		UpdateRollList(m_vctRollList);
	}
	else if ( emMode == emRollMoveBottom)
	{
		m_dwSelRollItemId = m_vctRollList.size() - 1;
		UpdateRollList(m_vctRollList);
	}
	else
	{
		CListContainerElementUI *pListContainerOri = (CListContainerElementUI*)pRollList->GetItemAt(m_dwSelRollItemId);
		if (pListContainerOri == NULL)
		{
			return;
		}
		if (m_vctRollList.at(m_dwSelRollItemId).m_bOnline)
		{
			pListContainerOri->SetAttribute(_T("bkcolor"), _T(""));
		}
		else
		{
			pListContainerOri->SetAttribute(_T("bkcolor"), _T("#FF40546C"));
		}

		if (emMode == emRollMoveUp)
		{
			m_dwSelRollItemId = m_dwSelRollItemId - 1;
		}
		if (emMode == emRollMoveDown)
		{
			m_dwSelRollItemId = m_dwSelRollItemId + 1;
		}

		if (emMode == emRollPre)
		{
			if (m_dwSelRollItemId == 0)
			{
				m_dwSelRollItemId = m_vctRollList.size()-1;
			}
			else
			{
				m_dwSelRollItemId = m_dwSelRollItemId - 1;
			}

			int dwSelIndex = m_dwSelRollItemId;
			while(!m_vctRollList.at(dwSelIndex).m_bOnline)//上一个会场已经掉线，跳过
			{
				dwSelIndex --;//直接点名上一个在线的
				if (dwSelIndex == -1)//向上没有在线的，保持不动
				{
					break;
				}
			}

			if (dwSelIndex != -1)
			{
				m_dwSelRollItemId = dwSelIndex;
			}

		}
		if (emMode == emRollNext)
		{
			if (m_dwSelRollItemId == m_vctRollList.size()-1)
			{
				m_dwSelRollItemId = 0;
			}
			else
			{
				m_dwSelRollItemId = m_dwSelRollItemId + 1;
			}

			int dwSelIndex = m_dwSelRollItemId;
			while(!m_vctRollList.at(dwSelIndex).m_bOnline)//下一个会场已经掉线，跳过
			{
				dwSelIndex ++;//直接点名下一个在线的
				if (dwSelIndex == m_vctRollList.size())//向下没有在线的，保持不动
				{
					dwSelIndex = -1;
					break;
				}
			}
			if (dwSelIndex != -1)
			{
				m_dwSelRollItemId = dwSelIndex;
			}
		}

		CListContainerElementUI *pListContainerSel = (CListContainerElementUI*)pRollList->GetItemAt(m_dwSelRollItemId);
		if (pListContainerSel == NULL)
		{
			return;
		}
		//先不选中,等收到更新状态消息再选中
		if ( emMode == emRollPre || emMode == emRollNext)
		{
// 			pRollList->SelectItem(m_dwSelRollItemId);
// 			RollOther(pListContainerOri,pListContainerSel);
			EnableRollBtn(false);//防止连续点击点名按钮
			return;
		}

		if (m_vctRollList.at(m_dwSelRollItemId).m_bOnline)
		{
			pListContainerSel->SetAttribute(_T("bkcolor"), _T(""));
		}
		else
		{
			pListContainerSel->SetAttribute(_T("bkcolor"), _T("#FF40546C"));
		}

		String strSel = ICncCommonOp::GetControlText(m_pm, _T("lbRollName"), pListContainerSel );
		String strOri = ICncCommonOp::GetControlText(m_pm, _T("lbRollName"), pListContainerOri );

		ICncCommonOp::SetControlText( strOri.c_str(), m_pm, _T("lbRollName"), pListContainerSel );
		ICncCommonOp::SetControlText( strSel.c_str(), m_pm,  _T("lbRollName"), pListContainerOri );
	}
	//pRollList->SelectItem(m_dwSelRollItemId);
	m_pm->SetTimer(pRollList,g_nRollSelTimerID,g_nRollSelInterval);

}

void CConfRollLogic::UpdateRoller()
{
	if (m_tRollerInfo.m_wEpID != TP_INVALID_INDEX)
	{
		ICncCommonOp::EnableControl(true,m_pm,_T("CheckStartConfroll"));
		ICncCommonOp::SetControlText( CA2T(m_tRollerInfo.m_achRoomName), m_pm, _T("lbRollerName"));
        if (m_tRollerInfo.m_emEpType != emTPEndpointTypeCNS)
        {
            ICncCommonOp::SetControlBkImg(_T("res/list/imgOrdinary.png"), m_pm, _T("UserItemPic"));
        }
        else
        {
            ICncCommonOp::SetControlBkImg(_T("res/confctrl/confroll/roller.png"), m_pm, _T("UserItemPic"));
        }
		//OspPrintf(TRUE,false,"m_tRollerInfo:UpdateRoller m_tRollerInfo.m_wEpID != TP_INVALID_INDEX  %d",m_tRollerInfo.m_wEpID);
		return;
	}

	ComInterface->GetRollState( m_tTpConfRollCallInfo );
	TTpRollCallList tTpRollCallList = m_tTpConfRollCallInfo.m_atRollCallMemList;

	TCMSConf tConf;
	BOOL32 bInConf = ComInterface->IsInConf( &tConf );
	if ( !bInConf )
	{
		return;
	}

	if (tTpRollCallList.m_wRollCaller != TP_INVALID_INDEX)
	{
		TCnsInfo* tInfor = tConf.GetCnsInfoByID(tTpRollCallList.m_wRollCaller);
		if (tInfor != NULL)
		{
			m_tRollerInfo = *(TCnsInfo*)tConf.GetCnsInfoByID(tTpRollCallList.m_wRollCaller);
			ICncCommonOp::EnableControl(true,m_pm,_T("CheckStartConfroll"));
			ICncCommonOp::SetControlText( CA2T(m_tRollerInfo.m_achRoomName), m_pm, _T("lbRollerName"));
            if (m_tRollerInfo.m_emEpType != emTPEndpointTypeCNS)
            {
                ICncCommonOp::SetControlBkImg(_T("res/list/imgOrdinary.png"), m_pm, _T("UserItemPic"));
            }
            else
            {
                ICncCommonOp::SetControlBkImg(_T("res/confctrl/confroll/roller.png"), m_pm, _T("UserItemPic"));
            }
			//OspPrintf(TRUE,false,"m_tRollerInfo: UpdateRoller tTpRollCallList.m_wRollCaller != TP_INVALID_INDEX %d %d",tTpRollCallList.m_wRollCaller,m_tRollerInfo.m_wEpID);
		}
	}
	else
	{
		bool bHandle = FALSE;
		OnChairNty(NULL,NULL,bHandle);
	}
}

void CConfRollLogic::UpdateRollItem(u32 wItemID, EMAttend eMAttend)
{
	CListUI* pRollList = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("RollList"));
	if ( pRollList == NULL )
	{
		return ;
	}

	CListContainerElementUI *pListContainer = (CListContainerElementUI*)pRollList->GetItemAt(wItemID);
	if (pListContainer == NULL)
	{
		return;
	}

	if (eMAttend == emAttend)
	{
		ICncCommonOp::SetControlBkImg(_T("res/confctrl/confroll/attend.png"), m_pm, _T("lbstateicon"),pListContainer);
	}
	else if (eMAttend == emAbsent)
	{
		ICncCommonOp::SetControlBkImg(_T("res/confctrl/confroll/absent.png"), m_pm, _T("lbstateicon"),pListContainer);
	}
	else
	{
		ICncCommonOp::SetControlBkImg(_T(""), m_pm, _T("lbstateicon"),pListContainer);
	}
}

//直接点名上一个或者下一个
void CConfRollLogic::RollOther(CListContainerElementUI *pOri, CListContainerElementUI *pCur)
{
	ICncCommonOp::ShowControl(false, m_pm, _T("BtnSelect"),pOri);
	ICncCommonOp::ShowControl(false, m_pm, _T("RollCtrl"),pOri);
	ICncCommonOp::ShowControl(true, m_pm, _T("ctrlpos"),pOri);

	ICncCommonOp::ShowControl(true, m_pm, _T("RollCtrl"),pCur);
	ICncCommonOp::ShowControl(false, m_pm, _T("ctrlpos"),pCur);
	ICncCommonOp::ShowControl(false, m_pm, _T("BtnSelect"),pCur);
}

bool CConfRollLogic::OnBtnSetLeftSpeaker(TNotifyUI& msg)
{
	return true;
}

bool CConfRollLogic::OnBtnSetCenterSpeaker(TNotifyUI& msg)
{
	return true;
}

bool CConfRollLogic::OnBtnSetRightSpeaker(TNotifyUI& msg)
{
	return true;
}

bool CConfRollLogic::OnRollItemClicked( TNotifyUI& msg )
{
	m_dwSelRollItemId = msg.wParam;

	EnableRollBtn(true);

	s32 dwPreItemId = msg.lParam;

	CListUI* pRollList = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("RollList"));
	if ( pRollList == NULL )
	{
		return false;
	}

	CListContainerElementUI *pListContainerSel = (CListContainerElementUI*)pRollList->GetItemAt(m_dwSelRollItemId);
	if (pListContainerSel == NULL)
	{
		return false;
	}

	ICncCommonOp::SetControlBkImg(_T("res/confctrl/confroll/icon_sel.png"), m_pm, _T("lbicom"),pListContainerSel );
	if ( m_tTpConfRollCallInfo.m_bStart && m_vctRollList.at(m_dwSelRollItemId).m_bOnline)//开启点名并且会场在线才显示点名按钮
	{
		if (m_dwSelRollItemId == m_dwCallTargetItemId)
		{
			ICncCommonOp::ShowControl(false, m_pm, _T("BtnSelect"),pListContainerSel);
			ICncCommonOp::ShowControl(true, m_pm, _T("RollCtrl"),pListContainerSel);
		}
		else
		{
			ICncCommonOp::ShowControl(true, m_pm, _T("BtnSelect"),pListContainerSel);
			ICncCommonOp::ShowControl(false, m_pm, _T("RollCtrl"),pListContainerSel);
		}

		ICncCommonOp::ShowControl(false, m_pm, _T("ctrlpos"),pListContainerSel);
	}

	CListContainerElementUI *pListContainerOri = (CListContainerElementUI*)pRollList->GetItemAt(dwPreItemId);
	if (pListContainerOri == NULL)
	{
		return false;
	}
	ICncCommonOp::SetControlBkImg(_T("res/confctrl/confroll/icon.png"), m_pm, _T("lbicom"),pListContainerOri);
	ICncCommonOp::ShowControl(false, m_pm, _T("BtnSelect"),pListContainerOri);
	ICncCommonOp::ShowControl(false, m_pm, _T("RollCtrl"),pListContainerOri);
	ICncCommonOp::ShowControl(true, m_pm, _T("ctrlpos"),pListContainerOri);

	return true;
}

bool CConfRollLogic::OnTimerRollList(TNotifyUI& msg)
{
	if (msg.wParam == g_nRollSelTimerID)
	{
		m_pm->KillTimer(msg.pSender, g_nRollSelTimerID);
		CListUI* pRollList = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("RollList"));
		if ( pRollList != NULL && m_dwSelRollItemId != -1)
		{
			pRollList->SelectItem(m_dwSelRollItemId);
			//pRollList->EnsureVisible(m_dwSelRollItemId);
		}
	}
	return true;
}

void CConfRollLogic::EnableRollBtn( bool bIsEnable )
{
	if ( !m_tTpConfRollCallInfo.m_bStart )
	{
		ICncCommonOp::EnableControl( bIsEnable, m_pm,  _T("BtnRollTop") );
		ICncCommonOp::EnableControl( bIsEnable, m_pm,  _T("BtnRollUp") );
		ICncCommonOp::EnableControl( bIsEnable, m_pm,  _T("BtnRollDown") );
		ICncCommonOp::EnableControl( bIsEnable, m_pm,  _T("BtnRollBottom") );
		ICncCommonOp::EnableControl( bIsEnable, m_pm,  _T("BtnRollDel") );	

		ICncCommonOp::EnableControl( false, m_pm,  _T("BtnPreConf") );
		ICncCommonOp::EnableControl( false, m_pm,  _T("BtnNextConf") );
	}
	else
	{
		ICncCommonOp::EnableControl( bIsEnable, m_pm,  _T("BtnPreConf") );
		ICncCommonOp::EnableControl( bIsEnable, m_pm,  _T("BtnNextConf") );

		ICncCommonOp::EnableControl( false, m_pm,  _T("BtnRollTop") );
		ICncCommonOp::EnableControl( false, m_pm,  _T("BtnRollUp") );
		ICncCommonOp::EnableControl( false, m_pm,  _T("BtnRollDown") );
		ICncCommonOp::EnableControl( false, m_pm,  _T("BtnRollBottom") );
		ICncCommonOp::EnableControl( false, m_pm,  _T("BtnRollDel") );	
	}
}

bool CConfRollLogic::OnBtnAddRoller( TNotifyUI& msg )
{
	ICncCommonOp::SetControlText(_T(""), m_pm, _T("EdtRollPSearch"));
	m_vctSearchCnsList.clear();
	m_bIsSearch = false;
	m_emSelConf = emSelConfRoller;
	m_bIsSelAll = false;
	m_vctSelConf.clear();

	UpdateCnsList();

	ICncCommonOp::ShowControl( true, m_pm, _T("PageRollSelConfList") );
	ICncCommonOp::ShowControl(false,m_pm,_T("BtnRollPSelAll"));
	return true;
}

bool CConfRollLogic::OnBtnAdd( TNotifyUI& msg )
{
	ICncCommonOp::SetControlText(_T(""), m_pm, _T("EdtRollPSearch"));
	m_vctSearchCnsList.clear();
	m_bIsSearch = false;
	m_emSelConf = emSelConfRollee;
	m_bIsSelAll = false;
	m_vctSelConf.clear();

	UpdateCnsList();

	ICncCommonOp::ShowControl(true,m_pm,_T("BtnRollPSelAll"));
	ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnRollPSelAll"));
	ICncCommonOp::ShowControl( true, m_pm, _T("PageRollSelConfList") );
	return true;
}

bool CConfRollLogic::OnBtnRollTop( TNotifyUI& msg )
{
	if(m_dwSelRollItemId == -1 || m_vctRollList.size() <= 1 ||  m_dwSelRollItemId == 0)
	{
		return false;
	}

	TRolleeState tRolleeState = m_vctRollList.at(m_dwSelRollItemId);
	m_vctRollList.erase(m_vctRollList.begin() + m_dwSelRollItemId);
	m_vctRollList.insert(m_vctRollList.begin(),tRolleeState);

	UpdateRollList(emRollMoveTop);
	return true;
}

bool CConfRollLogic::OnBtnRollUp( TNotifyUI& msg )
{
	if(m_dwSelRollItemId == -1 || m_vctRollList.size() <= 1 || m_dwSelRollItemId == 0)
	{
		return false;
	}

	TRolleeState tRolleeState = m_vctRollList.at(m_dwSelRollItemId);
	m_vctRollList.erase(m_vctRollList.begin() + m_dwSelRollItemId);
	m_vctRollList.insert(m_vctRollList.begin() + m_dwSelRollItemId - 1,tRolleeState);

	UpdateRollList(emRollMoveUp);

	return true;
}

bool CConfRollLogic::OnBtnRollDown( TNotifyUI& msg )
{
	if(m_dwSelRollItemId == -1 || m_vctRollList.size() <= 1 || m_dwSelRollItemId == m_vctRollList.size()-1)
	{
		return false;
	}

	TRolleeState tRolleeState = m_vctRollList.at(m_dwSelRollItemId);
	m_vctRollList.erase(m_vctRollList.begin() + m_dwSelRollItemId);
	m_vctRollList.insert(m_vctRollList.begin() + m_dwSelRollItemId + 1,tRolleeState);

	UpdateRollList(emRollMoveDown);
	return true;
}

bool CConfRollLogic::OnBtnRollBottom( TNotifyUI& msg )
{
	if(m_dwSelRollItemId == -1 || m_vctRollList.size() <= 1 ||  m_dwSelRollItemId == m_vctRollList.size()-1)
	{
		return false;
	}

	TRolleeState tRolleeState = m_vctRollList.at(m_dwSelRollItemId);
	m_vctRollList.erase(m_vctRollList.begin() + m_dwSelRollItemId);
	m_vctRollList.insert(m_vctRollList.end(),tRolleeState);

	UpdateRollList(emRollMoveBottom);
	return true;
}

bool CConfRollLogic::OnBtnRollPre(TNotifyUI& msg)
{
	if(m_dwSelRollItemId == -1 || m_vctRollList.size() <= 1)
	{
		return false;
	}

	TCMSConf tConfInfo;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
	if ( ! bInConf )
	{
		return false;
	}

	UpdateRollList(emRollPre);

	TTpRollCallNextEpInfo tRollNext;
	tRollNext.m_wConfID = tConfInfo.m_wConfID;
	tRollNext.m_wRollCaller = m_tRollerInfo.m_wEpID;
	tRollNext.m_wCallTarget = m_vctRollList.at(m_dwSelRollItemId).m_wEpID;
	ComInterface->RollNext(tRollNext);

	return true;
}

bool CConfRollLogic::OnBtnRollNext(TNotifyUI& msg)
{
	if(m_dwSelRollItemId == -1 || m_vctRollList.size() <= 1)
	{
		return false;
	}

	TCMSConf tConfInfo;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
	if ( ! bInConf )
	{
		return false;
	}

	UpdateRollList(emRollNext);

	TTpRollCallNextEpInfo tRollNext;
	tRollNext.m_wConfID = tConfInfo.m_wConfID;
	tRollNext.m_wRollCaller = m_tRollerInfo.m_wEpID;
	tRollNext.m_wCallTarget = m_vctRollList.at(m_dwSelRollItemId).m_wEpID;
	ComInterface->RollNext(tRollNext);

	return true;
}

bool CConfRollLogic::OnBtnRollDel( TNotifyUI& msg )
{
	if(m_dwSelRollItemId == -1)
	{
		return false;
	}

	int ret = ShowMessageBox(_T("是否删除会场？"),true);
	if ( IDOK != ret )
	{
		return true;
	}

	m_vctRollList.erase(m_vctRollList.begin() + m_dwSelRollItemId);
	UpdateRollList(m_vctRollList);
	m_dwSelRollItemId = -1;
	EnableRollBtn(false);
	return true;
}

bool CConfRollLogic::OnBtnRollSelCancel( TNotifyUI& msg )
{
	ICncCommonOp::ShowControl( false, m_pm, _T("PageRollSelConfList") );
	m_bIsSelAll = false;
	ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnRollPSelAll"));
	m_vctSelConf.clear();
	m_emSelConf = emSelConfNo;

	return true;
}

bool CConfRollLogic::OnCheckConfItem( TNotifyUI& msg )
{
	if (msg.pSender->GetParent()->GetParent()->GetName() != _T("RollCnsConfList"))
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

	CString str(ICncCommonOp::GetControlText(m_pm,_T("BtnRollPSelAll")).c_str());
	if (m_bIsSearch)
	{
		if (m_vctSelConf.size() == m_vctSearchCnsList.size() && str != _T("取消全选"))
		{
			m_bIsSelAll = true;
			ICncCommonOp::SetControlText(_T("取消全选"),m_pm,_T("BtnRollPSelAll"));
		}
		if (m_vctSelConf.size() != m_vctSearchCnsList.size() && str != _T("全 选"))
		{
			m_bIsSelAll = false;
			ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnRollPSelAll"));
		}
	}
	else
	{
		if (m_vctSelConf.size() == m_vctCurrentCnsList.size() && str != _T("取消全选"))
		{
			m_bIsSelAll = true;
			ICncCommonOp::SetControlText(_T("取消全选"),m_pm,_T("BtnRollPSelAll"));
		}
		if (m_vctSelConf.size() != m_vctCurrentCnsList.size() && str != _T("全 选"))
		{
			m_bIsSelAll = false;
			ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnRollPSelAll"));
		}
	}

	if ( m_emSelConf == emSelConfRoller && m_vctSelConf.size() > 1 )
	{
		ICncCommonOp::EnableControl(false, m_pm, _T("BtnRollPSelOK"));
	}
	else
	{
		ICncCommonOp::EnableControl(true, m_pm, _T("BtnRollPSelOK"));
	}
	return true;
}

bool CConfRollLogic::OnBtnRollSelAll( TNotifyUI& msg )
{
	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("RollCnsConfList") );
	if ( pTileLayoutUI == NULL )
	{
		return false;
	}
	m_bIsSelAll = !m_bIsSelAll;
	if ( m_bIsSelAll )
	{
		ICncCommonOp::SetControlText(_T("取消全选"),m_pm,_T("BtnRollPSelAll"));
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
		ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnRollPSelAll"));
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

void CConfRollLogic::UpdateCnsList()
{
	m_vctCurrentCnsList.clear();
	if (m_emSelConf == emSelConfRollee)
	{
		m_vctCurrentCnsList = m_vctCnsList;
	}

	if (m_emSelConf == emSelConfRoller)
	{
		m_vctCurrentCnsList = m_vctCnsNoChildList;//点名人不能是下级会场
	}

	m_vctSelConf.clear();
	CTouchListUI* pConfCnsList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("RollCnsConfList") );
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

		if (m_vctCurrentCnsList.at(i).m_emEpType != emTPEndpointTypeCNS)
		{
			m_pm->DoCase( _T("caseOrdinary"), pListContainer ); 
		}
		//pListContainer->SetTag( (UINT_PTR)&m_vctCurrentCnsList.at(i) );

		pConfCnsList->Add(pListContainer);
	}

	m_bIsSelAll = false;
	ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnRollPSelAll"));
}

bool CConfRollLogic::OnRefreshCnsLstNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TCMSConf tConfInfo ;
	bool bIn = ComInterface->IsInConf( &tConfInfo );
	if (!bIn)
	{
		return false;
	}

	m_vctCnsList.clear();
	m_vctCnsNoChildList.clear();

	for (int i = 0; i < tConfInfo.m_vctCnsList.size(); i++)
	{
		TCnsInfo tCnsInfo = tConfInfo.m_vctCnsList.at(i);
        if ( tCnsInfo.m_emEpType == emTPEndpointTypeUMS || tCnsInfo.m_emEpType == emTPEndpointH323MCU || 
             tCnsInfo.m_emEpType == emTPEndpointH323G400 || tCnsInfo.m_emEpType == emTPEndpointTypeVRS )
		{            
			continue;
		}

		if (tCnsInfo.m_bOnline)//只显示在线
		{
			m_vctCnsList.push_back(tCnsInfo);
			if (tCnsInfo.m_wParentEpID == TP_INVALID_INDEX)
			{
				m_vctCnsNoChildList.push_back(tCnsInfo);
			}
		}
	}

	if (m_bIsSearch)
	{
		m_bIsSearch = false;
		m_vctSearchCnsList.clear();
		ICncCommonOp::SetControlText(_T(""), m_pm,  _T("EdtRollPSearch"));
	}

	UpdateCnsList();
	UpdateRollState();
	return true;
}

bool CConfRollLogic::OnRollLstFixedInd(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	EmRollCallRspRet em = (EmRollCallRspRet)wParam;

	CString strError;
	switch(em)
	{
		// 开启点名的结果，注：关闭点名，只回复Ok或者OtherFail
	case em_StartRollCall_AssignMixFail:
		{
			strError = _T("资源不足，开启点名失败");
		}
		break;
	case em_StartRollCall_ConfAudMixMode:
		{
			strError = _T("混音已开启，开启点名失败，请关闭混音");
		}
		break;
	case em_StartRollCall_DisMode:
		{
			strError = _T("讨论已开启，开启点名失败，请关闭讨论");
		}
		break;
	case em_StartRollCall_AlreadyStart:
		{
			strError = _T("重复开启点名，当前已是点名模式");
		}
		break;
	case em_StartRollCall_AssignAddrFail:
		{
			strError = _T("点名开启失败，申请地址错误，不能开启点名");
		}
		break;
	case em_StartRollCall_NotTopUms:
		{
			strError = _T("当前操作的不是顶级UMS，操作无效");
		}
		break;
	case em_StartRollCall_CreateChanFail:
		{
			strError = _T("上调点名者音频或PUT点名者音频失败,不能开启点名");
		}
		break;
	case em_StartRollCall_OtherFail:
		{
			strError = _T("终止点名");
		}
		break;
	case em_UpdateRollCalList_ListFull:
		{
			strError = _T("更新点名列表点名列表满");
		}
		break;
	case em_UpdateRollCalList_NotTopUms:
		{
			strError = _T("更新点名列表，当前操作的不是顶级UMS，操作无效");
		}
		break;
	case em_UpdateRollCalList_InvalidEp:
		{
			strError = _T("更新点名列表, 无效会场");
		}
		break;
	case em_UpdateRollCalList_EpoffLine:
		{
			strError = _T("更新点名列表, 会场不在线");
		}
		break;
	case em_UpdateRollCalList_Fail:
		{
			strError = _T("更新点名列表出错，不能开启点名");
		}
		break;
	case em_RollCallNextEp_NotStart:
		{
			strError = _T("点名下一个时，尚未开启点名模式，操作无效");
		}
		break;
	case em_RollCallNextEp_NotTopUms:
		{
			strError = _T("点名下一个时，当前操作的不是顶级UMS，操作无效");
		}
		break;
	case em_RollCallNextEp_CallerChg:
		{
			strError = _T("点名下一个时，点名者发生了变化，终止点名");
		}
		break;
	case em_RollCallNextEp_EpError:
		{
			strError = _T("点名下一个时，会场错误，终止点名");
		}
		break;
	case em_RollCallNextEp_CreateChanFail:
		{
			strError = _T("上调被名者音频或PUT被名者音频失败，退出点名");
		}
		break;
	case em_RollCallNextEp_OtherFail:
		{
			strError = _T("系统异常");
		}
		break;

	default:
		break;
	}

	if (!strError.IsEmpty())
	{
		ShowPopMsg(strError);
	}

	return S_OK;
}

void CConfRollLogic::UpdateRollState()
{
	TCMSConf tConfInfo ;
	bool bIn = ComInterface->IsInConf( &tConfInfo );
	if (!bIn)
	{
		return;
	}

	if (m_tRollerInfo.m_wEpID != TP_INVALID_INDEX)
	{
		TCnsInfo* tInfor = tConfInfo.GetCnsInfoByID(m_tRollerInfo.m_wEpID);
		if (tInfor != NULL && !tInfor->m_bOnline)//点名人不在线
		{
			m_tRollerInfo.m_bOnline = tInfor->m_bOnline;
			ICncCommonOp::SetControlBkColor(_T("#FF40546C"), m_pm, _T("Rollerbg"));
		}
		else
		{
			ICncCommonOp::SetControlBkColor(_T(""), m_pm, _T("Rollerbg"));
		}
	}

	CListUI* pRollList = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("RollList"));
	if ( pRollList == NULL )
	{
		return ;
	}

	for (int i=0; i<m_vctRollList.size(); i++)
	{		
		TCnsInfo* tInfor = tConfInfo.GetCnsInfoByID(m_vctRollList.at(i).m_wEpID);
		if (tInfor == NULL)
		{
			continue;
		}

		CListContainerElementUI *pListContainer = (CListContainerElementUI*)pRollList->GetItemAt(i);
		if (pListContainer == NULL)
		{
			return;
		}

		bool bOnline = tInfor->m_bOnline;
		if (bOnline != m_vctRollList.at(i).m_bOnline)
		{
			if (bOnline)
			{
				pListContainer->SetAttribute(_T("bkcolor"), _T(""));
				if (i == m_dwSelRollItemId && !m_vctRollList.at(i).m_bOnline)//不在线时被选中，后来在线了
				{
					ICncCommonOp::ShowControl(false, m_pm, _T("BtnSelect"),pListContainer);
                    if (m_tTpConfRollCallInfo.m_bStart)
                    {
                        ICncCommonOp::ShowControl(true, m_pm, _T("RollCtrl"),pListContainer);
                        ICncCommonOp::ShowControl(false, m_pm, _T("ctrlpos"),pListContainer);
                    }
				}
			}
			else
			{
				pListContainer->SetAttribute(_T("bkcolor"), _T("#FF40546C"));
				if (i == m_dwSelRollItemId && m_vctRollList.at(i).m_bOnline)//在线时被选中了，后来掉线了
				{
					ICncCommonOp::ShowControl(false, m_pm, _T("BtnSelect"),pListContainer);
					ICncCommonOp::ShowControl(false, m_pm, _T("RollCtrl"),pListContainer);
					ICncCommonOp::ShowControl(true, m_pm, _T("ctrlpos"),pListContainer);
				}
			}

			m_vctRollList.at(i).m_bOnline = bOnline;
		}
	}
}

bool CConfRollLogic::OnBtnRollSelRoomOK( TNotifyUI& msg )
{
	if (m_emSelConf == emSelConfNo)
	{
		return false;
	}

	if (m_vctSelConf.size() == 0)
	{
		ShowMessageBox(_T("请选择添加的会场"));
		return false;
	}

	TCMSConf tConfInfo;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
	if ( ! bInConf )
	{
		return NO_ERROR;
	}

	if (m_emSelConf == emSelConfRoller)
	{
		if (m_vctSelConf.size() >1)
		{
			ShowMessageBox(_T("点名人只能有一个"));
			return false;
		}

		for (int j=0; j<m_vctRollList.size(); j++)
		{
			if (m_vctSelConf.at(0).m_wEpID == m_vctRollList.at(j).m_wEpID)
			{
				ShowMessageBox(_T("此被点名人已被加入到点名列表中，点名人和被点名人必须是不同会场，请重新选择"));
				return false;
			}
		}

		m_tRollerInfo = m_vctSelConf.at(0);
		m_emSelConf = emSelConfNo;
		ICncCommonOp::SetControlText( CA2T(m_tRollerInfo.m_achRoomName), m_pm, _T("lbRollerName"));
        if (m_tRollerInfo.m_emEpType != emTPEndpointTypeCNS)
        {
            ICncCommonOp::SetControlBkImg(_T("res/list/imgOrdinary.png"), m_pm, _T("UserItemPic"));
        }
        else
        {
            ICncCommonOp::SetControlBkImg(_T("res/confctrl/confroll/roller.png"), m_pm, _T("UserItemPic"));
        }
		//OspPrintf(TRUE,false,"m_tRollerInfo:OnBtnRollSelRoomOK %d",m_tRollerInfo.m_wEpID);
		ICncCommonOp::EnableControl(true,m_pm,_T("CheckStartConfroll"));
		ICncCommonOp::ShowControl( false, m_pm, _T("PageRollSelConfList") );
		return true;
	}

	bool bCallerEquelsCallee = false;
	u32 wAddCount = 0;	
	TTpUpdataRollCallList tTpUpdataRollCallList;

	for (int i=0; i<m_vctSelConf.size(); i++)//不重复添加
	{
		bool bInclude = false;
		for (int j=0; j<m_vctRollList.size(); j++)
		{
			if (m_vctSelConf.at(i).m_wEpID == m_vctRollList.at(j).m_wEpID)
			{
				bInclude = true;
				break;
			}
		}

		if (!bInclude)
		{
			if (!bCallerEquelsCallee && m_tRollerInfo.m_wEpID == m_vctSelConf.at(i).m_wEpID)// 点名者与被点名者必须不同
			{
				bCallerEquelsCallee = true;
				continue;
			}

			TRolleeState tRolleeState;
			tRolleeState.m_wEpID = m_vctSelConf.at(i).m_wEpID;
			tRolleeState.m_bOnline = m_vctSelConf.at(i).m_bOnline;
			memcpy(tRolleeState.m_achRoomName,m_vctSelConf.at(i).m_achRoomName,TP_MAX_ALIAS_LEN);
            tRolleeState.m_emEpType = m_vctSelConf.at(i).m_emEpType;
			m_vctRollList.push_back(tRolleeState);

			if (m_tTpConfRollCallInfo.m_bStart)
			{
				wAddCount++;		
				tTpUpdataRollCallList.m_atRollCallMemList.AddRollCallTarget(m_vctSelConf.at(i).m_wEpID);
			}
		}
	}

	if (m_tTpConfRollCallInfo.m_bStart && wAddCount != 0)
	{
		tTpUpdataRollCallList.m_bAdd = TRUE;
		tTpUpdataRollCallList.m_wConfID = tConfInfo.m_wConfID;
		tTpUpdataRollCallList.m_atRollCallMemList.SetRollCaller(m_tRollerInfo.m_wEpID);
		tTpUpdataRollCallList.m_atRollCallMemList.m_wNum = wAddCount;

		ComInterface->RollListFixedCmd(tTpUpdataRollCallList);
	}

	if (bCallerEquelsCallee)
	{
		ShowMessageBox(_T("被点名者中包含已选点名者，已自动去除"));
	}

	UpdateRollList(m_vctRollList);
//	CListUI* pRollList = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("RollList"));
// 	if (pRollList && m_vctRollList.size() != 1)
// 	{
// 		m_dwSelRollItemId = m_vctRollList.size() -1;
// 		//pRollList->SelectItem((m_vctRollList.size() -1));
// 		m_pm->SetTimer(pRollList,g_nRollSelTimerID,g_nRollSelInterval);
// 	}
// 	else
// 	{
		EnableRollBtn(false);
		m_dwSelRollItemId = -1;
//	}

	ICncCommonOp::ShowControl( false, m_pm, _T("PageRollSelConfList") );
	m_emSelConf = emSelConfNo;

	return true;
}

bool CConfRollLogic::OnRollSearchEditChange( TNotifyUI& msg )
{
	CEditUI* pEditSearch = (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("EdtRollPSearch") );
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
		ICncCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnRollPSelAll"));
		CTouchListUI *pTileLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("RollCnsConfList") );
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

bool CConfRollLogic::OnBtnAttend(TNotifyUI& msg)
{
	m_dwCallTargetItemId = -1;
	m_vctRollList.at(m_dwSelRollItemId).m_emAttend = emAttend;
	UpdateRollItem( m_dwSelRollItemId );
	UpDateAbsentState(em_RollCallPresentState_Ok);
	return true;
}

bool CConfRollLogic::OnBtnAbsent(TNotifyUI& msg)
{
	m_dwCallTargetItemId = -1;
	m_vctRollList.at(m_dwSelRollItemId).m_emAttend = emAbsent;
	UpdateRollItem( m_dwSelRollItemId, emAbsent );
	UpDateAbsentState(em_RollCallPresentState_Absent);
	return true;
}

void CConfRollLogic::UpDateAbsentState(EmRollCallPresentState em)
{

	TCMSConf tConfInfo;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
	if ( ! bInConf )
	{
		return;
	}

	TTpRollCallPresentStateMsg tTpRollCallPresentStateMsg;
	tTpRollCallPresentStateMsg.m_atEpState[0].m_wEpID = m_vctRollList.at(m_dwSelRollItemId).m_wEpID;
	tTpRollCallPresentStateMsg.m_atEpState[0].m_wEpState = em;
	tTpRollCallPresentStateMsg.m_wConfID = tConfInfo.m_wConfID;
	tTpRollCallPresentStateMsg.m_wValidNum = 1;

	ComInterface->RollAttendState( tTpRollCallPresentStateMsg );
}

bool CConfRollLogic::OnBtnItemSelect(TNotifyUI& msg)
{
	CListUI* pRollList = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("RollList"));
	if ( pRollList == NULL )
	{
		return false;
	}

	CListContainerElementUI *pListContainerSel = (CListContainerElementUI*)pRollList->GetItemAt(m_dwSelRollItemId);
	if (pListContainerSel == NULL)
	{
		return false;
	}

	ICncCommonOp::ShowControl(false, m_pm, _T("BtnSelect"),pListContainerSel);
	ICncCommonOp::ShowControl(true, m_pm, _T("RollCtrl"),pListContainerSel);
	ICncCommonOp::ShowControl(false, m_pm, _T("ctrlpos"),pListContainerSel);

	TCMSConf tConfInfo;
	BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
	if ( ! bInConf )
	{
		return false;
	}

	TTpRollCallNextEpInfo tRollNext;
	tRollNext.m_wConfID = tConfInfo.m_wConfID;
	tRollNext.m_wRollCaller = m_tRollerInfo.m_wEpID;
	tRollNext.m_wCallTarget = m_vctRollList.at(m_dwSelRollItemId).m_wEpID;
	ComInterface->RollNext(tRollNext);

//显示三屏状态
// 	TRolleeState tRolleeState =  m_vctRollList.at(m_dwSelRollItemId);
// 	CString strConfName;
// 	strConfName.Format( _T("%s"),CA2T( tRolleeState.m_achRoomName));
// 
// 	ICncCommonOp::SetControlText( strConfName, m_pm, _T("lbCenterView"));
// 
// 	if (tRolleeState.m_wSpeakerNum == 3)
// 	{
// 		ICncCommonOp::SetControlText( strConfName, m_pm, _T("lbLeftView"));
// 		ICncCommonOp::SetControlText( strConfName, m_pm, _T("lbRightView"));
// 	}
// 	else
// 	{
// 		ICncCommonOp::EnableControl(false,m_pm,_T("BtnSetLeftSpeaker"));
// 		ICncCommonOp::EnableControl(false,m_pm,_T("BtnSetRightSpeaker"));
// 	}

	return true;
}

// bool CConfRollLogic::OnStartRollRsp( WPARAM wParam, LPARAM lParam, bool& bHandle )
// {
// 	bool bIsRoll = ComInterface->IsStartRoll();
// 	
// 	CCheckBoxUI *pControl = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckConfrollShortCut") );
// 	if (pControl)
// 	{
// 		if (pControl->IsSelected() != bIsRoll)
// 		{
// 			pControl->SetCheckNoMsg(bIsRoll);
// 		}	
// 	}
// 
// 	if (!bIsRoll)//如果关闭了，清空会场三屏，列表不可选
// 	{
// 		CListUI* pRollList = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("RollList"));
// 		if ( pRollList == NULL )
// 		{
// 			return false;
// 		}
// 
// 		CListContainerElementUI *pListContainerSel = (CListContainerElementUI*)pRollList->GetItemAt(m_dwSelRollItemId);
// 		if (pListContainerSel == NULL)
// 		{
// 			return false;
// 		}
// 
// 		ICncCommonOp::ShowControl(false, m_pm, _T("BtnSelect"),pListContainerSel);
// 		ICncCommonOp::ShowControl(false, m_pm, _T("RollCtrl"),pListContainerSel);
// 		ICncCommonOp::ShowControl(true, m_pm, _T("ctrlpos"),pListContainerSel);
// 
// 		ICncCommonOp::SetControlText( _T(""), m_pm, _T("lbCenterView"));
// 		ICncCommonOp::SetControlText( _T(""), m_pm, _T("lbLeftView"));
// 		ICncCommonOp::SetControlText( _T(""), m_pm, _T("lbRightView"));
// 
// 		ICncCommonOp::EnableControl(false,m_pm,_T("BtnSetCenterSpeaker"));
// 		ICncCommonOp::EnableControl(false,m_pm,_T("BtnSetLeftSpeaker"));
// 		ICncCommonOp::EnableControl(false,m_pm,_T("BtnSetRightSpeaker"));
// 	}
// 
// 	return true;
// 
// }

bool CConfRollLogic::OnShortCutRoll( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	CCheckBoxUI *pControl = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckStartConfroll") );
	if (pControl)
	{
		pControl->SetCheck(!m_tTpConfRollCallInfo.m_bStart);
	}

	return true;
}

bool CConfRollLogic::OnChairNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	//OspPrintf(TRUE,false,"m_tRollerInfo:OnChairNty begin %d",m_tRollerInfo.m_wEpID);
	if (TP_INVALID_INDEX == m_tRollerInfo.m_wEpID)//若没有自己手动选择，则默认主席是点名人
	{
		TCMSConf tConfInfo;
		BOOL32 bInConf = ComInterface->IsInConf( &tConfInfo );
		if (!bInConf)
		{
			return false;
		}
		TCnsInfo* tInfor = tConfInfo.GetCnsInfoByID(tConfInfo.GetChairCnsID());
		if (tInfor != NULL)
		{
			m_tRollerInfo = *(TCnsInfo*)tInfor;
			ICncCommonOp::SetControlText( CA2T(m_tRollerInfo.m_achRoomName), m_pm, _T("lbRollerName"));
            if (m_tRollerInfo.m_emEpType != emTPEndpointTypeCNS)
            {
                ICncCommonOp::SetControlBkImg(_T("res/list/imgOrdinary.png"), m_pm, _T("UserItemPic"));
            }
            else
            {
                ICncCommonOp::SetControlBkImg(_T("res/confctrl/confroll/roller.png"), m_pm, _T("UserItemPic"));
            }
			//OspPrintf(TRUE,false,"m_tRollerInfo:OnChairNty inconf %d",m_tRollerInfo.m_wEpID);
			ICncCommonOp::EnableControl(true,m_pm,_T("CheckStartConfroll"));
			ICncCommonOp::ShowControl( false, m_pm, _T("PageRollSelConfList") );
		}
	}

	return true;
}

bool CConfRollLogic::OnConfStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	BOOL bInConf = ComInterface->IsInConf();
	if ( !bInConf )
	{
		OnDisconnect( wParam, lParam, bHandle );
	}

	return false;
}
