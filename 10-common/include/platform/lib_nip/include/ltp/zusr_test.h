/*=======================================================================
模块名      : ZUSER测试
文件名      : 
相关文件    : 
文件实现功能: 
作者        : feixiaoping
版本        : LTP Release 1.0
-------------------------------------------------------------------------
修改记录:
日  期				版本		修改人					修改内容
2006/02/14			1.0			feixiaoping					创建
=======================================================================*/
#ifdef LTP_NIP_TEST

#ifndef _ZUSR_TEST_H_
#define _ZUSR_TEST_H_

#include <sys/mman.h>

#if 0
enum preset_type
{
    PRE_DEL  = -1,         // 环境搭建
    TESTCASE,　　　　�// 测试数据
    PRE_ADD       // 环境搭建
};
#endif


enum rtn_type
{
    ZUSR_TST_SUCCEED = 0,   // 测试成功
    ZUSR_TST_WARNING,   // 警告
    ZUSR_TST_FAILED,    // 测试失败
};

#if 1
enum preset_type
{
	PRE_DEL = -1,
	TESTCASE = 0,
	PRE_ADD = 1,
};
#endif

#define MAXZUSRLEN 256
#define NULL_STR "*"
/*------------------------------------*/
//struct for nip testing
struct zusr_add_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* 预期结果 */
   int val;
   int     rtn;
};

/*------------------------------------*/
//struct for nip testing
struct zusr_get_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* 预期结果 */
    int val;
    int     rtn;
};

/*------------------------------------*/
//struct for nip testing
struct zusr_del_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* 预期结果 */
    int val;
    int     rtn;
};

/*------------------------------------*/
//struct for nip testing
struct zusr_check_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* 预期结果 */
    int val;
    int     rtn;
};

/*interproc*/
/*------------------------------------*/
//struct for nip testing
struct zusr_add_interproc_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* 预期结果 */
    int val;
    int     rtn;
};

/*------------------------------------*/
//struct for nip testing
struct zusr_del_interproc_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* 预期结果 */
    int val;
    int     rtn;
};

/*------------------------------------*/
//struct for nip testing
struct zusr_check_interproc_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* 预期结果 */
    int val;
    int     rtn;
};

/*------------------------------------*/
//struct for nip testing
struct zusr_get_interproc_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* 预期结果 */
    int val;
    int     rtn;
};

#endif

#endif

