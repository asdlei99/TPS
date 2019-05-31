// cameralogic.cpp: implementation of the CCameraLogic class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h" 
#include "cameraLogic.h"

#define MAX_PICSCEAPT_NUMBER 15
#define MIN_PICSCEAPT_NUMBER 1

u16 g_wCameraTimerID = 0;
u16 g_wReserProtectID = 0;

static UINT g_nZoomPlusTime = 0;
static UINT g_nZoomSubTime = 0;

VOID CALLBACK CBCameraTimerFun( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )   //by xhx
{
	if ( idEvent == g_wReserProtectID )
	{
		KillTimer( NULL,g_wReserProtectID );
	}
	else if ( idEvent == g_wCameraTimerID )
	{
		KillTimer( NULL, g_wCameraTimerID );
		CAMERALOGICRPTR->ResetNormal();
	}
	else if ( idEvent == g_nZoomPlusTime )
	{
		CAMERALOGICRPTR->m_bZoomPlus = false;
		KillTimer( NULL, g_nZoomPlusTime );
	}
	else if ( idEvent == g_nZoomSubTime )
	{
		CAMERALOGICRPTR->m_bZoomSub = false;
		KillTimer( NULL, g_nZoomSubTime );
	}
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCameraLogic::CCameraLogic()
: m_strComboboxCamera("ComboboxCamera")
, m_strStaticCamCategory("StcCamCategory")
, m_strBtnSwitchVisualField("PresetDlg/BtnSwitchVisualField")
, m_strBtnSwitchPersetMove("PresetDlg/BtnSwitchPersetMove")
, m_strComboboxExposureGain("ComboboxExposureGain")
, m_strComboboxShut("ComboboxShut")
, m_strComboboxBackLight("ComboboxBackLight")
, m_strSliderAperture("SliderAperture")
, m_strEdtAperture("EdtAperture")
, m_strSliderRGain("SliderRGain")
, m_strEdtRGain("EdtRGain")
, m_strSliderBGain("SliderBGain")
, m_strEdtBGain("EdtBGain")
, m_strSliderPicSceApt("ManuelModeDlg/SliderPicSceApt")
, m_strEdtPicSceApt("ManuelModeDlg/EdtPicSceApt")
, m_strSliderContrast("SliderContrast")
, m_strEdtContrast("EdtContrast")
, m_strSliderSaturat("SliderSaturat")
, m_strEdtSaturat("EdtSaturat")
, m_strSliderHue("SliderHue")
, m_strEdtHue("EdtHue")
, m_strSliderBright("SliderBright")
, m_strEdtBright("EdtBright")
, m_strEdtZoom("PresetDlg/EdtZoom")
, m_strBtnSwitch3DNR("BtnSwitch3DNR")
, m_strBtnSwitchAutoExposure("BtnSwitchAutoExposure")
, m_strBtnSwitchAutoWB("BtnSwitchAutoWB")
, m_strBtnZoomPlus("PresetDlg/BtnZoomPlus")
, m_strBtnZoomSub("PresetDlg/BtnZoomSub")
, m_bIsCameraPowerOn(false)
, m_bLoginByOther(false)
, m_bZoomPlus(false)
, m_bZoomSub(false)
{
}

CCameraLogic::~CCameraLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CCameraLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_CFG_NTY, CCameraLogic::OnCameraCfgNty, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_SELECT_IND, CCameraLogic::OnCameraSelectInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_ZOOM_IND, CCameraLogic::OnCameraZoomInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_OSDSHOW_IND, CCameraLogic::OnCameraOSDShowInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_AUTO_FOCUS_IND, CCameraLogic::OnCameraAutoFocusInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_FOCUS_IND, CCameraLogic::OnCameraFocusInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_PERSET_MOVE_IND, CCameraLogic::OnCameraPersetMoveInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_AUTO_EXPOSURE_IND, CCameraLogic::OnCameraAutoExposureInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_GAIN_IND, CCameraLogic::OnCameraGainInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_SHUT_SPD_IND, CCameraLogic::OnCameraShutSpdInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_BACK_LIGHT_IND, CCameraLogic::OnCameraBackLightInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_APERTURE_IND, CCameraLogic::OnCameraApertureInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_AUTO_WB_IND, CCameraLogic::OnCameraAutoWBInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_RGAIN_IND, CCameraLogic::OnCameraRGainInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_BGAIN_IND, CCameraLogic::OnCameraBGainInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_PIC_SCENE_MODE_IND, CCameraLogic::OnCameraPicSceneModeInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_GAMMA_IND, CCameraLogic::OnCameraGammaInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_PIC_SCE_APT_IND, CCameraLogic::OnCameraPicSceAptInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_CONTRAST_IND, CCameraLogic::OnCameraContrastInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_SATURAT_IND, CCameraLogic::OnCameraSaturatInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_HUE_IND, CCameraLogic::OnCameraHueInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_BRIGHT_IND, CCameraLogic::OnCameraBrightInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_NR_STM_CLEAN_IND, CCameraLogic::OnCameraNRStmCleanInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_3DNR_IND, CCameraLogic::OnCamera3DNRInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_RESET_IND, CCameraLogic::OnCameraResetInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_PERSET_SAVE_IND, CCameraLogic::OnCameraPersetSaveInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_SET_CAMERA_ZOOM_IND, CCameraLogic::OnSetCameraZoomInd, CAMERALOGICRPTR, CCameraLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_CAMERA_POWER_ON_NTY, CCameraLogic::OnCameraPowerOnNty, CAMERALOGICRPTR, CCameraLogic );
}

void CCameraLogic::UnRegMsg()
{
}

void CCameraLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::InitWnd", CCameraLogic::InitWnd, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnComboboxCameraClick", CCameraLogic::OnComboboxCameraClick, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnImportClick", CCameraLogic::OnBtnImportClick, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnExportClick", CCameraLogic::OnBtnExportClick, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnResumeClick", CCameraLogic::OnBtnResumeClick, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnUpgradeCameraClick", CCameraLogic::OnBtnUpgradeCameraClick, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnZoomPlusDown", CCameraLogic::OnBtnZoomPlusDown, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnZoomPlusUp", CCameraLogic::OnBtnZoomPlusUp, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnZoomSubDown", CCameraLogic::OnBtnZoomSubDown, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnZoomSubUp", CCameraLogic::OnBtnZoomSubUp, CAMERALOGICRPTR, CCameraLogic );
//	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnZoomPlusClick", CCameraLogic::OnBtnZoomPlusClick, CAMERALOGICRPTR, CCameraLogic );
//	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnZoomSubClick", CCameraLogic::OnBtnZoomSubClick, CAMERALOGICRPTR, CCameraLogic );
//	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnZoomPlusHold", CCameraLogic::OnBtnZoomPlusHold, CAMERALOGICRPTR, CCameraLogic );
//	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnZoomPlusHoldEnd", CCameraLogic::OnBtnZoomPlusHoldEnd, CAMERALOGICRPTR, CCameraLogic );
//	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnZoomSubHold", CCameraLogic::OnBtnZoomSubHold, CAMERALOGICRPTR, CCameraLogic );
//	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnZoomSubHoldEnd", CCameraLogic::OnBtnZoomSubHoldEnd, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnSwitchVisualFieldClick", CCameraLogic::OnBtnSwitchVisualFieldClick, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnPresetSaveClick", CCameraLogic::OnBtnPresetSaveClick, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnManuelFocusClick", CCameraLogic::OnBtnManuelFocusClick, CAMERALOGICRPTR, CCameraLogic );	
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnAutoFocusClick", CCameraLogic::OnBtnAutoFocusClick, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnLBtnDownFocusNear", CCameraLogic::OnLBtnDownFocusNear, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnLBtnUpFocusNear", CCameraLogic::OnLBtnUpFocusNear, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnLBtnDownFocusFar", CCameraLogic::OnLBtnDownFocusFar, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnLBtnUpFocusFar", CCameraLogic::OnLBtnUpFocusFar, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnSwitchPersetMove", CCameraLogic::OnBtnSwitchPersetMove, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnSwitchAutoExposure", CCameraLogic::OnBtnSwitchAutoExposure, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnSliderApertureChanged", CCameraLogic::OnSliderApertureChanged, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnSwitchAutoWB", CCameraLogic::OnBtnSwitchAutoWB, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnSliderRGainChanged", CCameraLogic::OnSliderRGainChanged, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnSliderBGainChanged", CCameraLogic::OnSliderBGainChanged, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnRadioLamp", CCameraLogic::OnBtnRadioLamp, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnRadioSun", CCameraLogic::OnBtnRadioSun, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnRadioManuel", CCameraLogic::OnBtnRadioManuel, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnGammaOnClick", CCameraLogic::OnBtnGammaOnClick, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnGammaOffClick", CCameraLogic::OnBtnGammaOffClick, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnSmart1Click", CCameraLogic::OnBtnSmart1Click, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnSmart2Click", CCameraLogic::OnBtnSmart2Click, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnSliderPicSceAptChanged", CCameraLogic::OnSliderPicSceAptChanged, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnSliderContrastChanged", CCameraLogic::OnSliderContrastChanged, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnSliderSaturatChanged", CCameraLogic::OnSliderSaturatChanged, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnSliderHueChanged", CCameraLogic::OnSliderHueChanged, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnSliderBrightChanged", CCameraLogic::OnSliderBrightChanged, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnNROffClick", CCameraLogic::OnBtnNROffClick, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnNRLowClick", CCameraLogic::OnBtnNRLowClick, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnNRMidClick", CCameraLogic::OnBtnNRMidClick, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnNRHighClick", CCameraLogic::OnBtnNRHighClick, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnSwitch3DNRClick", CCameraLogic::OnBtnSwitch3DNRClick, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnComboboxExposureGainClick", CCameraLogic::OnComboboxExposureGainClick, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnComboboxShutClick", CCameraLogic::OnComboboxShutClick, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnComboboxBackLightClick", CCameraLogic::OnComboboxBackLightClick, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnEdtApertureChange", CCameraLogic::OnEdtApertureChange, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnKillFocusEdtAperture", CCameraLogic::OnKillFocusEdtAperture, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnEdtRGainChange", CCameraLogic::OnEdtRGainChange, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnKillFocusEdtRGain", CCameraLogic::OnKillFocusEdtRGain, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnEdtBGainChange", CCameraLogic::OnEdtBGainChange, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnKillFocusEdtBGain", CCameraLogic::OnKillFocusEdtBGain, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnEdtPicSceAptChange", CCameraLogic::OnEdtPicSceAptChange, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnKillFocusEdtPicSceApt", CCameraLogic::OnKillFocusEdtPicSceApt, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnEdtContrastChange", CCameraLogic::OnEdtContrastChange, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnKillFocusEdtContrast", CCameraLogic::OnKillFocusEdtContrast, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnEdtSaturatChange", CCameraLogic::OnEdtSaturatChange, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnKillFocusEdtSaturat", CCameraLogic::OnKillFocusEdtSaturat, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnEdtHueChange", CCameraLogic::OnEdtHueChange, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnKillFocusEdtHue", CCameraLogic::OnKillFocusEdtHue, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnEdtBrightChange", CCameraLogic::OnEdtBrightChange, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnKillFocusEdtBright", CCameraLogic::OnKillFocusEdtBright, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnEdtZoomChange", CCameraLogic::OnEdtZoomChange, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnEdtZoomKillFocus", CCameraLogic::OnEdtZoomKillFocus, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnCameraClick", CCameraLogic::OnCameraClick, CAMERALOGICRPTR, CCameraLogic );	
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnComboboxApertureClick", CCameraLogic::OnComboboxApertureClick, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnSwitchNRClick", CCameraLogic::OnBtnSwitchNRClick, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnComboboxNRClick", CCameraLogic::OnComboboxNRClick, CAMERALOGICRPTR, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnSwitchsonyBLClick", CCameraLogic::OnBtnSwitchsonyBLClick, CAMERALOGICRPTR, CCameraLogic );

}

void CCameraLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CCameraLogic::InitWnd" );
}

bool CCameraLogic::InitWnd(  const IArgs & arg )
{
	CLogicBase::InitWnd( arg );

	std::vector<CString> vecCamera;																//设置摄像机下拉框数据
	vecCamera.push_back("摄像机1");
	vecCamera.push_back("摄像机2");
	vecCamera.push_back("摄像机3");
	UIFACTORYMGR_PTR->SetComboListData( m_strComboboxCamera, vecCamera, m_pWndTree );
	SetCamName( _T("摄像机1") );
	m_byCameraIndx = 0;

	vecCamera.clear();																			//sony摄像机配置
	vecCamera.push_back("95D");
	vecCamera.push_back("sony");
// 	UIFACTORYMGR_PTR->SetComboListData( m_strComboboxCameraSony, vecCamera, m_pWndTree );
// 	UIFACTORYMGR_PTR->SetComboText( m_strComboboxCameraSony, _T("95D"), m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strStaticCamCategory, _T("95D"), m_pWndTree );
	m_emCamType = emCamHD95D;

	//sony降噪等级
	vecCamera.clear();																
	vecCamera.push_back("level 1");
	vecCamera.push_back("level 2");
	vecCamera.push_back("level 3");
	vecCamera.push_back("level 4");
	vecCamera.push_back("level 5");
	UIFACTORYMGR_PTR->SetComboListData( "ComboboxNR", vecCamera, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboText( "ComboboxNR", _T("level 1"), m_pWndTree );

	//sony光圈调节
	vecCamera.clear();
	vecCamera.push_back("Close");
	vecCamera.push_back("F9.6");
	vecCamera.push_back("F8");
	vecCamera.push_back("F6.8");
	vecCamera.push_back("F5.6");
	vecCamera.push_back("F4.8");
	vecCamera.push_back("F4");
	vecCamera.push_back("F3.4");
	vecCamera.push_back("F2.8");
	vecCamera.push_back("F2.4");
	vecCamera.push_back("F2");
	vecCamera.push_back("F1.8");
	UIFACTORYMGR_PTR->SetComboListData( "ComboboxAperture", vecCamera, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboText( "ComboboxAperture", _T("Close"), m_pWndTree );

	std::vector<CString> vecExposureGain;														//设置曝光增益下拉框数据
	for ( int nExposureGain = 0; nExposureGain < 43; nExposureGain += 3 )
	{
		CString strExposureGain;
		strExposureGain.Format( "%ddB", nExposureGain );
		vecExposureGain.push_back(strExposureGain);
	}
	UIFACTORYMGR_PTR->SetComboListData( m_strComboboxExposureGain, vecExposureGain, m_pWndTree );  
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxExposureGain, "6dB", m_pWndTree );
	
	vecExposureGain.clear();
	//规格有误 sony摄像机曝光增益如下
// 	for ( float fExposureGain = -10.5; fExposureGain < 12; fExposureGain += 1.5 )
// 	{
// 		CString strExposureGain;
// 		strExposureGain.Format( "%.1fdB", fExposureGain );
// 		if ( strExposureGain.Right(3) == "0dB" )
// 		{
// 			int npos = strExposureGain.ReverseFind('.');
// 			if ( npos >= 0 )
// 			{
// 				strExposureGain = strExposureGain.Left(npos) + strExposureGain.Right(2);
// 			}
// 		}
// 		vecExposureGain.push_back(strExposureGain);
// 	}
	//14/10/16 by577
	for ( int nSonyExposureGain = 0; nSonyExposureGain < 30; nSonyExposureGain +=2 )           //设置sony曝光增益下拉框数据
	{
		CString strExposureGain;
		strExposureGain.Format( "%d", nSonyExposureGain );
		vecExposureGain.push_back(strExposureGain);
	}

	UIFACTORYMGR_PTR->SetComboListData( "ComboboxsonyExposureGain", vecExposureGain, m_pWndTree );  
	UIFACTORYMGR_PTR->SetComboText( "ComboboxsonyExposureGain", "0", m_pWndTree );

	std::vector<CString> vecShut;																//设置快门下拉框数据
	vecShut.push_back( "1/60" );
	vecShut.push_back( "1/100" );
	vecShut.push_back( "1/250" );
	vecShut.push_back( "1/500" );
	vecShut.push_back( "1/1000" );
	vecShut.push_back( "1/2000" );
	vecShut.push_back( "1/4000" );
	vecShut.push_back( "1/10000" );
	UIFACTORYMGR_PTR->SetComboListData( m_strComboboxShut, vecShut, m_pWndTree );  
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxShut, "1/60", m_pWndTree );

	vecShut.clear();																			//设置sony快门下拉框数据
	vecShut.push_back( "1/1" );
	vecShut.push_back( "1/2" );
	vecShut.push_back( "1/4" );
	vecShut.push_back( "1/8" );
	vecShut.push_back( "1/15" );
	vecShut.push_back( "1/30" );
	vecShut.push_back( "1/60" );
	vecShut.push_back( "1/90" );
	vecShut.push_back( "1/100" );
	vecShut.push_back( "1/125" );
	vecShut.push_back( "1/180" );
	vecShut.push_back( "1/250" );
	vecShut.push_back( "1/350" );
	vecShut.push_back( "1/500" );
	vecShut.push_back( "1/725" );
	vecShut.push_back( "1/1000" );
	vecShut.push_back( "1/1500" );
	vecShut.push_back( "1/2000" );
	vecShut.push_back( "1/3000" );
	vecShut.push_back( "1/4000" );
	vecShut.push_back( "1/6000" );
	vecShut.push_back( "1/10000" );
	UIFACTORYMGR_PTR->SetComboListData( "ComboboxsonyShut", vecShut, m_pWndTree );  
	UIFACTORYMGR_PTR->SetComboText( "ComboboxsonyShut", "1/1", m_pWndTree );

	std::vector<CString> vecBackLight;															//设置背光下拉框数据
	vecBackLight.push_back( "关闭" );
	for ( int nBackLight = 0; nBackLight < 16; nBackLight++ )
	{
		CString strBackLight;
		strBackLight.Format( "multi%d", nBackLight );
		vecBackLight.push_back(strBackLight);
	}
	vecBackLight.push_back( "center" );
	vecBackLight.push_back( "face detect" );
	UIFACTORYMGR_PTR->SetComboListData( m_strComboboxBackLight, vecBackLight, m_pWndTree );  
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxBackLight, "multi7", m_pWndTree );

	//Bug00173254  -- by xhx 20140123
	CTransparentBtn* pBtnZoomPlus = (CTransparentBtn*)UIFACTORYMGR_PTR->GetWindowPtr( m_strBtnZoomPlus, m_pWndTree );
	if ( NULL != pBtnZoomPlus )
	{
		pBtnZoomPlus->SetUseElapse(600);
	}

	CTransparentBtn* pBtnZoomSub = (CTransparentBtn*)UIFACTORYMGR_PTR->GetWindowPtr( m_strBtnZoomSub, m_pWndTree );
	if ( NULL != pBtnZoomSub )
	{
		pBtnZoomSub->SetUseElapse(600);
	}

	SetFocus(NULL);

	return true;
}

void CCameraLogic::Clear()
{
	int i = 0;
	m_bIsCameraPowerOn = false;
	m_bLoginByOther = false;
	KillTimer(NULL, g_wCameraTimerID);
	KillTimer(NULL, g_wReserProtectID);
	KillTimer(NULL, g_nZoomSubTime);
	KillTimer(NULL, g_nZoomPlusTime);
}

bool CCameraLogic::OnComboboxCameraClick( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	//m_bNty = false;

	Value_TransparentComboBoxText valueTransparentComboBoxText;
	UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, m_strComboboxCamera, m_pWndTree );

	u8 byCameraIndx = 0;
	String strComboText = valueTransparentComboBoxText.strComboText;
	if ( strComboText == "摄像机1" )
	{
		byCameraIndx = 0;
	}
	else if ( strComboText == "摄像机2" )
	{
		byCameraIndx = 1;
	}
	else if ( strComboText == "摄像机3" )
	{
		byCameraIndx = 2;
	}

	u16 nRet = COMIFMGRPTR->CamSelCmd( byCameraIndx );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "选择摄像机请求发送失败" );
	}

	return true;
}

bool CCameraLogic::OnBtnImportClick( const IArgs& args )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmImpCommonClean", NULL, g_stcStrImpCommonDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchImportCamCfg", NULL, g_stcStrImpCommonDlg );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrImpCommonDlg );

	return true;
}

bool CCameraLogic::OnBtnExportClick( const IArgs& args )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmExpCommonClean", NULL, g_stcStrExpCommonDlg );
	UIFACTORYMGR_PTR->LoadScheme( "SchExportCameraCfg", NULL, g_stcStrExpCommonDlg );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrExpCommonDlg );	

	return true;
}

bool CCameraLogic::OnBtnResumeClick( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	u16 nRet = COMIFMGRPTR->CamResetCmd();
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "恢复默认请求发送失败" );
		return true;
	}

	MSG_BOX_ONLY_READ( _T("正在恢复默认值，请稍等，摄像机配置暂时无法配置") );

	return true;
}

bool CCameraLogic::OnBtnUpgradeCameraClick( const IArgs& args )
{
	return true;
}

bool CCameraLogic::OnBtnZoomPlusDown( const IArgs& args )
{
	EmZoom emZoom = emTele;
	EmZoomStatus emZoomStatus = emStart;
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom , emZoomStatus);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom请求发送失败" );
	}
	return true;
}
bool CCameraLogic::OnBtnZoomPlusUp( const IArgs& args )
{
	EmZoom emZoom = emTele;
	EmZoomStatus emZoomStatus = emStop;
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom , emZoomStatus);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom请求发送失败" );
	}
	return true;
}
bool CCameraLogic::OnBtnZoomSubDown( const IArgs& args )
{
	EmZoom emZoom = emWide;
	EmZoomStatus emZoomStatus = emStart;
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom, emZoomStatus );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom请求发送失败" );
	}
	return true;
}
bool CCameraLogic::OnBtnZoomSubUp( const IArgs& args )
{
	EmZoom emZoom = emWide;
	EmZoomStatus emZoomStatus = emStop;
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom, emZoomStatus );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom请求发送失败" );
	}
	return true;
}

bool CCameraLogic::OnBtnZoomPlusClick( const IArgs& args )
{
	if (m_bZoomPlus)
	{
		return true;
	}
	m_bZoomPlus = true;
	g_nZoomPlusTime = SetTimer( NULL, 1, 1000, CBCameraTimerFun );

	EmZoom emZoom = emTele;
	EmZoomStatus emZoomStatus = emStart;
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom , emZoomStatus);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom请求发送失败" );
	}
	
	return true;
}

bool CCameraLogic::OnBtnZoomSubClick( const IArgs& args )
{
	if (m_bZoomSub)
	{
		return true;
	}
	m_bZoomSub = true;
	g_nZoomSubTime = SetTimer( NULL, 1, 1000, CBCameraTimerFun );

	EmZoom emZoom = emWide;
	EmZoomStatus emZoomStatus = emStart;
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom, emZoomStatus );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom请求发送失败" );
	}
	
	return true;
}

bool CCameraLogic::OnBtnZoomPlusHold( const IArgs& args )
{
	EmZoom emZoom = emTele;
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom请求发送失败" );
	}
	
	return true;
}

bool CCameraLogic::OnBtnZoomPlusHoldEnd( const IArgs& args )
{
	return true;
}

bool CCameraLogic::OnBtnZoomSubHold( const IArgs& args )
{
	EmZoom emZoom = emWide;
	
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( emZoom );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Zoom请求发送失败" );
	}
	
	return true;
}

bool CCameraLogic::OnBtnZoomSubHoldEnd( const IArgs& args )
{
	return true;
}


