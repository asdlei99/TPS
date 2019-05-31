#include "StdAfx.h"
#include "centermonitorlogic.h"
#include "confmsglogic.h"
#include "messageboxlogic.h"

template<> CCenterMonitorLogic* Singleton<CCenterMonitorLogic>::ms_pSingleton = NULL;

APP_BEGIN_MSG_MAP(CCenterMonitorLogic,CNotifyUIImpl)
    MSG_INIWINDOW(_T("RoomCtrlLayout"), OnInit)

	MSG_CLICK(_T("BtnWetPlus"), OnBtnTempPlus)
	MSG_CLICK(_T("BtnWetMinus"), OnBtnTempMinus)
	MSG_CLICK(_T("BtnWindPlus"), OnBtnWindPlus)
	MSG_CLICK(_T("BtnWindMinus"), OnBtnWindMinus)
	MSG_CLICK(_T("BtnWindAuto"), OnBtnWindAuto)
	MSG_CLICK(_T("btnAirAll"), OnBtnAirAll)

	//显示器控制
	MSG_CLICK(_T("btnFS"), OnOpFS)
	MSG_CLICK(_T("btnFView"), OnOpFView)
	MSG_CLICK(_T("btnStandard"), OnOpStandard)
	MSG_CLICK(_T("btnPTP"), OnOpPTP)
	MSG_CLICK(_T("btnVStandard"), OpVStandard)
	MSG_CLICK(_T("btnVUser"), OpVUser)
	MSG_CLICK(_T("btnVPC"), OpVPC)
	MSG_CLICK(_T("btnVTV"), OpVTV)
	MSG_CLICK(_T("btnHDMI1"), OnOpHDMI1)
	MSG_CLICK(_T("btnHDMI2"), OnOpHDMI2)
	MSG_CLICK(_T("btnHDMI3"), OnOpHDMI3)
	MSG_CLICK(_T("btnHDMI4"), OnOpHDMI4)
	MSG_CLICK(_T("btnYPbPr"), OnOpYPbPr)
	MSG_CLICK(_T("btnCVBs1"), OnOpCVBs1)
	MSG_CLICK(_T("btnCVBs2"), OnOpCVBs2)
	MSG_CLICK(_T("btnSPC"), OnOpSPC)
	MSG_CLICK(_T("btnVGA"), OnOpVGA)
	MSG_CLICK(_T("OpCold"), OnOpCold)
	MSG_CLICK(_T("OpHot"), OnOpHot)
	MSG_CLICK(_T("OpWind"), OnOpWind)     
	MSG_CLICK(_T("OpWet"), OnOpWet)


	MSG_SELECTCHANGE(_T("CheckScreen"), OnCheckScreenSel)
	MSG_SELECTCHANGE(_T("CheckStart"), OnCheckAircon)

	MSG_ITEMSELECTD(_T("MonitorList"), OnScreenMonitorItemClick)
	MSG_ITEMSELECTD(_T("AirconditionList"), OnScreenAirconItemClick)

	MSG_SELECTCHANGE(_T("OpFS"), OnOpFS)
	MSG_SELECTCHANGE(_T("OpFView"), OnOpFView)
	MSG_SELECTCHANGE(_T("OpStandard"), OnOpStandard)
	MSG_SELECTCHANGE(_T("OpPTP"), OnOpPTP)
	MSG_SELECTCHANGE(_T("OpVStandard"), OpVStandard)
	MSG_SELECTCHANGE(_T("OpVUser"), OpVUser)
	MSG_SELECTCHANGE(_T("OpVPC"), OpVPC)
	MSG_SELECTCHANGE(_T("OpVTV"), OpVTV)
	MSG_SELECTCHANGE(_T("OpHDMI1"), OnOpHDMI1)
	MSG_SELECTCHANGE(_T("OpHDMI2"), OnOpHDMI2)
	MSG_SELECTCHANGE(_T("OpHDMI3"), OnOpHDMI3)
	MSG_SELECTCHANGE(_T("OpYPbPr"), OnOpYPbPr)
	MSG_SELECTCHANGE(_T("OpCVBs1"), OnOpCVBs1)
	MSG_SELECTCHANGE(_T("OpCVBs2"), OnOpCVBs2)
	MSG_SELECTCHANGE(_T("OpSPC"), OnOpSPC)
	MSG_SELECTCHANGE(_T("OpVGA"), OnOpVGA)
	MSG_SELECTCHANGE(_T("OpCold"), OnOpCold)
	MSG_SELECTCHANGE(_T("OpHot"), OnOpHot)
	MSG_SELECTCHANGE(_T("OpWind"), OnOpWind)     
	MSG_SELECTCHANGE(_T("OpWet"), OnOpWet)

	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)

	USER_MSG(UI_CNS_TVSTATE_NTY,OnMonitorStateNty)
	USER_MSG(UI_CNS_TVPOWERMODE_IND,OnMonitorPowrInd)
	USER_MSG(UI_CNS_SELETETV_IND,OnSeleteMonitorInd) 
	//空调
	USER_MSG(UI_CNS_ACSTATE_NTY,OnACStateNty)
	USER_MSG(UI_CNS_SELECTAIR_IND,OnSelectAirInd)
	USER_MSG(UI_CNS_ACPOWERSTATE_IND,OnAirPowerInd)

    //显示器
    USER_MSG(UI_CNDISPLAYSHOW,OnDisPlayShowNty)


