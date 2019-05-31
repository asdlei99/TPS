/*=======================================================================
模块名      : 网管公用模块库
文件名      : nmscommon.cpp
相关文件    : 
文件实现功能: 
作者        : 李洪强
版本        : V4.0  Copyright(C) 2003-2005 Suzhou Keda Technology Co.Ltd
                    All rights reserved.
-------------------------------------------------------------------------
修改记录:
日  期      版本  修改人  修改内容
2004/07/16  3.0   李洪强  创建
2004/12/18  3.5   李洪强  增加TplArray模板类
2005/01/26  3.5   李洪强  修改TplArray插入操作的bug
=======================================================================*/

#include "stdafx.h"
#include "nmscommon.h"
#include "vccommon.h"
#include "AES.h"

#define NMSCOMMON_VER   (LPCSTR)"nmscommonver version: 40.30.01.01.20061020"

//////////////////////////////////////////////////////////////////////////
//
//     安全注册ocx控件的辅助函数
//
// Helper function to create a component category and associated description
HRESULT CreateComponentCategory(CATID catid, WCHAR *catDescription)
{
    ICatRegister *pcr = NULL;
    HRESULT hr = S_OK;

    hr = CoCreateInstance( CLSID_StdComponentCategoriesMgr, 
                           NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister,
                           (void**)&pcr );
    if ( FAILED( hr ) )
    {
        return hr;
    }

    // Make sure the HKCR\Component Categories\{..catid...}
    // key is registered
    CATEGORYINFO catinfo;
    catinfo.catid = catid;
    catinfo.lcid = 0x0409; // english

    // Make sure the provided description is not too long.
    // Only copy the first 127 characters if it is
    size_t nLen = wcslen(catDescription);
    if ( nLen > 127 )
    {
        nLen = 127;
    }

    wcsncpy( catinfo.szDescription, catDescription, nLen );
    // Make sure the description is null terminated
    catinfo.szDescription[nLen] = '\0';

    hr = pcr->RegisterCategories( 1, &catinfo );
    pcr->Release();

    return hr;
}

// Helper function to register a CLSID as belonging to a component category
HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid)
{
    // Register your component categories information.
    ICatRegister* pcr = NULL;
    HRESULT hr = S_OK;

    hr = CoCreateInstance( CLSID_StdComponentCategoriesMgr, 
                           NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister,
                           (void**)&pcr );
    if ( SUCCEEDED( hr ) )
    {
        // Register this category as being "implemented" by
        // the class.
        CATID rgcatid[1];
        rgcatid[0] = catid;
        hr = pcr->RegisterClassImplCategories( clsid, 1, rgcatid );
    }

    if ( pcr != NULL )
    {
        pcr->Release();
    }

    return hr;
}

// Helper function to unregister a CLSID as belonging to a component category
HRESULT UnRegisterCLSIDInCategory(REFCLSID clsid, CATID catid)
{
    ICatRegister* pcr = NULL;
    HRESULT hr = S_OK;

    hr = CoCreateInstance( CLSID_StdComponentCategoriesMgr, 
                           NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister,
                           (void**)&pcr );
    if ( SUCCEEDED( hr ) )
    {
        // Unregister this category as being "implemented" by
        // the class.
        CATID rgcatid[1];
        rgcatid[0] = catid;
        hr = pcr->UnRegisterClassImplCategories( clsid, 1, rgcatid );
    }

    if (pcr != NULL)
    {
        pcr->Release();
    }

    return hr;
}

/*=============================================================================
函 数 名:nmscommonver
功    能:打印NmsCommon库的版本号
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2004/09/13  3.5     李洪强  创建
=============================================================================*/
API void nmscommonver(void)
{
    OspPrintf( TRUE, FALSE, "%s compile time: %s %s\n", NMSCOMMON_VER,
               __DATE__, __TIME__ );
}

/*=============================================================================
函 数 名:GetConfBitrate
功    能:获取会议码率
参    数:u32 **ppdwBitrate              [out]   会议码率数组
         s32 &nNum                      [out]   数组大小
         u32 dwMCUType                  [in]    MCU类型
注    意:不需要给ppdwBitrate分配空间, 且不能delete ppdwBitrate
         8000C MCU只支持到4M
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2004/09/29  3.5     王昊    创建
2007/04/25  4.0     王廖荣  修改
=============================================================================*/
void GetConfBitrate(u32 **ppdwBitrate, s32 &nNum, u32 dwMCUType)
{
	static u32 adwBitrate8M[] = {384,
							512,
							768,
							1024,
							1216,
							1536,
							1792,
							2048,
							3072,
							4096,
							5120,
							6144,
							7168,
							8128};

	static u32 adwBitrate4M[] = {384,
							512,
							768,
							1024,
							1216,
							1536,
							1792,
							2048,
							3072,
							4096};

    if( MCU_TYPE_KDV8000C == dwMCUType)
    {
        *ppdwBitrate = adwBitrate4M;
        nNum = sizeof (adwBitrate4M) / sizeof (u32);
    }
	else
    {
        *ppdwBitrate = adwBitrate8M;
        nNum = sizeof (adwBitrate8M) / sizeof (u32);
    }
}

