#if !defined(AFX_ADDREDITLOGIC_H__0C0D4FD7_0F38_42EE_BF69_63626132215C__INCLUDED_)
#define AFX_ADDREDITLOGIC_H__0C0D4FD7_0F38_42EE_BF69_63626132215C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// addreditlogic.h : header file
//


enum EM_AddrBookType
{
	em_AddrBook_Normal,
	em_AddrBook_Add, 
	em_AddrBook_Modify,
};

/////////////////////////////////////////////////////////////////////////////
// CAddrEditLogic dialog

class CAddrEditLogic : public CDlgChild
{
// Construction
public:
	CAddrEditLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddrEditLogic)
	enum { IDD = IDD_DIALOG_ADDREDIT };
	CTransparentStatic	m_stcRightTitle;
	CTransparentStatic	m_stcCnNumber;
	CTransparentStatic	m_stcCnName;
	CTransparentEdit	m_edtSearch;
	CTransparentEdit	m_edtEntryNumber;
	CTransparentEdit	m_edtEntryName;
	CTransparentBtn	m_btnSave;
	CTransparentBtn	m_btnRevoke;
	CTransparentBtn	m_btnRefresh;
	CTransparentBtn	m_btnPaste;
	CTransparentBtn	m_btnLoadToLocal;
	CTransparentBtn	m_btnEdit;
	CTransparentBtn	m_btnDeleteItem;
	CTransparentBtn	m_btnDelete;
	CTransparentBtn	m_btnCut;
	CTransparentBtn	m_btnCopy;
	CTransparentBtn	m_btnCancel;
	CTransparentBtn	m_btnBackToAddr;
	CTransparentBtn	m_btnBack;
	CTransparentBtn	m_btnAllSel;
	CTransparentBtn	m_btnAllNoSel;
	CTransparentSwitchButton	m_btnAddrShowEx;
	CTransparentBtn	m_btnAddEntry;
	CTransparentStatic	m_stcLeftTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddrEditLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddrEditLogic)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	/**	 
	* 功能:  点击本地地址簿
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnBtnLocalAddr();
	/**	 
	* 功能:  点击全局地址簿
	* @return  bool
	* @remarks  
	*/
	afx_msg bool OnBtnGlobalAddr();
	
	/**	 
	* 功能:  点击返回
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnBtnBack();
	/**	 
	* 功能:  点击添加会场
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnAddEntry();
	/**	 
	* 功能:  点击添加分组
	* @return  bool
	* @remarks  
	*/
	afx_msg bool OnAddGroup();
	/**	 
	* 功能:  点击保存
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnSave();
	/**	 
	* 功能:  点击取消
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnCancel();
	/**	 
	* 功能:  点击编辑
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnEdit();
	/**	 
	* 功能:  搜索框消息响应
	* @return  bool
	* @remarks  
	*/
	afx_msg LRESULT OnSearchEditChange( WPARAM wParam, LPARAM lParam );
	/**	 
	* 功能:  点击复制
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnBtnCopy();
	/**	 
	* 功能:  点击剪切
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnBtnCut();
	/**	 
	* 功能:  点击粘贴
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnBtnPaste();
	/**	 
	* 功能:  点击撤销
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnBtnRevoke();
	/**	 
	* 功能:  点击删除
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnBtnDelete();
    /**	 
	* 功能:  点击单个条目删除
	* @return  bool
	* @remarks  
	*/
    afx_msg void OnBtnDeleteItem();
	/**	 
	* 功能:  点击更新全局地址簿
	* @return  bool
	* @remarks  
	*/	
	afx_msg void OnBtnRefreshGlobalAddr();
	/**	 
	* 功能:  点击全选/反选 全局地址簿
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnBtnSelectAll();
	afx_msg void OnBtnUnSelectAll();

	/**	 
	* 功能:  点击全局导入到本地地址簿
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnBtnLoadToLocal();

	afx_msg LRESULT OnBtnAddrShowOptn(WPARAM wParam, LPARAM lParam);
	
	afx_msg LRESULT UpdateAddrBook(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT UpdateGlobalAddrBook( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT UpdateGlobalAddrBookEx( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnAddEntryNty(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAddGroupNty(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAddrModifyNty(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnAddrOptFailed(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWaitRefreshOverTime( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnUpdateBtnAddrOptn( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnHideAddrOptn( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnNoSelResultNotify(WPARAM wParam, LPARAM lParam);        //未选择任何用户列表通知

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	/*=============================================================================
	函 数 名:InitDlg
	功    能:页面销毁抢断后初始化
	参    数:无
	注    意:无
	返 回 值:void
	-------------------------------------------------------------------------------
	修改纪录:
	日      期  版本    修改人    修改内容
	2013/04/08  1.0     石城      创建
	=============================================================================*/
	void InitDlg();

