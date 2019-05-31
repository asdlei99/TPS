#ifndef _h_cnstruct_h__
#define _h_cnstruct_h__
#include "tpsys.h"
#include <time.h>

#include "tpcommontype.h"
#include "tpcommonstruct.h"
#include "osp.h"
#include "cnconst.h"
#include "cnstype.h"

typedef struct tagTTPMCUSelViewReq
{
	TTPTerLabel tTerLabel;
	EmTpCtrlMode emTpCtrlMode;
	u8           byPos;
	
	tagTTPMCUSelViewReq()
	{
		memset(this, 0, sizeof(struct tagTTPMCUSelViewReq));
	}
}TTPMCUSelViewReq;

typedef struct tagTTPShowLogo
{
	s8        achLogoName[TP_MAX_ALIAS_LEN + 1];
	BOOL      bIsShowLogo;
    EmTpColor emColor;
    EmTpSize  emSize;
	EmTpLogoStyle emStyle;
	BOOL      bInit;//��ʶT300��һ������
}TTPShowLogo;

typedef struct tagTTPLogo
{
	u8          byIndex;
    TTPShowLogo tLogoInfo;
	tagTTPLogo()
	{
		Clear();
	}
	void Clear()
	{
		byIndex = 0;
		memset(&tLogoInfo, 0, sizeof(TTPShowLogo));
	}
}TTPLogo;

typedef struct tagTTPLogoInfo
{
    TTPShowLogo tFirsLogoInfo;
	TTPShowLogo tSecondLogoInfo;
	TTPShowLogo tThirdLogoInfo;
}TTPLogoInfo;

typedef struct tagTTPShowBanner
{
	s8        achBannerName[TP_MAX_ALIAS_LEN + 1];
    BOOL      bIsShowBanner;
	EmTpColor emColor;
    EmTpSize  emSize;
	EmTpStyle emStyle;
	emTpTransparency emTransparency;
}TTPShowBanner;

typedef struct tagTTPBanner
{
	u8            byIndex;
    TTPShowBanner tBannerInfo;
	tagTTPBanner()
	{
		Clear();
	}
	void Clear()
	{
		byIndex = 0;
		memset(&tBannerInfo, 0, sizeof(TTPShowBanner));
	}
}TTPBanner;

typedef struct tagTTPBannerInfo
{
    TTPShowBanner tFirstBannerInfo;
	TTPShowBanner tSeconfBannerInfo;
	TTPShowBanner tThirdBannerInfo;
}TTPBannerInfo;

//add by wangqichang
//��ƵԴ����
typedef struct tagTTPVideoSourceName
{
	EmTPMtVideoPort m_emPortType;
	s8 m_achSourceName[TP_MAX_ALIAS_LEN+1];
	public:
		tagTTPVideoSourceName()
		{
			memset(this, 0 , sizeof( tagTTPVideoSourceName ));
		}
}TTPVideoSourceName;

//ά������������Ƶ����
typedef struct tagTTPVideoInfoTool
{
	EmTPMtVideoPort        m_aemBigVideoSource[emEndMPCodec - 1];//��ͼ����ƵԴ
	EmTPMtVideoPort        m_aemMinVideoSource[emEndMPCodec - 1];//Сͼ����ƵԴ
	TTPVideoSourceName     m_atVideoSourceName[emTPC7Vid + 1];//��ƵԴ����(6��+ ȫ�������1)
	EmVidEncResizeMode     m_emVidEncResizeMode;//����Ƶͼ�������������
	BOOL                   m_bIsH323PipMerge;//H323���黭��ϳ�
	EmVidMergeStyle        m_emVideoMergeStyle;//����ϳɷ��
	public:
		tagTTPVideoInfoTool(){memset(this,0,sizeof(struct tagTTPVideoInfoTool));}
}TTPVideoInfoTool;

