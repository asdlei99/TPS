#include "StdAfx.h"
#include "calendarlogic.h"

template<> CCalendarLogic* Singleton<CCalendarLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CCalendarLogic, CNotifyUIImpl)

	MSG_CREATEWINDOW(_T("calendarLayout"), OnCreate)
	MSG_INIWINDOW(_T("calendarLayout"), OnInit)

	MSG_CLICK(_T("BtnLast"), OnBtnLast)
	MSG_CLICK(_T("BtnNext"), OnBtnNext)

	MSG_ITEMSELECTD(_T("DateList"), OnDateListItemClick)

	USER_MSG(UI_DISCONNECTED_CLEARDATA,OnDisconnect)
APP_END_MSG_MAP()


CCalendarLogic::CCalendarLogic( void )
{
}


CCalendarLogic::~CCalendarLogic(void)
{
}


bool CCalendarLogic::OnCreate( TNotifyUI& msg )
{
	REG_CNC_MSG_WND_OB(m_pm->GetPaintWindow());

	return false;
}

bool CCalendarLogic::OnInit(TNotifyUI& msg)
{
	return true;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
}

bool CCalendarLogic::OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle )
{
	return NO_ERROR;
}


bool CCalendarLogic::OnBtnLast( TNotifyUI& msg )
{
	if ( m_Month == 1 )
	{
		m_Month = 12;
		m_Year--;
	}
	else
	{
		m_Month--;
	}

	m_strSelDate.Format( _T("%d年%d月%d日"), m_Year, m_Month, m_Day );

	CString str;
	str.Format(_T("%d年%d月"),m_Year,m_Month);
	ICncCommonOp::SetControlText( str, m_pm, _T("lbYandM") );

	FillDates();
	return true;
}

bool CCalendarLogic::OnBtnNext( TNotifyUI& msg )
{
	if ( m_Month == 12 )
	{
		m_Month = 1;
		m_Year++;
	}
	else
	{
		m_Month++;
	}

	m_strSelDate.Format( _T("%d年%d月%d日"), m_Year, m_Month, m_Day );

	CString str;
	str.Format(_T("%d年%d月"),m_Year,m_Month);
	ICncCommonOp::SetControlText( str, m_pm, _T("lbYandM") );

	FillDates();
	return true;
}

bool CCalendarLogic::SetCalendarInfor( POINT pt, SYSTEMTIME sysTime )
{
	Window* pWnd = IWindowManager::GetSingletonPtr()->GetWindow( g_strCalendarDlg.c_str() );

	if ( pWnd != NULL )
	{
		pWnd->SetAutoHide( true );
	}

	RECT rt;
	GetWindowRect( m_pm->GetPaintWindow(),&rt );
	
	s32 nTop = pt.y - ( rt.bottom - rt.top ) + 78;
	s32 nLeft = pt.x - ( rt.right - rt.left )/2;

    RECT rcParent;
    HWND hparent = GetParent(m_pm->GetPaintWindow());
    GetWindowRect(hparent,&rcParent);

    nLeft += rcParent.left;
    if (nTop < 0)
    {
        nTop = rcParent.top;
    }
    else
    {
        nTop += rcParent.top;
    }

	SetWindowPos( m_pm->GetPaintWindow(), NULL, nLeft, nTop, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );

	SetSelDate(sysTime.wYear,sysTime.wMonth,sysTime.wDay);
	m_LastTime = sysTime;
	FillDates();
	return true;
}

void CCalendarLogic::FillDates()
{
	// Get current local time
	SYSTEMTIME st;
	GetLocalTime(&st);
	// Calculate day of the week
	int dayOfWeek = CalculateDayOfWeek( 1, m_Month, m_Year, true );
	// Get number of days of the current month
	int numberOfDays = GetNumberOfDays( m_Month, m_Year );
	int numberOflastMonthDays = GetNumberOfDays( m_Month - 1, m_Year );

	int day = 0;
	for ( int i=0; i<42; i++ )
	{
		// Check starting day of the month
		if ( ( i < dayOfWeek ) || ( day >= numberOfDays ) )
		{
			if( i < dayOfWeek )
			{
				m_Dates[i].mcState = LASTMONTH;
				m_Dates[i].mcDay = numberOflastMonthDays - dayOfWeek + i + 1;
			}
			if (day >= numberOfDays)
			{
				m_Dates[i].mcState = NEXTMONTH;
				m_Dates[i].mcDay = i - day - dayOfWeek + 1;
			}
			
		}
		else
		{
			day++;
			m_Dates[i].mcDay = day;
			if ( day == m_LastTime.wDay &&  m_Month == m_LastTime.wMonth )
				m_Dates[i].mcState = SELECTED;
			else
				m_Dates[i].mcState = UNSELECTED;
		}

		// If current day is today
		if ( ( day == st.wDay ) && ( m_Month == st.wMonth ) && ( m_Year == st.wYear ) )
			m_Dates[i].mcToday = true;
		else
			m_Dates[i].mcToday = false;
	}

	UpdateDates();

}


