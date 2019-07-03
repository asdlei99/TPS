// UIDataMgr.cpp: implementation of the CUIDataMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UIDataMgr.h"
#include "hzpysearch.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CUIDataMgr *CUIDataMgr::m_pThis = NULL;
CUIDataMgr::CUIDataMgr()
{

}

CUIDataMgr::~CUIDataMgr()
{

}


CUIDataMgr* CUIDataMgr::GetSingleTon()
{
    if ( m_pThis == NULL )
    {
        m_pThis = new CUIDataMgr();
    }
    return m_pThis;
}

void CUIDataMgr::GetCharExtent( IN const WCHAR * strCharacters, Gdiplus::Font*pFont, CSize& cSize )
{
    HDC hDc = ::GetDC( NULL ); 
    Graphics graph(hDc);
    RectF rcf;
    graph.MeasureString(strCharacters,-1,pFont,PointF(0,0),&rcf); 

    cSize.cx = rcf.Width;
    cSize.cy =  rcf.Height;

    if ( rcf.Width > cSize.cx )
    {
        cSize.cx += 1;
    }

    if ( rcf.Height > cSize.cy )
    {
        cSize.cy += 1;
    }

    ::ReleaseDC(NULL, hDc ); 
}



BOOL CUIDataMgr::HZPYMatchList( const CString strTextInput,  const CString strTextSrc )
{
	// TODO: Add your control notification handler code here	
	if ( strTextInput.IsEmpty() )
	{
		return TRUE;
	}

	if ( strTextSrc.IsEmpty() )
	{
		return FALSE;
	}
	
	if ( strTextInput.GetLength() > MAX_FIND_HANZI_LEN )
	{
		return FALSE;
	}
		
    char hzstr[ MAX_FIND_HANZI_LEN + 1] = {0};
	
    strncpy( hzstr, CT2A(strTextSrc), MAX_FIND_HANZI_LEN );
		
	CHZPYSearch hzpy;
	
	char arrDest[ MAX_FIND_HANZI_LEN + 1 ] = {0};	
    strncpy( arrDest, CT2A(strTextInput), MAX_FIND_HANZI_LEN );   //检索内容
	
	BOOL bFind = FALSE;	
	bFind = hzpy.HZPYMatchList(arrDest, hzstr);
	
	return bFind;
}

BOOL32 CUIDataMgr::IsValidIpV6(LPCSTR lptrIPStr)
{
    int nCheckChar = 0;
    int nCheckColon = 0;
    int nEllipsis = 0;
    s32 nLen = strlen( lptrIPStr );    //  字符串长度
    for ( s32 nCount = 0 ; nCount < nLen ; ++nCount )
    {
        if ((lptrIPStr[nCount] >= '0') && (lptrIPStr[nCount] <= '9'))
        {
            nCheckChar = 0;
        }
        else if ((lptrIPStr[nCount] >= 'a') && (lptrIPStr[nCount] <= 'f'))
        {
            nCheckChar = 0;
        }
        else if ((lptrIPStr[nCount] >= 'A') && (lptrIPStr[nCount] <= 'F'))
        {
            nCheckChar = 0;
        }
        else if (lptrIPStr[nCount] == ':')
        {
            nCheckColon++;
            nCheckChar++;
            if (nCheckChar > 2)//连续三个冒号
            {
                return 0;
            }
            else if (nCheckChar == 2)
            {
                nEllipsis++;
                if (nEllipsis > 1)//超过一次的省略
                {
                    return 0;
                }
            }
        }
        else
        {
            return 0;
        }
    }
    return (nCheckColon == 7) || (nEllipsis != 0);
}

bool CUIDataMgr::IsAllE164Number( String strText )
{
	LPCTSTR  lpstr  =  (LPCTSTR)strText.c_str(); 

	s32 nLen = _tcslen( lpstr );
	if ( nLen == 0 )
	{
		return false;
	}

	s32 nIndex = _tcsspn( lpstr, _T("0123456789*,#") );

	if ( nLen == nIndex )
	{
		return true;
	}
	return false;
}

//  ; /   ?   : @ & = + $ , % …… & ^ 空格 tab
bool CUIDataMgr::IsValidTPStr( String strText )
{
	CString strError = INVALID_ALIAS_FOR_CODE;
	CString str(strText.c_str());
	CString strRe = str.SpanExcluding( strError );
	if ( strRe != str )
	{
		return false;
	} 
	return true;
}

bool CUIDataMgr::IsValidFolderStr( String strText )
{
    CString strError = INVALID_ALIAS_FOR_FLODER;
    CString str(strText.c_str());
    CString strRe = str.SpanExcluding( strError );
    if ( strRe != str )
    {
        return false;
    } 
    return true;
}


