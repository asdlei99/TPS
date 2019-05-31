// systemtime.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "umssystimesetLogic.h"
#include "mainLogic.h"
#include "usermanageLogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern float CUR_SCREEN_WIDTH_PER;
extern float CUR_SCREEN_HEIGHT_PER;
/////////////////////////////////////////////////////////////////////////////
// CUmsSystimeSetLogic dialog
extern CMainLogic* g_cmainWnd;

CUmsSystimeSetLogic::CUmsSystimeSetLogic(CWnd* pParent /*=NULL*/)
	: CDlgChild(CUmsSystimeSetLogic::IDD, pParent),
		m_pUmsConfig(NULL)
{
	//{{AFX_DATA_INIT(CUmsSystimeSetLogic)
	//}}AFX_DATA_INIT
	//m_bShowMosaicHoriImg = FALSE;
    m_bIsEdit = FALSE;
    m_nExHour = 0;
    m_nExMin = 0;
    m_nExSec = 0;
    m_bEnterCalendar = FALSE;
	m_bEditingDate = FALSE;

}

void CUmsSystimeSetLogic::DoDataExchange(CDataExchange* pDX)
{
	CDlgChild::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUmsSystimeSetLogic)
	DDX_Control(pDX, IDC_STATIC_Date, m_stDate);
	DDX_Control(pDX, IDC_STATIC_StartTime, m_stStartTime);
	DDX_Control(pDX, IDC_EditHour, m_etSetHour);
	DDX_Control(pDX, IDC_EditMinute, m_etSetMin);
	DDX_Control(pDX, IDC_EditSec, m_etSetSec);
	DDX_Control(pDX, IDC_BUTTON_CALENDAR, m_btnCalendar);
	DDX_Control(pDX, IDC_BtnPlus, m_btnPlus);
	DDX_Control(pDX, IDC_BtnMinus, m_btnMinus);
	DDX_Control(pDX, IDC_EDIT_DATE, m_etDateSet);

	DDX_Control(pDX, IDC_EDIT_DOT_HOUR, m_edtDotHour);
	DDX_Control(pDX, IDC_EDIT_DOT_MIN, m_edtDotMin);
 
    
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUmsSystimeSetLogic, CDlgChild)
	//{{AFX_MSG_MAP(CUmsSystimeSetLogic)
	ON_BN_CLICKED(IDC_BUTTON_CALENDAR, OnBtnCalendar)
    ON_BN_CLICKED(IDC_BtnPlus, OnBtnPlus)
	ON_BN_CLICKED(IDC_BtnMinus, OnBtnMinus)
	ON_MESSAGE( WM_DEF_HIDE_LOSEFOCUSHIDER, OnHideAUtoHideWnd )
 	ON_MESSAGE( UI_GET_UMS_SYSTIME,  OnGetUmsSystimeTime )
	ON_MESSAGE( UI_CALENDAR_SELECT_DATE,  OnUpdateCalendarSelDate )
	ON_WM_TIMER()
	ON_EN_SETFOCUS(IDC_EditHour, OnSetfocusEditHour)
	ON_EN_SETFOCUS(IDC_EditMinute, OnSetfocusEditMinute)
	ON_EN_UPDATE(IDC_EditMinute, OnUpdateEditMinute)
	ON_EN_UPDATE(IDC_EditSec, OnUpdateEditSec)
    ON_EN_SETFOCUS(IDC_EditSec, OnSetfocusEditSec)
	ON_EN_UPDATE(IDC_EditHour, OnUpdateEditHour)
    ON_MESSAGE( WM_EDIT_ONCHAR, OnTimeEditChange )
    ON_MESSAGE( WM_BTN_HOLD, OnBtnHold )
    ON_MESSAGE( WM_BTN_HOLD_END, OnBtnHoldEnd )
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUmsSystimeSetLogic message handlers

void CUmsSystimeSetLogic::RegisterFun()
{
	REG_MSG( UI_GET_UMS_SYSTIME, GetSafeHwnd() );
}

