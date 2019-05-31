/*****************************************************************************
模块名      : CTvwManageLogic
文件名      : tvwmanageLogic.h
相关文件    : 
文件实现功能: umcweb用户管理模块
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/4/16      1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_TVW_H__1D927FCF_0EC8_445B_9D54_CFEA8B91D70F__INCLUDED_)
#define AFX_TVW_H__1D927FCF_0EC8_445B_9D54_CFEA8B91D70F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// usermanageLogic.h : header file
//
class CTvwManageLogic : public CDlgChild
{
// Construction
public:
	CTvwManageLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTvwManageLogic)
	enum { IDD = IDD_DIALOG_USERMANAGE };
	CTransparentStatic	m_stChildBkRight;
	CTransparentStatic	m_stChildBkLeft;
	CTransparentStatic	m_stUserLeftTitle;
	CTransparentStatic	m_stUserRightTitle;
	CTransparentBtn	    m_btnManage;
    CTransparentBtn	    m_btnBack;
    CTransparentBtn	    m_btnRemoveAll;
    CTransparentBtn	    m_btnDone;
	CTransparentEdit    m_etSearch;
	//}}AFX_DATA


private:
	CListChild* m_plsTvw;
	CLetterIndex* m_pLetterIndex;

    CViewList* m_pTvwView;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTvwManageLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTvwManageLogic)
	virtual BOOL OnInitDialog();	
	afx_msg void OnDestroy();
    afx_msg void OnBtnManage();
    afx_msg void OnBtnDone();
    afx_msg void OnBtnRemoveAll();
    afx_msg void OnBtnBack();
    afx_msg LRESULT OnRefreshConfList( WPARAM wparam, LPARAM lparam );
    afx_msg LRESULT OnRefreshConfCnsList( WPARAM wparam, LPARAM lparam );
	//afx_msg LRESULT OnUpdateConfList( WPARAM wparam, LPARAM lparam );
    afx_msg LRESULT OnHduPlanNty( WPARAM wparam, LPARAM lparam );
    afx_msg	LRESULT OnSearchEditChange(WPARAM wParam, LPARAM lParam);
    afx_msg	LRESULT OnUnSelItemNotify(WPARAM wParam, LPARAM lParam);
    afx_msg	LRESULT OnPlayHduRsp(WPARAM wParam, LPARAM lParam);
    afx_msg	LRESULT OnDragOver(WPARAM wParam, LPARAM lParam);
    afx_msg	LRESULT OnDragLeave(WPARAM wParam, LPARAM lParam);
    afx_msg	LRESULT OnDragEnd(WPARAM wParam, LPARAM lParam);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	/*=============================================================================
    函 数 名:InitDlg
    功    能:页面注销抢断后初始化
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
    2012/04/20  1.0               创建
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
    2012/04/20  1.0               创建
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
    2012/04/20  1.0               创建
    =============================================================================*/
	void SetControlPos();

    
    bool OnClickConfListItem( const IArgs & arg );

    bool OnClickCnsListIcon( const IArgs & arg );

    bool OnClickTvwItem( const IArgs & arg );

    bool OnClickTvwItemIcon( const IArgs & arg );

protected:
    /**
    * 功能:	更新会议列表标题
	* @return  无
	* @remarks
	*/
    void UpdateConfTitle();
    /**
    * 功能:	更新会场列表
	* @return  无
	* @remarks
	*/
    void UpdateConfCnsList();

    /**
    * 功能:	将会场加入电视墙中
    * @param [in] wIndex:电视墙索引
    * @param [in] tCnsInfo:会场信息
    * @param [in] bSel: 是否只是设为选中
	* @remarks
    * @author  肖楚然 
    * @date  2013/01/24
	*/
    void SetCnsInTvw( u16 wIndex, TCnsInfo tCnsInfo, BOOL bSel = FALSE );

private:
    CConfCtrlIF* m_pconfCtrlIF;
    CTvwCtrlIF*  m_pTvwCtrlIF;

    //vector<TCmsTvwInfo> m_vctTvwList; 
    vector<TTvwCns> m_vctTvwCnsList;     //电视墙列表
    vector<TCMSConf> m_vctCurConfList;   //当前会议列表

    THduPlanData  m_tHduPlanData;        //所有电视墙数据
    TCMSConf      m_tSelConf;            //当前选中会议
    BOOL          m_bManage;
    BOOL          m_bInCnsList;          //是否在会场列表中
    u16           m_wSelTvwIndex;        //选中电视墙索引
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TVW_H__1D927FCF_0EC8_445B_9D54_CFEA8B91D70F__INCLUDED_)
