#if !defined(AFX_ADDREDITLOGIC_H__0C0D4FD7_0F38_42EE_BF69_63626132215C__INCLUDED_)
#define AFX_ADDREDITLOGIC_H__0C0D4FD7_0F38_42EE_BF69_63626132215C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// addreditlogic.h : header file
//


enum EM_AddrBookType
{
	em_AddrBook_Normal,
	em_AddrBook_Add, 
	em_AddrBook_Modify,
};

/////////////////////////////////////////////////////////////////////////////
// CAddrEditLogic dialog

class CAddrEditLogic : public CDlgChild
{
// Construction
public:
	CAddrEditLogic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddrEditLogic)
	enum { IDD = IDD_DIALOG_ADDREDIT };
	CTransparentStatic	m_stcRightTitle;
	CTransparentStatic	m_stcCnNumber;
	CTransparentStatic	m_stcCnName;
	CTransparentEdit	m_edtSearch;
	CTransparentEdit	m_edtEntryNumber;
	CTransparentEdit	m_edtEntryName;
	CTransparentBtn	m_btnSave;
	CTransparentBtn	m_btnRevoke;
	CTransparentBtn	m_btnRefresh;
	CTransparentBtn	m_btnPaste;
	CTransparentBtn	m_btnLoadToLocal;
	CTransparentBtn	m_btnEdit;
	CTransparentBtn	m_btnDeleteItem;
	CTransparentBtn	m_btnDelete;
	CTransparentBtn	m_btnCut;
	CTransparentBtn	m_btnCopy;
	CTransparentBtn	m_btnCancel;
	CTransparentBtn	m_btnBackToAddr;
	CTransparentBtn	m_btnBack;
	CTransparentBtn	m_btnAllSel;
	CTransparentBtn	m_btnAllNoSel;
	CTransparentSwitchButton	m_btnAddrShowEx;
	CTransparentBtn	m_btnAddEntry;
	CTransparentStatic	m_stcLeftTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddrEditLogic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddrEditLogic)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	/**	 
	* ����:  ������ص�ַ��
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnBtnLocalAddr();
	/**	 
	* ����:  ���ȫ�ֵ�ַ��
	* @return  bool
	* @remarks  
	*/
	afx_msg bool OnBtnGlobalAddr();
	
	/**	 
	* ����:  �������
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnBtnBack();
	/**	 
	* ����:  �����ӻ᳡
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnAddEntry();
	/**	 
	* ����:  �����ӷ���
	* @return  bool
	* @remarks  
	*/
	afx_msg bool OnAddGroup();
	/**	 
	* ����:  �������
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnSave();
	/**	 
	* ����:  ���ȡ��
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnCancel();
	/**	 
	* ����:  ����༭
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnEdit();
	/**	 
	* ����:  ��������Ϣ��Ӧ
	* @return  bool
	* @remarks  
	*/
	afx_msg LRESULT OnSearchEditChange( WPARAM wParam, LPARAM lParam );
	/**	 
	* ����:  �������
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnBtnCopy();
	/**	 
	* ����:  �������
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnBtnCut();
	/**	 
	* ����:  ���ճ��
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnBtnPaste();
	/**	 
	* ����:  �������
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnBtnRevoke();
	/**	 
	* ����:  ���ɾ��
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnBtnDelete();
    /**	 
	* ����:  ���������Ŀɾ��
	* @return  bool
	* @remarks  
	*/
    afx_msg void OnBtnDeleteItem();
	/**	 
	* ����:  �������ȫ�ֵ�ַ��
	* @return  bool
	* @remarks  
	*/	
	afx_msg void OnBtnRefreshGlobalAddr();
	/**	 
	* ����:  ���ȫѡ/��ѡ ȫ�ֵ�ַ��
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnBtnSelectAll();
	afx_msg void OnBtnUnSelectAll();

	/**	 
	* ����:  ���ȫ�ֵ��뵽���ص�ַ��
	* @return  bool
	* @remarks  
	*/
	afx_msg void OnBtnLoadToLocal();

	afx_msg LRESULT OnBtnAddrShowOptn(WPARAM wParam, LPARAM lParam);
	
	afx_msg LRESULT UpdateAddrBook(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT UpdateGlobalAddrBook( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT UpdateGlobalAddrBookEx( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnAddEntryNty(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAddGroupNty(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAddrModifyNty(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnAddrOptFailed(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWaitRefreshOverTime( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnUpdateBtnAddrOptn( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnHideAddrOptn( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnNoSelResultNotify(WPARAM wParam, LPARAM lParam);        //δѡ���κ��û��б�֪ͨ

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	/*=============================================================================
	�� �� ��:InitDlg
	��    ��:ҳ���������Ϻ��ʼ��
	��    ��:��
	ע    ��:��
	�� �� ֵ:void
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��      ��  �汾    �޸���    �޸�����
	2013/04/08  1.0     ʯ��      ����
	=============================================================================*/
	void InitDlg();

protected:
	/**	 
	* ����:  ������ص�ַ����Ŀ
	* @return  bool
	* @remarks  
	*/
	bool OnClickAddrItem( const IArgs& args );
	

	/**	 
	* ����:  ������ص�ַ���Ҳ�ͼƬ
	* @return  bool
	* @remarks  
	*/
	bool OnClickAddrItemIcon( const IArgs& args );

	/**	 
	* ����:  ��ѡ/��ѡ ��ַ����Ŀ
	* @return  bool
	* @remarks  
	*/
	bool OnSelAddrItem( const IArgs& args );
	bool OnUnSelAddrItem( const IArgs& args );

	/**	 
	* ����:  �����ѡ�б��Ҳ�ͼƬ
	* @return  bool
	* @remarks  
	*/
	bool OnClickSelectItemIcon( const IArgs& args );

	/**	 
	* ����:  ���ȫ�ֵ�ַ����Ŀ
	* @return  bool
	* @remarks  
	*/
	bool OnClickGlobalAddrItem( const IArgs& args );

	/**	 
	* ����:  ���ȫ�ֵ�ַ���Ҳ�ͼƬ
	* @return  bool
	* @remarks  
	*/
	bool OnClickGlobalAddrItemIcon( const IArgs& args );


	/**	 
	* ����:  ��ѡ���б���ɾ��
	* @return  bool
	* @remarks  
	*/
	bool OnBtnDelItem( const IArgs& args );


	bool DelAddrEntry();

	bool SaveAddrEntry();
	bool SaveAddrGroup();

	/**	 
	* ����:  ȷ������ȫ�ֵ�ַ��
	* @return  bool
	* @remarks  
	*/
	bool SureRefreshGlobalAddr();

	/**	 
	* ����:  ���µ�ǰ��ʾ�б�
	* @return  
	* @remarks  
	*/
	void UpdateShowList(); 

	/**	 
	* ����:  ���ȫѡʱ������ѡ���б�
	* @return  
	* @remarks  
	*/
	void UpdateAllSelShowList();   //���bug����Ŀ����ʱ�����ȫѡ���ʱ���ӳ�  by xhx
	
	void UpdateLocalAddrList();
	void UpdateGlobalAddrList();
	void UpdateAddrTitle();
	/**	 
	* ����:  ���½���ؼ�״̬
	* @return  
	* @remarks  
	*/
	void UpdateUIState();

	void UpdateGlobalUIState();

	void SetAddrItemInfo( TAddrInfo& tAddrInfo, CAddrEntry& cEntry );
	/**	 
	* ����:  ��ȡ�����Ա�б�
	* @param[in]  dwGroupIndex  ������
	* @remarks  
	*/
	void GetAddrGroupMember( u32 dwGroupIndex );

	/**	 
	* ����:  ɾ���鼰���¼���
	* @param[in]  dwGroupIndex  ������
	* @remarks  
	*/
	void DelGroupAndLowGroup( u32 dwGroupIndex );

    /**	 
	* ����:  ��ȡ�鼰���¼���
	* @param[in]  dwGroupIndex  ������
    * @param[out] vctGroup      �鼰�¼����б�
	* @remarks  
	*/
    void GetGroupAndLowGroup( u32 dwGroupIndex, vector<u32>& vctGroup );

	/**	 
	* ����:  �б�û��ѡ����֪ͨ
	* @return  bool
	* @remarks  
	*/
	bool UnSelAddrList( const IArgs& args );

	/**	 
	* ����:  ���¸���ճ������ɾ����ť״̬ 
	* @return  
	* @remarks  
	*/
    void UpdateCtrlButton();

    bool OnEnterAddrGroup( const IArgs& args );

    bool OnAddrOptnShowAll();
    bool OnAddrOptnShowGroup();
    bool OnAddrOptnShowOnline();
    bool OnAddrOptnShowOffline();

    //���ɸѡ����б�
    void GetOptnShowList( vector<TAddrItem>& vctCurrentList );

private:
	/*=============================================================================
    �� �� ��:InitControlPane
    ��    ��:��ʼ��ҳ��ؼ�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2013/4/7    1.0     ʯ��      ����
    =============================================================================*/
	virtual BOOL InitControlPane();

	/*=============================================================================
    �� �� ��:SetControlPos
    ��    ��:�������пؼ�Ԫ��λ��  �ṩ������Ӧ�ֱ���
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/4/8    1.0     ʯ��      ����
    =============================================================================*/
	void SetControlPos();

	/*=============================================================================
    �� �� ��:RegisterFun
    ��    ��:List�������ע��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2013/4/8    1.0     ʯ��      ����
    =============================================================================*/
	void RegisterFun();

	/*=============================================================================
    �� �� ��:InitChildWindow
    ��    ��:��ʼ���Ӵ�����ͼ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:void
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/04/08  1.0     ʯ��		����
    =============================================================================*/
	BOOL InitChildWindow();

	/**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    void Clear();

	/**	 
	* ����:  load����
	* @return   
	* @remarks	 
	*/
	void LoadScheme( String strScheme );

	/*=============================================================================
	�� �� ��:GetAddrGroupPath
	��    ��:��ȡ����·��
	��    ��:dwGroupIndex  ������
	ע    ��:
	�� �� ֵ:��
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��      ��  �汾    �޸���   �޸�����
	2012/06/01  1.0     Ф��Ȼ     ����
	=============================================================================*/
	CString GetAddrGroupPath( u32 dwGroupIndex );

	/*=============================================================================
	�� �� ��:GetAddrGroupInfo
	��    ��:��ȡ������Ϣ
	��    ��:[in]dwGroupIndex ������  
			 [out]tGroupInfo  ����Ϣ
	ע    ��:
	�� �� ֵ:��
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��      ��  �汾    �޸���   �޸�����
	2012/06/01  1.0     Ф��Ȼ     ����
	=============================================================================*/
	void GetAddrGroupInfo( u32 dwGroupIndex, TGroupInfo& tGroupInfo );

	/*=============================================================================
	�� �� ��:UpdateAddrEntryList
	��    ��:���µ�ַ����Ŀ
	��    ��:��
	ע    ��:
	�� �� ֵ:��
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��      ��  �汾    �޸���   �޸�����
	2012/06/01  1.0     Ф��Ȼ     ����
	=============================================================================*/
	void UpdateAddrEntryList();

	/*=============================================================================
	�� �� ��:UpdateLevelOneGroup
	��    ��:���µ�һ����
	��    ��:��
	ע    ��:
	�� �� ֵ:��
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��      ��  �汾    �޸���   �޸�����
	2012/06/01  1.0     Ф��Ȼ     ����
	=============================================================================*/
	void UpdateLevelOneGroup();

	/*=============================================================================
	�� �� ��:DoClickAddrItem
	��    ��:������ص�ַ����Ŀ���Ҳ���ʾ��Ŀ��Ϣ
	��    ��:��
	ע    ��:
	�� �� ֵ:��
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��      ��  �汾    �޸���   �޸�����
	2012/06/01  1.0     ʯ��     ����
	=============================================================================*/
	void DoClickAddrItem();

	/*=============================================================================
	�� �� ��:ShowSelItemInfo
	��    ��:��ʾѡ����Ŀ��Ϣ
	��    ��:��
	ע    ��:
	�� �� ֵ:��
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��      ��  �汾    �޸���   �޸�����
	2012/06/01  1.0     ʯ��     ����
	=============================================================================*/
	void ShowSelItemInfo();

	/**	 
	* ����:  ����ȫѡ�ؼ�״̬
	* @return  
	* @remarks  
	*/
    void UpdateAllSelButton();

	/**	 
	* ����:  ����ˢ�¿ؼ�״̬
	* @return  
	* @remarks  
	*/
	void UpdRefreshBtn();

	/**	 
	* ����:  ��ȫ����ַ���е��루ÿ�ε���һ�����ӵ���Ӧ�������һ����
	* @return  
	* @remarks
	*/
	void LoadToLocal();

private:
	CListChild* m_pLocalAddrList;
	CListChild* m_pGlobalAddrList;
	CLetterIndex* m_pLetterIndex;

	CListChild* m_pListSelect;


	vector<TAddrItem> m_vctLocalList;        //���ص�ַ���б�
	vector<TAddrItem> m_vctGlobalList;       //ȫ�ֵ�ַ���б�
	vector<TAddrItem> m_vctGroupMemberList;  //���Ա�б�
	vector<TAddrItem> m_vctSelectList;       //ѡ���б�
	vector<TAddrItem> m_vctShowList;         //��ǰ��ʾ�б�
	vector<TAddrItem> m_vctSearchList;       //���������б�
	vector<TAddrItem> m_vctOperateList;      //ѡ�����ѱ������б�
	
	vector<s32>       m_vctListOffset;       //��¼ÿһ���б�ƫ����
	
	TAddrItem         m_SelItem;             //��ǰѡ����Ŀ
	TGroupInfo        m_SelGroup;            //��ǰ������

	EM_ItemType       m_emEditType;          //�༭����
	EM_AddrBookType   m_emAddrBookType;      //���/�޸�
	EM_Addrbook_OperateType    m_emOperateType;       //����/����
	BOOL              m_bWaitAddEntry;       //�ȴ������Ϣ
	BOOL              m_bWaitAddGroup;
	BOOL              m_bGlobalAddr;         //�Ƿ���ȫ�ֵ�ַ������
	EM_AddrShowState  m_emShowState;         //ɸѡ״̬
	BOOL			  m_bSearchEdit;		 //����״̬
	BOOL              m_bInGroup;            //�Ƿ�������� dyy

	//---umslib���ƽӿ� 
	CCncAddrbookIF *m_pCncAddrbookIF;
	CUmsConfigCtrlIF *m_pUmsConfig;

	//BOOL m_bSipEnd;			//��ʾsip��ַ�б����Ƿ����
	//BOOL m_bGkEnd;			//��ʾGk��ַ�б����Ƿ����

	BOOL m_bLoadToLocal;        //�Ƿ��е�ַ������ by xhx
	u32  m_dwGlobalAddrIndex;   //��¼Ҫ�����ַ������� xhx
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDREDITLOGIC_H__0C0D4FD7_0F38_42EE_BF69_63626132215C__INCLUDED_)
