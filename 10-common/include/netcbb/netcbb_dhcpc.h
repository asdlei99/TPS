#ifndef _NETCBB_DHCPC_H_
#define _NETCBB_DHCPC_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include "netcbb_def.h"

/* DHCPC�ص������Ļص����ͣ�����NetcbbDhcpcNotifyCallBack�ص�������dwMsgID */
#define NETCBB_DHCPC_MSG_BASE               (u32)30000
#define NETCBB_DHCPC_SUCC_MSG               (u32)(NETCBB_DHCPC_MSG_BASE+1)
#define NETCBB_DHCPC_FAIL_MSG               (u32)(NETCBB_DHCPC_MSG_BASE+2)

/* dhcpc�ص���������Ϣ�ṹ�壬����ǿ��ת��pMsg */
typedef struct NetcbbDhcpcAddrInfo
{
	char achDevName[NETCBB_IFACE_NAME_LEN]; /* �ӿ����� */
	TNetcbbAddr tIpAddrs;             /* ip��ַ */
	TNetcbbAddr tGateWay;             /* Ĭ�����ص�ַ */
	u32 dwIpPrefix;                   /* IP��ַ��������*/
	u32 dwLeaseTime;                  /* ��ַǰ׺(����) */
	u32 dwDnsNum;                     /* dns���� */
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
 * ������ : NetcbbDhcpcNotifyCallBack
 *
 * ���� : ֪ͨdhcp�ɹ�����ʧ��
 *
 * ���� :
 *       1.�˺�������Ӧ������̣��õ�״̬�󣬿���״̬�Լ���ַ��,
 *         �����Ϸ��ء�
 *       2.�����ڻص�������ʹ�������ź����ȣ������׵���������
 *       3.�ص�NETCBB_DHCPC_SUCC_MSGʱ����ַ���ػᱻ���ã�dns�������û�����
 *         ��dns��ַ����ͬ������˶�̬dns��ҵ���Լ�����NetcbbDNSSet���á�
 *
 *
 * ����˵�� :
 *      dwMsgID   - �¼����ͣ����������Ϣ���Ͷ���
 *      pMsg      - ����¼�������ƥ�����Ϣ���ݣ���������Ϣ����˵��
 *
 * ����ֵ : ��ʱ����Ϊ0���Ժ������չ
 ***********************************************************/
typedef int(*NetcbbDhcpcNotifyCallBack)(u32 dwMsgID, void* pMsg);

typedef struct
{
	u16 wSinFamily;
	NetcbbDhcpcNotifyCallBack pfDhcpcCallBack;
}TNetcbbDhcpcRegInfo;

/************************************************************
 * ������ : NetcbbDhcpcStart
 *
 * ���� : ��ָ���������Ͽ���DHCP-Client�˹���
 *
 * ���� :
 *
 * ����˵�� :
 *      pchIfaceName - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *      wSinFamily   - Э��ջ���� :  NETCBB_PROTO_TYPE_IPV4
 *                                   NETCBB_PROTO_TYPE_IPV6
 *      pfDhcpcCallBack - dhcpc�ص�����������֪ͨdhcpc�����н��
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ʧ��
 ***********************************************************/
s32 NetcbbDhcpcStart(char *pchIfaceName, u16 wSinFamily, NetcbbDhcpcNotifyCallBack pfDhcpcCallBack);

/************************************************************
 * ������ : NetcbbDhcpcStop
 *
 * ���� : ��ָ���������Ϲر�DHCP-Client�˹���
 *
 * ���� : ��
 *
 * ����˵�� :
 *      pchIfaceName - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *      wSinFamily   - Э��ջ���� :  NETCBB_PROTO_TYPE_IPV4
 *                                   NETCBB_PROTO_TYPE_IPV6
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ʧ��
 ***********************************************************/
s32 NetcbbDhcpcStop(char *pchIfaceName, u16 wSinFamily);

/************************************************************
 * ������ : NetcbbDhcpcGetIfstate
 *
 * ���� : ��ָ���������ϵ�dhcp��Ϣ
 *
 * ���� : ��
 *
 * ����˵�� :
 *      pchIfaceName - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *      wSinFamily   - Э��ջ���� :  NETCBB_PROTO_TYPE_IPV4
 *                                   NETCBB_PROTO_TYPE_IPV6
 *      ptNetdhcpcIfState - dhcpc������״̬
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ʧ��
 *          NETCBB_PROCESS_NOT_EXIST - UDHCPC���̲�����
 ***********************************************************/
s32 NetcbbDhcpcGetIfstate(char *pchIfaceName, u16 wSinFamily, TNetcbbDhcpcState* ptNetdhcpcIfState);

/************************************************************
 * ������ : NetcbbDNSSet
 *
 * ���� : ���þ�̬DNS
 *
 * ���� : ��dwNumΪ0ʱ����ʾɾ��pchIfaceName���ڣ�wSinFamilyЭ��ջ��dns��ַ
 *        ��atDnsIp����Ԫ��ֵȫΪ0ʱ����ʾɾ��pchIfaceName���ڣ�wSinFamilyЭ��ջ��dns��ַ
 *
 * ����˵�� :
 *      pchIfaceName - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *      wSinFamily   - Э��ջ���� :  NETCBB_PROTO_TYPE_IPV4
 *                                   NETCBB_PROTO_TYPE_IPV6
 *      atDnsIP      - dns��ַ�ṹ��������ָ��
 *      dwNum        - dns��ַ�ṹ�������Ա����
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ʧ��
 ***********************************************************/
s32 NetcbbDNSSet(char *pchIfaceName, u16 wSinFamily, TNetcbbAddr atDnsIP[], u32 dwNum);
/************************************************************
 * ������ : NetcbbDhcpcGetLeaseInfo
 *
 * ���� : ��ָ���������ϵ�dhcp��Ϣ
 *
 * ���� : ��
 *
 * ����˵�� :
 *      pchIfaceName - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *      wSinFamily   - Э��ջ���� :  NETCBB_PROTO_TYPE_IPV4
 *                                   NETCBB_PROTO_TYPE_IPV6
 *      TNetcbbDhcpcAddrInfo - dhcpc�Ļ�ȡ����Ϣ
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ʧ��
 ***********************************************************/

s32 NetcbbDhcpcGetLeaseInfo(char *pchIfaceName, u16 wSinFamily, TNetcbbDhcpcAddrInfo *ptNetDhcpcLeaseInfo);
/************************************************************
 * ������ : NetcbbDhcpcRenew
 *
 * ���� : �ڿ�����DHCP-Client�˹��ܵ��������������������Լ
 *
 * ���� : ��
 *
 * ����˵�� :
 *      pchIfaceName - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *      wSinFamily   - Э��ջ���� :  NETCBB_PROTO_TYPE_IPV4
 *                                   NETCBB_PROTO_TYPE_IPV6

 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ʧ��
 ***********************************************************/

s32 NetcbbDhcpcRenew(char *pchIfaceName, u16 wSinFamily);

/************************************************************
 * ������ : NetcbbDNSGet
 *
 * ���� : ��ȡDNSֵ
 *
 * ���� : ��
 *
 * ����˵�� :

 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ʧ��
 ***********************************************************/


s32 NetcbbDNSGet( TNetcbbDnsAddrInfo *atDnsIP);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
