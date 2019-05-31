/** @defgroup 有线网络配置逻辑单元
 *  @version V1.1.5
 *  @author  肖楚然
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
    //根据UI上的IP来设置PC
    BOOL SetPc( TIpConfig& tIpCfg ); 

    bool OnBtnCancelIp(TNotifyUI& msg);

protected:
    /** 窗口创建 
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnCreate(TNotifyUI& msg);

	/** 初始化消息 
	*  @param[in] 
	*  @return 
	*/
	bool OnInit(TNotifyUI& msg);

    /** 返回 
	*  @param[in] 
	*  @return 
	*/
    bool OnBtnBack(TNotifyUI& msg);

    bool OnTabWifiCfg(TNotifyUI& msg);

    bool OnTabIpCfg(TNotifyUI& msg);
   
    bool OnBtnSaveIp(TNotifyUI& msg);

    bool OnCheckAutoIp(TNotifyUI& msg);

    bool OnCheckAutoDns(TNotifyUI& msg);

    //获取界面IP配置
    bool GetIpCfgFrmUI( TIpConfig& tIpCfg );
    //根据pc的IP来设置UI
    void UpdateUI( TIpConfig& tIpCfg );

    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);
   
    CNetworkAdapter* GetIPCfg() { return m_pNetCfg; }

    APP_DECLARE_MSG_MAP()

public:
    CNetworkAdapter *m_pNetCfg;

    TIpConfig      m_tLocalIp;        ///<本地IP信息
    TIpConfig      m_tAUiIpCfg; 
};

