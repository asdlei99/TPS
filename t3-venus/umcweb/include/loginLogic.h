/*****************************************************************************
模块名      : CLoginLogic
文件名      : loginLogic.h
相关文件    : 
文件实现功能: umcweb 登陆模块
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/4/05      1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_LoginLogic_H__A3B9FD53_F9D8_4450_A937_FC34C0484A0B__INCLUDED_)
#define AFX_LoginLogic_H__A3B9FD53_F9D8_4450_A937_FC34C0484A0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginLogic.h : header file
//
class CLoginLogic : public CDlgChild
{
// Construction
public:
	CLoginLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLoginLogic)
	enum { IDD = IDD_DIALOG_LOGIN };
	CTransparentBtn	m_btnOnOrOff;
	CTransparentStatic	m_stRecordPassword;
	CTransparentStatic	m_stTitle;
	CTransparentStatic	m_stLogo;
	CTransparentStatic	m_stBkChild;
	CTransparentBtn m_btnLogin;
	CTransparentIpEdit	m_etIP;
	CTransparentEdit	m_etUserName;
	CTransparentEdit	m_etUserPSWD;
	CTransparentStatic	m_stCompay;
	CTransparentStatic	m_stVersion;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginLogic)
 
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
 
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool LoginCheck();

	// Generated message map functions
	//{{AFX_MSG(CLoginLogic)
	virtual BOOL OnInitDialog();
	afx_msg void OnLogin();
	afx_msg void OnButtonOnorOff();
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg LRESULT OnLoginResult(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	/*=============================================================================
    函 数 名:RegisterFun
    功    能:注册函数
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/06/29  1.0     刘德印    创建
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
    2012/04/05  1.0     刘德印    创建
    =============================================================================*/
	virtual BOOL InitControlPane();

	/*=============================================================================
    函 数 名:ShowWarningWnd
    功    能:是否显示提醒窗口
    参    数:UINT nShowFlag                          [in]    TRUE:显示   FALSE:隐藏
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/05  1.0     刘德印    创建
    =============================================================================*/
	void ShowWarningWnd(UINT nShowFlag);

	/*
	* 设置登陆界面IP
	*/
    void SetIP( DWORD dwIP ){ m_dwIP = dwIP; }

    /*
	* work around for outside function calling OnLogin()
	*/
    BOOL Login();

	void ReadConfig();

private:
	CString m_strRememberStatus;
	BOOL m_bIsBtnOnStatus; 
	u32  m_dwIP;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LoginLogic_H__A3B9FD53_F9D8_4450_A937_FC34C0484A0B__INCLUDED_)
