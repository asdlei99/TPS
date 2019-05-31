/*****************************************************************************
模块名      : CUmcwebCommon
文件名      : umcwebcommon.h
相关文件    : 
文件实现功能: 提供公共函数封装
作者        : 徐华秀
版本        : V1.0  Copyright(C) 2014-2015 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2015/01/06     1.0         徐华秀      创建
******************************************************************************/
#ifndef UMCWEBCOMMON_H 
#define UMCWEBCOMMON_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmcwebCommon  
{
public:
	CUmcwebCommon();
	virtual ~CUmcwebCommon();

	//主视频格式(TUmsVidFormat) - 格式名称(std::string) 转换
	static void ChangeMainVideoToName( const TUmsVidFormat& tTpMainVideoRes, std::string& strFormatName );

	//辅视频格式(TUmsVidFormat) - 格式名称(std::string) 转换
	static void ChangeMinorVideoToName( const TUmsVidFormat& tTpMinorVideoRes, std::string& strFormatName );

	//音频格式(EmTpAudioFormat) - 格式名称(std::string) 转换
	static void ChangeAudioFormatToName( const EmTpAudioFormat emTpAudioFormat, std::string& strFormatName );

	//string - time_t 转换(字符串格式： 2014 - 12 - 10  08 : 56)
	static void ChangeStringToTime( const std::string& strTime, time_t& timeData );
	static void ChangeTimeToString( const time_t& timeData, std::string& strTime );
};

#endif