/** @defgroup �û��Զ��嵥Ԫ
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2014.12.20
 */
#pragma once
class CUserDefinedLogic : public CNotifyUIImpl, public Singleton<CUserDefinedLogic> 
{
public:
	CUserDefinedLogic(void);
	~CUserDefinedLogic(void);
	
	/** ����ʱ����ʾ
	 *  @param[in] 
	 *  @return 
	 */
	void UpdateTime();
     /** ���µ�ǰ�û��Ƿ��ǳ�������Ա
	*  @param[in]
	*  @node 
	*  @return 
	*/
	void UpdateSuperadmin();

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
	
	/** ������水ť
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnOk(TNotifyUI& msg);
	/** ����޸Ļ�ȡ����ť
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnFixOrCancel(TNotifyUI& msg);
	/** ���ȡ�����ذ�ť
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnCancelDownload(TNotifyUI& msg);
	/** ����Ƿ����������ڸ���
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckIsPWEpochUpdate(TNotifyUI& msg);
	/** ����Ƿ���ϵͳ������ť
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckIsSysStandby(TNotifyUI& msg);
	/** ����Ƿ���ʱ��ͬ��
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckTimeSynchro(TNotifyUI& msg);
	/** ������ذ�ť
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnDownloadLog(TNotifyUI& msg);
	/** ʱ�����õļӼ���ť
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnHMinus(TNotifyUI& msg);
	bool OnBtnHAdd(TNotifyUI& msg);
	bool OnBtnMMinus(TNotifyUI& msg);
	bool OnBtnMAdd(TNotifyUI& msg);
	bool OnBtnSMinus(TNotifyUI& msg);
	bool OnBtnSAdd(TNotifyUI& msg);
	/** ʱ��������ؿؼ��Ƿ�ɲ���
	*  @param[in] bool true����Ϊ�ɲ��� false����Ϊ���ɲ���
	*  @node 
	*  @return 
	*/
	void EnableTimeCtrl( bool bIsEnable );
	/** ˢ�´���
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnSleepInfoNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
	
	/** ��������
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** �˳���ҳ�� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnBack(TNotifyUI& msg);
	/** �˳�cnc 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnExit(TNotifyUI& msg);

	/** ��������
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	//bool savePassWord(bool bIsSave);
	/** ������������
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool saveLockPassWord(bool bIsSave);
	/** ����ϵͳʱ��
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool saveSysTime(bool bIsSave);
	/** ����ϵͳ����
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool saveSysName(bool bIsSave);
	/** �����������ڸ�����Ϣ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool savePasswordUpdateInfo();
    /** ���泬������Ա��Ϣ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool saveSuperadminInfo(bool bIsSave);
	/** ��Ϣ�޸�ʱ״̬�л� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool setFixEnable(bool bIsEnable);
	/** ����ϵͳʱ��
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void UpdateSysTime();
	/** ���´���ʱ��
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void UpdateStandbyTime();
	/** ϵͳʱ�����֪ͨ����
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	HRESULT OnUpdateSysTime( WPARAM wparam, LPARAM lparam); 
	/** ͬ��ϵͳʱ�䵽������
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	u16   SyncTimeToServ( const SYSTEMTIME sysTime  );

	/** �Ƿ���Ը��£������ǰ�����ڱ༭״̬�򲻸��£�����͸��� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	BOOL32 IsCouldUpdate();
	/** ����״̬���� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDownloadProgress(WPARAM wParam, LPARAM lParam, bool& bHandle);

	//����ʱ��
	bool OnBtnDateSet(TNotifyUI& msg);
    //ʱ��ѡ�����Ӧ
	bool OnCalendarDateSel(WPARAM wParam, LPARAM lParam, bool& bHandle);

    //���������û�
    bool OnBtnUnLockAllUser(TNotifyUI& msg);

	BOOL InprovePrivilege( );
	/** �յ�������ʱ�䷴�������±���ʱ�� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnUpdateTime( WPARAM wParam, LPARAM lParam, bool& bHandle );

    /**	 
	* ����:  Edit����������
	* @return   
	*/
    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/**	 
	* ����:  ʱ��ͬ��
	* @return   
	*/
    bool OnCnSysTimeToCnc(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** �����޸����Լ�������
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnChangeUserInfo(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//��������������Ϣ
	bool OnCnPasswordUpdateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnChangePasswordUpdateInfo(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //��������Ա��Ϣ
    bool OnSuperadminNty(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnSetCnFtpRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	APP_DECLARE_MSG_MAP()
private:

	static const String m_strBtnFixOrCancel;	//�޸ġ�ȡ����ť
	static const String m_strBtnOk;			    //ȷ�ϰ�ť
//	static const String m_strEdtOldPassword;	//�û�ԭʼ����
//	static const String m_strEdtNewPassword;	//������
//	static const String m_strEdtCheckPassword;	//����ȷ��
	static const String m_strEdtLockPassword;	//��������
	static const String m_strComboPWEpochUpdate;//�������ڸ���
	static const String m_strEdtStandbyTime;	//ϵͳ����ʱ��
	static const String m_strCheckIsSysStandby;	

	bool m_bIsFix;                               //�Ƿ���б༭
	BOOL m_bIsSysStandby;						 //�Ƿ���ϵͳ����
	BOOL m_bCouldUpdateTime;					 //�Ƿ���Ը���
	BOOL m_bIsTimeSynchro;						 //�Ƿ���ʱ��ͬ��
	CFtpCtrl m_ftp;								 //ftp����
	TCenDevSleepInfo  m_tCenDevSleepInfo;//������Ϣ

	vector<CString>   m_vctLoglist;  //��־�б�
	CString m_strLogFolderPath;//������־����ļ���
	u16 m_wLogId;//��¼�������ص���־�ļ�

	TLoginInfo m_tLoginUser;//��ʱ�����޸ĺ����룬�����ɹ�������Ϊ��ǰ�û�������Ϣ

    bool m_bWaitFtpDownLog;//�ȴ�ftp���ӳɹ���������־��־λ
};