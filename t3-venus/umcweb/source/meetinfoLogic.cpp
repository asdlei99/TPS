// MeetingList.cpp : implementation file
//
#include "stdafx.h"
#include "umcwebproj.h"
#include "meetinfoLogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMeetinfoLogic dialog

extern float CUR_SCREEN_WIDTH_PER;  //屏幕宽度比率
extern float CUR_SCREEN_HEIGHT_PER; //屏幕高度比率

CMeetinfoLogic::CMeetinfoLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CMeetinfoLogic::IDD, pParent)
	,m_pconfCtrlIF(NULL)
	,m_tTmpConfigIF(NULL)
{
	//{{AFX_DATA_INIT(CMeetinfoLogic)
	//}}AFX_DATA_INIT

	m_plsCurMeet = NULL;
	m_plsOrderMeet = NULL;
	m_pLetterIndex = NULL;
	m_bIsAllSel = FALSE;
    m_bShowMosaicHoriImg = TRUE;
	m_emCurPageMeetType = em_Menu_AllMeet;
	m_pTCurCloseMeetTmp = NULL;
	m_bConfExist = FALSE;
}

void CMeetinfoLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMeetinfoLogic)
	DDX_Control(pDX, IDC_BUTTON_MENU, m_btnCheckMenu);
	DDX_Control(pDX, IDC_STATIC_CURMEETTITLE, m_stCurMeetTitle);
	DDX_Control(pDX, IDC_STATIC_ORDERMEETTITLE, m_stOrderMeetTitle);
	DDX_Control(pDX, IDC_STATIC_CHILDFRMBOTTOM, m_stChildBkBottom);
	DDX_Control(pDX, IDC_STATIC_CHILDFRMUP, m_stChildBkUp);
	DDX_Control(pDX, IDC_STATIC_LEFTTITLE, m_stLeftTitle);
	DDX_Control(pDX, IDC_EDIT_FIND, m_etSearch);
	DDX_Control(pDX, IDC_Btn_AllSelect, m_btnAllSel);
	DDX_Control(pDX, IDC_Btn_CloseMeeting, m_btnCloseMeeting);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMeetinfoLogic, CDlgChild)
	//{{AFX_MSG_MAP(CMeetinfoLogic)
	ON_BN_CLICKED(IDC_Btn_AllSelect, OnBtnAllSelect)
	ON_BN_CLICKED(IDC_Btn_CloseMeeting, OnBtnCloseMeeting)
	ON_MESSAGE( UI_UMS_REFRESH_CONFTEMPLATE_LIST,  OnRefreshTmpList )
	ON_MESSAGE( UI_UMS_REFRESH_CONF_LIST, OnRefreshConfList )
	ON_MESSAGE( UI_UMS_REFRESH_CONFCNS_LIST, OnUpdateConfList )
	ON_MESSAGE( UI_HUNGUP_UMS_CONF_REASON, OnHungupConfReason)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_MENU, OnBtnCheckMenu)
	ON_MESSAGE( WM_DEF_CLICKMEETLISTMENUUPDATE, OnClickMeetListMenuUpdate)
	ON_MESSAGE( UI_UMS_START_CONFTEMPLATE_RSP, OnStartConfResult )
	ON_MESSAGE( WM_DEF_HIDE_LOSEFOCUSHIDER, OnHideAUtoHideWnd )
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMeetinfoLogic message handlers
void CMeetinfoLogic::RegisterFun()
{
	REG_MSG_HANDLER( "CMeetinfoLogic::OnClickCurMeetLstItem", CMeetinfoLogic::OnClickCurMeetLstItem, this, CMeetinfoLogic );	
	REG_MSG_HANDLER( "CMeetinfoLogic::OnClickCurMeetLstItemIcon", CMeetinfoLogic::OnClickCurMeetLstItemIcon, this, CMeetinfoLogic );
	REG_MSG_HANDLER( "CMeetinfoLogic::OnClickOrderMeetLstItem", CMeetinfoLogic::OnClickOrderMeetLstItem, this, CMeetinfoLogic );	
	REG_MSG_HANDLER( "CMeetinfoLogic::OnClickOrderMeetLstItemIcon", CMeetinfoLogic::OnClickOrderMeetLstItemIcon, this, CMeetinfoLogic );
	REG_MSG( UI_UMS_REFRESH_CONFTEMPLATE_LIST, GetSafeHwnd() );
	REG_MSG( WM_DEF_HIDE_LOSEFOCUSHIDER, GetSafeHwnd() );
}

