/*****************************************************************************
模块名      : CSystemManageLogic
文件名      : systemmanageLogic.h
相关文件    : 
文件实现功能: umcweb系统设置模块
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/5/01      1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_SYSTEMDLG_H__F361BBD4_F48A_4A58_808E_F51215149564__INCLUDED_)
#define AFX_SYSTEMDLG_H__F361BBD4_F48A_4A58_808E_F51215149564__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// systemmanageLogic.h : header file
//
#include "sipserversetLogic.h"
#include "umsnetworksetLogic.h"
#include "umssystimesetLogic.h"
#include "gkserversetLogic.h"
#include "ListChild.h"
#include "nmcfglogic.h"
#include "vtrcfglogic.h"

#define SYSTEM_WND_MENU_UMSWEBCONFIG _T("UMS服务器网络配置")
#define SYSTEM_WND_MENU_SIPCONFIG _T("网呈注册服务器配置")
#define SYSTEM_WND_MENU_SYSTEMTIME _T("系统时间")
#define SYSTEM_WND_MENU_GKCONFIG _T("GK配置")
#define SYSTEM_WND_MENU_NMCFG _T("网管服务器配置")
#define SYSTEM_WND_MENU_VTRCFG _T("录像机配置")

/////////////////////////////////////////////////////////////////////////////
// CSystemManageLogic dialog
class CSystemManageLogic : public CDlgChild
{
// Construction
public:
	CSystemManageLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSystemManageLogic)
	enum { IDD = IDD_DIALOG_SYSTEMSET };
	CTransparentStatic	m_stChildBkRight;
	CTransparentStatic	m_stChildBkLeft;
	CTransparentBtn   	m_btnEdit;
	CTransparentStatic	m_stChildWndTitle;
	CTransparentStatic	m_stTitle;
	CTransparentBtn	    m_btnCancel;
	CTransparentBtn     m_btnSave;
	CTransparentBtn	    m_btnTimeSync;
	//}}AFX_DATA

private:   //控件元素
	CUmsNetworkSetLogic m_networkdlg;
	CSipServerSetLogic m_serversetdlg;
	CUmsSystimeSetLogic m_SystemTime;
	CGkServerSetLogic m_gkset;
	CNMCfgLogic m_cNMCfgLogic;
	CVTRCfgLogic m_cVTRCfgLogic;

	CListChild* m_plsMenu;    


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSystemManageLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSystemManageLogic)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnCancel();   
    
	afx_msg void OnDestroy();
	afx_msg void OnBtnEdit();


    
	afx_msg void OnBtnTimeSync();
	afx_msg LRESULT OnEthnetNotify(WPARAM wParam, LPARAM lParam);  //网络信息通知
	afx_msg LRESULT OnRegSipNotify(WPARAM wParam, LPARAM lParam);  //注册服务器信息通知
	afx_msg LRESULT OnRegSipResult(WPARAM wParam, LPARAM lParam);  //注册服务器结果
	afx_msg LRESULT OnRegGKResult(WPARAM wParam, LPARAM lParam);   //注册GK结果
    afx_msg LRESULT OnRecGKNotify(WPARAM wParam, LPARAM lParam);   //得到UMS发送过来的 GKINFO
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg LRESULT OnRefreshGlobalAddrbook(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnRefreshGlobalAddrbookEx(WPARAM wParam,LPARAM lParam);
	afx_msg HRESULT OnGetUmsSystimeTime( WPARAM wparam, LPARAM lparam );
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
    2012/04/23  1.0               创建
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
    2012/04/26  1.0     刘德印    创建
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
    2012/04/24  1.0     刘德印    创建
    =============================================================================*/
	virtual BOOL InitControlPane();


	/*=============================================================================
    函 数 名:InitChildWindow
    功    能:初始化子窗口视图
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/24  1.0     刘德印    创建
    =============================================================================*/
	virtual BOOL InitChildWindow();

	/*=============================================================================
    函 数 名:SetControlPos
    功    能:设置所有控件元素位置  提供给自适应分辨率
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/26  1.0     刘德印    创建
    =============================================================================*/
	void SetControlPos();

	/*=============================================================================
    函 数 名:ShowActiveWindow
    功    能:显示当前配置窗口
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/18  1.0     刘德印    创建
    =============================================================================*/
	void ShowActiveWindow(EM_CURRENT_WND_VIEW_TYPE emWndType);

	/*=============================================================================
    函 数 名:SetControlStatusOff
    功    能:收到通知关闭配置页面控件
    参    数:BOOL bIsOn: TRUE开启    FALSE:关闭
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/17  1.0     刘德印    创建
    =============================================================================*/
	void SetGKControl(BOOL bIsOn);

	/*=============================================================================
    函 数 名:OnClickLstItem
    功    能:系统菜单列表点击事件
    参    数:const IArgs & arg                          [in]    点击value
    注    意:无
    返 回 值:bool成功失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/18  1.0     刘德印    创建
    =============================================================================*/
	bool OnClickLstItem( const IArgs & arg );

	/*=============================================================================
    函 数 名:SaveSysTime
    功    能:保存UMS网络配置
    参    数:无
    注    意:无
    返 回 值:bool
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/16  1.0     刘德印    创建
    =============================================================================*/
	BOOL SaveEthnetCfg();

	/*=============================================================================
    函 数 名:SaveRegServer
    功    能:保存SIP服务器地址
    参    数:无
    注    意:无
    返 回 值:BOOL
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/28  1.0     刘德印    创建
    =============================================================================*/
	BOOL SaveRegServer();

	/*=============================================================================
    函 数 名:保存GK服务器地址
    功    能:保存系统时间
    参    数:无
    注    意:无
    返 回 值:BOOL
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/15  1.0     刘德印    创建
    =============================================================================*/
	BOOL SaveGkInfo();

	/*=============================================================================
    函 数 名:UpdateNetworkConfig
    功    能:更新网络配置信息
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/26  1.0     刘德印    创建
    =============================================================================*/
	void RevertNetConfig();
    
    void SetEditControl( bool bIsEnable );

    void SetNetCfgControl( bool bIsEnable );

    void SetControlToDefault();

private:
	CUmsConfigCtrlIF *m_pUmsConfig; //umslib配置接口
	CWnd* m_currentCwd;         //当前点击视图
	BOOL m_bGkSwitchStatus;
    DWORD m_dwIpGKServer;
	DWORD m_dwIpRegServer;
    s32 m_emCurrViewType;            //save clicked emun item 

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEMDLG_H__F361BBD4_F48A_4A58_808E_F51215149564__INCLUDED_)
