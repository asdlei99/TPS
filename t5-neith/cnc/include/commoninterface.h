/** @defgroup cnc����cnclib�Ĺ����ӿ� 
 *  @version V1.1.4
 *  @author  Ф��Ȼ
 *  @date    2014.8.14
 */
#pragma once

#include "cnclib.h"

class CCommonInterface
{
public:
	/** �����Ự
	*   @return u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
	*/
	void CreateSession();

	/** ���ٻỰ
	*   @return u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
	*/
	void DesdroySession();

	/** ��ȡ��Ƕ�Ĵ��ھ��
	*   @return HWND ���ش��ھ�� 
	*/
	HWND GetRecvWindow(){ return m_hRecvWnd;};
	/**
	* ����   ����CNS
	* @param [in]  dwIP	������UMS��IP��ַ��������
	* @param [in]  pStrUserName �û���	
	* @param [in]  pStrPswd	����
	* @return u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
	*/
	u16 Connect( u32 dwIp, u16 nPort, LPCTSTR pStrUserName, LPCTSTR pStrPswd ); 

	u16 RebootCns();

	u16 LinkCns();

    /** ����   ��õ�½CNS������
	*  @param[out] tLoginInfo
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    u16 GetLoginInfo( TLoginInfo& tLoginInfo );
	/** ����   ���õ�½CNS������
	*  @param[out] tLoginInfo
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    u16 SetLoginInfo( TLoginInfo tLoginInfo );

	/**
	* ����:  ��ǰ��¼���û��Ƿ��ǹ���Ա
	* @return  TRUE �ǹ���Ա��FALSE һ���û�
	*/
	BOOL IsManagerUser();

	//-----�᳡������ؽӿ� -------------
/** @defgroup  �᳡������ؽӿ�
 *  @{
 */  
	/**
	* ����:  ��ȡ����cns��Ϣ 
	*  @param[out] tCnsInfo����CNS��Ϣ
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	u16 GetLocalCnsInfo( TTPCnsInfo& tCnsInfo) const;
  
	/**
	* ����:  ����cns��Ϣ 
	* @param[in] tInfo CNS��Ϣ  byIndex ��Ϣ��������(0Ϊcnc 1Ϊά������)
	* @return �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	u16 UpdateCnsInfo( const TTPCnsInfo& tInfo, u8 byIndex = 0, EmTpIpNameNatSyn em= emSynInvalid);

	/**
	* ����:  ��ȡ��cns����Ϣ 
	* @param[out] vctScreenInfo����cns����Ϣ
	* @return �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	u16 GetCnsScreenInfo( vector<TScreenInfo>& vctScreenInfo ) const;

    u16 GetCnsScreenInfoByID( u8 screenID, TScreenInfo& tScreenInfo ) const;

	/**
	* ����:  ��ձ�cns����Ϣ 
	* @remarks 
	*/
	void ClearCnsScreenName();

	/**��ȡ��ǰȫ�������״̬
	*  @param[in] 
	*  @return BOOL �Ƿ���
	*/
	BOOL32 IsLocalCnsPanCam(); 

	/**���ػ᳡ȫ�������״̬ ����
	*  @param[in] Quite �Ƿ���
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 SetLocalCnsPanCam(u8 wCamId ,BOOL bPanCam = TRUE);

	/**��ȡ��ǰspeaker״̬���Ƿ�Ϊ����
	*  @param[in] 
	*  @return BOOL �Ƿ�Ϊ����
	*/
	BOOL32 IsLocalCnsQuite();

	/**��ȡ��ǰMic״̬���Ƿ�Ϊ ����
	*  @param[in] 
	*  @return BOOL �Ƿ�Ϊ����
	*/
	BOOL32 IsLocalCnsMute(); 

	/**���ػ᳡���� ����
	*  @param[in] Quite �Ƿ���
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 SetLocalCnsQuite( BOOL bQuite = TRUE );

	/**���ػ᳡���� ����
	*  @param[in] bMute �Ƿ�����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 SetLocalCnsMute( BOOL bMute = TRUE );

	/**���ڻ᳡��������
	*  @param[in] byVolume ����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 AdjustInputVol( u8 byVolume );

	/**���ڻ᳡�������
	*  @param[in] byVolume ����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 AdjustOutputVol( u8 byVolume );
	
	/**��ȡ�᳡��������
	*  @return  byVolume ����
	*/
	u8 GetInputVol();

	/**��ȡ�᳡�������
	*  @return byVolume ����
	*/
	u8 GetOutputVol();

	/**���û᳡������ϯ
	*  @param[in] bySeatId ��ϯID
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 SetCnsInnerSpeaker( u8 bySeatId );

	/**��ȡ�᳡������ϯ
	*  @param[in] 
	*  @return ��ϯID
	*/
	u8 GetCnsInnerSpeaker();


	/** 
	* ����  ����CNS�Ƿ������л�
	* @return  BOOL  �Ƿ�˫��
	* @remarks 
	*/
	BOOL32 IsViewLocalPIP();
	/** 
	* ����  ��ȡ����״̬
	* @return  
	* @remarks 
	*/
   BOOL32 GetRollState(TTpConfRollCallInfo &tTpConfRollCallInfo);
   /** 
	* ����  ��ȡ�������״̬
	* @return  
	* @remarks 
	*/
   BOOL32 GetRollAttendState(TTpRollCallPresentStateMsg &tTpRollCallPresentStateMsg);
   	/** 
	* ����  ��ȡ����״̬
	* @return  
	* @remarks 
	*/
   BOOL GetConfMixState(TTpAudMixInfo &tTpAudMixInfo);
    /** 
	* ����  ��ȡ�����б��޸Ļ�Ӧ
	* @return  
	* @remarks 
	*/
   BOOL GetConfMixIndFix(TTpAudMixListCmdRes &tTpAudMixListCmdRes);
	/** 
	* ����  ����CNS�Ƿ������л�
	* @return  BOOL  �Ƿ�˫��
	* @remarks 
	*/
	u16 ViewLocalPIPCmd( const u8 byScrnID, const BOOL bLocalP ) ;

/** @}*/

	//-----�����ؽӿ� -------------
/** @defgroup  �����ؽӿ�
 *  @{
 **
  
    /*
	**ѯ�ʻ���ģ������
	*/
	u16 GetCnTempPwdInd( s8 achPwd[] );

