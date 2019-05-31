/** @defgroup �����������
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2014.12.25
 */
#pragma once
class CConfCallCfgLogic : public CNotifyUIImpl
{
public:
	CConfCallCfgLogic(void);
	~CConfCallCfgLogic(void);

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
	/** ����༭���� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnOk(TNotifyUI& msg);
	/** ������б༭��ȡ���༭��ť 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnFixOrCancel(TNotifyUI& msg);
	/** ���ڵ������� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnSingleRateMinus(TNotifyUI& msg);
	bool OnBtnSingleRateAdd(TNotifyUI& msg);
	/** ������ʾ���� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnDulRateMinus(TNotifyUI& msg);
	bool OnBtnDulRateAdd(TNotifyUI& msg);
	/** ������ѯʱ�� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnPollTimeMinus(TNotifyUI& msg);
	bool OnBtnPollTimeAdd(TNotifyUI& msg);
	
	/** �Ƿ�����AES����
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckIsAESPassword(TNotifyUI& msg);
	/** �Ƿ���л�����ѯ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckIsPoll(TNotifyUI& msg);
	/** �Ƿ���л�������
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCheckIsConfDisc(TNotifyUI& msg);

	/** ��������
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
		/** ����:  ���ݷ�����������Ƶ��ʽ�ķ�����Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnUpdateAudioFormat( WPARAM wparam, LPARAM lparam, bool& bHandle );

	/** ����:  ���ݷ��������ջ�����ѡ��ʽ�ķ�����Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnUpdateVideoFormat( WPARAM wparam, LPARAM lparam, bool& bHandle );
						
	/** ����:  ���ݷ�����������ʾ��ѡ��ʽ�ķ�����Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnUpdateDualVideoFormat( WPARAM wparam, LPARAM lparam, bool& bHandle );
						
	/** ����:  ���ݷ��������յ������ʵķ�����Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnUpdateCallRate( WPARAM wparam, LPARAM lparam, bool& bHandle );
						
	/** ����:  ���ݷ�����������ʾ���ʵķ�����Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnUpdateDualCallRate( WPARAM wparam, LPARAM lparam, bool& bHandle );
						
	/** ����:  ���ݷ��������ջ������۵ķ�����Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnUpdateConfDis( WPARAM wparam, LPARAM lparam, bool& bHandle );
						
	/** ����:  ���ݷ��������ջ�����ѯ�ķ�����Ϣ�����½���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnUpdateConfPoll( WPARAM wparam, LPARAM lparam, bool& bHandle );
	/** ����:  AES֪ͨ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEncryptInfoInd( WPARAM wparam, LPARAM lparam, bool& bHandle );
	bool OnEncryptInfoNty( WPARAM wparam, LPARAM lparam, bool& bHandle );
	/** ������ذ�ť
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnBack(TNotifyUI& msg);
	/** ����˳���ť
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnExit(TNotifyUI& msg);
	/** �Ƿ���л�������
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool setFixEnable(bool bIsEnable);
	/** �������������Ƿ�ı�
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool IsAudioFormatChange();
	bool IsConfPollChange();
	bool IsConfDisChange();	
	bool IsDualCallRateChange();	
	bool IsCallRateChange();	
	bool IsDualVideoFomatChange();
	bool IsVideoFomatChange();
	bool IsConfEncryptChange();

	/** �����������ý��б���
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool SaveRate();
	bool SaveVideoFormat();
	bool SaveDualVideoFormat();
	bool SaveConfDis();
	bool SaveConfPoll();
	bool SaveAudioFormat();
	//bool SaveAESPassWord();//��ʱ����
	bool SaveConfEncryptInfo();

		/** ��ʽѡ��
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool Onop1080(TNotifyUI& msg);
	bool Onop720(TNotifyUI& msg);
	bool Onop4CIF(TNotifyUI& msg);
	bool Onop60fps(TNotifyUI& msg);
	bool Onop50fps(TNotifyUI& msg);
	bool Onop30fps(TNotifyUI& msg);
	bool Onop25fps(TNotifyUI& msg);
	bool OnopN1080(TNotifyUI& msg);
	bool OnopN720(TNotifyUI& msg);
	bool OnopN4CIF(TNotifyUI& msg);
	bool OnopUXGA(TNotifyUI& msg);
	bool OnopWXGA(TNotifyUI& msg);
	bool OnopSXGA(TNotifyUI& msg);
	bool OnopXGA(TNotifyUI& msg);
	bool OnopN60fps(TNotifyUI& msg);
	bool OnopN50fps(TNotifyUI& msg);
	bool OnopN30fps(TNotifyUI& msg);
	bool OnopN25fps(TNotifyUI& msg);
	bool OnopN5fps(TNotifyUI& msg);
	bool OnopMPEG4(TNotifyUI& msg);
	bool OnopG711A(TNotifyUI& msg);
	bool OnopG711U(TNotifyUI& msg);
	bool OnopG719(TNotifyUI& msg);
	bool OnopMP3(TNotifyUI& msg);
	bool OnopMP4(TNotifyUI& msg);
	bool OnopG772(TNotifyUI& msg);

	/** �������
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnopAESEncrypt(TNotifyUI& msg);
	bool OnopQTEncrypt(TNotifyUI& msg);
	bool OnopNoEncrypt(TNotifyUI& msg);

     /**	 
	* ����:  Edit����������
	* @return   
	*/
    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

	APP_DECLARE_MSG_MAP()

private:
	/** ������Ƶ��ʽ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void SetCallServerMode();
	/** ������ѡ��Ƶ��ʽ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void SetCallServerShowMode();
	/** ������ѡ��Ƶ��ʽ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void SetAudioFormat();
	/** �õ��ݶ�ֵ
	*  @param[in] ��ǰedit��ֵ bIsBtnPlus �Ƿ�ť�Ӳ���
	*  @node 
	*  @return 
	*/
	int GetRateFixed(int wNum, bool bIsBtnPlus = true);
	//��ѡoption����
	void EnableOp();
private:

	static const String m_strBtnFixOrCancel;	//�޸ġ�ȡ����ť
	static const String m_strBtnOk;			    //ȷ�ϰ�ť
	static const String m_strEdtOldPassword;	//�û�ԭʼ����
	static const String m_strEdtNewPassword;	//������
	static const String m_strEdtCheckPassword;	//����ȷ��
	static const String m_strEdtLockPassword;	//��������
	static const String m_strEdtAESPassword;	//ϵͳ����ʱ��
	static const String m_strCheckIsAESPassword;	

	bool m_bIsFix;			//�Ƿ���б༭
	bool m_bIsPoll;			//�Ƿ������ѯ
	bool m_bIsConfDisc;		//�Ƿ��������

	TTPVidForamt m_tVidForamt;//��Ƶ��ʽ
	TTPVidForamt m_tDualVidForamt;//��ѡ�����ʽ
	EmTpAudioFormat m_emAudioFormat;//��ѡ��Ƶ��ʽ
	TTpEncryptKey m_tEncryptInfo;//�������
};