/*****************************************************************************
   ģ����      : DataSwitch
   �ļ���      : dataswitch.h
   ����ļ�    :
   �ļ�ʵ�ֹ���: DataSwitchģ��ӿں�������
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2005/03/18  4.0         ��־ҵ        ����
   2005/08/10  4.0         ��־ҵ        ʵ��3.6�������Ĺ���
   2014/06/20  5.0         ������        ʵ��rtpswitch����
   2014/10/09  5.1         ������        �ϲ�����kdv��movision��dataswitch
******************************************************************************/

#ifndef DATASWITCH_H
#define DATASWITCH_H

#define DSVERSION       "DataSwitch.TS.6.0(Support IPv6)"

#include "osp.h"
#include "kdvtype.h"
#include "rtp_endpoint_id.h"     //rtp��ʶ�Ķ���ͽӿ�

#ifdef KDVTYPE_LEGACY_H	
#define  DATASWITCH_LEGACY_H	
#endif


/* DataSwitch ��� */
#define DSID    u32

#define DSID_LEN          16
#define DSID_MASK         0xffff0000
#define RTPID_MASK        0x0000ffff

#define DS_GET_DSID(rtpId) \
    ((((rtpId) & DSID_MASK) >> DSID_LEN) + 1)

#define DS_GET_DSRTPID(rtpId) \
    ((rtpId) & RTPID_MASK)

/*DataSwitch ����ֵ*/
#define DS_ERATELIMIT   2
#define DSOK    1
#define DSERROR 0

#define INVALID_DSID  0xffffffff   /*��Ч�ľ��ֵ*/

#if (defined _MSC_VER)
#include <Winsock2.h>
#include <ws2tcpip.h>
//TODO: inet_pton�Ĺ����Ƶ�OSP�����
#ifndef inet_pton
#define inet_pton
#endif
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#endif

typedef struct tagDsGlobalParam
{
	tagDsGlobalParam()
	{
		m_dwRecvBuff = 2 * 1024 * 1024 ;
		m_dwSendBuff = 2 * 1024 * 1024 ;
	}

	u32	m_dwRecvBuff;
	u32	m_dwSendBuff;
} TDsGlobalparam;

API void dsSetGlobalParam(TDsGlobalparam tParam );


#define SENDMEM_MAX_MODLEN        (u8)32        // ����ʱ���������޸ĳ���

API void dsSetApiTimeOut(s32 timeout);
/**********************************************************
 * ����: dsSetCapacity                                    *
 * ����: ��������(ֻ���ڴ�������ģ��֮ǰ����)             *
 * ����: dwMaxRcvGrp        - ����������                *
 *       dwMaxSndMmbPerRcvGrp  - ÿһ�����������Ŀ����   *
 * ���: ��                                               *
 * ����: �ɹ�����DSOK ����DSERROR                         *
 **********************************************************/
API u32 dsSetCapacity( u32 dwMaxRcvGrp, u32 dwMaxSndMmbPerRcvGrp );

/************************************************************
 * ��������dsCreate
 *
 * ���ܣ�  ����DataSwitchģ��
 *
 * ʵ��˵����
 * Dataswitch֧�֡����û�����ÿ�ε���dsCreate�ͻ᷵��һ��
 * �û���ʶ����ӡ�ɾ��ʱ��Ҫƥ���û���־��ת��ʱ�򲻿��ǡ�
 *
 * ����ֵ��
 * @return INVALID_DSID: ��ʾʧ�� ; ����ɹ�
 ************************************************************/
API DSID dsCreate();

/************************************************************
 * ��������dsDestroy
 *
 * ���ܣ� ��ֹDataSwitch������
 *
 * ʵ��˵����
 * һ��ɾ��һ���û���ֱ�������û���ɾ����������Դ��ȫ�ͷš�
 *
 * ����˵����
 * @param dsId  - �û���ʶ
 *
 * ����ֵ��
 ************************************************************/
API void dsDestroy( DSID dsId );

enum {
    DS_NONE_FLAG			= 0,				//�ޱ�־
	DS_RTP_RMV_EXT			= 0x1 << 0,			//ת��ʱ��ɾ��RTP��չͷ�����Ŀ��ʹ��
    DS_SKIP_POLICY_ROUTING  = 0x1 << 1,         //��ֹ���ں˲���·�ɶ���
	DS_IS_RTCP_RULE         = 0x1 << 2,         //ȷ��ΪRTCP�������ش��������Ҫ�޸�rtp�ش���ַ
};

typedef TOspNetAddr dsNetAddr;

#define DS_IS_VALID_ADDR(netaddr) OSP_IS_VALID_LOCAL_ADDR(netaddr)
#define DS_IS_VALID_LOCAL_ADDR(netaddr) OSP_IS_VALID_LOCAL_ADDR(netaddr)
#define DS_IS_VALID_REMOTE_ADDR(netaddr) OSP_IS_VALID_REMOTE_ADDR(netaddr)
/*
#define DS_IS_VALID_ADDR(netaddr)   \
    ((netaddr) &&   \
    (((netaddr)->v4addr.sin_family == AF_INET && (netaddr)->v4addr.sin_port) || \
    ((netaddr)->v6addr.sin6_family == AF_INET6 && (netaddr)->v6addr.sin6_port)))

#define DS_IS_VALID_LOCAL_ADDR(netaddr)   \
    ((netaddr) &&   \
    (((netaddr)->v4addr.sin_family == AF_INET && (netaddr)->v4addr.sin_port) || \
    ((netaddr)->v6addr.sin6_family == AF_INET6 && (netaddr)->v6addr.sin6_port)))

#define DS_IS_VALID_REMOTE_ADDR(netaddr)    \
    ((netaddr) &&   \
    (((netaddr)->v4addr.sin_family == AF_INET &&    \
        (netaddr)->v4addr.sin_addr.s_addr && (netaddr)->v4addr.sin_port) || \
    ((netaddr)->v6addr.sin6_family == AF_INET6 &&   \
        (netaddr)->v6addr.sin6_port)))
*/

