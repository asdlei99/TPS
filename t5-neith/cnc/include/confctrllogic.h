/** @defgroup ��������߼���Ԫ 
 *  @version V1.1.4
 *  @author  Ф��Ȼ
 *  @date    2014.12.26
 */
#pragma once

enum EmConfCtrlTabID
{
	emTabID_ConfCns = 0,
	emTabID_ConfRoll,
	emTabID_ConfMix,
	emTabID_VideoMix,
	emTabID_ConfPoll,
	emTabID_AudioMix,
	emTabID_ConfDual,
	emTabID_MixMotive,
	emTabID_PIP,
    emTabID_SeatMotive,
	emTabID_TvWall,
};


enum EM_CnsListShowState{
	emShowAll,
    emShowOnLine,
    emShowOffLine,
	emShowSpeaker,
	emShowMute,
	emShowQuiet,	
	emShowDual,
}; 

class CConfCtrlLogic : public CNotifyUIImpl, public Singleton<CConfCtrlLogic>
{
public:
	CConfCtrlLogic(void);
	~CConfCtrlLogic(void);

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

	/** ����᳡Tab 
	*  @param[in] 
	*  @return 
	*/
	bool OnTabConfCns(TNotifyUI& msg);

	/** ����Tab 
	*  @param[in] 
	*  @return 
	*/	
	bool OnTabConfMix(TNotifyUI& msg);
	/** ����ϳ�Tab 
	*  @param[in] 
	*  @return 
	*/	
	bool OnTabVideoMix(TNotifyUI& msg);
	/** ������ѯTab 
	*  @param[in] 
	*  @return 
	*/	
	bool OnTabConfPoll(TNotifyUI& msg);
	/** �������Tab 
	*  @param[in] 
	*  @return 
	*/	
	bool OnTabConfRoll(TNotifyUI& msg);
	/** ��������Tab 
	*  @param[in]  
	*  @return 
	*/	
	bool OnTabAudioMix(TNotifyUI& msg);
	/** ˫����ʾTab
	*  @param[in] 
	*  @return 
	*/	
	bool OnTabConfDual(TNotifyUI& msg);
	/** ˫����ʾTab
	*  @param[in] 
	*  @return 
	*/	
	bool OnTabMixMotive(TNotifyUI& msg);
	/** ���л�Tab
	*  @param[in] 
	*  @return 
	*/	
	bool OnTabPIP(TNotifyUI& msg);
    /** ��ϯ����Tab
	*  @param[in] 
	*  @return 
	*/	
	bool OnTabSeatMotive(TNotifyUI& msg);
	/** ����ǽTab
	*  @param[in] 
	*  @return 
	*/	
	bool OnTabTVWall(TNotifyUI& msg);
	/** ��Ե������Զҡ
	*  @param[in] 
	*  @return 
	*/	
	bool OnTabFeccCam(TNotifyUI& msg);
	
