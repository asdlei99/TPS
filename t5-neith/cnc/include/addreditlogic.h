#if !defined(AFX_ADDREDITLOGIC_H__INCLUDED_)
#define AFX_ADDREDITLOGIC_H__INCLUDED_
/** @defgroup ��ַ���༭�߼���Ԫ 
 *  @version V1.1.4
 *  @author  Ф��Ȼ
 *  @date    2015.1.29
 */
#pragma once


enum EM_AddrBookType
{
	em_AddrBook_Normal,
	em_AddrBook_Add, 
	em_AddrBook_Modify,
};

enum EM_OperateType
{
	em_AddrBook_Copy, 
	em_AddrBook_Cut,
};

class CAddrEditLogic : public CNotifyUIImpl, public Singleton<CAddrEditLogic> 
{
public:
	CAddrEditLogic(void);
	~CAddrEditLogic(void);

    void OnAddrEditTabSwitch( EmTitleTabID emTab );

    void OnWaitRefreshOverTime(); 

    void OnExitAddrEdit(); //�뿪���� 

    void UpdateTouchlist();
    void RefreshTouchlist();

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

	/** �����ַ����Ŀ 
	 *  @param[in] 
	 *  @return 
	 */
	bool OnAddrItemClick(TNotifyUI& msg);

    bool OnGlobalAddrItemClick(TNotifyUI& msg);
	//˫��������
	bool OnAddrItemDBClick( TNotifyUI& msg );

	bool OnCheckAddrItem(TNotifyUI& msg);

    bool OnBtnAddrCfg(TNotifyUI& msg);

    bool OnBtnAddrLabel(TNotifyUI& msg);

    bool OnBtnGlobalAddrLabel(TNotifyUI& msg);


    bool OnBtnSelectAll(TNotifyUI& msg);

	bool OnBtnCopy(TNotifyUI& msg);

	bool OnBtnCut(TNotifyUI& msg);

	bool OnBtnPaste(TNotifyUI& msg);

	bool OnBtnDelete(TNotifyUI& msg);

    bool OnBtnCnsIsSel(TNotifyUI& msg);

	bool DelAddrEntry();

	void GetGroupAndLowGroup( u32 dwGroupIndex, vector<u32>& vctGroup );


    bool OnComboShowEx(TNotifyUI& msg);
	/** ���������� 
	 *  @param[in] 
	 *  @return 
	 */
	bool OnComboMore(TNotifyUI& msg);

	bool OnBtnSaveAddr(TNotifyUI& msg);
	bool OnBtnCancelAddr(TNotifyUI& msg);

    bool SaveAddrEntry();
    bool SaveAddrGroup();

	/**	 
	* ����:  ��ȡ�����Ա�б�
	* @param[in]  dwGroupIndex  ������
	* @remarks  
	*/
	void GetAddrGroupMember( u32 dwGroupIndex );
    /**	 
	* ����:  ɾ���鼰���¼��� ���������Ŀ
	* @param[in]  dwGroupIndex  ������
	* @remarks  
	*/
    void DeleteGroupAndSubGroup( u32 dwGroupIndex );

	/**	 
	* ����:  ��������Ϣ��Ӧ
	* @return  bool
	* @remarks  
	*/
	bool OnSearchEditChange( TNotifyUI& msg );

    bool OnOnlineSearchEditChange( TNotifyUI& msg );

	//letterindex���
	bool OnLetterIndex(TNotifyUI& msg);
	bool OnLetterIndex2(TNotifyUI& msg);

	bool UpdateLocalAddrBook( WPARAM wParam, LPARAM lParam, bool& bHandle );

    bool UpdateGlobalAddrBook( WPARAM wParam, LPARAM lParam, bool& bHandle );

    bool OnAddEntryNty( WPARAM wParam, LPARAM lParam, bool& bHandle );

    bool OnAddGroupNty( WPARAM wParam, LPARAM lParam, bool& bHandle );

    bool OnDisconnect( WPARAM wParam, LPARAM lParam, bool& bHandle );

