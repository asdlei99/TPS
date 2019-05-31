/*****************************************************************************
ģ����      : CMeetinfoLogic
�ļ���      : meetinfoLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcweb ������Ϣģ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/5/28      1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_MEETINGLIST_H__ABC3C588_3E7D_40D7_987D_87B6C0BB8B54__INCLUDED_)
#define AFX_MEETINGLIST_H__ABC3C588_3E7D_40D7_987D_87B6C0BB8B54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// meetinfoLogic.h : header file//

#include "Menubar.h"
class CMeetinfoLogic : public CDlgChild
{
// Construction
public:
	CMeetinfoLogic(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CMeetinfoLogic)
	enum { IDD = IDD_DIALOG_MEETINFO };
	CTransparentCheckButton	    m_btnCheckMenu;
	CTransparentStatic	m_stCurMeetTitle;
	CTransparentStatic	m_stOrderMeetTitle;
	CTransparentStatic	m_stChildBkBottom;
	CTransparentStatic	m_stChildBkUp;
	CTransparentStatic	m_stLeftTitle;	
	CTransparentEdit	m_etSearch;
	CTransparentBtn	    m_btnAllSel;
	CTransparentBtn	    m_btnCloseMeeting;
	//}}AFX_DATA

private:
	CListChild* m_plsCurMeet;
	CListChild* m_plsOrderMeet;
	CLetterIndex* m_pLetterIndex;

public:
	CMenubar m_dlgMenubar;                        //�˵�Dlg    �ṩ����������

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeetinfoLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMeetinfoLogic)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAllSelect();
	afx_msg void OnBtnCloseMeeting();
	afx_msg LRESULT OnRefreshTmpList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRefreshConfList( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnUpdateConfList( WPARAM wparam, LPARAM lparam );
	afx_msg LRESULT OnHungupConfReason( WPARAM wparam, LPARAM lparam );
	afx_msg void OnDestroy();
	afx_msg void OnBtnCheckMenu();
	afx_msg LRESULT OnClickMeetListMenuUpdate( WPARAM wParam, LPARAM lParam );
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg LRESULT OnStartConfResult(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg	void OnSearchEditChange();
	afx_msg HRESULT OnHideAUtoHideWnd( WPARAM wparam, LPARAM lparam );
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
    2012/05/19  1.0               ����
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
    2012/05/19  1.0     ����ӡ    ����
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
    2012/05/19  1.0     ����ӡ    ����
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
    2012/05/28  1.0     ����ӡ    ����
    =============================================================================*/
	void SetControlPos();

	/*=============================================================================
    �� �� ��:SelectMeetListView
    ��    ��:ѡ��ǰList��ͼ
    ��    ��:EM_MENU_MEETTYPE emMenuType    [in]    ��ǰ��ͼ����
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/05/16  1.0     ����ӡ    ����
    =============================================================================*/
	void SelectMeetListView(EM_MENU_MEETTYPE emMenuType);

	/*=============================================================================
    �� �� ��:UserListRefresh
    ��    ��:ˢ�µ�ǰ�����б�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/05/26  1.0     ����ӡ    ����
    =============================================================================*/
	void CurMeetListRefresh();

	/*=============================================================================
    �� �� ��:MeetTmpRefresh
    ��    ��:ˢ�»���ģ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/05/26  1.0     ����ӡ    ����
    =============================================================================*/
	void MeetTmpRefresh();

	/*=============================================================================
    �� �� ��:GetTemplateById
    ��    ��:ͨ��ID����ģ��
    ��    ��:u16 nTmplateId                          [in]    ģ��ID
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/05/26  1.0     ����ӡ    ����
    =============================================================================*/
	TTPConfTemplate* GetTemplateById(u16 nTmplateId);

	/*=============================================================================
    �� �� ��:OnClickCurMeetLstItem
    ��    ��:��ǰ�����б����¼�
    ��    ��:const IArgs & arg                          [in]    ���value
    ע    ��:��
    �� �� ֵ:bool�ɹ�ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/05/29  1.0     ����ӡ    ����
    =============================================================================*/
	bool OnClickCurMeetLstItem( const IArgs & arg );
    bool OnClickCurMeetLstItemIcon( const IArgs & arg );

	/*=============================================================================
    �� �� ��:OnClickOrderMeetLstItem
    ��    ��:ԤԼ�����б����¼�
    ��    ��:const IArgs & arg                          [in]    ���value
    ע    ��:��
    �� �� ֵ:bool�ɹ�ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/05/29  1.0     ����ӡ    ����
    =============================================================================*/
	bool OnClickOrderMeetLstItem( const IArgs & arg );
    bool OnClickOrderMeetLstItemIcon( const IArgs & arg );

	
	/*=============================================================================
    �� �� ��:UpdateShowList
    ��    ��:�����б�չ��ͳһ�ӿ�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/20  1.0     ����ӡ    ����
    =============================================================================*/
	void UpdateCurConfShowList();
	void UpdateOrderConfShowList();

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

	void SetConfExist( BOOL bConfExist ){ m_bConfExist = bConfExist;};
	BOOL GetConfExist(){ return m_bConfExist;};

	CString FindConfNameById(u16 wConfId);

private:
	CConfCtrlIF* m_pconfCtrlIF;
	CConfTemplateCtrlIF* m_tTmpConfigIF;

	std::set<u16> m_setCurConfSelectedIconItem;    //��ǰ���鼯��
	std::set<u16> m_setOrderConfSelectedIconItem;  //ԤԼ���鼯��

	BOOL m_bIsAllSel;							   //�Ƿ�ȫѡ
	EM_MENU_MEETTYPE m_emCurPageMeetType;          //��ǰҳ����ʾ����
	TCMSConfTemplate* m_pTCurCloseMeetTmp;         //��ǰ���ģ��

	//��������
	TplArray<TCMSConfTemplate> m_tpOrderConfRefreshList;    //ԤԼ����ˢ���б�
	TplArray<TCMSConfTemplate> m_tpOrderConflShowList;      //ԤԼ����չ���б�
	TplArray<TCMSConfTemplate> m_tpOrderConfSearchList;     //ԤԼ�����ѯ�б�

	ARRAY<TCMSConf> m_vecCurConfRefreshList;    //��ǰ����ˢ���б�
	ARRAY<TCMSConf> m_vecCurConflShowList;      //��ǰ����չ���б�
	ARRAY<TCMSConf> m_vecCurConfSearchList;     //��ǰ�����ѯ�б�

	BOOL m_bConfExist;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEETINGLIST_H__ABC3C588_3E7D_40D7_987D_87B6C0BB8B54__INCLUDED_)
