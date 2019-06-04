/** @defgroup tpad�Ĺ����ӿ� 
 *  @version V1.1.5
 *  @author  ��ӨӨ
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
	* ����  ����/ֹͣ˫������
	* @return  BOOL  TRUE:������ FALSE:ֹͣ
	* @remarks 
	*/
    virtual u16 StartDualCodeStream( const TTPCnMediaTransPort  &tVideoTransAddr , const TTPCnMediaTransPort  &tAudioTransAddr ) const;
   
    virtual u16 StopDualCodeStream() const  ;

	/** 
	* ����  ����ؼ�֡
	* @return  BOOL  TRUE:���ܹؼ�֡����Լ����ǿ�Ʒ��͹ؼ�֡�� FALSE:�ܹؼ�֡����Լ�� 2012.8.16 by yjj
	* @remarks 
	*/
    virtual u16 ReqKeyFrame( BOOL32 bForce ) const ;

	virtual TTPCnMediaTransPort GetVedioTransAddr() const { return m_tVideoTranAddr ;}

    virtual TTPCnMediaTransPort GetAudioTransAddr() const { return m_tAudioTranAddr ;}
		 
	/**
	* ����:  ��ȡ����cns����״̬
	* @param [out]tConfInfo  ����cns�μӵĻ�����Ϣ
	* @return �ɹ�����TRUE,ʧ�ܷ���FALSE
	* @remarks 
	*/
    virtual TTPCnsConfStatus GetCnsConfStatus() const; 

	//�װ���������Ϣ��Ӧ dyy 2014-5-14
	void OnJoinWBConfCmd( const CMessage &cMsg );
	void OnLeaveWBConfNty( const CMessage &cMsg );
	void OnNewConfCallReq( const CMessage &cMsg );
	//�װ�����û᳡��������Ϣ����
	void OnCnsInfoNty( const CMessage &cMsg );

	//tpad���ðװ�IP����
	void SetDataServerInfoCmd( u32 dwIp );
	//�����Ƿ�ɹ�
	void OnSetDataServerInfoInd( const CMessage &cMsg );
	//tpad��½ʱ�յ��װ�ip
	void OnSetDataServerInfoNty( const CMessage &cMsg );
	//�Լ����ƿ����İװ����
	void OnSelfMakeCallCmd( const CMessage &cMsg );
	//��Ե�������ݻ�������nty 2014-9-12
	void OnSetDataConfNameNty( const CMessage &cMsg );
	//����cnc�װ����״̬
	void WBConfStateNty( BOOL bIsInWBConf );

	void WBConfStartNty( bool bIsSelfStart, bool bIsSuccess );
	//��ȡ�װ���Ϣ
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

    TTpEncryptKey    m_tTpEncryptKey;   //˫����Կ

	//�װ���ز���
	TTPDataConfInfo m_tTPDataConfInfo;
	TTPCnsConfStatus m_tWBConfStatus;
	TTPCnsInfo m_tCnsInfo;
};

