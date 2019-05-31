#ifndef _h_eventoutcnstool_h__
#define _h_eventoutcnstool_h__


#include "tpeventcomm.h"


#ifndef _MakeTpEventDescription_
enum EmCNSTOOLEVENT
{
#endif
	
	_ev_segment( outercnstool )

/***********************<<  Tool����CNS��ȡ��ǰϵͳ��Ϣ >>********************
*[��Ϣ��]
*NULL	
 *[��Ϣ����]	Tool	-->  CNS
 *
 */
 _event(  ev_tppGetSysInfo_Req )
 _ev_end

/***********************<<  CNS��ӦTool��ȡϵͳ��Ϣ >>********************
*[��Ϣ��]
*TTPSysInfo ϵͳʹ����Ϣ	
 *[��Ϣ����]	CNS	-->  Tool
 *
 */_event(  ev_tppGetSysInfo_Rsp )
	_body ( TTPSysInfo  , 1  )
   _ev_end

/***********************<<  CNS֪ͨTool��ǰϵͳ��Ϣ >>********************	
*[��Ϣ��]
*TTPSysInfo ϵͳʹ����Ϣ
 *[��Ϣ����]	CNS	-->  Tool
 *
 */_event(  ev_tppGetSysInfo_Nty )
	_body ( TTPSysInfo  , 1  )
   _ev_end

/***********************<<  Tool����CNS��ȡTPad�б� >>********************
*[��Ϣ��]
*NULL	
 *[��Ϣ����]	Tool	-->  CNS
 *
 */
_event(  ev_tppGetTPadIpList_Req )
_ev_end

/***********************<<  CNS��ӦTool��ȡTPad�б� >>********************
*[��Ϣ��]
*TTPTPadList TPad�б�	
 *[��Ϣ����]	CNS	-->  Tool
 *
 */
_event(  ev_tppGetTPadIpList_Rsp )
_body ( TTPTPadList  , 1  )
_ev_end

/***********************<<  CNS֪ͨTool��ǰTPad�б����ı� >>********************	
*[��Ϣ��]
*TTPTPadList TPad�б�
*s8 TPad�汾��
 *[��Ϣ����]	CNS	-->  Tool
 *
 */
_event(  ev_tppGetTPadIpList_Nty )
_body ( TTPTPadList  , 1  )	
_ev_end

/***********************<<  ������Ϣ֪ͨ >>********************	
*[��Ϣ��]
*TTPCnsConfStatus �᳡״̬
*TCnVideoParam ��Ƶ����
 *[��Ϣ����]	CNS	-->  Tool
 *
 */
_event(  ev_tppCnConfInfo_Nty )
_body ( TTPCnsConfStatus  , 1  )
_body ( TTPCnConfInfo , 1 )
_ev_end

/***********************<< T300��������  >>********************	
*[��Ϣ��]
*TTPVerFileInfo �����ļ���Ϣ
*[��Ϣ����]	Tool	-->  CNS
*
*/
_event(  ev_tppUpdate_Cmd )
_body ( TTPFTPFileInfo , 1 )
_ev_end


/***********************<<  T300������Ӧ >>********************	
*[��Ϣ��]
*BOOL �������
*[��Ϣ����]	CNS 	-->  Tool
*
*/
_event(  ev_tppUpdate_Ind )
_body ( BOOL  , 1  )	
_ev_end

/***********************<<  ��Ƶ�ӿ���������  >>********************	
*[��Ϣ��]
*TTpAudioPortInfo 3·����Ƶ�ӿ���Ϣ
*[��Ϣ����]	Tool	-->  CNS
*
*/
_event(  ev_tppSetAudioPort_Cmd )
_body ( TTpAudioPortInfo  , 3  )		
_ev_end


/***********************<<  ��Ƶ�ӿ����û�Ӧ >>********************	
*[��Ϣ��]
*TTpAudioPortInfo 3·����Ƶ�ӿ���Ϣ
*BOOL �����Ƿ�ɹ�
 *[��Ϣ����]	CNS	-->  Tool
 *
 */
_event(  ev_tppSetAudioPort_Ind )
_body ( TTpAudioPortInfo  , 3  )
_body ( BOOL, 1 )	
_ev_end


/***********************<<  ����Ƶѡ����󷽰����� >>********************	
*[��Ϣ��]
*TTPVgaMixInfo
*[��Ϣ����]	   Tool	-->  CNS
*
*/
_event(  ev_tppSelAVMatrixProject_Cmd )
_body ( TTPVgaMixInfo  , 1  )
_ev_end

/***********************<< ����Ƶѡ����󷽰���Ӧ  >>********************	
*[��Ϣ��]
*TTPVideoDiagInfo ��Ƶ��Ͻӿ���Ϣ
*TTPAudioDiagInfo ��Ƶ��Ͻӿ���Ϣ
*[��Ϣ����]	  CNS	-->  Tool
*
*/
_event(  ev_tppSelAVMatrixProject_Ind )
_body ( TTPVideoDiagInfo  , 1  )
_body ( TTPAudioDiagInfo  , 1  )	
_ev_end

/***********************<< ��ȡ������Ϣ����  >>********************	
*[��Ϣ��]
*NULL
*[��Ϣ����]	  Tool	-->  CNS
*
*/
_event(  ev_tppGetLostPacketInfo_Req )
_ev_end

/***********************<< ��ȡ������Ϣ��Ӧ  >>********************
*[��Ϣ��]
*u32
*u32
*[��Ϣ����]	  CNS	-->  Tool
*
*/
_event(  ev_tppGetLostPacketInfo_Rsp )
_body ( u32  , 1  )
_body ( u32  , 1  )
_ev_end

/***********************<< �����������������֪ͨ  >>********************
*[��Ϣ��]
*TTPUpDownSpeedInfo	��������������
*[��Ϣ����]	  CNS	-->  Tool
*
*/
_event(  ev_tppGetUpDownstreamRate_Nty )
_body ( TTPUpDownSpeedInfo  , 1  )
_ev_end

/***********************<< �����ַ������  >>********************
*[��Ϣ��]
*NULL	
*[��Ϣ����]	  Tool	-->  CNS
*
*/
_event(  ev_tppImportAddr_Req )
_ev_end

/***********************<< �����ַ����Ӧ  >>********************	
*[��Ϣ��]
*BOOL �����ַ�����
*[��Ϣ����]	  CNS	-->  Tool
*
*/
_event(  ev_tppImportAddr_Rsp )
_body ( BOOL  , 1  )
_ev_end

/***********************<< ����CNS֪ͨ  >>********************	
*[��Ϣ��]
*NULL
*[��Ϣ����]	  Tool	-->  CNS
*
*/
_event(  ev_tppReboot_Nty )
_ev_end

/***********************<< ��ȡϵͳ��Ϣ��ʱ��  >>********************	
*[��Ϣ��]
*NULL
*[��Ϣ����]	  Tool	-->  CNS
*
*/
_event(  ev_tppGetSysInfo_Timer )
_ev_end

/***********************<< ������ܷ�������Ӧ  >>********************	
*TTPNMServerCfg	���ܷ�����������Ϣ
*EmModifyNMServerRet ������ܷ��������
*[��Ϣ����]	  CNS	-->  Tool
*
*/
_event(  ev_tppCnAgtAddNMServer_Ind )
_body( TTPNMServerCfg, 1 )
_body( EmModifyNMServerRet, 1 )
_ev_end

/***********************<< ɾ�����ܷ�������Ӧ  >>********************
*TTPNMServerCfg	���ܷ�����������Ϣ
*EmModifyNMServerRet ɾ�����ܷ��������	
*[��Ϣ����]	  CNS	-->  Tool
*
*/
_event(  ev_tppCnAgtDelNMServer_Ind )
_body( TTPNMServerCfg, 1 )
_body( EmModifyNMServerRet, 1 )
_ev_end

/***********************<< �޸����ܷ�������Ӧ  >>********************	
*[��Ϣ��]
*TTPNMServerCfg	���ܷ�����������Ϣ
*EmModifyNMServerRet �޸����ܷ��������
*[��Ϣ����]	  CNS	-->  Tool
*
*  
*/
_event(  ev_tppCnAgtModifyNMServer_Ind )
_body( TTPNMServerCfg, 1 )
 _body( EmModifyNMServerRet, 1 )
_ev_end

/***********************<< ֪ͨά�����߹ܷ���������Ϣ  >>********************
*[��Ϣ��]
*TTPNMServerCfg	���ܷ�����������Ϣ
*[��Ϣ����]	  CNS	-->  Tool
*
*/
_event(  ev_tppCurAgtNMServerInfo_Nty )
_body( TTPNMServerCfg, 1 )
_ev_end

/***********************<< ά������ˢ�½�������  >>********************	
*[��Ϣ��]
*NULL
*[��Ϣ����]	  Tool	-->  CNS
*
*
*/
_event(  ev_tppRefresh_Req )
_ev_end

/***********************<< ��������Ϣ��ʱ��  >>********************	
*[��Ϣ��]
*NULL
*[��Ϣ����]	  CNS	-->  CNS
*
*
*/
_event(  ev_tppLoopbackTest_Timer )
_ev_end

//add by niu 2014-04-23
/***********************<< ���������Ի���ʱ����òɼ�����  >>********************	
*[��Ϣ��]
*NULL
*[��Ϣ����]	  CNS	-->  CNS
*
*
*/
_event(  ev_tppAutoLoopbackTest_Timer )
_ev_end
//end add by niu

/***********************<< ��ȡ������Ϣ��ʱ��  >>********************	
*[��Ϣ��]
*NULL
*[��Ϣ����]	  CNS	-->  CNS
*
*
*/
_event(  ev_tppEnableStartDual_Nty )
_ev_end

/***********************<< ���������ʻ�ȡ��ʱ��  >>********************
*[��Ϣ��]
*NULL	
*[��Ϣ����]	  CNS	-->  CNS
*
*
*/
_event(  ev_tppGetUpDownNetSpeed_Timer )
_ev_end

/***********************<< ��¼�ɹ����ȡ������Ϣ֪ͨ  >>********************	
*[��Ϣ��]
*NULL
*[��Ϣ����]	  CNS	-->  CNS
*
*
*/
_event(  ev_tppGetConfInfo_Nty )
_ev_end

/***********************<< ����Ƶ������Ϣ֪ͨ  >>********************
*[��Ϣ��]
*TVgaInfo VGA�豸��Ϣ
*TTPVgaMixInfo	
*[��Ϣ����]	  CNS	-->  Tool
*
*
*/
_event(  ev_tppAVInfo_Nty )
_body( TVgaInfo, CNS_VGA_TYPE_NUM )
_body( TTPVgaMixInfo, 1 )
_ev_end

/***********************<< ֪ͨά�������Ƿ���ʾ�᳡������Ϣ  >>********************	
*[��Ϣ��]
*BOOL	
*[��Ϣ����]	  CNS	-->  Tool
*
*/
_event( ev_tppShowRoomName_Nty )
_body( BOOL, 1 )
_ev_end

/***********************<< ��ʾ�᳡������ >>********************
*[��Ϣ��]
*BOOL		
*[��Ϣ����]	  CNS	<--  Tool
*
*/
_event( ev_tppShowRoomName_Cmd )
_body( BOOL, 1 )
_ev_end

// **********************<< ֪ͨά������ϵͳ��������Ϣ  >>********************	
// *[��Ϣ��]
// *TTPSleepInfo	
// *[��Ϣ����]	  CNS	-->  cnc
// *
// _event( ev_tppCnSysSleep_Nty )
// _body( TTPSleepInfo, 1 )
// _ev_end

// **********************<< ϵͳ�����������Ϣ  >>********************	
// *[��Ϣ��]
// *TTPSleepInfo	
// *[��Ϣ����]	  CNS	-->  Tool
// *
// _event( ev_tppCnSysSleep_Cmd )
// _body( TTPSleepInfo, 1 )
// _ev_end

/***********************<< ��Ƶ��������������  >>********************	
*[��Ϣ��]
*TTPEqualizer ��·��Ƶ��������ľ�������Ϣ	
*[��Ϣ����]	  Tool	-->  CNS
*
*/
_event( ev_tppSetAudioEqualizer_Cmd )
_body( TTPEqualizer, 3 )
_ev_end

/***********************<< ��Ƶ������������Ӧ  >>********************	
*[��Ϣ��]
*TTPEqualizer ��·��Ƶ��������ľ�������Ϣ
*BOOL �����Ƿ�ɹ�	
*[��Ϣ����]	  CNS	-->  Tool
*
*/
_event( ev_tppSetAudioEqualizer_Ind )
_body( TTPEqualizer, 3 )
_body( BOOL, 1 )
_ev_end

/***********************<< ��Ƶ��������������  >>********************	
*[��Ϣ��]
*u8*3 ��·����Ƶ����·��
*u8   �᳡����Ƶ����·��	
*[��Ϣ����]	  Tool	-->  CNS
*
*/
_event( ev_tppSetAudiotMixer_Cmd )
_body( u8, 4 )
_ev_end

/***********************<< ��Ƶ������������Ӧ  >>********************	
*[��Ϣ��]
*u8*3 ��·����Ƶ����·��
*u8   �᳡����Ƶ����·��
*BOOL �����Ƿ�ɹ�
*[��Ϣ����]	  CNS	-->  Tool
*
*/
_event( ev_tppSetAudiotMixer_Ind )
_body( u8, 4 )
_body( BOOL, 1 )
_ev_end

/***********************<< ���з�����������������  >>********************	
*[��Ϣ��]
*TTPCallSerInfo   ���з�����������Ϣ
*[��Ϣ����]	  Tool	-->  CNS
*
*/
_event( ev_tppSetCallServerInfo_Cmd )
_body( TTPCallSerInfo, 1 )
_ev_end

/***********************<< ���з�������������֪ͨ  >>********************	
*[��Ϣ��]
*TTPCallSerInfo   ���з�����������Ϣ
*[��Ϣ����]	  CNS	-->  Tool
*
*/
_event( ev_tppSetCallServerInfo_Nty )
_body( TTPCallSerInfo, 1 )
_ev_end

/***********************<< ���з���������������Ӧ  >>********************	
*[��Ϣ��]
*TTPCallSerInfo   ���з�����������Ϣ
*BOOL ���з����������Ƿ�ɹ�
*[��Ϣ����]	  CNS	-->  Tool
*
*/
_event( ev_tppSetCallServerInfo_Ind )
_body( TTPCallSerInfo, 1 )
_body( BOOL, 1 )
_ev_end

/***********************<< ����������������������  >>********************	
*[��Ϣ��]
*u32_ip   ����������������Ϣ
*[��Ϣ����]	  Tool	-->  CNS
*
*/
_event( ev_tppSetUpgradeServerInfo_Cmd )
_body( TTPUpgradeSer, 1 )
_ev_end

/***********************<< ������������������֪ͨ  >>********************	
*[��Ϣ��]
*u32_ip   ����������������Ϣ
*[��Ϣ����]	  CNS	-->  Tool
*
*/
_event( ev_tppSetUpgradeServerInfo_Nty )
_body( TTPUpgradeSer, 1 )
_ev_end

/***********************<< ��������������������Ӧ  >>********************	
*[��Ϣ��]
*u32_ip   ����������������Ϣ
*BOOL ���������������Ƿ�ɹ�
*[��Ϣ����]	  CNS	-->  Tool
*
*/
_event( ev_tppSetUpgradeServerInfo_Ind )
_body( TTPUpgradeSer, 1 )
_body( BOOL, 1 )
_ev_end

/***********************<< ֹͣ����Ƶ�ӿڲ�������  >>********************
*[��Ϣ��]
*[��Ϣ����]	  Tool	-->  Cns
*
*/
_event( ev_tppStopAVMatrixProject_Req )
_ev_end

/***********************<< ֹͣ����Ƶ�ӿڲ�����Ӧ  >>********************
*[��Ϣ��]
*[��Ϣ����]	  Cns	-->  Tool
*
*/
_event( ev_tppStopAVMatrixProject_Rsp )
_ev_end

/***********************<< ��Ƶ�ӿ����ûָ�Ĭ������  >>********************
*[��Ϣ��]
*[��Ϣ����]	  Tool	-->  Cns
*
*/
_event( ev_tppAudioRestoreDefaults_Cmd )
_body ( TTpAudioPortInfo  , 3  )
_ev_end

/***********************<< ��Ƶ�ӿ����ûָ�Ĭ��������Ӧ  >>********************
*[��Ϣ��]
*[��Ϣ����]	  Cns	-->  Tool
*
*/
_event( ev_tppAudioRestoreDefaults_Ind )
_body( BOOL, 1 )
_ev_end

/***********************<< �������ûָ�Ĭ������  >>********************
*[��Ϣ��]
*[��Ϣ����]	  Tool	-->  Cns
*
*/
_event( ev_tppMixRestoreDefaults_Cmd )
_body( u8, 4 )
_ev_end

/***********************<< �������ûָ�Ĭ��������Ӧ  >>********************
*[��Ϣ��]
*[��Ϣ����]	  Cns	-->  Tool
*
*/
_event( ev_tppMixRestoreDefaults_Ind )
_body( BOOL, 1 )
_ev_end

/***********************<< ���������ûָ�Ĭ������  >>********************
*[��Ϣ��]
*[��Ϣ����]	  Tool	-->  Cns
*
*/
_event( ev_tppEqualizerReDefaults_Cmd )
_body( TTPEqualizer, 3 )
_ev_end

/***********************<< ���������ûָ�Ĭ��������Ӧ  >>********************
*[��Ϣ��]
*[��Ϣ����]	  Cns	-->  Tool
*
*/
_event( ev_tppEqualizerReDefaults_Ind )
_body( BOOL, 1 )
_ev_end

/***********************<< B2�汾��ȡGK�б���Ϣ֪ͨ  >>********************
*[��Ϣ��]
*[��Ϣ����]	  Cncall -->Cns,Cns -->CNC  
*
*/
_event( ev_tppGetRegGKInfo_Nty )
_body( TTPMtRegInfo, 1 )
//_body( BOOL, 1 )
_ev_end

/***********************<< B2�汾��ȡSIP��ַ����Ϣ��Ӧ  >>********************
*[��Ϣ��]
*[��Ϣ����]	  Cncall -->Cns,Cns -->CNC  
*
*/
_event( ev_tppGetRegInfoCNS_Rsp )
_body( TRegPackInfoEx, 1 )
_body( EmGetRegInfoType, 1 )
_body( TCnsRegPackEx, 1 )
_ev_end

/***********************<< B2�汾��ȡSIP��ַ����Ϣ��Ӧ  >>********************
*[��Ϣ��]
*[��Ϣ����]	  Cncall -->Cns,Cns -->CNC  
*
*/
_event( ev_tppGetRegInfoUMS_Rsp )
_body( TRegPackInfoEx, 1 )
_body( EmGetRegInfoType, 1 )
_body( TUmsRegPackEx, 1 )
//_body( TUmsRegPackEx, 1 )
_ev_end

