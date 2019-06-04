/*=======================================================================
模块名      : 终端控制台
文件名      : MsgDriver.h
相关文件    : 
文件实现功能: 消息驱动器
作者        : 熊广化
版本        : V3.0  Copyright(C) 1997-2003 KDC, All rights reserved.
-------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2003/12/22  3.0         熊广化      创建
2003/03/02	3.0			熊广化		化简
2004/08/23  3.5         李洪强      规范代码，增加CDispEvent类
2013/11/03  4.0         刘德印      linux平台移植 fcgi消息通信逻辑扩展
=======================================================================*/
#ifndef MSGDRIVER_H
#define MSGDRIVER_H

class CMsgDriver : public ISingleTon<CMsgDriver>
{
public:
    CMsgDriver();
    ~CMsgDriver();
    // 得到发送消息指针
    CMessage* GetCMsgPtr(BOOL32 bClear = TRUE);
	// 得到发送终端消息的指针
	CTpMsg* GetKdvMsgPtr(BOOL32 bClear = TRUE);
    // 发送命令型消息 可发送普通CMessage或CMtMsg类型的消息
    virtual u16 PostMsg(u32 dwType = TYPE_CMESSAGE);
    // 发送请求型消息，暂时没有超时功能
    u16 PostCommand(CKdvDispEvent *pDispEvent, u16 dwWaitEvent,  u32 dwType = TYPE_CMESSAGE, u32 dwTimeOut = 1500);
    // 注册一个处理消息的类的指针
    void RegHandler(CKdvDispEvent* const pDispEvnet);
    // 注销一个处理消息的类的指针
    void UnregHandler(CKdvDispEvent* const pDispEvnet);
    // 清空所有注册的类的指针
    void ClearHandler();

	void SetSndInstID( u32 dwDstInstID );
	u32  GetSndInstID();
	
	void SetAppID( u32 dwAppID ){ m_dwAppID = dwAppID;};					//源（即客户端）APP ID
	u32  GetAppID(){ return m_dwAppID;};

	void SetDesAppID( u32 dwDesAppID ){ m_dwDesAppID = dwDesAppID;};		//端（即服务器 目的）APP ID
	u32  GetDesAppID(){ return m_dwDesAppID;};

	BOOL PostEvent( u32 dwEvent, const boost::any& arg );

	void ReleaseLock();

public:
	void MessageProc(/*CTpMsg *const ptMsg*/);

private:
	// 清空等待的消息
    void ClearWaiting();

protected:
    CTpMsg       m_cKdvMsg;             // 用于发送 tp消息的消息结构
	CMessage	 m_cMsg;				//用于发送其他非终端消息的消息结构
	
private:
    static vector<CKdvDispEvent*> m_vpDispEvent;	// 消息分发表
    u16     m_dwWaitingEvents;						// 正在等待应答的消息
    CKdvDispEvent      *m_pCurDispEvent;			// 正在处理的消息对应的响应类的指针
	u32             m_dwInstID;						//实例ID
	u32             m_dwAppID;						//源APP ID
	u32             m_dwDesAppID;					//目的APP ID
	SEMHANDLE		m_hSem;							//与web前台通信锁，用于保持与浏览器的通信，不至于因postMsg而断开
};

#define PTR_MSGDRIVER CMsgDriver::GetSingletonPtr()

#endif //MSGDRIVER_H
