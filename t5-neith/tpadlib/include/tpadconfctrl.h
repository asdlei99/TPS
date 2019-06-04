/** @defgroup tpad的公共接口 
 *  @version V1.1.5
 *  @author  邓莹莹
 *  @date    2016.6.28
 */
#pragma once
#include "tpadsession.h"
class CTpadConfCtrl : public CTpadConfCtrlIF
{
public:
	friend class CCncSession; 

	CTpadConfCtrl( CTPadSession &cTpadSession );
	~CTpadConfCtrl(void);

	virtual void DispEvent(const CMessage &cMsg);

	virtual void OnTimeOut(u16 wEvent);
	void BuildEventsMap();

	void OnLinkBreak(const CMessage& cMsg);
protected:
	void OnRecvDualNty( const CMessage &cMsg );

	void OnStartDualCdStrmRsp( const CMessage &cMsg );
	void OnStopDualCdStrmRsp( const CMessage &cMsg );
	void OnDualCodeEnCryptKeyNty( const CMessage &cMsg );

	void OnConfStateNty( const CMessage &cMsg );

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

	virtual TTPCnMediaTransPort GetVedioTransAddr() const { return m_tVideoTranAddr ;}

    virtual TTPCnMediaTransPort GetAudioTransAddr() const { return m_tAudioTranAddr ;}
		 
	/**
	* 功能:  获取本地cns会议状态
	* @param [out]tConfInfo  本级cns参加的会议信息
	* @return 成功返回TRUE,失败返回FALSE
	* @remarks 
	*/
    virtual TTPCnsConfStatus GetCnsConfStatus() const; 

	//白板会议相关消息响应 dyy 2014-5-14
	void OnJoinWBConfCmd( const CMessage &cMsg );
	void OnLeaveWBConfNty( const CMessage &cMsg );
	void OnNewConfCallReq( const CMessage &cMsg );
	//白板会议获得会场名进行消息解析
	void OnCnsInfoNty( const CMessage &cMsg );

	//tpad配置白板IP发送
	void SetDataServerInfoCmd( u32 dwIp );
	//配置是否成功
	void OnSetDataServerInfoInd( const CMessage &cMsg );
	//tpad登陆时收到白板ip
	void OnSetDataServerInfoNty( const CMessage &cMsg );
	//自己控制开启的白板会议
	void OnSelfMakeCallCmd( const CMessage &cMsg );
	//点对点会议数据会议名称nty 2014-9-12
	void OnSetDataConfNameNty( const CMessage &cMsg );
	//发给cnc白板会议状态
	void WBConfStateNty( BOOL bIsInWBConf );

	void WBConfStartNty( bool bIsSelfStart, bool bIsSuccess );
	//获取白板信息
	virtual TTPDataConfInfo GetDataConfInfo() const { return m_tTPDataConfInfo ;}
	virtual TTPCnsConfStatus GetWBCnsConfStatus() const { return m_tWBConfStatus ;}
	virtual TTPCnsInfo GetWBCnsInfo() const { return m_tCnsInfo ;}
private:
	CTPadSession *  m_pTpadSession;

	u16    m_nVideoNode;
	u16    m_nAudioNode;
	BOOL32 m_bRecvDual;
	TTPCnMediaTransPort m_tVideoTranAddr;
	TTPCnMediaTransPort m_tAudioTranAddr;

	TTPCnsConfStatus m_tCnsConfStatus;

    TTpEncryptKey    m_tTpEncryptKey;   //双流秘钥

	//白板相关参数
	TTPDataConfInfo m_tTPDataConfInfo;
	TTPCnsConfStatus m_tWBConfStatus;
	TTPCnsInfo m_tCnsInfo;
};

