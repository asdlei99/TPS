#include "StdAfx.h"
#include "filemanager.h"
#include "messageboxlogic.h"
#include "UIDataMgr.h"
#include "filepreview.h"
#include <io.h>
#include "toolwindowlogic.h"
#include "modalwndlogic.h"
#include <dbt.h>
#include <fstream>

template<> CFileManagerLogic* Singleton<CFileManagerLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CFileManagerLogic,CNotifyUIImpl)

	MSG_CREATEWINDOW(_T("FileManagerLayout"), OnCreate)
	MSG_INIWINDOW(_T("FileManagerLayout"), OnInit)
	//MSG_ITEMSELECTD(_T("FileList"), OnFileItemClick)

	MSG_SELECTCHANGE(_T("CheckBoxItemSel"), OnCheckItemSel)

	MSG_CLICK(_T("BtnGroupPath"), OnBtnFilePath)
	MSG_CLICK(_T("lbGroupPath"), OnBtnFilePath)

	MSG_CLICK(_T("FileItemPic"), OnFileItemPicClick)

	MSG_CLICK(_T("BtnAllSel"), OnBtnSelAll)
	MSG_CLICK(_T("BtnNewFolder"), OnBtnNewFolder)
	MSG_CLICK(_T("BtnManager"), OnBtnManager)
	MSG_CLICK(_T("BtnCopy"), OnBtnCopy)
	MSG_CLICK(_T("BtnCut"), OnBtnCut)
	MSG_CLICK(_T("BtnDelete"), OnBtnDelete)
	MSG_CLICK(_T("BtnRename"), OnBtnRename)
	MSG_CLICK(_T("BtnDone"), OnBtnDone)
	MSG_CLICK(_T("BtnPaste"), OnBtnPaste)
	MSG_CLICK(_T("BtnCancel"), OnBtnCancel)

	MSG_CLICK(_T("BtnBack"), OnBtnBack)
	MSG_CLICK(_T("BtnExit"), OnBtnExit)

	MSG_CLICK(_T("BtnCancelDel"), OnBtnCancelDel)
	MSG_CLICK(_T("BtnConfirmDel"), OnBtnConfirmDel)

	MSG_CLICK(_T("BtnSaveFolder"), OnBtnSaveName)
	MSG_CLICK(_T("BtnCancelMakeFolder"), OnBtnCancelMakeFolder)

	MSG_EDITCHANGE(_T("EdtSearch"), OnSearchEditChange)	

	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)

	MSG_LETTERINDEX_CLICK(_T("ListIndex"),OnLetterIndex)
    USER_MSG(WM_DUI_EDITSETFOCUS, OnEditSetFocus)
APP_END_MSG_MAP()

const String CFileManagerLogic::m_strFileListItem = _T("FileListItem");
const String CFileManagerLogic::m_strFileName = _T("FileItemName");
const String CFileManagerLogic::m_strSeachEdit = _T("EdtSearch");
const String CFileManagerLogic::m_strCheckBoxItemSel = _T("CheckBoxItemSel");

static UINT g_nOperatingID = 0;   //更新是否在操作
static UINT g_nTmIsSearch = 0;    //文件管理刷新延时保护

UINT ThreadDoEdit(LPVOID lpParam)
{
	CFileManagerLogic* ptr = (CFileManagerLogic*)lpParam;

	
	CString strCurPath = _T("");
	if(ptr->m_vctPathDirItem.size() != 0)
	{
		vector<TPathDirItem>::iterator iter = ptr->m_vctPathDirItem.begin();
		strCurPath.Format(_T("%s"),iter->strFullPath);
		if ( strCurPath.GetAt( strCurPath.GetLength() -1 ) != '\\' )
		{
			strCurPath += '\\';
		}
	}

	if ( ptr->m_emFileOptType == emFileOptTypeCut)  //cut files
	{        
		ptr->CBCutFiles( strCurPath );
	}
	else if (ptr->m_emFileOptType == emFileOptTypeCpy)
	{
		ptr->CBCopyFiles( strCurPath );
	}
	else if (ptr->m_emFileOptType == emFileOptTypeDel )
	{
		ptr->CBDelFiles();
	}
	else if (ptr->m_emFileOptType == emFileOptTypSearch )
	{
		ptr->CBSearch();
	}

	ptr->SetOperating(false);

	return 0;
}

VOID   CALLBACK   CFileManagerTimer(  HWND   hwnd,   UINT   uMsg, UINT_PTR  idEvent, DWORD   dwTime  )
{   
	if ( idEvent == g_nOperatingID )
	{
		if(CFileManagerLogic::GetSingletonPtr()->IsOperating())
		{
			return;
		}

		::KillTimer( NULL, g_nOperatingID );
		g_nOperatingID = 0;
		CFileManagerLogic::GetSingletonPtr()->UpdateAftOperat();
	}
    else if( idEvent == g_nTmIsSearch )
    {  
        ::KillTimer( NULL, g_nTmIsSearch );
        g_nTmIsSearch = 0;
        CFileManagerLogic::GetSingletonPtr()->m_bIsSearchTimer = false;
    }
}

CFileManagerLogic::CFileManagerLogic(void):m_bIsSelAll(false),m_bInRootDir(true),m_dwTrimCount(0),m_bIsManage(false),
	m_emFileOptType(emFileOptTypeNon),m_emNameEdt(emNameEdtNon),m_bPreview(false),m_pPrePage(NULL),m_pNextPage(NULL),
	m_bSearchEdit(false),m_dwRemDevice(0),m_bInRemoteDir(false),m_bDeviceChange(false),m_bIsOperating(false),m_bIsSearchTimer(false)
{
}

CFileManagerLogic::~CFileManagerLogic(void)
{
}

bool CFileManagerLogic::OnCreate( TNotifyUI& msg )
{
	REG_TPAD_MSG_WND_OB(m_pm->GetPaintWindow());
	return false;
}

