#ifndef _CNCPORTDIAGNOSISIF_H_
#define _CNCPORTDIAGNOSISIF_H_

#include "kdvdispevent.h"

class CCncPortDiagCtrlIF : public CKdvDispEvent
{
public:	
	//音频接口信息
	virtual TTpAudioPortInfo* GetAudioPortInfo() = 0;							
	virtual	u16 SetAudioPortInfoCmd( const TTpAudioPortInfo** atAudioPortInfo ) = 0;		
	virtual	u16 DefaultAudioPortCmd( const TTpAudioPortInfo** atAudioPortInfo ) = 0;
	
	//网络丢包信息
	virtual u16 LostPacketInfoReq() = 0;
	virtual const u8& GetLostPacketInfo()const = 0;			
	
	//上传下行速率
	virtual const TTPUpDownSpeedInfo& GetUpDownstreamRate()const = 0;	
	
	//选择音视频矩阵方案的命令
	virtual u16 SelAVMatrixCmd( const TTPVgaMixInfo& tVgaMixInfo ) = 0;
	//获取端口诊断结果
	virtual const TTPVideoDiagInfo& GetVideoDiagInfo()const = 0;
	virtual const TTPAudioDiagInfo& GetAudioDiagInfo()const = 0;
	
	//停止诊断测试请求
	virtual u16 StopAVMatrixReq() = 0;
	
	//Tpad列表
	virtual	const TTPTPadList& GetTpadList()const = 0;								
	virtual	u16 UpdateTpadListReq() = 0;	

	//重启Cns
	virtual u16 RebootCns() = 0;
	
	//升级T300
	virtual u16 UpgradeCns( const TTPFTPFileInfo& tVerFileInfo ) = 0;
	
	//维护工具刷新界面请求
	virtual u16 ReqRefresh() = 0;
	
	//音频混音数配置命令
	virtual u16 AudiotMixerCmd( const u8** aAudioMixerInfo ) = 0;
	virtual u8* GetAudioMixerInfo() = 0;
	virtual u16 DefaultMixerCmd( const u8** aAudioMixerInfo ) = 0;
	
	//音频均衡器配置命令
	virtual u16 AudioEqualizerCmd( const TTPEqualizer** atEqualizer ) = 0;
	virtual TTPEqualizer* GetAudioEqualizer() = 0;
	virtual u16 DefaultEqCmd( const TTPEqualizer** atEqualizer ) = 0;
	
	//呼叫服务器地址
	virtual u16 CallServerCmd( const TTPCallSerInfo& tCallSerInfo ) = 0;
	virtual const TTPCallSerInfo& GetCallServerInfo()const = 0;

	//升级服务器地址
	virtual u16 UpgradeSerCmd( const TTPUpgradeSer& tUpgradeSer ) = 0;
	virtual const TTPUpgradeSer& GetUpgradeSerInfo()const = 0;
	
	//台标文件上传成功通知
	virtual u16 ConfSignCmd( const BOOL& bOk, u8 byIndex ) = 0;
	
	//会议优选格式
	virtual u16 VideoFormatCmd( const TTPVidForamt& tVidForamt ) = 0;
	virtual const TTPVidForamt& GetVideoFormatInfo()const = 0;
	
	//演示优选格式
	virtual u16 DualVideoFormatCmd( const TTPVidForamt& tVidForamt ) = 0;
	virtual const TTPVidForamt& GetDualVideoFormatInfo()const = 0;
	
	//单屏码率
	virtual u16 CallRateCmd( const u16 wCallRate ) = 0;
	virtual const u16 GetCallRate()const = 0;
	
	//演示码率
	virtual u16 DualCallRateCmd( const u16 wDualCallRate ) = 0;
	virtual const u16 GetDualCallRate()const = 0;

    //会议轮询
    virtual u16 ConfPollCmd( const TTPPollInfo& tPollInfo ) = 0;
    virtual const TTPPollInfo& GetConfPollInfo()const = 0;

    //会议讨论
    virtual u16 ConfDisCmd( const BOOL& bDis ) = 0;
    virtual const BOOL& GetConfDisInfo()const = 0;

	//音频格式
	virtual u16 AudioFormatCmd( const EmTpAudioFormat& emAudioFormat ) = 0;
	virtual const EmTpAudioFormat& GetAudioFormatInfo() const = 0;

	//Encryt密码信息
	virtual	u16 GetEncrytInfo( TTpEncryptKey& tEncryt ) = 0;
	virtual	u16 EncrytCmd( const TTpEncryptKey& tEncryt ) = 0;
			/** 
	* 功能  	得到台标信息
	* @param [in] 	   
	* @return  
	* @remarks 
	*/	
	virtual const TTPLogoInfo& GetLogoInfo()const = 0;
	/** 
	* 功能  	得到横幅信息
	* @param [in] 	   
	* @return  
	* @remarks 
	*/	
	virtual const TTPBannerInfo& GetBannerInfo()const = 0;

			/** 
	* 功能  	台标设置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 CnIsShowLogoCmd( const TTPLogo& tTPLogo  ) = 0;
	/** 
	* 功能  	横幅设置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 CnIsShowBannerCmd( const TTPBanner& tTPBanner ) = 0;
    /** 
	* 功能  	设置ftp信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 SetCnFtpInfo(TTPFtpInfo tTPFtpInfo) = 0;
	/** 
	* 功能  	获取ftp信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual TTPFtpInfo GetCnFtpInfo() = 0;

	/** 
	* 功能  	获取telnet信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual TTPTelnetInfo GetCnTelnetInfo() = 0;

};

#endif 