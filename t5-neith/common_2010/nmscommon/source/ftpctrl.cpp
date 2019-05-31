/*=============================================================================
模   块   名: 网管公用模块库
文   件   名: ftpctrl.cpp
相 关  文 件: ftpctrl.h
文件实现功能: FTP上传下载控制
作        者: 王昊
版        本: V4.0  Copyright(C) 2003-2005 KDC, All rights reserved.
说        明: 需要使用MFC, 使用者需要包含wininet.lib库
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2005/09/29  4.0     王昊        创建
2012/07/18	4.7		邹俊龙		修正FTP端口值设置无效问题
								把获取文件大小过程移到线程中，防止界面卡死
								修正某些情况下连接服务器失败时，未通知外部
								新增emFtpConnect状态及事件
								新增emFtpWarning事件，非致命错误时，向外部发送警告消息而非emFtpEnd
								新增CFtpCtrlMsgDeal，允许外部通过继承该类的方式，接收Ftp消息
								下载上传文件时，不再有HWnd参数，而是提供接口在一开始设置
								新增删除文件函数
=============================================================================*/
#include "stdafx.h"
#include "ftpctrl.h"
#include "unicode.h"

#ifndef INTERNET_STATUS_USER_INPUT_REQUIRED
#define INTERNET_STATUS_USER_INPUT_REQUIRED	0x00000040
#endif

#define INTERNET_STATUS_DETECTING_PROXY			80

#define FTP_FILE_ASCII_COUNT    (s32)11
LPCTSTR g_pszAsciiFileExt[FTP_FILE_ASCII_COUNT] =
{
    _T(".txt"),
    _T(".ini"),
    _T(".c"),
    _T(".cpp"),
    _T(".h"),
    _T(".hpp"),
    _T(".bat"),
    _T(".html"),
    _T(".java"),
    _T(".htm"),
    _T(".jav")
//    _T(".doc")
};

/*=============================================================================
函 数 名:FtpCtrl_CallbackStatus
功    能:定义CFtpCtrl回调友元函数
参    数:HINTERNET hInternet                [in]    回调句柄
         DWORD dwContext                    [in]    CFtpCtrl
         DWORD dwInternetStatus             [in]    网络状态
         LPVOID lpvStatusInformation        [in]    附加状态信息
         DWORD dwStatusInformationLength    [in]    附加信息长度
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/09/29  4.0     王昊    创建
=============================================================================*/
void CALLBACK FtpCtrl_CallbackStatus(HINTERNET hInternet,
                                     DWORD dwContext,
                                     DWORD dwInternetStatus,
                                     LPVOID lpvStatusInformation,
                                     DWORD dwStatusInformationLength)
{
    CFtpCtrl *pcFtpCtrl = reinterpret_cast<CFtpCtrl*>(dwContext);

    if ( pcFtpCtrl == NULL )
    {
        return;
    }

    LPDWORD pdwInformation(NULL);
    TRACE(_T("FtpCtrl_CallbackStatus's Internet Status is %d\n"), dwInternetStatus);

    switch ( dwInternetStatus )
    {
    case INTERNET_STATUS_RESOLVING_NAME:        //  10
        TRACE( _T("Looking up the IP address for %s\n"), (LPCTSTR)lpvStatusInformation );
        break;
    case INTERNET_STATUS_NAME_RESOLVED:         //  11
        TRACE( _T("Name resolved %s\n"), (LPCTSTR)lpvStatusInformation );
        break;
    case INTERNET_STATUS_CONNECTING_TO_SERVER:  //  20
        // lpvStatusInformation是一个SOCKADDR的指针
        TRACE( _T("Connecting to server--%s...\n"), (LPCTSTR)lpvStatusInformation );
        break;
    case INTERNET_STATUS_CONNECTED_TO_SERVER:   //  21
        // lpvStatusInformation是一个SOCKADDR的指针
        TRACE( _T("Connected to server--%s\n"), (LPCTSTR)lpvStatusInformation );
        break;
    case INTERNET_STATUS_SENDING_REQUEST:       //  30
        TRACE( _T("Sending request\n") );
        break;
    case INTERNET_STATUS_REQUEST_SENT:          //  31
        {
            //  发送数据到服务器
            if ( pcFtpCtrl->GetFtpDirect() == emFtpUpload )
            {
                //  只有当处于上传状态的时候才处理
                if ( pcFtpCtrl->m_dwFtpHead > 0 && pcFtpCtrl ->m_dwFtpHead < 5 )
                {
                    // 5这个值是一个经验值，具体为什么，由于没有深入研究RFC的协议
                    // 所以还不知道，将来如果知道原因，可以补充上
                    pcFtpCtrl->m_dwFtpHead++;
                }
                else if ( pcFtpCtrl->m_dwFtpHead == 5 )
                {
                    pdwInformation = (LPDWORD)lpvStatusInformation;
                    u32 dwCurSize = pcFtpCtrl->IncreaseFtpSize(*pdwInformation);
                    TRACE( _T("本次发送的数据大小为: %d，总共数据为：%d\n"),
                           *pdwInformation, dwCurSize );
                    pcFtpCtrl->PostMsg( emFtpTransfer, dwCurSize );
                }
            }
            break;
        }
    case INTERNET_STATUS_RESPONSE_RECEIVED:     // 41
        {
            //  从服务器接收到的响应
            if ( pcFtpCtrl->GetFtpDirect() == emFtpDownload )
            {
                //  只有当处于下载状态的时候，才处理
                pdwInformation = (LPDWORD)lpvStatusInformation;
                if ( pcFtpCtrl->m_dwFtpHead > 0 && pcFtpCtrl->m_dwFtpHead < 6 )
                {
                    //  6这个值是一个经验值，具体为什么，由于没有深入研究rfc的协议
                    //  所以还不知道，将来如果知道原因，可以补充上
                    pcFtpCtrl->m_dwFtpHead++;
                    TRACE( _T("在连接之后第%d次接收数据！%d\n"),
                           pcFtpCtrl->m_dwFtpHead,
                           static_cast<DWORD>(*pdwInformation) );
                }
                else if ( pcFtpCtrl->m_dwFtpHead == 6 )
                {
                    pdwInformation = (LPDWORD)lpvStatusInformation;
                    u32 dwCurSize = pcFtpCtrl->IncreaseFtpSize(*pdwInformation);
                    TRACE( _T("本次接收的数据大小为: %d，总共数据为：%d\n"),
                           *pdwInformation, dwCurSize );
                    pcFtpCtrl->PostMsg( emFtpTransfer, dwCurSize );
                }
            }
            break;
        }
    case INTERNET_STATUS_RECEIVING_RESPONSE:    //  40
        TRACE( _T("等待服务器的响应！\n") );
        break;
    case INTERNET_STATUS_CTL_RESPONSE_RECEIVED: //  42
    case INTERNET_STATUS_PREFETCH:              //  43
    case INTERNET_STATUS_CLOSING_CONNECTION:    //  50
        TRACE( _T("Closing connection\n") );
        break;
    case INTERNET_STATUS_CONNECTION_CLOSED:     //  51
        TRACE( _T("Connection closed\n") );
        break;
    case INTERNET_STATUS_HANDLE_CREATED:        //  60
        {
            LPINTERNET_ASYNC_RESULT ptIAR
                = reinterpret_cast<LPINTERNET_ASYNC_RESULT>(lpvStatusInformation);
            TRACE( _T("InternetConnect Handle Created with Error: %d, Result: %d\n"),
                   ptIAR->dwError, ptIAR->dwResult );
            if ( hInternet == pcFtpCtrl->GetCurrentConnect() )
            {
                TRACE( _T("Connect Handle Created!\n") );
                pcFtpCtrl->m_dwFtpHead = 1;
            }
            else if ( hInternet == pcFtpCtrl->GetCurrentSession() )
            {
                TRACE( _T("Session handle created!\n") );
            }
            break;
        }
    case INTERNET_STATUS_HANDLE_CLOSING:        //  70
        pcFtpCtrl->m_dwFtpHead = 0;
        TRACE( _T("Handle closed with dif %d!\n"),
               pcFtpCtrl->GetCurProcSize() - pcFtpCtrl->GetTotalFileSize() );
        break;
    case INTERNET_STATUS_DETECTING_PROXY:       //  80
        TRACE( _T("Detecting proxy\n") );
        break;
    case INTERNET_STATUS_REQUEST_COMPLETE:      //  100
        {
            LPINTERNET_ASYNC_RESULT ptIAR =
                reinterpret_cast<LPINTERNET_ASYNC_RESULT>(lpvStatusInformation);
            TRACE( _T("一个异步操作完成，错误为：%d，结果为：%d\n"),
                   ptIAR->dwError, ptIAR->dwResult );
            break;
        }
    case INTERNET_STATUS_REDIRECT:              //  110
        TRACE( _T("HTTP request redirected to \n") );
        break;
    case INTERNET_STATUS_INTERMEDIATE_RESPONSE: //  120
        TRACE( _T("Received intermediate status message from the server.\n") );
        break;
    case INTERNET_STATUS_STATE_CHANGE:          //  200
        {
            TRACE( _T("Moved between a secure and a nonsecure site\n") );
            LPDWORD pdwRead = (LPDWORD)lpvStatusInformation;
            switch ( *pdwRead )
            {
            case INTERNET_STATE_CONNECTED:          //  0x00000001
                TRACE( _T("Connected state moved between secure and nonsecure site\n") );
                break;
            case INTERNET_STATE_DISCONNECTED:       //  0x00000002
                TRACE( _T("Disconnected from network\n") );
                break;
            case INTERNET_STATE_DISCONNECTED_BY_USER:   //  0x00000010
                TRACE( _T("Disconnected by user request\n") );
                break;
            case INTERNET_STATE_IDLE:               //  0x00000100
                TRACE( _T("No network requests are being made (by Wininet).\n") );
                break;
            case INTERNET_STATE_BUSY:               //  0x00000200
                TRACE( _T("Network requests are being made (by Wininet).\n") );
                break;
            case INTERNET_STATUS_USER_INPUT_REQUIRED:   //  0x00000040
                TRACE( _T("The request requires user input to complete\n") );
                break;
            default:
                break;
            }
            break;
        }
    default:
        break;
    }
}

