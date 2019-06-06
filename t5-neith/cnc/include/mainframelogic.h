// mainframelogic.h: interface for the CMainFrameLogic class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_MAINFRAMELOGIC_H__D2D7F34D_34EC_4A78_9C9F_4A11AD89D464__INCLUDED_)
#define AFX_MAINFRAMELOGIC_H__D2D7F34D_34EC_4A78_9C9F_4A11AD89D464__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMainFrameLogic : public CNotifyUIImpl, public Singleton<CMainFrameLogic> 
{
public:
	CMainFrameLogic();
	~CMainFrameLogic();

	bool SetTitle( LPCTSTR lpstrTitle );//设置显示标题 dyy 
	bool SetTitlePic( LPCTSTR lpstrTitle );//设置标题旁图片 dyy
	/** 设置标题栏Tab 
	*  @param[in] bShow 显示/隐藏  lpstrDlgName 调出的窗口名
	*  @return 是否成功
	*/
	bool SetTitleTab( bool bShow, LPCTSTR lpstrDlgName = _T("") );
	//隐藏提示按钮取消提示信封的闪动
	void HideTipBtn();
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

	/** 关闭应用
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnBtnQuit(TNotifyUI& msg);
	/** 退出
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnBtnExit(TNotifyUI& msg);

	/** 返回
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnBtnBack(TNotifyUI& msg);

	/** 点击标题栏Tab 
	 *  @param[in] 
	 *  @return 
	 */
	bool OnTabTitleLeft(TNotifyUI& msg);
	bool OnTabTitleRight(TNotifyUI& msg);
	//点击容器 响应条目回复未选状态
	bool OnContainerClick(TNotifyUI& msg);

	//bool OnConnetcted(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//tpad调用显示中控
	bool OnTpadShowCenterCtrlNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//tpad调用系统设置
	bool OnTpadShowSysConfigNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //tpad调用会场管理
    bool OnTpadShowCnsManageNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//tpad点击home键 2015-10-8 
	bool OnTpadHomeKeyNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//tpad下双流开始弹窗播放，自动隐藏cnc界面
	bool OnTpadShowDual(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//中控待机
	bool OnCentreSleepNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);	
	//UMS错误提示
	bool OnUmsReasonInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 新消息提醒
	 *  @param[in] 
	 *  @return 
	 */
	bool OnShowMsgNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
		/** 点击消息通知按钮
	 *  @param[in] 
	 *  @return 
	 */
	bool OnBtnTip(TNotifyUI& msg);
	/** 点击自动登录按钮
	 *  @param[in] 
	 *  @return 
	 */
	bool OnCheckAutoLogin(TNotifyUI& msg);
	bool OnCheckRemPassWord(TNotifyUI& msg);
	//链接成功 开始刷新时间
	bool OnConnectRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//会场名字更新
	bool OnCnsInfoNotify( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//有终端请求主席是否准许加入会议
	bool OnJoinConfReqChair( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//数据会议状态通知
	bool OnWBConfStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnNewConfCallReq( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//tpad登录时用户信息记录
	bool OnTpadLoginInfoNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
    //屏幕分辨率变化
    bool OnDisplayChange( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnCnsDisconnectNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnDisconnectClear( WPARAM wParam, LPARAM lParam, bool& bHandle );
    //会议状态变化
    bool OnConfStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
public:
	/** 更新消息通知按钮图片
	 *  @param[in] 
	 *  @return 
	 */
	void UpdateMsgImg();
	/** 更新时间显示
	 *  @param[in] 
	 *  @return 
	 */
	void UpdateTime();
	//ini文件路径
	CString GetIniFilePath();

	//更新登录界面显示信息
	void UpdateLoginShowInfo();

	APP_DECLARE_MSG_MAP()
		
private:
	CWndShadow m_cWndShadow;
	BOOL m_bMsgOn;   //消息图片是否点亮
	String m_strLastWnd;//（信息提示时）记录上一次操作的窗口，点击返回，返回此窗口

	bool m_bIsPadShowCenterOrSys;//是否是tpad调用显示的中控 dyy 2015-5-26 && 是否是tpad调出了系统设置
};

#endif // !defined(AFX_MAINFRAMELOGIC_H__D2D7F34D_34EC_4A78_9C9F_4A11AD89D464__INCLUDED_)