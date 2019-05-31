#include "StdAfx.h"
#include "cameracontrollogic.h"
#include "mainframelogic.h"

template<> CCameraControlLogic* Singleton<CCameraControlLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CCameraControlLogic, CNotifyUIImpl)

	MSG_CLICK(_T("BtnCramerBack"), OnBtnCramerBack)

	MSG_CLICK(_T("btnCamUp"), OnBtnCamUp)
	MSG_CLICK(_T("btnCamRight"), OnCamRight)
	MSG_CLICK(_T("btnCamLeft"), OnBtnCamLeft)
	MSG_CLICK(_T("btnCamDown"), OnBtnCamDown)
	MSG_CLICK(_T("btnViewPlus"), OnBtnViewPlus)
	MSG_CLICK(_T("btnViewMinus"), OnBtnViewMinus)
	MSG_CLICK(_T("btnFocusPlus"), OnBtnFocusPlus)
	MSG_CLICK(_T("btnFocusAuto"), OnBtnFocusAuto)
	MSG_CLICK(_T("btnFocusMinus"), OnBtnFocusMinus)
	MSG_CLICK(_T("btnBrightPlus"), OnBtnBrightPlus)
	MSG_CLICK(_T("btnBrightMinus"), OnBtnBrightMinus)

	MSG_BUTTONDOWN(_T("btnCamUp"), OnBtnCamUpDown)
	MSG_BUTTONDOWN(_T("btnCamRight"), OnCamRightDown)
	MSG_BUTTONDOWN(_T("btnCamLeft"), OnBtnCamLeftDown)
	MSG_BUTTONDOWN(_T("btnCamDown"), OnBtnCamDownDown)
	MSG_BUTTONDOWN(_T("btnFocusPlus"), OnBtnFocusPlusDown)
	MSG_BUTTONDOWN(_T("btnFocusMinus"), OnBtnFocusMinusDown)
	MSG_BUTTONDOWN(_T("btnBrightPlus"), OnBtnBrightPlusDown)
	MSG_BUTTONDOWN(_T("btnBrightMinus"), OnBtnBrightMinusDown)
	MSG_BUTTONDOWN(_T("btnViewPlus"), OnBtnViewPlusDown)
	MSG_BUTTONDOWN(_T("btnViewMinus"), OnBtnViewMinusDown)

	MSG_ITEMSELECTD(_T("ComboCamSel"), OnComboCamSel)

	USER_MSG( UI_CNS_323VEDIOSOR_NOTIFY, On323VedioSourceNty )
	USER_MSG( UI_DISCONNECTED_CLEARDATA, OnDisconnect )

APP_END_MSG_MAP()

//远摇控制时间间隔
#define TIME_FECCCONTROL 400

//定时器消息循环发送调控摄像机信息
static BOOL g_bIsFeccCamUp       = FALSE;   //是否正在向上调控
static BOOL g_bIsFeccCamDown     = FALSE;   //是否正在向下调控
static BOOL g_bIsFeccCamRight    = FALSE;   //是否正在向左调控
static BOOL g_bIsFeccCamLeft     = FALSE;   //是否正在向右调控
static BOOL g_bIsFeccFocusPlus   = FALSE;   //是否正在远焦调控
static BOOL g_bIsFeccFocusMinus  = FALSE;   //是否正在近焦调控
static BOOL g_bIsFeccBrightPlus  = FALSE;   //是否正在强光调控
static BOOL g_bIsFeccBrightMinus = FALSE;   //是否正在弱光调控
static BOOL g_bIsFeccViewPlus    = FALSE;   //是否正在视宽调控
static BOOL g_bIsFeccViewMinus   = FALSE;   //是否正在视窄调控

static UINT g_nTmFeccCamUp	     = 0;       //开始向上调控
static UINT g_nTmFeccCamDown     = 0;       //开始向下调控
static UINT g_nTmFeccCamRight    = 0;       //开始向右调控
static UINT g_nTmFeccCamLeft     = 0;       //开始向左调控
static UINT g_nTmFeccFocusPlus   = 0;       //开始聚焦推远
static UINT g_nTmFeccFocusMinus  = 0;       //开始聚焦拉近
static UINT g_nTmFeccBrightPlus  = 0;       //开始背光加强
static UINT g_nTmFeccBrightMinus = 0;       //开始背光减弱
static UINT g_nTmFeccViewPlus    = 0;       //开始视野加宽
static UINT g_nTmFeccViewMinus   = 0;       //开始视野减小


