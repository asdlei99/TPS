/** @defgroup 主窗口逻辑单元 
 *  @version V1.1.5
 *  @author  肖楚然
 *  @date    2016.6.27
 */
#if !defined(AFX_MAINFRAMELOGIC_H_)
#define AFX_MAINFRAMELOGIC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMainFrameLogic : public CNotifyUIImpl, public Singleton<CMainFrameLogic> 
{
public:
	CMainFrameLogic();
	~CMainFrameLogic();

protected:
	/** 窗口创建 
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnCreate(TNotifyUI& msg);

	/** 初始化消息 
	 *  @param[in] 
	 *  @node 
	 *  @return 
     */
    bool OnInit(TNotifyUI& msg);

	bool OnDeviceChange(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //链接成功
    bool OnConnectRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //断链
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//升级
	bool OnUpdateSysCmd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//退出
	bool OnBtnExit(TNotifyUI& msg);
	//帮助文档
	bool OnBtnHelp(TNotifyUI& msg);
	//调出cnc系统设置
	bool OnBtnSysConfig(TNotifyUI& msg);
	//更新wifi状态
	bool OnUpdateWifiState(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//电源变化消息
	bool OnPowerBroadcast(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//中控待机
	bool OnCentreSleepNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

	bool OnDisconnectClear(WPARAM wParam, LPARAM lParam, bool& bHandle);

	bool OnCncNoReconnectNty(WPARAM wParam, LPARAM lParam, bool& bHandle);

    APP_DECLARE_MSG_MAP()
public:

	/** 更新时间显示
	 *  @param[in] 
	 *  @return 
	 */
	void UpdateTime();

    /** ini文件路径
	 *  @param[in] 
	 *  @return 
	 */
    CString GetIniFilePath(CString StrAppName = _T("tpad"));

	//标题栏部分
	void UpdateSysTime(); //更新系统时间

	void UpdateWifiState(); //更新wifi图标

	void UpdatePowerState();//更新电源状态

	bool AutoLogin(bool bSuc);//自动登录后处理

    void ShowLoginPage();

    /** 设置是否主动退出
	 *  @return 
	 */
    void SetActiveExit( BOOL bActve );

    void RegDeviceChangeMsg();

    //win8系统音量键响应
    void OnThinkpadVolumeLow(int nStep = 1);
    void OnThinkpadVolumeAdd(int nStep = 1);		

	void ReConnectCns();

    void ShowLoginBtn();
private:
    BOOL    m_bActiveExit;      //是否主动退出
    BOOL    m_bRegDeviceChange; //是否响应DeviceChange消息
    int     m_nSysVol;          //系统音量
	Window* m_pKeyboard;
};

#endif // !defined(AFX_MAINFRAMELOGIC_H_)