protected:
	/**	 
	* 功能:  点击本地地址簿条目
	* @return  bool
	* @remarks  
	*/
	bool OnClickAddrItem( const IArgs& args );
	

	/**	 
	* 功能:  点击本地地址簿右侧图片
	* @return  bool
	* @remarks  
	*/
	bool OnClickAddrItemIcon( const IArgs& args );

	/**	 
	* 功能:  勾选/反选 地址簿条目
	* @return  bool
	* @remarks  
	*/
	bool OnSelAddrItem( const IArgs& args );
	bool OnUnSelAddrItem( const IArgs& args );

	/**	 
	* 功能:  点击已选列表右侧图片
	* @return  bool
	* @remarks  
	*/
	bool OnClickSelectItemIcon( const IArgs& args );

	/**	 
	* 功能:  点击全局地址簿条目
	* @return  bool
	* @remarks  
	*/
	bool OnClickGlobalAddrItem( const IArgs& args );

	/**	 
	* 功能:  点击全局地址簿右侧图片
	* @return  bool
	* @remarks  
	*/
	bool OnClickGlobalAddrItemIcon( const IArgs& args );


	/**	 
	* 功能:  从选中列表中删除
	* @return  bool
	* @remarks  
	*/
	bool OnBtnDelItem( const IArgs& args );


	bool DelAddrEntry();

	bool SaveAddrEntry();
	bool SaveAddrGroup();

	/**	 
	* 功能:  确定更新全局地址簿
	* @return  bool
	* @remarks  
	*/
	bool SureRefreshGlobalAddr();

	/**	 
	* 功能:  更新当前显示列表
	* @return  
	* @remarks  
	*/
	void UpdateShowList(); 

	/**	 
	* 功能:  点击全选时，更新选中列表
	* @return  
	* @remarks  
	*/
	void UpdateAllSelShowList();   //解决bug：条目过多时，点击全选后的时间延迟  by xhx
	
	void UpdateLocalAddrList();
	void UpdateGlobalAddrList();
	void UpdateAddrTitle();
	/**	 
	* 功能:  更新界面控件状态
	* @return  
	* @remarks  
	*/
	void UpdateUIState();

	void UpdateGlobalUIState();

	void SetAddrItemInfo( TAddrInfo& tAddrInfo, CAddrEntry& cEntry );
	/**	 
	* 功能:  获取分组成员列表
	* @param[in]  dwGroupIndex  组索引
	* @remarks  
	*/
	void GetAddrGroupMember( u32 dwGroupIndex );

	/**	 
	* 功能:  删除组及其下级组
	* @param[in]  dwGroupIndex  组索引
	* @remarks  
	*/
	void DelGroupAndLowGroup( u32 dwGroupIndex );

    /**	 
	* 功能:  获取组及其下级组
	* @param[in]  dwGroupIndex  组索引
    * @param[out] vctGroup      组及下级组列表
	* @remarks  
	*/
    void GetGroupAndLowGroup( u32 dwGroupIndex, vector<u32>& vctGroup );

	/**	 
	* 功能:  列表没有选中项通知
	* @return  bool
	* @remarks  
	*/
	bool UnSelAddrList( const IArgs& args );

	/**	 
	* 功能:  更新复制粘贴剪切删除按钮状态 
	* @return  
	* @remarks  
	*/
    void UpdateCtrlButton();

    bool OnEnterAddrGroup( const IArgs& args );

    bool OnAddrOptnShowAll();
    bool OnAddrOptnShowGroup();
    bool OnAddrOptnShowOnline();
    bool OnAddrOptnShowOffline();

    //获得筛选后的列表
    void GetOptnShowList( vector<TAddrItem>& vctCurrentList );

