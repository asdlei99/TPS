/*****************************************************************************
ģ����      : CPubFunc
�ļ���      : PubFunc.h
����ļ�    : 
�ļ�ʵ�ֹ���: umclib����ýӿڹ�����
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/5/28      1.0         ����ӡ      ����
******************************************************************************/

#if !defined(AFX_PUBFUNC_H__FC36759E_76A1_43CC_A0D9_C8D0619CC99B__INCLUDED_)
#define AFX_PUBFUNC_H__FC36759E_76A1_43CC_A0D9_C8D0619CC99B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "umsSessionctrlif.h"

class CPubFunc  
{
public:

	/*=============================================================================
    �� �� ��:GetUmsCesstionPtr
    ��    ��:CUmsSessionCtrlIF�ӿ�ָ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/05/29  1.0     ����ӡ    ����
    =============================================================================*/
	static CUmsSessionCtrlIF* GetUmsSesstionPtr();

	static void UmsSessionDestory();
 	
    virtual ~CPubFunc();
protected:
	CPubFunc();


private:
	static CPubFunc   *m_pThis;
	static CUmsSessionCtrlIF *m_pUmsSession;
};

#define BUSINESSIFPTR CPubFunc::GetUmsSesstionPtr()

#define DESTORYUMSSESSION CPubFunc::UmsSessionDestory();

#endif // !defined(AFX_PUBFUNC_H__FC36759E_76A1_43CC_A0D9_C8D0619CC99B__INCLUDED_)
