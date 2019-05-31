/*****************************************************************************
  ģ����      : 
  �ļ���      : kdvadapter_hd.h
  ����ļ�    : 
  �ļ�ʵ�ֹ���: 
  ����        : ��ѩ��
  �汾        : V1.0  Copyright(C) 2008-2009 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2012/4/24   1.0         ��ѩ��      ����
******************************************************************************/
#ifndef _CODEADAPTER_HD3_H_
#define _CODEADAPTER_HD3_H_

#include "codecwrapperdef_hd.h"
//////////////////////////////////////////////////////////////////////////
#define MAX_BAS_SESSION					4
#define BAS_BASIC_ADAPTER_MAX_NUM		4
#define BAS_ENHANCED_ADAPTER_MAX_NUM	7
//////////////////////////////////////////////////////////////////////////
//�����붨��

#define HARD_BAS_OK         0
#define HARD_BAS_BASE       5000

enum enBASErr
{
    Bas_Success = HARD_BAS_OK,
		
	Bas_Error_Base = HARD_BAS_BASE,
	Bas_Error_NoMemory,
	Bas_Error_NoDevice,
	Bas_Error_NoCreate,
	Bas_Error_Param,
	Bas_Error_Process
};
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//adapter structs
/* ������������� */
typedef struct tagVidAdapterCreate
{
    u32  m_dwDevVersion;	//enBoardType��Ʒ�汾��
    u32  m_dwMode;			//ҵ��ģʽ����BAS_BASIC
}TVidAdapterCreate;

typedef struct tagAdapterEncParam
{
	u32 m_dwEncoderId;		//������ID,0��1��2��3����;ÿ������ͨ�����Ǵ�0��ʼ
    TVideoEncParam m_tVideoEncParam;	//����������
}TAdapterEncParam;

//����ͨ��
typedef struct tagAdapterChannel
{
	u32 m_dwAdapterChnlId;	//������ͨ����,0��1��2��3����
    u32	m_dwDecMediaType;	//������������,����ʱ��ʡ���´�����������ʱ��;��ȷ��ʱ���Ĭ��ֵ
	u32 m_dwEncNum;			//����������
    TAdapterEncParam* m_ptEncParam; //�������
}TAdapterChannel;
//////////////////////////////////////////////////////////////////////////
class CAdapterChannel;

class CKdvVideoAdapter
{
public:
    CKdvVideoAdapter();
    ~CKdvVideoAdapter();

public:
    u16 Create(const TVidAdapterCreate &tInit);	//����������,������codecwrapperdef_hd.h
	u16 Destroy(void);	//�˳�

    u16 Start(u32 dwAdapterChnlId);	//��ʼĳһ·����		   
   	u16 Stop(u32 dwAdapterChnlId);	//ֹͣĳһ·����	
    
    u16 AddVideoChannel(const TAdapterChannel *ptAdpChannel);	//�������ͨ��
    u16 RemoveVideoChannel(u32 dwAdapterChnlId);				//ɾ������ͨ��

	//dwAdapterChnlId������ͨ����,dwEncoderId���������
    u16 GetVidDecStatus(u32 dwAdapterChnlId, TKdvDecStatus &tVidDecStatus); //�õ�����״̬��Ϣ
    u16 GetVidDecStatis(u32 dwAdapterChnlId, TKdvDecStatis &tVidDecStatis); //�õ�����ͳ����Ϣ

	u16 GetVidEncStatus(u32 dwAdapterChnlId, u32 dwEncoderId, TKdvEncStatus &tVidEncStatus);
	u16 GetVidEncStatis(u32 dwAdapterChnlId, u32 dwEncoderId, TKdvEncStatis &tVidEncStatis);

    u16 ChangeVideoEncParam(u32 dwAdapterChnlId, TVideoEncParam* ptVidEncParam, u32 dwEncNum = 1);	//�ı�һ����Ƶ����ͨ�����еı������
    u16 ChangeVideoDecParam(u32 dwAdapterChnlId, TVideoDecParam* ptVidDecParam);					//�ı�һ����Ƶ����ͨ���Ľ������

    u16 AddVideoEncParam(u32 dwAdapterChnlId, TVideoEncParam* ptVidEncParam, u32 dwEncId);
    u16 SetVidDataCallback(u32 dwAdapterChnlId, u32 dwEncoderId, FRAMECALLBACK fVidData, void* pContext); /*������Ƶ���ݻص���������*/
    u16 SetData(u32 dwAdapterChnlId, const TFrameHeader& tFrameInfo);        /*������Ƶ�������ݣ�������*/
    
    void  ShowChnInfo(u32 dwAdapterChnlId, BOOL32 bEnc);
	
    u16 SetFastUpdata(u32 dwAdapterChnlId,u32 dwEncoderId,BOOL32 bAllUpdate=FALSE);
    
    u16 SetVidDecResizeMode(u32 dwAdapterChnlId, u32 dwMode);
	u16 SetVidEncResizeMode(u32 dwAdapterChnlId, u32 dwMode);//ģʽ0:�Ӻڱߣ�1:�ñߣ�Ĭ��0

    u16 ClearVideo(); /*������Ƶ���棬������ֹͣ�յ����������*/
protected:
    CAdapterChannel* m_pCodec;
};

#endif
