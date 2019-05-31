#include "StdAfx.h"
#include "contentreqlogic.h"
#include "conftemplogic.h"
#include "messageboxlogic.h"

APP_BEGIN_MSG_MAP(CContentReqLogic, CNotifyUIImpl)

	MSG_CREATEWINDOW(_T("contentreqLayout"), OnCreate)
	MSG_INIWINDOW(_T("contentreqLayout"), OnInit)
	MSG_WINDOWDESTORY(_T("contentreqLayout"), OnDestroy)

	MSG_CLICK(_T("BtnCancel"), OnBtnCancel)
	MSG_CLICK(_T("BtnOk"), OnBtnOk)
	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)

APP_END_MSG_MAP()

string g_strContentReq = "";

int showContentReq()
{
	return WINDOW_MGR_PTR->ShowWindow(g_strContentReqDlg.c_str());
}

CContentReqLogic::CContentReqLogic( void )
{
}


CContentReqLogic::~CContentReqLogic(void)
{
}


bool CContentReqLogic::OnCreate( TNotifyUI& msg )
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

bool CContentReqLogic::OnInit(TNotifyUI& msg)
{
    TTPAlias tTPAlias = CConfTempLogic::GetSingletonPtr()->GetCallTempName();
    ICncCommonOp::SetControlText(CA2T(tTPAlias.m_abyAlias), m_pm, _T("LabTempName"));
	return true;
}

bool CContentReqLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	WINDOW_MGR_PTR->CloseWindow(g_strContentReqDlg.c_str(),IDCANCEL);
	return NO_ERROR;
}

bool CContentReqLogic::OnBtnCancel( TNotifyUI& msg )
{
	WINDOW_MGR_PTR->CloseWindow(g_strContentReqDlg.c_str(),IDCANCEL);
	return true;
}

bool CContentReqLogic::OnBtnOk( TNotifyUI& msg )
{
    CEditUI* pEdContent = (CEditUI*)ICncCommonOp::FindControl(m_pm,_T("EditContent"));
    CString strContent = _T("");
    if (pEdContent)
    {
        strContent = pEdContent->GetText();
    }
    if (strContent.IsEmpty())
    {
        ShowMessageBox(_T("模板密码不可为空"));
        return false;
    }
    g_strContentReq = CT2A(strContent);
	WINDOW_MGR_PTR->CloseWindow(g_strContentReqDlg.c_str(),IDOK);
	return true;
}

bool CContentReqLogic::OnDestroy( TNotifyUI& msg )
{
	UNREG_CNC_MSG_WND_OB(m_pm->GetPaintWindow());
	return true;
}