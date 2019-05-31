#include "StdAfx.h"
#include "sysconfiglogic.h"
#include "mainframelogic.h"
#include "userdefinedlogic.h"

APP_BEGIN_MSG_MAP(CSysConfigLogic,CNotifyUIImpl)

MSG_CLICK(_T("BtnBack"), OnBtnBack)
	MSG_CLICK(_T("BtnExit"), OnBtnExit)

	MSG_CREATEWINDOW(_T("SysConfigLayout"), OnCreate)
	MSG_INIWINDOW(_T("SysConfigLayout"), OnInit)

	MSG_CLICK(_T("BtnAddrManager"), OnBtnAddrManager)
	MSG_CLICK(_T("BtnUserManager"), OnBtnUserManager)
	MSG_CLICK(_T("lbUserManager"), OnBtnUserManager)
	MSG_CLICK(_T("BtnrConfCallCfg"), OnBtnConfCallCfg)
	MSG_CLICK(_T("BtnRoomControl"), OnBtnLocalRoomControl)
	MSG_CLICK(_T("BtnRegService"), OnBtnRegService)
	MSG_CLICK(_T("BtnUserDefined"), OnBtnUserDefined)

	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)

APP_END_MSG_MAP()

CSysConfigLogic::CSysConfigLogic(void)
{
}


CSysConfigLogic::~CSysConfigLogic(void)
{
}

bool CSysConfigLogic::OnCreate( TNotifyUI& msg )
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

bool CSysConfigLogic::OnInit( TNotifyUI& msg )
{
	return true;
}


bool CSysConfigLogic::OnBtnAddrManager( TNotifyUI& msg )
{
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight(g_strAddrEditDlg.c_str() );

	CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("地址簿管理"));
	CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgAddrbook.png"));
	CMainFrameLogic::GetSingletonPtr()->SetTitleTab( true, g_strAddrEditDlg.c_str() );
	WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
	UIDATAMGR->SetCurShowWndName( g_strAddrEditDlg );
	return true;
}

bool CSysConfigLogic::OnBtnUserManager( TNotifyUI& msg )
{
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight(g_strUserManagerDlg.c_str() );

	CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("用户管理"));
	CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgUserManage.png"));
	WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
	UIDATAMGR->SetCurShowWndName( g_strUserManagerDlg );
	return true;
}

bool CSysConfigLogic::OnBtnConfCallCfg( TNotifyUI& msg )
{
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight(g_strConfCallCfgDlg.c_str() );

	CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("会议呼叫设置"));
	CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgConfTemp.png"));
	WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
	UIDATAMGR->SetCurShowWndName( g_strConfCallCfgDlg );
	return true;
}

bool CSysConfigLogic::OnBtnLocalRoomControl( TNotifyUI& msg )
{
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight(g_strLocalRoomCfgDlg.c_str() );

	CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("本会场设置"));
	CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgRoomCtrl.png"));
	WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
	UIDATAMGR->SetCurShowWndName( g_strLocalRoomCfgDlg );
	return true;
}

bool CSysConfigLogic::OnBtnRegService( TNotifyUI& msg )
{
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight(g_strRegServiceDlg.c_str() );

	CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("服务器设置"));
	CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgServer.png"));
	WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
	UIDATAMGR->SetCurShowWndName( g_strRegServiceDlg );
	return true;
}

bool CSysConfigLogic::OnBtnUserDefined( TNotifyUI& msg )
{
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight(g_strUserDefinedDlg.c_str() );

	CMainFrameLogic::GetSingletonPtr()->SetTitle(_T("自定义设置"));
	CMainFrameLogic::GetSingletonPtr()->SetTitlePic(_T("res/title/imgSelfSet.png"));
	WINDOW_MGR_PTR->DoCase( g_stcStrMainFrameDlg.c_str(),_T("caseShowSubPage"));
	UIDATAMGR->SetCurShowWndName( g_strUserDefinedDlg );

    CUserDefinedLogic::GetSingletonPtr()->UpdateSuperadmin();
	return true;
}

bool CSysConfigLogic::OnBtnBack( TNotifyUI& msg )
{
	WINDOW_MGR_PTR->ShowWindowFromBottomToTop(g_strSysConfigDlg.c_str(),false );
	return true;
}

bool CSysConfigLogic::OnBtnExit( TNotifyUI& msg )
{
	WINDOW_MGR_PTR->ShowWindowFromBottomToTop(g_strSysConfigDlg.c_str(),false );
	return true;
}

bool CSysConfigLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	return true;
}