/*****************************************************************************
ģ����      : umcglodef
�ļ���      : umcglodef.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcwebserviceȫ�������ļ�
����        : ʯ��
�汾        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2014/08/11     1.0         ʯ��        ����
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
#define AID_UMC2UMS_APP  AID_UMSUE_APP		//DCS������APP��
#define AID_UMS2UMC_APP  AID_CMS2UMS_APP	//DCE�ͻ���APP��
#define UMS_LISTEN_PORT UMS_LISTIONPORT_CMS		//���Ӷ˿� UMS_LISTIONPORT_CMS
#define TELNET_PROMPT "umcwebserver1.0"		//Telnet��ǰ׺��ʾ��

#endif
