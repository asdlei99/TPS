/** @defgroup ϵͳ����
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2016-9-25
 */
#pragma once

enum EmDownState
{
	emDownNo = (u32)0,   //δ�����ļ����ز���
	emDowning,			 //�ļ�������
	emDownEnd,			 //�ļ����سɹ�
	emDownFail,			 //�ļ�����ʧ��
};

class CTPadUpdateLogic : public CNotifyUIImpl, public Singleton<CTPadUpdateLogic>
{
public:
	CTPadUpdateLogic(void);
	~CTPadUpdateLogic(void);
	//��ѹ�ļ�
	bool UnZip();
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

	bool OnBtnOk(TNotifyUI& msg);
	bool OnBtnCancel(TNotifyUI& msg);

	bool OnLoadTPadProgress( WPARAM wParam, LPARAM lParam, bool& bHandle );

    //����ftp����
    bool OnSetCnFtpRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	
	//�����ļ�
	bool DownLoadFile();
    bool BeginDownload();

	/** ����
	*  @param[in] ��Ϣ
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

	APP_DECLARE_MSG_MAP()

private:

	CFtpCtrl         m_cFtp;
	EmFtpStatus      m_emFtpStatus;
	TTPTPadVerInfo   m_tTPadVerInfo;   
	int              m_nProgress;        //���ؽ���
	CString          m_strSavePath;      //�����ļ�����·��
	EmDownState      m_emDownState;		 //�ļ�����״̬
    bool             m_bIsWaitForFtp;    //�ȴ�����ftp������
};
