/*****************************************************************************
ģ����      : umcwebstruct.h
�ļ���      : umcwebstruct.h
����ļ�    : 
�ļ�ʵ�ֹ���: umcwebservice �ڲ�struct��json�ֶζ����ļ�
����        : ʯ��
�汾        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2014/08/11     1.0         ʯ��        ����
******************************************************************************/
#ifndef _UMCWEBSTRUCT_H
#define _UMCWEBSTRUCT_H

#include "md5/md5.h"
#include "umconst.h"

/************************************************************************
* struct
************************************************************************/ 

/****************************************************************
* �û���¼��Ϣ
* MD5����
****************************************************************/
#define MAX_CHARLENGTH		32
class CLoginRequest
{
private:
	char		name[MAX_CHARLENGTH]; //�û���
	char		password[MAX_CHARLENGTH];//����
	CMD5Encrypt m_cMd5;
public:
	CLoginRequest()
	{
		memset(name,0,MAX_CHARLENGTH);
		memset(password,0,MAX_CHARLENGTH);
	}
	//���ú͵õ��û���
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
	//���ú͵õ�����
	char* GetPassword()
	{
		return password;
	}
	//��������Ϊ����
	void  SetPassword(char* buf)
	{
		
		m_cMd5.GetEncrypted(buf,password);
		password[MAX_CHARLENGTH-1]='\0';
	}
	//����������Ѿ�������
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
	char		name[MAX_CHARLENGTH]; //�û���
	char		password[MAX_CHARLENGTH];//����
	unsigned char	m_Actor;//Ȩ��
	char		fullname[MAX_CHARLENGTH];//�����û���
	char		discription[2*MAX_CHARLENGTH];//�û�����
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
	//�õ��û���
	char* GetName()
	{
		name[MAX_CHARLENGTH-1] = '\0';
		return name;
	}
	//�����û���
	void  SetName(char* buf)
	{
		if(buf == NULL)return;
		memset(name,0,MAX_CHARLENGTH);
		int length = (strlen(buf) >= MAX_CHARLENGTH -1 ? MAX_CHARLENGTH - 1: strlen(buf));
		memcpy(name,buf,length);
		name[length] = '\0';
	}
	//�õ�����
	char* GetPassword()
	{
		return password;
	}
	//��������
	void  SetPassword(char* buf)
	{
		m_cMd5.GetEncrypted(buf,password);
		password[MAX_CHARLENGTH-1]='\0';
	}
	//�Ѿ����ܵ�����
	void  SetEncryptedPassword(char* buf)
	{
		memcpy(password,buf,MAX_CHARLENGTH);
		password[MAX_CHARLENGTH-1]='\0';
	}
	//�õ��û�������
	char* GetFullName()
	{
		return fullname;
	}
	//�����û�������
	void SetFullName(char* buf)
	{
		if(buf == NULL)return;
		memset(fullname,0,MAX_CHARLENGTH);
		int length = (strlen(buf) >= MAX_CHARLENGTH -1 ? MAX_CHARLENGTH - 1: strlen(buf));
		memcpy(fullname,buf,length);
		fullname[length] = '\0';
	}
	//�õ��û�����
	char* GetDiscription()
	{
		return discription;
	}
	
	//�����û�����
	void SetDiscription(char* buf)
	{
		if(buf == NULL)return;
		memset(discription,0, 2*MAX_CHARLENGTH);
		int length = (strlen(buf) >= 2*MAX_CHARLENGTH -1 ?  2*MAX_CHARLENGTH - 1: strlen(buf));
		memcpy(discription,buf,length);
		discription[length] = '\0';
	}
	//�õ�Ȩ��
	unsigned char   GetActor(){return m_Actor;}
	//����Ȩ��
	void  SetActor(unsigned char actor){ m_Actor = actor;}
	//����ֵ
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
	//�ж��û����Ƿ���ͬ
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
	//�жϿ����Ƿ���ͬ
	bool IsPassWordEqual(char* newPass)
	{
		for (int i=0 ; i< MAX_CHARLENGTH-1; i++)
		{
			if (password[i] != newPass[i])
				return FALSE;
		}
		return TRUE;
	}
	//�ҵ��յ�
	bool IsEmpty()
	{
		if ( strlen(password) > 16 )
		      return FALSE;
		return TRUE;
	}
	//���
	void Empty()
	{
		memset(name,0,MAX_CHARLENGTH);
		memset(password,0,MAX_CHARLENGTH);
		memset(fullname,0,MAX_CHARLENGTH);
		memset(discription,0,2*MAX_CHARLENGTH);
		m_Actor = UM_OPERATOR;
	}	

};

#define OSP_RSP_SELF_HANDLE				0		//OSP�ظ���ҵ�����Լ��������ͷ�

#define ADDR_TYPE_SIP					1		//��ַ������SIP
#define ADDR_TYPE_GK					2		//��ַ������GK

/************************************************************************
* json�ֶ�
************************************************************************/ 
//��¼ �û�����ҵ��
#define PRO_ET_USR				"usr"		//�û���
#define PRO_ET_PSW				"pwd"		//����

/****************************************************************
* ѡ����Ϣ
****************************************************************/
typedef struct tagTUMCSelViewInfo
{
	u16 m_wID;				//ѡ��id
	EmViewEpType m_emType;		//ѡ������
	
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
* �᳡��Ϣ
****************************************************************/
#define UMC_MAX_SCREENNUM		3	//��Ļ����
typedef struct tagTUMCMtInfo : public TCnsInfo
{
	TUMCSelViewInfo m_tUMCSelViewInfo[UMC_MAX_SCREENNUM];			//ѡ����Ϣ
	
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
* ������Ϣ
****************************************************************/
typedef struct tagTConfinfo : public TTPConfInfo
{
 	vector<TUMCMtInfo>		m_vecTMtInfo;			//�᳡�б�
	
	vector<u16>				m_vecPollList;			//������ѯ�б�
	s32						m_nFlag;				//���±�ʶ
	u16						m_wInterval;			//��ѯ�������λ��
	EmPollStat				m_emStat;				//��ѯ״̬

	TConfAuxMixInfo			m_tConfAuxMixInfo;		//����������Ϣ

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

	////////////////////ɾ���᳡��Ϣ/////////////////////
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

	////////////////////���»᳡��Ϣ/////////////////////
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

	////////////////////��ȡ���᳡����/////////////////////
	s8 *GetChairManAliars()
    {
        TUMCMtInfo* p = GetCnsInfoByID( m_wDefaultChairMan );
        if ( p != NULL )
        {
            return p->m_achRoomName;
        }
        
        return "";
    }

	//����cns�Ļ᳡ID����ȡ�����cns��Ϣ
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

	//���ݻ᳡ID����ȡ����Ļ᳡����
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