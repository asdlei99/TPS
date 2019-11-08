// cncconfctrl.h: interface for the CCncConfCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNCCONFCTRL_H__2EF9234D_820A_40F3_9DC4_967387311945__INCLUDED_)
#define AFX_CNCCONFCTRL_H__2EF9234D_820A_40F3_9DC4_967387311945__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cnsSession.h"

class CCncConfCtrl : public CCncConfCtrlIF 
{
public:
	CCncConfCtrl(CCnsSession &cSession);
	virtual ~CCncConfCtrl();

    
    /** 
	* 功能  开启点对点会议
	* @return tDialParam 相应参数
	* @remarks 
	*/
    virtual const u16 MakeCall( TTPDialParam &tDialParam )  ;

    virtual u16 GetCnTempPwdInd( s8 achPwd[] );

    virtual const u16 HungupPtpConf();
	

	/** 
	* 功能  设置会场内发言人
	* @param [in]  byIndex  序号
	* @return 
	* @remarks 
	*/
	virtual u16 SetInnerSpeaker( u8 byIndex );


	/** 
	* 功能  开启/关闭本地哑音
	* @param [in]  bMute  开启/关闭
	* @return  
	* @remarks 
	*/
	virtual u16 SetCnsMute( BOOL bMute = TRUE );
	/** 
	* 功能  开启/关闭本地静音
	* @param [in]  bQutie  开启/关闭
	* @return  
	* @remarks 
	*/
    virtual u16 SetCnsQutie( BOOL bQutie = TRUE );
	/** 功能   设置单个麦克风状态
	*  @param[in] u8 麦克风索引 bcheck 开关选择
	*  @return 
	*/
	virtual u16 SetMicStateCmd( u8 nIndex, BOOL bCheck );

	/** 
	* 功能  调节输入声音
	* @return byVolume 音量
	* @remarks 
	*/
	virtual u16 AdjustInputVol( u8 byVolume );

	/** 
	* 功能  调节输出声音
	* @return byVolume 音量
	* @remarks 
	*/
	virtual u16 AdjustOutputVol( u8 byVolum );

	/** 
	* 功能  清空屏信息
	* @remarks 
	*/
	virtual void ClearCnsScreenInfo();


    /** 
	* 功能  设置选看
    * @param [in]  byScreenID  屏号
    * @param [in]  wEpID  选看的cnsID
	* @return  
	* @remarks 
	*/
	//virtual u16 SetSelView( u8 byScreenID, u16 wEpID ); ev_CnSingleView_Cmd消息废除 B4版本统一用ev_Cn_SelView_Req nlf确认 2015-5-28 dyy
	virtual u16 SetSelView( TTPSelViewReq tTPSelViewReq );

    /** 
	* 功能  取消选看
    * @param [in]  byScreenID  屏号 
	* @return  
	* @remarks 
	*/
	virtual u16 CancleSelView( u8 byScreenID );

   /** 
	* 功能  开启/停止轮询
    * @param [in]  bStart   true:开启，false：关闭
	* @return  
	*/
	virtual u16 StartPoll( BOOL  bStart );

	 /** 
	* 功能  开启/停止点名
    * @param 
	* @return  
	* @remarks 
	*/
	virtual u16 StartRoll( TTpConfRollCallInfo tTpConfRollCallInfo );
	/** 
	* 功能  点名下一个
    * @param [in]  tTpRollCallNextEpInfo  下一个的信息
	* @return  
	* @remarks 
	*/
	virtual u16 RollNext( TTpRollCallNextEpInfo tTpRollCallNextEpInfo );
	
	/** 
	* 功能  开启/停止混音
    * @param 
	* @return  
	* @remarks 
	*/
	virtual u16 StartConfMix( TTpAudMixInfo tTpAudMixInfo );
	/** 
	* 功能  //修改混音列表
    * @param [in]
	* @return  
	* @remarks 
	*/
	virtual u16 ConfMixFixCmd( TTpAudMixListCmd tTpAudMixListCmd );

    /** 
	* 功能  开启/停止双流
    * @param [in]  bStart   true:开启，false：关闭
	* @return  
	*/
	virtual u16 StartDual( BOOL  bStart );
    /** 
	* 功能  开启/停止双流码流
	* @return  BOOL  TRUE:开启， FALSE:停止
	* @remarks 
	*/
    virtual u16 StartDualCodeStream( const TTPCnMediaTransPort  &tVideoTransAddr , const TTPCnMediaTransPort  &tAudioTransAddr ) const;
   
    virtual u16 StopDualCodeStream() const  ;

	/** 
	* 功能  请求关键帧
	* @return  BOOL  TRUE:不受关键帧保护约束，强制发送关键帧， FALSE:受关键帧包含约束 2012.8.16 by yjj
	* @remarks 
	*/
    virtual u16 ReqKeyFrame( BOOL32 bForce ) const ;


     /** 
	* 功能  屏幕显示双流图像
	* @return    
	* @remarks 
	*/
    virtual u16 ScrnDisplayDual( const u16 wScrnID ) const ;


    /** 
	* 功能  屏幕显示双流图像
	* @return  
	* @remarks 
	*/
    virtual u16 ScrnStopDisplayDual( const u16 wScrnID ) const ;

     
    /** 
	* 功能  屏幕回显
	* @return    
	* @remarks 
	*/
    virtual u16 ScrnDisplayLocal( const u16 wScrnID ) const ;


    /** 
	* 功能  取消屏幕回显
	* @return    
	* @remarks 
	*/
    virtual u16 ScrnStopDisplayLocal( const u16 wScrnID ) const ;
 
	//开启画中画
	virtual u16 ViewLocalPIPCmd( const u8 byScrnID, const BOOL bLocalP );

    /** 
	* 功能  设置选看电视墙
    * @param [in]  byScreenID  屏号
	* @return  
	* @remarks 
	*/
	virtual u16 SelTVSView( u8 byScreenID );

    /** 
	* 功能  取消选看电视墙
    * @param [in]  byScreenID  屏号 
	* @return  
	* @remarks 
	*/
	virtual u16 CancelSelTVSView( u8 byScreenID );

	/** 
	* 功能  单独控制坐席激励
    * @param [in]  BOOL bIsAudMix 是否开启
	* @return  
	* @remarks 
	*/
	virtual u16 SetCnAuxMix( BOOL bIsAudMix );
		/** 
	* 功能  空闲状态双流开启
    * @param [in]  wID  预置位号
	* @return  
	* @remarks 
	*/
	virtual u16 SpareTimeScreenDualSet( u8 wID ,BOOL bIsShow );

    /** 
	* 功能  开启语音激励
    * @param [in]  TTPVacInfo tTPVacInfo 语音激励信息
	* @return  
	* @remarks 
	*/
	virtual u16 SetVoiceArouse( TTPVacInfo &tTPVacInfo );
	
public: //获取lib中缓存信息
   /** 
	* 功能  获取输出声音
	* @return  u8  音量
	* @remarks 
	*/
	virtual const u8& GetOutputVol() const;


   /** 
	* 功能  获取输入声音
	* @return  u8  音量
	* @remarks 
	*/
	virtual const u8& GetInputVol() const;


   /** 
	* 功能  获取会场内发言人
	* @return byIndex  序号
	* @remarks 
	*/
	virtual u8 GetInnerSpeaker() const;

	/** 
	* 功能  本地CNS是否哑音
	* @return  BOOL  是否哑音
	* @remarks 
	*/
	virtual BOOL IsLocalCnsMute() const;
	/** 
	* 功能  本地CNS是否静音
	* @return  BOOL  是否静音
	* @remarks 
	*/
    virtual BOOL IsLocalCnsQuite() const;

	/** 
	* 功能  本地画中画是否开启
	* @return  
	* @remarks 
	*/
    virtual BOOL IsViewLocalPIP() const;
    /** 
	* 功能  获取CNS会议状态
	* @return TTPCnsConfStatus 会议状态
	* @remarks 
	*/
	virtual const TTPCnsConfStatus& GetCnsConfStatus() const;


   /** 
	* 功能  获取屏信息
	* @return vector<TScreenInfo> 屏信息
	* @remarks 
	*/
	virtual const vector<TScreenInfo>& GetCnsScreenInfo() const;

   /** 
	* 功能  本地CNS是否开启双流
	* @return  BOOL  是否静音
	* @remarks 
	*/
    virtual BOOL IsLocalCnsDual() const;
	
	/** 
	* 功能  点对点会议坐席激励
	* @return  BOOL  是否点对点会议坐席激励
	* @remarks 
	*/
    virtual BOOL IsLocalPTPSeatArouse() const;