/*=============================================================================
函 数 名:FtpCtrlDownloadThread
功    能:FTP下载线程回调函数
参    数:LPVOID pParam                      [in]    CFtpCtrl
注    意:无
返 回 值:成功: 0    失败: -1
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/10/08  4.0     王昊    创建
=============================================================================*/
DWORD WINAPI FtpCtrlDownloadThread(LPVOID pParam)
{
    CFtpCtrl *pcFtpCtrl = reinterpret_cast<CFtpCtrl*>(pParam);

    if ( pcFtpCtrl == NULL )
    {
        return -1;
    }
    
	//获取远程文件的大小, 有的时候不能成功
	pcFtpCtrl->m_dwTotalFileSize = pcFtpCtrl->GetRemoteFileSize();
	TRACE(_T("Remote File size is %d\n"), pcFtpCtrl->m_dwTotalFileSize);

	if ( ! pcFtpCtrl->ConnectSrv() )
	{
		pcFtpCtrl->EndFtpFile();
		return -1;
	}

	pcFtpCtrl->PostMsg( (WPARAM)emFtpBegin, (LPARAM)pcFtpCtrl->m_dwTotalFileSize );

    //  获取文件
    BOOL32 bRet = FtpGetFile( pcFtpCtrl->GetCurrentConnect(),
                              pcFtpCtrl->GetCurrentRemoteFile(),
                              pcFtpCtrl->GetCurrentLocalFile(),
                              FALSE,
                              FILE_ATTRIBUTE_NORMAL,
                              pcFtpCtrl->GetCurrentFileType()
                                | INTERNET_FLAG_RELOAD
                                | INTERNET_FLAG_RESYNCHRONIZE,
                              (u32)pcFtpCtrl );
    if ( ! bRet )
    {
        LPTSTR pszMsg = NULL;
        DWORD dwErrorId = GetLastError();
        CFtpCtrl::FormatFtpError( dwErrorId, &pszMsg );
        TRACE( _T("FtpGetFile Error with %d--%s\n"), dwErrorId, pszMsg );
        LocalFree( pszMsg );
        pszMsg = NULL;
    }

    pcFtpCtrl->PostMsg( emFtpEnd, bRet ? 0 : GetLastError() );

    if ( pcFtpCtrl->IsDelRemoteFileAfterDownload() )
    {
        FtpDeleteFile( pcFtpCtrl->GetCurrentConnect(),
                       pcFtpCtrl->GetCurrentRemoteFile() );
    }

    pcFtpCtrl->EndFtpFile();
    TRACE( _T("FtpGetFile Thread with id 0x%x end!\n"), GetCurrentThreadId() );

    return bRet ? 0 : -1;
}

