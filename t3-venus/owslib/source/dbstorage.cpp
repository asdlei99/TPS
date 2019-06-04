#include "owslib.h"
//#include <stdlib.h>

CDBStorage::CDBStorage()
{
}

CDBStorage::~CDBStorage()
{
	Release();
}

BOOL CDBStorage::Release()
{
	mysql_close(&m_mysql);
	FLogPrt( "db disconnect!" );

	return TRUE;
}

/*
//调用system，暂时用CreateTable解决
BOOL CDBStorage::DumpDBFromFile(const std::string& strDB, const std::string& strUsr, const std::string& strPsw, const std::string& strConfFile)
{
	char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
	if ( strPsw == "")
	{
		sprintf( chSQL, "mysql -u%s %s < %s%s.sql;", strUsr.c_str(), strDB.c_str(), strConfFile.c_str(), strDB.c_str() );
	}
	else
	{
		sprintf( chSQL, "mysql -u%s -p%s %s < %s%s.sql;", strUsr.c_str(), strPsw.c_str(), strDB.c_str(), strConfFile.c_str(), strDB.c_str() );
	}

	int nRet = system(chSQL);
    if ( nRet != 0 )
    {
		FLogPrt("CDBStorage::DumpDBFromFile dumpdbfromfile failed! nRet=%d(127:调用/bin/sh失败,-1:其他失败原因)", nRet);
		return FALSE;
    }
	else
	{
		FLogPrt("CDBStorage::DumpDBFromFile dumpdbfromfile success!");
	}
	
	return TRUE;
}
*/

BOOL CDBStorage::CreateDB(const std::string strDB)
{
	std::string strSQL = "IF OBJECT_ID('";
	strSQL += strDB;
	strSQL += "') IS NULL CREATE DATABASE ";
	strSQL += strDB;
	strSQL += 59;
    if ( !ExecuteDML( strSQL ) )
    {
		FLogPrt("CDBStorage::CreateTable failed! strSQL:%s error=%s\n", strSQL.c_str(), mysql_error(&m_mysql));
		return FALSE;
    }

	return TRUE;
}

BOOL CDBStorage::DeleteDB(const std::string strDB)
{
	std::string strSQL = "IF OBJECT_ID('";
	strSQL += strDB;
	strSQL += "') IS NOT NULL DROP DATABASE ";
	strSQL += strDB;
	strSQL += 59;
    if ( !ExecuteDML( strSQL ) )
    {
		FLogPrt("CDBStorage::CreateTable failed! strSQL:%s error=%s\n", strSQL.c_str(), mysql_error(&m_mysql));
		return FALSE;
    }

	return TRUE;
}

BOOL CDBStorage::CreateTable(const std::string strSQL)
{
    if ( !ExecuteDML( strSQL ) )
    {
		FLogPrt("CDBStorage::CreateTable failed! strSQL:%s error=%s\n", strSQL.c_str(), mysql_error(&m_mysql));
		return FALSE;
    }

	return TRUE;
}

BOOL CDBStorage::DeleteTable(const std::string strTable)
{
	char chSQL[MAX_SQL_SENTENCE_LENTH] = {0};
	sprintf( chSQL, "DROP TABLE IF EXISTS `%s`;", strTable.c_str() );

    if ( !ExecuteDML( chSQL ) )
    {
		FLogPrt("CDBStorage::DeleteTable failed! strSQL:%s error=%s\n", chSQL, mysql_error(&m_mysql));
		return FALSE;
    }

	return TRUE;
}

BOOL CDBStorage::ClearTableData(const std::string strTable)
{
	std::string strSQL = "IF OBJECT_ID('";
	strSQL += strTable;
	strSQL += "') IS NOT NULL DELETE FROM ";
	strSQL += strTable;
	strSQL += 59;
    if ( !ExecuteDML( strSQL ) )
    {
		return FALSE;
    }

	return TRUE;
}

