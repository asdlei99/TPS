#include "StdAfx.h"
#include "system.h"
#include "cncmsgmanager.h"

template<> CSystem* Singleton<CSystem>::ms_pSingleton  = NULL;
const String CSystem::strMainWindow		= _T("cnc");
const String CSystem::strSkin			= _T("skin");
const String CSystem::strDefaultSkin	= _T("skin\\");
const String CSystem::strPCVersion      = _T("pcversion");

const String g_stcStrMainFrameDlg = _T("cnc"); 
const String g_stcStrLoginDlg = _T("LoginDlg");
const String g_strMainMenuDlg = _T("MainMenu");
const String g_strAddrbookDlg = _T("AddrBookDlg");
const String g_strInviteCnsDlg = _T("InviteCnsDlg");
const String g_strTemporaryCallDlg = _T("TemporaryCallDlg");
const String g_strConfTempDlg = _T("ConfTempDlg");
const String g_strConfCtrlDlg = _T("ConfCtrlDlg");
const String g_strRoomControlDlg = _T("RoomControlDlg");
const String g_strAddrEditDlg = _T("AddrEditDlg");
const String g_strRegServiceDlg = _T("RegServiceDlg");
const String g_strUserManagerDlg = _T("UserManagerDlg");
const String g_strUserDefinedDlg = _T("UserDefinedDlg");
const String g_strConfCallCfgDlg = _T("ConfCallCfgDlg");
const String g_strConfMsgDlg = _T("ConfMsgDlg");
const String g_strSysConfigDlg = _T("SysConfigDlg");
const String g_strLocalRoomCfgDlg = _T("LocalRoomCfgDlg");
const String g_strSrcSelWatchDlg = _T("SrcSelWatchDlg");
const String g_strMessageBoxDlg = _T("MessageBoxDlg");
const String g_strCalendarDlg = _T("CalendarDlg");
const String g_stcStrCenterCtrlDlg = _T("CenterControlDlg");
const String g_stcStrDualViewDlg = _T("DualViewDlg");
const String g_stcStrTvWallChildDlg = _T("TvWallChildDlg");
const String g_strReconnectBox = _T("ReconnectBox");
const String g_strContentReqDlg = _T("ContentReqDlg");

CSystem::CSystem(void)
{
}

CSystem::CSystem(String strFile) : m_strFile(strFile)
{
	bool bRet = IniSystem();
}


CSystem::~CSystem(void)
{

}


bool CSystem::IniSystem()
{
	// 初始化消息管理器
	if (ICncMsgManager::GetSingletonPtr() == 0) new CCncMsgManager();

	String strValue = _T("");
	bool bRet = DOCMNGR()->GetDoc(m_strFile, strSkin, strValue);
	CPaintManagerUI::SetResourcePath( bRet ? strValue.c_str() : strDefaultSkin.c_str() );

	bRet = DOCMNGR()->GetDoc(m_strFile, strPCVersion, strValue);
	UIDATAMGR->SetPcVersion( _tcscmp( strValue.c_str(), _T("true") )  == 0 /*atoi(CT2A(strValue.c_str(), DEFAULT_CODEGE))*/ );

    //是否自适应分辨率
	if (UIDATAMGR->IsPcVersion())
	{
		bRet = DOCMNGR()->GetDoc(m_strFile, _T("Resolution"), strValue);
	}
	else
	{
		bRet = DOCMNGR()->GetDoc(_T("..\\..\\") + m_strFile, _T("Resolution"), strValue);
	}
    
	SIZE sizeSrc;
	SIZE sizeDst;
	sizeSrc.cx = 1920;
	sizeSrc.cy = 1200;

    LPTSTR pstr = NULL;
    sizeDst.cx = _tcstol( (LPCTSTR)strValue.c_str(), &pstr, 10);  
    sizeDst.cy = _tcstol(pstr + 1, &pstr, 10);

	if ( sizeDst.cx != 0 && sizeDst.cy != 0 )
	{
		if ( (sizeDst.cx != sizeSrc.cx) || (sizeDst.cy != sizeSrc.cy ) )
		{
			CPaintManagerUI::SetSelfAdaption(true);
			CPaintManagerUI::SetAdpResolution( sizeSrc, sizeDst );
		}

        UIDATAMGR->SetCncMainPos(sizeDst);
	}
    else
    {
        UIDATAMGR->SetCncMainPos(sizeSrc);
    }

	ICncCommonOp::RegLogics();

	return true;
}


bool CSystem::Launch()
{

	bool bRet;
	if (UIDATAMGR->IsPcVersion())
	{
		bRet = IWindowManager::GetSingletonPtr()->ShowWindowCenter(CSystem::strMainWindow.c_str());
	}
	else
	{
		bRet = IWindowManager::GetSingletonPtr()->ShowWindow(CSystem::strMainWindow.c_str());
	}
	
	if (bRet == true)
	{
		CPaintManagerUI::MessageLoop();
	}
	else
	{
		//PT_LOGEVENT("创建主程序窗口失败\n");
	}
	return false;
}