bool CCameraLogic::OnBtnSwitchVisualFieldClick( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	Value_SwitchState valueSwitchState;
	UIFACTORYMGR_PTR->GetPropertyValue( valueSwitchState, m_strBtnSwitchVisualField, m_pWndTree );

	EmOSDShow emOSDShow;
	if ( valueSwitchState.bState )
	{
		emOSDShow = emOSDOn;
	}
	else
	{
		emOSDShow = emOSDOff;
	}
	
	u16 nRet = COMIFMGRPTR->SetCamOSDCmd( emOSDShow );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "在OSD上显示视野比例请求发送失败" );
	}

	return true;
}

bool CCameraLogic::OnBtnPresetSaveClick( const IArgs& args )
{
	u16 nRet = COMIFMGRPTR->CamPresetSaveCmd();
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "保存至预置位1请求发送失败" );
	}
	return true;
}

bool CCameraLogic::OnBtnManuelFocusClick( const IArgs& args )
{
	EmFocusMode emFocusMode = emFocusManuel;
	u16 nRet = COMIFMGRPTR->SetCamAutoFocusCmd(emFocusMode);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "手动焦距请求发送失败" );
	}
	return true;
}

bool CCameraLogic::OnBtnAutoFocusClick( const IArgs& args )
{
	EmFocusMode emFocusMode = emFocusAuto;
	u16 nRet = COMIFMGRPTR->SetCamAutoFocusCmd(emFocusMode);
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "自动焦距请求发送失败" );
	}
	return true;
}

bool CCameraLogic::OnLBtnDownFocusNear( const IArgs& args )
{
	EmFocus emFocus = emNear;
	EmCnAction emCnAction = emCnStart;
	
	u16 nRet = COMIFMGRPTR->SetCamFocusCmd( emFocus, emCnAction );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "焦距拉近请求发送失败" );
	}

	return true;
}

bool CCameraLogic::OnLBtnUpFocusNear( const IArgs& args )
{
	EmFocus emFocus = emNear;
	EmCnAction emCnAction = emCnStop;
	
	u16 nRet = COMIFMGRPTR->SetCamFocusCmd( emFocus, emCnAction );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "焦距拉近请求发送失败" );
	}

	return true;
}

bool CCameraLogic::OnLBtnDownFocusFar( const IArgs& args )
{
	EmFocus emFocus = emFar;
	EmCnAction emCnAction = emCnStart;
	
	u16 nRet = COMIFMGRPTR->SetCamFocusCmd( emFocus, emCnAction );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "焦距推远请求发送失败" );
	}
	
	return true;
}

bool CCameraLogic::OnLBtnUpFocusFar( const IArgs& args )
{
	EmFocus emFocus = emFar;
	EmCnAction emCnAction = emCnStop;
	
	u16 nRet = COMIFMGRPTR->SetCamFocusCmd( emFocus, emCnAction );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "焦距推远请求发送失败" );
	}
	
	return true;
}

bool CCameraLogic::OnBtnSwitchPersetMove( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	Value_SwitchState valueSwitchState;
	UIFACTORYMGR_PTR->GetPropertyValue( valueSwitchState, m_strBtnSwitchPersetMove, m_pWndTree );

	u16 nRet = COMIFMGRPTR->SetCamPresetMoveCmd( valueSwitchState.bState );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "开机调用预置位1请求发送失败" );
	}

	return true;
}

bool CCameraLogic::OnBtnSwitchAutoExposure( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	Value_SwitchState valueSwitchState;
	UIFACTORYMGR_PTR->GetPropertyValue( valueSwitchState, m_strBtnSwitchAutoExposure, m_pWndTree );

	if ( valueSwitchState.bState )
	{
		u16 nRet = COMIFMGRPTR->CamAutoExposureCmd( emExpAuto );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "自动曝光请求发送失败" );
		}
	}
	else
	{
		u16 nRet = COMIFMGRPTR->CamAutoExposureCmd( emExpManuel );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "手动曝光请求发送失败" );
		}
		else
		{
			EmGain emGain;
			GetGainValue( emGain );
			
			u16 nRetGain = COMIFMGRPTR->CamGainCmd( emGain );
			if ( nRetGain != NO_ERROR )
			{
				WARNMESSAGE( "增益请求发送失败" );
			}

			EmShutSpd emShutSpd;
			GetShutSpdValue( emShutSpd );
			u16 nRetShutSpd = COMIFMGRPTR->CamShutSpdCmd( emShutSpd );
			if ( nRetShutSpd != NO_ERROR )
			{
				WARNMESSAGE( "快门请求发送失败" );
			}

			if ( m_emCamType == emCamHD95D )
			{
				EmBackLightType emBackLightType;
				u8 byMulti = (u8)(TP_INVALID_INDEX);
				
				GetBackLightValue(emBackLightType, byMulti);
						
				u16 nRetBackLight = COMIFMGRPTR->CamBackLightCmd( emBackLightType, byMulti );
				if ( nRetBackLight != NO_ERROR )
				{
					WARNMESSAGE( "背光请求发送失败" );
				}
			}
			
			u8 byAperture;
			String strAperture;
			if ( m_emCamType == emCamHD95D )
			{
				UIFACTORYMGR_PTR->GetCaption( m_strEdtAperture, strAperture, m_pWndTree );			
				byAperture = atoi(strAperture.c_str());
			}
			else 
			{
				EmSonyIris emSonyIris;	
				GetSonyIrisValue( emSonyIris );
				byAperture = (u8)emSonyIris;
			}

			u16 nRetAperture = COMIFMGRPTR->CamAperture( byAperture );
			if ( nRetAperture != NO_ERROR )
			{
				WARNMESSAGE( "光圈调节请求发送失败" );
			}
		}
	}

	return true;
}

bool CCameraLogic::OnSliderApertureChanged( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	Value_CSliderCtrlPos valueCSliderCtrlPos;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strSliderAperture, m_pWndTree );

	CString strCaption;
	strCaption.Format( "%d", valueCSliderCtrlPos.nPos );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtAperture, m_pWndTree );


	u8 byAperture = valueCSliderCtrlPos.nPos;
	u8 byApertureInLib = 0;
	LIBDATAMGRPTR->GetCamAperture( byApertureInLib );
	if ( byAperture == byApertureInLib )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamAperture( byAperture );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "光圈调节请求发送失败" );
	}

	return true;
}

bool CCameraLogic::OnBtnSwitchAutoWB( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	Value_SwitchState valueSwitchState;
	UIFACTORYMGR_PTR->GetPropertyValue( valueSwitchState, m_strBtnSwitchAutoWB, m_pWndTree );
	
	if ( valueSwitchState.bState )
	{
		u16 nRet = COMIFMGRPTR->CamAutoWBCmd( emWBAuto );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "自动白平衡请求发送失败" );
		}
	}
	else
	{
		u16 nRet = COMIFMGRPTR->CamAutoWBCmd( emWBManual );
		if ( nRet != NO_ERROR )
		{
			WARNMESSAGE( "自动白平衡请求发送失败" );
		}

		String strRGain;
		UIFACTORYMGR_PTR->GetCaption( m_strEdtRGain, strRGain, m_pWndTree );
		
		u16 wRGain = atoi(strRGain.c_str());
		u16 nRetRGain = COMIFMGRPTR->CamRGainCmd( wRGain );
		if ( nRetRGain != NO_ERROR )
		{
			WARNMESSAGE( "RGain调节请求发送失败" );
		}


		String strBGain;
		UIFACTORYMGR_PTR->GetCaption( m_strEdtBGain, strBGain, m_pWndTree );

		u16 wBGain = atoi(strBGain.c_str());
		u16 nRetBGain = COMIFMGRPTR->CamBGainCmd( wBGain );
		if ( nRetBGain != NO_ERROR )
		{
			WARNMESSAGE( "BGain调节请求发送失败" );
		}
	}

	return true;
}

bool CCameraLogic::OnSliderRGainChanged( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}


	Value_CSliderCtrlPos valueCSliderCtrlPos;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strSliderRGain, m_pWndTree );
	
	SetRGainValue( valueCSliderCtrlPos.nPos );
	
	u16 wRGain = valueCSliderCtrlPos.nPos;
	u16 wRGainInLib = 0;
	LIBDATAMGRPTR->GetCamRGain( wRGainInLib );
	if ( wRGain == wRGainInLib )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamRGainCmd( wRGain );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "RGain调节请求发送失败" );
	}

	return true;
}

bool CCameraLogic::OnSliderBGainChanged( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	Value_CSliderCtrlPos valueCSliderCtrlPos;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strSliderBGain, m_pWndTree );
	
	SetBGainValue( valueCSliderCtrlPos.nPos );
	
	u16 wBGain = valueCSliderCtrlPos.nPos;
	u16 wBGainInLib = 0;
	LIBDATAMGRPTR->GetCamBGain( wBGainInLib );
	if ( wBGain == wBGainInLib )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamBGainCmd( wBGain );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "BGain调节请求发送失败" );
	}

	return true;
}

bool CCameraLogic::OnBtnRadioLamp( const IArgs& args )
{
	if ( m_pWndTree == NULL)
	{
		return false;
	}

	EmPicSceMode emPicSceMode = emLamp;
	u16 nRet = COMIFMGRPTR->CamPicSceneModeCmd( emPicSceMode );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "日光灯模式请求发送失败" );//失败时恢复原来的ButtonCheck状态
	}

	UIFACTORYMGR_PTR->LoadScheme( _T("SchPicSceneModeLamp"), m_pWndTree );

	return true;
}

bool CCameraLogic::OnBtnRadioSun( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	EmPicSceMode emPicSceMode = emSun;
	u16 nRet = COMIFMGRPTR->CamPicSceneModeCmd( emPicSceMode );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "太阳光模式请求发送失败" );
	}

	UIFACTORYMGR_PTR->LoadScheme( _T("SchPicSceneModeSun"), m_pWndTree );

	return true;
}

bool CCameraLogic::OnBtnRadioManuel( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	EmPicSceMode emPicSceMode = emManuel;
	u16 nRet = COMIFMGRPTR->CamPicSceneModeCmd( emPicSceMode );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "手动模式请求发送失败" );
	}

	UIFACTORYMGR_PTR->LoadScheme( _T("SchPicSceneModeManuel"), m_pWndTree );

	return true;
}

bool CCameraLogic::OnBtnGammaOnClick( const IArgs& args )
{
	EmGamma emGamma = emGammaOn;
	u16 nRet = COMIFMGRPTR->CamGammaCmd( emGamma );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Gamma On请求发送失败" );
	}

	return true;
}

bool CCameraLogic::OnBtnGammaOffClick( const IArgs& args )
{
	EmGamma emGamma = emGammaOff;
	u16 nRet = COMIFMGRPTR->CamGammaCmd( emGamma );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Gamma Off请求发送失败" );
	}

	return true;
}

bool CCameraLogic::OnBtnSmart1Click( const IArgs& args )
{
	EmGamma emGamma = emSmart1;
	u16 nRet = COMIFMGRPTR->CamGammaCmd( emGamma );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Gamma Smart1请求发送失败" );
	}

	return true;
}

bool CCameraLogic::OnBtnSmart2Click( const IArgs& args )
{
	EmGamma emGamma = emSmart2;
	u16 nRet = COMIFMGRPTR->CamGammaCmd( emGamma );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "Gamma Smart2请求发送失败" );
	}

	return true;
}

bool CCameraLogic::OnSliderPicSceAptChanged( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	Value_CSliderCtrlPos valueCSliderCtrlPos;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strSliderPicSceApt, m_pWndTree );
	
	SetPicSceAptValue( valueCSliderCtrlPos.nPos );

	u8 byPicSceApt = valueCSliderCtrlPos.nPos;
	u8 byPicSceAptInLib = 0;
	LIBDATAMGRPTR->GetCamPicSceApt( byPicSceAptInLib );
	if ( byPicSceApt == byPicSceAptInLib )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamPicSceAptCmd( byPicSceApt );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "模式光圈调节请求发送失败" );
	}
	return true;
}

