/*****************************************************************************
模块名      : cmc cnclib接口
文件名      : cncconfigif.h
相关文件    : 
文件实现功能: cns配置
作者        : 肖楚然
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/4/30   1.0         肖楚然        创建
******************************************************************************/
#ifndef __CNCCONFIGIF_H__
#define __CNCCONFIGIF_H__

#include "kdvdispevent.h"
#include "cncstruct.h"
#include <vector>

class CCncConfigIF : public CKdvDispEvent
{
public:
	/** 功能  注册SIP服务
	 *  @param[in] tSipCfg 配置信息
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 RegSipService(const TTPSipRegistrarCfg& tSipCfg) = 0;

	/** 功能  注销SIP服务
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 UnRegSipService() = 0;

	/** 功能   获得SIP配置
	 *  @return TTPSipRegistrarCfg SIP信息
	 */
	virtual const TTPSipRegistrarCfg& GetSipRegCfg() const = 0;

	/** 功能   获得网络配置
	 *  @return tagTTPEthnetInfo 网络配置信息
	 */
	virtual const TTPEthnetInfo& GetEthnetCfg() const = 0;

	/** 功能   GK
	 *  @return tGkCfg 配置信息
	 */
    virtual u16 RegGk( const TTPGKCfg& tGkCfg ) = 0;

    /** 功能   获得GK配置
	 *  @return tagTTPEthnetInfo 网络配置信息
	 */
	virtual  const TTPGKCfg& GetGkCfg() const = 0;

	/** 功能   更新网络配置
	 *  @param[in] cfg 网络配置
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 UpdateEthnetCfg( const TTPEthnetInfo& cfg, EmTpIpNameNatSyn em ) = 0;

	
	/** 功能   获得本地CNS信息
	 *  @return TTPCnsInfo CNS信息
	 */
	virtual const TTPCnsInfo& GetLocalCnsInfo() const = 0;

	/** 功能   获得本地CNS列表
	 *  @return vector<TTPCnsInfo> CNS列表
	 */
	virtual const vector<TTPCnsInfo>& GetLocalCnsList() const = 0;

	/** 功能   更新CNS信息
	 *  @param[in] tInfo CNS信息 byIndex 消息来自哪里(0为cnc 1为维护工具)
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 UpdateCnsInfo( const TTPCnsInfo& tInfo, u8 byIndex, EmTpIpNameNatSyn em ) = 0;

	/** 功能   设置CNS主会场
	 *  @param[in] pbyRoomName 会场名
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 SetMainCns( s8* pbyRoomName ) = 0;

	/** 功能   获取CNS主会场名
	 *  @return 成功返回会场名,失败返回NULL
	 *  @remarks 
	 */
	virtual const s8* GetMainCnsName() const = 0;
   
    /** 功能   设置系统时间
	 *  @return 成功返回会场名,失败返回NULL
	 *  @remarks 
	 */
    virtual u16 UpdateSysTime( const TTPTime& time ) = 0;
       
    /** 功能   获取系统时间
	 *  @return 成功返回会场名,失败返回NULL
	 *  @remarks 
	 */    
    virtual u16 ReqSysTime() = 0;

    /** 功能   获得双流源信息
	 *  @return TDualSrcInfo双流源信息
	 */
    virtual const TDualSrcInfo& GetDualSrcInfo() const = 0;

    /** 功能   获得演示源输出接口信息
	 *  @return TTPVgaMixInfo演示源输出接口信息
	 */
    virtual const TTPVgaMixInfo& GetVgaMixInfo() const = 0;

    /** 功能   选择双流源端口
	*  @param[out] emType 双流源类型
	*  @return 成功返回0,失败返回非0错误码
	*/
    virtual u16 SelDualInputPort( EmVgaType emType ) = 0;

    /** 功能   设置双流源信息
	*  @param[out] tVgaInfo 双流源信息
	*  @return 成功返回0,失败返回非0错误码
	*/
    virtual u16 SetDualPortInfo( const TVgaInfo& tVgaInfo, BOOL bDefault = FALSE ) = 0;

