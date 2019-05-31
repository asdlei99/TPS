/** @defgroup �᳡�����߼���Ԫ��ģ������ 
 *  @version V1.1.4
 *  @author  Ф��Ȼ
 *  @date    2015.1.29
 */
#pragma once
class CCnsManageLogic : public CNotifyUIImpl, public Singleton<CCnsManageLogic> 
{
public:
	CCnsManageLogic(void);
	~CCnsManageLogic(void);

	/** ���ģ����
	*  @param[in] ��Ϣ
	*  @return 
	*/
	bool OnCnsScreenItemClick(TNotifyUI& msg);
	/** �������ѡ��
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnScrSelWatch(TNotifyUI& msg);
	/** ���ȡ��ѡ��
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnCancelSelWatch(TNotifyUI& msg);
	//�������
	bool OnCheckScrLocal(TNotifyUI& msg);
	//���˫��
	bool OnCheckDualView(TNotifyUI& msg);
	//�������ǽ
	bool OnCheckTVWView(TNotifyUI& msg);
	//���÷�����ϯ
	bool OnBtnSpeakSeat1(TNotifyUI& msg);
	bool OnBtnSpeakSeat2(TNotifyUI& msg);
	bool OnBtnSpeakSeat3(TNotifyUI& msg);

	void InitCnsScreenList();

    void UpdateScreenMenu( u8 bSrcnID, CControlUI *pParent );
	
	bool OnConfStateNotify( WPARAM wParam, LPARAM lParam, bool& bHandle );
    bool OnRefreshConfCnsList( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnSelViewInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	
	bool OnCancelSelViewRsp(  WPARAM wParam, LPARAM lParam, bool& bHandle );//��ʱû��
	//������Ļ
	bool OnScreenStateNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//������ϯ
	bool OnSpokesManNotify( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//������Ӧ
	bool OnSelLocalRsp(  WPARAM wParam, LPARAM lParam, bool& bHandle  );
	bool OnCancleSelLocalRsp(  WPARAM wParam, LPARAM lParam, bool& bHandle  );
	//˫����Ӧ
	bool OnSelDualViewRsp(  WPARAM wParam, LPARAM lParam, bool& bHandle  );
	bool OnCancleDualViewRsp(  WPARAM wParam, LPARAM lParam, bool& bHandle  );
	//����˫����Ӧ
	bool OnSpareSelDualViewInd(  WPARAM wParam, LPARAM lParam, bool& bHandle  );
	bool OnSpareSelDualViewNty(  WPARAM wParam, LPARAM lParam, bool& bHandle  );
	//����ǽ��Ӧ
	bool OnSelTVSViewRsp(  WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnCancleSelTVSViewRsp(  WPARAM wParam, LPARAM lParam, bool& bHandle );

	//����������֪ͨ --add by wangkui 2016-8-23
	bool OnMuteOrSilencNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//�������֪ͨ   --add by wangkui 2016-8-23
	bool OnConfMixStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//�Ƿ��ڻ��������֪ͨ   --add by wangkui 2016-9-19
	bool OnEpInAudMixNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
    //���»������ʱ��
    void UpdateConfTime();
    void AdjustTime( time_t &time );
	
	//������������ʾ����״̬
	void RefreshCnsScreen();

	//�������ϵ�˫��״̬
	void RefreshScreenDual(u16 wScreenID);

	//����checkbox��ť״̬
	void UpDateCheckBoxState(String strCheckName, u16 wId, bool bCheck);
		/** ��������
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//ȡ��ѡ����Ļ
	void UnSelScreenList();
	//ˢ����ϯ
	void RefreshSpeakSeat();

	//���õ���ǽ����
	void EnableTVWall(int nSelIndex);
	APP_DECLARE_MSG_MAP()


private:
	CTouchListUI     *m_pSrceenList;
	int               m_nSelIndex;
    bool              m_bInConf;        //��ǰ�Ƿ��ڻ�����

    time_t            m_dwConfStartTime;            //����Ŀ�ʼʱ��
    CTimeSpan         m_tmConfDuration;             //��ǰ�������ʱ��

	static const String strCnsScreenList;
	static const String strCnsScreenListItem;

	bool m_bIsSpareDual;//�Ƿ��ڿ���ʱ��ʾ��˫�������ڿ������Ļ״̬��ˢ�£�
};

