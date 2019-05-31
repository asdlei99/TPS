/*****************************************************************************
ģ����      : CTvwManageLogic
�ļ���      : tvwmanageLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcweb�û�����ģ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/4/16      1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_TVW_H__1D927FCF_0EC8_445B_9D54_CFEA8B91D70F__INCLUDED_)
#define AFX_TVW_H__1D927FCF_0EC8_445B_9D54_CFEA8B91D70F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// usermanageLogic.h : header file
//
class CTvwManageLogic : public CDlgChild
{
// Construction
public:
	CTvwManageLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTvwManageLogic)
	enum { IDD = IDD_DIALOG_USERMANAGE };
	CTransparentStatic	m_stChildBkRight;
	CTransparentStatic	m_stChildBkLeft;
	CTransparentStatic	m_stUserLeftTitle;
	CTransparentStatic	m_stUserRightTitle;
	CTransparentBtn	    m_btnManage;
    CTransparentBtn	    m_btnBack;
    CTransparentBtn	    m_btnRemoveAll;
    CTransparentBtn	    m_btnDone;
	CTransparentEdit    m_etSearch;
	//}}AFX_DATA


private:
	CListChild* m_plsTvw;
	CLetterIndex* m_pLetterIndex;

    CViewList* m_pTvwView;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTvwManageLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTvwManageLogic)
	virtual BOOL OnInitDialog();	
	afx_msg void OnDestroy();
    afx_msg void OnBtnManage();
    afx_msg void OnBtnDone();
    afx_msg void OnBtnRemoveAll();
    afx_msg void OnBtnBack();
    afx_msg LRESULT OnRefreshConfList( WPARAM wparam, LPARAM lparam );
    afx_msg LRESULT OnRefreshConfCnsList( WPARAM wparam, LPARAM lparam );
	//afx_msg LRESULT OnUpdateConfList( WPARAM wparam, LPARAM lparam );
    afx_msg LRESULT OnHduPlanNty( WPARAM wparam, LPARAM lparam );
    afx_msg	LRESULT OnSearchEditChange(WPARAM wParam, LPARAM lParam);
    afx_msg	LRESULT OnUnSelItemNotify(WPARAM wParam, LPARAM lParam);
    afx_msg	LRESULT OnPlayHduRsp(WPARAM wParam, LPARAM lParam);
    afx_msg	LRESULT OnDragOver(WPARAM wParam, LPARAM lParam);
    afx_msg	LRESULT OnDragLeave(WPARAM wParam, LPARAM lParam);
    afx_msg	LRESULT OnDragEnd(WPARAM wParam, LPARAM lParam);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	/*=============================================================================
    �� �� ��:InitDlg
    ��    ��:ҳ��ע�����Ϻ��ʼ��
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
    2012/04/20  1.0               ����
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
    2012/04/20  1.0               ����
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
    2012/04/20  1.0               ����
    =============================================================================*/
	void SetControlPos();

    
    bool OnClickConfListItem( const IArgs & arg );

    bool OnClickCnsListIcon( const IArgs & arg );

    bool OnClickTvwItem( const IArgs & arg );

    bool OnClickTvwItemIcon( const IArgs & arg );

protected:
    /**
    * ����:	���»����б����
	* @return  ��
	* @remarks
	*/
    void UpdateConfTitle();
    /**
    * ����:	���»᳡�б�
	* @return  ��
	* @remarks
	*/
    void UpdateConfCnsList();

    /**
    * ����:	���᳡�������ǽ��
    * @param [in] wIndex:����ǽ����
    * @param [in] tCnsInfo:�᳡��Ϣ
    * @param [in] bSel: �Ƿ�ֻ����Ϊѡ��
	* @remarks
    * @author  Ф��Ȼ 
    * @date  2013/01/24
	*/
    void SetCnsInTvw( u16 wIndex, TCnsInfo tCnsInfo, BOOL bSel = FALSE );

private:
    CConfCtrlIF* m_pconfCtrlIF;
    CTvwCtrlIF*  m_pTvwCtrlIF;

    //vector<TCmsTvwInfo> m_vctTvwList; 
    vector<TTvwCns> m_vctTvwCnsList;     //����ǽ�б�
    vector<TCMSConf> m_vctCurConfList;   //��ǰ�����б�

    THduPlanData  m_tHduPlanData;        //���е���ǽ����
    TCMSConf      m_tSelConf;            //��ǰѡ�л���
    BOOL          m_bManage;
    BOOL          m_bInCnsList;          //�Ƿ��ڻ᳡�б���
    u16           m_wSelTvwIndex;        //ѡ�е���ǽ����
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TVW_H__1D927FCF_0EC8_445B_9D54_CFEA8B91D70F__INCLUDED_)
