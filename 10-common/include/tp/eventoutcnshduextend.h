#ifndef _h_eventoutcnshduextend_h__
#define _h_eventoutcnshduextend_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmUMSCNSHDUEVENT
{
#endif 
	
	_ev_segment( outercnshduextend  )


/***********************<< ����ǽ֪ͨ >>********************	
 *[��Ϣ��]
 * TTpHduPlanPackData 
 *[��Ϣ����]
 *  cnc <- cns, cns	 <-  ums
*/
_event(  ev_TpUMS_CNS_HduPlan_Nty  )
_body( TTpHduPlanPackData ,1 )			
_ev_end

/***********************<< ����ǽ���� >>********************	
 *[��Ϣ��]
 * TPAHduPlayReq 
 *[��Ϣ����]
 *  cnc -> cns, cns	 ->  ums
*/
_event(  ev_TpCNS_UMS_HduPlay_Req  )
_body( TTpHduPlayReq ,1 )			
_ev_end

/***********************<< ��������ǽ��Ӧ >>********************	
 *[��Ϣ��]
 * TPAHduPlayReq 
 * EmCnsHduPlayNackReason
 *[��Ϣ����]
 *  cnc <- cns, cns	 <-  ums
*/
_event(  ev_TpUMS_CNS_HduPlay_Ind  )
_body( TTpHduBaseInfo ,1 )	
_body( EmCnsHduPlayNackReason ,1 )		
_ev_end

/***********************<< ֹͣѡ�е���ǽ >>********************	
 *[��Ϣ��]
 * TPAHduPlayReq 
 *[��Ϣ����]
 *  cnc -> cns, cns	 ->  ums
*/
_event(  ev_TpCNS_UMS_HduStopPlay_Req  )
_body( TTpHduPlayReq ,1 )			
_ev_end

/***********************<< ֹͣѡ�е���ǽ��Ӧ >>********************	
 *[��Ϣ��]
 * TTpHduBaseInfo 
 *[��Ϣ����]
 *  cnc <- cns, cns	 <-  ums
*/
_event(  ev_TpUMS_CNS_HduStopPlay_Ind  )
_body( TTpHduBaseInfo ,1 )	
_body( u16 ,1 )		//0:�ɹ�����0��������
_ev_end

/***********************<< ֹͣȫ������ǽ >>********************	
 *[��Ϣ��]
 * TTpHduSetVolInfo 
 *[��Ϣ����]
 *  cnc -> cns, cns	 ->  ums
*/
_event(  ev_TpCNS_UMS_HduAllStopPlay_Req  )			
_ev_end

/***********************<< ���õ���ǽvol >>********************	
 *[��Ϣ��]
 * TPAHduPlayReq 
 *[��Ϣ����]
 *  cnc -> cns, cns	 ->  ums
*/
_event(  ev_TpCNS_UMS_HduSetVol_Req  )
_body( TTpHduSetVolInfo ,1 )			
_ev_end

/***********************<< ���õ���ǽvol��Ӧ >>********************	
 *[��Ϣ��]
 * TTpHduSetVolInfo 
 * EmCnsHduSetVolRes
 *[��Ϣ����]
 *  cnc <- cns, cns	 <-  ums
*/
_event(  ev_TpUMS_CNS_HduSetVol_Ind  )
_body( TTpHduSetVolInfo ,1 )	
_body( EmCnsHduSetVolRes ,1 )		//0:�ɹ�����0��������
_ev_end

/***********************<< ����ǽģʽ�ı� >>********************	
 *[��Ϣ��]
 * TTpHduChanModeSetInfo 
 *[��Ϣ����]
 *  cnc -> cns, cns	 ->  ums
*/
_event(  ev_TpHduChangeChanMode_Req  )
_body( TTpHduChanModeSetInfo ,1 )			
_ev_end

/***********************<< ����ǽģʽ�ı��Ӧ >>********************	
 *[��Ϣ��]
 * TTpHduChanModeSetInfo 
 * EmCnsHduChangeChanModeRes
 *[��Ϣ����]
 *  cnc <- cns, cns	 <-  ums
*/
_event(  ev_TpHduChangeChanMode_Ind  )
_body( TTpHduChanModeSetInfo ,1 )
_body( EmCnsHduChangeChanModeRes ,1 )			
_ev_end

/***********************<<����ͼ����ʾ>>********************	
 *[��Ϣ��]
 
 *[��Ϣ����]
 *  cnc -> cns
*/
_event(  ev_TpIconSwitch_Cmd  )
_body( BOOL ,1 )		
_ev_end

/***********************<< ����ͼ���Ӧ >>********************	
 *[��Ϣ��]
 
 *[��Ϣ����]
 *  cns -> cnc
*/
_event(  ev_TpIconSwitch_Ind  )
_body( BOOL ,1 )	
_body( BOOL ,1 )	
_ev_end

/***********************<<���û���ü�  >>************************
	*[��Ϣ��]

	*[��Ϣ����]
	*  cns	   -> cnmp
	*/
	_event( ev_TppSetVidCutLine )
	_body ( TTpVidCutLine, 1    )	
	_ev_end

	
	/***********************<<����ͼ��  >>************************
	*[��Ϣ��]

	*[��Ϣ����]
	*  cns	   -> cnmp
	*/
	_event( ev_TppSetIcon )
	_body ( TTpIconInfo, 1    )	
	_ev_end

		/***********************<<������Ƶ�������  >>************************
	*[��Ϣ��]

	*[��Ϣ����]
	*  cns	   -> cnmp
	*/
	_event( ev_TppSetMixType_Nty )
	_body ( TTpAudMix, 1    )
	_body ( u8, 1 )
	_ev_end

	
		/***********************<<������Ƶ�������  >>************************
	*[��Ϣ��]

	*[��Ϣ����]
	*  cnc	   -> cns
	*/
	_event( ev_TppSetMixType_Cmd )
	_body ( EmAudMixType, 1    )	
	_body ( u8, 1 )
	_ev_end

		/***********************<<������Ƶ������ͻ�Ӧ  >>************************
	*[��Ϣ��]

	*[��Ϣ����]
	*  cns	   -> cnc
	*/
	_event( ev_TppSetMixType_Ind )
	_body ( EmAudMixType, 1    )	
	_body ( u8, 1 )
	_ev_end

		/***********************<<���ñ�����������  >>************************
	*[��Ϣ��]

	*[��Ϣ����]
	*  cnc	   -> cns
	*/
	_event( ev_TppSetLocalAudExtend_Cmd )
	_body ( EmAudExtend, 1    )	
	_body ( u8, 1 )
	_ev_end

		/***********************<<���ñ���������Ӧ  >>************************
	*[��Ϣ��]

	*[��Ϣ����]
	*  cns	   -> cnc
	*/
	_event( ev_TppSetLocalAudExtend_Ind )
	_body ( EmAudExtend, 1    )	
	_body ( u8, 1 )
	_ev_end

		/***********************<<���ñ�������֪ͨ  >>************************
	*[��Ϣ��]

	*[��Ϣ����]
	*  cns	   -> cnmp
	*/
	_event( ev_TppSetLocalAudExtend_Nty )
	_body ( BOOL, 1    )	
	_body ( u8, 1 )
	_ev_end

	
	/***********************<< �������������  >>********************	
	*[��Ϣ����]	CNC->CNS,CNS	-->  UMS
	*
	*/
	_event(  evConfRollCallUpdate_Cmd )
	_body ( TTpConfRollCallInfo , 1 )	
	_ev_end
	
	
	
	/***********************<< ���������������Ӧ  >>********************	
	*[��Ϣ����]	UMS	-->  CNS, CNS->CNC
	*
	*/
	_event(  evConfRollCallUpdate_Ind )	
	_body ( TTpConfRollCallInfo , 1 )
	_ev_end
	
	
	
	
	/***********************<< ������һ������  >>********************	
	*[��Ϣ����]	CNC->CNS, CNS	-->  UMS
	*
	*/
	_event(  evConfRollCallNextEp_Cmd )
	_body ( TTpRollCallNextEpInfo , 1 )	
	_ev_end
	
	
	
	/***********************<< ������һ����Ӧ  >>********************	
	*[��Ϣ����]	UMS	-->  CNS, CNS->CNC
	*
	*/
	_event(  evConfRollCallNextEp_Ind )
	_body ( TTpRollCallNextEpInfo , 1 )	
	_ev_end

	
	/***********************<< �������������֪ͨ  >>********************	
	*[��Ϣ����]	UMS	-->  CNS, CNS->CNC
	*
	*/
	_event(  evConfRollCallUpdate_Nty )
	_body ( TTpConfRollCallInfo , 1 )	
_ev_end

// �������
/***********************<<  �������ܻ������������ƻ�����ֹͣ����cmd��Ϣ���� >>********************	
*[��Ϣ����]	CNS	-->  UMS, CNS -->CNC
��ע���������ܻ�����ֹͣ�����������Σ�����TUmsAudMixInfo�����m_tMixList�ֶ�
*
*/
_event(  evConfAudMixMode_Cmd )
_body ( TTpAudMixInfo  , 1  )
_ev_end

/***********************<<  �������ܻ������������ƻ�����ֹͣ����ind��Ϣ���� >>********************	
*[��Ϣ����]	UMS	-->  CNS, CNC -->CNS
*
*/
_event(  evConfAudMixMode_Ind ) 
_body ( TTpAudMixModeCmdRes  , 1  )
_ev_end

/***********************<< �޸Ļ�����Ա�б�cmd��Ϣ���ǻ���ģʽҲ��Ч >>********************	
*[��Ϣ����]	CNS	-->  UMS, CNS -->CNC
*
*/
_event(  evConfAudMixList_Cmd ) 
_body ( TTpAudMixListCmd  , 1  )
_ev_end

/***********************<<  �޸Ļ�����Ա�б�cmd��Ϣ��Ӧ >>********************	
*[��Ϣ����]	UMS	-->  CNS, CNC -->CNS
*
*/
_event(  evConfAudMixList_Ind ) 
_body ( TTpAudMixListCmdRes  , 1  )
_ev_end


/***********************<<  �������֪ͨ��Ϣ >>********************	
*[��Ϣ����]	UMS	-->  CNS, CNC -->CNS
*
*/
_event(  evtpConfAudMixMode_Nty ) 
_body ( TTpAudMixInfo  , 1  )
_ev_end

/***********************<< ��������µ����б�  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  evConfRollCallUpdataList_Cmd )
_body ( TTpUpdataRollCallList , 1 )	
_ev_end



/***********************<< ��������µ����б��Ӧ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  evConfRollCallUpdataList_Ind )
_body ( TTpUpdataRollCallListRes , 1 )	
_ev_end



/***********************<<  ��ϯ���µ�������� >>********************	
*[��Ϣ����] CNS->UMS
*
*/
_event(  evtpRollUpdate_PresentState )
_body ( TTpRollCallPresentStateMsg  , 1  )	
_ev_end


/***********************<<  ��������� ͬ�� >>********************	
*[��Ϣ����] UMS->CNS
*
*/
_event(  evtpRoll_PresentState_Nty )
_body ( TTpRollCallPresentStateMsg  , 1  )	
_ev_end

/***********************<<���û���ü�����  >>************************
*[��Ϣ��]
*[��Ϣ����]
*  cnc	   -> cns
*/
_event( ev_TppSetVidCutLine_Cmd )
_body ( BOOL, 1    )	
_ev_end

/***********************<<���û���ü���Ӧ  >>************************
*[��Ϣ��]
*[��Ϣ����]
*  cnc	   -> cns
*/
_event( ev_TppSetVidCutLine_Ind )
_body ( BOOL, 1    )
_body ( BOOL, 1    )	
_ev_end

/***********************<<Tptoolsץ������  >>************************
*[��Ϣ��]
*[��Ϣ����]
*  cnc	   -> cns
*/
_event( ev_TppToolgetPak_Cmd )
_body ( BOOL, 1    )	
_ev_end
/***********************<<ץ���ܾ�����  >>************************
*[��Ϣ��]
*[��Ϣ����]
*  cns	   -> cnc
*/
_event( ev_TppRefuseLogin_Nty )	
_body(u32_ip, 1)
_ev_end
/***********************<<���������÷�����ϯ  >>************************
*[��Ϣ��]
*[��Ϣ����]
*  cnc	   -> cns
*/
_event(  ev_CnSetSayState )
_body( u8, 1 )
_ev_end
/***********************<<�Ƿ��ڻ���״̬֪ͨ  >>************************
*[��Ϣ��]
*[��Ϣ����]
*  cns	   -> cnc
*/
_event(  ev_EpInAudMix_Nty )
_body( BOOL32, 1 )
_ev_end
/***********************<<����ͼ�����  >>************************
*[��Ϣ��]
*[��Ϣ����]
*  cnc	   -> cns
*/
_event(  ev_CnSetIconCfg_cmd )
_body( EmIconType, 1 )
_ev_end
/***********************<<�ر�ͼ��  >>************************
*[��Ϣ��]
*[��Ϣ����]
*  cnc	   -> cns
*/
_event(  ev_CnCloseIconCfg_cmd )
_body( EmIconType, 1 )
_ev_end

/***********************<<��ѯͼ��  >>************************
*[��Ϣ��]
*[��Ϣ����]
*  cnc	   -> cns
*/
_event(  ev_CnIconShow )
_ev_end

/***********************<< ���Ӽ��ܷ�����������������  >>********************	
  *[��Ϣ��]
  *TTpQtEncryptCfg ���Ӽ�����Ϣ
  *[��Ϣ����]	  CNC	-->  CNS
  *
  */
  _event( ev_tppSetQtEncryptInfo_Cmd )
  _body( TTpQtEncryptCfg, 1 )
  _ev_end

  /***********************<< ���Ӽ��ܷ�������������֪ͨ  >>********************	
  *[��Ϣ��]
  *TTpQtEncryptCfg ���Ӽ�����Ϣ
  *[��Ϣ����]	  CNC	-->  CNS
  *
  */
  _event( ev_tppSetQtEncryptInfo_Nty )
  _body( TTpQtEncryptCfg, 1 )
  _ev_end

   /***********************<< ���Ӽ��ܷ���������������Ӧ  >>********************	
  *[��Ϣ��]
  *TTpQtEncryptCfg ���Ӽ�����Ϣ
  *BOOL ���Ӽ�����Ϣ�Ƿ�д�������ļ�
  *[��Ϣ����]	  CNS	-->  CNC
  *
  */
  _event( ev_tppSetQtEncryptInfo_Ind )
  _body( TTpQtEncryptCfg, 1 )
  _body( BOOL, 1 )
  _body( u8, 1 )
  _ev_end

  /***********************<< ���᳡����323�ն���ƵԴ��cnc  >>*****************
  *[��Ϣ��]
  *TConfVidFeccInfo ���᳡��ƵԴ��Ϣ
  *[��Ϣ����] CNS-->CNC
  *
  */
  _event( ev_SendFeccVidSrcInfo_Nty )
  _body( TConfVidFeccInfo, 1 )
  _ev_end

     /***********************<< ����ϳ�ʱ����С����ߴ�  >>********************	
  *[��Ϣ��]
  *EmMeetingRoomType С����ߴ�
  *[��Ϣ����]     cns	-->	 cnmp
  */
  _event( ev_CnSetMeetingRoomType_Cmd )
  _body( EmTpVideoResolution, 1 )
  _ev_end

   /***********************<< �����������Ϣ����֪ͨ  >>********************	
  *[��Ϣ��]
  *TTPMatrixServerInfo �����������Ϣ
  *[��Ϣ����]	 cns   -->   tptools
  */
  _event( ev_CnSetMatrixServerInfo_Nty )
  _body( TTPMatrixServerInfo, 1 )
  _ev_end

     /***********************<< �����������Ϣ��������  >>********************	
  *[��Ϣ��]
  *TTPMatrixServerInfo �����������Ϣ
  *[��Ϣ����]	tptools   -->   cns
  */
  _event( ev_CnSetMatrixServerInfo_Cmd )
  _body( TTPMatrixServerInfo, 1 )
  _ev_end

     /***********************<< �����������Ϣ���û�Ӧ  >>********************	
  *[��Ϣ��]
  *TTPMatrixServerInfo �����������Ϣ
  *[��Ϣ����]	cns   -->   tptools
  */
  _event( ev_CnSetMatrixServerInfo_Ind )
  _body( TTPMatrixServerInfo, 1 )
  _body( BOOL, 1 )
  _ev_end

       /***********************<< ������˷翪������֪ͨ  >>********************	
  *[��Ϣ��]
  *TTPDesktopMicInfo ������˷���Ϣ
  *[��Ϣ����]	cns   -->   tptools
  */
  _event( ev_CnSetDesktopMicInfo_Nty )
  _body( BOOL, 1 )
  _ev_end

       /***********************<< ������˷翪����������  >>********************	
  *[��Ϣ��]
  *TTPDesktopMicInfo ������˷���Ϣ
  *[��Ϣ����]	tptools   -->   cns
  */
  _event( ev_CnSetDesktopMicInfo_Cmd )
  _body( BOOL, 1 )
  _ev_end
         /***********************<< ������˷翪�����û�Ӧ  >>********************	
  *[��Ϣ��]   
  *TTPDesktopMicInfo ������˷���Ϣ
  *[��Ϣ����]	cns   -->   tptools
  */
  _event( ev_CnSetDesktopMicInfo_Ind )
  _body( BOOL, 1 )
  _body( BOOL, 1 )
  _ev_end

  /***********************<< ����Telnet��������  >>********************	
  *[��Ϣ��]   
  *
  *[��Ϣ����]	cns   -->   tptools
  */
  _event( ev_CnSetTelnet_Req )
  _body( TTPTelnetInfo, 1 ) 
  _ev_end
  
  /***********************<< ����Telnet�����Ӧ  >>********************	
  *[��Ϣ��]   
  *
  *[��Ϣ����]	cns   -->   tptools
  */
  _event( ev_CnSetTelnet_Rsp )
  _body( TTPTelnetInfo, 1 )
  _body( BOOL, 1 ) 
  _ev_end
  
  /***********************<< ����FTP��������  >>********************	
  *[��Ϣ��]   
  *
  *[��Ϣ����]	cns   -->   tptools
  */
  _event( ev_CnSetFtp_Req )
  _body( TTPFtpInfo, 1 ) 
  _ev_end
  
  /***********************<< ����FTP�����Ӧ  >>********************	
  *[��Ϣ��]   
  *
  *[��Ϣ����]	cns   -->   tptools
  */
  _event( ev_CnSetFtp_Rsp )
  _body( TTPFtpInfo, 1 )
  _body( BOOL, 1 ) 
  _ev_end
  
  _event(  ev_CnCfgSetTelnet_Cmd )
  _body  ( TTPTelnetInfo, 1 )
  _ev_end
  
  _event(  ev_CnCfgSetTelnet_Nty )
  _body ( TTPTelnetInfo, 1 )
  _ev_end

  _event(  ev_CnTelnetInfo_Nty )
  _body  ( TTPTelnetInfo, 1 )
  _ev_end

  _event(  ev_CnFtpInfo_Nty )
  _body  ( TTPFtpInfo, 1 )
  _ev_end

    /***********************<< ����˫������Ϣ >>********************** 
*[��Ϣ��]
+TTPEthnetInfo		CNS����������Ϣ
*[��Ϣ����]
*  cnc	  -> cns
*/
  _event( ev_CnCfgWEthnet_Cmd )
  _body(TTPWEthnetInfo, 1 )
  _body(EmTpIpNameNatSyn, 1 )
  _ev_end

  _event( ev_CnCfgWEthnet_Rsp )
  _body(TTPWEthnetInfo, 1 )
  _body(EmTpIpNameNatSyn, 1 )
  _body( BOOL, 1 )
  _ev_end

  _event( ev_CnCfgWEthnet_Nty )
  _body(TTPWEthnetInfo, 1 ) 
  _ev_end
   //�����ڲ�ʹ��
  _event( ev_CnCfgEthnet1_Cmd )
  _body(TTPEthnetInfo, 1 )
  _body(EmTpIpNameNatSyn, 1 )
  _ev_end

  _event( ev_CnCfgEthState_Nty )
  _body(EmEthState, 1 )
  _ev_end

  _event( ev_CnSetMicPower_Cmd )
  _body(u8, 1 )
  _body(BOOL, 1 )
  _ev_end

  _event( ev_CnSetMicPower_Rsp )
  _body(u8, 1 )
  _body(BOOL, 1 )
  _body(BOOL, 1 )
  _ev_end

  _event( ev_CnMicPower_Nty )
  _body(TTpMicState, 1 )
  _ev_end

  _event( ev_CnMicPowerStyle_Nty )
  _body(TTpMicState, 1 )
  _ev_end

  _event( ev_CnMicPowerIner_Nty )
  _body(TTpMicState, 1 )
  _ev_end

  /***********************<< ֪ͨ323�ն���ƵԴ��cnc  >>*****************
  *[��Ϣ��]
  *TConfVidFeccInfo ���᳡��ƵԴ��Ϣ
  *[��Ϣ����] CNS-->CNC
  *
  */
  _event( ev_SendFeccVidSrcInfo_Ind )
  _body( TConfVidFeccInfo, 1 )
  _ev_end

  /***********************<< �޸ľ������� >>********************	
  *[��Ϣ��]
  * TTpSuperUser
  *[��Ϣ����]
  *  cnc	  -> cns
  */
  _event(  ev_tppChangeMatrixName_Cmd )
  _body( TTPMatrixName, 1 )
  _ev_end
  /***********************<< �޸ľ������ֻظ� >>********************	
  *[��Ϣ��]
  * TTpSuperUser
  *[��Ϣ����]
  *  cnc	  -> cns
  */
  _event(  ev_tppChangeMatrixName_Ind )
  _body( TTPMatrixName, 1 )
  _body( BOOL, 1 )
  _ev_end
  /***********************<< ���÷��ͶԶ�����ƵԴֻ�� >>********************	
  *[��Ϣ��]
  * TTpSuperUser
  *[��Ϣ����]
  *  cnc	  -> cns
  */
  _event(  ev_tppSetMainSrc_Cmd )  
  _body( u8, 1 )
  _ev_end
  /***********************<< ���÷��ͶԶ�����ƵԴֻ�� �ظ�>>********************	
  *[��Ϣ��]
  * TTpSuperUser
  *[��Ϣ����]
  *  cnc	  -> cns
  */
  _event(  ev_tppSetMainSrc_Ind )  
  _body( u8, 1 )
  _body( BOOL, 1 )
  _ev_end

  /***********************<< ���û��Ա��أ������ú�ȡ����>>********************	
   *[��Ϣ��]
   * TTpSuperUser
   *[��Ϣ����]
   *  cnc	  -> cns
   */
   _event(  ev_tppSetViewSrc_Cmd ) 
   _body( TTPSlectView, 1 ) 
   _ev_end
         /***********************<< ���û��Ա��ػظ�>>********************	
   *[��Ϣ��]
   * TTpSuperUser
   *[��Ϣ����]
   *  cnc	  -> cns
   */
   _event(  ev_tppSetViewSrc_Ind ) 
   _body( TTPSlectView, 1 )
   _body( BOOL, 1 )
   _ev_end

            /***********************<< SDK��Ϣ֪ͨcnmp>>********************	
   *[��Ϣ��]
   * TTpSuperUser
   *[��Ϣ����]
   *  cnc	  -> cns
   */
   _event(  ev_tppSdkVersion_Nty ) 
   _body( BOOL, 1 )
   _body( EmTPMtVideoPort, 1 )
   _ev_end

     /***********************<< ���÷��ͶԶ�����ƵԴֻ�� ֪ͨ>>********************	
  *[��Ϣ��]
  * TTpSuperUser
  *[��Ϣ����]
  *  cnc	  -> cns
  */
  _event(  ev_tppSetMainSrc_Nty )  
  _body( u8, 1 ) 
  _ev_end
    /***********************<< SDK�汾��֪>>********************	
  *[��Ϣ��]
  * TTpSuperUser
  *[��Ϣ����]
  *  cnc	  -> cns
  */
  _event(  ev_tppIsSdk_Nty )  
  _ev_end

  //ɾ��root�˻�
  _event( ev_CnDelRoot_Cmd )
  _ev_end
  //ɾ��root�˻���ʱ��
  _event( ev_CnDelRootTimer )
  _ev_end
#ifndef _MakeTpEventDescription_
		_ev_segment_end( outercnshduextend )
};
#endif
#endif 