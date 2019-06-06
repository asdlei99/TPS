/** @defgroup cnc调用cnclib的公共接口 
 *  @version V1.1.4
 *  @author  肖楚然
 *  @date    2014.8.14
 */
#pragma once

#include "cnclib.h"

class CCommonInterface
{
public:
	/** 创建会话
	*   @return u16 成功返回0;失败返回非0错误码 
	*/
	void CreateSession();

	/** 销毁会话
	*   @return u16 成功返回0;失败返回非0错误码 
	*/
	void DesdroySession();

	/** 获取内嵌的窗口句柄
	*   @return HWND 返回窗口句柄 
	*/
	HWND GetRecvWindow(){ return m_hRecvWnd;};
	/**
	* 功能   连接CNS
	* @param [in]  dwIP	被连接UMS的IP地址，主机序
	* @param [in]  pStrUserName 用户名	
	* @param [in]  pStrPswd	密码
	* @return u16 成功返回0;失败返回非0错误码 
	*/
	u16 Connect( u32 dwIp, u16 nPort, LPCTSTR pStrUserName, LPCTSTR pStrPswd ); 

	u16 RebootCns();

	u16 LinkCns();

    /** 功能   获得登陆CNS的配置
	*  @param[out] tLoginInfo
	*  @return 成功返回0,失败返回非0错误码
	*/
    u16 GetLoginInfo( TLoginInfo& tLoginInfo );
	/** 功能   设置登陆CNS的配置
	*  @param[out] tLoginInfo
	*  @return 成功返回0,失败返回非0错误码
	*/
    u16 SetLoginInfo( TLoginInfo tLoginInfo );

	/**
	* 功能:  当前登录的用户是否是管理员
	* @return  TRUE 是管理员，FALSE 一般用户
	*/
	BOOL IsManagerUser();

	//-----会场控制相关接口 -------------
/** @defgroup  会场控制相关接口
 *  @{
 */  
	/**
	* 功能:  获取本地cns信息 
	*  @param[out] tCnsInfo：本CNS信息
	*  @return 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	u16 GetLocalCnsInfo( TTPCnsInfo& tCnsInfo) const;
  
	/**
	* 功能:  更新cns信息 
	* @param[in] tInfo CNS信息  byIndex 消息来自哪里(0为cnc 1为维护工具)
	* @return 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	u16 UpdateCnsInfo( const TTPCnsInfo& tInfo, u8 byIndex = 0, EmTpIpNameNatSyn em= emSynInvalid);

	/**
	* 功能:  获取本cns屏信息 
	* @param[out] vctScreenInfo：本cns屏信息
	* @return 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	u16 GetCnsScreenInfo( vector<TScreenInfo>& vctScreenInfo ) const;

    u16 GetCnsScreenInfoByID( u8 screenID, TScreenInfo& tScreenInfo ) const;

	/**
	* 功能:  清空本cns屏信息 
	* @remarks 
	*/
	void ClearCnsScreenName();

	/**获取当前全景摄像机状态
	*  @param[in] 
	*  @return BOOL 是否开启
	*/
	BOOL32 IsLocalCnsPanCam(); 

	/**本地会场全景摄像机状态 设置
	*  @param[in] Quite 是否开启
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 SetLocalCnsPanCam(u8 wCamId ,BOOL bPanCam = TRUE);

	/**获取当前speaker状态，是否为静音
	*  @param[in] 
	*  @return BOOL 是否为静音
	*/
	BOOL32 IsLocalCnsQuite();

	/**获取当前Mic状态，是否为 哑音
	*  @param[in] 
	*  @return BOOL 是否为哑音
	*/
	BOOL32 IsLocalCnsMute(); 

	/**本地会场静音 设置
	*  @param[in] Quite 是否静音
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 SetLocalCnsQuite( BOOL bQuite = TRUE );

	/**本地会场哑音 设置
	*  @param[in] bMute 是否哑音
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 SetLocalCnsMute( BOOL bMute = TRUE );

	/**调节会场输入音量
	*  @param[in] byVolume 音量
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 AdjustInputVol( u8 byVolume );

	/**调节会场输出音量
	*  @param[in] byVolume 音量
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 AdjustOutputVol( u8 byVolume );
	
	/**获取会场输入音量
	*  @return  byVolume 音量
	*/
	u8 GetInputVol();

	/**获取会场输出音量
	*  @return byVolume 音量
	*/
	u8 GetOutputVol();

	/**设置会场发言坐席
	*  @param[in] bySeatId 坐席ID
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 SetCnsInnerSpeaker( u8 bySeatId );

	/**获取会场发言坐席
	*  @param[in] 
	*  @return 坐席ID
	*/
	u8 GetCnsInnerSpeaker();


	/** 
	* 功能  本地CNS是否开启画中画
	* @return  BOOL  是否双流
	* @remarks 
	*/
	BOOL32 IsViewLocalPIP();
	/** 
	* 功能  获取点名状态
	* @return  
	* @remarks 
	*/
   BOOL32 GetRollState(TTpConfRollCallInfo &tTpConfRollCallInfo);
   /** 
	* 功能  获取点名与会状态
	* @return  
	* @remarks 
	*/
   BOOL32 GetRollAttendState(TTpRollCallPresentStateMsg &tTpRollCallPresentStateMsg);
   	/** 
	* 功能  获取混音状态
	* @return  
	* @remarks 
	*/
   BOOL GetConfMixState(TTpAudMixInfo &tTpAudMixInfo);
    /** 
	* 功能  获取混音列表修改回应
	* @return  
	* @remarks 
	*/
   BOOL GetConfMixIndFix(TTpAudMixListCmdRes &tTpAudMixListCmdRes);
	/** 
	* 功能  本地CNS是否开启画中画
	* @return  BOOL  是否双流
	* @remarks 
	*/
	u16 ViewLocalPIPCmd( const u8 byScrnID, const BOOL bLocalP ) ;

/** @}*/

	//-----会控相关接口 -------------
/** @defgroup  会控相关接口
 *  @{
 **
  
    /*
	**询问会议模板密码
	*/
	u16 GetCnTempPwdInd( s8 achPwd[] );

	/**开启点对点会议 
	*  @param[in] tCnAddr   对端会场
	*  @return  
	*/
	u16 StartP2PConf( TCnAddr& tCnAddr );

    u16 HungupPtpConf();

