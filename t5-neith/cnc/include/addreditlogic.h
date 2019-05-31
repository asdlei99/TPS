#if !defined(AFX_ADDREDITLOGIC_H__INCLUDED_)
#define AFX_ADDREDITLOGIC_H__INCLUDED_
/** @defgroup 地址簿编辑逻辑单元 
 *  @version V1.1.4
 *  @author  肖楚然
 *  @date    2015.1.29
 */
#pragma once


enum EM_AddrBookType
{
	em_AddrBook_Normal,
	em_AddrBook_Add, 
	em_AddrBook_Modify,
};

enum EM_OperateType
{
	em_AddrBook_Copy, 
	em_AddrBook_Cut,
};

class CAddrEditLogic : public CNotifyUIImpl, public Singleton<CAddrEditLogic> 
{
public:
	CAddrEditLogic(void);
	~CAddrEditLogic(void);

    void OnAddrEditTabSwitch( EmTitleTabID emTab );

    void OnWaitRefreshOverTime(); 

    void OnExitAddrEdit(); //离开界面 

    void UpdateTouchlist();
    void RefreshTouchlist();

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

	/** 点击地址簿条目 
	 *  @param[in] 
	 *  @return 
	 */
	bool OnAddrItemClick(TNotifyUI& msg);

    bool OnGlobalAddrItemClick(TNotifyUI& msg);
	//双击进入组
	bool OnAddrItemDBClick( TNotifyUI& msg );

	bool OnCheckAddrItem(TNotifyUI& msg);

    bool OnBtnAddrCfg(TNotifyUI& msg);

    bool OnBtnAddrLabel(TNotifyUI& msg);

    bool OnBtnGlobalAddrLabel(TNotifyUI& msg);


    bool OnBtnSelectAll(TNotifyUI& msg);

	bool OnBtnCopy(TNotifyUI& msg);

	bool OnBtnCut(TNotifyUI& msg);

	bool OnBtnPaste(TNotifyUI& msg);

	bool OnBtnDelete(TNotifyUI& msg);

    bool OnBtnCnsIsSel(TNotifyUI& msg);

	bool DelAddrEntry();

	void GetGroupAndLowGroup( u32 dwGroupIndex, vector<u32>& vctGroup );


    bool OnComboShowEx(TNotifyUI& msg);
	/** 点击更多操作 
	 *  @param[in] 
	 *  @return 
	 */
	bool OnComboMore(TNotifyUI& msg);

	bool OnBtnSaveAddr(TNotifyUI& msg);
	bool OnBtnCancelAddr(TNotifyUI& msg);

    bool SaveAddrEntry();
    bool SaveAddrGroup();

	/**	 
	* 功能:  获取分组成员列表
	* @param[in]  dwGroupIndex  组索引
	* @remarks  
	*/
	void GetAddrGroupMember( u32 dwGroupIndex );
    /**	 
	* 功能:  删除组及其下级组 及里面的条目
	* @param[in]  dwGroupIndex  组索引
	* @remarks  
	*/
    void DeleteGroupAndSubGroup( u32 dwGroupIndex );

	/**	 
	* 功能:  搜索框消息响应
	* @return  bool
	* @remarks  
	*/
	bool OnSearchEditChange( TNotifyUI& msg );

    bool OnOnlineSearchEditChange( TNotifyUI& msg );

	//letterindex点击
	bool OnLetterIndex(TNotifyUI& msg);
	bool OnLetterIndex2(TNotifyUI& msg);

	bool UpdateLocalAddrBook( WPARAM wParam, LPARAM lParam, bool& bHandle );

    bool UpdateGlobalAddrBook( WPARAM wParam, LPARAM lParam, bool& bHandle );

    bool OnAddEntryNty( WPARAM wParam, LPARAM lParam, bool& bHandle );

    bool OnAddGroupNty( WPARAM wParam, LPARAM lParam, bool& bHandle );

    bool OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle );

    bool OnAddrBookModify(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnAddrBookDelete(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/**	 
	* 功能:  更新当前显示列表
	* @return   
	*/
	void UpdateShowList();

    void UpdateUIState();

    void UpdateGlobalUIState();

    void UpdateGlobalShowList();
	
	void UpdateLocalAddrList();
	void UpdateGlobalAddrList();

    /**	 
	* 功能:  更新地址簿目录路径
	* @return   
	*/
	void UpdateAddrPath();

    //获得筛选后的列表
    void GetOptnShowList( vector<TAddrItem>& vctCurrentList );

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

    bool OnBtnOnlineAllSel(TNotifyUI& msg);
    /**	 
	* 功能:  点击刷新
	* @return    
	*/
    bool OnRefreshAddr(TNotifyUI& msg);

    bool OnBtnOnlineCnsIsSel(TNotifyUI& msg);
    /**	 
	* 功能:  导入至本地
	* @return    
	*/
    bool OnBtnLoadToLocal(TNotifyUI& msg);
    /**	 
	* 功能:  从全部地址簿中导入（每次导入一条，接到回应后继续下一条）
	* @return  
	* @remarks
	*/
	void LoadToLocal();

    /**	 
	* 功能:  Edit激活弹出软键盘
	* @return   
	*/
    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

	APP_DECLARE_MSG_MAP()
		
private:
	CTouchListUI     *m_pAddrList;
    CTouchListUI     *m_pOnlineAddrList;     //全局地址簿

	vector<TAddrItem> m_vctLocalList;        //本地地址簿列表	
	vector<TAddrItem> m_vctGroupMemberList;  //组成员列表
	vector<TAddrItem> m_vctSelectList;       //选中列表
	vector<TAddrItem> m_vctShowList;         //当前显示列表
	vector<TAddrItem> m_vctSearchList;       //搜索出的列表
	vector<TAddrItem> m_vctOperateList;      //选中且已被操作列表

    vector<TAddrItem> m_vctGlobalList;       //全局地址簿列表
    vector<TAddrItem> m_vctGlobalShowList;   //全局地址簿显示列表
    vector<TAddrItem> m_vctGlobalSearchList; //全局地址簿搜索出的列表
    vector<TAddrItem> m_vctGlobalSelectList; //全局地址簿选中列表

    vector<TGroupInfo> m_vctGroupPath;       //组路径

	int               m_nSelIndex;			 //当前选中条目索引
    int               m_nGlobalSelIndex;	 //在线地址簿选中条目索引
    EM_ItemType       m_emSelType;           //选中类型
	TAddrItem         m_tSelItem;            //当前选中条目
    TAddrItem         m_tEditItem;           //当前编辑条目
	TGroupInfo        m_SelGroup;            //当前所在组
	BOOL              m_bGlobalAddr;         //是否在全局地址簿界面
	BOOL              m_bSearchEdit;         //是否在搜索

	EM_ItemType       m_emEditType;          //编辑类型
	EM_AddrBookType   m_emAddrBookType;      //添加/修改
	EM_OperateType    m_emOperateType;       //复制/剪切
	EM_AddrShowState  m_emShowState;         //筛选状态

    BOOL              m_bLoadToLocal;        //是否有地址簿导入     
    u32               m_dwGlobalAddrIndex;   //记录要导入地址簿的序号

	static const String strAddrEditList;
};

#endif // !defined(AFX_ADDREDITLOGIC_H__INCLUDED_)

