#include "owslib.h"

////////////////////////////////////////////////////////////////////////////
// CMsgDriver

vector<CKdvDispEvent*> CMsgDriver::m_vpDispEvent;

CMsgDriver::CMsgDriver()
           :m_dwInstID(1) 
{
    m_pCurDispEvent = NULL;
	m_dwAppID =	0;			//����Ĭ��ԴAPP ID AID_DCE2DCS_APP
	m_dwDesAppID = 0;		//Ĭ�Ϸ�����APP AID_DCS2DCE_APP
	m_dwWaitingEvents = 0;
	m_hSem = NULL;
	OspSemCCreate( &m_hSem, 0, MAX_LOG_USR_NUM );
}

CMsgDriver::~CMsgDriver()
{
	OspSemDelete(m_hSem);
}


/*=======================================================================
�� �� ��:   GetMtMsgPtr
��    ��:   �õ�������Ϣָ��(����TMtMsg)
��    ��:   BOOL bClear = TRUE         [in]������Ϣָ��ʱ�Ƿ������Ϣ��
�� �� ֵ:   ������Ϣ����Ϣָ��
�����Ϣ:
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾  �޸���  �޸�����
2004/09/30  4.0   liuruifei  ����
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
�� �� ��:   GetCMsgPtr
��    ��:   �õ�������Ϣָ��(����TMtMsg)
��    ��:   BOOL bClear = TRUE         [in]������Ϣָ��ʱ�Ƿ������Ϣ��
�� �� ֵ:   ������Ϣ����Ϣָ��
�����Ϣ:
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾  �޸���  �޸�����
2004/09/30  4.0   liuruifei  �޸�
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
�� �� ��:   PostMsg
��    ��:   ������������Ϣ������Ҫ�ն��л�Ӧ�����ýӿ�ǰҪҪͨ��GetPostMsgPtr
            ��������Ϣ��
��    ��:   u32 dwType = TYPE_CMESSAGE   [in]��Ϣ����TYPE_CMESSAGE��TYPE_MTMSG
�� �� ֵ:
�����Ϣ:
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾  �޸���  �޸�����
2004/08/25  3.5   ���ǿ  ����
=======================================================================*/
u16 CMsgDriver::PostMsg(u32 dwType)
{   
    u32 dwDesIID = MAKEIID( GetDesAppID(), 1 );				// Ŀ�ģ�ҵ����֮ǰUMS��1������һ��ʵ����
																			// �������ݻ����õ�DAEMON
	u32 dwSrcIID = MAKEIID(GetAppID());	// Դ  ���ն˿���̨
	u16 wRet = NO_ERROR;
	u16 wEvent = 0;
	if (TYPE_TPMSG == dwType) 
	{  
		//����CMtMsg��Ϣ��
		{
			wRet = m_cKdvMsg.Post(dwDesIID, g_MsgRecApp.GetNodeId(), dwSrcIID);
		}
		wEvent = m_cKdvMsg.GetEvent();
    }
	else
	{
		//����Osp CMessage��Ϣ
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
	//��ӡ���
    std::string strEvent = COwsCommon::GetEventDescribe(wEvent);
	if(wRet == NO_ERROR)
	{  	 
	    //PrtMsg( "[uewebser]: ������Ϣ:%s(%u).\n", strEvent,wEvent);
	}
	else
	{    
	     PrtMsg( "[dcwebserver]: ������Ϣ:%s(%du)ʧ��,�����룺%d\n", strEvent.c_str(),wEvent,wRet); 
	}

    return wRet;
}

/*=======================================================================
�� �� ��:   PostCommand
��    ��:   ������������Ϣ��һ�����Ҫ�ն��л�Ӧ�����޻�Ӧ�򱨳�ʱ�����ýӿ�ǰ
            ҪҪͨ��GetPostMsgPtr��������Ϣ�壨�����ȴ���Ϣ��
��    ��:   CDispEvent *pDispEvent     [in]��Ӧ��Ϣ�Ĵ���ָ��
            u16 wWaitEvent             [in]�ڴ���Ӧ����Ϣ
            u32 dwTimeOut = 1000       [in]�ڴ���Ӧ����Ϣ��ʱʱ��
�� �� ֵ:
�����Ϣ:
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾  �޸���  �޸�����
2004/08/25  3.5   ���ǿ  ����
2004/10/28  3.5   �����   �޸�
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
�� �� ��:   RegHandler
��    ��:   ע��һ��������Ϣ�����ָ��
��    ��:   CDispEvent* const pDispEvnet       [in]������Ϣ����ָ��
�� �� ֵ:
�����Ϣ:
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾  �޸���  �޸�����
2004/08/23  3.5   ���ǿ  ����
=======================================================================*/
void CMsgDriver::RegHandler(CKdvDispEvent* const pDispEvnet)
{
	//2.14.05.08 ldy  ȥ���ظ� 
	std::vector<CKdvDispEvent*>::iterator itr = find( m_vpDispEvent.begin(), m_vpDispEvent.end(), pDispEvnet );
	if ( itr == m_vpDispEvent.end() )
	{
		m_vpDispEvent.push_back(pDispEvnet);
	}
}

/*=======================================================================
�� �� ��:   RegHandler
��    ��:   ע��һ��������Ϣ�����ָ��
��    ��:   CDispEvent* const pDispEvnet       [in]������Ϣ����ָ��
�� �� ֵ:
�����Ϣ:
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾  �޸���  �޸�����
2004/08/23  3.5   ���ǿ  ����
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
�� �� ��:   ClearHandler
��    ��:   �������ע������ָ��
��    ��:
�� �� ֵ:
�����Ϣ:
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾  �޸���  �޸�����
2004/08/23  3.5   ���ǿ  ����
=======================================================================*/
void CMsgDriver::ClearHandler()
{
    m_vpDispEvent.clear();
}

void CMsgDriver::MessageProc(/*CTpMsg *const ptMsg*/)
{
	// ��OSP�ص��߳���ȡ��Ϣ
    CMsgHandler *pHandler = CMsgHandler::GetMsgHandler();
    if (!pHandler) 
    {
        return;
    }

    CMsgQueue cMsgQue;
    pHandler->PopAllMsg(cMsgQue);

    // �ַ���Ϣ
    while(!cMsgQue.IsEmpty())
    {
        const CMessage& cMsg = cMsgQue.Front();

		std::string strMsgName = COwsCommon::GetEventDescribe(cMsg.event);
		if( strMsgName.empty() )
		{
			PrtMsg( "\t�յ�BDS��Ϣ��---eventid:%d δע��---\n", cMsg.event );
		}

        // ������Ϣ�ַ���
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
			PrtMsg( "\t�յ�bds��Ϣ��---event:%s δ���κ�ҵ���ദ��---\n", strMsgName.c_str() );
        }

		// ��������Ӧ����Ϣ
		if(m_dwWaitingEvents == cMsg.event)
		{
			ClearWaiting();
			ReleaseLock();
		}
		
        cMsgQue.Pop();
    }
}



/*=============================================================================
  �� �� ���� ClearWaiting
  ��    �ܣ� ��յȴ���Ϣ���飬�Ա����IsHandleCmdʱΪFALSE��ʹ��Ϣ���Լ�������
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� void 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/10/13     3.5		�����                  �淶��
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