#ifndef _h_eventoutcnsnewextend_h__
#define _h_eventoutcnsnewextend_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSNEWEXTENDEVENT
{
#endif 
	
	_ev_segment( outercnsnewextend  )


  /***********************<< �޸ľ������� >>******************** 
 *[��Ϣ��]
 * TTPMatrixConfig   ��������
 *[��Ϣ����]
 *  cns <- tptool
*/
_event(  ev_CnSetMatrixConfig_Cmd  )
_body( TTPMatrixConfig ,1 )      
_ev_end

  /***********************<< ��������� >>******************** 
 *[��Ϣ��]
 * TTPMatrixConfig   ��������
 *[��Ϣ����]
 *  cns -> Matrix
*/
_event(  ev_CnMatrixCommand_Ind  )
_body( EmMatrixCommandType ,1 )      
_body( s8 , TP_MATRIX_RSP_LEN )     
_ev_end

  /***********************<< �����޸����������ϵ >>******************** 
 *[��Ϣ��]
 * u32        ���ͨ����
 * u32        ����ͨ����
 *[��Ϣ����]
 *  cns <- cnc
*/
_event(  ev_CnChangeMatrixOutInRelation_Cmd  )
_body( u32 ,1 )
_body( u32 ,1 )      
_ev_end

  /***********************<< �������Ԥ�� >>******************** 
 *[��Ϣ��]
 * s32        Ԥ����
 * s8         Ԥ������
 *[��Ϣ����]
 *  cns <- cnc
*/
_event(  ev_CnSaveMatrixScence_Cmd  )
_body( s32 ,1 )
_body( s8  , TP_MATRIX_SCENENAME_LEN + 1)
_ev_end

  /***********************<< �������Ԥ������ >>******************** 
 *[��Ϣ��]
 * s32        Ԥ����
 * s8         Ԥ������
 * BOOL       ���
 *[��Ϣ����]
 *  cns -> cnc
*/
_event(  ev_CnSaveMatrixScence_Ind  )
_body( s32   , 1 )   
_body( s8    , TP_MATRIX_SCENENAME_LEN + 1)
_body( BOOL  , 1 )    
_ev_end

  /***********************<< ���þ���Ԥ������ >>******************** 
 *[��Ϣ��]
 * s32        Ԥ����
 *[��Ϣ����]
 *  cns <- cnc
*/
_event(  ev_CnUseMatrixScence_Cmd  )
_body( s32  ,1 )    
_ev_end

  /***********************<< ���þ���Ԥ������ >>******************** 
 *[��Ϣ��]
 * s32        Ԥ����
 * BOOL       ���
 *[��Ϣ����]
 *  cns -> cnc
*/
_event(  ev_CnUseMatrixScence_Ind  )
_body( s32  ,1 )    
_body( BOOL  ,1 )    
_ev_end

  /***********************<< ֪ͨ����������Ϣ >>******************** 
 *[��Ϣ��]
 * TTPMatrixConfig        ����������Ϣ
 *[��Ϣ����]
 *  cns -> tptool / cnc
*/
_event(  ev_CnMatrixConfigInfo_Nty  )
_body( TTPMatrixConfig  ,1 )    
_ev_end

  /***********************<< ֪ͨ��ǰ������Ϣ >>******************** 
 *[��Ϣ��]
 * TTPCurMatrixInfo      ��ǰ������Ϣ
 *[��Ϣ����]
 *  cns -> cnc
*/
_event(  ev_CnCurMatrixInfo_Nty  )
_body( TTPCurMatrixInfo   , 1)
_ev_end

  /***********************<< ֪ͨ����Ԥ����Ϣ >>******************** 
 *[��Ϣ��]
 * TTPMatrixSceneInfo       ����Ԥ����Ϣ
 *[��Ϣ����]
 *  cns -> cnc
*/
_event(  ev_CnMatrixSceneInfo_Nty  )
_body( TTPMatrixSceneInfo   , TP_MATRIX_SCENENUM_MAX )    
_ev_end

  /***********************<< ������������Ϣ >>******************** 
 *[��Ϣ��]
 * u32                      ����Ԥ����
 * s8                       ������
 *[��Ϣ����]
 *  cns <- cnc
*/
_event(  ev_CnRenameMatrixScence_Cmd  )
_body( u32   , 1)
_body( s8   , TP_MATRIX_SCENENAME_LEN + 1)
_ev_end

  /***********************<< ������������Ϣ���� >>******************** 
 *[��Ϣ��]
 * u32                      ����Ԥ����
 * s8                       ������
 * BOOL                     ���
 *[��Ϣ����]
 *  cns -> cnc
*/
_event(  ev_CnRenameMatrixScence_Ind  )
_body( s8   , TP_MATRIX_SCENENAME_LEN + 1)
_body( u32   , 1)
_body( BOOL  ,  1)
_ev_end

  /***********************<< ɾ��������Ϣ >>******************** 
 *[��Ϣ��]
 * u32                      ����Ԥ����
 *[��Ϣ����]
 *  cns <- cnc
*/
_event(  ev_CnDeleteMatrixScence_Cmd  )
_body( u32   , 1)
_ev_end

  /***********************<< ɾ��������Ϣ���� >>******************** 
 *[��Ϣ��]
 * u32                      ����Ԥ����
 * BOOL                     ���
 *[��Ϣ����]
 *  cns -> cnc
*/
_event(  ev_CnDeleteMatrixScence_Ind  )
_body( u32   , 1)
_body( BOOL  ,  1)
_ev_end

  /***********************<< ֪ͨ��������״̬ >>******************** 
 *[��Ϣ��]
 * BOOL                 ���ӽ��
 *[��Ϣ����]
 *  cns -> cnc/tptool
*/
_event(  ev_CnMatrixOnlineState_Nty  )
_body( BOOL  ,  1)
_ev_end

  /***********************<< �������Ӷ�ʱ�� >>******************** 
 *[��Ϣ��]
 *[��Ϣ����]
 *  cns -> cns
*/
_event(  ev_timer_Matrix_Connected  )
_ev_end

  /***********************<< �����޸����������ϵ���� >>******************** 
 *[��Ϣ��]
 * s32                       �����Ӧ��ϵ            
 * BOOL                      ���    
 *[��Ϣ����]
 *  cns -> cnc
*/
_event(  ev_CnMatrixRelation_Ind  )
_body( s32   , MT_MAX_MATRIX_CHANNEL_LEN )    
_body( BOOL , 1 )
_ev_end

  /***********************<< �����޸����������ϵ���� >>******************** 
 *[��Ϣ��]
 * TTPMatrixConfig                       ����������Ϣ
 * BOOL                                  ���                
 *[��Ϣ����]
 *  cns -> cnc
*/
_event(  ev_CnSetMatrixConfig_Ind  )
_body( TTPMatrixConfig   , 1) 
_body( BOOL   , 1)
_ev_end

  /***********************<< com��ѡ������ >>******************** 
 *[��Ϣ��]
 * EmComType                       com2����
 * EmComType                       com3����            
 *[��Ϣ����]
 *  tptool -> cns
*/
_event(  ev_Cn_SelectCom_Cmd  )
_body( EmComType   , 1) 
_body( EmComType   , 1)
_ev_end

  /***********************<< com��ѡ�����ͷ��� >>******************** 
 *[��Ϣ��]
 * EmComType                       com2����
 * EmComType                       com3����            
 *[��Ϣ����]
 *  tptool <- cns
*/
_event(  ev_Cn_SelectCom_Ind  )
_body( EmComType   , 1) 
_body( EmComType   , 1)
_body( BOOL   , 1)
_ev_end

  /***********************<< com��ѡ������֪ͨ >>******************** 
 *[��Ϣ��]
 * EmComType                       com2����
 * EmComType                       com3����            
 *[��Ϣ����]
 *  tptool <- cndevice
*/
_event(  ev_Cn_SelectCom_Nty  )
_body( EmComType      , 1) 
_body( EmComType      , 1)
_ev_end

  /***********************<< ����������ѡ�� >>******************** 
 *[��Ϣ��]
 * BOOL                              ��ʶ�Ǽ��ű�������       
 *[��Ϣ����]
 *  cns <- cnc
*/
_event(  ev_cns_centreSelectDFScreen_Cmd  )
_body( BOOL   , MAX_CENTREDFSCREEN_GROUP_NUM ) 
_ev_end

  /***********************<< ����������ת�� >>******************** 
 *[��Ϣ��]
 * EmCommandType                     ָ������        
 *[��Ϣ����]
 *  cndevice <- cnc
*/
_event(  ev_Cn_CentreDFScreenCommand_Cmd  )
_body( EmCommandType   , 1 ) 
_ev_end

/***********************<< ����������ת������ >>******************** 
 *[��Ϣ��]
 * EmCommandType                     ָ������        
 * BOOL                              д����        
 *[��Ϣ����]
 *  cndevice <- cnc
*/
_event(  ev_Cn_CentreDFScreenCommand_Ind  )
_body( EmCommandType   , 1 ) 
_body( BOOL  ,  1)
_ev_end

  /***********************<< �޸��������������� >>******************** 
 *[��Ϣ��]
 * EmComConfigType                     ָ������      
 * TSerialCfg                          ��������  
 *[��Ϣ����]
 *  cndevice <- tptool
*/
_event(  ev_Cn_CentreModifyDFScreenConfig_Cmd  )
_body( EmComConfigType   , 1 ) 
_body( TSerialCfg , 1 )
_ev_end

  /***********************<< �޸��������������÷��� >>******************** 
 *[��Ϣ��]
 * EmComConfigType                     ָ������     
 * TSerialCfg                          ��������  
 * BOOL                                ���     
 *[��Ϣ����]
 *  cndevice -> tptool
*/
_event(  ev_Cn_CentreModifyDFScreenConfig_Ind  )
_body( EmComConfigType   , 1 ) 
_body( TSerialCfg , 1 )
_body( BOOL , 1 )
_ev_end

  /***********************<< �޸�������ת������Ϣ >>******************** 
 *[��Ϣ��]
 * u32                                 ����   
 * TSerialCfg                          ������Ϣ     
 *[��Ϣ����]
 *  cndevice <- tptool
*/
_event(  ev_Cn_CentreModifyDFScreenGroup_Cmd  )
_body( u32   , 1 ) 
_body( TCenDownOrFlipScreenCfg , MAX_CENTREDFSCREEN_GROUP_NUM )
_ev_end

  /***********************<< �޸�������ת������Ϣ���� >>******************** 
 *[��Ϣ��]
 * u32                                 ����   
 * TSerialCfg                          ������Ϣ 
 * BOOL                                ���    
 *[��Ϣ����]
 *  cndevice -> tptool CNC
*/
_event(  ev_Cn_CentreModifyDFScreenGroup_Ind  )
_body( u32   , 1 ) 
_body( TCenDownOrFlipScreenCfg , MAX_CENTREDFSCREEN_GROUP_NUM )
_body( BOOL , 1)
_ev_end

  /***********************<< ��һ��CNC��¼��ʾ >>******************** 
 *[��Ϣ��] 
 *[��Ϣ����]
 *  cnc <- cns
*/
_event(  ev_Cn_CNCFirstLogin_Nty  )
_ev_end

  /***********************<< ����ָ����� >>******************** 
 *[��Ϣ��] 
 * s8                       ָ������
 *[��Ϣ����]
 *  cnc <- cns
*/
_event(  ev_Cn_SendMatrixCommand_Cmd  )
_body( s8 , TP_MATRIX_CMDPRO_LEN)
_ev_end

  /***********************<< ��ǰ�����Ӧ��ϵ֪ͨ >>******************** 
 *[��Ϣ��] 
 * s32                       �����Ӧ��ϵ
 *[��Ϣ����]
 *  cnc <- cns
*/
_event(  ev_Cn_MatrixRelation_Nty  )
_body( s32   , MT_MAX_MATRIX_CHANNEL_LEN )    
_ev_end

  /***********************<< com��ѡ������ģ���֪ͨ >>******************** 
 *[��Ϣ��]
 * EmSerialType                    ��������
 * EmComType                       com����            
 *[��Ϣ����]
 *  �ڲ���Ϣ
*/
_event(  ev_Cn_CtrlSelectCom_Nty  )
_body( EmSerialType   , 1) 
_body( EmComType      , 1)
_ev_end

  /***********************<< �����޸����������ϵ���� >>******************** 
 *[��Ϣ��]
 * TTPMatrixSceneInfo        �����Ӧ��ϵ            
 * BOOL                      ���    
 *[��Ϣ����]
 *  cns -> cnc
*/
_event(  ev_CnMatrixOutInRelation_Ind  )
_body( TTPMatrixSceneInfo   , 1 )    
_body( BOOL , 1 )
_ev_end

  /***********************<< ��ǰ�����Ӧ��ϵ֪ͨ >>******************** 
 *[��Ϣ��] 
 * TTPMatrixSceneInfo       �����Ӧ��ϵ
 *[��Ϣ����]
 *  cnc <- cns
*/
_event(  ev_Cn_MatrixInOutRelation_Nty  )
_body( TTPMatrixSceneInfo   , 1 )    
_ev_end

  /***********************<< ����������֪ͨ >>******************** 
 *[��Ϣ��]
 * TCenDownOrFlipScreenInfo                    ������Ϣ
 *[��Ϣ����]
 *  cndevice -> cnc tptool
*/
_event(  ev_Cn_CentreDFScreenConfig_Nty  )
_body( TCenDownOrFlipScreenInfo   , 1) 
_ev_end

#ifndef _MakeTpEventDescription_
		_ev_segment_end( outercnsnewextend )
};
#endif
#endif 