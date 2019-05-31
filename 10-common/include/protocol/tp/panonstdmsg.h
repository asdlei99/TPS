#ifndef PANONSTDCOFMSG_H
#define PANONSTDCOFMSG_H
enum EmPAConfMsgType
{
	  emPAConfMsgTypeBegin = 0,

		emPAChanMsgBegin = 1,
		emPAConfFastUpdate,                 //NULL
		emPAConfFlowCtrl,                   //wBitRate
		emPAChanMeetingSpeaker,             //cns->ums �᳡�ڷ�����
		emPAChanSelecteCascad,              //add-by wuhu cns��umsָ��ѡ��, ���� u16,��ʾ�᳡id
		emPAChanSelecteCascadRes,           //ums�ظ�cnsѡ������� TPAChanSelecteCascadRes, ��ʾ���
    emPAChanSelecteCascadCancel,        //ȡ��ѡ�����޲���
		emPAChanSelecteCascadCancelRes,     //ȡ��ѡ�������  ����u32, ��ʾ��� 
		emPAChanSeeLocal,                   //ums -> cns, �����أ��޲���
		emPAChanSeeLocalCancel,             //ums -> cns  ȡ�������أ��޲���
		emPAChanMsgEnd = 160,

		emPAConfMsgBegin = 161,
		emPAConfYouAreSeeing,               //TYouAreSeeing ������ָʾ
		emPAConfBeChairman,                 //BOOL ums->cns ��Ϊ��ϯ
		emPAConfCascadingSpeaker,           //TPACascadingSpeaker �������� �����᳡�ڷ�����
		emPAConfStartPoll,                  //TPAPollCmd �������� ������ѯ
		emPAConfStartPollAck,               //TPAPollAck
		emPAConfPollNodeChange,             //TPAPollNodeChange ��������
		emPAConfEndPoll,                    //u32(Reserved)
		emPAConfPollFastUpdate,             //��������u32(Reserved)
		emPAConfStatusIndicate,             //TPAConfStatusInd , ums->cns
		emPAConfPeerMuteCmd,                //Զ������  TPAPeerMuteCmd
		emPAConfPeerMuteInd,                //Զ������״ָ̬ʾ TPAPeerMuteInd
		emPAConfCallCascadingOff,           //�����¼�δ���߻᳡ u16 epid
		emPAConfHangUpCascadingConf,        //�Ҷ��¼����� THangupCascadingConf
		emPAConfNodeUpdateTrList,           //֪ͨ���½����Ϣ TPAConfNodeUpdateTrList
		emPAConfNodeUpdateB2NewTrList,      //֪ͨ���½����Ϣ TPAConfNodeUpdateB2NEWTrList
		emPAConfNodeDelTrList,              //֪ͨɾ����� TPAConfNodeDelTrList
		emPAConfAudMixEpCmd,                //�ϼ�֪ͨ�¼�����ĳ���˵�  TPAAudMixEpCmdTr
		emPAConfAudMixEpAck,                // �¼�֪ͨ�ϼ�����ĳ���˵�Ľ�� TPAAudMixEpAckTr
		emPAConfAudMixEpStop,               // �ϼ���֪ͨ�¼�ֹͣĳ���˵�Ļ��� u16
		emPAConfAudMixOpenNCmd,             // �ϼ�֪ͨ�¼���Nģʽͨ�� TPAAudMixEpCmdTr
		emPAConfAudMixOpenNAck,             // �¼�֪ͨ�ϼ���Nģʽͨ�� TPAAudMixEpAckTr
		emPAConfPeerSoundOffCmd,            //Զ�˾��� TPAPeerMuteCmd
		emPAConfPeerSoundOffInd,            //Զ�˾���ָʾ TPAPeerMuteInd
		emPARequestDualStreamCmd,           //����˫�� TDualRequest
		emPARequestDualStreamInd,           //����˫��ָʾ BOOl + EmDualReason + TDualRequest
		emPASendDualStream,                 //��˫�� TDualInfo
		emPASendDualStreamAck,              //��˫����� TDualInfoAck
		emPAStopDualStream,                 //ֹͣ˫�� TPAEpKey
		emPADualStreamFastUpdate,           //˫���ؼ�֡���� BOOL32ֵ
		emPAViewLocal,                      //������ u32(Reserved)
		emPACancelViewlocal,                //ȡ�������� u32(Reserved)
		emPAStartRcvDualInd,                //����˫��ָʾTPAEpKey
		emPAStopRcvDualInd,                 //ֹͣ����˫��ָʾEmDualReason
		emPAAddTvMonitorCmd,                //����ǽ��� TPATvMonitorCmd 
		emPAAddTvMonitorInd,                //����ǽ��� TPATvMonitorInd 
		emPAStopMonitorCmd,	                //ֹͣ����ǽ�ļ��	u16
		emPAAskKeybyScreen,                 //ֹͣ����ǽ�ļ��	TPAAskKeyByScreenTr
		emPAPollDstNameInd,                 //֪ͨ��ѯĿ����Ϣ ,TPAPollDstName
		emPASrcDualNameInd,                 //֪ͨ˫��Դ��Ϣ TPAName
		emPAChairCapNotify,                 //֪ͨ�¼���ϯ��ϯ����
		emPAConfCnsList,                    // UMS��CNS���᳡�б�,   ������ TPAConfCnsList;
		emPAConfStartPolling,               //cns��ums������ѯ,  �޲��������贫���������u32ֵ
    emPAConfStartPollingRes,            //ums��Ӧcns��ѯ���, ������u32
		emPAConfClosePolling,               //cns��ums�ر���ѯ,   �޲��������贫���������u32ֵ
		emPAConfClosePollingRes,            //ums��cns��Ӧ�ر���ѯ���,  ���� u32
		emPAConfNotifyPollingRes,           //ums֪ͨcns��ǰ��ѯ���,   ���� BOOL32
		emPACascadeStartViewcmd,	          //�ϼ�֪ͨ�¼�ѡ��ĳ���᳡ TPAViewCmd
		emPACascadeStartViewInd,	          //�¼�֪ͨ�ϼ�ѡ��ĳ���᳡��� TPAViewAck
		emPACascadeStopView_cmd,	          //�ϼ�֪ͨ�¼�ֹͣĳ��ѡ��	u16
		emPACascadeGetVidcmd,	              //�ϼ������¼�ͼ�� TPAViewCmd
		emPACascadeGetVidInd,	              //�¼������¼�ͼ���� TPAViewAck
		emPACascadeStopGetVidcmd,	          //�ϼ�ֹ֪ͨͣ�¼�����	u16
		emPACascadeFlowCtrl,		            //�ϼ�֪ͨ�¼�flowctrl�� ����TPAFlowControl
		
