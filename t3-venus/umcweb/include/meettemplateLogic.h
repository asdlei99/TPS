/*****************************************************************************
模块名      : CMeetTemplateLogic
文件名      : meettemplateLogic.h
相关文件    : 
文件实现功能: umcweb 会议模板配置管理模块
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/5/22      1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_MEETINGTEMPLATE_H__F51438F9_4139_4D44_BD54_032B7D0600E3__INCLUDED_)
#define AFX_MEETINGTEMPLATE_H__F51438F9_4139_4D44_BD54_032B7D0600E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMeetTemplateLogic.h : header file
//
#include "mediacfglogic.h"
#include "meetdiscusslogic.h"

class CMeetTemplateLogic : public CDlgChild
{
// Construction
public:
	CMeetTemplateLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMeetTemplateLogic)
	enum { IDD = IDD_DIALOG_MEETTEMPLATE };
	CTransparentBtn	m_btnReturn;
	CTransparentEdit	m_edtDotHour;
	CTransparentBtn	m_btnSetTop;
	CTransparentBtn	m_btnSetBottom;
	CTransparentBtn	m_btnRemoveAll;
	CTransparentBtn	m_btnMoveUp;
	CTransparentBtn	m_btnMoveDown;
	CTransparentBtn	m_btnAllAdd;
	CTransparentBtn	m_btnStartConf;
	CTransparentStatic	m_stChildBkRight;
	CTransparentStatic	m_stChildBkLeft;
	CTransparentCheckButton	m_btnCheckCur;
	CTransparentCheckButton	m_btnCheckOrder;
	CTransparentBtn		m_btnSave;
	CTransparentBtn		m_btnCancel;
	CTransparentBtn		m_btnEdit;
	CTransparentEdit	m_etSearch;
	CTransparentBtn		m_btnNewTmp;
	CTransparentBtn		m_btnDelete;
	CTransparentBtn		m_btnAllSel;
	CTransparentStatic	m_stTemplateLeftTitle;
	CTransparentStatic	m_stTemplateRightTitle;
	CTransparentBtn	m_btnMeetingInfo;
	CTransparentBtn	m_btnGroupInfo;
	CTransparentBtn	m_btnPollingInfo;
	CTransparentBtn	m_btnDiscussInfo;
	CTransparentStatic	m_stName;
	CTransparentStatic	m_stNumber;
	CTransparentStatic	m_stTmpType;
	CTransparentStatic	m_stDate;
	CTransparentStatic	m_stStartTime;
	CTransparentStatic	m_stNameShow;
	CTransparentStatic	m_stNumberShow;
	CTransparentStatic	m_stTmpTypeShow;
	CTransparentStatic	m_stDateShow;
	CTransparentStatic	m_stStartTimeShow;
	CTransparentStatic	m_stConfRate;
	CTransparentStatic	m_stConfRateShow;
	CTransparentStatic	m_stConfRateUnit;
	CTransparentEdit	m_etConfRate;
	CTransparentStatic	m_stShowRate;
	CTransparentStatic	m_stShowRateShow;
	CTransparentStatic	m_stShowRateUnit;
	CTransparentEdit	m_etShowRate;
	CTransparentEdit	m_etName;
	CTransparentEdit	m_etNumber;	
	CTransparentEdit	m_etSetHour;
	CTransparentEdit	m_etSetMin;
	CTransparentBtn		m_btnCurrentMeet;
	CTransparentBtn		m_btnOrderMeet;
	CTransparentCheckButton		m_btnCalendar;
	CTransparentBtn		m_btnPlusTime;
	CTransparentBtn		m_btnSubTime;
	CTransparentEdit	m_etDateSet;
	CTransparentStatic	m_stIntervel;
	CTransparentStatic	m_stPollingSecond;
	CTransparentEdit	m_etPollingTime;
	CTransparentBtn		m_btnSubPollingTime;
	CTransparentBtn		m_btnPlusPollingTime;
	CTransparentStatic	m_stHomeMeeting;
	CTransparentEdit	m_etHomeMeeting;
	CTransparentStatic	m_stMediaInfo;
	CTransparentEdit	m_etAdaptRes;
	CTransparentBtn		m_btnMediaInfo;
	CTransparentBtn		m_btnSubConfRate;
	CTransparentBtn		m_btnPlusConfRate;
	CTransparentBtn		m_btnSubShowRate;
	CTransparentBtn		m_btnPlusShowRate;
	CTransparentSwitchButton m_btnSwitchPolling;
	//}}AFX_DATA

private:                                //控件元素
	CListChild* m_plsMeetTmp;
	CListChild* m_plsMeetEpRight;
	CListChild* m_plsMeetPollingRight;
	CListChild* m_plsLocalAddrbook;
	CListChild* m_plsPollingLeft;
	CListChild* m_plsDiscussLeft;
	
	CLetterIndex* m_pLetterTmp;
	CLetterIndex* m_pLetterAddrbook;
	CLetterIndex* m_pLetterPolling;
	CLetterIndex* m_pLetterDiscuss;

	CMediaCfgLogic m_dlgMediaCfg;
	CMeetDiscussLogic m_dlgMeetDiscuss;

public:
	CCalendarDlg m_dlgCalendar;         //公共供外面调用隐藏 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeetTemplateLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMeetTemplateLogic)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnNew();
	afx_msg void OnBtnDelete();
	afx_msg void OnBtnEdit();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnCancel();
	afx_msg void OnBtnAllSelect();
	afx_msg void OnBtnMeetingInfo();
	afx_msg void OnBtnEpInfo();
	afx_msg void OnBtnPollingInfo();
	afx_msg void OnBtnDiscussInfo();
	afx_msg void OnBtnPlusTime();
	afx_msg void OnBtnSubTime();
	afx_msg LRESULT OnTmpListOperateResult(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT UpdateGroupEpList( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT UpdatePollingList( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnRefreshAddrListListNotify(WPARAM wParam, LPARAM lParam); 
	afx_msg LRESULT OnRefreshTmpListNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnStartConfResult(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnConfTmpResUsedCountNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDelAllConftempRet(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnBtnCalendar();
	afx_msg void OnBtnCheckOrderConf();
	afx_msg void OnBtnCheckCurConf();
	afx_msg void OnBtnStartConf();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg LRESULT OnNoSelResultNotify(WPARAM wParam, LPARAM lParam);        //未选择任何用户列表通知
	afx_msg LRESULT OnUpdateCalendarSelDate(WPARAM wParam, LPARAM lParam);    //日历选择时间
	afx_msg LRESULT OnDiscussEpChange(WPARAM wParam, LPARAM lParam);		  //参与讨论的会场改变
	afx_msg LRESULT OnSwitchDiscuss(WPARAM wParam, LPARAM lParam);			  //开启/关闭会议讨论
	afx_msg void OnBtnAllAdd();
	afx_msg void OnBtnSetTop();
	afx_msg void OnBtnSetBottom();
	afx_msg void OnBtnRemoveAll();
	afx_msg void OnBtnMediaInfo();
	afx_msg void OnBtnMoveUp();
	afx_msg void OnBtnMoveDown();
	afx_msg	void OnSearchEditChange();
	afx_msg HRESULT OnHideWndNotify( WPARAM wparam, LPARAM lparam );
    afx_msg HRESULT OnBtnHold( WPARAM wparam, LPARAM lparam );
    afx_msg HRESULT OnBtnHoldEnd( WPARAM wparam, LPARAM lparam );
	afx_msg void OnSetfocusEditHour();
	afx_msg void OnSetfocusEditMinute();
	afx_msg void OnBtnReturn();
	afx_msg void OnBtnSubConfRate();
	afx_msg void OnBtnPlusConfRate();
	afx_msg void OnBtnSubShowRate();
	afx_msg void OnBtnPlusShowRate();
	afx_msg void OnBtnSubPollingTime();
	afx_msg void OnBtnPlusPollingTime();
	afx_msg LRESULT OnClickSwitchBtn(WPARAM wParam, LPARAM lParam);
	afx_msg	void OnConfRateEditChange();
	afx_msg	void OnShowRateEditChange();
    afx_msg	LRESULT OnDragEnd(WPARAM wParam, LPARAM lParam);
	afx_msg	LRESULT OnEditSetFocus(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnKillFoucs(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUmsReasonInd(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	//--- 页面环境 begin ----------------------------------------------------------

	/*=============================================================================
    函 数 名:InitDlg
    功    能:页面销毁抢断后初始化
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/20  1.0               创建
    =============================================================================*/
    void InitDlg();

	/*=============================================================================
    函 数 名:RegisterFun
    功    能:List点击函数注册
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/20  1.0     刘德印    创建
    =============================================================================*/
	void RegisterFun();

	/*=============================================================================
    函 数 名:CreatePageControls
    功    能:创建页面所需的全部控件环境
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/12  1.0     刘德印    创建
    =============================================================================*/
	BOOL CreatePageControls();

	/*=============================================================================
    函 数 名:InitControlPane
    功    能:初始化页面控件
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/20  1.0     刘德印    创建
    =============================================================================*/
	virtual BOOL InitControlPane();
	BOOL InitMeetInfoPageControl();	    //会议信息页面 
	BOOL InitMeetEpPageControl();		//会场信息页面
	BOOL InitMeetPollingPageControl();	//会场轮询信息页面
	BOOL InitMeetDiscussPageControl();  //会议讨论页面

	/*=============================================================================
    函 数 名:SetControlPos
    功    能:设置所有控件元素位置  提供给自适应分辨率
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/20  1.0     刘德印    创建
    =============================================================================*/
	void SetControlPos();

	/*=============================================================================
    函 数 名:GetLibPtr
    功    能:得到当前页面所需umslib接口指针
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/10  1.0     刘德印    创建
    =============================================================================*/
	void GetLibPtr();

	/*=============================================================================
    函 数 名:ShowPageScanf ShowPageEdit ShowPageNew
    功    能:浏览、编辑、新建状态页面控件显示
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/16  1.0     刘德印    创建
    =============================================================================*/
	void ShowPageScanf();
	void ShowPageEdit();
	void ShowPageNew();
	void ShowMeetInfoScanfPage(BOOL bShow);				   //显示会议信息浏览页面   媒体页面显示隐藏控制
	void ShowMeetInfoEditPage(BOOL bShow);				   //显示会议信息新建、编辑页面   媒体页面显示隐藏控制


	/*=============================================================================
    函 数 名:HideAllPageCtrl
    功    能:隐藏所有控件
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/20  1.0     刘德印    创建
    =============================================================================*/
	void HideAllPageCtrl();

	/*=============================================================================
    函 数 名:ResetInitPage
    功    能:重置界面控件
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/08  1.0     刘德印    创建
    =============================================================================*/
	void ResetInitPage();

	/*=============================================================================
    函 数 名:UpdateUIState
    功    能:全选等按钮状态控制
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/06/29  1.0     刘德印    创建
    =============================================================================*/
	void UpdateUIState();
	void ShowSortControl(BOOL bShow);       //排序控件显示
	void UpdateSortControlUIState();
	void SetSortControlDisable();           //无当前选中列表则显示禁止

	void ResetSerchEditLen();				//重置查询框的大小
	void SetAddrbookSerchEditLen();			//设置地址簿查询框位置
	void SetPollingLeftviewSerchEditLen();  //设置轮询左侧视图的查询框位置

	void SetMediaInfoBtnPos(BOOL bDefaut = TRUE);  //动态设置媒体控件位置
	void SetMediaInfoBtnHide(BOOL bHide = TRUE);   //设置媒体控件显示隐藏
	void SetMediaCfgHide(BOOL bHide = TRUE);	   //设置媒体配置页面显示隐藏

	void SetRateInfoPos(BOOL bDefaut = TRUE);      //动态设置码率控件位置
	void SetRateInfoHide(BOOL bHide = TRUE);       //设置码率控件显示隐藏

