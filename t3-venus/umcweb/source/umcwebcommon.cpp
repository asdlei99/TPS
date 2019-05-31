// KUtil.cpp: implementation of the CUmcwebCommon class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "umcwebproj.h"
#include "umcwebcommon.h"
#include "HZPYSearch.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
s32 g_arrPngId[27] = {IDR_PNG_INDEX_BK,IDR_PNG_INDEX_A,IDR_PNG_INDEX_B,IDR_PNG_INDEX_C,IDR_PNG_INDEX_D,IDR_PNG_INDEX_E,IDR_PNG_INDEX_F,IDR_PNG_INDEX_G
,IDR_PNG_INDEX_H,IDR_PNG_INDEX_I,IDR_PNG_INDEX_J,IDR_PNG_INDEX_K,IDR_PNG_INDEX_L,IDR_PNG_INDEX_M,IDR_PNG_INDEX_N
,IDR_PNG_INDEX_O,IDR_PNG_INDEX_P,IDR_PNG_INDEX_Q,IDR_PNG_INDEX_R,IDR_PNG_INDEX_S,IDR_PNG_INDEX_T
,IDR_PNG_INDEX_U,IDR_PNG_INDEX_V,IDR_PNG_INDEX_W,IDR_PNG_INDEX_X,IDR_PNG_INDEX_Y,IDR_PNG_INDEX_Z};

CUmcwebCommon::CUmcwebCommon()
{
}

CUmcwebCommon::~CUmcwebCommon()
{
}

void CUmcwebCommon::SetImgForTransEdit( CTransparentEdit *pEdit, BOOL bSetDisableImg )
{
	if ( pEdit != NULL  )
	{
		pEdit->SetImage( IDR_PNG_EDITLEFT, IDR_PNG_EDITMID, IDR_PNG_EDITRIGHT,
			IDR_PNG_EDITLEFTSEL, IDR_PNG_EDITMIDSEL, IDR_PNG_EDITRIGHTSEL,
			IDR_PNG_EDITLEFTDIS, IDR_PNG_EDITMIDDIS, IDR_PNG_EDITRIGHTDIS,
			IDR_PNG_EDITDELETE, IDR_PNG_EDITDELETEDOWN , IDR_PNG_EDITSEARCH);

		if ( bSetDisableImg )
		{
			pEdit->SetDisableImg(FALSE);
			pEdit->SetDisableColor( Color(46,55,76) );
		}
	}
}

void CUmcwebCommon::SetImgForTransEditTimeLft( CTransparentEdit *pEdit, BOOL bSetDisableImg )
{
	if ( pEdit != NULL  )
	{
		pEdit->SetImage( IDR_PNG_EDITLEFT, IDR_PNG_EDITMID, IDR_PNG_EDITMID,
			IDR_PNG_EDITLEFT, IDR_PNG_EDITMID, IDR_PNG_EDITMID,
			IDR_PNG_EDITLEFTDIS, IDR_PNG_EDITMIDDIS, IDR_PNG_EDITMIDDIS,
			IDR_PNG_EDITDELETE, IDR_PNG_EDITDELETEDOWN , IDR_PNG_EDITDELETEDOWN);

		if ( bSetDisableImg )
		{
			pEdit->SetDisableImg(FALSE);
			pEdit->SetDisableColor( Color(46,55,76) );
		}
	}
}


void CUmcwebCommon::SetImgForTransEditTimeMdl( CTransparentEdit *pEdit, BOOL bSetDisableImg )
{
	if ( pEdit != NULL  )
	{
		pEdit->SetImage( IDR_PNG_EDITMID, IDR_PNG_EDITMID, IDR_PNG_EDITMID,
			IDR_PNG_EDITMID, IDR_PNG_EDITMID, IDR_PNG_EDITMID,
			IDR_PNG_EDITMIDDIS, IDR_PNG_EDITMIDDIS, IDR_PNG_EDITMIDDIS,
			IDR_PNG_EDITDELETEDOWN, IDR_PNG_EDITDELETEDOWN , IDR_PNG_EDITDELETEDOWN);

		if ( bSetDisableImg )
		{
			pEdit->SetDisableImg(FALSE);
			pEdit->SetDisableColor( Color(46,55,76) );
		}
	}
}


