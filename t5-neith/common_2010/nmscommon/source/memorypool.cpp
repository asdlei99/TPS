// MemoryPool.cpp: implementation of the CMemoryPool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemoryPool.h"
#include "osp.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CTAapater<CMemoryManage> *CNormalPolicy::Find(int len)
{
	int num = 0;
	for( int i = 0; i < MemoryManageNum; i++ )
	{
		if( emMemNoERROR == m_pcManager[i]->CheckMemory(len, num) )
		{
			return &m_pcManager[i];
		}
	}
	return NULL;
}

void CPolicyFactory::SetpManage( CTAapater<CMemoryManage> *p )
{
	m_pcManager = p;
}


CTAapater<CMemoryManage> *CPolicyFactory::FindSuitable( int len, EmFitPolicy emplc /*= emNormalP*/ )
{
	CTAapater<CMemoryManage> * pTmp = NULL;
	switch( emplc )
	{
	case emNormalP:
		{
			CNormalPolicy cNormalPlc(m_pcManager);
			pTmp = cNormalPlc.Find(len);
		}
		break;
	case emPerfectP:
		break;
	case emBadP:
		break;
	default:
		break;
	}
	
	return pTmp;
}






template<> CMemoryPool* CSingleton<CMemoryPool>::m_psSingleton  = NULL;


void CMemoryPool::Init()
{
	for(int i = 0 ; i < MemoryManageNum; i++ )
	{
		memset( &m_atBlockBorder[i], 0 , sizeof( TBlockBorder ) );
	}

	m_nDropApplyTimes = 0;
	m_nGetFailureTime = 0;
}


CMemoryPool::CMemoryPool():CSingleton<CMemoryPool>()
{
	Init();
}

CMemoryPool::~CMemoryPool()
{

}
/*=============================================================================
函 数 名:  InitMemoryPool
功    能:  初始化内存
参    数:  维数为MemoryManageNum 的2列的数组 指针
注    意:  请把单位内存小的放在数组的前面
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容 
2010/12/17  4.0     沈  钦    创建
=============================================================================*/
EmMemoryError CMemoryPool::InitMemoryPool( int (*p)[2] )
{
	int nUnitMemoryLen = 0;
	int nUnitMemoryNum = 0;
	//初始时请确保块小的放在最前面	

	int i = 0 ;
	for( i = 0; i < MemoryManageNum ; i++ )
	{
		nUnitMemoryLen = *(*(p+i) + 0);
		nUnitMemoryNum = *(*(p+i) + 1);
		if( emMemNoERROR != m_acMemManage[i]->InitMemoryManage(nUnitMemoryLen, nUnitMemoryNum) )
		{
			return emMemErrNewError;
		}
	}
		

	for( i = 0; i < MemoryManageNum ; i++ )
	{
		m_acMemManage[i]->GetBlockBorder(m_atBlockBorder[i]);
	}

	m_cMangePlc.SetpManage( m_acMemManage );

	return emMemNoERROR;
}



/*=============================================================================
函 数 名:  InitMemoryPool
功    能:  初始化内存
参    数:  
注    意:  
返 回 值: 
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容 
2010/12/17  4.0     沈  钦    创建
=============================================================================*/
EmMemoryError CMemoryPool::InitMemoryPool()
{
	//初始时请确保块小的放在最前面
	if( emMemNoERROR != m_acMemManage[0]->InitMemoryManage(10, 10) )
	{
		return emMemErrNewError;
	}
	
	if( emMemNoERROR != m_acMemManage[1]->InitMemoryManage(20, 5)	)
	{
		return emMemErrNewError;
	}
	
	if( emMemNoERROR != m_acMemManage[2]->InitMemoryManage(30, 3)	)
	{
		return emMemErrNewError;
	}
	
	if( emMemNoERROR != m_acMemManage[3]->InitMemoryManage(50, 2)	)
	{
		return emMemErrNewError;
	}
	
	if( emMemNoERROR != m_acMemManage[4]->InitMemoryManage(100, 1) )
	{
		return emMemErrNewError;
	}
	
	for( int i = 0; i < MemoryManageNum ; i++ )
	{
		m_acMemManage[i]->GetBlockBorder(m_atBlockBorder[i]);
	}
	
	m_cMangePlc.SetpManage( m_acMemManage );
	
	return emMemNoERROR;
}
/*=============================================================================
函 数 名:  FindSuitable
功    能:  根据相应模式查找合适内存块
参    数:  [in]len 数据大小
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容 
2010/12/17  4.0     沈  钦    创建
=============================================================================*/
CTAapater<CMemoryManage>	*CMemoryPool::FindSuitable( int len)
{
	return m_cMangePlc.FindSuitable( len );
}
/*=============================================================================
函 数 名:  InputData
功    能:  放数据到内存
参    数:  [in]pdata 数据指针   [in]len 要存入内容的大小     [pout]  要存储的数据在 拷贝后的首地址
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2010/12/17  4.0     沈  钦    创建
=============================================================================*/
EmMemoryError	CMemoryPool::InputData(char *pdata, int len, char **pout)
{
	CTAapater<CMemoryManage>	*p = FindSuitable( len );
	if( NULL != p )
	{
		EmMemoryError emRes = emMemNoERROR;		
		emRes = (*p)->InputData( pdata, len, pout );
		return emRes;
	}
	
	m_nDropApplyTimes++;
	return   emMemErrNotEnoughError;
}



/*=============================================================================
函 数 名:  GettData
功    能:  获得数据
参    数:  [in]pdata 要查找的内容指针    [out]pout 输出内容的指针 [out]len输出长度
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2010/12/17  4.0     沈  钦    创建
=============================================================================*/
EmMemoryError	CMemoryPool::GetData(char *pdata, char *pout, int &len)
{
	EmMemoryError EmRes = emMemErrNotFound;
	for( int i = 0; i < MemoryManageNum; i++ )
	{
		if( m_atBlockBorder[i].startpos <= pdata &&  m_atBlockBorder[i].endpos >= pdata )
		{
			EmRes = m_acMemManage[i]->GetData(pdata, pout, len ) ;
			if( emMemErrNotFound == EmRes )
			{
				OspPrintf( 1, 0, "CMemoryPool::GetData  失败\n ");
				continue;
			}
			else if( emMemNoERROR == EmRes )
			{
				return EmRes;
			}
		}
	}

	m_nGetFailureTime++;
	return EmRes;
}


void CMemoryPool::PrintManageInfo()
{
	int NowFreeBlock = 0;
	int MaxUsingBlocks = 0;
	for( int i = 0; i < MemoryManageNum; i++ )
	{
		m_acMemManage[i]->GetManageInfo(NowFreeBlock, MaxUsingBlocks);
		OspPrintf(TRUE, FALSE, "内存管理%d  \n freeblock = %d    maxpeek = %d\n",  i, NowFreeBlock, MaxUsingBlocks  );
	}

	OspPrintf(TRUE, FALSE, "\nPool Info \n 内存申请失败次数 %d  内存获取失败次数 %d\n", m_nDropApplyTimes, m_nGetFailureTime );
};
