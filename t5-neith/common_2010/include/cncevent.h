/*****************************************************************************
模块名      : cms控制台
文件名      : evCmsLib.h
相关文件    : 
文件实现功能: 声明消息（供cms的UI部分和lib（umclib 和 cnclib）部分共同使用）
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/4/23   1.0         俞锦锦      创建
*******************************************************************************/
#pragma once

#ifndef _EVCMSLIB_20110423_H_
#define _EVCMSLIB_20110423_H_

#include "msgIdDispatch.h"
#include "tpeventcomm.h"

/** @defgroup  cms 消息定义部分
 *  @{
 */

// 网真控制台内部消息  

//#define CMS_MSG_BEGIN		WM_USER + 0x100


//umcLib中消息定义
enum EmUiUmcMsg
{

#define UI_UMC_MSG_BEGIN    CMS_MSG_BEGIN

	/************************************************************************/
	/** 连接  UMS  
	wparam = BOOL  //是否连接成功
	lparam = errorCode*/
	/************************************************************************/
	ev_UIUMSConnected		=	UI_UMC_MSG_BEGIN,
#define	UI_UMS_CONNECTED    ev_UIUMSConnected
	
		
		/************************************************************************/
		/**已断开UMS
		wParam = 0
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsDisconnected,
#define UI_UMS_DISCONNECTED	 ev_UIUmsDisconnected



        /************************************************************************/
		/**该账户已经在另一个地方登录
		wParam = u32_IP
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsGrabLoginNotify,
#define UI_UMS_GRAB_LOGIN_NOTIFY	 ev_UIUmsGrabLoginNotify

        /************************************************************************/
		/**UMS的错误信息通知
		wParam = TTPUmsReasonInd
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsReasonInd,
#define UI_UMS_UMSREASON_IND	 ev_UIUmsReasonInd
		

    	/************************************************************************/
		/** ums 命令处理超时
		wParam = 0
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsCmdTimeout,
#define UI_UMS_CMD_TIMEOUT	 ev_UIUmsCmdTimeout


        /************************************************************************/
		/** ums 登录命令处理超时
		wParam = 0
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsLoginTimeout,
#define UI_UMS_LOGIN_TIMEOUT	 ev_UIUmsLoginTimeout
	  
   
    	/************************************************************************/
		/** 会议模板操作结果回复
		wParam = 0
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsOperateConfTemplateRet,
#define UI_UMS_OPERATE_CONFTEMP_RET	 ev_UIUmsOperateConfTemplateRet

		/************************************************************************/
		/** 删除全部模板消息应答
		wParam = 0
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsDelAllConftempRet,
#define UI_UMS_DEL_ALL_CONFTEMP_RET	 ev_UIUmsDelAllConftempRet

		 /************************************************************************/
		 /**	会议模板更新通知
			wParam = confTempID  //发生变更的会议模板ID，删除时为第一个要删除的模板ID
			lparam = 0*/
		/************************************************************************/ 
        ev_UIUmsRefreshConfTemplateList ,
#define UI_UMS_REFRESH_CONFTEMPLATE_LIST  ev_UIUmsRefreshConfTemplateList



    	/************************************************************************/
		/** 用户操作结果回复
		wParam = 0
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsOperateUserRet,
#define UI_UMS_OPERATE_USER_RET	 ev_UIUmsOperateUserRet


		 /************************************************************************/
		 /**	用户更新通知
			wParam = 0
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRefreshUserList  ,
#define UI_UMS_REFRESH_USER_LIST ev_UIUmsRefreshUserList


        /************************************************************************/
		 /**	更新会议列表
			wParam = 0
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRefreshConfList   ,
#define UI_UMS_REFRESH_CONF_LIST ev_UIUmsRefreshConfList 



	    /************************************************************************/
		 /**	开启会议回复
			wParam = confTemplateID 
			lparam =  errorCode*/
		/************************************************************************/ 
	    ev_UIUmsStartConfTemplateRsp  ,
#define UI_UMS_START_CONFTEMPLATE_RSP ev_UIUmsStartConfTemplateRsp
        

		/************************************************************************/
		 /**	邀请cns入会回复
			wParam = strCnsInfoE164/alias 
			lparam =  errorCode*/
		/************************************************************************/ 
	    ev_UIUmsInviteCnsRsp  ,
#define UI_UMS_INVITE_CNS_RSP ev_UIUmsInviteCnsRsp


        /************************************************************************/
		 /**设置发言人结果
			wParam = confID 
			lparam =  EmTpApplySpeakerRet*/
		/************************************************************************/ 
	    ev_UIUmsSetSpeakerRsp  ,
#define UI_UMS_SET_SPEAKER_IND ev_UIUmsSetSpeakerRsp


        /************************************************************************/
		 /**设置哑音结果
			wParam = confID 
			lparam =  bStart*/
		/************************************************************************/ 
	    ev_UIUmsSetMuteCnsRsp  ,
#define UI_UMS_SET_MUTE_CNS_RSP ev_UIUmsSetMuteCnsRsp


        /************************************************************************/
		 /**设置静音结果
			wParam = confID 
			lparam =  bStart*/
		/************************************************************************/ 
	    ev_UIUmsSetQuietCnsRsp  ,
#define UI_UMS_SET_QUIET_CNS_RSP ev_UIUmsSetQuietCnsRsp


        /************************************************************************/
		 /**设置双流结果
			wParam = confID 
			lparam =  bStart*/
		/************************************************************************/ 
	    ev_UIUmsSetDualCnsRsp  ,
#define UI_UMS_SET_DUAL_CNS_RSP ev_UIUmsSetDualCnsRsp


        /************************************************************************/
		 /** 双流源改变通知
			wParam = confID 
			lparam =  cnsID*/
		/************************************************************************/ 
	    ev_UIUmsDualCnsNotify,
#define UI_UMS_DUAL_CNS_NOTIFY ev_UIUmsDualCnsNotify

 
         /************************************************************************/
		 /**	更新发言人通知
			wParam = confID
			lparam = speakerID*/
		/************************************************************************/ 
	    ev_UIUmsChangeSpeakerNotify,
#define UI_UMS_CHANGE_SPEAKER_NOTIFY ev_UIUmsChangeSpeakerNotify


            /************************************************************************/
		 /**	主席
			wParam = confID  下级会议ID
			lparam = */
		/************************************************************************/ 
	    ev_UIUmsChairCnsNotify,
#define UI_UMS_CHAIR_CNS_NOTIFY ev_UIUmsChairCnsNotify



    /************************************************************************/
		 /**	级联会议通知
			wParam = confID  下级会议ID
			lparam = */
		/************************************************************************/ 
	    ev_UIUmsCascadeConfNotify,
#define UI_UMS_CASCADE_CONF_NOTIFY ev_UIUmsCascadeConfNotify



        /************************************************************************/
		 /**	挂断会议回复
			wParam = confID 
			lparam = errorCode*/
		/************************************************************************/ 
	    ev_UIUmsHangupConfRsp ,
#define UI_UMS_HANGUP_CONF_RSP ev_UIUmsHangupConfRsp


		/************************************************************************/
		 /**	更新会议中的会场列表
			wParam = confID
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRefreshConfCnsList  ,
#define UI_UMS_REFRESH_CONFCNS_LIST ev_UIUmsRefreshConfCnsList

 
		/************************************************************************/
		 /**	更新会议中的会场列表
			wParam = confID
			lparam =  TConfCnsInfo*/
		/************************************************************************/ 
	    ev_UIUmsUpdateConfCnsList  ,
#define UI_UMS_UPDATE_CONFCNS_LIST ev_UIUmsUpdateConfCnsList
 

		/************************************************************************/
		 /**	更新会议 
		 
		/************************************************************************/ 
	    ev_UIUmsUpdateConfInfo  ,
#define UI_UMS_UPDATE_CONFINFO ev_UIUmsUpdateConfInfo


		/************************************************************************/
		 /**	更新会议中的混音列表
			wParam = confID
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRefreshConfAudMixList  ,
#define UI_UMS_REFRESH_CONFAUDMIX_LIST ev_UIUmsRefreshConfAudMixList

        /************************************************************************/
		 /** 更新会议中的混音列表-- 本地cns所在会议
			wParam = confID
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRefreshConfAudMixListLocal  ,
#define UI_UMS_REFRESH_CONFAUDMIX_LIST_LOCAL ev_UIUmsRefreshConfAudMixListLocal

		/************************************************************************/
		 /**	更新会议中轮询列表
			wParam = confID
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRefreshConfPollList  ,
#define UI_UMS_REFRESH_CONFPOLL_LIST ev_UIUmsRefreshConfPollList


 	/************************************************************************/
		 /** ums注册服务器信息通知
			wParam = 0
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRegInfoNotify  ,
#define UI_UMS_REG_INFO_NOTIFY ev_UIUmsRegInfoNotify


  	/************************************************************************/
		 /**	ums注册服务器结果
			wParam = EmTpCnsRegUms:注册返回的错误码
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
		/**	 系统时间通知
		/************************************************************************/ 
	    ev_GetUmsSystimeNotify  ,
#define UI_GET_UMS_SYSTIME  ev_GetUmsSystimeNotify


        /************************************************************************/
		/**	 会议中断通知
		/************************************************************************/ 
	    ev_HungUp_Conf_Reason,
#define UI_HUNGUP_UMS_CONF_REASON  ev_HungUp_Conf_Reason


        /************************************************************************/
		/**	 电视墙风格通知
             To Umc
		/************************************************************************/ 
        ev_Tvw_HduPlanNotify,
#define UI_UMS_HDUPLAN_NOTIFY  ev_Tvw_HduPlanNotify

        /************************************************************************/
		/**	 更新会议模板资源占用情况
             To Umc
		/************************************************************************/ 
        ev_ConfTmp_ResUsedCountNotify,
#define UI_UMS_CONFTMPRESUSEDCOUNT_NOTIFY  ev_ConfTmp_ResUsedCountNotify
         /************************************************************************/
		 /**	会议讨论添加会场消息反馈
			wParam = NULL
			lparam = EmDisListOprReslt*/
		/************************************************************************/ 
	    ev_UIAudMixDisListOprInd,
#define UI_UMS_AUDMIX_DISLISTOPR_IND ev_UIAudMixDisListOprInd
        /************************************************************************/
		 /**	讨论语音激励开关显隐反馈
			wParam = BOOL
			lparam = NULL*/
		/************************************************************************/ 
	    ev_UIAudExcitationVisibleInd,
#define UI_UMS_AUDEXCITATION_VISIBLE_IND ev_UIAudExcitationVisibleInd
         /************************************************************************/
		 /**	语音激励反馈
			wParam = NULL
			lparam = TConfAuxMixVacOpr*/
		/************************************************************************/ 
	    ev_UIAuxMixVacOprInd,
#define UI_UMS_AUDMIXVAC_IND ev_UIAuxMixVacOprInd
		/************************************************************************/
		 /** 开启会议讨论ind 用于界面通知失败原因
			wParam = NULL
			lparam = TConfAuxMixVacOpr*/
		/************************************************************************/ 
	    ev_UIAMixUpdateInd,
#define UI_UMS_AUDMIXIND ev_UIAMixUpdateInd

