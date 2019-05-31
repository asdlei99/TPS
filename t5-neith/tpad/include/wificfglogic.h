/** @defgroup wifi网络配置逻辑单元
 *  @version V1.1.5
 *  @author  肖楚然
 *  @date    2016.9.6
 */
#pragma once

#include "netadapter.h"

//加密模式
enum EM_WifiEncryptMode
{
    em_Wep_open = 1,
    em_Wep_share = 2,	
    em_WPA = 4,
    em_WPA2 = 7,
}; 

//加密算法
enum EM_WifiEncryptType
{
    em_Cipher_None = 0x00,
    em_Cipher_TKIP = 0x02,
    em_Cipher_AES = 0x04,
    em_Cipher_WEP = 0x101,
};



class CWifiCfgLogic : public CNotifyUIImpl, public Singleton<CWifiCfgLogic> 
{
public:
    CWifiCfgLogic(void);
    ~CWifiCfgLogic(void);

    void ReFreshIpCfg(); 
    //根据UI上的IP来设置PC
    BOOL SetPc( TIpConfig& tIpCfg );

    bool OnWiFiConnectTimeOut();

    void ReConnectLastWifi();

	void ShowWifiConnectModalTrue();

protected:
    /** 窗口创建 
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnCreate(TNotifyUI& msg);

    bool OnInit(TNotifyUI& msg);


    bool OnCheckWifiOpen(TNotifyUI& msg);

    bool OnBtnRefreshWifi(TNotifyUI& msg);

    bool OnBtnCfgWifiIp(TNotifyUI& msg);

    bool OnClickWifiItem(TNotifyUI& msg);

    bool OnBtnAddWifi(TNotifyUI& msg);

    bool OnBtnConnectWifi(TNotifyUI& msg);
    bool OnBtnConnectBack(TNotifyUI& msg);

    bool OnBtnCancelWifiAdd(TNotifyUI& msg);
    bool OnBtnSaveWifiAdd(TNotifyUI& msg);

    bool OnCheckSafe(TNotifyUI& msg);
   
    bool OnBtnSaveWifiIp(TNotifyUI& msg);

    bool OnWifiCheckAutoIp(TNotifyUI& msg);
    bool OnWifiCheckAutoDns(TNotifyUI& msg);

    /** 刷新wifi列表 
	*  @return
	*/
    void RefreshWifiList();

    //根据加密类型 检测wifi的密码是否合法
    BOOL32 CheckWifiPswd( int nMode, CString strPswd , CString& strErr);

    void ShowWifiConnectModal();

    bool OnWiFiConnectSuccess(WPARAM wParam, LPARAM lParam, bool& bHandle);
    bool OnWiFiConnectFailed(WPARAM wParam, LPARAM lParam, bool& bHandle);
    bool OnWiFiDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnWiFiScanResult(WPARAM wParam, LPARAM lParam, bool& bHandle);

    APP_DECLARE_MSG_MAP()

public:
    bool OnBtnCancelWifiIp(TNotifyUI& msg);

protected: //wifi ip配置
    void InitIpCfg();

    bool GetIpCfgFrmUI( TIpConfig& tIpCfg );

    //根据pc的IP来设置UI
    void UpdateUI( TIpConfig& tIpCfg );

    CNetworkAdapter* GetIPCfg() { return m_pNetCfg; }

private:
    TWlanInfo            m_tWlanInfo[WIFI_MAX_SEARCH_NUM];

    vector<TWifiItem>    m_vctWifiList;

    TWifiItem            m_tSelItem;        //当前选中条目

	BOOL                 m_bIsScanning;     //wifi正在经行扫描
    BOOL                 m_bWaitWifi;       //等待wifi连接回复
    BOOL                 m_bWaitReConnect;  //等待重连
    s8                   m_achConnectName[TP_MAX_ALIAS_LEN_CNC+1];    //正在连接的wifi名
    s8                   m_achLastWifiName[TP_MAX_ALIAS_LEN_CNC+1];   //已连接上的wifi名

public:
    CNetworkAdapter *m_pNetCfg;
    TIpConfig      m_tLocalIp;        ///wifi IP信息
    TIpConfig      m_tAUiIpCfg;
};

