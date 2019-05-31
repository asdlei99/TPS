#include "umcglodef.h"
#include "umcwebservice.h"

CUmcWebService cWebService;    //可以根据相应业务设置上传文件路径

int main(int argc, char* argv[])
{
	FLogInit("/tmp/umc_flog.txt");
	CLogInit("/tmp/umc_clog.txt");

	if ( cWebService.Init() != TRUE )
	{
		FLogPrt( "webservice init fails!" );
		return NO_ERROR;
	}
	else
	{
		FLogPrt( "webservice init success!" );
	}


	//用户初始加载FCGI模块 加载成功后将阻塞在FCGI_Accept_ThreadSafe循环请求中
	//采用FCGI处理请求应答消息响应
	FCGX_ParamArray fcgiEnv = NULL;
	while ( PTR_FCGICONTROL->FCGI_Accept_ThreadSafe( &fcgiEnv ) >= 0 )
	{
		cWebService.HandleRequestMsgEx(fcgiEnv);
	}

	cWebService.Release();

	FLogClose();
	CLogClose();
 
	return NO_ERROR;
}