    /** 
	* 功能  多点会议会场语音激励
	* @return  BOOL  是否多点会议会场语音激励
	* @remarks 
	*/
    virtual BOOL IsLocalMultiVoiceArouse() const;

    virtual TTPCnMediaTransPort GetVedioTransAddr() const { return m_tVideoTranAddr ;}
    virtual TTPCnMediaTransPort GetAudioTransAddr() const { return m_tAudioTranAddr ;}


    //virtual TScreenInfo *GetScreenInfoByID( const u8 byScreenID )  ;

    virtual BOOL32 IsRcvDual() const { return m_bRecvDual; }
	virtual TTpConfRollCallInfo GetRollState() const { return m_tTpConfRollCallInfo; }
	virtual TTpRollCallPresentStateMsg GetRollAttendState() const { return m_tTpRollCallPresentStateMsg; }
	virtual TTpAudMixInfo GetConfMixState() const { return m_tTpAudMixInfo; }
	virtual TTpAudMixListCmdRes GetConfMixIndFix() const { return m_tTpAudMixListCmdRes; }
protected:
    virtual void OnTimeOut(u16 wEvent); 
    virtual void DispEvent(const CMessage &cMsg);
	void BuildEventsMap();

	void OnLinkBreak(const CMessage& cMsg);

	/** 功能  会议状态通知
	* @param [in]  cMsg  消息内容
	* @return 
	* @remarks 消息  cns->cms  ev_CnConfState_Nty
	*/
	void OnConfStateNty(const CMessage& cMsg);
	/**
    * 功能: 哑音通知 
	* @param [in]	cMsg:消息内容
	* @return  无
	* @remarks 消息  cns->cms  ev_tppMuteInd
	*/
	void OnMuteInd(const CMessage &cMsg);
	/**
    * 功能: 静音通知 
	* @param [in]	cMsg:消息内容
	* @return  无
	* @remarks 消息  cns->cms  ev_tppQuietInd
	*/
	void OnQuietInd(const CMessage &cMsg);
	/**
    * 功能: 输入音量通知 
	* @param [in]	cMsg:消息内容
	* @return  无
	* @remarks 消息  cns->cms  ev_tppInputVolumeInd  
	*/
	void OnInputVolInd(const CMessage &cMsg);
	/**
	* 功能: 输出音量通知 
	* @param [in]	cMsg:消息内容
	* @return  无
	* @remarks 消息  cns->cms  ev_tppOutputVolumeInd  
	*/
	void OnOutPutVolInd(const CMessage &cMsg);
	/**
	* 功能: 设置会场发言人通知 
	* @param [in]	cMsg:消息内容
	* @return  无
	* @remarks 消息  cns->cms  ev_CnSetInnerSpeaker_Ind  
	*/
	void OnSetInnerSpeaker( const CMessage &cMsg);
	/**
	* 功能: 屏显示会场通知 
	* @param [in]	cMsg:消息内容
	* @return  无
	* @remarks 消息  cns->cms  ev_CnYouAreSeeing_Ind  
	*/
	void OnScreenDisplayInd(const CMessage &cMsg);

	void UpdateScreenInfo( u8 byScreen, s8* achCnsName );
    void UpdateScreenInfo( u8 byScreen, s8* achCnsName,EMPosPic emPic );
	void UpdateScreenInfo( u8 byScreen, EmTPPosStatus emStatus, EMPosPic emPos );
     
    void OnScreenStateNotify( const CMessage &cMsg );
    //选看回应
	void OnSetSelViewInd( const CMessage &cMsg );
	void OnSetSelViewNty( const CMessage &cMsg );
    
	void OnStartPollRsp( const CMessage &cMsg ); 

    void OnStartDualRsp( const CMessage &cMsg );
	void OnDualStatusNty( const CMessage &cMsg );
    void OnHungupNotify( const CMessage &cMsg );

    void OnStartDualCdStrmRsp( const CMessage &cMsg );
    void OnStopDualCdStrmRsp( const CMessage &cMsg );

    void OnScrnDisplayDualRsp( const CMessage &cMsg );
    void OnStopScrnDisplayDualRsp( const CMessage &cMsg );
    
    void OnScrnDisplayLocalRsp( const CMessage &cMsg );
    void OnStopDisplayLocalRsp( const CMessage &cMsg );

