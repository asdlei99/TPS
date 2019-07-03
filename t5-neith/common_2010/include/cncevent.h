/*****************************************************************************
ģ����      : cms����̨
�ļ���      : evCmsLib.h
����ļ�    : 
�ļ�ʵ�ֹ���: ������Ϣ����cms��UI���ֺ�lib��umclib �� cnclib�����ֹ�ͬʹ�ã�
����        : �����
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2011/4/23   1.0         �����      ����
*******************************************************************************/
#pragma once

#ifndef _EVCMSLIB_20110423_H_
#define _EVCMSLIB_20110423_H_

#include "msgIdDispatch.h"
#include "tpeventcomm.h"

/** @defgroup  cms ��Ϣ���岿��
 *  @{
 */

// �������̨�ڲ���Ϣ  

//#define CMS_MSG_BEGIN		WM_USER + 0x100


//umcLib����Ϣ����
enum EmUiUmcMsg
{

#define UI_UMC_MSG_BEGIN    CMS_MSG_BEGIN

	/************************************************************************/
	/** ����  UMS  
	wparam = BOOL  //�Ƿ����ӳɹ�
	lparam = errorCode*/
	/************************************************************************/
	ev_UIUMSConnected		=	UI_UMC_MSG_BEGIN,
#define	UI_UMS_CONNECTED    ev_UIUMSConnected
	
		
		/************************************************************************/
		/**�ѶϿ�UMS
		wParam = 0
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsDisconnected,
#define UI_UMS_DISCONNECTED	 ev_UIUmsDisconnected



        /************************************************************************/
		/**���˻��Ѿ�����һ���ط���¼
		wParam = u32_IP
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsGrabLoginNotify,
#define UI_UMS_GRAB_LOGIN_NOTIFY	 ev_UIUmsGrabLoginNotify

        /************************************************************************/
		/**UMS�Ĵ�����Ϣ֪ͨ
		wParam = TTPUmsReasonInd
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsReasonInd,
#define UI_UMS_UMSREASON_IND	 ev_UIUmsReasonInd
		

    	/************************************************************************/
		/** ums �����ʱ
		wParam = 0
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsCmdTimeout,
#define UI_UMS_CMD_TIMEOUT	 ev_UIUmsCmdTimeout


        /************************************************************************/
		/** ums ��¼�����ʱ
		wParam = 0
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsLoginTimeout,
#define UI_UMS_LOGIN_TIMEOUT	 ev_UIUmsLoginTimeout
	  
   
    	/************************************************************************/
		/** ����ģ���������ظ�
		wParam = 0
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsOperateConfTemplateRet,
#define UI_UMS_OPERATE_CONFTEMP_RET	 ev_UIUmsOperateConfTemplateRet

		/************************************************************************/
		/** ɾ��ȫ��ģ����ϢӦ��
		wParam = 0
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsDelAllConftempRet,
#define UI_UMS_DEL_ALL_CONFTEMP_RET	 ev_UIUmsDelAllConftempRet

		 /************************************************************************/
		 /**	����ģ�����֪ͨ
			wParam = confTempID  //��������Ļ���ģ��ID��ɾ��ʱΪ��һ��Ҫɾ����ģ��ID
			lparam = 0*/
		/************************************************************************/ 
        ev_UIUmsRefreshConfTemplateList ,
#define UI_UMS_REFRESH_CONFTEMPLATE_LIST  ev_UIUmsRefreshConfTemplateList



    	/************************************************************************/
		/** �û���������ظ�
		wParam = 0
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsOperateUserRet,
#define UI_UMS_OPERATE_USER_RET	 ev_UIUmsOperateUserRet


		 /************************************************************************/
		 /**	�û�����֪ͨ
			wParam = 0
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRefreshUserList  ,
#define UI_UMS_REFRESH_USER_LIST ev_UIUmsRefreshUserList


        /************************************************************************/
		 /**	���»����б�
			wParam = 0
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRefreshConfList   ,
#define UI_UMS_REFRESH_CONF_LIST ev_UIUmsRefreshConfList 



	    /************************************************************************/
		 /**	��������ظ�
			wParam = confTemplateID 
			lparam =  errorCode*/
		/************************************************************************/ 
	    ev_UIUmsStartConfTemplateRsp  ,
#define UI_UMS_START_CONFTEMPLATE_RSP ev_UIUmsStartConfTemplateRsp
        

		/************************************************************************/
		 /**	����cns���ظ�
			wParam = strCnsInfoE164/alias 
			lparam =  errorCode*/
		/************************************************************************/ 
	    ev_UIUmsInviteCnsRsp  ,
#define UI_UMS_INVITE_CNS_RSP ev_UIUmsInviteCnsRsp


        /************************************************************************/
		 /**���÷����˽��
			wParam = confID 
			lparam =  EmTpApplySpeakerRet*/
		/************************************************************************/ 
	    ev_UIUmsSetSpeakerRsp  ,
#define UI_UMS_SET_SPEAKER_IND ev_UIUmsSetSpeakerRsp


        /************************************************************************/
		 /**�����������
			wParam = confID 
			lparam =  bStart*/
		/************************************************************************/ 
	    ev_UIUmsSetMuteCnsRsp  ,
#define UI_UMS_SET_MUTE_CNS_RSP ev_UIUmsSetMuteCnsRsp


        /************************************************************************/
		 /**���þ������
			wParam = confID 
			lparam =  bStart*/
		/************************************************************************/ 
	    ev_UIUmsSetQuietCnsRsp  ,
#define UI_UMS_SET_QUIET_CNS_RSP ev_UIUmsSetQuietCnsRsp


        /************************************************************************/
		 /**����˫�����
			wParam = confID 
			lparam =  bStart*/
		/************************************************************************/ 
	    ev_UIUmsSetDualCnsRsp  ,
#define UI_UMS_SET_DUAL_CNS_RSP ev_UIUmsSetDualCnsRsp


        /************************************************************************/
		 /** ˫��Դ�ı�֪ͨ
			wParam = confID 
			lparam =  cnsID*/
		/************************************************************************/ 
	    ev_UIUmsDualCnsNotify,
#define UI_UMS_DUAL_CNS_NOTIFY ev_UIUmsDualCnsNotify

 
         /************************************************************************/
		 /**	���·�����֪ͨ
			wParam = confID
			lparam = speakerID*/
		/************************************************************************/ 
	    ev_UIUmsChangeSpeakerNotify,
#define UI_UMS_CHANGE_SPEAKER_NOTIFY ev_UIUmsChangeSpeakerNotify


            /************************************************************************/
		 /**	��ϯ
			wParam = confID  �¼�����ID
			lparam = */
		/************************************************************************/ 
	    ev_UIUmsChairCnsNotify,
#define UI_UMS_CHAIR_CNS_NOTIFY ev_UIUmsChairCnsNotify



    /************************************************************************/
		 /**	��������֪ͨ
			wParam = confID  �¼�����ID
			lparam = */
		/************************************************************************/ 
	    ev_UIUmsCascadeConfNotify,
#define UI_UMS_CASCADE_CONF_NOTIFY ev_UIUmsCascadeConfNotify



        /************************************************************************/
		 /**	�Ҷϻ���ظ�
			wParam = confID 
			lparam = errorCode*/
		/************************************************************************/ 
	    ev_UIUmsHangupConfRsp ,
#define UI_UMS_HANGUP_CONF_RSP ev_UIUmsHangupConfRsp


		/************************************************************************/
		 /**	���»����еĻ᳡�б�
			wParam = confID
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRefreshConfCnsList  ,
#define UI_UMS_REFRESH_CONFCNS_LIST ev_UIUmsRefreshConfCnsList

 
		/************************************************************************/
		 /**	���»����еĻ᳡�б�
			wParam = confID
			lparam =  TConfCnsInfo*/
		/************************************************************************/ 
	    ev_UIUmsUpdateConfCnsList  ,
#define UI_UMS_UPDATE_CONFCNS_LIST ev_UIUmsUpdateConfCnsList
 

		/************************************************************************/
		 /**	���»��� 
		 
		/************************************************************************/ 
	    ev_UIUmsUpdateConfInfo  ,
#define UI_UMS_UPDATE_CONFINFO ev_UIUmsUpdateConfInfo


		/************************************************************************/
		 /**	���»����еĻ����б�
			wParam = confID
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRefreshConfAudMixList  ,
#define UI_UMS_REFRESH_CONFAUDMIX_LIST ev_UIUmsRefreshConfAudMixList

        /************************************************************************/
		 /** ���»����еĻ����б�-- ����cns���ڻ���
			wParam = confID
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRefreshConfAudMixListLocal  ,
#define UI_UMS_REFRESH_CONFAUDMIX_LIST_LOCAL ev_UIUmsRefreshConfAudMixListLocal

		/************************************************************************/
		 /**	���»�������ѯ�б�
			wParam = confID
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRefreshConfPollList  ,
#define UI_UMS_REFRESH_CONFPOLL_LIST ev_UIUmsRefreshConfPollList


 	/************************************************************************/
		 /** umsע���������Ϣ֪ͨ
			wParam = 0
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRegInfoNotify  ,
#define UI_UMS_REG_INFO_NOTIFY ev_UIUmsRegInfoNotify


  	/************************************************************************/
		 /**	umsע����������
			wParam = EmTpCnsRegUms:ע�᷵�صĴ�����
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRegServRsp  ,
#define UI_UMS_REG_SERV_RSP ev_UIUmsRegServRsp


	/************************************************************************/
		 /**	umsIP
			wParam = EmTpCnsRegUms: 
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsEthnetInfoNotify  ,
#define UI_UMS_ETHNETINFO_NOTIFY ev_UIUmsEthnetInfoNotify

       
        /************************************************************************/
		/**	 ϵͳʱ��֪ͨ
		/************************************************************************/ 
	    ev_GetUmsSystimeNotify  ,
#define UI_GET_UMS_SYSTIME  ev_GetUmsSystimeNotify


        /************************************************************************/
		/**	 �����ж�֪ͨ
		/************************************************************************/ 
	    ev_HungUp_Conf_Reason,
#define UI_HUNGUP_UMS_CONF_REASON  ev_HungUp_Conf_Reason


        /************************************************************************/
		/**	 ����ǽ���֪ͨ
             To Umc
		/************************************************************************/ 
        ev_Tvw_HduPlanNotify,
#define UI_UMS_HDUPLAN_NOTIFY  ev_Tvw_HduPlanNotify

        /************************************************************************/
		/**	 ���»���ģ����Դռ�����
             To Umc
		/************************************************************************/ 
        ev_ConfTmp_ResUsedCountNotify,
#define UI_UMS_CONFTMPRESUSEDCOUNT_NOTIFY  ev_ConfTmp_ResUsedCountNotify
         /************************************************************************/
		 /**	����������ӻ᳡��Ϣ����
			wParam = NULL
			lparam = EmDisListOprReslt*/
		/************************************************************************/ 
	    ev_UIAudMixDisListOprInd,
#define UI_UMS_AUDMIX_DISLISTOPR_IND ev_UIAudMixDisListOprInd
        /************************************************************************/
		 /**	������������������������
			wParam = BOOL
			lparam = NULL*/
		/************************************************************************/ 
	    ev_UIAudExcitationVisibleInd,
#define UI_UMS_AUDEXCITATION_VISIBLE_IND ev_UIAudExcitationVisibleInd
         /************************************************************************/
		 /**	������������
			wParam = NULL
			lparam = TConfAuxMixVacOpr*/
		/************************************************************************/ 
	    ev_UIAuxMixVacOprInd,
#define UI_UMS_AUDMIXVAC_IND ev_UIAuxMixVacOprInd
		/************************************************************************/
		 /** ������������ind ���ڽ���֪ͨʧ��ԭ��
			wParam = NULL
			lparam = TConfAuxMixVacOpr*/
		/************************************************************************/ 
	    ev_UIAMixUpdateInd,
#define UI_UMS_AUDMIXIND ev_UIAMixUpdateInd

