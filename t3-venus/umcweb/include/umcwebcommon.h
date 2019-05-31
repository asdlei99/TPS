/*****************************************************************************
模块名      : CUmcwebCommon工具类
文件名      : umcwebcommon.h
相关文件    : 
文件实现功能: 提供公共函数封装
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/5/24      1.0         刘德印      创建
******************************************************************************/
#ifndef UMSWEBCOMMON_H 
#define UMSWEBCOMMON_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"
class CUmcwebCommon  
{
public:
	CUmcwebCommon();
	virtual ~CUmcwebCommon();

	/*=============================================================================
    函 数 名:MapValueCompare
    功    能:仿函数：判断map中是否存在和value相等的值
    参    数: std::pair<u16,CString> paD                           [in]    待比较pair数据源
	参    数: CString strTarget                                    [in]    比较文本
    注    意:无
    返 回 值:bool
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2012/06/20  1.0     刘德印    创建
    =============================================================================*/
	static bool MapValueCompare( std::pair<u16,CString> paData, CString strTarget);

	/*=============================================================================
    函 数 名:SetImgForTransEdit
    功    能:提供公共设置编辑框CTransparentEdit图片接口
    参    数:CTransparentEdit *pEdit                          [in]    待设置图片控件
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/18  1.0     刘德印    创建
    =============================================================================*/
	static void SetImgForTransEdit( CTransparentEdit *pEdit, BOOL bSetDisableImg = TRUE );


	/*=============================================================================
    函 数 名:SetImgForTransEditTimeL
    功    能:提供公共设置时间编辑框 分左侧 中间 和右侧的edit
    参    数:CTransparentEdit *pEdit                          [in]    待设置图片控件
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/09/12  1.0     俞锦锦    创建
    =============================================================================*/
    static void SetImgForTransEditTimeLft( CTransparentEdit *pEdit, BOOL bSetDisableImg = TRUE );
	static void SetImgForTransEditTimeMdl( CTransparentEdit *pEdit, BOOL bSetDisableImg = TRUE );
	static void SetImgForTransEditTimeRgt( CTransparentEdit *pEdit, BOOL bSetDisableImg = TRUE );


	/*=============================================================================
    函 数 名:SetImgForTransEdit
    功    能:提供公共设置查询编辑框CTransparentEdit图片接口
    参    数:CTransparentEdit *pEdit                          [in]    待设置图片控件
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/18  1.0     刘德印    创建
    =============================================================================*/
	static void SetImgForTransSearchEdit( CTransparentEdit *pEdit, BOOL bIsSearchEdit = TRUE, s32 nFontSize = 11, const CString& strText = "请输入字符或数字", s32 nLimitLen = 31 );

	/*=============================================================================
    函 数 名:SetImgForTransIpEdit
    功    能:提供公共设置CTransparentIpEdit图片接口
    参    数:CTransparentIpEdit *pEdit                          [in]    待设置图片控件
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/18  1.0     刘德印    创建
    =============================================================================*/
	static void SetImgForTransIpEdit( CTransparentIpEdit *pIpEdit );

	/*=============================================================================
    函 数 名:SetImgForLetter
    功    能:提供公共设置CLetterIndex图片接口
    参    数:CLetterIndex* pLetterIndexTmp                          [in]    待设置字母检索控件
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/18  1.0     刘德印    创建
    =============================================================================*/
	static void SetImgForLetter( CLetterIndex* pLetterIndexTmp );

	/*=============================================================================
    函 数 名:SetTextTransStatic
    功    能:提供统一设置Static文本格式等Style接口
    参    数:CTransparentStatic *pStatic                          [in]    待设置Staic控件
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/18  1.0     刘德印    创建
    =============================================================================*/
	static void SetTextTransStatic( CTransparentStatic *pStatic, const CString& strText = "", s32 nFontSize = 13, Color color = Color( 46, 55, 76 ) );
	

	/*=============================================================================
    函 数 名:SetTextTransCheckBtn
    功    能:提供统一设置Static文本格式等Style接口
    参    数:CTransparentCheckButton *pStatic                          [in]    待设置CheckBtn控件
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2013/02/26  1.0     刘德印    创建
    =============================================================================*/
	static void SetTextTransCheckBtn( CTransparentCheckButton *pCheckBtn, const CString& strText = "", s32 nFontSize = 13, Color color = Color( 46, 55, 76 ) );
	
