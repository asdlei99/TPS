/** @defgroup 画面合成逻辑单元 
 *  @version V1.1.4
 *  @author  肖楚然
 *  @date    2014.12.26
 */
#pragma once
class CVideoMixLogic : public CNotifyUIImpl, public Singleton<CVideoMixLogic> 
{
public:
	CVideoMixLogic(void);
	~CVideoMixLogic(void);

    void InitVideoMixPage();
	
	//点击返回按钮 隐藏此界面 不然点击其他快捷方式进入 扔停留在此界面
	void HideVideoMixStylePage();

protected:
	/** 窗口创建 
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnCreate(TNotifyUI& msg);

    /** 选择合成风格
	*  @param[in] 消息
	*  @return 是否成功
	*/
    bool OnComboSelMix(TNotifyUI& msg);
	
    bool OnChooseMixStyle(TNotifyUI& msg);
    /** 选择合成风格
	*  @param[in] 消息
	*  @return 是否成功
	*/
    bool OnVideoMixStyleClick(TNotifyUI& msg);

    bool OnBtnVidMixStyleOK(TNotifyUI& msg);
    bool OnBtnVidMixStyleCancel(TNotifyUI& msg);

    /** 删除所有合成通道
	*  @param[in] 消息
	*  @return 是否成功
	*/
    bool OnBtnVmpDeleteAll(TNotifyUI& msg);

    /** 保存预案
	*  @param[in] 消息
	*  @return 是否成功
	*/
    bool OnBtnSaveVmpCfg(TNotifyUI& msg);
    /** 调用预案
	*  @param[in] 消息
	*  @return 是否成功
	*/
    bool OnBtnCallVmpCfg(TNotifyUI& msg);

    /** 点击合成画面左上角配置按钮
	*  @param[in] 消息
	*  @return 是否成功
	*/
    bool OnBtnVideoMixCfg(TNotifyUI& msg);

    bool OnBtnVidMixAddCns(TNotifyUI& msg);

    bool OnBtnFollowSpeaker(TNotifyUI& msg);

    bool OnBtnFollowDual(TNotifyUI& msg);
    /** 选择会场进画面合成通道
	*  @param[in] 消息
	*  @return 
	*/
    bool OnBtnMixSelCns(TNotifyUI& msg);

    bool OnBtnMixDelete(TNotifyUI& msg);

    bool OnBtnSelRoomOK(TNotifyUI& msg);
    bool OnBtnSelCancel(TNotifyUI& msg);
    bool OnBtnSelAll(TNotifyUI& msg);

	bool OnBtnMixShowScreen(TNotifyUI& msg);
	bool OnBtnMixHideScreen(TNotifyUI& msg);
    bool OnCheckConfCnsItem(TNotifyUI& msg);

	bool OnMixCheckSrceen( TNotifyUI& msg );

    /** 开启画面合成器
	*  @param[in]
	*  @return 
	*/
    bool OnCheckOpenVidMix(TNotifyUI& msg);

    bool OnCheckMixBroadcast(TNotifyUI& msg);

    bool OnCheckVideoMixShortCut(TNotifyUI& msg);

	//letterindex点击
	bool OnLetterIndex(TNotifyUI& msg);

    bool OnSearchEditChange( TNotifyUI& msg );

    /** 刷新画面合成通道Layout
	*  @return 
	*/
    void UpdateVmpCfgLayout();

    void UpdateVmpCfgItem( u16 nIndex, CListContainerElementUI* pContainerElementUI );

    //更新界面按钮状态
    void UpdateVmpUIState();

    void UpdateVmpLayoutStyleSpecFour();
    void UpdateVmpLayoutStyleSix();
    void UpdateVmpLayoutStyleSeven();
    void UpdateVmpLayoutStyleEight();
    void UpdateVmpLayoutStyleTen();
    void UpdateVmpLayoutStyleTenM();
    void UpdateVmpLayoutStyleThirteen();
    void UpdateVmpLayoutStyleThirteenM();

    void UpdateCnsList();
	void UpdateShowList();

    void SetBrdVmpReq();

    //画面合成状态通知
    bool OnBrdVmpNty( WPARAM wParam, LPARAM lParam, bool& bHandle );

    bool OnRervesBrdVmpInd( WPARAM wParam, LPARAM lParam, bool& bHandle );

    bool OnSaveVmpCfgInd( WPARAM wParam, LPARAM lParam, bool& bHandle );

    bool OnRefreshCnsList( WPARAM wParam, LPARAM lParam, bool& bHandle );

    bool OnConfStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnShortCutVMix( WPARAM wParam, LPARAM lParam, bool& bHandle );
    
    APP_DECLARE_MSG_MAP()
	
private:
    CTouchListUI*             m_pMixCfgList;        //配置列表
    vector<TVidMixStyleInfo>  m_vctMixStyleInfo;    //画面合成风格

    vector<TVidMixBkgImg>     m_vctMixBkgImg;       //所有背景图片类型

    //EMVmpStyle                m_emVmpStyle;         //当前合成风格
    TVidMixStyleInfo          m_tChooseStyleInfo;   //新选择的合成风格
    int                       m_nCtrlIndex;         //当前操作的合成通道索引
    int                       m_nCurrentVmpIndex;   //当前选中的合成器索引

    TBrdVmpStyle              m_tLocalVmpStyle;     //记录本地合成器信息
    TBrdVmpResNtfy            m_tCurrentBrdVmp;     //服务器当前合成器状态     
    vector<TBrdVmpResNtfy>    m_vctBrdVmpInfo;      //所有合成器的状态

	vector<TCnsInfo>          m_vctCurrentCnsList;   //显示的Cns列表
    vector<TCnsInfo>          m_vctCnsList;          //Cns列表
    //vector<TCnsInfo>          m_vctSelCnsList;       //选中会场列表
	vector<pair<TCnsInfo,vector<int>>> m_vctSelCnsList;//选中会场列表<会场信息,选中会场屏幕>

    TCMSConf                  m_tConfInfo;           //当前会议信息

    BOOL                      m_bVmpAuto;           //当前风格是否是自动
    BOOL                      m_bWaitRerves;        //等待占用回复消息，期间不更新ResNtfy

	bool                      m_bIsSelAll;          //是否会议列表全选
	String                    m_strArrayScreen[MAX_SEAT_COUNT];  //左中右显示字符   
};