		ev_UIUmsEnd,
#define UI_UMS_MSG_END  ev_UIUmsEnd
		
} ;


//cncLib中消息定义
enum EmUiCnsMsg
{

#define UI_CNC_MSG_BEGIN  	UI_UMS_MSG_END + 0x1 

	/************************************************************************/
	/** 连接  CNS 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UICnsConnect	= UI_CNC_MSG_BEGIN,
#define	UI_CNS_CONNECTED  ev_UICnsConnect
	
	/************************************************************************/
	/** 已断开CNS
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UICnsDisconnected,
#define UI_CNS_DISCONNECTED	 ev_UICnsDisconnected

   /************************************************************************/
	/** 登录CNS 接收回复超时
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UICnsLoginTimeOut,
#define UI_CNS_LOGIN_TIMEOUT	 ev_UICnsLoginTimeOut
		 
    
	/************************************************************************/
	/**	更新地址簿
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UIAddrbookChanged,
#define UI_CNS_ADDRBOOK_CHANGED		ev_UIAddrbookChanged

	/************************************************************************/
	/**	地址簿添加条目通知
		wParam = EntryIndex
		lparam = 0*/
	/************************************************************************/ 
	ev_UIAddrbookAddEntry,
#define	UI_CNS_ADDRBOOK_ADDENTRY    ev_UIAddrbookAddEntry

	/************************************************************************/
	/**	地址簿添加条目、修改、删除条目通知
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
	/**	地址簿操作失败通知
		wParam = EntryIndex
		lparam = 0*/
	/************************************************************************/ 
    ev_UIAddrbookOptFailed,
#define	UI_CNS_ADDRBOOKOPT_FAILED      ev_UIAddrbookOptFailed

	/************************************************************************/
	/**	CNS信息
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsInfoNotify,
#define	UI_CNS_CNSINFO_NOTIFY       ev_UICnsInfoNotify

	/************************************************************************/
	/**	会议状态
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsConfStateNotify,
#define	UI_CNS_CONFSTATE_NOTIFY     ev_UICnsConfStateNotify

	/************************************************************************/
	/**	全场静音/哑音状态
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsAllMuteAndAllQuiteStateNotify,
#define	UI_CNS_ALLMUTE_ALLQUITE_NOTIFY     ev_UICnsAllMuteAndAllQuiteStateNotify

	/************************************************************************/
	/**	cns 离开会议
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsLeaveConfNotify,
#define	UI_CNS_LEAVECONF_NOTIFY     ev_UICnsLeaveConfNotify


 	/************************************************************************/
	/** 屏状态通知
	wParam = screenID
	lparam = emScreenState  
	/************************************************************************/
	ev_UiScreenStateNotify,
#define UI_CNS_SCREEN_STATE_NOTIFY  ev_UiScreenStateNotify

	/************************************************************************/
	/** 屏名通知
	wParam = screenID
	lparam = cstringCnsName */
	/************************************************************************/
	ev_UiScreenNameNotify,
#define UI_CNS_SCREEN_NAME_NOTIFY   ev_UiScreenNameNotify

	/************************************************************************/
	/** 设置选看回复
	wParam = screenID
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsSelViewInd,
#define UI_CNS_SEL_VIEW_IND   ev_UiCnsSelViewInd


    /************************************************************************/
	/** 选看通知
	wParam = screenID
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsCancleSelViewNty,
#define UI_CNS_SEL_VIEW_NTY   ev_UiCnsCancleSelViewNty

    /************************************************************************/
	/** 设置轮询回复
	wParam =  bSucess
	lparam = emReslut */
	/************************************************************************/
	ev_UiCnsStartPollRsp,
#define UI_CNS_START_POLL_RSP   ev_UiCnsStartPollRsp


    /************************************************************************/
	/** 轮询状态通知
	wParam =  bPoll
	lparam = 0 */
	/************************************************************************/
	ev_UiCnsPollStateNty,
#define UI_CNS_POLL_STATE_NOTIFY   ev_UiCnsPollStateNty


        /************************************************************************/
	/** 点对点会议挂断通知
	wParam =  bPoll
	lparam = 0 */
	/************************************************************************/
	evUiCnsHungupP2pNty,
#define UI_CNS_HUNGUP_P2P_NOTIFY   evUiCnsHungupP2pNty

   /************************************************************************/
	/** 设置双流回复
	wParam =  bStart
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsStartDualRsp,
#define UI_CNS_START_DUAL_RSP   ev_UiCnsStartDualRsp

	/************************************************************************/
	/** 双流状态通知
	wParam =  bStart
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsDualStateNty,
#define	UI_CNS_DUAL_STATE_NOTIFY   ev_UiCnsDualStateNty

	
   	/************************************************************************/
	/** 双流状态通知
	wParam =  bStart
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsRecvDualNty,
#define	UI_CNS_RECV_DUAL_NOTIFY   ev_UiCnsRecvDualNty

    /************************************************************************/
	/** 双流加密密钥通知
	/************************************************************************/
    ev_UiCnsRecvDualKeyNty,
#define UI_CNS_DUAL_KEY_NOTIFY   ev_UiCnsRecvDualKeyNty

    	/************************************************************************/
	/** 接收双流时异常中断
 
	/************************************************************************/
	ev_UiRecvDualInterruptNty,
#define	UI_RECV_DUAL_INTERRUPT   ev_UiRecvDualInterruptNty

	/************************************************************************/
	/** 发言坐席
	wParam = seatID
	lparam =  0 */
	/************************************************************************/
	ev_UiSpokesSeatNotify,
#define UI_CNS_SPOKES_SEAT_NOTIFY   ev_UiSpokesSeatNotify

	/************************************************************************/
	/* 静音哑音通知  
	wparam = bQuite 	是静音还是哑音.TRUE 静音， FALSE 哑音
	lparam = bOn		是开启还是关闭.开启静音使当前没有音频输出,反之是关闭静音*/
	/************************************************************************/
	ev_UiCnsQuiteMute,
#define UI_CNS_QUITE_MUTE           ev_UiCnsQuiteMute

	/************************************************************************/
	/* 输入音量更新通知  
	wparam = 0 	
	lparam = 0		
	/************************************************************************/
	ev_UiCnsInVolUpdate,
#define	UI_CNS_INVOL_UPDATE         ev_UiCnsInVolUpdate

	/************************************************************************/
	/* 输出量更新通知  
	wparam = 0 	
	lparam = 0		
	/************************************************************************/
	ev_UiCnsOutVolUpdate,
#define	UI_CNS_OUTVOL_UPDATE        ev_UiCnsOutVolUpdate      
    
	/************************************************************************/
	/**	Sip注册信息
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UIRegSipNotify,
#define	UI_CNS_REGSIP_NOTIFY       ev_UIRegSipNotify

	/************************************************************************/
	/**	Sip注册是否成功
		wParam = BOOL
		lparam = 会场名*/
	/************************************************************************/ 
	ev_UIRegSipResultNotify,
#define	UI_CNS_REGRESULT_NOTIFY       ev_UIRegSipResultNotify

	/************************************************************************/
	/**	Sip注册别名重复通知
		wParam = BOOL
		lparam = 会场名*/
	/************************************************************************/ 
	ev_UIRegSipAliasRepeatNotify,
#define	UI_CNS_SIPREG_ALIASREPEAT_NOTIFY       ev_UIRegSipAliasRepeatNotify

    /************************************************************************/
	/**	得到GK注册结果
	 
	/************************************************************************/ 
	ev_UIRegGkResultRsp,
#define	UI_CNS_REG_GK_RSP       ev_UIRegGkResultRsp


     /************************************************************************/
	/**	服务器通知 GK注册信息
	 
	/************************************************************************/ 
	ev_UIRegGkNty,
#define	UI_CNS_REG_GK_NTY       ev_UIRegGkNty


	/**	网络信息通知
		wParam = 0
		lparam = 0*/
	/************************************************************************/
	ev_UICnsEthnetInfoNotify,
#define	UI_CNS_ETHNETINFO_NOTIFY       ev_UICnsEthnetInfoNotify

    /**	网络类型通知
		wParam = 0
		lparam = 0*/
	/************************************************************************/
	ev_UICnsIPVTypeNotify,
#define	UI_CNS_IPVTYPE_NOTIFY       ev_UICnsIPVTypeNotify

	/**	IPV6配置通知
		wParam = 0
		lparam = 0*/
	/************************************************************************/
	ev_UICnsIPV6CfgNotify,
#define	UI_CNS_IPV6CFG_NOTIFY       ev_UICnsIPV6CfgNotify
	
