// cmsstruct.h: interface for the cmsstruct class.
//
//////////////////////////////////////////////////////////////////////
#ifndef _h_cmsstruct_h__
#define _h_cmsstruct_h__

#include "tpstruct.h"
#include "addrbook.h"
#include "cncconst.h"
#include "eventoutcnsextend.h"


//��������
enum EM_ConfType
{
	emConfMulti = 0,      //������
	emConfCascade,        //��������
	emConfP2P,            //��Ե����
	emConfOtherUms,       //��UMS���飨������UMS���ߣ�
	emConfUnKnown
};


typedef struct tagTUiCnsInfo : public TCnsInfo
{
    vector<u16>		m_vctChildMtList;	//�¼��᳡�б�

    tagTUiCnsInfo()
    {
        tagTUiCnsInfo::Clear();
    }

    tagTUiCnsInfo( TCnsInfo &tCnsInfo )
    {
        TCnsInfo::operator = (tCnsInfo);
    }

    tagTUiCnsInfo& operator = (const TCnsInfo &tCnsInfo)
    {
        TCnsInfo::operator = (tCnsInfo); 
        return *this;
    }

    void Clear()
    {
        TCnsInfo::Clear();
        m_vctChildMtList.clear();
    }
}TUiCnsInfo,*PTUiCnsInfo;