    /*************************<< �����ĵ���������� >>******************************	
 *[��Ϣ��]
 *  +EmDcamProType �����ͺ� emVISCAPro RS200 , emPELCOPro PC822
 *  
 *[��Ϣ����]
 *   
 *      tptool => cns 
 */_event(  ev_Cn_DocSetTypeCmd )
   _body (EmDCamProType, 1)
   _ev_end

    /*************************<< �����ĵ���������ͷ��� >>******************************	
 *[��Ϣ��]
 *  
 *  +EmDcamProType �����ͺ� emVISCAPro RS200 , emPELCOPro PC822
 *  +BOOL �����Ƿ�ɹ�
 *  +u8   ��ǰ���������
 *[��Ϣ����]
 *   
 *      cns  => tptool  
 */_event(  ev_Cn_DocSetTypeInd)
   _body (EmDCamProType, 1)
   _body (BOOL, 1)
   _body (u8  , 1)
   _ev_end

   /***********************<<  ��ũ���10��������  >>********************	
*[��Ϣ��]
*TTpAudioPortInfo ��ũ���10��Ϣ
*[��Ϣ����]	Tools	-->  CNS
*
*/
_event( ev_tppSetMic10Info_Cmd )
_body ( TTpMic10Info, 1 )		
_ev_end

