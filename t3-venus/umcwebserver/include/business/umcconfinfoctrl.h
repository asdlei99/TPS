/*****************************************************************************
模块名      : CUmcConfinfoCtrl
文件名      : umcconfinfoctrl.h
相关文件    : 
文件实现功能: 会议信息业务类
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2014/09/17  1.0         石城        创建
******************************************************************************/
#ifndef UMCCONFINFOCTRL_H
#define UMCCONFINFOCTRL_H


class CUmcConfinfoCtrl : public CKdvDispEvent, public ISingleTon<CUmcConfinfoCtrl>
{
public:
	CUmcConfinfoCtrl();
	virtual ~CUmcConfinfoCtrl();

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
	* 功能:	获取会议列表请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebListconfGetReq(const boost::any& arg);

	/**
	* 功能:	会场列表获取请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcListMtGetReq(const boost::any& arg);

	/**
	* 功能:	挂断会议请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebHangupconfReq(const boost::any& arg);

	/**
	* 功能:	开启双流请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcEpoperStartdualReq(const boost::any& arg);

	/**
	* 功能:	关闭双流请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcEpoperStopdualReq(const boost::any& arg);

	/**
	* 功能:	指定发言人请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcEpoperApplyspeakerReq(const boost::any& arg);

	/**
	* 功能:	静音请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcEpoperQuietReq(const boost::any& arg);

	/**
	* 功能:	哑音请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcEpoperMuteReq(const boost::any& arg);

	/**
	* 功能:	挂断请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcEpoperDropReq(const boost::any& arg);

	/**
	* 功能:	呼叫请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcEpoperCallReq(const boost::any& arg);

	/**
	* 功能:	选看请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcEpoperSelviewReq(const boost::any& arg);

	/**
	* 功能:	获取选看信息请求
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcSelviewInfoGetReq(const boost::any& arg);
	



	/********************浏览会议信息 - begin**************************************/

	/**
	* 功能:		刷新 会议管理-会议信息 通知型请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebRefreshConfinfoInfoNtyReq(const boost::any& arg);

	/**
	* 功能:		刷新 会议管理-会议信息-轮询列表 通知型请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebRefreshConfinfoPollingListNtyReq(const boost::any& arg);

	/**
	* 功能:		刷新 会议管理-会议信息-讨论列表 通知型请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebRefreshConfinfoDiscussListNtyReq(const boost::any& arg);

	/**********************浏览会议信息 - end**************************************/

	/**********************会议轮询 - begin****************************************/
	/**
	* 功能:		暂停、恢复轮询 请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebSuspendTurnReq(const boost::any& arg);

	/**
	* 功能:		开启、关闭轮询 请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebStartTurnReq(const boost::any& arg);

	/**
	* 功能:		更新轮询列表 请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebUpdateTurnReq(const boost::any& arg);

	/**********************会议轮询 - end******************************************/

	/**********************会议讨论 - begin****************************************/
	/**
	* 功能:		语音激励开启和关闭 请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebAuxMixVacSwitchReq(const boost::any& arg);

	/**
	* 功能:		添加和删除讨论成员（讨论下用）请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebUpdateAudMixInfoReq(const boost::any& arg);
	
	/**
	* 功能:		开启和关闭讨论，开启和关闭语音激励， 或者非讨论下，更新讨论成员 请求
	* @return	u16 成功返回0,失败返回非0错误码
	* @remarks	参数为前端传递过来的json数据
	*/
	u16 OnUmcwebStartAuxMixReq(const boost::any& arg);

	/**********************会议讨论 - end******************************************/

	/*******************************************************************************
	----------------function that handle msg from client:end----------------------
	*******************************************************************************/
	
private:
	/*******************************************************************************
	----------------function that handle msg from server:begin----------------------
	*******************************************************************************/

	/**
	* 功能:	UMS通知UMC增加会议列表
	* @return  void
	* @event evtp_AddConfList_Notify
	*/
	void OnAddConfListNotify( const CMessage& cMsg );

	/**
	* 功能:	UMS通知UMC会议会场列表
	* @return  void
	* @event evtp_UpdateConfCnsList_Notify
	*/
	void OnUpdateConfCnsListNotify( const CMessage& cMsg );

	/**
	* 功能:	CMS请求UMS挂断会议结果
	* @return  void
	* @event evtp_HungUpConf_result
	*/
	void OnHungUpConfRsp( const CMessage& cMsg );

	/**
	* 功能:	UMS通知UMC删除的会议列表
	* @return  void
	* @event evtp_DelConflist_Notify
	*/
	void OnDelConfListNotify( const CMessage& cMsg );

	/**
	* 功能:	请求开启双流结果
	* @return  void
	* @event evtp_StartDual_Ind
	*/
	void OnStartdualRsp( const CMessage& cMsg );

	/**
	* 功能:	请求关闭双流结果
	* @return  void
	* @event evtp_StopDual_Ind
	*/
	void OnStopdualRsp( const CMessage& cMsg );