	/** tabǰһҳ
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnGoLeft(TNotifyUI& msg);
	
	/** tab��һҳ
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnGoRight(TNotifyUI& msg);

	/** ���÷�����
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnSetSpeaker(TNotifyUI& msg);
	/** ָ��˫��
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnSetDual(TNotifyUI& msg);
	/** ����
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnSetQuiet(TNotifyUI& msg);
	/** ����
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnSetMute(TNotifyUI& msg);	
	/** �Ҷϻ᳡
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnHungupCns(TNotifyUI& msg);
	
	/** ����᳡�б���Ŀ 
	*  @param[in] 
	*  @return 
	*/
	bool OnConfCnsItemClick(TNotifyUI& msg);
	/** ��ѡ�᳡�б���Ŀ 
	*  @param[in] 
	*  @return 
	*/
	bool OnCheckConfCnsItem(TNotifyUI& msg);
	/** ��Ŀ�еĻ᳡���� 
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnItemSetCam(TNotifyUI& msg);
	bool OnBtnItemSetDual(TNotifyUI& msg);
	bool OnBtnItemSetSpeaker(TNotifyUI& msg);
	bool OnBtnItemSelectPlay(TNotifyUI& msg);
	bool OnBtnItemSetQuiet(TNotifyUI& msg);
	bool OnBtnItemSetMute(TNotifyUI& msg);
	bool OnBtnItemHangUp(TNotifyUI& msg);
	//���в����ߵĳ�Ա dyy 2015-6-29
	bool OnBtnItemCall(TNotifyUI& msg);
	//ѡ�� dyy 2015-7-2
	bool OnBtnCancelSelView(TNotifyUI& msg);	
	//ȡ��ȫ��ѡ��
	bool OnBtnSelectPlay(TNotifyUI& msg);	
    bool OnSearchEditChange(TNotifyUI& msg);
    bool OnComboShowEx(TNotifyUI& msg);

    //����б���·����ť
    bool OnBtnListMainPath(TNotifyUI& msg);

    void UpdateCnsItem( u16 wEpId );

	//���������ϯ����Checkbox dyy 2015-4-30 
	bool OnCheckPTPSeatArouse(TNotifyUI& msg);
	//����������ݷ�ʽ 
	bool OnCheckVSShortCut(TNotifyUI& msg);
	//���˫��Checkbox  
	bool OnCheckLocalCnsDual(TNotifyUI& msg);
	//�������˫����ݷ�ʽ 
	bool OnCheckDualShotCut(TNotifyUI& msg);
	//������л�Checkbox  
	bool OnCheckPIP(TNotifyUI& msg);
	//���л���ݷ�ʽ 
	bool OnCheckPIPShortCut(TNotifyUI& msg);
	//letterindex���
	bool OnLetterIndex(TNotifyUI& msg);
	// ѡ����Ƶ����Ŀ
	bool OnBtnVedioItemSel(TNotifyUI& msg);
	//ѡ����ƵԴ�б���һ��
	bool OnVedioItemSel(TNotifyUI& msg);
	//����������Ӧ ���ͻ�������һ��
	//bool OnVoiceArouseInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//���л���Ӧ
	bool OnPIPInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnPIPNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//˫����Ӧ
	bool OnCnsDualRsp( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnDualOffLineNotify( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnDualRcvInterruptNotify( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnRecvDualNty( WPARAM wParam, LPARAM lParam, bool& bHandle );

	bool OnConfStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnRefreshCnsLstNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);

	//����ȫ������/������ݷ�ʽ��Ӧ
	bool OnShortCutQuiteAll(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnShortCutMuteAll(WPARAM wParam, LPARAM lParam, bool& bHandle);

    //���þ���������Ӧ
    bool OnSetMuteCnsRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
    bool OnSetQuietCnsRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** ��ʾTab
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnSetTabShow(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//ˢ�¿�ݷ�ʽ
	void SetShortCutShow(EM_ShortcutType em);
	/** ��ݷ�ʽcheck״̬����
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnSetShortCheck(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ������ѯ֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	

	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

	//�л������˻�Ӧnty
	bool OnSpeakerNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnSpeakerInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//˫����Ӧ
	bool OnItemDualNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnItemDualInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//����ѡ��
	bool OnItemSelViewNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//���в����߻᳡��Ӧ
	bool OnCallOffCnsInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//����������ϯ�������ػ�Ӧ
	bool OnCnAuxInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//˫������nty
	bool OnCnsDualNty( WPARAM wParam, LPARAM lParam, bool& bHandle );

    /**	 
	* ����:  Edit����������
	* @return   
	*/
    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

	//����ƵԴ������Ϣ
	bool OnVidSrcNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** VGA��Ϣ֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	bool OnVgaInfoNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ˫���˿�֪ͨ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnSelDualPortInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool OnSelDefaultDualPortInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ������ƵԴ�б� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void UpdateVedioSourceList();

	APP_DECLARE_MSG_MAP()

public:
	void UpdateCnsList();
	void UpdateShowList();
	void OnDualWaitOverTime();

    //���ɸѡ����б�
    void GetOptnShowList( vector<TCnsInfo>& vctCurrentList );

    void UpdateListPath();
	
private:
	static const String strConfCtrlSlideTab;
	static const String strConfCnsList;
	static const String strConfCnsItem;	       //�᳡�б�Ԫ

	CTouchListUI       *m_pConfCnsList;        //����᳡�б�
	EM_CnsListShowState m_emCnsShowState;      //�᳡��ʾ״̬
    TCMSConf            m_tConfInfo;           //��ǰ������Ϣ
	int                 m_nSelIndex;   
	vector<TCnsInfo>    m_vctCnsList;          //Cns�б�
	vector<TCnsInfo>    m_vctSelectList;       //ѡ�л᳡�б�
    vector<TCnsInfo>    m_vctSearchList;       //ɸѡ�б�
    vector<TCnsInfo>    m_vctShowList;         //��ǰ��ʾ�б�
    vector<TCnsInfo>    m_vctChildCnsList;     //�¼��᳡�б�
    TCnsInfo            m_tParentCns;          //�ϼ��᳡�����ڼ�������

    BOOL                m_bSearchEdit;         //�Ƿ�������

	s32		m_nPollFlag;				//������ѯ���±�ʶ
	u16		m_wPollTotalNum;			//������ѯ������
	bool    m_bIsFirstPollListNty;		//������ѯ��һ�μ�¼��flag��֮�����һ��flag���жԱ� ��һ��ֹͣ��¼
	vector<u16>    m_vctPollList;       //������ѯ�б�᳡ID
	s32     m_CurPollItemId;			//��¼��ǰ��������ĿId

	bool    m_bIsIni;//�Ƿ��Ѿ�ini�� ���ڽ��е�Ե��л� Ϊiniʱ ������ѡ���л�
	int m_nEmShort;//��ʼ��֮ǰ�յ��Ŀ�ݷ�ʽ����

	TDualSrcInfo  m_tDualSrcInfo;
	bool m_bIsVSListExt;//�Ƿ��Ѿ�������ƵԴ�б�
	bool m_bSetVedioSourc;//�Ƿ��������ʾԴ�л�������Ѿ�������Ϣ����ind��֮ǰ���ظ�������Ϣ
};

