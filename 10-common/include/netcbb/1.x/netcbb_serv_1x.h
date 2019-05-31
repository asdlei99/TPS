#ifndef _NETCBB_SERV_1X_H
#define _NETCBB_SERV_1X_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "netcbb_serv.h"


#define NETSERVICE_TELNETD  NETCBB_SERVICE_TELNETD /* �궨��telnetd */
#define NETSERVICE_SSH      NETCBB_SERVICE_SSH     /* �궨��ssh */
#define NETSERVICE_FTPD     NETCBB_SERVICE_FTPD    /* �궨��ftpd */
#define NETSERVICE_TFTPD    NETCBB_SERVICE_TFTPD   /* �궨��tftpd */
#define NETSERVICE_HTTPD    NETCBB_SERVICE_HTTPD   /* �궨��httpd */

#define NETPROTO_TCP         NETCBB_TPROTO_TCP
#define NETPROTO_UDP         NETCBB_TPROTO_UDP



typedef struct {
    s8  *pchServName;   /* ������ */
    u16  wPort;         /* ����˿ں� */
    s8  *pchProto;      /* Э������ */
    s8  *pchArgPath;
}TServInfo;


/************************************************************
 * ������ : NetServiceStart
 *
 * ���� : ����������
 *
 * ���� :
 *
 * ����˵�� :
 *      pchServName - ������
 *      ptParaM     - ָ��TServInfo �Ľṹ��ָ��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetServiceStart(s8 *pchServName, TServInfo* ptParaM);

/************************************************************
 * ������ : NetServiceStop
 *
 * ���� : �رշ�����
 *
 * ���� :
 *
 * ����˵�� :
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetServiceStop(s8* pchServName, u16 wPort);

/************************************************************
 * ������ : NetModifyNetPwd
 *
 * ���� : �����������Э������ (�漰��Э����ftp telnet ssh)
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      pUser    - �û��� *      pPasswd  - �û���������
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetModifyNetPwd(s8* pUser, s8* pPasswd);

/************************************************************
 * ������ : NetAddNetUser
 *
 * ���� : �����û�(�漰��Э����ftp telnet ssh)
 *
 * ���� :
 *     ���ô˺������ӵ�Ϊ����Ա�û�
 *
 * ����˵�� :
 *      pUser    - �û���
 *      pPasswd  - �û���������
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetAddNetUser(s8* pUser, s8* pPasswd);

/************************************************************
 * ������ : NetAddNetCommonUser
 *
 * ���� : �����û�(�漰��Э����ftp telnet ssh)
 *
 * ���� :
 *     ���ô˺������ӵ�Ϊ��ͨ�û�
 *
 * ����˵�� :
 *      pUser    - �û���
 *      pPasswd  - �û���������
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetAddNetCommonUser(s8* pUser, s8* pPasswd);

/************************************************************
 * ������ : NetDelNetUser
 *
 * ���� : ɾ���û�(�漰��Э����ftp telnet ssh)
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      pUser    - �û���
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetDelNetUser(s8* pUser);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