		ev_UIUmsEnd,
#define UI_UMS_MSG_END  ev_UIUmsEnd
		
} ;


//cncLib����Ϣ����
enum EmUiCnsMsg
{

#define UI_CNC_MSG_BEGIN  	UI_UMS_MSG_END + 0x1 

	/************************************************************************/
	/** ����  CNS 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UICnsConnect	= UI_CNC_MSG_BEGIN,
#define	UI_CNS_CONNECTED  ev_UICnsConnect
	
	/************************************************************************/
	/** �ѶϿ�CNS
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UICnsDisconnected,
#define UI_CNS_DISCONNECTED	 ev_UICnsDisconnected

   /************************************************************************/
	/** ��¼CNS ���ջظ���ʱ
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UICnsLoginTimeOut,
#define UI_CNS_LOGIN_TIMEOUT	 ev_UICnsLoginTimeOut
		 
    
	/************************************************************************/
	/**	���µ�ַ��
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UIAddrbookChanged,
#define UI_CNS_ADDRBOOK_CHANGED		ev_UIAddrbookChanged

	/************************************************************************/
	/**	��ַ�������Ŀ֪ͨ
		wParam = EntryIndex
		lparam = 0*/
	/************************************************************************/ 
	ev_UIAddrbookAddEntry,
#define	UI_CNS_ADDRBOOK_ADDENTRY    ev_UIAddrbookAddEntry

	/************************************************************************/
	/**	��ַ�������Ŀ���޸ġ�ɾ����Ŀ֪ͨ
		wParam = EntryIndex
		lparam = 0*/
	/************************************************************************/ 
	ev_UIAddrbookAddGroup,
#define	UI_CNS_ADDRBOOK_ADDGROUP    ev_UIAddrbookAddGroup

	ev_UIAddrbookModify,
#define	UI_CNS_ADDRBOOK_MODIFY      ev_UIAddrbookModify

    ev_UIAddrbookDelete,
#define	UI_CNS_ADDRBOOK_DELETE      ev_UIAddrbookDelete

    /************************************************************************/
	/**	��ַ������ʧ��֪ͨ
		wParam = EntryIndex
		lparam = 0*/
	/************************************************************************/ 
    ev_UIAddrbookOptFailed,
#define	UI_CNS_ADDRBOOKOPT_FAILED      ev_UIAddrbookOptFailed

	/************************************************************************/
	/**	CNS��Ϣ
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsInfoNotify,
#define	UI_CNS_CNSINFO_NOTIFY       ev_UICnsInfoNotify

	/************************************************************************/
	/**	����״̬
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsConfStateNotify,
#define	UI_CNS_CONFSTATE_NOTIFY     ev_UICnsConfStateNotify

	/************************************************************************/
	/**	ȫ������/����״̬
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsAllMuteAndAllQuiteStateNotify,
#define	UI_CNS_ALLMUTE_ALLQUITE_NOTIFY     ev_UICnsAllMuteAndAllQuiteStateNotify

	/************************************************************************/
	/**	cns �뿪����
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsLeaveConfNotify,
#define	UI_CNS_LEAVECONF_NOTIFY     ev_UICnsLeaveConfNotify


 	/************************************************************************/
	/** ��״̬֪ͨ
	wParam = screenID
	lparam = emScreenState  
	/************************************************************************/
	ev_UiScreenStateNotify,
#define UI_CNS_SCREEN_STATE_NOTIFY  ev_UiScreenStateNotify

	/************************************************************************/
	/** ����֪ͨ
	wParam = screenID
	lparam = cstringCnsName */
	/************************************************************************/
	ev_UiScreenNameNotify,
#define UI_CNS_SCREEN_NAME_NOTIFY   ev_UiScreenNameNotify

	/************************************************************************/
	/** ����ѡ���ظ�
	wParam = screenID
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsSelViewInd,
#define UI_CNS_SEL_VIEW_IND   ev_UiCnsSelViewInd


    /************************************************************************/
	/** ѡ��֪ͨ
	wParam = screenID
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsCancleSelViewNty,
#define UI_CNS_SEL_VIEW_NTY   ev_UiCnsCancleSelViewNty

    /************************************************************************/
	/** ������ѯ�ظ�
	wParam =  bSucess
	lparam = emReslut */
	/************************************************************************/
	ev_UiCnsStartPollRsp,
#define UI_CNS_START_POLL_RSP   ev_UiCnsStartPollRsp


    /************************************************************************/
	/** ��ѯ״̬֪ͨ
	wParam =  bPoll
	lparam = 0 */
	/************************************************************************/
	ev_UiCnsPollStateNty,
#define UI_CNS_POLL_STATE_NOTIFY   ev_UiCnsPollStateNty


        /************************************************************************/
	/** ��Ե����Ҷ�֪ͨ
	wParam =  bPoll
	lparam = 0 */
	/************************************************************************/
	evUiCnsHungupP2pNty,
#define UI_CNS_HUNGUP_P2P_NOTIFY   evUiCnsHungupP2pNty

   /************************************************************************/
	/** ����˫���ظ�
	wParam =  bStart
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsStartDualRsp,
#define UI_CNS_START_DUAL_RSP   ev_UiCnsStartDualRsp

	/************************************************************************/
	/** ˫��״̬֪ͨ
	wParam =  bStart
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsDualStateNty,
#define	UI_CNS_DUAL_STATE_NOTIFY   ev_UiCnsDualStateNty

	
   	/************************************************************************/
	/** ˫��״̬֪ͨ
	wParam =  bStart
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsRecvDualNty,
#define	UI_CNS_RECV_DUAL_NOTIFY   ev_UiCnsRecvDualNty

    /************************************************************************/
	/** ˫��������Կ֪ͨ
	/************************************************************************/
    ev_UiCnsRecvDualKeyNty,
#define UI_CNS_DUAL_KEY_NOTIFY   ev_UiCnsRecvDualKeyNty

    	/************************************************************************/
	/** ����˫��ʱ�쳣�ж�
 
	/************************************************************************/
	ev_UiRecvDualInterruptNty,
#define	UI_RECV_DUAL_INTERRUPT   ev_UiRecvDualInterruptNty

	/************************************************************************/
	/** ������ϯ
	wParam = seatID
	lparam =  0 */
	/************************************************************************/
	ev_UiSpokesSeatNotify,
#define UI_CNS_SPOKES_SEAT_NOTIFY   ev_UiSpokesSeatNotify

	/************************************************************************/
	/* ��������֪ͨ  
	wparam = bQuite 	�Ǿ�����������.TRUE ������ FALSE ����
	lparam = bOn		�ǿ������ǹر�.��������ʹ��ǰû����Ƶ���,��֮�ǹرվ���*/
	/************************************************************************/
	ev_UiCnsQuiteMute,
#define UI_CNS_QUITE_MUTE           ev_UiCnsQuiteMute

	/************************************************************************/
	/* ������������֪ͨ  
	wparam = 0 	
	lparam = 0		
	/************************************************************************/
	ev_UiCnsInVolUpdate,
#define	UI_CNS_INVOL_UPDATE         ev_UiCnsInVolUpdate

	/************************************************************************/
	/* ���������֪ͨ  
	wparam = 0 	
	lparam = 0		
	/************************************************************************/
	ev_UiCnsOutVolUpdate,
#define	UI_CNS_OUTVOL_UPDATE        ev_UiCnsOutVolUpdate      
    
	/************************************************************************/
	/**	Sipע����Ϣ
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UIRegSipNotify,
#define	UI_CNS_REGSIP_NOTIFY       ev_UIRegSipNotify

	/************************************************************************/
	/**	Sipע���Ƿ�ɹ�
		wParam = BOOL
		lparam = �᳡��*/
	/************************************************************************/ 
	ev_UIRegSipResultNotify,
#define	UI_CNS_REGRESULT_NOTIFY       ev_UIRegSipResultNotify

	/************************************************************************/
	/**	Sipע������ظ�֪ͨ
		wParam = BOOL
		lparam = �᳡��*/
	/************************************************************************/ 
	ev_UIRegSipAliasRepeatNotify,
#define	UI_CNS_SIPREG_ALIASREPEAT_NOTIFY       ev_UIRegSipAliasRepeatNotify

    /************************************************************************/
	/**	�õ�GKע����
	 
	/************************************************************************/ 
	ev_UIRegGkResultRsp,
#define	UI_CNS_REG_GK_RSP       ev_UIRegGkResultRsp


     /************************************************************************/
	/**	������֪ͨ GKע����Ϣ
	 
	/************************************************************************/ 
	ev_UIRegGkNty,
#define	UI_CNS_REG_GK_NTY       ev_UIRegGkNty


	/**	������Ϣ֪ͨ
		wParam = 0
		lparam = 0*/
	/************************************************************************/
	ev_UICnsEthnetInfoNotify,
#define	UI_CNS_ETHNETINFO_NOTIFY       ev_UICnsEthnetInfoNotify

    /**	��������֪ͨ
		wParam = 0
		lparam = 0*/
	/************************************************************************/
	ev_UICnsIPVTypeNotify,
#define	UI_CNS_IPVTYPE_NOTIFY       ev_UICnsIPVTypeNotify

	/**	IPV6����֪ͨ
		wParam = 0
		lparam = 0*/
	/************************************************************************/
	ev_UICnsIPV6CfgNotify,
#define	UI_CNS_IPV6CFG_NOTIFY       ev_UICnsIPV6CfgNotify
	
	/************************************************************************/
	/**	���᳡��֪ͨ
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsMainRoomInd,
#define	UI_CNS_MAINROOM_NOTIFY       ev_UICnsMainRoomInd

	/************************************************************************/
	/**	�᳡����֪ͨ
		wParam = �᳡��
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsRoomOffline,
#define UI_CNS_ROOMOFFLINE           ev_UICnsRoomOffline

    /************************************************************************/
	/**	ϵͳʱ��ظ�
		wParam = TTpTime
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsSystimeRsp,
#define UI_CNS_SYSTIME_RSP           ev_UICnsSystimeRsp

	/************************************************************************/
	/**	Cns�᳡�б�
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsCnListNty,
#define	UI_CNS_CNLIST_NOTIFY         ev_UICnsCnListNty

	/************************************************************************/
	/**	����CNS�᳡֪ͨ
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsInsConnect,
#define	UI_CNSINS_CONNECTED          ev_UICnsInsConnect
 
	/************************************************************************/
	/**	����˫�������ظ�
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsStartDualCdStrmRsp,
#define	UI_CNSINS_START_DUALCODESTREAM_RSP          ev_UICnsStartDualCdStrmRsp   

	/************************************************************************/
	/**	ѡ��˫�������ظ�
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsScrnDisplayDualRsp,
#define	UI_CNS_SCRN_DISPLAY_DUAL_RSP          ev_UICnsScrnDisplayDualRsp  
    

    /************************************************************************/
	/**	ȡ��ѡ��˫�������ظ�
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsStopScrnDisplayDualRsp,
#define	UI_CNS_STOP_SCRN_DISPLAY_DUAL_RSP          ev_UICnsStopScrnDisplayDualRsp  
	
   /************************************************************************/
	/**	���� �ظ�
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsScrnDisplayLocalRsp,
#define	UI_CNS_SCRN_DISPLAY_LOCAL_RSP          ev_UICnsScrnDisplayLocalRsp  

    /************************************************************************/
	/**ȡ��	���� �ظ�
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsStopScrnDisplayLocalRsp,
#define	UI_CNS_STOP_SCRN_DISPLAY_LOCAL_RSP          ev_UICnsStopScrnDisplayLocalRsp  

	/************************************************************************/
	/**˫��Դ����֪ͨ
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsRoomDualOfflineNty,
#define UI_CNS_DUALOFFLINE_NOTIFY         ev_UICnsRoomDualOfflineNty

	/************************************************************************/
	/**���»���ģ��֪ͨ
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsRefreshConfTemplateList,
#define UI_CNS_REFRESH_CONFTEMPLATE_LIST         ev_UICnsRefreshConfTemplateList

	/************************************************************************/
	/**���»���ģ��֪ͨ
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsRefreshGlobalAddrbook,
#define UI_CNS_REFRESH_GLOBAL_ADDRBOOK         ev_UICnsRefreshGlobalAddrbook

	/************************************************************************/
	/**���»���ģ��֪ͨ
		wParam =  BOOL : ��ʾ�Ƿ���sip��ַ 
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsRefreshGlobalAddrbookEx,
#define UI_CNS_REFRESH_GLOBAL_ADDRBOOKEX       ev_UICnsRefreshGlobalAddrbookEx

    /************************************************************************/
	/**˫��Դ��Ϣ֪ͨ
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
    ev_UICnsVgaInfoNty,
#define UI_CNS_VGAINFO_NOTIFY                  ev_UICnsVgaInfoNty

    /************************************************************************/
	/**������˫��Դ��Ϣ֪ͨ
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
    ev_UICnsConfVgaInfoNty,
#define UI_CNS_CONFVGAINFO_NOTIFY              ev_UICnsConfVgaInfoNty

    /************************************************************************/
	/**�������л�˫��Դ֪ͨ
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
    ev_UICnsSelDualInputPortInd,
#define UI_CNS_SELDUALPORT_IND                 ev_UICnsSelDualInputPortInd

	    /************************************************************************/
	/**���ڻ������л�˫��Դ֪ͨ
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
    ev_UICnsSelDefaultDualInputPortInd,
#define UI_CNS_SELDEFAULTDUALPORT_IND                 ev_UICnsSelDefaultDualInputPortInd
	/************************************************************************/
	/**	������֪ͨ ��̬NATע����Ϣ
	 
	/************************************************************************/ 
	ev_UIRegNatNty,
#define	UI_CNS_REG_NAT_NTY       ev_UIRegNatNty