bool CFileManagerLogic::OnInit( TNotifyUI& msg )
{
	m_vctRootItem.reserve( 10 );  //for effective
	m_vctFileItem.reserve( 200 );
	m_vctRootItem.clear();

	vector<CString> vctItem;
	vctItem.push_back( _T("share") ); 
	vctItem.push_back( _T("log") );
	vctItem.push_back( _T("configure") );
	vctItem.push_back( _T("snapshot") );

	TFileItem tINIItem;
	int nIndex;
	for ( nIndex = 0; nIndex < vctItem.size(); nIndex++ )
	{
		tINIItem.setNULL();
		GetItemFromIni( tINIItem, vctItem.at(nIndex) );   
		if ( IsShow( vctItem.at(nIndex) ) == false )
		{
			continue;
		}

		CString strPath(tINIItem.achFilePath);
		tINIItem.dwFileCount = ComInterface->GetFolderFilesCount( strPath );

		m_vctRootItem.push_back( tINIItem );

	} 

	vector<TFileItem> vctDiskItem;
	m_dwRemDevice = ComInterface->GetUDiskList( vctDiskItem );   //save removable device count

	m_vctRootItem.insert( m_vctRootItem.end(), vctDiskItem.begin(), vctDiskItem.end());

	vector<TFileItem>::iterator iter = m_vctRootItem.begin();

	for ( int i = 0; i < m_vctRootItem.size(); i++ )
	{
		//int iLen = 2*wcslen(iter->achFilePath);//CString,TCHAR汉字算一个字符，因此不用普通计算长度 
		char chRtn[MAX_PATH] = {0};
		//wcstombs(chRtn,iter->achFilePath,iLen+1);
        strncpy( chRtn, (CT2A)iter->achFilePath, MAX_PATH );

		if ( _access( chRtn, 0 ) == -1 )
		{            
			if ( errno == ENOENT )
			{
				CreateDirectory( iter->achFilePath, NULL );
				//TRACE( "\n[CFileManageLogic::InitWnd] create folder : %s\n", iter->achFilePath );
			}
		}
		iter++;
	}

	m_bInRootDir = true;
	m_pm->DoCase(_T("caseRoot"));
	UpdateFileList();
	
	ToolWindowreSet(false,false);
	m_pPrePage = WINDOW_MGR_PTR->NewWindow( g_strToolWnd.c_str(), g_strToolWnd.c_str(), _T("tpad"), UI_WNDSTYLE_DIALOG, UI_WNDSTYLE_EX_DIALOG, 0, 0, 0 );
    ::SetWindowPos( m_pPrePage->GetHWND(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE);
	ToolWindowreSet(true,false);
	m_pNextPage = WINDOW_MGR_PTR->NewWindow( g_strToolWnd.c_str(), g_strToolWnd.c_str(), _T("tpad"), UI_WNDSTYLE_DIALOG, UI_WNDSTYLE_EX_DIALOG, 0, 0, 0 );
    ::SetWindowPos( m_pNextPage->GetHWND(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE);
	if (m_pPrePage)
	{
		m_pPrePage->ShowWindow(false);
	}
	if (m_pNextPage)
	{
		m_pNextPage->ShowWindow(false);
	}

    UpdateShowTime();
	return true;
}

bool CFileManagerLogic::IsShow( CString& strKey )
{
	TCHAR szUse[MAX_PATH] = { 0 };

	GetPrivateProfileString( strKey,       //section
		CFG_USE, TEXT("0"),        //part
		szUse, sizeof( szUse ), 
		CONFIG_FILE );
	CString str(szUse);
	if ( str == _T("1") )
	{
		return true;
	}
	else
	{
		return false;
	}

}

void CFileManagerLogic::UpdateAftOperat()
{
	m_vctTransItem.clear();
	if (m_bIsManage)
	{
		m_pm->DoCase(_T("caseMngNoSel"));
	}
	
	m_strEditFileFolder = _T("");
	CModalWndLogic::GetSingletonPtr()->CloseModalWnd();

	if(!m_bInRootDir)
	{
		if ( m_bSearchEdit )
		{
			if ( m_emFileOptType == emFileOptTypeCpy)
			{
				ITPadCommonOp::SetControlText( _T(""), m_pm, _T("EdtSearch") );
				m_bSearchEdit = false;
				ITPadCommonOp::ShowControl(false, m_pm, _T("lbNofile"));
				m_vctSearchItem.clear();

				GetFolderFiles(m_vctPathDirItem.at(0).strFullPath, m_vctFileItem);
			}
		}
		else
		{
			GetFolderFiles(m_vctPathDirItem.at(0).strFullPath, m_vctFileItem);
		}

		UpdateFileList();
	}
	else
	{
		if (m_bSearchEdit)
		{
			UpdateFileList();
		}
	}

	m_emFileOptType = emFileOptTypeNon;
}

bool CFileManagerLogic::CBCopyFiles(CString &strCurPath)
{
 	vector<TFileItem>::iterator iter = m_vctTransItem.begin(); 

	CString strDstPath = _T(""); //拷贝目的路径
	CString strDstName = _T(""); //拷贝后显示的名称，用于条目高亮

	for ( ; iter < m_vctTransItem.end(); iter++ )
	{ 
		TFileItem tFileItem = *iter;
		strDstPath.Format(_T("%s%s"),strCurPath,iter->achFileName);
		strDstName.Format(_T("%s"),iter->achFileName);

		BOOL32 bExit = PathFileExists( strDstPath );
		if ( bExit ) 
		{   
			CString strSrcDir = _T("");
			strSrcDir.Format(_T("%s"), iter->achFilePath);
			DWORD dwIndex = strSrcDir.ReverseFind( '\\' );
			if ( dwIndex != strSrcDir.GetLength() )
			{
				dwIndex++;
				strSrcDir.Delete( dwIndex, strSrcDir.GetLength() - dwIndex );  //keep '\\'
			}

			if ( strSrcDir == strCurPath )
			{
				MakeFileName( strDstPath, iter->bIsFolder == TRUE );

				DWORD dwIndex = strDstPath.ReverseFind( '\\' );
				if ( dwIndex == -1 )
				{
					continue;
				}
				strDstName = strDstPath.Right( strDstPath.GetLength() - dwIndex - 1);
			}
			else
			{
				CString strInfo = _T("");
				if ( iter->bIsFolder )
				{
					strInfo.Format( _T("文件夹：%s\r\n有重名文件夹: %s\n是否覆盖？"), strCurPath, iter->achFileName );                 
				}
				else
				{
					strInfo.Format( _T("文件夹：%s\r\n有重名文件: %s\n是否覆盖？"), strCurPath, iter->achFileName );                   
				} 

				int nRet = ShowMessageBox( strInfo, true );  

				if ( nRet != IDOK )
				{   
					continue;
				}

				SetFileAttributes( strDstPath, FILE_ATTRIBUTE_NORMAL );
				if ( iter->bIsFolder )
				{
					//文件夹的目的路径设为strCurPath
					strDstPath = strCurPath;
				}

			} 

		}
		else if ( iter->bIsFolder == TRUE )  //如果文件夹不存在，则 创建
		{   
			BOOL bRet = CreateDirectoryEx( iter->achFilePath, strDstPath, NULL );
			if ( !bRet )
			{
				GetFileErr( strDstPath );
				continue;
			} 

			strDstPath = strCurPath;
		} 


		BOOL32 bRe = TRUE;
		if( iter->bIsFolder )
		{
			CString str;
			str.Format(_T("%s"),iter->achFilePath);
			bRe = FileOprate( strDstPath, str, FO_COPY ); 
		}
		else
		{ 	  	 
			bRe = CopyFile( iter->achFilePath, strDstPath, FALSE ); 
		}

		if ( !bRe )
		{
			GetFileErr( iter->achFilePath );
		}
	}
  	return true;
}

void CFileManagerLogic::CBCutFiles(CString& strCurPath)
{
	CString strDstPath;
	CString strSrcPath;    
	int nRet;

	bool bRe = false;

	vector<TFileItem>::iterator iter = m_vctTransItem.begin();
	for ( ; iter < m_vctTransItem.end(); iter++ )
	{
		strDstPath.Format(_T("%s%s"), strCurPath, iter->achFileName);
		strSrcPath.Format(_T("%s"), iter->achFilePath);

		if (strDstPath == strSrcPath)
		{
			continue;
		}

		CString strSource(strSrcPath);
		strSource += '\0';
		CString strDest(strDstPath);
		strDest += '\0';

		nRet = MoveFileEx( strSource, strDest, MOVEFILE_WRITE_THROUGH | MOVEFILE_COPY_ALLOWED );
		if ( nRet == 0 )
		{
			nRet = GetLastError();
			if ( nRet == ERROR_ALREADY_EXISTS || nRet == ERROR_FILE_EXISTS )
			{
				CString strInfo;
				if (iter->bIsFolder == TRUE )
				{
					strInfo.Format( _T("文件夹：%s\r\n有重名文件夹: %s\n是否覆盖？"), strCurPath, iter->achFileName ); 

				}
				else
				{
					strInfo.Format( _T("文件夹：%s\r\n有重名文件: %s\n是否覆盖？"), strCurPath, iter->achFileName ); 
				}
				nRet = ShowMessageBox( strInfo, true ); 

				if ( nRet == IDOK )
				{    
					if ( iter->bIsFolder )
					{			
						BOOL32 bRe = SetFileAttributesEx( strDstPath, FILE_ATTRIBUTE_NORMAL );
						if ( !bRe )
						{
							return;
						}

						CString str = _T("");
						str.Format(_T("%s"), iter->achFilePath);
						bRe = FileOprate( strCurPath, str, FO_MOVE );

						if ( !bRe )
						{
							GetFileErr( strCurPath );	
						}            
					}
                    else
                    {
                        CString str = _T("");
                        str.Format(_T("%s"), iter->achFilePath);
                        bRe = FileOprate( strCurPath, str, FO_MOVE );

                        if ( !bRe )
                        {
                            GetFileErr( strCurPath );	
                        }   
                    }
				}
			}
			else if ( nRet == ERROR_DISK_FULL )
			{
				ShowMessageBox(_T("磁盘已满"));
				break;
			}
			else if ( nRet== ERROR_ACCESS_DENIED )
			{
				BOOL32 bExit = PathFileExists( strDstPath );
				if ( bExit ) 
				{
					CString strInfo;
					if ( iter->bIsFolder )
					{
						strInfo.Format( _T("文件夹：%s\r\n有重名文件夹: %s\n是否覆盖？"), strCurPath, iter->achFileName );                 
					}
					else
					{
						strInfo.Format( _T("文件夹：%s\r\n有重名文件: %s\n是否覆盖？"), strCurPath, iter->achFileName );                   
					} 

					int nRet = ShowMessageBox( strInfo, true );  

					if ( nRet != IDOK )
					{   
						continue;
					}
				}

				CString str = _T("");
				str.Format(_T("%s"), iter->achFilePath);
				bRe = FileOprate( strCurPath, str, FO_MOVE );

				if ( !bRe )
				{
					GetFileErr( strCurPath );	
				}   
			}
			else if ( nRet == ERROR_FILE_EXISTS )
			{
				ShowMessageBox(_T("文件不存在"));
			}
		}
	}
}

void CFileManagerLogic::CBDelFiles()
{
	vector<TFileItem>::iterator iter = m_vctTransItem.begin();
	for (; iter != m_vctTransItem.end(); iter++)
	{
		BOOL32 bRe  = SetFileAttributesEx( iter->achFilePath, FILE_ATTRIBUTE_NORMAL );
		if ( !bRe )
		{   
			break;
		}
		if ( TRUE == iter->bIsFolder )
		{   

			bool bRet = RecursiveDelete( (LPCTSTR)iter->achFilePath );  
			if (bRet)
			{
				bRe = RemoveDirectory( (LPCTSTR)iter->achFilePath );  
			}
			
			if (!bRe)
			{
				ShowMessageBox(_T("删除文件夹%s失败"),iter->achFileName);
			}
			if (m_bSearchEdit && bRe)
			{
				vector<TFileItem>::iterator iterS = m_vctSearchItem.begin();
				for (; iterS != m_vctSearchItem.end(); iterS++)
				{
					if ( _tcsicmp(iterS->achFilePath ,iter->achFilePath ) == 0 )
					{
						m_vctSearchItem.erase(iterS);
						break;
					}
				}
			}
		}
		else
		{   
			BOOL ret = DeleteFile( (LPCTSTR)iter->achFilePath );
			if ( !ret )
			{
				DWORD deErr = GetFileErr(  (LPCTSTR)iter->achFilePath  );
				if ( ERROR_ACCESS_DENIED != deErr )
				{
					break;
				} 
				ShowMessageBox(_T("删除文件%s失败"),iter->achFileName);
			}
			else
			{
				if (m_bSearchEdit && bRe)
				{
					vector<TFileItem>::iterator iterS = m_vctSearchItem.begin();
					for (; iterS != m_vctSearchItem.end(); iterS++)
					{
						if ( _tcsicmp(iterS->achFilePath ,iter->achFilePath ) == 0 )
						{
							m_vctSearchItem.erase(iterS);
							break;
						}
					}
				}
			}

		}      
	}          
}

void CFileManagerLogic::PageChange(bool bIsPrePage)
{
	int nSize = m_vctImgFileItem.size();
    if ( nSize <= 1 )    
    {
        return;
    }
    
    TFileItem tFileItem;
    for ( int i = 0; i < nSize; i++ )
    {
       if (_tcsicmp( m_tCurtPreviewFile.achFilePath, m_vctImgFileItem.at(i).achFilePath ) == 0 )
       {

			if (bIsPrePage)
			{
				if ( i == 0) 
				{
					tFileItem = m_vctImgFileItem.at( nSize-1 );
				}
				else
				{
					tFileItem = m_vctImgFileItem.at( i-1 );
				}

			}
			else
			{
				if ( i == (nSize-1) )
				{
					tFileItem = m_vctImgFileItem.at( 0 );
				}
				else
				{
					tFileItem = m_vctImgFileItem.at( i+1 );
				}
			}
             
			m_tCurtPreviewFile = tFileItem;
			break;
        }
    }

	APIPreQuit();
	CFilePreviewLogic::GetSingletonPtr()->SetFilePath(tFileItem.achFilePath);
	CString strPath(tFileItem.achFilePath);
	if (!m_bInRemoteDir)
	{
		strPath = strPath.Right(strPath.GetLength() - strPath.Find(':')-2);
	}
	
	ITPadCommonOp::SetControlText(strPath, m_pm, _T("lbTitleName"));
}

	

//make a name that does not exist in the folder
bool CFileManagerLogic::MakeFileName( CString& strPath, bool bfolder )
{
	BOOL    bFind;
	DWORD i = 0;
	CString strBk;
	CString strtemp =_T("-copy");

	DWORD dwCount;
	do 
	{
		strBk = strPath;
		if ( bfolder == false )
		{
			dwCount = strBk.ReverseFind( '.' );   
		}
		else
		{
			dwCount = strBk.GetLength( );
		}

		if ( i != 0 )
		{
			strtemp.Format( _T("-copy(%d)"), i );
		}
		strBk.Insert(dwCount, strtemp );
		CFileFind finder;
		bFind = finder.FindFile( (LPCTSTR)strBk );
		i++;
	} while ( bFind == TRUE );

	strPath = strBk;

	return true;
}

bool CFileManagerLogic::OnBtnBack(TNotifyUI& msg)
{
	if (m_bPreview)
	{
		m_bPreview = false;
		WINDOW_MGR_PTR->ShowWindow( g_strFilePreviewDlg.c_str(), false );
		APIPreQuit();

		if (m_pPrePage)
		{
			m_pPrePage->ShowWindow(false);
		}
		if (m_pNextPage)
		{
			m_pNextPage->ShowWindow(false);
		}

		ITPadCommonOp::SetControlText(_T("文件管理"), m_pm, _T("lbTitleName"));
	}
	else
	{
		if (!m_bInRootDir)
		{
			m_bInRootDir = true;
			m_pm->DoCase(_T("caseRoot"));

            ITPadCommonOp::SetControlText( _T(""), m_pm, _T("EdtSearch") );
			m_bSearchEdit = false;
            ITPadCommonOp::ShowControl(false, m_pm, _T("lbNofile"));
			m_vctSearchItem.clear();
			if ( m_bIsSelAll )
			{
				m_bIsSelAll = false;
				ITPadCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnAllSel"));
			}
			UpdateFileList();
			m_bInRemoteDir = false;
			m_bDeviceChange = false;
			
			if (m_emFileOptType != emFileOptTypeNon)
			{
				m_pm->DoCase(_T("caseMngEdit"));
			}
			else
			{
				if (m_bIsManage)
				{
					m_bIsManage = false;
				}
				if (m_vctTransItem.size()>0)
				{
					m_vctTransItem.clear();
				}
			}

			m_strRootSelItemPath = _T("");
			m_vctPathDirItem.clear();
		}
		else
		{
			WINDOW_MGR_PTR->ShowWindowFromLeftToRight( g_strFilemanagerDlg.c_str(), false );
		}
	}

	return NO_ERROR;
}

bool CFileManagerLogic::OnBtnExit(TNotifyUI& msg)
{
	if (m_bPreview)
	{
		m_bPreview = false;
		WINDOW_MGR_PTR->ShowWindow( g_strFilePreviewDlg.c_str(), false );
		APIPreQuit();

		if (m_pPrePage)
		{
			m_pPrePage->ShowWindow(false);
		}
		if (m_pNextPage)
		{
			m_pNextPage->ShowWindow(false);
		}

		ITPadCommonOp::SetControlText(_T("文件管理"), m_pm, _T("lbTitleName"));
	}

	if (!m_bInRootDir)
	{
		m_bInRootDir = true;
		m_pm->DoCase(_T("caseRoot"));

        ITPadCommonOp::SetControlText( _T(""), m_pm, _T("EdtSearch") );
		m_bSearchEdit = false;
        ITPadCommonOp::ShowControl(false, m_pm, _T("lbNofile"));
		m_vctSearchItem.clear();
		if ( m_bIsSelAll )
		{
			m_bIsSelAll = false;
			ITPadCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnAllSel"));
		}
		UpdateFileList();
		m_bInRemoteDir = false;
		m_bDeviceChange = false;

		if (m_emFileOptType != emFileOptTypeNon)
		{
			m_pm->DoCase(_T("caseMngEdit"));
		}
		else
		{
			if (m_bIsManage)
			{
				m_bIsManage = false;
			}
			if (m_vctTransItem.size()>0)
			{
				m_vctTransItem.clear();
			}
		}

		m_strRootSelItemPath = _T("");
		m_vctPathDirItem.clear();
	}

	WINDOW_MGR_PTR->ShowWindowFromLeftToRight( g_strFilemanagerDlg.c_str(), false );
	return true;
}

bool CFileManagerLogic::FileOprate(CString& strDst, CString& strSrc, UINT uOprFunType)
{
	bool bRe = true;  

	CString strSource(strSrc);
	strSource += '\0';
	CString strDest(strDst);
	strDest += '\0';

	SHFILEOPSTRUCT FileOp={0};
	FileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR // 不出现确认对话框 | 需要时直接创建一个文件夹,不需确定
		| FOF_NOERRORUI | FOF_SILENT;               // 不提示错误信息 | 不显示进度框
	FileOp.pFrom = strSource;
	FileOp.pTo = strDest;
	FileOp.wFunc = uOprFunType ;//FO_COPY;  
	FileOp.fAnyOperationsAborted = FALSE;

	int nRet = SHFileOperation(&FileOp);
	if ( FileOp.fAnyOperationsAborted )
	{
		bRe = false;
	}
	else if ( ERROR_SUCCESS != nRet )  
	{    
		CString strError = _T("");
		DWORD err = GetLastError();
		//strError.Format("\n[CFileManageLogic::FileOprate]rerturn %d  getlastErr=%d===========\n", nRet,err);
		//AfxOutputDebugString(strError); 

		switch (nRet)
		{     
		case ERROR_DEV_NOT_EXIST:  //device is no longer available
		case 0x402://在试图移动或拷贝一个不存在的文件时，出现这个文件系统错。一般地，它提示了，源缓冲中的某些东西应该修改一下。这个错误码弹出一个的错误框，你可以通过设置FOF_NOERRORUI标志抑制它的显示。
			//case 0x7C:
		case ERROR_FILE_NOT_FOUND://如果你试图重命名多重文件，这个消息就会出现。描述是相当直接的：系统不能找到指定的文件,win7上正在操作u盘时，拔掉u盘会返回该错误码
			strError = _T("系统找不到指定的目录");
			break;
		case 0x7C: //win7中磁盘满会返回124
			strError = _T("磁盘空间已满");
			break;
		} 	 

		bRe = false;
		if (!strError.IsEmpty())
		{
			ShowMessageBox(strError);
		}
	}

	return bRe;
}

void CFileManagerLogic::UpdateFileList()
{
	m_vctShowFileList.clear();
	if ( m_bSearchEdit )
	{
		m_vctShowFileList = m_vctSearchItem;
		if (m_bInRootDir && m_vctSearchItem.size()>0)
		{
			ITPadCommonOp::ShowControl(true, m_pm, _T("BtnManager"));
		}
	}
	else
	{
		if (m_bInRootDir)
		{
			m_vctShowFileList = m_vctRootItem;
		}
		else
		{
			if (m_bInRemoteDir && m_bDeviceChange)
			{
				//在移动设备中进行文件管理，此设备是否仍在用
				bool bIsStill = false;
				vector<TFileItem>::iterator iter = m_vctRootItem.begin();
				for (  ; iter < m_vctRootItem.end(); iter++ )
				{
					CString str(iter->achFilePath);
					if (str == m_strRootSelItemPath)
					{
						bIsStill = true;
						break;
					}
				}

				if (!bIsStill)//移动设备拔出
				{
					if (m_emFileOptType != emFileOptTypeNon)
					{
						m_emFileOptType = emFileOptTypeNon;
						m_vctTransItem.clear();
					}

					TNotifyUI msg;
					OnBtnBack(msg);
					return;
				}
			}

			m_vctShowFileList = m_vctFileItem;
		}
    }
	UpdateShowFileList();
}

void CFileManagerLogic::UpdateShowFileList()
{
    for(std::vector<TFileItem>::iterator it = m_vctShowFileList.begin() ; it != m_vctShowFileList.end(); )
    {
        if (true != (bool)PathFileExists(it->achFilePath) )
        {
            it = m_vctShowFileList.erase(it);
        }
        else
        {
            it ++;
        }
    }

	sort( m_vctShowFileList.begin(), m_vctShowFileList.end(), CUIDataMgr::FileMgrCompare );

	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ITPadCommonOp::FindControl( m_pm, _T("FileList") );
	if ( pTileLayoutUI == NULL )
	{
		return;
	}
	pTileLayoutUI->RemoveAll();
	m_vctImgFileItem.clear();
	for ( int i = 0; i < m_vctShowFileList.size(); i++ )
	{
		CListContainerElementUI *pListContainer = 
			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( m_strFileListItem.c_str() );

		ITPadCommonOp::SetControlText( m_vctShowFileList.at(i).achFileName, m_pm, m_strFileName.c_str(), pListContainer );

		if (m_bInRootDir)
		{
			if (m_vctShowFileList.at(i).em_DeviceType == emDevice_Udisk)
			{
				ITPadCommonOp::SetControlBkImg(_T("res/list/imgUdisc.png"), m_pm, _T("FileItemPic"), pListContainer);
			}
			else if (m_vctShowFileList.at(i).em_DeviceType == emDevice_HDD)
			{
				ITPadCommonOp::SetControlBkImg(_T("res/list/imgHardware.png"), m_pm, _T("FileItemPic"), pListContainer);
			}
			else if (m_vctShowFileList.at(i).bIsFolder)
			{
				ITPadCommonOp::SetControlBkImg(_T("res/list/imgFolder.png"), m_pm, _T("FileItemPic"), pListContainer);
			}
			else
			{
				ITPadCommonOp::SetControlBkImg(_T("res/list/imgFile.png"), m_pm, _T("FileItemPic"), pListContainer);
			}
		}
		else
		{
			if (m_vctShowFileList.at(i).bIsFolder)
			{
				ITPadCommonOp::SetControlBkImg(_T("res/list/imgFolder.png"), m_pm, _T("FileItemPic"), pListContainer);
			}
			else
			{
				ITPadCommonOp::SetControlBkImg(_T("res/list/imgFile.png"), m_pm, _T("FileItemPic"), pListContainer);
			}
		}

		if (!m_bIsManage || (m_bInRootDir && !m_bSearchEdit))
		{
			ITPadCommonOp::ShowControl(false, m_pm, _T("CheckBoxItemSel"), pListContainer);
		}
		else
		{
			CCheckBoxUI* pCheckBoxItemSel = (CCheckBoxUI*)ITPadCommonOp::FindControl( m_pm, _T("CheckBoxItemSel"), pListContainer);

			if ( pCheckBoxItemSel )
			{
				pCheckBoxItemSel->SetTag( (UINT_PTR)&m_vctShowFileList.at(i));		
			}
		}

		CButtonUI* pbutton = (CButtonUI*)ITPadCommonOp::FindControl( m_pm, _T("FileItemPic"), pListContainer);
		if ( pbutton )
		{
			pbutton->SetTag( (UINT_PTR)&m_vctShowFileList.at(i));		
		}

		pTileLayoutUI->Add(pListContainer);

		if ( m_vctShowFileList.at(i).em_fileType == emFileType_image )
		{
			m_vctImgFileItem.push_back( m_vctShowFileList.at(i) );
		}
	}

	if ( m_bIsSelAll )
	{
		m_bIsSelAll = false;
		ITPadCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnAllSel"));
	}
	
}

void CFileManagerLogic::UpdateNavigation(CString strFolderPath)
{
	int dwindex = 0;
	CString strFullPath = strFolderPath;
	m_vctPathDirItem.clear();

	while( TRUE )
	{
		int index = strFullPath.ReverseFind('\\');
		TPathDirItem tInfo;
		tInfo.strFullPath = strFullPath;
		CString strName = strFullPath.Right( strFullPath.GetLength() - 1 - index );
		if ( strName.IsEmpty() ) 
		{
			if (!m_bInRemoteDir)
			{
				break;
			}	
			else
			{
				strFullPath = strFullPath.Left( index );  
				continue;
			}
		}

		tInfo.strName = strName;

		TFontInfo* tFontInfo = m_pm->GetFontInfo(1);
		HFONT hfont = m_pm->GetFont(1);
		Graphics graphics(m_pm->GetPaintWindow());

		RectF rectString;

		StringFormat strFormat;
		strFormat.SetAlignment( StringAlignmentCenter );
		strFormat.SetLineAlignment(StringAlignmentCenter);

		Gdiplus::Font font(m_pm->GetPaintDC(),hfont);  
		graphics.MeasureString( strName, -1, &font, RectF(0,0,0,0), &strFormat, &rectString );

		CRect rc;
		rc.right = rc.left + rectString.Width + 7 ;

		tInfo.nItemLenth = BTN_WIDTH + (rc.right);

		m_vctPathDirItem.push_back( tInfo );
		strFullPath = strFullPath.Left( index );    
		if ( ++index <= m_dwTrimCount )
		{
			break;
		}
	};

	CHorizontalLayoutUI *pHLayoutUI = (CHorizontalLayoutUI*)ITPadCommonOp::FindControl( m_pm, _T("naviList") );
	if ( pHLayoutUI == NULL )
	{
		return;
	}
	pHLayoutUI->RemoveAll();
	for ( int i = m_vctPathDirItem.size() -1 ; i >= 0 ; i-- )
	{
		CHorizontalLayoutUI *pListContainer = 
			(CHorizontalLayoutUI*)CONTROLFACTORY()->GetControl( _T("NaviItem") );

		if (!pListContainer)
		{
			return;
		}

		if (i == 0)
		{
			ITPadCommonOp::ShowControl(false, m_pm, _T("lbCut"), pListContainer);
			m_vctPathDirItem.at(i).nItemLenth = m_vctPathDirItem.at(i).nItemLenth - 25;
		}

		pListContainer->SetFixedWidth(m_vctPathDirItem.at(i).nItemLenth);
		ITPadCommonOp::SetControlText( m_vctPathDirItem.at(i).strName, m_pm, _T("lbGroupPath"), pListContainer );
		
		CButtonUI* pBtn = (CButtonUI*)ITPadCommonOp::FindControl(m_pm, _T("BtnGroupPath"), pListContainer);
		if (pBtn)
		{
			pBtn->SetTag(i);//对应m_vctPathDirItem位置
		}
		CButtonUI* pBtnlb = (CButtonUI*)ITPadCommonOp::FindControl(m_pm, _T("lbGroupPath"), pListContainer);
		if (pBtnlb)
		{
			pBtnlb->SetTag(i);//对应m_vctPathDirItem位置
		}

		pHLayoutUI->Add(pListContainer);
	}

}

DWORD CFileManagerLogic::GetFolderFiles(CString strFolderPath, vector<TFileItem>& tListFileInfo)
{
	DWORD count = 0;  
	tListFileInfo.clear();

	if( strFolderPath.IsEmpty() == TRUE )
	{
		return count;
	}

	u16 wIndex = strFolderPath.ReverseFind( _T('\\') );
	if ( wIndex == strFolderPath.GetLength()-1 )
	{
		strFolderPath.Delete(wIndex, 1);
	}
	//保存路径
	wstring sFolderPath = strFolderPath +  _T("\\");
	strFolderPath +=  _T("\\*.*");

	TFileItem titemtemp;
	titemtemp.setNULL(); 
	//MFC遍历方式改为WIN32遍历方式(尝试文件乱码的Bug修改)
// 	WIN32_FIND_DATA ffd;
// 	HANDLE hFind = FindFirstFile(strFolderPath, &ffd);
// 	m_vctImgFileItem.clear();
// 	while(FindNextFile(hFind, &ffd))
// 	{
// 		if (wcscmp(ffd.cFileName, L"..") == 0 || wcscmp(ffd.cFileName, L".") == 0)
// 		{
// 			continue;
// 		}
// 		else
// 		{
// 			wcsncpy_s( titemtemp.achFilePath, (sFolderPath + ffd.cFileName).c_str(), MAX_PATH );
// 			if ( ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
// 			{
// 				titemtemp.bIsFolder = TRUE;
// 				titemtemp.dwFileCount = ComInterface->GetFolderFilesCount( titemtemp.achFilePath );   
// 			}
// 			else
// 			{   
// 				titemtemp.bIsFolder = FALSE;
// 			}
// 
// 			wcsncpy_s( titemtemp.achFileName, ffd.cFileName, MAX_PATH );
// 
//             if (true != (bool)PathFileExists(titemtemp.achFilePath) )
//             {
//                 continue;;
//             }
// 
// 			wstring strName = ffd.cFileName;
// 			int ipos = strName.rfind('.') + 1;
// 			int index = strName.length() - strName.rfind('.') - 1;
// 			wstring strSuf = strName.substr( ipos, index);
// 			if ( strSuf.compare(_T("bmp")) == 0 || strSuf.compare(_T("jpg")) == 0 || strSuf.compare(_T("png")) == 0 || strSuf.compare(_T("gif")) == 0)
// 			{
// 				titemtemp.em_fileType = emFileType_image;
// 			}
// 			else if ( strSuf.compare(_T("pdf")) == 0 )
// 			{
// 				titemtemp.em_fileType  = emFileType_pdf;
// 			}
// 			else if ( strSuf.compare(_T("ppt")) == 0 || strSuf.compare(_T("pptx")) == 0 )
// 			{
// 				titemtemp.em_fileType  = emFileType_ppt;
// 			}
// 			else if ( strSuf.compare(_T("txt")) == 0 )
// 			{
// 				titemtemp.em_fileType  = emFileType_txt;
// 			}
// 			else if ( strSuf.compare(_T("doc")) == 0 || strSuf.compare(_T("docx")) == 0 )
// 			{
// 				titemtemp.em_fileType  = emFileType_doc;
// 			}
// 			else if ( strSuf.compare(_T("xls")) == 0 || strSuf.compare(_T("xlsx")) == 0 )
// 			{
// 				titemtemp.em_fileType  = emFileType_xls;
// 			}
// 			else
// 			{
// 				titemtemp.em_fileType  = emFileType_unknown;
// 			}
// 
// 			tListFileInfo.push_back( titemtemp );
// 
// 			if ( titemtemp.em_fileType == emFileType_image )
// 			{
// 				m_vctImgFileItem.push_back( titemtemp );
// 			}
// 
// 			titemtemp.setNULL();
// 			count++;
// 		}
// 	}
// 	FindClose(hFind);

	CFileFind finder;
	BOOL bWorking = finder.FindFile( strFolderPath );
	if ( bWorking == 0 )
	{
		return count;
	}
	m_vctImgFileItem.clear();
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if ( finder.IsDots() || finder.IsHidden() )
		{
			continue;
		}

		CString strPath(finder.GetFilePath());
		//memcpy(titemtemp.achFilePath, strPath, strPath.GetLength()*2);
        wcsncpy_s( titemtemp.achFilePath, (LPCTSTR)strPath, MAX_PATH );

		if ( finder.IsDirectory() )
		{          
			if (!PathIsDirectory(titemtemp.achFilePath))
			{
				continue;
			}

			titemtemp.bIsFolder = TRUE;
			titemtemp.dwFileCount = ComInterface->GetFolderFilesCount( strPath );   
		}
		else
		{   
			ifstream file(CT2A(titemtemp.achFilePath));
			if (!file)
			{
				continue;
			}
			file.close();

			titemtemp.bIsFolder = FALSE;
		}
 
		CString strName(finder.GetFileName());
		//int dwSize = strName.GetLength();
		//memcpy(titemtemp.achFileName, strName, dwSize*2);
        wcsncpy_s( titemtemp.achFileName, (LPCTSTR)strName, MAX_PATH );

		int index = strName.GetLength() - strName.ReverseFind('.') - 1;
		CString strSuf = strName.Right( index );
		if ( strSuf.Compare(_T("bmp")) == 0 || strSuf.Compare(_T("jpg")) == 0 || strSuf.Compare(_T("png")) == 0 || strSuf.Compare(_T("gif")) == 0)
		{
			titemtemp.em_fileType = emFileType_image;
		}
		else if ( strSuf.Compare(_T("pdf")) == 0 )
		{
			titemtemp.em_fileType  = emFileType_pdf;
		}
		else if ( strSuf.Compare(_T("ppt")) == 0 || strSuf.Compare(_T("pptx")) == 0 )
		{
			titemtemp.em_fileType  = emFileType_ppt;
		}
 		else if ( strSuf.Compare(_T("txt")) == 0 )
 		{
 			titemtemp.em_fileType  = emFileType_txt;
 		}
		else if ( strSuf.Compare(_T("doc")) == 0 || strSuf.Compare(_T("docx")) == 0 )
		{
			titemtemp.em_fileType  = emFileType_doc;
		}
		else if ( strSuf.Compare(_T("xls")) == 0 || strSuf.Compare(_T("xlsx")) == 0 )
		{
			titemtemp.em_fileType  = emFileType_xls;
		}
		else
		{
			titemtemp.em_fileType  = emFileType_unknown;
		}

		tListFileInfo.push_back( titemtemp );

		if ( titemtemp.em_fileType == emFileType_image )
		{
			m_vctImgFileItem.push_back( titemtemp );
		}

		titemtemp.setNULL();
		count++;
	}

	finder.Close();

	return count;
}

bool CFileManagerLogic::OnFileItemClick( TNotifyUI& msg )
{
	int dwIndex = msg.wParam;
	int dwoldIndex = msg.lParam;
	TFileItem tFileItem = m_vctShowFileList.at(dwIndex);

	if ( tFileItem.bIsFolder)
	{
		if (m_bInRootDir)
		{
			m_bInRootDir = FALSE;
			m_pm->DoCase(_T("caseNoMng"));
			m_strRootSelItemPath.Format(_T("%s"),tFileItem.achFilePath);
		}

		if ( m_strRootSelItemPath.GetLength() > 3 )
		{
			m_dwTrimCount = m_strRootSelItemPath.ReverseFind('\\');
			m_dwTrimCount++;
		}
		else
		{
			m_dwTrimCount = 0;
		}

		GetFolderFiles(tFileItem.achFilePath, m_vctFileItem);
		//进去目录 搜索自动去掉
		if (m_bSearchEdit)
		{
			ITPadCommonOp::SetControlText( _T(""), m_pm, _T("EdtSearch") );
			m_bSearchEdit = false;
			ITPadCommonOp::ShowControl(false, m_pm, _T("lbNofile"));
			m_vctSearchItem.clear();
		}
		UpdateNavigation(tFileItem.achFilePath);
		UpdateFileList();
	}
	else
	{
		CTouchListUI *pTileLayoutUI = (CTouchListUI*)ITPadCommonOp::FindControl( m_pm, _T("FileList") );
		if (pTileLayoutUI)
		{
			pTileLayoutUI->SelectItem(-1);
		}

		CFilePreviewLogic::GetSingletonPtr()->SetFilePath(tFileItem.achFilePath);
		WINDOW_MGR_PTR->ShowWindow( g_strFilePreviewDlg.c_str(), true );
		m_bPreview = true;
	}

	return false;
}

bool CFileManagerLogic::OnBtnFilePath(TNotifyUI& msg)
{
    if(m_bIsSearchTimer)
    {
        return false;
    }
    m_bIsSearchTimer = true;//延时保护
    g_nTmIsSearch = SetTimer( NULL, 0, 1000, CFileManagerTimer ); 

	int nIndex = msg.pSender->GetTag();
	CString strPath(m_vctPathDirItem.at(nIndex).strFullPath);
	GetFolderFiles(strPath, m_vctFileItem);
	//进去目录 搜索自动去掉
	if (m_bSearchEdit)
	{
		ITPadCommonOp::SetControlText( _T(""), m_pm, _T("EdtSearch") );
		m_bSearchEdit = false;
        ITPadCommonOp::ShowControl(false, m_pm, _T("lbNofile"));
		m_vctSearchItem.clear();
	}
	UpdateNavigation(strPath);
	UpdateFileList();

	return true;
}

bool CFileManagerLogic::OnFileItemPicClick(TNotifyUI& msg)
{
    CButtonUI* pButton = dynamic_cast<CButtonUI*>(msg.pSender);
    if (!pButton)
    {
        return false;
    }
    TFileItem* pFileItem = (TFileItem*)pButton->GetTag();
    if (!pFileItem)
    {
        return false;
    }
    TFileItem tFileItem = *pFileItem;
	//TFileItem tFileItem = *(TFileItem*)msg.pSender->GetTag();
	if ( tFileItem.bIsFolder)
	{
		if (m_bInRootDir)
		{
			if (m_bSearchEdit)
			{
				vector<TFileItem>::iterator iter = m_vctRootItem.begin();
				for (  ; iter < m_vctRootItem.end(); iter++ )
				{
					CString strFolder(tFileItem.achFilePath);
					CString strDir(iter->achFilePath);
					if ( strFolder.Find(strDir) != -1)
					{
						m_strRootSelItemPath.Format(_T("%s"),iter->achFilePath);
						break;
					}
				}
			}
			else
			{
				m_strRootSelItemPath.Format(_T("%s"),tFileItem.achFilePath);
			}

			if (m_emFileOptType != emFileOptTypeNon )
			{
				m_pm->DoCase(_T("caseMngEdit"));
				m_pm->DoCase(_T("caseRoot2Dir"));//显示非根目录应该显示的项目
			}

			m_bInRootDir = false;
			if (!m_bIsManage)
			{
				m_pm->DoCase(_T("caseNoMng"));
			}
			
		}

		if ( m_strRootSelItemPath.GetLength() > 3 )
		{
			m_dwTrimCount = m_strRootSelItemPath.ReverseFind('\\');
			m_dwTrimCount++;
		}
		else
		{
			m_dwTrimCount = 0;
		}

		GetFolderFiles(tFileItem.achFilePath, m_vctFileItem);
		//进去目录 搜索自动去掉
		if (m_bSearchEdit)
		{
			ITPadCommonOp::SetControlText( _T(""), m_pm, _T("EdtSearch") );
			m_bSearchEdit = false;
			m_vctSearchItem.clear();
		}
		if( tFileItem.em_DeviceType != emDevice_No)
		{
			m_bInRemoteDir = true;
			m_bDeviceChange = false;//设备插拔在进入移动设备后进行判断
		}
		UpdateNavigation(tFileItem.achFilePath);
		UpdateFileList();
	}
	else
	{
		if ( tFileItem.em_fileType == emFileType_unknown)
		{
			return true;
		}

		CTouchListUI *pTileLayoutUI = (CTouchListUI*)ITPadCommonOp::FindControl( m_pm, _T("FileList") );
		if (pTileLayoutUI)
		{
			pTileLayoutUI->SelectItem(-1);
		}

		msg.pSender->SetEnabled(false);
		CFilePreviewLogic::GetSingletonPtr()->SetFilePath(tFileItem.achFilePath);
		//WINDOW_MGR_PTR->ShowWindowFromBottomToTop(g_strFilePreviewDlg.c_str(), true );
		WINDOW_MGR_PTR->ShowWindow(g_strFilePreviewDlg.c_str(), true );
		CFilePreviewLogic::GetSingletonPtr()->WindowPosSet(0, 0, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE);

		msg.pSender->SetEnabled(true);
		m_bPreview = true;

		if (IsImgFile(tFileItem.achFilePath) && (m_vctImgFileItem.size() > 1) )
		{
			m_tCurtPreviewFile = tFileItem;
			if (m_pPrePage)
			{
				m_pPrePage->ShowWindow(true);
			}
			if (m_pNextPage)
			{
				m_pNextPage->ShowWindow(true);
			}
		}

		CString strPath(tFileItem.achFilePath);
		if (!m_bInRemoteDir)
		{
			strPath = strPath.Right(strPath.GetLength() - strPath.Find(':')-2);
		}		
		
		ITPadCommonOp::SetControlText(strPath, m_pm, _T("lbTitleName"));
	}

	return true;
}

bool CFileManagerLogic::IsImgFile( LPCTSTR szFile )
{
	TCHAR*pExtern = StrRChr( szFile, NULL, _T('.') ); 

	const CString strImgTytpe;
	const_cast<CString&>(strImgTytpe) = _T(".bmp.jpg.jpeg.png.gif.svg.tiff.emf.dib");
	if(  NULL != pExtern  && StrStr( (LPCTSTR)strImgTytpe,pExtern) != NULL  )
	{
		return TRUE;
	}

	return FALSE; 
}

bool CFileManagerLogic::OnBtnNewFolder(TNotifyUI& msg)
{
	ITPadCommonOp::SetControlText(_T("新建文件夹"), m_pm, _T("lbTitle"));
	ITPadCommonOp::ShowControl(true, m_pm, _T("EdNewFolder"));
	ITPadCommonOp::SetControlText(_T(""), m_pm, _T("EdNewFolder"));
	ITPadCommonOp::ShowControl(true, m_pm, _T("PageNewFolder"));
	m_emNameEdt = emNameEdtNewFolder;
	m_vctTransItem.clear();
	return true;
}


bool CFileManagerLogic::OnBtnSaveName(TNotifyUI& msg)
{
	String strEdNewName = ITPadCommonOp::GetControlText( m_pm, _T("EdNewFolder") );
    if (strEdNewName.empty())
    {
		ShowMessageBox(_T("文件名不能为空"));
		return false;
    }
    if (!UIDATAMGR->IsValidFolderStr(strEdNewName))
    {
        CString str; 
        str.Format( _T("文件夹名不能包含括号中任何字符 [ %s ]"), INVALID_ALIAS_FOR_FLODER );
        ShowMessageBox( str );
        return false;
    }

	CString strCurPath = _T("");
	if (m_vctPathDirItem.size() != 0)
	{
		strCurPath = m_vctPathDirItem[0].strFullPath;
	}

	if (m_emNameEdt == emNameEdtNewFolder)
	{
		
		CString strDstPath = strCurPath + "\\" + strEdNewName.c_str();
		//   判断路径是否存在   
		if ( PathIsDirectory( strDstPath ) )   
		{   
			CString strInfo;
			strInfo.Format( _T("有重名文件夹，覆盖将删除原文件夹及其内部所有文件，是否覆盖？"));

			int nRet = ShowMessageBox( strInfo, true );             
			if ( nRet == IDOK )
			{  
				//覆盖原文件夹 要先删除原文件夹及里面的所有内容 才能新建成功 Bug00181587 dyy 2014-5-5
				if ( RecursiveDelete( (LPCTSTR)strDstPath ) )
				{
					RemoveDirectory( (LPCTSTR)strDstPath ); 
				}
			}
			else
			{
				return FALSE;
			}
		}

		if ( !CreateDirectory( strDstPath, NULL ) )   
		{
			CString strInfo;
			strInfo.Format(_T("创建文件夹%s失败！"), strEdNewName.c_str());   
			ShowMessageBox( strInfo ); 
			return FALSE;
		}    
	}
	else if ( m_emNameEdt == emNameEdtReName )
	{
		CString strNewName; //新名称
		BOOL bRe = FALSE;
		vector<TFileItem>::iterator iter;
		iter = m_vctTransItem.begin();
		for (; iter != m_vctTransItem.end();)
		{

			CString strPath(iter->achFilePath);
			CString strName(iter->achFileName);

			CString strPrefix = strPath.Left( strPath.ReverseFind('\\') + 1 );

			if ( iter->bIsFolder )
			{
				strNewName = strPrefix + strEdNewName.c_str();
			}
			else
			{
				int index = strPath.GetLength() - strPath.ReverseFind('.');
				CString strSuf = strPath.Right( index );
				strNewName = strPrefix + strEdNewName.c_str() + strSuf;  
			}

			if ( strPath != strNewName ) //只处理重命名与原来名称不同的文件
			{
				BOOL32 bExit = PathFileExists( strNewName );
				if ( bExit ) 
				{
					CString strInfo;
					strInfo.Format( _T("有重名文件%s，是否自动重命名？"),strEdNewName.c_str());  
					BOOL bRet  = ShowMessageBox(strInfo, true);
					if ( bRet == IDOK )
					{   
						//MakeFileName( strNewName, iter->bIsFolder );
						while ( bExit ) 
						{
							MakeFileName( strNewName, iter->bIsFolder );
							bExit = PathFileExists( strNewName );
						}
					}
					else
					{
						iter++;
						continue;
					}
				}

				SetFileAttributes( strPath, FILE_ATTRIBUTE_NORMAL );

				bRe = FileOprate( strNewName, strPath, FO_RENAME );
				if ( bRe )
				{
					CString strName = strNewName.Right( strNewName.GetLength() - strNewName.ReverseFind('\\') -1 );
					//memcpy(iter->achFileName,strName,strName.GetLength()*2);                   
					//memcpy(iter->achFilePath,strNewName,strNewName.GetLength()*2);
                    wcsncpy_s( iter->achFileName, (LPCTSTR)strName, MAX_PATH );
                    wcsncpy_s( iter->achFilePath, (LPCTSTR)strNewName, MAX_PATH );
				}
				else
				{
					GetFileErr( strPath );					
				}
			}    

			iter++;
		}

	}

	m_vctTransItem.clear();
	if (m_bIsManage)
	{
		m_pm->DoCase(_T("caseMngNoSel"));
	}
	
	if (m_bInRootDir)//根目录重命名后 重新搜索
	{
		m_vctSearchItem.clear();
		vector<TFileItem>::iterator iter = m_vctRootItem.begin();
		for (  ; iter < m_vctRootItem.end(); iter++ )
		{
			SearchItem( iter->achFilePath );
		}

		if (m_vctSearchItem.size() == 0)
		{
			ITPadCommonOp::ShowControl(true, m_pm, _T("lbNofile"));
		}
	}
	else
	{
		GetFolderFiles(strCurPath, m_vctFileItem);
		if (m_bSearchEdit)//重命名后，回到搜索时的目录，去掉搜索
		{
			ITPadCommonOp::SetControlText( _T(""), m_pm, _T("EdtSearch") );
			m_bSearchEdit = false;
			m_vctSearchItem.clear();
		}
	}

	ITPadCommonOp::ShowControl(false, m_pm, _T("PageNewFolder"));
	UpdateFileList();

	return true;
}

bool CFileManagerLogic::OnBtnCancelMakeFolder(TNotifyUI& msg)
{
	ITPadCommonOp::SetControlText(_T(""), m_pm, _T("EdNewFolder"));
	ITPadCommonOp::ShowControl(false, m_pm, _T("PageNewFolder"));
	return true;
}

bool CFileManagerLogic::OnBtnManager(TNotifyUI& msg)
{
	m_bIsManage = true;
	UpdateShowFileList();
	if (m_bIsManage)
	{
		m_pm->DoCase(_T("caseMngNoSel"));
	}

	return true;
}

bool CFileManagerLogic::OnBtnCopy(TNotifyUI& msg)
{
	m_pm->DoCase(_T("caseMngEdit"));
	m_emFileOptType = emFileOptTypeCpy;
	if (!m_bInRootDir)
	{
		m_strEditFileFolder = m_vctPathDirItem.at(0).strFullPath;
	}

	return true;
}

bool CFileManagerLogic::OnBtnCut(TNotifyUI& msg)
{
	m_pm->DoCase(_T("caseMngEdit"));
	m_emFileOptType = emFileOptTypeCut;
	if (!m_bInRootDir)
	{
		m_strEditFileFolder = m_vctPathDirItem.at(0).strFullPath;
	}

	return true;
}

bool CFileManagerLogic::OnBtnDelete(TNotifyUI& msg)
{
	m_emFileOptType = emFileOptTypeDel;
	int nRet = ShowMessageBox( _T("是否删除所选文件"), true );  
	if ( nRet == IDOK )
	{   
		OnBtnConfirmDel(msg);
	}
	else
	{
		OnBtnCancelDel(msg);
	}	
	
	return true;
}


bool CFileManagerLogic::OnBtnRename(TNotifyUI& msg)
{
	ITPadCommonOp::SetControlText(_T("重命名"), m_pm, _T("lbTitle"));
	ITPadCommonOp::ShowControl(true, m_pm, _T("EdNewFolder"));

    //文件名不显示后缀名
    CString strName(m_vctTransItem.at(0).achFileName);
    int index = strName.ReverseFind('.');
    CString strFileName = strName.Left( index );
	ITPadCommonOp::SetControlText(strFileName, m_pm, _T("EdNewFolder"));

	ITPadCommonOp::ShowControl(true, m_pm, _T("PageNewFolder"));
	m_emNameEdt = emNameEdtReName;

	return true;
}

bool CFileManagerLogic::OnBtnConfirmDel(TNotifyUI& msg)
{
	m_bIsOperating = true;
	AfxBeginThread( ThreadDoEdit, this ); 
	g_nOperatingID = SetTimer( NULL, 0, 200, CFileManagerTimer );

	CModalWndLogic::GetSingletonPtr()->ShowModalWnd( _T("正在处理，请稍后 ... ...") );

	return true;
}

bool CFileManagerLogic::OnBtnCancelDel( TNotifyUI& msg )
{
	m_vctTransItem.clear();
	if (m_bIsManage)
	{
		m_pm->DoCase(_T("caseMngNoSel"));
	}
	m_emFileOptType = emFileOptTypeNon;

	GetFolderFiles(m_vctPathDirItem.at(0).strFullPath, m_vctFileItem);
	UpdateFileList();
	return true;
}

bool CFileManagerLogic::OnBtnDone(TNotifyUI& msg)
{
	m_bIsManage = false;
	if ( m_bIsSelAll )
	{
		m_bIsSelAll = false;
		ITPadCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnAllSel"));
	}
	m_vctTransItem.clear();
	UpdateShowFileList();

	if (m_bInRootDir && m_bSearchEdit)
	{
		m_pm->DoCase(_T("caseRoot"));
		ITPadCommonOp::ShowControl(true, m_pm, _T("BtnManager"));
	}
	else
	{
		m_pm->DoCase(_T("caseNoMng"));
	}

	return true;
}

bool CFileManagerLogic::OnBtnPaste(TNotifyUI& msg)
{
	if (m_bInRootDir)
	{
		ShowMessageBox(_T("请选择要粘贴的目录位置"));
		return false;
	}

	m_bIsOperating = true;
	AfxBeginThread( ThreadDoEdit, this ); 
	g_nOperatingID = SetTimer( NULL, 0, 200, CFileManagerTimer );
	CModalWndLogic::GetSingletonPtr()->ShowModalWnd( _T("正在处理，请稍后 ... ...") );

	return true;
}

bool CFileManagerLogic::OnBtnCancel(TNotifyUI& msg)
{
	m_vctTransItem.clear();
	GetFolderFiles(m_strEditFileFolder, m_vctFileItem);
	m_emFileOptType = emFileOptTypeNon;
	//取消操作，不再搜索
	if (m_bSearchEdit)
	{
		ITPadCommonOp::SetControlText( _T(""), m_pm, _T("EdtSearch") );
		m_bSearchEdit = false;
		m_vctSearchItem.clear();
	}

	if (m_bInRootDir)
	{
		ITPadCommonOp::ShowControl(false, m_pm, _T("BtnPaste"));
		ITPadCommonOp::ShowControl(false, m_pm, _T("BtnCancel"));
		m_bIsManage = false;
	}
	else
	{
		if (m_strEditFileFolder.IsEmpty())
		{
			TNotifyUI msg;
			OnBtnBack(msg);
			return true;
		}
		
		UpdateNavigation(m_strEditFileFolder);
		m_pm->DoCase(_T("caseMngNoSel"));
		
	}

	UpdateFileList();

	return true;
}

bool CFileManagerLogic::OnBtnSelAll( TNotifyUI& msg )
{
	CTouchListUI *pTileLayoutUI = (CTouchListUI*)ITPadCommonOp::FindControl( m_pm, _T("FileList") );
	if ( pTileLayoutUI == NULL )
	{
		return false;
	}
	m_bIsSelAll = !m_bIsSelAll;
	if ( m_bIsSelAll )
	{
		ITPadCommonOp::SetControlText(_T("取消全选"),m_pm,_T("BtnAllSel"));
		for ( int i = 0; i <  pTileLayoutUI->GetCount(); i++ )
		{		
			CListContainerElementUI *pListContainer = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(i);
			CCheckBoxUI* pCheckBoxItemSel = (CCheckBoxUI*)ITPadCommonOp::FindControl( m_pm, _T("CheckBoxItemSel"), pListContainer);

			if ( pCheckBoxItemSel && !pCheckBoxItemSel->GetCheck())
			{
				pCheckBoxItemSel->SetCheck(true);
			}
		}
	}
	else
	{
		ITPadCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnAllSel"));
		for ( int i = 0; i <  pTileLayoutUI->GetCount(); i++ )
		{		
			CListContainerElementUI *pListContainer = (CListContainerElementUI*)pTileLayoutUI->GetItemAt(i);
			CCheckBoxUI* pCheckBoxItemSel = (CCheckBoxUI*)ITPadCommonOp::FindControl( m_pm, _T("CheckBoxItemSel"), pListContainer);

			if ( pCheckBoxItemSel )
			{
				pCheckBoxItemSel->SetCheck(false);
			}

		}
	}

	return true;
}

bool CFileManagerLogic::OnSearchEditChange( TNotifyUI& msg )
{
	m_vctSearchItem.clear();
	if (m_bIsManage && !m_bInRootDir)
	{
		m_pm->DoCase(_T("caseMngNoSel"));
	}

	ITPadCommonOp::ShowControl(false, m_pm, _T("lbNofile"));

	String strSearchName = ITPadCommonOp::GetControlText( m_pm, m_strSeachEdit.c_str() );
	if (strSearchName.empty())
	{
		if (m_emFileOptType == emFileOptTypeNon)
		{
			m_vctTransItem.clear();//若进行了文件操作，则清空搜索时不清空已选
		}
		m_bSearchEdit = false;
		if (m_bInRootDir)
		{
			m_pm->DoCase(_T("caseRoot"));
			if ( m_emFileOptType != emFileOptTypeNon )
			{
				m_pm->DoCase(_T("caseMngEdit"));
			}
		}
		else
		{
			GetFolderFiles(m_vctPathDirItem.at(0).strFullPath, m_vctFileItem);
		}
		
		UpdateFileList();
		return true;
	}

	m_vctTransItem.clear();
	m_bSearchEdit = true;

//取消搜索线程 因为若搜索单词 会进入editchenge多次 造成搜索结果变多
// 	m_bIsOperating = true;
// 	m_emFileOptType = emFileOptTypSearch;
// 	AfxBeginThread( ThreadDoEdit, this ); 
// 	g_nOperatingID = SetTimer( NULL, 0, 200, CFileManagerTimer );
// 	CModalWndLogic::GetSingletonPtr()->ShowModalWnd( _T("正在搜索，请稍后 ... ...") );

	if (m_bInRootDir)
	{
		vector<TFileItem>::iterator iter = m_vctRootItem.begin();
		for (  ; iter < m_vctRootItem.end(); iter++ )
		{
			SearchItem( iter->achFilePath );
		}
	}
	else
	{
		CString strPath = m_vctPathDirItem.at(0).strFullPath;
		TCHAR szSearch[MAX_PATH] = {0};
		_tcsncpy(szSearch, strPath, MAX_PATH);

		SearchItem( szSearch );
	}

	if (m_vctSearchItem.size() == 0)
	{
		ITPadCommonOp::ShowControl(true, m_pm, _T("lbNofile"));
	}

	UpdateFileList();
	return true;
}

bool CFileManagerLogic::CBSearch()
{
	if (m_bInRootDir)
	{
		vector<TFileItem>::iterator iter = m_vctRootItem.begin();
		for (  ; iter < m_vctRootItem.end(); iter++ )
		{
			SearchItem( iter->achFilePath );
		}
	}
	else
	{
		CString strPath = m_vctPathDirItem.at(0).strFullPath;
		TCHAR szSearch[MAX_PATH] = {0};
		_tcsncpy(szSearch, strPath, MAX_PATH);

		SearchItem( szSearch );
	}

	if (m_vctSearchItem.size() == 0)
	{
		ITPadCommonOp::ShowControl(true, m_pm, _T("lbNofile"));
	}

	return true;
}

void CFileManagerLogic::SearchItem(TCHAR * lpPath )
{
	TCHAR szFind[MAX_PATH];
	WIN32_FIND_DATA FindFileData;
	_tcsncpy(szFind,lpPath,MAX_PATH);
	_tcscat(szFind, _T("\\*.*"));
	HANDLE hFind=::FindFirstFile( szFind, &FindFileData );

	if( INVALID_HANDLE_VALUE == hFind )
	{
		return;
	}

	while( TRUE )
	{
// 		if( FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) //是文件夹就进入进行遍历
// 		{
// 
// 			if( FindFileData.cFileName[0] != '.' )           
// 			{
// 				TCHAR szFile[MAX_PATH];
// 				_tcsncpy( szFile, lpPath, MAX_PATH );
// 				_tcscat( szFile , _T("\\") );
// 				_tcscat( szFile, FindFileData.cFileName ); 
// 				SearchItem(szFile);
// 			}
// 			else
// 			{
// 				if( !FindNextFile( hFind, &FindFileData ) )
// 				{
// 					break;
// 				}
// 				else
// 				{
// 					continue;
// 				}
// 			}
// 		} 

		u32 dw1 = FindFileData.dwFileAttributes;

		CString strItemName;
		strItemName.Format(_T("%s"), FindFileData.cFileName);
		CString strItemPath;
		strItemPath.Format( _T("%s\\%s"), lpPath, strItemName);
		BOOL bFind = FALSE;		
		String strSearchName = ITPadCommonOp::GetControlText( m_pm, m_strSeachEdit.c_str() );
		bFind = UIDATAMGR->HZPYMatchList( strSearchName.c_str(), strItemName );
		if ( bFind )
		{	
			TFileItem tFileItem; 
			_tcsncpy(tFileItem.achFilePath,strItemPath,MAX_PATH);
			_tcsncpy(tFileItem.achFileName,strItemName,MAX_PATH);

			tFileItem.dwFileCount = ComInterface->GetFolderFilesCount( strItemPath );
			if( FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				tFileItem.bIsFolder = TRUE;
			}

			//tFileItem.bSel = FALSE;//选中状态针对当前界面，筛选后选中状态清空

			int index = strItemName.GetLength() - strItemName.ReverseFind('.') - 1;
			CString strSuf = strItemName.Right( index );
			if ( strSuf.Compare(_T("bmp")) == 0 || strSuf.Compare(_T("jpg")) == 0 || strSuf.Compare(_T("png")) == 0 || strSuf.Compare(_T("gif")) == 0)
			{
				tFileItem.em_fileType = emFileType_image;
			}
			else if ( strSuf.Compare(_T("pdf")) == 0 )
			{
				tFileItem.em_fileType = emFileType_pdf;
			}
			else if ( strSuf.Compare(_T("ppt")) == 0 || strSuf.Compare(_T("pptx")) == 0 )
			{
				tFileItem.em_fileType = emFileType_ppt;
			}
 			else if ( strSuf.Compare(_T("txt")) == 0 )
 			{
 				tFileItem.em_fileType = emFileType_txt;
 			}
			else if ( strSuf.Compare(_T("doc")) == 0 || strSuf.Compare(_T("docx")) == 0 )
			{
				tFileItem.em_fileType = emFileType_doc;
			}
			else if ( strSuf.Compare(_T("xls")) == 0 || strSuf.Compare(_T("xlsx")) == 0 )
			{
				tFileItem.em_fileType = emFileType_xls;
			}
			else
			{
				tFileItem.em_fileType = emFileType_unknown;
			}

			m_vctSearchItem.push_back( tFileItem );
		}

		if( !FindNextFile( hFind, &FindFileData ) )
			break;
	}

	FindClose(hFind);
}

LRESULT CFileManagerLogic::OnDongleChange( WPARAM wParam, LPARAM lParam )
{
	switch(wParam)
	{
	case DBT_DEVICEARRIVAL:           // 设备检测结束，并且可以使用
	//case DBT_DEVNODES_CHANGED:
		m_bDeviceChange = true;
		RebuildUdiskList();
		UpdateFileList();
		break;
	case DBT_DEVICEREMOVECOMPLETE:   //设备卸载或者拔出 
		{   
			PDEV_BROADCAST_HDR lpdb=(PDEV_BROADCAST_HDR)lParam;
			CString strDisk = _T("");
			if( lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME )//逻辑卷
			{
				PDEV_BROADCAST_VOLUME lpdbv =  (PDEV_BROADCAST_VOLUME)lpdb;
				if(lpdbv->dbcv_flags==0) //U盘
				{                                         
					char szPath[] = "x:\\";
					szPath[0] = FirstDriveFromMask( lpdbv ->dbcv_unitmask );
					strDisk.Format(_T("%s"),szPath);
				} 
			}

			m_bDeviceChange = true;
			RebuildUdiskList();
			UpdateFileList( );
		}

		break;
	}

	return NO_ERROR; 

}

void CFileManagerLogic::UpdateShowTime()
{
	SYSTEMTIME systime;
	GetLocalTime( &systime );

	CString strDate = _T("");
	strDate.Format(_T("%d-%d-%d"),systime.wYear,systime.wMonth,systime.wDay);
	CString strTime = _T("");
	CString strHour = _T("");
	CString strMinute = _T("");
	if (systime.wHour < 10)
	{
		strHour.Format(_T("0%d"),systime.wHour);
	}
	else
	{
		strHour.Format(_T("%d"),systime.wHour);
	}

	if (systime.wMinute < 10)
	{
		strMinute.Format(_T(":0%d"),systime.wMinute);
	}
	else
	{
		strMinute.Format(_T(":%d"),systime.wMinute);
	}
	strTime = strHour + strMinute;
	String 	strlbDate = ITPadCommonOp::GetControlText(m_pm,_T("lbDate"));
	CString strOriDate(strlbDate.c_str());
	if ( strOriDate != strDate)
	{
		ITPadCommonOp::SetControlText(strDate, m_pm, _T("lbDate"));
	}

	ITPadCommonOp::SetControlText(strTime, m_pm, _T("lbTime"));
}

char CFileManagerLogic::FirstDriveFromMask( ULONG unitmask )
{
	char i;

	for (i = 0; i < 26; ++i)
	{
		if (unitmask & 0x1)
			break;
		unitmask = unitmask >> 1;
	}

	return( i + 'A' );
}

void CFileManagerLogic::RebuildUdiskList()
{
	while ( m_dwRemDevice > 0 )
	{
		m_vctRootItem.pop_back();
		m_dwRemDevice--;
	}    

	vector<TFileItem> vctDiskItem;
	m_dwRemDevice = ComInterface->GetUDiskList( vctDiskItem );  
	m_vctRootItem.insert( m_vctRootItem.end(), vctDiskItem.begin(), vctDiskItem.end());

}

bool CFileManagerLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	m_bSearchEdit = false;
	ITPadCommonOp::SetControlText(_T(""),  m_pm, m_strSeachEdit.c_str());
		
	m_vctShowFileList.clear();
	m_vctSearchItem.clear();
	m_vctFileItem.clear();
	m_vctTransItem.clear();
	m_vctImgFileItem.clear();
	m_vctPathDirItem.clear();
	m_tCurtPreviewFile.setNULL();
	ITPadCommonOp::ShowControl(false, m_pm, _T("lbNofile"));

	if ( m_bIsSelAll )
	{
		m_bIsSelAll = false;
		ITPadCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnAllSel"));
	}

	if (m_bPreview)
	{
		m_bPreview = false;
		WINDOW_MGR_PTR->ShowWindow( g_strFilePreviewDlg.c_str(), false );
		APIPreQuit();

		if (m_pPrePage)
		{
			m_pPrePage->ShowWindow(false);
		}
		if (m_pNextPage)
		{
			m_pNextPage->ShowWindow(false);
		}

		ITPadCommonOp::SetControlText(_T("文件管理"), m_pm, _T("lbTitleName"));
	}

	m_bInRootDir = true;
	m_bInRemoteDir = false;
	m_bIsManage = false;
	m_strRootSelItemPath = _T("");
	m_strEditFileFolder = _T("");
	m_emNameEdt = emNameEdtNon;
	m_emFileOptType = emFileOptTypeNon;
	m_bDeviceChange = false;
    m_bIsSearchTimer = false;
	m_pm->DoCase(_T("caseRoot"));
	UpdateFileList();
	ITPadCommonOp::ShowControl(false, m_pm, _T("PageNewFolder"));
	WINDOW_MGR_PTR->ShowWindow( g_strFilemanagerDlg.c_str(), false );

	return true;
}