   /***********************<<  ��ũ���10���û�Ӧ  >>********************	
*[��Ϣ��]
*TTpAudioPortInfo ��ũ���10��Ϣ
*[��Ϣ����]	CNS	-->  Tools
*
*/
_event( ev_tppSetMic10Info_Ind )
_body ( TTpMic10Info, 1 )
_body ( BOOL , 1 )		
_ev_end

/*************************<< 323�ն��ϱ���ƵԴ������Ϣ >>******************************   
*[��Ϣ��]
*  +TVidSourceInfo 
*  
*[��Ϣ����]
*	
*	   cns => cnc
*/_event(  ev_H323SendVideoInfo_Nty )
  _body( TVidSourceInfo , 1 )
  _ev_end

/*************************<< 323�ն��ϱ���ƵԴ������Ϣ >>******************************   
*[��Ϣ��]
*  +TVidSourceInfo 
*  
*[��Ϣ����]
*	
*	   cns => cnc
*/_event(  ev_H323SendVideoFeccInfo_Nty )
  _body( BOOL32, 1 )
  _body( u8, 1 )
  _ev_end

/*************************<< GKע�� >>****************************** 
*[��Ϣ��]
*TTPGKCfg 
*[��Ϣ����]
*cns -> cns
*/
  _event( ev_tppGkRegister_Nty )
  _body( TTPGKCfg, 1 )
  _ev_end

