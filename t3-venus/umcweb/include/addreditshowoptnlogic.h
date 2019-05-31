#if !defined(AFX_ADDREDITSHOWOPTNLOGIC_H__1CFF73D4_F8EA_4317_AB2D_A574D3B27DF6__INCLUDED_)
#define AFX_ADDREDITSHOWOPTNLOGIC_H__1CFF73D4_F8EA_4317_AB2D_A574D3B27DF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// addreditshowoptnlogic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddrEditShowOptnLogic dialog	

class CAddrEditShowOptnLogic : public CTransparentBaseDlg
{
// Construction
public:
	CAddrEditShowOptnLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddrEditShowOptnLogic)
	enum { IDD = IDD_DIALOG_ADDREDITSHOWOPT };
	CTransparentStatic	m_stcOnline;
	CTransparentStatic	m_stcNotOnline;
	CTransparentStatic	m_stcNewGroupIcon;
	CTransparentStatic	m_stcNewGroup;
	CTransparentStatic	m_stcImportAddrBookIcon;
	CTransparentStatic	m_stcImportAddrBook;
	CTransparentStatic	m_stcGroup;
	CTransparentStatic	m_stcCheck;
	CTransparentStatic	m_stcAll;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddrEditShowOptnLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddrEditShowOptnLogic)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	afx_msg LRESULT OnHideWndNotify( WPARAM wParam, LPARAM lParam );
	afx_msg void OnStaticAll();
	afx_msg void OnStaticCheck();
	afx_msg void OnStaticGroup();
	afx_msg void OnStaticImportAddrbook();
	afx_msg void OnStaticImportAddrbookIcon();
	afx_msg void OnStaticNewGroup();
	afx_msg void OnStaticNewGroupIcon();
	afx_msg void OnStaticNotonline();
	afx_msg void OnStaticOnline();
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

	

public:
	static CAddrEditShowOptnLogic* GetDlgPtr();
	static void Clean();
	void InitDlg();
	void SetMenuCheck(EM_MENU_ADDRBOOKTYPE emMenuCheck);

private:
	static CAddrEditShowOptnLogic *m_pDlg;
	EM_MENU_ADDRBOOKTYPE m_emMenuCheck;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDREDITSHOWOPTNLOGIC_H__1CFF73D4_F8EA_4317_AB2D_A574D3B27DF6__INCLUDED_)
