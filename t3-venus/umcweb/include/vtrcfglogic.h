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
2013/4/7       1.0         石城        创建
******************************************************************************/
#if !defined(AFX_VTRCFGLOGIC_H__3186973F_53DF_46A1_9AA2_7A4C0B9BC6F8__INCLUDED_)
#define AFX_VTRCFGLOGIC_H__3186973F_53DF_46A1_9AA2_7A4C0B9BC6F8__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// vtrcfglogic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVTRCFGLOGIC dialog

class CVTRCfgLogic : public CDlgChild
{
// Construction
public:
	CVTRCfgLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVTRCfgLogic)
	enum { IDD = IDD_DIALOG_VTRCFG };
	CTransparentIpEdit	m_ipVTRIP;
	CTransparentEdit	m_edtVTRNo;
	CTransparentEdit	m_edtVTRName;
	CTransparentStatic	m_stcVTRIP;
	CTransparentStatic	m_stcVTRNo;
	CTransparentStatic	m_stcVTRName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVTRCfgLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual BOOL OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(CVTRCfgLogic)
	afx_msg LRESULT OnVtrNty(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAddVtrRsp(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDelVtrRsp(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMdyVtrRsp(WPARAM wParam, LPARAM lParam);
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
    2013/4/7    1.0     石城      创建
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

public:
	void SetEditState( BOOL bEdit );
	BOOL SaveVTRCfg();
	void FreshNMInfo();

private:
	void SetVTRCfg();
	bool GetVTRCfg( TVcrCfg& tVTRCfg, TVcrCfg& tVTRCfgOld );
	void UpdateTip( EmModifyVcrRet emRet );

public:
    bool m_bIsEdit;  //clicked edit

	//---umslib控制接口 
	CUmsVTRCtrlIF *m_pVTRCtrlIF;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VTRCFGLOGIC_H__3186973F_53DF_46A1_9AA2_7A4C0B9BC6F8__INCLUDED_)
