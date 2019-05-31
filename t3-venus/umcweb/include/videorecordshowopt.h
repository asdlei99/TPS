#if !defined(AFX_VIDEORECORDSHOWOPT_H__FE964C31_F5E2_4B51_BC11_316A159C7C85__INCLUDED_)
#define AFX_VIDEORECORDSHOWOPT_H__FE964C31_F5E2_4B51_BC11_316A159C7C85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// videorecordshowopt.h : header file
//

enum EM_ShowStateRecord
{
    emShowAllRecord = 0,
	emShowRecord,
	emShowPlay,
}; 


/////////////////////////////////////////////////////////////////////////////
// CVideoRecordShowOpt dialog

class CVideoRecordShowOpt : public CTransparentBaseDlg
{
// Construction
public:
	CVideoRecordShowOpt(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVideoRecordShowOpt)
	enum { IDD = IDD_DIALOG_VIDEORECORDSHOWOPT };
	CTransparentStatic	m_stcCheck;
	CTransparentStatic	m_stcAll;
	CTransparentStatic	m_stcRecord;
	CTransparentStatic	m_stcPlay;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoRecordShowOpt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVideoRecordShowOpt)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	afx_msg LRESULT OnHideWndNotify( WPARAM wParam, LPARAM lParam );
	afx_msg void OnStaticAll();
	afx_msg void OnStaticRecord();
	afx_msg void OnStaticPlay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
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

	void HideMsgBox();

	void UpdateShowOption();

public:
	static CVideoRecordShowOpt* GetDlgPtr();
	static void Clean();	
	void InitDlg();

	EM_ShowStateRecord  m_emShowState;         //ɸѡ״̬

private:
	static CVideoRecordShowOpt *m_pDlg;

	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEORECORDSHOWOPT_H__FE964C31_F5E2_4B51_BC11_316A159C7C85__INCLUDED_)
