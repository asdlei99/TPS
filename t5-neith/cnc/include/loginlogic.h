/** @defgroup ��½�����߼���Ԫ 
 *  @version V1.1.4
 *  @author  Ф��Ȼ
 *  @date    2014.8.18
 */
#pragma once

class CLoginLogic : public CNotifyUIImpl, public Singleton<CLoginLogic> 
{
public:
	CLoginLogic(void);
	~CLoginLogic(void);

	void UpdateSysName();
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

	//�˺��������Ϣ�ı�
	bool OnEdUserNameTextChange(TNotifyUI& msg);


	bool OnConnectRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//��ʱ
	bool OnCnsLoginTimeOut(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//����
	bool OnUmsGrabLogin(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//����
	bool OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle );

	APP_DECLARE_MSG_MAP()
	
};