VOID  CALLBACK  CWifiTimerFun(  HWND   hwnd,   UINT   uMsg, UINT_PTR  idEvent, DWORD   dwTime  )
{  
	//如果远摇会场ID无效,则停止远摇
	TConfEpID tFeccConfEpID;
	ComInterface->GetFeccConfEpInfo(tFeccConfEpID);
	if (tFeccConfEpID.m_wEpID == TP_INVALID_INDEX)
	{
		KillTimer( NULL, idEvent );
	}

	if ( idEvent == g_nTmFeccCamUp )
	{
		if (g_bIsFeccCamUp)
		{
			ComInterface->SetFeccCamPT( emUP, emCnStart );
		}
		else
		{
			ComInterface->SetFeccCamPT( emUP, emCnStop );
			KillTimer( NULL, g_nTmFeccCamUp );
			g_nTmFeccCamUp = 0;
		}
		
	}
	else if ( idEvent == g_nTmFeccCamRight )
	{
		if (g_bIsFeccCamRight)
		{
			ComInterface->SetFeccCamPT( emRight, emCnStart );
		}
		else
		{
			ComInterface->SetFeccCamPT( emRight, emCnStop );
			KillTimer( NULL, g_nTmFeccCamRight );
			g_nTmFeccCamRight = 0;
		}
	}
	else if ( idEvent == g_nTmFeccCamLeft )
	{
		if (g_bIsFeccCamLeft)
		{
			ComInterface->SetFeccCamPT( emLeft, emCnStart );
		}
		else
		{
			ComInterface->SetFeccCamPT( emLeft, emCnStop );
			KillTimer( NULL, g_nTmFeccCamLeft );
			g_nTmFeccCamLeft = 0;
		}
	}
	else if ( idEvent == g_nTmFeccCamDown )
	{
		if (g_bIsFeccCamDown)
		{
			ComInterface->SetFeccCamPT( emDown, emCnStart );
		}
		else
		{
			ComInterface->SetFeccCamPT( emDown, emCnStop );
			KillTimer( NULL, g_nTmFeccCamDown );
			g_nTmFeccCamDown = 0;
		}
	}
	else if ( idEvent == g_nTmFeccFocusPlus )
	{
		if (g_bIsFeccFocusPlus)
		{
			ComInterface->SetFeccCamFocus( emNear, emCnStart );
		}
		else
		{
			ComInterface->SetFeccCamFocus( emNear, emCnStop );
			KillTimer( NULL, g_nTmFeccFocusPlus );
			g_nTmFeccFocusPlus = 0;
		}
	}
	else if ( idEvent == g_nTmFeccFocusMinus )
	{
		if (g_bIsFeccFocusMinus)
		{
			ComInterface->SetFeccCamFocus( emFar, emCnStart );
		}
		else
		{
			ComInterface->SetFeccCamFocus( emFar, emCnStop );
			KillTimer( NULL, g_nTmFeccFocusMinus );
			g_nTmFeccFocusMinus = 0;
		}
	}
	else if ( idEvent == g_nTmFeccViewPlus )
	{
		if (g_bIsFeccViewPlus)
		{
			ComInterface->SetFeccCamView( emTele, emCnStart );
		}
		else
		{
			ComInterface->SetFeccCamView( emTele, emCnStop );
			KillTimer( NULL, g_nTmFeccViewPlus );
			g_nTmFeccViewPlus = 0;
		}
	}
	else if ( idEvent == g_nTmFeccViewMinus )
	{
		if (g_bIsFeccViewMinus)
		{
			ComInterface->SetFeccCamView( emWide, emCnStart );
		}
		else
		{
			ComInterface->SetFeccCamView( emWide, emCnStop );
			KillTimer( NULL, g_nTmFeccViewMinus );
			g_nTmFeccViewMinus = 0;
		}
	}
	else if ( idEvent == g_nTmFeccBrightPlus )
	{
		if (g_bIsFeccBrightPlus)
		{
			ComInterface->SetFeccCamBright( emBrightUp, emCnStart );
		}
		else
		{
			ComInterface->SetFeccCamBright( emBrightUp, emCnStop );
			KillTimer( NULL, g_nTmFeccBrightPlus );
			g_nTmFeccBrightPlus = 0;
		}
	}
	else if ( idEvent == g_nTmFeccBrightMinus )
	{
		if (g_bIsFeccBrightMinus)
		{
			ComInterface->SetFeccCamBright( emBrightDown, emCnStart );
		}
		else
		{
			ComInterface->SetFeccCamBright( emBrightDown, emCnStop );
			KillTimer( NULL, g_nTmFeccBrightMinus );
			g_nTmFeccBrightMinus = 0;
		}
	}
}

CCameraControlLogic::CCameraControlLogic(void)
{
}


CCameraControlLogic::~CCameraControlLogic(void)
{
}

