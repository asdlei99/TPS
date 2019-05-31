#ifndef _NETCBB_NTPC_1X_H_
#define _NETCBB_NTPC_1X_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include "netcbb_def.h"
#include "netcbb_ntpc.h"

//#define NETCBB_NTPC_MSG_BASE                  NETCBB_NTPC_MSG_BASE               /*NTP中调用主动向NTP-Server同步时间时回调函数的消息码基址 */
#define NETCBB_NTPC_SYNC_TIME_SUCCESS_MSG     NETCBB_NTPC_MSG_SYNC_TIME_SUCCESS  /*向NTP-Server同步时间校时成功，消息体：无*/
#define NETCBB_NTPC_SYNC_TIME_FAILED_MSG      NETCBB_NTPC_MSG_SYNC_TIME_FAILED   /*向NTP-Server同步时间校时失败，消息体：无*/


s32 NetCbbNtpcStart(u32 dwServerIp, u32 dwSyncTimeInterval, NetCbbNtpcSyncTimeCallBack  ptCallBack);
s32 NetCbbNtpcStop(void);
s32 NetCheckNtpcServer(u32 dwServerIp);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*_NETCBB_NTP_H_*/
