// CMainLogic.cpp : implementation file
//
#include "stdafx.h"
#include "umcwebproj.h"
#include "mainLogic.h"
#include "loginLogic.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainLogic dialog
static s32 g_nCurShiningCount = 0;
BOOL m_gIconShining;

extern CMainLogic* g_pMainDlg;
extern CLoginLogic* m_pLoginDlg;

extern float CUR_SCREEN_WIDTH_PER;
extern float CUR_SCREEN_HEIGHT_PER;
CMainLogic::CMainLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CMainLogic::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainLogic)
	//}}AFX_DATA_INIT
	m_IsCreateGrp = TRUE;
	m_bShowMosaicHoriImg = FALSE;
	m_dwBkResourceID = IDR_PNG_MAINWND_BK;
	m_cwndCurrent = NULL;
	m_gIconShining = FALSE;

	CPrintCtrl::GetPrintCtrl()->PrintAllMsg();
}

void CMainLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainLogic)
	DDX_Control(pDX, IDC_Btn_ADDREDIT, m_btnAddrEdit);
	DDX_Control(pDX, IDC_Btn_VTR, m_btnVTRSet);
	DDX_Control(pDX, IDC_BUTTON_WARNING, m_btnWarning);
	DDX_Control(pDX, IDC_STATIC_Title, m_stTitle);
	DDX_Control(pDX, IDC_STATIC_TOOLBARBK, m_stToolbarBK);
	DDX_Control(pDX, IDC_BUTTON_LOGO, m_btnLogo);
	DDX_Control(pDX, IDC_BtnMeetingTemplate, m_btnMeetTmp);
	DDX_Control(pDX, IDC_BtnMeetingList, m_btnMeetInfo);
	DDX_Control(pDX, IDC_BtnUser, m_btnUser);
	DDX_Control(pDX, IDC_BtnTvw, m_btnTvw);
	DDX_Control(pDX, IDC_BtnPublic, m_btnPublicAddr);
	DDX_Control(pDX, IDC_BtnLocal, m_btnLocalAddr);
	DDX_Control(pDX, IDC_Btn_System, m_btnSysSet);
	DDX_Control(pDX, IDC_Btn_Close, m_btnLogOff);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMainLogic, CDlgChild)
	//{{AFX_MSG_MAP(CMainLogic)
	ON_BN_CLICKED(IDC_Btn_Close, OnBtnLogoff)
	ON_BN_CLICKED(IDC_Btn_System, OnBtnSystemSet)
	ON_BN_CLICKED(IDC_BtnLocal, OnBtnLocalAddr)
	ON_BN_CLICKED(IDC_BUTTON_LOGO, OnBtnLogo)
	ON_BN_CLICKED(IDC_BtnMeetingList, OnBtnMeetInfo)
	ON_BN_CLICKED(IDC_BtnMeetingTemplate, OnBtnMeetTmp)
	ON_BN_CLICKED(IDC_BtnPublic, OnBtnPublicAddr)
	ON_BN_CLICKED(IDC_BtnTvw, OnBtnTvw)
	ON_BN_CLICKED(IDC_BtnUser, OnBtnUser)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_WARNING, OnButtonWarning)
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_DEF_UPDATE_WARNING_ICON, OnWarningIconNotify)
	ON_WM_TIMER()
	ON_MESSAGE(UI_UMS_CONNECTED, OnLoginResult)
	ON_BN_CLICKED(IDC_Btn_VTR, OnBtnVTRSet)
	ON_MESSAGE(UI_UMS_DISCONNECTED, OnUmsDisconn)
	ON_MESSAGE(UI_UMS_GRAB_LOGIN_NOTIFY, OnGrab)
	ON_BN_CLICKED(IDC_Btn_ADDREDIT, OnBtnADDREDIT)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMain message handlers
