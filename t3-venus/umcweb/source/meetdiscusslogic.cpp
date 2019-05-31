// meetdiscusslogic.cpp : implementation file
//
#include "stdafx.h"
#include "umcwebproj.h"
#include "meetdiscusslogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern float CUR_SCREEN_WIDTH_PER;  //屏幕宽度比率
extern float CUR_SCREEN_HEIGHT_PER; //屏幕高度比率

CRITICAL_SECTION g_csLockDiscuss;
/////////////////////////////////////////////////////////////////////////////
// CMeetDiscussLogic dialog
CMeetDiscussLogic::CMeetDiscussLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CMeetDiscussLogic::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMeetDiscussLogic)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_emOperateFlag = em_SCANF_PAGE_STATUS;
	m_bSwitchDiscuss = FALSE;

	m_rectGroup1 = CRect( 0, 0, 0, 0 );
	m_rectGroup2 = CRect( 0, 0, 0, 0 );
	m_rectGroup3 = CRect( 0, 0, 0, 0 );
	m_rectGroup4 = CRect( 0, 0, 0, 0 );

	::InitializeCriticalSection(&g_csLockDiscuss);
}

void CMeetDiscussLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMeetDiscussLogic)
	DDX_Control(pDX, IDC_STATIC_DISCUSS, m_stDiscuss);
	DDX_Control(pDX, IDC_STATIC_GROUP1, m_stGroup1);
	DDX_Control(pDX, IDC_STATIC_GROUP2, m_stGroup2);
	DDX_Control(pDX, IDC_STATIC_GROUP3, m_stGroup3);
	DDX_Control(pDX, IDC_STATIC_GROUP4, m_stGroup4);
	DDX_Control(pDX, IDC_STATIC_TGroup1, m_stGroupShow1);
	DDX_Control(pDX, IDC_STATIC_TGroup2, m_stGroupShow2);
	DDX_Control(pDX, IDC_STATIC_TGroup3, m_stGroupShow3);
	DDX_Control(pDX, IDC_STATIC_TGroup4, m_stGroupShow4);
	DDX_Control(pDX, IDC_EditGroup1, m_etGroup1);
	DDX_Control(pDX, IDC_EditGroup2, m_etGroup2);
	DDX_Control(pDX, IDC_EditGroup3, m_etGroup3);
	DDX_Control(pDX, IDC_EditGroup4, m_etGroup4);
	DDX_Control(pDX, IDC_BtnDiscuss, m_btnSwitchDiscuss);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMeetDiscussLogic, CDlgChild)
	//{{AFX_MSG_MAP(CMeetDiscussLogic)
	ON_WM_DESTROY()
	ON_MESSAGE( WM_BUTTON_CLICK, OnClickSwitchBtn )
	ON_MESSAGE( UI_EDITDELETE_CLICK, OnClickEditDel )
	ON_MESSAGE( UI_DRAG_END, OnDragEnd )
//	ON_MESSAGE( UI_DRAG_OVER, OnDragOver )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMeetDiscussLogic message handlers
void CMeetDiscussLogic::RegisterFun()
{
}

BOOL CMeetDiscussLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();
	
	RegisterFun();
	
	if ( !InitControlPane() )
	{
		return FALSE;
	}

	CDragWindow* pDragWindow = CDragWindow::GetDragWindow();
	if ( NULL != pDragWindow )
    {
		pDragWindow->RegisterDropWindow( (CWnd*)this );
    }
	
	return TRUE;
}

void CMeetDiscussLogic::InitDlg() 
{
	m_mapDiscussSelItem.clear();
	UpdateDiscussEdit( m_mapDiscussSelItem, FALSE, em_SCANF_PAGE_STATUS );
}

void CMeetDiscussLogic::OnDestroy() 
{
	CDlgChild::OnDestroy();
	
	::DeleteCriticalSection(&g_csLockDiscuss);
}

