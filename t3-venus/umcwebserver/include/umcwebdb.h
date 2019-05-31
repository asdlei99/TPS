/*****************************************************************************
ģ����      : umcwebdb.h
�ļ���      : umcwebdb.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcwebservice ���ݿⶨ���ļ�����δ��������������Ż���
����        : ʯ��
�汾        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2014/08/11     1.0         ʯ��        ����
******************************************************************************/
#ifndef _UMCWEVDB_H
#define _UMCWEVDB_H

#define DB_NAME "db_umcweb"					//���ݿ�����


/*****************************************************************************
������tb_addrbook_item����ַ����Ŀ��Ϣ��
�ֶΣ�
/*IId����ĿID�ţ�������INT UNSIGNED
/*IName���������� varchar(32)
/*INumber�����к��� varchar(16)
/*IType����ַ���ͣ�0��δ֪ 1��sip 2��gk
/*IOnline���Ƿ����ߣ�1��TRUE 0��FALSE
����ߣ�ʯ��
���ڣ�2014/8/20
******************************************************************************/
#define TB_ADDRBOOK_ITEM_NAME "tb_addrbook_item"

#define TB_ADDRBOOK_ITEM_FIELD_ID "IId"	
#define TB_ADDRBOOK_ITEM_FIELD_NAME "IName"
#define TB_ADDRBOOK_ITEM_FIELD_NUMBER "INumber"
#define TB_ADDRBOOK_ITEM_FIELD_IP "IIp"
#define TB_ADDRBOOK_ITEM_FIELD_TYPE "IType"
#define TB_ADDRBOOK_ITEM_FIELD_ONLINE "IOnline"

#define ROW_TB_ADDRBOOK_ITEM_FIELD_ID 0
#define ROW_TB_ADDRBOOK_ITEM_FIELD_NAME 1
#define ROW_TB_ADDRBOOK_ITEM_FIELD_NUMBER 2
#define ROW_TB_ADDRBOOK_ITEM_FIELD_IP 3
#define ROW_TB_ADDRBOOK_ITEM_FIELD_TYPE 4
#define ROW_TB_ADDRBOOK_ITEM_FIELD_ONLINE 5

#define TB_ADDRBOOK_ITEM_DESC \
"CREATE TABLE IF NOT EXISTS tb_addrbook_item(\
	IId INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,\
	IName varchar(32),\
	INumber varchar(16),\
	IIp varchar(32),\
	IType TINYINT NOT NULL,\
	IOnline TINYINT NOT NULL\
)ENGINE=InnoDB;"


/*****************************************************************************
������tb_addrbook_group����ַ������Ϣ��
�ֶΣ�
/*GId����ID�ţ������� INT UNSIGNED
/*GName�������� varchar(32)
����ߣ�ʯ��
���ڣ�2014/8/20
******************************************************************************/
#define TB_ADDRBOOK_GROUP_NAME "tb_addrbook_group"

#define TB_ADDRBOOK_GROUP_FIELD_ID "GId"	
#define TB_ADDRBOOK_GROUP_FIELD_NAME "GName"

#define ROW_TB_ADDRBOOK_GROUP_FIELD_ID 0	
#define ROW_TB_ADDRBOOK_GROUP_FIELD_NAME 1

#define TB_ADDRBOOK_GROUP_ROOT_ID 1		//���ڵ�id
#define TB_ADDRBOOK_GROUP_ROOT_NAME "root"		//���ڵ�name

#define TB_ADDRBOOK_GROUP_DESC \
"CREATE TABLE IF NOT EXISTS tb_addrbook_group(\
	GId INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,\
	GName varchar(32) NOT NULL UNIQUE\
)ENGINE=InnoDB;"


/*****************************************************************************
������tb_addrbook_ig����ַ����Ŀ-���ϵ��
�ֶΣ�
/*IId����ĿID�� INT UNSIGNED
/*GId����ID�� INT UNSIGNED
/*����:(IId,GId)
����ߣ�ʯ��
���ڣ�2014/8/21
******************************************************************************/
#define TB_ADDRBOOK_IG_NAME "tb_addrbook_ig"

