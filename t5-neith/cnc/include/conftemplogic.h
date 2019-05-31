/** @defgroup 会议模板逻辑单元 
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2014.12.10
 */
#pragma once

class CConfTempLogic : public CNotifyUIImpl, public Singleton<CConfTempLogic>
{
public:
	CConfTempLogic(void);
	~CConfTempLogic(void);

	void TempCallFail();
	//启用刷新按钮
	void OnWaitRefreshOverTime();

    //获取当前呼叫的模板名称
    TTPAlias GetCallTempName();
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

	/** 点击列表条目消息 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnConfTempItemClick(TNotifyUI& msg);

	/** 点击刷新按钮 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnRefresh(TNotifyUI& msg);
	
	/** 刷新列表 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnRefreshConftempLst(WPARAM wParam, LPARAM lParam, bool& bHandle);

    /** 询问会议模板密码 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCnGetTempPwdCmd(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** 断链 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** 会议状态通知 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnConfStateNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** 关键字搜索
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnSearchEditChange(TNotifyUI& msg);

	/** 点击模板选择按钮 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnTmpCall(TNotifyUI& msg);

	/** 点击取消呼叫按钮
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnNoticeBack(TNotifyUI& msg);
	//letterindex点击
	bool OnLetterIndex(TNotifyUI& msg);

    bool OnHungupConfInd(WPARAM wParam, LPARAM lParam, bool& bHandle);

    /**	 
	* 功能:  Edit激活弹出软键盘
	* @return   
	*/
    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

public:
		/** 刷新列表 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void UpdateConfTempList();
	APP_DECLARE_MSG_MAP()

private:

	vector<TTPAlias>     m_vctConfTempList;                 //会议模板列表 
	vector<TTPAlias>     m_vctSearchTempList;               //搜索到的会议模板列表 
	vector<TTPAlias>     m_vctShowTempList;                 //显示的会议模板列表 

	static const String m_strConfTempListItem;
	static const String m_strConfTempName;
	static const String m_strSeachEdit;                     //搜索框edit
	static const String m_strBtnTmpCall;                    //选择按钮

    TTPAlias            m_tTPAlias;                         //当前呼叫的模板（提示输入模板密码时需要用到）

};