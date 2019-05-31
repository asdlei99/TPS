/*****************************************************************************
ģ����      : CMainLogic
�ļ���      : mainLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcweb ������ģ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/4/08      1.0         ����ӡ      ����
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
    �� �� ��:InitDlg
    ��    ��:ҳ���������Ϻ��ʼ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/23  1.0               ����
    =============================================================================*/
    void InitDlg();

	/*=============================================================================
    �� �� ��:InitControlPane
    ��    ��:��ʼ��ҳ��ؼ�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/24  1.0     ����ӡ    ����
    =============================================================================*/
	virtual BOOL InitControlPane();


	/*=============================================================================
    �� �� ��:InitChildWindow
    ��    ��:��ʼ���Ӵ�����ͼ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/24  1.0     ����ӡ    ����
    =============================================================================*/
	BOOL InitChildWindow();

	/*=============================================================================
    �� �� ��:ShowActiveWindow
    ��    ��:��ʾ��ǰ���ܴ���
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/05/18  1.0     ����ӡ    ����
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