	/************************************************************************/
	/**	主会场名通知
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsMainRoomInd,
#define	UI_CNS_MAINROOM_NOTIFY       ev_UICnsMainRoomInd

	/************************************************************************/
	/**	会场离线通知
		wParam = 会场名
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsRoomOffline,
#define UI_CNS_ROOMOFFLINE           ev_UICnsRoomOffline

    /************************************************************************/
	/**	系统时间回复
		wParam = TTpTime
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsSystimeRsp,
#define UI_CNS_SYSTIME_RSP           ev_UICnsSystimeRsp

	/************************************************************************/
	/**	Cns会场列表
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsCnListNty,
#define	UI_CNS_CNLIST_NOTIFY         ev_UICnsCnListNty

	/************************************************************************/
	/**	连接CNS会场通知
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsInsConnect,
#define	UI_CNSINS_CONNECTED          ev_UICnsInsConnect
 
	/************************************************************************/
	/**	开启双流码流回复
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsStartDualCdStrmRsp,
#define	UI_CNSINS_START_DUALCODESTREAM_RSP          ev_UICnsStartDualCdStrmRsp   

	/************************************************************************/
	/**	选看双流码流回复
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsScrnDisplayDualRsp,
#define	UI_CNS_SCRN_DISPLAY_DUAL_RSP          ev_UICnsScrnDisplayDualRsp  
    

    /************************************************************************/
	/**	取消选看双流码流回复
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsStopScrnDisplayDualRsp,
#define	UI_CNS_STOP_SCRN_DISPLAY_DUAL_RSP          ev_UICnsStopScrnDisplayDualRsp  
	
   /************************************************************************/
	/**	回显 回复
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsScrnDisplayLocalRsp,
#define	UI_CNS_SCRN_DISPLAY_LOCAL_RSP          ev_UICnsScrnDisplayLocalRsp  

    /************************************************************************/
	/**取消	回显 回复
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsStopScrnDisplayLocalRsp,
#define	UI_CNS_STOP_SCRN_DISPLAY_LOCAL_RSP          ev_UICnsStopScrnDisplayLocalRsp  

	/************************************************************************/
	/**双流源掉线通知
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsRoomDualOfflineNty,
#define UI_CNS_DUALOFFLINE_NOTIFY         ev_UICnsRoomDualOfflineNty

	/************************************************************************/
	/**更新会议模板通知
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsRefreshConfTemplateList,
#define UI_CNS_REFRESH_CONFTEMPLATE_LIST         ev_UICnsRefreshConfTemplateList

	/************************************************************************/
	/**更新会议模板通知
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsRefreshGlobalAddrbook,
#define UI_CNS_REFRESH_GLOBAL_ADDRBOOK         ev_UICnsRefreshGlobalAddrbook

	/************************************************************************/
	/**更新会议模板通知
		wParam =  BOOL : 表示是否是sip地址 
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsRefreshGlobalAddrbookEx,
#define UI_CNS_REFRESH_GLOBAL_ADDRBOOKEX       ev_UICnsRefreshGlobalAddrbookEx

    /************************************************************************/
	/**双流源信息通知
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
    ev_UICnsVgaInfoNty,
#define UI_CNS_VGAINFO_NOTIFY                  ev_UICnsVgaInfoNty

    /************************************************************************/
	/**会议中双流源信息通知
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
    ev_UICnsConfVgaInfoNty,
#define UI_CNS_CONFVGAINFO_NOTIFY              ev_UICnsConfVgaInfoNty

    /************************************************************************/
	/**会议中切换双流源通知
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
    ev_UICnsSelDualInputPortInd,
#define UI_CNS_SELDUALPORT_IND                 ev_UICnsSelDualInputPortInd

	    /************************************************************************/
	/**不在会议中切换双流源通知
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
    ev_UICnsSelDefaultDualInputPortInd,
#define UI_CNS_SELDEFAULTDUALPORT_IND                 ev_UICnsSelDefaultDualInputPortInd
	/************************************************************************/
	/**	服务器通知 静态NAT注册信息
	 
	/************************************************************************/ 
	ev_UIRegNatNty,
#define	UI_CNS_REG_NAT_NTY       ev_UIRegNatNty


	/************************************************************************/
	/**  网管配置列表页添加修改网管当前选中数据发送
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiCnsNetMngSelDataClick,
#define UI_CNS_MSG_NETMNGSELDATA_Click  ev_UiCnsNetMngSelDataClick
	/************************************************************************/
	/**  系统待机页面信息通知
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiCnsSleepInfoNotify,
#define UI_CNS_SLEEPINFO_NOTIFY  ev_UiCnsSleepInfoNotify

    /************************************************************************/
	/**  中控温度通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSchTempNotify,
#define UI_CNS_SCHTEMP_NTY  ev_UiCnsSchTempNotify
    /************************************************************************/
	/**  中控灯光通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSchLightNotify,
#define UI_CNS_SCHLIGHT_NTY  ev_UiCnsSchLightNotify
    /************************************************************************/
	/**  中控面板状态通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSchStateNotify,
#define UI_CNS_SCHSTATE_NTY  ev_UiCnsSchStateNotify
    /************************************************************************/
	/**  系统电源开关回复
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSchPowerInd,
#define UI_CNS_SCHPOWER_IND  ev_UiCnsSchPowerInd
     /************************************************************************/
    /**  灯光开关回复
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSchAllLightInd,
#define UI_CNS_SCHALLLIGHT_IND  ev_UiCnsSchAllLightInd
    /************************************************************************/
	/**  主灯开关回复
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSchMidLightInd,
#define UI_CNS_SCHMIDLIGHT_IND  ev_UiCnsSchMidLightInd
    /************************************************************************/
	/**  主灯开关回复
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSchScrLightInd,
#define UI_CNS_SCHSCRLIGHT_IND  ev_UiCnsSchScrLightInd
    /************************************************************************/
	/**  电视机状态通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsTVStateNotify,
#define UI_CNS_TVSTATE_NTY  ev_UiCnsTVStateNotify
    /************************************************************************/
	/**  电视机开关回复
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSeleteTvInd,
#define  UI_CNS_SELETETV_IND ev_UiCnsSeleteTvInd
    /************************************************************************/
	/**  电视机选中状态回复
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsTVPowerModeInd,
#define  UI_CNS_TVPOWERMODE_IND ev_UiCnsTVPowerModeInd
    /************************************************************************/
	/**  文档摄像机状态通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsDCamStateNotify,
#define UI_CNS_DCAMSTATE_NTY  ev_UiCnsDCamStateNotify
	    /************************************************************************/
	/**  文档摄像机预置位选中状态通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsDCamPreposInd,
#define UI_CNS_DCAMPREPOS_IND  ev_UiCnsDCamPreposInd
    /************************************************************************/
	/**  文档摄像机选择切换回复
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsDCamSelectedInd,
#define UI_CNS_DCAMSELECTED_IND  ev_UiCnsDCamSelectedInd
    /************************************************************************/
	/**  文档摄像机开关回复
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsDCamPowerInd,
#define UI_CNS_DCAMPOWER_IND  ev_UiCnsDCamPowerInd
    /************************************************************************/
	/**  文档摄像机快照回复
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsDocSnapShotInd,
#define UI_CNS_DOCSNAPSHOT_IND  ev_UiCnsDocSnapShotInd
	/************************************************************************/
	/**  文档摄像机型号通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsDCamTypeInd,
#define UI_CNS_DCAMTYPE_IND  ev_UiCnsDCamTypeInd
	    /************************************************************************/
	/**  文档摄像zoom回复
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsDCamZoomInd,
#define UI_CNS_DCAMZOOM_IND  ev_UiCnsDCamZoomInd
    /************************************************************************/
	/**  空调状态通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsACStateNotify,
#define UI_CNS_ACSTATE_NTY  ev_UiCnsACStateNotify

	/************************************************************************/
	/**  空调选中项回复
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSelectAirInd,
#define  UI_CNS_SELECTAIR_IND ev_UiCnsSelectAirInd
	/************************************************************************/
	/**  空调全部应用开启后结果回复
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsApplyToAllInd,
#define  UI_CNS_APPLYTOALL_IND ev_UiCnsApplyToAllInd

	/************************************************************************/
	/**  空调电源开关状态通知
	wParam = *   
	lparam = */
	/************************************************************************/
     ev_UiCnsACPowerStateInd,
 #define UI_CNS_ACPOWERSTATE_IND  ev_UiCnsACPowerStateInd
    /************************************************************************/
	/**  中控待机通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiTPadCentreSleepNotify,
#define UI_TPAD_CENTRESLEEP_NTY  ev_UiTPadCentreSleepNotify

    /************************************************************************/
	/**  TPad登录用户通知
	wParam = User*   
	lparam = */
	/************************************************************************/
    ev_UiTPadLoginUserNotify,
#define UI_TPAD_LOGINUSER_NOTIFY  ev_UiTPadLoginUserNotify

    /************************************************************************/
	/**  TPad系统升级通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiTPadUpdateSystemCmd,
#define UI_TPAD_UPDATESYS_CMD  ev_UiTPadUpdateSystemCmd

    /************************************************************************/
	/**  UMS的错误信息通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiUmsReason_Ind,
#define UI_CNS_UMSREASON_IND   ev_UiUmsReason_Ind

    /************************************************************************/
	/**  cnc进行系统名称修改通知  dyy 2013年8月29日
	wParam = 系统名称   
	lparam = */
	/************************************************************************/
    ev_UiTPadCncSetSysNameNotify,
#define UI_TPAD_SETSYSNAME  ev_UiTPadCncSetSysNameNotify

    /************************************************************************/
	/**  TPad Home键响应
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiTPadHomeKeyNotify,
#define UI_TPAD_HOMEKEY_NOTIFY  ev_UiTPadHomeKeyNotify

    /************************************************************************/
	/**  cnc会议状态通知  
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiTPadConfStateNty,
#define UI_CONFSTATE_NTY  ev_UiTPadConfStateNty

    /************************************************************************/
	/**  开启pc双流的结果 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiTPadFileDualResult,
#define UI_FILE_DUAL_RESULT  ev_UiTPadFileDualResult

    /************************************************************************/
	/**  接收pc双流远端地址 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiTPadFileDualRcvAddr,
#define UI_FILE_DUAL_RCVADDR  ev_UiTPadFileDualRcvAddr

    /************************************************************************/
	/**  停止pc双流 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiTPadStopFileDual,
#define UI_FILE_DUAL_STOP  ev_UiTPadStopFileDual

    /************************************************************************/
	/**  pc双流key的通知 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiTPadFileDualkey,
#define UI_FILE_DUAL_KEY  ev_UiTPadFileDualkey

    /************************************************************************/
	/**  远端请求关键帧 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiTPadFileKeyFrame,
#define UI_FILE_DUAL_KEYFRAME_REQ  ev_UiTPadFileKeyFrame

	/************************************************************************/
	/** 设置选看电视墙回复
	wParam = screenID
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsSelTVSViewRsp,
#define UI_CNS_SEL_TVSVIEW_RSP   ev_UiCnsSelTVSViewRsp


    /************************************************************************/
	/** 取消选看电视墙回复
	wParam = screenID
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsCancleSelTVSViewRsp,
#define UI_CNS_CANCLE_SEL_TVSVIEW_RSP   ev_UiCnsCancleSelTVSViewRsp

    /************************************************************************/
	/** 会议主席通知
	wParam = 
	lparam =  */
	/************************************************************************/
	ev_UiCnsChairConfInfoNty,
#define UI_CNS_CHAIRCONFINFO_NTY   ev_UiCnsChairConfInfoNty

