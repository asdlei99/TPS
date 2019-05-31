/*****************************************************************************
模块名      : umcwebdb.h
文件名      : umcwebdb.h
相关文件    : 
文件实现功能: umcwebservice 数据库定义文件（暂未设计索引，后续优化）
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2014/08/11     1.0         石城        创建
******************************************************************************/
#ifndef _UMCWEVDB_H
#define _UMCWEVDB_H

#define DB_NAME "db_umcweb"					//数据库名称


/*****************************************************************************
表名：tb_addrbook_item（地址簿条目信息表）
字段：
/*IId：条目ID号（主键）INT UNSIGNED
/*IName：呼叫名称 varchar(32)
/*INumber：呼叫号码 varchar(16)
/*IType：地址类型，0：未知 1：sip 2：gk
/*IOnline：是否在线，1：TRUE 0：FALSE
设计者：石城
日期：2014/8/20
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
表名：tb_addrbook_group（地址簿组信息表）
字段：
/*GId：组ID号（主键） INT UNSIGNED
/*GName：组名称 varchar(32)
设计者：石城
日期：2014/8/20
******************************************************************************/
#define TB_ADDRBOOK_GROUP_NAME "tb_addrbook_group"

#define TB_ADDRBOOK_GROUP_FIELD_ID "GId"	
#define TB_ADDRBOOK_GROUP_FIELD_NAME "GName"

#define ROW_TB_ADDRBOOK_GROUP_FIELD_ID 0	
#define ROW_TB_ADDRBOOK_GROUP_FIELD_NAME 1

#define TB_ADDRBOOK_GROUP_ROOT_ID 1		//根节点id
#define TB_ADDRBOOK_GROUP_ROOT_NAME "root"		//根节点name

#define TB_ADDRBOOK_GROUP_DESC \
"CREATE TABLE IF NOT EXISTS tb_addrbook_group(\
	GId INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,\
	GName varchar(32) NOT NULL UNIQUE\
)ENGINE=InnoDB;"


/*****************************************************************************
表名：tb_addrbook_ig（地址簿条目-组关系表）
字段：
/*IId：条目ID号 INT UNSIGNED
/*GId：组ID号 INT UNSIGNED
/*主键:(IId,GId)
设计者：石城
日期：2014/8/21
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
表名：tb_addrbook_gg（地址簿组-组关系表）
字段：
/*GId：组ID号（主键）
/*GPid：上级组ID号
设计者：石城
日期：2014/8/21
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
表名：tb_addrbook_globle（全局地址簿信息表）
/*字段：
/*GId：ID号（主键）
/*GType：地址类型，1：sip 2：gk
/*GName：h323（名称）
/*GNumber：e164（号码）
/*GIp：IP
设计者：石城
日期：2014/8/21
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