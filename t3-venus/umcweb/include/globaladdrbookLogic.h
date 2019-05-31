/*****************************************************************************
ģ����      : CGkServerSetLogic
�ļ���      : gkserversetLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcweb ȫ�ֵ�ַ��ģ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/5/22      1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_GLOBALADDRBOOK_H__83F27E0D_40FA_4540_9ECD_0B06FC18AEBA__INCLUDED_)
#define AFX_GLOBALADDRBOOK_H__83F27E0D_40FA_4540_9ECD_0B06FC18AEBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// globaladdrbookLogic.h : header file
//
#include "cncaddrbookif.h"
#include "addrbook.h"

/////////////////////////////////////////////////////////////////////////////
// CGlobalAddrbookLogic dialog
class CGlobalAddrbookLogic : public CDlgChild
{
// Construction
public:
	CGlobalAddrbookLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGlobalAddrbookLogic)
	enum { IDD = IDD_DIALOG_GLOBALADDRBOOK };
	CTransparentStatic m_stLeftTitle;
	CTransparentBtn	m_btnAllSel;
	CTransparentBtn	m_btnExport;
	CTransparentBtn	m_btnRefresh;
	CTransparentEdit m_etAddrSearch;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGlobalAddrbookLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGlobalAddrbookLogic)
	afx_msg void OnBtnAllSel();
	afx_msg void OnBtnExport();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBtnRefresh();
	//}}AFX_MSG
	afx_msg LRESULT OnRefreshGlobalAddrbook(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnWaitRefreshOverTime(WPARAM wParam,LPARAM lParam);
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
    2012/04/20  1.0               ����
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
    2012/05/24  1.0     ����ӡ    ����
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
    2012/04/20  1.0     ����ӡ    ����
    =============================================================================*/
	virtual BOOL InitControlPane();

	void UpdateShowList();

	/*=============================================================================
    �� �� ��:OnClickGlobalLstItem
    ��    ��:ȫ�ֵ�ַ������¼�
    ��    ��:const IArgs & arg                          [in]    ���value
    ע    ��:��
    �� �� ֵ:bool�ɹ�ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/20  1.0     ����ӡ    ����
    =============================================================================*/
	bool OnClickGlobalLstItem( const IArgs & arg );
    bool OnClickGlobalLstItemIcon( const IArgs & arg );

	//��Ӧ������仯�¼�
	void OnSearchEditChange();

	void UpdateUIState();

private:
	CListChild* m_plsGlobalAddrbook;
	CLetterIndex* m_pLetterIndex;
	
	vector<TAddrItem> m_vctShowList;
	vector<TAddrItem> m_vctSearchList;

	CUmsConfigCtrlIF *m_pUmsConfig;
	CCncAddrbookIF *m_pCncAddrBook;
	TAddrItem  m_tAddrItem;                     //��ǰ��ѡ��ȫ�ֵ�ַ����Ŀ
	vector<TAddrItem> m_vctGlobalAddrList;      //ȫ�ֵ�ַ��
	vector<TAddrItem> m_vctSelectList;          //ѡ���б�
	BOOL m_bIsAllSel;

};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLOBALADDRBOOK_H__83F27E0D_40FA_4540_9ECD_0B06FC18AEBA__INCLUDED_)
