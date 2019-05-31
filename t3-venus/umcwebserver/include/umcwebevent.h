/*****************************************************************************
模块名      : umcwebevent.h
文件名      : umcwebevent.h
相关文件    : 
文件实现功能: umcwebservice 内部event定义文件
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2014/08/11     1.0         石城        创建
******************************************************************************/
#ifndef _UMCWEBEVENT_H
#define _UMCWEBEVENT_H


enum EmEventUmcweb
{
#define EVENT_UMCWEB_BEGIN					OSP_USEREVENT_BASE + 2500

	/************************************************************************
	* 功能：登陆请求
	* json：{"event":"ev_umcweb_login_req","usr":"admin","psw":"admin"}
	************************************************************************/
	ev_umcweb_login_req = EVENT_UMCWEB_BEGIN,

	/************************************************************************
	* 功能：登陆回复
	* json：//{"event":"ev_umcweb_login_res","EmDcwebLoginUmsRet":"0"}
	************************************************************************/
	ev_umcweb_login_res,

	/************************************************************************
	* 功能：全局地址簿刷新请求
	* json：{"event":"ev_umcweb_addrbook_globle_refresh_req"}
	************************************************************************/
	ev_umcweb_addrbook_globle_refresh_req,

	/************************************************************************
	* 功能：全局地址簿刷新回复
	* json：{"event":"ev_umcweb_addrbook_globle_refresh_res","bRet":"1"}
	************************************************************************/
	ev_umcweb_addrbook_globle_refresh_res,

	/************************************************************************
	* 功能：全局地址簿获取请求
	* json：{"event":"ev_umcweb_addrbook_globle_get_req",search":"会场01"}
	************************************************************************/
	ev_umcweb_addrbook_globle_get_req,

	/************************************************************************
	* 功能：全局地址簿获取回复
	* json：{"event":"ev_umcweb_addrbook_globle_get_res","items":[
				{"id":"1","type":"1","name":"网呈120","number":"120","ip":"172.16.216.120"}
				,{"id":"2","type":"2","name":"网呈121","number":"121","ip":"172.16.216.121"}
			]}
	************************************************************************/
	ev_umcweb_addrbook_globle_get_res,

	/************************************************************************
	* 功能：本地地址簿条目添加请求
	* json：{"event":"ev_umcweb_addrbook_item_add_req","name":"shicheng","number":"1","ip":"172.16.216.120"}
	************************************************************************/
	ev_umcweb_addrbook_item_add_req,

	/************************************************************************
	* 功能：本地地址簿条目添加回复
	* json：{"event":"ev_umcweb_addrbook_item_add_res","bRet":"1"}
	************************************************************************/
	ev_umcweb_addrbook_item_add_res,

	/************************************************************************
	* 功能：本地地址簿条目修改请求
	* json：{"event":"ev_umcweb_addrbook_item_mod_req","id":"1","name":"xiaochuran","number":"3"，"ip":"172.16.216.121"}
	************************************************************************/
	ev_umcweb_addrbook_item_mod_req,

	/************************************************************************
	* 功能：本地地址簿条目修改回复
	* json：{"event":"ev_umcweb_addrbook_item_mod_res","bRet":"1"}
	************************************************************************/
	ev_umcweb_addrbook_item_mod_res,

	/************************************************************************
	* 功能：本地地址簿条目删除请求
	* json：{"event":"ev_umcweb_addrbook_item_del_req","id":"1"}
	************************************************************************/
	ev_umcweb_addrbook_item_del_req,

	/************************************************************************
	* 功能：本地地址簿条目删除回复
	* json：{"event":"ev_umcweb_addrbook_item_del_res","bRet":"1"}
	************************************************************************/
	ev_umcweb_addrbook_item_del_res,

	/************************************************************************
	* 功能：本地地址簿条目和组获取请求
	* json：{"event":"ev_umcweb_addrbook_itemgroup_get_req","gid":"1"}
	************************************************************************/
	ev_umcweb_addrbook_itemgroup_get_req,

	/************************************************************************
	* 功能：本地地址簿条目和组获取回复
	* json：{"event":"ev_umcweb_addrbook_itemgroup_get_res","items":[
				{"id":"1","name":"shicheng","number":"1","ip":"172.16.216.120"}
				,{"id":"2","name":"xuhuaxiu","number":"2","ip":"172.16.216.121"}
				],"count":"2","groupitems":[
				{"id":"2","name":"gshicheng"},{"id":"3","name":"gxuhuaxiu"}
			],"groupcount":"2"}
	************************************************************************/
	ev_umcweb_addrbook_itemgroup_get_res,

	/************************************************************************
	* 功能：本地地址簿条目和组搜索请求
	* json：{"event":"ev_umcweb_addrbook_item_get_req","gid":"1","search":"22"}
	************************************************************************/
	ev_umcweb_addrbook_itemgroup_search_req,
	
	/************************************************************************
	* 功能：本地地址簿条目和组搜索回复
	* json：{"event":"ev_umcweb_addrbook_itemgroup_get_res","items":[
				{"id":"1","name":"shicheng","number":"1","ip":"172.16.216.120"}
				,{"id":"2","name":"xuhuaxiu","number":"2","ip":"172.16.216.121"}
				],"count":"2","groupitems":[
				{"id":"2","name":"gshicheng"},{"id":"3","name":"gxuhuaxiu"}
			],"groupcount":"2"}
	************************************************************************/
	ev_umcweb_addrbook_itemgroup_search_res,

