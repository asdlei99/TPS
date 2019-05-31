#ifndef _NETCBB_TRACEROUTE_1X_H_
#define _NETCBB_TRACEROUTE_1X_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include "netcbb_def.h"
#include "netcbb_traceroute.h"

typedef struct{
	u32 dwDstIp;               /* 网络序ip地址 */
	u32 dwTtl;                 /* TTL值 适用范围0-255, 0或者255可以取到, 业务可自行进行限制，但最大不超过255 */
}TTraceroutePara;

/* TNetTracerouteCallBack 返回值。对应TNetTracerouteCallBack 中 nResult 参数 */
#define  NET_TRACEROUTE_CB_ERROR                               101
#define  NET_TRACEROUTE_CB_TIMEOUT                             102
#define  NET_TRACEROUTE_CB_MIDDLE_ROUTE                        103
#define  NET_TRACEROUTE_CB_REACH_DST                           104
#define  NET_TRACEROUTE_CB_NETWORK_UNREACHABLE                 105
#define  NET_TRACEROUTE_CB_HOST_UNREACHABLE                    106        /* 回调此类型时 traceroute会自动停止 */


typedef int(*TNetTracerouteCallBack)(s32 nResult, s32 nTtl, s32 nTripTime, u32 dwIp, s8* achDomName, s32 nUserID, s32 nErrType, s32 nErrCode);

s32 NetTracerouteStart(TTraceroutePara* ptTraceroutePara, s32 nUserID, TNetTracerouteCallBack ptCallBackFunc);
s32 NetTracerouteStop(s32 nUserID);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_INTERFACE_H_ */