	/**
	* 功能:  使用会议模板开会 
	* @param [in]  tTemp: 模板 
	* @return 成功返回0，失败返回错误码
	*/
	u16 StartTemplateConf( const TTPAlias& tTemp ) ; 	

	/**
	* 功能:  开启一个即时会议 
	* @param [in] tCnsList :与会的终端列表 ,本会场为第一个成员，并设置为主会场
	* @param [out] achConfName :会议名
	* @return 成功返回0，失败返回错误码
	* @remarks ums预存一个用于开启临时会议的会议模板（ID为0），该会议模板界面不显示
	*/
	u16 StartInstantConf( const vector<TCnAddr>& tCnsList );	
 
	/**
	* 功能:  挂断会议 
	* @param [in] dwConfID：会议ID
	* @return 成功返回0，失败返回错误码
	* @remarks 结束会议
	*/
	u16 HangupConf( );

         
	/**
	* 功能:  邀请某会场参与会议 
	* @param [in] tEp:会场信息
	* @return 成功返回0，失败返回错误码
	* @remarks 当本会场为主会场时方可操作
	*/
	u16 InviteCns( const TTpCallAddr &tEp );

    /**
	* 功能:  邀请多个会场参与会议 
	* @param [in] tEp:会场信息
	* @return 成功返回0，失败返回错误码
	* @remarks 当本会场为主会场时方可操作
	*/
	u16 InviteCns( const tagConfCallEpAddrList &tEp );

    /**
    * 功能:	呼叫会议中已经存在的cns会场加入某会议
	* @param [int]  tEp	 会议和会场信息
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 消息：cms->ums  evtp_CallEP_cmd  \n
                       应回复：ums->cms evtp_CallEP_result   \n
	                   若成功，还应发：ums->cms evtp_UpdateConfCnsList_Notify
	*/ 
   u16 CallConfCns( const TConfEpID &tEp );
	 
    /**
	* 功能:  获取会议中cns的信息
	* @param [in] tEp:会场信息
    * @param [out] tCnsInfo:会场信息
	* @return 成功返回0，失败返回错误码
	* @remarks 当本会场为主会场时方可操作
	*/
    u16 GetConfCnsByID( const TConfEpID &tConfEpInfo , TCnsInfo* pTCnsInfo); 	

	/**
    * 功 能:	获取会议模板列表
	* @param 无
	* @return  会议模板列表
	*/
	const vector<TTPAlias>& GetConfTempList();

	/**
    * 功 能:	更新会议模板
	* @return  成功返回0,失败返回非0错误码
	*/
	u16 UpdateConfTemplate();


	/**
	* 功能:  获取本地cns会议状态
	* @return cns会议状态
	* @remarks 
	*/
    TTPCnsConfStatus GetLocalCnsConfState() const; 

	/**
	* 功能:  是否在会议中  
	* @param [out]  pConf   返回会议信息
	* @return  返回是否在会议中
	*/
	BOOL32 IsInConf( TCMSConf *pConf = NULL );

	/** 
	* 功能  开启/停止双流
    * @param [in]  bStart  true:开启，false：关闭
	* @return  
	* @remarks 
	*/
	u16 StartDual( BOOL32 bStart );

	//请求码流
	u16 StartDualCodeStream( const TTPCnMediaTransPort  &tVedioTransAddr, const TTPCnMediaTransPort  &tAudioTransAddr  ) const;
	u16 StopDualCodeStream() const;

	u16 ReqKeyFrame( BOOL32 bForce = TRUE ) const;

	TTPCnMediaTransPort GetVedioTransAddr() const  ;
	TTPCnMediaTransPort GetAudioTransAddr() const  ;

	/** 
	* 功能  本地cns是否开启双流
    * @param [in]  
	* @return  true:开启，false：关闭  
	*/
	BOOL32 IsLocalCnsDual() const;
	//点对点会议语音激励状态
	BOOL32 IsLocalPTPVoiceArouse() const;

	/** 
	* 功能  开启/停止轮询
    * @param [in]  bStart  true:开启，false：关闭
	* @return  
	* @remarks 
	*/
	u16 StartPoll( BOOL32 bStart );
	/** 
	* 功能  开启/停止点名
    * @param [in]  tTpConfRollCallInfo  点名信息
	* @return  
	* @remarks 
	*/
	u16 StartRoll( TTpConfRollCallInfo tTpConfRollCallInfo );
	/** 
	* 功能  点名下一个
    * @param [in]  tTpRollCallNextEpInfo  下一个的信息
	* @return  
	* @remarks 
	*/
	u16 RollNext( TTpRollCallNextEpInfo tTpRollCallNextEpInfo );
	/** 
	* 功能  与会状态更新
    * @param [in]  tTpRollCallPresentStateMsg  与会状态
	* @return  
	* @remarks 
	*/
	u16 RollAttendState( TTpRollCallPresentStateMsg tTpRollCallPresentStateMsg );
	/** 
	* 功能  开启点名后进行列表修改
    * @param [in]  tTpUpdataRollCallList  列表信息
	* @return  
	* @remarks 
	*/
	u16 RollListFixedCmd( TTpUpdataRollCallList tTpUpdataRollCallList );

	/** 
	* 功能  开启/停止混音
    * @param [in]  tTpAudMixInfo  混音信息
	* @return  
	* @remarks 
	*/
	u16 StartConfMix( TTpAudMixInfo tTpAudMixInfo );
	/** 
	* 功能  修改混音列表
    * @param [in]  tpAudMixListCmd  修改信息
	* @return  
	* @remarks 
	*/
	u16 FixConfMix( TTpAudMixListCmd tpAudMixListCmd );
	
	/**
	* 功能:  挂断某会场 
	* @param [in] tConfEpInfo: eqID 会议ID
	* @return 成功返回0，失败返回错误码
	* @remarks 会议列表中依然存在该会场，只是不在线
	*/
    u16 HangupCns( const TConfEpID &tConfEpInfo );

	/*功  能	会场摄像机控制
	参  数	tConfEpInfo: eqID 会议ID
	返回值	成功返回0，失败返回错误码
	说  明	摄像机远摇操作，保存远摇会场信息*/
	u16 SetFeccConfEpInfo( const TConfEpID &tConfEpInfo );