APP_END_MSG_MAP()


const String CCenterMonitorLogic::m_strSldTab = _T("slidetab");

CCenterMonitorLogic::CCenterMonitorLogic(void)
{
	m_dwMonitorScreenSelId = -1;
	m_dwAirconScreenSelId = -1;
    m_bDisplayShow = true;
}


CCenterMonitorLogic::~CCenterMonitorLogic(void)
{
}

bool CCenterMonitorLogic::OnInit( TNotifyUI& msg )
{
    if (m_bDisplayShow)
    {
        ICncCommonOp::ShowControl(true,m_pm,_T("Monitor"));
    }
    else
    {
        COptionUI *pOpMonitor = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("Monitor"));
        if (pOpMonitor && pOpMonitor->IsSelected())
        {
            //选中默认项
            COptionUI *pOp = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("Switch"));
            if (pOp)
            {
                pOp->Selected(true);
            }
        }
        ICncCommonOp::ShowControl(false,m_pm,_T("Monitor"));
    }
    return true;
}


bool CCenterMonitorLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_dwMonitorScreenSelId = -1;
	m_dwAirconScreenSelId = -1;

	CTouchListUI *pMonitorListLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MonitorList") );
	if (pMonitorListLayoutUI)
	{
		pMonitorListLayoutUI->SelectItem(-1);
		ICncCommonOp::SetControlText(_T("显示器 调节"),m_pm,_T("lbMonitor"));
	}
	pMonitorListLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("AirconditionList") );
	if (pMonitorListLayoutUI)
	{
		pMonitorListLayoutUI->SelectItem(-1);
	}

    m_bDisplayShow = true;
	return true;
}

bool CCenterMonitorLogic::OnCheckScreenSel( TNotifyUI& msg )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}
	//并且禁用此开关 ind回复后再恢复 dyy 2015-9-23 杨雷确认添加此控制
	pCheckBox->SetEnabled(false);

	bool bIsSet = false;
	if ( pCheckBox->IsSelected() )
	{
		bIsSet = true;
	}

	int dwScreenNo = -1;
	CListContainerElementUI* pItem = (CListContainerElementUI*)msg.pSender->GetParent()->GetParent();
	if (pItem)
	{
		dwScreenNo = pItem->GetIndex();
	}
	//点击check 跳转到此条目 2015-8-31  
	CTouchListUI *pMonitorListLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MonitorList") );
	if (pMonitorListLayoutUI)
	{
		pMonitorListLayoutUI->SelectItem(dwScreenNo);
	}

	if ( m_mapIsMonitor[dwScreenNo] != bIsSet)
	{
		m_mapIsMonitor[dwScreenNo] = bIsSet;

		if ( bIsSet )
		{
			ComInterface->SetTVPowerMode( dwScreenNo, emTVPowerON );
		}
		else
		{
			ComInterface->SetTVPowerMode( dwScreenNo, emTVPowerOFF );
		}
	}

	return true;
}


bool CCenterMonitorLogic::OnCheckAircon( TNotifyUI& msg )
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

	int dwScreenNo = -1;
	CListContainerElementUI* pItem = (CListContainerElementUI*)msg.pSender->GetParent()->GetParent();
	if (pItem)
	{
		dwScreenNo = pItem->GetIndex();
	}

	CTouchListUI *pMonitorListLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("AirconditionList") );
	if (pMonitorListLayoutUI)
	{
		pMonitorListLayoutUI->SelectItem(dwScreenNo);
	}

	if ( m_mapIsAirCon[dwScreenNo] != bIsSet)
	{
		m_mapIsAirCon[dwScreenNo] = bIsSet;
		EmCentreACPower em = emCenACPowerOff;
		if (bIsSet)
		{
			em = emCenACPowerOn;
		}
		ComInterface->SetACPowerMode(dwScreenNo,em);
	}

	return true;
}


bool CCenterMonitorLogic::OpVTV( TNotifyUI& msg )
{
	if (m_dwMonitorScreenSelId == -1)
	{
		ShowMessageBox(_T("请先选择要控制的显示器"));
		return true;
	}
// 	if (m_atModitorCfg[m_dwMonitorScreenSelId].emAudVisMode == emTVAVMovieMode)
// 	{
// 		return true;
// 	}
	ComInterface->SetTVAudVisMode( emTVAVMovieMode );
	m_atModitorCfg[m_dwMonitorScreenSelId].emAudVisMode = emTVAVMovieMode;
	return true;
}

bool CCenterMonitorLogic::OpVPC( TNotifyUI& msg )
{
	if (m_dwMonitorScreenSelId == -1)
	{
		ShowMessageBox(_T("请先选择要控制的显示器"));
		return true;
	}
// 	if (m_atModitorCfg[m_dwMonitorScreenSelId].emAudVisMode == emTVAVComputerMode)
// 	{
// 		return true;
// 	}
	ComInterface->SetTVAudVisMode( emTVAVComputerMode );
	m_atModitorCfg[m_dwMonitorScreenSelId].emAudVisMode = emTVAVComputerMode;
	return true;
}

