/*****************************************************************************
模块名      : CGkServerSetLogic
文件名      : gkserversetLogic.h
相关文件    : 
文件实现功能: umcweb GK服务器设置模块
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/5/04      1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_DLGGKSET_H__26BDFD46_062C_4AF8_9F8F_372D2AE1264B__INCLUDED_)
#define AFX_DLGGKSET_H__26BDFD46_062C_4AF8_9F8F_372D2AE1264B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//gkserversetLogic.h : header file
//
enum EM_GK_SERVER_BUTTONSTATUS{GK_ON = 0,GK_OFF};

class CGkServerSetLogic : public CDlgChild
{
// Construction
public:
	CGkServerSetLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGkServerSetLogic)
	enum { IDD = IDD_DIALOG_GKSERVERSET };
	CTransparentStatic	m_stGkOnAndOff;
	CTransparentStatic	m_stIpAddr;
	CTransparentIpEdit	m_Ip;
	CTransparentSwitchButton m_btnSwitch;
	//}}AFX_DATA

	EM_GK_SERVER_BUTTONSTATUS m_emGkSerBtnStatus;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGkServerSetLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGkServerSetLogic)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnClickSwitchBtn(WPARAM wParam, LPARAM lParam);
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
    2012/04/24  1.0               创建
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
    2012/04/28  1.0     刘德印    创建
    =============================================================================*/
	virtual BOOL InitControlPane();

	BOOL GetGKSwitchStatus(){return m_btnSwitch.GetSwitchState();};

	void SetSwitch();

	BOOL m_bSwitchStatus;
    
    bool m_bIsEdit;  //clicked edit
    
private:

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGKSET_H__26BDFD46_062C_4AF8_9F8F_372D2AE1264B__INCLUDED_)
