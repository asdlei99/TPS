#include "owslib.h"

//////////////////////////////////////////////////////////////////////////
// CMsgQueue
// 
CMsgQueue::CMsgQueue()
{
}

CMsgQueue::~CMsgQueue()
{
    Clear();
}

/*=============================================================================
  函 数 名： PushMsg
  功    能： 添加一条消息到消息队列
  算法实现： 
  全局变量： 
  参    数： CMessage* const pMsg  消息指针
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/12     3.5		王慧琛                  规范化
=============================================================================*/
void CMsgQueue::PushMsg(CMessage* const pMsg)
{
    CMessage cMsg;
    cMsg = *pMsg;
    cMsg.content = new u8[pMsg->length];
    memcpy(cMsg.content, pMsg->content, pMsg->length);
    m_queMsg.push(cMsg);
}

/*=============================================================================
  函 数 名： PopMsg
  功    能： 从消息队列里弹出一条消息，并添加到目标队列里
  算法实现： 
  全局变量： 
  参    数： CMsgQueue &cOutQue 目标队列
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/12     3.5		王慧琛                  规范化
=============================================================================*/
void CMsgQueue::PopMsg(CMsgQueue &cOutQue)
{
    CMessage *pMsg = &m_queMsg.front(); 
    cOutQue.PushMsg(pMsg);
    delete []pMsg->content;
    m_queMsg.pop();
}

/*=============================================================================
  函 数 名： Clear
  功    能： 清空队列
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/12     3.5		王慧琛                  规范化
=============================================================================*/
void CMsgQueue::Clear()
{
    while (!m_queMsg.empty()) 
    {
        CMessage *pMsg = &m_queMsg.front();
        delete []pMsg->content;
        m_queMsg.pop();
    }
}

/*=============================================================================
  函 数 名： IsEmpty
  功    能： 判断消息队列是否为空
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： BOOL 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/12     3.5		王慧琛                  规范化
=============================================================================*/
BOOL CMsgQueue::IsEmpty()
{
    return m_queMsg.empty();
}

//////////////////////////////////////////////////////////////////////////
//  COspAppBase
//
COspAppBase::COspAppBase()
{
    m_dwNodeId = INVALID_NODE;
}

COspAppBase::~COspAppBase()
{
}

/*=============================================================================
  函 数 名： ClearOspMsg
  功    能： 系统退出时清空OSP消息队列，防止出现刷新IE时的过期OSP消息
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/12     3.5		王慧琛                  规范化
=============================================================================*/
void COspAppBase::ClearOspMsg()
{
    CMsgHandler *pHandler = CMsgHandler::GetMsgHandler();
    if (pHandler) 
    {
        pHandler->ClearQueue();
    }
}


////////////////////////////////////////////////////////////////////////////////
// 全局Osp应用程序对象   
zTemplate<CMsgHandler, 1/*MAX_USERNUM*/, COspAppBase> g_MsgRecApp;		//开启多实例并发处理多用户    最大用户数为ums中用户个数
////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// CMsgRecver
// 
CMsgHandler* CMsgHandler::s_pMsgHandler = NULL;
CMsgHandler::CMsgHandler()
{
	s_pMsgHandler = this;
}

CMsgHandler::~CMsgHandler()
{
    s_pMsgHandler = NULL;
	ClearQueue();
}

/*=============================================================================
  函 数 名： PopAllMsg
  功    能： 清空OSP消息队列，并将其转入工作消息队列
  算法实现： 
  全局变量： 
  参    数： CMsgQueue &cMsgQue
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/12     3.5		王慧琛                  规范化
=============================================================================*/
void CMsgHandler::PopAllMsg(CMsgQueue &cMsgQue)
{
    while (!m_cMsgQue.IsEmpty()) 
    {
        m_cMsgQue.PopMsg(cMsgQue);
    }
}

/*=============================================================================
  函 数 名： ClearQueue
  功    能： 清空OSP消息队列，主要用于系统退出时
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/12     3.5		王慧琛                  规范化
=============================================================================*/
void CMsgHandler::ClearQueue()
{
    m_cMsgQue.Clear();
}

void CMsgHandler::InstanceEntry( CMessage *const pMsg )
{
    if (pMsg->type !=3)				//异步消息
    {
        if(m_cMsgQue.Size() == 0)	//原OSP消息队列为空时，通知本地消息队列再次来取消息
        {
            m_cMsgQue.PushMsg(pMsg);
			if ( NULL != PTR_MSGDRIVER )
			{
 				//CTpMsg kdvMsg( pMsg );
 				PTR_MSGDRIVER->MessageProc(/*&kdvMsg*/);
			}
        }
        else						//本地消息队列正在取消息时，在同时收到多个OSP消息时，有可能会走到这一步
        {
            m_cMsgQue.PushMsg(pMsg);
        }
    }
}

void CMsgHandler::DaemonInstanceEntry(CMessage *const pcMsg, CApp* pcApp )
{
}