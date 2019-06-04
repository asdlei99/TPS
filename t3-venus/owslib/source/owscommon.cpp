#include "owslib.h"

u32  COwsCommon::m_dwPrintMsgType = 0;		//要打印的消息类型
u32  COwsCommon::m_dwPrintMsgID = 0 ;		//要打印的消息号
u32  COwsCommon::m_dwPrintRangeMax = 0;		//要打印的消息范围 中的最大值
u32  COwsCommon::m_dwPrintRangeMin = 0;		//要打印的消息范围 中的最小值 
BOOL32  COwsCommon::m_bPrintMsgBdy =  /*FALSE*/TRUE;  //是否要打印消息体
BOOL32  COwsCommon::m_bPrintAllMsg =  FALSE; 
BOOL32  COwsCommon::m_bPrintEnterMsg =  FALSE; //是否要打印入口处消息
BOOL32  COwsCommon::m_bPrintOutMsg = FALSE;  //是否要打印出口处消息
u8    COwsCommon::m_bayPrintLevel = 0;
map<u16, u8> COwsCommon::m_mapEventLevel;
std::map<u16, std::string> COwsCommon::m_mapEventsName;
std::vector<std::string> COwsCommon::m_vecCLogFilter;

CFileCtrl COwsCommon::m_fileLog;
CFileCtrl COwsCommon::m_fileCrashLog;

void COwsCommon::MappingHelper( u16 wEvent, const std::string& strName )
{
    m_mapEventsName[wEvent] = strName;
}

std::string COwsCommon::GetEventDescribe( u16 wEvent )
{  
	std::string str = "";
	map<u16, std::string>::iterator itr = m_mapEventsName.find(wEvent);
    if(itr != m_mapEventsName.end())
	{
        str = (*itr).second; 
	}
	
	return str;
}

BOOL32 COwsCommon::IsPrintMsg( const u32 dwMsgID )
{ 
	if ( m_bPrintAllMsg )
	{
		return TRUE;
	}
	
	if ( m_dwPrintMsgID == dwMsgID)
	{
		return TRUE;
	}
	
	if ( m_dwPrintRangeMin <= dwMsgID 
		&& dwMsgID <= m_dwPrintRangeMax) 
	{
		return TRUE;
	} 
	
	map<u16, u8>::iterator itr = m_mapEventLevel.find(dwMsgID);
	if(itr != m_mapEventLevel.end())
	{  	
		if ( m_bayPrintLevel >= (*itr).second )
		{
			return TRUE;
		} 
	}  
	//如果dwMsgID 属于要打印的类型，则返回TRUE； 该部分需要由外部重写实现
	return FALSE;
}

BOOL32 COwsCommon::IsPrintMsgBdy() 
{
	return m_bPrintMsgBdy;
}

const std::string COwsCommon::GetTime()
{
	std::string strTime = boost::posix_time::to_iso_string( boost::posix_time::second_clock::local_time() );  
	
	int pos = strTime.find('T');		// 这时候strTime里存放时间的格式是YYYYMMDDTHHMMSS，日期和时间用大写字母T隔开了   
	strTime.replace( pos, 1, std::string("-") );  
	strTime.replace( pos + 3, 0, std::string(":") );  
	strTime.replace( pos + 6, 0, std::string(":") );  

    return strTime;
}

void  COwsCommon::PrintMsg(u32 dwMsgID,EmEventType emEventType, const char* format,...)
{  
//     //打印消息名 
	std::string strEventType = GetEventTypeDescribe(emEventType);
	std::string strEvent = GetEventDescribe( dwMsgID );
// 
// 	//打印消息名（打印中文会出现乱码，以后解决）
// 	boost::format frt("\n---%1%\n%2%: %3%[%4%].  ");
// 	frt % GetTime().c_str();
// 	frt % strEventType.c_str();
// 	frt % strEvent.c_str();
// 	frt % dwMsgID;
// 	std::string strFrt;
// 	strFrt = frt.str();
// 	OspPrintf( TRUE, FALSE, (s8*)strFrt.c_str() ); 
	
	//打印消息名
	char szMsg[DATA_BUFFER_SIZE] = {0}; 
    snprintf(szMsg,sizeof(szMsg),"\n%s%s: %s[%d].  ", GetTime().c_str(),strEventType.c_str(), strEvent.c_str(), dwMsgID );
	
	int nMsg = strlen(szMsg);
    szMsg[nMsg] = '\0';
 	OspPrintf( TRUE, FALSE,  szMsg );  


	//打印消息体
	va_list arg_ptr;  
	char szBuffer[DATA_BUFFER_SIZE] = { 0 };
	
	va_start(arg_ptr, format);  
	vsnprintf ( szBuffer, sizeof (szBuffer) / sizeof (char),format, arg_ptr) ; 
	va_end(arg_ptr); 
	int n = strlen(szBuffer);
    szBuffer[n] = '\0';
	
	OspPrintf(TRUE,FALSE,szBuffer); 
}

