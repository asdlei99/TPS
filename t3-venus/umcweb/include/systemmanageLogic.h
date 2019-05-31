/*****************************************************************************
ģ����      : CSystemManageLogic
�ļ���      : systemmanageLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcwebϵͳ����ģ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/5/01      1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_SYSTEMDLG_H__F361BBD4_F48A_4A58_808E_F51215149564__INCLUDED_)
#define AFX_SYSTEMDLG_H__F361BBD4_F48A_4A58_808E_F51215149564__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// systemmanageLogic.h : header file
//
#include "sipserversetLogic.h"
#include "umsnetworksetLogic.h"
#include "umssystimesetLogic.h"
#include "gkserversetLogic.h"
#include "ListChild.h"
#include "nmcfglogic.h"
#include "vtrcfglogic.h"

#define SYSTEM_WND_MENU_UMSWEBCONFIG _T("UMS��������������")
#define SYSTEM_WND_MENU_SIPCONFIG _T("����ע�����������")
#define SYSTEM_WND_MENU_SYSTEMTIME _T("ϵͳʱ��")
#define SYSTEM_WND_MENU_GKCONFIG _T("GK����")
#define SYSTEM_WND_MENU_NMCFG _T("���ܷ���������")
#define SYSTEM_WND_MENU_VTRCFG _T("¼�������")

/////////////////////////////////////////////////////////////////////////////
// CSystemManageLogic dialog
class CSystemManageLogic : public CDlgChild
{
// Construction
public:
	CSystemManageLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSystemManageLogic)
	enum { IDD = IDD_DIALOG_SYSTEMSET };
	CTransparentStatic	m_stChildBkRight;
	CTransparentStatic	m_stChildBkLeft;
	CTransparentBtn   	m_btnEdit;
	CTransparentStatic	m_stChildWndTitle;
	CTransparentStatic	m_stTitle;
	CTransparentBtn	    m_btnCancel;
	CTransparentBtn     m_btnSave;
	CTransparentBtn	    m_btnTimeSync;
	//}}AFX_DATA

private:   //�ؼ�Ԫ��
	CUmsNetworkSetLogic m_networkdlg;
	CSipServerSetLogic m_serversetdlg;
	CUmsSystimeSetLogic m_SystemTime;
	CGkServerSetLogic m_gkset;
	CNMCfgLogic m_cNMCfgLogic;
	CVTRCfgLogic m_cVTRCfgLogic;

	CListChild* m_plsMenu;    


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSystemManageLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSystemManageLogic)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnCancel();   
    
	afx_msg void OnDestroy();
	afx_msg void OnBtnEdit();


    
	afx_msg void OnBtnTimeSync();
	afx_msg LRESULT OnEthnetNotify(WPARAM wParam, LPARAM lParam);  //������Ϣ֪ͨ
	afx_msg LRESULT OnRegSipNotify(WPARAM wParam, LPARAM lParam);  //ע���������Ϣ֪ͨ
	afx_msg LRESULT OnRegSipResult(WPARAM wParam, LPARAM lParam);  //ע����������
	afx_msg LRESULT OnRegGKResult(WPARAM wParam, LPARAM lParam);   //ע��GK���
    afx_msg LRESULT OnRecGKNotify(WPARAM wParam, LPARAM lParam);   //�õ�UMS���͹����� GKINFO
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg LRESULT OnRefreshGlobalAddrbook(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnRefreshGlobalAddrbookEx(WPARAM wParam,LPARAM lParam);
	afx_msg HRESULT OnGetUmsSystimeTime( WPARAM wparam, LPARAM lparam );
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
    2012/04/23  1.0               ����
    =============================================================================*/
    void InitDlg();

	/*=============================================================================
    �� �� ��:RegisterFun
    ��    ��:List�������ע��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/26  1.0     ����ӡ    ����
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
	virtual BOOL InitChildWindow();

	/*=============================================================================
    �� �� ��:SetControlPos
    ��    ��:�������пؼ�Ԫ��λ��  �ṩ������Ӧ�ֱ���
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/26  1.0     ����ӡ    ����
    =============================================================================*/
	void SetControlPos();

	/*=============================================================================
    �� �� ��:ShowActiveWindow
    ��    ��:��ʾ��ǰ���ô���
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/05/18  1.0     ����ӡ    ����
    =============================================================================*/
	void ShowActiveWindow(EM_CURRENT_WND_VIEW_TYPE emWndType);

	/*=============================================================================
    �� �� ��:SetControlStatusOff
    ��    ��:�յ�֪ͨ�ر�����ҳ��ؼ�
    ��    ��:BOOL bIsOn: TRUE����    FALSE:�ر�
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/05/17  1.0     ����ӡ    ����
    =============================================================================*/
	void SetGKControl(BOOL bIsOn);

	/*=============================================================================
    �� �� ��:OnClickLstItem
    ��    ��:ϵͳ�˵��б����¼�
    ��    ��:const IArgs & arg                          [in]    ���value
    ע    ��:��
    �� �� ֵ:bool�ɹ�ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/05/18  1.0     ����ӡ    ����
    =============================================================================*/
	bool OnClickLstItem( const IArgs & arg );

	/*=============================================================================
    �� �� ��:SaveSysTime
    ��    ��:����UMS��������
    ��    ��:��
    ע    ��:��
    �� �� ֵ:bool
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/05/16  1.0     ����ӡ    ����
    =============================================================================*/
	BOOL SaveEthnetCfg();

	/*=============================================================================
    �� �� ��:SaveRegServer
    ��    ��:����SIP��������ַ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:BOOL
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/28  1.0     ����ӡ    ����
    =============================================================================*/
	BOOL SaveRegServer();

	/*=============================================================================
    �� �� ��:����GK��������ַ
    ��    ��:����ϵͳʱ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:BOOL
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/15  1.0     ����ӡ    ����
    =============================================================================*/
	BOOL SaveGkInfo();

	/*=============================================================================
    �� �� ��:UpdateNetworkConfig
    ��    ��:��������������Ϣ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/26  1.0     ����ӡ    ����
    =============================================================================*/
	void RevertNetConfig();
    
    void SetEditControl( bool bIsEnable );

    void SetNetCfgControl( bool bIsEnable );

    void SetControlToDefault();

private:
	CUmsConfigCtrlIF *m_pUmsConfig; //umslib���ýӿ�
	CWnd* m_currentCwd;         //��ǰ�����ͼ
	BOOL m_bGkSwitchStatus;
    DWORD m_dwIpGKServer;
	DWORD m_dwIpRegServer;
    s32 m_emCurrViewType;            //save clicked emun item 

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEMDLG_H__F361BBD4_F48A_4A58_808E_F51215149564__INCLUDED_)
