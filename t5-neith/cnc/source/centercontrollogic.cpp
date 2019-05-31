#include "StdAfx.h"
#include "centercontrollogic.h"
#include "confmsglogic.h"
#include "messageboxlogic.h"
#include "centermonitorlogic.h"

template<> CCenterCtrlLogic* Singleton<CCenterCtrlLogic>::ms_pSingleton  = NULL;
#define CENTERCTRL_TIMER_INTERVAL     500

APP_BEGIN_MSG_MAP(CCenterCtrlLogic,CNotifyUIImpl)
MSG_CREATEWINDOW(_T("CenterCtrlLayout"), OnCreate)
	MSG_INIWINDOW(_T("RoomCtrlLayout"), OnInit)

	MSG_CLICK(_T("BtnNoticeBack"), OnBtnNoticeBack)
	
	//文档摄像机控制
    MSG_ITEMSELECTD(_T("ComboDCamSel"), OnComboDCamSel)

	MSG_CLICK(_T("BtnSnapShot"), OnBtnSnapShot)
	MSG_CLICK(_T("BtnAutoFocus"), OnBtnAutoFocus)
	MSG_CLICK(_T("BtnAutoWB"), OnBtnAutoWB)
	MSG_CLICK(_T("BtnSavePrepose"), OnBtnSavePrepose)
	MSG_CLICK(_T("BtnCamPlus"), OnBtnCamPlus)
	MSG_CLICK(_T("BtnCamMinus"), OnBtnCamMinus)

	MSG_BUTTONDOWN(_T("BtnCamPlus"), OnBtnCamPlusDown)
	MSG_BUTTONDOWN(_T("BtnCamMinus"), OnBtnCamMinusDown)

	MSG_SELECTCHANGE(_T("CheckCam"), OnCheckCam) 

	MSG_SELECTCHANGE(_T("preposeA3"), OnOppreposeA3)
	MSG_SELECTCHANGE(_T("preposeA4"), OnOppreposeA4)     
	MSG_SELECTCHANGE(_T("preposeA5"), OnOppreposeA5)

	//开关面板相关
	MSG_CLICK(_T("BtnShutdownSys"), OnBtnShutdownSys)
	MSG_SELECTCHANGE(_T("BtnShutdownSys"), OnBtnShutdownSys) //OnCheckSys

	MSG_SELECTCHANGE(_T("CheckAllLight"), OnCheckAllLight) 
	MSG_SELECTCHANGE(_T("CheckConfLight"), OnCheckConfLight) 
	MSG_SELECTCHANGE(_T("CheckBgLight"), OnCheckBgLight) 

	//窗帘控制
	MSG_CLICK(_T("BtnCuitainStop"), OnBtnCuitainStop)
	MSG_CLICK(_T("BtnCuitainUp"), OnBtnCuitainUp)
	MSG_CLICK(_T("BtnCuitainDown"), OnBtnCuitainDown)

	MSG_SELECTCHANGE(_T("opAll"), OnopAll)  
	MSG_SELECTCHANGE(_T("curtain1"), Oncurtain1)
	MSG_SELECTCHANGE(_T("curtain2"), Oncurtain2)    
	MSG_SELECTCHANGE(_T("curtain3"), Oncurtain3)
	MSG_SELECTCHANGE(_T("curtain4"), Oncurtain4)    
	MSG_SELECTCHANGE(_T("curtain5"), Oncurtain5)
	MSG_SELECTCHANGE(_T("curtain6"), Oncurtain6)    

	//中控相关
	MSG_SELECTCHANGE(_T("Monitor"), OnTabMonitor)
	MSG_SELECTCHANGE(_T("Aircon"), OnTabAirCondition)
	MSG_SELECTCHANGE(_T("Switch"), OnTabSwitch)
	MSG_SELECTCHANGE(_T("Matrix"), OnTabMatrix)
    MSG_SELECTCHANGE(_T("Screen"), OnTabScreen)
//	MSG_SELECTCHANGE(_T("Camera"), OnTabCamera)
	MSG_SELECTCHANGE(_T("Curtain"), OnTabCurtain)

	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)

	//开关面板相关
	USER_MSG(UI_CNS_SCHPOWER_IND,OnCerterPowerInd)
	USER_MSG(UI_CNS_SCHALLLIGHT_IND,OnAllLightInd)
	USER_MSG(UI_CNS_SCHMIDLIGHT_IND,OnConfLightInd)
	USER_MSG(UI_CNS_SCHSCRLIGHT_IND,OnBgLightInd)
	USER_MSG(UI_CNS_SCHSTATE_NTY,OnCenterStateNty)
	USER_MSG(UI_CNS_SCHTEMP_NTY,OnSchTempNty)

	//文档摄像机控制
    USER_MSG(UI_CNS_DCAMSELECTED_IND,OnDCamSelectedInd)
	USER_MSG(UI_CNS_DCAMSTATE_NTY,OnDCamStateNty)
	USER_MSG(UI_CNS_DCAMPOWER_IND,OnDCamPowerInd)
	USER_MSG(UI_CNS_DOCSNAPSHOT_IND,OnDocSnapShotInd)
	USER_MSG(UI_CNS_DCAMPREPOS_IND,OnDocCamPrePosSelInd)
	USER_MSG(UI_CNS_DCAMTYPE_IND,OnDocCamTypeInd)
	USER_MSG(UI_CNS_DCAMZOOM_IND,OnDCamZoomInd)

	//窗帘相关
	USER_MSG(UI_TPAD_CURTAINSTATE_NTY,OnCurtainStateNty)

	USER_MSG(WM_CNC_DOCSNAPSHOTROGRESS,OnDownloadProgress)

	//电视机状态
	USER_MSG(UI_CNS_TVSTATE_NTY,OnMonitorStateNty)

    USER_MSG(UI_CNSETFTPRSP, OnSetCnFtpRsp)

APP_END_MSG_MAP()


static UINT g_nCenterCtrlTimerID = 0;
VOID CALLBACK CCenterCtrlTimerFun( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{
	if ( idEvent == g_nCenterCtrlTimerID )
	{
		CCenterCtrlLogic::GetSingletonPtr()->UpdateTimer();
	}
}

const String CCenterCtrlLogic::m_strSldTab = _T("slidetab");

CCenterCtrlLogic::CCenterCtrlLogic(void)
{
	m_bOff = FALSE;

	m_nUpdateTime = 0;
	m_nWaitTime = 0;
	m_wLocalTemp = 0;

	m_emRecallNum = emDCamRecallInvalid;
	m_nCurNum = 0;

	memset( m_achIsCurCheck, 0, 6*sizeof(BOOL) );
	m_strLogFolderPath = _T("");

    m_bIsShotcupOpenFtp = false;

    m_byDCamSelIndex = 0;
}

CCenterCtrlLogic::~CCenterCtrlLogic(void)
{
}

bool CCenterCtrlLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_bOff = FALSE;

	m_nUpdateTime = 0;
	m_nWaitTime = 0;
	m_wLocalTemp = 0;
	NoDegree();

	EndWaiting();
	 
	m_emRecallNum = emDCamRecallInvalid;
	m_nCurNum = 0;

	memset( m_achIsCurCheck, 0, 6*sizeof(BOOL) );
	ICncCommonOp::EnableControl(true, m_pm, _T("CheckCam"));
	EnableCam(false);
	ICncCommonOp::ShowControl( false, m_pm, _T("PageNotice") );

    m_bIsShotcupOpenFtp = false;
    m_byDCamSelIndex = 0;

	return true;
}

