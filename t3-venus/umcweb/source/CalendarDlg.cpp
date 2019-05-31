// CalendarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "umcwebproj.h"
#include "CalendarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalendarDlg dialog
CCalendarDlg::CCalendarDlg(CWnd* pParent /*=NULL*/)
	: CTransparentBaseDlg(CCalendarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalendarDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_dwBkResourceID = IDR_PNG_CALENDAR_BK;
	m_byteSourceConstantAlpha = 230;
	SetAutoHideStatus(TRUE);
	m_hNotifyWnd = NULL;
	m_pCalendar = NULL;
}

void CCalendarDlg::DoDataExchange(CDataExchange* pDX)
{
	CTransparentBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalendarDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCalendarDlg, CTransparentBaseDlg)
	//{{AFX_MSG_MAP(CCalendarDlg)
	ON_WM_DESTROY()
	ON_MESSAGE( UI_CALENDAR_SELECT_DATE,  OnUpdateCalendarSelDate )
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarDlg message handlers
BOOL CCalendarDlg::OnInitDialog() 
{
	CTransparentBaseDlg::OnInitDialog();

	this->SetWindowPos( NULL, 0, 0, 393, 289 ,SWP_HIDEWINDOW );
	
 	m_pCalendar = new CTransparentCalendar("Calendar","Calendar",CRect(0,0,415,370),this, GETUNIQID, WS_CHILD|WS_CLIPSIBLINGS );
 	if( m_pCalendar != NULL )
	{
		m_pCalendar->SetImage( IDR_PNG_CALENDAR_BK, IDR_PNG_CALENDAR_PREMONTH, IDR_PNG_CALENDAR_PREMONTHDOWN, IDR_PNG_CALENDAR_NEXTMONTH, IDR_PNG_CALENDAR_NEXTMONTHDOWN );
		m_pCalendar->SetWindowPos( NULL, 0, 0, 415, 370 ,SWP_SHOWWINDOW );
	}
	else
	{
		return FALSE;
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CCalendarDlg::GetDate()
{
	if( m_pCalendar != NULL )
	{
		return m_pCalendar->GetClickDateString();
	}
	return "";
}

void CCalendarDlg::OnDestroy() 
{
	CTransparentBaseDlg::OnDestroy();

	SAFE_RELEASE(m_pCalendar);
}

void CCalendarDlg::Clean()
{
	SAFE_RELEASE(m_pCalendar);
}

void CCalendarDlg::SetDate( int nYear,  int nMonth, int nDay )
{
	if( m_pCalendar != NULL )
	{
		m_pCalendar->SetSelDate( nYear, nMonth, nDay );
	}
}

LRESULT CCalendarDlg::OnUpdateCalendarSelDate(WPARAM wParam, LPARAM lParam)
{
	CString strSelDate = *(CString*)wParam;
	if ( m_hNotifyWnd != NULL )
	{
		::PostMessage( m_hNotifyWnd, UI_CALENDAR_SELECT_DATE, (WPARAM)&strSelDate, 0 );
	}

	return 0L;
}

void CCalendarDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{ 
    if ( !bShow )
    { 
		 
		SetWindowPos(NULL, -30000, -30000, 0, 0, SWP_NOACTIVATE ); 
	 
    }
	
	//CRect rc;
	//GetClientRect(&rc);
	//PrtMsg("\n CCalendarDlg::OnShowWindow  bShow=%d  rc.width=%d  height=%d\n",bShow,rc.Width(),rc.Height());
    CTransparentBaseDlg::OnShowWindow(bShow,nStatus);   
}

