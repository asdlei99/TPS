/** @defgroup ���������Ի���
 *  @version V1.1.6.4.0
 *  @author  Ф��Ȼ
 *  @date    2017.9.20
 */
#pragma once
class CReconnectLogic : public CNotifyUIImpl
{
public:
	CReconnectLogic(void);
	~CReconnectLogic(void);

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

	bool OnDestroy(TNotifyUI& msg);

	/** �˳�
	*  @param[in] ��Ϣ
	*  @return 
	*/
	bool OnBtnExit(TNotifyUI& msg);
	 
	//���ӻظ�
	bool OnConnectRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);

	APP_DECLARE_MSG_MAP()
};

