/*****************************************************************************
ģ����      : CMeetTemplateLogic
�ļ���      : meettemplateLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcweb ����ģ�����ù���ģ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/5/22      1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_MEETINGTEMPLATE_H__F51438F9_4139_4D44_BD54_032B7D0600E3__INCLUDED_)
#define AFX_MEETINGTEMPLATE_H__F51438F9_4139_4D44_BD54_032B7D0600E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMeetTemplateLogic.h : header file
//
#include "mediacfglogic.h"
#include "meetdiscusslogic.h"

class CMeetTemplateLogic : public CDlgChild
{
// Construction
public:
	CMeetTemplateLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMeetTemplateLogic)
	enum { IDD = IDD_DIALOG_MEETTEMPLATE };
	CTransparentBtn	m_btnReturn;
	CTransparentEdit	m_edtDotHour;
	CTransparentBtn	m_btnSetTop;
	CTransparentBtn	m_btnSetBottom;
	CTransparentBtn	m_btnRemoveAll;
	CTransparentBtn	m_btnMoveUp;
	CTransparentBtn	m_btnMoveDown;
	CTransparentBtn	m_btnAllAdd;
	CTransparentBtn	m_btnStartConf;
	CTransparentStatic	m_stChildBkRight;
	CTransparentStatic	m_stChildBkLeft;
	CTransparentCheckButton	m_btnCheckCur;
	CTransparentCheckButton	m_btnCheckOrder;
	CTransparentBtn		m_btnSave;
	CTransparentBtn		m_btnCancel;
	CTransparentBtn		m_btnEdit;
	CTransparentEdit	m_etSearch;
	CTransparentBtn		m_btnNewTmp;
	CTransparentBtn		m_btnDelete;
	CTransparentBtn		m_btnAllSel;
	CTransparentStatic	m_stTemplateLeftTitle;
	CTransparentStatic	m_stTemplateRightTitle;
	CTransparentBtn	m_btnMeetingInfo;
	CTransparentBtn	m_btnGroupInfo;
	CTransparentBtn	m_btnPollingInfo;
	CTransparentBtn	m_btnDiscussInfo;
	CTransparentStatic	m_stName;
	CTransparentStatic	m_stNumber;
	CTransparentStatic	m_stTmpType;
	CTransparentStatic	m_stDate;
	CTransparentStatic	m_stStartTime;
	CTransparentStatic	m_stNameShow;
	CTransparentStatic	m_stNumberShow;
	CTransparentStatic	m_stTmpTypeShow;
	CTransparentStatic	m_stDateShow;
	CTransparentStatic	m_stStartTimeShow;
	CTransparentStatic	m_stConfRate;
	CTransparentStatic	m_stConfRateShow;
	CTransparentStatic	m_stConfRateUnit;
	CTransparentEdit	m_etConfRate;
	CTransparentStatic	m_stShowRate;
	CTransparentStatic	m_stShowRateShow;
	CTransparentStatic	m_stShowRateUnit;
	CTransparentEdit	m_etShowRate;
	CTransparentEdit	m_etName;
	CTransparentEdit	m_etNumber;	
	CTransparentEdit	m_etSetHour;
	CTransparentEdit	m_etSetMin;
	CTransparentBtn		m_btnCurrentMeet;
	CTransparentBtn		m_btnOrderMeet;
	CTransparentCheckButton		m_btnCalendar;
	CTransparentBtn		m_btnPlusTime;
	CTransparentBtn		m_btnSubTime;
	CTransparentEdit	m_etDateSet;
	CTransparentStatic	m_stIntervel;
	CTransparentStatic	m_stPollingSecond;
	CTransparentEdit	m_etPollingTime;
	CTransparentBtn		m_btnSubPollingTime;
	CTransparentBtn		m_btnPlusPollingTime;
	CTransparentStatic	m_stHomeMeeting;
	CTransparentEdit	m_etHomeMeeting;
	CTransparentStatic	m_stMediaInfo;
	CTransparentEdit	m_etAdaptRes;
	CTransparentBtn		m_btnMediaInfo;
	CTransparentBtn		m_btnSubConfRate;
	CTransparentBtn		m_btnPlusConfRate;
	CTransparentBtn		m_btnSubShowRate;
	CTransparentBtn		m_btnPlusShowRate;
	CTransparentSwitchButton m_btnSwitchPolling;
	//}}AFX_DATA

private:                                //�ؼ�Ԫ��
	CListChild* m_plsMeetTmp;
	CListChild* m_plsMeetEpRight;
	CListChild* m_plsMeetPollingRight;
	CListChild* m_plsLocalAddrbook;
	CListChild* m_plsPollingLeft;
	CListChild* m_plsDiscussLeft;
	
	CLetterIndex* m_pLetterTmp;
	CLetterIndex* m_pLetterAddrbook;
	CLetterIndex* m_pLetterPolling;
	CLetterIndex* m_pLetterDiscuss;

	CMediaCfgLogic m_dlgMediaCfg;
	CMeetDiscussLogic m_dlgMeetDiscuss;

public:
	CCalendarDlg m_dlgCalendar;         //����������������� 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeetTemplateLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMeetTemplateLogic)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnNew();
	afx_msg void OnBtnDelete();
	afx_msg void OnBtnEdit();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnCancel();
	afx_msg void OnBtnAllSelect();
	afx_msg void OnBtnMeetingInfo();
	afx_msg void OnBtnEpInfo();
	afx_msg void OnBtnPollingInfo();
	afx_msg void OnBtnDiscussInfo();
	afx_msg void OnBtnPlusTime();
	afx_msg void OnBtnSubTime();
	afx_msg LRESULT OnTmpListOperateResult(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT UpdateGroupEpList( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT UpdatePollingList( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnRefreshAddrListListNotify(WPARAM wParam, LPARAM lParam); 
	afx_msg LRESULT OnRefreshTmpListNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnStartConfResult(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnConfTmpResUsedCountNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDelAllConftempRet(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnBtnCalendar();
	afx_msg void OnBtnCheckOrderConf();
	afx_msg void OnBtnCheckCurConf();
	afx_msg void OnBtnStartConf();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg LRESULT OnNoSelResultNotify(WPARAM wParam, LPARAM lParam);        //δѡ���κ��û��б�֪ͨ
	afx_msg LRESULT OnUpdateCalendarSelDate(WPARAM wParam, LPARAM lParam);    //����ѡ��ʱ��
	afx_msg LRESULT OnDiscussEpChange(WPARAM wParam, LPARAM lParam);		  //�������۵Ļ᳡�ı�
	afx_msg LRESULT OnSwitchDiscuss(WPARAM wParam, LPARAM lParam);			  //����/�رջ�������
	afx_msg void OnBtnAllAdd();
	afx_msg void OnBtnSetTop();
	afx_msg void OnBtnSetBottom();
	afx_msg void OnBtnRemoveAll();
	afx_msg void OnBtnMediaInfo();
	afx_msg void OnBtnMoveUp();
	afx_msg void OnBtnMoveDown();
	afx_msg	void OnSearchEditChange();
	afx_msg HRESULT OnHideWndNotify( WPARAM wparam, LPARAM lparam );
    afx_msg HRESULT OnBtnHold( WPARAM wparam, LPARAM lparam );
    afx_msg HRESULT OnBtnHoldEnd( WPARAM wparam, LPARAM lparam );
	afx_msg void OnSetfocusEditHour();
	afx_msg void OnSetfocusEditMinute();
	afx_msg void OnBtnReturn();
	afx_msg void OnBtnSubConfRate();
	afx_msg void OnBtnPlusConfRate();
	afx_msg void OnBtnSubShowRate();
	afx_msg void OnBtnPlusShowRate();
	afx_msg void OnBtnSubPollingTime();
	afx_msg void OnBtnPlusPollingTime();
	afx_msg LRESULT OnClickSwitchBtn(WPARAM wParam, LPARAM lParam);
	afx_msg	void OnConfRateEditChange();
	afx_msg	void OnShowRateEditChange();
    afx_msg	LRESULT OnDragEnd(WPARAM wParam, LPARAM lParam);
	afx_msg	LRESULT OnEditSetFocus(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnKillFoucs(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUmsReasonInd(WPARAM wParam, LPARAM lParam);
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
    �� �� ��:CreatePageControls
    ��    ��:����ҳ�������ȫ���ؼ�����
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/05/12  1.0     ����ӡ    ����
    =============================================================================*/
	BOOL CreatePageControls();

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
	BOOL InitMeetInfoPageControl();	    //������Ϣҳ�� 
	BOOL InitMeetEpPageControl();		//�᳡��Ϣҳ��
	BOOL InitMeetPollingPageControl();	//�᳡��ѯ��Ϣҳ��
	BOOL InitMeetDiscussPageControl();  //��������ҳ��

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
    �� �� ��:GetLibPtr
    ��    ��:�õ���ǰҳ������umslib�ӿ�ָ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/10  1.0     ����ӡ    ����
    =============================================================================*/
	void GetLibPtr();

	/*=============================================================================
    �� �� ��:ShowPageScanf ShowPageEdit ShowPageNew
    ��    ��:������༭���½�״̬ҳ��ؼ���ʾ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/05/16  1.0     ����ӡ    ����
    =============================================================================*/
	void ShowPageScanf();
	void ShowPageEdit();
	void ShowPageNew();
	void ShowMeetInfoScanfPage(BOOL bShow);				   //��ʾ������Ϣ���ҳ��   ý��ҳ����ʾ���ؿ���
	void ShowMeetInfoEditPage(BOOL bShow);				   //��ʾ������Ϣ�½����༭ҳ��   ý��ҳ����ʾ���ؿ���


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
    �� �� ��:ResetInitPage
    ��    ��:���ý���ؼ�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/08  1.0     ����ӡ    ����
    =============================================================================*/
	void ResetInitPage();

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
	void ShowSortControl(BOOL bShow);       //����ؼ���ʾ
	void UpdateSortControlUIState();
	void SetSortControlDisable();           //�޵�ǰѡ���б�����ʾ��ֹ

	void ResetSerchEditLen();				//���ò�ѯ��Ĵ�С
	void SetAddrbookSerchEditLen();			//���õ�ַ����ѯ��λ��
	void SetPollingLeftviewSerchEditLen();  //������ѯ�����ͼ�Ĳ�ѯ��λ��

	void SetMediaInfoBtnPos(BOOL bDefaut = TRUE);  //��̬����ý��ؼ�λ��
	void SetMediaInfoBtnHide(BOOL bHide = TRUE);   //����ý��ؼ���ʾ����
	void SetMediaCfgHide(BOOL bHide = TRUE);	   //����ý������ҳ����ʾ����

	void SetRateInfoPos(BOOL bDefaut = TRUE);      //��̬�������ʿؼ�λ��
	void SetRateInfoHide(BOOL bHide = TRUE);       //�������ʿؼ���ʾ����

//	void UpdatePollingUIState();			       //������ѯ����ؼ�״̬����

	//--- ҳ�滷�� end -------------------------------------------------------------


	//--- ������ begin -------------------------------------------------------------

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
    �� �� ��:UpdateAddrbookShowList
    ��    ��:�б�����ʾ��ַ����Ϣ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/05/26  1.0     ����ӡ    ����
    =============================================================================*/
	void UpdateAddrbookShowList();

	/*=============================================================================
    �� �� ��:UpdateTmpShowList
    ��    ��:����ģ��չ��ͳһ�ӿ�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/06/28  1.0     ����ӡ    ����
    =============================================================================*/
	void UpdateTmpShowList();

	/*=============================================================================
    �� �� ��:UpdatePollingLeftShowList
    ��    ��:��ѯ����б�չ��ͳһ�ӿ�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/06/28  1.0     ����ӡ    ����
    =============================================================================*/
	void UpdatePollingLeftShowList( std::map<u16,CString>& mapEpList, BOOL bIsShowIcon );

	void UpdatePollingLeftIcon();

	/*=============================================================================
    �� �� ��:UpdateDiscussLeftShowList
    ��    ��:������������б�չ��ͳһ�ӿ�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2014/02/18  1.0     �컪��    ����
    =============================================================================*/
	void UpdateDiscussLeftShowList( std::map<u16,CString>& mapEpList, BOOL bIsShowIcon );

	/*=============================================================================
    �� �� ��:UpPollCns DownPollCns TopPollCns BottomPollCns
    ��    ��:��ѯ�б��������
    ��    ��:wCurRow                          [in]   ��ǰ�����
    ע    ��:��
    �� �� ֵ:u16���سɹ���־
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/20  1.0     ����ӡ    ����
    =============================================================================*/
	u16 UpPollControl( u16 wCurRow );
	u16 DownPollControl( u16 wCurRow);
	u16 TopPollControl( u16 wCurRow );
	u16 BottomPollControl( u16 wCurRow );

	//��� �༭ �½� ҳ��ؼ����ݸ�ֵ
	void SetSelectedTmpDataToScanfPage(const TTPConfTemplate& tConfTmplate);
	void SetSelectedTmpDataToEditPage();
	void SetInitDataToNewPage();

	//�᳡�б���ѵ�б����������б�ֵ
	void SetEpListPageToEditPage(const TTPConfTemplate& tSelConfTmplate);
	void SetTurnListPageToEditPage(const TTPConfTemplate& tSelConfTmplate);
	void SetDiscussListPageToEditPage(const TTPConfTemplate& tSelTemplate);
	void CleanPageList();           //����б�����᳡�б����ѯ�б�

	void FilterAddrbookList();
	void FilterPollingLeftList();    //��ʾ��ѯ��ѯ����б�����
	void FilterDiscussLeftList();    //��ʾ��ѯ������������б�����

	//--- ������ end -------------------------------------------------------------


	//--- �б����¼� begin -----------------------------------------------------

	/*=============================================================================
    �� �� ��:OnClickTmpLstItem
    ��    ��:ģ���б����¼�
    ��    ��:const IArgs & arg                          [in]    ���value
    ע    ��:��
    �� �� ֵ:bool�ɹ�ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/20  1.0     ����ӡ    ����
    =============================================================================*/
	bool OnClickTmpLstItem( const IArgs & arg );
    bool OnClickTmpLstItemIcon( const IArgs & arg );

	/*=============================================================================
    �� �� ��:OnClickAddrbookLstItem
    ��    ��:��ַ���б����¼�
    ��    ��:const IArgs & arg                          [in]    ���value
    ע    ��:��
    �� �� ֵ:bool�ɹ�ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/20  1.0     ����ӡ    ����
    =============================================================================*/
	bool OnClickAddrbookLstItem( const IArgs & arg );
    bool OnClickAddrbookLstItemIcon( const IArgs & arg );

	/*=============================================================================
    �� �� ��:OnClickPollingPageLeftLstItem
    ��    ��:��ѵҳ������б����¼�
    ��    ��:const IArgs & arg                          [in]    ���value
    ע    ��:��
    �� �� ֵ:bool�ɹ�ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/20  1.0     ����ӡ    ����
    =============================================================================*/
	bool OnClickPollingPageLeftLstItem( const IArgs & arg );
    bool OnClickPollingPageLeftLstItemIcon( const IArgs & arg );

	/*=============================================================================
    �� �� ��:OnClickGroupPageDelItemIcon
    ��    ��:�᳡�б���ɾ���¼�
    ��    ��:const IArgs & arg                          [in]    ���value
    ע    ��:��
    �� �� ֵ:bool�ɹ�ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/20  1.0     ����ӡ    ����
    =============================================================================*/
    bool OnClickGroupPageDelItemIcon( const IArgs & arg );

	/*=============================================================================
    �� �� ��:OnClickPollingPageDelItem
    ��    ��:��ѵ�б���ɾ���¼�
    ��    ��:const IArgs & arg                          [in]    ���value
    ע    ��:��
    �� �� ֵ:bool�ɹ�ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/20  1.0     ����ӡ    ����
    =============================================================================*/
	bool OnClickPollingPageDelItem( const IArgs & arg );
    bool OnClickPollingPageDelItemIcon( const IArgs & arg );

	/*=============================================================================
    �� �� ��:OnClickDiscussPageLeftLstItem
    ��    ��:��������ҳ������б����¼�
    ��    ��:const IArgs & arg                          [in]    ���value
    ע    ��:��
    �� �� ֵ:bool�ɹ�ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2014/02/18  1.0     �컪��    ����
    =============================================================================*/
	bool OnClickDiscussPageLeftLstItem( const IArgs & arg );
    bool OnClickDiscussPageLeftLstItemIcon( const IArgs & arg );

	//--- �б����¼� end --------------------------------------------------------

	//--- �๫������ begin --------------------------------------------------------

	CString FindConfTurnListById(u16 nId);						         //ͨ����ѯid�ڻ᳡�б���ƥ��᳡����
	u16  FindConfTurnListByAlias(CString strTurnListName);		         //ͨ����ѯ�б������ڻ����б���ƥ��id
	CString FindConfDiscussListById(u16 nId);						     //ͨ�����ۻ᳡id�����᳡�б���ƥ��᳡����
	u16  FindConfDiscussListByAlias(CString strDiscussListName);		 //ͨ�������б����������᳡�б���ƥ��id
	BOOL CheckTmpMeetInfo();									         //��������Ϣҳ������
	BOOL CheckIsInputHomeMeeting();								         //������᳡��Ϣ�Ƿ�����
//	BOOL HomeMeetExistInEpList(const CString& strHomeMeetName);          //������᳡�Ƿ��Ѿ����ڷֻ᳡ 
	u16 FindMeetInEpList(const CString& strMeetName, const CString& strMeetNum, BOOL bHomeMeet = FALSE); //���Ҵ˻᳡�ڷֻ᳡�е�id
	void ReSetCnsEpId(u16 uDelPos);                                      //���÷ֻ᳡ID
	void CleanSearchList();                                              //������ͼ���ò�ѯ��   �����л���ͼ  ����б�
	TTPConfTemplate* GetConfTemplateByID( u16 wConfTemplateID ) const ;	 //���ݻ���ID��ȡ����ģ��ָ�� 
	BOOL AddToEpList( const CString& strAddrbookName, const CString& strAddrbookNum, BOOL bIsHomeConfChec = TRUE ); 
	void UpdateResUsedCountToControl( u16 wResNum );                     //������Դռ�����
	void UpdateDiscussShowListData();								     //���»�����������б�����(���᳡+�ֻ᳡)
	void UpdateGroupEpInfoList(const CString& strAddrbookName, const CString& strAddrbookNum, u16 wEpID); //����m_mapEpInfoList����

	bool ClickAddrbookLstItemIcon( const Data_AddrItemInfo *pItemInfo );
	bool ClickPollingPageLeftLstItemIcon( const Data_CnsAddr *pItemInfo );

	void UpdateSearchEdtStatus();											 //���²�ѯ�༭��״̬

	//--- �๫������ begin --------------------------------------------------------
