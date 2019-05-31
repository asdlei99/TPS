/*****************************************************************************
ģ����      : CVTRLogic
�ļ���      : vtrlogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcweb ¼�������ģ��
����        : ʯ��
�汾        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/4/8       1.0         ʯ��        ����
******************************************************************************/
#if !defined(AFX_VTRLOGIC_H__8408D96D_1F9B_45BB_AD60_E868DBEC1D50__INCLUDED_)
#define AFX_VTRLOGIC_H__8408D96D_1F9B_45BB_AD60_E868DBEC1D50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "vtrsetlogic.h"
#include "vediofilelistlogic.h"
#include "vediorecordlogic.h"


// vtrlogic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVTRLogic dialog

class CVTRLogic : public CDlgChild
{
// Construction
public:
	CVTRLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVTRLogic)
	enum { IDD = IDD_DIALOG_VTR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVTRLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVTRLogic)
	afx_msg void OnDestroy();
	afx_msg LRESULT OnTabChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRecBaseInfoNty( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecFileListInfoNty( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecMdyFileRsp( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecDelFileRsp( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecConfRecInfoNty( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecConfPlayInfoNty( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRefreshConfListNty( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecStartConfRsp( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecStopRecordRsp( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecPauseRecordRsp( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecResumeRecordRsp( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecStartPlayRsp( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecStopPlayRsp( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecPausePlayRsp( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnRecResumePlayRsp( WPARAM wparam, LPARAM lparam );

	afx_msg LRESULT OnVtrNty( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnAddVtrRsp( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnDelVtrRsp( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnMdyVtrRsp( WPARAM wparam, LPARAM lparam );

	afx_msg LRESULT OnVtrRegStateNty(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRecMtFormatRsp(WPARAM wParam, LPARAM lParam);
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

	virtual BOOL ShowWindow( int nCmdShow );


private:
	/*=============================================================================
    �� �� ��:InitChildWindow
    ��    ��:��ʼ���Ӵ�����ͼ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/08  1.0     ʯ��		����
    =============================================================================*/
	BOOL InitChildWindow();

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
	void ShowActiveWindow( EM_CURRENT_WND_VIEW_TYPE emWndType );

public:
	CVTRSetLogic *m_pVTRSetLogic;
	CVedioFileListLogic *m_pVedioFileListLogic;
	CVedioRecordLogic *m_pVedioRecordLogic;
	CWnd *m_pCurrentCwd;

	//---umslib���ƽӿ� 
	CUmsVTRCtrlIF *m_pVTRCtrlIF;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VTRLOGIC_H__8408D96D_1F9B_45BB_AD60_E868DBEC1D50__INCLUDED_)
