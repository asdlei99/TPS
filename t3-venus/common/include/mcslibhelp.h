/*=============================================================================
模   块   名: 会议控制台业务功能库
文   件   名: mcslibhelp.h
相 关  文 件: mcslibhelp.cpp
文件实现功能: mcslib帮助命令打印
作        者: 王昊
版        本: V4.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2005/08/09  4.0     王昊        创建
=============================================================================*/

#ifndef _MCSLIBHELP_20050809_H_
#define _MCSLIBHELP_20050809_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "osp.h"

/*=============================================================================
函 数 名:mcslibhelp
功    能:打印帮助命令
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void mcslibhelp(void);

/*=============================================================================
函 数 名:mcslibver
功    能:打印版本、编译时间和依赖库的版本和编译时间
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void mcslibver(void);

/*=============================================================================
函 数 名:pmsgctrl
功    能:消息打印控制
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void pmsgctrl(void);

/*=============================================================================
函 数 名:plistcmd
功    能:打印即时本地消息
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void plistcmd(void);

/*=============================================================================
函 数 名:setipport
功    能:设置端口号
参    数:s32 wPort                          [in]    测试端口号
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void setipport(s32 wPort);

/*=============================================================================
函 数 名:pipport
功    能:打印端口号
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void pipport(void);

/*=============================================================================
函 数 名:settelnetuser
功    能:设置telnet密码
参    数:LPSTR lptrUser                 [in]    用户名
         LPSTR lptrPwd                  [in]    密码
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/12/18  4.0     王昊    创建
=============================================================================*/
API void settelnetuser(LPSTR lptrUser, LPSTR lptrPwd);

/*=============================================================================
函 数 名:pallmsg
功    能:打印所有会议控制台相关消息
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void pallmsg(void);

/*=============================================================================
函 数 名:npallmsg
功    能:关闭打印所有会议控制台相关消息
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void npallmsg(void);

/*=============================================================================
函 数 名:pconfmsg
功    能:打印会议相关的消息
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void pconfmsg(void);

/*=============================================================================
函 数 名:npconfmsg
功    能:关闭打印会议相关的消息
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void npconfmsg(void);

/*=============================================================================
函 数 名:pmtmsg
功    能:打印终端操作相关消息
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void pmtmsg(void);

/*=============================================================================
函 数 名:npmtmsg
功    能:关闭打印终端操作相关消息
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void npmtmsg(void);

/*=============================================================================
函 数 名:pmcumsg
功    能:打印连接MCU及相关消息
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void pmcumsg(void);

/*=============================================================================
函 数 名:npmcumsg
功    能:关闭打印连接MCU及相关消息
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void npmcumsg(void);

/*=============================================================================
函 数 名:pperimsg
功    能:打印外设相关消息
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void pperimsg(void);

/*=============================================================================
函 数 名:npperimsg
功    能:关闭打印外设相关消息
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void npperimsg(void);

/*=============================================================================
函 数 名:paddrmsg
功    能:打印地址簿相关消息
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void paddrmsg(void);

/*=============================================================================
函 数 名:npaddrmsg
功    能:关闭打印地址簿相关消息
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void npaddrmsg(void);

/*=============================================================================
函 数 名:pusermsg
功    能:打印用户相关消息
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void pusermsg(void);

/*=============================================================================
函 数 名:npusermsg
功    能:关闭打印用户相关消息
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void npusermsg(void);

/*=============================================================================
函 数 名:ptestmsg
功    能:打印集成测试相关消息
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/10  4.0     王昊    创建
=============================================================================*/
API void ptestmsg(void);

/*=============================================================================
函 数 名:ptestmsg
功    能:关闭打印集成测试相关消息
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/10  4.0     王昊    创建
=============================================================================*/
API void nptestmsg(void);

/*=============================================================================
函 数 名:listallsession
功    能:列出当前所有连接
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void listallsession();

/*=============================================================================
函 数 名:listsession
功    能:列出连接会话的状态
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/03/02  4.0     顾振华  支持参数
=============================================================================*/
API void listsession(s32 nSessionIdx = INDEX_ERR);


