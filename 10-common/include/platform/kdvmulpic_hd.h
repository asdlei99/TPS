/*****************************************************************************
ģ����      : 
�ļ���      : kdvmulpic_hd.h
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : ������
�汾        : V1.0  Copyright(C) 2008-2009 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2008/11/12    1.0         ������      ����
******************************************************************************/

#ifndef _KDVMULPIC_HD3_H_
#define _KDVMULPIC_HD3_H_

#include "codecwrapperdef_hd.h"
//////////////////////////////////////////////////////////////////////////
//�����붨��
#define HARD_MULPIC_OK         0
#define HARD_MULPIC_BASE       4000

enum enMPUErr
{
    MulPic_Success = HARD_MULPIC_OK,
		
	MulPic_Err_Base = HARD_MULPIC_BASE,
	MulPic_Error_NoMem,
	MulPic_Error_NODev,
	MulPic_Error_NOCreate,
	MulPic_Error_Param,
	MulPic_Error_CreateAlready,
	MulPic_Error_NoVPLink,
};
//////////////////////////////////////////////////////////////////////////
//����ϳ����ͨ����
#define MULPIC_MAX_CHNS			25
#define MULPIC_MAX_CHNS_SIMPLE  10  //����VMP_SIMPLEģʽ���ͨ����
#define VMP_BASIC_ADAPT_NUM		3
#define VMP_ENHANCED_ADAPT_NUM	10

enum enMulPicType
{
    MULPIC_TYPE_ONE  = 0,	//0 -������
    MULPIC_TYPE_VTWO = 1,	//1 -�����棺���ҷ�
    MULPIC_TYPE_THREE   ,	//2 -������
    MULPIC_TYPE_FOUR    ,	//3 -�Ļ���
    MULPIC_TYPE_SIX     ,	//4 -������
    MULPIC_TYPE_ITWO    ,	//5 -�����棺
    MULPIC_TYPE_SFOUR   ,	//6 -�����Ļ��棺һ����С
    MULPIC_TYPE_SEVEN   ,	//7 -�߻��棺������С
    MULPIC_TYPE_EIGHT   ,	//8 -�˻���
    MULPIC_TYPE_NINE    ,		//9 -�Ż���
    MULPIC_TYPE_TEN     ,		//10-ʮ���棺�����С
    MULPIC_TYPE_THIRTEEN,	//11-ʮ������
    MULPIC_TYPE_SIXTEEN ,	//12-ʮ������
    MULPIC_TYPE_TWENTY ,	//13-��ʮ����
    MULPIC_TYPE_TWENTYFIVE,	//14-��ʮ�廭��  
    MULPIC_TYPE_THREE_2IBR,		// 2���ڵײ�����
    MULPIC_TYPE_THREE_2IB,		// 2 ���ڵײ�����
    MULPIC_TYPE_THREE_2IBL,		// 2���ڵײ�����
    MULPIC_TYPE_THREE_2ITL,		// 2���ڶ�������
    
    MULPIC_TYPE_VTHREE,			//��ֱ�ȴ�3����
    MULPIC_TYPE_FOUR_3IB,		// 3���ڵײ�����
    MULPIC_TYPE_TEN_MID_LR,	// 10���棬�м�������
    MULPIC_TYPE_THIRTEEN_MID,	// 13���棬�м���

    MULPIC_TYPE_SIMPLE_TWO,  //����Ϊ����VMP_SIMPLEģʽ���
    MULPIC_TYPE_SIMPLE_THREE,
    MULPIC_TYPE_SIMPLE_FOUR,
    MULPIC_TYPE_SIMPLE_FIVE,
    MULPIC_TYPE_SIMPLE_SIX,
    MULPIC_TYPE_SIMPLE_SEVEN,
    MULPIC_TYPE_SIMPLE_EIGHT,
    MULPIC_TYPE_SIMPLE_NINE,
    MULPIC_TYPE_SIMPLE_TEN,
    
    MULPIC_TYPE_NUM,
    MULPIC_TYPE_ERROR
};
//////////////////////////////////////////////////////////////////////////
typedef struct tagMultiPicCreate
{
    u32  m_dwDevVersion;	//enBoardType��Ʒ�汾��
    u32  m_dwMode;			//ҵ��ģʽ����VMP_BASIC
}TMultiPicCreate;

//״̬
typedef struct tagMulPicStatus
{
	BOOL32  bMergeStart;	//�Ƿ�ʼ����ϳɣ�
	s32  byType;			//����ϳ�����
	u8   byCurChnNum;		//��ǰ����ϳɵ�ͨ����
	TVideoEncParam tVideoEncParam; //ͼ��������
}TMulPicStatus;

//ͳ��
typedef struct tagMulPicChnStatis
{
	u32  m_dwBitRate;        //����
	u32  m_dwPackNum;        //����
	u32  m_dwLosePackNum;    //ȱ�ٵİ���
    BOOL32 m_bWaitKeyFrame;
}TMulPicChnStatis;

typedef struct tagMulPicColor
{
	u8 RColor;    //R����
	u8 GColor;    //G����
	u8 BColor;    //B����
    u8 byDefault;
}TMulPicColor;

class CMultiPic;
class CHardMulPic
{
public:
	CHardMulPic();
	~CHardMulPic();
public:
    /*�������� Create
      ��    �ܣ� 
	  ��    ���� const TMulCreate& tInit
	  �� �� ֵ��	s32 
	  ˵    ���� */
	s32 Create(const TMultiPicCreate &tInit);