//	void UpdatePollingUIState();			       //会议轮询界面控件状态控制

	//--- 页面环境 end -------------------------------------------------------------


	//--- 数据域 begin -------------------------------------------------------------

	/*=============================================================================
    函 数 名:MeetTmpRefresh
    功    能:刷新会议模板
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/26  1.0     刘德印    创建
    =============================================================================*/
	void MeetTmpRefresh();

	/*=============================================================================
    函 数 名:UpdateAddrbookShowList
    功    能:列表中显示地址簿信息
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/26  1.0     刘德印    创建
    =============================================================================*/
	void UpdateAddrbookShowList();

	/*=============================================================================
    函 数 名:UpdateTmpShowList
    功    能:会议模板展现统一接口
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/06/28  1.0     刘德印    创建
    =============================================================================*/
	void UpdateTmpShowList();

	/*=============================================================================
    函 数 名:UpdatePollingLeftShowList
    功    能:轮询左侧列表展现统一接口
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/06/28  1.0     刘德印    创建
    =============================================================================*/
	void UpdatePollingLeftShowList( std::map<u16,CString>& mapEpList, BOOL bIsShowIcon );

	void UpdatePollingLeftIcon();

	/*=============================================================================
    函 数 名:UpdateDiscussLeftShowList
    功    能:会议讨论左侧列表展现统一接口
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2014/02/18  1.0     徐华秀    创建
    =============================================================================*/
	void UpdateDiscussLeftShowList( std::map<u16,CString>& mapEpList, BOOL bIsShowIcon );

	/*=============================================================================
    函 数 名:UpPollCns DownPollCns TopPollCns BottomPollCns
    功    能:轮询列表排序操作
    参    数:wCurRow                          [in]   当前点击行
    注    意:无
    返 回 值:u16返回成功标志
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/20  1.0     刘德印    创建
    =============================================================================*/
	u16 UpPollControl( u16 wCurRow );
	u16 DownPollControl( u16 wCurRow);
	u16 TopPollControl( u16 wCurRow );
	u16 BottomPollControl( u16 wCurRow );

	//浏览 编辑 新建 页面控件数据赋值
	void SetSelectedTmpDataToScanfPage(const TTPConfTemplate& tConfTmplate);
	void SetSelectedTmpDataToEditPage();
	void SetInitDataToNewPage();

	//会场列表、轮训列表、会议讨论列表赋值
	void SetEpListPageToEditPage(const TTPConfTemplate& tSelConfTmplate);
	void SetTurnListPageToEditPage(const TTPConfTemplate& tSelConfTmplate);
	void SetDiscussListPageToEditPage(const TTPConfTemplate& tSelTemplate);
	void CleanPageList();           //清空列表包含会场列表和轮询列表

	void FilterAddrbookList();
	void FilterPollingLeftList();    //显示查询轮询左侧列表数据
	void FilterDiscussLeftList();    //显示查询会议讨论左侧列表数据

	//--- 数据域 end -------------------------------------------------------------


	//--- 列表点击事件 begin -----------------------------------------------------

	/*=============================================================================
    函 数 名:OnClickTmpLstItem
    功    能:模板列表点击事件
    参    数:const IArgs & arg                          [in]    点击value
    注    意:无
    返 回 值:bool成功失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/20  1.0     刘德印    创建
    =============================================================================*/
	bool OnClickTmpLstItem( const IArgs & arg );
    bool OnClickTmpLstItemIcon( const IArgs & arg );

	/*=============================================================================
    函 数 名:OnClickAddrbookLstItem
    功    能:地址簿列表点击事件
    参    数:const IArgs & arg                          [in]    点击value
    注    意:无
    返 回 值:bool成功失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/20  1.0     刘德印    创建
    =============================================================================*/
	bool OnClickAddrbookLstItem( const IArgs & arg );
    bool OnClickAddrbookLstItemIcon( const IArgs & arg );

	/*=============================================================================
    函 数 名:OnClickPollingPageLeftLstItem
    功    能:轮训页面左侧列表点击事件
    参    数:const IArgs & arg                          [in]    点击value
    注    意:无
    返 回 值:bool成功失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/20  1.0     刘德印    创建
    =============================================================================*/
	bool OnClickPollingPageLeftLstItem( const IArgs & arg );
    bool OnClickPollingPageLeftLstItemIcon( const IArgs & arg );

	/*=============================================================================
    函 数 名:OnClickGroupPageDelItemIcon
    功    能:会场列表点击删除事件
    参    数:const IArgs & arg                          [in]    点击value
    注    意:无
    返 回 值:bool成功失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/20  1.0     刘德印    创建
    =============================================================================*/
    bool OnClickGroupPageDelItemIcon( const IArgs & arg );

	/*=============================================================================
    函 数 名:OnClickPollingPageDelItem
    功    能:轮训列表点击删除事件
    参    数:const IArgs & arg                          [in]    点击value
    注    意:无
    返 回 值:bool成功失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/20  1.0     刘德印    创建
    =============================================================================*/
	bool OnClickPollingPageDelItem( const IArgs & arg );
    bool OnClickPollingPageDelItemIcon( const IArgs & arg );

	/*=============================================================================
    函 数 名:OnClickDiscussPageLeftLstItem
    功    能:会议讨论页面左侧列表点击事件
    参    数:const IArgs & arg                          [in]    点击value
    注    意:无
    返 回 值:bool成功失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2014/02/18  1.0     徐华秀    创建
    =============================================================================*/
	bool OnClickDiscussPageLeftLstItem( const IArgs & arg );
    bool OnClickDiscussPageLeftLstItemIcon( const IArgs & arg );

	//--- 列表点击事件 end --------------------------------------------------------

	//--- 类公共函数 begin --------------------------------------------------------

	CString FindConfTurnListById(u16 nId);						         //通过轮询id在会场列表中匹配会场名称
	u16  FindConfTurnListByAlias(CString strTurnListName);		         //通过轮询列表名称在会议列表中匹配id
	CString FindConfDiscussListById(u16 nId);						     //通过讨论会场id在与会会场列表中匹配会场名称
	u16  FindConfDiscussListByAlias(CString strDiscussListName);		 //通过讨论列表名称在与会会场列表中匹配id
	BOOL CheckTmpMeetInfo();									         //检测会议信息页面数据
	BOOL CheckIsInputHomeMeeting();								         //检测主会场信息是否输入