	/************************************************************************/
	/**  ���������б�ҳ����޸����ܵ�ǰѡ�����ݷ���
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiCnsNetMngSelDataClick,
#define UI_CNS_MSG_NETMNGSELDATA_Click  ev_UiCnsNetMngSelDataClick
	/************************************************************************/
	/**  ϵͳ����ҳ����Ϣ֪ͨ
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiCnsSleepInfoNotify,
#define UI_CNS_SLEEPINFO_NOTIFY  ev_UiCnsSleepInfoNotify

    /************************************************************************/
	/**  �п��¶�֪ͨ
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSchTempNotify,
#define UI_CNS_SCHTEMP_NTY  ev_UiCnsSchTempNotify
    /************************************************************************/
	/**  �пصƹ�֪ͨ
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSchLightNotify,
#define UI_CNS_SCHLIGHT_NTY  ev_UiCnsSchLightNotify
    /************************************************************************/
	/**  �п����״̬֪ͨ
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSchStateNotify,
#define UI_CNS_SCHSTATE_NTY  ev_UiCnsSchStateNotify
    /************************************************************************/
	/**  ϵͳ��Դ���ػظ�
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSchPowerInd,
#define UI_CNS_SCHPOWER_IND  ev_UiCnsSchPowerInd
     /************************************************************************/
    /**  �ƹ⿪�ػظ�
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSchAllLightInd,
#define UI_CNS_SCHALLLIGHT_IND  ev_UiCnsSchAllLightInd
    /************************************************************************/
	/**  ���ƿ��ػظ�
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSchMidLightInd,
#define UI_CNS_SCHMIDLIGHT_IND  ev_UiCnsSchMidLightInd
    /************************************************************************/
	/**  ���ƿ��ػظ�
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSchScrLightInd,
#define UI_CNS_SCHSCRLIGHT_IND  ev_UiCnsSchScrLightInd
    /************************************************************************/
	/**  ���ӻ�״̬֪ͨ
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsTVStateNotify,
#define UI_CNS_TVSTATE_NTY  ev_UiCnsTVStateNotify
    /************************************************************************/
	/**  ���ӻ����ػظ�
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSeleteTvInd,
#define  UI_CNS_SELETETV_IND ev_UiCnsSeleteTvInd
    /************************************************************************/
	/**  ���ӻ�ѡ��״̬�ظ�
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsTVPowerModeInd,
#define  UI_CNS_TVPOWERMODE_IND ev_UiCnsTVPowerModeInd
    /************************************************************************/
	/**  �ĵ������״̬֪ͨ
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsDCamStateNotify,
#define UI_CNS_DCAMSTATE_NTY  ev_UiCnsDCamStateNotify
	    /************************************************************************/
	/**  �ĵ������Ԥ��λѡ��״̬֪ͨ
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsDCamPreposInd,
#define UI_CNS_DCAMPREPOS_IND  ev_UiCnsDCamPreposInd
    /************************************************************************/
	/**  �ĵ������ѡ���л��ظ�
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsDCamSelectedInd,
#define UI_CNS_DCAMSELECTED_IND  ev_UiCnsDCamSelectedInd
    /************************************************************************/
	/**  �ĵ���������ػظ�
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsDCamPowerInd,
#define UI_CNS_DCAMPOWER_IND  ev_UiCnsDCamPowerInd
    /************************************************************************/
	/**  �ĵ���������ջظ�
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsDocSnapShotInd,
#define UI_CNS_DOCSNAPSHOT_IND  ev_UiCnsDocSnapShotInd
	/************************************************************************/
	/**  �ĵ�������ͺ�֪ͨ
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsDCamTypeInd,
#define UI_CNS_DCAMTYPE_IND  ev_UiCnsDCamTypeInd
	    /************************************************************************/
	/**  �ĵ�����zoom�ظ�
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsDCamZoomInd,
#define UI_CNS_DCAMZOOM_IND  ev_UiCnsDCamZoomInd
    /************************************************************************/
	/**  �յ�״̬֪ͨ
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsACStateNotify,
#define UI_CNS_ACSTATE_NTY  ev_UiCnsACStateNotify

	/************************************************************************/
	/**  �յ�ѡ����ظ�
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSelectAirInd,
#define  UI_CNS_SELECTAIR_IND ev_UiCnsSelectAirInd
	/************************************************************************/
	/**  �յ�ȫ��Ӧ�ÿ��������ظ�
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsApplyToAllInd,
#define  UI_CNS_APPLYTOALL_IND ev_UiCnsApplyToAllInd

	/************************************************************************/
	/**  �յ���Դ����״̬֪ͨ
	wParam = *   
	lparam = */
	/************************************************************************/
     ev_UiCnsACPowerStateInd,
 #define UI_CNS_ACPOWERSTATE_IND  ev_UiCnsACPowerStateInd
    /************************************************************************/
	/**  �пش���֪ͨ
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiTPadCentreSleepNotify,
#define UI_TPAD_CENTRESLEEP_NTY  ev_UiTPadCentreSleepNotify

    /************************************************************************/
	/**  TPad��¼�û�֪ͨ
	wParam = User*   
	lparam = */
	/************************************************************************/
    ev_UiTPadLoginUserNotify,
#define UI_TPAD_LOGINUSER_NOTIFY  ev_UiTPadLoginUserNotify

    /************************************************************************/
	/**  TPadϵͳ����֪ͨ
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiTPadUpdateSystemCmd,
#define UI_TPAD_UPDATESYS_CMD  ev_UiTPadUpdateSystemCmd

    /************************************************************************/
	/**  UMS�Ĵ�����Ϣ֪ͨ
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiUmsReason_Ind,
#define UI_CNS_UMSREASON_IND   ev_UiUmsReason_Ind

    /************************************************************************/
	/**  cnc����ϵͳ�����޸�֪ͨ  dyy 2013��8��29��
	wParam = ϵͳ����   
	lparam = */
	/************************************************************************/
    ev_UiTPadCncSetSysNameNotify,
#define UI_TPAD_SETSYSNAME  ev_UiTPadCncSetSysNameNotify

    /************************************************************************/
	/**  TPad Home����Ӧ
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiTPadHomeKeyNotify,
#define UI_TPAD_HOMEKEY_NOTIFY  ev_UiTPadHomeKeyNotify

    /************************************************************************/
	/**  cnc����״̬֪ͨ  
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiTPadConfStateNty,
#define UI_CONFSTATE_NTY  ev_UiTPadConfStateNty

    /************************************************************************/
	/**  ����pc˫���Ľ�� 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiTPadFileDualResult,
#define UI_FILE_DUAL_RESULT  ev_UiTPadFileDualResult

    /************************************************************************/
	/**  ����pc˫��Զ�˵�ַ 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiTPadFileDualRcvAddr,
#define UI_FILE_DUAL_RCVADDR  ev_UiTPadFileDualRcvAddr

    /************************************************************************/
	/**  ֹͣpc˫�� 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiTPadStopFileDual,
#define UI_FILE_DUAL_STOP  ev_UiTPadStopFileDual

    /************************************************************************/
	/**  pc˫��key��֪ͨ 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiTPadFileDualkey,
#define UI_FILE_DUAL_KEY  ev_UiTPadFileDualkey

    /************************************************************************/
	/**  Զ������ؼ�֡ 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiTPadFileKeyFrame,
#define UI_FILE_DUAL_KEYFRAME_REQ  ev_UiTPadFileKeyFrame

	/************************************************************************/
	/** ����ѡ������ǽ�ظ�
	wParam = screenID
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsSelTVSViewRsp,
#define UI_CNS_SEL_TVSVIEW_RSP   ev_UiCnsSelTVSViewRsp


    /************************************************************************/
	/** ȡ��ѡ������ǽ�ظ�
	wParam = screenID
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsCancleSelTVSViewRsp,
#define UI_CNS_CANCLE_SEL_TVSVIEW_RSP   ev_UiCnsCancleSelTVSViewRsp

    /************************************************************************/
	/** ������ϯ֪ͨ
	wParam = 
	lparam =  */
	/************************************************************************/
	ev_UiCnsChairConfInfoNty,
#define UI_CNS_CHAIRCONFINFO_NTY   ev_UiCnsChairConfInfoNty

	/************************************************************************/
	/**  ����ƵԴ������Ӧ
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnSetVedioInfoInd,
#define UI_CNS_SETMAINVEDIO_IND  ev_UiCnSetVedioInfoInd
	/************************************************************************/
	/**  ȫ���������Ϣ֪ͨ
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnPanCamInfoNty,
#define UI_CNS_PANCAMINFO_NTY  ev_UiCnPanCamInfoNty
		/************************************************************************/
	/**  ȫ�����������Ԥ��λ֪ͨ
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnPanCamPresetSaveInd,
#define UI_CNS_PANCAMPRESETSAVE_IND  ev_UiCnPanCamPresetSaveInd
	/************************************************************************/
	/**  ȫ�������ɾ��Ԥ��λ֪ͨ
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnPanCamPresetDeleteInd,
#define UI_CNS_PANCAMPRESETDEL_IND  ev_UiCnPanCamPresetDeleteInd
	/************************************************************************/
	/**  ȫ�����������Ԥ��λ֪ͨ
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnPanCamPresetImpleInd,
#define UI_CNS_PANCAMPRESETIMPLE_IND  ev_UiCnPanCamPresetImpleInd
	/************************************************************************/
	/**  ȫ�������Ԥ��λ���Ʊ�����֪ͨ
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnPanCamPresetNameSaveInd,
#define UI_CNS_PANCAMPRESETNAMESAVE_IND  ev_UiCnPanCamPresetNameSaveInd
	/************************************************************************/
	/**  ȫ�������ѡ��֪ͨ
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnPanCamSelInd,
#define UI_CNS_PANCAMSEL_IND  ev_UiCnPanCamSelInd

		/************************************************************************/
	/** ȫ��������������֪ͨ
	wParam = screenID
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsPanCamStartRsp,
#define UI_CNS_PANCAMSTART_RSP   ev_UiCnsPanCamStartRsp

    /************************************************************************/
	/** ����ϳ���״̬֪ͨ
	wParam = 
	lparam =  */
	/************************************************************************/
    ev_UiCnsBrdVmpNty,
#define UI_CNS_BRDVMP_NTY        ev_UiCnsBrdVmpNty

