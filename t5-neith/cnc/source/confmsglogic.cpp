#include "StdAfx.h"
#include "confmsglogic.h"


#define MAX_ALARM_SIZE    10
template<> CConfMsgDlgLogic* Singleton<CConfMsgDlgLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CConfMsgDlgLogic, CNotifyUIImpl)

	MSG_CREATEWINDOW(_T("ConfMsgLayout"), OnCreate)
	MSG_INIWINDOW(_T("ConfMsgLayout"), OnInit)
	MSG_ITEMSELECTD(_T("MsgList"), OnMsgListItemSelected)

	USER_MSG( UI_CNS_CONNECTED, OnConnectOk )
	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)
APP_END_MSG_MAP()


CConfMsgDlgLogic::CConfMsgDlgLogic(void)
{
	m_bLoginOK = FALSE;
	m_pMsgList = NULL;
}


CConfMsgDlgLogic::~CConfMsgDlgLogic(void)
{
}


bool CConfMsgDlgLogic::OnCreate( TNotifyUI& msg )
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

bool CConfMsgDlgLogic::OnInit(TNotifyUI& msg)
{
	return true;
}


bool CConfMsgDlgLogic::OnConnectOk( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_vctMsg.clear();

	//if ( IsWindowVisible(m_pm->GetPaintWindow()) )
	{
		WINDOW_MGR_PTR->ShowWindowFromBottomToTop( g_strConfMsgDlg.c_str(), false );
	}

	m_bLoginOK = (BOOL)wParam;

	return NO_ERROR;
}


bool CConfMsgDlgLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	if ( m_bLoginOK )
	{
		WINDOW_MGR_PTR->ShowWindowFromBottomToTop( g_strConfMsgDlg.c_str(), false );
		if (m_pMsgList)
		{
			m_pMsgList->RemoveAll();
		}
	}
	m_vctMsg.clear();
	m_bLoginOK = FALSE;

	return NO_ERROR;
}

void CConfMsgDlgLogic::AddMsg( CString strMsg, BOOL bShowNow )
{

	if ( m_vctMsg.size() >= MAX_ALARM_SIZE )
	{
		m_vctMsg.pop_back();
	}

	TConfMsg tConfMsg;
	tConfMsg.strMsg = strMsg;

	//系统消息前加上时间
	SYSTEMTIME st;
	GetLocalTime(&st);  
	CString strTime = _T("");
	strTime.Format(_T("%d-%d-%d   %.2d:%.2d:%.2d  "),st.wYear,st.wMonth,st.wDay, st.wHour, st.wMinute, st.wSecond );
	tConfMsg.strTime = strTime;

	m_vctMsg.insert( m_vctMsg.begin(), tConfMsg );

	UpdateMsgList();

	if ( bShowNow )
	{
		WINDOW_MGR_PTR->ShowWindowFromBottomToTop( g_strConfMsgDlg.c_str(), true );
	}
	else
	{
		NOTIFY_MSG( UI_CMS_SHOW_ALARM_DLG , 0 , 0 );
	}	
}

void CConfMsgDlgLogic::UpdateMsgList()
{

	m_pMsgList = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("MsgList"));
	CListUI *pTileLayoutUI = (CListUI*)ICncCommonOp::FindControl( m_pm, _T("MsgList") );
	if ( m_pMsgList == NULL )
	{
		return;
	}
	m_pMsgList->RemoveAll();
	for ( u16 i = 0; i < m_vctMsg.size(); i++ )
	{
		CListContainerElementUI *pListContainer = 
			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("ConfMsgListItem"));

		TConfMsg tConfMsg = m_vctMsg.at(i); 

		ICncCommonOp::SetControlText( tConfMsg.strMsg.c_str(), m_pm, _T("lbMsg"), pListContainer );

		ICncCommonOp::SetControlText( tConfMsg.strTime.c_str(), m_pm,  _T("lbTime"), pListContainer );

		m_pMsgList->Add(pListContainer);
		//m_pMsgList->AddAt(pListContainer,0);
	}

}

bool CConfMsgDlgLogic::OnMsgListItemSelected( TNotifyUI& msg )
{
	return false;
}