//�пص��ӻ�������Ϣ
typedef struct tagTCentreTVCfg
{
	EmSerialType           emSerialType;  //���ӻ����Ӵ�������
	EmTvPowerMode          emTvPowerMode; //���ӻ�����״̬ 
	EmTVAudVisMode         emAudVisMode; //���ӻ�����ģʽ
	EmTVDisplayMode        emDisMode;    //���ӻ���ʾģʽ
	EmTVInputSelect        emInpSelect;  //��������ѡ��
	EmTvSrcPowerMode	   emTvSrcPowerMode;//���ӻ��ϵ�ǰ����״̬
	EmTVModle			   emTvModle;  //���ӻ��ͺ�   add for B4 ---2015/2/4
    
	public:
		tagTCentreTVCfg()
		{
			memset( this, 0, sizeof(struct tagTCentreTVCfg) );
		}
		
}TCentreTVCfg;

//�пش�����Ϣ
typedef struct tagTCentreCurInfo
{
	BOOL			bCurOpen;
	u8				byCurNum;
	TCentreCurName  tCenCurName[MAX_CURTAIN_NUM];
	public:
		tagTCentreCurInfo()
		{
			memset( this, 0, sizeof(struct tagTCentreCurInfo) );
		}

}TCentreCurInfo;

//ȫ�������Ԥ��λ��
typedef struct tagTPanCamName
{
    s8  achPanCamName[MAX_PANCAMNAME_LEN];
	public:
		tagTPanCamName()
		{
			memset( this, 0, sizeof(struct tagTPanCamName) );
		}
		
}TPanCamName;
//ÿ�������һ��Ԥ��λ���Ϊ16��
typedef struct tagTPanCamGroupName
{
    TPanCamName  tPanCamName[MAX_PRESET_NUM];
	public:
		tagTPanCamGroupName()
		{
			memset( this, 0, sizeof(struct tagTPanCamGroupName) );
		}
		
}TPanCamGroupName;

//ȫ���������Ϣ
typedef struct tagTPanCamInfo
{
	BOOL			  bPanCamOpen;				//ȫ�������״̬
	u8				  byPanCamNum;              //ȫ�����������
	TPanCamGroupName  tPCamGroupName[MAX_PAN_NUM];       
	EmQCamProType     emQCamProType;            //ȫ�����������
	public:
		tagTPanCamInfo()
		{
			memset( this, 0, sizeof(struct tagTPanCamInfo) );
		}
		
}TPanCamInfo;

//end add
//˫����
typedef struct tagTDualScreenInfo
{
	BOOL			  bDualScreenOpen;	//˫����״̬
	public:
		tagTDualScreenInfo()
		{
			memset( this, 0, sizeof(struct tagTDualScreenInfo) );
		}
		
}TDualScreenInfo;

//˫����������
typedef struct tagTTPVAdapterInfo
{
	BOOL    bStartAdapter; //�Ƿ���˫������
	u32     dwProfile;    //Hp or BP
	u32     dwWidth; 	 //����ֱ��ʿ��
	u32     dwHeight;	 //����ֱ��ʸ߶�
	u32     dwFramerate; //����֡��
	u16     wBitRate;  //��������
	BOOL    bOnlySetNewApPara; //ֻ�����������
	public:
		tagTTPVAdapterInfo(){memset(this,0,sizeof(struct tagTTPVAdapterInfo));}
}TTPVAdapterInfo;

typedef struct tagTTPAutoTestLoopInfo //������������
{
	EmTpMediaType          emTpMediaType;
	EmTpVEncCodecType      emTpVEncCodecType; //������Ƶ����������Ҫ����
	EmTpCodecComponent     emCope;
	BOOL                   bLoop;//�Ի�
	u8                     byPos;      
	public:
		tagTTPAutoTestLoopInfo(){memset(this,0,sizeof(struct tagTTPAutoTestLoopInfo));}
}TTPAutoTestLoopInfo;

typedef struct tagTTPInterFaceTestInfo //���ڽӿڲ���
{
	EmTpCodecComponent     emCope;
	BOOL                   bLoop;//�Ի�
	u8                     byPos;      
	public:
		tagTTPInterFaceTestInfo(){memset(this,0,sizeof(struct tagTTPInterFaceTestInfo));}
}TTPInterFaceTestInfo;