bool CCameraLogic::OnSliderContrastChanged( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	Value_CSliderCtrlPos valueCSliderCtrlPos;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strSliderContrast, m_pWndTree );
	
	SetContrastValue( valueCSliderCtrlPos.nPos );

	u16 wContrast = valueCSliderCtrlPos.nPos;
	u16 wContrastInLib = 0;
	LIBDATAMGRPTR->GetCamContrast( wContrastInLib );
	if ( wContrast == wContrastInLib )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamContrastCmd( wContrast );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "对比度请求发送失败" );
	}

	return true;
}

bool CCameraLogic::OnSliderSaturatChanged( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	Value_CSliderCtrlPos valueCSliderCtrlPos;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strSliderSaturat, m_pWndTree );
	
	SetSaturatValue( valueCSliderCtrlPos.nPos );

	u16 wSaturat = valueCSliderCtrlPos.nPos;
	u16 wSaturatInLib = 0;
	LIBDATAMGRPTR->GetCamSaturat( wSaturatInLib );
	if ( wSaturat == wSaturatInLib )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamSaturatCmd( wSaturat );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "饱和度请求发送失败" );
	}

	return true;
}

bool CCameraLogic::OnSliderHueChanged( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}

	Value_CSliderCtrlPos valueCSliderCtrlPos;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strSliderHue, m_pWndTree );
	
	SetHueValue( valueCSliderCtrlPos.nPos );

	u16 wHue = valueCSliderCtrlPos.nPos;
	u16 wHueInLib = 0;
	LIBDATAMGRPTR->GetCamHue( wHueInLib );
	if ( wHue == wHueInLib )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamHueCmd( wHue );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "色度请求发送失败" );
	}

	return true;
}

bool CCameraLogic::OnSliderBrightChanged( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	BOOL bIsVisible = UIFACTORYMGR_PTR->IsVisible( m_strSliderBright, m_pWndTree );
	if ( !bIsVisible )
	{
		return false;
	}

	Value_CSliderCtrlPos valueCSliderCtrlPos;
	UIFACTORYMGR_PTR->GetPropertyValue( valueCSliderCtrlPos, m_strSliderBright, m_pWndTree );
	
	SetBrightValue( valueCSliderCtrlPos.nPos );

	u16 wBright = valueCSliderCtrlPos.nPos;
	u16 wBrightInLib = 0;
	LIBDATAMGRPTR->GetCamBright( wBrightInLib );
	if ( wBright == wBrightInLib )
	{
		return true;
	}

	u16 nRet = COMIFMGRPTR->CamBrightCmd( wBright );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "亮度请求发送失败" );
	}

	return true;
}

bool CCameraLogic::OnBtnNROffClick( const IArgs& args )
{
	EmStmClean emStmClean = emNRoff;
	u16 nRet = COMIFMGRPTR->CamNRStmCleanCmd( emStmClean );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "降噪过滤 off请求发送失败" );
	}

	return true;
}

bool CCameraLogic::OnBtnNRLowClick( const IArgs& args )
{
	EmStmClean emStmClean = emNRlow;
	u16 nRet = COMIFMGRPTR->CamNRStmCleanCmd( emStmClean );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "降噪过滤 low请求发送失败" );
	}

	return true;
}

bool CCameraLogic::OnBtnNRMidClick( const IArgs& args )
{
	EmStmClean emStmClean = emNRmid;
	u16 nRet = COMIFMGRPTR->CamNRStmCleanCmd( emStmClean );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "降噪过滤 mid请求发送失败" );
	}

	return true;
}

bool CCameraLogic::OnBtnNRHighClick( const IArgs& args )
{
	EmStmClean emStmClean = emNRhigh;
	u16 nRet = COMIFMGRPTR->CamNRStmCleanCmd( emStmClean );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "降噪过滤 high请求发送失败" );
	}

	return true;
}

bool CCameraLogic::OnBtnSwitch3DNRClick( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	Value_SwitchState valueSwitchState;
	UIFACTORYMGR_PTR->GetPropertyValue( valueSwitchState, m_strBtnSwitch3DNR, m_pWndTree );
	
	Em3DNR em3DNR;
	if ( valueSwitchState.bState )
	{
		em3DNR = em3DNROn;
	}
	else
	{
		em3DNR = em3DNROff;
	}
	
	u16 nRet = COMIFMGRPTR->Cam3DNRCmd( em3DNR );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "3D DNR请求发送失败" );
	}
	
	return true;
}

HRESULT CCameraLogic::OnCameraCfgNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_bIsCameraPowerOn && m_bLoginByOther )
	{
		m_bLoginByOther = false;
		KillTimer(NULL, g_wCameraTimerID);
	    ResetNormal();
	}

	TCnCameraCfg tCnCameraCfg;
	LIBDATAMGRPTR->GetCamCfg( tCnCameraCfg );
	SetCameraCfg( tCnCameraCfg );

	return S_OK;
}

HRESULT CCameraLogic::OnCameraSelectInd( WPARAM wparam, LPARAM lparam )
{
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( _T("选择摄像机设置失败") );
	}

	TCnCameraCfg tCnCameraCfg;
	LIBDATAMGRPTR->GetCamCfg( tCnCameraCfg );
	SetCameraCfg( tCnCameraCfg );

	//m_bNty = true;
	
	return S_OK;
}

HRESULT CCameraLogic::OnCameraZoomInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	EmZoom emZoom = static_cast<EmZoom>(wparam);
	BOOL bCamZoom = static_cast<BOOL>(lparam);

	if ( bCamZoom == FALSE )
	{
		WARNMESSAGE( "Zoom设置失败");
		return S_OK;
	}

	return S_OK;
}

HRESULT CCameraLogic::OnCameraOSDShowInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	EmOSDShow emOSDShow;
	LIBDATAMGRPTR->GetCamOSD( emOSDShow );
	BOOL bRet = static_cast<BOOL>(lparam);

	Value_SwitchState valueSwitchState;
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "OSDShow设置失败");
	}

	SetOSDShowValue( emOSDShow );

	return S_OK;
}

HRESULT CCameraLogic::OnCameraAutoFocusInd( WPARAM wparam, LPARAM lparam )
{
	EmFocusMode emFocusMode = static_cast<EmFocusMode>(wparam);
	BOOL bRet = static_cast<BOOL>(lparam);

	if ( bRet == FALSE )
	{
		SetCursorPos( 710, 530 );//20130326-解决弹出框后还能点击问题

		WARNMESSAGE( "自动焦距设置失败" );
	}

	return S_OK;
}

HRESULT CCameraLogic::OnCameraFocusInd( WPARAM wparam, LPARAM lparam )
{
	EmFocus emFocus = static_cast<EmFocus>(wparam);
	BOOL bRet = static_cast<BOOL>(lparam);

	if ( bRet == FALSE )
	{
		WARNMESSAGE( "焦距设置失败" );
	}
	return S_OK;
}

HRESULT CCameraLogic::OnCameraPersetMoveInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	BOOL bUsed;
	LIBDATAMGRPTR->GetCamPresetMove( bUsed );
	BOOL bRet = static_cast<BOOL>(lparam);
	
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "保存至预置位1设置失败");
	}

	SetPresetValue( bUsed );
	
	return S_OK;
}

HRESULT CCameraLogic::OnCameraAutoExposureInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	EmExpMode emExpMode;
	LIBDATAMGRPTR->GetCamExpMode( emExpMode );
	BOOL bRet = static_cast<BOOL>(lparam);

	if ( bRet == FALSE )
	{
		WARNMESSAGE( "自动曝光设置失败" );
	}

	SetAutoExp(emExpMode);


	return S_OK;
}

bool CCameraLogic::OnComboboxExposureGainClick( const IArgs& args )
{
	EmGain emGain;
	GetGainValue( emGain );
	
	u16 nRet = COMIFMGRPTR->CamGainCmd( emGain );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "增益请求发送失败" );
	}
	return true;
}

bool CCameraLogic::OnComboboxShutClick( const IArgs& args )
{
	EmShutSpd emShutSpd;
	GetShutSpdValue( emShutSpd );
	u16 nRet = COMIFMGRPTR->CamShutSpdCmd( emShutSpd );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "快门请求发送失败" );
	}
	return true;
}

HRESULT CCameraLogic::OnCameraGainInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	EmGain emGain;
	LIBDATAMGRPTR->GetCamGain( emGain );
	BOOL bRet = static_cast<BOOL>(lparam);

	if ( bRet == FALSE )
	{
		WARNMESSAGE( "增益设置失败" );
	}

	SetExpGainValue( emGain );

	return S_OK;
}

HRESULT CCameraLogic::OnCameraShutSpdInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	EmShutSpd emShutSpd;
	LIBDATAMGRPTR->GetCamShutSpd( emShutSpd );
	BOOL bRet = static_cast<BOOL>(lparam);

	if ( bRet == FALSE )
	{
		WARNMESSAGE( "快门设置失败" );
	}

	SetShutSpdValue(emShutSpd);

	return S_OK;
}

bool CCameraLogic::OnComboboxBackLightClick( const IArgs& args )
{		
	EmBackLightType emBackLightType;
	u8 byMulti = (u8)(TP_INVALID_INDEX);

	GetBackLightValue(emBackLightType, byMulti);


	u16 nRet = COMIFMGRPTR->CamBackLightCmd( emBackLightType, byMulti );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "背光请求发送失败" );
	}
	return true;
}

HRESULT CCameraLogic::OnCameraBackLightInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "背光设置失败" );
	}

	EmBackLightType emBackLightType;
	LIBDATAMGRPTR->GetCamBackLightType( emBackLightType );
	u8 byMulti = 16;
	if ( emBackLightType == emBLmulti )
	{
		LIBDATAMGRPTR->GetCamBackLightIndex( byMulti );
	}

	SetBackLightValue(emBackLightType, byMulti);


	return S_OK;
}

HRESULT CCameraLogic::OnCameraApertureInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	u8 byAperture;
	LIBDATAMGRPTR->GetCamAperture( byAperture );
	BOOL bRet = static_cast<BOOL>(lparam);

	if ( bRet == FALSE )
	{
		WARNMESSAGE( "光圈设置失败" );
	}

	SetAptValue( byAperture );

	return S_OK;
}

bool CCameraLogic::OnEdtApertureChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}

	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtAperture, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}

	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));
	
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}

	if ( nChar == 0x0d )
	{
		SetFocus(NULL);
	}

	return true;
}

bool CCameraLogic::OnKillFocusEdtAperture( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtAperture, str, m_pWndTree );
	
	SetApertureCmd(str.c_str());

	return true;
}

HRESULT CCameraLogic::OnCameraAutoWBInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	EmWBMode emWBMode;
	LIBDATAMGRPTR->GetCamWBMode( emWBMode );
	BOOL bRet = static_cast<BOOL>(lparam);
	
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "自动曝光设置失败" );
	}
	
	SetAutoWB(emWBMode);
	
	
	return S_OK;
}

bool CCameraLogic::OnEdtRGainChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtRGain, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
	
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));
	
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}
	
	if ( nChar == 0x0d )
	{
		SetFocus(NULL);
	}
	
	return true;
}

bool CCameraLogic::OnKillFocusEdtRGain( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtRGain, str, m_pWndTree );
	
	SetRGainCmd(str.c_str());
	
	return true;
}

void CCameraLogic::SetRGainCmd( CString str )
{
	int n = atoi( str );
	
	if ( n > 255 )
	{
		n = 255;
	}
	else if ( n < 0)
	{
		n = 0;
	}
	
	u16 nRet = COMIFMGRPTR->CamRGainCmd( n );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "RGain调节请求发送失败" );
	}
}

bool CCameraLogic::OnEdtBGainChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtBGain, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
	
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));
	
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}
	
	if ( nChar == 0x0d )
	{
		SetFocus(NULL);
	}
	
	return true;
}

bool CCameraLogic::OnKillFocusEdtBGain( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtBGain, str, m_pWndTree );
	
	SetBGainCmd(str.c_str());
	
	return true;
}

