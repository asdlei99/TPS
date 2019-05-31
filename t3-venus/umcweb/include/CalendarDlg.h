/*****************************************************************************
ģ����      : CCalendarDlg
�ļ���      : CalendarDlg.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcweb �����ؼ�
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/4/29      1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_CALENDARDLG_H__80F061A1_A543_41AF_B58C_EF4267700224__INCLUDED_)
#define AFX_CALENDARDLG_H__80F061A1_A543_41AF_B58C_EF4267700224__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalendarDlg.h : header file
//
#include "uiexhead.h"
class CCalendarDlg : public CTransparentBaseDlg
{
// Construction
public:
	CCalendarDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCalendarDlg)
	enum { IDD = IDD_DIALOG_CALENDAR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCalendarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnUpdateCalendarSelDate(WPARAM wParam, LPARAM lParam);        //����ѡ��ʱ��
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CString GetDate();
	void SetDate( int nYear,  int nMonth, int nDay );

	void SetNotifyWnd(HWND hWnd){ m_hNotifyWnd = hWnd;};


	void Clean();

private:
	CTransparentCalendar* m_pCalendar;
	HWND m_hNotifyWnd;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARDLG_H__80F061A1_A543_41AF_B58C_EF4267700224__INCLUDED_)