	/************************************************************************
	* 功能：本地地址簿条目获取请求
	* json：{"event":"ev_umcweb_addrbook_item_get_req","gid":"1","posBegin":"1","posEnd":"10"}
	************************************************************************/
	ev_umcweb_addrbook_item_get_req,

	/************************************************************************
	* 功能：本地地址簿条目获取回复
	* json：{"event":"ev_umcweb_addrbook_item_get_res","items":[
				{"id":"1","name":"shicheng","number":"1","ip":"172.16.216.120"}
				,{"id":"2","name":"xuhuaxiu","number":"2","ip":"172.16.216.121"}
			]}
	************************************************************************/
	ev_umcweb_addrbook_item_get_res,

	/************************************************************************
	* 功能：本地地址簿条目数量请求
	* json：{"event":"ev_umcweb_addrbook_item_number_req","gid":"1"}
	************************************************************************/
	ev_umcweb_addrbook_item_number_req,

	/************************************************************************
	* 功能：本地地址簿组获取请求
	* json：{"event":"ev_umcweb_addrbook_group_get_req","pid":"1"}
	************************************************************************/
	ev_umcweb_addrbook_group_get_req,

	/************************************************************************
	* 功能：本地地址簿组获取回复
	* json：{"event":"ev_umcweb_addrbook_group_get_res","items":[
				{"id":"2","name":"gshicheng"}
				,{"id":"3","name":"gxuhuaxiu"}
			]}
	************************************************************************/
	ev_umcweb_addrbook_group_get_res,

	/************************************************************************
	* 功能：本地地址簿条目数量回复
	* json：{"event":"ev_umcweb_addrbook_item_number_res","number":"8"}
	************************************************************************/
	ev_umcweb_addrbook_item_number_res,

	/************************************************************************
	* 功能：本地地址簿组添加请求
	* json：{"event":"ev_umcweb_addrbook_group_add_req","name":"gshicheng"}
	************************************************************************/
	ev_umcweb_addrbook_group_add_req,

	/************************************************************************
	* 功能：本地地址簿组添加回复
	* json：{"event":"ev_umcweb_addrbook_group_add_res","bRet":"1"}
	************************************************************************/
	ev_umcweb_addrbook_group_add_res,

	/************************************************************************
	* 功能：本地地址簿组修改请求
	* json：{"event":"ev_umcweb_addrbook_group_mod_req","id":"2","name":"gtiancai"}
	************************************************************************/
	ev_umcweb_addrbook_group_mod_req,

	/************************************************************************
	* 功能：本地地址簿组修改回复
	* json：{"event":"ev_umcweb_addrbook_group_mod_res","bRet":"1"}
	************************************************************************/
	ev_umcweb_addrbook_group_mod_res,

	/************************************************************************
	* 功能：本地地址簿组删除请求
	* json：{"event":"ev_umcweb_addrbook_group_del_req","id":"2"}
	************************************************************************/
	ev_umcweb_addrbook_group_del_req,

	/************************************************************************
	* 功能：本地地址簿组删除回复
	* json：{"event":"ev_umcweb_addrbook_group_del_res","bRet":"1"}
	************************************************************************/
	ev_umcweb_addrbook_group_del_res,

	/************************************************************************
	* 功能：本地地址簿条目-组关系添加请求
	* json：{"event":"ev_umcweb_addrbook_ig_add_req","iid":"1","gid":"2"}
	************************************************************************/
	ev_umcweb_addrbook_ig_add_req,

	/************************************************************************
	* 功能：本地地址簿条目-组关系添加回复
	* json：{"event":"ev_umcweb_addrbook_ig_add_res","bRet":"1"}
	************************************************************************/
	ev_umcweb_addrbook_ig_add_res,

	/************************************************************************
	* 功能：本地地址簿条目-组关系删除请求
	* json：{"event":"ev_umcweb_addrbook_ig_del_req","iid":"1","gid":"2"}
	************************************************************************/
	ev_umcweb_addrbook_ig_del_req,

	/************************************************************************
	* 功能：本地地址簿条目-组关系删除回复
	* json：{"event":"ev_umcweb_addrbook_ig_del_res","bRet":"1"}
	************************************************************************/
	ev_umcweb_addrbook_ig_del_res,

	/************************************************************************
	* 功能：本地地址簿组-组关系添加请求
	* json：{"event":"ev_umcweb_addrbook_gg_add_req","id":"2","pid":"1"}
	************************************************************************/
	ev_umcweb_addrbook_gg_add_req,

	/************************************************************************
	* 功能：本地地址簿组-组关系添加回复
	* json：{"event":"ev_umcweb_addrbook_gg_add_res","bRet":"1"}
	************************************************************************/
	ev_umcweb_addrbook_gg_add_res,

	/************************************************************************
	* 功能：本地地址簿组-组关系删除请求
	* json：{"event":"ev_umcweb_addrbook_gg_del_req","id":"2","pid":"1"}
	************************************************************************/
	ev_umcweb_addrbook_gg_del_req,

	/************************************************************************
	* 功能：本地地址簿组-组关系删除回复
	* json：{"event":"ev_umcweb_addrbook_gg_del_res","bRet":"1"}
	************************************************************************/
	ev_umcweb_addrbook_gg_del_res,

	/************************************************************************
	* 功能：获取会议列表请求
	* json：{"event":"ev_umcweb_confmng_listconf_get_req"}
	************************************************************************/
	ev_umcweb_confmng_listconf_get_req,

