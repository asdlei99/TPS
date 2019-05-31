/** @defgroup tpad的公共接口 
 *  @version V1.1.5
 *  @author  邓莹莹
 *  @date    2016.6.28
 */
#pragma once
#include "kdvdispevent.h"
#include "tpadplatstuct.h"
#include "tpcommonstruct.h"

class CTpadConfCtrlIF : public CKdvDispEvent
{
public:

		/** 
	* 功能  开启/停止双流码流
	* @return  BOOL  TRUE:开启， FALSE:停止
	* @remarks 
	*/
    virtual u16 StartDualCodeStream( const TTPCnMediaTransPort  &tVideoTransAddr , const TTPCnMediaTransPort  &tAudioTransAddr ) const = 0;

    virtual u16 StopDualCodeStream() const = 0;

    virtual u16 ReqKeyFrame( BOOL32 bForce ) const = 0;

	virtual TTPCnMediaTransPort GetVedioTransAddr() const = 0;
	
    virtual TTPCnMediaTransPort GetAudioTransAddr() const = 0;

	virtual void WBConfStartNty( bool bIsSelfStart, bool bIsSuccess  ) = 0;

	//virtual void NewConfCallRsp( BOOL bIsJoinWBConf ) = 0;

	virtual void WBConfStateNty( BOOL bIsInWBConf ) = 0;

	virtual void SetDataServerInfoCmd( u32 dwIp ) = 0;

	//获取白板信息
	virtual TTPDataConfInfo GetDataConfInfo() const = 0;
	virtual TTPCnsConfStatus GetWBCnsConfStatus() const = 0;
	virtual TTPCnsInfo GetWBCnsInfo() const = 0;

	/** 功能  获取CNS会议状态
	*  @return TTPCnsConfStatus 会议状态
	*  @remarks 
	*/
	virtual TTPCnsConfStatus GetCnsConfStatus() const = 0;

};

