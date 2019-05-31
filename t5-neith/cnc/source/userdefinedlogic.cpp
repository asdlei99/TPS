#include "StdAfx.h"
#include "userdefinedlogic.h"
#include "messageboxlogic.h"
#include "calendarlogic.h"
#include "confmsglogic.h"
#include "mainframelogic.h"
#include "loginlogic.h"

template<> CUserDefinedLogic* Singleton<CUserDefinedLogic>::ms_pSingleton  = NULL;

#define LOGPATH    _T("/usr/kdvlog/log/")
#define MAX_SYSLOG_NUM   3

APP_BEGIN_MSG_MAP(CUserDefinedLogic,CNotifyUIImpl)
	MSG_CREATEWINDOW(_T("RegServiceLayout"), OnCreate)
	MSG_INIWINDOW(_T("RegServiceLayout"), OnInit)

	MSG_CLICK(_T("BtnBack"), OnBtnBack)
	MSG_CLICK(_T("BtnExit"), OnBtnExit)
	MSG_CLICK(_T("BtnDownloadSysLog"), OnBtnDownloadLog)
	MSG_CLICK(_T("BtnOk"), OnBtnOk)
	MSG_CLICK(_T("BtnFixOrCancel"), OnBtnFixOrCancel)
	MSG_CLICK(_T("BtnNoticeBack"), OnBtnCancelDownload)
	
	MSG_CLICK(_T("BtnHMinus"), OnBtnHMinus)
	MSG_CLICK(_T("BtnHAdd"), OnBtnHAdd)
	MSG_CLICK(_T("BtnMMinus"), OnBtnMMinus)
	MSG_CLICK(_T("BtnMAdd"), OnBtnMAdd)
	MSG_CLICK(_T("BtnSMinus"), OnBtnSMinus)
	MSG_CLICK(_T("BtnSAdd"), OnBtnSAdd)
	MSG_CLICK(_T("BtnDateSet"), OnBtnDateSet)

    MSG_CLICK(_T("BtnUnLockAllUser"), OnBtnUnLockAllUser)

	MSG_SELECTCHANGE(_T("CheckIsPWEpochUpdate"), OnCheckIsPWEpochUpdate)
	MSG_SELECTCHANGE(_T("CheckIsSysStandby"), OnCheckIsSysStandby)
	MSG_SELECTCHANGE(_T("CheckTimeSynchro"), OnCheckTimeSynchro)

	USER_MSG( WM_CNC_LOGLOADPROGRESS, OnDownloadProgress )
	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)
	USER_MSG(UI_CNS_SLEEPINFO_NOTIFY,OnSleepInfoNotify)

	USER_MSG(UI_CNC_CALENDARDATE_SET,OnCalendarDateSel)
	USER_MSG(UI_CNS_SYSTIME_RSP,OnUpdateTime)
    USER_MSG(WM_DUI_EDITSETFOCUS, OnEditSetFocus)

	USER_MSG(UI_CNC_CNSYSTIMETOCNC_NTY, OnCnSysTimeToCnc)
	//可能修改了自己的密码
	USER_MSG(UI_UMS_REFRESH_USER_LIST,OnChangeUserInfo)

	//密码周期更新
	USER_MSG(UI_CNTPADPWUPDATE_NTY, OnCnPasswordUpdateNty)
	USER_MSG(UI_CNTPADPWUPDATE_IND, OnChangePasswordUpdateInfo)
    //超级管理员通知
    USER_MSG(UI_SUPERADMIN_NTY, OnSuperadminNty)
    //ftp开启通知
    USER_MSG(UI_CNSETFTPRSP, OnSetCnFtpRsp)

APP_END_MSG_MAP()

const String CUserDefinedLogic::m_strBtnFixOrCancel = _T("BtnFixOrCancel");
const String CUserDefinedLogic::m_strBtnOk = _T("BtnOk");
//const String CUserDefinedLogic::m_strEdtOldPassword = _T("edtOldPassword");
//const String CUserDefinedLogic::m_strEdtNewPassword = _T("edtNewPassword");
//const String CUserDefinedLogic::m_strEdtCheckPassword = _T("edtCheckPassword");
const String CUserDefinedLogic::m_strEdtLockPassword = _T("edtLockPassword");
const String CUserDefinedLogic::m_strComboPWEpochUpdate = _T("ComboPWEpochUpdate");
const String CUserDefinedLogic::m_strEdtStandbyTime = _T("edtStandbyTime");
const String CUserDefinedLogic::m_strCheckIsSysStandby = _T("CheckIsSysStandby");

CUserDefinedLogic::CUserDefinedLogic(void):m_bCouldUpdateTime(TRUE),m_bIsTimeSynchro(FALSE)
{
	m_bIsFix = false;
	m_bIsSysStandby = false;
	m_strLogFolderPath = _T("");
	m_wLogId = 0;
    m_bWaitFtpDownLog = false;
}


CUserDefinedLogic::~CUserDefinedLogic(void)
{
}

bool CUserDefinedLogic::OnCreate( TNotifyUI& msg )
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

