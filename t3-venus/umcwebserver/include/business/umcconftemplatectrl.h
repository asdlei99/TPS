/*****************************************************************************
模块名      : CUmcConfTemplateCtrl
文件名      : umcconftemplatectrl.h
相关文件    : 
文件实现功能: 会议模板业务类
作者        : 徐华秀
版本        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2014/11/19  1.0         徐华秀      创建
******************************************************************************/
#ifndef UMCCONFTEMPLATECTRL_H
#define UMCCONFTEMPLATECTRL_H


class CUmcConfTemplateCtrl : public CKdvDispEvent, public ISingleTon<CUmcConfTemplateCtrl>
{
public:
	CUmcConfTemplateCtrl();
	virtual ~CUmcConfTemplateCtrl();

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

	u16 GetResUsedCount(){ return m_wResUsedCount; };

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

private:
	/*******************************************************************************
	----------------function that handle msg from client:begin----------------------
	*******************************************************************************/

	/**
	* 功能:		添加会议模板请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebAddConftemplateReq(const boost::any& arg);

	/**
	* 功能:		更新会议模板请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebUpdateConftemplateReq(const boost::any& arg);

	/**
	* 功能:		删除会议模板请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebDelConftemplateReq(const boost::any& arg);

	/**
	* 功能:		删除全部模板请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebDelAllConftempReq(const boost::any& arg);

	/**
	* 功能:		召开会议请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebStartConfTemplateReq(const boost::any& arg);

	/**
	* 功能:		刷新会议模板列表通知型请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebRefreshConftempListNtyReq(const boost::any& arg);

	/**
	* 功能:		刷新会议模板具体信息通知型请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebRefreshConftempInfoNtyReq(const boost::any& arg);

	/**
	* 功能:		刷新会议模板与会会场列表通知型请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebRefreshConftempMeetNameListNtyReq(const boost::any& arg);

	/**
	* 功能:		刷新会议模板轮询列表通知型请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebRefreshConftempPollingListNtyReq(const boost::any& arg);

	/**
	* 功能:		刷新会议模板讨论列表通知型请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebRefreshConftempDiscussListNtyReq(const boost::any& arg);

	/**
	* 功能:		当前资源数通知型请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebConfBasUsedNtyReq(const boost::any& arg);

	/**
	* 功能:		获取预约会议通知型请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebConfmngListconfbookGetReq(const boost::any& arg);

	/**
	* 功能:		校验模板名称、号码是否重复 请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebCheckConftempRepeatReq(const boost::any& arg);

	/*******************************************************************************
	----------------function that handle msg from client:end------------------------
	*******************************************************************************/
	
private:
	/*******************************************************************************
	----------------function that handle msg from server:begin----------------------
	*******************************************************************************/

	/**
	* 功能		添加会议模板列表的通知(ums -> fcgi)
	* @return	void
	* @event	evtp_AddConftemplate_Notify
	*/
	void OnAddConfTempNotify( const CMessage& cMsg );

	/**
	* 功能		修改会议模板列表的通知(ums -> fcgi)
	* @return	void
	* @event	evtp_Updateconftemplate_Notify
	*/
	void OnUpdateConfTempNotify( const CMessage& cMsg );

	/**
	* 功能		删除会议模板列表的通知(ums -> fcgi)
	* @return	void
	* @event	evtp_Delconftemplate_Notify
	*/
	void OnDelConfTempNotify( const CMessage& cMsg );

	/**
	* 功能		删除全部模板消息应答(ums -> fcgi)
	* @return	void
	* @event	ev_del_all_conftemp_rsp
	*/
	void OnDelAllConfTempRsp( const CMessage& cMsg );

	/**
	* 功能		请求添加、删除、修改会议模板的回复(ums -> fcgi)
	* @return	void
	* @event	evpt_OperatorConfTemplate_Ret
	*/
	void OnOperateConfTempRsp( const CMessage& cMsg );

	/**
	* 功能		召开会议结果(ums -> fcgi)
	* @return	void
	* @event	evtp_StartConfTemplate_Ret
	*/
	void OnStartConfTemplateRsp( const CMessage& cMsg );

	/**
	* 功能		更新会议模板资源占用数(ums -> fcgi)
	* @return	void
	* @event	ev_conf_bas_used_nty
	*/
	void OnUpdateResUsedCountNotify( const CMessage& cMsg );

	void OnLinkBreak( const CMessage& cMsg );