/* �ṩ�����ֽ����ַ���õ�dsNetAddr�ṹ�� */
#define DS_SET_NETADDR_ADDR(netaddr, type, address)    \
    do {    \
        switch(type) {    \
        case AF_INET:   \
            (netaddr)->v4addr.sin_family = (type);      \
            (netaddr)->v4addr.sin_addr.s_addr = (address);   \
            break;      \
        case AF_INET6:  \
            (netaddr)->v6addr.sin6_family = (type);     \
            break;  \
        default:    \
            break;  \
        }   \
    } while(0)

/* �ṩ�����ַ�ַ������õ�dsNetAddr�ṹ�� */
#define DS_SET_NETADDR_ADDR_STR(netaddr, type, address)    \
    do {    \
        switch(type) {      \
        case AF_INET:       \
            (netaddr)->v4addr.sin_family = (type);      \
            if (address)    \
                OspPton(type, address, &((netaddr)->v4addr.sin_addr.s_addr));\
            else        \
                (netaddr)->v4addr.sin_addr.s_addr = INADDR_ANY;    \
            break;      \
        case AF_INET6:  \
            (netaddr)->v6addr.sin6_family = (type);     \
            if (address)    \
                OspPton(type, address, &((netaddr)->v6addr.sin6_addr.s6_addr));  \
            else    \
                memcpy(&(netaddr)->v6addr.sin6_addr, &in6addr_any, sizeof(in6addr_any));  \
            break;  \
        default:    \
            break;  \
        }   \
    } while(0)

/* �ṩ������˿ں����õ�dsNetAddr �� */
#define DS_SET_NETADDR_PORT(netaddr, type, port)    \
    do {    \
        switch(type) {    \
        case AF_INET:   \
            (netaddr)->v4addr.sin_family = (type);      \
            (netaddr)->v4addr.sin_port = htons(port);   \
            break;      \
        case AF_INET6:  \
            (netaddr)->v6addr.sin6_family = (type);     \
            (netaddr)->v6addr.sin6_port = htons(port);  \
            break;  \
        default:    \
            break;  \
        }   \
    } while(0)

/* -------------------- ��ʼ����rtpswitch -------------------*/
#define INVALID_RTPSWITCHID ((u32)-1)

//Ϊ�˶�ʵ���� DSRTPSID�����Ϊ 
/*
 *  31---------------------15-----------------------0
 *  |    DSID               | RTPID                 |
 *  -------------------------------------------------
 */
typedef u32		DSRTPSID;

#define DS_MAX_SECKEY_LEN (512)

//��Կ����
#define DS_SECKEY_LEN_AES_256_GCM (44)
#define DS_SECKEY_LEN_AES_128_GCM (28)
#define DS_SECKEY_LEN_AES_256_ICM (46)
#define DS_SECKEY_LEN_AES_128_ICM (30)
#define DS_SECKEY_LEN_SM4_128_CM  (30)
#define DS_SECKEY_LEN_SM1_128_CM  (30)

#define DS_SECKEY_LEN_AES_256_H235 (32)
#define DS_SECKEY_LEN_AES_192_H235 (28)
#define DS_SECKEY_LEN_AES_128_H235 (16)

//auth tag ����
#define DS_AUTH_LEN_80 (80)
#define DS_AUTH_LEN_32 (32)

typedef enum {
	DS_SECKEY_TYPE_UNDEFINED	= 0,
    DS_SECKEY_TYPE_STATIC		= 1, 
	DS_SECKEY_TYPE_DYNAMIC		= 2, 
	DS_SECKEY_TYPE_DTLS			= 3,
	DS_SECKEY_TYPE_MAX          = 4
} dsSecKeyTypes;

typedef enum {
    DS_REKEY_MODE_NULL  = 0, 
    DS_REKEY_MODE_BY_ID = 1, 
    DS_REKEY_MODE_BY_SN = 2, 
    DS_REKEY_MODE_MAX,       
} dsCryptReKeyMode;    

typedef struct dsCryptRekeyByidCfg {
    u8 rekey_rate;
    u64 intv;
    u16 id_len;
    u16 len_after_id;	//ҵ����Ҫ��д
    u8 *id_buf;			//ҵ����Ҫ��д
} dsCryptRekeyByidCfg;

typedef struct dsCryptRekeyBySNCfg {
    u16 sn_intv;
} dsCryptRekeyBySNCfg;

typedef struct dsCryptRekeyCfg {
    u8 rekey_mode;
    void *ctx;
    void *alloc_key;
    void *find_key;

    union {
        dsCryptRekeyByidCfg byid;
        dsCryptRekeyBySNCfg bysn;
    } cfg;

} dsCryptRekeyCfg;


//���ܻ�ȡkey�Ļص�
typedef u16 (*dsReKeyAllocCBById)(void* pContext, u8* pKey, u16* pKeyLen, u8* pKeyId, u16* pKeyIdLen);
//���ܻ�ȡkey�Ļص�
typedef u16 (*dsReKeyFindCBById)(void* pContext, u8* pKey, u16* pKeyLen, u8* pKeyId, u16 pKeyIdLen);

