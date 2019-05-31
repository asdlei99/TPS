/** @defgroup 登陆界面逻辑单元 
 *  @version V1.1.4
 *  @author  肖楚然
 *  @date    2014.8.18
 */
#pragma once

class CLoginLogic : public CNotifyUIImpl, public Singleton<CLoginLogic> 
{
public:
	CLoginLogic(void);
	~CLoginLogic(void);

	void UpdateSysName();
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

	//账号输入框信息改变
	bool OnEdUserNameTextChange(TNotifyUI& msg);


	bool OnConnectRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//超时
	bool OnCnsLoginTimeOut(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//抢登
	bool OnUmsGrabLogin(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//断链
	bool OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle );

	APP_DECLARE_MSG_MAP()
	
};

