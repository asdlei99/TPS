#ifdef LTP_NIP_TEST

#ifndef __MSG_H__
#define __MSG_H__

#define     HTONL(x)    (x) = htonl((x))
#define     NTOHL(x)    (x) = ntohl((x))

#define     LTP_NIP_PORT    32151   // �����������õĶ˿ں�

typedef char MODULE_TST_ITEM[32];

enum action {
    LN_DO_INIT = 0x01,      // ��ʼ������
    LN_DO_CLEANUP,          // �������ԣ��ͷ���Դ
    LN_DO_TUNNEL,           // ���Ͳ�������
    LN_ERROR = 0xee,
};

struct _tnnldata {
    u_long  handle;         // ���������
    int     port;           // ��������������ʹ�õĶ˿�
};

struct _cleanupdata {
    u_long  handle;          // ��Ҫ��ֹ�������ľ��
};


struct _initdata {
    MODULE_TST_ITEM item;   // ����������ID
    u_long  handle;         // ���������ľ��
};

struct ln_data {
    int     action;         // ����ָ��
    char    data[128];      // ��������
};


#endif

#endif