//	BOOL HomeMeetExistInEpList(const CString& strHomeMeetName);          //检测主会场是否已经存在分会场 
	u16 FindMeetInEpList(const CString& strMeetName, const CString& strMeetNum, BOOL bHomeMeet = FALSE); //查找此会场在分会场中的id
	void ReSetCnsEpId(u16 uDelPos);                                      //重置分会场ID
	void CleanSearchList();                                              //三个视图公用查询框   发生切换视图  清空列表
	TTPConfTemplate* GetConfTemplateByID( u16 wConfTemplateID ) const ;	 //根据会议ID获取会议模板指针 
	BOOL AddToEpList( const CString& strAddrbookName, const CString& strAddrbookNum, BOOL bIsHomeConfChec = TRUE ); 
	void UpdateResUsedCountToControl( u16 wResNum );                     //更新资源占用情况
	void UpdateDiscussShowListData();								     //更新会议讨论左侧列表数据(主会场+分会场)
	void UpdateGroupEpInfoList(const CString& strAddrbookName, const CString& strAddrbookNum, u16 wEpID); //更新m_mapEpInfoList数据

	bool ClickAddrbookLstItemIcon( const Data_AddrItemInfo *pItemInfo );
	bool ClickPollingPageLeftLstItemIcon( const Data_CnsAddr *pItemInfo );

	void UpdateSearchEdtStatus();											 //更新查询编辑框状态

	//--- 类公共函数 begin --------------------------------------------------------
