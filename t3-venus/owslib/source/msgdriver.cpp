#include "owslib.h"

////////////////////////////////////////////////////////////////////////////
// CMsgDriver

vector<CKdvDispEvent*> CMsgDriver::m_vpDispEvent;

CMsgDriver::CMsgDriver()
           :m_dwInstID(1) 
{
    m_pCurDispEvent = NULL;
	m_dwAppID =	0;			//设置默认源APP ID AID_DCE2DCS_APP
	m_dwDesAppID = 0;		//默认服务器APP AID_DCS2DCE_APP
	m_dwWaitingEvents = 0;
	m_hSem = NULL;
	OspSemCCreate( &m_hSem, 0, MAX_LOG_USR_NUM );
}

CMsgDriver::~CMsgDriver()
{
	OspSemDelete(m_hSem);
}


/*=======================================================================
函 数 名:   GetMtMsgPtr
功    能:   得到发送消息指针(发送TMtMsg)
参    数:   BOOL bClear = TRUE         [in]返回消息指针时是否清空消息体
返 回 值:   发送消息的消息指针
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/09/30  4.0   liuruifei  创建
=======================================================================*/
CTpMsg* CMsgDriver::GetKdvMsgPtr(BOOL32 bClear)
{
    if (bClear) 
    {
        memset( &m_cKdvMsg, 0, sizeof(CTpMsg) );
    }

    return &m_cKdvMsg;
}
/*=======================================================================
函 数 名:   GetCMsgPtr
功    能:   得到发送消息指针(发送TMtMsg)
参    数:   BOOL bClear = TRUE         [in]返回消息指针时是否清空消息体
返 回 值:   发送消息的消息指针
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/09/30  4.0   liuruifei  修改
=======================================================================*/
CMessage* CMsgDriver::GetCMsgPtr(BOOL32 bClear /* = TRUE */)
{
	if (bClear)
	{
		memset( &m_cMsg, 0, sizeof(CMessage));
	}

	return &m_cMsg;
}

/*=======================================================================
函 数 名:   PostMsg
功    能:   发送命令型消息，不需要终端有回应。调用接口前要要通过GetPostMsgPtr
            来设置消息体
参    数:   u32 dwType = TYPE_CMESSAGE   [in]消息类型TYPE_CMESSAGE或TYPE_MTMSG
返 回 值:
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/08/25  3.5   李洪强  创建
=======================================================================*/
u16 CMsgDriver::PostMsg(u32 dwType)
{   
    u32 dwDesIID = MAKEIID( GetDesAppID(), 1 );				// 目的：业务组之前UMS用1分配了一个实例号
																			// 现在数据会议用的DAEMON
	u32 dwSrcIID = MAKEIID(GetAppID());	// 源  ：终端控制台
	u16 wRet = NO_ERROR;
	u16 wEvent = 0;
	if (TYPE_TPMSG == dwType) 
	{  
		//发送CMtMsg消息体
		{
			wRet = m_cKdvMsg.Post(dwDesIID, g_MsgRecApp.GetNodeId(), dwSrcIID);
		}
		wEvent = m_cKdvMsg.GetEvent();
    }
	else
	{
		//发送Osp CMessage消息
		if(m_cMsg.dstid != INVALID_NODE)
		{
			dwDesIID = m_cMsg.dstid;
		}
		if(m_cMsg.srcid != INVALID_NODE)
		{
			dwSrcIID = m_cMsg.srcid;
		}

		wRet = OspPost(dwDesIID, m_cMsg.event, m_cMsg.content, m_cMsg.length,
        g_MsgRecApp.GetNodeId(), dwSrcIID);

		wEvent = m_cMsg.event;
	}
	//打印输出
    std::string strEvent = COwsCommon::GetEventDescribe(wEvent);
	if(wRet == NO_ERROR)
	{  	 
	    //PrtMsg( "[uewebser]: 发送消息:%s(%u).\n", strEvent,wEvent);
	}
	else
	{    
	     PrtMsg( "[dcwebserver]: 发送消息:%s(%du)失败,错误码：%d\n", strEvent.c_str(),wEvent,wRet); 
	}

    return wRet;
}

/*=======================================================================
函 数 名:   PostCommand
功    能:   发送请求型消息，一般会需要终端有回应，如无回应则报超时。调用接口前
            要要通过GetPostMsgPtr来设置消息体（单个等待消息）
参    数:   CDispEvent *pDispEvent     [in]响应消息的处理指针
            u16 wWaitEvent             [in]期待响应的消息
            u32 dwTimeOut = 1000       [in]期待响应的消息超时时间
返 回 值:
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/08/25  3.5   李洪强  创建
2004/10/28  3.5   王慧琛   修改
=======================================================================*/
u16 CMsgDriver::PostCommand(CKdvDispEvent *pDispEvent, u16 dwWaitEvent,  u32 dwType, u32 dwTimeOut)
{
    m_pCurDispEvent = pDispEvent;
    
	m_dwWaitingEvents = dwWaitEvent;

	u16 dwRet = PostMsg(dwType);

	if ( dwRet == 0 )
	{
		PrtMsg("\n-------------OspSemTake-------------\n");
		OspSemTake(m_hSem);
	}

    return dwRet;
}