//���ܻ�ȡkey�Ļص�
typedef u16 (*dsReKeyAllocCBBySn)(void* pContext, u8* pKey, u16* pKeyLen, u64 sn, BOOL32 *rekeyChange);
//���ܻ�ȡkey�Ļص�
typedef u16 (*dsReKeyFindCBBySn)(void* pContext, u8* pKey, u16* pKeyLen, u64 sn, BOOL32 *rekeyChange);

typedef struct {
  u8        keytype;  
  u16		keylen;
  u8		key[DS_MAX_SECKEY_LEN];  

  dsCryptRekeyCfg rekeyCfg;
} dsSecKey; 

#define DS_CIPHER_ENABLE      ((u8)1)
#define DS_CIPHER_DISABLE     ((u8)0)

#define DS_CIPHERPOLICY_NONE  ((u8)0)
#define DS_CIPHERPOLICY_H235  ((u8)1)
#define DS_CIPHERPOLICY_SRTP  ((u8)2)
#define DS_CIPHERPOLICY_MAX   ((u8)3)

//�㷨����
typedef enum {
	DS_SEC_ALG_NONE		= 0,
	DS_SEC_ALG_AES_128	= 1,
	DS_SEC_ALG_AES_192	= 2,
	DS_SEC_ALG_AES_256	= 3,
	DS_SEC_ALG_SM_4     = 4,
	DS_SEC_ALG_SM_1     = 5,
	DS_SEC_ALG_MAX      = 6
}dsCipherAlgId;

typedef enum {
	DS_AUTH_ALG_NONE		= 0,
	DS_AUTH_ALG_SHA1		= 1,
	DS_AUTH_ALG_SM_3        = 6,
	DS_AUTH_ALG_MAX         = 7
}dsAuthAlgId;


//ģʽ
typedef enum {
    SRTP_AES_ICM	= 1, 
	SRTP_AES_GCM	= 2,
	
	H235_AES_CBC	= 3,
	H235_AES_ECB	= 4,
	H235_AES_CFB1	= 5,

	SRTP_SM4_CM     = 6,

	SRTP_SM1_CM     = 7,
	DS_CRYPTO_TYPE_MAX = 8,
	SRTP_UNDEFINED  = 0,
} dsSrtpCryptoTypes;


typedef struct dsCipher{
  u8        enable;//�Ƿ����üӽ��� 1������ 0��������
  u8		policy;//ģʽ 0: none 1��H235 2: srtp 
  u8		isCipher;//�Ƿ�ӽ��� 1: �ӽ��� 0: ���ӽ���  
  u32		cipherAlgId;//�㷨id   
  u8        cipherMod;//���ܹ���ģʽ 
  //u8        ext_cipher;//�Ƿ������չͷ
  dsSecKey  seckey;//��Կ
  u8		isAuth;//�Ƿ���֤
  u32		authAlgId;//�㷨id
  u8        authTagLen;//auth tag ����
  dsSecKey  authKey;//��֤��Կ 
  dsCipher* next;
} dsCipher;

#define DS_EP_ATTR_MAX_SIZE (2048)
#define DS_EP_PATTR_MAX_SIZE (80)

//�ն�����
typedef union {
	u8 attr_data[DS_EP_PATTR_MAX_SIZE];
	void* align;
}dsEpAttr_t;

typedef enum {
    DS_SYNC_ADAPTER_INVALID = 0,
    DS_SYNC_ADAPTER_STD_TO_SSRCTS = 1,
    DS_SYNC_ADAPTER_SSRCTS_TO_STD = 2,  
} dsSyncAdapterType;

typedef enum {
    DS_MEDIA_TYPE_INVALID = 0,
    DS_MEDIA_TYPE_VIDEO = 1,
    DS_MEDIA_TYPE_AUDIO = 2,
    DS_MEDIA_TYPE_TEXT = 3,
	DS_MEDIA_TYPE_CTL = 4,
} dsMediaType;

/* rtp�ն˵���Ϣ */
typedef struct {
    dsRtpEndpointId id;     //rtp �ն�id
    dsNetAddr addr;         //rtp �ն˵������ַ
    s32 ifindex;            //rtp �ն˵���������
    dsMediaType mediaType;

	dsEpAttr_t attr;        //�ն�����
} dsRtpEndpoint;


typedef enum {    
	DS_FRAME_CB_EV       = 0x00000001, //֡�¼�֪ͨ
	DS_UNDEFINED_EV      = 0x00000000, 
} dsCBEvType;

// �ն��¼�֪ͨ�ص����� 

typedef struct {
	u8	ptype;
	u32 timestamp;
	u32 ssrc;
	u16 sequence;
} dsRtpInf;

typedef enum {
	DS_EVT_CB_SSRC_CHANGE       	= 0x00000001,		//Դ�б���

    DS_EVT_CB_KEYFRAME_DETECT   	= 0x00000002,		//Դ�б��� �����ؼ�֡

	DS_EVT_CB_UNDEFINED			    = 0x00000000, 
} dsFrameEvtCBType;

typedef struct {
   u32              type;    //�¼����� �ο� dsFrameEvtCBType��
                             //���Զ������ : type=DS_EVT_CB_SSRC_CHANGE|DS_EVT_CB_KEYFRAME_DETECT
   dsRtpEndpoint	src;     //udp/rtp����Դ��Ϣ
   dsRtpEndpoint	dst;     //udp/rtp����Ŀ����Ϣ
   DSRTPSID         dsRtpSId;//�������ʶ
   dsRtpInf			rtpInf;  //rtp��Ϣ
   BOOL32			bIFrame; //�Ƿ�ؼ�֡
   u8				EvtSrc;  //�¼�Դ srcEp 1 /dstEp : 2
} dsFrameEvtCBParam;

