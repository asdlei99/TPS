#include "stdafx.h"
#include "mainframelogic.h"
#include "cnsmanagelogic.h"
#include "addreditlogic.h"
#include "addrbooklogic.h"
#include "mainmenulogic.h"
#include "confmsglogic.h"
#include "userdefinedlogic.h"
#include "tvwalllogic.h"
#include "videomixlogic.h"

template<> CMainFrameLogic* Singleton<CMainFrameLogic>::ms_pSingleton  = NULL;

static UINT g_nMsgTimerID;   //timer 的id，用于刷新告警按钮
static UINT g_nUpdateTimerID;   //timer 的id，用于刷新时间
static UINT g_nFreshConfStateTimerID;   //timer 的id，用于第一次登录后刷新会议状态

VOID  CALLBACK  CBTimerPoc( HWND hwnd, UINT  uMsg, UINT_PTR idEvent, DWORD dwTime  );

APP_BEGIN_MSG_MAP(CMainFrameLogic, CNotifyUIImpl)
	MSG_CREATEWINDOW(_T("MainFrame"), OnCreate)
	MSG_INIWINDOW(_T("MainFrame"), OnInit)
	
	MSG_CLICK(_T("BtnQuit"), OnBtnQuit)
	MSG_CLICK(_T("BtnExit"), OnBtnExit)
	MSG_CLICK(_T("BtnBack"), OnBtnBack)
	
	MSG_CLICK(_T("BtnTipBg"), OnBtnTip)

	MSG_SELECTCHANGE(_T("CheckAutoLogin"), OnCheckAutoLogin)
	MSG_SELECTCHANGE(_T("CheckRemPassWord"), OnCheckRemPassWord)

	MSG_SELECTCHANGE(_T("titleTabLeft"), OnTabTitleLeft)
	MSG_SELECTCHANGE(_T("titleTabRight"), OnTabTitleRight)

	MSG_BUTTONDOWN(_T("CnsManageDlg"), OnContainerClick)

	USER_MSG(UI_CMS_SHOW_ALARM_DLG,OnShowMsgNotify)
	USER_MSG( UI_CNS_CONNECTED, OnConnectRsp )
	USER_MSG(UI_CNS_DISCONNECTED, OnDisconnect)
	
	USER_MSG(UI_TPAD_SHOWCENTRECTRL_NTY, OnTpadShowCenterCtrlNty)
	USER_MSG(UI_TPAD_SHOWSYSCONFIG_NTY, OnTpadShowSysConfigNty)
    USER_MSG(UI_TPAD_SHOWCNSMANAGE_NTY, OnTpadShowCnsManageNty)
    	
	USER_MSG(UI_TPAD_HOMEKEY_NOTIFY, OnTpadHomeKeyNty)	
	USER_MSG(UI_CNSINS_START_DUALCODESTREAM_RSP, OnTpadShowDual)

	//系统待机
	USER_MSG(UI_TPAD_CENTRESLEEP_NTY, OnCentreSleepNotify )
	//ums错误提示
	USER_MSG(UI_CNS_UMSREASON_IND, OnUmsReasonInd )
	USER_MSG(UI_CNS_CNSINFO_NOTIFY,OnCnsInfoNotify)
	//ums会场请求加入会议
	USER_MSG(UI_UMS_JOINCONF_REG,OnJoinConfReqChair)
	//数据会议状态通知
	USER_MSG(UI_WBCONFSTATE_NTY,OnWBConfStateNty) 
	USER_MSG(UI_NEWWBCONFCALL_REQ,OnNewConfCallReq)
	//tpad登录时用户信息记录 2015-10-9 
	USER_MSG(UI_TPAD_LOGINUSER_NOTIFY,OnTpadLoginInfoNty)

    USER_MSG( WM_DISPLAYCHANGE, OnDisplayChange )
	USER_MSG( UI_TPAD_CNSDISCONNECTED_NTY, OnCnsDisconnectNty )
	USER_MSG( UI_DISCONNECTED_CLEARDATA, OnDisconnectClear )
	
APP_END_MSG_MAP()

CMainFrameLogic::CMainFrameLogic()
{
	m_bMsgOn = FALSE;
	m_bIsPadShowCenterOrSys = false;
	g_nMsgTimerID = 0;
	g_nUpdateTimerID = 0;
	g_nFreshConfStateTimerID = 0;
	m_strLastWnd = _T("");
}


CMainFrameLogic::~CMainFrameLogic()
{
}