void CCameraLogic::SetBGainCmd( CString str )
{
	int n = atoi( str );
	
	if ( n > 255 )
	{
		n = 255;
	}
	else if ( n < 0)
	{
		n = 0;
	}
	
	u16 nRet = COMIFMGRPTR->CamBGainCmd( n );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "BGain调节请求发送失败" );
	}
}

HRESULT CCameraLogic::OnCameraRGainInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	u16 wRGain = 0;
	LIBDATAMGRPTR->GetCamRGain( wRGain );
	BOOL bRet = static_cast<BOOL>(lparam);
	
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "RGain设置失败" );
	}
	
	SetRGainValue(wRGain);

	
	return S_OK;
}

HRESULT CCameraLogic::OnCameraBGainInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	u16 wBGain = 0;
	LIBDATAMGRPTR->GetCamBGain( wBGain );
	BOOL bRet = static_cast<BOOL>(lparam);
	
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "BGain设置失败" );
	}
	
	SetBGainValue(wBGain);

	
	return S_OK;
}

HRESULT CCameraLogic::OnCameraPicSceneModeInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	EmPicSceMode emPicSceMode;
	LIBDATAMGRPTR->GetCamPicSceneMode(emPicSceMode);
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "模式设置失败" );
	}

	SetPicSceModeValue(emPicSceMode);


	return S_OK;
}

HRESULT CCameraLogic::OnCameraGammaInd( WPARAM wparam, LPARAM lparam )
{
	EmGamma emGamma;
	LIBDATAMGRPTR->GetCamGamma( emGamma );
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "Gamma设置失败" );
	}

	SetGammaValue(emGamma);


	return S_OK;
}

bool CCameraLogic::OnEdtPicSceAptChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtPicSceApt, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
	
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));
	
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}
	
	if ( nChar == 0x0d )
	{
		SetFocus(NULL);
	}
	
	return true;
}

bool CCameraLogic::OnKillFocusEdtPicSceApt( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtPicSceApt, str, m_pWndTree );
	
	SetPicSceAptCmd(str.c_str());
	
	return true;
}

void CCameraLogic::SetPicSceAptCmd( CString str )
{
	int n = atoi( str );
	
	if ( n > MAX_PICSCEAPT_NUMBER )
	{
		n = MAX_PICSCEAPT_NUMBER;
	}
	else if ( n < MIN_PICSCEAPT_NUMBER )
	{
		n = MIN_PICSCEAPT_NUMBER;
	}
	
	u16 nRet = COMIFMGRPTR->CamPicSceAptCmd( n );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "模式光圈调节请求发送失败" );
	}
}

bool CCameraLogic::OnEdtContrastChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtContrast, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
	
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));
	
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}
	
	if ( nChar == 0x0d )
	{
		SetFocus(NULL);
	}
	
	return true;
}

bool CCameraLogic::OnKillFocusEdtContrast( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtContrast, str, m_pWndTree );
	
	SetContrastCmd(str.c_str());
	
	return true;
}

void CCameraLogic::SetContrastCmd( CString str )
{
	int n = atoi( str );
	
	if ( n > 200 )
	{
		n = 200;
	}
	else if ( n < 0 )
	{
		n = 0;
	}
	
	u16 nRet = COMIFMGRPTR->CamContrastCmd( n );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "对比度请求发送失败" );
	}
}

bool CCameraLogic::OnEdtSaturatChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtSaturat, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
	
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));
	
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}
	
	if ( nChar == 0x0d )
	{
		SetFocus(NULL);
	}
	
	return true;
}

bool CCameraLogic::OnKillFocusEdtSaturat( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtSaturat, str, m_pWndTree );
	
	SetSaturatCmd(str.c_str());
	
	return true;
}

void CCameraLogic::SetSaturatCmd( CString str )
{
	int n = atoi( str );
	
	if ( n > 200 )
	{
		n = 200;
	}
	else if ( n < 0 )
	{
		n = 0;
	}
	
	u16 nRet = COMIFMGRPTR->CamSaturatCmd( n );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "饱和度请求发送失败" );
	}
}

bool CCameraLogic::OnEdtHueChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtHue, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
	
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));
	
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}
	
	if ( nChar == 0x0d )
	{
		SetFocus(NULL);
	}
	
	return true;
}

bool CCameraLogic::OnKillFocusEdtHue( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtHue, str, m_pWndTree );
	
	SetHueCmd(str.c_str());
	
	return true;
}

void CCameraLogic::SetHueCmd( CString str )
{
	int n = atoi( str );
	
	if ( n > 200 )
	{
		n = 200;
	}
	else if ( n < 0 )
	{
		n = 0;
	}
	
	u16 nRet = COMIFMGRPTR->CamHueCmd( n );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "色度请求发送失败" );
	}
}

bool CCameraLogic::OnEdtBrightChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return true;
	}
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtBright, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
	
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));
	
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}
	
	if ( nChar == 0x0d )
	{
		SetFocus(NULL);
	}
	
	return true;
}

bool CCameraLogic::OnKillFocusEdtBright( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtBright, str, m_pWndTree );
	SetBrightCmd(str.c_str());
	
	return true;
}

void CCameraLogic::SetBrightCmd( CString str )
{
	BOOL bIsVisible = UIFACTORYMGR_PTR->IsVisible( m_strEdtBright, m_pWndTree );
	if ( !bIsVisible )
	{
		return ;
	}

	int n = atoi( str );
	
	if ( n > 200 )
	{
		n = 200;
	}
	else if ( n < 0 )
	{
		n = 0;
	}
	
	u16 nRet = COMIFMGRPTR->CamBrightCmd( n );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "亮度请求发送失败" );
	}
}

bool CCameraLogic::OnEdtZoomChange( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
      
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &args ));
   
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}

	Value_WindowCaption valueWindowCaption;
	UIFACTORYMGR_PTR->GetPropertyValue( valueWindowCaption, m_strEdtZoom, m_pWndTree );
	
	CString str;
	str = OnlyFloat( valueWindowCaption.strCaption.c_str() );

	UIFACTORYMGR_PTR->SetCaption( m_strEdtZoom, str.GetBuffer(str.GetLength()), m_pWndTree );


	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtZoom, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}

	if ( nChar == 0x0d )	//0x0d表示为\n
	{
		SetZoomCmd(str);


		SetFocus(NULL);
	}

	return true;
}

bool CCameraLogic::OnEdtZoomKillFocus( const IArgs& args )
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtZoom, str, m_pWndTree );
		
	SetZoomCmd(str.c_str());

	return true;
}


HRESULT CCameraLogic::OnCameraPicSceAptInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	u8 byPicSceApt = 0;
	LIBDATAMGRPTR->GetCamPicSceApt( byPicSceApt );
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( _T("模式光圈设置失败") );
	}

	SetPicSceAptValue(byPicSceApt);


	return S_OK;
}

HRESULT CCameraLogic::OnCameraContrastInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}

	u16 wContrast = 0;
	LIBDATAMGRPTR->GetCamContrast( wContrast );
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( _T("对比度设置失败") );
	}

	SetContrastValue(wContrast);


	return S_OK;
}

HRESULT CCameraLogic::OnCameraSaturatInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	u16 wSaturat = 0;
	LIBDATAMGRPTR->GetCamSaturat( wSaturat );
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( _T("饱和度设置失败") );
	}
	
	SetSaturatValue(wSaturat);

	
	return S_OK;
}

HRESULT CCameraLogic::OnCameraHueInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	u16 wHue = 0;
	LIBDATAMGRPTR->GetCamHue( wHue );
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( _T("色度设置失败") );
	}
	
	SetHueValue(wHue);

	
	return S_OK;
}

HRESULT CCameraLogic::OnCameraBrightInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	u16 wBright = 0;
	LIBDATAMGRPTR->GetCamBright( wBright );
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( _T("亮度设置失败") );
	}
	
	SetBrightValue(wBright);

	
	return S_OK;
}

HRESULT CCameraLogic::OnCameraNRStmCleanInd( WPARAM wparam, LPARAM lparam )
{
	EmStmClean emStmClean;
	LIBDATAMGRPTR->GetCamNRStmClean( emStmClean );
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( _T("降噪过滤设置失败") );
	}

	SetNRStmCleanValue(emStmClean);


	return S_OK;
}

HRESULT CCameraLogic::OnCamera3DNRInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	Em3DNR em3DNR;
	LIBDATAMGRPTR->GetCam3DNR( em3DNR );
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "3D DNR设置失败");
	}

	Set3DNRValue(em3DNR);

	
	return S_OK;
}

HRESULT CCameraLogic::OnCameraResetInd( WPARAM wparam, LPARAM lparam )
{
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		CMsgboxDlgLogic::GetSingletonPtr()->Clear();
		WARNMESSAGE( _T("恢复默认设置失败") );
	}
	else
	{

		// 添加保护，防止恢复默认消息回的太快，导致导出的摄像机配置文件不全
		g_wReserProtectID = SetTimer( NULL, 1, 8000, CBCameraTimerFun );


		CMsgboxDlgLogic::GetSingletonPtr()->Clear();
		WARNMESSAGE( _T("恢复默认设置成功") );

		TCnCameraCfg tCnCameraCfg;
		LIBDATAMGRPTR->GetCamCfg( tCnCameraCfg );
		SetCameraCfg( tCnCameraCfg );
	}

	return S_OK;
}

HRESULT CCameraLogic::OnCameraPersetSaveInd( WPARAM wparam, LPARAM lparam )
{
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		TCnCameraCfg tCnCameraCfg;
		LIBDATAMGRPTR->GetCamCfg( tCnCameraCfg );
		if( tCnCameraCfg.emCamType == emCamHD95D )
		{
			SetCursorPos( 710, 530 );//20130326-解决弹出框后还能点击问题
		}
		WARNMESSAGE( _T("预置位保存设置失败") );
	}
	
	return S_OK;
}

