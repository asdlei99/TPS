#ifndef _NETCBB_WRAPPER_1X_H_
#define _NETCBB_WRAPPER_1X_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#include "netcbb_wrapper.h"
/************************************************************
 * ������ : NetInit
 *
 * ���� : ��ģ��ĳ�ʼ������
 *
 * ���� : ��
 *
 * ����˵�� :
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetInit(void);

/************************************************************
 * ������ : NetQueryNetcbbVersion
 *
 * ���� : �ṩ��ҵ�����õ�os�汾�Ų�ѯ
 *
 * ���� : ��
 *
 * ����˵�� :
 *      pchVer    - ��ȡ�汾���ַ���ָ��
 *      dwBufLen  - ���ַ����ĳ���
 *      pdwVerLen - ��ȡ�汾��ʵ���ַ������ȣ��ó��ȷ���֮ǰ�����dwBufLen�Ƚ��Ƿ����������ʱ�Ŷ�pVer��ֵ
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
extern s32 NetQueryVersion(char* pchVer, u32 dwBufLen);

/************************************************************
 * ������ : NetLogSwitch
 *
 * ���� : ��ģ���ӡ����(Ĭ�Ϲر�)
 *
 * ���� : ��
 *
 * ����˵�� :
 *      1  -  ��log
 *      0  -  �ر�log
 *       Ĭ�Ϲر�
 *
 * ����ֵ : OK    - �ɹ�
 *          ERROR - ʧ��
 ***********************************************************/
s32 NetLogSwitch(u32 dwSwitch);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_WRAPPER_H_ */
