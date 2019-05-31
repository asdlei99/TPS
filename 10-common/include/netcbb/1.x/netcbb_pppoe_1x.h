#include "netcbb_pppoe.h"


/* 上层业务程序调用PPPOE模块接口时出错返回值统一定义 */
#define PPPOE_OK                    (u16)0                   /* 调用成功时的返回值*/
#define PPPOE_INIT_NO_USERNAME      (u16)1                   /* 没有指定用户名时的返回值 */
#define PPPOE_INIT_NO_PASSWORD      (u16)2                   /* 没有指定登陆密码时的返回值 */
#define PPPOE_INIT_PARAM_INVALIDE   (u16)3                   /* 初始化时传入的参数不在最大最小值范围之内 */
#define PPPOE_START_NO_INIT         (u16)4                   /* 没有初始化 */
#define PPPOE_START_NO_REGCALLBACK  (u16)5                   /* 没有注册回调函数 */
#define PPPOE_CALLBACK_NULL         (u16)6                   /* 注册的回调函数为空指针 */
#define PPPOE_NOT_RUNNING           (u16)7                   /* 没有开启PPPOE服务 */
#define PPPOE_PARAMETER_NULL        (u16)8                   /* 获取版本信息时传入的指针为NULL */
#define PPPOE_CREAT_PIPE_FAILED     (u16)9                   /* 创建管道失败 */
#define PPPOE_CREAT_PROGRESS_FAILED (u16)10                  /* 创建子进程失败 */


/* PPPOE模块调用上层业务程序注册的回调函数发送通知消息的消息ID号定义 */
/* 消息ID的基址--------保留1千个消息定以（9000--10000） */
#define PPPOE_MSG_BASE              (u32)9000

/* 因为用户名或者密码不正确而造成PPPOE模块拨号身份验证失败的通知消息 */
/* 消息内容--- 结构体TAuthFailed */
#define PPPOE_AUTH_FAILED_MSG       (u32)(PPPOE_MSG_BASE + 1)

/* 拨号超时通知消息 */
/* 消息内容--- 无 */
#define PPPOE_DIAL_TIMEOUT_MSG      (u32)(PPPOE_MSG_BASE + 2)

/* 建链通知消息,消息内容是新获得的IP地址 */
/* 消息内容--- 结构体TConnNotify */
#define PPPOE_LINK_UP_MSG           (u32)(PPPOE_MSG_BASE + 3)

/* 断链通知消息 */
/* 消息内容--- 无 */
#define PPPOE_LINK_DOWN_MSG         (u32)(PPPOE_MSG_BASE + 4)

/* 找不到指定的ISP服务商通知消息 */
/* 消息内容--- 结构体 TNoServer */
#define PPPOE_NO_REQUIREDSERVER_MSG (u32)(PPPOE_MSG_BASE + 5)
#define PPPOE_DIALING_MSG           (u32)(PPPOE_MSG_BASE + 6)

/* 找不到服务器、超时等情况 */
#define PPPOE_GENERAL_SERVER_ERROR_MSG     (u32)(PPPOE_MSG_BASE + 7)


/* 上层业务程序初始化PPPOE模块时使用的结构体 */
typedef struct  PppoeInitParam{
    char      abyUserName [NETCBB_USERNAME_LEN];     /* 拨号时使用的用户名,必填项 */
    char      abyPassword [NETCBB_PASSWORD_LEN];    /* 拨号时使用的密码,必填项 */
    char      abyServerName[NETCBB_SERVNAME_LEN]; /* 指定拨号服务商的名字,可以不填 */
    BOOL32    bAutoDialEnable;                   /* 是否允许断链后自动拨号,默认不自动拨号,只有启用自动拨号后，重播次数和重拨时间才有意义。否则无效 */
    BOOL32    bDefaultRouteEnable;               /* 是否允许将对端的地址设为默认网关，默认不设为网关 */
    BOOL32    bDebug;                            /* 是否以debug模式运行pppoe，默认不运行在debug模式 */
    u32       dwAutoDialInterval;                /* 断链后再次自动拨号需要等带的时间（允许设置成0s）*/
    u16       wDialRetryTimes;                   /* 拨号尝试的次数，如果达到该次数还没有响应则拨号失败,默认为10，为0则无限制拨号 */
    u16       wLcpEchoSendInterval;              /* 链接建立后，发送LCP-ECHO包的时间间隔,默认设置为20 */
    u16       wLcpEchoRetryTimes;                /* 发送几次LCP-ECHO包没有得到相应则认为链接断开,默认设置为3 */
    u32       dwEthID;                           /* PPPOE服务需要绑定的以太网的ID号（从0开始）*/
}TPppoeInitParam;

/* 调用上层业务程序注册的回调函数发送建链通知消息的结构体 */
typedef struct ConnNotify{
    u32  dwOurIpAddr;   /* 本断获得的IP地址,网络序 */
    u32  dwPeerIpAddr;  /* 对端的IP地址 */
    u32  dwDnsServer1;  /* DNS Server1,网络序 */
    u32  dwDnsServer2;  /* DNS Server1,网络序 */
}TConnNotify;

/*上层业务程序注册的回调类型定义*/
/*参数说明 : u32 dwMsgID   - 消息的ID号,由PPPOE模块填充
 *              u8 *pbyMsg    - 指向消息内容的指针,由PPPOE模块填充
 *                           u32 dwMsgLen  - 消息内容的有效长度,由PPPOE模块填充 */
typedef void (*TPppoeCallBack)(u32 dwMsgID, u8* pbyMsg, u32 dwMsgLen);

#define MAX_VERSION_LEN             (u16)255                 /* PPPOE版本信息的最大长度 */
/*存储PPPOE版本信息的结构体*/
typedef struct PppoeVersion{
	    char  abyVersion[MAX_VERSION_LEN];
}TVersion;

/************************************************************
 * 函数名 : PppoeStart
 *
 * 功能 : 启动PPPoE服务
 *
 * 描述 : 原PppoeInit和PppoeCallBackReg都集成在NetPppoeStart中
 *
 * 参数说明 :
 *
 * 返回值 : oK - 成功
 *          ERROR - 失败
 *          参考netcbb_def.h
 ***********************************************************/
s32 NetPppoeStart(TPppoeInitParam* ptPppoeInitParam, TPppoeCallBack ptNotifyCallBack);

/************************************************************
 * 函数名 : PppoeStop
 *
 * 功能 : 停止PPPoE服务
 *
 * 描述 :
 *
 * 参数说明 :
 *
 * 返回值 : #define PPPOE_ OK           0
 *          #define PPPOE_NOT_RUNNING   6
 ***********************************************************/
s32 NetPppoeStop(void);

/************************************************************
 * 函数名 : NetPppoeVer
 *
 * 功能 : 获取PPPoE模块的版本信息
 *
 * 描述 :
 * 参数说明 :
 *      ptVersion - 指向存放版本信息的指针
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetPppoeVer(TVersion* ptVersion);
