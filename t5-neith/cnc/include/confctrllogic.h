/** @defgroup 会议控制逻辑单元 
 *  @version V1.1.4
 *  @author  肖楚然
 *  @date    2014.12.26
 */
#pragma once

enum EmConfCtrlTabID
{
	emTabID_ConfCns = 0,
	emTabID_ConfRoll,
	emTabID_ConfMix,
	emTabID_VideoMix,
	emTabID_ConfPoll,
	emTabID_AudioMix,
	emTabID_ConfDual,
	emTabID_MixMotive,
	emTabID_PIP,
    emTabID_SeatMotive,
	emTabID_TvWall,
};


enum EM_CnsListShowState{
	emShowAll,
    emShowOnLine,
    emShowOffLine,
	emShowSpeaker,
	emShowMute,
	emShowQuiet,	
	emShowDual,
}; 

class CConfCtrlLogic : public CNotifyUIImpl, public Singleton<CConfCtrlLogic>
{
public:
	CConfCtrlLogic(void);
	~CConfCtrlLogic(void);

protected:
	/** 窗口创建 
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnCreate(TNotifyUI& msg);

	/** 初始化消息 
	 *  @param[in] 
	 *  @return 
	 */
	bool OnInit(TNotifyUI& msg);

	/** 会议会场Tab 
	*  @param[in] 
	*  @return 
	*/
	bool OnTabConfCns(TNotifyUI& msg);

	/** 混音Tab 
	*  @param[in] 
	*  @return 
	*/	
	bool OnTabConfMix(TNotifyUI& msg);
	/** 画面合成Tab 
	*  @param[in] 
	*  @return 
	*/	
	bool OnTabVideoMix(TNotifyUI& msg);
	/** 会议轮询Tab 
	*  @param[in] 
	*  @return 
	*/	
	bool OnTabConfPoll(TNotifyUI& msg);
	/** 会议点名Tab 
	*  @param[in] 
	*  @return 
	*/	
	bool OnTabConfRoll(TNotifyUI& msg);
	/** 会议讨论Tab 
	*  @param[in]  
	*  @return 
	*/	
	bool OnTabAudioMix(TNotifyUI& msg);
	/** 双流演示Tab
	*  @param[in] 
	*  @return 
	*/	
	bool OnTabConfDual(TNotifyUI& msg);
	/** 双流演示Tab
	*  @param[in] 
	*  @return 
	*/	
	bool OnTabMixMotive(TNotifyUI& msg);
	/** 画中画Tab
	*  @param[in] 
	*  @return 
	*/	
	bool OnTabPIP(TNotifyUI& msg);
    /** 坐席激励Tab
	*  @param[in] 
	*  @return 
	*/	
	bool OnTabSeatMotive(TNotifyUI& msg);
	/** 电视墙Tab
	*  @param[in] 
	*  @return 
	*/	
	bool OnTabTVWall(TNotifyUI& msg);
	/** 点对点摄像机远摇
	*  @param[in] 
	*  @return 
	*/	
	bool OnTabFeccCam(TNotifyUI& msg);
	