    /************************************************************************/
	/** ռ�û���ϳ����ظ�
	wParam = 
	lparam =  */
	/************************************************************************/
    ev_UiCnsRervesBrdVmpInd,
#define UI_CNS_RERVESBRDVMP_IND  ev_UiCnsRervesBrdVmpInd

    /************************************************************************/
	/** ���滭��ϳ�Ԥ���ظ�
	wParam = 
	lparam =  */
	/************************************************************************/
    ev_UiCnsSaveVmpCfgInd,
#define UI_CNS_SAVEVMPCFG_IND        ev_UiCnsSaveVmpCfgInd

    /************************************************************************/
	/**  ����ǽ֪ͨ
	wParam =    
	/************************************************************************/
    ev_UiHduPlanNty,
#define UI_HDUPLAN_NTY  ev_UiHduPlanNty
	/************************************************************************/
	/**  ����ǽ�໭���������
	wParam =    
	/************************************************************************/
    ev_UiHduChangModeInd,
#define UI_HDUCHANGEMODE_IND  ev_UiHduChangModeInd
	/************************************************************************/
	/**  ����ǽ������������
	wParam =    
	/************************************************************************/
    ev_UiHduVolumeInd,
#define UI_HDUVOLUME_IND  ev_UiHduVolumeInd

	/************************************************************************/
	/**  ����ǽֹͣ�ۿ�
	wParam =    
	/************************************************************************/
    ev_UiHduStopPlayInd,
#define UI_HDUSTOPPLAY_IND  ev_UiHduStopPlayInd
	/************************************************************************/
	/**  ����ǽֹͣ�ۿ�
	wParam =    
	/************************************************************************/
    ev_UiHduPlayInd,
#define UI_HDUPLAY_IND  ev_UiHduPlayInd


    /************************************************************************/
	/** TPad�����п�
	wParam = 
	lparam =  */
	/************************************************************************/
    ev_UiTpadShowCenterCtrlNty,
#define UI_TPAD_SHOWCENTRECTRL_NTY        ev_UiTpadShowCenterCtrlNty
	/************************************************************************/
	/** ����ʱ˫��ind
	wParam = screenID
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsSpareDualInd,
#define UI_CNS_SPAREDUAL_IND   ev_UiCnsSpareDualInd
	/************************************************************************/
	/** ����ʱ˫��NTY
	wParam = screenID
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsSpareDualNty,
#define UI_CNS_SPAREDUAL_NTY   ev_UiCnsSpareDualNty
	/************************************************************************/
	/**  ��ƵԴ״̬֪ͨ
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnVidSrcNty,
#define UI_CNS_VIDSRC_NTY  ev_UiCnVidSrcNty
	/************************************************************************/
	/** ��������cns��������IND
	wParam = bIsMix
	lparam = bIsScucces */
	/************************************************************************/
	ev_UiCnsAuxMixInd,
#define UI_CNS_CNAUXMIX_IND   ev_UiCnsAuxMixInd
	/************************************************************************/
	/** ����Ƶ֪ͨ
	wParam = bLimit �Ƿ����Ƶڶ�·����Ƶѡ��
	lparam =  */
	/************************************************************************/
	ev_UiCnsMinVideoInfoNty,
#define UI_CNS_MINVEDIOINFO_NTY   ev_UiCnsMinVideoInfoNty
	/************************************************************************/
	/** ����Ƶ����֪ͨ */
	/************************************************************************/
	ev_UiCnsSetVideoInfoNty,
#define UI_CNS_SETVEDIOINFO_NTY   ev_UiCnsSetVideoInfoNty
    /************************************************************************/
	/** �ն˻᳡�������
	wParam =  0
	lparam = 0 */
	/************************************************************************/
	ev_UiUmsToCncJoinConf_Req,
#define UI_UMS_JOINCONF_REG   ev_UiUmsToCncJoinConf_Req
	/************************************************************************/
	/**  WB�»����������Tpad���� 
	wParam =    
	lparam = IP*/
	/************************************************************************/
    ev_UiNewWBConfCallReq,
#define UI_NEWWBCONFCALL_REQ  ev_UiNewWBConfCallReq
	    /************************************************************************/
	/**  ���ݻ���״̬��������
	wParam =    
	lparam = �Ƿ������ݻ�����
	/************************************************************************/
    ev_UiWBConfStateNty,
#define UI_WBCONFSTATE_NTY  ev_UiWBConfStateNty
   /************************************************************************/
	/**  ������������һ�����ݻ���
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiSelfStartWBConf,
#define UI_SELFSTARTWBCONFNTY  ev_UiSelfStartWBConf

    /************************************************************************/
	/**  �������ݻ��� 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiJoinWBConfCmd,
#define UI_JOINWBCONF_CMD  ev_UiJoinWBConfCmd
    /************************************************************************/
	/**  ���ʻ���������뿪���ݻ���  
	wParam =    
	lparam = ip */
	/************************************************************************/
    ev_UiLeaveWBConfNty,
#define UI_LEAVEWBCONF_NTY  ev_UiLeaveWBConfNty
    /************************************************************************/
	/**  �����û᳡��Ϣʱ���᳡����������
	wParam =    
	lparam = �᳡�� m_achRoomName*/
	/************************************************************************/
    ev_UiConfRoomName,
#define UI_CONFROOMNAME_NTY  ev_UiConfRoomName
    /************************************************************************/
	/**  WB����IP�������� cns->tpad 
	wParam =    
	lparam = IP*/
	/************************************************************************/
    ev_UiTppSetDataServerInfoNty,
#define UI_TPPSETDATASERVERINFONTY  ev_UiTppSetDataServerInfoNty
    /************************************************************************/
	/**  WB����IP�Ƿ�����ɹ�������������� cns->tpad 
	wParam =    
	lparam = IP*/
	/************************************************************************/
	ev_UiTppSetDataServerInd,
#define	UI_TPPSETDATASERVER_IND  ev_UiTppSetDataServerInd

    /************************************************************************/
	/**  ���˿�����Ƶ����
	wParam =    
	lparam = 
	/************************************************************************/
    ev_UiSelfStartConfCmdNty,
#define UI_SELFSTARTCONF_CMD  ev_UiSelfStartConfCmdNty
    /************************************************************************/
	/**  �޸İװ������ip
	wParam =  bool �Ƿ�ɹ�  
	lparam = IP*/
	/************************************************************************/
    ev_UiSetWBServerIpNty,
#define UI_SETWBSERVERIP_NTY  ev_UiSetWBServerIpNty
    /************************************************************************/
	/**  ��Ե�������ݻ�������Ϣ cns->tpad 
	wParam =    
	lparam = IP*/
	/************************************************************************/
    ev_UiTppSetDataConfNameNty,
#define UI_TPPSETDATACONFNAMENTY  ev_UiTppSetDataConfNameNty
    /************************************************************************/
	/**  ����T300֪ͨ cns->tpad 
	wParam =    
	lparam = IP*/
	/************************************************************************/
    ev_UiTppUpDateT300Nty,
#define UI_TPPUPDATET300NTY  ev_UiTppUpDateT300Nty
    /************************************************************************/
	/** TPad����ϵͳ����
	wParam = 
	lparam =  */
	/************************************************************************/
    ev_UiTpadShowSysConfigNty,
#define UI_TPAD_SHOWSYSCONFIG_NTY        ev_UiTpadShowSysConfigNty
    /************************************************************************/
	/** TPad�����᳡����
	/************************************************************************/
    ev_UiTpadShowCnsManageNty,
#define UI_TPAD_SHOWCNSMANAGE_NTY        ev_UiTpadShowCnsManageNty

	
	/************************************************************************/
		/** �����쳣
		wParam = �쳣������
		lparam = 0*/
		/************************************************************************/
	ev_UiCMsError,
#define UI_CMS_ERROR  ev_UiCMsError
	
    /************************************************************************/
	/**  
	wParam =  errorcode
	lparam = 0*/
	/************************************************************************/
	ev_UiConnectRsp,
#define UI_CONNECT_RSP  ev_UiConnectRsp


	/************************************************************************/
	/**  �����᳡�б��е�cns��Ŀ
	wParam =  cnsInfo
	lparam = ��������item�������Ļ��rect*/
	/************************************************************************/
	ev_UiCnsConfItemClick,
#define UI_CONF_CNS_ITEM_CLICK  ev_UiCnsConfItemClick
   

   /************************************************************************/
	/**  ��������ģ���б��е� ��Ŀ
	wParam =  wConfTempID
	lparam = ��������item�������Ļ��rect*/
	/************************************************************************/
    ev_UiCnsConfTempItemClick,
#define UI_CONF_TEMP_ITEM_CLICK  ev_UiCnsConfTempItemClick

   /************************************************************************/
	/**  ������ַ���б��е���Ŀ����
	wParam =  Args_ClickItemInfo
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsAddrItemCallClick,
#define	UI_ADDR_ITEM_CALL_CLICK  ev_UiCmsAddrItemCallClick


   /************************************************************************/
	/**  ����ʱ��֪ͨ,��titlebar֪ͨ ʱ�����ý���
	wParam =  SYSTEMTIME
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsUpdateTime,
#define	UI_CMS_UPDATE_SYSTEM_TIME  ev_UiCmsUpdateTime


      /************************************************************************/
	/**  ����ʱ��֪ͨ    ��ʱ�����ý���֪ͨtitlebar
	wParam =  SYSTEMTIME
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsModifySystemTime,
#define	UI_CMS_MODIFY_SYSTEM_TIME  ev_UiCmsModifySystemTime

  /************************************************************************/
	/**  mainmenu ����� Toolbar
	wParam =    
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsMainmenuClickToolBtn,
#define	UI_CMS_CLICK_TOOL_BTN  ev_UiCmsMainmenuClickToolBtn
  
   /************************************************************************/
	/**  calling timer ��ʱ�� ���᳡δ����
	wParam =    
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsCallingTimeOut,
#define	UI_CMS_CALLING_TIME_OUT  ev_UiCmsCallingTimeOut

    /************************************************************************/
	/**  ��ʾ����dlg
	wParam =    
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsShowCallingDlg,
#define	UI_UMS_SHOW_CALLING_DLG  ev_UiCmsShowCallingDlg


     /************************************************************************/
	/**  ���غ���dlg
	wParam =    
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsHideCallingDlg, 
#define	UI_UMS_HIDE_CALLING_DLG  ev_UiCmsHideCallingDlg

	/************************************************************************/
	/**  ��ʾ�澯dlg
	wParam =    
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsShowAlarmDlg,
#define UI_CMS_SHOW_ALARM_DLG  ev_UiCmsShowAlarmDlg 



   ev_UiCmsSwitchIme,
#define WM_SWITCH_IME  ev_UiCmsSwitchIme
 
   ev_UiCmsKeyboardClose,
#define WM_KEYBOARD_CLOSE  ev_UiCmsKeyboardClose

   /************************************************************************/
	/**  ��¼ok
	wParam =    
	lparam = 0*/
	/************************************************************************/
    ev_UiCmsLoginOk,
#define WM_CMS_UI_LOGIN_OK  ev_UiCmsLoginOk

