#ifndef _NETCBB_WEBS_H_
#define _NETCBB_WEBS_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define NET_WEBS_ENABLE          1
#define NET_WEBS_DISABLE         2
#define NET_WEBS_INSPECT_ENABLE  3
#define NET_WEBS_INSPECT_DISABLE 4

#define NET_WEBS_ERR_BASE        100

#define NET_WEBS_PORT_ERR       (NET_WEBS_ERR_BASE+1)  /* ¶Ë¿Ú°ó¶¨³ö´í */

s32 NetcbbWebsEnable(s32 port);
s32 NetcbbWebsDisable(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_WEBS_H_ */