    /*�������� Destory
      ��    �ܣ� 
	  �� �� ֵ��s32 
	  ˵    ���� */
    s32 Destory(); 
    
    s32 SetData(s32 nChnl, const TFrameHeader &tFrame);
	s32 SetVidDataCallback(s32 nChnl, FRAMECALLBACK fVidData, void* pContext); /*������Ƶ���ݻص�*/
	
	s32 AddChannel(s32 nChnNo);
	s32 RemoveChannel(s32 nChnNo);
	
	s32 SetMulPicType(s32 nNewType);
	/* MPU2�в�Ҫʹ��startmerge�����ñ������������ΪSetVideoEncParam*/
	s32 StartMerge(TVideoEncParam* ptVideoEncParam, s32 nEncNum);	
	s32 StartMerge();
	s32 SetVideoEncParam(TVideoEncParam* ptVideoEncParam, s32 nEncNum);
	s32 StopMerge();

	s32 ChangeVideoEncParam(s32 nIndex, TVideoEncParam* ptVidEncParam);	//�ı�һ����Ƶ�������

	s32 ChangeBitRate(s32 nIndex, u16 wBitRate/*kbps*/);
	//ֻ֧��VMP_BASIC��VMP_ENHANCED��VMP_ADP_1080P30DEC����,���߼䲻�ɻ���
	s32 ChangeMode(u32 dwMode);
	s32 SetFastUpdata(s32 nIndex);
	
	s32 GetStatus(s32 nChnNo, TMulPicStatus &tMulPicStatus);
	s32 GetDecStatis(s32 nChnNo, TMulPicChnStatis &tMulPicStatis);
	s32 GetEncStatis(s32 nIndex, TMulPicChnStatis &tMulPicStatis);
	/*������ʱС������ʾ����,Ŀǰ֧��:
		EN_PLAY_LAST(��һ֡),
		EN_PLAY_BMP(pbyBmp ָ��),
		EN_PLAY_BMP_USR(pbyBmp ָ��),
		EN_PLAY_BLACK(����)*/
	s32 SetNoStreamBak(u32 dwBakType ,/*��enplayMode����*/ u8 *pbyBmp = NULL, u32 dwBmpLen = 0, u32 dwChnlId = MULPIC_MAX_CHNS);

	/*���û���ϳɱ�����ɫtBGDColor,�Լ��߿���ɫtSlidelineColor[MULPIC_MAX_CHNS]��
	��Ҫ�ı�߿���ɫʱ��ֻҪ�ı�tSlidelineColor[]��Ӧͨ����ֵ����*/
	s32 SetBGDAndSidelineColor(TMulPicColor tBGDColor,
           TMulPicColor atSlidelineColor[MULPIC_MAX_CHNS], BOOL32 bAddSlideLine = FALSE);

	//�ɵ�������vipͨ���߿����ɫ����SetBGDAndSidelineColor��������ͬʱʹ��
	s32 SetVipChnl(TMulPicColor tVipSlideColor,u32 dwChnl);
	s32 SetResizeMode(u32 dwMode);//ģʽ0:�Ӻڱߣ�1:�ñߣ�2:�ǵȱ����죬Ĭ��0
	s32 SetEncResizeMode(u32 dwMode);//ģʽ0:�Ӻڱߣ�1:�ñߣ�2:�ǵȱ����죬Ĭ��0
	/*��ʼ����̨��*/
	s32 StartAddIcon(s32 nChnNo, u8 *pbyBmp, u32 dwBmpLen, u32 dwXPos, u32 dwYPos, u32 dwWidth,
								 u32 dwHeight, TBackBGDColor tBackBGDColor, u32 dwClarity);

	/* ֹͣ����̨�� */
	s32 StopAddIcon(s32 nChnNo);
	/*��ͣ������*/
	void StartEnc(u32 dwEncChnlId);
	void StopEnc(u32 dwEncChnlId);

    //�����ã����ú������ʷ���У�ĳЩ�ײ�С����֮��ı߿�
    //dwMergeStyle : ��������ԵĻ���ϳɷ��
    //pdwBorders   : �������Ҫ���Ե����б߿��
    //dwBorderNum  : ��Ҫ���Եı߿���
    //��: ���ʷ��MULPIC_TYPE_SIMPLE_FIVE�����ĸ�С���棬�ĸ�С����֮����3���߿�,
    //�����Ҫ�������еĵ�1����3���߿���ô: dwMergeStyle=MULPIC_TYPE_FIVE; 
    //dwBorderNum=2; pdwBorders=new u32[2]; pdwBorders[0]=1; pdwBorders[1]=3;
    s32 SetIgrDrawBorders(u32 dwMergeStyle, u32* pdwBorders, u32 dwBorderNum);
    
private:
    CMultiPic*  m_pMulPic;
};
/*
s32 HardMPUInit(u32 nMode); //nMode:enInitMode
s32 HardMPUInitDev(u32 nEncTos, u32 nDecTos, u32 nDspNum);
s32 HardMPUDestroy();

//DSP��ʼ�������٣�MCU�û�����Ҫ����
s32 HardMPUInitDSP();
s32 HardMPUDestroy();
*/
#endif /*_KDVMULPIC_HD_H_*/





















