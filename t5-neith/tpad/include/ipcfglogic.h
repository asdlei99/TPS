/** @defgroup �������������߼���Ԫ
 *  @version V1.1.5
 *  @author  Ф��Ȼ
 *  @date    2016.9.6
 */
#pragma once

#include "netadapter.h"

enum EmNetCfgTabID
{
    emTabID_WifiCfg = 0,
    emTabID_IpCfg,
};

class CIpCfgLogic : public CNotifyUIImpl, public Singleton<CIpCfgLogic> 
{
public:
    CIpCfgLogic(void);
    ~CIpCfgLogic(void);

    void ReFreshIpCfg(); 
    //����UI�ϵ�IP������PC
    BOOL SetPc( TIpConfig& tIpCfg ); 

    bool OnBtnCancelIp(TNotifyUI& msg);

protected:
    /** ���ڴ��� 
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnCreate(TNotifyUI& msg);

	/** ��ʼ����Ϣ 
	*  @param[in] 
	*  @return 
	*/
	bool OnInit(TNotifyUI& msg);

    /** ���� 
	*  @param[in] 
	*  @return 
	*/
    bool OnBtnBack(TNotifyUI& msg);

    bool OnTabWifiCfg(TNotifyUI& msg);

    bool OnTabIpCfg(TNotifyUI& msg);
   
    bool OnBtnSaveIp(TNotifyUI& msg);

    bool OnCheckAutoIp(TNotifyUI& msg);

    bool OnCheckAutoDns(TNotifyUI& msg);

    //��ȡ����IP����
    bool GetIpCfgFrmUI( TIpConfig& tIpCfg );
    //����pc��IP������UI
    void UpdateUI( TIpConfig& tIpCfg );

    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);
   
    CNetworkAdapter* GetIPCfg() { return m_pNetCfg; }

    APP_DECLARE_MSG_MAP()

public:
    CNetworkAdapter *m_pNetCfg;

    TIpConfig      m_tLocalIp;        ///<����IP��Ϣ
    TIpConfig      m_tAUiIpCfg; 
};