void CCameraControlLogic::EnableFeccCtrl( bool bIsEnable )
{

	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("ComboCamSel"));

	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnCamUp"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnCamLeft"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnCamRight"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnCamDown"));

	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnViewPlus"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnViewMinus"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnFocusPlus"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnFocusAuto"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnFocusMinus"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnBrightPlus"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("btnBrightMinus"));

}

bool CCameraControlLogic::OnBtnCramerBack( TNotifyUI& msg )
{
	//清空远摇会议数据
	TConfEpID tFeccConfEpID;
	tFeccConfEpID.Clear();
	ComInterface->SetFeccConfEpInfo(tFeccConfEpID);
	ICncCommonOp::ShowControl( false, m_pm, _T("ConfroomCramerLayout") );
	return false;
}

bool CCameraControlLogic::OnComboCamSel( TNotifyUI& msg )
{
	CComboUI* pcombo = (CComboUI*)msg.pSender;
	CListLabelElementUI *pListLabelElement = (CListLabelElementUI*)pcombo->GetItemAt(pcombo->GetCurSel());
	u8 nSourceID = pListLabelElement->GetTag();
	if (m_tVidFeccInfo.m_byVidno != nSourceID)
	{
		ComInterface->ChangeFeccSource(nSourceID);
	}
	return true;
}

bool CCameraControlLogic::OnBtnCamUp( TNotifyUI& msg )
{
	g_bIsFeccCamUp = FALSE;
	return true;
}
bool CCameraControlLogic::OnBtnCamUpDown( TNotifyUI& msg )
{
	if (g_nTmFeccCamUp != 0)
	{
		return false;
	}
	ComInterface->SetFeccCamPT( emUP, emCnStart );
	g_bIsFeccCamUp = TRUE;
	g_nTmFeccCamUp = SetTimer( NULL, 0, TIME_FECCCONTROL, CWifiTimerFun );
	return true;
}

bool CCameraControlLogic::OnCamRight( TNotifyUI& msg )
{
	g_bIsFeccCamRight = FALSE;
	return true;
}
bool CCameraControlLogic::OnCamRightDown( TNotifyUI& msg )
{
	if (g_nTmFeccCamRight != 0)
	{
		return false;
	}
	ComInterface->SetFeccCamPT( emRight, emCnStart );
	g_bIsFeccCamRight = TRUE;
	g_nTmFeccCamRight = SetTimer( NULL, 0, TIME_FECCCONTROL, CWifiTimerFun );
	return true;
}

bool CCameraControlLogic::OnBtnCamLeft( TNotifyUI& msg )
{
	g_bIsFeccCamLeft = FALSE;
	return true;
}
bool CCameraControlLogic::OnBtnCamLeftDown( TNotifyUI& msg )
{
	if (g_nTmFeccCamLeft != 0)
	{
		return false;
	}
	ComInterface->SetFeccCamPT( emLeft, emCnStart );
	g_bIsFeccCamLeft = TRUE;
	g_nTmFeccCamLeft = SetTimer( NULL, 0, TIME_FECCCONTROL, CWifiTimerFun );
	return true;
}

bool CCameraControlLogic::OnBtnCamDown( TNotifyUI& msg )
{
	g_bIsFeccCamDown = FALSE;
	return true;
}
bool CCameraControlLogic::OnBtnCamDownDown( TNotifyUI& msg )
{
	if (g_nTmFeccCamDown != 0)
	{
		return false;
	}
	ComInterface->SetFeccCamPT( emDown, emCnStart );
	g_bIsFeccCamDown = TRUE;
	g_nTmFeccCamDown = SetTimer( NULL, 0, TIME_FECCCONTROL, CWifiTimerFun );
	return true;
}

bool CCameraControlLogic::OnBtnViewPlus( TNotifyUI& msg )
{
	g_bIsFeccViewPlus = FALSE;
	return true;
}
bool CCameraControlLogic::OnBtnViewPlusDown( TNotifyUI& msg )
{
	if (g_nTmFeccViewPlus != 0)
	{
		return false;
	}
	ComInterface->SetFeccCamView( emTele, emCnStart );
	g_bIsFeccViewPlus = TRUE;
	g_nTmFeccViewPlus = SetTimer( NULL, 0, TIME_FECCCONTROL, CWifiTimerFun );
	return true;
}

bool CCameraControlLogic::OnBtnViewMinus( TNotifyUI& msg )
{
	g_bIsFeccViewMinus = FALSE;
	return true;
}
bool CCameraControlLogic::OnBtnViewMinusDown( TNotifyUI& msg )
{
	if (g_nTmFeccViewMinus != 0)
	{
		return false;
	}
	ComInterface->SetFeccCamView( emWide, emCnStart );
	g_bIsFeccViewMinus = TRUE;
	g_nTmFeccViewMinus = SetTimer( NULL, 0, TIME_FECCCONTROL, CWifiTimerFun );
	return true;
}