bool CMainFrameLogic::OnCreate( TNotifyUI& msg )
{
	HWND hWnd = m_pm->GetPaintWindow();
	LONG styleValue = ::GetWindowLong(hWnd, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	styleValue &= ~WS_SIZEBOX;//窗口大小不可拖拽 dyy 2015-4-29
	::SetWindowLong(hWnd, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	//窗口边框增加阴影效果
	/*m_cWndShadow.Create(hWnd);
	m_cWndShadow.SetSize(5);
	m_cWndShadow.SetSharpness(10);
	m_cWndShadow.SetDarkness(80);
	m_cWndShadow.SetPosition(0, 0);*/

	return false;
}

bool CMainFrameLogic::OnInit( TNotifyUI& msg )
{
	//WINDOW_MGR_PTR->ShowWindow( g_stcStrLoginDlg.c_str() );
	REG_CNC_MSG_WND_OB(m_pm->GetPaintWindow());

	bool bPC = UIDATAMGR->IsPcVersion();
	if( bPC )//pc版
	{
		CString strIniPath = GetIniFilePath();
		//读ini文件 配置
		int wAuto=0;
		wAuto = GetPrivateProfileInt(_T("LoginInfo"),_T("AutoLogin"), 0,strIniPath);
		TCHAR tchIP[16] = {0};
		TCHAR tchUserName[MAX_NAME_LEN]={0};
		TCHAR tchPassWord[MAX_NAME_LEN]={0};

		GetPrivateProfileString(_T("LoginInfo"),_T("IP"),_T(""), tchIP, 16, strIniPath);
		GetPrivateProfileString(_T("LoginInfo"),_T("UserName"),_T(""), tchUserName, MAX_NAME_LEN-1, strIniPath);
		GetPrivateProfileString(_T("LoginInfo"), _T("PassWord"),_T(""), tchPassWord, MAX_NAME_LEN-1, strIniPath);

		ICncCommonOp::SetControlText(tchIP, m_pm, _T("EdIp"));
		ICncCommonOp::SetControlText(tchUserName, m_pm, _T("EdUserName"));
		ICncCommonOp::SetControlText(tchPassWord, m_pm, _T("EdPassword"));

		TCHAR tchSysName[MAX_NAME_LEN]={0};
		GetPrivateProfileString(_T("SysNameInfo"),_T("name"), _T("网呈会场控制台"),tchSysName, MAX_NAME_LEN, strIniPath);
		ICncCommonOp::SetControlText(tchSysName, m_pm, _T("lbSysName"));

		//不自动登录
		if ( wAuto == 0 )
		{
			CString str(tchPassWord);
			if (!str.IsEmpty())
			{
				CCheckBoxUI *pCheckRemPassWord = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckRemPassWord") );
				if (pCheckRemPassWord)
				{
					pCheckRemPassWord->SetCheck(true);
				}
			}

			ICncCommonOp::ShowControl( true, m_pm, _T("PageLogin") );
			ICncCommonOp::ShowControl( false, m_pm, _T("PageCnsManage") );
			WINDOW_MGR_PTR->ShowWindow( g_strMainMenuDlg.c_str(), false );
		}
		//自动登录
		if ( wAuto == 1 )
		{
            CString cstrIp = tchIP;
            UIDATAMGR->GetClearIP(cstrIp);
			u32 dwIp = ntohl( inet_addr( CT2A(cstrIp) ) );
			u16 uRe = ComInterface->Connect( dwIp, CONNETCT_CNS_PORT, tchUserName, tchPassWord );

			CCheckBoxUI *pCheckAutoLogin = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckAutoLogin") );
			CCheckBoxUI *pCheckRemPassWord = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckRemPassWord") );

			if (pCheckAutoLogin && pCheckRemPassWord)
			{
				pCheckAutoLogin->SetCheck(true);
			}

			ICncCommonOp::ShowControl( false, m_pm, _T("PageLogin") );
			ICncCommonOp::ShowControl( true, m_pm, _T("PageCnsManage") );
			WINDOW_MGR_PTR->ShowWindow( g_strMainMenuDlg.c_str(), true);
		}
		//设置版本号
		CString strVer = _T("V");
		strVer  += _T(TPAD_VERSION_ID);
		ICncCommonOp::SetControlText(strVer, m_pm, _T("version"));
	}
	else //TPad版
	{
		RECT rcCaption = { 0 };
		m_pm->SetCaptionRect(rcCaption);

		ComInterface->ConnectTPad();
		
		ICncCommonOp::ShowControl( false, m_pm, _T("PageLogin") );
		ICncCommonOp::ShowControl( true, m_pm, _T("PageCnsManage") );
		WINDOW_MGR_PTR->ShowWindow( g_strMainMenuDlg.c_str(), true);
		WINDOW_MGR_PTR->ShowWindow( g_stcStrMainFrameDlg.c_str(), false );
		
	}

	WINDOW_MGR_PTR->ShowWindow( g_strAddrbookDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strConfTempDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strRegServiceDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strRoomControlDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strConfCtrlDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strAddrEditDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strUserManagerDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strUserDefinedDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strConfCallCfgDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strConfMsgDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strSysConfigDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strLocalRoomCfgDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strSrcSelWatchDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strCalendarDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_stcStrCenterCtrlDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_stcStrDualViewDlg.c_str(), false );
	//初始化模拟屏
	CCnsManageLogic::GetSingletonPtr()->InitCnsScreenList();

	//创建临时文件夹
	CString strFullPath = GetModuleFullPath() + TP_TEMPFILE_PATH;		
	if(!PathFileExists(strFullPath))
	{
		CreateDirectory(strFullPath, NULL);
	}
	return true;
}

bool CMainFrameLogic::OnBtnQuit( TNotifyUI& msg )
{
	int nResult = ShowMessageBox((_T("是否确定要关闭系统")),true);
	if ( IDOK == nResult )
	{
		CMainMenuLogic::GetSingletonPtr()->SaveShortCutToIni();
		ComInterface->ShutDownCmc();
	}
	return true;
}

bool CMainFrameLogic::OnBtnBack( TNotifyUI& msg )
{
	String strCurWnd = UIDATAMGR->GetCurShowWndName();

	if (m_bIsPadShowCenterOrSys && (strCurWnd == g_stcStrCenterCtrlDlg || strCurWnd == g_strSysConfigDlg) && !UIDATAMGR->IsPcVersion())
	{
		m_bIsPadShowCenterOrSys = false;
		WINDOW_MGR_PTR->ShowWindow( g_strMainMenuDlg.c_str(), true );

		m_pm->DoCase( _T("caseShowCnsManage") );
		if (strCurWnd == g_stcStrCenterCtrlDlg)
		{
			WINDOW_MGR_PTR->ShowWindow( g_stcStrCenterCtrlDlg.c_str(), false );		
		}
		else
		{
			WINDOW_MGR_PTR->ShowWindow( g_strSysConfigDlg.c_str(), false );		
		}	

		UIDATAMGR->SetCurShowWndName(_T(""));

		WINDOW_MGR_PTR->ShowMainWindowLeftToRight( g_stcStrMainFrameDlg.c_str(), false );

		return true;
	}

    if ( strCurWnd == g_stcStrTvWallChildDlg )
    {
        NOTIFY_MSG( UI_CNC_HIDE_TVWALLCHILDDLG_NTY, NULL, NULL );
        return true;
    }


	if ( strCurWnd == g_strConfMsgDlg || strCurWnd == g_strSysConfigDlg )
	{
		if (strCurWnd == g_strConfMsgDlg && !m_strLastWnd.empty())
		{
			CString strTitle = _T("");
			CString strImg = _T("");
			
			if ( m_strLastWnd == g_strConfMsgDlg)
			{
				strTitle = _T("消息提示");
				strImg = _T("res/title/imgMessage.png");
			}
			else if (m_strLastWnd == g_strRegServiceDlg)
			{
				strTitle = _T("服务器设置");
				strImg = _T("res/title/imgServer.png");
			}
			else if (m_strLastWnd == g_strAddrbookDlg)
			{
				strTitle = _T("地址簿");
				strImg = _T("res/title/imgAddrbook.png");
			}
            else if (m_strLastWnd == g_strAddrEditDlg)
            {
                strTitle = _T("地址簿管理");
                strImg = _T("res/title/imgAddrbook.png");
            }
			else if (m_strLastWnd == g_strInviteCnsDlg)
			{
				strTitle = _T("邀请会场");
				strImg = _T("res/title/imgInvite.png");
			}
			else if (m_strLastWnd == g_strConfTempDlg)
			{
				strTitle = _T("会议模板");
				strImg = _T("res/title/imgConfTemp.png");
			}
			else if (m_strLastWnd == g_strConfCtrlDlg)
			{
				strTitle = _T("会议管理");
				strImg = _T("res/title/imgConfCtrl.png");
			}
			else if (m_strLastWnd == g_strRoomControlDlg)
			{
				strTitle = _T("会场管理");
				strImg = _T("res/title/imgRoomCtrl.png");
			}
			else if (m_strLastWnd == g_strUserManagerDlg)
			{
				strTitle = _T("用户管理");
				strImg = _T("res/title/imgUserManage.png");
			}
			else if (m_strLastWnd == g_strUserDefinedDlg)
			{
				strTitle = _T("自定义设置");
				strImg = _T("res/title/imgSelfSet.png");
			}
			else if (m_strLastWnd == g_strConfCallCfgDlg)
			{
				strTitle = _T("会议呼叫设置");
				strImg = _T("res/title/imgConfTemp.png");
			}
			else if (m_strLastWnd == g_strLocalRoomCfgDlg)
			{
				strTitle = _T("本会场设置");
				strImg = _T("res/title/imgRoomCtrl.png");
			}
			else if (m_strLastWnd == g_strSrcSelWatchDlg)
			{
				strTitle = _T("会议选看");
				strImg = _T("res/title/imgSelWatch.png");
			}
			else if (m_strLastWnd == g_stcStrCenterCtrlDlg)
			{
				strTitle = _T("中控管理");
				strImg = _T("res/title/imgCenterCtrl.png");
			}

			CMainFrameLogic::GetSingletonPtr()->SetTitle(strTitle);
			CMainFrameLogic::GetSingletonPtr()->SetTitlePic(strImg);

			UIDATAMGR->SetCurShowWndName( m_strLastWnd );
			m_strLastWnd = _T("");

			WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));	
			WINDOW_MGR_PTR->ShowWindowFromBottomToTop( strCurWnd.c_str(), false );
			return true;
		}

		m_pm->DoCase( _T("caseShowCnsManage") );
		WINDOW_MGR_PTR->ShowWindowFromBottomToTop( strCurWnd.c_str(), false );
		UIDATAMGR->SetCurShowWndName(_T(""));
	}
	else
	{
		if ( strCurWnd == g_strInviteCnsDlg )
		{
			SetTitleTab( false );
            
            strCurWnd = g_strAddrbookDlg;
		}

        if ( strCurWnd == g_strAddrEditDlg )
        {
            String strAddrWnd = UIDATAMGR->GetCurAddrWndName();
            /*if ( strAddrWnd == g_strAddrbookDlg )
            {
                SetTitleTab( false );

                CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("地址簿"));
                CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgAddrbook.png"));

                //WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
                UIDATAMGR->SetCurShowWndName( g_strAddrbookDlg );
            }
            else*/ if ( strAddrWnd == g_strInviteCnsDlg )
            {
                CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("邀请会场"));
                CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgInvite.png"));
                CMainFrameLogic::GetSingletonPtr()->SetTitleTab( true, g_strInviteCnsDlg.c_str() );

                //WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
                UIDATAMGR->SetCurShowWndName( g_strInviteCnsDlg );
            }
            else
            {
                SetTitleTab( false );

                CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("地址簿"));
                CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgAddrbook.png"));
                UIDATAMGR->SetCurShowWndName( g_strAddrbookDlg );
            }

            CAddrEditLogic::GetSingletonPtr()->OnExitAddrEdit();
            
            WINDOW_MGR_PTR->ShowWindowFromLeftToRight( strCurWnd.c_str(), false );
            return true;
        }

		if ( /*strCurWnd == g_strAddrEditDlg ||*/ strCurWnd == g_strUserManagerDlg|| strCurWnd == g_strConfCallCfgDlg
			|| strCurWnd == g_strRegServiceDlg || strCurWnd == g_strLocalRoomCfgDlg|| strCurWnd == g_strUserDefinedDlg )  	 
		{			
			CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("系统设置"));
			CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgSysCfg.png"));

			WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowConfCtrl"));
			UIDATAMGR->SetCurShowWndName( g_strSysConfigDlg );
			WINDOW_MGR_PTR->ShowWindowFromLeftToRight( strCurWnd.c_str(), false );
			return true;
		}

		m_pm->DoCase( _T("caseShowCnsManage") );
		WINDOW_MGR_PTR->ShowWindowFromLeftToRight( strCurWnd.c_str(), false );
		UIDATAMGR->SetCurShowWndName(_T(""));
	}

	return true;
}

