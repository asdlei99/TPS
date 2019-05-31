#ifndef _NETCBB_INTERFACE_H_
#define _NETCBB_INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "netcbb_def.h"
#include "netcbb_e1.h"

/* 网路接口参数结构 */
typedef struct{
    u32 dwIpNum; /* 有效的IP地址数 */
    TNetcbbIfaceIp atNetIfaceIp[NETCBB_IP_MAX_NUM];  /* 存放IP地址等信息的数组 */
}TNetcbbIfaceAllIp;

/* 网路接口mac地址结构 */
typedef struct{
	u8 abyMacAddr[NETCBB_MAC_LEN];
}TNetcbbIfaceMac;

/* 单个路由参数结构 */
typedef struct{
	char achIfaceName[NETCBB_IFACE_NAME_LEN]; /* 接口名字, 如"eth0" */
	TNetcbbAddr tDestIpNet;    /* 目的子网，网络字节序 */
	TNetcbbAddr tDestGateWay;  /* 网关ip地址，网络字节序 */
	u32 dwPrefix;         /* 掩码，网络字节序 */
	u32 dwRoutePri;       /* 路由优先级(1-255)，默认为0 */
}TNetcbbIpRouteParam;

/* 多个路由参数结构 */
typedef struct{
	u32 dwIpRouteNum;    /* 得到的实际路由个数 */
	TNetcbbIpRouteParam tNetIpRouteParam[NETCBB_ROUTE_MAX_NUM];
}TNetcbbAllIpRouteInfo;

/* 路由通告回调结构体, 只用于ipv6 */
typedef struct{
	char achIfaceName[NETCBB_IFACE_NAME_LEN]; /* 接口名字, 如"eth0" */
	TNetcbbIfaceAllIp tNetIfaceAllIp;         /* 接口所有的Ipv6地址信息 */
}TNetcbbRouterAdCb;

typedef enum IP_CONFLICT_TYPE{
	NETCBB_IP_CONFLICT = 1,
	NETCBB_MAC_CONFLICT = 2,
}ENetcbbConflictType;

/* 网卡统计信息 */
typedef struct{
	u32 byEthId;
	u64 dwBandSended; /* (bit/s) 1Gbit/s == 1000Mbit/s == 1000*1000kbit/s == 1000*1000*1000 bit/s */
	u64 dwBandRecved; /* (bit/s) */
}TNetDevStat;

/* IP地址冲突回调函数类型定义 */
typedef void (*TNetcbbConflictCallBack)(ENetcbbConflictType eType, TNetcbbIfaceMac *ptIfaceMac, TNetcbbAddr *ptIpAddr);

/* 路由通告函数 */
typedef void (*TNetcbbRouterAdvertiseCallBack)(TNetcbbRouterAdCb *ptCbInfo);

/* 网卡统计通知函数 */
typedef void (*TDevStatNotifyCallBack)(TNetDevStat aptdevStat[], u32 dwEthNum);

/************************************************************
 * 函数名 : NetcbbRouterAdvertiseStart
 *
 * 功能 : 开启路由通告功能。
 *
 * 描述 :
 *       1.开启路由通告功能，注册路由通告回调函数。
 *         此功能只供ipv6协议栈配置路由通告地址使用。
 *       2.此函数处理应尽量简短，得到状态后，拷贝状态后,
 *         需马上返回。
 *       3.不能在回调函数中使用锁，信号量等，此容易导致死锁。
 *
 * 参数说明 :
 *      pchIfaceName   - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *      pfRACallback   - 路由通告回调函数
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbRouterAdvertiseStart(char *pchIfaceName, TNetcbbRouterAdvertiseCallBack pfRACallback);

/************************************************************
 * 函数名 : NetcbbRouterAdvertiseStop
 *
 * 功能 : 停止路由通告功能
 *
 * 描述 :
 *
 * 参数说明 :
 *      pchIfaceName   - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...) *
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbRouterAdvertiseStop(char *pchIfaceName);

/************************************************************
 * 函数名 : NetcbbIfaceGetIp
 *
 * 功能 : 获取网卡参数
 *
 * 描述 :
 *
 * 参数说明 :
 *      pchIfaceName   - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *      wSinFamily     - 协议栈类型 :  NETCBB_PROTO_TYPE_IPV4
 *                                     NETCBB_PROTO_TYPE_IPV6
 *                                     NETCBB_PROTO_TYPE_ALL
 *      ptNetIfaceIp   - 地址以及掩码信息
 *
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 系统错误
 *          NETCBB_INVALID_PARAM - 网络参数无效
 ***********************************************************/
