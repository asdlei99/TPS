#ifndef _NETCBB_TRACEROUTE_H_
#define _NETCBB_TRACEROUTE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include "netcbb_def.h"

/* TNetcbbTracerouteCallBack 返回值。对应TNetcbbTracerouteCallBack 中 nResult 参数 */
#define  NETCBB_TRACEROUTE_CB_ERROR                               101
#define  NETCBB_TRACEROUTE_CB_TIMEOUT                             102
#define  NETCBB_TRACEROUTE_CB_MIDDLE_ROUTE                        103
#define  NETCBB_TRACEROUTE_CB_REACH_DST                           104
#define  NETCBB_TRACEROUTE_CB_NETWORK_UNREACHABLE                 105
#define  NETCBB_TRACEROUTE_CB_HOST_UNREACHABLE                    106        /* 回调此类型时 traceroute会自动停止 */

/* traceroute api的函数返回值 */
#define  NETCBB_TRACEROUTE_CREAT_CB_THREAD_FAILED                 (NETCBB_TRACEROUTE_BASE_ERROR + 1)
#define  NETCBB_TRACEROUTE_STASRT_FAILED                          (NETCBB_TRACEROUTE_BASE_ERROR + 2)
#define  NETCBB_TRACEROUTE_STOP_FAILED                            (NETCBB_TRACEROUTE_BASE_ERROR + 3)
#define  NETCBB_TRACEROUTE_CREAT_SEM_FAILED                       (NETCBB_TRACEROUTE_BASE_ERROR + 4)

typedef struct
{
	u32 dwTtl;                 /* TTL值 适用范围0-255, 0或者255可以取到, 业务可自行进行限制，但最大不超过255 */
}TNetcbbTracerouteOpt;

typedef struct
{
	TNetcbbAddr tIpaddr;
	u32 dwTtl;
	s32 nUserId;
	s32 nTripTime;
	char* achDomName;
	s32 nErrType;
	s32 nErrCode;
	s32 nIsOver;
}TNetcbbTracerouteCBInfo;

/************************************************************
 * 函数名 : TNetcbbTracerouteCallBack
 *
 * 功能 : Traceroute 回调函数
 *
 * 描述 :
 *       1.此函数处理应尽量简短，得到状态后，拷贝状态后,
 *         需马上返回。
 *       2.不能在回调函数中使用锁，信号量等，此容易导致死锁。
 *
 * 参数说明 :
 *      nResult    - Traceroute 回调结果(NET_TRACEROUTE_CB_ERROR, NET_TRACEROUTE_CB_TIMEOUT,
 *                                             NET_TRACEROUTE_CB_MIDDLE_ROUTE, NET_TRACEROUTE_CB_REACH_DST)
 *      nTtl       - TTL值
 *      nTripTime  - 网络传输时间值(注意:单位是微秒, 不是毫秒)
 *      dwIp       - 路由ip地址
 *      achDomName - 路由域名(暂不支持)
 *      nUserID    - 用户ID标志，用户区分不同的用户调用(暂时不支持多用户调用，赋值0)
 *      nErrType   - 错误类型(暂时可以忽略,还未支持)
 *      nErrCode   - 错误码(暂时可以忽略,还未支持)
 *
 * 返回值 : 由上层业务实现
 ***********************************************************/
typedef int(*TNetcbbTracerouteCallBack)(s32 nResult, TNetcbbTracerouteCBInfo* ptTracertCbInfo);

/************************************************************
 * 函数名 : NetcbbTracerouteStart
 *
 * 功能 : 启动Traceroute功能
 *
 * 描述 :
 *      1.暂时不支持ipv6地址.
 *      2.nUserID值必须大于0.
 *
 * 参数说明 :
 *      ptTraceroutePara   - traceroute 参数
 *      nUserID            - 用户ID标志，用户区分不同的用户调用(暂时不支持多用户调用，请赋值0)
 *      ptCallBackFunc     - traceroute结果的回调函数
 *
 * 返回值 : NET_CALLBACK_NULL                       - 回调函数没有定义
 *          NET_TRACEROUTE_CREAT_CB_THREAD_FAILED   - 创建回调线程失败
 *          NET_TRACEROUTE_CREAT_SEM_FAILED         - 创建信号量失败
 *          NET_TRACEROUTE_STASRT_FAILED            - 启动失败
 *          NETCBB_OK                               - 启动成功
 ***********************************************************/
s32 NetcbbTracerouteStart(TNetcbbAddr tDestIp, TNetcbbTracerouteOpt* ptTraceRtOpt, s32 nUserID, TNetcbbTracerouteCallBack ptCallBackFunc);

/************************************************************
 * 函数名 : NetcbbTracerouteStop
 *
 * 功能 : 停止traceroute功能
 *
 * 描述 :
 *      1.暂时不支持ipv6地址.
 *      2.nUserID值必须大于0.
 *
 * 参数说明 :
 *      nUserID            - 用户ID(暂时不支持，请赋值0)
 *
 * 返回值 : NET_TRACEROUTE_STOP_FAILED   - 终止失败
 *          NETCBB_OK                    - 终止成功
 ***********************************************************/
s32 NetcbbTracerouteStop(s32 nUserID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_INTERFACE_H_ */

