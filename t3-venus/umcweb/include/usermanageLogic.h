/*****************************************************************************
模块名      : CUserManageLogic
文件名      : usermanageLogic.h
相关文件    : 
文件实现功能: umcweb用户管理模块
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/4/16      1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_USER_H__1D927FCF_0EC8_445B_9D54_CFEA8B91D70F__INCLUDED_)
#define AFX_USER_H__1D927FCF_0EC8_445B_9D54_CFEA8B91D70F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// usermanageLogic.h : header file
//
class CUserManageLogic : public CDlgChild
{
// Construction
public:
	CUserManageLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUserManageLogic)
	enum { IDD = IDD_DIALOG_USERMANAGE };
	CTransparentStatic	m_stChildBkRight;
	CTransparentStatic	m_stChildBkLeft;
	CTransparentStatic	m_stUserLeftTitle;
	CTransparentStatic	m_stUserRightTitle;
	CTransparentStatic	m_stUserName;
	CTransparentStatic	m_stPassword;
	CTransparentEdit	m_etUserName;
	CTransparentEdit	m_etPassword;
	CTransparentBtn	    m_btnSave;
	CTransparentBtn	    m_btnCancel;
	CTransparentBtn	    m_btnEdit;
	CTransparentEdit    m_etSearch;
	CTransparentBtn	    m_btnNewUser;
	CTransparentBtn	    m_btnDelete;
	CTransparentBtn	    m_btnAllSel;
	//}}AFX_DATA


private:
	CListChild* m_plsUser;
	CLetterIndex* m_pLetterIndex;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserManageLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserManageLogic)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnCancel();
	afx_msg void OnBtnDelete();
	afx_msg void OnBtnAllSelect();
	afx_msg void OnBtnNewUser();
	afx_msg void OnBtnEdit();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnRefreshUserList(WPARAM wParam, LPARAM lParam);          //刷新用户列表通知
	afx_msg LRESULT OnUserOperateResultNotify(WPARAM wParam, LPARAM lParam);  //用户操作结果反馈
	afx_msg LRESULT OnNoSelResultNotify(WPARAM wParam, LPARAM lParam);        //未选择任何用户列表通知
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
    函 数 名:ResetInitPage
    功    能:重置界面控件
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/20  1.0     刘德印    创建
    =============================================================================*/
	void ResetInitPage();

	/*=============================================================================
    函 数 名:ShowControlNewPage
    功    能:新建页面控件显示
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/20  1.0     刘德印    创建
    =============================================================================*/
	void ShowControlNewPage();

	/*=============================================================================
    函 数 名:ShowControlScanfPage
    功    能:浏览页面控件显示
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/20  1.0     刘德印    创建
    =============================================================================*/
	void ShowControlScanfPage();

	/*=============================================================================
    函 数 名:ShowControlEditPage
    功    能:编辑页面控件显示
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/20  1.0     刘德印    创建
    =============================================================================*/
	void ShowControlEditPage();

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
    函 数 名:UserListRefresh
    功    能:用户列表刷新
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/20  1.0     刘德印    创建
    =============================================================================*/
	void UserListRefresh();

	/*=============================================================================
    函 数 名:OnClickLstItem
    功    能:用户列表点击事件
    参    数:const IArgs & arg                          [in]    点击value
    注    意:无
    返 回 值:bool成功失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/20  1.0     刘德印    创建
    =============================================================================*/
	bool OnClickLstItem( const IArgs & arg );
    bool OnClickLstItemIcon( const IArgs & arg );

	/*=============================================================================
    函 数 名:UpdateShowList
    功    能:用户列表展现统一接口
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/20  1.0     刘德印    创建
    =============================================================================*/
	void UpdateShowList();

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

	/*=============================================================================
    函 数 名:JumpToSelLine
    功    能:新建 编辑等操作当前选中行的定位
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/06/30  1.0     刘德印    创建
    =============================================================================*/
	void JumpToSelLine();

	/*=============================================================================
    函 数 名:OnSearchEditChange
    功    能:查询控件对列表的过滤事件
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/07/02  1.0     刘德印    创建
    =============================================================================*/
	void OnSearchEditChange();

private:
	//---umslib控制接口 
	CUserCtrlIF * m_pUserctrlIF;

	//---操作控制
	EM_USERWND_CUROPERATE_STATE m_emCurOperateFlag;
	BOOL m_bIsAllSel;
	BOOL m_bJumpFlag;							//新建用户跳转到选中标志
	std::set<CString> m_setSelectedIconItem;	//当前被选中列表Item集合
	CUserFullInfo m_selUser;					//当前选中用户

	//搜索集合
	TplArray<CUserFullInfo> m_tpRefreshList;    //用户刷新列表
	TplArray<CUserFullInfo> m_tplShowList;      //用户展现列表
	TplArray<CUserFullInfo> m_tpSearchList;     //用户查询列表
	vector<CUserFullInfo>   m_vecShowList;      //用户展现列表供排序
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USER_H__1D927FCF_0EC8_445B_9D54_CFEA8B91D70F__INCLUDED_)
