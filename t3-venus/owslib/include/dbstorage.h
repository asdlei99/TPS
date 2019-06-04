/*****************************************************************************
模块名      : dbstorage.h
文件名      : dbstorage.h
相关文件    : 
文件实现功能: webservice DB Storage存取模块
作者        : 刘德印
备注		：数据库及表结构：数据库管理员脚本生成
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/10/11     1.0         刘德印      创建
******************************************************************************/
#ifndef DBSTORAGE_H
#define DBSTORAGE_H

#include "mysql.h"

#define DB_IP_ADDR "127.0.0.1"
#define DB_USR_NAME "root"
#define DB_USR_PSW ""
#define DB_IP_PORT 3306
#define DB_CONF_FILE "/opt/"

typedef std::vector<string> ROW;

class CDBStorage : public ISingleTon< CDBStorage >
{
public:
	CDBStorage();
	~CDBStorage();

	BOOL Release();

	/*********************************************************
	//从文件还原数据库
	//PARAM: 数据库名
	//SQL INFO EG: mysql -uroot -p db_dcweb < /opt/db_dcweb.sql
	**********************************************************/
	//调用system，暂时用CreateTable解决
	//BOOL DumpDBFromFile(const std::string& strDB, const std::string& strUsr = DB_USR_NAME, const std::string& strPsw = DB_USR_PSW,
	//	const std::string& strConfFile = DB_CONF_FILE);

	//创建数据库 PARAM: 数据库名
	BOOL CreateDB(const std::string strDB);

	//删除数据库 PARAM: 数据库名
	BOOL DeleteDB(const std::string strDB);

	//创建数据库表 SQL INFO EG: CREATE TABLE ...
	BOOL CreateTable(const std::string strSQL);

	//删除数据库表 PARAM: 表名
	BOOL DeleteTable(const std::string strTable);

	//清空指定表数据 PARAM: 表名
	BOOL ClearTableData(const std::string strTable);

	BOOL Connect(const std::string strDatabase, const std::string strIP = DB_IP_ADDR, 
		 const std::string strUsr = DB_USR_NAME, const std::string strPsw = DB_USR_PSW, int nPort = DB_IP_PORT );

	//执行增加、删除、修改SQL操作
	BOOL ExecuteDML(const std::string strSQL);

	//执行查询SQL操作
	BOOL ExecuteDQL(const char *pStrSQL, std::vector<ROW> &vecRes);

	int GetCount(const std::string strSQL);

	//找到某列是否存在
	BOOL FindValue( const std::string& strTable, const std::string& strColName, const std::string& strFind );

	//获取表内指定列的值集
	//boost::any GetColValues( const std::string& strTable, EM_DB_DATA_TYPE emDataTy = em_Data_Common, const std::string& strColName = "*" );

	int GetInsertID()
	{
		return m_mysql.insert_id;
	}

	MYSQL GetMySQL(){return m_mysql;};
	
private:
	MYSQL m_mysql;
	string m_strDatabase;
};

#define PTR_DBSTORAGE CDBStorage::GetSingletonPtr()             //DB Storage存取模块类指针

	
#endif