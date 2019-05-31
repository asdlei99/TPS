/** @defgroup ����ģ���߼���Ԫ 
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2014.12.10
 */
#pragma once

class CSysConfigLogic : public CNotifyUIImpl
{
public:
	CSysConfigLogic(void);
	~CSysConfigLogic(void);

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

	/** �����ַ������ť 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnAddrManager(TNotifyUI& msg);

	/** ���� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** ����û�����ť 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnUserManager(TNotifyUI& msg);

	/** �������������ð�ť
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnConfCallCfg(TNotifyUI& msg);
	/** ����᳡���ð�ť
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnLocalRoomControl(TNotifyUI& msg);
	/** �������������ť
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnRegService(TNotifyUI& msg);
	/** ����û��Զ��尴ť
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnUserDefined(TNotifyUI& msg);

	/** ���ȡ��
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnBack(TNotifyUI& msg);

	/** ����˳�
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnExit(TNotifyUI& msg);

	APP_DECLARE_MSG_MAP()

private:

};