/*****************************************************************************
模块名      : umcwebglobaldef.h
文件名      : umcwebglobaldef.h.h
相关文件    : 
文件实现功能: umcweb项目公共头文件
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/4/25      1.0         刘德印      创建
******************************************************************************/
#ifndef UMCWEBGLOBALDEF_H 
#define UMCWEBGLOBALDEF_H

#include "resource.h"

#pragma warning( disable : 4786 )	// 标识符名称超过255字节
#pragma warning( disable : 4067 )
#pragma warning( disable : 4129 )
#pragma warning( disable : 4503 )
#pragma warning( disable : 4800 )

//70-common
#include "uiexhead.h"
#include "cmsConst.h"
#include "tperrno.h"

#include "umclib.h"
#pragma comment(lib,"uiex.lib")
#include "transparentbasedlg.h"
#include "TransparentDlgWarning.h"
#include "MessageDlg.h"
//#include "umcwebglobaldef.h"
#include "umcwebcommon.h"
#include "outPrint.h"

//10-common
#include "kdvType.h"		// 公共类型
#include "evCmsLib.h"
#include "commonapi.h"

#include "IValue.h"
#include "ItemFactory.h"
#include "MsgDispatch.h"
#include "msghandle.h"

#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <set>
using namespace std;

//自定义宏
#define UMCWEB_CONFIG "C:\\UMSCONFIG.ini"

//自适应分辨率
#define BASE_SCREEN_WIDTH 1366
#define BASE_SCREEN_HEIGHT 768
#define BASE_SCREEN_WIDTH_INIE 1342
#define BASE_SCREEN_HEIGHT_INIE 651

//////////////////////////////////////////////////////////////////////////////////////////////////
//自定义消息映射函数
enum EM_DEFMSG_TYPE
{
	WM_DEF_UPDATEGROUPLISTCONTROL = UMSWEB_MSG_BEGIN,     //更新会议模板页面会场列表添加操作
	WM_DEF_UPDATEPOLLINGLISTCONTROL,			    	//更新会议模板页面轮询列表添加操作
    WM_DEF_UPDATESYSTEMINFO_WARNING,
	WM_DEF_UPDATE_WARNING_ICON,
	WM_DEF_CLICKMEETLISTMENUUPDATE,
	WM_DEF_HIDE_LOSEFOCUSHIDER,							//隐藏失去焦点就隐藏的窗口
	WM_DEF_SENDTMPINFOTOPAGE,							//媒体页面模板页面数据交互
	WM_DEF_CHANGEBKCOLOR,                                //发送改变背景色通知   WPARAM:TRUE登陆     否则为注销
	WM_DEF_HIDE_LOSEFOCUSHIDER_SHOWOPT,					//隐藏失去焦点就隐藏的OPT窗口
	WM_DEF_CHANGE_DISCUSSEP, 							//改变参与讨论的会场
	WM_DEF_SWITCH_DISCUSS								//开启/关闭会议讨论
};

//界面Tab视图
enum EM_CURRENT_WND_VIEW_TYPE
{
	em_WND_LOCALADDR = 0x1,
	em_WND_PUBLICADDR,
	em_WND_MEETTMP,
	em_WND_MEETINFO,
	em_WND_TVW,
	em_WND_SYSTEMSET,
	em_WND_VTR,
	em_WND_VTRSET,
	em_WND_VEDIOFILELIST,
	em_WND_VEDIORECORD,
	em_WND_USER,
	em_WND_UMSNETCFG,
	em_WND_SIPNETCFG,
	em_WND_GKSET,
	em_WND_SYSTEMTIME,
	em_WND_NMCFG,
	em_WND_VTRCFG,
	em_WND_ADDREDIT,
	em_WND_PAGECLEAN,
};

//地址簿操作类型
enum EM_Addrbook_OperateType
{
	em_AddrBook_Copy, 
	em_AddrBook_Cut,
};

//地址簿表菜单类型
enum EM_MENU_ADDRBOOKTYPE
{
	em_Menu_Addr_All = 0,
	em_Menu_Addr_Group,
	em_Menu_Addr_Online,
	em_Menu_Addr_NotOnline,
	em_Menu_Addr_NewGroup,
	em_Menu_Addr_Import,
};

//会议列表菜单类型
enum EM_MENU_MEETTYPE
{
	em_Menu_AllMeet = 0,
	em_Menu_CurMeet,
	em_Menu_OrderMeet
};

//用户管理界面类型
enum EM_USERWND_CUROPERATE_STATE
{
	em_NEW_STATUS = 0,
	em_EDIT_STATUS,
	em_DELETE_STATUS,
	em_SCANF_STATUS
};

//会议模板页面三个状态  编辑状态  新建状态  浏览状态
enum EM_OPERATE_FLAG
{	em_EDIT_PAGE_STATUS = 0,
	em_NEW_PAGE_STATUS,
	em_SCANF_PAGE_STATUS
};   
//会议模板页面    会议信息页面   会场页面   轮询页面   会议讨论
enum EM_CURRENT_TABPAGE
{
	em_MEETINFO_PAGE = 0,
	em_Ep_PAGE,
	em_POLLING_PAGE,
	em_DISCUSS_PAGE
};

//set focus on hour, minute, second
enum EM_CURRENT_FOCUS
{
    em_Focus_Hour = 0,
    em_Focus_Minute,
    em_Focus_Second
};


//指针清空
#define SAFE_RELEASE(x) if((x) != NULL){ delete (x); (x) = NULL; } 
#define SAFE_RELEASE_ARRAY(x) if((x) != NULL){ delete[] (x); (x) = NULL; } 

//获取唯一ID
#ifndef GETUNIQID
#define GETUNIQID CUmcwebCommon::GetUniqID()
#endif



typedef struct tagTvwCns
{
    TTPName	m_tName; //会场名称
    u16 m_wScreenNum;
    THduPlanUnit  m_tHduUnit[MAX_DISPLAY_NUM];
    
    tagTvwCns()
    {
        Clear();
    }
    
    void Clear()
    {
        m_wScreenNum = 1;
        m_tName.Clear();
        memset(m_tHduUnit, 0, sizeof(m_tHduUnit));
    }
}TTvwCns;

#define MSG_UI_VTR_TAB_CHANGE		WM_USER + 1

#define MAX_VTR_FILE_LIST_SIZE		32

#include "TouchListHelp.h"

#endif