CString ExpandEnvPathString( LPCTSTR lpszPath )
{
	static TCHAR abyPath[32768]; 
	ExpandEnvironmentStrings( lpszPath, abyPath, _countof(abyPath) );
	return abyPath;
}


/*=============================================================================
函 数 名:GetModuleFullPath
功    能:获取模块所在文件夹全路径, 包括最后的\
参    数:无
注    意:例如 C:\
返 回 值:文件夹字符串
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2004/10/26  3.5     王昊    创建
=============================================================================*/
CString GetModuleFullPath(void)
{
	TCHAR achDllName[32768] = _T("");
	CString csPath = _T("");

	//AfxGetInstanceHandle()可能获取失败
// 	GetModuleFileName( AfxGetInstanceHandle(), achDllName, MAX_PATH);

	MEMORY_BASIC_INFORMATION mbi;   
	static int dummy; 
	u32 dwLength = sizeof(mbi); 
	if ( dwLength == VirtualQuery( &dummy, &mbi, dwLength ) )
	{
		GetModuleFileName( reinterpret_cast<HMODULE>(mbi.AllocationBase), achDllName, _countof(achDllName) ); 
		size_t nBuffLen = GetLongPathName( achDllName, 0, 0 );
		if ( nBuffLen == _tcslen( achDllName ) )
		{
			csPath = achDllName;
		}
		else
		{
			TCHAR* pChar = new TCHAR[nBuffLen + 1];
			ZeroMemory( pChar, sizeof(TCHAR) * ( nBuffLen + 1 ) );
			GetLongPathName( achDllName, pChar, nBuffLen );
			csPath = pChar;
			delete[] pChar;
		}		
	}
    
	csPath = csPath.Left( csPath.ReverseFind(_T('\\')) + 1 );

	return csPath;
}

/*=============================================================================
函 数 名:ModuleRegToOsp

功    能:向OSP注册本模块
参    数:无
注    意:无
返 回 值:成功：TRUE; 失败：FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2004/10/26  3.5     王昊    创建
=============================================================================*/
BOOL32 ModuleRegToOsp(void)
{
	TCHAR achDllName[MAX_PATH] = _T("");
	GetModuleFileName( AfxGetInstanceHandle(), achDllName, _countof(achDllName) );
	return OspRegistModule( CT2A( achDllName ) );
}

/*=============================================================================
函 数 名:GetUrl
功    能:获取IE地址栏内容
参    数:const COleControl *pcCtrl          [in]    ocx控件
         CString &cstrUrl                   [out]   地址栏内容
注    意:无
返 回 值:成功:TRUE; 失败:FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/11/08  4.0     王昊    创建
=============================================================================*/
BOOL32 GetUrl(const LPOLECLIENTSITE pClientSite, CString &cstrUrl)
{
    if ( pClientSite == NULL )
    {
        return FALSE;
    }

	IWebBrowser2        *pBrowser = NULL;
    HRESULT             hr = S_OK;
    IServiceProvider    *pIsp1 = NULL;
    IServiceProvider    *pIsp2 = NULL;

    hr = pClientSite->QueryInterface( IID_IServiceProvider,
                                       reinterpret_cast<void**>(&pIsp1) );
    if ( FAILED(hr) )
    {
        return FALSE;
    }

    hr = pIsp1->QueryService( SID_STopLevelBrowser, IID_IServiceProvider,
                              reinterpret_cast<void**>(&pIsp2) );
    if ( FAILED(hr) )
    {
        pClientSite->Release();
        return FALSE;
    }

    hr = pIsp2->QueryService( SID_SWebBrowserApp, IID_IWebBrowser2,
                              reinterpret_cast<void**>(&pBrowser) );
    if ( FAILED(hr) )
    {
        pClientSite->Release();
        pIsp1->Release();
        return FALSE;
    }

    BSTR bstrUrl = NULL;
    pBrowser->get_LocationURL( &bstrUrl );
    cstrUrl = bstrUrl;
    ::SysFreeString( bstrUrl );

    pClientSite->Release();
//     pIsp1->Release();
//     pIsp2->Release();

    return TRUE;
}

