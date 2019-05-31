/*****************************************************************************
ģ����      : CMeetDiscussLogic
�ļ���      : meetdiscusslogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcweb ��������ҳ��
����        : �컪��
�汾        : V1.0
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2014/2/13      1.0         �컪��      ����
******************************************************************************/
#if !defined(AFX_MEETDISCUSSLOGIC_H__7AB7BD0A_0FBF_4ED9_9FA9_4B32C12093F8__INCLUDED_)
#define AFX_MEETDISCUSSLOGIC_H__7AB7BD0A_0FBF_4ED9_9FA9_4B32C12093F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// meetdiscusslogic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMeetDiscussLogic dialog
class CMeetDiscussLogic : public CDlgChild
{
// Construction
public:
	CMeetDiscussLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMeetDiscussLogic)
	enum { IDD = IDD_DIALOG_MEETDISCUSS };
	CTransparentStatic	m_stDiscuss;
	CTransparentStatic	m_stGroup1;
	CTransparentStatic	m_stGroup2;
	CTransparentStatic	m_stGroup3;
	CTransparentStatic	m_stGroup4;
	CTransparentStatic	m_stGroupShow1;
	CTransparentStatic	m_stGroupShow2;
	CTransparentStatic	m_stGroupShow3;
	CTransparentStatic	m_stGroupShow4;
	CTransparentEdit	m_etGroup1;
	CTransparentEdit	m_etGroup2;
	CTransparentEdit	m_etGroup3;
	CTransparentEdit	m_etGroup4;
	CTransparentSwitchButton m_btnSwitchDiscuss;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeetDiscussLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMeetDiscussLogic)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnClickSwitchBtn(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClickEditDel(WPARAM wParam, LPARAM lParam);
	afx_msg	LRESULT OnDragEnd(WPARAM wParam, LPARAM lParam);
//	afx_msg	LRESULT OnDragOver(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	//--- ҳ�滷�� begin ----------------------------------------------------------

	/*=============================================================================
    �� �� ��:InitDlg
    ��    ��:ҳ���������Ϻ��ʼ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2014/02/14  1.0               ����
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
    2014/02/13  1.0               ����
    =============================================================================*/
	void RegisterFun();

	/*=============================================================================
    �� �� ��:InitControlPane
    ��    ��:��ʼ��ҳ��ؼ�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:BOOL
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2014/02/13  1.0               ����
    =============================================================================*/
	virtual BOOL InitControlPane();

	/*=============================================================================
    �� �� ��:HideAllPageCtrl
    ��    ��:�������пؼ�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2014/02/14  1.0               ����
    =============================================================================*/
	void HideAllPageCtrl();

	/*=============================================================================
    �� �� ��:UpdateUIState
    ��    ��:״̬����
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2014/02/14  1.0               ����
    =============================================================================*/
	void UpdateUIState();

	//--- ҳ�滷�� end -------------------------------------------------------------

	//--- �๫������ begin --------------------------------------------------------

	BOOL AddToEpEdit( const CString& strEpName );
	BOOL DelFromEpEdit( const CString& strEpName ); 
	void UpdateDiscussEdit( std::map<u16,CString>& mapDiscussSelItem, BOOL bSwitchDiscuss, EM_OPERATE_FLAG emOperateFlag );

	//--- �๫������ end ----------------------------------------------------------

private:
	BOOL				m_bSwitchDiscuss;
	EM_OPERATE_FLAG		m_emOperateFlag;
	std::map<u16,CString> m_mapDiscussSelItem;       //�洢�������۽��湴ѡ�Ļ᳡

	CRect m_rectGroup1;
	CRect m_rectGroup2;
	CRect m_rectGroup3;
	CRect m_rectGroup4;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEETDISCUSSLOGIC_H__7AB7BD0A_0FBF_4ED9_9FA9_4B32C12093F8__INCLUDED_)