void CCameraLogic::SetCameraCfg( TCnCameraCfg tCnCameraCfg )
{
	CString strCaption;
	Value_SwitchState valueSwitchState;
	Value_TransparentComboBoxText valueTransparentComboBoxText;

	//设置摄像机型号
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strStaticCamCategory, str, m_pWndTree );

	switch( tCnCameraCfg.emCamType )
	{
	case emCamHD95D:	
		if ( str != "95D" )
		{
//			UIFACTORYMGR_PTR->SetComboText( m_strComboboxCameraSony, _T("95D"), m_pWndTree );
			UIFACTORYMGR_PTR->SetCaption( m_strStaticCamCategory, _T("95D"), m_pWndTree );
			m_emCamType = emCamHD95D;
			UIFACTORYMGR_PTR->LoadScheme( _T("Schm95D"), m_pWndTree );
		}
		break;
	case emCamSony:
		if ( str != "sony" )
		{
			UIFACTORYMGR_PTR->SetCaption( m_strStaticCamCategory, _T("sony"), m_pWndTree );
			m_emCamType = emCamSony;
			UIFACTORYMGR_PTR->LoadScheme( _T("Schmsony"), m_pWndTree );
		}
		break;
	default:
		break;
	}

	//摄像机名称
	u8 byCameraIndex = 0;
	LIBDATAMGRPTR->GetCamSel( byCameraIndex );
	//byCameraIndex = tCnCameraCfg.byAddr;
	switch ( byCameraIndex )
	{
	case 0:
		{
			strCaption = _T("摄像机1");
			m_byCameraIndx = 0;
			break;
		}
	case 1:
		{
			strCaption = _T("摄像机2");
			m_byCameraIndx = 1;
			break;
		}
	case 2:
		{
			strCaption = _T("摄像机3");
			m_byCameraIndx = 2;
			break;
		}
	default:
		break;
	}
	
	SetCamName(strCaption);

	SetZoomValue( ((float)tCnCameraCfg.wZoom)/100 );
	
	if ( m_emCamType == emCamHD95D)
	{
		//在视野上显示比例
		SetOSDShowValue( tCnCameraCfg.emOSDShow );
		
		//开机调用预置位1
		SetPresetValue( tCnCameraCfg.bUsed );
	}

	//曝光
	SetAutoExp( tCnCameraCfg.emExpMode );
	SetExpGainValue( tCnCameraCfg.emGain );
	SetShutSpdValue( tCnCameraCfg.emShutSpd );
	if ( m_emCamType == emCamHD95D)
	{
		SetBackLightValue( tCnCameraCfg.emBackLightType, tCnCameraCfg.byMulti );		
	}
	SetAptValue( tCnCameraCfg.byApt );

	//白平衡
	SetAutoWB( tCnCameraCfg.emWBMode );
	SetRGainValue( tCnCameraCfg.wRGain );
	SetBGainValue( tCnCameraCfg.wBGain );

	
	if ( m_emCamType == emCamHD95D )
	{
		//模式
		SetPicSceModeValue( tCnCameraCfg.emPicMode );
		SetGammaValue( tCnCameraCfg.emGamma );
		SetPicSceAptValue( tCnCameraCfg.byPicApt );
		
		//图片调节
		SetContrastValue( tCnCameraCfg.wContrast );
		SetSaturatValue( tCnCameraCfg.wSaturat );
		SetHueValue( tCnCameraCfg.wHue );
		SetBrightValue( tCnCameraCfg.wBright );
		
		//降噪
		SetNRStmCleanValue( tCnCameraCfg.emStmClean );
		Set3DNRValue( tCnCameraCfg.em3DNR );
	}
	else
	{	
		//sony降噪
		UIFACTORYMGR_PTR->SetSwitchState( "BtnNR", tCnCameraCfg.bStmClen, m_pWndTree );
		if ( tCnCameraCfg.bStmClen )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmBtnNROn", NULL, "CameraDlg/ComboboxNR" );
			//方案xml里未找到 先注掉
			//UIFACTORYMGR_PTR->LoadScheme( "SchmNROn", m_pWndTree, "ComboboxNR" );
		}
		else
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmBtnNROff", NULL, "CameraDlg/ComboboxNR" );
			//UIFACTORYMGR_PTR->LoadScheme( "SchmNROff", m_pWndTree, "ComboboxNR" );
		}
		String strLevel;
		switch ( tCnCameraCfg.byLevel )
		{
		case 1:
			strLevel = "level 1";
			break;
		case 2:
			strLevel = "level 2";
			break;
		case 3:
			strLevel = "level 3";
			break;
		case 4:
			strLevel = "level 4";
			break;
		case 5:
			strLevel = "level 5";
			break;
		default:
			break;
		}
		UIFACTORYMGR_PTR->SetComboText( "ComboboxNR", strLevel, m_pWndTree );
		//Sony背光调节开关
		UIFACTORYMGR_PTR->SetSwitchState( m_strBtnSwitch3DNR, tCnCameraCfg.bBackLight, m_pWndTree );
	}

	return;
}

void CCameraLogic::GetBackLightValue( EmBackLightType &emBackLightType, u8 &byMulti )
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	Value_TransparentComboBoxText valueTransparentComboBoxText;
	UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, m_strComboboxBackLight, m_pWndTree );
	
	String strComboText = valueTransparentComboBoxText.strComboText;
	if ( strComboText == "关闭" )
	{
		byMulti = 16;
		emBackLightType = emBLOff;
	}
	else if ( strComboText == "multi0" )
	{
		byMulti = 0;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi1" )
	{
		byMulti = 1;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi2" )
	{
		byMulti = 2;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi3" )
	{
		byMulti = 3;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi4" )
	{
		byMulti = 4;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi5" )
	{
		byMulti = 5;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi6" )
	{
		byMulti = 6;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi7" )
	{
		byMulti = 7;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi8" )
	{
		byMulti = 8;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi9" )
	{
		byMulti = 9;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi10" )
	{
		byMulti = 10;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi11" )
	{
		byMulti = 11;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi12" )
	{
		byMulti = 12;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi13" )
	{
		byMulti = 13;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi14" )
	{
		byMulti = 14;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "multi15" )
	{
		byMulti = 15;
		emBackLightType = emBLmulti;
	}
	else if ( strComboText == "center" )
	{
		byMulti = 16;
		emBackLightType = emBLcenter;
	}
	else if ( strComboText == "face detect" )
	{
		byMulti = 16;
		emBackLightType = emBLfacedetect;
	}
}

void CCameraLogic::GetShutSpdValue( EmShutSpd &emShutSpd )
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	
	Value_TransparentComboBoxText valueTransparentComboBoxText;
	if ( m_emCamType == emCamHD95D )
	{
		UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, m_strComboboxShut, m_pWndTree );
	} 
	else
	{
		UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, "ComboboxsonyShut", m_pWndTree );
	}
	
	String strComboText = valueTransparentComboBoxText.strComboText;
	if ( m_emCamType == emCamHD95D )
	{
		if ( strComboText == "1/60" )
		{
			emShutSpd = emShutSpd0;
		}
		else if ( strComboText == "1/100" )
		{
			emShutSpd = emShutSpd1;
		}
		else if ( strComboText == "1/250" )
		{
			emShutSpd = emShutSpd2;
		}
		else if ( strComboText == "1/500" )
		{
			emShutSpd = emShutSpd3;
		}
		else if ( strComboText == "1/1000" )
		{
			emShutSpd = emShutSpd4;
		}
		else if ( strComboText == "1/2000" )
		{
			emShutSpd = emShutSpd5;
		}
		else if ( strComboText == "1/4000" )
		{
			emShutSpd = emShutSpd6;
		}
		else if ( strComboText == "1/10000" )
		{
			emShutSpd = emShutSpd7;
		}
	} 
	else
	{
		if ( strComboText == "1/1" )
		{
			emShutSpd = emShutSpd0;
		}
		else if ( strComboText == "1/2" )
		{
			emShutSpd = emShutSpd1;
		}
		else if ( strComboText == "1/4" )
		{
			emShutSpd = emShutSpd2;
		}
		else if ( strComboText == "1/8" )
		{
			emShutSpd = emShutSpd3;
		}
		else if ( strComboText == "1/15" )
		{
			emShutSpd = emShutSpd4;
		}
		else if ( strComboText == "1/30" )
		{
			emShutSpd = emShutSpd5;
		}
		else if ( strComboText == "1/60" )
		{
			emShutSpd = emShutSpd6;
		}
		else if ( strComboText == "1/90" )
		{
			emShutSpd = emShutSpd7;
		}
		else if ( strComboText == "1/100" )
		{
			emShutSpd = emShutSpd8;
		}
		else if ( strComboText == "1/125" )
		{
			emShutSpd = emShutSpd9;
		}
		else if ( strComboText == "1/180" )
		{
			emShutSpd = emShutSpdA;
		}
		else if ( strComboText == "1/250" )
		{
			emShutSpd = emShutSpdB;
		}
		else if ( strComboText == "1/350" )
		{
			emShutSpd = emShutSpdC;
		}
		else if ( strComboText == "1/500" )
		{
			emShutSpd = emShutSpdD;
		}
		else if ( strComboText == "1/725" )
		{
			emShutSpd = emShutSpdE;
		}
		else if ( strComboText == "1/1000" )
		{
			emShutSpd = emShutSpdF;
		}
		else if ( strComboText == "1/1500" )
		{
			emShutSpd = emShutSpd10;
		}
		else if ( strComboText == "1/2000" )
		{
			emShutSpd = emShutSpd11;
		}
		else if ( strComboText == "1/3000" )
		{
			emShutSpd = emShutSpd12;
		}
		else if ( strComboText == "1/4000" )
		{
			emShutSpd = emShutSpd13;
		}
		else if ( strComboText == "1/6000" )
		{
			emShutSpd = emShutSpd14;
		}
		else if ( strComboText == "1/10000" )
		{
			emShutSpd = emShutSpd15;
		}
	}
}

void CCameraLogic::SetShutSpdValue( EmShutSpd emShutSpd )
{
	Value_TransparentComboBoxText valueTransparentComboBoxText;

	switch ( emShutSpd )
	{
	case emShutSpd0:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "1/60"; 
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "1/1"; 
			}	
			break;
		}
	case emShutSpd1:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "1/100"; 
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "1/2"; 
			}		
			break;
		}
	case emShutSpd2:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "1/250"; 
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "1/4"; 
			}
			break;
		}
	case emShutSpd3:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "1/500"; 
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "1/8"; 
			}
			break;
		}
	case emShutSpd4:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "1/1000"; 
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "1/15"; 
			}
			break;
		}
	case emShutSpd5:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "1/2000"; 
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "1/30"; 
			}
			break;
		}
	case emShutSpd6:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "1/4000"; 
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "1/60"; 
			}
			break;
		}
	case emShutSpd7:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "1/10000";
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "1/90";
			}
			break;
		}
	case emShutSpd8:
		{
			if ( m_emCamType == emCamSony )
			{
				valueTransparentComboBoxText.strComboText = "1/100";
			}
			break;
		}
	case emShutSpd9:
		{
			if ( m_emCamType == emCamSony )
			{
				valueTransparentComboBoxText.strComboText = "1/125";
			}
			break;
		}
	case emShutSpdA:
		{
			if ( m_emCamType == emCamSony )
			{
				valueTransparentComboBoxText.strComboText = "1/180";
			}
			break;
		}
	case emShutSpdB:
		{
			if ( m_emCamType == emCamSony )
			{
				valueTransparentComboBoxText.strComboText = "1/250";
			}
			break;
		}
	case emShutSpdC:
		{
			if ( m_emCamType == emCamSony )
			{
				valueTransparentComboBoxText.strComboText = "1/350";
			}
			break;
		}
	case emShutSpdD:
		{
			if ( m_emCamType == emCamSony )
			{
				valueTransparentComboBoxText.strComboText = "1/500";
			}
			break;
		}
	case emShutSpdE:
		{
			if ( m_emCamType == emCamSony )
			{
				valueTransparentComboBoxText.strComboText = "1/725";
			}
			break;
		}
	case emShutSpdF:
		{
			if ( m_emCamType == emCamSony )
			{
				valueTransparentComboBoxText.strComboText = "1/1000";
			}
			break;
		}
	case emShutSpd10:
		{
			if ( m_emCamType == emCamSony )
			{
				valueTransparentComboBoxText.strComboText = "1/1500";
			}
			break;
		}
	case emShutSpd11:
		{
			if ( m_emCamType == emCamSony )
			{
				valueTransparentComboBoxText.strComboText = "1/2000";
			}
			break;
		}
	case emShutSpd12:
		{
			if ( m_emCamType == emCamSony )
			{
				valueTransparentComboBoxText.strComboText = "1/3000";
			}
			break;
		}
	case emShutSpd13:
		{
			if ( m_emCamType == emCamSony )
			{
				valueTransparentComboBoxText.strComboText = "1/4000";
			}
			break;
		}
	case emShutSpd14:
		{
			if ( m_emCamType == emCamSony )
			{
				valueTransparentComboBoxText.strComboText = "1/6000";
			}
			break;
		}
	case emShutSpd15:
		{
			if ( m_emCamType == emCamSony )
			{
				valueTransparentComboBoxText.strComboText = "1/10000";
			}
			break;
		}
	default:
		break;
	}
	
	if ( m_emCamType == emCamHD95D )
	{
		UIFACTORYMGR_PTR->SetPropertyValue( valueTransparentComboBoxText, m_strComboboxShut, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->SetPropertyValue( valueTransparentComboBoxText, "ComboboxsonyShut", m_pWndTree );
	}
}