	/**������Ե���� 
	*  @param[in] tCnAddr   �Զ˻᳡
	*  @return  
	*/
	u16 StartP2PConf( TCnAddr& tCnAddr );

    u16 HungupPtpConf();

	/**
	* ����:  ʹ�û���ģ�忪�� 
	* @param [in]  tTemp: ģ�� 
	* @return �ɹ�����0��ʧ�ܷ��ش�����
	*/
	u16 StartTemplateConf( const TTPAlias& tTemp ) ; 	

	/**
	* ����:  ����һ����ʱ���� 
	* @param [in] tCnsList :�����ն��б� ,���᳡Ϊ��һ����Ա��������Ϊ���᳡
	* @param [out] achConfName :������
	* @return �ɹ�����0��ʧ�ܷ��ش�����
	* @remarks umsԤ��һ�����ڿ�����ʱ����Ļ���ģ�壨IDΪ0�����û���ģ����治��ʾ
	*/
	u16 StartInstantConf( const vector<TCnAddr>& tCnsList );	
 
	/**
	* ����:  �Ҷϻ��� 
	* @param [in] dwConfID������ID
	* @return �ɹ�����0��ʧ�ܷ��ش�����
	* @remarks ��������
	*/
	u16 HangupConf( );

         
	/**
	* ����:  ����ĳ�᳡������� 
	* @param [in] tEp:�᳡��Ϣ
	* @return �ɹ�����0��ʧ�ܷ��ش�����
	* @remarks �����᳡Ϊ���᳡ʱ���ɲ���
	*/
	u16 InviteCns( const TTpCallAddr &tEp );

    /**
	* ����:  �������᳡������� 
	* @param [in] tEp:�᳡��Ϣ
	* @return �ɹ�����0��ʧ�ܷ��ش�����
	* @remarks �����᳡Ϊ���᳡ʱ���ɲ���
	*/
	u16 InviteCns( const tagConfCallEpAddrList &tEp );

    /**
    * ����:	���л������Ѿ����ڵ�cns�᳡����ĳ����
	* @param [int]  tEp	 ����ͻ᳡��Ϣ
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��cms->ums  evtp_CallEP_cmd  \n
                       Ӧ�ظ���ums->cms evtp_CallEP_result   \n
	                   ���ɹ�����Ӧ����ums->cms evtp_UpdateConfCnsList_Notify
	*/ 
   u16 CallConfCns( const TConfEpID &tEp );
	 
    /**
	* ����:  ��ȡ������cns����Ϣ
	* @param [in] tEp:�᳡��Ϣ
    * @param [out] tCnsInfo:�᳡��Ϣ
	* @return �ɹ�����0��ʧ�ܷ��ش�����
	* @remarks �����᳡Ϊ���᳡ʱ���ɲ���
	*/
    u16 GetConfCnsByID( const TConfEpID &tConfEpInfo , TCnsInfo* pTCnsInfo); 	

	/**
    * �� ��:	��ȡ����ģ���б�
	* @param ��
	* @return  ����ģ���б�
	*/
	const vector<TTPAlias>& GetConfTempList();

	/**
    * �� ��:	���»���ģ��
	* @return  �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 UpdateConfTemplate();


	/**
	* ����:  ��ȡ����cns����״̬
	* @return cns����״̬
	* @remarks 
	*/
    TTPCnsConfStatus GetLocalCnsConfState() const; 

	/**
	* ����:  �Ƿ��ڻ�����  
	* @param [out]  pConf   ���ػ�����Ϣ
	* @return  �����Ƿ��ڻ�����
	*/
	BOOL32 IsInConf( TCMSConf *pConf = NULL );

	/** 
	* ����  ����/ֹͣ˫��
    * @param [in]  bStart  true:������false���ر�
	* @return  
	* @remarks 
	*/
	u16 StartDual( BOOL32 bStart );

	//��������
	u16 StartDualCodeStream( const TTPCnMediaTransPort  &tVedioTransAddr, const TTPCnMediaTransPort  &tAudioTransAddr  ) const;
	u16 StopDualCodeStream() const;

	u16 ReqKeyFrame( BOOL32 bForce = TRUE ) const;

	TTPCnMediaTransPort GetVedioTransAddr() const  ;
	TTPCnMediaTransPort GetAudioTransAddr() const  ;

	/** 
	* ����  ����cns�Ƿ���˫��
    * @param [in]  
	* @return  true:������false���ر�  
	*/
	BOOL32 IsLocalCnsDual() const;
	//��Ե������������״̬
	BOOL32 IsLocalPTPVoiceArouse() const;

	/** 
	* ����  ����/ֹͣ��ѯ
    * @param [in]  bStart  true:������false���ر�
	* @return  
	* @remarks 
	*/
	u16 StartPoll( BOOL32 bStart );
	/** 
	* ����  ����/ֹͣ����
    * @param [in]  tTpConfRollCallInfo  ������Ϣ
	* @return  
	* @remarks 
	*/
	u16 StartRoll( TTpConfRollCallInfo tTpConfRollCallInfo );
	/** 
	* ����  ������һ��
    * @param [in]  tTpRollCallNextEpInfo  ��һ������Ϣ
	* @return  
	* @remarks 
	*/
	u16 RollNext( TTpRollCallNextEpInfo tTpRollCallNextEpInfo );
	/** 
	* ����  ���״̬����
    * @param [in]  tTpRollCallPresentStateMsg  ���״̬
	* @return  
	* @remarks 
	*/
	u16 RollAttendState( TTpRollCallPresentStateMsg tTpRollCallPresentStateMsg );
	/** 
	* ����  ��������������б��޸�
    * @param [in]  tTpUpdataRollCallList  �б���Ϣ
	* @return  
	* @remarks 
	*/
	u16 RollListFixedCmd( TTpUpdataRollCallList tTpUpdataRollCallList );

	/** 
	* ����  ����/ֹͣ����
    * @param [in]  tTpAudMixInfo  ������Ϣ
	* @return  
	* @remarks 
	*/
	u16 StartConfMix( TTpAudMixInfo tTpAudMixInfo );
	/** 
	* ����  �޸Ļ����б�
    * @param [in]  tpAudMixListCmd  �޸���Ϣ
	* @return  
	* @remarks 
	*/
	u16 FixConfMix( TTpAudMixListCmd tpAudMixListCmd );
	
