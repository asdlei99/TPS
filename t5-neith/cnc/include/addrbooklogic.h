/** @defgroup ��ַ���߼���Ԫ 
 *  @version V1.1.4
 *  @author  Ф��Ȼ
 *  @date    2014.8.18
 */
#pragma once
class CAddrBookLogic : public CNotifyUIImpl, public Singleton<CAddrBookLogic> 
{
public:
	CAddrBookLogic(void);
	~CAddrBookLogic(void);

	void P2PCallFail();
    void OnWaitRefreshOverTime();
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

	/** ˢ��
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnBtnRefresh(TNotifyUI& msg);

	/** ��ѡ��Ŀ
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnCheckAddrItem(TNotifyUI& msg);
	/** ����
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnBtnAddrCall(TNotifyUI& msg);

    bool OnBtnAddrLabel(TNotifyUI& msg);

	/** �����ַ����Ŀ
	*  @param[in] ��Ϣ
	*  @return 
	*/
	bool OnAddrItemClick(TNotifyUI& msg);
	bool OnAddrItemDBClick(TNotifyUI& msg);
    /** �������᳡
	*  @param[in] ��Ϣ
	*  @return 
	*/
    bool OnBtnInviteCns(TNotifyUI& msg);

    bool OnBtnCnsIsSel(TNotifyUI& msg);

    /** �������
	*  @param[in] ��Ϣ
	*  @return 
	*/
    bool OnBtnAddrConfig(TNotifyUI& msg);

    /** �����ʱ����
	*  @param[in] ��Ϣ
	*  @return 
	*/
    bool OnBtnTemporaryCall(TNotifyUI& msg);

    /**	 
	* ����:  �����ַ���ص���·��
	* @return   
	*/
    bool OnBtnAddrMainPath(TNotifyUI& msg);
    /**	 
	* ����:  �����ַ����·��
	* @return   
	*/
    bool OnBtnGroupPath1(TNotifyUI& msg);


    bool OnBtnNoticeBack(TNotifyUI& msg);
	

	bool UpdateLocalAddrBook(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnConfStateNotify(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnHungupConfInd(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnDisconnect(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnUpdateGlobalAddrBook(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnAddrBookModify(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnAddrBookDelete(WPARAM wParam, LPARAM lParam, bool& bHandle);

	//������ʾ�����б�
	void UpdateShowList();
	void UpdateLocalAddrList();
	void UpdateGlobalAddrList();
	void UpdateGroupMemberList( u32 dwGroupIndex );
    //���ɸѡ����б�
    void GetOptnShowList( vector<TAddrItem>& vctList );

    /**	 
	* ����:  ���µ�ַ��Ŀ¼·��
	* @return   
	*/
	void UpdateAddrPath();

    bool OnComboShowEx( TNotifyUI& msg );

    bool OnSearchEditChange( TNotifyUI& msg );

	//letterindex���
	bool OnLetterIndex(TNotifyUI& msg);

    /**	 
	* ����:  ���������᳡
	* @return   
	*/
    bool OnBtnAddrInviteOther( TNotifyUI& msg );

    /**	 
	* ����:  ��ʱ����
	* @return   
	*/
    bool OnBtnAddrTemporaryCall( TNotifyUI& msg );

    /**	 
	* ����:  Edit����������
	* @return   
	*/
    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

	APP_DECLARE_MSG_MAP()

private:
	CTouchListUI     *m_pAddrList;

	vector<TAddrItem> m_vctLocalList;            //��һ�����ص�ַ���б�
	vector<TAddrItem> m_vctEntryList;            //���ص�ַ��������Ŀ
	vector<TAddrItem> m_vctGroupMemberList;      //�����Ա�б�
	vector<TAddrItem> m_vctSelectList;           //ѡ���б�
	vector<TAddrItem> m_vctSearchList;           //���������б�
	vector<TAddrItem> m_vctShowList;             //��ǰʵ����ʾ���б�
    vector<TGroupInfo> m_vctGroupPath;           //��·��

    EM_ItemType       m_emSelType;            //ѡ������
    BOOL              m_bSearchEdit;
	int               m_nSelIndex;  
    TGroupInfo        m_SelGroup;            //��ǰ������
    EM_AddrShowState  m_emAddrShowState;     //ɸѡ״̬

	static const String strAddrList;
	static const String strAddrListItem;	 //��ַ���б�Ԫ
	static const String strAddrName;	     //��ַ����Ŀ��
	static const String strAddrE164;	     //��ַ��E164��
};

