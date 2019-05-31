// MeetingTemplate.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "meettemplateLogic.h"
#include "mainLogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern float CUR_SCREEN_WIDTH_PER;  //屏幕宽度比率
extern float CUR_SCREEN_HEIGHT_PER; //屏幕高度比率

extern CMainLogic* g_cmainWnd;
CRITICAL_SECTION g_csLock;

CMeetTemplateLogic::CMeetTemplateLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CMeetTemplateLogic::IDD, pParent)
	,m_tTmpConfigIF(NULL),
	m_pconfCtrlIF(NULL),
	m_pAddrBookIF(NULL),
	m_pUmsConfig(NULL)
{
	//{{AFX_DATA_INIT(CMeetTemplateLogic)
	//}}AFX_DATA_INIT

	m_bIsAllSel = FALSE;
	//m_bShowMosaicHoriImg = FALSE;
	m_nCurPollingListSortRow = 0;
	m_nTurnLeftListCount = 0;
	::InitializeCriticalSection(&g_csLock);

	m_plsMeetTmp = NULL;
	m_plsMeetEpRight = NULL;
	m_plsMeetPollingRight= NULL;
	m_plsLocalAddrbook = NULL;
	m_plsPollingLeft = NULL;
	m_plsDiscussLeft = NULL;

	m_pLetterTmp = NULL;
	m_pLetterAddrbook = NULL;
	m_pLetterPolling = NULL;
	m_pLetterDiscuss = NULL;

	m_bShowMosaicHoriImg = TRUE;
	m_bIsSegment = TRUE;
	m_nSegmentLen = 690*CUR_SCREEN_WIDTH_PER;
	m_wResUsedCount = 0;

	m_bSwitchPolling = TRUE;
	m_bSwitchDiscuss = FALSE;
}

void CMeetTemplateLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMeetTemplateLogic)
	DDX_Control(pDX, IDC_BTN_MEDIARETURN, m_btnReturn);
	DDX_Control(pDX, IDC_EDIT_HOUR_DOT, m_edtDotHour);
	DDX_Control(pDX, IDC_BUTTON_SETTOP, m_btnSetTop);
	DDX_Control(pDX, IDC_BUTTON_SETBOTTOM, m_btnSetBottom);
	DDX_Control(pDX, IDC_BUTTON_REMOVEALL, m_btnRemoveAll);
	DDX_Control(pDX, IDC_BUTTON_MOVEUP, m_btnMoveUp);
	DDX_Control(pDX, IDC_BUTTON_MOVEDOWN, m_btnMoveDown);
	DDX_Control(pDX, IDC_BTN_ALLADD, m_btnAllAdd);
	DDX_Control(pDX, IDC_BUTTON_CALLCONF, m_btnStartConf);
	DDX_Control(pDX, IDC_STATIC_CHILDFRMRIGHT, m_stChildBkRight);
	DDX_Control(pDX, IDC_STATIC_CHILDFRMLEFT, m_stChildBkLeft);
	DDX_Control(pDX, IDC_BUTTON_CHECKCURMEET, m_btnCheckCur);
	DDX_Control(pDX, IDC_BUTTON_CHECKORDERMEET, m_btnCheckOrder);
	DDX_Control(pDX, IDC_BtnSave, m_btnSave);
	DDX_Control(pDX, IDC_BtnCancel, m_btnCancel);
	DDX_Control(pDX, IDC_BtnEdit, m_btnEdit);
	DDX_Control(pDX, IDC_EDIT_Ex, m_etSearch);
	DDX_Control(pDX, IDC_Btn_NewTemplate, m_btnNewTmp);
	DDX_Control(pDX, IDC_BtnDelete, m_btnDelete);
	DDX_Control(pDX, IDC_BtnAllSelect, m_btnAllSel);
	DDX_Control(pDX, IDC_STATIC_LEFTTITLE, m_stTemplateLeftTitle);
	DDX_Control(pDX, IDC_STATIC_RIGHT, m_stTemplateRightTitle);
	DDX_Control(pDX, IDC_Btn_MeetingInfo, m_btnMeetingInfo);
	DDX_Control(pDX, IDC_Btn_GroupInfo, m_btnGroupInfo);
	DDX_Control(pDX, IDC_Btn_PollingInfo, m_btnPollingInfo);
	DDX_Control(pDX, IDC_Btn_DiscussInfo, m_btnDiscussInfo);
	DDX_Control(pDX, IDC_STATIC_Name, m_stName);
	DDX_Control(pDX, IDC_STATIC_Number, m_stNumber);
	DDX_Control(pDX, IDC_STATIC_Type, m_stTmpType);
	DDX_Control(pDX, IDC_STATIC_Date, m_stDate);
	DDX_Control(pDX, IDC_STATIC_StartTime, m_stStartTime);
	DDX_Control(pDX, IDC_STATIC_TName, m_stNameShow);
	DDX_Control(pDX, IDC_STATIC_TNumber, m_stNumberShow);
	DDX_Control(pDX, IDC_STATIC_TType, m_stTmpTypeShow);
	DDX_Control(pDX, IDC_STATIC_TDate, m_stDateShow);
	DDX_Control(pDX, IDC_STATIC_TStartTime, m_stStartTimeShow);
	DDX_Control(pDX, IDC_EditName, m_etName);
	DDX_Control(pDX, IDC_EditNumber, m_etNumber);
	DDX_Control(pDX, IDC_EditHour, m_etSetHour);
	DDX_Control(pDX, IDC_EditMinute, m_etSetMin);
	DDX_Control(pDX, IDC_BUTTON_CALENDAR, m_btnCalendar);
	DDX_Control(pDX, IDC_BtnPlusHour, m_btnPlusTime);
	DDX_Control(pDX, IDC_BtnSubHour, m_btnSubTime);
	DDX_Control(pDX, IDC_EDIT_DATE, m_etDateSet);
	DDX_Control(pDX, IDC_STATIC_INTERVEL, m_stIntervel);
	DDX_Control(pDX, IDC_STATIC_POLLINGSECOND, m_stPollingSecond);
	DDX_Control(pDX, IDC_PollingEditName, m_etPollingTime);
	DDX_Control(pDX, IDC_BtnSubPollingTime, m_btnSubPollingTime);
	DDX_Control(pDX, IDC_BtnPlusPollingTime, m_btnPlusPollingTime);
	DDX_Control(pDX, IDC_STATIC_HOMEMEETING, m_stHomeMeeting);
	DDX_Control(pDX, IDC_GroupEditName, m_etHomeMeeting);
	DDX_Control(pDX, IDC_STATIC_MEDIAINFO, m_stMediaInfo);
	DDX_Control(pDX, IDC_EditAdaptRes, m_etAdaptRes);
	DDX_Control(pDX, IDC_BUTTON_MEDIAINFO, m_btnMediaInfo);
	DDX_Control(pDX, IDC_STATIC_CONFRATE, m_stConfRate);
	DDX_Control(pDX, IDC_STATIC_TConfRate, m_stConfRateShow);
	DDX_Control(pDX, IDC_STATIC_TConfRateUnit, m_stConfRateUnit);
	DDX_Control(pDX, IDC_EditConfRate, m_etConfRate);
	DDX_Control(pDX, IDC_STATIC_SHOWRATE, m_stShowRate);
	DDX_Control(pDX, IDC_STATIC_TShowRate, m_stShowRateShow);
	DDX_Control(pDX, IDC_STATIC_TShowRateUnit, m_stShowRateUnit);
	DDX_Control(pDX, IDC_EditShowRate, m_etShowRate);
	DDX_Control(pDX, IDC_BtnSubConfRate, m_btnSubConfRate);
	DDX_Control(pDX, IDC_BtnPlusConfRate, m_btnPlusConfRate);
	DDX_Control(pDX, IDC_BtnSubShowRate, m_btnSubShowRate);
	DDX_Control(pDX, IDC_BtnPlusShowRate, m_btnPlusShowRate);
	DDX_Control(pDX, IDC_BtnSwitchPolling, m_btnSwitchPolling);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMeetTemplateLogic, CDlgChild)
	//{{AFX_MSG_MAP(CMeetTemplateLogic)
	ON_BN_CLICKED(IDC_BTN_MEDIARETURN, OnBtnReturn)
	ON_BN_CLICKED(IDC_Btn_NewTemplate, OnBtnNew)
	ON_BN_CLICKED(IDC_BtnDelete, OnBtnDelete)
	ON_BN_CLICKED(IDC_BTN_EDIT, OnBtnEdit)
	ON_BN_CLICKED(IDC_BtnSave, OnBtnSave)
	ON_BN_CLICKED(IDC_BtnCancel, OnBtnCancel)
	ON_BN_CLICKED(IDC_BtnAllSelect, OnBtnAllSelect)
	ON_BN_CLICKED(IDC_Btn_MeetingInfo, OnBtnMeetingInfo)
	ON_BN_CLICKED(IDC_Btn_GroupInfo, OnBtnEpInfo)
	ON_BN_CLICKED(IDC_Btn_PollingInfo, OnBtnPollingInfo)
	ON_BN_CLICKED(IDC_Btn_DiscussInfo, OnBtnDiscussInfo)
	ON_BN_CLICKED(IDC_BtnPlusHour, OnBtnPlusTime)
	ON_BN_CLICKED(IDC_BtnSubHour, OnBtnSubTime)
 	ON_MESSAGE( UI_UMS_OPERATE_CONFTEMP_RET,  OnTmpListOperateResult )
	ON_MESSAGE(WM_DEF_UPDATEGROUPLISTCONTROL, UpdateGroupEpList)
	ON_MESSAGE(WM_DEF_UPDATEPOLLINGLISTCONTROL, UpdatePollingList)
	ON_MESSAGE(UI_CNS_ADDRBOOK_CHANGED,OnRefreshAddrListListNotify)  //地址簿初始化
	ON_MESSAGE( UI_UMS_REFRESH_CONFTEMPLATE_LIST,  OnRefreshTmpListNotify )
	ON_MESSAGE( UI_UMS_START_CONFTEMPLATE_RSP, OnStartConfResult )
	ON_MESSAGE( UI_UMS_CONFTMPRESUSEDCOUNT_NOTIFY, OnConfTmpResUsedCountNotify )
	ON_MESSAGE( UI_UMS_DEL_ALL_CONFTEMP_RET, OnDelAllConftempRet )
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CALENDAR, OnBtnCalendar)
	ON_BN_CLICKED(IDC_BUTTON_CHECKCURMEET, OnBtnCheckOrderConf)
	ON_BN_CLICKED(IDC_BUTTON_CHECKORDERMEET, OnBtnCheckCurConf)
	ON_BN_CLICKED(IDC_BUTTON_CALLCONF, OnBtnStartConf)
	ON_WM_SHOWWINDOW()
	ON_MESSAGE( WM_LST_UN_SELECT_ITEM,  OnNoSelResultNotify )
	ON_MESSAGE( UI_CALENDAR_SELECT_DATE,  OnUpdateCalendarSelDate )
	ON_BN_CLICKED(IDC_BTN_ALLADD, OnBtnAllAdd)
	ON_BN_CLICKED(IDC_BUTTON_SETTOP, OnBtnSetTop)
	ON_BN_CLICKED(IDC_BUTTON_SETBOTTOM, OnBtnSetBottom)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEALL, OnBtnRemoveAll)
	ON_BN_CLICKED(IDC_BUTTON_MOVEUP, OnBtnMoveUp)
	ON_BN_CLICKED(IDC_BUTTON_MOVEDOWN, OnBtnMoveDown)
	ON_MESSAGE( WM_DEF_HIDE_LOSEFOCUSHIDER, OnHideWndNotify ) 
    ON_MESSAGE( WM_BTN_HOLD, OnBtnHold ) 
    ON_MESSAGE( WM_BTN_HOLD_END, OnBtnHoldEnd ) 
	ON_EN_SETFOCUS(IDC_EditHour, OnSetfocusEditHour)
	ON_BN_CLICKED(IDC_BtnEdit, OnBtnEdit)
	ON_EN_SETFOCUS(IDC_EditMinute, OnSetfocusEditMinute)
	ON_BN_CLICKED(IDC_BUTTON_MEDIAINFO, OnBtnMediaInfo)
	ON_BN_CLICKED(IDC_BtnSubConfRate, OnBtnSubConfRate)
	ON_BN_CLICKED(IDC_BtnPlusConfRate, OnBtnPlusConfRate)
	ON_BN_CLICKED(IDC_BtnSubShowRate, OnBtnSubShowRate)
	ON_BN_CLICKED(IDC_BtnPlusShowRate, OnBtnPlusShowRate)
	ON_BN_CLICKED(IDC_BtnSubPollingTime, OnBtnSubPollingTime)
	ON_BN_CLICKED(IDC_BtnPlusPollingTime, OnBtnPlusPollingTime)
	ON_MESSAGE( WM_BUTTON_CLICK, OnClickSwitchBtn )
	ON_MESSAGE( WM_DEF_CHANGE_DISCUSSEP, OnDiscussEpChange )
	ON_MESSAGE( WM_DEF_SWITCH_DISCUSS, OnSwitchDiscuss )
    ON_MESSAGE( UI_DRAG_END, OnDragEnd )
	ON_MESSAGE( WM_EDIT_SETFOCUS, OnEditSetFocus )
	ON_MESSAGE( WM_KILL_FOCUS, OnKillFoucs )
	ON_MESSAGE( UI_UMS_UMSREASON_IND, OnUmsReasonInd )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMeetTemplateLogic message handlers
void CMeetTemplateLogic::RegisterFun()
{
	REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickTmpLstItem", CMeetTemplateLogic::OnClickTmpLstItem, this,CMeetTemplateLogic );	
	REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickTmpLstItemIcon", CMeetTemplateLogic::OnClickTmpLstItemIcon, this,CMeetTemplateLogic );
	REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickAddrbookLstItem", CMeetTemplateLogic::OnClickAddrbookLstItem, this,CMeetTemplateLogic );
	REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickAddrbookLstItemIcon", CMeetTemplateLogic::OnClickAddrbookLstItemIcon, this,CMeetTemplateLogic );
	REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickPollingPageLeftLstItem", CMeetTemplateLogic::OnClickPollingPageLeftLstItem, this,CMeetTemplateLogic );
	REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickPollingPageLeftLstItemIcon", CMeetTemplateLogic::OnClickPollingPageLeftLstItemIcon, this,CMeetTemplateLogic );
	REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickGroupPageDelItemIcon", CMeetTemplateLogic::OnClickGroupPageDelItemIcon, this,CMeetTemplateLogic );
	REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickPollingPageDelItemIcon", CMeetTemplateLogic::OnClickPollingPageDelItemIcon, this,CMeetTemplateLogic );
	REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickPollingPageDelItem", CMeetTemplateLogic::OnClickPollingPageDelItem, this,CMeetTemplateLogic );
	REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickDiscussPageLeftLstItem", CMeetTemplateLogic::OnClickDiscussPageLeftLstItem, this,CMeetTemplateLogic );
	REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickDiscussPageLeftLstItemIcon", CMeetTemplateLogic::OnClickDiscussPageLeftLstItemIcon, this,CMeetTemplateLogic );
	REG_MSG( UI_CNS_ADDRBOOK_CHANGED, GetSafeHwnd() );
	REG_MSG( UI_UMS_START_CONFTEMPLATE_RSP, GetSafeHwnd() );
	REG_MSG( WM_DEF_HIDE_LOSEFOCUSHIDER, GetSafeHwnd() );
}

BOOL CMeetTemplateLogic::InitControlPane()
{
	m_btnSave.SetImage( IDR_PNG_BTN_SAVE, IDR_PNG_BTN_SAVEDOWN, IDR_PNG_BTN_SAVE );
	m_btnCancel.SetImage( IDR_PNG_BTN_CANCEL, IDR_PNG_BTN_CANCELDOWN, IDR_PNG_BTN_CANCEL );
	m_btnEdit.SetImage( IDR_PNG_BTN_EDIT, IDR_PNG_BTN_EDITDOWN, IDR_PNG_BTN_EDIT );

	m_btnNewTmp.SetImage( IDR_PNG_BTN_NEWTMP, IDR_PNG_BTN_NEWTMPDOWN, IDR_PNG_BTN_NEWTMPDIS );
	m_btnAllSel.SetImage( IDR_PNG_BTN_ALLSEL, IDR_PNG_BTN_ALLSELDOWN, IDR_PNG_BTN_ALLSELDIS );
 	m_btnDelete.SetImage( IDR_PNG_BTN_DELETE, IDR_PNG_BTN_DELETEDOWN, IDR_PNG_BTN_DELETEDIS );
	m_btnAllAdd.SetImage( IDR_PNG_MEETTMPWND_BTN_ALLADD, IDR_PNG_MEETTMPWND_BTN_ALLADDDOWN, IDR_PNG_MEETTMPWND_BTN_ALLADDDIS );
	m_btnSetTop.SetImage( IDR_PNG_MEETTMPWND_BTN_SETTOP, IDR_PNG_MEETTMPWND_BTN_SETTOPDOWN, IDR_PNG_MEETTMPWND_BTN_SETTOPDIS );
	m_btnSetBottom.SetImage( IDR_PNG_MEETTMPWND_BTN_SETBOTTOM, IDR_PNG_MEETTMPWND_BTN_SETBOTTOMDOWN, IDR_PNG_MEETTMPWND_BTN_SETBOTTOMDIS );
	m_btnMoveUp.SetImage( IDR_PNG_MEETTMPWND_BTN_UP, IDR_PNG_MEETTMPWND_BTN_UPDOWN, IDR_PNG_MEETTMPWND_BTN_UPDIS );
	m_btnMoveDown.SetImage( IDR_PNG_MEETTMPWND_BTN_DOWN, IDR_PNG_MEETTMPWND_BTN_DOWNDOWN, IDR_PNG_MEETTMPWND_BTN_UPDOWNDIS );
	m_btnRemoveAll.SetImage( IDR_PNG_MEETTMPWND_BTN_ALLREMOVE, IDR_PNG_MEETTMPWND_BTN_ALLREMOVEDOWN, IDR_PNG_MEETTMPWND_BTN_ALLREMOVEDIS );

	m_btnMeetingInfo.SetImage( IDR_PNG_MEETTMPWND_BTN_MEETINFO, IDR_PNG_MEETTMPWND_BTN_MEETINFODOWN, IDR_PNG_MEETTMPWND_BTN_MEETINFOSEL );
	m_btnGroupInfo.SetImage( IDR_PNG_MEETTMPWND_BTN_MEETGROUP, IDR_PNG_MEETTMPWND_BTN_MEETGROUPDOWN, IDR_PNG_MEETTMPWND_BTN_MEETGROUPSEL );
 	m_btnPollingInfo.SetImage( IDR_PNG_MEETTMPWND_BTN_MEETPOLLING, IDR_PNG_MEETTMPWND_BTN_MEETPOLLINGDOWN, IDR_PNG_MEETTMPWND_BTN_MEETPOLLINGSEL );
	m_btnDiscussInfo.SetImage( IDR_PNG_MEETTMPWND_BTN_MEETDISCUSS, IDR_PNG_MEETTMPWND_BTN_MEETDISCUSSDOWN, IDR_PNG_MEETTMPWND_BTN_MEETDISCUSSSEL );
	
	m_btnCheckCur.SetImage( IDR_PNG_RADIO_SEL, IDR_PNG_RADIO_SEL, IDR_PNG_RADIO_SELDIS,IDR_PNG_RADIO_UNSEL, IDR_PNG_RADIO_UNSEL, IDR_PNG_RADIO_UNSELDIS );
	m_btnCheckOrder.SetImage( IDR_PNG_RADIO_SEL, IDR_PNG_RADIO_SEL, IDR_PNG_RADIO_SELDIS, IDR_PNG_RADIO_UNSEL, IDR_PNG_RADIO_UNSEL, IDR_PNG_RADIO_UNSELDIS );

	CUmcwebCommon::SetTextTransStatic( &m_stTemplateLeftTitle, "会议模板" , 14, Color( 24, 25, 27 ) );
	CUmcwebCommon::SetTextTransStatic( &m_stTemplateRightTitle, "会议模板信息" , 14, Color( 24, 25, 27 ) );
	m_btnMediaInfo.SetImage( IDR_PNG_BTN_EDITMEDIARIGHT, IDR_PNG_BTN_EDITMEDIARIGHT_DOWN, IDR_PNG_BTN_EDITMEDIARIGHT );

	CUmcwebCommon::SetImgForTransSearchEdit(&m_etSearch);

	return TRUE;
}

