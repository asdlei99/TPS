#if !defined(GLOBALHEADER_H)
#define GLOBALHEADER_H

#pragma once

#pragma warning(disable : 4786)
#pragma warning(disable : 4503)
#pragma warning(disable : 4800)
#pragma warning(disable : 4996)
#pragma warning(disable : 4018)

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
#include "cnccommonop.h"
#include "commoninterface.h"
#include "tpadplatconst.h"
#include "cncmsgmanager.h"
#include "UIDataMgr.h"
#include "wndshadow.h"
#include "tperrno.h"
#include "messageboxlogic.h"

#pragma comment(lib, "osplib.lib")
#pragma comment(lib, "kdvsys.lib")
#pragma comment(lib, "kdvaddrbook.lib")

//#pragma comment(lib, "nmscommon.lib")
#pragma comment(lib, LIB_NMSCOMMON)
#pragma comment(lib, "cnclib.lib")

//cns¿â 
#pragma comment(lib, "kdvlog.lib")
#pragma comment(lib, "tpmsgmgr.lib")
#pragma comment(lib, "cnmsg.lib")
#pragma comment(lib, "xmlengine.lib")
#pragma comment(lib, "tinyxml.lib")
#pragma comment(lib, "pfc.lib")

#endif
