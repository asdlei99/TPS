/*****************************************************************************
模块名      : umcwebstruct.h
文件名      : umcwebstruct.h
相关文件    : 
文件实现功能: umcwebservice 内部struct、json字段定义文件
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2014/08/11     1.0         石城        创建
******************************************************************************/
#ifndef _UMCWEBSTRUCT_H
#define _UMCWEBSTRUCT_H

#include "md5/md5.h"
#include "umconst.h"

/************************************************************************
* struct
************************************************************************/ 

/****************************************************************
* 用户登录信息
* MD5加密
****************************************************************/
#define MAX_CHARLENGTH		32
class CLoginRequest
{
private:
	char		name[MAX_CHARLENGTH]; //用户名
	char		password[MAX_CHARLENGTH];//密码
	CMD5Encrypt m_cMd5;
public:
	CLoginRequest()
	{
		memset(name,0,MAX_CHARLENGTH);
		memset(password,0,MAX_CHARLENGTH);
	}
	//设置和得到用户名
	char* GetName()
	{
		return name;
	}
	void  SetName(char* buf)
	{
		if(buf == NULL)return;
		memset(name,0,MAX_CHARLENGTH);
		int length = (strlen(buf) >= MAX_CHARLENGTH -1 ? MAX_CHARLENGTH - 1: strlen(buf));
		memcpy(name,buf,length);
		name[length] = '\0';
	};
	//设置和得到密码
	char* GetPassword()
	{
		return password;
	}
	//输入密码为明文
	void  SetPassword(char* buf)
	{
		
		m_cMd5.GetEncrypted(buf,password);
		password[MAX_CHARLENGTH-1]='\0';
	}
	//输入的密码已经加密了
	void SetEncryptedPassword(char* buf)
	{
		memcpy(password,buf,MAX_CHARLENGTH);
		password[MAX_CHARLENGTH-1]='\0';
	}
	void Empty()
	{
		memset(name,0,MAX_CHARLENGTH);
		memset(password,0,MAX_CHARLENGTH);
	}
};

class CUserFullInfo
{
private:
	CMD5Encrypt m_cMd5;
public:
	char		name[MAX_CHARLENGTH]; //用户名
	char		password[MAX_CHARLENGTH];//密码
	unsigned char	m_Actor;//权限
	char		fullname[MAX_CHARLENGTH];//完整用户名
	char		discription[2*MAX_CHARLENGTH];//用户描述
public:
	CUserFullInfo()
	{
		memset(name,0,MAX_CHARLENGTH);
		memset(password,0,MAX_CHARLENGTH);
		m_Actor = UM_OPERATOR;
		memset(fullname,0,MAX_CHARLENGTH);
		memset(discription,0,2*MAX_CHARLENGTH);
	}
	~CUserFullInfo(){};
	//得到用户名
	char* GetName()
	{
		name[MAX_CHARLENGTH-1] = '\0';
		return name;
	}
	//设置用户名
	void  SetName(char* buf)
	{
		if(buf == NULL)return;
		memset(name,0,MAX_CHARLENGTH);
		int length = (strlen(buf) >= MAX_CHARLENGTH -1 ? MAX_CHARLENGTH - 1: strlen(buf));
		memcpy(name,buf,length);
		name[length] = '\0';
	}
	//得到密码
	char* GetPassword()
	{
		return password;
	}
	//设置密码
	void  SetPassword(char* buf)
	{
		m_cMd5.GetEncrypted(buf,password);
		password[MAX_CHARLENGTH-1]='\0';
	}
	//已经加密的密码
	void  SetEncryptedPassword(char* buf)
	{
		memcpy(password,buf,MAX_CHARLENGTH);
		password[MAX_CHARLENGTH-1]='\0';
	}
	//得到用户完整名
	char* GetFullName()
	{
		return fullname;
	}
	//设置用户完整名
	void SetFullName(char* buf)
	{
		if(buf == NULL)return;
		memset(fullname,0,MAX_CHARLENGTH);
		int length = (strlen(buf) >= MAX_CHARLENGTH -1 ? MAX_CHARLENGTH - 1: strlen(buf));
		memcpy(fullname,buf,length);
		fullname[length] = '\0';
	}
	//得到用户描述
	char* GetDiscription()
	{
		return discription;
	}
	
