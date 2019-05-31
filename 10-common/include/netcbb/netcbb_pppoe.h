#ifndef _NETCBB_PPPOE_H_
#define _NETCBB_PPPOE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define NETCBB_USERNAME_LEN     255
#define NETCBB_PASSWORD_LEN     255
#define NETCBB_SERVNAME_LEN     255

/* pppoe���Żص���ϢID */
#define NETCBB_PPPOE_MSG_SUCC   		    1  /* ���ųɹ� */
#define NETCBB_PPPOE_MSG_DIALING		    2  /* ���ڲ��� */
#define NETCBB_PPPOE_MSG_DIAL_TIMEOUT		3  /* ���ų�ʱ */
#define NETCBB_PPPOE_MSG_AUTH_FAILED		4  /* ��֤ʧ�� */
#define NETCBB_PPPOE_MSG_DOWN		        5  /* pppoe����ر� */

typedef struct NetcbbPppoeParam{
	char      achUserName[NETCBB_USERNAME_LEN];   /* ����ʱʹ�õ��û���,������ */
	char      achPassword[NETCBB_PASSWORD_LEN];   /* ����ʱʹ�õ�����,������ */
	char      achServerName[NETCBB_SERVNAME_LEN]; /* ָ�����ŷ����̵�����,���Բ��� */
	char      achDevName[NETCBB_IFACE_NAME_LEN];      /* ������Ҫ�󶨵�����ӿ����֣���"eth0" */
	BOOL32    bAutoDialEnable;      /* �Ƿ�����������Զ�����,Ĭ�ϲ��Զ�����,ֻ�������Զ����ź��ز��������ز�ʱ��������塣������Ч */
	BOOL32    bDefaultRouteEnable;  /* �Ƿ������Զ˵ĵ�ַ��ΪĬ�����أ�Ĭ�ϲ���Ϊ���� */
	BOOL32    bDebug;               /* �Ƿ���debugģʽ����pppoe��Ĭ�ϲ�������debugģʽ */
	u32       dwAutoDialInterval;   /* �������ٴ��Զ�������Ҫ�ȴ���ʱ�䣨�������ó�0s��*/
	u16       wDialRetryTimes;      /* ���ų��ԵĴ���������ﵽ�ô�����û����Ӧ�򲦺�ʧ��,Ĭ��Ϊ10��Ϊ0�������Ʋ��� */
	u16       wLcpEchoSendInterval; /* ���ӽ����󣬷���LCP-ECHO����ʱ����,Ĭ������Ϊ20����ȡֵ1~255 */
	u16       wLcpEchoRetryTimes;   /* ���ͼ���LCP-ECHO��û�еõ���Ӧ����Ϊ���ӶϿ�,Ĭ������Ϊ3 */
}TNetcbbPppoeParam;

typedef struct NetcbbPppoeStates{
	BOOL32  bPppoeRunning;                          /* PPPOE�Ƿ����У�TRUR�����У�FALSE��û������ */
	TNetcbbAddr tOurIpaddr;                         /* ���ϻ�õ�IP��ַ,������ */
	TNetcbbAddr tPeerIpAddr;                        /* �Զ˵�IP��ַ */
	char    achServerName[NETCBB_SERVNAME_LEN]; /* ISP Server������ */
	u32     dwLinkKeepTimes;                        /* ��·������ʱ�� */
	u32     dwLinkDownTimes;                        /* ��·�����Ĵ���ͳ�� */
	u32     dwPktsSend;                             /* �ܹ����͵����ݰ���--��������Э����Լ��ϲ�ҵ���������ݰ� */
	u32     dwPktsRecv;                             /* �ܹ����յ����ݰ��� */
	u32     dwBytesSend;                            /* �ܹ����͵��ֽ��� */
	u32     dwBytesRecv;                            /* �ܹ����յ��ֽ��� */
}TNetcbbPppoeStates;

/* �����ϲ�ҵ�����ע��Ļص��������ͽ���֪ͨ��Ϣ�Ľṹ��
 * ��ӦNETCBB_PPPOE_SUCC��Ϣ
 */
