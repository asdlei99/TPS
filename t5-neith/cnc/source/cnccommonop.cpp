#include "StdAfx.h"
#include "cnccommonop.h"

#include "mainframelogic.h"
#include "loginlogic.h"
#include "mainmenulogic.h"
#include "cnsmanagelogic.h"
#include "addrbooklogic.h"
#include "conftemplogic.h"
#include "regservicelogic.h"
#include "roomctrllogic.h"
#include "PanCamlogic.h"
#include "confctrllogic.h"
#include "audmixlogic.h"
#include "videomixlogic.h"
#include "addreditlogic.h"
#include "usermanager.h"
#include "userdefinedlogic.h"
#include "confcallcfglogic.h"
#include "confmsglogic.h"
#include "sysconfiglogic.h"
#include "localroomcfglog.h"
#include "srcselwatch.h"
#include "messageboxlogic.h"
#include "calendarlogic.h"
#include "centercontrollogic.h"
#include "centermonitorlogic.h"
#include "confpolllogic.h"
#include "confrolllogic.h"
#include "confmixlogic.h"
#include "tvwalllogic.h"
#include "cameracontrollogic.h"
#include "matrixlogic.h"
#include "reconnectlogic.h"
#include "contentreqlogic.h"

ICncCommonOp::ICncCommonOp(void)
{
}


ICncCommonOp::~ICncCommonOp(void)
{
}


void ICncCommonOp::RegLogics()
{
	REG_LOGIC(CMainFrameLogic);
	REG_LOGIC(CLoginLogic);
	REG_LOGIC(CMainMenuLogic);
	REG_LOGIC(CCnsManageLogic);
	REG_LOGIC(CAddrBookLogic);
	REG_LOGIC(CConfTempLogic);
	REG_LOGIC(CRegServiceLogic);
	REG_LOGIC(CRoomCtrlLogic);
	REG_LOGIC(CPanCamLogic);
	REG_LOGIC(CConfCtrlLogic);
	REG_LOGIC(CAudMixLogic);
    REG_LOGIC(CVideoMixLogic);
	REG_LOGIC(CConfPollLogic);
	REG_LOGIC(CConfRollLogic);
	REG_LOGIC(CAddrEditLogic);
	REG_LOGIC(CUserManagerLogic);
	REG_LOGIC(CUserDefinedLogic);
	REG_LOGIC(CConfCallCfgLogic);
	REG_LOGIC(CConfMsgDlgLogic);
	REG_LOGIC(CSysConfigLogic);
	REG_LOGIC(CLocalRoomCfgLogic);
	REG_LOGIC(CSrcSelWatchLogic);
	REG_LOGIC(CMessageBoxLogic);
	REG_LOGIC(CCalendarLogic);
	REG_LOGIC(CCenterCtrlLogic);
	REG_LOGIC(CCenterMonitorLogic);
	REG_LOGIC(CConfMixLogic);
    REG_LOGIC(CTvWallLogic);
	REG_LOGIC(CCameraControlLogic);
	REG_LOGIC(CMatrixLogic);
	REG_LOGIC(CReconnectLogic);
    REG_LOGIC(CContentReqLogic);
	return ;
}

bool ICncCommonOp::NotifyMsg(u16 wMsgId, void *pData)
{
	TMsgParam Msg;
	Msg.wMsgId = wMsgId;
	Msg.pData = (UINT_PTR)pData;
	ICncMsgManager::GetSingletonPtr()->PostMsg(Msg);
	return true;
}

bool ICncCommonOp::NotifyMsg(u16 wMsgId, WPARAM wParam, LPARAM lParam)
{
	TMsgParam Msg;
	Msg.wMsgId = wMsgId;
	Msg.pData = (UINT_PTR)wParam;
	Msg.lParam = lParam;
	ICncMsgManager::GetSingletonPtr()->PostMsg(Msg);
	return true;
}


MbString ICncCommonOp::StringFormat(const char *format, ... )
{
	char str[1024] = { 0 };
	va_list pvlist;
	va_start(pvlist, format);
	vsnprintf((char *)str, 1024, format, pvlist);
	va_end(pvlist);
	return str;
}
