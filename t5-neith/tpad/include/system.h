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
extern const String g_strMessageBoxDlg;
extern const String g_strFilemanagerDlg;
extern const String g_strFilePreviewDlg;
extern const String g_strToolWnd;
extern const String g_strWbManager;
extern const String g_strVideoDlg;
extern const String g_strAboutDlg;
extern const String g_strModalDlg;
extern const String g_strNetCfgDlg;
extern const String g_strUpdateDlg;
extern const String g_strUdiscUpdateDlg;
extern const String g_strReconnectBox;