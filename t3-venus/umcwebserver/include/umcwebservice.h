/*****************************************************************************
模块名      : umcwebservice
文件名      : umcwebservice.h
相关文件    : 
文件实现功能: umcwebservice WebService类
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2014/08/11     1.0         石城        创建
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

	BOOL32 HandleRequestMsgEx(FCGX_ParamArray fcgiEnv);   //可以直接调用CWebServiceBase，此Ex主要是处理项目中包含处理发送上传命令到服务器的情况，如果不发送不需此函数
	
private:
	virtual void RegAllWebServiceCommand();
	BOOL InitDB();
	
private:
	
};


#endif
