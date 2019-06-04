/*****************************************************************************
ģ����      : COwsCommon
�ļ���      : owscommon.h
����ļ�    : 
�ļ�ʵ�ֹ���: owslib��������
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/08/29     1.0         ����ӡ      ����
******************************************************************************/
#ifndef OWSCOMMON_H
#define OWSCOMMON_H

#include "filectrl.h"

enum EmEventType
{
	emEventTypeServerSend,			//���ڴ�ӡfcgi->server��Ϣ
	emEventTypeServerRecv,			//���ڴ�ӡserver->fcgi��Ϣ
	emEventTypeClientSend,			//���ڴ�ӡfcgi->client��Ϣ
	emEventTypeClientRecv			//���ڴ�ӡclient->fcgi��Ϣ
};

/*****************************************************************************
	* ����:��������	 
	* @remarks	�û��������������г�ʼ���ȴ�����������ֱ��ͨ��GetSingletonPtr()����ȡָ�� 
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2012/11/29     1.0         �����      ����
	2013/11/29	   2.0         ����ӡ      linux��ƽ̨֧��
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


//ָ�����
#define SAFE_RELEASE(x) if((x) != NULL){ delete (x); (x) = NULL; } 
#define SAFE_RELEASE_ARRAY(x) if((x) != NULL){ delete[] (x); (x) = NULL; } 

class COwsCommon
{
public: 
	static void MappingHelper( u16 wEvent, const std::string& strName );
	static std::string GetEventDescribe( u16 wEvent );

	/*=============================================================================
    �� �� ��:PrtMsg
    ��    ��:��ӡĳ��Ϣ���������Ϣ���������õĴ�ӡ��Χ���򲻻��ӡ����
    ��    ��:dwMsgID ��Ҫ��ӡ����Ϣ�ţ�emEventType:Ҫ��ӡ����Ϣ���ͣ�usm����cns��format��Ҫ��ӡ����Ϣ����
    ע    ��:
    �� �� ֵ: 
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
	2013/11/29  2.0     ����ӡ  linux��ƽ̨֧��
    =============================================================================*/
	static void PrintMsg( u32 dwMsgID, EmEventType emEventType, const char * format,... );

	/*=============================================================================
    �� �� ��:PrtMsg
    ��    ��:��ӡĳ��Ϣ 
    ��    ��:format��Ҫ��ӡ����Ϣ����
    ע    ��:
    �� �� ֵ: 
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
	2013/11/29  2.0     ����ӡ  linux��ƽ̨֧��
    =============================================================================*/
	static void PrintMsg( const char * format,... );

		/*=============================================================================
    �� �� ��:IsPrintMsg
    ��    ��:�ж�dwMsgID�Ƿ�Ҫ��ӡ
    ��    ��:dwMsgID ��Ҫ��ӡ����Ϣ��
    ע    ��:���Ҫʹ�ô�ӡĳһ���͵���Ϣ���ܣ��ú���һ��Ҫ��д�������п��ܴ�ӡ������
    �� �� ֵ:�ɹ�TRUE��ʧ��FALSE
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
	2013/11/29  2.0     ����ӡ  linux��ƽ̨֧��
    =============================================================================*/
	static  BOOL32 IsPrintMsg( const u32 dwMsgID );

		/*=============================================================================
    �� �� ��:IsPrintMsgBdy
    ��    ��:�Ƿ�Ҫ��ӡ��Ϣ��
    ��    ��: 
    ע    ��: 
    �� �� ֵ:�ɹ�TRUE��ʧ��FALSE
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
	2013/11/29  2.0     ����ӡ  linux��ƽ̨֧��
    =============================================================================*/
	static  BOOL32 IsPrintMsgBdy() ;

		/*=============================================================================
    �� �� ��:GetTime
    ��    ��:��ƽ̨ʱ���ȡ
    ��    ��: 
    ע    ��: 
    �� �� ֵ:��ʽ�磺strTime����ʱ��ĸ�ʽ��YYYYMMDDTHHMMSS�����ں�ʱ���ô�д��ĸT������ 
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/11/02  1.0     ����ӡ  ����
    =============================================================================*/
	static const std::string GetTime();

		/*=============================================================================
    �� �� ��:emType
    ��    ��:��ȡ��Ϣ���͵�����
    ��    ��: 
    ע    ��: 
    �� �� ֵ: 
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
	2013/11/29  2.0     ����ӡ  linux��ƽ̨֧��
    =============================================================================*/
    static std::string GetEventTypeDescribe(EmEventType emType );

	/*=============================================================================
    �� �� ��:GetPropertyTree/GetPropertyTreeVar
    ��    ��:��ȡjson ptree/ͨ��ptree�õ���Ӧ��Ŀvalue
    ��    ��: 
    ע    ��: 
    �� �� ֵ:ptree�ṹ/��Ӧ���Ե�value
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/11/03  1.0     ����ӡ  ����
    =============================================================================*/
	static ptree GetPropertyTree(const std::string& strData);
	static std::string GetPropertyTreeVar( ptree& pte, const std::string& strVal );

	/*=============================================================================
    �� �� ��:GetPropertyTreeChildren
    ��    ��:ͨ��ptree�õ���Ӧ��Ŀvalue����ptree
    ��    ��: 
    ע    ��: 
    �� �� ֵ:ptree�ṹ
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2014/09/03  1.0     ʯ��    ����
    =============================================================================*/
	static vector<ptree> GetPropertyTreeChildren( ptree& pte, const std::string& strVal );

	/*=============================================================================
    �� �� ��:CreateStringJson
    ��    ��:����Json�ַ�����������json����
    ��    ��:StrJsonHead��jsonͷ��Ϣ��vecStrJson����json��
    ע    ��: 
    �� �� ֵ:ptree�ṹ
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2014/09/03  1.0     ʯ��    ����
    =============================================================================*/
	static std::string CreateStringJson( std::string StrJsonHead, vector<std::string> vecStrJson );

		/*=============================================================================
    �� �� ��:GetEventValue
    ��    ��:ͨ���¼��ַ����õ���Ӧֵ
    ��    ��: 
    ע    ��: 
    �� �� ֵ:�¼�ֵ
	˵    ��:Ӧ���ڽ���json�¼�
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/11/03  1.0     ����ӡ  ����
    =============================================================================*/
	static u16 GetEventValue( const std::string& strEvent );

		/*=============================================================================
    �� �� ��:GetIpStr
    ��    ��:�õ�IP��ַ
    ��    ��:
    ע    ��:
    �� �� ֵ:IP��ַ
	˵    ��:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/11/03  1.0     ����ӡ  ����
    =============================================================================*/
	static std::string GetIpStr(unsigned int dwIPAddr);

	//�ļ���־��ӡ��Ӧ������telnet��ӡ���ڵĵ���ģʽ��
	static BOOL FileLogInit(const std::string& strFile = "/tmp/filelog.txt");
	static BOOL FileLogPrt( char * format,... );
	static void FileLogClose();

	//�����쳣��־�����ڲ����쳣���������ļ�   �ļ�����crashlog.txtΪ��׺
	static BOOL CrashLogFilter();
	static BOOL CrashLogInit(const std::string& strFile = "/tmp/crashlog.txt");
	static BOOL CrashLogPrt( char * format,... );
	static void CrashLogClose();

	//�ڴ�ƥ��   �����ڴ��ַ�ƥ���λ��
	static u64 GetMatchPos( const u8* pContent, u64 nBufLen, u8* cpMatch, u64 nMatchLen, u64 nCurPos = 0 );

	static string StringFormat( const char * format,... );	
	