    bool OnAddrBookModify(WPARAM wParam, LPARAM lParam, bool& bHandle);

    bool OnAddrBookDelete(WPARAM wParam, LPARAM lParam, bool& bHandle);
	/**	 
	* ����:  ���µ�ǰ��ʾ�б�
	* @return   
	*/
	void UpdateShowList();

    void UpdateUIState();

    void UpdateGlobalUIState();

    void UpdateGlobalShowList();
	
	void UpdateLocalAddrList();
	void UpdateGlobalAddrList();

    /**	 
	* ����:  ���µ�ַ��Ŀ¼·��
	* @return   
	*/
	void UpdateAddrPath();

    //���ɸѡ����б�
    void GetOptnShowList( vector<TAddrItem>& vctCurrentList );

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

    bool OnBtnOnlineAllSel(TNotifyUI& msg);
    /**	 
	* ����:  ���ˢ��
	* @return    
	*/
    bool OnRefreshAddr(TNotifyUI& msg);

    bool OnBtnOnlineCnsIsSel(TNotifyUI& msg);
    /**	 
	* ����:  ����������
	* @return    
	*/
    bool OnBtnLoadToLocal(TNotifyUI& msg);
    /**	 
	* ����:  ��ȫ����ַ���е��루ÿ�ε���һ�����ӵ���Ӧ�������һ����
	* @return  
	* @remarks
	*/
	void LoadToLocal();

    /**	 
	* ����:  Edit����������
	* @return   
	*/
    bool OnEditSetFocus(WPARAM wParam, LPARAM lParam, bool& bHandle);

	APP_DECLARE_MSG_MAP()
		
private:
	CTouchListUI     *m_pAddrList;
    CTouchListUI     *m_pOnlineAddrList;     //ȫ�ֵ�ַ��

	vector<TAddrItem> m_vctLocalList;        //���ص�ַ���б�	
	vector<TAddrItem> m_vctGroupMemberList;  //���Ա�б�
	vector<TAddrItem> m_vctSelectList;       //ѡ���б�
	vector<TAddrItem> m_vctShowList;         //��ǰ��ʾ�б�
	vector<TAddrItem> m_vctSearchList;       //���������б�
	vector<TAddrItem> m_vctOperateList;      //ѡ�����ѱ������б�

    vector<TAddrItem> m_vctGlobalList;       //ȫ�ֵ�ַ���б�
    vector<TAddrItem> m_vctGlobalShowList;   //ȫ�ֵ�ַ����ʾ�б�
    vector<TAddrItem> m_vctGlobalSearchList; //ȫ�ֵ�ַ�����������б�
    vector<TAddrItem> m_vctGlobalSelectList; //ȫ�ֵ�ַ��ѡ���б�

    vector<TGroupInfo> m_vctGroupPath;       //��·��

	int               m_nSelIndex;			 //��ǰѡ����Ŀ����
    int               m_nGlobalSelIndex;	 //���ߵ�ַ��ѡ����Ŀ����
    EM_ItemType       m_emSelType;           //ѡ������
	TAddrItem         m_tSelItem;            //��ǰѡ����Ŀ
    TAddrItem         m_tEditItem;           //��ǰ�༭��Ŀ
	TGroupInfo        m_SelGroup;            //��ǰ������
	BOOL              m_bGlobalAddr;         //�Ƿ���ȫ�ֵ�ַ������
	BOOL              m_bSearchEdit;         //�Ƿ�������

	EM_ItemType       m_emEditType;          //�༭����
	EM_AddrBookType   m_emAddrBookType;      //���/�޸�
	EM_OperateType    m_emOperateType;       //����/����
	EM_AddrShowState  m_emShowState;         //ɸѡ״̬

    BOOL              m_bLoadToLocal;        //�Ƿ��е�ַ������     
    u32               m_dwGlobalAddrIndex;   //��¼Ҫ�����ַ�������

	static const String strAddrEditList;
};

#endif // !defined(AFX_ADDREDITLOGIC_H__INCLUDED_)

