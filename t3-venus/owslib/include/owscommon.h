/*****************************************************************************
模块名      : COwsCommon
文件名      : owscommon.h
相关文件    : 
文件实现功能: owslib公共函数
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/08/29     1.0         刘德印      创建
******************************************************************************/
#ifndef OWSCOMMON_H
#define OWSCOMMON_H

#include "filectrl.h"

enum EmEventType
{
	emEventTypeServerSend,			//用于打印fcgi->server消息
	emEventTypeServerRecv,			//用于打印server->fcgi消息
	emEventTypeClientSend,			//用于打印fcgi->client消息
	emEventTypeClientRecv			//用于打印client->fcgi消息
};

/*****************************************************************************
	* 功能:单例基类	 
	* @remarks	该基类的子类无需进行初始化等创建操作，可直接通过GetSingletonPtr()来获取指针 
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2012/11/29     1.0         俞锦锦      创建
	2013/11/29	   2.0         刘德印      linux跨平台支持
 ******************************************************************************/
template<class T> class ISingleTon
{
	protected:
		static T* ms_pSingleton; 
	
		ISingleTon( void )
		{  
		}

	public:
		~ISingleTon( void )
		{
		   RemoveInstance();
		}
	 
		static T* GetSingletonPtr( void )
		{  
			if ( NULL == ms_pSingleton )
			{
				ms_pSingleton = new T ;
			}
			return ms_pSingleton;
		}

		static void RemoveInstance()
		{
			if(ms_pSingleton)
			{
				delete ms_pSingleton;
			}
			ms_pSingleton = NULL;
		}
};
template <class T> T * ISingleTon<T>::ms_pSingleton = NULL;


//指针清空
#define SAFE_RELEASE(x) if((x) != NULL){ delete (x); (x) = NULL; } 
#define SAFE_RELEASE_ARRAY(x) if((x) != NULL){ delete[] (x); (x) = NULL; } 

class COwsCommon
{
public: 
	static void MappingHelper( u16 wEvent, const std::string& strName );
	static std::string GetEventDescribe( u16 wEvent );

	/*=============================================================================
    函 数 名:PrtMsg
    功    能:打印某消息，如果该消息不在已设置的打印范围，则不会打印出来
    参    数:dwMsgID ：要打印的消息号，emEventType:要打印的消息类型：usm还是cns，format：要打印的消息内容
    注    意:
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
	2013/11/29  2.0     刘德印  linux跨平台支持
    =============================================================================*/
	static void PrintMsg( u32 dwMsgID, EmEventType emEventType, const char * format,... );

	/*=============================================================================
    函 数 名:PrtMsg
    功    能:打印某消息 
    参    数:format：要打印的消息内容
    注    意:
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
	2013/11/29  2.0     刘德印  linux跨平台支持
    =============================================================================*/
	static void PrintMsg( const char * format,... );

		/*=============================================================================
    函 数 名:IsPrintMsg
    功    能:判断dwMsgID是否要打印
    参    数:dwMsgID ：要打印的消息号
    注    意:如果要使用打印某一类型的消息功能，该函数一定要重写，否则，有可能打印不出来
    返 回 值:成功TRUE，失败FALSE
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
	2013/11/29  2.0     刘德印  linux跨平台支持
    =============================================================================*/
	static  BOOL32 IsPrintMsg( const u32 dwMsgID );

		/*=============================================================================
    函 数 名:IsPrintMsgBdy
    功    能:是否要打印消息体
    参    数: 
    注    意: 
    返 回 值:成功TRUE，失败FALSE
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
	2013/11/29  2.0     刘德印  linux跨平台支持
    =============================================================================*/
	static  BOOL32 IsPrintMsgBdy() ;

		/*=============================================================================
    函 数 名:GetTime
    功    能:跨平台时间获取
    参    数: 
    注    意: 
    返 回 值:格式如：strTime里存放时间的格式是YYYYMMDDTHHMMSS，日期和时间用大写字母T隔开了 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2013/11/02  1.0     刘德印  创建
    =============================================================================*/
	static const std::string GetTime();

		/*=============================================================================
    函 数 名:emType
    功    能:获取消息类型的描述
    参    数: 
    注    意: 
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
	2013/11/29  2.0     刘德印  linux跨平台支持
    =============================================================================*/
    static std::string GetEventTypeDescribe(EmEventType emType );

