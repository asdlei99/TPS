#if !defined(GLOBALHEADER_H)
#define GLOBALHEADER_H

#pragma once

#pragma warning(disable : 4786)
#pragma warning(disable : 4503)
#pragma warning(disable : 4800)
#pragma warning(disable : 4996)

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>



#include "kdvtype.h"
#include "AppFrameHeader.h"

#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;

#include "templateClass.h"
using namespace AutoUIFactory;

#include "unicode.h"

#include "constdef.h"

#include "system.h"
#include "cncevent.h"
#include "tpadcommonop.h"
#include "commoninterface.h"
#include "tpadplatconst.h"
#include "tpadmsgmanager.h"
//#include "UIDataMgr.h"
#include "nmscommon.h"
#include "messageboxlogic.h"


#pragma comment(lib, "osplib.lib")
#pragma comment(lib, "kdvsys.lib")

#pragma comment(lib, LIB_NMSCOMMON)
#pragma comment(lib, "cnclib.lib") //包含cnclib是为了使用printctrl

//cns库 
#pragma comment(lib, "kdvlog.lib")
#pragma comment(lib, "tpmsgmgr.lib")
#pragma comment(lib, "cnmsg.lib")
#pragma comment(lib, "xmlengine.lib")
#pragma comment(lib, "tinyxml.lib")

#pragma comment (lib, "tpadlib.lib" )
#pragma comment(lib, "pfc.lib")

//wifi
#include "wlandllcommon.h"
#pragma comment(lib, "wlanapidll.lib")

//网络配置
#pragma comment(lib, "iphlpapi.lib" )
#pragma comment(lib, "SensAPI.Lib" )

//文件预览
#include "previewdllcommon.h"
#pragma comment(lib, "previewdll.lib")

//白板数据会议
#include "dllmain.h"
#pragma comment(lib, "whiteboard.lib")

#endif