typedef struct tagTTPCapMap 
{
	TTPMediaStream cMeadiaStream;
	s32 nChannelId;
	EmTpChannelHandle emChanHandle;
public:
    tagTTPCapMap(){ memset ( this, 0, sizeof( struct tagTTPCapMap) );}
	
}TTPCapMap;

typedef struct tagTTPCapPack 
{
	u16		  wTotalPackNum;
	u16		  wCurPackIndex;
	u16		  wValidCapNum;
	TTPCapMap atTPCapMap[4];
public:
    tagTTPCapPack(){ memset ( this, 0, sizeof( struct tagTTPCapPack) );}
	
}TTPCapPack;

typedef struct tagTTPVideoLoopTestInfo
{
	EmTpVideoLoopTest   emVideoLoopTest;
	BOOL                   bLoop;//�Ի�
	u8                     byPos;      
	public:
		tagTTPVideoLoopTestInfo(){memset(this,0,sizeof(struct tagTTPVideoLoopTestInfo));}
}TTPVideoLoopTestInfo;

typedef struct tagTTpConfEpInfo
{
	u16 m_wConfID; 
	TTpCallAddr m_tCallAddr;
	
	u16 m_Index;
	BOOL32 m_bPermit;
	
	tagTTpConfEpInfo()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_tCallAddr.Clear();
		m_Index = TP_INVALID_INDEX;
		m_bPermit = FALSE;
	}
	
}TTpConfEpInfo;

// begin add for Hdu
typedef struct tagTTpHduUnitPlayInfo
{
	u16		m_wConfID;		//����ID
	u16		m_wDstID;
	s8      m_achAlias[TP_MAX_EPID_LEN+1];
	u16		m_wScreenNum;	//����
	EmViewEpType		m_emType;
	EmCnsHduRunStatus	m_emStatus;

	tagTTpHduUnitPlayInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wDstID = TP_INVALID_INDEX;
		m_achAlias[0] = '\0';
		m_wScreenNum = TP_INVALID_INDEX;
		m_emType = EmEpType_Invalid;
		m_emStatus = emCnsHdu_Idle;
	}

	void SetAlias(const s8* alias)
	{
		strncpy(m_achAlias, alias, TP_MAX_EPID_LEN);
		m_achAlias[TP_MAX_EPID_LEN] = '\0';
	}

}TTpHduUnitPlayInfo;


typedef struct tagTTpHduPlanUnit
{	
	u8  	m_byReged;	//����״̬
	u8      m_byValid;
	u16		m_wIndex;	//����
	s8		m_achAlias[TP_MAX_EPID_LEN+1];	//HDU ������
	u8   	m_byVmp;
	u8		m_byVol;
	u8  	m_byMute;
	u8		m_byChanIndex;	//ͨ���� 0 �� 1

	TTpHduUnitPlayInfo	m_atPlayInfo[TP_MAX_VMP_SUBCHAN];

	tagTTpHduPlanUnit()
	{
		Clear();
	}

	void Clear()
	{
		m_byReged = 0;
		m_byValid = 0;
		m_wIndex = TP_INVALID_INDEX;
		m_achAlias[0] = '\0';
		m_byVmp = 0;
		m_byVol = 0;
		m_byMute = 0;
		m_byChanIndex = 0;
		for (u16 wIndex = 0 ; wIndex < TP_MAX_VMP_SUBCHAN; wIndex++)
		{
			m_atPlayInfo[wIndex].Clear();
		}
	}
}TTpHduPlanUnit;

typedef struct tagTTpHduPlanPackData
{
	u8		m_byRow;
	u8		m_byCol;
	u16		m_wNum; // ����

	u8      m_byFirst; // �Ƿ��ǵ�һ��
	u8		m_CurentNum;  // ��ǰ�������������Ч����
	TTpHduPlanUnit m_atUnits[TP_STYLE_DATA_PACK_NUM];  

	tagTTpHduPlanPackData()
	{
		Clear();
	}

	void Clear()
	{
		m_byRow = 0;
		m_byCol = 0;
		m_wNum = 0;
		m_byFirst = 0;
		m_CurentNum = 0;
		for (u16 wIndex = 0; wIndex < TP_STYLE_DATA_PACK_NUM; wIndex++)
		{
			m_atUnits[wIndex].Clear();
		}
	}

}TTpHduPlanPackData;

