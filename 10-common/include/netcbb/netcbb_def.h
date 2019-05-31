#ifndef _NETCBB_DEF_H_
#define _NETCBB_DEF_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <arpa/inet.h>

#define NETCBB_OK                        0
#define NETCBB_ERROR                    -1

/* api 返回值错误码定义，所有的返回值都已经统一，业务可以创建一个函数来处理返回值。不在头文件描述中一一介绍 */
#define NETCBB_BASE_ERROR               1100
#define NETCBB_IF_BASE_ERROR            1200
#define NETCBB_PING_BASE_ERROR          1300
#define NETCBB_TRACEROUTE_BASE_ERROR    1400
#define NET_E1_BASE_ERROR               1500


/* 根据这4种TIMEOUT返回值，可以采取对应的措施,例如重新调用对应函数或者忽略 */
#define NETCBB_IPC_SENDC_TIMEOUT        (NETCBB_BASE_ERROR+1)    /* client 发送消息超时 */
#define NETCBB_IPC_RECVC_TIMEOUT        (NETCBB_BASE_ERROR+2)    /* client 接受消息超时 */
#define NETCBB_IPC_SENDD_TIMEOUT        (NETCBB_BASE_ERROR+3)	 /* daemon发送消息超时 */
#define NETCBB_IPC_RECVD_TIMEOUT        (NETCBB_BASE_ERROR+4)    /* daemon接受消息超时 */
#define NETCBB_INVALID_PARAM            (NETCBB_BASE_ERROR+5)    /* 无效的参数 */
#define NETCBB_CALLBACK_NULL            (NETCBB_BASE_ERROR+6)    /* 回调函数没有定义 */
#define NETCBB_FORK_ERROR               (NETCBB_BASE_ERROR+7)    /* 创建子进程失败 */
#define NETCBB_PROCESS_NOT_EXIST        (NETCBB_BASE_ERROR+8)    /* 进程不存在 */
#define NETCBB_MODULE_INIT_ERROR        (NETCBB_BASE_ERROR+9)    /* 模块启动失败 */
#define NETCBB_NOT_THE_SAME_NET         (NETCBB_BASE_ERROR+11)   /* 网络参数不在同一个网段 */

#define NETCBB_IF_NOT_EXIST             (NETCBB_IF_BASE_ERROR+1) /* 接口不存在 */
#define NETCBB_IF_ADDR_NOT_EXIST        (NETCBB_IF_BASE_ERROR+2) /* 地址不存在 */


#define NETCBB_IF_UP                    1  /* 接口打开 */
#define NETCBB_IF_DOWN                  2  /* 接口关闭 */
#define NETCBB_IF_BUSY                  3  /* 接口使用中 */

#define NETCBB_ROUTE_MAX_NUM            10  /* 路由支持做多个数 */
#define NETCBB_NIC_MAX_NUM              4   /* 网卡支持做多个数 */
#define NETCBB_IP_MAX_NUM               16  /* 在Linux下一个网口可以配置的最多的IP地址 */
#define NETCBB_VERSION_LEN              256 /* 版本号的最大长度 */

#define NETCBB_PROTO_TYPE_IPV4          AF_INET      /* ipv4协议族 */
#define NETCBB_PROTO_TYPE_IPV6          AF_INET6     /* ipv6协议族 */
#define NETCBB_PROTO_TYPE_ALL           (AF_INET6+1) /* ipv4+ipv6 */

#define NETCBB_MAX_DNS_SERVER           64

#define NETCBB_IFACE_NAME_LEN           16
#define NETCBB_MAC_LEN                  6

#define NET_DEF_FILE_PATH_LEN       100
#define NET_DEF_FILE_LEN            32
#define NET_DEF_STR_LEN             32
#define NET_DEF_STR_LEN_LONGER      100


#if 1
/* NetSetEthParam函数中byIpOrMac输入值的宏定义 */
#define Net_SET_IP_AND_MASK         1      /* 设置IP地址和子网掩码 */
#define Net_SET_MAC_ADDR            2      /* 设置MAC地址 */
#define Net_SET_ETH_ALL_PARAM       3      /* 设置以太网的IP地址、子网掩码和MAC地址 */
#define Net_SET_ETH_SEC_IP          4      /* 设置以太网第二IP 地址 */

/* 根据这4种TIMEOUT返回值，可以采取对应的措施,例如重新调用对应函数或者忽略 */
#define NET_IPC_SENDC_TIMEOUT        NETCBB_IPC_SENDC_TIMEOUT    /* client 发送消息超时 */
#define NET_IPC_RECVC_TIMEOUT        NETCBB_IPC_RECVC_TIMEOUT    /* client 接受消息超时 */
#define NET_IPC_SENDD_TIMEOUT        NETCBB_IPC_SENDD_TIMEOUT	 /* daemon发送消息超时 */
#define NET_IPC_RECVD_TIMEOUT        NETCBB_IPC_RECVD_TIMEOUT    /* daemon接受消息超时 */
#define NET_INVALID_PARAM            NETCBB_INVALID_PARAM    /* 无效的参数 */
#define NET_CALLBACK_NULL           NETCBB_CALLBACK_NULL    /* 回调函数没有定义 */
#define NET_FORK_ERROR               NETCBB_FORK_ERROR    /* 创建子进程失败 */
#define NET_PROCESS_NOT_EXIST        NETCBB_PROCESS_NOT_EXIST    /* 进程不存在 */
#define NET_MODULE_INIT_ERROR        NETCBB_MODULE_INIT_ERROR    /* 模块启动失败 */
#define NET_NOT_THE_SAME_NET         NETCBB_NOT_THE_SAME_NET   /* 网络参数不在同一个网段 */

#define IP_ROUTE_MAX_NUM            NETCBB_ROUTE_MAX_NUM  /* 路由支持做多个数 */
#define IP_ADDR_MAX_NUM               NETCBB_IP_MAX_NUM  /* 在Linux下一个网口可以配置的最多的IP地址 */
#define NET_MAX_VERSION_LEN              NETCBB_VERSION_LEN /* 版本号的最大长度 */

#define NET_IF_NOT_EXIST             NETCBB_IF_NOT_EXIST /* 接口不存在 */
#define NET_IF_ADDR_NOT_EXIST        NETCBB_IF_ADDR_NOT_EXIST /* 地址不存在 */

#define NET_IF_DOWN            NETCBB_IF_DOWN
#define NET_IF_UP              NETCBB_IF_UP

#endif
/* IPv6地址类型 */
typedef enum{
	NETCBB_SCOPE_TYPE_DEF = 0, /* 默认使用NETCBB_SCOPE_TYPE_GLOBAL类型 */
	NETCBB_SCOPE_TYPE_HOST,
	NETCBB_SCOPE_TYPE_LINK, /* LINK地址, 此类型地址不可修改 */
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
	ENetcbbScopeType eScopeType; /* 默认值0为SCOPE_GLOBAL */
    TNetcbbAddr tIpAddr;         /* 网络字节序 */
    u32 dwPrefix;                /* 主机字节序 */
}TNetcbbIfaceIp;

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif

