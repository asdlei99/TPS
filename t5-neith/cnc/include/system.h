#pragma once


class CSystem : public Singleton<CSystem>
{
public:
/*
	xml标签定义
*/
	static const String strMainWindow;	// 主界面
	static const String strSkin;		// 界面路径
	static const String strDefaultSkin; // 默认皮肤路径
	static const String strPCVersion;   // 是否PC版
public:
	CSystem(void);
	CSystem(String strFile);
	~CSystem(void);

/** 系统启动 
 *  @param[in] 主xml文件 
 *  @node 
 *  @return 是否成功
 */
	bool Launch();

protected:
/** 初始化系统 
 *  @param[in] 
 *  @node 主要是读取xml配置信息
 *  @return 是否成功
 */
	bool IniSystem();

protected:
/*
	主文件路径
*/
	String m_strFile;
};



extern const String g_stcStrMainFrameDlg; 
extern const String g_stcStrLoginDlg;
extern const String g_strMainMenuDlg;
extern const String g_strAddrbookDlg;
extern const String g_strInviteCnsDlg;
extern const String g_strConfTempDlg;
extern const String g_strConfCtrlDlg;
extern const String g_strRoomControlDlg;
extern const String g_strAddrEditDlg;
extern const String g_strRegServiceDlg;
extern const String g_strUserManagerDlg;
extern const String g_strUserDefinedDlg;
extern const String g_strConfCallCfgDlg;
extern const String g_strConfMsgDlg;
extern const String g_strSysConfigDlg;
extern const String g_strLocalRoomCfgDlg;
extern const String g_strSrcSelWatchDlg;
extern const String g_strMessageBoxDlg;
extern const String g_strCalendarDlg;
extern const String g_stcStrCenterCtrlDlg; 
extern const String g_stcStrDualViewDlg; 
extern const String g_stcStrTvWallChildDlg;
extern const String g_strReconnectBox;
extern const String g_strContentReqDlg;
