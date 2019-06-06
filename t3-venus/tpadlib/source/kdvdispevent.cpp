
#include "StdAfx.h"
#include "kdvdispevent.h"

CKdvDispEvent::CKdvDispEvent()
{
    m_hWnd = NULL;
}

CKdvDispEvent::~CKdvDispEvent()
{
    ClearDisp();
}

/*=======================================================================
�� �� ��:   RegDispFunPointer
��    ��:   ��һ����Ϣ���䴦������ע�����
��    ��:   u16 wEvent                 [in]Ҫ��������Ϣ
            DISPEVENT_PFUN pFun        [in]������Ϣ���ຯ��ָ��
            u16 wMsgType               [in]������Ϣ������TYPE_CMESSAGE/TYPE_MTMSG
�� �� ֵ:
�����Ϣ:
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾  �޸���  �޸�����
2004/08/23  3.5   ���ǿ  ����
=======================================================================*/
void CKdvDispEvent::RegDispFunPointer(u16 wEvent, DISPEVENT_PFUN pFun)
{
    m_mappFun[wEvent] = pFun;
}

/*=======================================================================
�� �� ��:   HasRegEvent
��    ��:   �ж�һ��Ϣ�Ƿ��ڱ�����ע���
��    ��:   u16 wEvent                 [in]Ҫ������Ϣ
�� �� ֵ:   ע�������TRUE, ûע�������FALSE
�����Ϣ:
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾  �޸���  �޸�����
2004/08/23  3.5   ���ǿ  ����
=======================================================================*/
BOOL CKdvDispEvent::HasRegEvent(u16 wEvent) const
{
	if (m_mappFun.find(wEvent) != m_mappFun.end())
	{
		return TRUE;
    }
    return FALSE;  
}

/*=======================================================================
�� �� ��:   ClearDisp
��    ��:   ��յ�����ע�����Ϣ
��    ��:
�� �� ֵ:
�����Ϣ:
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾  �޸���  �޸�����
2004/08/23  3.5   ���ǿ  ����
=======================================================================*/
void CKdvDispEvent::ClearDisp()
{
    m_mappFun.clear();
}

/*=============================================================================
  �� �� ���� PostEvent ���տ�Ŀ�괰�ڷ�����Ϣ
  ��    �ܣ� 
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u32 dwEvent        �ն��ڲ�������¼�ID
             WPARAM wParam     
             LPARAM lParam
  �� �� ֵ�� BOOL               �Ƿ��ͳɹ�
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/10/13     3.5		�����                  �淶��
=============================================================================*/
BOOL CKdvDispEvent::PostEvent(u32 dwEvent, WPARAM wParam, LPARAM lParam)
{
    if(m_hWnd != NULL)
    {
        return ::SendMessage(m_hWnd, dwEvent, wParam, lParam);
    }
    return FALSE;
}