bool CMainFrameLogic::OnBtnExit( TNotifyUI& msg )
{
	if ( UIDATAMGR->IsPcVersion())
	{
		ComInterface->DisConnect();
	}
	else
	{
		if (m_bIsPadShowCenterOrSys)
		{
			WINDOW_MGR_PTR->ShowWindow( g_strMainMenuDlg.c_str(), true );
			m_bIsPadShowCenterOrSys = false;	
		}

		String strCurWnd = UIDATAMGR->GetCurShowWndName();
		if ( strCurWnd != _T(""))
		{
			if (strCurWnd == g_strConfMsgDlg && !m_strLastWnd.empty())
			{
				WINDOW_MGR_PTR->ShowWindow( m_strLastWnd.c_str(), false);
				m_strLastWnd = _T("");
			}

			if ( /*strCurWnd == g_strAddrEditDlg ||*/ strCurWnd == g_strUserManagerDlg|| strCurWnd == g_strConfCallCfgDlg
				|| strCurWnd == g_strRegServiceDlg || strCurWnd == g_strLocalRoomCfgDlg|| strCurWnd == g_strUserDefinedDlg )  	 
			{	
				WINDOW_MGR_PTR->ShowWindow( g_strSysConfigDlg.c_str(), false);
			}

			if ( strCurWnd == g_strInviteCnsDlg )
			{
				strCurWnd = g_strAddrbookDlg;
			}
			SetTitleTab( false );

            if ( strCurWnd == g_strAddrEditDlg )//地址簿管理界面时退出，同时关闭地址簿界面
            {
                WINDOW_MGR_PTR->ShowWindow( g_strAddrbookDlg.c_str(), false);
                CAddrEditLogic::GetSingletonPtr()->OnExitAddrEdit();
            }

            if ( strCurWnd == g_stcStrTvWallChildDlg )
            {
                CTvWallLogic::GetSingletonPtr()->HideChildWindow();
                WINDOW_MGR_PTR->ShowWindow( g_strConfCtrlDlg.c_str(), false);
            }

			m_pm->DoCase( _T("caseShowCnsManage") );
			WINDOW_MGR_PTR->ShowWindow( strCurWnd.c_str(), false);
			UIDATAMGR->SetCurShowWndName(_T(""));          
		}

		WINDOW_MGR_PTR->ShowMainWindowLeftToRight( g_stcStrMainFrameDlg.c_str(), false );	
	}

	return true;
}

bool CMainFrameLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	//PC版响应断链，Pad版响应TPad断链消息
	if ( UIDATAMGR->IsPcVersion())
	{
		//清空数据，退出到登陆界面
		NOTIFY_MSG( UI_DISCONNECTED_CLEARDATA );
	}

	return true;
}


bool CMainFrameLogic::OnTabTitleLeft(TNotifyUI& msg)
{
	String strCurWnd = UIDATAMGR->GetCurShowWndName();

	if ( strCurWnd == g_strAddrEditDlg )
	{
		CPaintManagerUI* pm = CAddrEditLogic::GetSingletonPtr()->GetPaintManagerUI();
		CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( pm, _T("AddrEditSlideTab") );
		if (pControl)
		{
			pControl->SelectItem(emTabID_Left);
            CAddrEditLogic::GetSingletonPtr()->OnAddrEditTabSwitch( emTabID_Left );
		}
	}
    else if ( strCurWnd == g_strInviteCnsDlg )
    {
        CPaintManagerUI* pm = CAddrBookLogic::GetSingletonPtr()->GetPaintManagerUI();
        CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( pm, _T("AddrBookLayout") );
        if (pControl)
        {
            pControl->SelectItem(emTabID_Left);
        }
    }

	return true;
}

bool CMainFrameLogic::OnTabTitleRight(TNotifyUI& msg)
{
	String strCurWnd = UIDATAMGR->GetCurShowWndName();

	if ( strCurWnd == g_strAddrEditDlg )
	{
		CPaintManagerUI* pm = CAddrEditLogic::GetSingletonPtr()->GetPaintManagerUI();
		CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( pm, _T("AddrEditSlideTab") );
		if (pControl)
		{
			pControl->SelectItem(emTabID_Right);
            CAddrEditLogic::GetSingletonPtr()->OnAddrEditTabSwitch( emTabID_Right );
		}
	}
    else if ( strCurWnd == g_strInviteCnsDlg )
    {
        CPaintManagerUI* pm = CAddrBookLogic::GetSingletonPtr()->GetPaintManagerUI();
        CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( pm, _T("AddrBookLayout") );
        if (pControl)
        {
            pControl->SelectItem(emTabID_Right);
        }
    }
	return true;
}

