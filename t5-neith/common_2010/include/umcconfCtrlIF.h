/*****************************************************************************
ģ����      : cnclib
�ļ���      : umcconfCtrlIF.h
����ļ�    : 
�ļ�ʵ�ֹ���: ��������صĽӿ�
����        : Ф��Ȼ
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2012/4/25   1.0         Ф��Ȼ      ����
******************************************************************************/

#if !defined(AFX_UMCCONFCTRLIF_H__10B44268_D175_431C_ACCA_A0A559086730__INCLUDED_)
#define AFX_UMCCONFCTRLIF_H__10B44268_D175_431C_ACCA_A0A559086730__INCLUDED_
#include "kdvdispevent.h"
#include "cncstruct.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmcConfCtrlIF:public  CKdvDispEvent   
{

public:
 
/** @defgroup  ������Ʋ��ֽӿ�
 *  @{
 */

  /**
    * ����:	��ȡ�����б�
	* @param [out]  tplConfList	 �����б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	virtual u16 GetConf(  TCMSConf &tplConf  ) const = 0;
   
  /**
    * ����:	��ȡ������cns�б�
	* @param [int]  vctConfCnsList	 CNS�б�
    * @param [out]  vctConfCnsList	 CNS�б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
    virtual u16 GetConfCnsList( vector<TCnsInfo> &vctConfCnsList ) const  = 0 ;
   
  /**
    * ����:	��ȡ��������б�
	* @param [int]  wConfID:����ID  
    * @param [out]  tplConfAudmixList	 �����б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
   virtual u16 GetConfAudmixList( TAuxMixList&tConfAudmixList ) const = 0 ;

    /**
    * ����:	��ȡ������ѯ�б�
	* @param [int]  wConfID:����ID  
    * @param [out]  tplConfPollList	 ��ѯ�б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
   //virtual u16 GetConfPollList(  TplArray<u16> &tplConfPollList ) const = 0;
 
   /**
    * ����:	����ĳcns�᳡����ĳ����
	* @param [int]  tEp	 ����ͻ᳡��Ϣ
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	virtual u16 InviteCnsReq( const TTpCallAddr &tAddr )  = 0;
 
    /**
    * ����:	���л������Ѿ����ڵ�cns�᳡����ĳ����
	* @param [int]  tEp	 ����ͻ᳡��Ϣ
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��cms->ums  evtp_CallEP_cmd  \n
                       Ӧ�ظ���ums->cms evtp_CallEP_result   \n
	                   ���ɹ�����Ӧ����ums->cms evtp_UpdateConfCnsList_Notify
	*/ 
	virtual u16 CallConfCnsReq( const TConfEpID &tEp ) = 0;

   /**
    * ����:	�Ҷϻ���
	* @param [int]  wConfID ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	virtual u16 HangupConfReq( ) = 0;
 
  /**
    * ����:	�Ҷ�ĳ�᳡
	* @param [int]  tConfEpInfo �����᳡ID �� ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks �����б�����Ȼ���ڸû᳡��ֻ�ǲ�����
	*/
	virtual u16 HangupCNSReq( const TConfEpID &tConfEpInfo ) = 0;

	 /**
    * ����:	�᳡���������
	* @param [int]  tConfEpInfo �����᳡ID �� ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks �᳡���������������Զҡ�Ļ᳡��Ϣ
	*/
	virtual u16 SetFeccConfEpInfo( const TConfEpID &tConfEpInfo ) = 0;

	/**
    * ����:	�᳡���������
	* @param [int]  tConfEpInfo �����᳡ID �� ����ID 
	* @return u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks �᳡�������������ȡԶҡ�Ļ᳡��Ϣ
	*/
	virtual u16 GetFeccConfEpInfo( TConfEpID &tConfEpInfo ) = 0;

	 /**
    * ����:	�᳡���������
	* @param [int]
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks �᳡�������������ȡ�᳡������ƵԴ
	*/
	virtual u16 ChangeFeccSource(u8 SourceId) = 0;

	/** ����   Զҡ���������PT
	*  @param[in] emDirection�� ����  emCnAction������
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    virtual u16 SetFeccCamPT( EmDirection emDirection, EmCnAction emCnAction ) = 0;

	/** ����   Զҡ�������Ұ����
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	virtual u16 SetFeccCamView( EmZoom emZoom, EmCnAction emCnAction ) = 0;

	/** ����   Զҡ�������������
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	virtual u16 SetFeccCamBright( EmPanCamBright emPanCamBright, EmCnAction emCnAction ) = 0;

		/** ����   Զҡ��������ڽ��� 
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	virtual u16 SetFeccCamFocus( EmFocus emFocus, EmCnAction emCnAction ) = 0;

	/** ����   Զҡ������Զ����ڽ��� 
	*  @param[in] 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	virtual u16 SetFeccCamAotoFocus() = 0;


  /**
    * ����:	�ӻ������Ƴ�ĳ�᳡
	* @param [int]  tConfEpInfo �����᳡ID �� ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks �����б��в����ڸû᳡
	*/
	virtual u16 RemoveCNSReq( const TConfEpID &tConfEpInfo )  = 0;

	/**
    * ����:	���÷��Ի᳡
	* @param [int]  wConfID	 ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 SetSpokeCnsReq( const TConfEpID &tConfEpInfo )    = 0;

    /**
    * ����:	����Զ��cns����
	* @param [int]  wConfID	 ����ID
    * @param [int]  bQuiet  TRUE:����������FALSE��ֹͣ����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 SetQuietCnsReq( const TConfEpID &tConfEpInfo, BOOL32 bQuiet)    = 0;


    /**
    * ����:	����Զ��cns����
	* @param [int]  wConfID	 ����ID
    * @param [int]  bMute  TRUE:����������FALSE��ֹͣ����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 SetMuteCnsReq( const TConfEpID &tConfEpInfo , BOOL32 bMute)    = 0;


     /**
    * ����:	����Զ��cns����˫��
	* @param [int]  wConfID	 ����ID
    * @param [int]  bStart  TRUE:����˫����FALSE��ֹͣ˫��
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 SetDualCnsReq( const TConfEpID &tConfEpInfo, BOOL32 bStart )    = 0; 

	/**
    * ����:	���»����б�����
	* @param [int]  tMixInfo	 �����б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 UpdateAudMixListReq( const TConfAuxMixInfo &tMixInfoList ) = 0;

	/**
    * ����:	���������б�����
	* @param [int]  tDisListOpr	 һ�������б����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 AudMixDisListOprCmd( const TDiscussListOpr &tDisListOpr ) = 0;

	/** 
	* ����:  ��������
    * @param [in	TConfAuxMixVacOpr	 
    * @return	�ɹ�����0,ʧ�ܷ��ط�0������
    * @remarks 	 */
	virtual u16 AuxMixVacOpr( const TConfAuxMixVacOpr tConfAuxMixVacOpr) = 0;

 
  /**
    * ����:	������ѯ�б�����
	* @param [int]  tTurnInfoList	 ��ѯ�б�
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 UpdatePollListReq( const TConfTurnInfo &tTurnInfoList ) = 0;


  /**
    * ����:	��������
	* @param [int]  wConfID	 ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 StartAuxMixReq( const u16 wConfID ) = 0;
 
  /**
    * ����:	ֹͣ����
	* @param [int]  wConfID	 ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 StopAuxMixReq( const u16 wConfID ) = 0;

  /**
    * ����:	������ѯ
	* @param [int]  wConfID	 ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 StartPollReq( const u16 wConfID ) = 0;


  /**
    * ����:	ֹͣ��ѯ 
	* @param [int]  wConfID	 ����ID
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  
	*/
	virtual u16 StopPollReq( const u16 wConfID ) = 0;


	//������ѯ��ͣ
	virtual u16 PollPauseCmd( const BOOL32& bIsPause ) = 0;
	virtual TTpPollStat GetPollState() = 0;

	//������ѯ�б����
	virtual u16 PollListUpdateCmd( const TTpPollListNtfy& tTpPollListNtfy ) = 0;
   		/** 
	* ����  	�����ѯ�б�
	* @param [in] 	   
	* @return  
	* @remarks 
	*/	
	virtual u16 GetPollList(  vector<u16>& vctPollList ) = 0;

    /**	����:	ѡ����ϳ��� 
	* @param [int]  tRersvesEqp	 �ϳ���
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������ 
	*/
    virtual u16 RervesBrdVmpReq( TRersvesEqpReq tRersvesEqp ) = 0;

    /**	����:	���û���ϳ� 
	* @param [int]  tVmpInfo	 ���úϳ�����Ϣ
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    virtual u16 SetBrdVmpReq( TSetVmpInfoReq tVmpInfo ) = 0;

	//��Ӧ�Ƿ�᳡���Լ������
	virtual u16 SetJoinConfInfo( TTpConfEpInfo tpConfEpInfo ) = 0;
    /**	����:	�㲥����ϳ� 
	* @param [int]  tBrdVmp	 �ϳ�����Ϣ
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    virtual u16 SetBroadcastVmpReq( TBrdVmpReq tBrdVmp ) = 0;
    /** 
	* ����  ��ȡ����ϳ�״̬
	* @return vector<TBrdVmpResNtfy> ����ϳ�״̬
	* @remarks 
	*/
	virtual const vector<TBrdVmpResNtfy>& GetBrdVmpStatus() const = 0;
    /** 
	* ����  ����ϳ�Ԥ��
	* @return  tBrdVmp  ����ϳ�״̬
	* @remarks 
	*/
    virtual u16 SaveVmpCfgReq( TBrdVmpResNtfy &tBrdVmp ) = 0;
    /** 
	* ����  ���úϳ�Ԥ��
    * @return  tEqp  ����ϳ�����Ϣ
	* @remarks 
	*/
    virtual u16 CallVmpCfgReq( TEqpInfo &tEqp ) = 0;
    /** 
	* ����  ��ȡ����ϳ�Ԥ��
	* @return  ����ϳ�Ԥ��
	* @remarks 
	*/
	virtual const TVmpMemberCfg GetCurrentVmpCfg() const = 0;

	//����ѡ��״̬
	virtual const TTPSelViewNtfy GetSelWatchStatus() const = 0;
		/** 
	* ����  ums��������
	* @return  ��������
	* @remarks 
	*/
	virtual const TTPUmsReasonInd GetUmsReason() const = 0;
	/** 
	* ����  ���������б�
	* @return  ���������б�
	* @remarks 
	*/
	virtual const TDiscussListOpr GetDiscussList() const = 0;
	virtual const TTpConfEpInfo GetJoinConfInfo() const = 0;

    /** 
	* ����  �ı����ǽģʽ
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
    virtual u16 ChangeChanModeReq( u16 wIndex, u8 byMode  ) = 0;
    /** 
	* ����  ���õ���ǽ����
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
    virtual u16 SetHduVolReq( u16 wIndex, u8 byVol ,BOOL32 bMute ) =0;
    /** 
	* ����  ֹͣ���ŵ���ǽͨ��
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
    virtual u16 StopPlayHdu( TTpHduPlayReq &tTvwInfo ) = 0;
    /** 
	* ����  ���󲥷ŵ���ǽͨ��
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
    virtual u16 PlayHduReq( const TTpHduPlayReq & tTvwInfo ) = 0 ;


	//����/��ȡ ȫ������/���� ״̬
	virtual bool IsAllQuite() = 0;
	virtual bool IsAllMute() = 0;


/** @}*/  //������Ʋ��ֽӿ�

};

#endif // !defined(AFX_CONFCTRLIF_H__10B44268_D175_431C_ACCA_A0A559086730__INCLUDED_)
