/*****************************************************************************
模块名      : CUmcAddrbookCtrl
文件名      : umcaddrbookctrl.h
相关文件    : 
文件实现功能: 地址簿业务类
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2014/08/20  1.0         石城        创建
******************************************************************************/
#ifndef UMCADDRBOOKCTRL_H
#define UMCADDRBOOKCTRL_H

class CUmcAddrbookCtrl : public CKdvDispEvent, public ISingleTon<CUmcAddrbookCtrl>
{
public:
	CUmcAddrbookCtrl();
	virtual ~CUmcAddrbookCtrl();

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
	----------------function that handle msg from server:begin----------------------
	*******************************************************************************/

	/**
	* 功能:	全局地址簿回复
	* @return  void
	* @event ev_umsGetRegInfo_UmsRspEx
	*/
	void OnAddrbookGlobleUmsRsp( const CMessage& cMsg );

	void OnAddrbookGlobleCnsRsp( const CMessage& cMsg );

	void OnAddrbookGlobleMtRsp( const CMessage& cMsg );
	
	void OnAddrbookGlobleMcuRsp( const CMessage& cMsg );
	

	void OnLinkBreak( const CMessage& cMsg );

	/*******************************************************************************
	----------------function that handle msg from server:end----------------------
	*******************************************************************************/

private:
	/*******************************************************************************
	----------------function that handle msg from client:begin----------------------
	*******************************************************************************/
	/**
	* 功能:	全局地址簿刷新请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnAddrbookGlobleRefreshReq(const boost::any& arg);

	/**
	* 功能:	全局地址簿获取请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnAddrbookGlobleGetReq(const boost::any& arg);

	/**
	* 功能:	本地地址簿条目添加请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnAddrbookItemAddReq(const boost::any& arg);

	/**
	* 功能:	本地地址簿条目修改请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnAddrbookItemModReq(const boost::any& arg);
	
	/**
	* 功能:	本地地址簿条目删除请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnAddrbookItemDelReq(const boost::any& arg);

	/**
	* 功能:	本地地址簿条目获取请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnAddrbookItemGetReq(const boost::any& arg);

	/**
	* 功能:	本地地址簿条目和组获取请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnAddrbookItemgroupGetReq(const boost::any& arg);

	/**
	* 功能:	本地地址簿条目和组搜索请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnAddrbookItemgroupSearchReq(const boost::any& arg);

	/**
	* 功能:	本地地址簿条目数量请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnAddrbookItemNumberReq(const boost::any& arg);

	/**
	* 功能:	本地地址簿组获取请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnAddrbookGroupGetReq(const boost::any& arg);
	
	/**
	* 功能:	本地地址簿组添加请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnAddrbookGroupAddReq(const boost::any& arg);

	/**
	* 功能:	本地地址簿组修改请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnAddrbookGroupModReq(const boost::any& arg);

	/**
	* 功能:	本地地址簿组删除请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnAddrbookGroupDelReq(const boost::any& arg);

	/**
	* 功能:	本地地址簿条目-组关系添加请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnAddrbookIgAddReq(const boost::any& arg);

	/**
	* 功能:	本地地址簿条目-组关系删除请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnAddrbookIgDelReq(const boost::any& arg);

	/**
	* 功能:	本地地址簿组-组关系添加请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnAddrbookGgAddReq(const boost::any& arg);

	/**
	* 功能:	本地地址簿组-组关系删除请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnAddrbookGgDelReq(const boost::any& arg);
	

	/*******************************************************************************
	----------------function that handle msg from client:end----------------------
	*******************************************************************************/

private:
	void  BuildEventsMap();
	void  BuildReqEventsMap();
	
	void ClearData();

	/**
	* 功能:	获取条目信息（根据别名类型->返回对应的字符串）
	* @param tTPAlias：别名，pChName：名称，pChNumber：号码，pChIp：ip
	* @return  void
	* @remarks	参数为前端传递过来的json数据
	*/
	void GetItemInfo( TTPAlias tTPAlias, char *pChName, char *pChNumber, char *pChIp );

	/**
	* 功能:	更新本地地址簿的在线、类型状态
	* @param 
	* @return  void
	*/
	void updAddrbookLocalState();

private:
	////////////////////data begin/////////////////////////////////////////////////////

	BOOL32			m_bIsEndSip;			//sip地址是否接收结束
	BOOL32			m_bIsEndGk;				//Gk地址是否接收结束

	////////////////////data end///////////////////////////////////////////////////////
};

#endif