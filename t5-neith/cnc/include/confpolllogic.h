/** @defgroup 会议轮询逻辑单元 
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2015-4-22 
 */
#pragma once

enum EMPollItemMoveMode{
	emMoveTop,
	emMoveUp,
	emMoveDown,
	emMoveBottom,
	emMoveNo,
}; 

class CConfPollLogic : public CNotifyUIImpl, public Singleton<CConfPollLogic>
{
public:
	CConfPollLogic(void);
	~CConfPollLogic(void);
	//外部调用更新列表
	void UpdatePollList();

protected:

	/** 点击开启会议轮询Checkbox 
	*  @param[in]                                
	*  @return 
	*/
	bool OnBtnCheckConfPoll(TNotifyUI& msg);	
	/** 点击开启会议轮询暂停
	*  @param[in]                                
	*  @return 
	*/
	bool OnBtnCheckPause(TNotifyUI& msg);
	/** 点击开启会议轮询快捷方式Checkbox 
	*  @param[in]                                
	*  @return 
	*/
	bool OnCheckConfPollShortCut(TNotifyUI& msg);

	/** 会议轮询暂停结果通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnPollPauseInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 会议轮询列表更新反馈通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnPollListInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 会议轮询列表通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnPollListNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 会议轮询通知
	 *  @param[in] 
	 *  @return 
	 */
	bool OnPollStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 断链响应
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 会议更新
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnRefreshCnsLstNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//更新会议轮询列表
	void UpdatePollList(vector<u16>  vctPollList);
	void UpdatePollList(EMPollItemMoveMode emMode);
	//会议轮询列表调整按钮启用
	void EnablePollBtn(bool bIsEnable);
	/** 点击会议轮询列表条目 
	*  @param[in] 
	*  @return 
	*/
	bool OnPollListClick(TNotifyUI& msg);
	/** 会议轮询列表操作
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnAddPoll(TNotifyUI& msg);
	bool OnBtnPollTop(TNotifyUI& msg);
	bool OnBtnPollUp(TNotifyUI& msg);
	bool OnBtnPollDown(TNotifyUI& msg);
	bool OnBtnPollBottom(TNotifyUI& msg);
	bool OnBtnPollDel(TNotifyUI& msg);
	//会议列表操作
	bool OnBtnPSelCancel( TNotifyUI& msg );
	bool OnCheckPConfItem( TNotifyUI& msg );
	bool OnBtnPSelAll( TNotifyUI& msg );
	bool OnBtnPSelRoomOK( TNotifyUI& msg );
	void UpdateCnsList();
	//向cns发列表更新消息
	bool UpdateCnsPollList(u16 wPollLstPos);//wPollLstPos 包相对于m_vctFixedPollList的起始位置
	//会议状态更新
	bool OnConfStateNotify( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//会议轮询开启结果
	bool OnStartPollRsp( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//快捷方式控制
	bool OnShortCutPoll( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//搜索
	bool OnSearchEditChange( TNotifyUI& msg );
	APP_DECLARE_MSG_MAP()
	
private:

	s32		m_nPollFlagInd;				//Ind的会议轮询更新标识。第一次不赋值，收到第一个ind后与此ind的flag相同
	bool    m_bIsFirstPollListInd;		//Ind的会议轮询列表跟新消息发出后的第一个ind，此后发出包的flag要和第一次来的ind带的flag相同

	s32     m_dwSelPollItemId;			//记录当前操作的条目Id

	vector<TCnsInfo>         m_vctCurrentCnsList;//显示的Cns列表
	vector<TCnsInfo>         m_vctSelConf;//选中的会场列表
	vector<TCnsInfo>         m_vctSearchCnsList;//搜索的会场列表
	bool m_bIsSelAll;//是否会议列表全选

	vector<u16>    m_vctPollList;       //当前界面的会议轮询列表会场ID
	vector<u16>    m_vctFixedPollList;  //修改后的会议轮询列表会场ID 用于发送修改消息
	bool m_bIsFixed;					//是否进行了修改
	bool m_bIsSearch;					//是否进行了搜索

    bool m_bIsSetPause;               //暂停轮询还是恢复
};

