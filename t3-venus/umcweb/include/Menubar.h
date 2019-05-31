/*****************************************************************************
ģ����      : CMenubar
�ļ���      : Menubar.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcweb �˵�ѡ���
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/5/20      1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_MENUBAR_H__DF917F80_FB16_4C31_8962_EB31FE959951__INCLUDED_)
#define AFX_MENUBAR_H__DF917F80_FB16_4C31_8962_EB31FE959951__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Menubar.h : header file
//
#include "transparentbasedlg.h"
class CMenubar : public CTransparentBaseDlg
{
// Construction
public:
	CMenubar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMenubar)
	enum { IDD = IDD_DIALOG_MENUBAR };
	CTransparentStatic	m_stOrderMeet;
	CTransparentStatic	m_stCurMeet;
	CTransparentStatic	m_stCheck;
	CTransparentStatic	m_stAllMeet;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMenubar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMenubar)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnClickAllMeet();
	afx_msg void OnClickCurMeet();
	afx_msg void OnClickOrderMeet();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void SetMenuCheck(EM_MENU_MEETTYPE emMenuCheck){ m_emMenuCheck = emMenuCheck;};
	EM_MENU_MEETTYPE GetMenuCheck(){ return m_emMenuCheck;};
	void InitMenuBtn();

private:
	EM_MENU_MEETTYPE m_emMenuCheck;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MENUBAR_H__DF917F80_FB16_4C31_8962_EB31FE959951__INCLUDED_)
