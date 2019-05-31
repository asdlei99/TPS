/*****************************************************************************
ģ����      : CUmsSystimeSetLogic
�ļ���      : umssystimesetLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcwebϵͳʱ������ģ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/4.17      1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_SYSTEMTIME_H__5E96BED9_FFF7_4134_B057_504950783EE2__INCLUDED_)
#define AFX_SYSTEMTIME_H__5E96BED9_FFF7_4134_B057_504950783EE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// umssystimesetLogic.h : header file
//
#include "CalendarDlg.h"

class CUmsSystimeSetLogic : public CDlgChild
{
// Construction
public:
	CUmsSystimeSetLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUmsSystimeSetLogic)
	enum { IDD = IDD_DIALOG_SYSTIMESET };
	CTransparentStatic	m_stDate;
	CTransparentStatic	m_stStartTime;
	CTransparentEdit	m_etSetHour;
	CTransparentEdit	m_etSetMin;
	CTransparentEdit	m_etSetSec;
	CTransparentEdit    m_edtDotHour;
    CTransparentEdit    m_edtDotMin;
	CTransparentCheckButton		m_btnCalendar;
	CTransparentBtn	    m_btnPlus;
	CTransparentBtn	    m_btnMinus;
	CTransparentEdit	m_etDateSet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUmsSystimeSetLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUmsSystimeSetLogic)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnCalendar();
	afx_msg void OnBtnPlus();
	afx_msg void OnBtnMinus();
	afx_msg HRESULT OnHideAUtoHideWnd( WPARAM wparam, LPARAM lparam );
	afx_msg HRESULT OnGetUmsSystimeTime( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnUpdateCalendarSelDate(WPARAM wParam, LPARAM lParam);        //����ѡ��ʱ��
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSetfocusEditHour();
	afx_msg void OnSetfocusEditMinute();
	afx_msg void OnUpdateEditMinute();
	afx_msg void OnUpdateEditSec();
	afx_msg void OnSetfocusEditSec();
	afx_msg void OnUpdateEditHour();
    afx_msg	LRESULT OnTimeEditChange(WPARAM wParam, LPARAM lParam);
    afx_msg	LRESULT OnBtnHold(WPARAM wParam, LPARAM lParam);  
    afx_msg	LRESULT OnBtnHoldEnd(WPARAM wParam, LPARAM lParam);       
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
    2012/04/24  1.0               ����
    =============================================================================*/
    void InitDlg();

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
    2012/04/28  1.0     ����ӡ    ����
    =============================================================================*/
	virtual BOOL InitControlPane();

	/*=============================================================================
    �� �� ��:SaveSysTime
    ��    ��:����ϵͳʱ��
    ��    ��:BOOL32 bSave = TRUE                          [in]  TRUE:����ϵͳʱ�䵽UMS������  FALSE:��ʾ����ʱ��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/26  1.0     ����ӡ    ����
    =============================================================================*/
	BOOL SaveSysTime();

	/*=============================================================================
    �� �� ��:UpdateSysTimeToControl
    ��    ��:����ϵͳʱ��ؼ�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/28  1.0     ����ӡ    ����
    =============================================================================*/
	void UpdateSysTimeToControl(struct tm& tmDate);

	void SyncTimeToServer();
	void SetTimeControl(BOOL bIsOn);

	CCalendarDlg m_dlgCalendar;
    
    UINT m_nTimer;   //save timer ID
    bool m_bIsEdit;  //clicked edit

private:
	CUmsConfigCtrlIF *m_pUmsConfig;
	time_t m_timeDate;

    int     m_nExHour;
    int     m_nExMin;
    int     m_nExSec;
    EM_CURRENT_FOCUS     m_emCurFocus;
    bool    m_bEnterCalendar; //whether clicked calendar Dlg.
	BOOL m_bEditingDate;
    
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEMTIME_H__5E96BED9_FFF7_4134_B057_504950783EE2__INCLUDED_)