/*=============================================================================
函 数 名:EncryptPwd
功    能:密码加密
参    数:LPCSTR lpszPwd                     [in]    原始密码, 最长32位(包括'/0')
         s8 aszEncryptedPwd[64]             [out]   加密密码
算法说明:字符替换
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/11/21  4.0     王昊    创建
2013/06/18	4.7		邹俊龙	修改为AES加密
=============================================================================*/
#define STR_AESKEY "b^dBV%Zzgixr4uaL"

bool EncryptPwd( const s8* lpszPwd, s8 aszEncryptedPwd[64] )
{
	if ( !lpszPwd || strlen( lpszPwd ) > 31 )
	{
		return false;
	}
	// 不足位填充为0
	s8 abyPsw[32];
	strncpy( abyPsw, lpszPwd, 32 );
	AES cAes;
	cAes.setMode( (u8*)STR_AESKEY, len16, len32, false );
	s8 aszTemp[32] = {0};
	u8 len = cAes.cipher( (u8*)abyPsw, (u8*)aszTemp );

	// 一次4字节，一共8次
	for ( int i = 0; i < 8; ++i )
	{
		sprintf( aszEncryptedPwd + (i*8),"%08X", *((u32*)( aszTemp + i*4 ) ) );
	}

	return true;
}

/*=============================================================================
函 数 名:DecryptPwd
功    能:密码解密
参    数:s8 aszEncryptedPwd[64]             [in]    加密密码
         LPSTR lpszPwd                      [out]   原始密码, 最长32位(包括'/0')
算法说明:字符替换
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/11/21  4.0     王昊    创建
2013/06/18	4.7		邹俊龙	修改为AES加密
=============================================================================*/
bool DecryptPwd( const s8 aszEncryptedPwd[64], s8* lpszPwd)
{
	u8 abyPsw[32];
	// 一次4字节，一共8次
	for ( int i = 0; i < 8; ++i )
	{
		sscanf( aszEncryptedPwd + (i*8),"%8X", (u32*)( abyPsw + i*4 ) );
	}

	AES cAes;
	cAes.setMode( (u8*)STR_AESKEY, len16, len32, true );
	s8 aszTemp[32] = {0};
	cAes.invCipher( abyPsw, (u8*)aszTemp );
	strcpy( lpszPwd, aszTemp );
	return true;
}

/*========================================================================
函 数 名：CheckIEBHOAvailable
功    能：检查IE中是否加载了和我们的OCX控件不兼容的插件
注    意：可以在控件的InitInstance()中进行调用，如返回FALSE则控件退出
          例如：
            BOOL CTestApp::InitInstance()
            {
	            BOOL bInit = COleControlModule::InitInstance();

	            if (bInit)
	            {
                    BOOL bBHOAvailable = CheckIEBHOAvailable( 0 );
                    if ( FALSE == bBHOAvailable )
                    {
                        return FALSE;
                    }
	            }

	            return bInit;
            }

参    数：LPCTSTR   [in]    提示信息
返 回 值：TRUE：    没有不兼容的插件或用户选择不卸载相应的插件
          FALSE：   检测到有不兼容的插件，且用户选择卸载相应的插件
相关消息：
--------------------------------------------------------------------------
修改记录：
日      期  版本    修改人  修改内容
2007/11/07  1.0     王廖荣    创建
2013/05/02	4.7		邹俊龙	修改参数，以支持新的多语言机制
							使用循环以支持多个不兼容控件的检测
							修正Unicode下，只能读取到文件路径的第一个字符的问题
========================================================================*/
BOOL32 CheckIEBHOAvailable( LPCTSTR lpszInfo )
{
	// 将来如还有发现不兼容的插件添加到此处
	
	// 检测IE程序中是否已经加载了FlashGet插件
    const TCHAR paszBHO[][50] =
    {
	    
		// 似乎FlashGet的插件会导致程序关闭时，IE弹出0x0000005错误 by zjl;
        _T("FlashGet BHO jccatch.dll")
    };


	const TCHAR paszSubKey[][256] = 
	{
		// jccatch.dll的GUID：FB5DA724-162B-11D3-8B9B-AA70B4B0B524
		_T("CLSID\\{FB5DA724-162B-11D3-8B9B-AA70B4B0B524}\\InprocServer32")
	};

    // 从注册表中读取插件的文件名
    CString strInfo = lpszInfo;
    CString strBHOName;
	CString strModule;

	// 创一个数组，最大个数不超过不兼容插件的个数
	HMODULE* arrayModule = new HMODULE[_countof(paszBHO)];
	memset( arrayModule, 0, sizeof( arrayModule ) );

	s32 nFindNum = 0;
	for ( s32 i = 0; i < _countof( paszSubKey ); ++i )
	{
		HKEY hKey = NULL;
	    LONG lRet = RegOpenKeyEx( HKEY_CLASSES_ROOT, paszSubKey[i],
                              0, KEY_READ, &hKey );

		if ( lRet == ERROR_SUCCESS )
		{
			TCHAR abyPath[MAX_PATH];
			DWORD dwSize = MAX_PATH;
			DWORD dwType = REG_SZ;
			lRet = RegQueryValueEx( hKey, NULL, NULL, &dwType, (LPBYTE)abyPath, &dwSize );
			if ( ERROR_SUCCESS == lRet )
			{
				strBHOName = abyPath;
				s32 nPos = strBHOName.ReverseFind( '\\' );
				strBHOName = strBHOName.Right( strBHOName.GetLength() - nPos - 1 );// .Left(nPos + 1);
			}
		}
		
		// 检查IE是否已经加载了
		HMODULE hModule = GetModuleHandle( strBHOName );

		if ( NULL != hModule )
		{
			arrayModule[ nFindNum ] = hModule;

			// 增加一个提示
			strModule.Format( _T("%d.%s\n"), ++nFindNum, paszBHO[i] );
			strInfo += strModule;
		}
	}

    if ( nFindNum > 0 )
    {
        int dwResult = AfxMessageBox( strInfo, MB_YESNO );
        if ( dwResult == IDNO )
        {
            return TRUE;
        }

		for ( s32 i = 0; i < nFindNum; ++i )
		{
			FARPROC pUninstall = GetProcAddress( arrayModule[i], "DllUnregisterServer" );

			if ( NULL != pUninstall )
			{
				// 卸载插件
				pUninstall();
			}
		}
        return FALSE;
    }
    return TRUE;
}