void CUmcwebCommon::SetImgForTransEditTimeRgt( CTransparentEdit *pEdit, BOOL bSetDisableImg )
{
	if ( pEdit != NULL  )
	{
		pEdit->SetImage( IDR_PNG_EDITMID, IDR_PNG_EDITMID, IDR_PNG_EDITRIGHT,
			IDR_PNG_EDITMID, IDR_PNG_EDITMID, IDR_PNG_EDITRIGHT,
			IDR_PNG_EDITMIDDIS, IDR_PNG_EDITMIDDIS, IDR_PNG_EDITRIGHTDIS,
			IDR_PNG_EDITDELETE, IDR_PNG_EDITDELETEDOWN , IDR_PNG_EDITDELETEDOWN);

		if ( bSetDisableImg )
		{
			pEdit->SetDisableImg(FALSE);
			pEdit->SetDisableColor( Color(46,55,76) );
		}
	}
}

void CUmcwebCommon::SetImgForTransSearchEdit( CTransparentEdit *pEdit, BOOL bIsSearchEdit, s32 nFontSize, const CString& strText, s32 nLimitLen )
{
	if ( pEdit != NULL  )
	{
		pEdit->SetImage( IDR_PNG_EDITLEFT, IDR_PNG_EDITMID, IDR_PNG_EDITRIGHT,
			IDR_PNG_EDITLEFTSEL, IDR_PNG_EDITMIDSEL, IDR_PNG_EDITRIGHTSEL,
			IDR_PNG_EDITLEFTDIS, IDR_PNG_EDITMIDDIS, IDR_PNG_EDITRIGHTDIS,
			IDR_PNG_EDITDELETE, IDR_PNG_EDITDELETEDOWN , IDR_PNG_EDITSEARCH);
		
		pEdit->SetSearchEdit(bIsSearchEdit);
		pEdit->SetTipStr(strText);
		pEdit->SetFont( nFontSize, "微软雅黑" );   
		pEdit->SetLimitText( nLimitLen );
	}
}

void CUmcwebCommon::SetImgForTransIpEdit( CTransparentIpEdit *pIpEdit )
{
	if ( pIpEdit != NULL  )
	{
		pIpEdit->SetImage( IDR_PNG_EDITLEFT, IDR_PNG_EDITMID, IDR_PNG_EDITRIGHT,
			IDR_PNG_EDITLEFTSEL, IDR_PNG_EDITMIDSEL, IDR_PNG_EDITRIGHTSEL,
			IDR_PNG_EDITLEFTDIS, IDR_PNG_EDITMIDDIS, IDR_PNG_EDITRIGHTDIS,
			IDR_PNG_EDITDELETE, IDR_PNG_EDITDELETEDOWN );

		pIpEdit->SetDisableImg(FALSE);
		pIpEdit->SetDisableColor( Color(46,55,76) );
	}
}

void CUmcwebCommon::SetTextTransStatic( CTransparentStatic *pStatic, const CString& strText, s32 nFontSize, Color color )
{
	if ( pStatic != NULL )
	{
		pStatic->SetWindowText(strText);
		pStatic->SetTextAlign(StringAlignmentNear);
		pStatic->SetTextColor(color);
		pStatic->SetFont( nFontSize, "微软雅黑" );
	}
}

void CUmcwebCommon::SetTextTransCheckBtn( CTransparentCheckButton *pCheckBtn, const CString& strText, s32 nFontSize, Color color )
{
	if ( pCheckBtn != NULL )
	{
		pCheckBtn->SetImage( IDR_PNG_CHECK_SEL, IDR_PNG_CHECK_SEL, IDR_PNG_CHECK_SELDIS, IDR_PNG_CHECK_UNSEL, IDR_PNG_CHECK_UNSEL, IDR_PNG_CHECK_UNSELDIS );
		pCheckBtn->SetFontSpan(0);
		pCheckBtn->SetWindowText(strText);
		pCheckBtn->SetTextColor( Color(46, 55, 76) );
		pCheckBtn->SetFont(11);
		pCheckBtn->SetButtonStyle( WS_CHILD|WS_CLIPSIBLINGS|BS_AUTOCHECKBOX  );
	}
}

void CUmcwebCommon::SetTextTransRadioBtn( CTransparentCheckButton *pCheckBtn, const CString& strText, s32 nFontSize, Color color )
{
	if ( pCheckBtn != NULL )
	{
		pCheckBtn->SetImage( IDR_PNG_RADIO_SEL, IDR_PNG_RADIO_SEL, IDR_PNG_RADIO_SELDIS, IDR_PNG_RADIO_UNSEL, IDR_PNG_RADIO_UNSEL, IDR_PNG_RADIO_UNSELDIS );
		pCheckBtn->SetFontSpan(0);
		pCheckBtn->SetWindowText(strText);
		pCheckBtn->SetTextColor( Color(46, 55, 76) );
		pCheckBtn->SetFont(11);
		pCheckBtn->SetButtonStyle( WS_CHILD|WS_CLIPSIBLINGS|BS_AUTOCHECKBOX  );
	}
}