	/**
	* 功能:	UMS通知CMS双流源改变
	* @return  void
	* @event evtp_DualEp_Notify
	*/
	void OnDualNotify( const CMessage& cMsg );

	/**
	* 功能:	UMS通知UMC指定发言人结果
	* @return  void
	* @event evtp_ApplySpeaker_result
	*/
	void OnSpeakerRsp( const CMessage& cMsg );

	/**
	* 功能:	UMS通知UMC发言人改变
	* @return  void
	* @event evtp_SpeakerChange_Notify
	*/
	void OnSpeakerNotify( const CMessage& cMsg );

	/**
	* 功能:	UMC指定远端静音回应
	* @return  void
	* @event evtp_QuietEp_Ind
	*/
	void OnQuietRsp( const CMessage& cMsg );

	/**
	* 功能:	 UMC指定远端哑音回应
	* @return  void
	* @event evtp_MuteEp_Ind
	*/
	void OnMuteRsp( const CMessage& cMsg );

	/**
	* 功能:	 UMC请求UMS挂断EP结果
	* @return  void
	* @event evtp_DropEp_Ind
	*/
	void OnDropRsp( const CMessage& cMsg );

	/**
	* 功能:	 UMC请求UMS呼叫已经存在的EP结果
	* @return  void
	* @event evtp_CallExistEP_result
	*/
	void OnCallRsp( const CMessage& cMsg );

	/**
	* 功能:	 通知UMC的选看状态
	* @return  void
	* @event ev_UMS_UMC_SelView_Ntfy
	*/
	void OnSelViewNotify( const CMessage& cMsg );

	/**
	* 功能:	 UMS->UMC的选看回应
	* @return  void
	* @event ev_UMS_UMC_SelView_Ind
	*/
	void OnSelViewRsp( const CMessage& cMsg );

	/**********************会议轮询 - begin**************************************/
	/**
	* 功能		UMS通知UMC会议轮询列表(ums -> fcgi)
	* @return	void
	* @event	evtp_UpdateConfTurnlist_Notify
	*/
	void OnUpdateConfTurnlistNotify( const CMessage& cMsg );

	/**
	* 功能		UMC请求UMS更新轮询列表回应(ums -> fcgi)
	* @return	void
	* @event	evtp_UpdateTurn_ind
	*/
	void OnUpdateTurnInd( const CMessage& cMsg );

	/**
	* 功能		UMC请求UMS开启轮询回应(ums -> fcgi)
	* @return	void
	* @event	evtp_StartTurn_ind
	*/
	void OnStartTurnInd( const CMessage& cMsg );

	/**
	* 功能		UMC请求UMS关闭轮询回应(ums -> fcgi)
	* @return	void
	* @event	evtp_StopTurn_ind
	*/
	void OnStopTurnInd( const CMessage& cMsg );

	/**
	* 功能		UMC请求UMS暂停暂停轮询回应(ums -> fcgi)
	* @return	void
	* @event	evtp_SuspendTurn_ind
	*/
	void OnSuspendTurnInd( const CMessage& cMsg );

	/**
	* 功能		UMS通知UMC轮询状态(ums -> fcgi)
	* @return	void
	* @event	evtp_TurnStat_ntfy
	*/
	void OnTurnStatNotify( const CMessage& cMsg );

	/**********************会议轮询 - end****************************************/

	/**********************会议讨论 - begin**************************************/
	/**
	* 功能		UMS通知UMC会议讨论列表(ums -> fcgi)
	* @return	void
	* @event	evtp_AuxMixInfo_Notify
	*/
	void OnAuxMixInfoNotify( const CMessage& cMsg );

	/**
	* 功能		UMC请求UMS添加和删除讨论成员回应(讨论下用)(ums -> fcgi)
	* @return	void
	* @event	evtp_UpdateAudMixInfo_Ind
	*/
	void OnUpdateAudMixInfoInd( const CMessage& cMsg );

	/**
	* 功能		UMC请求UMS开启和关闭讨论，开启和关闭语音激励， 或者非讨论下，更新讨论成员回应(ums -> fcgi)
	* @return	void
	* @event	evtp_StartAuxMix_ind
	*/
	void OnStartAuxMixInd( const CMessage& cMsg );

	/**
	* 功能		语音激励开启和关闭回应(ums -> fcgi)
	* @return	void
	* @event	ev_AuxMixVacSwitchInd
	*/
	void OnAuxMixVacSwitchInd( const CMessage& cMsg );

	/**********************会议讨论 - end****************************************/


	void OnLinkBreak( const CMessage& cMsg );

	/*******************************************************************************
	----------------function that handle msg from server:end----------------------
	*******************************************************************************/

private:
	/*******************************************************************************
	----------------function that post msg to server:begin--------------------------
	*******************************************************************************/