void CCenterCtrlLogic::NoDegree()
{
	ICncCommonOp::ShowControl(true,m_pm,_T("lbDegreeNo"));
	ICncCommonOp::ShowControl(false,m_pm,_T("lbpicdecate"));
	ICncCommonOp::ShowControl(false,m_pm,_T("lbpicdegree"));
	ICncCommonOp::ShowControl(false,m_pm,_T("lbdegreeimg"));
}

bool CCenterCtrlLogic::OnCreate( TNotifyUI& msg )
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
 
bool CCenterCtrlLogic::OnInit( TNotifyUI& msg )
{
	ComInterface->GetLocalCnsInfo( m_SelCnsInfo );

	CTouchListUI *pMonitorList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("MonitorList") );
	if ( pMonitorList == NULL )
	{
		return false;
	}

	pMonitorList->RemoveAll();
	for ( int dwIndex = 1; dwIndex <= 3; dwIndex++ )
	{
		CListContainerElementUI *pMonitorListContainer = 
			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("CenterScreenListItem") );

		CString strText = _T("");
		strText.Format(_T("显示器0%d"),dwIndex);

		ICncCommonOp::SetControlText( (LPCTSTR)strText,m_pm,_T("lbScreenLogo"),pMonitorListContainer);
		ICncCommonOp::ShowControl( false, m_pm, _T("lbScreenBanner"), pMonitorListContainer );

		CCheckBoxUI* pCheckBoxMonitor = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckScreen"), pMonitorListContainer);

		if ( pCheckBoxMonitor)
		{
			pCheckBoxMonitor->SetTag(dwIndex);
		}

		pMonitorList->Add(pMonitorListContainer);
	}

	ICncCommonOp::SetControlBkImg(_T("res//public//refresh.png"),m_pm,_T("lbStatePic"));
	ICncCommonOp::ShowControl( true, m_pm, _T("LbProcess") );
	ICncCommonOp::ShowControl( false, m_pm, _T("PageNotice") );

	SetIsCurCanCtrl(false);

	CCenterMonitorLogic::GetSingletonPtr()->updateMonitorState();

	//夏普显示器隐藏开关
	HideMonitorSwitch();
	return true;
}

bool CCenterCtrlLogic::HideMonitorSwitch()
{
	TCentreTVCfg  atTVCfg[MAX_CENTRETV_NUM];
	memcpy( atTVCfg , ComInterface->GetCentreTVCfg(), sizeof(TCentreTVCfg) * MAX_CENTRETV_NUM );

	bool bShow = true;
	EmTVModle emTVType = atTVCfg->emTvModle;
	if ( emSharp70LCD_LX640A == emTVType
		 || emSharp70LX550A == emTVType
		 || emSharp70LX565A == emTVType)
	{
		bShow = false;
	}

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
					pCheckBox->SetVisible(bShow);
				}
			}
		}	
	}
	return true;
}

bool CCenterCtrlLogic::OnTabMonitor( TNotifyUI& msg )
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, m_strSldTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(emTabID_Monitor);
	}
	return true;
}

bool CCenterCtrlLogic::OnTabAirCondition( TNotifyUI& msg )
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, m_strSldTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(emTabID_AirCondition);
	}
	return true;
}

bool CCenterCtrlLogic::OnTabSwitch( TNotifyUI& msg )
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, m_strSldTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(emTabID_Switch);
	}
	return true;
}

bool CCenterCtrlLogic::OnTabMatrix( TNotifyUI& msg )
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, m_strSldTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(emTabID_Matrix);
	}
	return true;
}

bool CCenterCtrlLogic::OnTabScreen( TNotifyUI& msg )
{
    CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, m_strSldTab.c_str() );
    if (pControl)
    {
        pControl->SelectItem(emTabID_Srceen);
    }
    return true;
}

/*bool CCenterCtrlLogic::OnTabCamera( TNotifyUI& msg )
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, m_strSldTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(emTabID_Camera);
	}

	return true;
}*/

bool CCenterCtrlLogic::OnTabCurtain( TNotifyUI& msg )
{
	CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( m_pm, m_strSldTab.c_str() );
	if (pControl)
	{
		pControl->SelectItem(emTabID_Curtain);
	}
	return true;
}

bool CCenterCtrlLogic::OnBtnShutdownSys( TNotifyUI& msg )
{
// 	CCheckBoxUI *pCheckBox = (CCheckBoxUI*)msg.pSender;
// 
// 	bool bCheck = false;
// 	if (pCheckBox && pCheckBox->GetCheck())
// 	{
// 		bCheck = true;
// 	}

// 	EnableSwitch(bCheck);
// 	
// 	if (m_bCheckSysState)
// 	{
// 		m_bCheckSysState = false;
// 		return true;
// 	}

	bool bShut = ShowMessageBox(_T("是否确认关闭系统"),true);
	if (!bShut)
	{
		return true;
	}

	ComInterface->SetSysPower( emSchPowerToggle );
	g_nCenterCtrlTimerID = SetTimer( NULL, 0, CENTERCTRL_TIMER_INTERVAL, CCenterCtrlTimerFun );

	m_nWaitTime = 0;
	m_nUpdateTime = 0;
	
	ICncCommonOp::SetControlText( _T("请稍候..."), m_pm, _T("LbProcess") );
	ICncCommonOp::SetControlText( _T(""), m_pm, _T("LabelTip") );
	ICncCommonOp::ShowControl( true, m_pm, _T("PageNotice") );
	return true;
}

