/*****************************************************************************
模块名      : webservicebase
文件名      : webservicebase.h
相关文件    : 
文件实现功能: webservice项目控制类  用于定制项目环境（是否支持fcgi websocket mysql 注册API函数等信息）
作者        : 刘德印
版本        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2014/01/15     1.0         刘德印      创建
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
