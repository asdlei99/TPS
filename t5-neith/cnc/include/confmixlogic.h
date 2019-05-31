/** @defgroup ��������߼���Ԫ 
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2016-8-1 
 */
#pragma once


class CConfMixLogic : public CNotifyUIImpl, public Singleton<CConfMixLogic>
{
public:
	CConfMixLogic(void);
	~CConfMixLogic(void);
	//�ⲿ���ø����б�
	void UpdateMixList();
	bool IsAutoMix();

protected:

	/** ��������������Checkbox 
	*  @param[in]                                
	*  @return 
	*/
	bool OnBtnConfMixStart(TNotifyUI& msg);	
	/** ����������������ݷ�ʽCheckbox 
	*  @param[in]                                
	*  @return 
	*/
	bool OnCheckConfMixShortCut(TNotifyUI& msg);
	/** �������������Ӧ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnConfMixInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ��������б�֪ͨ
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnMixFixInd(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** �������֪ͨ
	 *  @param[in] 
	 *  @return 
	 */
	bool OnConfMixStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);
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
	//������ѡ�б������״̬
	void UpdateConfMixState();
	//���»�������б�
	void UpdateMixList(vector<u16>  vctPollList);

	/** �����������б���Ŀ 
	*  @param[in] 
	*  @return 
	*/
	bool OnMixListClick(TNotifyUI& msg);
	/** ��������б����
	*  @param[in] 
	*  @return 
	*/
	bool OnBtnAddMix(TNotifyUI& msg);
	bool OnBtnMixDel(TNotifyUI& msg);
	//�����������޸Ļ����б�
	bool FixMixlist( bool bIsAdd );
	/** �������ģʽ����
	*  @param[in] 
	*  @return 
	*/
	bool OnOpManMix(TNotifyUI& msg);
	bool OnOpAutoMix(TNotifyUI& msg);
	//�����б����
	bool OnBtnMixSelCancel( TNotifyUI& msg );
	bool OnCheckMixConfItem( TNotifyUI& msg );
	bool OnBtnMixSelAll( TNotifyUI& msg );
	bool OnBtnMixSelRoomOK( TNotifyUI& msg );
	void UpdateCnsList();

	//����״̬���� �˳����� ״̬���
	bool OnConfStateNotify( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//��ݷ�ʽ����
	bool OnShortCutConfMix( WPARAM wParam, LPARAM lParam, bool& bHandle );
	//����
	bool OnMixSearchEditChange( TNotifyUI& msg );
	bool UpdateMixList(u16 wIndex, bool bSel);//������Ŀ״̬
	APP_DECLARE_MSG_MAP()
	
private:

	vector<s32>         m_vctFixMixList;//���������������ӡ�ɾ������Ŀ

	vector<TCnsInfo>         m_vctCurrentCnsList;//��ʾ��Cns�б�
	vector<TCnsInfo>         m_vctSelConf;//ѡ�еĻ᳡�б�
	vector<TCnsInfo>         m_vctSearchCnsList;//�����Ļ᳡�б�
	bool m_bIsSelAll;//�Ƿ�����б�ȫѡ

	vector<u16>    m_vctMixList;       //��ǰ����Ļ�������б�᳡ID
	bool m_bIsSearch;					//�Ƿ����������
	TTpAudMixInfo m_tTpAudMixInfo;//����״̬
};

