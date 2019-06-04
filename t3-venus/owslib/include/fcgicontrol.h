/*****************************************************************************
ģ����      : fcgicontrol.h
�ļ���      : fcgicontrol.h
����ļ�    : 
�ļ�ʵ�ֹ���: webservice FCGI����ģ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/11/15     1.0         ����ӡ      ����
******************************************************************************/
#ifndef FCGICONTROL_H
#define FCGICONTROL_H

#include "fcgi_stdio.h"

enum EM_FCGICONTENT_TYPE
{
	EM_FCGICONTENT_DEFAULT = 0x00,
	EM_FCGICONTENT_STRING,
	EM_FCGICONTENT_FILE
};

class CFCgiControl : public ISingleTon< CFCgiControl >
{
public:
	CFCgiControl();
	~CFCgiControl();

	static int FCGI_Accept_ThreadSafe( FCGX_ParamArray *fcgiEnv );
	static int GetInputLen( FCGX_ParamArray fcgiEnv );

	//application/x-www-form-urlencoded    �ַ�����
	//multipart/form-data                  �ļ���        Ŀǰ���õ������ַ�������
	EM_FCGICONTENT_TYPE GetContentType( FCGX_ParamArray fcgiEnv );

	static void FCGIPrintfStream( const char * format,... );

private:

};

#define PTR_FCGICONTROL CFCgiControl::GetSingletonPtr()             //FCGI����ģ����ָ��
#define PTR_FCGIPRINTF (CFCgiControl::FCGIPrintfStream)             //�������Ӧ�����ݵ�web browser����

#endif



