#ifndef _NETCBB_BOND_H_
#define _NETCBB_BOND_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "netcbb_def.h"

/* bondģʽ */
#define NETCBB_BOND_MODE_ROUNDROBIN    0
#define NETCBB_BOND_MODE_ACTIVEBACKUP  1  /* ����ģʽ */
#define NETCBB_BOND_MODE_XOR           2
#define NETCBB_BOND_MODE_BROADCAST     3
#define NETCBB_BOND_MODE_8023AD        4  /* ��������������ԽӵĽ�������֧����·�ۺ� */
#define NETCBB_BOND_MODE_TLB           5
#define NETCBB_BOND_MODE_ALB           6  /* TLB + RLB (receive load balancing) */

typedef struct
{
	char *achIface[NETCBB_NIC_MAX_NUM]; /* ��Ҫ�󶨵������ӿ��б�ָ�� */
	u32 dwIfaceNum;             /* ��Ҫ�󶨵������ӿڸ��� */
	char *pchActiveIface;       /* bond������ʹ�õ�����, ��"eth0" */
	char *pchBondPath;          /* bond.ko��·������/lib/module */
}TNetcbbBondParam;

/************************************************************
 * ������ : NetcbbBondStart
 *
 * ���� : ����bondģʽ
 *
 * ���� :
 *     1.Ŀǰhisi��֧��BOND_MODE_ACTIVEBACKUPģʽ.
 *     2.����ɹ�����ϵͳ������bond0����ӿڣ��������в�����ֱ�Ӳ���
 *       bond0���ɡ�
 *
 *
 * ����˵�� :
 *          dwBondMode    - bondģʽ(BOND_MODE_ROUNDROBIN��)
 *          ptBondParam   - bondģʽ����
 *
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ʧ��
 ***********************************************************/
s32 NetcbbBondStart(u32 dwBondMode, TNetcbbBondParam *ptBondParam);

/************************************************************
 * ������ : NetcbbBondStop
 *
 * ���� : ֹͣbondģʽ
 *
 * ���� : ֹͣbondģʽʱ���Ὣ������ص��������
 *
 * ����˵�� :
 *
 *
 * ����ֵ : NETCBB_OK    - �ɹ�
 *          NETCBB_ERROR - ʧ��
 ***********************************************************/
s32 NetcbbBondStop();


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