// �ն˻ص��������� 
typedef struct {
   BOOL32	bIsSwitch;//�Ƿ�ת��
} dsFrameEvtCBRetParam;

typedef void (*dsFrameEvtCB)(void					 *pAppData,			//�û��Զ���Ļص������Ĳ���
						     dsFrameEvtCBParam       *cbEvtParam,		//�ص��¼�����
						     dsFrameEvtCBRetParam    *cbEvtRetParam     //�ص����ز���
	                        );

// �ն��¼�֪ͨ�ص����� 
typedef struct dsFrameEvtCBAttr{
  u32                   type;               //�¼����� �ο� dsFrameEvtCBType��
                                            //���Զ������ : type=DS_EVT_CB_SSRC_CHANGE|DS_EVT_CB_KEYFRAME_DETECT
  void *				pAppData;			//�û��Զ���Ļص������Ĳ���
  dsFrameEvtCB			pdsFrameEvtCB;	    //�ص�����ָ��
  dsFrameEvtCBAttr*		next;			    //ҵ����Ҫ����
} dsFrameEvtCBAttr;

// �ն�PTֵ
typedef struct dsFixedPtAttr{
 u8				ptype;				//�غ�����
 dsFixedPtAttr*	next;				//ҵ����Ҫ����
} dsFixedPtAttr;

// rtp����������
typedef enum {
	DS_RTP_RCVGRP_MUX         = 0x00000001,		//�����й����Ŀ����ƥ�����й����Դ

	DS_RTP_RCVGRP_NONE	      = 0x00000000,		//������
} dsRtpRcvGrpType;

// rtp�������� �����ʹ��
#define     DS_RTP_RULE_NONE		((u64)0x0000000000000000)		//������
#define		DS_RULE_RTP				((u64)0x0000000000000001)		//RTP����
#define		DS_RULE_RTCP			((u64)0x0000000000000002)		//RTCP����
#define		DS_RULE_DOWN			((u64)0x0000000000000004)		//���й���,�� DS_RTP_RCVGRP_MUX ���͵Ľ������У��ù����Ŀ��Ϊ���������Դ
#define		DS_RULE_UP		        ((u64)0x0000000000000008)       //���й���,�� DS_RTP_RCVGRP_MUX ���͵Ľ������У��ù����ԴΪDS_RULE_DOWN�����Ŀ��
#define		DS_RULE_VIDEO			((u64)0x0000000000000010)       //��Ƶ����
#define		DS_RULE_AUDIO			((u64)0x0000000000000020)       //��Ƶ����
#define     DS_RULE_DATA            ((u64)0x0000000000000040)       //Զң����...


/* -------------------- ��ʼ����ͳ������ -------------------*/
//ͳ��������ض���
/* base */
//ȡֵ��Χ0~100������ֵ, ����Ϊ1%
typedef struct dsStatisPercent {
    u8 cur;
    u8 avg;
    u8 max;
} dsStatisPercent;

//ÿ���ڵ�����
typedef struct dsStatisRate {
    u32 cur;
    u32 avg;
    u32 max;
} dsStatisRate;

/* udp */
typedef struct dsUdpPktStatis {
    u64 totalPkts;
    dsStatisRate pktRate;
    u64 totalBytes;
    dsStatisRate bytesRate;
} dsUdpPktStatis;

typedef struct dsUdpErrStatis {
    u64 totalErrCnt;

    u16 sockErrCnt;
    u16 queueErrCnt;
    u16 checksumErrCnt;
} dsUdpErrStatis;

typedef struct dsUdpDropStatis {
    u64 totalDropPkt;
    u16 dropOverSizePkt;
} dsUdpDropStatis;

typedef struct dsUdpModStatis {
    u64 totalModPkts;
    u16 addrModPkts;
} dsUdpModStatis;

typedef struct dsUdpEndpointStatis {
    dsUdpPktStatis pkt;
    
    dsUdpErrStatis errors;
    dsUdpDropStatis dropped;
    dsUdpModStatis modified;
} dsUdpEndpointStatis;

/* rtp */
typedef struct dsRtpLossStatis {
    u32 lossCnt;
    u32 expected;
    dsStatisPercent lossPercent;
} dsRtpLossStatis;

typedef struct dsRtpErrStatis {
    u64 totalErrCnt;

    u16 cipherErrCnt;
    u16 queueErrCnt;
    u16 checksumErrCnt;
} dsRtpErrStatis;

typedef struct dsRtpPktStatis {
    u16 totalFecPkt;
    u16 totalRtxPkt;
    u16 totalRedPkt;
} dsRtpPktStatis;

typedef struct dsRtpDropStatis {
    u64 totalDropPkt;
    u16 dropFecPkt;
    u16 dropRedPkt;
	u16 dropBindPkt;
    u16 dropOverSizePkt;
	u16 dropMuxInvalidAddrPkt;
} dsRtpDropStatis;

typedef struct dsRtpModStatis {
    u64 totalModPkts;
    u16 rtpRmvExtHdr;
    u16 rtpRmvId;
} dsRtpModStatis;

typedef struct dsRtpReorderStatis {
    u64 totalCnt;
} dsRtpReorderStatis;

typedef struct dsRtpJitterStatis {
    u64 totalCnt;
} dsRtpJitterStatis;

typedef struct dsRtpEndpointStatis {
    dsUdpEndpointStatis udpStatis;

    dsRtpPktStatis pkts;
    dsRtpLossStatis loss;

    dsRtpErrStatis errors;
    dsRtpDropStatis dropped;
    dsRtpModStatis modified;
    dsRtpReorderStatis reorder;
    dsRtpJitterStatis jitter;
} dsRtpEndpointStatis;
/* -------------------- ��������ͳ������ -------------------*/


