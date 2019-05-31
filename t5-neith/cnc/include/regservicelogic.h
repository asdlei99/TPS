/** @defgroup ���������õ�Ԫ
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2014.12.10
 */
#pragma once
class CRegServiceLogic : public CNotifyUIImpl
{
public:
	CRegServiceLogic(void);
	~CRegServiceLogic(void);

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
	/** �Ƿ����GK 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnIsGk(TNotifyUI& msg);
	/** �Ƿ�������� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnIsQT(TNotifyUI& msg);
	/** ������Ϣ��Ӧ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** sip������ע��֪ͨ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnSipNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ע�����֪ͨ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnRegResultNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** �����ظ�֪ͨ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnRegAliasRepeatNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** GK����֪ͨ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnGkNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** GKע��ṹ֪ͨ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnGkRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ���з�����֪ͨ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCallSerNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ���з������·� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCallSerInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ����������֪ͨ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnUpSerNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ����������֪ͨ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnUpSerInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** �װ������֪ͨ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnWBServiceIPNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** �װ������֪ͨ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnWBServerInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ���Ӽ���֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnQTEncryptInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ���Ӽ���֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnQTEncryptNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** �˳���ҳ�� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnBack(TNotifyUI& msg);

	/** ���ʺ��з��������� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void SetCallServerInfo( TTPCallSerInfo tCallSerInfo );
	/** ���÷�����ip 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void SetUpgradeServiceIP(TTPUpgradeSer tUpgradeSer);
	/** ����sip������ip 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void SetSipIP(TTPSipRegistrarCfg tTPSipRegistrarCfg);

    /**	 
	* ����:  Edit����������
	* @return   
	*/
    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

	APP_DECLARE_MSG_MAP()

private:

	static const String m_strBtnFixOrCancel;	 //�޸ġ�ȡ����ť
	static const String m_strBtnOk;			 //ȷ�ϰ�ť
	static const String m_strBtnIsGk;			 //�Ƿ�ע��GK
	static const String m_strEdtRigIp;		 //ע�������ip Edit
	static const String m_strEdtGKIp;			 //GK������ip Edit
	static const String m_strEdtCallIp;		 //���з�����ip Edit
	static const String m_strEdtUpgradeIp;	 //����������ip Edit
	static const String m_strEdtDCIp;			 //���ݻ��������ip Edit
	static const String m_strEdtQTIp;	         //���Ӽ���ip Edit
	static const String m_strEdtQTID;			 //���Ӽ���ID Edit

	bool m_bIsFix;
	bool m_bIsGK;
};