	/************************************************************************
	* 功能：获取会议列表回应
	* json：{"event":"ev_umcweb_confmng_listconf_get_res"
				,"items":[{"confId":"1","confName":"石城会议","startTime":"18:18","persistenceTime":"3600","chairroomName":"主席会场","roomNumber":"5"}]
				,"count":"1"
			}
	************************************************************************/
	ev_umcweb_confmng_listconf_get_res,

	/************************************************************************
	* 功能：获取预约会议列表请求
	* json：{"event":"ev_umcweb_confmng_listconfbook_get_req"}
	************************************************************************/
	ev_umcweb_confmng_listconfbook_get_req,

	/************************************************************************
	* 功能：获取预约会议列表回应
	* json：{"event":"ev_umcweb_confmng_listconfbook_get_res"
				,"items":[{"confId":"1","confName":"石城会议","startTime":"18:18","endTime":"18:18","interval":"3600","chairroomName":"主席会场","roomNumber":"5"}]
				,"count":"1"
			}
	************************************************************************/
	ev_umcweb_confmng_listconfbook_get_res,

	/************************************************************************
	* 功能：挂断会议请求
	* json：{"event":"ev_umcweb_hangupconf_req","confid":"1"}
	************************************************************************/
	ev_umcweb_hangupconf_req,

	/************************************************************************
	* 功能：挂断会议请求
	* json：{"event":"ev_umcweb_hangupconf_req","confid":"1"}
	************************************************************************/
	ev_umcweb_hangupconf_res,

	/************************************************************************
	* 功能：添加用户请求
	* json：{"event":"ev_umcweb_AddUser_req","name":"23","pwd":"23"}
	************************************************************************/
	ev_umcweb_AddUser_req,

	/************************************************************************
	* 功能：添加用户回应
	* json：{"event":"ev_umcweb_AddUser_res","emRet":"1"}
	************************************************************************/
	ev_umcweb_AddUser_res,

	/************************************************************************
	* 功能：修改密码请求
	* json：{"event":"ev_umcweb_ChangePwd_req","name":"23","pwd":"23"}
	************************************************************************/
	ev_umcweb_ChangePwd_req,

	/************************************************************************
	* 功能：修改密码回应
	* json：{"event":"ev_umcweb_ChangePwd_res","emRet":"1"}
	************************************************************************/
	ev_umcweb_ChangePwd_res,

	/************************************************************************
	* 功能：删除用户请求
	* json：{"event":"ev_umcweb_DelUser_req","name":"23","pwd":"23"}
	************************************************************************/
	ev_umcweb_DelUser_req,

	/************************************************************************
	* 功能：删除用户回应
	* json：{"event":"ev_umcweb_DelUser_res","emRet":"1"}
	************************************************************************/
	ev_umcweb_DelUser_res,

	/************************************************************************
	* 功能：用户信息通知请求
	* json：{"event":"ev_umcweb_User_nty_req"}
	************************************************************************/
	ev_umcweb_User_nty_req,

	/************************************************************************
	* 功能：用户信息通知回应
	* json：{"event":"ev_umcweb_User_nty_res","items":[
				{"name":"admin","pwd":"admin"}
				,{"name":"1","pwd":"1"}
			]}
	************************************************************************/
	ev_umcweb_User_nty_res,

	/************************************************************************
	* 功能：网络服务器配置请求
	* json：{"event":"ev_umcweb_IpCfg_req","ip":"172.16.216.120","submask":"255.255.248.0","gateway":"172.16.216.254"}
	************************************************************************/
	ev_umcweb_IpCfg_req,

	/************************************************************************
	* 功能：网络服务器配置回应
	* json：{"event":"ev_umcweb_IpCfg_res","ip":"172.16.216.120","submask":"255.255.248.0","gateway":"172.16.216.254"}
	************************************************************************/
	ev_umcweb_IpCfg_res,

	/************************************************************************
	* 功能：网络服务器配置通知型请求
	* json：{"event":"ev_umcweb_IpCfg_nty_req"}
	************************************************************************/
	ev_umcweb_IpCfg_nty_req,

	/************************************************************************
	* 功能：网络服务器配置通知型回应
	* json：{"event":"ev_umcweb_IpCfg_nty_res","ip":"172.16.216.120","submask":"255.255.248.0","gateway":"172.16.216.254"}
	************************************************************************/
	ev_umcweb_IpCfg_nty_res,

	/************************************************************************
	* 功能：sip服务器配置请求
	* json：{"event":"ev_umcweb_sipserver_req","ip":"172.16.216.120"}
	************************************************************************/
	ev_umcweb_sipserver_req,

	/************************************************************************
	* 功能：sip服务器配置回应
	* json：{"event":"ev_umcweb_sipserver_res","ip":"172.16.216.120"}
	************************************************************************/
	ev_umcweb_sipserver_res,

	/************************************************************************
	* 功能：sip服务器配置通知型请求
	* json：{"event":"ev_umcweb_sipserver_nty_req"}
	************************************************************************/
	ev_umcweb_sipserver_nty_req,

	/************************************************************************
	* 功能：sip服务器配置通知型回应
	* json：{"event":"ev_umcweb_sipserver_nty_res","ip":"172.16.216.120"}
	************************************************************************/
	ev_umcweb_sipserver_nty_res,

	/************************************************************************
	* 功能：sip服务器配置请求
	* json：{"event":"ev_umcweb_gkserver_req","ip":"172.16.216.120","bReg":"1"}
	************************************************************************/
	ev_umcweb_gkserver_req,

	/************************************************************************
	* 功能：sip服务器配置回应
	* json：{"event":"ev_umcweb_sipserver_res","ip":"172.16.216.120","bReg":"1"}
	************************************************************************/
	ev_umcweb_gkserver_res,

