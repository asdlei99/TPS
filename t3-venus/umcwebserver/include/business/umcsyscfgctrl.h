/*****************************************************************************
模块名      : CUmcSysCfgCtrl
文件名      : umcsyscfgctrl.h
相关文件    : 
文件实现功能: 系统配置业务类
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2014/10/17  1.0         石城        创建
******************************************************************************/
#ifndef UMCSYSCFGCTRL_H
#define UMCSYSCFGCTRL_H


class CUmcSysCfgCtrl : public CKdvDispEvent, public ISingleTon<CUmcSysCfgCtrl>
{
public:
	CUmcSysCfgCtrl();
	virtual ~CUmcSysCfgCtrl();

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
	* 功能:	添加用户请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebAddUserReq(const boost::any& arg);

	/**
	* 功能:	修改密码请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebChangePwdReq(const boost::any& arg);

	/**
	* 功能:	删除用户请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebDelUserReq(const boost::any& arg);

	/**
	* 功能: 用户信息通知型请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebUserNtyReq(const boost::any& arg);

	/**
	* 功能: 网络服务器配置请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebIpCfgReq(const boost::any& arg);

	/**
	* 功能:	网络服务器配置通知型请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebIpCfgNtyReq(const boost::any& arg);

	/**
	* 功能: sip服务器配置请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebSipserverReq(const boost::any& arg);

	/**
	* 功能: gk服务器配置请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebGkserverReq(const boost::any& arg);

	/**
	* 功能:	sip服务器配置通知型请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebSipserverNtyReq(const boost::any& arg);

	/**
	* 功能:	gk服务器配置通知型请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebGkserverNtyReq(const boost::any& arg);
	

	/**
	* 功能:	时间同步至服务器请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebSetSysTimeReq(const boost::any& arg);	

	/**
	* 功能:	登录时服务器时间通知型请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebGetSysTimeNtyReq(const boost::any& arg);

	/**
	* 功能:	增/删/改 网管服务器信息请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
//	u16 OnUmcwebNMServerReq(const boost::any& arg);	

	/**
	* 功能:	网管服务器信息通知型请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
//	u16 OnUmcwebNMServerNtyReq(const boost::any& arg);
	
	/*******************************************************************************
	----------------function that handle msg from server:end----------------------
	*******************************************************************************/
	
private:
	/*******************************************************************************
	----------------function that handle msg from server:begin----------------------
	*******************************************************************************/

	/**
	* 功能:	增加用户通知（UMS->UMC）
	* @return  void
	* @event ev_UmsAddUser_Notify
	*/
	void OnAddUserNotify( const CMessage& cMsg );

	/**
	* 功能:	更新用户通知（UMS->UMC）
	* @return  void
	* @event ev_UmsUpdateUser_Notify
	*/
	void OnUpdateUserNotify( const CMessage& cMsg );

	/**
	* 功能:	删除用户通知（UMS->UMC）
	* @return  void
	* @event ev_UmsDelUser_Notify
	*/
	void OnDelUserNotify( const CMessage& cMsg );

	/**
	* 功能:	增加用户回复（UMS->UMC）
	* @return  void
	* @event ev_UMSAddUserRet
	*/
	void OnAddUserRsp( const CMessage& cMsg );

	/**
	* 功能:	增加用户回复（UMS->UMC）
	* @return  void
	* @event ev_UMSChangePWDRet
	*/
	void OnChangePWDRsp( const CMessage& cMsg );

	/**
	* 功能:	增加用户回复（UMS->UMC）
	* @return  void
	* @event ev_UMSDelUserRet
	*/
	void OnDelUserRsp( const CMessage& cMsg );

	/**
	* 功能:	网络服务器配置通知（UMS->UMC）
	* @return  void
	* @event ev_UmsIPCfg_Ind
	*/
	void OnIPCfgNty( const CMessage& cMsg );

	/**
	* 功能:	sip服务器配置通知（UMS->UMC）
	* @return  void
	* @event ev_umsreg_notify
	*/
	void OnSipserverNty( const CMessage& cMsg );

	/**
	* 功能:	gk服务器配置通知（UMS->UMC）
	* @return  void
	* @event ev_umsGKReg_notify
	*/
	void OnGkserverNty( const CMessage& cMsg );

	/**
	* 功能:	查询时间响应（UMS->UMC）
	* @return  void
	* @event ev_UmsGetSysTime_Rsp
	*/
	void OnUmsGetSysTimeRsp( const CMessage& cMsg );

	/**
	* 功能:	网管信息通知（UMS->UMC）
	* @return  void
	* @event ev_NMServer_nty
	*/
//	void OnNetMngNty( const CMessage& cMsg );

	/**
	* 功能:	添加网管服务器应答（UMS->UMC）
	* @return  void
	* @event ev_NMServerAdd_rsp
	*/
//	void OnAddNetMngRsp(const CMessage& cMsg);

	/**
	* 功能:	修改网管服务器应答（UMS->UMC）
	* @return  void
	* @event ev_NMServerMdy_rsp
	*/
//	void OnModifyNetMngRsp(const CMessage& cMsg);

	/**
	* 功能:	删除网管服务器应答（UMS->UMC）
	* @return  void
	* @event ev_NMServerDel_rsp
	*/
//	void OnDelNetMngRsp(const CMessage& cMsg);
	
	
	void OnLinkBreak( const CMessage& cMsg );

	/*******************************************************************************
	----------------function that handle msg from client:end----------------------
	*******************************************************************************/


private:
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
	* 功能:	清空数据
	* @return  无
	*/
	void ClearData();

public:
	void ShowSysCfginfo();

	/**
    * 功能:	 	        发送 添加/修改/删除 网管请求(fcgi -> ums)
	* @param [in]       网管信息
	* @return           u16 成功返回0, 失败返回非0错误码
	* @remarks 消息：   ev_NMServerAdd_req
	*/
//	u16  NetMngAddReq( const TTPNMServerCfg& tTPNMServerCfg );
//	u16  NetMngModifyReq( const TTPNMServerCfg& tTPNMServerCfg );
//	u16  NetMngDeleteReq( const TTPNMServerCfg& tTPNMServerCfg );

	//网管服务器信息请求(fcgi -> ums)
//	void NetMngInfoReq( vector<TTPNMServerCfg>& vecTTPNMServerCfg );
	//网管服务器信息通知(fcgi -> client)
//	void  NetMngInfoNty();

private:
	////////////////////data begin/////////////////////////////////////////////////////

	vector<CUserFullInfo> m_vecUser;			//用户列表
	TTPEthnetInfo   m_tEthnet;					//网络服务器信息
	TTPSipRegistrarCfg m_tSipRegCfg;			//sip服务器配置
	TTPGKCfg m_tGKRegCfg;						//gk服务器配置
	vector<TTPNMServerCfg> m_vecTTPNMServerCfg; //网管服务器信息

	////////////////////data end///////////////////////////////////////////////////////
};

#endif