bool CUserDefinedLogic::OnInit( TNotifyUI& msg )
{
	CComboUI* pComboEx = (CComboUI*)ICncCommonOp::FindControl( m_pm, _T("ComboPWEpochUpdate") );
	if ( pComboEx != NULL )
	{	
		CListLabelElementUI *pListLabelElement1 = (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
		pListLabelElement1->SetText(_T("1个月"));
		pComboEx->Add(pListLabelElement1);

		CListLabelElementUI *pListLabelElement2 = (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
		pListLabelElement2->SetText(_T("2个月"));
		pComboEx->Add(pListLabelElement2);

		CListLabelElementUI *pListLabelElement3 = (CListLabelElementUI*)CONTROLFACTORY()->GetControl( _T("ComboItem") );
		pListLabelElement3->SetText(_T("3个月"));
		pComboEx->Add(pListLabelElement3);
	}

	UpdateSysTime();
	UpdateStandbyTime();
	ComInterface->GetSysSleepInfo( m_tCenDevSleepInfo );

	ICncCommonOp::ShowControl(true, m_pm, _T("LbProcess"));
	ICncCommonOp::SetControlBkImg(_T("res//public//download.png"),m_pm,_T("lbStatePic"));
	ICncCommonOp::SetControlText(_T("正在下载，请稍后"),m_pm,_T("LabelTip"));
	ICncCommonOp::ShowControl( false, m_pm, _T("PageNotice") );

	CString strIniPath = CMainFrameLogic::GetSingletonPtr()->GetIniFilePath();
	TCHAR tchSysName[MAX_NAME_LEN]={0};
	GetPrivateProfileString(_T("SysNameInfo"),_T("name"), _T("网呈会场控制台"),tchSysName, MAX_NAME_LEN, strIniPath);

	ICncCommonOp::SetControlText(tchSysName, m_pm, _T("lbSysName"));
	ICncCommonOp::SetControlText(tchSysName, m_pm, _T("edtSysName"));

	setFixEnable(false);

	return true;
}


bool CUserDefinedLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_bIsFix = false;
	m_wLogId = 0;
    m_bWaitFtpDownLog = false;
	setFixEnable(m_bIsFix);
	ICncCommonOp::ShowControl(false,m_pm,_T("BtnOk"));
	ICncCommonOp::SetControlText(_T("修 改"),m_pm,_T("BtnFixOrCancel"));		
	//清空密码项
// 	ICncCommonOp::SetControlText(_T(""),m_pm,m_strEdtOldPassword.c_str());	
// 	ICncCommonOp::SetControlText(_T(""),m_pm,m_strEdtNewPassword.c_str());	
// 	ICncCommonOp::SetControlText(_T(""),m_pm,m_strEdtCheckPassword.c_str());
	ICncCommonOp::ShowControl( false, m_pm, _T("PageNotice") );
	return true;
}

bool CUserDefinedLogic::OnBtnOk( TNotifyUI& msg )
{
	if ( /*!savePassWord(true) ||*/!saveSysName(true) || !saveLockPassWord(true) || !saveSysTime(true) || !(savePasswordUpdateInfo()) || !(saveSuperadminInfo(true)))
	{
		return false;
	}
	
	m_bIsFix = false;
	ICncCommonOp::ShowControl(false,m_pm,_T("BtnOk"));
	ICncCommonOp::SetControlText(_T("修 改"),m_pm,_T("BtnFixOrCancel"));	
	setFixEnable(m_bIsFix);

	return true;
}

bool CUserDefinedLogic::OnBtnFixOrCancel( TNotifyUI& msg )
{
	m_bIsFix = !m_bIsFix;
	if ( m_bIsFix )
	{
		ICncCommonOp::ShowControl(true,m_pm,_T("BtnOk"));
		ICncCommonOp::SetControlText(_T("取 消"),m_pm,_T("BtnFixOrCancel"));		
		//清空密码项
// 		ICncCommonOp::SetControlText(_T(""),m_pm,m_strEdtOldPassword.c_str());	
// 		ICncCommonOp::SetControlText(_T(""),m_pm,m_strEdtNewPassword.c_str());	
// 		ICncCommonOp::SetControlText(_T(""),m_pm,m_strEdtCheckPassword.c_str());
	}
	else
	{		
		ICncCommonOp::ShowControl(false,m_pm,_T("BtnOk"));
		ICncCommonOp::SetControlText(_T("修 改"),m_pm,_T("BtnFixOrCancel"));	

		//savePassWord(false);
		saveLockPassWord(false);
		saveSysTime(false);
		saveSysName(false);
        saveSuperadminInfo(false);
	}
	//更新时间同步状态
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckTimeSynchro") );
	if (pCheckBox)
	{
		pCheckBox->SetCheck(m_bIsTimeSynchro);
	}

	UpdateStandbyTime();
	setFixEnable(m_bIsFix);
	//选中当前的日期
    CCheckBoxUI* pCheckBoxPWEpochUpdate = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckIsPWEpochUpdate") );
	CComboUI *pComboPWEpochUpdate = (CComboUI*)ICncCommonOp::FindControl( m_pm, m_strComboPWEpochUpdate.c_str() );
	if (pComboPWEpochUpdate && pCheckBoxPWEpochUpdate)
	{
		TTpPasswordUpdateInfo tTpPasswordUpdateInfo;
		ComInterface->GetPasswordUpdateInfo(tTpPasswordUpdateInfo);
        pCheckBoxPWEpochUpdate->SetCheck(tTpPasswordUpdateInfo.m_bOpen);
		pComboPWEpochUpdate->SelectItem(tTpPasswordUpdateInfo.m_emUpdateFrequency);
	}

	return true;
}

bool CUserDefinedLogic::OnCheckIsPWEpochUpdate( TNotifyUI& msg )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	CComboUI *pComboPWEpochUpdate = (CComboUI*)ICncCommonOp::FindControl( m_pm, m_strComboPWEpochUpdate.c_str() );
	if ( !pComboPWEpochUpdate )
	{
		return false;
	}

	if ( pCheckBox->IsSelected() )
	{
		pComboPWEpochUpdate->SetAttribute(_T("enabled"),_T("true"));
	}
	else
	{
		pComboPWEpochUpdate->SetAttribute(_T("enabled"),_T("false"));
	}

	return true;
}

bool CUserDefinedLogic::OnCheckIsSysStandby( TNotifyUI& msg )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	CEditUI *pEdtStandbyTime = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtStandbyTime.c_str() );
	if ( !pEdtStandbyTime )
	{
		return false;
	}

	if ( pCheckBox->IsSelected() )
	{
		m_bIsSysStandby = true;
		pEdtStandbyTime->SetAttribute(_T("enabled"),_T("true"));
	}
	else
	{
		m_bIsSysStandby = false;
		pEdtStandbyTime->SetAttribute(_T("enabled"),_T("false"));
	}

	return true;
}

bool CUserDefinedLogic::OnCheckTimeSynchro( TNotifyUI& msg )
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	EnableTimeCtrl(!pCheckBox->IsSelected());	

	return true;
}

bool CUserDefinedLogic::OnBtnBack( TNotifyUI& msg )
{
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight(g_strUserDefinedDlg.c_str(),false );
	return true;
}

bool CUserDefinedLogic::OnBtnExit( TNotifyUI& msg )
{
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight(g_strUserDefinedDlg.c_str(),false );
	return true;
}

