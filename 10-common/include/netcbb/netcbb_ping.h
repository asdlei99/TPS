#ifndef _NETCBB_PING_H_
#define _NETCBB_PING_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* TPingCallBack�ص��ķ���ֵ����Ӧ����ΪnResult */
#define  NETCBB_PING_REPLY          0    /* ping��������Ӧ */
#define  NETCBB_PING_TIMEOUT        1    /* ping����ʱ */
#define  NETCBB_PING_ERROR          2    /* ping��ϵͳ���� */
#define  NETCBB_PING_NET_UNREACH    3    /* ping�����粻�ɴ� */

/* ping api�ĺ�������ֵ */
#define  NETCBB_PING_CREAT_CB_THREAD_FAILED    (NETCBB_PING_BASE_ERROR + 1)
#define  NETCBB_PING_STASRT_FAILED             (NETCBB_PING_BASE_ERROR + 2)
#define  NETCBB_PING_STOP_FAILED               (NETCBB_PING_BASE_ERROR + 3)
#define  NETCBB_PING_ALREADY_START             (NETCBB_PING_BASE_ERROR + 4)
#define  NETCBB_PING_ALREADY_STOP              (NETCBB_PING_BASE_ERROR + 5)

/* NetPing�ӿڴ�������ṹ�� */
typedef struct{
    s32 nPktSize;   /* Ҫping�����ݱ��Ĵ�С�����ֽ�Ϊ��λ����С��56�����С��56������ֵ56 */
    s32 nTimeOut;   /* ping�ĳ�ʱֵ������Ϊ��λ */
    s32 nTtl;       /* TTLֵ���÷�Χ0-255, 0����255����ȡ��, ҵ������н������ƣ�����󲻳���255 */
    s32 nCount;     /* ping����Ŀ */
}TNetcbbPingOpt;

typedef struct
{
	s32 nTtl;
	s32 nTripTime;
	s32 nSeq;
	s32 nUserID;
	s32 nErrType;
	s32 nErrCode;
}TNetcbbPingCBInfo;

/************************************************************
 * ������ : TNetcbbPingCallBack
 *
 * ���� : ping�ص�����
 *
 * ���� :
 *       1.�˺�������Ӧ������̣��õ�״̬�󣬿���״̬��,
 *         �����Ϸ��ء�
 *       2.�����ڻص�������ʹ�������ź����ȣ������׵���������
 *
 * ����˵�� :
 *      nResult   - ping �ص����(NETCBB_PING_REPLY, NETCBB_PING_TIMEOUT, NETCBB_PING_ERROR)
 *      nTtl      - TTLֵ
 *      nTripTime - ���紫��ʱ��ֵ(ע��:��λ��΢��, ���Ǻ���)
 *      nSeq      - ping������
 *      nUserID   - �û�ID��־���û����ֲ�ͬ���û�����(��ʱ��֧�ֶ��û�����
 *      nErrType  - ��������(��ʱ���Ժ���,��δ֧��)
 *      nErrCode  - ������(��ʱ���Ժ���,��δ֧��)
 * ����ֵ : ���ϲ�ҵ��ʵ��
 ***********************************************************/
typedef int(*TNetcbbPingCallBack)(s32 nResult, TNetcbbPingCBInfo *ptPingCbInfo);

/************************************************************
 * ������ : NetcbbPingStart
 *
 * ���� : ����ping
 *
 * ���� :
 *     1.����һ�δ˽ӿ���Ҫ����һ��nUserID, ipv6��ipv4��nUserIDҲ���벻ͬ.
 *     2.nUserIDֵ�������0.
 *
 * ����˵�� :
 *      dwDestIP       - Ping��Ŀ��IP��ַ(������)
 *      ptPingOpt      - Ping�Ĳ����ṹ��ָ��
 *      nUserID        - �û�ID��־���û����ֲ�ͬ���û�����
 *      ptCallBackFunc - Ping����Ļص�����
 * ����ֵ : ok - �ɹ�
 *          NET_CALLBACK_NULL  - �ص�����û�ж���
 *          NETCBB_PING_CREAT_CB_THREAD_FAILED  - �����ص��߳�ʧ��
 *          NET_PING_STASRT_FAILED  - ����ʧ��
 ***********************************************************/
s32 NetcbbPingStart(TNetcbbAddr tDestIp, TNetcbbPingOpt* ptPingOpt, s32 nUserID, TNetcbbPingCallBack ptCallBackFunc);

/************************************************************
 * ������ : NetcbbPingStop
 *
 * ���� : ֹͣping
 *
 * ���� :
 *     1.nUserIDֵ�������0.
 *
 * ����˵�� :
 *      nUserID        - �û�ID��־���û����ֲ�ͬ���û�����(��ʱ��֧�ֶ��û����ã��븳ֵ0)
 * ����ֵ : ok - �ɹ�
 *          NET_PING_STOP_FAILED  - ��ֹʧ��
 ***********************************************************/
s32 NetcbbPingStop(s32 nUserID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*_NETCBB_INTERFACE_H_*/

