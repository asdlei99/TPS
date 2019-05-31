#ifndef _NETCBB_INTERFACE_H_
#define _NETCBB_INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "netcbb_def.h"
#include "netcbb_e1.h"

/* ��·�ӿڲ����ṹ */
typedef struct{
    u32 dwIpNum; /* ��Ч��IP��ַ�� */
    TNetcbbIfaceIp atNetIfaceIp[NETCBB_IP_MAX_NUM];  /* ���IP��ַ����Ϣ������ */
}TNetcbbIfaceAllIp;

/* ��·�ӿ�mac��ַ�ṹ */
typedef struct{
	u8 abyMacAddr[NETCBB_MAC_LEN];
}TNetcbbIfaceMac;

/* ����·�ɲ����ṹ */
typedef struct{
	char achIfaceName[NETCBB_IFACE_NAME_LEN]; /* �ӿ�����, ��"eth0" */
	TNetcbbAddr tDestIpNet;    /* Ŀ�������������ֽ��� */
	TNetcbbAddr tDestGateWay;  /* ����ip��ַ�������ֽ��� */
	u32 dwPrefix;         /* ���룬�����ֽ��� */
	u32 dwRoutePri;       /* ·�����ȼ�(1-255)��Ĭ��Ϊ0 */
}TNetcbbIpRouteParam;

/* ���·�ɲ����ṹ */
typedef struct{
	u32 dwIpRouteNum;    /* �õ���ʵ��·�ɸ��� */
	TNetcbbIpRouteParam tNetIpRouteParam[NETCBB_ROUTE_MAX_NUM];
}TNetcbbAllIpRouteInfo;

/* ·��ͨ��ص��ṹ��, ֻ����ipv6 */
typedef struct{
	char achIfaceName[NETCBB_IFACE_NAME_LEN]; /* �ӿ�����, ��"eth0" */
	TNetcbbIfaceAllIp tNetIfaceAllIp;         /* �ӿ����е�Ipv6��ַ��Ϣ */
}TNetcbbRouterAdCb;

typedef enum IP_CONFLICT_TYPE{
	NETCBB_IP_CONFLICT = 1,
	NETCBB_MAC_CONFLICT = 2,
}ENetcbbConflictType;

/* ����ͳ����Ϣ */
typedef struct{
	u32 byEthId;
	u64 dwBandSended; /* (bit/s) 1Gbit/s == 1000Mbit/s == 1000*1000kbit/s == 1000*1000*1000 bit/s */
	u64 dwBandRecved; /* (bit/s) */
}TNetDevStat;

/* IP��ַ��ͻ�ص��������Ͷ��� */
typedef void (*TNetcbbConflictCallBack)(ENetcbbConflictType eType, TNetcbbIfaceMac *ptIfaceMac, TNetcbbAddr *ptIpAddr);

/* ·��ͨ�溯�� */
typedef void (*TNetcbbRouterAdvertiseCallBack)(TNetcbbRouterAdCb *ptCbInfo);

/* ����ͳ��֪ͨ���� */
typedef void (*TDevStatNotifyCallBack)(TNetDevStat aptdevStat[], u32 dwEthNum);

/************************************************************
 * ������ : NetcbbRouterAdvertiseStart
 *
 * ���� : ����·��ͨ�湦�ܡ�
 *
 * ���� :
 *       1.����·��ͨ�湦�ܣ�ע��·��ͨ��ص�������
 *         �˹���ֻ��ipv6Э��ջ����·��ͨ���ַʹ�á�
 *       2.�˺�������Ӧ������̣��õ�״̬�󣬿���״̬��,
 *         �����Ϸ��ء�
 *       3.�����ڻص�������ʹ�������ź����ȣ������׵���������
 *
 * ����˵�� :
 *      pchIfaceName   - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *      pfRACallback   - ·��ͨ��ص�����
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbRouterAdvertiseStart(char *pchIfaceName, TNetcbbRouterAdvertiseCallBack pfRACallback);

/************************************************************
 * ������ : NetcbbRouterAdvertiseStop
 *
 * ���� : ֹͣ·��ͨ�湦��
 *
 * ���� :
 *
 * ����˵�� :
 *      pchIfaceName   - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...) *
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbRouterAdvertiseStop(char *pchIfaceName);

/************************************************************
 * ������ : NetcbbIfaceGetIp
 *
 * ���� : ��ȡ��������
 *
 * ���� :
 *
 * ����˵�� :
 *      pchIfaceName   - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *      wSinFamily     - Э��ջ���� :  NETCBB_PROTO_TYPE_IPV4
 *                                     NETCBB_PROTO_TYPE_IPV6
 *                                     NETCBB_PROTO_TYPE_ALL
 *      ptNetIfaceIp   - ��ַ�Լ�������Ϣ
 *
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ϵͳ����
 *          NETCBB_INVALID_PARAM - ���������Ч
 ***********************************************************/