    /*************************<< ���·����Ϣ���� >>******************************   
*[��Ϣ��]
*  +TRouteCfg 
*  
*[��Ϣ����]
*	
*	   tptools => cns
*/_event(  ev_tppAddRoute_Cmd )
  _body( TRouteCfg, 1 )
  _ev_end

    /*************************<< ����·����Ϣ��Ӧ >>******************************   
*[��Ϣ��]
*  +TRouteCfg 
*  
*[��Ϣ����]
*	
*	   tptools => cns
*/_event(  ev_tppAddRoute_Ind )
  _body( TRouteCfg, 1 )
  _body( BOOL, 1 )
  _ev_end

  /*************************<< �h��·����Ϣ���� >>******************************   
  *[��Ϣ��]
  *  +TRouteCfg 
  *  
  *[��Ϣ����]
  *	
  *	   tptools => cns
  */_event(  ev_tppDelRoute_Cmd )
  _body( TRouteCfg, 1 )
  _ev_end

  /*************************<< �h��·����Ϣ��Ӧ >>******************************   
  *[��Ϣ��]
  *  +TRouteCfg 
  *  
  *[��Ϣ����]
  *	
  *	   tptools => cns
  */_event(  ev_tppDelRoute_Ind )
  _body( TRouteCfg, 1 )
  _body( BOOL, 1 )
  _ev_end

