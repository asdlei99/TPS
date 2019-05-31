#ifndef __MULTILAN_HEADER_
#define __MULTILAN_HEADER_

#pragma once

#include <vector>
#include <algorithm>
#include <tchar.h>
#include <string.h>
#include <stdlib.h>
#include "kdvtype.h"
#include "unicode.h"

using namespace std;

#define MAX_LAN_NAME_LEN 50
#define INVALID_LANGID 0xFFFF

namespace multilan
{

class CLangInfo
{
public:
	CLangInfo()
	{
		m_bR2LLayout = false;
	}
	bool DoSupportLan( int dwLangID )
	{
		// 遍历看是否支持该语言
		return ( m_vctSuppportLan.end() != find( m_vctSuppportLan.begin(),
										 m_vctSuppportLan.end(),
										 dwLangID ) );
	}

	bool DoCompatibleLan( int dwLangID )
	{
		// 遍历看是否兼容该语言
		return ( m_vctCompatibleLan.end() != find( m_vctCompatibleLan.begin(),
										 m_vctCompatibleLan.end(),
										 dwLangID ) );
	}

	tstring m_strLocalName;
	tstring m_strEnglishName;
	tstring m_strVersion;
	tstring m_strFilePath;
	vector<unsigned short> m_vctSuppportLan;
	vector<unsigned short> m_vctCompatibleLan;
	bool				   m_bR2LLayout;
};

typedef void ( *PFUNC_OUTPUT )( LPCTSTR );

enum emLanError{
emLanErrorSuccess,
emLanErrorInvalidFilePath,
emLanErrorInvalidLangFile,
emLanErrorUnknownLanName,
emLanErrorDoNotSupport,
emLanErrorInvalidLangIdx,
};

class ILanguageManager
{
public:
	/*=============================================================================
	函 数 名： LoadFromPath
	功    能： 从路径加载语言文件
	算法实现： 
	全局变量： 
	参    数： [in] LPCTSTR lpszLanPath		语言文件所在目录
			   [in] LPCTSTR lpszFilter		语言文件过滤器
	返 回 值： u16		错误信息
	备    注： 如c:\下的所有xml文件，lpszLanPath为"C:", lpszFilter为"*.xml"
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2013/03/28  1.0         邹俊龙                  创建
	=============================================================================*/
	virtual u16 LoadFromPath( LPCTSTR lpszLanPath, LPCTSTR lpszFilter ) = 0;

	/*=============================================================================
	函 数 名： GetLangNum
	功    能： 根据语言信息个数
	算法实现： 
	全局变量： 
	参    数：
	返 回 值： u32		语言信息个数
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2013/03/28  1.0         邹俊龙                  创建
	=============================================================================*/
	virtual u32 GetLangNum() const = 0;

	/*=============================================================================
	函 数 名： GetCurLangIndex
	功    能： 获取当前语言的序号
	算法实现： 
	全局变量： 
	参    数：
	返 回 值： u32		当前语言序号
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2013/03/28  1.0         邹俊龙                  创建
	=============================================================================*/
	virtual u32 GetCurLangIndex() const = 0;

	/*=============================================================================
	函 数 名： GetLangInfo
	功    能： 根据语言序号获取语言信息
	算法实现： 
	全局变量： 
	参    数： u32		dwIndex			语言序号
	返 回 值： const TLanInfo*			语言信息指针，不成功为空
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2013/03/28  1.0         邹俊龙                  创建
	=============================================================================*/
	virtual const CLangInfo* GetLangInfo( u32 dwIndex ) const = 0;

	/*=============================================================================
	函 数 名： SetCurLang
	功    能： 根据系统语言ID设置当前语言
	算法实现： 
	全局变量： 
	参    数： [in] u16		wLangID			系统语言ID( GetSystemDefaultLangID 的返回值 )
			   [in] bool	bCompatible		是否启用兼容语言
	返 回 值： bool		是否设置成功
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2013/03/28  1.0         邹俊龙                  创建
	=============================================================================*/
	virtual u16 SetCurLang( u16 wLangId, bool bCompatible ) = 0;

	/*=============================================================================
	函 数 名： SetCurLan
	功    能： 根据语言名称设置当前语言
	算法实现： 
	全局变量： 
	参    数： [in] LPCTSTR		lpszLanName		语言名称
	返 回 值： u16	错误信息
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2013/03/28  1.0         邹俊龙                  创建
	=============================================================================*/
	virtual u16 SetCurLang( LPCTSTR lpszLanName ) = 0;

	/*=============================================================================
	函 数 名： SetCurLang
	功    能： 根据语言序号设置当前语言
	算法实现： 
	全局变量： 
	参    数： [in]u32	dwIndex			语言序号
	返 回 值： bool		bCompatible		是否设置成功
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2013/03/28  1.0         邹俊龙                  创建
	=============================================================================*/
	virtual u16 SetCurLang( u32 dwIndex ) = 0;

	/*=============================================================================
	函 数 名： GetCurLangInfo
	功    能： 获取当前语言信息
	算法实现： 
	全局变量： 
	参    数：
	返 回 值： const TLanInfo*		当前语言信息
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2013/03/28  1.0         邹俊龙                  创建
	=============================================================================*/
	virtual const CLangInfo* GetCurLangInfo() const = 0;

	/*=============================================================================
	函 数 名： GetString
	功    能： 通过字符串ID获取字符串，若未找到，返回默认值
	算法实现： 
	全局变量： 
	参    数： [in] LPCTSTR lpszStringId		字符串ID
			   [in] LPCTSTR lpszDefault		找不到的默认结果
	返 回 值： LPCTSTR					对应的字符串
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2013/03/28  1.0         邹俊龙                  创建
	=============================================================================*/
	virtual LPCTSTR GetString( LPCTSTR lpszStringId, LPCTSTR lpszDefault = _T("") ) const = 0;

	/*=============================================================================
	函 数 名： SetOutputFunc
	功    能： 设置打印函数指针
	算法实现： 
	全局变量： 
	参    数： PFUNC_OUTPUT				打印函数的指针
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2013/04/28  1.0         邹俊龙                  创建
	=============================================================================*/
	virtual void SetOutputFunc( PFUNC_OUTPUT pfunOutput ) = 0;

	/*=============================================================================
	函 数 名： Clear
	功    能： 清空
	算法实现： 
	全局变量： 
	参    数：
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2013/06/27  1.0         邹俊龙                  创建
	=============================================================================*/
	virtual void Clear() = 0;

};

}

#endif
