// SystemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "systemmanageLogic.h"
#include "mainLogic.h"
#include "usermanageLogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMainLogic* g_cmainWnd;

extern float CUR_SCREEN_WIDTH_PER;  //屏幕宽度比率
extern float CUR_SCREEN_HEIGHT_PER; //屏幕高度比率

/////////////////////////////////////////////////////////////////////////////
// CSystemManageLogic dialog
CSystemManageLogic::CSystemManageLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CSystemManageLogic::IDD, pParent),
	m_pUmsConfig(NULL)
{
	//{{AFX_DATA_INIT(CSystemManageLogic)
	//}}AFX_DATA_INIT

	m_currentCwd = NULL;
    m_bGkSwitchStatus = FALSE;

	m_bShowMosaicHoriImg = TRUE;
	m_bIsSegment = TRUE;
	m_nSegmentLen = 532*CUR_SCREEN_WIDTH_PER;
}

void CSystemManageLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSystemManageLogic)
	DDX_Control(pDX, IDC_BUTTON_TIMESYNC, m_btnTimeSync);
	DDX_Control(pDX, IDC_STATIC_CHILDFRMRIGHT, m_stChildBkRight);
	DDX_Control(pDX, IDC_STATIC_CHILDFRMLEFT, m_stChildBkLeft);
	DDX_Control(pDX, IDC_BTN_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_STATIC_CHILDWNDTITLE, m_stChildWndTitle);
	DDX_Control(pDX, IDC_STATIC_Title, m_stTitle);
	DDX_Control(pDX, IDC_Btn_Cancel, m_btnCancel);
	DDX_Control(pDX, IDC_Btn_Save, m_btnSave);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSystemManageLogic, CDlgChild)
	//{{AFX_MSG_MAP(CSystemManageLogic)
	ON_BN_CLICKED(IDC_Btn_Save, OnBtnSave)
	ON_BN_CLICKED(IDC_Btn_Cancel, OnBtnCancel)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_EDIT, OnBtnEdit)
	ON_BN_CLICKED(IDC_BUTTON_TIMESYNC, OnBtnTimeSync)
	ON_MESSAGE( UI_UMS_ETHNETINFO_NOTIFY,  OnEthnetNotify )
	ON_MESSAGE( UI_UMS_REG_INFO_NOTIFY,  OnRegSipNotify )
	ON_MESSAGE( UI_UMS_REG_SERV_RSP,  OnRegSipResult )
    ON_MESSAGE( UI_CNS_REG_GK_NTY,  OnRecGKNotify )
	ON_MESSAGE( UI_CNS_REG_GK_RSP,  OnRegGKResult )
	ON_MESSAGE(UI_CNS_REFRESH_GLOBAL_ADDRBOOK,OnRefreshGlobalAddrbook)
	ON_MESSAGE(UI_CNS_REFRESH_GLOBAL_ADDRBOOKEX,OnRefreshGlobalAddrbookEx)
	ON_MESSAGE( UI_GET_UMS_SYSTIME,  OnGetUmsSystimeTime )
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSystemManageLogic message handlers

void CSystemManageLogic::RegisterFun()
{
	REG_MSG_HANDLER( "CSystemManageLogic::OnClickLstItem", CSystemManageLogic::OnClickLstItem, this, CSystemManageLogic );	
}

BOOL CSystemManageLogic::InitControlPane()
{
	m_btnTimeSync.SetImage( IDR_PNG_BTN_TIMESYNC, IDR_PNG_BTN_TIMESYNCDOWN, IDR_PNG_BTN_TIMESYNC );
	m_btnSave.SetImage( IDR_PNG_BTN_SAVE, IDR_PNG_BTN_SAVEDOWN, IDR_PNG_BTN_SAVE );
	m_btnCancel.SetImage( IDR_PNG_BTN_CANCEL, IDR_PNG_BTN_CANCELDOWN, IDR_PNG_BTN_CANCEL );
	m_btnEdit.SetImage( IDR_PNG_BTN_EDITSYSWND, IDR_PNG_BTN_EDITSYSWND_DOWN, IDR_PNG_BTN_EDITSYSWND );

	m_stTitle.SetWindowText("系统设置");
	m_stTitle.SetTextAlign(StringAlignmentNear);
	m_stTitle.SetTextColor(Color( 24, 25, 27 ));
	m_stTitle.SetFont( 14, "微软雅黑" );

	m_stChildWndTitle.SetWindowText(SYSTEM_WND_MENU_UMSWEBCONFIG);
	m_stChildWndTitle.SetTextAlign(StringAlignmentNear);
	m_stChildWndTitle.SetTextColor(Color( 24, 25, 27 ));
	m_stChildWndTitle.SetFont( 14, "微软雅黑" );

	//菜单列表加入
	m_plsMenu = new CListChild( "", CRect(5, 46, 526+5, 488+46), this, "", 0, WS_CHILD );
	
	ARRAY<TMenuItemInfo> vecMenuLst;
	for ( s32 nIndex = em_WND_UMSNETCFG; nIndex <= em_WND_VTRCFG; nIndex++ )
	{
		TMenuItemInfo tMenuInfo;
		switch( nIndex )
		{
		case em_WND_UMSNETCFG:
			{
				tMenuInfo.strTxt = SYSTEM_WND_MENU_UMSWEBCONFIG;
			}
			break;
		case em_WND_SIPNETCFG:
			{
				tMenuInfo.strTxt = SYSTEM_WND_MENU_SIPCONFIG;		
			}
			break;
		case em_WND_GKSET:
			{
				tMenuInfo.strTxt = SYSTEM_WND_MENU_GKCONFIG;	
			}
			break;
		case em_WND_SYSTEMTIME:
			{
				tMenuInfo.strTxt = SYSTEM_WND_MENU_SYSTEMTIME;	
			}
			break;
		case em_WND_NMCFG:
			{
				tMenuInfo.strTxt = SYSTEM_WND_MENU_NMCFG;	
			}
			break;
		case em_WND_VTRCFG:
			{
				tMenuInfo.strTxt = SYSTEM_WND_MENU_VTRCFG;	
			}
			break;
		default:
			{

			}
			break;
		}
		tMenuInfo.strItemFunc = "CSystemManageLogic::OnClickLstItem";
		vecMenuLst.push_back(tMenuInfo);
	}

	if ( vecMenuLst.size() > 0 )
	{
		Value_TouchListMenu val_MenuList( &vecMenuLst );
        m_plsMenu->SetData( val_MenuList );	         		  
	}

	return TRUE;
}