#define DS_INIT_RTP_ENDPOINT(endpoint)  \
    do {    \
        (endpoint)->id = DS_RTP_ANY_ID; \
        (endpoint)->ifindex = -1;   \
        (endpoint)->mediaType = DS_MEDIA_TYPE_INVALID; \
        memset(&(endpoint)->addr, 0, sizeof((endpoint)->addr));  \
		memset(&(endpoint)->attr, 0, sizeof((endpoint)->attr));  \
    } while(0)

#define DS_SYNC_BUF_LEN (256)

typedef struct dsSyncAdapterAttr {
    dsSyncAdapterType type;
    char grpId[DS_SYNC_BUF_LEN];

    dsSyncAdapterAttr *next; //ҵ����Ҫ����
} dsSyncAdapterAttr;

//���ö���ͬ��ת������
//��������ep��id��mediaType�ֶκ��������ӿ�
API u32 dsAllocEpAttrSyncAdapter(dsRtpEndpoint *ep, const dsSyncAdapterAttr * const syncAttr);

//����Ŀ��Ϊdump,��Ŀ����Ч
API u32 dsAllocEpAttrDump(dsRtpEndpoint * dstEp);

//����Ŀ�Ĳ�ת��FEC,��Ŀ����Ч
API u32 dsAllocEpAttrDisFEC(dsRtpEndpoint * dstEp);

//����Ŀ����Ҫ�޸�����,��Ŀ����Ч
API u32 dsAllocEpAttrMdyRtpData(dsRtpEndpoint * dstEp);

//�����ն˼�������
API u32 dsAllocEpAttrCipher( dsRtpEndpoint * ep, const dsCipher * const cipher );

//�����ն��¼�֪ͨ�ص�,��Դ��Ч
API u32 dsAllocEpAttrFrameEvtCB( dsRtpEndpoint * srcEp, const dsFrameEvtCBAttr * const frameEvtCBAttr );

//�����ն˹̶�SSRC,��Ŀ����Ч
API u32 dsAllocEpAttrFixedSSRC( dsRtpEndpoint * dstEp);

//�����ն��޸�PTֵ,��Ŀ����Ч
API u32 dsAllocEpAttrFixedPT( dsRtpEndpoint * dstEp, const dsFixedPtAttr * const fixedPt );

//�����ն˹��˶౶���͵�rtp��
API u32 dsAllocEpAttrFilterRED(dsRtpEndpoint * dstEp);

//�ͷ��ն�������Դ
API u32 dsFreeEpAttr(dsRtpEndpoint * ep);

/****************************************************************
 * ����: dsCreateRtpRtcpSwitch()
 * ����: ��ĳ��ip��ַ�Ͷ˿ڴ���rtpswitch
 * ����:
 *   dsid: dataswitch ʵ��id
 *   addr: Ҫ����rtpswitch�ĵ�ַ�Ͷ˿���Ϣ
 * ���:
 *   ����ֵdsrtpswitch id��������INVALID_RTPSWITCHID
 ****************************************************************/
API DSRTPSID dsCreateRtpRtcpSwitch(DSID dsid, dsNetAddr *addr, dsRtpRcvGrpType rcvGrpType = DS_RTP_RCVGRP_NONE);


/****************************************************************
 * ����: dsAddRtpSwitchRule() / dsAddRtcpSwitchRule()
 * ����: ��ĳ��rtpswitch�����rtp��������
 * ����:
 *   id: rtpswitch��id����ʶ�������յ�ip��ַ�Ͷ˿�
 *   src: ������Դ��Ϣ������ԭip��ַ�Ͷ˿ڣ�ԭendpoint id��Ϣ��
 *        ���������ip��ַ�Ͷ˿ڣ��򲻳���ƥ���ַ�Ͷ˿�
 *        ���������endpoint id��Ϣ����ƥ��endpoint id��Ϣ
 *        ���src == NULL, �յ������а���ƥ���������.
 *   modifier: ��������ת�����޸ĵ�Դ��Ϣ, ��� == NULL, ���޸�
 *   dst: ����ת������Ŀ����Ϣ������Ŀ��ip�Ͷ˿ڣ�Ŀ��endpoint��
 *   priority: ��������ȼ�(1~100), Խ�����ȼ�Խ�ߡ�
 * ���:
 *   ����ֵDSOK��DSERROR.
 ****************************************************************/
API u32 dsAddRtpSwitchRule(
    DSRTPSID id,
    dsRtpEndpoint *src,
    dsRtpEndpoint *modifier,
    dsRtpEndpoint *dst,
    u32 priority);

API u32 dsAddRtcpSwitchRule(
    DSRTPSID id,
    dsRtpEndpoint *src,
    dsRtpEndpoint *modifier,
    dsRtpEndpoint *dst,
    u32 priority);

API u32 dsAddRtpRtcpSwitchRule(
    DSRTPSID id,
    dsRtpEndpoint *src,
    dsRtpEndpoint *modifier,
    dsRtpEndpoint *dst,
    u32 priority,
	u64 ruleType);
/****************************************************************
 * ����: dsRemoveRtpSwitchRule() / dsRemoveRtcpSwitchRule()
 * ����: ��ĳ��rtpswitch��ɾ��rtp��������
 * ����:
 *   id: �������ڵ�rtpswitch��id.
 *   src: ������Դ��Ϣ������ԭip��ַ�Ͷ˿ڣ�ԭendpoint id��Ϣ��
 *        ���src == NULL, ƥ������Դ
 *   modifier: ��������ת�����޸ĵ�Դ��Ϣ, ��� == NULL, ���޸�
 *   dst: ����ת������Ŀ����Ϣ������Ŀ��ip�Ͷ˿ڣ�Ŀ��endpoint��
 * ���:
 *   ����ֵDSOK��DSERROR.
 ****************************************************************/