    /*************************<< ·����Ϣ֪ͨ >>******************************   
  *[��Ϣ��]
  *  +TRouteCfg 
  *  
  *[��Ϣ����]
  *	
  *	   tptools => cns
  */_event(  ev_tppRouteInfo_Nty )
  _body( TRouteCfg, 16 )
  _ev_end

  /***********************<<  ��ʱ�ȴ������� >>********************** 
  *[��Ϣ��]
  *NULL
  *[��Ϣ����]
  *cns -> cns
  */
  _event( ev_TppCheckPID__timer )
  _ev_end

  /*************************<< ntpʱ��ͬ������������ >>******************************   
  *[��Ϣ��]
  * u32_ip   ʱ��ͬ��������������Ϣ
  *  
  *[��Ϣ����]
  *	
  *	tptools => cns
  */_event(  ev_tppSetNtpServerInfo_Cmd )
  _body( TTPNtpSer, 1 )
  _ev_end

    /*************************<< ntpʱ��ͬ����������Ӧ >>******************************   
  *[��Ϣ��]
  * u32_ip   ʱ��ͬ��������������Ϣ
  *  
  *[��Ϣ����]
  *	
  *	tptools => cns
  */_event(  ev_tppSetNtpServerInfo_Ind )
  _body( TTPNtpSer, 1 )
  _body( BOOL, 1 )
  _ev_end

