/*****************************************************************************
ģ����      : cnclib
�ļ���      : umcconfCtrl.h
����ļ�    : 
�ļ�ʵ�ֹ���: ��������صĲ���
����        : Ф��Ȼ
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/4/25      1.0         Ф��Ȼ       ����
******************************************************************************/

#if !defined(AFX_CONFCTRL_H__CAFB9774_3218_4A07_80D4_B5B6EEE1ABE7__INCLUDED_)
#define AFX_CONFCTRL_H__CAFB9774_3218_4A07_80D4_B5B6EEE1ABE7__INCLUDED_
#include "cnsSession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmcConfCtrl : public CUmcConfCtrlIF  
{

/** @defgroup  �������ʵ�ֲ���
 *   @{
 */
public:
 	friend class CCncSession; 
 
	CUmcConfCtrl( CCnsSession &cCnsSession );
	CUmcConfCtrl( const CUmcConfCtrl &){};
    

public:
  /**
    * ����:	��ȡ�����б�
	* @param [out]  tplConfList	 �����б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	virtual u16 GetConf(  TCMSConf &tplConfList ) const ; 

  /**
    * ����:	��ȡ������cns�б�
	* @param [int]  vctConfCnsList	 �����б�
    * @param [out]  vctConfCnsList	 CNS�б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
   virtual u16 GetConfCnsList( vector<TCnsInfo> &vctConfCnsList ) const ;

    /**
    * ����:	��ȡ��������б�
	* @param [int]  wConfID:����ID  
    * @param [out]  tConfAudmixList	 �����б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
   virtual u16 GetConfAudmixList( TAuxMixList&tConfAudmixList ) const ;

  /**
    * ����:	��ȡ������ѯ�б�
	* @param [int]  wConfID:����ID  
    * @param [out]  tplConfPollList	 ��ѯ�б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
   //virtual u16 GetConfPollList(  TplArray<u16> &tplConfPollList ) const ;


	 
  /**
    * ����:	����ĳcns�᳡����ĳ����
	* @param [int]  tEp	 ����ͻ᳡��Ϣ
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��cms->ums  evtp_CallEP_cmd  \n
                       Ӧ�ظ���ums->cms evtp_CallEP_result   \n
	                   ���ɹ�����Ӧ����ums->cms evtp_UpdateConfCnsList_Notify
	*/ 
	virtual u16 InviteCnsReq( const TTpCallAddr &tAddr );


    /**
    * ����:	���л������Ѿ����ڵ�cns�᳡����ĳ����
	* @param [int]  tEp	 ����ͻ᳡��Ϣ
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��cms->ums  evtp_CallEP_cmd  \n
                       Ӧ�ظ���ums->cms evtp_CallEP_result   \n
	                   ���ɹ�����Ӧ����ums->cms evtp_UpdateConfCnsList_Notify
	*/ 
	virtual u16 CallConfCnsReq( const TConfEpID &tEp );
   

  /**
    * ����:	�Ҷϻ���
	* @param [int]  wConfID ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	virtual u16 HangupConfReq( );


   /**
    * ����:	�Ҷ�ĳ�᳡
	* @param [int]  tConfEpInfo �����᳡ID �� ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks �����б�����Ȼ���ڸû᳡��ֻ�ǲ�����
	*/
	virtual u16 HangupCNSReq( const TConfEpID &tConfEpInfo );

	 /**
    * ����:	�᳡���������
	* @param [int]  tConfEpInfo �����᳡ID �� ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ����Զҡ�᳡��Ϣ
	*/
	virtual u16 SetFeccConfEpInfo( const TConfEpID &tConfEpInfo );

	/**
    * ����:	�᳡���������
	* @param [int]  tConfEpInfo �����᳡ID �� ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��ȡԶҡ�᳡��Ϣ
	*/
	virtual u16 GetFeccConfEpInfo( TConfEpID &tConfEpInfo );

	/**
    * ����:	�᳡���������
	* @param [int]  
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks �᳡������������л�Զҡ�᳡��ƵԴ
	*/
	virtual u16 ChangeFeccSource(u8 SourceId);

	/** ����   Զҡ���������PT
	*  @param[in] emDirection�� ����  emCnAction������
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    virtual u16 SetFeccCamPT( EmDirection emDirection, EmCnAction emCnAction );

	/** ����   Զҡ�������Ұ����
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	virtual u16 SetFeccCamView( EmZoom emZoom, EmCnAction emCnAction );

	/** ����   Զҡ�������������
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	virtual u16 SetFeccCamBright( EmPanCamBright emPanCamBright, EmCnAction emCnAction );

		/** ����   Զҡ��������ڽ��� 
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	virtual u16 SetFeccCamFocus( EmFocus emFocus, EmCnAction emCnAction );

	/** ����   Զҡ������Զ����ڽ��� 
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	virtual u16 SetFeccCamAotoFocus( );

	/**
    * ����:	�ӻ������Ƴ�ĳ�᳡
	* @param [int]  tConfEpInfo �����᳡ID �� ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks �����б��в����ڸû᳡
	*/
	virtual u16 RemoveCNSReq( const TConfEpID &tConfEpInfo ) ;

  	/**
    * ����:	���÷��Ի᳡
	* @param [int]  wConfID	 ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 SetSpokeCnsReq( const TConfEpID &tConfEpInfo ) ;

   
    /**
    * ����:	����Զ��cns����
	* @param [int]  wConfID	 ����ID
    * @param [int]  bQuiet  TRUE:����������FALSE��ֹͣ����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 SetQuietCnsReq( const TConfEpID &tConfEpInfo, BOOL32 bQuiet) ;

    /**
    * ����:	����Զ��cns����
	* @param [int]  wConfID	 ����ID
    * @param [int]  bMute  TRUE:����������FALSE��ֹͣ����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 SetMuteCnsReq( const TConfEpID &tConfEpInfo , BOOL32 bMute) ;

     /**
    * ����:	����Զ��cns����˫��
	* @param [int]  wConfID	 ����ID
    * @param [int]  bStart  TRUE:����˫����FALSE��ֹͣ˫��
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 SetDualCnsReq( const TConfEpID &tConfEpInfo, BOOL32 bStart ) ;

	/**
    * ����:	���»����б�����
	* @param [int]  tMixInfo	 �����б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 UpdateAudMixListReq( const TConfAuxMixInfo &tMixInfoList );


	/**
    * ����:	���������б�����
	* @param [int]  tDisListOpr	 һ�������б����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 AudMixDisListOprCmd( const TDiscussListOpr &tDisListOpr );

		/** 
	* ����:  ��������
    * @param [in	TConfAuxMixVacOpr	 
    * @return	�ɹ�����0,ʧ�ܷ��ط�0������
    * @remarks 	 */
	virtual u16 AuxMixVacOpr( const TConfAuxMixVacOpr tConfAuxMixVacOpr);

  /**
    * ����:	������ѯ�б�����
	* @param [int]  tTurnInfoList	 ��ѯ�б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 UpdatePollListReq( const TConfTurnInfo &tTurnInfoList );

	
  /**
    * ����:	��������
	* @param [int]  wConfID	 ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 StartAuxMixReq( const u16 wConfID );

 /**
    * ����:	ֹͣ����
	* @param [int]  wConfID	 ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 StopAuxMixReq( const u16 wConfID );


   /**
    * ����:	������ѯ
	* @param [int]  wConfID	 ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 StartPollReq( const u16 wConfID );


  /**
    * ����:	ֹͣ��ѯ 
	* @param [int]  wConfID	 ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 StopPollReq( const u16 wConfID );
	

	//������ѯ��ͣ
	virtual u16 PollPauseCmd( const BOOL32& bIsPause );
	virtual TTpPollStat GetPollState();
	//������ѯ�б����
	virtual u16 PollListUpdateCmd( const TTpPollListNtfy& tTpPollListNtfy );
	/** 
	* ����  	�����ѯ�б�
	* @param [in] 	   
	* @return  
	* @remarks 
	*/	
	virtual u16 GetPollList(  vector<u16>& vctPollList  );

    /**	����:	ѡ����ϳ��� 
	* @param [int]  tRersvesEqp	 �ϳ���
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������ 
	*/
    virtual u16 RervesBrdVmpReq( TRersvesEqpReq tRersvesEqp );

    /**	����:	���û���ϳ� 
	* @param [int]  tVmpInfo	 ���úϳ�����Ϣ
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    virtual u16 SetBrdVmpReq( TSetVmpInfoReq tVmpInfo );
	//��Ӧ�Ƿ�᳡���Լ������
	virtual u16 SetJoinConfInfo( TTpConfEpInfo tpConfEpInfo );

    /**	����:	�㲥����ϳ� 
	* @param [int]  tBrdVmp	 �ϳ�����Ϣ
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    virtual u16 SetBroadcastVmpReq( TBrdVmpReq tBrdVmp );

    /** 
	* ����  ��ȡ����ϳ�״̬
	* @return  vector<TBrdVmpResNtfy> ����ϳ�״̬
	* @remarks 
	*/
	virtual const vector<TBrdVmpResNtfy>& GetBrdVmpStatus() const;

    /** 
	* ����  ����ϳ�Ԥ��
	* @return  tBrdVmp  ����ϳ�״̬
	* @remarks 
	*/
    virtual u16 SaveVmpCfgReq( TBrdVmpResNtfy &tBrdVmp );
    /** 
	* ����  ���úϳ�Ԥ��
    * @return  tEqp  ����ϳ�����Ϣ
	* @remarks 
	*/
    virtual u16 CallVmpCfgReq( TEqpInfo &tEqp );
    /** 
	* ����  ��ȡ����ϳ�Ԥ��
	* @return  ����ϳ�Ԥ��
	* @remarks 
	*/
	virtual const TVmpMemberCfg GetCurrentVmpCfg() const;

	/** 
	* ����  ����ѡ��״̬
	* @return  ����ѡ��״̬
	* @remarks 
	*/
	virtual const TTPSelViewNtfy GetSelWatchStatus() const;
	/** 
	* ����  ums��������
	* @return  ��������
	* @remarks 
	*/
	virtual const TTPUmsReasonInd GetUmsReason() const;
	 /** 
	* ����  ���������б�
	* @return  ���������б�
	* @remarks 
	*/
	const TDiscussListOpr GetDiscussList() const;
	//����������᳡��Ϣ
	const TTpConfEpInfo GetJoinConfInfo() const;

    /** 
	* ����  ����ǽ
    * @return  
	* @remarks 
	*/
    virtual u16 ChangeChanModeReq( u16 wIndex, u8 byMode  );

    virtual u16 SetHduVolReq( u16 wIndex, u8 byVol ,BOOL32 bMute );

    virtual u16 StopPlayHdu( TTpHduPlayReq &tTvwInfo );

    virtual u16 PlayHduReq( const TTpHduPlayReq & tTvwInfo );

	//����/��ȡ ȫ������/���� ״̬
	void SetAllQuiet( const CMessage& cMsg );
	virtual bool IsAllQuite();
	void SetAllMute( const CMessage& cMsg );
	virtual bool IsAllMute();

protected: 

    void OnChairCnsNotify( const CMessage& cMsg );
	void OnConfStateNty( const CMessage& cMsg );

	void OnHungUpConfRsp( const CMessage& cMsg ); 
	void OnInviteCnsRsp( const CMessage& cMsg ); 
    void OnCallConfCnsRsp( const CMessage& cMsg ); 
    void OnHangupCnsInd( const CMessage& cMsg );
	void OnUpdateConfCnsListNotify( const CMessage& cMsg ); 
	void OnUpdateConfAuxMixlistNotify( const CMessage& cMsg ); 
	void OnUpdateConfAuxMixlistInd( const CMessage& cMsg ); 
	void OnUpdateConfPolllistNotify( const CMessage& cMsg ); 
    void OnUpdateConfSpeakerNotify( const CMessage& cMsg ); 
	void OnAudMixDisListOprNotify( const CMessage& cMsg );
    void OnAMixVacNotify( const CMessage& cMsg );//����������Ӧ

	void OnSetSpokeCnsRsp( const CMessage& cMsg ); 
    void OnSetMuteCnsRsp( const CMessage& cMsg ); 
    void OnSetSilenceCnsRsp( const CMessage& cMsg ); 
    void OnSetDualCnsRsp( const CMessage& cMsg ); 
    void OnDualCnsNotify( const CMessage& cMsg ); 
    
	void OnCnsLeaveNotify( const CMessage& cMsg ); 

    void OnUmsCommonReasonInd( const CMessage& cMsg ); 

	//����ϳ� ����ռ�úϳɻ�Ӧ
    void OnRervesBrdVmpInd( const CMessage& cMsg );
    //�������û���ϳɻ�Ӧ
    void OnSetBrdVmpInd( const CMessage& cMsg );
    //����㲥����ϳɻ�Ӧ
    void OnBrdVmpInd( const CMessage& cMsg );
    //�ϳ���״̬֪ͨ
    void OnBrdVmpNty( const CMessage& cMsg );
    //����ϳ�Ԥ��֪ͨ
    void OnSaveVmpCfgCmd( const CMessage& cMsg );
    void OnSaveVmpCfgInd( const CMessage& cMsg );

    void OnLinkBreak( const CMessage& cMsg ); 

	virtual void DispEvent(const CMessage &cMsg);
	
    virtual void OnTimeOut(u16 wEvent);

	//������ѯ�б���»�Ӧ֪ͨ
	void OnPollListInd( const CMessage& cMsg );
	//������ѯ�б�֪ͨ
	void OnPollListNty( const CMessage& cMsg );
	//������ѯ��ͣ���֪ͨ
	void OnPollPauseInd( const CMessage& cMsg );

	//��ѯ״̬ ������
	void OnPollStatusNty( const CMessage &cMsg );

	//�᳡ѡ�� ״̬����
	void OnSetSelViewNty( const CMessage &cMsg );
	//�ն˻᳡�������
	void OnJoinConfReq( const CMessage &cMsg );

    //��������
    void OnSetAudioInfoInd( const CMessage &cMsg );

    //����ǽ֪ͨ
    void OnHduPlanNty( const CMessage& cMsg );

    void OnHduChangeModeInd( const CMessage& cMsg );

    void OnHduVolInd( const CMessage& cMsg );
       
    void OnHduStopPlayInd( const CMessage& cMsg );
    
    void OnHduPlayInd( const CMessage& cMsg );
	
	//H323�᳡��ƵԴ֪ͨ
	void OnP2PH323VideoInfo( const CMessage& cMsg );
	//H323�᳡��ƵԴ��ǰԴ���Ƿ��Զҡ
	void OnP2PH323VideoFeccInfo( const CMessage& cMsg );

	//������H323�᳡��ƵԴ֪ͨ
	void OnMulConfH323VideoInfoNty( const CMessage& cMsg );
    void OnMulConfH323VideoInfoInd( const CMessage& cMsg );
    
private:
	void  BuildEventsMap();
	 
private:
    CCnsSession *  m_pCncSession;
	TCMSConf       m_tConfInfo; 
	vector<u16>    m_vctPollList;//������ѯ�б�
	bool           m_bIsFirstPollListNty;//�Ƿ������ѯ�б���Ϣ��һ��֪ͨ
	s32		       m_nPollListFlag;//flag��ͬ ���֮ǰ���� �����µļ�¼    
	TTPSelViewNtfy  m_tTPSelViewNtfy;//����ѡ���б���Ϣ
	TDiscussListOpr m_tDiscussListOpr;//���������б�
	TTpConfEpInfo m_tpConfEpInfo;//����᳡��Ϣ

	TVidFeccInfo m_tVidFeccInfo;//Զҡ��ƵԴ��Ϣ

    vector<TBrdVmpResNtfy>  m_vctBrdVmpInfo;    //���л���ϳ�����
    TVmpMemberCfg     m_tVmpCurrentCfg;         //��ǰԤ����Ϣ
    TBrdVmpResNtfy    m_tVmpSaveCfg;            //���ڱ���Ļ���ϳ�Ԥ����Ϣ
    int               m_nRevCfgIndex;           //����Ԥ��������,Ԥ�������յ�
    int               m_nSaveCfgIndex;          //����Ԥ��������

    TTpHduPlanPackData	m_tHduPlanPackData[TP_STYLE_DATA_AllPACK_NUM];   //����ǽ
    int               m_bPackDataIndex;
	TTPUmsReasonInd   m_tTPUmsReasonInd;//������ʾ

	bool                      m_bIsAllQuite;           //�Ƿ�ȫ������
	bool                      m_bIsAllMute;            //�Ƿ�ȫ������
	
	TConfEpID                 m_tConfEpInfo;           //Զҡ����ID�᳡ID

	vector<TVidFeccInfo>      m_vctConf323VidInfo;     //�������323�᳡��ƵԴ

/** @}*/ //�������ʵ�ֲ���
};

#endif // !defined(AFX_CONFCTRL_H__CAFB9774_3218_4A07_80D4_B5B6EEE1ABE7__INCLUDED_)
