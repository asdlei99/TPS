// vediorecordlogic.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "vediorecordlogic.h"
#include "videorecordshowopt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern float CUR_SCREEN_WIDTH_PER;  //屏幕宽度比率
extern float CUR_SCREEN_HEIGHT_PER; //屏幕高度比率

/////////////////////////////////////////////////////////////////////////////
// CVedioRecordLogic dialog

int g_nTime = 0;
CVedioRecordLogic::CVedioRecordLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CVedioRecordLogic::IDD, pParent)
{
	m_pListMeeting = NULL;
	m_pLetterIndex = NULL;
	m_pVTRCtrlIF = NULL;
	m_pconfCtrlIF = NULL;
	m_pVideoRecordEpLogic = NULL;
	m_pListVedioFile = NULL;
	m_emCurrentWnd = emCurrentWndMain;
	m_pProgressPlay = NULL;
	m_pCVedioRecordNameEditLogic = NULL;
}


void CVedioRecordLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVedioRecordLogic)
	DDX_Control(pDX, IDC_BUTTON_VTR_RECORD_RESUME, m_btnRecordResume);
	DDX_Control(pDX, IDC_BUTTON_VTR_PALYBACK_RESUME, m_btnPlayResume);
	DDX_Control(pDX, IDC_STATIC_VTR_PALYBACK_PROGRESSINFO, m_stcPlayProgress);
	DDX_Control(pDX, IDC_EDIT_Search_Play, m_edtSearchPlay);
	DDX_Control(pDX, IDC_BTN_SHOW_HP1080P60fps, m_radiobtnHP1080P60fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_HP1080P50fps, m_radiobtnHP1080P50fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_HP1080P30fps, m_radiobtnHP1080P30fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_HP1080P25fps, m_radiobtnHP1080P25fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_HP720P60fps, m_radiobtnHP720P60fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_HP720P50fps, m_radiobtnHP720P50fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_HP720P30fps, m_radiobtnHP720P30fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_HP720P25fps, m_radiobtnHP720P25fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_BP1080P60fps, m_radiobtnBP1080P60fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_BP1080P50fps, m_radiobtnBP1080P50fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_BP1080P30fps, m_radiobtnBP1080P30fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_BP1080P25fps, m_radiobtnBP1080P25fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_BP720P60fps, m_radiobtnBP720P60fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_BP720P50fps, m_radiobtnBP720P50fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_BP720P30fps, m_radiobtnBP720P30fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_BP720P25fps, m_radiobtnBP720P25fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_BP4CIF25fps, m_radiobtnBP4CIF25fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_BPUXGA60fps, m_radiobtnBPUXGA60fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_BPWXGA30fps, m_radiobtnBPWXGA30fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_BPSXGA30fps, m_radiobtnBPSXGA30fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_BPWXGA5fps, m_radiobtnBPWXGA5fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_BPSXGA5fps, m_radiobtnBPSXGA5fpsShow);
	DDX_Control(pDX, IDC_BTN_SHOW_BPXGA5fps, m_radiobtnBPXGA5fpsShow);
	DDX_Control(pDX, IDC_BTN_CONF_HP1080P60fps, m_radiobtnHP1080P60fps);
	DDX_Control(pDX, IDC_BTN_CONF_HP1080P50fps, m_radiobtnHP1080P50fps);
	DDX_Control(pDX, IDC_BTN_CONF_HP1080P30fps, m_radiobtnHP1080P30fps);
	DDX_Control(pDX, IDC_BTN_CONF_HP1080P25fps, m_radiobtnHP1080P25fps);
	DDX_Control(pDX, IDC_BTN_CONF_HP720P60fps, m_radiobtnHP720P60fps);
	DDX_Control(pDX, IDC_BTN_CONF_HP720P50fps, m_radiobtnHP720P50fps);
	DDX_Control(pDX, IDC_BTN_CONF_HP720P30fps, m_radiobtnHP720P30fps);
	DDX_Control(pDX, IDC_BTN_CONF_HP720P25fps, m_radiobtnHP720P25fps);
	DDX_Control(pDX, IDC_BTN_CONF_BP1080P60fps, m_radiobtnBP1080P60fps);
	DDX_Control(pDX, IDC_BTN_CONF_BP1080P50fps, m_radiobtnBP1080P50fps);
	DDX_Control(pDX, IDC_BTN_CONF_BP1080P30fps, m_radiobtnBP1080P30fps);
	DDX_Control(pDX, IDC_BTN_CONF_BP1080P25fps, m_radiobtnBP1080P25fps);
	DDX_Control(pDX, IDC_BTN_CONF_BP720P60fps, m_radiobtnBP720P60fps);
	DDX_Control(pDX, IDC_BTN_CONF_BP720P50fps, m_radiobtnBP720P50fps);
	DDX_Control(pDX, IDC_BTN_CONF_BP720P30fps, m_radiobtnBP720P30fps);
	DDX_Control(pDX, IDC_BTN_CONF_BP720P25fps, m_radiobtnBP720P25fps);
	DDX_Control(pDX, IDC_BTN_CONF_BP4CIF25fps, m_radiobtnBP4CIF25fps);
	DDX_Control(pDX, IDC_BUTTON_VTR_PALYBACK_START, m_btnPlayStart);
	DDX_Control(pDX, IDC_STATIC_VTR_PALYBACK, m_stcPlay);
	DDX_Control(pDX, IDC_STATIC_H264, m_stcH264);
	DDX_Control(pDX, IDC_EDIT_PLAY_CHOOSE, m_edtPlayChoose);
	DDX_Control(pDX, IDC_BUTTON_VTR_PLAYBACK_SWITCH, m_btnPlaySwitch);
	DDX_Control(pDX, IDC_BUTTON_VTR_PALYBACK_STOP, m_btnPlayStop);
	DDX_Control(pDX, IDC_BUTTON_VTR_PALYBACK_FINISH, m_btnPlayFinish);
	DDX_Control(pDX, IDC_BUTTON_PLAY_CHOOSE, m_btnPlayChoose);
	DDX_Control(pDX, IDC_BUTTON_CHILD_BACK, m_btnChildBack);
	DDX_Control(pDX, IDC_BUTTON_VTR_RECORD_START, m_btnRecordStart);
	DDX_Control(pDX, IDC_BUTTON_VTR_RECORD_FINISH, m_btnRecordFinish);
	DDX_Control(pDX, IDC_BUTTON_VTR_RECORD_STOP, m_btnRecordStop);
	DDX_Control(pDX, IDC_STATIC_VTR_RECORD_TIME_REAL, m_stcRecordTimeReal);
	DDX_Control(pDX, IDC_STATIC_VTR_RECORD_TIME, m_stcRecordTime);
	DDX_Control(pDX, IDC_BUTTON_SHOW_TYPE, m_btnShowType);
	DDX_Control(pDX, IDC_BUTTON_CONF_TYPE, m_btnConfType);
	DDX_Control(pDX, IDC_EDIT_SHOW_TYPE, m_edtShowType);
	DDX_Control(pDX, IDC_EDIT_CONF_TYPE, m_edtConfType);
	DDX_Control(pDX, IDC_STATIC_SHOW_TYPE, m_stcShowType);
	DDX_Control(pDX, IDC_STATIC_CONF_TYPE, m_stcConfType);
	DDX_Control(pDX, IDC_BUTTON_VTR_RECORD_SWITCH, m_btnSwitch);
	DDX_Control(pDX, IDC_STATIC_VTR_RECORD_DOUBLE_CURRENT, m_stcDoubleCurrent);
	DDX_Control(pDX, IDC_BUTTON_RECORD_RETURN, m_btnReturn);
	DDX_Control(pDX, IDC_EDIT_Search, m_sedtSearch);
 	DDX_Control(pDX, IDC_STATIC_CHILDWNDTITLE, m_stcChildWndTitle);
 	DDX_Control(pDX, IDC_STATIC_CHILDFRMRIGHT, m_stcChildFrmRight);
 	DDX_Control(pDX, IDC_STATIC_CHILDFRMLEFT, m_stcChildFrmLeft);
 	DDX_Control(pDX, IDC_STATIC_Title, m_stcTitle);
	DDX_Control(pDX, IDC_BUTTON_ShowEx, m_btnShowEx);
	DDX_Control(pDX, IDC_STATIC_REC_FILENAME, m_stcRecFileName);
	DDX_Control(pDX, IDC_STATIC_REC_FILENAME_REAL, m_stcRecFileNameReal);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVedioRecordLogic, CDlgChild)
	//{{AFX_MSG_MAP(CVedioRecordLogic)
	ON_BN_CLICKED(IDC_BUTTON_RECORD_RETURN, OnButtonRecordReturn)
	ON_BN_CLICKED(IDC_BUTTON_VTR_RECORD_START, OnButtonVtrRecordStart)
	ON_BN_CLICKED(IDC_BUTTON_VTR_RECORD_STOP, OnButtonVtrRecordStop)
	ON_BN_CLICKED(IDC_BUTTON_VTR_RECORD_FINISH, OnButtonVtrRecordFinish)
	ON_BN_CLICKED(IDC_BUTTON_CONF_TYPE, OnButtonConfType)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_TYPE, OnButtonShowType)
	ON_BN_CLICKED(IDC_BUTTON_CHILD_BACK, OnButtonChildBack)

	ON_BN_CLICKED(IDC_BTN_CONF_HP1080P60fps, OnBUTTONCONFHP1080P60fps)
	ON_BN_CLICKED(IDC_BTN_CONF_HP1080P50fps, OnBUTTONCONFHP1080P50fps)
	ON_BN_CLICKED(IDC_BTN_CONF_HP1080P30fps, OnBUTTONCONFHP1080P30fps)
	ON_BN_CLICKED(IDC_BTN_CONF_HP1080P25fps, OnBUTTONCONFHP1080P25fps)
	ON_BN_CLICKED(IDC_BTN_CONF_HP720P60fps, OnBUTTONCONFHP720P60fps)
	ON_BN_CLICKED(IDC_BTN_CONF_HP720P50fps, OnBUTTONCONFHP720P50fps)
	ON_BN_CLICKED(IDC_BTN_CONF_HP720P30fps, OnBUTTONCONFHP720P30fps)
	ON_BN_CLICKED(IDC_BTN_CONF_HP720P25fps, OnBUTTONCONFHP720P25fps)
	ON_BN_CLICKED(IDC_BTN_CONF_BP1080P60fps, OnBUTTONCONFBP1080P60fps)
	ON_BN_CLICKED(IDC_BTN_CONF_BP1080P50fps, OnBUTTONCONFBP1080P50fps)
	ON_BN_CLICKED(IDC_BTN_CONF_BP1080P30fps, OnBUTTONCONFBP1080P30fps)
	ON_BN_CLICKED(IDC_BTN_CONF_BP1080P25fps, OnBUTTONCONFBP1080P25fps)
	ON_BN_CLICKED(IDC_BTN_CONF_BP720P60fps, OnBUTTONCONFBP720P60fps)
	ON_BN_CLICKED(IDC_BTN_CONF_BP720P50fps, OnBUTTONCONFBP720P50fps)
	ON_BN_CLICKED(IDC_BTN_CONF_BP720P30fps, OnBUTTONCONFBP720P30fps)
	ON_BN_CLICKED(IDC_BTN_CONF_BP720P25fps, OnBUTTONCONFBP720P25fps)
	ON_BN_CLICKED(IDC_BTN_CONF_BP4CIF25fps, OnBUTTONCONFBP4CIF25fps)

	ON_MESSAGE(WM_BUTTON_CLICK, OnButtonSwitch)

	ON_BN_CLICKED(IDC_BTN_SHOW_HP1080P60fps, OnBUTTONSHOWHP1080P60fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_HP1080P50fps, OnBUTTONSHOWHP1080P50fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_HP1080P30fps, OnBUTTONSHOWHP1080P30fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_HP1080P25fps, OnBUTTONSHOWHP1080P25fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_HP720P60fps, OnBUTTONSHOWHP720P60fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_HP720P50fps, OnBUTTONSHOWHP720P50fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_HP720P30fps, OnBUTTONSHOWHP720P30fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_HP720P25fps, OnBUTTONSHOWHP720P25fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_BP1080P60fps, OnBUTTONSHOWBP1080P60fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_BP1080P50fps, OnBUTTONSHOWBP1080P50fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_BP1080P30fps, OnBUTTONSHOWBP1080P30fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_BP1080P25fps, OnBUTTONSHOWBP1080P25fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_BP720P60fps, OnBUTTONSHOWBP720P60fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_BP720P50fps, OnBUTTONSHOWBP720P50fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_BP720P30fps, OnBUTTONSHOWBP720P30fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_BP720P25fps, OnBUTTONSHOWBP720P25fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_BP4CIF25fps, OnBUTTONSHOWBP4CIF25fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_BPUXGA60fps, OnBUTTONSHOWBPUXGA60fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_BPWXGA30fps, OnBUTTONSHOWBPWXGA30fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_BPSXGA30fps, OnBUTTONSHOWBPSXGA30fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_BPWXGA5fps, OnBUTTONSHOWBPWXGA5fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_BPSXGA5fps, OnBUTTONSHOWBPSXGA5fps)
	ON_BN_CLICKED(IDC_BTN_SHOW_BPXGA5fps, OnBUTTONSHOWBPXGA5fps)
	
	ON_BN_CLICKED(IDC_BUTTON_VTR_PALYBACK_START, OnButtonVtrPalybackStart)
	ON_BN_CLICKED(IDC_BUTTON_PLAY_CHOOSE, OnButtonPlayChoose)
	ON_MESSAGE( WM_EDIT_CHANGED, OnUpdateEDITSearch )
	ON_BN_CLICKED(IDC_BUTTON_VTR_PALYBACK_RESUME, OnButtonVtrPalybackResume)
	ON_MESSAGE( UI_UMSTOOL_REC_FILE_LIST_INFO_NTY, OnRecFileListInfoNty )
	ON_MESSAGE( UI_UMSTOOL_REC_CONF_REC_INFO_NTY, OnRecConfRecInfoNty )
	ON_MESSAGE( UI_UMSTOOL_REC_CONF_PLAY_INFO_NTY, OnRecConfPlayInfoNty )
	ON_MESSAGE( UI_UMS_REFRESH_CONF_LIST, OnRefreshConfListNty )
	ON_MESSAGE( UI_UMSTOOL_REC_START_CONF_RSP, OnRecStartConfRsp )
	ON_MESSAGE( UI_UMSTOOL_REC_STOP_CONF_RSP, OnRecStopRecordRsp )
	ON_MESSAGE( UI_UMSTOOL_REC_PAUSE_CONF_RSP, OnRecPauseRecordRsp )
	ON_MESSAGE( UI_UMSTOOL_REC_RESUME_CONF_RSP, OnRecResumeRecordRsp )
	ON_MESSAGE( UI_UMSTOOL_START_PLAY_RSP, OnRecStartPlayRsp )
	ON_MESSAGE( UI_UMSTOOL_RESUME_PLAY_RSP, OnRecResumePlayRsp )
	ON_MESSAGE( UI_UMSTOOL_PAUSE_PLAY_RSP, OnRecPausePlayRsp )
	ON_MESSAGE( UI_UMSTOOL_STOP_PLAY_RSP, OnRecStopPlayRsp )
	ON_MESSAGE( UI_UMS_REFRESH_CONFCNS_LIST, OnRefreshConfCnsList )
	ON_MESSAGE( WM_TIMER, OnTimer )
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_VTR_RECORD_RESUME, OnButtonVtrRecordResume)
	ON_BN_CLICKED(IDC_BUTTON_VTR_PALYBACK_STOP, OnButtonPlayPause)
	ON_BN_CLICKED(IDC_BUTTON_VTR_PALYBACK_FINISH, OnButtonPlayFinish)
	ON_MESSAGE( WM_DEF_HIDE_LOSEFOCUSHIDER_SHOWOPT, OnHideOptn )
	ON_MESSAGE( UI_UMSTOOL_SHOWOPT_NTY, OnShowOptNty )
	ON_MESSAGE( WM_LST_UN_SELECT_ITEM,  OnNoSelResultNotify )
	ON_MESSAGE( UI_UMSTOOL_VTR_REG_STATE_NTY,  OnVtrRegStateNty )
	ON_MESSAGE( UI_UMSTOOL_REC_MDY_FILE_RSP, OnRecMdyFileRsp )	
	ON_MESSAGE(WM_EDIT_SETFOCUS, OnEditSetFocus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVedioRecordLogic message handlers
void CVedioRecordLogic::RegisterFun()
{
	REG_MSG_HANDLER( _T("CVedioRecordLogic::OnClickConfListItem"), CVedioRecordLogic::OnClickConfListItem, this, CVedioRecordLogic );
	REG_MSG_HANDLER( _T("CVedioRecordLogic::OnClickConfListItemIcon"), CVedioRecordLogic::OnClickConfListItemIcon, this, CVedioRecordLogic );
	REG_MSG_HANDLER( _T("CVedioRecordLogic::OnClickVedioFileLstItem"), CVedioRecordLogic::OnClickVedioFileLstItem, this, CVedioRecordLogic );
	REG_MSG_HANDLER( _T("CVedioRecordLogic::OnClickVedioFileLstItemIcon"), CVedioRecordLogic::OnClickVedioFileLstItemIcon, this, CVedioRecordLogic );
	REG_MSG( UI_UMSTOOL_REC_FILE_LIST_INFO_NTY, GetSafeHwnd() );
	REG_MSG( UI_UMSTOOL_REC_CONF_REC_INFO_NTY, GetSafeHwnd() );
	REG_MSG( UI_UMSTOOL_REC_CONF_PLAY_INFO_NTY, GetSafeHwnd() );
	REG_MSG( UI_UMS_REFRESH_CONF_LIST, GetSafeHwnd() );
	REG_MSG( UI_UMSTOOL_REC_START_CONF_RSP, GetSafeHwnd() );
	REG_MSG( UI_UMSTOOL_REC_STOP_CONF_RSP, GetSafeHwnd() );
	REG_MSG( UI_UMSTOOL_REC_PAUSE_CONF_RSP, GetSafeHwnd() );
	REG_MSG( UI_UMSTOOL_REC_RESUME_CONF_RSP, GetSafeHwnd() );
	REG_MSG( UI_UMSTOOL_START_PLAY_RSP, GetSafeHwnd() );
	REG_MSG( UI_UMSTOOL_RESUME_PLAY_RSP, GetSafeHwnd() );
	REG_MSG( UI_UMSTOOL_PAUSE_PLAY_RSP, GetSafeHwnd() );
	REG_MSG( UI_UMSTOOL_STOP_PLAY_RSP, GetSafeHwnd() );
	REG_MSG( UI_UMS_REFRESH_CONFCNS_LIST, GetSafeHwnd() );
	REG_MSG( WM_DEF_HIDE_LOSEFOCUSHIDER_SHOWOPT, GetSafeHwnd() );	
	REG_MSG( UI_UMSTOOL_SHOWOPT_NTY, GetSafeHwnd() );	
	REG_MSG( UI_UMSTOOL_VTR_REG_STATE_NTY, GetSafeHwnd() );
	REG_MSG( UI_UMSTOOL_REC_MDY_FILE_RSP, GetSafeHwnd() );
}

BOOL CVedioRecordLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();
	
	RegisterFun();               //注册函数
	if ( !InitControlPane() )    //初始化页面控件
	{ 
		return FALSE;
	}
	if( !InitChildWindow() )
	{
		return FALSE;
	}

	if( m_pVTRCtrlIF == NULL )
    {
        BUSINESSIFPTR->GetCtrlInterface(&m_pVTRCtrlIF);
    }
	if( m_pconfCtrlIF == NULL )
    {
        BUSINESSIFPTR->GetCtrlInterface(&m_pconfCtrlIF);
    }

	if ( m_pVideoRecordEpLogic->GetSafeHwnd() )
	{
		m_pVideoRecordEpLogic->InitDlg();
	}

	SetTimer( 5678, 1000, NULL );

	return TRUE;
}

BOOL CVedioRecordLogic::InitChildWindow()
{
	try
	{
		if ( m_pVideoRecordEpLogic == NULL)
		{
			m_pVideoRecordEpLogic = new CVideoRecordEpLogic;
			m_pVideoRecordEpLogic->Create( IDD_DIALOG_VIDEORECORD_EP, this); 
			m_pVideoRecordEpLogic->SetWindowPos( NULL, 0, 0, 1226*CUR_SCREEN_WIDTH_PER, 600*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW);
		}
		
		return TRUE;
	}
	catch (CException* e)
	{
		s8 chErr[1024];
		memset( chErr, 0, 1024 );
		e->GetErrorMessage( chErr,1024 );
		CString strErr;
		strErr += "文件操作失败，错误码";
		strErr += chErr;
		MESSAGEWND( strErr );
		return FALSE;
	}
}

void CVedioRecordLogic::OnDestroy() 
{
	CDlgChild::OnDestroy();

	SAFE_RELEASE(m_pListMeeting);
	SAFE_RELEASE(m_pLetterIndex);
	SAFE_RELEASE(m_pListVedioFile);

	if ( m_pVideoRecordEpLogic->GetSafeHwnd() )
	{
		m_pVideoRecordEpLogic->DestroyWindow();
		SAFE_RELEASE(m_pVideoRecordEpLogic);
	}

	KillTimer( 5678 );

	CVideoRecordShowOpt::Clean();
}


