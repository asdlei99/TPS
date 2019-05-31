/*****************************************************************************
模块名      : cnclib
文件名      : umcconfCtrlIF.h
相关文件    : 
文件实现功能: 多点会议相关的接口
作者        : 肖楚然
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2012/4/25   1.0         肖楚然      创建
******************************************************************************/

#if !defined(AFX_UMCCONFCTRLIF_H__10B44268_D175_431C_ACCA_A0A559086730__INCLUDED_)
#define AFX_UMCCONFCTRLIF_H__10B44268_D175_431C_ACCA_A0A559086730__INCLUDED_
#include "kdvdispevent.h"
#include "cncstruct.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmcConfCtrlIF:public  CKdvDispEvent   
{

public:
 
/** @defgroup  会议控制部分接口
 *  @{
 */

  /**
    * 功能:	获取会议列表
	* @param [out]  tplConfList	 会议列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16 GetConf(  TCMSConf &tplConf  ) const = 0;
   
  /**
    * 功能:	获取会议中cns列表
	* @param [int]  vctConfCnsList	 CNS列表
    * @param [out]  vctConfCnsList	 CNS列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
    virtual u16 GetConfCnsList( vector<TCnsInfo> &vctConfCnsList ) const  = 0 ;
   
  /**
    * 功能:	获取会议混音列表
	* @param [int]  wConfID:会议ID  
    * @param [out]  tplConfAudmixList	 混音列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
   virtual u16 GetConfAudmixList( TAuxMixList&tConfAudmixList ) const = 0 ;

    /**
    * 功能:	获取会议轮询列表
	* @param [int]  wConfID:会议ID  
    * @param [out]  tplConfPollList	 轮询列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
   //virtual u16 GetConfPollList(  TplArray<u16> &tplConfPollList ) const = 0;
 
   /**
    * 功能:	邀请某cns会场加入某会议
	* @param [int]  tEp	 会议和会场信息
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16 InviteCnsReq( const TTpCallAddr &tAddr )  = 0;
 
    /**
    * 功能:	呼叫会议中已经存在的cns会场加入某会议
	* @param [int]  tEp	 会议和会场信息
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 消息：cms->ums  evtp_CallEP_cmd  \n
                       应回复：ums->cms evtp_CallEP_result   \n
	                   若成功，还应发：ums->cms evtp_UpdateConfCnsList_Notify
	*/ 
	virtual u16 CallConfCnsReq( const TConfEpID &tEp ) = 0;

   /**
    * 功能:	挂断会议
	* @param [int]  wConfID 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16 HangupConfReq( ) = 0;
 
  /**
    * 功能:	挂断某会场
	* @param [int]  tConfEpInfo 包含会场ID 和 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 会议列表中依然存在该会场，只是不在线
	*/
	virtual u16 HangupCNSReq( const TConfEpID &tConfEpInfo ) = 0;

	 /**
    * 功能:	会场摄像机控制
	* @param [int]  tConfEpInfo 包含会场ID 和 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 会场摄像机操作，保存远摇的会场信息
	*/
	virtual u16 SetFeccConfEpInfo( const TConfEpID &tConfEpInfo ) = 0;

	/**
    * 功能:	会场摄像机控制
	* @param [int]  tConfEpInfo 包含会场ID 和 会议ID 
	* @return u16 成功返回0,失败返回非0错误码
	* @remarks 会场摄像机操作，获取远摇的会场信息
	*/
	virtual u16 GetFeccConfEpInfo( TConfEpID &tConfEpInfo ) = 0;

	 /**
    * 功能:	会场摄像机控制
	* @param [int]
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 会场摄像机操作，获取会场所有视频源
	*/
	virtual u16 ChangeFeccSource(u8 SourceId) = 0;

	/** 功能   远摇摄像机调节PT
	*  @param[in] emDirection： 方向  emCnAction：操作
	*  @return 成功返回0,失败返回非0错误码
	*/
    virtual u16 SetFeccCamPT( EmDirection emDirection, EmCnAction emCnAction ) = 0;

	/** 功能   远摇摄像机视野调节
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetFeccCamView( EmZoom emZoom, EmCnAction emCnAction ) = 0;

	/** 功能   远摇摄像机调节亮度
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetFeccCamBright( EmPanCamBright emPanCamBright, EmCnAction emCnAction ) = 0;

		/** 功能   远摇摄像机调节焦距 
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetFeccCamFocus( EmFocus emFocus, EmCnAction emCnAction ) = 0;

	/** 功能   远摇摄像机自动调节焦距 
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetFeccCamAotoFocus() = 0;


  /**
    * 功能:	从会议中移除某会场
	* @param [int]  tConfEpInfo 包含会场ID 和 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 会议列表中不存在该会场
	*/
	virtual u16 RemoveCNSReq( const TConfEpID &tConfEpInfo )  = 0;

	/**
    * 功能:	设置发言会场
	* @param [int]  wConfID	 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 SetSpokeCnsReq( const TConfEpID &tConfEpInfo )    = 0;

    /**
    * 功能:	设置远程cns静音
	* @param [int]  wConfID	 会议ID
    * @param [int]  bQuiet  TRUE:开启静音，FALSE：停止静音
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 SetQuietCnsReq( const TConfEpID &tConfEpInfo, BOOL32 bQuiet)    = 0;


    /**
    * 功能:	设置远程cns哑音
	* @param [int]  wConfID	 会议ID
    * @param [int]  bMute  TRUE:开启哑音，FALSE：停止哑音
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 SetMuteCnsReq( const TConfEpID &tConfEpInfo , BOOL32 bMute)    = 0;


     /**
    * 功能:	设置远程cns发起双流
	* @param [int]  wConfID	 会议ID
    * @param [int]  bStart  TRUE:开启双流，FALSE：停止双流
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 SetDualCnsReq( const TConfEpID &tConfEpInfo, BOOL32 bStart )    = 0; 

	/**
    * 功能:	更新混音列表请求
	* @param [int]  tMixInfo	 混音列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 UpdateAudMixListReq( const TConfAuxMixInfo &tMixInfoList ) = 0;

	/**
    * 功能:	操作混音列表请求
	* @param [int]  tDisListOpr	 一个混音列表操作
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 AudMixDisListOprCmd( const TDiscussListOpr &tDisListOpr ) = 0;

	/** 
	* 功能:  语音激励
    * @param [in	TConfAuxMixVacOpr	 
    * @return	成功返回0,失败返回非0错误码
    * @remarks 	 */
	virtual u16 AuxMixVacOpr( const TConfAuxMixVacOpr tConfAuxMixVacOpr) = 0;

 
  /**
    * 功能:	更新轮询列表请求
	* @param [int]  tTurnInfoList	 轮询列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 UpdatePollListReq( const TConfTurnInfo &tTurnInfoList ) = 0;


  /**
    * 功能:	开启混音
	* @param [int]  wConfID	 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 StartAuxMixReq( const u16 wConfID ) = 0;
 
  /**
    * 功能:	停止混音
	* @param [int]  wConfID	 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 StopAuxMixReq( const u16 wConfID ) = 0;

  /**
    * 功能:	开启轮询
	* @param [int]  wConfID	 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 StartPollReq( const u16 wConfID ) = 0;


  /**
    * 功能:	停止轮询 
	* @param [int]  wConfID	 会议ID
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  
	*/
	virtual u16 StopPollReq( const u16 wConfID ) = 0;


	//会议轮询暂停
	virtual u16 PollPauseCmd( const BOOL32& bIsPause ) = 0;
	virtual TTpPollStat GetPollState() = 0;

	//会议轮询列表更新
	virtual u16 PollListUpdateCmd( const TTpPollListNtfy& tTpPollListNtfy ) = 0;
   		/** 
	* 功能  	获得轮询列表
	* @param [in] 	   
	* @return  
	* @remarks 
	*/	
	virtual u16 GetPollList(  vector<u16>& vctPollList ) = 0;

    /**	功能:	选择画面合成器 
	* @param [int]  tRersvesEqp	 合成器
	* @return  u16 成功返回0,失败返回非0错误码 
	*/
    virtual u16 RervesBrdVmpReq( TRersvesEqpReq tRersvesEqp ) = 0;

    /**	功能:	配置画面合成 
	* @param [int]  tVmpInfo	 配置合成器信息
	* @return  u16 成功返回0,失败返回非0错误码
	*/
    virtual u16 SetBrdVmpReq( TSetVmpInfoReq tVmpInfo ) = 0;

	//响应是否会场可以加入会议
	virtual u16 SetJoinConfInfo( TTpConfEpInfo tpConfEpInfo ) = 0;
    /**	功能:	广播画面合成 
	* @param [int]  tBrdVmp	 合成器信息
	* @return  u16 成功返回0,失败返回非0错误码
	*/
    virtual u16 SetBroadcastVmpReq( TBrdVmpReq tBrdVmp ) = 0;
    /** 
	* 功能  获取画面合成状态
	* @return vector<TBrdVmpResNtfy> 画面合成状态
	* @remarks 
	*/
	virtual const vector<TBrdVmpResNtfy>& GetBrdVmpStatus() const = 0;
    /** 
	* 功能  保存合成预案
	* @return  tBrdVmp  画面合成状态
	* @remarks 
	*/
    virtual u16 SaveVmpCfgReq( TBrdVmpResNtfy &tBrdVmp ) = 0;
    /** 
	* 功能  调用合成预案
    * @return  tEqp  画面合成器信息
	* @remarks 
	*/
    virtual u16 CallVmpCfgReq( TEqpInfo &tEqp ) = 0;
    /** 
	* 功能  获取画面合成预案
	* @return  画面合成预案
	* @remarks 
	*/
	virtual const TVmpMemberCfg GetCurrentVmpCfg() const = 0;

	//会议选看状态
	virtual const TTPSelViewNtfy GetSelWatchStatus() const = 0;
		/** 
	* 功能  ums错误问题
	* @return  错误问题
	* @remarks 
	*/
	virtual const TTPUmsReasonInd GetUmsReason() const = 0;
	/** 
	* 功能  会议讨论列表
	* @return  会议讨论列表
	* @remarks 
	*/
	virtual const TDiscussListOpr GetDiscussList() const = 0;
	virtual const TTpConfEpInfo GetJoinConfInfo() const = 0;

    /** 
	* 功能  改变电视墙模式
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
    virtual u16 ChangeChanModeReq( u16 wIndex, u8 byMode  ) = 0;
    /** 
	* 功能  设置电视墙音量
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
    virtual u16 SetHduVolReq( u16 wIndex, u8 byVol ,BOOL32 bMute ) =0;
    /** 
	* 功能  停止播放电视墙通道
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
    virtual u16 StopPlayHdu( TTpHduPlayReq &tTvwInfo ) = 0;
    /** 
	* 功能  请求播放电视墙通道
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
    virtual u16 PlayHduReq( const TTpHduPlayReq & tTvwInfo ) = 0 ;


	//设置/获取 全场静音/哑音 状态
	virtual bool IsAllQuite() = 0;
	virtual bool IsAllMute() = 0;


/** @}*/  //会议控制部分接口

};

#endif // !defined(AFX_CONFCTRLIF_H__10B44268_D175_431C_ACCA_A0A559086730__INCLUDED_)