	//设置用户描述
	void SetDiscription(char* buf)
	{
		if(buf == NULL)return;
		memset(discription,0, 2*MAX_CHARLENGTH);
		int length = (strlen(buf) >= 2*MAX_CHARLENGTH -1 ?  2*MAX_CHARLENGTH - 1: strlen(buf));
		memcpy(discription,buf,length);
		discription[length] = '\0';
	}
	//得到权限
	unsigned char   GetActor(){return m_Actor;}
	//设置权限
	void  SetActor(unsigned char actor){ m_Actor = actor;}
	//对象赋值
	const CUserFullInfo& operator=(const CUserFullInfo& newInfo)
	{
		if (this != &newInfo)
		{
			memset(name,0,MAX_CHARLENGTH);
			memset(password,0,MAX_CHARLENGTH);
			memset(fullname,0,MAX_CHARLENGTH);
			memset(discription,0,2*MAX_CHARLENGTH);
			memcpy(name,newInfo.name,strlen(newInfo.name));
			memcpy(password,newInfo.password,MAX_CHARLENGTH);
			memcpy(fullname,newInfo.fullname,MAX_CHARLENGTH);
			memcpy(discription,newInfo.discription,2*MAX_CHARLENGTH);
			m_Actor = newInfo.m_Actor;
		}
		return *this;
	}
	//判断用户名是否相同
	bool IsEqualName(char* newName)
	{
		if (strlen(name) != strlen(newName) || strlen(newName) == 0 )
			return FALSE;
		for (unsigned int i=0 ; i< strlen(name) ; i++)
		{
			if (name[i] != newName[i])
				return FALSE;
		}
		return TRUE;
	}	
	//判断口令是否相同
	bool IsPassWordEqual(char* newPass)
	{
		for (int i=0 ; i< MAX_CHARLENGTH-1; i++)
		{
			if (password[i] != newPass[i])
				return FALSE;
		}
		return TRUE;
	}
	//找到空的
	bool IsEmpty()
	{
		if ( strlen(password) > 16 )
		      return FALSE;
		return TRUE;
	}
	//清空
	void Empty()
	{
		memset(name,0,MAX_CHARLENGTH);
		memset(password,0,MAX_CHARLENGTH);
		memset(fullname,0,MAX_CHARLENGTH);
		memset(discription,0,2*MAX_CHARLENGTH);
		m_Actor = UM_OPERATOR;
	}	

};

#define OSP_RSP_SELF_HANDLE				0		//OSP回复由业务类自己处理锁释放

#define ADDR_TYPE_SIP					1		//地址簿类型SIP
#define ADDR_TYPE_GK					2		//地址簿类型GK

/************************************************************************
* json字段
************************************************************************/ 
//登录 用户管理业务
#define PRO_ET_USR				"usr"		//用户名
#define PRO_ET_PSW				"pwd"		//密码

/****************************************************************
* 选看信息
****************************************************************/
typedef struct tagTUMCSelViewInfo
{
	u16 m_wID;				//选看id
	EmViewEpType m_emType;		//选看类型
	
	tagTUMCSelViewInfo()
    {
		tagTUMCSelViewInfo::Clear();
	}
	
	void Clear()
	{
		m_wID = TP_INVALID_INDEX;
		m_emType = EmEpType_Ter;
	}

	BOOL IsValid()
	{
		if ( m_wID == TP_INVALID_INDEX )
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}

}TUMCSelViewInfo,*PTUMCSelViewInfo;