void CCenterCtrlLogic::EnableSwitch( bool bIsEnable )
{
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("CheckAllLight"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("CheckConfLight"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("CheckBgLight"));
}

bool CCenterCtrlLogic::OnCheckAllLight( TNotifyUI& msg )
{
	CCheckBoxUI *pCheckBox = (CCheckBoxUI*)msg.pSender;

	bool bCheck = false;
	if (pCheckBox && pCheckBox->GetCheck())
	{
		bCheck = true;
	}

	TCentreSchCfg tSchCfg;
	ComInterface->GetCentreSchCfg(tSchCfg);
	if ( tSchCfg.emSchLight == emSchLightOn && bCheck)
	{
		return true;
	}

	if ( tSchCfg.emSchLight != emSchLightOn && !bCheck)
	{
		return true;
	}

	if ( bCheck )
	{
		ComInterface->SetSysAllLight( emSchLightOn );
	}
	else
	{
		ComInterface->SetSysAllLight( emSchLightOff  );
	}

	ICncCommonOp::EnableControl(false, m_pm, _T("CheckAllLight"));
	/*	ComInterface->SetSysAllLight( emSchLightToggle );*/

	return true;
}

bool CCenterCtrlLogic::OnCheckConfLight( TNotifyUI& msg )
{
	CCheckBoxUI *pCheckBox = (CCheckBoxUI*)msg.pSender;

	bool bCheck = false;
	if (pCheckBox && pCheckBox->GetCheck())
	{
		bCheck = true;
	}

	TCentreSchCfg tSchCfg;
	ComInterface->GetCentreSchCfg(tSchCfg);
	if ( tSchCfg.emSchMidLight == emSchMidLightOn && bCheck)
	{
		return true;
	}

	if ( tSchCfg.emSchMidLight != emSchMidLightOn && !bCheck)
	{
		return true;
	}
	
	if ( bCheck )
	{
		ComInterface->SetSysMainLight( emSchMidLightOn );
	}
	else
	{
		ComInterface->SetSysMainLight( emSchMidLightOff );
	}
	ICncCommonOp::EnableControl(false, m_pm, _T("CheckConfLight"));

	return true;
}

//用于补光灯
bool CCenterCtrlLogic::OnCheckBgLight( TNotifyUI& msg )
{
	CCheckBoxUI *pCheckBox = (CCheckBoxUI*)msg.pSender;

	bool bCheck = false;
	if (pCheckBox && pCheckBox->GetCheck())
	{
		bCheck = true;
	}

	TCentreSchCfg tSchCfg;
	ComInterface->GetCentreSchCfg(tSchCfg);
	if ( tSchCfg.emSchScrLight == emSchScrLightOn && bCheck)
	{
		return true;
	}

	if ( tSchCfg.emSchScrLight != emSchScrLightOn && !bCheck)
	{
		return true;
	}

	if ( bCheck )
	{
		ComInterface->SetSysAuxiLight( emSchScrLightOn );
	}
	else
	{
		ComInterface->SetSysAuxiLight( emSchScrLightOff  );
	}

	ICncCommonOp::EnableControl(false, m_pm, _T("CheckBgLight"));
	/*	ComInterface->SetSysAuxiLight( emSchScrLightToggle );*/

	return true;
}

bool CCenterCtrlLogic::OnAllLightInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bOk = (BOOL)wParam;  
	EmSchPower emPower = (EmSchPower)lParam;

	ICncCommonOp::EnableControl(true, m_pm, _T("CheckAllLight"));
	if (bOk)
	{
		return true;
	}
	else
	{
		CCheckBoxUI* pCheckAllLight = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckAllLight"));
		if (pCheckAllLight)
		{
			bool bCheck = false;
			if (emPower != emSchPowerOn)//不是开启失败 即为关闭失败 所以是on
			{
				bCheck = true;
			}
			pCheckAllLight->SetCheckNoMsg(bCheck);
			if (bCheck)
			{
				ShowPopMsg(_T("关闭所有灯光操作失败"));
			}
			else
			{
				ShowPopMsg(_T("开启所有灯光操作失败"));
			}
		}
	}
	return true;
}

bool CCenterCtrlLogic::OnConfLightInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bOk = (BOOL)wParam;  
	EmSchPower emPower = (EmSchPower)lParam;
	ICncCommonOp::EnableControl(true, m_pm, _T("CheckConfLight"));
	if (bOk)
	{
		return true;
	}
	else
	{
		CCheckBoxUI* pCheckConfLight = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckConfLight"));
		if (pCheckConfLight)
		{
			bool bCheck = false;
			if (emPower != emSchPowerOn)
			{
				bCheck = true;
			}
			pCheckConfLight->SetCheckNoMsg(bCheck);
		}
	}
	return true;
}

bool CCenterCtrlLogic::OnBgLightInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bOk = (BOOL)wParam;  
	EmSchPower emPower = (EmSchPower)lParam;
	ICncCommonOp::EnableControl(true, m_pm, _T("CheckBgLight"));

	if (bOk)
	{
		return true;
	}
	else
	{
		CCheckBoxUI* pCheckBgLight = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckBgLight"));
		if(emPower == emSchPowerOn)
		{
			if (pCheckBgLight)
			{
				pCheckBgLight->SetCheckNoMsg(false);
			}
			ShowPopMsg(_T("开启背景墙灯失败"));
		}
		else
		{
			if (pCheckBgLight)
			{
				pCheckBgLight->SetCheckNoMsg(true);
			}
			ShowPopMsg(_T("关闭背景墙灯失败"));
		}

	}
	return true;
}

bool CCenterCtrlLogic::OnCerterPowerInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bOk = (BOOL)wParam;  
	EmSchPower emPower = (EmSchPower)lParam;
	ICncCommonOp::EnableControl(true, m_pm, _T("BtnShutdownSys"));

	//CCheckBoxUI* pCheckSys = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("BtnShutdownSys"));

	if ( !bOk )
	{    
		//ShowMessageBox(_T("中控电源操作失败"),false);
		//pCheckSys->SetCheck(!pCheckSys->GetCheck());

		if ( emPower == emSchPowerOn )
		{
			ICncCommonOp::SetControlText( _T("系统启动失败,请稍候重试..."), m_pm, _T("LbProcess") ); 
		}
		else
		{
			ICncCommonOp::SetControlText( _T("系统关闭失败,请稍候重试..."), m_pm, _T("LbProcess") ); 
		}
		return NO_ERROR;
	}

	if ( emPower == emSchPowerOn )
	{
		ICncCommonOp::SetControlText( _T("系统正在启动，请稍候..."), m_pm, _T("LbProcess") ); 
		m_nWaitTime = 30 * 2;
		m_bOff = FALSE;
	}
	else
	{
		ICncCommonOp::SetControlText( _T("系统正在关闭，请稍候..."), m_pm, _T("LbProcess") ); 
		m_nWaitTime = 10 * 2;
		m_bOff = TRUE;
	}

	CString strLeftTime;
	strLeftTime.Format( _T("剩余 %d秒"), m_nWaitTime / 2 );
	ICncCommonOp::SetControlText( strLeftTime, m_pm, _T("LabelTip") ); 

	m_nUpdateTime = 0;

	return NO_ERROR;
}

bool CCenterCtrlLogic::OnCenterStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TCentreSchCfg tSchCfg;
	ComInterface->GetCentreSchCfg(tSchCfg);

	//电源
// 	CCheckBoxUI* pCheckSys = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("BtnShutdownSys"));
// 	if (pCheckSys->GetCheck())
// 	{
// 		bCheck = true;
// 	}
	
	bool bCheck = false;//现在状态
	bool bOn = false;//是否已经开启
	if ( tSchCfg.emSchPower == emSchPowerOn )
	{
		bOn = true;

		//ICncCommonOp::EnableControl(true, m_pm, _T("BtnShutdownSys"));
		EnableSwitch(true);
		//初次登录时温度处理
		u16 wTemp = tSchCfg.wSchTem;
		if ( m_wLocalTemp != wTemp )
		{
			m_wLocalTemp = wTemp;
			UpdateTempImg( m_wLocalTemp );
		} 
	}
	else
	{
		NoDegree();
		//ICncCommonOp::EnableControl(false, m_pm, _T("BtnShutdownSys"));   是否要禁用？？  dyy 2015-4-27
		EnableSwitch(false);
	}
	
