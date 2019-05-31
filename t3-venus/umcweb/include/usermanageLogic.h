/*****************************************************************************
ģ����      : CUserManageLogic
�ļ���      : usermanageLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcweb�û�����ģ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/4/16      1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_USER_H__1D927FCF_0EC8_445B_9D54_CFEA8B91D70F__INCLUDED_)
#define AFX_USER_H__1D927FCF_0EC8_445B_9D54_CFEA8B91D70F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// usermanageLogic.h : header file
//
class CUserManageLogic : public CDlgChild
{
// Construction
public:
	CUserManageLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUserManageLogic)
	enum { IDD = IDD_DIALOG_USERMANAGE };
	CTransparentStatic	m_stChildBkRight;
	CTransparentStatic	m_stChildBkLeft;
	CTransparentStatic	m_stUserLeftTitle;
	CTransparentStatic	m_stUserRightTitle;
	CTransparentStatic	m_stUserName;
	CTransparentStatic	m_stPassword;
	CTransparentEdit	m_etUserName;
	CTransparentEdit	m_etPassword;
	CTransparentBtn	    m_btnSave;
	CTransparentBtn	    m_btnCancel;
	CTransparentBtn	    m_btnEdit;
	CTransparentEdit    m_etSearch;
	CTransparentBtn	    m_btnNewUser;
	CTransparentBtn	    m_btnDelete;
	CTransparentBtn	    m_btnAllSel;
	//}}AFX_DATA


private:
	CListChild* m_plsUser;
	CLetterIndex* m_pLetterIndex;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserManageLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserManageLogic)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnCancel();
	afx_msg void OnBtnDelete();
	afx_msg void OnBtnAllSelect();
	afx_msg void OnBtnNewUser();
	afx_msg void OnBtnEdit();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnRefreshUserList(WPARAM wParam, LPARAM lParam);          //ˢ���û��б�֪ͨ
	afx_msg LRESULT OnUserOperateResultNotify(WPARAM wParam, LPARAM lParam);  //�û������������
	afx_msg LRESULT OnNoSelResultNotify(WPARAM wParam, LPARAM lParam);        //δѡ���κ��û��б�֪ͨ
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
    2012/04/20  1.0     ����ӡ    ����
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

	/*=============================================================================
    �� �� ��:SetControlPos
    ��    ��:�������пؼ�Ԫ��λ��  �ṩ������Ӧ�ֱ���
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/20  1.0     ����ӡ    ����
    =============================================================================*/
	void SetControlPos();

	/*=============================================================================
    �� �� ��:ResetInitPage
    ��    ��:���ý���ؼ�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/20  1.0     ����ӡ    ����
    =============================================================================*/
	void ResetInitPage();

	/*=============================================================================
    �� �� ��:ShowControlNewPage
    ��    ��:�½�ҳ��ؼ���ʾ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/20  1.0     ����ӡ    ����
    =============================================================================*/
	void ShowControlNewPage();

	/*=============================================================================
    �� �� ��:ShowControlScanfPage
    ��    ��:���ҳ��ؼ���ʾ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/20  1.0     ����ӡ    ����
    =============================================================================*/
	void ShowControlScanfPage();

	/*=============================================================================
    �� �� ��:ShowControlEditPage
    ��    ��:�༭ҳ��ؼ���ʾ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/20  1.0     ����ӡ    ����
    =============================================================================*/
	void ShowControlEditPage();

	/*=============================================================================
    �� �� ��:HideAllPageCtrl
    ��    ��:�������пؼ�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/20  1.0     ����ӡ    ����
    =============================================================================*/
	void HideAllPageCtrl();

	/*=============================================================================
    �� �� ��:UserListRefresh
    ��    ��:�û��б�ˢ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/20  1.0     ����ӡ    ����
    =============================================================================*/
	void UserListRefresh();

	/*=============================================================================
    �� �� ��:OnClickLstItem
    ��    ��:�û��б����¼�
    ��    ��:const IArgs & arg                          [in]    ���value
    ע    ��:��
    �� �� ֵ:bool�ɹ�ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/20  1.0     ����ӡ    ����
    =============================================================================*/
	bool OnClickLstItem( const IArgs & arg );
    bool OnClickLstItemIcon( const IArgs & arg );

	/*=============================================================================
    �� �� ��:UpdateShowList
    ��    ��:�û��б�չ��ͳһ�ӿ�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/20  1.0     ����ӡ    ����
    =============================================================================*/
	void UpdateShowList();

	/*=============================================================================
    �� �� ��:UpdateUIState
    ��    ��:ȫѡ�Ȱ�ť״̬����
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/06/29  1.0     ����ӡ    ����
    =============================================================================*/
	void UpdateUIState();

	/*=============================================================================
    �� �� ��:JumpToSelLine
    ��    ��:�½� �༭�Ȳ�����ǰѡ���еĶ�λ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/06/30  1.0     ����ӡ    ����
    =============================================================================*/
	void JumpToSelLine();

	/*=============================================================================
    �� �� ��:OnSearchEditChange
    ��    ��:��ѯ�ؼ����б�Ĺ����¼�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/07/02  1.0     ����ӡ    ����
    =============================================================================*/
	void OnSearchEditChange();

private:
	//---umslib���ƽӿ� 
	CUserCtrlIF * m_pUserctrlIF;

	//---��������
	EM_USERWND_CUROPERATE_STATE m_emCurOperateFlag;
	BOOL m_bIsAllSel;
	BOOL m_bJumpFlag;							//�½��û���ת��ѡ�б�־
	std::set<CString> m_setSelectedIconItem;	//��ǰ��ѡ���б�Item����
	CUserFullInfo m_selUser;					//��ǰѡ���û�

	//��������
	TplArray<CUserFullInfo> m_tpRefreshList;    //�û�ˢ���б�
	TplArray<CUserFullInfo> m_tplShowList;      //�û�չ���б�
	TplArray<CUserFullInfo> m_tpSearchList;     //�û���ѯ�б�
	vector<CUserFullInfo>   m_vecShowList;      //�û�չ���б�����
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USER_H__1D927FCF_0EC8_445B_9D54_CFEA8B91D70F__INCLUDED_)
