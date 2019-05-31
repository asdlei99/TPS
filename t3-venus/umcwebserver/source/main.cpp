#include "umcglodef.h"
#include "umcwebservice.h"

CUmcWebService cWebService;    //���Ը�����Ӧҵ�������ϴ��ļ�·��

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


	//�û���ʼ����FCGIģ�� ���سɹ���������FCGI_Accept_ThreadSafeѭ��������
	//����FCGI��������Ӧ����Ϣ��Ӧ
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