unsigned int CUmcwebCommon::GetUniqID()
{
	static unsigned int wID = 10000;
	return wID++;
}

void CUmcwebCommon::SetImgForLetter( CLetterIndex* pLetterIndexTmp )
{
	pLetterIndexTmp->SetImage(g_arrPngId);
}

bool CUmcwebCommon::IsValidTPStr( const CString& strText )
{
	CString strError = INVALID_ALIAS_FOR_CODE;
	CString str(strText);
	CString strRe = str.SpanExcluding( strError );
	if ( strRe != str )
	{
		return false;
	} 

    return true;
}

bool CUmcwebCommon::IsAllNumber( const CString& strText )
{
	LPCTSTR  lpstr = (LPCTSTR)strText; 
	
    s32 nLen = _tcslen( lpstr );
    if ( nLen == 0 )
    {
        return false;
    }
	
    s32 nIndex = _tcsspn( lpstr, _T("0123456789") );
	
	if ( nLen == nIndex )
	{
		return true;
	}
	return false;
}

bool CUmcwebCommon::IsAllE164Number( const CString& strText )
{
	LPCTSTR  lpstr = (LPCTSTR)strText; 
	
    int nLen = _tcslen( lpstr );
    if ( nLen == 0 )
    {
        return false;
    }
	
    int nIndex = 0;
	
	nIndex = _tcsspn( lpstr, _T("*#") );
	
	if ( nLen == nIndex )
	{
		return false;
	}
	
	nIndex = _tcsspn( lpstr, _T("0123456789*#") );
	
	if ( nLen == nIndex )
	{
		return true;
	}
	
	return false;
}

BOOL CUmcwebCommon::HZPYMatchList( const CString& strTextInput,  const CString& strTextSrc )
{
	// TODO: Add your control notification handler code here	
	if ( strTextInput.IsEmpty() )
	{
		return TRUE;
	}
	
	if ( strTextInput.GetLength() > MAX_FIND_HANZI_LEN )
	{
		return FALSE;
	}

	if ( strTextSrc.IsEmpty() )
	{
		return FALSE;
	}
	
    s8 hzstr[ MAX_FIND_HANZI_LEN + 1] = {0};
	
    strncpy( hzstr, strTextSrc, MAX_FIND_HANZI_LEN );
	
	CHZPYSearch hzpy;
	
	s8 arrDest[ MAX_FIND_HANZI_LEN + 1 ] = {0};	
    strncpy( arrDest, strTextInput, MAX_FIND_HANZI_LEN );   //检索内容
	
	BOOL bFind = FALSE;	
	bFind = hzpy.HZPYMatchList(arrDest, hzstr);
	
	return bFind;
}

bool CUmcwebCommon::MapValueCompare( std::pair<u16,CString> paData, CString strTarget )
{
	if ( paData.second == strTarget )
	{
		return true;
	} 
	else
	{
		return false;
	}
}

//数字轮转型
void CUmcwebCommon::PlusHourBtn( CTransparentEdit *pEdit ) 
{
	if ( pEdit == NULL )
	{
		return;
	}

	CString strHour;
	pEdit->GetWindowText(strHour);
	
	s32 nHour;
	nHour = atoi(strHour);

	if( 23 == nHour )
	{
		nHour = 0;
	}else
    {
        nHour++;
    }
    
	s8 bufHour[3] = { 0 };
	sprintf( bufHour, "%.2d", nHour );
	pEdit->SetWindowText(bufHour);
}

void CUmcwebCommon::SubHourBtn( CTransparentEdit *pEdit )
{
	if ( pEdit == NULL )
	{
		return;
	}

	CString strHour;
	pEdit->GetWindowText(strHour);
	
	s32 nHour;
	nHour = atoi(strHour);
	
	if( 0 == nHour )
	{
        nHour = 23;
		
	}else
	{
        nHour--;		
	}
	s8 bufHour[3] = { 0 };
	sprintf( bufHour, "%.2d", nHour );
	pEdit->SetWindowText(bufHour);
}

void CUmcwebCommon::PlusMinBtn( CTransparentEdit *pEdit )
{
	if ( pEdit == NULL )
	{
		return;
	}

	CString strMin;
	pEdit->GetWindowText(strMin);
	
	s32 nMin;
	nMin = atoi(strMin);

	if( 59 == nMin )
	{
        nMin = 0;
		
	}else
	{
        nMin++;		
    }
    
	s8 bufHour[3] = { 0 };
	sprintf( bufHour, "%.2d", nMin );
	pEdit->SetWindowText(bufHour);
}