// 	if (bCheck != bOn)
// 	{
// 		m_bCheckSysState = true;
// 		pCheckSys->SetCheck(bOn);
// 	}
	//所有灯光
	CCheckBoxUI* pCheckAllLight = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckAllLight"));
	bCheck = false;
	bOn = false;
	if (!pCheckAllLight)
	{
		return false;
	}
	if ( pCheckAllLight->GetCheck())
	{
		bCheck = true;
	}

	if ( tSchCfg.emSchLight == emSchLightOn )
	{
		bOn = true;
	}

	if (bCheck != bOn)
	{
		pCheckAllLight->SetCheckNoMsg(bOn);
	}

// 	if ( !m_bCurtainLogicExist )
// 	{

	//会议灯光
// 	CCheckBoxUI* pCheckConfLight = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckConfLight"));
// 	bCheck = false;
// 	bOn = false;
// 	if (!pCheckConfLight)
// 	{
// 		return false;
// 	}
// 	if (pCheckConfLight && pCheckConfLight->GetCheck())
// 	{
// 		bCheck = true;
// 	}
// 
// 	if ( tSchCfg.emSchMidLight == emSchMidLightOn )
// 	{
// 		bOn = true;
// 	}
// 	if (bCheck != bOn)
// 	{
// 		pCheckConfLight->SetCheckNoMsg(bOn);
// 	}
	//背景灯光 //用于补光 2015-8-19
	CCheckBoxUI* pCheckBgLight = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckBgLight"));
	bCheck = false;
	bOn = false;
	if (!pCheckBgLight)
	{
		return false;
	}
	if (pCheckBgLight->GetCheck())
	{
		bCheck = true;
	}

	if ( tSchCfg.emSchScrLight == emSchScrLightOn )
	{
		bOn = true;
	}
	if (bCheck != bOn)
	{
		pCheckBgLight->SetCheckNoMsg(bOn);
	}

	return NO_ERROR;
}

void CCenterCtrlLogic::UpdateTimer()
{
	if ( m_nWaitTime > 0 )
	{    
		m_nUpdateTime++;
		int nLeftTime = ( m_nWaitTime - m_nUpdateTime ) / 2;
		CString strLeftTime;
		strLeftTime.Format( _T("剩余 %d秒"), nLeftTime );
		ICncCommonOp::SetControlText( strLeftTime, m_pm, _T("LabelTip") );
		if ( m_nUpdateTime > m_nWaitTime )
		{
			//等待结束
			EndWaiting();
		}
	}
	//原代码修改 一直没ind 自加十次
	if ( m_nWaitTime == 0 && m_nUpdateTime < 10 )
	{
		m_nUpdateTime++;
	} 

	if ( m_nWaitTime == 0 && m_nUpdateTime > 10 )
	{
		EndWaiting();
	}   
}


void CCenterCtrlLogic::EndWaiting()
{ 
	KillTimer( NULL, g_nCenterCtrlTimerID );
	g_nCenterCtrlTimerID = 0;
	ICncCommonOp::ShowControl( false, m_pm, _T("PageNotice") );
	if ( 0 != m_nWaitTime && m_bOff )
	{
//		ComInterface->DisConnectTpad();
	}
	m_nWaitTime = 0;
	m_nUpdateTime = 0;
}

bool CCenterCtrlLogic::OnBtnNoticeBack( TNotifyUI& msg )
{
	EndWaiting();
	return true;
}

bool CCenterCtrlLogic::OnSchTempNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	u16 wTemp = (u16)wParam;

	if ( m_wLocalTemp != wTemp )
	{
		m_wLocalTemp = wTemp;
		UpdateTempImg( m_wLocalTemp );
	}  

	return NO_ERROR;
}

void CCenterCtrlLogic::UpdateTempImg( u16 wTemp )
{
	ICncCommonOp::ShowControl(false,m_pm,_T("lbDegreeNo"));
	ICncCommonOp::ShowControl(true,m_pm,_T("lbpicdecate"));
	ICncCommonOp::ShowControl(true,m_pm,_T("lbpicdegree"));
	ICncCommonOp::ShowControl(true,m_pm,_T("lbdegreeimg"));
	if ( wTemp > 99 )
	{
		return;
	}

	u8 byHigh = wTemp / 10;
	u8 byLow = wTemp % 10;

	CString strImgPath = _T("res/centerctrl/");

	//左边数字
	CString strImage;
	strImage.Format( _T("%d.png"), byHigh );
	strImage = strImgPath + strImage;

	ICncCommonOp::SetControlBkImg(strImage,m_pm,_T("lbpicdecate"));

	//右边数字
	strImage.Format( _T("%d.png"), byLow );
	strImage = strImgPath + strImage;

	ICncCommonOp::SetControlBkImg(strImage,m_pm,_T("lbpicdegree"));
}