/**
bool CUserDefinedLogic::savePassWord( bool bIsSave )
{
	if ( !bIsSave )
	{
		return true;
	}

	CEditUI *pEdtOldPassword = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtOldPassword.c_str() );   
	CEditUI *pEdtNewPassword = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtNewPassword.c_str() );
	CEditUI *pEdtCheckPassword = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtCheckPassword.c_str() );
	
	String strOriPassWord = ICncCommonOp::GetControlText(m_pm, m_strEdtOldPassword.c_str());
	String strNewPassWord = ICncCommonOp::GetControlText(m_pm, m_strEdtNewPassword.c_str());
	String strCheckPassWord = ICncCommonOp::GetControlText(m_pm, m_strEdtCheckPassword.c_str());

	if (strOriPassWord.empty() && strNewPassWord.empty() && strCheckPassWord.empty())
	{
		return true;
	}
	TLoginInfo tLoginUser;
	ComInterface->GetLoginInfo(tLoginUser);

	CUserFullInfo cUser,cLoginUser;
	cUser.SetPassword( CT2A(strOriPassWord.c_str()));
	if ( UIDATAMGR->IsPcVersion() )//pc版获得的未加密密码
	{
		cLoginUser.SetPassword(tLoginUser.achPswd);
		if ( !cLoginUser.IsPassWordEqual( cUser.GetPassword()) ) 
		{ 
			showMessageBox(_T("原密码输入错误"));
			pEdtOldPassword->SetFocusX();			
			return false;
		}
	}
	else//tpad版本获得的密码是已经加密后的密码
	{
		if ( !cUser.IsPassWordEqual( tLoginUser.achPswd ) ) 
		{ 
			showMessageBox(_T("原密码输入错误"));
			pEdtOldPassword->SetFocusX();			
			return false;
		}
	}

	if ( strNewPassWord == _T("") )
	{    
		showMessageBox(_T("密码不能为空"));
		pEdtNewPassword->SetFocusX();
		return false;
	}
	if ( strNewPassWord != strCheckPassWord )
	{    
		showMessageBox(_T("请确认两次密码输入一致"));
		pEdtNewPassword->SetFocusX();
		return false;
	}

	if (!UIDATAMGR->IsValidPWStr(strNewPassWord.c_str()))
	{
		showMessageBox(_T("密码设置不规范，请重新输入"));
		return false;
	}

    cUser.SetName( tLoginUser.achName );
	cUser.SetPassword( CT2A(strNewPassWord.c_str()) );
    //admin用户需要管理员权限才可以修改密码
    if ( strcmp( tLoginUser.achName, "admin" ) == 0 )
    {
        cUser.SetActor( UM_ADMIN );
        cUser.m_dwGuid = 1;
        cUser.SetDiscription("Administrator");
        cUser.SetFullName( "administrator" );
    }   
	u16 wRe = ComInterface->UpdateUser( cUser ); 
	if ( wRe != NO_ERROR )
	{
		showMessageBox(_T("修改密码失败"));
		return false;
	}
	if ( UIDATAMGR->IsPcVersion() )//pc版设置的未加密密码
	{
		m_tLoginUser = tLoginUser;
		sprintf_s( m_tLoginUser.achPswd, sizeof(m_tLoginUser.achPswd), CW2A(strNewPassWord.data()) );
	}
	else//pad版设置的加密密码
	{
		m_tLoginUser = tLoginUser;
		sprintf_s( m_tLoginUser.achPswd, sizeof(m_tLoginUser.achPswd), cUser.GetPassword() );
	}
	
	return true;
}
**/

bool CUserDefinedLogic::saveLockPassWord( bool bIsSave )
{
	CEditUI *pEdtLockPassword = (CEditUI*)ICncCommonOp::FindControl( m_pm, m_strEdtLockPassword.c_str() );
	if (pEdtLockPassword)
	{
		TLockScreenInfo tInfo  = UIDATAMGR->GetLockScreenInfo(); 
		//UIManagePtr->GetSwitchState( m_stcStrSwitchBtnScreenPswd, tInfo.bOpen, m_pWndTree );
		String strLockPsw = (LPCTSTR)pEdtLockPassword->GetText();

		memcpy(tInfo.achPswd, strLockPsw.c_str(), strLockPsw.length());
		//tInfo.achPswd = strLockPsw.c_str();
		UIDATAMGR->SetLockScreenInfo( tInfo );
	}
	return true;
}

bool CUserDefinedLogic::saveSysTime( bool bIsSave )
{
	TCenDevSleepInfo tOriCenDevSleepInfo;
	ComInterface->GetSysSleepInfo( tOriCenDevSleepInfo );
	if ( bIsSave )
	{
		String strStandbyTime = ICncCommonOp::GetControlText(m_pm,_T("edtStandbyTime"));
		if ( m_bIsSysStandby )
		{
			if (tOriCenDevSleepInfo.bSleepUsed != m_bIsSysStandby || tOriCenDevSleepInfo.wSleepWaitTime !=  _ttoi( strStandbyTime.c_str()))
			{
				if (strStandbyTime.empty())
				{
					showMessageBox(_T("待机时间不能为空"));
					return false;
				}
				int nSec  = _ttoi( strStandbyTime.c_str() );
				ICncCommonOp::SetControlText(_T("开"),m_pm,_T("lbIsSysStandby"));
			
				if ( nSec > 3600 || nSec < 1 )
				{
					showMessageBox(_T("待机时间为 1 ~ 3600 间的整数"));
					return false;
				}
				else
				{
					ICncCommonOp::SetControlText(strStandbyTime.c_str(),m_pm,_T("lbSysStandby"));
					if ( nSec != m_tCenDevSleepInfo.wSleepWaitTime || (BOOL)m_bIsSysStandby != m_tCenDevSleepInfo.bSleepUsed )
					{
						TCenDevSleepInfo tCenDevSleepInfo;
						tCenDevSleepInfo.bSleepUsed = m_bIsSysStandby;
						tCenDevSleepInfo.wSleepWaitTime =  _ttoi( strStandbyTime.c_str());	
						ComInterface->SetSysSleepInfo( tCenDevSleepInfo );
					}
				}
			}
		}
		else
		{
			if (tOriCenDevSleepInfo.bSleepUsed != m_bIsSysStandby )
			{
				ICncCommonOp::SetControlText(_T("关"),m_pm,_T("lbIsSysStandby"));
				TCenDevSleepInfo tCenDevSleepInfo;
				if (strStandbyTime.empty())//如果设置的值为空，就默认成5
				{
					tCenDevSleepInfo.wSleepWaitTime = 5;
				}
				else
				{
					tCenDevSleepInfo.wSleepWaitTime = tOriCenDevSleepInfo.wSleepWaitTime;
				}
				
				tCenDevSleepInfo.bSleepUsed = m_bIsSysStandby;
				ComInterface->SetSysSleepInfo( tCenDevSleepInfo );
			}
		}
	}

	if ( bIsSave )
	{
		CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckTimeSynchro"));
		if ( !pCheckBox || !pCheckBox->IsSelected())
		{
			ComInterface->SetTimeSynchroCmd(FALSE);
			//把时间设置为系统时间 
			SYSTEMTIME time;
			ZeroMemory( &time, sizeof(SYSTEMTIME));
			String str;
			str = ICncCommonOp::GetControlText(m_pm,_T("edtDate"));
			sscanf( (CT2A)str.c_str(), "%u年%u月%u日", &time.wYear, &time.wMonth, &time.wDay );

			str = ICncCommonOp::GetControlText(m_pm,_T("lbHour"));
			sscanf( (CT2A)str.c_str(), "%d", &time.wHour);

			str = ICncCommonOp::GetControlText(m_pm,_T("lbMinute"));
			sscanf( (CT2A)str.c_str(),"%d",&time.wMinute); 

			str = ICncCommonOp::GetControlText(m_pm,_T("lbSecond"));
			sscanf( (CT2A)str.c_str(),"%d",&time.wSecond); 

			SYSTEMTIME systime;
			GetLocalTime( &systime );

			if (systime.wYear == time.wYear && systime.wMonth == time.wMonth && systime.wDay == time.wDay && 
				systime.wHour == time.wHour && systime.wMinute == time.wMinute && systime.wSecond == time.wSecond )
			{
				return true;
			}

			if ( InprovePrivilege() == FALSE )
			{
				return false;
			}

			BOOL32 re = SetLocalTime( &time );
			if ( !re )
			{   
				showMessageBox(_T("设置系统时间失败"));
				return false;
			}
			else
			{   
				OnUpdateSysTime( (WPARAM)&time, 0 );
				SyncTimeToServ(  time ); 
				//NOTIFY_MSG(UI_CMS_MODIFY_SYSTEM_TIME , 0 , 0);
			}
		}
		else
		{
			ComInterface->SetTimeSynchroCmd(TRUE);
		}
		
	}
	else
	{    
		UpdateSysTime();
	}

	return true;
}