typedef struct tagTTpHduPlayReq
{
	EmViewEpType	m_emType;
	u16		m_wConfID;
	u16		m_wDstID;   // ����ǻ᳡�����ǻ᳡id������Ǻϳ�������������id
	s8      m_achAlias[TP_MAX_ALIAS_LEN + 1];  // �᳡���ƻ�����������
	u16		m_wScreenNum;  // 

	// ͨ����Ϣ
	u16		m_wIndex;		//����
	u8		m_bySubIndex;	//������
	BOOL32	m_bVmp; //�Ƿ��Ǻϳ�ͨ��

	tagTTpHduPlayReq()
	{
		m_emType = EmEpType_Invalid;
		m_wConfID = TP_INVALID_INDEX;
		m_wDstID = TP_INVALID_INDEX;
		m_achAlias[0] = '\0';
		m_wScreenNum = TP_INVALID_INDEX;
		m_wIndex = TP_INVALID_INDEX;
		m_bySubIndex = TP_MAX_VMP_SUBCHAN;
		m_bVmp = FALSE;
	}

	void SetAlias(const s8* alias)
	{
		strncpy(m_achAlias, alias, TP_MAX_ALIAS_LEN);
		m_achAlias[TP_MAX_ALIAS_LEN] = '\0';
	}

	tagTTpHduPlayReq& operator = (const tagTTpHduPlayReq& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		memcpy(this, &tRhs, sizeof(tRhs));
		return *this;
	}

}TTpHduPlayReq;

typedef struct tagTTpHduBaseInfo
{
	u16		m_wIndex;
	u8		m_bySubIndex;

	tagTTpHduBaseInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wIndex = TP_INVALID_INDEX;
		m_bySubIndex = 0;
	}

}TTpHduBaseInfo;

typedef struct tagTTpHduSetVolInfo
{
	TTpHduBaseInfo	m_tInfo;
	u8		m_byVol;
	BOOL32	m_bMute;

	tagTTpHduSetVolInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_tInfo.Clear();
		m_byVol = 0;
		m_bMute = FALSE;
	}
}TTpHduSetVolInfo;

typedef struct tagTTpHduChanModeSetInfo
{
	u16 m_wIndex;  // ͨ������
	u8  m_byMode;  // 0 Ϊһ���棬1Ϊ4����

	tagTTpHduChanModeSetInfo()
	{
		Clear();
	}

	BOOL32 IsValidMode()
	{
		return (0 == m_byMode || 1 == m_byMode);
	}

	void Clear()
	{
		m_wIndex = TP_INVALID_INDEX;
		m_byMode = 0;
	}

}TTpHduChanModeSetInfo;


// end add for hdu


