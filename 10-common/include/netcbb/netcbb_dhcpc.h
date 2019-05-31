#ifndef _NETCBB_DHCPC_H_
#define _NETCBB_DHCPC_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include "netcbb_def.h"

/* DHCPC回调函数的回调类型，用于NetcbbDhcpcNotifyCallBack回调函数的dwMsgID */
#define NETCBB_DHCPC_MSG_BASE               (u32)30000
#define NETCBB_DHCPC_SUCC_MSG               (u32)(NETCBB_DHCPC_MSG_BASE+1)
#define NETCBB_DHCPC_FAIL_MSG               (u32)(NETCBB_DHCPC_MSG_BASE+2)

/* dhcpc回调函数的消息结构体，用于强制转换pMsg */
typedef struct NetcbbDhcpcAddrInfo
{
	char achDevName[NETCBB_IFACE_NAME_LEN]; /* 接口名字 */
	TNetcbbAddr tIpAddrs;             /* ip地址 */
	TNetcbbAddr tGateWay;             /* 默认网关地址 */
	u32 dwIpPrefix;                   /* IP地址子网掩码*/
	u32 dwLeaseTime;                  /* 地址前缀(掩码) */
	u32 dwDnsNum;                     /* dns个数 */
	TNetcbbAddr atDnsServer[NETCBB_MAX_DNS_SERVER];
}TNetcbbDhcpcAddrInfo;

typedef struct
{
	u32 dwDhcpcIsRun;
}TNetcbbDhcpcState;

typedef struct NetcbbDnsAddrInfo
{
	u32 dwDnsNum;
	TNetcbbAddr atDnsServer[NETCBB_MAX_DNS_SERVER];
}TNetcbbDnsAddrInfo;

/************************************************************
 * 函数名 : NetcbbDhcpcNotifyCallBack
 *
 * 功能 : 通知dhcp成功或者失败
 *
 * 描述 :
 *       1.此函数处理应尽量简短，得到状态后，拷贝状态以及地址后,
 *         需马上返回。
 *       2.不能在回调函数中使用锁，信号量等，此容易导致死锁。
 *       3.回调NETCBB_DHCPC_SUCC_MSG时，地址网关会被设置，dns由于与用户设置
 *         的dns地址存在同步，则此动态dns由业务自己调用NetcbbDNSSet设置。
 *
 *
 * 参数说明 :
 *      dwMsgID   - 事件类型，见上面的消息类型定义
 *      pMsg      - 与该事件类型相匹配的消息内容，见上面消息类型说明
 *
 * 返回值 : 暂时都定为0，以后可以扩展
 ***********************************************************/
typedef int(*NetcbbDhcpcNotifyCallBack)(u32 dwMsgID, void* pMsg);

typedef struct
{
	u16 wSinFamily;
	NetcbbDhcpcNotifyCallBack pfDhcpcCallBack;
}TNetcbbDhcpcRegInfo;

/************************************************************
 * 函数名 : NetcbbDhcpcStart
 *
 * 功能 : 在指定的网口上开启DHCP-Client端功能
 *
 * 描述 :
 *
 * 参数说明 :
 *      pchIfaceName - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *      wSinFamily   - 协议栈类型 :  NETCBB_PROTO_TYPE_IPV4
 *                                   NETCBB_PROTO_TYPE_IPV6
 *      pfDhcpcCallBack - dhcpc回调函数，用于通知dhcpc的运行结果
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 失败
 ***********************************************************/
s32 NetcbbDhcpcStart(char *pchIfaceName, u16 wSinFamily, NetcbbDhcpcNotifyCallBack pfDhcpcCallBack);

/************************************************************
 * 函数名 : NetcbbDhcpcStop
 *
 * 功能 : 在指定的网口上关闭DHCP-Client端功能
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      pchIfaceName - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *      wSinFamily   - 协议栈类型 :  NETCBB_PROTO_TYPE_IPV4
 *                                   NETCBB_PROTO_TYPE_IPV6
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 失败
 ***********************************************************/
s32 NetcbbDhcpcStop(char *pchIfaceName, u16 wSinFamily);

/************************************************************
 * 函数名 : NetcbbDhcpcGetIfstate
 *
 * 功能 : 在指定的网口上的dhcp信息
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      pchIfaceName - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *      wSinFamily   - 协议栈类型 :  NETCBB_PROTO_TYPE_IPV4
 *                                   NETCBB_PROTO_TYPE_IPV6
 *      ptNetdhcpcIfState - dhcpc的运行状态
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 失败
 *          NETCBB_PROCESS_NOT_EXIST - UDHCPC进程不存在
 ***********************************************************/
s32 NetcbbDhcpcGetIfstate(char *pchIfaceName, u16 wSinFamily, TNetcbbDhcpcState* ptNetdhcpcIfState);

/************************************************************
 * 函数名 : NetcbbDNSSet
 *
 * 功能 : 设置静态DNS
 *
 * 描述 : 当dwNum为0时，表示删除pchIfaceName网口，wSinFamily协议栈的dns地址
 *        当atDnsIp数组元素值全为0时，表示删除pchIfaceName网口，wSinFamily协议栈的dns地址
 *
 * 参数说明 :
 *      pchIfaceName - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *      wSinFamily   - 协议栈类型 :  NETCBB_PROTO_TYPE_IPV4
 *                                   NETCBB_PROTO_TYPE_IPV6
 *      atDnsIP      - dns地址结构体数组首指针
 *      dwNum        - dns地址结构体数组成员个数
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 失败
 ***********************************************************/
s32 NetcbbDNSSet(char *pchIfaceName, u16 wSinFamily, TNetcbbAddr atDnsIP[], u32 dwNum);
/************************************************************
 * 函数名 : NetcbbDhcpcGetLeaseInfo
 *
 * 功能 : 在指定的网口上的dhcp信息
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      pchIfaceName - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *      wSinFamily   - 协议栈类型 :  NETCBB_PROTO_TYPE_IPV4
 *                                   NETCBB_PROTO_TYPE_IPV6
 *      TNetcbbDhcpcAddrInfo - dhcpc的获取的信息
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 失败
 ***********************************************************/

s32 NetcbbDhcpcGetLeaseInfo(char *pchIfaceName, u16 wSinFamily, TNetcbbDhcpcAddrInfo *ptNetDhcpcLeaseInfo);
/************************************************************
 * 函数名 : NetcbbDhcpcRenew
 *
 * 功能 : 在开启了DHCP-Client端功能的网口上主动请求更新租约
 *
 * 描述 : 无
 *
 * 参数说明 :
 *      pchIfaceName - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *      wSinFamily   - 协议栈类型 :  NETCBB_PROTO_TYPE_IPV4
 *                                   NETCBB_PROTO_TYPE_IPV6

 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 失败
 ***********************************************************/

s32 NetcbbDhcpcRenew(char *pchIfaceName, u16 wSinFamily);

/************************************************************
 * 函数名 : NetcbbDNSGet
 *
 * 功能 : 获取DNS值
 *
 * 描述 : 无
 *
 * 参数说明 :

 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 失败
 ***********************************************************/


s32 NetcbbDNSGet( TNetcbbDnsAddrInfo *atDnsIP);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
