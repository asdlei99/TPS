#ifndef _NETCBB_DHCPS_H_
#define _NETCBB_DHCPS_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include "netcbb_def.h"

/* DHCP-Server 回调函数的消息码基址 */
#define NETCBB_DHCPS_MSG_BASE          (u32)80000

/* dhcp 服务器的DNS配置信息 */
typedef struct{
	u32 dwDnsNum;
    TNetcbbAddr tDnsIp[NETCBB_MAX_DNS_SERVER];
}TNetcbbDnsInfo;

/* dhcp 服务器的网卡结构体定义 */
typedef struct{
	TNetcbbAddr tIpPoolStart;   /* 网络序 : dhcp-server分配的起始地址 */
	TNetcbbAddr tIpPoolEnd;     /* 网络序 : dhcp-server分配的终止地址 */
	u32 dwIpPoolPrefix;         /* 网络序 : dhcp-server分配的地址前缀 */
	TNetcbbAddr tRoutes;        /* 网络序 : dhcp-server分配的网关地址 */
	TNetcbbAddr tIfaceIp;       /* 网络序 : 网卡地址 */
	u32 dwIfacePrefix;          /* 网络序 : 子网掩码 */
	TNetcbbDnsInfo tDnsServerInfo;
}TNetcbbDhcpsInfo;

typedef struct
{
	u32 dwDhcpsIsRun;         /* 0:停止; 1: 运行 */
}TNetcbbDhcpsState;

/************************************************************
 * 函数名 : NetcbbDhcpsStart
 *
 * 功能 : 开启DHCP-Server功能
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      pchIfaceName    - 网卡名字(支持"ethX", "wlanX", "bondX",
 *                        "pppX"名字，X为0,1,2...)
 *      wSinFamily      - 协议栈类型 :  NETCBB_PROTO_TYPE_IPV4
 *                                      NETCBB_PROTO_TYPE_IPV6
 *      ptDhcpsConfInfo - dhcp-server的配置信息
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 失败\
 *          其他错误见netcbb_def.h
 ***********************************************************/
s32 NetcbbDhcpsStart(char *pchIfaceName, u16 wSinFamily, TNetcbbDhcpsInfo* ptDhcpsConfInfo);

/************************************************************
 * 函数名 : NetcbbDhcpsStop
 *
 * 功能 : 关闭DHCP-Server功能
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      pchIfaceName    - 网卡名字(支持"ethX", "wlanX", "bondX",
 *                        "pppX"名字，X为0,1,2...)
 *      wSinFamily      - 协议栈类型 :  NETCBB_PROTO_TYPE_IPV4
 *                                      NETCBB_PROTO_TYPE_IPV6
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 失败
 *          其他错误见netcbb_def.h
 ***********************************************************/
s32 NetcbbDhcpsStop(char *pchIfaceName, u16 wSinFamily);

/************************************************************
 * 函数名 : NetcbbDhcpsGetState
 *
 * 功能 : 获取dhcp-server运行状态
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      pchIfaceName    - 网卡名字(支持"ethX", "wlanX", "bondX",
 *                        "pppX"名字，X为0,1,2...)
 *      wSinFamily      - 协议栈类型 :  NETCBB_PROTO_TYPE_IPV4
 *                                      NETCBB_PROTO_TYPE_IPV6
 *     ptNetdhcpsState  - dhcp-server的运行状态
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 失败
 *          其他错误见netcbb_def.h
 ***********************************************************/
s32 NetcbbDhcpsGetState(char *pchIfaceName, u16 wSinFamily, TNetcbbDhcpsState* ptNetdhcpsState);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