void CCameraLogic::GetGainValue( EmGain &emGain )
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	Value_TransparentComboBoxText valueTransparentComboBoxText;
	if ( m_emCamType == emCamHD95D )
	{
		UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, m_strComboboxExposureGain, m_pWndTree );
	} 
	else
	{
		UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, "ComboboxsonyExposureGain", m_pWndTree );
	}
	
	String strComboText = valueTransparentComboBoxText.strComboText;
	if ( m_emCamType == emCamHD95D )
	{
		if ( strComboText == "0dB" )
		{
			emGain = em0dB;
		}
		else if ( strComboText == "3dB" )
		{
			emGain = em3dB;
		}
		else if ( strComboText == "6dB" )
		{
			emGain = em6dB;
		}
		else if ( strComboText == "9dB" )
		{
			emGain = em9dB;
		}
		else if ( strComboText == "12dB" )
		{
			emGain = em12dB;
		}
		else if ( strComboText == "15dB" )
		{
			emGain = em15dB;
		}
		else if ( strComboText == "18dB" )
		{
			emGain = em18dB;
		}
		else if ( strComboText == "21dB" )
		{
			emGain = em21dB;
		}
		else if ( strComboText == "24dB" )
		{
			emGain = em24dB;
		}
		else if ( strComboText == "27dB" )
		{
			emGain = em27dB;
		}
		else if ( strComboText == "30dB" )
		{
			emGain = em30dB;
		}
		else if ( strComboText == "33dB" )
		{
			emGain = em33dB;
		}
		else if ( strComboText == "36dB" )
		{
			emGain = em36dB;
		}
		else if ( strComboText == "39dB" )
		{
			emGain = em39dB;
		}
		else if ( strComboText == "42dB" )
		{
			emGain = em42dB;
		}
	} 
	else
	{
		if ( strComboText == "0" )
		{
			emGain = em0dB;
		}
		else if ( strComboText == "2" )
		{
			emGain = em3dB;
		}
		else if ( strComboText == "4" )
		{
			emGain = em6dB;
		}
		else if ( strComboText == "6" )
		{
			emGain = em9dB;
		}
		else if ( strComboText == "8" )
		{
			emGain = em12dB;
		}
		else if ( strComboText == "10" )
		{
			emGain = em15dB;
		}
		else if ( strComboText == "12" )
		{
			emGain = em18dB;
		}
		else if ( strComboText == "14" )
		{
			emGain = em21dB;
		}
		else if ( strComboText == "16" )
		{
			emGain = em24dB;
		}
		else if ( strComboText == "18" )
		{
			emGain = em27dB;
		}
		else if ( strComboText == "20" )
		{
			emGain = em30dB;
		}
		else if ( strComboText == "22" )
		{
			emGain = em33dB;
		}
		else if ( strComboText == "24" )
		{
			emGain = em36dB;
		}
		else if ( strComboText == "26" )
		{
			emGain = em39dB;
		}
		else if ( strComboText == "28" )
		{
			emGain = em42dB;
		}
	}
}

void CCameraLogic::SetExpGainValue( EmGain emGain )
{
	Value_TransparentComboBoxText valueTransparentComboBoxText;

	switch ( emGain )
	{
	case em0dB:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "0dB";
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "0";
			}		
			break;
		}
	case em3dB:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "3dB";
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "2";
			}
			break;
		}
	case em6dB:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "6dB";
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "4";
			}
			break;
		}
	case em9dB:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "9dB";
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "6";
			}
			break;
		}
	case em12dB:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "12dB";
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "8";
			}
			break;
		}
	case em15dB:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "15dB";
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "10";
			}
			break;
		}
	case em18dB:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "18dB";
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "12";
			}
			break;
		}
	case em21dB:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "21dB";
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "14";
			}
			break;
		}
	case em24dB:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "24dB";
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "16";
			}
			break;
		}
	case em27dB:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "27dB";
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "18";
			}
			break;
		}
	case em30dB:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "30dB";
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "20";
			}
			break;
		}
	case em33dB:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "33dB";
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "22";
			}
			break;
		}
	case em36dB:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "36dB";
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "24";
			}
			break;
		}
	case em39dB:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "39dB";
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "26";
			}
			break;
		}
	case em42dB:
		{
			if ( m_emCamType == emCamHD95D )
			{
				valueTransparentComboBoxText.strComboText = "42dB";
			} 
			else
			{
				valueTransparentComboBoxText.strComboText = "28";
			}
			break;
		}
	default:
		break;
	}

	if ( m_emCamType == emCamHD95D )
	{
		UIFACTORYMGR_PTR->SetPropertyValue( valueTransparentComboBoxText, m_strComboboxExposureGain, m_pWndTree );
	}	
	else
	{
		UIFACTORYMGR_PTR->SetPropertyValue( valueTransparentComboBoxText, "ComboboxsonyExposureGain", m_pWndTree );
	}
}

void CCameraLogic::SetBackLightValue( EmBackLightType emBackLightType, u8 byMulti )
{
	Value_TransparentComboBoxText valueTransparentComboBoxText;
	switch ( emBackLightType )
	{
	case emBLOff:
		{
			valueTransparentComboBoxText.strComboText = "关闭";
			break;
		}
	case emBLmulti:
		{
			switch ( byMulti )
			{
			case 0:
				{
					valueTransparentComboBoxText.strComboText = "multi0";
					break;
				}
			case 1:
				{
					valueTransparentComboBoxText.strComboText = "multi1";
					break;
				}
			case 2:
				{
					valueTransparentComboBoxText.strComboText = "multi2";
					break;
				}
			case 3:
				{
					valueTransparentComboBoxText.strComboText = "multi3";
					break;
				}
			case 4:
				{
					valueTransparentComboBoxText.strComboText = "multi4";
					break;
				}
			case 5:
				{
					valueTransparentComboBoxText.strComboText = "multi5";
					break;
				}
			case 6:
				{
					valueTransparentComboBoxText.strComboText = "multi6";
					break;
				}
			case 7:
				{
					valueTransparentComboBoxText.strComboText = "multi7";
					break;
				}
			case 8:
				{
					valueTransparentComboBoxText.strComboText = "multi8";
					break;
				}
			case 9:
				{
					valueTransparentComboBoxText.strComboText = "multi9";
					break;
				}
			case 10:
				{
					valueTransparentComboBoxText.strComboText = "multi10";
					break;
				}
			case 11:
				{
					valueTransparentComboBoxText.strComboText = "multi11";
					break;
				}
			case 12:
				{
					valueTransparentComboBoxText.strComboText = "multi12";
					break;
				}
			case 13:
				{
					valueTransparentComboBoxText.strComboText = "multi13";
					break;
				}
			case 14:
				{
					valueTransparentComboBoxText.strComboText = "multi14";
					break;
				}
			case 15:
				{
					valueTransparentComboBoxText.strComboText = "multi15";
					break;
				}
			default:
				break;
			}
			
			break;
		}
	case emBLcenter:
		{
			valueTransparentComboBoxText.strComboText = "center";
			break;
		}
	case emBLfacedetect:
		{
			valueTransparentComboBoxText.strComboText = "face detect";
			break;
		}
	default:
		break;
	}
	UIFACTORYMGR_PTR->SetPropertyValue( valueTransparentComboBoxText, m_strComboboxBackLight, m_pWndTree );
}

void CCameraLogic::SetAutoWB( EmWBMode emWBMode )
{
	if ( emWBMode == emWBAuto )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchAutoWB", m_pWndTree );
	}
	else if ( emWBMode == emWBManual )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchManuelWB", m_pWndTree );
	}
	else
	{
		
	}
}

void CCameraLogic::SetAutoExp( EmExpMode emExpMode )
{
	if ( emExpMode == emExpAuto )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchAutoExp", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchManuelExp", m_pWndTree );
	}
}

void CCameraLogic::SetCamName( CString strCaption )
{
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxCamera, (LPCTSTR)strCaption, m_pWndTree );
}

void CCameraLogic::SetOSDShowValue( EmOSDShow emOSDShow )
{
	Value_SwitchState valueSwitchState;
	if ( emOSDShow == emOSDOn )
	{
		valueSwitchState.bState = true;
	}
	else
	{
		valueSwitchState.bState = false;
	}
	
	UIFACTORYMGR_PTR->SetPropertyValue( valueSwitchState, m_strBtnSwitchVisualField, m_pWndTree );
}

void CCameraLogic::SetPresetValue( BOOL bUsed )
{
	Value_SwitchState valueSwitchState;
	valueSwitchState.bState = bUsed;
	UIFACTORYMGR_PTR->SetPropertyValue( valueSwitchState, m_strBtnSwitchPersetMove, m_pWndTree );
}

void CCameraLogic::SetAptValue( u8 byApt )
{
	if ( m_emCamType == emCamHD95D )
	{
		Value_CSliderCtrlPos valueCSliderCtrlPos;
		valueCSliderCtrlPos.nPos = byApt;
		UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderAperture, m_pWndTree );
		
		CString strCaption;
		strCaption.Format( "%d", byApt );
		UIFACTORYMGR_PTR->SetCaption( m_strEdtAperture, (LPCTSTR)strCaption, m_pWndTree );
		
		Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtAperture, m_pWndTree );
		if ( pWnd )
		{
			(( CEdit *) pWnd)->SetSel( -1 );
		}
	} 
	else
	{
		String strCaption;
		EmSonyIris emSonyIris = (EmSonyIris)byApt;
		switch( emSonyIris )
		{
		case emIrisOFF:
			strCaption = "Close";
			break;
		case emIrisF9_6:
			strCaption = "F9.6";
			break;
		case emIrisF8:
			strCaption = "F8";
			break;
		case emIrisF6_8:
			strCaption = "F6.8";
			break;
		case emIrisF5_6:
			strCaption = "F5.6";
			break;
		case emIrisF4_8:
			strCaption = "F4.8";
			break;
		case emIrisF4:
			strCaption = "F4";
			break;
		case emIrisF3_4:
			strCaption = "F3.4";
			break;
		case emIrisF2_8:
			strCaption = "F2.8";
			break;
		case emIrisF2_4:
			strCaption = "F2.4";
			break;
		case emIrisF2:
			strCaption = "F2";
			break;
		case emIrisF1_8:
			strCaption = "F1.8";
			break;
		}
		UIFACTORYMGR_PTR->SetComboText( "ComboboxAperture", strCaption, m_pWndTree );
	}
}

void CCameraLogic::SetRGainValue( u16 wRGain )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = wRGain;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderRGain, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", wRGain );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtRGain, m_pWndTree );

/*	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtRGain, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}*/
}

void CCameraLogic::SetBGainValue( u16 wBGain )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = wBGain;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderBGain, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", wBGain );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtBGain, m_pWndTree );

/*	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtBGain, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}*/
}

void CCameraLogic::SetPicSceModeValue( EmPicSceMode emPicSceMode )
{
	switch ( emPicSceMode )
	{
	case emLamp:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchPicSceneModeLamp"), m_pWndTree );
			break;
		}
	case emSun:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchPicSceneModeSun"), m_pWndTree );
			break;
		}
	case emManuel:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchPicSceneModeManuel"), m_pWndTree );
			break;
		}
	default:
		break;
	}
}

void CCameraLogic::SetGammaValue( EmGamma emGamma )
{
	switch ( emGamma )
	{
	case emGammaOn:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchGammaOn"), m_pWndTree );
			break;
		}
	case emGammaOff:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchGammaOff"), m_pWndTree );
			break;
		}
	case emSmart1:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchGammaSmart1"), m_pWndTree );
			break;
		}
	case emSmart2:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchGammaSmart2"), m_pWndTree );
			break;
		}
	default:
		break;
	}
}

void CCameraLogic::SetPicSceAptValue( u8 byPicSceApt )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = byPicSceApt;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderPicSceApt, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", byPicSceApt );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtPicSceApt, m_pWndTree );

/*	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtPicSceApt, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}*/
}

void CCameraLogic::SetContrastValue( u16 wContrast )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = wContrast;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderContrast, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", wContrast );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtContrast, m_pWndTree );

/*	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtContrast, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}*/
}

void CCameraLogic::SetSaturatValue( u16 wSaturat )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = wSaturat;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderSaturat, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", wSaturat );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtSaturat, m_pWndTree );

	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtSaturat, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
}

