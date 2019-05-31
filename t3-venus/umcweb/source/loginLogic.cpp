// LoginUmc.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "loginLogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define UMS_PORT   60001

extern CMainLogic * g_pMainDlg;
extern CLoginLogic* m_pLoginDlg;

BOOL g_bIsLoginDestory = FALSE; //ldy 解决同一进程删除顺序倒置  出现初始化失败问题

extern HHOOK g_hHook;
extern HANDLE m_hMutex;

extern float CUR_SCREEN_WIDTH_PER;
extern float CUR_SCREEN_HEIGHT_PER;
/////////////////////////////////////////////////////////////////////////////
// CLoginLogic dialog
CLoginLogic::CLoginLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CLoginLogic::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginLogic)
	//}}AFX_DATA_INIT
    m_IsCreateGrp = TRUE;
	//m_dwBkResourceID = IDR_PNG_LOGINWND_BK;
	m_bShowMosaicVertImg = TRUE;     //垂直背景
	m_bIsBtnOnStatus = TRUE;
	m_bShowMosaicHoriImg = FALSE;
    m_dwIP = 0;
	m_strRememberStatus = "ON";
}

void CLoginLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginLogic)
	DDX_Control(pDX, IDC_STATIC_COMPANY, m_stCompay);
	DDX_Control(pDX, IDC_STATIC_VERSION, m_stVersion);
	DDX_Control(pDX, IDC_BUTTON_ONOROFF, m_btnOnOrOff);
	DDX_Control(pDX, IDC_STATIC_RECORDPASSWORD, m_stRecordPassword);
	DDX_Control(pDX, IDC_STATIC_Title, m_stTitle);
	DDX_Control(pDX, IDC_STATIC_LOGO, m_stLogo);
	DDX_Control(pDX, IDC_STATIC_BKCHILD, m_stBkChild);
	DDX_Control(pDX, IDC_BUTTON_LOGIN, m_btnLogin);
	DDX_Control(pDX, IDC_IPADDR_UMC_IP, m_etIP);
	DDX_Control(pDX, IDC_EDIT_USER_NAME, m_etUserName);
	DDX_Control(pDX, IDC_EDIT_USER_PSWD, m_etUserPSWD);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLoginLogic, CDlgChild)
	//{{AFX_MSG_MAP(CLoginLogic)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, OnLogin)
	ON_BN_CLICKED(IDC_BUTTON_ONOROFF, OnButtonOnorOff)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(UI_UMS_CONNECTED, OnLoginResult)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginLogic message handlers

void CLoginLogic::RegisterFun()
{
	REG_MSG( UI_UMS_CONNECTED, GetSafeHwnd() );
}