//////////////////////////////////////////////////////////////////////////////////
//////文档摄像机控制                                      ///////////////////////
/////////////////////////////////////////////////////////////////////////////////
bool CCenterCtrlLogic::OnDCamStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	//文档摄像机信息
    map<u8, TCentreDCamCfg> mapDCamCfg;
    ComInterface->GetDCamStateMap(mapDCamCfg);
	//全景摄像机信息
	TPanCamInfo tPanCamInfo;
	ComInterface->GetPanCamList( tPanCamInfo );
    //判断文档摄像机是否全部可用
    BOOL bIsDCamUsed = FALSE;
    map<u8, TCentreDCamCfg>::iterator itor = mapDCamCfg.begin();
    for ( ; itor != mapDCamCfg.end() ; itor++ )
    {
        if ( itor->second.bDCamUsed )
        {
            bIsDCamUsed = TRUE;
            break;
        }
    }
    //有一个文档摄像机在使用 则显示Tab
    if ( !bIsDCamUsed )//不可用时 隐藏此tab 2015-6-29
	{
		ICncCommonOp::ShowControl(false,m_pm,_T("OptionFileCam"));
		//如果全景摄像机未开启则关闭tab栏
		if (tPanCamInfo.byPanCamNum == 0)
		{
			ICncCommonOp::ShowControl(false,m_pm,_T("camera"));
			ICncCommonOp::ShowControl(false,m_pm,_T("ctlCam"));
			//选中默认项
			COptionUI *pOp = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("Switch"));
			if (pOp)
			{
				pOp->Selected(true);
			}
		}
		else
		{
			//选中全景摄像机
			COptionUI *pOp = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("OptionFullCam"));
			if (pOp)
			{
				pOp->Selected(true);
			}
		}
		return true;
	}
	else
	{
		//打开tab栏
		ICncCommonOp::ShowControl(true,m_pm,_T("camera"));
		ICncCommonOp::ShowControl(true,m_pm,_T("ctlCam"));

        if (!ICncCommonOp::IsOptionSelected(m_pm,_T("OptionFileCam")))
        {
            ICncCommonOp::ShowControl(true,m_pm,_T("OptionFileCam"));
        }

		if (tPanCamInfo.byPanCamNum == 0)
		{
			//选中文档摄像机
            ICncCommonOp::OptionSelect(true, m_pm, _T("OptionFileCam"));
            m_pm->DoCase(_T("caseNoFullCamera"));
		}
        else
        {
            m_pm->DoCase(_T("caseHaveFullCamera"));
        }
	}
    //更新文档摄像机界面
    CComboUI* pCombo = (CComboUI*)ICncCommonOp::FindControl( m_pm, _T("ComboDCamSel") );
    if (pCombo)
    {
        pCombo->RemoveAll();
        itor = mapDCamCfg.begin();
        for ( ; itor != mapDCamCfg.end() ; itor++ )
        {
            CListLabelElementUI *pListLabelElement = (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
            CString str=_T("");
            str.Format(_T("文档摄像机%d"),itor->first);
            pListLabelElement->SetText(str);
            pCombo->Add(pListLabelElement);
        }
        pCombo->SelectItem(m_byDCamSelIndex);
    }

    TCentreDCamCfg tDCamCfg;
    ComInterface->GetDCamState(tDCamCfg, m_byDCamSelIndex);
	if ( tDCamCfg.emDcamProType == emPELCOPro )
	{
		tDCamCfg.emDCamPowerMode = emDCamPowerOn;
	}

	//设置check状态
	CCheckBoxUI *pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm, _T("CheckCam"));
	if (pCheckBox)
	{
		pCheckBox->SetCheckNoMsg( tDCamCfg.emDCamPowerMode == emDCamPowerOn );
	}

	if ( tDCamCfg.emDCamPowerMode == emDCamPowerOn )
	{
		EnableCam(true);
		ICncCommonOp::EnableControl(true, m_pm, _T("CheckCam"));

		m_emRecallNum = tDCamCfg.emDCamRecallNum;
		if ( m_emRecallNum == emDCamRecallOne )
		{
			ICncCommonOp::OptionSelect( true, m_pm, _T("preposeA3") );
		}
		else if ( m_emRecallNum == emDCamRecallTwo )
		{
			ICncCommonOp::OptionSelect( true, m_pm, _T("preposeA4") );
		}
		else if ( m_emRecallNum == emDCamRecallThree )
		{
			ICncCommonOp::OptionSelect( true, m_pm, _T("preposeA5") );
		}
	}
	else
	{
		EnableCam(false);

		if ( tDCamCfg.emDCamPowerMode == emDCamPowerDown )//没有电 禁用
		{
			ICncCommonOp::EnableControl(false, m_pm, _T("CheckCam"));
		}
	}

    EnableCam(tDCamCfg.bDCamUsed);

	ChangeInterface(tDCamCfg.emDcamProType);

	return NO_ERROR;
}

bool CCenterCtrlLogic::OnDCamSelectedInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    BOOL bIsOk = (BOOL)wParam;
    u8 byIndex = (u8)lParam;
    if (bIsOk)
    {
        m_byDCamSelIndex = byIndex;
        NOTIFY_MSG( UI_CNS_DCAMSTATE_NTY );
    }
    else
    {
        ShowPopMsg(_T("选择文档摄像机失败"));
        CComboUI *pCombo = (CComboUI*)ICncCommonOp::FindControl(m_pm, _T("ComboDCamSel"));
        if (pCombo)
        {
            pCombo->SelectItem(m_byDCamSelIndex);
        }
    }
    return NO_ERROR;
}