	/*=============================================================================
    函 数 名:SetTextTransRadioBtn
    功    能:提供统一设置Static文本格式等Style接口
    参    数:CTransparentCheckButton *pStatic                          [in]    待设置CheckBtn控件
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2014/02/14  1.0     石城    创建
    =============================================================================*/
	static void SetTextTransRadioBtn( CTransparentCheckButton *pCheckBtn, const CString& strText = "", s32 nFontSize = 13, Color color = Color( 46, 55, 76 ) );


	/*=============================================================================
    函 数 名:GetUniqID
    功    能:获取公共唯一ID
    参    数:无
    注    意:无
    返 回 值:unsigned int
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/16  1.0     刘德印    创建
    =============================================================================*/
	static unsigned int GetUniqID();

	/*=============================================================================
    函 数 名:IsValidTPStr
    功    能:" ;/?:@&=+$,%^"等特殊字符包含判断
    参    数: const CString& strText                          [in]    待查找文本
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2012/05/15  1.0     刘德印    创建
    =============================================================================*/
	static bool IsValidTPStr( const CString& strText = "" );

	/*=============================================================================
    函 数 名:IsAllNumber
    功    能:判断字串全部为数字
    参    数: const CString& strText                          [in]    待查找文本
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2012/05/18  1.0     刘德印    创建
    =============================================================================*/
	static bool IsAllNumber( const CString& strText = "" );
	static bool IsAllE164Number( const CString& strText = "" );

	/*=============================================================================
    函 数 名:HZPYMatchList
    功    能:查询所有输入框中匹配的数据在列表中
    参    数: const CString& strTextInput                          [in]    输入框内容文本
	参    数: const CString& strTextSrc                            [in]    待查找文本
    注    意:无
    返 回 值:BOOL
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2012/05/18  1.0     刘德印    创建
    =============================================================================*/
	static BOOL HZPYMatchList( const CString& strTextInput,  const CString& strTextSrc );

	/*=============================================================================
    函 数 名:PlusHourBtn SubHourBtn PlusMinBtn SubMinBtn PlusSecBtn SubSecBtn
    功    能:设置点击时间加减的公共处理函数
    参    数: CTransparentEdit *pEdit                          [in]    输入框控件指针
    注    意:无
    返 回 值:BOOL
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2012/05/18  1.0     刘德印    创建
    =============================================================================*/
	static void PlusHourBtn( CTransparentEdit *pEdit ); 
	static void SubHourBtn( CTransparentEdit *pEdit ); 
	static void PlusMinBtn( CTransparentEdit *pEdit ); 
	static void SubMinBtn( CTransparentEdit *pEdit ); 
	static void PlusSecBtn( CTransparentEdit *pEdit ); 
	static void SubSecBtn( CTransparentEdit *pEdit ); 

	static void GetResolutionScale( float &fx, float &fy);
	static void ResolutionAdp( long &nx, long &ny);
	static void FontSizeAdp( int &nFontSize );
	static void ResetChildWndSize( HWND hParentWnd );

	/*=============================================================================
    函 数 名:TimeToTm
    功    能:转换time_t时间为tm结构
    参    数: struct tm& tmDate                          [in]    time_t待转化时间
	参    数: const time_t& timeDate                     [in]    转换后的tm时间
    注    意:无
    返 回 值:BOOL
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2012/08/09  1.0     刘德印    创建
    =============================================================================*/
	static void TimeToTm( struct tm& tmDate, const time_t& timeDate );

	/*=============================================================================
    函 数 名:GetTime
    功    能:将dwTime转为nHour, nMin, nSec
    参    数: u32 dwTime								 [in]    待转换的时间
	参    数: int& nHour			                     [out]   转换后的小时
	参    数: int& nMin				                     [out]   转换后的分钟
	参    数: int& nSec				                     [out]   转换后的秒
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    20132/05/23  1.0     石城    创建
    =============================================================================*/
	static void GetTime( u32 dwTime, int& nHour, int& nMin, int& nSec );

};

#endif
