/** @defgroup 中控
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2015-3-31
 */
#pragma once

enum EmCenterCtrlTabID
{
	emTabID_Switch = 0,   //开关
	emTabID_Matrix = 5,   //矩阵
    emTabID_Srceen,       //升降屏
	emTabID_Monitor,      //显示器
	emTabID_AirCondition, //空调
//	emTabID_Camera,       //文档摄像机
	emTabID_Curtain,      //窗帘
};

class CCenterCtrlLogic : public CNotifyUIImpl, public Singleton<CCenterCtrlLogic>
{
public:
	CCenterCtrlLogic(void);
	~CCenterCtrlLogic(void);

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

	/** 失去焦点消息 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
/*	bool OnKillFocus(TNotifyUI& msg);*/
	
	/** 所有灯
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckAllLight(TNotifyUI& msg);
	/** 会议灯
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckConfLight(TNotifyUI& msg);
	/** 背景灯
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckBgLight(TNotifyUI& msg);
	/** 系统开关checkbox点击
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnShutdownSys(TNotifyUI& msg);
	/** 文档摄像机checkbox点击
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckCam(TNotifyUI& msg);
	/** 点击显示器
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnTabMonitor(TNotifyUI& msg);
	/** 点击空调
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnTabAirCondition(TNotifyUI& msg);
	/** 点击开关
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnTabSwitch(TNotifyUI& msg);
	/** 点击矩阵
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnTabMatrix(TNotifyUI& msg);
    /** 点击升降屏
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnTabScreen(TNotifyUI& msg);
		/** 点击文档摄像机
	*  @param[in] 
	*  @node 
	*  @return 
	*/	//bool OnTabCamera(TNotifyUI& msg);
	/** 点击窗帘
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnTabCurtain(TNotifyUI& msg);
	/** 断链响应
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//恢复无温度显示
	void NoDegree();

	//灯光控制响应
	bool OnAllLightInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnConfLightInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnBgLightInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//总电
	bool OnCerterPowerInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//状态通知
	bool OnCenterStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//温度通知
	bool OnSchTempNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//点击取消开启按钮
	bool OnBtnNoticeBack(TNotifyUI& msg);
	//停止等待窗口更新
	void EndWaiting();
	//更新温度显示
	void UpdateTempImg( u16 wTemp );
	//开关面板所有按钮状态可用控制
	void EnableSwitch( bool bIsEnable );

    //文档摄像机切换
    bool OnComboDCamSel(TNotifyUI& msg);
    bool OnDCamSelectedInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//文档摄像机所有按钮状态可用控制
	void EnableCam( bool bIsEnable );
	//文档摄像机状态通知
	bool OnDCamStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnDCamPowerInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//文档摄像机快照
	bool OnDocSnapShotInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//文档摄像机选择
	bool OnDocCamPrePosSelInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnOppreposeA3(TNotifyUI& msg);
	bool OnOppreposeA4(TNotifyUI& msg);
	bool OnOppreposeA5(TNotifyUI& msg);
	//点击文档摄像机快照按钮
	bool OnBtnSnapShot(TNotifyUI& msg);
	//点击文档摄像机自动对焦按钮
	bool OnBtnAutoFocus(TNotifyUI& msg);
	//点击文档摄像机自动白平衡钮
	bool OnBtnAutoWB(TNotifyUI& msg);
	//点击保存文档摄像机预置位按钮
	bool OnBtnSavePrepose(TNotifyUI& msg);
	//点击文档摄像机焦距加按钮抬起
	bool OnBtnCamPlus(TNotifyUI& msg);
	//点击文档摄像机焦距减按钮抬起
	bool OnBtnCamMinus(TNotifyUI& msg);
	//点击文档摄像机焦距加按钮按下
	bool OnBtnCamPlusDown(TNotifyUI& msg);
	//点击文档摄像机焦距减按钮按下
	bool OnBtnCamMinusDown(TNotifyUI& msg);	

	//窗帘状态通知
	bool OnCurtainStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//点击窗帘停止按钮
	bool OnBtnCuitainStop(TNotifyUI& msg);
	//点击窗帘上升按钮
	bool OnBtnCuitainUp(TNotifyUI& msg);
	//点击窗帘下降按钮
	bool OnBtnCuitainDown(TNotifyUI& msg);
	//点击窗帘全选按钮
	bool OnopAll(TNotifyUI& msg);
	//窗帘对应的选择操作
	bool Oncurtain1(TNotifyUI& msg);
	bool Oncurtain2(TNotifyUI& msg);
	bool Oncurtain3(TNotifyUI& msg);
	bool Oncurtain4(TNotifyUI& msg);
	bool Oncurtain5(TNotifyUI& msg);
	bool Oncurtain6(TNotifyUI& msg);
	//检查是否全选了窗帘
	void checkCurSelAll();
	//设置窗帘界面控制按钮可用
	void SetIsCurCanCtrl(bool bCurCanCtrl);
	
	/* 功能: 文档摄像机快照下载
	* @param    const String& strRemotePath     [in]     远端路径
	* @param    const String& strLocalFile      [in]     本地路径
	* @param    const String& strCheckFileName     [in]     文件名	
	* @return   BOOL 是否上传成功
	* @remarks  
	*/
	BOOL DownloadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bAutoEnd /*= TRUE */ );
	/** 文档摄像机快照下载响应
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnDownloadProgress(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 文档摄像机型号通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDocCamTypeInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	
	//文档摄像机焦距条件响应
	bool OnDCamZoomInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//启用\禁用文档摄像机焦距条件按钮
	//在点击后抬起事件时禁用按钮，收到ind后启用
	void SetZoomEnable(bool bIsEnabel);

	/** AC响应
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnMonitorStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//夏普显示器隐藏开关 --add by wangkui 2016-8-24
	bool HideMonitorSwitch();
    //开启ftp反馈
    bool OnSetCnFtpRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);

private:
	void ChangeInterface( EmDCamProType emCamModelType );
public:
	//更新timer弹窗
	void UpdateTimer();

	APP_DECLARE_MSG_MAP()
		


private:

	static const String m_strSldTab;			 //菜单Tab
	TTPCnsInfo           m_SelCnsInfo;

	BOOL         m_bOff;   //是否为关闭 关闭时主动跟cns断链 原程序迁移

	int          m_nUpdateTime;
	int          m_nWaitTime;

	int          m_wLocalTemp;//本地温度

	EmDCamRecallNum     m_emRecallNum;  //当前预置位
	u8 m_nCurNum;    //底层发过来的实际窗帘个数
	BOOL m_achIsCurCheck[MAX_CURTAIN_NUM];//本地窗帘选择情况

	CFtpCtrl m_cFtp;//下载文档摄像机快照
	CString m_strLogFolderPath;//本地日志存放文件夹

    bool        m_bIsShotcupOpenFtp;//快照时打开ftp

    u8          m_byDCamSelIndex;//当前选中的文档摄像机条目
};