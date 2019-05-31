/*****************************************************************************
ģ����      : CVTRCfgLogic
�ļ���      : vtrcfglogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcweb ¼�������ģ��
����        : ʯ��
�汾        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/4/8       1.0         ʯ��        ����
******************************************************************************/
#if !defined(AFX_VTRSETLOGIC_H__3D7BC606_AD76_44DE_86E2_ACB0F5266B8E__INCLUDED_)
#define AFX_VTRSETLOGIC_H__3D7BC606_AD76_44DE_86E2_ACB0F5266B8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "vediofilelistlogic.h"

// vtrsetlogic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVTRSetLogic dialog

class CVTRSetLogic : public CDlgChild
{
// Construction
public:
	CVTRSetLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVTRSetLogic)
	enum { IDD = IDD_DIALOG_VTRSET };
	CTransparentStatic	m_stcVtrNameReal;
	CTransparentStatic	m_stcDiskSpaceTotalReal;
	CTransparentStatic	m_stcDiskSpaceAvailableReal;
	CTransparentStatic	m_stcTitle;
	CTransparentStatic	m_stcVTRName;
	CTransparentStatic	m_stcDiskSpaceTotal;
	CTransparentStatic	m_stcDiskSpaceAvailable;
	CTransparentStatic	m_stcChildWndTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVTRSetLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CVTRSetLogic)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnRecBaseInfoNty( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnVtrNty( WPARAM wparam, LPARAM lparam );
	afx_msg void OnShowWindow( BOOL bShow, UINT nStatus );
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
    2013/04/08  1.0     ʯ��      ����
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
    2013/4/7    1.0     ʯ��      ����
    =============================================================================*/
	virtual BOOL InitControlPane();

	/*=============================================================================
    �� �� ��:RegisterFun
    ��    ��:List�������ע��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2013/4/8    1.0     ʯ��      ����
    =============================================================================*/
	void RegisterFun();

	/*=============================================================================
    �� �� ��:SetControlPos
    ��    ��:�������пؼ�Ԫ��λ��  �ṩ������Ӧ�ֱ���
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/4/8    1.0     ʯ��      ����
    =============================================================================*/
	void SetControlPos();

protected:
	/*=============================================================================
    �� �� ��:OnClickLstItem
    ��    ��:ϵͳ�˵��б����¼�
    ��    ��:const IArgs & arg                          [in]    ���value
    ע    ��:��
    �� �� ֵ:bool�ɹ�ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2013/04/08  1.0     ʯ��      ����
    =============================================================================*/
	bool OnClickLstItem( const IArgs & arg );

private:
	//������Ϣ�е�������Ч����ev_Vcr_nty�е�����
	void SetRecBaseInfo( vector<TRecBaseInfo> &vecTRecBaseInfo );

private:
	CListChild* m_pListMenu;

	//---umslib���ƽӿ� 
	CUmsVTRCtrlIF *m_pVTRCtrlIF;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VTRSETLOGIC_H__3D7BC606_AD76_44DE_86E2_ACB0F5266B8E__INCLUDED_)
