#include "StdAfx.h"
#include "tpadmsgmanager.h"
#include "WndObserver.h"

CTPadMsgManager::CTPadMsgManager(void)
{
}


CTPadMsgManager::~CTPadMsgManager(void)
{
}

void CTPadMsgManager::AddObserver(IObserver_MsgPrama* pObserver)
{
	m_cMsgManager.AddObserver(pObserver);
}


void CTPadMsgManager::RemoveObserver(IObserver_MsgPrama* pObserver)
{
	m_cMsgManager.RemoveObserver(pObserver);
}

void CTPadMsgManager::SendMsg(TMsgParam& tMsgParam)
{
	m_cMsgManager.SendMsg(tMsgParam);
}

void CTPadMsgManager::PostMsg( TMsgParam& tMsgParam )
{
	m_cMsgManager.PostMsg(tMsgParam);
}

void CTPadMsgManager::AddWindowObserver(HWND hwnd)
{
	WndObMap::iterator itr = m_mapWndObs.find(hwnd);
	if (itr != m_mapWndObs.end())
	{
		return;
	}
	CWndObserver *pWndOb = new CWndObserver(hwnd);
	m_mapWndObs[hwnd] = pWndOb;
	m_cMsgManager.AddObserver(pWndOb);
}

void CTPadMsgManager::RemoveWindowObserver( HWND hwnd )
{
	WndObMap::iterator itr = m_mapWndObs.find(hwnd);
	if (itr == m_mapWndObs.end())
	{
		return;
	}
	IObserver_MsgPrama *pWndOb = itr->second;
	m_cMsgManager.RemoveObserver(pWndOb);
	delete pWndOb;
	m_mapWndObs.erase(itr);
}