BOOL CMeetTemplateLogic::InitMeetInfoPageControl()
{
	m_btnReturn.SetImage( IDR_PNG_BTN_RETURN, IDR_PNG_BTN_RETURNDOWN, IDR_PNG_BTN_RETURN );
	m_btnReturn.SetWindowPos( NULL, 702, 4, m_btnReturn.GetImageSize().cx, m_btnReturn.GetImageSize().cy, SWP_HIDEWINDOW );

	//浏览控件
	CRect rectClient;
	this->GetClientRect(&rectClient);

	m_stName.SetWindowPos( NULL, (700 + 18 - 12)*CUR_SCREEN_WIDTH_PER,  112*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_stNumber.SetWindowPos( NULL, (700 + 18 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 18 + 27)*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );	
	m_stTmpType.SetWindowPos( NULL, (700 + 18 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 2*(18 + 27))*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_stDate.SetWindowPos( NULL, (700 + 18 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 3*(18 + 27))*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_stStartTime.SetWindowPos( NULL, (700 + 18 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 4*(18 + 27))*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_stNameShow.SetWindowPos( NULL, (700 + 134 - 12)*CUR_SCREEN_WIDTH_PER ,  112*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_stNumberShow.SetWindowPos( NULL, (700 + 134 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 18 + 27)*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_stTmpTypeShow.SetWindowPos( NULL, (700 + 134 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 2*(18 + 27))*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnCheckCur.SetWindowPos( NULL,  (700 + 134 - 12 + 5)*CUR_SCREEN_WIDTH_PER,  (112 + 2*(18 + 27))*CUR_SCREEN_HEIGHT_PER, m_btnCheckOrder.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnCheckOrder.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER ,SWP_HIDEWINDOW );
	m_btnCheckOrder.SetWindowPos( NULL,  (700 + 134 - 12 + 166)*CUR_SCREEN_WIDTH_PER,  (112 + 2*(18 + 27))*CUR_SCREEN_HEIGHT_PER, m_btnCheckOrder.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnCheckOrder.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER ,SWP_HIDEWINDOW );
	m_stDateShow.SetWindowPos( NULL, (700 + 134 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 3*(18 + 27))*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_stStartTimeShow.SetWindowPos( NULL, (700 + 134 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 4*(18 + 27))*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransStatic( &m_stName, "名称" );
	CUmcwebCommon::SetTextTransStatic( &m_stNumber, "号码" );
	CUmcwebCommon::SetTextTransStatic( &m_stTmpType, "类型" );
	CUmcwebCommon::SetTextTransStatic( &m_stDate, "日期" );
	CUmcwebCommon::SetTextTransStatic( &m_stStartTime, "开始时间" );
	CUmcwebCommon::SetTextTransStatic( &m_stMediaInfo, "媒体信息" );
	CUmcwebCommon::SetTextTransStatic( &m_stConfRate, "单屏码率" );
	CUmcwebCommon::SetTextTransStatic( &m_stShowRate, "演示码率" );
	CUmcwebCommon::SetTextTransStatic( &m_stNameShow, "" );
	CUmcwebCommon::SetTextTransStatic( &m_stNumberShow, "" );
	CUmcwebCommon::SetTextTransStatic( &m_stTmpTypeShow, "" );
	CUmcwebCommon::SetTextTransStatic( &m_stDateShow, "" );
	CUmcwebCommon::SetTextTransStatic( &m_stStartTimeShow, "" );
	CUmcwebCommon::SetTextTransStatic( &m_stConfRateShow, "" );
	CUmcwebCommon::SetTextTransStatic( &m_stShowRateShow, "" );
	CUmcwebCommon::SetTextTransStatic( &m_stConfRateUnit, "Kbps" );
	CUmcwebCommon::SetTextTransStatic( &m_stShowRateUnit, "Kbps" );

	m_btnCheckCur.SetWindowText("预约会议");
	m_btnCheckCur.SetShowText(TRUE);
	m_btnCheckCur.SetTextColor( Color(46, 55, 76) );
	m_btnCheckCur.SetButtonStyle( WS_CHILD|WS_CLIPSIBLINGS|BS_AUTORADIOBUTTON  );

	m_btnCheckOrder.SetWindowText("即时会议");
	m_btnCheckOrder.SetShowText(TRUE);
	m_btnCheckOrder.SetTextColor( Color(46, 55, 76) );
	m_btnCheckOrder.SetButtonStyle( WS_CHILD|WS_CLIPSIBLINGS|BS_AUTORADIOBUTTON  );

	//会议模板列表加入
	m_plsMeetTmp = new CListChild( "", CRect(12, 100, 690 - 60+12, 488+100), this, "", 0, WS_CHILD );
	if ( NULL != m_plsMeetTmp )
	{
		m_plsMeetTmp->SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 100*CUR_SCREEN_HEIGHT_PER, (690 - 60)*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
		m_plsMeetTmp->SetImage( IDR_PNG_LIST_TOPLEFT, IDR_PNG_LIST_TOPCEN, IDR_PNG_LIST_TOPRIGHT, IDR_PNG_LIST_CENLEFT, IDR_PNG_LIST_CENRIGHT,
			IDR_PNG_LIST_BTLEFT, IDR_PNG_LIST_BTCEN, IDR_PNG_LIST_BTRIGHT, IDR_PNG_LIST_TOPCEN, "PNG" );
		m_plsMeetTmp->SetSliderImage( IDR_PNG_LISTSLIDER_NORMALTOP, IDR_PNG_LISTSLIDER_NORMALMIDDLE, IDR_PNG_LISTSLIDER_NORMALBOTTOM, IDR_PNG_LISTSLIDER_DOWNTOP, 
            IDR_PNG_LISTSLIDER_DOWNMIDDLE, IDR_PNG_LISTSLIDER_DOWNBOTTOM, IDR_PNG_LISTSLIDER_BKGTOP, IDR_PNG_LISTSLIDER_BKGMIDDLE, IDR_PNG_LISTSLIDER_BKGBOTTOM, "PNG" );
        m_plsMeetTmp->SetSliderAlwaysShow( TRUE );
	}

	m_pLetterTmp = new CLetterIndex( "Letter", "Letter", CRect(0,0,39,486), this, GETUNIQID, WS_CHILD );
	CUmcwebCommon::SetImgForLetter(m_pLetterTmp);
	if ( NULL != m_pLetterTmp )
	{
		m_pLetterTmp->SetLetterHeight(18*CUR_SCREEN_HEIGHT_PER);
		m_pLetterTmp->SetBindList( m_plsMeetTmp );
		m_plsMeetTmp->GetWindowRect(&rectClient);
		ScreenToClient( &rectClient );

		rectClient.left = rectClient.right - 3;
		rectClient.right = rectClient.left + 7;
		m_plsMeetTmp->SetSliderRect( rectClient );

		m_pLetterTmp->SetWindowPos( NULL, rectClient.right + 2*CUR_SCREEN_WIDTH_PER, 100*CUR_SCREEN_HEIGHT_PER, 39*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER,SWP_HIDEWINDOW );
	}
	
	CUmcwebCommon::SetImgForTransEdit(&m_etName, FALSE);
	CUmcwebCommon::SetImgForTransEdit(&m_etNumber, FALSE);

	CUmcwebCommon::SetImgForTransEdit(&m_etConfRate, FALSE);
	m_etConfRate.SetWindowPos( NULL, (700 + 164 + 15)*CUR_SCREEN_WIDTH_PER,  (112 + 6*(18 + 27))*CUR_SCREEN_HEIGHT_PER + 7 - 2, 80*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_etConfRate.SetShowIcon(FALSE);
	m_etConfRate.SetLimitLength(4);
	m_etConfRate.SetTextAlign(StringAlignmentCenter);
	
	CUmcwebCommon::SetImgForTransEdit(&m_etShowRate, FALSE);
	m_etShowRate.SetWindowPos( NULL, (700 + 164 + 15)*CUR_SCREEN_WIDTH_PER,  (112 + 7*(18 + 27))*CUR_SCREEN_HEIGHT_PER + 7 - 2, 80*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_etShowRate.SetShowIcon(FALSE);
	m_etShowRate.SetLimitLength(4);
	m_etShowRate.SetTextAlign(StringAlignmentCenter);

	m_btnPlusConfRate.SetImage( IDR_PNG_BTN_PLUS, IDR_PNG_BTN_PLUSDOWN, IDR_PNG_BTN_PLUSDIS );
	m_btnPlusShowRate.SetImage( IDR_PNG_BTN_PLUS, IDR_PNG_BTN_PLUSDOWN, IDR_PNG_BTN_PLUSDIS );
	m_btnSubConfRate.SetImage( IDR_PNG_BTN_SUB, IDR_PNG_BTN_SUBDOWN, IDR_PNG_BTN_SUBDIS );
	m_btnSubShowRate.SetImage( IDR_PNG_BTN_SUB, IDR_PNG_BTN_SUBDOWN, IDR_PNG_BTN_SUBDIS );

	m_btnPlusConfRate.SetWindowPos( NULL, (700 + 274 - 10)*CUR_SCREEN_WIDTH_PER, (112 + 6*(18 + 27))*CUR_SCREEN_HEIGHT_PER + 7, m_btnPlusConfRate.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnPlusConfRate.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
    m_btnPlusShowRate.SetWindowPos( NULL, (700 + 274 - 10)*CUR_SCREEN_WIDTH_PER, (112 + 7*(18 + 27))*CUR_SCREEN_HEIGHT_PER + 7, m_btnPlusShowRate.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnPlusShowRate.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnSubConfRate.SetWindowPos( NULL, (700 + 134 - 10)*CUR_SCREEN_WIDTH_PER, (112 + 6*(18 + 27))*CUR_SCREEN_HEIGHT_PER + 7, m_btnSubConfRate.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnSubConfRate.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
    m_btnSubShowRate.SetWindowPos( NULL, (700 + 134 - 10)*CUR_SCREEN_WIDTH_PER, (112 + 7*(18 + 27))*CUR_SCREEN_HEIGHT_PER + 7, m_btnSubShowRate.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnSubShowRate.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	//设置媒体占用资源编辑框控件
	m_etAdaptRes.SetImage( IDR_PNG_BTN_EDITMEDIALEFT, IDR_PNG_BTN_EDITMEDIAMID, IDR_PNG_BTN_EDITMEDIAMID,
		IDR_PNG_BTN_EDITMEDIALEFT, IDR_PNG_BTN_EDITMEDIAMID, IDR_PNG_BTN_EDITMEDIAMID,
		IDR_PNG_BTN_EDITMEDIALEFT, IDR_PNG_BTN_EDITMEDIAMID, IDR_PNG_BTN_EDITMEDIAMID,
			0, 0 , 0);
	m_etAdaptRes.SetWindowText("");//会议所需适配资源5/8
//	m_etAdaptRes.EnableWindow(FALSE);
	m_etAdaptRes.SetDisableColor( Color(46, 55, 76) );
	m_etAdaptRes.SetVerCenter(TRUE);
	m_etAdaptRes.SetEditFrontLen(7);

	CUmcwebCommon::SetImgForTransEditTimeLft( &m_etSetHour, FALSE ); 
	m_etSetHour.SetShowIcon(FALSE);
    m_etSetHour.SetTextAlign(StringAlignmentCenter);
	m_etSetHour.EnableWindow(FALSE);
    m_etSetHour.SetWindowText("0");
	m_etSetHour.SetLimitLength(2);
	
	
	CUmcwebCommon::SetImgForTransEditTimeMdl( &m_edtDotHour, FALSE );
	m_edtDotHour.SetShowIcon(FALSE);
	m_edtDotHour.EnableWindow(FALSE);
    m_edtDotHour.SetWindowText(":");
    m_edtDotHour.SetTextAlign(StringAlignmentCenter);
    m_edtDotHour.SetTextColor(Color( 46, 55, 76 ),Color( 46, 55, 76 ) );
	m_edtDotHour.SetFont( 14, "微软雅黑" );
	
    CUmcwebCommon::SetImgForTransEditTimeRgt(&m_etSetMin, FALSE);
	m_etSetMin.SetShowIcon(FALSE);
	m_etSetMin.SetTextAlign(StringAlignmentCenter);
	m_etSetMin.EnableWindow(FALSE);
    m_etSetMin.SetWindowText("0");
    m_etSetMin.SetLimitLength(2);

	//编辑控件	
	this->GetClientRect(&rectClient);

	m_etNumber.SetWindowPos( NULL, (700 + 134 - 12)*CUR_SCREEN_WIDTH_PER, (112 + 45 - 9)*CUR_SCREEN_HEIGHT_PER, (391 - 10)*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_etName.SetWindowPos( NULL, (700 + 134 - 12)*CUR_SCREEN_WIDTH_PER, (112 - 9)*CUR_SCREEN_HEIGHT_PER, (391 - 10)*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_etName.SetLimitLength(31);
	m_etNumber.SetLimitLength(13);

	CRect rectEdit;
	m_etName.GetWindowRect(&rectEdit);
	ScreenToClient( &rectEdit );
	s32 nEditRight = rectEdit.right;
	
	m_btnCalendar.SetImage( IDR_PNG_CALENDAR_SEL, IDR_PNG_CALENDAR_DOWN, IDR_PNG_CALENDAR_SEL, 
		IDR_PNG_CALENDAR,IDR_PNG_CALENDAR_DOWN,IDR_PNG_CALENDAR);
    m_btnCalendar.SetButtonStyle( BS_AUTOCHECKBOX );

	m_btnCalendar.SetWindowPos( NULL, rectEdit.right - (m_btnCalendar.GetImageSize().cx + 1)*CUR_SCREEN_WIDTH_PER, (112 + 3*(18 + 27) - 6)*CUR_SCREEN_HEIGHT_PER, m_btnCalendar.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnCalendar.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	CUmcwebCommon::SetImgForTransEdit(&m_etDateSet, FALSE);
	s32 nEditLeft = rectEdit.left;

	m_btnCalendar.GetWindowRect(&rectEdit);
	ScreenToClient( &rectEdit );
	m_etDateSet.SetWindowPos( NULL, nEditLeft, (112 + 3*(18 + 27) - 8)*CUR_SCREEN_HEIGHT_PER, nEditRight - nEditLeft - m_btnCalendar.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	
	m_btnPlusTime.SetImage( IDR_PNG_BTN_PLUS, IDR_PNG_BTN_PLUSDOWN, IDR_PNG_BTN_PLUSDIS );
	
	m_stStartTime.GetWindowRect(&rectClient);
	ScreenToClient(&rectClient);

	m_dlgCalendar.Create(IDD_DIALOG_CALENDAR,this);
	m_etSetHour.SetWindowPos( NULL, nEditLeft, rectClient.top - 7*CUR_SCREEN_HEIGHT_PER, 64*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	
	m_etSetHour.GetWindowRect(&rectEdit);
	ScreenToClient( &rectEdit );
	nEditRight = rectEdit.right;
	m_edtDotHour.SetWindowPos( NULL, nEditRight, rectClient.top - 7*CUR_SCREEN_HEIGHT_PER, 14*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );


	m_btnSubTime.SetImage( IDR_PNG_BTN_SUB, IDR_PNG_BTN_SUBDOWN, IDR_PNG_BTN_SUBDIS );

	CRect rectDot;
	m_btnSubTime.GetWindowRect(&rectDot);
	ScreenToClient( &rectDot );

	m_etDateSet.SetShowIcon(FALSE);
	m_etDateSet.EnableWindow(FALSE);

	s32 nSetHourYPos = rectClient.top - 7*CUR_SCREEN_HEIGHT_PER;
	m_etSetHour.GetWindowRect(&rectClient);
	ScreenToClient(&rectClient);

	m_edtDotHour.GetWindowRect(&rectEdit);
	ScreenToClient( &rectEdit );
	nEditRight = rectEdit.right;
	m_etSetMin.SetWindowPos( NULL, nEditRight, nSetHourYPos, 64*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	m_etSetMin.GetWindowRect(&rectEdit);
	ScreenToClient( &rectEdit );
	nEditRight = rectEdit.right;

    m_btnPlusTime.SetWindowPos( NULL, nEditRight, nSetHourYPos, 51*CUR_SCREEN_WIDTH_PER, 22*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
    m_btnSubTime.SetWindowPos( NULL, nEditRight, nSetHourYPos + 22*CUR_SCREEN_HEIGHT_PER, 51*CUR_SCREEN_WIDTH_PER, 22*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	m_etSetHour.SetTextAlign(StringAlignmentCenter);
	m_etSetMin.SetTextAlign(StringAlignmentCenter);
	m_etSetHour.SetLimitLength(2);
	m_etSetMin.SetLimitLength(2);

	CRect rectBKRight;
	m_stChildBkRight.GetClientRect(&rectBKRight);
	ScreenToClient(&rectBKRight);
	m_btnStartConf.SetImage( IDR_PNG_MEETTMPWND_BTN_CALLCONF, IDR_PNG_MEETTMPWND_BTN_CALLCONFDOWN, IDR_PNG_MEETTMPWND_BTN_CALLCONFDOWN );

	return TRUE;
}

BOOL CMeetTemplateLogic::InitMeetEpPageControl()
{
	//会场列表加入
	m_plsMeetEpRight = new CListChild( "", CRect(700 , (651 - 14 - 391 - 51), 508+700, 390+(651 - 14 - 391 - 51)), this, "", 0, WS_CHILD );
	if ( NULL != m_plsMeetEpRight )
	{
		m_plsMeetEpRight->SetWindowPos( NULL, 700*CUR_SCREEN_WIDTH_PER , (651 - 14 - 391 - 51)*CUR_SCREEN_HEIGHT_PER, 508*CUR_SCREEN_WIDTH_PER, 390*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
		m_plsMeetEpRight->SetImage( IDR_PNG_LIST_TOPLEFT, IDR_PNG_LIST_TOPCEN, IDR_PNG_LIST_TOPRIGHT, IDR_PNG_LIST_CENLEFT, IDR_PNG_LIST_CENRIGHT,
			IDR_PNG_LIST_BTLEFT, IDR_PNG_LIST_BTCEN, IDR_PNG_LIST_BTRIGHT, IDR_PNG_LIST_TOPCEN, "PNG" );
	}

	//地址簿列表加入
	m_plsLocalAddrbook = new CListChild( "", CRect(12, 100, 630+12, 488+100), this, "", 0, WS_CHILD ); 

	if ( NULL != m_plsLocalAddrbook )
	{
		m_plsLocalAddrbook->SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 100*CUR_SCREEN_HEIGHT_PER, 630*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
		m_plsLocalAddrbook->SetImage( IDR_PNG_LIST_TOPLEFT, IDR_PNG_LIST_TOPCEN, IDR_PNG_LIST_TOPRIGHT, IDR_PNG_LIST_CENLEFT, IDR_PNG_LIST_CENRIGHT,
			IDR_PNG_LIST_BTLEFT, IDR_PNG_LIST_BTCEN, IDR_PNG_LIST_BTRIGHT, IDR_PNG_LIST_TOPCEN, "PNG" );
		m_plsLocalAddrbook->SetSliderImage( IDR_PNG_LISTSLIDER_NORMALTOP, IDR_PNG_LISTSLIDER_NORMALMIDDLE, IDR_PNG_LISTSLIDER_NORMALBOTTOM, IDR_PNG_LISTSLIDER_DOWNTOP, 
            IDR_PNG_LISTSLIDER_DOWNMIDDLE, IDR_PNG_LISTSLIDER_DOWNBOTTOM, IDR_PNG_LISTSLIDER_BKGTOP, IDR_PNG_LISTSLIDER_BKGMIDDLE, IDR_PNG_LISTSLIDER_BKGBOTTOM, "PNG" );
        m_plsLocalAddrbook->SetSliderAlwaysShow( TRUE );
		//m_plsLocalAddrbook->SetClickNoSel(TRUE);
		m_plsLocalAddrbook->SetClickFocus(FALSE);

		CRect rectList;
		m_plsLocalAddrbook->GetWindowRect(&rectList);
		ScreenToClient(&rectList);
		m_pLetterAddrbook = new CLetterIndex( "LetterEp", "LetterEp", CRect(0,0,39,486), this, GETUNIQID, WS_CHILD );
		if ( m_pLetterAddrbook != NULL )
		{
			rectList.left = rectList.right - 3;
			rectList.right = rectList.left + 7;
			m_plsLocalAddrbook->SetSliderRect( rectList );

			m_pLetterAddrbook->SetWindowPos( NULL, rectList.right + 2*CUR_SCREEN_WIDTH_PER, 100*CUR_SCREEN_HEIGHT_PER, 39*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER,SWP_HIDEWINDOW );
			CUmcwebCommon::SetImgForLetter(m_pLetterAddrbook);
			m_pLetterAddrbook->SetLetterHeight(18*CUR_SCREEN_WIDTH_PER);
			m_pLetterAddrbook->SetBindList( m_plsLocalAddrbook );
		}
	}

	CRect rectClient;
	this->GetClientRect(&rectClient);
	ScreenToClient(&rectClient);

	m_stNumber.SetWindowPos( NULL, (700 + 18 - 20)*CUR_SCREEN_WIDTH_PER,  (112 + 18 + 27)*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_stName.SetWindowPos( NULL, (700 + 18 - 20)*CUR_SCREEN_WIDTH_PER,  112*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_stHomeMeeting.SetWindowPos( NULL, (700 + 140 - 48)*CUR_SCREEN_WIDTH_PER ,  112*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransStatic( &m_stName, "主会场" );
	CUmcwebCommon::SetTextTransStatic( &m_stNumber, "分会场" );
	CUmcwebCommon::SetTextTransStatic( &m_stHomeMeeting, "" );

	CUmcwebCommon::SetImgForTransEdit(&m_etHomeMeeting, FALSE);
	m_etHomeMeeting.SetWindowPos( NULL, (700 + 144 - 52)*CUR_SCREEN_WIDTH_PER, (112 - 9)*CUR_SCREEN_HEIGHT_PER, 390*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_etHomeMeeting.SetLimitLength(31);

	m_btnCalendar.SetBindWnd( m_dlgCalendar.GetSafeHwnd() );

	return TRUE;
}

BOOL CMeetTemplateLogic::InitMeetPollingPageControl()
{
	CRect rectClient;
	this->GetClientRect(&rectClient);

	//轮询列表加入
	m_plsMeetPollingRight = new CListChild( "", CRect((700 + 12 - 12) , (651 - 14 - 391 - 51 + 18 + 27), 508+(700 + 12 - 12), (390 - (18 + 27))+(651 - 14 - 391 - 51 + 18 + 27)), this, "", 0, WS_CHILD );
	if ( NULL != m_plsMeetPollingRight )
	{
		m_plsMeetPollingRight->SetWindowPos( NULL, (700 + 12 - 12)*CUR_SCREEN_WIDTH_PER , (651 - 14 - 391 - 51 + 18 + 27)*CUR_SCREEN_HEIGHT_PER, 508*CUR_SCREEN_WIDTH_PER, (390 - (18 + 27))*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
		m_plsMeetPollingRight->SetImage( IDR_PNG_LIST_TOPLEFT, IDR_PNG_LIST_TOPCEN, IDR_PNG_LIST_TOPRIGHT, IDR_PNG_LIST_CENLEFT, IDR_PNG_LIST_CENRIGHT,
			IDR_PNG_LIST_BTLEFT, IDR_PNG_LIST_BTCEN, IDR_PNG_LIST_BTRIGHT, IDR_PNG_LIST_TOPCEN, "PNG" );
	}
  
	//轮询左视图会场列表加入
	m_plsPollingLeft = new CListChild( "", CRect(12, 100, (690 - 60)+12, 488+100), this, "", 0, WS_CHILD );
	if ( NULL != m_plsPollingLeft )
	{
		m_plsPollingLeft->SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 100*CUR_SCREEN_HEIGHT_PER, (690 - 60)*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
		m_plsPollingLeft->SetImage( IDR_PNG_LIST_TOPLEFT, IDR_PNG_LIST_TOPCEN, IDR_PNG_LIST_TOPRIGHT, IDR_PNG_LIST_CENLEFT, IDR_PNG_LIST_CENRIGHT,
			IDR_PNG_LIST_BTLEFT, IDR_PNG_LIST_BTCEN, IDR_PNG_LIST_BTRIGHT, IDR_PNG_LIST_TOPCEN, "PNG" );
		m_plsPollingLeft->SetSliderImage( IDR_PNG_LISTSLIDER_NORMALTOP, IDR_PNG_LISTSLIDER_NORMALMIDDLE, IDR_PNG_LISTSLIDER_NORMALBOTTOM, IDR_PNG_LISTSLIDER_DOWNTOP, 
            IDR_PNG_LISTSLIDER_DOWNMIDDLE, IDR_PNG_LISTSLIDER_DOWNBOTTOM, IDR_PNG_LISTSLIDER_BKGTOP, IDR_PNG_LISTSLIDER_BKGMIDDLE, IDR_PNG_LISTSLIDER_BKGBOTTOM, "PNG" );
        m_plsPollingLeft->SetSliderAlwaysShow( TRUE );
	}
 	m_pLetterPolling = new CLetterIndex( "LetterPolling", "LetterPolling", CRect(0,0,39,486), this, GETUNIQID, WS_CHILD );
	if( NULL != m_pLetterPolling )
	{
		CUmcwebCommon::SetImgForLetter(m_pLetterPolling);
		m_pLetterPolling->SetLetterHeight(18*CUR_SCREEN_WIDTH_PER);
		m_pLetterPolling->SetBindList( m_plsPollingLeft );
		m_plsPollingLeft->GetWindowRect(&rectClient);
		ScreenToClient(&rectClient);

		rectClient.left = rectClient.right - 3;
		rectClient.right = rectClient.left + 7;
		m_plsPollingLeft->SetSliderRect( rectClient );

		m_pLetterPolling->SetWindowPos( NULL, rectClient.right + 2*CUR_SCREEN_WIDTH_PER, 100*CUR_SCREEN_HEIGHT_PER, 39*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER,SWP_HIDEWINDOW );
	}

	m_plsPollingLeft->GetWindowRect(&rectClient);

	m_stNumber.SetWindowPos( NULL, (700 + 18 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 18 + 27)*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_stName.SetWindowPos( NULL, (700 + 18 - 12)*CUR_SCREEN_WIDTH_PER,  112*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_stTmpType.SetWindowPos( NULL, (700 + 18 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 2*(18 + 27))*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_stIntervel.SetWindowPos( NULL, (700 + 140 - 48)*CUR_SCREEN_WIDTH_PER ,  (112 + 18 + 27)*CUR_SCREEN_HEIGHT_PER, 80*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_stPollingSecond.SetWindowPos( NULL, (700 + 144 - 52 + 51 * 2 + 80 + 43)*CUR_SCREEN_WIDTH_PER,  (112 + 18 + 27)*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	CUmcwebCommon::SetTextTransStatic( &m_stName, "会议轮询" );
	CUmcwebCommon::SetTextTransStatic( &m_stNumber, "轮询间隔" );
	CUmcwebCommon::SetTextTransStatic( &m_stTmpType, "轮询排序" );
	CUmcwebCommon::SetTextTransStatic( &m_stIntervel, "" );
	CUmcwebCommon::SetTextTransStatic( &m_stPollingSecond, "秒" );
	
	CUmcwebCommon::SetImgForTransEdit(&m_etPollingTime, FALSE);
	m_etPollingTime.SetWindowPos( NULL, (700 + 144 - 52 + 51 + 30)*CUR_SCREEN_WIDTH_PER, ((112 + 18 + 27) - 9)*CUR_SCREEN_HEIGHT_PER, 80*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_etPollingTime.SetShowIcon(FALSE);
	m_etPollingTime.SetLimitLength(4);
	m_etPollingTime.SetTextAlign(StringAlignmentCenter);

	m_btnSwitchPolling.SetImage( IDR_PNG_LOGINWND_BTN_OFF,IDR_PNG_LOGINWND_BTN_OFFDOWN, IDR_PNG_LOGINWND_BTN_OFFDIS,
		IDR_PNG_LOGINWND_BTN_ON, IDR_PNG_LOGINWND_BTN_ONDOWN, IDR_PNG_LOGINWND_BTN_ONDIS );
	m_btnSwitchPolling.SetWindowPos( NULL, (700 + 134 - 52 + 312)*CUR_SCREEN_WIDTH_PER, (112 - 9)*CUR_SCREEN_HEIGHT_PER, 113*CUR_SCREEN_WIDTH_PER, 37*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnSwitchPolling.EnableWindow(FALSE);

	m_btnSubPollingTime.SetImage( IDR_PNG_BTN_SUB, IDR_PNG_BTN_SUBDOWN, IDR_PNG_BTN_SUBDIS );
	m_btnPlusPollingTime.SetImage( IDR_PNG_BTN_PLUS, IDR_PNG_BTN_PLUSDOWN, IDR_PNG_BTN_PLUSDIS );
	
	m_btnSubPollingTime.SetWindowPos( NULL, (700 + 144 - 52 + 25)*CUR_SCREEN_WIDTH_PER, ((112 + 18 + 27) - 7)*CUR_SCREEN_HEIGHT_PER, m_btnSubPollingTime.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnSubPollingTime.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
    m_btnPlusPollingTime.SetWindowPos( NULL, (700 + 144 - 52 + 51 + 80 + 37)*CUR_SCREEN_WIDTH_PER, ((112 + 18 + 27) - 7)*CUR_SCREEN_HEIGHT_PER, m_btnPlusPollingTime.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnPlusPollingTime.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	m_btnSetTop.SetWindowPos( NULL, (700 + 144 - 52 + 97)*CUR_SCREEN_WIDTH_PER,  (112 + 2*(18 + 27))*CUR_SCREEN_HEIGHT_PER, m_btnSetTop.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnSetTop.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnMoveUp.SetWindowPos( NULL, (700 + 144 - 52 + 97 + 1*(m_btnSetTop.GetImageSize().cx + 5))*CUR_SCREEN_WIDTH_PER,  (112 + 2*(18 + 27))*CUR_SCREEN_HEIGHT_PER, m_btnMoveUp.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnMoveUp.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnMoveDown.SetWindowPos( NULL, (700 + 144 - 52 + 97 + 2*(m_btnSetTop.GetImageSize().cx + 5))*CUR_SCREEN_WIDTH_PER,  (112 + 2*(18 + 27))*CUR_SCREEN_HEIGHT_PER, m_btnMoveDown.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnMoveDown.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnSetBottom.SetWindowPos( NULL, (700 + 144 - 52 + 97 + 3*(m_btnSetTop.GetImageSize().cx + 5))*CUR_SCREEN_WIDTH_PER,  (112 + 2*(18 + 27))*CUR_SCREEN_HEIGHT_PER, m_btnSetBottom.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnSetBottom.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnRemoveAll.SetWindowPos( NULL, (700 + 144 - 52 + 97 + 4*(m_btnSetTop.GetImageSize().cx + 5))*CUR_SCREEN_WIDTH_PER,  (112 + 2*(18 + 27))*CUR_SCREEN_HEIGHT_PER, m_btnRemoveAll.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnRemoveAll.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	return TRUE;
}

BOOL CMeetTemplateLogic::InitMeetDiscussPageControl()
{
	m_plsDiscussLeft = new CListChild( "", CRect(12, 100, 630+12, 488+100), this, "", 0, WS_CHILD ); 
	
	if ( NULL != m_plsDiscussLeft )
	{
		m_plsDiscussLeft->SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 100*CUR_SCREEN_HEIGHT_PER, 630*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
		m_plsDiscussLeft->SetImage( IDR_PNG_LIST_TOPLEFT, IDR_PNG_LIST_TOPCEN, IDR_PNG_LIST_TOPRIGHT, IDR_PNG_LIST_CENLEFT, IDR_PNG_LIST_CENRIGHT,
			IDR_PNG_LIST_BTLEFT, IDR_PNG_LIST_BTCEN, IDR_PNG_LIST_BTRIGHT, IDR_PNG_LIST_TOPCEN, "PNG" );
		m_plsDiscussLeft->SetSliderImage( IDR_PNG_LISTSLIDER_NORMALTOP, IDR_PNG_LISTSLIDER_NORMALMIDDLE, IDR_PNG_LISTSLIDER_NORMALBOTTOM, IDR_PNG_LISTSLIDER_DOWNTOP, 
            IDR_PNG_LISTSLIDER_DOWNMIDDLE, IDR_PNG_LISTSLIDER_DOWNBOTTOM, IDR_PNG_LISTSLIDER_BKGTOP, IDR_PNG_LISTSLIDER_BKGMIDDLE, IDR_PNG_LISTSLIDER_BKGBOTTOM, "PNG" );
        m_plsDiscussLeft->SetSliderAlwaysShow( TRUE );
		//m_plsDiscussLeft->SetClickNoSel(TRUE);
		m_plsDiscussLeft->SetClickFocus(FALSE);
		
		CRect rectList;
		m_plsDiscussLeft->GetWindowRect(&rectList);
		ScreenToClient(&rectList);
		m_pLetterDiscuss = new CLetterIndex( "LetterDiscuss", "LetterDiscuss", CRect(0,0,39,486), this, GETUNIQID, WS_CHILD );
		if ( m_pLetterDiscuss != NULL )
		{
			rectList.left = rectList.right - 3;
			rectList.right = rectList.left + 7;
			m_plsDiscussLeft->SetSliderRect( rectList );
			
			m_pLetterDiscuss->SetWindowPos( NULL, rectList.right + 2*CUR_SCREEN_WIDTH_PER, 100*CUR_SCREEN_HEIGHT_PER, 39*CUR_SCREEN_WIDTH_PER, 488*CUR_SCREEN_HEIGHT_PER,SWP_HIDEWINDOW );
			CUmcwebCommon::SetImgForLetter(m_pLetterDiscuss);
			m_pLetterDiscuss->SetLetterHeight(18*CUR_SCREEN_WIDTH_PER);
			m_pLetterDiscuss->SetBindList( m_plsDiscussLeft );
		}
	}

	return TRUE;
}

void CMeetTemplateLogic::SetMediaInfoBtnPos(BOOL bDefaut)
{
	CRect rectClient;
	this->GetClientRect(&rectClient);
	if ( bDefaut )
	{
		m_stMediaInfo.SetWindowPos( NULL, (700 + 18 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 3*(18 + 27))*CUR_SCREEN_HEIGHT_PER + 7, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
		m_etAdaptRes.SetWindowPos( NULL, (700 + 134 - 12)*CUR_SCREEN_WIDTH_PER, (112 + 3*45 - 3)*CUR_SCREEN_HEIGHT_PER, (391 - 10 - 41)*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
		m_btnMediaInfo.SetWindowPos( NULL, 1162*CUR_SCREEN_WIDTH_PER, (112 + 3*45 - 3)*CUR_SCREEN_HEIGHT_PER, m_btnMediaInfo.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnMediaInfo.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	}
	else
	{
		m_stMediaInfo.SetWindowPos( NULL, (700 + 18 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 5*(18 + 27))*CUR_SCREEN_HEIGHT_PER + 7, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
		m_etAdaptRes.SetWindowPos( NULL, (700 + 134 - 12)*CUR_SCREEN_WIDTH_PER, (112 + 5*45 - 3)*CUR_SCREEN_HEIGHT_PER, (391 - 10 - 41)*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
		m_btnMediaInfo.SetWindowPos( NULL, 1162*CUR_SCREEN_WIDTH_PER, (112 + 5*45 - 3)*CUR_SCREEN_HEIGHT_PER, m_btnMediaInfo.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnMediaInfo.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );	
	}
}

void CMeetTemplateLogic::SetMediaInfoBtnHide(BOOL bHide)
{
	if ( bHide )
	{
		m_stMediaInfo.ShowWindow(SW_HIDE);
		m_etAdaptRes.ShowWindow(SW_HIDE);
		m_btnMediaInfo.ShowWindow(SW_HIDE);
	}
	else
	{
		m_stMediaInfo.ShowWindow(SW_SHOW);
		m_etAdaptRes.ShowWindow(SW_SHOW);
		m_btnMediaInfo.ShowWindow(SW_SHOW);
	}
}

void CMeetTemplateLogic::SetRateInfoPos(BOOL bDefaut)
{
	CRect rectClient;
	this->GetClientRect(&rectClient);
	if ( bDefaut )
	{	
		m_stConfRate.SetWindowPos( NULL, (700 + 18 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 4*(18 + 27))*CUR_SCREEN_HEIGHT_PER + 7 + 7, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
		m_stShowRate.SetWindowPos( NULL, (700 + 18 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 5*(18 + 27))*CUR_SCREEN_HEIGHT_PER + 7 + 7, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );	
		m_stConfRateShow.SetWindowPos( NULL, (700 + 134 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 4*(18 + 27))*CUR_SCREEN_HEIGHT_PER + 7 + 7, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
		m_stShowRateShow.SetWindowPos( NULL, (700 + 134 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 5*(18 + 27))*CUR_SCREEN_HEIGHT_PER + 7 + 7, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	}
	else
	{	
		m_stConfRate.SetWindowPos( NULL, (700 + 18 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 6*(18 + 27))*CUR_SCREEN_HEIGHT_PER + 7 + 7, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
		m_stShowRate.SetWindowPos( NULL, (700 + 18 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 7*(18 + 27))*CUR_SCREEN_HEIGHT_PER + 7 + 7, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

		if ( em_SCANF_PAGE_STATUS == m_emOperateFlag )
		{
			m_stConfRateShow.SetWindowPos( NULL, (700 + 134 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 6*(18 + 27))*CUR_SCREEN_HEIGHT_PER + 7 + 7, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
			m_stShowRateShow.SetWindowPos( NULL, (700 + 134 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 7*(18 + 27))*CUR_SCREEN_HEIGHT_PER + 7 + 7, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
		}
		else
		{
			m_stConfRateUnit.SetWindowPos( NULL, (700 + 334 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 6*(18 + 27))*CUR_SCREEN_HEIGHT_PER + 7 + 7, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
			m_stShowRateUnit.SetWindowPos( NULL, (700 + 334 - 12)*CUR_SCREEN_WIDTH_PER,  (112 + 7*(18 + 27))*CUR_SCREEN_HEIGHT_PER + 7 + 7, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
		}
	}
}

void CMeetTemplateLogic::SetRateInfoHide(BOOL bHide)
{
	if ( bHide )
	{
		m_stConfRate.ShowWindow(SW_HIDE);
		m_stShowRate.ShowWindow(SW_HIDE);
		m_stConfRateShow.ShowWindow(SW_HIDE);
		m_stShowRateShow.ShowWindow(SW_HIDE);
		m_stConfRateUnit.ShowWindow(SW_HIDE);
		m_stShowRateUnit.ShowWindow(SW_HIDE);
		m_etConfRate.ShowWindow(SW_HIDE);
		m_etShowRate.ShowWindow(SW_HIDE);
		m_btnPlusConfRate.ShowWindow(SW_HIDE);
		m_btnSubConfRate.ShowWindow(SW_HIDE);
		m_btnPlusShowRate.ShowWindow(SW_HIDE);
		m_btnSubShowRate.ShowWindow(SW_HIDE);
		return;
	}

	m_stConfRate.ShowWindow(SW_SHOW);
	m_stShowRate.ShowWindow(SW_SHOW);

	if ( em_SCANF_PAGE_STATUS == m_emOperateFlag )
	{
		m_stConfRateShow.ShowWindow(SW_SHOW);
		m_stShowRateShow.ShowWindow(SW_SHOW);
		m_stConfRateUnit.ShowWindow(SW_HIDE);
		m_stShowRateUnit.ShowWindow(SW_HIDE);
		m_etConfRate.ShowWindow(SW_HIDE);
		m_etShowRate.ShowWindow(SW_HIDE);
		m_btnPlusConfRate.ShowWindow(SW_HIDE);
		m_btnSubConfRate.ShowWindow(SW_HIDE);
		m_btnPlusShowRate.ShowWindow(SW_HIDE);
		m_btnSubShowRate.ShowWindow(SW_HIDE);
	} 
	else
	{
		m_stConfRateShow.ShowWindow(SW_HIDE);
		m_stShowRateShow.ShowWindow(SW_HIDE);
		m_stConfRateUnit.ShowWindow(SW_SHOW);
		m_stShowRateUnit.ShowWindow(SW_SHOW);
		m_etConfRate.ShowWindow(SW_SHOW);
		m_etShowRate.ShowWindow(SW_SHOW);
		m_btnPlusConfRate.ShowWindow(SW_SHOW);
		m_btnSubConfRate.ShowWindow(SW_SHOW);
		m_btnPlusShowRate.ShowWindow(SW_SHOW);
		m_btnSubShowRate.ShowWindow(SW_SHOW);
	}
}

// void CMeetTemplateLogic::UpdatePollingUIState()
// {
// 	//需求确认,off时也可编辑  -- 20140408
// // 	m_btnPlusPollingTime.EnableWindow(m_bSwitchPolling);
// // 	m_btnSubPollingTime.EnableWindow(m_bSwitchPolling);
// // 	m_etPollingTime.EnableWindow(m_bSwitchPolling);
// 
// 	CleanSearchList();
// 
// 	if ( /*m_bSwitchPolling &&*/ m_mapEpList.size() - m_vecTurnList.size() > 0 )
// 	{
// 		m_btnAllAdd.EnableWindow(TRUE);
// 	}
// 	else
// 	{
// 		m_btnAllAdd.EnableWindow(FALSE);
// 	}
// 
// // 	if ( m_bSwitchPolling )
// // 	{
// 		UpdatePollingLeftShowList( m_mapEpList,  TRUE );
// 		UpdatePollingList( 0, 0 );
// // 	} 
// // 	else
// // 	{
// // 		if ( ( NULL == m_plsPollingLeft ) || ( NULL == m_plsMeetPollingRight ) )
// // 		{
// // 			return;
// // 		}
// // 		
// // 		TEpAddrList tCnsLst;
// // 		Value_TouchListTempCns val_TempCns( tCnsLst );
// // 		m_plsPollingLeft->SetData( val_TempCns);
// // 		
// // 		TCMSConfTemplate tCnsTemplate;
// // 		Value_TouchListTempPoll val_TempPoll( tCnsTemplate );
// // 		m_plsMeetPollingRight->SetData( val_TempPoll );
// // 
// // 		ShowSortControl(FALSE);
// // 	}
// 
// //	m_etSearch.EnableWindow(m_bSwitchPolling);
// }

void CMeetTemplateLogic::SetControlPos()
{
	//---界面主体
	CRect rectClient;
	this->GetClientRect(&rectClient);
	
	m_stTemplateLeftTitle.SetWindowPos( NULL, 17*CUR_SCREEN_WIDTH_PER,  14*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stTemplateRightTitle.SetWindowPos( NULL, 720*CUR_SCREEN_WIDTH_PER, 14*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	
	m_btnCancel.SetWindowPos( NULL, (1226 - 8 - m_btnCancel.GetImageSize().cx)*CUR_SCREEN_WIDTH_PER, 3*CUR_SCREEN_HEIGHT_PER, 
		m_btnCancel.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnCancel.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnEdit.SetWindowPos( NULL,  (1226 - 8 - m_btnEdit.GetImageSize().cx)*CUR_SCREEN_WIDTH_PER, 3*CUR_SCREEN_HEIGHT_PER, 
		m_btnEdit.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnEdit.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnCancel.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	m_btnSave.SetWindowPos( NULL, rectClient.left - (8 + m_btnSave.GetImageSize().cx)*CUR_SCREEN_WIDTH_PER, 3*CUR_SCREEN_HEIGHT_PER, 
		m_btnSave.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnSave.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	m_plsMeetTmp->GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	
	m_btnDelete.SetWindowPos( NULL, rectClient.right - m_btnDelete.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnDelete.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnDelete.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_btnAllAdd.SetWindowPos( NULL, rectClient.right - m_btnAllAdd.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnAllAdd.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnAllAdd.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
	m_btnDelete.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	m_btnAllSel.SetWindowPos( NULL, rectClient.right - 2*m_btnAllSel.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - 10*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnAllSel.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnAllSel.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );	
	m_btnNewTmp.SetWindowPos( NULL, rectClient.right - 3*m_btnNewTmp.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - 2*10*CUR_SCREEN_WIDTH_PER, 55*CUR_SCREEN_HEIGHT_PER, m_btnNewTmp.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnNewTmp.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

	m_btnNewTmp.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	m_etSearch.SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 53*CUR_SCREEN_HEIGHT_PER,  rectClient.right - 
		m_btnNewTmp.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - 15*CUR_SCREEN_WIDTH_PER,41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

	CRect rectTab;
	m_btnMeetingInfo.SetWindowPos( NULL,  (690 + 12)*CUR_SCREEN_WIDTH_PER, 51*CUR_SCREEN_HEIGHT_PER, m_btnMeetingInfo.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnMeetingInfo.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_btnMeetingInfo.GetWindowRect(&rectTab);
	ScreenToClient( &rectTab );
	m_btnGroupInfo.SetWindowPos( NULL, rectTab.right, 51*CUR_SCREEN_HEIGHT_PER, m_btnGroupInfo.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnGroupInfo.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_btnGroupInfo.GetWindowRect(&rectTab);
	ScreenToClient( &rectTab );
	m_btnPollingInfo.SetWindowPos( NULL, rectTab.right, 51*CUR_SCREEN_HEIGHT_PER, m_btnPollingInfo.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnPollingInfo.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_btnPollingInfo.GetWindowRect(&rectTab);
	ScreenToClient( &rectTab );
	m_btnDiscussInfo.SetWindowPos( NULL, rectTab.right, 51*CUR_SCREEN_HEIGHT_PER, m_btnDiscussInfo.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnDiscussInfo.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

	m_plsMeetTmp->GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	m_btnStartConf.SetWindowPos( NULL, 684*CUR_SCREEN_WIDTH_PER  + ((1226 - 685)*CUR_SCREEN_WIDTH_PER - m_btnStartConf.GetImageSize().cx*CUR_SCREEN_WIDTH_PER)/2, rectClient.bottom - 26*CUR_SCREEN_HEIGHT_PER -m_btnStartConf.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, m_btnStartConf.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnStartConf.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	SetMediaInfoBtnPos();
	SetMediaInfoBtnHide();
	SetRateInfoPos();
	SetRateInfoHide();
	m_btnReturn.ShowWindow(SW_HIDE);
}

BOOL CMeetTemplateLogic::CreatePageControls()
{
	//初始化父窗口所有控件元素
	if ( InitControlPane() )   //初始化所有控件
	{
		//初始化各个子窗口控件元素
		InitMeetInfoPageControl();
		InitMeetEpPageControl();
	    InitMeetPollingPageControl();
		InitMeetDiscussPageControl();
		
		SetControlPos();
	}
	else
	{
		return FALSE;
	}
	
	//设置默认初始页面
	m_tSelTemplate.Clear();
	ResetInitPage();

	return TRUE;
}

void CMeetTemplateLogic::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDlgChild::OnShowWindow(bShow, nStatus);
	
	if (bShow)
	{
		//获取cmslib接口指针
		GetLibPtr();
	}
}

void CMeetTemplateLogic::InitDlg() 
{  
	m_etSearch.SetWindowText("");
	m_tSelTemplate.InvalidConfTemp();

	m_emOperateFlag = em_SCANF_PAGE_STATUS;
	m_plsMeetTmp->SetSelItem(-1);
	SetSelectedTmpDataToScanfPage(m_tSelTemplate);

	ResetInitPage();

	m_tNewTemplate.Clear();
	m_tSelTemplate.Clear();
}

void CMeetTemplateLogic::GetLibPtr()
{
	if( m_tTmpConfigIF == NULL )
	{
		BUSINESSIFPTR->GetCtrlInterface(&m_tTmpConfigIF);
	}
	
	if( m_tTmpConfigIF != NULL )
	{
		m_tTmpConfigIF->SetNotifyWnd(this->m_hWnd);
	}
	
	if( m_pconfCtrlIF == NULL )
	{
		BUSINESSIFPTR->GetCtrlInterface(&m_pconfCtrlIF);
	}

	if( m_pAddrBookIF == NULL )
	{
		BUSINESSIFPTR->GetCtrlInterface(&m_pAddrBookIF);
	}

	if ( m_pUmsConfig == NULL )
	{
		BUSINESSIFPTR->GetCtrlInterface(&m_pUmsConfig);
	}
}

BOOL CMeetTemplateLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();

	GetLibPtr();	//获取cmslib接口指针
	RegisterFun();	//注册窗口函数

	m_dlgMediaCfg.Create( IDD_DIALOG_MEDIAICFG, this ); 		
	m_dlgMediaCfg.SetWindowPos( NULL, 690, 0, 536, 600, SWP_SHOWWINDOW ); 

	m_dlgMeetDiscuss.Create( IDD_DIALOG_MEETDISCUSS, this ); 		
	m_dlgMeetDiscuss.SetWindowPos( NULL, (700 + 18 - 12),  112 - 9, 536 - ((700 + 18 - 12) - 690), 600 - 112, SWP_SHOWWINDOW );

	if( !CreatePageControls() )
	{
		return FALSE;
	}
    
    m_btnPlusTime.SetUseTimer( TRUE );
    m_btnSubTime.SetUseTimer( TRUE );
	m_btnPlusConfRate.SetUseTimer( TRUE );
    m_btnSubConfRate.SetUseTimer( TRUE );
	m_btnPlusShowRate.SetUseTimer( TRUE );
    m_btnSubShowRate.SetUseTimer( TRUE );
	m_btnPlusPollingTime.SetUseTimer( TRUE );
	m_btnSubPollingTime.SetUseTimer( TRUE );

	CDragWindow* pDragWindow = CDragWindow::GetDragWindow();
	if ( NULL != pDragWindow )
    {
		pDragWindow->RegisterDropWindow( (CWnd*)this );
    }

	return TRUE; 
}

TTPConfTemplate* CMeetTemplateLogic::GetConfTemplateByID( u16 wConfTemplateID ) const 
{
	int nCont = m_tpTmpRefreshList.Size();
	for ( int i = 0 ; i< nCont; i++ )
	{
		u16 wConfTmpID = m_tpTmpRefreshList[i].m_wID;
		if ( wConfTmpID == wConfTemplateID ) 
		{
			return &m_tpTmpRefreshList[i];
		}
	}
	
	return NULL;
}

LRESULT CMeetTemplateLogic::OnRefreshTmpListNotify(WPARAM wParam, LPARAM lParam)
{
	MeetTmpRefresh();
    u16 swTmpId = (u16)wParam;
 	if ( m_emOperateFlag != em_SCANF_PAGE_STATUS )
	{
		return S_OK;
	}

	if( swTmpId == m_tSelTemplate.m_wID )   // 编辑状态
	{	
		TCMSConfTemplate* pTCmsConfTmp = (TCMSConfTemplate*)GetConfTemplateByID(swTmpId);
		if ( NULL  == pTCmsConfTmp )
		{
			return S_OK;
		}

		m_tSelTemplate = *pTCmsConfTmp;
		m_tBaseTemplate = m_tSelTemplate;

		if ( m_plsMeetTmp != NULL )
		{
			m_plsMeetTmp->SetSelItem( swTmpId );
		    m_tSelTemplate.m_wID = pTCmsConfTmp->m_wID;
		}

		//显示模板数据
		SetSelectedTmpDataToScanfPage(m_tSelTemplate);
	    UpdateResUsedCountToControl(m_dlgMediaCfg.GetCheckResNum());
	}
	else// if( INVALID_WORD == m_tSelTemplate.m_wID )  //新建状态
	{
		 CString strSelTmpName = m_tNewTemplate.m_achConfName;   //新建时实现名称跳转   之后赋值到选中Template
		 if ( strSelTmpName.IsEmpty() )
		 {
			 return S_OK;
		 }

		 TCMSConfTemplate *pConfTmp = (TCMSConfTemplate*)GetConfTemplateByID(swTmpId);
		 if ( NULL  == pConfTmp )
		 {
			 return S_OK;
		 }
		 
		 m_tSelTemplate = *pConfTmp;
		m_tBaseTemplate = m_tSelTemplate;

		 if ( NULL != pConfTmp  && strcmp( pConfTmp->m_achConfName, m_tSelTemplate.m_achConfName) == 0 )
		 {
			 m_tSelTemplate.m_wID = pConfTmp->m_wID;
			 if ( m_plsMeetTmp != NULL )
			 {
				 m_plsMeetTmp->SetSelItem( m_tSelTemplate.m_wID );
			 }

			//显示模板数据
			 SetSelectedTmpDataToScanfPage(m_tSelTemplate);
			 UpdateResUsedCountToControl(m_dlgMediaCfg.GetCheckResNum());
		 }			
	}

	return 0L;
}

void CMeetTemplateLogic::MeetTmpRefresh()
{
	m_tpTmpRefreshList.Clear();
	if ( m_tTmpConfigIF != NULL )
	{
		m_tTmpConfigIF->GetConfTemplateList(m_tpTmpRefreshList);

		//发送模板数据到会议列表
		CMsgHandle::SendMessage( UI_UMS_REFRESH_CONFTEMPLATE_LIST,(WPARAM)&m_tpTmpRefreshList );

		std::set<CString> setConfTmpSelectedIconItem; 
		for( s32 nIndex = 0; nIndex < m_tpTmpRefreshList.Size(); nIndex++ )
		{
			TCMSConfTemplate* pTConfTemp = (TCMSConfTemplate*)&m_tpTmpRefreshList.GetAt(nIndex);
			if ( pTConfTemp == NULL )
			{
				continue;
			}
			
			if ( pTConfTemp->m_tStartTime == 0 )
			{
				continue;
			}
			
			CString strConfName = pTConfTemp->m_achConfName;
			
			std::set<CString>::iterator iter = m_setSelectedTmpIconItem.find(strConfName);
			if ( iter != m_setSelectedTmpIconItem.end() )
			{
				setConfTmpSelectedIconItem.insert(strConfName);
			}
		}
		m_setSelectedTmpIconItem.clear();
		m_setSelectedTmpIconItem = setConfTmpSelectedIconItem;

		OnSearchEditChange();
		UpdateTmpShowList();
		UpdateUIState();
	}
}

LRESULT CMeetTemplateLogic::OnTmpListOperateResult(WPARAM wParam, LPARAM lParam)
{
	EmTpConfTemplateRet emErrCode;
	emErrCode = (EmTpConfTemplateRet)wParam;
	
	CString strMsg;
    CString strErr = "";
    switch(emErrCode)
    {
	case TP_ConfTemplate_UnKonw:
		{
			strErr = " ";//未知错误";  2012-8-7 SE石文娟确认未知错误不做提示 by yjj
		}
		break;
	case TP_ConfTemplate_MaxNum:             //模板数量到达上限
		{
			strErr = "模板数量到达上限";
		}
		break;
	case TP_ConfTemplate_E164Repeat:		//e164号码重复
		{
			strErr = "e164号码重复";
		}
		break;
	case TP_ConfTemplate_UnFindConf:		//未找到条目
		{
			strErr = "未找到条目";
		}
		break;
	case TP_ConfTemplate_ParamInValid:		//参数错误
		{
			strErr = "参数错误";
		}
		break;
	case TP_ConfTemplate_AddSuccess:
	case TP_ConfTemplate_DelSuccess:
	case TP_ConfTemplate_UpdateSuccess:
		{
			//strMsg = "会议模板操作成功";
		}
		//MESSAGEWND( strMsg  ); 			//ldy 120926  需求确认  操作成功不提醒
		return emErrCode;
    }	
	
 
    if (!strErr.IsEmpty() )   
    {
        strMsg = "会议模板操作失败: " + strErr; 
		MESSAGEWND( strMsg  );
    } 
	else
	{
		MESSAGEWND( "会议模板操作失败"  );
	}
	
    return emErrCode;	
}

void CMeetTemplateLogic::ResetInitPage()
{
	m_stTemplateRightTitle.SetWindowText("会议模板信息");
	m_emOperateFlag = em_SCANF_PAGE_STATUS;
	m_emTabFlag = em_MEETINFO_PAGE;
	m_etSearch.EnableWindow(TRUE);

	m_btnMeetingInfo.EnableWindow(FALSE);
	m_btnGroupInfo.EnableWindow(TRUE);
	m_btnPollingInfo.EnableWindow(TRUE);
	m_btnDiscussInfo.EnableWindow(TRUE);

	m_dlgCalendar.ShowWindow(SW_HIDE);

	m_btnCancel.ShowWindow(SW_HIDE);
	m_btnEdit.ShowWindow(SW_SHOW);
	m_btnSave.ShowWindow(SW_HIDE);

	m_btnNewTmp.ShowWindow(SW_SHOW);
	m_btnNewTmp.EnableWindow(TRUE);
	m_btnAllSel.ShowWindow(SW_SHOW);
	m_btnDelete.ShowWindow(SW_SHOW);

	m_mapEpList.clear();
	m_mapEpInfoList.clear();
	m_vecTurnList.clear();

	m_mapDiscussList.clear();
	m_mapDiscussSelItem.clear();

	UpdateUIState();
	CleanPageList();
	SetSelectedTmpDataToScanfPage(m_tSelTemplate);

	HideAllPageCtrl();
	ResetSerchEditLen();	
	
	if ( NULL != m_plsMeetPollingRight )
	{
		m_plsMeetPollingRight->SetSelItem(-1);
		SetSortControlDisable();
	}

	if ( ( NULL != m_plsMeetTmp ) && ( NULL != m_pLetterTmp ) )
	{
		m_plsMeetTmp->ShowWindow(TRUE);
		m_pLetterTmp->ShowWindow(TRUE);
		m_plsMeetTmp->SetSelItem( -1 );
		m_plsMeetTmp->EnableWindow(TRUE);
		m_pLetterTmp->EnableWindow(TRUE);
	}
}

LRESULT CMeetTemplateLogic::OnRefreshAddrListListNotify(WPARAM wParam, LPARAM lParam)
{
	m_vecLocalbookRefreshList.clear();
	vector<TAddrItem>* pvecAddrItem = (vector<TAddrItem>*)wParam;
	m_vecLocalbookRefreshList = *pvecAddrItem;

	if ( ( m_emOperateFlag != em_SCANF_PAGE_STATUS ) && ( m_emTabFlag == em_Ep_PAGE ) )
	{
		OnSearchEditChange();
	}
	else
	{
		m_vecLocalbookShowList = m_vecLocalbookRefreshList;
	}
	UpdateAddrbookShowList();
	return 0;
}

void CMeetTemplateLogic::UpdateAddrbookShowList()
{
	if ( m_pUmsConfig == NULL )
	{
		return;
	}

// 	if ( m_pAddrBookIF->GetAddrLoadingState() )
// 	{
// 		return;
// 	}

	FilterAddrbookList();   //多用户新建地址簿  重新得到m_vecLocalbookSearchList

	CString strText;
	m_etSearch.GetWindowText( strText );
	
	if ( strText.IsEmpty() )
	{
		m_vecLocalbookShowList = m_vecLocalbookRefreshList;
	}
	else
	{
		m_vecLocalbookShowList = m_vecLocalbookSearchList;
	}

	//sip、gk，在线、不在线状态
	vector<TAliasEx> vctCnsRegInfo;
	vctCnsRegInfo = m_pUmsConfig->GetAllTAliasEx();
	
	vector<TAddrItem>::iterator itShow = m_vecLocalbookShowList.begin();
	for ( ; itShow != m_vecLocalbookShowList.end(); itShow++ )
	{
		TAddrInfo tAddrInfo = itShow->tAddrInfo;
		
		CString strLetter;
		//获取条目名称字母索引。当只有会场号码时对号码排序，索引为空格+号码的形式，保证号码在名字前面 -2012.11.7 xcr		
        if ( strcmp( tAddrInfo.achEntryName, "" ) == 0 )
        {
            strLetter.Format( " %s", tAddrInfo.achE164 );
        }
        else
        {
			CListChild::GetFirstLetter( tAddrInfo.achEntryName, strLetter );
        }

		//如果条目在注册信息中，表示在线
		BOOL bFind = FALSE;
		TAliasEx* pTAliasEx = NULL;
		vector<TAliasEx>::iterator it = vctCnsRegInfo.begin();

		for ( ; it != vctCnsRegInfo.end(); it++ )
		{
			if ( it->m_vecTTPAlias.size() > 0 )
			{
				bFind = TRUE;
			}
			
			//只有当E164和会场名都匹配时，显示在线----------------20131123 by sc
			CString strE164;
			CString strEntryName;
			vector<TTPAlias>::iterator itTTPAlias = it->m_vecTTPAlias.begin();
			for ( ; itTTPAlias != it->m_vecTTPAlias.end(); itTTPAlias++ )
			{
				if ( itTTPAlias->m_byType == tp_Alias_e164 )
				{
					strE164 = itTTPAlias->m_abyAlias;
				}
				else
				{
					strEntryName = itTTPAlias->m_abyAlias;
				}
			}
			
			//名称不存在
			if ( 0 == strcmp( tAddrInfo.achEntryName, "" ) )
			{
				if ( strcmp( tAddrInfo.achE164, strE164 ) != 0 )
				{
					bFind = FALSE;
				}
			} 
			
			//号码不存在
			if ( 0 == strcmp( tAddrInfo.achE164, "" ) )
			{
				if ( strcmp( tAddrInfo.achEntryName, strEntryName ) != 0 )
				{
					bFind = FALSE;
				}
			}
			
			//名称号码都存在
			if ( 0 != strcmp( tAddrInfo.achEntryName, "" ) && 0 != strcmp( tAddrInfo.achE164, "" ) )
			{
				if ( strcmp( tAddrInfo.achE164, strE164 ) != 0 || strcmp( tAddrInfo.achEntryName, strEntryName ) != 0 )
				{
					bFind = FALSE;
				}
			}
			
			if ( bFind )
			{
				pTAliasEx = it;
				break;
			}
		}
		
		if ( pTAliasEx )
		{
			tAddrInfo.bOnLine = TRUE;
			//tAddrInfo.emAliasType = itfind->m_byType;
			tAddrInfo.m_emEndpointType = pTAliasEx->m_emEndpointType;
		}
		else
		{
			tAddrInfo.bOnLine = FALSE;
		}

		itShow->tAddrInfo = tAddrInfo;
		itShow->strNameLetter = strLetter;
	}

	Value_TouchListAddr val_ListAddrList( &m_vecLocalbookShowList, NULL, "", TRUE, FALSE, TRUE, FALSE );
	val_ListAddrList.m_strItemFunc = "CMeetTemplateLogic::OnClickAddrbookLstItem";
	val_ListAddrList.m_bAddIconShow = TRUE;
	if ( NULL != m_plsLocalAddrbook )
	{
		m_plsLocalAddrbook->SetData( val_ListAddrList );
	}
	m_plsLocalAddrbook->SetDragEnable( TRUE );
}

void CMeetTemplateLogic::OnBtnNew() 
{
	//判断模板个数达到上限无法新建
	if ( m_tpTmpRefreshList.Size() >= 128 )
	{
		s32 nRet = 0;
		MESSAGEWNDBOX( "会议模板个数达到上限，无法新建", this , nRet , FALSE );
		return;
	}
	
	m_emOperateFlag = em_NEW_PAGE_STATUS;

	m_tNewTemplate.Clear();
	s32 nIndex  = 0;
	for( nIndex = 0; nIndex < TP_CONF_MAX_MAIN_VIDEO_RES_NUM; nIndex++ )
	{
		m_tNewTemplate.m_atTpMainVideoRes[nIndex].Clear();
	}
	
	for( nIndex = 0; nIndex < TP_CONF_MAX_MINOR_VIDEO_RES_NUM; nIndex++ )
	{
		m_tNewTemplate.m_atTpMinorVideoRes[nIndex].Clear();			
	}

	m_tNewTemplate.m_wMainNum = 1;
	m_tNewTemplate.m_wMinorNum = 1;

	m_tNewTemplate.m_atTpMainVideoRes[0].m_emRes = emTPVHD1080p1920x1080;
	m_tNewTemplate.m_atTpMainVideoRes[0].m_wFrameRate = 60;
	m_tNewTemplate.m_atTpMainVideoRes[0].m_emQualityLvl = emTPH264HP;

	m_tNewTemplate.m_atTpMinorVideoRes[0].m_emRes = emTPVHD1080p1920x1080;
	m_tNewTemplate.m_atTpMinorVideoRes[0].m_wFrameRate = 60;
	m_tNewTemplate.m_atTpMinorVideoRes[0].m_emQualityLvl = emTPH264HP;

	::SendMessage( m_dlgMediaCfg, WM_DEF_SENDTMPINFOTOPAGE, (WPARAM)&m_tNewTemplate, (LPARAM)m_emOperateFlag );
	SetDiscussListPageToEditPage(m_tNewTemplate);

	if ( m_bSwitchPolling != m_tNewTemplate.m_tTurnList.m_bPollOn )
	{
		m_bSwitchPolling = m_tNewTemplate.m_tTurnList.m_bPollOn;
		m_btnSwitchPolling.SetSwitchState( !m_bSwitchPolling );
//		UpdatePollingUIState();
	}

	m_emCurFocus = em_Focus_Hour;

	m_mapEpList.clear();
	m_mapEpInfoList.clear();
	m_vecTurnList.clear();

	m_mapDiscussList.clear();
	m_mapDiscussSelItem.clear();

	m_btnAllAdd.EnableWindow(FALSE);
	m_btnCheckCur.EnableWindow(TRUE);
	m_btnCheckOrder.EnableWindow(TRUE);
	m_btnCheckOrder.SetCheck(TRUE);
	m_btnCheckCur.SetCheck(FALSE);
	m_etDateSet.SetWindowText("");
	m_etDateSet.EnableWindow(TRUE);
  	m_btnCalendar.EnableWindow(FALSE);
	m_btnCalendar.SetCheck( BST_UNCHECKED );
	m_btnPlusTime.EnableWindow(FALSE);
	m_btnSubTime.EnableWindow(FALSE);
	m_etSetHour.EnableWindow(FALSE);
	m_edtDotHour.EnableWindow(FALSE);
	m_etSetMin.EnableWindow(FALSE);

	m_btnAllSel.EnableWindow(FALSE);
	m_btnDelete.EnableWindow(FALSE);
	m_etDateSet.EnableWindow(FALSE);

	SetInitDataToNewPage();
	OnBtnMeetingInfo();
}

void CMeetTemplateLogic::OnBtnEdit() 
{
	m_emOperateFlag = em_EDIT_PAGE_STATUS;

    m_emCurFocus = em_Focus_Hour;

	m_dlgCalendar.ShowWindow(SW_HIDE);

	m_btnDelete.EnableWindow(FALSE);
	m_btnAllSel.EnableWindow(FALSE);

	CleanPageList();
	SetSelectedTmpDataToEditPage();

	m_etName.SetFocus();
}

void CMeetTemplateLogic::OnBtnCancel() 
{
	m_mapEpList.clear();
	m_mapEpInfoList.clear();
	m_vecTurnList.clear();
	m_etSearch.SetWindowText("");
	m_mapDiscussList.clear();
	m_mapDiscussSelItem.clear();

	//恢复媒体信息数据为原始数据
	TCMSConfTemplate tBaseTemplate = m_tBaseTemplate;
	if ( m_emOperateFlag == em_NEW_PAGE_STATUS )
	{
		s32 nIndex  = 0;
		for( nIndex = 0; nIndex < TP_CONF_MAX_MAIN_VIDEO_RES_NUM; nIndex++ )
		{
			m_tNewTemplate.m_atTpMainVideoRes[nIndex].Clear();
		}
		
		for( nIndex = 0; nIndex < TP_CONF_MAX_MINOR_VIDEO_RES_NUM; nIndex++ )
		{
			m_tNewTemplate.m_atTpMinorVideoRes[nIndex].Clear();			
		}
		
		m_tNewTemplate.m_wMainNum = 1;
		m_tNewTemplate.m_wMinorNum = 1;
		
		m_tNewTemplate.m_atTpMainVideoRes[0].m_emRes = emTPVHD1080p1920x1080;
		m_tNewTemplate.m_atTpMainVideoRes[0].m_wFrameRate = 60;
		m_tNewTemplate.m_atTpMainVideoRes[0].m_emQualityLvl = emTPH264HP;
		
		m_tNewTemplate.m_atTpMinorVideoRes[0].m_emRes = emTPVHD1080p1920x1080;
		m_tNewTemplate.m_atTpMinorVideoRes[0].m_wFrameRate = 60;
		m_tNewTemplate.m_atTpMinorVideoRes[0].m_emQualityLvl = emTPH264HP;

		m_tNewTemplate.m_emTpAudioFormat = emTPAMpegAACLD;
	}
	else if (m_emOperateFlag == em_EDIT_PAGE_STATUS )
	{
		m_tSelTemplate.m_wMainNum = tBaseTemplate.m_wMainNum;
		m_tSelTemplate.m_wMinorNum = tBaseTemplate.m_wMinorNum;
		
		s32 nIndex = 0;
		for ( nIndex = 0; nIndex < tBaseTemplate.m_wMainNum; nIndex++ )
		{
			m_tSelTemplate.m_atTpMainVideoRes[nIndex] = tBaseTemplate.m_atTpMainVideoRes[nIndex];	
		}
		
		for ( nIndex = 0; nIndex < tBaseTemplate.m_wMinorNum; nIndex++ )
		{
			m_tSelTemplate.m_atTpMinorVideoRes[nIndex] = tBaseTemplate.m_atTpMinorVideoRes[nIndex];	
		}

		m_tSelTemplate.m_emTpAudioFormat = tBaseTemplate.m_emTpAudioFormat;
	}

	u16 wResNum = CComInterface::GetNeedBasNum(m_tSelTemplate);
	UpdateResUsedCountToControl(wResNum);
	
	m_stTemplateRightTitle.SetWindowText("会议模板信息");
	m_emOperateFlag = em_SCANF_PAGE_STATUS;
	if( NULL != m_plsMeetTmp )
	{
		m_plsMeetTmp->EnableWindow(TRUE);
		m_pLetterTmp->EnableWindow(TRUE);
	}
	m_btnNewTmp.EnableWindow(TRUE);
	
	m_btnCancel.ShowWindow(SW_HIDE);
	m_btnEdit.ShowWindow(SW_SHOW);
	m_btnSave.ShowWindow(SW_HIDE);

	m_etSearch.EnableWindow(TRUE);

	CleanPageList();
	
	SetEpListPageToEditPage(m_tSelTemplate);
	SetTurnListPageToEditPage(m_tSelTemplate);
	SetDiscussListPageToEditPage(m_tSelTemplate);
	ShowPageScanf();

	CTime ctime(m_tSelTemplate.m_tStartTime);
	m_dlgCalendar.SetDate( ctime.GetYear(), ctime.GetMonth(), ctime.GetDay() );

	OnBtnMeetingInfo();
	UpdateUIState();
}

void CMeetTemplateLogic::OnBtnAllSelect() 
{
	m_bIsAllSel = !m_bIsAllSel;
	if ( m_plsMeetTmp->IsWindowVisible() )
	{
		m_setSelectedTmpIconItem.clear();
		if ( m_bIsAllSel )
		{
			for(s32 nIndex = 0; nIndex < m_tpTmpShowList.Size(); nIndex++ )
			{	
				CString strConfName = m_tpTmpShowList.GetAt(nIndex).m_achConfName;
				u16 nTemplateId = m_tpTmpShowList.GetAt(nIndex).m_wID;
				
				if ( !strConfName.IsEmpty() )
				{
					m_setSelectedTmpIconItem.insert(strConfName);
				}
			}
		}
		else
		{
			m_setSelectedTmpIconItem.clear();
		}
		UpdateTmpShowList();
		UpdateUIState();
	}
}

void CMeetTemplateLogic::OnBtnDelete() 
{
	s32 nRet = 0;
	MESSAGEWNDBOX( "是否删除所选模板信息", this , nRet , TRUE );
	
	if( nRet == IDOK )
	{
		if ( m_bIsAllSel )
		{
			CString strSearchName;
			m_etSearch.GetWindowText( strSearchName );
			if( strSearchName.IsEmpty() )
			{
				if ( NULL != m_tTmpConfigIF )
				{
					if( m_tTmpConfigIF->DelAllConfTempReq() != NO_ERROR )
					{
						MESSAGEWND( "删除全部模板请求发送失败" );
					}	
				}
				return;
			}	
		}
		
		for ( std::set<CString>::iterator iter = m_setSelectedTmpIconItem.begin(); iter != m_setSelectedTmpIconItem.end(); iter++ )
		{
			CString strClickedMeetTmpName = *iter;
			
			for( s32 nIndex = 0; nIndex < m_tpTmpRefreshList.Size(); nIndex++ )
			{
				if( m_tpTmpRefreshList.GetAt(nIndex).m_achConfName == strClickedMeetTmpName )
				{
					if( NULL != m_tTmpConfigIF )
					{
						if( m_tTmpConfigIF->DeleteConfTemplateReq( m_tpTmpRefreshList.GetAt(nIndex).m_wID ) != NO_ERROR )
						{
							MESSAGEWND( "删除模板请求发送失败"  );
						}
					}
				}
			}
		}		
	}
}

BOOL CMeetTemplateLogic::CheckTmpMeetInfo()
{
	m_tNewTemplate.Clear();
	CString strConfName;
	CString strConfE164;
	CString strDate;
	CString strHour;
	CString strMinute;
	CString strStartTime;
	m_etName.GetWindowText(strConfName);
	m_etNumber.GetWindowText(strConfE164);
	
	CString strError;
	int nRet = 0;
	if ( strConfName.IsEmpty() )
	{
		strError = "会议模板名称不能为空";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return FALSE;
	}

	if( CCallAddr::IsValidE164(strConfName) )
	{
		strError = "名称不可以全部为数字或[*#,]组合";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return FALSE;		
	}
	
	if ( !CUmcwebCommon::IsValidTPStr( strConfName ) )
    { 
		strError.Format("会议名不可以包含空格及括号中的任意字符 [ %s ]",INVALID_ALIAS_FOR_SHOW)  ;
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return FALSE;
	}
	
	for( s32 xIndex = 0; xIndex < m_tpTmpRefreshList.Size(); xIndex++ )
	{
		CString strCurTmpName;
		if( m_emOperateFlag == em_NEW_PAGE_STATUS )
		{
			if( m_tpTmpRefreshList.GetAt(xIndex).m_achConfName == strConfName )
			{
				strError = "模板名称重复";
				MESSAGEWNDBOX( strError, this , nRet , FALSE );
				return FALSE;
			}
		}
		else if ( m_emOperateFlag == em_EDIT_PAGE_STATUS)
		{
			strCurTmpName = m_tSelTemplate.m_achConfName;
			if( (m_tpTmpRefreshList.GetAt(xIndex).m_achConfName == strConfName) && ( strConfName != strCurTmpName ) )
			{
				strError = "模板名称重复";
				MESSAGEWNDBOX( strError, this , nRet , FALSE );
				return FALSE;
			}
		}
	}

	for( s32 yIndex = 0; yIndex < m_tpTmpRefreshList.Size(); yIndex++ )
	{
		CString strCurTmpE164;
		if ( m_emOperateFlag == em_EDIT_PAGE_STATUS)
		{
			strCurTmpE164 = m_tSelTemplate.m_achConfE164;
		}
		
		if( !strConfE164.IsEmpty() )
		{
			if( !CCallAddr::IsValidE164(strConfE164) )
			{
				strError = "号码必须全部为数字或[*#,]组合";
				MESSAGEWNDBOX( strError, this , nRet , FALSE );
				return FALSE;
			}
			
			if( (m_tpTmpRefreshList.GetAt(yIndex).m_achConfE164 == strConfE164) && ( strConfE164 != strCurTmpE164 ) )
			{
				strError = "模板号码重复";
				MESSAGEWNDBOX( strError, this , nRet , FALSE );
				return FALSE;
			}
		}
	}
	
	s8* pConfName = (s8*)(LPCTSTR)strConfName;
	s8* pConfE164 = (s8*)(LPCTSTR)strConfE164;
	
	sprintf( m_tNewTemplate.m_achConfName, "%s", pConfName );
	sprintf( m_tNewTemplate.m_achConfE164, "%s", pConfE164 );
	
	if( m_btnCheckOrder.GetCheck() )
	{
		m_tNewTemplate.m_tStartTime=0;
	}
	else
	{
		m_etDateSet.GetWindowText(strDate);
		m_etSetHour.GetWindowText(strHour);
		m_etSetMin.GetWindowText(strMinute);
		
		if ( atoi(strHour) > 23 || atoi(strHour) < 0 || strHour.IsEmpty() )
		{
			strError = "小时为 0 ~ 23 间的整数";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			return FALSE;
		}
		
		if ( atoi(strMinute) > 59 || atoi(strMinute) < 0 || strMinute.IsEmpty() )
        {
			strError = "分钟为 0 ~ 59 间的整数";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
            return FALSE;
        }
		
		//预约会议时间设置
		CString strStartTime;
		m_etDateSet.GetWindowText(strStartTime);
		
		s32 nYear = 0, nMonth = 0, nDay = 0;
		if ( !strStartTime.IsEmpty() )
		{
			sscanf( strStartTime, "%d年%d月%d日", &nYear, &nMonth, &nDay );   
		}
		else
		{
			strError = "请选择合理的预约会议时间";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			return FALSE;
		}
		
		SYSTEMTIME syStartTime;
		syStartTime.wYear = nYear;
		syStartTime.wMonth = nMonth;
		syStartTime.wDay = nDay;
		syStartTime.wHour = atoi(strHour);
		syStartTime.wMinute = atoi(strMinute);
		syStartTime.wSecond = 0;

		CTime starttime(syStartTime);
		//需求修改：预约会议开始和结束的时间范围为：2000年1月1日8点~2037年12月31日24点  -- 20140701 by xhx
		CTime limittime = CTime( 2000, 1, 1, 8, 0, 0, -1 );

		if ( nYear > 2037 || nYear < 2000 || starttime < limittime )
		{
			strError = "无法预约当前日期，请修改日期";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			return FALSE;
		}

// 		SYSTEMTIME sysCurTime;
// 		::GetLocalTime( &sysCurTime ); 
// 
// 		COleDateTime dStartTime(syStartTime); 
// 		COleDateTime dCurTime(sysCurTime); 
// 		COleDateTimeSpan dTimeSpan = dStartTime - dCurTime; 
// 		s32 nSecondSpan = dTimeSpan.GetTotalSeconds();
		
		if ( starttime < CTime::GetCurrentTime() )
//		if ( nSecondSpan < 0 )
		{
			strError = "请在当前时间之后创建会议";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			return FALSE;
		}

		m_tNewTemplate.m_tStartTime = starttime.GetTime();
 	}

	//检测会议码率、演示码率
	CString strConfRate;
	m_etConfRate.GetWindowText(strConfRate);
	CString strShowRate;
	m_etShowRate.GetWindowText(strShowRate);
	u16 wConfRate = atoi(strConfRate);
	u16 wShowRate = atoi(strShowRate);
	u16 wConfRateExtra = wConfRate % 64;
	u16 wShowRateExtra = wShowRate % 64;

	if ( ( 0 == wConfRate ) /*|| ( 0 == wShowRate )*/ || ( wConfRateExtra != 0 && wConfRate <= 8192 ) || ( wShowRateExtra != 0 && wShowRate <= 8192 ) )
	{
		strError = "码率必须为64的倍数";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );

		CString strRateShow;

		if ( wConfRateExtra != 0 )
		{
			if ( wConfRateExtra <= 32 )
			{
				wConfRate -= wConfRateExtra;
			} 
			else
			{
				wConfRate += 64 - wConfRateExtra;
			}

			strRateShow.Format( "%d", wConfRate );
			m_etConfRate.SetWindowText(strRateShow);
		}

		if ( wShowRateExtra != 0 )
		{
			if ( wShowRateExtra <= 32 )
			{
				wShowRate -= wShowRateExtra;
			} 
			else
			{
				wShowRate += 64 - wShowRateExtra;
			}

			strRateShow.Format( "%d", wShowRate );
			m_etShowRate.SetWindowText(strRateShow);
		}

		if ( 0 == wConfRate )
		{			
			wConfRate = 64;			
			strRateShow.Format( "%d", wConfRate );
			m_etConfRate.SetWindowText(strRateShow);
		}
		
// 		if ( 0 == wShowRate )
// 		{			
// 			wShowRate = 0/*64*/;
// 			strRateShow.Format( "%d", wShowRate );
// 			m_etShowRate.SetWindowText(strRateShow);
// 		}

		return FALSE;
	} 

	if ( wConfRate + wShowRate > 8192 )
	{
		strError = "单屏码率+演示码率必须小于等于8192Kbps";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return FALSE;
	}

	m_tNewTemplate.m_wConfBitRate = wConfRate;
	m_tNewTemplate.m_wBpConfBitRate = wConfRate;

	m_tNewTemplate.m_wHpDualBitRate = wShowRate;
	m_tNewTemplate.m_wBpDualBitRate = wShowRate;

	//检测媒体信息数据合法性
	TCMSConfTemplate* pTemplate =  m_dlgMediaCfg.GetSelTemplate();
	if ( NULL != pTemplate )
	{
		m_tNewTemplate.m_wMainNum = pTemplate->m_wMainNum;
		m_tNewTemplate.m_wMinorNum = pTemplate->m_wMinorNum;
		
		s32 nIndex = 0;
		for ( nIndex = 0; nIndex < pTemplate->m_wMainNum; nIndex++ )
		{
			m_tNewTemplate.m_atTpMainVideoRes[nIndex] = pTemplate->m_atTpMainVideoRes[nIndex];	
		}
		
		for ( nIndex = 0; nIndex < pTemplate->m_wMinorNum; nIndex++ )
		{
			m_tNewTemplate.m_atTpMinorVideoRes[nIndex] = pTemplate->m_atTpMinorVideoRes[nIndex];	
		}

		m_tNewTemplate.m_emTpAudioFormat = pTemplate->m_emTpAudioFormat;
	}

	if( m_tNewTemplate.m_wMainNum < 1 )
	{
		strError = "媒体信息的会议格式类型未选择";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return FALSE;
	}
	else if( m_tNewTemplate.m_wMinorNum < 1 )
	{
		strError = "媒体信息的演示格式类型未选择";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return FALSE;
	}


	//检测媒体资源数大于选中资源数
	s32 nResCount = m_dlgMediaCfg.GetCheckResNum();
	if( nResCount > m_wResUsedCount)
	{
		strError = "媒体资源数不足，请重新选择媒体格式";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return FALSE;
	}


	CString strHomeCns;
	m_etHomeMeeting.GetWindowText(strHomeCns);
	
	if( !CheckIsInputHomeMeeting() )
	{
		return FALSE;
	}
	
	CString strPollingInterver;
	m_etPollingTime.GetWindowText(strPollingInterver);
	u16 nPollingInterver = atoi(LPCTSTR(strPollingInterver));
	
	if ( strPollingInterver.IsEmpty() )
	{
		strError = "轮询时间间隔不能为空";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return FALSE; 
	}
	else if ( nPollingInterver < 5  || nPollingInterver > 7200 )
	{
		strError = "轮询间隔应是 5 ~ 7200 之间的整数";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return FALSE; 
	}

	//会议讨论开启时，讨论的会场最少为1个，最多为4个
	u16 wSize = 0;
	std::map<u16, CString>::iterator iterDiscussSelItem;
	for ( iterDiscussSelItem = m_mapDiscussSelItem.begin(); iterDiscussSelItem != m_mapDiscussSelItem.end(); iterDiscussSelItem++ )
	{
		CString strDiscussName = iterDiscussSelItem->second;
		if ( strcmp( strDiscussName, "" ) != 0 )
		{
			wSize++;
		}
	}

	if ( m_bSwitchDiscuss && wSize < 1 )
	{
		strError = "未选择参与讨论的会场";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return FALSE;
	}
	
	return TRUE;
}

BOOL CMeetTemplateLogic::CheckIsInputHomeMeeting()
{
	CString strHomeCns;
	m_etHomeMeeting.GetWindowText(strHomeCns);
	
	CString strError;
	int nRet = 0;
	if ( strHomeCns.IsEmpty() )
	{
		strError = "主会场名称不能为空";
		MESSAGEWNDBOX( strError, this , nRet , FALSE );
		return FALSE;
	}
	else
	{
// 		if( HomeMeetExistInEpList(strHomeCns) )
// 		{
// 			return FALSE;
// 		}

		std::map<u16,TEpAddr>::iterator iter = m_mapEpInfoList.begin();
		CString strHomeName = iter->second.m_tAlias.m_abyAlias;
		CString strHomeNum = iter->second.m_tE164.m_abyAlias;
		if ( TP_CONF_MAX_EPNUM != FindMeetInEpList(strHomeName, strHomeNum, TRUE) )
		{
			return FALSE;
		}
	}
	
	return TRUE;
}

void CMeetTemplateLogic::OnBtnSave() 
{
	if( !CheckTmpMeetInfo() )
	{
		return;
	}

	//主会场  名字和id即行号
	m_tNewTemplate.m_wDefaultChairMan = 0; //目前暂设置主席id为0
 	if ( m_tNewTemplate.m_wDefaultChairMan == INVALID_WORD )
	{
        m_tNewTemplate.m_wDefaultChairMan = 0; 
	}

// 	CString strHomeCns;
// 	m_etHomeMeeting.GetWindowText(strHomeCns);
// 	if ( !strHomeCns.IsEmpty() )
// 	{
// 		m_tNewTemplate.m_wDefaultChairMan = 0; //目前暂设置主席id为0
// 		//添加主席
// 		m_tNewTemplate.m_atEpList.m_wNum = 0; //存储自定义会场id
// 
// 		EmTpAliasType emAliasType;
// 		if( CCallAddr::IsValidE164(strHomeCns) )
// 		{
// 			emAliasType = tp_Alias_e164;	
// 		}
// 		else
// 		{
// 			emAliasType = tp_Alias_h323;
// 		}
// 
// 		EmConfAddEpRet emAddFlag;
// 		emAddFlag = m_tNewTemplate.m_atEpList.Add( emAliasType, (s8*)(LPCTSTR)strHomeCns );
// 	}
// 
// 	//会场列表添加
// 	u16 nCurGroupItem = 0;
// 	std::map<u16,CString>::iterator iterEpList;
// 	for ( iterEpList = m_mapEpList.begin(); iterEpList != m_mapEpList.end(); iterEpList++ )
// 	{
// 	 	LPCTSTR strEpName;
//  		strEpName = (LPCTSTR)iterEpList->second;
// 
// 		u16 nEpId = iterEpList->first;
// 
// 		EmTpAliasType emAliasType;
// 		if( CCallAddr::IsValidE164(strEpName) )
// 		{
// 			emAliasType = tp_Alias_e164;	
// 		}
// 		else
// 		{
// 			emAliasType = tp_Alias_h323;
// 		}
// 
// 		EmConfAddEpRet emAddFlag;
// 		emAddFlag = m_tNewTemplate.m_atEpList.Add( emAliasType, (s8*)strEpName );
// 
// 	 	nCurGroupItem++;
// 	}

	std::map<u16,TEpAddr>::iterator iterEpInfo;
	for ( iterEpInfo = m_mapEpInfoList.begin(); iterEpInfo != m_mapEpInfoList.end(); iterEpInfo++ )
	{
		TEpAddr tEpAddr = iterEpInfo->second;		
		EmConfAddEpRet emAddFlag;
		emAddFlag = m_tNewTemplate.m_atEpList.Add( tEpAddr.m_tAlias.m_abyAlias, tEpAddr.m_tE164.m_abyAlias );
		if ( TP_ConfAddEpRet_AliasReapeat == emAddFlag )
		{
			s32 nRet = 0;
			CString strErr;
			if ( strlen(tEpAddr.m_tAlias.m_abyAlias) == 0 )
			{
				strErr.Format( "分会场中存在重复会场，会场号码：%s", tEpAddr.m_tE164.m_abyAlias );
			}
			else if ( strlen(tEpAddr.m_tE164.m_abyAlias) == 0 )
			{
				strErr.Format( "分会场中存在重复会场，会场名称：%s", tEpAddr.m_tAlias.m_abyAlias );
			}
			else
			{
				strErr.Format( "分会场中存在重复会场，会场名称：%s，会场号码：%s", tEpAddr.m_tAlias.m_abyAlias, tEpAddr.m_tE164.m_abyAlias );
			}
            MESSAGEWNDBOX( strErr, this , nRet, FALSE );
			return;
		}
	}

	//会议讨论
	m_tNewTemplate.m_atAuxMixList.Clear();
	m_tNewTemplate.m_atAuxMixList.m_bAudMixOn = m_bSwitchDiscuss;

	std::map<u16,CString>::iterator iterDiscussSelItem;
	u16 wDiscussIndex = TP_INVALID_INDEX;
	for ( iterDiscussSelItem = m_mapDiscussSelItem.begin(); iterDiscussSelItem != m_mapDiscussSelItem.end(); iterDiscussSelItem++ )
	{
		u16 wIndex = iterDiscussSelItem->first;
		CString strDiscussName = iterDiscussSelItem->second;

		u16 wDiscussId = FindConfDiscussListByAlias(strDiscussName);
		if ( INVALID_WORD != wDiscussId )
		{
			m_tNewTemplate.m_atAuxMixList.m_awList[wIndex] = wDiscussId;
			if ( wDiscussIndex > wIndex )
			{
				wDiscussIndex = wIndex;
			}
		}	
	}

	m_tNewTemplate.m_atAuxMixList.m_wSpeakerIndex = wDiscussIndex;

	//轮询列表添加
	CString strPollingInterver;
	m_etPollingTime.GetWindowText(strPollingInterver);
	u16 nPollingInterver = atoi(LPCTSTR(strPollingInterver));
 	m_tNewTemplate.m_tTurnList.m_wNum = m_vecTurnList.size();
	m_tNewTemplate.m_tTurnList.m_bPollOn = m_bSwitchPolling;
	m_tNewTemplate.m_tTurnList.SetInterval(nPollingInterver);
	std::vector<CString>::iterator iterTurnList;
	u16 nCurTurnList = 0;
	for ( iterTurnList = m_vecTurnList.begin(); iterTurnList != m_vecTurnList.end(); iterTurnList++ )
	{
		CString strPollingName = *iterTurnList;

		u16 nTurnId;
 		nTurnId = FindConfTurnListByAlias(strPollingName);

		m_tNewTemplate.m_tTurnList.m_awList[nCurTurnList] = nTurnId; //存储自定义会场id
		++nCurTurnList;
	}

	if( m_emOperateFlag == em_EDIT_PAGE_STATUS )
	{
		m_tNewTemplate.m_wID = m_tSelTemplate.m_wID;
		u16 uErrNo = m_tTmpConfigIF->ModifyConfTemplateReq(m_tNewTemplate);
		if( uErrNo != NO_ERROR )
		{
			MESSAGEWND( "修改模板请求失败" );
		}
	}
	else if( m_emOperateFlag == em_NEW_PAGE_STATUS )
	{
		u16 uErrNo = m_tTmpConfigIF->AddConfTemplateReq(m_tNewTemplate);
		if( uErrNo != NO_ERROR )
		{
			MESSAGEWND( "添加模板请求失败" );
		}
	}
	m_tSelTemplate = m_tNewTemplate;

	m_emOperateFlag = em_SCANF_PAGE_STATUS;
	OnBtnMeetingInfo();
	m_etSearch.SetWindowText("");

	m_plsMeetTmp->SetSelItem(-1);
	m_plsMeetEpRight->SetSelItem(-1);
	m_plsMeetPollingRight->SetSelItem(-1);
}

void CMeetTemplateLogic::OnBtnMeetingInfo() 
{
	m_emTabFlag = em_MEETINFO_PAGE;
	
	m_btnMeetingInfo.EnableWindow(FALSE);
	m_btnGroupInfo.EnableWindow(TRUE);
	m_btnPollingInfo.EnableWindow(TRUE);
	m_btnDiscussInfo.EnableWindow(TRUE);

	switch( m_emOperateFlag )
	{
	case em_SCANF_PAGE_STATUS:
		{
			ShowPageScanf();
			m_etSearch.EnableWindow(TRUE);
		}
		break;
	case em_NEW_PAGE_STATUS:
		{
			ShowPageNew();
		}
		break;;
	case em_EDIT_PAGE_STATUS:
		{
			ShowPageEdit();
		}
		break;
	default:
		{
		}
		break;
	}
	m_etName.SetFocus();
	return;
}

void CMeetTemplateLogic::OnBtnEpInfo() 
{
	m_emTabFlag = em_Ep_PAGE;

	m_btnMeetingInfo.EnableWindow(TRUE);
	m_btnGroupInfo.EnableWindow(FALSE);
	m_btnPollingInfo.EnableWindow(TRUE);
	m_btnDiscussInfo.EnableWindow(TRUE);

	switch( m_emOperateFlag )
	{
	case em_SCANF_PAGE_STATUS:
		{
			ShowPageScanf();
			m_etSearch.EnableWindow(TRUE);
		}
		break;
	case em_NEW_PAGE_STATUS:
		{
			ShowPageNew();
		}
		break;;
	case em_EDIT_PAGE_STATUS:
		{
			ShowPageEdit();
		}
		break;
	default:
		{
		}
		break;
	}

	CString strHomeCns;
	m_etHomeMeeting.GetWindowText(strHomeCns);
	if ( strHomeCns.IsEmpty() )
	{
		m_etHomeMeeting.SetFocus();
	}
	else
	{
		m_plsMeetEpRight->SetFocus();
	}

	return;
}

void CMeetTemplateLogic::OnBtnPollingInfo() 
{
	m_emTabFlag = em_POLLING_PAGE;

	m_btnMeetingInfo.EnableWindow(TRUE);
	m_btnGroupInfo.EnableWindow(TRUE);
	m_btnPollingInfo.EnableWindow(FALSE);
	m_btnDiscussInfo.EnableWindow(TRUE);

	switch( m_emOperateFlag )
	{
	case em_SCANF_PAGE_STATUS:
		{
			ShowPageScanf();
			m_etSearch.EnableWindow(TRUE);
		}
		break;
	case em_NEW_PAGE_STATUS:
		{
			ShowPageNew();
		}
		break;;
	case em_EDIT_PAGE_STATUS:
		{
			ShowPageEdit();
		}
		break;
	default:
		{
		}
		break;
	}
	m_etPollingTime.SetFocus();
	return;
}

void CMeetTemplateLogic::OnBtnDiscussInfo() 
{
	m_emTabFlag = em_DISCUSS_PAGE;

	m_btnMeetingInfo.EnableWindow(TRUE);
	m_btnGroupInfo.EnableWindow(TRUE);
	m_btnPollingInfo.EnableWindow(TRUE);
	m_btnDiscussInfo.EnableWindow(FALSE);
	
	switch( m_emOperateFlag )
	{
	case em_SCANF_PAGE_STATUS:
		{
			ShowPageScanf();
			m_etSearch.EnableWindow(TRUE);
		}
		break;
	case em_NEW_PAGE_STATUS:
		{
			ShowPageNew();
		}
		break;;
	case em_EDIT_PAGE_STATUS:
		{
			ShowPageEdit();
		}
		break;
	default:
		{
		}
		break;
	}
}

void CMeetTemplateLogic::CleanSearchList()
{
	//优化地址簿条目过多时，切换页面卡
	CString strSearchName;
	m_etSearch.GetWindowText( strSearchName );
	if( strSearchName.IsEmpty() )
	{
		return;
	}

 	m_etSearch.SetWindowText("");    //三个页面公用查询框   只要发生切换  查询框清空 各列表数据重置
	UpdateTmpShowList();             //切换 清空 Edit有变化 刷新
	UpdateUIState();
	UpdateAddrbookShowList();
	UpdatePollingLeftShowList( m_mapEpList,  TRUE );
	UpdateDiscussShowListData();
	UpdateDiscussLeftShowList( m_mapDiscussList,  TRUE );
}

CString CMeetTemplateLogic::FindConfTurnListById(u16 nId)
{
	for ( std::map<u16,CString>::iterator iter = m_mapEpList.begin(); iter != m_mapEpList.end(); iter++ )
	{
		u16 nTurnId = iter->first;
		
		if( nTurnId == nId ) 
		{
			return iter->second;
		}
	}			
	
	return "";
}

u16 CMeetTemplateLogic::FindConfTurnListByAlias(CString strTurnListName)
{
//	TEpAddrList  tCnsLst;
	for ( std::map<u16,CString>::iterator iter = m_mapEpList.begin(); iter != m_mapEpList.end(); iter++ )
	{
		LPCTSTR strEpName = iter->second;
		if( strEpName == strTurnListName ) 
		{
			return iter->first;
		}
	}			
	
	return INVALID_WORD;
}

CString CMeetTemplateLogic::FindConfDiscussListById(u16 nId)
{
	std::map<u16,CString>::iterator iter = m_mapDiscussList.begin();
	u16 nDiscussId = iter->first;
	//Bug00184859 -- 20140626 by xhx
	if ( 0 != nDiscussId || m_mapDiscussList.empty() )
	{
		//更新会议讨论列表(主会场+分会场)
		m_mapDiscussList.clear();
		m_mapDiscussList = m_mapEpList;
		
		CString strHomeCns;
		if ( em_SCANF_PAGE_STATUS == m_emOperateFlag )
		{
			m_stHomeMeeting.GetWindowText(strHomeCns);
		}
		else
		{
			m_etHomeMeeting.GetWindowText(strHomeCns);
		}
		
		if ( !strHomeCns.IsEmpty() )
		{
			EnterCriticalSection(&g_csLock);
			std::map<u16,CString>::iterator iter;
			iter = find_if( m_mapDiscussList.begin(), m_mapDiscussList.end(), bind2nd( ptr_fun(CUmcwebCommon::MapValueCompare), strHomeCns ) );
			if ( iter == m_mapDiscussList.end() )
			{
				m_mapDiscussList.insert( std::make_pair<u16,CString>( 0, strHomeCns ) );
			}
			LeaveCriticalSection(&g_csLock);
		}
	}

	for ( iter = m_mapDiscussList.begin(); iter != m_mapDiscussList.end(); iter++ )
	{
		nDiscussId = iter->first;
		
		if( nDiscussId == nId ) 
		{
			return iter->second;
		}
	}
	
	return "";
}

u16  CMeetTemplateLogic::FindConfDiscussListByAlias(CString strDiscussListName)
{
//	TEpAddrList  tCnsLst;
	for ( std::map<u16,CString>::iterator iter = m_mapDiscussList.begin(); iter != m_mapDiscussList.end(); iter++ )
	{
		LPCTSTR strEpName = iter->second;
		if( strEpName == strDiscussListName ) 
		{
			return iter->first;
		}
	}			
	
	return INVALID_WORD;
}

void CMeetTemplateLogic::OnBtnPlusTime() 
{
	switch ( m_emCurFocus )
    {
    case em_Focus_Hour:
		{
			CUmcwebCommon::PlusHourBtn(&m_etSetHour);
		}
        break;
		
    case em_Focus_Minute:
		{
			CUmcwebCommon::PlusMinBtn(&m_etSetMin);
		}
        break;
    }
}

void CMeetTemplateLogic::OnBtnSubTime() 
{
	switch ( m_emCurFocus )
    {
    case em_Focus_Hour:
		{
			CUmcwebCommon::SubHourBtn(&m_etSetHour);
		}
        break;
        
    case em_Focus_Minute:  
		{
			CUmcwebCommon::SubSecBtn(&m_etSetMin);
		}
        break;
    }
}

void CMeetTemplateLogic::OnBtnSubConfRate()
{	
	CString strRate;
	m_etConfRate.GetWindowText(strRate);
	
	s32 nRate = atoi(strRate);
	if( nRate <= 64 )
	{
        nRate = 64;		
	}
	else
	{
		u16 wRateMultiple = nRate / 1024;
		u16 wRateExtra = nRate % 1024;
		if ( 0 == wRateExtra )
		{
			nRate = 1024 * ( wRateMultiple - 1);//nRate - 1024;	
		}
		else
		{
			nRate = 1024 * wRateMultiple;
		}
        
		if( nRate <= 64 )
		{
			nRate = 64;		
		}
	}

	strRate.Empty();
	strRate.Format( "%d", nRate );
	m_etConfRate.SetWindowText(strRate);
}

void CMeetTemplateLogic::OnBtnPlusConfRate()
{
	CString strRate;
	m_etConfRate.GetWindowText(strRate);
	
	s32 nRate = atoi(strRate);
	if( nRate >= 8192 )
	{
        nRate = 8192;		
	}
	else
	{
		u16 wRateMultiple = nRate / 1024;
        nRate = 1024 * ( wRateMultiple + 1);//nRate + 1024;
		if( nRate >= 8192 )
		{
			nRate = 8192;		
		}
	}
	
	strRate.Empty();
	strRate.Format( "%d", nRate );
	m_etConfRate.SetWindowText(strRate);
}

void CMeetTemplateLogic::OnBtnSubShowRate()
{
	CString strRate;
	m_etShowRate.GetWindowText(strRate);
	
	s32 nRate = atoi(strRate);
	if( nRate <= 0/*64*/ )
	{
        nRate = 0/*64*/;		
	}
	else
	{
		u16 wRateMultiple = nRate / 1024;
		u16 wRateExtra = nRate % 1024;
		if ( 0 == wRateExtra )
		{
			nRate = 1024 * ( wRateMultiple - 1);//nRate - 1024;	
		}
		else
		{
			nRate = 1024 * wRateMultiple;
		}

		if( nRate <= 0/*64*/ )
		{
			nRate = 0/*64*/;		
		}
	}
	
	strRate.Empty();
	strRate.Format( "%d", nRate );
	m_etShowRate.SetWindowText(strRate);
}

void CMeetTemplateLogic::OnBtnPlusShowRate()
{
	CString strRate;
	m_etShowRate.GetWindowText(strRate);
	
	s32 nRate = atoi(strRate);
	if( nRate >= 8192 )
	{
        nRate = 8192;		
	}
	else
	{
		u16 wRateMultiple = nRate / 1024;
        nRate = 1024 * ( wRateMultiple + 1);//nRate + 1024;
		if( nRate >= 8192 )
		{
			nRate = 8192;		
		}
	}
	
	strRate.Empty();
	strRate.Format( "%d", nRate );
	m_etShowRate.SetWindowText(strRate);
}

void CMeetTemplateLogic::OnBtnSubPollingTime()
{
	CString strTime;
	m_etPollingTime.GetWindowText(strTime);
	
	s32 nTime = atoi(strTime);
	
	if( nTime <= 5 )
	{
        nTime = 5;		
	}
	else
	{
        nTime = nTime - 5;
		if( nTime <= 5 )
		{
			nTime = 5;		
		}
	}
	
	strTime.Empty();
	strTime.Format( "%d", nTime );
	m_etPollingTime.SetWindowText(strTime);
}

void CMeetTemplateLogic::OnBtnPlusPollingTime()
{
	CString strTime;
	m_etPollingTime.GetWindowText(strTime);
	
	s32 nTime = atoi(strTime);
	if( nTime >= 7200 )
	{
        nTime = 7200;		
	}
	else
	{
        nTime = nTime + 5;
		if( nTime >= 7200 )
		{
			nTime = 7200;		
		}
	}
	
	strTime.Empty();
	strTime.Format( "%d", nTime );
	m_etPollingTime.SetWindowText(strTime);
}

LRESULT CMeetTemplateLogic::OnClickSwitchBtn(WPARAM wParam, LPARAM lParam) 
{
	m_bSwitchPolling = !m_btnSwitchPolling.GetSwitchState();

//	UpdatePollingUIState();
	return 0L;
}

LRESULT CMeetTemplateLogic::UpdateGroupEpList( WPARAM wParam, LPARAM lParam )
{
// 	BOOL bIsShowIcon = wParam;
// 	//会场列表
// 	TEpAddrList  tCnsLst;
// 	for ( std::map<u16,CString>::iterator iter = m_mapEpList.begin(); iter != m_mapEpList.end(); iter++ )
// 	{
// 		LPCTSTR strEpName = iter->second;
// 
// 		EmTpAliasType emAliasType;
// 		if( CCallAddr::IsValidE164(strEpName) )
// 		{
// 			emAliasType = tp_Alias_e164;	
// 		}
// 		else
// 		{
// 			emAliasType = tp_Alias_h323;
// 		}
// 
// 		tCnsLst.Add(emAliasType, (s8*)strEpName);
// 	}
// 	
// 	Value_TouchListTempCns val_TempCns( tCnsLst );
// 	
// 	val_TempCns.m_nImageId = IDR_PNG_LIST_DEL;
// 	if ( !bIsShowIcon )
// 	{
// 		val_TempCns.m_nImageId = 0;
// 	}
// 	val_TempCns.m_strClickItemFunc = "CMeetTemplateLogic::OnClickGroupPageDelItem";	
// 	m_plsMeetEpRight->SetData( val_TempCns );

	//经yjj确认，分会场同时显示名称和e164号 -- 20141023 by xhx
	BOOL bIsShowIcon = wParam;
	//会场列表
	vector<TAddrItem> vctAddrLst;
	TAddrItem tAddrItem;
	tAddrItem.emItemType = emEntryItem;
	for ( std::map<u16,TEpAddr>::iterator iter = m_mapEpInfoList.begin(); iter != m_mapEpInfoList.end(); iter++ )
	{
		u16 nPollingNum = iter->first;
		TEpAddr tEpAddr = iter->second;

		if ( 0 == nPollingNum )
		{
			continue;
		}
		
		TAddrInfo tAddrInfo;
		tAddrInfo.dwEntryIdx = nPollingNum - 1;

		strncpy( tAddrInfo.achEntryName, tEpAddr.m_tAlias.m_abyAlias, TP_MAX_ALIAS_LEN_CNC+1 );
		strncpy( tAddrInfo.achE164, tEpAddr.m_tE164.m_abyAlias, TP_MAX_ALIAS_LEN_CNC+1 );

		tAddrItem.tAddrInfo = tAddrInfo;
		tAddrItem.strImg = "AddrEditUnSelItem";
		vctAddrLst.push_back( tAddrItem );
	}

	ARRAY<String> vctSubItem;
	vctSubItem.push_back( "AddrDelItem" );
	Value_TouchListAddr val_TempAddr( &vctAddrLst, &vctSubItem, "", FALSE );
	if ( bIsShowIcon )
	{
		val_TempAddr.m_strItemFunc = "CMeetTemplateLogic::OnClickGroupPageDelItem";
		val_TempAddr.m_bAddrEditDlg = TRUE;
	}
 	else
 	{
		val_TempAddr.m_bAddIconShow = TRUE;
	}
	m_plsMeetEpRight->SetData(val_TempAddr);

	UpdatePollingLeftShowList( m_mapEpList, wParam );
	UpdateDiscussShowListData();
	UpdateDiscussLeftShowList( m_mapDiscussList,  wParam );

	return 0L;
}

LRESULT CMeetTemplateLogic::UpdatePollingList( WPARAM wParam, LPARAM lParam )
{
	m_tNewTemplate.m_tTurnList.Clear();

// 	if ( !m_bSwitchPolling )
// 	{
// 		return 0L;
// 	}

	TCMSConfTemplate tCnsTemplate;
	s32 nTurnListCount = m_vecTurnList.size();
	//轮询列表
	for ( std::vector<CString>::iterator iter = m_vecTurnList.begin(); iter != m_vecTurnList.end(); iter++ )
	{
		CString strPollingName = *iter;
		u16 nPollingId = FindConfTurnListByAlias(strPollingName);	
		tCnsTemplate.AddPollCns(nPollingId);
	}

	//会场列表
	for ( std::map<u16,CString>::iterator iterEp = m_mapEpList.begin(); iterEp != m_mapEpList.end(); iterEp++ )
	{
		LPCTSTR strEpName = iterEp->second;

		EmTpAliasType emAliasType;
		if( CCallAddr::IsValidE164(strEpName) )
		{
			emAliasType = tp_Alias_e164;	
		}
		else
		{
			emAliasType = tp_Alias_h323;
		}

		tCnsTemplate.AddConfEp(tp_Alias_h323, (s8*)strEpName);
	}

	Value_TouchListTempPoll val_TempPoll( tCnsTemplate );
	BOOL bIsShowIcon = FALSE;
	if ( m_emOperateFlag == em_SCANF_PAGE_STATUS )
	{
		bIsShowIcon = FALSE;
	}
	else
	{
		bIsShowIcon = TRUE;
	}
	val_TempPoll.m_bAddIconShow = bIsShowIcon;
	val_TempPoll.m_strClickItemFunc = "CMeetTemplateLogic::OnClickPollingPageDelItem";
	if ( NULL != m_plsMeetPollingRight )
	{
		m_plsMeetPollingRight->SetData( val_TempPoll );
	}

	if ( m_emTabFlag == em_POLLING_PAGE)
	{
		if( m_vecTurnList.size() > 0 )
		{
			ShowSortControl(TRUE);
		}
		else
		{
			ShowSortControl(FALSE);
		}
	}

	return 0L;
}

bool CMeetTemplateLogic::OnClickTmpLstItem( const IArgs & arg )
{	
	m_btnStartConf.EnableWindow(TRUE);
	CleanPageList();
	m_mapEpList.clear();
	m_mapEpInfoList.clear();
	m_vecTurnList.clear();
	m_mapDiscussList.clear();
	m_mapDiscussSelItem.clear();
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
        
		if ( const Data_ConfTemp *pItemInfo = dynamic_cast<const Data_ConfTemp*>( pBaseItem->GetUserData() )) 
		{   
			m_emOperateFlag = em_SCANF_PAGE_STATUS;
			m_tSelTemplate = pItemInfo->m_tConfTemp;

			m_tBaseTemplate = pItemInfo->m_tConfTemp;    //媒体信息缓存主、辅视频格式类型

			SetSelectedTmpDataToScanfPage(m_tSelTemplate);

			OnBtnMeetingInfo();
			m_plsMeetTmp->SetFocus();

		}
    }

	return true;
}

bool CMeetTemplateLogic::OnClickTmpLstItemIcon( const IArgs & arg )
{
	CleanPageList();
	m_mapEpList.clear();
	m_mapEpInfoList.clear();
	m_vecTurnList.clear();
	m_mapDiscussList.clear();
	m_mapDiscussSelItem.clear();
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg) )
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();
		if ( const Data_ConfTemp *pItemInfo = dynamic_cast<const Data_ConfTemp*>( pBaseItem->GetUserData() ) ) 
		{   	
			CString strAlisaName = pItemInfo->m_tConfTemp.m_achConfName;
		
			m_tSelTemplate.Clear();
			ResetInitPage();
			m_emOperateFlag = em_SCANF_PAGE_STATUS;	
			
			s32 nPreClickedItemCount = m_setSelectedTmpIconItem.size();
			m_setSelectedTmpIconItem.insert(strAlisaName);
			s32 nLastClickedItemCount = m_setSelectedTmpIconItem.size();
			
			if ( nPreClickedItemCount == nLastClickedItemCount )
			{
				m_setSelectedTmpIconItem.erase(strAlisaName);
			}
			
			UpdateTmpShowList();
			UpdateUIState();
			m_plsMeetTmp->SetFocus();	
		}
    }
    return true;
}

bool CMeetTemplateLogic::OnClickAddrbookLstItem( const IArgs & arg )
{
	return true;
}

bool CMeetTemplateLogic::OnClickAddrbookLstItemIcon( const IArgs & arg )
{
	//点击图标添加到会场列表及轮询列表左侧
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();        
        if ( const Data_AddrItemInfo *pItemInfo = dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() )) 
        {   
			ClickAddrbookLstItemIcon( pItemInfo );
        } 
    }
	return true;
}

bool CMeetTemplateLogic::ClickAddrbookLstItemIcon( const Data_AddrItemInfo *pItemInfo )
{
	CString strName;
	CString strNum;
	if ( pItemInfo->m_tAddrItem.emItemType == emGroupItem )
	{
		m_plsLocalAddrbook->SetSelItem(-1);
		
		CString strHomeCns;
		m_etHomeMeeting.GetWindowText(strHomeCns);
		if ( strHomeCns.IsEmpty() )
		{
			CString strError;
			int nRet = 0;
			strError = "不能加入分组作为主会场";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
			return false;
		}
		else
		{
			HWND hWndFocus = ::GetFocus();
			if ( hWndFocus == m_etHomeMeeting.GetSafeHwnd() )
			{
				CString strError;
				int nRet = 0;
				strError = "不能加入分组作为主会场";
				MESSAGEWNDBOX( strError, this , nRet , FALSE );
				return false;
			}
		}
		
		u32 adwEntrySetIndext[MAX_ADDRENTRY] = {0};
		u32 dwGroupIdx = pItemInfo->m_tAddrItem.tGroupInfo.dwGroupIdx ;
		if ( NULL != m_pAddrBookIF)
		{
			CAddrBook caddrbook = m_pAddrBookIF->GetAddrBook();
			
			bool bValid = caddrbook.IsAddrMultiSetEntryValid( dwGroupIdx );
			if ( !bValid )
			{
				return false;
			}
			u32 nEntryCount = caddrbook.GetGroupAllEntrySet( dwGroupIdx, adwEntrySetIndext); 
			if ( nEntryCount == 0 )
			{
				CString strError;
				int nRet = 0;
				strError = "当前分组不包含任何会场，不能添加";
				MESSAGEWNDBOX( strError, this , nRet , FALSE );
				return false;
			}
			
			
			for ( s32 nIndex = 0; nIndex < nEntryCount; nIndex++ )
			{
				if ( m_mapEpList.size() > 62 )
				{
					CString strError;
					int nRet = 0;
					strError = "当前会场个数已经达到上限，不能添加";
					MESSAGEWNDBOX( strError, this , nRet , FALSE );
					return false;
				}
				
				CAddrEntry cEntry;
				caddrbook.GetAddrEntry( &cEntry, adwEntrySetIndext[nIndex] );
				
				s8 aszEntryName[MAX_NAME_LEN + 1] = _T("");         //条目名称					
				cEntry.GetEntryName( aszEntryName, cEntry.GetEntryNameLen() + 1 );
				strName = aszEntryName;
				
				s8 aszE164[MAX_E164NUM_LEN + 1] = _T("");       //E164号
				cEntry.GetMtNumber( aszE164, cEntry.GetMtNumberLen() + 1 );
				strNum = aszE164;
				
				AddToEpList( strName, strNum, FALSE );
			}
		}
	}
	else
	{
		strName = pItemInfo->m_tAddrItem.tAddrInfo.achEntryName;
		strNum = pItemInfo->m_tAddrItem.tAddrInfo.achE164;
		
		AddToEpList( strName, strNum );
	}
	
	m_plsLocalAddrbook->SetSelItem(-1);

	return true;
}

bool CMeetTemplateLogic::ClickPollingPageLeftLstItemIcon( const Data_CnsAddr *pItemInfo )
{
	//m_plsPollingLeft->ResetSelItem(TRUE);

	CString strPollingName;
	strPollingName = pItemInfo->m_tEpAddr.m_tAlias.m_abyAlias;
	if ( strPollingName.IsEmpty() )
	{
		strPollingName = pItemInfo->m_tEpAddr.m_tE164.m_abyAlias;
	}

	u16 nPollingId = FindConfTurnListByAlias(strPollingName);		
	s32 nPreClickedItemCount = m_vecTurnList.size();
	std::vector<CString>::iterator iter = find( m_vecTurnList.begin(), m_vecTurnList.end(), strPollingName ); 
	if ( iter == m_vecTurnList.end() )
	{
		EnterCriticalSection(&g_csLock);
		m_vecTurnList.push_back(strPollingName);
		LeaveCriticalSection(&g_csLock);
	}
	s32 nLastClickedItemCount = m_vecTurnList.size();

	if ( nPreClickedItemCount != nLastClickedItemCount )
	{
		::SendMessage( this->m_hWnd, WM_DEF_UPDATEPOLLINGLISTCONTROL, 0, 0 ); //发送更新会场列表的消息
		
		UpdatePollingLeftIcon();
	}

	m_nCurPollingListSortRow = m_vecTurnList.size();
	m_plsMeetPollingRight->SetSelItem(m_nCurPollingListSortRow-1); 
	UpdateSortControlUIState();

	return true;
}

BOOL CMeetTemplateLogic::AddToEpList( const CString& strAddrbookName, const CString& strAddrbookNum, BOOL bIsHomeConfCheck )
{
	CString strHomeCns;
	m_etHomeMeeting.GetWindowText(strHomeCns);
	if ( strHomeCns.IsEmpty() )
	{
// 		if( HomeMeetExistInEpList(strAddrbookName) )
// 		{
// 			return FALSE;
// 		}
		if ( TP_CONF_MAX_EPNUM != FindMeetInEpList(strAddrbookName, strAddrbookNum, TRUE) )
		{
			return FALSE;
		}
		else
		{
			if ( !strAddrbookName.IsEmpty() )
			{
				m_etHomeMeeting.SetWindowText(strAddrbookName);
			}
			else
			{
				m_etHomeMeeting.SetWindowText(strAddrbookNum);
			}

			UpdateGroupEpInfoList(strAddrbookName, strAddrbookNum, 0);
			m_plsMeetEpRight->SetFocus();
			return TRUE;
		}
	}
	else
	{
		if ( m_etHomeMeeting.IsFocus() )
		{
// 			if( HomeMeetExistInEpList(strAddrbookName) )
// 			{
// 				return FALSE;
// 			}
			if ( TP_CONF_MAX_EPNUM != FindMeetInEpList(strAddrbookName, strAddrbookNum, TRUE) )
			{
				return FALSE;
			}
			else
			{
				if ( !strAddrbookName.IsEmpty() )
				{
					m_etHomeMeeting.SetWindowText(strAddrbookName);
				}
				else
				{
					m_etHomeMeeting.SetWindowText(strAddrbookNum);
				}

				UpdateGroupEpInfoList(strAddrbookName, strAddrbookNum, 0);
				m_plsMeetEpRight->SetFocus();
				return TRUE;
			}
		}
		else
		{
			if ( m_mapEpList.size() > 62 )
			{
				CString strError;
				int nRet = 0;
				strError = "当前会场个数已经达到上限，不能添加";
				MESSAGEWNDBOX( strError, this , nRet , FALSE );
				return FALSE;
			}

			if ( !strHomeCns.IsEmpty() )
			{
				std::map<u16,TEpAddr>::iterator iter = m_mapEpInfoList.begin();
				CString strHomeCnsName = iter->second.m_tAlias.m_abyAlias;
				CString strHomeCnsNum = iter->second.m_tE164.m_abyAlias;
				BOOL bHomeMeet = FALSE;
// 				if ( !strHomeCnsName.IsEmpty() && ( strHomeCnsName == strAddrbookName) )
// 				{
// 					bHomeMeet = TRUE;
// 				}
// 				else if ( !strHomeCnsNum.IsEmpty() && ( strHomeCnsNum == strAddrbookNum) )
// 				{
// 					bHomeMeet = TRUE;
// 				}
				if ( ( strHomeCnsName == strAddrbookName)  && ( strHomeCnsNum == strAddrbookNum) )
				{
					bHomeMeet = TRUE;
				}

				if ( bHomeMeet && bIsHomeConfCheck )
				{
					CString strError;
					int nRet = 0;
					strError = "当前所选分会场已经为主会场，不能添加";
					MESSAGEWNDBOX( strError, this , nRet , FALSE );
					return FALSE;
				}
			}
		}
	}

	u16 wEpID = FindMeetInEpList(strAddrbookName, strAddrbookNum);
	if ( TP_CONF_MAX_EPNUM != wEpID )
	{
		if ( bIsHomeConfCheck )   //直接跳转到重复行
		{
			m_plsMeetEpRight->SetSelItem( wEpID -1 );
		}
	}
	else
	{
		u16 wNewEpID = m_mapEpList.size() + 1;
		EnterCriticalSection(&g_csLock);
		if ( !strAddrbookName.IsEmpty() )
		{
			m_mapEpList.insert( std::make_pair<u16,CString>( wNewEpID, strAddrbookName ) );
		}
		else
		{
			m_mapEpList.insert( std::make_pair<u16,CString>( wNewEpID, strAddrbookNum ) );
		}
		LeaveCriticalSection(&g_csLock);

		UpdateGroupEpInfoList(strAddrbookName, strAddrbookNum, wNewEpID);

		::SendMessage( this->m_hWnd, WM_DEF_UPDATEGROUPLISTCONTROL, (WPARAM)TRUE, 0 ); //发送更新会场列表的消息
		
		if ( bIsHomeConfCheck )   //添加会场定位到末尾高亮显示
		{
			m_plsMeetEpRight->SetSelItem( wNewEpID - 1 );
		}
	}
	
// 	s32 nPreClickedItemCount = m_mapEpList.size();
// 	u16 nEpId = m_mapEpList.size() + 1;
// 
// 	EnterCriticalSection(&g_csLock);
// 	std::map<u16,CString>::iterator iter;
// 	iter = find_if( m_mapEpList.begin(), m_mapEpList.end(), bind2nd( ptr_fun(CUmcwebCommon::MapValueCompare), strAddrbookName ) );
// 	if ( iter == m_mapEpList.end() )
// 	{
// 		m_mapEpList.insert( std::make_pair<u16,CString>( nEpId, strAddrbookName ) );
// 	}
// 	LeaveCriticalSection(&g_csLock);
// 	
// 	s32 nLastClickedItemCount = m_mapEpList.size();	
// 	
// 	if ( m_mapEpList.size() > 0 )
// 	{
// 		if ( nPreClickedItemCount != nLastClickedItemCount )
// 		{
// 			::SendMessage( this->m_hWnd, WM_DEF_UPDATEGROUPLISTCONTROL, (WPARAM)TRUE, 0 ); //发送更新会场列表的消息
// 
// 			if ( bIsHomeConfCheck )   //添加会场定位到末尾高亮显示
// 			{
// 				m_plsMeetEpRight->SetSelItem(nEpId-1);
// 			}
// 		}
// 		else    //直接跳转到重复行
// 		{
// 			std::map<u16,CString>::iterator iterEp;
// 			for ( iterEp = m_mapEpList.begin(); iterEp != m_mapEpList.end(); iterEp++ )
// 			{
// 				u16 nCurEpId = iterEp->first;
// 				CString strEpName = iterEp->second;
// 				if ( strEpName == strAddrbookName )
// 				{
// 					if ( bIsHomeConfCheck )   //添加会场定位到末尾高亮显示
// 					{
// 						m_plsMeetEpRight->SetSelItem(nCurEpId-1);
// 						break;
// 					}
// 				}
// 			}
// 		}
// // 		else
// // 		{
// // 			MESSAGEWND( "当前地址簿已经存在会场列表中，不能重复添加" );
// // 		}
// 	}

	if ( m_mapEpList.size() - m_vecTurnList.size() > 0 )
	{
		m_btnAllAdd.EnableWindow(TRUE);
	}
	else
	{
		m_btnAllAdd.EnableWindow(FALSE);
	}

	return TRUE;
}

bool CMeetTemplateLogic::OnClickPollingPageLeftLstItem( const IArgs & arg )
{
	return true;
}
bool CMeetTemplateLogic::OnClickPollingPageLeftLstItemIcon( const IArgs & arg )
{
	//点击轮询列表左侧添加到轮询列表
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();        
        if ( const Data_CnsAddr *pItemInfo = dynamic_cast<const Data_CnsAddr*>( pBaseItem->GetUserData() )) 
        {
			ClickPollingPageLeftLstItemIcon( pItemInfo );
        } 
    }
	return true;
}

bool CMeetTemplateLogic::OnClickDiscussPageLeftLstItem( const IArgs & arg )
{
	return true;
}
bool CMeetTemplateLogic::OnClickDiscussPageLeftLstItemIcon( const IArgs & arg )
{
	//点击轮询列表左侧添加到轮询列表
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();        
        if ( const Data_CnsAddr *pItemInfo = dynamic_cast<const Data_CnsAddr*>( pBaseItem->GetUserData() )) 
        {  
			CString strDiscussName = pItemInfo->m_tEpAddr.m_tAlias.m_abyAlias;
			if ( strDiscussName.IsEmpty() )
			{
				strDiscussName = pItemInfo->m_tEpAddr.m_tE164.m_abyAlias;
			}

			BOOL bFind = FALSE;
			std::map<u16,CString>::iterator iter;
			for ( iter = m_mapDiscussSelItem.begin(); iter != m_mapDiscussSelItem.end(); iter++ )
			{
				CString strSelName = iter->second;
				if ( strcmp( strSelName, strDiscussName ) == 0 )
				{
					m_dlgMeetDiscuss.DelFromEpEdit(strDiscussName);
					bFind = TRUE;
					break;
				}
			}

			if ( !bFind )
			{
				m_dlgMeetDiscuss.AddToEpEdit(strDiscussName);
			}

			FilterDiscussLeftList();
        } 
    }
	return true;
}

void CMeetTemplateLogic::UpdatePollingLeftIcon()
{
	CString strSearchName;
	m_etSearch.GetWindowText( strSearchName );
	if ( !strSearchName.IsEmpty() )
	{
		UpdatePollingLeftShowList( m_mapEpSearchList,  TRUE );   //同步更新轮询左侧列表图标
	}
	else
	{
		UpdatePollingLeftShowList( m_mapEpList,  TRUE );   //同步更新轮询左侧列表图标
	}
}

bool CMeetTemplateLogic::OnClickGroupPageDelItemIcon( const IArgs & arg )
{
	if ( Args_ClickItemInfo *pclickInfo = dynamic_cast<Args_ClickItemInfo*>( const_cast<IArgs*>(&arg)) )
	{ 
		IBaseItem* pBaseItem = pclickInfo->m_pClickList->GetParentItem()->GetItemData();
		if ( pBaseItem != NULL )
		{
			Data_AddrItemInfo ItemInfo = *dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() );
			TAddrItem tAddrItem = ItemInfo.m_tAddrItem;

			EnterCriticalSection(&g_csLock);

			CString strDelName;
			strDelName = tAddrItem.tAddrInfo.achEntryName;
			if ( strDelName.IsEmpty() )
			{
				strDelName = tAddrItem.tAddrInfo.achE164;
			}

// 			u16 nPollingId = FindConfTurnListByAlias(strDelName);	

			u16 nPollingId = FindMeetInEpList( tAddrItem.tAddrInfo.achEntryName, tAddrItem.tAddrInfo.achE164 );

			s32 nPreClickedItemCount = m_mapEpList.size();

			std::map<u16,CString>::iterator iter = m_mapEpList.find( nPollingId ); 
			if ( iter != m_mapEpList.end() )
			{
				m_mapEpList.erase( nPollingId );
				m_mapEpInfoList.erase( nPollingId );
			}
			else
			{
				LeaveCriticalSection(&g_csLock);
				return false;
			}
			
			s32 nLastClickedItemCount = m_mapEpList.size();	
			
			if ( nPreClickedItemCount != nLastClickedItemCount )
			{
				ReSetCnsEpId(nPollingId);
				::SendMessage( this->m_hWnd, WM_DEF_UPDATEGROUPLISTCONTROL, (WPARAM)TRUE, 0 ); //发送更新会场列表的消息
				
				std::vector<CString>::iterator iter = find( m_vecTurnList.begin(), m_vecTurnList.end(), strDelName );
				if ( iter != m_vecTurnList.end() )
				{
					EnterCriticalSection(&g_csLock);
					m_vecTurnList.erase(iter);
					LeaveCriticalSection(&g_csLock);
					::SendMessage( this->m_hWnd, WM_DEF_UPDATEPOLLINGLISTCONTROL, 0, 0 ); //发送更新会场列表的消息
					m_plsMeetPollingRight->SetSelItem(-1);    //有左侧会场列表添加 会场列表删除  轮询列表删除   则取消焦点
					SetSortControlDisable();
				}
			}
			
			if ( m_mapEpList.size() - m_vecTurnList.size() > 0 )
			{
				m_btnAllAdd.EnableWindow(TRUE);
			}
			else
			{
				m_btnAllAdd.EnableWindow(FALSE);
			}
			
			LeaveCriticalSection(&g_csLock);
		}
	}
	
	return true;
}

bool CMeetTemplateLogic::OnClickPollingPageDelItem( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
		IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetItemData();
        
		if ( const Data_CnsID *pItemInfo = dynamic_cast<const Data_CnsID*>( pBaseItem->GetUserData() )) 
		{   
			u16 nPollingId = pItemInfo->m_wData;	
			CString strPollingName = FindConfTurnListById(nPollingId);
			
			m_nCurPollingListSortRow = 0;
			u16 nCurTurnList = 0;
			for ( std::vector<CString>::iterator iter = m_vecTurnList.begin(); iter != m_vecTurnList.end(); iter++ )
			{
				CString strTurnListName = *iter;
				++nCurTurnList;
				if ( strTurnListName != strPollingName )
				{
					continue;
				}
				else
				{
					m_nCurPollingListSortRow = nCurTurnList;
					break;
				}
			}

			UpdateSortControlUIState();
		}
	}
	return true;
}

bool CMeetTemplateLogic::OnClickPollingPageDelItemIcon( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();        
        if ( const Data_CnsID *pItemInfo = dynamic_cast<const Data_CnsID*>( pBaseItem->GetUserData() )) 
        {   
			u16 nPollingId = pItemInfo->m_wData;	
			CString strPollingName = FindConfTurnListById(nPollingId);

			std::vector<CString>::iterator iter = find( m_vecTurnList.begin(), m_vecTurnList.end(), strPollingName );
			if ( iter == m_vecTurnList.end() )
			{
				return false;
			}
			else
			{
				EnterCriticalSection(&g_csLock);
				m_vecTurnList.erase(iter);
				LeaveCriticalSection(&g_csLock);
			}
			
			::SendMessage( this->m_hWnd, WM_DEF_UPDATEPOLLINGLISTCONTROL, 0, 0 ); //发送更新会场列表的消息

			m_nCurPollingListSortRow = 0;
			m_plsMeetPollingRight->SetSelItem(-1);    //有左侧会场列表添加 会场列表删除  轮询列表删除   则取消焦点

			UpdatePollingLeftIcon();
			SetSortControlDisable();

			if ( m_mapEpList.size() - m_vecTurnList.size() > 0 )
			{
				m_btnAllAdd.EnableWindow(TRUE);
			}
			else
			{
				m_btnAllAdd.EnableWindow(FALSE);
			}
			FilterPollingLeftList();
        } 
    }
	
	return true;
}

void CMeetTemplateLogic::HideAllPageCtrl()
{
	m_btnMeetingInfo.ShowWindow(SW_SHOW);
	m_btnGroupInfo.ShowWindow(SW_SHOW);
	m_btnPollingInfo.ShowWindow(SW_SHOW);
	m_btnDiscussInfo.ShowWindow(SW_SHOW);
	m_stTemplateRightTitle.ShowWindow(SW_SHOW);

	m_btnAllAdd.ShowWindow(SW_HIDE);
	m_btnCancel.ShowWindow(SW_HIDE);
	m_btnEdit.ShowWindow(SW_HIDE);
	m_btnSave.ShowWindow(SW_HIDE);

	//会议信息页面
	m_etName.ShowWindow(SW_HIDE);
	m_etNumber.ShowWindow(SW_HIDE);
	
	m_etSetHour.ShowWindow(SW_HIDE);
	m_etSetMin.ShowWindow(SW_HIDE);	
	m_btnSubTime.ShowWindow(SW_HIDE);
	m_btnPlusTime.ShowWindow(SW_HIDE);
	m_edtDotHour.ShowWindow(SW_HIDE);
	m_etDateSet.ShowWindow(SW_HIDE);
	m_btnCalendar.ShowWindow(SW_HIDE);
	
	m_stName.ShowWindow(SW_HIDE);
	m_stNumber.ShowWindow(SW_HIDE);
	m_stTmpType.ShowWindow(SW_HIDE);
	m_stDate.ShowWindow(SW_HIDE);
	m_stStartTime.ShowWindow(SW_HIDE);
	
	m_stNameShow.ShowWindow(SW_HIDE);
	m_stNumberShow.ShowWindow(SW_HIDE);
	m_stTmpTypeShow.ShowWindow(SW_HIDE);
	m_stDateShow.ShowWindow(SW_HIDE);
	m_stStartTimeShow.ShowWindow(SW_HIDE);
	if ( ( NULL != m_plsMeetTmp ) && ( NULL != m_pLetterTmp ) )
	{
		m_plsMeetTmp->ShowWindow(SW_HIDE);
		m_pLetterTmp->ShowWindow(SW_HIDE);
	}

	m_dlgCalendar.ShowWindow(SW_HIDE);
	m_btnCheckCur.ShowWindow(SW_HIDE);
	m_btnCheckOrder.ShowWindow(SW_HIDE);
	m_btnStartConf.ShowWindow(SW_HIDE);

	//会场分组页面
	if ( ( NULL != m_plsMeetEpRight ) && ( NULL != m_plsLocalAddrbook ) && ( NULL != m_pLetterAddrbook ) )
	{
		m_plsMeetEpRight->ShowWindow(SW_HIDE);
		m_plsLocalAddrbook->ShowWindow(SW_HIDE);
		m_pLetterAddrbook->ShowWindow(SW_HIDE);
	}
	m_stHomeMeeting.ShowWindow(SW_HIDE);
	m_etHomeMeeting.ShowWindow(SW_HIDE);
	
	//轮询页面
	if ( ( NULL != m_plsMeetPollingRight ) && ( NULL != m_plsPollingLeft ) && ( NULL != m_pLetterPolling ) )
	{
		m_plsMeetPollingRight->ShowWindow(SW_HIDE);
		m_etPollingTime.ShowWindow(SW_HIDE);
		m_btnSubPollingTime.ShowWindow(SW_HIDE);
		m_btnPlusPollingTime.ShowWindow(SW_HIDE);
		m_stIntervel.ShowWindow(SW_HIDE);
		m_stPollingSecond.ShowWindow(SW_HIDE);
		m_btnSwitchPolling.ShowWindow(SW_HIDE);
		m_plsPollingLeft->ShowWindow(SW_HIDE);
		m_pLetterPolling->ShowWindow(SW_HIDE);
	}

	//会议讨论页面
	m_dlgMeetDiscuss.ShowWindow(SW_HIDE);
	if ( ( NULL != m_plsDiscussLeft ) && ( NULL != m_pLetterDiscuss ) )
	{
		m_plsDiscussLeft->ShowWindow(SW_HIDE);
		m_pLetterDiscuss->ShowWindow(SW_HIDE);
	}

	ShowSortControl(FALSE);
	SetMediaInfoBtnHide();
	SetRateInfoHide();

	m_dlgMediaCfg.ShowWindow(SW_HIDE);
	m_btnReturn.ShowWindow(SW_HIDE);
}
	
void CMeetTemplateLogic::ShowPageScanf()
{
	m_stTemplateLeftTitle.SetWindowText("会议模板");
	m_emOperateFlag = em_SCANF_PAGE_STATUS;

	HideAllPageCtrl();

	if ( ( NULL != m_plsMeetTmp ) && ( NULL != m_pLetterTmp ) )
	{
		m_plsMeetTmp->ShowWindow(TRUE);
		m_pLetterTmp->ShowWindow(TRUE);
		m_plsMeetTmp->EnableWindow(TRUE);
		m_pLetterTmp->EnableWindow(TRUE);
	}

	m_btnNewTmp.EnableWindow(TRUE);
	m_btnNewTmp.ShowWindow(SW_SHOW);
	m_btnAllSel.ShowWindow(SW_SHOW);
	m_btnDelete.ShowWindow(SW_SHOW);
	ResetSerchEditLen();	

	CString strSelConfName = m_tSelTemplate.m_achConfName;
	if ( strSelConfName.IsEmpty() )
	{
		m_btnSave.ShowWindow(SW_HIDE);
		m_btnCancel.ShowWindow(SW_HIDE);
		m_btnEdit.ShowWindow(SW_HIDE);
		return;
	}

	m_btnSave.ShowWindow(SW_HIDE);
	m_btnCancel.ShowWindow(SW_HIDE);
	m_btnEdit.ShowWindow(SW_SHOW);


	switch( m_emTabFlag )
	{
	case em_MEETINFO_PAGE:
		{
			CString strMeetTmpName;
			m_stNameShow.GetWindowText(strMeetTmpName);
			if ( strMeetTmpName.IsEmpty())
			{
				break;
			}

			m_stName.SetWindowText("名称");
			m_stNumber.SetWindowText("号码");
			m_stTmpType.SetWindowText("类型");

			ShowMeetInfoScanfPage(TRUE);
		}
		break;
	case em_Ep_PAGE:
		{
			m_stName.SetWindowText("主会场");
			m_stNumber.SetWindowText("分会场");
			m_plsMeetEpRight->ShowWindow(SW_SHOW);
			m_stName.ShowWindow(SW_SHOW);
			m_stNumber.ShowWindow(SW_SHOW);
			m_stHomeMeeting.ShowWindow(SW_SHOW);

			SetMediaInfoBtnHide(TRUE);
			SetRateInfoHide();
			m_btnReturn.ShowWindow(SW_HIDE);
		}
		break;
	case em_POLLING_PAGE:
		{
			m_stName.SetWindowText("会议轮询");
			m_stNumber.SetWindowText("轮询间隔");
			m_stTmpType.SetWindowText("轮询排序");
			m_plsMeetPollingRight->ShowWindow(SW_SHOW);
			m_pLetterPolling->ShowWindow(SW_SHOW);
			m_stName.ShowWindow(SW_SHOW);
			m_stNumber.ShowWindow(SW_SHOW);
			m_stTmpType.ShowWindow(SW_SHOW);
			m_stIntervel.ShowWindow(SW_SHOW);
			CString strIntervel;
			m_stIntervel.GetWindowText(strIntervel);
			m_stPollingSecond.ShowWindow(FALSE);
			m_btnSwitchPolling.EnableWindow(FALSE);
			m_btnSwitchPolling.ShowWindow(SW_SHOW);

			SetMediaInfoBtnHide(TRUE);
			SetRateInfoHide();
			m_btnReturn.ShowWindow(SW_HIDE);
		}
		break;
	case em_DISCUSS_PAGE:
		{
			m_dlgMeetDiscuss.ShowWindow(SW_SHOW);
		}
		break;
	default:
		{
		}
		break;
	}
}

void CMeetTemplateLogic::ShowPageEdit()
{
	m_emOperateFlag = em_EDIT_PAGE_STATUS;

	m_stTemplateRightTitle.SetWindowText("编辑会议模板");
	m_btnNewTmp.EnableWindow(FALSE);
	m_plsMeetTmp->EnableWindow(FALSE);
	m_pLetterTmp->EnableWindow(FALSE);

	m_btnAllSel.EnableWindow(FALSE);
	m_btnDelete.EnableWindow(FALSE);

	if ( m_dlgMediaCfg.IsWindowVisible() )
	{
		m_stPollingSecond.ShowWindow(FALSE);
		::SendMessage( m_dlgMediaCfg, WM_DEF_SENDTMPINFOTOPAGE, (WPARAM)&m_tSelTemplate, (LPARAM)m_emOperateFlag );

		CleanSearchList();
	}
	else
	{
		HideAllPageCtrl();

		switch( m_emTabFlag )
		{
		case em_MEETINFO_PAGE:
			{
				m_stTemplateLeftTitle.SetWindowText("会议模板");
				m_stName.SetWindowText("名称");
				m_stNumber.SetWindowText("号码");
				m_stTmpType.SetWindowText("类型");
				m_plsMeetTmp->ShowWindow(TRUE);
				m_pLetterTmp->ShowWindow(TRUE);
				
				ShowMeetInfoEditPage(TRUE);
				
				m_btnNewTmp.ShowWindow(SW_SHOW);
				m_btnAllSel.ShowWindow(SW_SHOW);
				m_btnDelete.ShowWindow(SW_SHOW);
				ResetSerchEditLen();
				CleanSearchList();
				
				SetMediaInfoBtnPos(FALSE);
				SetRateInfoPos(FALSE);
			}
			break;
		case em_Ep_PAGE:
			{
				m_stTemplateLeftTitle.SetWindowText("本地地址簿");
				m_stName.SetWindowText("主会场");
				m_stNumber.SetWindowText("分会场");
				m_plsMeetEpRight->ShowWindow(SW_SHOW);
				m_plsLocalAddrbook->ShowWindow(SW_SHOW);
				m_pLetterAddrbook->ShowWindow(SW_SHOW);
				m_stName.ShowWindow(SW_SHOW);
				m_stNumber.ShowWindow(SW_SHOW);
				m_etHomeMeeting.ShowWindow(SW_SHOW);	
				
				m_btnNewTmp.ShowWindow(SW_HIDE);
				m_btnAllSel.ShowWindow(SW_HIDE);
				m_btnDelete.ShowWindow(SW_HIDE);
				SetAddrbookSerchEditLen();	
				CleanSearchList();
			}
			break;
		case em_POLLING_PAGE:
			{
				m_stTemplateLeftTitle.SetWindowText("分会场");
				m_stName.SetWindowText("会议轮询");
				m_stNumber.SetWindowText("轮询间隔");
				m_stTmpType.SetWindowText("轮询排序");
				m_plsMeetPollingRight->ShowWindow(SW_SHOW);
				m_plsPollingLeft->ShowWindow(SW_SHOW);
				m_pLetterPolling->ShowWindow(SW_SHOW);
				m_stName.ShowWindow(SW_SHOW);
				m_stNumber.ShowWindow(SW_SHOW);
				m_stTmpType.ShowWindow(SW_SHOW);
				m_etPollingTime.ShowWindow(SW_SHOW);
				m_btnSubPollingTime.ShowWindow(SW_SHOW);
				m_btnPlusPollingTime.ShowWindow(SW_SHOW);
				m_stPollingSecond.ShowWindow(SW_SHOW);
				m_btnSwitchPolling.EnableWindow(TRUE);
				m_btnSwitchPolling.ShowWindow(SW_SHOW);
				
				m_btnNewTmp.ShowWindow(SW_HIDE);
				m_btnAllSel.ShowWindow(SW_HIDE);
				m_btnDelete.ShowWindow(SW_HIDE);
				m_btnAllAdd.ShowWindow(SW_SHOW);
				SetPollingLeftviewSerchEditLen();	
				
// 				if ( m_bSwitchPolling )
// 				{
				if ( m_vecTurnList.size() > 0 )
				{
					ShowSortControl(TRUE);
				}
//				}	
				else
				{
					ShowSortControl(FALSE);
				}
				CleanSearchList();
			}
			break;
		case em_DISCUSS_PAGE:
			{
				m_stTemplateLeftTitle.SetWindowText("与会会场列表");

				if ( ( NULL != m_plsDiscussLeft ) && ( NULL != m_pLetterDiscuss ) )
				{
					m_plsDiscussLeft->ShowWindow(SW_SHOW);
					m_pLetterDiscuss->ShowWindow(SW_SHOW);
				}
				
				m_btnNewTmp.ShowWindow(SW_HIDE);
				m_btnAllSel.ShowWindow(SW_HIDE);
				m_btnDelete.ShowWindow(SW_HIDE);

				SetAddrbookSerchEditLen();	
				CleanSearchList();
//				OnSwitchDiscuss( m_bSwitchDiscuss, 0 );

				//bug:编辑会议模版，讨论预案中已设置的会场，没有全部显示为已勾选状态   -- 20140529 by xhx
				CString strSearchName;
				m_etSearch.GetWindowText( strSearchName );
				if( strSearchName.IsEmpty() )
				{
					UpdateDiscussShowListData();
					UpdateDiscussLeftShowList( m_mapDiscussList,  TRUE );
				}
				
				m_dlgMeetDiscuss.ShowWindow(SW_SHOW);
			}
			break;
		default:
			{
			}
			break;
		}
		
	}
	
	m_btnSave.ShowWindow(SW_SHOW);
	m_btnCancel.ShowWindow(SW_SHOW);
	m_btnEdit.ShowWindow(SW_HIDE);
	m_btnAllSel.EnableWindow(FALSE);
	UpdateSearchEdtStatus();
}

void CMeetTemplateLogic::ShowPageNew()
{
	m_emOperateFlag = em_NEW_PAGE_STATUS;
	
	HideAllPageCtrl();
	
	m_btnSave.ShowWindow(SW_SHOW);
	m_btnCancel.ShowWindow(SW_SHOW);
	m_btnEdit.ShowWindow(SW_HIDE);
	
	m_stTemplateRightTitle.SetWindowText("编辑会议模板");
	m_btnNewTmp.EnableWindow(FALSE);
	if ( NULL != m_plsMeetTmp )
	{
		m_plsMeetTmp->EnableWindow(FALSE);
		m_pLetterTmp->EnableWindow(FALSE);
	}

	switch( m_emTabFlag )
	{
	case em_MEETINFO_PAGE:
		{
			m_stTemplateLeftTitle.SetWindowText("会议模板");
			m_stName.SetWindowText("名称");
			m_stNumber.SetWindowText("号码");
			m_stTmpType.SetWindowText("类型");
			if ( ( NULL != m_plsMeetTmp ) && ( NULL != m_plsMeetTmp ) )
			{
				m_plsMeetTmp->ShowWindow(TRUE);
				m_pLetterTmp->ShowWindow(TRUE);
			}

			m_dlgCalendar.ShowWindow(SW_HIDE);
	
			SetMediaInfoBtnHide(FALSE);
			m_btnReturn.ShowWindow(SW_HIDE);
			ShowMeetInfoEditPage(TRUE);

			m_btnNewTmp.ShowWindow(SW_SHOW);
			m_btnAllSel.ShowWindow(SW_SHOW);
			m_btnDelete.ShowWindow(SW_SHOW);
			ResetSerchEditLen();
			CleanSearchList();

			SetMediaInfoBtnPos(FALSE);
			SetRateInfoPos(FALSE);
		}
		break;
	case em_Ep_PAGE:
		{
			m_stTemplateLeftTitle.SetWindowText("本地地址簿");
			m_stName.SetWindowText("主会场");
			m_stNumber.SetWindowText("分会场");
			if ( ( NULL != m_plsMeetEpRight ) && ( NULL != m_plsLocalAddrbook ) && ( NULL != m_pLetterAddrbook ) )
			{
				m_plsMeetEpRight->ShowWindow(SW_SHOW);
				m_plsMeetEpRight->ShowWindow(SW_SHOW);
				m_plsLocalAddrbook->ShowWindow(SW_SHOW);
				m_pLetterAddrbook->ShowWindow(SW_SHOW);
			}
			m_stName.ShowWindow(SW_SHOW);
			m_stNumber.ShowWindow(SW_SHOW);
			m_etHomeMeeting.ShowWindow(SW_SHOW);

			m_btnNewTmp.ShowWindow(SW_HIDE);
			m_btnAllSel.ShowWindow(SW_HIDE);
			m_btnDelete.ShowWindow(SW_HIDE);
			SetAddrbookSerchEditLen();	
			CleanSearchList();
		}
		break;
	case em_POLLING_PAGE:
		{
			m_stTemplateLeftTitle.SetWindowText("分会场");
			m_stName.SetWindowText("会议轮询");
			m_stNumber.SetWindowText("轮询间隔");
			m_stTmpType.SetWindowText("轮询排序");
			if ( ( NULL != m_plsMeetPollingRight ) && ( NULL != m_plsPollingLeft ) && ( NULL != m_pLetterPolling ) )
			{
				m_plsMeetPollingRight->ShowWindow(SW_SHOW);
				m_plsPollingLeft->ShowWindow(SW_SHOW);
				m_pLetterPolling->ShowWindow(SW_SHOW);
			}
			m_stName.ShowWindow(SW_SHOW);
			m_stNumber.ShowWindow(SW_SHOW);
			m_stTmpType.ShowWindow(SW_SHOW);
			m_etPollingTime.ShowWindow(SW_SHOW);
			m_btnSubPollingTime.ShowWindow(SW_SHOW);
			m_btnPlusPollingTime.ShowWindow(SW_SHOW);
			m_stPollingSecond.ShowWindow(SW_SHOW);
			m_btnSwitchPolling.EnableWindow(TRUE);
			m_btnSwitchPolling.ShowWindow(SW_SHOW);

			m_btnNewTmp.ShowWindow(SW_HIDE);
			m_btnAllSel.ShowWindow(SW_HIDE);
			m_btnDelete.ShowWindow(SW_HIDE);
			m_btnAllAdd.ShowWindow(SW_SHOW);
			SetPollingLeftviewSerchEditLen();
// 			if ( m_bSwitchPolling )
// 			{
			if( m_vecTurnList.size() > 0 )
			{
				ShowSortControl(TRUE);
			}
//			}
			else
			{
				ShowSortControl(FALSE);
			}
			CleanSearchList();
		}
		break;
	case em_DISCUSS_PAGE:
		{
			m_stTemplateLeftTitle.SetWindowText("与会会场列表");

			if ( ( NULL != m_plsDiscussLeft ) && ( NULL != m_pLetterDiscuss ) )
			{
				m_plsDiscussLeft->ShowWindow(SW_SHOW);
				m_pLetterDiscuss->ShowWindow(SW_SHOW);
			}

			m_btnNewTmp.ShowWindow(SW_HIDE);
			m_btnAllSel.ShowWindow(SW_HIDE);
			m_btnDelete.ShowWindow(SW_HIDE);

			SetAddrbookSerchEditLen();	
			CleanSearchList();
//			OnSwitchDiscuss( m_bSwitchDiscuss, 0 );

			CString strSearchName;
			m_etSearch.GetWindowText( strSearchName );
			if( strSearchName.IsEmpty() )
			{
				UpdateDiscussShowListData();
				UpdateDiscussLeftShowList( m_mapDiscussList,  TRUE );
			}
			
			m_dlgMeetDiscuss.ShowWindow(SW_SHOW);
		}
		break;
	default:
		{	
		}
		break;
	}
	m_btnAllSel.EnableWindow(FALSE);
	m_btnDelete.EnableWindow(FALSE);
	UpdateSearchEdtStatus();
}

void CMeetTemplateLogic::ShowMeetInfoScanfPage(BOOL bShow)
{
	m_stName.ShowWindow(bShow);
	m_stNumber.ShowWindow(bShow);
	m_stTmpType.ShowWindow(bShow);
	m_stNameShow.ShowWindow(bShow);
	m_stNumberShow.ShowWindow(bShow);
	m_stTmpTypeShow.ShowWindow(bShow);
	m_btnStartConf.ShowWindow(bShow);

	if(	m_tSelTemplate.m_tStartTime == 0 )
	{
		m_stDate.ShowWindow(FALSE);
		m_stStartTime.ShowWindow(FALSE);
		m_stDateShow.ShowWindow(FALSE);
		m_stStartTimeShow.ShowWindow(FALSE);
		
		SetMediaInfoBtnPos();
		SetRateInfoPos();
	}
	else
	{
		m_stDate.ShowWindow(bShow);
		m_stStartTime.ShowWindow(bShow);
		m_stDateShow.ShowWindow(bShow);
		m_stStartTimeShow.ShowWindow(bShow);
		
		SetMediaInfoBtnPos(FALSE);
		SetRateInfoPos(FALSE);
	}

	SetMediaInfoBtnHide(!bShow);
	SetRateInfoHide(!bShow);
}

void CMeetTemplateLogic::ShowMeetInfoEditPage(BOOL bShow)
{
	m_stName.ShowWindow(bShow);
	m_stNumber.ShowWindow(bShow);
	m_stTmpType.ShowWindow(bShow);
	m_stDate.ShowWindow(bShow);
	m_stStartTime.ShowWindow(bShow);
	
	m_etName.ShowWindow(bShow);
	m_etNumber.ShowWindow(bShow);
	m_etSetHour.ShowWindow(bShow);
	m_etSetMin.ShowWindow(bShow);
	m_btnSubTime.ShowWindow(bShow);
	m_btnPlusTime.ShowWindow(bShow);
	m_edtDotHour.ShowWindow(bShow);
	m_etDateSet.ShowWindow(bShow);
	m_btnCalendar.ShowWindow(bShow);
	
	m_btnCheckCur.ShowWindow(bShow);
	m_btnCheckOrder.ShowWindow(bShow);
	m_btnCheckCur.EnableWindow(bShow);
	m_btnCheckOrder.EnableWindow(bShow);	

	SetMediaInfoBtnHide(!bShow);
	SetRateInfoHide(!bShow);
}

void CMeetTemplateLogic::ResetSerchEditLen()
{
	CRect rectClient;
	m_btnNewTmp.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	m_etSearch.SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 53*CUR_SCREEN_HEIGHT_PER,  rectClient.right - 
		m_btnNewTmp.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - 15*CUR_SCREEN_WIDTH_PER,41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
}

void CMeetTemplateLogic::SetAddrbookSerchEditLen()
{
	CRect rectClient;
	m_plsLocalAddrbook->GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	m_etSearch.SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 53*CUR_SCREEN_HEIGHT_PER, rectClient.right
	 - 10*CUR_SCREEN_WIDTH_PER,41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
}

void CMeetTemplateLogic::SetPollingLeftviewSerchEditLen()
{
	CRect rectClient;
	m_btnAllAdd.GetWindowRect(&rectClient);
	ScreenToClient( &rectClient );
	m_etSearch.SetWindowPos( NULL, 12*CUR_SCREEN_WIDTH_PER, 53*CUR_SCREEN_HEIGHT_PER, rectClient.right - 
		m_btnAllAdd.GetImageSize().cx*CUR_SCREEN_WIDTH_PER - 15*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
}

void CMeetTemplateLogic::SetSelectedTmpDataToScanfPage(const TTPConfTemplate& tSelConfTmplate)
{
	CleanPageList();
	m_mapEpList.clear();
	m_mapEpInfoList.clear();
	m_vecTurnList.clear();
	m_mapDiscussList.clear();
	m_mapDiscussSelItem.clear();
	
	m_stNameShow.SetWindowText(tSelConfTmplate.m_achConfName);
	m_stNumberShow.SetWindowText(tSelConfTmplate.m_achConfE164);
	if( tSelConfTmplate.m_tStartTime == 0 )
	{
		m_stTmpTypeShow.SetWindowText("即时会议");
		m_stDateShow.SetWindowText("");
		m_stStartTimeShow.SetWindowText("");
		m_stDateShow.ShowWindow(FALSE);
		m_stStartTimeShow.ShowWindow(FALSE);
		m_stDate.ShowWindow(FALSE);
		m_stStartTime.ShowWindow(FALSE);
		m_etDateSet.EnableWindow(FALSE);
		m_etDateSet.SetWindowText("");
	}
	else
	{
		m_stTmpTypeShow.SetWindowText("预约会议");
		CTime ctime(tSelConfTmplate.m_tStartTime);
		CString strDate = ctime.Format("%Y年%m月%d日");
		CString strTime = ctime.Format("%H:%M:%S");
		m_stDateShow.SetWindowText(strDate);
		m_stStartTimeShow.SetWindowText(strTime);	
		m_etDateSet.EnableWindow(TRUE);
	}	

	CString strConfRate;
	strConfRate.Format( "%d", m_tSelTemplate.m_wConfBitRate );
	m_stConfRateShow.SetWindowText(strConfRate);
	CString strShowRate;
	strShowRate.Format( "%d", m_tSelTemplate.m_wHpDualBitRate );
	m_stShowRateShow.SetWindowText(strShowRate);

	u16 wResNum = CComInterface::GetNeedBasNum(tSelConfTmplate);
	UpdateResUsedCountToControl(wResNum);

 	CString strHomeMeetingName;
 	TEpAddrList tTeAddrList = tSelConfTmplate.m_atEpList;
	strHomeMeetingName = tTeAddrList.m_tCnsList[0].m_tAlias.m_abyAlias;
	if ( strHomeMeetingName.IsEmpty() )
	{
		strHomeMeetingName = tTeAddrList.m_tCnsList[0].m_tE164.m_abyAlias;
	}

	m_stHomeMeeting.SetWindowText(strHomeMeetingName);

	//赋值会场列表和轮询列表
	SetEpListPageToEditPage(tSelConfTmplate);
	SetTurnListPageToEditPage(tSelConfTmplate);
	SetDiscussListPageToEditPage(tSelConfTmplate);

	if ( m_emOperateFlag == em_SCANF_PAGE_STATUS )
	{
		ShowPageScanf();				 //显示预览控件	
		
		::SendMessage( m_dlgMediaCfg, WM_DEF_SENDTMPINFOTOPAGE, (WPARAM)&m_tSelTemplate, (LPARAM)m_emOperateFlag ); //设置媒体信息
	}
}

void CMeetTemplateLogic::SetSelectedTmpDataToEditPage()
{
	//编辑控件数据赋值
	CString strName;
	m_stNameShow.GetWindowText(strName);
	m_etName.SetWindowText(strName);
	
	CString strNum;
	m_stNumberShow.GetWindowText(strNum);
	m_etNumber.SetWindowText(strNum);

	CString strConfRate;
	m_stConfRateShow.GetWindowText(strConfRate);
 	m_etConfRate.SetWindowText(strConfRate);
	CString strShowRate;
	m_stShowRateShow.GetWindowText(strShowRate);
 	m_etShowRate.SetWindowText(strShowRate);
	
	CString strTemplateType;
	m_stTmpTypeShow.GetWindowText(strTemplateType);
	if ( strTemplateType.Compare("预约会议") == 0 )
	{
		m_btnCalendar.EnableWindow(TRUE);
		m_btnPlusTime.EnableWindow(TRUE);
		m_btnSubTime.EnableWindow(TRUE);
		m_etSetHour.EnableWindow(TRUE);
		m_edtDotHour.EnableWindow(TRUE);
		m_etSetMin.EnableWindow(TRUE);
		m_etDateSet.EnableWindow(TRUE);

		m_btnCalendar.EnableWindow(TRUE);
		m_btnCheckCur.SetCheck(TRUE);
		m_btnCheckOrder.SetCheck(FALSE);

		CString strTemplateDate;
		m_stDateShow.GetWindowText(strTemplateDate);
		m_etDateSet.SetWindowText(strTemplateDate);

		CString strStartTime;
		m_stStartTimeShow.GetWindowText(strStartTime);
		
		s32 nHour = 0, nMin = 0, nSec = 0;   
		sscanf( strStartTime, "%d:%d:%d", &nHour, &nMin, &nSec );   

		s8 chCurHour[3] = { 0 };
		sprintf( chCurHour, "%.2d", nHour );
		s8 chCurMinute[3] = { 0 };
		sprintf( chCurMinute, "%.2d", nMin );

		m_etSetHour.SetWindowText(chCurHour);
		m_etSetMin.SetWindowText(chCurMinute);
	}
	else
	{
		m_btnCalendar.EnableWindow(FALSE);
		m_btnPlusTime.EnableWindow(FALSE);
		m_btnSubTime.EnableWindow(FALSE);
		m_etSetHour.EnableWindow(FALSE);
		m_edtDotHour.EnableWindow(FALSE);
		m_etSetMin.EnableWindow(FALSE);
		m_btnCheckOrder.SetCheck(TRUE);
		m_btnCheckCur.SetCheck(FALSE);
		m_etSetMin.SetWindowText("");
		m_etSetHour.SetWindowText("");
		m_etDateSet.EnableWindow(FALSE);
		m_etDateSet.SetWindowText("");
		
	}
	
	m_etName.SetFocus();

	CString strHomeMeeting;
	m_stHomeMeeting.GetWindowText(strHomeMeeting);
	m_etHomeMeeting.SetWindowText(strHomeMeeting);

	SetEpListPageToEditPage(m_tSelTemplate);
	SetTurnListPageToEditPage(m_tSelTemplate);
	SetDiscussListPageToEditPage(m_tSelTemplate);

	if ( m_emOperateFlag == em_EDIT_PAGE_STATUS )
	{
		ShowPageEdit();
	}
}

void CMeetTemplateLogic::SetEpListPageToEditPage(const TTPConfTemplate& tSelConfTmplate)
{
	//赋值会场列表和轮询列表
	m_mapEpList.clear();
	m_mapEpInfoList.clear();
	
	TEpAddrList tTeAddrList = tSelConfTmplate.m_atEpList;
	for (s32 nIndex = 0; nIndex < tTeAddrList.m_wNum; nIndex++ )
	{
		TEpAddr tTeAddr = tTeAddrList.m_tCnsList[nIndex];
		u16 nEpId = tTeAddr.m_wEpID;
		
		if ( nEpId == 0 )
		{
			m_mapEpInfoList.insert( std::make_pair<u16,TEpAddr>( 0, tTeAddr ) );
			continue;
		}
		
		s8 chEpId[8];
		memset( chEpId, 0 , 8 );
		itoa( nEpId, chEpId, 10 );
		
		CString strEpListName = tTeAddr.m_tAlias.m_abyAlias;
		if ( strEpListName.IsEmpty() )
		{
			strEpListName = tTeAddr.m_tE164.m_abyAlias;
		}
		
		u16 nItemRowId = m_mapEpList.size() + 1;
		
		s32 nPreClickedItemCount = m_mapEpList.size();
	
		std::map<u16,CString>::iterator iter = m_mapEpList.find( nItemRowId ); 
		if ( iter == m_mapEpList.end() )
		{
			EnterCriticalSection(&g_csLock);
			m_mapEpList.insert( std::make_pair<u16,CString>( nItemRowId, strEpListName ) );
			m_mapEpInfoList.insert( std::make_pair<u16,TEpAddr>( nItemRowId, tTeAddr ) );
			LeaveCriticalSection(&g_csLock);
		}

		s32 nLastClickedItemCount = m_mapEpList.size();	

		BOOL bIsShowIcon = FALSE;
		if ( m_emOperateFlag == em_SCANF_PAGE_STATUS )
		{
			bIsShowIcon = FALSE;
		}
		else
		{
			bIsShowIcon = TRUE;
		}

		if ( nPreClickedItemCount != nLastClickedItemCount )
		{
			::SendMessage( this->m_hWnd, WM_DEF_UPDATEGROUPLISTCONTROL, (WPARAM)bIsShowIcon, 0 ); //发送更新会场列表的消息
		}
	}

	if ( m_mapEpList.size() - m_vecTurnList.size() > 0 )
	{
		m_btnAllAdd.EnableWindow(TRUE);
	}
	else
	{
		m_btnAllAdd.EnableWindow(FALSE);
	}
}

void CMeetTemplateLogic::SetTurnListPageToEditPage(const TTPConfTemplate& tSelConfTmplate)
{
	s8 chTmpInterval[8];
	memset( chTmpInterval, 0, 8 );
	itoa( tSelConfTmplate.m_tTurnList.m_wInterval, chTmpInterval, 10 );
	CString strTurnInterval = chTmpInterval ;

	m_etPollingTime.SetWindowText(strTurnInterval);
	if( !strTurnInterval.IsEmpty() )
	{
		m_stPollingSecond.ShowWindow(TRUE);
	}

	if ( !strTurnInterval.IsEmpty() )
	{
		strTurnInterval += "  秒";
		m_stIntervel.SetWindowText(strTurnInterval);
	}

	m_vecTurnList.clear();
	//赋值轮询列表
	for (s32 nIndex = 0; nIndex < tSelConfTmplate.m_tTurnList.m_wNum; nIndex++ )
	{
		u16 nPollingId = tSelConfTmplate.m_tTurnList.m_awList[nIndex];
		if ( nPollingId == 0 )
		{
			continue;
		}

		CString strPollingName;
		strPollingName = FindConfTurnListById(nPollingId);

 		s32 nPreClickedItemCount = m_vecTurnList.size();

		std::vector<CString>::iterator iter = find( m_vecTurnList.begin(), m_vecTurnList.end(), strPollingName ); 
		if ( iter == m_vecTurnList.end() )
		{
			EnterCriticalSection(&g_csLock);
 			m_vecTurnList.push_back(strPollingName);
			LeaveCriticalSection(&g_csLock);
		}

 		s32 nLastClickedItemCount = m_vecTurnList.size();
 		if ( nPreClickedItemCount != nLastClickedItemCount )
 		{
 			::SendMessage( this->m_hWnd, WM_DEF_UPDATEPOLLINGLISTCONTROL, (WPARAM)(LPCTSTR)strPollingName, (LPARAM)nPollingId ); //发送更新会场列表的消息
		}
	}

	if ( m_bSwitchPolling != tSelConfTmplate.m_tTurnList.m_bPollOn )
	{
		m_bSwitchPolling = tSelConfTmplate.m_tTurnList.m_bPollOn;
		m_btnSwitchPolling.SetSwitchState( !m_bSwitchPolling );
//		UpdatePollingUIState();
	}
}

void CMeetTemplateLogic::SetInitDataToNewPage()
{
	//编辑控件数据赋值
	//浏览页面
	m_etName.SetWindowText("");
	m_etNumber.SetWindowText("");
	m_etSetMin.SetWindowText("");
	m_etDateSet.SetWindowText("");
	m_etSetHour.SetWindowText("");
	m_etConfRate.SetWindowText("2048");
	m_etShowRate.SetWindowText("2048");
	m_etName.SetFocus();
 
	m_etDateSet.SetWindowText("");
	//m_etAdaptRes.SetWindowText("会议所需适配资源 0/8");
	UpdateResUsedCountToControl(0);

	//会场分组页面
	m_etHomeMeeting.SetWindowText("");
	CleanPageList();

	//轮询页面
	m_mapEpList.clear();
	m_mapEpInfoList.clear();
	m_vecTurnList.clear();
	m_etPollingTime.SetWindowText("20");

	//会议讨论页面
	m_mapDiscussList.clear();
	m_mapDiscussSelItem.clear();

	SYSTEMTIME sysTime;
	::GetLocalTime( &sysTime ); 
	m_dlgCalendar.SetDate( sysTime.wYear, sysTime.wMonth, sysTime.wDay );

// 	CTime tmCur = CTime::GetCurrentTime();
// 	m_dlgCalendar.SetDate( tmCur.GetYear(), tmCur.GetMonth(), tmCur.GetDay() );
	
	if ( m_emOperateFlag == em_NEW_PAGE_STATUS )
	{
		ShowPageNew();
	}
}

void CMeetTemplateLogic::ReSetCnsEpId(u16 uDelPos)
{
	std::map<u16,CString> mapNew;
	//轮询列表
	for ( std::map<u16,CString>::iterator iter = m_mapEpList.begin(); iter != m_mapEpList.end(); iter++ )
	{
		u16 nPollingId = iter->first;
		LPCTSTR strPollingName = iter->second;
		if ( nPollingId < uDelPos )
		{
			std::map<u16,CString>::iterator iter = mapNew.find( nPollingId ); 
			if ( iter == mapNew.end() )
			{
				EnterCriticalSection(&g_csLock);
				mapNew.insert(std::make_pair<u16,CString>( nPollingId, strPollingName ) );
				LeaveCriticalSection(&g_csLock);
			}
			continue;
		}
		else
		{
			u16 nPollingKey = nPollingId - 1;
			std::map<u16,CString>::iterator iter = mapNew.find( nPollingKey ); 
			if ( iter == mapNew.end() )
			{
				EnterCriticalSection(&g_csLock);
				mapNew.insert(std::make_pair<u16,CString>( nPollingKey, strPollingName ) );
				LeaveCriticalSection(&g_csLock);
			}
		}
	}
	
	m_mapEpList.clear();
	for ( std::map<u16,CString>::iterator iterNew = mapNew.begin(); iterNew != mapNew.end(); iterNew++ )
	{
		u16 nPollingNum = iterNew->first;
		LPCTSTR strPollingName = iterNew->second;

		std::map<u16,CString>::iterator iter = m_mapEpList.find( nPollingNum ); 
		if ( iter == m_mapEpList.end() )
		{
			EnterCriticalSection(&g_csLock);
			m_mapEpList.insert(std::make_pair<u16,CString>( nPollingNum, strPollingName ) );
			LeaveCriticalSection(&g_csLock);
		}
	}

	//更新m_mapEpInfoList
	std::map<u16,TEpAddr> mapInfoNew;
	for ( std::map<u16,TEpAddr>::iterator iterInfo = m_mapEpInfoList.begin(); iterInfo != m_mapEpInfoList.end(); iterInfo++ )
	{
		u16 nPollingId = iterInfo->first;
		TEpAddr tEpAddr = iterInfo->second;
		if ( nPollingId < uDelPos )
		{
			std::map<u16,TEpAddr>::iterator iterInfoFind = mapInfoNew.find( nPollingId ); 
			if ( iterInfoFind == mapInfoNew.end() )
			{
				EnterCriticalSection(&g_csLock);
				mapInfoNew.insert(std::make_pair<u16,TEpAddr>( nPollingId, tEpAddr ) );
				LeaveCriticalSection(&g_csLock);
			}
			continue;
		}
		else
		{
			u16 nPollingKey = nPollingId - 1;
			std::map<u16,TEpAddr>::iterator iter = mapInfoNew.find( nPollingKey ); 
			if ( iter == mapInfoNew.end() )
			{
				EnterCriticalSection(&g_csLock);
				mapInfoNew.insert(std::make_pair<u16,TEpAddr>( nPollingKey, tEpAddr ) );
				LeaveCriticalSection(&g_csLock);
			}
		}
	}
	
	m_mapEpInfoList.clear();
	for ( std::map<u16,TEpAddr>::iterator iterInfoNew = mapInfoNew.begin(); iterInfoNew != mapInfoNew.end(); iterInfoNew++ )
	{
		u16 nPollingNum = iterInfoNew->first;
		TEpAddr tEpAddr = iterInfoNew->second;
		
		std::map<u16,TEpAddr>::iterator iterInfoFind = m_mapEpInfoList.find( nPollingNum ); 
		if ( iterInfoFind == m_mapEpInfoList.end() )
		{
			EnterCriticalSection(&g_csLock);
			m_mapEpInfoList.insert(std::make_pair<u16,TEpAddr>( nPollingNum, tEpAddr ) );
			LeaveCriticalSection(&g_csLock);
		}
	}
}

void CMeetTemplateLogic::CleanPageList()
{
	if ( ( NULL == m_plsMeetEpRight ) || ( NULL == m_plsPollingLeft ) || ( NULL == m_plsMeetPollingRight ) || ( NULL == m_plsDiscussLeft ) )
	{
		return;
	}

	vector<TAddrItem> vctAddrLst;
	Value_TouchListAddr val_TempAddr( &vctAddrLst );
	m_plsMeetEpRight->SetData(val_TempAddr);

	TEpAddrList tCnsLst;
	Value_TouchListTempCns val_TempCns( tCnsLst );
	m_plsPollingLeft->SetData( val_TempCns);
	m_plsDiscussLeft->SetData( val_TempCns);

	TCMSConfTemplate tCnsTemplate;
	Value_TouchListTempPoll val_TempPoll( tCnsTemplate );
	m_plsMeetPollingRight->SetData( val_TempPoll );
}

void CMeetTemplateLogic::OnBtnCalendar() 
{   
	s32 nCheck = m_btnCalendar.GetCheck();
	if( nCheck == BST_CHECKED )
	{
		m_dlgCalendar.SetNotifyWnd(this->GetSafeHwnd());
		CRect rectCalendar;
		m_btnCalendar.GetWindowRect(&rectCalendar);
		m_dlgCalendar.SetWindowPos(NULL, rectCalendar.left + m_btnCalendar.GetImageSize().cx - 415 - 48, rectCalendar.top - 50, 415, 370, SWP_SHOWWINDOW ); 
		m_dlgCalendar.ShowWindow(SW_SHOW);

		CString strDate;
		m_etDateSet.GetWindowText(strDate);
		if ( strDate.IsEmpty() )
		{
			SYSTEMTIME sysTime;
			::GetLocalTime( &sysTime ); 
			m_dlgCalendar.SetDate( sysTime.wYear, sysTime.wMonth, sysTime.wDay );

// 			CTime tmCur = CTime::GetCurrentTime();
// 			m_dlgCalendar.SetDate( tmCur.GetYear(), tmCur.GetMonth(), tmCur.GetDay() );
		}
		else
		{
			s32 nYear = 0, nMonth = 0, nDay = 0;
			sscanf( strDate, "%d年%d月%d日", &nYear, &nMonth, &nDay );  
			m_dlgCalendar.SetDate( nYear, nMonth, nDay );
		}
	}
	else
	{
		m_dlgCalendar.SetWindowPos(NULL,0,0,0,0,SWP_NOMOVE|SWP_NOACTIVATE);
	}
}

void CMeetTemplateLogic::OnBtnCheckOrderConf() 
{
	m_btnCalendar.EnableWindow(TRUE);	
	m_btnPlusTime.EnableWindow(TRUE);
	m_btnSubTime.EnableWindow(TRUE);
	m_etSetHour.EnableWindow(TRUE);
	m_edtDotHour.EnableWindow(TRUE);
	m_etSetMin.EnableWindow(TRUE);
	m_etDateSet.EnableWindow(TRUE);

	CString strSetTime;
	m_etDateSet.GetWindowText(strSetTime);
	if ( strSetTime.IsEmpty() )
	{
		SYSTEMTIME sysTime;
		::GetLocalTime( &sysTime );

// 		CTime tmCur = CTime::GetCurrentTime();
// 		CString strDate = tmCur.Format("%Y年%m月%d日");

		CString strDate;
		strDate.Format( "%d年%d月%d日", sysTime.wYear, sysTime.wMonth, sysTime.wDay );
		m_etDateSet.SetWindowText(strDate);

		s32 nHour = sysTime.wHour;//tmCur.GetHour();
		s32 nMin = sysTime.wMinute;//tmCur.GetMinute();
		s8 chCurHour[3] = { 0 };
		sprintf( chCurHour, "%.2d", nHour );
		s8 chCurMinute[3] = { 0 };
		sprintf( chCurMinute, "%.2d", nMin );
		
		m_etSetHour.SetWindowText(chCurHour);
		m_etSetMin.SetWindowText(chCurMinute);
	}
}

void CMeetTemplateLogic::OnBtnCheckCurConf() 
{
	m_btnCalendar.EnableWindow(FALSE);	
	m_btnPlusTime.EnableWindow(FALSE);
	m_btnSubTime.EnableWindow(FALSE);
	m_etSetHour.EnableWindow(FALSE);
	m_edtDotHour.EnableWindow(FALSE);
	m_etSetMin.EnableWindow(FALSE);
	m_etSetHour.SetWindowText("");
	m_etSetMin.SetWindowText("");
	m_etDateSet.EnableWindow(FALSE);
	m_etDateSet.SetWindowText("");
}

void CMeetTemplateLogic::OnDestroy() 
{
	CDlgChild::OnDestroy();

	m_tpTmpRefreshList.Clear();
	m_tpTmpShowList.Clear();
	m_tpTmpSearchList.Clear();

	SAFE_RELEASE(m_plsMeetTmp);
	SAFE_RELEASE(m_plsMeetEpRight);
	SAFE_RELEASE(m_plsMeetPollingRight);
	SAFE_RELEASE(m_plsLocalAddrbook);
	SAFE_RELEASE(m_plsPollingLeft);
	SAFE_RELEASE(m_plsDiscussLeft);
	SAFE_RELEASE(m_pLetterTmp);
	SAFE_RELEASE(m_pLetterPolling);
	SAFE_RELEASE(m_pLetterAddrbook);
	SAFE_RELEASE(m_pLetterDiscuss);

	::DeleteCriticalSection(&g_csLock);

	UN_REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickTmpLstItem");	
	UN_REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickTmpLstItemIcon" );
	UN_REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickAddrbookLstItem" );
	UN_REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickAddrbookLstItemIcon" );
	UN_REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickPollingPageLeftLstItem" );
	UN_REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickPollingPageLeftLstItemIcon" );
	UN_REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickGroupPageDelItemIcon" );
	UN_REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickPollingPageDelItemIcon" );
	UN_REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickPollingPageDelItem" );
	UN_REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickDiscussPageLeftLstItem" );
	UN_REG_MSG_HANDLER( "CMeetTemplateLogic::OnClickDiscussPageLeftLstItemIcon" );

	m_dlgCalendar.Clean();
}

void CMeetTemplateLogic::OnBtnStartConf() 
{
	if( m_pconfCtrlIF != NULL )
	{
		m_btnStartConf.EnableWindow(FALSE);

		u16 nCurTmpId = m_tSelTemplate.m_wID;
		m_pconfCtrlIF->StartTemplateConfReq(nCurTmpId);
	}
}

LRESULT CMeetTemplateLogic::OnStartConfResult(WPARAM wParam, LPARAM lParam)
{
	m_btnStartConf.EnableWindow(TRUE);
	TStartConfResult tRe = *reinterpret_cast<tagTStartConfResult*>(wParam);
    u32 dwErrID = NO_ERROR;
	CString strError;
    switch(tRe.m_emReason)
    {
    case TP_StartConf_UnKonw:
		{
			strError = "开启会议失败";//"未知错误";   //2012-8-7 SE石文娟确认未知错误不做提示 by yjj
		}
        break;
    case TP_StartConf_ConfTemplateUnExist:
		{
			strError = "开启会议失败：会议模板不存在";
		}
        break;
    case TP_StartConf_ConfFull:
		{
		   strError = "开启会议失败：会议已满";
		}
        break;
    case TP_StartConf_ResourceFull:
		{
			strError = "开启会议失败：媒体资源不足";
		}
        break;
    case TP_StartConf_ConfExist:
		{
			strError = "开启会议失败：会议已存在";
		}
        break;
	case TP_StartConf_SipUnReg:
		{
			strError = "开启会议失败：未注册网呈服务器";
		}
        break;
	case TP_StartConf_Success:
		{
			strError = "会议开启成功";

			TCMSConfTemplate* pTCmsConfTmp = (TCMSConfTemplate*)GetConfTemplateByID(m_tSelTemplate.m_wID);
			if ( NULL  == pTCmsConfTmp )
			{
				return S_OK;
			}

			m_tSelTemplate = *pTCmsConfTmp;
		    SetSelectedTmpDataToScanfPage(m_tSelTemplate);

			::SendMessage( g_cmainWnd->m_dlgMeetInfo, UI_UMS_REFRESH_CONF_LIST, 0, 0 );
		}
		break;
    default:
		{	
			strError = "开启会议失败";
			break;
		}
    }

	MESSAGEWND( strError );
	return 0L;
}

void CMeetTemplateLogic::OnSearchEditChange()
{
	CString strSearchName;
	m_etSearch.GetWindowText( strSearchName );

	if ( ( NULL == m_plsMeetTmp ) || ( NULL == m_plsLocalAddrbook ) )
	{
		return;
	}
	
	if ( m_plsMeetTmp->IsWindowVisible() )
	{
		if ( !strSearchName.IsEmpty() )
		{
			m_tpTmpSearchList.Clear();
			TplArray<TTPConfTemplate> tpShowList;
			tpShowList = m_tpTmpRefreshList;
			
			m_plsMeetTmp->SetYOffset( 0 );
			
			for ( s32 nIndex = 0; nIndex < tpShowList.Size(); nIndex++ )
			{
				TCMSConfTemplate tTPConfTmp;
				tTPConfTmp = tpShowList.GetAt(nIndex);
				CString strItemName;
				strItemName = tpShowList.GetAt(nIndex).m_achConfName;
				
				BOOL bFind = FALSE;			
				bFind = CUmcwebCommon::HZPYMatchList( strSearchName, strItemName );
				if ( bFind )
				{		
					m_tpTmpSearchList.Add( &tTPConfTmp );
				}
			}
		}
		UpdateTmpShowList();
		UpdateUIState();

		//输入则置其他控件页面为初始列表
		m_vecLocalbookShowList = m_vecLocalbookRefreshList;
		UpdateAddrbookShowList();
		UpdatePollingLeftShowList( m_mapEpList,  TRUE );
		UpdateDiscussShowListData();
		UpdateDiscussLeftShowList( m_mapDiscussList,  TRUE );

		if ( !strSearchName.IsEmpty() )
		{
			m_plsMeetTmp->SetYOffset( 0 );
		}
	}
	else if( m_plsLocalAddrbook->IsWindowVisible() )
	{
		if ( !strSearchName.IsEmpty() )
		{	
			m_plsLocalAddrbook->SetYOffset( 0 );
			FilterAddrbookList();
		}
		UpdateAddrbookShowList();	
		
		//输入则置其他控件页面为初始列表
		m_tpTmpShowList.Clear();
		m_tpTmpShowList = m_tpTmpRefreshList;
		UpdateTmpShowList();
		UpdateUIState();
		UpdatePollingLeftShowList( m_mapEpList,  TRUE );
		UpdateDiscussShowListData();
		UpdateDiscussLeftShowList( m_mapDiscussList,  TRUE );
	}
	else if( m_plsPollingLeft->IsWindowVisible() )
	{
		FilterPollingLeftList();
	}
	else if ( m_plsDiscussLeft->IsWindowVisible() )
	{
		FilterDiscussLeftList();
	}
}

void CMeetTemplateLogic::OnConfRateEditChange()
{
	CString strRate;
	m_etConfRate.GetWindowText(strRate);

	if ( "" != strRate )
	{
		s32 nRate = atoi(strRate);
		s32 nLen = strRate.GetLength();
		if ( (strRate.GetAt(nLen - 1) > '9') || (strRate.GetAt(nLen - 1) < '0') )
		{
			CString strRateShow = strRate.Left(nLen - 1);
			nRate = atoi(strRateShow);
			m_etConfRate.SetWindowText(strRateShow);
		}

		if ( nRate > 8192 )
		{
			m_etConfRate.SetWindowText("8192");
		}  
	} 

	m_etConfRate.SetSel(-1);
}

void CMeetTemplateLogic::OnShowRateEditChange()
{
	CString strRate;
	m_etShowRate.GetWindowText(strRate);

	if ( "" != strRate )
	{
		s32 nRate = atoi(strRate);
		s32 nLen = strRate.GetLength();
		if ( (strRate.GetAt(nLen - 1) > '9') || (strRate.GetAt(nLen - 1) < '0') )
		{
			CString strRateShow = strRate.Left(nLen - 1);
			nRate = atoi(strRateShow);
			m_etShowRate.SetWindowText(strRateShow);
		}
		
		if ( nRate > 8192 )
		{
			m_etShowRate.SetWindowText("8192");
		}  
	}     

	m_etShowRate.SetSel(-1);
}

void CMeetTemplateLogic::FilterPollingLeftList()
{
	CString strSearchName;
	m_etSearch.GetWindowText( strSearchName );
	if ( !strSearchName.IsEmpty() )
	{	
		std::map<u16,CString> mapSearchList;
		m_mapEpSearchList.clear();
		
		m_plsPollingLeft->SetYOffset( 0 );
		
		std::map<u16,CString>::iterator iter;
		for ( iter = m_mapEpList.begin(); iter != m_mapEpList.end(); iter++ )
		{
			u16 nPollingId = iter->first;
			CString strItemName;
			strItemName = iter->second;
			
			BOOL bFind = FALSE;			
			bFind = CUmcwebCommon::HZPYMatchList( strSearchName, strItemName );
			if ( bFind )
			{		
				m_mapEpSearchList.insert( std::make_pair<u16,CString>( nPollingId, strItemName ) );
			}
		}
		
		//m_mapEpSearchList移除轮询列表中的数据   得出查询集
		if ( m_vecTurnList.size() != 0 )
		{
			CString strSearchItem;
			u16 wKey = 0;
			iter = m_mapEpSearchList.begin();
			for ( ; iter != m_mapEpSearchList.end(); )
			{
				wKey = iter->first;
				strSearchItem = iter->second;
				std::vector<CString>::iterator iterFind = find( m_vecTurnList.begin(), m_vecTurnList.end(), strSearchItem );
				if ( iterFind != m_vecTurnList.end() )
				{
					iter = m_mapEpSearchList.erase( iter );
				}
				else
				{
					++iter;
				}
			}
		}
		
		UpdatePollingLeftShowList( m_mapEpSearchList,  TRUE );
	}
	else
	{
		UpdatePollingLeftShowList( m_mapEpList,  TRUE );
	}
	
	m_nTurnLeftListCount = m_vecTurnList.size();
	
	//输入则置其他控件页面为初始列表
	m_vecLocalbookShowList = m_vecLocalbookRefreshList;
	UpdateAddrbookShowList();	
	m_tpTmpShowList.Clear();
	m_tpTmpShowList = m_tpTmpRefreshList;
	UpdateTmpShowList();
	UpdateUIState();
}

void CMeetTemplateLogic::FilterAddrbookList()
{
	CString strSearchName;
	m_etSearch.GetWindowText( strSearchName );

	if ( !strSearchName.IsEmpty() )
	{	
		m_plsLocalAddrbook->SetYOffset( 0 );
		
		m_vecLocalbookSearchList.clear();
		vector<TAddrItem> vctShowList;
		vctShowList = m_vecLocalbookRefreshList;
		
		for ( int i = 0; i < vctShowList.size(); i++ )
		{
			BOOL bMatchNum = FALSE;
			CString strItemName;
			TAddrItem tAddrItem = vctShowList.at(i);
			if ( tAddrItem.emItemType == emEntryItem )
			{
				//名称为空用E164号匹配
				if ( strcmp( tAddrItem.tAddrInfo.achEntryName, "" ) == 0 )
				{
					strItemName = tAddrItem.tAddrInfo.achE164;
				}
				else
				{
					strItemName = tAddrItem.tAddrInfo.achEntryName;
					bMatchNum = TRUE;
				}		
			}
			else
			{
				strItemName = tAddrItem.tGroupInfo.achGroupName;
			}
			BOOL bFindName = FALSE;	
			BOOL bFindNum = FALSE;
			bFindName = CUmcwebCommon::HZPYMatchList( strSearchName, strItemName );
			if ( bFindName )
			{		
				m_vecLocalbookSearchList.push_back( tAddrItem );
			}
			else if ( bMatchNum )
			{
				//名字没有匹配到
				strItemName = tAddrItem.tAddrInfo.achE164;
				bFindNum = CUmcwebCommon::HZPYMatchList( strSearchName, strItemName );
				if ( bFindNum )
				{		
					m_vecLocalbookSearchList.push_back( tAddrItem );
				}
		    }
		}
	}
}

void CMeetTemplateLogic::FilterDiscussLeftList()
{
	UpdateDiscussShowListData();

	CString strSearchName;
	m_etSearch.GetWindowText( strSearchName );
	if ( !strSearchName.IsEmpty() )
	{	
		m_mapDiscussSearchList.clear();
		m_plsDiscussLeft->SetYOffset( 0 );
		
		std::map<u16,CString>::iterator iter;
		for ( iter = m_mapDiscussList.begin(); iter != m_mapDiscussList.end(); iter++ )
		{
			u16 nDiscussId = iter->first;
			CString strItemName = iter->second;
			
			BOOL bFind = CUmcwebCommon::HZPYMatchList( strSearchName, strItemName );
			if ( bFind )
			{		
				m_mapDiscussSearchList.insert( std::make_pair<u16,CString>( nDiscussId, strItemName ) );
			}
		}
		
		UpdateDiscussLeftShowList( m_mapDiscussSearchList,  TRUE );
	}
	else
	{
		UpdateDiscussLeftShowList( m_mapDiscussList,  TRUE );
	}
}

void CMeetTemplateLogic::UpdateTmpShowList()
{
	CString strText;
	m_etSearch.GetWindowText( strText );
	m_tpTmpShowList.Clear();
	if ( strText.IsEmpty() )
	{
		m_tpTmpShowList = m_tpTmpRefreshList;
	}
	else
	{
		m_tpTmpShowList = m_tpTmpSearchList;
	}

	vector<TCMSConfTemplate> vectConfTemplate;
	for( s32 nIndex = 0; nIndex < m_tpTmpShowList.Size(); nIndex++ )
	{
		TCMSConfTemplate tCmsConfTmp = *((TCMSConfTemplate*)&m_tpTmpShowList.GetAt(nIndex));
		vectConfTemplate.push_back(tCmsConfTmp);
	}
	
	Value_TouchListConfTemp val_tmpList( &vectConfTemplate, "CMeetTemplateLogic::OnClickTmpLstItem", NULL );
	val_tmpList.m_setClickedName = m_setSelectedTmpIconItem;
	if ( NULL != m_plsMeetTmp )
	{
		m_plsMeetTmp->SetData( val_tmpList );
	}

	//刷新列表完成跳转
	if ( m_emOperateFlag == em_SCANF_PAGE_STATUS )
	{
		BOOL bMatch = FALSE;
		for( s32 nIndexSort = 0; nIndexSort < m_tpTmpShowList.Size(); nIndexSort++ )
		{
			TCMSConfTemplate tCmsConf = *((TCMSConfTemplate*)&m_tpTmpShowList.GetAt(nIndexSort));
			
			if ( strcmp( tCmsConf.m_achConfName, m_tSelTemplate.m_achConfName) == 0 )
			{
				if ( m_plsMeetTmp != NULL )
				{
					m_plsMeetTmp->SetSelItem( m_tSelTemplate.m_wID );
					bMatch = TRUE;
					SetSelectedTmpDataToScanfPage(m_tSelTemplate);
					break;
				}
			}
		}
		if ( !bMatch )
		{
			m_tSelTemplate.Clear();
			m_plsMeetTmp->SetSelItem( -1 );
			ResetInitPage();
		}
	}
}

void CMeetTemplateLogic::UpdatePollingLeftShowList( std::map<u16,CString>& mapEpList, BOOL bIsShowIcon )
{
// 	if ( !m_bSwitchPolling )
// 	{
// 		return;
// 	}

	//会场列表
	TEpAddrList  tCnsLst;
	for ( std::map<u16,CString>::iterator iter = mapEpList.begin(); iter != mapEpList.end(); iter++ )
	{
		LPCTSTR strEpName = iter->second;

		EmTpAliasType emAliasType;
		if( CCallAddr::IsValidE164(strEpName) )
		{
			emAliasType = tp_Alias_e164;	
		}
		else
		{
			emAliasType = tp_Alias_h323;
		}

		tCnsLst.Add(emAliasType, (s8*)strEpName);
	}
	
	Value_TouchListTempCns val_TempCns( tCnsLst );
	val_TempCns.m_nImageId = IDR_PNG_LIST_ADD;
	//val_TempCns.m_bDrag = TRUE;
	if ( !bIsShowIcon )
	{
		val_TempCns.m_nImageId = 0;
	}

	//已经添加到轮询列表中的数据图标改变  不能重复添加
	val_TempCns.m_setClickedName.clear();
	for ( s32 nIndex = 0; nIndex < m_vecTurnList.size(); nIndex++ )
	{
		CString strTurnItemName = m_vecTurnList[nIndex];
		val_TempCns.m_setClickedName.insert(strTurnItemName);
	}

	val_TempCns.m_strClickItemFunc = "CMeetTemplateLogic::OnClickPollingPageLeftLstItem";
	m_plsPollingLeft->SetData( val_TempCns);
 	m_plsPollingLeft->SetDragEnable( TRUE );

	//更新全部添加按钮   过滤后    全部添加按钮状态控制
	if( m_plsPollingLeft->IsWindowVisible() )
	{
		CString strSearchName;
		m_etSearch.GetWindowText( strSearchName );
		
		if ( !strSearchName.IsEmpty() )
		{	
			//判断列 表空
			if ( m_mapEpSearchList.size() == 0 )
			{
				m_btnAllAdd.EnableWindow(FALSE);
			}
			else
			{
				if( m_vecTurnList.size() != m_nTurnLeftListCount )
				{		
					if ( m_vecTurnList.size() - m_nTurnLeftListCount == m_mapEpSearchList.size() )
					{
						m_btnAllAdd.EnableWindow(FALSE);
					}
					else
					{
						m_btnAllAdd.EnableWindow(TRUE);
					}
				}
				else
				{
					m_btnAllAdd.EnableWindow(TRUE);
				}
			}
		}
		else
		{
			if ( m_mapEpList.size() - m_vecTurnList.size() > 0 )
			{
				m_btnAllAdd.EnableWindow(TRUE);
			}
			else
			{
				m_btnAllAdd.EnableWindow(FALSE);
			}
		}
	}
}

void CMeetTemplateLogic::UpdateDiscussLeftShowList( std::map<u16,CString>& mapEpList, BOOL bIsShowIcon )
{
	TEpAddrList  tCnsLst;
	for ( std::map<u16,CString>::iterator iter = mapEpList.begin(); iter != mapEpList.end(); iter++ )
	{
		LPCTSTR strEpName = iter->second;
		
		EmTpAliasType emAliasType;
		if( CCallAddr::IsValidE164(strEpName) )
		{
			emAliasType = tp_Alias_e164;	
		}
		else
		{
			emAliasType = tp_Alias_h323;
		}
		
		tCnsLst.Add(emAliasType, (s8*)strEpName);
	}

	Value_TouchListTempCns val_TempCns( tCnsLst );
	val_TempCns.m_nImageId = IDR_PNG_LIST_NOCHECK;

	std::set<CString> setDiscussSelectedItem;
	std::map<u16,CString>::iterator iterDiscussSelItem;
	for ( iterDiscussSelItem = m_mapDiscussSelItem.begin(); iterDiscussSelItem != m_mapDiscussSelItem.end(); iterDiscussSelItem++ )
	{
		CString strDiscussName = iterDiscussSelItem->second;
		u16 wDiscussId = FindConfDiscussListByAlias(strDiscussName);
		if ( INVALID_WORD != wDiscussId )
		{
			setDiscussSelectedItem.insert(strDiscussName);
		}	
	}

	val_TempCns.m_setSelectedName = setDiscussSelectedItem;

	if ( !bIsShowIcon )
	{
		val_TempCns.m_nImageId = 0;
	}
	val_TempCns.m_strClickItemFunc = "CMeetTemplateLogic::OnClickDiscussPageLeftLstItem";
	m_plsDiscussLeft->SetData( val_TempCns);
	m_plsDiscussLeft->SetDragEnable( TRUE );
}

BOOL CMeetTemplateLogic::OnCommand(WPARAM wParam, LPARAM lParam) 
{
    if ( HIWORD(wParam) == EN_CHANGE )
    {
        if ( (HWND)lParam == m_etSetHour.GetSafeHwnd() )
        {   
            CString strHour;
            m_etSetHour.GetWindowText(strHour);
            s32 nHour;
            nHour = atoi(strHour);
            if ( nHour > 23 )
            {
                m_etSetHour.SetWindowText("23");
            }
			m_etSetHour.SetSel(-1);
        }
        else if ( (HWND)lParam == m_etSetMin.GetSafeHwnd() )
        {            
            
            CString strMin;
            m_etSetMin.GetWindowText(strMin);
            s32 nMin;
            nMin = atoi(strMin);
            if ( nMin > 59 )
            {
                m_etSetMin.SetWindowText("59");
            }       
			m_etSetMin.SetSel(-1);
        }
        else if ( (HWND)lParam == m_etPollingTime.GetSafeHwnd() )
        {
            CString strInterval;
            m_etPollingTime.GetWindowText(strInterval);
            s32 nIntervalNum;
            nIntervalNum = atoi(strInterval);
            if ( nIntervalNum > 7200 )
            {
                m_etPollingTime.SetWindowText( _T("7200") );
            }
			m_etPollingTime.SetSel(-1);
			//小于5未做判断

        }
		else if ( (HWND)lParam == m_etSearch.GetSafeHwnd() )
		{
			if ( HIWORD(wParam) == EN_CHANGE )
			{
				m_setSelectedTmpIconItem.clear();
				OnSearchEditChange();
				UpdateUIState();
			}
		}
		else if ( (HWND)lParam == m_etConfRate.GetSafeHwnd() )
        { 
			OnConfRateEditChange();
        }
		else if ( (HWND)lParam == m_etShowRate.GetSafeHwnd() )
        {      
			OnShowRateEditChange();
        }
    }

	return CDlgChild::OnCommand(wParam, lParam);
}

LRESULT CMeetTemplateLogic::OnNoSelResultNotify(WPARAM wParam, LPARAM lParam)
{
	HWND hWnd = (HWND)wParam;
	if ( m_emOperateFlag == em_SCANF_PAGE_STATUS )
	{
		if ( m_plsMeetTmp->GetSafeHwnd() == hWnd )
		{
			m_tSelTemplate.Clear();
			ResetInitPage();
		}
	}
	else
	{
		if( m_plsMeetPollingRight->GetSafeHwnd() == hWnd )
		{
			m_nCurPollingListSortRow = 0;
			SetSortControlDisable();
		}
	}
	m_plsMeetTmp->SetFocus();

	return 0L;
}

// BOOL CMeetTemplateLogic::HomeMeetExistInEpList(const CString& strHomeMeetName)
// {
// //	TEpAddrList  tCnsLst;
// 	CString strEpName;
// 	for ( std::map<u16,CString>::iterator iter = m_mapEpList.begin(); iter != m_mapEpList.end(); iter++ )
// 	{
// 		strEpName = iter->second;
// 		if ( strHomeMeetName == strEpName )
// 		{
// 			CString strError;
// 			int nRet = 0;
// 			strError = "当前所选主会场已经存在分会场列表中，不能添加";
// 			MESSAGEWNDBOX( strError, this , nRet , FALSE );
// 			return TRUE;
// 		}
// 	}
// 	
// 	return FALSE;
// }

u16 CMeetTemplateLogic::FindMeetInEpList(const CString& strMeetName, const CString& strMeetNum, BOOL bHomeMeet)
{
	if ( strMeetName.IsEmpty() && strMeetNum.IsEmpty() )
	{
		return TP_CONF_MAX_EPNUM;
	}
	
	BOOL bFind = FALSE;
	u16 wEpID = TP_CONF_MAX_EPNUM;
	for ( std::map<u16,TEpAddr>::iterator iter = m_mapEpInfoList.begin(); iter != m_mapEpInfoList.end(); iter++ )
	{
		wEpID = iter->first;
		if ( 0 == wEpID )
		{
			continue;
		}

		CString strEpName = iter->second.m_tAlias.m_abyAlias;
		CString strEpNum = iter->second.m_tE164.m_abyAlias;
// 		if ( !strEpName.IsEmpty() && strMeetName == strEpName )
// 		{
// 			bFind = TRUE;
// 			break;
// 		}
// 		else if ( !strEpNum.IsEmpty() && strMeetNum == strEpNum )
// 		{
// 			bFind = TRUE;
// 			break;
// 		}

		//经yjj确认，分会场同时显示名称和e164号，也同时匹配名称和e164号 -- 20141023 by xhx
		if ( strMeetName == strEpName &&  strMeetNum == strEpNum )
		{
			bFind = TRUE;
			break;
		}
	}

	if ( bFind )
	{
		if ( bHomeMeet )
		{
			CString strError;
			int nRet = 0;
			strError = "当前所选主会场已经存在分会场列表中，不能添加";
			MESSAGEWNDBOX( strError, this , nRet , FALSE );
		}

		return wEpID;
	}
	
	return TP_CONF_MAX_EPNUM;
}

void CMeetTemplateLogic::UpdateGroupEpInfoList(const CString& strAddrbookName, const CString& strAddrbookNum, u16 wEpID)
{
	if ( TP_CONF_MAX_EPNUM == wEpID )
	{
		return;
	}

	if ( strAddrbookName.IsEmpty() && strAddrbookNum.IsEmpty() )
	{
		return;
	}

	if ( TP_CONF_MAX_EPNUM != FindMeetInEpList(strAddrbookName, strAddrbookNum) )
	{
		return;
	}

	if ( 0 == wEpID )
	{
		m_mapEpInfoList.erase(wEpID);
	}

	TEpAddr tEpAddr;
	tEpAddr.m_tAlias.SetAlias(tp_Alias_h323, (LPCTSTR)strAddrbookName );
	tEpAddr.m_tE164.SetAlias(tp_Alias_e164, (LPCTSTR)strAddrbookNum );

	EnterCriticalSection(&g_csLock);
	m_mapEpInfoList.insert( std::make_pair<u16,TEpAddr>( wEpID, tEpAddr ) );
	LeaveCriticalSection(&g_csLock);
}

void CMeetTemplateLogic::OnBtnAllAdd() 
{
	std::map<u16,CString> mapEpList;
	CString strSearchName;
	m_etSearch.GetWindowText( strSearchName );
	if( strSearchName.IsEmpty() )
	{
		mapEpList = m_mapEpList;
	}
	else
	{
		mapEpList = m_mapEpSearchList;
	}

	std::map<u16,CString>::iterator iterEpList;
	for ( iterEpList = mapEpList.begin(); iterEpList != mapEpList.end(); iterEpList++ )
	{
		CString strEpName = iterEpList->second;
		std::vector<CString>::iterator iter = find( m_vecTurnList.begin(), m_vecTurnList.end(), strEpName ); 
		if ( iter == m_vecTurnList.end() )
		{
			EnterCriticalSection(&g_csLock);
			m_vecTurnList.push_back(strEpName);
			LeaveCriticalSection(&g_csLock);
		}
	}
	
	if ( m_vecTurnList.size() > 0 )
	{
		::SendMessage( this->m_hWnd, WM_DEF_UPDATEPOLLINGLISTCONTROL, 0, 0 ); //发送更新会场列表的消息

		UpdatePollingLeftIcon();
	}

	m_nCurPollingListSortRow = m_vecTurnList.size();
	m_plsMeetPollingRight->SetSelItem(m_nCurPollingListSortRow-1); 
	UpdateSortControlUIState();

	m_btnAllAdd.EnableWindow(FALSE);
}

void CMeetTemplateLogic::ShowSortControl(BOOL bShow)
{
	m_btnSetTop.ShowWindow(bShow);
	m_btnSetBottom.ShowWindow(bShow);
	m_btnMoveUp.ShowWindow(bShow);
	m_btnMoveDown.ShowWindow(bShow);
	m_btnRemoveAll.ShowWindow(bShow);
}

u16 CMeetTemplateLogic::UpPollControl( u16 wCurRow )
{
	if ( wCurRow - 2 < 0)
	{
		return ERR_CMS_CNSID_INVALID;
	}

	CString strDescName;
	strDescName = m_vecTurnList[wCurRow-2];

	CString strSrcName;
	strSrcName = m_vecTurnList[wCurRow-1];

	m_vecTurnList[wCurRow-1] = strDescName;
	m_vecTurnList[wCurRow -2] = strSrcName;
	m_nCurPollingListSortRow = wCurRow - 1;
	m_plsMeetPollingRight->SetSelItem( wCurRow - 2 );

	UpdateSortControlUIState();

	return NO_ERROR;
}

u16 CMeetTemplateLogic::DownPollControl( u16 wCurRow )
{
	if ( ( wCurRow - 1 < 0 ) || ( wCurRow >= m_vecTurnList.size() ) )
	{
		return ERR_CMS_CNSID_INVALID;
	}

	CString strDescName;
	strDescName = m_vecTurnList[wCurRow];
	
	CString strSrcName;
	strSrcName = m_vecTurnList[wCurRow-1];
	
	m_vecTurnList[wCurRow - 1] = strDescName;
	m_vecTurnList[wCurRow] = strSrcName;
	m_nCurPollingListSortRow = wCurRow + 1;
	m_plsMeetPollingRight->SetSelItem( wCurRow );

	UpdateSortControlUIState();

    return NO_ERROR;
}

u16 CMeetTemplateLogic::TopPollControl(u16 wCurRow )
{
	if ( wCurRow - 2 < 0)
	{
		return ERR_CMS_CNSID_INVALID;
	}
	
	CString strSrcName;
	strSrcName = m_vecTurnList[wCurRow-1];
	
	for ( u16 nIndex = wCurRow - 1; nIndex> 0; nIndex--)
    {
		m_vecTurnList[nIndex] = m_vecTurnList[nIndex -1];
    }

	m_vecTurnList[0] = strSrcName;
	m_nCurPollingListSortRow = 1;
	m_plsMeetPollingRight->SetSelItem( 0 );

	UpdateSortControlUIState();

    return NO_ERROR;
}

u16 CMeetTemplateLogic::BottomPollControl( u16 wCurRow )
{
   	if ( wCurRow - 1 < 0)
	{
		return ERR_CMS_CNSID_INVALID;
	}
	
	s32 nTurnListCount = m_vecTurnList.size();
	CString strSrcName;
	strSrcName = m_vecTurnList[wCurRow-1];
	
	for ( u16 nIndex = wCurRow - 1; nIndex < nTurnListCount - 1; nIndex++)
    {
        m_vecTurnList[nIndex] = m_vecTurnList[nIndex + 1];
    }
	
	m_vecTurnList[nTurnListCount - 1] = strSrcName;
	m_nCurPollingListSortRow = nTurnListCount;
	m_plsMeetPollingRight->SetSelItem( nTurnListCount - 1 );

	UpdateSortControlUIState();

    return NO_ERROR;
}

void CMeetTemplateLogic::OnBtnSetTop()
{
	if ( m_nCurPollingListSortRow <= 0 )
	{
		return;
	}

	TopPollControl(m_nCurPollingListSortRow);
	UpdatePollingList( 0, 0 );
}

void CMeetTemplateLogic::OnBtnSetBottom() 
{
	if ( m_nCurPollingListSortRow <= 0 )
	{
		return;
	}

	BottomPollControl(m_nCurPollingListSortRow);
	UpdatePollingList( 0, 0 );
}

void CMeetTemplateLogic::OnBtnMoveUp() 
{
	if ( m_nCurPollingListSortRow <= 0 )
	{
		return;
	}

	UpPollControl(m_nCurPollingListSortRow);
	UpdatePollingList( 0, 0 );
}

void CMeetTemplateLogic::OnBtnMoveDown() 
{
	if ( m_nCurPollingListSortRow <= 0 )
	{
		return;
	}

	DownPollControl(m_nCurPollingListSortRow);
	UpdatePollingList( 0, 0 );
}

void CMeetTemplateLogic::OnBtnRemoveAll() 
{
	m_vecTurnList.clear();

	//清空轮询列表
	TCMSConfTemplate tCnsTemplate;
	Value_TouchListTempPoll val_TempPoll( tCnsTemplate );
	if ( NULL != m_plsMeetPollingRight )
	{
		m_plsMeetPollingRight->SetData( val_TempPoll );
	}

	ShowSortControl(FALSE);

	UpdatePollingLeftIcon();

	CString strSearchName;
	m_etSearch.GetWindowText( strSearchName );
	if ( strSearchName.IsEmpty() )
	{
		m_btnAllAdd.EnableWindow(TRUE);
	}
	else
	{
		if ( !strSearchName.IsEmpty() )
		{	
			FilterPollingLeftList();
		}
	}
}

HRESULT CMeetTemplateLogic::OnHideWndNotify( WPARAM wparam, LPARAM lparam )
{
	if ( m_dlgCalendar.GetSafeHwnd() != NULL )
	{
	    BOOL bRet = m_dlgCalendar.SetWindowPos(NULL, -30000, -30000, 0, 0, SWP_HIDEWINDOW|SWP_NOACTIVATE ); 
	}

	return S_OK;
}

LRESULT CMeetTemplateLogic::OnUpdateCalendarSelDate(WPARAM wParam, LPARAM lParam)
{
	CString strDate = m_dlgCalendar.GetDate();
	if ( !strDate.IsEmpty() )
	{
		m_etDateSet.SetWindowText(strDate);
	}
	
	return 0L;
}

LRESULT CMeetTemplateLogic::OnDiscussEpChange(WPARAM wParam, LPARAM lParam)
{
	EnterCriticalSection(&g_csLock);
	m_mapDiscussSelItem.clear();
	m_mapDiscussSelItem = *reinterpret_cast<std::map<u16,CString>*>(wParam);
	LeaveCriticalSection(&g_csLock);

	FilterDiscussLeftList();

	return 0L;
}

LRESULT CMeetTemplateLogic::OnSwitchDiscuss(WPARAM wParam, LPARAM lParam)
{
	m_bSwitchDiscuss = (BOOL)wParam;

//	CleanSearchList();
	
	//需求确认,off时也可编辑  -- 20140408
// 	if ( m_bSwitchDiscuss )
// 	{
//		UpdateDiscussLeftShowList( m_mapDiscussList,  TRUE );
//	} 
// 	else
// 	{
// 		if ( NULL == m_plsDiscussLeft )
// 		{
// 			return 0L;
// 		}
// 		
// 		TEpAddrList tCnsLst;
// 		Value_TouchListTempCns val_TempCns( tCnsLst );
// 		m_plsDiscussLeft->SetData( val_TempCns);
// 	}

//	m_etSearch.EnableWindow(m_bSwitchDiscuss);
	
	return 0L;
}

LRESULT CMeetTemplateLogic::OnDragEnd(WPARAM wParam, LPARAM lParam)
{
	s32 x = LOWORD(lParam);
	s32 y = HIWORD(lParam);
	CPoint point(x, y);

	switch( m_emTabFlag )
	{
	case em_Ep_PAGE:
		{
			CRect rectList( 0, 0, 0, 0 );
			HWND hWndList = m_plsMeetEpRight->GetSafeHwnd();
			if ( NULL != hWndList )
			{
				CWnd* pMeetEpRight = CWnd::FromHandle(hWndList);
				pMeetEpRight->GetWindowRect(&rectList);
			}
			
			if ( rectList.PtInRect( point ) )
			{ 
				if ( const Data_AddrItemInfo *pItemInfo = dynamic_cast<const Data_AddrItemInfo*>( (IData*)wParam ) ) 
				{
					ClickAddrbookLstItemIcon( pItemInfo );
					return NO_ERROR;
				}
			} 

			CRect rectEdit( 0, 0, 0, 0 );
			HWND hWndEdit = m_etHomeMeeting.GetSafeHwnd();
			if ( NULL != hWndEdit )
			{
				CWnd* pEditHomeMeeting = CWnd::FromHandle(hWndEdit);
				pEditHomeMeeting->GetWindowRect(&rectEdit);
			}
			
			if ( rectEdit.PtInRect( point ) )
			{
				if ( const Data_AddrItemInfo *pItemInfo = dynamic_cast<const Data_AddrItemInfo*>( (IData*)wParam ) ) 
				{
					m_etHomeMeeting.SetFocus();
					ClickAddrbookLstItemIcon( pItemInfo );
				}
			}
		}
		break;
	case em_POLLING_PAGE:
		{
			CRect rect;
			HWND hWnd = m_plsMeetPollingRight->GetSafeHwnd();
			if ( NULL != hWnd )
			{
				CWnd* pMeetPollingRight = CWnd::FromHandle(hWnd);
				pMeetPollingRight->GetWindowRect(&rect);
			}
			
			if ( rect.PtInRect( point ) )
			{ 
				if ( const Data_CnsAddr *pItemInfo = dynamic_cast<const Data_CnsAddr*>( (IData*)wParam ) ) 
				{
					ClickPollingPageLeftLstItemIcon( pItemInfo );
				}
			}
		}
		break;
	case em_DISCUSS_PAGE:
		{
			
		}
		break;
	default:
		break;
	}
	
    return NO_ERROR;
}

LRESULT CMeetTemplateLogic::OnEditSetFocus(WPARAM wParam, LPARAM lParam)
{
	if ( m_etAdaptRes.IsFocus() )
	{
		OnBtnMediaInfo();
	}

	return NO_ERROR;
}

LRESULT CMeetTemplateLogic::OnKillFoucs(WPARAM wParam, LPARAM lParam)
{
	if ( (HWND)wParam == m_etPollingTime.GetSafeHwnd() )
	{
		CString strTime;
		m_etPollingTime.GetWindowText(strTime);
		
		s32 nTime = atoi(strTime);
		if( nTime <= 5 )
		{
			nTime = 5;		
		}
		else if ( nTime >= 7200 )
		{
			nTime = 7200;
		}
		
		strTime.Empty();
		strTime.Format( "%d", nTime );
		m_etPollingTime.SetWindowText(strTime);
	}

	return NO_ERROR;
}

void CMeetTemplateLogic::UpdateUIState()
{
	s32 nSelSize = m_setSelectedTmpIconItem.size();
	if ( nSelSize > 0 )
	{
		m_btnDelete.EnableWindow(TRUE);
		
		if ( nSelSize == m_tpTmpShowList.Size() )
		{
			m_bIsAllSel = TRUE;
			m_btnAllSel.SetImage( IDR_PNG_BTN_CANCELALLSEL, IDR_PNG_BTN_CANCELALLSELDOWN, IDR_PNG_BTN_CANCELALLSELDIS );
		}
		else
		{
			m_bIsAllSel = FALSE;
			m_btnAllSel.SetImage( IDR_PNG_BTN_ALLSEL, IDR_PNG_BTN_ALLSELDOWN, IDR_PNG_BTN_ALLSELDIS );
		}
	}
	else
	{
		m_btnDelete.EnableWindow(FALSE);
		
		m_bIsAllSel = FALSE;
		m_btnAllSel.SetImage( IDR_PNG_BTN_ALLSEL, IDR_PNG_BTN_ALLSELDOWN, IDR_PNG_BTN_ALLSELDIS );
		m_btnAllSel.EnableWindow(FALSE);
	}
	
	if ( m_tpTmpShowList.Size() == 0 )
	{
		m_btnAllSel.EnableWindow(FALSE);
	}
	else
	{
		m_btnAllSel.EnableWindow(TRUE);
	}
}

void CMeetTemplateLogic::UpdateSortControlUIState()
{
	if ( m_vecTurnList[m_nCurPollingListSortRow-1] == m_vecTurnList[0] ) //禁用上移和置顶 
	{ 
		m_btnSetTop.EnableWindow(FALSE);
		m_btnMoveUp.EnableWindow(FALSE);
	}
	else 
	{
		m_btnSetTop.EnableWindow(TRUE);
		m_btnMoveUp.EnableWindow(TRUE);
	}
	
	s32 nPollingListItem = m_vecTurnList.size() - 1;
	if ( m_vecTurnList[m_nCurPollingListSortRow-1] == m_vecTurnList[nPollingListItem]  ) //禁用下移和置底
	{
		m_btnSetBottom.EnableWindow(FALSE);
		m_btnMoveDown.EnableWindow(FALSE);
	}
	else 
	{
		m_btnSetBottom.EnableWindow(TRUE);
		m_btnMoveDown.EnableWindow(TRUE);
	} 
}

void CMeetTemplateLogic::SetSortControlDisable()
{
	m_btnSetTop.EnableWindow(FALSE);
	m_btnMoveUp.EnableWindow(FALSE);
	m_btnSetBottom.EnableWindow(FALSE);
	m_btnMoveDown.EnableWindow(FALSE);
}

HRESULT CMeetTemplateLogic::OnBtnHold( WPARAM wparam, LPARAM lparam )
{
	if ( (HWND)wparam == m_btnPlusTime.GetSafeHwnd() )
    {
		OnBtnPlusTime();
    }
    else if ( (HWND)wparam == m_btnSubTime.GetSafeHwnd() )
    {
		OnBtnSubTime();
    }
	else if ( (HWND)wparam == m_btnSubConfRate.GetSafeHwnd() )
    {
		OnBtnSubConfRate();
    }
	else if ( (HWND)wparam == m_btnPlusConfRate.GetSafeHwnd() )
    {
		OnBtnPlusConfRate();
    }
	else if ( (HWND)wparam == m_btnSubShowRate.GetSafeHwnd() )
    {
		OnBtnSubShowRate();
    }
	else if ( (HWND)wparam == m_btnPlusShowRate.GetSafeHwnd() )
    {
		OnBtnPlusShowRate();
    }
	else if ( (HWND)wparam == m_btnSubPollingTime.GetSafeHwnd() )
    {
		OnBtnSubPollingTime();
    }
	else if ( (HWND)wparam == m_btnPlusPollingTime.GetSafeHwnd() )
    {
		OnBtnPlusPollingTime();
    }
    
   return 0;
}

HRESULT CMeetTemplateLogic::OnBtnHoldEnd( WPARAM wparam, LPARAM lparam )
{
	if ( (HWND)wparam == m_btnSubConfRate.GetSafeHwnd() || (HWND)wparam == m_btnPlusConfRate.GetSafeHwnd() )
    {
		m_etConfRate.SetFocus();
		m_etConfRate.SetSel( 0, -1 );
    }
	else if ( (HWND)wparam == m_btnSubShowRate.GetSafeHwnd() || (HWND)wparam == m_btnPlusShowRate.GetSafeHwnd() )
    {
		m_etShowRate.SetFocus();
		m_etShowRate.SetSel( 0, -1 );
    }
	else if ( (HWND)wparam == m_btnSubPollingTime.GetSafeHwnd() || (HWND)wparam == m_btnPlusPollingTime.GetSafeHwnd() )
    {
		m_etPollingTime.SetFocus();
		m_etPollingTime.SetSel( 0, -1 );
    }
	else
	{
		switch( m_emCurFocus )
		{
		case em_Focus_Minute:
			{
				m_etSetMin.SetFocus();
				m_etSetMin.SetSel( 0, -1 );
				break;
			}
		case em_Focus_Hour:
			{
				m_etSetHour.SetFocus();
				m_etSetHour.SetSel( 0, -1 );
				break;
			}
	   }
	}

    return 0;
}

void CMeetTemplateLogic::OnSetfocusEditHour() 
{
    m_emCurFocus = em_Focus_Hour;
}

void CMeetTemplateLogic::OnSetfocusEditMinute() 
{
    m_emCurFocus = em_Focus_Minute;
}

void CMeetTemplateLogic::OnBtnMediaInfo()
{
	if ( em_NEW_PAGE_STATUS == m_emOperateFlag )
	{
		::SendMessage( m_dlgMediaCfg, WM_DEF_SENDTMPINFOTOPAGE, (WPARAM)&m_tNewTemplate, (LPARAM)m_emOperateFlag );
	}
	else
	{
		::SendMessage( m_dlgMediaCfg, WM_DEF_SENDTMPINFOTOPAGE, (WPARAM)&m_tSelTemplate, (LPARAM)m_emOperateFlag );
	}

	m_dlgMediaCfg.ShowWindow(SW_SHOW);
	
	SetMediaCfgHide(FALSE);
}

void CMeetTemplateLogic::SetMediaCfgHide(BOOL bHide)
{
	m_btnReturn.ShowWindow(!bHide);

	m_stTemplateRightTitle.ShowWindow(bHide);

	if( em_SCANF_PAGE_STATUS  == m_emOperateFlag )
	{
		ShowMeetInfoScanfPage(bHide);
		
		m_btnMeetingInfo.ShowWindow(bHide);
		m_btnGroupInfo.ShowWindow(bHide);
		m_btnPollingInfo.ShowWindow(bHide);
		m_btnDiscussInfo.ShowWindow(bHide);
		m_btnStartConf.ShowWindow(bHide);
		m_btnEdit.ShowWindow(bHide);
	}
	else
	{
		SetMediaInfoBtnPos(FALSE);
		SetRateInfoPos(FALSE);
		ShowMeetInfoEditPage(bHide);

		m_btnMeetingInfo.ShowWindow(bHide);
		m_btnGroupInfo.ShowWindow(bHide);
		m_btnPollingInfo.ShowWindow(bHide);
		m_btnDiscussInfo.ShowWindow(bHide);
		m_btnSave.ShowWindow(bHide);
		m_btnCancel.ShowWindow(bHide);
	}

	if ( em_SCANF_PAGE_STATUS == m_emOperateFlag )
	{
		m_btnEdit.ShowWindow(SW_SHOW);
		m_btnSave.ShowWindow(SW_HIDE);
		m_btnCancel.ShowWindow(SW_HIDE);
	}
	else
	{
		m_btnEdit.ShowWindow(SW_HIDE);
		m_btnSave.ShowWindow(SW_SHOW);
		m_btnCancel.ShowWindow(SW_SHOW);
	}
}

void CMeetTemplateLogic::OnBtnReturn()
{
	SetMediaCfgHide(TRUE);

	UpdateResUsedCountToControl(m_dlgMediaCfg.GetCheckResNum());

	TCMSConfTemplate* pTemplate =  m_dlgMediaCfg.GetSelTemplate();
	if ( NULL != pTemplate )
	{
		if ( m_emOperateFlag == em_NEW_PAGE_STATUS )
		{
			m_tNewTemplate.m_wMainNum = pTemplate->m_wMainNum;
			m_tNewTemplate.m_wMinorNum = pTemplate->m_wMinorNum;
			
			s32 nIndex = 0;
			for ( nIndex = 0; nIndex < pTemplate->m_wMainNum; nIndex++ )
			{
				m_tNewTemplate.m_atTpMainVideoRes[nIndex] = pTemplate->m_atTpMainVideoRes[nIndex];	
			}
			
			for ( nIndex = 0; nIndex < pTemplate->m_wMinorNum; nIndex++ )
			{
				m_tNewTemplate.m_atTpMinorVideoRes[nIndex] = pTemplate->m_atTpMinorVideoRes[nIndex];	
			}

			m_tNewTemplate.m_emTpAudioFormat = pTemplate->m_emTpAudioFormat;
		}
		else if ( m_emOperateFlag == em_EDIT_PAGE_STATUS  )
		{
			m_tSelTemplate.m_wMainNum = pTemplate->m_wMainNum;
			m_tSelTemplate.m_wMinorNum = pTemplate->m_wMinorNum;
			
			s32 nIndex = 0;
			for ( nIndex = 0; nIndex < pTemplate->m_wMainNum; nIndex++ )
			{
				m_tSelTemplate.m_atTpMainVideoRes[nIndex] = pTemplate->m_atTpMainVideoRes[nIndex];	
			}
			
			for ( nIndex = 0; nIndex < pTemplate->m_wMinorNum; nIndex++ )
			{
				m_tSelTemplate.m_atTpMinorVideoRes[nIndex] = pTemplate->m_atTpMinorVideoRes[nIndex];	
			}

			m_tSelTemplate.m_emTpAudioFormat = pTemplate->m_emTpAudioFormat;
		}
	}

	m_dlgMediaCfg.ShowWindow(SW_HIDE);
}

LRESULT CMeetTemplateLogic::OnConfTmpResUsedCountNotify(WPARAM wParam, LPARAM lParam)
{
	u16* wUsedCount = (u16*)(wParam);
	if ( NULL != wUsedCount )
	{
		m_wResUsedCount = *wUsedCount;

		u16 wResNum = 0; 
		if ( m_emOperateFlag == em_NEW_PAGE_STATUS )
		{
			wResNum = CComInterface::GetNeedBasNum(m_tNewTemplate);
		}
		else
		{
			wResNum = CComInterface::GetNeedBasNum(m_tSelTemplate);
		}

		UpdateResUsedCountToControl(wResNum);

		CMsgHandle::SendMessage( UI_UMS_CONFTMPRESUSEDCOUNT_NOTIFY, wParam, lParam );
	}

	return S_OK;
}

LRESULT CMeetTemplateLogic::OnDelAllConftempRet(WPARAM wParam, LPARAM lParam)
{
	EmTpConfTemplateRet emErrCode = (EmTpConfTemplateRet)wParam;
	
	if ( TP_ConfTemplate_DelSuccess == emErrCode )
	{
		MeetTmpRefresh();
	} 
	else
	{
		MESSAGEWND( "删除全部模板失败"  );
	}
	
    return S_OK;	
}

void CMeetTemplateLogic::UpdateResUsedCountToControl( u16 wResNum )
{
	if ( m_wResUsedCount == 0 )
	{
		m_etAdaptRes.SetWindowText("格式选择");
		return;
	}

	s8 chUsedCount[8];
	memset( chUsedCount, 0, 8 );
	itoa( m_wResUsedCount, chUsedCount, 10 );

	CString strText;
	strText = "会议所需适配资源 ";
	char chNum[10];
	memset( chNum, 0, 10 );
	itoa( wResNum , chNum, 10 );
	strText += chNum;
	strText += " / ";
	strText += chUsedCount;
	
	m_etAdaptRes.SetWindowText(strText);
}

void CMeetTemplateLogic::UpdateDiscussShowListData()
{
	//更新会议讨论列表(主会场+分会场)
	m_mapDiscussList.clear();
	m_mapDiscussList = m_mapEpList;

	CString strHomeCns;
	if ( em_SCANF_PAGE_STATUS == m_emOperateFlag )
	{
		m_stHomeMeeting.GetWindowText(strHomeCns);
	}
	else
	{
		m_etHomeMeeting.GetWindowText(strHomeCns);
	}
	
	if ( !strHomeCns.IsEmpty() )
	{
		EnterCriticalSection(&g_csLock);
		//u16 nEpId = m_mapDiscussList.size();
		std::map<u16,CString>::iterator iter;
		iter = find_if( m_mapDiscussList.begin(), m_mapDiscussList.end(), bind2nd( ptr_fun(CUmcwebCommon::MapValueCompare), strHomeCns ) );
		if ( iter == m_mapDiscussList.end() )
		{
			m_mapDiscussList.insert( std::make_pair<u16,CString>( 0, strHomeCns ) );
		}
		LeaveCriticalSection(&g_csLock);
	}

	//更新会议讨论列表勾选的会场
	std::map<u16,CString>::iterator iterSel = m_mapDiscussSelItem.begin();
	for ( ; iterSel != m_mapDiscussSelItem.end(); )
	{
		u16 wIndex = iterSel->first;
		CString strDiscussSelName = iterSel->second;
		
		std::map<u16,CString>::iterator iter;
		iter = find_if( m_mapDiscussList.begin(), m_mapDiscussList.end(), bind2nd( ptr_fun(CUmcwebCommon::MapValueCompare), strDiscussSelName ) );
		if ( iter == m_mapDiscussList.end() )
		{
			EnterCriticalSection(&g_csLock);
			iterSel++;
			m_mapDiscussSelItem.erase(wIndex);
			m_mapDiscussSelItem.insert( std::make_pair<u16,CString>(wIndex, "") );
			LeaveCriticalSection(&g_csLock);
			
			continue;
		}
		iterSel++;
	}

	m_dlgMeetDiscuss.UpdateDiscussEdit( m_mapDiscussSelItem, m_bSwitchDiscuss, m_emOperateFlag );
}

void CMeetTemplateLogic::SetDiscussListPageToEditPage(const TTPConfTemplate& tSelTemplate)
{
	m_mapDiscussSelItem.clear();

	for ( u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++ )
	{
		u16 nDiscussId = tSelTemplate.m_atAuxMixList.m_awList[wIndex];
		if ( TP_INVALID_INDEX ==  nDiscussId )
		{
			EnterCriticalSection(&g_csLock);
			m_mapDiscussSelItem.insert( std::make_pair<u16,CString>(wIndex, "") );
			LeaveCriticalSection(&g_csLock);
			continue;
		}

		CString strDiscussName = FindConfDiscussListById(nDiscussId);

		EnterCriticalSection(&g_csLock);
		m_mapDiscussSelItem.insert( std::make_pair<u16,CString>(wIndex, strDiscussName) );
		LeaveCriticalSection(&g_csLock);
	}

	m_bSwitchDiscuss = tSelTemplate.m_atAuxMixList.m_bAudMixOn;
	m_dlgMeetDiscuss.UpdateDiscussEdit( m_mapDiscussSelItem, tSelTemplate.m_atAuxMixList.m_bAudMixOn, m_emOperateFlag );
}

void CMeetTemplateLogic::UpdateSearchEdtStatus()
{
	if ( m_btnAllSel.IsWindowVisible() )
	{
		m_etSearch.EnableWindow(FALSE);
	}
	else
	{
		m_etSearch.EnableWindow(TRUE);

		//需求确认,off时也可编辑  -- 20140408
// 		switch( m_emTabFlag )
// 		{
// 		case em_MEETINFO_PAGE:
// 			{
// 				m_etSearch.EnableWindow(TRUE);
// 			}
// 			break;
// 		case em_Ep_PAGE:
// 			{
// 				m_etSearch.EnableWindow(TRUE);
// 			}
// 			break;
// 		case em_POLLING_PAGE:
// 			{
// 				m_etSearch.EnableWindow(m_bSwitchPolling);
// 			}
// 			break;
// 		case em_DISCUSS_PAGE:
// 			{
// 				m_etSearch.EnableWindow(m_bSwitchDiscuss);
// 			}
// 			break;
// 		default:
// 			break;
// 		}
	}
}

LRESULT CMeetTemplateLogic::OnUmsReasonInd(WPARAM wParam, LPARAM lParam)
{
	TTPUmsReasonInd tReason = *reinterpret_cast<TTPUmsReasonInd*>(wParam);

	CString strError;	
    switch( tReason.m_dwReason )
    {
    case TP_UMS_Discard_Start:
        strError = _T("开启讨论失败：媒体资源不足");
        break;
    case TP_UMS_Discard_AddEp:
        strError = _T("添加会场失败：媒体资源不足");
        break;
    case TP_UMS_Discard_EpOnLine:
        {
			u32 dwEpId = tReason.m_dwReserve1;
			CString strDiscussName = FindConfDiscussListById(dwEpId);
			if ( !strDiscussName.IsEmpty() )
			{
				strError.Format( "会场%s离开讨论：媒体资源不足", strDiscussName );
            }
        }        
        break;
    case TP_UMS_Discard_Error:
        strError = _T("会议讨论关闭：媒体资源不足");
        break;
    default:
        break;
    }
	
    if ( !strError.IsEmpty() )
    {
		MESSAGEWND( strError );
    }
	
    return S_OK;
}