	/************************************************************************/
	/**  主视频源设置响应
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnSetVedioInfoInd,
#define UI_CNS_SETMAINVEDIO_IND  ev_UiCnSetVedioInfoInd
	/************************************************************************/
	/**  全景摄像机信息通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnPanCamInfoNty,
#define UI_CNS_PANCAMINFO_NTY  ev_UiCnPanCamInfoNty
		/************************************************************************/
	/**  全景摄像机保存预置位通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnPanCamPresetSaveInd,
#define UI_CNS_PANCAMPRESETSAVE_IND  ev_UiCnPanCamPresetSaveInd
	/************************************************************************/
	/**  全景摄像机删除预置位通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnPanCamPresetDeleteInd,
#define UI_CNS_PANCAMPRESETDEL_IND  ev_UiCnPanCamPresetDeleteInd
	/************************************************************************/
	/**  全景摄像机调用预置位通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnPanCamPresetImpleInd,
#define UI_CNS_PANCAMPRESETIMPLE_IND  ev_UiCnPanCamPresetImpleInd
	/************************************************************************/
	/**  全景摄像机预置位名称保存结果通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnPanCamPresetNameSaveInd,
#define UI_CNS_PANCAMPRESETNAMESAVE_IND  ev_UiCnPanCamPresetNameSaveInd
	/************************************************************************/
	/**  全景摄像机选择通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnPanCamSelInd,
#define UI_CNS_PANCAMSEL_IND  ev_UiCnPanCamSelInd

		/************************************************************************/
	/** 全景摄像机开启结果通知
	wParam = screenID
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsPanCamStartRsp,
#define UI_CNS_PANCAMSTART_RSP   ev_UiCnsPanCamStartRsp

    /************************************************************************/
	/** 画面合成器状态通知
	wParam = 
	lparam =  */
	/************************************************************************/
    ev_UiCnsBrdVmpNty,
#define UI_CNS_BRDVMP_NTY        ev_UiCnsBrdVmpNty

    /************************************************************************/
	/** 占用画面合成器回复
	wParam = 
	lparam =  */
	/************************************************************************/
    ev_UiCnsRervesBrdVmpInd,
#define UI_CNS_RERVESBRDVMP_IND  ev_UiCnsRervesBrdVmpInd

    /************************************************************************/
	/** 保存画面合成预案回复
	wParam = 
	lparam =  */
	/************************************************************************/
    ev_UiCnsSaveVmpCfgInd,
#define UI_CNS_SAVEVMPCFG_IND        ev_UiCnsSaveVmpCfgInd

    /************************************************************************/
	/**  电视墙通知
	wParam =    
	/************************************************************************/
    ev_UiHduPlanNty,
#define UI_HDUPLAN_NTY  ev_UiHduPlanNty
	/************************************************************************/
	/**  电视墙多画面操作反馈
	wParam =    
	/************************************************************************/
    ev_UiHduChangModeInd,
#define UI_HDUCHANGEMODE_IND  ev_UiHduChangModeInd
	/************************************************************************/
	/**  电视墙设置音量反馈
	wParam =    
	/************************************************************************/
    ev_UiHduVolumeInd,
#define UI_HDUVOLUME_IND  ev_UiHduVolumeInd

	/************************************************************************/
	/**  电视墙停止观看
	wParam =    
	/************************************************************************/
    ev_UiHduStopPlayInd,
#define UI_HDUSTOPPLAY_IND  ev_UiHduStopPlayInd
	/************************************************************************/
	/**  电视墙停止观看
	wParam =    
	/************************************************************************/
    ev_UiHduPlayInd,
#define UI_HDUPLAY_IND  ev_UiHduPlayInd


    /************************************************************************/
	/** TPad调出中控
	wParam = 
	lparam =  */
	/************************************************************************/
    ev_UiTpadShowCenterCtrlNty,
#define UI_TPAD_SHOWCENTRECTRL_NTY        ev_UiTpadShowCenterCtrlNty
	/************************************************************************/
	/** 空闲时双流ind
	wParam = screenID
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsSpareDualInd,
#define UI_CNS_SPAREDUAL_IND   ev_UiCnsSpareDualInd
	/************************************************************************/
	/** 空闲时双流NTY
	wParam = screenID
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsSpareDualNty,
#define UI_CNS_SPAREDUAL_NTY   ev_UiCnsSpareDualNty
	/************************************************************************/
	/**  视频源状态通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnVidSrcNty,
#define UI_CNS_VIDSRC_NTY  ev_UiCnVidSrcNty
	/************************************************************************/
	/** 单独控制cns语音激励IND
	wParam = bIsMix
	lparam = bIsScucces */
	/************************************************************************/
	ev_UiCnsAuxMixInd,
#define UI_CNS_CNAUXMIX_IND   ev_UiCnsAuxMixInd
	/************************************************************************/
	/** 辅视频通知
	wParam = bLimit 是否限制第二路主视频选择
	lparam =  */
	/************************************************************************/
	ev_UiCnsMinVideoInfoNty,
#define UI_CNS_MINVEDIOINFO_NTY   ev_UiCnsMinVideoInfoNty
	/************************************************************************/
	/** 主视频设置通知 */
	/************************************************************************/
	ev_UiCnsSetVideoInfoNty,
#define UI_CNS_SETVEDIOINFO_NTY   ev_UiCnsSetVideoInfoNty
    /************************************************************************/
	/** 终端会场入会请求
	wParam =  0
	lparam = 0 */
	/************************************************************************/
	ev_UiUmsToCncJoinConf_Req,
#define UI_UMS_JOINCONF_REG   ev_UiUmsToCncJoinConf_Req
	/************************************************************************/
	/**  WB新会议呼进请求Tpad加入 
	wParam =    
	lparam = IP*/
	/************************************************************************/
    ev_UiNewWBConfCallReq,
#define UI_NEWWBCONFCALL_REQ  ev_UiNewWBConfCallReq
	    /************************************************************************/
	/**  数据会议状态发给界面
	wParam =    
	lparam = 是否在数据会议中
	/************************************************************************/
    ev_UiWBConfStateNty,
#define UI_WBCONFSTATE_NTY  ev_UiWBConfStateNty
   /************************************************************************/
	/**  本端主动开启一个数据会议
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiSelfStartWBConf,
#define UI_SELFSTARTWBCONFNTY  ev_UiSelfStartWBConf

    /************************************************************************/
	/**  加入数据会议 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiJoinWBConfCmd,
#define UI_JOINWBCONF_CMD  ev_UiJoinWBConfCmd
    /************************************************************************/
	/**  网呈会议结束，离开数据会议  
	wParam =    
	lparam = ip */
	/************************************************************************/
    ev_UiLeaveWBConfNty,
#define UI_LEAVEWBCONF_NTY  ev_UiLeaveWBConfNty
    /************************************************************************/
	/**  会议获得会场信息时将会场名发给界面
	wParam =    
	lparam = 会场名 m_achRoomName*/
	/************************************************************************/
    ev_UiConfRoomName,
#define UI_CONFROOMNAME_NTY  ev_UiConfRoomName
    /************************************************************************/
	/**  WB配置IP发给界面 cns->tpad 
	wParam =    
	lparam = IP*/
	/************************************************************************/
    ev_UiTppSetDataServerInfoNty,
#define UI_TPPSETDATASERVERINFONTY  ev_UiTppSetDataServerInfoNty
    /************************************************************************/
	/**  WB配置IP是否操作成功结果反馈给界面 cns->tpad 
	wParam =    
	lparam = IP*/
	/************************************************************************/
	ev_UiTppSetDataServerInd,
#define	UI_TPPSETDATASERVER_IND  ev_UiTppSetDataServerInd

    /************************************************************************/
	/**  本端开启视频会议
	wParam =    
	lparam = 
	/************************************************************************/
    ev_UiSelfStartConfCmdNty,
#define UI_SELFSTARTCONF_CMD  ev_UiSelfStartConfCmdNty
    /************************************************************************/
	/**  修改白板服务器ip
	wParam =  bool 是否成功  
	lparam = IP*/
	/************************************************************************/
    ev_UiSetWBServerIpNty,
#define UI_SETWBSERVERIP_NTY  ev_UiSetWBServerIpNty
    /************************************************************************/
	/**  点对点会议数据会议名消息 cns->tpad 
	wParam =    
	lparam = IP*/
	/************************************************************************/
    ev_UiTppSetDataConfNameNty,
#define UI_TPPSETDATACONFNAMENTY  ev_UiTppSetDataConfNameNty
    /************************************************************************/
	/**  升级T300通知 cns->tpad 
	wParam =    
	lparam = IP*/
	/************************************************************************/
    ev_UiTppUpDateT300Nty,
#define UI_TPPUPDATET300NTY  ev_UiTppUpDateT300Nty
    /************************************************************************/
	/** TPad调出系统设置
	wParam = 
	lparam =  */
	/************************************************************************/
    ev_UiTpadShowSysConfigNty,
#define UI_TPAD_SHOWSYSCONFIG_NTY        ev_UiTpadShowSysConfigNty
    /************************************************************************/
	/** TPad调出会场管理
	/************************************************************************/
    ev_UiTpadShowCnsManageNty,
#define UI_TPAD_SHOWCNSMANAGE_NTY        ev_UiTpadShowCnsManageNty

	
	/************************************************************************/
		/** 出现异常
		wParam = 异常错误码
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
	/**  单击会场列表中的cns条目
	wParam =  cnsInfo
	lparam = 所单击的item相对于屏幕的rect*/
	/************************************************************************/
	ev_UiCnsConfItemClick,
#define UI_CONF_CNS_ITEM_CLICK  ev_UiCnsConfItemClick
   

   /************************************************************************/
	/**  单击会议模板列表中的 条目
	wParam =  wConfTempID
	lparam = 所单击的item相对于屏幕的rect*/
	/************************************************************************/
    ev_UiCnsConfTempItemClick,
#define UI_CONF_TEMP_ITEM_CLICK  ev_UiCnsConfTempItemClick

   /************************************************************************/
	/**  单击地址簿列表中的条目呼叫
	wParam =  Args_ClickItemInfo
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsAddrItemCallClick,
#define	UI_ADDR_ITEM_CALL_CLICK  ev_UiCmsAddrItemCallClick


   /************************************************************************/
	/**  更新时间通知,由titlebar通知 时间设置界面
	wParam =  SYSTEMTIME
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsUpdateTime,
#define	UI_CMS_UPDATE_SYSTEM_TIME  ev_UiCmsUpdateTime


      /************************************************************************/
	/**  设置时间通知    由时间设置界面通知titlebar
	wParam =  SYSTEMTIME
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsModifySystemTime,
#define	UI_CMS_MODIFY_SYSTEM_TIME  ev_UiCmsModifySystemTime

  /************************************************************************/
	/**  mainmenu 点击了 Toolbar
	wParam =    
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsMainmenuClickToolBtn,
#define	UI_CMS_CLICK_TOOL_BTN  ev_UiCmsMainmenuClickToolBtn
  
   /************************************************************************/
	/**  calling timer 到时间 主会场未上线
	wParam =    
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsCallingTimeOut,
#define	UI_CMS_CALLING_TIME_OUT  ev_UiCmsCallingTimeOut

    /************************************************************************/
	/**  显示呼叫dlg
	wParam =    
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsShowCallingDlg,
#define	UI_UMS_SHOW_CALLING_DLG  ev_UiCmsShowCallingDlg


     /************************************************************************/
	/**  隐藏呼叫dlg
	wParam =    
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsHideCallingDlg, 
#define	UI_UMS_HIDE_CALLING_DLG  ev_UiCmsHideCallingDlg

	/************************************************************************/
	/**  显示告警dlg
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
	/**  登录ok
	wParam =    
	lparam = 0*/
	/************************************************************************/
    ev_UiCmsLoginOk,
#define WM_CMS_UI_LOGIN_OK  ev_UiCmsLoginOk

