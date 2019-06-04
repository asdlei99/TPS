/*****************************************************************************
ģ����      : owslib
�ļ���      : owslib.h
����ļ�    : 
�ļ�ʵ�ֹ���: owslibȫ�������ļ�
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/08/27     1.0         ����ӡ      ����
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

//jsonͨ���¼�����
#define PRO_ET_EVENT			"event"		//�¼���Ϣ

#define MAX_SQL_SENTENCE_LENTH	10*1024		//SQL�����󳤶�
#define MAX_JSON_SENTENCE_LENTH	1024		//JSON�����󳤶�

/*
//��¼��Ϣ   �ο�tptype.h����չ
enum EmWEBTpLoginUmsRet
{
	tp_WEB_LoginUms_sucess = 0,
	tp_WEB_LoginUms_NameError,			//�û�������
	tp_WEB_LoginUms_PwdError,			//�������
	tp_WEB_LoginUms_EnableConnectUms,	//����������ums
	tp_WEB_LoginUms_UnknowError,		//δ֪����
};
*/

//�ļ���Ϣ
struct TFile
{
	char* pFileBuf;	//�ļ�����ָ��
	u64 nFileLen;	//�ļ���С
	
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
#include "tpmsg.h"						//tpmsg�������Ϣͨ��
#include "lanman.h"						//���뷽ʽת��

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
