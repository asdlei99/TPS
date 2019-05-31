/*****************************************************************************
模块名      : CPubFunc
文件名      : PubFunc.h
相关文件    : 
文件实现功能: umclib库调用接口公共类
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/5/28      1.0         刘德印      创建
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
    函 数 名:GetUmsCesstionPtr
    功    能:CUmsSessionCtrlIF接口指针
    参    数:无
    注    意:无
    返 回 值:void
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/05/29  1.0     刘德印    创建
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
