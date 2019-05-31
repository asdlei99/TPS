#if !defined(AFX_VIDEORECORDEPSHOWOPT_H__13B3ACCB_0D45_4166_BE56_04B756BD2574__INCLUDED_)
#define AFX_VIDEORECORDEPSHOWOPT_H__13B3ACCB_0D45_4166_BE56_04B756BD2574__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// videorecordepshowopt.h : header file
//

enum EM_ShowStateRecordEp
{
    emShowAllRecordEp = 0,
	emShowRecordEp,
}; 


/////////////////////////////////////////////////////////////////////////////
// CVideoRecordEpShowOpt dialog

class CVideoRecordEpShowOpt : public CTransparentBaseDlg
{
// Construction
public:
	CVideoRecordEpShowOpt(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVideoRecordEpShowOpt)
	enum { IDD = IDD_DIALOG_VIDEORECORDEPSHOWOPT };
	CTransparentStatic	m_stcCheck;
	CTransparentStatic	m_stcAll;
	CTransparentStatic	m_stcRecord;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoRecordEpShowOpt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVideoRecordEpShowOpt)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	afx_msg LRESULT OnHideWndNotify( WPARAM wParam, LPARAM lParam );
	afx_msg void OnStaticAll();
	afx_msg void OnStaticRecord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
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
	static CVideoRecordEpShowOpt* GetDlgPtr();
	static void Clean();	
	void InitDlg();

	EM_ShowStateRecordEp  m_emShowState;         //ɸѡ״̬

private:
	static CVideoRecordEpShowOpt *m_pDlg;

	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEORECORDEPSHOWOPT_H__13B3ACCB_0D45_4166_BE56_04B756BD2574__INCLUDED_)
