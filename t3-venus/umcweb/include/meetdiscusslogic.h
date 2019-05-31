/*****************************************************************************
模块名      : CMeetDiscussLogic
文件名      : meetdiscusslogic.h
相关文件    : 
文件实现功能: umcweb 会议讨论页面
作者        : 徐华秀
版本        : V1.0
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2014/2/13      1.0         徐华秀      创建
******************************************************************************/
#if !defined(AFX_MEETDISCUSSLOGIC_H__7AB7BD0A_0FBF_4ED9_9FA9_4B32C12093F8__INCLUDED_)
#define AFX_MEETDISCUSSLOGIC_H__7AB7BD0A_0FBF_4ED9_9FA9_4B32C12093F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// meetdiscusslogic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMeetDiscussLogic dialog
class CMeetDiscussLogic : public CDlgChild
{
// Construction
public:
	CMeetDiscussLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMeetDiscussLogic)
	enum { IDD = IDD_DIALOG_MEETDISCUSS };
	CTransparentStatic	m_stDiscuss;
	CTransparentStatic	m_stGroup1;
	CTransparentStatic	m_stGroup2;
	CTransparentStatic	m_stGroup3;
	CTransparentStatic	m_stGroup4;
	CTransparentStatic	m_stGroupShow1;
	CTransparentStatic	m_stGroupShow2;
	CTransparentStatic	m_stGroupShow3;
	CTransparentStatic	m_stGroupShow4;
	CTransparentEdit	m_etGroup1;
	CTransparentEdit	m_etGroup2;
	CTransparentEdit	m_etGroup3;
	CTransparentEdit	m_etGroup4;
	CTransparentSwitchButton m_btnSwitchDiscuss;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeetDiscussLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMeetDiscussLogic)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnClickSwitchBtn(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClickEditDel(WPARAM wParam, LPARAM lParam);
	afx_msg	LRESULT OnDragEnd(WPARAM wParam, LPARAM lParam);
//	afx_msg	LRESULT OnDragOver(WPARAM wParam, LPARAM lParam);
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
    2014/02/14  1.0               创建
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
    2014/02/13  1.0               创建
    =============================================================================*/
	void RegisterFun();

	/*=============================================================================
    函 数 名:InitControlPane
    功    能:初始化页面控件
    参    数:无
    注    意:无
    返 回 值:BOOL
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2014/02/13  1.0               创建
    =============================================================================*/
	virtual BOOL InitControlPane();

	/*=============================================================================
    函 数 名:HideAllPageCtrl
    功    能:隐藏所有控件
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2014/02/14  1.0               创建
    =============================================================================*/
	void HideAllPageCtrl();

	/*=============================================================================
    函 数 名:UpdateUIState
    功    能:状态控制
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2014/02/14  1.0               创建
    =============================================================================*/
	void UpdateUIState();

	//--- 页面环境 end -------------------------------------------------------------

	//--- 类公共函数 begin --------------------------------------------------------

	BOOL AddToEpEdit( const CString& strEpName );
	BOOL DelFromEpEdit( const CString& strEpName ); 
	void UpdateDiscussEdit( std::map<u16,CString>& mapDiscussSelItem, BOOL bSwitchDiscuss, EM_OPERATE_FLAG emOperateFlag );

	//--- 类公共函数 end ----------------------------------------------------------

private:
	BOOL				m_bSwitchDiscuss;
	EM_OPERATE_FLAG		m_emOperateFlag;
	std::map<u16,CString> m_mapDiscussSelItem;       //存储会议讨论界面勾选的会场

	CRect m_rectGroup1;
	CRect m_rectGroup2;
	CRect m_rectGroup3;
	CRect m_rectGroup4;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEETDISCUSSLOGIC_H__7AB7BD0A_0FBF_4ED9_9FA9_4B32C12093F8__INCLUDED_)
