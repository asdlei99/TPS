/** @defgroup ���������
 *  @version V1.1.4
 *  @author  ylp
 *  @date    2019.4.18
 */
#pragma once

extern string g_strContentReq;

class CContentReqLogic : public CNotifyUIImpl
{
public:
	CContentReqLogic(void);
	~CContentReqLogic(void);
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

	/** ����
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnBtnCancel(TNotifyUI& msg);
	/** �˳�
	*  @param[in] ��Ϣ
	*  @return 
	*/
	bool OnBtnOk(TNotifyUI& msg);

	/** ����
	*  @param[in] ��Ϣ
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	
	APP_DECLARE_MSG_MAP()

};

int showContentReq();
#define ShowContentReq showContentReq
