/*=======================================================================
ģ����      : LTP����--�����շ�ģ��
�ļ���      : nip_ltp.h
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : JinFeng
�汾        : LTP Release 1.0
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��				�汾		�޸���					�޸�����
2006/01/09			1.0			SWP				        ����
2006/02/07			1.0			Jinfeng					�޸�
=======================================================================*/
#ifdef LTP_NIP_TEST

#ifndef __NIP_LTP_H__
#define __NIP_LTP_H__


#define   NL_MAX_TST    10

typedef  char    NL_MODULE[16];

/*----------------------------------------------------------------------
�� �� ��  : tst_list
��    ��  : ��������
ע    ��  : 
��    ��  : 
�� �� ֵ  : 
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��				�汾		�޸���					�޸�����
2006/01/09			1.0			SWP				        ����
2006/02/07			1.0			Jinfeng					�޸�
------------------------------------------------------------------------*/
struct tst_list
{
    NL_MODULE   tst;        // ����ģ����
    GList       *item;      // ������(�ڵ�)��
};


/*----------------------------------------------------------------------
�� �� ��  : nl_opts
��    ��  : 
ע    ��  : 
��    ��  : 
�� �� ֵ  : 
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��				�汾		�޸���					�޸�����
2006/01/09			1.0			SWP				        �޸�
2006/02/07			1.0			Jinfeng					����
------------------------------------------------------------------------*/
struct nl_opts {
    int (*tstdo)();         // ����ִ�е��߳�
    int (*cleanup)();       // ����ִ�н����������(������Ա�Զ���)
};


/*----------------------------------------------------------------------
�� �� ��  : nl_handle
��    ��  : 
ע    ��  : 
��    ��  : 
�� �� ֵ  : 
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��				�汾		�޸���					�޸�����
2006/01/09			1.0			SWP				        ����
2006/02/07			1.0			Jinfeng					�޸�
------------------------------------------------------------------------*/
struct nl_handle {
    MODULE_TST_ITEM item;       // ������ID
    struct nl_opts *opts;       // ������ѡ��(������Ҫ�������߳�)
    int  tunnel;                // ��������ʹ�õ�tunnel(TCP���ӵ�fd)
    int  thread_id;             // ������ִ���̵߳�ID
};
#define  NL_HANDLE   struct nl_handle

#define TESTCASE_OPT() \
static struct nl_opts opt = {  \
    .tstdo = tst_do,  \
    .cleanup = tst_cleanup,  \
};

/* Register TESTCASE ID to system */
#define TESTCASE_INIT(func_name, nl_module, module_tst_item)		 \
int func_name()		 \
{    \
		 if (nl_get_tst(nl_module) == NULL)    \
		 {   \
		 		 nl_register_tst(nl_module);    		 \
		 }    \
\
		 if (nl_register_item(module_tst_item, &opt) != 1)    /* ���ǺͿͻ���һ����ID*/\
		 {        \
		 		 printf("register item error\r\n");        \
		 		 return 0;    \
		 }    \
\
		 return 1;\
}

/* receive testdata for Driver */
#define RECV_TESTCASE(datatype) \
{ \
    if (tunnel_recv(fd, (void *)&tstdata, sizeof(struct datatype))	 \
                != sizeof(struct datatype))  \
        {   \
            tstdata.rtn = htonl(API_TST_WARNING);   \
            tunnel_send(fd, &tstdata, sizeof(struct datatype));   \
            continue;  \
        }   \
}

/* Set testcase, then get an fd to send/recv */
#define GET_TESTCASE( datatype) \
{  \
    memset(&tstdata, 0, sizeof(struct datatype));  \
    \
    while ((fd = tunnel_get(handle)) <= 0)    \
    {  \
        sleep(1);  \
    }  \
}

/* Execute testcase = main */
#define TESTCASE_EXEC(datatype, comp) \
static int \
tst_do(NL_HANDLE *handle) \
{  \
    int fd;  \
    int reval = 0;  \
    \
    struct datatype tstdata;  \
    \
    GET_TESTCASE(datatype);       \
    \
    while (1)  \
    {  \
        RECV_TESTCASE(datatype);  \
        \
        reval = self_func(&tstdata);  \
        \
        comp(reval);   \
        \
        tunnel_send(fd, &tstdata, sizeof(struct datatype));  \
    }  \
    \
    return 1;  \
}


/* compare test result with expect */
#define DEFAULT_COMP(ret)  \
{ \
    if ( ret == tstdata.val)  \
    {  \
        tstdata.val = htonl(ret);  \
        tstdata.rtn = htonl(API_TST_SUCCEED);  \
    }  \
    else  \
    {  \
        tstdata.val = htonl(ret);  \
        tstdata.rtn = htonl(API_TST_FAILED);  \
    }  \
}

/* For the logic compare in some case: !3 == !-1.
   Sometimes they told me return is non-zero  */
#define BOOL_COMP(ret)  \
{ \
    if ( !ret == !tstdata.val)  \
    {  \
        tstdata.val = htonl(ret);  \
        tstdata.rtn = htonl(API_TST_SUCCEED);  \
    }  \
    else  \
    {  \
        tstdata.val = htonl(ret);  \
        tstdata.rtn = htonl(API_TST_FAILED);  \
    }  \
}

#define TESTCASE_CLEAN() \
static int  \
tst_cleanup()  \
{  \
    return 1;  \
}  

#endif

#endif