BOOL CMainLogic::InitControlPane()
{
	//初始化界面控件图片控件
	m_stToolbarBK.SetImage( IDR_PNG_MAINWND_TOOLBARBK );
	m_btnLogo.SetImage( IDR_PNG_MAINWND_BTN_HOMESEL, IDR_PNG_MAINWND_BTN_HOMEDOWN, IDR_PNG_MAINWND_BTN_HOMESEL,
		IDR_PNG_MAINWND_BTN_HOME, IDR_PNG_MAINWND_BTN_HOMEDOWN, IDR_PNG_MAINWND_BTN_HOME );
	m_btnLogo.SetButtonStyle( BS_AUTORADIOBUTTON );
	m_btnWarning.SetImage( IDR_PNG_WARNINGWND_BTN, IDR_PNG_WARNINGWND_BTN, IDR_PNG_WARNINGWND_BTN, 
		IDR_PNG_WARNINGWND_BTN,IDR_PNG_WARNINGWND_BTN,IDR_PNG_WARNINGWND_BTN);
    m_btnWarning.SetButtonStyle( BS_AUTOCHECKBOX );
	m_btnWarning.SetCheck( BST_UNCHECKED);

	m_btnLocalAddr.SetImage( IDR_PNG_MAINWND_BTN_LOCALADDRSEL, IDR_PNG_MAINWND_BTN_LOCALADDRDOWN, IDR_PNG_MAINWND_BTN_LOCALADDRSEL, 
		                           IDR_PNG_MAINWND_BTN_LOCALADDR,IDR_PNG_MAINWND_BTN_LOCALADDRDOWN,IDR_PNG_MAINWND_BTN_LOCALADDR);
    m_btnLocalAddr.SetButtonStyle( BS_AUTORADIOBUTTON );

	m_btnPublicAddr.SetImage( IDR_PNG_MAINWND_BTN_PUBLICADDRSEL, IDR_PNG_MAINWND_BTN_PUBLICADDRDOWN, IDR_PNG_MAINWND_BTN_PUBLICADDRSEL, 
		IDR_PNG_MAINWND_BTN_PUBLICADDR,IDR_PNG_MAINWND_BTN_PUBLICADDRDOWN,IDR_PNG_MAINWND_BTN_PUBLICADDR);
    m_btnPublicAddr.SetButtonStyle( BS_AUTORADIOBUTTON );
 
	m_btnMeetTmp.SetImage( IDR_PNG_MAINWND_BTN_MEETTMPSEL, IDR_PNG_MAINWND_BTN_MEETTMPDOWN, IDR_PNG_MAINWND_BTN_MEETTMPSEL, 
		IDR_PNG_MAINWND_BTN_MEETTMP,IDR_PNG_MAINWND_BTN_MEETTMPDOWN,IDR_PNG_MAINWND_BTN_MEETTMP);
    m_btnMeetTmp.SetButtonStyle( BS_AUTORADIOBUTTON );

	m_btnMeetInfo.SetImage( IDR_PNG_MAINWND_BTN_MEETINFOSEL, IDR_PNG_MAINWND_BTN_MEETINFODOWN, IDR_PNG_MAINWND_BTN_MEETINFOSEL, 
		IDR_PNG_MAINWND_BTN_MEETINFO,IDR_PNG_MAINWND_BTN_MEETINFODOWN,IDR_PNG_MAINWND_BTN_MEETINFO);
    m_btnMeetInfo.SetButtonStyle( BS_AUTORADIOBUTTON );

	m_btnTvw.SetImage( IDR_PNG_MAINWND_BTN_TVWMANAGESEL, IDR_PNG_MAINWND_BTN_TVWMANAGEDOWN, IDR_PNG_MAINWND_BTN_TVWMANAGESEL,
		IDR_PNG_MAINWND_BTN_TVWMANAGE,IDR_PNG_MAINWND_BTN_TVWMANAGEDOWN,IDR_PNG_MAINWND_BTN_TVWMANAGE);
	m_btnTvw.SetButtonStyle( BS_AUTORADIOBUTTON );

	m_btnSysSet.SetImage( IDR_PNG_MAINWND_BTN_SYSSETSEL, IDR_PNG_MAINWND_BTN_SYSSETDOWN, IDR_PNG_MAINWND_BTN_SYSSETSEL, 
		IDR_PNG_MAINWND_BTN_SYSSET,IDR_PNG_MAINWND_BTN_SYSSETDOWN,IDR_PNG_MAINWND_BTN_SYSSET);
    m_btnSysSet.SetButtonStyle( BS_AUTORADIOBUTTON );

	m_btnUser.SetImage( IDR_PNG_MAINWND_BTN_USERSEL, IDR_PNG_MAINWND_BTN_USERDOWN, IDR_PNG_MAINWND_BTN_USERSEL, 
		IDR_PNG_MAINWND_BTN_USER,IDR_PNG_MAINWND_BTN_USERDOWN,IDR_PNG_MAINWND_BTN_USER);
    m_btnUser.SetButtonStyle( BS_AUTORADIOBUTTON );



	m_btnVTRSet.SetImage( IDR_PNG_MAINWND_BTN_VTRSEL, IDR_PNG_MAINWND_BTN_VTRDOWN, IDR_PNG_MAINWND_BTN_VTRSEL, 
		IDR_PNG_MAINWND_BTN_VTR,IDR_PNG_MAINWND_BTN_VTRDOWN,IDR_PNG_MAINWND_BTN_VTR);
    m_btnVTRSet.SetButtonStyle( BS_AUTORADIOBUTTON );

	m_btnAddrEdit.SetImage( IDR_PNG_MAINWND_BTN_ADDREDIT_SEL, IDR_PNG_MAINWND_BTN_ADDREDIT_DOWN, IDR_PNG_MAINWND_BTN_ADDREDIT_SEL, 
		IDR_PNG_MAINWND_BTN_ADDREDIT,IDR_PNG_MAINWND_BTN_ADDREDIT_DOWN,IDR_PNG_MAINWND_BTN_ADDREDIT);
    m_btnAddrEdit.SetButtonStyle( BS_AUTORADIOBUTTON );


	m_btnLogOff.SetImage( IDR_PNG_MAINWND_BTN_LOGOFF, IDR_PNG_MAINWND_BTN_LOGOFFDOWN, IDR_PNG_MAINWND_BTN_LOGOFF );

	

	CRect rectClient( 0, 0, /*BASE_SCREEN_WIDTH*/BASE_SCREEN_WIDTH_INIE*CUR_SCREEN_WIDTH_PER, BASE_SCREEN_HEIGHT_INIE*CUR_SCREEN_HEIGHT_PER );
	this->SetWindowPos( NULL, 0, 0, rectClient.Width(), rectClient.Height(), SWP_SHOWWINDOW ); 

	m_stTitle.SetWindowPos( NULL, 0 + m_stToolbarBK.GetImageSize().cx*CUR_SCREEN_WIDTH_PER,  13, rectClient.Width() - m_stToolbarBK.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, 32, SWP_SHOWWINDOW );
	m_stTitle.SetWindowText("网呈统一管理控制台");
	m_stTitle.SetTextAlign(StringAlignmentCenter);
	m_stTitle.SetTextColor(Color( 38, 54, 66 ));
	m_stTitle.SetFont( 18, "微软雅黑" );

	m_btnWarning.SetWindowPos( &m_stToolbarBK, rectClient.Width() - (7  + m_btnWarning.GetImageSize().cx)*CUR_SCREEN_WIDTH_PER, 3*CUR_SCREEN_HEIGHT_PER
		, m_btnWarning.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnWarning.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

	CSize sz( 0, 0 );
	sz = m_btnLogo.GetImageSize();
	m_btnLogo.SetWindowPos( &m_stToolbarBK, 6*CUR_SCREEN_WIDTH_PER, 13/*(49 + 6)*/*CUR_SCREEN_HEIGHT_PER, sz.cx*CUR_SCREEN_WIDTH_PER, sz.cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	
	sz = m_btnLocalAddr.GetImageSize();
	m_btnLogo.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
// 	m_btnLocalAddr.SetWindowPos( &m_stToolbarBK, 5*CUR_SCREEN_WIDTH_PER, rectClient.bottom + 4*CUR_SCREEN_HEIGHT_PER, sz.cx*CUR_SCREEN_WIDTH_PER, sz.cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
//  m_btnLocalAddr.GetWindowRect(&rectClient);
// 	ScreenToClient( &rectClient );
// 	m_btnPublicAddr.SetWindowPos( &m_stToolbarBK, 5*CUR_SCREEN_WIDTH_PER, rectClient.bottom + 4*CUR_SCREEN_HEIGHT_PER , sz.cx*CUR_SCREEN_WIDTH_PER, sz.cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
// 	m_btnPublicAddr.GetWindowRect(&rectClient);
// 	ScreenToClient( &rectClient );
	m_btnAddrEdit.SetWindowPos( &m_stToolbarBK, 6*CUR_SCREEN_WIDTH_PER, rectClient.bottom + 4*CUR_SCREEN_HEIGHT_PER, sz.cx*CUR_SCREEN_WIDTH_PER, sz.cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_btnAddrEdit.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );

	m_btnMeetTmp.SetWindowPos( &m_stToolbarBK, 6*CUR_SCREEN_WIDTH_PER, rectClient.bottom + 4*CUR_SCREEN_HEIGHT_PER, sz.cx*CUR_SCREEN_WIDTH_PER, sz.cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
 	m_btnMeetTmp.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	m_btnMeetInfo.SetWindowPos( &m_stToolbarBK, 6*CUR_SCREEN_WIDTH_PER, rectClient.bottom + 4*CUR_SCREEN_HEIGHT_PER, sz.cx*CUR_SCREEN_WIDTH_PER, sz.cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
 	m_btnMeetInfo.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	m_btnTvw.SetWindowPos( &m_stToolbarBK, 6*CUR_SCREEN_WIDTH_PER, rectClient.bottom + 4*CUR_SCREEN_HEIGHT_PER, sz.cx*CUR_SCREEN_WIDTH_PER, sz.cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
  	m_btnTvw.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );

	m_btnVTRSet.SetWindowPos( &m_stToolbarBK, 6*CUR_SCREEN_WIDTH_PER, rectClient.bottom + 4*CUR_SCREEN_HEIGHT_PER, sz.cx*CUR_SCREEN_WIDTH_PER, sz.cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_btnVTRSet.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );


	m_btnUser.SetWindowPos( &m_stToolbarBK, 6*CUR_SCREEN_WIDTH_PER, rectClient.bottom + 4*CUR_SCREEN_HEIGHT_PER, sz.cx*CUR_SCREEN_WIDTH_PER, sz.cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_btnUser.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );


	m_btnSysSet.SetWindowPos( &m_stToolbarBK, 6*CUR_SCREEN_WIDTH_PER, rectClient.bottom + 4*CUR_SCREEN_HEIGHT_PER, sz.cx*CUR_SCREEN_WIDTH_PER, sz.cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_btnSysSet.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );	

	m_btnLogOff.SetWindowPos( &m_stToolbarBK, 6*CUR_SCREEN_WIDTH_PER, rectClient.bottom + 4*CUR_SCREEN_HEIGHT_PER, sz.cx*CUR_SCREEN_WIDTH_PER, sz.cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

	m_btnLogOff.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );

	m_stToolbarBK.SetWindowPos( NULL, 1*CUR_SCREEN_WIDTH_PER, 5/*49*/*CUR_SCREEN_HEIGHT_PER, m_stToolbarBK.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, 
		(rectClient.bottom/* - 44*/)*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

	return TRUE;
}

BOOL CMainLogic::InitChildWindow()
{
	try
	{
//		m_dlgLocalAddr.Create( IDD_DIALOG_LOCALADDRBOOK, this); 
//		m_dlgLocalAddr.SetWindowPos( NULL, 110*CUR_SCREEN_WIDTH_PER, 48*CUR_SCREEN_HEIGHT_PER, 1226*CUR_SCREEN_WIDTH_PER, 600*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW);		 		 
    
// 		m_dlgGlobalAddrbook.Create( IDD_DIALOG_GLOBALADDRBOOK, this ); 
// 		m_dlgGlobalAddrbook.SetWindowPos( NULL, 110*CUR_SCREEN_WIDTH_PER, 48*CUR_SCREEN_HEIGHT_PER, 1226*CUR_SCREEN_WIDTH_PER, 600*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );	 		 
		  
		m_dlgMeetTmp.Create( IDD_DIALOG_MEETTEMPLATE, this); 
		m_dlgMeetTmp.SetWindowPos( NULL, 110*CUR_SCREEN_WIDTH_PER, 48*CUR_SCREEN_HEIGHT_PER, 1226*CUR_SCREEN_WIDTH_PER, 600*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );		 	 
	
		m_dlgMeetInfo.Create( IDD_DIALOG_MEETINFO, this); 
		m_dlgMeetInfo.SetWindowPos( NULL, 110*CUR_SCREEN_WIDTH_PER, 48*CUR_SCREEN_HEIGHT_PER, 1226*CUR_SCREEN_WIDTH_PER, 600*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW ); 	 	 
	 
		m_dlgSysSet.Create( IDD_DIALOG_SYSTEMSET, this); 
		m_dlgSysSet.SetWindowPos( NULL, 110*CUR_SCREEN_WIDTH_PER, 48*CUR_SCREEN_HEIGHT_PER, 1226*CUR_SCREEN_WIDTH_PER, 600*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW ); 	

		m_dlgUser.Create( IDD_DIALOG_USERMANAGE, this); 
		m_dlgUser.SetWindowPos( NULL, 110*CUR_SCREEN_WIDTH_PER, 48*CUR_SCREEN_HEIGHT_PER, 1226*CUR_SCREEN_WIDTH_PER, 600*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW ); 	
	 
		m_dlgTvw.Create( IDD_DIALOG_TVWMANAGE, this); 
		m_dlgTvw.SetWindowPos( NULL, 110*CUR_SCREEN_WIDTH_PER, 48*CUR_SCREEN_HEIGHT_PER, 1226*CUR_SCREEN_WIDTH_PER, 600*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW ); 	
	 
		m_dlgVTR.Create( IDD_DIALOG_VTRSET, this); 
		m_dlgVTR.SetWindowPos( NULL, 110*CUR_SCREEN_WIDTH_PER, 48*CUR_SCREEN_HEIGHT_PER, 1226*CUR_SCREEN_WIDTH_PER, 600*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW ); 	

		m_dlgAddrEdit.Create( IDD_DIALOG_ADDREDIT, this); 
		m_dlgAddrEdit.SetWindowPos( NULL, 110*CUR_SCREEN_WIDTH_PER, 48*CUR_SCREEN_HEIGHT_PER, 1226*CUR_SCREEN_WIDTH_PER, 600*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW ); 	


		CRect rectWarning;
		m_btnWarning.GetWindowRect(&rectWarning);
		ScreenToClient(&rectWarning);

		return TRUE;
	}
	catch (CException* e)
	{
		s8 chErr[1024];
		memset( chErr, 0, 1024 );
		e->GetErrorMessage( chErr,1024 );
		CString strErr;
		strErr += "文件操作失败，错误码";
		strErr += chErr;
		MESSAGEWND( strErr );
		return FALSE;
	}
}

BOOL CMainLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();

	if( !InitControlPane() )
	{
		return FALSE;
	}

	BUSINESSIFPTR->SetNotifyWnd( this->m_hWnd );

	if( !InitChildWindow() )
	{
		return FALSE;
	}

	OnBtnLogo();
	m_btnWarning.SetBindWnd( CTransparentDlgWarning::GetDlgPtr()->GetSafeHwnd() );

	SetTimer(5000, 2000, NULL);
	return TRUE;
}

//活动窗口显示
void CMainLogic::ShowActiveWindow(EM_CURRENT_WND_VIEW_TYPE emWndType)
{   
	if( m_dlgMeetTmp.m_dlgCalendar.GetSafeHwnd() != NULL && m_dlgMeetTmp.m_dlgCalendar.IsWindowVisible() )
	{
		m_dlgMeetTmp.m_dlgCalendar.ShowWindow(SW_HIDE);
		 
	}

	if( m_dlgMeetInfo.m_dlgMenubar.IsWindowVisible() )
	{
		m_dlgMeetInfo.m_dlgMenubar.ShowWindow(SW_HIDE);
	}

	m_emWndType = emWndType;
	BOOL bShowFlag = FALSE;
	CWnd* cwndCurrent = NULL;
	switch( emWndType )
	{
// 		case em_WND_LOCALADDR:
// 			{
// 				m_pImageBK = CSrcManage::GetImage( IDR_PNG_MAINWNDEMY_BK, "PNG" );
// 				if( m_cwndCurrent != NULL   )
// 				{
// 					bShowFlag = m_cwndCurrent->GetSafeHwnd() == m_dlgLocalAddr.GetSafeHwnd()?FALSE:TRUE;
// 				}
// 				else
// 				{
// 					bShowFlag = TRUE;
// 				}
// 				cwndCurrent = &m_dlgLocalAddr;
// 
// 				 
// 			    HIDEMESSAGEWND
// 				 
// 			}
// 			break;
// 		case em_WND_PUBLICADDR:
// 			{
// 				m_pImageBK = CSrcManage::GetImage( IDR_PNG_MAINWNDEMY_BK, "PNG" );
// 				if( m_cwndCurrent != NULL  )
// 				{
// 					bShowFlag = m_cwndCurrent->GetSafeHwnd() == m_dlgGlobalAddrbook.GetSafeHwnd()?FALSE:TRUE;
// 				}
// 				else
// 				{
// 					bShowFlag = TRUE;
// 				}
// 				cwndCurrent = &m_dlgGlobalAddrbook;
// 			}
// 			break;
		case em_WND_MEETTMP:
			{
				m_pImageBK = CSrcManage::GetImage( IDR_PNG_MAINWNDEMY_BK, "PNG" );
				if( m_cwndCurrent != NULL  )
				{
					bShowFlag = m_cwndCurrent->GetSafeHwnd() == m_dlgMeetTmp.GetSafeHwnd()?FALSE:TRUE;
				}
				else
				{
					bShowFlag = TRUE;
				}
				cwndCurrent = &m_dlgMeetTmp;

				HIDEMESSAGEWND
			}
			break;
		case em_WND_MEETINFO:
			{
				m_pImageBK = CSrcManage::GetImage( IDR_PNG_MAINWNDEMY_BK, "PNG" );
				if( m_cwndCurrent != NULL   )
				{
					bShowFlag = m_cwndCurrent->GetSafeHwnd() == m_dlgMeetInfo.GetSafeHwnd()?FALSE:TRUE;
				}
				else
				{
					bShowFlag = TRUE;
				}
				cwndCurrent = &m_dlgMeetInfo;
			}
			break;
		case em_WND_TVW:
			{
				m_pImageBK = CSrcManage::GetImage( IDR_PNG_MAINWNDEMY_BK, "PNG" );
				if( m_cwndCurrent != NULL   )
				{
					bShowFlag = m_cwndCurrent->GetSafeHwnd() == m_dlgTvw.GetSafeHwnd()?FALSE:TRUE;
				}
				else
				{
					bShowFlag = TRUE;
				}
				cwndCurrent = &m_dlgTvw;
			}
			break;	
		case em_WND_SYSTEMSET:
			{
				m_pImageBK = CSrcManage::GetImage( IDR_PNG_MAINWNDEMY_BK, "PNG" );
				if( m_cwndCurrent != NULL  )
				{
					bShowFlag = m_cwndCurrent->GetSafeHwnd() == m_dlgSysSet.GetSafeHwnd()?FALSE:TRUE;
				}
				else
				{
					bShowFlag = TRUE;
				}
				cwndCurrent = &m_dlgSysSet;

		    	HIDEMESSAGEWND
			}
			break;
		case em_WND_VTR:
			{
				m_pImageBK = CSrcManage::GetImage( IDR_PNG_MAINWNDEMY_BK, "PNG" );
				if( m_cwndCurrent != NULL  )
				{
					bShowFlag = m_cwndCurrent->GetSafeHwnd() == m_dlgVTR.GetSafeHwnd()?FALSE:TRUE;
				}
				else
				{
					bShowFlag = TRUE;
				}
				cwndCurrent = &m_dlgVTR;
				
				HIDEMESSAGEWND
			}
			break;
		case em_WND_USER:
			{
				m_pImageBK = CSrcManage::GetImage( IDR_PNG_MAINWNDEMY_BK, "PNG" );
				if( m_cwndCurrent != NULL   )
				{
					bShowFlag = m_cwndCurrent->GetSafeHwnd() == m_dlgUser.GetSafeHwnd()?FALSE:TRUE;
				}
				else
				{
					bShowFlag = TRUE;
				}
				cwndCurrent = &m_dlgUser;

				HIDEMESSAGEWND
			}
 			break;
		case em_WND_ADDREDIT:
			{
				m_pImageBK = CSrcManage::GetImage( IDR_PNG_MAINWNDEMY_BK, "PNG" );
				if( m_cwndCurrent != NULL   )
				{
					bShowFlag = m_cwndCurrent->GetSafeHwnd() == m_dlgAddrEdit.GetSafeHwnd()?FALSE:TRUE;
				}
				else
				{
					bShowFlag = TRUE;
				}
				cwndCurrent = &m_dlgAddrEdit;
				
				HIDEMESSAGEWND
			}
 			break;
		default:
			{
				m_pImageBK = CSrcManage::GetImage( IDR_PNG_MAINWND_BK, "PNG" );
				cwndCurrent = NULL;
				bShowFlag = TRUE;
				HIDEMESSAGEWND
			}
			break;
	}

	if( bShowFlag )
	{
		if( m_cwndCurrent != NULL && m_cwndCurrent->GetSafeHwnd() != NULL )
		{
			m_cwndCurrent->ShowWindow(FALSE);
			m_cwndCurrent = NULL;
		}
			
		if( cwndCurrent != NULL )
		{
			cwndCurrent->ShowWindow(TRUE);
			m_cwndCurrent = cwndCurrent;
		}
	} 
}

void CMainLogic::OnBtnLocalAddr() 
{   
    m_btnLocalAddr.SetCheck( BST_CHECKED);
	ShowActiveWindow(em_WND_LOCALADDR);
}

void CMainLogic::OnBtnPublicAddr() 
{
	m_btnPublicAddr.SetCheck( BST_CHECKED);
	ShowActiveWindow(em_WND_PUBLICADDR);
}

void CMainLogic::OnBtnMeetTmp() 
{
	m_btnMeetTmp.SetCheck( BST_CHECKED);
	ShowActiveWindow(em_WND_MEETTMP);
}

void CMainLogic::OnBtnMeetInfo() 
{
	m_btnMeetInfo.SetCheck( BST_CHECKED);
	ShowActiveWindow(em_WND_MEETINFO);
}

void CMainLogic::OnBtnTvw() 
{
	m_btnTvw.SetCheck( BST_CHECKED);
	ShowActiveWindow(em_WND_TVW);
}

void CMainLogic::OnBtnSystemSet() 
{	
	m_btnSysSet.SetCheck( BST_CHECKED);
	ShowActiveWindow(em_WND_SYSTEMSET);
}

void CMainLogic::OnBtnUser() 
{
	m_btnUser.SetCheck( BST_CHECKED);
	ShowActiveWindow(em_WND_USER);
}

void CMainLogic::OnBtnLogoff() 
{   
	s32 nRet = 0;
	MESSAGEWNDBOX( "是否注销当前系统？", this , nRet, TRUE );

	BOOL bCon = BUSINESSIFPTR->IsConnectedUms();
	if( nRet == IDOK )
	{ 
		RevertTabPage();
		if ( bCon )
		{  
			BUSINESSIFPTR->DisconnectUms();
		}
	}
}

void CMainLogic::OnBtnLogo() 
{
	m_btnLogo.SetCheck( BST_CHECKED);
	ShowActiveWindow(em_WND_PAGECLEAN);		
}

LRESULT CMainLogic::OnUmsDisconn(WPARAM wParam, LPARAM lParam)
{   
	RevertTabPage();

	//收到断链消息，关闭当前窗口 
	InitDlg();	
 
	//BOOL bIsShowMsgBox =  ISMSGBOXVISIBLE( FALSE ) ;
	if ( /*!bIsShowMsgBox &&*/ m_pLoginDlg != NULL  )
	{   
		ShowWindow( SW_HIDE );
		m_pLoginDlg->ShowWindow(SW_SHOW);
	}

	//发送背景色更新消息
	CMsgHandle::SendMessage( WM_DEF_CHANGEBKCOLOR, FALSE );

	HIDEMESSAGEWND
 
	return S_OK;
}

LRESULT CMainLogic::OnGrab(WPARAM wParam, LPARAM lParam)
{ 
	//ISMSGBOXVISIBLE( TRUE )

	RevertTabPage();
 
	BUSINESSIFPTR->DisconnectUms();
	if ( m_pLoginDlg != NULL )
	{
		ShowWindow( SW_HIDE );
		m_pLoginDlg->ShowWindow(SW_SHOW);
	}
	
	InitDlg();  //120810  ldy  修正抢占未初始化页面问题

	s32 nRet = 0;
	MESSAGEWNDBOX( "您已经被强制下线，该账户已在另一个地方登录", this , nRet , FALSE );

	return S_OK;
}

void CMainLogic::OnDestroy() 
{
	//m_dlgLocalAddr.DestroyWindow();
	//m_dlgGlobalAddrbook.DestroyWindow();
	m_dlgMeetTmp.DestroyWindow();
	m_dlgMeetInfo.DestroyWindow();
	m_dlgSysSet.DestroyWindow();
	m_dlgUser.DestroyWindow();
	m_dlgTvw.DestroyWindow();
	m_dlgVTR.DestroyWindow();
	m_dlgAddrEdit.DestroyWindow();

	m_cwndCurrent = NULL;

	KillTimer(5000);
	CDlgChild::OnDestroy();
}

void CMainLogic::OnSize(UINT nType, int cx, int cy) 
{
	CDlgChild::OnSize(nType, cx, cy);

}

void CMainLogic::OnButtonWarning() 
{   
	s32 nCheck = m_btnWarning.GetCheck();
	if ( nCheck == BST_UNCHECKED ) 
	{
		CTransparentDlgWarning::GetDlgPtr()->ShowWindow(SW_HIDE);
	}
	else
	{
 	    CTransparentDlgWarning::GetDlgPtr()->ShowWindow(SW_SHOW);
   
		CRect rectWarning;
		m_btnWarning.GetWindowRect(&rectWarning);
		CTransparentDlgWarning::GetDlgPtr()->SetWindowPos(NULL, rectWarning.left + m_btnWarning.GetImageSize().cx - 359 - 38, 
			      rectWarning.top, 359, 313, SWP_SHOWWINDOW ); 

	}
}

void CMainLogic::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CDlgChild::OnLButtonDown(nFlags, point);
}

LRESULT CMainLogic::OnWarningIconNotify(WPARAM wParam, LPARAM lParam)
{
	m_gIconShining = static_cast<BOOL>(lParam);

	OnTimer( 2 );
	SetTimer( 2, 500, NULL );

	return 0L;
}

void CMainLogic::OnTimer(UINT nIDEvent) 
{	
	//ldy 120912 修改提醒为一直闪烁直到用户点击查看
	if ( CTransparentDlgWarning::GetDlgPtr()->IsWindowVisible() )
	{
		m_btnWarning.SetImage( IDR_PNG_WARNINGWND_BTN, IDR_PNG_WARNINGWND_BTN, IDR_PNG_WARNINGWND_BTN, 
			IDR_PNG_WARNINGWND_BTN,IDR_PNG_WARNINGWND_BTN,IDR_PNG_WARNINGWND_BTN);
		g_nCurShiningCount = 0;
		m_gIconShining = FALSE;
		KillTimer(2);
	}

	if( nIDEvent == 2 && m_gIconShining )
	{	
		++g_nCurShiningCount;

		if ( g_nCurShiningCount%2 == 1 )
		{
			m_btnWarning.SetImage( IDR_PNG_WARNINGWND_BTNACTIVE, IDR_PNG_WARNINGWND_BTN, IDR_PNG_WARNINGWND_BTNACTIVE, 
									IDR_PNG_WARNINGWND_BTNACTIVE,IDR_PNG_WARNINGWND_BTN,IDR_PNG_WARNINGWND_BTNACTIVE);
		}
		else
		{
			m_btnWarning.SetImage( IDR_PNG_WARNINGWND_BTN, IDR_PNG_WARNINGWND_BTNACTIVE, IDR_PNG_WARNINGWND_BTN, 
									IDR_PNG_WARNINGWND_BTN,IDR_PNG_WARNINGWND_BTNACTIVE,IDR_PNG_WARNINGWND_BTN);
		}

		UpdateData(FALSE);
	}

	if( nIDEvent == 2 && !m_gIconShining )
	{
		m_btnWarning.SetImage( IDR_PNG_WARNINGWND_BTN, IDR_PNG_WARNINGWND_BTN, IDR_PNG_WARNINGWND_BTN, 
									IDR_PNG_WARNINGWND_BTN,IDR_PNG_WARNINGWND_BTN,IDR_PNG_WARNINGWND_BTN);
	}


	if ( nIDEvent == 5000 )
	{
		switch ( m_emWndType )
		{
		case em_WND_ADDREDIT:
			{
				m_btnVTRSet.SetStatus(0);
				m_btnLogo.SetStatus(0);
				m_btnMeetTmp.SetStatus(0); 
				m_btnMeetInfo.SetStatus(0);
				m_btnUser.SetStatus(0);
				m_btnTvw.SetStatus(0);
				m_btnSysSet.SetStatus(0);

				HWND hWnd = ::GetFocus();
				if ( hWnd == m_btnVTRSet.GetSafeHwnd() || hWnd == m_btnLogo.GetSafeHwnd()
					|| hWnd == m_btnMeetTmp.GetSafeHwnd() || hWnd == m_btnMeetInfo.GetSafeHwnd()
					|| hWnd == m_btnUser.GetSafeHwnd() || hWnd == m_btnTvw.GetSafeHwnd()
					|| hWnd == m_btnSysSet.GetSafeHwnd() )
				{
					::SetFocus(NULL);
				}

				break;
			}
		case em_WND_MEETTMP:
			{
				m_btnAddrEdit.SetStatus(0);
				m_btnVTRSet.SetStatus(0);
				m_btnLogo.SetStatus(0);
				m_btnMeetInfo.SetStatus(0);
				m_btnUser.SetStatus(0);
				m_btnTvw.SetStatus(0);
				m_btnSysSet.SetStatus(0);

				HWND hWnd = ::GetFocus();
				if ( hWnd == m_btnVTRSet.GetSafeHwnd() || hWnd == m_btnLogo.GetSafeHwnd()
					|| hWnd == m_btnAddrEdit.GetSafeHwnd() || hWnd == m_btnMeetInfo.GetSafeHwnd()
					|| hWnd == m_btnUser.GetSafeHwnd() || hWnd == m_btnTvw.GetSafeHwnd()
					|| hWnd == m_btnSysSet.GetSafeHwnd() )
				{
					::SetFocus(NULL);
				}
				
				break;
			}
		case em_WND_MEETINFO:
			{
				m_btnAddrEdit.SetStatus(0);
				m_btnVTRSet.SetStatus(0);
				m_btnLogo.SetStatus(0);
				m_btnMeetTmp.SetStatus(0);
				m_btnUser.SetStatus(0);
				m_btnTvw.SetStatus(0);
				m_btnSysSet.SetStatus(0);

				HWND hWnd = ::GetFocus();
				if ( hWnd == m_btnVTRSet.GetSafeHwnd() || hWnd == m_btnLogo.GetSafeHwnd()
					|| hWnd == m_btnAddrEdit.GetSafeHwnd() || hWnd == m_btnMeetTmp.GetSafeHwnd()
					|| hWnd == m_btnUser.GetSafeHwnd() || hWnd == m_btnTvw.GetSafeHwnd()
					|| hWnd == m_btnSysSet.GetSafeHwnd() )
				{
					::SetFocus(NULL);
				}
				
				break;
			}
		case em_WND_TVW:
			{
				m_btnAddrEdit.SetStatus(0);
				m_btnVTRSet.SetStatus(0);
				m_btnLogo.SetStatus(0);
				m_btnMeetTmp.SetStatus(0);
				m_btnMeetInfo.SetStatus(0);
				m_btnUser.SetStatus(0);
				m_btnSysSet.SetStatus(0);

				HWND hWnd = ::GetFocus();
				if ( hWnd == m_btnVTRSet.GetSafeHwnd() || hWnd == m_btnLogo.GetSafeHwnd()
					|| hWnd == m_btnAddrEdit.GetSafeHwnd() || hWnd == m_btnMeetTmp.GetSafeHwnd()
					|| hWnd == m_btnUser.GetSafeHwnd() || hWnd == m_btnMeetInfo.GetSafeHwnd()
					|| hWnd == m_btnSysSet.GetSafeHwnd() )
				{
					::SetFocus(NULL);
				}

				break;
			}
		case em_WND_SYSTEMSET:
			{
				m_btnAddrEdit.SetStatus(0);
				m_btnVTRSet.SetStatus(0);
				m_btnLogo.SetStatus(0);
				m_btnMeetTmp.SetStatus(0);
				m_btnMeetInfo.SetStatus(0);
				m_btnUser.SetStatus(0);
				m_btnTvw.SetStatus(0);

				HWND hWnd = ::GetFocus();
				if ( hWnd == m_btnVTRSet.GetSafeHwnd() || hWnd == m_btnLogo.GetSafeHwnd()
					|| hWnd == m_btnAddrEdit.GetSafeHwnd() || hWnd == m_btnMeetTmp.GetSafeHwnd()
					|| hWnd == m_btnUser.GetSafeHwnd() || hWnd == m_btnMeetInfo.GetSafeHwnd()
					|| hWnd == m_btnTvw.GetSafeHwnd() )
				{
					::SetFocus(NULL);
				}
				
				break;
			}
		case em_WND_USER:
			{
				m_btnAddrEdit.SetStatus(0);
				m_btnVTRSet.SetStatus(0);
				m_btnLogo.SetStatus(0);
				m_btnMeetTmp.SetStatus(0);
				m_btnMeetInfo.SetStatus(0);
				m_btnTvw.SetStatus(0);
				m_btnSysSet.SetStatus(0);

				HWND hWnd = ::GetFocus();
				if ( hWnd == m_btnVTRSet.GetSafeHwnd() || hWnd == m_btnLogo.GetSafeHwnd()
					|| hWnd == m_btnAddrEdit.GetSafeHwnd() || hWnd == m_btnMeetTmp.GetSafeHwnd()
					|| hWnd == m_btnSysSet.GetSafeHwnd() || hWnd == m_btnMeetInfo.GetSafeHwnd()
					|| hWnd == m_btnTvw.GetSafeHwnd() )
				{
					::SetFocus(NULL);
				}
				
				break;
			}
		case em_WND_VTR:
			{
				m_btnAddrEdit.SetStatus(0);
				m_btnLogo.SetStatus(0);
				m_btnMeetTmp.SetStatus(0);
				m_btnMeetInfo.SetStatus(0);
				m_btnUser.SetStatus(0);
				m_btnTvw.SetStatus(0);
				m_btnSysSet.SetStatus(0);

				HWND hWnd = ::GetFocus();
				if ( hWnd == m_btnUser.GetSafeHwnd() || hWnd == m_btnLogo.GetSafeHwnd()
					|| hWnd == m_btnAddrEdit.GetSafeHwnd() || hWnd == m_btnMeetTmp.GetSafeHwnd()
					|| hWnd == m_btnSysSet.GetSafeHwnd() || hWnd == m_btnMeetInfo.GetSafeHwnd()
					|| hWnd == m_btnTvw.GetSafeHwnd() )
				{
					::SetFocus(NULL);
				}
				
				break;
			}
		case em_WND_PAGECLEAN:
			{
				m_btnAddrEdit.SetStatus(0);
				m_btnVTRSet.SetStatus(0);
				m_btnMeetTmp.SetStatus(0);
				m_btnMeetInfo.SetStatus(0);
				m_btnUser.SetStatus(0);
				m_btnTvw.SetStatus(0);
				m_btnSysSet.SetStatus(0);

				HWND hWnd = ::GetFocus();
				if ( hWnd == m_btnUser.GetSafeHwnd() || hWnd == m_btnVTRSet.GetSafeHwnd()
					|| hWnd == m_btnAddrEdit.GetSafeHwnd() || hWnd == m_btnMeetTmp.GetSafeHwnd()
					|| hWnd == m_btnSysSet.GetSafeHwnd() || hWnd == m_btnMeetInfo.GetSafeHwnd()
					|| hWnd == m_btnTvw.GetSafeHwnd() )
				{
					::SetFocus(NULL);
				}
				
				break;
			}
		}
		this->RedrawWindow();
	}


	CDlgChild::OnTimer(nIDEvent);
}

void CMainLogic::InitDlg()
{
	if ( g_pMainDlg != NULL )
	{ 
		//m_dlgLocalAddr.InitDlg(); 
		//m_dlgGlobalAddrbook.InitDlg(); 
		m_dlgMeetTmp.InitDlg();  
		m_dlgMeetInfo.InitDlg(); 
		m_dlgSysSet.InitDlg(); 
		m_dlgUser.InitDlg();
		m_dlgTvw.InitDlg();
		m_dlgVTR.InitDlg();
		m_dlgAddrEdit.InitDlg();
	}

	if ( NULL != m_cwndCurrent )
	{
		m_cwndCurrent->ShowWindow(FALSE);
		m_cwndCurrent = NULL;
	}
	
	m_gIconShining = FALSE; 
}

void CMainLogic::RevertTabPage()
{
	CTransparentDlgWarning::GetDlgPtr()->InitDlg();  
	OnBtnLogo();  
	m_emWndType = em_WND_PAGECLEAN;
	m_cwndCurrent = NULL; 
	
	m_btnLogo.SetCheck(BST_CHECKED);
	m_btnLocalAddr.SetCheck( BST_UNCHECKED);
	m_btnPublicAddr.SetCheck( BST_UNCHECKED);
	m_btnMeetTmp.SetCheck( BST_UNCHECKED);
	m_btnMeetInfo.SetCheck( BST_UNCHECKED);
	m_btnSysSet.SetCheck( BST_UNCHECKED);
	m_btnUser.SetCheck( BST_UNCHECKED);
	m_btnTvw.SetCheck( BST_UNCHECKED );
	m_btnVTRSet.SetCheck( BST_UNCHECKED);
	m_btnAddrEdit.SetCheck( BST_UNCHECKED);
}

LRESULT CMainLogic::OnLoginResult(WPARAM wParam, LPARAM lParam)
{
	CMsgHandle::SendMessage( UI_UMS_CONNECTED, wParam, lParam );

	return 0L;
}


void CMainLogic::OnBtnVTRSet() 
{
	m_btnVTRSet.SetCheck( BST_CHECKED );
	ShowActiveWindow(em_WND_VTR);
}

void CMainLogic::OnBtnADDREDIT() 
{
	m_btnAddrEdit.SetCheck( BST_CHECKED );
	ShowActiveWindow(em_WND_ADDREDIT);
}
