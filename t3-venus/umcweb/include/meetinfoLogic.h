/*****************************************************************************
模块名      : CMeetinfoLogic
文件名      : meetinfoLogic.h
相关文件    : 
文件实现功能: umcweb 会议信息模块
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/5/28      1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_MEETINGLIST_H__ABC3C588_3E7D_40D7_987D_87B6C0BB8B54__INCLUDED_)
#define AFX_MEETINGLIST_H__ABC3C588_3E7D_40D7_987D_87B6C0BB8B54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// meetinfoLogic.h : header file//

#include "Menubar.h"
class CMeetinfoLogic : public CDlgChild
{
// Construction
public:
	CMeetinfoLogic(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CMeetinfoLogic)
	enum { IDD = IDD_DIALOG_MEETINFO };
	CTransparentCheckButton	    m_btnCheckMenu;
	CTransparentStatic	m_stCurMeetTitle;
	CTransparentStatic	m_stOrderMeetTitle;
	CTransparentStatic	m_stChildBkBottom;
	CTransparentStatic	m_stChildBkUp;
	CTransparentStatic	m_stLeftTitle;	
	CTransparentEdit	m_etSearch;
	CTransparentBtn	    m_btnAllSel;
	CTransparentBtn	    m_btnCloseMeeting;
	//}}AFX_DATA

private:
	CListChild* m_plsCurMeet;
	CListChild* m_plsOrderMeet;
	CLetterIndex* m_pLetterIndex;

public:
	CMenubar m_dlgMenubar;                        //菜单Dlg    提供给外面隐藏

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeetinfoLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMeetinfoLogic)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAllSelect();
	afx_msg void OnBtnCloseMeeting();
	afx_msg LRESULT OnRefreshTmpList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRefreshConfList( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnUpdateConfList( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnHungupConfReason( WPARAM wparam, LPARAM lparam );
	afx_msg void OnDestroy();
	afx_msg void OnBtnCheckMenu();
	afx_msg LRESULT OnClickMeetListMenuUpdate( WPARAM wParam, LPARAM lParam );
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg LRESULT OnStartConfResult(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg	void OnSearchEditChange();
	afx_msg HRESULT OnHideAUtoHideWnd( WPARAM wparam, LPARAM lparam );
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
    2012/05/19  1.0               创建
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
    2012/05/19  1.0     刘德印    创建
    =============================================================================*/
	void RegisterFun();

	/*=============================================================================
    函 数 名:InitControlPane
    功    能:初始化页面控件
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/19  1.0     刘德印    创建
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
    2012/05/28  1.0     刘德印    创建
    =============================================================================*/
	void SetControlPos();

	/*=============================================================================
    函 数 名:SelectMeetListView
    功    能:选择当前List视图
    参    数:EM_MENU_MEETTYPE emMenuType    [in]    当前视图类型
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/16  1.0     刘德印    创建
    =============================================================================*/
	void SelectMeetListView(EM_MENU_MEETTYPE emMenuType);

	/*=============================================================================
    函 数 名:UserListRefresh
    功    能:刷新当前会议列表
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/26  1.0     刘德印    创建
    =============================================================================*/
	void CurMeetListRefresh();

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
    函 数 名:GetTemplateById
    功    能:通过ID查找模板
    参    数:u16 nTmplateId                          [in]    模板ID
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/26  1.0     刘德印    创建
    =============================================================================*/
	TTPConfTemplate* GetTemplateById(u16 nTmplateId);

	/*=============================================================================
    函 数 名:OnClickCurMeetLstItem
    功    能:当前会议列表点击事件
    参    数:const IArgs & arg                          [in]    点击value
    注    意:无
    返 回 值:bool成功失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/29  1.0     刘德印    创建
    =============================================================================*/
	bool OnClickCurMeetLstItem( const IArgs & arg );
    bool OnClickCurMeetLstItemIcon( const IArgs & arg );

	/*=============================================================================
    函 数 名:OnClickOrderMeetLstItem
    功    能:预约会议列表点击事件
    参    数:const IArgs & arg                          [in]    点击value
    注    意:无
    返 回 值:bool成功失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/29  1.0     刘德印    创建
    =============================================================================*/
	bool OnClickOrderMeetLstItem( const IArgs & arg );
    bool OnClickOrderMeetLstItemIcon( const IArgs & arg );

	
	/*=============================================================================
    函 数 名:UpdateShowList
    功    能:会议列表展现统一接口
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/20  1.0     刘德印    创建
    =============================================================================*/
	void UpdateCurConfShowList();
	void UpdateOrderConfShowList();

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

	void SetConfExist( BOOL bConfExist ){ m_bConfExist = bConfExist;};
	BOOL GetConfExist(){ return m_bConfExist;};

	CString FindConfNameById(u16 wConfId);

private:
	CConfCtrlIF* m_pconfCtrlIF;
	CConfTemplateCtrlIF* m_tTmpConfigIF;

	std::set<u16> m_setCurConfSelectedIconItem;    //当前会议集合
	std::set<u16> m_setOrderConfSelectedIconItem;  //预约会议集合

	BOOL m_bIsAllSel;							   //是否全选
	EM_MENU_MEETTYPE m_emCurPageMeetType;          //当前页面显示类型
	TCMSConfTemplate* m_pTCurCloseMeetTmp;         //当前结会模板

	//搜索集合
	TplArray<TCMSConfTemplate> m_tpOrderConfRefreshList;    //预约会议刷新列表
	TplArray<TCMSConfTemplate> m_tpOrderConflShowList;      //预约会议展现列表
	TplArray<TCMSConfTemplate> m_tpOrderConfSearchList;     //预约会议查询列表

	ARRAY<TCMSConf> m_vecCurConfRefreshList;    //当前会议刷新列表
	ARRAY<TCMSConf> m_vecCurConflShowList;      //当前会议展现列表
	ARRAY<TCMSConf> m_vecCurConfSearchList;     //当前会议查询列表

	BOOL m_bConfExist;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEETINGLIST_H__ABC3C588_3E7D_40D7_987D_87B6C0BB8B54__INCLUDED_)
