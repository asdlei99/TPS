/** @defgroup 会议讨论逻辑单元 
 *  @version V1.1.4
 *  @author  dyy
 *  @date    2015-3-25
 */
#pragma once

struct TAudMixCtrls 
{
	CString strConfName;                           //会场名
	bool bIsSpeaker;		                     //是否是发言会场
	u16 wCnsID;                                 //对应的cnsID
	u16 wSpeakerNum;						    //会场屏数	
    EmTPEndpointType m_emEpType;			    //结点类型

	TAudMixCtrls()
	{
		strConfName = _T("");
		bIsSpeaker = false;
		wCnsID = TP_INVALID_INDEX;
		u16 m_wSpeakerNum = 0;
        m_emEpType = emTPEndpointTypeUnknown;
	}
};

enum EmCncListState{
	emCncListState_all,		//全选
	emCncListState_group,	//组
	emCncListState_inline,   //在线
	emCncListState_outline   //不在线
};

class CAudMixLogic : public CNotifyUIImpl, public Singleton<CAudMixLogic>
{
public:
	CAudMixLogic(void);
	~CAudMixLogic(void);

protected:
	//更新列表
	bool UpdateList( CString strPresetName, u8 wPageID, u8 wItemID);
	//点击开启会议讨论按钮
	bool OnCheckStartDisc(TNotifyUI& msg);
	//点击创建快捷方式按钮
	bool OnCheckDisShortCut(TNotifyUI& msg);
	//开启语音激励
	bool OnCheckAudioExc(TNotifyUI& msg);
	/**	 
	* 功能: 更新混音列表
	* @return  bool
	* @remarks  
	*/
	void UpdateCnsList();
	//会议状态更新
	bool OnConfStateNotify( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//刷新列表
	bool RefreshAudMixList( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnRefreshCnsList( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//开启会议讨论ind 用于提示失败原因
	bool OnStartAudMixInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//添加或删除会议讨论回应
	bool OnAudMixDisListOprInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//语音激励回应
	bool OnAudMixVacOprInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//切换发言人回应nty
	bool OnSpeakerNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnSpeakerInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	/**	 
	* 功能: 更新混音列表
	* @return  bool
	* @remarks  
	*/
	bool UpdateAudMixLst();
	/**	 
	* 功能:  会场是否已经选过
	* @return  bool
	* @remarks  
	*/	
	BOOL IsInAudMixList( u16 wCnsId );
	/** 断链响应
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** 点击会场列表中的确定按钮
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnSelRoomOK(TNotifyUI& msg);
	//会议列表全选
	bool OnBtnSelAll(TNotifyUI& msg);
	//会议列表取消
	bool OnBtnSelCancel(TNotifyUI& msg);
	//删除此会议讨论会场
	bool OnBtnDelDisc(TNotifyUI& msg);
	//选择混音会场地址簿筛选combo
	bool OnComboAddrShowEx(TNotifyUI& msg);
	//混音操作（沿用）
	void OprAudMixCtrl( TDiscussListOpr tListOpr );
	//点击预置位列表向左
	bool OnBtnListLeft(TNotifyUI& msg);
	//点击预置位列表向右
	bool OnBtnListRight(TNotifyUI& msg);
	//更新显示的预置位列表 bLeft是否向左更新
	void UpdateShowSliderList(bool bLeft);
	/** 点击会议讨论列表条目
	*  @param[in] 消息
	*  @return 
	*/
	bool OnDiscussItemClick(TNotifyUI& msg);
	/** 点击会议列表条目
	*  @param[in] 消息
	*  @return 
	*/
	bool OnSelConfItemClick(TNotifyUI& msg);
	//点击条目消息
	bool OnDiscussListItem(TNotifyUI& msg);
	/** 勾选会场列表条目 
	*  @param[in] 
	*  @return 
	*/
	bool OnCheckConfItem(TNotifyUI& msg);
	//点击添加会场
	bool OnBtnAddConf(TNotifyUI& msg);
	//点击替换
	bool OnBtnChangeConf(TNotifyUI& msg);
	//设置为发言会场
	bool OnBtnSpeaker(TNotifyUI& msg);
	//搜索
	bool OnSearchEditChange( TNotifyUI& msg );
	//登录成功 用于提示语音激励状态
	bool OnConnectRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	APP_DECLARE_MSG_MAP()
public:
	bool UpdateList();

private:
	vector<TCnsInfo>         m_vctCurrentCnsList;//显示的Cns列表
	vector<TAudMixCtrls>     m_vctAudmix;//会议讨论列表
	vector<TCnsInfo>         m_vctSelConf;//选中的会场列表
	vector<TCnsInfo>         m_vctSearchCnsList;//选中的会场列表
	int m_dwSelItemId;    //当前选中的在当前页下的ID
	u16 m_wCurPageIndex;  //当前列表起始项索引
	bool m_bIsSelAll;//是否会议列表全选

	bool m_bIsSearch;//是否进行了搜索
	bool m_bIsDel;//是否进行了删除
	int  m_nSpeakerCount;//目前列表中所有会场的屏数总和(单屏、双屏、三屏)

	bool    m_bIsFirstLogin;//是否刚登录成功
	bool    m_bIsChangeConf;//是否替换会场
	int     m_dwChangeItemIndex;//要替换的列表中位置编号
};


