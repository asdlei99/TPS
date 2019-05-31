#ifndef _NETCBB_DEF_H_
#define _NETCBB_DEF_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <arpa/inet.h>

#define NETCBB_OK                        0
#define NETCBB_ERROR                    -1

/* api ����ֵ�����붨�壬���еķ���ֵ���Ѿ�ͳһ��ҵ����Դ���һ��������������ֵ������ͷ�ļ�������һһ���� */
#define NETCBB_BASE_ERROR               1100
#define NETCBB_IF_BASE_ERROR            1200
#define NETCBB_PING_BASE_ERROR          1300
#define NETCBB_TRACEROUTE_BASE_ERROR    1400
#define NET_E1_BASE_ERROR               1500


/* ������4��TIMEOUT����ֵ�����Բ�ȡ��Ӧ�Ĵ�ʩ,�������µ��ö�Ӧ�������ߺ��� */
#define NETCBB_IPC_SENDC_TIMEOUT        (NETCBB_BASE_ERROR+1)    /* client ������Ϣ��ʱ */
#define NETCBB_IPC_RECVC_TIMEOUT        (NETCBB_BASE_ERROR+2)    /* client ������Ϣ��ʱ */
#define NETCBB_IPC_SENDD_TIMEOUT        (NETCBB_BASE_ERROR+3)	 /* daemon������Ϣ��ʱ */
#define NETCBB_IPC_RECVD_TIMEOUT        (NETCBB_BASE_ERROR+4)    /* daemon������Ϣ��ʱ */
#define NETCBB_INVALID_PARAM            (NETCBB_BASE_ERROR+5)    /* ��Ч�Ĳ��� */
#define NETCBB_CALLBACK_NULL            (NETCBB_BASE_ERROR+6)    /* �ص�����û�ж��� */
#define NETCBB_FORK_ERROR               (NETCBB_BASE_ERROR+7)    /* �����ӽ���ʧ�� */
#define NETCBB_PROCESS_NOT_EXIST        (NETCBB_BASE_ERROR+8)    /* ���̲����� */
#define NETCBB_MODULE_INIT_ERROR        (NETCBB_BASE_ERROR+9)    /* ģ������ʧ�� */
#define NETCBB_NOT_THE_SAME_NET         (NETCBB_BASE_ERROR+11)   /* �����������ͬһ������ */

#define NETCBB_IF_NOT_EXIST             (NETCBB_IF_BASE_ERROR+1) /* �ӿڲ����� */
#define NETCBB_IF_ADDR_NOT_EXIST        (NETCBB_IF_BASE_ERROR+2) /* ��ַ������ */


#define NETCBB_IF_UP                    1  /* �ӿڴ� */
#define NETCBB_IF_DOWN                  2  /* �ӿڹر� */
#define NETCBB_IF_BUSY                  3  /* �ӿ�ʹ���� */

#define NETCBB_ROUTE_MAX_NUM            10  /* ·��֧��������� */
#define NETCBB_NIC_MAX_NUM              4   /* ����֧��������� */
#define NETCBB_IP_MAX_NUM               16  /* ��Linux��һ�����ڿ������õ�����IP��ַ */
#define NETCBB_VERSION_LEN              256 /* �汾�ŵ���󳤶� */

#define NETCBB_PROTO_TYPE_IPV4          AF_INET      /* ipv4Э���� */
#define NETCBB_PROTO_TYPE_IPV6          AF_INET6     /* ipv6Э���� */
#define NETCBB_PROTO_TYPE_ALL           (AF_INET6+1) /* ipv4+ipv6 */

#define NETCBB_MAX_DNS_SERVER           64

#define NETCBB_IFACE_NAME_LEN           16
#define NETCBB_MAC_LEN                  6

#define NET_DEF_FILE_PATH_LEN       100
#define NET_DEF_FILE_LEN            32
#define NET_DEF_STR_LEN             32
#define NET_DEF_STR_LEN_LONGER      100


