#include "owslib.h"
#include "webservicebase.h"

CWebServiceBase::CWebServiceBase()
{
}

CWebServiceBase::~CWebServiceBase()
{
}

u16 CWebServiceBase::InitService()
{
	return NO_ERROR;
}

void CWebServiceBase::ReleaseService()
{
}

BOOL32 CWebServiceBase::HandleRequestMsg(FCGX_ParamArray fcgiEnv)
{
	u64 nInputLen = PTR_FCGICONTROL->GetInputLen( fcgiEnv );
	if( nInputLen == 0 )
	{
		return FALSE;
	}


	char* pInputBufUtf8 = new char[nInputLen + 1];
	memset( pInputBufUtf8, 0, nInputLen + 1 );
	int nLen = fcread( pInputBufUtf8, 1, nInputLen, stdin );
	PrtMsg( "\n-------------read len=%d-----------------\n", nLen );

	char* pInputBuf = NULL;
	utf8_to_gb2312(pInputBufUtf8, &pInputBuf);


	string strEvent;
	boost::any anyData;

	if ( EM_FCGICONTENT_FILE == PTR_FCGICONTROL->GetContentType(fcgiEnv) )
	{
		char* cpFilenameBegFlag = "filename=\"";
		char* cpFilenameEndFlag = "\"";
		
		u64 nFilenameBeg = COwsCommon::GetMatchPos( (u8*)pInputBuf, nLen, (u8*)cpFilenameBegFlag, 10 );
		u64 nFilenameEnd = COwsCommon::GetMatchPos( (u8*)pInputBuf, nLen, (u8*)cpFilenameEndFlag, 1, nFilenameBeg+10 );
		
		char arrFilename[NAME_MAX]={0};
		memcpy( arrFilename, pInputBuf+nFilenameBeg+10, nFilenameEnd-nFilenameBeg-10);
		PrtMsg( "\t---get fcgi filename = %s---\n", arrFilename );


		TFile tFile;
		tFile.pFileBuf = pInputBuf;
		tFile.nFileLen = nInputLen;

		
		strEvent = arrFilename;
		anyData = tFile;
	}
	else if ( EM_FCGICONTENT_STRING == PTR_FCGICONTROL->GetContentType(fcgiEnv) )
	{
		if( nLen == nInputLen )
		{
			std::string strPost = pInputBuf;   
			
			PrtMsg( "\t---get fcgi string = %s---\n", strPost.c_str() );
			ptree pte = COwsCommon::GetPropertyTree(strPost);

			strEvent = COwsCommon::GetPropertyTreeVar( pte, PRO_ET_EVENT );
			anyData = strPost;
		}
	}


	if ( !strEvent.empty() )
	{
		u32 uEvent = COwsCommon::GetEventValue(strEvent);
		
		if ( uEvent == 0 )
		{
			PrtMsg( "\t收到dcc消息：---event:%s 未注册---\n", strEvent.c_str() );
		}
		else
		{
			BOOL bHandle = PTR_MSGDRIVER->PostEvent( uEvent, anyData );
			if ( bHandle == FALSE )
			{
				PrtMsg( "\t收到dcc消息：---event:%s 未被任何业务类处理---\n", strEvent.c_str() );
			}
		}
	}

	SAFE_RELEASE_ARRAY(pInputBufUtf8);
	SAFE_RELEASE_ARRAY(pInputBuf);
	
	return TRUE;
}