s32 NetcbbIfaceGetIp(char *pchIfaceName, u16 wSinFamily, TNetcbbIfaceAllIp *ptNetIfaceIp);

/************************************************************
 * ������ : NetcbbIfaceSetIp
 *
 * ���� : ���ýӿڵ�ip��ַ
 *
 * ���� :
 *        1.�����pchIfaceName���ڵ�wSinFamilyЭ��ջ��ַ��Ȼ������
 *          ptNetIfaceIp��ַ��Ϣ.
 *        2.������õĵ�ַ����Ϊ0�����ʾ�����ǰ���ڵ�wSinFamilyЭ��ջ��ַ
 *
 * ����˵�� :
 *      pchIfaceName     - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *      wSinFamily  - Э��ջ���� : NETCBB_PROTO_TYPE_IPV4
 *                                 NETCBB_PROTO_TYPE_IPV6
 *      ptNetIfaceParam  - IP��ַ������
 *
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ϵͳ����
 *          NETCBB_INVALID_PARAM - ���������Ч
 ***********************************************************/
s32 NetcbbIfaceSetIp(char *pchIfaceName, u16 wSinFamily, TNetcbbIfaceAllIp *ptNetIfaceIp);

/************************************************************
 * ������ : NetcbbIfaceFlushIp
 *
 * ���� : ����ӿ����е�IP
 *
 * ���� :
 *
 * ����˵�� :
 *      pchIfaceName   - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *      wSinFamily  - Э��ջ���� :  NETCBB_PROTO_TYPE_IPV4
 *                                  NETCBB_PROTO_TYPE_IPV6
 *                                  NETCBB_PROTO_TYPE_ALL
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
 s32 NetcbbIfaceFlushIp(char *pchIfaceName, u16 wSinFamily);

/************************************************************
 * ������ : NetcbbIfaceAddIp
 *
 * ���� : ����ָ��IP��ַ
 *
 * ���� :
 *      Ŀǰ��ַ����ֻ֧��NETCBB_SCOPE_TYPE_GLOBAL, ��������������е���
 *
 * ����˵�� :
 *      pchIfaceName  - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *      ptNetIfaceIp  - ���ӵ�ָ��IP�ṹ��ָ��
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbIfaceAddIp(char *pchIfaceName, TNetcbbIfaceIp *ptNetIfaceIp);

/************************************************************
 * ������ : NetcbbIfaceDelIp
 *
 * ���� : ɾ��ָ��IP��ַ
 *
 * ���� :
 *      Ŀǰ��ַ����ֻ֧��NETCBB_SCOPE_TYPE_GLOBAL, ��������������е���
 *
 * ����˵�� :
 *      pchIfaceName  - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *      ptNetIfaceIp  - ɾ����ָ��IP�ṹ��ָ��
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbIfaceDelIp(char *pchIfaceName, TNetcbbIfaceIp *ptNetIfaceIp);

/************************************************************
 * ������ : NetcbbIfaceSetMac
 *
 * ���� : ���ýӿ�MAC��ַ
 *
 * ���� :
 *
 * ����˵�� :
 *      pchIfaceName  - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *      ptNetIfaceMac - ���mac��ַ�ṹ��ָ��
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbIfaceSetMac(char *pchIfaceName, TNetcbbIfaceMac *ptNetIfaceMac);

/************************************************************
 * ������ : NetcbbIfaceGetMac
 *
 * ���� : ��ȡָ���ӿ�MAC��ַ
 *
 * ���� :
 *
 * ����˵�� :
 *      pchIfaceName   - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *      ptNetIfaceMac  - ���mac��ַ�ṹ��ָ��
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbIfaceGetMac(char *pchIfaceName, TNetcbbIfaceMac *ptNetIfaceMac);

/************************************************************
 * ������ : NetcbbIfaceSetMtu
 *
 * ���� : ����ĳһ������MTUֵ
 *
 * ���� :
 *
 * ����˵�� :
 *      pchIfaceName - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *      dwMtu        - ���õ�MTUֵ
 *      wSinFamily  - Э��ջ����
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 *          NETCBB_IF_BUSY - ��������ʹ���У�����ʧ��
 ***********************************************************/
