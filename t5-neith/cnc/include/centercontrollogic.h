/** @defgroup �п�
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2015-3-31
 */
#pragma once

enum EmCenterCtrlTabID
{
	emTabID_Switch = 0,   //����
	emTabID_Matrix = 5,   //����
    emTabID_Srceen,       //������
	emTabID_Monitor,      //��ʾ��
	emTabID_AirCondition, //�յ�
//	emTabID_Camera,       //�ĵ������
	emTabID_Curtain,      //����
};

class CCenterCtrlLogic : public CNotifyUIImpl, public Singleton<CCenterCtrlLogic>
{
public:
	CCenterCtrlLogic(void);
	~CCenterCtrlLogic(void);

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

	/** ʧȥ������Ϣ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
/*	bool OnKillFocus(TNotifyUI& msg);*/
	
	/** ���е�
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckAllLight(TNotifyUI& msg);
	/** �����
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckConfLight(TNotifyUI& msg);
	/** ������
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckBgLight(TNotifyUI& msg);
	/** ϵͳ����checkbox���
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnShutdownSys(TNotifyUI& msg);
	/** �ĵ������checkbox���
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckCam(TNotifyUI& msg);
	/** �����ʾ��
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnTabMonitor(TNotifyUI& msg);
	/** ����յ�
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnTabAirCondition(TNotifyUI& msg);
	/** �������
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnTabSwitch(TNotifyUI& msg);
	/** �������
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnTabMatrix(TNotifyUI& msg);
    /** ���������
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnTabScreen(TNotifyUI& msg);
		/** ����ĵ������
	*  @param[in] 
	*  @node 
	*  @return 
	*/	//bool OnTabCamera(TNotifyUI& msg);
	/** �������
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnTabCurtain(TNotifyUI& msg);
	/** ������Ӧ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//�ָ����¶���ʾ
	void NoDegree();

	//�ƹ������Ӧ
	bool OnAllLightInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnConfLightInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnBgLightInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//�ܵ�
	bool OnCerterPowerInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//״̬֪ͨ
	bool OnCenterStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//�¶�֪ͨ
	bool OnSchTempNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//���ȡ��������ť
	bool OnBtnNoticeBack(TNotifyUI& msg);
	//ֹͣ�ȴ����ڸ���
	void EndWaiting();
	//�����¶���ʾ
	void UpdateTempImg( u16 wTemp );
	//����������а�ť״̬���ÿ���
	void EnableSwitch( bool bIsEnable );

    //�ĵ�������л�
    bool OnComboDCamSel(TNotifyUI& msg);
    bool OnDCamSelectedInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//�ĵ���������а�ť״̬���ÿ���
	void EnableCam( bool bIsEnable );
	//�ĵ������״̬֪ͨ
	bool OnDCamStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnDCamPowerInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//�ĵ����������
	bool OnDocSnapShotInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//�ĵ������ѡ��
	bool OnDocCamPrePosSelInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnOppreposeA3(TNotifyUI& msg);
	bool OnOppreposeA4(TNotifyUI& msg);
	bool OnOppreposeA5(TNotifyUI& msg);
	//����ĵ���������հ�ť
	bool OnBtnSnapShot(TNotifyUI& msg);
	//����ĵ�������Զ��Խ���ť
	bool OnBtnAutoFocus(TNotifyUI& msg);
	//����ĵ�������Զ���ƽ��ť
	bool OnBtnAutoWB(TNotifyUI& msg);
	//��������ĵ������Ԥ��λ��ť
	bool OnBtnSavePrepose(TNotifyUI& msg);
	//����ĵ����������Ӱ�ţ̌��
	bool OnBtnCamPlus(TNotifyUI& msg);
	//����ĵ�������������ţ̌��
	bool OnBtnCamMinus(TNotifyUI& msg);
	//����ĵ����������Ӱ�ť����
	bool OnBtnCamPlusDown(TNotifyUI& msg);
	//����ĵ�������������ť����
	bool OnBtnCamMinusDown(TNotifyUI& msg);	

	//����״̬֪ͨ
	bool OnCurtainStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//�������ֹͣ��ť
	bool OnBtnCuitainStop(TNotifyUI& msg);
	//�������������ť
	bool OnBtnCuitainUp(TNotifyUI& msg);
	//��������½���ť
	bool OnBtnCuitainDown(TNotifyUI& msg);
	//�������ȫѡ��ť
	bool OnopAll(TNotifyUI& msg);
	//������Ӧ��ѡ�����
	bool Oncurtain1(TNotifyUI& msg);
	bool Oncurtain2(TNotifyUI& msg);
	bool Oncurtain3(TNotifyUI& msg);
	bool Oncurtain4(TNotifyUI& msg);
	bool Oncurtain5(TNotifyUI& msg);
	bool Oncurtain6(TNotifyUI& msg);
	//����Ƿ�ȫѡ�˴���
	void checkCurSelAll();
	//���ô���������ư�ť����
	void SetIsCurCanCtrl(bool bCurCanCtrl);
	
	/* ����: �ĵ��������������
	* @param    const String& strRemotePath     [in]     Զ��·��
	* @param    const String& strLocalFile      [in]     ����·��
	* @param    const String& strCheckFileName     [in]     �ļ���	
	* @return   BOOL �Ƿ��ϴ��ɹ�
	* @remarks  
	*/
	BOOL DownloadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bAutoEnd /*= TRUE */ );
	/** �ĵ����������������Ӧ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnDownloadProgress(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** �ĵ�������ͺ�֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDocCamTypeInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	
	//�ĵ����������������Ӧ
	bool OnDCamZoomInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//����\�����ĵ����������������ť
	//�ڵ����̧���¼�ʱ���ð�ť���յ�ind������
	void SetZoomEnable(bool bIsEnabel);

	/** AC��Ӧ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnMonitorStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//������ʾ�����ؿ��� --add by wangkui 2016-8-24
	bool HideMonitorSwitch();
    //����ftp����
    bool OnSetCnFtpRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);

private:
	void ChangeInterface( EmDCamProType emCamModelType );
public:
	//����timer����
	void UpdateTimer();

	APP_DECLARE_MSG_MAP()
		


private:

	static const String m_strSldTab;			 //�˵�Tab
	TTPCnsInfo           m_SelCnsInfo;

	BOOL         m_bOff;   //�Ƿ�Ϊ�ر� �ر�ʱ������cns���� ԭ����Ǩ��

	int          m_nUpdateTime;
	int          m_nWaitTime;

	int          m_wLocalTemp;//�����¶�

	EmDCamRecallNum     m_emRecallNum;  //��ǰԤ��λ
	u8 m_nCurNum;    //�ײ㷢������ʵ�ʴ�������
	BOOL m_achIsCurCheck[MAX_CURTAIN_NUM];//���ش���ѡ�����

	CFtpCtrl m_cFtp;//�����ĵ����������
	CString m_strLogFolderPath;//������־����ļ���

    bool        m_bIsShotcupOpenFtp;//����ʱ��ftp

    u8          m_byDCamSelIndex;//��ǰѡ�е��ĵ��������Ŀ
};