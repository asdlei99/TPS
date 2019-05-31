/** @defgroup 用户自定义单元
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2014.12.20
 */
#pragma once
class CUserDefinedLogic : public CNotifyUIImpl, public Singleton<CUserDefinedLogic> 
{
public:
	CUserDefinedLogic(void);
	~CUserDefinedLogic(void);
	
	/** 更新时间显示
	 *  @param[in] 
	 *  @return 
	 */
	void UpdateTime();
     /** 更新当前用户是否是超级管理员
	*  @param[in]
	*  @node 
	*  @return 
	*/
	void UpdateSuperadmin();

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
	
	/** 点击保存按钮
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnOk(TNotifyUI& msg);
	/** 点击修改或取消按钮
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnFixOrCancel(TNotifyUI& msg);
	/** 点击取消下载按钮
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnCancelDownload(TNotifyUI& msg);
	/** 点击是否开启密码周期更新
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckIsPWEpochUpdate(TNotifyUI& msg);
	/** 点击是否开启系统待机按钮
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckIsSysStandby(TNotifyUI& msg);
	/** 点击是否开启时间同步
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckTimeSynchro(TNotifyUI& msg);
	/** 点击下载按钮
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnDownloadLog(TNotifyUI& msg);
	/** 时间设置的加减按钮
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnHMinus(TNotifyUI& msg);
	bool OnBtnHAdd(TNotifyUI& msg);
	bool OnBtnMMinus(TNotifyUI& msg);
	bool OnBtnMAdd(TNotifyUI& msg);
	bool OnBtnSMinus(TNotifyUI& msg);
	bool OnBtnSAdd(TNotifyUI& msg);
	/** 时间设置相关控件是否可操作
	*  @param[in] bool true设置为可操作 false设置为不可操作
	*  @node 
	*  @return 
	*/
	void EnableTimeCtrl( bool bIsEnable );
	/** 刷新待机
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnSleepInfoNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
	
	/** 断链处理
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 退出此页面 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnBack(TNotifyUI& msg);
	/** 退出cnc 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnExit(TNotifyUI& msg);

	/** 保存密码
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	//bool savePassWord(bool bIsSave);
	/** 保存锁屏密码
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool saveLockPassWord(bool bIsSave);
	/** 保存系统时间
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool saveSysTime(bool bIsSave);
	/** 保存系统名称
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool saveSysName(bool bIsSave);
	/** 保存密码周期更新信息
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool savePasswordUpdateInfo();
    /** 保存超级管理员信息
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool saveSuperadminInfo(bool bIsSave);
	/** 信息修改时状态切换 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool setFixEnable(bool bIsEnable);
	/** 更新系统时间
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void UpdateSysTime();
	/** 更新待机时间
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void UpdateStandbyTime();
	/** 系统时间更新通知处理
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	HRESULT OnUpdateSysTime( WPARAM wparam, LPARAM lparam); 
	/** 同步系统时间到服务器
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	u16   SyncTimeToServ( const SYSTEMTIME sysTime  );

	/** 是否可以更新，如果当前正处在编辑状态则不更新，否则就更新 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	BOOL32 IsCouldUpdate();
	/** 下载状态更新 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDownloadProgress(WPARAM wParam, LPARAM lParam, bool& bHandle);

	//设置时间
	bool OnBtnDateSet(TNotifyUI& msg);
    //时间选择后响应
	bool OnCalendarDateSel(WPARAM wParam, LPARAM lParam, bool& bHandle);

    //解锁所有用户
    bool OnBtnUnLockAllUser(TNotifyUI& msg);

	BOOL InprovePrivilege( );
	/** 收到服务器时间反馈，更新本地时间 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnUpdateTime( WPARAM wParam, LPARAM lParam, bool& bHandle );

    /**	 
	* 功能:  Edit激活弹出软键盘
	* @return   
	*/
    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/**	 
	* 功能:  时间同步
	* @return   
	*/
    bool OnCnSysTimeToCnc(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 可能修改了自己的密码
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnChangeUserInfo(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//更新密码周期信息
	bool OnCnPasswordUpdateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnChangePasswordUpdateInfo(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //超级管理员信息
    bool OnSuperadminNty(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnSetCnFtpRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	APP_DECLARE_MSG_MAP()
private:

	static const String m_strBtnFixOrCancel;	//修改、取消按钮
	static const String m_strBtnOk;			    //确认按钮
//	static const String m_strEdtOldPassword;	//用户原始密码
//	static const String m_strEdtNewPassword;	//新密码
//	static const String m_strEdtCheckPassword;	//密码确认
	static const String m_strEdtLockPassword;	//锁屏密码
	static const String m_strComboPWEpochUpdate;//密码周期更新
	static const String m_strEdtStandbyTime;	//系统待机时间
	static const String m_strCheckIsSysStandby;	

	bool m_bIsFix;                               //是否进行编辑
	BOOL m_bIsSysStandby;						 //是否开启系统待机
	BOOL m_bCouldUpdateTime;					 //是否可以更新
	BOOL m_bIsTimeSynchro;						 //是否是时间同步
	CFtpCtrl m_ftp;								 //ftp控制
	TCenDevSleepInfo  m_tCenDevSleepInfo;//待机信息

	vector<CString>   m_vctLoglist;  //日志列表
	CString m_strLogFolderPath;//本地日志存放文件夹
	u16 m_wLogId;//记录正在下载的日志文件

	TLoginInfo m_tLoginUser;//暂时保存修改后密码，反馈成功后设置为当前用户密码信息

    bool m_bWaitFtpDownLog;//等待ftp连接成功后下载日志标志位
};