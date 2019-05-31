#ifndef _TP_AUTH_H_
#define _TP_AUTH_H_

#include "kdvtype.h"


#if (defined(WIN32) || defined(_WIN32) ) && defined(_USRTPAUTHDLL)

#ifdef TPAUTHDLL_EXPORTS
#define TPAUTH_API __declspec(dllexport)
#else
#define TPAUTH_API __declspec(dllimport)
#endif

#else  // ����ƽ̨�ģ������Ǿ�̬����

#define TPAUTH_API 

#endif// (defined(WIN32) || defined(_WIN32) ) && defined(_USRTPAUTHDLL)

#ifndef TPIN
#define TPIN
#endif// TPIN

#ifndef TPOUT
#define TPOUT
#endif//TPOUT

#define TPAUTH_LISTEN_PORT		5050
#define TPAUTH_INNER_UDP_PORT	6666

typedef struct tagTTpAuthUserParam
{
	u32		m_dwAppCall;	//appcall (confid+epid)
	u32		m_dwPaCall;		//pacall
	u32		m_dwUserParam;  //��չ

	tagTTpAuthUserParam()
	{
		Clear();
	}

	void Clear()
	{
		m_dwAppCall = 0;
		m_dwPaCall = 0;
		m_dwUserParam = 0;
	}

	tagTTpAuthUserParam& operator = (const tagTTpAuthUserParam& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		this->m_dwAppCall = tRhs.m_dwAppCall;
		this->m_dwPaCall = tRhs.m_dwPaCall;
		this->m_dwUserParam = tRhs.m_dwUserParam;
		return *this;
	}

}TTpAuthUserParam;

enum EmTpAuthRes
{
	em_tp_auth_res_success = 0, // ��֤�ɹ�
	em_tp_auth_res_fail,
	em_tp_auth_res_unreachable,
	em_tp_auth_res_localerror,
	em_tp_auth_res_paramerror,

	em_tp_auth_res_end = 100,
};
typedef void (*CBTpAuthRes) (TTpAuthUserParam tUsrParam, u32 dwLocalIp, u32 dwDstIp, EmTpAuthRes emRes);

//��ʼ��������һ�μ���
//����ֵΪFALSE��Ϊ�����쳣
TPAUTH_API BOOL32 InitTpAuth(CBTpAuthRes pcbFunRes);

// ��֤����
// ��Ҫͬʱ���bWaitCB�ͷ���ֵ
//bWaitCBΪTRUE,����ֵΪem_tp_auth_res_success,��Ҫ�ȴ��ص���֪��֤���
//bWaitCBΪTRUE,����ֵΪ��em_tp_auth_res_success������,�����쳣
//bWaitCBΪFALSE,����ֵ��Ϊ��֤���
TPAUTH_API EmTpAuthRes TpAuthReq(TPIN TTpAuthUserParam tUsrParam, TPIN u32 dwLocalIp, TPIN u32 dwDstIp, TPOUT BOOL32& bWaitCB);


#endif //_TP_AUTH_H_