/*=============================================================================
函 数 名:listallconf
功    能:列出所有的即时会议
参    数:s32 nSessionIdx                [in]    连接索引号
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void listallconf(s32 nSessionIdx = INDEX_ERR);

/*=============================================================================
函 数 名:listconfinfo
功    能:列出即时会议的信息
参    数:s32 nConfIdx                   [in]    会议索引号
         s32 nSessionIdx                [in]    连接索引号
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void listconfinfo(s32 nConfIdx = INDEX_ERR, s32 nSessionIdx = INDEX_ERR);

/*=============================================================================
函 数 名:listmcutable
功    能:列出会议所有MCU及其终端列表
参    数:s32 nConfIdx                   [in]    会议索引号
         s32 nSessionIdx                [in]    连接索引号
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void listmcutable(s32 nConfIdx = INDEX_ERR, s32 nSessionIdx = INDEX_ERR);

/*=============================================================================
函 数 名:listconfallmtinfo
功    能:列出TConfAllMtInfo
参    数:s32 nConfIdx                   [in]    会议索引号
         s32 nSessionIdx                [in]    连接索引号
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void listconfallmtinfo( s32 nConfIdx = INDEX_ERR,
                            s32 nSessionIdx = INDEX_ERR );

/*=============================================================================
函 数 名:listmtlist
功    能:列出单级MCU终端列表
参    数:s32 nMcuIndex                  [in]    Mcu Id
         s32 nConfIdx                   [in]    会议索引号
         s32 nSessionIdx                [in]    连接索引号
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void listmtlist( s32 nMcuIndex = INDEX_ERR, s32 nConfIdx = INDEX_ERR,
                     s32 nSessionIdx = INDEX_ERR );

/*=============================================================================
函 数 名:listmtinfo
功    能:列出终端的完整信息
参    数:s32 nMtIndex                   [in]    Mt Id
         s32 nMcuIndex                  [in]    Mcu Id
         s32 nConfIdx                   [in]    会议索引号
         s32 nSessionIdx                [in]    连接索引号
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void listmtinfo( s32 nMtIndex = INDEX_ERR, s32 nMcuIndex = INDEX_ERR,
                     s32 nConfIdx = INDEX_ERR, s32 nSessionIdx = INDEX_ERR );

/*=============================================================================
函 数 名:listallmonitor
功    能:列出所有监控通道
参    数:s32 nSessionIdx                [in]    连接索引号
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/25  4.0     王昊    创建
=============================================================================*/
API void listallmonitor( s32 nSessionIdx = INDEX_ERR );

/*=============================================================================
函 数 名:listmonitor
功    能:列出指定监控通道
参    数:s32 nChannelIdx                [in]    指定通道
         s32 nSessionIdx                [in]    连接索引号
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/25  4.0     王昊    创建
=============================================================================*/
API void listmonitor( s32 nChannelIdx = INDEX_ERR,
                      s32 nSessionIdx = INDEX_ERR );

/*=============================================================================
函 数 名:listperi
功    能:列出所有外设
参    数:s32 nSessionIdx                [in]    连接索引号
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void listperi( s32 nSessionIdx = INDEX_ERR );

/*=============================================================================
函 数 名:listperiinfo
功    能:列出外设信息
参    数:s32 nEqpId                     [in]    外设Id
         s32 nSessionIdx                [in]    连接索引号
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void listperiinfo( s32 nEqpId, s32 nSessionIdx = INDEX_ERR );

/*=============================================================================
函 数 名:mcsprtaddrbook
功    能:列出地址簿信息
参    数:s32 nSessionIdx                [in]    连接索引号
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void mcsprtaddrbook( s32 nSessionIdx = INDEX_ERR );

/*=============================================================================
函 数 名:listalluser
功    能:列出用户信息
参    数:s32 nSessionIdx                [in]    连接索引号
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/09  4.0     王昊    创建
=============================================================================*/
API void listalluser( s32 nSessionIdx = INDEX_ERR );

/*=============================================================================
函 数 名:listmcu
功    能:列出指定MCU
参    数:s32 nSessionIdx                [in]    连接索引号
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/09/01  4.0     王昊    创建
=============================================================================*/
API void listmcu(s32 nSessionIdx = INDEX_ERR);

/*=============================================================================
函 数 名:listscheduleconf
功    能:列出所有预约会议
参    数:s32 nSessionIdx                [in]    连接索引号
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/11/23  4.0     王昊    创建
=============================================================================*/
API void listscheduleconf(s32 nSessionIdx = INDEX_ERR);

/*=============================================================================
函 数 名:listconftemplate
功    能:列出所有会议模板
参    数:s32 nSessionIdx                [in]    连接索引号
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/11/23  4.0     王昊    创建
=============================================================================*/
API void listconftemplate(s32 nSessionIdx = INDEX_ERR);

/*=============================================================================
函 数 名:pmsgbody
功    能:打印所有消息体
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/07/26  4.0     王昊    创建
=============================================================================*/
API void pmsgbody(void);

/*=============================================================================
函 数 名:npmsgbody
功    能:停止打印所有消息体
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/07/26  4.0     王昊    创建
=============================================================================*/
API void npmsgbody(void);

/*=============================================================================
函 数 名:pmcsmsgbody
功    能:打印MCS向MCU发送消息体
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/07/26  4.0     王昊    创建
=============================================================================*/
API void pmcsmsgbody(void);

/*=============================================================================
函 数 名:npmcsmsgbody
功    能:停止打印MCS向MCU发送消息体
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/07/26  4.0     王昊    创建
=============================================================================*/
API void npmcsmsgbody(void);

/*=============================================================================
函 数 名:pmcumsgbody
功    能:打印MCU向MCS发送消息体
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/07/26  4.0     王昊    创建
=============================================================================*/
API void pmcumsgbody(void);

/*=============================================================================
函 数 名:pnmcumsgbody
功    能:停止打印MCU向MCS发送消息体
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/07/26  4.0     王昊    创建
=============================================================================*/
API void pnmcumsgbody(void);

/*=============================================================================
函 数 名:listallboard
功    能:列出所有单板信息
参    数:s32 nSessionIdx                [in]    连接索引号
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/08/21  4.0     王昊    创建
=============================================================================*/
API void listallboard(s32 nSessionIdx = INDEX_ERR);

#endif  //  _MCSLIBHELP_20050809_H_