   /************************************************************************/
	/**  �Զ���¼CNS�᳡
	wParam =    
	lparam = 0*/
	/************************************************************************/	
	ev_UiCmsAutoLogCnsIns,
#define UI_CMS_AUTOLOG_CNSINS   ev_UiCmsAutoLogCnsIns


   /************************************************************************/
	/** ����Ͽ�
	wParam =    
	lparam = 0*/
	/************************************************************************/
   ev_UiCmsNetDisconnect,
#define WM_NET_DISCONNECT  ev_UiCmsNetDisconnect

   /************************************************************************/
	/**  IP ��ͻ
	wParam =    
	lparam = 0*/
	/************************************************************************/
   ev_UiCmsIpConflict,
#define WM_NET_IPCONFLICT  ev_UiCmsIpConflict

   /************************************************************************/
	/**  ����confmenu
	wParam =    
	lparam = 0*/
	/************************************************************************/
   ev_UiCmsIUpdateConfMenu,
#define WM_CMS_UPDATE_CONFMENU  ev_UiCmsIUpdateConfMenu


    /************************************************************************/
	/**  �������ʾ��Ƶ���밴ť
	wParam =   1 ��ʾ��Ҫ�����ʾ
	lparam = 0*/
	/************************************************************************/
   ev_UiCmsShowVideo,
#define WM_CMS_SHOWVIDEO  ev_UiCmsShowVideo


    /************************************************************************/
	/**  ����mainMenu
	wParam =    
	lparam = 0*/
	/************************************************************************/
    ev_UiCmsIUpdateMainMenu,
#define WM_CMS_UPDATE_CMAINMENU  ev_UiCmsIUpdateMainMenu

    /************************************************************************/
	/**  ����mainMenu
	wParam =    
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsHideVedio,
#define WM_CMS_HIDE_VEDIO  ev_UiCmsHideVedio

	/************************************************************************/
	/**  ��ʼ�ȴ�����ע����Ϣ
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiCncBeginWaitingRefresh,
#define UI_CNC_BEGINWAITING_REFRESH  ev_UiCncBeginWaitingRefresh

	/************************************************************************/
	/**  �����ȴ�����ע����Ϣ
	wParam = 0 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncEndWaitingRefresh,
#define UI_CNC_ENDWAITING_REFRESH  ev_UiCncEndWaitingRefresh

	/************************************************************************/
	/**  ֪ͨ�����ַ��ʱʣ�����Ŀ����
	wParam = u32 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncLoadAddrNumNty,
#define UI_CNC_LOADADDRNUM_NTY  ev_UiCncLoadAddrNumNty

	/************************************************************************/
	/**  �ȴ�����ע����Ϣ��ʱ
	wParam = 0 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncWaitingRefreshOverTime,
#define UI_CNC_WAITINGREFRESH_OVERTIME  ev_UiCncWaitingRefreshOverTime


	/************************************************************************/
	/**  ���ش��ڵ���Ϣ 
	wParam = 0 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncHideWnd,
#define UI_CNC_HIDE_WND  ev_UiCncHideWnd

	/************************************************************************/
	/**  ���з���������������ʽѡ�����Ϣ (callserverlogic2modelogic)
	wParam = TTPCallSerFormat 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncCallSvr2ModeChooseModeNty,
#define UI_CNC_CALLSVR2MODECHOOSE_MODE_NTY  ev_UiCncCallSvr2ModeChooseModeNty

	/************************************************************************/
	/**  ���з���������������ʽѡ�����Ϣ (modelogic2callserverlogic)
	wParam = TTPCallSerFormat 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncModeChoose2CallSvrModeNty,
#define UI_CNC_MODECHOOSE2CALLSVR_MODE_NTY  ev_UiCncModeChoose2CallSvrModeNty

	/************************************************************************/
	/**  ���з���������������ʽѡ�����Ϣ (callserverlogic2showmodelogic)
	wParam = TTPCallSerFormat 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncCallSvr2ShowModeChooseModeNty,
#define UI_CNC_CALLSVR2SHOWMODECHOOSE_MODE_NTY  ev_UiCncCallSvr2ShowModeChooseModeNty

	/************************************************************************/
	/**  ���з���������������ʽѡ�����Ϣ (showmodelogic2callserverlogic)
	wParam = TTPCallSerFormat 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncShowModeChoose2CallSvrModeNty,
#define UI_CNC_SHOWMODECHOOSE2CALLSVR_MODE_NTY  ev_UiCncShowModeChoose2CallSvrModeNty

	/************************************************************************/
	/**  ���з�����������Ƶ��ʽѡ�����Ϣ (callserverlogic2Audiomodelogic)
	wParam = EmTpAudioFormat
	lparam = 0*/
	/************************************************************************/
	ev_UiCncCallSvr2AudioModeNty,
#define UI_CNC_CALLSVR2AUDIO_MODE_NTY  ev_UiCncCallSvr2AudioModeNty

	/************************************************************************/
	/**  ���з�����������Ƶ��ʽѡ�����Ϣ (Audiomodelogic2callserverlogic)
	wParam = EmTpAudioFormat 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncAudioMode2CallSvrNty,
#define UI_CNC_AUDIO2CALLSVR_MODE_NTY  ev_UiCncAudioMode2CallSvrNty
				
    /************************************************************************/
	/**  ̨���ϴ���������(�������һ�ε�¼)
	wParam =  ����ֵ  
	lparam = 0*/
	/************************************************************************/	
	em_CNC_FL_CONFSIGNPROGRESS,
#define WM_CNC_FL_FTPCONFSIGNPROGRESS  em_CNC_FL_CONFSIGNPROGRESS		   
	/************************************************************************/
	/**  ̨���ϴ���������
	wParam =  ����ֵ  
	lparam = 0*/
	/************************************************************************/	
	em_CNC_CONFSIGNPROGRESS,
#define WM_CNC_FTPCONFSIGNPROGRESS  em_CNC_CONFSIGNPROGRESS		   
	/************************************************************************/
	/**  ����ϴ���������
	wParam =  ����ֵ  
	lparam = 0*/
	/************************************************************************/	
	em_CNC_CONFBANNERPROGRESS,
#define WM_CNC_FTPCONFBANNERPROGRESS  em_CNC_CONFBANNERPROGRESS		 
	
    /************************************************************************/
	/**  ������رջ��л��������� 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiViewLocalPIPInd,
#define UI_CNS_VIEWLOCALPIP_IND  ev_UiViewLocalPIPInd
	
    /************************************************************************/
	/**  ���л�������ر�״̬֪ͨ 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiViewLocalPIPNty,
#define UI_CNS_VIEWLOCALPIP_NTY  ev_UiViewLocalPIPNty

	/************************************************************************/
	/**  ��ݲ˵�����
	wParam =    �˵���ö�� EM_ShortcutType
	lparam =     �Ƿ���  */
	/************************************************************************/
    ev_UiShortCutNty,
#define UI_CNC_SET_SHORTCUT_NTY  ev_UiShortCutNty

	/************************************************************************/
	/**  ��ݲ˵�������ý��������Ŀ���н���
	wParam =    �˵���ö�� EM_ShortcutType
	lparam =       */
	/************************************************************************/
    ev_UiShowShortCutDlgNty,
#define UI_CNC_SHOW_SHORTCUTDLG_NTY  ev_UiShowShortCutDlgNty
	/************************************************************************/
	/**  ��¼ʱˢ�¿�ݷ�ʽ��ť״̬
	wParam =    �˵���ö�� EM_ShortcutType
	lparam =       */
	/************************************************************************/
    ev_UiShortCutCheckNty,
#define UI_CNC_SHORTCUTCHECK_NTY  ev_UiShortCutCheckNty
	/************************************************************************/
	/**  Ԥ��λ��ͼ����֪ͨ
	wParam =  ����ֵ  
	lparam = 0*/
	/************************************************************************/	
	em_CNC_PAMCAMRPRESETPROGRESS,
#define WM_CNC_PAMCAMRPRESETPROGRESS  em_CNC_PAMCAMRPRESETPROGRESS	
	/************************************************************************/
	/**  �ĵ��������������֪ͨ
	wParam =  ����ֵ  
	lparam = 0*/
	/************************************************************************/	
	em_CNC_DOCSNAPSHOTROGRESS,
#define WM_CNC_DOCSNAPSHOTROGRESS  em_CNC_DOCSNAPSHOTROGRESS	
   /************************************************************************/
	/**  calendar����ѡ��֪ͨ
	wParam =     ����
	lparam =     */
	/************************************************************************/
    ev_UiCalendarDateSet,
#define UI_CNC_CALENDARDATE_SET  ev_UiCalendarDateSet
	/************************************************************************/
	/**  ������ѯ��ݷ�ʽ��ѯ����֪ͨ
	wParam = 
	lparam =     */
	/************************************************************************/
    ev_UiShortCutPoll,
#define UI_CNC_SHORTCUT_POLL  ev_UiShortCutPoll
	/************************************************************************/
	/**  ���������ݷ�ʽ��ѯ����֪ͨ
	wParam = 
	lparam =     */
	/************************************************************************/
    ev_UiShortCutRoll,
#define UI_CNC_SHORTCUT_ROLL  ev_UiShortCutRoll
	/************************************************************************/
	/** ����ϳɿ�ݷ�ʽ��ѯ����֪ͨ
	wParam = 
	lparam =     */
	/************************************************************************/
    ev_UiShortCutVMix,
#define UI_CNC_SHORTCUT_VMIX  ev_UiShortCutVMix
	/************************************************************************/
	/**  ���������ݷ�ʽ����֪ͨ
	wParam = 
	lparam =     */
	/************************************************************************/
    ev_UiShortCutConfMix,
#define UI_CNC_SHORTCUT_CONFMIX  ev_UiShortCutConfMix
	/************************************************************************/
	/**  ȫ��������ݷ�ʽ����֪ͨ
	wParam = 
	lparam =     */
	/************************************************************************/
    ev_UiShortCutQuiteAll,
#define UI_CNC_SHORTCUT_QUITEALL  ev_UiShortCutQuiteAll
	/************************************************************************/
	/**  ȫ��������ݷ�ʽ����֪ͨ
	wParam = 
	lparam =     */
	/************************************************************************/
    ev_UiShortCutMuteAll,
#define UI_CNC_SHORTCUT_MUTEALL  ev_UiShortCutMuteAll
    /************************************************************************/
	/** ����״̬������Ӧ
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiConfRollInd,
#define UI_CNS_CONFROLL_IND  ev_UiConfRollInd	
    /************************************************************************/
	/**  ����״̬֪ͨ
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiConfRollNty,
#define UI_CNS_CONFROLL_NTY  ev_UiConfRollNty
	/************************************************************************/
	/**  �����������״̬֪ͨ
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiConfRollAattendNty,
#define UI_CNS_CONFROLL_ATTEND_NTY  ev_UiConfRollAattendNty
    /************************************************************************/
	/**  ������һ����Ӧ
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiConfRollNextInd,
#define UI_CNS_CONFROLLNEXT_IND  ev_UiConfRollNextInd
	/************************************************************************/
	/**  ��ӱ������˻�Ӧ
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiConfRollListFixedInd,
#define UI_CNS_CONFROLL_LISTFIXED_IND  ev_UiConfRollListFixedInd
	/************************************************************************/
	/** ����״̬֪ͨ
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiConMixNty,
#define UI_CNS_CONFMIX_NTY  ev_UiConMixNty	
	/************************************************************************/
	/** �������������Ӧ
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiConMixInd,
#define UI_CNS_CONFMIX_IND  ev_UiConMixInd	
	/************************************************************************/
	/** �޸Ļ�����Ա���������Ӧ
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiConMixFixInd,
#define UI_CNS_CONFMIX_FIX_IND  ev_UiConMixFixInd	
	/************************************************************************/
	/**  �Զ�����������log֪ͨ
	wParam =  ����ֵ  
	lparam = 0*/
	/************************************************************************/	
	em_cnc_LogDownloadProgress,
#define WM_CNC_LOGLOADPROGRESS  em_cnc_LogDownloadProgress	

