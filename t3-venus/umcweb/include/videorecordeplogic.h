#if !defined(AFX_VIDEORECORDEPLOGIC_H__06DB2F60_F191_48CB_89DC_F5BE6B6E8E17__INCLUDED_)
#define AFX_VIDEORECORDEPLOGIC_H__06DB2F60_F191_48CB_89DC_F5BE6B6E8E17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// videorecordeplogic.h : header file
//

#include "vediorecordnameeditlogic.h"

//����������
enum EmSchemeRecordEp
{
	emSchemeRecordEpClean = 0,
	emSchemeRecordEpSelItem,
	emSchemeRecordEpNoVtr,
	emSchemeRecordEpEnd,
	emSchemeRecordEpNoShow,
	emSchemeRecordEpDelConf
};

/////////////////////////////////////////////////////////////////////////////
// CVideoRecordEpLogic dialog

class CVideoRecordEpLogic : public CDlgChild
{
// Construction
public:
	CVideoRecordEpLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVideoRecordEpLogic)
	enum { IDD = IDD_DIALOG_VIDEORECORD_EP };
	CTransparentStatic	m_stcRecordTimeReal;
	CTransparentStatic	m_stcRecordTime;
	CTransparentStatic	m_stcTitle;
	CTransparentStatic	m_stcChildTitle;
	CTransparentEdit	m_edtSearch;
	CTransparentBtn	m_btnRecordStop;
	CTransparentBtn	m_btnRecordStart;
	CTransparentBtn	m_btnRecordResume;
	CTransparentBtn	m_btnRecordFinish;
	CTransparentBtn	m_btnBack;
	CTransparentSwitchButton	m_btnShowEx;
	CTransparentStatic m_stcRecFileName;
	CTransparentStatic m_stcRecFileNameReal;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoRecordEpLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVideoRecordEpLogic)
	afx_msg void OnDestroy();
	afx_msg void OnButtonRecordReturn();
	afx_msg void OnButtonVtrRecordStart();
	afx_msg void OnButtonVtrRecordResume();
	afx_msg void OnButtonVtrRecordStop();
	afx_msg void OnButtonVtrRecordFinish();
	afx_msg LRESULT OnUpdateEDITSearch( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnTimer( WPARAM wparam, LPARAM lparam );
	
	afx_msg LRESULT OnShowOptNty( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnBtnSwitch(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnHideOptn( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnNoSelResultNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnVtrRegStateNty(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRecMtFormatRsp(WPARAM wParam, LPARAM lParam);
	
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
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

protected:
	bool OnClickListItem( const IArgs & arg );
	bool OnClickListItemIcon( const IArgs & arg );

public:
	//0:��¼�������Ϣ����	1:¼����Ϣ����	2:������Ϣ����
	void RefreshConfEpList( int nRefresh = 0 );

	void LoadScheme( EmSchemeRecordEp emScheme );

private:
	void SetRecordEpInfo();
	TConRecState* GetRecMtInfo();
	void ShowSelItem();

public:
	TUmcRecInfo  m_tRecInfoSel;

private:
	CListChild* m_pList;
	CLetterIndex* m_pLetterIndex;

	//---umslib���ƽӿ� 
	CUmsVTRCtrlIF *m_pVTRCtrlIF;

	vector<TUmcRecInfo> m_vecTRecInfoSearch;
	vector<TUmcRecInfo> m_vecTRecInfo;

	CVedioRecordNameEditLogic* m_pCVedioRecordNameEditLogic;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEORECORDEPLOGIC_H__06DB2F60_F191_48CB_89DC_F5BE6B6E8E17__INCLUDED_)