/****************************************************************
* 会场信息
****************************************************************/
#define UMC_MAX_SCREENNUM		3	//屏幕数量
typedef struct tagTUMCMtInfo : public TCnsInfo
{
	TUMCSelViewInfo m_tUMCSelViewInfo[UMC_MAX_SCREENNUM];			//选看信息
	
	tagTUMCMtInfo()
    {
		tagTUMCMtInfo::Clear();
	}
	
	tagTUMCMtInfo( TCnsInfo &tCnsInfo )
	{
		tagTUMCMtInfo::Clear();
		
		TCnsInfo::operator = (tCnsInfo);
	}

	tagTUMCMtInfo& operator = (const TCnsInfo &tCnsInfo)
    {
        TCnsInfo::operator = (tCnsInfo); 
        return *this;
	}
	
	void Clear()
	{
		for ( int i = 0; i < UMC_MAX_SCREENNUM; i++ )
		{
			m_tUMCSelViewInfo[i].Clear();
		}
	}
}TUMCMtInfo,*PTUMCMtInfo;

/****************************************************************
* 会议信息
****************************************************************/
typedef struct tagTConfinfo : public TTPConfInfo
{
 	vector<TUMCMtInfo>		m_vecTMtInfo;			//会场列表
	
	vector<u16>				m_vecPollList;			//会议轮询列表
	s32						m_nFlag;				//更新标识
	u16						m_wInterval;			//轮询间隔，单位秒
	EmPollStat				m_emStat;				//轮询状态

	TConfAuxMixInfo			m_tConfAuxMixInfo;		//会议讨论信息

	tagTConfinfo()
    {
		tagTConfinfo::Clear();
	}

	tagTConfinfo( TTPConfInfo &tTPConfInfo )
	{
		tagTConfinfo::Clear();

		TTPConfInfo::operator = (tTPConfInfo);
	}

	void Clear()
	{
		m_vecTMtInfo.clear();

		m_vecPollList.clear();
		m_nFlag = 0;
		m_wInterval = 20;
		m_emStat = EmPollStat_Stop;

		m_tConfAuxMixInfo.Clear();
	}

	////////////////////删除会场信息/////////////////////
	void DelTCnsInfo( u16 wEpID )
	{
		vector<TUMCMtInfo>::iterator it = m_vecTMtInfo.begin();
		for ( ; it != m_vecTMtInfo.end(); it++ )
		{
			if ( wEpID == it->m_wEpID )
			{
				m_vecTMtInfo.erase(it);
				break;
			}
		}
	}

	////////////////////更新会场信息/////////////////////
	void UpdTCnsInfo( TCnsInfo tCnsInfo )
	{
		vector<TUMCMtInfo>::iterator it = m_vecTMtInfo.begin();
		for ( ; it != m_vecTMtInfo.end(); it++ )
		{
			if ( tCnsInfo.m_wEpID == it->m_wEpID )
			{
				*it = tCnsInfo;
				break;
			}
		}
	}

	////////////////////获取主会场名称/////////////////////
	s8 *GetChairManAliars()
    {
        TUMCMtInfo* p = GetCnsInfoByID( m_wDefaultChairMan );
        if ( p != NULL )
        {
            return p->m_achRoomName;
        }
        
        return "";
    }

	//根据cns的会场ID，获取具体的cns信息
    TUMCMtInfo* GetCnsInfoByID( u16 wCnsID )
    {
        vector<TUMCMtInfo>::iterator it = m_vecTMtInfo.begin();
        for ( ; it != m_vecTMtInfo.end(); it++ )
        {
            if ( it->m_wEpID == wCnsID ) 
            {
                return &(*it);
            }
		}

		PrtMsg("\n[TConfinfo::GetCnsInfoByID] cns(id=%d) is not exist \n", wCnsID);

        return NULL;
    }

	//根据会场ID，获取具体的会场名称
	char* GetMTNameByID( u16 wID )
	{
		TUMCMtInfo* pTUMCMtInfo	= GetCnsInfoByID(wID);

		if ( pTUMCMtInfo == NULL )
		{
			return NULL;
		}

		return pTUMCMtInfo->m_achRoomName;
	}

}TConfinfo,*PTConfinfo;

#endif