#if 1
/* NetSetEthParam������byIpOrMac����ֵ�ĺ궨�� */
#define Net_SET_IP_AND_MASK         1      /* ����IP��ַ���������� */
#define Net_SET_MAC_ADDR            2      /* ����MAC��ַ */
#define Net_SET_ETH_ALL_PARAM       3      /* ������̫����IP��ַ�����������MAC��ַ */
#define Net_SET_ETH_SEC_IP          4      /* ������̫���ڶ�IP ��ַ */

/* ������4��TIMEOUT����ֵ�����Բ�ȡ��Ӧ�Ĵ�ʩ,�������µ��ö�Ӧ�������ߺ��� */
#define NET_IPC_SENDC_TIMEOUT        NETCBB_IPC_SENDC_TIMEOUT    /* client ������Ϣ��ʱ */
#define NET_IPC_RECVC_TIMEOUT        NETCBB_IPC_RECVC_TIMEOUT    /* client ������Ϣ��ʱ */
#define NET_IPC_SENDD_TIMEOUT        NETCBB_IPC_SENDD_TIMEOUT	 /* daemon������Ϣ��ʱ */
#define NET_IPC_RECVD_TIMEOUT        NETCBB_IPC_RECVD_TIMEOUT    /* daemon������Ϣ��ʱ */
#define NET_INVALID_PARAM            NETCBB_INVALID_PARAM    /* ��Ч�Ĳ��� */
#define NET_CALLBACK_NULL           NETCBB_CALLBACK_NULL    /* �ص�����û�ж��� */
#define NET_FORK_ERROR               NETCBB_FORK_ERROR    /* �����ӽ���ʧ�� */
#define NET_PROCESS_NOT_EXIST        NETCBB_PROCESS_NOT_EXIST    /* ���̲����� */
#define NET_MODULE_INIT_ERROR        NETCBB_MODULE_INIT_ERROR    /* ģ������ʧ�� */
#define NET_NOT_THE_SAME_NET         NETCBB_NOT_THE_SAME_NET   /* �����������ͬһ������ */

#define IP_ROUTE_MAX_NUM            NETCBB_ROUTE_MAX_NUM  /* ·��֧��������� */
#define IP_ADDR_MAX_NUM               NETCBB_IP_MAX_NUM  /* ��Linux��һ�����ڿ������õ�����IP��ַ */
#define NET_MAX_VERSION_LEN              NETCBB_VERSION_LEN /* �汾�ŵ���󳤶� */

#define NET_IF_NOT_EXIST             NETCBB_IF_NOT_EXIST /* �ӿڲ����� */
#define NET_IF_ADDR_NOT_EXIST        NETCBB_IF_ADDR_NOT_EXIST /* ��ַ������ */

#define NET_IF_DOWN            NETCBB_IF_DOWN
#define NET_IF_UP              NETCBB_IF_UP

#endif
/* IPv6��ַ���� */
typedef enum{
	NETCBB_SCOPE_TYPE_DEF = 0, /* Ĭ��ʹ��NETCBB_SCOPE_TYPE_GLOBAL���� */
	NETCBB_SCOPE_TYPE_HOST,
	NETCBB_SCOPE_TYPE_LINK, /* LINK��ַ, �����͵�ַ�����޸� */
	NETCBB_SCOPE_TYPE_SITE,
	NETCBB_SCOPE_TYPE_GLOBAL,
}ENetcbbScopeType;

typedef struct NetcbbAddr
{
	u16 wSinFamily;  /* NETCBB_PROTO_TYPE_IPV4 or NETCBB_PROTO_TYPE_IPV6 */
	union{
		struct in_addr tV4Addr;
		struct in6_addr tV6Addr;
	};
}TNetcbbAddr;

typedef struct{
	ENetcbbScopeType eScopeType; /* Ĭ��ֵ0ΪSCOPE_GLOBAL */
    TNetcbbAddr tIpAddr;         /* �����ֽ��� */
    u32 dwPrefix;                /* �����ֽ��� */
}TNetcbbIfaceIp;

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif

