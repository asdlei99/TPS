/** @defgroup ��������߼���Ԫ 
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    22016-7-4
 */
#pragma once

enum EMRollItemMoveMode{
	emRollMoveTop,
	emRollMoveUp,
	emRollMoveDown,
	emRollMoveBottom,
	emRollPre,//����һ����
	emRollNext,//����һ����
	emRollMoveNo,
}; 

enum EMSelConf{
	emSelConfNo,
	emSelConfRoller,//����
	emSelConfRollee,//������
}; 

enum EMAttend{
	emAttendNo,//δ���е���
	emAttend,//��ϯ
	emAbsent,//δ��ϯ
}; 
typedef struct tagTRolleeState
{
	u16	m_wEpID;							//�᳡ID
	EMAttend m_emAttend;			        //�Ƿ��ϯ
	s8	m_achRoomName[TP_MAX_ALIAS_LEN+1];	//�᳡��
	bool m_bOnline;						    //�Ƿ�����
    EmTPEndpointType m_emEpType;			//�������

	tagTRolleeState()
	{	
		Clear();
	}

	void Clear()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_emAttend = emAttendNo;
		m_achRoomName[0] = '\0';
		m_bOnline = true;
        m_emEpType = emTPEndpointTypeUnknown;
	}

}TRolleeState;

class CConfRollLogic : public CNotifyUIImpl, public Singleton<CConfRollLogic>
{
public:
	CConfRollLogic(void);
	~CConfRollLogic(void);

	void UpdateRoller();
protected:

	/** ��������������Checkbox 
	*  @param[in]                                
	*  @return 
	*/
	bool OnCheckConfRoll(TNotifyUI& msg);	
	//��������
	//bool OnCheckRollImpel(TNotifyUI& msg);	
	/** ����������������ݷ�ʽCheckbox 
	*  @param[in]                                
	*  @return 
	*/
	bool OnCheckConfRollShortCut(TNotifyUI& msg);
	/** �������״̬���·���֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnRollStateInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** �������״̬֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnRollStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ��������б��б��������״̬֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnRolleeAttendStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ���������һ������
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnRollNextInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ������Ӧ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** �������
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnRefreshCnsLstNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ���������б��޸Ļ�Ӧ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnRollLstFixedInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//���»�������б�
	void UpdateRollList(vector<TRolleeState>  vctRollList);
	void UpdateRollList(EMRollItemMoveMode emMode);
	//���µ�����Ŀ״̬
	void UpdateRollItem(u32 wItemID, EMAttend eMAttend = emAttend);
	
	//��������б������ť����
	void EnableRollBtn(bool bIsEnable);
	/** �����������б���Ŀ 
	*  @param[in] 
	*  @return 
	*/
	bool OnRollItemClicked(TNotifyUI& msg);
	/** ��������б�ѡ��
	*  @param[in] 
	*  @return 
	*/
	bool OnTimerRollList(TNotifyUI& msg);
	/** ��������б����
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnAddRoller(TNotifyUI& msg);
	bool OnBtnAdd(TNotifyUI& msg);
	bool OnBtnRollTop(TNotifyUI& msg);
	bool OnBtnRollUp(TNotifyUI& msg);
	bool OnBtnRollDown(TNotifyUI& msg);
	bool OnBtnRollBottom(TNotifyUI& msg);
	bool OnBtnRollDel(TNotifyUI& msg);
	bool OnBtnRollPre(TNotifyUI& msg);
	bool OnBtnRollNext(TNotifyUI& msg);
	//�����б����
	bool OnBtnRollSelCancel( TNotifyUI& msg );
	bool OnCheckConfItem( TNotifyUI& msg );
	bool OnBtnRollSelAll( TNotifyUI& msg );
	bool OnBtnRollSelRoomOK( TNotifyUI& msg );
	void UpdateCnsList();
	//��ݷ�ʽ����
	bool OnShortCutRoll( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//��ϯ֪ͨ��Ĭ�ϵ�����Ϊ��ϯ
	bool OnChairNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//�˳����� ״̬���
	bool OnConfStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	//����
	bool OnRollSearchEditChange( TNotifyUI& msg );

	//���ȷ�ϳ�ϯ��ť
	bool OnBtnAttend( TNotifyUI& msg );
	//���ȷ�ϲ���ϯ��ť
	bool OnBtnAbsent( TNotifyUI& msg );
	//�������״̬
	void UpDateAbsentState(EmRollCallPresentState em);
	//�����Ŀ�е�����ť
	bool OnBtnItemSelect( TNotifyUI& msg );
	//ֱ�ӵ�����һ��������һ��		
	void RollOther(CListContainerElementUI *pOri, CListContainerElementUI *pCur);
	//ָ��������
	bool OnBtnSetLeftSpeaker( TNotifyUI& msg );
	bool OnBtnSetCenterSpeaker( TNotifyUI& msg );
	bool OnBtnSetRightSpeaker( TNotifyUI& msg );
	//������ѡ�����˺ͱ�����������״̬(�������û�)
	void UpdateRollState();
	APP_DECLARE_MSG_MAP()
	
private:

	s32     m_dwSelRollItemId;			//��¼��ǰ��������ĿId
	s32     m_dwCallTargetItemId;		//��¼��ǰ����������ĿId

	vector<TCnsInfo>         m_vctCurrentCnsList;//��ʾ��Cns�б�
	vector<TCnsInfo>         m_vctCnsList;//ȫ��cns�б�
	vector<TCnsInfo>         m_vctCnsNoChildList;//û���¼��᳡��cns�б�
	vector<TCnsInfo>         m_vctSelConf;//ѡ�еĻ᳡�б�
	vector<TCnsInfo>         m_vctSearchCnsList;//�����Ļ᳡�б�
	bool m_bIsSelAll;//�Ƿ�����б�ȫѡ

	vector<TRolleeState>    m_vctRollList; //��ǰ����Ļ�������б�᳡ID
	TCnsInfo  m_tRollerInfo;            //�����˻᳡��Ϣ
	bool m_bIsSearch;					//�Ƿ����������
	EMSelConf m_emSelConf;
	TTpConfRollCallInfo m_tTpConfRollCallInfo;//����״̬��Ϣ
};

