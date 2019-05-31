/** @defgroup ��½�����߼���Ԫ 
 *  @version V1.1.5
 *  @author  Ф��Ȼ
 *  @date    2016.6.27
 */
#pragma once

class CLoginLogic : public CNotifyUIImpl
{
public:
	CLoginLogic(void);
	~CLoginLogic(void);

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

	/** ��½
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnBtnLogin(TNotifyUI& msg);

    /** ��������
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
    bool OnBtnNetCfg(TNotifyUI& msg);

    /** �ػ�
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
    bool OnBtnPowerOff(TNotifyUI& msg);

	//�Զ���¼�ͼ�ס����
	bool OnCheckAutoLogin( TNotifyUI& msg );
	bool OnCheckRemPassWord( TNotifyUI& msg );

	//�˺��������Ϣ�ı�
	bool OnEdUserNameTextChange(TNotifyUI& msg);

	bool OnConnectRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//��ʱ
	bool OnCnsLoginTimeOut(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//����
	bool OnUmsGrabLogin(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//����
	bool OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//ϵͳ���޸�
	bool OnSysNameChange( WPARAM wParam, LPARAM lParam, bool& bHandle );

	APP_DECLARE_MSG_MAP()
private:
    BOOL    m_bHaveLogin;      //�Ƿ��½�ɹ���
};