		emPAOpenAudChanCmd,                 //����Ƶͨ��           TPAAudChanCmd
		emPAOpenAudChanAck,                 //����Ƶͨ��Ӧ��       TPAAudChanAck
		emPAOpenVidChanCmd,                 //����Ƶͨ��           TPAVidChanCmd
		emPAOpenVidChanAck,                 //����Ƶͨ��Ӧ��       TPAVidChanAck
		emPACloseVidChanCmd,                //�ر���Ƶͨ��           u16
		
		emPATpConfAMixUpdate_Cmd,           //�����鿪��           TPAConfAuxMixInfo
		emPATpConfAMixUpdate_Ind,           //�������Ӧ           TPAConfAuxMixInfo
		emPATpConfAMixUpdate_Nty,           //���������ۿ���֪ͨ   TPAConfAuxMixInfo
		
		emPATpConfApplySpeaker_Cmd,         //�������л�������     TPAConfEpID
		emPATpConfApplySpeaker_Ind,         //�������л������˻�Ӧ TPAConfEpID,  EmPATpApplySpeakerRet 
		emPATpConfApplySpeaker_Nty,         //�������л�������֪ͨ TPAConfEpID
		
		emPATpConfMute_Cmd,                 //���������Զ������      TPAConfEpID, BOOL,  TRUEָʾԶ��������FALSEȡ��Զ������
		emPATpConfMute_Ind,                 //���������Զ��������Ӧ  TPAConfEpID, BOOL,  TRUEָʾԶ��������FALSEȡ��Զ������
		emPATpConfMute_Nty,                 //���������Զ������֪ͨ  TPAConfEpID, BOOL,  TRUEָʾԶ��������FALSEȡ��Զ������

		emPATpConfQuiet_Cmd,                //���������Զ�˾���        TPAConfEpID, BOOL,  TRUEָʾԶ��������FALSEȡ��Զ������
		emPATpConfQuiet_Ind,		            //���������Զ�˾�����Ӧ    TPAConfEpID, BOOL,  TRUEָʾԶ��������FALSEȡ��Զ������
		emPATpConfQuiet_Nty,                //���������Զ�˾���֪ͨ    TPAConfEpID, BOOL,  TRUEָʾԶ��������FALSEȡ��Զ������
		