/*=============================================================================
函 数 名:FtpCtrlUploadThread
功    能:FTP上传线程回调函数
参    数:LPVOID pParam                      [in]    CFtpCtrl
注    意:无
返 回 值:成功: 0    失败: -1
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/10/08  4.0     王昊    创建
=============================================================================*/
DWORD WINAPI FtpCtrlUploadThread(LPVOID pParam)
{
    CFtpCtrl *pcFtpCtrl = reinterpret_cast<CFtpCtrl*>(pParam);
    if ( pcFtpCtrl == NULL )
    {
        return -1;
    }

	if ( ! pcFtpCtrl->ConnectSrv() )
    {
        pcFtpCtrl->EndFtpFile();
        return FALSE;
    }
	
	if (pcFtpCtrl->m_bCreateNewDirectory)
	{
		pcFtpCtrl->CreateFtpDirectory(pcFtpCtrl->GetCurrentRemoteFile());
	}
	
    //  发送消息，通知界面开始传输了
    pcFtpCtrl->PostMsg( (WPARAM)emFtpBegin, (LPARAM)pcFtpCtrl->m_dwTotalFileSize );

    FtpDeleteFile( pcFtpCtrl->GetCurrentConnect(),
                   pcFtpCtrl->GetCurrentRemoteFile() );
    //  上传文件
    BOOL32 bRet = FtpPutFile( pcFtpCtrl->GetCurrentConnect(),
                              pcFtpCtrl->GetCurrentLocalFile(),
                              pcFtpCtrl->GetCurrentRemoteFile(),
                              pcFtpCtrl->GetCurrentFileType()
                                | INTERNET_FLAG_RESYNCHRONIZE,
                              (DWORD)pcFtpCtrl );
    if ( ! bRet )
    {
        LPTSTR pszMsg = NULL;
        DWORD dwErrorId = GetLastError();
        CFtpCtrl::FormatFtpError( dwErrorId, &pszMsg );
        TRACE( _T("FtpPutFile Error with %d--%s\n"), dwErrorId, pszMsg );
        LocalFree( pszMsg );
        pszMsg = NULL;
    }

    pcFtpCtrl->PostMsg( (WPARAM)emFtpEnd, bRet ? 0 : GetLastError() );

    pcFtpCtrl->EndFtpFile();
    TRACE( _T("FtpPutFile Thread with id 0x%x end!\n"), GetCurrentThreadId() );

    return bRet ? 0 : -1;
}

//////////////////////////////////////////////////////////////////////////
//
//      CFtpCtrl
//

/*=============================================================================
函 数 名:CFtpCtrl
功    能:构造函数
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/09/29  4.0     王昊    创建
=============================================================================*/
CFtpCtrl::CFtpCtrl() : m_hSession( NULL )
                       ,m_hConnect( NULL )
                       ,m_wFtpSrvPort( INTERNET_DEFAULT_FTP_PORT )
                       ,m_hFtpThread( NULL )
                       ,m_pszAgent( NULL )
                       ,m_dwFtpThreadId( 0 )
                       ,m_hWnd( NULL )
                       ,m_dwFileType( FTP_TRANSFER_TYPE_UNKNOWN )
                       ,m_dwCurrentFtpSize( 0 )
                       ,m_dwTotalFileSize( TRUE )
                       ,m_dwEventId( 0 )
                       ,m_dwFtpHead( 0 )
                       ,m_bTransfering( FALSE )
                       ,m_bDelRemoteFile( FALSE )
                       ,m_byFtpDirect( emFtpDownload )
					   ,m_pMsgDeal( 0 )
					   ,m_bCreateNewDirectory( FALSE )
{
    ZeroMemory( m_aszFtpSrvIp,      sizeof (m_aszFtpSrvIp) );
    ZeroMemory( m_aszFtpSrvUser,    sizeof (m_aszFtpSrvUser) );
    ZeroMemory( m_aszFtpSrvPwd,     sizeof (m_aszFtpSrvPwd) );
    ZeroMemory( m_aszProxyName,     sizeof (m_aszProxyName) );
    ZeroMemory( m_aszProxyPwd,      sizeof (m_aszProxyPwd) );
    ZeroMemory( m_aszRemoteFile,    sizeof (m_aszRemoteFile) );
    ZeroMemory( m_aszLocalFile,     sizeof (m_aszLocalFile) );
}

/*=============================================================================
函 数 名:~CFtpCtrl
功    能:析构函数
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/09/29  4.0     王昊    创建
=============================================================================*/
CFtpCtrl::~CFtpCtrl()
{
    if ( m_pszAgent != NULL )
    {
        delete [] m_pszAgent;
        m_pszAgent = NULL;
    }
    EndFtpFile();
}

/*=============================================================================
函 数 名:IsFileAscii
功    能:判断一个要进行文件传输的文件是否是ASCII方式的
参    数:LPCTSTR pszFileName                [in]    文件名
注    意:无
返 回 值:是否ASCII方式
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/09/29  4.0     王昊    创建
=============================================================================*/
BOOL32 CFtpCtrl::IsFileAscii(LPCTSTR pszFileName)
{
    if ( pszFileName == NULL )
    {
        return FALSE;
    }

    LPCTSTR pszExt = _tcsrchr( pszFileName, '.' );
    if ( pszExt == NULL )
    {
        return FALSE;
    }

    for ( s32 nIndex = 0; nIndex < FTP_FILE_ASCII_COUNT; nIndex ++ )
    {
        if ( _tcsicmp( pszExt, g_pszAsciiFileExt[nIndex] ) == 0 )
        {
            return TRUE;
        }
    }

    return FALSE;
}


/*=============================================================================
函 数 名:FormatFtpError
功    能:获取系统的错误描述
参    数:u32 dwErrorCode                    [in]    错误码
         LPTSTR *ppszMsg                    [out]   描述信息
注    意:ppszMsg使用结束后，请调用LocalFree来释放该空间
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/09/29  4.0     王昊    创建
=============================================================================*/
void CFtpCtrl::FormatFtpError(DWORD dwErrorCode, LPTSTR *ppszMsg)
{
    if ( ppszMsg != NULL )
    {
        if ( dwErrorCode > INTERNET_ERROR_BASE )// 对于Internet的错误，要特殊处理
        {
            DWORD dwBufLen = 0;
            InternetGetLastResponseInfo( &dwErrorCode, NULL, &dwBufLen );
            LPTSTR pszMsg = (LPTSTR)LocalAlloc( LMEM_ZEROINIT, ( dwBufLen + 1 ) * sizeof(TCHAR) );
            InternetGetLastResponseInfo( &dwErrorCode, pszMsg, &dwBufLen );
            *ppszMsg = pszMsg;
        }
        else        // 查询普通的错误
        {
            FormatMessage(  FORMAT_MESSAGE_ALLOCATE_BUFFER |
                                FORMAT_MESSAGE_IGNORE_INSERTS |
                                FORMAT_MESSAGE_FROM_SYSTEM,
                            NULL, dwErrorCode,
                            MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
                            (LPTSTR)ppszMsg, 0, NULL);
        }
    }
}

