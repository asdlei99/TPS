/*****************************************************************************
  ģ����      : KDV system
  �ļ���      : kdvsys.h
  ����ļ�    : 
  �ļ�ʵ�ֹ���: KDV�����������궨��
  ����        : ����
  �汾        : V0.9  Copyright(C) 2001-2002 KDC, All rights reserved.
  -----------------------------------------------------------------------------
  �޸ļ�¼:
  ��  ��      �汾        �޸���      �޸�����
  2002/01/30  0.9         ����        ����
  2004/03/03  3.0         jianghy       �޸�
 ******************************************************************************/
#ifndef KDVSYS_H
#define KDVSYS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// {{{ codes those irrelevant with ini files.
#if defined(_WIN32) || defined(WIN32)
#define DllExport __declspec(dllexport)
#else /* VxWorks*/
#define DllExport
#endif

/* ����س� */
#if defined(_WIN32) || defined(WIN32)
#define     STR_RETURN          (const char*)"\r\n"
#elif defined( VXWORKS_SIMU )
#define     STR_RETURN          (const char*)"\r\n"
#else /* VxWorks */
#define     STR_RETURN          (const char*)"\n"
#endif

/* SNMP����FTP�ļ��ָ�� */
#define CHAR_FTPFILE_SEPARATOR       (char)'|'   /* ��ͬ�ļ�֮��ָ��� */
#define CHAR_FTPFILETYPE_SEPARATOR   (char)':'   /* �ļ���������֮��ָ��� */
#define CHAR_EXE_TYPE                (char)'E'   /* �������ļ����� */
#define CHAR_CFG_TYPE                (char)'C'   /* �����ļ����� */
#define CHAR_RES_TYPE                (char)'R'   /* ��Դ�ļ����� */
#define CHAR_WEB_TYPE                (char)'W'   /* web�ļ����� */
#define CHAR_PIC_TYPE                (char)'P'   /* ͼƬ�ļ����� */

/* ����Profile�ļ��б����������ַ������� */
#define STR_ENTRY_NUM           (const char*)"EntryNum"
#define STR_ENTRY               (const char*)"Entry"
#define SECTION_ipRouteTable    (const char*)"ipRouteTable"
#define FIELD_ipRouteDest       (const char*)"ipRouteDest"
#define FIELD_ipRouteNextHop    (const char*)"ipRouteNextHop"
#define FIELD_ipRouteMask       (const char*)"ipRouteMask"

/* OID length */
#define OID_IP_ADDR_LEN     4 
#define OID_ID_LEN          1 

/* maximum size of physical address */
#define MAXSIZE_PHYADDR     16

typedef unsigned char   MAC_TYPE[6];

/* ·������ */
#if defined( WIN32 )  || defined(_WIN32)   /* WIN32 */
#define PATH_FTP            (const char*)"ftp"
#define PATH_CONFIG         (const char*)"conf"
#define PATH_BIN            (const char*)"."
#define PATH_RES            (const char*)"res"
#define PATH_WEB            (const char*)"webfiles/doc"
#define PATH_PIC            (const char*)"webfiles/doc/images"
#define PATH_XML            (const char*)"webfiles" //add hzc
#define PATH_DOC            (const char*)"doc"      //add hzc
#elif defined( VXWORKS_SIMU )
#define PATH_FTP            (const char*)"ftp"
#define PATH_CONFIG         (const char*)"conf"
#define PATH_BIN            (const char*)"."
#define PATH_RES            (const char*)"res"
#else                   /* vxWorks */
#define PATH_FTP            (const char*)"/ftp"
#define PATH_CONFIG         (const char*)"/conf"
#define PATH_BIN            (const char*)""
#define PATH_RES            (const char*)"res"
#define PATH_WEB            (const char*)"/webfiles/doc"
#define PATH_PIC            (const char*)"/webfiles/doc/images"
#define PATH_XML            (const char*)"/webfiles"//add hzc
#define PATH_DOC            (const char*)"doc"    //add hzc

#endif


/* semTake��ʱ */
#define WAIT_SEM_TIMEOUT    2000    /* ticks */

/* SNMP PORT macro */
#define  SNMP_PORT          161         /* port for snmp */
#define  TRAP_PORT          162         /* port for snmp traps */