bool CCenterMonitorLogic::OpVUser( TNotifyUI& msg )
{
	if (m_dwMonitorScreenSelId == -1)
	{
		ShowMessageBox(_T("请先选择要控制的显示器"));
		return true;
	}
// 	if (m_atModitorCfg[m_dwMonitorScreenSelId].emAudVisMode == emTVAVUserMode)
// 	{
// 		return true;
// 	}
	ComInterface->SetTVAudVisMode( emTVAVUserMode );
	m_atModitorCfg[m_dwMonitorScreenSelId].emAudVisMode = emTVAVUserMode;
	return true;
}

bool CCenterMonitorLogic::OpVStandard( TNotifyUI& msg )
{
	if (m_dwMonitorScreenSelId == -1)
	{
		ShowMessageBox(_T("请先选择要控制的显示器"));
		return true;
	}
// 	if (m_atModitorCfg[m_dwMonitorScreenSelId].emAudVisMode == emTVAVStandardMode)
// 	{
// 		return true;
// 	}
	ComInterface->SetTVAudVisMode( emTVAVStandardMode );
	m_atModitorCfg[m_dwMonitorScreenSelId].emAudVisMode = emTVAVStandardMode;
	return true;
}

bool CCenterMonitorLogic::OnOpPTP( TNotifyUI& msg )
{
	if (m_dwMonitorScreenSelId == -1)
	{
		ShowMessageBox(_T("请先选择要控制的显示器"));
		return true;
	}
// 	if (m_atModitorCfg[m_dwMonitorScreenSelId].emDisMode == emTVDisPointMode)
// 	{
// 		return true;
// 	}
	ComInterface->SetTVDisMode( emTVDisPointMode );
	m_atModitorCfg[m_dwMonitorScreenSelId].emDisMode = emTVDisPointMode;
	return true;
}

bool CCenterMonitorLogic::OnOpStandard( TNotifyUI& msg )
{
	if (m_dwMonitorScreenSelId == -1)
	{
		ShowMessageBox(_T("请先选择要控制的显示器"));
		return true;
	}
// 	if (m_atModitorCfg[m_dwMonitorScreenSelId].emDisMode == emTVDisStandardMode)
// 	{
// 		return true;
// 	}
	ComInterface->SetTVDisMode( emTVDisStandardMode );
	m_atModitorCfg[m_dwMonitorScreenSelId].emDisMode = emTVDisStandardMode;
	return true;
}

bool CCenterMonitorLogic::OnOpFView( TNotifyUI& msg )
{
	if (m_dwMonitorScreenSelId == -1)
	{
		ShowMessageBox(_T("请先选择要控制的显示器"));
		return true;
	}
// 	if (m_atModitorCfg[m_dwMonitorScreenSelId].emDisMode == emTVDisPanoramaMode)
// 	{
// 		return true;
// 	}
	ComInterface->SetTVDisMode( emTVDisPanoramaMode );
	m_atModitorCfg[m_dwMonitorScreenSelId].emDisMode = emTVDisPanoramaMode;
	return true;
}

bool CCenterMonitorLogic::OnOpFS( TNotifyUI& msg )
{
	if (m_dwMonitorScreenSelId == -1)
	{
		ShowMessageBox(_T("请先选择要控制的显示器"));
		return true;
	}
// 	if (m_atModitorCfg[m_dwMonitorScreenSelId].emDisMode == emTVDisFullScrMode)
// 	{
// 		return true;
// 	}
	ComInterface->SetTVDisMode( emTVDisFullScrMode );
	m_atModitorCfg[m_dwMonitorScreenSelId].emDisMode = emTVDisFullScrMode;
	return true;
}


bool CCenterMonitorLogic::OnOpCVBs2( TNotifyUI& msg )
{
	if (m_dwMonitorScreenSelId == -1)
	{
		ShowMessageBox(_T("请先选择要控制的显示器"));
		return true;
	}
// 	if (m_atModitorCfg[m_dwMonitorScreenSelId].emInpSelect == emTVCVBS2)
// 	{
// 		return true;
// 	}
	ComInterface->SetTVInpSelect( m_dwMonitorScreenSelId, emTVCVBS2 );
	m_atModitorCfg[m_dwMonitorScreenSelId].emInpSelect = emTVCVBS2;
	return true;
}

bool CCenterMonitorLogic::OnOpCVBs1( TNotifyUI& msg )
{
	if (m_dwMonitorScreenSelId == -1)
	{
		ShowMessageBox(_T("请先选择要控制的显示器"));
		return true;
	}
// 	if (m_atModitorCfg[m_dwMonitorScreenSelId].emInpSelect == emTVCVBS1)
// 	{
// 		return true;
// 	}
	ComInterface->SetTVInpSelect( m_dwMonitorScreenSelId, emTVCVBS1 );
	m_atModitorCfg[m_dwMonitorScreenSelId].emInpSelect = emTVCVBS1;
	return true;
}