/*=============================================================================
函 数 名:SetServerParam
功    能:设置FTP服务器的连接参数
参    数:LPCTSTR pszIpAddr                  [in]    服务器IP地址
         LPCTSTR pszUser                    [in]    登录用户名称
         LPCTSTR pszPwd                     [in]    登录口令
         u16 wPort                          [in]    FTP服务器端口
         LPCTSTR pszProxyName               [in]    代理名称
         LPCTSTR pszProxyPwd                [in]    代理口令
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/09/29  4.0     王昊    创建
=============================================================================*/
BOOL32 CFtpCtrl::SetServerParam(LPCTSTR pszIpAddr, LPCTSTR pszUser,
                                LPCTSTR pszPwd,
                                u16 wPort /* = INTERNET_DEFAULT_FTP_PORT */,
                                LPCTSTR pszProxyName /* = NULL */,
                                LPCTSTR pszProxyPwd /* = NULL */)
{
    if ( pszIpAddr == NULL || pszUser == NULL || pszPwd == NULL )
    {
        return FALSE;
    }

    ZeroMemory( m_aszFtpSrvIp,      sizeof (m_aszFtpSrvIp) );
    ZeroMemory( m_aszFtpSrvUser,    sizeof (m_aszFtpSrvUser) );
    ZeroMemory( m_aszFtpSrvPwd,     sizeof (m_aszFtpSrvPwd) );
    ZeroMemory( m_aszProxyName,     sizeof (m_aszProxyName) );
    ZeroMemory( m_aszProxyPwd,      sizeof (m_aszProxyPwd) );

    _tcsncpy( m_aszFtpSrvIp, pszIpAddr, _countof (m_aszFtpSrvIp) - 1 );
    _tcsncpy( m_aszFtpSrvUser, pszUser, _countof (m_aszFtpSrvUser) - 1 );
    _tcsncpy( m_aszFtpSrvPwd, pszPwd, _countof (m_aszFtpSrvPwd) - 1 );
	
	m_wFtpSrvPort = wPort;

    if ( pszProxyName != NULL )
    {
        _tcsncpy( m_aszProxyName, pszProxyName, _countof (m_aszProxyName) - 1 );
    }
    if ( pszProxyPwd != NULL )
    {
        _tcsncpy( m_aszProxyPwd, pszProxyPwd, _countof (m_aszProxyPwd) - 1 );
    }

    return TRUE;
}

 /*=============================================================================
    函 数 名:CreateFtpDirectory
    功    能:创建FTP上传新目录
    参    数:LPCTSTR lpszFtpFilePath			[in] 上传的文件的具体路径
    注    意:无
    返 回 值:是否成功
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2012/11/21  4.7     吕冠娇    创建
    =============================================================================*/
BOOL32 CFtpCtrl::CreateFtpDirectory(LPCTSTR lpszFtpFilePath)
{
	CString csRemoteFile = lpszFtpFilePath;
	s32 nIndex = csRemoteFile.ReverseFind('/');
	CString csDirectory = csRemoteFile.Left(nIndex);
	
	BOOL bCreate = FALSE;
	BOOL bIsFind = FtpSetCurrentDirectory(m_hConnect, csDirectory);
	
	if (!bIsFind)
	{/*没有上传的目录*/
		bCreate = FtpCreateDirectory(m_hConnect, csDirectory);
	}	
	//把FTP上传的目录重新设回成根目录，FTP上传的目录默认是相对成根目录上传的
	FtpSetCurrentDirectory(m_hConnect, _T("./")); 
	
	return bCreate;
}

/*=============================================================================
函 数 名:BeginDownload
功    能:开始下载文件
参    数:HWND hWnd                          [in]    接收消息的窗口句柄
         LPCTSTR pszRemoteFile              [in]    远端文件名称
         LPCTSTR pszLocalFile               [in]    保存本地的文件名称
         u32 dwFileType                     [in]    文件传输类型
         LPCTSTR pszAgent                   [in]    InternetOpen第一个参数
         BOOL32 bDeleteRemoteFile           [in]    下载完毕后是否删除远端文件
注    意:无
返 回 值:是否成功
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/09/29  4.0     王昊    创建
=============================================================================*/
BOOL32 CFtpCtrl::BeginDownload( LPCTSTR pszRemoteFile,
                               LPCTSTR pszLocalFile,
                               u32 dwFileType /* = FTP_TRANSFER_TYPE_UNKNOWN */,
                               LPCTSTR pszAgent /* = FTP_AGENT */,
                               BOOL32 bDeleteRemoteFile /* = TRUE */)
{
    if ( ! CheckParam( pszRemoteFile, pszLocalFile, dwFileType ) )
    {
        return FALSE;
    }

    m_bDelRemoteFile = bDeleteRemoteFile;

    return DownloadFile( pszRemoteFile, pszLocalFile, dwFileType, pszAgent );
}

 /*=============================================================================
    函 数 名:BeginUpload
    功    能:开始上传文件
    参    数:HWND hWnd                          [in]    接收消息的窗口句柄
             LPCTSTR pszRemoteFile              [in]    远端文件名称
             LPCTSTR pszLocalFile               [in]    保存本地的文件名称
             u32 dwFileType                     [in]    文件传输类型
             LPCTSTR pszAgent                   [in]    InternetOpen第一个参数
			 BOOL32 bIsCreateNewDirectory       [in]	上传的目录没有时，是否创建新目录
    注    意:无
    返 回 值:是否成功
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/09/29  4.0     王昊    创建
	2012/11/21  4.7     吕冠娇  修改(添加上传的目录不存在时，可创建新目录功能，再进行FTP上传)
    =============================================================================*/
BOOL32 CFtpCtrl::BeginUpload( LPCTSTR pszRemoteFile,
                             LPCTSTR pszLocalFile,
                             u32 dwFileType /* = FTP_TRANSFER_TYPE_UNKNOWN */,
                             LPCTSTR pszAgent /* = FTP_AGENT */,
							 BOOL32 bIsCreateNewDirectory /*= FALSE*/)
{
    if ( ! CheckParam( pszRemoteFile, pszLocalFile, dwFileType ) )
    {
        return FALSE;
    }
	m_bCreateNewDirectory = bIsCreateNewDirectory;

    return UploadFile( pszRemoteFile, pszLocalFile, dwFileType, pszAgent);
}