BOOL CDBStorage::Connect(const std::string strDatabase, const std::string strIP, 
		 const std::string strUsr, const std::string strPsw,  int nPort )
{
	if ( NULL == mysql_init(&m_mysql) )
	{
		FLogPrt( "DB Storage Init Fails!" );
		return FALSE;
	}

	
	if ( NULL == mysql_real_connect( &m_mysql, strIP.c_str(), strUsr.c_str(), strPsw.c_str(), strDatabase.c_str(), nPort, NULL, 0 ) )
	{
		FLogPrt( "Failed to connect to database:Error:%s",mysql_error(&m_mysql) );
		return FALSE;
	}

// 	char value = 1;
// 	if ( mysql_options(&m_mysql, MYSQL_OPT_RECONNECT, (char *)&value) != 0 )
// 	{
// 		FLogPrt( "MYSQL_OPT_RECONNECT SET Fails!" );
// 		return FALSE;
// 	}

	mysql_query( &m_mysql, "set names utf8" );
	mysql_set_character_set(&m_mysql, "utf8");	//设置字符编码utf8格式

	m_strDatabase = strDatabase;
	FLogPrt( "db connect success!" );

	return TRUE;
}

BOOL CDBStorage::ExecuteDML(const std::string strSQL)
{
	PrtMsg( "%s", strSQL.c_str() );
	
	if ( mysql_ping(&m_mysql) != 0 )
	{
		if ( NULL == mysql_real_connect( &m_mysql, DB_IP_ADDR, DB_USR_NAME, DB_USR_PSW, m_strDatabase.c_str(), DB_IP_PORT, NULL, 0 ) )
		{
			FLogPrt( "mysql_ping failed , Failed to reconnect to database:Error:%s",mysql_error(&m_mysql) );
			return FALSE;
		}
		
		FLogPrt( "mysql_ping failed , succeed to reconnect to database" );
	}

	char* pSqlUtf8=NULL;
	gb2312_to_utf8((char*)strSQL.c_str(), &pSqlUtf8);

    int nRet = mysql_query(&m_mysql, pSqlUtf8);
	delete[] pSqlUtf8;

	if ( nRet != 0 )
	{
		string strError = mysql_error(&m_mysql);
		PrtMsg( "DB Storage Query Fails!, sql=%s, error=%s\n", strSQL.c_str(), strError.c_str() );

		return FALSE;
	}

	return TRUE;
}

BOOL CDBStorage::ExecuteDQL(const char *pStrSQL, std::vector<ROW> &vecRes)
{
	PrtMsg( "%s", pStrSQL );
	
	if ( mysql_ping(&m_mysql) != 0 )
	{
		if ( NULL == mysql_real_connect( &m_mysql, DB_IP_ADDR, DB_USR_NAME, DB_USR_PSW, m_strDatabase.c_str(), DB_IP_PORT, NULL, 0 ) )
		{
			FLogPrt( "mysql_ping failed , Failed to reconnect to database:Error:%s",mysql_error(&m_mysql) );
			return FALSE;
		}
		
		FLogPrt( "mysql_ping failed , succeed to reconnect to database" );
	}
	
	vecRes.clear();

	char* pSqlUtf8=NULL;
	gb2312_to_utf8((char*)pStrSQL, &pSqlUtf8);


    int nRet = mysql_query(&m_mysql, pSqlUtf8);

	delete[] pSqlUtf8;
	if ( nRet != 0 )
	{
		string strError = mysql_error(&m_mysql);
		PrtMsg( "DB Storage Query Fails!, sql=%s, error=%s\n", pStrSQL, strError.c_str() );

		return FALSE;
	}

	MYSQL_RES* pMYSQL_RES = NULL;
    pMYSQL_RES = mysql_store_result(&m_mysql);
	if ( pMYSQL_RES )
	{
		MYSQL_ROW row = NULL;
		while( row = mysql_fetch_row(pMYSQL_RES) )
		{
			ROW rowRes;
			int nCol = mysql_num_fields(pMYSQL_RES);
			for ( int i = 0; i < nCol; i++ )
			{
				char* pSqlGb2312 = NULL;
				utf8_to_gb2312(row[i], &pSqlGb2312);
				rowRes.push_back(pSqlGb2312);
				delete[] pSqlGb2312;
			}

			vecRes.push_back(rowRes);
		}
		mysql_free_result(pMYSQL_RES);
	}	
    
	return TRUE;
}

