/*****************************************************************************
ģ����      : CGkServerSetLogic
�ļ���      : gkserversetLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcweb GK����������ģ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/5/04      1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_DLGGKSET_H__26BDFD46_062C_4AF8_9F8F_372D2AE1264B__INCLUDED_)
#define AFX_DLGGKSET_H__26BDFD46_062C_4AF8_9F8F_372D2AE1264B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//gkserversetLogic.h : header file
//
enum EM_GK_SERVER_BUTTONSTATUS{GK_ON = 0,GK_OFF};

class CGkServerSetLogic : public CDlgChild
{
// Construction
public:
	CGkServerSetLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGkServerSetLogic)
	enum { IDD = IDD_DIALOG_GKSERVERSET };
	CTransparentStatic	m_stGkOnAndOff;
	CTransparentStatic	m_stIpAddr;
	CTransparentIpEdit	m_Ip;
	CTransparentSwitchButton m_btnSwitch;
	//}}AFX_DATA

	EM_GK_SERVER_BUTTONSTATUS m_emGkSerBtnStatus;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGkServerSetLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGkServerSetLogic)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnClickSwitchBtn(WPARAM wParam, LPARAM lParam);
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

	BOOL GetGKSwitchStatus(){return m_btnSwitch.GetSwitchState();};

	void SetSwitch();

	BOOL m_bSwitchStatus;
    
    bool m_bIsEdit;  //clicked edit
    
private:

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGKSET_H__26BDFD46_062C_4AF8_9F8F_372D2AE1264B__INCLUDED_)
