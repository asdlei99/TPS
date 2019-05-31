/** @defgroup �û�����Ԫ
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2014.12.10
 */
#pragma once
typedef struct tagUserList
{
	CUserFullInfo UserFullInfo;
	bool bIsSel;
	tagUserList()
	{
		clear();
	}
	void clear()
	{
		UserFullInfo.Empty();
		bIsSel = false;
	}
}TUserList;


class CWBConfLogic : public CNotifyUIImpl
{
public:
	CWBConfLogic(void);
	~CWBConfLogic(void);
	    /**	 
    * ����:  ���ݻ��飬����������
    * @return   
    * @remarks ���ؿ���ʱ��������ΪT300�����֣��������ʻ����Ժ����ָ���Ϊ��������������ǰ�װ����
    */
    void UpdateWBConfName( CString strConfName );

    /**	 
    * ����:  �������ݻ��鴰�ڣ�����װ�����û���
    * @return   
    * @remarks �װ�����û���Ϊ��ǰTPAD�ͻ��˵�½ʱ��ʾ������
    */
    void CreatWBConfDlg(); 
	     /**	 
    * ����:  TPAD�޸İװ�ip����
    * @return   
    * @remarks 
    */
    void SetDataServerInfoCmd( u32 dwIp ); 
	CString iptos( u32 dwIPAddr );
protected:
		/** ���ڴ��� 
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnCreate(TNotifyUI& msg);

	/** ��ʼ����Ϣ 
	 *  @param[in] 
	 *  @return 
	 */
	bool OnInit(TNotifyUI& msg);

	bool StartJVM();

	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnConfStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnJoinWBConfNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnLeaveWBConfNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnNewConfCallReq(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnConfRoomNameNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnWBConfStartNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnCnsSetDataServerInfoNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnSelfMakeCallCmdNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnSetWBServerIpNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnCnsSetDataCnfNameNty(WPARAM wParam, LPARAM lParam, bool& bHandle);

	    /**	 
    * ����:  �������ݻ���
    * @return   
    * @remarks 
    */
    bool JoinWDConf(const IArgs& args);
    /**	 
    * ����:  ���������ݻ���
    * @return   
    * @remarks 	  
    */
    bool QuitJoinWDConf(const IArgs& args);//���������ݻ���
    /**	 
    * ����:  ֪ͨcns�Ƿ�������ݻ���
    * @return   
    * @remarks 	  
    */
    void JoinNewConfRsp( BOOL bIsJoinWBConf );

	APP_DECLARE_MSG_MAP()
private:

	BOOL m_bCreateDataConfDlg;//�Ƿ��Ѿ����������ݻ��� dyy 2014��4��28�� 
	BOOL m_bInDataConf;//�Ƿ��Ѿ����������ݻ��� dyy 2014��4��28�� 
	BOOL m_bIsSelfStartDataConf;//�Ƿ񱾶˿�ʼ�����ݻ��� dyy 2014��4��28�� 
	BOOL m_bIsSelfStartCncConf;//�Ƿ񱾶˿�ʼ����Ƶ���� dyy 2014��5��27�� 

	CString m_strConfRoomName;//�᳡��
	CString m_strConfName;//������

	u32  m_dwWBIp;//�װ����������IP dyy 2014-5-16

	CString m_strLastConfName; //���һ�����ӻ���ʱ�Ļ�����
	//WCHAR *m_pwszUserName;//�᳡��
	CString m_strUserName;
	bool m_bIsLoginWBServer;//�Ƿ����ӵ����ݻ�������� 2014-10-20 


	JNIEnv * m_jni_env;
	JavaVM * m_jni_jvm;

};