/*=============================================================================
函 数 名:CheckParam
功    能:检查开始上传或下载时传入的参数是否正确
参    数:LPCTSTR pszRemoteFile              [in]    远端文件名称
         LPCTSTR pszLocalFile               [in]    保存本地的文件名称
         u32 dwFileType                     [in]    文件传输类型
注    意:无
返 回 值:参数是否正确
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/09/29  4.0     王昊    创建
=============================================================================*/
BOOL32 CFtpCtrl::CheckParam(LPCTSTR pszRemoteFile, LPCTSTR pszLocalFile,
                            u32 dwFileType)
{
    if ( pszRemoteFile == NULL || pszLocalFile == NULL
         || ( dwFileType != FTP_TRANSFER_TYPE_UNKNOWN
              && dwFileType != FTP_TRANSFER_TYPE_ASCII
              && dwFileType != FTP_TRANSFER_TYPE_BINARY ) )
    {
        return FALSE;
    }

    return !m_bTransfering;
}

/*=============================================================================
函 数 名:DownloadFile
功    能:下载文件
参    数:LPCTSTR pszRemoteFile              [in]    远端文件名称
         LPCTSTR pszLocalFile               [in]    保存本地的文件名称
         u32 dwFileType                     [in]    文件传输类型
         LPCTSTR pszAgent                   [in]    InternetOpen第一个参数
注    意:无
返 回 值:下载是否成功
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/09/29  4.0     王昊    创建
=============================================================================*/
BOOL32 CFtpCtrl::DownloadFile(LPCTSTR pszRemoteFile, LPCTSTR pszLocalFile,
                              u32 dwFileType, LPCTSTR pszAgent)
{
    ZeroMemory( m_aszRemoteFile,    sizeof (m_aszRemoteFile) );
    ZeroMemory( m_aszLocalFile,     sizeof (m_aszLocalFile) );

    _tcsncpy( m_aszRemoteFile, pszRemoteFile, _countof (m_aszRemoteFile) - 1 );
    _tcsncpy( m_aszLocalFile, pszLocalFile, _countof (m_aszLocalFile) - 1 );

    m_dwFileType = dwFileType & FTP_TRANSFER_TYPE_MASK;
    m_dwFtpHead = 0;
    m_byFtpDirect = emFtpDownload;

    if ( pszAgent != NULL )
    {
        delete [] m_pszAgent;
        m_pszAgent = new TCHAR [_tcslen(pszAgent) + 1];
        _tcscpy( m_pszAgent, pszAgent );
    }

    //  设置文件传输方式
    if ( dwFileType == FTP_TRANSFER_TYPE_UNKNOWN )
    {
        m_dwFileType = IsFileAscii( pszRemoteFile )
                        ? FTP_TRANSFER_TYPE_ASCII : FTP_TRANSFER_TYPE_BINARY;
    }
	m_dwTotalFileSize = 0;
	m_dwCurrentFtpSize = 0;

//     if ( ! ConnectSrv() )
//     {
//         EndFtpFile();
//         return FALSE;
//     }

	PostMsg( emFtpConnect, 0 );
    //  创建文件下载线程
    m_hFtpThread = CreateThread( NULL, 0, FtpCtrlDownloadThread, this,
                                 0, &m_dwFtpThreadId );
    if ( m_hFtpThread == NULL )
    {
		DWORD dwErrorID = GetLastError();
#ifdef _DEBUG
        LPTSTR pszMsg = NULL;
        FormatFtpError( dwErrorID, &pszMsg );
        TRACE( _T("CreateThread Error with %s\n"), pszMsg );
        LocalFree( pszMsg );
#endif
        InternetCloseHandle( m_hConnect );
        InternetCloseHandle( m_hSession );
		PostMsg( emFtpEnd, dwErrorID );
        return FALSE;
    }


    //  降低传输线程的优先级
    SetThreadPriority( m_hFtpThread, THREAD_PRIORITY_BELOW_NORMAL );
    m_bTransfering = TRUE;
    return TRUE;
}

/*=============================================================================
函 数 名:UploadFile
功    能:上传文件
参    数:LPCTSTR pszRemoteFile              [in]    远端文件名称
         LPCTSTR pszLocalFile               [in]    保存本地的文件名称
         u32 dwFileType                     [in]    文件传输类型
         LPCTSTR pszAgent                   [in]    InternetOpen第一个参数
注    意:无
返 回 值:上传是否成功
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/09/29  4.0     王昊    创建
=============================================================================*/
BOOL32 CFtpCtrl::UploadFile(LPCTSTR pszRemoteFile, LPCTSTR pszLocalFile,
                            u32 dwFileType, LPCTSTR pszAgent)
{
    ZeroMemory( m_aszRemoteFile,    sizeof (m_aszRemoteFile) );
    ZeroMemory( m_aszLocalFile,     sizeof (m_aszLocalFile) );

    _tcsncpy( m_aszRemoteFile, pszRemoteFile, _countof (m_aszRemoteFile) - 1 );
    _tcsncpy( m_aszLocalFile, pszLocalFile, _countof (m_aszLocalFile) - 1 );

    m_dwFtpHead = 0;
    m_byFtpDirect = emFtpUpload;
    m_dwFileType = dwFileType & FTP_TRANSFER_TYPE_MASK;

    if ( pszAgent != NULL )
    {
        delete [] m_pszAgent;
        m_pszAgent = new TCHAR [_tcslen(pszAgent) + 1];
        _tcscpy( m_pszAgent, pszAgent );
    }

    //  设置文件传输方式
    if ( dwFileType == FTP_TRANSFER_TYPE_UNKNOWN )
    {
        m_dwFileType = IsFileAscii( pszRemoteFile )
                        ? FTP_TRANSFER_TYPE_ASCII : FTP_TRANSFER_TYPE_BINARY;
    }

    //  计算本地文件的大小, 只要该文件存在, 就能够得到大小
    m_dwTotalFileSize = GetLocalFileSize();
    if ( m_dwTotalFileSize == (u32)-1 )
    {
        m_dwTotalFileSize = 0;
        return FALSE;
    }
    TRACE( _T("Local File size is %d\n"), m_dwTotalFileSize );

	m_dwCurrentFtpSize = 0;

	//  创建文件上传线程
    m_hFtpThread = CreateThread( NULL, 0, FtpCtrlUploadThread, this,
                                 0, &m_dwFtpThreadId );
    if ( m_hFtpThread == NULL )
    {
        LPTSTR pszMsg = NULL;
        FormatFtpError( GetLastError(), &pszMsg );
        TRACE( _T("CreateThread Error with %s\n"), pszMsg );
        LocalFree( pszMsg );
        InternetCloseHandle( m_hConnect );
        InternetCloseHandle( m_hSession );
        return FALSE;
    }

    //  降低传输线程的优先级
    SetThreadPriority( m_hFtpThread, THREAD_PRIORITY_BELOW_NORMAL );
    m_bTransfering = TRUE;
    return TRUE;
}