	/************************************************************************
	* 功能：sip服务器配置通知型请求
	* json：{"event":"ev_umcweb_gkserver_nty_req"}
	************************************************************************/
	ev_umcweb_gkserver_nty_req,

	/************************************************************************
	* 功能：sip服务器配置通知型回应
	* json：{"event":"ev_umcweb_gkserver_nty_req","ip":"172.16.216.120","bReg":"1"}
	************************************************************************/
	ev_umcweb_gkserver_nty_res,

	/************************************************************************
	* 功能：时间同步至服务器请求
	* json：{"event":"ev_umcweb_SetSysTime_req","nYear":"2014","nMonth":"10","nMDay":"30","nHour":"12","nMinute":"30","nSecond":"30"}
	************************************************************************/
	ev_umcweb_SetSysTime_req,

	/************************************************************************
	* 功能：时间同步至服务器回应
	* json：{"event":"ev_umcweb_SetSysTime_res","nYear":"2014","nMonth":"10","nMDay":"30","nHour":"12","nMinute":"30","nSecond":"30"}
	************************************************************************/
	ev_umcweb_SetSysTime_res,

	/************************************************************************
	* 功能：服务器时间通知型请求
	* json：{"event":"ev_umcweb_GetSysTime_nty_req"}
	************************************************************************/
	ev_umcweb_GetSysTime_nty_req,

	/************************************************************************
	* 功能：服务器时间通知型回应
	* json：{"event":"ev_umcweb_GetSysTime_nty_res","nYear":"2014","nMonth":"10","nMDay":"30","nHour":"12","nMinute":"30","nSecond":"30"}
	************************************************************************/
	ev_umcweb_GetSysTime_nty_res,

	/************************************************************************
	* 功能：增/删/改 网管服务器信息请求
	* json：{"event":"ev_umcweb_NMServer_req",
	"IsServerOn1":"1","NMServerIP1":"172.163.211.120","NMGetSetPort1":"126","NMTrapPort1":"163",
	"NMReadCommunity1":"Kedacom","NMWriteCommunity1":"Nexvision","NMServerNO1":"0",
	"IsServerOn2":"1","NMServerIP2":"172.163.211.120","NMGetSetPort2":"126","NMTrapPort2":"163",
	"NMReadCommunity2":"Kedacom","NMWriteCommunity2":"Nexvision","NMServerNO2":"1"}
	************************************************************************/
//	ev_umcweb_NMServer_req,

	/************************************************************************
	* 功能：增/删/改 网管服务器信息回应
	* json：{"event":"ev_umcweb_NMServer_res",
	"IsServerOn1":"1","NMServerIP1":"172.163.211.120","NMGetSetPort1":"126","NMTrapPort1":"163",
	"NMReadCommunity1":"Kedacom","NMWriteCommunity1":"Nexvision","NMServerNO1":"0",
	"IsServerOn2":"1","NMServerIP2":"172.163.211.120","NMGetSetPort2":"126","NMTrapPort2":"163",
	"NMReadCommunity2":"Kedacom","NMWriteCommunity2":"Nexvision","NMServerNO2":"1"}
	************************************************************************/
//	ev_umcweb_NMServer_res,

	/************************************************************************
	* 功能：网管服务器信息通知型请求
	* json：{"event":"ev_umcweb_NMServer_nty_req"}
	************************************************************************/
//	ev_umcweb_NMServer_nty_req,

	/************************************************************************
	* 功能：网管服务器信息通知型回应
	* json：{"event":"ev_umcweb_NMServer_nty_res",
	"IsServerOn1":"1","NMServerIP1":"172.163.211.120","NMGetSetPort1":"126","NMTrapPort1":"163",
	"NMReadCommunity1":"Kedacom","NMWriteCommunity1":"Nexvision","NMServerNO1":"0",
	"IsServerOn2":"1","NMServerIP2":"172.163.211.120","NMGetSetPort2":"126","NMTrapPort2":"163",
	"NMReadCommunity2":"Kedacom","NMWriteCommunity2":"Nexvision","NMServerNO2":"1"}
	************************************************************************/
//	ev_umcweb_NMServer_nty_res,


	/*************************会议模板 - begin******************************/

	/************************************************************************
	* 功能：会议模板操作结果回应
	* json：{"event":"ev_umcweb_OperatorConfTemplate_res","emReason":"0"}
	************************************************************************/
	ev_umcweb_OperatorConfTemplate_res,

	/************************************************************************
	* 功能：添加会议模板请求
	* json：{"event":"ev_umcweb_AddConftemplate_req",
	         "wConfTempID":"0","achConfName":"模板1","achStartTime":"0",
			 "atTpMainVideoRes":[{"achFormatName":"HP 1080P@50/60fps"},{"achFormatName":"HP 1080P@25/30fps"}],"wMainNum":"2",
			 "atTpMinorVideoRes":[{"achFormatName":"HP 1080P@50/60fps"},{"achFormatName":"HP 1080P@25/30fps"}],"wMinorNum":"2",
			 "atAudFmt":[{"achFormatName":"MPEG4 AAC-LD单声道"}],"wAudFmtNum":"1",
			 "nSingleRate":"2048","nShowRate":"2048","nUpBandWidth":"0","nDownBandWidth":"0",
			 "emEncryptModel":"2","achEncrypt":"123456",
			 "arrMeetList":[{"epId":"1","achMeetName":"会场1","achE164":"111","achMeetIp":"172.160.118.118"},
							{"epId":"2","achMeetName":"会场2","achE164":"222","achMeetIp":"172.160.118.118"}],"wMeetCount":"2",
			 "bPollOn":"1","wInterval":"20",
			 "arrPolling":[{"epId":"1","achMeetName":"会场1","achE164":"111","achMeetIp":"172.160.118.118"},
							{"epId":"2","achMeetName":"会场2","achE164":"222","achMeetIp":"172.160.118.118"}],"wPollingCount":"2",
			 "bDiscussOn":"0",
			 "arrDiscuss":[{"epId":"1","achMeetName":"会场1","achE164":"111","achMeetIp":"172.160.118.118"},
							{"epId":"2","achMeetName":"会场2","achE164":"222"}],"wDiscussCount":"2"
			}
	************************************************************************/
	ev_umcweb_AddConftemplate_req,

