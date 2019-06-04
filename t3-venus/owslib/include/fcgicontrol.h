/*****************************************************************************
模块名      : fcgicontrol.h
文件名      : fcgicontrol.h
相关文件    : 
文件实现功能: webservice FCGI控制模块
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/11/15     1.0         刘德印      创建
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

	//application/x-www-form-urlencoded    字符串流
	//multipart/form-data                  文件流        目前仅用到此两种发送类型
	EM_FCGICONTENT_TYPE GetContentType( FCGX_ParamArray fcgiEnv );

	static void FCGIPrintfStream( const char * format,... );

private:

};

#define PTR_FCGICONTROL CFCgiControl::GetSingletonPtr()             //FCGI控制模块类指针
#define PTR_FCGIPRINTF (CFCgiControl::FCGIPrintfStream)             //输出请求应答数据到web browser内容

#endif