//������Ϣ
typedef struct tagCMSConf : public TTPConfInfo
{
    EmCallType         m_emConfType;//��������
    	
	TAuxMixList	            m_tAudmixList;
	//TplArray<u16>	        m_tplPollList;
    
	BOOL32		        m_bStartAudmix;//�Ƿ�������
	BOOL32		        m_bVacOn;//�Ƿ��������е���������
	TTpPollStat	        m_tPollStat;//��¼��ǰ��ѯ״̬ dyy 2015-4-20
    //BOOL32              m_bCascadeConf;//�Ƿ��Ǽ�������
    TChairConfInfo      m_tCascadeConfInfo;  //����������Ϣ
    
    TTPAlias	m_tChairName;		//��ϯ����

	u16	m_wSelViewConfID;		//��ѡ���᳡��ID ���»᳡ѡ���б�״̬ 2015-6-26 dyy

    vector<TCnsInfo>	    m_vctCnsList; //�᳡�б�

    u16  GetChairCnsID()
    {   
        if ( strlen(m_tChairName.m_abyAlias) > 0  )
        {
            return GetCnsIDByAlias( m_tChairName.m_abyAlias ) ;
        }
        return INVALID_WORD;
    }


    tagCMSConf& operator = (const TTPConfInfo &tConf)
    {
        if(this == &tConf)
         return *this;  

        TTPConfInfo::operator = (tConf); 
        return *this;
	}
	
 
	BOOL32 operator == (const tagCMSConf& tRhs)
	{	
		return TTPConfInfo::m_wConfID == tRhs.m_wConfID;
	}
	
	void Clear()
	{  
		m_emConfType = emCallType_Invalid;
		m_vctCnsList.clear();

		m_tPollStat.m_wConfID = TP_INVALID_INDEX;
		m_tPollStat.m_emStat = EmPollStat_Stop;

		m_bStartAudmix = FALSE;
		m_bVacOn = FALSE;
        //m_bCascadeConf = FALSE;
		TTPConfInfo::Clear();
        m_tCascadeConfInfo.Clear();
        ZeroMemory( &m_tChairName,sizeof(TTPAlias ) );
		m_wSelViewConfID = TP_INVALID_INDEX;
	}


	tagCMSConf()
    {      
		tagCMSConf::Clear();
	}

    tagCMSConf( TTPConfInfo &tConf)
    {
        tagCMSConf::Clear();

        TTPConfInfo::operator = (tConf);        
	}

    void SetChairInfo( TTPAlias &tChair  )
    {
	   //memcpy( &m_tChairName, &tChair,sizeof(TTPAlias) ) ;

		m_tChairName = tChair;

		m_wDefaultChairMan = GetCnsIDByAlias( m_tChairName.m_abyAlias );	 
    }
   
    void ClearCascadeInfo()
    {
        m_tCascadeConfInfo.Clear();
		m_emConfType = emCallType_Invalid;
        //m_bCascadeConf = FALSE;
    }
 
    s8 *GetSpeakerAliars()
    {
        TCnsInfo* p = GetCnsInfoByID( m_wSpeaker );
        if ( p != NULL )
        {
            return p->m_achRoomName;
        }

        return "";
    }


    s8 *GetChairManAliars()
    {
        TCnsInfo* p = GetCnsInfoByID( m_wDefaultChairMan );
        if ( p != NULL )
        {
            return p->m_achRoomName;
        }
        
        return "";
    }


    s8 *GetDualAliars()
    {
        TCnsInfo* p = GetCnsInfoByID( m_wDual );
        if ( p != NULL )
        {
            return p->m_achRoomName;
        }
        
        return "";
    }

    //����cns�Ļ᳡ID����ȡ�����cns��Ϣ
    TCnsInfo* GetCnsInfoByID( u16 wCnsID )
    {
        s32 nCont = m_vctCnsList.size();
        for ( s32 i = 0; i< nCont; i++ )
        {
            if ( m_vctCnsList.at(i).m_wEpID == wCnsID ) 
            {
                return &(m_vctCnsList.at(i));
            }
	   }
        return NULL;
    }

	//���ݻ᳡������ȡcns��Ϣ
	TCnsInfo* GetCnsInfoByAlias( s8* strAlias )
	{
		s32 nCont = m_vctCnsList.size();
		for ( s32 i = 0; i< nCont; i++ )
		{
			if ( strcmp( m_vctCnsList.at(i).m_achRoomName, strAlias) == 0 ) 
			{
				return &m_vctCnsList.at(i);
			}
		}
		return NULL;
	}

    //��ȡ����cns��Ϣ
    TCnsInfo* GetLocalCnsInfo( TTPCnsInfo& tLocalInfo )
    {
        s32 nCont = m_vctCnsList.size();
        for ( s32 i = 0; i< nCont; i++ )
        {
            if ( strcmp( m_vctCnsList.at(i).m_achRoomName, tLocalInfo.m_achRoomName) == 0 ) 
            {
                return &m_vctCnsList.at(i);
            }
            else if ( strcmp(m_vctCnsList.at(i).m_achRoomName, tLocalInfo.m_achE164) == 0 )
            {
                return &m_vctCnsList.at(i);
            }
        }
        return NULL;
    }

   
	//����cns�Ļ᳡ID���������ڻ᳡�б�����к�
	s32 GetCnsIndexFrmCnsLst( u16 wCnsID )
	{
       s32 nCont = m_vctCnsList.size();
	   for ( s32 i = 0; i< nCont; i++ )
	   {
		   if ( m_vctCnsList.at(i).m_wEpID == wCnsID) 
		   {
			   return i;
		   }
	   }

	   return -1;
	}


    //����cns������ȡcns��ID
    u16 GetCnsIDByAlias( s8* strAlias )
    {
        s32 nCont = m_vctCnsList.size();
        for ( s32 i = 0; i< nCont; i++ )
        {
            if ( strcmp( m_vctCnsList.at(i).m_achRoomName, strAlias) == 0 ) 
            {
                return m_vctCnsList.at(i).m_wEpID;
            }
	   }
        
        return INVALID_WORD;
    }
 

	BOOL32 IsCnsInConf( s8* achRoomName )
	{
		for ( int i = 0; i < m_vctCnsList.size(); i++ )
		{
			if ( strcmp( achRoomName, m_vctCnsList.at(i).m_achRoomName ) == 0 )
			{
				if ( m_vctCnsList.at(i).m_bOnline )
				{
					return TRUE;
				}
				else
				{
					return FALSE;
				}
			}
		}
		return FALSE;
	}
	
	BOOL32 IsStartAudMix()
	{
		return m_bStartAudmix;
	}

	BOOL32 IsVacOn()
	{
		return m_bVacOn;
	}
}TCMSConf,*PTCMSConf;