BOOL CVedioRecordLogic::InitControlPane()
{
	CRect rectClient;
	this->GetClientRect(&rectClient);


	CUmcwebCommon::SetImgForTransSearchEdit(&m_edtSearchPlay);
	m_edtSearchPlay.SetWindowPos( NULL, 708*CUR_SCREEN_WIDTH_PER, 53*CUR_SCREEN_HEIGHT_PER, 504, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	
	
	m_btnReturn.SetImage( IDR_PNG_BTN_RETURN, IDR_PNG_BTN_RETURNDOWN, IDR_PNG_BTN_RETURN );
	m_btnReturn.SetWindowPos( NULL, 9*CUR_SCREEN_WIDTH_PER,  6*CUR_SCREEN_HEIGHT_PER, 66, 36, SWP_SHOWWINDOW );
	
	
	CUmcwebCommon::SetTextTransStatic( &m_stcChildWndTitle, _T("录像和回放设置") , 14, Color( 24, 25, 27 ) );
	m_stcChildWndTitle.SetWindowPos( NULL, (690 + 18)*CUR_SCREEN_WIDTH_PER, 14*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransStatic( &m_stcTitle, _T("录像和回放") , 14, Color( 24, 25, 27 ) );
	m_stcTitle.	SetWindowPos( NULL, (17+70)*CUR_SCREEN_WIDTH_PER,  14*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	
	m_btnShowEx.SetImage( IDR_PNG_ADDREDITWND_ADDRSHOWEX_SEL, IDR_PNG_ADDREDITWND_ADDRSHOWEX_DOWN, NULL,
        IDR_PNG_ADDREDITWND_ADDRSHOWEX_UNSEL,IDR_PNG_ADDREDITWND_ADDRSHOWEX_DOWN, NULL);
	m_btnShowEx.SetBindWnd( CVideoRecordShowOpt::GetDlgPtr()->GetSafeHwnd() );
	m_btnShowEx.SetWindowPos( NULL, (690-8-48)*CUR_SCREEN_WIDTH_PER, 6*CUR_SCREEN_HEIGHT_PER, 48*CUR_SCREEN_WIDTH_PER, 37*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );


	CUmcwebCommon::SetImgForTransSearchEdit(&m_sedtSearch);
	

	//会议列表加入
	m_pListMeeting = new CListChild( "", CRect(12, 100, (690 - 60)+12, 488+100), this, "", GETUNIQID, WS_CHILD );
	if ( NULL != m_pListMeeting )
	{
		m_pListMeeting->SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 100*CUR_SCREEN_HEIGHT_PER, (690 - 60)*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
		m_pListMeeting->SetImage( IDR_PNG_LIST_TOPLEFT, IDR_PNG_LIST_TOPCEN, IDR_PNG_LIST_TOPRIGHT, IDR_PNG_LIST_CENLEFT, IDR_PNG_LIST_CENRIGHT,
			IDR_PNG_LIST_BTLEFT, IDR_PNG_LIST_BTCEN, IDR_PNG_LIST_BTRIGHT, IDR_PNG_LIST_TOPCEN, "PNG" );
        m_pListMeeting->SetSliderImage( IDR_PNG_LISTSLIDER_NORMALTOP, IDR_PNG_LISTSLIDER_NORMALMIDDLE, IDR_PNG_LISTSLIDER_NORMALBOTTOM, IDR_PNG_LISTSLIDER_DOWNTOP, 
            IDR_PNG_LISTSLIDER_DOWNMIDDLE, IDR_PNG_LISTSLIDER_DOWNBOTTOM, IDR_PNG_LISTSLIDER_BKGTOP, IDR_PNG_LISTSLIDER_BKGMIDDLE, IDR_PNG_LISTSLIDER_BKGBOTTOM, "PNG" );
        m_pListMeeting->SetSliderAlwaysShow( TRUE );

		m_pLetterIndex = new CLetterIndex( "Letter", "Letter", CRect( 0, 0, 39, 486 ), this, GETUNIQID, WS_CHILD );
		if ( m_pLetterIndex != NULL )
		{
			CUmcwebCommon::SetImgForLetter(m_pLetterIndex);
			m_pLetterIndex->SetLetterHeight(18*CUR_SCREEN_HEIGHT_PER);
			m_pLetterIndex->SetBindList( m_pListMeeting );

			m_pListMeeting->GetWindowRect(&rectClient);
			ScreenToClient( &rectClient );

			m_sedtSearch.SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 53*CUR_SCREEN_HEIGHT_PER, rectClient.right-12, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
			
			rectClient.left = rectClient.right - 3;
			rectClient.right = rectClient.left + 7;
			m_pListMeeting->SetSliderRect( rectClient );
			
			m_pLetterIndex->SetWindowPos( NULL, rectClient.right + 2*CUR_SCREEN_WIDTH_PER, 100*CUR_SCREEN_HEIGHT_PER, 39*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER,SWP_SHOWWINDOW );	
		}
	}


	//录像和回访设置
	CUmcwebCommon::SetTextTransStatic( &m_stcDoubleCurrent, _T("录制演示") , 13, Color( 46, 55, 76 ) );
	m_stcDoubleCurrent.	SetWindowPos( NULL, 708*CUR_SCREEN_WIDTH_PER,  75*CUR_SCREEN_HEIGHT_PER, 300*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	
	m_btnSwitch.SetImage( IDR_PNG_LOGINWND_BTN_ON, IDR_PNG_LOGINWND_BTN_ONDOWN, IDR_PNG_LOGINWND_BTN_ONDIS,
        IDR_PNG_LOGINWND_BTN_OFF,IDR_PNG_LOGINWND_BTN_OFFDOWN, IDR_PNG_LOGINWND_BTN_OFFDIS);
	
	m_btnSwitch.SetWindowPos( NULL, (1226 - 11 - 113)*CUR_SCREEN_WIDTH_PER, 67*CUR_SCREEN_HEIGHT_PER, 113*CUR_SCREEN_WIDTH_PER, 37*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransStatic( &m_stcConfType, _T("会议格式") , 13, Color( 46, 55, 76 ) );
	m_stcConfType.SetWindowPos( NULL, 708*CUR_SCREEN_WIDTH_PER,  (75+20+33)*CUR_SCREEN_HEIGHT_PER, 300*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	
	m_edtConfType.SetImage( IDR_PNG_BTN_EDITMEDIALEFT, IDR_PNG_BTN_EDITMEDIAMID, IDR_PNG_BTN_EDITMEDIAMID,
		IDR_PNG_BTN_EDITMEDIALEFT, IDR_PNG_BTN_EDITMEDIAMID, IDR_PNG_BTN_EDITMEDIAMID,
		IDR_PNG_BTN_EDITMEDIALEFT, IDR_PNG_BTN_EDITMEDIAMID, IDR_PNG_BTN_EDITMEDIAMID,
		0, 0 , 0);
	m_edtConfType.SetWindowText("");
	m_edtConfType.EnableWindow(FALSE);
	m_edtConfType.SetDisableColor( Color(46, 55, 76) );
	m_edtConfType.SetDisableImg(FALSE);
	
	m_btnConfType.SetImage( IDR_PNG_BTN_EDITMEDIARIGHT, IDR_PNG_BTN_EDITMEDIARIGHT_DOWN, IDR_PNG_BTN_EDITMEDIARIGHT );
	m_edtConfType.SetWindowPos( NULL, (690+125)*CUR_SCREEN_WIDTH_PER, (67+37+15)*CUR_SCREEN_HEIGHT_PER, (393-41)*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnConfType.SetWindowPos( NULL, (690+125+393-41)*CUR_SCREEN_WIDTH_PER, (67+37+15)*CUR_SCREEN_HEIGHT_PER, 41*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransStatic( &m_stcShowType, _T("演示格式") , 13, Color( 46, 55, 76 ) );
	m_stcShowType.SetWindowPos( NULL, 708*CUR_SCREEN_WIDTH_PER,  (75+2*(20+33))*CUR_SCREEN_HEIGHT_PER, 300*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	
	m_edtShowType.SetImage( IDR_PNG_BTN_EDITMEDIALEFT, IDR_PNG_BTN_EDITMEDIAMID, IDR_PNG_BTN_EDITMEDIAMID,
		IDR_PNG_BTN_EDITMEDIALEFT, IDR_PNG_BTN_EDITMEDIAMID, IDR_PNG_BTN_EDITMEDIAMID,
		IDR_PNG_BTN_EDITMEDIALEFT, IDR_PNG_BTN_EDITMEDIAMID, IDR_PNG_BTN_EDITMEDIAMID,
		0, 0 , 0);
	m_edtShowType.SetWindowText("");
	m_edtShowType.EnableWindow(FALSE);
	m_edtShowType.SetDisableColor( Color(46, 55, 76) );
	m_edtShowType.SetDisableImg(FALSE);
		
	m_btnShowType.SetImage( IDR_PNG_BTN_EDITMEDIARIGHT, IDR_PNG_BTN_EDITMEDIARIGHT_DOWN, IDR_PNG_BTN_EDITMEDIARIGHT );
	m_edtShowType.SetWindowPos( NULL, (690+125)*CUR_SCREEN_WIDTH_PER, (67+37+15+41+13)*CUR_SCREEN_HEIGHT_PER, (393-41)*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnShowType.SetWindowPos( NULL, (690+125+393-41)*CUR_SCREEN_WIDTH_PER, (67+37+15+41+13)*CUR_SCREEN_HEIGHT_PER, 41*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransStatic( &m_stcRecordTime, _T("录制时间") , 13, Color( 46, 55, 76 ) );
	m_stcRecordTime.SetWindowPos( NULL, 708*CUR_SCREEN_WIDTH_PER,  (75+3*(20+33))*CUR_SCREEN_HEIGHT_PER, 300*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransStatic( &m_stcRecordTimeReal, _T("") , 13, Color( 46, 55, 76 ) );
	m_stcRecordTimeReal.SetWindowPos( NULL, (690+125+19)*CUR_SCREEN_WIDTH_PER,  (75+3*(20+33))*CUR_SCREEN_HEIGHT_PER, 300*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	
	m_btnRecordStart.SetImage( IDR_PNG_BTN_START_RECORD_NORMAL, IDR_PNG_BTN_START_RECORD_DOWN, IDR_PNG_BTN_START_RECORD_DISABLE );
	m_btnRecordStart.SetWindowPos( NULL, (1226-10-114)*CUR_SCREEN_WIDTH_PER,  (67+37+15+41+13+41+15)*CUR_SCREEN_HEIGHT_PER, 114, 37, SWP_HIDEWINDOW );
	
	m_btnRecordStop.SetImage( IDR_PNG_BTN_PAUSE_RECORD_NORMAL, IDR_PNG_PAUSE_RECORD_DOWN, IDR_PNG_PAUSE_RECORD_DISABLE );
	m_btnRecordStop.SetWindowPos( NULL, (1226-10-2*114-14)*CUR_SCREEN_WIDTH_PER,  (67+37+15+41+13+41+15)*CUR_SCREEN_HEIGHT_PER, 114, 37, SWP_HIDEWINDOW );

	m_btnRecordResume.SetImage( IDR_PNG_BTN_RESUME_RECORD_NORMAL, IDR_PNG_BTN_RESUME_RECORD_DOWN, IDR_PNG_BTN_RESUME_RECORD_DISABLE );
	m_btnRecordResume.SetWindowPos( NULL, (1226-10-2*114-14)*CUR_SCREEN_WIDTH_PER,  (67+37+15+41+13+41+15)*CUR_SCREEN_HEIGHT_PER, 114, 37, SWP_HIDEWINDOW );

	m_btnRecordFinish.SetImage( IDR_PNG_FINISH_RECORD_NORMAL, IDR_PNG_FINISH_RECORD_DOWN, IDR_PNG_FINISH_RECORD_DISABLE );
	m_btnRecordFinish.SetWindowPos( NULL, (1226-10-114)*CUR_SCREEN_WIDTH_PER,  (67+37+15+41+13+41+15)*CUR_SCREEN_HEIGHT_PER, 114, 37, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransStatic( &m_stcRecFileName, _T("录像名称") , 13, Color( 46, 55, 76 ) );
	m_stcRecFileName.SetWindowPos( NULL, 708*CUR_SCREEN_WIDTH_PER,  (75+4*(20+33))*CUR_SCREEN_HEIGHT_PER, 300*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransStatic( &m_stcRecFileNameReal, _T("") , 13, Color( 46, 55, 76 ) );
	m_stcRecFileNameReal.SetWindowPos( NULL, (690+125+19)*CUR_SCREEN_WIDTH_PER,  (75+4*(20+33))*CUR_SCREEN_HEIGHT_PER, 350*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );


	
	CUmcwebCommon::SetTextTransStatic( &m_stcPlay, _T("回放演示") , 13, Color( 46, 55, 76 ) );
	m_stcPlay.SetWindowPos( NULL, 708*CUR_SCREEN_WIDTH_PER,  342*CUR_SCREEN_HEIGHT_PER, 300*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	m_btnPlaySwitch.SetImage( IDR_PNG_LOGINWND_BTN_ON, IDR_PNG_LOGINWND_BTN_ONDOWN, IDR_PNG_LOGINWND_BTN_ONDIS,
        IDR_PNG_LOGINWND_BTN_OFF,IDR_PNG_LOGINWND_BTN_OFFDOWN, IDR_PNG_LOGINWND_BTN_OFFDIS);
	m_btnPlaySwitch.SetWindowPos( NULL, (1226-11-113)*CUR_SCREEN_WIDTH_PER, 334*CUR_SCREEN_HEIGHT_PER, 113*CUR_SCREEN_WIDTH_PER, 37*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	m_edtPlayChoose.SetImage( IDR_PNG_BTN_EDITMEDIALEFT, IDR_PNG_BTN_EDITMEDIAMID, IDR_PNG_BTN_EDITMEDIAMID,
		IDR_PNG_BTN_EDITMEDIALEFT, IDR_PNG_BTN_EDITMEDIAMID, IDR_PNG_BTN_EDITMEDIAMID,
		IDR_PNG_BTN_EDITMEDIALEFT, IDR_PNG_BTN_EDITMEDIAMID, IDR_PNG_BTN_EDITMEDIAMID,
		0, 0 , 0);
	m_edtPlayChoose.SetWindowText("");
	m_edtPlayChoose.EnableWindow(FALSE);
	m_edtPlayChoose.SetDisableColor( Color(46, 55, 76) );
	
	m_btnPlayChoose.SetImage( IDR_PNG_BTN_EDITMEDIARIGHT, IDR_PNG_BTN_EDITMEDIARIGHT_DOWN, IDR_PNG_BTN_EDITMEDIARIGHT );
	m_edtPlayChoose.SetWindowPos( NULL, 697*CUR_SCREEN_WIDTH_PER, (342+20+23)*CUR_SCREEN_HEIGHT_PER, (519-41)*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnPlayChoose.SetWindowPos( NULL, (697+519-41)*CUR_SCREEN_WIDTH_PER, (342+20+23)*CUR_SCREEN_HEIGHT_PER,
		41*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	m_btnPlayStart.SetImage( IDR_PNG_BTN_START_PLAY_NORMAL, IDR_PNG_BTN_START_PLAY_DOWN, IDR_PNG_BTN_START_PLAY_DISABLE );
	m_btnPlayStart.SetWindowPos( NULL, (1226-10-114)*CUR_SCREEN_WIDTH_PER,  (342+20+23+41+15)*CUR_SCREEN_HEIGHT_PER, 114, 37, SWP_HIDEWINDOW );
	
	m_btnPlayStop.SetImage( IDR_PNG_BTN_PAUSE_PLAY_NORMAL, IDR_PNG_BTN_PAUSE_PLAY_DOWN, IDR_PNG_BTN_PAUSE_PLAY_DISABLE );
	m_btnPlayStop.SetWindowPos( NULL, (1226-10-114-14-114)*CUR_SCREEN_WIDTH_PER,  (342+20+23+41+15)*CUR_SCREEN_HEIGHT_PER, 114, 37, SWP_HIDEWINDOW );
	
	m_btnPlayResume.SetImage( IDR_PNG_BTN_RESUME_PLAY_NORMAL, IDR_PNG_BTN_RESUME_PLAY_DOWN, IDR_PNG_BTN_RESUME_PLAY_DISABLE );
	m_btnPlayResume.SetWindowPos( NULL, (1226-10-114-14-114)*CUR_SCREEN_WIDTH_PER,  (342+20+23+41+15)*CUR_SCREEN_HEIGHT_PER, 114, 37, SWP_HIDEWINDOW );
	
	m_btnPlayFinish.SetImage( IDR_PNG_FINISH_PLAY_NORMAL, IDR_PNG_BTN_FINISH_PLAY_DOWN, IDR_PNG_BTN_FINISH_PLAY_DISABLE );
	m_btnPlayFinish.SetWindowPos( NULL, (1226-10-114)*CUR_SCREEN_WIDTH_PER,  (342+20+23+41+15)*CUR_SCREEN_HEIGHT_PER, 114, 37, SWP_HIDEWINDOW );
	

	m_pProgressPlay = new CTransparentProgress( "", "", 0, this, GETUNIQID, WS_CHILD );
 	m_pProgressPlay->SetImage( IDR_PNG_PROGRESS_LEFT, IDR_PNG_PROGRESS_MID, IDR_PNG_PROGRESS_RIGHT
		, IDR_PNG_PROGRESS_LEFT_HIGH, IDR_PNG_PROGRESS_MID_HIGH, IDR_PNG_PROGRESS_RIGHT_HIGH );
 	m_pProgressPlay->SetWindowPos( NULL, 709*CUR_SCREEN_WIDTH_PER,  (342+20+23+41+23+20+28)*CUR_SCREEN_HEIGHT_PER, 495, 10, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransStatic( &m_stcPlayProgress, _T("") , 13, Color( 46, 55, 76 ) );
	m_stcPlayProgress.SetWindowPos( NULL, 709*CUR_SCREEN_WIDTH_PER,  (342+20+23+41+23+20+28+10+6)*CUR_SCREEN_HEIGHT_PER, 500*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );




	m_btnChildBack.SetImage( IDR_PNG_BTN_RETURN, IDR_PNG_BTN_RETURNDOWN, IDR_PNG_BTN_RETURN );
	m_btnChildBack.SetWindowPos( NULL, 702*CUR_SCREEN_WIDTH_PER,  6*CUR_SCREEN_HEIGHT_PER, 66, 36, SWP_HIDEWINDOW );
	
	//会议格式
	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnHP1080P60fps, "HP 1080P@60fps" );
	m_radiobtnHP1080P60fps.SetWindowPos( NULL, 709*CUR_SCREEN_WIDTH_PER, 122*CUR_SCREEN_HEIGHT_PER, m_radiobtnHP1080P60fps.GetImageSize().cx, m_radiobtnHP1080P60fps.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnHP1080P50fps, "HP 1080P@50fps" );
	m_radiobtnHP1080P50fps.SetWindowPos( NULL, (690+189)*CUR_SCREEN_WIDTH_PER, 122*CUR_SCREEN_HEIGHT_PER, m_radiobtnHP1080P50fps.GetImageSize().cx, m_radiobtnHP1080P50fps.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnHP1080P30fps, "HP 1080P@30fps" );
	m_radiobtnHP1080P30fps.SetWindowPos( NULL, (690+359)*CUR_SCREEN_WIDTH_PER, 122*CUR_SCREEN_HEIGHT_PER, m_radiobtnHP1080P30fps.GetImageSize().cx, m_radiobtnHP1080P30fps.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnHP1080P25fps, "HP 1080P@25fps" );
	m_radiobtnHP1080P25fps.SetWindowPos( NULL, 709*CUR_SCREEN_WIDTH_PER, (122+26+m_radiobtnHP1080P25fps.GetImageSize().cy)*CUR_SCREEN_HEIGHT_PER, m_radiobtnHP1080P25fps.GetImageSize().cx, m_radiobtnHP1080P25fps.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnHP720P60fps, "HP 720P@60fps" );
	m_radiobtnHP720P60fps.SetWindowPos( NULL, (690+189)*CUR_SCREEN_WIDTH_PER, (122+26+m_radiobtnHP720P60fps.GetImageSize().cy)*CUR_SCREEN_HEIGHT_PER, m_radiobtnHP720P60fps.GetImageSize().cx, m_radiobtnHP720P60fps.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnHP720P50fps, "HP 720P@50fps" );
	m_radiobtnHP720P50fps.SetWindowPos( NULL, (690+359)*CUR_SCREEN_WIDTH_PER, (122+26+m_radiobtnHP720P50fps.GetImageSize().cy)*CUR_SCREEN_HEIGHT_PER, m_radiobtnHP720P50fps.GetImageSize().cx, m_radiobtnHP720P50fps.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnHP720P30fps, "HP 720P@30fps" );
	m_radiobtnHP720P30fps.SetWindowPos( NULL, 709*CUR_SCREEN_WIDTH_PER, (122+(26+m_radiobtnHP720P30fps.GetImageSize().cy)*2)*CUR_SCREEN_HEIGHT_PER, m_radiobtnHP720P30fps.GetImageSize().cx, m_radiobtnHP720P30fps.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnHP720P25fps, "HP 720P@25fps" );
	m_radiobtnHP720P25fps.SetWindowPos( NULL, (690+189)*CUR_SCREEN_WIDTH_PER, (122+(26+m_radiobtnHP720P25fps.GetImageSize().cy)*2)*CUR_SCREEN_HEIGHT_PER, m_radiobtnHP720P25fps.GetImageSize().cx, m_radiobtnHP720P25fps.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBP1080P60fps, "BP 1080P@60fps" );
	m_radiobtnBP1080P60fps.SetWindowPos( NULL, 709*CUR_SCREEN_WIDTH_PER, (122+(26+m_radiobtnBP1080P60fps.GetImageSize().cy)*3)*CUR_SCREEN_HEIGHT_PER, m_radiobtnBP1080P60fps.GetImageSize().cx, m_radiobtnBP1080P60fps.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBP1080P50fps, "BP 1080P@50fps" );
	m_radiobtnBP1080P50fps.SetWindowPos( NULL, (690+189)*CUR_SCREEN_WIDTH_PER, (122+(26+m_radiobtnBP1080P50fps.GetImageSize().cy)*3)*CUR_SCREEN_HEIGHT_PER, m_radiobtnBP1080P50fps.GetImageSize().cx, m_radiobtnBP1080P50fps.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBP1080P30fps, "BP 1080P@30fps" );
	m_radiobtnBP1080P30fps.SetWindowPos( NULL, (690+359)*CUR_SCREEN_WIDTH_PER, (122+(26+m_radiobtnBP1080P30fps.GetImageSize().cy)*3)*CUR_SCREEN_HEIGHT_PER, m_radiobtnBP1080P30fps.GetImageSize().cx, m_radiobtnBP1080P30fps.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBP1080P25fps, "BP 1080P@25fps" );
	m_radiobtnBP1080P25fps.SetWindowPos( NULL, 709*CUR_SCREEN_WIDTH_PER, (122+(26+m_radiobtnBP1080P25fps.GetImageSize().cy)*4)*CUR_SCREEN_HEIGHT_PER, m_radiobtnBP1080P25fps.GetImageSize().cx, m_radiobtnBP1080P25fps.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBP720P60fps, "BP 720P@60fps" );
	m_radiobtnBP720P60fps.SetWindowPos( NULL, (690+189)*CUR_SCREEN_WIDTH_PER, (122+(26+m_radiobtnBP720P60fps.GetImageSize().cy)*4)*CUR_SCREEN_HEIGHT_PER, m_radiobtnBP720P60fps.GetImageSize().cx, m_radiobtnBP720P60fps.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBP720P50fps, "BP 720P@50fps" );
	m_radiobtnBP720P50fps.SetWindowPos( NULL, (690+359)*CUR_SCREEN_WIDTH_PER, (122+(26+m_radiobtnBP720P50fps.GetImageSize().cy)*4)*CUR_SCREEN_HEIGHT_PER, m_radiobtnBP720P50fps.GetImageSize().cx, m_radiobtnBP720P50fps.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBP720P30fps, "BP 720P@30fps" );
	m_radiobtnBP720P30fps.SetWindowPos( NULL, 709*CUR_SCREEN_WIDTH_PER, (122+(26+m_radiobtnBP720P30fps.GetImageSize().cy)*5)*CUR_SCREEN_HEIGHT_PER, m_radiobtnBP720P30fps.GetImageSize().cx, m_radiobtnBP720P30fps.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBP720P25fps, "BP 720P@25fps" );
	m_radiobtnBP720P25fps.SetWindowPos( NULL, (690+189)*CUR_SCREEN_WIDTH_PER, (122+(26+m_radiobtnBP720P25fps.GetImageSize().cy)*5)*CUR_SCREEN_HEIGHT_PER, m_radiobtnBP720P25fps.GetImageSize().cx, m_radiobtnBP720P25fps.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBP4CIF25fps, "BP 4CIF@25fps" );
	m_radiobtnBP4CIF25fps.SetWindowPos( NULL, (690+359)*CUR_SCREEN_WIDTH_PER, (122+(26+m_radiobtnBP4CIF25fps.GetImageSize().cy)*5)*CUR_SCREEN_HEIGHT_PER, m_radiobtnBP4CIF25fps.GetImageSize().cx, m_radiobtnBP4CIF25fps.GetImageSize().cy, SWP_HIDEWINDOW );


	//演示格式
	CUmcwebCommon::SetTextTransStatic( &m_stcH264, _T("H.264") , 12, Color( 46, 55, 76 ) );
	m_stcH264.SetWindowPos( NULL, 708*CUR_SCREEN_WIDTH_PER,  75*CUR_SCREEN_HEIGHT_PER, 300*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_stcH264.SetWindowText( _T("H.264") );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnHP1080P60fpsShow, "HP 1080P@60fps" );
	m_radiobtnHP1080P60fpsShow.SetWindowPos( NULL, 709*CUR_SCREEN_WIDTH_PER, 122*CUR_SCREEN_HEIGHT_PER, m_radiobtnHP1080P60fpsShow.GetImageSize().cx, m_radiobtnHP1080P60fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnHP1080P50fpsShow, "HP 1080P@50fps" );
	m_radiobtnHP1080P50fpsShow.SetWindowPos( NULL, (690+189)*CUR_SCREEN_WIDTH_PER, 122*CUR_SCREEN_HEIGHT_PER, m_radiobtnHP1080P50fpsShow.GetImageSize().cx, m_radiobtnHP1080P50fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnHP1080P30fpsShow, "HP 1080P@30fps" );
	m_radiobtnHP1080P30fpsShow.SetWindowPos( NULL, (690+359)*CUR_SCREEN_WIDTH_PER, 122*CUR_SCREEN_HEIGHT_PER, m_radiobtnHP1080P30fpsShow.GetImageSize().cx, m_radiobtnHP1080P30fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnHP1080P25fpsShow, "HP 1080P@25fps" );
	m_radiobtnHP1080P25fpsShow.SetWindowPos( NULL, 709*CUR_SCREEN_WIDTH_PER, (122+26+m_radiobtnHP1080P25fpsShow.GetImageSize().cy)*CUR_SCREEN_HEIGHT_PER, m_radiobtnHP1080P25fpsShow.GetImageSize().cx, m_radiobtnHP1080P25fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnHP720P60fpsShow, "HP 720P@60fps" );
	m_radiobtnHP720P60fpsShow.SetWindowPos( NULL, (690+189)*CUR_SCREEN_WIDTH_PER, (122+26+m_radiobtnHP720P60fpsShow.GetImageSize().cy)*CUR_SCREEN_HEIGHT_PER, m_radiobtnHP720P60fpsShow.GetImageSize().cx, m_radiobtnHP720P60fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnHP720P50fpsShow, "HP 720P@50fps" );
	m_radiobtnHP720P50fpsShow.SetWindowPos( NULL, (690+359)*CUR_SCREEN_WIDTH_PER, (122+26+m_radiobtnHP720P50fpsShow.GetImageSize().cy)*CUR_SCREEN_HEIGHT_PER, m_radiobtnHP720P50fpsShow.GetImageSize().cx, m_radiobtnHP720P50fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnHP720P30fpsShow, "HP 720P@30fps" );
	m_radiobtnHP720P30fpsShow.SetWindowPos( NULL, 709*CUR_SCREEN_WIDTH_PER, (122+2*(26+m_radiobtnHP720P30fpsShow.GetImageSize().cy))*CUR_SCREEN_HEIGHT_PER, m_radiobtnHP720P30fpsShow.GetImageSize().cx, m_radiobtnHP720P30fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnHP720P25fpsShow, "HP 720P@25fps" );
	m_radiobtnHP720P25fpsShow.SetWindowPos( NULL, (690+189)*CUR_SCREEN_WIDTH_PER, (122+2*(26+m_radiobtnHP720P25fpsShow.GetImageSize().cy))*CUR_SCREEN_HEIGHT_PER, m_radiobtnHP720P25fpsShow.GetImageSize().cx, m_radiobtnHP720P25fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBP1080P60fpsShow, "BP 1080P@60fps" );
	m_radiobtnBP1080P60fpsShow.SetWindowPos( NULL, 709*CUR_SCREEN_WIDTH_PER, (122+3*(26+m_radiobtnBP1080P60fpsShow.GetImageSize().cy))*CUR_SCREEN_HEIGHT_PER, m_radiobtnBP1080P60fpsShow.GetImageSize().cx, m_radiobtnBP1080P60fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBP1080P50fpsShow, "BP 1080P@50fps" );
	m_radiobtnBP1080P50fpsShow.SetWindowPos( NULL, (690+189)*CUR_SCREEN_WIDTH_PER, (122+3*(26+m_radiobtnBP1080P50fpsShow.GetImageSize().cy))*CUR_SCREEN_HEIGHT_PER, m_radiobtnBP1080P50fpsShow.GetImageSize().cx, m_radiobtnBP1080P50fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBP1080P30fpsShow, "BP 1080P@30fps" );
	m_radiobtnBP1080P30fpsShow.SetWindowPos( NULL, (690+359)*CUR_SCREEN_WIDTH_PER, (122+3*(26+m_radiobtnBP1080P30fpsShow.GetImageSize().cy))*CUR_SCREEN_HEIGHT_PER, m_radiobtnBP1080P30fpsShow.GetImageSize().cx, m_radiobtnBP1080P30fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBP1080P25fpsShow, "BP 1080P@25fps" );
	m_radiobtnBP1080P25fpsShow.SetWindowPos( NULL, 709*CUR_SCREEN_WIDTH_PER, (122+4*(26+m_radiobtnBP1080P25fpsShow.GetImageSize().cy))*CUR_SCREEN_HEIGHT_PER, m_radiobtnBP1080P25fpsShow.GetImageSize().cx, m_radiobtnBP1080P25fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBP720P60fpsShow, "BP 720P@60fps" );
	m_radiobtnBP720P60fpsShow.SetWindowPos( NULL, (690+189)*CUR_SCREEN_WIDTH_PER, (122+4*(26+m_radiobtnBP720P60fpsShow.GetImageSize().cy))*CUR_SCREEN_HEIGHT_PER, m_radiobtnBP720P60fpsShow.GetImageSize().cx, m_radiobtnBP720P60fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBP720P50fpsShow, "BP 720P@50fps" );
	m_radiobtnBP720P50fpsShow.SetWindowPos( NULL, (690+359)*CUR_SCREEN_WIDTH_PER, (122+4*(26+m_radiobtnBP720P50fpsShow.GetImageSize().cy))*CUR_SCREEN_HEIGHT_PER, m_radiobtnBP720P50fpsShow.GetImageSize().cx, m_radiobtnBP720P50fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBP720P30fpsShow, "BP 720P@30fps" );
	m_radiobtnBP720P30fpsShow.SetWindowPos( NULL, 709*CUR_SCREEN_WIDTH_PER, (122+5*(26+m_radiobtnBP720P30fpsShow.GetImageSize().cy))*CUR_SCREEN_HEIGHT_PER, m_radiobtnBP720P30fpsShow.GetImageSize().cx, m_radiobtnBP720P30fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBP720P25fpsShow, "BP 720P@25fps" );
	m_radiobtnBP720P25fpsShow.SetWindowPos( NULL, (690+189)*CUR_SCREEN_WIDTH_PER, (122+5*(26+m_radiobtnBP720P25fpsShow.GetImageSize().cy))*CUR_SCREEN_HEIGHT_PER, m_radiobtnBP720P25fpsShow.GetImageSize().cx, m_radiobtnBP720P25fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBP4CIF25fpsShow, "BP 4CIF@25fps" );
	m_radiobtnBP4CIF25fpsShow.SetWindowPos( NULL, (690+359)*CUR_SCREEN_WIDTH_PER, (122+5*(26+m_radiobtnBP4CIF25fpsShow.GetImageSize().cy))*CUR_SCREEN_HEIGHT_PER, m_radiobtnBP4CIF25fpsShow.GetImageSize().cx, m_radiobtnBP4CIF25fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBPUXGA60fpsShow, "BP UXGA@60fps" );
	m_radiobtnBPUXGA60fpsShow.SetWindowPos( NULL, 709*CUR_SCREEN_WIDTH_PER, (122+6*(26+m_radiobtnBPUXGA60fpsShow.GetImageSize().cy))*CUR_SCREEN_HEIGHT_PER, m_radiobtnBPUXGA60fpsShow.GetImageSize().cx, m_radiobtnBPUXGA60fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBPWXGA30fpsShow, "BP WXGA@30fps" );
	m_radiobtnBPWXGA30fpsShow.SetWindowPos( NULL, (690+189)*CUR_SCREEN_WIDTH_PER, (122+6*(26+m_radiobtnBPWXGA30fpsShow.GetImageSize().cy))*CUR_SCREEN_HEIGHT_PER, m_radiobtnBPWXGA30fpsShow.GetImageSize().cx, m_radiobtnBPWXGA30fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBPSXGA30fpsShow, "BP SXGA@30fps" );
	m_radiobtnBPSXGA30fpsShow.SetWindowPos( NULL, (690+359)*CUR_SCREEN_WIDTH_PER, (122+6*(26+m_radiobtnBPSXGA30fpsShow.GetImageSize().cy))*CUR_SCREEN_HEIGHT_PER, m_radiobtnBPSXGA30fpsShow.GetImageSize().cx, m_radiobtnBPSXGA30fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBPWXGA5fpsShow, "BP WXGA@5fps" );
	m_radiobtnBPWXGA5fpsShow.SetWindowPos( NULL, 709*CUR_SCREEN_WIDTH_PER, (122+7*(26+m_radiobtnBPWXGA5fpsShow.GetImageSize().cy))*CUR_SCREEN_HEIGHT_PER, m_radiobtnBPWXGA5fpsShow.GetImageSize().cx, m_radiobtnBPWXGA5fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBPSXGA5fpsShow, "BP SXGA@5fps" );
	m_radiobtnBPSXGA5fpsShow.SetWindowPos( NULL, (690+189)*CUR_SCREEN_WIDTH_PER, (122+7*(26+m_radiobtnBPSXGA5fpsShow.GetImageSize().cy))*CUR_SCREEN_HEIGHT_PER, m_radiobtnBPSXGA5fpsShow.GetImageSize().cx, m_radiobtnBPSXGA5fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );
	
	CUmcwebCommon::SetTextTransCheckBtn( &m_radiobtnBPXGA5fpsShow, "BP XGA@5fps" );
	m_radiobtnBPXGA5fpsShow.SetWindowPos( NULL, (690+359)*CUR_SCREEN_WIDTH_PER, (122+7*(26+m_radiobtnBPXGA5fpsShow.GetImageSize().cy))*CUR_SCREEN_HEIGHT_PER, m_radiobtnBPXGA5fpsShow.GetImageSize().cx, m_radiobtnBPXGA5fpsShow.GetImageSize().cy, SWP_HIDEWINDOW );


	//回放文件选择
	m_edtPlayChoose.SetEditFrontLen(12);
	m_edtPlayChoose.SetEditBackLen(0);

	//列表加入
	if ( m_pListVedioFile == NULL )
	{
		m_pListVedioFile = new CListChild( "", CRect(708, 100, 502+708, 488+100), this, "", 0, WS_CHILD );
		m_pListVedioFile->SetWindowPos( NULL, 708*CUR_SCREEN_WIDTH_PER, 100*CUR_SCREEN_HEIGHT_PER, 502*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
		m_pListVedioFile->SetImage( IDR_PNG_LIST_TOPLEFT, IDR_PNG_LIST_TOPCEN, IDR_PNG_LIST_TOPRIGHT, IDR_PNG_LIST_CENLEFT, IDR_PNG_LIST_CENRIGHT,
			IDR_PNG_LIST_BTLEFT, IDR_PNG_LIST_BTCEN, IDR_PNG_LIST_BTRIGHT, IDR_PNG_LIST_TOPCEN, "PNG" );
        m_pListVedioFile->SetSliderImage( IDR_PNG_LISTSLIDER_NORMALTOP, IDR_PNG_LISTSLIDER_NORMALMIDDLE, IDR_PNG_LISTSLIDER_NORMALBOTTOM, IDR_PNG_LISTSLIDER_DOWNTOP, 
            IDR_PNG_LISTSLIDER_DOWNMIDDLE, IDR_PNG_LISTSLIDER_DOWNBOTTOM, IDR_PNG_LISTSLIDER_BKGTOP, IDR_PNG_LISTSLIDER_BKGMIDDLE, IDR_PNG_LISTSLIDER_BKGBOTTOM, "PNG" );
        m_pListVedioFile->SetSliderAlwaysShow( TRUE );
		
		
		m_pListVedioFile->GetWindowRect(&rectClient);
		ScreenToClient( &rectClient );
		
		rectClient.left = rectClient.right - 3;
		rectClient.right = rectClient.left + 7;
		m_pListVedioFile->SetSliderRect( rectClient );
	}

	m_radiobtnHP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fps.SetCheck(BST_UNCHECKED);;
	m_radiobtnHP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fps.SetCheck(BST_UNCHECKED);

	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);

	ShowChildWnd( em_Wnd_Init );

	return TRUE;
}

void CVedioRecordLogic::InitDlg()
{
	m_tUmcConfInfoSel.Clear();
	m_vecTUmcConfInfoSearch.clear();
	m_vecTUmcConfInfo.clear();

	ShowChildWnd( em_Wnd_Init );
	m_emCurrentWnd = emCurrentWndMain;

	ShowWindow(SW_HIDE);

	if ( m_pVideoRecordEpLogic->GetSafeHwnd() )
	{
		m_pVideoRecordEpLogic->InitDlg();
	}

	CVideoRecordShowOpt::GetDlgPtr()->InitDlg();

	if ( m_pCVedioRecordNameEditLogic )
	{
		m_pCVedioRecordNameEditLogic->SendMessage(WM_COMMAND, IDCANCEL);
	}
}

void CVedioRecordLogic::RefreshRecList( int nRefresh, int nConfID )
{
	if ( m_pconfCtrlIF == NULL )
	{
		return;
	}
	if ( m_pVTRCtrlIF == NULL )
	{	
		return;
	}

	vector<TCMSConf> vecTCMSConf;
	m_pconfCtrlIF->GetConfList(vecTCMSConf);
	
	vector<TConRecState> vecTConRecState;
	m_pVTRCtrlIF->GetRecConfInfo(vecTConRecState);

	vector<TConfPlayStatus> vecTConfPlayStatus;
	m_pVTRCtrlIF->GetPlayConfInfo(vecTConfPlayStatus);


	//1.将vecTCMSConf变成vecTUmcConfInfoNew
	vector<TUmcConfInfo> vecTUmcConfInfoNew;
	vector<TCMSConf>::iterator itConf = vecTCMSConf.begin();
	for ( ; itConf != vecTCMSConf.end(); itConf++ )
	{
		tagUmcConfInfo tUmcConfInfo(*itConf);

		u8 byEqpID = 0;
		m_pVTRCtrlIF->GetEqpID( byEqpID );

		//放像信息
		tUmcConfInfo.m_tConfPlayStatus.m_tInfo.m_byEqpID = byEqpID;
		tUmcConfInfo.m_tConfPlayStatus.m_tInfo.m_wConfID = itConf->m_wConfID;


		//录像信息

		//将会议加入
		TUmcRecInfo tUmcRecInfo;
		strncpy( tUmcRecInfo.m_achName, itConf->m_achConfName, TP_MAX_NAME_LEN );
//		strncpy( tUmcRecInfo.m_achE164, itConf->m_achConfE164, TP_MAX_ALIAS_LEN );
		tUmcRecInfo.m_tInfo.m_emType = em_rec_recorder_conf;
		tUmcRecInfo.m_tInfo.m_wConfID = itConf->m_wConfID;
		tUmcRecInfo.m_tInfo.m_byEqpID = byEqpID;
		if ( itConf->m_wMainNum > 0 )
		{
			tUmcRecInfo.m_tInfo.m_tConfRecInfo.m_tConfFormat = itConf->m_atTpMainVideoRes[itConf->m_wMainNum-1];
		}
		if ( itConf->m_wMinorNum > 0 )
		{
			tUmcRecInfo.m_tInfo.m_tDualFormat = itConf->m_atTpMinorVideoRes[itConf->m_wMinorNum-1];
		}
		
		
		tUmcConfInfo.m_vecTRecInfo.push_back(tUmcRecInfo);

		//将会场加入
		int nMTNum = itConf->m_tplCnsList.Size();
		for ( int n = 0; n < nMTNum; n++ )
		{
			TCnsInfo tCnsInfo = itConf->m_tplCnsList.GetAt(n);
			EmTPEndpointType emType = tCnsInfo.m_emEpType;
			
			if ( ( emTPEndpointTypeCNS != emType &&  emTPEndpointH323MT != emType && emTPEndpointH323SingleMCU != emType )
				|| !tCnsInfo.m_bOnline )
			{  
				//如果类型不是cns则过滤掉，不显示
				continue;
			}

			TUmcRecInfo tUmcRecInfo;
			strncpy( tUmcRecInfo.m_achName, itConf->m_tplCnsList.GetAt(n).m_achRoomName, TP_MAX_NAME_LEN );
//			itoa( itConf->m_tplCnsList.GetAt(n).m_wEpID, tUmcRecInfo.m_achE164, 10 );
			tUmcRecInfo.m_tInfo.m_emType = em_rec_recorder_mt;
			tUmcRecInfo.m_tInfo.m_wConfID = itConf->m_wConfID;
			tUmcRecInfo.m_tInfo.m_byEqpID = byEqpID;;
			tUmcRecInfo.m_tInfo.m_tMtRecInfo.m_wMtID = itConf->m_tplCnsList.GetAt(n).m_wEpID;

			tUmcConfInfo.m_vecTRecInfo.push_back(tUmcRecInfo);
		}

		vecTUmcConfInfoNew.push_back(tUmcConfInfo);
	}


	//2.1.将vecTConRecState植入vecTUmcConfInfoNew
	{
		vector<TUmcConfInfo>::iterator itConfInfoNew = vecTUmcConfInfoNew.begin();
		for ( ; itConfInfoNew != vecTUmcConfInfoNew.end(); itConfInfoNew++ )
		{		
			vector<TConRecState>::iterator itRecState = vecTConRecState.begin();
			for ( ; itRecState != vecTConRecState.end(); itRecState++ )
			{
				if ( itConfInfoNew->m_wConfID == itRecState->m_tInfo.m_wConfID )
				{
					vector<TUmcRecInfo>::iterator itRecInfoNew = itConfInfoNew->m_vecTRecInfo.begin();
					for ( ; itRecInfoNew != itConfInfoNew->m_vecTRecInfo.end(); itRecInfoNew++ )
					{
						if ( itRecInfoNew->m_tInfo.m_tMtRecInfo.m_wMtID == itRecState->m_tInfo.m_tMtRecInfo.m_wMtID )
						{
							//双流格式如果是off，保持本地的格式
							TUmsVidFormat tDualFormat;
							if ( itRecState->m_tInfo.m_bRecDual == FALSE )
							{
								tDualFormat = itRecInfoNew->m_tInfo.m_tDualFormat;
							}
							else
							{
								tDualFormat = itRecState->m_tInfo.m_tDualFormat;
							}

							*itRecInfoNew = *itRecState;
							
							itRecInfoNew->m_tInfo.m_tDualFormat = tDualFormat;
						}
					}
				}
			}
		}
	}
	
	
	//2.2.将vecTConfPlayStatus植入vecTUmcConfInfoNew
	{
		vector<TUmcConfInfo>::iterator itConfInfoNew = vecTUmcConfInfoNew.begin();
		for ( ; itConfInfoNew != vecTUmcConfInfoNew.end(); itConfInfoNew++ )
		{		
			vector<TConfPlayStatus>::iterator itPlayState = vecTConfPlayStatus.begin();
			for ( ; itPlayState != vecTConfPlayStatus.end(); itPlayState++ )
			{
				if ( itConfInfoNew->m_wConfID == itPlayState->m_tInfo.m_wConfID )
				{
					itConfInfoNew->m_tConfPlayStatus = *itPlayState;
				}
			}
		}
	}
	
	//2.3.将m_vecTUmcConfInfo中的本地信息植入vecTUmcConfInfoNew
	{
		vector<TUmcConfInfo>::iterator itConfInfoNew = vecTUmcConfInfoNew.begin();
		for ( ; itConfInfoNew != vecTUmcConfInfoNew.end(); itConfInfoNew++ )
		{
			vector<TUmcConfInfo>::iterator itConfInfoOld = m_vecTUmcConfInfo.begin();
			for ( ; itConfInfoOld != m_vecTUmcConfInfo.end(); itConfInfoOld++ )
			{
				if ( itConfInfoOld->m_wConfID == itConfInfoNew->m_wConfID )
				{
					vector<TUmcRecInfo>::iterator itRecStateNew = itConfInfoNew->m_vecTRecInfo.begin();
					for ( ; itRecStateNew != itConfInfoNew->m_vecTRecInfo.end(); itRecStateNew++ )
					{
						vector<TUmcRecInfo>::iterator itRecStateOld = itConfInfoOld->m_vecTRecInfo.begin();
						for ( ; itRecStateOld != itConfInfoOld->m_vecTRecInfo.end(); itRecStateOld++ )
						{
							if ( itRecStateNew->m_tInfo.m_emType == em_rec_recorder_conf 
								&& itRecStateOld->m_tInfo.m_emType == em_rec_recorder_conf 
								&& itRecStateNew->m_tInfo.m_wConfID == itRecStateOld->m_tInfo.m_wConfID
								&& (strcmp(itRecStateOld->m_tInfo.m_achFileName, itRecStateNew->m_tInfo.m_achFileName) == 0) )
							{
								itRecStateNew->m_dwRecTime = itRecStateOld->m_dwRecTime;
							}
						}
					}
				}
				
				
				if ( itConfInfoOld->m_wConfID == itConfInfoNew->m_wConfID 
					&& (strcmp(itConfInfoOld->m_tConfPlayStatus.m_tInfo.m_szFileName, itConfInfoNew->m_tConfPlayStatus.m_tInfo.m_szFileName) == 0) )
				{
					itConfInfoNew->m_tConfPlayStatus.m_dwCurTime = itConfInfoOld->m_tConfPlayStatus.m_dwCurTime;
					
					if ( itConfInfoOld->m_tConfPlayStatus.m_emState != em_rec_pause
						&& itConfInfoNew->m_tConfPlayStatus.m_emState == em_rec_working )
					{
						itConfInfoNew->m_tConfPlayStatus.m_dwCurTime = 0;
					}
				}
			}
		}
	}
	

	//得到m_vecTUmcConfInfo
	m_vecTUmcConfInfo = vecTUmcConfInfoNew;
	


	ShowOptEx();
    

	//5.在m_vecTUmcConfInfoSearch中查找m_pTUmcConfInfoSel
	bool bFind = false;
	if ( m_tUmcConfInfoSel.m_vecTRecInfo.size() > 0 )
	{
		vector<TUmcConfInfo>::iterator it = m_vecTUmcConfInfoSearch.begin();
		for ( ; it != m_vecTUmcConfInfoSearch.end(); it++ )
		{
			if ( m_tUmcConfInfoSel.m_wConfID == it->m_wConfID )
			{
				switch( nRefresh )
				{
				case 0:
					{
						break;
					}
				case 1:
					{
						TConfPlayStatus tConfPlayStatus = m_tUmcConfInfoSel.m_tConfPlayStatus;
						m_tUmcConfInfoSel = *it;
						m_tUmcConfInfoSel.m_tConfPlayStatus = tConfPlayStatus;
						
						break;
					}
				case 2:
					{
						vector<TUmcRecInfo> vecTRecInfo = m_tUmcConfInfoSel.m_vecTRecInfo;
						m_tUmcConfInfoSel = *it;
						m_tUmcConfInfoSel.m_vecTRecInfo = vecTRecInfo;
						
						break;
					}
				default:
					break;
				}
				
				bFind = true;
				break;
			}
		}
	}
	
	if ( bFind == false )
	{
		m_tUmcConfInfoSel.Clear();
	}

	ShowSelItem();
	
	
	
	if ( m_pVideoRecordEpLogic != NULL )
	{
		m_pVideoRecordEpLogic->RefreshConfEpList(nRefresh);
	}
}

void CVedioRecordLogic::RefreshConfList( EmConfType emType, int nConfID )
{
	switch( emType )
	{
	case emConfAdd:
		{
			//如果有则不处理
			vector<TUmcConfInfo>::iterator it = m_vecTUmcConfInfo.begin();
			for ( ; it != m_vecTUmcConfInfo.end(); it++ )
			{
				if ( it->m_wConfID == nConfID )
				{
					return;
				}
			}

			vector<TCMSConf> vecTCMSConf;
			m_pconfCtrlIF->GetConfList(vecTCMSConf);

			vector<TConRecState> vecTConRecState;
			m_pVTRCtrlIF->GetRecConfInfo(vecTConRecState);

			vector<TConfPlayStatus> vecTConfPlayStatus;
			m_pVTRCtrlIF->GetPlayConfInfo(vecTConfPlayStatus);
			
			vector<TCMSConf>::iterator itConf = vecTCMSConf.begin();
			for ( ; itConf != vecTCMSConf.end(); itConf++ )
			{
				if ( itConf->m_wConfID != nConfID )
				{
					continue;
				}
				
				TUmcConfInfo tUmcConfInfo(*itConf);
				
				u8 byEqpID = 0;
				m_pVTRCtrlIF->GetEqpID( byEqpID );
				
				//放像信息
				tUmcConfInfo.m_tConfPlayStatus.m_tInfo.m_byEqpID = byEqpID;
				tUmcConfInfo.m_tConfPlayStatus.m_tInfo.m_wConfID = itConf->m_wConfID;
				
				
				//录像信息
				
				//将会议加入
				TUmcRecInfo tUmcRecInfo;
				strncpy( tUmcRecInfo.m_achName, itConf->m_achConfName, TP_MAX_NAME_LEN );
				tUmcRecInfo.m_tInfo.m_emType = em_rec_recorder_conf;
				tUmcRecInfo.m_tInfo.m_wConfID = itConf->m_wConfID;
				tUmcRecInfo.m_tInfo.m_byEqpID = byEqpID;
				if ( itConf->m_wMainNum > 0 )
				{
					tUmcRecInfo.m_tInfo.m_tConfRecInfo.m_tConfFormat = itConf->m_atTpMainVideoRes[itConf->m_wMainNum-1];
				}
				if ( itConf->m_wMinorNum > 0 )
				{
					tUmcRecInfo.m_tInfo.m_tDualFormat = itConf->m_atTpMinorVideoRes[itConf->m_wMinorNum-1];
				}
				
				tUmcConfInfo.m_vecTRecInfo.push_back(tUmcRecInfo);
				
				

				//查找录像放像信息
				//将vecTConRecState植入
				{
					vector<TConRecState>::iterator itRecState = vecTConRecState.begin();
					for ( ; itRecState != vecTConRecState.end(); itRecState++ )
					{
						if ( tUmcConfInfo.m_wConfID == itRecState->m_tInfo.m_wConfID &&
							0 == itRecState->m_tInfo.m_tMtRecInfo.m_wMtID )
						{
							tUmcConfInfo.m_vecTRecInfo[0] = *itRecState;
						}
					}
				}
				
				
				//将vecTConfPlayStatus植入
				{
					vector<TConfPlayStatus>::iterator itPlayState = vecTConfPlayStatus.begin();
					for ( ; itPlayState != vecTConfPlayStatus.end(); itPlayState++ )
					{
						if ( tUmcConfInfo.m_wConfID == itPlayState->m_tInfo.m_wConfID )
						{
							tUmcConfInfo.m_tConfPlayStatus = *itPlayState;
						}
					}
				}

				
				m_vecTUmcConfInfo.push_back(tUmcConfInfo);

				ShowOptEx();
			}

			break;
		}
	case emConfDel:
		{
			vector<TUmcConfInfo>::iterator it = m_vecTUmcConfInfo.begin();
			for ( ; it != m_vecTUmcConfInfo.end(); it++ )
			{
				if ( it->m_wConfID == nConfID )
				{
					m_vecTUmcConfInfo.erase(it);
					break;
				}
			}
			
			ShowOptEx();

			TUmcConfInfo* pTUmcConfInfo = FindConfInfoSel();
			
			if ( pTUmcConfInfo == NULL )
			{
				m_tUmcConfInfoSel.Clear();

				if ( m_emCurrentWnd == emCurrentWndEp )
				{
					m_pVideoRecordEpLogic->LoadScheme(emSchemeRecordEpDelConf);
				}
				else if ( m_emCurrentWnd == emCurrentWndConfTyye )
				{
					ShowChildWnd( em_Wnd_No_Show );
					m_stcChildWndTitle.SetWindowText( _T("会议格式") );
					m_stcChildWndTitle.SetWindowPos( NULL, (690 + 12 + 17 + 66)*CUR_SCREEN_WIDTH_PER, 14*CUR_SCREEN_HEIGHT_PER, 300*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
					m_btnChildBack.ShowWindow(SW_SHOW);
					m_emCurrentWnd = emCurrentWndConfTyye;
				}
				else if ( m_emCurrentWnd == emCurrentWndShowTyye )
				{
					ShowChildWnd( em_Wnd_No_Show );
					m_stcChildWndTitle.SetWindowText( _T("演示格式") );
					m_stcChildWndTitle.SetWindowPos( NULL, (690 + 12 + 17 + 66)*CUR_SCREEN_WIDTH_PER, 14*CUR_SCREEN_HEIGHT_PER, 300*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
					m_btnChildBack.ShowWindow(SW_SHOW);
					m_emCurrentWnd = emCurrentWndShowTyye;
				}
				else if ( m_emCurrentWnd == emCurrentWndPlayTyye )
				{
					ShowChildWnd( em_Wnd_No_Show );
					m_stcChildWndTitle.SetWindowText( _T("文件选择") );
					m_stcChildWndTitle.SetWindowPos( NULL, (690 + 12 + 17 + 66)*CUR_SCREEN_WIDTH_PER, 14*CUR_SCREEN_HEIGHT_PER, 300*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
					m_btnChildBack.ShowWindow(SW_SHOW);
					m_emCurrentWnd = emCurrentWndPlayTyye;
				}
			}
			
			ShowSelItem();

			break;
		}
	case emConfCnsChange:
		{
			TUmcConfInfo* pTUmcConfInfo = NULL;
			vector<TUmcConfInfo>::iterator it = m_vecTUmcConfInfo.begin();
			for ( ; it != m_vecTUmcConfInfo.end(); it++ )
			{
				if ( it->m_wConfID == nConfID )
				{
					pTUmcConfInfo = it;
				}
			}

			if ( pTUmcConfInfo == NULL )
			{
				return;
			}

			vector<TCMSConf> vecTCMSConf;
			m_pconfCtrlIF->GetConfList(vecTCMSConf);

			vector<TConRecState> vecTConRecState;
			m_pVTRCtrlIF->GetRecConfInfo(vecTConRecState);
			
			vector<TCMSConf>::iterator itConf = vecTCMSConf.begin();
			for ( ; itConf != vecTCMSConf.end(); itConf++ )
			{
				if ( itConf->m_wConfID != nConfID )
				{
					continue;
				}
				
				u8 byEqpID = 0;
				m_pVTRCtrlIF->GetEqpID( byEqpID );
				
				//将会场加入
				int nMTNum = itConf->m_tplCnsList.Size();
				for ( int n = 0; n < nMTNum; n++ )
				{
					TCnsInfo tCnsInfo = itConf->m_tplCnsList.GetAt(n);
					EmTPEndpointType emType = tCnsInfo.m_emEpType;

// 					BOOL32	m_bOnline = tCnsInfo.m_bOnline;
// 					CString str = tCnsInfo.m_achRoomName;
// 					if ( str == "tp56" )
// 					{
// 						int k = 0;
// 					}

					if ( ( emTPEndpointTypeCNS != emType &&  emTPEndpointH323MT != emType && emTPEndpointH323SingleMCU != emType )
						|| !tCnsInfo.m_bOnline )
					{  
						//如果类型不是cns则过滤掉，不显示
						vector<TUmcRecInfo>::iterator it = pTUmcConfInfo->m_vecTRecInfo.begin();
						for ( ; it != pTUmcConfInfo->m_vecTRecInfo.end(); it++ )
						{
							if ( strcmp( it->m_achName, tCnsInfo.m_achRoomName) == 0 )
							{
								pTUmcConfInfo->m_vecTRecInfo.erase(it);
								break;
							}
						}
						
						//同时检查sel信息
						vector<TUmcRecInfo>::iterator itSel = m_tUmcConfInfoSel.m_vecTRecInfo.begin();
						for ( ; itSel != m_tUmcConfInfoSel.m_vecTRecInfo.end(); itSel++ )
						{
							if ( strcmp( tCnsInfo.m_achRoomName, itSel->m_achName ) == 0 )
							{
								m_tUmcConfInfoSel.m_vecTRecInfo.erase(itSel);
								break;
							}
						}


						continue;
					}

					TUmcRecInfo tUmcRecInfo;
					strncpy( tUmcRecInfo.m_achName, itConf->m_tplCnsList.GetAt(n).m_achRoomName, TP_MAX_NAME_LEN );
//					itoa( itConf->m_tplCnsList.GetAt(n).m_wEpID, tUmcRecInfo.m_achE164, 10 );
					tUmcRecInfo.m_tInfo.m_emType = em_rec_recorder_mt;
					tUmcRecInfo.m_tInfo.m_wConfID = itConf->m_wConfID;
					tUmcRecInfo.m_tInfo.m_byEqpID = byEqpID;;
					tUmcRecInfo.m_tInfo.m_tMtRecInfo.m_wMtID = itConf->m_tplCnsList.GetAt(n).m_wEpID;

					BOOL bFind = FALSE;
					vector<TUmcRecInfo>::iterator it = pTUmcConfInfo->m_vecTRecInfo.begin();
					for( ; it != pTUmcConfInfo->m_vecTRecInfo.end(); it++ )
					{
						if ( strcmp( tUmcRecInfo.m_achName, it->m_achName) == 0 )
						{
							bFind = TRUE;
							break;
						}
					}
					
					if ( bFind )
					{
						continue;
					}
					else
					{
						//找到了那个Add的会场
						//查找录像放像信息
						//将vecTConRecState植入
						{
							vector<TConRecState>::iterator itRecState = vecTConRecState.begin();
							for ( ; itRecState != vecTConRecState.end(); itRecState++ )
							{
								if ( tUmcRecInfo.m_tInfo.m_wConfID == itRecState->m_tInfo.m_wConfID &&
									tUmcRecInfo.m_tInfo.m_tMtRecInfo.m_wMtID == itRecState->m_tInfo.m_tMtRecInfo.m_wMtID )
								{
									tUmcRecInfo = *itRecState;
								}
							}
						}
					}

					pTUmcConfInfo->m_vecTRecInfo.push_back(tUmcRecInfo);
					vector<TUmcRecInfo>::iterator itSel = m_tUmcConfInfoSel.m_vecTRecInfo.begin();
					for ( ; itSel != m_tUmcConfInfoSel.m_vecTRecInfo.end(); itSel++ )
					{
						if ( strcmp( tCnsInfo.m_achRoomName, itSel->m_achName ) == 0 )
						{
							m_tUmcConfInfoSel.m_vecTRecInfo.push_back(tUmcRecInfo);
						}
					}
				}

				ShowOptEx();
			}

			break;
		}
	default:
		break;
	}
}


void CVedioRecordLogic::SetConfAndPlayInfo()
{
	SetConfInfo();
	SetPlayInfo();
}

LRESULT CVedioRecordLogic::OnRecFileListInfoNty( WPARAM wparam, LPARAM lparam )
{
	RefreshRecFileList();

	return S_OK;
}

LRESULT CVedioRecordLogic::OnRecConfRecInfoNty( WPARAM wparam, LPARAM lparam )
{
	RefreshRecList(1);

	return S_OK;
}

LRESULT CVedioRecordLogic::OnRecConfPlayInfoNty( WPARAM wparam, LPARAM lparam )
{
	RefreshRecList(2);
	
	return S_OK;
}


LRESULT CVedioRecordLogic::OnRefreshConfCnsList( WPARAM wparam, LPARAM lparam )
{
	TConfCnsInfo tConfCnsInfo = *(TConfCnsInfo*)lparam;

	RefreshConfList( emConfCnsChange, tConfCnsInfo.m_wConfID );
	
	return S_OK;
}

LRESULT CVedioRecordLogic::OnRefreshConfListNty( WPARAM wparam, LPARAM lparam )
{
	emConfNtyType emType = (emConfNtyType)wparam;

	switch( emType )
	{
	case emLinkBreak:
		{
			RefreshRecList(0);
			if ( m_pVideoRecordEpLogic != NULL )
			{
				m_pVideoRecordEpLogic->RefreshConfEpList(0);
			}
			break;
		}
	case emAddConfListNotify:
		{
			u16* pConfID = (u16*)lparam;
			if ( pConfID == NULL )
			{
				return S_OK;
			}

			u16 arr[3] = { 0 };
			memcpy( arr, pConfID, 3*sizeof(u16) );
			
			for ( int n = 0; n < TP_REFRESH_LIST_THREE; n++ )
			{
				if ( arr[n] != 0 )
				{
					RefreshConfList( emConfAdd, arr[n] );
				}
			}
			break;
		}
	case emDelConfListNotify:
		{
			u16* pConfID = (u16*)lparam;
			if ( pConfID == NULL )
			{
				return S_OK;
			}
			
			u16 arr[3] = { 0 };
			memcpy( arr, pConfID, 3*sizeof(u16) );
			
			for ( int n = 0; n < TP_REFRESH_LIST_THREE; n++ )
			{
				if ( arr[n] != 0 )
				{
					RefreshConfList( emConfDel, arr[n] );
				}
			}

			break;
		}
	case emCasadeNotify:
		{
		}
	default:
		break;
	}

	return S_OK;
}

bool CVedioRecordLogic::OnClickConfListItem( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( const Data_RecordInfo *pItemInfo = dynamic_cast<const Data_RecordInfo*>( pBaseItem->GetUserData() )) 
        {
			if ( m_pVTRCtrlIF == NULL )
			{
				return true;
			}
			
			BOOL32 bRegState;
			m_pVTRCtrlIF->GetVtrRegState( bRegState );
			if( bRegState == FALSE )
			{
				m_tUmcConfInfoSel.Clear();
			}
			else
			{
				m_tUmcConfInfoSel = *(pItemInfo->m_pTUmcConfInfo);
				ShowChildWnd( em_Wnd_Record_Cfg );
				ShowSelItem();
			}
		}
    }
	
	return true;
}

bool CVedioRecordLogic::OnClickConfListItemIcon( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData(); 
		if ( const Data_RecordInfo *pItemInfo = dynamic_cast<const Data_RecordInfo*>( pBaseItem->GetUserData() )) 
        {
			m_tUmcConfInfoSel = *(pItemInfo->m_pTUmcConfInfo);
			if ( m_pVideoRecordEpLogic->GetSafeHwnd() )
			{
				m_pVideoRecordEpLogic->RefreshConfEpList();
			}

			ShowChildWnd( em_Wnd_Room );
		}
    }
	
	return true;
}

void CVedioRecordLogic::ShowChildWnd( EmChildWndType emChildWndType )
{
	switch ( emChildWndType )
	{
	case em_Wnd_Record_Cfg:
		{
			m_btnReturn.ShowWindow(SW_SHOW);
			m_stcChildWndTitle.ShowWindow(SW_HIDE);
			m_stcChildWndTitle.SetWindowText( _T("录像回放设置") );
			m_stcChildWndTitle.SetWindowPos( NULL, 720*CUR_SCREEN_WIDTH_PER, 14*CUR_SCREEN_HEIGHT_PER, 300*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
			m_btnShowEx.ShowWindow(SW_SHOW);
			m_btnShowEx.EnableWindow(TRUE);
			m_sedtSearch.ShowWindow(SW_SHOW);
			m_pListMeeting->ShowWindow(SW_SHOW);
			m_pLetterIndex->ShowWindow(SW_SHOW);
			m_stcDoubleCurrent.ShowWindow(SW_SHOW);
			m_btnSwitch.ShowWindow(SW_SHOW);
			m_stcConfType.ShowWindow(SW_SHOW);
			m_edtConfType.ShowWindow(SW_SHOW);
			m_btnConfType.ShowWindow(SW_SHOW);
			m_stcShowType.ShowWindow(SW_SHOW);
			m_edtShowType.ShowWindow(SW_SHOW);
			m_btnShowType.ShowWindow(SW_SHOW);
			m_stcRecordTime.ShowWindow(SW_SHOW);
			m_stcRecordTimeReal.ShowWindow(SW_SHOW);
			m_btnRecordStart.ShowWindow(SW_SHOW);
			m_btnRecordResume.ShowWindow(SW_SHOW);
			m_btnRecordStop.ShowWindow(SW_SHOW);
			m_btnRecordFinish.ShowWindow(SW_SHOW);
			m_stcRecFileName.ShowWindow(SW_SHOW);
			m_stcRecFileNameReal.ShowWindow(SW_SHOW);
			m_stcPlay.ShowWindow(SW_SHOW);
			m_btnPlaySwitch.ShowWindow(SW_SHOW);
			m_edtPlayChoose.ShowWindow(SW_SHOW);
			m_btnPlayChoose.ShowWindow(SW_SHOW);
			m_btnPlayStart.ShowWindow(SW_SHOW);
			m_btnPlayResume.ShowWindow(SW_SHOW);
			m_btnPlayStop.ShowWindow(SW_SHOW);
			m_btnPlayFinish.ShowWindow(SW_SHOW);
			if ( m_pProgressPlay )
			{
				m_pProgressPlay->ShowWindow(SW_SHOW);
			}
			m_stcPlayProgress.ShowWindow(SW_SHOW);

			m_btnChildBack.ShowWindow(SW_HIDE);

			m_stcH264.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P60fps.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P50fps.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P30fps.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P25fps.ShowWindow(SW_HIDE);
			m_radiobtnHP720P60fps.ShowWindow(SW_HIDE);
			m_radiobtnHP720P50fps.ShowWindow(SW_HIDE);
			m_radiobtnHP720P30fps.ShowWindow(SW_HIDE);
			m_radiobtnHP720P25fps.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P60fps.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P50fps.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P30fps.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P25fps.ShowWindow(SW_HIDE);
			m_radiobtnBP720P60fps.ShowWindow(SW_HIDE);
			m_radiobtnBP720P50fps.ShowWindow(SW_HIDE);
			m_radiobtnBP720P30fps.ShowWindow(SW_HIDE);
			m_radiobtnBP720P25fps.ShowWindow(SW_HIDE);
			m_radiobtnBP4CIF25fps.ShowWindow(SW_HIDE);
			
			m_radiobtnHP1080P60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P50fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP720P60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP720P50fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP720P30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP720P25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P50fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP720P60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP720P50fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP720P30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP720P25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP4CIF25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPUXGA60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPWXGA30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPSXGA30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPWXGA5fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPSXGA5fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPXGA5fpsShow.ShowWindow(SW_HIDE);

			m_edtSearchPlay.ShowWindow(SW_HIDE);
			m_pListVedioFile->ShowWindow(SW_HIDE);

			if ( m_pVideoRecordEpLogic->GetSafeHwnd() )
			{
				m_pVideoRecordEpLogic->ShowWindow(SW_HIDE);
			}

			LoadScheme(emSchmeControlBtn);

			SetConfAndPlayInfo();
			
			m_emCurrentWnd = emCurrentWndMain;

			break;
		}
	case em_Wnd_Conf_Type:
		{
			m_stcChildWndTitle.ShowWindow(SW_HIDE);
			m_stcChildWndTitle.SetWindowPos( NULL, (690 + 12 + 17 + 66)*CUR_SCREEN_WIDTH_PER, 14*CUR_SCREEN_HEIGHT_PER, 300*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
			m_stcChildWndTitle.SetWindowText( _T("会议格式") );
			m_btnShowEx.ShowWindow(SW_SHOW);
			m_btnShowEx.EnableWindow(FALSE);
			m_stcDoubleCurrent.ShowWindow(SW_HIDE);
			m_btnSwitch.ShowWindow(SW_HIDE);
			m_stcConfType.ShowWindow(SW_HIDE);
			m_edtConfType.ShowWindow(SW_HIDE);
 			m_btnConfType.ShowWindow(SW_HIDE);
			m_stcShowType.ShowWindow(SW_HIDE);
			m_edtShowType.ShowWindow(SW_HIDE);
			m_btnShowType.ShowWindow(SW_HIDE);
			m_stcRecordTime.ShowWindow(SW_HIDE);
			m_stcRecordTimeReal.ShowWindow(SW_HIDE);
			m_btnRecordStart.ShowWindow(SW_HIDE);
			m_btnRecordResume.ShowWindow(SW_HIDE);
			m_btnRecordStop.ShowWindow(SW_HIDE);
			m_btnRecordFinish.ShowWindow(SW_HIDE);
			m_stcRecFileName.ShowWindow(SW_HIDE);
			m_stcRecFileNameReal.ShowWindow(SW_HIDE);
			m_stcPlay.ShowWindow(SW_HIDE);
			m_btnPlaySwitch.ShowWindow(SW_HIDE);
			m_edtPlayChoose.ShowWindow(SW_HIDE);
			m_btnPlayChoose.ShowWindow(SW_HIDE);
			m_btnPlayStart.ShowWindow(SW_HIDE);
			m_btnPlayResume.ShowWindow(SW_HIDE);
			m_btnPlayStop.ShowWindow(SW_HIDE);
			m_btnPlayFinish.ShowWindow(SW_HIDE);
			if ( m_pProgressPlay )
			{
				m_pProgressPlay->ShowWindow(SW_HIDE);
			}
			m_stcPlayProgress.ShowWindow(SW_HIDE);

			m_btnChildBack.ShowWindow(SW_SHOW);

			m_stcH264.ShowWindow(SW_SHOW);
			m_radiobtnHP1080P60fps.ShowWindow(SW_SHOW);
			m_radiobtnHP1080P50fps.ShowWindow(SW_SHOW);
			m_radiobtnHP1080P30fps.ShowWindow(SW_SHOW);
			m_radiobtnHP1080P25fps.ShowWindow(SW_SHOW);
			m_radiobtnHP720P60fps.ShowWindow(SW_SHOW);
			m_radiobtnHP720P50fps.ShowWindow(SW_SHOW);
			m_radiobtnHP720P30fps.ShowWindow(SW_SHOW);
			m_radiobtnHP720P25fps.ShowWindow(SW_SHOW);
			m_radiobtnBP1080P60fps.ShowWindow(SW_SHOW);
			m_radiobtnBP1080P50fps.ShowWindow(SW_SHOW);
			m_radiobtnBP1080P30fps.ShowWindow(SW_SHOW);
			m_radiobtnBP1080P25fps.ShowWindow(SW_SHOW);
			m_radiobtnBP720P60fps.ShowWindow(SW_SHOW);
			m_radiobtnBP720P50fps.ShowWindow(SW_SHOW);
			m_radiobtnBP720P30fps.ShowWindow(SW_SHOW);
			m_radiobtnBP720P25fps.ShowWindow(SW_SHOW);
			m_radiobtnBP4CIF25fps.ShowWindow(SW_SHOW);

 			m_emCurrentWnd = emCurrentWndConfTyye; 	


			//解决搜索栏得到焦点的bug
			::SetFocus(NULL);		
		}
		break;
	case em_Wnd_Show_Type:
		{
			m_stcChildWndTitle.ShowWindow(SW_HIDE);
			m_stcChildWndTitle.SetWindowText( _T("演示格式") );
			m_stcChildWndTitle.SetWindowPos( NULL, (690 + 12 + 17 + 66)*CUR_SCREEN_WIDTH_PER, 14*CUR_SCREEN_HEIGHT_PER, 300*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
			m_btnShowEx.ShowWindow(SW_SHOW);
			m_btnShowEx.EnableWindow(FALSE);
			m_stcDoubleCurrent.ShowWindow(SW_HIDE);
			m_btnShowEx.EnableWindow(TRUE);
			m_btnSwitch.ShowWindow(SW_HIDE);
			m_stcConfType.ShowWindow(SW_HIDE);
			m_edtConfType.ShowWindow(SW_HIDE);
			m_btnConfType.ShowWindow(SW_HIDE);
			m_stcShowType.ShowWindow(SW_HIDE);
			m_edtShowType.ShowWindow(SW_HIDE);
			m_btnShowType.ShowWindow(SW_HIDE);
			m_stcRecordTime.ShowWindow(SW_HIDE);
			m_stcRecordTimeReal.ShowWindow(SW_HIDE);
			m_btnRecordStart.ShowWindow(SW_HIDE);
			m_btnRecordResume.ShowWindow(SW_HIDE);
			m_btnRecordStop.ShowWindow(SW_HIDE);
			m_btnRecordFinish.ShowWindow(SW_HIDE);
			m_stcRecFileName.ShowWindow(SW_HIDE);
			m_stcRecFileNameReal.ShowWindow(SW_HIDE);
			m_stcPlay.ShowWindow(SW_HIDE);
			m_btnPlaySwitch.ShowWindow(SW_HIDE);
			m_edtPlayChoose.ShowWindow(SW_HIDE);
			m_btnPlayChoose.ShowWindow(SW_HIDE);
			m_btnPlayStart.ShowWindow(SW_HIDE);
			m_btnPlayResume.ShowWindow(SW_HIDE);
			m_btnPlayStop.ShowWindow(SW_HIDE);
			m_btnPlayFinish.ShowWindow(SW_HIDE);
			if ( m_pProgressPlay )
			{
				m_pProgressPlay->ShowWindow(SW_HIDE);
			}
			m_stcPlayProgress.ShowWindow(SW_HIDE);

			m_btnChildBack.ShowWindow(SW_SHOW);

			m_stcH264.ShowWindow(SW_SHOW);
			m_radiobtnHP1080P60fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnHP1080P50fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnHP1080P30fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnHP1080P25fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnHP720P60fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnHP720P50fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnHP720P30fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnHP720P25fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnBP1080P60fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnBP1080P50fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnBP1080P30fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnBP1080P25fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnBP720P60fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnBP720P50fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnBP720P30fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnBP720P25fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnBP4CIF25fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnBPUXGA60fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnBPWXGA30fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnBPSXGA30fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnBPWXGA5fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnBPSXGA5fpsShow.ShowWindow(SW_SHOW);
			m_radiobtnBPXGA5fpsShow.ShowWindow(SW_SHOW);

			m_emCurrentWnd = emCurrentWndShowTyye;

			//解决搜索栏得到焦点的bug
			::SetFocus(NULL);
			break;
		}
	case em_Wnd_play_choose:
		{
			m_stcChildWndTitle.ShowWindow(SW_HIDE);
			m_stcChildWndTitle.SetWindowText( _T("文件选择") );
			m_stcChildWndTitle.SetWindowPos( NULL, (690 + 12 + 17 + 66)*CUR_SCREEN_WIDTH_PER, 14*CUR_SCREEN_HEIGHT_PER, 300*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
			m_btnShowEx.ShowWindow(SW_SHOW);
			m_btnShowEx.EnableWindow(FALSE);
			m_stcDoubleCurrent.ShowWindow(SW_HIDE);
			m_btnSwitch.ShowWindow(SW_HIDE);
			m_stcConfType.ShowWindow(SW_HIDE);
			m_edtConfType.ShowWindow(SW_HIDE);
			m_btnConfType.ShowWindow(SW_HIDE);
			m_stcShowType.ShowWindow(SW_HIDE);
			m_edtShowType.ShowWindow(SW_HIDE);
			m_btnShowType.ShowWindow(SW_HIDE);
			m_stcRecordTime.ShowWindow(SW_HIDE);
			m_stcRecordTimeReal.ShowWindow(SW_HIDE);
			m_btnRecordStart.ShowWindow(SW_HIDE);
			m_btnRecordResume.ShowWindow(SW_HIDE);
			m_btnRecordStop.ShowWindow(SW_HIDE);
			m_btnRecordFinish.ShowWindow(SW_HIDE);
			m_stcRecFileName.ShowWindow(SW_HIDE);
			m_stcRecFileNameReal.ShowWindow(SW_HIDE);
			m_stcPlay.ShowWindow(SW_HIDE);
			m_btnPlaySwitch.ShowWindow(SW_HIDE);
			m_edtPlayChoose.ShowWindow(SW_HIDE);
			m_btnPlayChoose.ShowWindow(SW_HIDE);
			m_btnPlayStart.ShowWindow(SW_HIDE);
			m_btnPlayResume.ShowWindow(SW_HIDE);
			m_btnPlayStop.ShowWindow(SW_HIDE);
			m_btnPlayFinish.ShowWindow(SW_HIDE);
			if ( m_pProgressPlay )
			{
				m_pProgressPlay->ShowWindow(SW_HIDE);
			}
			m_stcPlayProgress.ShowWindow(SW_HIDE);

			m_btnChildBack.ShowWindow(SW_SHOW);
			m_edtSearchPlay.ShowWindow(SW_SHOW);
			m_pListVedioFile->ShowWindow(SW_SHOW);

			m_emCurrentWnd = emCurrentWndPlayTyye;

			//解决搜索栏得到焦点的bug
			::SetFocus(NULL);
			break;
		}
	case em_Wnd_Room:
		{
			m_btnReturn.ShowWindow(SW_HIDE);
			m_stcChildWndTitle.ShowWindow(SW_HIDE);
			m_btnShowEx.ShowWindow(SW_HIDE);
			m_sedtSearch.ShowWindow(SW_HIDE);
			m_pListMeeting->ShowWindow(SW_HIDE);
			m_pLetterIndex->ShowWindow(SW_HIDE);
			m_stcTitle.ShowWindow(SW_HIDE);
			m_stcDoubleCurrent.ShowWindow(SW_HIDE);
			m_btnSwitch.ShowWindow(SW_HIDE);
			m_stcConfType.ShowWindow(SW_HIDE);
			m_edtConfType.ShowWindow(SW_HIDE);
			m_btnConfType.ShowWindow(SW_HIDE);
			m_stcShowType.ShowWindow(SW_HIDE);
			m_edtShowType.ShowWindow(SW_HIDE);
			m_btnShowType.ShowWindow(SW_HIDE);
			m_stcRecordTime.ShowWindow(SW_HIDE);
			m_stcRecordTimeReal.ShowWindow(SW_HIDE);
			m_btnRecordStart.ShowWindow(SW_HIDE);
			m_btnRecordResume.ShowWindow(SW_HIDE);
			m_btnRecordStop.ShowWindow(SW_HIDE);
			m_btnRecordFinish.ShowWindow(SW_HIDE);
			m_stcRecFileName.ShowWindow(SW_HIDE);
			m_stcRecFileNameReal.ShowWindow(SW_HIDE);
			m_stcPlay.ShowWindow(SW_HIDE);
			m_btnPlaySwitch.ShowWindow(SW_HIDE);
			m_edtPlayChoose.ShowWindow(SW_HIDE);
			m_btnPlayChoose.ShowWindow(SW_HIDE);
			m_btnPlayStart.ShowWindow(SW_HIDE);
			m_btnPlayResume.ShowWindow(SW_HIDE);
			m_btnPlayStop.ShowWindow(SW_HIDE);
			m_btnPlayFinish.ShowWindow(SW_HIDE);
			if ( m_pProgressPlay )
			{
				m_pProgressPlay->ShowWindow(SW_HIDE);
			}
			m_stcPlayProgress.ShowWindow(SW_HIDE);
			
			m_btnChildBack.ShowWindow(SW_HIDE);

			m_stcH264.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P60fps.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P50fps.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P30fps.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P25fps.ShowWindow(SW_HIDE);
			m_radiobtnHP720P60fps.ShowWindow(SW_HIDE);
			m_radiobtnHP720P50fps.ShowWindow(SW_HIDE);
			m_radiobtnHP720P30fps.ShowWindow(SW_HIDE);
			m_radiobtnHP720P25fps.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P60fps.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P50fps.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P30fps.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P25fps.ShowWindow(SW_HIDE);
			m_radiobtnBP720P60fps.ShowWindow(SW_HIDE);
			m_radiobtnBP720P50fps.ShowWindow(SW_HIDE);
			m_radiobtnBP720P30fps.ShowWindow(SW_HIDE);
			m_radiobtnBP720P25fps.ShowWindow(SW_HIDE);
			m_radiobtnBP4CIF25fps.ShowWindow(SW_HIDE);
			
			m_radiobtnHP1080P60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P50fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP720P60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP720P50fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP720P30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP720P25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P50fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP720P60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP720P50fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP720P30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP720P25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP4CIF25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPUXGA60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPWXGA30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPSXGA30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPWXGA5fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPSXGA5fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPXGA5fpsShow.ShowWindow(SW_HIDE);

			if ( m_pVideoRecordEpLogic->GetSafeHwnd() )
			{
				m_pVideoRecordEpLogic->ShowWindow(SW_SHOW);
			}
			
			m_emCurrentWnd = emCurrentWndEp;

			break;
		}
	case em_Wnd_Init:
		{
			m_stcChildWndTitle.ShowWindow(SW_HIDE);
			m_btnReturn.ShowWindow(SW_SHOW);
			m_stcChildWndTitle.SetWindowText( _T("录像回放设置") );
			m_stcChildWndTitle.SetWindowPos( NULL, 720*CUR_SCREEN_WIDTH_PER, 14*CUR_SCREEN_HEIGHT_PER, 300*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
			m_btnShowEx.ShowWindow(SW_SHOW);
			m_btnShowEx.EnableWindow(TRUE);
			m_sedtSearch.SetWindowText("");
			m_sedtSearch.ShowWindow(SW_SHOW);
			m_pListMeeting->ShowWindow(SW_SHOW);
			m_pLetterIndex->ShowWindow(SW_SHOW);
			m_stcDoubleCurrent.ShowWindow(SW_HIDE);
			m_btnSwitch.ShowWindow(SW_HIDE);
			m_stcConfType.ShowWindow(SW_HIDE);
			m_edtConfType.ShowWindow(SW_HIDE);
			m_btnConfType.ShowWindow(SW_HIDE);
			m_stcShowType.ShowWindow(SW_HIDE);
			m_edtShowType.ShowWindow(SW_HIDE);
			m_btnShowType.ShowWindow(SW_HIDE);
			m_stcRecordTime.ShowWindow(SW_HIDE);
			m_stcRecordTimeReal.ShowWindow(SW_HIDE);
			m_btnRecordStart.ShowWindow(SW_HIDE);
			m_btnRecordResume.ShowWindow(SW_HIDE);
			m_btnRecordStop.ShowWindow(SW_HIDE);
			m_btnRecordFinish.ShowWindow(SW_HIDE);
			m_stcRecFileName.ShowWindow(SW_HIDE);
			m_stcRecFileNameReal.ShowWindow(SW_HIDE);
			m_stcPlay.ShowWindow(SW_HIDE);
			m_btnPlaySwitch.ShowWindow(SW_HIDE);
			m_edtPlayChoose.ShowWindow(SW_HIDE);
			m_btnPlayChoose.ShowWindow(SW_HIDE);
			m_btnPlayStart.ShowWindow(SW_HIDE);
			m_btnPlayResume.ShowWindow(SW_HIDE);
			m_btnPlayStop.ShowWindow(SW_HIDE);
			m_btnPlayFinish.ShowWindow(SW_HIDE);
			if ( m_pProgressPlay )
			{
				m_pProgressPlay->ShowWindow(SW_HIDE);
			}
			m_stcPlayProgress.ShowWindow(SW_HIDE);
			
			m_btnChildBack.ShowWindow(SW_HIDE);

			m_stcH264.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P60fps.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P50fps.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P30fps.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P25fps.ShowWindow(SW_HIDE);
			m_radiobtnHP720P60fps.ShowWindow(SW_HIDE);
			m_radiobtnHP720P50fps.ShowWindow(SW_HIDE);
			m_radiobtnHP720P30fps.ShowWindow(SW_HIDE);
			m_radiobtnHP720P25fps.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P60fps.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P50fps.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P30fps.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P25fps.ShowWindow(SW_HIDE);
			m_radiobtnBP720P60fps.ShowWindow(SW_HIDE);
			m_radiobtnBP720P50fps.ShowWindow(SW_HIDE);
			m_radiobtnBP720P30fps.ShowWindow(SW_HIDE);
			m_radiobtnBP720P25fps.ShowWindow(SW_HIDE);
			m_radiobtnBP4CIF25fps.ShowWindow(SW_HIDE);
			
			m_radiobtnHP1080P60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P50fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP720P60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP720P50fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP720P30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP720P25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P50fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP720P60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP720P50fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP720P30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP720P25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP4CIF25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPUXGA60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPWXGA30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPSXGA30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPWXGA5fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPSXGA5fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPXGA5fpsShow.ShowWindow(SW_HIDE);
			
			m_edtSearchPlay.SetWindowText("");
			m_edtSearchPlay.ShowWindow(SW_HIDE);
			m_pListVedioFile->ShowWindow(SW_HIDE);
			
			if ( m_pVideoRecordEpLogic->GetSafeHwnd() )
			{
				m_pVideoRecordEpLogic->ShowWindow(SW_HIDE);
			}

			m_pListMeeting->SetSelItem(-1);
			m_pListVedioFile->SetSelItem(-1);
			
			m_emCurrentWnd = emCurrentWndMain;
			
			break;
		}
	case em_Wnd_NoVtr:
		{
			if ( m_emCurrentWnd == emCurrentWndEp )
			{
				break;
			}
			m_stcChildWndTitle.SetWindowText( _T("录像回放设置") );
			m_stcChildWndTitle.SetWindowPos( NULL, 720*CUR_SCREEN_WIDTH_PER, 14*CUR_SCREEN_HEIGHT_PER, 300*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
			m_stcDoubleCurrent.ShowWindow(SW_HIDE);
			m_btnSwitch.ShowWindow(SW_HIDE);
			m_stcConfType.ShowWindow(SW_HIDE);
			m_edtConfType.ShowWindow(SW_HIDE);
			m_btnConfType.ShowWindow(SW_HIDE);
			m_stcShowType.ShowWindow(SW_HIDE);
			m_edtShowType.ShowWindow(SW_HIDE);
			m_btnShowType.ShowWindow(SW_HIDE);
			m_stcRecordTime.ShowWindow(SW_HIDE);
			m_stcRecordTimeReal.ShowWindow(SW_HIDE);
			m_btnRecordStart.ShowWindow(SW_HIDE);
			m_btnRecordResume.ShowWindow(SW_HIDE);
			m_btnRecordStop.ShowWindow(SW_HIDE);
			m_btnRecordFinish.ShowWindow(SW_HIDE);
			m_stcRecFileName.ShowWindow(SW_HIDE);
			m_stcRecFileNameReal.ShowWindow(SW_HIDE);
			m_stcPlay.ShowWindow(SW_HIDE);
			m_btnPlaySwitch.ShowWindow(SW_HIDE);
			m_edtPlayChoose.ShowWindow(SW_HIDE);
			m_btnPlayChoose.ShowWindow(SW_HIDE);
			m_btnPlayStart.ShowWindow(SW_HIDE);
			m_btnPlayResume.ShowWindow(SW_HIDE);
			m_btnPlayStop.ShowWindow(SW_HIDE);
			m_btnPlayFinish.ShowWindow(SW_HIDE);
			if ( m_pProgressPlay )
			{
				m_pProgressPlay->ShowWindow(SW_HIDE);
			}
			m_stcPlayProgress.ShowWindow(SW_HIDE);
			
			m_btnChildBack.ShowWindow(SW_HIDE);

			m_stcH264.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P60fps.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P50fps.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P30fps.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P25fps.ShowWindow(SW_HIDE);
			m_radiobtnHP720P60fps.ShowWindow(SW_HIDE);
			m_radiobtnHP720P50fps.ShowWindow(SW_HIDE);
			m_radiobtnHP720P30fps.ShowWindow(SW_HIDE);
			m_radiobtnHP720P25fps.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P60fps.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P50fps.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P30fps.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P25fps.ShowWindow(SW_HIDE);
			m_radiobtnBP720P60fps.ShowWindow(SW_HIDE);
			m_radiobtnBP720P50fps.ShowWindow(SW_HIDE);
			m_radiobtnBP720P30fps.ShowWindow(SW_HIDE);
			m_radiobtnBP720P25fps.ShowWindow(SW_HIDE);
			m_radiobtnBP4CIF25fps.ShowWindow(SW_HIDE);
			
			m_radiobtnHP1080P60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P50fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP720P60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP720P50fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP720P30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP720P25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P50fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP720P60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP720P50fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP720P30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP720P25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP4CIF25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPUXGA60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPWXGA30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPSXGA30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPWXGA5fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPSXGA5fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPXGA5fpsShow.ShowWindow(SW_HIDE);
			
			m_edtSearchPlay.SetWindowText("");
			m_edtSearchPlay.ShowWindow(SW_HIDE);
			m_pListVedioFile->ShowWindow(SW_HIDE);
			m_pListVedioFile->SetSelItem(-1);
			
			m_emCurrentWnd = emCurrentWndMain;
			
			break;
		}
	case em_Wnd_No_Show:
		{
			m_stcChildWndTitle.SetWindowText( _T("录像回放设置") );
			m_stcChildWndTitle.SetWindowPos( NULL, 720*CUR_SCREEN_WIDTH_PER, 14*CUR_SCREEN_HEIGHT_PER, 300*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

			m_stcDoubleCurrent.ShowWindow(SW_HIDE);
			m_btnSwitch.ShowWindow(SW_HIDE);
			m_stcConfType.ShowWindow(SW_HIDE);
			m_edtConfType.ShowWindow(SW_HIDE);
			m_btnConfType.ShowWindow(SW_HIDE);
			m_stcShowType.ShowWindow(SW_HIDE);
			m_edtShowType.ShowWindow(SW_HIDE);
			m_btnShowType.ShowWindow(SW_HIDE);
			m_stcRecordTime.ShowWindow(SW_HIDE);
			m_stcRecordTimeReal.ShowWindow(SW_HIDE);
			m_btnRecordStart.ShowWindow(SW_HIDE);
			m_btnRecordResume.ShowWindow(SW_HIDE);
			m_btnRecordStop.ShowWindow(SW_HIDE);
			m_btnRecordFinish.ShowWindow(SW_HIDE);
			m_stcRecFileName.ShowWindow(SW_HIDE);
			m_stcRecFileNameReal.ShowWindow(SW_HIDE);
			m_stcPlay.ShowWindow(SW_HIDE);
			m_btnPlaySwitch.ShowWindow(SW_HIDE);
			m_edtPlayChoose.ShowWindow(SW_HIDE);
			m_btnPlayChoose.ShowWindow(SW_HIDE);
			m_btnPlayStart.ShowWindow(SW_HIDE);
			m_btnPlayResume.ShowWindow(SW_HIDE);
			m_btnPlayStop.ShowWindow(SW_HIDE);
			m_btnPlayFinish.ShowWindow(SW_HIDE);
			if ( m_pProgressPlay )
			{
				m_pProgressPlay->ShowWindow(SW_HIDE);
			}
			m_stcPlayProgress.ShowWindow(SW_HIDE);
			
			m_btnChildBack.ShowWindow(SW_HIDE);
			
			m_stcH264.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P60fps.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P50fps.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P30fps.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P25fps.ShowWindow(SW_HIDE);
			m_radiobtnHP720P60fps.ShowWindow(SW_HIDE);
			m_radiobtnHP720P50fps.ShowWindow(SW_HIDE);
			m_radiobtnHP720P30fps.ShowWindow(SW_HIDE);
			m_radiobtnHP720P25fps.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P60fps.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P50fps.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P30fps.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P25fps.ShowWindow(SW_HIDE);
			m_radiobtnBP720P60fps.ShowWindow(SW_HIDE);
			m_radiobtnBP720P50fps.ShowWindow(SW_HIDE);
			m_radiobtnBP720P30fps.ShowWindow(SW_HIDE);
			m_radiobtnBP720P25fps.ShowWindow(SW_HIDE);
			m_radiobtnBP4CIF25fps.ShowWindow(SW_HIDE);
			
			m_radiobtnHP1080P60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P50fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP1080P25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP720P60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP720P50fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP720P30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnHP720P25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P50fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP1080P25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP720P60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP720P50fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP720P30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP720P25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBP4CIF25fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPUXGA60fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPWXGA30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPSXGA30fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPWXGA5fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPSXGA5fpsShow.ShowWindow(SW_HIDE);
			m_radiobtnBPXGA5fpsShow.ShowWindow(SW_HIDE);
			
			m_edtSearchPlay.SetWindowText("");
			m_edtSearchPlay.ShowWindow(SW_HIDE);
			m_pListVedioFile->ShowWindow(SW_HIDE);
			
			m_pListMeeting->SetSelItem(-1);
			m_pListVedioFile->SetSelItem(-1);
			
			m_emCurrentWnd = emCurrentWndMain;
			
			break;
		}
	default:
		break;
	}
}

void CVedioRecordLogic::OnButtonRecordReturn() 
{
	GetParent()->SendMessage( MSG_UI_VTR_TAB_CHANGE, em_WND_VTRSET, 0 );
}

void CVedioRecordLogic::SetConfInfo()
{
	TConRecState* pTConRecState = GetRecConfInfoInSel();	

	if ( pTConRecState == NULL )
	{
		return;
	}

	BOOL bOn = FALSE;
	if ( pTConRecState->m_tInfo.m_bRecDual == TRUE )
	{
		bOn = TRUE;
	}
	m_btnSwitch.SetSwitchState( pTConRecState->m_tInfo.m_bRecDual );
	OnButtonSwitch( (WPARAM)m_btnSwitch.GetSafeHwnd(), 0 );

	RedrawWindow();

	CString strCaption;

	//conftype
	SetConfType();

	//showtype
	SetShowType();

	//btn
	switch ( pTConRecState->m_emState )
	{
	case em_rec_unknow:
		{
			m_btnRecordStart.ShowWindow( SW_SHOW );
			m_btnRecordStop.ShowWindow( SW_HIDE );
			m_btnRecordResume.ShowWindow( SW_HIDE );
			m_btnRecordFinish.ShowWindow( SW_HIDE );
			break;
		}
	case em_rec_working:
		{
			m_btnRecordStart.ShowWindow( SW_HIDE );
			m_btnRecordStop.ShowWindow( SW_SHOW );
			m_btnRecordResume.ShowWindow( SW_HIDE );
			m_btnRecordFinish.ShowWindow( SW_SHOW );
			break;
		}
	case em_rec_pause:
		{
			m_btnRecordStart.ShowWindow( SW_HIDE );
			m_btnRecordStop.ShowWindow( SW_HIDE );
			m_btnRecordResume.ShowWindow( SW_SHOW );
			m_btnRecordFinish.ShowWindow( SW_SHOW );
			break;
		}
	case em_rec_finish:
		{
			m_btnRecordStart.ShowWindow( SW_SHOW );
			m_btnRecordStop.ShowWindow( SW_HIDE );
			m_btnRecordResume.ShowWindow( SW_HIDE );
			m_btnRecordFinish.ShowWindow( SW_HIDE );
			break;
		}
	default:
		break;
	}
}

void CVedioRecordLogic::SetPlayInfo()
{	
	if ( !( m_tUmcConfInfoSel.m_vecTRecInfo.size() > 0 ) )
	{
		return;
	}

	BOOL bOn = FALSE;
	if ( m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_bPlayInDual == TRUE )
	{
		bOn = TRUE;
	}
	m_btnPlaySwitch.SetSwitchState( bOn );
	
	//filesel
	if ( m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_szFileName[0] == '\0')
	{
		m_edtPlayChoose.SetWindowText("文件选择");
	}
	else
	{
		CString strFileName( "文件选择" );
		strFileName += "            ";
		if ( strlen(m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_szFileName) < 35 )
		{
			strFileName += m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_szFileName;
		}
		else
		{
			s8 achFileName[34] = {0};
        	sprintf(achFileName, "%.*s %.*s", 31, m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_szFileName, sizeof("..."), "...");
			strFileName += achFileName;
		}
		m_edtPlayChoose.SetWindowText( strFileName );
	}

	//btn
	switch ( m_tUmcConfInfoSel.m_tConfPlayStatus.m_emState )
	{
	case em_rec_unknow:
		{
			m_btnPlayStart.ShowWindow( SW_SHOW );
			m_btnPlayStop.ShowWindow( SW_HIDE );
			m_btnPlayResume.ShowWindow( SW_HIDE );
			m_btnPlayFinish.ShowWindow( SW_HIDE );
			break;
		}
	case em_rec_working:
		{
			m_btnPlayStart.ShowWindow( SW_HIDE );
			m_btnPlayStop.ShowWindow( SW_SHOW );
			m_btnPlayResume.ShowWindow( SW_HIDE );
			m_btnPlayFinish.ShowWindow( SW_SHOW );
			break;
		}
	case em_rec_pause:
		{
			m_btnPlayStart.ShowWindow( SW_HIDE );
			m_btnPlayStop.ShowWindow( SW_HIDE );
			m_btnPlayResume.ShowWindow( SW_SHOW );
			m_btnPlayFinish.ShowWindow( SW_SHOW );
			break;
		}
	case em_rec_finish:
		{
			m_btnPlayStart.ShowWindow( SW_SHOW );
			m_btnPlayStop.ShowWindow( SW_HIDE );
			m_btnPlayResume.ShowWindow( SW_HIDE );
			m_btnPlayFinish.ShowWindow( SW_HIDE );
			break;
		}
	default:
		break;
	}
}

TConRecState* CVedioRecordLogic::GetRecConfInfoInVec()
{
	TUmcConfInfo* pTUmcConfInfoSel = FindConfInfoSel();

	if ( pTUmcConfInfoSel == NULL )
	{
		return NULL;
	}

	vector<TUmcRecInfo>::iterator itRec = pTUmcConfInfoSel->m_vecTRecInfo.begin();
	for ( ; itRec != pTUmcConfInfoSel->m_vecTRecInfo.end(); itRec++ )
	{
		if ( itRec->m_tInfo.m_emType == em_rec_recorder_conf )
		{
			return itRec;
		}
	}

	return NULL;
}

TConRecState* CVedioRecordLogic::GetRecConfInfoInSel()
{
	vector<TUmcRecInfo>::iterator it = m_tUmcConfInfoSel.m_vecTRecInfo.begin();
	for ( ; it != m_tUmcConfInfoSel.m_vecTRecInfo.end(); it++ )
	{
		if ( it->m_tInfo.m_emType == em_rec_recorder_conf )
		{
			return it;
		}
	}

	return NULL;
}

void CVedioRecordLogic::OnButtonVtrRecordStart() 
{
	if ( SelItemState() == emMeetStatePlay )
	{
		CString strError;
		int nRet = 0;
		strError = "当前会议正在放像，不能录像";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return;
	}
	if ( m_pVTRCtrlIF == NULL )
	{
		return;
	}

	TConRecState* pTConRecState = GetRecConfInfoInSel();
	if ( pTConRecState == NULL )
	{
		return;
	}

	CString strConfType;
	CString strShowType;
	m_edtConfType.GetWindowText(strConfType);
	m_edtShowType.GetWindowText(strShowType);

	if ( strConfType.IsEmpty() && strShowType.IsEmpty() )
	{
		CString strError;
		int nRet = 0;
		strError = "会议格式或演示格式未配置";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return;
	}
	
	CVedioRecordNameEditLogic cLogic( pTConRecState->m_tInfo );
	m_pCVedioRecordNameEditLogic = &cLogic;
	cLogic.DoModal();
	m_pCVedioRecordNameEditLogic = NULL;
}

void CVedioRecordLogic::OnButtonVtrRecordStop() 
{
	if ( m_pVTRCtrlIF == NULL )
	{
		return;
	}
	
	TConRecState* pTConRecState = GetRecConfInfoInSel();
	if ( pTConRecState == NULL )
	{
		return;
	}

	TRecConfRes tRecConfRes;
	tRecConfRes.m_byEqpID = pTConRecState->m_tInfo.m_byEqpID;
	tRecConfRes.m_emType = pTConRecState->m_tInfo.m_emType;
	tRecConfRes.m_wConfID = pTConRecState->m_tInfo.m_wConfID;
	tRecConfRes.m_wMtID = pTConRecState->m_tInfo.m_tMtRecInfo.m_wMtID;
	
	u16 nRet = m_pVTRCtrlIF->RecPauseConfReq( tRecConfRes );
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( _T("暂停录像请求发送失败") );
	}
}

void CVedioRecordLogic::OnButtonVtrRecordFinish() 
{
	if ( m_pVTRCtrlIF == NULL )
	{
		return;
	}
	
	TConRecState* pTConRecState = GetRecConfInfoInSel();
	if ( pTConRecState == NULL )
	{
		return;
	}
	
	TRecConfRes tRecConfRes;
	tRecConfRes.m_byEqpID = pTConRecState->m_tInfo.m_byEqpID;
	tRecConfRes.m_emType = pTConRecState->m_tInfo.m_emType;
	tRecConfRes.m_wConfID = pTConRecState->m_tInfo.m_wConfID;
	tRecConfRes.m_wMtID = pTConRecState->m_tInfo.m_tMtRecInfo.m_wMtID;
	
	u16 nRet = m_pVTRCtrlIF->RecStopConfReq( tRecConfRes );
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( _T("结束录像请求发送失败") );
	}
}

void CVedioRecordLogic::OnButtonConfType() 
{
	ShowChildWnd(em_Wnd_Conf_Type);
	ShowAllConfType();
}

void CVedioRecordLogic::OnButtonShowType() 
{
 	ShowChildWnd(em_Wnd_Show_Type);
	ShowAllShowType();
}

void CVedioRecordLogic::OnButtonChildBack() 
{
	switch( m_emCurrentWnd )
	{
	case emCurrentWndConfTyye:
		{
			SetConfTypeToWndRecordCfg();
			break;
		}
	case emCurrentWndShowTyye:
		{
			SetShowTypeToWndRecordType();
			break;
		}
	case emCurrentWndPlayTyye:
		{
			SetPlayChooseToWndRecordType();
			break;
		}
	default:
		break;
	}

	ShowChildWnd(em_Wnd_Record_Cfg);
}

void CVedioRecordLogic::SetConfTypeToWndRecordCfg()
{
	TConRecState* pTConRecState = GetRecConfInfoInSel();
	if ( pTConRecState == NULL )
	{
		return;
	}
	

	TUmsVidFormat* pTUmsVidFormatMain = &(pTConRecState->m_tInfo.m_tConfRecInfo.m_tConfFormat);
	CString strCaption = _T("H.264");

	bool bFind = false;

	pTUmsVidFormatMain->m_emFormat = emTPVH264;

	if ( m_radiobtnHP1080P60fps.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMain->m_emQualityLvl = emTPH264HP;
		pTUmsVidFormatMain->m_emRes = emTPVHD1080p1920x1080;
		pTUmsVidFormatMain->m_wFrameRate = 60;
		strCaption += _T(" HP 1080P60fps");
		bFind = true;
	}
	else if ( m_radiobtnHP1080P50fps.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMain->m_emQualityLvl = emTPH264HP;
		pTUmsVidFormatMain->m_emRes = emTPVHD1080p1920x1080;
		pTUmsVidFormatMain->m_wFrameRate = 50;
		strCaption += _T(" HP 1080P50fps");
		bFind = true;
	}
	else if ( m_radiobtnHP1080P30fps.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMain->m_emQualityLvl = emTPH264HP;
		pTUmsVidFormatMain->m_emRes = emTPVHD1080p1920x1080;
		pTUmsVidFormatMain->m_wFrameRate = 30;
		strCaption += _T(" HP 1080P30fps");
		bFind = true;
	}
	else if ( m_radiobtnHP1080P25fps.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMain->m_emQualityLvl = emTPH264HP;
		pTUmsVidFormatMain->m_emRes = emTPVHD1080p1920x1080;
		pTUmsVidFormatMain->m_wFrameRate = 25;
		strCaption += _T(" HP 1080P25fps");
		bFind = true;
		
	}
	else if ( m_radiobtnHP720P60fps.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMain->m_emQualityLvl = emTPH264HP;
		pTUmsVidFormatMain->m_emRes = emTPVHD720p1280x720;
		pTUmsVidFormatMain->m_wFrameRate = 60;
		strCaption += _T(" HP 720P60fps");
		bFind = true;
	}
	else if ( m_radiobtnHP720P50fps.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMain->m_emQualityLvl = emTPH264HP;
		pTUmsVidFormatMain->m_emRes = emTPVHD720p1280x720;
		pTUmsVidFormatMain->m_wFrameRate = 50;
		strCaption += _T(" HP 720P50fps");
		bFind = true;
	}
	else if ( m_radiobtnHP720P30fps.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMain->m_emQualityLvl = emTPH264HP;
		pTUmsVidFormatMain->m_emRes = emTPVHD720p1280x720;
		pTUmsVidFormatMain->m_wFrameRate = 30;
		strCaption += _T(" HP 720P30fps");
		bFind = true;
	}
	else if ( m_radiobtnHP720P25fps.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMain->m_emQualityLvl = emTPH264HP;
		pTUmsVidFormatMain->m_emRes = emTPVHD720p1280x720;
		pTUmsVidFormatMain->m_wFrameRate = 25;
		strCaption += _T(" HP 720P25fps");
		bFind = true;
	}
	else if ( m_radiobtnBP1080P60fps.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMain->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMain->m_emRes = emTPVHD1080p1920x1080;
		pTUmsVidFormatMain->m_wFrameRate = 60;
		strCaption += _T(" BP 1080P60fps");
		bFind = true;
	}
	else if ( m_radiobtnBP1080P50fps.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMain->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMain->m_emRes = emTPVHD1080p1920x1080;
		pTUmsVidFormatMain->m_wFrameRate = 50;
		strCaption += _T(" BP 1080P50fps");
		bFind = true;
	}
	else if ( m_radiobtnBP1080P30fps.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMain->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMain->m_emRes = emTPVHD1080p1920x1080;
		pTUmsVidFormatMain->m_wFrameRate = 30;
		strCaption += _T(" BP 1080P30fps");
		bFind = true;
	}
	else if ( m_radiobtnBP1080P25fps.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMain->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMain->m_emRes = emTPVHD1080p1920x1080;
		pTUmsVidFormatMain->m_wFrameRate = 25;
		strCaption += _T(" BP 1080P25fps");
		bFind = true;
	}
	else if ( m_radiobtnBP720P60fps.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMain->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMain->m_emRes = emTPVHD720p1280x720;
		pTUmsVidFormatMain->m_wFrameRate = 60;
		strCaption += _T(" BP 720P60fps");
		bFind = true;
	}
	else if ( m_radiobtnBP720P50fps.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMain->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMain->m_emRes = emTPVHD720p1280x720;
		pTUmsVidFormatMain->m_wFrameRate = 50;
		strCaption += _T(" BP 720P50fps");
		bFind = true;
	}
	else if ( m_radiobtnBP720P30fps.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMain->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMain->m_emRes = emTPVHD720p1280x720;
		pTUmsVidFormatMain->m_wFrameRate = 30;
		strCaption += _T(" BP 720P30fps");
		bFind = true;
	}
	else if ( m_radiobtnBP720P25fps.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMain->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMain->m_emRes = emTPVHD720p1280x720;
		pTUmsVidFormatMain->m_wFrameRate = 25;
		strCaption += _T(" BP 4CIF25fps");
		bFind = true;
	}
	else if ( m_radiobtnBP4CIF25fps.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMain->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMain->m_emRes = emTPV4CIF;
		pTUmsVidFormatMain->m_wFrameRate = 25;
		strCaption += _T(" BP 4CIF25fps");
		bFind = true;
	}
	

	if ( bFind )
	{
		m_edtConfType.SetWindowText( strCaption );
	}
}

void CVedioRecordLogic::SetShowTypeToWndRecordType()
{
	TConRecState* pTConRecState = GetRecConfInfoInSel();
	if ( pTConRecState == NULL )
	{
		return;
	}

	TUmsVidFormat* pTUmsVidFormatMinor = &(pTConRecState->m_tInfo.m_tDualFormat);
	CString strCaption = _T("H.264");

	bool bFind = false;

	CString strFormat = _T("H.264");
	m_stcH264.GetWindowText( strFormat );
	if ( strFormat == _T("H.264") )
	{
		strCaption = _T("H.264");
		pTUmsVidFormatMinor->m_emFormat = emTPVH264;
	}
	
	if ( m_radiobtnHP1080P60fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264HP;
		pTUmsVidFormatMinor->m_emRes = emTPVHD1080p1920x1080;
		pTUmsVidFormatMinor->m_wFrameRate = 60;
		strCaption += _T(" HP 1080P60fps");
		bFind = true;
	}
	else if ( m_radiobtnHP1080P50fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264HP;
		pTUmsVidFormatMinor->m_emRes = emTPVHD1080p1920x1080;
		pTUmsVidFormatMinor->m_wFrameRate = 50;
		strCaption += _T(" HP 1080P50fps");
		bFind = true;
	}
	else if ( m_radiobtnHP1080P30fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264HP;
		pTUmsVidFormatMinor->m_emRes = emTPVHD1080p1920x1080;
		pTUmsVidFormatMinor->m_wFrameRate = 30;
		strCaption += _T(" HP 1080P30fps");
		bFind = true;
	}
	else if ( m_radiobtnHP1080P25fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264HP;
		pTUmsVidFormatMinor->m_emRes = emTPVHD1080p1920x1080;
		pTUmsVidFormatMinor->m_wFrameRate = 25;
		strCaption += _T(" HP 1080P25fps");
		bFind = true;
	}
	else if ( m_radiobtnHP720P60fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264HP;
		pTUmsVidFormatMinor->m_emRes = emTPVHD720p1280x720;
		pTUmsVidFormatMinor->m_wFrameRate = 60;
		strCaption += _T(" HP 720P60fps");
		bFind = true;
	}
	else if ( m_radiobtnHP720P50fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264HP;
		pTUmsVidFormatMinor->m_emRes = emTPVHD720p1280x720;
		pTUmsVidFormatMinor->m_wFrameRate = 50;
		strCaption += _T(" HP 720P50fps");
		bFind = true;
	}
	else if ( m_radiobtnHP720P30fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264HP;
		pTUmsVidFormatMinor->m_emRes = emTPVHD720p1280x720;
		pTUmsVidFormatMinor->m_wFrameRate = 30;
		strCaption += _T(" HP 720P30fps");
		bFind = true;
	}
	else if ( m_radiobtnHP720P25fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264HP;
		pTUmsVidFormatMinor->m_emRes = emTPVHD720p1280x720;
		pTUmsVidFormatMinor->m_wFrameRate = 25;
		strCaption += _T(" HP 720P25fps");
		bFind = true;
	}
	else if ( m_radiobtnBP1080P60fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMinor->m_emRes = emTPVHD1080p1920x1080;
		pTUmsVidFormatMinor->m_wFrameRate = 60;
		strCaption += _T(" BP 1080P60fps");
		bFind = true;
	}
	else if ( m_radiobtnBP1080P50fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMinor->m_emRes = emTPVHD1080p1920x1080;
		pTUmsVidFormatMinor->m_wFrameRate = 50;
		strCaption += _T(" BP 1080P50fps");
		bFind = true;
	}
	else if ( m_radiobtnBP1080P30fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMinor->m_emRes = emTPVHD1080p1920x1080;
		pTUmsVidFormatMinor->m_wFrameRate = 30;
		strCaption += _T(" BP 1080P30fps");
		bFind = true;
	}
	else if ( m_radiobtnBP1080P25fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMinor->m_emRes = emTPVHD1080p1920x1080;
		pTUmsVidFormatMinor->m_wFrameRate = 25;
		strCaption += _T(" BP 1080P25fps");
		bFind = true;
	}
	else if ( m_radiobtnBP720P60fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMinor->m_emRes = emTPVHD720p1280x720;
		pTUmsVidFormatMinor->m_wFrameRate = 60;
		strCaption += _T(" BP 720P60fps");
		bFind = true;
	}
	else if ( m_radiobtnBP720P50fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMinor->m_emRes = emTPVHD720p1280x720;
		pTUmsVidFormatMinor->m_wFrameRate = 50;
		strCaption += _T(" BP 720P50fps");
		bFind = true;
	}
	else if ( m_radiobtnBP720P30fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMinor->m_emRes = emTPVHD720p1280x720;
		pTUmsVidFormatMinor->m_wFrameRate = 30;
		strCaption += _T(" BP 720P30fps");
		bFind = true;
	}
	else if ( m_radiobtnBP720P25fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMinor->m_emRes = emTPVHD720p1280x720;
		pTUmsVidFormatMinor->m_wFrameRate = 25;
		strCaption += _T(" BP 720P25fps");
		bFind = true;
	}
	else if ( m_radiobtnBP4CIF25fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMinor->m_emRes = emTPV4CIF;
		pTUmsVidFormatMinor->m_wFrameRate = 25;
		strCaption += _T(" BP 4CIF25fps");
		bFind = true;
	}
	else if ( m_radiobtnBPUXGA60fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMinor->m_emRes = emTPVGA1600x1200;
		pTUmsVidFormatMinor->m_wFrameRate = 60;
		strCaption += _T(" BP UXGA60fps");
		bFind = true;
	}
	else if ( m_radiobtnBPWXGA30fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMinor->m_emRes = emTPVGA1280x768;
		pTUmsVidFormatMinor->m_wFrameRate = 30;
		strCaption += _T(" BP WXGA30fps");
		bFind = true;
	}
	else if ( m_radiobtnBPSXGA30fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMinor->m_emRes = emTPVGA1280x1024;
		pTUmsVidFormatMinor->m_wFrameRate = 30;
		strCaption += _T(" BP SXGA30fps");
		bFind = true;
	}
	else if ( m_radiobtnBPWXGA5fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMinor->m_emRes = emTPVGA1280x768;
		pTUmsVidFormatMinor->m_wFrameRate = 5;
		strCaption += _T(" BP WXGA5fps");
		bFind = true;
	}
	else if ( m_radiobtnBPSXGA5fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMinor->m_emRes = emTPVGA1280x1024;
		pTUmsVidFormatMinor->m_wFrameRate = 5;
		strCaption += _T(" BP SXGA5fps");
		bFind = true;
	}
	else if ( m_radiobtnBPXGA5fpsShow.GetCheck() == BST_CHECKED )
	{
		pTUmsVidFormatMinor->m_emQualityLvl = emTPH264BP;
		pTUmsVidFormatMinor->m_emRes = emTPVGA1024x768;
		pTUmsVidFormatMinor->m_wFrameRate = 5;
		strCaption += _T(" BP XGA5fps");
		bFind = true;
	}
	
	if (bFind)
	{
		m_edtShowType.SetWindowText( strCaption );
	}
}

void CVedioRecordLogic::ShowAllConfType()
{
	m_radiobtnHP1080P60fps.ShowWindow(SW_SHOW);
	m_radiobtnHP1080P50fps.ShowWindow(SW_SHOW);
	m_radiobtnHP1080P30fps.ShowWindow(SW_SHOW);
	m_radiobtnHP1080P25fps.ShowWindow(SW_SHOW);
	m_radiobtnHP720P60fps.ShowWindow(SW_SHOW);
	m_radiobtnHP720P50fps.ShowWindow(SW_SHOW);
	m_radiobtnHP720P30fps.ShowWindow(SW_SHOW);
	m_radiobtnHP720P25fps.ShowWindow(SW_SHOW);
	m_radiobtnBP1080P60fps.ShowWindow(SW_SHOW);
	m_radiobtnBP1080P50fps.ShowWindow(SW_SHOW);
	m_radiobtnBP1080P30fps.ShowWindow(SW_SHOW);
	m_radiobtnBP1080P25fps.ShowWindow(SW_SHOW);
	m_radiobtnBP720P60fps.ShowWindow(SW_SHOW);
	m_radiobtnBP720P50fps.ShowWindow(SW_SHOW);
	m_radiobtnBP720P30fps.ShowWindow(SW_SHOW);
	m_radiobtnBP720P25fps.ShowWindow(SW_SHOW);
	m_radiobtnBP4CIF25fps.ShowWindow(SW_SHOW);

	m_radiobtnHP1080P60fps.EnableWindow(FALSE);
	m_radiobtnHP1080P50fps.EnableWindow(FALSE);
	m_radiobtnHP1080P30fps.EnableWindow(FALSE);
	m_radiobtnHP1080P25fps.EnableWindow(FALSE);
	m_radiobtnHP720P60fps.EnableWindow(FALSE);
	m_radiobtnHP720P50fps.EnableWindow(FALSE);
	m_radiobtnHP720P30fps.EnableWindow(FALSE);
	m_radiobtnHP720P25fps.EnableWindow(FALSE);
	m_radiobtnBP1080P60fps.EnableWindow(FALSE);
	m_radiobtnBP1080P50fps.EnableWindow(FALSE);
	m_radiobtnBP1080P30fps.EnableWindow(FALSE);
	m_radiobtnBP1080P25fps.EnableWindow(FALSE);
	m_radiobtnBP720P60fps.EnableWindow(FALSE);
	m_radiobtnBP720P50fps.EnableWindow(FALSE);
	m_radiobtnBP720P30fps.EnableWindow(FALSE);
	m_radiobtnBP720P25fps.EnableWindow(FALSE);
	m_radiobtnBP4CIF25fps.EnableWindow(FALSE);
	

	if ( !( m_tUmcConfInfoSel.m_vecTRecInfo.size() > 0 ) )
	{
		return;
	}

	for ( int n = 0; n < m_tUmcConfInfoSel.m_wMainNum; n++ )
	{
		TUmsVidFormat tUmsVidFormat = (m_tUmcConfInfoSel.m_atTpMainVideoRes)[n];
		if ( emTPH264HP == tUmsVidFormat.m_emQualityLvl )
		{
			if ( emTPVHD1080p1920x1080 == tUmsVidFormat.m_emRes )
			{
				if ( 60 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnHP1080P60fps.EnableWindow(TRUE);
				} 
				else if ( 50 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnHP1080P50fps.EnableWindow(TRUE);
				}
				else if ( 30 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnHP1080P30fps.EnableWindow(TRUE);
				}
				else if ( 25 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnHP1080P25fps.EnableWindow(TRUE);
				}
			} 
			else if ( emTPVHD720p1280x720 == tUmsVidFormat.m_emRes )
			{
				if ( 60 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnHP720P60fps.EnableWindow(TRUE);
				}
				else if ( 50 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnHP720P50fps.EnableWindow(TRUE);
				}
				else if ( 30 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnHP720P30fps.EnableWindow(TRUE);
				}
				else if ( 25 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnHP720P25fps.EnableWindow(TRUE);
				}
			}
		}
		else
		{
			if ( emTPVHD1080p1920x1080 == tUmsVidFormat.m_emRes )
			{
				if ( 60 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBP1080P60fps.EnableWindow(TRUE);
				} 
				else if ( 50 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBP1080P50fps.EnableWindow(TRUE);
				}
				else if ( 30 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBP1080P30fps.EnableWindow(TRUE);
				}
				else if ( 25 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBP1080P25fps.EnableWindow(TRUE);
				}
			} 
			else if ( emTPVHD720p1280x720 == tUmsVidFormat.m_emRes )
			{
				if ( 60 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBP720P60fps.EnableWindow(TRUE);
				}
				else if ( 50 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBP720P50fps.EnableWindow(TRUE);
				}
				else if ( 30 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBP720P30fps.EnableWindow(TRUE);
				}
				else if ( 25 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBP720P25fps.EnableWindow(TRUE);
				}
			}
			else if ( emTPV4CIF == tUmsVidFormat.m_emRes )
			{
				if ( 25 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBP4CIF25fps.EnableWindow(TRUE);
				}
			}
		}
	}
}

void CVedioRecordLogic::SetConfType()
{
	m_radiobtnHP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fps.SetCheck(BST_UNCHECKED);

	TConRecState* pTConRecState = GetRecConfInfoInSel();
	if ( pTConRecState == NULL )
	{
		return;
	}

	TUmsVidFormat tUmsVidFormat = pTConRecState->m_tInfo.m_tConfRecInfo.m_tConfFormat;

	if ( emTPH264HP == tUmsVidFormat.m_emQualityLvl )
	{
		if ( emTPVHD1080p1920x1080 == tUmsVidFormat.m_emRes )
		{
			if ( 60 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnHP1080P60fps.SetCheck(BST_CHECKED);
			} 
			else if ( 50 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnHP1080P50fps.SetCheck(BST_CHECKED);
			}
			else if ( 30 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnHP1080P30fps.SetCheck(BST_CHECKED);
			}
			else if ( 25 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnHP1080P25fps.SetCheck(BST_CHECKED);
			}
		} 
		else if ( emTPVHD720p1280x720 == tUmsVidFormat.m_emRes )
		{
			if ( 60 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnHP720P60fps.SetCheck(BST_CHECKED);
			}
			else if ( 50 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnHP720P50fps.SetCheck(BST_CHECKED);
			} 
			else if ( 30 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnHP720P30fps.SetCheck(BST_CHECKED);
			} 
			else if ( 25 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnHP720P25fps.SetCheck(BST_CHECKED);
			} 
		}
	}
	else
	{
		if ( emTPVHD1080p1920x1080 == tUmsVidFormat.m_emRes )
		{
			if ( 60 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBP1080P60fps.SetCheck(BST_CHECKED);
			} 
			else if ( 50 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBP1080P50fps.SetCheck(BST_CHECKED);
			} 
			else if ( 30 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBP1080P30fps.SetCheck(BST_CHECKED);
			} 
			else if ( 25 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBP1080P25fps.SetCheck(BST_CHECKED);
			} 
		} 
		else if ( emTPVHD720p1280x720 == tUmsVidFormat.m_emRes )
		{
			if ( 60 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBP720P60fps.SetCheck(BST_CHECKED);
			} 
			else if ( 50 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBP720P50fps.SetCheck(BST_CHECKED);
			} 
			else if ( 30 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBP720P30fps.SetCheck(BST_CHECKED);
			} 
			else if ( 25 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBP720P25fps.SetCheck(BST_CHECKED);
			} 
		}
		else if ( emTPV4CIF == tUmsVidFormat.m_emRes )
		{
			if ( 25 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBP4CIF25fps.SetCheck(BST_CHECKED);
			} 
		}
	}

	CString strCaption = _T("H.264");
	
	switch ( tUmsVidFormat.m_emQualityLvl )
	{
	case emTPH264HP:
		{
			strCaption += _T(" HP ");
			break;
		}
	case emTPH264BP:
		{
			strCaption += _T(" BP ");
			break;
		}
	default:
		break;
	}
	
	switch ( tUmsVidFormat.m_emRes )
	{
	case emTPVHD1080p1920x1080:
		{
			strCaption += _T("1080P");
			break;
		}
	case emTPVHD720p1280x720:
		{
			strCaption += _T("720P");
			break;
		}
	case emTPV4CIF:
		{
			strCaption += _T("4CIF");
			break;
		}
	default:
		break;
	}
	
	switch ( tUmsVidFormat.m_wFrameRate )
	{
	case 60:
		{
			strCaption += _T("@60fps");
			break;
		}
	case 50:
		{
			strCaption += _T("@50fps");
			break;
		}
	case 30:
		{
			strCaption += _T("@30fps");
			break;
		}
	case 25:
		{
			strCaption += _T("@25fps");
			break;
		}
	default:
		break;
	}

	if ( !( m_tUmcConfInfoSel.m_vecTRecInfo.size() > 0 ) )
	{
		return;
	}

	m_edtConfType.SetWindowText( strCaption );
	if ( m_tUmcConfInfoSel.m_wMainNum == 1 )
	{
		m_edtConfType.EnableWindow(FALSE);
		m_btnConfType.ShowWindow( SW_HIDE );
	}
	else
	{
		m_edtConfType.EnableWindow(TRUE);
		m_btnConfType.ShowWindow( SW_SHOW );
	}
}

void CVedioRecordLogic::SetShowType()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);


	TConRecState* pTConRecState = GetRecConfInfoInSel();
	if ( pTConRecState == NULL )
	{
		return;
	}

	TUmsVidFormat tUmsVidFormat = pTConRecState->m_tInfo.m_tDualFormat;

	if ( emTPH264HP == tUmsVidFormat.m_emQualityLvl )
	{
		if ( emTPVHD1080p1920x1080 == tUmsVidFormat.m_emRes )
		{
			if ( 60 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnHP1080P60fpsShow.SetCheck(BST_CHECKED);
			}
			else if ( 50 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnHP1080P50fpsShow.SetCheck(BST_CHECKED);
			}
			else if ( 30 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnHP1080P30fpsShow.SetCheck(BST_CHECKED);
			}
			else if ( 25 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnHP1080P25fpsShow.SetCheck(BST_CHECKED);
			}
		} 
		else if ( emTPVHD720p1280x720 == tUmsVidFormat.m_emRes )
		{
			if ( 60 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnHP720P60fpsShow.SetCheck(BST_CHECKED);
			} 
			else if ( 50 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnHP720P50fpsShow.SetCheck(BST_CHECKED);
			} 
			else if ( 30 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnHP720P30fpsShow.SetCheck(BST_CHECKED);
			} 
			else if ( 25 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnHP720P25fpsShow.SetCheck(BST_CHECKED);
			} 
		}
	}
	else
	{
		if ( emTPVHD1080p1920x1080 == tUmsVidFormat.m_emRes )
		{
			if ( 60 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBP1080P60fpsShow.SetCheck(BST_CHECKED);
			}
			else if ( 50 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBP1080P50fpsShow.SetCheck(BST_CHECKED);
			}
			else if ( 30 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBP1080P30fpsShow.SetCheck(BST_CHECKED);
			}
			else if ( 25 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBP1080P25fpsShow.SetCheck(BST_CHECKED);
			}
		} 
		else if ( emTPVHD720p1280x720 == tUmsVidFormat.m_emRes )
		{
			if ( 60 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBP720P60fpsShow.SetCheck(BST_CHECKED);
			} 
			else if ( 50 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBP720P50fpsShow.SetCheck(BST_CHECKED);
			} 
			else if ( 30 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBP720P30fpsShow.SetCheck(BST_CHECKED);
			} 
			else if ( 25 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBP720P25fpsShow.SetCheck(BST_CHECKED);
			} 
		}
		else if ( emTPV4CIF == tUmsVidFormat.m_emRes )
		{
			if ( 25 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBP4CIF25fpsShow.SetCheck(BST_CHECKED);
			} 
		}
		else if ( emTPVGA1600x1200 == tUmsVidFormat.m_emRes )
		{
			if ( 60 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBPUXGA60fpsShow.SetCheck(BST_CHECKED);
			} 
		}
		else if ( emTPVGA1280x768 == tUmsVidFormat.m_emRes )
		{
			if ( 30 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBPWXGA30fpsShow.SetCheck(BST_CHECKED);
			}
			else if ( 5 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBPWXGA5fpsShow.SetCheck(BST_CHECKED);
			}
		}
		else if ( emTPVGA1280x1024 == tUmsVidFormat.m_emRes )
		{
			if ( 30 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBPSXGA30fpsShow.SetCheck(BST_CHECKED);
			}
			else if ( 5 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBPSXGA5fpsShow.SetCheck(BST_CHECKED);
			} 
		}
		else if ( emTPVGA1024x768 == tUmsVidFormat.m_emRes )
		{
			if ( 5 == tUmsVidFormat.m_wFrameRate )
			{
				m_radiobtnBPXGA5fpsShow.SetCheck(BST_CHECKED);
			} 
		}
	}

	CString strCaption = _T("H.264");
	
	switch ( tUmsVidFormat.m_emQualityLvl )
	{
	case emTPH264HP:
		{
			strCaption += _T(" HP ");
			break;
		}
	case emTPH264BP:
		{
			strCaption += _T(" BP ");
			break;
		}
	default:
		break;
	}
	
	switch ( tUmsVidFormat.m_emRes )
	{
	case emTPVHD1080p1920x1080:
		{
			strCaption += _T("1080P");
			break;
		}
	case emTPVHD720p1280x720:
		{
			strCaption += _T("720P");
			break;
		}
	case emTPVGA1024x768:
		{
			strCaption += _T("XGA");
			break;
		}
	case emTPVGA1280x1024:
		{
			strCaption += _T("SXGA");
			break;
		}
	case emTPVGA1280x768:
		{
			strCaption += _T("WXGA");
			break;
		}
	case emTPVGA1600x1200:
		{
			strCaption += _T("UXGA");
			break;
		}
	case emTPV4CIF:
		{
			strCaption += _T("4CIF");
			break;
		}
	default:
		break;
	}
	
	switch ( tUmsVidFormat.m_wFrameRate )
	{
	case 60:
		{
			strCaption += _T("@60fps");
			break;
		}
	case 50:
		{
			strCaption += _T("@50fps");
			break;
		}
	case 30:
		{
			strCaption += _T("@30fps");
			break;
		}
	case 25:
		{
			strCaption += _T("@25fps");
			break;
		}
	case 5:
		{
			strCaption += _T("@5fps");
			break;
		}
	default:
		break;
	}

	m_edtShowType.SetWindowText( strCaption );
 	if ( m_tUmcConfInfoSel.m_wMinorNum == 1 )
 	{
		m_edtShowType.EnableWindow(FALSE);
		m_btnShowType.ShowWindow( SW_HIDE );
 	}
 	else
	{
		m_edtShowType.EnableWindow(TRUE);
		m_btnShowType.ShowWindow( SW_SHOW );
	}
}

void CVedioRecordLogic::ShowAllShowType()
{
	m_radiobtnHP1080P60fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnHP1080P50fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnHP1080P30fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnHP1080P25fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnHP720P60fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnHP720P50fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnHP720P30fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnHP720P25fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnBP1080P60fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnBP1080P50fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnBP1080P30fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnBP1080P25fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnBP720P60fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnBP720P50fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnBP720P30fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnBP720P25fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnBP4CIF25fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnBPUXGA60fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnBPWXGA30fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnBPSXGA30fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnBPWXGA5fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnBPSXGA5fpsShow.ShowWindow(SW_SHOW);
	m_radiobtnBPXGA5fpsShow.ShowWindow(SW_SHOW);

	m_radiobtnHP1080P60fpsShow.EnableWindow(FALSE);
	m_radiobtnHP1080P50fpsShow.EnableWindow(FALSE);
	m_radiobtnHP1080P30fpsShow.EnableWindow(FALSE);
	m_radiobtnHP1080P25fpsShow.EnableWindow(FALSE);
	m_radiobtnHP720P60fpsShow.EnableWindow(FALSE);
	m_radiobtnHP720P50fpsShow.EnableWindow(FALSE);
	m_radiobtnHP720P30fpsShow.EnableWindow(FALSE);
	m_radiobtnHP720P25fpsShow.EnableWindow(FALSE);
	m_radiobtnBP1080P60fpsShow.EnableWindow(FALSE);
	m_radiobtnBP1080P50fpsShow.EnableWindow(FALSE);
	m_radiobtnBP1080P30fpsShow.EnableWindow(FALSE);
	m_radiobtnBP1080P25fpsShow.EnableWindow(FALSE);
	m_radiobtnBP720P60fpsShow.EnableWindow(FALSE);
	m_radiobtnBP720P50fpsShow.EnableWindow(FALSE);
	m_radiobtnBP720P30fpsShow.EnableWindow(FALSE);
	m_radiobtnBP720P25fpsShow.EnableWindow(FALSE);
	m_radiobtnBP4CIF25fpsShow.EnableWindow(FALSE);
	m_radiobtnBPUXGA60fpsShow.EnableWindow(FALSE);
	m_radiobtnBPWXGA30fpsShow.EnableWindow(FALSE);
	m_radiobtnBPSXGA30fpsShow.EnableWindow(FALSE);
	m_radiobtnBPWXGA5fpsShow.EnableWindow(FALSE);
	m_radiobtnBPSXGA5fpsShow.EnableWindow(FALSE);
	m_radiobtnBPXGA5fpsShow.EnableWindow(FALSE);
	
	if ( !( m_tUmcConfInfoSel.m_vecTRecInfo.size() > 0 ) )
	{
		return;
	}

	for ( int n = 0; n < m_tUmcConfInfoSel.m_wMinorNum; n++ )
	{
		TUmsVidFormat tUmsVidFormat = (m_tUmcConfInfoSel.m_atTpMinorVideoRes)[n];
		if ( emTPH264HP == tUmsVidFormat.m_emQualityLvl )
		{
			if ( emTPVHD1080p1920x1080 == tUmsVidFormat.m_emRes )
			{
				if ( 60 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnHP1080P60fpsShow.EnableWindow(TRUE);
				}
				else if ( 50 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnHP1080P50fpsShow.EnableWindow(TRUE);
				}
				else if ( 30 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnHP1080P30fpsShow.EnableWindow(TRUE);
				}
				else if ( 25 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnHP1080P25fpsShow.EnableWindow(TRUE);
				}
			} 
			else if ( emTPVHD720p1280x720 == tUmsVidFormat.m_emRes )
			{
				if ( 60 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnHP720P60fpsShow.EnableWindow(TRUE);
				} 
				else if ( 50 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnHP720P50fpsShow.EnableWindow(TRUE);
				} 
				else if ( 30 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnHP720P30fpsShow.EnableWindow(TRUE);
				} 
				else if ( 25 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnHP720P25fpsShow.EnableWindow(TRUE);
				} 
			}
		}
		else
		{
			if ( emTPVHD1080p1920x1080 == tUmsVidFormat.m_emRes )
			{
				if ( 60 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBP1080P60fpsShow.EnableWindow(TRUE);
				}
				else if ( 50 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBP1080P50fpsShow.EnableWindow(TRUE);
				}
				else if ( 30 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBP1080P30fpsShow.EnableWindow(TRUE);
				}
				else if ( 25 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBP1080P25fpsShow.EnableWindow(TRUE);
				}
			} 
			else if ( emTPVHD720p1280x720 == tUmsVidFormat.m_emRes )
			{
				if ( 60 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBP720P60fpsShow.EnableWindow(TRUE);
				} 
				else if ( 50 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBP720P50fpsShow.EnableWindow(TRUE);
				} 
				else if ( 30 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBP720P30fpsShow.EnableWindow(TRUE);
				} 
				else if ( 25 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBP720P25fpsShow.EnableWindow(TRUE);
				} 
			}
			else if ( emTPV4CIF == tUmsVidFormat.m_emRes )
			{
				if ( 25 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBP4CIF25fpsShow.EnableWindow(TRUE);
				} 
			}
			else if ( emTPVGA1600x1200 == tUmsVidFormat.m_emRes )
			{
				if ( 60 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBPUXGA60fpsShow.EnableWindow(TRUE);
				} 
			}
			else if ( emTPVGA1280x768 == tUmsVidFormat.m_emRes )
			{
				if ( 30 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBPWXGA30fpsShow.EnableWindow(TRUE);
				}
				else if ( 5 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBPWXGA5fpsShow.EnableWindow(TRUE);
				}
			}
			else if ( emTPVGA1280x1024 == tUmsVidFormat.m_emRes )
			{
				if ( 30 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBPSXGA30fpsShow.EnableWindow(TRUE);
				}
				else if ( 5 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBPSXGA5fpsShow.EnableWindow(TRUE);
				} 
			}
			else if ( emTPVGA1024x768 == tUmsVidFormat.m_emRes )
			{
				if ( 5 == tUmsVidFormat.m_wFrameRate )
				{
					m_radiobtnBPXGA5fpsShow.EnableWindow(TRUE);
				} 
			}
		}
	}
}

void CVedioRecordLogic::OnBUTTONCONFHP1080P60fps() 
{
	m_radiobtnHP1080P60fps.SetCheck(BST_CHECKED);
	m_radiobtnHP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fps.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONCONFHP1080P50fps()
{
	m_radiobtnHP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fps.SetCheck(BST_CHECKED);
	m_radiobtnHP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fps.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONCONFHP1080P30fps()
{
	m_radiobtnHP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fps.SetCheck(BST_CHECKED);
	m_radiobtnHP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fps.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONCONFHP1080P25fps()
{
	m_radiobtnHP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fps.SetCheck(BST_CHECKED);
	m_radiobtnHP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fps.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONCONFHP720P60fps()
{
	m_radiobtnHP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fps.SetCheck(BST_CHECKED);
	m_radiobtnHP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fps.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONCONFHP720P50fps()
{
	m_radiobtnHP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fps.SetCheck(BST_CHECKED);
	m_radiobtnHP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fps.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONCONFHP720P30fps()
{
	m_radiobtnHP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fps.SetCheck(BST_CHECKED);
	m_radiobtnHP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fps.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONCONFHP720P25fps()
{
	m_radiobtnHP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fps.SetCheck(BST_CHECKED);
	m_radiobtnBP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fps.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONCONFBP1080P60fps()
{
	m_radiobtnHP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fps.SetCheck(BST_CHECKED);
	m_radiobtnBP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fps.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONCONFBP1080P50fps()
{
	m_radiobtnHP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fps.SetCheck(BST_CHECKED);
	m_radiobtnBP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fps.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONCONFBP1080P30fps()
{
	m_radiobtnHP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fps.SetCheck(BST_CHECKED);
	m_radiobtnBP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fps.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONCONFBP1080P25fps()
{
	m_radiobtnHP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fps.SetCheck(BST_CHECKED);
	m_radiobtnBP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fps.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONCONFBP720P60fps()
{
	m_radiobtnHP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fps.SetCheck(BST_CHECKED);
	m_radiobtnBP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fps.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONCONFBP720P50fps()
{
	m_radiobtnHP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fps.SetCheck(BST_CHECKED);
	m_radiobtnBP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fps.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONCONFBP720P30fps()
{
	m_radiobtnHP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fps.SetCheck(BST_CHECKED);
	m_radiobtnBP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fps.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONCONFBP720P25fps()
{
	m_radiobtnHP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fps.SetCheck(BST_CHECKED);
	m_radiobtnBP4CIF25fps.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONCONFBP4CIF25fps()
{
	m_radiobtnHP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fps.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fps.SetCheck(BST_CHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWHP1080P60fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWHP1080P50fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWHP1080P30fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWHP1080P25fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWHP720P60fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWHP720P50fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWHP720P30fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWHP720P25fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWBP1080P60fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWBP1080P50fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWBP1080P30fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWBP1080P25fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWBP720P60fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWBP720P50fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWBP720P30fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWBP720P25fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWBP4CIF25fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWBPUXGA60fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWBPWXGA30fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWBPSXGA30fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWBPWXGA5fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWBPSXGA5fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_CHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_UNCHECKED);
}

void CVedioRecordLogic::OnBUTTONSHOWBPXGA5fps()
{
	m_radiobtnHP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnHP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP1080P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P50fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP720P25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBP4CIF25fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPUXGA60fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA30fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPWXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPSXGA5fpsShow.SetCheck(BST_UNCHECKED);
	m_radiobtnBPXGA5fpsShow.SetCheck(BST_CHECKED);
}

LRESULT CVedioRecordLogic::OnButtonSwitch( WPARAM wParam, LPARAM lParam )
{
	HWND hWnd = (HWND)wParam;
	if ( hWnd == m_btnSwitch.GetSafeHwnd() )
	{
		TConRecState* pTConRecState = GetRecConfInfoInSel();
		if ( pTConRecState == NULL )
		{
			return 0;
		}
		
		BOOL bSwitch = m_btnSwitch.GetSwitchState();
		pTConRecState->m_tInfo.m_bRecDual = bSwitch;
		m_btnShowType.EnableWindow(bSwitch);
	}
	else if ( hWnd == m_btnPlaySwitch.GetSafeHwnd() )
	{
		if ( !( m_tUmcConfInfoSel.m_vecTRecInfo.size() > 0 ) )
		{
			return 0;
		}
		
		m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_bPlayInDual = m_btnPlaySwitch.GetSwitchState();
	}
	else if ( hWnd == m_btnShowEx.GetSafeHwnd() )
	{
		bool bOn = false;
		bOn = m_btnShowEx.GetSwitchState();
		if ( bOn )
		{
			CRect rect;
			m_btnShowEx.GetWindowRect(&rect);
			CVideoRecordShowOpt::GetDlgPtr()->ShowWindow(SW_SHOW);
			CVideoRecordShowOpt::GetDlgPtr()->SetWindowPos(NULL, rect.right - 232, rect.bottom, 232, 162, SWP_SHOWWINDOW );
		}
		else
		{
			CVideoRecordShowOpt::GetDlgPtr()->ShowWindow(SW_HIDE);
		}
	}

	return 0;
}

void CVedioRecordLogic::OnButtonVtrPalybackStart() 
{
	if ( SelItemState() == emMeetStateRec || SelItemState() == emMeetStateRecMt )
	{
		CString strError;
		int nRet = 0;
		strError = "当前会议正在录像，不能放像";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return;
	}

	if ( m_pVTRCtrlIF == NULL )
	{
		return;
	}


	if ( !( m_tUmcConfInfoSel.m_vecTRecInfo.size() > 0 ) )
	{
		return;
	}

	CString strPlayChoose;
	m_edtPlayChoose.GetWindowText(strPlayChoose);
	if ( strPlayChoose == "文件选择" )
	{
		CString strError;
		int nRet = 0;
		strError = "请选择回放文件";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return;
	}

	bool bFind = false;
	vector<TRecFileInfo> vecTVtrFileInfo;
	TRecFileInfo tRecFileInfo = m_pVTRCtrlIF->FindFileName( m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_szFileName );

	if ( tRecFileInfo.m_szFilelName[0] == '\0' )
	{
		s32 nRet = 0;
		CString str;
		str.Format( "%s已不存在，不能回放", m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_szFileName );
		MESSAGEWNDBOX( str, this , nRet , FALSE );
		return;
	}

	if ( !CVedioRecordNameEditLogic::IsExistElement(tRecFileInfo.m_szFilelName) )
	{
		s32 nRet = 0;
		CString str;
		str.Format( "不存在回放文件格式，不能回放" );
		MESSAGEWNDBOX( str, this , nRet , FALSE );
		return;
	}

	//解析文件名
	TUmsVidFormat tConfFormat;
	TUmsVidFormat tDualFormat;
	BOOL bDual;
	CVedioRecordNameEditLogic::ParseRecordName( tRecFileInfo.m_szFilelName, tConfFormat, bDual, tDualFormat );

	BOOL bSwitchDual = m_btnPlaySwitch.GetSwitchState();
	BOOL bRet = FALSE;
	if ( bSwitchDual )
	{
		if ( bDual )
		{
			bRet = CheckPalyFormat( tConfFormat, bDual, tDualFormat );
		}
		else
		{
			s32 nRet = 0;
			CString str;
			str.Format( "放像失败：录像中无演示" );
			MESSAGEWNDBOX( str, this , nRet , FALSE );
			return;
		}
	}
	else
	{
		bRet = CheckPalyFormat( tConfFormat, FALSE, tDualFormat );
	}

	if ( !bRet )
	{
		s32 nRet = 0;
		CString str;
		str.Format( "回放格式不匹配，不能回放" );
		MESSAGEWNDBOX( str, this , nRet , FALSE );
		return;
	}

	m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_tConfFormat = tConfFormat;
	if ( bDual )
	{
		m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_tDualFormat = tDualFormat;
	}

	u16 nRet = m_pVTRCtrlIF->RecStartPlayReq( m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo );
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( _T("开始回放请求发送失败") );
		return;
	}
}

void CVedioRecordLogic::SetPlayChooseToWndPlayChoose() 
{
	if ( m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_szFileName[0] == '\0' )
	{
		m_edtSearchPlay.SetWindowText("");
		m_pListVedioFile->SetSelItem(-1);
	}
}

void CVedioRecordLogic::SetPlayChooseToWndRecordType()
{
	if ( !( m_tUmcConfInfoSel.m_vecTRecInfo.size() > 0 ) )
	{
		return;
	}

	if ( m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_szFileName[0] == '\0' )
	{
		m_edtPlayChoose.SetWindowText("文件选择");
	}
	else
	{
		CString strFileName( "文件选择" );
		strFileName += "            ";
		if ( strlen(m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_szFileName) < 35 )
		{
			strFileName += m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_szFileName;
		}
		else
		{
			s8 achFileName[34] = {0};
			sprintf(achFileName, "%.*s %.*s", 31, m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_szFileName, sizeof("..."), "...");
			strFileName += achFileName;
		}
		m_edtPlayChoose.SetWindowText( strFileName );

//		m_edtPlayChoose.SetWindowText( m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_szFileName );
	}
}

bool CVedioRecordLogic::OnClickVedioFileLstItem( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
		if ( const Data_FileInfo *pItemInfo = dynamic_cast<const Data_FileInfo*>( pBaseItem->GetUserData() )) 
        {	
			if ( !( m_tUmcConfInfoSel.m_vecTRecInfo.size() > 0 ) )
			{
				return true;
			}

			strncpy( m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_szFileName, pItemInfo->m_tRecFileInfo.m_szFilelName, TP_REC_FILE_LEN-1 );
		}
    }
	
	return true;
}

bool CVedioRecordLogic::OnClickVedioFileLstItemIcon( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();
		if ( const Data_FileInfo *pItemInfo = dynamic_cast<const Data_FileInfo*>( pBaseItem->GetUserData() )) 
        {
			if ( !( m_tUmcConfInfoSel.m_vecTRecInfo.size() > 0 ) )
			{
				return true;
			}
			
			strncpy( m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_szFileName, pItemInfo->m_tRecFileInfo.m_szFilelName, TP_REC_FILE_LEN-1 );
		}
    }
	
	return true;
}

void CVedioRecordLogic::OnButtonPlayChoose()
{
	ShowChildWnd(em_Wnd_play_choose);
 	SetPlayChooseToWndPlayChoose();
}

LRESULT CVedioRecordLogic::OnRecStartConfRsp( WPARAM wparam, LPARAM lparam )
{
	EmUseReccorderRes emRet = static_cast<EmUseReccorderRes>(lparam);

	if ( emRet == em_rec_success )
	{
	}
	else
	{
		ShowTip(emRet);
	}
	
	return S_OK;
}

LRESULT CVedioRecordLogic::OnRecStopRecordRsp( WPARAM wparam, LPARAM lparam )
{
	EmUseReccorderRes emRet = (EmUseReccorderRes)lparam;
	
	if ( emRet == em_rec_success )
	{
	}
	else
	{
		ShowTip(emRet);
	}
	
	return S_OK;
}

LRESULT CVedioRecordLogic::OnRecPauseRecordRsp( WPARAM wparam, LPARAM lparam )
{
	EmUseReccorderRes emRet = (EmUseReccorderRes)lparam;
	
	if ( emRet == em_rec_success )
	{
	}
	else
	{
		ShowTip(emRet);
	}
	
	return S_OK;
}

LRESULT CVedioRecordLogic::OnRecResumeRecordRsp( WPARAM wparam, LPARAM lparam )
{
	EmUseReccorderRes emRet = (EmUseReccorderRes)lparam;
	
	if ( emRet == em_rec_success )
	{
	}
	else
	{
		ShowTip(emRet);
	}
	
	return S_OK;
}

LRESULT CVedioRecordLogic::OnRecStartPlayRsp( WPARAM wparam, LPARAM lparam )
{	
	EmUseReccorderRes emRet = (EmUseReccorderRes)lparam;
	
	if ( emRet == em_rec_success )
	{
	}
	else
	{
		ShowTip(emRet);
	}

	return S_OK;
}

LRESULT CVedioRecordLogic::OnRecStopPlayRsp( WPARAM wparam, LPARAM lparam )
{	
	EmUseReccorderRes emRet = (EmUseReccorderRes)lparam;
	
	if ( emRet == em_rec_success )
	{
	}
	else
	{
		ShowTip(emRet);
	}

	return S_OK;
}

LRESULT CVedioRecordLogic::OnRecResumePlayRsp( WPARAM wparam, LPARAM lparam )
{	
	EmUseReccorderRes emRet = (EmUseReccorderRes)lparam;
	
	if ( emRet == em_rec_success )
	{
	}
	else
	{
		ShowTip(emRet);
	}
	
	return S_OK;
}

LRESULT CVedioRecordLogic::OnRecPausePlayRsp( WPARAM wparam, LPARAM lparam )
{	
	EmUseReccorderRes emRet = (EmUseReccorderRes)lparam;
	
	if ( emRet == em_rec_success )
	{
	}
	else
	{
		ShowTip(emRet);
	}
	
	return S_OK;
}

LRESULT CVedioRecordLogic::OnTimer( WPARAM wparam, LPARAM lparam )
{
	vector<TUmcConfInfo>::iterator itConf = m_vecTUmcConfInfo.begin();
	for ( ; itConf != m_vecTUmcConfInfo.end(); itConf++ )
	{
		vector<TUmcRecInfo>::iterator itRec = itConf->m_vecTRecInfo.begin();
		for ( ; itRec != itConf->m_vecTRecInfo.end(); itRec++ )
		{
			if ( itRec->m_emState == em_rec_working )
			{
				itRec->m_dwRecTime++;
			}
		}

		if ( itConf->m_tConfPlayStatus.m_emState == em_rec_working
			&& itConf->m_tConfPlayStatus.m_dwCurTime < itConf->m_tConfPlayStatus.m_dwTotalTime )
		{
			itConf->m_tConfPlayStatus.m_dwCurTime++;

			//录像、放像到时间不需要自动停止，服务器会停止
// 			if ( itConf->m_tConfPlayStatus.m_dwCurTime == itConf->m_tConfPlayStatus.m_dwTotalTime )
// 			{
// 				TPlayStatusMdyInfo tPlayStatusMdyInfo;
// 				tPlayStatusMdyInfo.m_byEqpID = itConf->m_tConfPlayStatus.m_tInfo.m_byEqpID;
// 				tPlayStatusMdyInfo.m_wConfID = itConf->m_tConfPlayStatus.m_tInfo.m_wConfID;
// 				
// 				u16 nRet = m_pVTRCtrlIF->RecStopPlayReq( tPlayStatusMdyInfo );
// 				if ( nRet != NO_ERROR )
// 				{
// 					MESSAGEWND( _T("结束回放请求发送失败") );
// 				}
// 			}
		}
	}

	if (  m_tUmcConfInfoSel.m_vecTRecInfo.size() == 0  )
	{
		if ( m_emCurrentWnd == emCurrentWndMain )
		{
			ShowChildWnd( em_Wnd_No_Show );
		}
		return S_OK;
	}

	


	ShowSelItem();


	return S_OK;
}

LRESULT CVedioRecordLogic::OnUpdateEDITSearch( WPARAM wParam, LPARAM lParam )
{
	HWND wnd = (HWND)wParam;

	if ( m_sedtSearch.GetSafeHwnd() == wnd )
	{
		RefreshRecList();
	}
	else if ( m_edtSearchPlay.GetSafeHwnd() == wnd )
	{
		RefreshRecFileList();
	}

	return S_OK;
}

void CVedioRecordLogic::RefreshRecFileList()
{
	vector<TRecFileInfo> vecTRecFileInfoNoSuffix;
	if ( m_pVTRCtrlIF != NULL )
	{
		m_pVTRCtrlIF->GetRecFileListInfoNoSuffix( vecTRecFileInfoNoSuffix );
	}
	
	
	vector<TRecFileInfo> vecTRecFileInfoSearch;
	CString strSearch;
	m_edtSearchPlay.GetWindowText(strSearch);
	if ( strSearch != _T("") )
	{
		vector<TRecFileInfo>::iterator it = vecTRecFileInfoNoSuffix.begin();
		for ( ; it != vecTRecFileInfoNoSuffix.end(); it++ )
		{
			BOOL bFind = FALSE;			
			bFind = CUmcwebCommon::HZPYMatchList( strSearch, it->m_szFilelName );
			if ( bFind )
			{		
				vecTRecFileInfoSearch.push_back(*it);
			}
		}
	}
	else
	{
		vecTRecFileInfoSearch = vecTRecFileInfoNoSuffix;
	}
	
	if ( m_pListVedioFile != NULL )
	{
		Value_ListFile val_ListFile( &vecTRecFileInfoSearch, "CVedioRecordLogic::OnClickVedioFileLstItem", 2 );
		m_pListVedioFile->SetData( val_ListFile );
 	}


	m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_szFileName[0] = '\0';
	m_pListVedioFile->SetSelItem(-1);
}

void CVedioRecordLogic::OnButtonVtrPalybackResume() 
{
	if ( m_pVTRCtrlIF == NULL )
	{
		return;
	}

	if ( !( m_tUmcConfInfoSel.m_vecTRecInfo.size() > 0 ) )
	{
		return;
	}

	TPlayStatusMdyInfo tPlayStatusMdyInfo;
	tPlayStatusMdyInfo.m_byEqpID = m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_byEqpID;
	tPlayStatusMdyInfo.m_wConfID = m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_wConfID;
	
	u16 nRet = m_pVTRCtrlIF->RecResumePlayReq( tPlayStatusMdyInfo );
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( _T("继续回放请求发送失败") );
	}
}

void CVedioRecordLogic::OnButtonVtrRecordResume() 
{
	if ( m_pVTRCtrlIF == NULL )
	{
		return;
	}

	TConRecState* pTConRecState = GetRecConfInfoInSel();
	if ( pTConRecState == NULL )
	{
		return;
	}

	TRecConfRes tRecConfRes;
	tRecConfRes.m_byEqpID = pTConRecState->m_tInfo.m_byEqpID;
	tRecConfRes.m_emType = pTConRecState->m_tInfo.m_emType;
	tRecConfRes.m_wConfID = pTConRecState->m_tInfo.m_wConfID;
	tRecConfRes.m_wMtID = pTConRecState->m_tInfo.m_tMtRecInfo.m_wMtID;

	u16 nRet = m_pVTRCtrlIF->RecResumeConfReq( tRecConfRes );
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( _T("继续录像请求发送失败") );
	}
}

void CVedioRecordLogic::OnButtonPlayFinish()
{
	if ( m_pVTRCtrlIF == NULL )
	{
		return;
	}

	if ( !( m_tUmcConfInfoSel.m_vecTRecInfo.size() > 0 ) )
	{
		return;
	}
	
	TPlayStatusMdyInfo tPlayStatusMdyInfo;
	tPlayStatusMdyInfo.m_byEqpID = m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_byEqpID;
	tPlayStatusMdyInfo.m_wConfID = m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_wConfID;
	
	u16 nRet = m_pVTRCtrlIF->RecStopPlayReq( tPlayStatusMdyInfo );
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( _T("结束回放请求发送失败") );
	}
}

void CVedioRecordLogic::OnButtonPlayPause()
{
	if ( m_pVTRCtrlIF == NULL )
	{
		return;
	}

	if ( !( m_tUmcConfInfoSel.m_vecTRecInfo.size() > 0 ) )
	{
		return;
	}
	
	TPlayStatusMdyInfo tPlayStatusMdyInfo;
	tPlayStatusMdyInfo.m_byEqpID = m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_byEqpID;
	tPlayStatusMdyInfo.m_wConfID = m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_wConfID;
	
	u16 nRet = m_pVTRCtrlIF->RecPausePlayReq( tPlayStatusMdyInfo );
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( _T("暂停回放请求发送失败") );
	}
}

void CVedioRecordLogic::ShowTip( EmUseReccorderRes emRes )
{
	switch( emRes )
	{
	case em_rec_success:
		{
			break;
		}
	case em_rec_invalid:
		{
			MESSAGEWND("无效的录像机");
			break;
		}
	case em_rec_unregisted:
		{
			MESSAGEWND("录像机未注册");
			break;
		}
	case em_rec_no_resource:
		{
			MESSAGEWND("无可用资源");
			break;
		}
	case em_rec_invalid_conf:
		{
			MESSAGEWND("会场不在线");
			break;
		}
	case em_rec_invalid_format:
		{
			MESSAGEWND("无效的格式");
			break;
		}
	case em_rec_unknow_rectype:
		{
			MESSAGEWND("未知的录制类型");
			break;
		}
	case em_rec_invalid_mt:
		{
			MESSAGEWND("无效的会场");
			break;
		}
	case em_rec_recordering:
		{
			MESSAGEWND("正在录像");
			break;
		}
	case em_rec_playing:
		{
			MESSAGEWND("正在放像");
			break;
		}
	case em_rec_chair_playing:
		{
			MESSAGEWND("上级正在进行放像");
			break;
		}
	case em_rec_server_reject:
		{
			MESSAGEWND("录播服务器拒绝");
			break;
		}
	case em_rec_invalid_rec_info:
		{
			MESSAGEWND("未找到对应的录制信息");
			break;
		}
	case em_rec_invalid_play_info:
		{
			MESSAGEWND("未找到对应的播放信息");
			break;
		}
	case em_rec_no_in_pause:
		{
			MESSAGEWND("会议不处于暂停状态");
			break;
		}
	case em_rec_mt_offline:
		{
			MESSAGEWND("会场掉线");
			break;
		}
	case em_rec_name_hasunderline:
		{
			MESSAGEWND("名字中包含下划线");
			break;
		}
	case em_rec_longnamesize:
		{
			MESSAGEWND("过长的文件名");
			break;
		}
	case em_rec_fileexist:
		{
			MESSAGEWND("文件已经存在");
			break;
		}
	case em_rec_fileinuse:
		{
			MESSAGEWND("文件正在被操作");
			break;
		}
	case em_rec_loadlib_failed:
		{
			MESSAGEWND("录播服务器调用lib库失败");
			break;
		}
	case em_rec_setrecmode_failed:
		{
			MESSAGEWND("设置录像方式失败");
			break;
		}
	case em_rec_publicfailed:
		{
			MESSAGEWND("发布失败");
			break;
		}
	case em_rec_inrequesting:
		{
			MESSAGEWND("正在请求");
			break;
		}
	case em_rec_req_failed:
		{
			MESSAGEWND("请求失败");
			break;
		}
	case em_rec_norecord:
		{
			MESSAGEWND("未录像");
			break;
		}
	case em_rec_file_damange:
		{
			MESSAGEWND("放像文件损坏");
			break;
		}
		case em_rec_in_stopping:
		{
			MESSAGEWND("录像正在被停止");
			break;
		}
	case em_rec_in_pausing:
		{
			MESSAGEWND("录像处于处于暂停状态");
			break;
		}
	case em_rec_no_in_working:
		{
			MESSAGEWND("不处于工作状态");
			break;
		}
	case em_rec_invalid_channel:
		{
			MESSAGEWND("无效的通道");
			break;
		}
	case em_rec_unmatch_format:
		{
			MESSAGEWND("格式未匹配");
			break;
		}
	case em_rec_unknow_reason:
		{
			MESSAGEWND("未知错误");
			break;
		}
	default:
		break;
	}
}

void CVedioRecordLogic::LoadScheme( EmScheme emScheme )
{
	switch( emScheme )
	{
	case emSchmeControlBtn:
		{
			TConRecState* pTConRecState = GetRecConfInfoInSel();
			if ( pTConRecState == NULL )
			{
				break;
			}

			if ( pTConRecState->m_emState == em_rec_working || pTConRecState->m_emState == em_rec_pause )
			{
				m_btnSwitch.EnableWindow(FALSE);
				m_btnShowType.EnableWindow(FALSE);
				m_btnConfType.EnableWindow(FALSE);
			}
			else
			{
				m_btnSwitch.EnableWindow(TRUE);
				m_btnShowType.EnableWindow(TRUE);
				m_btnConfType.EnableWindow(TRUE);
			}

			if ( !( m_tUmcConfInfoSel.m_vecTRecInfo.size() > 0 ) )
			{
				break;
			}
 
			
			if ( m_tUmcConfInfoSel.m_tConfPlayStatus.m_emState == em_rec_working
				|| m_tUmcConfInfoSel.m_tConfPlayStatus.m_emState == em_rec_pause )
			{
				m_btnPlaySwitch.EnableWindow(FALSE);
				m_btnPlayChoose.EnableWindow(FALSE);
			}
			else
			{
				m_btnPlaySwitch.EnableWindow(TRUE);
				m_btnPlayChoose.EnableWindow(TRUE);
			}

			break;
		}
	default:
		break;
	}
}

LRESULT CVedioRecordLogic::OnHideOptn( WPARAM wParam, LPARAM lParam )
{
	m_btnShowEx.SetSwitchState(FALSE);
	
	return S_OK;
}

LRESULT CVedioRecordLogic::OnShowOptNty( WPARAM wParam, LPARAM lParam )
{
	EM_ShowStateRecord emShowState = (EM_ShowStateRecord)wParam;
	RefreshRecList();

	//CMsgHandle::SendMessage( WM_DEF_HIDE_LOSEFOCUSHIDER_SHOWOPT );

	return S_OK;
}

TUmcConfInfo* CVedioRecordLogic::FindConfInfoSel()
{
	if ( !( m_tUmcConfInfoSel.m_vecTRecInfo.size() > 0 ) )
	{
		return NULL;
	}
	
	vector<TUmcConfInfo>::iterator it = m_vecTUmcConfInfo.begin();
	for ( ; it != m_vecTUmcConfInfo.end(); it++ )
	{
		if ( m_tUmcConfInfoSel.m_wConfID == it->m_wConfID )
		{
			return it;
		}
	}

	return NULL;
}

LRESULT CVedioRecordLogic::OnNoSelResultNotify(WPARAM wParam, LPARAM lParam)
{
	HWND hWnd = (HWND)wParam;
	if ( hWnd == m_pListMeeting->GetSafeHwnd() )
	{
		ShowChildWnd(em_Wnd_Init);
		
		m_tUmcConfInfoSel.Clear();
	}
	if ( hWnd == m_pListVedioFile->GetSafeHwnd() )
	{
		m_tUmcConfInfoSel.m_tConfPlayStatus.m_tInfo.m_szFileName[0] = '\0';
	}
	
	return 0;
}

EmMeetState CVedioRecordLogic::SelItemState()
{
	if ( m_tUmcConfInfoSel.m_vecTRecInfo.size() == 0 )
	{
		return emMeetStateEnd;
	}

	BOOL bRecMt = FALSE;
	BOOL bRecConf = FALSE;

	vector<TUmcRecInfo>::iterator itRec = m_tUmcConfInfoSel.m_vecTRecInfo.begin();
	for ( ; itRec != m_tUmcConfInfoSel.m_vecTRecInfo.end(); itRec++ )
	{
		if ( itRec->m_tInfo.m_emType == em_rec_recorder_mt
			&& ( itRec->m_emState == em_rec_pause || itRec->m_emState == em_rec_working ) )
		{
			bRecMt = TRUE;
		}
		else if ( itRec->m_tInfo.m_emType == em_rec_recorder_conf
			&& ( itRec->m_emState == em_rec_pause || itRec->m_emState == em_rec_working ) )
		{
			bRecConf = TRUE;
		}
		
	}

	if ( bRecMt )
	{
		return emMeetStateRecMt;
	}

	if ( bRecConf )
	{
		return emMeetStateRec;
	}
	
	if ( m_tUmcConfInfoSel.m_tConfPlayStatus.m_emState == em_rec_pause 
		|| m_tUmcConfInfoSel.m_tConfPlayStatus.m_emState == em_rec_working )
	{
		return emMeetStatePlay;
	}

	return emMeetStateEnd;
}

LRESULT CVedioRecordLogic::OnVtrRegStateNty(WPARAM wParam, LPARAM lParam)
{
	if ( m_pVTRCtrlIF == NULL )
	{
		return 0;
	}

	BOOL32 bRegState;
	m_pVTRCtrlIF->GetVtrRegState( bRegState );
	if( bRegState == FALSE )
	{
		m_tUmcConfInfoSel.Clear();
		ShowChildWnd( em_Wnd_NoVtr );
	}

	return 0;
}

void CVedioRecordLogic::ShowSelItem()
{
	TConRecState* pTConRecState = GetRecConfInfoInVec();
	if ( pTConRecState == NULL )
	{
		return;
	}
	
	if ( pTConRecState->m_emState == em_rec_working || pTConRecState->m_emState == em_rec_pause
		|| pTConRecState->m_emState == em_rec_finish )
	{
		int nSec = 0;
		int nMin = 0;
		int nHour = 0;
		CUmcwebCommon::GetTime( pTConRecState->m_dwRecTime, nHour, nMin, nSec );
		
		CString strCaption;
		strCaption.Format( "%d:%d:%d",nHour, nMin, nSec );
		m_stcRecordTimeReal.SetWindowText(strCaption);

		strCaption = m_pVTRCtrlIF->GetNoSuffixString(pTConRecState->m_tInfo.m_achFileName);

		m_stcRecFileNameReal.SetWindowText(strCaption);
	}
	else
	{
		m_stcRecordTimeReal.SetWindowText("");
		m_stcRecFileNameReal.SetWindowText("");
	}


	TUmcConfInfo* pTUmcConfInfoSel = FindConfInfoSel();
	if ( pTUmcConfInfoSel == NULL )
	{
		return;
	}
	
	if ( pTUmcConfInfoSel->m_tConfPlayStatus.m_emState == em_rec_working || pTUmcConfInfoSel->m_tConfPlayStatus.m_emState == em_rec_pause )
	{
		int nCurSec = 0;
		int nCurMin = 0;
		int nCurHour = 0;
		int nTotalSec = 0;
		int nTotalMin = 0;
		int nTotalHour = 0;
		CUmcwebCommon::GetTime( pTUmcConfInfoSel->m_tConfPlayStatus.m_dwCurTime, nCurHour, nCurMin, nCurSec );
		CUmcwebCommon::GetTime( m_tUmcConfInfoSel.m_tConfPlayStatus.m_dwTotalTime, nTotalHour, nTotalMin, nTotalSec );
		
		
		
		CString strCaption;
		strCaption.Format( "%d:%d:%d / %d:%d:%d",nCurHour, nCurMin, nCurSec, nTotalHour, nTotalMin, nTotalSec );
		m_stcPlayProgress.SetWindowText(strCaption);
		
		int nProgress = (float)pTUmcConfInfoSel->m_tConfPlayStatus.m_dwCurTime/m_tUmcConfInfoSel.m_tConfPlayStatus.m_dwTotalTime*100;

		if ( nProgress >= 0 && nProgress <= 1 )
		{
			nProgress = 1;
		}
		else if ( nProgress > 1 && nProgress <= 2 )
		{
			nProgress = 2;
		}
		else if ( nProgress > 100 )
		{
			nProgress = 100;
		}
		if ( m_pProgressPlay )
		{
			m_pProgressPlay->SetPos( nProgress );
		}
	}
	else
	{
		m_stcPlayProgress.SetWindowText("");
		
		if ( m_pProgressPlay )
		{
			m_pProgressPlay->SetPos( 0 );
		}
	}
	
	if ( m_emCurrentWnd == emCurrentWndMain )
	{
		LoadScheme(emSchmeControlBtn);
		SetConfAndPlayInfo();
	}
	
	if ( this->IsWindowVisible() )
	{
		RedrawWindow();
	}
}

void CVedioRecordLogic::ShowOptEx()
{
	//3.从vecTUmcConfInfoNew中ShowOpt
	vector<TUmcConfInfo> vecTUmcConfInfoShowOpt;
	switch( CVideoRecordShowOpt::GetDlgPtr()->m_emShowState )
	{
	case emShowAllRecord:
		{
			vecTUmcConfInfoShowOpt = m_vecTUmcConfInfo;
			break;
		}
	case emShowRecord:
		{
			vector<TUmcConfInfo>::iterator itConfInfoNew = m_vecTUmcConfInfo.begin();
			for ( ; itConfInfoNew != m_vecTUmcConfInfo.end(); itConfInfoNew++ )
			{		
				vector<TUmcRecInfo>::iterator itRecState = itConfInfoNew->m_vecTRecInfo.begin();
				for ( ; itRecState != itConfInfoNew->m_vecTRecInfo.end(); itRecState++ )
				{
					if ( itRecState->m_tInfo.m_wConfID != 0 && itRecState->m_tInfo.m_emType == em_rec_recorder_conf
						&& ( itRecState->m_emState == em_rec_working || itRecState->m_emState == em_rec_pause ) )
					{
						vecTUmcConfInfoShowOpt.push_back( *itConfInfoNew );
					}
				}
			}
			break;
		}
	case emShowPlay:
		{
			vector<TUmcConfInfo>::iterator itConfInfoNew = m_vecTUmcConfInfo.begin();
			for ( ; itConfInfoNew != m_vecTUmcConfInfo.end(); itConfInfoNew++ )
			{
				if ( itConfInfoNew->m_tConfPlayStatus.m_emState == em_rec_working 
					|| itConfInfoNew->m_tConfPlayStatus.m_emState == em_rec_pause )
				{
					vecTUmcConfInfoShowOpt.push_back( *itConfInfoNew );
				}
			}
			break;
		}
	default:
		break;
	}
	
	//4.Search
	m_vecTUmcConfInfoSearch.clear();
	
	CString strSearch;
	m_sedtSearch.GetWindowText(strSearch);
	if ( strSearch != _T("") )
	{
		vector<TUmcConfInfo>::iterator it = vecTUmcConfInfoShowOpt.begin();
		for ( ; it != vecTUmcConfInfoShowOpt.end(); it++ )
		{
			BOOL bFind = FALSE;			
			bFind = CUmcwebCommon::HZPYMatchList( strSearch, it->m_achConfName );
			if ( bFind )
			{		
				m_vecTUmcConfInfoSearch.push_back(*it);
			}
		}
	}
	else
	{
		m_vecTUmcConfInfoSearch = vecTUmcConfInfoShowOpt;
	}

	Value_ListRecord val_curConfList( &m_vecTUmcConfInfoSearch, "CVedioRecordLogic::OnClickConfListItem" );
    if ( m_pListMeeting != NULL )
    {
        m_pListMeeting->SetData( val_curConfList );
	}

	vector<TUmcConfInfo>::iterator it = m_vecTUmcConfInfoSearch.begin();
	int nSelItem = -1;
	for ( ; it != m_vecTUmcConfInfoSearch.end(); it++ )
	{
		nSelItem++;
		if ( strcmp(m_tUmcConfInfoSel.m_achConfName, it->m_achConfName ) == 0 )
		{
			m_pListMeeting->SetSelItem(nSelItem);
			break;
		}
	}
}

BOOL CVedioRecordLogic::CheckPalyFormat( TUmsVidFormat tConfFormat, BOOL bDual, TUmsVidFormat tDualFormat )
{
	BOOL bConfFormat = FALSE;
	BOOL bDualFormat = FALSE;

	if ( m_tUmcConfInfoSel.m_vecTRecInfo.size() > 0 )
	{
		for ( int n = 0; n < m_tUmcConfInfoSel.m_wMainNum; n++ )
		{
			if ( CheckFormat( m_tUmcConfInfoSel.m_atTpMainVideoRes[n], tConfFormat ) )
			{
				bConfFormat = TRUE;
				break;
			}
		}

		if ( bDual )
		{
			for ( int n = 0; n < m_tUmcConfInfoSel.m_wMinorNum; n++ )
			{
				if ( CheckFormat( m_tUmcConfInfoSel.m_atTpMinorVideoRes[n], tDualFormat ) )
				{
					bDualFormat = TRUE;
					break;
				}
			}
		}
		else
		{
			bDualFormat = TRUE;
		}
		
	}


	return ( bConfFormat && bDualFormat );
}

BOOL CVedioRecordLogic::CheckFormat( TUmsVidFormat tUmsVidFormat, TUmsVidFormat tUmsVidFormatChecked )
{
	if ( tUmsVidFormat.m_wFrameRate < tUmsVidFormatChecked.m_wFrameRate )
	{
		//对于同格式同分辨率中60帧到50帧，30帧到25帧，允许放像
		if ( (tUmsVidFormatChecked.m_wFrameRate == 60 && tUmsVidFormat.m_wFrameRate == 50)
			|| (tUmsVidFormatChecked.m_wFrameRate == 30 && tUmsVidFormat.m_wFrameRate == 25) )
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	if ( tUmsVidFormat.m_emFormat != tUmsVidFormatChecked.m_emFormat ||
		tUmsVidFormat.m_emRes < tUmsVidFormatChecked.m_emRes ||
		tUmsVidFormat.m_emQualityLvl != tUmsVidFormatChecked.m_emQualityLvl )
	{
		return FALSE;
	}

	return TRUE;
}

LRESULT CVedioRecordLogic::OnRecMdyFileRsp(WPARAM wParam, LPARAM lParam)
{
	TRecFileInfo* pTRecFileInfo  = reinterpret_cast<TRecFileInfo*>(wParam);
	TRecFileInfo tRecFileInfoOld = *pTRecFileInfo;
	TRecFileInfo tRecFileInfoNew = *++pTRecFileInfo;
	
	BOOL bRet = static_cast<BOOL>(lParam);
	
	if ( bRet )
	{
		RefreshRecFileList();
	}

	return 0;
}

LRESULT CVedioRecordLogic::OnEditSetFocus( WPARAM wparam, LPARAM lparam )
{
	if ( wparam == (WPARAM)m_edtConfType.GetSafeHwnd())
	{
		OnButtonConfType();
	}
	else if ( wparam == (WPARAM)m_edtShowType.GetSafeHwnd() )
	{
		OnButtonShowType();
	}
	return 0;
}