bool CUserDefinedLogic::saveSysName(bool bIsSave)
{
	CString strIniPath = CMainFrameLogic::GetSingletonPtr()->GetIniFilePath();
	TCHAR tchSysName[MAX_NAME_LEN]={0};
	GetPrivateProfileString(_T("SysNameInfo"),_T("name"), _T("网呈会场控制台"),tchSysName, MAX_NAME_LEN, strIniPath);

	if (!bIsSave)
	{
		ICncCommonOp::SetControlText(tchSysName, m_pm, _T("lbSysName"));
		ICncCommonOp::SetControlText(tchSysName, m_pm, _T("edtSysName"));
		return true;
	}

	String strName = ICncCommonOp::GetControlText(m_pm, _T("edtSysName"));
	if (strName.empty())
	{
		showMessageBox(_T("系统名称不能为空"));
		CEditUI* pEdit = (CEditUI*)ICncCommonOp::FindControl(m_pm, _T("edtSysName"));
		if (pEdit)
		{
			pEdit->SetFocus();
		}
		return false;
	}

	CString str(tchSysName);
	if (str != strName.c_str())
	{
		WritePrivateProfileString(_T("SysNameInfo"),_T("name"),strName.c_str(),strIniPath);

		ICncCommonOp::SetControlText(strName.c_str(), m_pm, _T("lbSysName"));
		ICncCommonOp::SetControlText(strName.c_str(), m_pm, _T("edtSysName"));

		u16 wRe = ComInterface->changeSysName(); 
		if ( wRe != NO_ERROR )
		{
			showMessageBox(_T("修改系统名失败"));
			//ini文件恢复成之前的名称
			ICncCommonOp::SetControlText(str, m_pm, _T("lbSysName"));
			ICncCommonOp::SetControlText(str, m_pm, _T("edtSysName"));
			WritePrivateProfileString(_T("SysNameInfo"),_T("name"),str,strIniPath);
			return false;
		}
		
		if (UIDATAMGR->IsPcVersion())
		{
			CLoginLogic::GetSingletonPtr()->UpdateSysName();
		}
		
	}

	return true;
}

bool CUserDefinedLogic::savePasswordUpdateInfo()
{
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckIsPWEpochUpdate") );
	CComboUI *pComboPWEpochUpdate = (CComboUI*)ICncCommonOp::FindControl( m_pm, m_strComboPWEpochUpdate.c_str() );
	if ( !pCheckBox || !pComboPWEpochUpdate )
	{
		return false;
	}
	//修改界面显示的状态
	TTpPasswordUpdateInfo tTpPasswordUpdateInfo;
	tTpPasswordUpdateInfo.m_bOpen = pCheckBox->GetCheck();
	tTpPasswordUpdateInfo.m_emUpdateFrequency = (EmUpdateFrequency)pComboPWEpochUpdate->GetCurSel();
	//当前cns保存的状态
	TTpPasswordUpdateInfo tTpPasswordUpdateInfoCur;
	ComInterface->GetPasswordUpdateInfo(tTpPasswordUpdateInfoCur);
	if (tTpPasswordUpdateInfoCur.m_bOpen == tTpPasswordUpdateInfo.m_bOpen && tTpPasswordUpdateInfoCur.m_emUpdateFrequency == tTpPasswordUpdateInfo.m_emUpdateFrequency)
	{
		return true;
	}
	//时间
	SYSTEMTIME systime;
	GetLocalTime( &systime );

	tTpPasswordUpdateInfo.m_tTime.m_wYear     = systime.wYear;
	tTpPasswordUpdateInfo.m_tTime.m_byMonth   = systime.wMonth;
	tTpPasswordUpdateInfo.m_tTime.m_byMDay    = systime.wDay;
	tTpPasswordUpdateInfo.m_tTime.m_byHour    = systime.wHour;
	tTpPasswordUpdateInfo.m_tTime.m_byMinute  = systime.wMinute;
	tTpPasswordUpdateInfo.m_tTime.m_bySecond  = systime.wSecond;

	ComInterface->SetTpadPasswordUpdate(tTpPasswordUpdateInfo);

	return true;
}

bool CUserDefinedLogic::saveSuperadminInfo(bool bIsSave)
{
    TLoginInfo tLoginUser;
    ComInterface->GetLoginInfo(tLoginUser);
    if ( strcmp( T300E_TPAD_SUPERUSRNAME, tLoginUser.achName) != 0 )
    {
        return true;
    }

    //当前cns保存的状态
    TTpSuperUser tTpSuperUserCur;
    ComInterface->GetSuperadmninInfo(tTpSuperUserCur);

    if (!bIsSave)
    {
        CString strLockNumber = _T("");
        strLockNumber.Format(_T("%d"), tTpSuperUserCur.m_byLockNumber);
        ICncCommonOp::SetControlText(strLockNumber, m_pm, _T("EditPWErrorCount"));
        CString strLockTime = _T("");
        strLockTime.Format(_T("%d"), tTpSuperUserCur.m_dwLockTime);
        ICncCommonOp::SetControlText(strLockTime, m_pm, _T("EditPWLockTimer"));
        return true;
    }
    
    CEditUI* pEditErrorCount = (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("EditPWErrorCount") );
    CEditUI* pEditLockTime = (CEditUI*)ICncCommonOp::FindControl( m_pm, _T("EditPWLockTimer") );

    if (!pEditErrorCount || !pEditLockTime)
    {
        return false;
    }

    CString strLockCount = pEditErrorCount->GetText();
    CString strLockTime = pEditLockTime->GetText();
    //修改界面显示的状态
    TTpSuperUser tTpSuperUser;
    tTpSuperUser.m_byLockNumber = _tstoi(strLockCount);
    tTpSuperUser.m_dwLockTime = _tstoi(strLockTime);

    if (tTpSuperUserCur.m_byLockNumber == tTpSuperUser.m_byLockNumber && tTpSuperUserCur.m_dwLockTime == tTpSuperUser.m_dwLockTime)
    {
        return true;
    }

    if (tTpSuperUser.m_byLockNumber <= 0 || tTpSuperUser.m_byLockNumber > 10)
    {
        showMessageBox(_T("密码输错次数范围是1-10"));
        return false;
    }

    if (tTpSuperUser.m_dwLockTime <= 0 || tTpSuperUser.m_dwLockTime > 1440)
    {
        showMessageBox(_T("密码锁定时间范围是1-1440"));
        return false;
    }

    ComInterface->SetSuperadmninInfo(tTpSuperUser);

    return true;
}

