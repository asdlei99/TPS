#include "StdAfx.h"
#include "reconnectlogic.h"


APP_BEGIN_MSG_MAP(CReconnectLogic, CNotifyUIImpl)

	MSG_CREATEWINDOW(_T("ReconnectBoxLayout"), OnCreate)
	MSG_INIWINDOW(_T("ReconnectBoxLayout"), OnInit)
	MSG_WINDOWDESTORY(_T("ReconnectBoxLayout"), OnDestroy)
	MSG_CLICK(_T("BtnExit"), OnBtnExit)

	USER_MSG( UI_CNS_CONNECTED, OnConnectRsp )
	USER_MSG( UI_DISCONNECTED_CLEARDATA, OnDisconnectClear )

APP_END_MSG_MAP()

CReconnectLogic::CReconnectLogic(void)
{
}

CReconnectLogic::~CReconnectLogic(void)
{
}

bool CReconnectLogic::OnCreate( TNotifyUI& msg )
{
	REG_CNC_MSG_WND_OB(m_pm->GetPaintWindow());

	s32 nTop = 0;
	RECT rcParent;
	HWND hparent = GetParent(m_pm->GetPaintWindow());
	GetWindowRect(hparent,&rcParent);
	SIZE szDlg = m_pm->GetInitSize();
	s32 nLeft = (rcParent.right - rcParent.left - szDlg.cx)/2;
	nTop = (rcParent.bottom - rcParent.top - szDlg.cy)/2;
	if ( CPaintManagerUI::IsSelfAdaption() )
	{
		float fAdpX, fAdpY;
		CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
		nTop = s32(nTop * fAdpY);
		nLeft = s32(nLeft * fAdpY);
	}
	SetWindowPos( m_pm->GetPaintWindow(), HWND_TOPMOST, nLeft, nTop, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );
	return false;
}

bool CReconnectLogic::OnInit(TNotifyUI& msg)
{
	return true;
}

bool CReconnectLogic::OnDestroy( TNotifyUI& msg )
{
	UNREG_CNC_MSG_WND_OB(m_pm->GetPaintWindow());
	return true;
}

bool CReconnectLogic::OnBtnExit(TNotifyUI& msg)
{
	ComInterface->NotifyTPadNoReconnect();

	//清空数据，退出到登陆界面
	NOTIFY_MSG( UI_DISCONNECTED_CLEARDATA );
	WINDOW_MGR_PTR->CloseWindow(g_strReconnectBox.c_str(),IDOK);
	return true;
}


bool CReconnectLogic::OnConnectRsp( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	if (wParam != TRUE)
	{
		return false;	
	}

	WINDOW_MGR_PTR->CloseWindow(g_strReconnectBox.c_str(),IDCANCEL);
	return true;
}

bool CReconnectLogic::OnDisconnectClear(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	WINDOW_MGR_PTR->CloseWindow(g_strReconnectBox.c_str(),IDCANCEL);
	return true;
}
