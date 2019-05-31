/*=============================================================================
模   块   名: ATL7编码转换类
文   件   名: atlconv7_vc6.h
相 关  文 件: 
文件实现功能: 
由于VC6所带ATL中，编码转换红A2T、T2A、A2W等宏使用不当会导致堆栈溢出
因此移植VS2010中所带ATL7的编码转换类CA2T、CT2A等到VC6
此文件在高于VS2010的版本上无效
作        者: 邹俊龙
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2013/01/23  4.7     邹俊龙        创建
=============================================================================*/
#pragma once

#if ( _MSC_VER <= 1200 )

inline UINT WINAPI _AtlGetConversionACP() throw()
{
#ifdef _CONVERSION_DONT_USE_THREAD_LOCALE
	return CP_ACP;
#else
	return CP_THREAD_ACP;
#endif
}

template <class _CharType>
inline void AtlConvAllocMemory(
	_CharType** ppBuff,
	int nLength,
	_CharType* pszFixedBuffer,
	int nFixedBufferLength)
{
	ASSERT(ppBuff != NULL);
	ASSERT(nLength >= 0);
	ASSERT(pszFixedBuffer != NULL);

	//if buffer malloced, try to realloc.
	if (*ppBuff != pszFixedBuffer)
	{
		if( nLength > nFixedBufferLength )
		{
			_CharType* ppReallocBuf = static_cast< _CharType* >( realloc(*ppBuff, nLength * sizeof( _CharType ) ) );
			ASSERT( ppReallocBuf != NULL );
//			if (ppReallocBuf == NULL) 
//			{
//				AtlThrow( E_OUTOFMEMORY );
//			}
			*ppBuff = ppReallocBuf;
		} else
		{
			free(*ppBuff);
			*ppBuff=pszFixedBuffer;
		}

	} else //Buffer is not currently malloced.
	{
		if( nLength > nFixedBufferLength )
		{
			*ppBuff = static_cast< _CharType* >( calloc(nLength,sizeof( _CharType ) ) );
		} else
		{			
			*ppBuff=pszFixedBuffer;
		}
	}

	ASSERT( *ppBuff != NULL );

// 	if (*ppBuff == NULL)
// 	{
//		AtlThrow( E_OUTOFMEMORY );
//	}
}

#define ATLCONV_DEADLAND_FILL 0xFE

template <class _CharType>
inline void AtlConvFreeMemory(
	_CharType* pBuff,
	_CharType* pszFixedBuffer,
	int nFixedBufferLength)
{
	(nFixedBufferLength);
	if( pBuff != pszFixedBuffer )
	{
		free( pBuff );
	} 	
#ifdef _DEBUG
	else
	{		
		memset(pszFixedBuffer,ATLCONV_DEADLAND_FILL,nFixedBufferLength*sizeof(_CharType));
	}
#endif
}

template< int t_nBufferLength = 128 >
class CW2WEX
{
public:
	CW2WEX( LPCWSTR psz) :
		m_psz( m_szBuffer )
	{
		Init( psz );
	}
	CW2WEX(
			 LPCWSTR psz, 
			 UINT nCodePage) :
		m_psz( m_szBuffer )
	{
		(void)nCodePage;  // Code page doesn't matter

		Init( psz );
	}
	~CW2WEX()
	{
		AtlConvFreeMemory(m_psz,m_szBuffer,t_nBufferLength);
	}

	operator LPWSTR() const
	{
		return( m_psz );
	}

private:
	void Init( LPCWSTR psz)
	{
		if (psz == NULL)
		{
			m_psz = NULL;
			return;
		}
		int nLength = lstrlenW( psz )+1;
		AtlConvAllocMemory(&m_psz,nLength,m_szBuffer,t_nBufferLength);
//		ATLASSUME(m_psz != NULL);

		ASSERT( m_psz != NULL );
		memcpy( m_psz, psz, nLength*sizeof( wchar_t ));
	}

public:
	LPWSTR m_psz;
	wchar_t m_szBuffer[t_nBufferLength];

private:
	CW2WEX( const CW2WEX&);
	CW2WEX& operator=( const CW2WEX&);
};
typedef CW2WEX<> CW2W;