    /************************************************************************/
	/**  ��ݲ˵�������ý��������Ŀ���н���
	wParam =    �˵���ö�� EM_ShortcutType
	lparam =       */
	/************************************************************************/
    ev_UiHideTvWallChildDlgNty,
#define UI_CNC_HIDE_TVWALLCHILDDLG_NTY  ev_UiHideTvWallChildDlgNty

	/************************************************************************/
	/**  ������ѯ�б���·���֪ͨ
	wParam = m_wRet 
	lparam = m_nFlag 
	/************************************************************************/
	ev_UiPollListInd,
#define UI_CNSPOLLLIST_IND  ev_UiPollListInd
	/************************************************************************/
	/**  ������ѯ�б�֪ͨ
	wParam =  
	lparam =  
	/************************************************************************/
	ev_UiPollListNty,
#define UI_CNSPOLLLIST_NTY  ev_UiPollListNty
	/************************************************************************/
	/**  ������ѯ��֪ͣͨ
	wParam = u32_Ip
	lparam = bSuccess 
	/************************************************************************/
	ev_UiPollPauseInd,
#define UI_CNSPOLLPAUSE_IND  ev_UiPollPauseInd

    ev_UIVidMixOpenStatusNty,
#define UI_CNC_VIDMIXSTATUS_NTY  ev_UIVidMixOpenStatusNty

	/************************************************************************/
	/**  ����ü�֪ͨ
	wParam = BOOL TRUE������FALSE�ر�
	lparam = bSuccess 
	/************************************************************************/
	ev_UiVidCutLineInd,
#define UI_CNC_VIDCUTLINE_IND  ev_UiVidCutLineInd

	/************************************************************************/
	/**  �Ƿ��ڻ��������֪ͨ
	wParam = BOOL TRUE�ڣ�FALSE����
	/************************************************************************/
	ev_UiInAudMixNty,
#define UI_CNC_INAUDMIX_NTY  ev_UiInAudMixNty
	/************************************************************************/
	/**	323�᳡��ƵԴ֪ͨ
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICns323VedioSourceListNty,
#define	UI_CNS_323VEDIOSOR_NOTIFY         ev_UICns323VedioSourceListNty
	/************************************************************************/
	/**  ���Ӽ�����Ӧ
	wParam = 0
	lparam = BOOL TRUE�ɹ���FALSEʧ��
	/************************************************************************/
	ev_UiQTEncryptInd,
#define UI_CNC_QTENCRYPT_IND  ev_UiQTEncryptInd
	/************************************************************************/
	/**  ���Ӽ���֪ͨ
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_UiQTEncryptNty,
#define UI_CNC_QTENCRYPT_NTY  ev_UiQTEncryptNty
	/************************************************************************/
	/**  ʱ��ͬ������״̬��ʾ
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_CnSysTimeToCncNty,
#define UI_CNC_CNSYSTIMETOCNC_NTY  ev_CnSysTimeToCncNty
	/************************************************************************/
	/**  �Ƿ�������˷�֪ͨ
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_CnDesktopMicInfoNty,
#define UI_CNC_CNDESKTOPMICINFO_NTY  ev_CnDesktopMicInfoNty
	/************************************************************************/
	/**  ��˷���֪ͨ
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_CnMicPowerStyleNty,
#define UI_CNC_CNMICPOWERSTYLE_NTY  ev_CnMicPowerStyleNty
	/************************************************************************/
	/**  ��˷�״̬֪ͨ
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_CnMicPowerNty,
#define UI_CNC_CNMICPOWER_NTY  ev_CnMicPowerNty
	/************************************************************************/
	/**  ������˷�״̬����
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_CnSetMicPowerRsp,
#define UI_CNC_CNSETMICPOWER_RSP  ev_CnSetMicPowerRsp

    /************************************************************************/
	/**  ������������Ϣ֪ͨ
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_CentreDFScreenConfigNty,
#define UI_CNC_CENTREDFSCREENCONFIG_NTY  ev_CentreDFScreenConfigNty

    /************************************************************************/
	/**  ��������������֪ͨ
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_CentreDFScreenCmdInd,
#define UI_CNC_CENTREDFSCREENCMD_IND  ev_CentreDFScreenCmdInd

	/************************************************************************/
	/**  TPad��cnc֪ͨ����
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_TpadCnsDisconnectedNty,
#define UI_TPAD_CNSDISCONNECTED_NTY  ev_TpadCnsDisconnectedNty	

	/************************************************************************/
	/**  �����������
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_DisconnectedClearData,
#define	UI_DISCONNECTED_CLEARDATA  ev_DisconnectedClearData
	/************************************************************************/
	/**  �������ڸ���֪ͨ
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_CnTpadPWUpdate_Nty,
#define UI_CNTPADPWUPDATE_NTY  ev_CnTpadPWUpdate_Nty
	/************************************************************************/
	/**  �������ڸ�����Ӧ
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_CnTpadPWUpdate_Ind,
#define UI_CNTPADPWUPDATE_IND  ev_CnTpadPWUpdate_Ind

    /************************************************************************/
	/**  ��������Ա֪ͨ
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_Superadmin_Nty,
#define UI_SUPERADMIN_NTY  ev_Superadmin_Nty

    /************************************************************************/
	/**  T300�������һ�ε�¼
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_FirstLoginAfterUpdate_Nty,
#define UI_FIRSTLOGINAFTERUPDATE_NTY  ev_FirstLoginAfterUpdate_Nty

    /************************************************************************/
	/**  ѯ�ʻ���ģ������
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_GetTempPwd_Cmd,
#define UI_GETTEMPPWD_CMD  ev_GetTempPwd_Cmd

    ev_UICncEnd,
#define	UI_CNC_MSG_END   ev_UICncEnd

};



//cms �߼���Ԫ�����Ϣ����
enum EmUiCmsMsg
{  

#define UI_CMS_MSG_BEGIN  UI_CNC_MSG_END + 0x1

    	
	ev_UiCmsMsgEnd,
#define UI_CMS_MSG_END  ev_UiCmsMsgEnd
};


enum EmTPadMsg
{
    #define EV_TPAD_MSG_BEGIN  CMS_MSG_BEGIN + 900

    ev_TPadMsg_Begin = EV_TPAD_MSG_BEGIN,

    /************************************************************************/
	/** ֪ͨTpad��¼��Ϣ
	/************************************************************************/
    ev_TPadLoginInfo_Nty,

    /************************************************************************/
	/** cnc�޸�ϵͳ���� dyy
	/************************************************************************/
    ev_TPadSetSysName_Nty,

    /************************************************************************/
	/** ֪ͨTpad Home����Ӧ
	/************************************************************************/
    ev_TPadHomeKey_Nty,

	/************************************************************************/
	/** ֪ͨTpad��Ӧ������cns����
	/************************************************************************/
    ev_TpadDisconnectCns_Nty,
	
    /************************************************************************/
	/** ֪ͨcnc �Ƿ����װ����  
	/************************************************************************/
    ev_WBConfStateNty,
    /************************************************************************/
	/** ֪ͨ���п�  dyy 2015-5-26
	/************************************************************************/
    ev_OpenCenterCtrl_Nty,
    /************************************************************************/
	/** ֪ͨ��ϵͳ����  dyy 2016-8-29
	/************************************************************************/
    ev_OpenSysConfig_Nty,
    /************************************************************************/
	/** ֪ͨ�򿪻᳡����  2017.3.10
	/************************************************************************/
    ev_OpenCnsManage_Nty,
	/************************************************************************/
	/** TPad֪ͨcnc������Ϣ  xcr 2017.9.22
	/************************************************************************/
	ev_CnsDisconnect_Nty,

    ev_TPadMsg_End,
};


//cnstool��Ϣ����
enum EmUiCnstoolMsg
{
#define UI_CNSTOOL_MSG_BEGIN  CNSTOOL_MSG_BEGIN + 0x1

    	/************************************************************************/
		/** �����쳣
		wParam = �쳣������
		lparam = 0*/
		/************************************************************************/
	ev_UiCNSTOOLError = UI_CNSTOOL_MSG_BEGIN,
#define UI_CNSTOOL_ERROR  ev_UiCNSTOOLError

	/************************************************************************/
	/**  ����TPadIP�б�ظ���Ϣ
	wParam =  &TTPTPadList
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolTPadIPRsp,
#define UI_CNSTOOL_MSG_TPadIP_RSP  ev_UiCnstoolTPadIPRsp

	/************************************************************************/
	/**  ����TPadIP�б�֪ͨ��Ϣ
	wParam =  &TTPTPadList
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolTPadIPNty,
#define UI_CNSTOOL_MSG_TPadIP_NTY  ev_UiCnstoolTPadIPNty

	/************************************************************************/
	/**  ����cpu/�ڴ�֪ͨ��Ϣ
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolSYSInfoNty,
#define UI_CNSTOOL_MSG_CPURAM_NTY  ev_UiCnstoolSYSInfoNty

	/************************************************************************/
	/**  ���ջ�����Ϣ֪ͨ��Ϣ
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolConfInfoNty,
#define UI_CNSTOOL_MSG_CONF_NTY  ev_UiCnstoolConfInfoNty

	/************************************************************************/
	/**  ������Ƶ�˿�����֪ͨ��Ϣ
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolAudPortInd,
#define UI_CNSTOOL_MSG_AudPort_NTY  ev_UiCnstoolAudPortInd
	
	/************************************************************************/
	/**  ����Ĭ����Ƶ�˿���Ϣ
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDftAudPortInd,
#define UI_CNSTOOL_MSG_DftAudPort_NTY  ev_UiCnstoolDftAudPortInd
	
	/************************************************************************/
	/**  ��������������֪ͨ��Ϣ
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolUpDownstreamInd,
#define UI_CNSTOOL_MSG_UpDownstream_NTY  ev_UiCnstoolUpDownstreamInd

	/************************************************************************/
	/**  ���ն�����Ϣ
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolLostPacketRsp,
#define UI_CNSTOOL_MSG_LostPacket_Rsp  ev_UiCnstoolLostPacketRsp

	/************************************************************************/
	/**  ������ϲ�����Ϣ
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolAVDiagInd,
#define UI_CNSTOOL_MSG_AVDiag_IND  ev_UiCnstoolAVDiagInd

	/************************************************************************/
	/**  �������ָʾ
	wParam = EmModifyNMServerRet �Ƿ�ɹ�
	lparam = ��*/
	/************************************************************************/
	ev_UICnstoolAddNetmngInd,
#define UI_CNSTOOL_ADD_NETMNG_IND  ev_UICnstoolAddNetmngInd

	/************************************************************************/
	/**  ɾ������ָʾ
	wParam = EmModifyNMServerRet �Ƿ�ɹ�
	lparam = ��*/
	/************************************************************************/
	ev_UICnstoolDelNetmngInd,
#define UI_CNSTOOL_DEL_NETMNG_IND  ev_UICnstoolDelNetmngInd

	/************************************************************************/
	/**  ������Ϣ֪ͨ
	wParam = TTPNMServerCfg* ������Ϣ
	lparam = ��*/
	/************************************************************************/
	ev_UICnstoolNetmngNty,
#define UI_CNSTOOL_NETMNG_NTY  ev_UICnstoolNetmngNty

	/************************************************************************/
	/**  �޸�����ָʾ
	wParam = EmModifyNMServerRet �Ƿ�ɹ�
	lparam = ��*/
	/************************************************************************/
	ev_UICnstoolModifyNetmngInd,
#define UI_CNSTOOL_MODIFY_NETMNG_IND  ev_UICnstoolModifyNetmngInd

