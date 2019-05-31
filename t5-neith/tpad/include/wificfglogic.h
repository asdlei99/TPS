/** @defgroup wifi���������߼���Ԫ
 *  @version V1.1.5
 *  @author  Ф��Ȼ
 *  @date    2016.9.6
 */
#pragma once

#include "netadapter.h"

//����ģʽ
enum EM_WifiEncryptMode
{
    em_Wep_open = 1,
    em_Wep_share = 2,	
    em_WPA = 4,
    em_WPA2 = 7,
}; 

//�����㷨
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
    //����UI�ϵ�IP������PC
    BOOL SetPc( TIpConfig& tIpCfg );

    bool OnWiFiConnectTimeOut();

    void ReConnectLastWifi();

	void ShowWifiConnectModalTrue();

protected:
    /** ���ڴ��� 
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
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

    /** ˢ��wifi�б� 
	*  @return
	*/
    void RefreshWifiList();

    //���ݼ������� ���wifi�������Ƿ�Ϸ�
    BOOL32 CheckWifiPswd( int nMode, CString strPswd , CString& strErr);

    void ShowWifiConnectModal();

    bool OnWiFiConnectSuccess(WPARAM wParam, LPARAM lParam, bool& bHandle);
    bool OnWiFiConnectFailed(WPARAM wParam, LPARAM lParam, bool& bHandle);
    bool OnWiFiDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnWiFiScanResult(WPARAM wParam, LPARAM lParam, bool& bHandle);

    APP_DECLARE_MSG_MAP()

public:
    bool OnBtnCancelWifiIp(TNotifyUI& msg);

protected: //wifi ip����
    void InitIpCfg();

    bool GetIpCfgFrmUI( TIpConfig& tIpCfg );

    //����pc��IP������UI
    void UpdateUI( TIpConfig& tIpCfg );

    CNetworkAdapter* GetIPCfg() { return m_pNetCfg; }

private:
    TWlanInfo            m_tWlanInfo[WIFI_MAX_SEARCH_NUM];

    vector<TWifiItem>    m_vctWifiList;

    TWifiItem            m_tSelItem;        //��ǰѡ����Ŀ

	BOOL                 m_bIsScanning;     //wifi���ھ���ɨ��
    BOOL                 m_bWaitWifi;       //�ȴ�wifi���ӻظ�
    BOOL                 m_bWaitReConnect;  //�ȴ�����
    s8                   m_achConnectName[TP_MAX_ALIAS_LEN_CNC+1];    //�������ӵ�wifi��
    s8                   m_achLastWifiName[TP_MAX_ALIAS_LEN_CNC+1];   //�������ϵ�wifi��

public:
    CNetworkAdapter *m_pNetCfg;
    TIpConfig      m_tLocalIp;        ///wifi IP��Ϣ
    TIpConfig      m_tAUiIpCfg;
};