bool CCenterMonitorLogic::OnOpYPbPr( TNotifyUI& msg )
{
	if (m_dwMonitorScreenSelId == -1)
	{
		ShowMessageBox(_T("请先选择要控制的显示器"));
		return true;
	}
// 	if (m_atModitorCfg[m_dwMonitorScreenSelId].emInpSelect == emTVYpbPr)
// 	{
// 		return true;
// 	}
	ComInterface->SetTVInpSelect( m_dwMonitorScreenSelId, emTVYpbPr );
	m_atModitorCfg[m_dwMonitorScreenSelId].emInpSelect = emTVYpbPr;
	return true;
}
bool CCenterMonitorLogic::OnOpHDMI4( TNotifyUI& msg )
{
	if (m_dwMonitorScreenSelId == -1)
	{
		ShowMessageBox(_T("请先选择要控制的显示器"));
		return true;
	}
// 	if (m_atModitorCfg[m_dwMonitorScreenSelId].emInpSelect == emTVHDMI3)
// 	{
// 		return true;
// 	}
	ComInterface->SetTVInpSelect( m_dwMonitorScreenSelId, emTVHDMI4 );
	m_atModitorCfg[m_dwMonitorScreenSelId].emInpSelect = emTVHDMI4;
	return true;
}

bool CCenterMonitorLogic::OnOpHDMI3( TNotifyUI& msg )
{
	if (m_dwMonitorScreenSelId == -1)
	{
		ShowMessageBox(_T("请先选择要控制的显示器"));
		return true;
	}
// 	if (m_atModitorCfg[m_dwMonitorScreenSelId].emInpSelect == emTVHDMI3)
// 	{
// 		return true;
// 	}
	ComInterface->SetTVInpSelect( m_dwMonitorScreenSelId, emTVHDMI3 );
	m_atModitorCfg[m_dwMonitorScreenSelId].emInpSelect = emTVHDMI3;
	return true;
}

bool CCenterMonitorLogic::OnOpHDMI2( TNotifyUI& msg )
{
	if (m_dwMonitorScreenSelId == -1)
	{
		ShowMessageBox(_T("请先选择要控制的显示器"));
		return true;
	}
// 	if (m_atModitorCfg[m_dwMonitorScreenSelId].emInpSelect == emTVHDMI2)
// 	{
// 		return true;
// 	}
	ComInterface->SetTVInpSelect( m_dwMonitorScreenSelId, emTVHDMI2 );
	m_atModitorCfg[m_dwMonitorScreenSelId].emInpSelect = emTVHDMI2;
	return true;
}

bool CCenterMonitorLogic::OnOpHDMI1( TNotifyUI& msg )
{ 
	if (m_dwMonitorScreenSelId == -1)
	{
		ShowMessageBox(_T("请先选择要控制的显示器"));
		return true;
	}
// 	if (m_atModitorCfg[m_dwMonitorScreenSelId].emInpSelect == emTVHDMI1)
// 	{
// 		return true;
// 	}
	ComInterface->SetTVInpSelect( m_dwMonitorScreenSelId, emTVHDMI1 );
	m_atModitorCfg[m_dwMonitorScreenSelId].emInpSelect = emTVHDMI1;
	return true;
}

bool CCenterMonitorLogic::OnOpSPC( TNotifyUI& msg )
{
	if (m_dwMonitorScreenSelId == -1)
	{
		ShowMessageBox(_T("请先选择要控制的显示器"));
		return true;
	}
// 	if (m_atModitorCfg[m_dwMonitorScreenSelId].emInpSelect == emTVComputer)
// 	{
// 		return true;
// 	}
	ComInterface->SetTVInpSelect( m_dwMonitorScreenSelId, emTVComputer );
	m_atModitorCfg[m_dwMonitorScreenSelId].emInpSelect = emTVComputer;
	return true;
}

bool CCenterMonitorLogic::OnOpVGA( TNotifyUI& msg )
{
	if (m_dwMonitorScreenSelId == -1)
	{
		ShowMessageBox(_T("请先选择要控制的显示器"));
		return true;
	}
// 	if (m_atModitorCfg[m_dwMonitorScreenSelId].emInpSelect == emTVComputer)
// 	{
// 		return true;
// 	}
	ComInterface->SetTVInpSelect( m_dwMonitorScreenSelId, emTVVGA );	
	m_atModitorCfg[m_dwMonitorScreenSelId].emInpSelect = emTVVGA;
	return true;

}

bool CCenterMonitorLogic::OnOpCold( TNotifyUI& msg )
{
	ComInterface->SetACMode(emCenAcref);
	return true;
}

bool CCenterMonitorLogic::OnOpHot( TNotifyUI& msg )
{
	ComInterface->SetACMode(emCenACheat);
	return true;
}

bool CCenterMonitorLogic::OnOpWind( TNotifyUI& msg )
{
	ComInterface->SetACMode(emCenACBlowIn);
	return true;
}

bool CCenterMonitorLogic::OnOpWet( TNotifyUI& msg )
{
	ComInterface->SetACMode(emCenACdeh);
	return true;
}

bool CCenterMonitorLogic::OnScreenAirconItemClick( TNotifyUI& msg )
{
	int nIndex = -1;
	if ( const CTouchListUI *pItem = dynamic_cast<const CTouchListUI*>(msg.pSender) )
	{
		nIndex = pItem->GetCurSel();
	}
	if (nIndex == -1)
	{
		return true;
	}

	if (nIndex == m_dwAirconScreenSelId)
	{
		return true;
	}

	ComInterface->SelectAirMonitor(msg.wParam);
	return false;
}

