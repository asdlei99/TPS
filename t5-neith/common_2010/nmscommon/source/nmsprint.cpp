/***********************************************************************************************************
*											公用打印模块
*  目的: 主要为了管理Osp打印、
*  用法: 通过在EmPrintRegUserName里面添加注册用户ID，在程序开始之处调用reguser来注册
*  第一步 CNmsPrint::RegUser(NMSPRINT_ID_MuXingmao, "muxingmao") 
*  第二步 CNmsPrint::Print() 参数第一个填ID，后面的跟OspPrintf类似
************************************************************************************************************/
#include "StdAfx.h"
#include "nmsprint.h"
#include <time.h>

map< string, PTRegUserInfo > CNmsPrint::m_mapUserS; 
char* CNmsPrint::strNmsDefaultScrip = "NMS";
/*---------------------------------------------------------------------
* 函 数 名：RegUserS
* 功    能：以字符串作为key
* 参数说明：s8* pKey						[in]	键值
			s8* pUserName					[in]	描述
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/12/16	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
BOOL32 CNmsPrint::RegUser( s8* pKey , s8* pUserName )
{
	map< string, PTRegUserInfo >::iterator begin = m_mapUserS.find( pKey );
	if ( begin == m_mapUserS.end() )
	{
		PTRegUserInfo ptRegUserInfo = new TRegUserInfo;
		strcpy( ptRegUserInfo->achName, pUserName );
		ptRegUserInfo->bLogOpen = FALSE;
		m_mapUserS.insert( map< string, PTRegUserInfo >::value_type( pKey, ptRegUserInfo) );
		return TRUE;
	}
	else
	{
		PTRegUserInfo ptRegUserInfo = begin->second;
		strcpy( ptRegUserInfo->achName, pUserName );
	}
	return FALSE;
}

/*---------------------------------------------------------------------
* 函 数 名：OpenLog 
* 功    能：打开开关 通过你所记住的ID，如果不记得，可以先调用showalluser
* 参数说明：[in] dwUserID 唯一标识ID
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/13	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
BOOL32 CNmsPrint::OpenLog( u32 dwIndex )
{
	PTRegUserInfo pUserInfo = GetRegUserInfo( dwIndex );
	if ( pUserInfo != NULL )
	{
		pUserInfo->bLogOpen = TRUE;
		OspPrintf( 1, 0, "用户 %s 开关已经打开!\n", pUserInfo->achName );
		return TRUE;
	}
	OspPrintf( 1, 0, "没有此用户 ,可通过showalluser查看所有用户\n" );
	return FALSE;	
}

/*---------------------------------------------------------------------
* 函 数 名：OpenLog
* 功    能：通过用户名打开开关
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/13	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
BOOL32 CNmsPrint::OpenLog( s8* pUser )
{
	PTRegUserInfo pUserInfo = GetRegUserInfo( pUser );
	if ( pUserInfo != NULL )
	{
		pUserInfo->bLogOpen = TRUE;
		OspPrintf( 1, 0, "用户 %s 开关已经打开!\n", pUserInfo->achName );
		return TRUE;
	}
	OspPrintf( 1, 0, "没有此用户 ,可通过showalluser查看所有用户\n" );
	return FALSE;	
}

/*---------------------------------------------------------------------
* 函 数 名：CloseLog
* 功    能：关闭开关
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/13	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
BOOL32 CNmsPrint::CloseLog( u32 dwIndex )
{
	PTRegUserInfo pUserInfo = GetRegUserInfo( dwIndex );
	if ( pUserInfo != NULL )
	{
		pUserInfo->bLogOpen = FALSE;
		OspPrintf( 1, 0, "用户 %s 开关已经关闭!\n", pUserInfo->achName );
		return TRUE;
	}
	OspPrintf( 1, 0, "没有此用户 ,可通过showalluser查看所有用户\n" );
	return FALSE;
}

/*---------------------------------------------------------------------
* 函 数 名：CloseLog
* 功    能：关闭开关
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/13	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
BOOL32 CNmsPrint::CloseLog( s8* pUser )
{
	PTRegUserInfo pUserInfo = GetRegUserInfo( pUser );
	if ( pUserInfo != NULL )
	{
		pUserInfo->bLogOpen = FALSE;
		OspPrintf( 1, 0, "用户 %s 开关已经关闭!\n", pUserInfo->achName );
		return TRUE;
	}
	OspPrintf( 1, 0, "没有此用户 ,可通过showalluser查看所有用户\n" );
	return FALSE;
}

/*---------------------------------------------------------------------
* 函 数 名：IsLogOpen
* 功    能：开关是否打开
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/13	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
BOOL32 CNmsPrint::IsLogOpen( s8* pUserName )
{
	PTRegUserInfo pUserInfo = GetRegUserInfo( pUserName );
	if ( pUserInfo != NULL )
	{
		return pUserInfo->bLogOpen;
	}
	return FALSE;
}

/*---------------------------------------------------------------------
* 函 数 名：IsLogOpen
* 功    能：开关是否打开
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/13	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
BOOL32 CNmsPrint::IsLogOpen( u32 dwUserId )
{
	PTRegUserInfo pUserInfo = GetRegUserInfo( dwUserId );
	if ( pUserInfo != NULL )
	{
		return pUserInfo->bLogOpen;
	}
	return FALSE;
}

/*---------------------------------------------------------------------
* 函 数 名：GetRegUserInfo
* 功    能：获得注册用户信息
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/13	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
PTRegUserInfo CNmsPrint::GetRegUserInfo( u32 dwIndex )
{
	u32 dwCount = m_mapUserS.size();
	u32 dwTemp = 0;
	if ( dwCount > dwIndex )
	{
		map< string, PTRegUserInfo >::iterator begin = m_mapUserS.begin();
		while ( begin != m_mapUserS.end() )
		{
			if ( dwTemp == dwIndex )
			{
				return begin->second;
			}	
			dwTemp++;
			begin++;
		}
	}
	return NULL;
}

/*---------------------------------------------------------------------
* 函 数 名：GetRegUserInfo
* 功    能：获得注册用户信息
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/13	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
PTRegUserInfo CNmsPrint::GetRegUserInfo( s8* pUser )
{
	map< string, PTRegUserInfo >::iterator begin = m_mapUserS.find( pUser );
	if ( begin != m_mapUserS.end() )
	{
		return begin->second;
	}
	return NULL;
}

BOOL32 CNmsPrint::Printf( s8* pUser, const s8* pScrip , ... )
{   
	PTRegUserInfo ptRegUserInfo = GetRegUserInfo( pUser );
	// 没有找到注册的话，如果第一次进入这个函数，会默认注册，这样以后可以通过showalluser来看一下自己以前写的调试代码
	if ( ptRegUserInfo == NULL )
	{
		CNmsPrint::RegUser( pUser, pUser );
		return FALSE;
	}
	if ( ptRegUserInfo->bLogOpen == FALSE )
	{
		return FALSE;
	}

	s8 result[1024];

	va_list arg;
	va_start( arg, pScrip ); // 获取参数列表
	_vsnprintf( result, sizeof(result), pScrip, arg );
	va_end( arg ); // 结束
	
	time_t _t = time(NULL);
	
	struct tm* _tmp = localtime(&_t);
	
	OspPrintf( 1, 0, "[ %02d:%02d:%02d ] [%s] %s\n", _tmp->tm_hour, _tmp->tm_min, _tmp->tm_sec, ptRegUserInfo->achName, result );
	
	return TRUE;
}

// 关闭开关
API void closelog( s8* pUser )
{
	try
	{
		CNmsPrint::CloseLog( pUser );
	}
	catch ( ... )
	{
		try
		{
			s64* pData = (s64*)&pUser;
			CNmsPrint::CloseLog( *pData );
		}
		catch (...)
		{
			OspPrintf( 1, 0, "[system] operate error\n");
		}		
	}
}

API void openalllog()
{
	map< string, PTRegUserInfo >::iterator begin2 = CNmsPrint::m_mapUserS.begin();
	while ( begin2 != CNmsPrint::m_mapUserS.end() )
	{
		PTRegUserInfo ptRegUserInfo = begin2->second;
		ptRegUserInfo->bLogOpen = TRUE;		
		begin2++;
	}

	OspPrintf( 1, 0, "[NmsPrint]  所有开关已经打开!\n" );
}

API void closealllog()
{
	map< string, PTRegUserInfo >::iterator begin2 = CNmsPrint::m_mapUserS.begin();
	while ( begin2 != CNmsPrint::m_mapUserS.end() )
	{
		PTRegUserInfo ptRegUserInfo = begin2->second;
		ptRegUserInfo->bLogOpen = FALSE;		
		begin2++;
	}
	OspPrintf( 1, 0, "[NmsPrint]  所有开关已经关闭!\n" );
}

// 打开开关
API void openlog( s8* pUser )
{
	try
	{
		CNmsPrint::OpenLog( pUser );
	}
	catch ( ... )
	{
		try
		{
			s32* pData = (s32*)&pUser;		
			CNmsPrint::OpenLog( *pData );
		}
		catch (...)
		{
			OspPrintf( 1, 0, "[system] operate error\n");
		}		
	}
}

API void reguser( s8* pUser, s8* pInfo )
{
	try
	{
		CNmsPrint::RegUser( pUser, pInfo );
	}
	catch ( ... )
	{
		try
		{
			s32* pData = (s32*)&pUser;
			char buf[20] = {0};
			_itoa( *pData, buf, sizeof(buf) );
			CNmsPrint::RegUser( buf, pInfo );
		}
		catch (...)
		{
			OspPrintf( 1, 0, "[system] operate error\n");
		}		
	}
}

API void nmsprinthelp()
{
	OspPrintf( 1, 0, "===============================公用打印接口===============================\n");
	OspPrintf( 1, 0, "* 函数: showalluser()      查看所有注册用户\n");
	OspPrintf( 1, 0, "* 函数: openlog( s8* )	 打开开关\n");
	OspPrintf( 1, 0, "* 函数: reguser(s8*,s8*)   注册用户\n");
	OspPrintf( 1, 0, "* 函数: closelog( s8* )	 通过ID关闭开关\n");
	OspPrintf( 1, 0, "===========================================================================");
}

// 显示所有注册用户
API void showalluser()
{
	OspPrintf( 1, 0 ,"[NmsPrint] 当前用户数量: %d \n", CNmsPrint::m_mapUserS.size() );
	map< string, PTRegUserInfo >::iterator begin1 = CNmsPrint::m_mapUserS.begin();
	s32 nIndex = 0;
	while ( begin1 != CNmsPrint::m_mapUserS.end() )
	{
		PTRegUserInfo ptRegUserInfo = begin1->second;
		string str = begin1->first;
		OspPrintf( 1, 0, "[NmsPrint] [%d] ID= %s Desc= %s LogOption= %s \n", nIndex++, str.c_str(), ptRegUserInfo->achName, ptRegUserInfo->bLogOpen ? "open" : "close" );
		begin1++;
	}
}