bool CFileManagerLogic::OnLetterIndex( TNotifyUI& msg )
{
	int nLetterIndex = (int)msg.wParam;
	CTouchListUI* pTouch = (CTouchListUI*)ITPadCommonOp::FindControl(m_pm, _T("FileList"));
	if (!pTouch)
	{
		return false;
	}

	if (nLetterIndex == 0)
	{
		pTouch->ScrollToIndexLetter(0);
		return true;
	}

	CString strIndex;
	nLetterIndex = 'A' + nLetterIndex -1;
	strIndex.Format( _T("%c"), (char)nLetterIndex );
	int nYOffset = 0;
	int nItemCount = m_vctShowFileList.size();

	//解决条目过多时，点击字母会卡的问题 ，使用二分法
	int swLowIndex = 0;
	int swHighIndex = nItemCount;
	int swMidIndex = 0;   //置当前查找区间上、下界的初值 

	while( swLowIndex < swHighIndex )
	{   
		int nMidIndex = swMidIndex;
		//当前查找区间R[low..high]非空 
		swMidIndex =( swLowIndex + swHighIndex )/2; 
		if ( nMidIndex == swMidIndex )
		{
			break;
		}

		CString strLetter = _T("");
		int iLen = 2*wcslen(m_vctShowFileList.at(swMidIndex).achFileName);//CString,TCHAR汉字算一个字符，因此不用普通计算长度 
		char chRtn[MAX_PATH] = {0};
		wcstombs(chRtn,m_vctShowFileList.at(swMidIndex).achFileName,iLen+1);

		UIDATAMGR->GetFirstLetter( chRtn, strLetter );
		
		int nRe = strIndex.Compare( strLetter );
		if(  nRe == 0 )  
		{        
			break;   
		} 
		else if ( nRe < 0 )
		{   
			swHighIndex = swMidIndex;  //当前查找区间R[low..mid]  
		}
		else
		{   
			swLowIndex = swMidIndex + 1;//当前查找区间R[mid..heith] 
		}						 

	} 

	//swLowIndex与swHighIndex相等时，跟swMidIndex比较
	if ( swLowIndex == swHighIndex )
	{
		if ( swMidIndex < swHighIndex )
		{
			swHighIndex = swMidIndex;
		}
		else
		{
			swLowIndex = swMidIndex;
		}
	}

	//取swLowIndex和swHighIndex中第一个比strIndex大的返回
	if ( swLowIndex > swHighIndex )
	{
		CString strLetter = _T("");
		int iLen = 2*wcslen(m_vctShowFileList.at(swMidIndex).achFileName);//CString,TCHAR汉字算一个字符，因此不用普通计算长度 
		char chRtn[MAX_PATH] = {0};
		wcstombs(chRtn,m_vctShowFileList.at(swMidIndex).achFileName,iLen+1);

		UIDATAMGR->GetFirstLetter( chRtn, strLetter ); 


		int nRe = strIndex.Compare( strLetter );
		if( nRe > 0 )		 
		{
			swMidIndex = swLowIndex;
		}
		else
		{
			swMidIndex = swHighIndex;
		}

	}

	pTouch->ScrollToIndexLetter(swMidIndex);

	return true;
}

