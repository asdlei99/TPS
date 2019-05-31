/** @defgroup 会场管理逻辑单元（模拟屏） 
 *  @version V1.1.4
 *  @author  肖楚然
 *  @date    2015.1.29
 */
#pragma once
class CCnsManageLogic : public CNotifyUIImpl, public Singleton<CCnsManageLogic> 
{
public:
	CCnsManageLogic(void);
	~CCnsManageLogic(void);

	/** 点击模拟屏
	*  @param[in] 消息
	*  @return 
	*/
	bool OnCnsScreenItemClick(TNotifyUI& msg);
	/** 点击会议选看
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnScrSelWatch(TNotifyUI& msg);
	/** 点击取消选看
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnCancelSelWatch(TNotifyUI& msg);
	//点击回显
	bool OnCheckScrLocal(TNotifyUI& msg);
	//点击双流
	bool OnCheckDualView(TNotifyUI& msg);
	//点击电视墙
	bool OnCheckTVWView(TNotifyUI& msg);
	//设置发言坐席
	bool OnBtnSpeakSeat1(TNotifyUI& msg);
	bool OnBtnSpeakSeat2(TNotifyUI& msg);
	bool OnBtnSpeakSeat3(TNotifyUI& msg);

	void InitCnsScreenList();

    void UpdateScreenMenu( u8 bSrcnID, CControlUI *pParent );
	
	bool OnConfStateNotify( WPARAM wParam, LPARAM lParam, bool& bHandle );
    bool OnRefreshConfCnsList( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnSelViewInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	
	bool OnCancelSelViewRsp(  WPARAM wParam, LPARAM lParam, bool& bHandle );//暂时没用
	//更新屏幕
	bool OnScreenStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//更新坐席
	bool OnSpokesManNotify( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//回显响应
	bool OnSelLocalRsp(  WPARAM wParam, LPARAM lParam, bool& bHandle  );
	bool OnCancleSelLocalRsp(  WPARAM wParam, LPARAM lParam, bool& bHandle  );
	//双流响应
	bool OnSelDualViewRsp(  WPARAM wParam, LPARAM lParam, bool& bHandle  );
	bool OnCancleDualViewRsp(  WPARAM wParam, LPARAM lParam, bool& bHandle  );
	//空闲双流响应
	bool OnSpareSelDualViewInd(  WPARAM wParam, LPARAM lParam, bool& bHandle  );
	bool OnSpareSelDualViewNty(  WPARAM wParam, LPARAM lParam, bool& bHandle  );
	//电视墙响应
	bool OnSelTVSViewRsp(  WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnCancleSelTVSViewRsp(  WPARAM wParam, LPARAM lParam, bool& bHandle );

	//静音、哑音通知 --add by wangkui 2016-8-23
	bool OnMuteOrSilencNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//会议混音通知   --add by wangkui 2016-8-23
	bool OnConfMixStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//是否在会议混音中通知   --add by wangkui 2016-9-19
	bool OnEpInAudMixNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //更新会议持续时间
    void UpdateConfTime();
    void AdjustTime( time_t &time );
	
	//更新所以屏显示名称状态
	void RefreshCnsScreen();

	//更新屏上的双流状态
	void RefreshScreenDual(u16 wScreenID);

	//更新checkbox按钮状态
	void UpDateCheckBoxState(String strCheckName, u16 wId, bool bCheck);
		/** 断链处理
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//取消选择屏幕
	void UnSelScreenList();
	//刷新坐席
	void RefreshSpeakSeat();

	//启用电视墙控制
	void EnableTVWall(int nSelIndex);
	APP_DECLARE_MSG_MAP()


private:
	CTouchListUI     *m_pSrceenList;
	int               m_nSelIndex;
    bool              m_bInConf;        //当前是否在会议中

    time_t            m_dwConfStartTime;            //会议的开始时间
    CTimeSpan         m_tmConfDuration;             //当前会议持续时长

	static const String strCnsScreenList;
	static const String strCnsScreenListItem;

	bool m_bIsSpareDual;//是否在空闲时显示了双流（用于开会后屏幕状态的刷新）
};