void  CCenterCtrlLogic::EnableCam( bool bIsEnable )
{
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("BtnSnapShot"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("BtnAutoFocus"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("BtnAutoWB"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("BtnSavePrepose"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("BtnCamPlus"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("BtnCamMinus"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("BtnCamPlus"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("BtnCamMinus"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("preposeA3"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("preposeA4"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("preposeA5"));
}

bool CCenterCtrlLogic::OnDCamPowerInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	ICncCommonOp::EnableControl(true, m_pm, _T("CheckCam"));
	BOOL bOk = (BOOL)wParam;    
	u8 byIndex = (u8)lParam;
	//Ind回false时不会再有Nty消息，恢复按钮状态
	if ( !bOk )
	{
        TCentreDCamCfg tDCamCfg;
        ComInterface->GetDCamState(tDCamCfg, byIndex);
        if ( tDCamCfg.emDCamPowerMode == emDCamPowerOn )
		{
			EnableCam(false);
			ShowPopMsg(_T("开启文档摄像机失败"));
		}
		else
		{
			EnableCam(true);
			ShowPopMsg(_T("关闭文档摄像机失败"));
		}

		//设置check状态
		CCheckBoxUI *pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm, _T("CheckCam"));
		if (pCheckBox)
		{
			pCheckBox->SetCheck(tDCamCfg.emDCamPowerMode != emDCamPowerOn);
		}
	}

	return NO_ERROR;
}

bool CCenterCtrlLogic::OnDocSnapShotInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	if (m_emRecallNum == emDCamRecallInvalid)
	{
		showMessageBox(_T("请先选择预置位"));
	}

	BOOL bOk = (BOOL)wParam;    
	u8 wCamID = m_emRecallNum/*lParam*/;
	if ( !bOk )
	{
		ShowPopMsg(_T("文档摄像机快照生成失败"));
	}
	else
	{
		if (m_strLogFolderPath.IsEmpty())
		{
			TCHAR chExeFullPath[MAX_PATH] = _T(""); 
			GetModuleFileName(NULL,chExeFullPath,MAX_PATH);//

			CString strCfgPath = chExeFullPath;
			int dwIndex = strCfgPath.ReverseFind( _T('\\') );    
			strCfgPath.Delete( dwIndex, strCfgPath.GetLength() - dwIndex );
			dwIndex = strCfgPath.ReverseFind( _T('\\') );
			dwIndex++;
			strCfgPath.Delete( dwIndex, strCfgPath.GetLength() - dwIndex );
			CString strCfgFile = strCfgPath + CFG_FILE;

			TCHAR szReadPath[MAX_PATH] = { 0 };	

			GetPrivateProfileString( _T("snapshot"), CFG_PATH, TEXT("快照/"), szReadPath, sizeof(szReadPath), strCfgFile );

			m_strLogFolderPath = szReadPath;

			if ( m_strLogFolderPath == _T("快照/") )
			{
				PrtMsg( "\n[CSaveLog::GetLogPathFromIni] can't get the path of the log folder \n");
				m_strLogFolderPath = GetModuleFullPath() + m_strLogFolderPath;
				//return;
			}
			else
			{
				m_strLogFolderPath = m_strLogFolderPath + _T("/");
			}
		}

		CString strFolder (m_strLogFolderPath);
		ComInterface->CreateDir(strFolder);
		
		CString strDocSnapName = _T("");
		strDocSnapName.Format(_T("document_%d.jpg"),wCamID);
		if ( !DownloadCore( _T(TP_SNAPSHOT_PATH), (String)strFolder, (String)strDocSnapName, FALSE) )
		{			
			ShowPopMsg(_T("文档摄像机快照下载失败"));
		}
	}

	return NO_ERROR;
}

BOOL CCenterCtrlLogic::DownloadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bAutoEnd /*= TRUE */ )
{
	CString strIpAddr;

	m_cFtp.SethWnd( m_pm->GetPaintWindow() );
	m_cFtp.RegisterMsgHandle( WM_CNC_DOCSNAPSHOTROGRESS );

	u32 dwIp;
	ComInterface->GetLoginIp(dwIp);		
	struct in_addr addrIPAddr;
	addrIPAddr.S_un.S_addr = htonl(dwIp);
	strIpAddr = CA2T(inet_ntoa(addrIPAddr));

	TTPFtpInfo tTPFtpInfo;
	ComInterface->GetCnFtpInfo(tTPFtpInfo);
	if (tTPFtpInfo.bOpen == FALSE)
	{
		ShowPopMsg(_T("FTP上传服务器未开启!"));
		return FALSE;
	}
	BOOL32 bRet = m_cFtp.SetServerParam( strIpAddr, CA2W(tTPFtpInfo.achUserName)/*_T("admin")*/, CA2W(tTPFtpInfo.achPassword)/* _T("kedacomTP")*/ );
	if ( !bRet )
	{
		ShowPopMsg(_T("设置FTP上传服务器失败!"));
		return FALSE;
	}

	String strRemoteFilePath = strRemotePath;
	strRemoteFilePath += strCheckFileName;
	m_cFtp.SetAutoEndFtpFile(bAutoEnd);

	CString strLocalPath(strLocalFile.c_str());	
	
	SYSTEMTIME systime;
	GetLocalTime( &systime );

	CString strDate = _T("");
	CString strNum = _T("");

	strDate.Format(_T("%d"),systime.wYear);
	if (systime.wMonth < 10 )
	{
		strNum.Format(_T("0%d"),systime.wMonth);
	}
	else
	{
		strNum.Format(_T("%d"),systime.wMonth);
	}
	strDate = strDate+strNum;
	if (systime.wDay < 10 )
	{
		strNum.Format(_T("0%d"),systime.wDay);
	}
	else
	{
		strNum.Format(_T("%d"),systime.wDay);
	}
	strDate = strDate+strNum;
	if (systime.wHour <10)
	{
		strNum.Format(_T("_0%d"),systime.wHour);
	}
	else
	{
		strNum.Format(_T("_%d"),systime.wHour);
	}
	strDate = strDate+strNum;
	if ( systime.wMinute <10)
	{
		strNum.Format(_T("0%d"),systime.wMinute);
	}
	else 
	{
		strNum.Format(_T("%d"),systime.wMinute);
	}
	strDate = strDate+strNum;
	CString strFile = _T("");
// 	CString strName(strCheckFileName.c_str());
// 	strName = strName.Left(strName.GetLength() - 4);
	strFile.Format(_T("快照_%s.jpg"),strDate);
	strLocalPath = strLocalFile.c_str() + strFile;

	int i = 0;
	while (PathFileExists(strLocalPath))//自动重命名
	{
		i++; 
		strFile.Format(_T("快照_%s_%d.jpg"),strDate, i);
		strLocalPath = strLocalFile.c_str() + strFile;
	}
	
	if ( !m_cFtp.BeginDownload(  strRemoteFilePath.c_str(), strLocalPath, FTP_TRANSFER_TYPE_BINARY, FTP_AGENT ,FALSE) )
	{
		ShowPopMsg(_T("文档摄像机快照文件下载失败，参数错误!"));
		m_cFtp.SetAutoEndFtpFile(TRUE);
		return FALSE;
	}
	return TRUE;
}

bool CCenterCtrlLogic::OnDownloadProgress( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	EmFtpStatus emFileFtpStatus = static_cast<EmFtpStatus>(wParam);

	switch( emFileFtpStatus )
	{
	case emFtpBegin:
		{
			//PrtMsg( 0, emEventTypeCmsWindow, _T("%s已经进入传输状态！"), m_vecDownloadPicName.at(0).c_str() );
		}
		break;
	case emFtpTransfer:
		{
		}
		break;
	case emFtpEnd:
		{
			DWORD dwSuccess = static_cast<DWORD>(lParam);     //FTP接口0为成功  默认失败
			CString strLocalName(m_cFtp.GetCurrentLocalFile());
			strLocalName = strLocalName.Right( strLocalName.GetLength() - strLocalName.ReverseFind( '\/' ) - 1);
			m_cFtp.EndFtpFile();	
			if ( 0 != dwSuccess )
			{
				LPTSTR pszMsg = NULL;
				m_cFtp.FormatFtpError( dwSuccess, &pszMsg );
				OspPrintf( TRUE, FALSE, "文档摄像机快照下载出错，错误原因：%s", pszMsg );

				CString strMsg=_T("");
				strMsg.Format(_T("文档摄像机快照下载出错"));
				ShowPopMsg(strMsg);

				LocalFree( pszMsg );
			}	
			else
			{
				OspPrintf( TRUE, FALSE, "文档摄像机快照下载成功");
				CString str = _T("");
				str.Format(_T("快照“%s”保存成功"),strLocalName);
				ShowPopMsg(str);
			}
		}
		break;
	default:
		{
		}
		break;
	}	
	return true;
}

bool CCenterCtrlLogic::OnMonitorStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	return HideMonitorSwitch();
}

bool CCenterCtrlLogic::OnDocCamTypeInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	EmDCamProType emCamModelType = *(EmDCamProType*)wParam;
	BOOL bSuccess = *(BOOL*)lParam;

	if ( bSuccess == TRUE )
	{
		ChangeInterface(emCamModelType);
	}

	return true;
}

void CCenterCtrlLogic::ChangeInterface( EmDCamProType emCamModelType )
{
	if ( emCamModelType == emVISCAPro )
	{
		ICncCommonOp::ShowControl(true,m_pm,_T("CheckCam"));
		ICncCommonOp::ShowControl(true,m_pm,_T("BtnAutoWB"));
		ICncCommonOp::ShowControl(true,m_pm,_T("CamSwitchLabel"));
	//	ICncCommonOp::ShowControl(true,m_pm,_T("BtnAutoFocus"));
	}
	else if ( emCamModelType == emPELCOPro )
	{
		ICncCommonOp::ShowControl(false,m_pm,_T("CheckCam"));
		ICncCommonOp::ShowControl(false,m_pm,_T("BtnAutoWB"));
		ICncCommonOp::ShowControl(false,m_pm,_T("CamSwitchLabel"));
	//	ICncCommonOp::ShowControl(false,m_pm,_T("BtnAutoFocus"));
	}
}

bool CCenterCtrlLogic::OnComboDCamSel(TNotifyUI& msg)
{
    u8 byIndex = msg.wParam;
    if (m_byDCamSelIndex != byIndex)
    {
        ComInterface->SetDCamSelectIndex(byIndex);
    }
    return true;
}

bool CCenterCtrlLogic::OnOppreposeA3( TNotifyUI& msg )
{
	if (m_emRecallNum != emDCamRecallOne)
	{
		ComInterface->SetDCamRecall( emDCamRecallOne );
	}
	
	return true;
}

bool CCenterCtrlLogic::OnOppreposeA4( TNotifyUI& msg )
{
	if (m_emRecallNum != emDCamRecallTwo)
	{
		ComInterface->SetDCamRecall( emDCamRecallTwo );
	}

	return true;
}

bool CCenterCtrlLogic::OnOppreposeA5( TNotifyUI& msg )
{
	if (m_emRecallNum != emDCamRecallThree)
	{
		ComInterface->SetDCamRecall( emDCamRecallThree );
	}

	return true;
}

bool CCenterCtrlLogic::OnBtnSnapShot( TNotifyUI& msg )
{
	if (m_emRecallNum == emDCamRecallInvalid)
	{
		showMessageBox(_T("请先设置文档摄像机预置位"));
		return NO_ERROR;
	}
    //判断ftp是否开启，未开启先开启
    TTPFtpInfo tTPFtpInfo;
    ComInterface->GetCnFtpInfo(tTPFtpInfo);
    if (tTPFtpInfo.bOpen == FALSE)
    {
        m_bIsShotcupOpenFtp = true;
        tTPFtpInfo.bOpen = TRUE;
        ComInterface->SetCnFtpInfo(tTPFtpInfo);
    }
    //快照
	ComInterface->SetDocSnapShot();
	return NO_ERROR;
}

bool CCenterCtrlLogic::OnBtnAutoFocus( TNotifyUI& msg )
{
	ComInterface->SetDCamAFMode( emDCamAFOn );
	return true;
}

bool CCenterCtrlLogic::OnBtnAutoWB( TNotifyUI& msg )
{
	ComInterface->SetDCamWBMode( emDcamWBAuto );
	return true; 
}

bool CCenterCtrlLogic::OnCheckCam( TNotifyUI& msg )
{
	CCheckBoxUI *pCheckBox = (CCheckBoxUI*)msg.pSender;

	bool bCheck = false;
	if (pCheckBox && pCheckBox->GetCheck())
	{
		bCheck = true;
	}

	TCentreDCamCfg tDCamCfg;
	ComInterface->GetDCamState(tDCamCfg, m_byDCamSelIndex);

	if (tDCamCfg.emDCamPowerMode == emDCamPowerOn && bCheck) 
	{
		return true;
	}

	if (tDCamCfg.emDCamPowerMode != emDCamPowerOn && !bCheck)
	{
		return true;
	}

	EnableCam(bCheck);

	ICncCommonOp::EnableControl(false, m_pm, _T("CheckCam"));

	if ( bCheck )
	{
		ComInterface->SetDCamPower( emDCamPowerOn );
	}
	else
	{
		ComInterface->SetDCamPower( emDCamPowerOff );
	}

	return true;
}

bool CCenterCtrlLogic::OnBtnCamPlus( TNotifyUI& msg )
{
	ComInterface->SetDCamZoom( emDCamZoomTele );
	SetZoomEnable(false);
	return true;
}

bool CCenterCtrlLogic::OnBtnCamMinus( TNotifyUI& msg )
{
	ComInterface->SetDCamZoom( emDCamZoomWide );
	SetZoomEnable(false);
	return true;
}

bool CCenterCtrlLogic::OnBtnCamPlusDown( TNotifyUI& msg )
{
	ComInterface->SetDCamZoom( emDCamZoomTele, emCnStart );
	return true;
}

bool CCenterCtrlLogic::OnBtnCamMinusDown( TNotifyUI& msg )
{
	ComInterface->SetDCamZoom( emDCamZoomWide, emCnStart );
	return true;
}

bool CCenterCtrlLogic::OnBtnSavePrepose( TNotifyUI& msg )
{
	ComInterface->SetDCamPreset( m_emRecallNum );
	return true;  
}


//////////////////////////////////////////////////////////////////////////////////
//////        窗帘控制                                    ///////////////////////
/////////////////////////////////////////////////////////////////////////////////
bool CCenterCtrlLogic::OnCurtainStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TCentreCurInfo tCentreCurInfo;
	ComInterface->GetCentreCurInfor( tCentreCurInfo );
	m_nCurNum = tCentreCurInfo.byCurNum;
	if ( !(BOOL)tCentreCurInfo.bCurOpen )//不可用时 隐藏此tab 2015-9-7
	{
		ICncCommonOp::ShowControl(false,m_pm,_T("Curtain"));
		//选中第一项
		COptionUI *pOpCurt = (COptionUI*)ICncCommonOp::FindControl(m_pm,_T("Curtain"));
		if (pOpCurt && pOpCurt->IsSelected())
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
		ICncCommonOp::ShowControl(true,m_pm,_T("Curtain"));
	}

	for( u8 Index = 0; Index < MAX_CURTAIN_NUM; Index++ )
	{
		CString strOp;
		strOp.Format( _T("curtain%d"), Index+1 );
		CString strCurName;
		strCurName.Format( _T("lbcurtain%d"), Index+1 );
		COptionUI *pOp = (COptionUI*)ICncCommonOp::FindControl(m_pm,strOp);
		if (pOp)
		{
			pOp->Selected(false);
		}
		if ( Index < m_nCurNum)
		{
			CString strName(tCentreCurInfo.tCenCurName[Index].achCurName);			
			ICncCommonOp::SetControlText(strName, m_pm, strCurName);
			ICncCommonOp::EnableControl(true, m_pm, strOp);//数目内的按是否开启显示
		}
		else
		{
			ICncCommonOp::SetControlText(_T("无"), m_pm, strCurName);
			ICncCommonOp::EnableControl(false, m_pm, strOp);//少于数目的禁用
		}

	}

	memset( m_achIsCurCheck, 0, 6*sizeof(BOOL) );
	COptionUI* popAll = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("opAll"));
	if (popAll)
	{
		popAll->Selected(false);
		popAll->SetEnabled(tCentreCurInfo.bCurOpen);
	} 
	
	return true;	
}

bool CCenterCtrlLogic::OnBtnCuitainUp( TNotifyUI& msg )
{
	ComInterface->SetCurtainState( m_achIsCurCheck, emCurUp );
	return true;
}

bool CCenterCtrlLogic::OnBtnCuitainDown( TNotifyUI& msg )
{
	ComInterface->SetCurtainState( m_achIsCurCheck, emCurDown );
	return true;
}

bool CCenterCtrlLogic::OnBtnCuitainStop( TNotifyUI& msg )
{
	ComInterface->SetCurtainState( m_achIsCurCheck, emCurStop );	
	return true;
}

bool CCenterCtrlLogic::OnopAll( TNotifyUI& msg )
{
	COptionUI* popAll = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("opAll"));
	if (!popAll)
	{
		return false;
	}

	bool bSel = popAll->IsSelected();
	CString strCurnName = _T("");

	for (int i=0; i<m_nCurNum; i++)
	{
		strCurnName.Format(_T("curtain%d"),i+1);
		COptionUI* pOpcurtain1 = (COptionUI*)ICncCommonOp::FindControl( m_pm, strCurnName);
		if (pOpcurtain1 && bSel != pOpcurtain1->IsSelected())
		{
			pOpcurtain1->SetCheckNoMsg(bSel);
		} 
		m_achIsCurCheck[i] = bSel;
	}

	return true;
}

