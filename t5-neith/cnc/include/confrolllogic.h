/** @defgroup 会议点名逻辑单元 
 *  @version V1.1.4
 *  @author  邓莹莹
 *  @date    22016-7-4
 */
#pragma once

enum EMRollItemMoveMode{
	emRollMoveTop,
	emRollMoveUp,
	emRollMoveDown,
	emRollMoveBottom,
	emRollPre,//点上一个名
	emRollNext,//点下一个名
	emRollMoveNo,
}; 

enum EMSelConf{
	emSelConfNo,
	emSelConfRoller,//点名
	emSelConfRollee,//被点名
}; 

enum EMAttend{
	emAttendNo,//未进行点名
	emAttend,//出席
	emAbsent,//未出席
}; 
typedef struct tagTRolleeState
{
	u16	m_wEpID;							//会场ID
	EMAttend m_emAttend;			        //是否出席
	s8	m_achRoomName[TP_MAX_ALIAS_LEN+1];	//会场名
	bool m_bOnline;						    //是否在线
    EmTPEndpointType m_emEpType;			//结点类型

	tagTRolleeState()
	{	
		Clear();
	}

	void Clear()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_emAttend = emAttendNo;
		m_achRoomName[0] = '\0';
		m_bOnline = true;
        m_emEpType = emTPEndpointTypeUnknown;
	}

}TRolleeState;

class CConfRollLogic : public CNotifyUIImpl, public Singleton<CConfRollLogic>
{
public:
	CConfRollLogic(void);
	~CConfRollLogic(void);

	void UpdateRoller();
protected:

	/** 点击开启会议点名Checkbox 
	*  @param[in]                                
	*  @return 
	*/
	bool OnCheckConfRoll(TNotifyUI& msg);	
	//语音激励
	//bool OnCheckRollImpel(TNotifyUI& msg);	
	/** 点击开启会议点名快捷方式Checkbox 
	*  @param[in]                                
	*  @return 
	*/
	bool OnCheckConfRollShortCut(TNotifyUI& msg);
	/** 会议点名状态更新反馈通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnRollStateInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 会议点名状态通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnRollStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 会议点名列表中被点名与会状态通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnRolleeAttendStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 会议点名下一个反馈
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnRollNextInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
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
	/** 被点名人列表修改回应
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnRollLstFixedInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//更新会议点名列表
	void UpdateRollList(vector<TRolleeState>  vctRollList);
	void UpdateRollList(EMRollItemMoveMode emMode);
	//更新点名条目状态
	void UpdateRollItem(u32 wItemID, EMAttend eMAttend = emAttend);
	
	//会议点名列表调整按钮启用
	void EnableRollBtn(bool bIsEnable);
	/** 点击会议点名列表条目 
	*  @param[in] 
	*  @return 
	*/
	bool OnRollItemClicked(TNotifyUI& msg);
	/** 会议点名列表选中
	*  @param[in] 
	*  @return 
	*/
	bool OnTimerRollList(TNotifyUI& msg);
	/** 会议点名列表操作
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnAddRoller(TNotifyUI& msg);
	bool OnBtnAdd(TNotifyUI& msg);
	bool OnBtnRollTop(TNotifyUI& msg);
	bool OnBtnRollUp(TNotifyUI& msg);
	bool OnBtnRollDown(TNotifyUI& msg);
	bool OnBtnRollBottom(TNotifyUI& msg);
	bool OnBtnRollDel(TNotifyUI& msg);
	bool OnBtnRollPre(TNotifyUI& msg);
	bool OnBtnRollNext(TNotifyUI& msg);
	//会议列表操作
	bool OnBtnRollSelCancel( TNotifyUI& msg );
	bool OnCheckConfItem( TNotifyUI& msg );
	bool OnBtnRollSelAll( TNotifyUI& msg );
	bool OnBtnRollSelRoomOK( TNotifyUI& msg );
	void UpdateCnsList();
	//快捷方式控制
	bool OnShortCutRoll( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//主席通知，默认点名人为主席
	bool OnChairNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//退出会议 状态清空
	bool OnConfStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//搜索
	bool OnRollSearchEditChange( TNotifyUI& msg );

	//点击确认出席按钮
	bool OnBtnAttend( TNotifyUI& msg );
	//点击确认不出席按钮
	bool OnBtnAbsent( TNotifyUI& msg );
	//更新与会状态
	void UpDateAbsentState(EmRollCallPresentState em);
	//点击条目中点名按钮
	bool OnBtnItemSelect( TNotifyUI& msg );
	//直接点名上一个或者下一个		
	void RollOther(CListContainerElementUI *pOri, CListContainerElementUI *pCur);
	//指定发言人
	bool OnBtnSetLeftSpeaker( TNotifyUI& msg );
	bool OnBtnSetCenterSpeaker( TNotifyUI& msg );
	bool OnBtnSetRightSpeaker( TNotifyUI& msg );
	//更新已选点名人和被点名人在线状态(不在线置灰)
	void UpdateRollState();
	APP_DECLARE_MSG_MAP()
	
private:

	s32     m_dwSelRollItemId;			//记录当前操作的条目Id
	s32     m_dwCallTargetItemId;		//记录当前被点名的条目Id

	vector<TCnsInfo>         m_vctCurrentCnsList;//显示的Cns列表
	vector<TCnsInfo>         m_vctCnsList;//全部cns列表
	vector<TCnsInfo>         m_vctCnsNoChildList;//没有下级会场的cns列表
	vector<TCnsInfo>         m_vctSelConf;//选中的会场列表
	vector<TCnsInfo>         m_vctSearchCnsList;//搜索的会场列表
	bool m_bIsSelAll;//是否会议列表全选

	vector<TRolleeState>    m_vctRollList; //当前界面的会议点名列表会场ID
	TCnsInfo  m_tRollerInfo;            //点名人会场信息
	bool m_bIsSearch;					//是否进行了搜索
	EMSelConf m_emSelConf;
	TTpConfRollCallInfo m_tTpConfRollCallInfo;//点名状态信息
};

