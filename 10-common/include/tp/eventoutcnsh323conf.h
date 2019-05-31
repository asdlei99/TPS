#ifndef _h_eventoutcnsh323conf_h__
#define _h_eventoutcnsh323conf_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSH323CONFEVENT
{
#endif 

  _ev_segment( outercnsh323conf  )


/***********************<< ��ʼ������ָʾ >>********************** 
*[��Ϣ��]

*[��Ϣ����]
*  cns	  <- cncall
*/
_event(  ev_CnModuleMultipleConference )
_ev_end
	  
/***********************<< ȡ��������ָʾ >>********************** 
*[��Ϣ��]

*[��Ϣ����]
*  cns	  <- cncall
*/
_event(  ev_CnModuleCancelMultipleConference )
_ev_end

/***********************<< �����ն˱�� >>********************** 
*[��Ϣ��]
TTPMDLTERLABEL
*[��Ϣ����]
*  cns	  <- cncall
*/
_event(  ev_CnModuleTerminalNumberAssign )
_body(TTPTerLabel, 1)
_ev_end

/***********************<< �����˿��������� >>********************** 
*[��Ϣ��]

*[��Ϣ����]
*  cns	  <- cncall
*/
_event(  ev_CnModuleSeenByAll )
_ev_end

/***********************<< ȡ�������˿� >>********************** 
*[��Ϣ��]

*[��Ϣ����]
*  cns	  <- cncall
*/
_event(  ev_CnModuleCancelSeenByAll )
_ev_end

/***********************<< �����б� >>********************** 
*[��Ϣ��]

*[��Ϣ����]
*  cncall	  <- cns
*/
_event(  ev_CnModuleTerminalListRequest )

_ev_end

/***********************<< �����б� >>********************** 
*[��Ϣ��]

*[��Ϣ����]
*  cncall	  <- cns
*/
_event(  ev_CnModuleTerminalIDListRequest )

_ev_end



/***********************<< ������� >>********************** 
*[��Ϣ��]
TTPMDLTERLABEL
*[��Ϣ����]
*  cns	  <- cncall
*/
_event(  ev_CnModuleTerminalJoinConf )
_body( TCnsInfo, 1 )
_ev_end

/***********************<< �뿪���� >>********************** 
*[��Ϣ��]
TTPMDLTERLABEL
*[��Ϣ����]
*  cns	  <- cncall
*/
_event(  ev_CnModuleterminalLeftConf )
_body( TCnsInfo, 1 )
_ev_end

/***********************<< cncԶң��Դ>>****************************
*					
*[��Ϣ����]
*  CNC	 ->  CNS
*/

_event(  ev_Cn_FeccChangeSrc_Cmd )
_body( TConfEpID, 1 )
_body( u8, 1 )
_ev_end

/***************<< cnc����Զң�����PTָ���cns>>*******************
*					
*[��Ϣ����]
*  CNC	  ->  CNS    CNS   ->   CNCALL
*/

_event(  ev_Cn_FeccCamPT_Cmd )
_body( TConfEpID, 1 )
_body( EmDirection, 1 )
_body( EmCnAction, 1 )
_ev_end
/******************<< cnc����Զң�Զ��۽�ָ���cns>>*******************
*					
*[��Ϣ����]
*  CNC	  ->  CNS    CNS   ->   CNCALL
*/

_event(  ev_Cn_FeccCamAutoFocus_Cmd )
_body( TConfEpID, 1 )
_ev_end
/******************<< cnc����Զң�۽�ָ���cns>>***********************
*					
*[��Ϣ����]
*  CNC	  ->  CNS    CNS   ->   CNCALL
*/

_event(  ev_Cn_FeccCamFocus_Cmd )
_body( TConfEpID, 1 )
_body( EmFocus, 1 )
_body( EmCnAction, 1 )
_ev_end
/******************<< cnc����ԶңZoom����ָ���cns>>***********************
*					
*[��Ϣ����]
*  CNC	  ->  CNS    CNS   ->   CNCALL
*/

_event(  ev_Cn_FeccCamZoom_Cmd )
_body( TConfEpID, 1 )
_body( EmZoom, 1 )
_body( EmCnAction, 1 )
_ev_end
/******************<< cnc����Զң���ȵ���ָ���cns>>***********************
*					
*[��Ϣ����]
*  CNC	  ->  CNS    CNS   ->   CNCALL
*/

_event(  ev_Cn_FeccCamBackLight_Cmd )
_body( TConfEpID, 1 )
_body( EmPanCamBright, 1 )
_body( EmCnAction, 1 )
_ev_end

#ifndef _MakeTpEventDescription_
   _ev_segment_end( outercnsh323conf )
};
#endif
#endif //TPP_EVENT_H