BOOL CLoginLogic::InitControlPane()
{   
	int nFontSize = 12;
	CRect rectClient( 0, 0, /*BASE_SCREEN_WIDTH*/BASE_SCREEN_WIDTH_INIE*CUR_SCREEN_WIDTH_PER, BASE_SCREEN_HEIGHT_INIE*CUR_SCREEN_HEIGHT_PER );
	this->SetWindowPos( NULL, 0, 0, rectClient.Width(), rectClient.Height(), SWP_SHOWWINDOW ); 

	//初始化界面控件图片控件
	m_stBkChild.SetImage( IDR_PNG_LOGINWND_BKCHILD );
	m_btnOnOrOff.SetImage( IDR_PNG_LOGINWND_BTN_ON,IDR_PNG_LOGINWND_BTN_ONDOWN, IDR_PNG_LOGINWND_BTN_ONDIS );
	m_btnLogin.SetImage( IDR_PNG_LOGINWND_BTN_LOGINDIS, IDR_PNG_LOGINWND_BTN_LOGIN, IDR_PNG_LOGINWND_BTN_LOGIN );
	m_stLogo.SetImage(IDR_PNG_LOGINWND_LOGO);

	CUmcwebCommon::SetImgForTransIpEdit(&m_etIP);
	CUmcwebCommon::SetImgForTransEdit(&m_etUserName);
	CUmcwebCommon::SetImgForTransEdit(&m_etUserPSWD);

	m_etIP.SetSearchEdit(FALSE);
	m_etUserName.SetSearchEdit(FALSE);
	m_etUserPSWD.SetSearchEdit(FALSE);
	
	s32 nBKChildWidth = m_stBkChild.GetImageSize().cx*CUR_SCREEN_WIDTH_PER;
	s32 nBKChildHeight = m_stBkChild.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER;
	
	s32 nBKChildXPos = ( rectClient.Width() - nBKChildWidth )/2;
	
	CSize sz( 0, 0 );
	CRect rc( 0, 0, 0, 0 );
	
	sz = m_stLogo.GetImageSize();
	m_stLogo.SetWindowPos( NULL, nBKChildXPos + nBKChildWidth/2 - 88*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, 
		sz.cx*CUR_SCREEN_WIDTH_PER, sz.cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	
	m_stTitle.SetWindowPos( NULL, 0,  20 + m_stLogo.GetImageSize().cy + 14, rectClient.Width(), sz.cy,
		   SWP_SHOWWINDOW );
	m_stTitle.SetWindowText("网呈统一管理控制台");
	m_stTitle.SetTextAlign(StringAlignmentCenter);
	m_stTitle.SetTextColor(Color( 49, 49, 49 ));
	m_stTitle.SetFont( 18, "微软雅黑" );

	m_stTitle.GetWindowRect(&rc);
	this->ScreenToClient( &rc );
	s32 nBKChildYPos = rc.bottom + 17;

	m_stBkChild.SetWindowPos( NULL, nBKChildXPos, nBKChildYPos, 
		nBKChildWidth, nBKChildHeight,  SWP_SHOWWINDOW );
   
	UINT nShow = SWP_HIDEWINDOW;
	if ( m_dwIP == 0 )
	{  
		nShow = SWP_SHOWWINDOW;		  
	} 
	else
	{
		m_etIP.SetAddress( m_dwIP );
	}
	
	m_etIP.SetWindowPos( &m_stBkChild, nBKChildXPos + 68*CUR_SCREEN_WIDTH_PER, nBKChildYPos + 29*CUR_SCREEN_HEIGHT_PER, 
		314*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER,	nShow );

	CRect rectWarning;
	this->GetWindowRect(&rectWarning);
	ScreenToClient(rectWarning);
	m_etUserPSWD.SetWindowPos( &m_stBkChild, nBKChildXPos + 68*CUR_SCREEN_WIDTH_PER, nBKChildYPos + 29*CUR_SCREEN_HEIGHT_PER + 2*(41 + 11)*CUR_SCREEN_HEIGHT_PER, 314*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, 
		SWP_SHOWWINDOW );
	m_etUserName.SetWindowPos( &m_stBkChild, nBKChildXPos + 68*CUR_SCREEN_WIDTH_PER, nBKChildYPos + (29 + 41 + 11)*CUR_SCREEN_HEIGHT_PER, 
		314*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );   //最后设置为焦点停留位置

	m_etUserName.SetFont( nFontSize, "微软雅黑" );
	m_etUserName.SetLimitLength(31);
	m_etUserName.SetTipStr("请输入用户名");

	m_etUserPSWD.SetFont( nFontSize, "微软雅黑" );
	m_etUserPSWD.SetLimitLength(31);
	m_etUserPSWD.SetTipStr("请输入密码");

	m_etIP.SetTipStr("请输入IP地址");

	m_etUserPSWD.GetWindowRect(&rc);
	this->ScreenToClient( &rc );
	m_stRecordPassword.SetWindowPos( &m_stBkChild , nBKChildXPos + 83 , rc.bottom + 23,  314 , /*41*/25,
		SWP_SHOWWINDOW );
	m_stRecordPassword.SetWindowText("记住密码");
	m_stRecordPassword.SetTextColor(Color( 67, 67, 68 ));
	m_stRecordPassword.SetFont( nFontSize, "微软雅黑" );

	sz = m_btnOnOrOff.GetImageSize();
	m_btnOnOrOff.SetWindowPos( &m_stBkChild, nBKChildXPos + nBKChildWidth - (70 + sz.cx)*CUR_SCREEN_WIDTH_PER, rc.bottom + 17*CUR_SCREEN_HEIGHT_PER, sz.cx*CUR_SCREEN_WIDTH_PER, sz.cy*CUR_SCREEN_HEIGHT_PER, 
		SWP_SHOWWINDOW );	
 
	m_btnOnOrOff.GetWindowRect( &rc ); 
	ScreenToClient( &rc );
    sz = m_btnLogin.GetImageSize();
	m_btnLogin.SetWindowPos( &m_stBkChild, nBKChildXPos + 160*CUR_SCREEN_WIDTH_PER, rc.bottom + 22*CUR_SCREEN_HEIGHT_PER,
							 sz.cx*CUR_SCREEN_WIDTH_PER, sz.cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

	m_stVersion.SetWindowPos( NULL, 0, rectClient.bottom - (40 + 24 + 13)*CUR_SCREEN_HEIGHT_PER, rectClient.Width(), 24, SWP_SHOWWINDOW );
	m_stVersion.SetWindowText("V1.1.3.0.0");
	m_stVersion.SetTextAlign(StringAlignmentCenter);
	m_stVersion.SetTextColor(Color( 65, 72, 83 ));
	m_stVersion.SetFont( nFontSize, "微软雅黑" );

	m_stVersion.GetWindowRect( &rc );
	this->ScreenToClient( &rc );
	m_stCompay.SetWindowPos( &wndTop, 0, rc.top - (4 + 24)*CUR_SCREEN_HEIGHT_PER, rc.Width(), 24, SWP_SHOWWINDOW );
	m_stCompay.SetWindowText("Copyright (C) 2010-2014, 苏州科达科技股份有限公司");
	m_stCompay.SetTextAlign(StringAlignmentCenter);
	m_stCompay.SetTextColor(Color( 65, 72, 83 ));
	m_stCompay.SetFont( nFontSize, "微软雅黑" );

	CTransparentDlgWarning::GetDlgPtr()->SetWindowPos( &wndTop, rectWarning.right - 359*CUR_SCREEN_WIDTH_PER, 
		rectWarning.top + 40*CUR_SCREEN_HEIGHT_PER, /*359*CUR_SCREEN_WIDTH_PER*/0, /*313*CUR_SCREEN_HEIGHT_PER*/0, 
		SWP_HIDEWINDOW | SWP_NOSIZE); 

	return TRUE;
}

BOOL CLoginLogic::OnInitDialog()
{
	CDlgChild::OnInitDialog();

	CMsgHandle::Init();

	RegisterFun();

	g_bIsLoginDestory = FALSE;

	this->CenterWindow();
	InitControlPane();

	ReadConfig();

	if( NULL == g_hHook )
	{
		g_hHook = ::SetWindowsHookEx( WH_GETMESSAGE, GetMessageProc, 
                     AfxGetInstanceHandle(), GetCurrentThreadId() );
	}

	return TRUE;
}

void CLoginLogic::ReadConfig()
{
	s8 strBuf[256];
	memset( strBuf, 0, 256 );
	
	GetPrivateProfileString( _T("login"), _T("remembered"), NULL, strBuf, 40, UMCWEB_CONFIG );
	
	m_strRememberStatus = strBuf;
	if ( m_strRememberStatus.IsEmpty() )
	{
		m_strRememberStatus == "ON"; 
		m_bIsBtnOnStatus = TRUE;
		m_btnOnOrOff.SetImage( IDR_PNG_LOGINWND_BTN_ON,IDR_PNG_LOGINWND_BTN_ONDOWN, IDR_PNG_LOGINWND_BTN_ONDIS );
	}
	else if ( m_strRememberStatus == "ON" )
	{
		m_bIsBtnOnStatus = TRUE;
		m_btnOnOrOff.SetImage( IDR_PNG_LOGINWND_BTN_ON,IDR_PNG_LOGINWND_BTN_ONDOWN, IDR_PNG_LOGINWND_BTN_ONDIS );		
	}
	else
	{
		m_bIsBtnOnStatus = FALSE;
		m_btnOnOrOff.SetImage( IDR_PNG_LOGINWND_BTN_OFF,IDR_PNG_LOGINWND_BTN_OFFDOWN, IDR_PNG_LOGINWND_BTN_OFFDIS );
	}
	
	if( m_bIsBtnOnStatus )
	{
		if ( m_dwIP == 0 )
		{
			GetPrivateProfileString(_T("login"),_T("ip"),NULL, strBuf, 40, UMCWEB_CONFIG );
			CString strIpAddr = strBuf;
			DWORD dwIpAddr = ntohl(inet_addr(strIpAddr));
			m_etIP.SetAddress(dwIpAddr); 
		}
		else
		{
			GetPrivateProfileString(_T("login"),_T("ip"),NULL, strBuf, 40, UMCWEB_CONFIG );
			CString strIpAddr = strBuf;
			DWORD dwIpAddr = ntohl(inet_addr(strIpAddr));
			if ( m_dwIP != dwIpAddr )
			{
				return;
			}
		}

		GetPrivateProfileString( _T("login"), _T("username"), NULL, strBuf, 40, UMCWEB_CONFIG );
		m_etUserName.SetWindowText(strBuf);
		
		GetPrivateProfileString( _T("login"), _T("userpswd"), NULL, strBuf, 40, UMCWEB_CONFIG );
		m_etUserPSWD.SetWindowText(strBuf);
	}
	else
	{
		m_etIP.SetAddress(m_dwIP); 
		GetPrivateProfileString( _T("login"), _T("username"),NULL, strBuf, 40, UMCWEB_CONFIG );
		m_etUserName.SetWindowText(strBuf);
	}
}

void CLoginLogic::OnLogin() 
{
	CString strUserName;
	CString strUserPSWD;

	DWORD dwIpAddr = 0;
	m_etIP.GetAddress(dwIpAddr);

	m_etUserName.GetWindowText(strUserName);
	m_etUserPSWD.GetWindowText(strUserPSWD);

	if( !LoginCheck() ) 
	{
		//ShowWarningWnd(SWP_SHOWWINDOW);
		return;
	} 
 
	m_btnLogin.EnableWindow(FALSE);

	BOOL bCon = BUSINESSIFPTR->IsConnectedUms();
	if ( bCon )
	{   
		
		BUSINESSIFPTR->DisconnectUms();
	}

	u16 nRet = BUSINESSIFPTR->ConnectUms( dwIpAddr, (u16)UMS_LISTIONPORT_CMS, (LPCTSTR)strUserName, (LPCTSTR)strUserPSWD, TRUE );
	SetTimer( 11, 30000, NULL );  //设置连接服务器超时时间
	if ( nRet != NO_ERROR )
	{
		//加入错误码 IP 用户名   密码
		in_addr tAddr;
		tAddr.S_un.S_addr = ntohl(dwIpAddr);
		PrtMsg("\n  Error ID:%d, IP:%s, User Name:%s, PassWord:%s\n  ", 
				   nRet , inet_ntoa(tAddr), strUserName, strUserPSWD ); 

		MESSAGEWND( "登录失败：网络连接失败" );
		ShowWarningWnd(SWP_SHOWWINDOW);
		m_btnLogin.EnableWindow(TRUE);
		KillTimer( 11 );
	}
}

bool CLoginLogic::LoginCheck()
{
	CString strWarning;

	strWarning.TrimLeft();
	strWarning.TrimRight();
	int nIpLen = strWarning.GetLength();

	DWORD dwIpAddr = 0;
	m_etIP.GetAddress(dwIpAddr);
	m_etIP.GetWindowText(strWarning);
	strWarning.TrimLeft();
	strWarning.TrimRight();
	if ( strWarning.GetLength() == 0 )
	{
		CString strError = "IP地址不能为空！";
		int nRet = 0;
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return FALSE;
	}
	if( !CCallAddr::IsValidIpV4(dwIpAddr) )
	{
		CString strError = "IP地址非法！";
		int nRet = 0;
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return FALSE;
	}
	strWarning.Empty();

	m_etUserName.GetWindowText(strWarning);
	strWarning.TrimLeft();
	strWarning.TrimRight();
	if ( !strWarning.GetLength() )
	{
		CString strError;
		int nRet = 0;
		strError = "登录用户名不能为空！";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return FALSE;
	}
	strWarning.Empty();
	
	m_etUserPSWD.GetWindowText(strWarning);
	//密码全为空格的情况
	//strWarning.TrimLeft();
	//strWarning.TrimRight();
	if (strWarning.IsEmpty())
	{
		CString strError;
		int nRet = 0;
		strError = "登录密码不能为空！";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return FALSE;
	}

	return TRUE;
}

LRESULT CLoginLogic::OnLoginResult(WPARAM wParam, LPARAM lParam)
{
	m_btnLogin.EnableWindow(TRUE);
	KillTimer( 11 );

	CString strError;
	if( 0 == wParam )
	{
		switch( lParam )
		{
		case ERR_UMC_LOGIN_UMS_USER_ERR:
			strError = (_T("登录失败：用户名错误"));
			break;
		case ERR_UMC_LOGIN_UMS_PSWD_ERR:
			strError = (_T("登录失败：密码错误"));
			break;
		case ERR_UMC_LOGIN_UMS_MAX_LOGIN:
			strError = (_T("已达登录用户最大数"));
			break;
		case ERR_UMC_LOGIN_UMS_LOGED:
			strError = (_T("当前用户已登录"));
			break;
		case ERR_UMC_LOGIN_UMS_SYSINITING:
			strError = (_T("当前系统正在初始化，请稍候"));
			break;
		}
		
	   
		MESSAGEWND( strError );
		ShowWarningWnd(SWP_SHOWWINDOW);
	}
	else
	{
		CString strUserName;
		CString strPSWD;

		DWORD dwIpAddr = 0;
	    m_etIP.GetAddress(dwIpAddr);
		CString strIpAddr = m_etIP.GetIpStr(dwIpAddr);
		
		m_etUserName.GetWindowText(strUserName);
		m_etUserPSWD.GetWindowText(strPSWD);

		//显示主窗口
		if( m_bIsBtnOnStatus )
		{
			DeleteFile(UMCWEB_CONFIG);
			WritePrivateProfileString( _T("login"), _T("ip"), strIpAddr, UMCWEB_CONFIG );
			WritePrivateProfileString( _T("login"),_T("username"), strUserName , UMCWEB_CONFIG );
			WritePrivateProfileString( _T("login"),_T("userpswd"), strPSWD , UMCWEB_CONFIG );
			WritePrivateProfileString( _T("login"),_T("remembered"), "ON", UMCWEB_CONFIG );
		}
		else
		{
			DeleteFile(UMCWEB_CONFIG);
			WritePrivateProfileString( _T("login"), _T("ip"), "", UMCWEB_CONFIG );
			WritePrivateProfileString( _T("login"),_T("username"), strUserName , UMCWEB_CONFIG );
			WritePrivateProfileString( _T("login"),_T("userpswd"), "" , UMCWEB_CONFIG );
			WritePrivateProfileString( _T("login"),_T("remembered"), "OFF", UMCWEB_CONFIG );
			//m_etIP.SetAddress(0);
			m_etUserPSWD.SetWindowText("");
		}

		this->ShowWindow(SW_HIDE);
		HIDEMESSAGEWND
         
		if ( g_pMainDlg == NULL )
		{
			g_pMainDlg = new CMainLogic( this );
			g_pMainDlg->Create(IDD_DIALOG_MAIN,this);
		}

		if ( g_pMainDlg != NULL )
		{
			g_pMainDlg->ShowWindow(SW_SHOW);
			g_pMainDlg->RevertTabPage();
		}

		//发送背景色更新消息
		CMsgHandle::SendMessage( WM_DEF_CHANGEBKCOLOR, TRUE );
	}
	return 0;
}

void CLoginLogic::OnButtonOnorOff() 
{
	m_bIsBtnOnStatus = !m_bIsBtnOnStatus;

	if ( m_bIsBtnOnStatus )
	{
		m_btnOnOrOff.SetImage( IDR_PNG_LOGINWND_BTN_ON,IDR_PNG_LOGINWND_BTN_ONDOWN, IDR_PNG_LOGINWND_BTN_ONDIS );
	}
	else
	{
		m_btnOnOrOff.SetImage( IDR_PNG_LOGINWND_BTN_OFF,IDR_PNG_LOGINWND_BTN_OFFDOWN, IDR_PNG_LOGINWND_BTN_OFFDIS );
	}
}

void CLoginLogic::ShowWarningWnd(UINT nShowFlag)
{
	CRect rectWarning;
	m_stLogo.GetWindowRect(&rectWarning);
	//bug：64位电脑,登陆界面弹出的提示框位置不准确 -- 20140604 by xhx
	CTransparentDlgWarning::GetDlgPtr()->SetWindowPos(NULL, /*1366 - 359*/rectWarning.right + 200, rectWarning.top, 359, 313, nShowFlag );
}

void CLoginLogic::OnDestroy() 
{
	CTransparentDlgWarning::Clean();

	if ( NULL != g_hHook )
	{
		::UnhookWindowsHookEx(g_hHook);
		g_hHook = NULL;
	}

	CMsgHandle::Destroy();

	CDlgChild::OnDestroy();
}

BOOL CLoginLogic::Login()
{
    OnLogin();
    return TRUE;
}

void CLoginLogic::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDlgChild::OnShowWindow(bShow, nStatus);
	
	//::PostMessage( GetSafeHwnd(), WM_SETFOCUS, 0, 0 );   //120806---ldy 去除为用户提供默认焦点
}

void CLoginLogic::OnTimer(UINT nIDEvent) 
{
	if ( nIDEvent == 11 )
	{
		MESSAGEWND( "连接服务器超时" );
		ShowWarningWnd(SWP_SHOWWINDOW);
		m_btnLogin.EnableWindow(TRUE);
		KillTimer( 11 );
	}
	
	CDlgChild::OnTimer(nIDEvent);
}