template< int t_nBufferLength = 128 >
class CA2AEX
{
public:
	CA2AEX( LPCSTR psz) :
		m_psz( m_szBuffer )
	{
		Init( psz );
	}
	CA2AEX(
			 LPCSTR psz, 
			 UINT nCodePage) :
		m_psz( m_szBuffer )
	{
		(void)nCodePage;  // Code page doesn't matter

		Init( psz );
	}
	~CA2AEX()
	{
		AtlConvFreeMemory(m_psz,m_szBuffer,t_nBufferLength);
	}

	operator LPSTR() const
	{
		return( m_psz );
	}

private:
	void Init( LPCSTR psz)
	{
		if (psz == NULL)
		{
			m_psz = NULL;
			return;
		}
		int nLength = lstrlenA( psz )+1;
		AtlConvAllocMemory(&m_psz,nLength,m_szBuffer,t_nBufferLength);		
		memcpy( m_psz, psz, nLength*sizeof( char ));
	}

public:
	LPSTR m_psz;
	char m_szBuffer[t_nBufferLength];

private:
	CA2AEX( const CA2AEX&);
	CA2AEX& operator=( const CA2AEX&);
};
typedef CA2AEX<> CA2A;

template< int t_nBufferLength = 128 >
class CA2CAEX
{
public:
	CA2CAEX( LPCSTR psz)  :
		m_psz( psz )
	{
	}
	CA2CAEX(
			 LPCSTR psz, 
			 UINT nCodePage) :
		m_psz( psz )
	{
		(void)nCodePage;
	}
	~CA2CAEX()
	{
	}
	
	 operator LPCSTR() const
	{
		return( m_psz );
	}
	
public:
	LPCSTR m_psz;

private:
	CA2CAEX( const CA2CAEX&);
	CA2CAEX& operator=( const CA2CAEX&);
};
typedef CA2CAEX<> CA2CA;

template< int t_nBufferLength = 128 >
class CW2CWEX
{
public:
	CW2CWEX( LPCWSTR psz) :
		m_psz( psz )
	{
	}
	CW2CWEX(
			 LPCWSTR psz, 
			 UINT nCodePage)  :
		m_psz( psz )
	{		
		UNREFERENCED_PARAMETER(nCodePage);
	}
	~CW2CWEX()
	{
	}

	 operator LPCWSTR() const
	{
		return( m_psz );
	}

public:
	LPCWSTR m_psz;

private:
	CW2CWEX( const CW2CWEX&);
	CW2CWEX& operator=( const CW2CWEX&);
};
typedef CW2CWEX<> CW2CW;

template< int t_nBufferLength = 128 >
class CA2WEX
{
public:
	CA2WEX( LPCSTR psz) :
		m_psz( m_szBuffer )
	{
		Init( psz, _AtlGetConversionACP() );
	}
	CA2WEX(
			 LPCSTR psz, 
			 UINT nCodePage) :
		m_psz( m_szBuffer )
	{
		Init( psz, nCodePage );
	}
	~CA2WEX() throw()
	{
		AtlConvFreeMemory(m_psz,m_szBuffer,t_nBufferLength);
	}

	 operator LPWSTR() const
	{
		return( m_psz );
	}

private:
	void Init(
		 LPCSTR psz, 
		 UINT nCodePage)
	{
		if (psz == NULL)
		{
			m_psz = NULL;
			return;
		}
		int nLengthA = lstrlenA( psz )+1;
		int nLengthW = nLengthA;

		AtlConvAllocMemory(&m_psz,nLengthW,m_szBuffer,t_nBufferLength);

		BOOL bFailed=(0 == ::MultiByteToWideChar( nCodePage, 0, psz, nLengthA, m_psz, nLengthW ) );
		if (bFailed)
		{
			if (GetLastError()==ERROR_INSUFFICIENT_BUFFER)
			{
				nLengthW = ::MultiByteToWideChar( nCodePage, 0, psz, nLengthA, NULL, 0);
				AtlConvAllocMemory(&m_psz,nLengthW,m_szBuffer,t_nBufferLength);
				bFailed=(0 == ::MultiByteToWideChar( nCodePage, 0, psz, nLengthA, m_psz, nLengthW ) );
			}			
		}

		ASSERT( !bFailed );
// 		if (bFailed)
// 		{
// 			AtlThrowLastWin32();
// 		}	
	}

public:
	LPWSTR m_psz;
	wchar_t m_szBuffer[t_nBufferLength];

private:
	CA2WEX( const CA2WEX&);
	CA2WEX& operator=( const CA2WEX&);
};
typedef CA2WEX<> CA2W;