	/*功  能	会场摄像机控制
	参  数	tConfEpInfo: eqID 会议ID
	返回值	成功返回0，失败返回错误码
	说  明	摄像机远摇操作，获取远摇会场信息*/
	u16 GetFeccConfEpInfo( TConfEpID &tConfEpInfo );

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
    u16 SetFeccCamPT( EmDirection emDirection, EmCnAction emCnAction );

	/** 功能   远摇摄像机视野调节
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 SetFeccCamView( EmZoom emZoom, EmCnAction emCnAction );

	/** 功能   远摇摄像机调节亮度
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 SetFeccCamBright( EmPanCamBright emPanCamBright, EmCnAction emCnAction );

		/** 功能   远摇摄像机调节焦距 
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 SetFeccCamFocus( EmFocus emFocus, EmCnAction emCnAction );

	/** 功能   远摇摄像机自动调节焦距 
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 SetFeccCamAotoFocus();
 
	/**
	* 功能:  从会议中移除某会场 
	* @param [in] tConfEpInfo: eqID 会议ID
	* @return 成功返回0，失败返回错误码
	* @remarks 移除后会议列表中不存在该会场 ,暂时不用该接口
	*/
	u16 RemoveCns( const TConfEpID &tConfEpInfo );

	/**
	* 功能:  设置发言会场
	* @param [in]wConfID	 会议ID
	* @return 成功返回0，失败返回错误码 
	*/ 
	u16 SetSpokeCns( const TConfEpID &tConfEpInfo );
    /**
	* 功能:  设置会场哑音
	* @param [in]
	* @return 成功返回0，失败返回错误码 
	*/ 
    u16 SetMuteCns( const TConfEpID &tConfEpInfo , BOOL32 bMute);
    /**
	* 功能:  设置会场静音
	* @param [in]
	* @return 成功返回0，失败返回错误码 
	*/
    u16 SetQuietCns( const TConfEpID &tConfEpInfo, BOOL32 bQuiet);
    /**
	* 功能:  设置会场双流
	* @param [in]
	* @return 成功返回0，失败返回错误码 
	*/
    u16 SetDualCns( const TConfEpID &tConfEpInfo, BOOL32 bStart );
     
    /** 
	* 功能:  更新混音列表请求
    * @param [in	tMixInfo	 混音列表
    * @return	成功返回0,失败返回非0错误码
    * @remarks 	 */
	u16 UpdateAudMixList( const TConfAuxMixInfo &tMixInfoList );

	/** 
	* 功能:  语音激励
    * @param [in	TConfAuxMixVacOpr	 
    * @return	成功返回0,失败返回非0错误码
    * @remarks 	 */
	u16 AuxMixVacOpr( const TConfAuxMixVacOpr tConfAuxMixVacOpr);
	/** 
	* 功能:  单独控制语音激励
    * @param [in	是否开启	 
    * @return	成功返回0,失败返回非0错误码
    * @remarks 	 */
	u16 SetCnAuxMix( BOOL bIsAudMix);
	/** 
	* 功能:  发送UI_CNS_CONFSTATE_NOTIFY消息刷新界面会议状态
    * @param [in	 
    * @return	成功返回0,失败返回非0错误码
    * @remarks 	 */
	u16 FreshConf();
	/** 
	* 功能:  混音列表操作请求
    * @param [in	tDisListOpr	 混音列表操作
    * @return	成功返回0,失败返回非0错误码
    * @remarks 	 */
	u16 AudMixDisListOpr( const TDiscussListOpr &tDisListOpr );

     /** 
	* 功能  取消选看
    * @param [in]  byScreenID  屏号
	* @return  
	* @remarks 
	*/
	u16 ScrnCancleSelView( u8 byScreenID );

	/** 
	* 功能  屏幕显示双流图像
	* @param [in]  wScrnID  屏号
	* @return
	* @remarks 
	*/
    u16 ScrnDisplayDual( const u16 wScrnID ) const;

		/** 
	* 功能  屏幕显示双流图像
	* @param [in]  wScrnID  屏号 bIsShow 是否显示
	* @return
	* @remarks 
	*/
    u16 ScrnSpareTimeDisplayDual( u16 wScrnID, BOOL bIsShow);

     /** 
	* 功能  屏幕取消显示双流图像
	* @return  
	* @remarks 
	*/
    u16 ScrnStopDisplayDual( const u16 wScrnID ) const;

    /** 
	* 功能  屏幕显示回显
	* @param [in]  wScrnID  屏号
	* @return    
	* @remarks 
	*/
    u16 ScrnDisplayLocal( const u16 wScrnID ) const;

    /** 
	* 功能  取消屏幕回显
	* @return    
	* @remarks 
	*/
    u16 ScrnStopDisplayLocal( const u16 wScrnID ) const;

    /** 
	* 功能  是否接收双流
	* @return    
	* @remarks 
	*/
    BOOL32 IsRcvDual() const; 
    /**
	* 功能:  获取画面合成状态
	* @return 画面合成状态
	* @remarks 
	*/
    const vector<TBrdVmpResNtfy>& GetBrdVmpStatus(); 
    /**
	* 功能:  获取会议选看状态
	* @return 会议选看状态
	* @remarks 
	*/
    const TTPSelViewNtfy GetSelWatchStatus();
		/** 
	* 功能  ums错误问题
	* @return  错误问题
	* @remarks 
	*/
	const TTPUmsReasonInd GetUmsReason();
	//获得会议讨论列表
	const TDiscussListOpr GetDiscussList();
	//获得加入会议会场信息
	const TTpConfEpInfo GetJoinConfInfo();
	//设置是否允许会场加入会议
	u16 SetJoinConfInfo(TTpConfEpInfo tpConfEpInfo);
	//获取全场静音哑音状态
	bool IsAllQuite();
	bool IsAllMute();

    /**
	* 功能:  占用画面合成器
    * @param [in]  tEqpInfo  画面合成器
	* @return 
	*/
    u16 RervesBrdVmpReq( TRersvesEqpReq tRersvesEqp );
    /**
	* 功能:  配置画面合成
    * @param [in]  tVmpInfo  画面合成信息
	* @return 
	*/
    u16 SetBrdVmpReq( TSetVmpInfoReq tVmpInfo );
    /**
	* 功能:  广播画面合成
    * @param [in]  tVmpInfo  画面合成信息
	* @return 
	*/
    u16 SetBroadcastVmpReq( TBrdVmpReq tBrdVmp );
    /**
	* 功能:  保存合成预案
    * @param [in]  tVmpInfo  画面合成信息
	* @return 
	*/
    u16 SaveVmpCfgReq( TBrdVmpResNtfy &tBrdVmp );
    /**
	* 功能:  调用合成预案
	* @return 
	*/
    u16 CallVmpCfgReq( TEqpInfo &tEqp );