s32 NetcbbIfaceSetMtu(char *pchIfaceName, u16 wSinFamily, u32 dwMtu);

/************************************************************
 * ������ : NetcbbIfaceGetMtu
 *
 * ���� : ��ȡĳһ������MTUֵ
 *
 * ���� :
 *
 * ����˵�� :
 *      pchIfaceName - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *      pdwMtu       - �洢mtuֵ��bufferָ��
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbIfaceGetMtu(char *pchIfaceName, u32* pdwMtu);

/************************************************************
 * ������ : NetcbbSetDefGateway
 *
 * ���� : ����Ĭ������ip
 *
 * ���� : 1.��ֵַΪȫ0ʱ����ʾɾ����ǰ���أ���wSinFamily����ֵ����
 *          ���ΪNETCBB_PROTO_TYPE_IPV4����NETCBB_PROTO_TYPE_IPV6
 *        2.�����ַ��0��pchInfaceNameΪNULLʱ����ϵͳ�Լ�ƥ���Ӧ�������������ء�
 *        3.�����ַΪ0����pchInfaceNameΪNULLʱ�����ɾ����ӦЭ������������ء�
 *
 * ����˵�� :
 *      pchIfaceName - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *      tGateWay     - Ĭ������ip��ַ�������ͣ�������
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbSetDefGateway(char *pchIfaceName, TNetcbbAddr tGateWay);

/************************************************************
 * ������ : NetcbbGetDefGateway
 *
 * ���� : ��ȡĬ������ip
 *
 * ���� : ���pchIfaceNameΪNULL, ���Զ���ȡϵͳ�е�Ĭ�����ص�ַ,
 *        ���ϵͳ�д��ڶ����ַ�������Ϊ��������һ��Ĭ�����ص�ַ.
 *
 * ����˵�� :
 *      pchIfaceName - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *      wSinFamily   - Э��ջ���� : NETCBB_PROTO_TYPE_IPV4
 *                                  NETCBB_PROTO_TYPE_IPV6
 *      ptGateWay    - Ĭ������ip��ַ
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbGetDefGateway(char *pchIfaceName, u16 wSinFamily, TNetcbbAddr *ptGateWay);

/************************************************************
 * ������ : NetcbbDelDefGateway
 *
 * ���� : ɾ��Ĭ������ip
 *
 * ���� :
 *        1.���pchIfaceName����NULL, ��ɾ��ϵͳ�����е�wSinFamilyЭ�������ء�
 *
 *
 * ����˵�� :
 *      pchIfaceName - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *      wSinFamily  - Э��ջ���� :  NETCBB_PROTO_TYPE_IPV4
 *                                  NETCBB_PROTO_TYPE_IPV6
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbDelDefGateway(char *pchIfaceName, u16 wSinFamily);

/************************************************************
 * ������ : NetcbbAddOneIpRoute
 *
 * ���� : ����һ��·��
 *
 * ���� :
 *      ptNetIpRouteParam->achIfaceName���Ϊȫ0ʱ����ϵͳ�Լ�����·��
 *      ���õĽӿ�(��eth0����eth1)
 *
 *
 * ����˵�� :
 *      ptNetIpRouteParam - ָ����·����Ϣ��TNetIpRouteParam�ṹָ��
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbAddOneIpRoute(TNetcbbIpRouteParam *ptNetIpRouteParam);

/************************************************************
 * ������ : NetcbbDelOneIpRoute
 *
 * ���� : ɾ��һ��·��
 *
 * ���� :
 *      ptNetIpRouteParam->achIfaceName���Ϊȫ0ʱ����ϵͳ�Լ�����·��
 *      ���õĽӿ�(��eth0����eth1)
 *
 * ����˵�� :
 *      ptNetIpRouteParam    - ָ����·����Ϣ��TNetIpRouteParam�ṹָ��
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbDelOneIpRoute(TNetcbbIpRouteParam *ptNetIpRouteParam);

/************************************************************
 * ������ : NetcbbGetAllIpRoute
 *
 * ���� : ��ȡ����·����Ϣ
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      wSinFamily  - Э��ջ���� :  NETCBB_PROTO_TYPE_IPV4
 *                                  NETCBB_PROTO_TYPE_IPV6
 *                                  NETCBB_PROTO_TYPE_ALL
 *      ptNetIpRouteParam    - ָ����·����Ϣ��TNetIpRouteParam�ṹָ��
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbGetAllIpRoute(u16 wSinFamily, TNetcbbAllIpRouteInfo *ptNetAllIpRouteInfo);

/************************************************************
 * ������ : NetcbbModifyIpRouteMetric
 *
 * ���� : �޸�һ��·�ɵ�metric
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      ptNetIpRouteParam    - ָ����·����Ϣ��TNetIpRouteParam�ṹָ��
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbModifyIpRouteMetric(TNetcbbIpRouteParam *ptNetIpRouteParam);

/************************************************************
 * ������ : NetIpConflictCallBackReg
 *
 * ���� : ע��ip��ַ��ͻʱ�ص�����,���豸��IP��ַ���ⲿ�豸��
 *        ͻʱ������øú���֪ͨҵ�����
 *
 * ���� :
 *        1.ipv6��ͻ����ݲ�֧�֡�
 *
 *
 * ����˵�� :
 *      wSinFamily  - Э��ջ���� :  NETCBB_PROTO_TYPE_IPV4
 *                                  NETCBB_PROTO_TYPE_IPV6
 *      ptFunc    - ִ��ҵ�����ע��Ļص�����ָ��
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbIpConflictCheckStart(u16 wSinFamily, TNetcbbConflictCallBack ptFunc);

/************************************************************
 * ������ : NetIpConflictCallBackReg
 *
 * ���� : ע��ip��ַ��ͻʱ�ص�����,���豸��IP��ַ���ⲿ�豸��
 *        ͻʱ������øú���֪ͨҵ�����
 *
 * ���� :
 *        1.ipv6��ͻ����ݲ�֧�֡�
 *
 *
 * ����˵�� :
 *      wSinFamily  - Э��ջ���� :  NETCBB_PROTO_TYPE_IPV4
 *                                  NETCBB_PROTO_TYPE_IPV6
 *      ptFunc    - ִ��ҵ�����ע��Ļص�����ָ��
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbIpConflictCheckStop(u16 wSinFamily);

/************************************************************
 * ������ : NetcbbSetDscp
 *
 * ���� : ����ip��ͷdscpֵ(0-63)
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      nSockfd    - Ҫ���õ��׽���������
 *      byDscp     - Ҫ���õ�dscpֵ(0-63)
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbSetDscp(u16 wSinFamily, s32 nSockfd, u8 byDscp);

/************************************************************
 * ������ : NetCheckTheSameNet
 *
 * ���� : У��ip�������Ƿ���ͬһ����
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      tIpAddr  - ip��ַ
 *      dwPrefix - ����ǰ׺
 *      tGateway - ����
 *
 * ����ֵ : NETCBB_OK    - У��ɹ�, ��ͬһ������
 *          NETCBB_NOT_THE_SAME_NET  - ����ͬһ������
 *          NETCBB_INVALID_PARAM - �����������
 ***********************************************************/
