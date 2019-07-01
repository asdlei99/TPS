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
CUIDataMgr::CUIDataMgr():
                        m_strSimulateCnsDlgName(_T("")),
                        m_strSchmMainMenuShow(_T("")),
                        m_tLockScreenInfo(),
                        m_emLocalCnsState (emLocalCnsIdle),    ///<本地cns的当前状态
						m_strCurShowWnd( _T("") )

{
    m_bIsPcVersion = TRUE;

    m_sizeMain.cx = 1920;
    m_sizeMain.cy = 1200;
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

void CUIDataMgr::SetLockScreenInfo( TLockScreenInfo tInfo )
{
    m_tLockScreenInfo = tInfo;
}

TLockScreenInfo& CUIDataMgr::GetLockScreenInfo()
{
    return m_tLockScreenInfo;
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
 
    int nLength = CStringA(strTextSrc).GetLength();
	
    if ( nLength > MAX_FIND_HANZI_LEN )
    {   //只有临时会议模板会导致名称超过32字节
        int nIndex = strTextSrc.Find( _T("的临时会议") );
        CString strTextSrcNew = strTextSrc.Left( nIndex );
        strncpy( hzstr, CT2A(strTextSrcNew), sizeof(hzstr)-1 );
    }
    else
    {
        strcpy( hzstr, CT2A(strTextSrc) );
    }
    		
	CHZPYSearch hzpy;
	
	char arrDest[ MAX_FIND_HANZI_LEN + 1 ] = {0};	
    strcpy( arrDest, CT2A(strTextInput) );   //检索内容
	
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

	s32 nIndex = _tcsspn( lpstr, _T("0123456789*,") );

	if ( nLen == nIndex )
	{
		return true;
	}
	return false;
}

//  ; /   ?   : @ & = + $ , % …… & ^ 空格 tab ——
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

bool CUIDataMgr::IsValidPWStr( CString szPWStr )
{
	if (szPWStr.IsEmpty())
	{
		return false;
	}
	//要求:8-16个字符，至少包含字母，数字，特殊字符三个中的两个
	int nCount = szPWStr.GetLength();
	if (nCount < 8 || nCount > 16)
	{
		return false;
	}
	//纯数字
	CString szTemp = szPWStr.SpanIncluding(_T("0123456789"));
	if (szTemp == szPWStr)
	{
		return false;
	}
	//纯英文字母
	szTemp = szPWStr.SpanIncluding(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	if (szTemp == szPWStr)
	{
		return false;
	}
	//纯特殊字符
	szTemp = szPWStr.SpanExcluding(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"));
	if (szTemp == szPWStr)
	{
		return false;
	}
	//除限定字符外的字符
	szTemp = szPWStr.SpanIncluding(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_."));
	if (szTemp != szPWStr)
	{
		return false;
	}

	return true;
}

void CUIDataMgr::GetPWlevel( CString szPWStr,  TPWElement &tPWElementLevel, TPWElement &tPWElementState )
{
	bool bhavechar = false;
	bool bhavedigit = false;
	bool bhavespcial = false;
	if (szPWStr.GetLength() < 8 || szPWStr.GetLength() > 16)
	{
		tPWElementState.m_bElement0 = true;//密码长度不在范围内
	}

	for (int i = 0 ; i < szPWStr.GetLength() ; i++)
	{
		if( ( szPWStr.GetAt(i) >= 'a' && szPWStr.GetAt(i) <= 'z' ) ||
			( szPWStr.GetAt(i) >= 'A' && szPWStr.GetAt(i) <= 'Z' ) )//是 英文字符
		{
			tPWElementLevel.m_bElement0 = true;
			bhavechar = true;
		}
		else if (szPWStr.GetAt(i) >= '0' && szPWStr.GetAt(i) <= '9' )//是 数字
		{
			tPWElementLevel.m_bElement0 = true;
			bhavedigit = true;
		}
		else if( szPWStr.GetAt(i) == '_' ) //是 _
		{
			tPWElementLevel.m_bElement1 = true;
			bhavespcial = true;
		}
		else if( szPWStr.GetAt(i) == '.' )//是 .
		{
			tPWElementLevel.m_bElement2 = true;
			bhavespcial = true;
		}
		else//其它
		{
			tPWElementState.m_bElement1 = true;//包含范围内的其它字符
		}
	}

	int numtype = 0;
	if (bhavechar)
	{
		numtype++;
	}
	if (bhavedigit)
	{
		numtype++;
	}
	if (bhavespcial)
	{
		numtype++;
	}
	if (numtype < 2)
	{
		tPWElementState.m_bElement2 = true;//只包含一种类型
	}
}

bool CUIDataMgr::UserItemCompare( CUserFullInfo& tItem1, CUserFullInfo& tItem2 )
{
	CString strLetter1;
	CString strLetter2;	

	GetFirstLetter( tItem1.GetName(), strLetter1 );
	GetFirstLetter( tItem2.GetName(), strLetter2 );

	if ( strLetter1.Compare( strLetter2 ) < 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CUIDataMgr::CnsInfoCompare(TCnsInfo& tInfo1, TCnsInfo& tInfo2)
{
	if ( tInfo1 == tInfo2 )
	{
		return true;
	}

	CString strLetter1;
	CString strLetter2;	

	GetFirstLetter( tInfo1.m_achRoomName, strLetter1 );
	GetFirstLetter( tInfo2.m_achRoomName, strLetter2 );

    //始终让模板显示在最后
    CString strNewLetter1;
    CString strNewLetter2;
    if ( tInfo1.m_emEpType == emTPEndpointTypeUMS || tInfo1.m_emEpType == emTPEndpointH323MCU )
    {
        strNewLetter1.Format( _T("}%s"), (LPCTSTR)strLetter1 );
    }
    else
    {
        strNewLetter1 = strLetter1;
    }
    if ( tInfo2.m_emEpType == emTPEndpointTypeUMS || tInfo2.m_emEpType == emTPEndpointH323MCU )
    {
        strNewLetter2.Format( _T("}%s"), (LPCTSTR)strLetter2 );
    }
    else
    {
        strNewLetter2 = strLetter2;
    }

	if ( strNewLetter1.Compare( strNewLetter2 ) < 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CUIDataMgr::SelViewCompare(TSelViewInfo& tSelViewInfo1, TSelViewInfo& tSelViewInfo2)
{
	CString strLetter1;
	CString strLetter2;	

	GetFirstLetter( tSelViewInfo1.m_achRoomName, strLetter1 );
	GetFirstLetter( tSelViewInfo2.m_achRoomName, strLetter2 );

	if ( strLetter1.Compare( strLetter2 ) < 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CUIDataMgr::ConfTempCompare( TTPAlias& tAlias1, TTPAlias& tAlias2 )
{   
    CString strLetter1;
    CString strLetter2;	

	GetFirstLetter( tAlias1.m_abyAlias, strLetter1 );
	GetFirstLetter( tAlias2.m_abyAlias, strLetter2 );

	if ( strLetter1.Compare( strLetter2 ) < 0 )
	{
	   return true;
	}
	else
	{
	   return false;
	}
}

bool CUIDataMgr::AddrItemCompare( TAddrItem& tItem1, TAddrItem& tItem2 )
{
	if ( tItem1 == tItem2 )
	{
		return true;
	}

	if ( tItem1.strNameLetter.Compare( tItem2.strNameLetter ) < 0 )
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
    if (strIp == _T(""))
    {
        return;
    }
    int nIp[4] = {0};
    CString strClearIp = _T("");
    swscanf( strIp, _T("%d.%d.%d.%d"), &nIp[0],&nIp[1],&nIp[2],&nIp[3] );
    strClearIp.Format( _T("%d.%d.%d.%d"), nIp[0], nIp[1], nIp[2], nIp[3] );
    strIp = strClearIp;
}