	/** 功能   更新NAT配置
	 *  @param[in] cfg NAT配置
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 UpdateNATCfg( const TTPNatCfg& cfg, EmTpIpNameNatSyn em ) = 0;
	
	/** 功能   获得NAT配置
	 *  @return tagTTPNatCfg 网络配置信息
	 */
	virtual const TTPNatCfg& GetNATCfg() const = 0;

	/** 功能   设置系统待机信息
	*  @param[out] tTPSleepInfo 系统待机信息
	*  @return 成功返回0,失败返回非0错误码
	*/
    virtual u16 SetSysSleepInfo( const TCenDevSleepInfo& tCenDevSleepInfo ) = 0;

	 /** 功能   获得系统待机信息
	 *  @return TTPSleepInfo 系统待机信息
	 */
    virtual const TCenDevSleepInfo& GetSysSleepInfo() const = 0;
	/**
    * 功能:	 	        发送添加网管请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_CnAgtAddNMServerCmd
	*/
	virtual u16  NetMngAddCmd( const TTPNMServerCfg& tTPNMServerCfg ) = 0;

    /**
    * 功能:	 	        发送修改网管请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_CnAgtDelNMServerCmd
	*/
	virtual u16  NetMngModifyCmd( const TTPNMServerCfg& tTPNMServerCfg ) = 0;

    /**
    * 功能:	 	        发送删除网管请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_CnAgtModifyNMServerCmd
	*/
	virtual u16  NetMngDeleteCmd( const TTPNMServerCfg& tTPNMServerCfg ) = 0;

