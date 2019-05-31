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
2013/4/7       1.0         ʯ��        ����
******************************************************************************/
#if !defined(AFX_VTRCFGLOGIC_H__3186973F_53DF_46A1_9AA2_7A4C0B9BC6F8__INCLUDED_)
#define AFX_VTRCFGLOGIC_H__3186973F_53DF_46A1_9AA2_7A4C0B9BC6F8__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// vtrcfglogic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVTRCFGLOGIC dialog

class CVTRCfgLogic : public CDlgChild
{
// Construction
public:
	CVTRCfgLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVTRCfgLogic)
	enum { IDD = IDD_DIALOG_VTRCFG };
	CTransparentIpEdit	m_ipVTRIP;
	CTransparentEdit	m_edtVTRNo;
	CTransparentEdit	m_edtVTRName;
	CTransparentStatic	m_stcVTRIP;
	CTransparentStatic	m_stcVTRNo;
	CTransparentStatic	m_stcVTRName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVTRCfgLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual BOOL OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(CVTRCfgLogic)
	afx_msg LRESULT OnVtrNty(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAddVtrRsp(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDelVtrRsp(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMdyVtrRsp(WPARAM wParam, LPARAM lParam);
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
    2013/4/7    1.0     ʯ��      ����
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

public:
	void SetEditState( BOOL bEdit );
	BOOL SaveVTRCfg();
	void FreshNMInfo();

private:
	void SetVTRCfg();
	bool GetVTRCfg( TVcrCfg& tVTRCfg, TVcrCfg& tVTRCfgOld );
	void UpdateTip( EmModifyVcrRet emRet );

public:
    bool m_bIsEdit;  //clicked edit

	//---umslib���ƽӿ� 
	CUmsVTRCtrlIF *m_pVTRCtrlIF;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VTRCFGLOGIC_H__3186973F_53DF_46A1_9AA2_7A4C0B9BC6F8__INCLUDED_)
