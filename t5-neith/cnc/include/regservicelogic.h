/** @defgroup 服务器设置单元
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2014.12.10
 */
#pragma once
class CRegServiceLogic : public CNotifyUIImpl
{
public:
	CRegServiceLogic(void);
	~CRegServiceLogic(void);

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
	/** 是否进行GK 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnIsGk(TNotifyUI& msg);
	/** 是否进行量子 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnIsQT(TNotifyUI& msg);
	/** 断链消息响应 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** sip服务器注册通知 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnSipNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 注销结果通知 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnRegResultNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 名称重复通知 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnRegAliasRepeatNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** GK内容通知 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnGkNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** GK注册结构通知 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnGkRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 呼叫服务器通知 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCallSerNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 呼叫服务器下发 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCallSerInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 升级服务器通知 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnUpSerNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 升级服务器通知 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnUpSerInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 白板服务器通知 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnWBServiceIPNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 白板服务器通知 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnWBServerInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 量子加密通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnQTEncryptInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 量子加密通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnQTEncryptNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 退出此页面 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnBack(TNotifyUI& msg);

	/** 涉资呼叫服务器内容 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void SetCallServerInfo( TTPCallSerInfo tCallSerInfo );
	/** 设置服务器ip 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void SetUpgradeServiceIP(TTPUpgradeSer tUpgradeSer);
	/** 设置sip服务器ip 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void SetSipIP(TTPSipRegistrarCfg tTPSipRegistrarCfg);

    /**	 
	* 功能:  Edit激活弹出软键盘
	* @return   
	*/
    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

	APP_DECLARE_MSG_MAP()

private:

	static const String m_strBtnFixOrCancel;	 //修改、取消按钮
	static const String m_strBtnOk;			 //确认按钮
	static const String m_strBtnIsGk;			 //是否注册GK
	static const String m_strEdtRigIp;		 //注册服务器ip Edit
	static const String m_strEdtGKIp;			 //GK服务器ip Edit
	static const String m_strEdtCallIp;		 //呼叫服务器ip Edit
	static const String m_strEdtUpgradeIp;	 //升级服务器ip Edit
	static const String m_strEdtDCIp;			 //数据会议服务器ip Edit
	static const String m_strEdtQTIp;	         //量子加密ip Edit
	static const String m_strEdtQTID;			 //量子加密ID Edit

	bool m_bIsFix;
	bool m_bIsGK;
};