public:
	static std::vector<std::string> m_vecCLogFilter;

private:
	static u32  m_dwPrintMsgType;    //Ҫ��ӡ����Ϣ����
	static u32  m_dwPrintMsgID;      //Ҫ��ӡ����Ϣ��
	static u32  m_dwPrintRangeMax;   //Ҫ��ӡ����Ϣ��Χ �е����ֵ
	static u32  m_dwPrintRangeMin;   //Ҫ��ӡ����Ϣ��Χ �е���Сֵ
	static BOOL32 m_bPrintMsgBdy;    //�Ƿ�Ҫ��ӡ��Ϣ��
	static BOOL32 m_bPrintAllMsg;    //�Ƿ�Ҫ��ӡȫ����Ϣ
	static BOOL32 m_bPrintEnterMsg;  //�Ƿ�Ҫ��ӡ��ڴ���Ϣ
	static BOOL32 m_bPrintOutMsg;    //�Ƿ�Ҫ��ӡ���ڴ���Ϣ
    static u8     m_bayPrintLevel;   //��ǰ�Ĵ�ӡ����.   0 ����ӡ 
	static map<u16, u8>       m_mapEventLevel;         // ��Ϣ����

	static std::map<u16, std::string>   m_mapEventsName;		// ��Ϣ����ӳ���
	static CFileCtrl m_fileLog;
	static CFileCtrl m_fileCrashLog;

	enum { MAX_LOG_FILE_LENGTH = 3*1024*1024 };
};

#define PrtMsg (COwsCommon::PrintMsg)							//��ӡ��Ϣ�ӿ�

#define FLogInit (COwsCommon::FileLogInit)
#define FLogPrt (COwsCommon::FileLogPrt)						//����ļ���־
#define FLogClose (COwsCommon::FileLogClose)

#define CLogInit (COwsCommon::CrashLogInit)
#define CLogClose (COwsCommon::CrashLogClose)

#endif