bool CUserDefinedLogic::setFixEnable(bool bIsEnable)
{
	if ( bIsEnable )
	{
		m_pm->DoCase(_T("caseSet"));
	}
	else
	{
		m_pm->DoCase(_T("caseSetCancel"));
	}

	return true;
}

bool CUserDefinedLogic::OnBtnDownloadLog( TNotifyUI& msg )
{
    TTPFtpInfo tTPFtpInfo;
    ComInterface->GetCnFtpInfo(tTPFtpInfo);
    if (tTPFtpInfo.bOpen == FALSE)
    {
        //未开启则等待开启后再上传
        m_bWaitFtpDownLog = true;
        tTPFtpInfo.bOpen = TRUE;
        ComInterface->SetCnFtpInfo(tTPFtpInfo);
        return false;
    }

	ICncCommonOp::ShowControl( true, m_pm, _T("PageNotice") );

	u32 dwIp;
	ComInterface->GetLoginIp(dwIp);		
	struct in_addr addrIPAddr;
	addrIPAddr.S_un.S_addr = htonl(dwIp);
	CString strIpAddr = CA2T(inet_ntoa(addrIPAddr));

	m_ftp.SethWnd( m_pm->GetPaintWindow() );
	m_ftp.RegisterMsgHandle( WM_CNC_LOGLOADPROGRESS );

	//TTPFtpInfo tTPFtpInfo; //静默开启时已定义
	ComInterface->GetCnFtpInfo(tTPFtpInfo);
	if (tTPFtpInfo.bOpen == FALSE)
	{
		ShowPopMsg(_T("FTP上传服务器未开启!"));
		return FALSE;
	}
	BOOL32 bRet = m_ftp.SetServerParam( strIpAddr, CA2W(tTPFtpInfo.achUserName)/*_T("admin")*/, CA2W(tTPFtpInfo.achPassword)/*_T("kedacomTP")*/ );
	if ( !bRet )
	{
		ShowPopMsg(_T("设置FTP上传服务器失败!"));
		return FALSE;
	}

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

		GetPrivateProfileString( _T("log"), CFG_PATH, TEXT("Log/"), szReadPath, sizeof(szReadPath), strCfgFile );

		m_strLogFolderPath = szReadPath;

		if ( m_strLogFolderPath == _T("Log/") )
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

	m_vctLoglist.clear();
	if( m_ftp.FindfFtpFile(LOGPATH,_T("kdvlog.txt")) )
	{
		m_vctLoglist.push_back(_T("kdvlog.txt"));
	}
	
	for (int i=0; i<MAX_SYSLOG_NUM; i++)
	{
		CString str;
		str.Format(_T("kdvlog_%d.txt"),i);
		if( m_ftp.FindfFtpFile(LOGPATH,str) )
		{
			m_vctLoglist.push_back(str);
		}
	}

	//add by wangkui 2016-11-21
	if (m_vctLoglist.empty())
	{
		ICncCommonOp::ShowControl( false, m_pm, _T("PageNotice") );
		ShowPopMsg(_T("无日志"));
		return FALSE;
	}

	CString strLocalFilePath( m_strLogFolderPath );
	ComInterface->CreateDir( m_strLogFolderPath );
	strLocalFilePath = strLocalFilePath + m_vctLoglist.at(0);
	m_wLogId = 0;

	CString strRemoteFilePath(LOGPATH);
	strRemoteFilePath = strRemoteFilePath + m_vctLoglist.at(0);

	if ( !m_ftp.BeginDownload( strRemoteFilePath, strLocalFilePath, FTP_TRANSFER_TYPE_BINARY, FTP_AGENT, 0 ) ) 
	{
		//g_rlog.WriteLog(EM_ERROR, "%s:%d  %s\n", __FILE__, __LINE__, "[FTPError]上传文件失败，FTP设置参数错误！");
		m_ftp.SetAutoEndFtpFile(TRUE);
		return FALSE;
	}

	m_ftp.SetAutoEndFtpFile(true);

	return true;
}

bool CUserDefinedLogic::OnBtnCancelDownload( TNotifyUI& msg )
{
	m_ftp.EndFtpFile();
	ICncCommonOp::SetControlText(_T("正在下载，请稍后"),m_pm,_T("LabelTip"));
	ICncCommonOp::ShowControl( false, m_pm, _T("PageNotice") );
	return true;
}

void CUserDefinedLogic::UpdateSysTime()
{
	SYSTEMTIME sysTime;
	::GetLocalTime( &sysTime );
	OnUpdateSysTime( (WPARAM)&sysTime, 0 );
}

HRESULT CUserDefinedLogic::OnUpdateSysTime( WPARAM wparam, LPARAM lparam )
{
	if ( !IsCouldUpdate() )
	{
		return NO_ERROR;
	}

	SYSTEMTIME time = * reinterpret_cast< SYSTEMTIME *>(wparam);

	CString str = _T("");
	str.Format(_T("%d年%d月%d日"),time.wYear, time.wMonth, time.wDay);

	ICncCommonOp::SetControlText(str,m_pm, _T("lbDate"));
	ICncCommonOp::SetControlText(str,m_pm, _T("edtDate"));

	str.Format(_T("%.2d"),time.wHour);
	ICncCommonOp::SetControlText(str,m_pm, _T("lbHour"));

	str.Format(_T("%.2d"),time.wMinute);
	ICncCommonOp::SetControlText(str,m_pm, _T("lbMinute"));

	str.Format(_T("%.2d"),time.wSecond);
	ICncCommonOp::SetControlText(str,m_pm, _T("lbSecond"));

	return NO_ERROR;
}

BOOL32 CUserDefinedLogic::IsCouldUpdate()
{
	return m_bCouldUpdateTime;
}

u16 CUserDefinedLogic::SyncTimeToServ( const SYSTEMTIME sysTime )
{
	TTPTime time;
	time.m_wYear = sysTime.wYear;
	time.m_byMonth = sysTime.wMonth;
	time.m_byMDay = sysTime.wDay;
	time.m_byHour = sysTime.wHour;
	time.m_byMinute = sysTime.wMinute;
	time.m_bySecond = sysTime.wSecond;
	u16 re =  ComInterface->UpdateSysTime( time ); 

	if ( re == NO_ERROR )
	{  
		ComInterface->ReqSysTime();
	} 

	return re;
}

