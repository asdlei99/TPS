#ifndef _NETCBB_SERV_1X_H
#define _NETCBB_SERV_1X_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "netcbb_serv.h"


#define NETSERVICE_TELNETD  NETCBB_SERVICE_TELNETD /* 宏定义telnetd */
#define NETSERVICE_SSH      NETCBB_SERVICE_SSH     /* 宏定义ssh */
#define NETSERVICE_FTPD     NETCBB_SERVICE_FTPD    /* 宏定义ftpd */
#define NETSERVICE_TFTPD    NETCBB_SERVICE_TFTPD   /* 宏定义tftpd */
#define NETSERVICE_HTTPD    NETCBB_SERVICE_HTTPD   /* 宏定义httpd */

#define NETPROTO_TCP         NETCBB_TPROTO_TCP
#define NETPROTO_UDP         NETCBB_TPROTO_UDP



typedef struct {
    s8  *pchServName;   /* 服务名 */
    u16  wPort;         /* 服务端口号 */
    s8  *pchProto;      /* 协议类型 */
    s8  *pchArgPath;
}TServInfo;


/************************************************************
 * 函数名 : NetServiceStart
 *
 * 功能 : 开启服务功能
 *
 * 描述 :
 *
 * 参数说明 :
 *      pchServName - 服务名
 *      ptParaM     - 指向TServInfo 的结构体指针
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetServiceStart(s8 *pchServName, TServInfo* ptParaM);

/************************************************************
 * 函数名 : NetServiceStop
 *
 * 功能 : 关闭服务功能
 *
 * 描述 :
 *
 * 参数说明 :
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetServiceStop(s8* pchServName, u16 wPort);

/************************************************************
 * 函数名 : NetModifyNetPwd
 *
 * 功能 : 设置网络基础协议密码 (涉及到协议有ftp telnet ssh)
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      pUser    - 用户名 *      pPasswd  - 用户设置密码
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetModifyNetPwd(s8* pUser, s8* pPasswd);

/************************************************************
 * 函数名 : NetAddNetUser
 *
 * 功能 : 增加用户(涉及到协议有ftp telnet ssh)
 *
 * 描述 :
 *     调用此函数增加的为管理员用户
 *
 * 参数说明 :
 *      pUser    - 用户名
 *      pPasswd  - 用户设置密码
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetAddNetUser(s8* pUser, s8* pPasswd);

/************************************************************
 * 函数名 : NetAddNetCommonUser
 *
 * 功能 : 增加用户(涉及到协议有ftp telnet ssh)
 *
 * 描述 :
 *     调用此函数增加的为普通用户
 *
 * 参数说明 :
 *      pUser    - 用户名
 *      pPasswd  - 用户设置密码
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetAddNetCommonUser(s8* pUser, s8* pPasswd);

/************************************************************
 * 函数名 : NetDelNetUser
 *
 * 功能 : 删除用户(涉及到协议有ftp telnet ssh)
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      pUser    - 用户名
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetDelNetUser(s8* pUser);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
