/** @defgroup 地址簿逻辑单元 
 *  @version V1.1.4
 *  @author  肖楚然
 *  @date    2014.8.18
 */
#pragma once
class CAddrBookLogic : public CNotifyUIImpl, public Singleton<CAddrBookLogic> 
{
public:
	CAddrBookLogic(void);
	~CAddrBookLogic(void);

	void P2PCallFail();
    void OnWaitRefreshOverTime();
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

	/** 刷新
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnBtnRefresh(TNotifyUI& msg);

	/** 勾选条目
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnCheckAddrItem(TNotifyUI& msg);
	/** 呼叫
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnBtnAddrCall(TNotifyUI& msg);

    bool OnBtnAddrLabel(TNotifyUI& msg);

	/** 点击地址簿条目
	*  @param[in] 消息
	*  @return 
	*/
	bool OnAddrItemClick(TNotifyUI& msg);
	bool OnAddrItemDBClick(TNotifyUI& msg);
    /** 点击邀请会场
	*  @param[in] 消息
	*  @return 
	*/
    bool OnBtnInviteCns(TNotifyUI& msg);

    bool OnBtnCnsIsSel(TNotifyUI& msg);

    /** 点击配置
	*  @param[in] 消息
	*  @return 
	*/
    bool OnBtnAddrConfig(TNotifyUI& msg);

    /** 点击临时呼叫
	*  @param[in] 消息
	*  @return 
	*/
    bool OnBtnTemporaryCall(TNotifyUI& msg);

    /**	 
	* 功能:  点击地址簿回到主路径
	* @return   
	*/
    bool OnBtnAddrMainPath(TNotifyUI& msg);
    /**	 
	* 功能:  点击地址簿子路径
	* @return   
	*/
    bool OnBtnGroupPath1(TNotifyUI& msg);


    bool OnBtnNoticeBack(TNotifyUI& msg);
	

	bool UpdateLocalAddrBook(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnConfStateNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnHungupConfInd(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnUpdateGlobalAddrBook(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnAddrBookModify(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnAddrBookDelete(WPARAM wParam, LPARAM lParam, bool& bHandle);

	//更新显示出的列表
	void UpdateShowList();
	void UpdateLocalAddrList();
	void UpdateGlobalAddrList();
	void UpdateGroupMemberList( u32 dwGroupIndex );
    //获得筛选后的列表
    void GetOptnShowList( vector<TAddrItem>& vctList );

    /**	 
	* 功能:  更新地址簿目录路径
	* @return   
	*/
	void UpdateAddrPath();

    bool OnComboShowEx( TNotifyUI& msg );

    bool OnSearchEditChange( TNotifyUI& msg );

	//letterindex点击
	bool OnLetterIndex(TNotifyUI& msg);

    /**	 
	* 功能:  呼叫其它会场
	* @return   
	*/
    bool OnBtnAddrInviteOther( TNotifyUI& msg );

    /**	 
	* 功能:  临时呼叫
	* @return   
	*/
    bool OnBtnAddrTemporaryCall( TNotifyUI& msg );

    /**	 
	* 功能:  Edit激活弹出软键盘
	* @return   
	*/
    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

	APP_DECLARE_MSG_MAP()

private:
	CTouchListUI     *m_pAddrList;

	vector<TAddrItem> m_vctLocalList;            //第一级本地地址簿列表
	vector<TAddrItem> m_vctEntryList;            //本地地址簿所有条目
	vector<TAddrItem> m_vctGroupMemberList;      //分组成员列表
	vector<TAddrItem> m_vctSelectList;           //选中列表
	vector<TAddrItem> m_vctSearchList;           //搜索到的列表
	vector<TAddrItem> m_vctShowList;             //当前实际显示的列表
    vector<TGroupInfo> m_vctGroupPath;           //组路径

    EM_ItemType       m_emSelType;            //选中类型
    BOOL              m_bSearchEdit;
	int               m_nSelIndex;  
    TGroupInfo        m_SelGroup;            //当前所在组
    EM_AddrShowState  m_emAddrShowState;     //筛选状态

	static const String strAddrList;
	static const String strAddrListItem;	 //地址簿列表单元
	static const String strAddrName;	     //地址簿条目名
	static const String strAddrE164;	     //地址簿E164号
};

