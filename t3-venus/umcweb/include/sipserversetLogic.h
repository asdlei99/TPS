/*****************************************************************************
ģ����      : CSipServerSetLogic
�ļ���      : sipserversetLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcweb SIP����������ģ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/5/03      1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_SERVERSETDLG_H__41A673EA_ACBE_498A_AC51_5C4B29527CAC__INCLUDED_)
#define AFX_SERVERSETDLG_H__41A673EA_ACBE_498A_AC51_5C4B29527CAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// sipserversetLogic.h : header file
//
class CSipServerSetLogic : public CDlgChild
{
// Construction
public:
	CSipServerSetLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSipServerSetLogic)
	enum { IDD = IDD_DIALOG_SIPSERVERSET };
	CTransparentStatic	m_stIpAddr;
	CTransparentIpEdit	m_Ip;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSipServerSetLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSipServerSetLogic)
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

#endif // !defined(AFX_SERVERSETDLG_H__41A673EA_ACBE_498A_AC51_5C4B29527CAC__INCLUDED_)