	/*******************************************************************************
	----------------function that handle msg from server:end------------------------
	*******************************************************************************/

private:
	/*******************************************************************************
	----------------function that post msg to server:begin--------------------------
	*******************************************************************************/

	/**
    * 功能:				添加会议模板(fcgi -> ums)
	* @param [in]		tConfTemp 会议模板 
	* @return			u16 成功返回0, 失败返回非0错误码
	* @remarks 消息：	fcgi->ums: evtp_AddConfTemplate_req
	                    应回复 ums->fcgi: evpt_OperatorConfTemplate_Ret
	                    若成功，则又有 ums->fcgi: evtp_AddConftemplate_Notify
	*/
	u16 AddConfTemplateReq( const TTPConfTemplate &tConfTemp );

	/**
    * 功能:				修改会议模板(fcgi -> ums)
	* @param [in]		tConfTemp 会议模板 
	* @return			u16 成功返回0, 失败返回非0错误码
	* @remarks 消息：   fcgi->ums: evtp_Updateconftemplate_Req
	                    应回复 ums->fcgi: evpt_OperatorConfTemplate_Ret
	                    若成功，则又有 ums->fcgi: evtp_Updateconftemplate_Notify
	*/
	u16 ModifyConfTemplateReq( const TTPConfTemplate &tConfTemp );

	/**
    * 功能:				删除会议模板(fcgi -> ums)
	* @param [in]		wConfTempID 会议模板ID
	* @return			u16 成功返回0, 失败返回非0错误码
	* @remarks 消息：   fcgi->ums: evtp_DelConftemplate_Req
	                    应回复 ums->fcgi: evpt_OperatorConfTemplate_Ret
	                    若成功，则又有 ums->fcgi: evtp_Delconftemplate_Notify
	*/
	u16 DeleteConfTemplateReq( const u16 wConfTempID );

	/**
    * 功能:				删除全部模板(fcgi -> ums)
	* @param			无
	* @return			u16 成功返回0, 失败返回非0错误码
	* @remarks 消息：	fcgi->ums: ev_del_all_conftemp_req
	                    应回复 ums->fcgi: ev_del_all_conftemp_rsp
	*/
	u16 DelAllConfTempReq();

	/**
    * 功能:				召开会议(fcgi -> ums)
	* @param			wConfTemplateID 会议模板ID
	* @return			u16 成功返回0, 失败返回非0错误码
	* @remarks 消息：	fcgi->ums: evtp_StartConfTemplate_Req
	                    应回复 ums->fcgi: evtp_StartConfTemplate_Ret
	*/
	u16 StartTemplateConfReq( const u16 wConfTemplateID );

	/*******************************************************************************
	----------------function that post msg to server:end----------------------------
	*******************************************************************************/

private:
	//会议模板信息 ptree - TTPConfTemplate 转换
	bool ChangePtreeToTTPConfTemplate( /*const*/ ptree& pte, TTPConfTemplate& tTPConfTemplate );

	//通过会议模板ID查找该模板信息
	bool FindConfTempInfoByID( const u16 wID, TTPConfTemplate& tTPConfTemplate );

	//通过会场ID查找该会场信息
//	u16 FindMeetIDByName( const TTPConfTemplate& tTPConfTemplate, const std::string& strMeetName, const std::string& strMeetNum );
	bool FindMeetInfoByID( const TTPConfTemplate& tTPConfTemplate, const u16 wEpID, TTpCallAddr& tTpCallAddr );
	
	//格式名称(std::string) - 主视频格式(TUmsVidFormat) 转换
	void ChangeNameToMainVideo( const u16 wMainCheckCount, const std::string& strFormatName, TTPConfTemplate& tTPConfTemplate );

	//格式名称(std::string) - 辅视频格式(TUmsVidFormat) 转换
	void ChangeNameToMinorVideo( const u16 wMinorCheckCount, const std::string& strFormatName, TTPConfTemplate& tTPConfTemplate );

	//格式名称(std::string) - 音频格式(EmTpAudioFormat) 转换
	void ChangeNameToAudioFormat( const u16 wAudFmtNum, const std::string& strFormatName, TTPConfTemplate& tTPConfTemplate );

private:
	////////////////////data begin/////////////////////////////////////////////////////
	std::vector<TTPConfTemplate> m_vecConfTempList;
	u16		m_wResUsedCount;	//当前资源数
	////////////////////data end///////////////////////////////////////////////////////
};

#endif