template< int t_nBufferLength = 128 >
class CW2AEX
{
public:
	CW2AEX( LPCWSTR psz) :
		m_psz( m_szBuffer )
	{
		Init( psz, _AtlGetConversionACP() );
	}
	CW2AEX(
			 LPCWSTR psz, 
			 UINT nCodePage) :
		m_psz( m_szBuffer )
	{
		Init( psz, nCodePage );
	}
	~CW2AEX()
	{		
		AtlConvFreeMemory(m_psz,m_szBuffer,t_nBufferLength);
	}

	 operator LPSTR() const
	{
		return( m_psz );
	}

private:
	void Init(
		 LPCWSTR psz, 
		 UINT nConvertCodePage)
	{
		if (psz == NULL)
		{
			m_psz = NULL;
			return;
		}
		int nLengthW = lstrlenW( psz )+1;		 
		int nLengthA = nLengthW*4;
		
		AtlConvAllocMemory(&m_psz,nLengthA,m_szBuffer,t_nBufferLength);

		BOOL bFailed=(0 == ::WideCharToMultiByte( nConvertCodePage, 0, psz, nLengthW, m_psz, nLengthA, NULL, NULL ));
		if (bFailed)
		{
			if (GetLastError()==ERROR_INSUFFICIENT_BUFFER)
			{
				nLengthA = ::WideCharToMultiByte( nConvertCodePage, 0, psz, nLengthW, NULL, 0, NULL, NULL );
				AtlConvAllocMemory(&m_psz,nLengthA,m_szBuffer,t_nBufferLength);
				bFailed=(0 == ::WideCharToMultiByte( nConvertCodePage, 0, psz, nLengthW, m_psz, nLengthA, NULL, NULL ));
			}			
		}

		ASSERT( !bFailed );
//		if (bFailed)
//		{
//			AtlThrowLastWin32();
//		}
	}

public:
	LPSTR m_psz;
	char m_szBuffer[t_nBufferLength];

private:
	CW2AEX( const CW2AEX&);
	CW2AEX& operator=( const CW2AEX&);
};
typedef CW2AEX<> CW2A;

#ifdef _UNICODE

#define CW2T CW2W
#define CW2TEX CW2WEX
#define CW2CT CW2CW
#define CW2CTEX CW2CWEX
#define CT2W CW2W
#define CT2WEX CW2WEX
#define CT2CW CW2CW
#define CT2CWEX CW2CWEX

#define CA2T CA2W
#define CA2TEX CA2WEX
#define CA2CT CA2W
#define CA2CTEX CA2WEX
#define CT2A CW2A
#define CT2AEX CW2AEX
#define CT2CA CW2A
#define CT2CAEX CW2AEX

#else  // !_UNICODE

#define CW2T CW2A
#define CW2TEX CW2AEX
#define CW2CT CW2A
#define CW2CTEX CW2AEX
#define CT2W CA2W
#define CT2WEX CA2WEX
#define CT2CW CA2W
#define CT2CWEX CA2WEX

#define CA2T CA2A
#define CA2TEX CA2AEX
#define CA2CT CA2CA
#define CA2CTEX CA2CAEX
#define CT2A CA2A
#define CT2AEX CA2AEX
#define CT2CA CA2CA
#define CT2CAEX CA2CAEX

#endif  // !_UNICODE

#define COLE2T CW2T
#define COLE2TEX CW2TEX
#define COLE2CT CW2CT
#define COLE2CTEX CW2CTEX
#define CT2OLE CT2W
#define CT2OLEEX CT2WEX
#define CT2COLE CT2CW
#define CT2COLEEX CT2CWEX
#endif