/*=============================================================================
函 数 名:ConnectSrv
功    能:连接服务器
参    数:无
注    意:无
返 回 值:连接是否成功
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/09/29  4.0     王昊    创建
2012/04/17	4.0		邹俊龙	出错后通知外部错误信息
=============================================================================*/
BOOL32 CFtpCtrl::ConnectSrv(void)
{
	if ( ( m_hSession != NULL )&& ( m_hConnect != NULL))
	{
		return TRUE;
	}

	if (m_hSession == NULL )
	{	
		// 打开Internet连接
		m_hSession = InternetOpen( m_pszAgent, INTERNET_OPEN_TYPE_DIRECT,
								   m_aszProxyName[0] == 0 ? NULL : m_aszProxyName,
								   m_aszProxyPwd[0] == 0 ? NULL : m_aszProxyPwd,
								   INTERNET_FLAG_NO_CACHE_WRITE);

		if ( m_hSession == NULL )
		{

			DWORD dwErrorId = GetLastError();
			
#ifdef _DEBUG
			LPTSTR pszMsg = NULL;
			FormatFtpError( GetLastError(), &pszMsg );
			TRACE( _T("InternetOpen Error with %s\n"), pszMsg );
			LocalFree( pszMsg );
			pszMsg = NULL;
#endif
			
			PostMsg( (WPARAM)emFtpEnd, dwErrorId );
			return FALSE;

		}

		// 设置状态回调函数
		if ( InternetSetStatusCallback( m_hSession, FtpCtrl_CallbackStatus )
					== INTERNET_INVALID_STATUS_CALLBACK )
		{
			DWORD dwErrorId = GetLastError();

	#ifdef _DEBUG
			LPTSTR pszMsg = NULL;
			FormatFtpError( dwErrorId, &pszMsg );
			TRACE( _T("InternetSetStatusCallback Error with %s\n"), pszMsg );
			LocalFree( pszMsg );
			pszMsg = NULL;
	#endif
			InternetCloseHandle( m_hSession );
			PostMsg( (WPARAM)emFtpEnd, dwErrorId );
			return FALSE;
		}

	}

	if ( m_hConnect == NULL )
	{	
		//  连接到对方
		m_hConnect = InternetConnect( m_hSession, m_aszFtpSrvIp,
									  m_wFtpSrvPort, m_aszFtpSrvUser,
									  m_aszFtpSrvPwd, INTERNET_SERVICE_FTP,
									  INTERNET_FLAG_PASSIVE
											| INTERNET_FLAG_EXISTING_CONNECT,
									  (DWORD)this );
		if ( m_hConnect == NULL )
		{
			if ( m_hConnect == NULL )
			{
				DWORD dwErrorId = GetLastError();
#ifdef _DEBUG
				LPTSTR pszMsg = NULL;
				FormatFtpError( dwErrorId, &pszMsg );
				TRACE( _T("InternetConnect Error with %s\n"), pszMsg );
				LocalFree( pszMsg );
				pszMsg = NULL;
#endif
				InternetCloseHandle( m_hSession );
				//  通知下载对话框下载失败
				PostMsg( (WPARAM)emFtpEnd, dwErrorId );
				return FALSE;
			}
		}

		//设置ftp发送和接收的超时时间
		u32 dwMisSec = FTP_TIMEOUT;
		InternetSetOption( m_hConnect, INTERNET_OPTION_CONTROL_SEND_TIMEOUT,
						   &dwMisSec, sizeof (u32) );
		InternetSetOption( m_hConnect, INTERNET_OPTION_CONTROL_RECEIVE_TIMEOUT,
						   &dwMisSec, sizeof (u32) );
		InternetSetOption( m_hConnect, INTERNET_OPTION_DATA_SEND_TIMEOUT,
						   &dwMisSec, sizeof (u32) );
		InternetSetOption( m_hConnect, INTERNET_OPTION_DATA_RECEIVE_TIMEOUT,
						   &dwMisSec, sizeof (u32) );

		return TRUE;
	}
	return FALSE;
}

/*=============================================================================
函 数 名:EndFtpFile
功    能:停止FTP传输
参    数:无
注    意:无
返 回 值:是否成功
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/10/08  4.0     王昊    创建
=============================================================================*/
BOOL32 CFtpCtrl::EndFtpFile(void)
{
    if ( m_hConnect != NULL )
    {
        InternetCloseHandle(m_hConnect);
        m_hConnect = NULL;
    }
    if ( m_hSession != NULL )
    {
        InternetCloseHandle(m_hSession);
        m_hSession = NULL;
    }
    if ( m_hFtpThread != NULL )
    {
        CloseHandle( m_hFtpThread );
        m_hFtpThread = NULL;
    }
    m_bTransfering = FALSE;
    return TRUE;
}

/*=============================================================================
函 数 名:IncreaseFtpSize
功    能:在文件传输过程中, 设置实际已经传输的文件大小
参    数:u32 dwProcSize             [in]    新完成大小
注    意:无
返 回 值:已完成大小
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/10/08  4.0     王昊    创建
=============================================================================*/
u32 CFtpCtrl::IncreaseFtpSize(u32 dwProcSize)
{
    if (m_dwCurrentFtpSize < m_dwTotalFileSize)
    {
        m_dwCurrentFtpSize += dwProcSize;
    }
    return m_dwCurrentFtpSize;
}

/*=============================================================================
函 数 名:GetRemoteFileSize
功    能:获取远端文件的大小
参    数:无
注    意:无
返 回 值:远端文件的大小
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/09/29  4.0     王昊    创建
=============================================================================*/
u32	CFtpCtrl::GetRemoteFileSize(void)
{
    u32 dwRemoteFileSize = GetVaxRemoteFileSize();
    if ( dwRemoteFileSize != -1 && dwRemoteFileSize != 0 )
    {
        return dwRemoteFileSize;
    }

    dwRemoteFileSize = GetWinRemoteFileSize();
    if ( dwRemoteFileSize != -1 && dwRemoteFileSize != 0 )
    {
        return dwRemoteFileSize;
    }

    return 0;
}