API u32 dsRemoveRtpSwitchRule(
    DSRTPSID id,
    dsRtpEndpoint *src,
    dsRtpEndpoint *modifier,
    dsRtpEndpoint *dst);

API u32 dsRemoveRtcpSwitchRule(
    DSRTPSID id,
    dsRtpEndpoint *src,
    dsRtpEndpoint *modifier,
    dsRtpEndpoint *dst);

API u32 dsRemoveRtpRtcpSwitchRule(
    DSRTPSID id,
    dsRtpEndpoint *src,
    dsRtpEndpoint *modifier,
    dsRtpEndpoint *dst,
	u64 ruleType);

/****************************************************************
 * ����: dsDestroyRtpSwitch()
 * ����: ���һ��rtpswitch
 * ����:
 *   dsid: dataswitch ʵ��id
 *   id:   rtp switch id
 * ���:
 *   ����ֵDSOK��DSERROR.
 ****************************************************************/
 API u32 dsDestroyRtpSwitch(DSID dsid, DSRTPSID id);


/*---------------- ����rtpswitch ͳ����Ϣ�ӿ� ��ʼ -------------------------*/
/****************************************************************
 * ����: dsGetStatistics()
 * ����: ��ȡdsid��Ӧ��RTPRTCP��ת����ͳ������(����RtpRtcpSwitchʵ����һ��)
 * ����:
 *   dsid: dataswitch ʵ��id
 *   statisSrc: ����rtpת�����ܽ���ͳ����Ϣ, ���ָ��ָ����ڴ���������Ч�ڴ��
 *   statisDst: ����rtpת�����ܷ���ͳ����Ϣ, ���ָ��ָ����ڴ���������Ч�ڴ��
 * ���:
 *   ����ֵDSOK��DSERROR.
 ****************************************************************/
API s32 dsGetStatistics(DSID dsid, dsRtpEndpointStatis *srcStatis, dsRtpEndpointStatis *dstStatis);

/****************************************************************
 * ����: dsGetRtpRtcpSwitchStatistics()
 * ����: ��ȡrtpswitch��ĳ��������շ�ͳ����Ϣ
 * ����:
 *   id: rtpswitch��id����ʶ�������յ�ip��ַ�Ͷ˿�
 *   lclStatis[out]: ����������Ľ���ͳ����Ϣ, ���ָ��ָ����ڴ���������Ч�ڴ��
 * ���:
 *   ����ֵDSOK��DSERROR.
 ****************************************************************/
API s32 dsGetRtpRtcpSwitchStatistics(
    DSRTPSID id,
    dsRtpEndpointStatis *lclStatis);

/****************************************************************
 * ����: dsGetRtpSwitchRuleStatistics()
 * ����: ��ȡrtpswitch��ĳ��������շ�ͳ����Ϣ
 * ����:
 *   id: rtpswitch��id����ʶ�������յ�ip��ַ�Ͷ˿�
 *   epSrc[in]: dsAddRtpSwitchRule �����src�ṹ
 *   epDst[in]: dsAddRtpSwitchRule �����dst�ṹ
 *   statisSrc[out]: ��������Ľ���ͳ����Ϣ, ���ָ��ָ����ڴ���������Ч�ڴ��
 *   statisDst[out]: ��������ķ���ͳ����Ϣ, ���ָ��ָ����ڴ���������Ч�ڴ��
 * ���:
 *   ����ֵDSOK��DSERROR.
 ****************************************************************/
API s32 dsGetRtpSwitchRuleStatistics(
    DSRTPSID id,
    dsRtpEndpoint *srcEp,
    dsRtpEndpoint *dstEp,
    dsRtpEndpointStatis *srcStatis,
    dsRtpEndpointStatis *dstStatis);
/*---------------- ����rtpswitch ͳ����Ϣ�ӿ� ���� -------------------------*/



/*---------------- ����rtpswitch ���� -------------------------*/

/*---------------- ����sipswitch ��ʼ -------------------------*/
#define INVALID_SIPSWITCHID ((u32)-1)

 //Ϊ�˶�ʵ���� DSSIPSID�����Ϊ 
/*
 *  31---------------------15-----------------------0
 *  |    DSID               | SIPID                 |
 *  -------------------------------------------------
 */
 typedef u32		DSSIPSID;

#define DS_SIP_INVALID_ID   ((u8*)0x0)

enum
{
    /* for src match */
    DS_SRC_SIP_ANY_ID = 0x0,    //ת��ʱԴ��ƥ���κ���Ϣ
    DS_SRC_SIP_MATCH_ID = 0x1,  //ת��ʱԴ����ƥ��e164��callid

    /* for modifier action */
    DS_MOD_SIP_UNTOUCH_ID = 0x0, //ת��ʱ���޸İ��е�e164��callid��Ϣ
    DS_MOD_SIP_CHANGE_ID = 0x1,  //ת��ʱ�޸İ��е�e164��callid��Ϣ
    DS_MOD_SIP_REMOVE_ID = 0x2,  //ת��ʱȥ�����е�e164��callid��Ϣ

    /* for forward to destination */
    DS_DST_SIP_TO_IP = 0x0,     //ת����ָ����ip��ַ�Ͷ˿�
    DS_DST_SIP_TO_ID = 0x1,     //ת����ָ����e164�ź�callid�ն�
};

#define DS_MAX_E164_LEN     64
#define DS_MAX_CALLID_LEN   64

