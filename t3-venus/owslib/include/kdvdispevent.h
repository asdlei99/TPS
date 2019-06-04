/*=======================================================================
模块名      : CKdvDispEvent
文件名      : kdvdispevent.h
相关文件    : 
文件实现功能: 各接口基类，主要用于分发消息
作者        : 王廖荣
版本        : V4.0  Copyright(C) 2003-2006 KDC, All rights reserved.
-------------------------------------------------------------------------
修改记录:
日  期      版本  修改人  修改内容
2006/08/22  3.0   王廖荣    创建
2013/11/03  4.0   刘德印    linux平台移植 fcgi消息通信逻辑扩展
=======================================================================*/
#ifndef __DISPEVENT_H__
#define __DISPEVENT_H__

#define TYPE_CMESSAGE  0         // 一般的CMessage消息
#define TYPE_TPMSG     1         // 收发的消息为CTPMSG ,需要进行消息类型的转换

class CKdvDispEvent
{
public:
    typedef void(CKdvDispEvent::*DISPEVENT_PFUN)(const CMessage & cMsg);
    typedef void(CKdvDispEvent::*DISPEVENT_REQ_PFUN)(const boost::any& arg);		//by ldy 2013.11.03扩展
public:
    CKdvDispEvent();
    virtual ~CKdvDispEvent();
    // 判断一消息是否在本类中注册过
    BOOL HasRegEvent(u16 wEvent) const;
    // 分发消息，引起相对应的类的函数的调用，各子类完成自已的调用
    virtual void DispEvent(const CMessage &cMsg) = 0;

	// 判断一消息是否在本类中注册过
    BOOL HasRegReqEvent(u16 wEvent) const;
	// 分发消息，引起相对应的类的函数的调用，各子类完成自已的调用
	virtual void DispReqEvent( u16 wEvent, const boost::any& arg ) = 0;

    // 消息超时的响应，暂时未作超时机制
    //virtual void OnTimeOut(u16 wEvent) = 0;

protected:
    // 将一个消息和其处理函数注册进来
    void RegDispFunPointer(u16 wEvent, DISPEVENT_PFUN pFun);
    // 清空掉所有注册的信息
    void ClearDisp();

    // 将一个消息和其处理函数注册进来
    void RegDispReqFunPointer(u16 wEvent, DISPEVENT_REQ_PFUN pFun);

protected:
	// 4.0 修改为只是用事件的Id
	std::map<u16, DISPEVENT_PFUN> m_mappFun;			//用于回应的分发		ums->业务类
	std::map<u16, DISPEVENT_REQ_PFUN> m_mappReqFun;		//用于请求消息发送的映射	fcgi->业务类  by ldy 2013.11.03扩展

};

//注册回应消息映射
#define REG_PFUN(event, fun)	\
    RegDispFunPointer(event, (void(CKdvDispEvent::*)(const CMessage &cMsg))fun);

//分发消息映射
#define DISP_FUN(clsName, cMsg)	\
if(m_mappFun.find(cMsg.event) != m_mappFun.end())	\
{	\
   (this->*(void(clsName::*)(const CMessage &cMsg))(m_mappFun[cMsg.event]))(cMsg);	\
}

//注册请求消息映射		by ldy 2013.11.03扩展
#define REG_REQ_PFUN(event, fun)	\
RegDispReqFunPointer(event, (void(CKdvDispEvent::*)(const boost::any& arg))fun);

//分发消息映射
#define DISP_REQ_FUN(clsName, event, arg )	\
	if(m_mappReqFun.find(event) != m_mappReqFun.end())	\
{	\
	   (this->*(void(clsName::*)(const boost::any& arg))(m_mappReqFun[event]))( arg );	\
}

#endif