/** @defgroup tpad�Ĺ����ӿ� 
 *  @version V1.1.5
 *  @author  ��ӨӨ
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
	* ����  ����/ֹͣ˫������
	* @return  BOOL  TRUE:������ FALSE:ֹͣ
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

	//��ȡ�װ���Ϣ
	virtual TTPDataConfInfo GetDataConfInfo() const = 0;
	virtual TTPCnsConfStatus GetWBCnsConfStatus() const = 0;
	virtual TTPCnsInfo GetWBCnsInfo() const = 0;

	/** ����  ��ȡCNS����״̬
	*  @return TTPCnsConfStatus ����״̬
	*  @remarks 
	*/
	virtual TTPCnsConfStatus GetCnsConfStatus() const = 0;

};

