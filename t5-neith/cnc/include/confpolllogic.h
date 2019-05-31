/** @defgroup ������ѯ�߼���Ԫ 
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2015-4-22 
 */
#pragma once

enum EMPollItemMoveMode{
	emMoveTop,
	emMoveUp,
	emMoveDown,
	emMoveBottom,
	emMoveNo,
}; 

class CConfPollLogic : public CNotifyUIImpl, public Singleton<CConfPollLogic>
{
public:
	CConfPollLogic(void);
	~CConfPollLogic(void);
	//�ⲿ���ø����б�
	void UpdatePollList();

protected:

	/** �������������ѯCheckbox 
	*  @param[in]                                
	*  @return 
	*/
	bool OnBtnCheckConfPoll(TNotifyUI& msg);	
	/** �������������ѯ��ͣ
	*  @param[in]                                
	*  @return 
	*/
	bool OnBtnCheckPause(TNotifyUI& msg);
	/** �������������ѯ��ݷ�ʽCheckbox 
	*  @param[in]                                
	*  @return 
	*/
	bool OnCheckConfPollShortCut(TNotifyUI& msg);

	/** ������ѯ��ͣ���֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnPollPauseInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ������ѯ�б���·���֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnPollListInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ������ѯ�б�֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnPollListNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ������ѯ֪ͨ
	 *  @param[in] 
	 *  @return 
	 */
	bool OnPollStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
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
	//���»�����ѯ�б�
	void UpdatePollList(vector<u16>  vctPollList);
	void UpdatePollList(EMPollItemMoveMode emMode);
	//������ѯ�б������ť����
	void EnablePollBtn(bool bIsEnable);
	/** ���������ѯ�б���Ŀ 
	*  @param[in] 
	*  @return 
	*/
	bool OnPollListClick(TNotifyUI& msg);
	/** ������ѯ�б����
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnAddPoll(TNotifyUI& msg);
	bool OnBtnPollTop(TNotifyUI& msg);
	bool OnBtnPollUp(TNotifyUI& msg);
	bool OnBtnPollDown(TNotifyUI& msg);
	bool OnBtnPollBottom(TNotifyUI& msg);
	bool OnBtnPollDel(TNotifyUI& msg);
	//�����б����
	bool OnBtnPSelCancel( TNotifyUI& msg );
	bool OnCheckPConfItem( TNotifyUI& msg );
	bool OnBtnPSelAll( TNotifyUI& msg );
	bool OnBtnPSelRoomOK( TNotifyUI& msg );
	void UpdateCnsList();
	//��cns���б������Ϣ
	bool UpdateCnsPollList(u16 wPollLstPos);//wPollLstPos �������m_vctFixedPollList����ʼλ��
	//����״̬����
	bool OnConfStateNotify( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//������ѯ�������
	bool OnStartPollRsp( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//��ݷ�ʽ����
	bool OnShortCutPoll( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//����
	bool OnSearchEditChange( TNotifyUI& msg );
	APP_DECLARE_MSG_MAP()
	
private:

	s32		m_nPollFlagInd;				//Ind�Ļ�����ѯ���±�ʶ����һ�β���ֵ���յ���һ��ind�����ind��flag��ͬ
	bool    m_bIsFirstPollListInd;		//Ind�Ļ�����ѯ�б������Ϣ������ĵ�һ��ind���˺󷢳�����flagҪ�͵�һ������ind����flag��ͬ

	s32     m_dwSelPollItemId;			//��¼��ǰ��������ĿId

	vector<TCnsInfo>         m_vctCurrentCnsList;//��ʾ��Cns�б�
	vector<TCnsInfo>         m_vctSelConf;//ѡ�еĻ᳡�б�
	vector<TCnsInfo>         m_vctSearchCnsList;//�����Ļ᳡�б�
	bool m_bIsSelAll;//�Ƿ�����б�ȫѡ

	vector<u16>    m_vctPollList;       //��ǰ����Ļ�����ѯ�б�᳡ID
	vector<u16>    m_vctFixedPollList;  //�޸ĺ�Ļ�����ѯ�б�᳡ID ���ڷ����޸���Ϣ
	bool m_bIsFixed;					//�Ƿ�������޸�
	bool m_bIsSearch;					//�Ƿ����������

    bool m_bIsSetPause;               //��ͣ��ѯ���ǻָ�
};