s32 NetcbbCheckIsSameNet(TNetcbbAddr tIpAddr, u32 dwPrefix, TNetcbbAddr tGateway);

/************************************************************
 * ������ : NetcbbIfaceShutdown
 *
 * ���� : �ر�����
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      pchIfaceName - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbIfaceShutdown(char *pchIfaceName);

/************************************************************
 * ������ : NetcbbIfaceNoShutdown
 *
 * ���� : ������
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      pchIfaceName - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbIfaceNoShutdown(char *pchIfaceName);

/************************************************************
 * ������ : NetGetEthState
 *
 * ���� : ��ȡ����״̬
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      pchIfaceName - ��������(֧��"ethX", "wlanX", "bondX", "pppX"���֣�XΪ0,1,2...)
 *      pdwFlag  - ����״̬��NETCBB_IF_UP     ����up
 *                           NETCBB_IF_DOWN   ����down
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ����
 ***********************************************************/
s32 NetcbbGetIfaceState(char *pchIfaceName, u32* pdwFlag);

/************************************************************
 * ������ : NetcbbStatCallBackRegister
 *
 * ���� : ע���豸ͳ��ֵ�ص�����
 *
 * ���� :
 *
 *
 * ����˵�� :
 *      nInterval  - �ص������ͬʱ���ݴ˼�����㷢���Լ����յļ��.
 *      pfNotifyCb - �ص�֪ͨ����.
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetcbbStatNotifyCallbackReg(int nInterval, TDevStatNotifyCallBack pfNotifyCb);

/************************************************************
 * ������ : NetcbbStatStop
 *
 * ���� : �ر�ע���豸ͳ��ֵ
 *
 * ���� :
 *
 *
 * ����˵�� :
 *     		��
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ����
 ***********************************************************/
s32 NetcbbStatStop(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_INTERFACE_H_ */
