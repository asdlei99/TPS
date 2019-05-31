/** @defgroup 会议混音逻辑单元 
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    2016-8-1 
 */
#pragma once


class CConfMixLogic : public CNotifyUIImpl, public Singleton<CConfMixLogic>
{
public:
	CConfMixLogic(void);
	~CConfMixLogic(void);
	//外部调用更新列表
	void UpdateMixList();
	bool IsAutoMix();

protected:

	/** 点击开启会议混音Checkbox 
	*  @param[in]                                
	*  @return 
	*/
	bool OnBtnConfMixStart(TNotifyUI& msg);	
	/** 点击开启会议混音快捷方式Checkbox 
	*  @param[in]                                
	*  @return 
	*/
	bool OnCheckConfMixShortCut(TNotifyUI& msg);
	/** 会议混音开启回应
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnConfMixInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 会议混音列表通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnMixFixInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 会议混音通知
	 *  @param[in] 
	 *  @return 
	 */
	bool OnConfMixStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
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
	//更新已选列表的在线状态
	void UpdateConfMixState();
	//更新会议混音列表
	void UpdateMixList(vector<u16>  vctPollList);

	/** 点击会议混音列表条目 
	*  @param[in] 
	*  @return 
	*/
	bool OnMixListClick(TNotifyUI& msg);
	/** 会议混音列表操作
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnAddMix(TNotifyUI& msg);
	bool OnBtnMixDel(TNotifyUI& msg);
	//开启混音后修改混音列表
	bool FixMixlist( bool bIsAdd );
	/** 会议混音模式操作
	*  @param[in] 
	*  @return 
	*/
	bool OnOpManMix(TNotifyUI& msg);
	bool OnOpAutoMix(TNotifyUI& msg);
	//会议列表操作
	bool OnBtnMixSelCancel( TNotifyUI& msg );
	bool OnCheckMixConfItem( TNotifyUI& msg );
	bool OnBtnMixSelAll( TNotifyUI& msg );
	bool OnBtnMixSelRoomOK( TNotifyUI& msg );
	void UpdateCnsList();

	//会议状态更新 退出会议 状态清空
	bool OnConfStateNotify( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//快捷方式控制
	bool OnShortCutConfMix( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//搜索
	bool OnMixSearchEditChange( TNotifyUI& msg );
	bool UpdateMixList(u16 wIndex, bool bSel);//更新条目状态
	APP_DECLARE_MSG_MAP()
	
private:

	vector<s32>         m_vctFixMixList;//开启混音后进行添加、删除的条目

	vector<TCnsInfo>         m_vctCurrentCnsList;//显示的Cns列表
	vector<TCnsInfo>         m_vctSelConf;//选中的会场列表
	vector<TCnsInfo>         m_vctSearchCnsList;//搜索的会场列表
	bool m_bIsSelAll;//是否会议列表全选

	vector<u16>    m_vctMixList;       //当前界面的会议混音列表会场ID
	bool m_bIsSearch;					//是否进行了搜索
	TTpAudMixInfo m_tTpAudMixInfo;//混音状态
};