	/**********************会议轮询 - begin**************************************/
	/**
    * 功能:				UMC请求UMS更新轮询列表(fcgi -> ums)
	* @param [in]		tConfTurnInfo
	* @return			u16 成功返回0, 失败返回非0错误码
	* @remarks 消息：	fcgi->ums: evtp_UpdateTurn_cmd
	                    应回复 ums->fcgi: evtp_UpdateTurn_ind
	*/
	u16 UpdateTurnReq( const TConfTurnInfo &tConfTurnInfo );

	/**
    * 功能:				UMC请求UMS开启轮询(fcgi -> ums)
	* @param [in]		wConfID
	* @return			u16 成功返回0, 失败返回非0错误码
	* @remarks 消息：	fcgi->ums: evtp_StartTurn_cmd
	                    应回复 ums->fcgi: evtp_StartTurn_ind
	*/
	u16 StartTurnReq( const u16 wConfID );

	/**
    * 功能:				UMC请求UMS关闭轮询(fcgi -> ums)
	* @param [in]		wConfID
	* @return			u16 成功返回0, 失败返回非0错误码
	* @remarks 消息：	fcgi->ums: evtp_StopTurn_cmd
	                    应回复 ums->fcgi: evtp_StopTurn_ind
	*/
	u16 StopTurnReq( const u16 wConfID );

	/**
    * 功能:				UMC请求UMS暂停暂停轮询(fcgi -> ums)
	* @param [in]		wConfID
	* @return			u16 成功返回0, 失败返回非0错误码
	* @remarks 消息：	fcgi->ums: evtp_SuspendTurn_cmd
	                    应回复 ums->fcgi: evtp_SuspendTurn_ind
	*/
	u16 SuspendTurnReq( const u16 wConfID, const BOOL32 bSuspend );

	/**********************会议轮询 - end****************************************/

	/**********************会议讨论 - begin**************************************/
	/**
    * 功能:				UMC请求UMS添加和删除讨论成员(讨论下用)(fcgi -> ums)
	* @param [in]		tDiscussListOpr
	* @return			u16 成功返回0, 失败返回非0错误码
	* @remarks 消息：	fcgi->ums: evtp_UpdateAudMixInfo_cmd
	                    应回复 ums->fcgi: evtp_UpdateAudMixInfo_Ind、evtp_AuxMixInfo_Notify
	*/
	u16 UpdateAudMixInfoReq( const TDiscussListOpr& tDiscussListOpr );

	/**
    * 功能:				UMC请求UMS开启和关闭讨论，开启和关闭语音激励， 或者非讨论下，更新讨论成员(fcgi -> ums)
	* @param [in]		tConfAuxMixInfo
	* @return			u16 成功返回0, 失败返回非0错误码
	* @remarks 消息：	fcgi->ums: evtp_StartAuxMix_cmd
	                    应回复 ums->fcgi: evtp_StartAuxMix_ind、evtp_AuxMixInfo_Notify
	*/
	u16 StartAuxMixReq( const TConfAuxMixInfo& tConfAuxMixInfo );

	/**
    * 功能:				语音激励开启和关闭(fcgi -> ums)
	* @param [in]		tConfAuxMixVacOpr
	* @return			u16 成功返回0, 失败返回非0错误码
	* @remarks 消息：	fcgi->ums: ev_AuxMixVacSwitch
	                    应回复 ums->fcgi: ev_AuxMixVacSwitchInd、evtp_AuxMixInfo_Notify
	*/
	u16 AuxMixVacSwitchReq( const TConfAuxMixVacOpr& tConfAuxMixVacOpr );

	/**********************会议讨论 - end****************************************/

	/*******************************************************************************
	----------------function that post msg to server:end----------------------------
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

	/**
    * 功能:	通过confID 获取 会议信息
	* @param [int]  wConfID	 会议ID
	* @return  TConfinfo*
	* @remarks  
	*/
    TConfinfo*  GetConfInfoByID( u16 wConfID );
	
	/**
    * 功能:	通过confID 删除 会议信息
	* @param [int]  wConfID	 会议ID
	* @return  TRUE: 删除成功, FALSE: 删除失败 
	* @remarks  
	*/
	BOOL DelConfInfoByID( u16 wConfID );

	/**
    * 功能:	通过wConfID查询对应会议的轮询信息并通知前端
	* @param [u16]  wConfID	 会议ID
	* @return u16
	* @remarks  
	*/
	u16 UmcwebRefreshConfinfoPollingList( const u16 wConfID );

	/**
    * 功能:	通过wConfID查询对应会议的讨论信息并通知前端
	* @param [u16]  wConfID	 会议ID
	* @return u16
	* @remarks  
	*/
	u16 UmcwebRefreshConfinfoDiscussList( const u16 wConfID );

public:
	void ShowConfinfo();

private:
	////////////////////data begin/////////////////////////////////////////////////////

	vector<TConfinfo> m_vecTConfinfo;			//会议信息

	////////////////////data end///////////////////////////////////////////////////////
};

#endif