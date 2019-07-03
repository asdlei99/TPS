#include "stdafx.h"
#include "UIDataMgr.h"
#include "mainframelogic.h"
#include "filemanager.h"
#include "toolwindowlogic.h"
#include "aboutlogic.h"
#include "messageboxlogic.h"
#include "sysupdateLogic.h"
#include "mainmenulogic.h"
#include "netadapter.h"
#include <dbt.h>

template<> CMainFrameLogic* Singleton<CMainFrameLogic>::ms_pSingleton  = NULL;


static UINT g_nUpdateTimerID;   //timer ��id������ˢ��ʱ��
static UINT g_wLoginTimerID = 0;//�Զ���¼��timer
static UINT g_wReConnectTimerID = 0;//�Զ�������timer
static UINT g_nDeviceChangeTimerID = 0;//��ʱ��ӦWM_DEVICECHANGE����ֹ����ʱ����

//static int m_nAutoLoginCount = 0;
VOID  CALLBACK  CBTimerPoc( HWND hwnd, UINT  uMsg, UINT_PTR idEvent, DWORD dwTime  );

//u16 g_wLocalTimerID;             //����ʱ���timer ��handle,ˢ�±�����ʱ�� �ϲ���g_nUpdateTimerID

APP_BEGIN_MSG_MAP(CMainFrameLogic, CNotifyUIImpl)
	MSG_CREATEWINDOW(_T("MainFrame"), OnCreate)
	MSG_INIWINDOW(_T("MainFrame"), OnInit)
	
	MSG_CLICK(_T("BtnHelp"), OnBtnHelp)
	MSG_CLICK(_T("BtnSysConfig"), OnBtnSysConfig)
	MSG_CLICK(_T("BtnExit"), OnBtnExit)

    USER_MSG( UI_CNS_CONNECTED, OnConnectRsp )    
	USER_MSG( WM_DEVICECHANGE, OnDeviceChange )
	USER_MSG( UI_TPAD_UPDATESYS_CMD, OnUpdateSysCmd )
	//�����������Ϣ
	USER_MSG( WM_WLAN_CONNECT_SUCCED, OnUpdateWifiState )
	USER_MSG( UI_TPAD_REFRESH_WIFI, OnUpdateWifiState )
	USER_MSG( WM_POWERBROADCAST, OnPowerBroadcast )
	//ϵͳ����
	USER_MSG(UI_TPAD_CENTRESLEEP_NTY, OnCentreSleepNotify )

    USER_MSG(WM_DUI_EDITSETFOCUS, OnEditSetFocus)

	USER_MSG(UI_CNS_DISCONNECTED, OnDisconnect)
	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnectClear)
	USER_MSG(UI_TPAD_CNSDISCONNECTED_NTY, OnCncNoReconnectNty)

APP_END_MSG_MAP()

CMainFrameLogic::CMainFrameLogic()
{
	g_nUpdateTimerID = 0;	
	g_wLoginTimerID = 0;
    g_wReConnectTimerID = 0;
    g_nDeviceChangeTimerID = 0;
    m_bActiveExit = FALSE;
    m_bRegDeviceChange = FALSE; 
    m_pKeyboard = NULL;
    m_nSysVol = 0;
}


CMainFrameLogic::~CMainFrameLogic()
{
    APIUninitVolumeCtrl();
}

