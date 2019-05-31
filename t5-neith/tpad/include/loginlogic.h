/** @defgroup 登陆界面逻辑单元 
 *  @version V1.1.5
 *  @author  肖楚然
 *  @date    2016.6.27
 */
#pragma once

class CLoginLogic : public CNotifyUIImpl
{
public:
	CLoginLogic(void);
	~CLoginLogic(void);

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

	/** 登陆
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnBtnLogin(TNotifyUI& msg);

    /** 网络设置
	*  @param[in] 消息
	*  @return 是否成功
	*/
    bool OnBtnNetCfg(TNotifyUI& msg);

    /** 关机
	*  @param[in] 消息
	*  @return 是否成功
	*/
    bool OnBtnPowerOff(TNotifyUI& msg);

	//自动登录和记住密码
	bool OnCheckAutoLogin( TNotifyUI& msg );
	bool OnCheckRemPassWord( TNotifyUI& msg );

	//账号输入框信息改变
	bool OnEdUserNameTextChange(TNotifyUI& msg);

	bool OnConnectRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//超时
	bool OnCnsLoginTimeOut(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//抢登
	bool OnUmsGrabLogin(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//断链
	bool OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//系统名修改
	bool OnSysNameChange( WPARAM wParam, LPARAM lParam, bool& bHandle );

	APP_DECLARE_MSG_MAP()
private:
    BOOL    m_bHaveLogin;      //是否登陆成功过
};