s32 NetcbbIfaceGetIp(char *pchIfaceName, u16 wSinFamily, TNetcbbIfaceAllIp *ptNetIfaceIp);

/************************************************************
 * 函数名 : NetcbbIfaceSetIp
 *
 * 功能 : 设置接口的ip地址
 *
 * 描述 :
 *        1.先清除pchIfaceName网口的wSinFamily协议栈地址，然后配置
 *          ptNetIfaceIp地址信息.
 *        2.如果设置的地址个数为0，则表示清除当前网口的wSinFamily协议栈地址
 *
 * 参数说明 :
 *      pchIfaceName     - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *      wSinFamily  - 协议栈类型 : NETCBB_PROTO_TYPE_IPV4
 *                                 NETCBB_PROTO_TYPE_IPV6
 *      ptNetIfaceParam  - IP地址和掩码
 *
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 系统错误
 *          NETCBB_INVALID_PARAM - 网络参数无效
 ***********************************************************/
s32 NetcbbIfaceSetIp(char *pchIfaceName, u16 wSinFamily, TNetcbbIfaceAllIp *ptNetIfaceIp);

/************************************************************
 * 函数名 : NetcbbIfaceFlushIp
 *
 * 功能 : 清除接口所有的IP
 *
 * 描述 :
 *
 * 参数说明 :
 *      pchIfaceName   - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *      wSinFamily  - 协议栈类型 :  NETCBB_PROTO_TYPE_IPV4
 *                                  NETCBB_PROTO_TYPE_IPV6
 *                                  NETCBB_PROTO_TYPE_ALL
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
 s32 NetcbbIfaceFlushIp(char *pchIfaceName, u16 wSinFamily);

/************************************************************
 * 函数名 : NetcbbIfaceAddIp
 *
 * 功能 : 增加指定IP地址
 *
 * 描述 :
 *      目前地址类型只支持NETCBB_SCOPE_TYPE_GLOBAL, 后续根据需求进行调整
 *
 * 参数说明 :
 *      pchIfaceName  - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *      ptNetIfaceIp  - 增加的指定IP结构体指针
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbIfaceAddIp(char *pchIfaceName, TNetcbbIfaceIp *ptNetIfaceIp);

/************************************************************
 * 函数名 : NetcbbIfaceDelIp
 *
 * 功能 : 删除指定IP地址
 *
 * 描述 :
 *      目前地址类型只支持NETCBB_SCOPE_TYPE_GLOBAL, 后续根据需求进行调整
 *
 * 参数说明 :
 *      pchIfaceName  - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *      ptNetIfaceIp  - 删除的指定IP结构体指针
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbIfaceDelIp(char *pchIfaceName, TNetcbbIfaceIp *ptNetIfaceIp);

/************************************************************
 * 函数名 : NetcbbIfaceSetMac
 *
 * 功能 : 设置接口MAC地址
 *
 * 描述 :
 *
 * 参数说明 :
 *      pchIfaceName  - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *      ptNetIfaceMac - 存放mac地址结构体指针
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbIfaceSetMac(char *pchIfaceName, TNetcbbIfaceMac *ptNetIfaceMac);

/************************************************************
 * 函数名 : NetcbbIfaceGetMac
 *
 * 功能 : 获取指定接口MAC地址
 *
 * 描述 :
 *
 * 参数说明 :
 *      pchIfaceName   - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *      ptNetIfaceMac  - 存放mac地址结构体指针
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbIfaceGetMac(char *pchIfaceName, TNetcbbIfaceMac *ptNetIfaceMac);

/************************************************************
 * 函数名 : NetcbbIfaceSetMtu
 *
 * 功能 : 设置某一网卡的MTU值
 *
 * 描述 :
 *
 * 参数说明 :
 *      pchIfaceName - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *      dwMtu        - 设置的MTU值
 *      wSinFamily  - 协议栈类型
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 *          NETCBB_IF_BUSY - 网卡正在使用中，设置失败
 ***********************************************************/