bool CMainFrameLogic::SetTitle( LPCTSTR lpstrTitle )
{
	return ICncCommonOp::SetControlText( lpstrTitle, m_pm, _T("StcTitleName") );
}

bool CMainFrameLogic::SetTitlePic( LPCTSTR lpstrTitle )
{
	return ICncCommonOp::SetControlBkImg( lpstrTitle, m_pm, _T("StcTitleImg") );
}

bool CMainFrameLogic::SetTitleTab( bool bShow, LPCTSTR lpstrDlgName )
{
	if ( bShow )
	{
		if ( lpstrDlgName == g_strAddrEditDlg )
		{
			ICncCommonOp::SetControlText( _T("本地地址簿"), m_pm, _T("titleTabLeft") );
			ICncCommonOp::SetControlText( _T("在线地址簿"), m_pm, _T("titleTabRight") );
		}
        else if ( lpstrDlgName == g_strInviteCnsDlg )
        {
            ICncCommonOp::SetControlText( _T("地址簿"), m_pm, _T("titleTabLeft") );
            ICncCommonOp::SetControlText( _T("其它"), m_pm, _T("titleTabRight") );
        }

        COptionUI *pOption = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("titleTabLeft") );
        if (pOption)
        {
            pOption->Selected( true );
        }

		ICncCommonOp::ShowControl( true, m_pm, _T("titleTabLeft") );
		ICncCommonOp::ShowControl( true, m_pm, _T("titleTabRight") );
		
	}
	else
	{
		ICncCommonOp::ShowControl( false, m_pm, _T("titleTabLeft") );
		ICncCommonOp::ShowControl( false, m_pm, _T("titleTabRight") );

        COptionUI *pOption = (COptionUI*)ICncCommonOp::FindControl( m_pm, _T("titleTabLeft") );
        if (pOption)
        {
            pOption->Selected( true );
        }
	}
	return true;
}

bool CMainFrameLogic::OnShowMsgNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	String strCurWnd = UIDATAMGR->GetCurShowWndName();
	if (strCurWnd == g_strConfMsgDlg)//当前在提示页 不显示
	{
		return true;
	}

	ICncCommonOp::EnableControl( true, m_pm, _T("BtnTipBg") );
	g_nMsgTimerID = SetTimer( NULL, NULL, 500, CBTimerPoc );
	return true;
}

void CMainFrameLogic::UpdateMsgImg()
{
	ICncCommonOp::ShowControl(true,m_pm,_T("BtnTip"));
	if ( m_bMsgOn )
	{
		ICncCommonOp::SetControlBkImg( _T("res/public/tip_normal.png"), m_pm, _T("BtnTip") );
	}
	else
	{
		ICncCommonOp::SetControlBkImg( _T("res/public/tip_down.png"), m_pm, _T("BtnTip") );
	}
	m_bMsgOn = !m_bMsgOn;
}

bool CMainFrameLogic::OnBtnTip( TNotifyUI& msg )
{
	HideTipBtn();

	m_strLastWnd = UIDATAMGR->GetCurShowWndName();
	CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("消息提示"));
	CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgMessage.png"));

	WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
	UIDATAMGR->SetCurShowWndName( g_strConfMsgDlg );
	WINDOW_MGR_PTR->ShowWindowFromBottomToTop(g_strConfMsgDlg.c_str() );

	m_bMsgOn = false;
	
	return true;
}

void CMainFrameLogic::HideTipBtn()
{
	if ( g_nMsgTimerID != 0 )
	{
		KillTimer( NULL, g_nMsgTimerID );
		g_nMsgTimerID = 0;

		ICncCommonOp::ShowControl(false,m_pm,_T("BtnTip"));
		ICncCommonOp::EnableControl( false, m_pm, _T("BtnTipBg") );
	}
}

bool CMainFrameLogic::OnConnectRsp( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	if (wParam != TRUE)
	{
		if ( UIDATAMGR->IsPcVersion() )
		{
			ICncCommonOp::ShowControl( true, m_pm, _T("PageLogin") );
			ICncCommonOp::ShowControl( false, m_pm, _T("PageCnsManage") );
		}	
				
		/*WINDOW_MGR_PTR->ShowWindow( g_strMainMenuDlg.c_str(), false );	
		WINDOW_MGR_PTR->ShowWindow( g_strAddrbookDlg.c_str(), false );
		WINDOW_MGR_PTR->ShowWindow( g_strConfTempDlg.c_str(), false );
		WINDOW_MGR_PTR->ShowWindow( g_strRegServiceDlg.c_str(), false );
		WINDOW_MGR_PTR->ShowWindow( g_strRoomControlDlg.c_str(), false );
		WINDOW_MGR_PTR->ShowWindow( g_strConfCtrlDlg.c_str(), false );
		WINDOW_MGR_PTR->ShowWindow( g_strInviteCnsDlg.c_str(),false);
		WINDOW_MGR_PTR->ShowWindow( g_strAddrEditDlg.c_str(), false );
		WINDOW_MGR_PTR->ShowWindow( g_strUserManagerDlg.c_str(), false );
		WINDOW_MGR_PTR->ShowWindow( g_strUserDefinedDlg.c_str(), false );
		WINDOW_MGR_PTR->ShowWindow( g_strConfCallCfgDlg.c_str(), false );
		WINDOW_MGR_PTR->ShowWindow( g_strConfMsgDlg.c_str(), false );
		WINDOW_MGR_PTR->ShowWindow( g_strSysConfigDlg.c_str(), false );
		WINDOW_MGR_PTR->ShowWindow( g_strLocalRoomCfgDlg.c_str(), false );
		WINDOW_MGR_PTR->ShowWindow( g_strSrcSelWatchDlg.c_str(), false );
		WINDOW_MGR_PTR->ShowWindow( g_strCalendarDlg.c_str(), false );
		WINDOW_MGR_PTR->ShowWindow( g_stcStrCenterCtrlDlg.c_str(), false );
		WINDOW_MGR_PTR->ShowWindow( g_stcStrDualViewDlg.c_str(),false);*/

		return false;	
	}

	UpdateTime();
	g_nUpdateTimerID = SetTimer( NULL, NULL, 1000, CBTimerPoc );
	g_nFreshConfStateTimerID = SetTimer( NULL, NULL, 2000, CBTimerPoc );

	//记录到ini文件 
	String strIP = ICncCommonOp::GetControlText(m_pm, _T("EdIp"));
	String strUser = ICncCommonOp::GetControlText(m_pm, _T("EdUserName"));
	String strPassword = ICncCommonOp::GetControlText(m_pm, _T("EdPassword"));

	CString strIniPath = GetIniFilePath();

    CString cstrIp = strIP.c_str();
    UIDATAMGR->GetClearIP(cstrIp);
	WritePrivateProfileString(_T("LoginInfo"),_T("IP"),cstrIp,strIniPath);
	WritePrivateProfileString(_T("LoginInfo"),_T("UserName"),strUser.c_str(),strIniPath);
	
	CCheckBoxUI *pCheckAutoLogin = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckAutoLogin") );
	CCheckBoxUI *pCheckRemPassWord = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckRemPassWord") );
	if (pCheckAutoLogin)
	{
		if (pCheckAutoLogin->GetCheck())
		{
			WritePrivateProfileString(_T("LoginInfo"),_T("AutoLogin"),_T("1"),strIniPath);
			WritePrivateProfileString(_T("LoginInfo"),_T("PassWord"),strPassword.c_str(),strIniPath);
            WritePrivateProfileString(_T("LoginInfo"),_T("RemberPW"),_T("1"),strIniPath);
		}
		else
		{
			WritePrivateProfileString(_T("LoginInfo"),_T("AutoLogin"),_T("0"),strIniPath);
			if (pCheckRemPassWord->GetCheck())
			{
				WritePrivateProfileString(_T("LoginInfo"),_T("PassWord"),strPassword.c_str(),strIniPath);
				WritePrivateProfileString(_T("LoginInfo"),_T("RemberPW"),_T("1"),strIniPath);
			}
			else
			{
				WritePrivateProfileString(_T("LoginInfo"),_T("PassWord"),_T(""),strIniPath);
				WritePrivateProfileString(_T("LoginInfo"),_T("RemberPW"),_T("0"),strIniPath);
			}
		}
	}
	return true;
}

bool CMainFrameLogic::OnCnsInfoNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TTPCnsInfo tLocalCnsInfo;
	ComInterface->GetLocalCnsInfo( tLocalCnsInfo );

	ICncCommonOp::SetControlText((CA2T)tLocalCnsInfo.m_achRoomName,m_pm,_T("StcRoomName"));
	return true;
}

void CMainFrameLogic::UpdateTime()
{
	SYSTEMTIME systime;
	GetLocalTime( &systime );

	CString strDate = _T("");
	strDate.Format(_T("%d-%d-%d"),systime.wYear,systime.wMonth,systime.wDay);
	CString strTime = _T("");
	CString strHour = _T("");
	CString strMinute = _T("");
	if (systime.wHour < 10)
	{
		strHour.Format(_T("0%d"),systime.wHour);
	}
	else
	{
		strHour.Format(_T("%d"),systime.wHour);
	}

	if (systime.wMinute < 10)
	{
		strMinute.Format(_T(":0%d"),systime.wMinute);
	}
	else
	{
		strMinute.Format(_T(":%d"),systime.wMinute);
	}
	strTime = strHour + strMinute;
	String 	strlbDate = ICncCommonOp::GetControlText(m_pm,_T("lbDate"));
	CString strOriDate(strlbDate.c_str());
	if ( strOriDate != strDate)
	{
		ICncCommonOp::SetControlText(strDate, m_pm, _T("lbDate"));
	}
	
	ICncCommonOp::SetControlText(strTime, m_pm, _T("lbTime"));
}

CString CMainFrameLogic::GetIniFilePath()
{
	TCHAR tchPath[MAX_PATH] = {0};
	CString strIniFilePath;
	if (S_OK == SHGetFolderPathW(NULL,CSIDL_APPDATA,NULL,0,tchPath))
	{
		CString strIniFileDir(tchPath);
		strIniFileDir = strIniFileDir + _T("\\cnc");		
		if(!PathFileExists(strIniFileDir))
		{
			CreateDirectory(strIniFileDir, NULL);
		}
		strIniFilePath = strIniFileDir + _T("\\conf.ini");
	}

	return strIniFilePath;
}

void CMainFrameLogic::UpdateLoginShowInfo()
{
	CString strIniPath = GetIniFilePath();
	int wRemPW = GetPrivateProfileInt(_T("LoginInfo"),_T("RemberPW"), 0,strIniPath);
	if (!wRemPW)
	{
		ICncCommonOp::SetControlText(_T(""), m_pm, _T("EdPassword"));
	}
}

//自动登录一定记住密码
bool CMainFrameLogic::OnCheckAutoLogin( TNotifyUI& msg )
{
	CCheckBoxUI *pCheckAutoLogin = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckAutoLogin") );
	CCheckBoxUI *pCheckRemPassWord = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckRemPassWord") );
	if (pCheckAutoLogin && pCheckRemPassWord)
	{
		if (pCheckAutoLogin->GetCheck())
		{
			pCheckRemPassWord->SetCheck(true);
		}
	}
	return true;
}

bool CMainFrameLogic::OnTpadShowCenterCtrlNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_bIsPadShowCenterOrSys = true;
	WINDOW_MGR_PTR->ShowWindow( g_strMainMenuDlg.c_str(), false );

	WINDOW_MGR_PTR->ShowWindowInitLocation( g_stcStrCenterCtrlDlg.c_str() );
	//WINDOW_MGR_PTR->BringWindowTop( g_stcStrMainFrameDlg.c_str() );
	//WINDOW_MGR_PTR->ShowWindow( g_stcStrMainFrameDlg.c_str(), true );
    WINDOW_MGR_PTR->ShowMainWindowLeftToRight( g_stcStrMainFrameDlg.c_str(), true );
	
	CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("中控管理"));
	CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgCenterCtrl.png"));

	WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
	UIDATAMGR->SetCurShowWndName( g_stcStrCenterCtrlDlg );

	return true;
}

bool CMainFrameLogic::OnTpadShowSysConfigNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_bIsPadShowCenterOrSys = true;
	WINDOW_MGR_PTR->ShowWindow( g_strMainMenuDlg.c_str(), false );

	WINDOW_MGR_PTR->ShowWindowInitLocation( g_strSysConfigDlg.c_str() );
	//WINDOW_MGR_PTR->BringWindowTop( g_stcStrMainFrameDlg.c_str() );
	WINDOW_MGR_PTR->ShowMainWindowLeftToRight( g_stcStrMainFrameDlg.c_str(), true );
	
	CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("系统设置"));
	CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgSysCfg.png"));

	WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
	UIDATAMGR->SetCurShowWndName( g_strSysConfigDlg );

	return true;
}

bool CMainFrameLogic::OnTpadShowCnsManageNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    WINDOW_MGR_PTR->ShowMainWindowLeftToRight( g_stcStrMainFrameDlg.c_str(), true );
    return true;
}

bool CMainFrameLogic::OnTpadHomeKeyNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TNotifyUI msg;
	OnBtnExit(msg);
	return true;
}

bool CMainFrameLogic::OnTpadShowDual(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	EmTPAddDualRcvResult emReVideo = (EmTPAddDualRcvResult)wParam;
	EmTPAddDualRcvResult emReAudio = (EmTPAddDualRcvResult)lParam;

	if ( emReVideo == emAddDualRcvSucceed && !UIDATAMGR->IsPcVersion())
	{     
		OnTpadHomeKeyNty(NULL,NULL,bHandle);
		return NO_ERROR;
	}

	if( emReAudio != emAddDualRcvSucceed && emReVideo != emAddDualRcvSucceed )
	{
		switch( emReVideo )
		{
		case emAddDualRcvFailNoDual:
			ShowPopMsg( _T("观看演示失败：当前未处于接收双流状态") );
			break;

		case emAddDualRcvFailIllegalPos:
			ShowPopMsg( _T("观看演示失败：通道非法") );
			break;

		case emAddDualRcvFailNoPos:
			ShowPopMsg( _T("观看演示失败：无空闲通道") );
			break;

		case emAddDualRcvFailUnKown:
			ShowPopMsg( _T("观看演示失败") );

		case emAddDualRcvFailStatusError:
			ShowPopMsg( _T("观看演示失败：当前已处于双流状态") );
			break;
		default:
			ShowPopMsg( _T("观看演示失败") );
			break;
		}

		return S_FALSE;
	}

	if ( emReVideo != emAddDualRcvSucceed )
	{
		switch( emReVideo )
		{
		case emAddDualRcvFailNoDual:
			ShowPopMsg( _T("接收演示视频失败：当前未处于接收双流状态") );
			break;

		case emAddDualRcvFailIllegalPos:
			ShowPopMsg( _T("接收演示视频失败：通道非法") );
			break;

		case emAddDualRcvFailNoPos:
			ShowPopMsg( _T("接收演示视频失败：无空闲通道当前无演示") );
			break;

		case emAddDualRcvFailUnKown:
			ShowPopMsg( _T("接收演示视频失败") );
			break;

		case emAddDualRcvFailStatusError:
			ShowPopMsg( _T("接收演示视频失败：当前已处于双流状态"));
			break;
		default:
			ShowPopMsg( _T("接收演示视频失败") );
			break;
		}
	}

	return NO_ERROR;
}