#define TB_ADDRBOOK_IG_FIELD_IID "IId"
#define TB_ADDRBOOK_IG_FIELD_GID "GId"

#define ROW_TB_ADDRBOOK_IG_FIELD_IID 0	
#define ROW_TB_ADDRBOOK_IG_FIELD_GID 1

#define TB_ADDRBOOK_IG_DESC \
"CREATE TABLE IF NOT EXISTS tb_addrbook_ig(\
IId INT UNSIGNED NOT NULL,\
GId INT UNSIGNED NOT NULL,\
FOREIGN KEY (IId) REFERENCES tb_addrbook_item(IId) ON DELETE CASCADE,\
FOREIGN KEY (GId) REFERENCES tb_addrbook_group(GId) ON DELETE CASCADE,\
PRIMARY KEY(IId,GId)\
)ENGINE=InnoDB;"


/*****************************************************************************
������tb_addrbook_gg����ַ����-���ϵ��
�ֶΣ�
/*GId����ID�ţ�������
/*GPid���ϼ���ID��
����ߣ�ʯ��
���ڣ�2014/8/21
******************************************************************************/
#define TB_ADDRBOOK_GG_NAME "tb_addrbook_gg"

#define TB_ADDRBOOK_GG_FIELD_GID "GId"	
#define TB_ADDRBOOK_GG_FIELD_GPID "GPid"

#define ROW_TB_ADDRBOOK_GG_FIELD_GID 0	
#define ROW_TB_ADDRBOOK_GG_FIELD_GPID 1

#define TB_ADDRBOOK_GG_DESC \
"CREATE TABLE IF NOT EXISTS tb_addrbook_gg(\
GId INT UNSIGNED NOT NULL PRIMARY KEY,\
GPid INT UNSIGNED NOT NULL,\
FOREIGN KEY (GId) REFERENCES tb_addrbook_group(GId) ON DELETE CASCADE,\
FOREIGN KEY (GPid) REFERENCES tb_addrbook_group(GId) ON DELETE CASCADE\
)ENGINE=InnoDB;"


/*****************************************************************************
������tb_addrbook_globle��ȫ�ֵ�ַ����Ϣ��
/*�ֶΣ�
/*GId��ID�ţ�������
/*GType����ַ���ͣ�1��sip 2��gk
/*GName��h323�����ƣ�
/*GNumber��e164�����룩
/*GIp��IP
����ߣ�ʯ��
���ڣ�2014/8/21
******************************************************************************/
#define TB_ADDRBOOK_GLOBLE_NAME "tb_addrbook_globle"

#define TB_ADDRBOOK_GLOBLE_FIELD_ID "GId"
#define TB_ADDRBOOK_GLOBLE_FIELD_TYPE "GType"
#define TB_ADDRBOOK_GLOBLE_FIELD_NAME "GName"
#define TB_ADDRBOOK_GLOBLE_FIELD_NUMBER "GNumber"
#define TB_ADDRBOOK_GLOBLE_FIELD_IP "GIp"

#define ROW_TB_ADDRBOOK_GLOBLE_FIELD_ID 0
#define ROW_TB_ADDRBOOK_GLOBLE_FIELD_TYPE 1
#define ROW_TB_ADDRBOOK_GLOBLE_FIELD_NAME 2
#define ROW_TB_ADDRBOOK_GLOBLE_FIELD_NUMBER 3
#define ROW_TB_ADDRBOOK_GLOBLE_FIELD_IP 4

#define TB_ADDRBOOK_GLOBLE_DESC \
"CREATE TABLE IF NOT EXISTS tb_addrbook_globle(\
GId INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,\
GType TINYINT NOT NULL,\
GName varchar(64),\
GNumber varchar(64),\
GIp varchar(64)\
)ENGINE=InnoDB;"


#endif