/*=============================================================================
函 数 名:GetLocalFileSize
功    能:获取本地文件的大小
参    数:无
注    意:无
返 回 值:本地文件的大小
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/09/29  4.0     王昊    创建
=============================================================================*/
u32	CFtpCtrl::GetLocalFileSize(void)
{
    //判断文件是否存在
    HANDLE hFile = CreateFile( m_aszLocalFile, 0, 0, NULL, OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL, NULL );
    if ( hFile == INVALID_HANDLE_VALUE )
    {
        return 0;
    }
    //获取文件大小
    u32 dwSize = GetFileSize( hFile, NULL );
    CloseHandle( hFile );
    hFile = NULL;

    return dwSize;
}

/*=============================================================================
函 数 名:GetWinRemoteFileSize
功    能:获取远端windows文件大小
参    数:无
注    意:无
返 回 值:远端windows文件大小
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/09/29  4.0     王昊    创建
=============================================================================*/
u32 CFtpCtrl::GetWinRemoteFileSize(void)
{
    u32 dwSize          = 0;
    DWORD dwErrorId     = ERROR_SUCCESS;
    LPTSTR pszMsg       = NULL;
    HINTERNET hSession  = NULL;
    HINTERNET hConnect  = NULL;
    HINTERNET hFile     = NULL;
    HINSTANCE hLibrary  = NULL;
    typedef DWORD (WINAPI *FtpGetFileSize_Proc)(HINTERNET, LPDWORD);

    __try
    {
        if ( m_aszRemoteFile[0] == 0 )
        {
            dwSize = 0;
            __leave;
        }

        hSession = InternetOpen( m_pszAgent, INTERNET_OPEN_TYPE_DIRECT,
                                 m_aszProxyName[0] == 0 ? NULL : m_aszProxyName,
                                 m_aszProxyPwd[0] == 0 ? NULL : m_aszProxyPwd,
                                 INTERNET_FLAG_NO_CACHE_WRITE );
        if ( hSession == NULL )
        {
            dwErrorId = GetLastError();
            FormatFtpError( dwErrorId, &pszMsg );
            TRACE( _T("InternetOpen Error With %d--%s\n"), dwErrorId, pszMsg );
            LocalFree( pszMsg );
            dwSize = -1;
            __leave;
        }

        hConnect = InternetConnect( hSession, m_aszFtpSrvIp, m_wFtpSrvPort,
                                    m_aszFtpSrvUser, m_aszFtpSrvPwd,
                                    INTERNET_SERVICE_FTP,
                                    INTERNET_FLAG_PASSIVE | INTERNET_FLAG_EXISTING_CONNECT,
                                    0 );
        if ( hConnect == NULL )
        {
            dwErrorId = GetLastError();
            FormatFtpError( dwErrorId, &pszMsg );
            TRACE( _T("InternetConnect Error With %d--%s\n"), dwErrorId, pszMsg );
            LocalFree( pszMsg );
            dwSize = -1;
            __leave;
        }

        hFile = FtpOpenFile( hConnect, m_aszRemoteFile, GENERIC_READ,
                             m_dwFileType | INTERNET_FLAG_RELOAD | INTERNET_FLAG_RESYNCHRONIZE,
                             NULL );
        if ( hFile == NULL )
        {
            dwErrorId = GetLastError();
            FormatFtpError( dwErrorId, &pszMsg );
            TRACE( _T("FtpOpen Error With %d--%s\n"), dwErrorId, pszMsg );
            LocalFree( pszMsg );
            dwSize = -1;
            __leave;
        }

        //直接从dll中得到FtpGetFileSize函数来获取文件大小
        hLibrary = LoadLibrary( _T("wininet.dll") );
        if ( hLibrary == NULL )
        {
            TRACE( _T("Load Library failed!\n") );
            dwErrorId = GetLastError();
            dwSize = 0;
            __leave;
        }

        FtpGetFileSize_Proc pfnFtpGetFileSize = 
		    (FtpGetFileSize_Proc)GetProcAddress( hLibrary, "FtpGetFileSize" );
        if ( pfnFtpGetFileSize == NULL )
        {
            TRACE( _T("Get Proc FtpGetFileSize Failed!\n") );
            dwErrorId = GetLastError();
            dwSize = 0;
            __leave;
        }

        dwSize = pfnFtpGetFileSize( hFile, NULL );
    }
    __finally
    {
        if ( hFile != NULL )
        {
            InternetCloseHandle( hFile );
//            hFile = NULL;
        }

        if ( hConnect != NULL )
        {
            InternetCloseHandle( hConnect );
//            hConnect = NULL;
        }

        if ( hSession != NULL )
        {
            InternetCloseHandle( hSession );
//            hSession = NULL;
        }

        if ( hLibrary != NULL )
        {
            FreeLibrary( hLibrary );
//            hLibrary = NULL;
        }

        if ( dwErrorId != ERROR_SUCCESS )
        {
            PostMsg( emFtpWarning, dwErrorId );
        }        
    }
	return dwSize;
}

