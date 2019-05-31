/*****************************************************************************
ģ����      : CMediaCfgLogic
�ļ���      : mediacfglogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcweb ý������ҳ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/2/20      1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_MEDIACFGLOGIC_H__737F35D3_454D_401B_A515_7D37F9F58671__INCLUDED_)
#define AFX_MEDIACFGLOGIC_H__737F35D3_454D_401B_A515_7D37F9F58671__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// mediacfglogic.h : header file
//

//ý����Ϣҳ��    �����ʽ   ��ʾ��ʽ
enum EM_MEDIA_CURRENT_TABPAGE
{
	em_CONFFORMAT_PAGE = 0,
	em_SHOWFORMAT_PAGE,
	em_AUDIOFORMAT_PAGE
};

const float VICP1080p50or60f = 1.00f;
const float VICP1080p25or30f = 0.5f;
const float VICP720p50or60f = 0.44f;
const float VICP720p25or30f = 0.22f;
const float VICPWXGAp30f = 0.25f;
const float VICPWXGAp5f = 0.04f;
const float VICPUXGAp60f = 0.93f;
const float VICPSXGAp30f = 0.32f;
const float VICPSXGAp5f = 0.05f;
const float VICP4CIFp25f = 0.08f;
const float VICPXGAp5f = 0.032f;

/////////////////////////////////////////////////////////////////////////////
// CMediaCfgLogic dialog
class CMediaCfgLogic : public CDlgChild
{
// Construction
public:
	CMediaCfgLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMediaCfgLogic)
	enum { IDD = IDD_DIALOG_MEDIAICFG };
	CTransparentStatic	m_stMediaInfo;

	CTransparentBtn	m_btnConfFormat;
	CTransparentBtn	m_btnShowFormat;
	CTransparentBtn m_btnAudioFormat;

	CTransparentCheckButton		m_btnHP1080P5060F;
	CTransparentCheckButton		m_btnHP1080P2530F;

	CTransparentCheckButton		m_btnHP720P5060F;
	CTransparentCheckButton		m_btnHP720P2530F;
	
	CTransparentCheckButton		m_btnBP1080P5060F;
	CTransparentCheckButton		m_btnBP1080P2530F;
	
	CTransparentCheckButton		m_btnBP720P5060F;
	CTransparentCheckButton		m_btnBP720P2530F;

	CTransparentCheckButton		m_btnBP4CIFP25F;

	CTransparentCheckButton		m_btnBPUXGAP60F;
	CTransparentCheckButton		m_btnBPWXGAP30F;
	CTransparentCheckButton		m_btnBPSXGAP30F;

	CTransparentCheckButton		m_btnBPWXGAP5F;
	CTransparentCheckButton		m_btnBPSXGAP5F;
	CTransparentCheckButton		m_btnBPXGAP5F;

	CTransparentCheckButton		m_radiobtnMpegAACLD;
	CTransparentCheckButton		m_radiobtnG711A;
	CTransparentCheckButton		m_radiobtnG711U;
	CTransparentCheckButton		m_radiobtnG719;
	CTransparentCheckButton		m_radiobtnG7221;
	CTransparentCheckButton		m_radiobtnMP3;
	CTransparentCheckButton		m_radiobtnMpegAACLC;

	CTransparentStatic	m_stAdaptRes;
	CTransparentStatic  m_stAllRes;
	CTransparentStatic	m_stResCount;
	CTransparentStatic	m_stAllAdaptResCount;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMediaCfgLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMediaCfgLogic)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBtnConfFormat();
	afx_msg void OnBtnShowFormat();
	afx_msg void OnBtnAudioFormat();

	afx_msg void OnBtnHP1080P5060F();
	afx_msg void OnBtnHP1080P2530F();

	afx_msg void OnBtnHP720P5060F();
	afx_msg void OnBtnHP720P2530F();
		
	afx_msg void OnBtnBP1080P5060F();
	afx_msg void OnBtnBP1080P2530F();
		
	afx_msg void OnBtnBP720P5060F();
	afx_msg void OnBtnBP720P2530F();

	afx_msg void OnBtnBP4CIFP25F();

	afx_msg void OnBtnBPUXGAP60F();
	afx_msg void OnBtnBPWXGAP30F();
	afx_msg void OnBtnBPSXGAP30F();

	afx_msg void OnBtnBPWXGAP5F();
	afx_msg void OnBtnBPSXGAP5F();
	afx_msg void OnBtnBPXGAP5F();

	afx_msg void OnRadioBtnMpegAACLD();
	afx_msg void OnRadioBtnG711A();
	afx_msg void OnRadioBtnG711U();
	afx_msg void OnRadioBtnG719();
	afx_msg void OnRadioBtnG7221();
	afx_msg void OnRadioBtnMP3();
	afx_msg void OnRadioBtnMpegAACLC();

	afx_msg LRESULT OnSendTmpInfoToPage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnConfTmpResUsedCountNotify(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	/*=============================================================================
    �� �� ��:RegisterFun
    ��    ��:List�������ע��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2013/02/22  1.0     ����ӡ    ����
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
    2012/02/20  1.0     ����ӡ    ����
    =============================================================================*/
	virtual BOOL InitControlPane();

	BOOL InitFormatPageControl();   //��ʼ�� ����/��ʾ ��ʽҳ��ؼ�
	BOOL InitAudioPageControl();    //��ʼ����Ƶ��ʽҳ��ؼ�

	TCMSConfTemplate* GetSelTemplate()
	{ 
		return &m_tSelTemplate;
	};

	u16 GetCheckResNum(){return m_wCheckResNum;};                        //�õ���ǰѡ�����Դ����
		
	void UpdateResUsedCountToControl( u16 wResNum );                     //������Դռ�����

// 	TCMSConfTemplate* GetBaseSelTemplate(){ return m_tBaseTemplate;};
// 	void SetBaseSelTemplate(){ return m_pTSelTemplate;};

private:
	/*=============================================================================
    �� �� ��:CountVideoResNum
    ��    ��:������ѡ��Ƶ��Դռ�����
    ��    ��:��
    ע    ��:��
    �� �� ֵ:u16  ռ����Դ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/02/20  1.0     ����ӡ    ����
    =============================================================================*/
	void CountVideoResNum();

	/*=============================================================================
    �� �� ��:CountVICPValueSum
    ��    ��:���㹴ѡ�ĸ�ʽ��ռ�õ�VICPֵ�ܺ�(���ɳ���3)
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2014/03/06  1.0     �컪��    ����
    =============================================================================*/
	void CountVICPValueSum();

	/*=============================================================================
    �� �� ��:EnableMinorMaxCheckBtn
    ��    ��:�ûҸ���Ƶδ��ѡ��ʽ�в���ѡ�ĸ�ʽ
    ��    ��:float fLastVICPValue
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2014/03/06  1.0     �컪��    ����
    =============================================================================*/
	void EnableMinorUnableCheckBtn( float fLastVICPValue );

	/*=============================================================================
    �� �� ��:EnableVedioCheckBtn
    ��    ��:��������Ƶ��ť״̬
    ��    ��:BOOL bEnable
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/02/20  1.0     ����ӡ    ����
    =============================================================================*/
	void EnableMainCheckBtn(BOOL bEnable);

	/*=============================================================================
    �� �� ��:EnableVedioCheckBtn
    ��    ��:���ø���Ƶ��ť״̬
    ��    ��:BOOL bEnable
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/02/20  1.0     ����ӡ    ����
    =============================================================================*/
	void EnableMinorCheckBtn(BOOL bEnable);

	/*=============================================================================
    �� �� ��:EnableMainMaxCheckBtn
    ��    ��:��ѡ�������Ƶ��ʽ����6   �����û�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2014/02/18  1.0     �컪��    ����
    =============================================================================*/
	void EnableMainMaxCheckBtn();

	/*=============================================================================
    �� �� ��:EnableMinorMaxCheckBtn
    ��    ��:��ѡ��ĸ�����Ƶ��ʽ����6   �����û�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/02/20  1.0     ����ӡ    ����
    =============================================================================*/
	void EnableMinorMaxCheckBtn();

	/*=============================================================================
    �� �� ��:EnableAudioRadioBtn
    ��    ��:������Ƶ��ʽ����״̬
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2014/02/25  1.0     �컪��    ����
    =============================================================================*/
	void EnableAudioRadioBtn(BOOL bEnable);

	/*=============================================================================
    �� �� ��:SetMainVideoBtnStatus
    ��    ��:������������Ƶ��ʽ��ť����ʾ״̬
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/02/20  1.0     ����ӡ    ����
    =============================================================================*/
	void SetMainVideoBtnStatus(const TUmsVidFormat& tTpMainVideoRes);
	void SetMinorVideoBtnStatus(const TUmsVidFormat& tTpMinorVideoRes);

	/*=============================================================================
    �� �� ��:SetConfFormatHide
    ��    ��:���ػ����ʽ���水��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2014/02/25  1.0     �컪��    ����
    =============================================================================*/
	void SetConfFormatHide( BOOL bHide = TRUE );
	void SetShowFormatExHide( BOOL bHide = TRUE );
	void SetAudioFormatHide( BOOL bHide = TRUE );

	/*=============================================================================
    �� �� ��:UpdateVedioControl
    ��    ��:��������������ؼ�״̬
    ��    ��:TCMSConfTemplate* pTTemplate    ����ģ������
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/02/20  1.0     ����ӡ    ����
    =============================================================================*/
	void UpdateVedioControl(TCMSConfTemplate* pTTemplate);

	void UpdateAudioControl(TCMSConfTemplate* pTTemplate);

	/*=============================================================================
    �� �� ��:ShowMediaFormat
    ��    ��:��ʾý���ʽ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2014/02/25  1.0     �컪��    ����
    =============================================================================*/
	void ShowMediaFormat();

private:
	EM_OPERATE_FLAG m_emOperateFlag;				//��ǰ����״̬  �༭ �½� ���
	TCMSConfTemplate m_tSelTemplate;				//��ǰ���ģ��	
	//TCMSConfTemplate  m_tBaseTemplate;			//ԭʼѡ��ģ��ý����Ϣ
	u16 m_wCheckResNum;                             //��ǰѡ����Դ����

	u16 m_wMainCheckCount;
	u16 m_wMinorCheckCount;

	u16 m_wAllResCount;
	EM_MEDIA_CURRENT_TABPAGE m_emTabFlag;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDIACFGLOGIC_H__737F35D3_454D_401B_A515_7D37F9F58671__INCLUDED_)