	/************************************************************************
	* 功能：更新会议模板请求
	* json：{"event":"ev_umcweb_UpdateConftemplate_req",
	         "wConfTempID":"1","achConfName":"模板1","achStartTime":"0",
			 "atTpMainVideoRes":[{"achFormatName":"HP 1080P@50/60fps"},{"achFormatName":"HP 1080P@25/30fps"}],"wMainNum":"2",
			 "atTpMinorVideoRes":[{"achFormatName":"HP 1080P@50/60fps"},{"achFormatName":"HP 1080P@25/30fps"}],"wMinorNum":"2",
			 "atAudFmt":[{"achFormatName":"MPEG4 AAC-LD单声道"}],"wAudFmtNum":"1",
			 "nSingleRate":"2048","nShowRate":"2048","nUpBandWidth":"0","nDownBandWidth":"0",
			 "emEncryptModel":"2","achEncrypt":"123456",
			 "arrMeetList":[{"epId":"1","achMeetName":"会场1","achE164":"111","achMeetIp":"172.160.118.118"},
							{"epId":"2","achMeetName":"会场2","achE164":"222","achMeetIp":"172.160.118.118"}],"wMeetCount":"2",
			 "bPollOn":"1","wInterval":"20",
			 "arrPolling":[{"epId":"1","achMeetName":"会场1","achE164":"111","achMeetIp":"172.160.118.118"},
			 {"epId":"2","achMeetName":"会场2","achE164":"222","achMeetIp":"172.160.118.118"}],"wPollingCount":"2",
			 "bDiscussOn":"0",
			 "arrDiscuss":[{"epId":"1","achMeetName":"会场1","achE164":"111","achMeetIp":"172.160.118.118"},
			 {"epId":"2","achMeetName":"会场2","achE164":"222"}],"wDiscussCount":"2"
			}
	************************************************************************/
	ev_umcweb_UpdateConftemplate_req,

	/************************************************************************
	* 功能：删除会议模板请求
	* json：{"event":"ev_umcweb_DelConftemplate_req","wConfTempID":"1"}
	************************************************************************/
	ev_umcweb_DelConftemplate_req,

	/************************************************************************
	* 功能：会议模板更新结果回应
	* json：{"event":"ev_umcweb_RefreshConfTempResult_res","wConfTempID":"1"}
	************************************************************************/
	ev_umcweb_RefreshConfTempResult_res,

	/************************************************************************
	* 功能：删除全部模板请求
	* json：{"event":"ev_umcweb_DelAllConftemp_req"}
	************************************************************************/
	ev_umcweb_DelAllConftemp_req,

	/************************************************************************
	* 功能：删除全部模板回应
	* json：{"event":"ev_umcweb_DelAllConftemp_res","emReason":"0"}
	************************************************************************/
	ev_umcweb_DelAllConftemp_res,

	/************************************************************************
	* 功能：召开会议请求
	* json：{"event":"ev_umcweb_StartConfTemplate_req","wConfTempID":"1"}
	************************************************************************/
	ev_umcweb_StartConfTemplate_req,

	/************************************************************************
	* 功能：召开会议结果回应
	* json：{"event":"ev_umcweb_StartConfTemplate_res","emReason":"0"}
	************************************************************************/
	ev_umcweb_StartConfTemplate_res,

	/************************************************************************
	* 功能：刷新会议模板列表通知型请求
	* json：{"event":"ev_umcweb_RefreshConftempList_nty_req","strSearch":"模板1"}
	************************************************************************/
	ev_umcweb_RefreshConftempList_nty_req,

	/************************************************************************
	* 功能：刷新会议模板列表通知型回应
	* json：{"event":"ev_umcweb_RefreshConftempList_nty_res","items":[
				{"wConfTempID":"1","achConfName":"模板1","achStartTime":"0","nMeetNum":"10","achHomeMeetName":"会场1"},
				{"wConfTempID":"2","achConfName":"模板2","achStartTime":"0","nMeetNum":"10","achHomeMeetName":"会场2"}
			],"count":"2"}
	************************************************************************/
	ev_umcweb_RefreshConftempList_nty_res,

	/************************************************************************
	* 功能：刷新会议模板具体信息通知型请求
	* json：{"event":"ev_umcweb_RefreshConftempInfo_nty_req","wConfTempID":"1"}
	************************************************************************/
	ev_umcweb_RefreshConftempInfo_nty_req,

