// mediacfglogic.cpp : implementation file
//
#include "stdafx.h"
#include "umcwebproj.h"
#include "mediacfglogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMediaCfgLogic dialog
CMediaCfgLogic::CMediaCfgLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CMediaCfgLogic::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMediaCfgLogic)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_emOperateFlag = em_SCANF_PAGE_STATUS;
	m_emTabFlag = em_CONFFORMAT_PAGE;
	m_wMainCheckCount = 0;
	m_wMinorCheckCount = 0;
	m_wAllResCount = 0;
}

void CMediaCfgLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMediaCfgLogic)
	DDX_Control(pDX, IDC_STATIC_MEDIAINFO, m_stMediaInfo);
	DDX_Control(pDX, IDC_Btn_ConfFormat, m_btnConfFormat);
	DDX_Control(pDX, IDC_Btn_ShowFormat, m_btnShowFormat);
	DDX_Control(pDX, IDC_Btn_AudioFormat, m_btnAudioFormat);

	DDX_Control(pDX, IDC_BTN_HP1080P60F, m_btnHP1080P5060F);
	DDX_Control(pDX, IDC_BTN_HP1080P30F, m_btnHP1080P2530F);

	DDX_Control(pDX, IDC_BTN_HP720P60F, m_btnHP720P5060F);
	DDX_Control(pDX, IDC_BTN_HP720P30F, m_btnHP720P2530F);

	DDX_Control(pDX, IDC_BTN_BP1080P60F, m_btnBP1080P5060F);
	DDX_Control(pDX, IDC_BTN_BP1080P30F, m_btnBP1080P2530F);

	DDX_Control(pDX, IDC_BTN_BP720P60F, m_btnBP720P5060F);
	DDX_Control(pDX, IDC_BTN_BP720P30F, m_btnBP720P2530F);

	DDX_Control(pDX, IDC_BTN_BP4CIFP25F, m_btnBP4CIFP25F);

	DDX_Control(pDX, IDC_BTN_BPUXGAP60F, m_btnBPUXGAP60F);
	DDX_Control(pDX, IDC_BTN_BPWXGAP30F, m_btnBPWXGAP30F);
	DDX_Control(pDX, IDC_BTN_BPSXGAP30F, m_btnBPSXGAP30F);

	DDX_Control(pDX, IDC_BTN_BPWXGAP5F, m_btnBPWXGAP5F);
	DDX_Control(pDX, IDC_BTN_BPSXGAP5F, m_btnBPSXGAP5F);
	DDX_Control(pDX, IDC_BTN_BPXGAP5F, m_btnBPXGAP5F);

	DDX_Control(pDX, IDC_BUTTON_MpegAACLD, m_radiobtnMpegAACLD);
	DDX_Control(pDX, IDC_BUTTON_G711A, m_radiobtnG711A);
	DDX_Control(pDX, IDC_BUTTON_G711U, m_radiobtnG711U);
	DDX_Control(pDX, IDC_BUTTON_G719, m_radiobtnG719);
	DDX_Control(pDX, IDC_BUTTON_G7221, m_radiobtnG7221);
	DDX_Control(pDX, IDC_BUTTON_MP3, m_radiobtnMP3);
	DDX_Control(pDX, IDC_BUTTON_MpegAACLC, m_radiobtnMpegAACLC);

	DDX_Control(pDX, IDC_STATIC_CONFADPRES, m_stAdaptRes);
	DDX_Control(pDX, IDC_STATIC_ALLADPRES, m_stAllRes);
	DDX_Control(pDX, IDC_STATIC_RESCOUNT, m_stResCount);
	DDX_Control(pDX, IDC_STATIC_ALLRESCOUNT, m_stAllAdaptResCount);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMediaCfgLogic, CDlgChild)
	//{{AFX_MSG_MAP(CMediaCfgLogic)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_Btn_ConfFormat, OnBtnConfFormat)
	ON_BN_CLICKED(IDC_Btn_ShowFormat, OnBtnShowFormat)
	ON_BN_CLICKED(IDC_Btn_AudioFormat, OnBtnAudioFormat)

	ON_BN_CLICKED(IDC_BTN_HP1080P60F, OnBtnHP1080P5060F)
	ON_BN_CLICKED(IDC_BTN_HP1080P30F, OnBtnHP1080P2530F)

	ON_BN_CLICKED(IDC_BTN_HP720P60F, OnBtnHP720P5060F)
	ON_BN_CLICKED(IDC_BTN_HP720P30F, OnBtnHP720P2530F)

	ON_BN_CLICKED(IDC_BTN_BP1080P60F, OnBtnBP1080P5060F)
	ON_BN_CLICKED(IDC_BTN_BP1080P30F, OnBtnBP1080P2530F)

	ON_BN_CLICKED(IDC_BTN_BP720P60F, OnBtnBP720P5060F)
	ON_BN_CLICKED(IDC_BTN_BP720P30F, OnBtnBP720P2530F)

	ON_BN_CLICKED(IDC_BTN_BP4CIFP25F, OnBtnBP4CIFP25F)

	ON_BN_CLICKED(IDC_BTN_BPUXGAP60F, OnBtnBPUXGAP60F)
	ON_BN_CLICKED(IDC_BTN_BPWXGAP30F, OnBtnBPWXGAP30F)
	ON_BN_CLICKED(IDC_BTN_BPSXGAP30F, OnBtnBPSXGAP30F)

	ON_BN_CLICKED(IDC_BTN_BPWXGAP5F, OnBtnBPWXGAP5F)
	ON_BN_CLICKED(IDC_BTN_BPSXGAP5F, OnBtnBPSXGAP5F)
	ON_BN_CLICKED(IDC_BTN_BPXGAP5F, OnBtnBPXGAP5F)

	ON_BN_CLICKED(IDC_BUTTON_MpegAACLD, OnRadioBtnMpegAACLD)
	ON_BN_CLICKED(IDC_BUTTON_G711A, OnRadioBtnG711A)
	ON_BN_CLICKED(IDC_BUTTON_G711U, OnRadioBtnG711U)
	ON_BN_CLICKED(IDC_BUTTON_G719, OnRadioBtnG719)
	ON_BN_CLICKED(IDC_BUTTON_G7221, OnRadioBtnG7221)
	ON_BN_CLICKED(IDC_BUTTON_MP3, OnRadioBtnMP3)
	ON_BN_CLICKED(IDC_BUTTON_MpegAACLC, OnRadioBtnMpegAACLC)

	ON_MESSAGE( WM_DEF_SENDTMPINFOTOPAGE,  OnSendTmpInfoToPage )
	ON_MESSAGE( UI_UMS_CONFTMPRESUSEDCOUNT_NOTIFY,  OnConfTmpResUsedCountNotify )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMediaCfgLogic message handlers
void CMediaCfgLogic::RegisterFun()
{
	REG_MSG( UI_UMS_CONFTMPRESUSEDCOUNT_NOTIFY, GetSafeHwnd() );
}

