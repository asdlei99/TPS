#include "StdAfx.h"
#include "mainmenulogic.h"
#include "messageboxlogic.h"


template<> CMainMenuLogic* Singleton<CMainMenuLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CMainMenuLogic, CNotifyUIImpl)
	MSG_CREATEWINDOW(_T("MainMenuLayout"), OnCreate)
	MSG_INIWINDOW(_T("MainMenuLayout"), OnInit)

    MSG_CLICK(_T("BtnCnsManage"), OnBtnCnsManage)
//    MSG_CLICK(_T("BtnCenterCtrl"), OnBtnCenterCtrl)
    MSG_CLICK(_T("BtnFileManage"), OnBtnFileManage)
    MSG_CLICK(_T("BtnBrowser"), OnBtnBrowser)
    MSG_CLICK(_T("BtnDataConf"), OnBtnDataConf)
    MSG_CLICK(_T("BtnWatchDual"), OnBtnWatchDual)

    USER_MSG(UI_CONFSTATE_NTY,OnConfStateNty)
	USER_MSG(UI_CNS_RECV_DUAL_NOTIFY,OnDualRecvStateNotify)
	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)
APP_END_MSG_MAP()



CMainMenuLogic::CMainMenuLogic(void)  : m_hWnd(NULL)
{
	m_bDual = false;
}


CMainMenuLogic::~CMainMenuLogic(void)
{
}