	/**
	* ����:  �Ҷ�ĳ�᳡ 
	* @param [in] tConfEpInfo: eqID ����ID
	* @return �ɹ�����0��ʧ�ܷ��ش�����
	* @remarks �����б�����Ȼ���ڸû᳡��ֻ�ǲ�����
	*/
    u16 HangupCns( const TConfEpID &tConfEpInfo );

	/*��  ��	�᳡���������
	��  ��	tConfEpInfo: eqID ����ID
	����ֵ	�ɹ�����0��ʧ�ܷ��ش�����
	˵  ��	�����Զҡ����������Զҡ�᳡��Ϣ*/
	u16 SetFeccConfEpInfo( const TConfEpID &tConfEpInfo );

	/*��  ��	�᳡���������
	��  ��	tConfEpInfo: eqID ����ID
	����ֵ	�ɹ�����0��ʧ�ܷ��ش�����
	˵  ��	�����Զҡ��������ȡԶҡ�᳡��Ϣ*/
	u16 GetFeccConfEpInfo( TConfEpID &tConfEpInfo );

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
    u16 SetFeccCamPT( EmDirection emDirection, EmCnAction emCnAction );

	/** ����   Զҡ�������Ұ����
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 SetFeccCamView( EmZoom emZoom, EmCnAction emCnAction );

	/** ����   Զҡ�������������
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 SetFeccCamBright( EmPanCamBright emPanCamBright, EmCnAction emCnAction );

		/** ����   Զҡ��������ڽ��� 
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 SetFeccCamFocus( EmFocus emFocus, EmCnAction emCnAction );

	/** ����   Զҡ������Զ����ڽ��� 
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 SetFeccCamAotoFocus();
 
	/**
	* ����:  �ӻ������Ƴ�ĳ�᳡ 
	* @param [in] tConfEpInfo: eqID ����ID
	* @return �ɹ�����0��ʧ�ܷ��ش�����
	* @remarks �Ƴ�������б��в����ڸû᳡ ,��ʱ���øýӿ�
	*/
	u16 RemoveCns( const TConfEpID &tConfEpInfo );

	/**
	* ����:  ���÷��Ի᳡
	* @param [in]wConfID	 ����ID
	* @return �ɹ�����0��ʧ�ܷ��ش����� 
	*/ 
	u16 SetSpokeCns( const TConfEpID &tConfEpInfo );
    /**
	* ����:  ���û᳡����
	* @param [in]
	* @return �ɹ�����0��ʧ�ܷ��ش����� 
	*/ 
    u16 SetMuteCns( const TConfEpID &tConfEpInfo , BOOL32 bMute);
    /**
	* ����:  ���û᳡����
	* @param [in]
	* @return �ɹ�����0��ʧ�ܷ��ش����� 
	*/
    u16 SetQuietCns( const TConfEpID &tConfEpInfo, BOOL32 bQuiet);
    /**
	* ����:  ���û᳡˫��
	* @param [in]
	* @return �ɹ�����0��ʧ�ܷ��ش����� 
	*/
    u16 SetDualCns( const TConfEpID &tConfEpInfo, BOOL32 bStart );
     
    /** 
	* ����:  ���»����б�����
    * @param [in	tMixInfo	 �����б�
    * @return	�ɹ�����0,ʧ�ܷ��ط�0������
    * @remarks 	 */
	u16 UpdateAudMixList( const TConfAuxMixInfo &tMixInfoList );

	/** 
	* ����:  ��������
    * @param [in	TConfAuxMixVacOpr	 
    * @return	�ɹ�����0,ʧ�ܷ��ط�0������
    * @remarks 	 */
	u16 AuxMixVacOpr( const TConfAuxMixVacOpr tConfAuxMixVacOpr);
	/** 
	* ����:  ����������������
    * @param [in	�Ƿ���	 
    * @return	�ɹ�����0,ʧ�ܷ��ط�0������
    * @remarks 	 */
	u16 SetCnAuxMix( BOOL bIsAudMix);
	/** 
	* ����:  ����UI_CNS_CONFSTATE_NOTIFY��Ϣˢ�½������״̬
    * @param [in	 
    * @return	�ɹ�����0,ʧ�ܷ��ط�0������
    * @remarks 	 */
	u16 FreshConf();
	/** 
	* ����:  �����б��������
    * @param [in	tDisListOpr	 �����б����
    * @return	�ɹ�����0,ʧ�ܷ��ط�0������
    * @remarks 	 */
	u16 AudMixDisListOpr( const TDiscussListOpr &tDisListOpr );

     /** 
	* ����  ȡ��ѡ��
    * @param [in]  byScreenID  ����
	* @return  
	* @remarks 
	*/
	u16 ScrnCancleSelView( u8 byScreenID );

	/** 
	* ����  ��Ļ��ʾ˫��ͼ��
	* @param [in]  wScrnID  ����
	* @return
	* @remarks 
	*/
    u16 ScrnDisplayDual( const u16 wScrnID ) const;

		/** 
	* ����  ��Ļ��ʾ˫��ͼ��
	* @param [in]  wScrnID  ���� bIsShow �Ƿ���ʾ
	* @return
	* @remarks 
	*/
    u16 ScrnSpareTimeDisplayDual( u16 wScrnID, BOOL bIsShow);

     /** 
	* ����  ��Ļȡ����ʾ˫��ͼ��
	* @return  
	* @remarks 
	*/
    u16 ScrnStopDisplayDual( const u16 wScrnID ) const;

    /** 
	* ����  ��Ļ��ʾ����
	* @param [in]  wScrnID  ����
	* @return    
	* @remarks 
	*/
    u16 ScrnDisplayLocal( const u16 wScrnID ) const;

    /** 
	* ����  ȡ����Ļ����
	* @return    
	* @remarks 
	*/
    u16 ScrnStopDisplayLocal( const u16 wScrnID ) const;

    /** 
	* ����  �Ƿ����˫��
	* @return    
	* @remarks 
	*/
    BOOL32 IsRcvDual() const; 
    /**
	* ����:  ��ȡ����ϳ�״̬
	* @return ����ϳ�״̬
	* @remarks 
	*/
    const vector<TBrdVmpResNtfy>& GetBrdVmpStatus(); 
    /**
	* ����:  ��ȡ����ѡ��״̬
	* @return ����ѡ��״̬
	* @remarks 
	*/
    const TTPSelViewNtfy GetSelWatchStatus();
		/** 
	* ����  ums��������
	* @return  ��������
	* @remarks 
	*/
	const TTPUmsReasonInd GetUmsReason();
	//��û��������б�
	const TDiscussListOpr GetDiscussList();
	//��ü������᳡��Ϣ
	const TTpConfEpInfo GetJoinConfInfo();
	//�����Ƿ�����᳡�������
	u16 SetJoinConfInfo(TTpConfEpInfo tpConfEpInfo);
	//��ȡȫ����������״̬
	bool IsAllQuite();
	bool IsAllMute();