bool CCenterCtrlLogic::Oncurtain1( TNotifyUI& msg )
{
	COptionUI* pOpcurtain1 = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("curtain1"));
	bool bSel = FALSE;
	if (pOpcurtain1 && pOpcurtain1->IsSelected())
	{
		bSel = TRUE;
	} 
	m_achIsCurCheck[0] = bSel;
	checkCurSelAll();
	return true;
}

bool CCenterCtrlLogic::Oncurtain2( TNotifyUI& msg )
{
	COptionUI* pOpcurtain2 = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("curtain2"));
	bool bSel = FALSE;
	if (pOpcurtain2 && pOpcurtain2->IsSelected())
	{
		bSel = TRUE;
	} 
	m_achIsCurCheck[1] = bSel;
	checkCurSelAll();
	return true;
}

bool CCenterCtrlLogic::Oncurtain3( TNotifyUI& msg )
{
	COptionUI* pOpcurtain3 = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("curtain3"));
	bool bSel = FALSE;
	if (pOpcurtain3 && pOpcurtain3->IsSelected())
	{
		bSel = TRUE;
	} 
	m_achIsCurCheck[2] = bSel;
	checkCurSelAll();
	return true;
}

bool CCenterCtrlLogic::Oncurtain4( TNotifyUI& msg )
{
	COptionUI* pOpcurtain4 = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("curtain4"));
	bool bSel = FALSE;
	if (pOpcurtain4 && pOpcurtain4->IsSelected())
	{
		bSel = TRUE;
	} 
	m_achIsCurCheck[3] = bSel;
	checkCurSelAll();
	return true;
}

