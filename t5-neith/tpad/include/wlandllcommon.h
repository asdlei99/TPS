#ifndef WLANDLLCOMMON_H
#define WLANDLLCOMMON_H

//#include "wlanapi.h"

#define WM_WLAN_CONNECT_SUCCED      ( WM_USER + 3000 )
#define WM_WLAN_CONNECT_FAILED      ( WM_WLAN_CONNECT_SUCCED + 1 )
#define WM_WLAN_DISCONT             ( WM_WLAN_CONNECT_FAILED + 1 )
#define WM_WLAN_NOTAVAILABLE	    ( WM_WLAN_DISCONT + 1 )
#define WM_WLAN_CONNECT_ING         ( WM_WLAN_NOTAVAILABLE + 1 )
#define WM_WLAN_SCAN_RESULT         ( WM_WLAN_CONNECT_ING + 1 )
//�����仯��Ϣ
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
	char	m_chrSsid[32];           //��������
	BOOL    m_bEnableSect;           //�Ƿ����
	int     m_nQuality;              //�ź�ǿ��
	int		m_dotBssType;            //����ṹ
	int		m_dotTypeOfAuth;         //��������
	int     m_dotTyprOfCipher;       //��Կ�㷨
	BOOL    m_bConnected;            //�Ƿ�������
    WCHAR   strProfileName[256];
    DOT11_SSID dot11Ssid;

	tagWlanInfo()
	{
		memset( this, 0, sizeof(tagWlanInfo) );
	}
	
}TWlanInfo, *PWlanInfo;


//ע��ص�����
DLL_DECL VOID APIWlanReg( HWND hWnd );

//ɨ������������Ϣ����ȡ���õ���������
DLL_DECL BOOL APIWlanDriverScan();
//ɨ��������Ϣ
DLL_DECL int APIWlanScan( TWlanInfo tWlanInfo[MAX_WIFI_NUM] ); 

//��ȡ��ǰ����������Ϣ
DLL_DECL VOID APIWlanInit();

//���������ļ���xml��
DLL_DECL VOID APIWlanCreateProfile( char* pchrSsid );

//����ָ������
DLL_DECL VOID APIWlanConnect( char* pchrUISsid, char* pchrKey );

//�Ͽ���ǰ����
DLL_DECL VOID APIWlanDisConn();

//�˳�Wifi����
DLL_DECL VOID APIWlanQuit();

//Wifi�Ƿ�������
DLL_DECL BOOL APIWlanIsConn();

//��ȡ�����ϵ�wifi��Ϣ
DLL_DECL BOOL APIWlanGetConnInfo( TWlanInfo& tWlanInfo );

//�½�Wifi���� (�������ơ��������͡���Կ�㷨������)
DLL_DECL VOID APIWlanNewConnect( char* pchrUISsid, int nTypeOfAut, int nTyprOfCipher, char* pchrKey );

//����/�ر�wifi
DLL_DECL VOID APIWlanEnableWifi( BOOL bEnable );

//wifi�Ƿ�����
DLL_DECL BOOL APIWlanIsWifiEnable();

//Wlan�����ļ��Ƿ��Ѵ���
DLL_DECL BOOL APIWlanIsHaveProfile( char* pchProfileName );

//ɾ��Wlan�����ļ�
DLL_DECL VOID APIWlanDeleteProfile( char* pchProfileName );

//�����������ļ�,ֱ������
DLL_DECL VOID APIWlanDirectConnect( char* pchUISsid );

//////////////////////////////////////////////////////////////////////////////////////////////////////
//�������ƽӿ�
DLL_DECL VOID APIInitVolumeCtrl();

//ע��ص�����
DLL_DECL VOID APIRegVolumeCtrlWnd( HWND hWnd );

//����״̬
DLL_DECL VOID APIGetMute( BOOL &bMute );
DLL_DECL VOID APISetMute( BOOL bMute );

//������С
DLL_DECL VOID APIGetMasterVolume( int &nVolume );
DLL_DECL VOID APISetMasterVolume( int nVolume );

DLL_DECL VOID APIUninitVolumeCtrl();

#endif