bool CMainFrameLogic::OnCentreSleepNotify( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	if ( UIDATAMGR->IsPcVersion() )
	{
		ComInterface->DisConnect();
	}
	return NO_ERROR;
}

bool CMainFrameLogic::OnUmsReasonInd( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	TTPUmsReasonInd tReason;
	tReason = ComInterface->GetUmsReason();

	TCMSConf tConf;
	BOOL bInConf = ComInterface->IsInConf( &tConf );

	CString strMsg = _T("");

	switch( tReason.m_dwReason )
	{
// 	case TP_UMS_Discard_Start:
// 		strMsg = _T("开启讨论失败：媒体资源不足");
// 		break;
	case TP_UMS_Discard_AddEp:
		{
			u32 dwEpId = tReason.m_dwReserve1;
			if ( bInConf )
			{
				TCnsInfo *tCnsInfo = tConf.GetCnsInfoByID( dwEpId );
				if ( tCnsInfo != NULL )
				{
					strMsg.Format( _T("统一开启讨论时，会场%s进入讨论失败"), (CA2T)tCnsInfo->m_achRoomName );
				}
			}
		}   
		break;
	case TP_UMS_Discard_EpOnLine:
		{
			u32 dwEpId = tReason.m_dwReserve1;
			EmDiscussOprRes em = (EmDiscussOprRes)tReason.m_dwReserve2;
			if ( bInConf )
			{
				TCnsInfo *tCnsInfo = tConf.GetCnsInfoByID( dwEpId );
				if ( tCnsInfo != NULL )
				{
					strMsg.Format( _T("会场%s上线时，进入讨论失败"), (CA2T)tCnsInfo->m_achRoomName );
				}
			}
		}        
		break;
	case TP_UMS_VMP_Audience_ChanNoVid:
		{
			vector<TBrdVmpResNtfy> vctBrdVmpArray = ComInterface->GetBrdVmpStatus();

			u32 dwEpId = tReason.m_dwReserve1;
			u32 dwId = tReason.m_dwReserve2;//合成器id

			CString strVmpName = _T("");
			for (int i = 0; i<vctBrdVmpArray.size(); i++)
			{
				if (vctBrdVmpArray.at(i).m_tEqpInfo.m_byEqpID = dwId)
				{
					strVmpName.Format(_T("%s"), (CA2T)vctBrdVmpArray.at(i).m_tEqpInfo.m_szEqpAlias);
				}
			}
			if ( bInConf )
			{
				TCnsInfo *tCnsInfo = tConf.GetCnsInfoByID( dwEpId );
				if ( tCnsInfo != NULL )
				{
					strMsg.Format( _T("合成器vip不足，普通会场进入合成器无图像"));//普通会场%s进入合成器无图像"), (CA2T)tCnsInfo->m_achRoomName )// 提示太长，显示不下，去掉会场名
				}
			}
		}        
		break;
	case TP_UMS_VMP_Speaker_ChanNoVid:
		{
			vector<TBrdVmpResNtfy> vctBrdVmpArray = ComInterface->GetBrdVmpStatus();

			u32 dwEpId = tReason.m_dwReserve1;
			u32 dwId = tReason.m_dwReserve2;//合成器id

			CString strVmpName = _T("");
			for (int i = 0; i<vctBrdVmpArray.size(); i++)
			{
				if (vctBrdVmpArray.at(i).m_tEqpInfo.m_byEqpID = dwId)
				{
					strVmpName.Format(_T("%s"), (CA2T)vctBrdVmpArray.at(i).m_tEqpInfo.m_szEqpAlias);
				}
			}

			if ( bInConf )
			{
				TCnsInfo *tCnsInfo = tConf.GetCnsInfoByID( dwEpId );
				if ( tCnsInfo != NULL )
				{
					strMsg.Format( _T("合成器vip不足，发言会场%s进入合成器无图像"), (CA2T)tCnsInfo->m_achRoomName );
				}
			}
		}        
		break;
	case TP_UMS_VMP_Dual_ChanNoVid:
		{
			vector<TBrdVmpResNtfy> vctBrdVmpArray = ComInterface->GetBrdVmpStatus();

			u32 dwEpId = tReason.m_dwReserve1;
			u32 dwId = tReason.m_dwReserve2;//合成器id

			CString strVmpName = _T("");
			for (int i = 0; i<vctBrdVmpArray.size(); i++)
			{
				if (vctBrdVmpArray.at(i).m_tEqpInfo.m_byEqpID = dwId)
				{
					strVmpName.Format(_T("%s"), (CA2T)vctBrdVmpArray.at(i).m_tEqpInfo.m_szEqpAlias);
				}
			}
			if ( bInConf )
			{
				TCnsInfo *tCnsInfo = tConf.GetCnsInfoByID( dwEpId );
				strVmpName = strVmpName + _T("无图像");
				if ( tCnsInfo != NULL )
				{
					strMsg.Format( _T("合成器vip不足，会场%s的双流进入合成器无图像"), (CA2T)tCnsInfo->m_achRoomName );
					strMsg = strMsg + strVmpName;

				}
			}
		}        
		break;
	case TP_UMS_VMP_GetVidFail:
		{
			vector<TBrdVmpResNtfy> vctBrdVmpArray = ComInterface->GetBrdVmpStatus();
			u32 dwEpId = tReason.m_dwReserve1;
			u32 dwId = tReason.m_dwReserve2;//合成器id

			CString strVmpName = _T("");
			for (int i = 0; i<vctBrdVmpArray.size(); i++)
			{
				if (vctBrdVmpArray.at(i).m_tEqpInfo.m_byEqpID = dwId)
				{
					strVmpName.Format(_T("%s"), (CA2T)vctBrdVmpArray.at(i).m_tEqpInfo.m_szEqpAlias);
				}
			}
			if ( bInConf )
			{
				TCnsInfo *tCnsInfo = tConf.GetCnsInfoByID( dwEpId );
				if ( tCnsInfo != NULL )
				{
					strMsg.Format( _T("码流调度失败，会场%s进入合成器无图像"), (CA2T)tCnsInfo->m_achRoomName);
				}
			}
		}        
		break;
	case TP_UMS_Poll_BasDisCnnt:
		{
			strMsg = _T("适配掉线，轮询停止");
		}        
		break;
	case TP_UMS_Poll_VmpDisCnnt:
		{
			strMsg = _T("合成掉线，轮询停止");
		}        
		break;
	case TP_UMS_Poll_EpNextBas:
		{
			u32 dwEpId = tReason.m_dwReserve1;
			if ( bInConf )
			{
				TCnsInfo *tCnsInfo = tConf.GetCnsInfoByID( dwEpId );
				if ( tCnsInfo != NULL )
				{
					strMsg.Format( _T("轮询跳过会场%s：适配资源不足"), (CA2T)tCnsInfo->m_achRoomName );
				}
			}
		}        
		break;
	case TP_UMS_Poll_EpNextBW:
		{
			u32 dwEpId = tReason.m_dwReserve1;
			if ( bInConf )
			{
				TCnsInfo *tCnsInfo = tConf.GetCnsInfoByID( dwEpId );
				if ( tCnsInfo != NULL )
				{
					strMsg.Format( _T("轮询跳过会场%s：带宽资源不足"), (CA2T)tCnsInfo->m_achRoomName );
				}
			}
		}        
		break;
	case TP_UMS_View_BasDisCnnt:
		{
			strMsg = _T("适配不足，选看停止");
		}        
		break;
	case TP_UMS_View_VmpDisCnnt:
		{
			strMsg = _T("已关闭画面合成，选看停止");
		}        
		break;
	case TP_UMS_View_BWFull:
		{
			strMsg = _T("带宽不足，选看停止");
		}        
		break;
	case TP_UMS_View_NoVid:
		{
			strMsg = _T("无视频源，选看停止");
		}        
		break;
	case TP_UMS_View_NoVmp:
		{
			strMsg = _T("无法收看合成图像：画面合成资源不足");
		}
		break;
	case TP_Discuss_StopByUms_NoVaildEp:
		{
			strMsg = _T("讨论内无有效成员，讨论结束");
		}        
		break;
	case TP_Discuss_StopByUms_MixError:
		{
			strMsg = _T("混音板掉线，讨论结束");
		}        
		break;
	case TP_Discuss_StopByUms_BasError:
		{
			strMsg = _T("适配板掉线，讨论结束");
		}        
		break;
	case TP_Discuss_StopByUms_VmpError:
		{
			strMsg = _T("合成板掉线，讨论结束");
		}        
		break;

	case TP_UMS_AdapterQuit:
		{
			strMsg = _T("接入板掉线");
		}        
		break;
	case TP_UMS_AllEpHungUp:
		{
			strMsg = _T("所有会场挂断");
		}        
		break;
	case TP_UMS_BasDisConnect:
		{
			strMsg = _T("适配板掉线");
		}        
		break;
	case TP_UMS_BasStartFail:
		{
			strMsg = _T("适配开启失败");
		}        
		break;
	case TP_UMS_MediaTransQuit:
		{
			strMsg = _T("转发板掉线");
		}        
		break;
	case TP_UMS_ChairIsB3CNS:
		{
			strMsg = _T("主席是老版本CNS");
		}        
		break;
	case Tp_UMS_TvWall_MTVmpFail:
		{
			strMsg = _T("资源不足，进入电视墙通道失败");
		}        
		break;
	case TP_UMS_TvWall_InvalidMT:
		{
			strMsg = _T("无效终端，进入电视墙通道失败");
		}        
		break;
	case TP_UMS_TvWall_BandError:
		{
			strMsg = _T("带宽不足，进入电视墙通道失败");
		}        
		break;
	case TP_UMS_TvWall_VmpError:
		{
			strMsg = _T("合成器掉线，进入电视墙通道失败");
		}        
		break;
	case TP_UMS_Dual_BasDisCnnt:
		{
			strMsg = _T("适配掉线，双流停止");
		}        
		break;
	case TP_UMS_Dual_MixDisCnnt:
		{
			strMsg = _T("混音器掉线，双流停止");
		}        
		break;
	case TP_UMS_Dual_BasFull:
		{
			strMsg = _T("开启双流失败：适配资源不足");
		} 
		break;
	case TP_UMS_QuitAudMix:
		{
			strMsg = _T("会议语音激励关闭：资源不足");
		}        
		break; 
	case TP_UMS_ChairIsUMS:
		{
			strMsg = _T("主席是UMS");
		}        
		break;
	case TP_UMS_ChairIsMT:
		{
			strMsg = _T("主席是MT");
		}        
		break;
	case TP_UMS_ChairIsMCU:
		{
			strMsg = _T("主席是MCU");
		} 
		break;
	case TP_UMS_SuperDropped:
		{
			strMsg = _T("上级掉线");
		}        
		break; 
	case TP_UMS_ChairIsFailed:
		{
			strMsg = _T("主席未上线");
		}        
		break;
    case TP_UMS_TvWall_VmpCapFail:
        {
            strMsg = _T("合成能力不足");
        }
        break;
    case TP_UMS_TvWall_AssignVmpFail:
        {
            strMsg = _T("多画面通道不支持选看画面合成器");
        }
        break;
	case TP_ROLLCALLER_OFFLINE:
		{
			strMsg = _T("点名人离开，点名结束");
		} 
		break;
	case Tp_ROLLCALL_MIX_ERROR:
		{
			strMsg = _T("系统异常，请检查");
		}        
		break; 
	case Tp_ROLLCALL_CREATE_CHAN_FAIL:
		{
			strMsg = _T("上调码流或PUT音频错误");
		}        
		break;
	case TP_CONFAUDMIX_MIX_ERROR:
		{
			strMsg = _T("会议混音，混音器错误");
		}        
		break; 
	case TP_CONFAUDMIX_STOP_NO_EP:
		{
			strMsg = _T("无在线会场，混音关闭");
		}        
		break;
 	case TP_CONFAUDMIX_MIXCHAN_FULL:
 		{
 			strMsg = _T("会议混音，混音通道满");
 		}        
 		break; 
 	case TP_CONFAUDMIX_DELETE_SPEAKER:
 		{
 			strMsg = _T("会议混音时不能删除发言会场");
 		}        
 		break;
	case Tp_ROLLCALL_START_NO_TARGET:
 		{
 			strMsg = _T("未选择被点名人，点名开启失败");
 		}        
 		break; 
 	case Tp_ROLLCALL_ALLTARGET_OFFLINE:
 		{
 			strMsg = _T("无被点名人在线，点名结束");
 		}        
		break;
	case TP_UMS_SpeakerVmpError:
		{
			strMsg = _T("系统异常，请检查");
		}        
		break;
	case TP_UMS_FECC_NO_323MT:
		{
			strMsg = _T("摄像机远摇时非323终端");
		}        
		break;
	case TP_UMS_FECC_CHANNEL_NOT_OPEN:
		{
			strMsg = _T("摄像机远摇时远遥通道未打开");
		}        
		break;
	default:
		break;
	}

	if ( !strMsg.IsEmpty() )
	{
		ShowPopMsg( strMsg );
	}

	return S_OK;
}

