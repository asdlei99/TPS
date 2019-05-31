#ifndef _NETCBB_BOND_H_
#define _NETCBB_BOND_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "netcbb_def.h"

/* bond模式 */
#define NETCBB_BOND_MODE_ROUNDROBIN    0
#define NETCBB_BOND_MODE_ACTIVEBACKUP  1  /* 主备模式 */
#define NETCBB_BOND_MODE_XOR           2
#define NETCBB_BOND_MODE_BROADCAST     3
#define NETCBB_BOND_MODE_8023AD        4  /* 带宽翻倍，网卡需对接的交换机需支持链路聚合 */
#define NETCBB_BOND_MODE_TLB           5
#define NETCBB_BOND_MODE_ALB           6  /* TLB + RLB (receive load balancing) */

typedef struct
{
	char *achIface[NETCBB_NIC_MAX_NUM]; /* 需要绑定的网卡接口列表指针 */
	u32 dwIfaceNum;             /* 需要绑定的网卡接口个数 */
	char *pchActiveIface;       /* bond中优先使用的网卡, 如"eth0" */
	char *pchBondPath;          /* bond.ko的路径，如/lib/module */
}TNetcbbBondParam;

/************************************************************
 * 函数名 : NetcbbBondStart
 *
 * 功能 : 开启bond模式
 *
 * 描述 :
 *     1.目前hisi仅支持BOND_MODE_ACTIVEBACKUP模式.
 *     2.如果成功，则系统总是有bond0虚拟接口，后续所有操作均直接操作
 *       bond0即可。
 *
 *
 * 参数说明 :
 *          dwBondMode    - bond模式(BOND_MODE_ROUNDROBIN等)
 *          ptBondParam   - bond模式参数
 *
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 失败
 ***********************************************************/
s32 NetcbbBondStart(u32 dwBondMode, TNetcbbBondParam *ptBondParam);

/************************************************************
 * 函数名 : NetcbbBondStop
 *
 * 功能 : 停止bond模式
 *
 * 描述 : 停止bond模式时，会将网口相关的配置清除
 *
 * 参数说明 :
 *
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 失败
 ***********************************************************/
s32 NetcbbBondStop();


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
