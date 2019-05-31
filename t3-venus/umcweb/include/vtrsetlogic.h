/*****************************************************************************
模块名      : CVTRCfgLogic
文件名      : vtrcfglogic.h
相关文件    : 
文件实现功能: umcweb 录像机配置模块
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/4/8       1.0         石城        创建
******************************************************************************/
#if !defined(AFX_VTRSETLOGIC_H__3D7BC606_AD76_44DE_86E2_ACB0F5266B8E__INCLUDED_)
#define AFX_VTRSETLOGIC_H__3D7BC606_AD76_44DE_86E2_ACB0F5266B8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "vediofilelistlogic.h"

// vtrsetlogic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVTRSetLogic dialog

class CVTRSetLogic : public CDlgChild
{
// Construction
public:
	CVTRSetLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVTRSetLogic)
	enum { IDD = IDD_DIALOG_VTRSET };
	CTransparentStatic	m_stcVtrNameReal;
	CTransparentStatic	m_stcDiskSpaceTotalReal;
	CTransparentStatic	m_stcDiskSpaceAvailableReal;
	CTransparentStatic	m_stcTitle;
	CTransparentStatic	m_stcVTRName;
	CTransparentStatic	m_stcDiskSpaceTotal;
	CTransparentStatic	m_stcDiskSpaceAvailable;
	CTransparentStatic	m_stcChildWndTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVTRSetLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CVTRSetLogic)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnRecBaseInfoNty( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnVtrNty( WPARAM wparam, LPARAM lparam );
	afx_msg void OnShowWindow( BOOL bShow, UINT nStatus );
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

protected:
	/*=============================================================================
    函 数 名:OnClickLstItem
    功    能:系统菜单列表点击事件
    参    数:const IArgs & arg                          [in]    点击value
    注    意:无
    返 回 值:bool成功失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2013/04/08  1.0     石城      创建
    =============================================================================*/
	bool OnClickLstItem( const IArgs & arg );

private:
	//基本信息中的名称无效、用ev_Vcr_nty中的名称
	void SetRecBaseInfo( vector<TRecBaseInfo> &vecTRecBaseInfo );

private:
	CListChild* m_pListMenu;

	//---umslib控制接口 
	CUmsVTRCtrlIF *m_pVTRCtrlIF;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VTRSETLOGIC_H__3D7BC606_AD76_44DE_86E2_ACB0F5266B8E__INCLUDED_)
