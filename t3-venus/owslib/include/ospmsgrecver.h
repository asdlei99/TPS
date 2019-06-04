/*=======================================================================
模块名      : ospmsgrecver.h
文件名      : ospmsgrecver.h
相关文件    : 
文件实现功能: Osp App Instance和CMsgQueue消息队列处理
作者        : 王廖荣
版本        : V4.0  Copyright(C) 2003-2006 KDC, All rights reserved.
-------------------------------------------------------------------------
修改记录:
日  期      版本  修改人  修改内容
2006/08/22  3.0   王廖荣    创建
2013/11/03  4.0   刘德印    linux平台移植 fcgi消息通信逻辑扩展
=======================================================================*/
#ifndef _OSPMSGRECVER_H
#define _OSPMSGRECVER_H

#define INSTANCE_COUNT	1	// 接收消息的实例的数目

/************************************************************************/
/*                        消息队列定义                                  */
/************************************************************************/
class CMsgQueue
{
public:
    CMsgQueue();
    ~CMsgQueue();
    // 将一条消息压入队列中
    void PushMsg(CMessage* const pMsg);
    // 从队列中取出一条消息
    void PopMsg(CMsgQueue &cOutQue);
    // 从队列中弹出一条消息
    void Pop() 
    { 
        CMessage *pMsg = &m_queMsg.front(); 
        delete []pMsg->content;
        m_queMsg.pop(); 
    }
    // 队列是否为空
    BOOL IsEmpty();
    // 清空队列
    void Clear();
    // 得到队列最前面元素
    CMessage& Front() { return m_queMsg.front();}
    // 得到队列的大小
    s32 Size() { return m_queMsg.size(); }
private:
    queue<CMessage> m_queMsg;
};


class CMsgHandler : public CInstance 
{
public:
	CMsgHandler();
	virtual ~CMsgHandler();

	virtual void InstanceEntry(CMessage *const ptMsg);
    virtual void DaemonInstanceEntry(CMessage *const pcMsg, CApp* pcApp );

    // 提取缓冲的消息队列(线程安全)
    void PopAllMsg(CMsgQueue &cMsgQue);
    // 清空消息队列
    void ClearQueue();
    // 同步消息反馈
    u32 PutSyncAck(const void* pAckBuf=NULL, u16 u16AckSize=0);

	
public:
	static CMsgHandler* GetMsgHandler() { return s_pMsgHandler; }

protected:
    // 消息缓冲队列及其保护关键区
    CMsgQueue       m_cMsgQue;
private:
    static CMsgHandler *s_pMsgHandler;
};

class COspAppBase
{
public:
    COspAppBase();
    ~COspAppBase();
    // 获取当前连接节点的标识(线程安全)
    u32 GetNodeId(){ return m_dwNodeId;}
    // 设置当前连接节点的标识(线程安全)
    void SetNodeId(u32 dwId) { m_dwNodeId = dwId; }
    //清空消息队列
    void ClearOspMsg();
protected:
    u32                     m_dwNodeId;     // 当前建立连接的节点标识
};

////////////////////////////////////////////////////////////////////////////////
// 全局Osp应用程序对象
extern zTemplate<CMsgHandler, 1/*MAX_USERNUM*/, COspAppBase> g_MsgRecApp;

#endif