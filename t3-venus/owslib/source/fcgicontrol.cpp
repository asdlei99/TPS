#include "owslib.h"

CFCgiControl::CFCgiControl()
{
}

CFCgiControl::~CFCgiControl()
{
}

/** 线程安全的Accept. */
int CFCgiControl::FCGI_Accept_ThreadSafe( FCGX_ParamArray *fcgiEnv )
{
	char **savedEnviron = NULL;
	char **requestEnviron = NULL;
	
	savedEnviron = environ;
	int acceptStatus = FCGI_Accept();
	requestEnviron = environ;
	environ = savedEnviron;
	
	// 传出..
	*fcgiEnv = requestEnviron;
	
	if(acceptStatus >= 0 && !FCGX_IsCGI()) {
	/*
	* requestEnviron指向FCGI_Accept分配的内存中的名-值对。
	* 可以读取，不可保留指针 -- 改为获得拷贝。
		*/
	}

	return acceptStatus;
}

int CFCgiControl::GetInputLen( FCGX_ParamArray fcgiEnv )
{
	char *pContentLen = FCGX_GetParam( "CONTENT_LENGTH", fcgiEnv );
	int inputLen = 0;
	if ( NULL != pContentLen )
	{
		inputLen = strtol( pContentLen, NULL, 10 );
	}
	return inputLen;
}

EM_FCGICONTENT_TYPE CFCgiControl::GetContentType( FCGX_ParamArray fcgiEnv )
{
	char* pContent = FCGX_GetParam( "CONTENT_TYPE", fcgiEnv );
	if ( NULL == pContent )		//判空再赋值  防止Linux下null赋值崩溃问题
	{
		PrtMsg( "get a default fcgi type is null\n" );
		FLogPrt("get a default fcgi type is null\n");
 		return EM_FCGICONTENT_DEFAULT;
	}
	else
	{
		std::string strTmp = pContent;
		if ( !strTmp.empty() )
		{
			if ( std::string::npos != strTmp.find( "multipart/form-data" ) )
			{
				return EM_FCGICONTENT_FILE;
			}
			else
			{
				return EM_FCGICONTENT_STRING;	
			}
		}
	}
}

void CFCgiControl::FCGIPrintfStream( const char * format,... )
{
	va_list arg_ptr;  
	char szBuffer[DATA_BUFFER_SIZE] = { 0 };
	
	va_start(arg_ptr, format);  
	vsnprintf ( szBuffer, sizeof (szBuffer) / sizeof (char),format, arg_ptr) ; 
	va_end(arg_ptr); 
	int n = strlen(szBuffer);
    szBuffer[n] = '\0';
	
	char* pUtf8=NULL;
	gb2312_to_utf8(szBuffer, &pUtf8);

	printf("Content-type:text/html\r\n\r\n"); 
	printf( pUtf8 );

	delete[] pUtf8;
}