s32 NetcbbIfaceSetMtu(char *pchIfaceName, u16 wSinFamily, u32 dwMtu);

/************************************************************
 * 函数名 : NetcbbIfaceGetMtu
 *
 * 功能 : 获取某一网卡的MTU值
 *
 * 描述 :
 *
 * 参数说明 :
 *      pchIfaceName - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *      pdwMtu       - 存储mtu值的buffer指针
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbIfaceGetMtu(char *pchIfaceName, u32* pdwMtu);

/************************************************************
 * 函数名 : NetcbbSetDefGateway
 *
 * 功能 : 设置默认网关ip
 *
 * 描述 : 1.地址值为全0时，表示删除当前网关，但wSinFamily类型值必须
 *          填充为NETCBB_PROTO_TYPE_IPV4或者NETCBB_PROTO_TYPE_IPV6
 *        2.如果地址非0且pchInfaceName为NULL时，由系统自己匹配对应的网口设置网关。
 *        3.如果地址为0，且pchInfaceName为NULL时，则会删除对应协议族的所有网关。
 *
 * 参数说明 :
 *      pchIfaceName - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *      tGateWay     - 默认网关ip地址，长整型，网络序
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbSetDefGateway(char *pchIfaceName, TNetcbbAddr tGateWay);

/************************************************************
 * 函数名 : NetcbbGetDefGateway
 *
 * 功能 : 获取默认网关ip
 *
 * 描述 : 如果pchIfaceName为NULL, 则自动获取系统中的默认网关地址,
 *        如果系统中存在多个地址，则可能为其中任意一个默认网关地址.
 *
 * 参数说明 :
 *      pchIfaceName - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *      wSinFamily   - 协议栈类型 : NETCBB_PROTO_TYPE_IPV4
 *                                  NETCBB_PROTO_TYPE_IPV6
 *      ptGateWay    - 默认网关ip地址
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbGetDefGateway(char *pchIfaceName, u16 wSinFamily, TNetcbbAddr *ptGateWay);

/************************************************************
 * 函数名 : NetcbbDelDefGateway
 *
 * 功能 : 删除默认网关ip
 *
 * 描述 :
 *        1.如果pchIfaceName传入NULL, 则删除系统中所有的wSinFamily协议族网关。
 *
 *
 * 参数说明 :
 *      pchIfaceName - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *      wSinFamily  - 协议栈类型 :  NETCBB_PROTO_TYPE_IPV4
 *                                  NETCBB_PROTO_TYPE_IPV6
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbDelDefGateway(char *pchIfaceName, u16 wSinFamily);

/************************************************************
 * 函数名 : NetcbbAddOneIpRoute
 *
 * 功能 : 增加一条路由
 *
 * 描述 :
 *      ptNetIpRouteParam->achIfaceName如果为全0时，由系统自己设置路由
 *      配置的接口(如eth0或者eth1)
 *
 *
 * 参数说明 :
 *      ptNetIpRouteParam - 指向存放路由信息的TNetIpRouteParam结构指针
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbAddOneIpRoute(TNetcbbIpRouteParam *ptNetIpRouteParam);

/************************************************************
 * 函数名 : NetcbbDelOneIpRoute
 *
 * 功能 : 删除一条路由
 *
 * 描述 :
 *      ptNetIpRouteParam->achIfaceName如果为全0时，由系统自己设置路由
 *      配置的接口(如eth0或者eth1)
 *
 * 参数说明 :
 *      ptNetIpRouteParam    - 指向存放路由信息的TNetIpRouteParam结构指针
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbDelOneIpRoute(TNetcbbIpRouteParam *ptNetIpRouteParam);

/************************************************************
 * 函数名 : NetcbbGetAllIpRoute
 *
 * 功能 : 读取所有路由信息
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      wSinFamily  - 协议栈类型 :  NETCBB_PROTO_TYPE_IPV4
 *                                  NETCBB_PROTO_TYPE_IPV6
 *                                  NETCBB_PROTO_TYPE_ALL
 *      ptNetIpRouteParam    - 指向存放路由信息的TNetIpRouteParam结构指针
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbGetAllIpRoute(u16 wSinFamily, TNetcbbAllIpRouteInfo *ptNetAllIpRouteInfo);

/************************************************************
 * 函数名 : NetcbbModifyIpRouteMetric
 *
 * 功能 : 修改一条路由的metric
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      ptNetIpRouteParam    - 指向存放路由信息的TNetIpRouteParam结构指针
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbModifyIpRouteMetric(TNetcbbIpRouteParam *ptNetIpRouteParam);

/************************************************************
 * 函数名 : NetIpConflictCallBackReg
 *
 * 功能 : 注册ip地址冲突时回调函数,当设备的IP地址和外部设备冲
 *        突时，会调用该函数通知业务程序
 *
 * 描述 :
 *        1.ipv6冲突检测暂不支持。
 *
 *
 * 参数说明 :
 *      wSinFamily  - 协议栈类型 :  NETCBB_PROTO_TYPE_IPV4
 *                                  NETCBB_PROTO_TYPE_IPV6
 *      ptFunc    - 执行业务程序注册的回调函数指针
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbIpConflictCheckStart(u16 wSinFamily, TNetcbbConflictCallBack ptFunc);

/************************************************************
 * 函数名 : NetIpConflictCallBackReg
 *
 * 功能 : 注册ip地址冲突时回调函数,当设备的IP地址和外部设备冲
 *        突时，会调用该函数通知业务程序
 *
 * 描述 :
 *        1.ipv6冲突检测暂不支持。
 *
 *
 * 参数说明 :
 *      wSinFamily  - 协议栈类型 :  NETCBB_PROTO_TYPE_IPV4
 *                                  NETCBB_PROTO_TYPE_IPV6
 *      ptFunc    - 执行业务程序注册的回调函数指针
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbIpConflictCheckStop(u16 wSinFamily);

/************************************************************
 * 函数名 : NetcbbSetDscp
 *
 * 功能 : 设置ip包头dscp值(0-63)
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      nSockfd    - 要设置的套接字描述符
 *      byDscp     - 要设置的dscp值(0-63)
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbSetDscp(u16 wSinFamily, s32 nSockfd, u8 byDscp);

/************************************************************
 * 函数名 : NetCheckTheSameNet
 *
 * 功能 : 校验ip和网关是否在同一网段
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      tIpAddr  - ip地址
 *      dwPrefix - 掩码前缀
 *      tGateway - 网关
 *
 * 返回值 : NETCBB_OK    - 校验成功, 在同一个网段
 *          NETCBB_NOT_THE_SAME_NET  - 不在同一个网段
 *          NETCBB_INVALID_PARAM - 参数本身错误
 ***********************************************************/
