#include "StdAfx.h"
#include "tpadcommonop.h"

#include "mainframelogic.h"
#include "loginlogic.h"
#include "mainmenulogic.h"
#include "messageboxlogic.h"
#include "filemanager.h"
#include "filepreview.h"
#include "toolwindowlogic.h"
#include "wbconflogic.h"
#include "videologic.h"
#include "aboutlogic.h"
#include "modalwndlogic.h"
#include "ipcfglogic.h"
#include "wificfglogic.h"
#include "tpadupdateLogic.h"
#include "sysupdateLogic.h"
#include "reconnectlogic.h"

ITPadCommonOp::ITPadCommonOp(void)
{
}


ITPadCommonOp::~ITPadCommonOp(void)
{
}


void ITPadCommonOp::RegLogics()
{
	REG_LOGIC(CMainFrameLogic);
	REG_LOGIC(CLoginLogic);
    REG_LOGIC(CMainMenuLogic);
    REG_LOGIC(CMessageBoxLogic);
	REG_LOGIC(CFileManagerLogic);
	REG_LOGIC(CFilePreviewLogic);
	REG_LOGIC(CToolWindowLogic);
	REG_LOGIC(CWBConfLogic);
	REG_LOGIC(CVideoLogic);
	REG_LOGIC(CAboutLogic);
	REG_LOGIC(CModalWndLogic);	
    REG_LOGIC(CIpCfgLogic);
    REG_LOGIC(CWifiCfgLogic);
	REG_LOGIC(CTPadUpdateLogic);
	REG_LOGIC(CSysUpdateLogic);
	REG_LOGIC(CReconnectLogic);
	return ;
}

bool ITPadCommonOp::NotifyMsg(u16 wMsgId, void *pData)
{
	TMsgParam Msg;
	Msg.wMsgId = wMsgId;
	Msg.pData = (UINT_PTR)pData;
	ITPadMsgManager::GetSingletonPtr()->PostMsg(Msg);
	return true;
}

bool ITPadCommonOp::NotifyMsg(u16 wMsgId, WPARAM wParam, LPARAM lParam)
{
	TMsgParam Msg;
	Msg.wMsgId = wMsgId;
	Msg.pData = (UINT_PTR)wParam;
	Msg.lParam = lParam;
	ITPadMsgManager::GetSingletonPtr()->PostMsg(Msg);
	return true;
}


MbString ITPadCommonOp::StringFormat(const char *format, ... )
{
	char str[1024] = { 0 };
	va_list pvlist;
	va_start(pvlist, format);
	vsnprintf((char *)str, 1024, format, pvlist);
	va_end(pvlist);
	return str;
}
