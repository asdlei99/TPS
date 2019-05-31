#include "StdAfx.h"
#include "aboutlogic.h"
#include "filepreview.h"
#include "messageboxlogic.h"


//lint -e309
//lint -e69      can't cast from int to struct
//lint -e78      Symbol XXX used in expression
//lint -e84      sizeof object is zero or object is undefined
//lint -e121     Attempting to initialize an object of undefined type 'void')
//lint -e1018    Expected a type after 'new'
//lint -e1043    Attempting to 'delete' a non-pointer
//lint -e1054    屏蔽pclint错误
//lint -e1072    Reference variable '' must be initialized

template<> CAboutLogic* Singleton<CAboutLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CAboutLogic,CNotifyUIImpl)

	MSG_CREATEWINDOW(_T("AboutLayout"), OnCreate)
	MSG_INIWINDOW(_T("AboutLayout"), OnInit)
	
	MSG_ITEMSELECTD(_T("AboutList"), OnFileItemClick)

	MSG_CLICK(_T("BtnBack"), OnBtnBack)
	MSG_CLICK(_T("BtnExit"), OnBtnExit)

	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)

APP_END_MSG_MAP()


CAboutLogic::CAboutLogic(void):m_bPreview(false)
{
}

CAboutLogic::~CAboutLogic(void)
{
}

bool CAboutLogic::OnCreate( TNotifyUI& msg )
{
	REG_TPAD_MSG_WND_OB(m_pm->GetPaintWindow());
	return false;
}

bool CAboutLogic::OnInit( TNotifyUI& msg )
{
	m_mapAboutFileList.insert(pair<CString,CString>( _T("常见问题"), _T("CommonProblems")));
	m_mapAboutFileList.insert(pair<CString,CString>( _T("快速指南"), _T("QuickGuide")));
	m_mapAboutFileList.insert(pair<CString,CString>( _T("帮助文档"), _T("HelpDocument")));

	UpdateShowFileList();
    UpdateShowTime();
	return true;
}

bool CAboutLogic::OnBtnBack(TNotifyUI& msg)
{
	if (m_bPreview)
	{
		m_bPreview = false;
		WINDOW_MGR_PTR->ShowWindow( g_strFilePreviewDlg.c_str(), false );
		APIPreQuit();

		CTouchListUI *pTileLayoutUI = (CTouchListUI*)ITPadCommonOp::FindControl( m_pm, _T("AboutList") );
		if ( pTileLayoutUI)
		{
			pTileLayoutUI->SelectItem(-1);
		}
		ITPadCommonOp::SetControlText(_T("帮助信息"), m_pm, _T("lbTitleName"));
	}
	else
	{
		WINDOW_MGR_PTR->ShowWindowFromLeftToRight( g_strAboutDlg.c_str(), false );
	}

	return NO_ERROR;
}

bool CAboutLogic::OnBtnExit(TNotifyUI& msg)
{
	if (m_bPreview)
	{
		m_bPreview = false;
		WINDOW_MGR_PTR->ShowWindow( g_strFilePreviewDlg.c_str(), false );
		APIPreQuit();

		ITPadCommonOp::SetControlText(_T("帮助信息"), m_pm, _T("lbTitleName"));
	}
	
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight( g_strAboutDlg.c_str(), false );
	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ITPadCommonOp::FindControl( m_pm, _T("AboutList") );
	if ( pTileLayoutUI)
	{
		pTileLayoutUI->SelectItem(-1);
	}

	return true;
}

void CAboutLogic::UpdateShowFileList()
{
	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ITPadCommonOp::FindControl( m_pm, _T("AboutList") );
	if ( pTileLayoutUI == NULL )
	{
		return;
	}
	pTileLayoutUI->RemoveAll();
	map<CString, CString>::iterator itFileMap = m_mapAboutFileList.begin(); 
	for ( ; itFileMap != m_mapAboutFileList.end(); itFileMap++ )
	{
		CListContainerElementUI *pListContainer = 
			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("AboutListItem") );

		ITPadCommonOp::SetControlText( itFileMap->first, m_pm, _T("FileItemName"), pListContainer );
		ITPadCommonOp::ShowControl(false, m_pm, _T("CheckBoxItemSel"), pListContainer);

		pTileLayoutUI->Add(pListContainer);
	}
}


bool CAboutLogic::OnFileItemClick( TNotifyUI& msg )
{
	int dwIndex = msg.wParam;
	CTouchListUI *pTileAboutLayoutUI = (CTouchListUI*)ITPadCommonOp::FindControl( m_pm, _T("AboutList") );
	wstring strkey = ITPadCommonOp::GetControlText( m_pm, _T("FileItemName"), 
		                                            pTileAboutLayoutUI->GetItemAt(dwIndex));
	map<CString, CString>::iterator itFileMap = m_mapAboutFileList.find(strkey.data()); 
	if (itFileMap == m_mapAboutFileList.end())
	{
		return false;
	}
	
	TCHAR Buffer[MAX_PATH];
	DWORD dwRet;
	dwRet = GetCurrentDirectory(MAX_PATH, Buffer);
	CString strExePath(Buffer);

	CString	strFilePath = _T("");
	strFilePath.Format(_T("%s\\help\\%s.pdf"), strExePath, itFileMap->second);

	BOOL32 bExist = PathFileExists( strFilePath );
	if ( !bExist ) 
	{
		ShowMessageBox((itFileMap->first + _T("暂不存在")));
		return NO_ERROR;
	}
	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ITPadCommonOp::FindControl( m_pm, _T("FileList") );
	if (pTileLayoutUI)
	{
		pTileLayoutUI->SelectItem(-1);
	}

	CFilePreviewLogic::GetSingletonPtr()->SetFilePath(strFilePath);
	//WINDOW_MGR_PTR->ShowWindowFromBottomToTop( g_strFilePreviewDlg.c_str(), true );
	WINDOW_MGR_PTR->ShowWindow(g_strFilePreviewDlg.c_str(), true );
	CFilePreviewLogic::GetSingletonPtr()->WindowPosSet(0, 0, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE);
	m_bPreview = true;
	

	ITPadCommonOp::SetControlText(itFileMap->first, m_pm, _T("lbTitleName"));

	return NOERROR;
}


void CAboutLogic::UpdateShowTime()
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
	String 	strlbDate = ITPadCommonOp::GetControlText(m_pm,_T("lbDate"));
	CString strOriDate(strlbDate.c_str());
	if ( strOriDate != strDate)
	{
		ITPadCommonOp::SetControlText(strDate, m_pm, _T("lbDate"));
	}

	ITPadCommonOp::SetControlText(strTime, m_pm, _T("lbTime"));
}
bool CAboutLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{	
	if (m_bPreview)
	{
		m_bPreview = false;
		WINDOW_MGR_PTR->ShowWindow( g_strFilePreviewDlg.c_str(), false );
		APIPreQuit();

		ITPadCommonOp::SetControlText(_T("帮助信息"), m_pm, _T("lbTitleName"));
	}
	WINDOW_MGR_PTR->ShowWindow( g_strAboutDlg.c_str(), false );

	return true;
}