bool CUserDefinedLogic::OnBtnHMinus( TNotifyUI& msg )
{
	CLabelUI *plbHour = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbHour") ); 
	if (plbHour)
	{
		CString str = plbHour->GetText();
		int dwNum = _ttoi(str);
		if ( dwNum == 0)
		{
			dwNum = 23;
		}
		else
		{
			dwNum --;
		}
		str.Format(_T("%d"), dwNum);
		plbHour->SetText(str);
	}

	return NO_ERROR;
}

bool CUserDefinedLogic::OnBtnHAdd( TNotifyUI& msg )
{
	CLabelUI *plbHour = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbHour") ); 
	if (plbHour)
	{
		CString str = plbHour->GetText();
		int dwNum = _ttoi(str);
		if ( dwNum == 23)
		{
			dwNum = 0;
		}
		else
		{
			dwNum ++;
		}
		
		str.Format(_T("%d"), dwNum);
		plbHour->SetText(str);
	}

	return NO_ERROR;
}

bool CUserDefinedLogic::OnBtnMMinus( TNotifyUI& msg )
{
	CLabelUI *plbMinute = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbMinute") ); 
	if (plbMinute)
	{
		CString str = plbMinute->GetText();
		int dwNum = _ttoi(str);
		if ( dwNum == 0)
		{
			dwNum = 59;
		}
		else
		{
			dwNum --;
		}
		str.Format(_T("%d"), dwNum);
		plbMinute->SetText(str);
	}

	return NO_ERROR;
}

bool CUserDefinedLogic::OnBtnMAdd( TNotifyUI& msg )
{
	CLabelUI *plbMinute = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbMinute") ); 
	if (plbMinute)
	{
		CString str = plbMinute->GetText();
		int dwNum = _ttoi(str);
		if ( dwNum == 59)
		{
			dwNum = 0;
		}
		else
		{
			dwNum ++;
		}
		str.Format(_T("%d"), dwNum);
		plbMinute->SetText(str);
	}

	return NO_ERROR;
}

bool CUserDefinedLogic::OnBtnSMinus( TNotifyUI& msg )
{
	CLabelUI *pllbSecond = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbSecond") ); 
	if (pllbSecond)
	{
		CString str = pllbSecond->GetText();
		int dwNum = _ttoi(str);
		if ( dwNum == 0)
		{
			dwNum = 59;
		}
		else
		{
			dwNum --;
		}
		str.Format(_T("%d"), dwNum);
		pllbSecond->SetText(str);
	}

	return NO_ERROR;
}

bool CUserDefinedLogic::OnBtnSAdd( TNotifyUI& msg )
{
	CLabelUI *plbSecond = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbSecond") ); 
	if (plbSecond)
	{
		CString str = plbSecond->GetText();
		int dwNum = _ttoi(str);
		if ( dwNum == 59)
		{
			dwNum = 0;
		}
		else
		{
			dwNum ++;
		}
		str.Format(_T("%d"), dwNum);
		plbSecond->SetText(str);
	}

	return NO_ERROR;
}

void CUserDefinedLogic::EnableTimeCtrl( bool bIsEnable )
{

	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("edtDate"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("BtnDateSet"));

	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("BtnHMinus"));
	//ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("lbHour"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("BtnHAdd"));
	//ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("lbdot"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("BtnMMinus"));
	//ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("lbMinute"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("BtnMAdd"));
	//ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("lbdot2"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("BtnSMinus"));
	//ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("lbSecond"));
	ICncCommonOp::EnableControl(bIsEnable,m_pm,_T("BtnSAdd"));

}

