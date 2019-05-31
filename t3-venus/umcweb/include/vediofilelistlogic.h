/*****************************************************************************
模块名      : CVedioFileListLogic
文件名      : vediofilelistlogic.h
相关文件    : 
文件实现功能: umcweb 录像机配置模块
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/4/8       1.0         石城        创建
******************************************************************************/
#if !defined(AFX_VEDIOFILELISTLOGIC_H__76934FF8_7E41_4A5A_98C8_DCC399B29A64__INCLUDED_)
#define AFX_VEDIOFILELISTLOGIC_H__76934FF8_7E41_4A5A_98C8_DCC399B29A64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// vediofilelistlogic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVedioFileListLogic dialog

class CVedioFileListLogic : public CDlgChild
{
// Construction
public:
	CVedioFileListLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVedioFileListLogic)
	enum { IDD = IDD_DIALOG_VIDEOFILELIST };
	CTransparentBtn	m_btnDelSingle;
	CStatic	m_stcEqpIDReal;
	CTransparentBtn	m_btnCheckAll;
	CTransparentBtn	m_btnUnCheckAll;
	CTransparentStatic	m_stcFileName;
	CTransparentEdit	m_sedtSearch;
	CTransparentEdit	m_edtFileName;
	CTransparentBtn	m_btnSave;
	CTransparentBtn	m_btnBack;
	CTransparentBtn	m_btnEdit;
	CTransparentBtn	m_btnDel;
	CTransparentBtn	m_btnCancel;
	CTransparentStatic	m_stcChildWndTitle;
	CTransparentStatic	m_stcTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVedioFileListLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CVedioFileListLogic)
	afx_msg void OnDestroy();
	afx_msg void OnButtonVtrFileback();
	afx_msg LRESULT OnRecFileListInfoNty( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecMdyFileRsp( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecDelFileRsp( WPARAM wparam, LPARAM lparam );
	afx_msg void OnButtonVtrEdit();
	afx_msg void OnButtonVtrSave();
	afx_msg void OnButtonVtrCancel();
	afx_msg void OnButtonDelSingle();
	afx_msg void OnButtonVtrDel();
	afx_msg void OnButtonVtrCheckAll();
	afx_msg void OnButtonVtrUnCheckAll();
	afx_msg LRESULT OnUpdateEditVtrSearch( WPARAM wparam, LPARAM lparam );
	LRESULT OnNoSelResultNotify(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
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

protected:
	bool OnClickLstItem( const IArgs & arg );
	bool OnClickLstItemIcon( const IArgs & arg );
	bool OnClickDelLstItem( const IArgs & arg );
	bool OnClickDelLstItemIcon( const IArgs & arg );

private:
	void RefreshRecFileList();
	void SetFileInfo( TRecFileInfo tRecFileInfo );
	void GetFileInfo( TRecFileInfo &tRecFileInfo );
	void ShowFileInfoPage( BOOL bShow );
	void RefreshDelList();
	void ShowDelPage( BOOL bShow );
	BOOL SetDeleteFile( TRecFileInfo tRecFileInfo );
	void RefreshAllList();
	void LoadScheme( int emScheme );
	int CheckFileName( CString strFileName );

private:
	CListChild* m_pListVedioFile;
	CListChild* m_pListDel;
	
	CLetterIndex* m_pLetterIndex;

	//---umslib控制接口 
	CUmsVTRCtrlIF *m_pVTRCtrlIF;

	vector<TRecFileInfo> m_vecTRecFileInfoSearch;

	TRecFileInfo m_tRecFileInfoSel;
	vector<TRecFileInfo> m_vecTRecFileInfoSel;

	BOOL m_bEdit;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VEDIOFILELISTLOGIC_H__76934FF8_7E41_4A5A_98C8_DCC399B29A64__INCLUDED_)