typedef struct NetcbbPppoeAddr{
	TNetcbbAddr tOurIpaddr;  /* ���ϻ�õ�IP��ַ,������ */
	TNetcbbAddr tPeerIpAddr; /* �Զ˵�IP��ַ */
	TNetcbbAddr tDnsServer1; /* DNS Server1,������ */
	TNetcbbAddr tDnsServer2; /* DNS Server1,������ */
}TNetcbbPppoeAddr;

/* ֪ͨҵ������Ҳ���ָ����ISP Server����Ϣ�ṹ�� */
typedef struct NoServer{
    char  achServerName[NETCBB_SERVNAME_LEN]; /* ISP Server������ */
}TNoServer;

/*�洢PPPOE�汾��Ϣ�Ľṹ��*/
typedef struct Version{
    char  achVersion[NETCBB_VERSION_LEN];
}TNetcbbVersion;

/************************************************************
 * ������ : TNetcbbPppoeCallBack
 *
 * ���� : �ص�pppoe���Ž��
 *
 * ���� :
 *       1.�˺�������Ӧ������̣��õ�״̬�󣬿���״̬�Լ���ַ��,
 *         �����Ϸ��ء�
 *       2.�����ڻص�������ʹ�������ź����ȣ������׵���������
 *
 * ����˵�� :
 *       dwMsgID   - ��Ϣ��ID�ţ���NETCBB_PPPOE_SUCC��
 *       msg       - ָ����Ϣ���ݵ�ָ��,��PPPOEģ�����
 *       dwMsgLen  - ��Ϣ���ݵ���Ч����,��PPPOEģ�����
 *
 * ����ֵ : oK - �ɹ�
 *          NETCBB_ERROR - ʧ��
 *          �ο�netcbb_def.h
 ***********************************************************/
typedef void (*TNetcbbPppoeCallBack)(u32 dwMsgID, void* msg, u32 dwMsgLen);

/************************************************************
 * ������ : NetcbbPppoeStart
 *
 * ���� : ����PPPoE����
 *
 * ���� : ��ʱ���ṩ֧�ֶ�������������֧�ֶ����������뵥��
 *        ������ʵ��
 *
 * ����˵�� :
 *       ptPppoeParam     - pppoe��������Ҫ�Ĳ���
 *       wSinFamily       - Э��ջ���� :  NETCBB_PROTO_TYPE_IPV4
 *                                      NETCBB_PROTO_TYPE_IPV6
 *       ptNotifyCallBack - pppoe�ص�֪ͨ����
 *
 * ����ֵ : NETCBB_OK
 *          NETCBB_ERROR
 *          �����ο�netcbb_def.h
 ***********************************************************/
s32 NetcbbPppoeStart(TNetcbbPppoeParam* ptPppoeParam, u16 wSinFamily, TNetcbbPppoeCallBack ptNotifyCallBack);

/************************************************************
 * ������ : NetcbbPppoeStop
 *
 * ���� : ֹͣPPPoE����
 *
 * ���� :

 *
 * ����˵�� :
 *      pchIfaceName   - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *      wSinFamily     - Э��ջ���� :  NETCBB_PROTO_TYPE_IPV4
 *                                     NETCBB_PROTO_TYPE_IPV6
 *
 * ����ֵ : NETCBB_OK
 *          NETCBB_ERROR
 *          �����ο�netcbb_def.h
 ***********************************************************/
s32 NetcbbPppoeStop(char *pchIfaceName, u16 wSinFamily);

/************************************************************
 * ������ : NetcbbPppoeStatesDump
 *
 * ���� : ��ȡPPPoEģ���ͳ����Ϣ
 *
 * ���� : ��ʱ���ṩ֧��
 *
 * ����˵�� :
 *      ptPppoeStates - ָ����ͳ�ƽ����ָ��
 *
 * ����ֵ : ��
 ***********************************************************/
void NetcbbPppoeStatesDump(TNetcbbPppoeStates* ptPppoeStates);

/************************************************************
 * ������ : NetcbbPppoeVer
 *
 * ���� : ��ȡPPPoEģ��İ汾��Ϣ
 *
 * ���� :
 *
 * ����˵�� :
 *      ptVersion - ָ���Ű汾��Ϣ��ָ��
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ʧ��
 ***********************************************************/
s32 NetcbbPppoeVer(TNetcbbVersion* ptVersion);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_PPPOE_H_ */

