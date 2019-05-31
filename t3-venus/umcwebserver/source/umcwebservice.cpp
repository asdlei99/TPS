#include "umcglodef.h"
#include "umcwebservice.h"
#include "umcsessionctrl.h"

CUmcWebService::CUmcWebService()
{
}

CUmcWebService::~CUmcWebService()
{
}

BOOL CUmcWebService::Init()
{
	if ( NO_ERROR != InitService() )
	{
		FLogPrt("CUmcWebService::Init initservice fails!");
		return FALSE;
	}

	if ( !InitDB() )
	{
		return FALSE;
	}

	InitTpEvent();

	//初始化创建Session  创建APP服务
	PTR_SESSION;

	//初始化CMsgDriver
	PTR_MSGDRIVER;

	RegAllWebServiceCommand();

	return TRUE;
}

void CUmcWebService::Release()
{
	ReleaseService();
	
	CUmcSessionCtrl::RemoveInstance();

	CMsgDriver::RemoveInstance();

	CDBStorage::RemoveInstance();
}

BOOL32 CUmcWebService::HandleRequestMsgEx(FCGX_ParamArray fcgiEnv)
{
	HandleRequestMsg(fcgiEnv);

	return TRUE;
}

API void help( void )
{
	OspPrintf( TRUE, FALSE, "    sayconnect:        是否连接到ums\n" );
	OspPrintf( TRUE, FALSE, "    releaselock:       释放与前台通信锁\n" );
	OspPrintf( TRUE, FALSE, "    showconfinfo:      查看会议信息\n" );
	OspPrintf( TRUE, FALSE, "    showsyscfginfo:    查看系统信息\n" );
}

API void sayconnect( void )
{
	PrtMsg("connect = %d\n", PTR_SESSION->IsConnected() );
}

API void releaselock( void )
{
	PTR_MSGDRIVER->ReleaseLock();
}

API void showconfinfo( void )
{
	CUmcConfinfoCtrl *pConfinfoCtrl = PTR_SESSION->GetUmcConfinfoCtrl();
	if ( pConfinfoCtrl == NULL )
	{
		return;
	}

	pConfinfoCtrl->ShowConfinfo();
}

API void showsyscfginfo( void )
{
	CUmcSysCfgCtrl *pSysCfgCtrl = PTR_SESSION->GetUmcSysCfgCtrl();
	if ( pSysCfgCtrl == NULL )
	{
		return;
	}
	
	pSysCfgCtrl->ShowSysCfginfo();
}

void CUmcWebService::RegAllWebServiceCommand()
{
	tpOwsRegCommand(help);
	tpOwsRegCommand(sayconnect);
	tpOwsRegCommand(releaselock);
	tpOwsRegCommand(showconfinfo);
}

BOOL CUmcWebService::InitDB()
{
	if ( PTR_DBSTORAGE->Connect(DB_NAME) )
	{
		if ( !PTR_DBSTORAGE->CreateTable(TB_ADDRBOOK_ITEM_DESC))
		{
			FLogPrt("CUmcWebService::InitDB CreateTable(%s) failed!", TB_ADDRBOOK_ITEM_NAME);
			return FALSE;
		}
 
		if ( !PTR_DBSTORAGE->CreateTable(TB_ADDRBOOK_GROUP_DESC))
		{
			FLogPrt("CUmcWebService::InitDB CreateTable(%s) failed!", TB_ADDRBOOK_GROUP_NAME);
			return FALSE;
		}
		else
		{
			char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
			sprintf( chSQL, "select * from %s where %s=%d"
				, TB_ADDRBOOK_GROUP_NAME, TB_ADDRBOOK_GROUP_FIELD_ID, TB_ADDRBOOK_GROUP_ROOT_ID );

			if ( PTR_DBSTORAGE->GetCount(chSQL) == 0 )
			{
				char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
				sprintf( chSQL, "insert into %s(%s,%s) values(\"%d\",\"%s\");"
					, TB_ADDRBOOK_GROUP_NAME, TB_ADDRBOOK_GROUP_FIELD_ID, TB_ADDRBOOK_GROUP_FIELD_NAME
					, TB_ADDRBOOK_GROUP_ROOT_ID, TB_ADDRBOOK_GROUP_ROOT_NAME );
				BOOL bRet = PTR_DBSTORAGE->ExecuteDML(chSQL);
				if ( !bRet )
				{
					FLogPrt("CUmcWebService::InitDB Table(%s) insert root failed!", TB_ADDRBOOK_GROUP_NAME);
					return FALSE;
				}
			}
		}


		if ( !PTR_DBSTORAGE->CreateTable(TB_ADDRBOOK_IG_DESC))
		{
			FLogPrt("CUmcWebService::InitDB CreateTable(%s) failed!", TB_ADDRBOOK_IG_NAME);
			return FALSE;
		}

		if ( !PTR_DBSTORAGE->CreateTable(TB_ADDRBOOK_GG_DESC))
		{
			FLogPrt("CUmcWebService::InitDB CreateTable(%s) failed!", TB_ADDRBOOK_GG_NAME);
			return FALSE;
		}

		if ( !PTR_DBSTORAGE->DeleteTable(TB_ADDRBOOK_GLOBLE_NAME) || !PTR_DBSTORAGE->CreateTable(TB_ADDRBOOK_GLOBLE_DESC))
		{
			FLogPrt("CUmcWebService::InitDB CreateTable(%s) failed!", TB_ADDRBOOK_GLOBLE_NAME);
			return FALSE;
		}
	}
	else
	{
		FLogPrt("CUmcWebService::InitDB dbconnect failed!");
		return FALSE;
	}
 
	FLogPrt("CUmcWebService::InitDB success!");

	return TRUE;
}