bool CFileManagerLogic::OnCheckItemSel(TNotifyUI& msg)
{
	TFileItem tFileItem = *(TFileItem*)msg.pSender->GetTag();
	CCheckBoxUI* pCheckBox = (CCheckBoxUI*)msg.pSender;
	if ( !pCheckBox )
	{
		return false;
	}

	if ( pCheckBox->GetCheck() )
	{
		m_vctTransItem.push_back(tFileItem);
		if (m_vctTransItem.size() == m_vctShowFileList.size())
		{
			m_bIsSelAll = true;
			ITPadCommonOp::SetControlText(_T("取消全选"),m_pm,_T("BtnAllSel"));
		}
	}
	else
	{	

		vector<TFileItem>::iterator iter = m_vctTransItem.begin();
		while( iter != m_vctTransItem.end() )
		{			
			if (  0 == _tcscmp( &(*iter->achFilePath), tFileItem.achFilePath )  )
			{
				m_vctTransItem.erase(iter);
				break;
			}		
			iter++;
		}
		if ( m_bIsSelAll )
		{
			m_bIsSelAll = false;
			ITPadCommonOp::SetControlText(_T("全 选"),m_pm,_T("BtnAllSel"));
		}
	}

	if (m_vctTransItem.size() == 0)
	{
		if (m_bIsManage)
		{
			m_pm->DoCase(_T("caseMngNoSel"));
		}
	}
	else
	{
		m_pm->DoCase(_T("caseMngSel"));
	}

	return NO_ERROR;
}