/* sip�ն˵���Ϣ */
typedef struct {
    u8 e164[DS_MAX_E164_LEN];
    u8 callId[DS_MAX_CALLID_LEN];
    u16 action;     //��ʶe164��callid�е���Ϣ���ʹ��
    s16 ifindex;            //sip �ն˵���������
    dsNetAddr addr;         //sip �ն˵������ַ
} dsSipEndpoint;

#define DS_INIT_SIP_ENDPOINT(endpoint)  \
    do {    \
        (endpoint)->action = 0x0; \
        (endpoint)->ifindex = -1;   \
        memset(&((endpoint)->e164[0]), 0, sizeof((endpoint)->e164)); \
        memset(&((endpoint)->callId[0]), 0, sizeof((endpoint)->callId)); \
        memset(&(endpoint)->addr, 0, sizeof((endpoint)->addr));  \
    } while(0)

/****************************************************************
 * ����: dsCreateSipSwitch()
 * ����: ��ĳ��ip��ַ�Ͷ˿ڴ���sipswitch
 * ����:
 *   dsid: dataswitch ʵ��id
 *   addr: Ҫ����sipswitch�ĵ�ַ�Ͷ˿���Ϣ
 * ���:
 *   ����ֵdssipswitch id��������INVALID_SIPSWITCHID
 ****************************************************************/
API DSSIPSID dsCreateSipSwitch(DSID dsid, dsNetAddr *addr);

/****************************************************************
 * ����: dsAddSipSwitchRule()
 * ����: ��ĳ��sipswitch�����sip��������
 * ����:
 *   id: sipswitch��id����ʶ�������յ�ip��ַ�Ͷ˿�
 *   src: ������Դ��Ϣ������ԭip��ַ�Ͷ˿ڣ�ԭendpoint id��Ϣ��
 *        ��������Դip��ַ�Ͷ˿�ת����
 *          ����addr��Ϣ����actionΪDS_SRC_SIP_ANY_ID
 *        ��������e164��callid��Ϣת����
 *          ����e164��callid����actionΪDS_SRC_SIP_MATCH_ID
 *        ���src == NULL, �յ������а���ƥ���������.
 *
 *   modifier: ��������ת�����޸ĵ�Դ��Ϣ, ��� == NULL, ���޸�
 *         ������޸ĸ����ݰ���Դip�Ͷ˿ڣ�����addr��Ϣ
 *         ������޸ĸ����ݰ���e164��callid��Ϣ������e164��callid����
 *          action����ΪDS_MOD_SIP_CHANGE_ID����DS_MOD_SIP_REMOVE_ID
 *
 *   dst: ����ת������Ŀ����Ϣ������Ŀ��ip�Ͷ˿ڣ�Ŀ��endpoint��
 *         ���Ŀ���豸�Ĺ���ip����֪����ͨ��nat��Խ����ȡ��addr���
 *         ���Ӧ��e164��callid�������յ�nat��Խ�����Զ�������������ĵ�ַ��
 *
 *   priority: ��������ȼ�(1~100), Խ�����ȼ�Խ�ߡ�
 * ���:
 *   ����ֵDSOK��DSERROR.
 ****************************************************************/
API u32 dsAddSipSwitchRule(
    DSSIPSID id,
    dsSipEndpoint *src,
    dsSipEndpoint *modifier,
    dsSipEndpoint *dst,
    u32 priority);

/****************************************************************
 * ����: dsRemoveSipSwitchRule()
 * ����: ��ĳ��sipswitch��ɾ��sip��������
 * ����:
 *   id: �������ڵ�sipswitch��id.
 *   src: ������Դ��Ϣ������ԭip��ַ�Ͷ˿ڣ�ԭendpoint id��Ϣ��
 *        ���src == NULL, ƥ������Դ
 *   modifier: ��������ת�����޸ĵ�Դ��Ϣ, ��� == NULL, ���޸�
 *   dst: ����ת������Ŀ����Ϣ������Ŀ��ip�Ͷ˿ڣ�Ŀ��endpoint��
 * ���:
 *   ����ֵDSOK��DSERROR.
 ****************************************************************/
API u32 dsRemoveSipSwitchRule(
    DSSIPSID id,
    dsSipEndpoint *src,
    dsSipEndpoint *modifier,
    dsSipEndpoint *dst);

/****************************************************************
 * ����: dsDestroySipSwitch()
 * ����: ���һ��sipswitch
 * ����:
 *   dsid: dataswitch ʵ��id
 *   id:   sip switch id
 * ���:
 *   ����ֵDSOK��DSERROR.
 ****************************************************************/
 API u32 dsDestroySipSwitch(DSID dsid, DSSIPSID id);

/*---------------- ����sipswitch ���� -------------------------*/

/**********************************************************
 * ����: dsGetRecvBytesCount	                          *
 * ����: ��ѯ�������ֽ���                                 *
 * ����:												  *
 * ���: ��                                               *
 * ����: ���ؼ�ʱ�����ֽ���								  *
 **********************************************************/
API s64 dsGetRecvBytesCount( );

/**********************************************************
 * ����: dsGetSendBytesCount	                          *
 * ����: ��ѯ�������ֽ���                                 *
 * ����:												  *
 * ���: ��                                               *
 * ����: ���ؼ�ʱ�ֽ���									  *
 **********************************************************/
API s64 dsGetSendBytesCount( );

 /**********************************************************
 * ����: DsGetUdpSocket                               *
 * ����: ��ȡһ��dataswitch�Ķ˿�ȥ��������, �ṩ��proxy   *
 *       clientʹ���Խ���޷�ʹ��raw socket�����⡣        *
 * ����:
 * @param dsId          - DSID
 * @param ptLocAddr     - ���ص�ַ��Ϣ
 * ���: ��                                               *
 * ����: �ɹ�����socket ����invalid_socket                *
 **********************************************************/
