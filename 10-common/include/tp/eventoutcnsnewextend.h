#ifndef _h_eventoutcnsnewextend_h__
#define _h_eventoutcnsnewextend_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSNEWEXTENDEVENT
{
#endif 
	
	_ev_segment( outercnsnewextend  )


  /***********************<< 修改矩阵配置 >>******************** 
 *[消息体]
 * TTPMatrixConfig   矩阵配置
 *[消息方向]
 *  cns <- tptool
*/
_event(  ev_CnSetMatrixConfig_Cmd  )
_body( TTPMatrixConfig ,1 )      
_ev_end

  /***********************<< 矩阵命令反馈 >>******************** 
 *[消息体]
 * TTPMatrixConfig   矩阵配置
 *[消息方向]
 *  cns -> Matrix
*/
_event(  ev_CnMatrixCommand_Ind  )
_body( EmMatrixCommandType ,1 )      
_body( s8 , TP_MATRIX_RSP_LEN )     
_ev_end

  /***********************<< 矩阵修改输入输出关系 >>******************** 
 *[消息体]
 * u32        输出通道号
 * u32        输入通道号
 *[消息方向]
 *  cns <- cnc
*/
_event(  ev_CnChangeMatrixOutInRelation_Cmd  )
_body( u32 ,1 )
_body( u32 ,1 )      
_ev_end

  /***********************<< 保存矩阵预案 >>******************** 
 *[消息体]
 * s32        预案号
 * s8         预案名称
 *[消息方向]
 *  cns <- cnc
*/
_event(  ev_CnSaveMatrixScence_Cmd  )
_body( s32 ,1 )
_body( s8  , TP_MATRIX_SCENENAME_LEN + 1)
_ev_end

  /***********************<< 保存矩阵预案反馈 >>******************** 
 *[消息体]
 * s32        预案号
 * s8         预案名称
 * BOOL       结果
 *[消息方向]
 *  cns -> cnc
*/
_event(  ev_CnSaveMatrixScence_Ind  )
_body( s32   , 1 )   
_body( s8    , TP_MATRIX_SCENENAME_LEN + 1)
_body( BOOL  , 1 )    
_ev_end

  /***********************<< 调用矩阵预案反馈 >>******************** 
 *[消息体]
 * s32        预案号
 *[消息方向]
 *  cns <- cnc
*/
_event(  ev_CnUseMatrixScence_Cmd  )
_body( s32  ,1 )    
_ev_end

  /***********************<< 调用矩阵预案反馈 >>******************** 
 *[消息体]
 * s32        预案号
 * BOOL       结果
 *[消息方向]
 *  cns -> cnc
*/
_event(  ev_CnUseMatrixScence_Ind  )
_body( s32  ,1 )    
_body( BOOL  ,1 )    
_ev_end

  /***********************<< 通知矩阵配置信息 >>******************** 
 *[消息体]
 * TTPMatrixConfig        矩阵配置信息
 *[消息方向]
 *  cns -> tptool / cnc
*/
_event(  ev_CnMatrixConfigInfo_Nty  )
_body( TTPMatrixConfig  ,1 )    
_ev_end

  /***********************<< 通知当前矩阵信息 >>******************** 
 *[消息体]
 * TTPCurMatrixInfo      当前矩阵信息
 *[消息方向]
 *  cns -> cnc
*/
_event(  ev_CnCurMatrixInfo_Nty  )
_body( TTPCurMatrixInfo   , 1)
_ev_end

  /***********************<< 通知矩阵预案信息 >>******************** 
 *[消息体]
 * TTPMatrixSceneInfo       矩阵预案信息
 *[消息方向]
 *  cns -> cnc
*/
_event(  ev_CnMatrixSceneInfo_Nty  )
_body( TTPMatrixSceneInfo   , TP_MATRIX_SCENENUM_MAX )    
_ev_end

  /***********************<< 重命名矩阵信息 >>******************** 
 *[消息体]
 * u32                      矩阵预案号
 * s8                       矩阵名
 *[消息方向]
 *  cns <- cnc
*/
_event(  ev_CnRenameMatrixScence_Cmd  )
_body( u32   , 1)
_body( s8   , TP_MATRIX_SCENENAME_LEN + 1)
_ev_end

  /***********************<< 重命名矩阵信息反馈 >>******************** 
 *[消息体]
 * u32                      矩阵预案号
 * s8                       矩阵名
 * BOOL                     结果
 *[消息方向]
 *  cns -> cnc
*/
_event(  ev_CnRenameMatrixScence_Ind  )
_body( s8   , TP_MATRIX_SCENENAME_LEN + 1)
_body( u32   , 1)
_body( BOOL  ,  1)
_ev_end

  /***********************<< 删除矩阵信息 >>******************** 
 *[消息体]
 * u32                      矩阵预案号
 *[消息方向]
 *  cns <- cnc
*/
_event(  ev_CnDeleteMatrixScence_Cmd  )
_body( u32   , 1)
_ev_end

  /***********************<< 删除矩阵信息反馈 >>******************** 
 *[消息体]
 * u32                      矩阵预案号
 * BOOL                     结果
 *[消息方向]
 *  cns -> cnc
*/
_event(  ev_CnDeleteMatrixScence_Ind  )
_body( u32   , 1)
_body( BOOL  ,  1)
_ev_end

  /***********************<< 通知矩阵连接状态 >>******************** 
 *[消息体]
 * BOOL                 连接结果
 *[消息方向]
 *  cns -> cnc/tptool
*/
_event(  ev_CnMatrixOnlineState_Nty  )
_body( BOOL  ,  1)
_ev_end

  /***********************<< 矩阵连接定时器 >>******************** 
 *[消息体]
 *[消息方向]
 *  cns -> cns
*/
_event(  ev_timer_Matrix_Connected  )
_ev_end

  /***********************<< 矩阵修改输入输出关系反馈 >>******************** 
 *[消息体]
 * s32                       矩阵对应关系            
 * BOOL                      结果    
 *[消息方向]
 *  cns -> cnc
*/
_event(  ev_CnMatrixRelation_Ind  )
_body( s32   , MT_MAX_MATRIX_CHANNEL_LEN )    
_body( BOOL , 1 )
_ev_end

  /***********************<< 矩阵修改输入输出关系反馈 >>******************** 
 *[消息体]
 * TTPMatrixConfig                       矩阵配置信息
 * BOOL                                  结果                
 *[消息方向]
 *  cns -> cnc
*/
_event(  ev_CnSetMatrixConfig_Ind  )
_body( TTPMatrixConfig   , 1) 
_body( BOOL   , 1)
_ev_end

  /***********************<< com口选择类型 >>******************** 
 *[消息体]
 * EmComType                       com2类型
 * EmComType                       com3类型            
 *[消息方向]
 *  tptool -> cns
*/
_event(  ev_Cn_SelectCom_Cmd  )
_body( EmComType   , 1) 
_body( EmComType   , 1)
_ev_end

  /***********************<< com口选择类型反馈 >>******************** 
 *[消息体]
 * EmComType                       com2类型
 * EmComType                       com3类型            
 *[消息方向]
 *  tptool <- cns
*/
_event(  ev_Cn_SelectCom_Ind  )
_body( EmComType   , 1) 
_body( EmComType   , 1)
_body( BOOL   , 1)
_ev_end

  /***********************<< com口选择类型通知 >>******************** 
 *[消息体]
 * EmComType                       com2类型
 * EmComType                       com3类型            
 *[消息方向]
 *  tptool <- cndevice
*/
_event(  ev_Cn_SelectCom_Nty  )
_body( EmComType      , 1) 
_body( EmComType      , 1)
_ev_end

  /***********************<< 升降屏排数选择 >>******************** 
 *[消息体]
 * BOOL                              标识那几排被启用了       
 *[消息方向]
 *  cns <- cnc
*/
_event(  ev_cns_centreSelectDFScreen_Cmd  )
_body( BOOL   , MAX_CENTREDFSCREEN_GROUP_NUM ) 
_ev_end

  /***********************<< 操作升级旋转屏 >>******************** 
 *[消息体]
 * EmCommandType                     指令类型        
 *[消息方向]
 *  cndevice <- cnc
*/
_event(  ev_Cn_CentreDFScreenCommand_Cmd  )
_body( EmCommandType   , 1 ) 
_ev_end

/***********************<< 操作升级旋转屏反馈 >>******************** 
 *[消息体]
 * EmCommandType                     指令类型        
 * BOOL                              写入结果        
 *[消息方向]
 *  cndevice <- cnc
*/
_event(  ev_Cn_CentreDFScreenCommand_Ind  )
_body( EmCommandType   , 1 ) 
_body( BOOL  ,  1)
_ev_end

  /***********************<< 修改升降屏参数配置 >>******************** 
 *[消息体]
 * EmComConfigType                     指令类型      
 * TSerialCfg                          串口配置  
 *[消息方向]
 *  cndevice <- tptool
*/
_event(  ev_Cn_CentreModifyDFScreenConfig_Cmd  )
_body( EmComConfigType   , 1 ) 
_body( TSerialCfg , 1 )
_ev_end

  /***********************<< 修改升降屏参数配置反馈 >>******************** 
 *[消息体]
 * EmComConfigType                     指令类型     
 * TSerialCfg                          串口配置  
 * BOOL                                结果     
 *[消息方向]
 *  cndevice -> tptool
*/
_event(  ev_Cn_CentreModifyDFScreenConfig_Ind  )
_body( EmComConfigType   , 1 ) 
_body( TSerialCfg , 1 )
_body( BOOL , 1 )
_ev_end

  /***********************<< 修改升级旋转屏组信息 >>******************** 
 *[消息体]
 * u32                                 组数   
 * TSerialCfg                          各组信息     
 *[消息方向]
 *  cndevice <- tptool
*/
_event(  ev_Cn_CentreModifyDFScreenGroup_Cmd  )
_body( u32   , 1 ) 
_body( TCenDownOrFlipScreenCfg , MAX_CENTREDFSCREEN_GROUP_NUM )
_ev_end

  /***********************<< 修改升级旋转屏组信息反馈 >>******************** 
 *[消息体]
 * u32                                 组数   
 * TSerialCfg                          各组信息 
 * BOOL                                结果    
 *[消息方向]
 *  cndevice -> tptool CNC
*/
_event(  ev_Cn_CentreModifyDFScreenGroup_Ind  )
_body( u32   , 1 ) 
_body( TCenDownOrFlipScreenCfg , MAX_CENTREDFSCREEN_GROUP_NUM )
_body( BOOL , 1)
_ev_end

  /***********************<< 第一次CNC登录提示 >>******************** 
 *[消息体] 
 *[消息方向]
 *  cnc <- cns
*/
_event(  ev_Cn_CNCFirstLogin_Nty  )
_ev_end

  /***********************<< 发送指令操作 >>******************** 
 *[消息体] 
 * s8                       指令内容
 *[消息方向]
 *  cnc <- cns
*/
_event(  ev_Cn_SendMatrixCommand_Cmd  )
_body( s8 , TP_MATRIX_CMDPRO_LEN)
_ev_end

  /***********************<< 当前矩阵对应关系通知 >>******************** 
 *[消息体] 
 * s32                       矩阵对应关系
 *[消息方向]
 *  cnc <- cns
*/
_event(  ev_Cn_MatrixRelation_Nty  )
_body( s32   , MT_MAX_MATRIX_CHANNEL_LEN )    
_ev_end

  /***********************<< com口选择类型模块间通知 >>******************** 
 *[消息体]
 * EmSerialType                    串口类型
 * EmComType                       com类型            
 *[消息方向]
 *  内部消息
*/
_event(  ev_Cn_CtrlSelectCom_Nty  )
_body( EmSerialType   , 1) 
_body( EmComType      , 1)
_ev_end

  /***********************<< 矩阵修改输入输出关系反馈 >>******************** 
 *[消息体]
 * TTPMatrixSceneInfo        矩阵对应关系            
 * BOOL                      结果    
 *[消息方向]
 *  cns -> cnc
*/
_event(  ev_CnMatrixOutInRelation_Ind  )
_body( TTPMatrixSceneInfo   , 1 )    
_body( BOOL , 1 )
_ev_end

  /***********************<< 当前矩阵对应关系通知 >>******************** 
 *[消息体] 
 * TTPMatrixSceneInfo       矩阵对应关系
 *[消息方向]
 *  cnc <- cns
*/
_event(  ev_Cn_MatrixInOutRelation_Nty  )
_body( TTPMatrixSceneInfo   , 1 )    
_ev_end

  /***********************<< 升降屏配置通知 >>******************** 
 *[消息体]
 * TCenDownOrFlipScreenInfo                    配置信息
 *[消息方向]
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