void CFileManagerLogic::GetItemFromIni( TFileItem& tKeyItem, CString strKey )
{
	TCHAR szReadName[MAX_PATH + 1] = { 0 };
	TCHAR szReadPath[MAX_PATH + 1] = { 0 };	

	GetPrivateProfileString( strKey,       //section
		CFG_NAME, TEXT("ERROR"),        //part
		szReadName, sizeof(szReadName), 
		CONFIG_FILE );

	GetPrivateProfileString( strKey,       //section
		CFG_PATH, TEXT("ERROR"),        //part
		szReadPath, sizeof(szReadPath), 
		CONFIG_FILE );

	tKeyItem.bIsFolder = TRUE;
	memcpy(tKeyItem.achFileName,szReadName,sizeof(szReadName));
	memcpy(tKeyItem.achFilePath,szReadPath,sizeof(szReadPath));
}

bool CFileManagerLogic::RecursiveDelete(CString strPath)
{
	CFileFind filefinder;   

	if(strPath.Right(1) != _T("\\"))
	{
		strPath += _T("\\");
	}    
	strPath += _T("*.*");

	BOOL bRet = filefinder.FindFile(strPath);

	while(bRet)
	{
		bRet = filefinder.FindNextFile();

		strPath = filefinder.GetFilePath();

		BOOL32 bRe = SetFileAttributesEx(strPath, FILE_ATTRIBUTE_NORMAL);

		if ( !filefinder.IsDirectory() )  //delete file
		{
			BOOL re = DeleteFile( strPath );
			if ( !re )
			{
				DWORD dwErr = GetFileErr( strPath );
				if ( ERROR_ACCESS_DENIED == dwErr )
				{
					return false;
				}

			}
		}
		else if ( !filefinder.IsDots() && filefinder.IsDirectory() ) //delete folder
		{
			RecursiveDelete( strPath ); 
			RemoveDirectory( strPath );                     
		}
	}

	return TRUE;
}