private:
	CConfCtrlIF* m_pconfCtrlIF;             //������ƽӿ�
	CConfTemplateCtrlIF* m_tTmpConfigIF;    //ģ����ƽӿ� 
	CCncAddrbookIF*  m_pAddrBookIF;         //��ַ���ӿ�
	CUmsConfigCtrlIF *m_pUmsConfig;
	
	TCMSConfTemplate m_tNewTemplate;        //��ǰ����½�ģ��
	TCMSConfTemplate m_tSelTemplate;        //��ǰ���ѡ��ģ��

	TCMSConfTemplate  m_tBaseTemplate;		//ԭʼѡ��ģ��ý����Ϣ

	EM_OPERATE_FLAG m_emOperateFlag;        //��ǰ����״̬  �༭ �½� ���
	EM_CURRENT_TABPAGE m_emTabFlag;         //��ǰ���ҳ��  ������Ϣ  �᳡��Ϣ   ��ѯ��Ϣ

	BOOL m_bIsAllSel;
	s32  m_nCurPollingListSortRow;          //��ǰ�����ѯ�к�  ���������ʹ��
	s32  m_nTurnLeftListCount;              //��ѯ���¼��ѯ�б����Ŀ��   ���ڿ���ȫ����Ӱ�ť״̬

	EM_CURRENT_FOCUS     m_emCurFocus;

	//��������
	TplArray<TTPConfTemplate> m_tpTmpRefreshList;    //����ģ��ˢ���б�
	TplArray<TTPConfTemplate> m_tpTmpShowList;       //����ģ��չ���б�
	TplArray<TTPConfTemplate> m_tpTmpSearchList;     //����ģ���ѯ�б�

	vector<TAddrItem> m_vecLocalbookRefreshList;     //���ص�ַ��ˢ���б�
	vector<TAddrItem> m_vecLocalbookShowList;		 //���ص�ַ��չ���б�
	vector<TAddrItem> m_vecLocalbookSearchList;		 //���ص�ַ����ѯ�б�

	std::map<u16,CString> m_mapEpList;               //�洢��ǰ����л��½�ģ��Ļ᳡�б�   �½����༭״̬��ʹ��   id��Ϊɾ������ʱ��ʹ��        
	std::map<u16,CString> m_mapEpSearchList;  
	std::vector<CString> m_vecTurnList;              //�洢��ǰ����л��½�ģ�����ѯ�б�  �½�״̬���༭��ʹ��
	std::set<CString> m_setSelectedTmpIconItem;      //�洢��ǰ�����ѡ��ģ��set��
	u16 m_wResUsedCount;                             //��ǰ��Դ��
	std::map<u16,TEpAddr> m_mapEpInfoList;           //�洢��ǰ����л��½�ģ��Ļ᳡�б�(�����᳡e164��ip)   �½����༭״̬��ʹ��   ��������ums��������ʱʹ��

	//��������
	std::map<u16,CString> m_mapDiscussList;          //�洢�������۽�������б�����
	std::map<u16,CString> m_mapDiscussSearchList;    //�������۽�������б��ѯ����
	std::map<u16,CString> m_mapDiscussSelItem;       //�洢�������۽��湴ѡ�Ļ᳡

	BOOL m_bSwitchPolling;							 //�Ƿ���������ѯ
	BOOL m_bSwitchDiscuss;							 //�Ƿ�����������
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEETINGTEMPLATE_H__F51438F9_4139_4D44_BD54_032B7D0600E3__INCLUDED_)