    void OnRecvDualNty( const CMessage &cMsg );
	void OnCnDualOfflineNty( const CMessage &cMsg );
    void OnDualRcvInterruptNty( const CMessage &cMsg );

	void OnViewLocalPIPInd( const CMessage &cMsg );
	void OnViewLocalPIPNty( const CMessage &cMsg );
	void OnSetSelTVSViewRsp( const CMessage &cMsg );
	//麦克风相关
	void OnCnSetDesktopMicInfoNty( const CMessage &cMsg );
	void OnCnSetDesktopMicInfoInd( const CMessage &cMsg );
	void OnCnMicPowerStyleNty( const CMessage &cMsg );
	void OnCnMicPowerNty( const CMessage &cMsg );
	void OnCnSetMicPowerRsp( const CMessage &cMsg );

	//空闲双流设置
	void OnSpareDualSetNty(const CMessage& cMsg);
	void OnSpareDualSetInd(const CMessage& cMsg);
	//单独坐席激励回复
	void OnCnAuxMixInd(const CMessage& cMsg);
	//开启点名回复
	void OnStartRollNty(const CMessage& cMsg);
	void OnStartRollInd(const CMessage& cMsg);
	//点名下一个回复
	void OnRollNextInd(const CMessage& cMsg);

	//被点名者与会状态发送
	u16 RollAttendState( TTpRollCallPresentStateMsg tTpRollCallPresentStateMsg );
	//被点名者与会状态回应；整体列表中与会状态登陆时通知
	void OnRollAttendNty( const CMessage &cMsg );

	//开启会议后被点名者列表更新
	u16 RollListFixedCmd(TTpUpdataRollCallList tTpUpdataRollCallList);
	//开启会议后被点名者列表更新回复
	void OnRollListFixedInd(const CMessage& cMsg);

	//开启会议混音回应
	void OnStarConfMixInd(const CMessage& cMsg);
	//修改混音列表结果通知
	void OnConfMixFixInd(const CMessage& cMsg);

	//会议混音状态通知
	void OnConfMixStateNty(const CMessage& cMsg);

	//当前会场是否在会议混音中通知
	void OnEpInAudMixNty(const CMessage& cMsg);

    //询问会议模板密码
    void OnCnGetTempPwdCmd(const CMessage& cMsg);

    //多点会议会场语音激励通知
    void OnVoiceArouseNty(const CMessage& cMsg);
    //多点会议会场语音激励反馈
    void OnVoiceArouseInd(const CMessage& cMsg);

private:
	CCnsSession      *m_pSession;

	TTPCnsConfStatus m_tCnsConfStatus;

    TTPCnMediaTransPort m_tVideoTranAddr;
    TTPCnMediaTransPort m_tAudioTranAddr;
    u16              m_nVideoNode;
    u16              m_nAudioNode;
	u8               m_bySpeakSeat; //发言坐席ID
	u8	             m_byInputVol;	//输入声音
	u8				 m_byOutputVol;	//输出声音
	BOOL32			 m_bMute;	    //是否哑音		
	BOOL32			 m_bQuite;      //是否静音
    BOOL32           m_bDual;
    BOOL32           m_bRecvDual;
	vector<TScreenInfo>  m_vctScreenInfo;
	vector<TTPNMServerCfg> m_vecTTPNMServerCfg;		//网管服务器信息
    BOOL32           m_bVoiceArouse;//是否开启语音激励
    BOOL32           m_bLocalPIP;	//是否开启画中画
	BOOL32           m_bPTPSeatArouse;//是否开启点对点坐席激励
	TTpConfRollCallInfo   m_tTpConfRollCallInfo;//点名状态
	TTpRollCallPresentStateMsg   m_tTpRollCallPresentStateMsg;//点名与会状态
	TTpAudMixInfo   m_tTpAudMixInfo;//混音状态
	TTpAudMixListCmdRes m_tTpAudMixListCmdRes;//修改混音结果
	BOOL32			 m_bInAudMix;   //是否在会议混音中
	TTpMicState      m_tTpMicStyle; //麦克风风格
	TTpMicState      m_tTpMicState; //麦克风状态
};

#endif // !defined(AFX_CNCCONFCTRL_H__2EF9234D_820A_40F3_9DC4_967387311945__INCLUDED_)