void COwsCommon::PrintMsg( const char * format,... )
{
	va_list arg_ptr;  
	char szBuffer[DATA_BUFFER_SIZE] = { 0 };
	
	va_start(arg_ptr, format);  
	vsnprintf ( szBuffer, sizeof (szBuffer) / sizeof (char),format, arg_ptr) ; 
	va_end(arg_ptr); 

	int nBuffer = strlen(szBuffer);
    szBuffer[nBuffer] = '\0';
	
	OspPrintf(TRUE,FALSE,szBuffer); 
}

std::string COwsCommon::GetEventTypeDescribe(EmEventType emType )
{
	std::string str = " ";
    switch(emType) 
    {
    case emEventTypeServerSend:
		str = "[发送 SERVER 消息]";
		break;
    case emEventTypeServerRecv:
		str = "[收到 SERVER 消息]";
		break; 
	case emEventTypeClientSend:
		str = "[发送 CLIENT 消息]";
		break;
	case emEventTypeClientRecv:
		str = "[收到 CLIENT 消息]";
		break;
    default:
        ;
    }
	
    return str;
}

ptree COwsCommon::GetPropertyTree(const std::string& strData)
{
	ptree pte;
	stringstream stm(strData);
	try
	{
		read_json<ptree>( stm, pte ); 
	}
	catch (...)
	{
		PrtMsg( "%s json format error!\n", strData.c_str() );
		//assert(false);
	}

	return pte;
}

std::string COwsCommon::GetPropertyTreeVar( ptree& pte, const std::string& strVal )
{
	std::string strValue;
	try
	{
		strValue = pte.get<std::string>(strVal);
	}
	catch (...)
	{
		PrtMsg( "%s json parse error!\n", strVal.c_str() );
		//assert(false);
	}

	return strValue;
}

vector<ptree> COwsCommon::GetPropertyTreeChildren( ptree& pt, const std::string& strVal )
{
	vector<ptree> VecPtChildren;

	try
	{
		ptree image_array = pt.get_child(strVal);  // get_child得到数组对象
		
		// 遍历数组  
		BOOST_FOREACH( boost::property_tree::ptree::value_type &v, image_array )  
		{
			ptree ptChild = v.second;
			VecPtChildren.push_back(ptChild);
		}
	}
	catch (...)
	{
		PrtMsg( "%s json parse error!\n", strVal.c_str() );
		//assert(false);
	}
	
	return VecPtChildren;
}

std::string COwsCommon::CreateStringJson( std::string StrJsonHead, vector<std::string> vecStrJson )
{
	std::string strJson;
	strJson = StrJsonHead + "[";

	vector<std::string>::iterator it = vecStrJson.begin();
	for ( ; it != vecStrJson.end(); it++ )
	{
		strJson += *it + ",";
	}

	if ( vecStrJson.size() > 0 )
	{
		strJson = strJson.substr(0,strJson.length()-1);
	}
	
	strJson += "]";

	string strTail = StringFormat( ",\"count\":\"%d\"}", vecStrJson.size() );

	strJson += strTail;

	return strJson;
}

u16 COwsCommon::GetEventValue( const std::string& strEvent )
{
	u16 nKey = 0;
	std::string str = "";
	map<u16, std::string>::iterator itr = m_mapEventsName.begin();
    for( ; itr != m_mapEventsName.end(); itr++ )
	{
        str = (*itr).second; 
		if ( str == strEvent )
		{
			nKey = (*itr).first;
			return nKey;
		}
	}
	
	return nKey;
}

