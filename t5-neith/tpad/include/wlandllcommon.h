#ifndef WLANDLLCOMMON_H
#define WLANDLLCOMMON_H

//#include "wlanapi.h"

#define WM_WLAN_CONNECT_SUCCED      ( WM_USER + 3000 )
#define WM_WLAN_CONNECT_FAILED      ( WM_WLAN_CONNECT_SUCCED + 1 )
#define WM_WLAN_DISCONT             ( WM_WLAN_CONNECT_FAILED + 1 )
#define WM_WLAN_NOTAVAILABLE	    ( WM_WLAN_DISCONT + 1 )
#define WM_WLAN_CONNECT_ING         ( WM_WLAN_NOTAVAILABLE + 1 )
#define WM_WLAN_SCAN_RESULT         ( WM_WLAN_CONNECT_ING + 1 )
//音量变化消息
#define WM_VOLUMECTRL_CHANGE        ( WM_WLAN_SCAN_RESULT + 1 )   

#define BSSTYPE_INFRASTRUCTURE          1
#define BSSTYPE_ADHOC                   2

#define MAX_WIFI_NUM                    30

#ifndef DLL_EXPORTS
#define DLL_DECL __declspec(dllexport)
#else
#define DLL_DECL __declspec(dllimport)
#endif

typedef struct tagWlanInfo 
{
	char	m_chrSsid[32];           //网络名称
	BOOL    m_bEnableSect;           //是否加密
	int     m_nQuality;              //信号强度
	int		m_dotBssType;            //网络结构
	int		m_dotTypeOfAuth;         //加密类型
	int     m_dotTyprOfCipher;       //密钥算法
	BOOL    m_bConnected;            //是否已连接
    WCHAR   strProfileName[256];
    DOT11_SSID dot11Ssid;

	tagWlanInfo()
	{
		memset( this, 0, sizeof(tagWlanInfo) );
	}
	
}TWlanInfo, *PWlanInfo;


//注册回调函数
DLL_DECL VOID APIWlanReg( HWND hWnd );

//扫描网络驱动信息，获取可用的无线网络
DLL_DECL BOOL APIWlanDriverScan();
//扫描网络信息
DLL_DECL int APIWlanScan( TWlanInfo tWlanInfo[MAX_WIFI_NUM] ); 

//获取当前可用网络信息
DLL_DECL VOID APIWlanInit();

//导入配置文件（xml）
DLL_DECL VOID APIWlanCreateProfile( char* pchrSsid );

//连接指定网络
DLL_DECL VOID APIWlanConnect( char* pchrUISsid, char* pchrKey );

//断开当前连接
DLL_DECL VOID APIWlanDisConn();

//退出Wifi设置
DLL_DECL VOID APIWlanQuit();

//Wifi是否连接上
DLL_DECL BOOL APIWlanIsConn();

//获取连接上的wifi信息
DLL_DECL BOOL APIWlanGetConnInfo( TWlanInfo& tWlanInfo );

//新建Wifi连接 (网络名称、加密类型、密钥算法、密码)
DLL_DECL VOID APIWlanNewConnect( char* pchrUISsid, int nTypeOfAut, int nTyprOfCipher, char* pchrKey );

//启用/关闭wifi
DLL_DECL VOID APIWlanEnableWifi( BOOL bEnable );

//wifi是否启用
DLL_DECL BOOL APIWlanIsWifiEnable();

//Wlan配置文件是否已存在
DLL_DECL BOOL APIWlanIsHaveProfile( char* pchProfileName );

//删除Wlan配置文件
DLL_DECL VOID APIWlanDeleteProfile( char* pchProfileName );

//不创建配置文件,直接连接
DLL_DECL VOID APIWlanDirectConnect( char* pchUISsid );

//////////////////////////////////////////////////////////////////////////////////////////////////////
//音量控制接口
DLL_DECL VOID APIInitVolumeCtrl();

//注册回调窗口
DLL_DECL VOID APIRegVolumeCtrlWnd( HWND hWnd );

//静音状态
DLL_DECL VOID APIGetMute( BOOL &bMute );
DLL_DECL VOID APISetMute( BOOL bMute );

//音量大小
DLL_DECL VOID APIGetMasterVolume( int &nVolume );
DLL_DECL VOID APISetMasterVolume( int nVolume );

DLL_DECL VOID APIUninitVolumeCtrl();

#endif