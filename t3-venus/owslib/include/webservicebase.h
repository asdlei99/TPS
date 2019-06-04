/*****************************************************************************
ģ����      : webservicebase
�ļ���      : webservicebase.h
����ļ�    : 
�ļ�ʵ�ֹ���: webservice��Ŀ������  ���ڶ�����Ŀ�������Ƿ�֧��fcgi websocket mysql ע��API��������Ϣ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2014/01/15     1.0         ����ӡ      ����
******************************************************************************/
#ifndef _WEBSERVICEBASE_H
#define _WEBSERVICEBASE_H

class CWebServiceBase
{
public:
	virtual void RegAllWebServiceCommand() = 0;
	BOOL32 HandleRequestMsg(FCGX_ParamArray fcgiEnv);

protected:
	CWebServiceBase();
	virtual ~CWebServiceBase();

	u16 InitService();    
	
	void ReleaseService();

private:	
	std::string m_strUploadFile;

};


#endif