	/************************************************************************
	* 功能：刷新会议模板具体信息通知型回应
	* json：{"event":"ev_umcweb_RefreshConftempInfo_nty_res",
			"wConfTempID":"1","achConfName":"模板1","achConfNum":"123","achStartTime":"0","nSingleRate":"2048","nShowRate":"2048","nUpBandWidth":"0","nDownBandWidth":"0",
			"emEncryptModel":"2","achEncrypt":"123456","nPollingTime":"20","wResNum":"5","wResUsedCount":"10",
			"atTpMainVideoRes":[{"achFormatName":"HP 1080P@50/60fps"},{"achFormatName":"HP 1080P@25/30fps"}],"wMainNum":"2",
			"atTpMinorVideoRes":[{"achFormatName":"HP 1080P@50/60fps"},{"achFormatName":"HP 1080P@25/30fps"}],"wMinorNum":"2",
			"atAudFmt":[{"achFormatName":"MPEG4 AAC-LD单声道"}],"wAudFmtNum":"1"
			}
	************************************************************************/
	ev_umcweb_RefreshConftempInfo_nty_res,

	/************************************************************************
	* 功能：刷新会议模板与会会场列表通知型请求
	* json：{"event":"ev_umcweb_RefreshConftemp_MeetNameList_nty_req","wConfTempID":"1","strSearch","会场1"}
	************************************************************************/
	ev_umcweb_RefreshConftemp_MeetNameList_nty_req,

	/************************************************************************
	* 功能：刷新会议模板与会会场列表通知型回应
	* json：{"event":"ev_umcweb_RefreshConftemp_MeetNameList_nty_res",
	        "items":[{"epId":"1","achMeetName":"会场1","achE164":"111","achMeetIp":"172.160.118.118"},
					{"epId":"2","achMeetName":"会场2","achE164":"222","achMeetIp":"172.160.118.118"}],"count":"2"}
	************************************************************************/
	ev_umcweb_RefreshConftemp_MeetNameList_nty_res,

	/************************************************************************
	* 功能：刷新会议模板轮询列表通知型请求
	* json：{"event":"ev_umcweb_RefreshConftemp_PollingList_nty_req","wConfTempID":"1"}
	************************************************************************/
	ev_umcweb_RefreshConftemp_PollingList_nty_req,

	/************************************************************************
	* 功能：刷新会议模板轮询列表通知型回应
	* json：{"event":"ev_umcweb_RefreshConftemp_PollingList_nty_res","bPollOn","0","wInterval","20",
	        "items":[{"epId":"1","achMeetName":"会场1","achE164":"111","achMeetIp":"172.160.118.118"},
					{"epId":"2","achMeetName":"会场2","achE164":"222","achMeetIp":"172.160.118.118"}],"count":"2"}
	************************************************************************/
	ev_umcweb_RefreshConftemp_PollingList_nty_res,

	/************************************************************************
	* 功能：刷新会议模板讨论列表通知型请求
	* json：{"event":"ev_umcweb_RefreshConftemp_DiscussList_nty_req","wConfTempID":"1"}
	************************************************************************/
	ev_umcweb_RefreshConftemp_DiscussList_nty_req,

	/************************************************************************
	* 功能：刷新会议模板讨论列表通知型回应
	* json：{"event":"ev_umcweb_RefreshConftemp_DiscussList_nty_res","bDiscussOn","0",
	        "items":[{"epId":"1","achMeetName":"会场1","achE164":"111","achMeetIp":"172.160.118.118"},
					{"epId":"2","achMeetName":"会场2","achE164":"222","achMeetIp":"172.160.118.118"}],"count":"2"}
	************************************************************************/
	ev_umcweb_RefreshConftemp_DiscussList_nty_res,

	/************************************************************************
	* 功能：当前资源数通知型请求
	* json：{"event":"ev_umcweb_ConfBasUsed_nty_req"}
	************************************************************************/
	ev_umcweb_ConfBasUsed_nty_req,

	/************************************************************************
	* 功能：当前资源数通知型回应
	* json：{"event":"ev_umcweb_ConfBasUsed_nty_res","wResUsedCount":"14"}
	************************************************************************/
	ev_umcweb_ConfBasUsed_nty_res,

	/************************************************************************
	* 功能：校验模板名称、号码是否重复 请求
	* json：{"event":"ev_umcweb_CheckConftempRepeat_req","wConfTempID":"1","achConfName":"模板1","achConfNum":"123"}
	************************************************************************/
	ev_umcweb_CheckConftempRepeat_req,

	/************************************************************************
	* 功能：校验模板名称、号码是否重复 回应
	* json：{"event":"ev_umcweb_CheckConftempRepeat_res","wNameRet":"0","wNumRet":"0"}
	************************************************************************/
	ev_umcweb_CheckConftempRepeat_res,

	/*************************会议模板 - end******************************/



	/*************************会场操作 - begin******************************/

	/************************************************************************
	* 功能：开启双流请求
	* json：{"event":"ev_umcweb_epoper_startdual_req","confid":"1","epid":"1"}
	************************************************************************/
	ev_umcweb_epoper_startdual_req,

	/************************************************************************
	* 功能：开启双流回应
	* json：{"event":"ev_umcweb_epoper_startdual_res","bRet":"1"}
	************************************************************************/
	ev_umcweb_epoper_startdual_res,

	/************************************************************************
	* 功能：关闭双流请求
	* json：{"event":"ev_umcweb_epoper_stopdual_req","confid":"1","epid":"1"}
	************************************************************************/
	ev_umcweb_epoper_stopdual_req,

	/************************************************************************
	* 功能：关闭双流回应
	* json：{"event":"ev_umcweb_epoper_stopdual_res","emRet":"0"}
	************************************************************************/
	ev_umcweb_epoper_stopdual_res,

