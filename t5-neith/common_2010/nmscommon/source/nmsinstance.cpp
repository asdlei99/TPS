#include "StdAfx.h"
#include "nmsinstance.h"
#include "NmsPrint.h"

CInstanceAssist* CNmsInstance::m_pBaseIntanceAssist = NULL;

// 监控联动添加文件
/*---------------------------------------------------------------------
* 函 数 名：CreateInstanceAssist
* 功    能：创建一个Assist（原型模式）
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/20	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
BOOL32 CNmsInstance::CreateInstanceAssist()
{
	if ( m_pBaseIntanceAssist == NULL )
	{
		return FALSE;
	}
	m_pAssist = m_pBaseIntanceAssist->Clone();
	return TRUE;
}

/*---------------------------------------------------------------------
* 函 数 名：SetInstanceAssistType
* 功    能：设置原型
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/20	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
BOOL32 CNmsInstance::SetInstanceAssistType( CInstanceAssist* pType )
{
	m_pBaseIntanceAssist = pType;
	return TRUE;
}

/*---------------------------------------------------------------------
* 函 数 名：CheckMsg
* 功    能：对数据进行一些常规的检测
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/20	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
BOOL32 CInstanceAssist::CheckMsg( CMessage *const pMsg )
{
	return TRUE;
}

/*---------------------------------------------------------------------
* 函 数 名：SetInstanceParam
* 功    能：连接的时候设置参数
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/23	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
void CInstanceAssist::SetInstanceParam(u32 dwDstAppId, u32 dwDstNode, u32 dwSrcAppId, u32 dwSrcNode )
{
	m_dwDstAppId	= dwDstAppId;
	m_dwDstNode		= dwDstNode;
	m_dwSrcAppId	= dwSrcAppId;
	m_dwSrcNode		= dwSrcNode;
	m_bConnected	= TRUE;
	int nCode = OspNodeDiscCBRegQ( m_dwDstNode, HIWORD16(m_dwSrcAppId), LOWORD16(m_dwSrcAppId) );
}

/*---------------------------------------------------------------------
* 函 数 名：
* 功    能：
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/20	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
BOOL32 CInstanceAssist::PostMsg( u16 wEvent, void* pBody /* = NULL */, u32 dwBodyLen /* = 0 */ )
{
	if ( m_bConnected == TRUE )
	{
		int nCode = OspPost( m_dwDstAppId ,wEvent, pBody, dwBodyLen, m_dwDstNode,m_dwSrcAppId, m_dwSrcNode );
		// 发送消息
		return TRUE;
	}	
	return FALSE;
}

/*---------------------------------------------------------------------
* 函 数 名：DaemonInstanceEntry
* 功    能：处理接入信息
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/11	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
void CNmsInstance::DaemonInstanceEntry( CMessage *const pMsg, CApp* )
{
	try
	{
		if ( CanConnect( pMsg ) == TRUE )
		{
			OspPost( MAKEIID( GetAppID(), CInstance::PENDING ), pMsg->event, pMsg->content, pMsg->length, pMsg->dstnode, pMsg->srcid, pMsg->srcnode );
		}	
	}
	catch ( ... )
	{

	}
}

/*---------------------------------------------------------------------
* 函 数 名：InstanceEntry
* 功    能：接收消息的总入口
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/11	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
void CNmsInstance::InstanceEntry( CMessage *const pMsg )
{
	try
	{
		// 发现没有对应的Assist对象，分配之
		if ( m_pAssist == NULL )
		{
			if ( CreateInstanceAssist() == FALSE )
			{
				CNmsPrint::Printf( "Default", "创建处理对象失败!\n" );
				return;
			}
		}
		m_pAssist->TransData( this, pMsg );
	}
	catch (...) // 一般会出现注册的Observer已经被外部delete了，比如注册的是一个窗口
	{
		OspPrintf( 1, 0, "Observer may be deleted \n" );
	}	
}

/*---------------------------------------------------------------------
* 函 数 名：CanConnect
* 功    能：给定一个链接的条件
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/24	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
BOOL32 CNmsInstance::CanConnect( CMessage *const pMsg )
{
	return TRUE;
}

/*---------------------------------------------------------------------
* 函 数 名：StartTimer
* 功    能：开启一个timer
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/09/09	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
BOOL32 CNmsInstance::StartTimer( u32 nTimer, long nMilliSeconds, u32 nPara /* = 0 */ )
{
	return SetTimer( nTimer, nMilliSeconds, nPara );
}

/*---------------------------------------------------------------------
* 函 数 名：StopTimer
* 功    能：停止一个timer
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/09/09	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
BOOL32 CNmsInstance::StopTimer( u32 nTimer )
{
	return KillTimer( nTimer );
}