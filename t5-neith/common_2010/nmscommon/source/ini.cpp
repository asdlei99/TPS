// Ini.cpp: implementation of the CIni class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ini.h"
#include "kdvsys.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CIni::CIni( LPCTSTR pFileName, int nBufLen /* = 256 */)
{
	m_nBufLen = nBufLen;
	m_pcBuf = new TCHAR[m_nBufLen];
	SetFilePath(pFileName);
}

CIni::CIni(const CIni &cIni )
{
	m_nBufLen = cIni.m_nBufLen;
	m_strFileName = cIni.m_strFileName;
	m_pcBuf = new TCHAR[m_nBufLen];
	memcpy(m_pcBuf, cIni.m_pcBuf, m_nBufLen);
}

CIni& CIni::operator=(const CIni &cIni)
{
	delete[] m_pcBuf;
	m_nBufLen = cIni.m_nBufLen;
	m_strFileName = cIni.m_strFileName;
	m_pcBuf = new TCHAR[m_nBufLen];
	memcpy(m_pcBuf, cIni.m_pcBuf, m_nBufLen);

	return *this;
}

CIni::~CIni()
{
	delete[] m_pcBuf;
	m_pcBuf = NULL;
}

bool CIni::GetBool( LPCTSTR lpAppName, LPCTSTR lpKeyName, bool bDefault /* = false */ )
{
	ReEncode();
	int dwValue = 0;
#ifdef _WINDOWS_
	dwValue = GetPrivateProfileInt(lpAppName, lpKeyName, bDefault ? 1 : 0, m_strFileName.c_str());
#else
	GetRegKeyInt(m_strFileName.c_str(), lpAppName, lpKeyName, bDefault ? 1 : 0, &dwValue);
#endif
	return (0 != dwValue);
}

unsigned int CIni::GetInt( LPCTSTR lpAppName, LPCTSTR lpKeyName, unsigned int nDefalut /* = 0 */ )
{
	ReEncode();
	int dwValue = 0;
#ifdef _WINDOWS_
	dwValue = GetPrivateProfileInt(lpAppName, lpKeyName, nDefalut, m_strFileName.c_str());
#else
	GetRegKeyInt(m_strFileName.c_str(), lpAppName, lpKeyName, nDefalut, &dwValue);
#endif
	return dwValue;
}

unsigned long CIni::GetString( LPCTSTR lpAppName, LPCTSTR lpKeyName, LPTSTR lpValue, int nSize, LPCTSTR lpDefault /* = "" */ )
{
	ReEncode();
	unsigned long dwLenth = 0;
#ifdef _WINDOWS_
	dwLenth = GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, lpValue, nSize, m_strFileName.c_str());
#else
	GetRegKeyString(m_strFileName.c_str(), lpAppName, lpKeyName, lpDefault, lpValue, nSize);
	dwLenth = strlen(lpValue);
#endif
	return dwLenth;
}

unsigned long CIni::GetString( LPCTSTR lpAppName, LPCTSTR lpKeyName, tstring& strValue, LPCTSTR lpDefault /* = "" */ )
{
	unsigned long rtn = GetString(lpAppName, lpKeyName, m_pcBuf, m_nBufLen, lpDefault);
	strValue = m_pcBuf;
	return rtn;
}

bool CIni::SetString( LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpValue )
{
	CheckFileCodeHeadInfo();
#ifdef _WINDOWS_
	return (WritePrivateProfileString(lpAppName, lpKeyName, lpValue, m_strFileName.c_str()) != FALSE);
#else
	return (SetRegKeyString(m_strFileName.c_str(),lpAppName, lpKeyName, lpValue) != FALSE);
#endif
}

bool CIni::SetString( LPCTSTR lpAppName, LPCTSTR lpKeyName, const tstring& strValue )
{
	CheckFileCodeHeadInfo();
	return (SetString(lpAppName, lpKeyName, strValue.c_str()) != FALSE);
}

bool CIni::SetInt( LPCTSTR lpAppName, LPCTSTR lpKeyName, int nValue )
{
	return (SetString(lpAppName, lpKeyName, _itot(nValue, m_pcBuf, 10)) != FALSE);
}