BOOL CMeetDiscussLogic::InitControlPane()
{
	CUmcwebCommon::SetTextTransStatic( &m_stDiscuss, "会议讨论" );
	CUmcwebCommon::SetTextTransStatic( &m_stGroup1, "会场" );
	CUmcwebCommon::SetTextTransStatic( &m_stGroup2, "会场" );
	CUmcwebCommon::SetTextTransStatic( &m_stGroup3, "会场" );
	CUmcwebCommon::SetTextTransStatic( &m_stGroup4, "会场" );
	CUmcwebCommon::SetTextTransStatic( &m_stGroupShow1, "" );
	CUmcwebCommon::SetTextTransStatic( &m_stGroupShow2, "" );
	CUmcwebCommon::SetTextTransStatic( &m_stGroupShow3, "" );
	CUmcwebCommon::SetTextTransStatic( &m_stGroupShow4, "" );

	//浏览控件
	CRect rectClient;
	this->GetClientRect(&rectClient);

	m_stDiscuss.SetWindowPos( NULL, 0,  9, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stGroup1.SetWindowPos( NULL, 0,  (18 + 27)*CUR_SCREEN_HEIGHT_PER + 9, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );	
	m_stGroup2.SetWindowPos( NULL, 0,  2*(18 + 27)*CUR_SCREEN_HEIGHT_PER + 9, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );	
	m_stGroup3.SetWindowPos( NULL, 0,  3*(18 + 27)*CUR_SCREEN_HEIGHT_PER + 9, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );	
	m_stGroup4.SetWindowPos( NULL, 0,  4*(18 + 27)*CUR_SCREEN_HEIGHT_PER + 9, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );	

	m_stGroupShow1.SetWindowPos( NULL, 125*CUR_SCREEN_WIDTH_PER,  (18 + 27)*CUR_SCREEN_HEIGHT_PER + 9, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );	
	m_stGroupShow2.SetWindowPos( NULL, 125*CUR_SCREEN_WIDTH_PER,  2*(18 + 27)*CUR_SCREEN_HEIGHT_PER + 9, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );	
	m_stGroupShow3.SetWindowPos( NULL, 125*CUR_SCREEN_WIDTH_PER,  3*(18 + 27)*CUR_SCREEN_HEIGHT_PER + 9, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );	
	m_stGroupShow4.SetWindowPos( NULL, 125*CUR_SCREEN_WIDTH_PER,  4*(18 + 27)*CUR_SCREEN_HEIGHT_PER + 9, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );	

	CUmcwebCommon::SetImgForTransEdit(&m_etGroup1, FALSE);
	m_etGroup1.SetWindowPos( NULL, 113*CUR_SCREEN_WIDTH_PER,  (18 + 27)*CUR_SCREEN_HEIGHT_PER, 390*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_etGroup1.SetLimitLength(31);

	CUmcwebCommon::SetImgForTransEdit(&m_etGroup2, FALSE);
	m_etGroup2.SetWindowPos( NULL, 113*CUR_SCREEN_WIDTH_PER,  2*(18 + 27)*CUR_SCREEN_HEIGHT_PER, 390*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_etGroup2.SetLimitLength(31);

	CUmcwebCommon::SetImgForTransEdit(&m_etGroup3, FALSE);
	m_etGroup3.SetWindowPos( NULL, 113*CUR_SCREEN_WIDTH_PER,  3*(18 + 27)*CUR_SCREEN_HEIGHT_PER, 390*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_etGroup3.SetLimitLength(31);

	CUmcwebCommon::SetImgForTransEdit(&m_etGroup4, FALSE);
	m_etGroup4.SetWindowPos( NULL, 113*CUR_SCREEN_WIDTH_PER,  4*(18 + 27)*CUR_SCREEN_HEIGHT_PER, 390*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_etGroup4.SetLimitLength(31);

	m_btnSwitchDiscuss.SetImage( IDR_PNG_LOGINWND_BTN_ON, IDR_PNG_LOGINWND_BTN_ONDOWN, IDR_PNG_LOGINWND_BTN_ONDIS,
        IDR_PNG_LOGINWND_BTN_OFF,IDR_PNG_LOGINWND_BTN_OFFDOWN, IDR_PNG_LOGINWND_BTN_OFFDIS);
	m_btnSwitchDiscuss.SetWindowPos( NULL, 388*CUR_SCREEN_WIDTH_PER, 0, 113*CUR_SCREEN_WIDTH_PER, 37*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_btnSwitchDiscuss.EnableWindow(FALSE);

	HWND hWndEditGroup = NULL;
	CWnd* pWndEditGroup = NULL;

	hWndEditGroup = m_etGroup1.GetSafeHwnd();
	if ( NULL != hWndEditGroup )
	{
		pWndEditGroup = CWnd::FromHandle(hWndEditGroup);
		if ( NULL != pWndEditGroup )
		{
			pWndEditGroup->GetWindowRect(&m_rectGroup1);
		}
	}

	hWndEditGroup = m_etGroup2.GetSafeHwnd();
	if ( NULL != hWndEditGroup )
	{
		pWndEditGroup = CWnd::FromHandle(hWndEditGroup);
		if ( NULL != pWndEditGroup )
		{
			pWndEditGroup->GetWindowRect(&m_rectGroup2);
		}
	}

	hWndEditGroup = m_etGroup3.GetSafeHwnd();
	if ( NULL != hWndEditGroup )
	{
		pWndEditGroup = CWnd::FromHandle(hWndEditGroup);
		if ( NULL != pWndEditGroup )
		{
			pWndEditGroup->GetWindowRect(&m_rectGroup3);
		}
	}

	hWndEditGroup = m_etGroup4.GetSafeHwnd();
	if ( NULL != hWndEditGroup )
	{
		pWndEditGroup = CWnd::FromHandle(hWndEditGroup);
		if ( NULL != pWndEditGroup )
		{
			pWndEditGroup->GetWindowRect(&m_rectGroup4);
		}
	}

	ScreenToClient(&m_rectGroup1);
	ScreenToClient(&m_rectGroup2);
	ScreenToClient(&m_rectGroup3);
	ScreenToClient(&m_rectGroup4);

	return TRUE;
}

LRESULT CMeetDiscussLogic::OnClickSwitchBtn(WPARAM wParam, LPARAM lParam) 
{
	m_bSwitchDiscuss = m_btnSwitchDiscuss.GetSwitchState();

	//需求确认,off时也可编辑  -- 20140408
// 	m_etGroup1.EnableWindow(m_bSwitchDiscuss);
// 	m_etGroup2.EnableWindow(m_bSwitchDiscuss);
// 	m_etGroup3.EnableWindow(m_bSwitchDiscuss);
// 	m_etGroup4.EnableWindow(m_bSwitchDiscuss);

	GetParent()->SendMessage( WM_DEF_SWITCH_DISCUSS, (WPARAM)(LPCTSTR)m_bSwitchDiscuss, 0 );

	return 0L;
}

LRESULT CMeetDiscussLogic::OnClickEditDel(WPARAM wParam, LPARAM lParam) 
{
	u16 wIndex = TP_CONF_MAX_AUDMIXNUM;
	if ( m_etGroup1.IsFocus() )
	{
		wIndex = 0;		
	}
	else if ( m_etGroup2.IsFocus() )
	{
		wIndex = 1;
	}
	else if ( m_etGroup3.IsFocus() )
	{
		wIndex = 2;
	}
	else if ( m_etGroup4.IsFocus() )
	{
		wIndex = 3;
	}

	EnterCriticalSection(&g_csLockDiscuss);
	m_mapDiscussSelItem.erase(wIndex);
	m_mapDiscussSelItem.insert( std::make_pair<u16,CString>(wIndex, "") );
	LeaveCriticalSection(&g_csLockDiscuss);

	GetParent()->SendMessage( WM_DEF_CHANGE_DISCUSSEP, (WPARAM)&m_mapDiscussSelItem, 0 );

	return 0L;
}

void CMeetDiscussLogic::UpdateDiscussEdit( std::map<u16,CString>& mapDiscussSelItem, BOOL bSwitchDiscuss, EM_OPERATE_FLAG emOperateFlag )
{
	if ( m_bSwitchDiscuss != bSwitchDiscuss )
	{
		m_bSwitchDiscuss = bSwitchDiscuss;
		m_btnSwitchDiscuss.SetSwitchState( m_bSwitchDiscuss );
//		OnClickSwitchBtn( 0, 0 );
	}
	
	m_emOperateFlag = emOperateFlag;
	
	UpdateUIState();

	m_etGroup1.SetWindowText("");
	m_etGroup2.SetWindowText("");
	m_etGroup3.SetWindowText("");
	m_etGroup4.SetWindowText("");
	m_stGroupShow1.SetWindowText("");
	m_stGroupShow2.SetWindowText("");
	m_stGroupShow3.SetWindowText("");
	m_stGroupShow4.SetWindowText("");

	EnterCriticalSection(&g_csLockDiscuss);
	m_mapDiscussSelItem.clear();
	m_mapDiscussSelItem = mapDiscussSelItem;
	LeaveCriticalSection(&g_csLockDiscuss);

	std::map<u16,CString>::iterator iter;
	for ( iter = m_mapDiscussSelItem.begin(); iter != m_mapDiscussSelItem.end(); iter++ )
	{
		u16 wIndex = iter->first;
		CString strDiscussSelItem = iter->second;

		switch( wIndex )
		{
		case 0:
			{
				m_etGroup1.SetWindowText(strDiscussSelItem);
				m_stGroupShow1.SetWindowText(strDiscussSelItem);
			}
			break;
		case 1:
			{
				m_etGroup2.SetWindowText(strDiscussSelItem);
				m_stGroupShow2.SetWindowText(strDiscussSelItem);
			}
			break;
		case 2:
			{
				m_etGroup3.SetWindowText(strDiscussSelItem);
				m_stGroupShow3.SetWindowText(strDiscussSelItem);
			}
			break;
		case 3:
			{
				m_etGroup4.SetWindowText(strDiscussSelItem);
				m_stGroupShow4.SetWindowText(strDiscussSelItem);
			}
			break;
		default:
			break;
		}
	}
}

void CMeetDiscussLogic::UpdateUIState()
{
	if ( em_SCANF_PAGE_STATUS == m_emOperateFlag )
	{
		m_stGroupShow1.ShowWindow(SW_SHOW);
		m_stGroupShow2.ShowWindow(SW_SHOW);
		m_stGroupShow3.ShowWindow(SW_SHOW);
		m_stGroupShow4.ShowWindow(SW_SHOW);
		
		m_etGroup1.ShowWindow(SW_HIDE);
		m_etGroup2.ShowWindow(SW_HIDE);
		m_etGroup3.ShowWindow(SW_HIDE);
		m_etGroup4.ShowWindow(SW_HIDE);
		
		m_btnSwitchDiscuss.EnableWindow(FALSE);
	} 
	else
	{
		m_stGroupShow1.ShowWindow(SW_HIDE);
		m_stGroupShow2.ShowWindow(SW_HIDE);
		m_stGroupShow3.ShowWindow(SW_HIDE);
		m_stGroupShow4.ShowWindow(SW_HIDE);
		
		m_etGroup1.ShowWindow(SW_SHOW);
		m_etGroup2.ShowWindow(SW_SHOW);
		m_etGroup3.ShowWindow(SW_SHOW);
		m_etGroup4.ShowWindow(SW_SHOW);

		//需求确认,off时也可编辑  -- 20140408
// 		m_etGroup1.EnableWindow(m_bSwitchDiscuss);
// 		m_etGroup2.EnableWindow(m_bSwitchDiscuss);
// 		m_etGroup3.EnableWindow(m_bSwitchDiscuss);
// 		m_etGroup4.EnableWindow(m_bSwitchDiscuss);
		
		m_btnSwitchDiscuss.EnableWindow(TRUE);
	}
}

void CMeetDiscussLogic::HideAllPageCtrl()
{
	m_stDiscuss.ShowWindow(SW_HIDE);
	
	m_stGroup1.ShowWindow(SW_HIDE);
	m_stGroup2.ShowWindow(SW_HIDE);
	m_stGroup3.ShowWindow(SW_HIDE);
	m_stGroup4.ShowWindow(SW_HIDE);
	
	m_stGroupShow1.ShowWindow(SW_HIDE);
	m_stGroupShow2.ShowWindow(SW_HIDE);
	m_stGroupShow3.ShowWindow(SW_HIDE);
	m_stGroupShow4.ShowWindow(SW_HIDE);

	m_etGroup1.ShowWindow(SW_HIDE);
	m_etGroup2.ShowWindow(SW_HIDE);
	m_etGroup3.ShowWindow(SW_HIDE);
	m_etGroup4.ShowWindow(SW_HIDE);
}

BOOL CMeetDiscussLogic::AddToEpEdit( const CString& strEpName )
{
	if ( 0 == m_mapDiscussSelItem.size() )
	{
		EnterCriticalSection(&g_csLockDiscuss);
		m_mapDiscussSelItem.insert( std::make_pair<u16,CString>(0, "") );
		m_mapDiscussSelItem.insert( std::make_pair<u16,CString>(1, "") );
		m_mapDiscussSelItem.insert( std::make_pair<u16,CString>(2, "") );
		m_mapDiscussSelItem.insert( std::make_pair<u16,CString>(3, "") );
		LeaveCriticalSection(&g_csLockDiscuss);
	}

	BOOL bAdd = FALSE;
	u16 wIndex = TP_CONF_MAX_AUDMIXNUM;
	std::map<u16,CString>::iterator iter;
	if ( m_etGroup1.IsFocus() )
	{
		wIndex = 0;
		iter = m_mapDiscussSelItem.find(wIndex);
		if ( strcmp( iter->second, "" ) != 0 )
		{
			EnterCriticalSection(&g_csLockDiscuss);
			m_mapDiscussSelItem.erase(wIndex);
			m_mapDiscussSelItem.insert( std::make_pair<u16,CString>(wIndex, "") );
			LeaveCriticalSection(&g_csLockDiscuss);
		}

		m_etGroup1.SetWindowText(strEpName);
		bAdd = TRUE;
	}
	else if ( m_etGroup2.IsFocus() )
	{
		wIndex = 1;
		iter = m_mapDiscussSelItem.find(wIndex);
		if ( strcmp( iter->second, "" ) != 0 )
		{
			EnterCriticalSection(&g_csLockDiscuss);
			m_mapDiscussSelItem.erase(wIndex);
			m_mapDiscussSelItem.insert( std::make_pair<u16,CString>(wIndex, "") );
			LeaveCriticalSection(&g_csLockDiscuss);
		}
		
		m_etGroup2.SetWindowText(strEpName);
		bAdd = TRUE;
	}
	else if ( m_etGroup3.IsFocus() )
	{
		wIndex = 2;
		iter = m_mapDiscussSelItem.find(wIndex);
		if ( strcmp( iter->second, "" ) != 0 )
		{
			EnterCriticalSection(&g_csLockDiscuss);
			m_mapDiscussSelItem.erase(wIndex);
			m_mapDiscussSelItem.insert( std::make_pair<u16,CString>(wIndex, "") );
			LeaveCriticalSection(&g_csLockDiscuss);
		}
		
		m_etGroup3.SetWindowText(strEpName);
		bAdd = TRUE;
	}
	else if ( m_etGroup4.IsFocus() )
	{
		wIndex = 3;
		iter = m_mapDiscussSelItem.find(wIndex);
		if ( strcmp( iter->second, "" ) != 0 )
		{
			EnterCriticalSection(&g_csLockDiscuss);
			m_mapDiscussSelItem.erase(wIndex);
			m_mapDiscussSelItem.insert( std::make_pair<u16,CString>(wIndex, "") );
			LeaveCriticalSection(&g_csLockDiscuss);
		}
		
		m_etGroup4.SetWindowText(strEpName);
		bAdd = TRUE;
	}
	else
	{
		for ( iter = m_mapDiscussSelItem.begin(); iter != m_mapDiscussSelItem.end(); iter++ )
		{
			wIndex = iter->first;
			CString strGroupName = iter->second;

			if ( strcmp( strGroupName, "" ) == 0 )
			{
				bAdd = TRUE;
				switch ( wIndex )
				{
				case 0:
					{
						m_etGroup1.SetWindowText(strEpName);
						m_etGroup1.SetFocus();
					}
					break;
				case 1:
					{
						m_etGroup2.SetWindowText(strEpName);
						m_etGroup2.SetFocus();
					}
					break;
				case 2:
					{
						m_etGroup3.SetWindowText(strEpName);
						m_etGroup3.SetFocus();
					}
					break;
				case 3:
					{
						m_etGroup4.SetWindowText(strEpName);
						m_etGroup4.SetFocus();
					}
					break;
				default:
					{
						bAdd = FALSE;
					}
					break;
				}

				break;
			}
		}
	}	

	if ( bAdd )
	{
		EnterCriticalSection(&g_csLockDiscuss);
		m_mapDiscussSelItem.erase(wIndex);
		m_mapDiscussSelItem.insert( std::make_pair<u16,CString>(wIndex, strEpName) );
		LeaveCriticalSection(&g_csLockDiscuss);

		GetParent()->SendMessage( WM_DEF_CHANGE_DISCUSSEP, (WPARAM)&m_mapDiscussSelItem, 0 );
	}

	return bAdd;
}

BOOL CMeetDiscussLogic::DelFromEpEdit( const CString& strEpName )
{
	BOOL bDel = FALSE;
	u16 wIndex = TP_CONF_MAX_AUDMIXNUM;

	std::map<u16,CString>::iterator iter;
	for ( iter = m_mapDiscussSelItem.begin(); iter != m_mapDiscussSelItem.end(); iter++ )
	{
		wIndex = iter->first;
		CString strGroupName = iter->second;
		
		if ( strcmp( strGroupName, strEpName ) == 0 )
		{
			bDel = TRUE;

			switch ( wIndex )
			{
			case 0:
				{
					m_etGroup1.SetWindowText("");
					m_etGroup1.SetFocus();
				}
				break;
			case 1:
				{
					m_etGroup2.SetWindowText("");
					m_etGroup2.SetFocus();
				}
				break;
			case 2:
				{
					m_etGroup3.SetWindowText("");
					m_etGroup3.SetFocus();
				}
				break;
			case 3:
				{
					m_etGroup4.SetWindowText("");
					m_etGroup4.SetFocus();
				}
				break;
			default:
				{
					bDel = FALSE;
				}
				break;
			}
			
			break;
		}
	}

	if ( bDel )
	{
		EnterCriticalSection(&g_csLockDiscuss);
		m_mapDiscussSelItem.erase(wIndex);
		m_mapDiscussSelItem.insert( std::make_pair<u16,CString>(wIndex, "") );
		LeaveCriticalSection(&g_csLockDiscuss);

		GetParent()->SendMessage( WM_DEF_CHANGE_DISCUSSEP, (WPARAM)&m_mapDiscussSelItem, 0 );
	}

	return bDel;
}

LRESULT CMeetDiscussLogic::OnDragEnd(WPARAM wParam, LPARAM lParam)
{
	s32 x = LOWORD(lParam);
	s32 y = HIWORD(lParam);
	CPoint point(x, y);

	this->ScreenToClient(&point);

	BOOL bAdd = TRUE;
	if ( m_rectGroup1.PtInRect( point ) )
	{ 
		m_etGroup1.SetFocus();
	}
	else if ( m_rectGroup2.PtInRect( point ) )
	{ 
		m_etGroup2.SetFocus();
	}
	else if ( m_rectGroup3.PtInRect( point ) )
	{ 
		m_etGroup3.SetFocus();
	}
	else if ( m_rectGroup4.PtInRect( point ) )
	{ 
		m_etGroup4.SetFocus();
	}
	else
	{
		bAdd = FALSE;
	}

	if ( bAdd )
	{
		if ( const Data_CnsAddr *pItemInfo = dynamic_cast<const Data_CnsAddr*>( (IData*)wParam ) ) 
		{
			CString strPollingName = pItemInfo->m_tEpAddr.m_tAlias.m_abyAlias;
			if ( strPollingName.IsEmpty() )
			{
				strPollingName = pItemInfo->m_tEpAddr.m_tE164.m_abyAlias;
			}

			std::map<u16,CString>::iterator iter;
			u16 wIndex = TP_CONF_MAX_AUDMIXNUM;
			for ( iter = m_mapDiscussSelItem.begin(); iter != m_mapDiscussSelItem.end(); iter++ )
			{
				if ( strcmp( iter->second, strPollingName ) == 0 )
				{
					wIndex = iter->first;

					EnterCriticalSection(&g_csLockDiscuss);
					m_mapDiscussSelItem.erase(wIndex);
					m_mapDiscussSelItem.insert( std::make_pair<u16,CString>(wIndex, "") );
					LeaveCriticalSection(&g_csLockDiscuss);
					break;
				}
			}

			AddToEpEdit( strPollingName );
		}
	}

    return NO_ERROR;
}

// LRESULT CMeetDiscussLogic::OnDragOver(WPARAM wParam, LPARAM lParam)
// {	
// 	s32 x = LOWORD(lParam);
// 	s32 y = HIWORD(lParam);
// 	CPoint point(x, y);
// 
// 	this->ScreenToClient(&point);
// 
// 	OspPrintf( TRUE, FALSE, "OnDragOver : x = %d, y = %d\n", x, y);
// 
// 	if ( m_rectGroup1.PtInRect( point ) )
// 	{ 
// 		m_etGroup1.SetFocus();
// 	}
// 	else if ( m_rectGroup2.PtInRect( point ) )
// 	{ 
// 		m_etGroup2.SetFocus();
// 	}
// 	else if ( m_rectGroup3.PtInRect( point ) )
// 	{ 
// 		m_etGroup3.SetFocus();
// 	}
// 	else if ( m_rectGroup4.PtInRect( point ) )
// 	{ 
// 		m_etGroup4.SetFocus();
// 	}
// 	
//     return NO_ERROR;
// }