//����Ϣ
typedef struct tagScreenInfo
{
	u8  byScreenID;
	s8  achCnsName[TP_MAX_ALIAS_LEN+1];
	EmTPPosStatus  emScreenState;
	EMPosPic emPosPic;    

	tagScreenInfo()
	{
		clear();
	}
	void clear()
	{
		byScreenID = 0;		
		ZeroMemory( achCnsName, sizeof(achCnsName) );
		emScreenState = emPosInAcitve;
		emPosPic = emPic_Invalid;
	}
} TScreenInfo, *PTScreenInfo;
 

//��ϯ��Ϣ
typedef struct tagSeatInfo{
	u8 bySeatID;              
	BOOL32 bSpokesMan;
	
	tagSeatInfo()
	{
          bySeatID = 0;
          bSpokesMan = FALSE;
	}
} TSeatInfo, *PTSeatInfo;



 //�����еĻ᳡״̬ 
enum EM_CnsState{
    emCnsStateMute = 0x1,         //����  �������Ƶĵ�һλ��0 ��ʾ��������1��ʾ����
    emCnsStateSilence = 0x2,      //  �����������Ƶĵڶ�λ��0 ��ʾ�Ǿ�����1��ʾ����
    emCnsStateDbFolw = 0x4,     // ˫�� ,   �����Ƶĵ���λ��0 ��ʾ�� ˫�� ��1��ʾ ˫�� 
};

//RoomInfo : CNS
typedef struct tagTCnsInfoEx :public TCnsInfo
{
    DWORD dwIndex;    //��commeninterface���У��ýṹ��Ĵ洢���
    BOOL32 bMute;       //�Ƿ����� 
    BOOL32 bSilence;   // �Ƿ���
    BOOL32 bDbFlow;  //�Ƿ�˫�� 
   
    BOOL32 operator ==( tagTCnsInfoEx & cnsInfo )
    {   
        BOOL32 re = FALSE;
        if ( this->dwIndex == cnsInfo.dwIndex && 
               (TCnsInfo::operator == (cnsInfo) ) )
        {
            re = TRUE;
        }
        return re;
    }


    tagTCnsInfoEx()
    {
        TCnsInfo::Clear();
       dwIndex = 0;
       bMute = FALSE;
       bSilence = FALSE;
       bDbFlow = FALSE;
    }

}TCnsInfoEx, *PTCnsInfoEx;


typedef struct tagTPAddrInfo
{
	u32  dwEntryIdx;                               // ��Ŀ����
	u32  dwInGroupIdx;                             // �������� 
	s8   achEntryName[TP_MAX_ALIAS_LEN_CNC+1];
	s8   achE164[TP_MAX_ALIAS_LEN_CNC+1];
    s8   achIp[TP_MAX_ALIAS_LEN_CNC+1];
	u8   byTerType;                                // �ն�����:0�����ն� 1����ն� 2��ͨ�ն�
    BOOL              bOnLine;                     // �Ƿ�����
	EmTPEndpointType  m_emEndpointType;		       // ��ַ����

	tagTPAddrInfo()
	{ 
		SetNull();
	}

	BOOL32 operator ==( const tagTPAddrInfo & tInfo )
    {   
		if ( strcmp( achEntryName, tInfo.achEntryName ) == 0 && dwEntryIdx == tInfo.dwEntryIdx &&  dwInGroupIdx == tInfo.dwInGroupIdx
            && byTerType == tInfo.byTerType )
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
    }

	void SetNull()
	{
		dwEntryIdx = INVALID_INDEX;
		dwInGroupIdx = INVALID_INDEX;
		memset( achEntryName, 0, sizeof(achEntryName) );
		memset( achE164, 0, sizeof(achE164) );
        memset( achIp, 0, sizeof(achIp) );  
		byTerType = 0;
        bOnLine = FALSE;
		m_emEndpointType = emTPEndpointTypeUnknown;
	}

	BOOL32 IsNull()
	{
		if ( dwEntryIdx == INVALID_INDEX )
		{
			return TRUE;
		}
		return FALSE;
	}
}TAddrInfo;

