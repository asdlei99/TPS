/*****************************************************************************
模块名      : CUmcSession
文件名      : umcsession.h
相关文件    : 
文件实现功能: 一个umc的会话,1.连接umc 2.监控整个连接过程，有断链则发出通知 3.控制所有直接和umc交互的接口（发送消息等）
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2014/08/11  1.0         石城        创建
******************************************************************************/
#ifndef UMCSSESSIONCTRL_H
#define UMCSSESSIONCTRL_H

#include "umcaddrbookctrl.h"
#include "umcconfinfoctrl.h"
#include "umcsyscfgctrl.h"
#include "umcconftemplatectrl.h"

class CUmcSessionCtrl : public CKdvDispEvent, public ISingleTon<CUmcSessionCtrl>
{
public:
	CUmcSessionCtrl();
	virtual ~CUmcSessionCtrl();

public:
	/**
	* 功能:	分发消息，引起相对应的类的函数的调用，各子类完成自已的调用
	* @param [in]  消息
	* @return  无
	* @remarks server->各个业务类(通过CMsgDriver转发)
	*/
	virtual void DispEvent(const CMessage &cMsg);

	/**
	* 功能:	分发消息，引起相对应的类的函数的调用，各子类完成自已的调用
	* @param [in]  消息
	* @return  无
	* @remarks client->各个业务类(通过CMsgDriver转发)
	*/
	virtual void DispReqEvent( u16 wEvent, const boost::any& arg );

private:
	/*******************************************************************************
	----------------function that handle msg from client:begin----------------------
	*******************************************************************************/

	/**
	* 功能:	请求连接DCS服务器请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnConnectUmsReq(const boost::any& arg);

	/**
	* 功能:	断链通知型请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	* @eg: "{\"event\":\"ev_dcweb_OSP_DISCONNECT_nty_req\"}"
	*/
	u16 OnLinkBreakReq(const boost::any& arg);

	/*******************************************************************************
	----------------function that handle msg from server:end----------------------
	*******************************************************************************/
	
private:
	/*******************************************************************************
	----------------function that handle msg from server:begin----------------------
	*******************************************************************************/

    void  OnConnectUmsRsp( const CMessage& cMsg );		//连接到DCS服务器回应
	void OnLinkBreak( const CMessage& cMsg );

	/*******************************************************************************
	----------------function that handle msg from client:end----------------------
	*******************************************************************************/

public:
	/**
	* 功能:	查询是否已连接
	* @return  TRUE 	已连接    FALSE	没有连接
    */
	BOOL IsConnected();

	CUmcConfinfoCtrl* GetUmcConfinfoCtrl(){ return m_pConfinfoCtrl; };
	CUmcSysCfgCtrl* GetUmcSysCfgCtrl(){ return m_pSysCfgCtrl; };
	CUmcConfTemplateCtrl* GetUmcConfTemplateCtrl(){ return m_pConfTemplateCtrl; };

private:
	/**
	* 功能:	初始化OSP,创建app 
	* @return  成功返回0，失败返回错误码  
	*/
	virtual u16 InitializeLib( u16 wAppID, u16 wDesAppID );

	/**
	* 功能:	建立与服务器的连接
	* @return  u16 成功返回0,失败返回非0错误码
	*/
	u16 ConnectToUms( string strUsr, string strPwd );

	/**
	* 功能:	断开与服务器的连接
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	在没有连接到服务器时调用此方法，不起任何作用
	*/
	u16 DisConnect() ; 
 
	/**
	* 功能:	注册msg from server消息
	* @return  无
	*/
	void  BuildEventsMap();

	/**
	* 功能:	注册msg from client消息
	* @return  无
	*/
	void  BuildReqEventsMap();
	
	/**
	* 功能:	注册打印消息
	* @return  无
	*/
	void  MappingEventName();

	/**
	* 功能:	清空数据
	* @return  无
	*/
	void ClearData();

public:
	BOOL m_bRefresh;		//是否需要即时推送前端

private:
	////////////////////data begin/////////////////////////////////////////////////////

	BOOL32 m_bLogin;        //是否已经登录

	/////////////////业务类////////////////////
	CUmcAddrbookCtrl *m_pAddrbookCtrl;
	CUmcConfinfoCtrl *m_pConfinfoCtrl;
	CUmcSysCfgCtrl *m_pSysCfgCtrl;
	CUmcConfTemplateCtrl *m_pConfTemplateCtrl;

	////////////////////data end///////////////////////////////////////////////////////
};


#define PTR_SESSION    CUmcSessionCtrl::GetSingletonPtr()     //Session实例指针
#endif