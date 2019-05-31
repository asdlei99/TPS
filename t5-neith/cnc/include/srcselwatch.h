/** @defgroup ����ѡ������
 *  @version V1.1.4
 *  @author  ��ӨӨ
 *  @date    2015-2-11 
 */
#pragma once

class CSrcSelWatchLogic : public CNotifyUIImpl, public Singleton<CSrcSelWatchLogic>
{
public:
	CSrcSelWatchLogic(void);
	~CSrcSelWatchLogic(void);

	//ȡ��ѡ��
	void CancelSelWatch(int nIndex);
		/** ˢ���û��б� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	void UpdateCnsInfoList();

    //����ѡ����
    void ReSetSelScreen();
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

	/** ����б���Ŀ��Ϣ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnCnsInfoListItemClick(TNotifyUI& msg);
	/** �����ѡ�б���Ŀ��Ϣ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnSelConfInfoListItemClick(TNotifyUI& msg);
	/** ���ˢ�°�ť 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnRefreshCnsInfoList(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/** ��������
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** ���� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/	
	bool OnSearchEditChange(TNotifyUI& msg);
	/** �����Ϊ��1 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnSetWatch1(TNotifyUI& msg);
	/** �����Ϊ��2 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnSetWatch2(TNotifyUI& msg);
	/** �����Ϊ��3 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnSetWatch3(TNotifyUI& msg);
	/** ��ʾ��ѡ
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnShowSel(TNotifyUI& msg);
	/** ȡ�� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnCancel(TNotifyUI& msg);
	/** ȷ�� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnOK(TNotifyUI& msg);
	/** �����ѡ�б��еİ�ť ��ʾѡ��Ļ᳡λ�� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnGetSelItemInMainList(TNotifyUI& msg);
	/** ȡ����ǰ��Ļѡ�� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnCancelCurWatch(TNotifyUI& msg);
	/** ȡ������ѡ�� 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnCancelWatch(TNotifyUI& msg);
	/** �����᳡��ʾ��Ļѡ��
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnShowScreenOption(TNotifyUI& msg);
	/** �����᳡������Ļѡ��
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnHideScreenOption(TNotifyUI& msg);
	/** �᳡ѡ��
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnBtnRoomWatch(TNotifyUI& msg);
	/** �᳡ѡ��checkbox
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnListBtnRoomSel(TNotifyUI& msg);
	/** ��������б���Ŀ��Ϣ 
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnScreenSlectListItemClick(TNotifyUI& msg);
	/** ѡ��nty
	*  @param[in] 
	*  @node 
	*  @return 
	*/
	bool OnSelViewNty(WPARAM wParam, LPARAM lParam, bool& bHandle);

	bool OnConfStateNty(WPARAM wParam, LPARAM lParam, bool& bHandle);

    /**	 
	* ����:  Edit����������
	* @return   
	*/
    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

	/** ��ק
	*  @param[in] 
	*  @node 
	*  @return 
	*/
    bool OnDragIsStart(TNotifyUI& msg);
	bool OnDragDrop(TNotifyUI& msg);
	bool OnDragEnter(TNotifyUI& msg);
	bool OnDragLeave(TNotifyUI& msg);
	bool OnDragDone(TNotifyUI& msg);
    bool OnDragIsOver(TNotifyUI& msg);

	//letterindex���
	bool OnLetterIndex(TNotifyUI& msg);

	//��ѡ�б�ˢ��
	void UpdateSelList();
	bool SetScreenWatch(int nScreenID);
	
	//�ָ���ʼ����
	void RestoreInitUI();
	APP_DECLARE_MSG_MAP()

private:
	
	vector<TSelViewInfo>  m_vctCnsInfoList;        //���ص�ַ���б� 
	vector<TSelViewInfo>  m_vctSearchLst;   //�û������б� 
	TSelViewInfo m_aSelWatch[3];			    //������Ӧ����Ŀ
	TSelViewInfo m_tCurSelectViewInfo;          //��ǰѡ����Ŀ��Ϣ
	TCMSConf            m_tConfInfo;            //��ǰ������Ϣ
	BOOL                m_bSearchEdit;          //�Ƿ�������

	static const String m_strCnsInfoList;       //�û��б�  
	static const String m_strCnsInfoListItem;   //�û��б���Ŀ
	static const String m_strSeachEdit;	     //������edit

	u16 m_wCurrentSelIndex;                  //��ǰѡ����Ŀ���
	bool m_bIsGetScreenState;//�ж��Ƿ��Ѿ�����ѡ�б���screen��Ϣͬ��
	bool m_bIsVideoMix;//�Ƿ�������ϳ�   
	bool m_bIsClickBtnCancelWatch;//�Ƿ�����"ȡ��ѡ��"��ť

    bool m_bIsNeedUpdate;//�Ƿ���Ҫˢ�£���ק֮��
    bool m_bIsDraging;//������ק�ؼ�
};