bool CCenterMonitorLogic::OnMonitorPowrInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	//IND后有nty nty更新 2015-8-28 fxb确认
	u8 byIndex = (u8)wParam; 
	CTouchListUI *pMonitorListLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MonitorList") );
	if (pMonitorListLayoutUI)
	{
		CListContainerElementUI* pItem = (CListContainerElementUI*)pMonitorListLayoutUI->GetItemAt(byIndex);
		if (pItem)
		{
			//ind回复后再恢复
			ICncCommonOp::EnableControl(true,m_pm,_T("CheckScreen"),pItem);
		}
	}

	EmTvPowerMode emPower = (EmTvPowerMode)lParam;
	CString str = _T("");
	if (emPower == emTVPowerON)
	{
		str.Format(_T("显示器0%d开启失败"),byIndex+1);
	}
	else
	{
		str.Format(_T("显示器0%d关闭失败"),byIndex+1);
	}
	
	ShowPopMsg(str);

	return true;
}

bool CCenterMonitorLogic::OnMonitorStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	return updateMonitorState();
}

bool CCenterMonitorLogic::updateMonitorState()
{
	TCentreTVCfg  atTVCfg[MAX_CENTRETV_NUM];
	memcpy( atTVCfg , ComInterface->GetCentreTVCfg(), sizeof(TCentreTVCfg) * MAX_CENTRETV_NUM );

	CTouchListUI *pMonitorListLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MonitorList") );
	for (int i = 0; i<MAX_CENTRETV_NUM; i++)
	{
		if (pMonitorListLayoutUI)
		{
			CListContainerElementUI *pMonitorListContainer = (CListContainerElementUI*) pMonitorListLayoutUI->GetItemAt(i);
			if (pMonitorListContainer)
			{
				CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckScreen"), pMonitorListContainer);
				if (pCheckBox)
				{
					bool bCheck;
					if(atTVCfg[i].emTvPowerMode == emTVPowerON)
					{
						pCheckBox->SetEnabled(true);
						bCheck = true;
					}
					else if (atTVCfg[i].emTvPowerMode == emTVPowerOFF)
					{
						pCheckBox->SetEnabled(true);
						bCheck = false;
					}
					else
					{
						pCheckBox->SetEnabled(false);
						bCheck = false;
					}

					m_mapIsMonitor[i] = bCheck;
					pCheckBox->SetCheckNoMsg(bCheck);
				}
			}
		}
	}

	if (atTVCfg->emTvModle != m_atModitorCfg->emTvModle)
	{
		if (atTVCfg->emTvModle == emSharp70LX565A)
		{
			ICncCommonOp::ShowControl(false,m_pm,_T("Monitor"));
			ICncCommonOp::ShowControl(false,m_pm,_T("ctlMonitor"));
			//选中第一项
			COptionUI *pOpMonitor = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("Monitor"));
			if (pOpMonitor && pOpMonitor->IsSelected())
			{
				COptionUI *pOp = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("Switch"));
				if (pOp)
				{
					pOp->Selected(true);
				}
			}
		}
		else
		{
            if (m_bDisplayShow)
            {
                ICncCommonOp::ShowControl(true,m_pm,_T("Monitor"));
                ICncCommonOp::ShowControl(true,m_pm,_T("ctlMonitor"));
            }
		}

		if (atTVCfg->emTvModle == emKangGuan70B17 || atTVCfg->emTvModle == emKeShi70GMO1A)
		{
			m_pm->DoCase(_T("caseKGmonitor"));
			if (atTVCfg->emTvModle == emKeShi70GMO1A)
			{
				m_pm->DoCase(_T("caseKeShiMonitor"));
			}
			else
			{
				m_pm->DoCase(_T("caseNotKeShiMonitor"));
			}
		}
		else
		{
			m_pm->DoCase(_T("caseNormalMonitor"));
		}
	}

	memcpy( m_atModitorCfg, atTVCfg, sizeof(TCentreTVCfg) * MAX_CENTRETV_NUM );

	return true;
}

bool CCenterMonitorLogic::OnSeleteMonitorInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	u8 wId = (u8)wParam;
	BOOL bok = (BOOL)lParam;

	if ( bok )
	{
		//返回选择成功的时候再记录
		m_dwMonitorScreenSelId = wId;
	}
	else
	{
		CTouchListUI *pMonitorListLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MonitorList") );
		if (pMonitorListLayoutUI)
		{
			pMonitorListLayoutUI->SelectItem(m_dwMonitorScreenSelId);
		}
		CString str=_T("");
		str.Format(_T("显示器0%d选择失败"), wId+1);
		ShowPopMsg(str);
	}

	return true;
}

