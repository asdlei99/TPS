#include "StdAfx.h"
#include "filepreview.h"
#include "filemanager.h"

#define DEFAULT_TITLE_HEIGHT   79
template<> CFilePreviewLogic* Singleton<CFilePreviewLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CFilePreviewLogic,CNotifyUIImpl)

	MSG_CREATEWINDOW(_T("FilePreviewLayout"), OnCreate)
	MSG_INIWINDOW(_T("FilePreviewLayout"), OnInit)
	MSG_CLICK(_T("BtnPreviewBack"), OnBtnPreviewBack)

APP_END_MSG_MAP()


CFilePreviewLogic::CFilePreviewLogic(void)
{
}

CFilePreviewLogic::~CFilePreviewLogic(void)
{
	APIPreQuit();
}

bool CFilePreviewLogic::OnCreate(TNotifyUI& msg)
{
	REG_TPAD_MSG_WND_OB(m_pm->GetPaintWindow());
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

bool CFilePreviewLogic::OnInit(TNotifyUI& msg)
{
	return true;
}

bool CFilePreviewLogic::WindowPosSet(int X, int Y, int cx, int cy, UINT uFlags)
{
	s32 nTop = DEFAULT_TITLE_HEIGHT + Y;
	if ( CPaintManagerUI::IsSelfAdaption() )
	{
		float fAdpX, fAdpY;
		CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
		nTop = s32(nTop * fAdpY);
	}
	SetWindowPos( m_pm->GetPaintWindow(), NULL, X, nTop, cx, cy, uFlags );
	return true;
}

bool CFilePreviewLogic::OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	APIPreQuit();
	return true;
}

bool CFilePreviewLogic::OnBtnPreviewBack(TNotifyUI& msg)
{
	WINDOW_MGR_PTR->ShowWindow( g_strFilePreviewDlg.c_str(), false );
	return true;
}

const void CFilePreviewLogic::SetFilePath(const TCHAR* chFileName)
{
	APIPreQuit();
	APIPreInit(m_pm->GetPaintWindow());

	m_strFilePath.Empty();
	m_strFilePath.Format(_T("%s"),chFileName); 

 	char chRtn[MAX_PATH] = {0};
 	strncpy((LPSTR)chRtn, CT2A(chFileName), MAX_PATH); 

	if ( !m_strFilePath.IsEmpty() )
	{
		APIShowPre( chRtn, DEFAULT_TITLE_HEIGHT);
	}
}