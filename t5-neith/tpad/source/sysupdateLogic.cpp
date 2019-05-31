#include "StdAfx.h"
#include "sysupdateLogic.h"

#define CFG_UPDATE          _T("Update")
#define UPDATE_FILE			_T("updatetpad\\UpdateConfig.ini")

//系统升级线程
UINT ThreadSysUpdate(LPVOID lpParam)
{   
	BOOL bOK = CSysUpdateLogic::GetSingleton().SysUpdate();
	NOTIFY_MSG( UI_TPAD_SYSUPDATE_OVER, bOK, 0 );

	return NO_ERROR;
} 

template<> CSysUpdateLogic* Singleton<CSysUpdateLogic>::ms_pSingleton  = NULL;
APP_BEGIN_MSG_MAP(CSysUpdateLogic, CNotifyUIImpl)

	MSG_CREATEWINDOW(_T("UdiscUpdateLayout"), OnCreate)
	MSG_INIWINDOW(_T("UdiscUpdateLayout"), OnInit)
	MSG_WINDOWDESTORY(_T("UdiscUpdateLayout"), OnDestroy)

	USER_MSG(UI_CNS_DISCONNECTED,OnDisconnect)
	USER_MSG(UI_TPAD_SYSUPDATE_OVER,OnSysUpdateOver)

	MSG_CLICK(_T("BtnOk"), OnBtnOk)
	MSG_CLICK(_T("BtnCancel"), OnBtnCancel)

APP_END_MSG_MAP()

static CString m_strVer = _T("");
static CString m_strOriVer = _T("");

bool showUdisUpdateDlg(LPCTSTR lpstrVer, LPCTSTR lpstrOriVer)
{
	m_strVer = lpstrVer;
	m_strOriVer = lpstrOriVer;
	WINDOW_MGR_PTR->ShowModal( g_strUdiscUpdateDlg.c_str() );

	return true;
}

CSysUpdateLogic::CSysUpdateLogic( void )
{
}


CSysUpdateLogic::~CSysUpdateLogic(void)
{
}


void CSysUpdateLogic::CloseUdiscUpWnd()
{
	WINDOW_MGR_PTR->CloseWindow(g_strUdiscUpdateDlg.c_str(),IDOK);
	CSysUpdateLogic::RemoveInstance();
}

bool CSysUpdateLogic::OnCreate( TNotifyUI& msg )
{
	REG_TPAD_MSG_WND_OB(m_pm->GetPaintWindow());

	s32 nTop = 0;
	RECT rcParent;
	HWND hparent = GetParent(m_pm->GetPaintWindow());
	GetWindowRect(hparent,&rcParent);
	SIZE szDlg = m_pm->GetInitSize();
	s32 nLeft = (rcParent.right - rcParent.left - szDlg.cx)/2;
	nTop = (rcParent.bottom - rcParent.top - szDlg.cy)/2;
	if ( CPaintManagerUI::IsSelfAdaption() )
	{
		float fAdpX, fAdpY;
		CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
		nTop = s32(nTop * fAdpY);
		nLeft = s32(nLeft * fAdpY);
	}
	//SetWindowPos( m_pm->GetPaintWindow(), HWND_TOPMOST, nLeft, nTop, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );
	 ::SetWindowPos( m_pm->GetPaintWindow(), HWND_TOPMOST, nLeft, nTop, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOACTIVATE);
	return false;
}

bool CSysUpdateLogic::OnInit(TNotifyUI& msg)
{
	CString cstrPath = GetModuleFullPath();
	cstrPath = cstrPath.Left( cstrPath.ReverseFind('\\') );
	m_strUpdatePath = cstrPath.Left( cstrPath.ReverseFind('\\') + 1);

	BOOL bHaveUDisk = FALSE;
	BOOL bExist = ComInterface->GetFirstUDiskNameByFileName( m_strUDiskName, _T("updatetpad\\UpdateConfig.ini"), bHaveUDisk );	
	
	m_emCopyState = emCopyNo;
	
	CString strTip;
	int numCheckReturn = wcscmp(m_strVer,m_strOriVer);
	if (0 == numCheckReturn)
	{
		strTip.Format(_T("系统检测已是最新版本%s,请确认是否修复?"),m_strOriVer);
		ITPadCommonOp::SetControlText( _T("立即修复"), m_pm, _T("BtnOk") );
	}
	else if (0 > numCheckReturn)
	{
		strTip.Format(_T("系统检测到版本%s,请确认是否回退此版本?"),m_strVer);
		ITPadCommonOp::SetControlText( _T("立即回退"), m_pm, _T("BtnOk") );
	}
	else
	{
		strTip.Format(_T("系统检测到新版本%s,请确认是否升级?"),m_strVer);
	}

	ITPadCommonOp::SetControlText( strTip, m_pm, _T("LabelTip") );
	return true;
}

