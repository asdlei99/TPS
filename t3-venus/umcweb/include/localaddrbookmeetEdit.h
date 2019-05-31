/*****************************************************************************
模块名      : CLocalAddrbookMeetEdit
文件名      : localaddrbookmeetEdit.h
相关文件    : 
文件实现功能: umcweb 本地地址簿会场编辑页面
作者        : 
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/5/17      1.0                     创建
******************************************************************************/
#if !defined(AFX_LOCALADDRMEETINGEDIT_H__BF8705B1_69D8_40B9_8A40_8EFA47276F08__INCLUDED_)
#define AFX_LOCALADDRMEETINGEDIT_H__BF8705B1_69D8_40B9_8A40_8EFA47276F08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LocalAddrMeetingEdit.h : header file
//
#include "localaddrbookgroupEdit.h"
class CLocalAddrbookMeetEdit : public CTransparentBaseDlg
{
// Construction
public:
	CLocalAddrbookMeetEdit( CWnd* pParent = NULL );   // standard constructor
	CLocalAddrbookMeetEdit( CCncAddrbookIF* pAdBk, CWnd* pParent = NULL );
	CLocalAddrbookMeetEdit( CCncAddrbookIF* pAdBk, TAddrInfo tAddrInfo, CWnd* pParent=NULL );
// Dialog Data
	//{{AFX_DATA(CLocalAddrbookMeetEdit)
	enum { IDD = IDD_DIALOG_LOCALADDR_MEETINGEDIT };
	CTransparentStatic	m_stEditMeet;
	CTransparentStatic	m_stMeetCode;
	CTransparentStatic	m_stMeetName;
	CTransparentBtn		m_btnCancel;
	CTransparentBtn		m_btnSave;
	CTransparentEdit	m_etMeetName;
	CTransparentEdit	m_etMeetCode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocalAddrbookMeetEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CCncAddrbookIF *m_pAddrBook;
	CAddrEntry m_AddrEntry;

	TAddrInfo  m_tAddrInfo;
	bool m_Editing;

	// Generated message map functions
	//{{AFX_MSG(CLocalAddrbookMeetEdit)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCALADDRMEETINGEDIT_H__BF8705B1_69D8_40B9_8A40_8EFA47276F08__INCLUDED_)
