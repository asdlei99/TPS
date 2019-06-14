/** @defgroup ���������߼���Ԫ 
 *  @version V1.1.4
 *  @author  dyy
 *  @date    2015-3-25
 */
#pragma once

struct TAudMixCtrls 
{
	CString strConfName;                           //�᳡��
	bool bIsSpeaker;		                     //�Ƿ��Ƿ��Ի᳡
	u16 wCnsID;                                 //��Ӧ��cnsID
	u16 wSpeakerNum;						    //�᳡����	
    EmTPEndpointType m_emEpType;			    //�������

	TAudMixCtrls()
	{
		strConfName = _T("");
		bIsSpeaker = false;
		wCnsID = TP_INVALID_INDEX;
		u16 m_wSpeakerNum = 0;
        m_emEpType = emTPEndpointTypeUnknown;
	}
};

enum EmCncListState{
	emCncListState_all,		//ȫѡ
	emCncListState_group,	//��
	emCncListState_inline,   //����
	emCncListState_outline   //������
};

class CAudMixLogic : public CNotifyUIImpl, public Singleton<CAudMixLogic>
{
public:
	CAudMixLogic(void);
	~CAudMixLogic(void);

protected:
	//�����б�
	bool UpdateList( CString strPresetName, u8 wPageID, u8 wItemID);
	//��������������۰�ť
	bool OnCheckStartDisc(TNotifyUI& msg);
	//���������ݷ�ʽ��ť
	bool OnCheckDisShortCut(TNotifyUI& msg);
	//������������
	bool OnCheckAudioExc(TNotifyUI& msg);
	/**	 
	* ����: ���»����б�
	* @return  bool
	* @remarks  
	*/
	void UpdateCnsList();
	//����״̬����
	bool OnConfStateNotify( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//ˢ���б�
	bool RefreshAudMixList( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnRefreshCnsList( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//������������ind ������ʾʧ��ԭ��
	bool OnStartAudMixInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//��ӻ�ɾ���������ۻ�Ӧ
	bool OnAudMixDisListOprInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//����������Ӧ
	bool OnAudMixVacOprInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//�л������˻�Ӧnty
	bool OnSpeakerNty( WPARAM wParam, LPARAM lParam, bool& bHandle );
	bool OnSpeakerInd( WPARAM wParam, LPARAM lParam, bool& bHandle );
	/**	 
	* ����: ���»����б�
	* @return  bool
	* @remarks  
	*/
	bool UpdateAudMixLst();
	/**	 
	* ����:  �᳡�Ƿ��Ѿ�ѡ��
	* @return  bool
	* @remarks  
	*/	
	BOOL IsInAudMixList( u16 wCnsId );
	/** ������Ӧ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ����᳡�б��е�ȷ����ť
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnSelRoomOK(TNotifyUI& msg);
	//�����б�ȫѡ
	bool OnBtnSelAll(TNotifyUI& msg);
	//�����б�ȡ��
	bool OnBtnSelCancel(TNotifyUI& msg);
	//ɾ���˻������ۻ᳡
	bool OnBtnDelDisc(TNotifyUI& msg);
	//ѡ������᳡��ַ��ɸѡcombo
	bool OnComboAddrShowEx(TNotifyUI& msg);
	//�������������ã�
	void OprAudMixCtrl( TDiscussListOpr tListOpr );
	//���Ԥ��λ�б�����
	bool OnBtnListLeft(TNotifyUI& msg);
	//���Ԥ��λ�б�����
	bool OnBtnListRight(TNotifyUI& msg);
	//������ʾ��Ԥ��λ�б� bLeft�Ƿ��������
	void UpdateShowSliderList(bool bLeft);
	/** ������������б���Ŀ
	*  @param[in] ��Ϣ
	*  @return 
	*/
	bool OnDiscussItemClick(TNotifyUI& msg);
	/** ��������б���Ŀ
	*  @param[in] ��Ϣ
	*  @return 
	*/
	bool OnSelConfItemClick(TNotifyUI& msg);
	//�����Ŀ��Ϣ
	bool OnDiscussListItem(TNotifyUI& msg);
	/** ��ѡ�᳡�б���Ŀ 
	*  @param[in] 
	*  @return 
	*/
	bool OnCheckConfItem(TNotifyUI& msg);
	//�����ӻ᳡
	bool OnBtnAddConf(TNotifyUI& msg);
	//����滻
	bool OnBtnChangeConf(TNotifyUI& msg);
	//����Ϊ���Ի᳡
	bool OnBtnSpeaker(TNotifyUI& msg);
	//����
	bool OnSearchEditChange( TNotifyUI& msg );
	//��¼�ɹ� ������ʾ��������״̬
	bool OnConnectRsp(WPARAM wParam, LPARAM lParam, bool& bHandle);
	APP_DECLARE_MSG_MAP()
public:
	bool UpdateList();

private:
	vector<TCnsInfo>         m_vctCurrentCnsList;//��ʾ��Cns�б�
	vector<TAudMixCtrls>     m_vctAudmix;//���������б�
	vector<TCnsInfo>         m_vctSelConf;//ѡ�еĻ᳡�б�
	vector<TCnsInfo>         m_vctSearchCnsList;//ѡ�еĻ᳡�б�
	int m_dwSelItemId;    //��ǰѡ�е��ڵ�ǰҳ�µ�ID
	u16 m_wCurPageIndex;  //��ǰ�б���ʼ������
	bool m_bIsSelAll;//�Ƿ�����б�ȫѡ

	bool m_bIsSearch;//�Ƿ����������
	bool m_bIsDel;//�Ƿ������ɾ��
	int  m_nSpeakerCount;//Ŀǰ�б������л᳡�������ܺ�(������˫��������)

	bool    m_bIsFirstLogin;//�Ƿ�յ�¼�ɹ�
	bool    m_bIsChangeConf;//�Ƿ��滻�᳡
	int     m_dwChangeItemIndex;//Ҫ�滻���б���λ�ñ��
};