   /************************************************************************/
	/**  自动登录CNS会场
	wParam =    
	lparam = 0*/
	/************************************************************************/	
	ev_UiCmsAutoLogCnsIns,
#define UI_CMS_AUTOLOG_CNSINS   ev_UiCmsAutoLogCnsIns


   /************************************************************************/
	/** 网络断开
	wParam =    
	lparam = 0*/
	/************************************************************************/
   ev_UiCmsNetDisconnect,
#define WM_NET_DISCONNECT  ev_UiCmsNetDisconnect

   /************************************************************************/
	/**  IP 冲突
	wParam =    
	lparam = 0*/
	/************************************************************************/
   ev_UiCmsIpConflict,
#define WM_NET_IPCONFLICT  ev_UiCmsIpConflict

   /************************************************************************/
	/**  更新confmenu
	wParam =    
	lparam = 0*/
	/************************************************************************/
   ev_UiCmsIUpdateConfMenu,
#define WM_CMS_UPDATE_CONFMENU  ev_UiCmsIUpdateConfMenu


    /************************************************************************/
	/**  点击了显示视频解码按钮
	wParam =   1 表示是要最大化显示
	lparam = 0*/
	/************************************************************************/
   ev_UiCmsShowVideo,
#define WM_CMS_SHOWVIDEO  ev_UiCmsShowVideo


    /************************************************************************/
	/**  更新mainMenu
	wParam =    
	lparam = 0*/
	/************************************************************************/
    ev_UiCmsIUpdateMainMenu,
#define WM_CMS_UPDATE_CMAINMENU  ev_UiCmsIUpdateMainMenu

    /************************************************************************/
	/**  更新mainMenu
	wParam =    
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsHideVedio,
#define WM_CMS_HIDE_VEDIO  ev_UiCmsHideVedio

	/************************************************************************/
	/**  开始等待更新注册信息
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiCncBeginWaitingRefresh,
#define UI_CNC_BEGINWAITING_REFRESH  ev_UiCncBeginWaitingRefresh

	/************************************************************************/
	/**  结束等待更新注册信息
	wParam = 0 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncEndWaitingRefresh,
#define UI_CNC_ENDWAITING_REFRESH  ev_UiCncEndWaitingRefresh

	/************************************************************************/
	/**  通知导入地址簿时剩余的条目数量
	wParam = u32 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncLoadAddrNumNty,
#define UI_CNC_LOADADDRNUM_NTY  ev_UiCncLoadAddrNumNty

	/************************************************************************/
	/**  等待更新注册信息超时
	wParam = 0 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncWaitingRefreshOverTime,
#define UI_CNC_WAITINGREFRESH_OVERTIME  ev_UiCncWaitingRefreshOverTime


	/************************************************************************/
	/**  隐藏窗口的消息 
	wParam = 0 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncHideWnd,
#define UI_CNC_HIDE_WND  ev_UiCncHideWnd

	/************************************************************************/
	/**  呼叫服务器配置码流格式选择的消息 (callserverlogic2modelogic)
	wParam = TTPCallSerFormat 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncCallSvr2ModeChooseModeNty,
#define UI_CNC_CALLSVR2MODECHOOSE_MODE_NTY  ev_UiCncCallSvr2ModeChooseModeNty

	/************************************************************************/
	/**  呼叫服务器配置码流格式选择的消息 (modelogic2callserverlogic)
	wParam = TTPCallSerFormat 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncModeChoose2CallSvrModeNty,
#define UI_CNC_MODECHOOSE2CALLSVR_MODE_NTY  ev_UiCncModeChoose2CallSvrModeNty

	/************************************************************************/
	/**  呼叫服务器配置码流格式选择的消息 (callserverlogic2showmodelogic)
	wParam = TTPCallSerFormat 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncCallSvr2ShowModeChooseModeNty,
#define UI_CNC_CALLSVR2SHOWMODECHOOSE_MODE_NTY  ev_UiCncCallSvr2ShowModeChooseModeNty

	/************************************************************************/
	/**  呼叫服务器配置码流格式选择的消息 (showmodelogic2callserverlogic)
	wParam = TTPCallSerFormat 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncShowModeChoose2CallSvrModeNty,
#define UI_CNC_SHOWMODECHOOSE2CALLSVR_MODE_NTY  ev_UiCncShowModeChoose2CallSvrModeNty

	/************************************************************************/
	/**  呼叫服务器配置音频格式选择的消息 (callserverlogic2Audiomodelogic)
	wParam = EmTpAudioFormat
	lparam = 0*/
	/************************************************************************/
	ev_UiCncCallSvr2AudioModeNty,
#define UI_CNC_CALLSVR2AUDIO_MODE_NTY  ev_UiCncCallSvr2AudioModeNty

	/************************************************************************/
	/**  呼叫服务器配置音频格式选择的消息 (Audiomodelogic2callserverlogic)
	wParam = EmTpAudioFormat 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncAudioMode2CallSvrNty,
#define UI_CNC_AUDIO2CALLSVR_MODE_NTY  ev_UiCncAudioMode2CallSvrNty
				
    /************************************************************************/
	/**  台标上传进度提醒(升级后第一次登录)
	wParam =  进度值  
	lparam = 0*/
	/************************************************************************/	
	em_CNC_FL_CONFSIGNPROGRESS,
#define WM_CNC_FL_FTPCONFSIGNPROGRESS  em_CNC_FL_CONFSIGNPROGRESS		   
	/************************************************************************/
	/**  台标上传进度提醒
	wParam =  进度值  
	lparam = 0*/
	/************************************************************************/	
	em_CNC_CONFSIGNPROGRESS,
#define WM_CNC_FTPCONFSIGNPROGRESS  em_CNC_CONFSIGNPROGRESS		   
	/************************************************************************/
	/**  横幅上传进度提醒
	wParam =  进度值  
	lparam = 0*/
	/************************************************************************/	
	em_CNC_CONFBANNERPROGRESS,
#define WM_CNC_FTPCONFBANNERPROGRESS  em_CNC_CONFBANNERPROGRESS		 
	
    /************************************************************************/
	/**  开启或关闭画中画操作反馈 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiViewLocalPIPInd,
#define UI_CNS_VIEWLOCALPIP_IND  ev_UiViewLocalPIPInd
	
    /************************************************************************/
	/**  画中画开启或关闭状态通知 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiViewLocalPIPNty,
#define UI_CNS_VIEWLOCALPIP_NTY  ev_UiViewLocalPIPNty

	/************************************************************************/
	/**  快捷菜单设置
	wParam =    菜单项枚举 EM_ShortcutType
	lparam =     是否开启  */
	/************************************************************************/
    ev_UiShortCutNty,
#define UI_CNC_SET_SHORTCUT_NTY  ev_UiShortCutNty

	/************************************************************************/
	/**  快捷菜单点击设置进入具体项目进行界面
	wParam =    菜单项枚举 EM_ShortcutType
	lparam =       */
	/************************************************************************/
    ev_UiShowShortCutDlgNty,
#define UI_CNC_SHOW_SHORTCUTDLG_NTY  ev_UiShowShortCutDlgNty
	/************************************************************************/
	/**  登录时刷新快捷方式按钮状态
	wParam =    菜单项枚举 EM_ShortcutType
	lparam =       */
	/************************************************************************/
    ev_UiShortCutCheckNty,
#define UI_CNC_SHORTCUTCHECK_NTY  ev_UiShortCutCheckNty
	/************************************************************************/
	/**  预置位截图下载通知
	wParam =  进度值  
	lparam = 0*/
	/************************************************************************/	
	em_CNC_PAMCAMRPRESETPROGRESS,
#define WM_CNC_PAMCAMRPRESETPROGRESS  em_CNC_PAMCAMRPRESETPROGRESS	
	/************************************************************************/
	/**  文档摄像机快照下载通知
	wParam =  进度值  
	lparam = 0*/
	/************************************************************************/	
	em_CNC_DOCSNAPSHOTROGRESS,
#define WM_CNC_DOCSNAPSHOTROGRESS  em_CNC_DOCSNAPSHOTROGRESS	
   /************************************************************************/
	/**  calendar日期选择通知
	wParam =     日期
	lparam =     */
	/************************************************************************/
    ev_UiCalendarDateSet,
#define UI_CNC_CALENDARDATE_SET  ev_UiCalendarDateSet
	/************************************************************************/
	/**  会议轮询快捷方式轮询操作通知
	wParam = 
	lparam =     */
	/************************************************************************/
    ev_UiShortCutPoll,
#define UI_CNC_SHORTCUT_POLL  ev_UiShortCutPoll
	/************************************************************************/
	/**  会议点名快捷方式轮询操作通知
	wParam = 
	lparam =     */
	/************************************************************************/
    ev_UiShortCutRoll,
#define UI_CNC_SHORTCUT_ROLL  ev_UiShortCutRoll
	/************************************************************************/
	/** 画面合成快捷方式轮询操作通知
	wParam = 
	lparam =     */
	/************************************************************************/
    ev_UiShortCutVMix,
#define UI_CNC_SHORTCUT_VMIX  ev_UiShortCutVMix
	/************************************************************************/
	/**  会议混音快捷方式操作通知
	wParam = 
	lparam =     */
	/************************************************************************/
    ev_UiShortCutConfMix,
#define UI_CNC_SHORTCUT_CONFMIX  ev_UiShortCutConfMix
	/************************************************************************/
	/**  全场静音快捷方式操作通知
	wParam = 
	lparam =     */
	/************************************************************************/
    ev_UiShortCutQuiteAll,
#define UI_CNC_SHORTCUT_QUITEALL  ev_UiShortCutQuiteAll
	/************************************************************************/
	/**  全场哑音快捷方式操作通知
	wParam = 
	lparam =     */
	/************************************************************************/
    ev_UiShortCutMuteAll,
#define UI_CNC_SHORTCUT_MUTEALL  ev_UiShortCutMuteAll
    /************************************************************************/
	/** 点名状态操作回应
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiConfRollInd,
#define UI_CNS_CONFROLL_IND  ev_UiConfRollInd	
    /************************************************************************/
	/**  点名状态通知
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiConfRollNty,
#define UI_CNS_CONFROLL_NTY  ev_UiConfRollNty
	/************************************************************************/
	/**  被点名人与会状态通知
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiConfRollAattendNty,
#define UI_CNS_CONFROLL_ATTEND_NTY  ev_UiConfRollAattendNty
    /************************************************************************/
	/**  点名下一个回应
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiConfRollNextInd,
#define UI_CNS_CONFROLLNEXT_IND  ev_UiConfRollNextInd
	/************************************************************************/
	/**  添加被点名人回应
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiConfRollListFixedInd,
#define UI_CNS_CONFROLL_LISTFIXED_IND  ev_UiConfRollListFixedInd
	/************************************************************************/
	/** 混音状态通知
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiConMixNty,
#define UI_CNS_CONFMIX_NTY  ev_UiConMixNty	
	/************************************************************************/
	/** 混音请求操作回应
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiConMixInd,
#define UI_CNS_CONFMIX_IND  ev_UiConMixInd	
	/************************************************************************/
	/** 修改混音成员请求操作回应
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiConMixFixInd,
#define UI_CNS_CONFMIX_FIX_IND  ev_UiConMixFixInd	
	/************************************************************************/
	/**  自定义设置下载log通知
	wParam =  进度值  
	lparam = 0*/
	/************************************************************************/	
	em_cnc_LogDownloadProgress,
#define WM_CNC_LOGLOADPROGRESS  em_cnc_LogDownloadProgress	

