/*****************************************************************************
模块名      : CMediaCfgLogic
文件名      : mediacfglogic.h
相关文件    : 
文件实现功能: umcweb 媒体配置页面
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/2/20      1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_MEDIACFGLOGIC_H__737F35D3_454D_401B_A515_7D37F9F58671__INCLUDED_)
#define AFX_MEDIACFGLOGIC_H__737F35D3_454D_401B_A515_7D37F9F58671__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// mediacfglogic.h : header file
//

//媒体信息页面    会议格式   演示格式
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
    函 数 名:RegisterFun
    功    能:List点击函数注册
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2013/02/22  1.0     刘德印    创建
    =============================================================================*/
	void RegisterFun();

	/*=============================================================================
    函 数 名:InitControlPane
    功    能:初始化页面控件
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/02/20  1.0     刘德印    创建
    =============================================================================*/
	virtual BOOL InitControlPane();

	BOOL InitFormatPageControl();   //初始化 会议/演示 格式页面控件
	BOOL InitAudioPageControl();    //初始化音频格式页面控件

	TCMSConfTemplate* GetSelTemplate()
	{ 
		return &m_tSelTemplate;
	};

	u16 GetCheckResNum(){return m_wCheckResNum;};                        //得到当前选择的资源总数
		
	void UpdateResUsedCountToControl( u16 wResNum );                     //更新资源占用情况

// 	TCMSConfTemplate* GetBaseSelTemplate(){ return m_tBaseTemplate;};
// 	void SetBaseSelTemplate(){ return m_pTSelTemplate;};

private:
	/*=============================================================================
    函 数 名:CountVideoResNum
    功    能:计算所选视频资源占用情况
    参    数:无
    注    意:无
    返 回 值:u16  占用资源数
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/02/20  1.0     刘德印    创建
    =============================================================================*/
	void CountVideoResNum();

	/*=============================================================================
    函 数 名:CountVICPValueSum
    功    能:计算勾选的格式所占用的VICP值总和(不可超过3)
    参    数:无
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2014/03/06  1.0     徐华秀    创建
    =============================================================================*/
	void CountVICPValueSum();

	/*=============================================================================
    函 数 名:EnableMinorMaxCheckBtn
    功    能:置灰辅视频未勾选格式中不可选的格式
    参    数:float fLastVICPValue
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2014/03/06  1.0     徐华秀    创建
    =============================================================================*/
	void EnableMinorUnableCheckBtn( float fLastVICPValue );

	/*=============================================================================
    函 数 名:EnableVedioCheckBtn
    功    能:设置主视频按钮状态
    参    数:BOOL bEnable
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/02/20  1.0     刘德印    创建
    =============================================================================*/
	void EnableMainCheckBtn(BOOL bEnable);

	/*=============================================================================
    函 数 名:EnableVedioCheckBtn
    功    能:设置辅视频按钮状态
    参    数:BOOL bEnable
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/02/20  1.0     刘德印    创建
    =============================================================================*/
	void EnableMinorCheckBtn(BOOL bEnable);

	/*=============================================================================
    函 数 名:EnableMainMaxCheckBtn
    功    能:当选择的主视频格式大于6   其余置灰
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2014/02/18  1.0     徐华秀    创建
    =============================================================================*/
	void EnableMainMaxCheckBtn();

	/*=============================================================================
    函 数 名:EnableMinorMaxCheckBtn
    功    能:当选择的辅助视频格式大于6   其余置灰
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/02/20  1.0     刘德印    创建
    =============================================================================*/
	void EnableMinorMaxCheckBtn();

	/*=============================================================================
    函 数 名:EnableAudioRadioBtn
    功    能:设置音频格式按键状态
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2014/02/25  1.0     徐华秀    创建
    =============================================================================*/
	void EnableAudioRadioBtn(BOOL bEnable);

	/*=============================================================================
    函 数 名:SetMainVideoBtnStatus
    功    能:设置主、辅视频格式按钮的显示状态
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/02/20  1.0     刘德印    创建
    =============================================================================*/
	void SetMainVideoBtnStatus(const TUmsVidFormat& tTpMainVideoRes);
	void SetMinorVideoBtnStatus(const TUmsVidFormat& tTpMinorVideoRes);

	/*=============================================================================
    函 数 名:SetConfFormatHide
    功    能:隐藏会议格式界面按键
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2014/02/25  1.0     徐华秀    创建
    =============================================================================*/
	void SetConfFormatHide( BOOL bHide = TRUE );
	void SetShowFormatExHide( BOOL bHide = TRUE );
	void SetAudioFormatHide( BOOL bHide = TRUE );

	/*=============================================================================
    函 数 名:UpdateVedioControl
    功    能:更新主、辅界面控件状态
    参    数:TCMSConfTemplate* pTTemplate    会议模板数据
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/02/20  1.0     刘德印    创建
    =============================================================================*/
	void UpdateVedioControl(TCMSConfTemplate* pTTemplate);

	void UpdateAudioControl(TCMSConfTemplate* pTTemplate);

	/*=============================================================================
    函 数 名:ShowMediaFormat
    功    能:显示媒体格式
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2014/02/25  1.0     徐华秀    创建
    =============================================================================*/
	void ShowMediaFormat();

private:
	EM_OPERATE_FLAG m_emOperateFlag;				//当前操作状态  编辑 新建 浏览
	TCMSConfTemplate m_tSelTemplate;				//当前点击模板	
	//TCMSConfTemplate  m_tBaseTemplate;			//原始选中模板媒体信息
	u16 m_wCheckResNum;                             //当前选择资源总数

	u16 m_wMainCheckCount;
	u16 m_wMinorCheckCount;

	u16 m_wAllResCount;
	EM_MEDIA_CURRENT_TABPAGE m_emTabFlag;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDIACFGLOGIC_H__737F35D3_454D_401B_A515_7D37F9F58671__INCLUDED_)