bool CSysUpdateLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_strUDiskName.Empty();
	m_emCopyState = emCopyNo;

	WINDOW_MGR_PTR->CloseWindow(g_strUdiscUpdateDlg.c_str(), IDCANCEL);
	CSysUpdateLogic::RemoveInstance();
	return NO_ERROR;
}

bool CSysUpdateLogic::OnDestroy( TNotifyUI& msg )
{
	UNREG_TPAD_MSG_WND_OB(m_pm->GetPaintWindow());
	//CSysUpdateLogic::RemoveInstance();
	return true;
}


bool CSysUpdateLogic::OnBtnOk(TNotifyUI& msg)
{
	if (m_emCopyState == emCopyNo)
	{
		UpdateNow();
	}
	
	if (m_emCopyState == emCopyEnd)
	{
		ComInterface->ExitWindowsOS( emReboot );
	}

	if (m_emCopyState == emCopyFail)
	{
		OnBtnCancel(msg);
	}

	return true;
}


bool CSysUpdateLogic::OnBtnCancel(TNotifyUI& msg)
{
	m_pm->DoCase(_T("caseNoCopy"));
	m_emCopyState = emCopyNo;
	WINDOW_MGR_PTR->CloseWindow(g_strUdiscUpdateDlg.c_str(), IDCANCEL);
	CSysUpdateLogic::RemoveInstance();
	return true;
}

bool CSysUpdateLogic::UpdateNow()
{	
	m_pm->DoCase(_T("caseUpdate"));

	//将升级标志置为0
	CString strUpdateFile = m_strUpdatePath + UPDATE_FILE;
	WritePrivateProfileString( CFG_UPDATE, CFG_UPDATE, TEXT("0"), strUpdateFile );

	//开启系统升级线程
	AfxBeginThread( ThreadSysUpdate, NULL );
// 	BOOL bOK = SysUpdate();
// 	NOTIFY_MSG( UI_TPAD_SYSUPDATE_OVER, bOK, 0 );

	return true;
}

bool CSysUpdateLogic::SysUpdate()
{
	CString strFileFrom = m_strUDiskName + _T("updatetpad");
	CString strFileTo = m_strUpdatePath  ;//"C:\\Program Files (x86)\\Kedacom";

	BOOL bExist = ComInterface->ExistDir( strFileTo );	
	if ( !bExist )
	{
		//不存在则创建
		ComInterface->CreateDir( strFileTo );
	}

	BOOL bOK = CopyFiles( strFileTo, strFileFrom );

	return bOK;
}

BOOL CSysUpdateLogic::CopyFiles( CString& strDst, CString& strSrc )
{
	CString strSource(strSrc);
	strSource += '\0';
	CString strDest(strDst);
	strDest += '\0';

	SHFILEOPSTRUCT FileOp={0};
	FileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR // 不出现确认对话框 | 需要时直接创建一个文件夹,不需确定
		| FOF_NOERRORUI | FOF_SILENT;               // 不提示错误信息 | 不显示进度框
	FileOp.pFrom = strSource;
	FileOp.pTo = strDest;
	FileOp.wFunc = FO_COPY;
	int nRe = SHFileOperation(&FileOp);
	if (ERROR_SUCCESS != nRe )
	{
		DWORD err = GetLastError();
		//strError.Format("\n[CFileManageLogic::FileOprate]rerturn %d  getlastErr=%d===========\n", nRet,err);
		//AfxOutputDebugString(strError); 

		switch (nRe)
		{     
		case ERROR_DEV_NOT_EXIST:  //device is no longer available
		case 0x402://在试图移动或拷贝一个不存在的文件时，出现这个文件系统错。一般地，它提示了，源缓冲中的某些东西应该修改一下。这个错误码弹出一个的错误框，你可以通过设置FOF_NOERRORUI标志抑制它的显示。
			//case 0x7C:
		case ERROR_FILE_NOT_FOUND://如果你试图重命名多重文件，这个消息就会出现。描述是相当直接的：系统不能找到指定的文件,win7上正在操作u盘时，拔掉u盘会返回该错误码
			//strError = _T("系统找不到指定的目录");
			break;
		case 0x7C: //win7中磁盘满会返回124
			//strError = _T("磁盘空间已满");
			break;
		} 
	}
	return nRe == 0;   
}

bool CSysUpdateLogic::OnSysUpdateOver( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	CString strUpdateFile = m_strUpdatePath + UPDATE_FILE;

	BOOL bOk = (BOOL)wParam;
	if ( bOk )
	{
		m_emCopyState = emCopyEnd;
		WritePrivateProfileString( CFG_UPDATE, CFG_UPDATE, TEXT("1"), strUpdateFile );
		m_pm->DoCase(_T("caseCopyEnd"));
	}
	else
	{
		m_emCopyState = emCopyFail;
		WritePrivateProfileString( CFG_UPDATE, CFG_UPDATE, TEXT("0"), strUpdateFile );
		m_pm->DoCase(_T("caseCopyFail"));
	}	

	return NO_ERROR;
}