    /************************************************************************/
	/**  快捷菜单点击设置进入具体项目进行界面
	wParam =    菜单项枚举 EM_ShortcutType
	lparam =       */
	/************************************************************************/
    ev_UiHideTvWallChildDlgNty,
#define UI_CNC_HIDE_TVWALLCHILDDLG_NTY  ev_UiHideTvWallChildDlgNty

	/************************************************************************/
	/**  会议轮询列表更新反馈通知
	wParam = m_wRet 
	lparam = m_nFlag 
	/************************************************************************/
	ev_UiPollListInd,
#define UI_CNSPOLLLIST_IND  ev_UiPollListInd
	/************************************************************************/
	/**  会议轮询列表通知
	wParam =  
	lparam =  
	/************************************************************************/
	ev_UiPollListNty,
#define UI_CNSPOLLLIST_NTY  ev_UiPollListNty
	/************************************************************************/
	/**  会议轮询暂停通知
	wParam = u32_Ip
	lparam = bSuccess 
	/************************************************************************/
	ev_UiPollPauseInd,
#define UI_CNSPOLLPAUSE_IND  ev_UiPollPauseInd

    ev_UIVidMixOpenStatusNty,
#define UI_CNC_VIDMIXSTATUS_NTY  ev_UIVidMixOpenStatusNty

	/************************************************************************/
	/**  画面裁剪通知
	wParam = BOOL TRUE开启，FALSE关闭
	lparam = bSuccess 
	/************************************************************************/
	ev_UiVidCutLineInd,
#define UI_CNC_VIDCUTLINE_IND  ev_UiVidCutLineInd

	/************************************************************************/
	/**  是否在会议混音中通知
	wParam = BOOL TRUE在，FALSE不在
	/************************************************************************/
	ev_UiInAudMixNty,
#define UI_CNC_INAUDMIX_NTY  ev_UiInAudMixNty
	/************************************************************************/
	/**	323会场视频源通知
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICns323VedioSourceListNty,
#define	UI_CNS_323VEDIOSOR_NOTIFY         ev_UICns323VedioSourceListNty
	/************************************************************************/
	/**  量子加密响应
	wParam = 0
	lparam = BOOL TRUE成功，FALSE失败
	/************************************************************************/
	ev_UiQTEncryptInd,
#define UI_CNC_QTENCRYPT_IND  ev_UiQTEncryptInd
	/************************************************************************/
	/**  量子加密通知
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_UiQTEncryptNty,
#define UI_CNC_QTENCRYPT_NTY  ev_UiQTEncryptNty
	/************************************************************************/
	/**  时间同步界面状态显示
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_CnSysTimeToCncNty,
#define UI_CNC_CNSYSTIMETOCNC_NTY  ev_CnSysTimeToCncNty
	/************************************************************************/
	/**  是否桌面麦克风通知
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_CnDesktopMicInfoNty,
#define UI_CNC_CNDESKTOPMICINFO_NTY  ev_CnDesktopMicInfoNty
	/************************************************************************/
	/**  麦克风风格通知
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_CnMicPowerStyleNty,
#define UI_CNC_CNMICPOWERSTYLE_NTY  ev_CnMicPowerStyleNty
	/************************************************************************/
	/**  麦克风状态通知
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_CnMicPowerNty,
#define UI_CNC_CNMICPOWER_NTY  ev_CnMicPowerNty
	/************************************************************************/
	/**  设置麦克风状态返回
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_CnSetMicPowerRsp,
#define UI_CNC_CNSETMICPOWER_RSP  ev_CnSetMicPowerRsp

    /************************************************************************/
	/**  升降屏配置信息通知
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_CentreDFScreenConfigNty,
#define UI_CNC_CENTREDFSCREENCONFIG_NTY  ev_CentreDFScreenConfigNty

    /************************************************************************/
	/**  操作升降屏反馈通知
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_CentreDFScreenCmdInd,
#define UI_CNC_CENTREDFSCREENCMD_IND  ev_CentreDFScreenCmdInd

	/************************************************************************/
	/**  TPad向cnc通知断链
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_TpadCnsDisconnectedNty,
#define UI_TPAD_CNSDISCONNECTED_NTY  ev_TpadCnsDisconnectedNty	

	/************************************************************************/
	/**  断链清空数据
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_DisconnectedClearData,
#define	UI_DISCONNECTED_CLEARDATA  ev_DisconnectedClearData
	/************************************************************************/
	/**  密码周期更新通知
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_CnTpadPWUpdate_Nty,
#define UI_CNTPADPWUPDATE_NTY  ev_CnTpadPWUpdate_Nty
	/************************************************************************/
	/**  密码周期更新响应
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_CnTpadPWUpdate_Ind,
#define UI_CNTPADPWUPDATE_IND  ev_CnTpadPWUpdate_Ind

    /************************************************************************/
	/**  超级管理员通知
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_Superadmin_Nty,
#define UI_SUPERADMIN_NTY  ev_Superadmin_Nty

    /************************************************************************/
	/**  T300升级后第一次登录
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_FirstLoginAfterUpdate_Nty,
#define UI_FIRSTLOGINAFTERUPDATE_NTY  ev_FirstLoginAfterUpdate_Nty

    /************************************************************************/
	/**  询问会议模板密码
	wParam =  0
	lparam =  0
	/************************************************************************/
	ev_GetTempPwd_Cmd,
#define UI_GETTEMPPWD_CMD  ev_GetTempPwd_Cmd

    ev_UICncEnd,
#define	UI_CNC_MSG_END   ev_UICncEnd

};



//cms 逻辑单元间的消息定义
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
	/** 通知Tpad登录信息
	/************************************************************************/
    ev_TPadLoginInfo_Nty,

    /************************************************************************/
	/** cnc修改系统名称 dyy
	/************************************************************************/
    ev_TPadSetSysName_Nty,

    /************************************************************************/
	/** 通知Tpad Home键响应
	/************************************************************************/
    ev_TPadHomeKey_Nty,

	/************************************************************************/
	/** 通知Tpad响应主动跟cns断链
	/************************************************************************/
    ev_TpadDisconnectCns_Nty,
	
    /************************************************************************/
	/** 通知cnc 是否加入白板会议  
	/************************************************************************/
    ev_WBConfStateNty,
    /************************************************************************/
	/** 通知打开中控  dyy 2015-5-26
	/************************************************************************/
    ev_OpenCenterCtrl_Nty,
    /************************************************************************/
	/** 通知打开系统设置  dyy 2016-8-29
	/************************************************************************/
    ev_OpenSysConfig_Nty,
    /************************************************************************/
	/** 通知打开会场管理  2017.3.10
	/************************************************************************/
    ev_OpenCnsManage_Nty,
	/************************************************************************/
	/** TPad通知cnc断链消息  xcr 2017.9.22
	/************************************************************************/
	ev_CnsDisconnect_Nty,

    ev_TPadMsg_End,
};


//cnstool消息定义
enum EmUiCnstoolMsg
{
#define UI_CNSTOOL_MSG_BEGIN  CNSTOOL_MSG_BEGIN + 0x1

    	/************************************************************************/
		/** 出现异常
		wParam = 异常错误码
		lparam = 0*/
		/************************************************************************/
	ev_UiCNSTOOLError = UI_CNSTOOL_MSG_BEGIN,
#define UI_CNSTOOL_ERROR  ev_UiCNSTOOLError

	/************************************************************************/
	/**  请求TPadIP列表回复消息
	wParam =  &TTPTPadList
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolTPadIPRsp,
#define UI_CNSTOOL_MSG_TPadIP_RSP  ev_UiCnstoolTPadIPRsp

	/************************************************************************/
	/**  接收TPadIP列表通知消息
	wParam =  &TTPTPadList
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolTPadIPNty,
#define UI_CNSTOOL_MSG_TPadIP_NTY  ev_UiCnstoolTPadIPNty

	/************************************************************************/
	/**  接收cpu/内存通知消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolSYSInfoNty,
#define UI_CNSTOOL_MSG_CPURAM_NTY  ev_UiCnstoolSYSInfoNty

	/************************************************************************/
	/**  接收会议信息通知消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolConfInfoNty,
#define UI_CNSTOOL_MSG_CONF_NTY  ev_UiCnstoolConfInfoNty

	/************************************************************************/
	/**  接收音频端口设置通知消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolAudPortInd,
#define UI_CNSTOOL_MSG_AudPort_NTY  ev_UiCnstoolAudPortInd
	
	/************************************************************************/
	/**  接收默认音频端口消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDftAudPortInd,
#define UI_CNSTOOL_MSG_DftAudPort_NTY  ev_UiCnstoolDftAudPortInd
	
	/************************************************************************/
	/**  接收上下行速率通知消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolUpDownstreamInd,
#define UI_CNSTOOL_MSG_UpDownstream_NTY  ev_UiCnstoolUpDownstreamInd

	/************************************************************************/
	/**  接收丢包消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolLostPacketRsp,
#define UI_CNSTOOL_MSG_LostPacket_Rsp  ev_UiCnstoolLostPacketRsp

	/************************************************************************/
	/**  接收诊断测试消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolAVDiagInd,
#define UI_CNSTOOL_MSG_AVDiag_IND  ev_UiCnstoolAVDiagInd

	/************************************************************************/
	/**  添加网管指示
	wParam = EmModifyNMServerRet 是否成功
	lparam = 无*/
	/************************************************************************/
	ev_UICnstoolAddNetmngInd,
#define UI_CNSTOOL_ADD_NETMNG_IND  ev_UICnstoolAddNetmngInd