bool CMainFrameLogic::OnCreate( TNotifyUI& msg )
{
	HWND hWnd = m_pm->GetPaintWindow();
	LONG styleValue = ::GetWindowLong(hWnd, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	styleValue &= ~WS_SIZEBOX;//���ڴ�С������ק
	::SetWindowLong(hWnd, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

#ifndef _DEBUG
	RECT rcCaption = {0,0,0,0};
	m_pm->SetCaptionRect(rcCaption);
#endif // _DEBUG

    g_nDeviceChangeTimerID = SetTimer( NULL, 0, 2000, CBTimerPoc );//2s��ſ��Ե����¼����ֹ������ʱ�����¼��������

    //ϵͳ�����ӿ�
    APIInitVolumeCtrl();
    APIGetMasterVolume( m_nSysVol );
	return false;
}

bool CMainFrameLogic::OnInit( TNotifyUI& msg )
{
	REG_TPAD_MSG_WND_OB(m_pm->GetPaintWindow());

	//��ini�ļ� ����
	int wAuto=0;
	wAuto = GetPrivateProfileInt(_T("LoginInfo"),_T("AutoLogin"), 0, GetIniFilePath());
	TCHAR tchIP[40] = {0};
	TCHAR tchUserName[MAX_NAME_LEN]={0};
	TCHAR tchPassWord[MAX_NAME_LEN]={0};

	GetPrivateProfileString(_T("LoginInfo"),_T("IP"),_T(""), tchIP, 40, GetIniFilePath());
	GetPrivateProfileString(_T("LoginInfo"),_T("UserName"),_T(""), tchUserName, MAX_NAME_LEN-1, GetIniFilePath());
	GetPrivateProfileString(_T("LoginInfo"), _T("PassWord"),_T(""), tchPassWord, MAX_NAME_LEN-1, GetIniFilePath());

	ITPadCommonOp::SetControlText(tchIP, m_pm, _T("EdIp"));
	ITPadCommonOp::SetControlText(tchUserName, m_pm, _T("EdUserName"));
	ITPadCommonOp::SetControlText(tchPassWord, m_pm, _T("EdPassword"));

	//����ϵͳ����
	CString strIniPath = GetIniFilePath(_T("cnc"));
	TCHAR tchSysName[MAX_NAME_LEN]={0};
	GetPrivateProfileString(_T("SysNameInfo"),_T("name"), _T("���ʻ᳡����̨"),tchSysName, MAX_NAME_LEN, strIniPath);
	ITPadCommonOp::SetControlText(tchSysName, m_pm, _T("lbSysName"));

	//���Զ���¼
	if ( wAuto == 0 )
	{
		CString str(tchPassWord);
		if (!str.IsEmpty())
		{
			CCheckBoxUI *pCheckRemPassWord = (CCheckBoxUI*)ITPadCommonOp::FindControl( m_pm, _T("CheckRemPassWord") );
			if (pCheckRemPassWord)
			{
				pCheckRemPassWord->SetCheckNoMsg(true);
			}
		}

	}
	//�Զ���¼
	else if ( wAuto == 1 )
	{
		CCheckBoxUI *pCheckAutoLogin = (CCheckBoxUI*)ITPadCommonOp::FindControl( m_pm, _T("CheckAutoLogin") );
		CCheckBoxUI *pCheckRemPassWord = (CCheckBoxUI*)ITPadCommonOp::FindControl( m_pm, _T("CheckRemPassWord") );

		if (pCheckAutoLogin && pCheckRemPassWord)
		{
			pCheckAutoLogin->SetCheckNoMsg(true);
			pCheckRemPassWord->SetCheckNoMsg(true);
		}
        //��ʱ5���½����ֹ����ʱwifi��û������ -xcr
		g_wLoginTimerID = SetTimer( NULL, 0, 5000, CBTimerPoc );
	}

	ITPadCommonOp::ShowControl( true, m_pm, _T("PageLogin") );
	ITPadCommonOp::ShowControl( false, m_pm, _T("PageTPadMain") );
	WINDOW_MGR_PTR->ShowWindow( g_strMainMenuDlg.c_str(), false);

	WINDOW_MGR_PTR->ShowWindow( g_strFilemanagerDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strFilePreviewDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strWbManager.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strVideoDlg.c_str(), false );
	WINDOW_MGR_PTR->ShowWindow( g_strAboutDlg.c_str(), false );
    WINDOW_MGR_PTR->ShowWindow( g_strNetCfgDlg.c_str(), false );

	ToolWindowreSet(false, true);
	m_pKeyboard = WINDOW_MGR_PTR->NewWindow( g_strToolWnd.c_str(), g_strToolWnd.c_str(), _T(""), WS_POPUP, UI_WNDSTYLE_EX_TOOL, 0, 0, 0 );
	m_pKeyboard->ShowWindow(true);

	UpdateSysTime();
	//g_wLocalTimerID = SetTimer( NULL, 0, 30000, CBTimerPoc );
	UpdateWifiState();

    CEditUI* pEdPassword = (CEditUI*)ITPadCommonOp::FindControl(m_pm,_T("EdPassword"));
    if ( pEdPassword != NULL )
    {
        pEdPassword->SetPasswordChar( _T('��') );
    }
    
	//���ð汾��
	CString strVer = _T("V");
	strVer  += _T(TPAD_VERSION_ID);
	ITPadCommonOp::SetControlText(strVer, m_pm, _T("version"));
	return true;
}


bool CMainFrameLogic::OnDeviceChange(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	bHandle = true;
	CFileManagerLogic::GetSingleton().OnDongleChange(wParam,lParam);

	switch(wParam)
	{
	case DBT_DEVICEARRIVAL:           // �豸�����������ҿ���ʹ��
		{
			//���ҵ�һ������update.ini�ļ���U��
			CString strUDiskName = _T("");
			BOOL bHaveUDisk = FALSE;
			BOOL bExist = ComInterface->GetFirstUDiskNameByFileName( strUDiskName, _T("updatetpad\\UpdateConfig.ini"), bHaveUDisk );	
			if ( bExist )
			{
				TCHAR tchVersion[MAX_NAME_LEN]={0};
				GetPrivateProfileString(_T("Version"),_T("Version"),_T(""), tchVersion, MAX_NAME_LEN-1, strUDiskName+ _T("updatetpad\\UpdateConfig.ini"));
				CString strVer(tchVersion);
				s8 achVersion[MAX_DEVICEVER_LEN] = {0};
				ComInterface->GetTPadVersion( achVersion );
				CString strOriVer(achVersion);

				ShowUdisUpdateDlg(strVer, strOriVer);
			}
		}        
		break;
    /*����Ϣ���࣬�ݲ���Ӧ����ֹ����
      case DBT_DEVNODES_CHANGED:   //��Ӧ�����豸������������������������»�ȡ      
        //CNetworkAdapter::CreateCurNetCardName();
        if ( m_bRegDeviceChange )
        {
            CNetworkAdapter::GetNetAdapterName();
        }     
        //OspPrintf( 1, 0, "OnDeviceChange DBT_DEVNODES_CHANGED : %d \n", wParam);
        break; */
	default:
		break;
	}

	return true;
}

CString CMainFrameLogic::GetIniFilePath(CString StrAppName /*= _T("tpad")*/)
{
	TCHAR tchPath[MAX_PATH] = {0};
	CString strIniFilePath;
	if (S_OK == SHGetFolderPathW(NULL,CSIDL_APPDATA,NULL,0,tchPath))
	{
		CString strIniFileDir(tchPath);
		strIniFileDir = strIniFileDir + _T("\\") + StrAppName;
		if(!PathFileExists(strIniFileDir))
		{
			CreateDirectory(strIniFileDir, NULL);
		}
		strIniFilePath = strIniFileDir + _T("\\conf.ini");
	}

	return strIniFilePath;
}

bool CMainFrameLogic::OnConnectRsp( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    if (wParam != TRUE)
    {
		if ( !ComInterface->IsAutoLogin() )
		{
			//��½ʧ��ʱ�����Զ������� �Զ�����ʱ���Դ���Ϣ
			m_bActiveExit = TRUE;
		}    
        return false;	
    }

    m_bActiveExit = FALSE;
    ComInterface->SetAutoLogin( FALSE );
    if ( g_wReConnectTimerID != 0 )
    {
        KillTimer( NULL, g_wReConnectTimerID );
        g_wReConnectTimerID = 0;
    }

    g_nUpdateTimerID = SetTimer( NULL, NULL, 30000, CBTimerPoc );
    //g_nFreshConfStateTimerID = SetTimer( NULL, NULL, 2000, CBTimerPoc );

    //��¼��ini�ļ� 
    String strIP = ITPadCommonOp::GetControlText(m_pm, _T("EdIp"));
    String strUser = ITPadCommonOp::GetControlText(m_pm, _T("EdUserName"));
    String strPassword = ITPadCommonOp::GetControlText(m_pm, _T("EdPassword"));

    CString strIniPath = GetIniFilePath();

    CString cstrIp = strIP.c_str();
    //UIDATAMGR->GetClearIP(cstrIp);
    WritePrivateProfileString(_T("LoginInfo"),_T("IP"),cstrIp,strIniPath);
    WritePrivateProfileString(_T("LoginInfo"),_T("UserName"),strUser.c_str(),strIniPath);

    CCheckBoxUI *pCheckAutoLogin = (CCheckBoxUI*)ITPadCommonOp::FindControl( m_pm, _T("CheckAutoLogin") );
    CCheckBoxUI *pCheckRemPassWord = (CCheckBoxUI*)ITPadCommonOp::FindControl( m_pm, _T("CheckRemPassWord") );
    if (pCheckAutoLogin)
    {
        if (pCheckAutoLogin->GetCheck())
        {
            WritePrivateProfileString(_T("LoginInfo"),_T("AutoLogin"),_T("1"),strIniPath);
            WritePrivateProfileString(_T("LoginInfo"),_T("PassWord"),strPassword.c_str(),strIniPath);
        }
        else
        {
            WritePrivateProfileString(_T("LoginInfo"),_T("AutoLogin"),_T("0"),strIniPath);
            if (pCheckRemPassWord->GetCheck())
            {
                WritePrivateProfileString(_T("LoginInfo"),_T("PassWord"),strPassword.c_str(),strIniPath);
            }
            else
            {
                WritePrivateProfileString(_T("LoginInfo"),_T("PassWord"),_T(""),strIniPath);
            }
        }
    }

	CMainMenuLogic::GetSingletonPtr()->UpdateMainMenu();
	if (ComInterface->IsManagerUser())
	{
		m_pm->DoCase(_T("caseAdminLogin"));
	}
	else
	{
		m_pm->DoCase(_T("caseNoAdminLogin"));
	}
    return true;
}


bool CMainFrameLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
    //�������˳��������Զ����� -2017.1.4 xcr
    if ( !m_bActiveExit )
    {
		//�Զ�����ʱ�յ�����Ϣ˵������ʧ�ܣ���������
		if ( ComInterface->IsAutoLogin() )
		{
			return true;
		}

		LPCWSTR className = NULL;
		LPCWSTR windName = _T("cnc");
		HWND hWnd = ::FindWindow( className , windName );
		if ( IsWindow( hWnd ) )
		{
			if ( ::IsWindowVisible( hWnd ) )
			{
				g_wReConnectTimerID = SetTimer( NULL, 0, 5000, CBTimerPoc ); 
				//���cnc��ʾ,����cnc�ĶԻ���
				ComInterface->NotifyCnsDisconnect( m_bActiveExit );
				return true;
			}         
		}

		g_wReConnectTimerID = SetTimer( NULL, 0, 5000, CBTimerPoc ); 
		WINDOW_MGR_PTR->ShowModal(g_strReconnectBox.c_str());
    }
	else
	{
		ComInterface->NotifyCnsDisconnect( m_bActiveExit );
		//������ݣ��˳�����½����
		NOTIFY_MSG( UI_DISCONNECTED_CLEARDATA );	
	}

    return true;
}

bool CMainFrameLogic::OnDisconnectClear(WPARAM wParam, LPARAM lParam, bool& bHandle)
{	
	if ( g_wReConnectTimerID != 0 )
	{
		KillTimer( NULL, g_wReConnectTimerID );
		g_wReConnectTimerID = 0;
		ComInterface->SetAutoLogin( FALSE );
	}	

	ITPadCommonOp::ShowControl( true, m_pm, _T("PageLogin") );
	ITPadCommonOp::ShowControl( false, m_pm, _T("PageTPadMain") );
	WINDOW_MGR_PTR->ShowWindow( g_strMainMenuDlg.c_str(), false );
	return true;
}

bool CMainFrameLogic::OnCncNoReconnectNty(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	if ( g_wReConnectTimerID != 0 )
	{
		KillTimer( NULL, g_wReConnectTimerID );
		g_wReConnectTimerID = 0;
	}
	ComInterface->SetAutoLogin( FALSE );
	//������ݣ��˳�����½����
	NOTIFY_MSG( UI_DISCONNECTED_CLEARDATA );
	return true;
}

VOID  CALLBACK  CBTimerPoc( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{
    if ( idEvent == g_nUpdateTimerID )
    {
        CMainFrameLogic::GetSingletonPtr()->UpdateSysTime();
        CFileManagerLogic::GetSingletonPtr()->UpdateShowTime();
		CAboutLogic::GetSingletonPtr()->UpdateShowTime();
    }
	else if ( idEvent == g_wLoginTimerID )
	{
		//m_nAutoLoginCount ++;
		vector<TNodeInfo> vctNodeList;
		if ( ComInterface->IsReadyLogin( vctNodeList ) )
		{
			KillTimer( NULL, g_wLoginTimerID );
			g_wLoginTimerID = 0;
			CMainFrameLogic::GetSingletonPtr()->AutoLogin(true);
		}
		else
		{			
			KillTimer( NULL, g_wLoginTimerID );
			g_wLoginTimerID = 0;
			CMainFrameLogic::GetSingletonPtr()->AutoLogin(false);
		}
	}
    else if ( idEvent == g_wReConnectTimerID )
    {
        CMainFrameLogic::GetSingletonPtr()->ReConnectCns();
    }
    else if ( idEvent == g_nDeviceChangeTimerID )
    {
        CMainFrameLogic::GetSingletonPtr()->ShowLoginBtn();//2s�������¼

        CMainFrameLogic::GetSingletonPtr()->RegDeviceChangeMsg();
        KillTimer( NULL, g_nDeviceChangeTimerID );
        g_nDeviceChangeTimerID = 0;
    }

}

bool CMainFrameLogic::OnBtnExit(TNotifyUI& msg)
{
	int nRet = ShowMessageBox( _T("�Ƿ�Ҫע����"), true);
	if ( nRet == IDOK )
	{  
        m_bActiveExit = TRUE; //�����˳�
		ComInterface->DisConnect();
	}
	return true;
}

bool CMainFrameLogic::OnBtnHelp(TNotifyUI& msg)
{
	WINDOW_MGR_PTR->ShowWindowFromLeftToRight( g_strAboutDlg.c_str(), true );
	return true;
}

bool CMainFrameLogic::OnBtnSysConfig(TNotifyUI& msg)
{
    if ( ComInterface->IsReceiveDual() )
    {
        return true;
    }

	ComInterface->OpenSysConfig();

	//����cnc 2016-5-6 
	//�������
	TMainMenuInfo tMenuInfo;
	tMenuInfo.SetNull();
	memcpy(tMenuInfo.achName, MENU_CNSCONSOLE, sizeof(MENU_CNSCONSOLE)); 
	memcpy(tMenuInfo.achExePath, _T("cnc\\cnc.exe"), sizeof(_T("cnc\\cnc.exe")));
	memcpy(tMenuInfo.achExeCaption, _T("cnc"), sizeof(_T("cnc")));

	ComInterface->OpenExe( tMenuInfo );
	return true;
}

bool CMainFrameLogic::OnUpdateSysCmd(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	TTPTPadVerInfo tTPTPadVerInfo;
	ComInterface->GetTPadVerInfo(tTPTPadVerInfo);

	s8 achVersion[MAX_DEVICEVER_LEN] = {0};
	ComInterface->GetTPadVersion( achVersion );

	//if ( nVersionId > nCurrentId )   ��Ϊ�汾�Ų�һ�¾����� -2014.6.6 xcr
	if ( strcmp( tTPTPadVerInfo.m_achTPadVersion, achVersion ) != 0 )
	{
		WINDOW_MGR_PTR->ShowModal(g_strUpdateDlg.c_str());
	}

	return NO_ERROR;
}

bool CMainFrameLogic::OnUpdateWifiState(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	CMainFrameLogic::GetSingletonPtr()->UpdateWifiState();
	return true;
}

bool CMainFrameLogic::OnPowerBroadcast(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
	if ( wParam == PBT_APMPOWERSTATUSCHANGE )
	{
		CMainFrameLogic::GetSingletonPtr()->UpdatePowerState();
	}
	return true;
}

bool CMainFrameLogic::OnCentreSleepNotify(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    m_bActiveExit = TRUE; //ϵͳ�������Զ�����
	ComInterface->DisConnect();
	return NO_ERROR;
}

void CMainFrameLogic::UpdateSysTime()
{
	SYSTEMTIME sysTime;
	::GetLocalTime( &sysTime );

	CString strHorMin;
	strHorMin.Format( _T("%.2d"), sysTime.wHour );

	CString strMin;
	strMin.Format( _T("%.2d"), sysTime.wMinute );

	strHorMin = strHorMin + ":" + strMin;

	ITPadCommonOp::SetControlText(strHorMin, m_pm, _T("labTime"));

    UpdateWifiState();
	//���µ�Դͼ��
	UpdatePowerState();
}

void CMainFrameLogic::UpdatePowerState()
{
	//���µ��
	SYSTEM_POWER_STATUS ps;
	GetSystemPowerStatus(&ps);

	//BatteryFlag 8:�����  128:û�е��  255:δ֪
	if ( ps.BatteryFlag == BATTERY_FLAG_NO_BATTERY || ps.BatteryFlag == BATTERY_FLAG_UNKNOWN )
	{
		ITPadCommonOp::SetControlText(_T(""), m_pm, _T("labBatteryLife"));
	}
	else
	{
		CString strLife;
		strLife.Format( _T("%d"), ps.BatteryLifePercent );
		strLife += _T("%");
		ITPadCommonOp::SetControlText(strLife, m_pm, _T("labBatteryLife"));
	}

	int nLife = 0;
	//�Ƿ�ʹ�ý�����Դ
	if ( ps.ACLineStatus != AC_LINE_ONLINE )
	{	
		m_pm->DoCase(_T("caseBatteryNOACLine"));

		if ( ps.BatteryFlag == BATTERY_FLAG_NO_BATTERY || ps.BatteryFlag == BATTERY_FLAG_UNKNOWN )
		{
			nLife = 0;
		}
		else
		{
			nLife = ps.BatteryLifePercent;		
		}
	}
	else
	{	
		//255��ʾʹ�ý�����Դ
		m_pm->DoCase(_T("caseBatteryACLine"));
		nLife = 100/*255*/;
	}

	CProgressUI *pProgressBattery = (CProgressUI*)ITPadCommonOp::FindControl( m_pm, _T("progressBarBattery") );
	if (pProgressBattery)
	{
		pProgressBattery->SetValue(nLife);
	}
}

bool CMainFrameLogic::AutoLogin(bool bSuc)
{
	TCHAR tchIP[16] = {0};
	TCHAR tchUserName[MAX_NAME_LEN]={0};
	TCHAR tchPassWord[MAX_NAME_LEN]={0};

	GetPrivateProfileString(_T("LoginInfo"),_T("IP"),_T(""), tchIP, 16, GetIniFilePath());
	GetPrivateProfileString(_T("LoginInfo"),_T("UserName"),_T(""), tchUserName, MAX_NAME_LEN-1, GetIniFilePath());
	GetPrivateProfileString(_T("LoginInfo"), _T("PassWord"),_T(""), tchPassWord, MAX_NAME_LEN-1, GetIniFilePath());

	if (bSuc)
	{
        CString cstrIp = tchIP;
        UIDATAMGR->GetClearIP(cstrIp);
		u32 dwIp = ntohl( inet_addr( CT2A(cstrIp) ) );
		u16 uRe = ComInterface->Connect( dwIp, CONNETCT_CNS_PORT, tchUserName, tchPassWord );
	}
	else
	{
		ShowMessageBox((_T("�Զ���½ʧ�ܣ��᳡����ģ��δ����")),false);
	}

	return true;
}

void CMainFrameLogic::UpdateWifiState()
{
	if ( APIWlanIsConn() )
	{
		// 		TWlanInfo  tWlanInfo[WIFI_MAX_SEARCH_NUM];
		// 		ZeroMemory( &(tWlanInfo[0]), sizeof( tWlanInfo ) );
		// 		int nTotalItemNum = APIWlanScan( tWlanInfo );
		// 		
		// 		int nWifiSignal = 0;
		// 		for ( int nIndex = 0; nIndex < nTotalItemNum; nIndex++ )
		// 		{
		// 			if ( tWlanInfo[nIndex].m_bConnected )
		// 			{
		// 				nWifiSignal = tWlanInfo[nIndex].m_nQuality;				
		// 				break;
		// 			}
		// 		}

		TWlanInfo tWlanInfo;
		BOOL bConnect = APIWlanGetConnInfo( tWlanInfo );

		int nWifiSignal = 0;
		if ( bConnect )
		{
			nWifiSignal = tWlanInfo.m_nQuality;
		}

		if ( nWifiSignal == 0 )
		{
			m_pm->DoCase( _T("caseWifiNoSignal") );
		}
		else if ( nWifiSignal > 0 && nWifiSignal <= 33 )
		{
			m_pm->DoCase( _T("caseWifiLittleSignal") );
		}
		else if ( nWifiSignal > 33 && nWifiSignal <= 66 )
		{
			m_pm->DoCase( _T("caseWifiHalfSignal") );
		}
		else if ( nWifiSignal > 66 )
		{			
			m_pm->DoCase( _T("caseWifiFullSignal") );
		}		
	}
	else
	{
		m_pm->DoCase( _T("caseWifiNoSignal") );
	}
}

void CMainFrameLogic::ShowLoginPage()
{
    ITPadCommonOp::ShowControl( true, m_pm, _T("PageLogin") );
}

void CMainFrameLogic::ReConnectCns()
{
    ComInterface->SetAutoLogin( TRUE );
    ComInterface->ReConnectCns();
}

void CMainFrameLogic::SetActiveExit( BOOL bActve )
{
    m_bActiveExit = bActve;
}

void CMainFrameLogic::RegDeviceChangeMsg()
{
    m_bRegDeviceChange = TRUE;
}

//ϵͳ����
void CMainFrameLogic::OnThinkpadVolumeLow(int nStep)
{
    APIGetMasterVolume( m_nSysVol );

    if ( m_nSysVol > 0 )
    {
		if (m_nSysVol - nStep < 0)
		{
			APISetMasterVolume( 0 );
		}
		else
		{
			APISetMasterVolume( (m_nSysVol - nStep) );
		}

        APIGetMasterVolume( m_nSysVol );
    }
}

void CMainFrameLogic::OnThinkpadVolumeAdd(int nStep)
{
    APIGetMasterVolume( m_nSysVol );

    if ( m_nSysVol < 100 )
    {
        //SetMasterVolumeValue( (nStep + 1) * VOLUME_STEP );
		if (m_nSysVol + nStep > 100)
		{
			APISetMasterVolume( 100 );
		}
		else
		{
			APISetMasterVolume( (m_nSysVol + nStep) );
		}
        
        APIGetMasterVolume( m_nSysVol );
    }
}

bool CMainFrameLogic::OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    ComInterface->ShowKeyboard();
    return true;
}

void CMainFrameLogic::ShowLoginBtn()
{
    ITPadCommonOp::EnableControl( true, m_pm, _T("BtnLogin") );//����2s��ſ��Ե�¼
}
