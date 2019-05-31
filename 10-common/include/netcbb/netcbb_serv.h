#ifndef _NETCBB_SERV_H
#define _NETCBB_SERV_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define NETCBB_SERVICE_TELNETD  "telnetd" /* �궨��telnetd */
#define NETCBB_SERVICE_SSH      "ssh"     /* �궨��ssh */
#define NETCBB_SERVICE_FTPD     "ftpd"    /* �궨��ftpd */
#define NETCBB_SERVICE_TFTPD    "tftpd"   /* �궨��tftpd */
#define NETCBB_SERVICE_HTTPD    "httpd"   /* �궨��httpd */

#define NETCBB_TPROTO_TCP	"tcp"		/* only support ipv4 */
#define NETCBB_TPROTO_UDP	"udp"		/* only support ipv4 */
#define NETCBB_TPROTO_TCP_V6	"tcp6"		/* support ipv4&6 */
#define NETCBB_TPROTO_UDP_V6	"udp6"		/* support ipv4&6 */




typedef struct {
    char  *pchServerName;   /* ������ */
    u16    wPort;           /* ����˿ں� */
    char  *pchProto;        /* Э������ */
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
 * ������ : NetServiceFtpStart
 *
 * ���� : ����ftp����
 *
 * ���� :
 *
 * ����˵�� :
 *
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetServiceFtpStart();

/************************************************************
 * ������ : NetServiceFtpStop
 *
 * ���� : �ر�ftp����
 *
 * ���� :
 *
 * ����˵�� :
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetServiceFtpStop();

/************************************************************
 * ������ : NetServiceTelnetStart
 *
 * ���� : ����telnet����
 *
 * ���� :
 *
 * ����˵�� :
 *
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetServiceTelnetStart();

/************************************************************
 * ������ : NetServiceTelnetStart
 *
 * ���� : �ر�telnet����
 *
 * ���� :
 *
 * ����˵�� :
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetServiceTelnetStop();

/************************************************************
 * ������ : NetServiceHttpStart
 *
 * ���� : ����http����
 *
 * ���� :
 *
 * ����˵�� :
 *
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetServiceHttpStart();

/************************************************************
 * ������ : NetServiceHttpStop
 *
 * ���� : �ر�http����
 *
 * ���� :
 *
 * ����˵�� :
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetServiceHttpStop();

#endif
/************************************************************
 * ������ : NetcbbServiceStart
 *
 * ���� : ����������
 *
 * ���� :
 *
 * ����˵�� :
 *      pchServName - ������
 *      ptParaM     - ָ��TServInfo �Ľṹ��ָ��
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbServiceStart(TNetcbbServInfo* ptServerInfo);

/************************************************************
 * ������ : NetcbbServiceStop
 *
 * ���� : �رշ�����
 *
 * ���� :
 *
 * ����˵�� :
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbServiceStop(char* pchServerName);

/************************************************************
 * ������ : NetcbbModifyNetPwd
 *
 * ���� : �����������Э������ (�漰��Э����ftp telnet ssh)
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      pUser    - �û���
 *      pPasswd  - �û���������
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbModifyNetPwd(char* pchUser, char* pchPasswd);

/************************************************************
 * ������ : NetcbbAddNetUser
 *
 * ���� : �����û�(�漰��Э����ftp telnet ssh)
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      pUser    - �û���
 *      pPasswd  - �û���������
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbAddNetUser(char *pchUser, char *pchPasswd);

/************************************************************
 * ������ : NetcbbDelNetUser
 *
 * ���� : ɾ���û�(�漰��Э����ftp telnet ssh)
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      pUser    - �û���
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbDelNetUser(char *pchUser);

/************************************************************
 * ������ : NetcbbAddNetCommonUser
 *
 * ���� : �����ͨ�û�(�漰��Э����ftp telnet ssh)
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      pUser    - �û���
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/

s32 NetcbbAddNetCommonUser(char *pchUser, char *pchPasswd);




#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