    /**
	* ����:  ռ�û���ϳ���
    * @param [in]  tEqpInfo  ����ϳ���
	* @return 
	*/
    u16 RervesBrdVmpReq( TRersvesEqpReq tRersvesEqp );
    /**
	* ����:  ���û���ϳ�
    * @param [in]  tVmpInfo  ����ϳ���Ϣ
	* @return 
	*/
    u16 SetBrdVmpReq( TSetVmpInfoReq tVmpInfo );
    /**
	* ����:  �㲥����ϳ�
    * @param [in]  tVmpInfo  ����ϳ���Ϣ
	* @return 
	*/
    u16 SetBroadcastVmpReq( TBrdVmpReq tBrdVmp );
    /**
	* ����:  ����ϳ�Ԥ��
    * @param [in]  tVmpInfo  ����ϳ���Ϣ
	* @return 
	*/
    u16 SaveVmpCfgReq( TBrdVmpResNtfy &tBrdVmp );
    /**
	* ����:  ���úϳ�Ԥ��
	* @return 
	*/
    u16 CallVmpCfgReq( TEqpInfo &tEqp );

	/**
	* ����:  �ı����ǽģʽ
	* @return 
	*/
	u16 ChangeChanModeReq( u16 wIndex, u8 byMode  );
    /**
	* ����:  ���õ���ǽ����
	* @return 
	*/
	u16 SetHduVolReq( u16 wIndex, u8 byVol ,BOOL32 bMute );
    /**
	* ����:  ֹͣ����ǽ
	* @return 
	*/
	u16 StopPlayHdu( TTpHduPlayReq &tTvwInfo);
    /**
	* ����:  ���ŵ���ǽ
	* @return 
	*/
	u16 PlayHduReq( TTpHduPlayReq &tTvwInfo );

/** @}*/ 

	 //-----ϵͳ�����������-------------  
/** @defgroup  ϵͳ����
 *  @{
 */

	/** ����   �����ʾԴ��Ϣ
	*  @param[out] tDualSrcinfo ��ʾԴ����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    u16 GetDualSrcInfo( TDualSrcInfo& tDualSrcinfo );

    /** ����   ѡ����ʾԴ�˿�
	*  @param[out] emType ��ʾԴ����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    u16 SelDualInputPort( EmVgaType emType );

    /** ����   ������ʾԴ��Ϣ
	*  @param[in] tVgaInfo ��ʾԴ��Ϣ
    *  @param[in] bDefault �Ƿ�Ĭ����ʾԴ
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    u16 SetDualPortInfo( const TVgaInfo& tVgaInfo, BOOL bDefault );

	/** ����   ���SIP����
	*  @param[out] tSipCfg SIP����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetSipCfg( TTPSipRegistrarCfg& tSipCfg );

    /** ����   ���Gk����
	*  @param[out] tGkCfg
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetGkCfg( TTPGKCfg& tGkCfg );

	/** ����:  ������������
	*  @param[in] tInfo ��������
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*  @remarks 
	*/
	u16 UpdateEthnetCfg( const TTPEthnetInfo& tInfo, EmTpIpNameNatSyn em= emSynInvalid );

	/** ����   �����������
	*  @param[out] tInfo ��������
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetEthnetCfg( TTPEthnetInfo& tInfo );

	/** ����   ���NAT����
	*  @param[out] tInfo NAT����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetNATCfg( TTPNatCfg& tInfo );

	 /** ����   ����ϵͳʱ��
	 *  @return �ɹ����ػ᳡��,ʧ�ܷ���NULL
	 *  @remarks 
	 */
     u16 UpdateSysTime( const TTPTime& time ) ;
      
    /** ����   ��ȡϵͳʱ��
	 *  @return �ɹ����ػ᳡��,ʧ�ܷ���NULL
	 *  @remarks 
	 */
    u16 ReqSysTime();

