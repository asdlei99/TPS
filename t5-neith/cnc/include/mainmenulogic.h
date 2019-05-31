/** @defgroup 主功能目录逻辑单元 
 *  @version V1.1.4
 *  @author  肖楚然
 *  @date    2014.12.11
 */

#pragma once
class CMainMenuLogic : public CNotifyUIImpl, public Singleton<CMainMenuLogic>
{
public:
	CMainMenuLogic(void);
	~CMainMenuLogic(void);

	void OnExtendMainMenu();
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

	/** 点击展开/收起 
	 *  @param[in] 
	 *  @return 
	 */
	bool OnBtnExtend(TNotifyUI& msg);

	/** 点击地址簿 
	 *  @param[in]  
	 *  @return 
	 */
	bool OnBtnAddrBook(TNotifyUI& msg);

	/** 点击会议模板 
	 *  @param[in] 
	 *  @return 
	 */
	bool OnBtnConfTemp(TNotifyUI& msg);
	
	/** 点击会场控制 
	 *  @param[in] 
	 *  @return 
	 */
	bool OnBtnRoomCtrl(TNotifyUI& msg);
	/** 点击会议控制
	 *  @param[in] 
	 *  @return 
	 */
	bool OnBtnConfCtrl(TNotifyUI& msg);

	/** 点击设置
	 *  @param[in] 
	 *  @return
	 */
	bool OnBtnSysCfg(TNotifyUI& msg);
	/** 点击信息显示
	 *  @param[in] 
	 *  @return 
	 */
	bool OnBtnMsg( TNotifyUI& msg );
	/** 点击快捷方式按钮
	 *  @param[in] 
	 *  @return 
	 */
	bool OnBtnShortCutState( TNotifyUI& msg );
	/** 点击中控
	 *  @param[in] 
	 *  @return 
	 */
	bool OnBtnCenterCtrl(TNotifyUI& msg);    
    /** 点击邀请会场
	 *  @param[in] 
	 *  @return 
	 */
    bool OnBtnInviteCns(TNotifyUI& msg);
    /** 点击结束会议
	 *  @param[in] 
	 *  @return 
	 */
    bool OnBtnEndConf(TNotifyUI& msg);
	/** 点击快捷操作设置
	 *  @param[in] 
	 *  @return 
	 */
	bool OnBtnShortCutListSet(TNotifyUI& msg);
	/** 快捷操作设置消息
	 *  @param[in] 
	 *  @return 
	 */
	bool OnShortCutNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 快捷操作状态刷新
	 *  @param[in] 
	 *  @return 
	 */
	bool OnShortCutStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 会议讨论设置消息
	 *  @param[in] 
	 *  @return 
	 */
	bool OnStartConfDiscNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 快捷操作设置消息
	 *  @param[in] 
	 *  @return 
	 */
	bool OnPanCamStartNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 画中画通知
	 *  @param[in] 
	 *  @return 
	 */
	bool OnPIPNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnPIPInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 双流通知
	 *  @param[in] 
	 *  @return 
	 */
	bool OnCnsDualRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//点对点语音激励响应
	bool OnCnPTPAuxInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//点名状态
	bool OnRollStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//混音状态
	bool OnConfMixStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 静音哑音通知
	 *  @param[in] 
	 *  @return 
	 */
	bool OnMuteOrSliencNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 会议轮询通知
	 *  @param[in] 
	 *  @return 
	 */
	bool OnPollStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 会议轮询暂停通知
	 *  @param[in] 
	 *  @return 
	 */
	bool OnPollPauseInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 断链响应
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 更新快捷操作列表
	 *  @param[in] 
	 *  @return 
	 */
	void UpdateShortCutLst();

	/** 获得快捷方式条目container
	 *  @param[in] emShortcutType 条目类型
	 *  @param[out] ContainerElementUI 条目容器
	 *  @return 
	 */
	void GetItemContainer(EM_ShortcutType emShortcutType);

	//点击会议轮询暂停按钮
	bool OnBtnPollPause(TNotifyUI& msg);

    /** 会议状态通知
	 *  @param[in] 
	 *  @return 
	 */	
	bool OnConfStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);

    /** 挂断会议
	 *  @param[in] 
	 *  @return 
	 */	
    bool HungupConf();

    bool OnVidMIxStatusNty(WPARAM wParam, LPARAM lParam, bool& bHandle);

public:
	 /** 保存快捷方式到ini
	 *  @param[in] 
	 *  @return 
	 */	
	void SaveShortCutToIni();
	//点击容器 响应条目回复未选状态
	bool OnContainerClick( TNotifyUI& msg );
	//更新会议混音状态	
	void UpdateConfMixState();
	APP_DECLARE_MSG_MAP()
private:
	HWND m_hWnd;     //g_strMainMenuDlg句柄
	BOOL m_bExtend;  //menu是否展开
	CControlUI        *m_pBtnMsg;
	CControlUI        *m_pBtnSysCfg;

	s32  m_nMainMenuInitHeight; //MainMenuDlg初始高度

	vector<EM_ShortcutType> m_vctShortCutList;  //快捷方式列表
	CListContainerElementUI* m_pContainerElementUI;//当前选中的快捷方式

	RECT m_rectBtnCfg;
	RECT m_rectBtnMsg;
};