/* SNMP TRAP�Զ���specificTrap */
#define SPECIFICTRAP_COLD_RESTART       1L
#define SPECIFICTRAP_POWERON            1L   //add by hzc
#define SPECIFICTRAP_POWEROFF           2L
#define SPECIFICTRAP_ALARM_GENERATE     3L
#define SPECIFICTRAP_ALARM_RESTORE      4L
#define SPECIFICTRAP_LED_STATE          5L
#define SPECIFICTRAP_CONF_STATE         6L
#define SPECIFICTRAP_MT_STATE           7L
#define SPECIFICTRAP_AUTODETECT         8L   //�Զ�̽�� //add by hzc

/* PrintMsg() typeȡֵ */
#define MESSAGE_INFO            (unsigned char  )0x1
#define MESSAGE_WARNING         (unsigned char  )0x2
#define MESSAGE_ERROR           (unsigned char  )0x3

#define MESSAGE_BUFFER_LEN      (uint16_t)1024   /* ��Ϣ�������󳤶� */

#ifndef MAX_PATH
/* �������·������ */
#define MAX_PATH                (uint16_t)256
#endif

// ����vc�������������MAX_PATHΪ260 ������Ķ��峤�ȴ��ڳ��룬����window��linux�汾��������
// �������ú궨�����MAX_PATH�궨��
#define KDV_MAX_PATH            (uint16_t)256

#ifndef MAX_LINE_LEN
/* ����һ�е���󳤶� */
#define MAX_LINE_LEN            (uint16_t)1024
#endif

#define MAX_SECTIONNAME_LEN     (uint16_t)50
#define MAX_KEYNAME_LEN         (uint16_t)50
#define MAX_VALUE_LEN           (uint16_t)255
#define MAX_WRITE_SECTIONONECE_LEN  (uint16_t)(20*100)//дһ��section����󳤶�

/* OpenProfile() byOpenMode ȡֵ */
#define PROFILE_READONLY        (unsigned char  )0x1       /*ֻ��*/
#define PROFILE_WRITE           (unsigned char  )0x2       /*��д*/
#define PROFILE_READWRITE       PROFILE_WRITE   /*��д*/
#define PROFILE_WRITEONLY       (unsigned char  )0x4       /*ֻд*/

#define PROFILE_MAX_OPEN        (uint16_t)20        /* ���ļ��������Ŀ */

typedef uint32_t                   tKeyHandle;

#define INVALID_KEYHANDLE       (uint16_t)0xFFFF    /* ��Ч���ļ���� */

/* Profile�ļ�ע�ͷ����� */
#define PROFILE_COMMENT1        (const char*)";"
#define PROFILE_COMMENT2        (const char*)"//"
#define PROFILE_COMMENT3        (const char*)"--"
#define PROFILE_COMMENT4        (const char*)"#"

/* struct definition */
typedef struct
{
    uint16_t  dwAddrLen;                      /* Length of address */
    unsigned char   phyAddress[MAXSIZE_PHYADDR];    /* physical address value */
} PHYADDR_STRUCT;

typedef struct
{
    unsigned char   byDtiNo;
    unsigned char   byE1No;
} MCU_E1_STRUCT;

typedef struct
{
    unsigned char   byDtiNo;
    unsigned char   byE1No;
    unsigned char   byTsNo;
} MCU_TS_STRUCT;

typedef struct
{
    uint32_t   dwTsNumber;                 /* TS number */
    MCU_TS_STRUCT   *ptMcuTs;         /* MCU TS array */
} MCU_TS_ARRAY_STRUCT;

typedef struct
{
    unsigned char   byE1No;
    unsigned char   byTsNo;
} MT_TS_STRUCT;

/* -----------------------  ϵͳ���ú���  ----------------------------- */
#define LOWORD16(l)     ((uint16_t)(l))
#define HIWORD16(l)     ((uint16_t)(((uint32_t)(l) >> 16) & 0xFFFF))
#define MAKEDWORD(l,h)  ((uint32_t)(((uint16_t)(l)) | ((uint32_t)((uint16_t)(h))) << 16))

#ifndef _WINDEF_  /* Ϊ���ܹ���Windows��ʹ�� */
#define LOBYTE(w)       ((unsigned char)(w))
#define HIBYTE(w)       ((unsigned char)(((uint16_t)(w) >> 8) & 0xFF))
#define MAKEWORD(l,h)   ((uint16_t)(((unsigned char)(l)) | ((uint16_t)((unsigned char)(h))) << 8))
#endif