/*=============================================================================
函 数 名:GetVaxRemoteFileSize
功    能:获取远端VAX文件大小
参    数:无
注    意:无
返 回 值:远端VAX文件大小
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/09/29  4.0     王昊    创建
=============================================================================*/
u32 CFtpCtrl::GetVaxRemoteFileSize(void)
{
    if ( m_aszRemoteFile[0] == 0 )
    {
        return 0;
    }

    CString cstrRemoteFile( m_aszRemoteFile );
    CString cstrPath( _T("/*.*") );
    s32 nIndex = cstrRemoteFile.ReverseFind( '/' );
    if ( nIndex != -1 )
    {
        cstrPath = cstrRemoteFile.Left( nIndex + 1 );
    }
    else
    {
        nIndex = cstrRemoteFile.ReverseFind( '\\' );
        if ( nIndex != -1 )
        {
            cstrPath = cstrRemoteFile.Left( nIndex + 1 );
        }
    }

    CString cstrFile = cstrRemoteFile.Mid( nIndex + 1 );
    cstrFile.MakeLower();

    LPTSTR pszMsg = NULL;
    HINTERNET hSession = InternetOpen( m_pszAgent, INTERNET_OPEN_TYPE_DIRECT,
									   m_aszProxyName[0] == 0
                                            ? NULL : m_aszProxyName,
									   m_aszProxyPwd[0] == 0
                                            ? NULL : m_aszProxyPwd,
									   INTERNET_FLAG_NO_CACHE_WRITE );
    if ( hSession == NULL )
    {
        u32 dwErrorId = GetLastError();
        FormatFtpError( dwErrorId, &pszMsg );
        TRACE( _T("InternetOpen Error With %d--%s\n"), dwErrorId, pszMsg );
        LocalFree( pszMsg );
        PostMsg( emFtpWarning, dwErrorId );
        return -1;
    }

    HINTERNET hConnect = InternetConnect( hSession, m_aszFtpSrvIp,
                                          m_wFtpSrvPort, m_aszFtpSrvUser,
                                          m_aszFtpSrvPwd, INTERNET_SERVICE_FTP,
                                          INTERNET_FLAG_PASSIVE
                                            | INTERNET_FLAG_EXISTING_CONNECT,
                                          0 );
    if ( hConnect == NULL )
    {
        u32 dwErrorId = GetLastError();
        FormatFtpError( dwErrorId, &pszMsg );
        TRACE( _T("InternetOpen Error With %d--%s\n"), dwErrorId, pszMsg );
        LocalFree( pszMsg );
        PostMsg( emFtpWarning, dwErrorId );
        InternetCloseHandle( hSession );
        return -1;
    }

    WIN32_FIND_DATA sWFD; 
    ZeroMemory( &sWFD, sizeof (sWFD) );
    BOOL32 bResult = TRUE;

    HINTERNET hFileConnection = FtpFindFirstFile( hConnect, cstrPath, &sWFD,
                                                  INTERNET_FLAG_RESYNCHRONIZE
                                                    | INTERNET_FLAG_RELOAD,
                                                  NULL);
    if ( hFileConnection == NULL )
    {
        u32 dwErrorId = GetLastError();
        FormatFtpError( dwErrorId, &pszMsg );
        TRACE( _T("FtpFindFirstFile Error With %d--%s\n"), dwErrorId, pszMsg );
        LocalFree( pszMsg );
        PostMsg( emFtpWarning, dwErrorId );
        InternetCloseHandle( hSession );
        InternetCloseHandle( hSession );
        return -1;
    }

    //由于从vax上获取文件列表时带有时间等属性，所以需要分离
    while ( bResult )
    {
        bResult = InternetFindNextFile( hFileConnection, &sWFD );
        CString cstrDir = sWFD.cFileName;
        cstrDir.MakeLower();
        if ( cstrDir.Find( cstrFile ) == -1 )
        {
            continue;
        }

        cstrDir.TrimLeft();
        cstrDir.TrimRight();

        CString cstrSize, cstrDate, cstrTime, cstrName, cstrType;
        //1
        nIndex = cstrDir.Find( ' ' );
        if ( nIndex != -1 )
        {
            cstrSize = cstrDir.Left( nIndex );
            cstrDir = cstrDir.Mid( nIndex );
        }
        else
        {
            continue;
        }

        //2
        cstrDir.TrimLeft();
        nIndex = cstrDir.Find(' ');
        if ( nIndex != -1 )
        {
            cstrDir = cstrDir.Mid( nIndex );
        }
        else
        {
            continue;
        }

        //3
        cstrDir.TrimLeft();
        nIndex = cstrDir.Find(' ');
        if ( nIndex != -1 )
        {
            cstrDir = cstrDir.Mid( nIndex );
        }
        else
        {
            continue;
        }

        //4
        cstrDir.TrimLeft();
        nIndex = cstrDir.Find(' ');
        if ( nIndex != -1 )
        {
	        cstrName = cstrDir.Left( nIndex );
        }
        else
        {
	        cstrName = cstrDir;
        }

        if ( cstrName == _T('.') || cstrName == _T("..") )
        {
            continue;
        }

        if ( cstrRemoteFile.Find( cstrName ) != -1 )
        {			
            InternetCloseHandle( hFileConnection );
            InternetCloseHandle( hConnect );
            InternetCloseHandle( hSession );
            return _ttol( cstrSize );
        }
	}

    InternetCloseHandle( hFileConnection );
    InternetCloseHandle( hConnect );
    InternetCloseHandle( hSession );

    return -1;
}

/*=============================================================================
函 数 名:PostMsg
功    能:删除FTP文件
参    数:LPCTSTR aszRemoteFile          [in]    FTP文件名
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2012/07/19  4.7     邹俊龙    创建
=============================================================================*/
BOOL32 CFtpCtrl::DeleteRemoteFile( LPCTSTR aszRemoteFile )
{
	if ( !ConnectSrv() )
	{
        EndFtpFile();
        return FALSE;
	}
	BOOL32 bRet = FtpDeleteFile( GetCurrentConnect(), aszRemoteFile );
	EndFtpFile();
	return bRet;
}

/*=============================================================================
函 数 名:PostMsg
功    能:消息发送
参    数:WPARAM wParam                  [in]    消息子类型
         LPARAM lParam                  [in]    消息参数
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/10/08  4.0     王昊    创建
=============================================================================*/
void CFtpCtrl::PostMsg(WPARAM wParam, LPARAM lParam /* = 0 */)
{
	if ( m_pMsgDeal != 0 )
	{
		m_pMsgDeal->OnMessage( wParam, lParam );
	}
	
    if ( m_hWnd != 0 )
    {
        PostMessage( m_hWnd, m_dwEventId, wParam, lParam );
    }
}


BOOL32 CFtpCtrl::RenameFtpFile( LPCTSTR pszRemoteTempFile, LPCTSTR pszRemoteFile )
{
	HINTERNET nRet = GetCurrentConnect();
	BOOL32 bRet = FtpRenameFile( GetCurrentConnect(), pszRemoteTempFile, pszRemoteFile );

	if ( NULL == GetCurrentConnect() )
	{
		EndFtpFile();
	}

	return bRet;
}

BOOL32 CFtpCtrl::FindfFtpFile( LPCTSTR pszRemotePath, LPCTSTR pstrRemoteName )
{
	if ( ConnectSrv() == FALSE )
	{
		EndFtpFile();
		return FALSE ;
	}

	BOOL bRe = FtpSetCurrentDirectory( m_hConnect, pszRemotePath );
	if ( !bRe )
	{
		return FALSE;	
	}

	WIN32_FIND_DATA pData;
	HINTERNET hFind;

	hFind = FtpFindFirstFile( m_hConnect, /*"*.*"*/pstrRemoteName, &pData, 0, 0 );
	if (!hFind)   
	{
		InternetCloseHandle(hFind);
		return FALSE;
	}

	InternetCloseHandle(hFind);
	return TRUE;
}

//设置远端文件名字，用于获取远端文件大小
void CFtpCtrl::SetRemoteFileName(LPCTSTR pszRemoteFileName)
{
    _tcsncpy( m_aszRemoteFile, pszRemoteFileName, _countof (m_aszRemoteFile) - 1 );
}