bool CUserDefinedLogic::OnDownloadProgress( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	//add by wangkui 2016-11-22
	if (m_vctLoglist.empty())
	{
		return false;
	}
	
	EmFtpStatus emFileFtpStatus = static_cast<EmFtpStatus>(wParam);
	switch( emFileFtpStatus )
	{
	case emFtpBegin:
		{
		}
		break;
	case emFtpTransfer:
		{

			int dwCurrentFtpSize = m_ftp.GetCurrentFtpSize();
			int dwtTotalFileSize = m_ftp.GetTotalFileSize();
			if ( dwtTotalFileSize != 0)
			{
				int dwFtpProgress = ( 100 * (float)m_ftp.GetCurrentFtpSize() )/(m_ftp.GetTotalFileSize() );			
				CString str;
				str.Format(_T("共有文件%d个，第%d个文件已下载：%d%%"),m_vctLoglist.size(),m_wLogId+1,dwFtpProgress);

				ICncCommonOp::SetControlText(str,m_pm,_T("LbProcess"));
			}
		}
		break;
	case emFtpEnd:
		{
			DWORD dwSuccess = static_cast<DWORD>(lParam);     //FTP接口0为成功  默认失败
			m_ftp.EndFtpFile();	

			ICncCommonOp::SetControlText(_T(""),m_pm,_T("LbProcess"));

			if ( 0 == dwSuccess )
			{
				if (m_wLogId == m_vctLoglist.size()-1)
				{
					ICncCommonOp::SetControlText(_T("下载完成"),m_pm,_T("LabelTip"));
				}
			}
			else
			{
				if (m_wLogId == m_vctLoglist.size()-1)
				{
					LPTSTR pszMsg = NULL;
					m_ftp.FormatFtpError( dwSuccess, &pszMsg );
					CString str;
					str.Format(_T("下载失败，错误原因：%s"), pszMsg);
					ICncCommonOp::SetControlText(str,m_pm,_T("LabelTip"));
					LocalFree( pszMsg );
				}
			}

			m_wLogId ++;
			if (m_wLogId == m_vctLoglist.size())
			{
				m_wLogId = 0;
				return TRUE;
			}

			CString strRemoteFilePath(LOGPATH);
			strRemoteFilePath = strRemoteFilePath + m_vctLoglist.at(m_wLogId);
			CString strLocalFilePath( m_strLogFolderPath );
			strLocalFilePath = strLocalFilePath + m_vctLoglist.at(m_wLogId);

			if ( !m_ftp.BeginDownload( strRemoteFilePath, strLocalFilePath, FTP_TRANSFER_TYPE_BINARY, FTP_AGENT, 0 ) ) 
			{
				m_ftp.SetAutoEndFtpFile(TRUE);
				return FALSE;
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

bool CUserDefinedLogic::OnSleepInfoNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	ComInterface->GetSysSleepInfo( m_tCenDevSleepInfo );
	UpdateStandbyTime();
	return true;
}

void CUserDefinedLogic::UpdateStandbyTime()
{
	char arr[12];
	itoa( m_tCenDevSleepInfo.wSleepWaitTime, arr, 10 );
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl(m_pm,_T("CheckIsSysStandby"));
	if ( !pCheckBox )
	{
		return;
	}
	pCheckBox->Selected(m_tCenDevSleepInfo.bSleepUsed);

	if (m_tCenDevSleepInfo.bSleepUsed)
	{
		ICncCommonOp::SetControlText(_T("开"),m_pm,_T("lbIsSysStandby"));
	}
	else
	{
		ICncCommonOp::SetControlText(_T("关"),m_pm,_T("lbIsSysStandby"));
	}
	CString str(arr);
	ICncCommonOp::SetControlText(str,m_pm,_T("lbSysStandby"));
	ICncCommonOp::SetControlText(str,m_pm,_T("edtStandbyTime"));
	

}

bool CUserDefinedLogic::OnBtnDateSet( TNotifyUI& msg )
{
	 POINT pt;

	 RECT rt = msg.pSender->GetPos();
	 pt.x = rt.left + ((rt.right - rt.left)/2);
	 pt.y = rt.top;
	
	 SYSTEMTIME time;
	 ZeroMemory( &time, sizeof(SYSTEMTIME));
	 String str;
	 str = ICncCommonOp::GetControlText(m_pm,_T("edtDate"));
	 sscanf( (CT2A)str.c_str(), "%u年%u月%u日", &time.wYear, &time.wMonth, &time.wDay );

	 CCalendarLogic::GetSingletonPtr()->SetCalendarInfor(pt, time);

	 WINDOW_MGR_PTR->ShowWindow(g_strCalendarDlg.c_str());

	return true;
}

bool CUserDefinedLogic::OnCalendarDateSel( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	CString str = *reinterpret_cast<CString*>(wParam);
	ICncCommonOp::SetControlText(str, m_pm, _T("lbDate"));
	ICncCommonOp::SetControlText(str, m_pm, _T("edtDate"));
	return true;
}

BOOL CUserDefinedLogic::InprovePrivilege( )
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;

	// Get a token for this process.
	if (  !OpenProcessToken( GetCurrentProcess(),
		 TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken) )
	{
		showMessageBox(_T("无法获取访问令牌句柄"));
		return FALSE ;
	}

	// Get the LUID for the shutdown privilege.
	LookupPrivilegeValue(NULL, SE_SYSTEMTIME_NAME, 
		&tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;  // one privilege to set   
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	// Get the shutdown privilege for this process.
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
		(PTOKEN_PRIVILEGES)NULL, 0);

	if (GetLastError() != ERROR_SUCCESS)
	{
		showMessageBox(_T("修改权限失败"));
		return FALSE;
	}
	return TRUE;
}

bool CUserDefinedLogic::OnUpdateTime( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TTPTime tTptime = *(TTPTime*)wParam;
	SYSTEMTIME sysTime;
	ZeroMemory( &sysTime, sizeof(SYSTEMTIME));
	sysTime.wYear = tTptime.m_wYear;
	sysTime.wMonth = tTptime.m_byMonth;
	sysTime.wDay = tTptime.m_byMDay;
	sysTime.wHour = tTptime.m_byHour;
	sysTime.wMinute = tTptime.m_byMinute;
	sysTime.wSecond = tTptime.m_bySecond;
	if ( sysTime.wYear == 0 || sysTime.wMonth == 0 || sysTime.wDay == 0 )
	{
		return false;
	}

	SYSTEMTIME sysCurTime;
	GetLocalTime( &sysCurTime );

	if (sysTime.wYear == sysCurTime.wYear && sysTime.wMonth == sysCurTime.wMonth && sysTime.wDay == sysCurTime.wDay && 
		sysTime.wHour == sysCurTime.wHour && sysTime.wMinute == sysCurTime.wMinute && sysTime.wSecond == sysCurTime.wSecond )
	{
		return true;
	}

	BOOL32 re = SetLocalTime( &sysTime );
	if ( !re )
	{   
		showMessageBox(_T("设置系统时间失败"));
		return false;
	}

	OnUpdateSysTime( (WPARAM)&sysTime, 0 );
	return true;
};

void CUserDefinedLogic::UpdateTime()
{
	SYSTEMTIME systime;
	GetLocalTime( &systime );

	if (!m_bIsFix)
	{
		CString strSecond = _T("");
		if (systime.wSecond < 10 && !m_bIsFix)
		{
			strSecond.Format(_T("0%d"),systime.wSecond);
		}
		else
		{
			strSecond.Format(_T("%d"),systime.wSecond);
		}

		ICncCommonOp::SetControlText(strSecond, m_pm, _T("lbSecond"));

		CString strHour = _T("");
		CString strMinute = _T("");

		if (systime.wHour < 10 )
		{
			strHour.Format(_T("0%d"),systime.wHour);
		}
		else
		{
			strHour.Format(_T("%d"),systime.wHour);
		}

		if (systime.wMinute < 10 )
		{
			strMinute.Format(_T("0%d"),systime.wMinute);
		}
		else
		{
			strMinute.Format(_T("%d"),systime.wMinute);
		}

		ICncCommonOp::SetControlText(strHour, m_pm, _T("lbHour"));
		ICncCommonOp::SetControlText(strMinute, m_pm, _T("lbMinute"));
	}
}

bool CUserDefinedLogic::OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    ComInterface->ShowKeyboard();
    return true;
}

bool CUserDefinedLogic::OnCnSysTimeToCnc(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	m_bIsTimeSynchro = lParam;
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckTimeSynchro") );
	if (pCheckBox)
	{
		pCheckBox->SetCheck(m_bIsTimeSynchro);
	}
	if (m_bIsTimeSynchro)
	{
		EnableTimeCtrl(false);
		OnUpdateTime( wParam, lParam, bHandle );
	}
	else
	{
		EnableTimeCtrl(true);

	}
	return true;
}

bool CUserDefinedLogic::OnChangeUserInfo( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	//用户信息列表
	TplArray<CUserFullInfo>* tplUserList;
	tplUserList = ComInterface->GetUserList();
	//当前登录的用户
	TLoginInfo tLoginUser;
	ComInterface->GetLoginInfo(tLoginUser);

	if (!tplUserList->IsEmpty())
	{
		for (int i = 0 ; i < tplUserList->Size() ; i++)
		{
			if ( strcmp( tplUserList->GetAt(i).GetName(), tLoginUser.achName) == 0 )
			{
				CUserFullInfo cUser;
				cUser.SetPassword( tLoginUser.achPswd );
				if ( UIDATAMGR->IsPcVersion() )
				{
					if ( !cUser.IsPassWordEqual( m_tLoginUser.achPswd ) ) 
					{ 
						ComInterface->SetLoginInfo(m_tLoginUser);
					}
				}
				else
				{
					if ( !cUser.IsPassWordEqual( m_tLoginUser.achPswd ) ) 
					{ 
						ComInterface->SetLoginInfo(m_tLoginUser);
					}
				}
				break;
			}
		}
	}

	return true;
}

bool CUserDefinedLogic::OnCnPasswordUpdateNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	TTpPasswordUpdateInfo tTpPasswordUpdateInfo = *(TTpPasswordUpdateInfo*)wParam;
	if (tTpPasswordUpdateInfo.m_bOpen)
	{
		//当前系统时间
		SYSTEMTIME systime;
		GetLocalTime( &systime );
		TTPTime tTptimeCur;
		tTptimeCur.m_wYear     = systime.wYear;
		tTptimeCur.m_byMonth   = systime.wMonth;
		tTptimeCur.m_byMDay    = systime.wDay;
		tTptimeCur.m_byHour    = systime.wHour;
		tTptimeCur.m_byMinute  = systime.wMinute;
		tTptimeCur.m_bySecond  = systime.wSecond;
        //如果时间为0，则通知cns将当前时间设为起始时间
        if ( 0 == tTpPasswordUpdateInfo.m_tTime.m_wYear    &&
             0 == tTpPasswordUpdateInfo.m_tTime.m_byMonth  &&
             0 == tTpPasswordUpdateInfo.m_tTime.m_byMDay   &&
             0 == tTpPasswordUpdateInfo.m_tTime.m_byHour   &&
             0 == tTpPasswordUpdateInfo.m_tTime.m_byMinute &&
             0 == tTpPasswordUpdateInfo.m_tTime.m_bySecond )
        {
            tTpPasswordUpdateInfo.m_tTime = tTptimeCur;
            ComInterface->SetTpadPasswordUpdate(tTpPasswordUpdateInfo);
            return true;
        }
		//Cns保存修改时间+安全周期
		TTPTime tTptimeCns = tTpPasswordUpdateInfo.m_tTime;
		int nTimeCycle = (int)tTpPasswordUpdateInfo.m_emUpdateFrequency + 1;
		if (tTptimeCns.m_byMonth + nTimeCycle <= 12)
		{
			tTptimeCns.m_byMonth += nTimeCycle;
		}
		else
		{
			tTptimeCns.m_wYear ++;
			tTptimeCns.m_byMonth = tTptimeCns.m_byMonth + nTimeCycle - 12;
		}
		//对比时间判断是否超过周期、
		if ( tTptimeCns < tTptimeCur)
		{
			ShowPopMsg(_T("密码长期未更新,存在一定风险,请修改密码！"));
		}
	}

	return OnChangePasswordUpdateInfo( wParam, lParam, bHandle);
}