API SOCKHANDLE DsGetUdpSocket(DSID dsId, dsNetAddr *ptLocAddr);


 /**********************************************************
 * ����: DsReleaseUdpSocket                                *
 * ����: �ͷŻ�ȡ����dataswitch socket�� �ṩ��proxy       *
 *       clientʹ���Խ���޷�ʹ��raw socket�����⡣        *
 * ����:
 * @param SOCKHANDLE          - socket
 * ���: ��                                               *
 * ����: �ɹ�����DSOK ����DSERROR                         *
 **********************************************************/
API u32 DsReleaseUdpSocket(DSID dsId, SOCKHANDLE socket);

//DsInit ExFlag
enum
{
    DS_INIT_EXT_NONE = 0x0,             //�������κ���չ��־
    DS_INIT_EXT_RTCP_NO_MAPIP = 0x1,    //rtcp��ʹ��raw socket ��ַαװ���ͣ�ֻ�ԷǶ˿ڸ��ýӿ�������
};

 /**********************************************************
 * ����: DsInit                                            *
 * ����: ��ʼ��DsInit��,������ǰ����,Ĭ�ϲ������κ���չ��־*
 * ����:                                                   *
 * @param u32          - dwExFlag                          *
 * ���: ��                                                *
 * ����: �ɹ�����DSOK ����DSERROR                          *
 **********************************************************/
API u32 DsInit(u32 dwExFlag = DS_INIT_EXT_NONE);

 /**********************************************************
 * ����: dsBindRtpRule                                     *
 * ����: ���ù�����й���                                  *
 * ����:                                                   *
 * srcId: rtpswitch��id����ʶ ��Դ �Ľ��յ�ip��ַ�Ͷ˿�  *
 * srcSrc: ��Դ��Դ��Ϣ                                  *
 * dstId: rtpswitch��id����ʶ ��Ŀ�� �Ľ��յ�ip��ַ�Ͷ˿�*
 * dstSrc: ��Ŀ�ĵ�Դ��Ϣ                                *
 * dstModifier: ��Ŀ�ĵ��޸���Ϣ                         *
 * dstDst: ��Ŀ�ĵ�Ŀ����Ϣ                              *
 * priority: ��������ȼ�(1~100), Խ�����ȼ�Խ�ߡ�         *
 * ���:                                                   *
 * ����: �ɹ�����DSOK ����DSERROR                          *
 **********************************************************/
API u32 dsBindRtpRule(DSRTPSID srcId, dsRtpEndpoint *srcSrc, DSRTPSID dstId, dsRtpEndpoint *dstSrc,
				   dsRtpEndpoint *dstModifier, dsRtpEndpoint *dstDst, u32 priority);

 /**********************************************************
 * ����: dsRmvBindRtpRule                                  *
 * ����: ɾ����������                                      *
 * ����:                                                   *
 * srcId: rtpswitch��id����ʶ ��Դ �Ľ��յ�ip��ַ�Ͷ˿�  *
 * srcSrc: ��Դ��Դ��Ϣ                                  *
 * dstId: rtpswitch��id����ʶ ��Ŀ�� �Ľ��յ�ip��ַ�Ͷ˿�*
 * dstSrc: ��Ŀ�ĵ�Դ��Ϣ                                *
 * dstModifier: ��Ŀ�ĵ��޸���Ϣ                         *
 * dstDst: ��Ŀ�ĵ�Ŀ����Ϣ                              *
 * ���:                                                   *
 * ����: �ɹ�����DSOK ����DSERROR                          *
 **********************************************************/
API u32 dsRmvBindRtpRule(DSRTPSID srcId, dsRtpEndpoint *srcSrc, DSRTPSID dstId, dsRtpEndpoint *dstSrc,
				      dsRtpEndpoint *dstModifier, dsRtpEndpoint *dstDst);


#ifdef DATASWITCH_LEGACY_H

/**********************************************************
 * ����: dsSpecifyFwdSrc                                  *
 * ����: Ϊָ�����յ�ַ����ת�����ݰ�������Դ��ַ       *
 * ����:
 * @param dsId          - DSID
 * @param OrigIP        - ԭʼIP
 * @param OrigPort      - ԭʼPort
 * @param MappedIP      - ӳ��IP
 * @param MappedPort    - ӳ��Port
 * ���: ��                                               *
 * ����: �ɹ�����DSOK ����DSERROR                         *
 **********************************************************/
API u32 dsSpecifyFwdSrc(DSID dsId, u32 OrigIP, u16 OrigPort, u32 MappedIP, u16 MappedPort);

/**********************************************************
 * ����: dsResetFwdSrc                                    *
 * ����: �ָ�ָ����ַת�����ݰ���Դ��ַ
 * ����:
 * @param dsId          - DSID
 * @param OrigIP        - ԭʼIP
 * @param OrigPort      - ԭʼPort
 * ���: ��                                               *
 * ����: �ɹ�����DSOK ����DSERROR                         *
 **********************************************************/
API u32 dsResetFwdSrc(DSID dsId, u32 OrigIP, u16 OrigPort);

#endif


/**********************************************************
 * ����: dsFlush                                          *
 * ����: �����ʵ�����н���
 * ����:
 * @param dsId          - DSID
 * ���: ��                                               *
 * ����: �ɹ�����DSOK ����DSERROR                         *
 **********************************************************/
API u32 dsFlush(DSID dsId);

#endif