	/************************************************************************/
	/**  ����ҳ������޸����ܵ�ǰѡ�����ݷ���
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiCnstoolNetMngSelDataClick,
#define UI_CNSTOOL_MSG_NETMNGSELDATA_Click  ev_UiCnstoolNetMngSelDataClick
	
	/************************************************************************/
	/**  ���պ��з�������֪ͨ��Ϣ
	wParam = 0   
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolCallSerNty,
#define UI_CNSTOOL_MSG_CallSer_NTY  ev_UiCnstoolCallSerNty
		
	/************************************************************************/
	/**  ���պ��з������Ļظ���Ϣ
	wParam = TTPCallSerInfo  
	lparam = bSuccess 
	/************************************************************************/
	ev_UiCnstoolCallSerInd,
#define UI_CNSTOOL_MSG_CallSer_IND  ev_UiCnstoolCallSerInd
	
	/************************************************************************/
	/**  ����������������֪ͨ��Ϣ
	wParam = 0   
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolUpgradeSerNty,
#define UI_CNSTOOL_MSG_UpgradeSer_NTY  ev_UiCnstoolUpgradeSerNty
		
	/************************************************************************/
	/**  ���������������Ļظ���Ϣ
	wParam = u32_Ip
	lparam = bSuccess 
	/************************************************************************/
	ev_UiCnstoolUpgradeSerInd,
#define UI_CNSTOOL_MSG_UpgradeSer_IND  ev_UiCnstoolUpgradeSerInd
		
	/************************************************************************/
	/**  �����п���Ϣ�пյ�����Ϣ
	wParam = 0  
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolAirInfoNty,
#define UI_CNSTOOL_MSG_AirInfo_NTY  ev_UiCnstoolAirInfoNty
	
	/************************************************************************/
	/**  �����п���Ϣ���·����Ϣ
	wParam = 0 
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolXinFengInfoNty,
#define UI_CNSTOOL_MSG_XinFengInfo_NTY  ev_UiCnstoolXinFengInfoNty
	
	/************************************************************************/
	/**  �����п���Ϣ����ʾ������Ϣ
	wParam = 0 
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolDisplayInfoNty,
#define UI_CNSTOOL_MSG_DisplayInfo_NTY  ev_UiCnstoolDisplayInfoNty
	
	/************************************************************************/
	/**  �����п���Ϣ�����������Ϣ
	wParam = 0 
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolCameraInfoNty,
#define UI_CNSTOOL_MSG_CameraInfo_NTY  ev_UiCnstoolCameraInfoNty
	
	/************************************************************************/
	/**  �����п���Ϣ���ĵ����������Ϣ
	wParam = 0 
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolDocCamInfoNty,
#define UI_CNSTOOL_MSG_DocCamInfo_NTY  ev_UiCnstoolDocCamInfoNty
	
	/************************************************************************/
	/**  �����п���Ϣ�еƹ����Ϣ
	wParam = 0 
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolLightInfoNty,
#define UI_CNSTOOL_MSG_LightInfo_NTY  ev_UiCnstoolLightInfoNty

	/************************************************************************/
	/**  ���������֪ͨ
	wParam = NULL
	lparam = NULL
	/************************************************************************/
	ev_UICnstoolCameraCfgNty,
#define UI_CNSTOOL_CAMERA_CFG_NTY  ev_UICnstoolCameraCfgNty

	/************************************************************************/
	/**  ѡ������������������
	wParam = NULL
	lparam = BOOL  = TRUE ѡ��ɹ� =FALSE ѡ��ʧ��
	/************************************************************************/
	ev_UICnstoolCameraSelectInd,
#define UI_CNSTOOL_CAMERA_SELECT_IND  ev_UICnstoolCameraSelectInd

	/************************************************************************/
	/**  �ָ�������������÷�����Ϣ
	wParam = NULL
	lparam = BOOL   =TRUE ���óɹ�  FALSE ����ʧ��
	/************************************************************************/
	ev_UICnstoolCameraResetInd,
#define UI_CNSTOOL_CAMERA_RESET_IND  ev_UICnstoolCameraResetInd

	/************************************************************************/
	/**  ������Ұ���ڷ�������
	wParam = NULL
	lparam = BOOL:				TRUE ���óɹ�  =FALSE ����ʧ��
	/************************************************************************/
	ev_UICnstoolCameraZoomInd,
#define UI_CNSTOOL_CAMERA_ZOOM_IND  ev_UICnstoolCameraZoomInd

	/************************************************************************/
	/**  ����� ��Ұ��OSD����ʾ������������
	wParam = NULL
	lparam = BOOL          =TRUE ���óɹ�  =FALSE ����ʧ��
	/************************************************************************/
	ev_UICnstoolCameraOSDShowInd,
#define UI_CNSTOOL_CAMERA_OSDSHOW_IND  ev_UICnstoolCameraOSDShowInd

	/************************************************************************/
	/**  ����ͷ�Զ��۽���������
	wParam = BOOL   =TRUE ���óɹ�   =FALSE ����ʧ��
	lparam = NULL
	/************************************************************************/
	ev_UICnstoolCameraAutoFocusInd,
#define UI_CNSTOOL_CAMERA_AUTO_FOCUS_IND  ev_UICnstoolCameraAutoFocusInd

	/************************************************************************/
	/**  ����ͷ�۽���������
	wParam = EmFocus         emFar Զ��  emNear����
	lparam = BOOL        =TRUE ���óɹ�  =FALSE ����ʧ��
	/************************************************************************/
	ev_UICnstoolCameraFocusInd,
#define UI_CNSTOOL_CAMERA_FOCUS_IND  ev_UICnstoolCameraFocusInd

	/************************************************************************/
	/**  ������Զ��عⷵ������
	wParam = NULL
	lparam = BOOL       =TRUE ���óɹ�  =FALSE ����ʧ�� 
	/************************************************************************/
	ev_UICnstoolCameraAutoExposureInd,
#define UI_CNSTOOL_CAMERA_AUTO_EXPOSURE_IND  ev_UICnstoolCameraAutoExposureInd

	/************************************************************************/
	/**  ������ֶ��ع⡪��������ڷ�������
	wParam = NULL
	lparam = BOOL    =��TRUE ���óɹ�   =FALSE ����ʧ��
	/************************************************************************/
	ev_UICnstoolCameraGainInd,
#define UI_CNSTOOL_CAMERA_GAIN_IND  ev_UICnstoolCameraGainInd

	/************************************************************************/
	/**  ������ֶ��ع⡪�����ŵ��ڷ�������
	wParam = NULL
	lparam = BOOL    =��TRUE ���óɹ�   =FALSE ����ʧ��
	/************************************************************************/
	ev_UICnstoolCameraShutSpdInd,
#define UI_CNSTOOL_CAMERA_SHUT_SPD_IND  ev_UICnstoolCameraShutSpdInd

	/************************************************************************/
	/**  ������ֶ��ع⡪��������ڷ�������
	wParam = NULL
	lparam = BOOL    =��TRUE ���óɹ�   =FALSE ����ʧ��
	/************************************************************************/
	ev_UICnstoolCameraBackLightInd,
#define UI_CNSTOOL_CAMERA_BACK_LIGHT_IND  ev_UICnstoolCameraBackLightInd

	/************************************************************************/
	/**  ������ֶ��ع⡪����Ȧ���ڷ�������
	wParam = NULL
	lparam = BOOL   =TRUE ���óɹ�   =FALSE ����ʧ��
	/************************************************************************/
	ev_UICnstoolCameraApertureInd,
#define UI_CNSTOOL_CAMERA_APERTURE_IND  ev_UICnstoolCameraApertureInd

	/************************************************************************/
	/**  ������Զ���ƽ�ⷵ������
	wParam = BOOL   =TRUE ���óɹ�   =FALSE ����ʧ��
	lparam = NULL
	/************************************************************************/
	ev_UICnstoolCameraAutoWBInd,
#define UI_CNSTOOL_CAMERA_AUTO_WB_IND  ev_UICnstoolCameraAutoWBInd

	/************************************************************************/
	/**  ������ֶ���ƽ��--R Gain��������
	wParam = NULL
	lparam = BOOL   =TRUE ���óɹ�      =FALSE  ����ʧ��
	/************************************************************************/
	ev_UICnstoolCameraRGainInd,
#define UI_CNSTOOL_CAMERA_RGAIN_IND  ev_UICnstoolCameraRGainInd

	/************************************************************************/
	/**  ������ֶ���ƽ��--B Gain��������
	wParam = NULL
	lparam = BOOL   =TRUE ���óɹ�      =FALSE  ����ʧ��
	/************************************************************************/
	ev_UICnstoolCameraBGainInd,
#define UI_CNSTOOL_CAMERA_BGAIN_IND  ev_UICnstoolCameraBGainInd

	/************************************************************************/
	/**  ���������ģʽ��������
	wParam = NULL
	lparam = BOOL   =TRUE ���óɹ�      =FALSE  ����ʧ��
	/************************************************************************/
	ev_UICnstoolCameraPicSceneModeInd,
#define UI_CNSTOOL_CAMERA_PIC_SCENE_MODE_IND  ev_UICnstoolCameraPicSceneModeInd

	/************************************************************************/
	/**  ����� ģʽ--- �ֶ� GAMMA���ڷ�������
	wParam = NULL
	lparam = BOOL   =TRUE ���óɹ�      =FALSE  ����ʧ��
	/************************************************************************/
	ev_UICnstoolCameraGammaInd,
#define UI_CNSTOOL_CAMERA_GAMMA_IND  ev_UICnstoolCameraGammaInd

	/************************************************************************/
	/**  ����� ģʽ--- ��Ȧ���ڷ�������
	wParam = NULL
	lparam = BOOL   =TRUE ���óɹ�      =FALSE  ����ʧ��
	/************************************************************************/
	ev_UICnstoolCameraPicSceAptInd,
#define UI_CNSTOOL_CAMERA_PIC_SCE_APT_IND  ev_UICnstoolCameraPicSceAptInd

	/************************************************************************/
	/**  ����� ͼƬ����---�Աȶ� ���ڷ�������
	wParam = NULL
	lparam = BOOL   =TRUE ���óɹ�      =FALSE  ����ʧ��
	/************************************************************************/
	ev_UICnstoolCameraContrastInd,
#define UI_CNSTOOL_CAMERA_CONTRAST_IND  ev_UICnstoolCameraContrastInd

	/************************************************************************/
	/**  ����� ͼƬ����---���Ͷ� ���ڷ�������
	wParam = NULL
	lparam = BOOL   =TRUE ���óɹ�      =FALSE  ����ʧ��
	/************************************************************************/
	ev_UICnstoolCameraSaturatInd,
#define UI_CNSTOOL_CAMERA_SATURAT_IND  ev_UICnstoolCameraSaturatInd

	/************************************************************************/
	/**  ����� ͼƬ����--- ɫ�� ���ڷ�������
	wParam = NULL
	lparam = BOOL   =TRUE ���óɹ�      =FALSE  ����ʧ��
	/************************************************************************/
	ev_UICnstoolCameraHueInd,
#define UI_CNSTOOL_CAMERA_HUE_IND  ev_UICnstoolCameraHueInd

	/************************************************************************/
	/**  ����� ͼƬ����--- ���� ���ڷ�������
	wParam = NULL
	lparam = BOOL   =TRUE ���óɹ�      =FALSE  ����ʧ��
	/************************************************************************/
	ev_UICnstoolCameraBrightInd,
#define UI_CNSTOOL_CAMERA_BRIGHT_IND  ev_UICnstoolCameraBrightInd

	/************************************************************************/
	/**  ����� ����---������ ���ڷ�������
	wParam = NULL
	lparam = BOOL   =TRUE ���óɹ�      =FALSE  ����ʧ��
	/************************************************************************/
	ev_UICnstoolCameraNRStmCleanInd,
#define UI_CNSTOOL_CAMERA_NR_STM_CLEAN_IND  ev_UICnstoolCameraNRStmCleanInd

