/*****************************************************************************
ģ����      : CLoginLogic
�ļ���      : loginLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcweb ��½ģ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/4/05      1.0         ����ӡ      ����
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
    �� �� ��:RegisterFun
    ��    ��:ע�ắ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/06/29  1.0     ����ӡ    ����
    =============================================================================*/
	void RegisterFun();

	/*=============================================================================
    �� �� ��:InitControlPane
    ��    ��:��ʼ��ҳ��ؼ�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/05  1.0     ����ӡ    ����
    =============================================================================*/
	virtual BOOL InitControlPane();

	/*=============================================================================
    �� �� ��:ShowWarningWnd
    ��    ��:�Ƿ���ʾ���Ѵ���
    ��    ��:UINT nShowFlag                          [in]    TRUE:��ʾ   FALSE:����
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/05  1.0     ����ӡ    ����
    =============================================================================*/
	void ShowWarningWnd(UINT nShowFlag);

	/*
	* ���õ�½����IP
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
