// Telnetsocket.h: interface for the CTelnetSocket class.
//
//////////////////////////////////////////////////////////////////////

/*****************************************************************************
ģ����      : ץ�����ģ�飨�ͷ�����������
�ļ���      : telnetsocket.h
����ļ�    : netcapture.h
�ļ�ʵ�ֹ���: Զ�̵�¼��������������������ץ������
����        : �����
�汾        : V1.0  Copyright(C) 2012-2016 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2016/8/15      1.0					   ����
******************************************************************************/

#ifndef _TELNET_SOCKET_H_
#define _TELNET_SOCKET_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "netcapture.h"
#include  <afxsock.h>

class CTelnetSocket : public CAsyncSocket
{
public:
	CTelnetSocket();
	virtual ~CTelnetSocket();
	
	void SetLoginInfo(TLoginInfo& tInfo);	//���õ�½��Ϣ
	
	s8* GetRcvBuf();                 
	
	void ConnectRemote();       //Զ�̵�½������
	
	virtual void Close();      
	
protected:
	virtual void OnClose(int nErrorCode);           
	virtual void OnConnect(int nErrorCode);  //��½������
	virtual void OnOutOfBandData(int nErrorCode);  //Խ��
	virtual void OnReceive(int nErrorCode);   //�յ�������������Ϣ
	virtual void OnSend(int nErrorCode);      //���͸�������������Ϣ
	
	void    OnReceiveMsgFromT300e(s8* ach);          //�����Է�����T300E����Ϣ���л�Ӧ
	
protected:		
	TLoginInfo   m_tLoginInfo;
	TRcvBuf     *m_pRcvBuf;

	s8          m_nLoginNum;             //��¼����
	s8          m_nCdRamdiskNum;		 //����/ramdisk/Ŀ¼����
	s8          m_nCmdStartNum;		     //����ץ���������
};


#endif //_TELNET_SOCKET_H_