void CCameraLogic::SetHueValue( u16 wHue )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = wHue;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderHue, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", wHue );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	//UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtHue, m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strEdtHue, strCaption.GetBuffer(strCaption.GetLength()), m_pWndTree );

/*	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtHue, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}*/
}

void CCameraLogic::SetBrightValue( u16 wBright )
{
	Value_CSliderCtrlPos valueCSliderCtrlPos;
	valueCSliderCtrlPos.nPos = wBright;
	UIFACTORYMGR_PTR->SetPropertyValue( valueCSliderCtrlPos, m_strSliderBright, m_pWndTree );
	
	CString strCaption;
	strCaption.Format( "%d", wBright );
	Value_WindowCaption valueWindowCaption;
	valueWindowCaption.strCaption = strCaption;
	UIFACTORYMGR_PTR->SetPropertyValue( valueWindowCaption, m_strEdtBright, m_pWndTree );

/*	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtBright, m_pWndTree );
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}*/
}

void CCameraLogic::SetNRStmCleanValue( EmStmClean emStmClean )
{
	switch ( emStmClean )
	{
	case emNRoff:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchNROff"), m_pWndTree );
			break;
		}
	case emNRlow:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchNROffLow"), m_pWndTree );
			break;
		}
	case emNRmid:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchNROffMid"), m_pWndTree );
			break;
		}
	case emNRhigh:
		{
			UIFACTORYMGR_PTR->LoadScheme( _T("SchNROffHigh"), m_pWndTree );
			break;
		}
	default:
		break;
	}
}

void CCameraLogic::Set3DNRValue( Em3DNR em3DNR )
{
	Value_SwitchState valueSwitchState;
	if ( em3DNR == em3DNROn )
	{
		valueSwitchState.bState = true;
	}
	else
	{
		valueSwitchState.bState = false;
	}
	
	UIFACTORYMGR_PTR->SetPropertyValue( valueSwitchState, m_strBtnSwitch3DNR, m_pWndTree );
}

float CCameraLogic::StringToFloatTwo( CString str )
{
	float f = 0;
	f = atof((LPCTSTR)str);
	char strRet[10] = {0};
	sprintf(strRet,"%.2f",f);
	f = atof(strRet);
	return f;
}

CString CCameraLogic::OnlyFloat( CString str )
{
	// 只允许输数据
	int nStringLength = str.GetLength();
	int nDotCount = 0;
	// 点字符不能多于1个
	int nIndex = 0;
	for ( ; nIndex < nStringLength; nIndex++ )
	{
		if ( str[ nIndex ] == '.' )
		{
			nDotCount++;
			if ( nDotCount > 1 )
			{
				CString csTmp;
				csTmp = str.Left( nIndex );
				csTmp += str.Right( str.GetLength() - nIndex - 1 );
				//csRadius = csRadius.Left( nIndex + 1 ) + csRadius.Right( nStringLength - ( nIndex + 1 ) - 1 );
				//GetDlgItem( IDC_EDIT_AREA_S )->SetWindowText( csTmp );
				return csTmp;
			}
		}
	}
	
	// 不允许输入数字和点以外的字符
	nIndex = 0;
	for ( ; nIndex < nStringLength; nIndex++ )
	{
		if ( str[ nIndex ] != '.' && ( str[ nIndex ] > '9' || str[ nIndex ] < '0' ) )
		{
			str = str.Left( nIndex ) + str.Right( str.GetLength() - nIndex - 1 );
			//GetDlgItem( IDC_EDIT_AREA_S )->SetWindowText( csTmp );
			return str;
		}
	}

	return str;
}

HRESULT CCameraLogic::OnSetCameraZoomInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	u16 wZoom = 0;
	LIBDATAMGRPTR->GetCamZoom( wZoom );
	BOOL bRet = static_cast<BOOL>(lparam);
	if ( bRet == FALSE )
	{
		WARNMESSAGE( "zoom设置失败");
	}
	
	SetZoomValue((float)wZoom/100);

	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strEdtZoom, m_pWndTree );
	if ( pWnd )
	{
		pWnd->ShowWindow(SW_HIDE);
		pWnd->ShowWindow(SW_SHOW);
	}
	
	return S_OK;
}

void CCameraLogic::SetZoomValue( float fZoom )
{
	CString strCaption;
	strCaption.Format( "%.2f", fZoom );
	UIFACTORYMGR_PTR->SetCaption( m_strEdtZoom, strCaption.GetBuffer(strCaption.GetLength()), m_pWndTree );
}

void CCameraLogic::SetZoomCmd( CString str )
{
	float fZoom = StringToFloatTwo( str );
	
	if ( fZoom > 10 )
	{
		fZoom = 10.00;
	}
	else if ( fZoom < 1)
	{
		fZoom = 1.00;
	}
	
	u16 wZoom = (fZoom+1.0e-6)*100;
	u16 nRet = COMIFMGRPTR->SetCamZoomCmd( wZoom );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "zoom请求发送失败" );
	}
}

void CCameraLogic::SetApertureCmd( CString str )
{
	int nAperture = atoi( str );
	
	if ( nAperture > 100 )
	{
		nAperture = 100;
	}
	else if ( nAperture < 0)
	{
		nAperture = 0;
	}
	
	u16 nRet = COMIFMGRPTR->CamAperture( nAperture );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "光圈调节请求发送失败" );
	}
}

HRESULT CCameraLogic::OnCameraPowerOnNty( WPARAM wparam, LPARAM lparam )
{
	if ( NULL == m_pWndTree )
	{
		return S_FALSE;
	}

	m_bLoginByOther = static_cast<BOOL>(lparam);
	m_bIsCameraPowerOn = true;

	WARNMESSAGE( "摄像机已上电，硬件需要两分钟才能操作 " );

	KillTimer(NULL, g_wCameraTimerID);
	g_wCameraTimerID = SetTimer( NULL, 1, 120000, CBCameraTimerFun );

	UIFACTORYMGR_PTR->LoadScheme( "SchmEnable", m_pWndTree );
	
	return S_OK;
}

// VOID CALLBACK CBCameraTimerFun( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
// {  
// 	KillTimer(NULL, g_wCameraTimerID);
// 	CAMERALOGICRPTR->ResetNormal();
// }

void CCameraLogic::ResetNormal()
{
	if ( NULL == m_pWndTree )
	{
		return;
	}

	if ( m_bIsCameraPowerOn )
	{
		m_bIsCameraPowerOn = false;
		UIFACTORYMGR_PTR->LoadScheme( "SchmNormal", m_pWndTree );
	}
}

bool CCameraLogic::OnCameraClick( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
		
	Value_TransparentComboBoxText valueTransparentComboBoxText;
	UIFACTORYMGR_PTR->GetPropertyValue( valueTransparentComboBoxText, m_strStaticCamCategory, m_pWndTree );
	
	String strComboText = valueTransparentComboBoxText.strComboText;
	if ( strComboText == "95D" )
	{
		m_emCamType = emCamHD95D;
		UIFACTORYMGR_PTR->LoadScheme( _T("Schm95D"), m_pWndTree );
	}
	else if ( strComboText == "sony" )
	{
		m_emCamType = emCamSony;
		UIFACTORYMGR_PTR->LoadScheme( _T("Schmsony"), m_pWndTree );
	}

	u16 nRet = COMIFMGRPTR->SetCamTypeCmd( m_emCamType );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "选择摄像机类型请求发送失败" );
	}
	
	return true;
}

void CCameraLogic::GetSonyIrisValue( EmSonyIris& emSonyIris )
{
	String strAperture;
	UIFACTORYMGR_PTR->GetComboText( "ComboboxAperture", strAperture, m_pWndTree );
	if ( strAperture == "Close" )
	{
		emSonyIris = emIrisOFF;
	}
	else if ( strAperture == "F9.6" )
	{
		emSonyIris = emIrisF9_6;
	}
	else if ( strAperture == "F8" )
	{
		emSonyIris = emIrisF8;
	}
	else if ( strAperture == "F6.8" )
	{
		emSonyIris = emIrisF6_8;
	}
	else if ( strAperture == "F5.6" )
	{
		emSonyIris = emIrisF5_6;
	}
	else if ( strAperture == "F4.8" )
	{
		emSonyIris = emIrisF4_8;
	}
	else if ( strAperture == "F4" )
	{
		emSonyIris = emIrisF4;
	}
	else if ( strAperture == "F3.4" )
	{
		emSonyIris = emIrisF3_4;
	}
	else if ( strAperture == "F2.8" )
	{
		emSonyIris = emIrisF2_8;
	}
	else if ( strAperture == "F2.4" )
	{
		emSonyIris = emIrisF2_4;
	}
	else if ( strAperture == "F2" )
	{
		emSonyIris = emIrisF2;
	}
	else if ( strAperture == "F1.8" )
	{
		emSonyIris = emIrisF1_8;
	}	
}

bool CCameraLogic::OnComboboxApertureClick( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	EmSonyIris emSonyIris;
	GetSonyIrisValue( emSonyIris );

	u8 byAperture = (u8)emSonyIris;
	u8 byApertureInLib = 0;
	LIBDATAMGRPTR->GetCamAperture( byApertureInLib );
	if ( emSonyIris == byApertureInLib )
	{
		return true;
	}
	
	u16 nRet = COMIFMGRPTR->CamAperture( byAperture );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "sony光圈调节请求发送失败" );
	}
	
	return true;
}

bool CCameraLogic::OnBtnSwitchNRClick( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	Value_SwitchState valueSwitchState;
	UIFACTORYMGR_PTR->GetPropertyValue( valueSwitchState, "BtnNR", m_pWndTree );
	
	u8 bylevel = 0;
	GetStmClenValue(bylevel);
	if ( valueSwitchState.bState )
	{
		//直接找到拥有该方案的窗口,然后改变窗口属性--适用于响应单个窗口
		UIFACTORYMGR_PTR->LoadScheme( "SchmBtnNROn", NULL, "CameraDlg/ComboboxNR" );
		//在m_pWndTree(cameraDlg.xml)中查找,采用遍历的方式找到拥有该方案的所有窗口,然后改变拥有该方案的属性
		//UIFACTORYMGR_PTR->LoadScheme( "SchmBtnNROn", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmBtnNROff", NULL, "CameraDlg/ComboboxNR" );
	}
	
	u16 nRet = COMIFMGRPTR->SonyStmClenCmd( valueSwitchState.bState, bylevel );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "sony降噪请求发送失败" );
	}
	
	return true;
}

void CCameraLogic::GetStmClenValue( u8& bylevel )
{
	String strLevel;
	UIFACTORYMGR_PTR->GetComboText( "ComboboxNR", strLevel, m_pWndTree );
	if ( strLevel == "level 1" )
	{
		bylevel = 1;
	} 
	else if ( strLevel == "level 2" )
	{
		bylevel = 2;
	}
	else if ( strLevel == "level 3" )
	{
		bylevel = 3;
	}
	else if ( strLevel == "level 4" )
	{
		bylevel = 4;
	}
	else if ( strLevel == "level 5" )
	{
		bylevel = 5;
	}	
}

bool CCameraLogic::OnComboboxNRClick( const IArgs& args )
{
	u8 bylevel;
	GetStmClenValue( bylevel );
	
	u16 nRet = COMIFMGRPTR->SonyStmClenCmd( TRUE, bylevel );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "sony降噪请求发送失败" );
	}
	
	return true;
}

bool CCameraLogic::OnBtnSwitchsonyBLClick( const IArgs& args )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}
	
	Value_SwitchState valueSwitchState;
	UIFACTORYMGR_PTR->GetPropertyValue( valueSwitchState, m_strBtnSwitch3DNR, m_pWndTree );
	
	u16 nRet = COMIFMGRPTR->SonyBackLightCmd( valueSwitchState.bState );
	if ( nRet != NO_ERROR )
	{
		WARNMESSAGE( "sony背光调节请求发送失败" );
	}
                                              
	return true;
}