BOOL CMeetinfoLogic::InitControlPane()
{
	//初始化界面控件图片控件
	m_btnAllSel.SetImage( IDR_PNG_BTN_ALLSEL, IDR_PNG_BTN_ALLSELDOWN, IDR_PNG_BTN_ALLSELDIS );
	m_btnCloseMeeting.SetImage( IDR_PNG_MEETLISTWND_BTN_CLOSEMEET, IDR_PNG_MEETLISTWND_BTN_CLOSEMEETDOWN, IDR_PNG_MEETLISTWND_BTN_CLOSEMEETDIS );
  	m_btnCheckMenu.SetImage( IDR_PNG_MEETLISTWND_BTN_CHECKMENUSEL, IDR_PNG_MEETLISTWND_BTN_CHECKMENUDOWN, IDR_PNG_MEETLISTWND_BTN_CHECKMENUSEL, 
  		IDR_PNG_MEETLISTWND_BTN_CHECKMENU,IDR_PNG_MEETLISTWND_BTN_CHECKMENUDOWN,IDR_PNG_MEETLISTWND_BTN_CHECKMENU);
    m_btnCheckMenu.SetButtonStyle( BS_AUTOCHECKBOX );

	m_btnCloseMeeting.EnableWindow(FALSE);

	m_stChildBkBottom.SetWindowText("预约会议");

	CUmcwebCommon::SetTextTransStatic( &m_stCurMeetTitle, "当前会议" , 10, Color( 255, 255, 255 ) );
	CUmcwebCommon::SetTextTransStatic( &m_stOrderMeetTitle, "预约会议" , 10, Color( 255, 255, 255 ) );
	CUmcwebCommon::SetTextTransStatic( &m_stLeftTitle, "会议信息" , 14, Color( 24, 25, 27 ) );

	CUmcwebCommon::SetImgForTransSearchEdit(&m_etSearch);

	//当前会议列表加入
	m_plsCurMeet = new CListChild( "", CRect(11, 100 + 33, 1226 - 62 - 2+11, 215+100 + 33), this, "", 0, WS_CHILD );
	if ( NULL != m_plsCurMeet )
	{
		m_plsCurMeet->SetWindowPos( NULL, 11*CUR_SCREEN_WIDTH_PER, (100 + 33)*CUR_SCREEN_HEIGHT_PER, (1226 - 62 - 2)*CUR_SCREEN_WIDTH_PER, 215*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
		m_plsCurMeet->SetImage( IDR_PNG_LIST_TOPLEFT, IDR_PNG_LIST_TOPCEN, IDR_PNG_LIST_TOPRIGHT, IDR_PNG_LIST_CENLEFT, IDR_PNG_LIST_CENRIGHT,
			IDR_PNG_LIST_BTLEFT, IDR_PNG_LIST_BTCEN, IDR_PNG_LIST_BTRIGHT, IDR_PNG_LIST_TOPCEN, "PNG" );
		m_plsCurMeet->SetSliderImage( IDR_PNG_LISTSLIDER_NORMALTOP, IDR_PNG_LISTSLIDER_NORMALMIDDLE, IDR_PNG_LISTSLIDER_NORMALBOTTOM, IDR_PNG_LISTSLIDER_DOWNTOP, 
            IDR_PNG_LISTSLIDER_DOWNMIDDLE, IDR_PNG_LISTSLIDER_DOWNBOTTOM, IDR_PNG_LISTSLIDER_BKGTOP, IDR_PNG_LISTSLIDER_BKGMIDDLE, IDR_PNG_LISTSLIDER_BKGBOTTOM, "PNG" );
        m_plsCurMeet->SetSliderAlwaysShow( TRUE );

		m_pLetterIndex = new CLetterIndex( "Letter", "Letter", CRect(0,0,39,486), this, GETUNIQID, WS_CHILD );
		if ( m_pLetterIndex != NULL )
		{
			CUmcwebCommon::SetImgForLetter(m_pLetterIndex);
			m_pLetterIndex->SetLetterHeight(18*CUR_SCREEN_HEIGHT_PER);
            m_pLetterIndex->AddBindList( m_plsCurMeet );

			CRect rc;
			m_plsCurMeet->GetWindowRect(&rc);
			ScreenToClient( &rc );
			rc.left = rc.right - 3;
			rc.right = rc.left + 7;
			m_plsCurMeet->SetSliderRect( rc );
		}
	}
	
	//预约会议列表加入
	m_plsOrderMeet = new CListChild( "", CRect(11, 342 + 36, 1226 - 62 - 2+11, 211+342 + 36), this, "", 0, WS_CHILD );
	if ( NULL != m_plsOrderMeet )
	{
		m_plsOrderMeet->SetWindowPos( NULL, 11*CUR_SCREEN_WIDTH_PER, (342 + 36)*CUR_SCREEN_HEIGHT_PER, (1226 - 62 - 2)*CUR_SCREEN_WIDTH_PER, 211*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
		m_plsOrderMeet->SetImage( IDR_PNG_LIST_TOPLEFT, IDR_PNG_LIST_TOPCEN, IDR_PNG_LIST_TOPRIGHT, IDR_PNG_LIST_CENLEFT, IDR_PNG_LIST_CENRIGHT,
			IDR_PNG_LIST_BTLEFT, IDR_PNG_LIST_BTCEN, IDR_PNG_LIST_BTRIGHT, IDR_PNG_LIST_TOPCEN, "PNG" );
		m_plsOrderMeet->SetSliderImage( IDR_PNG_LISTSLIDER_NORMALTOP, IDR_PNG_LISTSLIDER_NORMALMIDDLE, IDR_PNG_LISTSLIDER_NORMALBOTTOM, IDR_PNG_LISTSLIDER_DOWNTOP, 
            IDR_PNG_LISTSLIDER_DOWNMIDDLE, IDR_PNG_LISTSLIDER_DOWNBOTTOM, IDR_PNG_LISTSLIDER_BKGTOP, IDR_PNG_LISTSLIDER_BKGMIDDLE, IDR_PNG_LISTSLIDER_BKGBOTTOM, "PNG" );
        m_plsOrderMeet->SetSliderAlwaysShow( TRUE );

		CRect rcOrderMeet;
		m_plsOrderMeet->GetWindowRect(&rcOrderMeet);
		ScreenToClient( &rcOrderMeet );
		rcOrderMeet.left = rcOrderMeet.right - 3;
		rcOrderMeet.right = rcOrderMeet.left + 7;
		m_plsOrderMeet->SetSliderRect( rcOrderMeet );

		if ( m_pLetterIndex != NULL )
		{
			m_pLetterIndex->AddBindList( m_plsOrderMeet );
		}
	}

	m_dlgMenubar.Create( IDD_DIALOG_MENUBAR, this );

	return TRUE;
}

void CMeetinfoLogic::SetControlPos()
{
	CRect rectClient( 0, 0, 1252, 651 );
	this->GetClientRect(&rectClient);

	m_stChildBkUp.SetWindowPos( NULL, 13*CUR_SCREEN_WIDTH_PER, 101*CUR_SCREEN_HEIGHT_PER, (1226 - 65)*CUR_SCREEN_WIDTH_PER, 32*CUR_SCREEN_HEIGHT_PER,  SWP_SHOWWINDOW );
	m_stChildBkUp.SetMosaicHoriImage( IDR_PNG_MEETLISTWND_BTN_SEPALEFT, IDR_PNG_MEETLISTWND_BTN_SEPARIGHT, IDR_PNG_MEETLISTWND_BTN_SEPAMID );
	m_stChildBkBottom.SetWindowPos( NULL, 13*CUR_SCREEN_WIDTH_PER, 346*CUR_SCREEN_HEIGHT_PER, (1226 - 65)*CUR_SCREEN_WIDTH_PER, 32*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stChildBkBottom.SetMosaicHoriImage( IDR_PNG_MEETLISTWND_BTN_SEPALEFT, IDR_PNG_MEETLISTWND_BTN_SEPARIGHT, IDR_PNG_MEETLISTWND_BTN_SEPAMID );
	
	m_stCurMeetTitle.SetWindowPos( &m_stChildBkUp, 17*CUR_SCREEN_WIDTH_PER, 107*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 14*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stOrderMeetTitle.SetWindowPos( &m_stChildBkBottom, 17*CUR_SCREEN_WIDTH_PER, 350*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 14*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stLeftTitle.SetWindowPos( NULL, 17,  14, rectClient.Width(), 24, SWP_SHOWWINDOW );

	if ( NULL != m_plsCurMeet )
	{
		m_plsCurMeet->SetWindowPos( NULL, 11*CUR_SCREEN_WIDTH_PER, (100 + 33)*CUR_SCREEN_HEIGHT_PER, (1226 - 62 - 2)*CUR_SCREEN_WIDTH_PER, 215*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

		m_plsCurMeet->GetWindowRect(&rectClient);
		ScreenToClient( &rectClient );
		if ( m_pLetterIndex != NULL )
		{	
			rectClient.left = rectClient.right - 3;
			rectClient.right = rectClient.left + 7;
			m_plsCurMeet->SetSliderRect( rectClient );

			m_pLetterIndex->SetWindowPos( NULL, rectClient.right + 2*CUR_SCREEN_WIDTH_PER, 100*CUR_SCREEN_HEIGHT_PER, 39*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER,SWP_SHOWWINDOW );	
		}

	}

	if ( NULL != m_plsOrderMeet )
	{
		m_plsOrderMeet->SetWindowPos( NULL, 11*CUR_SCREEN_WIDTH_PER, (342 + 36)*CUR_SCREEN_HEIGHT_PER, (1226 - 62 - 2)*CUR_SCREEN_WIDTH_PER, 211*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
		
		CRect rcOrderMeet;
		m_plsOrderMeet->GetWindowRect(&rcOrderMeet);
		ScreenToClient( &rcOrderMeet );
		rcOrderMeet.left = rcOrderMeet.right - 3;
		rcOrderMeet.right = rcOrderMeet.left + 7;
		m_plsOrderMeet->SetSliderRect( rcOrderMeet );
	}

	m_btnCheckMenu.SetWindowPos( &wndTop, rectClient.right - 18*CUR_SCREEN_WIDTH_PER, 4*CUR_SCREEN_HEIGHT_PER, 
		m_btnCheckMenu.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnCheckMenu.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

	m_plsCurMeet->GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	m_btnCloseMeeting.SetWindowPos( &wndTop, rectClient.right - m_btnCloseMeeting.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnCloseMeeting.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnCloseMeeting.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_NOZORDER|SWP_SHOWWINDOW );
	
	m_btnCloseMeeting.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	m_btnAllSel.SetWindowPos( &wndTop, rectClient.right - m_btnAllSel.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - m_btnAllSel.GetImageSize().cx*CUR_SCREEN_WIDTH_PER 
		- 10*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnAllSel.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnAllSel.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_NOZORDER|SWP_SHOWWINDOW );
	
	m_btnAllSel.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	m_etSearch.SetWindowPos( &wndTop, 12*CUR_SCREEN_WIDTH_PER, 53*CUR_SCREEN_HEIGHT_PER,  rectClient.right - 
		m_btnAllSel.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - 15*CUR_SCREEN_WIDTH_PER,41*CUR_SCREEN_HEIGHT_PER, SWP_NOZORDER|SWP_SHOWWINDOW );
}

void CMeetinfoLogic::SelectMeetListView(EM_MENU_MEETTYPE emMenuType)
{	
	switch ( emMenuType )
	{
	case em_Menu_AllMeet:
		{
			if( m_plsCurMeet != NULL && m_plsOrderMeet != NULL )
			{
				UpdateUIState();
				m_plsCurMeet->SetWindowPos( NULL, 11*CUR_SCREEN_WIDTH_PER, (100 + 33)*CUR_SCREEN_HEIGHT_PER, (1226 - 62 - 2)*CUR_SCREEN_WIDTH_PER, 215*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
				m_plsOrderMeet->SetWindowPos( NULL, 11*CUR_SCREEN_WIDTH_PER, (342 + 36)*CUR_SCREEN_HEIGHT_PER, (1226 - 62 - 2)*CUR_SCREEN_WIDTH_PER, 211*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
				
				CRect rc;
				m_plsCurMeet->GetWindowRect(&rc);
				ScreenToClient( &rc );
				rc.left = rc.right - 3;
				rc.right = rc.left + 7;
				m_plsCurMeet->SetSliderRect( rc );
				
				CRect rcOrderMeet;
				m_plsOrderMeet->GetWindowRect(&rcOrderMeet);
				ScreenToClient( &rcOrderMeet );
				rcOrderMeet.left = rcOrderMeet.right - 3;
				rcOrderMeet.right = rcOrderMeet.left + 7;
				m_plsOrderMeet->SetSliderRect( rcOrderMeet );

				m_stCurMeetTitle.SetWindowText("当前会议");
				m_stChildBkBottom.ShowWindow(SW_SHOW);
			}
		}
		break;
	case em_Menu_CurMeet:
		{
			if( m_plsCurMeet != NULL && m_plsOrderMeet != NULL )
			{
				UpdateUIState();
				m_plsOrderMeet->ShowWindow(SW_HIDE);
				m_stCurMeetTitle.SetWindowText("当前会议");
				m_stChildBkBottom.ShowWindow(SW_HIDE);
				m_plsCurMeet->SetWindowPos( NULL, 11*CUR_SCREEN_WIDTH_PER, (100 + 30)*CUR_SCREEN_HEIGHT_PER, (1226 - 62 - 2)*CUR_SCREEN_WIDTH_PER, (208 + 179 + 2 + 72)*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
			
				CRect rc;
				m_plsCurMeet->GetWindowRect(&rc);
				ScreenToClient( &rc );
				rc.left = rc.right - 3;
				rc.right = rc.left + 7;
				m_plsCurMeet->SetSliderRect( rc );
			}
		}
		break;
	case em_Menu_OrderMeet:
		{
			if( m_plsCurMeet != NULL && m_plsOrderMeet != NULL )
			{
				UpdateUIState();
				m_plsCurMeet->ShowWindow(SW_HIDE);
				m_stCurMeetTitle.SetWindowText("预约会议");
				m_stChildBkBottom.ShowWindow(SW_HIDE);
				m_plsOrderMeet->SetWindowPos( NULL, 11*CUR_SCREEN_WIDTH_PER, (100 + 30)*CUR_SCREEN_HEIGHT_PER, (1226 - 62 - 2)*CUR_SCREEN_WIDTH_PER, (208 + 179 + 2 + 72)*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
				
				CRect rcOrderMeet;
				m_plsOrderMeet->GetWindowRect(&rcOrderMeet);
				ScreenToClient( &rcOrderMeet );
				rcOrderMeet.left = rcOrderMeet.right - 3;
				rcOrderMeet.right = rcOrderMeet.left + 7;
				m_plsOrderMeet->SetSliderRect( rcOrderMeet );	
			}
		}
		break;
	default:
		{
		}
		break;
	}
}

BOOL CMeetinfoLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();

	RegisterFun();				//注册函数
	if ( !InitControlPane() )	//初始化页面控件
	{
		return FALSE;
	}
	SetControlPos();			//设置页面控件位置

 	if( m_pconfCtrlIF == NULL )
 	{
		BUSINESSIFPTR->GetCtrlInterface(&m_pconfCtrlIF);
 	}
		
 	if( m_pconfCtrlIF != NULL )
	{
	 	m_pconfCtrlIF->SetNotifyWnd( this->m_hWnd );
 	} 

	m_btnCheckMenu.SetBindWnd( m_dlgMenubar );

	return TRUE;
}

LRESULT CMeetinfoLogic::OnRefreshConfList( WPARAM wparam, LPARAM lparam )
{
	if( m_pconfCtrlIF == NULL )
	{
		BUSINESSIFPTR->GetCtrlInterface(&m_pconfCtrlIF);
 	}

	CurMeetListRefresh();
	m_plsCurMeet->SetSelItem(-1);

    CMsgHandle::SendMessage( UI_UMS_REFRESH_CONF_LIST, wparam, lparam );

	return S_OK;
}

LRESULT CMeetinfoLogic::OnUpdateConfList( WPARAM wparam, LPARAM lparam )
{
	if( m_pconfCtrlIF == NULL )
	{
		BUSINESSIFPTR->GetCtrlInterface(&m_pconfCtrlIF);
	}
	
	CurMeetListRefresh();

    CMsgHandle::SendMessage( UI_UMS_REFRESH_CONFCNS_LIST, wparam, lparam );

	return S_OK;
}

void CMeetinfoLogic::CurMeetListRefresh()
{
	m_vecCurConfRefreshList.clear();
	if ( m_pconfCtrlIF != NULL )
	{
		m_pconfCtrlIF->GetConfList(m_vecCurConfRefreshList);

		if ( m_vecCurConfRefreshList.size() == 0 )
		{
			SetConfExist(FALSE);
		}
		else
		{
			SetConfExist(TRUE);
		}

		std::set<u16> setCurConfSelectedIconItem;
		for ( s32 nIndex = 0; nIndex < m_vecCurConfRefreshList.size(); nIndex++ )
		{	
			TCMSConf tCmsConf = m_vecCurConfRefreshList[nIndex];
			u16 nConfId = tCmsConf.m_wConfID;
			
			std::set<u16>::iterator iter = m_setCurConfSelectedIconItem.find(nConfId);
			if ( iter != m_setCurConfSelectedIconItem.end() )
			{
				setCurConfSelectedIconItem.insert(nConfId);
			}
		}
		m_setCurConfSelectedIconItem.clear();
		m_setCurConfSelectedIconItem = setCurConfSelectedIconItem;

		OnSearchEditChange();
		UpdateCurConfShowList();
		UpdateUIState();
	}
}

LRESULT CMeetinfoLogic::OnRefreshTmpList(WPARAM wParam, LPARAM lParam)
{
 	if( m_tTmpConfigIF == NULL )
 	{
 		BUSINESSIFPTR->GetCtrlInterface(&m_tTmpConfigIF);
 	}

	MeetTmpRefresh();

	if ( NULL != m_plsOrderMeet )
	{
		m_plsOrderMeet->SetSelItem(-1);
	}

	return 0L;
}

void CMeetinfoLogic::MeetTmpRefresh()
{
	m_tpOrderConfRefreshList.Clear();
	TplArray<TTPConfTemplate> tTmpList;
	if ( m_tTmpConfigIF != NULL )
	{
		m_tTmpConfigIF->GetConfTemplateList(tTmpList);

		std::set<u16> setOrderConfSelectedIconItem; 
		for( s32 nIndex = 0; nIndex < tTmpList.Size(); nIndex++ )
		{
			TCMSConfTemplate* pTConfTemp = (TCMSConfTemplate*)&tTmpList.GetAt(nIndex);
			if ( pTConfTemp == NULL )
			{
				continue;
			}

			if ( pTConfTemp->m_tStartTime == 0 )
			{
				continue;
			}
			
			u16 nTmpId = pTConfTemp->m_wID;
			
			std::set<u16>::iterator iter = m_setOrderConfSelectedIconItem.find(nTmpId);
			if ( iter != m_setOrderConfSelectedIconItem.end() )
			{
				setOrderConfSelectedIconItem.insert(nTmpId);
			}

			m_tpOrderConfRefreshList.Add(pTConfTemp);
		}
		m_setOrderConfSelectedIconItem.clear();
		m_setOrderConfSelectedIconItem = setOrderConfSelectedIconItem;

		OnSearchEditChange();
		UpdateOrderConfShowList();
		UpdateUIState();
	}
}

void CMeetinfoLogic::OnBtnAllSelect() 
{
	m_bIsAllSel = !m_bIsAllSel;

	if ( m_plsOrderMeet->IsWindowVisible() )
	{
		m_setOrderConfSelectedIconItem.clear();
		if ( m_bIsAllSel )
		{
			for( s32 nIndex = 0; nIndex < m_tpOrderConflShowList.Size(); nIndex++ )
			{
				u16 nTmpId = m_tpOrderConflShowList.GetAt(nIndex).m_wID;
				m_setOrderConfSelectedIconItem.insert(nTmpId);
			}
		}
		UpdateOrderConfShowList();	
	}

	if ( m_plsCurMeet->IsWindowVisible() )
	{
		m_setCurConfSelectedIconItem.clear();
		if ( m_bIsAllSel )
		{
			for( s32 nIndex = 0; nIndex < m_vecCurConflShowList.size(); nIndex++ )
			{
				TCMSConf tConf = m_vecCurConflShowList.at(nIndex);
				u16 nConfId = tConf.m_wConfID;
				m_setCurConfSelectedIconItem.insert(nConfId);
			}	
		}
		UpdateCurConfShowList();
	}

	UpdateUIState();
}

TTPConfTemplate* CMeetinfoLogic::GetTemplateById(u16 nTmplateId)
{
	if ( m_tTmpConfigIF != NULL )
	{
		for( s32 nIndex = 0; nIndex < m_tpOrderConfRefreshList.Size(); nIndex++ )
		{
			TTPConfTemplate tConfTemp = m_tpOrderConfRefreshList.GetAt(nIndex);
			u16 nTmpId = tConfTemp.m_wID;
			if ( nTmpId == nTmplateId )
			{
				return &(m_tpOrderConfRefreshList.GetAt(nIndex));
			}
		}
	}

	return NULL;
}

void CMeetinfoLogic::OnBtnCloseMeeting() 
{
	s32 nRet = 0;
	MESSAGEWNDBOX( "是否挂断所选会议？", this , nRet, TRUE );
	if( nRet == IDOK )
	{
		if ( m_plsOrderMeet->IsWindowVisible() )
		{
			//修改预约会议为即使会议属性
   			for ( std::set<u16>::iterator iterOrderMeet = m_setOrderConfSelectedIconItem.begin(); iterOrderMeet != m_setOrderConfSelectedIconItem.end(); iterOrderMeet++ )
			{
				u16 nOrderMeetId = *iterOrderMeet;
				m_pTCurCloseMeetTmp = (TCMSConfTemplate*)GetTemplateById(nOrderMeetId);
				if ( m_pTCurCloseMeetTmp != NULL )
				{
					if ( m_tTmpConfigIF != NULL )
					{
						m_pTCurCloseMeetTmp->m_tStartTime = 0;
						s32 nRet = m_tTmpConfigIF->ModifyConfTemplateReq(*m_pTCurCloseMeetTmp);
						if ( nRet != NO_ERROR )
						{
							MESSAGEWND( "结束会议请求发送失败" );
						}
					}
				}
			}
		}

		if ( m_plsCurMeet->IsWindowVisible() )
		{
			//发送关闭当前会议通知
   			for ( std::set<u16>::iterator iterCurMeet = m_setCurConfSelectedIconItem.begin(); iterCurMeet != m_setCurConfSelectedIconItem.end(); iterCurMeet++ )
			{
				u16 nCurMeetId = *iterCurMeet;
				if ( m_pconfCtrlIF != NULL )
				{
					s32 nRet = m_pconfCtrlIF->HangupConfReq(nCurMeetId);
					if ( nRet != NO_ERROR )
					{
						MESSAGEWND( "结束会议请求发送失败"  );
					}
				}
			}
		}
	}
}

bool CMeetinfoLogic::OnClickCurMeetLstItem( const IArgs & arg )
{
	return true;
}

bool CMeetinfoLogic::OnClickCurMeetLstItemIcon( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg) )
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();
		if ( const Data_Conf *pItemInfo = dynamic_cast<const Data_Conf*>( pBaseItem->GetUserData() ) ) 
		{   
			TCMSConf  tCmsConf = pItemInfo->m_tCmsConf;
			u16 nConfId = tCmsConf.m_wConfID;
			
			s32 nPreClickedItemCount = m_setCurConfSelectedIconItem.size();
			m_setCurConfSelectedIconItem.insert(nConfId);
			s32 nLastClickedItemCount = m_setCurConfSelectedIconItem.size();
			
			if ( nPreClickedItemCount == nLastClickedItemCount )
			{
				m_setCurConfSelectedIconItem.erase(nConfId);
			}

			UpdateCurConfShowList();
			UpdateUIState();
		}
    }

	return true;
}

void CMeetinfoLogic::OnSearchEditChange()
{
	CString strSearchName;
	m_etSearch.GetWindowText( strSearchName );

	if ( ( NULL == m_plsOrderMeet ) || ( NULL == m_plsCurMeet ) ) 
	{
		return;
	}

	if ( m_plsOrderMeet->IsWindowVisible() )
	{
		if ( !strSearchName.IsEmpty() )
		{
			m_tpOrderConfSearchList.Clear();
			TplArray<TCMSConfTemplate> tpShowList;
			tpShowList = m_tpOrderConfRefreshList;
			
			if ( m_plsOrderMeet != NULL )
			{
				m_plsOrderMeet->SetYOffset( 0 );
			}
			
			for ( s32 nIndex = 0; nIndex < tpShowList.Size(); nIndex++ )
			{
				TCMSConfTemplate tTPConfTmp;
				tTPConfTmp = tpShowList.GetAt(nIndex);
				CString strItemName;
				strItemName = tpShowList.GetAt(nIndex).m_achConfName;
				
				BOOL bFind = FALSE;			
				bFind = CUmcwebCommon::HZPYMatchList( strSearchName, strItemName );
				if ( bFind )
				{		
					m_tpOrderConfSearchList.Add( &tTPConfTmp );
				}
			}
		}

		UpdateOrderConfShowList();
		UpdateUIState();
	}
	
	if ( m_plsCurMeet->IsWindowVisible() )
	{
		if ( !strSearchName.IsEmpty() )
		{
			m_vecCurConfSearchList.clear();
			ARRAY<TCMSConf> vecShowList;
			vecShowList = m_vecCurConfRefreshList;
			
			if ( m_plsCurMeet != NULL )
			{
				m_plsCurMeet->SetYOffset( 0 );
			}
			
			for ( s32 nIndex = 0; nIndex < vecShowList.size(); nIndex++ )
			{
				TCMSConf  tCmsConf = vecShowList[nIndex];

				CString strItemName;
				strItemName = vecShowList[nIndex].m_achConfName;
				
				BOOL bFind = FALSE;			
				bFind = CUmcwebCommon::HZPYMatchList( strSearchName, strItemName );
				if ( bFind )
				{		
					m_vecCurConfSearchList.push_back( tCmsConf );
				}
			}
		}

		UpdateCurConfShowList();
		UpdateUIState();
	}
}

void CMeetinfoLogic::UpdateOrderConfShowList()
{
	CString strText;
	m_etSearch.GetWindowText( strText );
	m_tpOrderConflShowList.Clear();
	if ( strText.IsEmpty() )
	{
		m_tpOrderConflShowList = m_tpOrderConfRefreshList;
	}
	else
	{
		m_tpOrderConflShowList = m_tpOrderConfSearchList;
	}
	Value_TouchListOrderConf val_orderConfList( &m_tpOrderConflShowList, "CMeetinfoLogic::OnClickOrderMeetLstItem", NULL );
	val_orderConfList.m_setClickedId = m_setOrderConfSelectedIconItem;
	if( m_plsOrderMeet != NULL )
	{
		m_plsOrderMeet->SetData( val_orderConfList );
	}
}

void CMeetinfoLogic::UpdateCurConfShowList()
{
	CString strText;
	m_etSearch.GetWindowText( strText );
	
	if ( strText.IsEmpty() )
	{
		m_vecCurConflShowList = m_vecCurConfRefreshList;
	}
	else
	{
		m_vecCurConflShowList = m_vecCurConfSearchList;
	}
	Value_TouchListConf val_curConfList( &m_vecCurConflShowList, "CMeetinfoLogic::OnClickCurMeetLstItem", NULL );
	val_curConfList.m_setClickedId = m_setCurConfSelectedIconItem;
	if ( m_plsCurMeet != NULL )
	{
		m_plsCurMeet->SetData( val_curConfList );
	}
}

bool CMeetinfoLogic::OnClickOrderMeetLstItem( const IArgs & arg )
{
	return true;
}

bool CMeetinfoLogic::OnClickOrderMeetLstItemIcon( const IArgs & arg )
{
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg) )
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();
		if ( const Data_OrderConf *pItemInfo = dynamic_cast<const Data_OrderConf*>( pBaseItem->GetUserData() ) ) 
		{   
			TCMSConfTemplate tConfTemp = pItemInfo->m_tConfTemp;
			u16 nTmpId = tConfTemp.m_wID;

			s32 nPreClickedItemCount = m_setOrderConfSelectedIconItem.size();
			m_setOrderConfSelectedIconItem.insert(nTmpId);
			s32 nLastClickedItemCount = m_setOrderConfSelectedIconItem.size();
			
			if ( nPreClickedItemCount == nLastClickedItemCount )
			{
			 	m_setOrderConfSelectedIconItem.erase(nTmpId);
 			}

			UpdateOrderConfShowList();
			UpdateUIState();
		}
    }

	return true;
}

void CMeetinfoLogic::OnDestroy() 
{
	CDlgChild::OnDestroy();

	m_tpOrderConfRefreshList.Clear();
	m_tpOrderConflShowList.Clear();
	m_tpOrderConfSearchList.Clear();
	
	SAFE_RELEASE(m_plsCurMeet);
	SAFE_RELEASE(m_plsOrderMeet);
	SAFE_RELEASE(m_pLetterIndex);
}

void CMeetinfoLogic::OnBtnCheckMenu() 
{
	s32 nCheck = m_btnCheckMenu.GetCheck();
	if( nCheck == BST_CHECKED )
	{
		CRect rectCalendar;
		m_btnCheckMenu.GetWindowRect(&rectCalendar);
		m_dlgMenubar.SetWindowPos( NULL, rectCalendar.left + m_btnCheckMenu.GetImageSize().cx - 232 - 2, 
			                         rectCalendar.bottom - 2, 232, 162, SWP_SHOWWINDOW ); 	 
	}
	else
	{
		m_dlgMenubar.ShowWindow(SW_HIDE);
	}
}

LRESULT CMeetinfoLogic::OnClickMeetListMenuUpdate( WPARAM wParam, LPARAM lParam )
{
	m_emCurPageMeetType = (EM_MENU_MEETTYPE)wParam;
	switch ( m_emCurPageMeetType )
	{
	case em_Menu_AllMeet:
		{
			SelectMeetListView(em_Menu_AllMeet);

			CurMeetListRefresh();
			MeetTmpRefresh();
		}
		break;
	case em_Menu_CurMeet:
		{
			SelectMeetListView(em_Menu_CurMeet);
			if ( m_plsCurMeet != NULL )
			{
				m_plsCurMeet->SetYOffset(0);
			}
			CurMeetListRefresh();
		}
		break;
	case em_Menu_OrderMeet:
		{
			SelectMeetListView(em_Menu_OrderMeet);
			if ( m_plsOrderMeet != NULL )
			{
				m_plsOrderMeet->SetYOffset(0);
			}
			MeetTmpRefresh();
		}
		break;
	default:
		{
		}
		break;
	}

	if ( m_plsOrderMeet != NULL )
	{
		m_plsOrderMeet->SetYOffset(0);
		m_plsOrderMeet->SetSelItem(-1);
	}

	if( m_plsCurMeet != NULL )
	{
		m_plsCurMeet->SetYOffset(0);
		m_plsCurMeet->SetSelItem(-1);
	}

	return 0L;
}

void CMeetinfoLogic::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDlgChild::OnShowWindow(bShow, nStatus);

	if( m_pconfCtrlIF == NULL )
	{
		BUSINESSIFPTR->GetCtrlInterface(&m_pconfCtrlIF);
	}
	
	if( m_pconfCtrlIF != NULL )
	{
		m_pconfCtrlIF->SetNotifyWnd( this->m_hWnd );
 	} 
}

void CMeetinfoLogic::InitDlg() 
{
	m_etSearch.SetWindowText("");
	ShowWindow(SW_HIDE); 
	m_bIsAllSel = FALSE;
    m_bShowMosaicHoriImg = TRUE;
	m_emCurPageMeetType = em_Menu_AllMeet;

	MeetTmpRefresh();
	CurMeetListRefresh();

	if ( m_plsOrderMeet != NULL )
	{
		m_plsOrderMeet->SetYOffset(0);
		m_plsOrderMeet->SetSelItem(-1);
	}
	
	if( m_plsCurMeet != NULL )
	{
		m_plsCurMeet->SetYOffset(0);
		m_plsCurMeet->SetSelItem(-1);
	}

	SelectMeetListView(em_Menu_AllMeet);

	m_dlgMenubar.InitMenuBtn();
}

LRESULT CMeetinfoLogic::OnStartConfResult(WPARAM wParam, LPARAM lParam)
{
	TStartConfResult* tRe = reinterpret_cast<tagTStartConfResult*>(wParam);
	if ( tRe != NULL )
	{
		CMsgHandle::SendMessage( UI_UMS_START_CONFTEMPLATE_RSP,(WPARAM)(TStartConfResult*)tRe );	
	}

	return 0L;
}

BOOL CMeetinfoLogic::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if ( (HWND)lParam == m_etSearch.GetSafeHwnd() )
	{
		if ( HIWORD(wParam) == EN_CHANGE )
		{
			m_setCurConfSelectedIconItem.clear();
			m_setOrderConfSelectedIconItem.clear();
			OnSearchEditChange();
			UpdateUIState();
		}
    }
	
	return CDlgChild::OnCommand(wParam, lParam);
}

void CMeetinfoLogic::UpdateUIState()
{
	s32 nCurOrderConfCount = m_tpOrderConflShowList.Size();
	s32 nCurConfCount = m_vecCurConflShowList.size();
	switch ( m_emCurPageMeetType )
	{
	case em_Menu_AllMeet:
		{
			s32 nSelSize = m_setCurConfSelectedIconItem.size() + m_setOrderConfSelectedIconItem.size();
			if ( nSelSize > 0 )
			{
				m_btnCloseMeeting.EnableWindow(TRUE);
				
				if ( nSelSize == nCurConfCount + nCurOrderConfCount )
				{
					m_bIsAllSel = TRUE;
					m_btnAllSel.SetImage( IDR_PNG_BTN_CANCELALLSEL, IDR_PNG_BTN_CANCELALLSELDOWN, IDR_PNG_BTN_CANCELALLSELDIS );
				}
				else
				{
					m_bIsAllSel = FALSE;
					m_btnAllSel.SetImage( IDR_PNG_BTN_ALLSEL, IDR_PNG_BTN_ALLSELDOWN, IDR_PNG_BTN_ALLSELDIS );
				}
			}
			else
			{
				m_btnCloseMeeting.EnableWindow(FALSE);
				
				m_bIsAllSel = FALSE;
				m_btnAllSel.SetImage( IDR_PNG_BTN_ALLSEL, IDR_PNG_BTN_ALLSELDOWN, IDR_PNG_BTN_ALLSELDIS );
				m_btnAllSel.EnableWindow(FALSE);
			}
			
			if ( nCurConfCount + nCurOrderConfCount == 0 )
			{
				m_btnAllSel.EnableWindow(FALSE);
			}
			else
			{
				m_btnAllSel.EnableWindow(TRUE);
			}
		}
		break;
	case em_Menu_CurMeet:
		{
			s32 nSelSize = m_setCurConfSelectedIconItem.size();
			if ( nSelSize > 0 )
			{
				m_btnCloseMeeting.EnableWindow(TRUE);
				
				if ( nSelSize == nCurConfCount )
				{
					m_bIsAllSel = TRUE;
					m_btnAllSel.SetImage( IDR_PNG_BTN_CANCELALLSEL, IDR_PNG_BTN_CANCELALLSELDOWN, IDR_PNG_BTN_CANCELALLSELDIS );
				}
				else
				{
					m_bIsAllSel = FALSE;
					m_btnAllSel.SetImage( IDR_PNG_BTN_ALLSEL, IDR_PNG_BTN_ALLSELDOWN, IDR_PNG_BTN_ALLSELDIS );
				}
			}
			else
			{
				m_btnCloseMeeting.EnableWindow(FALSE);
				
				m_bIsAllSel = FALSE;
				m_btnAllSel.SetImage( IDR_PNG_BTN_ALLSEL, IDR_PNG_BTN_ALLSELDOWN, IDR_PNG_BTN_ALLSELDIS );
				m_btnAllSel.EnableWindow(FALSE);
			}
			
			if ( nCurConfCount == 0 )
			{
				m_btnAllSel.EnableWindow(FALSE);
			}
			else
			{
				m_btnAllSel.EnableWindow(TRUE);
			}
		}
		break;
	case em_Menu_OrderMeet:
		{
			s32 nSelSize = m_setOrderConfSelectedIconItem.size();
			if ( nSelSize > 0 )
			{
				m_btnCloseMeeting.EnableWindow(TRUE);
				
				if ( nSelSize == nCurOrderConfCount )
				{
					m_bIsAllSel = TRUE;
					m_btnAllSel.SetImage( IDR_PNG_BTN_CANCELALLSEL, IDR_PNG_BTN_CANCELALLSELDOWN, IDR_PNG_BTN_CANCELALLSELDIS );
				}
				else
				{
					m_bIsAllSel = FALSE;
					m_btnAllSel.SetImage( IDR_PNG_BTN_ALLSEL, IDR_PNG_BTN_ALLSELDOWN, IDR_PNG_BTN_ALLSELDIS );
				}
			}
			else
			{
				m_btnCloseMeeting.EnableWindow(FALSE);
				
				m_bIsAllSel = FALSE;
				m_btnAllSel.SetImage( IDR_PNG_BTN_ALLSEL, IDR_PNG_BTN_ALLSELDOWN, IDR_PNG_BTN_ALLSELDIS );
				m_btnAllSel.EnableWindow(FALSE);
			}
			
			if ( nCurOrderConfCount == 0 )
			{
				m_btnAllSel.EnableWindow(FALSE);
			}
			else
			{
				m_btnAllSel.EnableWindow(TRUE);
			}
		}
		break;
	default:
		{
		}
		break;
	}
}

HRESULT CMeetinfoLogic::OnHideAUtoHideWnd( WPARAM wparam, LPARAM lparam )
{   
	if ( m_dlgMenubar.GetSafeHwnd() != NULL )
	{
		BOOL bRet = m_dlgMenubar.SetWindowPos(NULL, -30000, -30000, 0, 0, SWP_HIDEWINDOW|SWP_NOACTIVATE ); 
		//OspPrintf( TRUE, FALSE, "\n------ShowWindow Return: %d------", bRet );
	}

	return S_OK;
}

LRESULT CMeetinfoLogic::OnHungupConfReason( WPARAM wparam, LPARAM lparam )
{
	u16 wConfID = (u16)wparam;
	u32 wErrorID = (u32)lparam;

	BOOL bErrorFlag = FALSE;
	CString strError;
	strError = "会议";	
	strError += FindConfNameById(wConfID);
	strError += "结束  ";
	strError += "结束原因：";
	switch( wErrorID )
	{
	case TP_UMS_ChairIsUMS:
	case TP_UMS_ChairIsMT:
	case TP_UMS_ChairIsMCU:
		{
			strError += "主席只能是网呈会场";
			bErrorFlag = TRUE;
		}
		break;
	case TP_UMS_SuperDropped:
		{
			strError += "上级掉线";
			bErrorFlag = TRUE;
		}
		break;
	case TP_UMS_AdapterQuit:
		{
			strError += "接入板掉线";
			bErrorFlag = TRUE;
		}
		break;
	case TP_UMS_AllEpHungUp:
		{
			strError += "所有会场挂断";
			bErrorFlag = TRUE;
		}
		break;
	case TP_UMS_BasDisConnect:
		{
			strError += "适配板掉线";
			bErrorFlag = TRUE;
		}
		break;

	case TP_UMS_BasStartFail:
		{
			strError += "开启适配失败";
			bErrorFlag = TRUE;
		}
		break;
	case TP_UMS_MediaTransQuit:
		{
			strError += "转发板掉线";
			bErrorFlag = TRUE;
		}
		break;
	case TP_UMS_ChairIsFailed:
		{
			strError += "主席未上线";
			bErrorFlag = TRUE;
		}
		break;
	default:
		{
		}
	}
	
	if ( bErrorFlag )
	{
		MESSAGEWND(strError);
	}

	return 0L;
}

CString CMeetinfoLogic::FindConfNameById(u16 wConfId)
{
	if ( wConfId == INVALID_WORD )
	{
		return "";
	}
	
	CString strConfName;
	for ( s32 nIndex = 0; nIndex < m_vecCurConfRefreshList.size(); nIndex++ )
	{	
		TCMSConf tCmsConf = m_vecCurConfRefreshList[nIndex];
		u16 wConfNum = tCmsConf.m_wConfID;
		if ( wConfNum == wConfId )
		{
			strConfName = tCmsConf.m_achConfName;
		}
	}	
	
	return strConfName;
}