bool CMainFrameLogic::OnCheckRemPassWord( TNotifyUI& msg )
{
	CCheckBoxUI *pCheckAutoLogin = (CCheckBoxUI*)ICncCommonOp::FindControl( m_pm, _T("CheckAutoLogin") );
	CCheckBoxUI *pCheckRemPassWord = (CCheckBoxUI*)msg.pSender;
	if (pCheckAutoLogin && pCheckRemPassWord)
	{
		if (pCheckAutoLogin->GetCheck())
		{
			if ( !pCheckRemPassWord->GetCheck())
			{
				pCheckAutoLogin->Selected(false);
			}
		}
	}
	return true;
}

bool CMainFrameLogic::OnJoinConfReqChair( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	BOOL32 bChairCns = ComInterface->IsLocalCnsChairMan();
	if ( !bChairCns )//不是主席不响应
	{
		return false;
	}

	TTpConfEpInfo tInfo = ComInterface->GetJoinConfInfo();	

	CString strName = _T("");
	if( strcmp( tInfo.m_tCallAddr.m_tAlias.m_abyAlias, "" ) == 0 )
	{
		if (strcmp( tInfo.m_tCallAddr.m_tE164.m_abyAlias, "" ) == 0)
		{//ip最后
			in_addr tAddr;
			tAddr.S_un.S_addr = tInfo.m_tCallAddr.m_dwIP;
			String strIP = (CA2T)inet_ntoa(tAddr);
			if ( strIP == _T("0.0.0.0") )
			{
				strIP = _T("");
			}
			strName.Format(_T("是否允许%s加入会议"),strIP.c_str());
		}
		else//E164
		{
			strName.Format(_T("是否允许%s加入会议"),(CA2T)tInfo.m_tCallAddr.m_tE164.m_abyAlias);
		}
	}
	else//别名最先
	{
		strName.Format(_T("是否允许%s加入会议"),(CA2T)tInfo.m_tCallAddr.m_tAlias.m_abyAlias);
	}
	
	bool bRet = ShowMessageBox(strName,true);
	tInfo.m_bPermit = bRet;

	ComInterface->SetJoinConfInfo(tInfo);

	return true;
}

