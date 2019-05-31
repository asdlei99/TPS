/** @defgroup 会议呼叫设置
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2014.12.25
 */
#pragma once
class CConfCallCfgLogic : public CNotifyUIImpl
{
public:
	CConfCallCfgLogic(void);
	~CConfCallCfgLogic(void);

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
	/** 点击编辑保存 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnOk(TNotifyUI& msg);
	/** 点击进行编辑或取消编辑按钮 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnFixOrCancel(TNotifyUI& msg);
	/** 调节单屏码率 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnSingleRateMinus(TNotifyUI& msg);
	bool OnBtnSingleRateAdd(TNotifyUI& msg);
	/** 调节演示码率 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnDulRateMinus(TNotifyUI& msg);
	bool OnBtnDulRateAdd(TNotifyUI& msg);
	/** 调节轮询时间 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnPollTimeMinus(TNotifyUI& msg);
	bool OnBtnPollTimeAdd(TNotifyUI& msg);
	
	/** 是否设置AES密码
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckIsAESPassword(TNotifyUI& msg);
	/** 是否进行会议轮询
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckIsPoll(TNotifyUI& msg);
	/** 是否进行会议讨论
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckIsConfDisc(TNotifyUI& msg);

	/** 断链处理
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
		/** 功能:  根据服务器接收音频格式的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnUpdateAudioFormat( WPARAM wparam, LPARAM lparam, bool& bHandle );

	/** 功能:  根据服务器接收会议优选格式的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnUpdateVideoFormat( WPARAM wparam, LPARAM lparam, bool& bHandle );
						
	/** 功能:  根据服务器接收演示优选格式的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnUpdateDualVideoFormat( WPARAM wparam, LPARAM lparam, bool& bHandle );
						
	/** 功能:  根据服务器接收单屏码率的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnUpdateCallRate( WPARAM wparam, LPARAM lparam, bool& bHandle );
						
	/** 功能:  根据服务器接收演示码率的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnUpdateDualCallRate( WPARAM wparam, LPARAM lparam, bool& bHandle );
						
	/** 功能:  根据服务器接收会议讨论的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnUpdateConfDis( WPARAM wparam, LPARAM lparam, bool& bHandle );
						
	/** 功能:  根据服务器接收会议轮询的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnUpdateConfPoll( WPARAM wparam, LPARAM lparam, bool& bHandle );
	/** 功能:  AES通知
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEncryptInfoInd( WPARAM wparam, LPARAM lparam, bool& bHandle );
	bool OnEncryptInfoNty( WPARAM wparam, LPARAM lparam, bool& bHandle );
	/** 点击返回按钮
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnBack(TNotifyUI& msg);
	/** 点击退出按钮
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnExit(TNotifyUI& msg);
	/** 是否进行会议讨论
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool setFixEnable(bool bIsEnable);
	/** 各个参数设置是否改变
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool IsAudioFormatChange();
	bool IsConfPollChange();
	bool IsConfDisChange();	
	bool IsDualCallRateChange();	
	bool IsCallRateChange();	
	bool IsDualVideoFomatChange();
	bool IsVideoFomatChange();
	bool IsConfEncryptChange();

	/** 各个参数设置进行保存
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool SaveRate();
	bool SaveVideoFormat();
	bool SaveDualVideoFormat();
	bool SaveConfDis();
	bool SaveConfPoll();
	bool SaveAudioFormat();
	//bool SaveAESPassWord();//暂时不用
	bool SaveConfEncryptInfo();

		/** 格式选择
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool Onop1080(TNotifyUI& msg);
	bool Onop720(TNotifyUI& msg);
	bool Onop4CIF(TNotifyUI& msg);
	bool Onop60fps(TNotifyUI& msg);
	bool Onop50fps(TNotifyUI& msg);
	bool Onop30fps(TNotifyUI& msg);
	bool Onop25fps(TNotifyUI& msg);
	bool OnopN1080(TNotifyUI& msg);
	bool OnopN720(TNotifyUI& msg);
	bool OnopN4CIF(TNotifyUI& msg);
	bool OnopUXGA(TNotifyUI& msg);
	bool OnopWXGA(TNotifyUI& msg);
	bool OnopSXGA(TNotifyUI& msg);
	bool OnopXGA(TNotifyUI& msg);
	bool OnopN60fps(TNotifyUI& msg);
	bool OnopN50fps(TNotifyUI& msg);
	bool OnopN30fps(TNotifyUI& msg);
	bool OnopN25fps(TNotifyUI& msg);
	bool OnopN5fps(TNotifyUI& msg);
	bool OnopMPEG4(TNotifyUI& msg);
	bool OnopG711A(TNotifyUI& msg);
	bool OnopG711U(TNotifyUI& msg);
	bool OnopG719(TNotifyUI& msg);
	bool OnopMP3(TNotifyUI& msg);
	bool OnopMP4(TNotifyUI& msg);
	bool OnopG772(TNotifyUI& msg);

	/** 会议加密
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnopAESEncrypt(TNotifyUI& msg);
	bool OnopQTEncrypt(TNotifyUI& msg);
	bool OnopNoEncrypt(TNotifyUI& msg);

     /**	 
	* 功能:  Edit激活弹出软键盘
	* @return   
	*/
    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

	APP_DECLARE_MSG_MAP()

private:
	/** 设置视频格式
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void SetCallServerMode();
	/** 设置优选视频格式
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void SetCallServerShowMode();
	/** 设置优选音频格式
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void SetAudioFormat();
	/** 得到梯度值
	*  @param[in] 当前edit数值 bIsBtnPlus 是否按钮加操作
	*  @node 
	*  @return 
	*/
	int GetRateFixed(int wNum, bool bIsBtnPlus = true);
	//优选option可用
	void EnableOp();
private:

	static const String m_strBtnFixOrCancel;	//修改、取消按钮
	static const String m_strBtnOk;			    //确认按钮
	static const String m_strEdtOldPassword;	//用户原始密码
	static const String m_strEdtNewPassword;	//新密码
	static const String m_strEdtCheckPassword;	//密码确认
	static const String m_strEdtLockPassword;	//锁屏密码
	static const String m_strEdtAESPassword;	//系统待机时间
	static const String m_strCheckIsAESPassword;	

	bool m_bIsFix;			//是否进行编辑
	bool m_bIsPoll;			//是否会议轮询
	bool m_bIsConfDisc;		//是否会议讨论

	TTPVidForamt m_tVidForamt;//视频格式
	TTPVidForamt m_tDualVidForamt;//优选会议格式
	EmTpAudioFormat m_emAudioFormat;//优选音频格式
	TTpEncryptKey m_tEncryptInfo;//会议加密
};