int CDBStorage::GetCount(const std::string strSQL)
{
	int nRowCount = 0;

	if ( ExecuteDML( strSQL ) )
	{
		MYSQL_RES* resSql = NULL;
		resSql = mysql_store_result(&m_mysql);
		nRowCount = mysql_num_rows(resSql);
	}

	return nRowCount;
}

BOOL CDBStorage::FindValue( const std::string& strTable, const std::string& strColName, const std::string& strFind )
{
    MYSQL_RES* resSql = NULL;
    MYSQL_FIELD* field = NULL;
	
    string sql = "SELECT ";
	sql += strColName.c_str();
	sql += " FROM ";
	sql += strTable.c_str();
 	sql += 59;
    if ( !ExecuteDML( sql ) )
    {
		return FALSE;
    }
    resSql = mysql_store_result(&m_mysql);
	
    int nFieldCount = mysql_num_fields(resSql);
	
    for( int i = 0; i < nFieldCount; i++ )
    {
		field = mysql_fetch_field_direct( resSql, i );
		
		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(resSql);
		while( NULL != row )
		{
			if ( 0 == strcmp( row[0], strFind.c_str() ) )
			{
				return TRUE;
			}
			
			row = mysql_fetch_row(resSql);
		}
    }

	return FALSE;
}


// boost::any CDBStorage::GetColValues( const std::string& strTable, EM_DB_DATA_TYPE emDataTy, const std::string& strColName )
// {
// 	std::vector<boost::any> vecTableData;	//普通表中数据集合
// 
//     MYSQL_RES* resSql = NULL;
//     MYSQL_FIELD* field = NULL;
// 
// 	std::string sql = "SELECT ";
//  	sql += strColName.c_str();
// 	sql += " FROM ";
//  	sql += strTable.c_str();
//  	sql += 59;
//     if ( !ExecuteDML( sql ) )
//     {
// 		return vecTableData;
//     }
// 
//     resSql = mysql_store_result(&m_mysql);
// 	
//     int nFieldCount = mysql_num_fields(resSql);
// 	field = mysql_fetch_field_direct( resSql, 0/*i*/ );
// 
// 	MYSQL_ROW row = NULL;
// 	row = mysql_fetch_row(resSql);
// 	while( NULL != row )
// 	{
// 		if( em_Data_UsrInfo == emDataTy )
// 		{
// 			CUserFullInfo tUsrInfo;
// 			tUsrInfo.SetName(row[0]);
// 			tUsrInfo.SetPassword(row[1]);
// 			vecTableData.push_back(tUsrInfo);						
// 		}
// 		else if ( em_DATA_Addrbook == emDataTy )
// 		{
// 			TADDRENTRYINFOEX tAddrEx;
// 			tAddrEx.dwID = boost::lexical_cast<u32>(row[0]);
// 			strncpy( tAddrEx.chName, row[1], strlen(row[1]) );
//  			tAddrEx.bIsFolder = boost::lexical_cast<bool>(row[2]);
// 			strncpy( tAddrEx.chEno, row[3], strlen(row[3]) );
//  			tAddrEx.bSip = boost::lexical_cast<bool>(row[4]);
//  			tAddrEx.dwPid = boost::lexical_cast<u32>(row[5]);
//  			vecTableData.push_back(tAddrEx);
// 		}
// 		else
// 		{
// 			vecTableData.push_back(row[0]);
// 		}
// 
// 		row = mysql_fetch_row(resSql);
// 	}
// 
// 	return vecTableData;
// }