	/************************************************************************/
	/**  删除网管指示
	wParam = EmModifyNMServerRet 是否成功
	lparam = 无*/
	/************************************************************************/
	ev_UICnstoolDelNetmngInd,
#define UI_CNSTOOL_DEL_NETMNG_IND  ev_UICnstoolDelNetmngInd

	/************************************************************************/
	/**  网管信息通知
	wParam = TTPNMServerCfg* 网管信息
	lparam = 无*/
	/************************************************************************/
	ev_UICnstoolNetmngNty,
#define UI_CNSTOOL_NETMNG_NTY  ev_UICnstoolNetmngNty

	/************************************************************************/
	/**  修改网管指示
	wParam = EmModifyNMServerRet 是否成功
	lparam = 无*/
	/************************************************************************/
	ev_UICnstoolModifyNetmngInd,
#define UI_CNSTOOL_MODIFY_NETMNG_IND  ev_UICnstoolModifyNetmngInd

	/************************************************************************/
	/**  单板页面添加修改网管当前选中数据发送
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiCnstoolNetMngSelDataClick,
#define UI_CNSTOOL_MSG_NETMNGSELDATA_Click  ev_UiCnstoolNetMngSelDataClick
	
	/************************************************************************/
	/**  接收呼叫服务器的通知信息
	wParam = 0   
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolCallSerNty,
#define UI_CNSTOOL_MSG_CallSer_NTY  ev_UiCnstoolCallSerNty
		
	/************************************************************************/
	/**  接收呼叫服务器的回复信息
	wParam = TTPCallSerInfo  
	lparam = bSuccess 
	/************************************************************************/
	ev_UiCnstoolCallSerInd,
#define UI_CNSTOOL_MSG_CallSer_IND  ev_UiCnstoolCallSerInd
	
	/************************************************************************/
	/**  接收升级服务器的通知信息
	wParam = 0   
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolUpgradeSerNty,
#define UI_CNSTOOL_MSG_UpgradeSer_NTY  ev_UiCnstoolUpgradeSerNty
		
	/************************************************************************/
	/**  接收升级服务器的回复信息
	wParam = u32_Ip
	lparam = bSuccess 
	/************************************************************************/
	ev_UiCnstoolUpgradeSerInd,
#define UI_CNSTOOL_MSG_UpgradeSer_IND  ev_UiCnstoolUpgradeSerInd
		
	/************************************************************************/
	/**  接收中控信息中空调的信息
	wParam = 0  
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolAirInfoNty,
#define UI_CNSTOOL_MSG_AirInfo_NTY  ev_UiCnstoolAirInfoNty
	
	/************************************************************************/
	/**  接收中控信息中新风的信息
	wParam = 0 
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolXinFengInfoNty,
#define UI_CNSTOOL_MSG_XinFengInfo_NTY  ev_UiCnstoolXinFengInfoNty
	
	/************************************************************************/
	/**  接收中控信息中显示器的信息
	wParam = 0 
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolDisplayInfoNty,
#define UI_CNSTOOL_MSG_DisplayInfo_NTY  ev_UiCnstoolDisplayInfoNty
	
	/************************************************************************/
	/**  接收中控信息中摄像机的信息
	wParam = 0 
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolCameraInfoNty,
#define UI_CNSTOOL_MSG_CameraInfo_NTY  ev_UiCnstoolCameraInfoNty
	
	/************************************************************************/
	/**  接收中控信息中文档摄像机的信息
	wParam = 0 
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolDocCamInfoNty,
#define UI_CNSTOOL_MSG_DocCamInfo_NTY  ev_UiCnstoolDocCamInfoNty
	
	/************************************************************************/
	/**  接收中控信息中灯光的信息
	wParam = 0 
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolLightInfoNty,
#define UI_CNSTOOL_MSG_LightInfo_NTY  ev_UiCnstoolLightInfoNty

	/************************************************************************/
	/**  摄像机配置通知
	wParam = NULL
	lparam = NULL
	/************************************************************************/
	ev_UICnstoolCameraCfgNty,
#define UI_CNSTOOL_CAMERA_CFG_NTY  ev_UICnstoolCameraCfgNty

	/************************************************************************/
	/**  选择控制摄像机返回命令
	wParam = NULL
	lparam = BOOL  = TRUE 选择成功 =FALSE 选择失败
	/************************************************************************/
	ev_UICnstoolCameraSelectInd,
#define UI_CNSTOOL_CAMERA_SELECT_IND  ev_UICnstoolCameraSelectInd

	/************************************************************************/
	/**  恢复摄像机出厂配置返回消息
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功  FALSE 设置失败
	/************************************************************************/
	ev_UICnstoolCameraResetInd,
#define UI_CNSTOOL_CAMERA_RESET_IND  ev_UICnstoolCameraResetInd

	/************************************************************************/
	/**  摄像视野调节返回命令
	wParam = NULL
	lparam = BOOL:				TRUE 设置成功  =FALSE 设置失败
	/************************************************************************/
	ev_UICnstoolCameraZoomInd,
#define UI_CNSTOOL_CAMERA_ZOOM_IND  ev_UICnstoolCameraZoomInd

	/************************************************************************/
	/**  摄像机 视野在OSD上显示比例返回命令
	wParam = NULL
	lparam = BOOL          =TRUE 设置成功  =FALSE 设置失败
	/************************************************************************/
	ev_UICnstoolCameraOSDShowInd,
#define UI_CNSTOOL_CAMERA_OSDSHOW_IND  ev_UICnstoolCameraOSDShowInd

	/************************************************************************/
	/**  摄像头自动聚焦返回命令
	wParam = BOOL   =TRUE 设置成功   =FALSE 设置失败
	lparam = NULL
	/************************************************************************/
	ev_UICnstoolCameraAutoFocusInd,
#define UI_CNSTOOL_CAMERA_AUTO_FOCUS_IND  ev_UICnstoolCameraAutoFocusInd

	/************************************************************************/
	/**  摄像头聚焦返回命令
	wParam = EmFocus         emFar 远焦  emNear近焦
	lparam = BOOL        =TRUE 设置成功  =FALSE 设置失败
	/************************************************************************/
	ev_UICnstoolCameraFocusInd,
#define UI_CNSTOOL_CAMERA_FOCUS_IND  ev_UICnstoolCameraFocusInd

	/************************************************************************/
	/**  摄像机自动曝光返回命令
	wParam = NULL
	lparam = BOOL       =TRUE 设置成功  =FALSE 设置失败 
	/************************************************************************/
	ev_UICnstoolCameraAutoExposureInd,
#define UI_CNSTOOL_CAMERA_AUTO_EXPOSURE_IND  ev_UICnstoolCameraAutoExposureInd

	/************************************************************************/
	/**  摄像机手动曝光——增益调节返回命令
	wParam = NULL
	lparam = BOOL    =　TRUE 设置成功   =FALSE 设置失败
	/************************************************************************/
	ev_UICnstoolCameraGainInd,
#define UI_CNSTOOL_CAMERA_GAIN_IND  ev_UICnstoolCameraGainInd

	/************************************************************************/
	/**  摄像机手动曝光——快门调节返回命令
	wParam = NULL
	lparam = BOOL    =　TRUE 设置成功   =FALSE 设置失败
	/************************************************************************/
	ev_UICnstoolCameraShutSpdInd,
#define UI_CNSTOOL_CAMERA_SHUT_SPD_IND  ev_UICnstoolCameraShutSpdInd

	/************************************************************************/
	/**  摄像机手动曝光——背光调节返回命令
	wParam = NULL
	lparam = BOOL    =　TRUE 设置成功   =FALSE 设置失败
	/************************************************************************/
	ev_UICnstoolCameraBackLightInd,
#define UI_CNSTOOL_CAMERA_BACK_LIGHT_IND  ev_UICnstoolCameraBackLightInd

	/************************************************************************/
	/**  摄像机手动曝光——光圈调节返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功   =FALSE 设置失败
	/************************************************************************/
	ev_UICnstoolCameraApertureInd,
#define UI_CNSTOOL_CAMERA_APERTURE_IND  ev_UICnstoolCameraApertureInd

	/************************************************************************/
	/**  摄像机自动白平衡返回命令
	wParam = BOOL   =TRUE 设置成功   =FALSE 设置失败
	lparam = NULL
	/************************************************************************/
	ev_UICnstoolCameraAutoWBInd,
#define UI_CNSTOOL_CAMERA_AUTO_WB_IND  ev_UICnstoolCameraAutoWBInd

	/************************************************************************/
	/**  摄像机手动白平衡--R Gain返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCameraRGainInd,
#define UI_CNSTOOL_CAMERA_RGAIN_IND  ev_UICnstoolCameraRGainInd

	/************************************************************************/
	/**  摄像机手动白平衡--B Gain返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCameraBGainInd,
#define UI_CNSTOOL_CAMERA_BGAIN_IND  ev_UICnstoolCameraBGainInd

	/************************************************************************/
	/**  摄像机场景模式返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCameraPicSceneModeInd,
#define UI_CNSTOOL_CAMERA_PIC_SCENE_MODE_IND  ev_UICnstoolCameraPicSceneModeInd

	/************************************************************************/
	/**  摄像机 模式--- 手动 GAMMA调节返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCameraGammaInd,
#define UI_CNSTOOL_CAMERA_GAMMA_IND  ev_UICnstoolCameraGammaInd

	/************************************************************************/
	/**  摄像机 模式--- 光圈调节返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCameraPicSceAptInd,
#define UI_CNSTOOL_CAMERA_PIC_SCE_APT_IND  ev_UICnstoolCameraPicSceAptInd

	/************************************************************************/
	/**  摄像机 图片调节---对比度 调节返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCameraContrastInd,
#define UI_CNSTOOL_CAMERA_CONTRAST_IND  ev_UICnstoolCameraContrastInd

	/************************************************************************/
	/**  摄像机 图片调节---饱和度 调节返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCameraSaturatInd,
#define UI_CNSTOOL_CAMERA_SATURAT_IND  ev_UICnstoolCameraSaturatInd

	/************************************************************************/
	/**  摄像机 图片调节--- 色度 调节返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCameraHueInd,
#define UI_CNSTOOL_CAMERA_HUE_IND  ev_UICnstoolCameraHueInd

	/************************************************************************/
	/**  摄像机 图片调节--- 亮度 调节返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCameraBrightInd,
#define UI_CNSTOOL_CAMERA_BRIGHT_IND  ev_UICnstoolCameraBrightInd

	/************************************************************************/
	/**  摄像机 降噪---噪点过滤 调节返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCameraNRStmCleanInd,
#define UI_CNSTOOL_CAMERA_NR_STM_CLEAN_IND  ev_UICnstoolCameraNRStmCleanInd

	/************************************************************************/
	/**  摄像机 降噪---3D降噪 调节返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCamera3DNRInd,
#define UI_CNSTOOL_CAMERA_3DNR_IND  ev_UICnstoolCamera3DNRInd

	/************************************************************************/
	/**  摄像机 预置位保存返回命令
	wParam = NULL	
	lparam = BOOL	TRUE= 保存预置位成功   = FALSE 保存失败
	/************************************************************************/
	ev_UICnstoolCameraPersetSaveInd,
#define UI_CNSTOOL_CAMERA_PERSET_SAVE_IND  ev_UICnstoolCameraPersetSaveInd

