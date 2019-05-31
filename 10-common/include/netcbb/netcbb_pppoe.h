#ifndef _NETCBB_PPPOE_H_
#define _NETCBB_PPPOE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define NETCBB_USERNAME_LEN     255
#define NETCBB_PASSWORD_LEN     255
#define NETCBB_SERVNAME_LEN     255

/* pppoe拨号回调消息ID */
#define NETCBB_PPPOE_MSG_SUCC   		    1  /* 拨号成功 */
#define NETCBB_PPPOE_MSG_DIALING		    2  /* 正在拨号 */
#define NETCBB_PPPOE_MSG_DIAL_TIMEOUT		3  /* 拨号超时 */
#define NETCBB_PPPOE_MSG_AUTH_FAILED		4  /* 认证失败 */
#define NETCBB_PPPOE_MSG_DOWN		        5  /* pppoe服务关闭 */

typedef struct NetcbbPppoeParam{
	char      achUserName[NETCBB_USERNAME_LEN];   /* 拨号时使用的用户名,必填项 */
	char      achPassword[NETCBB_PASSWORD_LEN];   /* 拨号时使用的密码,必填项 */
	char      achServerName[NETCBB_SERVNAME_LEN]; /* 指定拨号服务商的名字,可以不填 */
	char      achDevName[NETCBB_IFACE_NAME_LEN];      /* 拨号需要绑定的网络接口名字，如"eth0" */
	BOOL32    bAutoDialEnable;      /* 是否允许断链后自动拨号,默认不自动拨号,只有启用自动拨号后，重播次数和重拨时间才有意义。否则无效 */
	BOOL32    bDefaultRouteEnable;  /* 是否允许将对端的地址设为默认网关，默认不设为网关 */
	BOOL32    bDebug;               /* 是否以debug模式运行pppoe，默认不运行在debug模式 */
	u32       dwAutoDialInterval;   /* 断链后再次自动拨号需要等带的时间（允许设置成0s）*/
	u16       wDialRetryTimes;      /* 拨号尝试的次数，如果达到该次数还没有响应则拨号失败,默认为10，为0则无限制拨号 */
	u16       wLcpEchoSendInterval; /* 链接建立后，发送LCP-ECHO包的时间间隔,默认设置为20，可取值1~255 */
	u16       wLcpEchoRetryTimes;   /* 发送几次LCP-ECHO包没有得到相应则认为链接断开,默认设置为3 */
}TNetcbbPppoeParam;

typedef struct NetcbbPppoeStates{
	BOOL32  bPppoeRunning;                          /* PPPOE是否运行，TRUR—运行；FALSE—没有运行 */
	TNetcbbAddr tOurIpaddr;                         /* 本断获得的IP地址,网络序 */
	TNetcbbAddr tPeerIpAddr;                        /* 对端的IP地址 */
	char    achServerName[NETCBB_SERVNAME_LEN]; /* ISP Server的名字 */
	u32     dwLinkKeepTimes;                        /* 链路建立的时间 */
	u32     dwLinkDownTimes;                        /* 链路断链的次数统计 */
	u32     dwPktsSend;                             /* 总共发送的数据包数--包括各类协议包以及上层业务程序的数据包 */
	u32     dwPktsRecv;                             /* 总共接收的数据包数 */
	u32     dwBytesSend;                            /* 总共发送的字节数 */
	u32     dwBytesRecv;                            /* 总共接收的字节数 */
}TNetcbbPppoeStates;

/* 调用上层业务程序注册的回调函数发送建链通知消息的结构体
 * 对应NETCBB_PPPOE_SUCC消息
 */
typedef struct NetcbbPppoeAddr{
	TNetcbbAddr tOurIpaddr;  /* 本断获得的IP地址,网络序 */
	TNetcbbAddr tPeerIpAddr; /* 对端的IP地址 */
	TNetcbbAddr tDnsServer1; /* DNS Server1,网络序 */
	TNetcbbAddr tDnsServer2; /* DNS Server1,网络序 */
}TNetcbbPppoeAddr;

/* 通知业务程序找不到指定的ISP Server的消息结构体 */
typedef struct NoServer{
    char  achServerName[NETCBB_SERVNAME_LEN]; /* ISP Server的名字 */
}TNoServer;

/*存储PPPOE版本信息的结构体*/
typedef struct Version{
    char  achVersion[NETCBB_VERSION_LEN];
}TNetcbbVersion;

/************************************************************
 * 函数名 : TNetcbbPppoeCallBack
 *
 * 功能 : 回调pppoe拨号结果
 *
 * 描述 :
 *       1.此函数处理应尽量简短，得到状态后，拷贝状态以及地址后,
 *         需马上返回。
 *       2.不能在回调函数中使用锁，信号量等，此容易导致死锁。
 *
 * 参数说明 :
 *       dwMsgID   - 消息的ID号，如NETCBB_PPPOE_SUCC等
 *       msg       - 指向消息内容的指针,由PPPOE模块填充
 *       dwMsgLen  - 消息内容的有效长度,由PPPOE模块填充
 *
 * 返回值 : oK - 成功
 *          NETCBB_ERROR - 失败
 *          参考netcbb_def.h
 ***********************************************************/
typedef void (*TNetcbbPppoeCallBack)(u32 dwMsgID, void* msg, u32 dwMsgLen);

/************************************************************
 * 函数名 : NetcbbPppoeStart
 *
 * 功能 : 启动PPPoE服务
 *
 * 描述 : 暂时不提供支持多网卡服务，如有支持多网卡需求，请单独
 *        提需求实现
 *
 * 参数说明 :
 *       ptPppoeParam     - pppoe拨号所需要的参数
 *       wSinFamily       - 协议栈类型 :  NETCBB_PROTO_TYPE_IPV4
 *                                      NETCBB_PROTO_TYPE_IPV6
 *       ptNotifyCallBack - pppoe回调通知函数
 *
 * 返回值 : NETCBB_OK
 *          NETCBB_ERROR
 *          其他参考netcbb_def.h
 ***********************************************************/
s32 NetcbbPppoeStart(TNetcbbPppoeParam* ptPppoeParam, u16 wSinFamily, TNetcbbPppoeCallBack ptNotifyCallBack);

/************************************************************
 * 函数名 : NetcbbPppoeStop
 *
 * 功能 : 停止PPPoE服务
 *
 * 描述 :

 *
 * 参数说明 :
 *      pchIfaceName   - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *      wSinFamily     - 协议栈类型 :  NETCBB_PROTO_TYPE_IPV4
 *                                     NETCBB_PROTO_TYPE_IPV6
 *
 * 返回值 : NETCBB_OK
 *          NETCBB_ERROR
 *          其他参考netcbb_def.h
 ***********************************************************/
s32 NetcbbPppoeStop(char *pchIfaceName, u16 wSinFamily);

/************************************************************
 * 函数名 : NetcbbPppoeStatesDump
 *
 * 功能 : 获取PPPoE模块的统计信息
 *
 * 描述 : 暂时不提供支持
 *
 * 参数说明 :
 *      ptPppoeStates - 指向存放统计结果的指针
 *
 * 返回值 : 无
 ***********************************************************/
void NetcbbPppoeStatesDump(TNetcbbPppoeStates* ptPppoeStates);

/************************************************************
 * 函数名 : NetcbbPppoeVer
 *
 * 功能 : 获取PPPoE模块的版本信息
 *
 * 描述 :
 *
 * 参数说明 :
 *      ptVersion - 指向存放版本信息的指针
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 失败
 ***********************************************************/
s32 NetcbbPppoeVer(TNetcbbVersion* ptVersion);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_PPPOE_H_ */

