/*****************************************************************************
ģ����      : dbstorage.h
�ļ���      : dbstorage.h
����ļ�    : 
�ļ�ʵ�ֹ���: webservice DB Storage��ȡģ��
����        : ����ӡ
��ע		�����ݿ⼰��ṹ�����ݿ����Ա�ű�����
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/10/11     1.0         ����ӡ      ����
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
	//���ļ���ԭ���ݿ�
	//PARAM: ���ݿ���
	//SQL INFO EG: mysql -uroot -p db_dcweb < /opt/db_dcweb.sql
	**********************************************************/
	//����system����ʱ��CreateTable���
	//BOOL DumpDBFromFile(const std::string& strDB, const std::string& strUsr = DB_USR_NAME, const std::string& strPsw = DB_USR_PSW,
	//	const std::string& strConfFile = DB_CONF_FILE);

	//�������ݿ� PARAM: ���ݿ���
	BOOL CreateDB(const std::string strDB);

	//ɾ�����ݿ� PARAM: ���ݿ���
	BOOL DeleteDB(const std::string strDB);

	//�������ݿ�� SQL INFO EG: CREATE TABLE ...
	BOOL CreateTable(const std::string strSQL);

	//ɾ�����ݿ�� PARAM: ����
	BOOL DeleteTable(const std::string strTable);

	//���ָ�������� PARAM: ����
	BOOL ClearTableData(const std::string strTable);

	BOOL Connect(const std::string strDatabase, const std::string strIP = DB_IP_ADDR, 
		 const std::string strUsr = DB_USR_NAME, const std::string strPsw = DB_USR_PSW, int nPort = DB_IP_PORT );

	//ִ�����ӡ�ɾ�����޸�SQL����
	BOOL ExecuteDML(const std::string strSQL);

	//ִ�в�ѯSQL����
	BOOL ExecuteDQL(const char *pStrSQL, std::vector<ROW> &vecRes);

	int GetCount(const std::string strSQL);

	//�ҵ�ĳ���Ƿ����
	BOOL FindValue( const std::string& strTable, const std::string& strColName, const std::string& strFind );

	//��ȡ����ָ���е�ֵ��
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

#define PTR_DBSTORAGE CDBStorage::GetSingletonPtr()             //DB Storage��ȡģ����ָ��

	
#endif