std::string COwsCommon::GetIpStr(unsigned int dwIPAddr)
{
	std::string strIP;
	in_addr addrIPAddr;
	addrIPAddr.s_addr = dwIPAddr;
	strIP = inet_ntoa(addrIPAddr);
	
    return strIP;
}

BOOL COwsCommon::FileLogInit(const std::string& strFile)
{
	if ( !m_fileLog.Open(strFile) )
	{
		PrtMsg( "file log init fails!\n" );
		return FALSE;
	}

	FLogPrt( "file log init success!" );

	return TRUE;
}

void COwsCommon::FileLogClose()
{
	if ( m_fileLog.Close() )
	{
		FLogPrt( "file log close success!" );
	}
}

BOOL COwsCommon::FileLogPrt( char * format,... )
{
	va_list arg_ptr;  
	char szBuffer[DATA_BUFFER_SIZE] = { 0 };
	
	va_start(arg_ptr, format);  
	vsnprintf ( szBuffer, sizeof (szBuffer) / sizeof (char),format, arg_ptr) ; 
	va_end(arg_ptr); 
	int n = strlen(szBuffer);
    szBuffer[n] = '\0';

	std::string strBufferTmp = "[";
	strBufferTmp += GetTime();
	strBufferTmp += "]	";
	strBufferTmp += szBuffer;
	strBufferTmp += "\n";

	if ( !m_fileLog.Write( (const u8*)strBufferTmp.c_str(), strBufferTmp.size(), SEEK_END, MAX_LOG_FILE_LENGTH ) )
	{
		PrtMsg( "file log no init or reaches the maximum length, write fails!\n" );
		return FALSE;
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// 功能：崩溃异常捕获
void DumpStack()
{
	void* pStrBuf[DATA_BUFFER_SIZE];
	int nBackLen = backtrace( pStrBuf, DATA_BUFFER_SIZE );
	char** ppInfos = backtrace_symbols( pStrBuf, nBackLen );

	if( !ppInfos )
	{
		//exit(1);
		return;
	}

	COwsCommon::CrashLogPrt( "========================" );
	
    char strCmd[512];
    //int nRetLen = snprintf( strCmd, sizeof(strCmd),
	//	"addr2line -ifC -e ../cgi-bin/uewebservice.fcgi" );
	int nRetLen = snprintf( strCmd, sizeof(strCmd),
		"addr2line -ifC -e /opt/dcs/dcswebinterpreter/dcewebservice.fcgi" );

	char* strPrtBuf = strCmd + nRetLen;
	size_t szCmdLen = sizeof(strCmd) - nRetLen;
	for( int nIndex = 0; nIndex < nBackLen; ++nIndex ) 
	{
		//COwsCommon::CrashLogPrt( "%s\n", ppInfos[nIndex] );    //堆栈打印   注释
		if( szCmdLen > 0 ) 
		{
            nRetLen = snprintf( strPrtBuf, szCmdLen, " %p", pStrBuf[nIndex] );
            strPrtBuf += nRetLen;
            szCmdLen -= nRetLen;
        }
    }

	COwsCommon::CrashLogPrt( "[crash dump]:" );
	COwsCommon::CrashLogPrt( "[cmd]:%s", strCmd );
	
    FILE* fp = NULL;			//读管道
    char strCmdBuf[128] = { 0 };
    if( ( fp = popen( strCmd, "r" ) ) ) 
	{
		BOOL bFind = FALSE;		//如果匹配到过滤   则对应函数下面的行号也过滤
        while( fgets( strCmdBuf, sizeof(strCmdBuf), fp ) )
		{
			if ( bFind )
			{
				bFind = FALSE;
				continue;
			}

			int nCmdLen = strlen(strCmdBuf);  
			if( strCmdBuf[nCmdLen-1] == '\n' ) //去除回车符
			{
				strCmdBuf[nCmdLen-1] = 0;
            }

			std::vector<std::string>::iterator itr = find( COwsCommon::m_vecCLogFilter.begin(), COwsCommon::m_vecCLogFilter.end(), strCmdBuf );
			if ( itr != COwsCommon::m_vecCLogFilter.end() )
			{
				bFind = TRUE;

				continue;
			}
			COwsCommon::CrashLogPrt( "[info]:%s", strCmdBuf );
		}
        pclose(fp);
    }
	COwsCommon::CrashLogPrt( "========================\n" );
    free(ppInfos);

	FLogPrt( "catch a crash dump!" );
}

void CB_SEGV_HANDLE(int s)
{
    DumpStack();
    exit(127 + s);	//一定要终端退出  否则会循环检测并输出打印
}

BOOL COwsCommon::CrashLogFilter()
{
	m_vecCLogFilter.clear();
	m_vecCLogFilter.push_back("CB_SEGV_HANDLE(int)");
	m_vecCLogFilter.push_back("DumpStack()");
	m_vecCLogFilter.push_back("??");
	m_vecCLogFilter.push_back("??:0");	
	m_vecCLogFilter.push_back("_start");

	return TRUE;
}

BOOL COwsCommon::CrashLogInit(const std::string& strFile)
{
	if ( !m_fileCrashLog.Open(strFile) )
	{
		PrtMsg( "crash log init fails!\n" );
		return FALSE;
	}

	CrashLogFilter();
	
	CrashLogPrt( "crash log init success!" );

    struct sigaction sa;
    memset( &sa, 0, sizeof(sa) );
    sa.sa_handler = CB_SEGV_HANDLE;
    sigemptyset( &sa.sa_mask );
    if( sigaction( SIGSEGV, &sa, 0 ) < 0 ) 
	{
        CrashLogPrt( "crash log sigaction error!" );
        //exit(1);
		return FALSE;
    }
	
	return TRUE;
}

BOOL COwsCommon::CrashLogPrt( char * format,... )
{
	va_list arg_ptr;  
	char szBuffer[DATA_BUFFER_SIZE] = { 0 };
	
	va_start(arg_ptr, format);  
	vsnprintf ( szBuffer, sizeof (szBuffer) / sizeof (char),format, arg_ptr) ; 
	va_end(arg_ptr); 
	int n = strlen(szBuffer);
    szBuffer[n] = '\0';

	std::string strBufferTmp = "[";
	strBufferTmp += GetTime();
	strBufferTmp += "]	";
	strBufferTmp += szBuffer;
	strBufferTmp += "\n";
	
	if ( !m_fileCrashLog.Write( (const u8*)strBufferTmp.c_str(), strBufferTmp.size(), SEEK_END, MAX_LOG_FILE_LENGTH ) )
	{
		PrtMsg( "crash log no init or reaches the maximum length, write fails!\n" );
		return FALSE;
	}
	
	return TRUE;
}

void COwsCommon::CrashLogClose()
{
	if ( m_fileCrashLog.Close() )
	{
		CrashLogPrt( "crash log close success!" );
	}
}

u64 COwsCommon::GetMatchPos( const u8* pContent, u64 nBufLen, u8* cpMatch, u64 nMatchLen, u64 nCurPos )
{
    u64 nPos = 0;
    char* cpContent;
    u64 nContentSize = nBufLen;
    cpContent = new char[nContentSize + 1];
	memset( cpContent, 0, nContentSize + 1 );
    memcpy( cpContent, pContent, nContentSize );
    if ( nCurPos >= nContentSize )
    {
		SAFE_RELEASE_ARRAY(cpContent);
        return -1;
    }
	
    char* pMove = cpContent;
    pMove += nCurPos;
    while( memcmp( pMove, cpMatch, nMatchLen ) )
    {
        pMove++;
        ++nPos;
		
        if ( nPos >= nContentSize )
        {
			SAFE_RELEASE_ARRAY(cpContent);
            return -1;
        }
        if ( nContentSize - nPos - nCurPos < nMatchLen )
        {
			SAFE_RELEASE_ARRAY(cpContent);
            return -1;
        }
    } 
	
	SAFE_RELEASE_ARRAY(cpContent);
	
    return nPos + nCurPos;
}


string COwsCommon::StringFormat( const char * format,... )
{
	va_list arg_ptr;  
	char szBuffer[DATA_BUFFER_SIZE] = { 0 };
	
	va_start(arg_ptr, format);  
	vsnprintf ( szBuffer, sizeof (szBuffer) / sizeof (char),format, arg_ptr) ; 
	va_end(arg_ptr); 
	int n = strlen(szBuffer);
    szBuffer[n] = '\0';

	return szBuffer;
}