	/**
	* 功能:  改变电视墙模式
	* @return 
	*/
	u16 ChangeChanModeReq( u16 wIndex, u8 byMode  );
    /**
	* 功能:  设置电视墙音量
	* @return 
	*/
	u16 SetHduVolReq( u16 wIndex, u8 byVol ,BOOL32 bMute );
    /**
	* 功能:  停止电视墙
	* @return 
	*/
	u16 StopPlayHdu( TTpHduPlayReq &tTvwInfo);
    /**
	* 功能:  播放电视墙
	* @return 
	*/
	u16 PlayHduReq( TTpHduPlayReq &tTvwInfo );

/** @}*/ 

	 //-----系统配置相关设置-------------  
/** @defgroup  系统配置
 *  @{
 */

	/** 功能   获得演示源信息
	*  @param[out] tDualSrcinfo 演示源配置
	*  @return 成功返回0,失败返回非0错误码
	*/
    u16 GetDualSrcInfo( TDualSrcInfo& tDualSrcinfo );

    /** 功能   选择演示源端口
	*  @param[out] emType 演示源类型
	*  @return 成功返回0,失败返回非0错误码
	*/
    u16 SelDualInputPort( EmVgaType emType );

    /** 功能   设置演示源信息
	*  @param[in] tVgaInfo 演示源信息
    *  @param[in] bDefault 是否默认演示源
	*  @return 成功返回0,失败返回非0错误码
	*/
    u16 SetDualPortInfo( const TVgaInfo& tVgaInfo, BOOL bDefault );

	/** 功能   获得SIP配置
	*  @param[out] tSipCfg SIP配置
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetSipCfg( TTPSipRegistrarCfg& tSipCfg );

    /** 功能   获得Gk配置
	*  @param[out] tGkCfg
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetGkCfg( TTPGKCfg& tGkCfg );

	/** 功能:  更新网络配置
	*  @param[in] tInfo 网络配置
	*  @return 成功返回0,失败返回非0错误码
	*  @remarks 
	*/
	u16 UpdateEthnetCfg( const TTPEthnetInfo& tInfo, EmTpIpNameNatSyn em= emSynInvalid );

	/** 功能   获得网络配置
	*  @param[out] tInfo 网络配置
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetEthnetCfg( TTPEthnetInfo& tInfo );

	/** 功能   获得NAT配置
	*  @param[out] tInfo NAT配置
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetNATCfg( TTPNatCfg& tInfo );

	 /** 功能   设置系统时间
	 *  @return 成功返回会场名,失败返回NULL
	 *  @remarks 
	 */
     u16 UpdateSysTime( const TTPTime& time ) ;
      
    /** 功能   获取系统时间
	 *  @return 成功返回会场名,失败返回NULL
	 *  @remarks 
	 */
    u16 ReqSysTime();