BOOL CUmsSystimeSetLogic::InitControlPane()
{   
	m_btnCalendar.SetImage( IDR_PNG_CALENDAR_SEL, IDR_PNG_CALENDAR_DOWN, IDR_PNG_CALENDAR_SEL, 
		IDR_PNG_CALENDAR,IDR_PNG_CALENDAR_DOWN,IDR_PNG_CALENDAR);
    m_btnCalendar.SetButtonStyle( BS_AUTOCHECKBOX );
   
	m_btnPlus.SetImage( IDR_PNG_BTN_PLUS, IDR_PNG_BTN_PLUSDOWN, IDR_PNG_BTN_PLUS );
	m_btnMinus.SetImage( IDR_PNG_BTN_SUB, IDR_PNG_BTN_SUBDOWN, IDR_PNG_BTN_SUB );

	//浏览控件
	CRect rectClient;
	this->GetClientRect(&rectClient);
	
	ScreenToClient(&rectClient);
	
	m_stDate.SetWindowPos( NULL, 18*CUR_SCREEN_WIDTH_PER, (81 - 46)*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stDate.SetWindowText("日期");
	m_stDate.SetTextAlign(StringAlignmentNear);
	m_stDate.SetTextColor(Color( 46, 55, 76 ));
	m_stDate.SetFont( 13, "微软雅黑" );

    CUmcwebCommon::SetImgForTransEdit(&m_etDateSet);  //date window
    m_etDateSet.SetShowIcon(FALSE);

	m_stStartTime.SetWindowPos( NULL, 18*CUR_SCREEN_WIDTH_PER, 85*CUR_SCREEN_HEIGHT_PER, rectClient.Width()*CUR_SCREEN_WIDTH_PER, 20*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_stStartTime.SetWindowText("时间");
	m_stStartTime.SetTextAlign(StringAlignmentNear);
	m_stStartTime.SetTextColor(Color( 46, 55, 76 ));
	m_stStartTime.SetFont( 13, "微软雅黑" );
	
	CUmcwebCommon::SetImgForTransEditTimeLft( &m_etSetHour ); 
	m_etSetHour.SetShowIcon(FALSE);
    m_etSetHour.SetTextAlign(StringAlignmentCenter);
	m_etSetHour.EnableWindow(FALSE);
    m_etSetHour.SetWindowPos( NULL, 76*CUR_SCREEN_WIDTH_PER, 72*CUR_SCREEN_HEIGHT_PER, 64*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
    m_etSetHour.SetWindowText("0");
	m_etSetHour.SetLimitLength(2);

	
	CUmcwebCommon::SetImgForTransEditTimeMdl( &m_edtDotHour );
	m_edtDotHour.SetShowIcon(FALSE);
	m_edtDotHour.EnableWindow(FALSE);
    m_edtDotHour.SetWindowPos( NULL, 138*CUR_SCREEN_WIDTH_PER, 72*CUR_SCREEN_HEIGHT_PER, 14*CUR_SCREEN_WIDTH_PER, /*20*/41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
    m_edtDotHour.SetWindowText(":");
    m_edtDotHour.SetTextAlign(StringAlignmentCenter);
    m_edtDotHour.SetTextColor(Color( 46, 55, 76 ),Color( 46, 55, 76 ) );
	m_edtDotHour.SetFont( 14, "微软雅黑" );

	CUmcwebCommon::SetImgForTransEditTimeMdl(&m_etSetMin);
	m_etSetMin.SetShowIcon(FALSE);    //not show "X" , delete icon 
	m_etSetMin.SetTextAlign(StringAlignmentCenter);
	m_etSetMin.EnableWindow(FALSE);
    m_etSetMin.SetWindowPos( NULL, 150*CUR_SCREEN_WIDTH_PER,  72*CUR_SCREEN_HEIGHT_PER, 64*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
	m_etSetMin.SetWindowText("0");
    m_etSetMin.SetLimitLength(2);


	CUmcwebCommon::SetImgForTransEditTimeMdl( &m_edtDotMin );
	m_edtDotMin.SetShowIcon(FALSE);
	m_edtDotMin.EnableWindow(FALSE);
    m_edtDotMin.SetWindowPos( NULL,  213*CUR_SCREEN_WIDTH_PER, 72*CUR_SCREEN_HEIGHT_PER,  14*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
    m_edtDotMin.SetWindowText(":");
    m_edtDotMin.SetTextAlign(StringAlignmentCenter);
    m_edtDotMin.SetTextColor(Color( 46, 55, 76 ),Color( 46, 55, 76 ) );
	m_edtDotMin.SetFont( 14, "微软雅黑" );

    CUmcwebCommon::SetImgForTransEditTimeRgt(&m_etSetSec);
	m_etSetSec.SetShowIcon(FALSE);
	m_etSetSec.SetTextAlign(StringAlignmentCenter);
	m_etSetSec.EnableWindow(FALSE);
    m_etSetSec.SetWindowPos( NULL, 224*CUR_SCREEN_WIDTH_PER,  72*CUR_SCREEN_HEIGHT_PER, 64*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );
    m_etSetSec.SetWindowText("0");
    m_etSetSec.SetLimitLength(2);

	CRect rect;
	m_etSetSec.GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_etDateSet.SetWindowPos( NULL, 76*CUR_SCREEN_WIDTH_PER, 24*CUR_SCREEN_HEIGHT_PER, (rect.right - 76)*CUR_SCREEN_WIDTH_PER, 41*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

    m_btnPlus.SetWindowPos( NULL, 288*CUR_SCREEN_WIDTH_PER, 71*CUR_SCREEN_HEIGHT_PER, 51*CUR_SCREEN_WIDTH_PER, 22*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );
    m_btnMinus.SetWindowPos( NULL, 288*CUR_SCREEN_WIDTH_PER, 93*CUR_SCREEN_HEIGHT_PER, 51*CUR_SCREEN_WIDTH_PER, 22*CUR_SCREEN_HEIGHT_PER, SWP_HIDEWINDOW );

	m_dlgCalendar.Create(IDD_DIALOG_CALENDAR,this);
    m_dlgCalendar.ShowWindow( SW_HIDE );

	m_etDateSet.GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_btnCalendar.SetWindowPos( NULL, rect.right + 1*CUR_SCREEN_WIDTH_PER , 28*CUR_SCREEN_HEIGHT_PER, m_btnCalendar.GetImageSize().cx*CUR_SCREEN_WIDTH_PER, m_btnCalendar.GetImageSize().cy*CUR_SCREEN_HEIGHT_PER, SWP_SHOWWINDOW );

	return TRUE;
}

BOOL CUmsSystimeSetLogic::OnInitDialog() 
{
	CDlgChild::OnInitDialog();

	RegisterFun();
	if ( !InitControlPane() )
	{
		return FALSE;
	}

	if( m_pUmsConfig == NULL )
	{
		BUSINESSIFPTR->GetCtrlInterface(&m_pUmsConfig);
	}
	
	m_btnCalendar.SetBindWnd( m_dlgCalendar.GetSafeHwnd() );

    REG_MSG( WM_DEF_HIDE_LOSEFOCUSHIDER, GetSafeHwnd() );

	SetTimeControl( FALSE ); //hide btn  & start timer
	
    m_btnPlus.SetUseTimer( TRUE );
    m_btnMinus.SetUseTimer( TRUE );
	return TRUE;  
}

void CUmsSystimeSetLogic::OnBtnCalendar() 
{
	int nCheck = m_btnCalendar.GetCheck();
	if( nCheck == BST_CHECKED )
	{	
        m_bEnterCalendar = TRUE; //do not update 

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
		m_dlgCalendar.ShowWindow(SW_HIDE);
        //m_bEnterCalendar = FALSE; //do not update 
	}
}

void CUmsSystimeSetLogic::OnBtnPlus() 
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
    case em_Focus_Second:
		{
		  CUmcwebCommon::PlusSecBtn(&m_etSetSec);
		}
        break;
    }

	m_bEditingDate = TRUE;
}

void CUmsSystimeSetLogic::OnBtnMinus() 
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
    case em_Focus_Second:
		{
			CUmcwebCommon::SubSecBtn(&m_etSetSec);
		}
        break;
    }

	m_bEditingDate = TRUE;
}

BOOL CUmsSystimeSetLogic::SaveSysTime()
{ 
    //把时间设置为系统时间 
    SYSTEMTIME time;
    ZeroMemory( &time, sizeof(SYSTEMTIME));

    CString strDate;
	m_etDateSet.GetWindowText(strDate);
    sscanf( strDate, "%u年%u月%u日", &time.wYear, &time.wMonth, &time.wDay );
    
    CString strHour;
	m_etSetHour.GetWindowText(strHour);
    if ( strHour.IsEmpty() )
    {
        strHour = "00"; 
        m_etSetHour.SetWindowText( strHour );
    }  
	sscanf( strHour, "%d", &time.wHour );
    
    CString strMin;
	m_etSetMin.GetWindowText(strMin);
    if ( strMin.IsEmpty() )
    {
        strMin = "00";
        m_etSetHour.SetWindowText( strMin );
        
    }
    sscanf( strMin, "%d", &time.wMinute ); 
	
	CString strSec;
	m_etSetSec.GetWindowText(strSec);
    if ( strSec.IsEmpty() )
    {
        strSec = "00";
        m_etSetHour.SetWindowText( strSec );
        
    }
    sscanf( strSec, "%d", &time.wSecond ); 

	//发送请求到服务器
	TTPTime tTPTimeSever;
	tTPTimeSever.m_wYear = time.wYear;
	tTPTimeSever.m_byMonth = time.wMonth;
	tTPTimeSever.m_byMDay = time.wDay;
	tTPTimeSever.m_byHour = time.wHour;
	tTPTimeSever.m_byMinute = time.wMinute;
	tTPTimeSever.m_bySecond = time.wSecond;

	CTime curtime(time);
	//需求修改：同步至服务器时间范围：2000年1月1日8点~2037年12月31日24点  -- 20140701 by xhx
	CTime limittime = CTime( 2000, 1, 1, 8, 0, 0, -1 );
	if ( tTPTimeSever.m_wYear > 2037 || tTPTimeSever.m_wYear < 2000 || curtime < limittime )
	{
		MESSAGEWND( "系统时间设置不正确，请修改日期" );
		return FALSE;
	}

	if ( m_pUmsConfig != NULL )
	{
		u16 nRet = m_pUmsConfig->OnSysTimeSetReq(tTPTimeSever);
		if ( nRet != NO_ERROR )
		{
			MESSAGEWND( "系统时间请求发送失败" );
		}
	}

	m_bEditingDate = FALSE;   

	return TRUE;
}

void CUmsSystimeSetLogic::UpdateSysTimeToControl( struct tm& tmDate )
{
	if ( m_bEditingDate )
	{
		return;
	}
	
	s8 bufDate[20] = { 0 };
	
    if ( !m_bEnterCalendar )
    {
        sprintf( bufDate, "%d年%d月%d日",tmDate.tm_year, tmDate.tm_mon, tmDate.tm_mday );
        m_etDateSet.SetWindowText(bufDate);
    }   
	
	s8 bufHour[3] = { 0 };
	s8 bufMin[3] = { 0 };
	s8 bufSec[3] = { 0 };
	sprintf( bufHour, "%.2d", tmDate.tm_hour );
	sprintf( bufMin, "%.2d", tmDate.tm_min );
    sprintf( bufSec, "%.2d", tmDate.tm_sec );
	
    CString strTime;
    m_etSetHour.GetWindowText( strTime );
    if ( strTime != bufHour )
    {   
        m_etSetHour.SetWindowText(bufHour);
        if ( m_emCurFocus == em_Focus_Hour )
        {
            m_etSetHour.SetSel( 0, -1 );
        }
    }
    
    m_etSetMin.GetWindowText( strTime );
    if ( strTime != bufMin )
    {   
        m_etSetMin.SetWindowText(bufMin);
        if ( m_emCurFocus == em_Focus_Minute )
        {
            m_etSetMin.SetSel( 0, -1 );
        }
    }
	
    m_etSetSec.SetWindowText(bufSec);
    if ( m_emCurFocus == em_Focus_Second )
    {
        m_etSetSec.SetSel( 0, -1 );
    }
}

void CUmsSystimeSetLogic::InitDlg()
{   
	SetTimeControl(FALSE);
	m_btnCalendar.SetCheck(BST_UNCHECKED); 
	m_bIsEdit = FALSE;  //restore
} 

HRESULT CUmsSystimeSetLogic::OnHideAUtoHideWnd( WPARAM wparam, LPARAM lparam )
{   
	if ( m_dlgCalendar.GetSafeHwnd() != NULL )
	{
	    BOOL bRet = m_dlgCalendar.SetWindowPos(NULL, -30000, -30000, 0, 0, SWP_HIDEWINDOW|SWP_NOACTIVATE ); 
		//OspPrintf( TRUE, FALSE, "\n------ShowWindow Return: %d------", bRet );
	}

	return S_OK;
}

HRESULT CUmsSystimeSetLogic::OnGetUmsSystimeTime( WPARAM wparam, LPARAM lparam )
{  
	if ( m_pUmsConfig != NULL )
	{
		TTPTime tTPTimeSever;
		m_pUmsConfig->GetUmsSystime(tTPTimeSever);

		if ( !tTPTimeSever.IsValid() )
		{
			MESSAGEWND( "服务器时间无效" );
			return 0L;
		}

		struct tm tmDate;
		memset(&tmDate, 0, sizeof(tmDate));
		tmDate.tm_year = tTPTimeSever.m_wYear - 1900;
		tmDate.tm_mon = tTPTimeSever.m_byMonth - 1;
		tmDate.tm_mday = tTPTimeSever.m_byMDay;
		tmDate.tm_hour = tTPTimeSever.m_byHour;
		tmDate.tm_min = tTPTimeSever.m_byMinute;
		tmDate.tm_sec = tTPTimeSever.m_bySecond;

		m_timeDate = mktime(&tmDate);
		//防止time_t越界
		if ( m_timeDate < 0 )
		{
			m_timeDate = 0;
		}

		m_nTimer = SetTimer( 1, 1000, NULL );    
	}

	return S_OK;
}

void CUmsSystimeSetLogic::OnTimer(UINT nIDEvent) 
{
	if ( nIDEvent == m_nTimer )
	{
 		m_timeDate += 1;
		//防止time_t越界
		if ( m_timeDate < 0 )
		{
			m_timeDate = 0;
		}

		struct tm tmTmpDate;
		CUmcwebCommon::TimeToTm( tmTmpDate, m_timeDate );

 		UpdateSysTimeToControl(tmTmpDate);
	}
		
	CDlgChild::OnTimer(nIDEvent);
}

LRESULT CUmsSystimeSetLogic::OnUpdateCalendarSelDate(WPARAM wParam, LPARAM lParam)
{
	CString strDate = m_dlgCalendar.GetDate();
	if ( !strDate.IsEmpty() )
	{        
		m_etDateSet.SetWindowText(strDate);
	}

	return 0L;
}

void CUmsSystimeSetLogic::SyncTimeToServer()
{ 
	//发送本地时间到服务器
	SYSTEMTIME sysTime;
	::GetLocalTime( &sysTime );

	TTPTime tTPTimeSever;
	tTPTimeSever.m_wYear = sysTime.wYear;
	tTPTimeSever.m_byMonth = sysTime.wMonth;
	tTPTimeSever.m_byMDay = sysTime.wDay;
	tTPTimeSever.m_byHour = sysTime.wHour;
	tTPTimeSever.m_byMinute = sysTime.wMinute;
	tTPTimeSever.m_bySecond = sysTime.wSecond;

	CTime curtime(sysTime);
	//需求修改：同步至服务器时间范围：2000年1月1日8点~2037年12月31日24点  -- 20140701 by xhx
	CTime limittime = CTime( 2000, 1, 1, 8, 0, 0, -1 );
	if ( tTPTimeSever.m_wYear > 2037 || tTPTimeSever.m_wYear < 2000 || curtime < limittime )
	{
		MESSAGEWND( "系统时间设置不正确，请修改日期" );
		return;
	}

	if ( m_pUmsConfig != NULL )
	{
		u16 nRet = m_pUmsConfig->OnSysTimeSetReq(tTPTimeSever);
		if ( nRet != NO_ERROR )
		{
			MESSAGEWND( "系统时间请求发送失败" );
		}
	}
}

// TRUE , edit time & date , kill timer; else disable ,update system time
void CUmsSystimeSetLogic::SetTimeControl(BOOL bIsOn)
{   
	m_edtDotHour.EnableWindow(bIsOn);
	m_edtDotMin.EnableWindow(bIsOn);
    m_etSetHour.EnableWindow(bIsOn);
    m_etSetMin.EnableWindow(bIsOn);
    m_etSetSec.EnableWindow(bIsOn);
    m_etDateSet.EnableWindow(bIsOn);    

	m_btnPlus.ShowWindow(bIsOn);
	m_btnMinus.ShowWindow(bIsOn);
    m_btnCalendar.ShowWindow(bIsOn);
    
    if( !bIsOn ) 
    {
        m_emCurFocus = em_Focus_Hour;
        m_bEnterCalendar = FALSE;       

		m_bEditingDate = FALSE;
    }
}

void CUmsSystimeSetLogic::OnSetfocusEditHour() 
{
    s8 chTemp[3] = {0} ;
	m_etSetHour.GetWindowText(chTemp, sizeof( chTemp) );
    m_nExHour = atoi(chTemp);
    m_emCurFocus = em_Focus_Hour;
}

void CUmsSystimeSetLogic::OnSetfocusEditMinute() 
{
    s8 chTemp[3] = {0} ;
    m_etSetMin.GetWindowText(chTemp, sizeof( chTemp) );
    m_nExMin = atoi(chTemp);
    m_emCurFocus = em_Focus_Minute;

}

void CUmsSystimeSetLogic::OnSetfocusEditSec() 
{
    s8 chTemp[3] = {0} ;
    m_etSetSec.GetWindowText(chTemp, sizeof( chTemp) );
    m_nExSec = atoi(chTemp);
    m_emCurFocus = em_Focus_Second;

}

void CUmsSystimeSetLogic::OnUpdateEditHour() 
{	
    CString strTemp;
    m_etSetHour.GetWindowText( strTemp );
    s32 nHour = atoi(strTemp);
    if ( nHour > 23 )
    {
        nHour = m_nExHour;
        strTemp.Format( "%d", nHour );        
        m_etSetHour.SetWindowText( strTemp );

        m_etSetHour.SetSel( -1 );
    }
    else
    {
        m_nExHour = nHour;
        return;
    } 
}

void CUmsSystimeSetLogic::OnUpdateEditMinute() 
{	
    CString strTemp;
    m_etSetMin.GetWindowText( strTemp );
    s32 nMin = atoi( strTemp );
    if ( nMin > 59 )
    {
        nMin = m_nExMin;
        strTemp.Format( "%d", nMin ); 
        m_etSetMin.SetWindowText( strTemp );

        m_etSetMin.SetSel( -1 );
    }
    else
    {
        m_nExMin = nMin;

        return;
    }    
}

void CUmsSystimeSetLogic::OnUpdateEditSec() 
{
    CString strTemp;
    m_etSetSec.GetWindowText( strTemp );
    s32 nSec = atoi( strTemp );
    if ( nSec > 59 )
    {
        nSec = m_nExSec;
        strTemp.Format( "%d", nSec ); 
        m_etSetSec.SetWindowText( strTemp );

        m_etSetSec.SetSel( -1 );
    }
    else
    {
        m_nExSec = nSec;

        return;
    }
}

//if input happen then kill timer
LRESULT CUmsSystimeSetLogic::OnTimeEditChange( WPARAM wParam, LPARAM lParam )
{
    if ( (HWND)wParam == m_etSetSec.GetSafeHwnd() ||
		(HWND)wParam == m_etSetMin.GetSafeHwnd() ||
		(HWND)wParam == m_etSetHour.GetSafeHwnd() )
    {
		m_bEditingDate = TRUE;      
    }  

    return 0;
}

LRESULT CUmsSystimeSetLogic::OnBtnHold( WPARAM wParam, LPARAM lParam )
{

    if ( (HWND)wParam == m_btnPlus.GetSafeHwnd() )
    {
        OnBtnPlus();
    }
    else if ( (HWND)wParam == m_btnMinus.GetSafeHwnd() )
    {
        OnBtnMinus();
    }
    return 0;
}

LRESULT CUmsSystimeSetLogic::OnBtnHoldEnd( WPARAM wParam, LPARAM lParam )
{
    switch( m_emCurFocus )
    {
    case em_Focus_Second:
        {
            m_etSetSec.SetFocus();
            m_etSetSec.SetSel( 0, -1 );
            break;
        }
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

    return 0;
}

void CUmsSystimeSetLogic::OnDestroy() 
{
	CDlgChild::OnDestroy();
	
	m_dlgCalendar.Clean();
}
