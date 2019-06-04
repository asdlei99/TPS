#include "owslib.h"

CFileCtrl::CFileCtrl():
m_pFile(NULL)
{
}

CFileCtrl::~CFileCtrl()
{
}

BOOL CFileCtrl::Close()
{
	if ( NULL != m_pFile )
	{
		fclose(m_pFile);
		m_pFile = NULL;
	}

	return TRUE;
}

BOOL CFileCtrl::Open( const std::string& strFile, const std::string& strType )
{
	m_pFile = fopen( strFile.c_str(), strType.c_str() );  //读写打开一个文本文件，允许读或在文本末追加数据,不存在文件则创建
	if( NULL == m_pFile )
	{
		return FALSE;
	}

	return TRUE;
}
		  
u64 CFileCtrl::GetLen()
{
	if ( NULL == m_pFile )
	{
		return 0;
	}

	fseek( m_pFile, 0L, SEEK_END );
	u64 nLen = ftell(m_pFile);
	return nLen;
}

BOOL CFileCtrl::Write( const u8* pBuf, u64 nBufLen, s16 nPos, u64 nMaxLen, u64 nSeekPos )
{
	if ( NULL != m_pFile )
	{
		//u64 nLen = GetLen();
		if ( nMaxLen < nBufLen + nSeekPos /*nLen + nBufLen + nSeekPos*/ )
		{
			return FALSE;
		}

		fseek( m_pFile, nSeekPos, nPos );
		fwrite( (void*)pBuf, nBufLen, 1, m_pFile );	
		fflush(m_pFile);						//即时缓存读写 
	}

	return TRUE;
}

u64 CFileCtrl::Read( u8* pBuf, u64 nBufLen, u64 nSeekPos )
{
	u64 nLen = GetLen();
	if ( nSeekPos + nBufLen > nLen )
	{
		return 0;
	}

	fseek( m_pFile, nSeekPos, SEEK_SET );
	return fread( pBuf, 1, nBufLen, m_pFile );
}
