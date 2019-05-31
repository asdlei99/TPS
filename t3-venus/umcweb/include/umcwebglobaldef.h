/*****************************************************************************
ģ����      : umcwebglobaldef.h
�ļ���      : umcwebglobaldef.h.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcweb��Ŀ����ͷ�ļ�
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/4/25      1.0         ����ӡ      ����
******************************************************************************/
#ifndef UMCWEBGLOBALDEF_H 
#define UMCWEBGLOBALDEF_H

#include "resource.h"

#pragma warning( disable : 4786 )	// ��ʶ�����Ƴ���255�ֽ�
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
#include "kdvType.h"		// ��������
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

//�Զ����
#define UMCWEB_CONFIG "C:\\UMSCONFIG.ini"

//����Ӧ�ֱ���
#define BASE_SCREEN_WIDTH 1366
#define BASE_SCREEN_HEIGHT 768
#define BASE_SCREEN_WIDTH_INIE 1342
#define BASE_SCREEN_HEIGHT_INIE 651

//////////////////////////////////////////////////////////////////////////////////////////////////
//�Զ�����Ϣӳ�亯��
enum EM_DEFMSG_TYPE
{
	WM_DEF_UPDATEGROUPLISTCONTROL = UMSWEB_MSG_BEGIN,     //���»���ģ��ҳ��᳡�б���Ӳ���
	WM_DEF_UPDATEPOLLINGLISTCONTROL,			    	//���»���ģ��ҳ����ѯ�б���Ӳ���
    WM_DEF_UPDATESYSTEMINFO_WARNING,
	WM_DEF_UPDATE_WARNING_ICON,
	WM_DEF_CLICKMEETLISTMENUUPDATE,
	WM_DEF_HIDE_LOSEFOCUSHIDER,							//����ʧȥ��������صĴ���
	WM_DEF_SENDTMPINFOTOPAGE,							//ý��ҳ��ģ��ҳ�����ݽ���
	WM_DEF_CHANGEBKCOLOR,                                //���͸ı䱳��ɫ֪ͨ   WPARAM:TRUE��½     ����Ϊע��
	WM_DEF_HIDE_LOSEFOCUSHIDER_SHOWOPT,					//����ʧȥ��������ص�OPT����
	WM_DEF_CHANGE_DISCUSSEP, 							//�ı�������۵Ļ᳡
	WM_DEF_SWITCH_DISCUSS								//����/�رջ�������
};

//����Tab��ͼ
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

//��ַ����������
enum EM_Addrbook_OperateType
{
	em_AddrBook_Copy, 
	em_AddrBook_Cut,
};

//��ַ����˵�����
enum EM_MENU_ADDRBOOKTYPE
{
	em_Menu_Addr_All = 0,
	em_Menu_Addr_Group,
	em_Menu_Addr_Online,
	em_Menu_Addr_NotOnline,
	em_Menu_Addr_NewGroup,
	em_Menu_Addr_Import,
};

//�����б�˵�����
enum EM_MENU_MEETTYPE
{
	em_Menu_AllMeet = 0,
	em_Menu_CurMeet,
	em_Menu_OrderMeet
};

//�û������������
enum EM_USERWND_CUROPERATE_STATE
{
	em_NEW_STATUS = 0,
	em_EDIT_STATUS,
	em_DELETE_STATUS,
	em_SCANF_STATUS
};

//����ģ��ҳ������״̬  �༭״̬  �½�״̬  ���״̬
enum EM_OPERATE_FLAG
{	em_EDIT_PAGE_STATUS = 0,
	em_NEW_PAGE_STATUS,
	em_SCANF_PAGE_STATUS
};   
//����ģ��ҳ��    ������Ϣҳ��   �᳡ҳ��   ��ѯҳ��   ��������
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


//ָ�����
#define SAFE_RELEASE(x) if((x) != NULL){ delete (x); (x) = NULL; } 
#define SAFE_RELEASE_ARRAY(x) if((x) != NULL){ delete[] (x); (x) = NULL; } 

//��ȡΨһID
#ifndef GETUNIQID
#define GETUNIQID CUmcwebCommon::GetUniqID()
#endif



typedef struct tagTvwCns
{
    TTPName	m_tName; //�᳡����
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
