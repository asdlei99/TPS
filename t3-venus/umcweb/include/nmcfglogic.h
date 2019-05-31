/*****************************************************************************
ģ����      : CNMCfgLogic
�ļ���      : nmcfglogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcweb ��������ģ��
����        : ʯ��
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/2/22      1.0         ʯ��        ����
******************************************************************************/
#if !defined(AFX_NMCFGLOGIC_H__79C6223E_7FC8_49CD_8CB8_1B73EEF5B6E7__INCLUDED_)
#define AFX_NMCFGLOGIC_H__79C6223E_7FC8_49CD_8CB8_1B73EEF5B6E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

#define UMCWEB_MAX_COMMUNITY_LENGTH		31

// nmcfglogic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNMCfgLogic dialog

class CNMCfgLogic : public CDlgChild
{
// Construction
public:
	CNMCfgLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNMCfgLogic)
	enum { IDD = IDD_DIALOG_NMCFG };
	CTransparentEdit	m_edtNMReadCommunity2;
	CTransparentEdit	m_edtNMReadCommunity1;
	CTransparentEdit	m_edtNMGetSetPort2;
	CTransparentIpEdit	m_ipNMServerIP2;
	CTransparentEdit	m_edtNMTrapPort2;
	CTransparentEdit	m_edtNMWriteCommunity2;
	CTransparentEdit	m_edtNMWriteCommunity1;
	CTransparentStatic	m_stcNMGetSetPort2;
	CTransparentStatic	m_stcNMReadCommunity1;
	CTransparentStatic	m_stcNMReadCommunity2;
	CTransparentStatic	m_stcNMWriteCommunity1;
	CTransparentStatic	m_stcNMServerIP2;
	CTransparentStatic	m_stcNMSvrIP2;
	CTransparentStatic	m_stcNMTrapPort2;
	CTransparentStatic	m_stcNMWriteCommunity2;
	CTransparentEdit	m_edtNMTrapPort1;
	CTransparentStatic	m_stcNMTrapPort1;
	CTransparentEdit	m_edtNMGetSetPort1;
	CTransparentStatic	m_stcNMGetSetPort1;
	CTransparentStatic	m_stcNMServerIP1;
	CTransparentIpEdit	m_ipNMServerIP1;
	CTransparentStatic	m_stcNMSvrIP1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNMCfgLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual BOOL OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(CNMCfgLogic)
		// NOTE: the ClassWizard will add member functions here
	afx_msg HRESULT OnNetMngNty( WPARAM wparam, LPARAM lparam );
	afx_msg HRESULT OnAddNMRsp( WPARAM wparam, LPARAM lparam );
	afx_msg HRESULT OnDelNMRsp( WPARAM wparam, LPARAM lparam );
	afx_msg HRESULT OnModNMRsp( WPARAM wparam, LPARAM lparam );
	afx_msg void OnDestroy();
	//}}AFX_MSG
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
    2013/02/26  1.0     ʯ��      ����
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
    2013/02/26  1.0     ʯ��      ����
    =============================================================================*/
	virtual BOOL InitControlPane();
public:
	BOOL SaveNMCfg();
	void SetEditState( BOOL bEdit );
	void FreshNMInfo();
private:
	void SetDefaultValue();
	void SetNMSvr( vector<TTPNMServerCfg>& vecTTPNMServerCfg );
	bool GetNMSvr( vector<TTPNMServerCfg>& vecTTPNMServerCfg );

public:
    bool m_bIsEdit;  //clicked edit

private:
	CUmsNetMngCtrlIF *m_pUmsNMConfig; //umslib���ýӿ�
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NMCFGLOGIC_H__79C6223E_7FC8_49CD_8CB8_1B73EEF5B6E7__INCLUDED_)