	/************************************************************************
	* 功能：指定发言人请求
	* json：{"event":"ev_umcweb_epoper_applyspeaker_req","confid":"1","epid":"1"}
	************************************************************************/
	ev_umcweb_epoper_applyspeaker_req,

	/************************************************************************
	* 功能：指定发言人回应
	* json：{"event":"ev_umcweb_epoper_applyspeaker_res","emRet":"0"}
	************************************************************************/
	ev_umcweb_epoper_applyspeaker_res,

	/************************************************************************
	* 功能：静音请求
	* json：{"event":"ev_umcweb_epoper_quiet_req","confid":"1","epid":"1","bquiet":"0"}
	************************************************************************/
	ev_umcweb_epoper_quiet_req,

	/************************************************************************
	* 功能：静音回应
	* json：{"event":"ev_umcweb_epoper_quiet_res","bRet":"0"}
	************************************************************************/
	ev_umcweb_epoper_quiet_res,

	/************************************************************************
	* 功能：哑音请求
	* json：{"event":"ev_umcweb_epoper_mute_req","confid":"1","epid":"1","bmute":"0"}
	************************************************************************/
	ev_umcweb_epoper_mute_req,

	/************************************************************************
	* 功能：哑音回应
	* json：{"event":"ev_umcweb_epoper_mute_res","bRet":"0"}
	************************************************************************/
	ev_umcweb_epoper_mute_res,

	/************************************************************************
	* 功能：挂断请求
	* json：{"event":"ev_umcweb_epoper_drop_req","confid":"1","epid":"1"}
	************************************************************************/
	ev_umcweb_epoper_drop_req,

	/************************************************************************
	* 功能：挂断回应
	* json：{"event":"ev_umcweb_epoper_drop_res","emRet":"0"}
	************************************************************************/
	ev_umcweb_epoper_drop_res,

	/************************************************************************
	* 功能：呼叫请求
	* json：{"event":"ev_umcweb_epoper_call_req","confid":"1","epid":"1"}
	************************************************************************/
	ev_umcweb_epoper_call_req,

	/************************************************************************
	* 功能：呼叫回应
	* json：{"event":"ev_umcweb_epoper_call_res","emRet":"0"}
	************************************************************************/
	ev_umcweb_epoper_call_res,

	/************************************************************************
	* 功能：会场列表获取请求
	* json：{"event":"ev_umcweb_list_meetingroom_get_req","confid":"1"}
	************************************************************************/
	ev_umcweb_list_meetingroom_get_req,

	/************************************************************************
	* 功能：会场列表获取回应
	* json：{"event":"ev_umcweb_list_meetingroom_get_res"
			,"items":[{"epId":"1","achMeetName":"会场01","achE164":"12306","achMeetIp":"172.16.0.2"
					,"bOnline":"1","bDual":"0","bSpeaker":"0","bQuiet":"0","bMute":"0"}]
			,"count":"1"}
	************************************************************************/
	ev_umcweb_list_meetingroom_get_res,

	/************************************************************************
	* 功能：会场选看请求
	* json：{"event":"ev_umcweb_epoper_selview_req","confid":"1","epid":"1","screenIndex":"0","bSel":"0","emType":"0","dstEpID":"2"}
	************************************************************************/
	ev_umcweb_epoper_selview_req,

	/************************************************************************
	* 功能：会场选看回应
	* json：{"event":"ev_umcweb_epoper_selview_res","emRet":"0"}
	************************************************************************/
	ev_umcweb_epoper_selview_res,

	/************************************************************************
	* 功能：获取选看信息请求
	* json：{"event":"ev_umcweb_selviewinfo_get_req","confid":"1","epid":"1"}
	************************************************************************/
	ev_umcweb_selviewinfo_get_req,

	/************************************************************************
	* 功能：获取选看信息回应
	* json：{"event":"ev_umcweb_selviewinfo_get_res","items":[{"selId":"1","selType":"1","selName":"会场01"}],"count":"1"}
	************************************************************************/
	ev_umcweb_selviewinfo_get_res,
	

	/*************************会场操作 - end******************************/



	/*******************会议管理 - 浏览会议信息 - begin*********************/

	/************************************************************************
	* 功能：刷新 会议管理-会议信息 通知型请求
	* json：{"event":"ev_umcweb_RefreshConfinfoInfo_nty_req","wCurConfID":"1"}
	************************************************************************/
	ev_umcweb_RefreshConfinfoInfo_nty_req,

	/************************************************************************
	* 功能：刷新 会议管理-会议信息 通知型回应
	* json：{"event":"ev_umcweb_RefreshConfinfoInfo_nty_res",
			"achConfName":"模板1","achConfNum":"123","achStartTime":"0","nSingleRate":"2048","nShowRate":"2048","nUpBandWidth":"0","nDownBandWidth":"0",
			"achEncrypt":"123456","nPollingTime":"20","achAudioFormat":"MPEG4 AAC-LD单声道","wResNum":"5","wResUsedCount":"10",
			"atTpMainVideoRes":[{"achFormatName":"HP 1080P@50/60fps"},{"achFormatName":"HP 1080P@25/30fps"}],"wMainNum":"2",
			"atTpMinorVideoRes":[{"achFormatName":"HP 1080P@50/60fps"},{"achFormatName":"HP 1080P@25/30fps"}],"wMinorNum":"2"
			}
	************************************************************************/
	ev_umcweb_RefreshConfinfoInfo_nty_res,