    /*************************<< ntpʱ��ͬ��������֪ͨ >>******************************   
  *[��Ϣ��]
  * u32_ip   ʱ��ͬ��������������Ϣ
  *  
  *[��Ϣ����]
  *	
  *	tptools => cns
  */_event(  ev_tppSetNtpServerInfo_Nty )
  _body( TTPNtpSer, 1 )
  _ev_end

    /***********************<< �����Ƿ��¼ͬ��ʱ������ >>********************** 
  *[��Ϣ��]	
  *BOOL    �Ƿ�ͬ��ʱ�䵽cns					
  *[��Ϣ����]
  *  cnc	  ->  cns
  */
  _event(  ev_CnNtpIsUsed_Cmd )
  _body (BOOL, 1)
  _ev_end

  /***********************<< �����Ƿ��¼ͬ��ʱ���Ӧ >>********************** 
  *[��Ϣ��]	
  *BOOL    �Ƿ�ͬ��ʱ�䵽cns					
  *[��Ϣ����]
  *  cns	  ->  cnc
  */
  _event(  ev_CnNtpIsUsed_Ind )
  _body (BOOL, 1)
  _body (BOOL, 1)
  _body( TTPTime, 1 )
  _ev_end

  /***********************<< ֪ͨcnc��ǰcns��ϵͳʱ�� >>********************** 
  *[��Ϣ��]	
  *TTPTime ϵͳʱ��
  *BOOL    �Ƿ�ͬ��ʱ�䵽cns					
  *[��Ϣ����]
  *  cns	  ->  cnc
  */
  _event(  ev_CnSysTimeToCnc_Nty )
  _body( TTPTime, 1 )
  _body( BOOL, 1 )
  _ev_end