private:
	/*=============================================================================
    函 数 名:InitControlPane
    功    能:初始化页面控件
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2013/4/7    1.0     石城      创建
    =============================================================================*/
	virtual BOOL InitControlPane();

	/*=============================================================================
    函 数 名:SetControlPos
    功    能:设置所有控件元素位置  提供给自适应分辨率
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/4/8    1.0     石城      创建
    =============================================================================*/
	void SetControlPos();

	/*=============================================================================
    函 数 名:RegisterFun
    功    能:List点击函数注册
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2013/4/8    1.0     石城      创建
    =============================================================================*/
	void RegisterFun();

	/*=============================================================================
    函 数 名:InitChildWindow
    功    能:初始化子窗口视图
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/08  1.0     石城		创建
    =============================================================================*/
	BOOL InitChildWindow();

	/**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    void Clear();

	/**	 
	* 功能:  load方案
	* @return   
	* @remarks	 
	*/
	void LoadScheme( String strScheme );

	/*=============================================================================
	函 数 名:GetAddrGroupPath
	功    能:获取分组路径
	参    数:dwGroupIndex  组索引
	注    意:
	返 回 值:无
	-------------------------------------------------------------------------------
	修改纪录:
	日      期  版本    修改人   修改内容
	2012/06/01  1.0     肖楚然     创建
	=============================================================================*/
	CString GetAddrGroupPath( u32 dwGroupIndex );

	/*=============================================================================
	函 数 名:GetAddrGroupInfo
	功    能:获取分组信息
	参    数:[in]dwGroupIndex 组索引  
			 [out]tGroupInfo  组信息
	注    意:
	返 回 值:无
	-------------------------------------------------------------------------------
	修改纪录:
	日      期  版本    修改人   修改内容
	2012/06/01  1.0     肖楚然     创建
	=============================================================================*/
	void GetAddrGroupInfo( u32 dwGroupIndex, TGroupInfo& tGroupInfo );

	/*=============================================================================
	函 数 名:UpdateAddrEntryList
	功    能:更新地址簿条目
	参    数:无
	注    意:
	返 回 值:无
	-------------------------------------------------------------------------------
	修改纪录:
	日      期  版本    修改人   修改内容
	2012/06/01  1.0     肖楚然     创建
	=============================================================================*/
	void UpdateAddrEntryList();

	/*=============================================================================
	函 数 名:UpdateLevelOneGroup
	功    能:更新第一级组
	参    数:无
	注    意:
	返 回 值:无
	-------------------------------------------------------------------------------
	修改纪录:
	日      期  版本    修改人   修改内容
	2012/06/01  1.0     肖楚然     创建
	=============================================================================*/
	void UpdateLevelOneGroup();

	/*=============================================================================
	函 数 名:DoClickAddrItem
	功    能:点击本地地址薄条目后右侧显示条目信息
	参    数:无
	注    意:
	返 回 值:无
	-------------------------------------------------------------------------------
	修改纪录:
	日      期  版本    修改人   修改内容
	2012/06/01  1.0     石城     创建
	=============================================================================*/
	void DoClickAddrItem();

	/*=============================================================================
	函 数 名:ShowSelItemInfo
	功    能:显示选中条目信息
	参    数:无
	注    意:
	返 回 值:无
	-------------------------------------------------------------------------------
	修改纪录:
	日      期  版本    修改人   修改内容
	2012/06/01  1.0     石城     创建
	=============================================================================*/
	void ShowSelItemInfo();

	/**	 
	* 功能:  更新全选控件状态
	* @return  
	* @remarks  
	*/
    void UpdateAllSelButton();

	/**	 
	* 功能:  更新刷新控件状态
	* @return  
	* @remarks  
	*/
	void UpdRefreshBtn();

	/**	 
	* 功能:  从全部地址簿中导入（每次导入一条，接到回应后继续下一条）
	* @return  
	* @remarks
	*/
	void LoadToLocal();

private:
	CListChild* m_pLocalAddrList;
	CListChild* m_pGlobalAddrList;
	CLetterIndex* m_pLetterIndex;

	CListChild* m_pListSelect;


	vector<TAddrItem> m_vctLocalList;        //本地地址簿列表
	vector<TAddrItem> m_vctGlobalList;       //全局地址簿列表
	vector<TAddrItem> m_vctGroupMemberList;  //组成员列表
	vector<TAddrItem> m_vctSelectList;       //选中列表
	vector<TAddrItem> m_vctShowList;         //当前显示列表
	vector<TAddrItem> m_vctSearchList;       //搜索出的列表
	vector<TAddrItem> m_vctOperateList;      //选中且已被操作列表
	
	vector<s32>       m_vctListOffset;       //记录每一层列表偏移量
	
	TAddrItem         m_SelItem;             //当前选中条目
	TGroupInfo        m_SelGroup;            //当前所在组

	EM_ItemType       m_emEditType;          //编辑类型
	EM_AddrBookType   m_emAddrBookType;      //添加/修改
	EM_Addrbook_OperateType    m_emOperateType;       //复制/剪切
	BOOL              m_bWaitAddEntry;       //等待添加消息
	BOOL              m_bWaitAddGroup;
	BOOL              m_bGlobalAddr;         //是否在全局地址簿界面
	EM_AddrShowState  m_emShowState;         //筛选状态
	BOOL			  m_bSearchEdit;		 //搜索状态
	BOOL              m_bInGroup;            //是否进入组内 dyy

	//---umslib控制接口 
	CCncAddrbookIF *m_pCncAddrbookIF;
	CUmsConfigCtrlIF *m_pUmsConfig;

	//BOOL m_bSipEnd;			//表示sip地址列表发送是否结束
	//BOOL m_bGkEnd;			//表示Gk地址列表发送是否结束

	BOOL m_bLoadToLocal;        //是否有地址簿导入 by xhx
	u32  m_dwGlobalAddrIndex;   //记录要导入地址簿的序号 xhx
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDREDITLOGIC_H__0C0D4FD7_0F38_42EE_BF69_63626132215C__INCLUDED_)