void CSystemManageLogic::SetControlPos()
{
	CRect rectClient;
	this->GetClientRect(&rectClient);
	
	//m_stChildBkLeft.SetWindowPos( NULL, 0, 0, 532*CUR_SCREEN_WIDTH_PER, 558*CUR_SCREEN_HEIGHT_PER,  SWP_SHOWWINDOW );
	//m_stChildBkLeft.SetMosaicHoriImage( IDR_PNG_WNDCHILDLEFT, IDR_PNG_WNDCHILDRIGHT, IDR_PNG_WNDCHILDMID );
	
	//m_stChildBkRight.SetWindowPos( NULL, 526*CUR_SCREEN_WIDTH_PER, 0, (1226 - 527)*CUR_SCREEN_WIDTH_PER, 558*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	//m_stChildBkRight.SetMosaicHoriImage( IDR_PNG_WNDCHILDLEFT, IDR_PNG_WNDCHILDRIGHT, IDR_PNG_WNDCHILDMID );

	m_stTitle.SetWindowPos( NULL, 17*CUR_SCREEN_WIDTH_PER,  14*CUR_SCREEN_HEIGHT_PER, rectClient.Width(), 24, SWP_SHOWWINDOW );
	m_stChildWndTitle.SetWindowPos( NULL, (526 + 18)*CUR_SCREEN_WIDTH_PER, 14*CUR_SCREEN_HEIGHT_PER, rectClient.Width(), 24, SWP_SHOWWINDOW );

//     m_stChildBkRight.GetWindowRect(&rectClient);
 	ScreenToClient( &rectClient );
	m_btnCancel.SetWindowPos( NULL,  1226*CUR_SCREEN_WIDTH_PER - (8 + m_btnCancel.GetImageSize().cx)*CUR_SCREEN_WIDTH_PER, 3*CUR_SCREEN_HEIGHT_PER, m_btnCancel.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnSave.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnEdit.SetWindowPos( NULL,  1226*CUR_SCREEN_WIDTH_PER - (8 + m_btnEdit.GetImageSize().cx)*CUR_SCREEN_WIDTH_PER, 3*CUR_SCREEN_HEIGHT_PER, m_btnEdit.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnEdit.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_btnSave.SetWindowPos( NULL,  1226*CUR_SCREEN_WIDTH_PER - 2*(8 + m_btnSave.GetImageSize().cx)*CUR_SCREEN_WIDTH_PER, 3*CUR_SCREEN_HEIGHT_PER, m_btnSave.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnSave.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnTimeSync.SetWindowPos( NULL, 1226*CUR_SCREEN_WIDTH_PER - (8 +m_btnSave.GetImageSize().cx)*CUR_SCREEN_WIDTH_PER - (8 + m_btnTimeSync.GetImageSize().cx)*CUR_SCREEN_WIDTH_PER, 3*CUR_SCREEN_HEIGHT_PER, m_btnTimeSync.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnSave.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	if ( NULL != m_plsMenu )
	{
		m_plsMenu->SetWindowPos( NULL, 5*CUR_SCREEN_WIDTH_PER, 46*CUR_SCREEN_HEIGHT_PER, 526*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	}

}

BOOL CSystemManageLogic::InitChildWindow()
{
	try
	{
		m_networkdlg.Create( IDD_DIALOG_UMSNETWORKSET, this ); 		
		m_networkdlg.SetWindowPos( NULL, 526*CUR_SCREEN_WIDTH_PER, 50*CUR_SCREEN_HEIGHT_PER, (1226 - 527)*CUR_SCREEN_WIDTH_PER, 558*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW ); 
		
		m_serversetdlg.Create( IDD_DIALOG_SIPSERVERSET, this ); 
		m_serversetdlg.SetWindowPos( NULL, 526*CUR_SCREEN_WIDTH_PER, 50*CUR_SCREEN_HEIGHT_PER, (1226 - 527)*CUR_SCREEN_WIDTH_PER, 558*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW ); 
		
		m_SystemTime.Create( IDD_DIALOG_SYSTIMESET, this ); 
		m_SystemTime.SetWindowPos( NULL, 526*CUR_SCREEN_WIDTH_PER, 50*CUR_SCREEN_HEIGHT_PER, (1226 - 527)*CUR_SCREEN_WIDTH_PER, 558*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW ); 
		
		m_gkset.Create( IDD_DIALOG_GKSERVERSET, this ); 
		m_gkset.SetWindowPos( NULL, 526*CUR_SCREEN_WIDTH_PER, 50*CUR_SCREEN_HEIGHT_PER, (1226 - 527)*CUR_SCREEN_WIDTH_PER, 558*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW ); 

		m_cNMCfgLogic.Create( IDD_DIALOG_NMCFG, this ); 
		m_cNMCfgLogic.SetWindowPos( NULL, 526*CUR_SCREEN_WIDTH_PER, 50*CUR_SCREEN_HEIGHT_PER, (1226 - 527)*CUR_SCREEN_WIDTH_PER, 558*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW ); 
		
		m_cVTRCfgLogic.Create( IDD_DIALOG_VTRCFG, this ); 
		m_cVTRCfgLogic.SetWindowPos( NULL, 526*CUR_SCREEN_WIDTH_PER, 50*CUR_SCREEN_HEIGHT_PER, (1226 - 527)*CUR_SCREEN_WIDTH_PER, 558*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW ); 

		return TRUE;
	}
	catch (CException* e)
	{
		if ( e != NULL )
		{
			s8 chErr[1024];
			e->GetErrorMessage( chErr,1024 );
			CString strErr;
			strErr += "文件操作失败，错误码";
			strErr += chErr;
			MESSAGEWND( strErr );
		}

		return FALSE;
	}
}

BOOL CSystemManageLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();

	RegisterFun();
	if ( !InitControlPane() )
	{
		return FALSE;
	}
    m_plsMenu->SetSelItem( 0 );
    m_emCurrViewType = em_WND_UMSNETCFG; //set default 

	SetControlPos();

	if(InitChildWindow())
	{
		m_currentCwd = NULL;
 		ShowActiveWindow( em_WND_UMSNETCFG );

		if( m_pUmsConfig == NULL )
		{
			BUSINESSIFPTR->GetCtrlInterface(&m_pUmsConfig);
		}
		
		if( m_pUmsConfig != NULL )
		{
			m_pUmsConfig->SetNotifyWnd( this->m_hWnd );
		} 

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CSystemManageLogic::ShowActiveWindow(EM_CURRENT_WND_VIEW_TYPE emWndType)
{
	if ( emWndType != em_WND_SYSTEMTIME )
	{
        if( m_btnTimeSync.IsWindowVisible() )
        {
            m_btnTimeSync.ShowWindow( FALSE );
        }
	}
	else // configure time window
    {
        if ( m_btnEdit.IsWindowVisible() )
        {
            m_btnTimeSync.ShowWindow(TRUE);
		}
        else
        {
            m_btnTimeSync.ShowWindow( FALSE );

        }
    }
	
	BOOL bShowFlag = FALSE;
	CWnd* cwndCurrent = NULL;
	
	switch( emWndType )
	{
	case em_WND_UMSNETCFG:	
		{
			if( m_currentCwd != NULL )
			{
				bShowFlag = ( m_currentCwd->GetSafeHwnd() == m_networkdlg.GetSafeHwnd() )?FALSE:TRUE;
			}
			else
			{
				bShowFlag = TRUE;
			}
			cwndCurrent = &m_networkdlg;
			m_stChildWndTitle.SetWindowText(SYSTEM_WND_MENU_UMSWEBCONFIG);
		}
		break;
	case em_WND_SIPNETCFG:
		{
			if( m_currentCwd != NULL )
			{
				bShowFlag = ( m_currentCwd->GetSafeHwnd() == m_serversetdlg.GetSafeHwnd() )?FALSE:TRUE;
			}
			else
			{
				bShowFlag = TRUE;
			}
			cwndCurrent = &m_serversetdlg;
			m_stChildWndTitle.SetWindowText(SYSTEM_WND_MENU_SIPCONFIG);
		}
		break;
	case em_WND_SYSTEMTIME:
		{
			if( m_currentCwd != NULL )
			{
				bShowFlag = ( m_currentCwd->GetSafeHwnd() == m_SystemTime.GetSafeHwnd() )?FALSE:TRUE;
			}
			else
			{
				bShowFlag = TRUE;
			}
			cwndCurrent = &m_SystemTime;
			m_stChildWndTitle.SetWindowText(SYSTEM_WND_MENU_SYSTEMTIME);
		}
		break;
	case em_WND_GKSET:
		{
			if( m_currentCwd != NULL )
			{
				bShowFlag = m_currentCwd->GetSafeHwnd() == m_gkset.GetSafeHwnd()?FALSE:TRUE;
			}
			else
			{
				bShowFlag = TRUE;
			}
			cwndCurrent = &m_gkset;
			m_stChildWndTitle.SetWindowText(SYSTEM_WND_MENU_GKCONFIG);
		}
		break;
	case em_WND_NMCFG:
		{
			if( m_currentCwd != NULL )
			{
				bShowFlag = m_currentCwd->GetSafeHwnd() == m_cNMCfgLogic.GetSafeHwnd()?FALSE:TRUE;
			}
			else
			{
				bShowFlag = TRUE;
			}
			cwndCurrent = &m_cNMCfgLogic;
			m_stChildWndTitle.SetWindowText(SYSTEM_WND_MENU_NMCFG);
		}
		break;
	case em_WND_VTRCFG:
		{
			if( m_currentCwd != NULL )
			{
				bShowFlag = m_currentCwd->GetSafeHwnd() == m_cVTRCfgLogic.GetSafeHwnd()?FALSE:TRUE;
			}
			else
			{
				bShowFlag = TRUE;
			}
			cwndCurrent = &m_cVTRCfgLogic;
			m_stChildWndTitle.SetWindowText(SYSTEM_WND_MENU_VTRCFG);
		}
		break;
	default:
		break;
	}
	
	if( bShowFlag )
	{
		if( m_currentCwd != NULL )
		{
			m_currentCwd->ShowWindow(FALSE); //hide the previous window 
		}
		
		if( cwndCurrent != NULL )
		{
			cwndCurrent->ShowWindow(SW_SHOW);  //show the current window 
			m_currentCwd = cwndCurrent;
		}
	}
}

//left item is clicked
bool CSystemManageLogic::OnClickLstItem( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( const Data_Menu *pItemInfo = dynamic_cast<const Data_Menu*>( pBaseItem->GetUserData() )) 
        { 
			TMenuItemInfo tMenuInfo = pItemInfo->m_tMenuInfo;
			if ( tMenuInfo.strTxt == SYSTEM_WND_MENU_UMSWEBCONFIG )
			{  
                if ( m_networkdlg.m_bIsEdit == FALSE )
                {
                    SetEditControl( FALSE );                    
                }
                else 
                {
                    SetEditControl( TRUE );
                }
                m_emCurrViewType = em_WND_UMSNETCFG;
				m_stChildWndTitle.SetWindowText(SYSTEM_WND_MENU_UMSWEBCONFIG);
				ShowActiveWindow(em_WND_UMSNETCFG);
			}
			if ( tMenuInfo.strTxt == SYSTEM_WND_MENU_SIPCONFIG )
			{
                if ( m_serversetdlg.m_bIsEdit == FALSE )
                {
                    SetEditControl( FALSE );                    

                }
                else
                {
                    SetEditControl( TRUE );
                }
                m_emCurrViewType = em_WND_SIPNETCFG;

				m_stChildWndTitle.SetWindowText(SYSTEM_WND_MENU_SIPCONFIG);	
				ShowActiveWindow(em_WND_SIPNETCFG);
			}
			if ( tMenuInfo.strTxt == SYSTEM_WND_MENU_SYSTEMTIME )
			{
                if ( m_SystemTime.m_bIsEdit == FALSE )
                {
                    SetEditControl( FALSE );                  

                }
                else
                {
                    SetEditControl( TRUE );
                }
                m_emCurrViewType = em_WND_SYSTEMTIME;

				m_stChildWndTitle.SetWindowText(SYSTEM_WND_MENU_SYSTEMTIME);
				ShowActiveWindow(em_WND_SYSTEMTIME);
			}
			if ( tMenuInfo.strTxt == SYSTEM_WND_MENU_GKCONFIG )
			{
                if ( m_gkset.m_bIsEdit == FALSE )
                {
                    SetEditControl( FALSE );          

                }
                else
                {
                    SetEditControl( TRUE );
                }
                m_emCurrViewType = em_WND_GKSET;

				m_stChildWndTitle.SetWindowText(SYSTEM_WND_MENU_GKCONFIG);
				ShowActiveWindow(em_WND_GKSET);
			}
			if ( tMenuInfo.strTxt == SYSTEM_WND_MENU_NMCFG )
			{
                if ( m_cNMCfgLogic.m_bIsEdit == FALSE )
                {
                    SetEditControl( FALSE );          
                }
                else
                {
                    SetEditControl( TRUE );
                }
                m_emCurrViewType = em_WND_NMCFG;
				
				m_stChildWndTitle.SetWindowText(SYSTEM_WND_MENU_NMCFG);
				ShowActiveWindow(em_WND_NMCFG);
			}
			if ( tMenuInfo.strTxt == SYSTEM_WND_MENU_VTRCFG )
			{
                if ( m_cVTRCfgLogic.m_bIsEdit == FALSE )
                {
                    SetEditControl( FALSE );          
                }
                else
                {
                    SetEditControl( TRUE );
                }
                m_emCurrViewType = em_WND_VTRCFG;
				
				m_stChildWndTitle.SetWindowText(SYSTEM_WND_MENU_VTRCFG);
				ShowActiveWindow(em_WND_VTRCFG);
			}
		}
    }
	
	return true;
}

void CSystemManageLogic::OnBtnEdit() 
{
    bool bIsStarted = g_cmainWnd->m_dlgMeetInfo.GetConfExist();
    if ( bIsStarted == TRUE && m_emCurrViewType != em_WND_SYSTEMTIME )
    {
        s32 nRet = 0;
        CString strInfo;
        switch ( m_emCurrViewType )
        {
        case em_WND_UMSNETCFG:
			{
				strInfo = "会议中,不能修改网络配置";
			}    
            break;
        case em_WND_SIPNETCFG:
			{
			    strInfo = "会议中，不能修改注册服务器地址";
			}
            break;

        case em_WND_GKSET:
			{
				strInfo = "会议中，不能修改GK地址";
			}
			break;
		case em_WND_NMCFG:
			{
				strInfo = "会议中，不能修改网管配置";
			}
			break;
		case em_WND_VTRCFG:
			{
				strInfo = "会议中，不能修改录像机配置";
			}
			break;
        }
        
        MESSAGEWNDBOX( strInfo, this , nRet , FALSE );

        return;
    }
    SetEditControl( TRUE );  //show save, cancel & hide Edit 

    if( m_btnTimeSync.IsWindowVisible() )
    {
        m_btnTimeSync.ShowWindow( FALSE );
    }
    if ( m_emCurrViewType == em_WND_SYSTEMTIME )
    { 
        m_SystemTime.m_bIsEdit = TRUE;
        m_SystemTime.SetTimeControl(TRUE);  //show btn & stop timer
	    
    }
    else if ( m_emCurrViewType == em_WND_UMSNETCFG )
    {
        m_networkdlg.m_bIsEdit = TRUE;
        SetNetCfgControl( TRUE );        
    }
    else if ( m_emCurrViewType == em_WND_SIPNETCFG )
    {
        m_serversetdlg.m_bIsEdit = TRUE;
        m_serversetdlg.m_Ip.EnableWindow( TRUE );
    }
    else if ( m_emCurrViewType == em_WND_GKSET )
    {
        m_gkset.m_bIsEdit = TRUE;
        
        SetGKControl( TRUE );
    }
	else if ( m_emCurrViewType == em_WND_NMCFG )
    {
        m_cNMCfgLogic.m_bIsEdit = TRUE;
        
        m_cNMCfgLogic.SetEditState( TRUE );
    }
	else if ( m_emCurrViewType == em_WND_VTRCFG )
    {
        m_cVTRCfgLogic.m_bIsEdit = TRUE;
        
        m_cVTRCfgLogic.SetEditState( TRUE );
    }
}

void CSystemManageLogic::OnBtnCancel() 
{
    SetEditControl( FALSE );

    if ( m_emCurrViewType == em_WND_SYSTEMTIME )
    {
        m_SystemTime.m_bIsEdit = FALSE;

        m_SystemTime.SetTimeControl(FALSE);   //hide btn & start timer
        if( m_currentCwd->GetSafeHwnd()  ==  m_SystemTime.GetSafeHwnd()?TRUE:FALSE )
        {
            m_btnTimeSync.ShowWindow(TRUE);
	    }

    }
	else if ( m_emCurrViewType == em_WND_UMSNETCFG )
	{
        m_networkdlg.m_bIsEdit = FALSE;

        SetNetCfgControl( FALSE );
        RevertNetConfig();
	}
    else if ( m_emCurrViewType == em_WND_SIPNETCFG )
    {
        m_serversetdlg.m_bIsEdit = FALSE;

        m_serversetdlg.m_Ip.EnableWindow( FALSE );
        OnRegSipNotify( 0, 0 );
    }
	else if ( m_emCurrViewType == em_WND_GKSET )
	{
        m_gkset.m_bIsEdit = FALSE;
        SetGKControl(FALSE);
	} 
	else if ( m_emCurrViewType == em_WND_NMCFG )
	{
        m_cNMCfgLogic.m_bIsEdit = FALSE;
        m_cNMCfgLogic.SetEditState(FALSE);
		m_cNMCfgLogic.FreshNMInfo();
	} 
	else if ( m_emCurrViewType == em_WND_VTRCFG )
	{
        m_cVTRCfgLogic.m_bIsEdit = FALSE;
        m_cVTRCfgLogic.SetEditState(FALSE);
		m_cVTRCfgLogic.FreshNMInfo();
	} 
}

BOOL CSystemManageLogic::SaveEthnetCfg()
{
	DWORD dwIp = 0;
	m_networkdlg.m_Ip.GetAddress(dwIp);

	CString strIp;
	m_networkdlg.m_Ip.GetWindowText(strIp);

	CString strError;
	int nRet = 0;
	if( strIp.GetLength() == 0 )
	{
		strError = "IP地址不能为空";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return FALSE;
	}

	if ( !CCallAddr::IsValidCallIP( dwIp, strError, 0 ) ) 
	{
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		
		return FALSE;
    }

	DWORD dwIpSub = 0;
	m_networkdlg.m_Ip_Sub.GetAddress(dwIpSub);

	CString strIpSub;
	m_networkdlg.m_Ip_Sub.GetWindowText(strIpSub);
	if( strIpSub.GetLength() == 0 )
	{
		strError = "子网掩码不能为空";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return FALSE;
	}

	if( !CCallAddr::IsValidIpMask(dwIpSub) )
	{
		strError = "子网掩码无效，子网掩码必须是相邻的，请输入有效的掩码";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return FALSE;
	}

	if ( !CCallAddr::IsValidDevIP( dwIp, dwIpSub, strError, 0 ) )
	{
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return FALSE;
	}

	DWORD dwIpGatWay = 0;
	m_networkdlg.m_Ip_GetWay.GetAddress(dwIpGatWay);

	CString strIpGatWay;
	m_networkdlg.m_Ip_GetWay.GetWindowText(strIpGatWay);

	if ( !strIpGatWay.IsEmpty() && !CCallAddr::IsValidIpV4( dwIpGatWay ) )
	{
		strError = "网关IP地址非法";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );		
		return FALSE;
	}

	if ( !strIpGatWay.IsEmpty() )
    {
        DWORD dwNetID = dwIp & dwIpSub;
        DWORD dwNetGate = dwIpGatWay & dwIpSub;
        if ( dwNetGate != dwNetID )
        {
			strError = "网关不在由IP地址和子网掩码定义的同一网络段上，是否保存此配置?";
			MESSAGEWNDBOX( strError, this , nRet , TRUE );	
			if ( IDCANCEL == nRet )
			{
				return FALSE;
			}
        }
	}

	TTPEthnetInfo tTypethnetInfo;
	tTypethnetInfo.bEnable = TRUE;
	tTypethnetInfo.dwIP = htonl(dwIp);
	tTypethnetInfo.dwMask = htonl(dwIpSub);
	tTypethnetInfo.dwGateWay = htonl(dwIpGatWay);
	
	BUSINESSIFPTR->GetCtrlInterface(&m_pUmsConfig);
 
	if( m_pUmsConfig != NULL )
	{
        TTPEthnetInfo tEthnet;
	    m_pUmsConfig->GetEthnetCfg(tEthnet);
        
        if ( tTypethnetInfo.dwIP == tEthnet.dwIP 
            && tTypethnetInfo.dwMask == tEthnet.dwMask 
            && tTypethnetInfo.dwGateWay == tEthnet.dwGateWay )
        {
            return TRUE;
        }

		s32 nRet = 0;
		MESSAGEWNDBOX( "修改网络配置后服务器将立即重启，请确认后点击确定?", this , nRet , TRUE );
		if( nRet == IDOK )
		{
			m_networkdlg.m_Ip.SetAddress(dwIp);
			m_networkdlg.m_Ip_Sub.SetAddress(dwIpSub);
			m_networkdlg.m_Ip_GetWay.SetAddress(dwIpGatWay);
			UpdateData(FALSE);

			m_pUmsConfig->UpdateEthnetCfg(tTypethnetInfo);
		}
		else
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CSystemManageLogic::SaveRegServer()
{
	DWORD dwIpServer = 0;
	m_serversetdlg.m_Ip.GetAddress(dwIpServer);

	CString strIp;
	m_serversetdlg.m_Ip.GetWindowText(strIp);

	CString strError;
	int nRet = 0;
	if( strIp.GetLength() == 0 )
	{
// 		strError = "IP地址不能为空";
// 		MESSAGEWNDBOX( strError, this , nRet , FALSE );
// 		return FALSE;
	}
	else if( !CCallAddr::IsValidIpV4(dwIpServer)  )
	{
		strError = "IP地址非法";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return FALSE;
	}

	if( htonl(dwIpServer) == m_dwIpRegServer ) 
	{
		return TRUE;
	}

	m_serversetdlg.m_Ip.SetAddress(dwIpServer);

	TTPSipRegistrarCfg tSip;
	tSip.bUsed = TRUE;
	tSip.dwRegIP = htonl(dwIpServer);
	tSip.wRegPort = 5060;
	tSip.wExpire = 30;
	
	BUSINESSIFPTR->GetCtrlInterface(&m_pUmsConfig);
	u32 nResult = m_pUmsConfig->RegSipService(tSip);
	if ( nResult != NO_ERROR )
	{
		MESSAGEWND( "注册服务器请求发送失败" );
		
		return FALSE;
	}

	return TRUE;
}

BOOL CSystemManageLogic::SaveGkInfo()
{
	DWORD dwIpGk = 0;
	m_gkset.m_Ip.GetAddress(dwIpGk);

    CString strIp;
	m_gkset.m_Ip.GetWindowText(strIp);

	CString strError;
	int nRet = 0;
	//120806--ldy OFF状体GK为空的不做判断  ON状态判空
	if ( m_gkset.m_bSwitchStatus )
	{
		//131105---sc GK地址可以为空
//		if( strIp.GetLength() == 0 )
//		{
// 			strError = "IP地址不能为空";
// 			MESSAGEWNDBOX( strError, this , nRet , FALSE );
//			return TRUE;
//		}
		if( !CCallAddr::IsValidIpV4(dwIpGk) && strIp.GetLength() != 0 )
		{
			strError = "IP地址非法";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			return FALSE;
		}
	}
	else
	{
		if( (strIp.GetLength() != 0 )&&!CCallAddr::IsValidIpV4(dwIpGk))
		{
			strError = "IP地址非法";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			return FALSE;
		}
	}
    
    if( htonl(dwIpGk) == m_dwIpGKServer && m_gkset.m_bSwitchStatus == m_bGkSwitchStatus ) 
    {
        return TRUE;
	}

	TTPGKCfg tGKCfg;
	tGKCfg.bUsed = m_gkset.m_bSwitchStatus;
	tGKCfg.dwGKIP = htonl(dwIpGk);
	tGKCfg.wExpire = 30;
	BUSINESSIFPTR->GetCtrlInterface(&m_pUmsConfig);
	
	if ( NULL != m_pUmsConfig )
	{
		m_pUmsConfig->GkRegReq(tGKCfg);
	}
    m_dwIpGKServer = dwIpGk;
    m_bGkSwitchStatus = m_gkset.GetGKSwitchStatus();

	return TRUE;
}

void CSystemManageLogic::OnBtnSave() 
{
    bool bIsStarted = g_cmainWnd->m_dlgMeetInfo.GetConfExist();	
    if ( bIsStarted == TRUE && m_emCurrViewType != em_WND_SYSTEMTIME )
    {
        s32 nRet = 0;
        CString strInfo;
        switch ( m_emCurrViewType )
        {
        case em_WND_UMSNETCFG:
            strInfo = "会议中,无法保存网络配置";
            break;
            
        case em_WND_SIPNETCFG:
            strInfo = "会议中,无法保存网呈服务器地址";
            break;
            
        case em_WND_GKSET:
            strInfo = "会议中,无法保存GK地址";
            break;
		case em_WND_SYSTEMSET:
            strInfo = "会议中,无法保存系统时间";
            break;
		case em_WND_NMCFG:
            strInfo = "会议中,无法保存网管服务器";
            break;
		case em_WND_VTRCFG:
            strInfo = "会议中,无法保存录像机配置";
            break;
        }
        
        MESSAGEWNDBOX( strInfo, this , nRet , FALSE );
        return;
    }


	BOOL bSaveSuccessFlag = FALSE;  //保存成功则关闭所有控件未Disable状态
	if( m_emCurrViewType == em_WND_UMSNETCFG )
	{
		if ( bSaveSuccessFlag = SaveEthnetCfg() )
		{
			m_networkdlg.m_bIsEdit = FALSE;
		}
		else
		{
			m_networkdlg.m_bIsEdit = TRUE;
		}

		//120803--ldy 加入修改IP保存Edit框即时生效
 		if ( bSaveSuccessFlag )
 		{
 			SetNetCfgControl( FALSE );
 			m_btnSave.ShowWindow( FALSE );
 			m_btnCancel.ShowWindow( FALSE);
 			m_btnEdit.ShowWindow( TRUE );
 			return;
 		}
	}
	else if( m_emCurrViewType == em_WND_SIPNETCFG )
	{
		if ( bSaveSuccessFlag = SaveRegServer() )
		{
			m_serversetdlg.m_bIsEdit = FALSE;
		}
		else
		{
			m_serversetdlg.m_bIsEdit = TRUE;
		}
		
		if ( bSaveSuccessFlag )
		{
			SetEditControl( FALSE );
			m_serversetdlg.m_bIsEdit = FALSE;
			m_serversetdlg.m_Ip.EnableWindow( FALSE );
			return;
		}
	}
	else if( m_emCurrViewType == em_WND_SYSTEMTIME )
	{
		if ( bSaveSuccessFlag = m_SystemTime.SaveSysTime() )
		{
			m_SystemTime.m_bIsEdit = FALSE;
		}
		else
		{
			m_SystemTime.m_bIsEdit = TRUE;
		}
	}
	else if( m_emCurrViewType == em_WND_GKSET )
	{	
		if ( bSaveSuccessFlag = SaveGkInfo() )
		{
			m_gkset.m_bIsEdit = FALSE;
		}
		else
		{
			m_gkset.m_bIsEdit = TRUE;
		}
	}
	else if( m_emCurrViewType == em_WND_NMCFG )
	{	
		if ( bSaveSuccessFlag = m_cNMCfgLogic.SaveNMCfg() )
		{
			m_cNMCfgLogic.m_bIsEdit = FALSE;
		}
		else
		{
			m_cNMCfgLogic.m_bIsEdit = TRUE;
		}
	}
	else if( m_emCurrViewType == em_WND_VTRCFG )
	{	
		if ( bSaveSuccessFlag = m_cVTRCfgLogic.SaveVTRCfg() )
		{
			m_cVTRCfgLogic.m_bIsEdit = FALSE;
		}
		else
		{
			m_cVTRCfgLogic.m_bIsEdit = TRUE;
		}
	}

	if( bSaveSuccessFlag )
	{
		OnBtnCancel();     //保存后关闭控件 
	}
}

//get original UMS NetCfg from lib
void CSystemManageLogic::RevertNetConfig()
{
	OnEthnetNotify( 0, 0 );
}

LRESULT CSystemManageLogic::OnEthnetNotify(WPARAM wParam, LPARAM lParam)
{
	TTPEthnetInfo tEthnet;
	m_pUmsConfig->GetEthnetCfg(tEthnet);
	m_networkdlg.m_Ip.SetAddress(htonl(tEthnet.dwIP));
	m_networkdlg.m_Ip_Sub.SetAddress(htonl(tEthnet.dwMask));
	m_networkdlg.m_Ip_GetWay.SetAddress(htonl(tEthnet.dwGateWay));
	
	return 0L;
}

LRESULT CSystemManageLogic::OnRegSipNotify(WPARAM wParam, LPARAM lParam)
{
	TTPSipRegistrarCfg tSipCfg;
	if ( m_pUmsConfig != NULL )
	{
		m_pUmsConfig->GetSipCfg(tSipCfg);
		m_dwIpRegServer = tSipCfg.dwRegIP;
		m_serversetdlg.m_Ip.SetAddress(htonl(tSipCfg.dwRegIP));
	}

	return 0L;
}

LRESULT CSystemManageLogic::OnRegSipResult(WPARAM wParam, LPARAM lParam)
{
	{
		TUCSipRegResult tRegResult = *reinterpret_cast<TUCSipRegResult*>(wParam);
		EmTpCnsRegUms tRegUms = (EmTpCnsRegUms)tRegResult.m_emTpCnsRegUms;
		CString strErr;
		switch( tRegUms )
		{
		case tp_CnsRegRet_Unknow:
			{
				strErr = "未知的网呈服务器";
			}
			break;
		case tp_CnsRegRet_Success:
			{
				strErr = "注册网呈服务器成功";
				MESSAGEWND( strErr );

				return 0L;
			}
			break;
		case tp_CnsRegRet_MaxRegNum:
			{
				strErr = "注册个数已达到最大值";
			}
			break;
		case tp_CnsRegRet_MaxAliasNum:
			{
				strErr = "注册别名的个数已达到最大值";
			}
			break;
		case tp_CnsRegRet_MsgError:
			{
				strErr = "注册消息错误";
			}
			break;
		case tp_CnsRegRet_AliasRepeat:
			{
				if ( tRegResult.m_nAliasNum == 0 )
				{
					strErr = "网呈服务器注册别名重复";
					MESSAGEWND( strErr );
					return 0L;
				}

				for ( s32 nIndex = 0; nIndex < tRegResult.m_nAliasNum; nIndex++ )
				{
					strErr = "注册 ";
					strErr += tRegResult.m_atTPAlias[nIndex].m_abyAlias;
					strErr += " 别名重复";
					MESSAGEWND( strErr );
				}

				return 0L;
			}
			break;
		case tp_CnsRegRet_UnReg:
			{
				strErr = "未找到删除记录";
			}
			break;
		case tp_CnsRegRet_SysError:
			{
				strErr = "APP错误";
			}
			break;
		case tp_CnsRegRet_NotFind:
			{
				strErr = "查找失败";
			}
			break;
		case tp_CnsRegRet_Fail:
			{
				strErr = "";
			}
			break;
		case tp_CnsRegRet_Unreachable:
			{
				strErr = "服务器不可达";
			}
			break;
		default:
			{
				strErr = ""; //"未知错误";	2012-8-7 SE石文娟确认未知错误不做提示 by yjj  
			}
			break;
		}
		
		if ( !strErr.IsEmpty() )
		{
			CString strTemp = "注册网呈服务器失败";
			if ( !strErr.IsEmpty() )
			{
				strTemp  = strTemp + ": " + strErr;
			}
		 
			MESSAGEWND( strTemp );
		}
		else
		{
			MESSAGEWND( "注册网呈服务器失败" );
		}
	}

	return 0L;
}

LRESULT CSystemManageLogic::OnRecGKNotify(WPARAM wParam, LPARAM lParam)
{
    TTPGKCfg* tGKRegCfg = (TTPGKCfg*) wParam;
    m_gkset.m_Ip.SetAddress( ntohl(tGKRegCfg->dwGKIP) );
    m_gkset.m_btnSwitch.SetSwitchState( tGKRegCfg->bUsed );
	m_gkset.m_bSwitchStatus = tGKRegCfg->bUsed;

    return 0L;
}

LRESULT CSystemManageLogic::OnRegGKResult(WPARAM wParam, LPARAM lParam)
{
    bool bOk = false;
    EmTpCnsRegUms emRe = (EmTpCnsRegUms)wParam;
    
    CString strTemp = "";
    switch( wParam )
    {
        
    case tp_CnsRegRet_Success:		    //成功
        bOk  = true;
        break;
    case tp_CnsRegRet_MaxRegNum:		//注册满
        strTemp = "注册个数以达到最大值";
        break;
    case tp_CnsRegRet_MaxAliasNum:	    //注册满
        strTemp = "注册别名的个数以达到最大值";
        break;
    case tp_CnsRegRet_MsgError:	    	//注册消息错误
        strTemp = "注册消息错误";
        break;
    case tp_CnsRegRet_AliasRepeat:	    //别名重复
        strTemp = "注册别名重复";
        break;
    case tp_CnsRegRet_UnReg:			//删除时，未找到删除记录
        strTemp = "未找到该记录";
        break;
    case tp_CnsRegRet_SysError:		    //APP错误
        strTemp = "APP错误";
        break;
    case tp_CnsRegRet_NotFind:		    //查找失败
        strTemp = "查找失败";
        break;   
    case tp_CnsRegRet_Unreachable:      //服务器不可达
        strTemp = "服务器不可达";
        break;
    default:
        strTemp = "" ;                  //"未知错误";2012-8-7 SE石文娟确认未知错误不做提示 by yjj
        break;
    }
    
    CString strName = "注册GK失败";
    
    if ( bOk )
    {
        MESSAGEWND( "注册GK成功" );
    }
    else
    {   
		if ( !strTemp.IsEmpty() )
		{
			strName = strName + ": " + strTemp;
		}
		 
        MESSAGEWND( strName   );
	}

	return 0L;
}

void CSystemManageLogic::SetGKControl(BOOL bEnable) 
{	
	m_gkset.m_btnSwitch.EnableWindow(bEnable);

    if ( bEnable )  //true to Edit, backup Info
    {
        m_gkset.m_Ip.GetAddress( m_dwIpGKServer );
        m_bGkSwitchStatus = m_gkset.GetGKSwitchStatus();  
        if ( m_bGkSwitchStatus )
        {
            m_gkset.m_Ip.EnableWindow(TRUE);
        }
        
    }
	else //false to restore the IP or update the IP
    {
        m_gkset.m_Ip.SetAddress( m_dwIpGKServer );
        m_gkset.m_btnSwitch.SetSwitchState( m_bGkSwitchStatus );  //?
        m_gkset.m_Ip.EnableWindow(FALSE);
		//Bug00178389
		m_gkset.m_bSwitchStatus = m_bGkSwitchStatus;
    }    
    
}

void CSystemManageLogic::OnDestroy() 
{
	CDlgChild::OnDestroy();

	SAFE_RELEASE(m_plsMenu);
	
	m_networkdlg.DestroyWindow();
	m_serversetdlg.DestroyWindow();
	m_SystemTime.DestroyWindow();
	m_gkset.DestroyWindow();
	m_cNMCfgLogic.DestroyWindow();
	m_cVTRCfgLogic.DestroyWindow();
}

void CSystemManageLogic::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDlgChild::OnShowWindow(bShow, nStatus);
	
	if(bShow)
	{
		if( m_pUmsConfig == NULL )
		{
			BUSINESSIFPTR->GetCtrlInterface(&m_pUmsConfig);
		}
	}
}

void CSystemManageLogic::InitDlg()
{   
	ShowWindow(SW_HIDE);

    SetControlToDefault();

    m_plsMenu->SetSelItem( 0 );
   	m_currentCwd = &m_networkdlg;          //set to default
    m_emCurrViewType = em_WND_UMSNETCFG;   //set to default 
    m_stChildWndTitle.SetWindowText( SYSTEM_WND_MENU_UMSWEBCONFIG );
    
    //初始化子功能页面
    m_networkdlg.InitDlg();
    m_serversetdlg.InitDlg();
    m_SystemTime.InitDlg();
	m_gkset.InitDlg();
	m_cNMCfgLogic.InitDlg();
	m_cVTRCfgLogic.InitDlg();
}

LRESULT CSystemManageLogic::OnRefreshGlobalAddrbook( WPARAM wParam, LPARAM lParam )
{
	CMsgHandle::SendMessage( UI_CNS_REFRESH_GLOBAL_ADDRBOOK );    //发送数据到全局地址簿
	return S_OK;
}

LRESULT CSystemManageLogic::OnRefreshGlobalAddrbookEx( WPARAM wParam, LPARAM lParam )
{
	CMsgHandle::SendMessage( UI_CNS_REFRESH_GLOBAL_ADDRBOOKEX, wParam, lParam );    //发送数据到全局地址簿
	return S_OK;
}

HRESULT CSystemManageLogic::OnGetUmsSystimeTime( WPARAM wparam, LPARAM lparam )
{  
	CMsgHandle::SendMessage( UI_GET_UMS_SYSTIME );   //发送UMS服务器系统时间到系统时间设置页面
	return S_OK;
}

void CSystemManageLogic::OnBtnTimeSync()
{
	m_SystemTime.SyncTimeToServer();
}

void CSystemManageLogic::SetNetCfgControl( bool bIsEnable )
{
    m_networkdlg.m_Ip.EnableWindow( bIsEnable );
    m_networkdlg.m_Ip_Sub.EnableWindow( bIsEnable );
    m_networkdlg.m_Ip_GetWay.EnableWindow( bIsEnable );
}

//true show save , cancel & hide edit
//false show edit & hide save, cancel
void CSystemManageLogic::SetEditControl( bool bIsEnable )
{
    m_btnSave.ShowWindow( bIsEnable );
    m_btnCancel.ShowWindow( bIsEnable);

    m_btnEdit.ShowWindow( !bIsEnable );
}

//only show net configure window
void CSystemManageLogic::SetControlToDefault()
{
    m_networkdlg.ShowWindow( SW_SHOW );  //show this window at login
    
    if ( m_emCurrViewType == em_WND_SIPNETCFG )
    {
        m_serversetdlg.ShowWindow( SW_HIDE );
    }
    else if ( m_emCurrViewType == em_WND_SYSTEMTIME)
    {        
        m_btnTimeSync.ShowWindow( SW_HIDE ); 
        m_SystemTime.ShowWindow( SW_HIDE );
        
    }
    else if ( m_emCurrViewType == em_WND_GKSET )
    {
        m_gkset.ShowWindow( SW_HIDE );
    } 

    SetEditControl( FALSE );
    
    if ( m_networkdlg.m_bIsEdit == TRUE )
    {       
        SetNetCfgControl( FALSE );      
    }
    if ( m_serversetdlg.m_bIsEdit == TRUE )
    {        
        m_serversetdlg.m_Ip.EnableWindow( FALSE ); 
    }
    if ( m_gkset.m_bIsEdit == TRUE )
    {    
        SetGKControl( FALSE );    
    }
    if ( m_SystemTime.m_bIsEdit == TRUE )
    {  
        m_SystemTime.SetTimeControl( FALSE );  //show btn & stop timer
    }
}