bool CIni::SetBool( LPCTSTR lpAppName, LPCTSTR lpKeyName, bool bValue )
{
	return (SetString(lpAppName, lpKeyName, bValue ? _T("1") : _T("0")) != FALSE);
}

bool CIni::SetSection( LPCTSTR lpAppName, LPCTSTR lpString )
{
	CheckFileCodeHeadInfo();
#ifdef _WINDOWS_
	return(WritePrivateProfileSection(lpAppName, lpString, m_strFileName.c_str()) != FALSE);
#else
	return(SetRegKeySection(m_strFileName.c_str(), lpAppName, lpString, 0, NULL) != FALSE);
#endif	
}

bool CIni::Clear()
{
	FILE *pFile;
	pFile = _tfopen( m_strFileName.c_str(), _T("w+") );

	if ( pFile == NULL)
	{
		return false;
	}
	// 写入bom头
	char head[2] = { (char)0xFF, (char)0xFE };
	fwrite( head, sizeof(char), 2, pFile );
	fclose( pFile );
	return true;
}

void CIni::SetFilePath( LPCTSTR pFileName )
{
	if ( pFileName != 0 )
	{
		m_strFileName = pFileName;
		#ifdef _UNICODE
		if ( Exist()  )
		{
			ReEncode();
		}
		#endif
	}
}

bool CIni::Exist()
{
	FILE *pFile;
	pFile = _tfopen( m_strFileName.c_str(), _T("r") );

	if ( pFile == NULL )
	{
		return false;
	}
	
	fclose( pFile );
	return true;
}

//每次读写之前检查下是否已经包含文件头，确保是unicode编码   lbg 2013.06.21
void CIni::CheckFileCodeHeadInfo()
{
	#ifdef _UNICODE
	if ( !Exist()  )
	{
		Clear();
	}
	else
	{
		ReEncode();
	}
	#endif
}

bool CIni::ReEncode()
{
	unsigned char byType = GetCodeType();
	if ( byType == UTF8_FORMAT || byType == LOCAL_FORMAT )
	{
		FILE *pFile = _tfopen( m_strFileName.c_str(), _T("rb+") );
		if ( pFile )
		{
			fseek( pFile, 0L, SEEK_END );
			size_t size = ftell( pFile );
			if ( size == 0 )
			{
				Clear();
			}
			else
			{
				unsigned int dwCodePage = CP_ACP;

				// UTF8 移三位
				if ( byType == UTF8_FORMAT )
				{
					fseek( pFile, 3L, SEEK_SET );
					dwCodePage = CP_UTF8;
				}
				else
				{
					fseek( pFile, 0L, SEEK_SET );
				}

				char* pBuf = new char[size + 1];
				size_t nSize = fread( pBuf, sizeof(char), size, pFile );
				pBuf[nSize] = 0;
				CA2W u16File( pBuf, dwCodePage );
				delete[] pBuf;
				fclose( pFile );

				// 清空内容，写入头
				Clear();
				pFile = _tfopen( m_strFileName.c_str(), _T("rb+") );
				if ( pFile )
				{
					// 跳过头
					fseek( pFile, 2L, SEEK_SET );
					fwrite( (void*)u16File.m_psz, sizeof(WCHAR), wcslen( u16File.m_psz ), pFile );
					fclose( pFile );
				}
			}
			return true;
		}
	}
	return false;
}

unsigned char CIni::GetCodeType()
{
	FILE *pFile;
	pFile = _tfopen( m_strFileName.c_str(), _T("rb") );
	unsigned char byCodeType = UNKNOWN_FILE;
	if ( pFile != NULL )
	{
		char head[3] = {0};
		fread( head, sizeof(char), 3, pFile );
		if ( char(0xEF) == head[0] && char(0xBB) == head[1] && char(0xBF) == head[2] )
		{
			byCodeType = UTF8_FORMAT;
		}
		else if ( char(0xFF) == head[0] && char(0xFE) == head[1] )
		{
			byCodeType = UTF16_LE_FORMAT;
		}
		else if ( char(0xFE) == head[0] && char(0xFF) == head[1] )
		{
			byCodeType = UTF16_BE_FORMAT;
		}
		else
		{
			byCodeType = LOCAL_FORMAT;
		}
		fclose( pFile );
	}
	return byCodeType;
};