	/** 
	* 功能  获取网管信息
	* @param [in]  
	* @return  
	*/
	virtual void GetNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg )const = 0;

	/** 
	* 功能  请求SIP注册信息
	* @param [in]  emType 注册类型
	* @return  
	* @remarks 
	*/
	virtual u16 ReqSipRegInfo( EmGetRegInfoType emType ) = 0;

	/** 
	* 功能  获取Cns注册信息
	* @return  vector<TTPAlias>  Cns注册信息
	* @remarks 
	*/
	virtual const vector<TAddrInfo>& GetCnsRegInfo() const = 0;

	/** 
	* 功能  获取Ums注册信息
	* @return  vector<TTPAlias>  Ums注册信息
	* @remarks
	*/
	virtual const vector<TTPAlias>& GetUmsRegInfo() const = 0;

	/**
	* 功能   白板服务器配置
	* @param [in]  dwIP	IP地址
	* @param [in] 
	* @param [in] 
	* @return u16 
	*/  
    virtual u16 SetDataServerInfoCmd( u32 dwIp ) =0 ;

	//白板服务器地址
	virtual const TTPDataConfInfo& GetWBSerIp()const = 0;

	/** 
	* 功能  主视频源设置
	* @param [in]  
	* @return  
	*/
	virtual u16 SetMainVideoPort( EmTPMtVideoPort emTPMtVideoPort, u8 wID ) = 0;
		/** 
	* 功能  主视频源获得
	* @param [in]  
	* @return  
	*/
	virtual const map<u16, EmTPMtVideoPort>& GetMainVideoPort() const = 0;
	/** 
	* 功能  主视频源设置信息
	* @param [in]  
	* @return  
	*/
	virtual const TTPVideoInfoTool& GetVedioInfo() const = 0;

	 /** 功能   获得全景摄像机信息
	 *  @return TDualSrcInfo全景摄像机信息
	 */
    virtual const TPanCamInfo& GetPanCamInfo() const = 0;
		
	/**本地会场全景摄像机状态 设置
	*  @param[in] Quite 是否开启
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetLocalCnsPanCam(u8 wCamId ,BOOL bPanCam = TRUE) = 0;

	/** 功能   设置全景摄像机当前选中编号
	*  @param[in] wIndex 当前选中编号
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetPanCamSelectIndex( u8 wIndex ) = 0;
	/**获取当前全景摄像机状态，是否开启
	*  @param[in] 
	*  @return BOOL 
	*/
	virtual BOOL32 IsLocalCnsPanCam() const = 0; 
	/** 功能   全景摄像机调节PT
	*  @param[in] emDirection： 方向  emCnAction：操作
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetPanCamPT( EmDirection emDirection, EmCnAction emCnAction ) = 0;

			/** 功能   全景摄像机视野调节
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetPanCamView( EmZoom emZoom, EmCnAction emCnAction )= 0;

		/** 功能   全景摄像机调节亮度
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetPanCamLight( EmPanCamBright emPanCamBright, EmCnAction emCnAction )= 0;

		/** 功能   全景摄像机调节焦距 
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetPanCamFocus( EmFocus emFocus, EmCnAction emCnAction )= 0;

	/** 功能   全景摄像机自动调节焦距 
	*  @param[in] 
	*  @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 SetPanCamAotoFocus()= 0;
	/** 
	* 功能  全景摄像机保存预置位
    * @param [in]  wID  预置位号
	* @return  
	* @remarks 
	*/
	virtual u16 SavePanCamPreset(  u8 wID ) = 0; 
	 /** 
	* 功能  全景摄像机调用预置位
    * @param [in]  wID  预置位号
	* @return  
	* @remarks 
	*/
	virtual u16 ImpelPanCamPreset(  u8 wID ) = 0;
		 /** 
	* 功能  全景摄像机删除预置位
    * @param [in]  wID  预置位号
	* @return  
	* @remarks 
	*/
	virtual u16 DeletePanCamPreset(  u8 wID ) = 0;
	/** 
	* 功能  全景摄像机预置位名修改
    * @param [in]  wID  预置位号
	* @return  
	* @remarks 
	*/
	virtual u16 SavePanCamPresetName(  u8 wID ,TPanCamName tPanCamName) = 0;
	/**获取当前画面裁剪状态，是否开启
	*  @param[in] 
	*  @return BOOL 是否开启
	*/
	virtual BOOL32 IsVidCutLine() const = 0; 
	/** 
	* 功能  设置画面裁剪
    * @param [in]  BOOL bIsVidCutLine 是否开启
	* @return  
	* @remarks 
	*/
	virtual u16 SetVidCutLine( BOOL bIsVidCutLine ) = 0;

	/** 功能   设置量子加密
	 *  @return
	 */
	virtual u16 SetQtEncryptCfg( const TTpQtEncryptCfg& tQtEncrypt) = 0;
	/** 功能   获得量子加密信息
	 *  @return TTpQtEncryptCfg量子加密信息
	 */
    virtual const TTpQtEncryptCfg& GetQTEncrypt() const = 0;

	/**
    * 功能:	 	        时间同步请求
 	* @param [in]       
 	* @return           u16 成功返回0,失败返回非0错误码
 	*/
 	virtual u16  SetTimeSynchroCmd( BOOL bIsCheck ) = 0;

	/**
    * 功能:	 	        密码周期更新请求
 	* @param [in]       
 	* @return           u16 成功返回0,失败返回非0错误码
 	*/
 	virtual u16 SetTpadPasswordUpdate( TTpPasswordUpdateInfo tTpPasswordUpdateInfo ) = 0;
	/**
    * 功能:	 	        获取密码周期更新信息
 	* @param [in]       
 	* @return           u16 成功返回0,失败返回非0错误码
 	*/
 	virtual const TTpPasswordUpdateInfo& GetPasswordUpdateInfo() const = 0;

    //超级管理员信息
    virtual u16 SetSuperadmninInfo(TTpSuperUser tTpSuperUser) = 0;
    virtual const TTpSuperUser& GetSuperadmninInfo() const = 0;
    virtual u16 UnlockAllUser() = 0;
};

#endif