#ifndef _h_eventoutcnds_h__
#define _h_eventoutcnds_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSCNDSEVENT
{
#endif 
	
	_ev_segment( outercnds  )


	/***********************<<  ����һ������ >>********************	
 *[��Ϣ��]			 
 *   TTPCnDsData
 *[��Ϣ����]	cndsnodepool	--> cnmediadsinst
 *
 */_event(  ev_cn_media_dscreate )
  _body( EmMediaDateType, 1)
	_body( TTPCnDsData,		1 )
   _ev_end

/***********************<<  ����һ������ >>********************	
 *[��Ϣ��]			 
 *   TTPCnDsData
 *[��Ϣ����]		cndsnodepool	--> cnmediadsinst
 *
 */_event(  ev_cn_media_dsdestroy )
	_body( TTPCnDsData,		1)
   _ev_end

     /***********************<< ȡ��ds handle >>**********************	
 *[��Ϣ��]			 
 *��
 *[��Ϣ����]
 *   cnService--> cndsmgr
 */
   _event( ev_Cn_GetDSHandle_Req )
   _body( u8,		1)
   _ev_end

     /***********************<< ȡ��ds handle >>**********************	
 *[��Ϣ��]			 
 *u32_ip 
 *[��Ϣ����]
 *  cndsmgr --> cnService
 */
   _event( ev_Cn_GetDSHandle_Rsp )
   _body( u32, 1 )
   _ev_end



/***********************<< ����mt��cns�������� >>**********************	
 *[��Ϣ��]	
 *u32
 *u16 edge tpye
 *u16 RcvFrom Type
 *u16 SendTo Type
 *
 *[��Ϣ����]
 *   cnService--> cndsmgr

 *����RcvFrom �� SendTo��rtp�����Լ������RTCP����
 */
 _event( ev_Cn_Ds_Create_DsPair_Cmd )
    _body( u32, 1 )
	_body( u16, 1)
   _body ( u16    , 1    )
   _body ( u16    , 1    )
   _ev_end

   /***********************<< ����Ds >>**********************	
 *[��Ϣ��]		
 *u32 Ds Handle
 *u16 Ds Type
 *u16 Rcv From Port Type
 *u16 Snd To Port Type
 *TTPCnMediaTransPort
 *[��Ϣ����]
 *   cnService --> cndsmgr
 */
   _event( ev_Cn_Ds_Create_RTP_Ds_Cmd )
   _body( u32, 1 )
  _body( u16, 1)
  _body( u16, 1)
  _body( u16, 1)
   _ev_end

      /***********************<< ����Ds >>**********************	
 *[��Ϣ��]		
 *u32 Ds Handle
 *u16 Ds Type
 *u16 Rcv From Port Type
 *u16 Snd To Port Type
 *TTPCnMediaTransPort
 *[��Ϣ����]
 *   cnService --> cndsmgr
 */
   _event( ev_Cn_Ds_Create_RTCP_Ds_Cmd )
   _body( u32, 1 )
  _body( u16, 1)
  _body( u16, 1)
  _body( u16, 1)
   _ev_end

    /***********************<< ��������ds�ͽڵ� >>**********************	
 *[��Ϣ��]			 
 *u32 Ds Handle
 *[��Ϣ����]
 *   cnService --> cndsmgr
 */
   _event( ev_Cn_Ds_Destroy_All_Cmd )
   _body( u32, 1 )
   _body( BOOL, 1 )
   _ev_end

    /***********************<< �����ض�����ds >>**********************	
 *[��Ϣ��]			 
 *u32 Ds Handle
 *u16 Ds Type
 *[��Ϣ����]
 *   cnService --> cndsmgr
 */
   _event( ev_Cn_Ds_Destroy_Ds_Cmd )
   _body( u32, 1 )
   _body( u16, 1 )
   _ev_end

     /***********************<< �����ض�����ds��Ds�ڵ� >>**********************	
 *[��Ϣ��]			 
 *u32 Ds Handle
 *u16 Ds Type
 *[��Ϣ����]
 *   cnService --> cndsmgr
 */
   _event( ev_Cn_Ds_Destroy_Ds_And_Node_Cmd )
   _body( u32, 1 )
   _body( u16, 1 )
   _ev_end

        /***********************<< �����ض�����ds��Ds�ڵ� >>**********************	
 *[��Ϣ��]			 
 *u32 Ds Handle
 *u16 Ds Type
 *[��Ϣ����]
 *   cnService --> cndsmgr
 */
   _event( ev_Cn_Ds_Destroy_Ds_Port_Cmd )
   _body( u32, 1 )
   _body( u16, 1 )
   _ev_end

      /***********************<< �ؽ��ض�����ds >>**********************	
 *[��Ϣ��]			 
 *u32 Ds Handle
 *u16 Ds Type
 *[��Ϣ����]
 *   cnService --> cndsmgr
 */
   _event( ev_Cn_Ds_Rebuild_Ds_Cmd )
   _body( u32, 1 )
   _body( u16, 1 )
   _ev_end

  /***********************<< ��ʾ�ض�����ds >>**********************	
 *[��Ϣ��]			 
 *u32 Ds Handle
 *[��Ϣ����]
 *   cnService --> cndsmgr
 */
   _event( ev_Cn_Ds_Show_DsNode_Cmd )
   _body( u32, 1 )
   _body( EmTPDsNode, 1 )
   _ev_end

/***********************<< ����netbuf >>**********************	
 *[��Ϣ��]			 
 *u32  Handle
 *u16 Ds Type
 *TTPCnRSParam
 *TTPCnNetBufPara 
 *[��Ϣ����]
 *   cnService --> cndsmgr
 * NB ��dst �˿�Ϊ�Զ�����
 */
   _event( ev_Cn_Nb_Create_Cmd )
   _body( u32, 1 )
   _body( u16, 1 )
   _body( u16, 1 )
   _body( TTPCnRSParam, 1 )	 
   _body( TTPCnNetBufPara, 1 )	 
   _ev_end
 
   /***********************<< ���������� >>**********************	
 *[��Ϣ��]			 
 *EmCnAudioMixID ����������
 *u16
 *[��Ϣ����]
 *   cnService --> cnaudiomixinst
 */
   _event( ev_Cn_AMix_Create )
   _body( EmCnAudioMixID, 1 )
   _body( u16, 1 )
   _ev_end

      /***********************<< ���ٻ����� >>**********************	
 *[��Ϣ��]			 
 *EmCnAudioMixID ����������
 *u16
 *[��Ϣ����]
 *   cnService --> cnaudiomixinst
 */  
   _event( ev_Cn_AMix_Destroy )
   _body( EmCnAudioMixID, 1 )
   _body( u16, 1 )
   _ev_end

   /***********************<< �������ͨ�� >>**********************	
 *[��Ϣ��]			 
 *EmCnAudioMixID ����������
 *u8
 *TTPMixerChannelParam
 *[��Ϣ����]
 *   cnService --> cnaudiomixinst
 */
   _event( ev_Cn_AMix_CreateChan_Cmd )
   _body( EmCnAudioMixID, 1 )
   _body( u8, 1 )
   _body( TTPMixerChannelParam, 1 )
   _ev_end

      /***********************<< ɾ������ͨ�� >>**********************	
 *[��Ϣ��]			 
 *EmCnAudioMixID ����������
 *u8
 *[��Ϣ����]
 *   cnService --> cnaudiomixinst
 */
   _event( ev_Cn_AMix_DestroyChan_Cmd )
   _body( EmCnAudioMixID, 1 )
   _body( u8, 1 )
   _ev_end


      /***********************<< ����Nģʽ >>**********************	
 *[��Ϣ��]			 
 *EmCnAudioMixID
 *TTPNetAddress  LocalAddr
 *TTPNetAddress  LocalRtcpAddr
 *TTPNetAddress DstNetAddr
 *[��Ϣ����]
 *   cnService --> cnaudiomixinst
 */
   _event( ev_Cn_AMix_SetNMode_Cmd )
   _body( EmCnAudioMixID, 1 )
   _body( TTPNetAddress, 1 )
   _body( TTPNetAddress, 1 )
   _body( TTPNetAddress, 1 )
   _ev_end

      /***********************<< ��ʼ���� >>**********************	
 *[��Ϣ��]			 
 *EmCnAudioMixID
 *[��Ϣ����]
 *   cnService --> cnaudiomixinst
 */
   _event( ev_Cn_AMix_StartMix_Cmd)
   _body( EmCnAudioMixID, 1 )
   _ev_end

        /***********************<< ֹͣ���� >>**********************	
 *[��Ϣ��]			 
 *u32
 *[��Ϣ����]
 *   cnService --> cnaudiomixinst
 */
   _event( ev_Cn_AMix_StopMix_Cmd)
   _body( EmCnAudioMixID, 1 )
   _ev_end

  /***********************<< �����ص�ͨ�� >>**********************	
 *[��Ϣ��]			 
 *EmCnAudioMixID
 *u8
 *[��Ϣ����]
 *   cnaudiomixinst --> cnservice
 */
   _event( ev_Cn_AMix_Channel_CBPos_Nty)
   _body( EmCnAudioMixID, 1 )
   _body( u8, 1 )
   _ev_end

   /*********˫��ͨ�������ɹ�֪ͨ**************************/
   //�������Ƿ���ͨ��
   /*[��Ϣ����]
   *  cnservice --> cnc
   */
   _event( ev_Cn_DualChanConnect_Nty )
   _body( BOOL, 1)
   _ev_end
   
   /*********˫��ͨ���ͷųɹ�֪ͨ**************************/
   /*[��Ϣ��]��
    * BOOL �Ƿ���ͨ��
	* EmTPChannelReason �Ͽ�ԭ��
   /*[��Ϣ����]
   *  cnservice --> cnc
   */
   _event( ev_Cn_DualChanDisConnect_Nty )
   _body( BOOL, 1)
   _body( EmTPChannelReason, 1)
   _ev_end
   
  /*********��ȡPad�ؼ�֡�Ķ�ʱ��**************************/
   //[��Ϣ��]
   /*��
   *[��Ϣ����]
   *  cnservice --> cnservice
   */
   _event(  ev_CnPadKeyFrame_Timer )
   _ev_end

   /*********���PC Ds**************************/
   //[��Ϣ��]
   /*PC IP��u32_ip
   *[��Ϣ����]
   *  cnservice --> cnservice
   */
   _event(  ev_CnDsAddRcvToPC_Cmd )
   _body( u32_ip, 1)
   _ev_end

   /*********cndsע��cn�Ķ�ʱ��**************************/
   //[��Ϣ��]
   /*��
   *[��Ϣ����]
   *  cndsmgr --> cndsmgr
   */
   _event(  ev_CnDsRegCn_timer )
  _ev_end

   /*********cndsע��cn�ĳ�ʱ��ʱ��**************************/
   //[��Ϣ��]
   /*��
   *[��Ϣ����]
   *  cndsmgr --> cndsmgr
   */
  _event(  ev_CnDsRegCn_timer_Out )
  _ev_end

   /*********cnds����ע��cn**************************/
   //[��Ϣ��]
   /*��
   *[��Ϣ����]
   *  cndsmgr --> cnservice
   */
  _event(  ev_CnDsregcn_req )
  _body( u32_ip, 1 )
  _ev_end
  
  /*********cnds����ע��cn�Ļظ�**************************/
   //[��Ϣ��]
   /*cns IP��u32_ip
   *[��Ϣ����]
   *  cnservice -->cndsmgr 
   */
  _event(  ev_CnDsregcn_Rsp )
  _body( u32_ip, 1)
  _ev_end


   /*********cnds����ע��cn�Ļظ�**************************/
   //[��Ϣ��]
   /*u32:handle
   u16: type
	TTPCnMediaTransPort
   *[��Ϣ����]
   *  cnservice -->cndsmgr 
   */
  _event( ev_Cn_Ds_Add_Port_Cmd )
  _body( u32, 1 )
  _body( u16, 1 )
  _body ( TTPCnMediaTransPort    , 1    )
   _ev_end

  
	  /***********************<< ����Ds >>**********************	
 *[��Ϣ��]	
 *u32 Ds src Handle
 *u32 Ds dest Handle
 *u16 Ds Type
 *u16 Rcv From Port Type
 *u16 Snd To Port Type
 *TTPCnMediaTransPort
 *[��Ϣ����]
 *   cnService --> cndsmgr
 */
   _event( ev_Cn_Create_Debug_RTP_Ds_Cmd )
   _body( u32, 1 )
    _body( u32, 1 )
  _body( u32, 1 )
  _body( u16, 1)
  _body( u16, 1)
  _body( u16, 1)
   _ev_end
   
   	  /***********************<< ����Ds >>**********************	
 *[��Ϣ��]		
 *u32 Ds src Handle
 *u32 Ds dest Handle
 *u16 Ds Type
 *u16 Rcv From Port Type
 *u16 Snd To Port Type
 *TTPCnMediaTransPort
 *[��Ϣ����]
 *   cnService --> cndsmgr
 */
   _event( ev_Cn_Create_Debug_RTCP_Ds_Cmd )
   _body( u32, 1 )
   _body( u32, 1 )
  _body( u32, 1 )
  _body( u16, 1)
  _body( u16, 1)
  _body( u16, 1)
   _ev_end

      	  /***********************<< ����Ds >>**********************	
 *[��Ϣ��]		
 *u32 Ds src Handle
 *u32 Ds dest Handle
 *u16 Ds Type
 *u16 Rcv From Port Type
 *u16 Snd To Port Type
 *TTPCnMediaTransPort
 *[��Ϣ����]
 *   cnService --> cndsmgr
 */
   _event( ev_Cn_Trans_Ds_Cmd )
   _body( u16, 1 ) 
   _body( TTPCnMediaTransPort, 2 )
   _ev_end


   _event( ev_Cn_DestryTrans_Ds_Cmd )
   _body( u16, 1 )  
   _body( u8, 1 )
   _ev_end

   _event( ev_Cn_Trans_Ds_Ind )
   _body( BOOL, 1 )
   _body( u8, 1 )
   _ev_end

   _event( ev_Cn_ManualSpeaker_Nty)
   _body( EmCnAudioMixID, 1 )
   _body( u8, 1 )
   _ev_end

   _event( ev_Cn_ManualSpeaker_Ind)
   _body( EmCnAudioMixID, 1 )
   _body( u8, 1 )
   _ev_end

   _event( ev_Cn_ManualAudSp_Nty)   
   _body( u8, 1 )
   _ev_end

   /***********************<< ����Ds >>**********************	
   *[��Ϣ��]		
   *u32 Ds src Handle
   *u32 Ds dest Handle
   *u16 Ds Type
   *u16 Rcv From Port Type
   *u16 Snd To Port Type
   *TTPCnMediaTransPort
   *[��Ϣ����]
   *   cnService --> cndsmgr
   */
   _event( ev_Cn_VirRemotTrans_Ds_Cmd )
   _body( u16, 1 ) 
   _body( TTPCnMediaTransPort, 2 )
   _ev_end  
   
   _event( ev_Cn_VirRemotTrans_Ds_Ind )
   _body( BOOL, 1 ) 
   _body( u8, 1 )
   _ev_end
   
   _event( ev_Cn_DestryDTrans_Ds_Cmd )
   _body( u16, 1 )   
   _body( u8, 1 )
   _ev_end
   
   /***********************<< ���ն�����ؼ�֡������ >>********************	
   *[��Ϣ��]
   * TTpCodecComponent
   *[��Ϣ����]
   *  cns	  -> mt
   */
   _event(  ev_tppKeyFrame_Req )
   _body( TTpCodecComponent, 1)
   _body( u8, 1)
   _ev_end
   //˫��ɾ������
   _event( ev_TppDestroyDual_Cmd )
   _body( u8, 1 )
   _ev_end
   
   //ת��˫������
   _event( ev_TppTransDual_Cmd )
   _body( TTPCnMediaTransPort, 2 )
   _ev_end
   
   _event( ev_Cn_TransDual_Ind )
   _body( BOOL, 1 ) 
   _body( u8, 1)
  _ev_end

   /***********************<< ��������ԱȨ�޵����� >>********************	
   *[��Ϣ��]
   * TTpSuperUser
   *[��Ϣ����]
   *  cnc	  -> cns
   */
   _event(  ev_tppSuperadmin_Cmd )
   _body( TTpSuperUser, 1 )
   _ev_end

   _event(  ev_tppSuperadmin_Ind )
   _body( TTpSuperUser, 1 )
   _body( BOOL, 1 )
   _ev_end

   _event(  ev_tppSuperadmin_Nty )
   _body( TTpSuperUser, 1 )
   _ev_end

   /***********************<< ��������Աһ������������ >>********************	
   *[��Ϣ��]
   * TTpSuperUser
   *[��Ϣ����]
   *  cnc	  -> cns
   */
   _event(  ev_tppSuperadminClear_Cmd )
   _body( BOOL, 1 )
   _ev_end

   _event(  ev_tppSuperadminClear_Ind )
   _body( BOOL, 1 )
   _ev_end

   /***********************<< �������е����������� >>********************	
   *[��Ϣ��]
   * u8:������С
   *[��Ϣ����]
   *  cnc	  -> cns
   */
   _event(  ev_tppSetAudioVolumAll_Cmd )
   _body( u8, 1 )
   _ev_end

  /***********************<<  ������Ƶ�����������ƻ�Ӧ  >>********************	
  *[��Ϣ��]
  *u8:������С
  *BOOL
  *[��Ϣ����]	cns	-->  cnc
  *
  */
  _event(  ev_tppSetAudioVolumAll_Ind )
  _body ( u8  , 1  )	
  _body ( BOOL  , 1  )	
  _ev_end

  /***********************<< ��Ƶ�б��֪ >>********************	
  *[��Ϣ��]
  * TTpSuperUser
  *[��Ϣ����]
  *  cnc	  -> cns
  */
  _event(  ev_tppMatrixinfo_Nty )
  _body( TTPMatrixInfo, 1 )
  _ev_end
  /***********************<< ��ƵԴ�л�������˫ >>********************	
  *[��Ϣ��]
  * TTpSuperUser
  *[��Ϣ����]
  *  cnc	  -> cns
  */
  _event(  ev_tppChangeMatrix_Cmd )
  _body( u8, 1 )
  _body( u8, 1 )
  _ev_end
  /***********************<< ��Ƶ�б��֪ >>********************	
  *[��Ϣ��]
  * TTpSuperUser
  *[��Ϣ����]
  *  cnc	  -> cns
  */
  _event(  ev_tppChangeMatrix_Ind )
  _body( u8, 1 )
  _body( BOOL, 1 )
  _ev_end  



#ifndef _MakeTpEventDescription_
		_ev_segment_end( outercnds )
};
#endif
#endif