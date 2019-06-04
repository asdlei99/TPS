/*=======================================================================
ģ����      : ospmsgrecver.h
�ļ���      : ospmsgrecver.h
����ļ�    : 
�ļ�ʵ�ֹ���: Osp App Instance��CMsgQueue��Ϣ���д���
����        : ������
�汾        : V4.0  Copyright(C) 2003-2006 KDC, All rights reserved.
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾  �޸���  �޸�����
2006/08/22  3.0   ������    ����
2013/11/03  4.0   ����ӡ    linuxƽ̨��ֲ fcgi��Ϣͨ���߼���չ
=======================================================================*/
#ifndef _OSPMSGRECVER_H
#define _OSPMSGRECVER_H

#define INSTANCE_COUNT	1	// ������Ϣ��ʵ������Ŀ

/************************************************************************/
/*                        ��Ϣ���ж���                                  */
/************************************************************************/
class CMsgQueue
{
public:
    CMsgQueue();
    ~CMsgQueue();
    // ��һ����Ϣѹ�������
    void PushMsg(CMessage* const pMsg);
    // �Ӷ�����ȡ��һ����Ϣ
    void PopMsg(CMsgQueue &cOutQue);
    // �Ӷ����е���һ����Ϣ
    void Pop() 
    { 
        CMessage *pMsg = &m_queMsg.front(); 
        delete []pMsg->content;
        m_queMsg.pop(); 
    }
    // �����Ƿ�Ϊ��
    BOOL IsEmpty();
    // ��ն���
    void Clear();
    // �õ�������ǰ��Ԫ��
    CMessage& Front() { return m_queMsg.front();}
    // �õ����еĴ�С
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

    // ��ȡ�������Ϣ����(�̰߳�ȫ)
    void PopAllMsg(CMsgQueue &cMsgQue);
    // �����Ϣ����
    void ClearQueue();
    // ͬ����Ϣ����
    u32 PutSyncAck(const void* pAckBuf=NULL, u16 u16AckSize=0);

	
public:
	static CMsgHandler* GetMsgHandler() { return s_pMsgHandler; }

protected:
    // ��Ϣ������м��䱣���ؼ���
    CMsgQueue       m_cMsgQue;
private:
    static CMsgHandler *s_pMsgHandler;
};

class COspAppBase
{
public:
    COspAppBase();
    ~COspAppBase();
    // ��ȡ��ǰ���ӽڵ�ı�ʶ(�̰߳�ȫ)
    u32 GetNodeId(){ return m_dwNodeId;}
    // ���õ�ǰ���ӽڵ�ı�ʶ(�̰߳�ȫ)
    void SetNodeId(u32 dwId) { m_dwNodeId = dwId; }
    //�����Ϣ����
    void ClearOspMsg();
protected:
    u32                     m_dwNodeId;     // ��ǰ�������ӵĽڵ��ʶ
};

////////////////////////////////////////////////////////////////////////////////
// ȫ��OspӦ�ó������
extern zTemplate<CMsgHandler, 1/*MAX_USERNUM*/, COspAppBase> g_MsgRecApp;

#endif