//�����б�
typedef struct tagTTpRollCallList
{
	u16	m_wNum;
	u16	m_awList[TP_MAX_ROLLCALL_NUM];	      //�����б�,���б�������
	u16 m_wRollCaller;                       //������
	u16 m_wCallTarget;                       //��ǰ��������

	tagTTpRollCallList()
	{
		Clear();
	}

	tagTTpRollCallList& operator=(const tagTTpRollCallList& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}

		for (u16 wIndex = 0; wIndex < tInfo.m_wNum; ++wIndex)
		{
			m_awList[wIndex] = tInfo.m_awList[wIndex];
		}
		m_wNum = tInfo.m_wNum;
        m_wRollCaller = tInfo.m_wRollCaller;
		m_wCallTarget = tInfo.m_wCallTarget;

		return *this;
	}

	void Clear()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_ROLLCALL_NUM; ++wIndex)
		{
			m_awList[wIndex] = TP_INVALID_INDEX;
		}
		m_wNum = 0;
		m_wRollCaller = TP_INVALID_INDEX;
        m_wCallTarget = TP_INVALID_INDEX;
	}


	BOOL32 SetRollCaller(u16 wEpID)
	{
		if (!(TP_VALID_HANDLE(wEpID)))
		{
            return FALSE;
		}

		// �������뱻�����߱��벻ͬ
		for (u16 wIndex = 0; wIndex < TP_MAX_ROLLCALL_NUM; wIndex++)
		{
            if (m_awList[wIndex] == wEpID)
			{
				return FALSE;
			}
		}
		
        m_wRollCaller = wEpID;
		
        return TRUE;
	}
	
	u16 GetRollCaller()
	{
		return m_wRollCaller;
	}
	

	BOOL32 SetRollCallTarget(u16 wEpID)
	{
		if (!(TP_VALID_HANDLE(wEpID)))
		{
            return FALSE;
		}
		
        m_wCallTarget = wEpID;
		
        return TRUE;
	}

	u16 GetRollCallTarget()
	{
		return m_wCallTarget;
	}

	BOOL32 IsRollCallTargetInList(u16 wEpID)
	{
		if (!TP_VALID_HANDLE(wEpID))
		{
            return FALSE;
		}
		
		for (u16 wIndex = 0; wIndex < m_wNum; ++wIndex)
		{
			if (m_awList[wIndex] == wEpID)
			{
				return TRUE;
			}
		}
		
		return FALSE;
	}
	
	u16 GetTargetIndex(u16 wEpID)
	{
		if (!TP_VALID_HANDLE(wEpID))
		{
            return TP_INVALID_INDEX;
		}
		
		
        for(u16 wIndex = 0; wIndex < m_wNum; wIndex++)
		{
			if (m_awList[wIndex] == wEpID)
			{
				return wIndex;
			}
		}
		
        return TP_INVALID_INDEX;
	}

	u16 AddRollCallTarget(u16 wEpID)
	{		
		u16 wIndex = 0;

		if (!TP_VALID_HANDLE(wEpID))
		{
            return TP_INVALID_INDEX;
		}

		// �������ظ��ı�������
		for (wIndex = 0; wIndex < TP_MAX_ROLLCALL_NUM; ++wIndex)
		{
			if (m_awList[wIndex] == wEpID)
			{
				return TP_INVALID_INDEX;
			}
		}

		for (wIndex = 0; wIndex < TP_MAX_ROLLCALL_NUM; ++wIndex)
		{
			if (!TP_VALID_HANDLE(m_awList[wIndex]))
			{
				m_awList[wIndex] = wEpID;
				m_wNum++;
				return wIndex;
			}
		}

		return TP_INVALID_INDEX;
	}


	void DelRollCallTarget(u16 wEpId)
	{
		u16 wIndex = 0;
		u16 wDelIndex = TP_INVALID_INDEX;
		for (wIndex = 0; wIndex < TP_MAX_ROLLCALL_NUM; ++wIndex)
		{
			if (m_awList[wIndex] == wEpId)
			{
				m_awList[wIndex] = TP_INVALID_INDEX;
				wDelIndex = wIndex;
				m_wNum--;
				break;
			}
		}

		if (TP_VALID_HANDLE(wDelIndex))
		{
			for (wIndex = wDelIndex+1; wIndex < TP_MAX_ROLLCALL_NUM; ++wIndex)
			{
				if (TP_VALID_HANDLE(m_awList[wIndex]))
				{
					m_awList[wIndex-1] = m_awList[wIndex];
					m_awList[wIndex] = TP_INVALID_INDEX;
					continue;
				}
				break;
			}
		}
		return;
	}

	u16 GetRollCallTargetNum() const
	{
		//��������Ա����������������
		return m_wNum;
	}

}TTpRollCallList, *PTTpRollCallList;

typedef struct tagTTpConfRollCallInfo
{
	u16					m_wConfID;
	BOOL32				m_bStart;
	TTpRollCallList		m_atRollCallMemList;
	EmRollCallRspRet	m_emRet;  // ���������Ľ��
	
	tagTTpConfRollCallInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_bStart  = FALSE;
		
		m_atRollCallMemList.Clear();
		m_emRet = em_RollCallOprRsp_End;
	}
	
}TTpConfRollCallInfo;