bool CCameraControlLogic::OnBtnFocusPlus( TNotifyUI& msg )
{
	g_bIsFeccFocusPlus = FALSE;
	return true;
}
bool CCameraControlLogic::OnBtnFocusPlusDown( TNotifyUI& msg )
{
	if (g_nTmFeccFocusPlus != 0)
	{
		return false;
	}
	ComInterface->SetFeccCamFocus( emNear, emCnStart );
	g_bIsFeccFocusPlus = TRUE;
	g_nTmFeccFocusPlus = SetTimer( NULL, 0, TIME_FECCCONTROL, CWifiTimerFun );
	return true;
}

bool CCameraControlLogic::OnBtnFocusAuto( TNotifyUI& msg )
{
	ComInterface->SetFeccCamAotoFocus();
	return true;
}

bool CCameraControlLogic::OnBtnFocusMinus( TNotifyUI& msg )
{
	g_bIsFeccFocusMinus = FALSE;
	return true;
}
bool CCameraControlLogic::OnBtnFocusMinusDown( TNotifyUI& msg )
{
	if (g_nTmFeccFocusMinus != 0)
	{
		return false;
	}
	ComInterface->SetFeccCamFocus( emFar, emCnStart );
	g_bIsFeccFocusMinus = TRUE;
	g_nTmFeccFocusMinus = SetTimer( NULL, 0, TIME_FECCCONTROL, CWifiTimerFun );
	return true;
}

bool CCameraControlLogic::OnBtnBrightPlus( TNotifyUI& msg )
{
	g_bIsFeccBrightPlus = FALSE;
	return true;
}
bool CCameraControlLogic::OnBtnBrightPlusDown( TNotifyUI& msg )
{
	if (g_nTmFeccBrightPlus != 0)
	{
		return false;
	}
	ComInterface->SetFeccCamBright( emBrightUp, emCnStart );
	g_bIsFeccBrightPlus = TRUE;
	g_nTmFeccBrightPlus = SetTimer( NULL, 0, TIME_FECCCONTROL, CWifiTimerFun );
	return true;
}

bool CCameraControlLogic::OnBtnBrightMinus( TNotifyUI& msg )
{
	g_bIsFeccBrightMinus = FALSE;
	return true;
}
bool CCameraControlLogic::OnBtnBrightMinusDown( TNotifyUI& msg )
{
	if (g_nTmFeccBrightMinus != 0)
	{
		return false;
	}
	ComInterface->SetFeccCamBright( emBrightDown, emCnStart );
	g_bIsFeccBrightMinus = TRUE;
	g_nTmFeccBrightMinus = SetTimer( NULL, 0, TIME_FECCCONTROL, CWifiTimerFun );
	return true;
}

bool CCameraControlLogic::On323VedioSourceNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	m_tVidFeccInfo = *( TVidFeccInfo * )wParam;
	//视频源
	CComboUI* pCombo = (CComboUI*)ICncCommonOp::FindControl( m_pm, _T("ComboCamSel") );
	if (pCombo)
	{
		ICncCommonOp::EnableControl( true, m_pm, _T("ComboCamSel") );
		pCombo->RemoveAll();

		TVidSourceInfo tVidSourceInfo = m_tVidFeccInfo.m_tVidSourceInfo;
		if (tVidSourceInfo.m_byNum == 0)
		{
			EnableFeccCtrl(false);
			return false;
		}
		for ( int nIndex = 0 ; nIndex < tVidSourceInfo.m_byNum ; nIndex++ )
		{
			TVidAliasInfo tVidAliasInfo = tVidSourceInfo.m_atVidInfo[nIndex];
			CListLabelElementUI *pListLabelElement = (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
			pListLabelElement->SetText(CA2T(tVidAliasInfo.m_abyAlias));
			pListLabelElement->SetTag(tVidAliasInfo.m_byIndex);
			pCombo->Add(pListLabelElement);
			//选中当前源
			if ( m_tVidFeccInfo.m_byVidno == tVidAliasInfo.m_byIndex )
			{
				pCombo->SelectItem(nIndex);
			}
		}
	}
	if ( !m_tVidFeccInfo.m_bAllowFecc )
	{
		EnableFeccCtrl(false);
	}
	else
	{
		EnableFeccCtrl(true);
	}
	return true;
}

bool CCameraControlLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	//断开时，清空远摇数据
	TConfEpID tFeccConfEpID;
	tFeccConfEpID.Clear();
	ComInterface->SetFeccConfEpInfo(tFeccConfEpID);
	return true;
}
