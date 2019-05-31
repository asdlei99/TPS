#include "StdAfx.h"
#include "system.h"


template<> CSystem* Singleton<CSystem>::ms_pSingleton  = NULL;
const String CSystem::strMainWindow		= _T("tpad");
const String CSystem::strSkin			= _T("skin");
const String CSystem::strDefaultSkin	= _T("skin\\");

const String g_stcStrMainFrameDlg = _T("tpad"); 
const String g_stcStrLoginDlg = _T("LoginDlg");
const String g_strMainMenuDlg = _T("MainMenu");
const String g_strMessageBoxDlg = _T("MessageBoxDlg");
const String g_strFilemanagerDlg = _T("FileManager");
const String g_strFilePreviewDlg = _T("FilePreview");
const String g_strToolWnd = _T("ToolWindow");
const String g_strWbManager = _T("WbManager");
const String g_strVideoDlg = _T("VideoWindow");
const String g_strAboutDlg = _T("AboutWindow");
const String g_strModalDlg = _T("ModalWindow");
const String g_strNetCfgDlg = _T("NetCfgDlg");
const String g_strUpdateDlg = _T("UpdateWindow");
const String g_strUdiscUpdateDlg = _T("UdiscUpdateWindow");
const String g_strReconnectBox = _T("ReconnectBox");

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
	if (ITPadMsgManager::GetSingletonPtr() == 0) new CTPadMsgManager();

	String strValue = _T("");
	bool bRet = DOCMNGR()->GetDoc(m_strFile, strSkin, strValue);
	CPaintManagerUI::SetResourcePath( bRet ? strValue.c_str() : strDefaultSkin.c_str() );

    //是否自适应分辨率
    bRet = DOCMNGR()->GetDoc(m_strFile, _T("Resolution"), strValue);
    SIZE sizeSrc;
    SIZE sizeDst;
    sizeSrc.cx = 1920;
    sizeSrc.cy = 1200;

    LPTSTR pstr = NULL;
    sizeDst.cx = _tcstol( (LPCTSTR)strValue.c_str(), &pstr, 10);  
    sizeDst.cy = _tcstol(pstr + 1, &pstr, 10);

    if ( (sizeDst.cx != sizeSrc.cx) || (sizeDst.cy != sizeSrc.cy ) )
    {
        CPaintManagerUI::SetSelfAdaption(true);
        CPaintManagerUI::SetAdpResolution( sizeSrc, sizeDst );
    }


	ITPadCommonOp::RegLogics();

	return true;
}


bool CSystem::Launch()
{
	bool bRet;
	bRet = IWindowManager::GetSingletonPtr()->ShowWindow(CSystem::strMainWindow.c_str());	
	if (bRet == true)
	{
        Window* pWnd = WINDOW_MGR_PTR->GetWindow(CSystem::strMainWindow.c_str());
        if ( pWnd != NULL )
        {
            ::SetProp( pWnd->GetHWND(), AfxGetApp()->m_pszAppName, (HANDLE)1 );

            ::SetForegroundWindow( pWnd->GetHWND() );
        }       

		CPaintManagerUI::MessageLoop();
	}
	else
	{
		//PT_LOGEVENT("创建主程序窗口失败\n");
	}
	return false;
}