	/************************************************************************/
	/**  摄像机 设置开机调用预置位
	wParam = NULL	
	lparam = BOOL	TRUE= 设置成功   = FALSE 设置失败
	/************************************************************************/
	ev_UICnstoolCameraPersetMoveInd,
#define UI_CNSTOOL_CAMERA_PERSET_MOVE_IND  ev_UICnstoolCameraPersetMoveInd

	/************************************************************************/
	/**  摄像机 设置ZOOM
	wParam = NULL	
	lparam = BOOL	TRUE= 设置成功   = FALSE 设置失败
	/************************************************************************/
	ev_UICnstoolSetCameraZoomInd,
#define UI_CNSTOOL_SET_CAMERA_ZOOM_IND  ev_UICnstoolSetCameraZoomInd
			
	/************************************************************************/
	/**  接收音频混音数设置通知消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolAudMixerInd,
#define UI_CNSTOOL_MSG_AudMixer_NTY  ev_UiCnstoolAudMixerInd
				
	/************************************************************************/
	/**  接收系统默认音频混音数消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDefaultMixerInd,
#define UI_CNSTOOL_MSG_DftMixer_NTY  ev_UiCnstoolDefaultMixerInd
	
	/************************************************************************/
	/**  接收音频均衡器设置通知消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolAudEqualizerInd,
#define UI_CNSTOOL_MSG_AudEqualizer_NTY  ev_UiCnstoolAudEqualizerInd
				
	/************************************************************************/
	/**  接收系统默认音频均衡器消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDefaultEqInd,
#define UI_CNSTOOL_MSG_DftEq_NTY  ev_UiCnstoolDefaultEqInd
			
	/************************************************************************/
	/**  接收升级T300回复消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolUpgradeCnsInd,
#define UI_CNSTOOL_MSG_UpgradeCns_NTY  ev_UiCnstoolUpgradeCnsInd
			
	/************************************************************************/
	/**  接收停止测试回复消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolStopAVMatrixRsp,
#define UI_CNSTOOL_MSG_StopAVMatrix_RSP  ev_UiCnstoolStopAVMatrixRsp
				
	/************************************************************************/
	/**  中控摄像机状态通知信息
	wParam =  aemCam   存放摄像机数组头指针
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolCamPowerStateNty,
#define UI_CNSTOOL_MSG_CamPowerState_NTY  ev_UiCnstoolCamPowerStateNty
				
	/************************************************************************/
	/**  根据收到的GK注册消息改变基本信息界面的状态
	wParam =  0   
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolGKRspNty,
#define UI_CNSTOOL_MSG_GKRsp_NTY  ev_UiCnstoolGKRspNty
				
	/************************************************************************/
	/**  根据收到的sip注册消息改变基本信息界面的状态
	wParam =  0   
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolSIPRspNty,
#define UI_CNSTOOL_MSG_SIPRsp_NTY  ev_UiCnstoolSIPRspNty
				
	/************************************************************************/
	/**  日志下载进度提醒 
	wParam =  进度值  
	lparam = 0*/
	/************************************************************************/
	em_CNSTOOL_FTPLOGPROGRESS,
#define WM_CNSTOOL_FTPLOGPROGRESS  em_CNSTOOL_FTPLOGPROGRESS				   
				
	/************************************************************************/
	/**  地址簿导入导出进度提醒
	wParam =  进度值  
	lparam = 0*/
	/************************************************************************/	
	em_CNSTOOL_FTPADDRBOOKPROGRESS,
#define WM_CNSTOOL_FTPADDRBOOKPROGRESS  em_CNSTOOL_FTPADDRBOOKPROGRESS      
				
	/************************************************************************/
	/**  台标上传进度提醒
	wParam =  进度值  
	lparam = 0*/
	/************************************************************************/	
	em_CNSTOOL_CONFSIGNPROGRESS,
#define WM_CNSTOOL_FTPCONFSIGNPROGRESS  em_CNSTOOL_CONFSIGNPROGRESS		   
				
	/************************************************************************/
	/**  文件上传进度提醒 
	wParam =  进度值  
	lparam = 0*/
	/************************************************************************/
	em_CNSTOOL_UPLODEPROGRESS,
#define WM_CNSTOOL_UPLODEPROGRESS  em_CNSTOOL_UPLODEPROGRESS				   

	/************************************************************************/
	/**  收到摄像机上电消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolCameraPowerOnNty,
#define UI_CNSTOOL_CAMERA_POWER_ON_NTY  ev_UICnstoolCameraPowerOnNty
	
	/************************************************************************/
	/**  收到会议优选格式消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolVideoFormatInd,
#define UI_CNSTOOL_VIDEOFORMAT_IND  ev_UICnstoolVideoFormatInd
		
	/************************************************************************/
	/**  收到演示优选格式消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolDualVideoFormatInd,
#define UI_CNSTOOL_DUALVIDEOFORMAT_IND  ev_UICnstoolDualVideoFormatInd
			
	/************************************************************************/
	/**  收到单屏码率消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolCallRateInd,
#define UI_CNSTOOL_CALLRATE_IND  ev_UICnstoolCallRateInd
				
	/************************************************************************/
	/**  收到演示码率消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolDualCallRateInd,
#define UI_CNSTOOL_DUALCALLRATE_IND  ev_UICnstoolDualCallRateInd
					
	/************************************************************************/
	/**  收到版本通知消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolVerInfoNty,
#define UI_CNSTOOL_VERINFO_NTY  ev_UICnstoolVerInfoNty
				
	/************************************************************************/
	/**  收到会议讨论消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolConfDisInd,
#define UI_CNSTOOL_CONFDIS_IND  ev_UICnstoolConfDisInd
				
	/************************************************************************/
	/**  收到会议轮询消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolConfPollInd,
#define UI_CNSTOOL_CONFPOOL_IND  ev_UICnstoolConfPollInd
				
	/************************************************************************/
	/**  收到音频格式消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolAudioFormatInd,
#define UI_CNSTOOL_AUDIOFORMAT_IND  ev_UICnstoolAudioFormatInd
				
	/************************************************************************/
	/**  中控电视墙通知信息
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolCfgDisplayInd,
#define UI_CNSTOOL_MSG_DISPLAY_IND  ev_UiCnstoolCfgDisplayInd

	/************************************************************************/
	/**  收到窗帘名称数组消息
	wParam = 窗帘名称数组  
	lparam = 0*/
	/************************************************************************/
	ev_UITpadCurtainStateNty,
#define UI_TPAD_CURTAINSTATE_NTY  ev_UITpadCurtainStateNty
	/************************************************************************/
	/**  收到显示台标消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnIsShowLogoInd,
#define UI_CNC_ISSHOWLOGO_IND  ev_UICnIsShowLogoInd
	/************************************************************************/
	/**  收到显示台标消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnIsShowLogoNty,
#define UI_CNC_ISSHOWLOGO_NTY  ev_UICnIsShowLogoNty
	/************************************************************************/
	/**  收到显示横幅消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnIsShowBannerInd,
#define UI_CNC_ISSHOWBANNER_IND  ev_UICnIsShowBannerInd
	/************************************************************************/
	/**  收到显示横幅消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnIsShowBannerNty,
#define UI_CNC_ISSHOWBANNER_NTY  ev_UICnIsShowBannerNty
	/************************************************************************/
	/**  加密配置设置通知
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UISetEncryptInfo_Nty,
#define UI_ENCRYPTINFO_NTY  ev_UISetEncryptInfo_Nty
	/************************************************************************/
	/**  加密配置设置回应
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UISetEncryptInfo_Ind,
#define UI_ENCRYPTINFO_IND  ev_UISetEncryptInfo_Ind

	/************************************************************************/
	/**  数据会议服务器的通知信息
	wParam = u32_Ip
	lparam = bSuccess 
	/************************************************************************/
	ev_UiCnstoolDBSerNty,
#define UI_CNSTOOL_MSG_BD_NTY  ev_UiCnstoolDBSerNty
	/************************************************************************/
	/**  数据会议服务器的回复信息
	wParam = u32_Ip
	lparam = bSuccess 
	/************************************************************************/
	ev_UiCnstoolDBSerInd,
#define UI_CNSTOOL_MSG_BD_IND  ev_UiCnstoolDBSerInd
    /************************************************************************/
	/**  Ftp信息设置反馈
	wParam = u32_Ip
	lparam = bSuccess 
	/************************************************************************/
	ev_CnSetFtpRsp,
#define UI_CNSETFTPRSP  ev_CnSetFtpRsp
    /************************************************************************/
	/**  显示器显示提示
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_CnDisplayShow_Ind,
#define UI_CNDISPLAYSHOW  ev_CnDisplayShow_Ind
    /************************************************************************/
	/**  矩阵界面显示通知
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_MatrixConfigNty,
#define UI_MATRIXCONFIG_NTY  ev_MatrixConfigNty
    /************************************************************************/
	/**  矩阵场景通知
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_MatrixSceneNty,
#define UI_MATRIXSCENE_NTY  ev_MatrixSceneNty
    /************************************************************************/
	/**  矩阵场景添加反馈
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_SaveMatrixSceneInd,
#define UI_SAVEMATRIXSCENE_IND  ev_SaveMatrixSceneInd
    /************************************************************************/
	/**  当前矩阵场景通知
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_CurMatrixSceneNty,
#define UI_CURMATRIXSCENE_NTY  ev_CurMatrixSceneNty
	/************************************************************************/
	/**  修改矩阵场景名称反馈
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_ReNameMatrixSceneInd,
#define UI_RENAMEMATRIXSCENE_IND  ev_ReNameMatrixSceneInd
    /************************************************************************/
	/**  删除矩阵场景反馈
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_DeleteMatrixSceneInd,
#define UI_DELETEMATRIXSCENE_IND  ev_DeleteMatrixSceneInd
    /************************************************************************/
	/**  删除矩阵场景反馈
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_ApplyMatrixSceneInd,
#define UI_APPLYMATRIXSCENE_IND  ev_ApplyMatrixSceneInd

    /************************************************************************/
	/**  串口切换通知
	wParam = bShow
	lparam = bSuccess 
	/************************************************************************/
	ev_SelectComInd,
#define UI_SELECTCOMG_IND  ev_SelectComInd
};

//* @}*/
#endif 