BOOL32 GetOsVersion( u32& dwMajorVer, u32& dwMinorVer )
{
	OSVERSIONINFO osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	
	if ( GetVersionEx(&osvi) )
	{
		dwMajorVer = osvi.dwMajorVersion;
		dwMinorVer = osvi.dwMinorVersion;
		return TRUE;
	}
	else
	{
		dwMajorVer = 0;
		dwMinorVer = 0;
		return FALSE;
	}
}


/*=============================================================================
  函 数 名： GetIdlePort
  功    能： 获取指定端口区间的一个空闲端口
  算法实现： 
  全局变量： 
  参    数： wStartPort：起始监测端口，dwIP：本地ip，wEndPort：监测结束端口
  返 回 值： 空闲端口值 
=============================================================================*/
u16 GetIdlePort( u32 dwIP, u16 wStartPort, u16 wEndPort )
{
	u16 wPort = wStartPort;
	BOOL32 bContinue = TRUE;
	for (u16 wIndex = 0; bContinue; wIndex++)
	{
		SOCKET ListenSocket;
		ListenSocket = socket(AF_INET, SOCK_DGRAM, 0);
		if (ListenSocket != INVALID_SOCKET) 
		{
			sockaddr_in service;
			service.sin_family = AF_INET;
			service.sin_addr.s_addr = htonl(dwIP);
			wPort = wPort + wIndex;
			service.sin_port = htons(wPort);
			if (bind( ListenSocket, (SOCKADDR*) &service, sizeof(service)) == SOCKET_ERROR) 
			{
				closesocket(ListenSocket);
				//超出wEndPort直接跳出循环,并返回无效端口
				if ( wPort > wEndPort )
				{
					wPort = 0xFFFF;
					bContinue = FALSE;
					break;
				}
				continue;
			}
			closesocket(ListenSocket);
			break;
		}
	}
	return wPort;
}


HWND GetWndByAppName( CString strAppname )
{
    if ( strAppname.IsEmpty() )
    {
        return 0;
    }

    HANDLE  hSem  =  CreateSemaphore(NULL,  1,  1, (LPCTSTR)strAppname );   

    //   信号量存在，则程序已有一个实例运行   
    if (GetLastError()   ==   ERROR_ALREADY_EXISTS)   
    {  		
        //   关闭信号量句柄   
        CloseHandle(hSem);   
        //   寻找先前实例的主窗口   
        HWND   hWndPrevious = ::GetWindow(::GetDesktopWindow(),GW_CHILD);   
        while   (::IsWindow(hWndPrevious))   
        {   
            //   检查窗口是否有预设的标记?   
            //   有，则是我们寻找的主窗   
            if   (::GetProp(hWndPrevious, (LPCTSTR)strAppname))   
            {  
                return   hWndPrevious;   
            }   
            //   继续寻找下一个窗口   
            hWndPrevious   =   ::GetWindow(hWndPrevious,GW_HWNDNEXT); 
        }   
        //   前一实例已存在，但找不到其主窗   
        //   退出本实例   
        return   0;   
    } 

    return 0;
}