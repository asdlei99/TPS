/*****************************************************************************
模块名      : CMainLogic
文件名      : mainLogic.h
相关文件    : 
文件实现功能: umcweb 主窗口模块
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/4/08      1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_MAIN_H__9A90447E_28A0_43EC_BAAC_C8D3E9232777__INCLUDED_)
#define AFX_MAIN_H__9A90447E_28A0_43EC_BAAC_C8D3E9232777__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//mainLogic.h : header file
//
#include "systemmanageLogic.h"
#include "localaddrbookLogic.h"
#include "meetinfoLogic.h"
#include "meetTemplateLogic.h"
#include "usermanageLogic.h"
#include "globaladdrbookLogic.h"
#include "tvwmanageLogic.h"
#include "vtrlogic.h"
#include "addreditlogic.h"

class CMainLogic : public CDlgChild
{
// Construction
public:
	CMainLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMainLogic)
	enum { IDD = IDD_DIALOG_MAIN };
	CTransparentCheckButton	m_btnAddrEdit;
	CTransparentCheckButton	m_btnVTRSet;
	CTransparentCheckButton	m_btnWarning;
	CTransparentStatic	m_stTitle;
	CTransparentStatic	m_stToolbarBK;
	CTransparentCheckButton	m_btnLogo; 
	CTransparentCheckButton m_btnMeetTmp; 
	CTransparentCheckButton	m_btnMeetInfo;
	CTransparentCheckButton	m_btnUser;
	CTransparentCheckButton	m_btnTvw;
	CTransparentCheckButton	m_btnPublicAddr; 
	CTransparentCheckButton m_btnLocalAddr;
	CTransparentCheckButton	m_btnSysSet;
	CTransparentBtn	m_btnLogOff;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMainLogic)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnLogoff();
	afx_msg void OnBtnSystemSet();
	afx_msg void OnBtnLocalAddr();
	afx_msg void OnBtnLogo();
	afx_msg void OnBtnMeetInfo();
	afx_msg void OnBtnMeetTmp();
	afx_msg void OnBtnPublicAddr();
	afx_msg void OnBtnTvw();
	afx_msg void OnBtnUser();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonWarning();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnWarningIconNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnLoginResult(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBtnVTRSet();
	afx_msg void OnBtnADDREDIT();
	//}}AFX_MSG
	afx_msg LRESULT OnUmsDisconn(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGrab(WPARAM wParam, LPARAM lParam);
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
	BOOL InitChildWindow();

	/*=============================================================================
    函 数 名:ShowActiveWindow
    功    能:显示当前功能窗口
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/18  1.0     刘德印    创建
    =============================================================================*/
	void ShowActiveWindow(EM_CURRENT_WND_VIEW_TYPE emWndType);

	void RevertTabPage();

public:
	//CLocalAddrbookLogic m_dlgLocalAddr;	
	//CGlobalAddrbookLogic m_dlgGlobalAddrbook;
	CMeetTemplateLogic m_dlgMeetTmp;
	CMeetinfoLogic m_dlgMeetInfo;	
	CSystemManageLogic m_dlgSysSet;
	CUserManageLogic m_dlgUser;
	CTvwManageLogic m_dlgTvw;
	CVTRLogic m_dlgVTR;
	CAddrEditLogic m_dlgAddrEdit;

private:
	CWnd* m_cwndCurrent; 
	EM_CURRENT_WND_VIEW_TYPE m_emWndType;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAIN_H__9A90447E_28A0_43EC_BAAC_C8D3E9232777__INCLUDED_)
