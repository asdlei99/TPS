#ifndef _NETCBB_WEBS_1X_H_
#define _NETCBB_WEBS_1X_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#include "netcbb_webs.h"
/************************************************************
 * ������ : NetWebsEnable
 *
 * ���� : ������ֹͣweb server
 *
 * ���� : ��
 *
 * ����˵�� :
 *      port     - Ҫ���ö˿ں�
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetWebsEnable(s32 port);

/************************************************************
 * ������ : NetWebsDisable
 *
 * ���� : ������ֹͣweb server
 *
 * ���� : ��
 *
 * ����˵�� :
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetWebsDisable(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_WEBS_H_ */
