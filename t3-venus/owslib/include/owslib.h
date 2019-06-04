/*****************************************************************************
模块名      : owslib
文件名      : owslib.h
相关文件    : 
文件实现功能: owslib全局声明文件
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/08/27     1.0         刘德印      创建
******************************************************************************/
#ifndef _OWSLIB_H
#define _OWSLIB_H

//boost library
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/any.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time.hpp>   
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
using namespace boost::property_tree;
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>  
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/foreach.hpp>
#include <boost/noncopyable.hpp>


//system include
//#include <stdio.h>
#include <pthread.h>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

//crash dump
#include <csignal>
#include <unistd.h>
#include <execinfo.h>


//osp series
#include "kdvtype.h"
#include "osp.h"


//#define SERVER_IP_ADDR			"127.0.0.1"

#define DATA_BUFFER_SIZE		10*1024

#define NO_ERROR				0L
#define RET_FAILS				1L
#define _MAX_FNAME				64  /* max. length of file name component */
#define MAX_PATH				260

#define MAX_LOG_USR_NUM			128	/*MAX_USERNUM*/

//json通信事件定义
#define PRO_ET_EVENT			"event"		//事件消息

#define MAX_SQL_SENTENCE_LENTH	10*1024		//SQL语句最大长度
#define MAX_JSON_SENTENCE_LENTH	1024		//JSON语句最大长度

/*
//登录信息   参考tptype.h并扩展
enum EmWEBTpLoginUmsRet
{
	tp_WEB_LoginUms_sucess = 0,
	tp_WEB_LoginUms_NameError,			//用户名错误
	tp_WEB_LoginUms_PwdError,			//密码错误
	tp_WEB_LoginUms_EnableConnectUms,	//不能连接至ums
	tp_WEB_LoginUms_UnknowError,		//未知错误
};
*/

//文件信息
struct TFile
{
	char* pFileBuf;	//文件缓存指针
	u64 nFileLen;	//文件大小
	
	TFile()
	{
		pFileBuf = NULL;
		nFileLen = 0;
	}
};

#ifdef _LINUX_
#define tpOwsRegCommand( fun ) OspRegCommand (#fun, (void*) fun, "")
#else
#define tpOwsRegCommand( fun ) 
#endif

//10-common msg transmission
#include "tpmsg.h"						//tpmsg编解码消息通信
#include "lanman.h"						//编码方式转换

//owslib common
#include "threadctrl.h"
#include "filectrl.h"
#include "owscommon.h"
#include "fcgicontrol.h"
#include "dbstorage.h"

#include "kdvdispevent.h"
#include "commandqueue.h"

#include "ospmsgrecver.h"
#include "msgdriver.h"

#include "webservicebase.h"


#endif