BOOL CMediaCfgLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();
	
	RegisterFun();

	if ( InitControlPane() )
	{
		InitFormatPageControl();
		InitAudioPageControl();
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMediaCfgLogic::InitControlPane()
{
	CRect rectClient;
	this->GetClientRect(&rectClient);

	CUmcwebCommon::SetTextTransStatic( &m_stMediaInfo, "媒体信息" , 14, Color( 24, 25, 27 ) );
	m_stMediaInfo.SetWindowPos( NULL, 12 + 17 + 66, 14, rectClient.Width(), 20, SWP_SHOWWINDOW );

	m_btnConfFormat.SetImage( IDR_PNG_MEETTMPWND_BTN_MEETCONFFORMAT, IDR_PNG_MEETTMPWND_BTN_MEETCONFFORMATDOWN, IDR_PNG_MEETTMPWND_BTN_MEETCONFFORMATSEL );
	m_btnShowFormat.SetImage( IDR_PNG_MEETTMPWND_BTN_MEETSHOWFORMAT, IDR_PNG_MEETTMPWND_BTN_MEETSHOWFORMATDOWN, IDR_PNG_MEETTMPWND_BTN_MEETSHOWFORMATSEL );
	m_btnAudioFormat.SetImage( IDR_PNG_MEETTMPWND_BTN_MEETAUDIOFORMAT, IDR_PNG_MEETTMPWND_BTN_MEETAUDIOFORMATDOWN, IDR_PNG_MEETTMPWND_BTN_MEETAUDIOFORMATSEL );

	CRect rectTab;
	m_btnConfFormat.SetWindowPos( NULL, 12, 51, m_btnConfFormat.GetImageSize().cx, m_btnConfFormat.GetImageSize().cy, SWP_SHOWWINDOW );
	m_btnConfFormat.GetWindowRect(&rectTab);
	ScreenToClient( &rectTab );
	m_btnShowFormat.SetWindowPos( NULL, rectTab.right, 51, m_btnShowFormat.GetImageSize().cx, m_btnShowFormat.GetImageSize().cy, SWP_SHOWWINDOW );
	m_btnShowFormat.GetWindowRect(&rectTab);
	ScreenToClient( &rectTab );
	m_btnAudioFormat.SetWindowPos( NULL, rectTab.right, 51, m_btnShowFormat.GetImageSize().cx, m_btnShowFormat.GetImageSize().cy, SWP_SHOWWINDOW );

	m_btnConfFormat.EnableWindow(FALSE);
	m_btnShowFormat.EnableWindow(TRUE);
	m_btnAudioFormat.EnableWindow(TRUE);

	return TRUE;
}
BOOL CMediaCfgLogic::InitFormatPageControl()
{
	//第一行
	CUmcwebCommon::SetTextTransCheckBtn( &m_btnHP1080P5060F, "HP 1080P@50/60fps" );
	m_btnHP1080P5060F.SetWindowPos( NULL, 21, 105, m_btnHP1080P5060F.GetImageSize().cx, m_btnHP1080P5060F.GetImageSize().cy, SWP_HIDEWINDOW );
		
	CUmcwebCommon::SetTextTransCheckBtn( &m_btnHP1080P2530F, "HP 1080P@25/30fps" );
	m_btnHP1080P2530F.SetWindowPos( NULL, 21 + 240, 105, m_btnHP1080P2530F.GetImageSize().cx, m_btnHP1080P2530F.GetImageSize().cy, SWP_HIDEWINDOW );
	
	//第二行	
	CUmcwebCommon::SetTextTransCheckBtn( &m_btnHP720P5060F, "HP 720P@50/60fps" );
	m_btnHP720P5060F.SetWindowPos( NULL, 21, 105 + 59, m_btnHP720P5060F.GetImageSize().cx, m_btnHP720P5060F.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_btnHP720P2530F, "HP 720P@25/30fps" );
	m_btnHP720P2530F.SetWindowPos( NULL, 21 + 240, 105 + 59, m_btnHP720P2530F.GetImageSize().cx, m_btnHP720P2530F.GetImageSize().cy, SWP_HIDEWINDOW );
		
	//第三行
	CUmcwebCommon::SetTextTransCheckBtn( &m_btnBP1080P5060F, "BP 1080P@50/60fps" );
	m_btnBP1080P5060F.SetWindowPos( NULL, 21, 105 + 59 * 2, m_btnBP1080P5060F.GetImageSize().cx, m_btnBP1080P5060F.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransCheckBtn( &m_btnBP1080P2530F, "BP 1080P@25/30fps" );
	m_btnBP1080P2530F.SetWindowPos( NULL, 21 + 240, 105 + 59 * 2, m_btnBP1080P2530F.GetImageSize().cx, m_btnBP1080P2530F.GetImageSize().cy, SWP_HIDEWINDOW );
	
	//第四行
	CUmcwebCommon::SetTextTransCheckBtn( &m_btnBP720P5060F, "BP 720P@50/60fps" );
	m_btnBP720P5060F.SetWindowPos( NULL, 21,  105 + 59 * 3, m_btnBP720P5060F.GetImageSize().cx, m_btnBP720P5060F.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransCheckBtn( &m_btnBP720P2530F, "BP 720P@25/30fps" );	
	m_btnBP720P2530F.SetWindowPos( NULL, 21 + 240, 105 + 59 * 3, m_btnBP720P2530F.GetImageSize().cx, m_btnBP720P2530F.GetImageSize().cy, SWP_HIDEWINDOW );
	
	//第五行
	CUmcwebCommon::SetTextTransCheckBtn( &m_btnBP4CIFP25F, "BP 4CIF@25fps" );	
	m_btnBP4CIFP25F.SetWindowPos( NULL, 21, 105 + 59 * 4, m_btnBP4CIFP25F.GetImageSize().cx, m_btnBP4CIFP25F.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransCheckBtn( &m_btnBPUXGAP60F, "BP UXGA@60fps" );	
	m_btnBPUXGAP60F.SetWindowPos( NULL, 21 + 240, 105 + 59 * 4, m_btnBPUXGAP60F.GetImageSize().cx, m_btnBPUXGAP60F.GetImageSize().cy, SWP_HIDEWINDOW );
	
	//第六行
	CUmcwebCommon::SetTextTransCheckBtn( &m_btnBPWXGAP30F, "BP WXGA@30fps" );	
	m_btnBPWXGAP30F.SetWindowPos( NULL, 21, 105 + 59 * 5, m_btnBPWXGAP30F.GetImageSize().cx, m_btnBPWXGAP30F.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransCheckBtn( &m_btnBPSXGAP30F, "BP SXGA@30fps" );	
	m_btnBPSXGAP30F.SetWindowPos( NULL, 21 + 240, 105 + 59 * 5, m_btnBPSXGAP30F.GetImageSize().cx, m_btnBPSXGAP30F.GetImageSize().cy, SWP_HIDEWINDOW );
	
	//第七行
	CUmcwebCommon::SetTextTransCheckBtn( &m_btnBPWXGAP5F, "BP WXGA@5fps" );	
	m_btnBPWXGAP5F.SetWindowPos( NULL, 21, 105 + 59 * 6, m_btnBPWXGAP5F.GetImageSize().cx, m_btnBPWXGAP5F.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransCheckBtn( &m_btnBPSXGAP5F, "BP SXGA@5fps" );	
	m_btnBPSXGAP5F.SetWindowPos( NULL, 21 + 240, 105 + 59 * 6, m_btnBPSXGAP5F.GetImageSize().cx, m_btnBPSXGAP5F.GetImageSize().cy, SWP_HIDEWINDOW );
	
	//第八行
	CUmcwebCommon::SetTextTransCheckBtn( &m_btnBPXGAP5F, "BP XGA@5fps" );	
	m_btnBPXGAP5F.SetWindowPos( NULL, 21, 105 + 59 * 7, m_btnBPXGAP5F.GetImageSize().cx, m_btnBPXGAP5F.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CRect rectClient;
	this->GetClientRect(&rectClient);

	//会议所需适配资源
	CRect rcControl;
	m_btnBPXGAP5F.GetWindowRect(&rcControl);
	this->ScreenToClient( &rcControl );
	
	CUmcwebCommon::SetTextTransStatic( &m_stAdaptRes, "会议所需适配资源数  ", 13, Color( 0, 114, 255 ) );
	m_stAdaptRes.SetWindowPos( NULL, 21,  rcControl.bottom + 15, rectClient.Width(), 17, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransStatic( &m_stAllRes, "总适配资源数  ", 13, Color( 0, 114, 255 ) );
	m_stAllRes.SetWindowPos( NULL, 300,  rcControl.bottom + 15, rectClient.Width(), 17, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransStatic( &m_stResCount, "5", 13, Color( 0, 114, 255 ) );
	m_stResCount.SetWindowPos( NULL, 195,  rcControl.bottom + 15, rectClient.Width(), 17, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransStatic( &m_stAllAdaptResCount, "8 ", 13, Color( 0, 114, 255 ) );
	m_stAllAdaptResCount.SetWindowPos( NULL, 428,  rcControl.bottom + 15, rectClient.Width(), 17, SWP_HIDEWINDOW );
	
	return TRUE;
}

BOOL CMediaCfgLogic::InitAudioPageControl()
{
	CUmcwebCommon::SetTextTransRadioBtn( &m_radiobtnMpegAACLD, "MPEG4 AAC-LD单声道" );
	m_radiobtnMpegAACLD.SetWindowPos( NULL, 25, 105, m_radiobtnMpegAACLD.GetImageSize().cx, m_radiobtnMpegAACLD.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransRadioBtn( &m_radiobtnG711A, "G.711A" );
	m_radiobtnG711A.SetWindowPos( NULL, 25, 105 + 70, m_radiobtnG711A.GetImageSize().cx, m_radiobtnG711A.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransRadioBtn( &m_radiobtnG711U, "G.711U" );
	m_radiobtnG711U.SetWindowPos( NULL, 25, 105 + 2 * 70, m_radiobtnG711U.GetImageSize().cx, m_radiobtnG711U.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransRadioBtn( &m_radiobtnG719, "G.719" );
	m_radiobtnG719.SetWindowPos( NULL, 25, 105 + 3 * 70, m_radiobtnG719.GetImageSize().cx, m_radiobtnG719.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransRadioBtn( &m_radiobtnG7221, "G.722.1 Annex C Polycom Siren14" );
	m_radiobtnG7221.SetWindowPos( NULL, 25, 105 + 4 * 70, m_radiobtnG7221.GetImageSize().cx, m_radiobtnG7221.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransRadioBtn( &m_radiobtnMP3, "MP3" );
	m_radiobtnMP3.SetWindowPos( NULL, 25, 105 + 5 * 70, m_radiobtnMP3.GetImageSize().cx, m_radiobtnMP3.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransRadioBtn( &m_radiobtnMpegAACLC, "MPEG4 AAC-LC单声道" );
	m_radiobtnMpegAACLC.SetWindowPos( NULL, 25, 105 + 6 * 70, m_radiobtnMpegAACLC.GetImageSize().cx, m_radiobtnMpegAACLC.GetImageSize().cy, SWP_HIDEWINDOW );

	return TRUE;
}

void CMediaCfgLogic::OnDestroy() 
{
	CDlgChild::OnDestroy();

	m_wMainCheckCount = 0;
	m_wMinorCheckCount = 0;
}

void CMediaCfgLogic::OnBtnConfFormat() 
{
	m_emTabFlag = em_CONFFORMAT_PAGE;
	
	m_btnConfFormat.EnableWindow(FALSE);
	m_btnShowFormat.EnableWindow(TRUE);
	m_btnAudioFormat.EnableWindow(TRUE);

	ShowMediaFormat();

	UpdateVedioControl(&m_tSelTemplate);
	if ( em_SCANF_PAGE_STATUS == m_emOperateFlag )
	{
		EnableMainCheckBtn(FALSE);	
	}
	else
	{
		EnableMainCheckBtn(TRUE);
		CountVideoResNum();
	}
	
	return;
}

void CMediaCfgLogic::OnBtnShowFormat() 
{
	m_emTabFlag = em_SHOWFORMAT_PAGE;
	
	m_btnConfFormat.EnableWindow(TRUE);
	m_btnShowFormat.EnableWindow(FALSE);
	m_btnAudioFormat.EnableWindow(TRUE);

	ShowMediaFormat();

	UpdateVedioControl(&m_tSelTemplate);
	if ( em_SCANF_PAGE_STATUS == m_emOperateFlag )
	{
		EnableMinorCheckBtn(FALSE);
	}
	else
	{
		EnableMinorCheckBtn(TRUE);
		CountVideoResNum();
	}
	
	return;
}

void CMediaCfgLogic::OnBtnAudioFormat() 
{
	m_emTabFlag = em_AUDIOFORMAT_PAGE;
	
	m_btnConfFormat.EnableWindow(TRUE);
	m_btnShowFormat.EnableWindow(TRUE);
	m_btnAudioFormat.EnableWindow(FALSE);

	ShowMediaFormat();

	UpdateAudioControl(&m_tSelTemplate);
	if ( em_SCANF_PAGE_STATUS == m_emOperateFlag )
	{
		EnableAudioRadioBtn(FALSE);
	}
	else
	{
		EnableAudioRadioBtn(TRUE);
	}
	
	return;
}

void CMediaCfgLogic::ShowMediaFormat()
{
	switch ( m_emTabFlag )
	{
	case em_CONFFORMAT_PAGE:
		{
			SetConfFormatHide( FALSE );
			SetShowFormatExHide( TRUE );
			SetAudioFormatHide( TRUE );
		}
		break;
	case em_SHOWFORMAT_PAGE:
		{
			SetConfFormatHide( FALSE );
			SetShowFormatExHide( FALSE );
			SetAudioFormatHide( TRUE );
		}
		break;
	case em_AUDIOFORMAT_PAGE:
		{
			SetConfFormatHide( TRUE );
			SetShowFormatExHide( TRUE );
			SetAudioFormatHide( FALSE );
		}
		break;
	default:
		{
			SetConfFormatHide( TRUE );
			SetShowFormatExHide( TRUE );
			SetAudioFormatHide( TRUE );
		}
		break;
	}
}

void CMediaCfgLogic::CountVideoResNum()
{
	if ( em_CONFFORMAT_PAGE == m_emTabFlag )
	{
		//主视频格式
		m_wMainCheckCount = 0;
		if ( BST_CHECKED == m_btnHP1080P5060F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_emRes = emTPVHD1080p1920x1080;
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_wFrameRate = 60;
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_emQualityLvl = emTPH264HP;
			++m_wMainCheckCount;
		}
		
		if ( BST_CHECKED == m_btnHP1080P2530F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_emRes = emTPVHD1080p1920x1080;
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_wFrameRate = 30;
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_emQualityLvl = emTPH264HP;
			++m_wMainCheckCount;	
		}
		
		if ( BST_CHECKED == m_btnHP720P5060F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_emRes = emTPVHD720p1280x720;
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_wFrameRate = 60;
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_emQualityLvl = emTPH264HP;
			++m_wMainCheckCount;	
		}

		if ( BST_CHECKED == m_btnHP720P2530F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_emRes = emTPVHD720p1280x720;
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_wFrameRate = 30;
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_emQualityLvl = emTPH264HP;
			++m_wMainCheckCount;	
		}

		if ( BST_CHECKED == m_btnBP1080P5060F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_emRes = emTPVHD1080p1920x1080;
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_wFrameRate = 60;
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_emQualityLvl = emTPH264BP;
			++m_wMainCheckCount;	
		}

		if ( BST_CHECKED == m_btnBP1080P2530F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_emRes = emTPVHD1080p1920x1080;
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_wFrameRate = 30;
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_emQualityLvl = emTPH264BP;
			++m_wMainCheckCount;	
		}

		if ( BST_CHECKED == m_btnBP720P5060F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_emRes = emTPVHD720p1280x720;
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_wFrameRate = 60;
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_emQualityLvl = emTPH264BP;
			++m_wMainCheckCount;	
		}

		if ( BST_CHECKED == m_btnBP720P2530F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_emRes = emTPVHD720p1280x720;
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_wFrameRate = 30;
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_emQualityLvl = emTPH264BP;
			++m_wMainCheckCount;	
		}

		if ( BST_CHECKED == m_btnBP4CIFP25F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_emRes = emTPV4CIF;
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_wFrameRate = 25;
			m_tSelTemplate.m_atTpMainVideoRes[m_wMainCheckCount].m_emQualityLvl = emTPH264BP;
			++m_wMainCheckCount;	
		}

		m_tSelTemplate.m_wMainNum = m_wMainCheckCount;

		if ( m_wMainCheckCount >= 6 )
		{
			EnableMainMaxCheckBtn();
		} 
		else
		{
			EnableMainCheckBtn(TRUE);
		}
	} 
	else if ( em_SHOWFORMAT_PAGE == m_emTabFlag )
	{
		//辅视频格式
		m_wMinorCheckCount = 0;
		if ( BST_CHECKED == m_btnHP1080P5060F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emRes = emTPVHD1080p1920x1080;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_wFrameRate = 60;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emQualityLvl = emTPH264HP;
			++m_wMinorCheckCount;
		}
		
		if ( BST_CHECKED == m_btnHP1080P2530F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emRes = emTPVHD1080p1920x1080;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_wFrameRate = 30;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emQualityLvl = emTPH264HP;
			++m_wMinorCheckCount;	
		}
		
		if ( BST_CHECKED == m_btnHP720P5060F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emRes = emTPVHD720p1280x720;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_wFrameRate = 60;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emQualityLvl = emTPH264HP;
			++m_wMinorCheckCount;	
		}

		if ( BST_CHECKED == m_btnHP720P2530F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emRes = emTPVHD720p1280x720;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_wFrameRate = 30;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emQualityLvl = emTPH264HP;
			++m_wMinorCheckCount;	
		}

		if ( BST_CHECKED == m_btnBP1080P5060F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emRes = emTPVHD1080p1920x1080;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_wFrameRate = 60;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emQualityLvl = emTPH264BP;
			++m_wMinorCheckCount;	
		}

		if ( BST_CHECKED == m_btnBP1080P2530F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emRes = emTPVHD1080p1920x1080;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_wFrameRate = 30;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emQualityLvl = emTPH264BP;
			++m_wMinorCheckCount;	
		}

		if ( BST_CHECKED == m_btnBP720P5060F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emRes = emTPVHD720p1280x720;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_wFrameRate = 60;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emQualityLvl = emTPH264BP;
			++m_wMinorCheckCount;	
		}

		if ( BST_CHECKED == m_btnBP720P2530F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emRes = emTPVHD720p1280x720;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_wFrameRate = 30;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emQualityLvl = emTPH264BP;
			++m_wMinorCheckCount;	
		}

		if ( BST_CHECKED == m_btnBP4CIFP25F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emRes = emTPV4CIF;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_wFrameRate = 25;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emQualityLvl = emTPH264BP;
			++m_wMinorCheckCount;	
		}

		if ( BST_CHECKED == m_btnBPUXGAP60F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emRes = emTPVGA1600x1200;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_wFrameRate = 60;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emQualityLvl = emTPH264BP;
			++m_wMinorCheckCount;
		}
		
		if ( BST_CHECKED == m_btnBPWXGAP30F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emRes = emTPVGA1280x800;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_wFrameRate = 30;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emQualityLvl = emTPH264BP;
			++m_wMinorCheckCount;	
		}
		
		if ( BST_CHECKED == m_btnBPSXGAP30F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emRes = emTPVGA1280x1024;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_wFrameRate = 30;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emQualityLvl = emTPH264BP;
			++m_wMinorCheckCount;	
		}
		
		if ( BST_CHECKED == m_btnBPWXGAP5F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emRes = emTPVGA1280x800;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_wFrameRate = 5;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emQualityLvl = emTPH264BP;
			++m_wMinorCheckCount;	
		}
		
		if ( BST_CHECKED == m_btnBPSXGAP5F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emRes = emTPVGA1280x1024;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_wFrameRate = 5;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emQualityLvl = emTPH264BP;
			++m_wMinorCheckCount;	
		}
		
		if ( BST_CHECKED == m_btnBPXGAP5F.GetCheck() )
		{
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emRes = emTPVGA1024x768;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_wFrameRate = 5;
			m_tSelTemplate.m_atTpMinorVideoRes[m_wMinorCheckCount].m_emQualityLvl = emTPH264BP;
			++m_wMinorCheckCount;	
		}

		m_tSelTemplate.m_wMinorNum = m_wMinorCheckCount;

// 		if ( 5 == m_wMinorCheckCount )
// 		{
// 			CountVICPValueSum();
// 		}
// 		else 
		if ( m_wMinorCheckCount >= 6 )
		{
			EnableMinorMaxCheckBtn();
		}
		else
		{
			EnableMinorCheckBtn(TRUE);
		}
	}
	else
	{
		//音频格式 error
	}

	m_wCheckResNum = CComInterface::GetNeedBasNum(m_tSelTemplate);
	UpdateResUsedCountToControl(m_wCheckResNum);
}

void CMediaCfgLogic::CountVICPValueSum()
{
// 	float fVICPValueSum = 0;
// 	float fVICPValueMax = 0;
// 
// 	if ( ( BST_CHECKED == m_btnHP1080P60F.GetCheck() ) || ( BST_CHECKED == m_btnHP1080P50F.GetCheck() ) )
// 	{
// 		fVICPValueSum += VICP1080p50or60f;
// 		if ( VICP1080p50or60f > fVICPValueMax )
// 		{
// 			fVICPValueMax = VICP1080p50or60f;
// 		}
// 	}
// 
// 	if ( ( BST_CHECKED == m_btnHP1080P30F.GetCheck() ) || ( BST_CHECKED == m_btnHP1080P25F.GetCheck() ) )
// 	{
// 		fVICPValueSum += VICP1080p25or30f;
// 		if ( VICP1080p25or30f > fVICPValueMax )
// 		{
// 			fVICPValueMax = VICP1080p25or30f;
// 		}
// 	}
// 
// 	if ( ( BST_CHECKED == m_btnHP720P60F.GetCheck() ) || ( BST_CHECKED == m_btnHP720P50F.GetCheck() ) )
// 	{	
// 		fVICPValueSum += VICP720p50or60f;
// 		if ( VICP720p50or60f > fVICPValueMax )
// 		{
// 			fVICPValueMax = VICP720p50or60f;
// 		}
// 	}
// 
// 	if ( ( BST_CHECKED == m_btnHP720P30F.GetCheck() ) || ( BST_CHECKED == m_btnHP720P25F.GetCheck() ) )
// 	{	
// 		fVICPValueSum += VICP720p25or30f;
// 		if ( VICP720p25or30f > fVICPValueMax )
// 		{
// 			fVICPValueMax = VICP720p25or30f;
// 		}
// 	}
// 
// 	if ( ( BST_CHECKED == m_btnBP1080P60F.GetCheck() ) || ( BST_CHECKED == m_btnBP1080P50F.GetCheck() ) )
// 	{	
// 		fVICPValueSum += VICP1080p50or60f;
// 		if ( VICP1080p50or60f > fVICPValueMax )
// 		{
// 			fVICPValueMax = VICP1080p50or60f;
// 		}
// 	}
// 
// 	if ( ( BST_CHECKED == m_btnBP1080P30F.GetCheck() ) || ( BST_CHECKED == m_btnBP1080P25F.GetCheck() ) )
// 	{	
// 		fVICPValueSum += VICP1080p25or30f;
// 		if ( VICP1080p25or30f > fVICPValueMax )
// 		{
// 			fVICPValueMax = VICP1080p25or30f;
// 		}
// 	}
// 
// 	if ( ( BST_CHECKED == m_btnBP720P60F.GetCheck() ) || ( BST_CHECKED == m_btnBP720P50F.GetCheck() ) )
// 	{	
// 		fVICPValueSum += VICP720p50or60f;
// 		if ( VICP720p50or60f > fVICPValueMax )
// 		{
// 			fVICPValueMax = VICP720p50or60f;
// 		}
// 	}
// 
// 	if ( ( BST_CHECKED == m_btnBP720P30F.GetCheck() ) || ( BST_CHECKED == m_btnBP720P25F.GetCheck() ) )
// 	{
// 		fVICPValueSum += VICP720p25or30f;
// 		if ( VICP720p25or30f > fVICPValueMax )
// 		{
// 			fVICPValueMax = VICP720p25or30f;
// 		}
// 	}
// 
// 	if ( BST_CHECKED == m_btnBP4CIFP25F.GetCheck() )
// 	{	
// 		fVICPValueSum += VICP4CIFp25f;
// 		if ( VICP4CIFp25f > fVICPValueMax )
// 		{
// 			fVICPValueMax = VICP4CIFp25f;
// 		}
// 	}
// 
// 	if ( BST_CHECKED == m_btnBPUXGAP60F.GetCheck() )
// 	{
// 		fVICPValueSum += VICPUXGAp60f;
// 		if ( VICPUXGAp60f > fVICPValueMax )
// 		{
// 			fVICPValueMax = VICPUXGAp60f;
// 		}
// 	}
// 
// 	if ( BST_CHECKED == m_btnBPWXGAP30F.GetCheck() )
// 	{	
// 		fVICPValueSum += VICPWXGAp30f;
// 		if ( VICPWXGAp30f > fVICPValueMax )
// 		{
// 			fVICPValueMax = VICPWXGAp30f;
// 		}
// 	}
// 
// 	if ( BST_CHECKED == m_btnBPSXGAP30F.GetCheck() )
// 	{	
// 		fVICPValueSum += VICPSXGAp30f;
// 		if ( VICPSXGAp30f > fVICPValueMax )
// 		{
// 			fVICPValueMax = VICPSXGAp30f;
// 		}
// 	}
// 
// 	if ( BST_CHECKED == m_btnBPWXGAP5F.GetCheck() )
// 	{	
// 		fVICPValueSum += VICPWXGAp5f;
// 		if ( VICPWXGAp5f > fVICPValueMax )
// 		{
// 			fVICPValueMax = VICPWXGAp5f;
// 		}
// 	}
// 
// 	if ( BST_CHECKED == m_btnBPSXGAP5F.GetCheck() )
// 	{	
// 		fVICPValueSum += VICPSXGAp5f;
// 		if ( VICPSXGAp5f > fVICPValueMax )
// 		{
// 			fVICPValueMax = VICPSXGAp5f;
// 		}
// 	}
// 
// 	if ( BST_CHECKED == m_btnBPXGAP5F.GetCheck() )
// 	{	
// 		fVICPValueSum += VICPXGAp5f;
// 		if ( VICPXGAp5f > fVICPValueMax )
// 		{
// 			fVICPValueMax = VICPXGAp5f;
// 		}
// 	}
// 
// 	fVICPValueSum = fVICPValueSum - fVICPValueMax;
// 	float fLastVICPValue = 3.000f - fVICPValueSum; 
// 
// 	EnableMinorUnableCheckBtn( fLastVICPValue );
}

void CMediaCfgLogic::EnableMinorUnableCheckBtn( float fLastVICPValue )
{
// 	EnableMinorCheckBtn(TRUE);
// 
// 	if ( ( BST_UNCHECKED == m_btnHP1080P60F.GetCheck() ) && ( BST_UNCHECKED == m_btnHP1080P50F.GetCheck() ) )
// 	{
// 		if ( VICP1080p50or60f > fLastVICPValue )
// 		{
// 			m_btnHP1080P60F.EnableWindow(FALSE);
// 			m_btnHP1080P50F.EnableWindow(FALSE);
// 		}
// 	}
// 	
// 	if ( ( BST_UNCHECKED == m_btnHP1080P30F.GetCheck() ) && ( BST_UNCHECKED == m_btnHP1080P25F.GetCheck() ) )
// 	{
// 		if ( VICP1080p25or30f > fLastVICPValue )
// 		{
// 			m_btnHP1080P30F.EnableWindow(FALSE);
// 			m_btnHP1080P25F.EnableWindow(FALSE);
// 		}
// 	}
// 	
// 	if ( ( BST_UNCHECKED == m_btnHP720P60F.GetCheck() ) && ( BST_UNCHECKED == m_btnHP720P50F.GetCheck() ) )
// 	{
// 		if ( VICP720p50or60f > fLastVICPValue )
// 		{
// 			m_btnHP720P60F.EnableWindow(FALSE);
// 			m_btnHP720P50F.EnableWindow(FALSE);
// 		}
// 	}
// 	
// 	if ( ( BST_UNCHECKED == m_btnHP720P30F.GetCheck() ) && ( BST_UNCHECKED == m_btnHP720P25F.GetCheck() ) )
// 	{
// 		if ( VICP720p25or30f > fLastVICPValue )
// 		{
// 			m_btnHP720P30F.EnableWindow(FALSE);
// 			m_btnHP720P25F.EnableWindow(FALSE);
// 		}
// 	}
// 	
// 	if ( ( BST_UNCHECKED == m_btnBP1080P60F.GetCheck() ) && ( BST_UNCHECKED == m_btnBP1080P50F.GetCheck() ) )
// 	{
// 		if ( VICP1080p50or60f > fLastVICPValue )
// 		{
// 			m_btnBP1080P60F.EnableWindow(FALSE);
// 			m_btnBP1080P50F.EnableWindow(FALSE);
// 		}
// 	}
// 	
// 	if ( ( BST_UNCHECKED == m_btnBP1080P30F.GetCheck() ) && ( BST_UNCHECKED == m_btnBP1080P25F.GetCheck() ) )
// 	{
// 		if ( VICP1080p25or30f > fLastVICPValue )
// 		{
// 			m_btnBP1080P30F.EnableWindow(FALSE);
// 			m_btnBP1080P25F.EnableWindow(FALSE);
// 		}
// 	}
// 	
// 	if ( ( BST_UNCHECKED == m_btnBP720P60F.GetCheck() ) && ( BST_UNCHECKED == m_btnBP720P50F.GetCheck() ) )
// 	{
// 		if ( VICP720p50or60f > fLastVICPValue )
// 		{
// 			m_btnBP720P60F.EnableWindow(FALSE);
// 			m_btnBP720P50F.EnableWindow(FALSE);
// 		}
// 	}
// 	
// 	if ( ( BST_UNCHECKED == m_btnBP720P30F.GetCheck() ) && ( BST_UNCHECKED == m_btnBP720P25F.GetCheck() ) )
// 	{
// 		if ( VICP720p25or30f > fLastVICPValue )
// 		{
// 			m_btnBP720P30F.EnableWindow(FALSE);
// 			m_btnBP720P25F.EnableWindow(FALSE);
// 		}
// 	}
// 	
// 	if ( BST_UNCHECKED == m_btnBP4CIFP25F.GetCheck() )
// 	{
// 		if ( VICP4CIFp25f > fLastVICPValue )
// 		{
// 			m_btnBP4CIFP25F.EnableWindow(FALSE);
// 		}
// 	}
// 	
// 	if ( BST_UNCHECKED == m_btnBPUXGAP60F.GetCheck() )
// 	{
// 		if ( VICPUXGAp60f > fLastVICPValue )
// 		{
// 			m_btnBPUXGAP60F.EnableWindow(FALSE);
// 		}
// 	}
// 	
// 	if ( BST_UNCHECKED == m_btnBPWXGAP30F.GetCheck() )
// 	{
// 		if ( VICPWXGAp30f > fLastVICPValue )
// 		{
// 			m_btnBPWXGAP30F.EnableWindow(FALSE);
// 		}
// 	}
// 	
// 	if ( BST_UNCHECKED == m_btnBPSXGAP30F.GetCheck() )
// 	{
// 		if ( VICPSXGAp30f > fLastVICPValue )
// 		{
// 			m_btnBPSXGAP30F.EnableWindow(FALSE);
// 		}
// 	}
// 	
// 	if ( BST_UNCHECKED == m_btnBPWXGAP5F.GetCheck() )
// 	{
// 		if ( VICPWXGAp5f > fLastVICPValue )
// 		{
// 			m_btnBPWXGAP5F.EnableWindow(FALSE);
// 		}
// 	}
// 	
// 	if ( BST_UNCHECKED == m_btnBPSXGAP5F.GetCheck() )
// 	{
// 		if ( VICPSXGAp5f > fLastVICPValue )
// 		{
// 			m_btnBPSXGAP5F.EnableWindow(FALSE);
// 		}
// 	}
// 	
// 	if ( BST_UNCHECKED == m_btnBPXGAP5F.GetCheck() )
// 	{
// 		if ( VICPXGAp5f > fLastVICPValue )
// 		{
// 			m_btnBPXGAP5F.EnableWindow(FALSE);
// 		}
// 	}
}

void CMediaCfgLogic::EnableMainCheckBtn(BOOL bEnable)
{
	m_btnHP1080P5060F.EnableWindow(bEnable);
	m_btnHP1080P2530F.EnableWindow(bEnable);

	m_btnHP720P5060F.EnableWindow(bEnable);
	m_btnHP720P2530F.EnableWindow(bEnable);

	m_btnBP1080P5060F.EnableWindow(bEnable);
	m_btnBP1080P2530F.EnableWindow(bEnable);
	
	m_btnBP720P5060F.EnableWindow(bEnable);
	m_btnBP720P2530F.EnableWindow(bEnable);

	m_btnBP4CIFP25F.EnableWindow(bEnable);
}

void CMediaCfgLogic::EnableMinorCheckBtn(BOOL bEnable)
{
	m_btnHP1080P5060F.EnableWindow(bEnable);
	m_btnHP1080P2530F.EnableWindow(bEnable);

	m_btnHP720P5060F.EnableWindow(bEnable);
	m_btnHP720P2530F.EnableWindow(bEnable);
	
	m_btnBP1080P5060F.EnableWindow(bEnable);
	m_btnBP1080P2530F.EnableWindow(bEnable);
	
	m_btnBP720P5060F.EnableWindow(bEnable);
	m_btnBP720P2530F.EnableWindow(bEnable);

	m_btnBP4CIFP25F.EnableWindow(bEnable);

	m_btnBPUXGAP60F.EnableWindow(bEnable);
	m_btnBPWXGAP30F.EnableWindow(bEnable);
	m_btnBPSXGAP30F.EnableWindow(bEnable);

	m_btnBPWXGAP5F.EnableWindow(bEnable);
	m_btnBPSXGAP5F.EnableWindow(bEnable);
	m_btnBPXGAP5F.EnableWindow(bEnable);
}

void CMediaCfgLogic::EnableAudioRadioBtn(BOOL bEnable)
{
	m_radiobtnMpegAACLD.EnableWindow(bEnable);
	m_radiobtnG711A.EnableWindow(bEnable);
	m_radiobtnG711U.EnableWindow(bEnable);
	m_radiobtnG719.EnableWindow(bEnable);
	m_radiobtnG7221.EnableWindow(bEnable);
	m_radiobtnMP3.EnableWindow(bEnable);
	m_radiobtnMpegAACLC.EnableWindow(bEnable);
}

void CMediaCfgLogic::SetConfFormatHide(BOOL bHide)
{
	m_btnHP1080P5060F.ShowWindow(!bHide);
	m_btnHP1080P2530F.ShowWindow(!bHide);
		
	m_btnHP720P5060F.ShowWindow(!bHide);
	m_btnHP720P2530F.ShowWindow(!bHide);
		
	m_btnBP1080P5060F.ShowWindow(!bHide);
	m_btnBP1080P2530F.ShowWindow(!bHide);

	m_btnBP720P5060F.ShowWindow(!bHide);		
	m_btnBP720P2530F.ShowWindow(!bHide);

	m_btnBP4CIFP25F.ShowWindow(!bHide);

	m_stAdaptRes.ShowWindow(!bHide);
	m_stAllRes.ShowWindow(!bHide);
	m_stResCount.ShowWindow(!bHide);
	m_stAllAdaptResCount.ShowWindow(!bHide);
}

void CMediaCfgLogic::SetShowFormatExHide(BOOL bHide)
{
	m_btnBPUXGAP60F.ShowWindow(!bHide);
	m_btnBPWXGAP30F.ShowWindow(!bHide);
	m_btnBPSXGAP30F.ShowWindow(!bHide);

	m_btnBPWXGAP5F.ShowWindow(!bHide);
	m_btnBPSXGAP5F.ShowWindow(!bHide);
	m_btnBPXGAP5F.ShowWindow(!bHide);
}

void CMediaCfgLogic::SetAudioFormatHide(BOOL bHide)
{
	m_radiobtnMpegAACLD.ShowWindow(!bHide);
	m_radiobtnG711A.ShowWindow(!bHide);
	m_radiobtnG711U.ShowWindow(!bHide);
	m_radiobtnG719.ShowWindow(!bHide);
	m_radiobtnG7221.ShowWindow(!bHide);
	m_radiobtnMP3.ShowWindow(!bHide);
	m_radiobtnMpegAACLC.ShowWindow(!bHide);
}

void CMediaCfgLogic::EnableMainMaxCheckBtn()
{
	if ( BST_CHECKED != m_btnHP1080P5060F.GetCheck() )
	{
		m_btnHP1080P5060F.EnableWindow(FALSE);
	}
	
	if ( BST_CHECKED != m_btnHP1080P2530F.GetCheck() )
	{
		m_btnHP1080P2530F.EnableWindow(FALSE);
	}
	
	if ( BST_CHECKED != m_btnHP720P5060F.GetCheck() )
	{
		m_btnHP720P5060F.EnableWindow(FALSE);
	}
	
	if ( BST_CHECKED != m_btnHP720P2530F.GetCheck() )
	{
		m_btnHP720P2530F.EnableWindow(FALSE);	
	}
	
	if ( BST_CHECKED != m_btnBP1080P5060F.GetCheck() )
	{
		m_btnBP1080P5060F.EnableWindow(FALSE);
	}
	
	if ( BST_CHECKED != m_btnBP1080P2530F.GetCheck() )
	{
		m_btnBP1080P2530F.EnableWindow(FALSE);
	}

	if ( BST_CHECKED != m_btnBP720P5060F.GetCheck() )
	{
		m_btnBP720P5060F.EnableWindow(FALSE);
	}

	if ( BST_CHECKED != m_btnBP720P2530F.GetCheck() )
	{
		m_btnBP720P2530F.EnableWindow(FALSE);
	}
	
	if ( BST_CHECKED != m_btnBP4CIFP25F.GetCheck() )
	{
		m_btnBP4CIFP25F.EnableWindow(FALSE);	
	}
}

void CMediaCfgLogic::EnableMinorMaxCheckBtn()
{
	if ( BST_CHECKED != m_btnHP1080P5060F.GetCheck() )
	{
		m_btnHP1080P5060F.EnableWindow(FALSE);
	}
	
	if ( BST_CHECKED != m_btnHP1080P2530F.GetCheck() )
	{
		m_btnHP1080P2530F.EnableWindow(FALSE);
	}
	
	if ( BST_CHECKED != m_btnHP720P5060F.GetCheck() )
	{
		m_btnHP720P5060F.EnableWindow(FALSE);
	}
	
	if ( BST_CHECKED != m_btnHP720P2530F.GetCheck() )
	{
		m_btnHP720P2530F.EnableWindow(FALSE);	
	}
	
	if ( BST_CHECKED != m_btnBP1080P5060F.GetCheck() )
	{
		m_btnBP1080P5060F.EnableWindow(FALSE);
	}
	
	if ( BST_CHECKED != m_btnBP1080P2530F.GetCheck() )
	{
		m_btnBP1080P2530F.EnableWindow(FALSE);
	}
	
	if ( BST_CHECKED != m_btnBP720P5060F.GetCheck() )
	{
		m_btnBP720P5060F.EnableWindow(FALSE);
	}
	
	if ( BST_CHECKED != m_btnBP720P2530F.GetCheck() )
	{
		m_btnBP720P2530F.EnableWindow(FALSE);
	}

	if ( BST_CHECKED != m_btnBP4CIFP25F.GetCheck() )
	{
		m_btnBP4CIFP25F.EnableWindow(FALSE);	
	}
	
	if ( BST_CHECKED != m_btnBPUXGAP60F.GetCheck() )
	{
		m_btnBPUXGAP60F.EnableWindow(FALSE);	
	}
	
	if ( BST_CHECKED != m_btnBPWXGAP30F.GetCheck() )
	{
		m_btnBPWXGAP30F.EnableWindow(FALSE);	
	}
	
	if ( BST_CHECKED != m_btnBPSXGAP30F.GetCheck() )
	{
		m_btnBPSXGAP30F.EnableWindow(FALSE);
	}
	
	if ( BST_CHECKED != m_btnBPWXGAP5F.GetCheck() )
	{
		m_btnBPWXGAP5F.EnableWindow(FALSE);
	}

	if ( BST_CHECKED != m_btnBPSXGAP5F.GetCheck() )
	{
		m_btnBPSXGAP5F.EnableWindow(FALSE);
	}
	
	if ( BST_CHECKED != m_btnBPXGAP5F.GetCheck() )
	{
		m_btnBPXGAP5F.EnableWindow(FALSE);
	}
}

void CMediaCfgLogic::OnBtnHP1080P5060F()
{
	CountVideoResNum();
}

void CMediaCfgLogic::OnBtnHP1080P2530F()
{
	CountVideoResNum();
}

void CMediaCfgLogic::OnBtnHP720P5060F()
{
	CountVideoResNum();
}

void CMediaCfgLogic::OnBtnHP720P2530F()
{
	CountVideoResNum();
}

void CMediaCfgLogic::OnBtnBP1080P5060F()
{
	CountVideoResNum();
}

void CMediaCfgLogic::OnBtnBP1080P2530F()
{
	CountVideoResNum();
}

void CMediaCfgLogic::OnBtnBP720P5060F()
{
	CountVideoResNum();
}

void CMediaCfgLogic::OnBtnBP720P2530F()
{
	CountVideoResNum();
}

void CMediaCfgLogic::OnBtnBP4CIFP25F()
{
	CountVideoResNum();
}

void CMediaCfgLogic::OnBtnBPUXGAP60F()
{
	CountVideoResNum();
}

void CMediaCfgLogic::OnBtnBPWXGAP30F()
{
	CountVideoResNum();
}

void CMediaCfgLogic::OnBtnBPSXGAP30F()
{
	CountVideoResNum();
}

void CMediaCfgLogic::OnBtnBPWXGAP5F()
{
	CountVideoResNum();
}

void CMediaCfgLogic::OnBtnBPSXGAP5F()
{
	CountVideoResNum();
}

void CMediaCfgLogic::OnBtnBPXGAP5F()
{
	CountVideoResNum();
}

void CMediaCfgLogic::OnRadioBtnMpegAACLD()
{
	m_radiobtnMpegAACLD.SetCheck(BST_CHECKED);
	m_radiobtnG711A.SetCheck(BST_UNCHECKED);
	m_radiobtnG711U.SetCheck(BST_UNCHECKED);
	m_radiobtnG719.SetCheck(BST_UNCHECKED);
	m_radiobtnG7221.SetCheck(BST_UNCHECKED);
	m_radiobtnMP3.SetCheck(BST_UNCHECKED);
	m_radiobtnMpegAACLC.SetCheck(BST_UNCHECKED);
	
	m_tSelTemplate.m_emTpAudioFormat = emTPAMpegAACLD;
}

void CMediaCfgLogic::OnRadioBtnG711A()
{
	m_radiobtnMpegAACLD.SetCheck(BST_UNCHECKED);
	m_radiobtnG711A.SetCheck(BST_CHECKED);
	m_radiobtnG711U.SetCheck(BST_UNCHECKED);
	m_radiobtnG719.SetCheck(BST_UNCHECKED);
	m_radiobtnG7221.SetCheck(BST_UNCHECKED);
	m_radiobtnMP3.SetCheck(BST_UNCHECKED);
	m_radiobtnMpegAACLC.SetCheck(BST_UNCHECKED);
	
	m_tSelTemplate.m_emTpAudioFormat = emTPAG711a;
}

void CMediaCfgLogic::OnRadioBtnG711U()
{
	m_radiobtnMpegAACLD.SetCheck(BST_UNCHECKED);
	m_radiobtnG711A.SetCheck(BST_UNCHECKED);
	m_radiobtnG711U.SetCheck(BST_CHECKED);
	m_radiobtnG719.SetCheck(BST_UNCHECKED);
	m_radiobtnG7221.SetCheck(BST_UNCHECKED);
	m_radiobtnMP3.SetCheck(BST_UNCHECKED);
	m_radiobtnMpegAACLC.SetCheck(BST_UNCHECKED);
	
	m_tSelTemplate.m_emTpAudioFormat = emTPAG711u;
}

void CMediaCfgLogic::OnRadioBtnG719()
{
	m_radiobtnMpegAACLD.SetCheck(BST_UNCHECKED);
	m_radiobtnG711A.SetCheck(BST_UNCHECKED);
	m_radiobtnG711U.SetCheck(BST_UNCHECKED);
	m_radiobtnG719.SetCheck(BST_CHECKED);
	m_radiobtnG7221.SetCheck(BST_UNCHECKED);
	m_radiobtnMP3.SetCheck(BST_UNCHECKED);
	m_radiobtnMpegAACLC.SetCheck(BST_UNCHECKED);
	
	m_tSelTemplate.m_emTpAudioFormat = emTPAG719;
}

void CMediaCfgLogic::OnRadioBtnG7221()
{
	m_radiobtnMpegAACLD.SetCheck(BST_UNCHECKED);
	m_radiobtnG711A.SetCheck(BST_UNCHECKED);
	m_radiobtnG711U.SetCheck(BST_UNCHECKED);
	m_radiobtnG719.SetCheck(BST_UNCHECKED);
	m_radiobtnG7221.SetCheck(BST_CHECKED);
	m_radiobtnMP3.SetCheck(BST_UNCHECKED);
	m_radiobtnMpegAACLC.SetCheck(BST_UNCHECKED);
	
	m_tSelTemplate.m_emTpAudioFormat = emTPAG7221;
}

void CMediaCfgLogic::OnRadioBtnMP3()
{
	m_radiobtnMpegAACLD.SetCheck(BST_UNCHECKED);
	m_radiobtnG711A.SetCheck(BST_UNCHECKED);
	m_radiobtnG711U.SetCheck(BST_UNCHECKED);
	m_radiobtnG719.SetCheck(BST_UNCHECKED);
	m_radiobtnG7221.SetCheck(BST_UNCHECKED);
	m_radiobtnMP3.SetCheck(BST_CHECKED);
	m_radiobtnMpegAACLC.SetCheck(BST_UNCHECKED);
	
	m_tSelTemplate.m_emTpAudioFormat = emTPAMP3;
}

void CMediaCfgLogic::OnRadioBtnMpegAACLC()
{
	m_radiobtnMpegAACLD.SetCheck(BST_UNCHECKED);
	m_radiobtnG711A.SetCheck(BST_UNCHECKED);
	m_radiobtnG711U.SetCheck(BST_UNCHECKED);
	m_radiobtnG719.SetCheck(BST_UNCHECKED);
	m_radiobtnG7221.SetCheck(BST_UNCHECKED);
	m_radiobtnMP3.SetCheck(BST_UNCHECKED);
	m_radiobtnMpegAACLC.SetCheck(BST_CHECKED);

	m_tSelTemplate.m_emTpAudioFormat = emTPAMpegAACLC;
}

LRESULT CMediaCfgLogic::OnSendTmpInfoToPage(WPARAM wParam, LPARAM lParam)
{
	m_tSelTemplate = *reinterpret_cast<TCMSConfTemplate*>(wParam);
	m_emOperateFlag = static_cast<EM_OPERATE_FLAG>(lParam);

	//经测试确认，仅在媒体配置中点击编辑时留在当前显示界面   20140508 by xhx
	if ( this->IsWindowVisible() )
	{
		if ( em_EDIT_PAGE_STATUS == m_emOperateFlag )
		{
			if ( em_CONFFORMAT_PAGE == m_emTabFlag )
			{
				OnBtnConfFormat();
			} 
			else if ( em_SHOWFORMAT_PAGE == m_emTabFlag )
			{
				OnBtnShowFormat();
			}
			else if ( em_AUDIOFORMAT_PAGE == m_emTabFlag )
			{
				OnBtnAudioFormat();
			}

			return 0L;
		}
	}

	OnBtnConfFormat();

	return 0L;
}

void CMediaCfgLogic::UpdateVedioControl(TCMSConfTemplate* pTTemplate)
{
	if ( NULL != pTTemplate )
	{
		m_btnHP1080P5060F.SetCheck(BST_UNCHECKED);
		m_btnHP1080P2530F.SetCheck(BST_UNCHECKED);
		
		m_btnHP720P5060F.SetCheck(BST_UNCHECKED);
		m_btnHP720P2530F.SetCheck(BST_UNCHECKED);
		
		m_btnBP1080P5060F.SetCheck(BST_UNCHECKED);
		m_btnBP1080P2530F.SetCheck(BST_UNCHECKED);

		m_btnBP720P5060F.SetCheck(BST_UNCHECKED);
		m_btnBP720P2530F.SetCheck(BST_UNCHECKED);

		m_btnBP4CIFP25F.SetCheck(BST_UNCHECKED);

//		if ( em_SHOWFORMAT_PAGE == m_emTabFlag )
//		{
			m_btnBPUXGAP60F.SetCheck(BST_UNCHECKED);	
			m_btnBPWXGAP30F.SetCheck(BST_UNCHECKED);
			m_btnBPSXGAP30F.SetCheck(BST_UNCHECKED);
			m_btnBPWXGAP5F.SetCheck(BST_UNCHECKED);
			m_btnBPSXGAP5F.SetCheck(BST_UNCHECKED);
			m_btnBPXGAP5F.SetCheck(BST_UNCHECKED);
//		}

		s32 nIndex = 0;
		if ( em_CONFFORMAT_PAGE == m_emTabFlag )
		{
			for ( nIndex = 0; nIndex < pTTemplate->m_wMainNum; nIndex++ )
			{
				SetMainVideoBtnStatus(pTTemplate->m_atTpMainVideoRes[nIndex]);	
			}
		}	
		
		if ( em_SHOWFORMAT_PAGE == m_emTabFlag )
		{
			for ( nIndex = 0; nIndex < pTTemplate->m_wMinorNum; nIndex++ )
			{
				SetMinorVideoBtnStatus(pTTemplate->m_atTpMinorVideoRes[nIndex]);	
			}
		}	

		m_wCheckResNum = CComInterface::GetNeedBasNum(*pTTemplate);
		UpdateResUsedCountToControl(m_wCheckResNum);
	}
}

void CMediaCfgLogic::UpdateAudioControl(TCMSConfTemplate* pTTemplate)
{
	if ( NULL != pTTemplate )
	{
		m_radiobtnMpegAACLD.SetCheck(BST_UNCHECKED);
		m_radiobtnG711A.SetCheck(BST_UNCHECKED);
		m_radiobtnG711U.SetCheck(BST_UNCHECKED);
		m_radiobtnG719.SetCheck(BST_UNCHECKED);
		m_radiobtnG7221.SetCheck(BST_UNCHECKED);
		m_radiobtnMP3.SetCheck(BST_UNCHECKED);
		m_radiobtnMpegAACLC.SetCheck(BST_UNCHECKED);

		if ( emTPAMpegAACLD == pTTemplate->m_emTpAudioFormat )
		{
			m_radiobtnMpegAACLD.SetCheck(BST_CHECKED);
		} 
		else if ( emTPAG711a == pTTemplate->m_emTpAudioFormat )
		{
			m_radiobtnG711A.SetCheck(BST_CHECKED);
		}
		else if ( emTPAG711u == pTTemplate->m_emTpAudioFormat )
		{
			m_radiobtnG711U.SetCheck(BST_CHECKED);
		}
		else if ( emTPAG719 == pTTemplate->m_emTpAudioFormat )
		{
			m_radiobtnG719.SetCheck(BST_CHECKED);
		}
		else if ( emTPAG7221 == pTTemplate->m_emTpAudioFormat )
		{
			m_radiobtnG7221.SetCheck(BST_CHECKED);
		}
		else if ( emTPAMP3 == pTTemplate->m_emTpAudioFormat )
		{
			m_radiobtnMP3.SetCheck(BST_CHECKED);
		}
		else if ( emTPAMpegAACLC == pTTemplate->m_emTpAudioFormat )
		{
			m_radiobtnMpegAACLC.SetCheck(BST_CHECKED);
		}
	}
}

void CMediaCfgLogic::SetMainVideoBtnStatus(const TUmsVidFormat& tTpMainVideoRes)
{
	if ( em_CONFFORMAT_PAGE != m_emTabFlag )
	{
		return;
	}

	if( (emTPVHD1080p1920x1080 == tTpMainVideoRes.m_emRes) && (60 == tTpMainVideoRes.m_wFrameRate)
		&& (emTPH264HP == tTpMainVideoRes.m_emQualityLvl) )
	{
		m_btnHP1080P5060F.SetCheck(BST_CHECKED);
	}

	if( (emTPVHD1080p1920x1080 == tTpMainVideoRes.m_emRes) && (30 == tTpMainVideoRes.m_wFrameRate)
		&& (emTPH264HP == tTpMainVideoRes.m_emQualityLvl) )
	{
		m_btnHP1080P2530F.SetCheck(BST_CHECKED);		
	}

	if( (emTPVHD720p1280x720 == tTpMainVideoRes.m_emRes) && (60 == tTpMainVideoRes.m_wFrameRate)
		&& (emTPH264HP == tTpMainVideoRes.m_emQualityLvl) )
	{
		m_btnHP720P5060F.SetCheck(BST_CHECKED);		
	}

	if( (emTPVHD720p1280x720 == tTpMainVideoRes.m_emRes) && (30 == tTpMainVideoRes.m_wFrameRate)
		&& (emTPH264HP == tTpMainVideoRes.m_emQualityLvl) )
	{
		m_btnHP720P2530F.SetCheck(BST_CHECKED);
	}
	
	if( (emTPVHD1080p1920x1080 == tTpMainVideoRes.m_emRes) && (60 == tTpMainVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMainVideoRes.m_emQualityLvl) )
	{
		m_btnBP1080P5060F.SetCheck(BST_CHECKED);		
	}

	if( (emTPVHD1080p1920x1080 == tTpMainVideoRes.m_emRes) && (30 == tTpMainVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMainVideoRes.m_emQualityLvl) )
	{
		m_btnBP1080P2530F.SetCheck(BST_CHECKED);		
	}
	
	if( (emTPVHD720p1280x720 == tTpMainVideoRes.m_emRes) && (60 == tTpMainVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMainVideoRes.m_emQualityLvl) )
	{
		m_btnBP720P5060F.SetCheck(BST_CHECKED);
	}

	if( (emTPVHD720p1280x720 == tTpMainVideoRes.m_emRes) && (30 == tTpMainVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMainVideoRes.m_emQualityLvl) )
	{
		m_btnBP720P2530F.SetCheck(BST_CHECKED);		
	}
	
	if( (emTPV4CIF == tTpMainVideoRes.m_emRes) && (25 == tTpMainVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMainVideoRes.m_emQualityLvl) )
	{
		m_btnBP4CIFP25F.SetCheck(BST_CHECKED);		
	}
}

void CMediaCfgLogic::SetMinorVideoBtnStatus(const TUmsVidFormat& tTpMinorVideoRes)
{
	if ( em_SHOWFORMAT_PAGE != m_emTabFlag )
	{
		return;
	}

	if( (emTPVHD1080p1920x1080 == tTpMinorVideoRes.m_emRes) && (60 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264HP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		m_btnHP1080P5060F.SetCheck(BST_CHECKED);
	}

	if( (emTPVHD1080p1920x1080 == tTpMinorVideoRes.m_emRes) && (30 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264HP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		m_btnHP1080P2530F.SetCheck(BST_CHECKED);		
	}

	if( (emTPVHD720p1280x720 == tTpMinorVideoRes.m_emRes) && (60 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264HP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		m_btnHP720P5060F.SetCheck(BST_CHECKED);		
	}

	if( (emTPVHD720p1280x720 == tTpMinorVideoRes.m_emRes) && (30 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264HP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		m_btnHP720P2530F.SetCheck(BST_CHECKED);
	}
	
	if( (emTPVHD1080p1920x1080 == tTpMinorVideoRes.m_emRes) && (60 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		m_btnBP1080P5060F.SetCheck(BST_CHECKED);		
	}
	
	if( (emTPVHD1080p1920x1080 == tTpMinorVideoRes.m_emRes) && (30 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		m_btnBP1080P2530F.SetCheck(BST_CHECKED);		
	}
	
	if( (emTPVHD720p1280x720 == tTpMinorVideoRes.m_emRes) && (60 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		m_btnBP720P5060F.SetCheck(BST_CHECKED);
	}

	if( (emTPVHD720p1280x720 == tTpMinorVideoRes.m_emRes) && (30 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		m_btnBP720P2530F.SetCheck(BST_CHECKED);		
	}
	
	if( (emTPV4CIF == tTpMinorVideoRes.m_emRes) && (25 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		m_btnBP4CIFP25F.SetCheck(BST_CHECKED);		
	}

	if( (emTPVGA1600x1200 == tTpMinorVideoRes.m_emRes) && (60 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		m_btnBPUXGAP60F.SetCheck(BST_CHECKED);	
	}

	if( (emTPVGA1280x800 == tTpMinorVideoRes.m_emRes) && (30 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		m_btnBPWXGAP30F.SetCheck(BST_CHECKED);			
	}

	if( (emTPVGA1280x1024 == tTpMinorVideoRes.m_emRes) && (30 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		m_btnBPSXGAP30F.SetCheck(BST_CHECKED);			
	}

	if( (emTPVGA1280x800 == tTpMinorVideoRes.m_emRes) && (5 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		m_btnBPWXGAP5F.SetCheck(BST_CHECKED);			
	}

	if( (emTPVGA1280x1024 == tTpMinorVideoRes.m_emRes) && (5 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		m_btnBPSXGAP5F.SetCheck(BST_CHECKED);			
	}

	if( (emTPVGA1024x768 == tTpMinorVideoRes.m_emRes) && (5 == tTpMinorVideoRes.m_wFrameRate)
		&& (emTPH264BP == tTpMinorVideoRes.m_emQualityLvl) )
	{
		m_btnBPXGAP5F.SetCheck(BST_CHECKED);			
	}
}

LRESULT CMediaCfgLogic::OnConfTmpResUsedCountNotify(WPARAM wParam, LPARAM lParam)
{
	u16* wUsedCount = (u16*)(wParam);
	if ( NULL != wUsedCount )
	{
		s8 chUsedCount[8];
		memset( chUsedCount, 0, 8 );
		itoa( *wUsedCount, chUsedCount, 10 );
		m_wAllResCount = *wUsedCount;

		if ( m_wAllResCount == 0 )
		{
//			m_stAdaptRes.SetWindowText("");
//			m_stAllRes.SetWindowText("");
			m_stAllAdaptResCount.SetWindowText("0"); //ln确认显示"0" -- 20140703
		}
		else
		{
//			m_stAdaptRes.SetWindowText("会议所需适配资源数  ");
//			m_stAllRes.SetWindowText("总适配资源数  ");
			//CString strResCont = " / ";
			CString strResCont /*+*/= chUsedCount;
			m_stAllAdaptResCount.SetWindowText(strResCont);
		}

		UpdateResUsedCountToControl(m_wCheckResNum);
	}

	if ( m_wAllResCount == 0 )
	{
		m_btnHP1080P5060F.SetButtonStyle( BS_AUTORADIOBUTTON );
		m_btnHP1080P2530F.SetButtonStyle( BS_AUTORADIOBUTTON );
		
		m_btnHP720P5060F.SetButtonStyle( BS_AUTORADIOBUTTON );
		m_btnHP720P2530F.SetButtonStyle( BS_AUTORADIOBUTTON );
		
		m_btnBP1080P5060F.SetButtonStyle( BS_AUTORADIOBUTTON );
		m_btnBP1080P2530F.SetButtonStyle( BS_AUTORADIOBUTTON );
		
		m_btnBP720P5060F.SetButtonStyle( BS_AUTORADIOBUTTON );
		m_btnBP720P2530F.SetButtonStyle( BS_AUTORADIOBUTTON );

		m_btnBP4CIFP25F.SetButtonStyle( BS_AUTORADIOBUTTON );

		m_btnBPUXGAP60F.SetButtonStyle( BS_AUTORADIOBUTTON );
		m_btnBPWXGAP30F.SetButtonStyle( BS_AUTORADIOBUTTON );
		m_btnBPSXGAP30F.SetButtonStyle( BS_AUTORADIOBUTTON );

		m_btnBPWXGAP5F.SetButtonStyle( BS_AUTORADIOBUTTON );
		m_btnBPSXGAP5F.SetButtonStyle( BS_AUTORADIOBUTTON );
		m_btnBPXGAP5F.SetButtonStyle( BS_AUTORADIOBUTTON );
	}
	else
	{
		m_btnHP1080P5060F.SetButtonStyle( BS_AUTOCHECKBOX );
		m_btnHP1080P2530F.SetButtonStyle( BS_AUTOCHECKBOX );
		
		m_btnHP720P5060F.SetButtonStyle( BS_AUTOCHECKBOX );
		m_btnHP720P2530F.SetButtonStyle( BS_AUTOCHECKBOX );
		
		m_btnBP1080P5060F.SetButtonStyle( BS_AUTOCHECKBOX );
		m_btnBP1080P2530F.SetButtonStyle( BS_AUTOCHECKBOX );

		m_btnBP720P5060F.SetButtonStyle( BS_AUTOCHECKBOX );
		m_btnBP720P2530F.SetButtonStyle( BS_AUTOCHECKBOX );

		m_btnBP4CIFP25F.SetButtonStyle( BS_AUTOCHECKBOX );

		m_btnBPUXGAP60F.SetButtonStyle( BS_AUTOCHECKBOX );
		m_btnBPWXGAP30F.SetButtonStyle( BS_AUTOCHECKBOX );
		m_btnBPSXGAP30F.SetButtonStyle( BS_AUTOCHECKBOX );

		m_btnBPWXGAP5F.SetButtonStyle( BS_AUTOCHECKBOX );
		m_btnBPSXGAP5F.SetButtonStyle( BS_AUTOCHECKBOX );
		m_btnBPXGAP5F.SetButtonStyle( BS_AUTOCHECKBOX );
	}

	return S_OK;
}

void CMediaCfgLogic::UpdateResUsedCountToControl( u16 wResNum )
{
	//ln确认 -- 20140711
// 	if ( m_wAllResCount == 0 )
// 	{
// 		m_stResCount.SetWindowText(" 0");
// 		return;
// 	}

	CString strText;
	char chNum[10];
	memset( chNum, 0, 10 );
 	itoa( wResNum , chNum, 10 );
	if ( strlen(chNum) <= 1 )
	{
		strText += " ";
	}
	strText += chNum;
	m_stResCount.SetWindowText(strText);

	if ( m_wAllResCount < wResNum )
	{
		m_stResCount.SetTextColor(Color(255,0,0));
	}
	else
	{
		m_stResCount.SetTextColor(Color( 0, 114, 255 ));
	}
}


