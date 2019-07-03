/*******************************************************************************
 *  ģ����   : �ն�ҵ��                                                        *
 *  �ļ���   : mtsysapi.h                                                      *
 *  ����ļ� :                                                                 *
 *  ʵ�ֹ��� : �ṩ�ն�ҵ��ϵ�����ӿں���                                      *
 *  ����     : ������                                                          *
 *  �汾     : V3.0  Copyright(c) 1997-2005 KDC, All rights reserved.          *
 *                                                                             *
 *    =======================================================================  *
 *  �޸ļ�¼:                                                                  *
 *    ��  ��      �汾        �޸���      �޸�����                             *
 *  2005/7/20     4.0         ������      ����                                 *
 *                                                                             *
 *******************************************************************************/

#include "osp.h"
#include "tptype.h"
#include "tpstruct.h"
#include "mthint.h"
#ifndef _MT_SYS_API_H_
#define _MT_SYS_API_H_

#ifdef WIN32
#define MTAPI   extern "C"			__declspec(dllexport)
#else //#ifdef ( _VXWORKS_ || _LINUX_ )
#define MTAPI   extern "C"		
#endif

//�ն˴�ӡ����
extern "C" void cnPrintf( char *szFormat, ... );

typedef struct tagTPingRtn
{
	s32 nTimeOut;
    s32 nReachable;  //�Ƿ񵽴�
    s32 nTTL;
    s32 nTripTime;
}TPingRtn;

//ϵͳ����״̬
enum EmMtSysUpdateStatus
{
	emSysUpdateInit = 0,
	emSysUpdateProcessing,
	emSysUpdateSucceed,
	emSysUpdateFail	
};

typedef struct tagTModuleInit
{
	void (  *install   ) ( void );
	BOOL (  *startapp  ) ( void );
	void (  *stopapp   ) ( void );
	void (  *uninstall ) ( void );
}TModuleInit, *PTModuleInit;

API void mtStartCodec();
API void mtStopCodec();
API void mtRegCodec( BOOL ( *startapp ) ( void ) ,void ( *stopapp ) ( void ) );

API void mtStartService();
API void mtStopService();
API void mtRegService( BOOL ( *startapp ) ( void ) ,void ( *stopapp ) ( void ) );



API void mtStartUE();
API void mtStopUE();
API void mtRegUE( BOOL ( *startapp ) ( void ) ,void ( *stopapp ) ( void ) );

API void mtStartTPReg();
API void mtStopTPReg();
API void mtRegTPReg( BOOL ( *startapp ) ( void ) ,void ( *stopapp ) ( void ) );


MTAPI EmMtModel GetMtModel();//��ȡ�ն��ͺ�

MTAPI EmFileSys GetFileSys();//��ȡ�ն��ļ�ϵͳ
	
BOOL mtMakeDir(const s8* path );
BOOL mtPathExist(const s8* path);
s8* mtGetFileName(EmMtFile emFile );
MTAPI BOOL HardwareInit();//Ӳ����ʼ��


#if defined(_VXWORKS_) || defined(_LINUX_)

API BOOL InitDSP();
API void mtPing( s8* pchHost, s32 nPacketSize, s32 nTTL, s32 nTimeout, TPingRtn* ptReturn );

#endif//

    /*********************************************/
    /*                �弶���ú���               */
    /*********************************************/

API void mtstart();
API void mtquit();

//����ת��
u8 mtMapAudioType(EmTpAudioFormat format );//Mt������Ƶ��ʽת��ΪKdvDef�е���Ƶ����

//mtsysapi��ʼ��
BOOL mtSysApiInit();
void mtSysApiExit();


//������Ƶ���ͻ�ȡ��������
u16 mtGetBitrate( EmTpAudioFormat emFormat );
//��̬�غ�
u8 mtGetDynamicPayload( EmTpVideoFormat emFormat );

enum EmPathList{
	emFtpPath = 0,
	emRamdiskConfPath,
	emConfPath,
	emUserInfoPath,
	emWebfilesPath,
	emWebDocPath,
	emDataPath,
	emResPath,
	emPathListEnd
};

void mtStartSpeaker( BOOL bOpen ); // �����ر�������

//8010�ն˵�ι������, xjx_080310
BOOL mtOpenWdGuard(u32 dwNoticeTimeout);
BOOL mtCloseWdGuard(void);
BOOL mtNoticeWdGuard(void);
BOOL mtWdGuardIsOpened(void);
s32 mtSetVidOffsetParam( u32 dwInterface, s32 dwHoff, s32 dwVoff );
void MtmpStartInstallSemphore();
void MtmpStartUninstallSemphore();
void TransAddressFromTpToOsp( const TTPTransAddr &tTPTransAddr, TOspNetAddr &tOspNetAddr);
void TransAddressFromOspToTp( const TOspNetAddr &tOspNetAddr, TTPTransAddr &tTPTransAddr);
void PrintOspNetAddr( const TOspNetAddr tOspNetAddr);
BOOL OspNetAddrCmp( const TOspNetAddr tOspNetAddr, const TOspNetAddr tOspNetAddr_2);
BOOL OspNetAddrIsValid( const TOspNetAddr tOspNetAddr);
void cnPrintOspNetAddr( const TOspNetAddr tOspNetAddr);
BOOL OspNetAddrCmpPort( const TOspNetAddr tOspNetAddr, const TOspNetAddr tOspNetAddr_2);
BOOL OspNetAddrCmpIsZore( const TOspNetAddr tOspNetAddr);

#endif/*!_MT_SYS_API_H_*/
