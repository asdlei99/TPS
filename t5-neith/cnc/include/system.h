#pragma once


class CSystem : public Singleton<CSystem>
{
public:
/*
	xml��ǩ����
*/
	static const String strMainWindow;	// ������
	static const String strSkin;		// ����·��
	static const String strDefaultSkin; // Ĭ��Ƥ��·��
	static const String strPCVersion;   // �Ƿ�PC��
public:
	CSystem(void);
	CSystem(String strFile);
	~CSystem(void);

/** ϵͳ���� 
 *  @param[in] ��xml�ļ� 
 *  @node 
 *  @return �Ƿ�ɹ�
 */
	bool Launch();

protected:
/** ��ʼ��ϵͳ 
 *  @param[in] 
 *  @node ��Ҫ�Ƕ�ȡxml������Ϣ
 *  @return �Ƿ�ɹ�
 */
	bool IniSystem();

protected:
/*
	���ļ�·��
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