bool CCenterCtrlLogic::Oncurtain5( TNotifyUI& msg )
{
	COptionUI* pOpcurtain5 = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("curtain5"));
	bool bSel = FALSE;
	if (pOpcurtain5 && pOpcurtain5->IsSelected())
	{
		bSel = TRUE;
	} 
	m_achIsCurCheck[4] = bSel;
	checkCurSelAll();
	return true;
}

bool CCenterCtrlLogic::Oncurtain6( TNotifyUI& msg )
{
	COptionUI* pOpcurtain6 = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("curtain6"));
	bool bSel = FALSE;
	if (pOpcurtain6 && pOpcurtain6->IsSelected())
	{
		bSel = TRUE;
	} 
	m_achIsCurCheck[5] = bSel;

	checkCurSelAll();
	return true;
}

void CCenterCtrlLogic::checkCurSelAll()
{
	int dwSelCount = 0;
	for(int i = 0; i< m_nCurNum; i++)
	{
		if (m_achIsCurCheck[i])
		{
			dwSelCount++;
		}
	}

	bool bCanCtrl = false;
	if (dwSelCount>0)
	{
		bCanCtrl = true;
	}

	SetIsCurCanCtrl(bCanCtrl);

	COptionUI* pOpAll = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("opAll"));
	if (!pOpAll)
	{
		return;
	}

	if (dwSelCount == m_nCurNum)
	{
		if (!pOpAll->IsSelected())
		{
			pOpAll->SetCheckNoMsg(true);
		} 
	}
	else
	{
		if (pOpAll->IsSelected())
		{
			pOpAll->SetCheckNoMsg(false);
		} 
	}
}

void CCenterCtrlLogic::SetIsCurCanCtrl(bool bCurCanCtrl)
{
	ICncCommonOp::EnableControl(bCurCanCtrl,m_pm,_T("BtnCuitainStop"));
	ICncCommonOp::EnableControl(bCurCanCtrl,m_pm,_T("BtnCuitainUp"));
	ICncCommonOp::EnableControl(bCurCanCtrl,m_pm,_T("BtnCuitainDown"));
}

bool CCenterCtrlLogic::OnDocCamPrePosSelInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL bOk = (BOOL)wParam;    
	EmDCamRecallNum emNum = (EmDCamRecallNum)lParam;

	if (!bOk)//失败提示 状态还原
	{
		CString str = _T("");
		CString strOpt = _T("");
		if ( emNum == emDCamRecallOne )
		{
			str = _T("文档摄像机预置位A3设置失败");
			strOpt = _T("preposeA3");
		}
		else if ( emNum == emDCamRecallTwo )
		{
			str = _T("文档摄像机预置位A4设置失败");
			strOpt = _T("preposeA4");
		}
		else if ( emNum == emDCamRecallThree )
		{
			str = _T("文档摄像机预置位A5设置失败");
			strOpt = _T("preposeA5");
		}

		ShowPopMsg(str);

		if ( m_emRecallNum == emDCamRecallOne )
		{
			ICncCommonOp::OptionSelect( true, m_pm, _T("preposeA3") );
		}
		else if ( m_emRecallNum == emDCamRecallTwo )
		{
			ICncCommonOp::OptionSelect( true, m_pm, _T("preposeA4") );
		}
		else if ( m_emRecallNum == emDCamRecallThree )
		{
			ICncCommonOp::OptionSelect( true, m_pm, _T("preposeA5") );
		}
		else
		{
			ICncCommonOp::OptionSelect( false, m_pm, strOpt );
		}
	}

	return true;
}

bool CCenterCtrlLogic::OnDCamZoomInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	SetZoomEnable(true);
	return true;
}

void CCenterCtrlLogic::SetZoomEnable( bool bIsEnabel )
{
	ICncCommonOp::EnableControl(bIsEnabel, m_pm, _T("BtnCamPlus")) ;
	ICncCommonOp::EnableControl(bIsEnabel, m_pm, _T("BtnCamMinus")) ;
}

bool CCenterCtrlLogic::OnSetCnFtpRsp(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    TTPFtpInfo tTPFtpInfo;
    ComInterface->GetCnFtpInfo(tTPFtpInfo);
    if (tTPFtpInfo.bOpen == FALSE && m_bIsShotcupOpenFtp)
    {
        ShowPopMsg(_T("FTP上传服务器开启失败!"));
        return false;
    }
    if (m_bIsShotcupOpenFtp)
    {
        m_bIsShotcupOpenFtp = false;
    }
    return true;
}