/*****************************************************************************
模块名      : CMessageDlg
文件名      : MessageDlg.h
相关文件    : 
文件实现功能: umcweb MessageBox类型弹出框
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/4/27      1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_MESSAGEDLG_H__D8151CFF_B2D6_4AB9_B97B_51000AADA848__INCLUDED_)
#define AFX_MESSAGEDLG_H__D8151CFF_B2D6_4AB9_B97B_51000AADA848__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MessageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMessageDlg dialog

#include "transparentbasedlg.h"

class CMessageDlg : public CTransparentBaseDlg
{
// Construction
public:
	CMessageDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMessageDlg)
	enum { IDD = IDD_DIALOG_MESSAGEBOX };
	CTransparentStatic	m_stTitle;
	CTransparentStatic	m_stMsgContent;
	CTransparentBtn	m_btnCancel;
	CTransparentBtn	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMessageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnOk();
	afx_msg void OnBtnCancel();
	afx_msg void OnDestroy();
 
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	static BOOL IsMsgBoxVisible( BOOL bEndDlg ); 
	void MessageBoxWnd( const CString& strText, BOOL bShowBtnCancel = TRUE );
private:
	CString m_strWndTxt;
	//static CMessageDlg *m_pDlg;
 
	static BOOL m_bShowBtnCancel;

};

//MessageBox弹出框
#define MESSAGEWNDBOX( p, pthis, ret ,bShow ){  \
	ISMSGBOXVISIBLE(TRUE); \
	CMessageDlg dlgMessage(pthis) ;\
	dlgMessage.MessageBoxWnd(p,bShow); \
	s32 nRetValue = dlgMessage.DoModal(); \
	_RPT1( 0, "\n返回值ID = %d\n", nRetValue );\
	 ret = nRetValue; }


#define ISMSGBOXVISIBLE( bEndDlg )   CMessageDlg::IsMsgBoxVisible( bEndDlg ) ;
 

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGEDLG_H__D8151CFF_B2D6_4AB9_B97B_51000AADA848__INCLUDED_)
