/*****************************************************************************
模块名      : umcglodef
文件名      : umcglodef.h
相关文件    : 
文件实现功能: umcwebservice全局声明文件
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2014/08/11     1.0         石城        创建
******************************************************************************/
#ifndef _UMCGLODEF_H
#define _UMCGLODEF_H


//10-common
#include "tpmsginit.h"
#include "tpsys.h"
#include "tpstruct.h"
#include "eventoutumslogin.h"
#include "eventoutumsreg.h"
#include "eventoutumscall.h"
#include "tpcommonstruct.h"
#include "eventoutumscfg.h"
#include "tpcommontype.h"
#include "eventoutumsconftemplate.h"
#include "eventoutumsboard.h"
#include "commonapi.h"
#include "eventoutumsselview.h"


//t3-venus
#include "owslib.h"
#include "umcwebevent.h"
#include "umcwebstruct.h"
#include "umcwebdb.h"
#include "umcsessionctrl.h"
#include "umcwebcommon.h"


//APP&PORT NO define
#define AID_UMC2UMS_APP  AID_UMSUE_APP		//DCS服务器APP号
#define AID_UMS2UMC_APP  AID_CMS2UMS_APP	//DCE客户端APP号
#define UMS_LISTEN_PORT UMS_LISTIONPORT_CMS		//连接端口 UMS_LISTIONPORT_CMS
#define TELNET_PROMPT "umcwebserver1.0"		//Telnet的前缀提示符

#endif
