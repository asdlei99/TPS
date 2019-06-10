#ifndef _USER_PASS_H_
#define _USER_PASS_H_

/* user_pass.h - 
 *
 * Copyright 1997-2002 suzhu Keda co.
 *
 * description :
 * -------------------------
 * Purpose: for user and password logging in
 *
 * modification history
 * -------------------------
 * 2004/12/14, feixp write.
 * say: �����������Ϊint������ʧ�ܷ���0����֮����ֵ����0
 *      �����������Ϊuser_pass_node *������ʧ�ܷ���NULL
 */
#if 0
#include "lib/zebra.h"
#include "lib/vty.h"
#endif

struct vty;

#ifdef __cplusplus
extern "C" {
#endif
#define USERNAME_CONFIG_ZLOG    1
#define USERNAME_LOG_LENGTH                                     512
#define  USER_PASS_LEN 32                     /*�û�����������ַ�������󳤶�*/
#define  USER_PASS_NODE_LIMIT 20         /*����������EXEC��֤���û���������ļ�¼��*/
#define  ZMSG_USER_PASS_OPTION ZMSG_USER_PASS_BASE + 1
#define ORDER_CHAR 				 4



typedef enum user_password
{
  USER_PASS_EXEC = 0,     /*EXEC ��֤*/
  USER_PASS_EXEC_SUPER,     /*EXEC SUPER ��֤*/
  USER_PASS_FTP,         /*FTP ��֤*/
  USER_PASS_TELNET,      /*TELNET ��֤*/
  USER_PASS_TELNET_SUPER,      /*TELNET ��֤*/
  USER_PASS_PPP,         /*PPP��· ��֤*/
  USER_PASS_HTTP,
  USER_PASS_MAX,         /*��֤���͵����ֵ*/
}user_password;

#ifdef SERVICE_TYPE_DIS
char *service_display[USER_PASS_MAX] = {"exec","exec super", "ftp","telnet","telnet super","ppp","http"};
#endif

typedef enum user_pass_option
{
	user_pass_check_option = 0,
	user_pass_get_option,
	user_pass_add_option,
	user_pass_del_option,
}user_pass_option;




/*****************************************************************
*   this four internface function is called by user
*
******************************************************************/


/*��ʼ��ȫ������*/
extern int user_pass_init( );
extern int user_pass_init_forppp( );



/*�ҵ���id������������Ҳ�������*/

extern int user_pass_add_usepass( int id, char * pstr_user, 
						 char * pstr_pass);

/*�ҵ���id���������, ���Ұ����û���������Ӧ�����룬���У�
�򷵻�ֵΪ1����char ** pstr_pass������Ӧ�����룬 ���򷵻�ֵΪ0*/
extern int user_pass_get_pass(int id, char * pstr_user, char * pstr_pass);

/*�ҵ���id�������������ɾ������*/
extern int  user_pass_del_usepass(int id, char * pstr_user//, 
						  /*char * pstr_pass*/);
/*��֤�û���������*/
extern int user_pass_check(int id, char * pstr_user, char * pass);

/*���������ʾ�û����������������Ϣ */
extern int config_user_pass_write_host(struct vty *vty);

/*������������û����������������Ϣ */
extern int config_user_pass_erase_host(struct vty *vty);

/*��֤�û���������,�ڿ�����±�����*/
extern int user_pass_check_interproc(int id, char * pstr_user, char * pass);

/*������user_pass_get_pass��ͬ��ֻ���ڿ�����±�����*/
extern int user_pass_get_pass_interproc(int id, char * pstr_user, char * pstr_pass);

/*�����û���������,�ڿ�����±�����*/
extern int user_pass_add_usepass_interproc(int id, char *user, char * pass);

/*ɾ���û���������,�ڿ�����±�����*/
extern int user_pass_del_usepass_interproc(int id, char *user);

/*�����������ҳ�ʼ��ȫ������*/
extern void  _user_pass_init( );


extern int username_config_error_logging(const char * fmt, ...);

/*����ָ������ļ�¼����*/
extern int user_pass_num(int id);


#ifdef __cplusplus
}
#endif

#endif/* _USER_PASS_H_ */





