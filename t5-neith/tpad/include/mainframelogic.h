/** @defgroup �������߼���Ԫ 
 *  @version V1.1.5
 *  @author  Ф��Ȼ
 *  @date    2016.6.27
 */
#if !defined(AFX_MAINFRAMELOGIC_H_)
#define AFX_MAINFRAMELOGIC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMainFrameLogic : public CNotifyUIImpl, public Singleton<CMainFrameLogic> 
{
public:
	CMainFrameLogic();
	~CMainFrameLogic();

protected:
	/** ���ڴ��� 
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnCreate(TNotifyUI& msg);

	/** ��ʼ����Ϣ 
	 *  @param[in] 
	 *  @node 
	 *  @return 
     */
    bool OnInit(TNotifyUI& msg);

	bool OnDeviceChange(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //���ӳɹ�
    bool OnConnectRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //����
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//����
	bool OnUpdateSysCmd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//�˳�
	bool OnBtnExit(TNotifyUI& msg);
	//�����ĵ�
	bool OnBtnHelp(TNotifyUI& msg);
	//����cncϵͳ����
	bool OnBtnSysConfig(TNotifyUI& msg);
	//����wifi״̬
	bool OnUpdateWifiState(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//��Դ�仯��Ϣ
	bool OnPowerBroadcast(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//�пش���
	bool OnCentreSleepNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

	bool OnDisconnectClear(WPARAM wParam, LPARAM lParam, bool& bHandle);

	bool OnCncNoReconnectNty(WPARAM wParam, LPARAM lParam, bool& bHandle);

    APP_DECLARE_MSG_MAP()
public:

	/** ����ʱ����ʾ
	 *  @param[in] 
	 *  @return 
	 */
	void UpdateTime();

    /** ini�ļ�·��
	 *  @param[in] 
	 *  @return 
	 */
    CString GetIniFilePath(CString StrAppName = _T("tpad"));

	//����������
	void UpdateSysTime(); //����ϵͳʱ��

	void UpdateWifiState(); //����wifiͼ��

	void UpdatePowerState();//���µ�Դ״̬

	bool AutoLogin(bool bSuc);//�Զ���¼����

    void ShowLoginPage();

    /** �����Ƿ������˳�
	 *  @return 
	 */
    void SetActiveExit( BOOL bActve );

    void RegDeviceChangeMsg();

    //win8ϵͳ��������Ӧ
    void OnThinkpadVolumeLow(int nStep = 1);
    void OnThinkpadVolumeAdd(int nStep = 1);		

	void ReConnectCns();

    void ShowLoginBtn();
private:
    BOOL    m_bActiveExit;      //�Ƿ������˳�
    BOOL    m_bRegDeviceChange; //�Ƿ���ӦDeviceChange��Ϣ
    int     m_nSysVol;          //ϵͳ����
	Window* m_pKeyboard;
};

#endif // !defined(AFX_MAINFRAMELOGIC_H_)