bool CUserDefinedLogic::OnChangePasswordUpdateInfo(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	TTpPasswordUpdateInfo tTpPasswordUpdateInfo = *(TTpPasswordUpdateInfo*)wParam;

	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckIsPWEpochUpdate") );
	CComboUI *pComboPWEpochUpdate = (CComboUI*)ICncCommonOp::FindControl( m_pm, m_strComboPWEpochUpdate.c_str() );
	if ( !pCheckBox || !pComboPWEpochUpdate )
	{
		return false;
	}

	
	pCheckBox->SetCheck(tTpPasswordUpdateInfo.m_bOpen);
	if (tTpPasswordUpdateInfo.m_bOpen)
	{
		ICncCommonOp::SetControlText(_T("开"),m_pm,_T("lbIsPWEpochUpdate"));
	}
	else
	{
		ICncCommonOp::SetControlText(_T("关"),m_pm,_T("lbIsPWEpochUpdate"));
	}

	switch(tTpPasswordUpdateInfo.m_emUpdateFrequency)
	{
	case 0:
		ICncCommonOp::SetControlText(_T("1个月"),m_pm,_T("lbPWEpochUpdate"));
		pComboPWEpochUpdate->SelectItem(0);
		break;
	case 1:
		ICncCommonOp::SetControlText(_T("2个月"),m_pm,_T("lbPWEpochUpdate"));
		pComboPWEpochUpdate->SelectItem(1);
		break;
	case 2:
		ICncCommonOp::SetControlText(_T("3个月"),m_pm,_T("lbPWEpochUpdate"));
		pComboPWEpochUpdate->SelectItem(2);
		break;
	default:
		ICncCommonOp::SetControlText(_T(""),m_pm,_T("lbPWEpochUpdate"));
		break;
	}

	return true;
}

bool CUserDefinedLogic::OnSetCnFtpRsp(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    TTPFtpInfo tTPFtpInfo;
    ComInterface->GetCnFtpInfo(tTPFtpInfo);
    if (tTPFtpInfo.bOpen == FALSE)
    {
        if (m_bWaitFtpDownLog)
        {
            m_bWaitFtpDownLog = false;
            ShowPopMsg(_T("FTP上传服务器开启失败!"));
        }
        return false;
    }

    if (m_bWaitFtpDownLog)
    {
        m_bWaitFtpDownLog = false;
        TNotifyUI msg;
        OnBtnDownloadLog(msg);
    }

    return true;
}

void CUserDefinedLogic::UpdateSuperadmin()
{
    //当前登录的用户
    TLoginInfo tLoginUser;
    ComInterface->GetLoginInfo(tLoginUser);
    if ( strcmp( T300E_TPAD_SUPERUSRNAME, tLoginUser.achName) == 0 )
    {
        m_pm->DoCase(_T("caseSuperAdmin"));
    }
    else
    {
        m_pm->DoCase(_T("caseNormalUser"));
    }
}

bool CUserDefinedLogic::OnBtnUnLockAllUser( TNotifyUI& msg )
{
    ComInterface->UnlockAllUser();

    return true;
}

bool CUserDefinedLogic::OnSuperadminNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    TTpSuperUser tTpSuperUser = *(TTpSuperUser*)wParam;

    CString strLockNumber = _T("");
    strLockNumber.Format(_T("%d"), tTpSuperUser.m_byLockNumber);
    ICncCommonOp::SetControlText( strLockNumber,m_pm,_T("EditPWErrorCount"));
    CString strLockNumberl = _T("");
    strLockNumberl.Format(_T("%d 次"), tTpSuperUser.m_byLockNumber);
    ICncCommonOp::SetControlText( strLockNumberl,m_pm,_T("lbPWErrorCount"));

    CString strLockTime = _T("");
    strLockTime.Format(_T("%d"), tTpSuperUser.m_dwLockTime);
    ICncCommonOp::SetControlText( strLockTime,m_pm,_T("EditPWLockTimer"));
    CString strLockTimel = _T("");
    strLockTimel.Format(_T("%d 分钟"), tTpSuperUser.m_dwLockTime);
    ICncCommonOp::SetControlText( strLockTimel,m_pm,_T("lbPWLockTimer"));

    return true;
}