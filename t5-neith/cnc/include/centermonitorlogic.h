/** @defgroup 中控显示器
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2015-3-31
 */
#pragma once

class CCenterMonitorLogic : public CNotifyUIImpl, public Singleton<CCenterMonitorLogic> 
{
public:
	CCenterMonitorLogic(void);
	~CCenterMonitorLogic(void);
	//更新显示器状态
	bool updateMonitorState();
protected:
    /** 初始化消息 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnInit(TNotifyUI& msg);
	/** 点击显示屏check
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnCheckScreenSel(TNotifyUI& msg);
	/** 点击空调check
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnCheckAircon(TNotifyUI& msg);

	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** 点击台标条目
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnScreenMonitorItemClick(TNotifyUI& msg);
	/** 点击横幅条目 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnScreenAirconItemClick(TNotifyUI& msg);
	/** AC通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnMonitorPowrInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** AC响应
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnMonitorStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** Monitor通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnACStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnSelectAirInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnAirPowerInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** Monitor响应
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnSeleteMonitorInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 台标设置
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnOpFS(TNotifyUI& msg);
	bool OnOpFView(TNotifyUI& msg);
	bool OnOpStandard(TNotifyUI& msg);
	bool OnOpPTP(TNotifyUI& msg);
	bool OpVStandard(TNotifyUI& msg);
	bool OpVUser(TNotifyUI& msg);
	bool OpVPC(TNotifyUI& msg);
	bool OpVTV(TNotifyUI& msg);
	bool OnOpHDMI1(TNotifyUI& msg);
	bool OnOpHDMI2(TNotifyUI& msg);
	bool OnOpHDMI3(TNotifyUI& msg);
	bool OnOpHDMI4(TNotifyUI& msg);
	bool OnOpYPbPr(TNotifyUI& msg);
	bool OnOpCVBs1(TNotifyUI& msg);
	bool OnOpCVBs2(TNotifyUI& msg);
	/** 横幅设置
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnOpSPC(TNotifyUI& msg);
	bool OnOpVGA(TNotifyUI& msg);
	bool OnOpCold(TNotifyUI& msg);
	bool OnOpHot(TNotifyUI& msg);
	bool OnOpWind(TNotifyUI& msg);
	bool OnOpWet(TNotifyUI& msg);
	/** 空调应用到全部
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnAirAll(TNotifyUI& msg);
	//空调湿度调节
	bool OnBtnTempPlus(TNotifyUI& msg);
	bool OnBtnTempMinus(TNotifyUI& msg);
	//空调风量调节
	bool OnBtnWindPlus(TNotifyUI& msg);
	bool OnBtnWindMinus(TNotifyUI& msg);
	bool OnBtnWindAuto(TNotifyUI& msg);

    //显示器
    bool OnDisPlayShowNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	
	//更新空调窗口状态
	bool updateACState(CListContainerElementUI *pAircondListContainer, TCentreACCfg tCentreACCfg, u32 dwIndex);
	APP_DECLARE_MSG_MAP()
		

private:

	static const String m_strSldTab;			 //菜单Tab

	int m_dwMonitorScreenSelId;   //显示器
	int m_dwAirconScreenSelId;   //空调

	map<u16, bool>       m_mapIsMonitor;     // 记录屏是否开启Monitor
	map<u16, bool>       m_mapIsAirCon;   // 记录屏是否开启AC

	TCentreTVCfg          m_atModitorCfg[MAX_CENTRETV_NUM];//显示器设置	 

	vector<TCentreACCfg> m_vecTCentreACCfg;//空调信息

    bool m_bDisplayShow;//显示器显示
};