typedef struct tagTTpRollCallNextEpInfo
{
	u16 m_wConfID;
    u16 m_wRollCaller;
	u16 m_wCallTarget;
    EmRollCallRspRet m_emRet;
	
	tagTTpRollCallNextEpInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wRollCaller = TP_INVALID_INDEX;
		m_wCallTarget = TP_INVALID_INDEX;
		m_emRet = em_RollCallOprRsp_End;
	}
	
}TTpRollCallNextEpInfo;

// for umsaudmix
typedef struct tagTTpAudMixList
{
	u16						m_wNum;
	u16						m_awMixEp[TP_APU2_MAX_CHAN_NUM];
	
	tagTTpAudMixList()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wNum = 0;
		for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
		{
			m_awMixEp[wIndex] = TP_INVALID_INDEX;
		}
	}
	
	BOOL32 AddID(u16 wEpID)
	{		
		u16 wIndex = 0;
		for (wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; ++wIndex)
		{
			if (m_awMixEp[wIndex] == wEpID)
			{
				return FALSE;
			}
		}
		for (wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; ++wIndex)
		{
			if (!TP_VALID_HANDLE(m_awMixEp[wIndex]))
			{
				m_awMixEp[wIndex] = wEpID;
				m_wNum++;
				return TRUE;
			}
		}
		return FALSE;
	}
	
	void DelId(u16 wEpId)
	{
		u16 wIndex = 0;
		u16 wDelIndex = TP_INVALID_INDEX;
		for (wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; ++wIndex)
		{
			if (m_awMixEp[wIndex] == wEpId)
			{
				m_awMixEp[wIndex] = TP_INVALID_INDEX;
				wDelIndex = wIndex;
				m_wNum--;
				break;
			}
		}
		
		if (TP_VALID_HANDLE(wDelIndex))
		{
			for (wIndex = wDelIndex+1; wIndex < TP_APU2_MAX_CHAN_NUM; ++wIndex)
			{
				if (TP_VALID_HANDLE(m_awMixEp[wIndex]))
				{
					m_awMixEp[wIndex-1] = m_awMixEp[wIndex];
					m_awMixEp[wIndex] = TP_INVALID_INDEX;
					continue;
				}
				break;
			}
		}
		return;
	}

	BOOL32 IsInList(u16 wEpId) const
	{
		u16 wIndex = 0;
		for (wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; ++wIndex)
		{
			if (m_awMixEp[wIndex] == wEpId)
			{
				return TRUE;
			}
		}
		return FALSE;
	}

	tagTTpAudMixList& operator = (const tagTTpAudMixList& tInfo)
	{
		if (this != &tInfo)
		{
			m_wNum = tInfo.m_wNum;
			for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
			{
				m_awMixEp[wIndex] = tInfo.m_awMixEp[wIndex];
			}
		}
		return *this;
	}
	
	
}TTpAudMixList;

typedef struct tagTTpAudMixInfo
{
	u16					m_wConfId;
	TTpAudMixList		m_tMixList;
	EmAudMixMode		m_emMode;
	
	tagTTpAudMixInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wConfId = TP_INVALID_INDEX;
		m_tMixList.Clear();
		m_emMode = em_umsaudmixmode_idle;
	}
	
	tagTTpAudMixInfo& operator = (const tagTTpAudMixInfo& tInfo)
	{
		if (this != &tInfo)
		{
			m_wConfId = tInfo.m_wConfId;
			m_tMixList = tInfo.m_tMixList;
			m_emMode = tInfo.m_emMode;
		}
		return *this;
	}
	
}TTpAudMixInfo;

typedef struct tagTTpAudMixModeCmdRes
{
	u16					m_wConfId;
	EmAudMixMode		m_emCmdMode;
	EmAudMixRes		    m_emRes;
	
	tagTTpAudMixModeCmdRes()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wConfId = TP_INVALID_INDEX;
		m_emCmdMode = em_umsaudmixmode_idle;
		m_emRes = em_umsaudmixres_unkown;
	}
	
}TTpAudMixModeCmdRes;