typedef struct tagTPGroupInfo
{
	u32 dwGroupIdx;
	u32 dwInGroupIdx;                              // �������� 
	s8  achGroupName[TP_MAX_ALIAS_LEN_CNC+1];          // ����
	s32 nEntryNum;                                 // ��Ŀ����
	u32 adwEntryIdx[MAXNUM_ENTRY_TABLE];	       // ����ն�����
	s32 nDownGroupNum;                             // �¼������
	tagTPGroupInfo()
	{ 
		SetNull();
	}

	BOOL operator ==( const tagTPGroupInfo & tInfo )
	{
		if ( strcmp( achGroupName, tInfo.achGroupName ) == 0 && dwGroupIdx == tInfo.dwGroupIdx )
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	void SetNull()
	{
		dwGroupIdx = INVALID_INDEX;
		dwInGroupIdx = INVALID_INDEX;
		memset( achGroupName, 0, sizeof(achGroupName) );
		nEntryNum = 0;
		memset( adwEntryIdx, 0, sizeof(adwEntryIdx) );
		nDownGroupNum = 0;
	}
	BOOL32 IsNull()
	{
		if ( dwGroupIdx == INVALID_INDEX )
		{
			return TRUE;
		}
		return FALSE;
	}
}TGroupInfo;

enum EM_ItemType
{
	emEntryItem = 0,
	emGroupItem,
};

typedef struct tagAddrItem
{
	EM_ItemType emItemType;
	TAddrInfo   tAddrInfo;
	TGroupInfo  tGroupInfo;
	//s8     achNameLetter[TP_MAX_ALIAS_LEN_CNC+1];
	CString     strNameLetter;

	tagAddrItem()
	{ 
		emItemType = emEntryItem;
        strNameLetter.Empty();
        //memset(achNameLetter, 0, sizeof(achNameLetter));
	}

	BOOL operator ==( const tagAddrItem & tItem )
    {
		if ( emItemType == tItem.emItemType )
		{
			if ( emItemType == emEntryItem )
			{
				return tAddrInfo == tItem.tAddrInfo;
			}
			else
			{
				return tGroupInfo == tItem.tGroupInfo;
			}
		}
		else
		{
			return FALSE;
		}
	}

	BOOL32 IsNull()
	{
		if ( emItemType == emEntryItem )
		{
			return tAddrInfo.IsNull();
		}
		else
		{
			return tGroupInfo.IsNull();
		}
	}

	void SetNull()
	{
		emItemType = emEntryItem;
		tAddrInfo.SetNull();
		tGroupInfo.SetNull();
		strNameLetter.Empty();
	}

	BOOL IsSameName( tagAddrItem& tItem )
	{
		if ( emItemType == tItem.emItemType )
		{
			if ( emItemType == emEntryItem )
			{
				//��Ŀ���ƺ�E164�ź�IPȫ��һ�������
				if ( strcmp( tAddrInfo.achEntryName, tItem.tAddrInfo.achEntryName ) == 0
					&& strcmp( tAddrInfo.achE164, tItem.tAddrInfo.achE164 ) == 0
                    && strcmp( tAddrInfo.achIp, tItem.tAddrInfo.achIp ) == 0 )
				{
					return TRUE;
                }
				else
				{
					return FALSE;
				}		
			}
			else
			{
				return strcmp( tGroupInfo.achGroupName, tItem.tGroupInfo.achGroupName ) == 0;
			}
		}
		else
		{
			return FALSE;
		}
	}
	
}TAddrItem;


enum EM_AddrShowState
{
    emShowAllAddr = 0,
    emShowGroup,
    emShowOnline,
    emShowOffline,
}; 

typedef struct tagConfCallEpAddrList 
{
    u16 m_wConfID;
    TEpAddrList m_tEpAdrLst;
    tagConfCallEpAddrList()
    { 
        m_wConfID = INVALID_WORD;
    }

    VOID Clear()
    {
        m_wConfID = INVALID_WORD;
        ZeroMemory( &m_tEpAdrLst, sizeof(TEpAddrList));
    }

} TConfCallEpAddrList;


//����ǽ��Ϣ
typedef struct tagCmsTvwInfo: public TTPHduRegInfo
{  
    BOOL bCodeStream; 

    tagCmsTvwInfo():TTPHduRegInfo()
    { 
       bCodeStream = TRUE;
    }

    void ClearCnsInfo()
    { 
        ZeroMemory( m_achAlias, sizeof(m_achAlias) ) ;
        
    }

    u16 SetCnsInfo(const s8 *pCnsAliars  )
    {
        if ( pCnsAliars == NULL )
        {
            return ERR_CMS_CNS_ALIARS_EMPTY;
        }
       
        _snprintf( m_achAlias, sizeof(m_achAlias), "%s",pCnsAliars );  
        return NO_ERROR; 
    }

    tagCmsTvwInfo &operator = ( TTPHduRegInfo & tHdu)
    {
        TTPHduRegInfo::operator = (tHdu);
//         _snprintf( m_achAlias, sizeof(m_achAlias), "%s",tHdu.m_achAlias );
//          m_dwChannelHandle = tHdu.m_dwChannelHandle;
//          m_bIsOnline = tHdu.m_bIsOnline;	//HDU�Ƿ�ע��
//          m_dwIpAddr = tHdu.m_dwIpAddr;		//����IP��ַ	,   ������
//          m_wStartPort = tHdu.m_wStartPort;	//������ʼ���ն˿�, ������  
 
         return *this;
    } 

   
   
    
    BOOL32 operator == (const tagCmsTvwInfo& tRhs)
    {	
        return  m_dwChannelHandle == tRhs.m_dwChannelHandle;
	}

}TCmsTvwInfo;

//��¼��Ϣ
typedef struct tagLoginInfo
{
	u32     dwIp;
	u16     nPort;
	s8      achName[TP_MAX_ALIAS_LEN_CNC+1];
	s8      achPswd[TP_MAX_ALIAS_LEN_CNC+1];
    TOspNetAddr         tRmtAddr;   //IPV6��ַ
    EmProtocolVersion   emIPver;    //IP����

	tagLoginInfo()
	{
		memset( this, 0, sizeof(tagLoginInfo) );
	}
}TLoginInfo;

//����������Ϣ,ϵͳ����
typedef struct tagLockScreenInfo
{
	bool   bOpen;
	s8  achPswd[TP_MAX_ALIAS_LEN_CNC+1];
	s8  achSysName[TP_MAX_ALIAS_LEN_CNC+1];

	tagLockScreenInfo()
	{
		bOpen = false;
		memset( &achPswd, 0, sizeof(achPswd));
		memset( &achSysName, 0, sizeof(achSysName));
	}
}TLockScreenInfo;

//������MainMenu��Ŀ��Ϣ
typedef struct tagConfMenuInfo
{
	s8 achName[TP_MAX_ALIAS_LEN_CNC+1];	            //����
	int     nIndex;                 //��Ŀ����
	s8 achItemType[TP_MAX_ALIAS_LEN_CNC+1];            //��Ŀ����
	s8 achItemFunc[TP_MAX_ALIAS_LEN_CNC+1];            //��Ŀ�����¼�
	s8 achImgFolder[TP_MAX_ALIAS_LEN_CNC+1];           //��ĿͼƬ·��
	BOOL    bShow;                  //�Ƿ�Ӧ����ʾ
	BOOL    bSetShow;               //�Ƿ�����Ϊ��ʾ

	tagConfMenuInfo()
	{
		nIndex = 0;
		bShow = TRUE;
		bSetShow = TRUE;
		memset(&achName, 0, sizeof(achName));
		memset(&achItemType, 0, sizeof(achItemType));
		memset(&achItemFunc, 0, sizeof(achItemFunc));
		memset(&achImgFolder, 0, sizeof(achImgFolder));
	}
}TConfMenuInfo;

/*
enum Em_ImgSchm{
    emImgSchm0,
	emImgSchm1,
	emImgSchm2,
	emImgSchm3,
	emImgSchm4
};
*/

typedef struct tagDualSrcInfo
{
    vector<TVgaInfo>  vctVgaInfo;
    EmVgaType         emDefaultType;
    EmVgaType         emCurrentType;

    tagDualSrcInfo()
    {
        Clear();
    }

    void Clear()
    {
        vctVgaInfo.clear();
        emDefaultType = emVgaType001;
        emCurrentType = emVgaType001;
    }

}TDualSrcInfo;

enum EM_BrdOptType
{
	em_UnKnow_Ret,
	em_Add_Ret,
	em_Modify_Ret,
	em_Del_Ret
};

enum EM_ShortcutType
{
	emShortcutPanCam = 0,	//ȫ�������
	emShortcutSilence,	    //����
	emShortcutMute,			//����
	emShortcutDulDisplay,   //˫����ʾ
	emShortcutVoiceAct,     //��������
	emShortcutPIP,			//���л�
	emShortcutPicSynthesis, //����ϳ�
	emShortcutCofPoll,		//������ѯ
	emShortcutCofMix,		//�������
	emShortcutCofDiscuss,   //��������
	emShortcutCofRoll,		//�������
	emShortcutTVWall,		//����ǽ
	emShortcutQuiteAll,     //ȫ������
	emShortcutMuteAll,		//ȫ������
}; 

//����ϳɷ��
typedef struct tagVidMixStyleInfo
{
    EMVmpStyle   emVmpStyle;
    WCHAR        achStyleName[TP_MAX_ALIAS_LEN_CNC+1];
    int          nChnlNum;               //ͨ������

    tagVidMixStyleInfo()
    {
        memset( this, 0, sizeof(tagVidMixStyleInfo));
    }
}TVidMixStyleInfo;

typedef struct tagVidMixBkgImg
{
    int          nIndex;
    WCHAR        achVidNormalImgPath[MAX_PATH];        //��Ŀ����ͼƬ·��
    WCHAR        achVidSelImgPath[MAX_PATH];           //��Ŀѡ�б���ͼƬ·��

    tagVidMixBkgImg()
    {
        memset( this, 0, sizeof(tagVidMixBkgImg));
    }
}TVidMixBkgImg;


//����ϳ�Ԥ����Ϣ
typedef struct tagTVmpMemberCfg
{
    u16			m_wConfID;
    EMVmpStyle	m_emStyle;
    u16			m_wSpeakerIndx;		   //�����˸�������
    u16			m_wDualIndx;		   //˫����������  
    TTPVmpCfgChnl	m_atEpList[TP_VMP_MAX_IN_CHN_NUM];
    tagTVmpMemberCfg()
    {
        Clear();
    }
    tagTVmpMemberCfg& operator = (const tagTVmpMemberCfg& tRhs)
    {
        if(this == &tRhs)
            return *this;
        m_wConfID = tRhs.m_wConfID;
        m_emStyle = tRhs.m_emStyle;
        m_wSpeakerIndx = tRhs.m_wSpeakerIndx;
        m_wDualIndx = tRhs.m_wDualIndx;

        for (u16 wIndex = 0 ; wIndex < TP_VMP_MAX_IN_CHN_NUM ; ++wIndex)
        {
            m_atEpList[wIndex] = tRhs.m_atEpList[wIndex];
        }
        return *this;
    }

    void Clear()
    {
        m_wConfID = TP_INVALID_INDEX;
        m_emStyle = tp_VmpStyle_DYNAMIC;
        m_wSpeakerIndx = TP_INVALID_INDEX;
        m_wDualIndx = TP_INVALID_INDEX;

        for ( u16 wIndex = 0; wIndex < TP_VMP_MAX_IN_CHN_NUM; wIndex ++ )
        {
            m_atEpList[wIndex].Clear();
        }
    }
}TVmpMemberCfg;



/*
typedef struct tagTBrdOptRet
{
	EM_BrdOptType emBrdOptType;
	EmTpBoardRet emTpBoardRet;

	tagTBrdOptRet()
	{
		Clear();
	}

	void Clear()
	{
		emBrdOptType = em_UnKnow_Ret;
		emTpBoardRet = emTP_Board_UnKonw;
	}

}TBrdOptRet;

typedef struct tagTTvwBrdOptRet
{
	EM_BrdOptType emBrdOptType;
	EmModifyHduRet emTvwModifyHduRet;
	
	tagTTvwBrdOptRet()
	{
		Clear();
	}
	
	void Clear()
	{
		emBrdOptType = em_UnKnow_Ret;
		emTvwModifyHduRet = em_hdu_brd_no_cfg;
	}
	
}TTvwBrdOptRet;


//�᳡�ͻ����¼����Ϣ
typedef struct tagUmcRecInfo : public TConRecState
{
	s8  m_achName[TP_MAX_NAME_LEN+1];		//�����᳡����

	tagUmcRecInfo& operator = (const TConRecState &tConRecState)
    {
        if(this == &tConRecState)
			return *this;  
		
        TConRecState::operator = (tConRecState); 
        return *this;
	}
	
	tagUmcRecInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		memset( m_achName, 0, TP_MAX_NAME_LEN+1 );
	}
	
}TUmcRecInfo;

//������Ϣ(����¼�������Ϣ)
typedef struct tagUmcConfInfo : public TCMSConf
{
	vector<TUmcRecInfo> m_vecTRecInfo;		//�᳡�ͻ����¼����Ϣ
	TConfPlayStatus m_tConfPlayStatus;		//������Ϣ

	tagUmcConfInfo( TCMSConf &tCMSConf )
    {
        tagUmcConfInfo::Clear();

        TCMSConf::operator = (tCMSConf);
	}

	tagUmcConfInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_vecTRecInfo.clear();
		m_tConfPlayStatus.Clear();
		TCMSConf::Clear();
	}

}TUmcConfInfo;

//������ʽ
typedef struct tagTTPCallSerFormat
{
	u16         m_byFrameRate; 
	EmTpVideoResolution  emRes; 
	EmTpVideoQualityLevel emTpVideoQualityLevel; //HP,BP
	public:
		tagTTPCallSerFormat()
		{ 
			Clear();
		}
		void Clear()
		{
			memset( this ,0 ,sizeof( struct  tagTTPCallSerFormat ) );
			emTpVideoQualityLevel = emTPH264HP;
		}
		
}TTPCallSerFormat;

//��������(��������)
typedef struct tagRegAlias : public TTPAlias
{
	EmTPEndpointType	m_emEndpointType;

	tagRegAlias()
	{
		Clear();
	}
	void Clear()
	{
		m_emEndpointType = emTPEndpointTypeUnknown;
	}
	
	tagTTPAlias& operator = (const TTPAlias& tAlias)
	{
		if (this == &tAlias)
		{
			return *this;
		}
		TTPAlias::operator = (tAlias); 
		return *this;
	}
}TRegAlias;

//��������(��������)
typedef struct tagAliasEx
{
	EmTPEndpointType	m_emEndpointType;
	vector<TTPAlias>    m_vecTTPAlias;
	
	tagAliasEx()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emEndpointType = emTPEndpointTypeUnknown;
		m_vecTTPAlias.clear();
	}
	
	//shishi
	BOOL32 operator == (tagAliasEx& tRhs)
    {	
		BOOL32 bFind = FALSE;
		
		vector<TTPAlias>::iterator it = m_vecTTPAlias.begin();
		for ( ; it != m_vecTTPAlias.end(); it++ )
		{
			vector<TTPAlias>::iterator itRhs = tRhs.m_vecTTPAlias.begin();
			for ( ; itRhs != tRhs.m_vecTTPAlias.end(); itRhs++ )
			{
				if ( it->m_byType == itRhs->m_byType
					&& ( strcmp( it->m_abyAlias, itRhs->m_abyAlias ) == 0 ) )
				{
					bFind = TRUE;
				}
			}
		}
		
        return  bFind;
	}
	
}TAliasEx;*/

enum EmTitleTabID
{
    emTabID_Left = 0,
    emTabID_Right,
};

//ȫ�������Ԥ��λ��Ϣ
struct TPanCam
{
	CString	strPanCamName;//ȫ�������Ԥ��λ����
	int wCamID;//��Ӧȫ�������ID
	int wPresetID;//Ԥ��λ���

	TPanCam(){ clear() ;};
	void clear()
	{ 
		strPanCamName = _T(""); 
		wCamID = -1;
		wPresetID = -1;
	};

	void Copy(TPanCam tPanCam)
	{ 
		strPanCamName = tPanCam.strPanCamName; 
		wCamID = tPanCam.wCamID;
		wPresetID = tPanCam.wPresetID;
	};
};


#endif 
