// MemoryManage.cpp: implementation of the CMemoryManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MemoryManage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
	
#define DELARRAYPTR(p) if( NULL != p ) { delete []p;  p= NULL; }





CMemoryManage::CMemoryManage()//: CTAapater<CMemoryManage>()
{
	ResetVal();
}

CMemoryManage::~CMemoryManage()
{	
	ClearAllMemory();
	ResetVal();
}

void CMemoryManage::ResetVal()
{
	m_pCurrentBlock = NULL;
	m_pMemStart = NULL;
	m_pMemBlockStart = NULL;
	m_nMemoryTotalSize = 0;
	m_nBlockSize = 0;
	m_dwDropApplyTimes = 0;
	m_bReInting = FALSE;
	m_nMaxUsingBlocks = 0;
	m_nFreeBlock = 0;
}

void CMemoryManage::ClearAllMemory()
{
	DELARRAYPTR( m_pMemStart )
	DELARRAYPTR( m_pMemBlockStart )
}
/*=============================================================================
函 数 名:  InitMemoryManage
功    能:  初始化内存
参    数:  [in]blocksize 块大小   [in]blocknum   块的数目
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容 
2010/12/17  4.0     沈  钦    创建
    =============================================================================*/
EmMemoryError CMemoryManage::InitMemoryManage(int blocksize /*= DEFAULTBLOCKSIZE*/, int blocknum /*= DEFAULTBLOCKNUM*/)
{
	m_nMemoryTotalSize =  blocksize * blocknum ;
	if( m_nMemoryTotalSize <= 0 )
	{
		m_nMemoryTotalSize = 0;
		return emMemErrNewError;
	}
	m_nBlockSize = blocksize;

	m_pMemStart = new char [ blocksize * blocknum ] ;
	if( m_pMemStart == NULL )
	{
		return emMemErrNewError;
	}
	memset( m_pMemStart, 0, blocksize * blocknum );

	m_pMemBlockStart = new TMemBlock[ blocknum ];
	if( m_pMemBlockStart == NULL )
	{
		return emMemErrNewError;
	}
	memset(m_pMemBlockStart, 0, sizeof(TMemBlock) * blocknum );


	//配对 TMemBlock与真实内存的关系
	for( int  i = 0; i < blocknum - 1; i++ )
	{
		( (PTMemBlock)(m_pMemBlockStart + i) )->pBlock = m_pMemStart + blocksize * i;
		( (PTMemBlock)(m_pMemBlockStart + i) )->pNext =  (PTMemBlock)(m_pMemBlockStart + (1 + i)) ; 
	}

	( (PTMemBlock)(m_pMemBlockStart + blocknum - 1) )->pBlock = m_pMemStart + blocksize * (blocknum - 1);
	( (PTMemBlock)(m_pMemBlockStart + blocknum - 1) )->pNext = m_pMemBlockStart;//最后一个指向第一个

	m_pCurrentBlock = m_pMemBlockStart;

	m_nFreeBlock = blocknum;
	

	
	return emMemNoERROR;
}


