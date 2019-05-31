/** @defgroup 内容请求框
 *  @version V1.1.4
 *  @author  ylp
 *  @date    2019.4.18
 */
#pragma once

extern string g_strContentReq;

class CContentReqLogic : public CNotifyUIImpl
{
public:
	CContentReqLogic(void);
	~CContentReqLogic(void);
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

	/** 返回
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnBtnCancel(TNotifyUI& msg);
	/** 退出
	*  @param[in] 消息
	*  @return 
	*/
	bool OnBtnOk(TNotifyUI& msg);

	/** 断链
	*  @param[in] 消息
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	
	APP_DECLARE_MSG_MAP()

};

int showContentReq();
#define ShowContentReq showContentReq
