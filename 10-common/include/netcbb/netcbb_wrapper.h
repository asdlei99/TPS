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
 * ������ : NetcbbInit
 *
 * ���� : netcbb�ĳ�ʼ������
 *
 * ���� : ��
 *
 * ����˵�� :
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ʧ��
 ***********************************************************/
s32 NetcbbInit(void);

/************************************************************
 * ������ : NetQueryNetcbbVersion
 *
 * ���� : �ṩ��ҵ�����õ�netcbb����İ汾��ѯ�Ų�ѯ����
 *
 * ���� :
 *     1.pchVer����ռ��СΪ256�ֽڣ����߸���
 *
 * ����˵�� :
 *      pchVer    - ��ȡ�汾���ַ���ָ��
 *      dwBufLen  - ���ַ����ĳ���
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ʧ��
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
 * ������ : NetcbbLogSwitch
 *
 * ���� : ��ģ���ӡ����(Ĭ�Ϲر�)
 *
 * ���� : ��
 *
 * ����˵�� :
 *       eDebugLevel  - ���Լ���
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ʧ��
 ***********************************************************/
s32 NetcbbLogSwitch(ENetcbbDebugLevel eDebugLevel);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_WRAPPER_H_ */