		emPATpConfStartDual_Cmd,            //������˫������          TPAConfEpID   
		emPATpConfStartDual_Ind,            //������˫������Ӧ��      TPAConfEpID,  EmPATPDualReason
		emPATpConfStopDual_Cmd,             //������ͣ˫������        TPAConfEpID
		emPATpConfStopDual_Ind,             //������ͣ˫������Ӧ��    TPAConfEpID,  EmPATPDualReason
		emPATpConfDualEp_Nty,               //������˫���᳡�㲥֪ͨ  TPAConfEpID

		emPATpInviteCnsByAlias_Cmd,         //��������ͨ�����������б��в����ڵĻ᳡          TPAAlias
		emPATpInviteCnsByAlias_Ind,         //��������ͨ�����������б��в����ڵĻ᳡��Ӧ      TPAAlias, EmPACnsCallReason
		emPATpInviteCnsByEpId_Cmd,          //��������ͨ�����ֺ����б��д��ڵĲ����߻᳡      u16 wEpId
		emPATpInviteCnsByEpId_Ind,          //��������ͨ�����ֺ����б��д��ڵĲ����߻᳡��Ӧ  u16 wEpId, EmPACnsCallReason
	
		emPATpHangupCns_Cmd,                 //���Ҷ�ָ���᳡         u16 wEpId
		emPATpHangupCns_Ind,                 //���Ҷ�ָ���᳡��Ӧ     u16 wEpId, EmPACnsCallReason
		emPATpHangupConf_Cmd,                //�Ҷϻ���                 �޲������贫���������u32ֵ
		
		emPATpUpdateConfTurnlist_Nty,        //��ѯ�б�֪ͨ           TPAConfTurnInfo
		emPATpCallEPResult_Ind,              //���н����           TPAConfCallEpAddr, EmPACnsCallReason,  
		emPATpChairConfInfo_Nty,             //֪ͨ��ϯ������Ϣ       TPAChairConfInfo
		emPATpAudMixStatus_Nty,              //�᳡��������״̬֪ͨ   TPAAudMixStat

		emPAAdjustFrameRate_Cmd,             //TPAAdjustFrameRate
		emPAAdjustVidRes_Cmd,                //TPAAdjustVidRes
		
		emPAUmsDiscussScreenStat_Notify,     //����ģʽ�еĻ᳡����Ҫ�յ�����״̬֪ͨ, TPADisScreenStat 
		emPAUmsCnsSpeakerIndxAdjust_Notify,  //TPACascadingSpeaker
		
		emPAUmsDiscussFastUpdate_Req,        /*����Դ�᳡ID������ţ��Ϳ���ͨ��AskKeyByScreen����Ŀ��᳡�ķ���������ؼ�֡
		                                        TPADisAskKeyFrame */
		emPAUmsAudMixDisListOpr_Cmd,         //CNC -> CNS -> UMS, TPADisListOpr
		emPAUmsAudMixDisListOpr_Ind,         //UMS -> CNS -> CNC, TPADisListOpr

		emPAUmsCascadeOpenChairChan_Cmd,     // UMS �������� ����ϯͨ������, TPACascadeOpenChanCmd
		emPAUmsCascadeOpenChairChan_Ack,     // UMS �������� ����ϯͨ��Ӧ��, TPACascadeOpenChanAck

		emPAUmsCommonReasonToUI_Ind,         // ��Ϣ����: ums -> cns -> cnc, ��Ϣ����: TPAUmsReasonInd

    emPAUmsConfRecPlayState_Nty,         // ���·���״̬, ��Ϣ����: TPAUmsUpRecPlayState
    emPAUmsConfStopRecPlay_Req,          // ֹͣ�¼��ķ����޲��������贫���������u32ֵ
		
		emPAChanResetFastUpdate,				     //ͨ����Ϣ������ȥ��ums�Ĺؼ�֡������u32
		emPAJoinWBConf_Cmd,						       //��Ϣ�壺U32 dwDsIPAddr
		emPAJoinWBConf_Ind,					         //��Ϣ�壺BOOL bIsSucc
		emPAHangupWBConf_Cmd,			          //��Ϣ�壺Null
};

#endif