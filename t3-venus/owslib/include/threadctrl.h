/*****************************************************************************
模块名      : threadctrl.h
文件名      : threadctrl.h
相关文件    : 
文件实现功能: 线程相关操作/同步锁控制
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/11/27     1.0         刘德印      创建
******************************************************************************/
#ifndef THREADCTRL_H
#define THREADCTRL_H

#include "owscommon.h"

//////////////////////////////////////////////////////////////////////////
//普通线程锁
class CLock
{
public:
	CLock()
	{
	#ifdef _LINUX_
		pthread_mutex_init( &m_mtx, NULL );
		PrtMsg("pthread_mutex_init\n");
	#else
		InitializeCriticalSection(&m_mtx);
	#endif
	}
	
	~CLock()
	{
	#ifdef _LINUX_
		PrtMsg("pthread_mutex_destroy\n");
		pthread_mutex_destroy(&m_mtx);
	#else	
		DeleteCriticalSection(&m_mtx);
	#endif
	}
	
	bool Lock()
	{
	#ifdef _LINUX_
		int nRet = pthread_mutex_lock(&m_mtx);
		PrtMsg("pthread_mutex_lock\n");
		return ( 0 == nRet );
	#else
		EnterCriticalSection(&m_mtx);
		return true;
	#endif
	}
	
	bool UnLock()
	{
	#ifdef _LINUX_
		int nRet = pthread_mutex_unlock(&m_mtx);
		PrtMsg("pthread_mutex_unlock\n");
		return ( 0 == nRet );
	#else
		LeaveCriticalSection(&m_mtx);
		return true;		
	#endif
	}
	
private:

	#ifdef _LINUX_
		pthread_mutex_t m_mtx;
	#else
		CRITICAL_SECTION m_mtx;
	#endif

};

#endif