int CCalendarLogic::CalculateDayOfWeek(int day, int month, int year, BOOL bGregorian)
{
	int result = -1;

	// Calculate params
	int a = (int)((14-month) / 12);
	int y = year - a;
	int m = month + 12*a - 2;

	// Calculate day of the week
	if ( bGregorian == TRUE )
		result = (int)((day + y + y/4 - y/100 + y/400 + (31*m)/12) % 7);
	else
		result = (int)((5 + day + y + y/4 + (31*m)/12) % 7);

	return result;
}

bool CCalendarLogic::IsLeapYear(int year, BOOL bGregorian)
{
	bool result = false;

	// Is year a leap year
	if ( bGregorian == TRUE )
	{
		if ( ( year % 400 == 0 ) || ( ( year % 4 == 0 ) && ( year % 100 != 0 ) ) )
			result = true;
	}
	else
	{
		if ( year % 4 == 0 )
			result = true;
	}

	return result;
}


int CCalendarLogic::GetNumberOfDays(int month, int year)
{
	int result;

	// Calculate number of days in the month
	if ( month != 2 )
	{
		// In the first half of the year
		if ( month <= 7 )
		{
			if ( month % 2 == 1 )
				result = 31;
			else
				result = 30;
		}
		// In the second half of the year
		else
		{
			if ( month % 2 == 0 )
				result = 31;
			else
				result = 30;
		}
	}
	else
	{
		// If year is leap year
		if ( IsLeapYear(year, TRUE) )
			result = 29;
		else
			result = 28;
	}

	return result;
}

void CCalendarLogic::SetSelDate( int nYear, int nMonth, int nDay )
{
	m_Year = nYear;
	m_Month = nMonth;
	m_Day = nDay;

	CString str;
	str.Format(_T("%d年%d月"),m_Year,m_Month);
	ICncCommonOp::SetControlText( str, m_pm, _T("lbYandM") );
}

bool CCalendarLogic::OnDateListItemClick( TNotifyUI& msg )
{
	int numberOfDays = CalculateDayOfWeek( 1, m_Month, m_Year, true );
	if ( m_Day + numberOfDays == msg.wParam + 1)
	{
		return false;
	}
	m_Day = m_Dates[msg.wParam].mcDay;
	if (m_Dates[msg.wParam].mcState == LASTMONTH)
	{
        if ( m_Month == 1 )
        {
            m_Month = 12;
            m_Year--;
        }
        else
        {
            m_Month--;
        }
	}
	if (m_Dates[msg.wParam].mcState == NEXTMONTH)
	{
        if ( m_Month == 12 )
        {
            m_Month = 1;
            m_Year++;
        }
        else
        {
            m_Month++;
        }
	}
	m_strSelDate.Format( _T("%d年%d月%d日"), m_Year, m_Month, m_Day );
	// Send notification message
	NOTIFY_MSG(UI_CNC_CALENDARDATE_SET,(WPARAM)&m_strSelDate, 0);
	WINDOW_MGR_PTR->ShowWindow(g_strCalendarDlg.c_str(),false);

	return true;
}

void CCalendarLogic::UpdateDates()
{
	CTouchListUI *pDateList = (CTouchListUI*)ICncCommonOp::FindControl( m_pm, _T("DateList") );
	if ( pDateList == NULL )
	{
		return;
	}
	pDateList->RemoveAll();

	int dwSelId = -1;
	for ( int i=1; i<=42; i++ )
	{
		CListContainerElementUI *pListContainer = 
			(CListContainerElementUI*)CONTROLFACTORY()->GetControl( _T("DateItem") );

		CString str = _T("");
		str.Format(_T("%d"), m_Dates[i-1].mcDay);
		ICncCommonOp::SetControlText( str, m_pm, _T("lbdate"), pListContainer );
		// If date is selected
		if ( m_Dates[i-1].mcState != SELECTED )
		{
			// Draw today marker 
			if ( ( m_Dates[i-1].mcToday == true ) && ( m_Dates[i-1].mcState == SELECTED || m_Dates[i-1].mcState == UNSELECTED) )
			{
				ICncCommonOp::SetControlBkImg( _T("res\\calendar\\bktoday.png"), m_pm, _T("lbdate"), pListContainer );
			}
			
			if (m_Dates[i-1].mcState == NEXTMONTH || m_Dates[i-1].mcState == LASTMONTH )
			{
				CLabelUI *pDateItem = (CLabelUI*)ICncCommonOp::FindControl( m_pm, _T("lbdate"), pListContainer );
				if (pDateItem)
				{
					pDateItem->SetAttribute(_T("textcolor"),_T("#33D4DEEB"));
				}
			}		
		}

		if ( m_Dates[i-1].mcState == SELECTED )
		{
			dwSelId = i-1;
		}

		pDateList->Add(pListContainer);
	}

	pDateList->SelectItem(dwSelId);

}