	/** 功能   升级服务器地址
	 *  @param[in] TTPUpgradeSer 服务器地址结构体
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 UpgradeSerCmd( const TTPUpgradeSer& tUpgradeSer );

	/**获取服务器发过来的网管信息页数据 
	*/
	u16 GetNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg );

 	/**
    * 功能:	 	        发送添加网管请求
 	* @param [in]       网管信息
 	* @return           u16 成功返回0,失败返回非0错误码
 	*/
 	u16  NetMngAddCmd( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * 功能:	 	        发送修改网管请求
 	* @param [in]       网管信息
 	* @return           u16 成功返回0,失败返回非0错误码
 	*/
	u16  NetMngModifyCmd( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * 功能:	 	        发送删除网管请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  NetMngDeleteCmd( const TTPNMServerCfg& tTPNMServerCfg );

	/** 功能   设置系统待机信息
	*  @param[in] tTPSleepInfo 系统待机信息
    *  @param[in] bDefault 是否启用系统待机
	*  @return 成功返回0,失败返回非0错误码
	*/
    u16 SetSysSleepInfo( const TCenDevSleepInfo& tCenDevSleepInfo );

	/** 功能   获得系统待机信息
	*  @param[out] tDualSrcinfo 演示源配置
	*  @return 成功返回0,失败返回非0错误码
	*/
    u16 GetSysSleepInfo( TCenDevSleepInfo& tCenDevSleepInfo );

	/** 功能:  CNS设置SIP注册配置 
	*  @param[in] tSipCfg Sip注册配置
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 CnsRegSipService( const TTPSipRegistrarCfg &tSipCfg );

	/** 功能:  CNS注销SIP服务 
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 CnsUnRegSipService();

    /** 功能:  CNS设置Gk注册配置 
	*  @param[in] tSipCfg Sip注册配置
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 CnsRegGkService( const TTPGKCfg &tCfg );

	/** 功能:  更新NAT配置
	*  @param[in] tInfo NAT配置
	*  @return 成功返回0,失败返回非0错误码
	*  @remarks 
	*/
	u16 UpdateNATCfg( const TTPNatCfg& tInfo, EmTpIpNameNatSyn em= emSynInvalid );

	/** 功能   获得服务器地址
	*  @param[out] TTPUpgradeSer 服务器地址结构体
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetUpgradeSerInfo( TTPUpgradeSer& tUpgradeSer );

	/** 功能   呼叫服务器
	*   @param[in] u32_ip 服务器地址
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 CallServerCmd( const TTPCallSerInfo& tCallSerInfo );

	/** 功能   获取呼叫服务器配置
	*  @param[out] TTPCallSerInfo 呼叫服务器配置
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetCallServerInfo( TTPCallSerInfo& tCallSerInfo );

	/**功能    获取当前画面裁剪状态，是否开启
	*  @param[in] 
	*  @return BOOL 是否开启
	*/
	BOOL32 IsVidCutLine() const;
	/** 
	* 功能  设置画面裁剪
    * @param [in]  BOOL bIsVidCutLine 是否开启
	* @return  
	* @remarks 
	*/
	u16 SetVidCutLine( BOOL bIsVidCutLine );
	
	/** 功能   设置量子加密
	 *  @return
	 */
	u16 SetQtEncryptCfg( const TTpQtEncryptCfg& tQtEncrypt);
	/** 功能   获得量子加密信息
	 *  @return TTpQtEncryptCfg量子加密信息
	 */
    u16 GetQTEncrypt(TTpQtEncryptCfg& tQtEncrypt);
	/**
    * 功能:	 	        时间同步请求
 	* @param [in]       
 	* @return           u16 成功返回0,失败返回非0错误码
 	*/
 	u16  SetTimeSynchroCmd( BOOL bIsCheck );
/** @}*/ 

	//密码周期更新
	u16 SetTpadPasswordUpdate( TTpPasswordUpdateInfo tTpPasswordUpdateInfo );
	//获取密码周期信息
	u16 GetPasswordUpdateInfo( TTpPasswordUpdateInfo& tTpPasswordUpdateInfo );

    //超级管理员信息
    u16 SetSuperadmninInfo(TTpSuperUser tTpSuperUser);
    u16 GetSuperadmninInfo(TTpSuperUser& tTpSuperUser);
    //超级管理员解锁所有用户
    u16 UnlockAllUser();

	//-----地址簿相关-------------  
/** @defgroup  地址簿相关
 *  @{
 */	 
	/** 功能:  获取地址簿
	 *  @return CAddrBook 返回地址簿对象
	 */
	CAddrBook& GetAddrBook();

	/** 功能:  添加地址簿条目
	 *  @param[in] entry 地址簿条目
	 *  @return 成功返回0,失败返回非0错误码
	 */ 
	u16 AddEntry( const CAddrEntry& entry );

	/** 功能:  修改地址簿条目
	 *  @param[in] entry 地址簿条目
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 ModifyEntry( const CAddrEntry& entry );

	/** 功能:  删除地址簿条目
	 *  @param[in] dwIndex 地址簿条目索引
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 DeleteEntry( u32 dwIndex );

	/** 功能:  删除多个地址簿条目
	 *  @param[in] vctEntry 地址簿条目索引表
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 DeleteMultiEntry( vector<u32>& vctEntry );

	/** 添加地址簿条目组
	 *  @param[in] group 地址簿条目组
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 AddGroup( const CAddrMultiSetEntry& group );

	/** 修改地址簿条目组
	 *  @param[in] entry 地址簿条目组
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 ModifyGroup( const CAddrMultiSetEntry& group );

	/** 删除地址簿条目组
	 *  @param[in] dwIndex 地址簿组索引
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 DeleteGroup( u32 dwIndex );

    /** 功能:  删除多个地址簿组
	 *  @param[in] vctGroup 地址簿组索引表
	 *  @return 成功返回0,失败返回非0错误码
	 */
    u16 DeleteMultiGroup( vector<u32>& vctGroup );

	/** 添加地址簿组成员
	 *  @param[in] tGroupEntry 地址簿组信息
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 AddEntryToGroup( const TADDRMULTISETENTRY& tGroupEntry );

	/** 删除地址簿组成员
	 *  @param[in] tGroupEntry 地址簿组信息
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 DelEntryFromGroup( const TADDRMULTISETENTRY& tGroupEntry );

	/** 添加地址簿组关系
	 *  @param[in] dwGroupIndex 组索引
	 *  @param[in] dwUpGroupIndex 上级组索引
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 AddGroupToGroup( u32 dwGroupIndex, u32 dwUpGroupIndex );

	/** 删除地址簿组关系
	 *  @param[in] dwGroupIndex 组索引
	 *  @param[in] dwUpGroupIndex 上级组索引
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 DelGroupFromGroup( u32 dwGroupIndex, u32 dwUpGroupIndex );

	/** 更新全局地址簿
	 *  @return 成功返回0,失败返回非0错误码
	 */
	u16 UpdateGlobalAddrbook();

	/**
	* 功能:  获取本地地址簿列表  
	* @return  成功返回地址簿列表指针，失败返回空
	*/
	const vector<TAddrItem>* GetLocalAddrList();

	/**
	* 功能:  获取全局地址簿列表  
	* @return  成功返回地址簿列表指针，失败返回空
	*/
	const vector<TAddrItem>* GetGlobalAddrList() const;

	/**
	* 功能:  获取cns注册的地址簿条目  
	* @return  成功返回地址簿列表指针，失败返回空
	*/
	void GetCnsRegInfo( vector<TAddrInfo>* pvctCnsRegInfo );

    /** 功能  清空获取到的Sip注册信息
	*  @param[in] emTyep  类型
	*  @return 无
	*/
	void ClearSipRegInfo( EmGetRegInfoType emTyep );

    /**
	* 功能:  获取本地地址簿条目列表  
	* @return  成功返回地址簿列表指针，失败返回空
	*/
    const vector<TAddrItem>* GetAddrEntryList();

	/**
	* 功能:  获取地址簿分组成员列表  
	* @param[in]  dwGroupIndex  组索引
	* @param[out] vctGroupMemberList  分组成员列表
	* @return  
	*/
	void GetAddrGroupMember( u32 dwGroupIndex, vector<TAddrItem>& vctGroupMemberList );

	/**
	* 功能:  获取地址簿分组信息
	*  @param[in]  dwGroupIndex  组索引
	*  @param[out] tGroupInfo  分组信息
	*  @return
	*/
	void GetAddrGroupInfo( u32 dwGroupIndex, TGroupInfo& tGroupInfo );

	 //-----用户相关 -------------
/** @defgroup  用户相关
 *  @{
 */
	 
	/**
	* 功能:  获取用户列表  
	* @return  成功返回用户列表指针，失败返回空
	*/
   TplArray<CUserFullInfo>* GetUserList() ;
	
   /**
	* 功能:  添加用户 
	* @param [in]  user  
	* @return  成功返回0，失败返回错误码
	*/
	u16 AddUser( const CUserFullInfo& user )    ;
    
	/**
	* 功能:  修改用户信息 
	* @param [in]  user  
	* @return  成功返回0，失败返回错误码
	*/
	u16 UpdateUser( const CUserFullInfo& user )   ;
	 
	/**
	* 功能:  删除用户 
	* @param [in]  user  
	* @return  成功返回0，失败返回错误码
	*/
    u16 DeleteUser( const CUserFullInfo & user ) ;
	 
	/**
	* 功能:  根据用户名获取用户信息 
	* @param [in]  pUserName  
	* @return  成功返回用户信息指针，失败返回空指针
	*/
	CUserFullInfo *GetUserByName ( s8 *pUserName )  const ;

	/**
	* 功能:  获取地址簿分组路径名
	*  @param[in]  dwGroupIndex  组索引
	*  @return  路径名
	*/
	CString GetAddrGroupPath( u32 dwGroupIndex );


/**
	* 功能:  判断用户名是否以存在 
	* @param [in]  pUserName  
	* @return  成功返回TREU，失败返回FLASE
	*/
	BOOL32  IsExistUser ( s8 *pUserName ) const ;

	/** 将CAddrEntry数据设到TAddrInfo中
	 *  @param[out] tAddrInfo  地址条目信息
	 *  @param[in]  cAddrEntry 地址簿条目信息
	 *  @return 
	 */
	void SetAddrItemInfo( TAddrInfo& tAddrInfo, CAddrEntry& cAddrEntry );

	/** 获取组中的条目信息
	 *  @param[in]   tGroupInfo  地址组信息
	 *  @param[out]  vctAddrInfo 地址条目信息列表
	 *  @return 
	 */
	void GetGroupAddrInfo( const TGroupInfo& tGroupInfo, vector<TAddrInfo>& vctAddrInfo );  

	BOOL GetAddrLoadingState();
	void SetAddrLoadingState(BOOL bAddrLoading);

	/**
	* 功能   白板服务器配置
	* @param [in]  dwIP	IP地址
	* @param [in] 
	* @param [in] 
	* @return u16 
	*/  
    u16 SetDataServerInfoCmd( const u32 dwIp );

	/**
	* 功能   单个麦克风状态控制
	* @param [in]  nIndex 麦克风索引
	* @param [in]  bCheck 状态
	* @return u16 
	*/  
    u16 SetMicStateCmd( u8 nIndex, BOOL bCheck );

	/** 设置数据会议状态
	 *  @param[out] 
	 *  @param[in]  
	 *  @return 
	 */
    void SetWBConfState(  bool bIsInWBConf ){ m_bIsInWBConf = bIsInWBConf; };

    bool GetWBConfState(){ return m_bIsInWBConf; };

    /** 功能   获得白板ip配置
	*  @param[out] TTPDataConfInfo 白板服务器地址结构体
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetWBSerIp( TTPDataConfInfo& tWBSerIp );

 	//修改系统名
	u16 changeSysName();
	/** 
	* 功能  	获取会议优选格式
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetVideoFormatInfo( TTPVidForamt& tVidForamt )const;
	/** 
	* 功能  	获取演示优选格式
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetDualVideoFormatInfo( TTPVidForamt& tVidForamt )const;
	/** 
	* 功能  	获取单屏码率
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCallRateInfo( u16& wCallRate )const;
	/** 
	* 功能  	获取演示码率
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetDualCallRateInfo( u16& wDualCallRate )const;
	/** 
	* 功能  修改演示码率
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 DualCallRateCmd( const u16 wDualCallRate );
	/** 
	* 功能  修改单屏演示码率
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 CallRateCmd( const u16 wDualCallRate );
	/** 
	* 功能  	获取会议轮询信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetConfPollInfo( TTPPollInfo& tPollInfo )const;
	/** 
	* 功能  	修改会议轮询信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 ConfPollCmd( const TTPPollInfo& tPollInfo );
	/** 
	* 功能  	获取会议讨论信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetConfDisInfo( BOOL& bDis )const;
	/** 
	* 功能  	获取音频格式信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	EmTpAudioFormat GetAudioFormatInfo()const;

	/**
    * 功能:	 	        设置音频格式信息
	* @param [in]       
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  AudioFormatCmd( const EmTpAudioFormat& emAudioFormat );

	/** 
	* 功能  	设置音频格式信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 VideoFormatCmd( const TTPVidForamt& tVidForamt );
	/** 
	* 功能  	设置演示优选格式信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 DualVideoFormatCmd( const TTPVidForamt& tVidForamt );
	/** 
	* 功能  	设置会议讨论信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	u16 ConfDisCmd( const BOOL& bDis );
	/** 功能   获得logo信息
	*  @param[out] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetLogoInfo( TTPLogoInfo& tInfo );
	/** 功能   获得banner配置
	*  @param[out] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 GetBannerInfo( TTPBannerInfo& tInfo );
	/** 
	* 功能  	台标设置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 CnIsShowLogoCmd( const TTPLogo& tTPLogo );
	/** 
	* 功能  	横幅设置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 CnIsShowBannerCmd( const TTPBanner& tTPBanner );
// 	/** 
// 	* 功能  台标文件上传成功通知
// 	* @param [in] 	 
// 	* @return  
// 	* @remarks 
// 	*/
// 	u16 ConfSignCmd( const BOOL& bOk, u8 byIndex );
	/**
	* 功能:	获取登陆cns 的IP 
	* @return  u32  IP
    */
	u16 GetLoginIp( u32 & IP ); 
	/**
	* 功能:	获取本地 的IP 
	* @return  u32  IP
    */
	 u16 GetLocalIP( u32 & IP ) ;
     /** 
	* 功能  	设置ftp信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 SetCnFtpInfo(TTPFtpInfo tTPFtpInfo);
	/** 
	* 功能  	获取ftp信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCnFtpInfo(TTPFtpInfo &tTPFtpInfo);
	/** 
	* 功能  	获取telnet信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCnTelnetInfo(TTPTelnetInfo &tTPTelnetInfo);
	/** 
	* 功能  Encryt密码设置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 EncrytCmd( const TTpEncryptKey& tEncryt );
	/**
	* 功能:	获取Encryt密码设置
	* @return  Encryt密码设置
    */
	u16 GetEncrytInfo( TTpEncryptKey& tEncryt ); 

    /** 
	* 功能  设置选看
    * @param [in]  byScreenID  屏号
    * @param [in]  wEpID  选看的cnsID
	* @return  
	* @remarks 
	*/
	u16 SetSelView( TTPSelViewReq tTPSelViewReq ) ;//B4消息号统一用ev_Cn_SelView_Req

     /** 
	* 功能  取消选看
    * @param [in]  byScreenID  屏号
    * @param [in]  wEpID  选看的cnsID
	* @return  
	* @remarks 
	*/
	u16 CancleSelView( u8 byScreenID ) ;
	/** 
	* 功能  	获取中控电视墙开启状态
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	BOOL GetDisplayState() const;
	    /** 
	* 功能  设置电视墙选看
    * @param [in]  byScreenID  屏号
	* @return  
	* @remarks 
	*/
	u16 SetSelTVSView( u8 byScreenID ) ;

     /** 
	* 功能  取消电视墙选看
    * @param [in]  byScreenID  屏号
    * @param [in]  wEpID  选看的cnsID
	* @return  
	* @remarks 
	*/
	u16 CancleSelTVSView( u8 byScreenID ) ;
	/**
	* 功能:  本级cns是否是主席 
	* @return 成功返回TRUE,失败返回FALSE
	* @remarks 由CNS负责管理该状态
	*/
	BOOL32 IsLocalCnsChairMan()  ;

	   /**
	* 功能:  获取会议信息  
	* @return  返回列表指针
	*/
    TCMSConf  &GetConfInfo(){ return m_tConfInfo ; }
	/** 功能   获得全景摄像机列表
	*  @param[out] tDualSrcinfo 演示源配置
	*  @return 成功返回0,失败返回非0错误码
	*/
    u16 GetPanCamList( TPanCamInfo& tPanCamInfo );
	/** 功能   设置全景摄像机当前选中编号
	*  @param[in] wIndex 当前选中编号
	*  @return 成功返回0,失败返回非0错误码
	*/
    u16 SetPanCamSelectIndex( u8 wIndex );
	/** 功能   设置主视频源端口
	*  @param[in] emTPMtVideoPort：主视频源端口 wID：对应第几路视频ID
	*  @return 成功返回0,失败返回非0错误码
	*/
    u16 SetMainVideoPort( EmTPMtVideoPort emTPMtVideoPort, u8 wID );
	/** 功能   获得主视频源端口
	*  @param[out] mapEmTPMtVideoPort 主视频源
	*  @return 成功返回0,失败返回非0错误码
	*/
    u16 GetMainVideoPort(  map<u16, EmTPMtVideoPort>& mapEmTPMtVideoPort );
	/** 功能   获得主视频配置项
	*  @param[out] tTPVideoInfoTool 主视频配置项
	*  @return 成功返回0,失败返回非0错误码
	*/
    u16 GetVedioInfo(  TTPVideoInfoTool& tTPVideoInfoTool );

	/** 功能   全景摄像机调节PT
	*  @param[in] emDirection： 方向  emCnAction：操作
	*  @return 成功返回0,失败返回非0错误码
	*/
    u16 SetPanCamPT( EmDirection emDirection, EmCnAction emCnAction );

	/** 功能   全景摄像机视野调节
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 SetPanCamView( EmZoom emZoom, EmCnAction emCnAction );

	/** 功能   全景摄像机调节亮度
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 SetPanCamBright( EmPanCamBright emPanCamBright, EmCnAction emCnAction );

		/** 功能   全景摄像机调节焦距 
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 SetPanCamFocus( EmFocus emFocus, EmCnAction emCnAction );

	/** 功能   全景摄像机自动调节焦距 
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	u16 SetPanCamAotoFocus();
	    /** 
	* 功能  全景摄像机保存预置位
    * @param [in]  wID  预置位号
	* @return  
	* @remarks 
	*/
	u16 SavePanCamPreset(  u8 wID ); 
	 /** 
	* 功能  全景摄像机调用预置位
    * @param [in]  wID  预置位号
	* @return  
	* @remarks 
	*/
	u16 ImpelPanCamPreset(  u8 wID ); 
	/** 
	* 功能  全景摄像机删除预置位
    * @param [in]  wID  预置位号
	* @return  
	* @remarks 
	*/
	u16 DeletePanCamPreset(  u8 wID ); 
	/** 
	* 功能  全景摄像机预置位名称修改
    * @param [in]  wID  预置位号
	* @return  
	* @remarks 
	*/
	u16 SavePanCamPresetName(  u8 wID, TPanCamName tPanCamName ); 
	/** 
	* 功能  会议轮询暂停
    * @param [in]  BOOL32& bIsPause 是否暂停
	* @return  
	* @remarks 
	*/
	u16 PollPauseCmd( const BOOL32& bIsPause );
		/** 
	* 功能  获取会议轮询暂停状态
    * @param [in]  
	* @return  BOOL32 是否暂停
	* @remarks 
	*/
	TTpPollStat GetPollState();
	/** 
	* 功能  会议轮询列表更新
    * @param [in]  TTpPollListInd 列表信息
	* @return  
	* @remarks 
	*/
	u16 PollListUpdateCmd( const TTpPollListNtfy& tTpPollListNtfy );
	/** 
	* 功能  获取会议轮询列表
    * @param [in]  TTpPollListNtfy& tTpPollListNtfy 列表信息
	* @return  
	* @remarks 
	*/
	u16 GetPollList( vector<u16>& vctPollList );

    /** 
	* 功能  设置/获取当前画面合成开关
    * @param [in]  bOpen 开关
	* @return  
	* @remarks 
	*/
    void SetCurtVidMixOpen( BOOL bOpen ){ m_bVidMixOpen = bOpen; }
    BOOL IsCurtVidMixOpen(){ return m_bVidMixOpen; }

/** 
 *  中控接口开始
 */	

    u16 SetSysPower( EmSchPower emPower );

    u16 SetSysAllLight( EmSchLight emLight );

    u16 SetSysMainLight( EmSchMidLight emLight );

    u16 SetSysAuxiLight( EmSchScrLight emLight );

    u16 SelectTVMonitor( u8 byIndex );

    u16 SetTVPowerMode( u8 byIndex, EmTvPowerMode emMode );

    u16 SetTVAudVisMode( EmTVAudVisMode emMode );

    u16 SetTVDisMode( EmTVDisplayMode emMode );

    u16 SetTVInpSelect( u8 byIndex, EmTVInputSelect emSelect );
    
    TCentreTVCfg* GetCentreTVCfg();

    u16 SetDCamSelectIndex( u8 byIndex );

    u16 SetDCamPower( EmDCamPower emPower );

    u16 SetDCamAFMode( EmDCamAFMode emMode );

    u16 SetDCamWBMode( EmDCamWBMode emMode );

    u16 SetDCamZoom( EmDCamZoom emZoom, EmCnAction emAction = emCnStop );

    u16 SetDCamPreset( EmDCamRecallNum emNum );

    u16 SetDCamRecall( EmDCamRecallNum emNum );

	u16 SetDocSnapShot();

//	u16 SetAirPower( EmCentreACPower emPower );

	u16 SetACMode( EmCentreACMode emMode );

	u16 SetACTemp( u8 byTemp );

	u16 SetACAirVol( EmCentreACAirVol emAirVol );
    //空调屏幕选中项消息
	u16 SelectAirMonitor( u8 byIndex );

	u16 GetCentreACCfg( vector<TCentreACCfg> &vecTCentreACCfg );

	u16 SetACPowerMode( u8 byIndex, EmCentreACPower emMode );
	
	u16 SetApplyToAll( u8 byIndex, BOOL* abIsCtrl );

	u16 GetApplyToAllInfo( BOOL** pIsCtrl );

	u16 SetCurtainState( BOOL* bIsCtrl, EmCurAction emCurAction );

	u16 GetCentreCurName( vector<TCentreCurName> &vecTCentreCurName );
	u16 GetCentreCurInfor( TCentreCurInfo &tCentreCurInfo );
	//中控开关信息 2015-6-17 
	u16 GetCentreSchCfg( TCentreSchCfg &tCentreSchCfg );
    u16 GetDCamStateMap( map<u8, TCentreDCamCfg> &mapDCamCfg );
    u16 GetDCamState( TCentreDCamCfg &tCentreDCamCfg, u8 byIndex );
    //矩阵
    BOOL GetMatrixOnlineState();
    TTPMatrixSceneInfo* GetMatrixScneInfo();
    u16 GetCurMatrixInfo(TTPCurMatrixInfo &tTPCurMatrixInfo);
    u16 GetMatrixConfig(TTPMatrixConfig &tTPMatrixConfig);
	  /**
    * 功能:	断开与UMS和CNS的连接
	* @param [in]  
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	在没有连接到UMS/CNS时调用此方法，不起任何作用
	*/
	u16 DisConnect() ; 
	//退出程序
	void  ShutDownCmc( BOOL bRestart = FALSE );
	//连接到TPad
	u16 ConnectTPad();

/**中控接口完*/

	//判断目录是否存在
	BOOL ExistDir( const CString strDir );

	//创建目录
	BOOL CreateDir( CString strDir );
	//tpad登录时用户信息记录
	u16 UpdateTpadLoginInfo();

    /**
    * 功能:	弹出系统软键盘 
	* @remarks  只有pad版弹出	
	*/
    void ShowKeyboard();

	//cnc点击退出，通知TPad不再重连
	u16 NotifyTPadNoReconnect();

	/**
	* 功能:	获取登录返回结果
	* @return  u8  number
    */
	u16 GetLoginRet(TLoginRet& tLoginRet) ;

    //矩阵
    u16 SetMatrixInOutCmd( u32 dwIn, u32 dwOut );
    u16 SaveMatrixScenceCmd( s32 dwIndex, s8* achName );
    u16 ReNameMatrixScenceCmd( u32 dwIndex, s8* achName );
    u16 DeleteMatrixScenceCmd( u32 dwIndex );
    u16 ApplyMatrixScenceCmd( s32 dwIndex );

protected:
	void UpdateAddrList();
	void UpdateAddrEntryList();
	void UpdateLevelOneGroup();

	/** 响应本地地址簿更新消息
	 *  @return 
	 */
	LRESULT UpdateAddrBook( WPARAM wParam, LPARAM lParam );

	/** 响应全局地址簿更新消息
	 *  @return 
	 */
	LRESULT OnRefreshGlobalAddrBook( WPARAM wParam, LPARAM lParam );


	afx_msg LRESULT OnRefreshConfTemplateLst(  WPARAM wParam, LPARAM lParam ) ;

	/*cns 本地会议相关*/ 

	afx_msg LRESULT OnCnsEthnetInfoNotify( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnCnsRegSigServNotify( WPARAM wParam, LPARAM lParam );

	afx_msg LRESULT OnConnectCns(  WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnCnsInfoNotify( WPARAM wParam, LPARAM lParam );

	afx_msg LRESULT OnTPadLoginUserNty( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnRefreshUserLst(  WPARAM wParam, LPARAM lParam ) ;
/** @}*/


public:
	/** 获取接口指针 */
	static CCommonInterface* GetCommIF();

	/** 销毁接口指针 */
	void DestroyCommIF();

	~CCommonInterface(void);

private:
	CCommonInterface(void);
	static  CCommonInterface*  m_pMySelf;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HWND                 m_hRecvWnd;         // 内嵌接收消息的窗口
	WNDPROC              m_wndprocOld;       // 系统窗口过程

private:
    CCnsSessionCtrlIF   *m_pCnsSession;       //cns会话
 
	/**cnclib 相关接口*/
	CCncConfigIF        *m_pCnsConfigCtrl;
	CCncConfCtrlIF      *m_pCnsConfCtrl;
    CUmcConfCtrlIF      *m_pUmsConfCtrl;
	CCncAddrbookIF      *m_pAddrBookCtrl;
	CCncUserCtrlIF      *m_pCnsUserCtrl;
	CCncPortDiagCtrlIF	*m_pPortDiagCtrl;
	CCncCenterCtrlIF    *m_pCenterCtrl;//添加中控 dyy 2015-4-1 
    /**中控相关接口*/
    CCncCenterCtrlIF    *m_pCenterCtrlIF;

	TLoginInfo           m_tLoginInfo;

	/**地址簿相关数据*/
	vector<TAddrItem>         m_vctLocalAddrList;       //本地地址簿
	vector<TAddrItem>         m_vctGlobalAddrList;      //全局地址簿
	vector<TAddrItem>         m_vctEntryList;           //本地地址簿所有条目

	
	//vector<TTPAlias>          m_vctConfTempList;        //会议模板列表	
	TplArray<CUserFullInfo>   m_tplUserList;           ///<用户列表
	
	TCMSConf                  m_tConfInfo;
    BOOL                      m_bVidMixOpen;           //当前画面合成是否开启
    bool					  m_bIsInWBConf;
};

#define ComInterface  CCommonInterface::GetCommIF()