private:
	CConfCtrlIF* m_pconfCtrlIF;             //会议控制接口
	CConfTemplateCtrlIF* m_tTmpConfigIF;    //模板控制接口 
	CCncAddrbookIF*  m_pAddrBookIF;         //地址簿接口
	CUmsConfigCtrlIF *m_pUmsConfig;
	
	TCMSConfTemplate m_tNewTemplate;        //当前点击新建模板
	TCMSConfTemplate m_tSelTemplate;        //当前点击选中模板

	TCMSConfTemplate  m_tBaseTemplate;		//原始选中模板媒体信息

	EM_OPERATE_FLAG m_emOperateFlag;        //当前操作状态  编辑 新建 浏览
	EM_CURRENT_TABPAGE m_emTabFlag;         //当前点击页面  会议信息  会场信息   轮询信息

	BOOL m_bIsAllSel;
	s32  m_nCurPollingListSortRow;          //当前点击轮询行号  供排序操作使用
	s32  m_nTurnLeftListCount;              //查询后记录轮询列表的条目数   用于控制全部添加按钮状态

	EM_CURRENT_FOCUS     m_emCurFocus;

	//搜索集合
	TplArray<TTPConfTemplate> m_tpTmpRefreshList;    //会议模板刷新列表
	TplArray<TTPConfTemplate> m_tpTmpShowList;       //会议模板展现列表
	TplArray<TTPConfTemplate> m_tpTmpSearchList;     //会议模板查询列表

	vector<TAddrItem> m_vecLocalbookRefreshList;     //本地地址簿刷新列表
	vector<TAddrItem> m_vecLocalbookShowList;		 //本地地址簿展现列表
	vector<TAddrItem> m_vecLocalbookSearchList;		 //本地地址簿查询列表

	std::map<u16,CString> m_mapEpList;               //存储当前点击行或新建模板的会场列表   新建及编辑状态下使用   id作为删除索引时候使用        
	std::map<u16,CString> m_mapEpSearchList;  
	std::vector<CString> m_vecTurnList;              //存储当前点击行或新建模板的轮询列表  新建状态及编辑下使用
	std::set<CString> m_setSelectedTmpIconItem;      //存储当前点击勾选的模板set集
	u16 m_wResUsedCount;                             //当前资源数
	std::map<u16,TEpAddr> m_mapEpInfoList;           //存储当前点击行或新建模板的会场列表(包括会场e164、ip)   新建及编辑状态下使用   点击保存给ums发送数据时使用

	//会议讨论
	std::map<u16,CString> m_mapDiscussList;          //存储会议讨论界面左侧列表数据
	std::map<u16,CString> m_mapDiscussSearchList;    //会议讨论界面左侧列表查询数据
	std::map<u16,CString> m_mapDiscussSelItem;       //存储会议讨论界面勾选的会场

	BOOL m_bSwitchPolling;							 //是否开启会议轮询
	BOOL m_bSwitchDiscuss;							 //是否开启会议讨论
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEETINGTEMPLATE_H__F51438F9_4139_4D44_BD54_032B7D0600E3__INCLUDED_)
