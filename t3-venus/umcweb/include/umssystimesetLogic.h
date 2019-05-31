/*****************************************************************************
模块名      : CUmsSystimeSetLogic
文件名      : umssystimesetLogic.h
相关文件    : 
文件实现功能: umcweb系统时间设置模块
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/4.17      1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_SYSTEMTIME_H__5E96BED9_FFF7_4134_B057_504950783EE2__INCLUDED_)
#define AFX_SYSTEMTIME_H__5E96BED9_FFF7_4134_B057_504950783EE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// umssystimesetLogic.h : header file
//
#include "CalendarDlg.h"

class CUmsSystimeSetLogic : public CDlgChild
{
// Construction
public:
	CUmsSystimeSetLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUmsSystimeSetLogic)
	enum { IDD = IDD_DIALOG_SYSTIMESET };
	CTransparentStatic	m_stDate;
	CTransparentStatic	m_stStartTime;
	CTransparentEdit	m_etSetHour;
	CTransparentEdit	m_etSetMin;
	CTransparentEdit	m_etSetSec;
	CTransparentEdit    m_edtDotHour;
    CTransparentEdit    m_edtDotMin;
	CTransparentCheckButton		m_btnCalendar;
	CTransparentBtn	    m_btnPlus;
	CTransparentBtn	    m_btnMinus;
	CTransparentEdit	m_etDateSet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUmsSystimeSetLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUmsSystimeSetLogic)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnCalendar();
	afx_msg void OnBtnPlus();
	afx_msg void OnBtnMinus();
	afx_msg HRESULT OnHideAUtoHideWnd( WPARAM wparam, LPARAM lparam );
	afx_msg HRESULT OnGetUmsSystimeTime( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnUpdateCalendarSelDate(WPARAM wParam, LPARAM lParam);        //日历选择时间
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSetfocusEditHour();
	afx_msg void OnSetfocusEditMinute();
	afx_msg void OnUpdateEditMinute();
	afx_msg void OnUpdateEditSec();
	afx_msg void OnSetfocusEditSec();
	afx_msg void OnUpdateEditHour();
    afx_msg	LRESULT OnTimeEditChange(WPARAM wParam, LPARAM lParam);
    afx_msg	LRESULT OnBtnHold(WPARAM wParam, LPARAM lParam);  
    afx_msg	LRESULT OnBtnHoldEnd(WPARAM wParam, LPARAM lParam);       
	afx_msg void OnDestroy();
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
    2012/04/28  1.0     刘德印    创建
    =============================================================================*/
	virtual BOOL InitControlPane();

	/*=============================================================================
    函 数 名:SaveSysTime
    功    能:保存系统时间
    参    数:BOOL32 bSave = TRUE                          [in]  TRUE:保存系统时间到UMS服务器  FALSE:显示本地时间
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/26  1.0     刘德印    创建
    =============================================================================*/
	BOOL SaveSysTime();

	/*=============================================================================
    函 数 名:UpdateSysTimeToControl
    功    能:更新系统时间控件
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/28  1.0     刘德印    创建
    =============================================================================*/
	void UpdateSysTimeToControl(struct tm& tmDate);

	void SyncTimeToServer();
	void SetTimeControl(BOOL bIsOn);

	CCalendarDlg m_dlgCalendar;
    
    UINT m_nTimer;   //save timer ID
    bool m_bIsEdit;  //clicked edit

private:
	CUmsConfigCtrlIF *m_pUmsConfig;
	time_t m_timeDate;

    int     m_nExHour;
    int     m_nExMin;
    int     m_nExSec;
    EM_CURRENT_FOCUS     m_emCurFocus;
    bool    m_bEnterCalendar; //whether clicked calendar Dlg.
	BOOL m_bEditingDate;
    
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEMTIME_H__5E96BED9_FFF7_4134_B057_504950783EE2__INCLUDED_)
