#ifndef _NETCBB_NTPC_H_
#define _NETCBB_NTPC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include "netcbb_def.h"

/* ��Ϣ���� */
#define NETCBB_NTPC_MSG_BASE                  (u32)30000                       /* NTP�е���������NTP-Serverͬ��ʱ��ʱ�ص���������Ϣ���ַ */
#define NETCBB_NTPC_MSG_SYNC_TIME_SUCCESS     (u32)(NETCBB_NTPC_MSG_BASE + 1)  /* ��NTP-Serverͬ��ʱ��Уʱ�ɹ�����Ϣ�壺��*/
#define NETCBB_NTPC_MSG_SYNC_TIME_FAILED      (u32)(NETCBB_NTPC_MSG_BASE + 2)  /* ��NTP-Serverͬ��ʱ��Уʱʧ�ܣ���Ϣ�壺��*/

/************************************************************
 * ������ : NetCbbNTPCSyncTimeCallBack
 *
 * ���� : ������ͬ��NTP-Serverͬ��ϵͳʱ��ʱ��֪ͨ�û���������Ļص�����
 *
 * ���� : ��
 *
 *
 * ����˵�� :
 *      dwMsgID   - �¼����ͣ����������Ϣ���Ͷ���
 *      pMsg      - ����¼�������ƥ�����Ϣ���ݣ�Ŀǰ������ΪNULL���Ժ������չ
 *
 * ����ֵ : ��ʱ����Ϊ0���Ժ������չ
 ***********************************************************/
typedef int(*NetCbbNtpcSyncTimeCallBack)(u32 dwMsgID, void* pMsg);

/************************************************************
 * ������ : NetcbbNtpcStart
 *
 * ���� : ����NTP-Client�˹���
 *
 * ���� : ��
 *
 *
 * ����˵��:
 *      dwServerIp          - NTP-Server��IP��ַ�������ֽ���
 *      dwSyncTimeInterval  - ��NTP-Server����ʱ��ͬ����ʱ����������Ϊ��λ����Χ��64s~1024s��
 *                            �����ù���֮�󣬵ײ�ᰴ���û����õ�ʱ������
 *                            ÿ��һ��ʱ�����NTP-Serverͬ��ϵͳʱ�䲢���õ�����ϵͳ��
 *      ptCallBack          - �ص�֪ͨntpͬ�����
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ʧ��
 ***********************************************************/
s32 NetcbbNtpcStart(TNetcbbAddr tServerIp, u32 dwSyncTimeInterval, NetCbbNtpcSyncTimeCallBack ptCallBack);

/************************************************************
 * ������ : NetcbbNtpcStop
 *
 * ���� : �ر�NTP-Client�˹���
 *
 * ���� : ��
 *
 * ����˵�� :
 *      wSinFamily  - Э��ջ���� :  NETCBB_PROTO_TYPE_IPV4
 *                                  NETCBB_PROTO_TYPE_IPV6
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ʧ��
 ***********************************************************/
s32 NetcbbNtpcStop(u16 wSinFamily);


/************************************************************
 * ������ : NetcbbNtpcSerCheck
 *
 * ���� : ����NTPSer ��IP����
 *
 * ���� : ��
 *
 * ����˵�� :dwServerIp          - NTP-Server��IP��ַ�������ֽ���
 *
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ʧ��
 ***********************************************************/

s32 NetcbbNtpcSerCheck(TNetcbbAddr tServerIp);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*_NETCBB_NTP_H_*/

