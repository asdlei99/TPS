// MemManger.cpp: implementation of the CMemManger class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "memmanger.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

template<> CMemoryManager* CSingleton<CMemoryManager>::m_psSingleton  = NULL;

CMemoryManager::CMemoryManager(int iItemSize,int iItemCount)
{
	m_WaitEvent =  ::CreateEvent(NULL,TRUE,FALSE,NULL);
	InitializeCriticalSection(&m_lock);
	
	if (!Init(iItemSize,iItemCount))
		AfxMessageBox(_T("自定义内存区开辟失败！"));
};

CMemoryManager::~CMemoryManager()
{
	//::GlobalUnlock(hData);
	::GlobalFree(pData);
	DeleteCriticalSection(&m_lock); 
	CloseHandle(m_WaitEvent);
};

//初始化内存区（预留内存区）
//iItemSize - 每块字节数 iItemCount - 总块数
BOOL CMemoryManager::Init(int iItemSize,int iItemCount)
{
	int iIndexAddr;
	
	m_ItemSize  = iItemSize;
	m_ItemCount = iItemCount;
	m_BlockSize = iItemSize + 9;
	
	
	pData = ::GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,
		4 + iItemCount * (iItemSize + 9) +
        iItemCount * 4);
	if (!pData) return FALSE;
	
	//初始化空闲块信息
	*((int *)pData) = iItemCount;
	m_FreeIndexAddr = (int)pData + 4 + iItemCount * (iItemSize + 9);
	for(int i=1;i<=m_ItemCount;i++)
	{
		*((int *)(m_FreeIndexAddr + (i-1)*4)) = i; //空闲索引
		iIndexAddr = (int)pData + 4 + (i - 1) * m_BlockSize + m_ItemSize + 1;
		*((int *)iIndexAddr) = i;//各块索引
	}
	
	return TRUE;
}

void CMemoryManager::Lock()
{
	EnterCriticalSection(&m_lock); 
}

void CMemoryManager::UnLock()
{
	LeaveCriticalSection(&m_lock); 
}

//申请内存引用
LPVOID CMemoryManager::New(int Len)
{
	BOOL blnGet = FALSE;
	int iIndex;
	int iNext = 0;
	int iNeedCount;
	int iFreeCount;
	int iRefAddr;
	
	LPVOID p = NULL;
	
	//计算需要申请的块数
	iNeedCount = (int)(Len / m_ItemSize);
	if (iNeedCount * m_ItemSize < Len) iNeedCount++;
	
	while(!blnGet)
	{
		//检查是否存在足够空闲块
		Lock();
        iFreeCount = *((int *)pData);
		if (iFreeCount * m_ItemSize < Len) 
		{
			//空间不足，进入等待
			UnLock();
			WaitForSingleObject(m_WaitEvent,200);
		}
		else
		{
			for(int i=iFreeCount;i>=1;i--)
			{
				//读取空闲块索引
				iIndex = *((int *)(m_FreeIndexAddr + (i-1)*4));
				iRefAddr = (int)pData + 4 + (iIndex - 1) * m_BlockSize + m_ItemSize;
				
				//写入占用标志
				*((unsigned char *)iRefAddr) = 1;
				
				//减少空闲总数
				*((int *)pData) = *((int *)pData) - 1;
				
				//写下一块索引
				*((int *)(iRefAddr+5)) = iNext;
				
				//获取块首地址
				p = (LPVOID)(iRefAddr - m_ItemSize);
				
				iNeedCount--;
				if (iNeedCount == 0) break;
				
				//保存当前块索引
				iNext = iIndex;
			}
			
			UnLock();
			blnGet = TRUE;
		}
	}
	
	return p;
}

//释放内存引用
BOOL CMemoryManager::Delete(LPVOID p)
{
	unsigned char *pRef;
	int  *pNext;
	int  iNext = 1;
	
	if (p == NULL) return TRUE;
	
	while(iNext >= 1)
	{
		//清除数据块内容
		//ZeroMemory(p,m_ItemSize);
		
		Lock();
		
		//清除引用
		pRef = (unsigned char *)((int)p + m_ItemSize);
		//增加空闲数 写空闲索引
		if (*pRef != 0)
		{
			int *pFree = (int *)pData;
			*pFree = *pFree + 1;
			*((int *)(m_FreeIndexAddr + (*pFree - 1) * 4)) = *((int *)((int)p + m_ItemSize + 1));
		}
		*pRef = 0;
		//读取并清除下一块索引
		pNext = (int *)((int)p + m_ItemSize + 5);
		iNext = *pNext;
		*pNext = 0;
		
		UnLock();
		
		//计算下一块地址
		if(iNext >= 1)
			p = (LPVOID)((int)pData + 4 + (iNext - 1) * (m_ItemSize + 5));
	}
	
	p = NULL;
	return TRUE;
}

//获取数据块字节数
int CMemoryManager::GetItemSize()
{
	return m_ItemSize;
}

//获取总块数
int CMemoryManager::GetItemCount()
{
	return m_ItemCount;
}

//获取总空闲数
int CMemoryManager::GetFreeCount()
{
	int iCnt;
	Lock();
	CopyMemory(&iCnt,pData,4);
	UnLock();
	return iCnt;
}