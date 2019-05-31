#include "StdAfx.h"
#include "toolwindowlogic.h"
#include "filemanager.h"
#include <io.h>

APP_BEGIN_MSG_MAP(CToolWindowLogic, CNotifyUIImpl)

	MSG_CREATEWINDOW(_T("ToolWindowLayout"), OnCreate)
	MSG_INIWINDOW(_T("ToolWindowLayout"), OnInit)
	MSG_WINDOWDESTORY(_T("ToolWindowLayout"), OnDestroy)
	MSG_CLICK(_T("BtnPageChange"), OnBtnPageChange)
	MSG_CLICK(_T("ToolWindowLayout"), OnBtnPageChange)

APP_END_MSG_MAP()

static bool    m_bIsPageChange = false;
static bool    m_bIsKeyBoard = false;
void ToolWindowreSet(bool bIsNextPage /*= false*/, bool bIsKeyBoard /*= false*/)
{
	m_bIsPageChange = bIsNextPage;
	m_bIsKeyBoard = bIsKeyBoard;
}

CToolWindowLogic::CToolWindowLogic( void )
{
	m_bLButtonDown = false;
	m_ptDown.x = -1;
	m_ptDown.y = -1;	
}


CToolWindowLogic::~CToolWindowLogic(void)
{
}


bool CToolWindowLogic::OnCreate( TNotifyUI& msg )
{
	m_bIsPrePage = m_bIsPageChange;
	m_bIsKeyBoardWnd = m_bIsKeyBoard;
	REG_TPAD_MSG_WND_OB(m_pm->GetPaintWindow());

	s32 nTop = 0;
	s32 nLeft = 0;
	SIZE szDlg = m_pm->GetInitSize();

	if (m_bIsKeyBoardWnd)
	{
		nTop = GetSystemMetrics(SM_CYSCREEN) - 5*szDlg.cy;
		nLeft = GetSystemMetrics(SM_CXSCREEN)  - 2*szDlg.cx;
		::SetWindowPos( m_pm->GetPaintWindow(), HWND_TOPMOST, nLeft, nTop, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOACTIVATE);
		return false;
	}
	else
	{
		RECT rcParent;
		HWND hparent = GetParent(m_pm->GetPaintWindow());
		GetWindowRect(hparent,&rcParent);

		nTop = (rcParent.bottom - rcParent.top - szDlg.cy)/2;
		if (m_bIsPrePage)
		{
			nLeft = rcParent.left + szDlg.cx;
		}
		else
		{
			nLeft = rcParent.right  - 2*szDlg.cx;
		}
	}

	SetWindowPos( m_pm->GetPaintWindow(), NULL, nLeft, nTop, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );
	return false;
}

bool CToolWindowLogic::OnInit(TNotifyUI& msg)
{
	CButtonUI* pbtn = (CButtonUI*)ITPadCommonOp::FindControl(m_pm, _T("BtnPageChange"));
	if (!pbtn)
	{
		return false;
	}

	if (m_bIsKeyBoardWnd)
	{
		m_pm->DoCase(_T("keyboard"));
		return true;
	}
	
	if (!m_bIsPrePage)
	{
		pbtn->SetAttribute(_T("normalimage"),_T("res/public/pagechangebtn/next.png"));
		pbtn->SetAttribute(_T("hotimage"),_T("res//public/pagechangebtn/next_down.png"));
		pbtn->SetAttribute(_T("pushedimage"),_T("res//public/pagechangebtn/next_down.png"));
	}

	return true;
}


bool CToolWindowLogic::OnDestroy( TNotifyUI& msg )
{
	UNREG_TPAD_MSG_WND_OB(m_pm->GetPaintWindow());
	return true;
}

bool CToolWindowLogic::OnBtnPageChange(TNotifyUI& msg)
{
	if (m_bIsKeyBoardWnd)
	{
		ShowKeyboard();
		return true;
	}

	CFileManagerLogic::GetSingleton().PageChange(m_bIsPrePage);

	return true;
}

LRESULT CToolWindowLogic::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if (!m_bIsKeyBoardWnd)
	{
		return 0;
	}

	LRESULT lRes = 0;
	switch (uMsg)
	{
	case WM_LBUTTONUP:		lRes = OnLButtonUp(uMsg, wParam, lParam, bHandled); break;
	case WM_LBUTTONDOWN:	lRes = OnLButtonDown(uMsg, wParam, lParam, bHandled); break;
	case WM_MOUSEMOVE:		lRes = OnMouseMove(uMsg, wParam, lParam, bHandled); break;
	}

	return lRes;
}

LRESULT CToolWindowLogic::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	m_bLButtonDown = true;
	CPoint point;
	GetCursorPos( &point );
	m_ptDown = point;
	bHandled = FALSE;
	return 0;
}

LRESULT CToolWindowLogic::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	ReleaseCapture();//不release一下一直获得消息 dyy 2014-6-16
	m_bLButtonDown = false;
	CPoint point;
	GetCursorPos( &point );
	if ( m_ptDown == point )
	{
		bHandled = FALSE;
		return 0;
	}
	else
	{
		bHandled = TRUE;
		return 0;
	}
	return 0;
}

LRESULT CToolWindowLogic::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if ( !m_bLButtonDown )
	{
		bHandled = FALSE;
		return 0;
	}

	CPoint point;
	CRect rcWindow;
	GetWindowRect( m_pm->GetPaintWindow(), &rcWindow);

	GetCursorPos( &point );
	int nX = point.x - rcWindow.Width()/2 > 0 ? point.x - rcWindow.Width()/2 : 0;
	int nY = point.y - rcWindow.Height()/2 > 0 ? point.y - rcWindow.Height()/2 : 0;
	::SetWindowPos( m_pm->GetPaintWindow(), NULL, nX, nY, 0, 0,  SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOACTIVATE );
	bHandled = FALSE; // Leave the message to next case  
	return 0; 
}

void CToolWindowLogic::ShowKeyboard()
{
	ComInterface->ShowKeyboard();
}

