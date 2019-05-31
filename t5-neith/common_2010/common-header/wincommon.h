/*************************************************************************
模块名      ：wincommon
文件名      ：wincommon.h
相关文件    ：
文件实现功能：一些windows通用宏定义
			请在包含window相关头文件前包含
作者        ：邹俊龙
版本        ：V4.0 Copyright(C) 2003-2005 KDC, All rights reserved.
--------------------------------------------------------------------------
修改记录：
日期			 版本    修改人    修改内容
2013.04.10   4.7     邹俊龙     创建
**************************************************************************/

#pragma once

// 禁止显示安全提示
#ifndef _CRT_SECURE_NO_DEPRECATE
	#define _CRT_SECURE_NO_DEPRECATE
#endif

// 自动将不安全的字符串函数替换为_s版本
#ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
	#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#endif

// 使用MS旧版本的SWPRINTF，兼容6.0
#ifndef _CRT_NON_CONFORMING_SWPRINTFS
	#define _CRT_NON_CONFORMING_SWPRINTFS 1
#endif

// 定义支持的最低的windows版本
// VC 6.0 下若设置_WIN32_WINNT 0x501，会导致CFileDialog析构时崩溃
// 该问题在VC 7.1中修复，因此之前版本都_WIN32_WINNT 都应低于0x501
// 详见：http://social.msdn.microsoft.com/forums/en-US/vcgeneral/thread/55664186-aae7-4ae9-a3e9-e38659335df6/
#ifndef _WIN32_WINNT
	#if( _MSC_VER <= 1300 )
		#define	_WIN32_WINNT 0x400
	#else
		#define _WIN32_WINNT 0x501
	#endif
#endif

// MS VC++ 10.0 _MSC_VER = 1600
// MS VC++ 9.0 _MSC_VER = 1500
// MS VC++ 8.0 _MSC_VER = 1400
// MS VC++ 7.1 _MSC_VER = 1310
// MS VC++ 7.0 _MSC_VER = 1300
// MS VC++ 6.0 _MSC_VER = 1200
// MS VC++ 5.0 _MSC_VER = 1100

// Minimum system required		_WIN32_WINNT
// Windows Server 2008			>=0x0600
// Windows Vista				>=0x0600
// Windows Server 2003			>=0x0502
// Windows XP                   >=0x0501
// Windows 2000                 >=0x0500
// Windows NT 4.0               >=0x0400
// Windows Me                   >=0x0500
// Windows 98                   >=0x0410
// Windows 95                   >=0x0400

//	删除单个指针
#ifndef DEL_PTR
	#define DEL_PTR(p)              if (p != NULL) { delete p; p = NULL; }
#endif

//	删除数组指针
#ifndef DEL_PTR_ARRAY
	#define DEL_PTR_ARRAY(p)        if (p != NULL) { delete [] p; p = NULL; }
#endif