	/************************************************************************/
	/**  ����� ����---3D���� ���ڷ�������
	wParam = NULL
	lparam = BOOL   =TRUE ���óɹ�      =FALSE  ����ʧ��
	/************************************************************************/
	ev_UICnstoolCamera3DNRInd,
#define UI_CNSTOOL_CAMERA_3DNR_IND  ev_UICnstoolCamera3DNRInd

	/************************************************************************/
	/**  ����� Ԥ��λ���淵������
	wParam = NULL	
	lparam = BOOL	TRUE= ����Ԥ��λ�ɹ�   = FALSE ����ʧ��
	/************************************************************************/
	ev_UICnstoolCameraPersetSaveInd,
#define UI_CNSTOOL_CAMERA_PERSET_SAVE_IND  ev_UICnstoolCameraPersetSaveInd

	/************************************************************************/
	/**  ����� ���ÿ�������Ԥ��λ
	wParam = NULL	
	lparam = BOOL	TRUE= ���óɹ�   = FALSE ����ʧ��
	/************************************************************************/
	ev_UICnstoolCameraPersetMoveInd,
#define UI_CNSTOOL_CAMERA_PERSET_MOVE_IND  ev_UICnstoolCameraPersetMoveInd

	/************************************************************************/
	/**  ����� ����ZOOM
	wParam = NULL	
	lparam = BOOL	TRUE= ���óɹ�   = FALSE ����ʧ��
	/************************************************************************/
	ev_UICnstoolSetCameraZoomInd,
#define UI_CNSTOOL_SET_CAMERA_ZOOM_IND  ev_UICnstoolSetCameraZoomInd
			
	/************************************************************************/
	/**  ������Ƶ����������֪ͨ��Ϣ
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolAudMixerInd,
#define UI_CNSTOOL_MSG_AudMixer_NTY  ev_UiCnstoolAudMixerInd
				
	/************************************************************************/
	/**  ����ϵͳĬ����Ƶ��������Ϣ
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDefaultMixerInd,
#define UI_CNSTOOL_MSG_DftMixer_NTY  ev_UiCnstoolDefaultMixerInd
	
	/************************************************************************/
	/**  ������Ƶ����������֪ͨ��Ϣ
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolAudEqualizerInd,
#define UI_CNSTOOL_MSG_AudEqualizer_NTY  ev_UiCnstoolAudEqualizerInd
				
	/************************************************************************/
	/**  ����ϵͳĬ����Ƶ��������Ϣ
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDefaultEqInd,
#define UI_CNSTOOL_MSG_DftEq_NTY  ev_UiCnstoolDefaultEqInd
			
	/************************************************************************/
	/**  ��������T300�ظ���Ϣ
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolUpgradeCnsInd,
#define UI_CNSTOOL_MSG_UpgradeCns_NTY  ev_UiCnstoolUpgradeCnsInd
			
	/************************************************************************/
	/**  ����ֹͣ���Իظ���Ϣ
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolStopAVMatrixRsp,
#define UI_CNSTOOL_MSG_StopAVMatrix_RSP  ev_UiCnstoolStopAVMatrixRsp
				
	/************************************************************************/
	/**  �п������״̬֪ͨ��Ϣ
	wParam =  aemCam   ������������ͷָ��
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolCamPowerStateNty,
#define UI_CNSTOOL_MSG_CamPowerState_NTY  ev_UiCnstoolCamPowerStateNty
				
	/************************************************************************/
	/**  �����յ���GKע����Ϣ�ı������Ϣ�����״̬
	wParam =  0   
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolGKRspNty,
#define UI_CNSTOOL_MSG_GKRsp_NTY  ev_UiCnstoolGKRspNty
				
	/************************************************************************/
	/**  �����յ���sipע����Ϣ�ı������Ϣ�����״̬
	wParam =  0   
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolSIPRspNty,
#define UI_CNSTOOL_MSG_SIPRsp_NTY  ev_UiCnstoolSIPRspNty
				
	/************************************************************************/
	/**  ��־���ؽ������� 
	wParam =  ����ֵ  
	lparam = 0*/
	/************************************************************************/
	em_CNSTOOL_FTPLOGPROGRESS,
#define WM_CNSTOOL_FTPLOGPROGRESS  em_CNSTOOL_FTPLOGPROGRESS				   
				
	/************************************************************************/
	/**  ��ַ�����뵼����������
	wParam =  ����ֵ  
	lparam = 0*/
	/************************************************************************/	
	em_CNSTOOL_FTPADDRBOOKPROGRESS,
#define WM_CNSTOOL_FTPADDRBOOKPROGRESS  em_CNSTOOL_FTPADDRBOOKPROGRESS      
				
	/************************************************************************/
	/**  ̨���ϴ���������
	wParam =  ����ֵ  
	lparam = 0*/
	/************************************************************************/	
	em_CNSTOOL_CONFSIGNPROGRESS,
#define WM_CNSTOOL_FTPCONFSIGNPROGRESS  em_CNSTOOL_CONFSIGNPROGRESS		   
				
	/************************************************************************/
	/**  �ļ��ϴ��������� 
	wParam =  ����ֵ  
	lparam = 0*/
	/************************************************************************/
	em_CNSTOOL_UPLODEPROGRESS,
#define WM_CNSTOOL_UPLODEPROGRESS  em_CNSTOOL_UPLODEPROGRESS				   

	/************************************************************************/
	/**  �յ�������ϵ���Ϣ
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolCameraPowerOnNty,
#define UI_CNSTOOL_CAMERA_POWER_ON_NTY  ev_UICnstoolCameraPowerOnNty
	
	/************************************************************************/
	/**  �յ�������ѡ��ʽ��Ϣ
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolVideoFormatInd,
#define UI_CNSTOOL_VIDEOFORMAT_IND  ev_UICnstoolVideoFormatInd
		
	/************************************************************************/
	/**  �յ���ʾ��ѡ��ʽ��Ϣ
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolDualVideoFormatInd,
#define UI_CNSTOOL_DUALVIDEOFORMAT_IND  ev_UICnstoolDualVideoFormatInd
			
	/************************************************************************/
	/**  �յ�����������Ϣ
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolCallRateInd,
#define UI_CNSTOOL_CALLRATE_IND  ev_UICnstoolCallRateInd
				
	/************************************************************************/
	/**  �յ���ʾ������Ϣ
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolDualCallRateInd,
#define UI_CNSTOOL_DUALCALLRATE_IND  ev_UICnstoolDualCallRateInd
					
	/************************************************************************/
	/**  �յ��汾֪ͨ��Ϣ
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolVerInfoNty,
#define UI_CNSTOOL_VERINFO_NTY  ev_UICnstoolVerInfoNty
				
	/************************************************************************/
	/**  �յ�����������Ϣ
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolConfDisInd,
#define UI_CNSTOOL_CONFDIS_IND  ev_UICnstoolConfDisInd
				
	/************************************************************************/
	/**  �յ�������ѯ��Ϣ
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolConfPollInd,
#define UI_CNSTOOL_CONFPOOL_IND  ev_UICnstoolConfPollInd
				
	/************************************************************************/
	/**  �յ���Ƶ��ʽ��Ϣ
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolAudioFormatInd,
#define UI_CNSTOOL_AUDIOFORMAT_IND  ev_UICnstoolAudioFormatInd
				
	/************************************************************************/
	/**  �пص���ǽ֪ͨ��Ϣ
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolCfgDisplayInd,
#define UI_CNSTOOL_MSG_DISPLAY_IND  ev_UiCnstoolCfgDisplayInd

	/************************************************************************/
	/**  �յ���������������Ϣ
	wParam = ������������  
	lparam = 0*/
	/************************************************************************/
	ev_UITpadCurtainStateNty,
#define UI_TPAD_CURTAINSTATE_NTY  ev_UITpadCurtainStateNty
	/************************************************************************/
	/**  �յ���ʾ̨����Ϣ
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnIsShowLogoInd,
#define UI_CNC_ISSHOWLOGO_IND  ev_UICnIsShowLogoInd
	/************************************************************************/
	/**  �յ���ʾ̨����Ϣ
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnIsShowLogoNty,
#define UI_CNC_ISSHOWLOGO_NTY  ev_UICnIsShowLogoNty
	/************************************************************************/
	/**  �յ���ʾ�����Ϣ
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnIsShowBannerInd,
#define UI_CNC_ISSHOWBANNER_IND  ev_UICnIsShowBannerInd
	/************************************************************************/
	/**  �յ���ʾ�����Ϣ
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnIsShowBannerNty,
#define UI_CNC_ISSHOWBANNER_NTY  ev_UICnIsShowBannerNty
	/************************************************************************/
	/**  ������������֪ͨ
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UISetEncryptInfo_Nty,
#define UI_ENCRYPTINFO_NTY  ev_UISetEncryptInfo_Nty
	/************************************************************************/
	/**  �����������û�Ӧ
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UISetEncryptInfo_Ind,
#define UI_ENCRYPTINFO_IND  ev_UISetEncryptInfo_Ind

	/************************************************************************/
	/**  ���ݻ����������֪ͨ��Ϣ
	wParam = u32_Ip
	lparam = bSuccess 
	/************************************************************************/
	ev_UiCnstoolDBSerNty,
#define UI_CNSTOOL_MSG_BD_NTY  ev_UiCnstoolDBSerNty
	/************************************************************************/
	/**  ���ݻ���������Ļظ���Ϣ
	wParam = u32_Ip
	lparam = bSuccess 
	/************************************************************************/
	ev_UiCnstoolDBSerInd,
#define UI_CNSTOOL_MSG_BD_IND  ev_UiCnstoolDBSerInd
    /************************************************************************/
	/**  Ftp��Ϣ���÷���
	wParam = u32_Ip
	lparam = bSuccess 
	/************************************************************************/
	ev_CnSetFtpRsp,
#define UI_CNSETFTPRSP  ev_CnSetFtpRsp
    /************************************************************************/
	/**  ��ʾ����ʾ��ʾ
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_CnDisplayShow_Ind,
#define UI_CNDISPLAYSHOW  ev_CnDisplayShow_Ind
    /************************************************************************/
	/**  ���������ʾ֪ͨ
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_MatrixConfigNty,
#define UI_MATRIXCONFIG_NTY  ev_MatrixConfigNty
    /************************************************************************/
	/**  ���󳡾�֪ͨ
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_MatrixSceneNty,
#define UI_MATRIXSCENE_NTY  ev_MatrixSceneNty
    /************************************************************************/
	/**  ���󳡾���ӷ���
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_SaveMatrixSceneInd,
#define UI_SAVEMATRIXSCENE_IND  ev_SaveMatrixSceneInd
    /************************************************************************/
	/**  ��ǰ���󳡾�֪ͨ
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_CurMatrixSceneNty,
#define UI_CURMATRIXSCENE_NTY  ev_CurMatrixSceneNty
	/************************************************************************/
	/**  �޸ľ��󳡾����Ʒ���
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_ReNameMatrixSceneInd,
#define UI_RENAMEMATRIXSCENE_IND  ev_ReNameMatrixSceneInd
    /************************************************************************/
	/**  ɾ�����󳡾�����
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_DeleteMatrixSceneInd,
#define UI_DELETEMATRIXSCENE_IND  ev_DeleteMatrixSceneInd
    /************************************************************************/
	/**  ɾ�����󳡾�����
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_ApplyMatrixSceneInd,
#define UI_APPLYMATRIXSCENE_IND  ev_ApplyMatrixSceneInd

    /************************************************************************/
	/**  �����л�֪ͨ
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_SelectComInd,
#define UI_SELECTCOMG_IND  ev_SelectComInd
};

//* @}*/
#endif 