	/** tab前一页
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnGoLeft(TNotifyUI& msg);
	
	/** tab后一页
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnGoRight(TNotifyUI& msg);

	/** 设置发言人
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnSetSpeaker(TNotifyUI& msg);
	/** 指定双流
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnSetDual(TNotifyUI& msg);
	/** 静音
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnSetQuiet(TNotifyUI& msg);
	/** 哑音
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnSetMute(TNotifyUI& msg);	
	/** 挂断会场
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnHungupCns(TNotifyUI& msg);
	
	/** 点击会场列表条目 
	*  @param[in] 
	*  @return 
	*/
	bool OnConfCnsItemClick(TNotifyUI& msg);
	/** 勾选会场列表条目 
	*  @param[in] 
	*  @return 
	*/
	bool OnCheckConfCnsItem(TNotifyUI& msg);
	/** 条目中的会场操作 
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnItemSetCam(TNotifyUI& msg);
	bool OnBtnItemSetDual(TNotifyUI& msg);
	bool OnBtnItemSetSpeaker(TNotifyUI& msg);
	bool OnBtnItemSelectPlay(TNotifyUI& msg);
	bool OnBtnItemSetQuiet(TNotifyUI& msg);
	bool OnBtnItemSetMute(TNotifyUI& msg);
	bool OnBtnItemHangUp(TNotifyUI& msg);
	//呼叫不在线的成员 dyy 2015-6-29
	bool OnBtnItemCall(TNotifyUI& msg);
	//选看 dyy 2015-7-2
	bool OnBtnCancelSelView(TNotifyUI& msg);	
	//取消全部选看
	bool OnBtnSelectPlay(TNotifyUI& msg);	
    bool OnSearchEditChange(TNotifyUI& msg);
    bool OnComboShowEx(TNotifyUI& msg);

    //点击列表主路径按钮
    bool OnBtnListMainPath(TNotifyUI& msg);

    void UpdateCnsItem( u16 wEpId );

	//点击本地坐席激励Checkbox dyy 2015-4-30 
	bool OnCheckPTPSeatArouse(TNotifyUI& msg);
	//语音激励快捷方式 
	bool OnCheckVSShortCut(TNotifyUI& msg);
	//点击双流Checkbox  
	bool OnCheckLocalCnsDual(TNotifyUI& msg);
	//点击本地双流快捷方式 
	bool OnCheckDualShotCut(TNotifyUI& msg);
	//点击画中画Checkbox  
	bool OnCheckPIP(TNotifyUI& msg);
	//画中画快捷方式 
	bool OnCheckPIPShortCut(TNotifyUI& msg);
	//letterindex点击
	bool OnLetterIndex(TNotifyUI& msg);
	// 选择视频项条目
	bool OnBtnVedioItemSel(TNotifyUI& msg);
	//选择视频源列表中一项
	bool OnVedioItemSel(TNotifyUI& msg);
	//语音激励回应 多点和会议讨论一起
	//bool OnVoiceArouseInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//画中画回应
	bool OnPIPInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnPIPNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//双流回应
	bool OnCnsDualRsp( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnDualOffLineNotify( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnDualRcvInterruptNotify( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnRecvDualNty( WPARAM wParam, LPARAM lParam, bool& bHandle );

	bool OnConfStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnRefreshCnsLstNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);

	//设置全场静音/哑音快捷方式响应
	bool OnShortCutQuiteAll(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnShortCutMuteAll(WPARAM wParam, LPARAM lParam, bool& bHandle);

    //设置静音哑音回应
    bool OnSetMuteCnsRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
    bool OnSetQuietCnsRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** 显示Tab
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnSetTabShow(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//刷新快捷方式
	void SetShortCutShow(EM_ShortcutType em);
	/** 快捷方式check状态设置
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnSetShortCheck(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 会议轮询通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/	

	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

	//切换发言人回应nty
	bool OnSpeakerNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnSpeakerInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//双流回应
	bool OnItemDualNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnItemDualInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//会议选看
	bool OnItemSelViewNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//呼叫不在线会场回应
	bool OnCallOffCnsInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//单独控制坐席激励开关回应
	bool OnCnAuxInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//双流开关nty
	bool OnCnsDualNty( WPARAM wParam, LPARAM lParam, bool& bHandle );

    /**	 
	* 功能:  Edit激活弹出软键盘
	* @return   
	*/
    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

	//主视频源设置消息
	bool OnVidSrcNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** VGA信息通知
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnVgaInfoNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 双流端口通知 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnSelDualPortInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnSelDefaultDualPortInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 更新视频源列表 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void UpdateVedioSourceList();

	APP_DECLARE_MSG_MAP()

public:
	void UpdateCnsList();
	void UpdateShowList();
	void OnDualWaitOverTime();

    //获得筛选后的列表
    void GetOptnShowList( vector<TCnsInfo>& vctCurrentList );

    void UpdateListPath();
	
private:
	static const String strConfCtrlSlideTab;
	static const String strConfCnsList;
	static const String strConfCnsItem;	       //会场列表单元

	CTouchListUI       *m_pConfCnsList;        //会议会场列表
	EM_CnsListShowState m_emCnsShowState;      //会场显示状态
    TCMSConf            m_tConfInfo;           //当前会议信息
	int                 m_nSelIndex;   
	vector<TCnsInfo>    m_vctCnsList;          //Cns列表
	vector<TCnsInfo>    m_vctSelectList;       //选中会场列表
    vector<TCnsInfo>    m_vctSearchList;       //筛选列表
    vector<TCnsInfo>    m_vctShowList;         //当前显示列表
    vector<TCnsInfo>    m_vctChildCnsList;     //下级会场列表
    TCnsInfo            m_tParentCns;          //上级会场，用于级联会议

    BOOL                m_bSearchEdit;         //是否在搜索

	s32		m_nPollFlag;				//会议轮询更新标识
	u16		m_wPollTotalNum;			//会议轮询总数量
	bool    m_bIsFirstPollListNty;		//会议轮询第一次记录下flag，之后和上一次flag进行对比 不一样停止记录
	vector<u16>    m_vctPollList;       //会议轮询列表会场ID
	s32     m_CurPollItemId;			//记录当前操作的条目Id

	bool    m_bIsIni;//是否已经ini过 用于进行点对点切换 为ini时 不进行选中切换
	int m_nEmShort;//初始化之前收到的快捷方式调出

	TDualSrcInfo  m_tDualSrcInfo;
	bool m_bIsVSListExt;//是否已经有了视频源列表
	bool m_bSetVedioSourc;//是否进行了演示源切换，如果已经发了消息，在ind来之前不重复发送消息
};