s32 NetcbbCheckIsSameNet(TNetcbbAddr tIpAddr, u32 dwPrefix, TNetcbbAddr tGateway);

/************************************************************
 * 函数名 : NetcbbIfaceShutdown
 *
 * 功能 : 关闭网卡
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      pchIfaceName - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbIfaceShutdown(char *pchIfaceName);

/************************************************************
 * 函数名 : NetcbbIfaceNoShutdown
 *
 * 功能 : 打开网卡
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      pchIfaceName - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbIfaceNoShutdown(char *pchIfaceName);

/************************************************************
 * 函数名 : NetGetEthState
 *
 * 功能 : 获取网卡状态
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      pchIfaceName - 网卡名字(支持"ethX", "wlanX", "bondX", "pppX"名字，X为0,1,2...)
 *      pdwFlag  - 网卡状态：NETCBB_IF_UP     网卡up
 *                           NETCBB_IF_DOWN   网卡down
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbGetIfaceState(char *pchIfaceName, u32* pdwFlag);

/************************************************************
 * 函数名 : NetcbbStatCallBackRegister
 *
 * 功能 : 注册设备统计值回调函数
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      nInterval  - 回调间隔，同时根据此间隔计算发送以及接收的间隔.
 *      pfNotifyCb - 回调通知函数.
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetcbbStatNotifyCallbackReg(int nInterval, TDevStatNotifyCallBack pfNotifyCb);

/************************************************************
 * 函数名 : NetcbbStatStop
 *
 * 功能 : 关闭注册设备统计值
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *     		无
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetcbbStatStop(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_INTERFACE_H_ */
