/** @defgroup 会议模板逻辑单元 
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2014.12.10
 */
#pragma once

class CSysConfigLogic : public CNotifyUIImpl
{
public:
	CSysConfigLogic(void);
	~CSysConfigLogic(void);

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

	/** 点击地址簿管理按钮 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnAddrManager(TNotifyUI& msg);

	/** 断链 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** 点击用户管理按钮 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnUserManager(TNotifyUI& msg);

	/** 点击会议呼叫设置按钮
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnConfCallCfg(TNotifyUI& msg);
	/** 点击会场设置按钮
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnLocalRoomControl(TNotifyUI& msg);
	/** 点击服务器管理按钮
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnRegService(TNotifyUI& msg);
	/** 点击用户自定义按钮
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnUserDefined(TNotifyUI& msg);

	/** 点击取消
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnBack(TNotifyUI& msg);

	/** 点击退出
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnExit(TNotifyUI& msg);

	APP_DECLARE_MSG_MAP()

private:

};