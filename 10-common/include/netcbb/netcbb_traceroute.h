#ifndef _NETCBB_TRACEROUTE_H_
#define _NETCBB_TRACEROUTE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include "netcbb_def.h"

/* TNetcbbTracerouteCallBack ����ֵ����ӦTNetcbbTracerouteCallBack �� nResult ���� */
#define  NETCBB_TRACEROUTE_CB_ERROR                               101
#define  NETCBB_TRACEROUTE_CB_TIMEOUT                             102
#define  NETCBB_TRACEROUTE_CB_MIDDLE_ROUTE                        103
#define  NETCBB_TRACEROUTE_CB_REACH_DST                           104
#define  NETCBB_TRACEROUTE_CB_NETWORK_UNREACHABLE                 105
#define  NETCBB_TRACEROUTE_CB_HOST_UNREACHABLE                    106        /* �ص�������ʱ traceroute���Զ�ֹͣ */

/* traceroute api�ĺ�������ֵ */
#define  NETCBB_TRACEROUTE_CREAT_CB_THREAD_FAILED                 (NETCBB_TRACEROUTE_BASE_ERROR + 1)
#define  NETCBB_TRACEROUTE_STASRT_FAILED                          (NETCBB_TRACEROUTE_BASE_ERROR + 2)
#define  NETCBB_TRACEROUTE_STOP_FAILED                            (NETCBB_TRACEROUTE_BASE_ERROR + 3)
#define  NETCBB_TRACEROUTE_CREAT_SEM_FAILED                       (NETCBB_TRACEROUTE_BASE_ERROR + 4)

typedef struct
{
	u32 dwTtl;                 /* TTLֵ ���÷�Χ0-255, 0����255����ȡ��, ҵ������н������ƣ�����󲻳���255 */
}TNetcbbTracerouteOpt;

typedef struct
{
	TNetcbbAddr tIpaddr;
	u32 dwTtl;
	s32 nUserId;
	s32 nTripTime;
	char* achDomName;
	s32 nErrType;
	s32 nErrCode;
	s32 nIsOver;
}TNetcbbTracerouteCBInfo;

/************************************************************
 * ������ : TNetcbbTracerouteCallBack
 *
 * ���� : Traceroute �ص�����
 *
 * ���� :
 *       1.�˺�������Ӧ������̣��õ�״̬�󣬿���״̬��,
 *         �����Ϸ��ء�
 *       2.�����ڻص�������ʹ�������ź����ȣ������׵���������
 *
 * ����˵�� :
 *      nResult    - Traceroute �ص����(NET_TRACEROUTE_CB_ERROR, NET_TRACEROUTE_CB_TIMEOUT,
 *                                             NET_TRACEROUTE_CB_MIDDLE_ROUTE, NET_TRACEROUTE_CB_REACH_DST)
 *      nTtl       - TTLֵ
 *      nTripTime  - ���紫��ʱ��ֵ(ע��:��λ��΢��, ���Ǻ���)
 *      dwIp       - ·��ip��ַ
 *      achDomName - ·������(�ݲ�֧��)
 *      nUserID    - �û�ID��־���û����ֲ�ͬ���û�����(��ʱ��֧�ֶ��û����ã���ֵ0)
 *      nErrType   - ��������(��ʱ���Ժ���,��δ֧��)
 *      nErrCode   - ������(��ʱ���Ժ���,��δ֧��)
 *
 * ����ֵ : ���ϲ�ҵ��ʵ��
 ***********************************************************/
typedef int(*TNetcbbTracerouteCallBack)(s32 nResult, TNetcbbTracerouteCBInfo* ptTracertCbInfo);

/************************************************************
 * ������ : NetcbbTracerouteStart
 *
 * ���� : ����Traceroute����
 *
 * ���� :
 *      1.��ʱ��֧��ipv6��ַ.
 *      2.nUserIDֵ�������0.
 *
 * ����˵�� :
 *      ptTraceroutePara   - traceroute ����
 *      nUserID            - �û�ID��־���û����ֲ�ͬ���û�����(��ʱ��֧�ֶ��û����ã��븳ֵ0)
 *      ptCallBackFunc     - traceroute����Ļص�����
 *
 * ����ֵ : NET_CALLBACK_NULL                       - �ص�����û�ж���
 *          NET_TRACEROUTE_CREAT_CB_THREAD_FAILED   - �����ص��߳�ʧ��
 *          NET_TRACEROUTE_CREAT_SEM_FAILED         - �����ź���ʧ��
 *          NET_TRACEROUTE_STASRT_FAILED            - ����ʧ��
 *          NETCBB_OK                               - �����ɹ�
 ***********************************************************/
s32 NetcbbTracerouteStart(TNetcbbAddr tDestIp, TNetcbbTracerouteOpt* ptTraceRtOpt, s32 nUserID, TNetcbbTracerouteCallBack ptCallBackFunc);

/************************************************************
 * ������ : NetcbbTracerouteStop
 *
 * ���� : ֹͣtraceroute����
 *
 * ���� :
 *      1.��ʱ��֧��ipv6��ַ.
 *      2.nUserIDֵ�������0.
 *
 * ����˵�� :
 *      nUserID            - �û�ID(��ʱ��֧�֣��븳ֵ0)
 *
 * ����ֵ : NET_TRACEROUTE_STOP_FAILED   - ��ֹʧ��
 *          NETCBB_OK                    - ��ֹ�ɹ�
 ***********************************************************/
s32 NetcbbTracerouteStop(s32 nUserID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_INTERFACE_H_ */