typedef struct tagTTpAudMixListCmd
{
	u16					m_wConfId;
	TTpAudMixList		m_tList;
	EmAudMixListOpr  	m_emOpr;

	tagTTpAudMixListCmd()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wConfId = TP_INVALID_INDEX;
		m_tList.Clear();
		m_emOpr = em_umsaudmixlistopr_unkown;
	}
	
}TTpAudMixListCmd;

typedef struct tagTTpAudMixListCmdRes
{
	u16					m_wConfId;
	TTpAudMixList		m_tList;
	EmAudMixRes		    m_aemRes[TP_APU2_MAX_CHAN_NUM];
	
	tagTTpAudMixListCmdRes()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wConfId = TP_INVALID_INDEX;
		m_tList.Clear();
		for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
		{
			m_aemRes[wIndex] = em_umsaudmixres_unkown;
		}
	}
	
}TTpAudMixListCmdRes;

typedef struct tagTTpUpdataRollCallList
{
	u16					m_wConfID;            //����ID
	BOOL32				m_bAdd;               //���ɾ��
	TTpRollCallList		m_atRollCallMemList;  //���ɾ�������б�
	
	tagTTpUpdataRollCallList()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_bAdd    = FALSE;
		
		m_atRollCallMemList.Clear();
	}
	
}TTpUpdataRollCallList;



typedef struct tagTTpUpdataRollCallListRes
{
	u16					m_wConfID;            //����ID
	BOOL32				m_bAdd;               //���ɾ��
	TTpRollCallList		m_atRollCallMemList;  //���ɾ�������б�, update ʱ�������б��е�m_wRollCaller��m_wCallTarget 
	EmRollCallRspRet    m_emRet[TP_MAX_ROLLCALL_NUM];   //ÿһ�� ������ɾ�� EP �Ľ��
	
	tagTTpUpdataRollCallListRes()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_bAdd    = FALSE;
		
		m_atRollCallMemList.Clear();
		
		for(u16 wIndex = 0; wIndex < TP_MAX_ROLLCALL_NUM; wIndex++)
		{
            m_emRet[wIndex] = em_RollCallOprRsp_End;
		}
	}
	
}TTpUpdataRollCallListRes;



typedef struct tagTTpRollCallPresentStateEpInfo
{
    u16 m_wEpID;                  //����ID
    u16 m_wEpState;               //״̬  EmRollCallPresentState ǿת

	tagTTpRollCallPresentStateEpInfo()
	{
        Clear();
	}

	void Clear()
	{
        m_wEpID = TP_INVALID_INDEX;
        m_wEpState = 0;
	}

	tagTTpRollCallPresentStateEpInfo& operator = (const tagTTpRollCallPresentStateEpInfo& tInfo)
	{
		if (this != &tInfo)
		{
			m_wEpID = tInfo.m_wEpID;
			m_wEpState = tInfo.m_wEpState;
		}
		
		return *this;
	}

}TTpRollCallPresentStateEpInfo;

typedef struct tagTTpRollCallPresentStateMsg
{
    u16 m_wConfID;

    u16 m_wValidNum;              //  ״̬��������Ч��
    TTpRollCallPresentStateEpInfo  m_atEpState[TP_MAX_ROLLCALL_NUM];  //��������״̬

	tagTTpRollCallPresentStateMsg()
	{
		Clear();
	}

	void Clear()
	{
		m_wConfID      = TP_INVALID_INDEX;
		m_wValidNum    = 0;

		for(u16 wIndex = 0; wIndex < TP_MAX_ROLLCALL_NUM; wIndex++)
		{
            m_atEpState[wIndex].Clear();
		}
	}

	tagTTpRollCallPresentStateMsg& operator = (const tagTTpRollCallPresentStateMsg& tInfo)
	{
		if (this != &tInfo)
		{
			m_wConfID = tInfo.m_wConfID;
			m_wValidNum = tInfo.m_wValidNum;

			for (u16 wIndex = 0; wIndex < m_wValidNum; wIndex++)
			{
                 m_atEpState[wIndex] = tInfo.m_atEpState[wIndex];
			}

		}

		return *this;
	}
	
}TTpRollCallPresentStateMsg;

#endif //_h_cnstruct_h__