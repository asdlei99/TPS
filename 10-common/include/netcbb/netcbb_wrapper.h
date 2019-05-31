#ifndef _NETCBB_WRAPPER_H_
#define _NETCBB_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "netcbb_def.h"
#include "netcbb_interface.h"
#include "netcbb_dhcpc.h"
#include "netcbb_pppoe.h"
#include "netcbb_dhcps.h"
#include "netcbb_ntpc.h"
#include "netcbb_serv.h"
#include "netcbb_ping.h"
#include "netcbb_traceroute.h"

#include "1.x/netcbb_pppoe_1x.h"
#include "1.x/netcbb_traceroute_1x.h"
#include "1.x/netcbb_dhcps_1x.h"
#include "1.x/netcbb_serv_1x.h"
#include "1.x/netcbb_bond_1x.h"
#include "1.x/netcbb_dhcpc_1x.h"
#include "1.x/netcbb_interface_1x.h"
#include "1.x/netcbb_ping_1x.h"
#include "1.x/netcbb_webs_1x.h"
#include "1.x/netcbb_ntpc_1x.h"
#include "1.x/netcbb_wrapper_1x.h"

/************************************************************
 * 函数名 : NetcbbInit
 *
 * 功能 : netcbb的初始化函数
 *
 * 描述 : 无
 *
 * 参数说明 :
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 失败
 ***********************************************************/
s32 NetcbbInit(void);

/************************************************************
 * 函数名 : NetQueryNetcbbVersion
 *
 * 功能 : 提供给业务层调用的netcbb组件的版本查询号查询函数
 *
 * 描述 :
 *     1.pchVer建议空间大小为256字节，或者更大。
 *
 * 参数说明 :
 *      pchVer    - 获取版本的字符串指针
 *      dwBufLen  - 该字符串的长度
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 失败
 ***********************************************************/
s32 NetcbbQueryVersion(char* pchVer, u32 dwBufLen);

typedef enum{
	NETCBB_LEVEL_NONE,
	NETCBB_LEVEL_ALART,
	NETCBB_LEVEL_ERR,
	NETCBB_LEVEL_WARNING,
	NETCBB_LEVEL_INFO,
	NETCBB_LEVEL_DEBUG,
}ENetcbbDebugLevel;

/************************************************************
 * 函数名 : NetcbbLogSwitch
 *
 * 功能 : 本模块打印开关(默认关闭)
 *
 * 描述 : 无
 *
 * 参数说明 :
 *       eDebugLevel  - 调试级别
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 失败
 ***********************************************************/
s32 NetcbbLogSwitch(ENetcbbDebugLevel eDebugLevel);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_WRAPPER_H_ */