/*=======================================================================
函 数 名:   RegHandler
功    能:   注册一个处理消息的类的指针
参    数:   CDispEvent* const pDispEvnet       [in]处理消息的类指针
返 回 值:
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/08/23  3.5   李洪强  创建
=======================================================================*/
void CMsgDriver::RegHandler(CKdvDispEvent* const pDispEvnet)
{
	//2.14.05.08 ldy  去除重复 
	std::vector<CKdvDispEvent*>::iterator itr = find( m_vpDispEvent.begin(), m_vpDispEvent.end(), pDispEvnet );
	if ( itr == m_vpDispEvent.end() )
	{
		m_vpDispEvent.push_back(pDispEvnet);
	}
}

/*=======================================================================
函 数 名:   RegHandler
功    能:   注销一个处理消息的类的指针
参    数:   CDispEvent* const pDispEvnet       [in]处理消息的类指针
返 回 值:
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/08/23  3.5   李洪强  创建
=======================================================================*/
void CMsgDriver::UnregHandler(CKdvDispEvent* const pDispEvnet)
{
    vector<CKdvDispEvent*>::iterator itr = m_vpDispEvent.begin();
    for(; itr != m_vpDispEvent.end(); itr++)
    {
        if (*itr == pDispEvnet) 
        {
            m_vpDispEvent.erase(itr);
            break;
        }
    }
}

/*=======================================================================
函 数 名:   ClearHandler
功    能:   清空所有注册的类的指针
参    数:
返 回 值:
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/08/23  3.5   李洪强  创建
=======================================================================*/
void CMsgDriver::ClearHandler()
{
    m_vpDispEvent.clear();
}

void CMsgDriver::MessageProc(/*CTpMsg *const ptMsg*/)
{
	// 从OSP回调线程提取消息
    CMsgHandler *pHandler = CMsgHandler::GetMsgHandler();
    if (!pHandler) 
    {
        return;
    }

    CMsgQueue cMsgQue;
    pHandler->PopAllMsg(cMsgQue);

    // 分发消息
    while(!cMsgQue.IsEmpty())
    {
        const CMessage& cMsg = cMsgQue.Front();

		std::string strMsgName = COwsCommon::GetEventDescribe(cMsg.event);
		if( strMsgName.empty() )
		{
			PrtMsg( "\t收到BDS消息：---eventid:%d 未注册---\n", cMsg.event );
		}

        // 检索消息分发表
		vector<CKdvDispEvent*>::iterator itr = m_vpDispEvent.begin();
        BOOL bHandle = FALSE;
        for(; itr != m_vpDispEvent.end(); itr++)
        {
            if ((*itr)->HasRegEvent(cMsg.event)) 
            {
                (*itr)->DispEvent(cMsg);

                bHandle = TRUE;
            }
        }
        if (!bHandle) 
        {
			PrtMsg( "\t收到bds消息：---event:%s 未被任何业务类处理---\n", strMsgName.c_str() );
        }

		// 检索命令应答消息
		if(m_dwWaitingEvents == cMsg.event)
		{
			ClearWaiting();
			ReleaseLock();
		}
		
        cMsgQue.Pop();
    }
}



/*=============================================================================
  函 数 名： ClearWaiting
  功    能： 清空等待消息数组，以便调用IsHandleCmd时为FALSE，使消息得以继续发送
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/13     3.5		王慧琛                  规范化
=============================================================================*/
void CMsgDriver::ClearWaiting()
{
    m_pCurDispEvent = NULL;
	m_dwWaitingEvents = 0;
}

void CMsgDriver::SetSndInstID( u32 dwInstID )
{
	m_dwInstID = dwInstID;
}

u32  CMsgDriver::GetSndInstID()
{
	return m_dwInstID;
}

BOOL CMsgDriver::PostEvent( u32 dwEvent, const boost::any& arg )
{
	BOOL bHandle = FALSE;
	if ( m_vpDispEvent.size() > 0 )
	{
		vector<CKdvDispEvent*>::iterator itr = m_vpDispEvent.begin();
		for(; itr != m_vpDispEvent.end(); itr++)
		{
			if ((*itr)->HasRegReqEvent(dwEvent)) 
            {
                (*itr)->DispReqEvent( dwEvent, arg );
				
                bHandle = TRUE;
            }
		}
	}
	return bHandle;
}

void CMsgDriver::ReleaseLock()
{
	::OspSemGive(m_hSem);
	PrtMsg("\n-------------OspSemGive-------------\n");
}