	/************************************************************************
	* 功能：刷新 会议管理-会议信息-轮询列表 通知型请求
	* json：{"event":"ev_umcweb_RefreshConfinfo_PollingList_nty_req","wCurConfID":"1"}
	************************************************************************/
	ev_umcweb_RefreshConfinfo_PollingList_nty_req,

	/************************************************************************
	* 功能：刷新 会议管理-会议信息-轮询列表 通知型回应
	* json：{"event":"ev_umcweb_RefreshConfinfo_PollingList_nty_res","bPollOn","0","wInterval","20",
	        "items":[{"achMeetName":"会场1","achE164":"111"},{"achMeetName":"会场2","achE164":"222"}],"count":"2"}
	************************************************************************/
	ev_umcweb_RefreshConfinfo_PollingList_nty_res,

	/************************************************************************
	* 功能：刷新 会议管理-会议信息-讨论列表 通知型请求
	* json：{"event":"ev_umcweb_RefreshConfinfo_DiscussList_nty_req","wCurConfID":"1"}
	************************************************************************/
	ev_umcweb_RefreshConfinfo_DiscussList_nty_req,

	/************************************************************************
	* 功能：刷新 会议管理-会议信息-讨论列表 通知型回应
	* json：{"event":"ev_umcweb_RefreshConfinfo_DiscussList_nty_res","bDiscussOn","0",
	        "items":[{"achMeetName":"会场1","achE164":"111"},{"achMeetName":"会场2","achE164":"222"}],"count":"2"}
	************************************************************************/
	ev_umcweb_RefreshConfinfo_DiscussList_nty_res,

	/*******************会议管理 - 浏览会议信息 - end***********************/

	/*******************会议管理 - 会议轮询 - begin*************************/

	/************************************************************************
	* 功能：暂停、恢复轮询 请求
	* json：{"event":"ev_umcweb_SuspendTurn_req","wCurConfID":"1","bSuspend":"1"}
	************************************************************************/
	ev_umcweb_SuspendTurn_req,

	/************************************************************************
	* 功能：暂停、恢复轮询 回应
	* json：{"event":"ev_umcweb_SuspendTurn_res","emTPPollResult":"0"}
	************************************************************************/
	ev_umcweb_SuspendTurn_res,

	/************************************************************************
	* 功能：开启、关闭轮询 请求
	* json：{"event":"ev_umcweb_StartTurn_req","wCurConfID":"1","bStart":"1"}
	************************************************************************/
	ev_umcweb_StartTurn_req,

	/************************************************************************
	* 功能：开启、关闭轮询 回应
	* json：{"event":"ev_umcweb_StartTurn_res","bStart","1","emTPPollResult":"0"}
	************************************************************************/
	ev_umcweb_StartTurn_res,

	/************************************************************************
	* 功能：更新轮询列表 请求
	* json：{"event":"ev_umcweb_UpdateTurn_req","wCurConfID","1","wInterval":"20",
			"arrPolling":[{"epId":"1","achMeetName":"会场1","achE164":"111","achMeetIp":"172.160.118.118"},
						  {"epId":"2","achMeetName":"会场2","achE164":"222","achMeetIp":"172.160.118.118"}],
						  "wPollingCount":"2"}
	************************************************************************/
	ev_umcweb_UpdateTurn_req,

	/*******************会议管理 - 会议轮询 - end***************************/

	/*******************会议管理 - 会议讨论 - begin*************************/

	/************************************************************************
	* 功能：语音激励开启和关闭请求
	* json：{"event":"ev_umcweb_AuxMixVacSwitch_req","wCurConfID":"1","bVacOn":"1"}
	************************************************************************/
	ev_umcweb_AuxMixVacSwitch_req,

	/************************************************************************
	* 功能：语音激励开启和关闭回应
	* json：{"event":"ev_umcweb_AuxMixVacSwitch_res","bVacOn","1","wOprRet":"0"}
	************************************************************************/
	ev_umcweb_AuxMixVacSwitch_res,

	/************************************************************************
	* 功能：添加和删除讨论成员（讨论下用）请求
	* json：{"event":"ev_umcweb_UpdateAudMixInfo_req","wCurConfID":"1","wEpID":"1","emOprType":"0"}
	************************************************************************/
	ev_umcweb_UpdateAudMixInfo_req,

	/************************************************************************
	* 功能：添加和删除讨论成员（讨论下用）回应
	* json：{"event":"ev_umcweb_UpdateAudMixInfo_res"}
	************************************************************************/
	//ev_umcweb_UpdateAudMixInfo_res,

	/************************************************************************
	* 功能：开启和关闭讨论，开启和关闭语音激励， 或者非讨论下，更新讨论成员 请求
	* json：{"event":"ev_umcweb_StartAuxMix_req","wCurConfID":"1","bStart":"1","bVacOn":"1","wSpeakerIndex":"1",
		     "arrDiscuss":[{"epId":"1","achMeetName":"会场1","achE164":"111","achMeetIp":"172.160.118.118"},
						   {"epId":"2","achMeetName":"会场2","achE164":"222","achMeetIp":"172.160.118.118"}],
						    "wDiscussCount":"2"}
	************************************************************************/
	ev_umcweb_StartAuxMix_req,

	/************************************************************************
	* 功能：开启和关闭讨论，开启和关闭语音激励， 或者非讨论下，更新讨论成员 回应
	* json：{"event":"ev_umcweb_StartAuxMix_res"}
	************************************************************************/
	//ev_umcweb_StartAuxMix_res,

	/*******************会议管理 - 会议讨论 - end***************************/
	

	ev_umcweb_end,
#define EVENT_UMCWEB_END  ev_umcweb_end
};


#endif