//bool CCenterMonitorLogic::UpdateMonitorTag( TCentreTVCfg tCentreTVCfg )
// {
// 	EmTVInputSelect emTVInputSelect = tCentreTVCfg.emInpSelect;  
// 	EmTVAudVisMode emTVAudVisMode = tCentreTVCfg.emAudVisMode;   
// 	EmTVDisplayMode emTVDisplayMode = tCentreTVCfg.emDisMode; 
// 		
// 	switch(emTVInputSelect)
// 	{
// 	case emTVHDMI1:
// 		ICncCommonOp::OptionSelect( true, m_pm, _T("OpHDMI1") );
// 		break;
// 	case emTVHDMI2:
// 		ICncCommonOp::OptionSelect( true, m_pm, _T("OpHDMI2") );
// 		break;	
// 	case emTVHDMI3:
// 		ICncCommonOp::OptionSelect( true, m_pm, _T("OpHDMI3") );
// 		break;	
// 	case emTVYpbPr:
// 		ICncCommonOp::OptionSelect( true, m_pm, _T("OpYPbPr") );
// 		break;	
// 	case emTVCVBS1:
// 		ICncCommonOp::OptionSelect( true, m_pm, _T("OpCVBs1") );
// 		break;	
// 	case emTVCVBS2:
// 		ICncCommonOp::OptionSelect( true, m_pm, _T("OpCVBs2") );
// 		break;	
// 	case emTVComputer:
// 		ICncCommonOp::OptionSelect( true, m_pm, _T("OpSPC") );
// 		break;
// 
// 	case emTVHDMI4:
// 		ICncCommonOp::OptionSelect( true, m_pm, _T("OpVGA") );
// 		break;
// 	}
// 
// 	switch(emTVAudVisMode)
// 	{
// 	case emTVAVStandardMode:
// 		ICncCommonOp::OptionSelect( true, m_pm, _T("OpVStandard") );
// 		break;
// 	case emTVAVMovieMode:
// 		ICncCommonOp::OptionSelect( true, m_pm, _T("OpVTV") );
// 		break;	
// 	case emTVAVUserMode:
// 		ICncCommonOp::OptionSelect( true, m_pm, _T("OpVUser") );
// 		break;	
// 	case emTVAVComputerMode:
// 		ICncCommonOp::OptionSelect( true, m_pm, _T("OpVPC") );
// 		break;
// 	}
// 
// 	switch(emTVDisplayMode)
// 	{
// 	case emTVDisFullScrMode:
// 		ICncCommonOp::OptionSelect( true, m_pm, _T("OpFS") );
// 		break;
// 	case emTVDisPanoramaMode:
// 		ICncCommonOp::OptionSelect( true, m_pm, _T("OpFView") );
// 		break;	
// 	case emTVDisPointMode:
// 		ICncCommonOp::OptionSelect( true, m_pm, _T("OpPTP") );
// 		break;	
// 	case emTVDisStandardMode:
// 		ICncCommonOp::OptionSelect( true, m_pm, _T("OpStandard") );
// 		break;
// 	}
// 
// 	return true;
// }

bool CCenterMonitorLogic::OnBtnAirAll( TNotifyUI& msg )
{
	return true;
}
bool CCenterMonitorLogic::OnBtnTempMinus( TNotifyUI& msg )
{
	if (m_dwAirconScreenSelId == -1)
	{
		ShowMessageBox(_T("请先选择要控制的空调"));
		return true;
	}

	if (m_vecTCentreACCfg.at(m_dwAirconScreenSelId).bySetTemp == 17)
	{
		return true;
	}

	u8 byTemp = m_vecTCentreACCfg.at(m_dwAirconScreenSelId).bySetTemp -- ;
	ComInterface->SetACTemp(byTemp);
	return true;
}
bool CCenterMonitorLogic::OnBtnTempPlus( TNotifyUI& msg )
{
	if (m_dwAirconScreenSelId == -1)
	{
		ShowMessageBox(_T("请先选择要控制的空调"));
		return true;
	}
	if (m_vecTCentreACCfg.at(m_dwAirconScreenSelId).bySetTemp == 30)
	{
		return true;
	}

	u8 byTemp = m_vecTCentreACCfg.at(m_dwAirconScreenSelId).bySetTemp ++ ;
	ComInterface->SetACTemp(byTemp);
	return true;
}

