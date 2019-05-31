/** @defgroup 断链重连对话框
 *  @version V1.1.6.4.0
 *  @author  肖楚然
 *  @date    2017.9.20
 */
#pragma once
class CReconnectLogic : public CNotifyUIImpl
{
public:
	CReconnectLogic(void);
	~CReconnectLogic(void);

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

	bool OnDestroy(TNotifyUI& msg);

	/** 退出
	*  @param[in] 消息
	*  @return 
	*/
	bool OnBtnExit(TNotifyUI& msg);
	 
	//链接回复
	bool OnConnectRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);

	APP_DECLARE_MSG_MAP()
};

