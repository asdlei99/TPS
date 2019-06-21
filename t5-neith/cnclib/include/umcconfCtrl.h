/*****************************************************************************
模块名      : cnclib
文件名      : umcconfCtrl.h
相关文件    : 
文件实现功能: 多点会议相关的操作
作者        : 肖楚然
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/4/25      1.0         肖楚然       创建
******************************************************************************/

#if !defined(AFX_CONFCTRL_H__CAFB9774_3218_4A07_80D4_B5B6EEE1ABE7__INCLUDED_)
#define AFX_CONFCTRL_H__CAFB9774_3218_4A07_80D4_B5B6EEE1ABE7__INCLUDED_
#include "cnsSession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmcConfCtrl : public CUmcConfCtrlIF  
{

/** @defgroup  会议控制实现部分
 *   @{
 */
public:
 	friend class CCncSession; 
 
	CUmcConfCtrl( CCnsSession &cCnsSession );
	CUmcConfCtrl( const CUmcConfCtrl &){};
    

public:
  /**
    * 功能:	获取会议列表
	* @param [out]  tplConfList	 会议列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16 GetConf(  TCMSConf &tplConfList ) const ; 

  /**
    * 功能:	获取会议中cns列表
	* @param [int]  vctConfCnsList	 会议列表
    * @param [out]  vctConfCnsList	 CNS列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
   virtual u16 GetConfCnsList( vector<TCnsInfo> &vctConfCnsList ) const ;

    /**
    * 功能:	获取会议混音列表
	* @param [int]  wConfID:会议ID  
    * @param [out]  tConfAudmixList	 混音列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
   virtual u16 GetConfAudmixList( TAuxMixList&tConfAudmixList ) const ;

  /**
    * 功能:	获取会议轮询列表
	* @param [int]  wConfID:会议ID  
    * @param [out]  tplConfPollList	 轮询列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
   //virtual u16 GetConfPollList(  TplArray<u16> &tplConfPollList ) const ;


	 
  /**
    * 功能:	邀请某cns会场加入某会议
	* @param [int]  tEp	 会议和会场信息
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 消息：cms->ums  evtp_CallEP_cmd  \n
                       应回复：ums->cms evtp_CallEP_result   \n
	                   若成功，还应发：ums->cms evtp_UpdateConfCnsList_Notify
	*/ 
	virtual u16 InviteCnsReq( const TTpCallAddr &tAddr );


    /**
    * 功能:	呼叫会议中已经存在的cns会场加入某会议
	* @param [int]  tEp	 会议和会场信息
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 消息：cms->ums  evtp_CallEP_cmd  \n
                       应回复：ums->cms evtp_CallEP_result   \n
	                   若成功，还应发：ums->cms evtp_UpdateConfCnsList_Notify
	*/ 
	virtual u16 CallConfCnsReq( const TConfEpID &tEp );
   

  /**
    * 功能:	挂断会议
	* @param [int]  wConfID 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16 HangupConfReq( );


   /**
    * 功能:	挂断某会场
	* @param [int]  tConfEpInfo 包含会场ID 和 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 会议列表中依然存在该会场，只是不在线
	*/
	virtual u16 HangupCNSReq( const TConfEpID &tConfEpInfo );

	 /**
    * 功能:	会场摄像机控制
	* @param [int]  tConfEpInfo 包含会场ID 和 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 保存远摇会场信息
	*/
	virtual u16 SetFeccConfEpInfo( const TConfEpID &tConfEpInfo );

	/**
    * 功能:	会场摄像机控制
	* @param [int]  tConfEpInfo 包含会场ID 和 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 获取远摇会场信息
	*/
	virtual u16 GetFeccConfEpInfo( TConfEpID &tConfEpInfo );

	/**
    * 功能:	会场摄像机控制
	* @param [int]  
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 会场摄像机操作，切换远摇会场视频源
	*/
	virtual u16 ChangeFeccSource(u8 SourceId);

	/** 功能   远摇摄像机调节PT
	*  @param[in] emDirection： 方向  emCnAction：操作
	*  @return 成功返回0,失败返回非0错误码
	*/
    virtual u16 SetFeccCamPT( EmDirection emDirection, EmCnAction emCnAction );

	/** 功能   远摇摄像机视野调节
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetFeccCamView( EmZoom emZoom, EmCnAction emCnAction );

	/** 功能   远摇摄像机调节亮度
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetFeccCamBright( EmPanCamBright emPanCamBright, EmCnAction emCnAction );

		/** 功能   远摇摄像机调节焦距 
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetFeccCamFocus( EmFocus emFocus, EmCnAction emCnAction );

	/** 功能   远摇摄像机自动调节焦距 
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetFeccCamAotoFocus( );

	/**
    * 功能:	从会议中移除某会场
	* @param [int]  tConfEpInfo 包含会场ID 和 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 会议列表中不存在该会场
	*/
	virtual u16 RemoveCNSReq( const TConfEpID &tConfEpInfo ) ;

  	/**
    * 功能:	设置发言会场
	* @param [int]  wConfID	 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 SetSpokeCnsReq( const TConfEpID &tConfEpInfo ) ;

   
    /**
    * 功能:	设置远程cns静音
	* @param [int]  wConfID	 会议ID
    * @param [int]  bQuiet  TRUE:开启静音，FALSE：停止静音
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 SetQuietCnsReq( const TConfEpID &tConfEpInfo, BOOL32 bQuiet) ;

    /**
    * 功能:	设置远程cns哑音
	* @param [int]  wConfID	 会议ID
    * @param [int]  bMute  TRUE:开启哑音，FALSE：停止哑音
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 SetMuteCnsReq( const TConfEpID &tConfEpInfo , BOOL32 bMute) ;

     /**
    * 功能:	设置远程cns发起双流
	* @param [int]  wConfID	 会议ID
    * @param [int]  bStart  TRUE:开启双流，FALSE：停止双流
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 SetDualCnsReq( const TConfEpID &tConfEpInfo, BOOL32 bStart ) ;

	/**
    * 功能:	更新混音列表请求
	* @param [int]  tMixInfo	 混音列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 UpdateAudMixListReq( const TConfAuxMixInfo &tMixInfoList );


	/**
    * 功能:	操作混音列表请求
	* @param [int]  tDisListOpr	 一个混音列表操作
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 AudMixDisListOprCmd( const TDiscussListOpr &tDisListOpr );

		/** 
	* 功能:  语音激励
    * @param [in	TConfAuxMixVacOpr	 
    * @return	成功返回0,失败返回非0错误码
    * @remarks 	 */
	virtual u16 AuxMixVacOpr( const TConfAuxMixVacOpr tConfAuxMixVacOpr);

  /**
    * 功能:	更新轮询列表请求
	* @param [int]  tTurnInfoList	 轮询列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 UpdatePollListReq( const TConfTurnInfo &tTurnInfoList );

	
  /**
    * 功能:	开启混音
	* @param [int]  wConfID	 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 StartAuxMixReq( const u16 wConfID );

 /**
    * 功能:	停止混音
	* @param [int]  wConfID	 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 StopAuxMixReq( const u16 wConfID );


   /**
    * 功能:	开启轮询
	* @param [int]  wConfID	 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 StartPollReq( const u16 wConfID );


  /**
    * 功能:	停止轮询 
	* @param [int]  wConfID	 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 StopPollReq( const u16 wConfID );
	

	//会议轮询暂停
	virtual u16 PollPauseCmd( const BOOL32& bIsPause );
	virtual TTpPollStat GetPollState();
	//会议轮询列表更新
	virtual u16 PollListUpdateCmd( const TTpPollListNtfy& tTpPollListNtfy );
	/** 
	* 功能  	获得轮询列表
	* @param [in] 	   
	* @return  
	* @remarks 
	*/	
	virtual u16 GetPollList(  vector<u16>& vctPollList  );

    /**	功能:	选择画面合成器 
	* @param [int]  tRersvesEqp	 合成器
	* @return  u16 成功返回0,失败返回非0错误码 
	*/
    virtual u16 RervesBrdVmpReq( TRersvesEqpReq tRersvesEqp );

    /**	功能:	配置画面合成 
	* @param [int]  tVmpInfo	 配置合成器信息
	* @return  u16 成功返回0,失败返回非0错误码
	*/
    virtual u16 SetBrdVmpReq( TSetVmpInfoReq tVmpInfo );
	//响应是否会场可以加入会议
	virtual u16 SetJoinConfInfo( TTpConfEpInfo tpConfEpInfo );

    /**	功能:	广播画面合成 
	* @param [int]  tBrdVmp	 合成器信息
	* @return  u16 成功返回0,失败返回非0错误码
	*/
    virtual u16 SetBroadcastVmpReq( TBrdVmpReq tBrdVmp );

    /** 
	* 功能  获取画面合成状态
	* @return  vector<TBrdVmpResNtfy> 画面合成状态
	* @remarks 
	*/
	virtual const vector<TBrdVmpResNtfy>& GetBrdVmpStatus() const;

    /** 
	* 功能  保存合成预案
	* @return  tBrdVmp  画面合成状态
	* @remarks 
	*/
    virtual u16 SaveVmpCfgReq( TBrdVmpResNtfy &tBrdVmp );
    /** 
	* 功能  调用合成预案
    * @return  tEqp  画面合成器信息
	* @remarks 
	*/
    virtual u16 CallVmpCfgReq( TEqpInfo &tEqp );
    /** 
	* 功能  获取画面合成预案
	* @return  画面合成预案
	* @remarks 
	*/
	virtual const TVmpMemberCfg GetCurrentVmpCfg() const;

	/** 
	* 功能  会议选看状态
	* @return  会议选看状态
	* @remarks 
	*/
	virtual const TTPSelViewNtfy GetSelWatchStatus() const;
	/** 
	* 功能  ums错误问题
	* @return  错误问题
	* @remarks 
	*/
	virtual const TTPUmsReasonInd GetUmsReason() const;
	 /** 
	* 功能  会议讨论列表
	* @return  会议讨论列表
	* @remarks 
	*/
	const TDiscussListOpr GetDiscussList() const;
	//申请加入会议会场信息
	const TTpConfEpInfo GetJoinConfInfo() const;

    /** 
	* 功能  电视墙
    * @return  
	* @remarks 
	*/
    virtual u16 ChangeChanModeReq( u16 wIndex, u8 byMode  );

    virtual u16 SetHduVolReq( u16 wIndex, u8 byVol ,BOOL32 bMute );

    virtual u16 StopPlayHdu( TTpHduPlayReq &tTvwInfo );

    virtual u16 PlayHduReq( const TTpHduPlayReq & tTvwInfo );

	//设置/获取 全场静音/哑音 状态
	void SetAllQuiet( const CMessage& cMsg );
	virtual bool IsAllQuite();
	void SetAllMute( const CMessage& cMsg );
	virtual bool IsAllMute();

protected: 

    void OnChairCnsNotify( const CMessage& cMsg );
	void OnConfStateNty( const CMessage& cMsg );

	void OnHungUpConfRsp( const CMessage& cMsg ); 
	void OnInviteCnsRsp( const CMessage& cMsg ); 
    void OnCallConfCnsRsp( const CMessage& cMsg ); 
    void OnHangupCnsInd( const CMessage& cMsg );
	void OnUpdateConfCnsListNotify( const CMessage& cMsg ); 
	void OnUpdateConfAuxMixlistNotify( const CMessage& cMsg ); 
	void OnUpdateConfAuxMixlistInd( const CMessage& cMsg ); 
	void OnUpdateConfPolllistNotify( const CMessage& cMsg ); 
    void OnUpdateConfSpeakerNotify( const CMessage& cMsg ); 
	void OnAudMixDisListOprNotify( const CMessage& cMsg );
    void OnAMixVacNotify( const CMessage& cMsg );//语音激励回应

	void OnSetSpokeCnsRsp( const CMessage& cMsg ); 
    void OnSetMuteCnsRsp( const CMessage& cMsg ); 
    void OnSetSilenceCnsRsp( const CMessage& cMsg ); 
    void OnSetDualCnsRsp( const CMessage& cMsg ); 
    void OnDualCnsNotify( const CMessage& cMsg ); 
    
	void OnCnsLeaveNotify( const CMessage& cMsg ); 

    void OnUmsCommonReasonInd( const CMessage& cMsg ); 

	//画面合成 请求占用合成回应
    void OnRervesBrdVmpInd( const CMessage& cMsg );
    //请求配置画面合成回应
    void OnSetBrdVmpInd( const CMessage& cMsg );
    //请求广播画面合成回应
    void OnBrdVmpInd( const CMessage& cMsg );
    //合成器状态通知
    void OnBrdVmpNty( const CMessage& cMsg );
    //画面合成预案通知
    void OnSaveVmpCfgCmd( const CMessage& cMsg );
    void OnSaveVmpCfgInd( const CMessage& cMsg );

    void OnLinkBreak( const CMessage& cMsg ); 

	virtual void DispEvent(const CMessage &cMsg);
	
    virtual void OnTimeOut(u16 wEvent);

	//会议轮询列表更新回应通知
	void OnPollListInd( const CMessage& cMsg );
	//会议轮询列表通知
	void OnPollListNty( const CMessage& cMsg );
	//会议轮询暂停结果通知
	void OnPollPauseInd( const CMessage& cMsg );

	//轮询状态 会议中
	void OnPollStatusNty( const CMessage &cMsg );

	//会场选看 状态保存
	void OnSetSelViewNty( const CMessage &cMsg );
	//终端会场入会请求
	void OnJoinConfReq( const CMessage &cMsg );

    //会议讨论
    void OnSetAudioInfoInd( const CMessage &cMsg );

    //电视墙通知
    void OnHduPlanNty( const CMessage& cMsg );

    void OnHduChangeModeInd( const CMessage& cMsg );

    void OnHduVolInd( const CMessage& cMsg );
       
    void OnHduStopPlayInd( const CMessage& cMsg );
    
    void OnHduPlayInd( const CMessage& cMsg );
	
	//H323会场视频源通知
	void OnP2PH323VideoInfo( const CMessage& cMsg );
	//H323会场视频源当前源和是否可远摇
	void OnP2PH323VideoFeccInfo( const CMessage& cMsg );

	//多点会议H323会场视频源通知
	void OnMulConfH323VideoInfoNty( const CMessage& cMsg );
    void OnMulConfH323VideoInfoInd( const CMessage& cMsg );
    
private:
	void  BuildEventsMap();
	 
private:
    CCnsSession *  m_pCncSession;
	TCMSConf       m_tConfInfo; 
	vector<u16>    m_vctPollList;//会议轮询列表
	bool           m_bIsFirstPollListNty;//是否会议轮询列表消息第一次通知
	s32		       m_nPollListFlag;//flag不同 清空之前数据 进行新的记录    
	TTPSelViewNtfy  m_tTPSelViewNtfy;//会议选看列表信息
	TDiscussListOpr m_tDiscussListOpr;//会议讨论列表
	TTpConfEpInfo m_tpConfEpInfo;//加入会场信息

	TVidFeccInfo m_tVidFeccInfo;//远摇视频源信息

    vector<TBrdVmpResNtfy>  m_vctBrdVmpInfo;    //所有画面合成数据
    TVmpMemberCfg     m_tVmpCurrentCfg;         //当前预案信息
    TBrdVmpResNtfy    m_tVmpSaveCfg;            //正在保存的画面合成预案信息
    int               m_nRevCfgIndex;           //接收预案的索引,预案分批收到
    int               m_nSaveCfgIndex;          //保存预案的索引

    TTpHduPlanPackData	m_tHduPlanPackData[TP_STYLE_DATA_AllPACK_NUM];   //电视墙
    int               m_bPackDataIndex;
	TTPUmsReasonInd   m_tTPUmsReasonInd;//错误提示

	bool                      m_bIsAllQuite;           //是否全场静音
	bool                      m_bIsAllMute;            //是否全场哑音
	
	TConfEpID                 m_tConfEpInfo;           //远摇会议ID会场ID

	vector<TVidFeccInfo>      m_vctConf323VidInfo;     //多点会议的323会场视频源

/** @}*/ //会议控制实现部分
};

#endif // !defined(AFX_CONFCTRL_H__CAFB9774_3218_4A07_80D4_B5B6EEE1ABE7__INCLUDED_)
