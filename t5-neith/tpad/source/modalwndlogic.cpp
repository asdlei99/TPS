#include "StdAfx.h"
#include "modalwndlogic.h"

template<> CModalWndLogic* Singleton<CModalWndLogic>::ms_pSingleton  = NULL;

CString CModalWndLogic::m_strText = _T("");

APP_BEGIN_MSG_MAP(CModalWndLogic, CNotifyUIImpl)

	MSG_CREATEWINDOW(_T("ModalWndLayout"), OnCreate)
	MSG_INIWINDOW(_T("ModalWndLayout"), OnInit)
	MSG_WINDOWDESTORY(_T("ModalWndLayout"), OnDestroy)

	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)

APP_END_MSG_MAP()


CModalWndLogic::CModalWndLogic( void )
{
}


CModalWndLogic::~CModalWndLogic(void)
{
}


bool CModalWndLogic::OnCreate( TNotifyUI& msg )
{
	REG_TPAD_MSG_WND_OB(m_pm->GetPaintWindow());

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
	SetWindowPos( m_pm->GetPaintWindow(), NULL, nLeft, nTop, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );
	return false;
}

bool CModalWndLogic::OnInit(TNotifyUI& msg)
{
    ITPadCommonOp::SetControlText( m_strText, m_pm, _T("LabelTip") );
	return true;
}

bool CModalWndLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    m_strText = _T("");
    if ( WINDOW_MGR_PTR->IsWindowVisible(g_strModalDlg.c_str()) )
    {
	    WINDOW_MGR_PTR->HideWindow(g_strModalDlg.c_str());
	    WINDOW_MGR_PTR->CloseWindow(g_strModalDlg.c_str(),IDCANCEL);
    }

	CModalWndLogic::RemoveInstance();
	return NO_ERROR;
}

bool CModalWndLogic::OnDestroy( TNotifyUI& msg )
{
	UNREG_TPAD_MSG_WND_OB(m_pm->GetPaintWindow());
	return true;
}

bool CModalWndLogic::ShowModalWnd( LPCTSTR lpstrText )
{
    m_strText = lpstrText;
    return WINDOW_MGR_PTR->ShowModal(g_strModalDlg.c_str()); 
}

void CModalWndLogic::SetWndText( CString strText )
{
    m_strText = strText;
    ITPadCommonOp::SetControlText( strText, m_pm, _T("LabelTip") );
}

void CModalWndLogic::CloseModalWnd()
{
    if ( CModalWndLogic::GetSingletonPtr() != NULL )
    {
        WINDOW_MGR_PTR->CloseWindow(g_strModalDlg.c_str(),IDOK);
        CModalWndLogic::RemoveInstance();
    }  
}