bool CMainFrameLogic::OnWBConfStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	if( UIDATAMGR->IsPcVersion() )//pc版不处理白板
	{
		return false;
	}

	bool bIsInWBConf = wParam;
	ComInterface->SetWBConfState( bIsInWBConf );

	return true;
}

bool CMainFrameLogic::OnNewConfCallReq( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	if( UIDATAMGR->IsPcVersion() )//pc版不处理白板
	{
		return false;
	}
	//不在数据会议中 不处理
	if ( !ComInterface->GetWBConfState() )
	{
		return false;
	}
	//cnc未显示 不弹窗
	if (!IWindowManager::GetSingletonPtr()->IsWindowVisible(_T("cnc")))
	{
		return false;
	}

	CString strMsg;
	strMsg.Format(_T("数据会议结束"));
	ShowPopMsg( strMsg );
	return true;
}

bool CMainFrameLogic::OnTpadLoginInfoNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	ComInterface->UpdateTpadLoginInfo();
    NOTIFY_MSG(UI_UMS_REFRESH_USER_LIST,wParam,lParam);
	return false;
}

bool CMainFrameLogic::OnContainerClick( TNotifyUI& msg )
{
	CCnsManageLogic::GetSingletonPtr()->UnSelScreenList();
	return true;
}

VOID  CALLBACK  CBTimerPoc( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{
	if ( idEvent == g_nMsgTimerID )
	{
		CMainFrameLogic::GetSingletonPtr()->UpdateMsgImg();
	}
	else if ( idEvent == g_nUpdateTimerID )
	{
		CMainFrameLogic::GetSingletonPtr()->UpdateTime();
		CUserDefinedLogic::GetSingletonPtr()->UpdateTime();
	}
	else if ( idEvent == g_nFreshConfStateTimerID )
	{
		ComInterface->FreshConf();
		KillTimer(NULL,g_nFreshConfStateTimerID);
		g_nFreshConfStateTimerID = 0;
	}
}

bool CMainFrameLogic::OnDisplayChange( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    //屏幕分辨率变化后刷新
    if( m_pm != NULL )
    {
        m_pm->UpdateLayout();
    } 
    return true;
}

bool CMainFrameLogic::OnCnsDisconnectNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	if( UIDATAMGR->IsPcVersion() )//pc版不处理此消息
	{
		return true;
	}

	BOOL bActiveExit = (BOOL)wParam;
	if ( !bActiveExit )
	{
		WINDOW_MGR_PTR->ShowModal(g_strReconnectBox.c_str());
	}
	else
	{
		//清空数据，退出到登陆界面
		NOTIFY_MSG( UI_DISCONNECTED_CLEARDATA );	
	}
	return true;
}

bool CMainFrameLogic::OnDisconnectClear( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	if ( UIDATAMGR->IsPcVersion())
	{
		//更新登录界面显示信息
		UpdateLoginShowInfo();

		ICncCommonOp::ShowControl( true, m_pm, _T("PageLogin") );
		ICncCommonOp::ShowControl( false, m_pm, _T("PageCnsManage") );
		WINDOW_MGR_PTR->ShowWindow( g_strMainMenuDlg.c_str(), false );
	}
	else
	{
		WINDOW_MGR_PTR->ShowWindow( g_stcStrMainFrameDlg.c_str(), false );
	}
	
	SetTitleTab( false );

	WINDOW_MGR_PTR->ShowWindow( g_strAddrbookDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strConfTempDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strRegServiceDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strRoomControlDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strConfCtrlDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strAddrEditDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strUserManagerDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strUserDefinedDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strConfCallCfgDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strConfMsgDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strSysConfigDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strLocalRoomCfgDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strSrcSelWatchDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strCalendarDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_stcStrCenterCtrlDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_stcStrDualViewDlg.c_str(),false);

	if ( m_pm != NULL )
	{
		m_pm->DoCase( _T("caseShowCnsManage") );
		//还原tab
		CPaintManagerUI* pm = CAddrEditLogic::GetSingletonPtr()->GetPaintManagerUI();
		CSlideTabLayoutUI *pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( pm, _T("AddrEditSlideTab") );
		if (pControl)
		{
			pControl->SelectItem(emTabID_Left);
		}
		pm = CAddrBookLogic::GetSingletonPtr()->GetPaintManagerUI();
		pControl = (CSlideTabLayoutUI*)ICncCommonOp::FindControl( pm, _T("AddrBookLayout") );
		if (pControl)
		{
			pControl->SelectItem(emTabID_Left);
		}
	}   

	if (g_nMsgTimerID != 0)
	{
		KillTimer(NULL,g_nMsgTimerID);
		g_nMsgTimerID = 0;
		ICncCommonOp::ShowControl(false,m_pm,_T("BtnTip"));
		ICncCommonOp::EnableControl( false, m_pm, _T("BtnTipBg") );
	}

	if (g_nUpdateTimerID != 0)
	{
		KillTimer(NULL,g_nUpdateTimerID);
		g_nUpdateTimerID = 0;
	}

	if (g_nFreshConfStateTimerID != 0)
	{
		KillTimer(NULL,g_nFreshConfStateTimerID);
		g_nFreshConfStateTimerID = 0;
	}

	m_bIsPadShowCenterOrSys = false;
	m_bMsgOn = FALSE;

	m_strLastWnd = _T("");
	UIDATAMGR->SetCurShowWndName(_T(""));
	//断链的时候保存一下快捷方式
	CMainMenuLogic::GetSingletonPtr()->SaveShortCutToIni();

	return true;
}