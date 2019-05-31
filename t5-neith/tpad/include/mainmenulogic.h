/** @defgroup 主菜单逻辑单元 
 *  @version V1.1.5
 *  @author  肖楚然
 *  @date    2016.7.11
 */

#pragma once
class CMainMenuLogic : public CNotifyUIImpl, public Singleton<CMainMenuLogic>
{
public:
	CMainMenuLogic(void);
	~CMainMenuLogic(void);

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
	/** 点击会场管理 
	 *  @param[in] 
	 *  @return 
	 */
    bool OnBtnCnsManage(TNotifyUI& msg);
    /** 点击中控管理 
	 *  @param[in] 
	 *  @return 
	 */
    bool OnBtnCenterCtrl(TNotifyUI& msg);
    /** 点击文件管理 
	 *  @param[in] 
	 *  @return 
	 */
    bool OnBtnFileManage(TNotifyUI& msg);
    /** 点击浏览器 
	 *  @param[in] 
	 *  @return 
	 */
    bool OnBtnBrowser(TNotifyUI& msg);
    /** 点击数据会议 
	 *  @param[in] 
	 *  @return 
	 */
    bool OnBtnDataConf(TNotifyUI& msg);
    /** 点击收看演示 
    *  @param[in] 
	 *  @return 
	 */
    bool OnBtnWatchDual(TNotifyUI& msg);
    //会议状态
    bool OnConfStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//双流接收状态
	bool OnDualRecvStateNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
public:
	//更新menu
	void UpdateMainMenu();
	APP_DECLARE_MSG_MAP()
private:
	HWND m_hWnd;     //g_strMainMenuDlg句柄
	bool m_bDual;
};

