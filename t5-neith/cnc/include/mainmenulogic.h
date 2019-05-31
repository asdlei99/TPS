/** @defgroup ������Ŀ¼�߼���Ԫ 
 *  @version V1.1.4
 *  @author  Ф��Ȼ
 *  @date    2014.12.11
 */

#pragma once
class CMainMenuLogic : public CNotifyUIImpl, public Singleton<CMainMenuLogic>
{
public:
	CMainMenuLogic(void);
	~CMainMenuLogic(void);

	void OnExtendMainMenu();
protected:
	/** ���ڴ��� 
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnCreate(TNotifyUI& msg);

	/** ��ʼ����Ϣ 
	 *  @param[in] 
	 *  @return 
	 */
	bool OnInit(TNotifyUI& msg);

	/** ���չ��/���� 
	 *  @param[in] 
	 *  @return 
	 */
	bool OnBtnExtend(TNotifyUI& msg);

	/** �����ַ�� 
	 *  @param[in]  
	 *  @return 
	 */
	bool OnBtnAddrBook(TNotifyUI& msg);

	/** �������ģ�� 
	 *  @param[in] 
	 *  @return 
	 */
	bool OnBtnConfTemp(TNotifyUI& msg);
	
	/** ����᳡���� 
	 *  @param[in] 
	 *  @return 
	 */
	bool OnBtnRoomCtrl(TNotifyUI& msg);
	/** ����������
	 *  @param[in] 
	 *  @return 
	 */
	bool OnBtnConfCtrl(TNotifyUI& msg);

	/** �������
	 *  @param[in] 
	 *  @return
	 */
	bool OnBtnSysCfg(TNotifyUI& msg);
	/** �����Ϣ��ʾ
	 *  @param[in] 
	 *  @return 
	 */
	bool OnBtnMsg( TNotifyUI& msg );
	/** �����ݷ�ʽ��ť
	 *  @param[in] 
	 *  @return 
	 */
	bool OnBtnShortCutState( TNotifyUI& msg );
	/** ����п�
	 *  @param[in] 
	 *  @return 
	 */
	bool OnBtnCenterCtrl(TNotifyUI& msg);    
    /** �������᳡
	 *  @param[in] 
	 *  @return 
	 */
    bool OnBtnInviteCns(TNotifyUI& msg);
    /** �����������
	 *  @param[in] 
	 *  @return 
	 */
    bool OnBtnEndConf(TNotifyUI& msg);
	/** �����ݲ�������
	 *  @param[in] 
	 *  @return 
	 */
	bool OnBtnShortCutListSet(TNotifyUI& msg);
	/** ��ݲ���������Ϣ
	 *  @param[in] 
	 *  @return 
	 */
	bool OnShortCutNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ��ݲ���״̬ˢ��
	 *  @param[in] 
	 *  @return 
	 */
	bool OnShortCutStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ��������������Ϣ
	 *  @param[in] 
	 *  @return 
	 */
	bool OnStartConfDiscNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ��ݲ���������Ϣ
	 *  @param[in] 
	 *  @return 
	 */
	bool OnPanCamStartNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ���л�֪ͨ
	 *  @param[in] 
	 *  @return 
	 */
	bool OnPIPNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnPIPInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ˫��֪ͨ
	 *  @param[in] 
	 *  @return 
	 */
	bool OnCnsDualRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//��Ե�����������Ӧ
	bool OnCnPTPAuxInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//����״̬
	bool OnRollStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//����״̬
	bool OnConfMixStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ��������֪ͨ
	 *  @param[in] 
	 *  @return 
	 */
	bool OnMuteOrSliencNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ������ѯ֪ͨ
	 *  @param[in] 
	 *  @return 
	 */
	bool OnPollStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ������ѯ��֪ͣͨ
	 *  @param[in] 
	 *  @return 
	 */
	bool OnPollPauseInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ������Ӧ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ���¿�ݲ����б�
	 *  @param[in] 
	 *  @return 
	 */
	void UpdateShortCutLst();

	/** ��ÿ�ݷ�ʽ��Ŀcontainer
	 *  @param[in] emShortcutType ��Ŀ����
	 *  @param[out] ContainerElementUI ��Ŀ����
	 *  @return 
	 */
	void GetItemContainer(EM_ShortcutType emShortcutType);

	//���������ѯ��ͣ��ť
	bool OnBtnPollPause(TNotifyUI& msg);

    /** ����״̬֪ͨ
	 *  @param[in] 
	 *  @return 
	 */	
	bool OnConfStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);

    /** �Ҷϻ���
	 *  @param[in] 
	 *  @return 
	 */	
    bool HungupConf();

    bool OnVidMIxStatusNty(WPARAM wParam, LPARAM lParam, bool& bHandle);

public:
	 /** �����ݷ�ʽ��ini
	 *  @param[in] 
	 *  @return 
	 */	
	void SaveShortCutToIni();
	//������� ��Ӧ��Ŀ�ظ�δѡ״̬
	bool OnContainerClick( TNotifyUI& msg );
	//���»������״̬	
	void UpdateConfMixState();
	APP_DECLARE_MSG_MAP()
private:
	HWND m_hWnd;     //g_strMainMenuDlg���
	BOOL m_bExtend;  //menu�Ƿ�չ��
	CControlUI        *m_pBtnMsg;
	CControlUI        *m_pBtnSysCfg;

	s32  m_nMainMenuInitHeight; //MainMenuDlg��ʼ�߶�

	vector<EM_ShortcutType> m_vctShortCutList;  //��ݷ�ʽ�б�
	CListContainerElementUI* m_pContainerElementUI;//��ǰѡ�еĿ�ݷ�ʽ

	RECT m_rectBtnCfg;
	RECT m_rectBtnMsg;
};

