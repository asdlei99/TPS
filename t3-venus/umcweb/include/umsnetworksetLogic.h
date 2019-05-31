/*****************************************************************************
ģ����      : CUmsNetworkSetLogic
�ļ���      : umsnetworksetLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcweb UMS��������ģ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/4.22      1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_SYSTEMNETWORKDLG_H__66E76971_8C16_4B2D_BA8C_23B1F3D2AB08__INCLUDED_)
#define AFX_SYSTEMNETWORKDLG_H__66E76971_8C16_4B2D_BA8C_23B1F3D2AB08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// umsnetworksetLogic.h : header file
//
class CUmsNetworkSetLogic : public CDlgChild
{
// Construction
public:
	CUmsNetworkSetLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUmsNetworkSetLogic)
	enum { IDD = IDD_DIALOG_UMSNETWORKSET };
	CTransparentStatic	m_stIpAddr;
	CTransparentStatic	m_stIpSub;
	CTransparentStatic	m_stIpGatway;
	CTransparentIpEdit	m_Ip;
	CTransparentIpEdit	m_Ip_Sub;
	CTransparentIpEdit	m_Ip_GetWay;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUmsNetworkSetLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUmsNetworkSetLogic)
	virtual BOOL OnInitDialog();
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
    2012/04/24  1.0               ����
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
    2012/04/28  1.0     ����ӡ    ����
    =============================================================================*/
	virtual BOOL InitControlPane();
    
    bool m_bIsEdit;  //clicked edit
private:
    
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEMNETWORKDLG_H__66E76971_8C16_4B2D_BA8C_23B1F3D2AB08__INCLUDED_)
