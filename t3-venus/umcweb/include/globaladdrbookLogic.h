/*****************************************************************************
模块名      : CGkServerSetLogic
文件名      : gkserversetLogic.h
相关文件    : 
文件实现功能: umcweb 全局地址簿模块
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/5/22      1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_GLOBALADDRBOOK_H__83F27E0D_40FA_4540_9ECD_0B06FC18AEBA__INCLUDED_)
#define AFX_GLOBALADDRBOOK_H__83F27E0D_40FA_4540_9ECD_0B06FC18AEBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// globaladdrbookLogic.h : header file
//
#include "cncaddrbookif.h"
#include "addrbook.h"

/////////////////////////////////////////////////////////////////////////////
// CGlobalAddrbookLogic dialog
class CGlobalAddrbookLogic : public CDlgChild
{
// Construction
public:
	CGlobalAddrbookLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGlobalAddrbookLogic)
	enum { IDD = IDD_DIALOG_GLOBALADDRBOOK };
	CTransparentStatic m_stLeftTitle;
	CTransparentBtn	m_btnAllSel;
	CTransparentBtn	m_btnExport;
	CTransparentBtn	m_btnRefresh;
	CTransparentEdit m_etAddrSearch;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGlobalAddrbookLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGlobalAddrbookLogic)
	afx_msg void OnBtnAllSel();
	afx_msg void OnBtnExport();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBtnRefresh();
	//}}AFX_MSG
	afx_msg LRESULT OnRefreshGlobalAddrbook(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnWaitRefreshOverTime(WPARAM wParam,LPARAM lParam);
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
    2012/05/24  1.0     刘德印    创建
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

	void UpdateShowList();

	/*=============================================================================
    函 数 名:OnClickGlobalLstItem
    功    能:全局地址簿点击事件
    参    数:const IArgs & arg                          [in]    点击value
    注    意:无
    返 回 值:bool成功失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/04/20  1.0     刘德印    创建
    =============================================================================*/
	bool OnClickGlobalLstItem( const IArgs & arg );
    bool OnClickGlobalLstItemIcon( const IArgs & arg );

	//响应搜索框变化事件
	void OnSearchEditChange();

	void UpdateUIState();

private:
	CListChild* m_plsGlobalAddrbook;
	CLetterIndex* m_pLetterIndex;
	
	vector<TAddrItem> m_vctShowList;
	vector<TAddrItem> m_vctSearchList;

	CUmsConfigCtrlIF *m_pUmsConfig;
	CCncAddrbookIF *m_pCncAddrBook;
	TAddrItem  m_tAddrItem;                     //当前被选择全局地址簿条目
	vector<TAddrItem> m_vctGlobalAddrList;      //全局地址簿
	vector<TAddrItem> m_vctSelectList;          //选中列表
	BOOL m_bIsAllSel;

};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLOBALADDRBOOK_H__83F27E0D_40FA_4540_9ECD_0B06FC18AEBA__INCLUDED_)
