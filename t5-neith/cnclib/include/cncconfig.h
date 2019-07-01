// cncconfig.h: interface for the CCncConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNCCONFIG_H__40492EAF_0B43_4101_A0B9_FDD4C21B1D4A__INCLUDED_)
#define AFX_CNCCONFIG_H__40492EAF_0B43_4101_A0B9_FDD4C21B1D4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cnsSession.h"

class CCncConfig : public CCncConfigIF 
{
	friend class CCnsSession;
public:
	CCncConfig(CCnsSession &cSession);
	virtual ~CCncConfig();

	//注册SIP服务
	virtual u16 RegSipService( const TTPSipRegistrarCfg& tSipCfg );
	virtual u16 UnRegSipService();
	virtual const TTPSipRegistrarCfg& GetSipRegCfg() const;


    //注册GK
    virtual u16 RegGk( const TTPGKCfg& tGkCfg );
    
 
    /** 功能   获得GK配置
	 *  @return tagTTPEthnetInfo 网络配置信息
	 */
	virtual  const TTPGKCfg& GetGkCfg() const ;


	/** 功能   更新CNS信息
	 *  @param[in] tInfo CNS信息  byIndex 消息来自哪里(0为cnc 1为维护工具)
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 UpdateCnsInfo( const TTPCnsInfo& tInfo, u8 byIndex, EmTpIpNameNatSyn em );

	virtual u16 SetMainCns( s8* pbyRoomName );

	virtual const s8* GetMainCnsName() const;

	//更新网络配置
	virtual const TTPEthnetInfo& GetEthnetCfg() const;
	virtual u16 UpdateEthnetCfg( const TTPEthnetInfo& cfg, EmTpIpNameNatSyn em );

	virtual const TTPCnsInfo& GetLocalCnsInfo() const;
	virtual const vector<TTPCnsInfo>& GetLocalCnsList() const;
    
	//更改NAT设置*******2012.11.1 JYY添加
	virtual u16 UpdateNATCfg( const TTPNatCfg& cfg, EmTpIpNameNatSyn em );
	virtual const TTPNatCfg& GetNATCfg() const;

	//设置系统时间
    virtual u16 UpdateSysTime( const TTPTime& time );
    //获取系统时间
    virtual u16 ReqSysTime(); 

    //设置双流源端口
    virtual u16 SelDualInputPort( EmVgaType emType );
    virtual u16 SetDualPortInfo( const TVgaInfo& tVgaInfo, BOOL bDefault = FALSE );

    virtual const TDualSrcInfo& GetDualSrcInfo() const;
    virtual const TTPVgaMixInfo& GetVgaMixInfo() const;

	//设置系统待机端口
	virtual u16 SetSysSleepInfo( const TCenDevSleepInfo& tCenDevSleepInfo );
	virtual const TCenDevSleepInfo& GetSysSleepInfo() const;

	/**
    * 功能:	 	        发送添加网管请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_CnAgtAddNMServerCmd
	*/
	virtual u16  NetMngAddCmd( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * 功能:	 	        发送修改网管请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_CnAgtDelNMServerCmd
	*/
	virtual u16  NetMngModifyCmd( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * 功能:	 	        发送删除网管请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_CnAgtModifyNMServerCmd
	*/
	virtual u16  NetMngDeleteCmd( const TTPNMServerCfg& tTPNMServerCfg );

	/** 
	* 功能  获取网管信息
	* @param [in]  
	* @return  
	*/
	virtual void GetNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg )const;

	/** 
	* 功能  请求SIP注册信息
	* @param [in]  
	* @return  
	* @remarks 
	*/
	virtual u16 ReqSipRegInfo( EmGetRegInfoType emType );

	/** 
	* 功能  获取Cns注册信息
	* @param [in]  
	* @return  
	*/
	virtual const vector<TAddrInfo>& GetCnsRegInfo() const;

	/** 
	* 功能  获取Ums注册信息
	* @param [in]  
	* @return  
	*/
	virtual const vector<TTPAlias>& GetUmsRegInfo() const;

	/** 功能   获得全景摄像机信息
	 *  @return TDualSrcInfo全景摄像机信息
	 */
    virtual const TPanCamInfo& GetPanCamInfo() const;
		/**获取当前全景摄像机状态，是否开启
	*  @param[in] 
	*  @return BOOL 是否为哑音
	*/
	virtual BOOL32 IsLocalCnsPanCam() const; 

	/**本地会场全景摄像机状态 设置
	*  @param[in] Quite 是否开启
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetLocalCnsPanCam( u8 wCamId ,BOOL bPanCam = TRUE);
//数据会议相关
	virtual u16 SetDataServerInfoCmd( u32 dwIp );
	const TTPDataConfInfo& GetWBSerIp() const;
	void OnWBServerNty( const CMessage& cMsg ) ;
	void OnWBServerInd( const CMessage& cMsg ) ;
	/** 
	* 功能  主视频源设置
	* @param [in]  
	* @return  
	*/
	virtual u16 SetMainVideoPort( EmTPMtVideoPort emTPMtVideoPort, u8 wID );
	virtual const map<u16, EmTPMtVideoPort>& GetMainVideoPort() const;
	virtual const TTPVideoInfoTool& GetVedioInfo() const{ return m_tTPVideoInfoTool;};
	void OnSetLocalCnsPanCamNty( const CMessage &cMsg );
	/** 功能   设置全景摄像机当前选中编号
	*  @param[in] wIndex 当前选中编号
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetPanCamSelectIndex( u8 wIndex );

	/** 功能   全景摄像机调节PT
	*  @param[in] emDirection： 方向  emCnAction：操作
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetPanCamPT( EmDirection emDirection, EmCnAction emCnAction );

		/** 功能   全景摄像机视野调节
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetPanCamView( EmZoom emZoom, EmCnAction emCnAction );

		/** 功能   全景摄像机调节亮度
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetPanCamLight( EmPanCamBright emPanCamBright, EmCnAction emCnAction );

		/** 功能   全景摄像机调节焦距 
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetPanCamFocus( EmFocus emFocus, EmCnAction emCnAction );

	/** 功能   全景摄像机自动调节焦距 
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetPanCamAotoFocus();
		/** 
	* 功能  全景摄像机保存预置位
    * @param [in]  wID  预置位号
	* @return  
	* @remarks 
	*/
	virtual u16 SavePanCamPreset(  u8 wID ); 
	 /** 
	* 功能  全景摄像机调用预置位
    * @param [in]  wID  预置位号
	* @return  
	* @remarks 
	*/
	virtual u16 ImpelPanCamPreset(  u8 wID );
		 /** 
	* 功能  全景摄像机删除预置位
    * @param [in]  wID  预置位号
	* @return  
	* @remarks 
	*/
	virtual u16 DeletePanCamPreset(  u8 wID );
	/** 
	* 功能  全景摄像机预置位名修改
    * @param [in]  wID  预置位号
	* @return  
	* @remarks 
	*/
	virtual u16 SavePanCamPresetName(  u8 wID ,TPanCamName tPanCamName);

	/**获取当前画面裁剪状态，是否开启
	*  @param[in] 
	*  @return BOOL 是否开启
	*/
	virtual BOOL32 IsVidCutLine() const; 
	/** 
	* 功能  设置画面裁剪
    * @param [in]  BOOL bIsVidCutLine 是否开启
	* @return  
	* @remarks 
	*/
	virtual u16 SetVidCutLine( BOOL bIsVidCutLine );

	/** 功能   设置量子加密
	 *  @return
	 */
	virtual u16 SetQtEncryptCfg( const TTpQtEncryptCfg& tQtEncrypt);
	/** 功能   获得量子加密信息
	 *  @return TTpQtEncryptCfg量子加密信息
	 */
    virtual const TTpQtEncryptCfg& GetQTEncrypt() const;

	/**
    * 功能:	 	        时间同步请求
 	* @param [in]       
 	* @return           u16 成功返回0,失败返回非0错误码
 	*/
 	virtual u16  SetTimeSynchroCmd( BOOL bIsCheck );
	//密码更新周期请求
	virtual u16 SetTpadPasswordUpdate(TTpPasswordUpdateInfo tTpPasswordUpdateInfo);
	//获取密码更新周期信息
	virtual const TTpPasswordUpdateInfo& GetPasswordUpdateInfo()const;

    //超级管理员信息
    virtual u16 SetSuperadmninInfo(TTpSuperUser tTpSuperUser);
    virtual const TTpSuperUser& GetSuperadmninInfo() const;
    virtual u16 UnlockAllUser();

    //设置IPV6配置
    virtual u16 SetIpv6Cfg( TTPEthnetIPV6Info tTPEthnetIPV6Info, EmTpIpNameNatSyn emTpIpNameNatSyn);
    //获取IPV6配置
    virtual const TTPEthnetIPV6Info GetIpv6Cfg();
    //设置IPV6类型
    virtual u16 SetIpvType( EmProtocolVersion emProtocolVer );
    //获取IPV6类型
    virtual const EmProtocolVersion GetIpvType();

protected:
    virtual void OnTimeOut(u16 wEvent); 
    virtual void DispEvent(const CMessage &cMsg);
	void BuildEventsMap();
	void UpdateCnsList( TTPCnsInfo tCnsInfo );

	//消息处理
	void OnLinkBreak(const CMessage& cMsg);
	void OnCnsInfoNty(const CMessage& cMsg);
	void OnRegSipNty(const CMessage& cMsg);	
	void OnEthnetInfoInd(const CMessage& cMsg);
	void OnMainCnsInd(const CMessage& cMsg);
	//void OnCnsOnlineNty(const CMessage& cMsg);
	void OnCnsOfflineNty(const CMessage& cMsg);
    void OnSysTimeRsp(const CMessage& cMsg);
	void OnRegResultNty(const CMessage& cMsg);
	void OnRegResultFailNty(const CMessage& cMsg);
    void OnRegGkRsp(const CMessage& cMsg);
    void OnRegGkNty(const CMessage& cMsg);

	void OnSysSleepNty(const CMessage& cMsg);
	void OnRegNatNty(const CMessage& cMsg);
    void OnSetDualPortNameInd(const CMessage& cMsg);
    void OnSelDualInputPortInd(const CMessage& cMsg);
    void OnVgaInfoNty(const CMessage& cMsg);
    void OnConfVgaInfoNty(const CMessage& cMsg);
	void OnVidCurLineInd(const CMessage& cMsg);

    //Ipv6配置
    void OnCfgEthnetIPV6Ind(const CMessage& cMsg);
    void OnIPVtpyeInd(const CMessage& cMsg);

	/**
    * 功能:	  添加网管通知
	* @param [out]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void  OnAddNetMngInd(const CMessage& cMsg);
 
	/**
    * 功能:	  删除网管通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnDelNetMngInd(const CMessage& cMsg);

	/**
    * 功能:	  修改网管通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnModifyNetMngInd(const CMessage& cMsg);

	/**
    * 功能:	  网管信息通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnNetMngNty(const CMessage& cMsg);

	//注册信息消息处理
	void OnRegInfoRsp(const CMessage& cMsg);
	void OnRegInfoNty(const CMessage& cMsg);
	void OnGetGkRegInfo(const CMessage& cMsg);
	void OnGetCnsRegInfo(const CMessage& cMsg);
	void OnGetUmsRegInfo(const CMessage& cMsg);

	//主视频设置回应
	void OnMainVideoPort(const CMessage& cMsg);

	//全景摄像机信息
	void OnPanCamCfgNty(const CMessage& cMsg);
	//全景摄像机保存预置位结果
	void OnPanCamSavePresetInd(const CMessage& cMsg);
	//全景摄像机删除预置位结果
	void OnPanCamDeletePresetInd(const CMessage& cMsg);
	//全景摄像机调用预置位结果
	void OnPanCamImplePresetInd(const CMessage& cMsg);
	//全景摄像机修改预置位名称保存结果
	void OnPanCamSavePresetNameInd(const CMessage& cMsg);	
	//全景摄像机选择反馈
	void OnPanCamSelInd(const CMessage& cMsg);	
	//视频源状态通知 是否有视频源 dyy 2015-6-17
	void OnVidSrcNty(const CMessage& cMsg);
	//主视频设置通知
	void OnVedioInfoNty(const CMessage& cMsg);

	//量子加密
	void OnSetQTEncryptInd(const CMessage& cMsg);
	void OnSetQTEncryptNty(const CMessage& cMsg);

	//时间同步
	void OnCnSysTimeToCncNty(const CMessage& cMsg);
	void OnCnNtpIsUsedInd(const CMessage& cMsg);

	//密码周期更新
	void OnCnTpadPasswordUpdateNty(const CMessage& cMsg);
	void OnCnTpadPasswordUpdateInd(const CMessage& cMsg);

    //超级管理员信息
    void OnSuperadminNty(const CMessage& cMsg);
    void OnSuperadminInd(const CMessage& cMsg);

    //升级后第一次登录
    void OnFirstLoginAfterUpdateNty(const CMessage& cMsg);

private:
	CCnsSession        *m_pSession;
	TTPEthnetInfo       m_tEthnetInfo;       //网络信息
	TTPSipRegistrarCfg  m_tSipCfg;           //SIP注册信息
	TTPCnsInfo          m_tLocalCnsInfo;     //本地CNS信息
	vector<TTPCnsInfo>  m_vctCnsList;        //本CNS列表
	s8                  m_achMainRoom[TP_MAX_ALIAS_LEN+1];  //主会场名
    TTPGKCfg            m_tGkCfg;            //GK配置
    TDualSrcInfo        m_tDualSrcInfo;      //双流源信息
	TCenDevSleepInfo    m_tCenDevSleepInfo;  //系统待机信息
	TTPNatCfg			m_tNATCfg;			 //NAT信息
	TTPVgaMixInfo       m_tVgaMixInfo;       //演示源输出接口信息

	vector<TTPNMServerCfg>	m_vecTTPNMServerCfg;		//网管服务器信息

	vector<TAddrInfo>  m_vctGkRegInfo;
	vector<TAddrInfo>  m_vctCnsRegInfo;
	vector<TTPAlias>   m_vctUmsRegInfo;

	TTPDataConfInfo    m_tWBSerIp;
	map<u16, EmTPMtVideoPort> m_mapEmTPMtVideoPort;
	TPanCamInfo  m_tPanCamInfo;//全景摄像机信息 
	BOOL32           m_bLocalPanCam;	//是否开启全景摄像机
	BOOL32             m_bVidCutLine;//是否开启画面裁剪
	TTPVideoInfoTool m_tTPVideoInfoTool;//主视频配置项

	//量子加密
	TTpQtEncryptCfg m_tQTEncrypt;
	TTPTime         m_tTPTime;

	//密码周期更新
	TTpPasswordUpdateInfo m_tTpPasswordUpdateInfo;
    //超级管理员信息
    TTpSuperUser m_tTpSuperUser;

    //GK注册相关
    TUCSipRegResult m_tUCSipRegResult;

    EmProtocolVersion   m_emProtocolVersion; //IPV类型
    TTPEthnetIPV6Info	m_tTPEthnetIPV6Info; //IPV6配置
};

#endif // !defined(AFX_CNCCONFIG_H__40492EAF_0B43_4101_A0B9_FDD4C21B1D4A__INCLUDED_)
