#ifndef _NETCBB_PING_1X_H_
#define _NETCBB_PING_1X_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "netcbb_ping.h"

/* NetPing接口传入参数结构体 */
typedef struct{
	s32 nPktSize;   /* 要ping的数据报的大小，以字节为单位不得小于56，如果小于56，将赋值56 */
	s32 nTimeOut;   /* ping的超时值，以秒为单位 */
	s32 nTtl;       /* TTL值 适用范围0-255, 0或者255可以取到, 业务可自行进行限制，但最大不超过255 */
	s32 nCount;     /* ping包数目 */
}TPingOpt;

/* TPingCallBack回调的返回值，对应参数为nResult */
#define    NET_PING_REPLY          0    /* ping包正常回应 */
#define    NET_PING_TIMEOUT        1    /* ping包超时 */
#define    NET_PING_ERROR          2    /* ping包系统错误 */
#define    NET_PING_NET_UNREACH    3    /* ping包网络不可达 */


#define    NET_PING_CREAT_CB_THREAD_FAILED    NETCBB_PING_CREAT_CB_THREAD_FAILED
#define    NET_PING_STASRT_FAILED             NETCBB_PING_STASRT_FAILED
#define    NET_PING_STOP_FAILED               NETCBB_PING_STOP_FAILED
#define    NET_PING_ALREADY_START             NETCBB_PING_ALREADY_START
#define    NET_PING_ALREADY_STOP              NETCBB_PING_ALREADY_STOP


typedef int(*TNetPingCallBack)(s32 nResult, s32 nTtl, s32 nTripTime, s32 nSeq, s32 nUserID, s32 nErrType, s32 nErrCode);
s32 NetPingStart(u32 dwDestIP, TPingOpt* ptPingOpt, s32 nUserID, TNetPingCallBack ptCallBackFunc);
s32 NetPingStop(s32 nUserID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