  /***********************<<  ��Ƶ������������  >>********************	
  *[��Ϣ��]
  *TTpAudioPortInfo 3·����Ƶ�ӿ���Ϣ
  *[��Ϣ����]	Tool	-->  CNS
  *
  */
  _event(  ev_tppSetAudioVolum_Cmd )
  _body ( u8  , 1  )	
  _body ( u8  , 1  )	
  _body ( BOOL  , 1  )
  _ev_end
  
  /***********************<<  ��Ƶ�����������ƻ�Ӧ  >>********************	
  *[��Ϣ��]
  *TTpAudioPortInfo 3·����Ƶ�ӿ���Ϣ
  *[��Ϣ����]	Tool	-->  CNS
  *
  */
  _event(  ev_tppSetAudioVolum_Ind )
  _body ( u8  , 1  )	
  _body ( BOOL  , 1  )	
_ev_end

    /***********************<< Tpad���������Ը������� >>********************** 
  *[��Ϣ��]	
  *TTpPasswordUpdateInfo 					
  *[��Ϣ����]
  *  cnc	  ->  cns
  */
  _event( ev_CnTpadPasswordUpdate_Cmd )
  _body( TTpPasswordUpdateInfo, 1 )
  _ev_end

      /***********************<< Tpad���������Ը�����Ӧ >>********************** 
  *[��Ϣ��]	
  *TTpPasswordUpdateInfo 					
  *[��Ϣ����]
  *  cns	  ->  cnc
  */
  _event( ev_CnTpadPasswordUpdate_Ind )
  _body( TTpPasswordUpdateInfo, 1 )
  _body( BOOL, 1 )
  _ev_end

      /***********************<< Tpad���������Ը���֪ͨ >>********************** 
  *[��Ϣ��]	
  *TTpPasswordUpdateInfo 					
  *[��Ϣ����]
  *  cns	  ->  cnc
  */
  _event(  ev_CnTpadPasswordUpdate_Nty )
  _body( TTpPasswordUpdateInfo, 1 )
  _ev_end

#ifndef _MakeTpEventDescription_
		_ev_segment_end(outercnstool)
};
#endif


#endif // _h_tooleventoutcomm_h__
