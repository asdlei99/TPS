/*****************************************************************************
ģ����      : umcwebservice
�ļ���      : umcwebservice.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcwebservice WebService��
����        : ʯ��
�汾        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2014/08/11     1.0         ʯ��        ����
******************************************************************************/
#ifndef _UMCWEBSERVICE_H
#define _UMCWEBSERVICE_H

class CUmcWebService: public CWebServiceBase
{
public:
	CUmcWebService();
	~CUmcWebService();
	
public:
	BOOL Init();

	void Release();

	BOOL32 HandleRequestMsgEx(FCGX_ParamArray fcgiEnv);   //����ֱ�ӵ���CWebServiceBase����Ex��Ҫ�Ǵ�����Ŀ�а����������ϴ�������������������������Ͳ���˺���
	
private:
	virtual void RegAllWebServiceCommand();
	BOOL InitDB();
	
private:
	
};


#endif
