#ifndef _NETCBB_SERV_H
#define _NETCBB_SERV_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define NETCBB_SERVICE_TELNETD  "telnetd" /* 宏定义telnetd */
#define NETCBB_SERVICE_SSH      "ssh"     /* 宏定义ssh */
#define NETCBB_SERVICE_FTPD     "ftpd"    /* 宏定义ftpd */
#define NETCBB_SERVICE_TFTPD    "tftpd"   /* 宏定义tftpd */
#define NETCBB_SERVICE_HTTPD    "httpd"   /* 宏定义httpd */

#define NETCBB_TPROTO_TCP	"tcp"		/* only support ipv4 */
#define NETCBB_TPROTO_UDP	"udp"		/* only support ipv4 */
#define NETCBB_TPROTO_TCP_V6	"tcp6"		/* support ipv4&6 */
#define NETCBB_TPROTO_UDP_V6	"udp6"		/* support ipv4&6 */




typedef struct {
    char  *pchServerName;   /* 服务名 */
    u16    wPort;           /* 服务端口号 */
    char  *pchProto;        /* 协议类型 */
    char  *pchArgPath;
}TNetcbbServInfo;

#ifdef NETCBBS_OS_ANDROID
/* The service name below defined according to 'netstat -tap' */
#define NETSERVICE_TELNETD  "telnet"
#define NETSERVICE_FTPD     "ftp"
#define NETSERVICE_HTTPD    "webcache"

/* The service name below defined according to inetd.conf */
#define NET_TELNETD_CONF    "telnetd"
#define NET_FTPD_CONF       "ftpd"
#define NET_HTTPD_CONF      "httpd"

#define INETD_CONF_PATH     "/etc/inetd.conf"


/************************************************************
 * 函数名 : NetServiceFtpStart
 *
 * 功能 : 开启ftp服务
 *
 * 描述 :
 *
 * 参数说明 :
 *
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetServiceFtpStart();

/************************************************************
 * 函数名 : NetServiceFtpStop
 *
 * 功能 : 关闭ftp功能
 *
 * 描述 :
 *
 * 参数说明 :
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetServiceFtpStop();

/************************************************************
 * 函数名 : NetServiceTelnetStart
 *
 * 功能 : 开启telnet服务
 *
 * 描述 :
 *
 * 参数说明 :
 *
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetServiceTelnetStart();

/************************************************************
 * 函数名 : NetServiceTelnetStart
 *
 * 功能 : 关闭telnet服务
 *
 * 描述 :
 *
 * 参数说明 :
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetServiceTelnetStop();

/************************************************************
 * 函数名 : NetServiceHttpStart
 *
 * 功能 : 开启http服务
 *
 * 描述 :
 *
 * 参数说明 :
 *
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetServiceHttpStart();

/************************************************************
 * 函数名 : NetServiceHttpStop
 *
 * 功能 : 关闭http服务
 *
 * 描述 :
 *
 * 参数说明 :
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetServiceHttpStop();

#endif
/************************************************************
 * 函数名 : NetcbbServiceStart
 *
 * 功能 : 开启服务功能
 *
 * 描述 :
 *
 * 参数说明 :
 *      pchServName - 服务名
 *      ptParaM     - 指向TServInfo 的结构体指针
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbServiceStart(TNetcbbServInfo* ptServerInfo);

/************************************************************
 * 函数名 : NetcbbServiceStop
 *
 * 功能 : 关闭服务功能
 *
 * 描述 :
 *
 * 参数说明 :
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbServiceStop(char* pchServerName);

/************************************************************
 * 函数名 : NetcbbModifyNetPwd
 *
 * 功能 : 设置网络基础协议密码 (涉及到协议有ftp telnet ssh)
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      pUser    - 用户名
 *      pPasswd  - 用户设置密码
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbModifyNetPwd(char* pchUser, char* pchPasswd);

/************************************************************
 * 函数名 : NetcbbAddNetUser
 *
 * 功能 : 增加用户(涉及到协议有ftp telnet ssh)
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      pUser    - 用户名
 *      pPasswd  - 用户设置密码
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbAddNetUser(char *pchUser, char *pchPasswd);

/************************************************************
 * 函数名 : NetcbbDelNetUser
 *
 * 功能 : 删除用户(涉及到协议有ftp telnet ssh)
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      pUser    - 用户名
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/
s32 NetcbbDelNetUser(char *pchUser);

/************************************************************
 * 函数名 : NetcbbAddNetCommonUser
 *
 * 功能 : 添加普通用户(涉及到协议有ftp telnet ssh)
 *
 * 描述 :
 *
 *
 * 参数说明 :
 *      pUser    - 用户名
 *
 * 返回值 : NETCBB_OK    - 成功
 *          NETCBB_ERROR - 错误
 ***********************************************************/

s32 NetcbbAddNetCommonUser(char *pchUser, char *pchPasswd);




#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