EmMemoryError CMemoryManage::ReInit( int blocksize /*= DEFAULTBLOCKSIZE*/, int blocknum /*= DEFAULTBLOCKNUM*/ )
{
	m_bReInting = TRUE;
	int nBlockNum = m_nMemoryTotalSize / m_nBlockSize;
	int nBlockSize = m_nBlockSize;
	ClearAllMemory();
	ResetVal();
	EmMemoryError emRes =  InitMemoryManage(  nBlockSize,  nBlockNum );
	m_bReInting = FALSE;
	return emRes;
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
EmMemoryError CMemoryManage::InputData(char *pdata, int len, char **pout)
{
	if(m_bReInting)
	{
		return emMemErrReIniting;
	}
	int nBlockNum = 0;
	EmMemoryError emRes = CheckMemorySize( len , nBlockNum);
	if(  emRes != emMemNoERROR )
	{
		m_dwDropApplyTimes++;
		return emRes;
	}
	
	char *pPos = pdata;
	
	if( 1 == nBlockNum )
	{
		*pout = SetData(m_pCurrentBlock, 1, pdata, len );
		m_pCurrentBlock = m_pCurrentBlock->pNext;		
	}
	else//大于1
	{
		for( int i = 0; i < nBlockNum - 1 ; i++ )
		{
			if( i == 0 )
			{
				*pout = SetData(m_pCurrentBlock, nBlockNum, pPos, m_nBlockSize );//连续块的第一个块中nOccupyBlockSize存放的是连续块的个数

			}
			else
			{
				SetData(m_pCurrentBlock, -1, pPos, m_nBlockSize );//连续块的非第一个块中nOccupyBlockSize存放的是-1
			}
			
			m_pCurrentBlock = m_pCurrentBlock->pNext;
			pPos += m_nBlockSize;
		}
		SetData(m_pCurrentBlock, -1, pPos, len - m_nBlockSize *(nBlockNum - 1)  ); 
		m_pCurrentBlock = m_pCurrentBlock->pNext;
	}
	

	//计算使用最高峰值
	int nOccupyBlocks = (m_nMemoryTotalSize / m_nBlockSize)  - m_nFreeBlock;
	if( nOccupyBlocks  >  m_nMaxUsingBlocks )
	{
		m_nMaxUsingBlocks = nOccupyBlocks;
	}
	return emMemNoERROR;
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
EmMemoryError CMemoryManage::GetData(char *pdata, char *pout, int &len)
{
	if(m_bReInting)
	{
		return emMemErrReIniting;
	}

	if( NULL == pdata || NULL == pout )
	{
		pdata = NULL;
		pout = NULL;
		len = 0 ;
		return emMemErrNotFound;
	}


	char *pGetOut = pout;

	PTMemBlock pBlock = FindPos(pdata);
	if( NULL != pBlock )
	{
		int nBlocks		= 0;
		int nDataSize	= 0;
		GetData(pBlock, pGetOut, nBlocks, nDataSize);
		pGetOut += nDataSize;
		

		

		if( 1 == nBlocks )
		{
			len = pGetOut - pout;
			return emMemNoERROR;
		}
		else if( nBlocks > 1 )
		{
			int nCopyBlocks  = 0;
			for( int i = 1; i < nBlocks; i++ )//已经取过一次数据所以 i=1
			{
				pBlock = pBlock->pNext;
				GetData(pBlock, pGetOut, nCopyBlocks, nDataSize);
				pGetOut += nDataSize;
			}

			len = pGetOut - pout;
			return emMemNoERROR;
		}
		else
		{
			pout = NULL;
			len = 0 ;
			return emMemErrNotFound;
		}		
	}

	pout = NULL;
	len = 0 ;
	return emMemErrNotFound;
}

/*=============================================================================
函 数 名:  CheckMemorySize
功    能:  检查内存是否够
参    数:  [in]len 要存入内容的大小    [out]numblock 需要分配的内存块个数
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2010/12/17  4.0     沈  钦    创建
    =============================================================================*/
EmMemoryError CMemoryManage::CheckMemorySize(int len, int &blockcount)
{
	if( len > m_nMemoryTotalSize )
	{
		return emMemErrNotEnoughError;
	}
	
	int nBlock = len / m_nBlockSize;
	if( nBlock * m_nBlockSize < len ) 
	{
		nBlock++;
	}
	
	if( m_nFreeBlock < nBlock  )
	{
		return emMemErrNotEnoughError;
	}

	blockcount = nBlock ;

	return emMemNoERROR;
}


/*=============================================================================
函 数 名:  FindPos
功    能:  找内存
参    数:  [in]point 要找的内存指针
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2010/12/17  4.0     沈  钦    创建
    =============================================================================*/
PTMemBlock CMemoryManage::FindPos(char *point)
{
	int nBlockCount = m_nMemoryTotalSize / m_nBlockSize;
	for( int i = 0; i < nBlockCount; i++ )
	{
		if( ( (PTMemBlock)(m_pMemBlockStart + i) )->pBlock == point )
		{
			return ( (PTMemBlock)(m_pMemBlockStart + i) );
		}
	}
	return NULL;
}