	/** ����   ������������ַ
	 *  @param[in] TTPUpgradeSer ��������ַ�ṹ��
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 UpgradeSerCmd( const TTPUpgradeSer& tUpgradeSer );

	/**��ȡ��������������������Ϣҳ���� 
	*/
	u16 GetNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg );

 	/**
    * ����:	 	        ���������������
 	* @param [in]       ������Ϣ
 	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
 	*/
 	u16  NetMngAddCmd( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * ����:	 	        �����޸���������
 	* @param [in]       ������Ϣ
 	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
 	*/
	u16  NetMngModifyCmd( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * ����:	 	        ����ɾ����������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  NetMngDeleteCmd( const TTPNMServerCfg& tTPNMServerCfg );

	/** ����   ����ϵͳ������Ϣ
	*  @param[in] tTPSleepInfo ϵͳ������Ϣ
    *  @param[in] bDefault �Ƿ�����ϵͳ����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    u16 SetSysSleepInfo( const TCenDevSleepInfo& tCenDevSleepInfo );

	/** ����   ���ϵͳ������Ϣ
	*  @param[out] tDualSrcinfo ��ʾԴ����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    u16 GetSysSleepInfo( TCenDevSleepInfo& tCenDevSleepInfo );

	/** ����:  CNS����SIPע������ 
	*  @param[in] tSipCfg Sipע������
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 CnsRegSipService( const TTPSipRegistrarCfg &tSipCfg );

	/** ����:  CNSע��SIP���� 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 CnsUnRegSipService();

    /** ����:  CNS����Gkע������ 
	*  @param[in] tSipCfg Sipע������
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 CnsRegGkService( const TTPGKCfg &tCfg );

	/** ����:  ����NAT����
	*  @param[in] tInfo NAT����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*  @remarks 
	*/
	u16 UpdateNATCfg( const TTPNatCfg& tInfo, EmTpIpNameNatSyn em= emSynInvalid );

	/** ����   ��÷�������ַ
	*  @param[out] TTPUpgradeSer ��������ַ�ṹ��
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetUpgradeSerInfo( TTPUpgradeSer& tUpgradeSer );

	/** ����   ���з�����
	*   @param[in] u32_ip ��������ַ
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 CallServerCmd( const TTPCallSerInfo& tCallSerInfo );

	/** ����   ��ȡ���з���������
	*  @param[out] TTPCallSerInfo ���з���������
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetCallServerInfo( TTPCallSerInfo& tCallSerInfo );

	/**����    ��ȡ��ǰ����ü�״̬���Ƿ���
	*  @param[in] 
	*  @return BOOL �Ƿ���
	*/
	BOOL32 IsVidCutLine() const;
	/** 
	* ����  ���û���ü�
    * @param [in]  BOOL bIsVidCutLine �Ƿ���
	* @return  
	* @remarks 
	*/
	u16 SetVidCutLine( BOOL bIsVidCutLine );
	
	/** ����   �������Ӽ���
	 *  @return
	 */
	u16 SetQtEncryptCfg( const TTpQtEncryptCfg& tQtEncrypt);
	/** ����   ������Ӽ�����Ϣ
	 *  @return TTpQtEncryptCfg���Ӽ�����Ϣ
	 */
    u16 GetQTEncrypt(TTpQtEncryptCfg& tQtEncrypt);
	/**
    * ����:	 	        ʱ��ͬ������
 	* @param [in]       
 	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
 	*/
 	u16  SetTimeSynchroCmd( BOOL bIsCheck );
/** @}*/ 

	//�������ڸ���
	u16 SetTpadPasswordUpdate( TTpPasswordUpdateInfo tTpPasswordUpdateInfo );
	//��ȡ����������Ϣ
	u16 GetPasswordUpdateInfo( TTpPasswordUpdateInfo& tTpPasswordUpdateInfo );

    //��������Ա��Ϣ
    u16 SetSuperadmninInfo(TTpSuperUser tTpSuperUser);
    u16 GetSuperadmninInfo(TTpSuperUser& tTpSuperUser);
    //��������Ա���������û�
    u16 UnlockAllUser();

	//-----��ַ�����-------------  
/** @defgroup  ��ַ�����
 *  @{
 */	 
	/** ����:  ��ȡ��ַ��
	 *  @return CAddrBook ���ص�ַ������
	 */
	CAddrBook& GetAddrBook();

	/** ����:  ��ӵ�ַ����Ŀ
	 *  @param[in] entry ��ַ����Ŀ
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */ 
	u16 AddEntry( const CAddrEntry& entry );

	/** ����:  �޸ĵ�ַ����Ŀ
	 *  @param[in] entry ��ַ����Ŀ
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 ModifyEntry( const CAddrEntry& entry );

	/** ����:  ɾ����ַ����Ŀ
	 *  @param[in] dwIndex ��ַ����Ŀ����
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 DeleteEntry( u32 dwIndex );

	/** ����:  ɾ�������ַ����Ŀ
	 *  @param[in] vctEntry ��ַ����Ŀ������
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 DeleteMultiEntry( vector<u32>& vctEntry );

	/** ��ӵ�ַ����Ŀ��
	 *  @param[in] group ��ַ����Ŀ��
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 AddGroup( const CAddrMultiSetEntry& group );

	/** �޸ĵ�ַ����Ŀ��
	 *  @param[in] entry ��ַ����Ŀ��
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 ModifyGroup( const CAddrMultiSetEntry& group );

	/** ɾ����ַ����Ŀ��
	 *  @param[in] dwIndex ��ַ��������
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 DeleteGroup( u32 dwIndex );

    /** ����:  ɾ�������ַ����
	 *  @param[in] vctGroup ��ַ����������
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
    u16 DeleteMultiGroup( vector<u32>& vctGroup );

	/** ��ӵ�ַ�����Ա
	 *  @param[in] tGroupEntry ��ַ������Ϣ
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 AddEntryToGroup( const TADDRMULTISETENTRY& tGroupEntry );

	/** ɾ����ַ�����Ա
	 *  @param[in] tGroupEntry ��ַ������Ϣ
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 DelEntryFromGroup( const TADDRMULTISETENTRY& tGroupEntry );

	/** ��ӵ�ַ�����ϵ
	 *  @param[in] dwGroupIndex ������
	 *  @param[in] dwUpGroupIndex �ϼ�������
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 AddGroupToGroup( u32 dwGroupIndex, u32 dwUpGroupIndex );

	/** ɾ����ַ�����ϵ
	 *  @param[in] dwGroupIndex ������
	 *  @param[in] dwUpGroupIndex �ϼ�������
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 DelGroupFromGroup( u32 dwGroupIndex, u32 dwUpGroupIndex );

	/** ����ȫ�ֵ�ַ��
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 UpdateGlobalAddrbook();

	/**
	* ����:  ��ȡ���ص�ַ���б�  
	* @return  �ɹ����ص�ַ���б�ָ�룬ʧ�ܷ��ؿ�
	*/
	const vector<TAddrItem>* GetLocalAddrList();

	/**
	* ����:  ��ȡȫ�ֵ�ַ���б�  
	* @return  �ɹ����ص�ַ���б�ָ�룬ʧ�ܷ��ؿ�
	*/
	const vector<TAddrItem>* GetGlobalAddrList() const;

	/**
	* ����:  ��ȡcnsע��ĵ�ַ����Ŀ  
	* @return  �ɹ����ص�ַ���б�ָ�룬ʧ�ܷ��ؿ�
	*/
	void GetCnsRegInfo( vector<TAddrInfo>* pvctCnsRegInfo );

    /** ����  ��ջ�ȡ����Sipע����Ϣ
	*  @param[in] emTyep  ����
	*  @return ��
	*/
	void ClearSipRegInfo( EmGetRegInfoType emTyep );

    /**
	* ����:  ��ȡ���ص�ַ����Ŀ�б�  
	* @return  �ɹ����ص�ַ���б�ָ�룬ʧ�ܷ��ؿ�
	*/
    const vector<TAddrItem>* GetAddrEntryList();

	/**
	* ����:  ��ȡ��ַ�������Ա�б�  
	* @param[in]  dwGroupIndex  ������
	* @param[out] vctGroupMemberList  �����Ա�б�
	* @return  
	*/
	void GetAddrGroupMember( u32 dwGroupIndex, vector<TAddrItem>& vctGroupMemberList );

	/**
	* ����:  ��ȡ��ַ��������Ϣ
	*  @param[in]  dwGroupIndex  ������
	*  @param[out] tGroupInfo  ������Ϣ
	*  @return
	*/
	void GetAddrGroupInfo( u32 dwGroupIndex, TGroupInfo& tGroupInfo );

	 //-----�û���� -------------
/** @defgroup  �û����
 *  @{
 */
	 
	/**
	* ����:  ��ȡ�û��б�  
	* @return  �ɹ������û��б�ָ�룬ʧ�ܷ��ؿ�
	*/
   TplArray<CUserFullInfo>* GetUserList() ;
	
   /**
	* ����:  ����û� 
	* @param [in]  user  
	* @return  �ɹ�����0��ʧ�ܷ��ش�����
	*/
	u16 AddUser( const CUserFullInfo& user )    ;
    
	/**
	* ����:  �޸��û���Ϣ 
	* @param [in]  user  
	* @return  �ɹ�����0��ʧ�ܷ��ش�����
	*/
	u16 UpdateUser( const CUserFullInfo& user )   ;
	 
	/**
	* ����:  ɾ���û� 
	* @param [in]  user  
	* @return  �ɹ�����0��ʧ�ܷ��ش�����
	*/
    u16 DeleteUser( const CUserFullInfo & user ) ;
	 
	/**
	* ����:  �����û�����ȡ�û���Ϣ 
	* @param [in]  pUserName  
	* @return  �ɹ������û���Ϣָ�룬ʧ�ܷ��ؿ�ָ��
	*/
	CUserFullInfo *GetUserByName ( s8 *pUserName )  const ;

	/**
	* ����:  ��ȡ��ַ������·����
	*  @param[in]  dwGroupIndex  ������
	*  @return  ·����
	*/
	CString GetAddrGroupPath( u32 dwGroupIndex );


/**
	* ����:  �ж��û����Ƿ��Դ��� 
	* @param [in]  pUserName  
	* @return  �ɹ�����TREU��ʧ�ܷ���FLASE
	*/
	BOOL32  IsExistUser ( s8 *pUserName ) const ;

	/** ��CAddrEntry�����赽TAddrInfo��
	 *  @param[out] tAddrInfo  ��ַ��Ŀ��Ϣ
	 *  @param[in]  cAddrEntry ��ַ����Ŀ��Ϣ
	 *  @return 
	 */
	void SetAddrItemInfo( TAddrInfo& tAddrInfo, CAddrEntry& cAddrEntry );

	/** ��ȡ���е���Ŀ��Ϣ
	 *  @param[in]   tGroupInfo  ��ַ����Ϣ
	 *  @param[out]  vctAddrInfo ��ַ��Ŀ��Ϣ�б�
	 *  @return 
	 */
	void GetGroupAddrInfo( const TGroupInfo& tGroupInfo, vector<TAddrInfo>& vctAddrInfo );  

	BOOL GetAddrLoadingState();
	void SetAddrLoadingState(BOOL bAddrLoading);

	/**
	* ����   �װ����������
	* @param [in]  dwIP	IP��ַ
	* @param [in] 
	* @param [in] 
	* @return u16 
	*/  
    u16 SetDataServerInfoCmd( const u32 dwIp );

	/**
	* ����   ������˷�״̬����
	* @param [in]  nIndex ��˷�����
	* @param [in]  bCheck ״̬
	* @return u16 
	*/  
    u16 SetMicStateCmd( u8 nIndex, BOOL bCheck );

	/** �������ݻ���״̬
	 *  @param[out] 
	 *  @param[in]  
	 *  @return 
	 */
    void SetWBConfState(  bool bIsInWBConf ){ m_bIsInWBConf = bIsInWBConf; };

    bool GetWBConfState(){ return m_bIsInWBConf; };

    /** ����   ��ðװ�ip����
	*  @param[out] TTPDataConfInfo �װ��������ַ�ṹ��
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetWBSerIp( TTPDataConfInfo& tWBSerIp );

 	//�޸�ϵͳ��
	u16 changeSysName();
	/** 
	* ����  	��ȡ������ѡ��ʽ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetVideoFormatInfo( TTPVidForamt& tVidForamt )const;
	/** 
	* ����  	��ȡ��ʾ��ѡ��ʽ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetDualVideoFormatInfo( TTPVidForamt& tVidForamt )const;
	/** 
	* ����  	��ȡ��������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCallRateInfo( u16& wCallRate )const;
	/** 
	* ����  	��ȡ��ʾ����
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetDualCallRateInfo( u16& wDualCallRate )const;
	/** 
	* ����  �޸���ʾ����
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 DualCallRateCmd( const u16 wDualCallRate );
	/** 
	* ����  �޸ĵ�����ʾ����
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 CallRateCmd( const u16 wDualCallRate );
	/** 
	* ����  	��ȡ������ѯ��Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetConfPollInfo( TTPPollInfo& tPollInfo )const;
	/** 
	* ����  	�޸Ļ�����ѯ��Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 ConfPollCmd( const TTPPollInfo& tPollInfo );
	/** 
	* ����  	��ȡ����������Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetConfDisInfo( BOOL& bDis )const;
	/** 
	* ����  	��ȡ��Ƶ��ʽ��Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	EmTpAudioFormat GetAudioFormatInfo()const;

	/**
    * ����:	 	        ������Ƶ��ʽ��Ϣ
	* @param [in]       
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  AudioFormatCmd( const EmTpAudioFormat& emAudioFormat );

	/** 
	* ����  	������Ƶ��ʽ��Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 VideoFormatCmd( const TTPVidForamt& tVidForamt );
	/** 
	* ����  	������ʾ��ѡ��ʽ��Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 DualVideoFormatCmd( const TTPVidForamt& tVidForamt );
	/** 
	* ����  	���û���������Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	u16 ConfDisCmd( const BOOL& bDis );
	/** ����   ���logo��Ϣ
	*  @param[out] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetLogoInfo( TTPLogoInfo& tInfo );
	/** ����   ���banner����
	*  @param[out] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetBannerInfo( TTPBannerInfo& tInfo );
	/** 
	* ����  	̨������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 CnIsShowLogoCmd( const TTPLogo& tTPLogo );
	/** 
	* ����  	�������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	virtual u16 CnIsShowBannerCmd( const TTPBanner& tTPBanner );
// 	/** 
// 	* ����  ̨���ļ��ϴ��ɹ�֪ͨ
// 	* @param [in] 	 
// 	* @return  
// 	* @remarks 
// 	*/
// 	u16 ConfSignCmd( const BOOL& bOk, u8 byIndex );
	/**
	* ����:	��ȡ��½cns ��IP 
	* @return  u32  IP
    */
	u16 GetLoginIp( u32 & IP ); 
	/**
	* ����:	��ȡ���� ��IP 
	* @return  u32  IP
    */
	 u16 GetLocalIP( u32 & IP ) ;
     /** 
	* ����  	����ftp��Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 SetCnFtpInfo(TTPFtpInfo tTPFtpInfo);
	/** 
	* ����  	��ȡftp��Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCnFtpInfo(TTPFtpInfo &tTPFtpInfo);
	/** 
	* ����  	��ȡtelnet��Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCnTelnetInfo(TTPTelnetInfo &tTPTelnetInfo);
	/** 
	* ����  Encryt��������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 EncrytCmd( const TTpEncryptKey& tEncryt );
	/**
	* ����:	��ȡEncryt��������
	* @return  Encryt��������
    */
	u16 GetEncrytInfo( TTpEncryptKey& tEncryt ); 

    /** 
	* ����  ����ѡ��
    * @param [in]  byScreenID  ����
    * @param [in]  wEpID  ѡ����cnsID
	* @return  
	* @remarks 
	*/
	u16 SetSelView( TTPSelViewReq tTPSelViewReq ) ;//B4��Ϣ��ͳһ��ev_Cn_SelView_Req

     /** 
	* ����  ȡ��ѡ��
    * @param [in]  byScreenID  ����
    * @param [in]  wEpID  ѡ����cnsID
	* @return  
	* @remarks 
	*/
	u16 CancleSelView( u8 byScreenID ) ;
	/** 
	* ����  	��ȡ�пص���ǽ����״̬
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	BOOL GetDisplayState() const;
	    /** 
	* ����  ���õ���ǽѡ��
    * @param [in]  byScreenID  ����
	* @return  
	* @remarks 
	*/
	u16 SetSelTVSView( u8 byScreenID ) ;

     /** 
	* ����  ȡ������ǽѡ��
    * @param [in]  byScreenID  ����
    * @param [in]  wEpID  ѡ����cnsID
	* @return  
	* @remarks 
	*/
	u16 CancleSelTVSView( u8 byScreenID ) ;
	/**
	* ����:  ����cns�Ƿ�����ϯ 
	* @return �ɹ�����TRUE,ʧ�ܷ���FALSE
	* @remarks ��CNS��������״̬
	*/
	BOOL32 IsLocalCnsChairMan()  ;

	   /**
	* ����:  ��ȡ������Ϣ  
	* @return  �����б�ָ��
	*/
    TCMSConf  &GetConfInfo(){ return m_tConfInfo ; }
	/** ����   ���ȫ��������б�
	*  @param[out] tDualSrcinfo ��ʾԴ����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    u16 GetPanCamList( TPanCamInfo& tPanCamInfo );
	/** ����   ����ȫ���������ǰѡ�б��
	*  @param[in] wIndex ��ǰѡ�б��
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    u16 SetPanCamSelectIndex( u8 wIndex );
	/** ����   ��������ƵԴ�˿�
	*  @param[in] emTPMtVideoPort������ƵԴ�˿� wID����Ӧ�ڼ�·��ƵID
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    u16 SetMainVideoPort( EmTPMtVideoPort emTPMtVideoPort, u8 wID );
	/** ����   �������ƵԴ�˿�
	*  @param[out] mapEmTPMtVideoPort ����ƵԴ
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    u16 GetMainVideoPort(  map<u16, EmTPMtVideoPort>& mapEmTPMtVideoPort );
	/** ����   �������Ƶ������
	*  @param[out] tTPVideoInfoTool ����Ƶ������
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    u16 GetVedioInfo(  TTPVideoInfoTool& tTPVideoInfoTool );

	/** ����   ȫ�����������PT
	*  @param[in] emDirection�� ����  emCnAction������
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    u16 SetPanCamPT( EmDirection emDirection, EmCnAction emCnAction );

	/** ����   ȫ���������Ұ����
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 SetPanCamView( EmZoom emZoom, EmCnAction emCnAction );

	/** ����   ȫ���������������
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 SetPanCamBright( EmPanCamBright emPanCamBright, EmCnAction emCnAction );

		/** ����   ȫ����������ڽ��� 
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 SetPanCamFocus( EmFocus emFocus, EmCnAction emCnAction );

	/** ����   ȫ��������Զ����ڽ��� 
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 SetPanCamAotoFocus();
	    /** 
	* ����  ȫ�����������Ԥ��λ
    * @param [in]  wID  Ԥ��λ��
	* @return  
	* @remarks 
	*/
	u16 SavePanCamPreset(  u8 wID ); 
	 /** 
	* ����  ȫ�����������Ԥ��λ
    * @param [in]  wID  Ԥ��λ��
	* @return  
	* @remarks 
	*/
	u16 ImpelPanCamPreset(  u8 wID ); 
	/** 
	* ����  ȫ�������ɾ��Ԥ��λ
    * @param [in]  wID  Ԥ��λ��
	* @return  
	* @remarks 
	*/
	u16 DeletePanCamPreset(  u8 wID ); 
	/** 
	* ����  ȫ�������Ԥ��λ�����޸�
    * @param [in]  wID  Ԥ��λ��
	* @return  
	* @remarks 
	*/
	u16 SavePanCamPresetName(  u8 wID, TPanCamName tPanCamName ); 
	/** 
	* ����  ������ѯ��ͣ
    * @param [in]  BOOL32& bIsPause �Ƿ���ͣ
	* @return  
	* @remarks 
	*/
	u16 PollPauseCmd( const BOOL32& bIsPause );
		/** 
	* ����  ��ȡ������ѯ��ͣ״̬
    * @param [in]  
	* @return  BOOL32 �Ƿ���ͣ
	* @remarks 
	*/
	TTpPollStat GetPollState();
	/** 
	* ����  ������ѯ�б����
    * @param [in]  TTpPollListInd �б���Ϣ
	* @return  
	* @remarks 
	*/
	u16 PollListUpdateCmd( const TTpPollListNtfy& tTpPollListNtfy );
	/** 
	* ����  ��ȡ������ѯ�б�
    * @param [in]  TTpPollListNtfy& tTpPollListNtfy �б���Ϣ
	* @return  
	* @remarks 
	*/
	u16 GetPollList( vector<u16>& vctPollList );

    /** 
	* ����  ����/��ȡ��ǰ����ϳɿ���
    * @param [in]  bOpen ����
	* @return  
	* @remarks 
	*/
    void SetCurtVidMixOpen( BOOL bOpen ){ m_bVidMixOpen = bOpen; }
    BOOL IsCurtVidMixOpen(){ return m_bVidMixOpen; }

/** 
 *  �пؽӿڿ�ʼ
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
    //�յ���Ļѡ������Ϣ
	u16 SelectAirMonitor( u8 byIndex );

	u16 GetCentreACCfg( vector<TCentreACCfg> &vecTCentreACCfg );

	u16 SetACPowerMode( u8 byIndex, EmCentreACPower emMode );
	
	u16 SetApplyToAll( u8 byIndex, BOOL* abIsCtrl );

	u16 GetApplyToAllInfo( BOOL** pIsCtrl );

	u16 SetCurtainState( BOOL* bIsCtrl, EmCurAction emCurAction );

	u16 GetCentreCurName( vector<TCentreCurName> &vecTCentreCurName );
	u16 GetCentreCurInfor( TCentreCurInfo &tCentreCurInfo );
	//�пؿ�����Ϣ 2015-6-17 
	u16 GetCentreSchCfg( TCentreSchCfg &tCentreSchCfg );
    u16 GetDCamStateMap( map<u8, TCentreDCamCfg> &mapDCamCfg );
    u16 GetDCamState( TCentreDCamCfg &tCentreDCamCfg, u8 byIndex );
    //����
    BOOL GetMatrixOnlineState();
    TTPMatrixSceneInfo* GetMatrixScneInfo();
    u16 GetCurMatrixInfo(TTPCurMatrixInfo &tTPCurMatrixInfo);
    u16 GetMatrixConfig(TTPMatrixConfig &tTPMatrixConfig);
	  /**
    * ����:	�Ͽ���UMS��CNS������
	* @param [in]  
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	��û�����ӵ�UMS/CNSʱ���ô˷����������κ�����
	*/
	u16 DisConnect() ; 
	//�˳�����
	void  ShutDownCmc( BOOL bRestart = FALSE );
	//���ӵ�TPad
	u16 ConnectTPad();

/**�пؽӿ���*/

	//�ж�Ŀ¼�Ƿ����
	BOOL ExistDir( const CString strDir );

	//����Ŀ¼
	BOOL CreateDir( CString strDir );
	//tpad��¼ʱ�û���Ϣ��¼
	u16 UpdateTpadLoginInfo();

    /**
    * ����:	����ϵͳ����� 
	* @remarks  ֻ��pad�浯��	
	*/
    void ShowKeyboard();

	//cnc����˳���֪ͨTPad��������
	u16 NotifyTPadNoReconnect();

	/**
	* ����:	��ȡ��¼���ؽ��
	* @return  u8  number
    */
	u16 GetLoginRet(TLoginRet& tLoginRet) ;

    //����
    u16 SetMatrixInOutCmd( u32 dwIn, u32 dwOut );
    u16 SaveMatrixScenceCmd( s32 dwIndex, s8* achName );
    u16 ReNameMatrixScenceCmd( u32 dwIndex, s8* achName );
    u16 DeleteMatrixScenceCmd( u32 dwIndex );
    u16 ApplyMatrixScenceCmd( s32 dwIndex );

protected:
	void UpdateAddrList();
	void UpdateAddrEntryList();
	void UpdateLevelOneGroup();

	/** ��Ӧ���ص�ַ��������Ϣ
	 *  @return 
	 */
	LRESULT UpdateAddrBook( WPARAM wParam, LPARAM lParam );

	/** ��Ӧȫ�ֵ�ַ��������Ϣ
	 *  @return 
	 */
	LRESULT OnRefreshGlobalAddrBook( WPARAM wParam, LPARAM lParam );


	afx_msg LRESULT OnRefreshConfTemplateLst(  WPARAM wParam, LPARAM lParam ) ;

	/*cns ���ػ������*/ 

	afx_msg LRESULT OnCnsEthnetInfoNotify( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnCnsRegSigServNotify( WPARAM wParam, LPARAM lParam );

	afx_msg LRESULT OnConnectCns(  WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnCnsInfoNotify( WPARAM wParam, LPARAM lParam );

	afx_msg LRESULT OnTPadLoginUserNty( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnRefreshUserLst(  WPARAM wParam, LPARAM lParam ) ;
/** @}*/


public:
	/** ��ȡ�ӿ�ָ�� */
	static CCommonInterface* GetCommIF();

	/** ���ٽӿ�ָ�� */
	void DestroyCommIF();

	~CCommonInterface(void);

private:
	CCommonInterface(void);
	static  CCommonInterface*  m_pMySelf;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HWND                 m_hRecvWnd;         // ��Ƕ������Ϣ�Ĵ���
	WNDPROC              m_wndprocOld;       // ϵͳ���ڹ���

private:
    CCnsSessionCtrlIF   *m_pCnsSession;       //cns�Ự
 
	/**cnclib ��ؽӿ�*/
	CCncConfigIF        *m_pCnsConfigCtrl;
	CCncConfCtrlIF      *m_pCnsConfCtrl;
    CUmcConfCtrlIF      *m_pUmsConfCtrl;
	CCncAddrbookIF      *m_pAddrBookCtrl;
	CCncUserCtrlIF      *m_pCnsUserCtrl;
	CCncPortDiagCtrlIF	*m_pPortDiagCtrl;
	CCncCenterCtrlIF    *m_pCenterCtrl;//����п� dyy 2015-4-1 
    /**�п���ؽӿ�*/
    CCncCenterCtrlIF    *m_pCenterCtrlIF;

	TLoginInfo           m_tLoginInfo;

	/**��ַ���������*/
	vector<TAddrItem>         m_vctLocalAddrList;       //���ص�ַ��
	vector<TAddrItem>         m_vctGlobalAddrList;      //ȫ�ֵ�ַ��
	vector<TAddrItem>         m_vctEntryList;           //���ص�ַ��������Ŀ

	
	//vector<TTPAlias>          m_vctConfTempList;        //����ģ���б�	
	TplArray<CUserFullInfo>   m_tplUserList;           ///<�û��б�
	
	TCMSConf                  m_tConfInfo;
    BOOL                      m_bVidMixOpen;           //��ǰ����ϳ��Ƿ���
    bool					  m_bIsInWBConf;
};

#define ComInterface  CCommonInterface::GetCommIF()