bool CCenterMonitorLogic::OnBtnWindPlus( TNotifyUI& msg )
{
	if (m_dwAirconScreenSelId == -1)
	{
		ShowMessageBox(_T("请先选择要控制的空调"));
		return true;
	}
	EmCentreACAirVol em;
	if (m_vecTCentreACCfg.at(m_dwAirconScreenSelId).emACAirVol == emCenACVol5)
	{
		return true;
	}
	else if (m_vecTCentreACCfg.at(m_dwAirconScreenSelId).emACAirVol == emCenACVol4)
	{
		em = emCenACVol5;
	}
	else if (m_vecTCentreACCfg.at(m_dwAirconScreenSelId).emACAirVol == emCenACVol3)
	{
		em = emCenACVol4;
	}
	else if (m_vecTCentreACCfg.at(m_dwAirconScreenSelId).emACAirVol == emCenACVol2)
	{
		em = emCenACVol3;
	}
	else if (m_vecTCentreACCfg.at(m_dwAirconScreenSelId).emACAirVol == emCenACVol1)
	{
		em = emCenACVol2;
	}
	else if (m_vecTCentreACCfg.at(m_dwAirconScreenSelId).emACAirVol == emCenACVolAuto)
	{
		em = emCenACVol1;
	}

	ComInterface->SetACAirVol(em);
	return true;
}
bool CCenterMonitorLogic::OnBtnWindMinus( TNotifyUI& msg )
{
	if (m_dwAirconScreenSelId == -1)
	{
		ShowMessageBox(_T("请先选择要控制的空调"));
		return true;
	}
	EmCentreACAirVol em;
	if (m_vecTCentreACCfg.at(m_dwAirconScreenSelId).emACAirVol == emCenACVol1)
	{
		return true;
	}
	else if (m_vecTCentreACCfg.at(m_dwAirconScreenSelId).emACAirVol == emCenACVol5)
	{
		em = emCenACVol4;
	}
	else if (m_vecTCentreACCfg.at(m_dwAirconScreenSelId).emACAirVol == emCenACVol4)
	{
		em = emCenACVol3;
	}
	else if (m_vecTCentreACCfg.at(m_dwAirconScreenSelId).emACAirVol == emCenACVol3)
	{
		em = emCenACVol2;
	}
	else if (m_vecTCentreACCfg.at(m_dwAirconScreenSelId).emACAirVol == emCenACVol2)
	{
		em = emCenACVol1;
	}
	else if (m_vecTCentreACCfg.at(m_dwAirconScreenSelId).emACAirVol == emCenACVolAuto)
	{
		em = emCenACVol1;
	}
	ComInterface->SetACAirVol(em);
	return true;
}

bool CCenterMonitorLogic::OnBtnWindAuto( TNotifyUI& msg )
{
	ComInterface->SetACAirVol( emCenACVolAuto );
	return true;
}

bool CCenterMonitorLogic::OnACStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	ComInterface->GetCentreACCfg( m_vecTCentreACCfg );

	u8 wAirNum = (u8)wParam;
	if (wAirNum == 0)
	{
		//不可用时 隐藏此tab 2015-7-8
		ICncCommonOp::ShowControl(false,m_pm,_T("Aircon"));
		ICncCommonOp::ShowControl(false,m_pm,_T("airlayout"));
		ICncCommonOp::ShowControl(false,m_pm,_T("ctlAir"));
		//选中第一项
		COptionUI *pOpAir = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("Aircon"));
		if (pOpAir && pOpAir->IsSelected())
		{
			COptionUI *pOp = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("Switch"));
			if (pOp)
			{
				pOp->Selected(true);
			}
		}

		return true;
	}
	else
	{
		ICncCommonOp::ShowControl(true,m_pm,_T("Aircon"));
		ICncCommonOp::ShowControl(true,m_pm,_T("airlayout"));
		ICncCommonOp::ShowControl(true,m_pm,_T("ctlAir"));
	}

	CTouchListUI *pAirconditionList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("AirconditionList") );
	if ( pAirconditionList == NULL )
	{
		return false;
	}

	if (pAirconditionList->GetCount() != m_vecTCentreACCfg.size())
	{
		pAirconditionList->RemoveAll();
		CString strCol = _T("");
		strCol.Format(_T("%d"),m_vecTCentreACCfg.size());
		pAirconditionList->SetAttribute(_T("columns"),strCol);
		for ( int dwIndex = 0; dwIndex < m_vecTCentreACCfg.size(); dwIndex++ )
		{
			CListContainerElementUI *pAircondListContainer = 
				(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("AirConListItem") );
			if (!pAircondListContainer)
			{
				return false;
			}

			CString strText=_T("");
			strText.Format(_T("空调0%d"),dwIndex+1);
			ICncCommonOp::SetControlText( (LPCTSTR)strText,m_pm,_T("lbScreenAircon"),pAircondListContainer);

			if (updateACState(pAircondListContainer,m_vecTCentreACCfg.at(dwIndex),dwIndex))
			{
				pAirconditionList->Add(pAircondListContainer);
			}			
		}
	}
	else
	{
		for ( int dwIndex = 0; dwIndex < m_vecTCentreACCfg.size(); dwIndex++ )
		{
			CListContainerElementUI *pAircondListContainer = (CListContainerElementUI *)pAirconditionList->GetItemAt(dwIndex);
			if (pAircondListContainer)
			{
				updateACState(pAircondListContainer,m_vecTCentreACCfg.at(dwIndex),dwIndex);
			}
		}
	}

	return true;
}

