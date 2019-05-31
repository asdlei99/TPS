#ifndef _NETCBB_DHCPS_H_
#define _NETCBB_DHCPS_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include "netcbb_def.h"

/* DHCP-Server �ص���������Ϣ���ַ */
#define NETCBB_DHCPS_MSG_BASE          (u32)80000

/* dhcp ��������DNS������Ϣ */
typedef struct{
	u32 dwDnsNum;
    TNetcbbAddr tDnsIp[NETCBB_MAX_DNS_SERVER];
}TNetcbbDnsInfo;

/* dhcp �������������ṹ�嶨�� */
typedef struct{
	TNetcbbAddr tIpPoolStart;   /* ������ : dhcp-server�������ʼ��ַ */
	TNetcbbAddr tIpPoolEnd;     /* ������ : dhcp-server�������ֹ��ַ */
	u32 dwIpPoolPrefix;         /* ������ : dhcp-server����ĵ�ַǰ׺ */
	TNetcbbAddr tRoutes;        /* ������ : dhcp-server��������ص�ַ */
	TNetcbbAddr tIfaceIp;       /* ������ : ������ַ */
	u32 dwIfacePrefix;          /* ������ : �������� */
	TNetcbbDnsInfo tDnsServerInfo;
}TNetcbbDhcpsInfo;

typedef struct
{
	u32 dwDhcpsIsRun;         /* 0:ֹͣ; 1: ���� */
}TNetcbbDhcpsState;

/************************************************************
 * ������ : NetcbbDhcpsStart
 *
 * ���� : ����DHCP-Server����
 *
 * ���� : ��
 *
 * ����˵�� :
 *      pchIfaceName    - ��������(֧��"ethX", "wlanX", "bondX",
 *                        "pppX"���֣�XΪ0,1,2...)
 *      wSinFamily      - Э��ջ���� :  NETCBB_PROTO_TYPE_IPV4
 *                                      NETCBB_PROTO_TYPE_IPV6
 *      ptDhcpsConfInfo - dhcp-server��������Ϣ
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ʧ��\
 *          ���������netcbb_def.h
 ***********************************************************/
s32 NetcbbDhcpsStart(char *pchIfaceName, u16 wSinFamily, TNetcbbDhcpsInfo* ptDhcpsConfInfo);

/************************************************************
 * ������ : NetcbbDhcpsStop
 *
 * ���� : �ر�DHCP-Server����
 *
 * ���� : ��
 *
 * ����˵�� :
 *      pchIfaceName    - ��������(֧��"ethX", "wlanX", "bondX",
 *                        "pppX"���֣�XΪ0,1,2...)
 *      wSinFamily      - Э��ջ���� :  NETCBB_PROTO_TYPE_IPV4
 *                                      NETCBB_PROTO_TYPE_IPV6
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ʧ��
 *          ���������netcbb_def.h
 ***********************************************************/
s32 NetcbbDhcpsStop(char *pchIfaceName, u16 wSinFamily);

/************************************************************
 * ������ : NetcbbDhcpsGetState
 *
 * ���� : ��ȡdhcp-server����״̬
 *
 * ���� : ��
 *
 * ����˵�� :
 *      pchIfaceName    - ��������(֧��"ethX", "wlanX", "bondX",
 *                        "pppX"���֣�XΪ0,1,2...)
 *      wSinFamily      - Э��ջ���� :  NETCBB_PROTO_TYPE_IPV4
 *                                      NETCBB_PROTO_TYPE_IPV6
 *     ptNetdhcpsState  - dhcp-server������״̬
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ʧ��
 *          ���������netcbb_def.h
 ***********************************************************/
s32 NetcbbDhcpsGetState(char *pchIfaceName, u16 wSinFamily, TNetcbbDhcpsState* ptNetdhcpsState);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