#ifdef _DEBUG 
#undef ASSERT
#define ASSERT(exp)    \
{ \
    if ( !( exp ) ) \
    { \
        printf((char*)"Assert File %s, Line %d (%s)\n", \
                __FILE__, __LINE__, (char*)#exp ); \
    } \
}
#else
#undef ASSERT
#define ASSERT( exp )    {}
#endif

// }}}
// {{{ functions with ini files

/* ��ȡ�����ļ��ຯ�� */
DllExport int32_t GetRegKeyInt(
        const char* lpszProfileName,  /* �ļ�����������·����*/
        const char* lpszSectionName,  /* Profile�еĶ���   */
        const char* lpszKeyName,      /* ���ڵĹؼ�����    */
        const int32_t sdwDefault,       /* ʧ��ʱ���ص�Ĭ��ֵ*/
        int32_t  *sdwReturnValue        /* ����ֵ            */
        );

/* �������ļ��ж�ȡһ������ֵ */
DllExport int32_t GetRegKeyStringTable(
        const char* lpszProfileName,  /* �ļ�����������·����*/
        const char* lpszSectionName,  /* Profile�еĶ���   */        
        const char* lpszDefault,      /* ʧ��ʱ���ص�Ĭ��ֵ*/
        char* *lpszEntryArray,        /* �����ַ�������ָ�� */
        uint32_t *dwEntryNum,            /* �ַ���������Ŀ���ɹ��󷵻��ַ�������ʵ����
                                       Ŀ���紫�����Ŀ���������ļ�¼���贫�� */
        uint32_t dwBufSize               /* �����ִ��ĳ��ȣ��粻����ضϣ���
                                       ��һ���ֽ�����'\0'    */
        );

/* �������ļ��ж�ȡһ�ű�������������� */
DllExport int32_t GetRegKeyString(
        const char* lpszProfileName,  /* �ļ�����������·����*/
        const char* lpszSectionName,  /* Profile�еĶ���   */
        const char* lpszKeyName,      /* ���ڵĹؼ�����    */
        const char* lpszDefault,      /* ʧ��ʱ���ص�Ĭ��ֵ*/
        char* lpszReturnValue,        /* �����ִ�          */
        uint32_t dwBufSize               /* �����ִ��ĳ��ȣ��粻����ضϣ���
                                       ��һ���ֽ�����'\0'    */
        );

/**
 *
 * ��Ҫ��ע����:
 *
 *   ԭ���� libkdvsys.a ���ṩ�ķ��� `GetRegKeyString2' ��Ϊֱ�Ӳ���δ�ܿ���
 *   �뱣�����ļ�ָ������ڵ���ȱ�ݵ������������Ѿ��������°�� API ���ṩ�ˡ�
 *   ��ͬ�Ĺ��ܽ��ɷ��� `GetRegKeyString' �ṩ��
 *
 *   ����Ҫ������ȡһ�������ļ��е������ֵ�ʱ��ʹ�� <kprop.h> ���ṩ�������
 *   TKProps ��صķ��������Ի�ø�Ч�ķ��ʡ��μ����´���Ƭ�Σ�
 *
 *   : // ��δ�����Ҫ����˵����λ�ȡ����ֵ��ʡȥ�˴�����ļ��ȣ�
 *   : // ���ϸ�Ĳ�Ʒ����������Ӧ�ü�������ġ�
 *   : char achBuff[120];         // ����������ֵ�Ļ���
 *   : TKProps * ptProps = NULL;  // ����һ�� TKProps ����ľ�������ÿգ�
 *   : KPropsInit(&ptProps, 1);   // ����һ�� TKProps ���󣬲�ָ�����ִ�Сд
 *   : KPropsLoadPath(ptProps, "myconf.ini"); // �� myconf.ini �м��������ֵ�
 *   : KPropsGetString(ptProps,   // �� TKProps �����л�ȡ����ֵ
 *   :     "group", "key",        // ʹ��ָ���ķ��� group �͹ؼ��� key
 *   :     "def",                 // �������ó�ȱʡֵ�����δ�ҵ���
 *   :     achBuff, sizeof(achBuff)); // ������뻺��
 *   :
 *   : // ... ����ʹ�� ptProps �������������Բ�ѯ������
 *   :
 *   : KPropsDestroy(&ptProps);   // �������Ӧ���ͷŵ���������е���Դ
 *
 * ���ڷ��� `GetRegKeyString2' ԭ���Ľӿڶ������£�
 *
 * DllExport int32_t GetRegKeyString2(
 *         FILE *stream,
 *         const char* lpszSectionName,
 *         const char* lpszKeyName,
 *         const char* lpszDefault,
 *         char* lpszReturnValue,
 *         uint32_t dwBufSize
 *         );
 *
 * -- л־�֣�2015-03-04
 */

/* �����ļ�����������ļ��ж�ȡһ�ַ���ֵ�����ļ�����"rb"��ʽ�� */
DllExport int32_t SetRegKeyInt(
        const char* lpszProfileName,  /* �ļ�����������·����*/
        const char* lpszSectionName,  /* Profile�еĶ���   */
        const char* lpszKeyName,      /* ���ڵĹؼ�����    */
        const int32_t sdwValue          /* �µ�����ֵ        */
        );

/* �������ļ���д��һ�µ������͵�ֵ��������������Զ����� */
DllExport int32_t SetRegKeyString(
        const char* lpszProfileName,  /* �ļ�����������·����*/
        const char* lpszSectionName,  /* Profile�еĶ���   */
        const char* lpszKeyName,      /* ���ڵĹؼ�����    */
        const char* lpszValue         /* �µ��ִ�ֵ, NULL���ʾɾ������ */
        );

/*====================================================================
  ������      SetRegKeySection
  ����        ���������ļ���д��һ��������
                (һ�����20*100�������ô�СӦ��ε��øýӿ�д��)��
                ������������Զ�����
  �㷨ʵ��    ������ѡ�
  ����ȫ�ֱ�������
  �������˵����const char* lpszProfileName, �ļ�����������·����   
                const char* lpszSectionName, Profile�еĶ���
                const char* lpszValue, �µ��ִ�ֵ, NULL���ʾɾ��
                uint16_t wCurInSectionOffset,��ǰд��Ķ���ƫ��
                         ���磺д�����ʱ�����õĵ�����࣬����Ҫ�ֶ��д��
                const char* lpSzSectionKeepKey ����Ҫ�����Ĺؼ�����
                         ���磺дһ���ε�ʱ��Ҫ����entrynum��ֵ��
  ����ֵ˵��  ��TRUE/0
  ====================================================================*/
DllExport int32_t SetRegKeySection(
        const char* lpszProfileName, 
        const char* lpszSectionName, 
        const char* lpszValue,
        uint16_t wCurInSectionOffset,
        const char* lpSzSectionKeepKey
        );

/* �������ļ���д��һ�µ��ַ����͵�ֵ��������������Զ����� */
DllExport int32_t DeleteRegKey(
        const char* lpszProfileName,  /* �ļ�����������·����*/
        const char* lpszSectionName,  /* Profile�еĶ���   */
        const char* lpszKeyName       /* ���ڵĹؼ�����    */
        );

/* �������ļ���ɾ��һ��Key */
#if !defined( WIN32 ) && !defined(_WIN32)
DllExport int32_t ReadRouteTable( const char*  lpszProfileName );
#endif
/* �������ļ��ж�ȡ·�ɱ����� */

/* �ַ��������ຯ�� */
DllExport void Trim( char* lpszSrc );        /* ȥ���ַ�����ǰ���������ո��Լ�TAB�� */
DllExport void StrUpper( char* lpszSrc );    /* �ַ���ת���ɴ�д */
DllExport void StrLower( char* lpszSrc );    /* �ַ���ת����Сд */

/*====================================================================
  ����        ����֤�Ƿ�Ϸ�����
  �������˵����u16 wYear, ��
  unsigned char byMonth, ��
  unsigned char byDay, ��
  unsigned char byHour, ʱ
  unsigned char byMin, ��
  unsigned char bySec, ��
  ����ֵ˵��  ���Ϸ�����TRUE�����𷵻�FALSE
  ====================================================================*/
DllExport int32_t IsValidTime( uint16_t wYear, unsigned char byMonth, unsigned char byDay, 
        unsigned char byHour, unsigned char byMin, unsigned char bySec );

// }}}
#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* KDVSYS_H */

/* end of file sys.h */
/* vim:set foldmethod=marker: */