void CUmcwebCommon::SubMinBtn( CTransparentEdit *pEdit ) 
{
	if ( pEdit == NULL )
	{
		return;
	}

	CString strMin;
	pEdit->GetWindowText(strMin);
	
	s32 nMin;
	nMin = atoi(strMin);
	
    if( 0 == nMin )
	{
        nMin = 59;
		
	}else
	{
        nMin--;		
    }
	
	s8 bufHour[3] = { 0 };
	sprintf( bufHour, "%.2d", nMin );
	pEdit->SetWindowText(bufHour);
}

void CUmcwebCommon::PlusSecBtn( CTransparentEdit *pEdit )
{
	if ( pEdit == NULL )
	{
		return;
	}

	CString strSec;
	pEdit->GetWindowText(strSec);
	
	s32 nSec;
	nSec = atoi(strSec);

    if( 59 == nSec )
    {
        nSec = 0;
        
    }else
    {
        nSec++;		
    }
	
	s8 bufHour[3] = { 0 };
	sprintf( bufHour, "%.2d", nSec );
	pEdit->SetWindowText(bufHour);
}

void CUmcwebCommon::SubSecBtn( CTransparentEdit *pEdit ) 
{
	if ( pEdit == NULL )
	{
		return;
	}

	CString strSec;
	pEdit->GetWindowText(strSec);
	
	s32 nSec;
	nSec = atoi(strSec);

    if( 0 == nSec )
	{
        nSec = 59;
		
	}else
	{
        nSec--;		
    }
	
	s8 bufHour[3] = { 0 };
	sprintf( bufHour, "%.2d", nSec );
	pEdit->SetWindowText(bufHour);
}

void CUmcwebCommon::GetResolutionScale( float &fx, float &fy)
{ 
    int oriX = BASE_SCREEN_WIDTH_INIE;
	int oriY = BASE_SCREEN_HEIGHT_INIE;
    
    long curX =  GetSystemMetrics(SM_CXSCREEN );
    long curY = GetSystemMetrics(SM_CYSCREEN);

	if ( curX < 1280 )
	{
		fx =  (float)curX / 1280;
	}
	else
	{
		if ( oriX != 0 )
		{
			fx =  (float)curX / oriX;
		}
	}

	if ( curY < 768 )
	{
		fy =  (float)curY / 768;
	}
	else
	{
		if ( oriY != 0 )
		{
			fy =  (float)curY / oriY;
		}
	}
}

//分辨率自适应
void CUmcwebCommon::ResolutionAdp( long &nx, long &ny)
{
    int oriX = BASE_SCREEN_WIDTH;
	int oriY = BASE_SCREEN_HEIGHT;
    
    long curX =  GetSystemMetrics(SM_CXSCREEN );
    long curY = GetSystemMetrics(SM_CYSCREEN);
    
    if ( oriX != 0 )
    {
        nx = nx* curX / oriX;
    }
    
    if ( oriY != 0 )
    {
        ny = ny* curY / oriY;
    }
}

//字体大小自适应
void CUmcwebCommon::FontSizeAdp( int &nFontSize )
{   
    // 字体随分辨率等比变化 2012-2-9 by yjj
    float fx, fy;
    CUmcwebCommon::GetResolutionScale( fx, fy );
    if ( fx < fy )
    {
        fx  = fy;
    }
    
    nFontSize *= fx; 
}

void CUmcwebCommon::ResetChildWndSize( HWND hParentWnd )
{
    HWND hwndChild = ::GetWindow( hParentWnd, GW_CHILD );

    float fx, fy;
	CUmcwebCommon::GetResolutionScale( fx, fy );

	CRect rect;
	::GetWindowRect( hParentWnd, &rect );
    ::SetWindowPos( hParentWnd, NULL, rect.left*fx, rect.top*fy, rect.Width()*fx, rect.Height()*fy, SWP_NOZORDER );

    while( hwndChild != NULL )
    {
        ResetChildWndSize( hwndChild );
        hwndChild = ::GetWindow( hwndChild, GW_HWNDNEXT );
    }
}

void CUmcwebCommon::TimeToTm( struct tm& tmDate, const time_t& timeDate )
{
	time_t tm = timeDate;
	tmDate = *(localtime(&tm));
	tmDate.tm_year += 1900;
	tmDate.tm_mon += 1;
}

void CUmcwebCommon::GetTime( u32 dwTime, int& nHour, int& nMin, int& nSec )
{
	nSec = dwTime%60;
	nMin = (dwTime%3600)/60;
	nHour = dwTime/3600;
}