bool CCenterMonitorLogic::updateACState(CListContainerElementUI *pAircondListContainer, TCentreACCfg tCentreACCfg, u32 dwIndex)
{
	CCheckBoxUI* pCheckBoxAircond = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckStart"), pAircondListContainer);
	CLabelUI* plbMode = NULL;
	switch(tCentreACCfg.emACMode)
	{
	case emCenACBlowIn:
		plbMode = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbWind"), pAircondListContainer);
		break;
	case emCenACheat:
		plbMode = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbHot"), pAircondListContainer);
		break;
	case emCenAcref:
		plbMode = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbCold"), pAircondListContainer);
		break;
	case emCenACdeh:
		plbMode = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbWet"), pAircondListContainer);
		break;
	}
	if (!plbMode)
	{
		return false;
	}
	plbMode->SetAttribute(_T("textcolor"),_T("#FFFFFFFF"));
	if ( !pCheckBoxAircond)
	{
		return false;
	}

	bool bSet = false;
	if (tCentreACCfg.emACPower == emCenACPowerOn)
	{
		bSet = true;
	}
	m_mapIsAirCon[dwIndex] = bSet;
	pCheckBoxAircond->SetCheckNoMsg(bSet);

	u8 nTemp = tCentreACCfg.bySetTemp;
	CLabelUI* plbDenTemp = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbDec"), pAircondListContainer);
	CLabelUI* plbTemp = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbNum"), pAircondListContainer);
	if (!plbDenTemp || !plbTemp)
	{
		return false;
	}
	
	CString strNum = _T("");
	strNum.Format(_T("res/centerctrl/%d.png"),nTemp/10);
	plbDenTemp->SetBkImage(strNum);
	strNum.Format(_T("res/centerctrl/%d.png"),nTemp%10);
	plbTemp->SetBkImage(strNum);
	

	CLabelUI* plbAirVolum = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbAirVolum"), pAircondListContainer);
	if (!plbAirVolum)
	{
		return false;
	}

	switch(tCentreACCfg.emACAirVol)
	{
	case emCenACVol1:
		plbAirVolum->SetBkImage(_T("airvolume1"));
		break;
	case emCenACVol2:
		plbAirVolum->SetBkImage(_T("airvolume2"));
		break;
	case emCenACVol3:
		plbAirVolum->SetBkImage(_T("airvolume3"));
		break;
	case emCenACVol4:
		plbAirVolum->SetBkImage(_T("airvolume4"));
		break;
	case emCenACVol5:
		plbAirVolum->SetBkImage(_T("airvolume_full"));
		break;
	case emCenACVolAuto:
		plbAirVolum->SetBkImage(_T("airvolume_full"));
		break;
	}

	if (tCentreACCfg.emACPower == emCenACPowerOff)
	{
		plbAirVolum->SetBkImage(_T("airvolume_off"));
	}

	return true;
}

bool CCenterMonitorLogic::OnSelectAirInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bOk = lParam;
	u8 by = wParam;
	if (!bOk)
	{
		CString str = _T("");
		str.Format(_T("空调0%d选择失败"), by+1);
		ShowPopMsg(str);
		CTouchListUI *pACListLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("AirconditionList") );
		if (pACListLayoutUI)
		{
			pACListLayoutUI->SelectItem(m_dwAirconScreenSelId);
		}
	}
	else
	{
		m_dwAirconScreenSelId = (u8)wParam; 
	}
	
	return NO_ERROR;
}

bool CCenterMonitorLogic::OnAirPowerInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	EmCentreACPower em = (EmCentreACPower)wParam;
	u8 by = (u8)lParam;
	bool bOk = true;
	CString str = _T("");
	str.Format(_T("空调0%d关闭失败"),by+1);
	if (em == emCenACPowerOn)
	{
		bOk = false;
		str.Format(_T("空调0%d开启失败"),by+1);
	}
	m_mapIsAirCon[by] = bOk;

	CTouchListUI *pACListLayoutUI = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("AirconditionList") );
	if (pACListLayoutUI)
	{
		CListContainerElementUI* pItem = (CListContainerElementUI*)pACListLayoutUI->GetItemAt(by);
		if (pItem)
		{
			CCheckBoxUI* pCheck = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckStart"),pItem);
			if (pCheck)
			{
				pCheck->SetCheckNoMsg(bOk);
			}
		}
	}

	ShowPopMsg(str);

	return true;
}

bool CCenterMonitorLogic::OnScreenMonitorItemClick( TNotifyUI& msg )
{
	bool bIsKGmonitor = false;
	if (m_atModitorCfg->emTvModle == emKangGuan70B17)
	{
		bIsKGmonitor = true;
	}
	int nIndex = -1;
	if ( const CTouchListUI *pItem = dynamic_cast<const CTouchListUI*>(msg.pSender) )
	{
		nIndex = pItem->GetCurSel();
	}
	if (nIndex == -1)
	{
		if (!bIsKGmonitor)
		{
			ICncCommonOp::SetControlText(_T("显示器 调节"),m_pm,_T("lbMonitor"));
		}
		return true;
	}

	if (!bIsKGmonitor)
	{
		CString str = _T("");
		str.Format(_T("显示器0%d 调节"),nIndex+1);
		ICncCommonOp::SetControlText(str,m_pm,_T("lbMonitor"));
	}

	if (nIndex == m_dwMonitorScreenSelId)
	{
		return true;
	}

	ComInterface->SelectTVMonitor(msg.wParam);
	return true;
}

bool CCenterMonitorLogic::OnDisPlayShowNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    m_bDisplayShow = (BOOL)wParam;
    
    if (m_bDisplayShow)
    {
        ICncCommonOp::ShowControl(true,m_pm,_T("Monitor"));
    }
    else
    {
        COptionUI *pOpMonitor = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("Monitor"));
        if (pOpMonitor && pOpMonitor->IsSelected())
        {
            //选中默认项
            COptionUI *pOp = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("Switch"));
            if (pOp)
            {
                pOp->Selected(true);
            }
        }
        ICncCommonOp::ShowControl(false,m_pm,_T("Monitor"));
    }

    return true;
}