	/*=============================================================================
    函 数 名:GetPropertyTree/GetPropertyTreeVar
    功    能:获取json ptree/通过ptree得到对应条目value
    参    数: 
    注    意: 
    返 回 值:ptree结构/对应属性的value
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2013/11/03  1.0     刘德印  创建
    =============================================================================*/
	static ptree GetPropertyTree(const std::string& strData);
	static std::string GetPropertyTreeVar( ptree& pte, const std::string& strVal );

	/*=============================================================================
    函 数 名:GetPropertyTreeChildren
    功    能:通过ptree得到对应条目value的子ptree
    参    数: 
    注    意: 
    返 回 值:ptree结构
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2014/09/03  1.0     石城    创建
    =============================================================================*/
	static vector<ptree> GetPropertyTreeChildren( ptree& pte, const std::string& strVal );

	/*=============================================================================
    函 数 名:CreateStringJson
    功    能:生成Json字符串（带有子json串）
    参    数:StrJsonHead：json头信息，vecStrJson：子json串
    注    意: 
    返 回 值:ptree结构
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2014/09/03  1.0     石城    创建
    =============================================================================*/
	static std::string CreateStringJson( std::string StrJsonHead, vector<std::string> vecStrJson );

		/*=============================================================================
    函 数 名:GetEventValue
    功    能:通过事件字符串得到对应值
    参    数: 
    注    意: 
    返 回 值:事件值
	说    明:应用在解析json事件
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2013/11/03  1.0     刘德印  创建
    =============================================================================*/
	static u16 GetEventValue( const std::string& strEvent );

		/*=============================================================================
    函 数 名:GetIpStr
    功    能:得到IP地址
    参    数:
    注    意:
    返 回 值:IP地址
	说    明:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2013/11/03  1.0     刘德印  创建
    =============================================================================*/
	static std::string GetIpStr(unsigned int dwIPAddr);

	//文件日志打印：应用在无telnet打印窗口的调试模式下
	static BOOL FileLogInit(const std::string& strFile = "/tmp/filelog.txt");
	static BOOL FileLogPrt( char * format,... );
	static void FileLogClose();

	//崩溃异常日志：用于捕获异常崩溃生成文件   文件名以crashlog.txt为后缀
	static BOOL CrashLogFilter();
	static BOOL CrashLogInit(const std::string& strFile = "/tmp/crashlog.txt");
	static BOOL CrashLogPrt( char * format,... );
	static void CrashLogClose();

	//内存匹配   返回内存字符匹配的位置
	static u64 GetMatchPos( const u8* pContent, u64 nBufLen, u8* cpMatch, u64 nMatchLen, u64 nCurPos = 0 );

	static string StringFormat( const char * format,... );	
	


public:
	static std::vector<std::string> m_vecCLogFilter;

private:
	static u32  m_dwPrintMsgType;    //要打印的消息类型
	static u32  m_dwPrintMsgID;      //要打印的消息号
	static u32  m_dwPrintRangeMax;   //要打印的消息范围 中的最大值
	static u32  m_dwPrintRangeMin;   //要打印的消息范围 中的最小值
	static BOOL32 m_bPrintMsgBdy;    //是否要打印消息体
	static BOOL32 m_bPrintAllMsg;    //是否要打印全部消息
	static BOOL32 m_bPrintEnterMsg;  //是否要打印入口处消息
	static BOOL32 m_bPrintOutMsg;    //是否要打印出口处消息
    static u8     m_bayPrintLevel;   //当前的打印级别.   0 不打印 
	static map<u16, u8>       m_mapEventLevel;         // 消息级别

	static std::map<u16, std::string>   m_mapEventsName;		// 消息名称映射表
	static CFileCtrl m_fileLog;
	static CFileCtrl m_fileCrashLog;

	enum { MAX_LOG_FILE_LENGTH = 3*1024*1024 };
};

#define PrtMsg (COwsCommon::PrintMsg)							//打印消息接口

#define FLogInit (COwsCommon::FileLogInit)
#define FLogPrt (COwsCommon::FileLogPrt)						//输出文件日志
#define FLogClose (COwsCommon::FileLogClose)

#define CLogInit (COwsCommon::CrashLogInit)
#define CLogClose (COwsCommon::CrashLogClose)

#endif