bool CUIDataMgr::FileMgrCompare( TFileItem& tItem1, TFileItem& tItem2 )
{   
    CString strLetter1;
    CString strLetter2;	

	TCHAR   achFileName[MAX_PATH+1];
    memcpy(&achFileName, tItem1.achFileName, sizeof(tItem1.achFileName));
    CStringA strName1;
    strName1.Format( "%s", (CT2A)achFileName );

	GetFirstLetter( strName1, strLetter1 );

    memset(&achFileName, 0, sizeof(achFileName));
    memcpy(&achFileName, tItem2.achFileName, sizeof(tItem2.achFileName));
    CStringA strName2;
    strName2.Format( "%s", (CT2A)achFileName );

	GetFirstLetter( strName2, strLetter2 );

	if ( strLetter1.Compare( strLetter2 ) < 0 )
	{
	   return true;
	}
	else
	{
	   return false;
	}
}


void CUIDataMgr::GetFirstLetter(CStringA strName, CString& strFirstLetter)
{
    BYTE ucHigh, ucLow;
    int  nCode;
    CString strRet;

    strFirstLetter.Empty();
    int nStrLength = strName.GetLength();

    for ( int i = 0; i < nStrLength; i++ )
    {
        if ( (BYTE)strName[i] < 0x80 )
        {
            strRet = strName[i];
            strRet.MakeUpper();
            strFirstLetter += strRet;
            continue;
        }

        if ( i+1 >= nStrLength )
        {
            break;
        }

        ucHigh = (BYTE)strName[i];		
        ucLow  = (BYTE)strName[i+1];
        if ( ucHigh < 0xa1 || ucLow < 0xa1)
        {
            continue;
        }
        else
        {
            nCode = (ucHigh - 0xa0) * 100 + ucLow - 0xa0;
        }

        if ( nCode < 5590 )
        {
            strRet = FirstLetter( nCode );
        }
        else
        {
            strRet = CPYChar::GetPYChar( strName[i], strName[i+1] ); 
        }

        strFirstLetter += strRet;
        i++;
    }
}


CString CUIDataMgr::FirstLetter(int nCode)
{
    if(nCode >= 1601 && nCode < 1637) return _T("A");
    if(nCode >= 1637 && nCode < 1833) return _T("B");
    if(nCode >= 1833 && nCode < 2078) return _T("C");
    if(nCode >= 2078 && nCode < 2274) return _T("D");
    if(nCode >= 2274 && nCode < 2302) return _T("E");
    if(nCode >= 2302 && nCode < 2433) return _T("F");
    if(nCode >= 2433 && nCode < 2594) return _T("G");
    if(nCode >= 2594 && nCode < 2787) return _T("H");
    if(nCode >= 2787 && nCode < 3106) return _T("J");
    if(nCode >= 3106 && nCode < 3212) return _T("K");
    if(nCode >= 3212 && nCode < 3472) return _T("L");
    if(nCode >= 3472 && nCode < 3635) return _T("M");
    if(nCode >= 3635 && nCode < 3722) return _T("N");
    if(nCode >= 3722 && nCode < 3730) return _T("O");
    if(nCode >= 3730 && nCode < 3858) return _T("P");
    if(nCode >= 3858 && nCode < 4027) return _T("Q");
    if(nCode >= 4027 && nCode < 4086) return _T("R");
    if(nCode >= 4086 && nCode < 4390) return _T("S");
    if(nCode >= 4390 && nCode < 4558) return _T("T");
    if(nCode >= 4558 && nCode < 4684) return _T("W");
    if(nCode >= 4684 && nCode < 4925) return _T("X");
    if(nCode >= 4925 && nCode < 5249) return _T("Y");
    if(nCode >= 5249 && nCode < 5590) return _T("Z");

    return _T("");
}

void CUIDataMgr::GetClearIP(CString& strIp)
{
    int nIp[4] = {0};
    CString strClearIp = _T("");
    sscanf( CT2A(strIp), "%d.%d.%d.%d", &nIp[0],&nIp[1],&nIp[2],&nIp[3] );
    strClearIp.Format( _T("%d.%d.%d.%d"), nIp[0], nIp[1], nIp[2], nIp[3] );
    strIp = strClearIp;
}

CString CUIDataMgr::UTF82Unicode(const char* szU8)
{
    int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);
    wchar_t* wszString = new wchar_t[wcsLen + 1];
    ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);
    wszString[wcsLen] = '\0';
    CString unicodeString(wszString);
    delete[] wszString;
    wszString = NULL;
    return unicodeString;
}