BOOL32 CFileManagerLogic::SetFileAttributesEx( LPCWSTR lpFileName, DWORD dwFileAttributes )
{
	BOOL32 bSetSuc = SetFileAttributes( lpFileName, dwFileAttributes );
	if ( !bSetSuc )
	{
		GetFileErr( lpFileName );
	}

	return bSetSuc;
}

//处理文件失败,0 表示无失败，若有失败，会在该函数中 提示
DWORD CFileManagerLogic::GetFileErr(  LPCWSTR lpFileName )
{
	DWORD dwErr = GetLastError();
	CString strErr = _T("");
	//strErr.Format(_T("\n[CFileManageLogic::CBCopyFiles] SetFileAttributes fail ,err = %d \n"),dwErr);
	switch(dwErr)
	{
	case ERROR_FILE_NOT_FOUND:
		strErr = _T("系统找不到指定的文件");
		break;
	case ERROR_DEV_NOT_EXIST:
	case ERROR_PATH_NOT_FOUND: 
		strErr = _T("系统找不到指定的目录");
		break;
	case ERROR_TOO_MANY_OPEN_FILES: 
	case ERROR_OPEN_FAILED:
		strErr.Format(_T("打开文件(%s)失败"),lpFileName); 
		break;
	case ERROR_ACCESS_DENIED: 
		strErr.Format(_T("访问文件(%s)失败"),lpFileName);
		break; 
	case ERROR_FILE_EXISTS:
		strErr.Format(_T("文件(%s)已存在"),lpFileName);
		break;
	case ERROR_ALREADY_EXISTS:
		strErr.Format(_T("目录(%s)已存在"),lpFileName);
		break;
	case ERROR_DISK_FULL:
		strErr = _T("磁盘空间已满");
		break;

	default:
		//AfxOutputDebugString( strErr );  
		break;
	}

	if (!strErr.IsEmpty())
	{
		ShowMessageBox(strErr);
	}	
	return dwErr;
}

bool CFileManagerLogic::OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle)
{
    ComInterface->ShowKeyboard();
    return true;
}