bool CMainMenuLogic::OnCreate( TNotifyUI& msg )
{
	REG_TPAD_MSG_WND_OB(m_pm->GetPaintWindow());

	HWND hWnd = m_pm->GetPaintWindow();
	LONG styleValue = ::GetWindowLong(hWnd, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(hWnd, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

    s32 nTop = 28;
    if ( CPaintManagerUI::IsSelfAdaption() )
    {
        float fAdpX, fAdpY;
        CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
        nTop = s32(nTop * fAdpY);
    }
    SetWindowPos( m_pm->GetPaintWindow(), NULL, 0, nTop, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );

	return false;
}

bool CMainMenuLogic::OnInit(TNotifyUI& msg)
{
	UpdateMainMenu();
	return true;
}

void CMainMenuLogic::UpdateMainMenu()
{
	if (ComInterface->IsManagerUser())
	{
		m_pm->DoCase(_T("caseAdmin"));
	}
	else
	{
		m_pm->DoCase(_T("caseNoAdmin"));
	}
}

bool CMainMenuLogic::OnBtnCnsManage( TNotifyUI& msg )
{
	if ( ComInterface->IsReceiveDual() )
	{
		return true;
	}

    ComInterface->OpenCnsManage();

	//调出cnc 2016-5-6 
// 	//会议管理
	TMainMenuInfo tMenuInfo;
	tMenuInfo.SetNull();
	memcpy(tMenuInfo.achName, MENU_CNSCONSOLE, sizeof(MENU_CNSCONSOLE)); 
	memcpy(tMenuInfo.achExePath, _T("cnc\\cnc.exe"), sizeof(_T("cnc\\cnc.exe")));
	memcpy(tMenuInfo.achExeCaption, _T("cnc"), sizeof(_T("cnc")));

	ComInterface->OpenExe( tMenuInfo );

	return true;
}

bool CMainMenuLogic::OnBtnCenterCtrl( TNotifyUI& msg )
{
	if ( ComInterface->IsReceiveDual() )
	{
		return true;
	}

	ComInterface->OpenCenterCtrl();

	//调出cnc 2016-5-6 
	//会议管理
	TMainMenuInfo tMenuInfo;
	tMenuInfo.SetNull();
	memcpy(tMenuInfo.achName, MENU_CNSCONSOLE, sizeof(MENU_CNSCONSOLE)); 
	memcpy(tMenuInfo.achExePath, _T("cnc\\cnc.exe"), sizeof(_T("cnc\\cnc.exe")));
	memcpy(tMenuInfo.achExeCaption, _T("cnc"), sizeof(_T("cnc")));

	ComInterface->OpenExe( tMenuInfo );
    return true;
}

bool CMainMenuLogic::OnBtnFileManage( TNotifyUI& msg )
{
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight( g_strFilemanagerDlg.c_str(), true );
    return true;
}

bool CMainMenuLogic::OnBtnBrowser( TNotifyUI& msg )
{
	if ( ComInterface->IsReceiveDual() )
	{
		return true;
	}

	TMainMenuInfo tMenuInfo;
	tMenuInfo.SetNull();
	memcpy(tMenuInfo.achName, MENU_IEXPLORE, sizeof(MENU_IEXPLORE)); 
	if ( ComInterface->Is64BitSystem() )//对操作系统类型进行判断，调用32位ie dyy 2013.7.4
	{
		memcpy(tMenuInfo.achExePath, _T("C:\\Program Files (x86)\\Internet Explorer\\IEXPLORE.EXE"), sizeof(_T("C:\\Program Files (x86)\\Internet Explorer\\IEXPLORE.EXE"))); 
	}
	else
	{
		memcpy(tMenuInfo.achExePath, _T("C:\\Program Files\\Internet Explorer\\IEXPLORE.EXE"), sizeof(_T("C:\\Program Files\\Internet Explorer\\IEXPLORE.EXE")));
	}
	
	memcpy(tMenuInfo.achExeClassName, _T("IEFrame"), sizeof(_T("IEFrame")));
	ComInterface->OpenExe( tMenuInfo );

    return true;
}

bool CMainMenuLogic::OnBtnDataConf( TNotifyUI& msg )
{
	WB_API_showDataConfWindow(TRUE);
    return true;
}

bool CMainMenuLogic::OnBtnWatchDual( TNotifyUI& msg )
{
	if( m_bDual )
	{ 
		//正在显示双流时做保护，防止连续点击观看演示
		if ( !ComInterface->IsReceiveDual() )
		{
			ComInterface->SetReceiveDual( TRUE );
			NOTIFY_MSG( WM_CMS_SHOWVIDEO, (WPARAM)TRUE , 0 );
		}
	}
	else
	{
		ShowMessageBox(_T("当前无演示"));
	}
    return true;
}

bool CMainMenuLogic::OnConfStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    TTPCnsConfStatus tconfState = ComInterface->GetLocalCnsConfState();
    if (tconfState.m_emTPEncryptType == emTPEncryptTypeQt)
    {
        CHorizontalLayoutUI* pParentAdmin = (CHorizontalLayoutUI*)ITPadCommonOp::FindControl(m_pm,_T("MainMenuBtnLayout1"));
        if (pParentAdmin)
        {
            ITPadCommonOp::EnableControl(false,m_pm,_T("BtnWatchDual"),pParentAdmin);
        }
        CHorizontalLayoutUI* pParentNotAdmin = (CHorizontalLayoutUI*)ITPadCommonOp::FindControl(m_pm,_T("MainMenuNoAdminLayout"));
        if (pParentNotAdmin)
        {
            ITPadCommonOp::EnableControl(false,m_pm,_T("BtnWatchDual"),pParentNotAdmin);
        }
    }
    else
    {
        CHorizontalLayoutUI* pParentAdmin = (CHorizontalLayoutUI*)ITPadCommonOp::FindControl(m_pm,_T("MainMenuBtnLayout1"));
        if (pParentAdmin)
        {
            ITPadCommonOp::EnableControl(true,m_pm,_T("BtnWatchDual"),pParentAdmin);
        }
        CHorizontalLayoutUI* pParentNotAdmin = (CHorizontalLayoutUI*)ITPadCommonOp::FindControl(m_pm,_T("MainMenuNoAdminLayout"));
        if (pParentNotAdmin)
        {
            ITPadCommonOp::EnableControl(true,m_pm,_T("BtnWatchDual"),pParentNotAdmin);
        }
    }
    return NO_ERROR;
}

bool CMainMenuLogic::OnDualRecvStateNotify(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	m_bDual = (BOOL32)wParam;

	if (ComInterface->IsManagerUser())//管理员默认不自动显示双流
	{
		return true;
	}

	//tpad界面收到双流直接显示
	if ( m_bDual )
	{
		//B4收到双流后直接显示
		LPCWSTR className = NULL;
		LPCWSTR windName = _T("cnc");

		HWND hWnd = ::FindWindow( className , windName );
		if ( IsWindow( hWnd ) )
		{
			if ( ::IsWindowVisible( hWnd ) )
			{
				//若cnc显示 隐藏掉 2016-2-2
				::ShowWindow( hWnd, SW_HIDE );
			}         
		}

		ComInterface->SetReceiveDual( TRUE );
		NOTIFY_MSG( WM_CMS_SHOWVIDEO, (WPARAM)TRUE , 0 );
	}

	return NO_ERROR;
}

bool CMainMenuLogic::OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	m_bDual = false;
	ComInterface->SetReceiveDual( FALSE );
	return true;
}
