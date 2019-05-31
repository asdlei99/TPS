#include "StdAfx.h"
#include "cncmsgmanager.h"
#include "WndObserver.h"

CCncMsgManager::CCncMsgManager(void)
{
}


CCncMsgManager::~CCncMsgManager(void)
{
}

void CCncMsgManager::AddObserver(IObserver_MsgPrama* pObserver)
{
	m_cMsgManager.AddObserver(pObserver);
}


void CCncMsgManager::RemoveObserver(IObserver_MsgPrama* pObserver)
{
	m_cMsgManager.RemoveObserver(pObserver);
}

void CCncMsgManager::SendMsg(TMsgParam& tMsgParam)
{
	m_cMsgManager.SendMsg(tMsgParam);
}

void CCncMsgManager::PostMsg( TMsgParam& tMsgParam )
{
	m_cMsgManager.PostMsg(tMsgParam);
}

void CCncMsgManager::AddWindowObserver(HWND hwnd)
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

void CCncMsgManager::RemoveWindowObserver( HWND hwnd )
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
